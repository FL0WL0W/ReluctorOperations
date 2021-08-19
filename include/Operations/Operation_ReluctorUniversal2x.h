#include "Operations/IOperation.h"
#include "Operations/Operation_DigitalPinRecord.h"
#include "ReluctorResult.h"
#include "Interpolation.h"

#ifndef OPERATION_RELUCTORUNIVERSAL2X_H
#define OPERATION_RELUCTORUNIVERSAL2X_H
namespace OperationArchitecture
{
	class Operation_ReluctorUniversal2x : public IOperation<ReluctorResult, Record*, EmbeddedIOServices::tick_t>
	{
	protected:
		float _risingPostion;
		float _fallingPosition;
	public:		
        Operation_ReluctorUniversal2x(float risingPostion, float fallingPosition);

		ReluctorResult Execute(Record *, EmbeddedIOServices::tick_t) override;

		static IOperationBase *Create(const void *config, size_t &sizeOut);
	};
}
#endif