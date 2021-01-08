#pragma once
#include "Menu.h"
#include "Hacks.h"
#include "D3D9VtableIndex.h"

void hCreateFont(IDirect3DDevice9* pDevice) {
	if (pFont == NULL) {
		D3DXCreateFont(pDevice, 14, 6, 500, 1, 0, 1, 0, 4, 0 | (0 << 4), "Calibri", &pFont);
	}
	else {
		if (hDevice != pDevice) {
			hDevice = pDevice;
			try {
				if (pFont != 0) pFont->Release();

			}
			catch (...) {}

			pFont = 0;
			D3DXCreateFont(pDevice, 14, 6, 500, 1, 0, 1, 0, 4, 0 | (0 << 4), "Calibri", &pFont);
		}
	}
}

DWORD hD3D9VTable() {
	DWORD dwObjBase = (DWORD)LoadLibraryA("D3D9.DLL");
	while (dwObjBase++ < dwObjBase + 0x127850) {
		if ((*(WORD*)(dwObjBase + 0x00)) == 0x06C7 && (*(WORD*)(dwObjBase + 0x06)) == 0x8689 && (*(WORD*)(dwObjBase + 0x0C)) == 0x8689) {
			dwObjBase += 2;
			break;
		}
	}
	return (dwObjBase);
}

#pragma region typedefs
std::uintptr_t presentAddr = 0;
std::uintptr_t resetAddr = 0;
std::uintptr_t endsceneAddr = 0;

typedef HRESULT(__stdcall* tPresent) (IDirect3DDevice9* pDevice, const RECT* pSourceRect, const RECT* pDestRect, HWND hDestWindowOverride, const RGNDATA* pDirtyRegion);
tPresent oPresent;

typedef HRESULT(__stdcall* tReset) (IDirect3DDevice9* pDevice, D3DPRESENT_PARAMETERS* pPresentationParameters);
tReset oReset;

typedef HRESULT(__stdcall* tEndScene)(IDirect3DDevice9* pDevice);
tEndScene oEndScene;
#pragma endregion

#pragma region DummyDeviceMethod
static HWND window;
void* d3d9Device[119];

BOOL CALLBACK EnumWindowsCallback(HWND handle, LPARAM lParam) {
	DWORD wndProcId;
	GetWindowThreadProcessId(handle, &wndProcId);
	if (GetCurrentProcessId() != wndProcId)
		return TRUE; // skip to next window
	window = handle;
	return FALSE; // window found abort search
}

HWND GetProcessWindow() {
	window = NULL;
	EnumWindows(EnumWindowsCallback, NULL);
	return window;
}

bool GetD3D9Device(void** pTable, size_t Size) {
	if (!pTable)
		return false;
	IDirect3D9* pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (!pD3D)
		return false;
	IDirect3DDevice9* pDummyDevice = NULL;
	// options to create dummy device
	D3DPRESENT_PARAMETERS d3dpp = {};
	d3dpp.Windowed = false;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.hDeviceWindow = GetProcessWindow();
	HRESULT dummyDeviceCreated = pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, d3dpp.hDeviceWindow, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &pDummyDevice);
	if (dummyDeviceCreated != S_OK) {
		// may fail in windowed fullscreen mode, trying again with windowed mode
		d3dpp.Windowed = !d3dpp.Windowed;
		dummyDeviceCreated = pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, d3dpp.hDeviceWindow, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &pDummyDevice);
		if (dummyDeviceCreated != S_OK) {
			pD3D->Release();
			return false;
		}
	}
	memcpy(pTable, *reinterpret_cast<void***>(pDummyDevice), Size);
	pDummyDevice->Release();
	pD3D->Release();
	return true;
}
#pragma endregion