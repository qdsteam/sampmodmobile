#pragma once

class CMenu
{
public:
	CMenu();
	~CMenu() {};

	void Render();
	void Show(bool bShow);

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