#include "Operations/OperationFactory.h"
#include "EmbeddedIOServiceCollection.h"

#ifndef RELUCTOROPERATIONFACTORYREGISTER_H
#define RELUCTOROPERATIONFACTORYREGISTER_H
namespace OperationArchitecture
{
	class ReluctorOperationFactoryRegister
	{
		public:
		static void Register(uint32_t idOffset, OperationFactory *factory, const EmbeddedIOServices::EmbeddedIOServiceCollection *embeddedIOServiceCollection);
	};
}
#endif