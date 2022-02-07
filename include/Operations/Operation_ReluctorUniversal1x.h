#include "Operations/IOperation.h"
#include "Operations/Operation_DigitalPinRecord.h"
#include "ReluctorResult.h"
#include "Interpolation.h"

#ifndef OPERATION_RELUCTORUNIVERSAL1X_H
#define OPERATION_RELUCTORUNIVERSAL1X_H
namespace ReluctorOperations
{
	class Operation_ReluctorUniversal1x : public OperationArchitecture::IOperation<ReluctorResult, EmbeddedIOOperations::Record*, EmbeddedIOServices::tick_t>
	{
	protected:
		const position_t _risingPostion;
		const position_t _fallingPosition;
	public:		
        Operation_ReluctorUniversal1x(const position_t risingPostion, const position_t fallingPosition);

		ReluctorResult Execute(EmbeddedIOOperations::Record *, EmbeddedIOServices::tick_t) override;

		static OperationArchitecture::IOperationBase *Create(const void *config, size_t &sizeOut);
	};
}
#endif