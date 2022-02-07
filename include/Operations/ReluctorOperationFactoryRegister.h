#include "Operations/OperationFactory.h"

#ifndef RELUCTOROPERATIONFACTORYREGISTER_H
#define RELUCTOROPERATIONFACTORYREGISTER_H
namespace ReluctorOperations
{
	class ReluctorOperationFactoryRegister
	{
		public:
		static void Register(uint32_t idOffset, OperationArchitecture::OperationFactory *factory);
	};
}
#endif