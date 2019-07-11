#include "main.h"
#include "game/game.h"
#include "net/netgame.h"
#include "gui/gui.h"
#include "vendor/imgui/imgui_internal.h"
#include "keyboard.h"
#include "sets.h"
#include "servers.h"
#include "settings.h"
#include "modsa.h"

#include <stdlib.h>
#include <string.h>

extern CGUI *pGUI;
extern CGame *pGame;
extern CNetGame *pNetGame;
extern CKeyBoard *pKeyBoard;
extern CServersWindow *pServersWindow;
extern CSettings *pSettings;
extern CModSAWindow *pModSAWindow;

char szUsernameInputBuffer[100];
char utf8UsernameInputBuffer[100*3];

char szPasswordInputBuffer[100];
char utf8PasswordInputBuffer[100*3];

CSetsWindow::CSetsWindow()
{
	m_bIsActive = false;
}

CSetsWindow::~CSetsWindow()
{

}

void CSetsWindow::Show(bool bShow)
{
	if(pGame) 
		pGame->FindPlayerPed()->TogglePlayerControllable(false);

	m_bIsActive = bShow;

	if(bShow != false) 
	{
		sprintf(utf8UsernameInputBuffer, "%s", pSettings->Get().szNickName);
		sprintf(szUsernameInputBuffer, "%s", pSettings->Get().szNickName);
	}
}

void CSetsWindow::Clear()
{
	m_bIsActive = false;

	memset(szUsernameInputBuffer, 0, 100);
	memset(utf8UsernameInputBuffer, 0, 100*3);

	memset(szPasswordInputBuffer, 0, 100);
	memset(utf8PasswordInputBuffer, 0, 100*3);
}

void SetsWindowInputHandler(const char* str)
{
	if(!str || *str == '\0') return;
	strcpy(szUsernameInputBuffer, str);
	cp1251_to_utf8(utf8UsernameInputBuffer, str);
}

void SetsWindowInputHandlerTwo(const char* str)
{
	if(!str || *str == '\0') return;
	strcpy(szPasswordInputBuffer, str);
	cp1251_to_utf8(utf8PasswordInputBuffer, str);
}

void CSetsWindow::Render()
{
	if(!m_bIsActive) return;

	ImGuiIO &io = ImGui::GetIO();

	ImGui::StyleColorsClassic();

	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(8,8));

	ImGui::Begin("> Server Properties", nullptr, 
		ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoResize);

		ImGui::Text("Введите свой игровой никнейм");

		ImGui::ItemSize( ImVec2(0, pGUI->GetFontSize()/2 + 2.5) );

		if( ImGui::Button(utf8UsernameInputBuffer, ImVec2((555 - 125), 50) ))
		{
			pKeyBoard->Open(&SetsWindowInputHandler);
		}

		ImGui::SameLine(0, pGUI->GetFontSize() - 10.5);
		
		if(ImGui::Button("Импорт", ImVec2(125, 50)))
		{
			sprintf(utf8UsernameInputBuffer, "%s", pSettings->Get().szNickName);
			sprintf(szUsernameInputBuffer, "%s", pSettings->Get().szNickName);
		}

		ImGui::ItemSize( ImVec2(0, pGUI->GetFontSize()/2 + 5) );
		
		ImGui::SetCursorPosX((ImGui::GetWindowWidth() - 278 + ImGui::GetStyle().ItemSpacing.x) / 2);

		if(ImGui::Button("Далее", ImVec2(125, 50)))
		{
			if(strlen(utf8UsernameInputBuffer) >= 3)
			{
				username = szUsernameInputBuffer;
				password = szPasswordInputBuffer;
				
				unsigned short port = 7777;
        		pModSAWindow->extOS = 0;
	
        		char *address = ADDRFOUR;//ADDRLOC;
	
        		pNetGame = new CNetGame(address, port, username, password);
	
        		Show(false);
	
        		pModSAWindow->protect = 1;
        		if(pGame) 
        		    pGame->FindPlayerPed()->TogglePlayerControllable(true);
        	}else{
        		sprintf(utf8UsernameInputBuffer, "%s", pSettings->Get().szNickName);
				sprintf(szUsernameInputBuffer, "%s", pSettings->Get().szNickName);
				username = szUsernameInputBuffer;
				password = szPasswordInputBuffer;
				
				unsigned short port = 7777;
        		pModSAWindow->extOS = 0;
	
        		char *address = ADDRFOUR;
	
        		pNetGame = new CNetGame(address, port, username, password);
	
        		Show(false);
	
        		pModSAWindow->protect = 1;
        		if(pGame) 
        		    pGame->FindPlayerPed()->TogglePlayerControllable(true);
        	}
		}

		ImGui::SameLine(0, pGUI->GetFontSize());
		
		if(ImGui::Button("Выйти", ImVec2(125, 50)))
		{
			exit(0);
		}

	ImGui::SetWindowSize(ImVec2(-1, -1));
	ImVec2 size = ImGui::GetWindowSize();
	ImGui::SetWindowPos( ImVec2( ((io.DisplaySize.x - size.x)/2), ((io.DisplaySize.y - size.y)/2)) );
	ImGui::End();

	ImGui::PopStyleVar();
}