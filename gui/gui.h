#pragma once
#include "vendor/imgui/imgui.h"

enum eTouchType
{
	TOUCH_POP = 1,
	TOUCH_PUSH = 2,
	TOUCH_MOVE = 3
};

class CGUI
{
public:
	CGUI();
	~CGUI();

	void Render();

	float ScaleX(float x) { return m_vecScale.x * x; }
	float ScaleY(float y) { return m_vecScale.y * y; }
	ImFont* GetFont() { return m_pFont; }
	ImFont* GetSampFont() { return m_pSampFont; }
	float GetFontSize() { return m_fFontSize; }

	bool OnTouchEvent(int type, bool multi, int x, int y);

	void RenderText(ImVec2& pos, ImU32 col, bool bOutline, const char* text_begin, const char* text_end = nullptr);

private:
	void RenderRakNetStatistics();
	void RenderCheatBox();
	void SetupStyleColors();

private:
	ImFont* 	m_pFont;
	ImFont*		m_pSampFont;

	ImVec2		m_vecScale;
	float 		m_fFontSize;
	float		m_fCheatsBoxPosX;
	float		m_fCheatsBoxPosY;

	bool 		m_fCheatsBox;

	bool 		m_bMousePressed;
	ImVec2		m_vecMousePos;

	bool		m_bNeedClearMousePos;

public:
	int 		m_gm;
	int 		m_fz;
	int 		m_wh;
	int 		m_fly;
	int 		m_nf;
	int 		m_bd;
	int 		m_gravity;
	int 		m_xyz;
	int 		m_INVIS;
	int 		m_FLASH;
	int 		m_Airbreak;
};