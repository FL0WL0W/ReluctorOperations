#include "Operations/Operation_ReluctorGM24x.h"

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
		frameindex_t last = record->Last;
		if(!record->Frames[last].Valid)
		{
			return ret;
		}
		const frameindex_t startingLast = last;
		while(ITimerService::TickLessThanTick(ret.CalculatedTick, record->Frames[last].Tick))
		{
			last = Record<bool>::Subtract(last, 1, record->Length);
			if(!record->Frames[last].Valid)
			{
				return ret;
			}
			if(startingLast == last)
			{
				return ret;
			}
		}

		const frameindex_t lastMinus8 =  Record<bool>::Subtract(last, 8, record->Length);
		if(!record->Frames[lastMinus8].Valid)
		{
			return ret;
		}

		const frameindex_t lastMinus1 =  Record<bool>::Subtract(last, 1, record->Length);
		const frameindex_t lastMinus2 =  Record<bool>::Subtract(last, 2, record->Length);
		const frameindex_t lastMinus4 =  Record<bool>::Subtract(last, 4, record->Length);
		const frameindex_t lastMinus6 =  Record<bool>::Subtract(last, 6, record->Length);
		
		frameindex_t lastDown = last;
		if(record->Frames[last].State)
			lastDown = lastMinus1;
		const frameindex_t lastDownMinus2 =  Record<bool>::Subtract(lastDown, 2, record->Length);
		const frameindex_t lastDownMinus4 =  Record<bool>::Subtract(lastDown, 4, record->Length);
		const tick_t delta1 = tick - record->Frames[lastDown].Tick;
		const tick_t delta2 = record->Frames[lastDown].Tick - record->Frames[lastDownMinus2].Tick;
		if(delta1 > (delta2 * 2))
		{
			return ret;
		}
		const tick_t delta3 = record->Frames[lastDownMinus2].Tick - record->Frames[lastDownMinus4].Tick;
		if((delta2 * 2) < delta3 || (delta3 * 2) < delta2)
		{
			return ret;
		}

		const bool risingEdge = record->Frames[last].State;
		uint8_t pulseSignature = risingEdge ? 0x01U : 0U;
		pulseSignature |= IsLongPulse(record, last)       ? 0x02U : 0U;
		pulseSignature |= IsLongPulse(record, lastMinus2) ? 0x04U : 0U;
		pulseSignature |= IsLongPulse(record, lastMinus4) ? 0x08U : 0U;
		pulseSignature |= IsLongPulse(record, lastMinus6) ? 0x10U : 0U;
		pulseSignature |= IsLongPulse(record, lastMinus8) ? 0x20U : 0U;

		// Bit 0 is the current edge state (1 = rising, 0 = falling).
		// Bits 1 through 5 contain the five pulse lengths, ordered from
		// newest to oldest. Each valid signature maps directly to an angle.
		uint16_t baseDegree;
		switch(pulseSignature)
		{
			case 0b100000U: baseDegree =   0U; break; // LSSSS, falling
			case 0b100001U: baseDegree =  12U; break; // LSSSS, rising
			case 0b000000U: baseDegree =  15U; break; // SSSSS, falling
			case 0b000001U: baseDegree =  18U; break; // SSSSS, rising
			case 0b000010U: baseDegree =  30U; break; // SSSSL, falling
			case 0b000011U: baseDegree =  33U; break; // SSSSL, rising
			case 0b000110U: baseDegree =  45U; break; // SSSLL, falling
			case 0b000111U: baseDegree =  48U; break; // SSSLL, rising
			case 0b001110U: baseDegree =  60U; break; // SSLLL, falling
			case 0b001111U: baseDegree =  63U; break; // SSLLL, rising
			case 0b011110U: baseDegree =  75U; break; // SLLLL, falling
			case 0b011111U: baseDegree =  78U; break; // SLLLL, rising
			case 0b111110U: baseDegree =  90U; break; // LLLLL, falling
			case 0b111111U: baseDegree = 102U; break; // LLLLL, rising
			case 0b111100U: baseDegree = 105U; break; // LLLLS, falling
			case 0b111101U: baseDegree = 108U; break; // LLLLS, rising
			case 0b111010U: baseDegree = 120U; break; // LLLSL, falling
			case 0b111011U: baseDegree = 123U; break; // LLLSL, rising
			case 0b110110U: baseDegree = 135U; break; // LLSLL, falling
			case 0b110111U: baseDegree = 138U; break; // LLSLL, rising
			case 0b101110U: baseDegree = 150U; break; // LSLLL, falling
			case 0b101111U: baseDegree = 162U; break; // LSLLL, rising
			case 0b011100U: baseDegree = 165U; break; // SLLLS, falling
			case 0b011101U: baseDegree = 177U; break; // SLLLS, rising
			case 0b111000U: baseDegree = 180U; break; // LLLSS, falling
			case 0b111001U: baseDegree = 183U; break; // LLLSS, rising
			case 0b110010U: baseDegree = 195U; break; // LLSSL, falling
			case 0b110011U: baseDegree = 198U; break; // LLSSL, rising
			case 0b100110U: baseDegree = 210U; break; // LSSLL, falling
			case 0b100111U: baseDegree = 222U; break; // LSSLL, rising
			case 0b001100U: baseDegree = 225U; break; // SSLLS, falling
			case 0b001101U: baseDegree = 237U; break; // SSLLS, rising
			case 0b011000U: baseDegree = 240U; break; // SLLSS, falling
			case 0b011001U: baseDegree = 252U; break; // SLLSS, rising
			case 0b110000U: baseDegree = 255U; break; // LLSSS, falling
			case 0b110001U: baseDegree = 258U; break; // LLSSS, rising
			case 0b100010U: baseDegree = 270U; break; // LSSSL, falling
			case 0b100011U: baseDegree = 282U; break; // LSSSL, rising
			case 0b000100U: baseDegree = 285U; break; // SSSLS, falling
			case 0b000101U: baseDegree = 288U; break; // SSSLS, rising
			case 0b001010U: baseDegree = 300U; break; // SSLSL, falling
			case 0b001011U: baseDegree = 312U; break; // SSLSL, rising
			case 0b010100U: baseDegree = 315U; break; // SLSLS, falling
			case 0b010101U: baseDegree = 327U; break; // SLSLS, rising
			case 0b101000U: baseDegree = 330U; break; // LSLSS, falling
			case 0b101001U: baseDegree = 342U; break; // LSLSS, rising
			case 0b010000U: baseDegree = 345U; break; // SLSSS, falling
			case 0b010001U: baseDegree = 357U; break; // SLSSS, rising
			default:
				return ret;
		}

		tick_t delta = record->Frames[lastDown].Tick - record->Frames[lastDownMinus4].Tick;
		uint16_t deltaDegrees = 30;

		// //average position dot over the last 5ms
		// frameindex_t lastFrame = record->TicksPerSecond / (50 * delta);
		// //limit to 1 resolution
		// if(lastFrame > 48)
		// 	lastFrame = 48;
		// //limit to 2 pulses (30 degrees)
		// if(lastFrame < 4)
		// 	lastFrame = 4;

		//average position dot over the last reolution
		frameindex_t lastFrame = 48;
		for(lastFrame = lastFrame - lastFrame % 2; lastFrame > 2; lastFrame -= 2)
		{
			const frameindex_t lastDownMinus =  Record<bool>::Subtract(lastDown, lastFrame, record->Length);
			if(record->Frames[lastDownMinus].Valid)
			{
				delta = record->Frames[lastDown].Tick - record->Frames[lastDownMinus].Tick;
				deltaDegrees = (lastFrame / 2) * 15;
				break;
			}
		}

		ret.PositionDot = static_cast<float>(deltaDegrees) / delta;
		ret.Position = baseDegree + ((ret.CalculatedTick - record->Frames[last].Tick) * ret.PositionDot);
		while(ret.Position > 360)
			ret.Position -= 360;
		ret.PositionDot *= record->TicksPerSecond;
		ret.Synced = true;
		return ret;
	}

	bool Operation_ReluctorGM24x::IsLongPulse(Record<bool> *record, frameindex_t frame)
	{
		if(record->Frames[frame].State)
			frame = Record<bool>::Subtract(frame, 1, record->Length);

		const frameindex_t frameMinus1 = Record<bool>::Subtract(frame, 1, record->Length);
		const frameindex_t frameMinus2 = Record<bool>::Subtract(frame, 2, record->Length);

		const tick_t deltaPulse = record->Frames[frame].Tick - record->Frames[frameMinus1].Tick;
		const tick_t delta15degrees = record->Frames[frame].Tick - record->Frames[frameMinus2].Tick;

		return deltaPulse > (delta15degrees / 2);
	}
}
#endif
