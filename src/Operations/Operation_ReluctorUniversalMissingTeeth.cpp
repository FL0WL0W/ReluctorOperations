#include "Operations/Operation_ReluctorUniversalMissingTeeth.h"
#include "Config.h"

using namespace EmbeddedIOServices;
using namespace OperationArchitecture;
using namespace EmbeddedIOOperations;

#ifdef OPERATION_RELUCTORUNIVERSALMISSINGTEETH_H
namespace ReluctorOperations
{
	Operation_ReluctorUniversalMissingTeeth::Operation_ReluctorUniversalMissingTeeth(const Operation_ReluctorUniversalMissingTeethConfig * const config) :
		_config(config)
	{ }

	ReluctorResult Operation_ReluctorUniversalMissingTeeth::Execute(Record<bool> *record, tick_t tick)
	{
		ReluctorResult ret;
		ret.CalculatedTick = tick;
		ret.Synced = false;
		frameindex_t last = record->Last;
		if(!record->Frames[last].Valid)
			return ret;

		//line up last to be before tick
		const frameindex_t startingLast = last;
		while(ITimerService::TickLessThanTick(ret.CalculatedTick, record->Frames[last].Tick))
		{
			last = Record<bool>::Subtract(last, 1, record->Length);
			if(!record->Frames[last].Valid)
				return ret;
			if(startingLast == last)
				return ret;
		}

		// frameindex_t lastMinus2 =  Record<bool>::Subtract(last, 2, record->Length);
		// frameindex_t lastMinus4 =  Record<bool>::Subtract(last, 4, record->Length);

		// if(!record->Frames[lastMinus2].Valid || !record->Frames[lastMinus4].Valid)
		// 	return ret;

		//ensure stability
		// const tick_t delta1 = tick - record->Frames[last].Tick;
		// const tick_t delta2 = record->Frames[last].Tick - record->Frames[lastMinus2].Tick;
		// if(delta1 > (delta2 * 2))
		// 	return ret;
		// const tick_t delta3 = record->Frames[lastMinus2].Tick - record->Frames[lastMinus4].Tick;
		// if((delta2 * 2) < delta3 || (delta3 * 2) < delta2)
		// 	return ret;

		//line up with falling edge
		frameindex_t firstToothEdgeFramesAgo = 0;
		if(record->Frames[last].State)
		{
			if(_config->ToothWidth > 0)
			{
				firstToothEdgeFramesAgo++;
			}
			else
			{
				last = Record<bool>::Subtract(last, 1, record->Length);
			}
		}

		if(_config->NumberOfTeethMissing > 0) 
		{
			//find missing tooth
			while(true)
			{
				const frameindex_t firstToothEdge = Record<bool>::Subtract(last, firstToothEdgeFramesAgo, record->Length);
				const frameindex_t firstToothEdgeMinus2 = Record<bool>::Subtract(last, firstToothEdgeFramesAgo + 2, record->Length);
				const frameindex_t firstToothEdgeMinus4 = Record<bool>::Subtract(last, firstToothEdgeFramesAgo + 4, record->Length);

				const tick_t firstToothPulse = record->Frames[firstToothEdge].Tick - record->Frames[firstToothEdgeMinus2].Tick;
				const tick_t previousPulse = record->Frames[firstToothEdgeMinus2].Tick - record->Frames[firstToothEdgeMinus4].Tick;
				
				//if these pulses are not valid
				if(!record->Frames[firstToothEdgeMinus4].Valid || firstToothEdgeFramesAgo >= (record->Length + 4 + Record<bool>::Subtract(record->Last, startingLast, record->Length)))
					return ret;

				//if first pulse is greater than half the amount of missing teeth, then it is the first pulse
				if(firstToothPulse * 2 > previousPulse * (_config->NumberOfTeethMissing + 2))
					break;

				firstToothEdgeFramesAgo+=2;
			}

			//throw out the teeth around the missing tooth as they are influenced by the missing tooth
			const bool numberOfTeethGreaterThan10 = (_config->NumberOfTeeth - _config->NumberOfTeethMissing) > 6;
			if(firstToothEdgeFramesAgo < (numberOfTeethGreaterThan10? 4 : 2))
			{
				last = Record<bool>::Subtract(last, firstToothEdgeFramesAgo + (numberOfTeethGreaterThan10? 4 : 2), record->Length);
				firstToothEdgeFramesAgo = (_config->NumberOfTeeth - _config->NumberOfTeethMissing) * 2 - (numberOfTeethGreaterThan10? 4 : 2);
			}
			else
			{
				const frameindex_t endingTooth = (_config->NumberOfTeeth - _config->NumberOfTeethMissing) * 2 - 3;
				if(firstToothEdgeFramesAgo > endingTooth)
				{
					frameindex_t teethOver = (firstToothEdgeFramesAgo - endingTooth) + (numberOfTeethGreaterThan10? 4 : 2);
					if(!(_config->ToothWidth > 0) && teethOver % 2 == 1)
						teethOver--;
					last = Record<bool>::Subtract(last, teethOver, record->Length);
					firstToothEdgeFramesAgo -= teethOver;
				}
			}
		} 
		else
		{
			frameindex_t framesSinceLastFirstTooth;
			
			//increment last first tooth until close to last
			while((framesSinceLastFirstTooth = Record<bool>::Subtract(last, _lastFirstTooth, record->Length)) > (_config->NumberOfTeeth * 2 + 1)) 
				_lastFirstTooth = Record<bool>::Add(_lastFirstTooth, _config->NumberOfTeeth * 2, record->Length);

			//increment last first tooth until a valid falling edge
			while((framesSinceLastFirstTooth = Record<bool>::Subtract(last, _lastFirstTooth, record->Length)) > 0) 
			{
				if(record->Frames[_lastFirstTooth].Valid && !record->Frames[_lastFirstTooth].State)
					break;

				_lastFirstTooth = Record<bool>::Add(_lastFirstTooth, 1, record->Length);
			}

			//return if last first tooth is invalid
			if(!record->Frames[_lastFirstTooth].Valid || record->Frames[_lastFirstTooth].State)
				return ret;

			firstToothEdgeFramesAgo += framesSinceLastFirstTooth;
		}

		//require 1 full revolution for Postion Dot calculation
		const frameindex_t lastMinus1Revolution = Record<bool>::Subtract(last, (_config->NumberOfTeeth - _config->NumberOfTeethMissing) * 2, record->Length);
		if(!record->Frames[lastMinus1Revolution].Valid || ITimerService::TickLessThanTick(record->Frames[last].Tick, record->Frames[lastMinus1Revolution].Tick))
			return ret;

		const position_t degreesPerPeriod = static_cast<position_t>(360) / _config->NumberOfTeeth;
		//								number of periods			degreesPerPeriod					add tooth width if on odd tooth						add first tooth position
		const position_t basePosition = ((firstToothEdgeFramesAgo / 2) * degreesPerPeriod) + ((firstToothEdgeFramesAgo % 2 == 1)? _config->ToothWidth : 0) + _config->FirstToothPosition;

		//average position dot over the last revolution
		ret.PositionDot = static_cast<position_t>(360) / (record->Frames[last].Tick - record->Frames[lastMinus1Revolution].Tick);
		ret.Position = basePosition + ((ret.CalculatedTick - record->Frames[last].Tick) * ret.PositionDot);
		while(ret.Position > 360)
			ret.Position -= 360;
		ret.PositionDot *= record->TicksPerSecond;
		ret.Synced = true;
		return ret;
	}

	AbstractOperation *Operation_ReluctorUniversalMissingTeeth::Create(const void *config, size_t &sizeOut)
	{
		return new Operation_ReluctorUniversalMissingTeeth(Config::CastConfigAndOffset<Operation_ReluctorUniversalMissingTeethConfig>(config, sizeOut));
	}
}
#endif