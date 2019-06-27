#include "main.h"
#include "game/game.h"
#include "net/netgame.h"
#include "gui/gui.h"
#include "dialog.h"
#include "vendor/imgui/imgui_internal.h"
#include "keyboard.h"
#include <stdlib.h>
#include <string.h>
#include "modsa.h"

extern CGUI *pGUI;
extern CGame *pGame;
extern CNetGame *pNetGame;
extern CKeyBoard *pKeyBoard;
extern CModSAWindow *pModSAWindow;

char szDialogInputBuffer[100];
char utf8DialogInputBuffer[100*3];

CDialogWindow::CDialogWindow()
{
	m_bIsActive = false;
	m_putf8Info = nullptr;
	m_pszInfo = nullptr;
	passEntering = 0;

	if(m_bSL != 1)
		m_bSL = 0;
}

CDialogWindow::~CDialogWindow()
{

}

void CDialogWindow::Show(bool bShow)
{
	if(pModSAWindow->m_bSD == 1)return;
	if(pGame) 
		pGame->FindPlayerPed()->TogglePlayerControllable(!bShow);

	m_bIsActive = bShow;
}

void CDialogWindow::Clear()
{
	if(m_putf8Info)
	{
		free(m_putf8Info);
		m_putf8Info = nullptr;
	}

	if(m_pszInfo)
	{
		free(m_pszInfo);
		m_pszInfo = nullptr;
	}

	m_bIsActive = false;
	m_byteDialogStyle = 0;
	m_wDialogID = -1;
	m_utf8Title[0] = 0;
	m_utf8Button1[0] = 0;
	m_utf8Button2[0] = 0;
	passEntering = 0;

	m_fSizeX = -1.0f;
	m_fSizeY = -1.0f;

	memset(szDialogInputBuffer, 0, 100);
	memset(utf8DialogInputBuffer, 0, 100*3);
}

void CDialogWindow::SetInfo(char* szInfo, int length)
{
	if(!szInfo || !length) return;

	if(m_putf8Info)
	{
		free(m_putf8Info);
		m_putf8Info = nullptr;
	}

	if(m_pszInfo)
	{
		free(m_pszInfo);
		m_pszInfo = nullptr;
	}

	m_putf8Info = (char*)malloc((length * 3) + 1);
	if(!m_putf8Info)
	{
		Log("CDialog::SetInfo: can't allocate memory");
		return;
	}

	m_pszInfo = (char*)malloc((length * 3) + 1);
	if(!m_pszInfo)
	{
		Log("CDialog::SetInfo: can't allocate memory");
		return;
	}

	cp1251_to_utf8(m_putf8Info, szInfo);

	// =========
	char szNonColorEmbeddedMsg[4200];
	int iNonColorEmbeddedMsgLen = 0;

	for (size_t pos = 0; pos < strlen(szInfo) && szInfo[pos] != '\0'; pos++)
	{
		if(pos+7 < strlen(szInfo))
		{
			if (szInfo[pos] == '{' && szInfo[pos+7] == '}')
			{
				pos += 7;
				continue;
			}
		}

		szNonColorEmbeddedMsg[iNonColorEmbeddedMsgLen] = szInfo[pos];
		iNonColorEmbeddedMsgLen++;
	}

	szNonColorEmbeddedMsg[iNonColorEmbeddedMsgLen] = 0;
	// ========

	cp1251_to_utf8(m_pszInfo, szNonColorEmbeddedMsg);
}

bool ProcessInlineHexColor(const char* start, const char* end, ImVec4& color);

void TextWithColors(const char* fmt, ...)
{
	char tempStr[4096];

	va_list argPtr;
	va_start(argPtr, fmt);
	vsnprintf(tempStr, sizeof(tempStr), fmt, argPtr);
	va_end(argPtr);
	tempStr[sizeof(tempStr) - 1] = '\0';

	bool pushedColorStyle = false;
	const char* textStart = tempStr;
	const char* textCur = tempStr;
	while(textCur < (tempStr + sizeof(tempStr)) && *textCur != '\0')
	{
		if (*textCur == '{')
		{
			// Print accumulated text
			if (textCur != textStart)
			{
				ImGui::TextUnformatted(textStart, textCur);
				ImGui::SameLine(0.0f, 0.0f);
			}

			// Process color code
			const char* colorStart = textCur + 1;
			do
			{
				++textCur;
			} while (*textCur != '\0' && *textCur != '}');

			// Change color
			if (pushedColorStyle)
			{
				ImGui::PopStyleColor();
				pushedColorStyle = false;
			}

			ImVec4 textColor;
			if (ProcessInlineHexColor(colorStart, textCur, textColor))
			{
				ImGui::PushStyleColor(ImGuiCol_Text, textColor);
				pushedColorStyle = true;
			}

			textStart = textCur + 1;
		}
		else if (*textCur == '\n')
		{
			// Print accumulated text an go to next line
			ImGui::TextUnformatted(textStart, textCur);
			textStart = textCur + 1;
		}

		++textCur;
	}

	if (textCur != textStart)
		ImGui::TextUnformatted(textStart, textCur);
	else
		ImGui::NewLine();

	if(pushedColorStyle)
		ImGui::PopStyleColor();
}

void DialogWindowInputHandler(const char* str)
{
	if(!str || *str == '\0') return;
	strcpy(szDialogInputBuffer, str);
	cp1251_to_utf8(utf8DialogInputBuffer, str);
}


void CDialogWindow::ShowListItemsWithHeader()
{
	char bufString[4096];
    strcpy(bufString, m_putf8Info);
    char *str = bufString;
    char *pch;
    int i = -1;
    pch = strtok (str, "\n");
    while (pch != NULL)
    {
        i++;
        char ifdd[16];
        if(i == NULL) sprintf(ifdd, "%s", pch); 
        	else sprintf(ifdd, "%d. %s", i - 1, pch);
        TextWithColors(ifdd);

       	char item_id[16];
        sprintf(item_id, "Item #%d", i - 1);
        
        if(i != NULL && ImGui::Button(item_id, ImVec2(350, 50)))
        {
            Show(false);
            char enss[16] = "%d";
            sprintf(enss, "%d", i);
            if(pNetGame)
                pNetGame->SendDialogResponse(m_wDialogID, 1, i - 1, enss);
        }
    pch = strtok (NULL, "\n");
    }
}

void CDialogWindow::ShowListInfoWithHeader()
{
	char bufString[4096];
    strcpy(bufString, m_putf8Info);
    char *str = bufString;
    char *pch;
    int i = -1;
    pch = strtok (str, "\n");
    while (pch != NULL)
    {
        i++;
        if(i > 8)m_bSL = 1;
        if(i <= 8)m_bSL = 0;
        TextWithColors(pch);
   		pch = strtok (NULL, "\n");
    }
}

void CDialogWindow::ShowListItems()
{
	char bufString[4096];
    strcpy(bufString, m_putf8Info);
    char *str = bufString;
    char *pch;
    int i = -1;
    pch = strtok (str, "\n");
    while (pch != NULL)
    {
        i++;
        char ifdd[16];
        sprintf(ifdd, "%d. %s", i + 1, pch);
        TextWithColors(ifdd);

        if(i == NULL && ImGui::Button("Item #1", ImVec2(350, 50)))
        {
            Show(false);
            char enss[16];
            sprintf(enss, "Item %d", i);
            if(pNetGame)
                pNetGame->SendDialogResponse(m_wDialogID, 1, i, enss);
        }

       	char item_id[16];
        sprintf(item_id, "Item #%d", i + 1);
        
        if(i != NULL && ImGui::Button(item_id, ImVec2(350, 50)))
        {
            Show(false);
            char enss[16] = "%d";
            sprintf(enss, "%d", i);
            if(pNetGame)
                pNetGame->SendDialogResponse(m_wDialogID, 1, i, enss);
        }
    pch = strtok (NULL, "\n");
    }
}

void CDialogWindow::ShowListInfo()
{
	char bufString[4096];
    strcpy(bufString, m_putf8Info);
    char *str = bufString;
    char *pch;
    int i = -1;
    pch = strtok (str, "\n");
    while (pch != NULL)
    {
        i++;
        if(i > 8)m_bSL = 1;
        if(i <= 8)m_bSL = 0;
        TextWithColors(pch);
   		pch = strtok (NULL, "\n");
    }
}

void CDialogWindow::GetListItemsCount()
{
	char bufString[4096];
    strcpy(bufString, m_putf8Info);
    char *str = bufString;
    char *pch;
    int i = -1;
    pch = strtok (str, "\n");
    while (pch != NULL)
    {
        i++;
        if(i > 8)m_bSL = 1;
        if(i <= 8)m_bSL = 0;
   		pch = strtok (NULL, "\n");
    }
}

void CDialogWindow::Render()
{
	if(!m_bIsActive || !m_putf8Info) return;

	ImGuiIO &io = ImGui::GetIO();

	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(8, 8));

	ImGui::Begin("dialog_title", nullptr, 
		ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoResize);
	TextWithColors(m_utf8Title);

	ImGui::ItemSize( ImVec2(0, pGUI->GetFontSize()/2 + 2.75) );
	switch(m_byteDialogStyle)
	{
		case DIALOG_STYLE_MSGBOX:
		TextWithColors(m_putf8Info);
		ImGui::ItemSize( ImVec2(0, pGUI->GetFontSize()/2 + 50) );
		break;

		case DIALOG_STYLE_PASSWORD:
		TextWithColors(m_putf8Info);
		ImGui::ItemSize( ImVec2(0, pGUI->GetFontSize()/2 + 10) );

		int passStrLen;
		passStrLen = strlen(utf8DialogInputBuffer);

		if(passStrLen != 0)
		{
			if( ImGui::Button("********", ImVec2(ImGui::CalcTextSize(m_putf8Info).x, 45) ))
			{
				if(!pKeyBoard->IsOpen())
					pKeyBoard->Open(&DialogWindowInputHandler);
			}
		}else{
			if( ImGui::Button("", ImVec2(ImGui::CalcTextSize(m_putf8Info).x, 45) ))
			{
				if(!pKeyBoard->IsOpen())
					pKeyBoard->Open(&DialogWindowInputHandler);
			}
		}

		passEntering = 1;
		
		ImGui::ItemSize( ImVec2(0, pGUI->GetFontSize()/2 + 5) );
		break;

		case DIALOG_STYLE_INPUT:
		TextWithColors(m_putf8Info);
		ImGui::ItemSize( ImVec2(0, pGUI->GetFontSize()/2 + 10) );
		if( ImGui::Button(utf8DialogInputBuffer, ImVec2(ImGui::CalcTextSize(m_putf8Info).x, 45) ))
		{
			if(!pKeyBoard->IsOpen())
				pKeyBoard->Open(&DialogWindowInputHandler);
		}
		ImGui::ItemSize( ImVec2(0, pGUI->GetFontSize()/2 + 5) );
		break;

		case DIALOG_STYLE_TABLIST_HEADERS:
		GetListItemsCount();
		if(m_bSL != 1){
			ImGui::SetCursorPosY(36.75);
			ImGui::BeginChild("infobox", ImVec2(385, ImGui::GetWindowHeight() / 2 + 67.5), true, 
				ImGuiWindowFlags_AlwaysUseWindowPadding | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_AlwaysAutoResize);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(7, 7));
			ImGui::Begin("itembox", nullptr, 
				ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_HorizontalScrollbar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove);
			ShowListItemsWithHeader();
			ImGui::SetWindowSize(ImVec2(-1, -1));
			ImVec2 size = ImGui::GetWindowSize();
			ImGui::SetWindowPos( ImVec2( ((io.DisplaySize.x - size.x + 435)/2), ((io.DisplaySize.y - size.y)/2)) );
			ImGui::End();
			ShowListInfoWithHeader();
			ImGui::ItemSize( ImVec2(285, 155) );
			ImGui::EndChild();
		}else{
			ImGui::SetCursorPosY(36.75);
			ImGui::BeginChild("infobox", ImVec2(385, ImGui::GetWindowHeight() / 2 + 67.5), true, 
				ImGuiWindowFlags_AlwaysUseWindowPadding | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_AlwaysAutoResize);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(7, 7));
			ImGui::Begin("itembox", nullptr, 
				ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_HorizontalScrollbar);
			ShowListItemsWithHeader();
			ImGui::SetWindowSize(ImVec2(-1, -1));
			ImVec2 size = ImGui::GetWindowSize();
			ImGui::SetWindowPos( ImVec2( ((io.DisplaySize.x - size.x + 435)/2), ((io.DisplaySize.y - size.y)/2)) );
			ImGui::End();
			ShowListInfoWithHeader();
			ImGui::ItemSize( ImVec2(285, 155) );
			ImGui::EndChild();
		}
		break;

		case DIALOG_STYLE_TABLIST:
		case DIALOG_STYLE_LIST:
		GetListItemsCount();
		if(m_bSL != 1){
			ImGui::SetCursorPosY(36.75);
			ImGui::BeginChild("listinfo", ImVec2(385, ImGui::GetWindowHeight() / 2 + 67.5), true, 
				ImGuiWindowFlags_AlwaysUseWindowPadding | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_AlwaysAutoResize);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(7, 7));
			ImGui::Begin("listitems", nullptr, 
				ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_HorizontalScrollbar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove);
			ShowListItems();
			ImGui::SetWindowSize(ImVec2(-1, -1));
			ImVec2 size = ImGui::GetWindowSize();
			ImGui::SetWindowPos( ImVec2( ((io.DisplaySize.x - size.x + 435)/2), ((io.DisplaySize.y - size.y)/2)) );
			ImGui::End();
			ShowListInfo();
			//ImGui::SetScrollHere();
			ImGui::ItemSize( ImVec2(285, 155) );
			ImGui::EndChild();
		}else{
			ImGui::SetCursorPosY(36.75);
			ImGui::BeginChild("listinfo", ImVec2(385, ImGui::GetWindowHeight() / 2 + 67.5), true, 
				ImGuiWindowFlags_AlwaysUseWindowPadding | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_AlwaysAutoResize);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(7, 7));
			ImGui::Begin("listitems", nullptr, 
				ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_HorizontalScrollbar);
			ShowListItems();
			//ImGui::SetScrollHere();
			ImGui::SetWindowSize(ImVec2(-1, -1));
			ImVec2 size = ImGui::GetWindowSize();
			ImGui::SetWindowPos( ImVec2( ((io.DisplaySize.x - size.x + 435)/2), ((io.DisplaySize.y - size.y)/2)) );
			ImGui::End();
			ShowListInfo();
			ImGui::ItemSize( ImVec2(285, 155) );
			ImGui::EndChild();
		}
		break;
	}

	ImGui::SetCursorPosX((ImGui::GetWindowWidth() - 278 + ImGui::GetStyle().ItemSpacing.x) / 2);

	if(m_utf8Button1[0] != 0) 
	{
		if(ImGui::Button(m_utf8Button1, ImVec2((278/2) - 18.8, 50)))
		{
			Show(false);

			char *strid = szDialogInputBuffer;
			int id = atoi(strid) - 1;
			if(pNetGame) 
				pNetGame->SendDialogResponse(m_wDialogID, 1, id, szDialogInputBuffer);

			passEntering = 0;
		}
	}

	ImGui::SameLine(0, pGUI->GetFontSize());

	if(m_utf8Button2[0] != 0) 
	{
		if(ImGui::Button(m_utf8Button2, ImVec2((278/2) - 18.8,50)))
		{
			Show(false);
			if(pNetGame) 
				pNetGame->SendDialogResponse(m_wDialogID, 0, -1, szDialogInputBuffer);

			passEntering = 0;
		}
	}

	ImGui::SetWindowSize(ImVec2(-1, -1));
	ImVec2 size = ImGui::GetWindowSize();

	if(m_byteDialogStyle == DIALOG_STYLE_LIST or m_byteDialogStyle == DIALOG_STYLE_TABLIST or m_byteDialogStyle == DIALOG_STYLE_TABLIST_HEADERS) 
		ImGui::SetWindowPos( ImVec2( ((io.DisplaySize.x - size.x)/2 - 190), ((io.DisplaySize.y - size.y)/2)) );
			else ImGui::SetWindowPos( ImVec2( ((io.DisplaySize.x - size.x)/2), ((io.DisplaySize.y - size.y)/2)) );

	ImGui::End();

	ImGui::PopStyleVar();
}