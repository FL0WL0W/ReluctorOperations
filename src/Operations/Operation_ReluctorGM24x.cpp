#include "Operations/Operation_ReluctorGM24x.h"
#include <algorithm>
#include <vector>

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
		for(validCount = 10; validCount < (sizeof(lastMinus) / sizeof(lastMinus[0])) && record->Frames[lastMinus[validCount]].Valid; validCount++) ;
		if(validCount < 11)
		{
			return ret;
		}

		tick_t deltas[validCount];
		for(uint8_t i = 0; i < validCount-1; i++)
		{
			deltas[i] = record->Frames[lastMinus[i]].Tick - record->Frames[lastMinus[i + 1]].Tick;
		}

		std::vector<tick_t> delta15s = std::vector<tick_t>(5);
		for(uint8_t i = 0; i < 10; i+=2)
		{
			delta15s[i / 2] = deltas[i] + deltas[i + 1];
		}
		
		//median of last 5 delta15s.
		std::nth_element(delta15s.begin(), delta15s.begin() + delta15s.size() / 2, delta15s.end());
		const tick_t median15 = delta15s[delta15s.size() / 2];

		// Consider synchronization lost after two expected 15-degree
		// periods without reaching the most recent falling edge.
		const tick_t ticksSinceLastFalling =
			ret.CalculatedTick - record->Frames[lastMinus[0]].Tick;
		if(ticksSinceLastFalling > (median15 * 2))
		{
			return ret;
		}
		
		uint8_t median15Index = 0xFF;
		for(uint8_t i = 0; i < 10; i+=2)
		{
			if(median15 == deltas[i] + deltas[i + 1])
			{
				median15Index = i;
				break;
			}
		}

		if(median15Index == 0xFF)
		{
			return ret;
		}

		//validate pulses forward in time from median
		for(int8_t i = median15Index - 2; i >= 0; i-=2)
		{
			if(deltas[i] + deltas[i+1] > (median15 * 3) / 2)
			{
				return ret; // long pulse means timeout, so we don't have a valid sync
			}
			if(deltas[i] < median15 / 10 || deltas[i + 1] < median15 / 10)
			{
				//add the period to the previous delta
				if(i > 0)
				{
					deltas[i - 1] += deltas[i] + deltas[i + 1];
				}
				//remove these transitions
				validCount -= 2;
				for(uint8_t j = i; j < validCount; j++)
				{
					lastMinus[j] = lastMinus[j + 2];
					deltas[j] = deltas[j + 2];
				}
				median15Index -= 2;
			}
		}

		//validate pulses backward in time from median
		for(uint8_t i = median15Index + 2; i < validCount - 1;)
		{
			if(deltas[i] + deltas[i+1] > (median15 * 3) / 2)
			{
				// The long interval is not trustworthy, but the frames newer
				// than it are still contiguous.
				validCount = i;
				if(validCount < 11)
				{
					return ret;
				}
				break;
			}
			if(deltas[i] < median15 / 10 || deltas[i + 1] < median15 / 10)
			{
				//add the period to the next delta
				if(i + 2 < validCount - 1)
				{
					deltas[i] += deltas[i + 1] + deltas[i + 2];
				}
				//remove these transitions
				validCount -= 2;
				for(uint8_t j = i+1; j < validCount; j++)
				{
					lastMinus[j] = lastMinus[j + 2];
					deltas[j] = deltas[j + 2];
				}
			}
			else
			{
				i += 2;
			}
		}

		delta15s = std::vector<tick_t>((validCount - 1) / 2);
		for(uint8_t i = 0; i < validCount-2; i+=2)
		{
			delta15s[i / 2] = deltas[i] + deltas[i + 1];
		}

		uint8_t pulseSignature = 0;
		for(uint8_t i = 0; i < 10; i+=2)
		{
			if(deltas[i] > (median15 * 9) / 15)
				pulseSignature |= 0x1 << (i / 2);
			else if(deltas[i] > (median15 * 6) / 15)
				return ret;
		}

		// Bits 0 through 4 contain the five pulse lengths, ordered from
		// newest to oldest. Each valid signature maps directly to an angle.
		uint16_t baseDegree;
		switch(pulseSignature & 0b111111U)
		{
			case 0b10000U: baseDegree =   0U; break; // LSSSS
			case 0b00000U: baseDegree =  15U; break; // SSSSS
			case 0b00001U: baseDegree =  30U; break; // SSSSL
			case 0b00011U: baseDegree =  45U; break; // SSSLL
			case 0b00111U: baseDegree =  60U; break; // SSLLL
			case 0b01111U: baseDegree =  75U; break; // SLLLL
			case 0b11111U: baseDegree =  90U; break; // LLLLL
			case 0b11110U: baseDegree = 105U; break; // LLLLS
			case 0b11101U: baseDegree = 120U; break; // LLLSL
			case 0b11011U: baseDegree = 135U; break; // LLSLL
			case 0b10111U: baseDegree = 150U; break; // LSLLL
			case 0b01110U: baseDegree = 165U; break; // SLLLS
			case 0b11100U: baseDegree = 180U; break; // LLLSS
			case 0b11001U: baseDegree = 195U; break; // LLSSL
			case 0b10011U: baseDegree = 210U; break; // LSSLL
			case 0b00110U: baseDegree = 225U; break; // SSLLS
			case 0b01100U: baseDegree = 240U; break; // SLLSS
			case 0b11000U: baseDegree = 255U; break; // LLSSS
			case 0b10001U: baseDegree = 270U; break; // LSSSL
			case 0b00010U: baseDegree = 285U; break; // SSSLS
			case 0b00101U: baseDegree = 300U; break; // SSLSL
			case 0b01010U: baseDegree = 315U; break; // SLSLS
			case 0b10100U: baseDegree = 330U; break; // LSLSS
			case 0b01000U: baseDegree = 345U; break; // SLSSS
			default:
				return ret;
		}

		tick_t delta = 0;
		uint16_t deltaDegrees = 0;
		for(std::vector<tick_t>::iterator it = delta15s.begin(); it != delta15s.end(); ++it)
		{
			delta += *it;
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
