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

		uint16_t baseDegree = 0;

		if(IsLongPulse(record, last))
		{
			if(IsLongPulse(record, lastMinus2))
			{
				if(IsLongPulse(record, lastMinus4))
				{
					if(IsLongPulse(record, lastMinus6))
					{
						if(IsLongPulse(record, lastMinus8))
						{
							//long-long-long-long-long
							if(record->Frames[last].State)
								//102
								baseDegree = 102;
							else
								//90
								baseDegree = 90;
						}
						else
						{
							//long-long-long-long-short
							if(record->Frames[last].State)
								//78
								baseDegree = 78;
							else
								//75
								baseDegree = 75;
						}
					}
					else
					{
						if(IsLongPulse(record, lastMinus8))
						{
							//long-long-long-short-long
							if(record->Frames[last].State)
								//162
								baseDegree = 162;
							else
								//150
								baseDegree = 150;
						}
						else
						{
							//long-long-long-short-short
							if(record->Frames[last].State)
								//63
								baseDegree = 63;
							else
								//60
								baseDegree = 60;
						}
					}
				}
				else
				{
					if(IsLongPulse(record, lastMinus6))
					{
						if(IsLongPulse(record, lastMinus8))
						{
							//long-long-short-long-long
							if(record->Frames[last].State)
								//138
								baseDegree = 138;
							else
								//135
								baseDegree = 135;
						}
						else
						{
							//long-long-short-long-short
							//wtf?
							return ret;
						}
					}
					else
					{
						if(IsLongPulse(record, lastMinus8))
						{
							//long-long-short-short-long
							if(record->Frames[last].State)
								//222
								baseDegree = 222;
							else
								//210
								baseDegree = 210;
						}
						else
						{
							//long-long-short-short-short
							if(record->Frames[last].State)
								//48
								baseDegree = 48;
							else
								//45
								baseDegree = 45;
						}
					}
				}
			}
			else
			{
				if(IsLongPulse(record, lastMinus4))
				{
					if(IsLongPulse(record, lastMinus6))
					{
						if(IsLongPulse(record, lastMinus8))
						{
							//long-short-long-long-long
							if(record->Frames[last].State)
								//123
								baseDegree = 123;
							else
								//120
								baseDegree = 120;
						}
						else
						{
							//long-short-long-long-short
							//wtf?
							return ret;
						}
					}
					else
					{
						if(IsLongPulse(record, lastMinus8))
						{
							//long-short-long-short-long
							//wtf?
							return ret;
						}
						else
						{
							//long-short-long-short-short
							if(record->Frames[last].State)
								//312
								baseDegree = 312;
							else
								//300
								baseDegree = 300;
						}
					}
				}
				else
				{
					if(IsLongPulse(record, lastMinus6))
					{
						if(IsLongPulse(record, lastMinus8))
						{
							//long-short-short-long-long
							if(record->Frames[last].State)
								//198
								baseDegree = 198;
							else
								//195
								baseDegree = 195;
						}
						else
						{
							//long-short-short-long-short
							//wtf?
							return ret;
						}
					}
					else
					{
						if(IsLongPulse(record, lastMinus8))
						{
							//long-short-short-short-long
							if(record->Frames[last].State)
								//282
								baseDegree = 282;
							else
								//270
								baseDegree = 270;
						}
						else
						{
							//long-short-short-short-short
							if(record->Frames[last].State)
								//33
								baseDegree = 33;
							else
								//30
								baseDegree = 30;
						}
					}
				}
			}
		}
		else
		{
			if(IsLongPulse(record, lastMinus2))
			{
				if(IsLongPulse(record, lastMinus4))
				{
					if(IsLongPulse(record, lastMinus6))
					{
						if(IsLongPulse(record, lastMinus8))
						{
							//short-long-long-long-long
							if(record->Frames[last].State)
								//108
								baseDegree = 108;
							else
								//105
								baseDegree = 105;
						}
						else
						{
							//short-long-long-long-short
							if(record->Frames[last].State)
								//177
								baseDegree = 177;
							else
								//165
								baseDegree = 165;
						}
					}
					else
					{
						if(IsLongPulse(record, lastMinus8))
						{
							//short-long-long-short-long
							//wtf?
							return ret;
						}
						else
						{
							//short-long-long-short-short
							if(record->Frames[last].State)
								//237
								baseDegree = 237;
							else
								//225
								baseDegree = 225;
						}
					}
				}
				else
				{
					if(IsLongPulse(record, lastMinus6))
					{
						if(IsLongPulse(record, lastMinus8))
						{
							//short-long-short-long-long
							//wtf?
							return ret;
						}
						else
						{
							//short-long-short-long-short
							if(record->Frames[last].State)
								//327
								baseDegree = 327;
							else
								//315
								baseDegree = 315;
						}
					}
					else
					{
						if(IsLongPulse(record, lastMinus8))
						{
							//short-long-short-short-long
							//wtf?
							return ret;
						}
						else
						{
							//short-long-short-short-short
							if(record->Frames[last].State)
								//288
								baseDegree = 288;
							else
								//285
								baseDegree = 285;
						}
					}
				}
			}
			else
			{
				if(IsLongPulse(record, lastMinus4))
				{
					if(IsLongPulse(record, lastMinus6))
					{
						if(IsLongPulse(record, lastMinus8))
						{
							//short-short-long-long-long
							if(record->Frames[last].State)
								//183
								baseDegree = 183;
							else
								//180
								baseDegree = 180;
						}
						else
						{
							//short-short-long-long-short
							if(record->Frames[last].State)
								//252
								baseDegree = 252;
							else
								//240
								baseDegree = 240;
						}
					}
					else
					{
						if(IsLongPulse(record, lastMinus8))
						{
							//short-short-long-short-long
							if(record->Frames[last].State)
								//342
								baseDegree = 342;
							else
								//330
								baseDegree = 330;
						}
						else
						{
							//short-short-long-short-short
							//wtf?
							return ret;
						}
					}
				}
				else
				{
					if(IsLongPulse(record, lastMinus6))
					{
						if(IsLongPulse(record, lastMinus8))
						{
							//short-short-short-long-long
							if(record->Frames[last].State)
								//258
								baseDegree = 258;
							else
								//255
								baseDegree = 255;
						}
						else
						{
							//short-short-short-long-short
							if(record->Frames[last].State)
								//357
								baseDegree = 357;
							else
								//345
								baseDegree = 345;
						}
					}
					else
					{
						if(IsLongPulse(record, lastMinus8))
						{
							//short-short-short-short-long
							if(record->Frames[last].State)
								//12
								baseDegree = 12;
							else
								//0
								baseDegree = 0;
						}
						else
						{
							//short-short-short-short-short
							if(record->Frames[last].State)
								//18
								baseDegree = 18;
							else
								//15
								baseDegree = 15;
						}
					}
				}
			}
		}

		//average position dot over the last 5ms
		tick_t delta = record->Frames[lastDown].Tick - record->Frames[lastDownMinus4].Tick;
		uint16_t deltaDegrees = 30;
		frameindex_t lastFrame = record->TicksPerSecond / (50 * delta);
		//limit to 1 resolution
		if(lastFrame > 48)
			lastFrame = 48;
		//limit to 2 pulses (30 degrees)
		if(lastFrame < 4)
			lastFrame = 4;
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

	Operation_ReluctorGM24x Operation_ReluctorGM24x::Instance;
}
#endif