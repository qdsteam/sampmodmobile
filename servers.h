#pragma once

class CServersWindow
{
public:
	CServersWindow();
	~CServersWindow();

	void Render();
	void Clear();
	void Show(bool bShow);
	void ShowAllServers();

public:
	bool		m_bIsActive;
	int			m_bMenuStep;
};