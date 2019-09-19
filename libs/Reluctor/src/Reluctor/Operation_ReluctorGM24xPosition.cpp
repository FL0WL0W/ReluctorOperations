#include "Reluctor/Operation_ReluctorGM24xPosition.h"

#ifdef OPERATION_RELUCTORGM24XPOSITION_H
namespace Reluctor
{
	Operation_ReluctorGM24xPosition::Operation_ReluctorGM24xPosition(HardwareAbstraction::ITimerService *timerService)
	{
		_timerService = timerService;
	}

	float Operation_ReluctorGM24xPosition::Execute(VariableBus::Record *record, uint32_t tick)
	{
		uint8_t last = record->Last;
		if(!record->Frames[last].Valid)
			return -1;
		const uint8_t startingLast = last;
		while(tick - record->Frames[last].Tick > 2147483648)
		{
			last = VariableBus::Record::Subtract(last, 1, record->Length);
			if(!record->Frames[last].Valid)
				return -1;
			if(startingLast == last)
				return -1;
		}

		uint8_t lastMinus8 =  VariableBus::Record::Subtract(last, 8, record->Length);
		if(!record->Frames[lastMinus8].Valid)
			return -1;

		uint8_t lastMinus1 =  VariableBus::Record::Subtract(last, 1, record->Length);
		uint8_t lastMinus2 =  VariableBus::Record::Subtract(last, 2, record->Length);
		uint8_t lastMinus4 =  VariableBus::Record::Subtract(last, 4, record->Length);
		uint8_t lastMinus6 =  VariableBus::Record::Subtract(last, 6, record->Length);

		uint16_t baseDegree = 0;
		uint16_t pulseDegree = 0;

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
							return -1;
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
							return -1;
						}
					}
					else
					{
						if(IsLongPulse(record, lastMinus8))
						{
							//long-short-long-short-long
							//wtf?
							return -1;
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
							return -1;
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
			pulseDegree = baseDegree % 15;
			if(pulseDegree == 0)
				pulseDegree = 12;
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
							return -1;
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
							return -1;
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
							return -1;
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
							return -1;
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
			pulseDegree = baseDegree % 15;
			if(pulseDegree == 0)
				pulseDegree = 3;
		}

		return baseDegree + static_cast<float>((tick - record->Frames[last].Tick) * pulseDegree) / (record->Frames[last].Tick - record->Frames[lastMinus1].Tick);
	}

	bool Operation_ReluctorGM24xPosition::IsLongPulse(VariableBus::Record *record, uint8_t frame)
	{
		if(record->Frames[frame].State)
			frame = VariableBus::Record::Subtract(frame, 1, record->Length);

		uint8_t frameMinus1 = VariableBus::Record::Subtract(frame, 1, record->Length);
		uint8_t frameMinus2 = VariableBus::Record::Subtract(frame, 2, record->Length);

		uint32_t ticksPer15Degrees = record->Frames[frame].Tick - record->Frames[frameMinus2].Tick;
		uint32_t ticksPer7P5Degrees = ticksPer15Degrees / 2;

		return record->Frames[frame].Tick - record->Frames[frameMinus1].Tick > ticksPer7P5Degrees;
	}

	Operations::IOperationBase *Operation_ReluctorGM24xPosition::Create(Service::ServiceLocator * const &serviceLocator, const void *config, unsigned int &sizeOut)
	{
		return new Operation_ReluctorGM24xPosition(serviceLocator->LocateAndCast<HardwareAbstraction::ITimerService>(TIMER_SERVICE_ID));
	}

	ISERVICE_REGISTERFACTORY_CPP(Operation_ReluctorGM24xPosition, 1002)
}
#endif