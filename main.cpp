#include <jni.h>
#include <android/log.h>
#include <ucontext.h>
#include <pthread.h>

#include "main.h"
#include "game/game.h"
#include "game/RW/RenderWare.h"
#include "net/netgame.h"
#include "gui/gui.h"
#include "chatwindow.h"
#include "spawnscreen.h"
#include "playertags.h"
#include "dialog.h"
#include "keyboard.h"
#include "extrakeyboard.h"
#include "settings.h"
#include "debug.h"
#include "modsa.h"
#include "servers.h"
#include "sets.h"
#include "timer.hpp"
#include "customserver.h"
#include "menu.h"
#include "textdraw.h"
#include "playerslist.h"
//#include "shpora.h"
#include "skinchanger.h"

#include "util/armhook.h"
#include "checkfilehash.h"

uintptr_t g_libGTASA = 0;

const char* g_pszStorage = nullptr;

CGame *pGame = nullptr;
CNetGame *pNetGame = nullptr;

CDialogWindow *pDialogWindow = nullptr;
CModSAWindow *pModSAWindow = nullptr;
CServersWindow *pServersWindow = nullptr;
CSetsWindow *pSetsWindow = nullptr;
CCustomServerWindow *pCustomServer = nullptr;
CSkinChanger *pSkinChanger = nullptr;
//CShpora *pShpora = nullptr;

CChatWindow *pChatWindow = nullptr;
CSpawnScreen *pSpawnScreen = nullptr;
CMenu *pMenu = nullptr;
CTextDraw *pTextDraw = nullptr;
CPlayersList *pPlayersList = nullptr;
CPlayerTags *pPlayerTags = nullptr;

CGUI *pGUI = nullptr;
CKeyBoard *pKeyBoard = nullptr;
CExtraKeyBoard *pExtraKeyBoard = nullptr;
CDebug *pDebug = nullptr;
CSettings *pSettings = nullptr;

void InitHookStuff();
void InstallSpecialHooks();
void InitRenderWareFunctions();
void ApplyInGamePatches();
void ApplyPatches_level0();
void MainLoop();

void InitSAMP()
{
	Log("Initializing SAMP..");
	g_pszStorage = (const char*)(g_libGTASA+0x63C4B8);

	if(!g_pszStorage)
	{
		Log("Error: storage path not found!");
		std::terminate();
		return;
	}

	Log("Storage 1: %s", g_pszStorage);

	pSettings = new CSettings();
}

void InitInMenu()
{
	pGame = new CGame();
	pGame->InitInMenu();
	
	if(pSettings->Get().bDebug)
		pDebug = new CDebug();

	pGUI = new CGUI();
	pSkinChanger = new CSkinChanger();
	//pPlayersList = new CPlayersList();
	//pShpora = new CShpora();
	pDialogWindow = new CDialogWindow();
	pExtraKeyBoard = new CExtraKeyBoard();
	pMenu = new CMenu();
	pTextDraw = new CTextDraw();
	pModSAWindow = new CModSAWindow();
	pServersWindow = new CServersWindow();
	pKeyBoard = new CKeyBoard();
	pPlayerTags = new CPlayerTags();
	pChatWindow = new CChatWindow();
	pSpawnScreen = new CSpawnScreen();
	pSetsWindow = new CSetsWindow();
	pCustomServer = new CCustomServerWindow();
}

void InitInGame()
{
	static bool bGameInited = false;
	static bool bNetworkInited = false;

	if(!bGameInited)
	{
		pGame->InitInGame();
		pGame->SetMaxStats();

		if(pDebug && !pSettings->Get().bOnline)pDebug->SpawnLocalPlayer();

		bGameInited = true;
		return;
	}

	if(!bNetworkInited && pSettings->Get().bOnline)
	{
		pModSAWindow->Clear();
		pSetsWindow->Clear();
		pSetsWindow->Show(true);
		bNetworkInited = true;
		return;
	}
}

void MainLoop()
{
	InitInGame();

	if(pDebug) pDebug->Process();
	if(pNetGame) pNetGame->Process();
}

void handler(int signum, siginfo_t *info, void* contextPtr)
{
	ucontext* context = (ucontext_t*)contextPtr;

	if(info->si_signo == SIGSEGV)
	{
		Log("SIGSEGV | Fault address: 0x%X", info->si_addr);
		Log("libGTASA base address: 0x%X", g_libGTASA);
		Log("register states:");

		Log("r0: 0x%X, r1: 0x%X, r2: 0x%X, r3: 0x%X", 
			context->uc_mcontext.arm_r0, 
			context->uc_mcontext.arm_r1, 
			context->uc_mcontext.arm_r2,
			context->uc_mcontext.arm_r3);
		Log("r4: 0x%x, r5: 0x%x, r6: 0x%x, r7: 0x%x",
			context->uc_mcontext.arm_r4,
			context->uc_mcontext.arm_r5,
			context->uc_mcontext.arm_r6,
			context->uc_mcontext.arm_r7);
		Log("r8: 0x%x, r9: 0x%x, sl: 0x%x, fp: 0x%x",
			context->uc_mcontext.arm_r8,
			context->uc_mcontext.arm_r9,
			context->uc_mcontext.arm_r10,
			context->uc_mcontext.arm_fp);
		Log("ip: 0x%x, sp: 0x%x, lr: 0x%x, pc: 0x%x",
			context->uc_mcontext.arm_ip,
			context->uc_mcontext.arm_sp,
			context->uc_mcontext.arm_lr,
			context->uc_mcontext.arm_pc);

		Log("> backtrace:");
		Log("1: libGTASA.so + 0x%X", context->uc_mcontext.arm_pc - g_libGTASA);
		Log("2: libGTASA.so + 0x%X", context->uc_mcontext.arm_lr - g_libGTASA);

		exit(0);
	}

	return;
}

void *Init(void *p)
{
	ApplyPatches_level0();

	pthread_exit(0);
}

jint JNI_OnLoad(JavaVM *vm, void *reserved)
{
	Log("SAMP library loaded! Build time: " __DATE__ " " __TIME__);

	g_libGTASA = FindLibrary("libGTASA.so");
	if(g_libGTASA == 0)
	{
		Log("ERROR: libGTASA.so address not found!");
		return 0;
	}

	Log("libGTASA.so image base address: 0x%X", g_libGTASA);

	srand(time(0));

	InitHookStuff();
	InitRenderWareFunctions();
	InstallSpecialHooks();

	pthread_t thread;
	pthread_create(&thread, 0, Init, 0);

	struct sigaction act;
	act.sa_sigaction = handler;
	sigemptyset(&act.sa_mask);
	act.sa_flags = SA_SIGINFO;
	sigaction(SIGSEGV, &act, 0);

	return JNI_VERSION_1_4;
}

void Log(const char *fmt, ...)
{	
	char buffer[0xFF];
	static FILE* flLog = nullptr;

	if(flLog == nullptr && g_pszStorage != nullptr)
	{
		sprintf(buffer, "%sSAMP/samp_log.txt", g_pszStorage);
		flLog = fopen(buffer, "a");
	}

	memset(buffer, 0, sizeof(buffer));

	va_list arg;
	va_start(arg, fmt);
	vsnprintf(buffer, sizeof(buffer), fmt, arg);
	va_end(arg);

	__android_log_write(ANDROID_LOG_INFO, "AXL", buffer);

	if(pDebug) pDebug->AddMessage(buffer);

	if(flLog == nullptr) return;
	fprintf(flLog, "%s\n", buffer);
	fflush(flLog);

	return;
}

uint32_t GetTickCount()
{
	struct timeval tv;
	gettimeofday(&tv, nullptr);
	return (tv.tv_sec*1000+tv.tv_usec/1000);
}
