#include "Operations/Operation_ReluctorUniversal2x.h"
#include "Config.h"

using namespace EmbeddedIOServices;

#ifdef OPERATION_RELUCTORUNIVERSAL2X_H
namespace OperationArchitecture
{
	Operation_ReluctorUniversal2x::Operation_ReluctorUniversal2x(float risingPostion, float fallingPosition)
	{
		_risingPostion = risingPostion;
		_fallingPosition = fallingPosition;
	}

	ReluctorResult Operation_ReluctorUniversal2x::Execute(Record *record, tick_t tick)
	{
		ReluctorResult ret;
		ret.CalculatedTick = tick;
		ret.Synced = false;
		uint16_t last = record->Last;
		if(!record->Frames[last].Valid)
			return ret;;
		const uint16_t startingLast = last;
		while(ITimerService::TickLessThanTick(ret.CalculatedTick, record->Frames[last].Tick))
		{
			last = Record::Subtract(last, 1, record->Length);
			if(!record->Frames[last].Valid)
				return ret;
			if(startingLast == last)
				return ret;
		}

		uint16_t lastMinus1 =  Record::Subtract(last, 1, record->Length);
		uint16_t lastMinus2 =  Record::Subtract(last, 2, record->Length);
		uint16_t lastMinus4 =  Record::Subtract(last, 4, record->Length);

		if(!record->Frames[lastMinus2].Valid || !record->Frames[lastMinus4].Valid)
			return ret;

		//ensure stability
		const float delta1 = static_cast<float>(tick - record->Frames[last].Tick);
		const float delta2 = static_cast<float>(record->Frames[last].Tick - record->Frames[lastMinus2].Tick);
		if(delta1 * 0.5 > delta2)
			return ret;
		const float delta3 = static_cast<float>(record->Frames[lastMinus2].Tick - record->Frames[lastMinus4].Tick);
		const float similarity = delta2 / delta3;
		if(similarity < 0.5 || similarity > 2)
			return ret;

		float deltaPosition = 0;
		float basePosition = 0;
		if(record->Frames[last].State)
		{
			deltaPosition = _risingPostion - _fallingPosition;
			basePosition = _risingPostion;
		}
		else
		{
			deltaPosition = _fallingPosition - _risingPostion;
			basePosition = _fallingPosition;
		}

		while(deltaPosition < 0)
			deltaPosition += 360;
		//account for negative positions and weird positions > 360
		while(deltaPosition > 360)
			deltaPosition -= 360;

		ret.PositionDot = deltaPosition / (record->Frames[last].Tick - record->Frames[lastMinus1].Tick);
		ret.Position = basePosition + (ret.CalculatedTick - record->Frames[last].Tick) * ret.PositionDot;
		while(ret.Position > 360)
			ret.Position -= 360;
		ret.PositionDot *= record->TicksPerSecond;
		ret.Synced = true;
		return ret;
	}

	IOperationBase *Operation_ReluctorUniversal2x::Create(const void *config, size_t &sizeOut)
	{
		return new Operation_ReluctorUniversal2x(Config::CastAndOffset<float>(config, sizeOut), Config::CastAndOffset<float>(config, sizeOut));
	}
}
#endif