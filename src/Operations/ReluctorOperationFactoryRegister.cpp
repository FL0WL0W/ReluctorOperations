#include "Operations/ReluctorOperationFactoryRegister.h"
#include "Operations/Operation_ReluctorGM24x.h"
#include "Operations/Operation_ReluctorUniversal1x.h"
#include "Operations/Operation_ReluctorUniversalMissingTeeth.h"

#ifdef RELUCTOROPERATIONFACTORYREGISTER_H

namespace OperationArchitecture
{
    void ReluctorOperationFactoryRegister::Register(uint32_t idOffset, OperationFactory *factory)
    {
        factory->Register(idOffset + 1, &Operation_ReluctorGM24x::Instance);
        factory->Register(idOffset + 2, Operation_ReluctorUniversal1x::Create);
        factory->Register(idOffset + 3, Operation_ReluctorUniversalMissingTeeth::Create);
    }
}

#endif