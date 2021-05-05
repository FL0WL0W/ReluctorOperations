#include "Operations/OperationFactory.h"

#ifndef RELUCTOROPERATIONFACTORYREGISTER_H
#define RELUCTOROPERATIONFACTORYREGISTER_H
namespace OperationArchitecture
{
	class ReluctorOperationFactoryRegister
	{
		public:
		static void Register(uint32_t idOffset, OperationFactory *factory);
	};
}
#endif