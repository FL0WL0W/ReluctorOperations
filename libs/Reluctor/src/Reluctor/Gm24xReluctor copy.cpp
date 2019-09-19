// #include <stdint.h>
// #include "Reluctor/Gm24xReluctor.h"

// namespace Reluctor
// {
// 	Gm24xReluctor::Gm24xReluctor(const HardwareAbstraction::HardwareAbstractionCollection *hardwareAbstractionCollection, const uint16_t pin)
// 	{
// 		_hardwareAbstractionCollection = hardwareAbstractionCollection;
// 		_pin = pin;
// 		_hardwareAbstractionCollection->DigitalService->ScheduleRecurringInterrupt(_pin, new HardwareAbstraction::CallBack<Gm24xReluctor>(this, &Gm24xReluctor::InterruptCallBack));
// 		_isSynced = false;
// 		_lastTick = 0;
// 		_period   = 0;
// 		_state	  = 0;
// 		_subState = 0;
// 	}
	
// 	float Gm24xReluctor::GetPosition()
// 	{
// 		float position;
// 		do
// 		{
// 			_interruptCalled = false;
// 			position = _state * 15 + (_hardwareAbstractionCollection->TimerService->GetElapsedTick(_lastTick) * 15) / static_cast<float>(_period);
// 		} while(_interruptCalled);
		
// 		return position;
// 	}
	
// 	float Gm24xReluctor::GetTickPerDegree(void)
// 	{
// 		return _period / 15.0f;
// 	}
	
// 	uint16_t Gm24xReluctor::GetRpm(void)
// 	{
// 		return ((60 * _hardwareAbstractionCollection->TimerService->GetTicksPerSecond()) / 24) / _period;
// 	}
		
// 	uint16_t Gm24xReluctor::GetResolution()
// 	{
// 		return 24;
// 	}

// 	bool Gm24xReluctor::IsSynced()
// 	{
// 		if(_isSynced && _hardwareAbstractionCollection->TimerService->GetElapsedTick(_lastTick) > _period * 2)
// 			_isSynced = false;
// 		return _isSynced;
// 	}

// 	void Gm24xReluctor::InterruptCallBack()
// 	{
// 		bool rising = _hardwareAbstractionCollection->DigitalService->ReadPin(_pin);
// 		uint32_t tick = _hardwareAbstractionCollection->TimerService->GetTick();

// 		int32_t elapsedTick = tick - _lastTick;

// 		if(_isSynced && elapsedTick < 0)
// 			return;

// 		if (!rising)
// 		{
// 			_period = elapsedTick;
			
// 			_state++;
// 			if (_state > 23)
// 				_state = 0;
			
// 			if(tick == 0)
// 				_lastTick = 1;
// 			else
// 				_lastTick = tick;
// 		}
// 		else if(_period != 0)
// 		{
// 			uint32_t interumPeriod = elapsedTick;
			
// 			if (interumPeriod > _period * 0.6)
// 			{
// 				//short pulse
// 				//    _
// 				//|__| |
// 				//   ^
// 				_subState = 0;
// 			}
// 			else
// 			{
// 				//long pulse
// 				//   __
// 				//|_|  |
// 				//  ^
// 				_subState++;
// 				if (_subState == 5)
// 				{
// 					_state = 5;
// 					_isSynced = true;
// 				}
// 			}
// 		}
		
// 		_interruptCalled = true;
// 	}
// }