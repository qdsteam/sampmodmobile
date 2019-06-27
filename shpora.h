#pragma once

class CShpora
{
public:
	CShpora();
	~CShpora();

	void Render();
	void Clear();
	void Show(bool bShow);
	
public:
	bool		m_bIsActive;
	int			step;
};