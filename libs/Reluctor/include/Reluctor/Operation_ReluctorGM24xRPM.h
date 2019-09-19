#include "Operations/IOperation.h"
#include "VariableBus/VariableService_DigitalPinRecord.h"
#include "Service/IService.h"
#include "Service/ServiceLocator.h"
#include "Service/HardwareAbstractionServiceBuilder.h"
#include "Packed.h"
#include "Interpolation.h"
#include "VariableType.h"

#ifndef OPERATION_RELUCTORGM24XRPM_H
#define OPERATION_RELUCTORGM24XRPM_H
namespace Reluctor
{
	class Operation_ReluctorGM24xRPM : public Operations::IOperation<float, VariableBus::Record*>
	{
	protected:
		HardwareAbstraction::ITimerService *_timerService;
	public:		
        Operation_ReluctorGM24xRPM(HardwareAbstraction::ITimerService *);

		float Execute(VariableBus::Record *) override;

		static Operations::IOperationBase *Create(Service::ServiceLocator * const &serviceLocator, const void *config, unsigned int &sizeOut);
		ISERVICE_REGISTERFACTORY_H
	};
}
#endif