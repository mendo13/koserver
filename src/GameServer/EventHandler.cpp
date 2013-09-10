#include "stdafx.h"
#include "DBAgent.h"

using std::string;
using std::vector;

void CGameServerDlg::SendBifrostTime(CUser *pUser, bool bSendAll) {

	Packet result(WIZ_BIFROST,uint8(BIFROST_EVENT));
	result << g_pMain->m_sBifrostRemainingTime;

	if (bSendAll)
	{
		g_pMain->Send_All(&result,nullptr, 0, ZONE_RONARK_LAND);
		g_pMain->Send_All(&result,nullptr, 0, ZONE_BIFROST);
	}
	else
	{
		if (pUser == nullptr)
			return;

		pUser->Send(&result);
	}
}

void CUser::BifrostProcess(CUser * pUser)
{
	if (pUser == nullptr)
		return;

	if (g_pMain->m_BifrostVictory == 0 && g_pMain->m_bAttackBifrostMonument)
	{
		g_pMain->m_sBifrostTime = g_pMain->m_xBifrostTime;
		g_pMain->m_sBifrostRemainingTime = g_pMain->m_sBifrostTime;
		g_pMain->m_BifrostVictory = pUser->GetNation();
		g_pMain->SendFormattedResource(pUser->GetNation() == ELMORAD ? IDS_BEEF_ROAST_VICTORY_ELMORAD : IDS_BEEF_ROAST_VICTORY_KARUS, Nation::ALL,false);
		g_pMain->SendBifrostTime(nullptr, true);

		if (g_pMain->m_bAttackBifrostMonument)
			g_pMain->m_bAttackBifrostMonument = false;
	}
	else if (g_pMain->m_BifrostVictory == 1 || g_pMain->m_BifrostVictory == 2) 
	{
		if (pUser->GetNation() != g_pMain->m_BifrostVictory && g_pMain->m_bAttackBifrostMonument)
		{
			g_pMain->m_BifrostVictory = 3;
			g_pMain->SendFormattedResource(pUser->GetNation() == ELMORAD ? IDS_BEEF_ROAST_VICTORY_ELMORAD : IDS_BEEF_ROAST_VICTORY_KARUS, Nation::ALL,false);

			if (g_pMain->m_bAttackBifrostMonument)
				g_pMain->m_bAttackBifrostMonument = false;
		}
	}
}

void CUser::TempleProcess(Packet &pkt )
{
	uint8 opcode = pkt.read<uint8>();

	switch(opcode)
	{
	case MONSTER_STONE:
		MonsterStoneProcess(); 
	case TEMPLE_JOIN:
		TempleOperations(opcode);
		break;
	case TEMPLE_DISBAND:
		TempleOperations(opcode);
		break;
	}
}

void CUser::MonsterStoneProcess()
{

} 

void CUser::TempleOperations(uint8 bType)
{
	uint16 nActiveEvent = g_pMain->pTempleEvent.ActiveEvent;

	uint8 bResult = 1;
	Packet result(WIZ_EVENT);

	if(bType == TEMPLE_JOIN && !isJoinedTemple())
	{
		result <<  uint8(TEMPLE_JOIN) << bResult << nActiveEvent;
		if (nActiveEvent == EVENT_CHAOS)
		{
			if (CheckExistItem(910246000,1))
				bResult = 1;
			else if (m_sItemArray[RIGHTHAND].nNum == MATTOCK || m_sItemArray[RIGHTHAND].nNum == GOLDEN_MATTOCK || isMining())
				bResult = 4; 
			else
				bResult = 3;
		}

		if (bResult != 1)
		{
			result.put(0, bResult);
			Send(&result);
			return;
		}

		if(bResult == 1) {
			GetNation() == KARUS ? g_pMain->pTempleEvent.KarusUserCount++ :g_pMain->pTempleEvent.ElMoradUserCount++;
			g_pMain->pTempleEvent.AllUserCount = (g_pMain->pTempleEvent.KarusUserCount + g_pMain->pTempleEvent.ElMoradUserCount);
			Send(&result);
			SetJoinedStatus();
		}

		TempleOperations(TEMPLE_COUNTER);
	}
	else if (bType == TEMPLE_DISBAND && isJoinedTemple())
	{
		result <<  uint8(TEMPLE_DISBAND) << bResult << nActiveEvent;
		GetNation() == KARUS ? g_pMain->pTempleEvent.KarusUserCount-- : g_pMain->pTempleEvent.ElMoradUserCount--;
		g_pMain->pTempleEvent.AllUserCount = g_pMain->pTempleEvent.KarusUserCount + g_pMain->pTempleEvent.ElMoradUserCount;
		Send(&result);
		SetJoinedStatus();
		TempleOperations(TEMPLE_COUNTER);
	}
	else if (bType == TEMPLE_COUNTER)
	{
		result << uint8(TEMPLE_COUNTER) << nActiveEvent;

		if(nActiveEvent == EVENT_CHAOS)
			result << g_pMain->pTempleEvent.AllUserCount;
		else
			result << g_pMain->pTempleEvent.KarusUserCount << g_pMain->pTempleEvent.ElMoradUserCount;

		g_pMain->Send_All(&result);
	}
}