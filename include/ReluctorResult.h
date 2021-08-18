#include "stdint.h"
#include "ITimerService.h"

#ifndef RELUCTORRESULT_H
#define RELUCTORRESULT_H
namespace OperationArchitecture
{
    struct ReluctorResult
    {
        float Position;
        float PositionDot;
		EmbeddedIOServices::tick_t CalculatedTick;
        bool Synced : 1;
        
		constexpr float GetRPM()
		{
			return PositionDot / 6;
		}
    };
}
#endif