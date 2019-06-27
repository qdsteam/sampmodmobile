#pragma once

class CSetsWindow
{
public:
	CSetsWindow();
	~CSetsWindow();

	void Render();
	void Clear();
	void Show(bool bShow);
	
public:
	bool		m_bIsActive;
	char		*username;
	char		*password;
};