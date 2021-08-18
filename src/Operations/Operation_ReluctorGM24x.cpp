#include "Operations/Operation_ReluctorGM24x.h"

#ifdef OPERATION_RELUCTORGM24X_H
namespace OperationArchitecture
{
	ReluctorResult Operation_ReluctorGM24x::Execute(Record *record, uint32_t tick)
	{
		ReluctorResult ret;
		ret.CalculatedTick = tick;
		ret.Synced = false;
		uint16_t last = record->Last;
		if(!record->Frames[last].Valid)
			return ret;
		const uint16_t startingLast = last;
		while(ret.CalculatedTick - record->Frames[last].Tick > 0x80000000)
		{
			last = Record::Subtract(last, 1, record->Length);
			if(!record->Frames[last].Valid)
				return ret;
			if(startingLast == last)
				return ret;
		}

		const uint16_t lastMinus8 =  Record::Subtract(last, 8, record->Length);
		if(!record->Frames[lastMinus8].Valid)
			return ret;

		const uint16_t lastMinus1 =  Record::Subtract(last, 1, record->Length);
		const uint16_t lastMinus2 =  Record::Subtract(last, 2, record->Length);
		const uint16_t lastMinus4 =  Record::Subtract(last, 4, record->Length);
		const uint16_t lastMinus6 =  Record::Subtract(last, 6, record->Length);
		
		uint16_t lastDown = last;
		if(record->Frames[last].State)
			lastDown = lastMinus1;
		const uint16_t lastDownMinus2 =  Record::Subtract(lastDown, 2, record->Length);
		const uint16_t lastDownMinus4 =  Record::Subtract(lastDown, 4, record->Length);
		const float delta1 = static_cast<float>(tick - record->Frames[lastDown].Tick);
		const float delta2 = static_cast<float>(record->Frames[lastDown].Tick - record->Frames[lastDownMinus2].Tick);
		if(delta1 * 0.5 > delta2)
			return ret;
		const float delta3 = static_cast<float>(record->Frames[lastDownMinus2].Tick - record->Frames[lastDownMinus4].Tick);
		const float similarity = delta2 / delta3;
		if(similarity < 0.5 || similarity > 2)
			return ret;

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

		uint32_t delta = record->Frames[lastDown].Tick - record->Frames[lastDownMinus4].Tick;
		uint16_t deltaDegrees = 30;
		for(uint8_t lastFrame = 48; delta > 4; lastFrame -= 2)
		{
			const uint16_t lastDownMinus =  Record::Subtract(lastDown, lastFrame, record->Length);
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

	bool Operation_ReluctorGM24x::IsLongPulse(Record *record, uint16_t frame)
	{
		if(record->Frames[frame].State)
			frame = Record::Subtract(frame, 1, record->Length);

		const uint16_t frameMinus1 = Record::Subtract(frame, 1, record->Length);
		const uint16_t frameMinus2 = Record::Subtract(frame, 2, record->Length);

		const uint32_t deltaPulse = record->Frames[frame].Tick - record->Frames[frameMinus1].Tick;
		const uint32_t delta15degrees = record->Frames[frame].Tick - record->Frames[frameMinus2].Tick;

		return deltaPulse > (delta15degrees / 2);
	}

	Operation_ReluctorGM24x Operation_ReluctorGM24x::Instance;
}
#endif