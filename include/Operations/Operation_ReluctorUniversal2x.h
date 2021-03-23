#include "Operations/IOperation.h"
#include "Operations/Operation_DigitalPinRecord.h"
#include "ReluctorResult.h"
#include "Packed.h"
#include "Interpolation.h"

#ifndef OPERATION_RELUCTORUNIVERSAL2X_H
#define OPERATION_RELUCTORUNIVERSAL2X_H
namespace OperationArchitecture
{
	class Operation_ReluctorUniversal2x : public IOperation<ReluctorResult, Record*, uint32_t>
	{
	protected:
		EmbeddedIOServices::ITimerService *_timerService;
		float _risingPostion;
		float _fallingPosition;
	public:		
        Operation_ReluctorUniversal2x(EmbeddedIOServices::ITimerService *, float risingPostion, float fallingPosition);

		ReluctorResult Execute(Record *, uint32_t) override;

		static IOperationBase *Create(const EmbeddedIOServices::EmbeddedIOServiceCollection *embeddedIOServiceCollection, const void *config, unsigned int &sizeOut);
	};
}
#endif