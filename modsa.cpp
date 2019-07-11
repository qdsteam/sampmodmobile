/*
    * m0d_SA Mobile v0.0.0.4
    *
    * Authors - QDS Team
    * YouTube - https://www.youtube.com/Quildeesaw
    * Community - https://vk.com/quildeesaw
    * Source - https://github.com/qdsteam/m0d_SA_Mobile
*/

#include "main.h"
#include "game/game.h"
#include "net/netgame.h"
#include "game/common.h"
#include "gui/gui.h"
#include "modsa.h"
#include "vendor/imgui/imgui_internal.h"
#include "keyboard.h"
#include "chatwindow.h"
#include "net/vehiclepool.h"
#include <stdlib.h>
#include <string.h>
#include "timer.hpp"
#include "game/vehicle.h"
#include "net/vehiclepool.h"
#include "net/playerpool.h"
#include "net/localplayer.h"
#include "extrakeyboard.h"

extern CGUI *pGUI;
extern CGame *pGame;
extern CNetGame *pNetGame;
extern CKeyBoard *pKeyBoard;
extern CChatWindow *pChatWindow;

CModSAWindow::CModSAWindow()
{
	m_bIsActive = false;
    m_bMenuStep = 0;
    if(m_bGodMode != 1)
        m_bGodMode = 0;
    if(m_bWallHack != 1)
        m_bWallHack = 0;
    if(m_bCols != 1)
        m_bCols = 0;
    if(m_bVP != 1)
        m_bVP = 0;
    if(m_bVP2 != 1)
        m_bVP2 = 0;
    if(m_bVV != 1)
        m_bVV = 0;
    if(m_bCO != 1)
        m_bCO = 0;
    if(m_bPH != 1)
        m_bPH = 0;
    if(m_bINVIS != 1)
        m_bINVIS = 0;
    if(lockinp != 1)
        lockinp = 0;
    if(m_bRPFV != 1)
        m_bRPFV = 0;
    if(m_bSD != 1)
        m_bSD = 0;
    if(m_bAPA != 1)
        m_bAPA = 0;
    if(m_bRPW != 1)
        m_bRPW = 0;
    if(m_bCP != 1)
        m_bCP = 0;
    if(m_bCP2 != 1)
        m_bCP2 = 0;
    if(m_bNF != 1)
        m_bNF = 0;
    if(m_bGCW != 1)
        m_bGCW = 0;
    if(m_bCA != 1)
        m_bCA = 0;
    if(m_bSPP != 1)
        m_bSPP = 0;
    if(m_bGPP != 1)
        m_bGPP = 0;
    if(m_bCTL != 1)
        m_bCTL = 0;
    if(m_bEV != 1)
        m_bEV = 0;
    if(rxyz != 1)
        rxyz = 0;
    if(flock != 1)
        flock = 0;
    if(m_bKrutilka != 1)
        m_bKrutilka = 0;
    if(marker_X != 1)
        marker_X = 0;
    if(marker_Y != 1)
        marker_Y = 0;
    if(marker_Z != 1)
        marker_Z = 0;
    if(fDist == NULL)
        fDist = 0.7;
    if(protect == NULL)
        protect = 0;
    if(lock_weather != 1)
        lock_weather = 0;
    if(lock_time != 1)
        lock_time = 0;
    if(zbot_reps == NULL)
        zbot_reps = 10;
    if(m_bot != 1)
        m_bot = 0;
    if(extOS != 1)
        extOS = 0;
    if(m_bFLASH != 1)
        m_bFLASH = 0;
    if(m_bCE != 1)
        m_bCE = 0;
    if(m_bSPN != 1)
        m_bSPN = 0;
    if(m_bAGZ != 1)
        m_bAGZ = 0;
    if(m_bTPC != 1)
        m_bTPC = 0;
    if(m_bSTD != 1)
        m_bSTD = 0;
    if(m_bHTD != 1)
        m_bHTD = 0;
    if(m_bSM != 1)
        m_bSM = 0;
    if(m_bHM != 1)
        m_bHM = 0;
    if(m_bSG != 1)
        m_bSG = 0;
    if(m_clock != 1)
        m_clock = 0;
    if(m_bSPS != 1)
        m_bSPS = 0;
    if(radar != 1)
        radar = 0;
    if(fastfire != 1)
        fastfire = 0;
    if(carvisible != 1)
        carvisible = 0;
    if(m_bAirbreak != 1)
        m_bAirbreak = 0;
    if(curAnim != 1)
        curAnim = 0;
    if(dnames != 1)
        dnames = 0;
    if(players != 1)
        players = 0;
}

CModSAWindow::~CModSAWindow()
{

}

void CModSAWindow::Show(bool bShow)
{
    if(pGame && protect != 1)
        pGame->FindPlayerPed()->TogglePlayerControllableWithoutLock(!bShow);
	m_bIsActive = bShow;
}

void CModSAWindow::Clear()
{
	m_bIsActive = false;
    m_bMenuStep = 0;
    m_bGodMode = 0;
    m_bWallHack = 0;
    m_bCols = 0;
    m_bVP = 0;
    m_bVP2 = 0;
    m_bVV = 0;
    m_bCO = 0;
    m_bPH = 0;
    players = 0;
    lockinp = 0;
    flock = 0;
    m_bRPFV = 0;
    m_bSD = 0;
    m_bAPA = 0;
    m_bRPW = 0;
    m_bCP = 0;
    m_bCP2 = 0;
    m_bNF = 0;
    dnames = 0;
    m_bAGZ = 0;
    m_bGCW = 0;
    curAnim = 0;
    m_bTPC = 0;
    m_bCA = 0;
    m_bSPP = 0;
    sPos1X = 0;
    sPos1Y = 0;
    sPos1Z = 0;
    sPos2X = 0;
    sPos2Y = 0;
    sPos2Z = 0;
    sPos3X = 0;
    sPos3Y = 0;
    sPos3Z = 0;
    m_bINVIS = 0;
    m_bGPP = 0;
    radar = 0;
    m_bCTL = 0;
    m_bKrutilka = 0;
    fastfire = 0;
    carvisible = 0;
    m_bFLASH = 0;
    m_bAirbreak = 0;
    m_bCE = 0;
    m_bSG = 0;
    m_clock = 0;
    rxyz = 0;
    marker_X = 0;
    marker_Y = 0;
    marker_Z = 0;
    fDist = 0.7;
    lock_weather = 0;
    lock_time = 0;
    zbot_reps = 10;
    m_bot = 0;
    m_bEV = 0;
    extOS = 0;
    m_bSPN = 0;
    m_bSTD = 0;
    m_bHTD = 0;
    m_bSM = 0;
    m_bHM = 0;
    m_bSPS = 0;
}


void CModSAWindow::StoreMarkerXYZ(float x, float y, float z)
{
    marker_X = x; // X
    marker_Y = y; // Y
    marker_Z = z; // Z

    //pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}Marker on X: %f Y: %f Z: %f", marker_X, marker_Y, marker_Z);
}

void CModSAWindow::SetFlySets(float distance)
{
    fDist = distance;
}

float CModSAWindow::GetFlySets()
{
    return (float)fDist;
}

void CModSAWindow::ZavodBotTemp(int stepId)
{
    // допилить
}

void CModSAWindow::StartBotById(int id)
{
   // допилить
}

void CModSAWindow::ShowFlyMenu(bool bShow)
{
    if(!bShow)return;

    pGUI->m_fly = 1;

    ImGui::Text("Speed (default: 0.7)");

    if(ImGui::Button("Add", ImVec2(80, 50)))
    {
        MATRIX4X4 mat;
        pGame->FindPlayerPed()->GetMatrix(&mat);
        pGame->PlaySound(1053, mat.pos.X, mat.pos.Y, mat.pos.Z);
        SetFlySets((GetFlySets() + 0.1));
        //pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}Set distance to %f", GetFlySets());
        char str[4096];
        sprintf(str, "%f ~<~~<~~<~~<~~n~~n~~n~", GetFlySets());
        pGame->DisplayGameText(str, 1750, 3);
    }

    ImGui::SameLine(0, pGUI->GetFontSize());

    if(ImGui::Button("Del", ImVec2(80, 50)))
    {
        MATRIX4X4 mat;
        pGame->FindPlayerPed()->GetMatrix(&mat);
        pGame->PlaySound(1053, mat.pos.X, mat.pos.Y, mat.pos.Z);
        SetFlySets((GetFlySets() - 0.1));
        //pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}Set distance to %f", GetFlySets());
        char str[4096];
        sprintf(str, "%f ~<~~<~~<~~<~~n~~n~~n~", GetFlySets());
        pGame->DisplayGameText(str, 1750, 3);
    }

    // ---------------------------------------------- //
    ImGui::ItemSize( ImVec2(0, pGUI->GetFontSize()/2 + 5) );
    ImGui::Text("Functions");

    MATRIX4X4 mat;
    pGame->FindPlayerPed()->GetMatrix(&mat);

    pGame->SetGravity(0.000005);

    VECTOR vecMoveSpeed;
    if(GetFlySets() <= 0.7)pGame->FindPlayerPed()->ApplyAnimation("DEALER_IDLE", "DEALER", 9.1, 1, 0, 0, 1, 1);
    if(GetFlySets() > 0.7)pGame->FindPlayerPed()->ApplyAnimation("FALL_SKYDIVE_ACCEL", "PARACHUTE", 4.1, 1, 0, 0, 1, 1);

    if(ImGui::Button("FRONT", ImVec2(100, 50)))
    {
        MATRIX4X4 mat;
        pGame->FindPlayerPed()->GetMatrix(&mat);
        pGame->PlaySound(1053, mat.pos.X, mat.pos.Y, mat.pos.Z);
        pGame->FindPlayerPed()->ForceTargetRotation(352.46);
        if(!pGame->FindPlayerPed()->IsInVehicle()){
            vecMoveSpeed.X = 0.0f;
            vecMoveSpeed.Y = GetFlySets();
            vecMoveSpeed.Z = 0.0f;
            pGame->FindPlayerPed()->SetMoveSpeedVector(vecMoveSpeed);
        }else{
            ScriptCommand(&set_car_z_angle, pGame->FindPlayerPed()->GetCurrentVehicleID(), 352.46);
            ScriptCommand(&set_car_coordinates, pGame->FindPlayerPed()->GetCurrentVehicleID(), mat.pos.X, mat.pos.Y + GetFlySets(), mat.pos.Z);
        }
        pGame->GetCamera()->SetBehindPlayer();  
    }

    ImGui::SameLine(0, pGUI->GetFontSize());

    if(ImGui::Button("BACK", ImVec2(100, 50)))
    {
        MATRIX4X4 mat;
        pGame->FindPlayerPed()->GetMatrix(&mat);
        pGame->PlaySound(1053, mat.pos.X, mat.pos.Y, mat.pos.Z);
        pGame->FindPlayerPed()->ForceTargetRotation(172.46);
        if(!pGame->FindPlayerPed()->IsInVehicle()){
            vecMoveSpeed.X = 0.0f;
            vecMoveSpeed.Y -= GetFlySets();
            vecMoveSpeed.Z = 0.0f;
            pGame->FindPlayerPed()->SetMoveSpeedVector(vecMoveSpeed);
        }else{
            ScriptCommand(&set_car_z_angle, pGame->FindPlayerPed()->GetCurrentVehicleID(), 172.46);
            ScriptCommand(&set_car_coordinates, pGame->FindPlayerPed()->GetCurrentVehicleID(), mat.pos.X, mat.pos.Y - GetFlySets(), mat.pos.Z);
        }
        pGame->GetCamera()->SetBehindPlayer();  
    }

    // ---------------------------------------------- //
    ImGui::ItemSize( ImVec2(0, pGUI->GetFontSize()/2 + 2.5) );

    if(ImGui::Button("UP", ImVec2(100, 50)))
    {
        MATRIX4X4 mat;
        pGame->FindPlayerPed()->GetMatrix(&mat);
        pGame->PlaySound(1053, mat.pos.X, mat.pos.Y, mat.pos.Z);
        if(!pGame->FindPlayerPed()->IsInVehicle()){
            vecMoveSpeed.X = 0.0f;
            vecMoveSpeed.Y = 0.0;
            vecMoveSpeed.Z += (GetFlySets() / 2);
            pGame->FindPlayerPed()->SetMoveSpeedVector(vecMoveSpeed);
            //pGame->FindPlayerPed()->TeleportTo(mat.pos.X, mat.pos.Y, mat.pos.Z + GetFlySets() * 2.0);
        }else{
            ScriptCommand(&set_car_coordinates, pGame->FindPlayerPed()->GetCurrentVehicleID(), mat.pos.X, mat.pos.Y, mat.pos.Z + GetFlySets());
        }
        pGame->GetCamera()->SetBehindPlayer();  
    }

    ImGui::SameLine(0, pGUI->GetFontSize());

    if(ImGui::Button("DOWN", ImVec2(100, 50)))
    {
        MATRIX4X4 mat;
        pGame->FindPlayerPed()->GetMatrix(&mat);
        pGame->PlaySound(1053, mat.pos.X, mat.pos.Y, mat.pos.Z);
        if(!pGame->FindPlayerPed()->IsInVehicle()){
            vecMoveSpeed.X = 0.0f;
            vecMoveSpeed.Y = 0.0;
            vecMoveSpeed.Z -= (GetFlySets() / 2);
            pGame->FindPlayerPed()->SetMoveSpeedVector(vecMoveSpeed);
            //pGame->FindPlayerPed()->TeleportTo(mat.pos.X, mat.pos.Y, mat.pos.Z - GetFlySets() * 2.0);
        }else{
            ScriptCommand(&set_car_coordinates, pGame->FindPlayerPed()->GetCurrentVehicleID(), mat.pos.X, mat.pos.Y, mat.pos.Z - GetFlySets());
        }
        pGame->GetCamera()->SetBehindPlayer();  
    }

    // ---------------------------------------------- //
    ImGui::ItemSize( ImVec2(0, pGUI->GetFontSize()/2 + 2.5) );

    if(ImGui::Button("LEFT", ImVec2(100, 50)))
    {
        MATRIX4X4 mat;
        pGame->FindPlayerPed()->GetMatrix(&mat);
        pGame->PlaySound(1053, mat.pos.X, mat.pos.Y, mat.pos.Z);
        pGame->FindPlayerPed()->ForceTargetRotation(86.51);
        if(!pGame->FindPlayerPed()->IsInVehicle()){
            vecMoveSpeed.X -= GetFlySets();
            vecMoveSpeed.Y = 0.0f;
            vecMoveSpeed.Z = 0.0f;
            pGame->FindPlayerPed()->SetMoveSpeedVector(vecMoveSpeed);
        }else{
            ScriptCommand(&set_car_z_angle, pGame->FindPlayerPed()->GetCurrentVehicleID(), 85.51);
            ScriptCommand(&set_car_coordinates, pGame->FindPlayerPed()->GetCurrentVehicleID(), mat.pos.X - GetFlySets(), mat.pos.Y, mat.pos.Z);
        }
        pGame->GetCamera()->SetBehindPlayer();  
    }

    ImGui::SameLine(0, pGUI->GetFontSize());

    if(ImGui::Button("RIGHT", ImVec2(100, 50)))
    {
        MATRIX4X4 mat;
        pGame->FindPlayerPed()->GetMatrix(&mat);
        pGame->PlaySound(1053, mat.pos.X, mat.pos.Y, mat.pos.Z);
        pGame->FindPlayerPed()->ForceTargetRotation(266.48);
        if(!pGame->FindPlayerPed()->IsInVehicle()){
            vecMoveSpeed.X = GetFlySets();
            vecMoveSpeed.Y = 0.0f;
            vecMoveSpeed.Z = 0.0f;
            pGame->FindPlayerPed()->SetMoveSpeedVector(vecMoveSpeed);
        }else{
            ScriptCommand(&set_car_z_angle, pGame->FindPlayerPed()->GetCurrentVehicleID(), 266.48);
            ScriptCommand(&set_car_coordinates, pGame->FindPlayerPed()->GetCurrentVehicleID(), mat.pos.X + GetFlySets(), mat.pos.Y, mat.pos.Z);
        }
        pGame->GetCamera()->SetBehindPlayer();  
    }

    // ---------------------------------------------- //
    ImGui::ItemSize( ImVec2(0, pGUI->GetFontSize()/2 + 2.5) );

    if(ImGui::Button("L-B", ImVec2(100, 50)))
    {
        MATRIX4X4 mat;
        pGame->FindPlayerPed()->GetMatrix(&mat);
        pGame->PlaySound(1053, mat.pos.X, mat.pos.Y, mat.pos.Z);
        pGame->FindPlayerPed()->ForceTargetRotation(147.49);
        if(!pGame->FindPlayerPed()->IsInVehicle()){
            vecMoveSpeed.X -= GetFlySets() / 2;
            vecMoveSpeed.Y -= GetFlySets() / 2;
            vecMoveSpeed.Z = 0.0f;
            pGame->FindPlayerPed()->SetMoveSpeedVector(vecMoveSpeed);
        }else{
            ScriptCommand(&set_car_z_angle, pGame->FindPlayerPed()->GetCurrentVehicleID(), 147.49);
            ScriptCommand(&set_car_coordinates, pGame->FindPlayerPed()->GetCurrentVehicleID(), mat.pos.X - GetFlySets(), mat.pos.Y - GetFlySets(), mat.pos.Z);
        }
        pGame->GetCamera()->SetBehindPlayer();  
    }

    ImGui::SameLine(0, pGUI->GetFontSize());

    if(ImGui::Button("R-F", ImVec2(100, 50)))
    {
        MATRIX4X4 mat;
        pGame->FindPlayerPed()->GetMatrix(&mat);
        pGame->PlaySound(1053, mat.pos.X, mat.pos.Y, mat.pos.Z);
        pGame->FindPlayerPed()->ForceTargetRotation(319.07);
        if(!pGame->FindPlayerPed()->IsInVehicle()){
            vecMoveSpeed.X = GetFlySets() / 2;
            vecMoveSpeed.Y = GetFlySets() / 2;
            vecMoveSpeed.Z = 0.0f;
            pGame->FindPlayerPed()->SetMoveSpeedVector(vecMoveSpeed);
        }else{
            ScriptCommand(&set_car_z_angle, pGame->FindPlayerPed()->GetCurrentVehicleID(), 319.07);
            ScriptCommand(&set_car_coordinates, pGame->FindPlayerPed()->GetCurrentVehicleID(), mat.pos.X + GetFlySets(), mat.pos.Y  + GetFlySets(), mat.pos.Z);
        }
        pGame->GetCamera()->SetBehindPlayer();  
    }

    ImGui::ItemSize( ImVec2(0, pGUI->GetFontSize()/2 + 2.5) );

    if(ImGui::Button("R-B", ImVec2(100, 50)))
    {
        MATRIX4X4 mat;
        pGame->FindPlayerPed()->GetMatrix(&mat);
        pGame->PlaySound(1053, mat.pos.X, mat.pos.Y, mat.pos.Z);
        pGame->FindPlayerPed()->ForceTargetRotation(226.99);
        if(!pGame->FindPlayerPed()->IsInVehicle()){
            vecMoveSpeed.X = GetFlySets() / 2;
            vecMoveSpeed.Y -= GetFlySets() / 2;
            vecMoveSpeed.Z = 0.0f;
            pGame->FindPlayerPed()->SetMoveSpeedVector(vecMoveSpeed);
        }else{
            ScriptCommand(&set_car_z_angle, pGame->FindPlayerPed()->GetCurrentVehicleID(), 226.99);
            ScriptCommand(&set_car_coordinates, pGame->FindPlayerPed()->GetCurrentVehicleID(), mat.pos.X + GetFlySets(), mat.pos.Y - GetFlySets(), mat.pos.Z);
        }
        pGame->GetCamera()->SetBehindPlayer();  
    }

    ImGui::SameLine(0, pGUI->GetFontSize());

    if(ImGui::Button("L-F", ImVec2(100, 50)))
    {
        MATRIX4X4 mat;
        pGame->FindPlayerPed()->GetMatrix(&mat);
        pGame->PlaySound(1053, mat.pos.X, mat.pos.Y, mat.pos.Z);
        pGame->FindPlayerPed()->ForceTargetRotation(45.90);
        if(!pGame->FindPlayerPed()->IsInVehicle()){
            vecMoveSpeed.X -= GetFlySets() / 2;
            vecMoveSpeed.Y = GetFlySets() / 2;
            vecMoveSpeed.Z = 0.0f;
            pGame->FindPlayerPed()->SetMoveSpeedVector(vecMoveSpeed);
        }else{
            ScriptCommand(&set_car_z_angle, pGame->FindPlayerPed()->GetCurrentVehicleID(), 45.90);
            ScriptCommand(&set_car_coordinates, pGame->FindPlayerPed()->GetCurrentVehicleID(), mat.pos.X - GetFlySets(), mat.pos.Y, mat.pos.Z + GetFlySets());
        }
        pGame->GetCamera()->SetBehindPlayer();  
    }

    // ---------------------------------------------- //


    ImGui::ItemSize( ImVec2(0, pGUI->GetFontSize()/2 + 2.5) );

    if(flock == NULL){
        if(ImGui::Button("Lock", ImVec2(150, 50)))
        {
            MATRIX4X4 mat;
            pGame->FindPlayerPed()->GetMatrix(&mat);
            pGame->PlaySound(1053, mat.pos.X, mat.pos.Y, mat.pos.Z);
            ScriptCommand(&lock_actor, pGame->FindPlayerPed()->m_dwGTAId, 1);
            flock = 1;
        }
    } else {
        if(ImGui::Button("(O) Lock", ImVec2(150, 50)))
        {
            MATRIX4X4 mat;
            pGame->FindPlayerPed()->GetMatrix(&mat);
            pGame->PlaySound(1053, mat.pos.X, mat.pos.Y, mat.pos.Z);
            ScriptCommand(&lock_actor, pGame->FindPlayerPed()->m_dwGTAId, 0);
            flock = 0;
        }
    }
    
    if(ImGui::Button("Close", ImVec2(150, 50)))
    {
        MATRIX4X4 mat;
        pGame->FindPlayerPed()->GetMatrix(&mat);
        pGame->PlaySound(1053, mat.pos.X, mat.pos.Y, mat.pos.Z);
        ShowFlyMenu(false);
        Show(false);
        pGame->FindPlayerPed()->TogglePlayerControllable(true);
        pGame->SetGravity(0.008);
        ScriptCommand(&lock_actor, pGame->FindPlayerPed()->m_dwGTAId, 0);
        ScriptCommand(&disembark_instantly_actor, pGame->FindPlayerPed()->m_dwGTAId);
        pGUI->m_fly = 0;
        if(pGUI->m_bd != 1)m_bKrutilka = 0;
    }

    if(ImGui::Button("Back", ImVec2(150, 50)))
    {
        MATRIX4X4 mat;
        pGame->FindPlayerPed()->GetMatrix(&mat);
        pGame->PlaySound(1052, mat.pos.X, mat.pos.Y, mat.pos.Z);
        ShowFlyMenu(false);
        m_bMenuStep = 2;
        pGame->SetGravity(0.008);
        ScriptCommand(&lock_actor, pGame->FindPlayerPed()->m_dwGTAId, 0);
        ScriptCommand(&disembark_instantly_actor, pGame->FindPlayerPed()->m_dwGTAId);
        pGUI->m_fly = 0;
        if(pGUI->m_bd != 1)m_bKrutilka = 0;
    }
}

void CModSAWindow::ToggleCheat(int cheatid)
{ 
    MATRIX4X4 mat;
    pGame->FindPlayerPed()->GetMatrix(&mat);
    if(cheatid != 2)pGame->PlaySound(1053, mat.pos.X, mat.pos.Y, mat.pos.Z);

    CVehiclePool *pVehiclePool = pNetGame->GetVehiclePool();
    CVehicle *pVehicle;

    VEHICLEID VehicleID = pVehiclePool->FindIDFromGtaPtr((VEHICLE_TYPE *)GamePool_FindPlayerPed()->pVehicle);

    pVehicle = pVehiclePool->GetAt(VehicleID);

    switch(cheatid){
        case 0:
            // not using....
        break;
        case 1:
        if(m_bGodMode == NULL){
            float dHealth = pGame->FindPlayerPed()->GetHealth();
            m_bGodMode = 1;
            m_bPH = 1;
            pGUI->m_gm = 1;
            pGame->FindPlayerPed()->sHealth = dHealth;
            pGame->FindPlayerPed()->SetHealth(5000000);
            ScriptCommand(&set_actor_immunities, pGame->FindPlayerPed()->m_dwGTAId, 1, 1, 1, 1, 1);

            if(pGame->FindPlayerPed()->IsInVehicle()){
                ScriptCommand(&set_car_immunities, pGame->FindPlayerPed()->GetCurrentVehicleID(), 1,1,1,1,1);
                ScriptCommand(&toggle_car_tires_vulnerable, pGame->FindPlayerPed()->GetCurrentVehicleID(), 0);
            }

            //pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}God Mode Activated!");
        }else{
            pGame->FindPlayerPed()->SetHealth(pGame->FindPlayerPed()->sHealth);
            if(pGame->FindPlayerPed()->IsInVehicle()){
                ScriptCommand(&set_car_immunities, pGame->FindPlayerPed()->GetCurrentVehicleID(), 0,0,0,0,0);
                ScriptCommand(&toggle_car_tires_vulnerable, pGame->FindPlayerPed()->GetCurrentVehicleID(), 1);
            }
            m_bGodMode = 0;
            m_bPH = 0;
            pGUI->m_gm = 0;
            ScriptCommand(&set_actor_immunities, pGame->FindPlayerPed()->m_dwGTAId, 0, 0, 0, 0, 0);
            //pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}God Mode Deactivated!");
        }
        break;
        case 2:
        if(m_bWallHack == NULL){
            m_bWallHack = 1;
            pGUI->m_wh = 1;
            pNetGame->m_fNameTagDrawDistance = 1500;
            pGame->PlaySound(1133, mat.pos.X, mat.pos.Y, mat.pos.Z);
            //pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}Wall Hack Activated!");
        }else{
            m_bWallHack = 0;
            pGUI->m_wh = 0;
            pNetGame->m_fNameTagDrawDistance = 70;
            pGame->PlaySound(1145, mat.pos.X, mat.pos.Y, mat.pos.Z);
            //pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}Wall Hack Deactivated!");
        }
        break;
        case 3:
        if(m_bCols == NULL){
            m_bCols = 1;
            pGUI->m_fz = 1;
            ScriptCommand(&set_char_collision, pGame->FindPlayerPed()->m_dwGTAId, 0);
            //pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}Freeze Activated!");
        }else{
            m_bCols = 0;
            pGUI->m_fz = 0;
            ScriptCommand(&set_char_collision, pGame->FindPlayerPed()->m_dwGTAId, 1);
            //pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}Freeze Deactivated!");
        } 
        break;
        case 4:
        if(m_bKrutilka == NULL){
            m_bKrutilka = 1;
            pGUI->m_bd = 1;
            //pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}Behind Activated!");
        }else{
            m_bKrutilka = 0;
            pGUI->m_bd = 0;
            //pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}Behind Deactivated!");
        } 
        break;

        case 5:
        if(m_bNF == NULL){
            m_bNF = 1;
            pGUI->m_nf = 1;
            //pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}No Fall Activated!");
        }else{
            m_bNF = 0;
            pGUI->m_nf = 0;
            //pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}No Fall Deactivated!");
        } 
        break;

        case 6:
        if(m_bINVIS == NULL){
            m_bINVIS = 1;
            pGUI->m_INVIS = 1;
            //pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}No Fall Activated!");
        }else{
            m_bINVIS = 0;
            pGUI->m_INVIS = 0;
            //pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}No Fall Deactivated!");
        } 
        break;
        case 7:
        if(m_bFLASH == NULL){
            m_bFLASH = 1;
            pGUI->m_FLASH = 1;
            //pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}Flash enabled!");
        }else{
            pGUI->m_FLASH = 0;
            m_bFLASH = 0;
            //pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}Flash disabled!");
        }
        break;
        case 8:
        if(m_bAirbreak == NULL){
            m_bAirbreak = 1;
            pGUI->m_Airbreak = 1;
            //pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}Air Break enabled!");
        }else{
            pGUI->m_Airbreak = 0;
            m_bAirbreak = 0;
            //pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}Air Break disabled!");
        }
        break;
    }
}

void CModSAWindow::ToggleRPC(int rpcid){
    MATRIX4X4 mat;
    pGame->FindPlayerPed()->GetMatrix(&mat);
    pGame->PlaySound(1053, mat.pos.X, mat.pos.Y, mat.pos.Z);
    switch(rpcid){
        case 0:
        if(m_bVP == NULL){
            m_bVP = 1;
            //pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}Ignor RPC enabled!");
        }else{
            m_bVP = 0;
            //pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}Ignor RPC disabled!");
        } 
        break;

        case 1:
        if(m_bVP2 == NULL){
            m_bVP2 = 1;
            //pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}Ignor RPC enabled!");
        }else{
            m_bVP2 = 0;
            //pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}Ignor RPC disabled!");
        } 
        break;

        case 2:
        if(m_bVV == NULL){
            m_bVV = 1;
            //pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}Ignor RPC enabled!");
        }else{
            m_bVV = 0;
            //pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}Ignor RPC disabled!");
        } 
        break;

        case 3:
        if(m_bCO == NULL){
            m_bCO = 1;
            //pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}Ignor RPC enabled!");
        }else{
            m_bCO = 0;
            //pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}Ignor RPC disabled!");
        } 
        break;

        case 4:
        if(m_bPH == NULL){
            m_bPH = 1;
            //pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}Ignor RPC enabled!");
        }else{
            m_bPH = 0;
            //pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}Ignor RPC disabled!");
        } 
        break;
        case 5:
        if(m_bRPFV == NULL){
            m_bRPFV = 1;
            //pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}Ignor RPC enabled!");
        }else{
            m_bRPFV = 0;
            //pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}Ignor RPC disabled!");
        }
        break;
        case 6:
        if(m_bSD == NULL){
            m_bSD = 1;
            //pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}Ignor RPC enabled!");
        }else{
            m_bSD = 0;
            //pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}Ignor RPC disabled!");
        }
        break;
        case 7:
        if(m_bAPA == NULL){
            m_bAPA = 1;
            //pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}Ignor RPC enabled!");
        }else{
            m_bAPA = 0;
            //pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}Ignor RPC disabled!");
        }
        break;
        case 8:
        if(m_bRPW == NULL){
            m_bRPW = 1;
            //pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}Ignor RPC enabled!");
        }else{
            m_bRPW = 0;
            //pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}Ignor RPC disabled!");
        }
        break;
        case 9:
        if(m_bCP == NULL){
            m_bCP = 1;
            //pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}Ignor RPC enabled!");
        }else{
            m_bCP = 0;
            //pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}Ignor RPC disabled!");
        }
        break;
        case 10:
        if(m_bGCW == NULL){
            m_bGCW = 1;
            //pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}Ignor RPC enabled!");
        }else{
            m_bGCW = 0;
            //pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}Ignor RPC disabled!");
        }
        break;
        case 11:
        if(m_bCP2 == NULL){
            m_bCP2 = 1;
            //pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}Ignor RPC enabled!");
        }else{
            m_bCP2 = 0;
            //pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}Ignor RPC disabled!");
        }
        break;
        case 12:
        if(m_bCA == NULL){
            m_bCA = 1;
            //pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}Ignor RPC enabled!");
        }else{
            m_bCA = 0;
            //pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}Ignor RPC disabled!");
        }
        break;
        case 13:
        if(m_bSPP == NULL){
            m_bSPP = 1;
            //pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}Ignor RPC enabled!");
        }else{
            m_bSPP = 0;
            //pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}Ignor RPC disabled!");
        }
        break;
        case 14:
        if(m_bGPP == NULL){
            MATRIX4X4 mat;
            pGame->FindPlayerPed()->GetMatrix(&mat);
            sx = mat.pos.X;
            sy = mat.pos.Y;
            sz = mat.pos.Z;
            m_bGPP = 1;
            //pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}Ignor RPC enabled!");
        }else{
            m_bGPP = 0;
            //pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}Ignor RPC disabled!");
        }
        break;
        case 15:
        if(m_bCTL == NULL){
            m_bCTL = 1;
            //pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}Ignor RPC enabled!");
        }else{
            m_bCTL = 0;
            //pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}Ignor RPC disabled!");
        }
        break;
        case 16:
        if(m_bEV == NULL){
            m_bEV = 1;
            //pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}Ignor RPC enabled!");
        }else{
            m_bEV = 0;
            //pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}Ignor RPC disabled!");
        }
        break;
        case 17:
        if(m_bCE == NULL){
            m_bCE = 1;
            //pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}Ignor RPC enabled!");
        }else{
            m_bCE = 0;
            //pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}Ignor RPC disabled!");
        }
        break;
        case 18:
        if(m_bSPN == NULL){
            m_bSPN = 1;
            //pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}Ignor RPC enabled!");
        }else{
            m_bSPN = 0;
            //pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}Ignor RPC disabled!");
        }
        break;
        case 19:
        if(m_bAGZ == NULL){
            m_bAGZ = 1;
            //pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}Ignor RPC enabled!");
        }else{
            m_bAGZ = 0;
            //pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}Ignor RPC disabled!");
        }
        break;
        case 20:
        if(m_bTPC == NULL){
            m_bTPC = 1;
            //pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}Ignor RPC enabled!");
        }else{
            m_bTPC = 0;
            //pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}Ignor RPC disabled!");
        }
        break;
        case 21:
        if(m_bSTD == NULL){
            m_bSTD = 1;
            //pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}Ignor RPC enabled!");
        }else{
            m_bSTD = 0;
            //pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}Ignor RPC disabled!");
        }
        break;
        case 22:
        if(m_bHTD == NULL){
            m_bHTD = 1;
            //pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}Ignor RPC enabled!");
        }else{
            m_bHTD = 0;
            //pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}Ignor RPC disabled!");
        }
        break;
        case 23:
        if(m_bSM == NULL){
            m_bSM = 1;
            //pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}Ignor RPC enabled!");
        }else{
            m_bSM = 0;
            //pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}Ignor RPC disabled!");
        }
        break;
        case 24:
        if(m_bHM == NULL){
            m_bHM = 1;
            //pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}Ignor RPC enabled!");
        }else{
            m_bHM = 0;
            //pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}Ignor RPC disabled!");
        }
        break;
        case 25:
        if(m_bSG == NULL){
            m_bSG = 1;
            //pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}Ignor RPC enabled!");
        }else{
            m_bSG = 0;
            //pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}Ignor RPC disabled!");
        }
        break;
        case 26:
        if(m_bSPS == NULL){
            m_bSPS = 1;
            //pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}Ignor RPC enabled!");
        }else{
            m_bSPS = 0;
            //pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}Ignor RPC disabled!");
        }
        break;
    }
}

void CModSAWindow::ToggleNoKickTeleport(float x, float y, float z)
{
   // todo
}

void CModSAWindow::ToggleTeleport(int posid){
    MATRIX4X4 mat;
    pGame->FindPlayerPed()->GetMatrix(&mat);
    pGame->PlaySound(1053, mat.pos.X, mat.pos.Y, mat.pos.Z);
    pGame->FindPlayerPed()->SetInterior(0);
    switch(posid){
        case 0: // City Hall
            if(!pGame->FindPlayerPed()->IsInVehicle()){
                pGame->FindPlayerPed()->TeleportTo(1478.51, -1766.22, 18.80);
            }else{
                ScriptCommand(&set_car_coordinates, pGame->FindPlayerPed()->GetCurrentVehicleID(), 1478.51, -1766.22, 18.80);
            }

            //pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}Teleported!");
        break;
        case 1: // Fabrica
            if(!pGame->FindPlayerPed()->IsInVehicle()){
                pGame->FindPlayerPed()->TeleportTo(-87.04, -302.43, 3.15);
            }else{
                ScriptCommand(&set_car_coordinates, pGame->FindPlayerPed()->GetCurrentVehicleID(), -87.04, -302.43, 3.15);
            }

            //pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}Teleported!");
        break;
        case 2: // Ferma
            if(!pGame->FindPlayerPed()->IsInVehicle()){
                pGame->FindPlayerPed()->TeleportTo(-369.37, -1423.99, 25.73);
            }else{
                ScriptCommand(&set_car_coordinates, pGame->FindPlayerPed()->GetCurrentVehicleID(), -369.37, -1423.99, 25.73);
            }

            //pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}Teleported!");
        break;
        case 3: // Vinewood Mountain
            if(!pGame->FindPlayerPed()->IsInVehicle()){
                pGame->FindPlayerPed()->TeleportTo(1422.15, -877.47, 49.67);
            }else{
                ScriptCommand(&set_car_coordinates, pGame->FindPlayerPed()->GetCurrentVehicleID(), 1422.15, -877.47, 49.67);
            }

            //pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}Teleported!");
        break;
        case 4: // Mazebank roof
            if(!pGame->FindPlayerPed()->IsInVehicle()){
                pGame->FindPlayerPed()->TeleportTo(1544.82, -1352.42, 329.48);
            }else{
                ScriptCommand(&set_car_coordinates, pGame->FindPlayerPed()->GetCurrentVehicleID(), 1544.82, -1352.42, 329.48);
            }

            //pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}Teleported!");
        break;
        case 5: // Railway LS
            if(!pGame->FindPlayerPed()->IsInVehicle()){
                pGame->FindPlayerPed()->TeleportTo(1764.81, -1911.92, 13.57);
            }else{
                ScriptCommand(&set_car_coordinates, pGame->FindPlayerPed()->GetCurrentVehicleID(), 1764.81, -1911.92, 13.57);
            }

            //pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}Teleported!");
        break;
        case 6: // Railway LV
            if(!pGame->FindPlayerPed()->IsInVehicle()){
                pGame->FindPlayerPed()->TeleportTo(2860.13, 1290.82, 11.39);
            }else{
                ScriptCommand(&set_car_coordinates, pGame->FindPlayerPed()->GetCurrentVehicleID(), 2860.13, 1290.82, 11.39);
            }

            //pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}Teleported!");
        break;
        case 7: // Railway SF
            if(!pGame->FindPlayerPed()->IsInVehicle()){
                pGame->FindPlayerPed()->TeleportTo(-1985.86, 137.66, 27.69);
            }else{
                ScriptCommand(&set_car_coordinates, pGame->FindPlayerPed()->GetCurrentVehicleID(), -1985.86, 137.66, 27.69);
            }

            //pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}Teleported!");
        break;
        case 8: // Bus Station
            if(!pGame->FindPlayerPed()->IsInVehicle()){
                pGame->FindPlayerPed()->TeleportTo(1224.93, -1815.15, 16.59);
            }else{
                ScriptCommand(&set_car_coordinates, pGame->FindPlayerPed()->GetCurrentVehicleID(), 1224.93, -1815.15, 16.59);
            }

            //pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}Teleported!");
        break;
        case 9: // Taxi Station
            if(!pGame->FindPlayerPed()->IsInVehicle()){
                pGame->FindPlayerPed()->TeleportTo(1108.06, -1799.94, 16.59);
            }else{
                ScriptCommand(&set_car_coordinates, pGame->FindPlayerPed()->GetCurrentVehicleID(), 1108.06, -1799.94, 16.59);
            }

            //pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}Teleported!");
        break;
        case 10: // Ganton
            if(!pGame->FindPlayerPed()->IsInVehicle()){
                pGame->FindPlayerPed()->TeleportTo(2536.30, -1663.86, 15.15);
            }else{
                ScriptCommand(&set_car_coordinates, pGame->FindPlayerPed()->GetCurrentVehicleID(), 2536.30, -1663.86, 15.15);
            }

            //pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}Teleported!");
        break;
        case 11: // Emmet Lane
            if(!pGame->FindPlayerPed()->IsInVehicle()){
                pGame->FindPlayerPed()->TeleportTo(2446.70, -1978.78, 13.55);
            }else{
                ScriptCommand(&set_car_coordinates, pGame->FindPlayerPed()->GetCurrentVehicleID(), 2446.70, -1978.78, 13.55);
            }

            //pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}Teleported!");
        break;
        case 12: // Willowfield
            if(!pGame->FindPlayerPed()->IsInVehicle()){
                pGame->FindPlayerPed()->TeleportTo(2652.78, -2033.69, 13.15);
            }else{
                ScriptCommand(&set_car_coordinates, pGame->FindPlayerPed()->GetCurrentVehicleID(), 2652.78, -2033.69, 13.15);
            }

            //pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}Teleported!");
        break;
        case 13: // Glen Park
            if(!pGame->FindPlayerPed()->IsInVehicle()){
                pGame->FindPlayerPed()->TeleportTo(1984.78, -1151.83, 21.07);
            }else{
                ScriptCommand(&set_car_coordinates, pGame->FindPlayerPed()->GetCurrentVehicleID(), 1984.78, -1151.83, 21.07);
            }

            //pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}Teleported!");
        break;
        case 14: // LSPD
            if(!pGame->FindPlayerPed()->IsInVehicle()){
                pGame->FindPlayerPed()->TeleportTo(1550.44, -1669.59, 13.56);
            }else{
                ScriptCommand(&set_car_coordinates, pGame->FindPlayerPed()->GetCurrentVehicleID(), 1550.44, -1669.59, 13.56);
            }

            //pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}Teleported!");
        break;
        case 15: // LVPD
            if(!pGame->FindPlayerPed()->IsInVehicle()){
                pGame->FindPlayerPed()->TeleportTo(2308.01, 2448.11, 10.82);
            }else{
                ScriptCommand(&set_car_coordinates, pGame->FindPlayerPed()->GetCurrentVehicleID(), 2308.01, 2448.11, 10.82);
            }

            //pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}Teleported!");
        break;
        case 16: // SFPD
            if(!pGame->FindPlayerPed()->IsInVehicle()){
                pGame->FindPlayerPed()->TeleportTo(-1598.05, 714.07, 13.10);
            }else{
                ScriptCommand(&set_car_coordinates, pGame->FindPlayerPed()->GetCurrentVehicleID(), -1598.05, 714.07, 13.10);
            }

            //pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}Teleported!");
        break;
        case 17: // Driving School
            if(!pGame->FindPlayerPed()->IsInVehicle()){
                pGame->FindPlayerPed()->TeleportTo(-2025.56, -92.01, 35.32);
            }else{
                ScriptCommand(&set_car_coordinates, pGame->FindPlayerPed()->GetCurrentVehicleID(), -2025.56, -92.01, 35.32);
            }

            //pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}Teleported!");
        break;
        case 18: // LS Car Shop
            if(!pGame->FindPlayerPed()->IsInVehicle()){
                pGame->FindPlayerPed()->TeleportTo(554.46, -1269.06, 17.24);
            }else{
                ScriptCommand(&set_car_coordinates, pGame->FindPlayerPed()->GetCurrentVehicleID(), 554.46, -1269.06, 17.24);
            }

            //pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}Teleported!");
        break;
        case 19: // LV Car Shop
            if(!pGame->FindPlayerPed()->IsInVehicle()){
                pGame->FindPlayerPed()->TeleportTo(2198.83, 1391.02, 10.82);
            }else{
                ScriptCommand(&set_car_coordinates, pGame->FindPlayerPed()->GetCurrentVehicleID(), 2198.83, 1391.02, 10.82);
            }

            //pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}Teleported!");
        break;
        case 20: // SF Car Shop
            if(!pGame->FindPlayerPed()->IsInVehicle()){
                pGame->FindPlayerPed()->TeleportTo(-1974.41, 288.67, 35.17);
            }else{
                ScriptCommand(&set_car_coordinates, pGame->FindPlayerPed()->GetCurrentVehicleID(), -1974.41, 288.67, 35.17);
            }

            //pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}Teleported!");
        break;
        case 21: // LS Motorcycle Shop
            if(!pGame->FindPlayerPed()->IsInVehicle()){
                pGame->FindPlayerPed()->TeleportTo(2133.05, -1135.37, 25.69);
            }else{
                ScriptCommand(&set_car_coordinates, pGame->FindPlayerPed()->GetCurrentVehicleID(), 2133.05, -1135.37, 25.69);
            }

            //pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}Teleported!");
        break;
        case 22: // Vagos #1 (on the beach)
            if(!pGame->FindPlayerPed()->IsInVehicle()){
                pGame->FindPlayerPed()->TeleportTo(2771.16, -1624.63, 10.93);
            }else{
                ScriptCommand(&set_car_coordinates, pGame->FindPlayerPed()->GetCurrentVehicleID(), 2771.16, -1624.63, 10.93);
            }

            //pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}Teleported!");
        break;
        case 23: // Vagos #2 (on the mountain)
            if(!pGame->FindPlayerPed()->IsInVehicle()){
                pGame->FindPlayerPed()->TeleportTo(2756.51, -1181.45, 69.40);
            }else{
                ScriptCommand(&set_car_coordinates, pGame->FindPlayerPed()->GetCurrentVehicleID(), 2756.51, -1181.45, 69.40);
            }

            //pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}Teleported!");
        break;
        case 24: // Rifa
            if(!pGame->FindPlayerPed()->IsInVehicle()){
                pGame->FindPlayerPed()->TeleportTo(2184.85, -1810.15, 13.38);
            }else{
                ScriptCommand(&set_car_coordinates, pGame->FindPlayerPed()->GetCurrentVehicleID(), 2184.85, -1810.15, 13.38);
            }

            //pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}Teleported!");
        break;
        case 25: // Aztecs
            if(!pGame->FindPlayerPed()->IsInVehicle()){
                pGame->FindPlayerPed()->TeleportTo(1665.32, -2109.61, 13.55);
            }else{
                ScriptCommand(&set_car_coordinates, pGame->FindPlayerPed()->GetCurrentVehicleID(), 1665.32, -2109.61, 13.55);
            }

            //pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}Teleported!");
        break;
        case 26: // Hospital LS
            if(!pGame->FindPlayerPed()->IsInVehicle()){
                pGame->FindPlayerPed()->TeleportTo(1183.75, -1323.58, 13.58);
            }else{
                ScriptCommand(&set_car_coordinates, pGame->FindPlayerPed()->GetCurrentVehicleID(), 1183.75, -1323.58, 13.58);
            }

            //pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}Teleported!");
        break;
        case 27: // Hospital LV
            if(!pGame->FindPlayerPed()->IsInVehicle()){
                pGame->FindPlayerPed()->TeleportTo(1607.87, 1831.97, 10.82);
            }else{
                ScriptCommand(&set_car_coordinates, pGame->FindPlayerPed()->GetCurrentVehicleID(), 1607.87, 1831.97, 10.82);
            }

            //pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}Teleported!");
        break;
        case 28: // Hospital SF
            if(!pGame->FindPlayerPed()->IsInVehicle()){
                pGame->FindPlayerPed()->TeleportTo(-2653.50, 631.28, 14.45);
            }else{
                ScriptCommand(&set_car_coordinates, pGame->FindPlayerPed()->GetCurrentVehicleID(), -2653.50, 631.28, 14.45);
            }

            //pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}Teleported!");
        break;
        case 29: // FBI
            if(!pGame->FindPlayerPed()->IsInVehicle()){
                pGame->FindPlayerPed()->TeleportTo(-2450.51, 503.69, 30.09);
            }else{
                ScriptCommand(&set_car_coordinates, pGame->FindPlayerPed()->GetCurrentVehicleID(), -2450.51, 503.69, 30.09);
            }

            //pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}Teleported!");
        break;
        case 30: // Mine
            if(!pGame->FindPlayerPed()->IsInVehicle()){
                pGame->FindPlayerPed()->TeleportTo(-1858.78, -1570.18, 21.75);
            }else{
                ScriptCommand(&set_car_coordinates, pGame->FindPlayerPed()->GetCurrentVehicleID(), -1858.78, -1570.18, 21.75);
            }

            //pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}Teleported!");
        break;
        case 31: // Chiliad Mountain
            if(!pGame->FindPlayerPed()->IsInVehicle()){
                pGame->FindPlayerPed()->TeleportTo(-2234.46, -1735.08, 480.83);
            }else{
                ScriptCommand(&set_car_coordinates, pGame->FindPlayerPed()->GetCurrentVehicleID(), -2234.46, -1735.08, 480.83);
            }

            //pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}Teleported!");
        break;
        case 32: // Airport
            if(!pGame->FindPlayerPed()->IsInVehicle()){
                pGame->FindPlayerPed()->TeleportTo(1682.15, -2264.46, 13.51);
            }else{
                ScriptCommand(&set_car_coordinates, pGame->FindPlayerPed()->GetCurrentVehicleID(), 1682.15, -2264.46, 13.51);
            }

            //pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}Teleported!");
        break;
        case 33: // Stock
            if(!pGame->FindPlayerPed()->IsInVehicle()){
                pGame->FindPlayerPed()->TeleportTo(2115.66, -2274.92, 20.68);
            }else{
                ScriptCommand(&set_car_coordinates, pGame->FindPlayerPed()->GetCurrentVehicleID(), 2115.66, -2274.92, 20.68);
            }

            //pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}Teleported!");
        break;
        case 34: // Railway LS #2
            if(!pGame->FindPlayerPed()->IsInVehicle()){
                pGame->FindPlayerPed()->TeleportTo(1979.31, -1968.83, 16.69);
            }else{
                ScriptCommand(&set_car_coordinates, pGame->FindPlayerPed()->GetCurrentVehicleID(), 1979.31, -1968.83, 16.69);
            }

            //pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}Teleported!");
        break;
        case 35: // 24/7 Shop
            if(!pGame->FindPlayerPed()->IsInVehicle()){
                pGame->FindPlayerPed()->TeleportTo(1828.29, -1844.15, 13.58);
            }else{
                ScriptCommand(&set_car_coordinates, pGame->FindPlayerPed()->GetCurrentVehicleID(), 1828.29, -1844.15, 13.58);
            }

            //pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}Teleported!");
        break;
        case 36: // Lighthouse
            if(!pGame->FindPlayerPed()->IsInVehicle()){
                pGame->FindPlayerPed()->TeleportTo(155.16, -1939.62, 3.77);
            }else{
                ScriptCommand(&set_car_coordinates, pGame->FindPlayerPed()->GetCurrentVehicleID(), 155.16, -1939.62, 3.77);
            }

            //pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}Teleported!");
        break;
        case 37: // Ferris Wheel
            if(!pGame->FindPlayerPed()->IsInVehicle()){
                pGame->FindPlayerPed()->TeleportTo(377.73, -2027.40, 7.83);
            }else{
                ScriptCommand(&set_car_coordinates, pGame->FindPlayerPed()->GetCurrentVehicleID(), 377.73, -2027.40, 7.83);
            }

            //pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}Teleported!");
        break;
        case 38: // Gas Station
            if(!pGame->FindPlayerPed()->IsInVehicle()){
                pGame->FindPlayerPed()->TeleportTo(1938.90, -1775.52, 13.38);
            }else{
                ScriptCommand(&set_car_coordinates, pGame->FindPlayerPed()->GetCurrentVehicleID(), 1938.90, -1775.52, 13.38);
            }

            //pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}Teleported!");
        break;
        case 39: // Pizzeria
            if(!pGame->FindPlayerPed()->IsInVehicle()){
                pGame->FindPlayerPed()->TeleportTo(2094.95, -1807.60, 13.55);
            }else{
                ScriptCommand(&set_car_coordinates, pGame->FindPlayerPed()->GetCurrentVehicleID(), 2094.95, -1807.60, 13.55);
            }

            //pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}Teleported!");
        break;
        case 40: // Pay N Spray
            if(!pGame->FindPlayerPed()->IsInVehicle()){
                pGame->FindPlayerPed()->TeleportTo(2078.11, -1831.03, 13.38);
            }else{
                ScriptCommand(&set_car_coordinates, pGame->FindPlayerPed()->GetCurrentVehicleID(), 2078.11, -1831.03, 13.38);
            }

            //pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}Teleported!");
        break;
        case 41: // Bank LS
            if(!pGame->FindPlayerPed()->IsInVehicle()){
                pGame->FindPlayerPed()->TeleportTo(1413.92, -1701.24, 13.54);
            }else{
                ScriptCommand(&set_car_coordinates, pGame->FindPlayerPed()->GetCurrentVehicleID(), 1413.92, -1701.24, 13.54);
            }

            //pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}Teleported!");
        break;
        case 42: // Ammunation
            if(!pGame->FindPlayerPed()->IsInVehicle()){
                pGame->FindPlayerPed()->TeleportTo(1364.24, -1279.50, 13.55);
            }else{
                ScriptCommand(&set_car_coordinates, pGame->FindPlayerPed()->GetCurrentVehicleID(), 1364.24, -1279.50, 13.55);
            }

            //pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}Teleported!");
        break;
        case 43: // Skate Park
            if(!pGame->FindPlayerPed()->IsInVehicle()){
                pGame->FindPlayerPed()->TeleportTo(1938.28, -1401.67, 13.57);
            }else{
                ScriptCommand(&set_car_coordinates, pGame->FindPlayerPed()->GetCurrentVehicleID(), 1938.28, -1401.67, 13.57);
            }

            //pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}Teleported!");
        break;
        case 44: // Hotel #1
            if(!pGame->FindPlayerPed()->IsInVehicle()){
                pGame->FindPlayerPed()->TeleportTo(332.14, -1519.99, 35.87);
            }else{
                ScriptCommand(&set_car_coordinates, pGame->FindPlayerPed()->GetCurrentVehicleID(), 332.14, -1519.99, 35.87);
            }

            //pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}Teleported!");
        break;
        case 45: // Hotel #2
            if(!pGame->FindPlayerPed()->IsInVehicle()){
                pGame->FindPlayerPed()->TeleportTo(2226.11, -1159.69, 25.77);
            }else{
                ScriptCommand(&set_car_coordinates, pGame->FindPlayerPed()->GetCurrentVehicleID(), 2226.11, -1159.69, 25.77);
            }

            //pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}Teleported!");
        break;
        case 46: // Docks
            if(!pGame->FindPlayerPed()->IsInVehicle()){
                pGame->FindPlayerPed()->TeleportTo(2787.66, -2400.03, 13.63);
            }else{
                ScriptCommand(&set_car_coordinates, pGame->FindPlayerPed()->GetCurrentVehicleID(), 2787.66, -2400.03, 13.63);
            }

            //pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}Teleported!");
        break;
        case 47: // Dump
            if(!pGame->FindPlayerPed()->IsInVehicle()){
                pGame->FindPlayerPed()->TeleportTo(2197.49, -1976.91, 13.56);
            }else{
                ScriptCommand(&set_car_coordinates, pGame->FindPlayerPed()->GetCurrentVehicleID(), 2197.49, -1976.91, 13.56);
            }

            //pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}Teleported!");
        break;
        case 48: // Zone 51 (enter)
            if(!pGame->FindPlayerPed()->IsInVehicle()){
                pGame->FindPlayerPed()->TeleportTo(213.71, 1879.46, 13.14);
            }else{
                ScriptCommand(&set_car_coordinates, pGame->FindPlayerPed()->GetCurrentVehicleID(), 213.71, 1879.46, 13.14);
            }

            //pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}Teleported!");
        break;
        case 49: // Zone 51 (angars)
            if(!pGame->FindPlayerPed()->IsInVehicle()){
                pGame->FindPlayerPed()->TeleportTo(292.31, 1656.36, 17.64);
            }else{
                ScriptCommand(&set_car_coordinates, pGame->FindPlayerPed()->GetCurrentVehicleID(), 292.31, 1656.36, 17.64);
            }

            //pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}Teleported!");
        break;
        case 50: // ECDD
            if(!pGame->FindPlayerPed()->IsInVehicle()){
                pGame->FindPlayerPed()->TeleportTo(-385.08, 2237.69, 42.09);
            }else{
                ScriptCommand(&set_car_coordinates, pGame->FindPlayerPed()->GetCurrentVehicleID(), -385.08, 2237.69, 42.09);
            }

            //pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}Teleported!");
        break;
        case 51: // Mafia #1 LV
            if(!pGame->FindPlayerPed()->IsInVehicle()){
                pGame->FindPlayerPed()->TeleportTo(1430.80, 753.25, 10.82);
            }else{
                ScriptCommand(&set_car_coordinates, pGame->FindPlayerPed()->GetCurrentVehicleID(), 1430.80, 753.25, 10.82);
            }

            //pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}Teleported!");
        break;
        case 52: // Mafia #2 LV
            if(!pGame->FindPlayerPed()->IsInVehicle()){
                pGame->FindPlayerPed()->TeleportTo(2608.07, 1834.11, 10.82);
            }else{
                ScriptCommand(&set_car_coordinates, pGame->FindPlayerPed()->GetCurrentVehicleID(), 2608.07, 1834.11, 10.82);
            }

            //pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}Teleported!");
        break;
        case 53: // Russian Mafia
            if(!pGame->FindPlayerPed()->IsInVehicle()){
                pGame->FindPlayerPed()->TeleportTo(947.80, 1733.72, 8.85);
            }else{
                ScriptCommand(&set_car_coordinates, pGame->FindPlayerPed()->GetCurrentVehicleID(), 947.80, 1733.72, 8.85);
            }

            //pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}Teleported!");
        break;
        case 54: // Mafia #3 SF
            if(!pGame->FindPlayerPed()->IsInVehicle()){
                pGame->FindPlayerPed()->TeleportTo(-2726.54, -314.45, 7.19);
            }else{
                ScriptCommand(&set_car_coordinates, pGame->FindPlayerPed()->GetCurrentVehicleID(), -2726.54, -314.45, 7.19);
            }

            //pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}Teleported!");
        break;
        case 55: // Alhambra
            if(!pGame->FindPlayerPed()->IsInVehicle()){
                pGame->FindPlayerPed()->TeleportTo(1831.02, -1682.09, 13.55);
            }else{
                ScriptCommand(&set_car_coordinates, pGame->FindPlayerPed()->GetCurrentVehicleID(), 1831.02, -1682.09, 13.55);
            }

            //pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}Teleported!");
        break;
        case 69:
            //ToggleNoKickTeleport(marker_X, marker_Y, marker_Z);
            if(!pGame->FindPlayerPed()->IsInVehicle()){
                pGame->FindPlayerPed()->TeleportTo(marker_X, marker_Y, marker_Z);
            }else{
                ScriptCommand(&set_car_coordinates, pGame->FindPlayerPed()->GetCurrentVehicleID(), marker_X, marker_Y, marker_Z);
            }

            //pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}Teleported!");
        break;
    }
}

void CModSAWindow::Render()
{
	if(!m_bIsActive || m_bMenuStep == 0 || protect != 0) 
    {
        m_bIsActive = false;
        return;
    }

    ImGui::StyleColorsClassic();

	ImGuiIO &io = ImGui::GetIO();

	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(8, 8));

    ImGui::Begin("cheat_menu", nullptr, 
        ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_HorizontalScrollbar | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize);
    switch(m_bMenuStep){
        case 1:
        ImGui::Text("SA-MP MOD Mobile");
        if(ImGui::Button("Cheats", ImVec2(280, 50)))
        {
            MATRIX4X4 mat;
            pGame->FindPlayerPed()->GetMatrix(&mat);
            pGame->PlaySound(1053, mat.pos.X, mat.pos.Y, mat.pos.Z);
            m_bMenuStep = 2;
        }

        if(ImGui::Button("Harmful Cheats", ImVec2(280, 50)))
        {
            MATRIX4X4 mat;
            pGame->FindPlayerPed()->GetMatrix(&mat);
            pGame->PlaySound(1053, mat.pos.X, mat.pos.Y, mat.pos.Z);
            m_bMenuStep = 6;
        }

        if(ImGui::Button("Weapons", ImVec2(280, 50)))
        {
            MATRIX4X4 mat;
            pGame->FindPlayerPed()->GetMatrix(&mat);
            pGame->PlaySound(1053, mat.pos.X, mat.pos.Y, mat.pos.Z);
            m_bMenuStep = 5;
        }

        if(ImGui::Button("Pos Master", ImVec2(280, 50)))
        {
            MATRIX4X4 mat;
            pGame->FindPlayerPed()->GetMatrix(&mat);
            pGame->PlaySound(1053, mat.pos.X, mat.pos.Y, mat.pos.Z);
            m_bMenuStep = 13;
        }

        if(ImGui::Button("Teleports", ImVec2(280, 50)))
        {
            MATRIX4X4 mat;
            pGame->FindPlayerPed()->GetMatrix(&mat);
            pGame->PlaySound(1053, mat.pos.X, mat.pos.Y, mat.pos.Z);
            m_bMenuStep = 7;
        }

        if(ImGui::Button("Settings", ImVec2(280, 50)))
        {
            MATRIX4X4 mat;
            pGame->FindPlayerPed()->GetMatrix(&mat);
            pGame->PlaySound(1053, mat.pos.X, mat.pos.Y, mat.pos.Z);
            m_bMenuStep = 3;
        }

        if(ImGui::Button("GTA Patches", ImVec2(280, 50)))
        {
            MATRIX4X4 mat;
            pGame->FindPlayerPed()->GetMatrix(&mat);
            pGame->PlaySound(1053, mat.pos.X, mat.pos.Y, mat.pos.Z);
            m_bMenuStep = 12;
        }

        if(ImGui::Button("SA-MP Patches", ImVec2(280, 50)))
        {
            MATRIX4X4 mat;
            pGame->FindPlayerPed()->GetMatrix(&mat);
            pGame->PlaySound(1053, mat.pos.X, mat.pos.Y, mat.pos.Z);
            m_bMenuStep = 8;
        }

        if(ImGui::Button("Close", ImVec2(280, 50)))
        {
            MATRIX4X4 mat;
            pGame->FindPlayerPed()->GetMatrix(&mat);
            pGame->PlaySound(1053, mat.pos.X, mat.pos.Y, mat.pos.Z);
            Show(false);
        }

        break;
        case 2:
        ImGui::Text("Cheats");
        if(m_bWallHack == 1){
            if(ImGui::Button("(O) Wall Hack", ImVec2(200, 50)))
            {
                ToggleCheat(2);
                //Show(false);
            }
        }else{
            if(ImGui::Button("Wall Hack", ImVec2(200, 50)))
            {
                ToggleCheat(2);
                //Show(false);
            }
        } 

        if(m_bNF == 1){
            if(ImGui::Button("(O) No Fall", ImVec2(200, 50)))
            {
                ToggleCheat(5);
                //Show(false);
            }
        }else{
            if(ImGui::Button("No Fall", ImVec2(200, 50)))
            {
                ToggleCheat(5);
                //Show(false);
            }
        }

        if(m_bGodMode == 1){
            if(ImGui::Button("(O) Invincible", ImVec2(200, 50)))
            {
                ToggleCheat(1);
                //Show(false);
            }
        }else{
            if(ImGui::Button("Invincible", ImVec2(200, 50)))
            {
                ToggleCheat(1);
                //Show(false);
            }
        }

        if(m_bCols == 1){
            if(ImGui::Button("(O) Freeze", ImVec2(200, 50)))
            {
                ToggleCheat(3);
                //Show(false);
            }
        }else{
            if(ImGui::Button("Freeze", ImVec2(200, 50)))
            {
                ToggleCheat(3);
                //Show(false);
            }
        }

        if(m_bINVIS == 1){
            if(ImGui::Button("(O) Invisible", ImVec2(200, 50)))
            {
                ToggleCheat(6);
                //Show(false);
            }
        }else{
            if(ImGui::Button("Invisible", ImVec2(200, 50)))
            {
                ToggleCheat(6);
                //Show(false);
            }
        }

        if(ImGui::Button("Fly Hack", ImVec2(200, 50)))
        {
            MATRIX4X4 mat;
            pGame->FindPlayerPed()->GetMatrix(&mat);
            pGame->PlaySound(1053, mat.pos.X, mat.pos.Y, mat.pos.Z);
            m_bKrutilka = 1;
            m_bMenuStep = 11;
        }

        if(m_bFLASH == 1){
            if(ImGui::Button("(O) Flash", ImVec2(200, 50)))
            {
                ToggleCheat(7);
                //Show(false);
            }
        }else{
            if(ImGui::Button("Flash", ImVec2(200, 50)))
            {
                ToggleCheat(7);
                //Show(false);
            }
        }

        //if(m_bAirbreak == 1){
        //    if(ImGui::Button("(O) Air Break", ImVec2(200, 50)))
        //    {
        //        ToggleCheat(8);
        //        //Show(false);
        //    }
        //}else{
        //    if(ImGui::Button("Air Break", ImVec2(200, 50)))
        //    {
        //        ToggleCheat(8);
        //        //Show(false);
        //    }
        //}

        if(m_bKrutilka == 1){
            if(ImGui::Button("(O) Behind", ImVec2(200, 50)))
            {
                ToggleCheat(4);
                //Show(false);
            }
        }else{
            if(ImGui::Button("Behind", ImVec2(200, 50)))
            {
                ToggleCheat(4);
                //Show(false);
            }
        }

        if(ImGui::Button("Gravity", ImVec2(200, 50)))
        {
            MATRIX4X4 mat;
            pGame->FindPlayerPed()->GetMatrix(&mat);
            pGame->PlaySound(1053, mat.pos.X, mat.pos.Y, mat.pos.Z);
            m_bMenuStep = 4;
        }

        if(ImGui::Button("Close", ImVec2(200, 50)))
        {
            MATRIX4X4 mat;
            pGame->FindPlayerPed()->GetMatrix(&mat);
            pGame->PlaySound(1053, mat.pos.X, mat.pos.Y, mat.pos.Z);
            Show(false);
        }

        if(ImGui::Button("Back", ImVec2(200, 50)))
        {
            MATRIX4X4 mat;
            pGame->FindPlayerPed()->GetMatrix(&mat);
            pGame->PlaySound(1052, mat.pos.X, mat.pos.Y, mat.pos.Z);
            m_bMenuStep = 1;
        }
        break;
        case 3:
        ImGui::Text("Settings");
        if(ImGui::Button("Clear chat", ImVec2(280, 50)))
        {
            MATRIX4X4 mat;
            pGame->FindPlayerPed()->GetMatrix(&mat);
            pGame->PlaySound(1053, mat.pos.X, mat.pos.Y, mat.pos.Z);
            for(int i = 0; i <= 50; i++)pChatWindow->AddInfoMessage(" ");
            //Show(false);
        }

        if(lockinp == 1){
            if(ImGui::Button("(O) Lock chat input", ImVec2(280, 50)))
            {
                MATRIX4X4 mat;
                pGame->FindPlayerPed()->GetMatrix(&mat);
                pGame->PlaySound(1053, mat.pos.X, mat.pos.Y, mat.pos.Z);
                if(lockinp == 0){
                    lockinp = 1;
                    pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}Chat input lock is enabled!");
                }else if(lockinp == 1){
                    lockinp = 0;
                    pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}Chat input lock is disabled!");
                }
                //Show(false);
            }
        }else{
            if(ImGui::Button("Lock chat input", ImVec2(280, 50)))
            {
                MATRIX4X4 mat;
                pGame->FindPlayerPed()->GetMatrix(&mat);
                pGame->PlaySound(1053, mat.pos.X, mat.pos.Y, mat.pos.Z);
                if(lockinp == 0){
                    lockinp = 1;
                    pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}Chat input lock is enabled!");
                }else if(lockinp == 1){
                    lockinp = 0;
                    pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}Chat input lock is disabled!");
                }
                //Show(false);
            }
        }

        if(rxyz == 1){
            if(ImGui::Button("(O) Render XYZ", ImVec2(280, 50)))
            {
                MATRIX4X4 mat;
                pGame->FindPlayerPed()->GetMatrix(&mat);
                pGame->PlaySound(1053, mat.pos.X, mat.pos.Y, mat.pos.Z);
                if(rxyz == 0){
                    pGUI->m_xyz = 1;
                    rxyz = 1;
                }else if(rxyz == 1){
                    pGUI->m_xyz = 0;
                    rxyz = 0;
                }
                //Show(false);
            }
        }else{
            if(ImGui::Button("Render XYZ", ImVec2(280, 50)))
            {
                MATRIX4X4 mat;
                pGame->FindPlayerPed()->GetMatrix(&mat);
                pGame->PlaySound(1053, mat.pos.X, mat.pos.Y, mat.pos.Z);
                if(lockinp == 0){
                    pGUI->m_xyz = 1;
                    rxyz = 1;
                }else if(rxyz == 1){
                    pGUI->m_xyz = 0;
                    rxyz = 0;
                }
                //Show(false);
            }
        }

        if(dnames == 1){
            if(ImGui::Button("(O) Hide Nicknames", ImVec2(280, 50)))
            {
                MATRIX4X4 mat;
                pGame->FindPlayerPed()->GetMatrix(&mat);
                pGame->PlaySound(1053, mat.pos.X, mat.pos.Y, mat.pos.Z);
                if(dnames == 0){
                    dnames = 1;
                }else if(dnames == 1){
                    dnames = 0;
                }
                //Show(false);
            }
        }else{
            if(ImGui::Button("Hide Nicknames", ImVec2(280, 50)))
            {
                MATRIX4X4 mat;
                pGame->FindPlayerPed()->GetMatrix(&mat);
                pGame->PlaySound(1053, mat.pos.X, mat.pos.Y, mat.pos.Z);
                if(dnames == 0){
                    dnames = 1;
                }else if(dnames == 1){
                    dnames = 0;
                }
                //Show(false);
            }
        }

        if(players == 1){
            if(ImGui::Button("New Players", ImVec2(280, 50)))
            {
                MATRIX4X4 mat;
                pGame->FindPlayerPed()->GetMatrix(&mat);
                pGame->PlaySound(1053, mat.pos.X, mat.pos.Y, mat.pos.Z);
                if(players == 0){
                    players = 1;
                }else if(players == 1){
                    players = 0;
                }
                //Show(false);
            }
        }else{
            if(ImGui::Button("(O) New Players", ImVec2(280, 50)))
            {
                MATRIX4X4 mat;
                pGame->FindPlayerPed()->GetMatrix(&mat);
                pGame->PlaySound(1053, mat.pos.X, mat.pos.Y, mat.pos.Z);
                if(players == 0){
                    players = 1;
                }else if(players == 1){
                    players = 0;
                }
                //Show(false);
            }
        }

        if(ImGui::Button("Close", ImVec2(280, 50)))
        {
            MATRIX4X4 mat;
            pGame->FindPlayerPed()->GetMatrix(&mat);
            pGame->PlaySound(1053, mat.pos.X, mat.pos.Y, mat.pos.Z);
            Show(false);
        }

        if(ImGui::Button("Back", ImVec2(280, 50)))
        {
            MATRIX4X4 mat;
            pGame->FindPlayerPed()->GetMatrix(&mat);
            pGame->PlaySound(1052, mat.pos.X, mat.pos.Y, mat.pos.Z);
            m_bMenuStep = 1;
        }
        break;

        case 4:
        pGUI->m_gravity = 1;
        ImGui::Text("Gravity (Default: 0.008)");
        if(ImGui::Button("- Gravity", ImVec2(280, 50)))
        {
            MATRIX4X4 mat;
            pGame->FindPlayerPed()->GetMatrix(&mat);
            pGame->PlaySound(1053, mat.pos.X, mat.pos.Y, mat.pos.Z);
            pGame->SetGravity(pGame->GetGravity() - 0.001);
            //pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}Set gravity to %f", pGame->GetGravity());
            char str[4096];
            sprintf(str, "%f ~<~~<~~<~~<~~n~~n~~n~", pGame->GetGravity());
            pGame->DisplayGameText(str, 1750, 3);
        }

        if(ImGui::Button("+ Gravity", ImVec2(280, 50)))
        {
            MATRIX4X4 mat;
            pGame->FindPlayerPed()->GetMatrix(&mat);
            pGame->PlaySound(1053, mat.pos.X, mat.pos.Y, mat.pos.Z);
            pGame->SetGravity(pGame->GetGravity() + 0.001);
            //pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}Set gravity to %f", pGame->GetGravity());
            char str[4096];
            sprintf(str, "%f ~<~~<~~<~~<~~n~~n~~n~", pGame->GetGravity());
            pGame->DisplayGameText(str, 1750, 3);
            
        }

        if(ImGui::Button("Restore Gravity", ImVec2(280, 50)))
        {
            MATRIX4X4 mat;
            pGame->FindPlayerPed()->GetMatrix(&mat);
            pGame->PlaySound(1053, mat.pos.X, mat.pos.Y, mat.pos.Z);
            pGame->SetGravity(0.008);
            //pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}Set gravity to %f", pGame->GetGravity());
            char str[4096];
            sprintf(str, "%f~n~~n~~n~~n~~n~~n~", pGame->GetGravity());
            pGame->DisplayGameText(str, 1750, 3);
        }

        if(ImGui::Button("Close", ImVec2(280, 50)))
        {
            MATRIX4X4 mat;
            pGame->FindPlayerPed()->GetMatrix(&mat);
            pGame->PlaySound(1053, mat.pos.X, mat.pos.Y, mat.pos.Z);
            pGUI->m_gravity = 0;
            Show(false);
        }

        if(ImGui::Button("Back", ImVec2(280, 50)))
        {
            MATRIX4X4 mat;
            pGame->FindPlayerPed()->GetMatrix(&mat);
            pGame->PlaySound(1052, mat.pos.X, mat.pos.Y, mat.pos.Z);
            pGUI->m_gravity = 0;
            m_bMenuStep = 2;
        }
        break;

        case 5:
        ImGui::Text("Weapons");
        if(ImGui::Button("Brass Knuckles", ImVec2(280, 50)))
        {
            MATRIX4X4 mat;
            pGame->FindPlayerPed()->GetMatrix(&mat);
            pGame->PlaySound(1053, mat.pos.X, mat.pos.Y, mat.pos.Z);
            pGame->FindPlayerPed()->GiveWeapon(1, 9999);
            //pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}Gived weapon id 1");
            //Show(false);
        }

        if(ImGui::Button("Golf Club", ImVec2(280, 50)))
        {
            MATRIX4X4 mat;
            pGame->FindPlayerPed()->GetMatrix(&mat);
            pGame->PlaySound(1053, mat.pos.X, mat.pos.Y, mat.pos.Z);
            pGame->FindPlayerPed()->GiveWeapon(2, 9999);
            //pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}Gived weapon id 2");
            //Show(false);
        }

        if(ImGui::Button("Baton", ImVec2(280, 50)))
        {
            MATRIX4X4 mat;
            pGame->FindPlayerPed()->GetMatrix(&mat);
            pGame->PlaySound(1053, mat.pos.X, mat.pos.Y, mat.pos.Z);
            pGame->FindPlayerPed()->GiveWeapon(3, 9999);
            //pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}Gived weapon id 3");
            //Show(false);
        }

        if(ImGui::Button("Knife", ImVec2(280, 50)))
        {
            MATRIX4X4 mat;
            pGame->FindPlayerPed()->GetMatrix(&mat);
            pGame->PlaySound(1053, mat.pos.X, mat.pos.Y, mat.pos.Z);
            pGame->FindPlayerPed()->GiveWeapon(4, 9999);
            //pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}Gived weapon id 4");
            //Show(false);
        }

        if(ImGui::Button("Baseball Bat", ImVec2(280, 50)))
        {
            MATRIX4X4 mat;
            pGame->FindPlayerPed()->GetMatrix(&mat);
            pGame->PlaySound(1053, mat.pos.X, mat.pos.Y, mat.pos.Z);
            pGame->FindPlayerPed()->GiveWeapon(5, 9999);
            //pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}Gived weapon id 5");
            //Show(false);
        }

        if(ImGui::Button("Shovel", ImVec2(280, 50)))
        {
            MATRIX4X4 mat;
            pGame->FindPlayerPed()->GetMatrix(&mat);
            pGame->PlaySound(1053, mat.pos.X, mat.pos.Y, mat.pos.Z);
            pGame->FindPlayerPed()->GiveWeapon(6, 9999);
            //pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}Gived weapon id 6");
            //Show(false);
        }

        if(ImGui::Button("Pool Cue", ImVec2(280, 50)))
        {
            MATRIX4X4 mat;
            pGame->FindPlayerPed()->GetMatrix(&mat);
            pGame->PlaySound(1053, mat.pos.X, mat.pos.Y, mat.pos.Z);
            pGame->FindPlayerPed()->GiveWeapon(7, 9999);
            //pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}Gived weapon id 7");
            //Show(false);
        }

        if(ImGui::Button("Katana", ImVec2(280, 50)))
        {
            MATRIX4X4 mat;
            pGame->FindPlayerPed()->GetMatrix(&mat);
            pGame->PlaySound(1053, mat.pos.X, mat.pos.Y, mat.pos.Z);
            pGame->FindPlayerPed()->GiveWeapon(8, 9999);
            //pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}Gived weapon id 8");
            //Show(false);
        }

        if(ImGui::Button("Chainsaw", ImVec2(280, 50)))
        {
            MATRIX4X4 mat;
            pGame->FindPlayerPed()->GetMatrix(&mat);
            pGame->PlaySound(1053, mat.pos.X, mat.pos.Y, mat.pos.Z);
            pGame->FindPlayerPed()->GiveWeapon(9, 9999);
            //pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}Gived weapon id 9");
            //Show(false);
        }

        if(ImGui::Button("Purple Dildo", ImVec2(280, 50)))
        {
            MATRIX4X4 mat;
            pGame->FindPlayerPed()->GetMatrix(&mat);
            pGame->PlaySound(1053, mat.pos.X, mat.pos.Y, mat.pos.Z);
            pGame->FindPlayerPed()->GiveWeapon(10, 9999);
            //pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}Gived weapon id 10");
            //Show(false);
        }

        if(ImGui::Button("Dildo", ImVec2(280, 50)))
        {
            MATRIX4X4 mat;
            pGame->FindPlayerPed()->GetMatrix(&mat);
            pGame->PlaySound(1053, mat.pos.X, mat.pos.Y, mat.pos.Z);
            pGame->FindPlayerPed()->GiveWeapon(11, 9999);
            //pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}Gived weapon id 11");
            //Show(false);
        }

        if(ImGui::Button("Vibrator", ImVec2(280, 50)))
        {
            MATRIX4X4 mat;
            pGame->FindPlayerPed()->GetMatrix(&mat);
            pGame->PlaySound(1053, mat.pos.X, mat.pos.Y, mat.pos.Z);
            pGame->FindPlayerPed()->GiveWeapon(12, 9999);
            //pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}Gived weapon id 12");
            //Show(false);
        }

        if(ImGui::Button("Silver Vibrator", ImVec2(280, 50)))
        {
            MATRIX4X4 mat;
            pGame->FindPlayerPed()->GetMatrix(&mat);
            pGame->PlaySound(1053, mat.pos.X, mat.pos.Y, mat.pos.Z);
            pGame->FindPlayerPed()->GiveWeapon(13, 9999);
            //pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}Gived weapon id 13");
            //Show(false);
        }

        if(ImGui::Button("Flowers", ImVec2(280, 50)))
        {
            MATRIX4X4 mat;
            pGame->FindPlayerPed()->GetMatrix(&mat);
            pGame->PlaySound(1053, mat.pos.X, mat.pos.Y, mat.pos.Z);
            pGame->FindPlayerPed()->GiveWeapon(14, 9999);
            //pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}Gived weapon id 14");
            //Show(false);
        }

        if(ImGui::Button("Cane", ImVec2(280, 50)))
        {
            MATRIX4X4 mat;
            pGame->FindPlayerPed()->GetMatrix(&mat);
            pGame->PlaySound(1053, mat.pos.X, mat.pos.Y, mat.pos.Z);
            pGame->FindPlayerPed()->GiveWeapon(15, 9999);
            //pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}Gived weapon id 15");
            //Show(false);
        }

        if(ImGui::Button("Grenade", ImVec2(280, 50)))
        {
            MATRIX4X4 mat;
            pGame->FindPlayerPed()->GetMatrix(&mat);
            pGame->PlaySound(1053, mat.pos.X, mat.pos.Y, mat.pos.Z);
            pGame->FindPlayerPed()->GiveWeapon(16, 9999);
            //pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}Gived weapon id 16");
            //Show(false);
        }

        if(ImGui::Button("Tear Gas", ImVec2(280, 50)))
        {
            MATRIX4X4 mat;
            pGame->FindPlayerPed()->GetMatrix(&mat);
            pGame->PlaySound(1053, mat.pos.X, mat.pos.Y, mat.pos.Z);
            pGame->FindPlayerPed()->GiveWeapon(17, 9999);
            //pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}Gived weapon id 17");
            //Show(false);
        }

        if(ImGui::Button("Molotov Cocktail", ImVec2(280, 50)))
        {
            MATRIX4X4 mat;
            pGame->FindPlayerPed()->GetMatrix(&mat);
            pGame->PlaySound(1053, mat.pos.X, mat.pos.Y, mat.pos.Z);
            pGame->FindPlayerPed()->GiveWeapon(18, 9999);
            //pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}Gived weapon id 18");
            //Show(false);
        }
        
        if(ImGui::Button("9mm", ImVec2(280, 50)))
        {
            MATRIX4X4 mat;
            pGame->FindPlayerPed()->GetMatrix(&mat);
            pGame->PlaySound(1053, mat.pos.X, mat.pos.Y, mat.pos.Z);
            pGame->FindPlayerPed()->GiveWeapon(22, 9999);
            //pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}Gived weapon id 22");
            //Show(false);
        }

        if(ImGui::Button("Silenced 9mm", ImVec2(280, 50)))
        {
            MATRIX4X4 mat;
            pGame->FindPlayerPed()->GetMatrix(&mat);
            pGame->PlaySound(1053, mat.pos.X, mat.pos.Y, mat.pos.Z);
            pGame->FindPlayerPed()->GiveWeapon(23, 9999);
            //pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}Gived weapon id 23");
            //Show(false);
        }

        if(ImGui::Button("Desert Eagle", ImVec2(280, 50)))
        {
            MATRIX4X4 mat;
            pGame->FindPlayerPed()->GetMatrix(&mat);
            pGame->PlaySound(1053, mat.pos.X, mat.pos.Y, mat.pos.Z);
            pGame->FindPlayerPed()->GiveWeapon(24, 9999);
            //pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}Gived weapon id 24");
            //Show(false);
        }

        if(ImGui::Button("Shotgun", ImVec2(280, 50)))
        {
            MATRIX4X4 mat;
            pGame->FindPlayerPed()->GetMatrix(&mat);
            pGame->PlaySound(1053, mat.pos.X, mat.pos.Y, mat.pos.Z);
            pGame->FindPlayerPed()->GiveWeapon(25, 9999);
            //pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}Gived weapon id 25");
            //Show(false);
        }

        if(ImGui::Button("Sawnoff Shotgun", ImVec2(280, 50)))
        {
            MATRIX4X4 mat;
            pGame->FindPlayerPed()->GetMatrix(&mat);
            pGame->PlaySound(1053, mat.pos.X, mat.pos.Y, mat.pos.Z);
            pGame->FindPlayerPed()->GiveWeapon(26, 9999);
            //pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}Gived weapon id 26");
            //Show(false);
        }

        if(ImGui::Button("Combat Shotgun", ImVec2(280, 50)))
        {
            MATRIX4X4 mat;
            pGame->FindPlayerPed()->GetMatrix(&mat);
            pGame->PlaySound(1053, mat.pos.X, mat.pos.Y, mat.pos.Z);
            pGame->FindPlayerPed()->GiveWeapon(27, 9999);
            //pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}Gived weapon id 27");
            //Show(false);
        }

        if(ImGui::Button("UZI", ImVec2(280, 50)))
        {
            MATRIX4X4 mat;
            pGame->FindPlayerPed()->GetMatrix(&mat);
            pGame->PlaySound(1053, mat.pos.X, mat.pos.Y, mat.pos.Z);
            pGame->FindPlayerPed()->GiveWeapon(28, 9999);
            //pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}Gived weapon id 28");
            //Show(false);
        }

        if(ImGui::Button("MP5", ImVec2(280, 50)))
        {
            MATRIX4X4 mat;
            pGame->FindPlayerPed()->GetMatrix(&mat);
            pGame->PlaySound(1053, mat.pos.X, mat.pos.Y, mat.pos.Z);
            pGame->FindPlayerPed()->GiveWeapon(29, 9999);
            //pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}Gived weapon id 29");
            //Show(false);
        }

        if(ImGui::Button("AK-47", ImVec2(280, 50)))
        {
            MATRIX4X4 mat;
            pGame->FindPlayerPed()->GetMatrix(&mat);
            pGame->PlaySound(1053, mat.pos.X, mat.pos.Y, mat.pos.Z);
            pGame->FindPlayerPed()->GiveWeapon(30, 9999);
            //pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}Gived weapon id 30");
            //Show(false);
        }

        if(ImGui::Button("M4", ImVec2(280, 50)))
        {
            MATRIX4X4 mat;
            pGame->FindPlayerPed()->GetMatrix(&mat);
            pGame->PlaySound(1053, mat.pos.X, mat.pos.Y, mat.pos.Z);
            pGame->FindPlayerPed()->GiveWeapon(31, 9999);
            //pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}Gived weapon id 31");
            //Show(false);
        }

        if(ImGui::Button("TEC-9", ImVec2(280, 50)))
        {
            MATRIX4X4 mat;
            pGame->FindPlayerPed()->GetMatrix(&mat);
            pGame->PlaySound(1053, mat.pos.X, mat.pos.Y, mat.pos.Z);
            pGame->FindPlayerPed()->GiveWeapon(32, 9999);
            //pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}Gived weapon id 32");
            //Show(false);
        }

        if(ImGui::Button("Country Rifle", ImVec2(280, 50)))
        {
            MATRIX4X4 mat;
            pGame->FindPlayerPed()->GetMatrix(&mat);
            pGame->PlaySound(1053, mat.pos.X, mat.pos.Y, mat.pos.Z);
            pGame->FindPlayerPed()->GiveWeapon(33, 9999);
            //pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}Gived weapon id 33");
            //Show(false);
        }
        
        if(ImGui::Button("Sniper Rifle", ImVec2(280, 50)))
        {
            MATRIX4X4 mat;
            pGame->FindPlayerPed()->GetMatrix(&mat);
            pGame->PlaySound(1053, mat.pos.X, mat.pos.Y, mat.pos.Z);
            pGame->FindPlayerPed()->GiveWeapon(34, 9999);
            //pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}Gived weapon id 34");
            //Show(false);
        }

        if(ImGui::Button("RPG", ImVec2(280, 50)))
        {
            MATRIX4X4 mat;
            pGame->FindPlayerPed()->GetMatrix(&mat);
            pGame->PlaySound(1053, mat.pos.X, mat.pos.Y, mat.pos.Z);
            pGame->FindPlayerPed()->GiveWeapon(35, 9999);
            //pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}Gived weapon id 35");
            //Show(false);
        }

        if(ImGui::Button("HS Rocket", ImVec2(280, 50)))
        {
            MATRIX4X4 mat;
            pGame->FindPlayerPed()->GetMatrix(&mat);
            pGame->PlaySound(1053, mat.pos.X, mat.pos.Y, mat.pos.Z);
            pGame->FindPlayerPed()->GiveWeapon(36, 9999);
            //pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}Gived weapon id 36");
            //Show(false);
        }

        if(ImGui::Button("Flamethrower", ImVec2(280, 50)))
        {
            MATRIX4X4 mat;
            pGame->FindPlayerPed()->GetMatrix(&mat);
            pGame->PlaySound(1053, mat.pos.X, mat.pos.Y, mat.pos.Z);
            pGame->FindPlayerPed()->GiveWeapon(37, 9999);
            //pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}Gived weapon id 37");
            //Show(false);
        }

        if(ImGui::Button("Minigun", ImVec2(280, 50)))
        {
            MATRIX4X4 mat;
            pGame->FindPlayerPed()->GetMatrix(&mat);
            pGame->PlaySound(1053, mat.pos.X, mat.pos.Y, mat.pos.Z);
            pGame->FindPlayerPed()->GiveWeapon(38, 9999);
            //pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}Gived weapon id 38");
            //Show(false);
        }

        if(ImGui::Button("C-4", ImVec2(280, 50)))
        {
            MATRIX4X4 mat;
            pGame->FindPlayerPed()->GetMatrix(&mat);
            pGame->PlaySound(1053, mat.pos.X, mat.pos.Y, mat.pos.Z);
            pGame->FindPlayerPed()->GiveWeapon(39, 9999);
            //pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}Gived weapon id 39");
            //Show(false);
        }

        if(ImGui::Button("Detonator", ImVec2(280, 50)))
        {
            MATRIX4X4 mat;
            pGame->FindPlayerPed()->GetMatrix(&mat);
            pGame->PlaySound(1053, mat.pos.X, mat.pos.Y, mat.pos.Z);
            pGame->FindPlayerPed()->GiveWeapon(40, 9999);
            //pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}Gived weapon id 40");
            //Show(false);
        }

        if(ImGui::Button("Spraycan", ImVec2(280, 50)))
        {
            MATRIX4X4 mat;
            pGame->FindPlayerPed()->GetMatrix(&mat);
            pGame->PlaySound(1053, mat.pos.X, mat.pos.Y, mat.pos.Z);
            pGame->FindPlayerPed()->GiveWeapon(41, 9999);
            //pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}Gived weapon id 41");
            //Show(false);
        }

        if(ImGui::Button("Fire Extinguisher", ImVec2(280, 50)))
        {
            MATRIX4X4 mat;
            pGame->FindPlayerPed()->GetMatrix(&mat);
            pGame->PlaySound(1053, mat.pos.X, mat.pos.Y, mat.pos.Z);
            pGame->FindPlayerPed()->GiveWeapon(42, 9999);
            //pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}Gived weapon id 42");
            //Show(false);
        }

        if(ImGui::Button("Camera", ImVec2(280, 50)))
        {
            MATRIX4X4 mat;
            pGame->FindPlayerPed()->GetMatrix(&mat);
            pGame->PlaySound(1053, mat.pos.X, mat.pos.Y, mat.pos.Z);
            pGame->FindPlayerPed()->GiveWeapon(43, 9999);
            //pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}Gived weapon id 43");
            //Show(false);
        }

        if(ImGui::Button("Night Vis Goggles", ImVec2(280, 50)))
        {
            MATRIX4X4 mat;
            pGame->FindPlayerPed()->GetMatrix(&mat);
            pGame->PlaySound(1053, mat.pos.X, mat.pos.Y, mat.pos.Z);
            pGame->FindPlayerPed()->GiveWeapon(44, 9999);
            //pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}Gived weapon id 44");
            //Show(false);
        }

        if(ImGui::Button("Thermal Goggles", ImVec2(280, 50)))
        {
            MATRIX4X4 mat;
            pGame->FindPlayerPed()->GetMatrix(&mat);
            pGame->PlaySound(1053, mat.pos.X, mat.pos.Y, mat.pos.Z);
            pGame->FindPlayerPed()->GiveWeapon(45, 9999);
            //pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}Gived weapon id 45");
            //Show(false);
        }

        if(ImGui::Button("Parachute", ImVec2(280, 50)))
        {
            MATRIX4X4 mat;
            pGame->FindPlayerPed()->GetMatrix(&mat);
            pGame->PlaySound(1053, mat.pos.X, mat.pos.Y, mat.pos.Z);
            pGame->FindPlayerPed()->GiveWeapon(46, 9999);
            //pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}Gived weapon id 46");
            //Show(false);
        }

        if(ImGui::Button("Close", ImVec2(280, 50)))
        {
            MATRIX4X4 mat;
            pGame->FindPlayerPed()->GetMatrix(&mat);
            pGame->PlaySound(1053, mat.pos.X, mat.pos.Y, mat.pos.Z);
            Show(false);
        }

        if(ImGui::Button("Back", ImVec2(280, 50)))
        {
            MATRIX4X4 mat;
            pGame->FindPlayerPed()->GetMatrix(&mat);
            pGame->PlaySound(1052, mat.pos.X, mat.pos.Y, mat.pos.Z);
            m_bMenuStep = 1;
        }
        break;

        case 6:
        ImGui::Text("Harmful Cheats");
        if(ImGui::Button("Blowup Car", ImVec2(280, 50)))
        {
            MATRIX4X4 mat;
            pGame->FindPlayerPed()->GetMatrix(&mat);
            pGame->PlaySound(1053, mat.pos.X, mat.pos.Y, mat.pos.Z);
            int i = 1000;

            CVehiclePool *pVehiclePool = pNetGame->GetVehiclePool();
            CVehicle *pVehicle;

            VEHICLEID VehicleID = pVehiclePool->FindIDFromGtaPtr((VEHICLE_TYPE *)GamePool_FindPlayerPed()->pVehicle);

            pVehicle = pVehiclePool->GetAt(VehicleID);

            while(i != 0)
            {
                i--;

                if(pGame->FindPlayerPed()->IsInVehicle()) 
                    pVehicle->SetHealth(i);
            }
            
            //Show(false);
        }

        if(ImGui::Button("Close", ImVec2(280, 50)))
        {
            MATRIX4X4 mat;
            pGame->FindPlayerPed()->GetMatrix(&mat);
            pGame->PlaySound(1053, mat.pos.X, mat.pos.Y, mat.pos.Z);
            Show(false);
        }

        if(ImGui::Button("Back", ImVec2(280, 50)))
        {
            MATRIX4X4 mat;
            pGame->FindPlayerPed()->GetMatrix(&mat);
            pGame->PlaySound(1052, mat.pos.X, mat.pos.Y, mat.pos.Z);
            m_bMenuStep = 1;
        }
        break;
        case 7:
        ImGui::Text("Teleports");
        if(ImGui::Button("Marker", ImVec2(280, 50)))
        {
            ToggleTeleport(69);
            //Show(false);
        }

        if(ImGui::Button("City Hall LS", ImVec2(280, 50)))
        {
            ToggleTeleport(0);
            //Show(false);
        }
        
        if(ImGui::Button("Factory", ImVec2(280, 50)))
        {
            ToggleTeleport(1);
            //Show(false);
        }

        if(ImGui::Button("Farm", ImVec2(280, 50)))
        {
            ToggleTeleport(2);
            //Show(false);
        }

        if(ImGui::Button("Vinewood's mountain", ImVec2(280, 50)))
        {
            ToggleTeleport(3);
            //Show(false);
        }

        if(ImGui::Button("Skyscraper", ImVec2(280, 50)))
        {
            ToggleTeleport(4);
            //Show(false);
        }

        if(ImGui::Button("LS Railway station", ImVec2(280, 50)))
        {
            ToggleTeleport(5);
            //Show(false);
        }

        if(ImGui::Button("LV Railway station", ImVec2(280, 50)))
        {
            ToggleTeleport(6);
            //Show(false);
        }

        if(ImGui::Button("SF Railway station", ImVec2(280, 50)))
        {
            ToggleTeleport(7);
            //Show(false);
        }

        if(ImGui::Button("Bus Station", ImVec2(280, 50)))
        {
            ToggleTeleport(8);
            //Show(false);
        }

        if(ImGui::Button("Taxi Station", ImVec2(280, 50)))
        {
            ToggleTeleport(9);
            //Show(false);
        }

        if(ImGui::Button("Grove Street", ImVec2(280, 50)))
        {
            ToggleTeleport(10);
            //Show(false);
        }

        if(ImGui::Button("Emmet lane", ImVec2(280, 50)))
        {
            ToggleTeleport(11);
            //Show(false);
        }

        if(ImGui::Button("Willowfield", ImVec2(280, 50)))
        {
            ToggleTeleport(12);
            //Show(false);
        }

        if(ImGui::Button("Glen park", ImVec2(280, 50)))
        {
            ToggleTeleport(13);
            //Show(false);
        }

        if(ImGui::Button("LSPD", ImVec2(280, 50)))
        {
            ToggleTeleport(14);
            //Show(false);
        }

        if(ImGui::Button("LVPD", ImVec2(280, 50)))
        {
            ToggleTeleport(15);
            //Show(false);
        }

        if(ImGui::Button("SFPD", ImVec2(280, 50)))
        {
            ToggleTeleport(16);
            //Show(false);
        }

        if(ImGui::Button("Driving School", ImVec2(280, 50)))
        {
            ToggleTeleport(17);
            //Show(false);
        }

        if(ImGui::Button("LS Car shop", ImVec2(280, 50)))
        {
            ToggleTeleport(18);
            //Show(false);
        }

        if(ImGui::Button("LV Car shop", ImVec2(280, 50)))
        {
            ToggleTeleport(19);
            //Show(false);
        }

        if(ImGui::Button("SF Car shop", ImVec2(280, 50)))
        {
            ToggleTeleport(20);
            //Show(false);
        }

        if(ImGui::Button("LS Moto shop", ImVec2(280, 50)))
        {
            ToggleTeleport(21);
            //Show(false);
        }

        if(ImGui::Button("Vagos #1", ImVec2(280, 50)))
        {
            ToggleTeleport(22);
            //Show(false);
        }

        if(ImGui::Button("Vagos #2", ImVec2(280, 50)))
        {
            ToggleTeleport(23);
            //Show(false);
        }

        if(ImGui::Button("Rifa", ImVec2(280, 50)))
        {
            ToggleTeleport(24);
            //Show(false);
        }

        if(ImGui::Button("Aztecas", ImVec2(280, 50)))
        {
            ToggleTeleport(25);
            //Show(false);
        }

        if(ImGui::Button("LS Hospital", ImVec2(280, 50)))
        {
            ToggleTeleport(26);
            //Show(false);
        }

        if(ImGui::Button("LV Hospital", ImVec2(280, 50)))
        {
            ToggleTeleport(27);
            //Show(false);
        }

        if(ImGui::Button("SF Hospital", ImVec2(280, 50)))
        {
            ToggleTeleport(28);
            //Show(false);
        }

        if(ImGui::Button("FBI", ImVec2(280, 50)))
        {
            ToggleTeleport(29);
            //Show(false);
        }

        if(ImGui::Button("Mine", ImVec2(280, 50)))
        {
            ToggleTeleport(30);
            //Show(false);
        }

        if(ImGui::Button("Chiliad", ImVec2(280, 50)))
        {
            ToggleTeleport(31);
            //Show(false);
        }

        if(ImGui::Button("Airport", ImVec2(280, 50)))
        {
            ToggleTeleport(32);
            //Show(false);
        }

        if(ImGui::Button("Storage", ImVec2(280, 50)))
        {
            ToggleTeleport(33);
            //Show(false);
        }

        if(ImGui::Button("LS Railway St. #2", ImVec2(280, 50)))
        {
            ToggleTeleport(34);
            //Show(false);
        }

        if(ImGui::Button("24/7 Shop", ImVec2(280, 50)))
        {
            ToggleTeleport(35);
            //Show(false);
        }

        if(ImGui::Button("Lighthouse", ImVec2(280, 50)))
        {
            ToggleTeleport(36);
            //Show(false);
        }

        if(ImGui::Button("Ferris wheel", ImVec2(280, 50)))
        {
            ToggleTeleport(37);
            //Show(false);
        }

        if(ImGui::Button("Gas station", ImVec2(280, 50)))
        {
            ToggleTeleport(38);
            //Show(false);
        }

        if(ImGui::Button("Pizzeria", ImVec2(280, 50)))
        {
            ToggleTeleport(39);
            //Show(false);
        }

        if(ImGui::Button("Pay'n'Spray", ImVec2(280, 50)))
        {
            ToggleTeleport(40);
            //Show(false);
        }

        if(ImGui::Button("LS Bank", ImVec2(280, 50)))
        {
            ToggleTeleport(41);
            //Show(false);
        }

        if(ImGui::Button("Gun Shop LS", ImVec2(280, 50)))
        {
            ToggleTeleport(42);
            //Show(false);
        }

        if(ImGui::Button("Skate park", ImVec2(280, 50)))
        {
            ToggleTeleport(43);
            //Show(false);
        }

        if(ImGui::Button("Hotel #1", ImVec2(280, 50)))
        {
            ToggleTeleport(44);
            //Show(false);
        }

        if(ImGui::Button("Hotel #2", ImVec2(280, 50)))
        {
            ToggleTeleport(45);
            //Show(false);
        }

        if(ImGui::Button("Docks", ImVec2(280, 50)))
        {
            ToggleTeleport(46);
            //Show(false);
        }

        if(ImGui::Button("Dump", ImVec2(280, 50)))
        {
            ToggleTeleport(47);
            //Show(false);
        }

        if(ImGui::Button("Zone 51 (В)", ImVec2(280, 50)))
        {
            ToggleTeleport(48);
            //Show(false);
        }

        if(ImGui::Button("Zone 51 (А)", ImVec2(280, 50)))
        {
            ToggleTeleport(49);
            //Show(false);
        }

        if(ImGui::Button("ECDD", ImVec2(280, 50)))
        {
            ToggleTeleport(50);
            //Show(false);
        }

        if(ImGui::Button("Mafia LV #1", ImVec2(280, 50)))
        {
            ToggleTeleport(51);
            //Show(false);
        }

        if(ImGui::Button("Mafia LV #2", ImVec2(280, 50)))
        {
            ToggleTeleport(52);
            //Show(false);
        }

        if(ImGui::Button("Russian Mafia", ImVec2(280, 50)))
        {
            ToggleTeleport(53);
            //Show(false);
        }

        if(ImGui::Button("Mafia SF", ImVec2(280, 50)))
        {
            ToggleTeleport(54);
            //Show(false);
        }

        if(ImGui::Button("Alhambra", ImVec2(280, 50)))
        {
            ToggleTeleport(55);
            //Show(false);
        }

        if(ImGui::Button("Close", ImVec2(280, 50)))
        {
            MATRIX4X4 mat;
            pGame->FindPlayerPed()->GetMatrix(&mat);
            pGame->PlaySound(1053, mat.pos.X, mat.pos.Y, mat.pos.Z);
            Show(false);
        }

        if(ImGui::Button("Back", ImVec2(280, 50)))
        {
            MATRIX4X4 mat;
            pGame->FindPlayerPed()->GetMatrix(&mat);
            pGame->PlaySound(1052, mat.pos.X, mat.pos.Y, mat.pos.Z);
            m_bMenuStep = 1;
        }
        break;

        case 8:
        ImGui::Text("SA-MP Patches");
        if(ImGui::Button("Ignor Incoming RPC", ImVec2(280, 50)))
        {
            m_bMenuStep = 9;
        }

       if(ImGui::Button("Ignor Outcoming RPC", ImVec2(280, 50)))
       {
           m_bMenuStep = 10;
       }

       //if(ImGui::Button("Ignor Incoming Packet", ImVec2(280, 50)))
       //{
       //    //Show(false);
       //}

       //if(ImGui::Button("Ignor Outcoming Packet", ImVec2(280, 50)))
       //{
       //    //Show(false);
       //}

        if(ImGui::Button("Close", ImVec2(280, 50)))
        {
            MATRIX4X4 mat;
            pGame->FindPlayerPed()->GetMatrix(&mat);
            pGame->PlaySound(1053, mat.pos.X, mat.pos.Y, mat.pos.Z);
            Show(false);
        }

        if(ImGui::Button("Back", ImVec2(280, 50)))
        {
            MATRIX4X4 mat;
            pGame->FindPlayerPed()->GetMatrix(&mat);
            pGame->PlaySound(1052, mat.pos.X, mat.pos.Y, mat.pos.Z);
            m_bMenuStep = 1;
        }
        break;

        case 9:
        ImGui::Text("Incoming RPC");

        //if(ImGui::Button("SetPlayerName", ImVec2(280, 50)))
        //{
        //    //Show(false);
        //}

        if(m_bSPP == 1){
            if(ImGui::Button("(O) SetPlayerPos", ImVec2(280, 50)))
            {
                ToggleRPC(13);
                //Show(false);
            }
        }else{
            if(ImGui::Button("SetPlayerPos", ImVec2(280, 50)))
            {
                ToggleRPC(13);
                //Show(false);
            }
        }

        if(m_bPH == 1){
            if(ImGui::Button("(O) SetPlayerHealth", ImVec2(280, 50)))
            {
                ToggleRPC(4);
                //Show(false);
            }
        }else{
            if(ImGui::Button("SetPlayerHealth", ImVec2(280, 50)))
            {
                ToggleRPC(4);
                //Show(false);
            }
        }

        if(m_bRPW == 1){
            if(ImGui::Button("(O) ResetPlayerWeapons", ImVec2(280, 50)))
            {
                ToggleRPC(8);
                //Show(false);
            }
        }else{
            if(ImGui::Button("ResetPlayerWeapons", ImVec2(280, 50)))
            {
                ToggleRPC(8);
                //Show(false);
            }
        }

        if(m_bVP2 == 1){
            if(ImGui::Button("(O) SetVehicleParamsEx", ImVec2(280, 50)))
            {
                ToggleRPC(1);
                //Show(false);
            }
        }else{
            if(ImGui::Button("SetVehicleParamsEx", ImVec2(280, 50)))
            {
                ToggleRPC(1);
                //Show(false);
            }
        }

        if(m_bCTL == 1){
            if(ImGui::Button("(O) Create3DTextLabel", ImVec2(280, 50)))
            {
                ToggleRPC(15);
                //Show(false);
            }
        }else{
            if(ImGui::Button("Create3DTextLabel", ImVec2(280, 50)))
            {
                ToggleRPC(15);
                //Show(false);
            }
        }

        if(m_bCE == 1){
            if(ImGui::Button("(O) CreateExplosion", ImVec2(280, 50)))
            {
                ToggleRPC(17);
                //Show(false);
            }
        }else{
            if(ImGui::Button("CreateExplosion", ImVec2(280, 50)))
            {
                ToggleRPC(17);
                //Show(false);
            }
        }

        if(m_bSPN == 1){
            if(ImGui::Button("(O) SetPlayerName", ImVec2(280, 50)))
            {
                ToggleRPC(18);
                //Show(false);
            }
        }else{
            if(ImGui::Button("SetPlayerName", ImVec2(280, 50)))
            {
                ToggleRPC(18);
                //Show(false);
            }
        }

        if(m_bAGZ == 1){
            if(ImGui::Button("(O) AddGangZone", ImVec2(280, 50)))
            {
                ToggleRPC(19);
                //Show(false);
            }
        }else{
            if(ImGui::Button("AddGangZone", ImVec2(280, 50)))
            {
                ToggleRPC(19);
                //Show(false);
            }
        }

        if(m_bTPC == 1){
            if(ImGui::Button("(O) TogglePlayerControllable", ImVec2(280, 50)))
            {
                ToggleRPC(20);
                //Show(false);
            }
        }else{
            if(ImGui::Button("TogglePlayerControllable", ImVec2(280, 50)))
            {
                ToggleRPC(20);
                //Show(false);
            }
        }

        if(m_bSTD == 1){
            if(ImGui::Button("(O) ShowTextDraw", ImVec2(280, 50)))
            {
                ToggleRPC(21);
                //Show(false);
            }
        }else{
            if(ImGui::Button("ShowTextDraw", ImVec2(280, 50)))
            {
                ToggleRPC(21);
                //Show(false);
            }
        }

        if(m_bHTD == 1){
            if(ImGui::Button("(O) HideTextDraw", ImVec2(280, 50)))
            {
                ToggleRPC(22);
                //Show(false);
            }
        }else{
            if(ImGui::Button("HideTextDraw", ImVec2(280, 50)))
            {
                ToggleRPC(22);
                //Show(false);
            }
        }

        if(m_bSM == 1){
            if(ImGui::Button("(O) ShowMenu", ImVec2(280, 50)))
            {
                ToggleRPC(23);
                //Show(false);
            }
        }else{
            if(ImGui::Button("ShowMenu", ImVec2(280, 50)))
            {
                ToggleRPC(23);
                //Show(false);
            }
        }

        if(m_bHM == 1){
            if(ImGui::Button("(O) HideMenu", ImVec2(280, 50)))
            {
                ToggleRPC(24);
                //Show(false);
            }
        }else{
            if(ImGui::Button("HideMenu", ImVec2(280, 50)))
            {
                ToggleRPC(24);
                //Show(false);
            }
        }

        if(m_bSG == 1){
            if(ImGui::Button("(O) SetGravity", ImVec2(280, 50)))
            {
                ToggleRPC(25);
                //Show(false);
            }
        }else{
            if(ImGui::Button("SetGravity", ImVec2(280, 50)))
            {
                ToggleRPC(25);
                //Show(false);
            }
        }

        if(m_bSPS == 1){
            if(ImGui::Button("(O) SetPlayerSkin", ImVec2(280, 50)))
            {
                ToggleRPC(26);
                //Show(false);
            }
        }else{
            if(ImGui::Button("SetPlayerSkin", ImVec2(280, 50)))
            {
                ToggleRPC(26);
                //Show(false);
            }
        }

        if(m_bCO == 1){
            if(ImGui::Button("(O) CreateObject", ImVec2(280, 50)))
            {
                ToggleRPC(3);
                //Show(false);
            }
        }else{
            if(ImGui::Button("CreateObject", ImVec2(280, 50)))
            {
                ToggleRPC(3);
                //Show(false);
            }
        }

        if(m_bSD == 1){
            if(ImGui::Button("(O) ShowDialog", ImVec2(280, 50)))
            {
                ToggleRPC(6);
                //Show(false);
            }
        }else{
            if(ImGui::Button("ShowDialog", ImVec2(280, 50)))
            {
                ToggleRPC(6);
                //Show(false);
            }
        }

        if(m_bRPFV == 1){
            if(ImGui::Button("(O) RemovePlayerFromVehicle", ImVec2(280, 50)))
            {
                ToggleRPC(5);
                //Show(false);
            }
        }else{
            if(ImGui::Button("RemovePlayerFromVehicle", ImVec2(280, 50)))
            {
                ToggleRPC(5);
                //Show(false);
            }
        }

        
        if(m_bAPA == 1){
           if(ImGui::Button("(O) ApplyAnimations", ImVec2(280, 50)))
            {
                ToggleRPC(7);
                //Show(false);
            }
        }else{
            if(ImGui::Button("ApplyAnimations", ImVec2(280, 50)))
            {
                ToggleRPC(7);
                //Show(false);
            }
        }

         if(m_bCA == 1){
           if(ImGui::Button("(O) ClearAnimations", ImVec2(280, 50)))
            {
                ToggleRPC(12);
                //Show(false);
            }
        }else{
            if(ImGui::Button("ClearAnimations", ImVec2(280, 50)))
            {
                ToggleRPC(12);
                //Show(false);
            }
        }

        if(m_bVV == 1){
            if(ImGui::Button("(O) SetVehicleVelocity", ImVec2(280, 50)))
            {
                ToggleRPC(2);
                //Show(false);
            }
        }else{
            if(ImGui::Button("SetVehicleVelocity", ImVec2(280, 50)))
            {
                ToggleRPC(2);
                //Show(false);
            }
        }

        if(m_bCP == 1){
            if(ImGui::Button("(O) CreatePickup", ImVec2(280, 50)))
            {
                ToggleRPC(11);
                //Show(false);
            }
        }else{
            if(ImGui::Button("CreatePickup", ImVec2(280, 50)))
            {
                ToggleRPC(11);
                //Show(false);
            }
        }

        if(m_bVP == 1){
            if(ImGui::Button("(O) SetVehicleParams", ImVec2(280, 50)))
            {
                ToggleRPC(0);
                //Show(false);
            }
        }else{
            if(ImGui::Button("SetVehicleParams", ImVec2(280, 50)))
            {
                ToggleRPC(0);
                //Show(false);
            }
        }

        if(ImGui::Button("Close", ImVec2(280, 50)))
        {
            MATRIX4X4 mat;
            pGame->FindPlayerPed()->GetMatrix(&mat);
            pGame->PlaySound(1053, mat.pos.X, mat.pos.Y, mat.pos.Z);
            Show(false);
        }

        if(ImGui::Button("Back", ImVec2(280, 50)))
        {
            MATRIX4X4 mat;
            pGame->FindPlayerPed()->GetMatrix(&mat);
            pGame->PlaySound(1052, mat.pos.X, mat.pos.Y, mat.pos.Z);
            m_bMenuStep = 8;
        }
        break;

        case 10:
        ImGui::Text("Outcoming RPC");

        if(m_bGCW == 1){
            if(ImGui::Button("(O) GetCurrentWeapon", ImVec2(280, 50)))
            {
                ToggleRPC(10);
                //Show(false);
            }
        }else{
            if(ImGui::Button("GetCurrentWeapon", ImVec2(280, 50)))
            {
                ToggleRPC(10);
                //Show(false);
            }
        }

        if(m_bGPP == 1){
            if(ImGui::Button("(O) GetPlayerPos", ImVec2(280, 50)))
            {
                ToggleRPC(14);
                //Show(false);
            }
        }else{
            if(ImGui::Button("GetPlayerPos", ImVec2(280, 50)))
            {
                ToggleRPC(14);
                //Show(false);
            }
        }

        if(m_bEV == 1){
            if(ImGui::Button("(O) EnterVehicle", ImVec2(280, 50)))
            {
                ToggleRPC(16);
                //Show(false);
            }
        }else{
            if(ImGui::Button("EnterVehicle", ImVec2(280, 50)))
            {
                ToggleRPC(16);
                //Show(false);
            }
        }

        if(ImGui::Button("Close", ImVec2(280, 50)))
        {
            MATRIX4X4 mat;
            pGame->FindPlayerPed()->GetMatrix(&mat);
            pGame->PlaySound(1053, mat.pos.X, mat.pos.Y, mat.pos.Z);
            Show(false);
        }

        if(ImGui::Button("Back", ImVec2(280, 50)))
        {
            MATRIX4X4 mat;
            pGame->FindPlayerPed()->GetMatrix(&mat);
            pGame->PlaySound(1052, mat.pos.X, mat.pos.Y, mat.pos.Z);
            m_bMenuStep = 8;
        }
        break;

        case 11:
            ShowFlyMenu(true);
        break;

        case 12:
        ImGui::Text("GTA Patches");
        if(ImGui::Button("Money +", ImVec2(280, 50)))
        {
            MATRIX4X4 mat;
            pGame->FindPlayerPed()->GetMatrix(&mat);
            pGame->PlaySound(1053, mat.pos.X, mat.pos.Y, mat.pos.Z);
            pGame->AddToLocalMoney(100000000);
            //Show(false);
        }

        if(m_clock != 1)
        {
            if(ImGui::Button("Clock", ImVec2(280, 50)))
            {
                MATRIX4X4 mat;
                pGame->FindPlayerPed()->GetMatrix(&mat);
                pGame->PlaySound(1053, mat.pos.X, mat.pos.Y, mat.pos.Z);
                m_clock = 1;
                pGame->EnableClock(true);
            }
        }else{
            if(ImGui::Button("(O) Clock", ImVec2(280, 50)))
            {
                MATRIX4X4 mat;
                pGame->FindPlayerPed()->GetMatrix(&mat);
                pGame->PlaySound(1053, mat.pos.X, mat.pos.Y, mat.pos.Z);
                m_clock = 0;
                pGame->EnableClock(false);
            }
        }

        if(lock_time != 1)
        {
            if(ImGui::Button("Freeze Time", ImVec2(280, 50)))
            {
                MATRIX4X4 mat;
                pGame->FindPlayerPed()->GetMatrix(&mat);
                pGame->PlaySound(1053, mat.pos.X, mat.pos.Y, mat.pos.Z);
                lock_time = 1;
            }
        }else{
            if(ImGui::Button("(O) Freeze Time", ImVec2(280, 50)))
            {
                MATRIX4X4 mat;
                pGame->FindPlayerPed()->GetMatrix(&mat);
                pGame->PlaySound(1053, mat.pos.X, mat.pos.Y, mat.pos.Z);
                lock_time = 0;
            }
        } 

        if(lock_weather != 1)
        {
            if(ImGui::Button("Freeze Weather", ImVec2(280, 50)))
            {
                MATRIX4X4 mat;
                pGame->FindPlayerPed()->GetMatrix(&mat);
                pGame->PlaySound(1053, mat.pos.X, mat.pos.Y, mat.pos.Z);
                lock_weather = 1;
            }
        }else{
            if(ImGui::Button("(O) Freeze Weather", ImVec2(280, 50)))
            {
                MATRIX4X4 mat;
                pGame->FindPlayerPed()->GetMatrix(&mat);
                pGame->PlaySound(1053, mat.pos.X, mat.pos.Y, mat.pos.Z);
                lock_weather = 0;
            }
        } 

        if(radar != 1)
        {
            if(ImGui::Button("Radar", ImVec2(280, 50)))
            {
                MATRIX4X4 mat;
                pGame->FindPlayerPed()->GetMatrix(&mat);
                pGame->PlaySound(1053, mat.pos.X, mat.pos.Y, mat.pos.Z);
                ScriptCommand(&display_radar, 0);
                radar = 1;
            }
        }else{
            if(ImGui::Button("(O) Radar", ImVec2(280, 50)))
            {
                MATRIX4X4 mat;
                pGame->FindPlayerPed()->GetMatrix(&mat);
                pGame->PlaySound(1053, mat.pos.X, mat.pos.Y, mat.pos.Z);
                ScriptCommand(&display_radar, 1);
                radar = 0;
            }
        } 

        if(fastfire != 1){
            if(ImGui::Button("Fast Firing", ImVec2(280, 50)))
            {
                MATRIX4X4 mat;
                pGame->FindPlayerPed()->GetMatrix(&mat);
                pGame->PlaySound(1053, mat.pos.X, mat.pos.Y, mat.pos.Z);
                fastfire = 1;
            }
        }else{
            if(ImGui::Button("(O) Fast Firing", ImVec2(280, 50)))
            {
                MATRIX4X4 mat;
                pGame->FindPlayerPed()->GetMatrix(&mat);
                pGame->PlaySound(1053, mat.pos.X, mat.pos.Y, mat.pos.Z);
                fastfire = 0;
            }
        }

        if(carvisible != 1){
            if(ImGui::Button("Car Invisibility", ImVec2(280, 50)))
            {
                MATRIX4X4 mat;
                pGame->FindPlayerPed()->GetMatrix(&mat);
                pGame->PlaySound(1053, mat.pos.X, mat.pos.Y, mat.pos.Z);
                ScriptCommand(&set_car_visible, pGame->FindPlayerPed()->GetCurrentVehicleID(), 0);
                carvisible = 1;
            }
        }else{
            if(ImGui::Button("(O) Car Invisibility", ImVec2(280, 50)))
            {
                MATRIX4X4 mat;
                pGame->FindPlayerPed()->GetMatrix(&mat);
                pGame->PlaySound(1053, mat.pos.X, mat.pos.Y, mat.pos.Z);
                ScriptCommand(&set_car_visible, pGame->FindPlayerPed()->GetCurrentVehicleID(), 1);
                carvisible = 0;
            }
        }

        if(ImGui::Button("Close", ImVec2(280, 50)))
        {
            MATRIX4X4 mat;
            pGame->FindPlayerPed()->GetMatrix(&mat);
            pGame->PlaySound(1053, mat.pos.X, mat.pos.Y, mat.pos.Z);
            Show(false);
        }

        if(ImGui::Button("Back", ImVec2(280, 50)))
        {
            MATRIX4X4 mat;
            pGame->FindPlayerPed()->GetMatrix(&mat);
            pGame->PlaySound(1052, mat.pos.X, mat.pos.Y, mat.pos.Z);
            m_bMenuStep = 1;
        }
        break;
        case 13:
        ImGui::Text("Pos Master");

        if(ImGui::Button("Save Pos #1", ImVec2(280, 50)))
        {
            MATRIX4X4 mat;
            pGame->FindPlayerPed()->GetMatrix(&mat);
            pGame->PlaySound(1053, mat.pos.X, mat.pos.Y, mat.pos.Z);

            sPos1X = mat.pos.X;
            sPos1Y = mat.pos.Y;
            sPos1Z = mat.pos.Z;

            pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}Saved the pos #1");
        }

        if(ImGui::Button("Save Pos #2", ImVec2(280, 50)))
        {
            MATRIX4X4 mat;
            pGame->FindPlayerPed()->GetMatrix(&mat);
            pGame->PlaySound(1053, mat.pos.X, mat.pos.Y, mat.pos.Z);

            sPos2X = mat.pos.X;
            sPos2Y = mat.pos.Y;
            sPos2Z = mat.pos.Z;
            pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}Saved the pos #2");
        }

        if(ImGui::Button("Save Pos #3", ImVec2(280, 50)))
        {
            MATRIX4X4 mat;
            pGame->FindPlayerPed()->GetMatrix(&mat);
            pGame->PlaySound(1053, mat.pos.X, mat.pos.Y, mat.pos.Z);

            sPos3X = mat.pos.X;
            sPos3Y = mat.pos.Y;
            sPos3Z = mat.pos.Z;
            pChatWindow->AddInfoMessage("{FFEA0A}> {FFFFFF}Saved the pos #3");
        }

        if(ImGui::Button("Teleport Pos #1", ImVec2(280, 50)))
        {
            MATRIX4X4 mat;
            pGame->FindPlayerPed()->GetMatrix(&mat);
            pGame->PlaySound(1053, mat.pos.X, mat.pos.Y, mat.pos.Z);

            pGame->FindPlayerPed()->TeleportTo(sPos1X, sPos1Y, sPos1Z);
        }

        if(ImGui::Button("Teleport Pos #2", ImVec2(280, 50)))
        {
            MATRIX4X4 mat;
            pGame->FindPlayerPed()->GetMatrix(&mat);
            pGame->PlaySound(1053, mat.pos.X, mat.pos.Y, mat.pos.Z);

            pGame->FindPlayerPed()->TeleportTo(sPos2X, sPos2Y, sPos2Z);
        }

        if(ImGui::Button("Teleport Pos #3", ImVec2(280, 50)))
        {
            MATRIX4X4 mat;
            pGame->FindPlayerPed()->GetMatrix(&mat);
            pGame->PlaySound(1053, mat.pos.X, mat.pos.Y, mat.pos.Z);

            pGame->FindPlayerPed()->TeleportTo(sPos3X, sPos3Y, sPos3Z);
        }

        if(ImGui::Button("Close", ImVec2(280, 50)))
        {
            MATRIX4X4 mat;
            pGame->FindPlayerPed()->GetMatrix(&mat);
            pGame->PlaySound(1053, mat.pos.X, mat.pos.Y, mat.pos.Z);
            Show(false);
        }

        if(ImGui::Button("Back", ImVec2(280, 50)))
        {
            MATRIX4X4 mat;
            pGame->FindPlayerPed()->GetMatrix(&mat);
            pGame->PlaySound(1052, mat.pos.X, mat.pos.Y, mat.pos.Z);
            m_bMenuStep = 1;
        }
        break;
    }
    
    ImGui::SetWindowSize(ImVec2(-8, -8));
    ImVec2 size = ImGui::GetWindowSize();
    ImGui::SetWindowPos( ImVec2( ((io.DisplaySize.x - size.x + 435)/2), ((io.DisplaySize.y - size.y)/2) ) );
    ImGui::End();
    ImGui::PopStyleVar();
}