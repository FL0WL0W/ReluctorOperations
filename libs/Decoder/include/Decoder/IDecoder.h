#include "stdint.h"

#ifndef DECODER_H
#define DECODER_H
namespace Decoder
{	
	class IDecoder
	{
	public:
		virtual float GetPosition() = 0;
		virtual uint32_t GetTickPerDegree() = 0;
		virtual uint16_t GetRpm() = 0;
		virtual uint16_t GetResolution() = 0;
		virtual bool IsSynced() = 0;
	};
}
#endif