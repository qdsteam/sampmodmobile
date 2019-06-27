#pragma once

class CCustomServerWindow
{
public:
	CCustomServerWindow();
	~CCustomServerWindow();

	void Render();
	void Clear();
	void Show(bool bShow);
	
public:
	bool				m_bIsActive;
	char*				address;
	int					port;
	bool				m_bFixer;
};