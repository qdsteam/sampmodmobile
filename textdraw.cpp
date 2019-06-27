#include "main.h"
#include "game/game.h"
#include "net/netgame.h"
#include "gui/gui.h"
#include "vendor/imgui/imgui_internal.h"
#include "keyboard.h"
#include <stdlib.h>
#include <string.h>
#include "textdraw.h"
#include "settings.h"
#include "timer.hpp"

extern CGUI *pGUI;
extern CGame *pGame;
extern CNetGame *pNetGame;
extern CKeyBoard *pKeyBoard;
extern CSettings *pSettings;

char szItemIdInputBuffer[100];
char utf8ItemIdInputBuffer[100*3];

CTextDraw::CTextDraw()
{
	m_bIsActive = false;
	tdStorage = "";
}

CTextDraw::~CTextDraw()
{

}

void CTextDraw::Show(bool bShow)
{
	m_bIsActive = bShow;
}

void CTextDraw::Clear()
{
	m_bIsActive = false;
	tdStorage = "";

	memset(szItemIdInputBuffer, 0, 100);
	memset(utf8ItemIdInputBuffer, 0, 100*3);
}

void ItemIdWindowInputHandler(const char* str)
{
	if(!str || *str == '\0') return;
	strcpy(szItemIdInputBuffer, str);
	cp1251_to_utf8(utf8ItemIdInputBuffer, str);
}

void CTextDraw::StoreTD(uint16_t wTextID)
{
	wtID = wTextID;
}

void CTextDraw::Render()
{
	if(!m_bIsActive) return;

	ImGuiIO &io = ImGui::GetIO();

	ImGui::StyleColorsClassic();

	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(8,8));

	ImGui::Begin("> TextDraw", nullptr, 
		ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoResize);

	char str[4096];
	CPlayerPool *pPlayerPool = pNetGame->GetPlayerPool();
	CLocalPlayer *pLocalPlayer = 0;
	if(pPlayerPool) pLocalPlayer = pPlayerPool->GetLocalPlayer();

	if( ImGui::Button(utf8ItemIdInputBuffer, ImVec2(200, 45) ))
	{
		pKeyBoard->Open(&ItemIdWindowInputHandler);
	}

	ImGui::ItemSize( ImVec2(0, pGUI->GetFontSize()/2 + 5) );

	if(ImGui::Button("Send", ImVec2(200, 50)))
	{
		char *id = szItemIdInputBuffer;
		int tid = atoi(id);

		pLocalPlayer->SendTextDrawClick(tid);
	}

	if(ImGui::Button("Close", ImVec2(200, 50)))
	{
		Show(false);
	}

	ImGui::SetWindowSize(ImVec2(-1, -1));
	ImVec2 size = ImGui::GetWindowSize();
	ImGui::SetWindowPos( ImVec2( ((io.DisplaySize.x - size.x + 435)/2), ((io.DisplaySize.y - size.y)/2)) );
	ImGui::End();

	ImGui::PopStyleVar();
}