#pragma once

class CSkinChanger
{
public:
	CSkinChanger();
	~CSkinChanger();

	void Render();
	void Clear();
	void Show(bool bShow);
	
public:
	bool				m_bIsActive;
};