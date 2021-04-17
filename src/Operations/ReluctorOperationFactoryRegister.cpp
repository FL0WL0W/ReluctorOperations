#include "Operations/ReluctorOperationFactoryRegister.h"
#include "CreateWithParameters.h"
#include "Operations/Operation_ReluctorGM24x.h"
#include "Operations/Operation_ReluctorUniversal2x.h"

using namespace EmbeddedIOServices;

#ifdef RELUCTOROPERATIONFACTORYREGISTER_H

namespace OperationArchitecture
{
    void ReluctorOperationFactoryRegister::Register(uint32_t idOffset, OperationFactory *factory, const EmbeddedIOServiceCollection *embeddedIOServiceCollection)
    {
        factory->Register(idOffset + 1, new CreateWithParameters<const EmbeddedIOServiceCollection *>(Operation_ReluctorGM24x::Create, embeddedIOServiceCollection));
        factory->Register(idOffset + 2, new CreateWithParameters<const EmbeddedIOServiceCollection *>(Operation_ReluctorUniversal2x::Create, embeddedIOServiceCollection));
    }
}

#endif