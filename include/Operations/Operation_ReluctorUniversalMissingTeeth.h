#include "Operations/IOperation.h"
#include "Record.h"
#include "ReluctorResult.h"
#include "Interpolation.h"
#include "Config.h"

#ifndef OPERATION_RELUCTORUNIVERSALMISSINGTEETH_H
#define OPERATION_RELUCTORUNIVERSALMISSINGTEETH_H
namespace ReluctorOperations
{
	struct Operation_ReluctorUniversalMissingTeethConfig
	{
		size_t Size() const
		{
			size_t s = sizeof(position_t);
			OperationArchitecture::Config::AlignAndAddSize<position_t>(s);
			OperationArchitecture::Config::AlignAndAddSize<uint8_t>(s);
			OperationArchitecture::Config::AlignAndAddSize<uint8_t>(s);
			return s;
		}

		const position_t FirstToothPosition;
		const position_t ToothWidth;
		const uint8_t NumberOfTeeth;
		const uint8_t NumberOfTeethMissing;
	};

	class Operation_ReluctorUniversalMissingTeeth : public OperationArchitecture::IOperation<ReluctorResult, EmbeddedIOOperations::Record<bool>*, EmbeddedIOServices::tick_t>
	{
	protected:
		const Operation_ReluctorUniversalMissingTeethConfig * const _config;
	public:		
        Operation_ReluctorUniversalMissingTeeth(const Operation_ReluctorUniversalMissingTeethConfig * const config);

		ReluctorResult Execute(EmbeddedIOOperations::Record<bool> *, EmbeddedIOServices::tick_t) override;

		static OperationArchitecture::IOperationBase *Create(const void *config, size_t &sizeOut);
	};
}
#endif