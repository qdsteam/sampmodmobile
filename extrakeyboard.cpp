#include "main.h"
#include "game/game.h"
#include "net/netgame.h"
#include "game/common.h"
#include "gui/gui.h"
#include "extrakeyboard.h"
#include "vendor/imgui/imgui_internal.h"
#include "keyboard.h"
#include "chatwindow.h"
#include "net/vehiclepool.h"
#include <stdlib.h>
#include <string.h>
#include "settings.h"
#include "sets.h"
#include "modsa.h"
#include "dialog.h"
#include "customserver.h"
#include "net/playerpool.h"
#include "net/localplayer.h"

extern CGUI *pGUI;
extern CGame *pGame;
extern CNetGame *pNetGame;
extern CKeyBoard *pKeyBoard;
extern CChatWindow *pChatWindow;
extern CSettings *pSettings;
extern CSetsWindow *pSetsWindow;
extern CModSAWindow *pModSAWindow;

CExtraKeyBoard::CExtraKeyBoard()
{
	m_bIsActive = false;
}

CExtraKeyBoard::~CExtraKeyBoard()
{

}

void CExtraKeyBoard::Show(bool bShow)
{
	if(pGame) 
        pGame->FindPlayerPed()->TogglePlayerControllable(!bShow);

	m_bIsActive = bShow;
}

void CExtraKeyBoard::Clear()
{
	m_bIsActive = false;
}

void CExtraKeyBoard::AddKeys()
{
    CPlayerPool *pPlayerPool = pNetGame->GetPlayerPool();
    CLocalPlayer *pLocalPlayer = 0;
    if(pPlayerPool) pLocalPlayer = pPlayerPool->GetLocalPlayer();

    if(ImGui::Button("ALT", ImVec2(350, 50)))
    {
         key = ID_KEY_ALT;
         pLocalPlayer->SendFakeOnFootFullSyncData();
         Show(false);
    }

    if(ImGui::Button("C", ImVec2(350, 50)))
    {
         key = ID_KEY_C;
         pLocalPlayer->SendFakeOnFootFullSyncData();
         Show(false);
    }

    if(ImGui::Button("TAB", ImVec2(350, 50)))
    {
         key = ID_KEY_TAB;
         pLocalPlayer->SendFakeOnFootFullSyncData();
         Show(false);
    }

    if(ImGui::Button("LCTRL", ImVec2(350, 50)))
    {
         key = ID_KEY_LCTRL;
         pLocalPlayer->SendFakeOnFootFullSyncData();
         Show(false);
    }

    if(ImGui::Button("SPACE", ImVec2(350, 50)))
    {
         key = ID_KEY_SPACE;
         pLocalPlayer->SendFakeOnFootFullSyncData();
         Show(false);
    }

    if(ImGui::Button("ENTER", ImVec2(350, 50)))
    {
         key = ID_KEY_ENTER;
         pLocalPlayer->SendFakeOnFootFullSyncData();
         Show(false);
    }

    if(ImGui::Button("LSHIFT", ImVec2(350, 50)))
    {
         key = ID_KEY_LSHIFT;
         pLocalPlayer->SendFakeOnFootFullSyncData();
         Show(false);
    }

    if(ImGui::Button("E", ImVec2(350, 50)))
    {
         key = ID_KEY_E;
         pLocalPlayer->SendFakeOnFootFullSyncData();
         Show(false);
    }

    if(ImGui::Button("Q", ImVec2(350, 50)))
    {
         key = ID_KEY_Q;
         pLocalPlayer->SendFakeOnFootFullSyncData();
         Show(false);
    }

    if(ImGui::Button("RMB", ImVec2(350, 50)))
    {
         key = ID_KEY_RMB;
         pLocalPlayer->SendFakeOnFootFullSyncData();
         Show(false);
    }

    if(ImGui::Button("2", ImVec2(350, 50)))
    {
         key = ID_KEY_TWO;
         pLocalPlayer->SendFakeOnFootFullSyncData();
         Show(false);
    }

    if(ImGui::Button("Numpad +", ImVec2(350, 50)))
    {
         key = ID_KEY_TWOS;
         pLocalPlayer->SendFakeOnFootFullSyncData();
         Show(false);
    }

    if(ImGui::Button("Y", ImVec2(350, 50)))
    {
         key = ID_KEY_Y;
         pLocalPlayer->SendFakeOnFootFullSyncData();
         Show(false);
    }

    if(ImGui::Button("N", ImVec2(350, 50)))
    {
         key = ID_KEY_N;
         pLocalPlayer->SendFakeOnFootFullSyncData();
         Show(false);
    }
}

void CExtraKeyBoard::Render()
{
	if(!m_bIsActive) return;

	ImGuiIO &io = ImGui::GetIO();
    
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(8, 8));

    ImGui::Begin("> Select the button", nullptr, 
        ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);

    AddKeys();

    if(ImGui::Button("Close", ImVec2(350, 50)))
    {
         Show(false);
    }
    
    ImGui::SetWindowSize(ImVec2(-8, -8));
    ImVec2 size = ImGui::GetWindowSize();
    ImGui::SetWindowPos( ImVec2( ((io.DisplaySize.x - size.x)/2), ((io.DisplaySize.y - size.y)/2) ) );
    ImGui::End();
    ImGui::PopStyleVar();
}