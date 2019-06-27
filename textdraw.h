#pragma once

class CTextDraw
{
public:
	CTextDraw();
	~CTextDraw();

	void Render();
	void Clear();
	void Show(bool bShow);
	void StoreTD(uint16_t wTextID);
	
public:
	bool		m_bIsActive;
	char*		tdStorage;
	
	uint16_t	wtID;
};