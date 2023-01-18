#include "Operations/Operation_ReluctorUniversal1x.h"
#include "Config.h"

using namespace EmbeddedIOServices;
using namespace OperationArchitecture;
using namespace EmbeddedIOOperations;

#ifdef OPERATION_RELUCTORUNIVERSAL1X_H
namespace ReluctorOperations
{
	Operation_ReluctorUniversal1x::Operation_ReluctorUniversal1x(const Operation_ReluctorUniversal1xMode mode, const position_t risingPosition, const position_t fallingPosition) :
		_mode(mode),
		_risingPosition(risingPosition),
		_fallingPosition(fallingPosition)
	{ }

	ReluctorResult Operation_ReluctorUniversal1x::Execute(Record<bool> *record, tick_t tick)
	{
		ReluctorResult ret;
		ret.CalculatedTick = tick;
		ret.Synced = false;
		frameindex_t last = record->Last;
		if(!record->Frames[last].Valid)
			return ret;;
		const frameindex_t startingLast = last;
		while(ITimerService::TickLessThanTick(ret.CalculatedTick, record->Frames[last].Tick))
		{
			last = Record<bool>::Subtract(last, 1, record->Length);
			if(!record->Frames[last].Valid)
				return ret;
			if(startingLast == last)
				return ret;
		}

		frameindex_t lastMinus1 = Record<bool>::Subtract(last, 1, record->Length);
		frameindex_t lastMinus2 = Record<bool>::Subtract(last, 2, record->Length);
		frameindex_t lastMinus4 = Record<bool>::Subtract(last, 4, record->Length);

		if(!record->Frames[lastMinus2].Valid || !record->Frames[lastMinus4].Valid)
			return ret;

		//ensure stability
		const tick_t delta1 = tick - record->Frames[last].Tick;
		const tick_t delta2 = record->Frames[last].Tick - record->Frames[lastMinus2].Tick;
		if(delta1 > (delta2 * 2))
			return ret;
		const tick_t delta3 = record->Frames[lastMinus2].Tick - record->Frames[lastMinus4].Tick;
		if((delta2 * 2) < delta3 || (delta3 * 2) < delta2)
			return ret;

		if(_mode == BothEdges)
		{
			position_t deltaPosition = 0;
			position_t basePosition = 0;
			if(record->Frames[last].State)
			{
				deltaPosition = _risingPosition - _fallingPosition;
				basePosition = _risingPosition;
			}
			else
			{
				deltaPosition = _fallingPosition - _risingPosition;
				basePosition = _fallingPosition;
			}

			while(deltaPosition < 0)
				deltaPosition += 360;
			//account for negative positions and weird positions > 360
			while(deltaPosition > 360)
				deltaPosition -= 360;

			ret.PositionDot = deltaPosition / (record->Frames[last].Tick - record->Frames[lastMinus1].Tick);
			ret.Position = basePosition + ((ret.CalculatedTick - record->Frames[last].Tick) * ret.PositionDot);
		}
		else
		{
			if(_mode == RisingEdge)
			{
				if(!record->Frames[last].State)
				{
					last = lastMinus1;
					lastMinus1 = Record<bool>::Subtract(last, 1, record->Length);
				}
				ret.Position = _risingPosition;
			}
			if(_mode == FallingEdge)
			{
				if(record->Frames[last].State)
				{
					last = lastMinus1;
					lastMinus1 = Record<bool>::Subtract(last, 1, record->Length);
				}
				ret.Position = _fallingPosition;
			}
			ret.PositionDot = 360 / (record->Frames[last].Tick - record->Frames[lastMinus1].Tick);
			ret.Position += (ret.CalculatedTick - record->Frames[last].Tick) * ret.PositionDot;
		}

		while(ret.Position > 360)
			ret.Position -= 360;
		ret.PositionDot *= record->TicksPerSecond;
		ret.Synced = true;
		return ret;
	}

	AbstractOperation *Operation_ReluctorUniversal1x::Create(const void *config, size_t &sizeOut)
	{
		const Operation_ReluctorUniversal1xMode mode = Config::CastAndOffset<Operation_ReluctorUniversal1xMode>(config, sizeOut);
		
		if(mode == BothEdges)
		{
			const position_t rising = Config::CastAndOffset<position_t>(config, sizeOut);
			const position_t falling = Config::CastAndOffset<position_t>(config, sizeOut);
			return new Operation_ReluctorUniversal1x(mode, rising, falling);
		}
		
		if(mode == RisingEdge)
		{
			const position_t rising = Config::CastAndOffset<position_t>(config, sizeOut);
			return new Operation_ReluctorUniversal1x(mode, rising, 0);
		}
		
		if(mode == FallingEdge)
		{
			const position_t falling = Config::CastAndOffset<position_t>(config, sizeOut);
			return new Operation_ReluctorUniversal1x(mode, 0, falling);
		}

		return 0;
	}
}
#endif