#pragma once

// keyboard buttons
#define	ID_KEY_ALT 1024
#define	ID_KEY_TAB 1
#define	ID_KEY_C 2
#define	ID_KEY_LCTRL 4
#define	ID_KEY_SPACE 8
#define	ID_KEY_ENTER 16
#define	ID_KEY_LSHIFT 32
#define	ID_KEY_E 64
#define	ID_KEY_RMB 128
#define	ID_KEY_Q 256

#define	ID_KEY_TWO 320
#define	ID_KEY_TWOS 512

#define	ID_KEY_Y 65536
#define	ID_KEY_N 131072

class CExtraKeyBoard
{
public:
	CExtraKeyBoard();
	~CExtraKeyBoard();

	void Render();
	void Clear();
	void Show(bool bShow);

	void AddKeys();

public:
	bool		m_bIsActive;
	uint16_t	key;
};