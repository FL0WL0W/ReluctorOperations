#include "Operations/Operation_ReluctorGM24x.h"
#include <algorithm>
#include <vector>
#include <cstdio>

using namespace EmbeddedIOServices;
using namespace OperationArchitecture;
using namespace EmbeddedIOOperations;

#ifdef OPERATION_RELUCTORGM24X_H

namespace ReluctorOperations
{
	ReluctorResult Operation_ReluctorGM24x::Execute(Record<bool> *record, tick_t tick)
	{
		ReluctorResult ret;
		ret.CalculatedTick = tick;
		ret.Synced = false;
		frameindex_t lastMinus[48];
		lastMinus[0] = record->Last;
		if(!record->Frames[lastMinus[0]].Valid)
		{
			return ret;
		}
		const frameindex_t startingLast = lastMinus[0];
		while(ITimerService::TickLessThanTick(ret.CalculatedTick, record->Frames[lastMinus[0]].Tick))
		{
			lastMinus[0] = Record<bool>::Subtract(lastMinus[0], 1, record->Length);
			if(!record->Frames[lastMinus[0]].Valid)
			{
				return ret;
			}
			if(startingLast == lastMinus[0])
			{
				return ret;
			}
		}
		//always reference on falling edges
		if(record->Frames[lastMinus[0]].State)
		{
			lastMinus[0] = Record<bool>::Subtract(lastMinus[0], 1, record->Length);
		}

		for(uint8_t i = 1; i < (sizeof(lastMinus) / sizeof(lastMinus[0])); i++)
		{
			lastMinus[i] = Record<bool>::Subtract(lastMinus[0], i, record->Length);
		}
		uint8_t validCount = 0;
		for(validCount = 1; validCount < (sizeof(lastMinus) / sizeof(lastMinus[0])) && record->Frames[lastMinus[validCount]].Valid && lastMinus[validCount] != startingLast; validCount++) ;
		const uint8_t requiredValidCount = 13;
		if(validCount < requiredValidCount)
		{
			return ret;
		}

		tick_t deltas[validCount];
		for(uint8_t i = 0; i < validCount-1; i++)
		{
			deltas[i] = record->Frames[lastMinus[i]].Tick - record->Frames[lastMinus[i + 1]].Tick;
		}

		std::vector<tick_t> deltasSorted = std::vector<tick_t>(12);
		for(uint8_t i = 0; i < 12; i++)
		{
			deltasSorted[i] = deltas[i];
		}
		std::sort(deltasSorted.begin(), deltasSorted.end());
		
		const tick_t median15 = deltasSorted[3] + deltasSorted[9];

		// Consider synchronization lost after two expected 15-degree
		// periods without reaching the most recent falling edge.
		const tick_t ticksSinceLastFalling =
			ret.CalculatedTick - record->Frames[lastMinus[0]].Tick;
		if(ticksSinceLastFalling > (median15 * 2))
			return ret;

		//look for timeout or short pulse
		for(uint8_t i = 0; i < validCount - 2; i+= 2)
		{
			if(deltas[i] + deltas[i+1] > (median15 * 3) / 2 || deltas[i] < median15 / 10 || deltas[i+1] < median15 / 10)
			{
				// The long interval is not trustworthy, but the frames newer
				// than it are still contiguous.
				validCount = i;
				if(validCount < requiredValidCount)
					return ret;
				break;
			}
		}

		uint8_t pulseSignature = 0;
		for(uint8_t i = 0; i < 12; i+=2)
		{
			if(deltas[i] > (median15 * 9) / 15)
				pulseSignature |= 0x1 << (i / 2);
			else if(deltas[i] > (median15 * 6) / 15)
				return ret;
		}

		// Bits 0 through 5 contain the five pulse lengths, ordered from
		// newest to oldest. Each valid signature maps directly to an angle.
		uint16_t baseDegree;
		switch(pulseSignature & 0b111111U)
		{
			case 0b010000U: baseDegree =   0U; break; // SLSSSS
			case 0b100000U: baseDegree =  15U; break; // LSSSSS
			case 0b000001U: baseDegree =  30U; break; // SSSSSL
			case 0b000011U: baseDegree =  45U; break; // SSSSLL
			case 0b000111U: baseDegree =  60U; break; // SSSLLL
			case 0b001111U: baseDegree =  75U; break; // SSLLLL
			case 0b011111U: baseDegree =  90U; break; // SLLLLL
			case 0b111110U: baseDegree = 105U; break; // LLLLLS
			case 0b111101U: baseDegree = 120U; break; // LLLLSL
			case 0b111011U: baseDegree = 135U; break; // LLLSLL
			case 0b110111U: baseDegree = 150U; break; // LLSLLL
			case 0b101110U: baseDegree = 165U; break; // LSLLLS
			case 0b011100U: baseDegree = 180U; break; // SLLLSS
			case 0b111001U: baseDegree = 195U; break; // LLLSSL
			case 0b110011U: baseDegree = 210U; break; // LLSSLL
			case 0b100110U: baseDegree = 225U; break; // LSSLLS
			case 0b001100U: baseDegree = 240U; break; // SSLLSS
			case 0b011000U: baseDegree = 255U; break; // SLLSSS
			case 0b110001U: baseDegree = 270U; break; // LLSSSL
			case 0b100010U: baseDegree = 285U; break; // LSSSLS
			case 0b000101U: baseDegree = 300U; break; // SSSLSL
			case 0b001010U: baseDegree = 315U; break; // SSLSLS
			case 0b010100U: baseDegree = 330U; break; // SLSLSS
			case 0b101000U: baseDegree = 345U; break; // LSLSSS
			default: return ret; // Invalid signature
		}

		tick_t delta = 0;
		uint16_t deltaDegrees = 0;
		for(uint8_t i = 0; i < validCount-2; i+=2)
		{
			delta += deltas[i] + deltas[i + 1];
			deltaDegrees += 15;
		}

		ret.PositionDot = static_cast<float>(deltaDegrees) / delta;
		ret.Position = baseDegree + ((ret.CalculatedTick - record->Frames[lastMinus[0]].Tick) * ret.PositionDot);
		while(ret.Position > 360)
			ret.Position -= 360;
		ret.PositionDot *= record->TicksPerSecond;
		ret.Synced = true;
		return ret;
	}
}
#endif
