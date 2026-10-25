#include "Operations/OperationFactory.h"
#include "Operations/Operation_ReluctorGM24x.h"
#include "Operations/Operation_ReluctorUniversal1x.h"
#include "Operations/Operation_ReluctorUniversalMissingTeeth.h"

#ifndef RELUCTOROPERATIONFACTORYREGISTER_H
#define RELUCTOROPERATIONFACTORYREGISTER_H
namespace ReluctorOperations
{
    extern Operation_ReluctorGM24x Operation_ReluctorGM24xInstance;

	template<uint32_t idOffset>
	constexpr auto RegisterReluctorOperationFactory = []() {
    	return std::array<OperationArchitecture::OperationFactoryEntry, 3>{{
			{ idOffset + 1, [](const void *config, size_t &size){ return static_cast<OperationArchitecture::AbstractOperation *>(&Operation_ReluctorGM24xInstance); } },
			{ idOffset + 2, Operation_ReluctorUniversal1x::Create },
			{ idOffset + 3, Operation_ReluctorUniversalMissingTeeth::Create }
    	}};
	};
}
#endif