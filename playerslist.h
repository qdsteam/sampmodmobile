#pragma once

class CPlayersList
{
public:
	CPlayersList();
	~CPlayersList();

	void Render();
	void Clear();
	void Show(bool bShow);

public:
	bool		m_bIsActive;
	
	char*		szInfo;
	int			playersCount;
	bool 		out;
};