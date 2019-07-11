#include <string.h>
#include <stdlib.h>

#include "main.h"
#include "game/game.h"
#include "net/netgame.h"
#include "gui/gui.h"
#include "vendor/imgui/imgui_internal.h"
#include "keyboard.h"
#include "skinchanger.h"
#include "chatwindow.h"
#include "modsa.h"
#include "vendor/inih/cpp/INIReader.h"

extern CGUI *pGUI;
extern CGame *pGame;
extern CNetGame *pNetGame;
extern CKeyBoard *pKeyBoard;
extern CChatWindow *pChatWindow;
extern CModSAWindow *pModSAWindow;

char szSkinIDInputBuffer[100];
char utf8SkinIDInputBuffer[100*3];

CSkinChanger::CSkinChanger()
{
	m_bIsActive = false;
}

CSkinChanger::~CSkinChanger()
{

}

void CSkinChanger::Show(bool bShow)
{
	if(pGame) 
		pGame->FindPlayerPed()->TogglePlayerControllable(!bShow);

	m_bIsActive = bShow;
}

void CSkinChanger::Clear()
{
	m_bIsActive = false;

	memset(szSkinIDInputBuffer, 0, 100);
	memset(utf8SkinIDInputBuffer, 0, 100*3);
}

void SkinIDWindowInputHandler(const char* str)
{
	if(!str || *str == '\0') return;
	strcpy(szSkinIDInputBuffer, str);
	cp1251_to_utf8(utf8SkinIDInputBuffer, str);
}

void CSkinChanger::Render()
{
	if(!m_bIsActive) return;

	ImGuiIO &io = ImGui::GetIO();

	ImGui::StyleColorsClassic();
	
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(8,8));

	ImGui::Begin("> Skin Changer", nullptr, 
		ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoResize);

		ImGui::Text("Enter the skin ID");

		if( ImGui::Button(utf8SkinIDInputBuffer, ImVec2(555, 50) ))
		{
			if(!pKeyBoard->IsOpen())
				pKeyBoard->Open(&SkinIDWindowInputHandler);
		}

		ImGui::ItemSize( ImVec2(0, pGUI->GetFontSize()/2 + 5) );

		ImGui::SetCursorPosX((ImGui::GetWindowWidth() - 278 + ImGui::GetStyle().ItemSpacing.x) / 2);

		if(ImGui::Button("Apply", ImVec2(125, 50)))
		{
			char *strskinid = szSkinIDInputBuffer;
			unsigned int skinid = atoi(strskinid);

			//if(pModSAWindow->protect != 1)
			//{
			//	pGame->FindPlayerPed()->SetModelIndex(skinid);
			//}else{
				if(skinid != 0 && skinid != 99 && skinid != 92) pGame->FindPlayerPed()->SetModelIndex(skinid);
					else pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}You can not use this skin!");
			//}
			
			Show(false);
		}

		ImGui::SameLine(0, pGUI->GetFontSize());
		
		if(ImGui::Button("Cancel", ImVec2(125, 50)))
		{
			Show(false);
		}

	ImGui::SetWindowSize(ImVec2(-1, -1));
	ImVec2 size = ImGui::GetWindowSize();
	ImGui::SetWindowPos( ImVec2( ((io.DisplaySize.x - size.x)/2), ((io.DisplaySize.y - size.y)/2)) );
	ImGui::End();

	ImGui::PopStyleVar();
}