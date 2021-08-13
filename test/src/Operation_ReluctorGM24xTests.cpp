#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "Operations/Operation_ReluctorGM24x.h"
using namespace testing;
using namespace OperationArchitecture;

namespace UnitTests
{
	class Operation_ReluctorGM24xTests : public Test
	{
		protected:
		IOperationBase *_operation;
		Record *_record;

		Operation_ReluctorGM24xTests() 
		{			
			size_t size = 0;
			_operation = &Operation_ReluctorGM24x::Instance;

			_record = new Record();
			_record->TicksPerSecond = 5000;
			_record->Initialize(200);
			_record->Frames[0].State = false;
			_record->Frames[0].Valid = true;
			_record->Frames[0].Tick = 0;
			_record->Frames[1].State = true;
			_record->Frames[1].Valid = true;
			_record->Frames[1].Tick = 1200;
			_record->Frames[2].State = false;
			_record->Frames[2].Valid = true;
			_record->Frames[2].Tick = 1500;
			_record->Frames[3].State = true;
			_record->Frames[3].Valid = true;
			_record->Frames[3].Tick = 1800;
			_record->Frames[4].State = false;
			_record->Frames[4].Valid = true;
			_record->Frames[4].Tick = 3000;
			_record->Frames[5].State = true;
			_record->Frames[5].Valid = true;
			_record->Frames[5].Tick = 3300;
			_record->Frames[6].State = false;
			_record->Frames[6].Valid = true;
			_record->Frames[6].Tick = 4500;
			_record->Frames[7].State = true;
			_record->Frames[7].Valid = true;
			_record->Frames[7].Tick = 4800;
			_record->Frames[8].State = false;
			_record->Frames[8].Valid = true;
			_record->Frames[8].Tick = 6000;
			_record->Frames[9].State = true;
			_record->Frames[9].Valid = true;
			_record->Frames[9].Tick = 6300;
			_record->Frames[10].State = false;
			_record->Frames[10].Valid = true;
			_record->Frames[10].Tick = 7500;
			_record->Frames[11].State = true;
			_record->Frames[11].Valid = true;
			_record->Frames[11].Tick = 7800;
			_record->Frames[12].State = false;
			_record->Frames[12].Valid = true;
			_record->Frames[12].Tick = 9000;
			_record->Frames[13].State = true;
			_record->Frames[13].Valid = true;
			_record->Frames[13].Tick = 10200;
			_record->Frames[14].State = false;
			_record->Frames[14].Valid = true;
			_record->Frames[14].Tick = 10500;
			_record->Frames[15].State = true;
			_record->Frames[15].Valid = true;
			_record->Frames[15].Tick = 10800;
			_record->Frames[16].State = false;
			_record->Frames[16].Valid = true;
			_record->Frames[16].Tick = 12000;
			_record->Frames[17].State = true;
			_record->Frames[17].Valid = true;
			_record->Frames[17].Tick = 12300;
			_record->Frames[18].State = false;
			_record->Frames[18].Valid = true;
			_record->Frames[18].Tick = 13500;
			_record->Frames[19].State = true;
			_record->Frames[19].Valid = true;
			_record->Frames[19].Tick = 13800;
			_record->Frames[20].State = false;
			_record->Frames[20].Valid = true;
			_record->Frames[20].Tick = 15000;
			_record->Frames[21].State = true;
			_record->Frames[21].Valid = true;
			_record->Frames[21].Tick = 16200;
			_record->Frames[22].State = false;
			_record->Frames[22].Valid = true;
			_record->Frames[22].Tick = 16500;
			_record->Frames[23].State = true;
			_record->Frames[23].Valid = true;
			_record->Frames[23].Tick = 17700;
			_record->Frames[24].State = false;
			_record->Frames[24].Valid = true;
			_record->Frames[24].Tick = 18000;
			_record->Frames[25].State = true;
			_record->Frames[25].Valid = true;
			_record->Frames[25].Tick = 18300;
			_record->Frames[26].State = false;
			_record->Frames[26].Valid = true;
			_record->Frames[26].Tick = 19500;
			_record->Frames[27].State = true;
			_record->Frames[27].Valid = true;
			_record->Frames[27].Tick = 19800;
			_record->Frames[28].State = false;
			_record->Frames[28].Valid = true;
			_record->Frames[28].Tick = 21000;
			_record->Frames[29].State = true;
			_record->Frames[29].Valid = true;
			_record->Frames[29].Tick = 22200;
			_record->Frames[30].State = false;
			_record->Frames[30].Valid = true;
			_record->Frames[30].Tick = 22500;
			_record->Frames[31].State = true;
			_record->Frames[31].Valid = true;
			_record->Frames[31].Tick = 23700;
			_record->Frames[32].State = false;
			_record->Frames[32].Valid = true;
			_record->Frames[32].Tick = 24000;
			_record->Frames[33].State = true;
			_record->Frames[33].Valid = true;
			_record->Frames[33].Tick = 25200;
			_record->Frames[34].State = false;
			_record->Frames[34].Valid = true;
			_record->Frames[34].Tick = 25500;
			_record->Frames[35].State = true;
			_record->Frames[35].Valid = true;
			_record->Frames[35].Tick = 25800;
			_record->Frames[36].State = false;
			_record->Frames[36].Valid = true;
			_record->Frames[36].Tick = 27000;
			_record->Frames[37].State = true;
			_record->Frames[37].Valid = true;
			_record->Frames[37].Tick = 28200;
			_record->Frames[38].State = false;
			_record->Frames[38].Valid = true;
			_record->Frames[38].Tick = 28500;
			_record->Frames[39].State = true;
			_record->Frames[39].Valid = true;
			_record->Frames[39].Tick = 28800;
			_record->Frames[40].State = false;
			_record->Frames[40].Valid = true;
			_record->Frames[40].Tick = 30000;
			_record->Frames[41].State = true;
			_record->Frames[41].Valid = true;
			_record->Frames[41].Tick = 31200;
			_record->Frames[42].State = false;
			_record->Frames[42].Valid = true;
			_record->Frames[42].Tick = 31500;
			_record->Frames[43].State = true;
			_record->Frames[43].Valid = true;
			_record->Frames[43].Tick = 32700;
			_record->Frames[44].State = false;
			_record->Frames[44].Valid = true;
			_record->Frames[44].Tick = 33000;
			_record->Frames[45].State = true;
			_record->Frames[45].Valid = true;
			_record->Frames[45].Tick = 34200;
			_record->Frames[46].State = false;
			_record->Frames[46].Valid = true;
			_record->Frames[46].Tick = 34500;
			_record->Frames[47].State = true;
			_record->Frames[47].Valid = true;
			_record->Frames[47].Tick = 35700;
			_record->Frames[48].State = false;
			_record->Frames[48].Valid = true;
			_record->Frames[48].Tick = 36000;
			_record->Frames[49].State = true;
			_record->Frames[49].Valid = true;
			_record->Frames[49].Tick = 37200;
			_record->Frames[50].State = false;
			_record->Frames[50].Valid = true;
			_record->Frames[50].Tick = 37500;
			_record->Frames[51].State = true;
			_record->Frames[51].Valid = true;
			_record->Frames[51].Tick = 37800;
			_record->Frames[52].State = false;
			_record->Frames[52].Valid = true;
			_record->Frames[52].Tick = 39000;
			_record->Frames[53].State = true;
			_record->Frames[53].Valid = true;
			_record->Frames[53].Tick = 39300;
			_record->Frames[54].State = false;
			_record->Frames[54].Valid = true;
			_record->Frames[54].Tick = 40500;
			_record->Frames[55].State = true;
			_record->Frames[55].Valid = true;
			_record->Frames[55].Tick = 40800;
			_record->Frames[56].State = false;
			_record->Frames[56].Valid = true;
			_record->Frames[56].Tick = 42000;
			_record->Frames[57].State = true;
			_record->Frames[57].Valid = true;
			_record->Frames[57].Tick = 42300;
			_record->Frames[58].State = false;
			_record->Frames[58].Valid = true;
			_record->Frames[58].Tick = 43500;
			_record->Last = 58;
		}
	};

	TEST_F(Operation_ReluctorGM24xTests, DegreeIsCorrectForCorrectTick)
	{
		//not enough pulses to sync
		ASSERT_EQ(false, _operation->Execute<ReluctorResult>(_record, 0).Synced);
		ASSERT_EQ(false, _operation->Execute<ReluctorResult>(_record, 10).Synced);
		ASSERT_EQ(false, _operation->Execute<ReluctorResult>(_record, 100).Synced);
		ASSERT_EQ(false, _operation->Execute<ReluctorResult>(_record, 1000).Synced);
		ASSERT_EQ(false, _operation->Execute<ReluctorResult>(_record, 1000).Synced);
		ASSERT_EQ(false, _operation->Execute<ReluctorResult>(_record, 5900).Synced);
		//synced
		ASSERT_EQ(true, _operation->Execute<ReluctorResult>(_record, 6000).Synced);
		ASSERT_EQ(60, _operation->Execute<ReluctorResult>(_record, 6000).Position);
		ASSERT_EQ(50, _operation->Execute<ReluctorResult>(_record, 6000).PositionDot);
		ASSERT_EQ(61, _operation->Execute<ReluctorResult>(_record, 6100).Position);
		ASSERT_EQ(61.5, _operation->Execute<ReluctorResult>(_record, 6150).Position);
		ASSERT_EQ(63, _operation->Execute<ReluctorResult>(_record, 6300).Position);
		ASSERT_EQ(64, _operation->Execute<ReluctorResult>(_record, 6400).Position);
		ASSERT_EQ(75, _operation->Execute<ReluctorResult>(_record, 7500).Position);
		ASSERT_EQ(76, _operation->Execute<ReluctorResult>(_record, 7600).Position);
		ASSERT_EQ(78, _operation->Execute<ReluctorResult>(_record, 7800).Position);
		ASSERT_EQ(79, _operation->Execute<ReluctorResult>(_record, 7900).Position);
		ASSERT_EQ(90, _operation->Execute<ReluctorResult>(_record, 9000).Position);
		ASSERT_EQ(91, _operation->Execute<ReluctorResult>(_record, 9100).Position);
		ASSERT_EQ(102, _operation->Execute<ReluctorResult>(_record, 10200).Position);
		ASSERT_EQ(103, _operation->Execute<ReluctorResult>(_record, 10300).Position);
		ASSERT_EQ(105, _operation->Execute<ReluctorResult>(_record, 10500).Position);
		ASSERT_EQ(106, _operation->Execute<ReluctorResult>(_record, 10600).Position);
		ASSERT_EQ(108, _operation->Execute<ReluctorResult>(_record, 10800).Position);
		ASSERT_EQ(109, _operation->Execute<ReluctorResult>(_record, 10900).Position);
		ASSERT_EQ(120, _operation->Execute<ReluctorResult>(_record, 12000).Position);
		ASSERT_EQ(121, _operation->Execute<ReluctorResult>(_record, 12100).Position);
		ASSERT_EQ(123, _operation->Execute<ReluctorResult>(_record, 12300).Position);
		ASSERT_EQ(124, _operation->Execute<ReluctorResult>(_record, 12400).Position);
		ASSERT_EQ(135, _operation->Execute<ReluctorResult>(_record, 13500).Position);
		ASSERT_EQ(136, _operation->Execute<ReluctorResult>(_record, 13600).Position);
		ASSERT_EQ(138, _operation->Execute<ReluctorResult>(_record, 13800).Position);
		ASSERT_EQ(139, _operation->Execute<ReluctorResult>(_record, 13900).Position);
		ASSERT_EQ(150, _operation->Execute<ReluctorResult>(_record, 15000).Position);
		ASSERT_EQ(151, _operation->Execute<ReluctorResult>(_record, 15100).Position);
		ASSERT_EQ(162, _operation->Execute<ReluctorResult>(_record, 16200).Position);
		ASSERT_EQ(163, _operation->Execute<ReluctorResult>(_record, 16300).Position);
		ASSERT_EQ(165, _operation->Execute<ReluctorResult>(_record, 16500).Position);
		ASSERT_EQ(166, _operation->Execute<ReluctorResult>(_record, 16600).Position);
		ASSERT_EQ(177, _operation->Execute<ReluctorResult>(_record, 17700).Position);
		ASSERT_EQ(178, _operation->Execute<ReluctorResult>(_record, 17800).Position);
		ASSERT_EQ(180, _operation->Execute<ReluctorResult>(_record, 18000).Position);
		ASSERT_EQ(181, _operation->Execute<ReluctorResult>(_record, 18100).Position);
		ASSERT_EQ(183, _operation->Execute<ReluctorResult>(_record, 18300).Position);
		ASSERT_EQ(184, _operation->Execute<ReluctorResult>(_record, 18400).Position);
		ASSERT_EQ(195, _operation->Execute<ReluctorResult>(_record, 19500).Position);
		ASSERT_EQ(196, _operation->Execute<ReluctorResult>(_record, 19600).Position);
		ASSERT_EQ(198, _operation->Execute<ReluctorResult>(_record, 19800).Position);
		ASSERT_EQ(199, _operation->Execute<ReluctorResult>(_record, 19900).Position);
		ASSERT_EQ(210, _operation->Execute<ReluctorResult>(_record, 21000).Position);
		ASSERT_EQ(211, _operation->Execute<ReluctorResult>(_record, 21100).Position);
		ASSERT_EQ(222, _operation->Execute<ReluctorResult>(_record, 22200).Position);
		ASSERT_EQ(223, _operation->Execute<ReluctorResult>(_record, 22300).Position);
		ASSERT_EQ(225, _operation->Execute<ReluctorResult>(_record, 22500).Position);
		ASSERT_EQ(226, _operation->Execute<ReluctorResult>(_record, 22600).Position);
		ASSERT_EQ(237, _operation->Execute<ReluctorResult>(_record, 23700).Position);
		ASSERT_EQ(238, _operation->Execute<ReluctorResult>(_record, 23800).Position);
		ASSERT_EQ(240, _operation->Execute<ReluctorResult>(_record, 24000).Position);
		ASSERT_EQ(241, _operation->Execute<ReluctorResult>(_record, 24100).Position);
		ASSERT_EQ(252, _operation->Execute<ReluctorResult>(_record, 25200).Position);
		ASSERT_EQ(253, _operation->Execute<ReluctorResult>(_record, 25300).Position);
		ASSERT_EQ(255, _operation->Execute<ReluctorResult>(_record, 25500).Position);
		ASSERT_EQ(256, _operation->Execute<ReluctorResult>(_record, 25600).Position);
		ASSERT_EQ(258, _operation->Execute<ReluctorResult>(_record, 25800).Position);
		ASSERT_EQ(259, _operation->Execute<ReluctorResult>(_record, 25900).Position);
		ASSERT_EQ(270, _operation->Execute<ReluctorResult>(_record, 27000).Position);
		ASSERT_EQ(271, _operation->Execute<ReluctorResult>(_record, 27100).Position);
		ASSERT_EQ(282, _operation->Execute<ReluctorResult>(_record, 28200).Position);
		ASSERT_EQ(283, _operation->Execute<ReluctorResult>(_record, 28300).Position);
		ASSERT_EQ(285, _operation->Execute<ReluctorResult>(_record, 28500).Position);
		ASSERT_EQ(286, _operation->Execute<ReluctorResult>(_record, 28600).Position);
		ASSERT_EQ(288, _operation->Execute<ReluctorResult>(_record, 28800).Position);
		ASSERT_EQ(289, _operation->Execute<ReluctorResult>(_record, 28900).Position);
		ASSERT_EQ(301, _operation->Execute<ReluctorResult>(_record, 30100).Position);
		ASSERT_EQ(312, _operation->Execute<ReluctorResult>(_record, 31200).Position);
		ASSERT_EQ(313, _operation->Execute<ReluctorResult>(_record, 31300).Position);
		ASSERT_EQ(315, _operation->Execute<ReluctorResult>(_record, 31500).Position);
		ASSERT_EQ(316, _operation->Execute<ReluctorResult>(_record, 31600).Position);
		ASSERT_EQ(327, _operation->Execute<ReluctorResult>(_record, 32700).Position);
		ASSERT_EQ(328, _operation->Execute<ReluctorResult>(_record, 32800).Position);
		ASSERT_EQ(330, _operation->Execute<ReluctorResult>(_record, 33000).Position);
		ASSERT_EQ(331, _operation->Execute<ReluctorResult>(_record, 33100).Position);
		ASSERT_EQ(342, _operation->Execute<ReluctorResult>(_record, 34200).Position);
		ASSERT_EQ(343, _operation->Execute<ReluctorResult>(_record, 34300).Position);
		ASSERT_EQ(345, _operation->Execute<ReluctorResult>(_record, 34500).Position);
		ASSERT_EQ(346, _operation->Execute<ReluctorResult>(_record, 34600).Position);
		ASSERT_EQ(352, _operation->Execute<ReluctorResult>(_record, 35200).Position);
		ASSERT_EQ(353, _operation->Execute<ReluctorResult>(_record, 35300).Position);
		ASSERT_EQ(0, _operation->Execute<ReluctorResult>(_record, 36000).Position);
		ASSERT_EQ(1, _operation->Execute<ReluctorResult>(_record, 36100).Position);
		ASSERT_EQ(12, _operation->Execute<ReluctorResult>(_record, 37200).Position);
		ASSERT_EQ(13, _operation->Execute<ReluctorResult>(_record, 37300).Position);
		ASSERT_EQ(15, _operation->Execute<ReluctorResult>(_record, 37500).Position);
		ASSERT_EQ(16, _operation->Execute<ReluctorResult>(_record, 37600).Position);
		ASSERT_EQ(18, _operation->Execute<ReluctorResult>(_record, 37800).Position);
		ASSERT_EQ(19, _operation->Execute<ReluctorResult>(_record, 37900).Position);
		ASSERT_EQ(30, _operation->Execute<ReluctorResult>(_record, 39000).Position);
		ASSERT_EQ(31, _operation->Execute<ReluctorResult>(_record, 39100).Position);
		ASSERT_EQ(33, _operation->Execute<ReluctorResult>(_record, 39300).Position);
		ASSERT_EQ(34, _operation->Execute<ReluctorResult>(_record, 39400).Position);
		ASSERT_EQ(45, _operation->Execute<ReluctorResult>(_record, 40500).Position);
		ASSERT_EQ(46, _operation->Execute<ReluctorResult>(_record, 40600).Position);
		ASSERT_EQ(48, _operation->Execute<ReluctorResult>(_record, 40800).Position);
		ASSERT_EQ(49, _operation->Execute<ReluctorResult>(_record, 40900).Position);
		ASSERT_EQ(59, _operation->Execute<ReluctorResult>(_record, 41900).Position);
		ASSERT_EQ(60, _operation->Execute<ReluctorResult>(_record, 42000).Position);

		//too much time without a pulse
		ASSERT_EQ(false, _operation->Execute<ReluctorResult>(_record, 100000).Synced);
	}
}
