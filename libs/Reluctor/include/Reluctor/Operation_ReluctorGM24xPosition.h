#include "Operations/IOperation.h"
#include "VariableBus/VariableService_DigitalPinRecord.h"
#include "Service/IService.h"
#include "Service/ServiceLocator.h"
#include "Service/HardwareAbstractionServiceBuilder.h"
#include "Packed.h"
#include "Interpolation.h"
#include "VariableType.h"

#ifndef OPERATION_RELUCTORGM24XPOSITION_H
#define OPERATION_RELUCTORGM24XPOSITION_H
namespace Reluctor
{
	class Operation_ReluctorGM24xPosition : public Operations::IOperation<float, VariableBus::Record*, uint32_t>
	{
	protected:
		HardwareAbstraction::ITimerService *_timerService;
	public:		
        Operation_ReluctorGM24xPosition(HardwareAbstraction::ITimerService *);

		float Execute(VariableBus::Record *, uint32_t) override;
		bool IsLongPulse(VariableBus::Record *, uint8_t frame);

		static Operations::IOperationBase *Create(Service::ServiceLocator * const &serviceLocator, const void *config, unsigned int &sizeOut);
		ISERVICE_REGISTERFACTORY_H
	};
}
#endif