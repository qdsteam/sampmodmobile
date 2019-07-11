#include "main.h"
#include "game/game.h"
#include "net/netgame.h"
#include "game/common.h"
#include "gui/gui.h"
#include "playerslist.h"
#include "vendor/imgui/imgui_internal.h"
#include "timer.hpp"
#include <stdlib.h>
#include <string.h>

extern CGUI *pGUI;
extern CGame *pGame;
extern CNetGame *pNetGame;

CPlayersList::CPlayersList()
{
	m_bIsActive = false;
    szInfo = " ";
    playersCount = 0;
    out = false;
}

CPlayersList::~CPlayersList()
{

}

void CPlayersList::Show(bool bShow)
{
	if(pGame) 
        pGame->FindPlayerPed()->TogglePlayerControllable(!bShow);

	m_bIsActive = bShow;
    if(bShow != false) out = false;
}

void CPlayersList::Clear()
{
	m_bIsActive = false;
    szInfo = " ";
    playersCount = 0;
    out = false;
}

int lastPlayerCount = 0;
void CPlayersList::Render()
{
	if(!m_bIsActive) return;

	ImGuiIO &io = ImGui::GetIO();

    ImGui::StyleColorsClassic();
    
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(8, 8));

    char motd[256];

    if(pNetGame) sprintf(motd, "> %.64s", pNetGame->m_szHostName);

    ImGui::Begin(motd, nullptr, 
        ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
    ImGui::Text("Players: %i / 1000", playersCount);

    ImGui::ItemSize( ImVec2(0, 1.2) );
    if(ImGui::Button("Close", ImVec2(500, 50)))
    {
        Show(false);
    }

    ImGui::ItemSize( ImVec2(0, 5) );

    ImGui::Text("  ID | Name");

    CPlayerPool* pPlayerPool = pNetGame->GetPlayerPool();

    ImGui::BeginChild("playersChild", ImVec2(500, 650), true, 
                ImGuiWindowFlags_AlwaysUseWindowPadding | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);

    char szBuf[4096] = "";

    for(PLAYERID playerId = 0; playerId < playersCount; playerId++)
    {
        if(pPlayerPool->GetSlotState(playerId) == true)
        {
            CRemotePlayer* pPlayer = pPlayerPool->GetAt(playerId);
            uint32_t dwColor = pPlayer->GetPlayerColor();
            char* pName = (char*)pPlayerPool->GetPlayerName(playerId);

            sprintf(szBuf, "[%i] %s", playerId, pName);
            ImGui::Text("%s", szBuf);
        }
    }

    ImGui::EndChild();

    ImGui::SetWindowSize(ImVec2(-1, -1));
    ImVec2 size = ImGui::GetWindowSize();
    ImGui::SetWindowPos( ImVec2( ((io.DisplaySize.x - size.x)/2), ((io.DisplaySize.y - size.y)/2) ) );
    ImGui::End();
    ImGui::PopStyleVar();
}