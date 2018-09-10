#include "CrankCamDecoders/ICrankCamDecoder.h"

#ifndef MOCKCRANKCAMDECODERSERVICE_H
#define MOCKCRANKCAMDECODERSERVICE_H
namespace HardwareAbstraction
{
	class MockCrankCamDecoder : public ICrankCamDecoder
	{
	public:
		MOCK_METHOD0(GetCrankPosition, void());
		MOCK_METHOD0(GetCamPosition, void());
		MOCK_METHOD0(GetTickPerDegree, unsigned int());
		MOCK_METHOD0(GetRpm, unsigned short());
		MOCK_METHOD1(CrankEdgeTrigger, void(EdgeTrigger));
		MOCK_METHOD1(CamEdgeTrigger, void(EdgeTrigger));
		MOCK_METHOD0(IsSynced, bool());
		MOCK_METHOD0(HasCamPosition, bool());
	};
}
#endif