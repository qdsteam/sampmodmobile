#include "main.h"
#include "game/game.h"
#include "net/netgame.h"
#include "game/common.h"
#include "gui/gui.h"
#include "servers.h"
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

extern CGUI *pGUI;
extern CGame *pGame;
extern CNetGame *pNetGame;
extern CKeyBoard *pKeyBoard;
extern CChatWindow *pChatWindow;
extern CSettings *pSettings;
extern CSetsWindow *pSetsWindow;
extern CModSAWindow *pModSAWindow;
extern CCustomServerWindow *pCustomServer;

char* AddressOne = ADDRZERO;
char* AddressTwo = ADDRONE;
char* AddressThree = ADDRTWO;

CServersWindow::CServersWindow()
{
	m_bIsActive = false;
    m_bMenuStep = 0;
}

CServersWindow::~CServersWindow()
{

}

void CServersWindow::Show(bool bShow)
{
	if(pGame) 
        pGame->FindPlayerPed()->TogglePlayerControllable(false);

	m_bIsActive = bShow;
}

void CServersWindow::Clear()
{
	m_bIsActive = false;
    m_bMenuStep = 0;
}

void CServersWindow::ShowAllServers()
{

    ImGui::StyleColorsClassic();

    ImGui::Text("Direct connection");

    if(ImGui::Button("Custom Server", ImVec2(350, 50)))
    {
         pCustomServer->Show(true);
         Show(false);
         pModSAWindow->extOS = 0;
    }

    ImGui::ItemSize( ImVec2(0, pGUI->GetFontSize()/2 + 5) );
    ImGui::Text("Official");

    if(ImGui::Button("Mordor RP", ImVec2(350, 50)))
    {
        unsigned short port = 7777;
        pModSAWindow->extOS = 0;

        pNetGame = new CNetGame( 
            AddressTwo,
            port, 
            pSetsWindow->username,
            pSetsWindow->password);
        Show(false);

        pModSAWindow->protect = 1;
        if(pGame) 
            pGame->FindPlayerPed()->TogglePlayerControllable(true);
    }

    if(ImGui::Button("SanTrope RP", ImVec2(350, 50)))
    {
        unsigned short port = 7777;
        pModSAWindow->extOS = 0;
        pModSAWindow->ToggleRPC(9); // pickups

        pNetGame = new CNetGame( 
            AddressThree,
            port, 
            pSetsWindow->username,
            pSetsWindow->password);
        Show(false);

        pModSAWindow->protect = 1;
        if(pGame) 
            pGame->FindPlayerPed()->TogglePlayerControllable(true);
    }

    ImGui::ItemSize( ImVec2(0, pGUI->GetFontSize()/2 + 5) );
    ImGui::Text("Internet");

    if(ImGui::Button("Axwell World", ImVec2(350, 50)))
    {
        unsigned short port = 7778;

        pModSAWindow->extOS = 1;

        pNetGame = new CNetGame( 
            AddressOne,
            port, 
            pSetsWindow->username,
            pSetsWindow->password);
        Show(false);
        pModSAWindow->protect = 0;

        if(pGame) 
            pGame->FindPlayerPed()->TogglePlayerControllable(true);
    }
}

void CServersWindow::Render()
{
	if(!m_bIsActive || m_bMenuStep == 0) return;

	ImGuiIO &io = ImGui::GetIO();

    ImGui::StyleColorsClassic();
    
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(8, 8));

    ImGui::Begin("> Select the server", nullptr, 
        ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);

    switch(m_bMenuStep){
        case 1:
            ShowAllServers();
        break;
    }
    
    ImGui::SetWindowSize(ImVec2(-8, -8));
    ImVec2 size = ImGui::GetWindowSize();
    ImGui::SetWindowPos( ImVec2( ((io.DisplaySize.x - size.x)/2), ((io.DisplaySize.y - size.y)/2) ) );
    ImGui::End();
    ImGui::PopStyleVar();
}