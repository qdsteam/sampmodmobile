#include "main.h"
#include "game/game.h"
#include "net/netgame.h"
#include "game/common.h"
#include "gui/gui.h"
#include "playerslist.h"
#include "vendor/imgui/imgui_internal.h"
#include <stdlib.h>
#include <string.h>

extern CGUI *pGUI;
extern CGame *pGame;
extern CNetGame *pNetGame;

CPlayersList::CPlayersList()
{
	m_bIsActive = false;
}

CPlayersList::~CPlayersList()
{

}

void CPlayersList::Show(bool bShow)
{
	if(pGame) 
        pGame->FindPlayerPed()->TogglePlayerControllable(!bShow);

	m_bIsActive = bShow;
}

void CPlayersList::Clear()
{
	m_bIsActive = false;
}

void CPlayersList::AddToList(char *buf)
{
    szBuf = buf;
}

void CPlayersList::RemoveFromList(char *buf)
{
    // todo
}

void CPlayersList::Render()
{
	if(!m_bIsActive) return;

	ImGuiIO &io = ImGui::GetIO();

    ImGui::StyleColorsClassic();
    
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(8, 8));

    char motd[256];

    if(pNetGame) sprintf(motd, "> %.64s", pNetGame->m_szHostName);

    ImGui::Begin(motd, nullptr, 
        ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);

    // todo

    ImGui::SetWindowSize(ImVec2(-8, -8));
    ImVec2 size = ImGui::GetWindowSize();
    ImGui::SetWindowPos( ImVec2( ((io.DisplaySize.x - size.x)/2), ((io.DisplaySize.y - size.y)/2) ) );
    ImGui::End();
    ImGui::PopStyleVar();
}