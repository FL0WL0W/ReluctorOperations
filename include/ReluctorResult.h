
#include "Packed.h"
#include "stdint.h"

#ifndef RELUCTORRESULT_H
#define RELUCTORRESULT_H
namespace OperationArchitecture
{
    PACK(struct ReluctorResult
    {
        float Position;
        float PositionDot;
		uint32_t CalculatedTick;
        bool Synced : 1;
        
		constexpr float GetRPM()
		{
			return PositionDot / 6;
		}
    });
}
#endif