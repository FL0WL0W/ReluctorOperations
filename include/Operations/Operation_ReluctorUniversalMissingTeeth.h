#include "Operations/IOperation.h"
#include "Operations/Operation_DigitalPinRecord.h"
#include "ReluctorResult.h"
#include "Interpolation.h"
#include "Config.h"

#ifndef OPERATION_RELUCTORUNIVERSALMISSINGTEETH_H
#define OPERATION_RELUCTORUNIVERSALMISSINGTEETH_H
namespace OperationArchitecture
{
	struct Operation_ReluctorUniversalMissingTeethConfig
	{
		size_t Size() const
		{
			size_t s = sizeof(position_t);
			Config::AlignAndAddSize<position_t>(s);
			Config::AlignAndAddSize<uint8_t>(s);
			Config::AlignAndAddSize<uint8_t>(s);
			return s;
		}

		const position_t FirstToothPosition;
		const position_t ToothWidth;
		const uint8_t NumberOfTeeth;
		const uint8_t NumberOfTeethMissing;
	};

	class Operation_ReluctorUniversalMissingTeeth : public IOperation<ReluctorResult, Record*, EmbeddedIOServices::tick_t>
	{
	protected:
		const Operation_ReluctorUniversalMissingTeethConfig * const _config;
	public:		
        Operation_ReluctorUniversalMissingTeeth(const Operation_ReluctorUniversalMissingTeethConfig * const config);

		ReluctorResult Execute(Record *, EmbeddedIOServices::tick_t) override;

		static IOperationBase *Create(const void *config, size_t &sizeOut);
	};
}
#endif