#include "Operations/Operation.h"
#include "Record.h"
#include "ReluctorResult.h"
#include "Interpolation.h"

#ifndef OPERATION_RELUCTORUNIVERSAL1X_H
#define OPERATION_RELUCTORUNIVERSAL1X_H
namespace ReluctorOperations
{
	enum Operation_ReluctorUniversal1xMode {
		BothEdges = 0,
		RisingEdge = 1,
		FallingEdge = 2
	};

	class Operation_ReluctorUniversal1x : public OperationArchitecture::Operation<ReluctorResult, EmbeddedIOOperations::Record<bool>*, EmbeddedIOServices::tick_t>
	{
	protected:
		const Operation_ReluctorUniversal1xMode _mode;
		const position_t _risingPosition;
		const position_t _fallingPosition;
	public:		
        Operation_ReluctorUniversal1x(const Operation_ReluctorUniversal1xMode mode, const position_t risingPosition, const position_t fallingPosition);

		ReluctorResult Execute(EmbeddedIOOperations::Record<bool> *, EmbeddedIOServices::tick_t) override;

		static OperationArchitecture::AbstractOperation *Create(const void *config, size_t &sizeOut);
	};
}
#endif