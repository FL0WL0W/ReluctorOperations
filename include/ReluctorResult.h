#include "stdint.h"
#include "ITimerService.h"

#ifndef RELUCTORRESULT_H
#define RELUCTORRESULT_H
namespace ReluctorOperations
{
    typedef float position_t;
    typedef float positiondot_t;
    typedef float rpm_t;

    struct ReluctorResult
    {
        position_t Position;
        positiondot_t PositionDot;
		EmbeddedIOServices::tick_t CalculatedTick;
        bool Synced : 1;

        ReluctorResult() : Synced(false) {}
        
		constexpr rpm_t GetRPM()
		{
			return PositionDot / 6;
		}
    };
}
#endif