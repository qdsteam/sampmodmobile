#include "../main.h"
#include "RW/RenderWare.h"
#include "game.h"
#include "gui/gui.h"

extern CGUI *pGUI;

RwTexture *splashTexture = nullptr;

#define COLOR_WHITE		0xFFFFFFFF
#define COLOR_BLACK 	0xFF000000
#define COLOR_ORANGE 	0xFF00A5FF
#define COLOR_ROSE		0xFFFF99FF
#define COLOR_BRED		0xFF9933FF
#define COLOR_BLUE		0xFF6C2713
#define COLOR_CYAN		0xFFCE6816
#define COLOR_1			0xFFB58891
#define COLOR_2			0xFF673F40

struct stRect
{
	int x1;	// left
	int y1;	// top
	int x2;	// right
	int y2;	// bottom
};

struct stfRect
{
	float x1;
	float y1;
	float x2;
	float y2;
};

#define MAX_SCHEMAS 4
uint32_t colors[MAX_SCHEMAS][2] = {
	{ COLOR_ROSE,	COLOR_BRED },
	{ COLOR_BLACK, 	COLOR_ORANGE },
	{ COLOR_CYAN,	COLOR_BLUE },
	{ COLOR_1,		COLOR_2 }
};
unsigned int color_scheme = 0;

void LoadSplashTexture()
{
	Log("Loading splash texture..");
	splashTexture = (RwTexture*)LoadTextureFromDB("samp", "mylogo");

	color_scheme = 1;//rand() % MAX_SCHEMAS;
}

void Draw(stRect *rect, uint32_t color, RwRaster *raster = nullptr, stfRect *uv = nullptr)
{
	
}

void RenderSplash()
{
	
}

void ImGui_ImplRenderWare_RenderDrawData(ImDrawData* draw_data);
void ImGui_ImplRenderWare_NewFrame();

void RenderSplashScreen()
{

	if(!pGUI) return;

	ImGuiIO& io = ImGui::GetIO();

	ImGui_ImplRenderWare_NewFrame();
	ImGui::NewFrame();
	ImGui::GetBackgroundDrawList()->AddText(ImVec2((io.DisplaySize.x)/2, (io.DisplaySize.y)/2), 0xF60000AA, 
		"\n\t"
		u8"Loading MultiPlayer...");
	ImGui::GetBackgroundDrawList()->AddText(ImVec2((io.DisplaySize.x)/2, (io.DisplaySize.y - 100)/2), 0xAAAAAAAA, 
		"\n\t"
		u8"vk.com/mobile.samp");

	ImGui::EndFrame();
	ImGui::Render();
	ImGui_ImplRenderWare_RenderDrawData(ImGui::GetDrawData());
}