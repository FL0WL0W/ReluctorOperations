#include "Operations/IOperation.h"
#include "Operations/Operation_DigitalPinRecord.h"
#include "ReluctorResult.h"
#include "Interpolation.h"

#ifndef OPERATION_RELUCTORGM24X_H
#define OPERATION_RELUCTORGM24X_H
namespace OperationArchitecture
{
	class Operation_ReluctorGM24x : public IOperation<ReluctorResult, Record*, uint32_t>
	{
	public:
		ReluctorResult Execute(Record *, uint32_t) override;
		bool IsLongPulse(Record *, uint16_t frame);

		static Operation_ReluctorGM24x Instance;
	};
}
#endif