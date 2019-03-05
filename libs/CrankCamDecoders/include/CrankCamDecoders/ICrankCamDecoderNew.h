#include "stdint.h"

#ifndef ICRANKCAMDECODERNEW_H
#define ICRANKCAMDECODERNEW_H
namespace CrankCamDecoders
{	
	class ICrankCamDecoderNew
	{
	public:
		virtual float GetPosition(void) = 0;
		virtual uint32_t GetTickPerDegree(void) = 0;
		virtual unsigned short GetRpm(void) = 0;
		virtual bool IsSynced() = 0;
	};
}
#endif