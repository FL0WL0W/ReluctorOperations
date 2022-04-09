#include "Operations/IOperation.h"
#include "Record.h"
#include "ReluctorResult.h"
#include "Interpolation.h"

#ifndef OPERATION_RELUCTORGM24X_H
#define OPERATION_RELUCTORGM24X_H
namespace ReluctorOperations
{
	class Operation_ReluctorGM24x : public OperationArchitecture::IOperation<ReluctorResult, EmbeddedIOOperations::Record<bool>*, EmbeddedIOServices::tick_t>
	{
	public:
		ReluctorResult Execute(EmbeddedIOOperations::Record<bool> *, EmbeddedIOServices::tick_t) override;
		bool IsLongPulse(EmbeddedIOOperations::Record<bool> *, uint16_t frame);

		static Operation_ReluctorGM24x Instance;
	};
}
#endif