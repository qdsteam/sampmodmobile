#pragma once

class CSpawnScreen
{
public:
	CSpawnScreen();
	~CSpawnScreen() {};

	void Render();
	void Show(bool bShow) { m_bEnabled = bShow; }

public:
	bool	m_bEnabled;
private:
	float	m_fPosX;
	float	m_fPosY;
	float 	m_fSizeX;
	float 	m_fSizeY;
	float 	m_fButWidth;
	float 	m_fButHeight;
};