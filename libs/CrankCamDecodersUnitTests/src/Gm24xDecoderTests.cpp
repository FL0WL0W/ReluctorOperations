#include <functional>
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "MockTimerService.h"
#include "MockDigitalService.h"
#include "HardwareAbstraction/HardwareAbstractionCollection.h"
#include "CrankCamDecoders/ICrankCamDecoder.h"
#include "CrankCamDecoders/Gm24xDecoder.h"
using ::testing::AtLeast;
using ::testing::Return;

using namespace CrankCamDecoders;

namespace UnitTests
{	
	TEST(GM24XDECODER, WhenCrankTriggerImmediatelyAfterCamTriggerCrankPositionIsCorrect)
	{
		HardwareAbstraction::HardwareAbstractionCollection collection;
		HardwareAbstraction::MockTimerService timerService;
		HardwareAbstraction::MockDigitalService digitalService;
		collection.TimerService = &timerService;
		collection.DigitalService = &digitalService;
		Gm24xDecoderConfig config;
		Gm24xDecoder *decoder = new Gm24xDecoder(&collection, &config);
		EXPECT_CALL(timerService, GetTicksPerSecond())
			.Times(AtLeast(1))
			.WillRepeatedly(Return(500000));

		EXPECT_CALL(timerService, GetTick())
			.Times(10)
			.WillOnce(Return(10))
			.WillOnce(Return(2093))
			.WillOnce(Return(4176))
			.WillOnce(Return(6259))
			.WillOnce(Return(8142))
			.WillOnce(Return(8342))
			.WillOnce(Return(8342))
			.WillOnce(Return(10425))
			.WillOnce(Return(10425))
			.WillOnce(Return(11466));

		decoder->CrankEdgeTrigger(EdgeTrigger::Down);

		decoder->CrankEdgeTrigger(EdgeTrigger::Down);
			
		decoder->CrankEdgeTrigger(EdgeTrigger::Down);
			
		decoder->CrankEdgeTrigger(EdgeTrigger::Down);

		decoder->CamEdgeTrigger(EdgeTrigger::Down);

		decoder->CrankEdgeTrigger(EdgeTrigger::Down);
		ASSERT_FLOAT_EQ(0.0f, decoder->GetCrankPosition()) << (const wchar_t*)"crank position not correct";
		ASSERT_EQ(600, (int)decoder->GetRpm()) <<  (const wchar_t*)"rpm not correct";

		decoder->CrankEdgeTrigger(EdgeTrigger::Down);
		ASSERT_FLOAT_EQ(15.0f, decoder->GetCrankPosition()) << (const wchar_t*)"crank position not correct";
		ASSERT_EQ(600, (int)decoder->GetRpm()) <<  (const wchar_t*)"rpm not correct";

		ASSERT_NEAR(22.5f, decoder->GetCrankPosition(), 0.02f) << (const wchar_t*)"crank position not correct";
		ASSERT_EQ(600, (int)decoder->GetRpm()) <<  (const wchar_t*)"rpm not correct";
	}

	TEST(GM24XDECODER, WhenCrankTriggerImmediatelyBeforeCamTriggerCrankPositionIsCorrect)
	{
		HardwareAbstraction::HardwareAbstractionCollection collection;
		HardwareAbstraction::MockTimerService timerService;
		HardwareAbstraction::MockDigitalService digitalService;
		collection.TimerService = &timerService;
		collection.DigitalService = &digitalService;
		Gm24xDecoderConfig config;
		Gm24xDecoder *decoder = new Gm24xDecoder(&collection, &config);
		EXPECT_CALL(timerService, GetTicksPerSecond())
			.Times(AtLeast(1))
			.WillRepeatedly(Return(1000000));

		EXPECT_CALL(timerService, GetTick())
			.Times(10)
			.WillOnce(Return(10))
			.WillOnce(Return(2093))
			.WillOnce(Return(4176))
			.WillOnce(Return(6259))
			.WillOnce(Return(8342))
			.WillOnce(Return(8442))
			.WillOnce(Return(8442))
			.WillOnce(Return(10425))
			.WillOnce(Return(10425))
			.WillOnce(Return(11466));

		decoder->CrankEdgeTrigger(EdgeTrigger::Down);

		decoder->CrankEdgeTrigger(EdgeTrigger::Down);

		decoder->CrankEdgeTrigger(EdgeTrigger::Down);

		decoder->CrankEdgeTrigger(EdgeTrigger::Down);

		decoder->CrankEdgeTrigger(EdgeTrigger::Down);

		decoder->CamEdgeTrigger(EdgeTrigger::Down);
		ASSERT_NEAR(0.72f, decoder->GetCrankPosition(), 0.001f) << (const wchar_t*)"crank position not correct";
		ASSERT_EQ(1200, (int)decoder->GetRpm()) <<  (const wchar_t*)"rpm not correct";

		decoder->CrankEdgeTrigger(EdgeTrigger::Down);
		ASSERT_FLOAT_EQ(15.0f, decoder->GetCrankPosition()) << (const wchar_t*)"crank position not correct";
		ASSERT_EQ(1200, (int)decoder->GetRpm()) <<  (const wchar_t*)"rpm not correct";

		ASSERT_NEAR(22.5f, decoder->GetCrankPosition(), 0.02f) << (const wchar_t*)"crank position not correct";
		ASSERT_EQ(1200, (int)decoder->GetRpm()) <<  (const wchar_t*)"rpm not correct";
	}

	TEST(GM24XDECODER, SyncedReturnsTrueWhenCamTicked)
	{
		HardwareAbstraction::HardwareAbstractionCollection collection;
		HardwareAbstraction::MockTimerService timerService;
		HardwareAbstraction::MockDigitalService digitalService;
		collection.TimerService = &timerService;
		collection.DigitalService = &digitalService;
		Gm24xDecoderConfig config;
		Gm24xDecoder *decoder = new Gm24xDecoder(&collection, &config);

		ASSERT_FALSE(decoder->IsSynced());

		decoder->CamEdgeTrigger(EdgeTrigger::Down);

		ASSERT_TRUE(decoder->IsSynced());

		decoder = new Gm24xDecoder(&collection, &config);

		ASSERT_FALSE(decoder->IsSynced());

		decoder->CamEdgeTrigger(EdgeTrigger::Up);

		ASSERT_TRUE(decoder->IsSynced());
	}

	TEST(GM24XDECODER, HasCamPositionReturnsFalseWhenCamNotTicked)
	{
		HardwareAbstraction::HardwareAbstractionCollection collection;
		HardwareAbstraction::MockTimerService timerService;
		HardwareAbstraction::MockDigitalService digitalService;
		collection.TimerService = &timerService;
		collection.DigitalService = &digitalService;
		Gm24xDecoderConfig config;
		Gm24xDecoder *decoder = new Gm24xDecoder(&collection, &config);

		ASSERT_FALSE(decoder->IsSynced());
		ASSERT_TRUE(decoder->HasCamPosition());

		unsigned int tick = 0;

		for (int i = 0; i < 47; i++)
		{
			tick += 8;
			EXPECT_CALL(timerService, GetTick())
				.Times(1)
				.WillOnce(Return(tick));

			decoder->CrankEdgeTrigger(EdgeTrigger::Down);
			ASSERT_TRUE(decoder->HasCamPosition());
			ASSERT_FALSE(decoder->IsSynced());

			decoder->CrankEdgeTrigger(EdgeTrigger::Up);
			ASSERT_FALSE(decoder->IsSynced());
			ASSERT_TRUE(decoder->HasCamPosition());
		}

		tick += 4;
		EXPECT_CALL(timerService, GetTick())
			.Times(2)
			.WillOnce(Return(tick))
			.WillOnce(Return(tick + 4));

		decoder->CrankEdgeTrigger(EdgeTrigger::Down);
		ASSERT_FALSE(decoder->HasCamPosition());
		ASSERT_FALSE(decoder->IsSynced());

		decoder->CrankEdgeTrigger(EdgeTrigger::Up);
		ASSERT_FALSE(decoder->IsSynced());
		ASSERT_FALSE(decoder->HasCamPosition());
	}

	TEST(GM24XDECODER, SyncedReturnsTrueAfterCrankVerificationWhenCamNotTicked)
	{
		HardwareAbstraction::HardwareAbstractionCollection collection;
		HardwareAbstraction::MockTimerService timerService;
		HardwareAbstraction::MockDigitalService digitalService;
		collection.TimerService = &timerService;
		collection.DigitalService = &digitalService;
		Gm24xDecoderConfig config;
		Gm24xDecoder *decoder = new Gm24xDecoder(&collection, &config);

		ASSERT_FALSE(decoder->IsSynced());
		ASSERT_TRUE(decoder->HasCamPosition());

		unsigned int tick = 0;

		for (int i = 0; i < 47; i++)
		{
			tick += 8;
			EXPECT_CALL(timerService, GetTick())
				.Times(1)
				.WillOnce(Return(tick));

			decoder->CrankEdgeTrigger(EdgeTrigger::Down);
			ASSERT_TRUE(decoder->HasCamPosition());
			ASSERT_FALSE(decoder->IsSynced());

			decoder->CrankEdgeTrigger(EdgeTrigger::Up);
			ASSERT_FALSE(decoder->IsSynced());
			ASSERT_TRUE(decoder->HasCamPosition());
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

		decoder->CrankEdgeTrigger(EdgeTrigger::Down);
		ASSERT_FALSE(decoder->HasCamPosition());
		ASSERT_FALSE(decoder->IsSynced());

		decoder->CrankEdgeTrigger(EdgeTrigger::Up);
		ASSERT_FALSE(decoder->HasCamPosition());
		ASSERT_FALSE(decoder->IsSynced());

		decoder->CrankEdgeTrigger(EdgeTrigger::Down);
		ASSERT_FALSE(decoder->HasCamPosition());
		ASSERT_FALSE(decoder->IsSynced());

		decoder->CrankEdgeTrigger(EdgeTrigger::Up);
		ASSERT_FALSE(decoder->HasCamPosition());
		ASSERT_FALSE(decoder->IsSynced());

		decoder->CrankEdgeTrigger(EdgeTrigger::Down);
		ASSERT_FALSE(decoder->HasCamPosition());
		ASSERT_FALSE(decoder->IsSynced());

		decoder->CrankEdgeTrigger(EdgeTrigger::Up);
		ASSERT_FALSE(decoder->HasCamPosition());
		ASSERT_FALSE(decoder->IsSynced());

		decoder->CrankEdgeTrigger(EdgeTrigger::Down);
		ASSERT_FALSE(decoder->HasCamPosition());
		ASSERT_FALSE(decoder->IsSynced());

		decoder->CrankEdgeTrigger(EdgeTrigger::Up);
		ASSERT_FALSE(decoder->HasCamPosition());
		ASSERT_FALSE(decoder->IsSynced());

		decoder->CrankEdgeTrigger(EdgeTrigger::Down);
		ASSERT_FALSE(decoder->HasCamPosition());
		ASSERT_FALSE(decoder->IsSynced());

		tick += 34;
		EXPECT_CALL(timerService, GetTick())
			.Times(11)
			.WillOnce(Return(tick))
			.WillOnce(Return(tick + 6))
			.WillOnce(Return(tick + 8))
			.WillOnce(Return(tick + 14))
			.WillOnce(Return(tick + 16))
			.WillOnce(Return(tick + 22))
			.WillOnce(Return(tick + 24))
			.WillOnce(Return(tick + 30))
			.WillOnce(Return(tick + 32))
			.WillOnce(Return(tick + 32))
			.WillOnce(Return(tick + 32));

		decoder->CrankEdgeTrigger(EdgeTrigger::Up);
		ASSERT_FALSE(decoder->HasCamPosition());
		ASSERT_FALSE(decoder->IsSynced());

		decoder->CrankEdgeTrigger(EdgeTrigger::Down);
		ASSERT_FALSE(decoder->HasCamPosition());
		ASSERT_FALSE(decoder->IsSynced());

		decoder->CrankEdgeTrigger(EdgeTrigger::Up);
		ASSERT_FALSE(decoder->HasCamPosition());
		ASSERT_FALSE(decoder->IsSynced());

		decoder->CrankEdgeTrigger(EdgeTrigger::Down);
		ASSERT_FALSE(decoder->HasCamPosition());
		ASSERT_FALSE(decoder->IsSynced());

		decoder->CrankEdgeTrigger(EdgeTrigger::Up);
		ASSERT_FALSE(decoder->HasCamPosition());
		ASSERT_FALSE(decoder->IsSynced());

		decoder->CrankEdgeTrigger(EdgeTrigger::Down);
		ASSERT_FALSE(decoder->HasCamPosition());
		ASSERT_FALSE(decoder->IsSynced());

		decoder->CrankEdgeTrigger(EdgeTrigger::Up);
		ASSERT_FALSE(decoder->HasCamPosition());
		ASSERT_FALSE(decoder->IsSynced());

		decoder->CrankEdgeTrigger(EdgeTrigger::Down);
		ASSERT_FALSE(decoder->HasCamPosition());
		ASSERT_FALSE(decoder->IsSynced());

		decoder->CrankEdgeTrigger(EdgeTrigger::Up);
		ASSERT_FALSE(decoder->HasCamPosition());
		ASSERT_TRUE(decoder->IsSynced());
		ASSERT_FLOAT_EQ(75 + 3.75f, decoder->GetCamPosition());
		ASSERT_FLOAT_EQ(75 + 3.75f, decoder->GetCrankPosition());

		tick += 38;
		EXPECT_CALL(timerService, GetTick())
			.Times(45)
			.WillOnce(Return(tick))
			.WillOnce(Return(tick))
			.WillOnce(Return(tick))
			.WillOnce(Return(tick + 6))
			.WillOnce(Return(tick + 6))
			.WillOnce(Return(tick + 6))
			.WillOnce(Return(tick + 8))
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
			.WillOnce(Return(tick + 144))
			.WillOnce(Return(tick + 144));

		decoder->CrankEdgeTrigger(EdgeTrigger::Down);
		ASSERT_FALSE(decoder->HasCamPosition());
		ASSERT_TRUE(decoder->IsSynced());
		ASSERT_FLOAT_EQ(90.0f, decoder->GetCamPosition());
		ASSERT_FLOAT_EQ(90.0f, decoder->GetCrankPosition());

		decoder->CrankEdgeTrigger(EdgeTrigger::Up);
		ASSERT_FALSE(decoder->HasCamPosition());
		ASSERT_TRUE(decoder->IsSynced());
		ASSERT_FLOAT_EQ(105 - 3.75f, decoder->GetCamPosition());
		ASSERT_FLOAT_EQ(105 - 3.75f, decoder->GetCrankPosition());

		decoder->CrankEdgeTrigger(EdgeTrigger::Down);
		ASSERT_FALSE(decoder->HasCamPosition());
		ASSERT_TRUE(decoder->IsSynced());
		ASSERT_FLOAT_EQ(105, decoder->GetCamPosition());
		ASSERT_FLOAT_EQ(105, decoder->GetCrankPosition());


		decoder->CrankEdgeTrigger(EdgeTrigger::Up);
		ASSERT_FALSE(decoder->HasCamPosition());
		ASSERT_TRUE(decoder->IsSynced());

		decoder->CrankEdgeTrigger(EdgeTrigger::Down);
		ASSERT_FALSE(decoder->HasCamPosition());
		ASSERT_TRUE(decoder->IsSynced());

		decoder->CrankEdgeTrigger(EdgeTrigger::Up);
		ASSERT_FALSE(decoder->HasCamPosition());
		ASSERT_TRUE(decoder->IsSynced());

		decoder->CrankEdgeTrigger(EdgeTrigger::Down);
		ASSERT_FALSE(decoder->HasCamPosition());
		ASSERT_TRUE(decoder->IsSynced());

		decoder->CrankEdgeTrigger(EdgeTrigger::Up);
		ASSERT_FALSE(decoder->HasCamPosition());
		ASSERT_TRUE(decoder->IsSynced());

		decoder->CrankEdgeTrigger(EdgeTrigger::Down);
		ASSERT_FALSE(decoder->HasCamPosition());
		ASSERT_TRUE(decoder->IsSynced());

		decoder->CrankEdgeTrigger(EdgeTrigger::Up);
		ASSERT_FALSE(decoder->HasCamPosition());
		ASSERT_TRUE(decoder->IsSynced());

		decoder->CrankEdgeTrigger(EdgeTrigger::Down);
		ASSERT_FALSE(decoder->HasCamPosition());
		ASSERT_TRUE(decoder->IsSynced());

		decoder->CrankEdgeTrigger(EdgeTrigger::Up);
		ASSERT_FALSE(decoder->HasCamPosition());
		ASSERT_TRUE(decoder->IsSynced());

		decoder->CrankEdgeTrigger(EdgeTrigger::Down);
		ASSERT_FALSE(decoder->HasCamPosition());
		ASSERT_TRUE(decoder->IsSynced());

		decoder->CrankEdgeTrigger(EdgeTrigger::Up);
		ASSERT_FALSE(decoder->HasCamPosition());
		ASSERT_TRUE(decoder->IsSynced());

		decoder->CrankEdgeTrigger(EdgeTrigger::Down);
		ASSERT_FALSE(decoder->HasCamPosition());
		ASSERT_TRUE(decoder->IsSynced());

		decoder->CrankEdgeTrigger(EdgeTrigger::Up);
		ASSERT_FALSE(decoder->HasCamPosition());
		ASSERT_TRUE(decoder->IsSynced());

		decoder->CrankEdgeTrigger(EdgeTrigger::Down);
		ASSERT_FALSE(decoder->HasCamPosition());
		ASSERT_TRUE(decoder->IsSynced());

		decoder->CrankEdgeTrigger(EdgeTrigger::Up);
		ASSERT_FALSE(decoder->HasCamPosition());
		ASSERT_TRUE(decoder->IsSynced());

		decoder->CrankEdgeTrigger(EdgeTrigger::Down);
		ASSERT_FALSE(decoder->HasCamPosition());
		ASSERT_TRUE(decoder->IsSynced());

		decoder->CrankEdgeTrigger(EdgeTrigger::Up);
		ASSERT_FALSE(decoder->HasCamPosition());
		ASSERT_TRUE(decoder->IsSynced());

		decoder->CrankEdgeTrigger(EdgeTrigger::Down);
		ASSERT_FALSE(decoder->HasCamPosition());
		ASSERT_TRUE(decoder->IsSynced());

		decoder->CrankEdgeTrigger(EdgeTrigger::Up);
		ASSERT_FALSE(decoder->HasCamPosition());
		ASSERT_TRUE(decoder->IsSynced());

		decoder->CrankEdgeTrigger(EdgeTrigger::Down);
		ASSERT_FALSE(decoder->HasCamPosition());
		ASSERT_TRUE(decoder->IsSynced());

		decoder->CrankEdgeTrigger(EdgeTrigger::Up);
		ASSERT_FALSE(decoder->HasCamPosition());
		ASSERT_TRUE(decoder->IsSynced());

		decoder->CrankEdgeTrigger(EdgeTrigger::Down);
		ASSERT_FALSE(decoder->HasCamPosition());
		ASSERT_TRUE(decoder->IsSynced());

		decoder->CrankEdgeTrigger(EdgeTrigger::Up);
		ASSERT_FALSE(decoder->HasCamPosition());
		ASSERT_TRUE(decoder->IsSynced());

		decoder->CrankEdgeTrigger(EdgeTrigger::Down);
		ASSERT_FALSE(decoder->HasCamPosition());
		ASSERT_TRUE(decoder->IsSynced());

		decoder->CrankEdgeTrigger(EdgeTrigger::Up);
		ASSERT_FALSE(decoder->HasCamPosition());
		ASSERT_TRUE(decoder->IsSynced());

		decoder->CrankEdgeTrigger(EdgeTrigger::Down);
		ASSERT_FALSE(decoder->HasCamPosition());
		ASSERT_TRUE(decoder->IsSynced());

		decoder->CrankEdgeTrigger(EdgeTrigger::Up);
		ASSERT_FALSE(decoder->HasCamPosition());
		ASSERT_TRUE(decoder->IsSynced());

		decoder->CrankEdgeTrigger(EdgeTrigger::Down);
		ASSERT_FALSE(decoder->HasCamPosition());
		ASSERT_TRUE(decoder->IsSynced());

		decoder->CrankEdgeTrigger(EdgeTrigger::Up);
		ASSERT_FALSE(decoder->HasCamPosition());
		ASSERT_TRUE(decoder->IsSynced());

		decoder->CrankEdgeTrigger(EdgeTrigger::Down);
		ASSERT_FALSE(decoder->HasCamPosition());
		ASSERT_TRUE(decoder->IsSynced());

		decoder->CrankEdgeTrigger(EdgeTrigger::Up);
		ASSERT_FALSE(decoder->HasCamPosition());
		ASSERT_TRUE(decoder->IsSynced());

		decoder->CrankEdgeTrigger(EdgeTrigger::Down);
		ASSERT_FALSE(decoder->HasCamPosition());
		ASSERT_TRUE(decoder->IsSynced());

		decoder->CrankEdgeTrigger(EdgeTrigger::Up);
		ASSERT_FALSE(decoder->HasCamPosition());
		ASSERT_TRUE(decoder->IsSynced());

		decoder->CrankEdgeTrigger(EdgeTrigger::Down);
		ASSERT_FALSE(decoder->HasCamPosition());
		ASSERT_TRUE(decoder->IsSynced());

		ASSERT_FLOAT_EQ(0, decoder->GetCamPosition());
		ASSERT_FLOAT_EQ(0, decoder->GetCrankPosition());
	}
}