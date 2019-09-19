#include "Operations/Operation_FrequencyPinRead.h"

#ifdef OPERATION_FREQUENCYPINREAD_H
namespace Operations
{
	Operation_FrequencyPinRead::Operation_FrequencyPinRead( HardwareAbstraction::IPwmService *pwmService, const uint16_t pin, const uint16_t minFrequency)
	{
		_pwmService = pwmService;
		_pin = pin;
		_minFrequency = minFrequency;

		_pwmService->InitPin(_pin, In, _minFrequency);
	}

	float Operation_FrequencyPinRead::Execute()
	{
		return 1 / _pwmService->ReadPin(_pin).Period;
	}

	IOperationBase *Operation_FrequencyPinRead::Create(Service::ServiceLocator * const &serviceLocator, const void *config, unsigned int &sizeOut)
	{
		const uint16_t pin = IService::CastAndOffset<uint16_t>(config, sizeOut);
		const uint16_t minFrequency = IService::CastAndOffset<uint16_t>(config, sizeOut);
		return new Operation_FrequencyPinRead(serviceLocator->LocateAndCast<HardwareAbstraction::IPwmService>(PWM_SERVICE_ID), pin, minFrequency);
	}

	ISERVICE_REGISTERFACTORY_CPP(Operation_FrequencyPinRead, 6)
}
#endif