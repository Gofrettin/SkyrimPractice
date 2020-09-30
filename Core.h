#pragma once
#include "Menu.h"
#include "Hacks.h"
#include "D3D9VtableIndex.h"

void hCreateFont(IDirect3DDevice9* pDevice)
{
	if (pFont == NULL)
	{
		D3DXCreateFont(pDevice, 14, 6, 500, 1, 0, 1, 0, 4, 0 | (0 << 4), "Calibri", &pFont);
	}
	else
	{
		if (hDevice != pDevice)
		{
			hDevice = pDevice;

			try
			{
				if (pFont != 0) pFont->Release();

			}
			catch (...) {}

			pFont = 0;
			D3DXCreateFont(pDevice, 14, 6, 500, 1, 0, 1, 0, 4, 0 | (0 << 4), "Calibri", &pFont);
		}
	}
}

DWORD hD3D9VTable()
{
	DWORD dwObjBase = (DWORD)LoadLibraryA("D3D9.DLL");
	while (dwObjBase++ < dwObjBase + 0x127850)
	{
		if ((*(WORD*)(dwObjBase + 0x00)) == 0x06C7 && (*(WORD*)(dwObjBase + 0x06)) == 0x8689 && (*(WORD*)(dwObjBase + 0x0C)) == 0x8689)
		{
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