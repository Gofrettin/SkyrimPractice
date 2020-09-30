#pragma once
#ifndef _MENU_H_
#define _MENU_H_

#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <time.h>
#include <stdio.h>

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

#pragma warning(disable: 4244)
#pragma warning(disable: 4996)
#pragma warning(disable: 4390)

#define hFolder 1
#define hText   2
#define hItem   3
#define hSubFd  4

#define hWhite          D3DCOLOR_ARGB(255,255,255,255) 
#define hRed            D3DCOLOR_ARGB(255,255,0,0) 
#define hGreen          D3DCOLOR_ARGB(255,0,255,0)
#define hBlue           D3DCOLOR_ARGB(255,0,0,255)
#define hBlack          D3DCOLOR_ARGB(255,0,0,0)
#define hPurple         D3DCOLOR_ARGB(255,125,0,255)
#define hGrey           D3DCOLOR_ARGB(255,128,128,128)
#define hGrey2          D3DCOLOR_ARGB(150,50,50,50)
#define hYellow         D3DCOLOR_ARGB(255,255,255,0)
#define hOrange         D3DCOLOR_ARGB(255,255,140,0)
#define hCyan           D3DCOLOR_ARGB(255,0,139,200)
#define hPink           D3DCOLOR_ARGB(255,255,192,203)
#define hLightBlue      D3DCOLOR_ARGB(255, 66, 180, 230)
#define hTransparent    D3DCOLOR_ARGB(100, 0, 0, 0)

#define hMOn	  hGreen
#define hMOff	  hWhite
#define hMFolder  hYellow
#define hMText	  hWhite
#define hMCurrent hOrange

typedef struct
{
	int  typ;
	char* txt;
	char** opt;
	int* var;
	int  maxval;
}tMENU;

class hMenuCore
{
public:
	hMenuCore(char* Name = 0, int maxentries = 130, int maxwidth = 300, int maxheight = 15)
	{
		title = Name;
		maxitems = maxentries;
		cur = noitems = visible = 0;
		x = 15;
		y = 17;
		totwidth = maxwidth;
		height = maxheight;
		titleheight = totheight = height + 5;
		col_group = hMFolder;
		col_text = hMText;
		col_off = hMOff;
		col_on = hMOn;
		col_current = hMCurrent;
		MENU = (tMENU**)malloc(4 * maxitems);
		for (int i = 0; i < maxitems; i++) MENU[i] = (tMENU*)malloc(sizeof(tMENU));
	}
	~hMenuCore() {
		for (int i = 0; i < maxitems; i++) free(MENU[i]);
		free(MENU);
	}

	DWORD col_title;
	DWORD col_group;
	DWORD col_group1;
	DWORD col_text;
	DWORD col_off;
	DWORD col_on;
	DWORD col_current;

	int x, y;
	int totwidth, totheight;
	int height;
	int titleheight;
	int max_x, max_y;
	int m_x, m_y;
	int m_lm, m_rm;
	char* title;
	int cur;
	int noitems;
	int visible;
	int moving;

	tMENU** MENU;

	void Save(char* szSection, char* szKey, int iValue);
	int  Load(char* szSection, char* szKey, int iDefaultValue);
	void AddItem(char* txt, int* var, char** opt, int maxvalue = 2, int typ = hItem);
	void AddGroup(char* txt, int* var, char** opt, int maxvalue = 2);
	void AddSubb(char* txt, int* var, char** opt, int maxvalue = 2);
	void AddText(char* txt, char* opt = (char*)"");
	void Show(ID3DXFont* pFont1, IDirect3DDevice9* pDevice);
	void Nav(void);
	void CheckTitleMove(int rm, int mx, int my);
	void DrawText(CHAR* Text, INT PosX, INT PosY, DWORD Color, ID3DXFont* pFont);
	void DrawTextR(int x, int y, DWORD color, char* text, ID3DXFont* pFont);
	void DrawTextL(int x, int y, DWORD color, char* text, ID3DXFont* pFont);
	void DrawTextC(int x, int y, DWORD color, char* text, ID3DXFont* pFont);
	void DrawTextShadow(CHAR* Text, INT PosX, INT PosY, DWORD Color, ID3DXFont* pFont);
	void DrawTextShadowR(INT PosX, INT PosY, DWORD Color, CHAR* Text, ID3DXFont* pFont);
	void DrawTextShadowL(INT PosX, INT PosY, DWORD Color, CHAR* Text, ID3DXFont* pFont);
	void DrawTextShadowC(INT PosX, INT PosY, DWORD Color, CHAR* Text, ID3DXFont* pFont);
	void hDrawBox(int x, int y, int w, int h, D3DCOLOR Color, IDirect3DDevice9* pDevice);
	void hDrawBox_s(IDirect3DDevice9* pDevice, int x, int y, int w, int h, DWORD Color);
	void hDrawRectangle(int x, int y, int w, int h, int s, DWORD Color, IDirect3DDevice9* pDevice);
	void hDrawMouse(D3DXVECTOR2 Pos, D3DCOLOR Color, IDirect3DDevice9* pDevice);
	void DisableAllMenuItems();

private:
	int	maxitems;
	int dx, dy;
	int FindItem(void);

};

#endif// _MENU_H_