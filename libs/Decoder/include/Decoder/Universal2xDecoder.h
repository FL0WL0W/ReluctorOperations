#include "Decoder/IDecoder.h"
#include "HardwareAbstraction/ICallBack.h"
#include "HardwareAbstraction/HardwareAbstractionCollection.h"
#include "stdint.h"
#include "math.h"
#include "Packed.h"

#ifndef UNIVERSAL2XDECODER_H
#define UNIVERSAL2XDECODER_H
namespace Decoder
{
	PACK(
	struct Universal2xDecoderConfig {
		constexpr const unsigned int Size() const
		{
			return sizeof(Universal2xDecoderConfig);
		}

		uint16_t Pin;
		float RisingPosition;
		float FallingPosition;
	});

	class Universal2xDecoder : public IDecoder
	{
	protected:
		const HardwareAbstraction::HardwareAbstractionCollection *_hardwareAbstractionCollection;
		const Universal2xDecoderConfig *_config;

		bool _state;
		bool _isSynced;
		uint32_t _lastTick;
		uint32_t _period;
		const uint32_t time() const;
	public:
		Universal2xDecoder(const HardwareAbstraction::HardwareAbstractionCollection *hardwareAbstractionCollection, const Universal2xDecoderConfig *config);
		float GetPosition() override;
		uint32_t GetTickPerDegree() override;
		uint16_t GetRpm() override;
		uint16_t GetResolution() override;
		bool IsSynced() override;
		static void InterruptCallBack(void *decoder);
		void Interrupt();
	};
}
#endif