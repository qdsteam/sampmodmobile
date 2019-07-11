#include "main.h"
#include "game/game.h"
#include "net/netgame.h"
#include "gui/gui.h"
#include "vendor/imgui/imgui_internal.h"
#include "keyboard.h"
#include <stdlib.h>
#include "sets.h"
#include "servers.h"
#include "settings.h"
#include "customserver.h"
#include "chatwindow.h"
#include "modsa.h"
#include "vendor/inih/cpp/INIReader.h"
#include <string.h>

extern CGUI *pGUI;
extern CGame *pGame;
extern CNetGame *pNetGame;
extern CKeyBoard *pKeyBoard;
extern CServersWindow *pServersWindow;
extern CChatWindow *pChatWindow;
extern CSetsWindow *pSetsWindow;
extern CModSAWindow *pModSAWindow;
extern CSettings *pSettings;

char szIPInputBuffer[100];
char utf8IPInputBuffer[100*3];

char szPortInputBuffer[100];
char utf8PortInputBuffer[100*3];

CCustomServerWindow::CCustomServerWindow()
{
	m_bIsActive = false;
	m_bFixer = false;
	m_bFixer2 = false;
}

CCustomServerWindow::~CCustomServerWindow()
{

}

void CCustomServerWindow::Show(bool bShow)
{
	if(pGame) 
		pGame->FindPlayerPed()->TogglePlayerControllable(false);

	m_bIsActive = bShow;
	m_bFixer = false;
}

void CCustomServerWindow::Clear()
{
	m_bIsActive = false;
	m_bFixer = false;

	memset(szIPInputBuffer, 0, 100);
	memset(utf8IPInputBuffer, 0, 100*3);

	memset(szPortInputBuffer, 0, 100);
	memset(utf8PortInputBuffer, 0, 100*3);
}

void IPWindowInputHandler(const char* str)
{
	if(!str || *str == '\0') return;
	strcpy(szIPInputBuffer, str);
	cp1251_to_utf8(utf8IPInputBuffer, str);
}

void PortWindowInputHandler(const char* str)
{
	if(!str || *str == '\0') return;
	strcpy(szPortInputBuffer, str);
	cp1251_to_utf8(utf8PortInputBuffer, str);
}

void CCustomServerWindow::Render()
{
	if(!m_bIsActive) return;

	ImGuiIO &io = ImGui::GetIO();
	
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(8,8));

	ImGui::Begin("> Custom Server", nullptr, 
		ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoResize);

		ImGui::Text("IP Address:");

		if( ImGui::Button(utf8IPInputBuffer, ImVec2(555, 50) ))
		{
			pKeyBoard->Open(&IPWindowInputHandler);
		}

		ImGui::ItemSize( ImVec2(0, pGUI->GetFontSize()/2 + 5) );

		ImGui::Text("Port:");

		if( ImGui::Button(utf8PortInputBuffer, ImVec2(555, 50) ))
		{
			pKeyBoard->Open(&PortWindowInputHandler);
		}

		ImGui::ItemSize( ImVec2(0, pGUI->GetFontSize()/2 + 5) );

		if(m_bFixer == false)
		{
			if(ImGui::Button("Fix crash", ImVec2(165, 50)))
			{
				if(m_bFixer == true){
					m_bFixer = false;
				}else{
					m_bFixer = true;
				}
			}
		}else{
			if(ImGui::Button("(O) Fix crash", ImVec2(165, 50)))
			{
				if(m_bFixer == true){
					m_bFixer = false;
				}else{
					m_bFixer = true;
				}
			}
		}

		ImGui::SameLine(0, pGUI->GetFontSize());

		if(m_bFixer2 == false)
		{
			if(ImGui::Button("(O) Objects", ImVec2(165, 50)))
			{
				if(m_bFixer2 == true){
					m_bFixer2 = false;
				}else{
					m_bFixer2 = true;
				}
			}
		}else{
			if(ImGui::Button("Objects", ImVec2(165, 50)))
			{
				if(m_bFixer2 == true){
					m_bFixer2 = false;
				}else{
					m_bFixer2 = true;
				}
			}
		}

		ImGui::SameLine(0, pGUI->GetFontSize());

		if(pModSAWindow->m_bCTL == false)
		{
			if(ImGui::Button("(O) 3DTextLabel", ImVec2(165, 50)))
			{
				pModSAWindow->ToggleRPC(15);
			}
		}else{
			if(ImGui::Button("3DTextLabel", ImVec2(165, 50)))
			{
				pModSAWindow->ToggleRPC(15);
			}
		}

		ImGui::ItemSize( ImVec2(0, pGUI->GetFontSize()/2 + 5) );
		ImGui::SetCursorPosX((ImGui::GetWindowWidth() - 278 + ImGui::GetStyle().ItemSpacing.x) / 2);

		if(ImGui::Button("Connect", ImVec2(125, 50)))
		{
			address = szIPInputBuffer;
			char *po = szPortInputBuffer;
			port = atoi(po);
			
			pModSAWindow->protect = 0;

			if(m_bFixer)
			{
				pModSAWindow->ToggleRPC(3); // objects
				pModSAWindow->ToggleRPC(9); // pickups
				//pModSAWindow->ToggleRPC(15); // 3DTextLabel 
			} 

			pNetGame = new CNetGame(address, port, pSettings->Get().szNickName, pSettings->Get().szPassword);
			Show(false);
			
			if(pGame) 
            	pGame->FindPlayerPed()->TogglePlayerControllable(true);
		}

		ImGui::SameLine(0, pGUI->GetFontSize());
		
		if(ImGui::Button("Import", ImVec2(125, 50)))
		{
			pModSAWindow->protect = 0;

			sprintf(szIPInputBuffer, "%s", pSettings->Get().szHost);
			sprintf(utf8IPInputBuffer, "%s", pSettings->Get().szHost);

			sprintf(szPortInputBuffer, "%d", pSettings->Get().iPort);
			sprintf(utf8PortInputBuffer, "%d", pSettings->Get().iPort);
		}

	ImGui::SetWindowSize(ImVec2(-1, -1));
	ImVec2 size = ImGui::GetWindowSize();
	ImGui::SetWindowPos( ImVec2( ((io.DisplaySize.x - size.x)/2), ((io.DisplaySize.y - size.y)/2)) );
	ImGui::End();

	ImGui::PopStyleVar();
}