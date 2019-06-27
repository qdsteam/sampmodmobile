#pragma once

class CModSAWindow
{
public:
	CModSAWindow();
	~CModSAWindow();

	void Render();
	void Clear();
	void Show(bool bShow);

	void ToggleCheat(int cheatid);
	void ToggleRPC(int rpcid);
	void ToggleTeleport(int posid);

	void StoreMarkerXYZ(float x, float y, float z);
	void ShowFlyMenu(bool bShow);

	void StartBotById(int id);

	void ToggleNoKickTeleport(float x, float y, float z);

	void SetFlySets(float distance);
	float GetFlySets();

	void ZavodBotTemp(int stepId);

public:
	bool		m_bIsActive;
	int			m_bMenuStep;
	int 		m_bFlyHack;
	int			m_bGodMode;
	int			m_bWallHack;
	int			m_bCols;
	int 		m_bINVIS;

	int			m_bVP;
	int			m_bVP2;
	int			m_bVV;
	int			m_bCO;
	int			m_bPH;
	int			m_bRPFV;
	int			m_bSD;
	int			m_bAPA;
	int			m_bRPW;
	int			m_bNF;
	int			m_bCP;
	int			m_bCP2;
	int			m_bGCW;
	int			m_bCA;
	int			m_bSPP;
	int			m_bGPP;
	int			m_bCTL;
	int			m_bEV;
	int 		m_bFLASH;
	int			m_bCE;
	int			m_bSPN;
	int			m_bAGZ;
	int 		m_bTPC;
	int 		m_bSTD;
	int 		m_bHTD;
	int			m_bSM;
	int 		m_bHM;
	int 		m_bSG;
	int 		m_clock;
	int 		m_bSPS;
	int			m_bAirbreak;
	int			fastfire;
	int			carvisible;

	int			protect;
	int			m_bKrutilka;
	int			lockinp;
	int			lock_weather;
	int 		lock_time;
	int 		rxyz;
	int 		flock;
	int			botzavod;
	int 		radar;

	float 		sPos1X;
	float 		sPos1Y;
	float 		sPos1Z;

	float 		sPos2X;
	float 		sPos2Y;
	float 		sPos2Z;

	float 		sPos3X;
	float 		sPos3Y;
	float 		sPos3Z;

	int 		dnames;
	int			players;

	int			zbot_reps;
	int			m_bot;
	int			extOS;
	int			curAnim;

	float 		i_x;
	float 		i_y;
	float 		i_z;

	float		marker_X;
	float		marker_Y;
	float		marker_Z;

	float		sx;
	float		sy;
	float		sz;

	float 		cHealth;
	float		xHealth;

	float 		fDist;

	char*		m_szAddress;
	int			m_szPort;
};