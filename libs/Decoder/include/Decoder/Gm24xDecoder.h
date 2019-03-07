#include "Decoder/IDecoder.h"
#include "HardwareAbstraction/ICallBack.h"
#include "HardwareAbstraction/HardwareAbstractionCollection.h"
#include "stdint.h"
#include "Packed.h"

#ifndef GM24XDECODER_H
#define GM24XDECODER_H
namespace Decoder
{
	class Gm24xDecoder : public IDecoder
	{
	protected:
		const HardwareAbstraction::HardwareAbstractionCollection *_hardwareAbstractionCollection;
		uint16_t _pin;

		unsigned char _state;
		unsigned char _subState;
		bool _isSynced;
		uint32_t _lastTick;
		uint32_t _period;
		const uint32_t time() const;
	public:
		Gm24xDecoder(const HardwareAbstraction::HardwareAbstractionCollection *hardwareAbstractionCollection, const uint16_t pin);
		float GetPosition() override;
		uint32_t GetTickPerDegree() override;
		uint16_t GetRpm() override;
		uint16_t GetResolution() override;
		static void InterruptCallBack(void *decoder);
		void Interrupt();
		bool IsSynced() override;
	};
}
#endif