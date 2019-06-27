#pragma once

#define MAX_PICKUPS 4096

#pragma pack(1)
typedef struct _PICKUP
{
	int iModel;
	int iType;
	float fX;
	float fY;
	float fZ;
} PICKUP;

typedef struct _DROPPED_WEAPON
{
	bool bDroppedWeapon;
	PLAYERID fromPlayer;
} DROPPED_WEAPON;

#pragma pack(1)
class CPickupPool
{
private:
	int 			m_iPickupCount;
	uint32_t 		m_dwHnd[MAX_PICKUPS];
	uint32_t 		m_iPickupID[MAX_PICKUPS];
	uint32_t 		m_iTimer[MAX_PICKUPS];
	DROPPED_WEAPON 	m_droppedWeapon[MAX_PICKUPS];
	PICKUP 			m_Pickups[MAX_PICKUPS];


public:
	CPickupPool();
	~CPickupPool();

	void New(PICKUP* pPickup, int iPickup);
	void NewWeapon(PICKUP* pPickup, int iPickup);
	void Destroy(int iPickup);
	void PickedUp(int iPickup);
	void Process();

	int GetNumberFromID(int id);
};