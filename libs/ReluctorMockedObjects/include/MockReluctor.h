#include "Reluctor/IReluctor.h"

#ifndef MOCKRELUCTORSERVICE_H
#define MOCKRELUCTORSERVICE_H
namespace Reluctor
{
	class MockReluctor : public IReluctor
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