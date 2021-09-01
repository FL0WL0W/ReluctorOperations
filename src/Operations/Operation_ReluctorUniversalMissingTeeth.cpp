#include "Operations/Operation_ReluctorUniversalMissingTeeth.h"
#include "Config.h"

using namespace EmbeddedIOServices;

#ifdef OPERATION_RELUCTORUNIVERSALMISSINGTEETH_H
namespace OperationArchitecture
{
	Operation_ReluctorUniversalMissingTeeth::Operation_ReluctorUniversalMissingTeeth(const Operation_ReluctorUniversalMissingTeethConfig * const config) :
		_config(config)
	{ }

	ReluctorResult Operation_ReluctorUniversalMissingTeeth::Execute(Record *record, tick_t tick)
	{
		ReluctorResult ret;
		ret.CalculatedTick = tick;
		ret.Synced = false;
		frameindex_t last = record->Last;
		if(!record->Frames[last].Valid)
			return ret;

		//line up last and firstTooth to be before tick
		const frameindex_t startingLast = last;
		while(ITimerService::TickLessThanTick(ret.CalculatedTick, record->Frames[last].Tick))
		{
			last = Record::Subtract(last, 1, record->Length);
			if(!record->Frames[last].Valid)
				return ret;
			if(startingLast == last)
				return ret;
		}

		//require 1 full revolution for Postion Dot calculation
		const frameindex_t lastMinus1Revolution = Record::Subtract(last, (_config->NumberOfTeeth - _config->NumberOfTeethMissing) * 2, record->Length);
		if(!record->Frames[lastMinus1Revolution].Valid)
			return ret;

		//line up with period capture
		frameindex_t firstToothEdgeFramesAgo = 0;
		if(record->Frames[last].State != _config->FirstToothPositionOnRising)
			firstToothEdgeFramesAgo++;

		//find missing tooth
		while(true)
		{
			const frameindex_t firstToothEdge = Record::Subtract(last, firstToothEdgeFramesAgo, record->Length);
			const frameindex_t firstToothEdgeMinus2 = Record::Subtract(last, firstToothEdgeFramesAgo + 2, record->Length);
			const frameindex_t firstToothEdgeMinus4 = Record::Subtract(last, firstToothEdgeFramesAgo + 4, record->Length);

			const tick_t firstToothPulse = record->Frames[firstToothEdge].Tick - record->Frames[firstToothEdgeMinus2].Tick;
			const tick_t previousPulse = record->Frames[firstToothEdgeMinus2].Tick - record->Frames[firstToothEdgeMinus4].Tick;
			
			//if these pulses are not valid
			if(!record->Frames[firstToothEdgeMinus4].Valid || firstToothEdgeFramesAgo >= (record->Length + 4 + (record->Last - startingLast)))
				return ret;

			//if first pulse is greater than half the amount of missing teeth, then it is the first pulse
			if(firstToothPulse * 2 > previousPulse * (_config->NumberOfTeethMissing + 2))
				break;

			firstToothEdgeFramesAgo+=2;
		}

		const position_t degreesPerPeriod = static_cast<position_t>(360) / _config->NumberOfTeeth;
		//								number of periods			degreesPerPeriod					add tooth width if on odd tooth						add first tooth position
		const position_t basePosition = ((firstToothEdgeFramesAgo / 2) * degreesPerPeriod) + (firstToothEdgeFramesAgo % 2 == 1? _config->ToothWidth : 0) + _config->FirstToothPosition;

		//average position dot over the last revolution
		ret.PositionDot = static_cast<position_t>(360) / (record->Frames[last].Tick - record->Frames[lastMinus1Revolution].Tick);
		ret.Position = basePosition + ((ret.CalculatedTick - record->Frames[last].Tick) * ret.PositionDot);
		while(ret.Position > 360)
			ret.Position -= 360;
		ret.PositionDot *= record->TicksPerSecond;
		ret.Synced = true;
		return ret;
	}

	IOperationBase *Operation_ReluctorUniversalMissingTeeth::Create(const void *config, size_t &sizeOut)
	{
		return new Operation_ReluctorUniversalMissingTeeth(Config::CastConfigAndOffset<Operation_ReluctorUniversalMissingTeethConfig>(config, sizeOut));
	}
}
#endif