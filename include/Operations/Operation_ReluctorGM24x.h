#include "Operations/IOperation.h"
#include "Operations/Operation_DigitalPinRecord.h"
#include <tuple>

#ifndef OPERATION_RELUCTORGM24X_H
#define OPERATION_RELUCTORGM24X_H
namespace OperationArchitecture
{
	//Return Variables
	//Synced, Position, PositionDot
	//Parameters
	//PinRecord, CurrentTick
	class Operation_ReluctorGM24x : public IOperation<std::tuple<bool, float, float>, Record*, uint32_t>
	{
	protected:
		static Operation_ReluctorGM24x *_instance;
	public:
		std::tuple<bool, float, float> Execute(Record *, uint32_t) override;
		bool IsLongPulse(Record *, uint16_t frame);

		static IOperationBase *Create(const void *config, unsigned int &sizeOut);
		static Operation_ReluctorGM24x *Construct();
	};
}
#endif