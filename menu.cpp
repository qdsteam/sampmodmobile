#include "main.h"
#include "gui/gui.h"
#include "menu.h"
#include "chatwindow.h"
#include "settings.h"

#include "game/game.h"
#include "net/netgame.h"

extern CGUI *pGUI;
extern CGame *pGame;
extern CNetGame *pNetGame;
extern CChatWindow *pChatWindow;
extern CSettings *pSettings;

CMenu::CMenu()
{
	m_fPosX = pGUI->ScaleX( pSettings->Get().fSpawnScreenPosX );
	m_fPosY = pGUI->ScaleY( pSettings->Get().fSpawnScreenPosY );
	m_fSizeX = pGUI->ScaleX( pSettings->Get().fSpawnScreenSizeX );
	m_fSizeY = pGUI->ScaleY( pSettings->Get().fSpawnScreenSizeY );
	m_fButWidth = m_fSizeX / 3;
	m_fButHeight = m_fSizeY * 0.9;

	m_bEnabled = false;
}

void CMenu::Show(bool bShow)
{
	if(pGame)
		pGame->FindPlayerPed()->TogglePlayerControllable(!bShow);
	m_bEnabled = bShow;
}

void CMenu::Render()
{
	if(!m_bEnabled) 
		return;

	ImGuiIO &io = ImGui::GetIO();
	CPlayerPool *pPlayerPool = pNetGame->GetPlayerPool();
	CLocalPlayer *pLocalPlayer = 0;
	if(pPlayerPool) pLocalPlayer = pPlayerPool->GetLocalPlayer();

	MATRIX4X4 matPlayer;
	pLocalPlayer->GetPlayerPed()->GetMatrix(&matPlayer);

	ImGui::Begin("Menu", nullptr, 
		ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | 
		ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoSavedSettings);

	if (ImGui::Button("1", ImVec2(m_fButWidth, m_fButHeight)))
	{
		pGame->PlaySound(1053,matPlayer.pos.X,matPlayer.pos.Y,matPlayer.pos.Z);
		pLocalPlayer->SendMenuRow(0);
	}
	ImGui::SameLine(0, 5);
	if (ImGui::Button("2", ImVec2(m_fButWidth, m_fButHeight)))
	{
		pGame->PlaySound(1052,matPlayer.pos.X,matPlayer.pos.Y,matPlayer.pos.Z);
		pLocalPlayer->SendMenuRow(1);
	}
	ImGui::SameLine(0, 5);
	if (ImGui::Button("3", ImVec2(m_fButWidth, m_fButHeight)))
	{
		pGame->PlaySound(1052,matPlayer.pos.X,matPlayer.pos.Y,matPlayer.pos.Z);
		pLocalPlayer->SendMenuRow(2);
	}
	if (ImGui::Button("4", ImVec2(m_fButWidth, m_fButHeight)))
	{
		pGame->PlaySound(1052,matPlayer.pos.X,matPlayer.pos.Y,matPlayer.pos.Z);
		pLocalPlayer->SendMenuRow(3);
	}
	ImGui::SameLine(0, 5);
	if (ImGui::Button("5", ImVec2(m_fButWidth, m_fButHeight)))
	{
		pGame->PlaySound(1052,matPlayer.pos.X,matPlayer.pos.Y,matPlayer.pos.Z);
		pLocalPlayer->SendMenuRow(4);
	}
	ImGui::SameLine(0, 5);
	if (ImGui::Button("6", ImVec2(m_fButWidth, m_fButHeight)))
	{
		pGame->PlaySound(1052,matPlayer.pos.X,matPlayer.pos.Y,matPlayer.pos.Z);
		pLocalPlayer->SendMenuRow(5);
	}

	if (ImGui::Button("7", ImVec2(m_fButWidth, m_fButHeight)))
	{
		pGame->PlaySound(1052,matPlayer.pos.X,matPlayer.pos.Y,matPlayer.pos.Z);
		pLocalPlayer->SendMenuRow(6);
	}
	ImGui::SameLine(0, 5);
	if (ImGui::Button("8", ImVec2(m_fButWidth, m_fButHeight)))
	{
		pGame->PlaySound(1052,matPlayer.pos.X,matPlayer.pos.Y,matPlayer.pos.Z);
		pLocalPlayer->SendMenuRow(7);
	}
	ImGui::SameLine(0, 5);
	if (ImGui::Button("9", ImVec2(m_fButWidth, m_fButHeight)))
	{
		pGame->PlaySound(1052,matPlayer.pos.X,matPlayer.pos.Y,matPlayer.pos.Z);
		pLocalPlayer->SendMenuRow(8);
	}

	ImGui::SetWindowSize(ImVec2(-1, -1));
	ImVec2 size = ImGui::GetWindowSize();
	
	ImGui::SetWindowPos( ImVec2( ((io.DisplaySize.x - size.x)/2), ((io.DisplaySize.y * 0.95) - size.y) ) );
	ImGui::End();
}