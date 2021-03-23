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

	std::tuple<bool, float, float> Operation_ReluctorUniversal2x::Execute(Record *record, uint32_t tick)
	{
		uint8_t last = record->Last;
		if(!record->Frames[last].Valid)
			return std::tuple<bool, float, float>{false, 0, 0};
		const uint8_t startingLast = last;
		while(tick - record->Frames[last].Tick > 0x80000000)
		{
			last = Record::Subtract(last, 1, record->Length);
			if(!record->Frames[last].Valid)
				return std::tuple<bool, float, float>{false, 0, 0};
			if(startingLast == last)
				return std::tuple<bool, float, float>{false, 0, 0};
		}

		uint16_t lastMinus1 =  Record::Subtract(last, 1, record->Length);
		uint16_t lastMinus2 =  Record::Subtract(last, 2, record->Length);
		uint16_t lastMinus4 =  Record::Subtract(last, 4, record->Length);

		if(!record->Frames[lastMinus2].Valid || !record->Frames[lastMinus4].Valid)
			return std::tuple<bool, float, float>{false, 0, 0};

		//ensure stability
		const float delta1 = static_cast<float>(tick - record->Frames[last].Tick);
		const float delta2 = static_cast<float>(record->Frames[last].Tick - record->Frames[lastMinus2].Tick);
		if(delta1 * 0.5 > delta2)
			return std::tuple<bool, float, float>{false, 0, 0};
		const float delta3 = static_cast<float>(record->Frames[lastMinus2].Tick - record->Frames[lastMinus4].Tick);
		const float similarity = delta2 / delta3;
		if(similarity < 0.5 || similarity > 2)
			return std::tuple<bool, float, float>{false, 0, 0};

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

		float positionDot = deltaPosition / (record->Frames[last].Tick - record->Frames[lastMinus1].Tick);
		float position = basePosition + (tick - record->Frames[last].Tick) * positionDot;
		while(position > 360)
			position -= 360;
		positionDot *= record->TicksPerSecond;
		return std::tuple<bool, float, float>{true, position, positionDot};
	}

	IOperationBase *Operation_ReluctorUniversal2x::Create(const void *config, unsigned int &sizeOut)
	{
		return new Operation_ReluctorUniversal2x(Config::CastAndOffset<float>(config, sizeOut), Config::CastAndOffset<float>(config, sizeOut));
	}
}
#endif