#include "Operations/IOperation.h"
#include "VariableBus/VariableService_DigitalPinRecord.h"
#include "Service/IService.h"
#include "Service/ServiceLocator.h"
#include "Service/HardwareAbstractionServiceBuilder.h"
#include "Packed.h"
#include "Interpolation.h"
#include "VariableType.h"
#include "Reluctor/ReluctorResult.h"

#ifndef OPERATION_RELUCTORGM24X_H
#define OPERATION_RELUCTORGM24X_H
namespace Reluctor
{
	class Operation_ReluctorGM24x : public Operations::IOperation<ReluctorResult, VariableBus::Record*, uint32_t>
	{
	protected:
		HardwareAbstraction::ITimerService *_timerService;
	public:		
        Operation_ReluctorGM24x(HardwareAbstraction::ITimerService *);

		ReluctorResult Execute(VariableBus::Record *, uint32_t) override;
		bool IsLongPulse(VariableBus::Record *, uint8_t frame);

		static Operations::IOperationBase *Create(Service::ServiceLocator * const &serviceLocator, const void *config, unsigned int &sizeOut);
		ISERVICE_REGISTERFACTORY_H
	};
}
#endif