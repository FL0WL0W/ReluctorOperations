#include "Decoder/IDecoder.h"

#ifndef MOCKDECODERSERVICE_H
#define MOCKDECODERSERVICE_H
namespace Decoder
{
	class MockDecoder : public IDecoder
	{
	public:
		MOCK_METHOD0(GetPosition, float());
		MOCK_METHOD0(GetTickPerDegree, uint32_t());
		MOCK_METHOD0(GetRpm, uint16_t());
		MOCK_METHOD0(GetRpm, GetResolution());
		MOCK_METHOD0(IsSynced, bool());
	};
}
#endif