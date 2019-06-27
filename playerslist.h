#pragma once

class CPlayersList
{
public:
	CPlayersList();
	~CPlayersList();

	void Render();
	void Clear();
	void Show(bool bShow);
	void AddToList(char *buf);
	void RemoveFromList(char *buf);


public:
	bool		m_bIsActive;
	char*		szBuf;
	char*		name;
};