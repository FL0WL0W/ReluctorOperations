#include <functional>
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "MockTimerService.h"
#include "MockDigitalService.h"
#include "CrankCamDecoders/Gm24xDecoderNew.h"
using ::testing::AtLeast;
using ::testing::Return;

using namespace CrankCamDecoders;

namespace UnitTests
{	
	TEST(GM24XDECODERNEW, SyncedReturnsTrueAfterCrankVerification)
	{
		HardwareAbstraction::HardwareAbstractionCollection collection;
		HardwareAbstraction::MockTimerService timerService;
		HardwareAbstraction::MockDigitalService digitalService;
		collection.TimerService = &timerService;
		collection.DigitalService = &digitalService;
		Gm24xDecoderNew *decoder = new Gm24xDecoderNew(&collection, 1);

		ASSERT_FALSE(decoder->IsSynced());

		unsigned int tick = 0;

		for (int i = 0; i < 47; i++)
		{
			tick += 2;
			EXPECT_CALL(timerService, GetTick())
				.Times(1)
				.WillRepeatedly(Return(tick));
				
			EXPECT_CALL(digitalService, ReadPin(1))
				.Times(1)
				.WillOnce(Return(false));

			Gm24xDecoderNew::InterruptCallBack(decoder);
			ASSERT_FALSE(decoder->IsSynced());

			tick += 6;
			EXPECT_CALL(timerService, GetTick())
				.Times(1)
				.WillRepeatedly(Return(tick));

			EXPECT_CALL(digitalService, ReadPin(1))
				.Times(1)
				.WillOnce(Return(true));
				
			Gm24xDecoderNew::InterruptCallBack(decoder);
			ASSERT_FALSE(decoder->IsSynced());
		}

		tick += 4;
		EXPECT_CALL(timerService, GetTick())
			.Times(9)
			.WillOnce(Return(tick))
			.WillOnce(Return(tick + 6))
			.WillOnce(Return(tick + 8))
			.WillOnce(Return(tick + 14))
			.WillOnce(Return(tick + 16))
			.WillOnce(Return(tick + 22))
			.WillOnce(Return(tick + 24))
			.WillOnce(Return(tick + 30))
			.WillOnce(Return(tick + 32));

		EXPECT_CALL(digitalService, ReadPin(1))
			.Times(1)
			.WillOnce(Return(false));

		Gm24xDecoderNew::InterruptCallBack(decoder);
		ASSERT_FALSE(decoder->IsSynced());

		EXPECT_CALL(digitalService, ReadPin(1))
			.Times(1)
			.WillOnce(Return(true));

		Gm24xDecoderNew::InterruptCallBack(decoder);
		ASSERT_FALSE(decoder->IsSynced());

		EXPECT_CALL(digitalService, ReadPin(1))
			.Times(1)
			.WillOnce(Return(false));

		Gm24xDecoderNew::InterruptCallBack(decoder);
		ASSERT_FALSE(decoder->IsSynced());

		EXPECT_CALL(digitalService, ReadPin(1))
			.Times(1)
			.WillOnce(Return(true));

		Gm24xDecoderNew::InterruptCallBack(decoder);
		ASSERT_FALSE(decoder->IsSynced());

		EXPECT_CALL(digitalService, ReadPin(1))
			.Times(1)
			.WillOnce(Return(false));

		Gm24xDecoderNew::InterruptCallBack(decoder);
		ASSERT_FALSE(decoder->IsSynced());

		EXPECT_CALL(digitalService, ReadPin(1))
			.Times(1)
			.WillOnce(Return(true));

		Gm24xDecoderNew::InterruptCallBack(decoder);
		ASSERT_FALSE(decoder->IsSynced());

		EXPECT_CALL(digitalService, ReadPin(1))
			.Times(1)
			.WillOnce(Return(false));

		Gm24xDecoderNew::InterruptCallBack(decoder);
		ASSERT_FALSE(decoder->IsSynced());

		EXPECT_CALL(digitalService, ReadPin(1))
			.Times(1)
			.WillOnce(Return(true));

		Gm24xDecoderNew::InterruptCallBack(decoder);
		ASSERT_FALSE(decoder->IsSynced());

		EXPECT_CALL(digitalService, ReadPin(1))
			.Times(1)
			.WillOnce(Return(false));

		Gm24xDecoderNew::InterruptCallBack(decoder);
		ASSERT_FALSE(decoder->IsSynced());

		tick += 34;
		EXPECT_CALL(timerService, GetTick())
			.Times(10)
			.WillOnce(Return(tick))
			.WillOnce(Return(tick + 6))
			.WillOnce(Return(tick + 8))
			.WillOnce(Return(tick + 14))
			.WillOnce(Return(tick + 16))
			.WillOnce(Return(tick + 22))
			.WillOnce(Return(tick + 24))
			.WillOnce(Return(tick + 30))
			.WillOnce(Return(tick + 32))
			.WillOnce(Return(tick + 32));

		EXPECT_CALL(digitalService, ReadPin(1))
			.Times(1)
			.WillOnce(Return(true));

		Gm24xDecoderNew::InterruptCallBack(decoder);
		ASSERT_FALSE(decoder->IsSynced());

		EXPECT_CALL(digitalService, ReadPin(1))
			.Times(1)
			.WillOnce(Return(false));

		Gm24xDecoderNew::InterruptCallBack(decoder);
		ASSERT_FALSE(decoder->IsSynced());

		EXPECT_CALL(digitalService, ReadPin(1))
			.Times(1)
			.WillOnce(Return(true));

		Gm24xDecoderNew::InterruptCallBack(decoder);
		ASSERT_FALSE(decoder->IsSynced());

		EXPECT_CALL(digitalService, ReadPin(1))
			.Times(1)
			.WillOnce(Return(false));

		Gm24xDecoderNew::InterruptCallBack(decoder);
		ASSERT_FALSE(decoder->IsSynced());

		EXPECT_CALL(digitalService, ReadPin(1))
			.Times(1)
			.WillOnce(Return(true));

		Gm24xDecoderNew::InterruptCallBack(decoder);
		ASSERT_FALSE(decoder->IsSynced());

		EXPECT_CALL(digitalService, ReadPin(1))
			.Times(1)
			.WillOnce(Return(false));

		Gm24xDecoderNew::InterruptCallBack(decoder);
		ASSERT_FALSE(decoder->IsSynced());

		EXPECT_CALL(digitalService, ReadPin(1))
			.Times(1)
			.WillOnce(Return(true));

		Gm24xDecoderNew::InterruptCallBack(decoder);
		ASSERT_FALSE(decoder->IsSynced());

		EXPECT_CALL(digitalService, ReadPin(1))
			.Times(1)
			.WillOnce(Return(false));

		Gm24xDecoderNew::InterruptCallBack(decoder);
		ASSERT_FALSE(decoder->IsSynced());

		EXPECT_CALL(digitalService, ReadPin(1))
			.Times(1)
			.WillOnce(Return(true));

		Gm24xDecoderNew::InterruptCallBack(decoder);
		ASSERT_TRUE(decoder->IsSynced());
		ASSERT_FLOAT_EQ(75 + 3.75f, decoder->GetPosition());

		tick += 38;
		EXPECT_CALL(timerService, GetTick())
			.Times(41)
			.WillOnce(Return(tick))
			.WillOnce(Return(tick))
			.WillOnce(Return(tick + 6))
			.WillOnce(Return(tick + 6))
			.WillOnce(Return(tick + 8))
			.WillOnce(Return(tick + 8))
			.WillOnce(Return(tick + 14))
			.WillOnce(Return(tick + 16))
			.WillOnce(Return(tick + 22))
			.WillOnce(Return(tick + 24))
			.WillOnce(Return(tick + 30))
			.WillOnce(Return(tick + 32))
			.WillOnce(Return(tick + 38))
			.WillOnce(Return(tick + 40))
			.WillOnce(Return(tick + 46))
			.WillOnce(Return(tick + 48))
			.WillOnce(Return(tick + 54))
			.WillOnce(Return(tick + 56))
			.WillOnce(Return(tick + 62))
			.WillOnce(Return(tick + 64))
			.WillOnce(Return(tick + 70))
			.WillOnce(Return(tick + 72))
			.WillOnce(Return(tick + 78))
			.WillOnce(Return(tick + 80))
			.WillOnce(Return(tick + 86))
			.WillOnce(Return(tick + 88))
			.WillOnce(Return(tick + 94))
			.WillOnce(Return(tick + 96))
			.WillOnce(Return(tick + 102))
			.WillOnce(Return(tick + 104))
			.WillOnce(Return(tick + 110))
			.WillOnce(Return(tick + 112))
			.WillOnce(Return(tick + 118))
			.WillOnce(Return(tick + 120))
			.WillOnce(Return(tick + 126))
			.WillOnce(Return(tick + 128))
			.WillOnce(Return(tick + 134))
			.WillOnce(Return(tick + 136))
			.WillOnce(Return(tick + 142))
			.WillOnce(Return(tick + 144))
			.WillOnce(Return(tick + 144));

		EXPECT_CALL(digitalService, ReadPin(1))
			.Times(1)
			.WillOnce(Return(false));

		Gm24xDecoderNew::InterruptCallBack(decoder);
		ASSERT_TRUE(decoder->IsSynced());
		ASSERT_FLOAT_EQ(90.0f, decoder->GetPosition());

		EXPECT_CALL(digitalService, ReadPin(1))
			.Times(1)
			.WillOnce(Return(true));

		Gm24xDecoderNew::InterruptCallBack(decoder);
		ASSERT_TRUE(decoder->IsSynced());
		ASSERT_FLOAT_EQ(105 - 3.75f, decoder->GetPosition());

		EXPECT_CALL(digitalService, ReadPin(1))
			.Times(1)
			.WillOnce(Return(false));

		Gm24xDecoderNew::InterruptCallBack(decoder);
		ASSERT_TRUE(decoder->IsSynced());
		ASSERT_FLOAT_EQ(105, decoder->GetPosition());


		EXPECT_CALL(digitalService, ReadPin(1))
			.Times(1)
			.WillOnce(Return(true));

		Gm24xDecoderNew::InterruptCallBack(decoder);
		ASSERT_TRUE(decoder->IsSynced());

		EXPECT_CALL(digitalService, ReadPin(1))
			.Times(1)
			.WillOnce(Return(false));

		Gm24xDecoderNew::InterruptCallBack(decoder);
		ASSERT_TRUE(decoder->IsSynced());

		EXPECT_CALL(digitalService, ReadPin(1))
			.Times(1)
			.WillOnce(Return(true));

		Gm24xDecoderNew::InterruptCallBack(decoder);
		ASSERT_TRUE(decoder->IsSynced());

		EXPECT_CALL(digitalService, ReadPin(1))
			.Times(1)
			.WillOnce(Return(false));

		Gm24xDecoderNew::InterruptCallBack(decoder);
		ASSERT_TRUE(decoder->IsSynced());

		EXPECT_CALL(digitalService, ReadPin(1))
			.Times(1)
			.WillOnce(Return(true));

		Gm24xDecoderNew::InterruptCallBack(decoder);
		ASSERT_TRUE(decoder->IsSynced());

		EXPECT_CALL(digitalService, ReadPin(1))
			.Times(1)
			.WillOnce(Return(false));

		Gm24xDecoderNew::InterruptCallBack(decoder);
		ASSERT_TRUE(decoder->IsSynced());

		EXPECT_CALL(digitalService, ReadPin(1))
			.Times(1)
			.WillOnce(Return(true));

		Gm24xDecoderNew::InterruptCallBack(decoder);
		ASSERT_TRUE(decoder->IsSynced());

		EXPECT_CALL(digitalService, ReadPin(1))
			.Times(1)
			.WillOnce(Return(false));

		Gm24xDecoderNew::InterruptCallBack(decoder);
		ASSERT_TRUE(decoder->IsSynced());

		EXPECT_CALL(digitalService, ReadPin(1))
			.Times(1)
			.WillOnce(Return(true));

		Gm24xDecoderNew::InterruptCallBack(decoder);
		ASSERT_TRUE(decoder->IsSynced());

		EXPECT_CALL(digitalService, ReadPin(1))
			.Times(1)
			.WillOnce(Return(false));

		Gm24xDecoderNew::InterruptCallBack(decoder);
		ASSERT_TRUE(decoder->IsSynced());

		EXPECT_CALL(digitalService, ReadPin(1))
			.Times(1)
			.WillOnce(Return(true));

		Gm24xDecoderNew::InterruptCallBack(decoder);
		ASSERT_TRUE(decoder->IsSynced());

		EXPECT_CALL(digitalService, ReadPin(1))
			.Times(1)
			.WillOnce(Return(false));

		Gm24xDecoderNew::InterruptCallBack(decoder);
		ASSERT_TRUE(decoder->IsSynced());

		EXPECT_CALL(digitalService, ReadPin(1))
			.Times(1)
			.WillOnce(Return(true));

		Gm24xDecoderNew::InterruptCallBack(decoder);
		ASSERT_TRUE(decoder->IsSynced());

		EXPECT_CALL(digitalService, ReadPin(1))
			.Times(1)
			.WillOnce(Return(false));

		Gm24xDecoderNew::InterruptCallBack(decoder);
		ASSERT_TRUE(decoder->IsSynced());

		EXPECT_CALL(digitalService, ReadPin(1))
			.Times(1)
			.WillOnce(Return(true));

		Gm24xDecoderNew::InterruptCallBack(decoder);
		ASSERT_TRUE(decoder->IsSynced());

		EXPECT_CALL(digitalService, ReadPin(1))
			.Times(1)
			.WillOnce(Return(false));

		Gm24xDecoderNew::InterruptCallBack(decoder);
		ASSERT_TRUE(decoder->IsSynced());

		EXPECT_CALL(digitalService, ReadPin(1))
			.Times(1)
			.WillOnce(Return(true));

		Gm24xDecoderNew::InterruptCallBack(decoder);
		ASSERT_TRUE(decoder->IsSynced());

		EXPECT_CALL(digitalService, ReadPin(1))
			.Times(1)
			.WillOnce(Return(false));

		Gm24xDecoderNew::InterruptCallBack(decoder);
		ASSERT_TRUE(decoder->IsSynced());

		EXPECT_CALL(digitalService, ReadPin(1))
			.Times(1)
			.WillOnce(Return(true));

		Gm24xDecoderNew::InterruptCallBack(decoder);
		ASSERT_TRUE(decoder->IsSynced());

		EXPECT_CALL(digitalService, ReadPin(1))
			.Times(1)
			.WillOnce(Return(false));

		Gm24xDecoderNew::InterruptCallBack(decoder);
		ASSERT_TRUE(decoder->IsSynced());

		EXPECT_CALL(digitalService, ReadPin(1))
			.Times(1)
			.WillOnce(Return(true));

		Gm24xDecoderNew::InterruptCallBack(decoder);
		ASSERT_TRUE(decoder->IsSynced());

		EXPECT_CALL(digitalService, ReadPin(1))
			.Times(1)
			.WillOnce(Return(false));

		Gm24xDecoderNew::InterruptCallBack(decoder);
		ASSERT_TRUE(decoder->IsSynced());

		EXPECT_CALL(digitalService, ReadPin(1))
			.Times(1)
			.WillOnce(Return(true));

		Gm24xDecoderNew::InterruptCallBack(decoder);
		ASSERT_TRUE(decoder->IsSynced());

		EXPECT_CALL(digitalService, ReadPin(1))
			.Times(1)
			.WillOnce(Return(false));

		Gm24xDecoderNew::InterruptCallBack(decoder);
		ASSERT_TRUE(decoder->IsSynced());

		EXPECT_CALL(digitalService, ReadPin(1))
			.Times(1)
			.WillOnce(Return(true));

		Gm24xDecoderNew::InterruptCallBack(decoder);
		ASSERT_TRUE(decoder->IsSynced());

		EXPECT_CALL(digitalService, ReadPin(1))
			.Times(1)
			.WillOnce(Return(false));

		Gm24xDecoderNew::InterruptCallBack(decoder);
		ASSERT_TRUE(decoder->IsSynced());

		EXPECT_CALL(digitalService, ReadPin(1))
			.Times(1)
			.WillOnce(Return(true));

		Gm24xDecoderNew::InterruptCallBack(decoder);
		ASSERT_TRUE(decoder->IsSynced());

		EXPECT_CALL(digitalService, ReadPin(1))
			.Times(1)
			.WillOnce(Return(false));

		Gm24xDecoderNew::InterruptCallBack(decoder);
		ASSERT_TRUE(decoder->IsSynced());

		EXPECT_CALL(digitalService, ReadPin(1))
			.Times(1)
			.WillOnce(Return(true));

		Gm24xDecoderNew::InterruptCallBack(decoder);
		ASSERT_TRUE(decoder->IsSynced());

		EXPECT_CALL(digitalService, ReadPin(1))
			.Times(1)
			.WillOnce(Return(false));

		Gm24xDecoderNew::InterruptCallBack(decoder);
		ASSERT_TRUE(decoder->IsSynced());

		EXPECT_CALL(digitalService, ReadPin(1))
			.Times(1)
			.WillOnce(Return(true));

		Gm24xDecoderNew::InterruptCallBack(decoder);
		ASSERT_TRUE(decoder->IsSynced());

		EXPECT_CALL(digitalService, ReadPin(1))
			.Times(1)
			.WillOnce(Return(false));

		Gm24xDecoderNew::InterruptCallBack(decoder);
		ASSERT_TRUE(decoder->IsSynced());

		EXPECT_CALL(digitalService, ReadPin(1))
			.Times(1)
			.WillOnce(Return(true));

		Gm24xDecoderNew::InterruptCallBack(decoder);
		ASSERT_TRUE(decoder->IsSynced());

		EXPECT_CALL(digitalService, ReadPin(1))
			.Times(1)
			.WillOnce(Return(false));

		Gm24xDecoderNew::InterruptCallBack(decoder);
		ASSERT_TRUE(decoder->IsSynced());

		ASSERT_FLOAT_EQ(0, decoder->GetPosition());
	}
}