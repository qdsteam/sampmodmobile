#include "../main.h"
#include "gui.h"
#include "../game/game.h"
#include "../net/netgame.h"
#include "../game/RW/RenderWare.h"
#include "../chatwindow.h"
#include "../spawnscreen.h"
#include "../playertags.h"
#include "../dialog.h"
#include "../extrakeyboard.h"
#include "../keyboard.h"
#include "../debug.h"
#include "../settings.h"
#include "../modsa.h"
#include "../menu.h"
#include "../servers.h"
#include "../customserver.h"
#include "../sets.h"
#include "../textdraw.h"
#include "../playerslist.h"
#include "../skinchanger.h"
#include <time.h>
#include <ctime>
#include <stdio.h>
#include <string.h>

extern CModSAWindow *pModSAWindow;
extern CPlayersList *pPlayersList;
extern CSkinChanger *pSkinChanger;
extern CExtraKeyBoard *pExtraKeyBoard;
extern CServersWindow *pServersWindow;
extern CSetsWindow *pSetsWindow;
extern CCustomServerWindow *pCustomServer;

extern CSpawnScreen *pSpawnScreen;
extern CPlayerTags *pPlayerTags;
extern CDialogWindow *pDialogWindow;
extern CMenu *pMenu;
extern CTextDraw *pTextDraw;
extern CDebug *pDebug;
extern CChatWindow *pChatWindow;
extern CSettings *pSettings;
extern CKeyBoard *pKeyBoard;
extern CNetGame *pNetGame;
extern CGame *pGame;

/* imgui_impl_renderware.h */
void ImGui_ImplRenderWare_RenderDrawData(ImDrawData* draw_data);
bool ImGui_ImplRenderWare_Init();
void ImGui_ImplRenderWare_NewFrame();
void ImGui_ImplRenderWare_ShutDown();

/*
	Все координаты GUI-элементов задаются
	относительно разрешения 1920x1080
*/
#define MULT_X	0.00052083333f	// 1/1920
#define MULT_Y	0.00092592592f 	// 1/1080

CGUI::CGUI()
{
	Log("Initializing GUI..");

	// setup ImGUI
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO &io = ImGui::GetIO();

	ImGui_ImplRenderWare_Init();

	// scale
	m_vecScale.x = io.DisplaySize.x * MULT_X;
	m_vecScale.y = io.DisplaySize.y * MULT_Y;
	// font Size
	m_fFontSize = ScaleY( pSettings->Get().fFontSize );

	m_fCheatsBoxPosX = ScaleX( pSettings->Get().fCheatsBoxWidth );
	m_fCheatsBoxPosY = ScaleY( pSettings->Get().fCheatsBoxHeight );

	m_fCheatsBox = (bool)pSettings->Get().fCheatsBox;

	// mouse/touch
	m_bMousePressed = false;
	m_vecMousePos = ImVec2(0, 0);

	Log("GUI | Scale factor: %f, %f Font size: %f", m_vecScale.x, m_vecScale.y, m_fFontSize);

	// setup style
	ImGuiStyle& style = ImGui::GetStyle();
	style.ScrollbarSize = ScaleY(35.0f);
	style.WindowBorderSize = 0.0f;
	ImGui::StyleColorsClassic();


	// load fonts
	char path[0xFF];
	sprintf(path, "%sSAMP/fonts/%s", g_pszStorage, pSettings->Get().szFont);
	// cp1251 ranges
	static const ImWchar ranges[] = 
	{
		0x0020, 0x0080,
		0x00A0, 0x00C0,
		0x0400, 0x0460,
		0x0490, 0x04A0,
		0x2010, 0x2040,
		0x20A0, 0x20B0,
		0x2110, 0x2130,
		0
	};
	Log("GUI | Loading font: %s", pSettings->Get().szFont);
	m_pFont = io.Fonts->AddFontFromFileTTF(path, m_fFontSize, nullptr, ranges);
	Log("GUI | ImFont pointer = 0x%X", m_pFont);
}

CGUI::~CGUI()
{
	ImGui_ImplRenderWare_ShutDown();
	ImGui::DestroyContext();
}

void CGUI::Render()
{
	ImGuiIO& io = ImGui::GetIO();

	ImGui_ImplRenderWare_NewFrame();
	ImGui::NewFrame();

	if(pPlayerTags) pPlayerTags->Render();
	
	if(pNetGame && pNetGame->GetLabelPool())
	{
		pNetGame->GetLabelPool()->Draw();
	}

	if(pChatWindow) 
		pChatWindow->Render();

	if(pExtraKeyBoard) 
		pExtraKeyBoard->Render();
	if(pMenu && pMenu->m_bEnabled) 
		pMenu->Render();
	if(pTextDraw && pTextDraw->m_bIsActive) 
		pTextDraw->Render();
	if(pDialogWindow && pDialogWindow->m_bIsActive) 
		pDialogWindow->Render();
	if(pModSAWindow && pModSAWindow->m_bIsActive) 
		pModSAWindow->Render();
	if(pSkinChanger && pSkinChanger->m_bIsActive)
		pSkinChanger->Render();
	if(pPlayersList && pPlayersList->m_bIsActive)
		pPlayersList->Render();

	if(m_fCheatsBox) RenderCheatBox();

	if(pCustomServer && !pNetGame) 
		pCustomServer->Render();

	if(pSpawnScreen) 
		pSpawnScreen->Render();
	if(pKeyBoard) 
		pKeyBoard->Render();
	
	ImGui::EndFrame();
	ImGui::Render();
	ImGui_ImplRenderWare_RenderDrawData(ImGui::GetDrawData());

	if(m_bNeedClearMousePos)
	{
		io.MousePos = ImVec2(-1, -1);
		m_bNeedClearMousePos = false;
	}
}

bool CGUI::OnTouchEvent(int type, bool multi, int x, int y)
{
	ImGuiIO& io = ImGui::GetIO();

	if(!pKeyBoard->OnTouchEvent(type, multi, x, y)) return false;
	if(!pChatWindow->OnTouchEvent(type, multi, x, y)) return false;

	switch(type)
	{
		case TOUCH_PUSH:
		io.MousePos = ImVec2(x, y);
		io.MouseDown[0] = true;

		if((x >= m_fCheatsBoxPosX && y >= m_fCheatsBoxPosY) && (x <= m_fCheatsBoxPosX + 80 && y <= m_fCheatsBoxPosY + 120))
		{
			if(pNetGame && pNetGame->GetGameState() == GAMESTATE_CONNECTED)
			{
				pModSAWindow->m_bMenuStep = 1;
				pModSAWindow->Show(true);
			}
		}
		break;

		case TOUCH_POP:
		io.MouseDown[0] = false;
		m_bNeedClearMousePos = true;
		break;

		case TOUCH_MOVE:
		io.MousePos = ImVec2(x, y);
		break;
	}

	return true;
}

void CGUI::RenderCheatBox()
{
	char buffer[80];
	time_t seconds = time(NULL);
	tm* timeinfo = localtime(&seconds);
	char* format = "[%I:%M:%S]";
	strftime(buffer, 80, format, timeinfo);

	MATRIX4X4 mat;
    pGame->FindPlayerPed()->GetMatrix(&mat);
	float x = mat.pos.X;
	float y = mat.pos.Y;
	float z = mat.pos.Z;

   	char str[4096];
   	if(m_xyz == 1) sprintf(str, "%s\n(X: %f Y: %f Z: %f)\n", buffer, x, y, z);
   		else sprintf(str, "%s\n", buffer);

   	if(m_gm == 1)strcat(str, "   - Invincible\n");
   	if(m_fz == 1)strcat(str, "   - Freeze\n");
   	if(m_Airbreak == 1)strcat(str, "   - Air Break\n");
   	if(m_nf == 1)strcat(str, "   - NoFall\n");
   	if(m_INVIS == 1)strcat(str, "   - Invisible\n");
   	if(m_FLASH == 1)strcat(str, "   - Flash\n");
   	if(m_wh == 1)strcat(str, "   - WallHack\n");
   	if(m_fly == 1)strcat(str, "   - Fly\n");
   	if(m_bd == 1)strcat(str, "   - Behind\n");
   	if(m_gravity == 1)strcat(str, "   - Gravity\n");

   	float cbX, cbY;

   	cbX = m_fCheatsBoxPosX;
   	cbY = m_fCheatsBoxPosY;

   	int rCol1 = 248; //(rand() % 248 +240);
   	int rCol2 = 110; // (rand() % 115 +110);
   	int rCol3 = 5; //(rand() % 5 +1);

   	ImGui::GetBackgroundDrawList()->AddText(
		ImVec2((cbX + 1.4) + (0.75 * 3.25), (cbY + 1.5)), 
		ImColor(0,0,0,255), str);
	ImGui::GetBackgroundDrawList()->AddText(
		ImVec2((cbX + 1.4) + (0.75 * 3.25), (cbY - 0.5)), 
		ImColor(0,0,0,255), str);	
	ImGui::GetBackgroundDrawList()->AddText(
		ImVec2((cbX - 0.6) + (0.75 * 3.25), (cbY - 0.5)), 
		ImColor(0,0,0,255), str);
	ImGui::GetBackgroundDrawList()->AddText(
		ImVec2((cbX - 0.6) + (0.75 * 3.25), (cbY + 1.5)), 
		ImColor(0,0,0,255), str);
	ImGui::GetBackgroundDrawList()->AddText(
		ImVec2(cbX + (0.75 * 3.25), cbY), 
		ImColor(rCol1,rCol2,rCol3,255), str);
}

void CGUI::RenderRakNetStatistics()
{
		// StatisticsToString(rss, message, 0);

		//ImGui::GetOverlayDrawList()->AddText(
		//	ImVec2(ScaleX(10), ScaleY(400)),
		//	ImColor(IM_COL32_BLACK), message);
}

void CGUI::RenderText(ImVec2& posCur, ImU32 col, bool bOutline, const char* text_begin, const char* text_end)
{
	int iOffset = pSettings->Get().iFontOutline;

	if(bOutline)
	{
		posCur.x -= iOffset;
		ImGui::GetBackgroundDrawList()->AddText(posCur, ImColor(IM_COL32_BLACK), text_begin, text_end);
		posCur.x += iOffset;
		// right 
		posCur.x += iOffset;
		ImGui::GetBackgroundDrawList()->AddText(posCur, ImColor(IM_COL32_BLACK), text_begin, text_end);
		posCur.x -= iOffset;
		// above
		posCur.y -= iOffset;
		ImGui::GetBackgroundDrawList()->AddText(posCur, ImColor(IM_COL32_BLACK), text_begin, text_end);
		posCur.y += iOffset;
		// below
		posCur.y += iOffset;
		ImGui::GetBackgroundDrawList()->AddText(posCur, ImColor(IM_COL32_BLACK), text_begin, text_end);
		posCur.y -= iOffset;
	}

	ImGui::GetBackgroundDrawList()->AddText(posCur, col, text_begin, text_end);
}
