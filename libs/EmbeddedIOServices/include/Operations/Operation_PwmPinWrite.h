#include "Operations/IOperation.h"
#include "Service/IService.h"
#include "Service/ServiceLocator.h"
#include "Service/HardwareAbstractionServiceBuilder.h"
#include "Packed.h"
#include "Interpolation.h"
#include "VariableType.h"

#ifndef OPERATION_PWMPINWRITE_H
#define OPERATION_PWMPINWRITE_H
namespace Operations
{
	class Operation_PwmPinWrite : public IOperation<void, float, float>
	{
	protected:
		HardwareAbstraction::IPwmService *_pwmService;
		uint16_t _pin;
		uint16_t _minFrequency;
	public:		
        Operation_PwmPinWrite(HardwareAbstraction::IPwmService *pwmService, const uint16_t pin, const uint16_t minFrequency);

		void Execute(float period, float pulseWidth) override;

		static IOperationBase *Create(Service::ServiceLocator * const &serviceLocator, const void *config, unsigned int &sizeOut);
		ISERVICE_REGISTERFACTORY_H
	};
}
#endif