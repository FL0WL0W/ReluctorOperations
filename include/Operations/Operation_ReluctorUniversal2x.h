#include "Operations/IOperation.h"
#include "Operations/Operation_DigitalPinRecord.h"
#include <tuple>

#ifndef OPERATION_RELUCTORUNIVERSAL2X_H
#define OPERATION_RELUCTORUNIVERSAL2X_H
namespace OperationArchitecture
{
	//Return Variables
	//Synced, Position, PositionDot
	//Parameters
	//PinRecord, CurrentTick
	class Operation_ReluctorUniversal2x : public IOperation<std::tuple<bool, float, float>, Record*, uint32_t>
	{
	protected:
		float _risingPostion;
		float _fallingPosition;
	public:		
        Operation_ReluctorUniversal2x(float risingPostion, float fallingPosition);

		std::tuple<bool, float, float> Execute(Record *, uint32_t) override;

		static IOperationBase *Create(const void *config, unsigned int &sizeOut);
	};
}
#endif