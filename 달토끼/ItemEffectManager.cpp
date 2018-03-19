#include "pch.h"
#include "Item.h"
#include "FootBoardManager.h"
#include "Player.h"
#include "ItemEffectManager.h"

//������ 3���� ���� ���ϴ�.
void ItemEffectManager::ItemEffect_Star()
{
	int playerLength = m_pPlayer->Get_BoardLength() + 1;
	if (m_pFootboardManager)
	{
		for (int len = playerLength; len < playerLength + m_StarPlusLenght; ++len) {
			m_pFootboardManager->IsExisted_FootBoard(len, k_LeftIndex);
			m_pFootboardManager->IsExisted_FootBoard(len, k_FrontIndex);
			m_pFootboardManager->IsExisted_FootBoard(len, k_RightIndex);
		}
	}
}

void ItemEffectManager::ItemEffect_Carrat()
{
	if (m_pPlayer) {
		m_pPlayer->StateChange_AutoWaiting();
	}
}

void ItemEffectManager::ItemEffect_Shield()
{
	if (m_pPlayer) {

	}
}
