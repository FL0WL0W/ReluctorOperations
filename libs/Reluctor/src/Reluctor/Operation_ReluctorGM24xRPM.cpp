#include "Reluctor/Operation_ReluctorGM24xRPM.h"

#ifdef OPERATION_RELUCTORGM24XRPM_H
namespace Reluctor
{
	Operation_ReluctorGM24xRPM::Operation_ReluctorGM24xRPM(HardwareAbstraction::ITimerService *timerService)
	{
		_timerService = timerService;
	}

	float Operation_ReluctorGM24xRPM::Execute(VariableBus::Record *record)
	{
		uint8_t lastFallingEdge = record->Last;
		if(record->Frames[lastFallingEdge].State)
			lastFallingEdge = VariableBus::Record::Subtract(lastFallingEdge, 1, record->Length);
		if(!record->Frames[lastFallingEdge].Valid)
			return -1;
			
		const uint8_t prevFallingEdge = VariableBus::Record::Subtract(lastFallingEdge, 2, record->Length);
		if(!record->Frames[prevFallingEdge].Valid)
			return -1;

		const uint32_t period = record->Frames[lastFallingEdge].Tick - record->Frames[prevFallingEdge].Tick;
		if(period > 2147483648)
			return -1;

		return static_cast<float>(_timerService->GetTicksPerSecond() * 60) / period;
	}

	Operations::IOperationBase *Operation_ReluctorGM24xRPM::Create(Service::ServiceLocator * const &serviceLocator, const void *config, unsigned int &sizeOut)
	{
		return new Operation_ReluctorGM24xRPM(serviceLocator->LocateAndCast<HardwareAbstraction::ITimerService>(TIMER_SERVICE_ID));
	}

	ISERVICE_REGISTERFACTORY_CPP(Operation_ReluctorGM24xRPM, 1001)
}
#endif