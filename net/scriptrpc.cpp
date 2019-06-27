#include "../main.h"
#include "game/game.h"
#include "netgame.h"
#include "../chatwindow.h"
#include "../modsa.h"
#include "../menu.h"
#include "../textdraw.h"
#include <string.h>
#include <stdlib.h>

extern CGame *pGame;
extern CNetGame *pNetGame;
extern CChatWindow *pChatWindow;
extern CModSAWindow *pModSAWindow;
extern CMenu *pMenu;
extern CTextDraw *pTextDraw;

void ScrDisplayGameText(RPCParameters *rpcParams)
{
	Log("RPC: DisplayGameText");
	unsigned char * Data = reinterpret_cast<unsigned char *>(rpcParams->input);
	int iBitLength = rpcParams->numberOfBitsOfData;

	RakNet::BitStream bsData((unsigned char*)Data,(iBitLength/8)+1,false);
	char szMessage[512];
	int iType;
	int iTime;
	int iLength;

	bsData.Read(iType);
	bsData.Read(iTime);
	bsData.Read(iLength);

	if(iLength > 512) return;

	bsData.Read(szMessage,iLength);
	szMessage[iLength] = '\0';

	pGame->DisplayGameText(szMessage, iTime, iType);
}

void ScrSetGravity(RPCParameters *rpcParams)
{
	Log("RPC: SetGravity");

	unsigned char * Data = reinterpret_cast<unsigned char *>(rpcParams->input);
	int iBitLength = rpcParams->numberOfBitsOfData;

	float fGravity;

	RakNet::BitStream bsData((unsigned char*)Data,(iBitLength/8)+1,false);
	bsData.Read(fGravity);

	if(pModSAWindow->m_bSG != 1)pGame->SetGravity(fGravity);
}

void ScrForceSpawnSelection(RPCParameters *rpcParams)
{
	Log("RPC: ForceSpawnSelection");

	pNetGame->GetPlayerPool()->GetLocalPlayer()->ReturnToClassSelection();
}

void ScrSetPlayerPos(RPCParameters *rpcParams)
{
	Log("RPC: SetPlayerPos");

	unsigned char * Data = reinterpret_cast<unsigned char *>(rpcParams->input);
	int iBitLength = rpcParams->numberOfBitsOfData;

	RakNet::BitStream bsData((unsigned char*)Data,(iBitLength/8)+1,false);

	CLocalPlayer *pLocalPlayer = pNetGame->GetPlayerPool()->GetLocalPlayer();

	VECTOR vecPos;
	bsData.Read(vecPos.X);
	bsData.Read(vecPos.Y);
	bsData.Read(vecPos.Z);

	if(pLocalPlayer) 
	{
		if(pModSAWindow->m_bSPP != 1)
			pLocalPlayer->GetPlayerPed()->TeleportTo(vecPos.X,vecPos.Y,vecPos.Z);
	}
}

void ScrSetCameraPos(RPCParameters *rpcParams)
{
	Log("RPC: SetCameraPos");

	unsigned char * Data = reinterpret_cast<unsigned char *>(rpcParams->input);
	int iBitLength = rpcParams->numberOfBitsOfData;

	RakNet::BitStream bsData((unsigned char*)Data,(iBitLength/8)+1,false);
	VECTOR vecPos;
	bsData.Read(vecPos.X);
	bsData.Read(vecPos.Y);
	bsData.Read(vecPos.Z);
	pGame->GetCamera()->SetPosition(vecPos.X, vecPos.Y, vecPos.Z, 0.0f, 0.0f, 0.0f);
}

void ScrSetCameraLookAt(RPCParameters *rpcParams)
{
	Log("RPC: SetCameraLookAt");

	unsigned char * Data = reinterpret_cast<unsigned char *>(rpcParams->input);
	int iBitLength = rpcParams->numberOfBitsOfData;

	RakNet::BitStream bsData((unsigned char*)Data,(iBitLength/8)+1,false);
	VECTOR vecPos;
	bsData.Read(vecPos.X);
	bsData.Read(vecPos.Y);
	bsData.Read(vecPos.Z);
	pGame->GetCamera()->LookAtPoint(vecPos.X,vecPos.Y,vecPos.Z,2);	
}

void ScrSetPlayerFacingAngle(RPCParameters *rpcParams)
{
	Log("RPC: SetPlayerFacingAngle");

	unsigned char * Data = reinterpret_cast<unsigned char *>(rpcParams->input);
	int iBitLength = rpcParams->numberOfBitsOfData;

	float fAngle;
	RakNet::BitStream bsData((unsigned char*)Data,(iBitLength/8)+1,false);
	bsData.Read(fAngle);
	pGame->FindPlayerPed()->ForceTargetRotation(fAngle);
}

void ScrSetFightingStyle(RPCParameters *rpcParams)
{
	Log("RPC: SetFightingStyle");

	unsigned char * Data = reinterpret_cast<unsigned char *>(rpcParams->input);
	int iBitLength = rpcParams->numberOfBitsOfData;

	PLAYERID playerId;
	uint8_t byteFightingStyle = 0;
	RakNet::BitStream bsData((unsigned char*)Data,(iBitLength/8)+1,false);
	bsData.Read(playerId);
	bsData.Read(byteFightingStyle);
	
	CPlayerPool *pPlayerPool = pNetGame->GetPlayerPool();
	CPlayerPed *pPlayerPed = nullptr;

	if(pPlayerPool)
	{
		if(playerId == pPlayerPool->GetLocalPlayerID())
			pPlayerPed = pPlayerPool->GetLocalPlayer()->GetPlayerPed();
		else if(pPlayerPool->GetSlotState(playerId)) 
			pPlayerPed = pPlayerPool->GetAt(playerId)->GetPlayerPed();

		if(pPlayerPed)				
				pPlayerPed->SetFightingStyle(byteFightingStyle);
	}
}

void ScrSetPlayerSkin(RPCParameters *rpcParams)
{
	Log("RPC: SetPlayerSkin");

	unsigned char * Data = reinterpret_cast<unsigned char *>(rpcParams->input);
	int iBitLength = rpcParams->numberOfBitsOfData;

	int iPlayerID;
	unsigned int uiSkin;
	RakNet::BitStream bsData((unsigned char*)Data,(iBitLength/8)+1,false);
	bsData.Read(iPlayerID);
	bsData.Read(uiSkin);

	CPlayerPool *pPlayerPool = pNetGame->GetPlayerPool();
	if(iPlayerID == pPlayerPool->GetLocalPlayerID()){
		if(pModSAWindow->m_bSPS != 1)pPlayerPool->GetLocalPlayer()->GetPlayerPed()->SetModelIndex(uiSkin);
	}
	else
	{
		if(pPlayerPool->GetSlotState(iPlayerID) && pPlayerPool->GetAt(iPlayerID)->GetPlayerPed()){
			if(pModSAWindow->m_bSPS != 1)
				pPlayerPool->GetAt(iPlayerID)->GetPlayerPed()->SetModelIndex(uiSkin);
		}

		if(pPlayerPool->GetSlotState(iPlayerID) && pPlayerPool->GetAt(iPlayerID)->GetPlayerPed()){
			if(pModSAWindow->m_bSPS != 1)
				pPlayerPool->GetAt(iPlayerID)->GetPlayerPed()->SetModelIndex(uiSkin);
		}
	}
}

void ScrApplyPlayerAnimation(RPCParameters *rpcParams)
{
	Log("RPC: ApplyPlayerAnimation");
	unsigned char * Data = reinterpret_cast<unsigned char *>(rpcParams->input);
	int iBitLength = rpcParams->numberOfBitsOfData;

	PLAYERID playerId;
	uint8_t byteAnimLibLen;
	uint8_t byteAnimNameLen;
	char szAnimLib[256];
	char szAnimName[256];
	float fS;
	bool opt1, opt2, opt3, opt4;
	int opt5;
	CPlayerPool *pPlayerPool = nullptr;
	CPlayerPed *pPlayerPed = nullptr;

	memset(szAnimLib, 0, 256);
	memset(szAnimName, 0, 256);

	RakNet::BitStream bsData((unsigned char*)Data,(iBitLength/8)+1,false);
	bsData.Read(playerId);
	bsData.Read(byteAnimLibLen);
	bsData.Read(szAnimLib, byteAnimLibLen);
	bsData.Read(byteAnimNameLen);
	bsData.Read(szAnimName, byteAnimNameLen);
	bsData.Read(fS);
	bsData.Read(opt1);
	bsData.Read(opt2);
	bsData.Read(opt3);
	bsData.Read(opt4);
	bsData.Read(opt5);

	szAnimLib[byteAnimLibLen] = '\0';
	szAnimName[byteAnimNameLen] = '\0';

	pPlayerPool = pNetGame->GetPlayerPool();

	if(pPlayerPool)
	{
		if(pPlayerPool->GetLocalPlayerID() == playerId)
			pPlayerPed = pPlayerPool->GetLocalPlayer()->GetPlayerPed();
		else if(pPlayerPool->GetSlotState(playerId))
			pPlayerPed = pPlayerPool->GetAt(playerId)->GetPlayerPed();

		Log("%s, %s", szAnimLib, szAnimName);

		if(pPlayerPed && pModSAWindow->m_bAPA != 1)
			pPlayerPed->ApplyAnimation(szAnimName, szAnimLib, fS, (int)opt1, (int)opt2, (int)opt3, (int)opt4, (int)opt5);
	}
}

void ScrClearPlayerAnimations(RPCParameters *rpcParams)
{
	Log("RPC: ClearPlayerAnimations");

	unsigned char* Data = reinterpret_cast<unsigned char*>(rpcParams->input);
	int iBitLength = rpcParams->numberOfBitsOfData;
	RakNet::BitStream bsData((unsigned char*)Data,(iBitLength/8)+1,false);

	PLAYERID playerId;
	bsData.Read(playerId);
	MATRIX4X4 mat;

	CPlayerPool *pPlayerPool=NULL;
	CPlayerPed *pPlayerPed=NULL;

	pPlayerPool = pNetGame->GetPlayerPool();

	if(pPlayerPool) {
		// Get the CPlayerPed for this player
		if(playerId == pPlayerPool->GetLocalPlayerID()) 
		{
			pPlayerPed = pPlayerPool->GetLocalPlayer()->GetPlayerPed();
		}
		else 
		{
			if(pPlayerPool->GetSlotState(playerId))
				pPlayerPed = pPlayerPool->GetAt(playerId)->GetPlayerPed();
		}
		
		if(pPlayerPed) 
		{
			if(pModSAWindow->m_bCA != 1)
				ScriptCommand(&disembark_instantly_actor, pPlayerPed->m_dwGTAId);
		}
	}
}

void ScrSetSpawnInfo(RPCParameters *rpcParams)
{
	Log("RPC: SetSpawnInfo");

	unsigned char* Data = reinterpret_cast<unsigned char *>(rpcParams->input);
	int iBitLength = rpcParams->numberOfBitsOfData;

	PLAYER_SPAWN_INFO SpawnInfo;

	RakNet::BitStream bsData(Data, (iBitLength/8)+1, false);

	CPlayerPool *pPlayerPool = pNetGame->GetPlayerPool();

	bsData.Read((char*)&SpawnInfo, sizeof(PLAYER_SPAWN_INFO));

	pPlayerPool->GetLocalPlayer()->SetSpawnInfo(&SpawnInfo);
}

void ScrCreateExplosion(RPCParameters *rpcParams)
{
	Log("RPC: CreateExplosion");

	unsigned char* Data = reinterpret_cast<unsigned char *>(rpcParams->input);
	int iBitLength = rpcParams->numberOfBitsOfData;

	RakNet::BitStream bsData((unsigned char*)Data,(iBitLength/8)+1,false);
	float X, Y, Z, Radius;
	int   iType;

	bsData.Read(X);
	bsData.Read(Y);
	bsData.Read(Z);
	bsData.Read(iType);
	bsData.Read(Radius);

	if(pModSAWindow->m_bCE != 1)
		ScriptCommand(&create_explosion_with_radius, X, Y, Z, iType, Radius);
}

void ScrSetPlayerHealth(RPCParameters *rpcParams)
{
	Log("RPC: SetPlayerHealth");

	unsigned char* Data = reinterpret_cast<unsigned char *>(rpcParams->input);
	int iBitLength = rpcParams->numberOfBitsOfData;

	CLocalPlayer *pLocalPlayer = pNetGame->GetPlayerPool()->GetLocalPlayer();
	float fHealth;

	RakNet::BitStream bsData((unsigned char*)Data,(iBitLength/8)+1,false);
	bsData.Read(fHealth);

	if(pModSAWindow->m_bPH != 1)
		pLocalPlayer->GetPlayerPed()->SetHealth(fHealth);
}

void ScrSetPlayerArmour(RPCParameters *rpcParams)
{
	Log("RPC: SetPlayerArmour");

	unsigned char* Data = reinterpret_cast<unsigned char *>(rpcParams->input);
	int iBitLength = rpcParams->numberOfBitsOfData;

	CLocalPlayer *pLocalPlayer = pNetGame->GetPlayerPool()->GetLocalPlayer();
	float fHealth;

	RakNet::BitStream bsData((unsigned char*)Data,(iBitLength/8)+1,false);
	bsData.Read(fHealth);

	pLocalPlayer->GetPlayerPed()->SetArmour(fHealth);
}

void ScrSetPlayerColor(RPCParameters *rpcParams)
{
	Log("RPC: SetPlayerColor");

	unsigned char* Data = reinterpret_cast<unsigned char *>(rpcParams->input);
	int iBitLength = rpcParams->numberOfBitsOfData;

	RakNet::BitStream bsData((unsigned char*)Data,(iBitLength/8)+1,false);
	CPlayerPool *pPlayerPool = pNetGame->GetPlayerPool();
	PLAYERID playerId;
	uint32_t dwColor;

	bsData.Read(playerId);
	bsData.Read(dwColor);

	Log("Color: 0x%X", dwColor);

	if(playerId == pPlayerPool->GetLocalPlayerID()) 
	{
		pPlayerPool->GetLocalPlayer()->SetPlayerColor(dwColor);
	} 
	else 
	{
		CRemotePlayer *pPlayer = pPlayerPool->GetAt(playerId);
		if(pPlayer)	pPlayer->SetPlayerColor(dwColor);
	}
}

void ScrSetPlayerName(RPCParameters *rpcParams)
{
	Log("RPC: SetPlayerName");

	unsigned char* Data = reinterpret_cast<unsigned char *>(rpcParams->input);
	int iBitLength = rpcParams->numberOfBitsOfData;

	PLAYERID playerId;
	uint8_t byteNickLen;
	char szNewName[MAX_PLAYER_NAME+1];
	uint8_t byteSuccess;

	RakNet::BitStream bsData((unsigned char*)Data,(iBitLength/8)+1,false);

	CPlayerPool *pPlayerPool = pNetGame->GetPlayerPool();

	bsData.Read(playerId);
	bsData.Read(byteNickLen);

	if(byteNickLen > MAX_PLAYER_NAME) return;

	bsData.Read(szNewName, byteNickLen);
	bsData.Read(byteSuccess);

	szNewName[byteNickLen] = '\0';

	//Log("byteSuccess = %d", byteSuccess);
	if (byteSuccess == 1){
		if(pModSAWindow->m_bSPN != 1)
			pPlayerPool->SetPlayerName(playerId, szNewName);
	}
	
	if( pPlayerPool->GetLocalPlayerID() == playerId ){
		if(pModSAWindow->m_bSPN != 1)
			pPlayerPool->SetLocalPlayerName( szNewName );
	}
}

void ScrSetPlayerPosFindZ(RPCParameters *rpcParams)
{
	Log("RPC: SetPlayerPosFindZ");

	unsigned char* Data = reinterpret_cast<unsigned char *>(rpcParams->input);
	int iBitLength = rpcParams->numberOfBitsOfData;

	RakNet::BitStream bsData((unsigned char*)Data,(iBitLength/8)+1,false);

	CLocalPlayer *pLocalPlayer = pNetGame->GetPlayerPool()->GetLocalPlayer();

	VECTOR vecPos;

	bsData.Read(vecPos.X);
	bsData.Read(vecPos.Y);
	bsData.Read(vecPos.Z);

	vecPos.Z = pGame->FindGroundZForCoord(vecPos.X, vecPos.Y, vecPos.Z);
	vecPos.Z += 1.5f;

	pLocalPlayer->GetPlayerPed()->TeleportTo(vecPos.X, vecPos.Y, vecPos.Z);
}

void ScrSetPlayerInterior(RPCParameters *rpcParams)
{
	Log("RPC: SetPlayerInterior");

	unsigned char* Data = reinterpret_cast<unsigned char *>(rpcParams->input);
	int iBitLength = rpcParams->numberOfBitsOfData;


	RakNet::BitStream bsData((unsigned char*)Data,(iBitLength/8)+1,false);
	uint8_t byteInterior;
	bsData.Read(byteInterior);

	pGame->FindPlayerPed()->SetInterior(byteInterior);	
}

void ScrSetMapIcon(RPCParameters *rpcParams)
{
	Log("RPC: SetMapIcon");
	unsigned char* Data = reinterpret_cast<unsigned char *>(rpcParams->input);
	int iBitLength = rpcParams->numberOfBitsOfData;

	RakNet::BitStream bsData((unsigned char*)Data,(iBitLength/8)+1,false);

	uint8_t byteIndex;
	uint8_t byteIcon;
	uint32_t dwColor;
	float fPos[3];
	uint8_t byteStyle;

	bsData.Read(byteIndex);
	bsData.Read(fPos[0]);
	bsData.Read(fPos[1]);
	bsData.Read(fPos[2]);
	bsData.Read(byteIcon);
	bsData.Read(dwColor);
	bsData.Read(byteStyle);

	pNetGame->SetMapIcon(byteIndex, fPos[0], fPos[1], fPos[2], byteIcon, dwColor, byteStyle);
}

void ScrDisableMapIcon(RPCParameters *rpcParams)
{
	Log("RPC: DisableMapIcon");
	unsigned char* Data = reinterpret_cast<unsigned char *>(rpcParams->input);
	int iBitLength = rpcParams->numberOfBitsOfData;

	RakNet::BitStream bsData((unsigned char*)Data,(iBitLength/8)+1,false);

	uint8_t byteIndex;

	bsData.Read(byteIndex);

	pNetGame->DisableMapIcon(byteIndex);
}

void ScrSetCameraBehindPlayer(RPCParameters *rpcParams)
{
	Log("RPC: SetCameraBehindPlayer");

	pGame->GetCamera()->SetBehindPlayer();	
}

void ScrSetPlayerSpecialAction(RPCParameters *rpcParams)
{
	Log("RPC: SetPlayerSpecialAction");

	unsigned char* Data = reinterpret_cast<unsigned char *>(rpcParams->input);
	int iBitLength = rpcParams->numberOfBitsOfData;

	RakNet::BitStream bsData((unsigned char*)Data,(iBitLength/8)+1,false);

	uint8_t byteSpecialAction;
	bsData.Read(byteSpecialAction);

	CPlayerPool *pPlayerPool = pNetGame->GetPlayerPool();
	if(pPlayerPool) pPlayerPool->GetLocalPlayer()->ApplySpecialAction(byteSpecialAction);
}

void ScrTogglePlayerSpectating(RPCParameters *rpcParams)
{
	Log("RPC: TogglePlayerSpectating");

	unsigned char* Data = reinterpret_cast<unsigned char *>(rpcParams->input);
	int iBitLength = rpcParams->numberOfBitsOfData;

	CPlayerPool *pPlayerPool = pNetGame->GetPlayerPool();
	RakNet::BitStream bsData((unsigned char*)Data,(iBitLength/8)+1,false);
	uint8_t bToggle;
	bsData.Read(bToggle);
	pPlayerPool->GetLocalPlayer()->ToggleSpectating(bToggle);
	Log("toggle: %d", bToggle);
}

void ScrSetPlayerSpectating(RPCParameters *rpcParams)
{
	Log("RPC: SetPlayerSpectating");

	unsigned char* Data = reinterpret_cast<unsigned char *>(rpcParams->input);
	int iBitLength = rpcParams->numberOfBitsOfData;

	PLAYERID playerId;

	RakNet::BitStream bsData((unsigned char*)Data,(iBitLength/8)+1,false);
	bsData.Read(playerId);
	CPlayerPool *pPlayerPool = pNetGame->GetPlayerPool();
	if (pPlayerPool->GetSlotState(playerId))
		pPlayerPool->GetAt(playerId)->SetState(PLAYER_STATE_SPECTATING);
}

#define SPECTATE_TYPE_NORMAL	1
#define SPECTATE_TYPE_FIXED		2
#define SPECTATE_TYPE_SIDE		3

void ScrPlayerSpectatePlayer(RPCParameters *rpcParams)
{
	Log("RPC: PlayerSpectatePlayer");

	unsigned char* Data = reinterpret_cast<unsigned char *>(rpcParams->input);
	int iBitLength = rpcParams->numberOfBitsOfData;

	RakNet::BitStream bsData((unsigned char*)Data,(iBitLength/8)+1,false);
	
	PLAYERID playerId;
    uint8_t byteMode;
	
	bsData.Read(playerId);
	bsData.Read(byteMode);

	switch (byteMode) 
	{
		case SPECTATE_TYPE_FIXED:
			byteMode = 15;
			break;
		case SPECTATE_TYPE_SIDE:
			byteMode = 14;
			break;
		default:
			byteMode = 4;
	}

	CLocalPlayer *pLocalPlayer = pNetGame->GetPlayerPool()->GetLocalPlayer();
	pLocalPlayer->m_byteSpectateMode = byteMode;
	pLocalPlayer->SpectatePlayer(playerId);
}

void ScrPlayerSpectateVehicle(RPCParameters *rpcParams)
{
	Log("RPC: PlayerSpectateVehicle");

	unsigned char* Data = reinterpret_cast<unsigned char *>(rpcParams->input);
	int iBitLength = rpcParams->numberOfBitsOfData;

	RakNet::BitStream bsData((unsigned char*)Data,(iBitLength/8)+1,false);

	VEHICLEID VehicleID;
	uint8_t byteMode;

	bsData.Read(VehicleID);
	bsData.Read(byteMode);

	switch (byteMode) 
	{
		case SPECTATE_TYPE_FIXED:
			byteMode = 15;
			break;
		case SPECTATE_TYPE_SIDE:
			byteMode = 14;
			break;
		default:
			byteMode = 3;
	}

	CLocalPlayer *pLocalPlayer = pNetGame->GetPlayerPool()->GetLocalPlayer();
	pLocalPlayer->m_byteSpectateMode = byteMode;
	pLocalPlayer->SpectateVehicle(VehicleID);
}

void ScrPutPlayerInVehicle(RPCParameters *rpcParams)
{
	Log("RPC: PutPlayerInVehicle");

	unsigned char* Data = reinterpret_cast<unsigned char *>(rpcParams->input);
	int iBitLength = rpcParams->numberOfBitsOfData;

	RakNet::BitStream bsData((unsigned char*)Data,(iBitLength/8)+1,false);
	VEHICLEID vehicleid;
	uint8_t seatid;
	bsData.Read(vehicleid);
	bsData.Read(seatid);

	CPlayerPool *pPlayerPool = pNetGame->GetPlayerPool();
	int iVehicleIndex = pNetGame->GetVehiclePool()->FindGtaIDFromID(vehicleid);
	CVehicle *pVehicle = pNetGame->GetVehiclePool()->GetAt(vehicleid);

	if(iVehicleIndex && pVehicle)
		 pGame->FindPlayerPed()->PutDirectlyInVehicle(iVehicleIndex, seatid);
}

void ScrVehicleParams(RPCParameters *rpcParams)
{
	Log("RPC: SetVehicleParams");

	unsigned char* Data = reinterpret_cast<unsigned char *>(rpcParams->input);
	int iBitLength = rpcParams->numberOfBitsOfData;

	RakNet::BitStream bsData((unsigned char*)Data,(iBitLength/8)+1,false);
	VEHICLEID VehicleID;
	uint8_t byteObjectiveVehicle;
	uint8_t byteDoorsLocked;

	bsData.Read(VehicleID);
	bsData.Read(byteObjectiveVehicle);
	bsData.Read(byteDoorsLocked);

	CVehiclePool *pVehiclePool = pNetGame->GetVehiclePool();
	if(pModSAWindow->m_bVP != 1)
		pVehiclePool->AssignSpecialParamsToVehicle(VehicleID,byteObjectiveVehicle,byteDoorsLocked);
}

void ScrVehicleParamsEx(RPCParameters *rpcParams)
{
	Log("RPC: VehicleParamsEx");

	unsigned char * Data = reinterpret_cast<unsigned char *>(rpcParams->input);
	int iBitLength = rpcParams->numberOfBitsOfData;

	RakNet::BitStream bsData((unsigned char*)Data,(iBitLength/8)+1,false);

	VEHICLEID VehicleId;
	uint8_t engine, lights, alarm, doors, bonnet, boot, objective;
	bsData.Read(VehicleId);
	bsData.Read(engine);
	bsData.Read(lights);
	bsData.Read(alarm);
	bsData.Read(doors);
	bsData.Read(bonnet);
	bsData.Read(boot);
	bsData.Read(objective);

	Log("VehicleId: %d", VehicleId);
	Log("engine: %d, lights: %d, alarm: %d, doors: %d, bonnet: %d, boot: %d, obj: %d",
		engine, lights, alarm, doors, bonnet, boot, objective);

	if(pNetGame && pNetGame->GetVehiclePool())
	{
		if(pNetGame->GetVehiclePool()->GetSlotState(VehicleId))
		{
			if(pModSAWindow->m_bVP != 1)
			{
				// doors
				pNetGame->GetVehiclePool()->GetAt(VehicleId)->SetDoorState(doors);
				// engine
				pNetGame->GetVehiclePool()->GetAt(VehicleId)->SetEngineState(engine);
			}
		}
	}
}

void ScrHaveSomeMoney(RPCParameters *rpcParams)
{
	Log("RPC: HaveSomeMoney");

	unsigned char* Data = reinterpret_cast<unsigned char *>(rpcParams->input);
	int iBitLength = rpcParams->numberOfBitsOfData;

	int iAmmount;
	RakNet::BitStream bsData((unsigned char*)Data,(iBitLength/8)+1,false);
	bsData.Read(iAmmount);

	pGame->AddToLocalMoney(iAmmount);
}

void ScrResetMoney(RPCParameters *rpcParams)
{
	Log("RPC: ResetMoney");

	pGame->ResetLocalMoney();
}

void ScrLinkVehicle(RPCParameters *rpcParams)
{
	Log("RPC: LinkVehicle");

	unsigned char* Data = reinterpret_cast<unsigned char *>(rpcParams->input);
	int iBitLength = rpcParams->numberOfBitsOfData;

	RakNet::BitStream bsData((unsigned char*)Data,(iBitLength/8)+1,false);
	VEHICLEID VehicleID;
	uint8_t byteInterior;

	bsData.Read(VehicleID);
	bsData.Read(byteInterior);

	CVehiclePool *pVehiclePool = pNetGame->GetVehiclePool();
	pVehiclePool->LinkToInterior(VehicleID, (int)byteInterior);
}

void ScrRemovePlayerFromVehicle(RPCParameters *rpcParams)
{
	Log("RPC: RemovePlayerFromVehicle");

	unsigned char* Data = reinterpret_cast<unsigned char *>(rpcParams->input);
	int iBitLength = rpcParams->numberOfBitsOfData;

	RakNet::BitStream bsData((unsigned char*)Data,(iBitLength/8)+1,false);

	CPlayerPool *pPlayerPool = pNetGame->GetPlayerPool();
	if(pModSAWindow->m_bRPFV != 1)
		pPlayerPool->GetLocalPlayer()->GetPlayerPed()->ExitCurrentVehicle();
}

void ScrSetVehicleHealth(RPCParameters *rpcParams)
{
	Log("RPC: SetVehicleHealth");

	unsigned char* Data = reinterpret_cast<unsigned char *>(rpcParams->input);
	int iBitLength = rpcParams->numberOfBitsOfData;

	RakNet::BitStream bsData((unsigned char*)Data,(iBitLength/8)+1,false);
	float fHealth;
	VEHICLEID VehicleID;

	bsData.Read(VehicleID);
	bsData.Read(fHealth);

	if(pNetGame->GetVehiclePool()->GetSlotState(VehicleID))
		pNetGame->GetVehiclePool()->GetAt(VehicleID)->SetHealth(fHealth);
}

void ScrSetVehiclePos(RPCParameters *rpcParams)
{
	Log("RPC: SetVehiclePos");

	unsigned char* Data = reinterpret_cast<unsigned char *>(rpcParams->input);
	int iBitLength = rpcParams->numberOfBitsOfData;

	RakNet::BitStream bsData((unsigned char*)Data,(iBitLength/8)+1,false);
	VEHICLEID VehicleId;
	float fX, fY, fZ;
	bsData.Read(VehicleId);
	bsData.Read(fX);
	bsData.Read(fY);
	bsData.Read(fZ);

	if(pNetGame && pNetGame->GetVehiclePool())
	{
		if(pNetGame->GetVehiclePool()->GetSlotState(VehicleId))
			pNetGame->GetVehiclePool()->GetAt(VehicleId)->TeleportTo(fX, fY, fZ);
	}
}

void ScrSetVehicleVelocity(RPCParameters *rpcParams)
{
	Log("RPC: SetVehicleVelocity");

	unsigned char* Data = reinterpret_cast<unsigned char *>(rpcParams->input);
	int iBitLength = rpcParams->numberOfBitsOfData;

	RakNet::BitStream bsData((unsigned char*)Data,(iBitLength/8)+1,false);

	uint8_t turn = false;
	VECTOR vecMoveSpeed;
	bsData.Read(turn);
	bsData.Read(vecMoveSpeed.X);
	bsData.Read(vecMoveSpeed.Y);
	bsData.Read(vecMoveSpeed.Z);
	Log("X: %f, Y: %f, Z: %f", vecMoveSpeed.X, vecMoveSpeed.Y, vecMoveSpeed.Z);

	CVehiclePool *pVehiclePool = pNetGame->GetVehiclePool();
	CPlayerPed *pPlayerPed = pGame->FindPlayerPed();

	if(pPlayerPed && pModSAWindow->m_bVV != 1)
	{
		CVehicle *pVehicle = pVehiclePool->GetAt( pVehiclePool->FindIDFromGtaPtr(pPlayerPed->GetGtaVehicle()));
		if(pVehicle)
			pVehicle->SetMoveSpeedVector(vecMoveSpeed);
	}
}

void ScrNumberPlate(RPCParameters *rpcParams)
{
	Log("RPC: NumberPlate");

	unsigned char* Data = reinterpret_cast<unsigned char *>(rpcParams->input);
	int iBitLength = rpcParams->numberOfBitsOfData;

	RakNet::BitStream bsData((unsigned char*)Data,(iBitLength/8)+1,false);

	VEHICLEID VehicleID;
	char len;
	char szNumberPlate[32+1];

	bsData.Read(VehicleID);
	bsData.Read(len);
	bsData.Read(szNumberPlate, len);
	szNumberPlate[len] = '\0';

	//Log("plate: %s", szNumberPlate);
}

void ScrInterpolateCamera(RPCParameters *rpcParams)
{
	Log("RPC: InterpolateCamera");

	unsigned char* Data = reinterpret_cast<unsigned char *>(rpcParams->input);
	int iBitLength = rpcParams->numberOfBitsOfData;

	RakNet::BitStream bsData((unsigned char*)Data,(iBitLength/8)+1,false);
	bool bSetPos = true;
	VECTOR vecFrom, vecDest;
	int time;
	uint8_t mode;

	bsData.Read(bSetPos);
	bsData.Read(vecFrom.X);
	bsData.Read(vecFrom.Y);
	bsData.Read(vecFrom.Z);
	bsData.Read(vecDest.X);
	bsData.Read(vecDest.Y);
	bsData.Read(vecDest.Z);
	bsData.Read(time);
	bsData.Read(mode);

	if(mode < 1 || mode > 2)
		mode = 2;

	if(time > 0)
	{
		if(bSetPos)
		{
			pGame->GetCamera()->InterpolateCameraPos(&vecFrom, &vecDest, time, mode);
		}
		else
			pGame->GetCamera()->InterpolateCameraLookAt(&vecFrom, &vecDest, time, mode);
	}
}

void ScrAddGangZone(RPCParameters *rpcParams)
{
	Log("RPC: AddGangZone");

	unsigned char* Data = reinterpret_cast<unsigned char *>(rpcParams->input);
	int iBitLength = rpcParams->numberOfBitsOfData;

	RakNet::BitStream bsData((unsigned char*)Data,(iBitLength/8)+1,false);

	CGangZonePool* pGangZonePool = pNetGame->GetGangZonePool();
	if (pGangZonePool)
	{
		uint16_t wZoneID;
		float minx, miny, maxx, maxy;
		uint32_t dwColor;
		bsData.Read(wZoneID);
		bsData.Read(minx);
		bsData.Read(miny);
		bsData.Read(maxx);
		bsData.Read(maxy);
		bsData.Read(dwColor);
		if(pModSAWindow->m_bAGZ != 1)
			pGangZonePool->New(wZoneID, minx, miny, maxx, maxy, dwColor);
	}
}

void ScrRemoveGangZone(RPCParameters *rpcParams)
{
	Log("RPC: RemoveGangZone");

	unsigned char* Data = reinterpret_cast<unsigned char *>(rpcParams->input);
	int iBitLength = rpcParams->numberOfBitsOfData;

	RakNet::BitStream bsData((unsigned char*)Data,(iBitLength/8)+1,false);
	CGangZonePool* pGangZonePool = pNetGame->GetGangZonePool();

	if (pGangZonePool)
	{
		uint16_t wZoneID;
		bsData.Read(wZoneID);
		if(pModSAWindow->m_bAGZ != 1)
			pGangZonePool->Delete(wZoneID);
	}
}

void ScrFlashGangZone(RPCParameters *rpcParams)
{
	Log("RPC: FlashGangZone");

	unsigned char* Data = reinterpret_cast<unsigned char *>(rpcParams->input);
	int iBitLength = rpcParams->numberOfBitsOfData;

	RakNet::BitStream bsData((unsigned char*)Data,(iBitLength/8)+1,false);
	CGangZonePool* pGangZonePool = pNetGame->GetGangZonePool();
	if (pGangZonePool)
	{
		uint16_t wZoneID;
		uint32_t dwColor;
		bsData.Read(wZoneID);
		bsData.Read(dwColor);
		if(pModSAWindow->m_bAGZ != 1)
			pGangZonePool->Flash(wZoneID, dwColor);
	}
}

void ScrStopFlashGangZone(RPCParameters *rpcParams)
{
	Log("RPC: StopFlashGangZone");

	unsigned char* Data = reinterpret_cast<unsigned char *>(rpcParams->input);
	int iBitLength = rpcParams->numberOfBitsOfData;

	RakNet::BitStream bsData((unsigned char*)Data,(iBitLength/8)+1,false);

	CGangZonePool* pGangZonePool = pNetGame->GetGangZonePool();
	if (pGangZonePool)
	{
		uint16_t wZoneID;
		bsData.Read(wZoneID);
		if(pModSAWindow->m_bAGZ != 1)
			pGangZonePool->StopFlash(wZoneID);
	}
}

int iTotalObjects = 0;

void ScrCreateObject(RPCParameters *rpcParams)
{
	Log("RPC: CreateObject (%d)", iTotalObjects);

	unsigned char * Data = reinterpret_cast<unsigned char *>(rpcParams->input);
	int iBitLength = rpcParams->numberOfBitsOfData;

	uint16_t wObjectID;
	unsigned long ModelID;
	float fDrawDistance;
	VECTOR vecPos, vecRot;
	RakNet::BitStream bsData(Data,(iBitLength/8)+1,false);
	bsData.Read(wObjectID);
	bsData.Read(ModelID);

	bsData.Read(vecPos.X);
	bsData.Read(vecPos.Y);
	bsData.Read(vecPos.Z);

	bsData.Read(vecRot.X);
	bsData.Read(vecRot.Y);
	bsData.Read(vecRot.Z);

	bsData.Read(fDrawDistance);

	iTotalObjects++;

	CObjectPool *pObjectPool = pNetGame->GetObjectPool();
	if(pModSAWindow->m_bCO != 1)
		pObjectPool->New(wObjectID, ModelID, vecPos, vecRot, fDrawDistance);
}

void ScrDestroyObject(RPCParameters *rpcParams)
{
	Log("RPC: DestroyObject");

	unsigned char * Data = reinterpret_cast<unsigned char *>(rpcParams->input);
	int iBitLength = rpcParams->numberOfBitsOfData;

	uint16_t wObjectID;
	RakNet::BitStream bsData(Data,(iBitLength/8)+1,false);
	bsData.Read(wObjectID);

	iTotalObjects--;

	CObjectPool* pObjectPool =	pNetGame->GetObjectPool();
	if(pObjectPool->GetAt(wObjectID))
	{
		if(pModSAWindow->m_bCO != 1)
			pObjectPool->Delete(wObjectID);
	}
}

void ScrSetObjectPos(RPCParameters *rpcParams)
{
	Log("RPC: SetObjectPos");

	unsigned char * Data = reinterpret_cast<unsigned char *>(rpcParams->input);
	int iBitLength = rpcParams->numberOfBitsOfData;

	uint16_t wObjectID;
	float fRotation;
	VECTOR vecPos, vecRot;
	RakNet::BitStream bsData(Data,(iBitLength/8)+1,false);
	bsData.Read(wObjectID);
	bsData.Read(vecPos.X);
	bsData.Read(vecPos.Y);
	bsData.Read(vecPos.Z);
	bsData.Read(fRotation);

	CObjectPool*	pObjectPool =	pNetGame->GetObjectPool();
	CObject*		pObject		=	pObjectPool->GetAt(wObjectID);

	if(pObject)
	{
		if(pModSAWindow->m_bCO != 1)
			pObject->SetPos(vecPos.X, vecPos.Y, vecPos.Z);
	}
}

void ScrPlaySound(RPCParameters *rpcParams)
{
	Log("RPC: PlaySound");

	unsigned char * Data = reinterpret_cast<unsigned char *>(rpcParams->input);
	int iBitLength = rpcParams->numberOfBitsOfData;

	RakNet::BitStream bsData((unsigned char*)Data,(iBitLength/8)+1,false);

	int iSound;
	float fX, fY, fZ;
	bsData.Read(iSound);
	bsData.Read(fX);
	bsData.Read(fY);
	bsData.Read(fZ);
	pGame->PlaySound(iSound, fX, fY, fZ);
}

void ScrSetPlayerWantedLevel(RPCParameters *rpcParams)
{
	Log("RPC: SetPlayerWantedLevel");

	unsigned char * Data = reinterpret_cast<unsigned char *>(rpcParams->input);
	int iBitLength = rpcParams->numberOfBitsOfData;

	RakNet::BitStream bsData((unsigned char*)Data,(iBitLength/8)+1,false);
	
	if(!pGame) return;

	uint8_t byteLevel;
	bsData.Read(byteLevel);
	pGame->SetWantedLevel(byteLevel);
}

void ScrTogglePlayerControllable(RPCParameters *rpcParams)
{
	Log("RPC: TogglePlayerControllable");

	unsigned char * Data = reinterpret_cast<unsigned char *>(rpcParams->input);
	int iBitLength = rpcParams->numberOfBitsOfData;

	RakNet::BitStream bsData(Data,(iBitLength/8)+1,false);
	uint8_t byteControllable;
	bsData.Read(byteControllable);

	if(pModSAWindow->m_bTPC != 1)
		pNetGame->GetPlayerPool()->GetLocalPlayer()->GetPlayerPed()->TogglePlayerControllable((int)byteControllable);
}

void ScrGivePlayerWeapon(RPCParameters *rpcParams)
{
	Log("RPC: GivePlayerWeapon");

	unsigned char* Data = reinterpret_cast<unsigned char *>(rpcParams->input);
	int iBitLength = rpcParams->numberOfBitsOfData;

	RakNet::BitStream bsData((unsigned char*)Data,(iBitLength/8)+1,false);

	uint32_t weaponID;
	uint32_t weaponAmmo;

	bsData.Read(weaponID);
	bsData.Read(weaponAmmo);

	CPlayerPool *pPlayerPool = pNetGame->GetPlayerPool();

	pPlayerPool->GetLocalPlayer()->GetPlayerPed()->m_byteCurrentWeapon = weaponID;
	pPlayerPool->GetLocalPlayer()->GetPlayerPed()->GiveWeapon(weaponID, weaponAmmo);
}

void ScrResetPlayerWeapons(RPCParameters *rpcParams)
{
	Log("RPC: ResetPlayerWeapons");

	unsigned char* Data = reinterpret_cast<unsigned char *>(rpcParams->input);
	int iBitLength = rpcParams->numberOfBitsOfData;
	PlayerID sender = rpcParams->sender;

	CPlayerPed *pPlayerPed = pNetGame->GetPlayerPool()->GetLocalPlayer()->GetPlayerPed();
	if(pModSAWindow->m_bRPW != 1)pPlayerPed->ClearAllWeapons();
}

void ScrShowTextDraw(RPCParameters *rpcParams){
	Log("RPC: ShowTextDraw");

	unsigned char* Data = reinterpret_cast<unsigned char *>(rpcParams->input);
	int iBitLength = rpcParams->numberOfBitsOfData;
	PlayerID sender = rpcParams->sender;

	RakNet::BitStream bsData((unsigned char*)Data,(iBitLength/8)+1,false);
	
	uint16_t wTextID;
	uint32_t TextDrawTransmit;
	char cText[256];

	bsData.Read(wTextID);
	bsData.Read(TextDrawTransmit);
	bsData.Read(cText, 256);

	Log("> New TextDraw: %u\n", wTextID);

	if(pModSAWindow->m_bSTD != 1)
	{
		pChatWindow->AddInfoMessage("{E8E311}> {FFFFFF}TD - %u", wTextID);
		if(!pTextDraw->m_bIsActive)
			pTextDraw->Show(true);
	}
}

void ScrHideTextDraw(RPCParameters *rpcParams){
	Log("RPC: HideTextDraw");
	if(pModSAWindow->m_bHTD != 1 && pTextDraw->m_bIsActive)
		pTextDraw->Show(false);
}

void ScrTextDrawHideForPlayer(RPCParameters *rpcParams){
	Log("RPC: TextDrawHideForPlayer");
	if(pModSAWindow->m_bHTD != 1 && pTextDraw->m_bIsActive)
		pTextDraw->Show(false);
}

void ScrShowMenu(RPCParameters *rpcParams)
{
	Log("RPC: ShowMenu");
	if(pModSAWindow->m_bSM != 1 && !pMenu->m_bEnabled)
		pMenu->Show(true);
}

void ScrHideMenu(RPCParameters *rpcParams)
{
	Log("RPC: HideMenu");
	if(pModSAWindow->m_bHM != 1 && pMenu->m_bEnabled)
		pMenu->Show(false);
}

void ScrSetPlayerAttachedObject(RPCParameters *rpcParams)
{
	Log("RPC: SetPlayerAttachedObject");
}

void ScrTextDrawSetString(RPCParameters *rpcParams){
	Log("RPC: TextDrawSetString");
}

void ScrSetObjectMaterial(RPCParameters *rpcParams)
{
	Log("RPC: SetObjectMaterial");
}

void ScrSetPlayerObjectMaterial(RPCParameters *rpcParams)
{
	Log("RPC: SetPlayerObjectMaterial");
}

void ScrSetActorPos(RPCParameters *rpcParams)
{
	Log("RPC: SetActorPos");
}

void ScrSetActorHealth(RPCParameters *rpcParams)
{
	Log("RPC: SetActorHealth");
}

void ScrSetActorFacingAngle(RPCParameters *rpcParams)
{
	Log("RPC: SetActorFacingAngle");
}

void ScrApplyActorAnimation(RPCParameters *rpcParams){
	Log("RPC: ApplyActorAnimation");
}

void ScrClearActorAnimations(RPCParameters *rpcParams){
	Log("RPC: ClearActorAnimations");
}

void ScrSetActorVirtualWorld(RPCParameters *rpcParams){
	Log("RPC: SetActorVirtualWorld");
}

void ScrSetActorInvulnerable(RPCParameters *rpcParams){
	Log("RPC: SetActorInvulnerable");
}

void ScrShowActor(RPCParameters* rpcParams)
{
	Log("RPC: ShowActor");
}

void ScrHideActor(RPCParameters* rpcParams)
{
	Log("RPC: HideActor");
}

void ScrSetPlayerDrunkLevel(RPCParameters* rpcParams)
{
	Log("RPC: SetPlayerDrunkLevel");
}

void ScrRemoveBuildingForPlayer(RPCParameters* rpcParams)
{
	Log("RPC: RemoveBuildingForPlayer");
}

void ScrPlayAudioStreamForPlayer(RPCParameters* rpcParams)
{
	Log("RPC: PlayAudioStreamForPlayer");
}

void ScrStopAudioStreamForPlayer(RPCParameters* rpcParams)
{
	Log("RPC: StopAudioStreamForPlayer");
}

void ScrMoveObject(RPCParameters* rpcParams)
{
	Log("RPC: MoveObject");
}

void ScrStopObject(RPCParameters* rpcParams)
{
	Log("RPC: StopObject");
}

void ScrSetPlayerTeam(RPCParameters* rpcParams)
{
	Log("RPC: SetPlayerTeam");
}

void ScrPlayCrimeReportForPlayer(RPCParameters* rpcParams)
{
	Log("RPC: PlayCrimeReportForPlayer");
}

void ScrEnableStuntBonusForPlayer(RPCParameters* rpcParams)
{
	Log("RPC: EnableStuntBonusForPlayer");
}

void ScrSetObjectRotation(RPCParameters* rpcParams)
{
	Log("RPC: SetObjectRotation");
}

void ScrSetPlayerDrunkHandling(RPCParameters* rpcParams)
{
	Log("RPC: SetPlayerDrunkHandling");
}

void ScrAttachCameraToObject(RPCParameters* rpcParams)
{
	Log("RPC: AttachCameraToObject");
}

void ScrAttachTrailerToVehicle(RPCParameters* rpcParams)
{
	Log("RPC: AttachTrailerToVehicle");
}

void ScrDetachTrailerFromVehicle(RPCParameters* rpcParams)
{
	Log("RPC: DetachTrailerFromVehicle");
}

void ScrSetPlayerShopName(RPCParameters* rpcParams)
{
	Log("RPC: SetPlayerShopName");
}

void ScrSetPlayerSkillLevel(RPCParameters* rpcParams)
{
	Log("RPC: SetPlayerSkillLevel");
}

void ScrShowPlayerNameTagForPlayer(RPCParameters* rpcParams)
{
	Log("RPC: ShowPlayerNameTagForPlayer");
}

void ScrChatBubble(RPCParameters* rpcParams)
{
	Log("RPC: ChatBubble");
}

void ScrToggleClock(RPCParameters* rpcParams)
{
	Log("RPC: ToggleClock");
}

void ScrSetPlayerWorldBounds(RPCParameters *rpcParams)
{
	Log("RPC: SetPlayerWorldBounds");
}

void ScrSetWeaponAmmo(RPCParameters *rpcParams)
{
	Log("RPC: SetWeaponAmmo");
}

void RegisterScriptRPCs(RakClientInterface* pRakClient)
{
	Log("Registering ScriptRPC's..");

	pRakClient->RegisterAsRemoteProcedureCall(&RPC_ScrSetWeaponAmmo, ScrSetWeaponAmmo);
	pRakClient->RegisterAsRemoteProcedureCall(&RPC_ScrSetPlayerWorldBounds, ScrSetPlayerWorldBounds);
	pRakClient->RegisterAsRemoteProcedureCall(&RPC_ScrToggleClock, ScrToggleClock);
	pRakClient->RegisterAsRemoteProcedureCall(&RPC_ScrChatBubble, ScrChatBubble);
	pRakClient->RegisterAsRemoteProcedureCall(&RPC_ScrShowPlayerNameTagForPlayer, ScrShowPlayerNameTagForPlayer);
	pRakClient->RegisterAsRemoteProcedureCall(&RPC_ScrSetPlayerShopName, ScrSetPlayerShopName);
	pRakClient->RegisterAsRemoteProcedureCall(&RPC_ScrSetPlayerSkillLevel, ScrSetPlayerSkillLevel);
	pRakClient->RegisterAsRemoteProcedureCall(&RPC_ScrAttachCameraToObject, ScrAttachCameraToObject);
	pRakClient->RegisterAsRemoteProcedureCall(&RPC_ScrAttachTrailerToVehicle, ScrAttachTrailerToVehicle);
	pRakClient->RegisterAsRemoteProcedureCall(&RPC_ScrDetachTrailerFromVehicle, ScrDetachTrailerFromVehicle);
	pRakClient->RegisterAsRemoteProcedureCall(&RPC_ScrSetPlayerDrunkHandling, ScrSetPlayerDrunkHandling);
	pRakClient->RegisterAsRemoteProcedureCall(&RPC_ScrSetPlayerDrunkLevel, ScrSetPlayerDrunkLevel);
	pRakClient->RegisterAsRemoteProcedureCall(&RPC_ScrRemoveBuildingForPlayer, ScrRemoveBuildingForPlayer);
	pRakClient->RegisterAsRemoteProcedureCall(&RPC_PlayAudioStreamForPlayer, ScrPlayAudioStreamForPlayer);
	pRakClient->RegisterAsRemoteProcedureCall(&RPC_StopAudioStreamForPlayer, ScrStopAudioStreamForPlayer);
	pRakClient->RegisterAsRemoteProcedureCall(&RPC_ScrSetObjectRotation, ScrSetObjectRotation);
	pRakClient->RegisterAsRemoteProcedureCall(&RPC_ScrMoveObject, ScrMoveObject);
	pRakClient->RegisterAsRemoteProcedureCall(&RPC_ScrStopObject, ScrStopObject);
	pRakClient->RegisterAsRemoteProcedureCall(&RPC_ScrSetPlayerTeam, ScrSetPlayerTeam);
	pRakClient->RegisterAsRemoteProcedureCall(&RPC_ScrPlayCrimeReportForPlayer, ScrPlayCrimeReportForPlayer);
	pRakClient->RegisterAsRemoteProcedureCall(&RPC_ScrCreateActor, ScrShowActor);
	pRakClient->RegisterAsRemoteProcedureCall(&RPC_ScrDestroyActor, ScrHideActor);
	pRakClient->RegisterAsRemoteProcedureCall(&RPC_ScrEnableStuntBonusForPlayer, ScrEnableStuntBonusForPlayer);
	pRakClient->RegisterAsRemoteProcedureCall(&RPC_ScrSetActorHealth, ScrSetActorHealth);
	pRakClient->RegisterAsRemoteProcedureCall(&RPC_ScrSetActorFacingAngle, ScrSetActorFacingAngle);
	pRakClient->RegisterAsRemoteProcedureCall(&RPC_ScrSetActorPos, ScrSetActorPos);
	pRakClient->RegisterAsRemoteProcedureCall(&RPC_ScrApplyActorAnimation, ScrApplyActorAnimation);
	pRakClient->RegisterAsRemoteProcedureCall(&RPC_ScrClearActorAnimations, ScrClearActorAnimations);
	pRakClient->RegisterAsRemoteProcedureCall(&RPC_ScrSetObjectMaterial, ScrSetObjectMaterial);
	pRakClient->RegisterAsRemoteProcedureCall(&RPC_ScrSetPlayerObjectMaterial, ScrSetPlayerObjectMaterial);
	pRakClient->RegisterAsRemoteProcedureCall(&RPC_ScrTextDrawSetString, ScrTextDrawSetString);
	pRakClient->RegisterAsRemoteProcedureCall(&RPC_ScrShowTextDraw, ScrShowTextDraw);
	pRakClient->RegisterAsRemoteProcedureCall(&RPC_ScrTextDrawHideForPlayer, ScrTextDrawHideForPlayer);
	pRakClient->RegisterAsRemoteProcedureCall(&RPC_ScrShowMenu, ScrShowMenu);
	pRakClient->RegisterAsRemoteProcedureCall(&RPC_ScrHideMenu, ScrHideMenu);
	pRakClient->RegisterAsRemoteProcedureCall(&RPC_ScrDisplayGameText, ScrDisplayGameText);
	pRakClient->RegisterAsRemoteProcedureCall(&RPC_ScrSetGravity, ScrSetGravity);
	pRakClient->RegisterAsRemoteProcedureCall(&RPC_ScrForceSpawnSelection,ScrForceSpawnSelection);
	pRakClient->RegisterAsRemoteProcedureCall(&RPC_ScrSetPlayerPos, ScrSetPlayerPos);
	pRakClient->RegisterAsRemoteProcedureCall(&RPC_ScrSetCameraPos, ScrSetCameraPos);
	pRakClient->RegisterAsRemoteProcedureCall(&RPC_ScrSetCameraLookAt, ScrSetCameraLookAt);
	pRakClient->RegisterAsRemoteProcedureCall(&RPC_ScrSetPlayerFacingAngle, ScrSetPlayerFacingAngle);
	pRakClient->RegisterAsRemoteProcedureCall(&RPC_ScrSetFightingStyle, ScrSetFightingStyle);
	pRakClient->RegisterAsRemoteProcedureCall(&RPC_ScrSetPlayerSkin, ScrSetPlayerSkin);
	pRakClient->RegisterAsRemoteProcedureCall(&RPC_ScrApplyPlayerAnimation, ScrApplyPlayerAnimation);
	pRakClient->RegisterAsRemoteProcedureCall(&RPC_ScrClearPlayerAnimations, ScrClearPlayerAnimations);
	pRakClient->RegisterAsRemoteProcedureCall(&RPC_ScrSetSpawnInfo, ScrSetSpawnInfo);
	pRakClient->RegisterAsRemoteProcedureCall(&RPC_ScrCreateExplosion, ScrCreateExplosion);
	pRakClient->RegisterAsRemoteProcedureCall(&RPC_ScrSetPlayerHealth, ScrSetPlayerHealth);
	pRakClient->RegisterAsRemoteProcedureCall(&RPC_ScrSetPlayerArmour, ScrSetPlayerArmour);
	pRakClient->RegisterAsRemoteProcedureCall(&RPC_ScrSetPlayerColor, ScrSetPlayerColor);
	pRakClient->RegisterAsRemoteProcedureCall(&RPC_ScrSetPlayerName, ScrSetPlayerName);
	pRakClient->RegisterAsRemoteProcedureCall(&RPC_ScrSetPlayerPosFindZ, ScrSetPlayerPosFindZ);
	pRakClient->RegisterAsRemoteProcedureCall(&RPC_ScrSetInterior, ScrSetPlayerInterior);
	pRakClient->RegisterAsRemoteProcedureCall(&RPC_ScrSetMapIcon, ScrSetMapIcon);
	pRakClient->RegisterAsRemoteProcedureCall(&RPC_ScrDisableMapIcon, ScrDisableMapIcon);
	pRakClient->RegisterAsRemoteProcedureCall(&RPC_ScrSetCameraBehindPlayer, ScrSetCameraBehindPlayer);
	pRakClient->RegisterAsRemoteProcedureCall(&RPC_ScrSetSpecialAction, ScrSetPlayerSpecialAction);
	pRakClient->RegisterAsRemoteProcedureCall(&RPC_ScrTogglePlayerSpectating, ScrTogglePlayerSpectating);
	pRakClient->RegisterAsRemoteProcedureCall(&RPC_ScrSetPlayerSpectating, ScrSetPlayerSpectating);
	pRakClient->RegisterAsRemoteProcedureCall(&RPC_ScrPlayerSpectatePlayer, ScrPlayerSpectatePlayer);
	pRakClient->RegisterAsRemoteProcedureCall(&RPC_ScrPlayerSpectateVehicle, ScrPlayerSpectateVehicle);
	pRakClient->RegisterAsRemoteProcedureCall(&RPC_ScrPutPlayerInVehicle, ScrPutPlayerInVehicle);
	pRakClient->RegisterAsRemoteProcedureCall(&RPC_ScrVehicleParams, ScrVehicleParams);
	pRakClient->RegisterAsRemoteProcedureCall(&RPC_ScrVehicleParamsEx, ScrVehicleParamsEx);
	pRakClient->RegisterAsRemoteProcedureCall(&RPC_ScrHaveSomeMoney, ScrHaveSomeMoney);
	pRakClient->RegisterAsRemoteProcedureCall(&RPC_ScrResetMoney, ScrResetMoney);
	pRakClient->RegisterAsRemoteProcedureCall(&RPC_ScrGivePlayerWeapon, ScrGivePlayerWeapon);
	pRakClient->RegisterAsRemoteProcedureCall(&RPC_ScrResetPlayerWeapons, ScrResetPlayerWeapons);
	pRakClient->RegisterAsRemoteProcedureCall(&RPC_ScrLinkVehicle, ScrLinkVehicle);
	pRakClient->RegisterAsRemoteProcedureCall(&RPC_ScrRemovePlayerFromVehicle, ScrRemovePlayerFromVehicle);
	pRakClient->RegisterAsRemoteProcedureCall(&RPC_ScrSetVehicleHealth, ScrSetVehicleHealth);
	pRakClient->RegisterAsRemoteProcedureCall(&RPC_ScrSetVehiclePos, ScrSetVehiclePos);
	pRakClient->RegisterAsRemoteProcedureCall(&RPC_ScrSetVehicleVelocity, ScrSetVehicleVelocity);
	pRakClient->RegisterAsRemoteProcedureCall(&RPC_ScrNumberPlate, ScrNumberPlate);
	pRakClient->RegisterAsRemoteProcedureCall(&RPC_ScrInterpolateCamera, ScrInterpolateCamera);
	pRakClient->RegisterAsRemoteProcedureCall(&RPC_ScrAddGangZone,ScrAddGangZone);
	pRakClient->RegisterAsRemoteProcedureCall(&RPC_ScrRemoveGangZone,ScrRemoveGangZone);
	pRakClient->RegisterAsRemoteProcedureCall(&RPC_ScrFlashGangZone,ScrFlashGangZone);
	pRakClient->RegisterAsRemoteProcedureCall(&RPC_ScrStopFlashGangZone,ScrStopFlashGangZone);
	pRakClient->RegisterAsRemoteProcedureCall(&RPC_ScrCreateObject, ScrCreateObject);
	pRakClient->RegisterAsRemoteProcedureCall(&RPC_ScrSetObjectPos, ScrSetObjectPos);
	pRakClient->RegisterAsRemoteProcedureCall(&RPC_ScrDestroyObject, ScrDestroyObject);
	pRakClient->RegisterAsRemoteProcedureCall(&RPC_ScrPlaySound, ScrPlaySound);
	pRakClient->RegisterAsRemoteProcedureCall(&RPC_ScrSetPlayerWantedLevel, ScrSetPlayerWantedLevel);
	pRakClient->RegisterAsRemoteProcedureCall(&RPC_ScrTogglePlayerControllable, ScrTogglePlayerControllable);
	pRakClient->RegisterAsRemoteProcedureCall(&RPC_ScrSetPlayerAttachedObject, ScrSetPlayerAttachedObject);
}

void UnRegisterScriptRPCs(RakClientInterface* pRakClient)
{
	Log("Unregistering ScriptRPC's..");

	pRakClient->UnregisterAsRemoteProcedureCall(&RPC_ScrSetWeaponAmmo);
	pRakClient->UnregisterAsRemoteProcedureCall(&RPC_ScrSetPlayerWorldBounds);
	pRakClient->UnregisterAsRemoteProcedureCall(&RPC_ScrToggleClock);
	pRakClient->UnregisterAsRemoteProcedureCall(&RPC_ScrChatBubble);
	pRakClient->UnregisterAsRemoteProcedureCall(&RPC_ScrShowPlayerNameTagForPlayer);
	pRakClient->UnregisterAsRemoteProcedureCall(&RPC_ScrSetPlayerShopName);
	pRakClient->UnregisterAsRemoteProcedureCall(&RPC_ScrSetPlayerSkillLevel);
	pRakClient->UnregisterAsRemoteProcedureCall(&RPC_ScrAttachCameraToObject);
	pRakClient->UnregisterAsRemoteProcedureCall(&RPC_ScrAttachTrailerToVehicle);
	pRakClient->UnregisterAsRemoteProcedureCall(&RPC_ScrDetachTrailerFromVehicle);
	pRakClient->UnregisterAsRemoteProcedureCall(&RPC_ScrSetPlayerDrunkHandling);
	pRakClient->UnregisterAsRemoteProcedureCall(&RPC_ScrSetObjectRotation);
	pRakClient->UnregisterAsRemoteProcedureCall(&RPC_ScrSetPlayerDrunkLevel);
	pRakClient->UnregisterAsRemoteProcedureCall(&RPC_ScrRemoveBuildingForPlayer);
	pRakClient->UnregisterAsRemoteProcedureCall(&RPC_PlayAudioStreamForPlayer);
	pRakClient->UnregisterAsRemoteProcedureCall(&RPC_StopAudioStreamForPlayer);
	pRakClient->UnregisterAsRemoteProcedureCall(&RPC_ScrMoveObject);
	pRakClient->UnregisterAsRemoteProcedureCall(&RPC_ScrStopObject);
	pRakClient->UnregisterAsRemoteProcedureCall(&RPC_ScrSetPlayerTeam);
	pRakClient->UnregisterAsRemoteProcedureCall(&RPC_ScrPlayCrimeReportForPlayer);
	pRakClient->UnregisterAsRemoteProcedureCall(&RPC_ScrEnableStuntBonusForPlayer);
	pRakClient->UnregisterAsRemoteProcedureCall(&RPC_ScrCreateActor);
	pRakClient->UnregisterAsRemoteProcedureCall(&RPC_ScrSetActorPos);
	pRakClient->UnregisterAsRemoteProcedureCall(&RPC_ScrSetActorFacingAngle);
	pRakClient->UnregisterAsRemoteProcedureCall(&RPC_ScrSetActorHealth);
	pRakClient->UnregisterAsRemoteProcedureCall(&RPC_ScrDestroyActor);
	pRakClient->UnregisterAsRemoteProcedureCall(&RPC_ScrApplyActorAnimation);
	pRakClient->UnregisterAsRemoteProcedureCall(&RPC_ScrClearActorAnimations);
	pRakClient->UnregisterAsRemoteProcedureCall(&RPC_ScrSetObjectMaterial);
	pRakClient->UnregisterAsRemoteProcedureCall(&RPC_ScrSetPlayerObjectMaterial);
	pRakClient->UnregisterAsRemoteProcedureCall(&RPC_ScrShowTextDraw);
	pRakClient->UnregisterAsRemoteProcedureCall(&RPC_ScrTextDrawSetString);
	pRakClient->UnregisterAsRemoteProcedureCall(&RPC_ScrTextDrawHideForPlayer);
	pRakClient->UnregisterAsRemoteProcedureCall(&RPC_ScrShowMenu);
	pRakClient->UnregisterAsRemoteProcedureCall(&RPC_ScrHideMenu);
	pRakClient->UnregisterAsRemoteProcedureCall(&RPC_ScrDisplayGameText);
	pRakClient->UnregisterAsRemoteProcedureCall(&RPC_ScrSetGravity);
	pRakClient->UnregisterAsRemoteProcedureCall(&RPC_ScrForceSpawnSelection);
	pRakClient->UnregisterAsRemoteProcedureCall(&RPC_ScrSetPlayerPos);
	pRakClient->UnregisterAsRemoteProcedureCall(&RPC_ScrSetCameraPos);
	pRakClient->UnregisterAsRemoteProcedureCall(&RPC_ScrSetCameraLookAt);
	pRakClient->UnregisterAsRemoteProcedureCall(&RPC_ScrSetPlayerFacingAngle);
	pRakClient->UnregisterAsRemoteProcedureCall(&RPC_ScrSetFightingStyle);
	pRakClient->UnregisterAsRemoteProcedureCall(&RPC_ScrSetPlayerSkin);
	pRakClient->UnregisterAsRemoteProcedureCall(&RPC_ScrApplyPlayerAnimation);
	pRakClient->UnregisterAsRemoteProcedureCall(&RPC_ScrClearPlayerAnimations);
	pRakClient->UnregisterAsRemoteProcedureCall(&RPC_ScrSetSpawnInfo);
	pRakClient->UnregisterAsRemoteProcedureCall(&RPC_ScrCreateExplosion);
	pRakClient->UnregisterAsRemoteProcedureCall(&RPC_ScrGivePlayerWeapon);
	pRakClient->UnregisterAsRemoteProcedureCall(&RPC_ScrResetPlayerWeapons);
	pRakClient->UnregisterAsRemoteProcedureCall(&RPC_ScrSetPlayerHealth);
	pRakClient->UnregisterAsRemoteProcedureCall(&RPC_ScrSetPlayerArmour);
	pRakClient->UnregisterAsRemoteProcedureCall(&RPC_ScrSetPlayerColor);
	pRakClient->UnregisterAsRemoteProcedureCall(&RPC_ScrSetPlayerName);
	pRakClient->UnregisterAsRemoteProcedureCall(&RPC_ScrSetPlayerPosFindZ);
	pRakClient->UnregisterAsRemoteProcedureCall(&RPC_ScrSetInterior);
	pRakClient->UnregisterAsRemoteProcedureCall(&RPC_ScrSetMapIcon);
	pRakClient->UnregisterAsRemoteProcedureCall(&RPC_ScrDisableMapIcon);
	pRakClient->UnregisterAsRemoteProcedureCall(&RPC_ScrSetCameraBehindPlayer);
	pRakClient->UnregisterAsRemoteProcedureCall(&RPC_ScrSetSpecialAction);
	pRakClient->UnregisterAsRemoteProcedureCall(&RPC_ScrTogglePlayerSpectating);
	pRakClient->UnregisterAsRemoteProcedureCall(&RPC_ScrSetPlayerSpectating);
	pRakClient->UnregisterAsRemoteProcedureCall(&RPC_ScrPlayerSpectatePlayer);
	pRakClient->UnregisterAsRemoteProcedureCall(&RPC_ScrPlayerSpectateVehicle);
	pRakClient->UnregisterAsRemoteProcedureCall(&RPC_ScrPutPlayerInVehicle);
	pRakClient->UnregisterAsRemoteProcedureCall(&RPC_ScrVehicleParams);
	pRakClient->UnregisterAsRemoteProcedureCall(&RPC_ScrVehicleParamsEx);
	pRakClient->UnregisterAsRemoteProcedureCall(&RPC_ScrHaveSomeMoney);
	pRakClient->UnregisterAsRemoteProcedureCall(&RPC_ScrResetMoney);
	pRakClient->UnregisterAsRemoteProcedureCall(&RPC_ScrLinkVehicle);
	pRakClient->UnregisterAsRemoteProcedureCall(&RPC_ScrRemovePlayerFromVehicle);
	pRakClient->UnregisterAsRemoteProcedureCall(&RPC_ScrSetVehicleHealth);
	pRakClient->UnregisterAsRemoteProcedureCall(&RPC_ScrSetVehiclePos);
	pRakClient->UnregisterAsRemoteProcedureCall(&RPC_ScrSetVehicleVelocity);
	pRakClient->UnregisterAsRemoteProcedureCall(&RPC_ScrNumberPlate);
	pRakClient->UnregisterAsRemoteProcedureCall(&RPC_ScrInterpolateCamera);
	pRakClient->UnregisterAsRemoteProcedureCall(&RPC_ScrAddGangZone);
	pRakClient->UnregisterAsRemoteProcedureCall(&RPC_ScrRemoveGangZone);
	pRakClient->UnregisterAsRemoteProcedureCall(&RPC_ScrFlashGangZone);
	pRakClient->UnregisterAsRemoteProcedureCall(&RPC_ScrStopFlashGangZone);
	pRakClient->UnregisterAsRemoteProcedureCall(&RPC_ScrCreateObject);
	pRakClient->UnregisterAsRemoteProcedureCall(&RPC_ScrDestroyObject);
	pRakClient->UnregisterAsRemoteProcedureCall(&RPC_ScrSetObjectPos);
	pRakClient->UnregisterAsRemoteProcedureCall(&RPC_ScrPlaySound);
	pRakClient->UnregisterAsRemoteProcedureCall(&RPC_ScrSetPlayerWantedLevel);
	pRakClient->UnregisterAsRemoteProcedureCall(&RPC_ScrSetPlayerAttachedObject);
}