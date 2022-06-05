#include "Operations/ReluctorOperationFactoryRegister.h"
#include "Operations/Operation_ReluctorGM24x.h"
#include "Operations/Operation_ReluctorUniversal1x.h"
#include "Operations/Operation_ReluctorUniversalMissingTeeth.h"

using namespace OperationArchitecture;

#ifdef RELUCTOROPERATIONFACTORYREGISTER_H
namespace ReluctorOperations
{
    Operation_ReluctorGM24x *Operation_ReluctorGM24xInstance = 0;
    void ReluctorOperationFactoryRegister::Register(uint32_t idOffset, OperationFactory *factory)
    {
        if(Operation_ReluctorGM24xInstance == 0)
            Operation_ReluctorGM24xInstance = new Operation_ReluctorGM24x();
        factory->Register(idOffset + 1, Operation_ReluctorGM24xInstance);
        factory->Register(idOffset + 2, Operation_ReluctorUniversal1x::Create);
        factory->Register(idOffset + 3, Operation_ReluctorUniversalMissingTeeth::Create);
    }
}
#endif