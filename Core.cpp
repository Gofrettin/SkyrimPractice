#include "Core.h"

/*Used Resources
Skyrim GH Tutorial -> https://guidedhacking.com/threads/skyrim-hack-tutorial-series-esp-entitylist-noclip-cheats.13072/
Radar Funcs -> https://guidedhacking.com/threads/c-cs-go-radar-source-code.11914/ -> Modified it to work with skyrim
Rendering with Steam Overlay -> https://aixxe.net/2017/09/steam-overlay-rendering
Detour Class -> https://guidedhacking.com/threads/broihons-memory-stuff.8771/
Vector Class -> https://www.unknowncheats.me/forum/c-and-c/157292-variadic-vector-class.html

THIS CODE STILL NEEDS WORK :)

*/

//Detour DetourUtilReset = Detour();
//Detour DetourUtilPresent = Detour();
//Detour DetourUtilEndScene = Detour();
Detour DetourEntityHook = Detour();
Detour DetourNoclipHook = Detour();

void hBuildItems()
{
	hMenu->AddGroup((char*)("[ Visual ]"), &hMenuFolder[1], (char**)(hFld), 2);
	if (hMenuFolder[1])
	{
		hMenu->AddItem((char*)("CrossHair"), &hMenuItem[1], (char**)(hOpt), 2);
		hMenu->AddItem((char*)("ESP"), &hMenuItem[2], (char**)(hOpt), 2);
		hMenu->AddItem((char*)("Radar"), &hMenuItem[3], (char**)(hOpt), 2);
	}

	hMenu->AddGroup((char*)("[ Etc... ]"), &hMenuFolder[2], (char**)(hFld), 2);
	if (hMenuFolder[2]) {
		hMenu->AddItem((char*)("Dupe"), &hMenuItem[4], (char**)(hOpt), 2);
		hMenu->AddItem((char*)("God Mode"), &hMenuItem[5], (char**)(hOpt), 2);
		hMenu->AddItem((char*)("No Gravity"), &hMenuItem[6], (char**)(hOpt), 2);
		hMenu->AddItem((char*)("No Clip"), &hMenuItem[7], (char**)(hOpt), 2);
	}

	hMenu->AddGroup((char*)("[ Settings ]"), &hMenuFolder[3], (char**)(hFld), 2);
	if (hMenuFolder[3])
	{
		hMenu->AddItem((char*)("Mouse Control"), &hMenuSettings[2], (char**)(hOpt), 2);
		hMenu->AddItem((char*)("Move Menu"), &hMenuSettings[3], (char**)(hOpt), 2);
		hMenu->AddItem((char*)("Reset"), &hMenuSettings[4], (char**)(hOpt), 2);
		hMenu->AddItem((char*)("Exit"), &hMenuSettings[5], (char**)(hOpt), 2);
	}
}

void hBuildMenu(IDirect3DDevice9* pDevice)
{
	if (!hMenu)
	{
		hMenu = new hMenuCore((char*)("Skyrim"), 100, 155, 15);
		hMenu->visible = 1;
		hMenu->col_title = hWhite;
	}
	else {
		if (!hMenu->noitems)
			hBuildItems();
		if (hMenu->visible == 1)
		{
			//Title Box
			hMenu->hDrawBox((int)hMenu->x - 7, (int)hMenu->y - 10, (int)hMenu->totwidth, (float)21, hTransparent, pDevice);
			hMenu->hDrawRectangle((int)hMenu->x - 7, hMenu->y - 10, (int)hMenu->totwidth, (float)21, 1, hWhite, pDevice);

			//Item Box
			hMenu->hDrawBox((int)hMenu->x - 7, (int)hMenu->y + 15, (int)hMenu->totwidth, (float)hMenu->noitems * hMenu->height + 12, hTransparent, pDevice);
			hMenu->hDrawRectangle((int)hMenu->x - 7, hMenu->y + 15, (int)hMenu->totwidth, (float)hMenu->noitems * hMenu->height + 12, 1, hWhite, pDevice);

			//Credits Box
			hMenu->hDrawBox((int)hMenu->x - 7, (int)(hMenu->y + hMenu->totheight) + 11, (int)hMenu->totwidth, (float)21, hTransparent, pDevice);
			hMenu->hDrawRectangle((int)hMenu->x - 7, (hMenu->y + hMenu->totheight) + 11, (int)hMenu->totwidth, (float)21, 1, hWhite, pDevice);
			hMenu->DrawTextShadowC((int)hMenu->x + (hMenu->totwidth / 2), hMenu->max_y + 15, hWhite, (char*)("Menu"), pFont);

		}
		hMenu->Show(pFont, pDevice);
		hMenu->Nav();
	}
}

#pragma region Hooked Functions
HRESULT __stdcall userReset(IDirect3DDevice9* pDevice, D3DPRESENT_PARAMETERS* pPresentationParameters) {
	pFont->OnLostDevice();
	HRESULT hTorna = oReset(pDevice, pPresentationParameters);
	if (SUCCEEDED(hTorna))
	{
		pFont->OnResetDevice();
	}
	return hTorna;
}

HRESULT __stdcall userPresent(IDirect3DDevice9* pDevice, const RECT* src, const RECT* dest, HWND wnd_override, const RGNDATA* dirty_region) {
	pDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
	hCreateFont(pDevice);
	hBuildMenu(pDevice);
	hBuildHacks(pDevice);
	pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
	return oPresent(pDevice, src, dest, wnd_override, dirty_region);
}

HRESULT __stdcall userEndScene(IDirect3DDevice9* pDevice) {
	return oEndScene(pDevice);
}
#pragma endregion

void hThread()
{
#pragma region Vtable Hook
	//PDWORD D3DVTable;
	//do
	//{
	//	*(DWORD*)&D3DVTable = *(DWORD*)hD3D9VTable();
	//} while (!D3DVTable);
	//oReset = (tReset)DetourUtilReset.CreateDetour((void*)D3DVTable[16], (void*)userReset, 5, true);
	//oPresent = (tPresent)DetourUtilPresent.CreateDetour((void*)D3DVTable[17], (void*)userPresent, 5, true);
	//oEndScene = (tEndScene)DetourUtilEndScene.CreateDetour((void*)D3DVTable[42], (void*)userEndScene, 7, true);
#pragma endregion

#pragma region gameoverlay.dll Hook
	MODULEINFO gameOverlayInfo = GetModuleInfo("gameoverlayrenderer.dll");
	presentAddr = ((uintptr_t)find_signature("FF 15 ? ? ? ? 8B F8 85 DB", (uint8_t*)gameOverlayInfo.lpBaseOfDll, gameOverlayInfo.SizeOfImage)) + 2;
	resetAddr = ((uintptr_t)find_signature("FF 15 ? ? ? ? 8B F8 85 FF 78 18", (uint8_t*)gameOverlayInfo.lpBaseOfDll, gameOverlayInfo.SizeOfImage)) + 2;
	oPresent = **reinterpret_cast<decltype(&oPresent)*>(presentAddr);
	oReset = **reinterpret_cast<decltype(&oReset)*>(resetAddr);
	**reinterpret_cast<void***>(presentAddr) = reinterpret_cast<void*>(&userPresent);
	**reinterpret_cast<void***>(resetAddr) = reinterpret_cast<void*>(&userReset);
#pragma endregion
	
	modInfo = GetModuleInfo(const_cast<char*>(PROCESS_NAME.c_str()));

	DWORD entityAddy = (DWORD)find_signature("8B 56 34 8B 46 38 8B 4E 3C 8D 7E 34", (uint8_t*)modInfo.lpBaseOfDll, modInfo.SizeOfImage);
	EntlistJmpBack = entityAddy + 0x6;
	DetourEntityHook.CreateDetour((void*)entityAddy, (void*)entityhook, 6, true);

	DWORD noclipAddy = (DWORD)find_signature("8B 52 78 D9 42 0C 8B 01", (uint8_t*)modInfo.lpBaseOfDll, modInfo.SizeOfImage);
	noclipJmpBack = noclipAddy + 0x6;
	DetourNoclipHook.CreateDetour((void*)noclipAddy, (void*)nocliphook, 6, true);
	
	LocalPlayerPtr = (DWORD)find_signature("1C 20 0D 01 00 00 00", (uint8_t*)0x12000000, (size_t)0xFFFFFF);
	LocalPlayer = (playerent*)(LocalPlayerPtr);

	ViewMatrix = (DWORD)modInfo.lpBaseOfDll + 0x173EA10;
	Waypoint = (DWORD)modInfo.lpBaseOfDll + 0x1740298;
	LoadingScreen = (DWORD)modInfo.lpBaseOfDll + 0x17337CC;
	GodMode = (DWORD)modInfo.lpBaseOfDll + 0x17398C4;
	Gravity = (DWORD)modInfo.lpBaseOfDll + 0xED65B4;

	DupePatch.CreatePatch(0x47F89F, (PBYTE)("\x01\x41\x08"), false);
}

void settingsThread(HMODULE hMod)
{
	for (;;)
	{
		hSettings();
		Sleep(5);
		if (menu_exit) {

#pragma region Vtable unhook
			//DetourUtilReset.Remove();
			//DetourUtilPresent.Remove();
			//DetourUtilEndScene.Remove();
#pragma endregion

#pragma region gameoverlay.dll unhook
			** reinterpret_cast<void***>(presentAddr) = *reinterpret_cast<void**>(&oPresent);
			**reinterpret_cast<void***>(resetAddr) = *reinterpret_cast<void**>(&oReset);
#pragma endregion

			DetourEntityHook.Remove();
			DetourNoclipHook.Remove();

			DupePatch.Remove();

			Sleep(50);
			FreeLibraryAndExitThread(hMod, 0);
		}
	}
	Sleep(20);
}

BOOL APIENTRY DllMain(HMODULE hMod, DWORD hReason, LPVOID hReserved)
{
	DisableThreadLibraryCalls(hMod);
	if (hReason == DLL_PROCESS_ATTACH)
	{
		CreateThread(0, 0, (LPTHREAD_START_ROUTINE)hThread, hMod, 0, 0);
		CreateThread(0, 0, (LPTHREAD_START_ROUTINE)settingsThread, hMod, 0, 0);
	}
	return TRUE;
}