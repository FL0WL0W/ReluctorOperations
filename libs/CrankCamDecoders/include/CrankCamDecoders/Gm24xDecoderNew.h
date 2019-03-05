#include "CrankCamDecoders/ICrankCamDecoderNew.h"
#include "HardwareAbstraction/ICallBack.h"
#include "HardwareAbstraction/HardwareAbstractionCollection.h"
#include "stdint.h"
#include "Packed.h"

#ifndef GM24XDECODER_H
#define GM24XDECODER_H
namespace CrankCamDecoders
{
	class Gm24xDecoderNew : public ICrankCamDecoderNew
	{
	protected:
		const HardwareAbstraction::HardwareAbstractionCollection *_hardwareAbstractionCollection;
		uint16_t _pin;

		unsigned char _state;
		unsigned char _crankState;
		bool _isSynced;
		uint32_t _lastCrankTick;
		uint32_t _crankPeriod;
		unsigned int crankTime();
	public:
		Gm24xDecoderNew(const HardwareAbstraction::HardwareAbstractionCollection *hardwareAbstractionCollection, const uint16_t pin);
		float GetPosition() override;
		uint32_t GetTickPerDegree() override;
		unsigned short GetRpm() override;
		static void InterruptCallBack(void *decoder);
		void Interrupt();
		bool IsSynced() override;
	};
}
#endif