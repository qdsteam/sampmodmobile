#include "main.h"
#include "game/game.h"
#include "net/netgame.h"
#include "gui/gui.h"
#include "vendor/imgui/imgui_internal.h"
#include "keyboard.h"
#include "shpora.h"

#include <stdlib.h>
#include <string.h>

extern CGUI *pGUI;
extern CGame *pGame;
extern CNetGame *pNetGame;
extern CKeyBoard *pKeyBoard;

CShpora::CShpora()
{
	m_bIsActive = false;
	step = 0;
}

CShpora::~CShpora()
{

}

void CShpora::Show(bool bShow)
{
	if(pGame) 
		pGame->FindPlayerPed()->TogglePlayerControllable(!bShow);

	m_bIsActive = bShow;
}

void CShpora::Clear()
{
	m_bIsActive = false;
	step = 0;
}

void CShpora::Render()
{
	if(!m_bIsActive) return;

	ImGuiIO &io = ImGui::GetIO();

	ImGui::StyleColorsClassic();

	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(8,8));

	ImGui::Begin("shpora", nullptr, 
		ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoResize);

	if(ImGui::Button("Close", ImVec2(125, 50)))
	{
		step = 0;
		Show(false);
	}
	ImGui::SetWindowSize(ImVec2(-1, -1));
	ImVec2 size = ImGui::GetWindowSize();
	ImGui::SetWindowPos( ImVec2( ((io.DisplaySize.x - size.x)/2), ((io.DisplaySize.y - size.y)/2)) );
	ImGui::End();

	ImGui::PopStyleVar();
}