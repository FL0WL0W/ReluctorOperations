#include <stdint.h>
#include "CrankCamDecoders/Gm24xDecoderNew.h"

namespace CrankCamDecoders
{
	Gm24xDecoderNew::Gm24xDecoderNew(const HardwareAbstraction::HardwareAbstractionCollection *hardwareAbstractionCollection, const uint16_t pin)
	{
		_hardwareAbstractionCollection = hardwareAbstractionCollection;
		_pin = pin;
		_hardwareAbstractionCollection->DigitalService->ScheduleRecurringInterrupt(_pin, new HardwareAbstraction::CallBack(InterruptCallBack, this));
		_isSynced = false;
		_lastCrankTick = 0;
		_crankPeriod   = 0;
		_state		   = 0;
		_crankState	   = 0;
	}
	
	unsigned int Gm24xDecoderNew::crankTime()
	{
		unsigned int crankTick = _hardwareAbstractionCollection->TimerService->GetTick();
		if (crankTick < _lastCrankTick)
		{
			return crankTick + (4294967295 - _lastCrankTick);
		}
		return crankTick - _lastCrankTick;
	}
	
	float Gm24xDecoderNew::GetPosition(void)
	{
		return _state * 15 + (crankTime() * 15) / (float)_crankPeriod;
	}
	
	uint32_t Gm24xDecoderNew::GetTickPerDegree(void)
	{
		return _crankPeriod / 15;
	}
	
	unsigned short Gm24xDecoderNew::GetRpm(void)
	{
		return ((60 * _hardwareAbstractionCollection->TimerService->GetTicksPerSecond()) / 24) / _crankPeriod;
	}
		
	bool Gm24xDecoderNew::IsSynced()
	{
		return _isSynced;
	}

	void Gm24xDecoderNew::InterruptCallBack(void *decoder)
	{
		reinterpret_cast<Gm24xDecoderNew *>(decoder)->Interrupt();
	}

	void Gm24xDecoderNew::Interrupt()
	{
		bool rising = _hardwareAbstractionCollection->DigitalService->ReadPin(_pin);

		if (!rising)
		{
			unsigned int crankTick = _hardwareAbstractionCollection->TimerService->GetTick();
			if (crankTick < _lastCrankTick)
			{
				_crankPeriod = crankTick + (4294967295 - _lastCrankTick);
			}
			else
			{
				_crankPeriod = crankTick - _lastCrankTick;
			}
			
			_state++;
			if (_state > 23)
			{
				_state = 0;
			}
			
			_lastCrankTick = crankTick;
		}
		else
		{
			unsigned int crankTick = _hardwareAbstractionCollection->TimerService->GetTick();
			unsigned int interumCrankPeriod = 0;
			if (crankTick < _lastCrankTick)
			{
				interumCrankPeriod = crankTick + (4294967295 - _lastCrankTick);
			}
			else
			{
				interumCrankPeriod = crankTick - _lastCrankTick;
			}
			
			if (interumCrankPeriod > _crankPeriod * 0.6)
			{
				//short pulse
				//    _
				//|__| |
				//   ^
				_crankState = 0;
				
			}
			else
			{
				//long pulse
				//   __
				//|_|  |
				//  ^
				_crankState++;
				if (_crankState == 5)
				{
					_state = 5;
					_isSynced = true;
				}
			}
		}
	}
}