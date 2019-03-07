#include <stdint.h>
#include "Decoder/Gm24xDecoder.h"

namespace Decoder
{
	Gm24xDecoder::Gm24xDecoder(const HardwareAbstraction::HardwareAbstractionCollection *hardwareAbstractionCollection, const uint16_t pin)
	{
		_hardwareAbstractionCollection = hardwareAbstractionCollection;
		_pin = pin;
		_hardwareAbstractionCollection->DigitalService->ScheduleRecurringInterrupt(_pin, new HardwareAbstraction::CallBack(InterruptCallBack, this));
		_isSynced = false;
		_lastTick = 0;
		_period   = 0;
		_state	  = 0;
		_subState = 0;
	}
	
	const uint32_t Gm24xDecoder::time() const
	{
		uint32_t tick = _hardwareAbstractionCollection->TimerService->GetTick();
		if (tick < _lastTick)
			return tick + (4294967295 - _lastTick);
		return tick - _lastTick;
	}
	
	float Gm24xDecoder::GetPosition(void)
	{
		return _state * 15 + (time() * 15) / static_cast<float>(_period);
	}
	
	uint32_t Gm24xDecoder::GetTickPerDegree(void)
	{
		return _period / 15;
	}
	
	uint16_t Gm24xDecoder::GetRpm(void)
	{
		return ((60 * _hardwareAbstractionCollection->TimerService->GetTicksPerSecond()) / 24) / _period;
	}
		
	uint16_t Gm24xDecoder::GetResolution()
	{
		return 24;
	}

	bool Gm24xDecoder::IsSynced()
	{
		return _isSynced;
	}

	void Gm24xDecoder::InterruptCallBack(void *decoder)
	{
		reinterpret_cast<Gm24xDecoder *>(decoder)->Interrupt();
	}

	void Gm24xDecoder::Interrupt()
	{
		bool rising = _hardwareAbstractionCollection->DigitalService->ReadPin(_pin);

		uint32_t tick = _hardwareAbstractionCollection->TimerService->GetTick();
			
		if (!rising)
		{
			if (tick < _lastTick)
				_period = tick + (4294967295 - _lastTick);
			else
				_period = tick - _lastTick;
			
			_state++;
			if (_state > 23)
				_state = 0;
			
			_lastTick = tick;
		}
		else if(_period != 0)
		{
			uint32_t interumPeriod;
			if (tick < _lastTick)
				interumPeriod = tick + (4294967295 - _lastTick);
			else
				interumPeriod = tick - _lastTick;
			
			if (interumPeriod > _period * 0.6)
			{
				//short pulse
				//    _
				//|__| |
				//   ^
				_subState = 0;
			}
			else
			{
				//long pulse
				//   __
				//|_|  |
				//  ^
				_subState++;
				if (_subState == 5)
				{
					_state = 5;
					_isSynced = true;
				}
			}
		}
	}
}