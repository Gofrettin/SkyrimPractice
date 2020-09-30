#include "Menu.h"

char file[255];

bool mouse_enabled;
bool menu_move;
bool menu_exit = false;

POINT mpos;

void hMenuCore::AddItem(char* txt, int* var, char** opt, int maxval, int typ)
{
	if (noitems >= (maxitems - 3)) return;
	MENU[noitems]->typ = typ;
	MENU[noitems]->txt = txt;
	MENU[noitems]->opt = opt;
	MENU[noitems]->var = var;
	MENU[noitems]->maxval = maxval;
	noitems++;
	totheight = (noitems * height) + titleheight;
}

void hMenuCore::AddGroup(char* txt, int* var, char** opt, int maxval)
{
	AddItem(txt, var, opt, maxval, hFolder);
}

void hMenuCore::AddSubb(char* txt, int* var, char** opt, int maxval)
{
	AddItem(txt, var, opt, maxval, hSubFd);
}

void hMenuCore::AddText(char* txt, char* opt)
{
	AddItem(txt, 0, (char**)opt, 0, hText);
}

void hMenuCore::DrawText(CHAR* Text, INT PosX, INT PosY, DWORD Color, ID3DXFont* pFont)
{
	RECT Rect;
	SetRect(&Rect, PosX, PosY, PosX, PosY);
	pFont->DrawTextA(0, Text, -1, &Rect, DT_NOCLIP, Color);
}

void hMenuCore::DrawTextL(int x, int y, DWORD color, char* text, ID3DXFont* pFont)
{
	RECT rect;
	SetRect(&rect, x, y, x, y);
	pFont->DrawTextA(NULL, text, -1, &rect, DT_LEFT | DT_NOCLIP, color);
}

void hMenuCore::DrawTextR(int x, int y, DWORD color, char* text, ID3DXFont* pFont)
{
	RECT rect;
	SetRect(&rect, x, y, x, y);
	pFont->DrawTextA(NULL, text, -1, &rect, DT_RIGHT | DT_NOCLIP, color);
}

void hMenuCore::DrawTextC(int x, int y, DWORD color, char* text, ID3DXFont* pFont)
{
	RECT rect;
	SetRect(&rect, x, y, x, y);
	pFont->DrawTextA(NULL, text, -1, &rect, DT_CENTER | DT_NOCLIP, color);
}

void hMenuCore::DrawTextShadow(CHAR* Text, INT PosX, INT PosY, DWORD Color, ID3DXFont* pFont)
{
	DrawText(Text, (float)PosX + 1, (float)PosY, D3DCOLOR_ARGB(255, 0, 0, 0), pFont);
	DrawText(Text, (float)PosX - 1, (float)PosY, D3DCOLOR_ARGB(255, 0, 0, 0), pFont);
	DrawText(Text, (float)PosX, (float)PosY + 1, D3DCOLOR_ARGB(255, 0, 0, 0), pFont);
	DrawText(Text, (float)PosX, (float)PosY - 1, D3DCOLOR_ARGB(255, 0, 0, 0), pFont);

	DrawText(Text, (float)PosX, (float)PosY, Color, pFont);
}

void hMenuCore::DrawTextShadowL(INT PosX, INT PosY, DWORD Color, CHAR* Text, ID3DXFont* pFont)
{
	DrawTextL((float)PosX + 1, (float)PosY, D3DCOLOR_ARGB(255, 0, 0, 0), Text, pFont);
	DrawTextL((float)PosX - 1, (float)PosY, D3DCOLOR_ARGB(255, 0, 0, 0), Text, pFont);
	DrawTextL((float)PosX, (float)PosY + 1, D3DCOLOR_ARGB(255, 0, 0, 0), Text, pFont);
	DrawTextL((float)PosX, (float)PosY - 1, D3DCOLOR_ARGB(255, 0, 0, 0), Text, pFont);

	DrawTextL((float)PosX, (float)PosY, Color, Text, pFont);
}

void hMenuCore::DrawTextShadowR(INT PosX, INT PosY, DWORD Color, CHAR* Text, ID3DXFont* pFont)
{
	DrawTextR((float)PosX + 1, (float)PosY, D3DCOLOR_ARGB(255, 0, 0, 0), Text, pFont);
	DrawTextR((float)PosX - 1, (float)PosY, D3DCOLOR_ARGB(255, 0, 0, 0), Text, pFont);
	DrawTextR((float)PosX, (float)PosY + 1, D3DCOLOR_ARGB(255, 0, 0, 0), Text, pFont);
	DrawTextR((float)PosX, (float)PosY - 1, D3DCOLOR_ARGB(255, 0, 0, 0), Text, pFont);

	DrawTextR((float)PosX, (float)PosY, Color, Text, pFont);
}

void hMenuCore::DrawTextShadowC(INT PosX, INT PosY, DWORD Color, CHAR* Text, ID3DXFont* pFont)
{
	DrawTextC((float)PosX + 1, (float)PosY, D3DCOLOR_ARGB(255, 0, 0, 0), Text, pFont);
	DrawTextC((float)PosX - 1, (float)PosY, D3DCOLOR_ARGB(255, 0, 0, 0), Text, pFont);
	DrawTextC((float)PosX, (float)PosY + 1, D3DCOLOR_ARGB(255, 0, 0, 0), Text, pFont);
	DrawTextC((float)PosX, (float)PosY - 1, D3DCOLOR_ARGB(255, 0, 0, 0), Text, pFont);

	DrawTextC((float)PosX, (float)PosY, Color, Text, pFont);
}

void hMenuCore::hDrawBox(int x, int y, int w, int h, D3DCOLOR Color, IDirect3DDevice9* pDevice)
{
	struct Vertex
	{
		float x, y, z, ht;
		DWORD Color;
	};
	Vertex V[8];

	V[0].Color = V[1].Color = V[2].Color = V[3].Color = Color;
	V[0].z = V[1].z = V[2].z = V[3].z = 0.0f;
	V[0].ht = V[1].ht = V[2].ht = V[3].ht = 0.0f;

	V[0].x = V[1].x = (float)x;
	V[0].y = V[2].y = (float)(y + h);
	V[1].y = V[3].y = (float)y;
	V[2].x = V[3].x = (float)(x + w);

	pDevice->SetTexture(0, NULL);
	pDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1);
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, V, sizeof(Vertex));
}

void hMenuCore::hDrawBox_s(IDirect3DDevice9* pDevice, int x, int y, int w, int h, DWORD Color)
{
	D3DRECT rec;
	rec.x1 = x;
	rec.x2 = x + w;
	rec.y1 = y;
	rec.y2 = y + h;
	pDevice->Clear(1, &rec, D3DCLEAR_TARGET, Color, 0, 0);
}
void hMenuCore::hDrawRectangle(int x, int y, int w, int h, int s, DWORD Color, IDirect3DDevice9* pDevice)
{
	hDrawBox_s(pDevice, x, y, w, s, Color);
	hDrawBox_s(pDevice, x, y, s, h, Color);
	hDrawBox_s(pDevice, (x + w), y, s, h, Color);
	hDrawBox_s(pDevice, x, (y + h), w + s, s, Color);
}

void hMenuCore::hDrawMouse(D3DXVECTOR2 Pos, D3DCOLOR Color, IDirect3DDevice9* pDevice)
{
	int bList[9] = { 12,10,8,6,5,4,3,2,1 };
	int cList[6] = { 8,6,4,3,2,1 };

	for (int i = 0; i < 9; i++)
		this->hDrawRectangle(Pos.x + i, Pos.y + i, 1, bList[i], 1, hBlack, pDevice);
	for (int i = 0; i < 6; i++)
		this->hDrawRectangle(Pos.x + (i + 1), Pos.y + (i + 2), 1, cList[i], 1, Color, pDevice);
	return;
}

void hMenuCore::Save(char* szSection, char* szKey, int iValue)
{
	char szValue[255];
	sprintf(szValue, "%d", iValue);
	WritePrivateProfileStringA(szSection, szKey, szValue, file);
}

int hMenuCore::Load(char* szSection, char* szKey, int iDefaultValue)
{
	int iResult = GetPrivateProfileIntA(szSection, szKey, iDefaultValue, file);
	return iResult;
}

void hMenuCore::DisableAllMenuItems()
{
	cur = 0;

	for (int i = 0; i <= (maxitems - 1); i++)
		MENU[i]->var = 0;

	noitems = 0;
}

void hMenuCore::Show(ID3DXFont* pFont, IDirect3DDevice9* pDevice)
{
	int i, val, cy;
	DWORD color;
	DWORD ColorQ;

	if (!visible)
		return;

	max_x = x + totwidth;
	max_y = y + totheight;
	cy = y;

	GetCursorPos(&mpos);
	ScreenToClient(GetForegroundWindow(), &mpos);

	if (menu_move)
	{
		x = (((x <= mpos.x + 4) && (x >= mpos.x)) || ((x >= mpos.x - 4) && (x <= mpos.x))) ? (x = mpos.x) : (x += ((mpos.x - x) / 4));
		y = (((y <= mpos.y + 4) && (y >= mpos.y)) || ((y >= mpos.y - 4) && (y <= mpos.y))) ? (y = mpos.y) : (y += ((mpos.y - y) / 4));
	}

	if (mouse_enabled)
	{
		this->hDrawMouse(D3DXVECTOR2((float)mpos.x, (float)mpos.y), hRed, pDevice);
	}

	if (title)
	{
		DrawTextShadowC((int)(x + (totwidth / 2)), (int)cy - 5, col_title, title, pFont);
		cy += titleheight;
	}

	for (i = 0; i < noitems; i++)
	{
		if (MENU[i]->typ == hText)
		{
			DrawTextShadowL(x, cy, hWhite, MENU[i]->txt, pFont);

			if (MENU[i]->opt)
			{
				DrawTextShadowR((int)(x + totwidth), (int)cy, color, (char*)MENU[i]->opt, pFont);
			}
		}
		else {
			val = (MENU[i]->var) ? (*MENU[i]->var) : 0;

			if (m_x >= x && m_x < max_x && m_y >= cy && m_y < (cy + height))
			{
				color = hOrange;
			}
			else if (i == cur)
			{
				color = col_current;
			}
			else if (MENU[i]->typ == hFolder)
			{
				color = col_group;
			}
			else if (MENU[i]->typ == hSubFd)
			{
				color = (val) ? col_on : col_off;
			}
			else
			{
				color = (val) ? col_on : col_off;
			}

			if (val > 0)
			{
				ColorQ = hGreen;
			}
			else {
				ColorQ = hRed;
			}

			if (MENU[i]->typ == hItem)
			{
				DrawTextShadowL((int)x + 13, (int)cy, color, MENU[i]->txt, pFont);
			}
			else {
				if (val > 0)
				{
					this->hDrawBox((int)x - 6, (int)cy + 2, (int)totwidth - 1, (float)12, hGrey2, pDevice);
				}
				DrawTextShadowL((int)x, (int)cy, color, MENU[i]->txt, pFont);
			}

			if (MENU[i]->opt)
			{
				if (MENU[i]->typ == hItem)
				{
					hDrawRectangle((int)x + 2, (int)cy + 4, (int)6, (float)6, 1, hBlack, pDevice);
					hDrawBox((int)x + 3, (int)cy + 5, (int)5, (float)5, ColorQ, pDevice);
					DrawTextShadowR((int)((x + totwidth) - 15), (int)cy, ColorQ, (char*)MENU[i]->opt[val], pFont);
				}
				else {
					DrawTextShadowR((int)(x + totwidth) - 15, (int)cy, color, (char*)MENU[i]->opt[val], pFont);
				}
			}

		}
		cy += height;
	}
}

int hMenuCore::FindItem(void)
{
	if (m_x <= x || m_x >= max_x || m_y <= y || m_y >= max_y) return -1;
	if ((m_y - y) > titleheight) {
		int row = (m_y - y - titleheight) / height;
		if (MENU[row]->typ == hText || MENU[row]->var == 0) return -1;
		return row;
	}
	return 999;
}

void hMenuCore::CheckTitleMove(int rm, int mx, int my)
{
	m_x = mx;
	m_y = my;
	if (rm && FindItem() == 999)
	{
		moving = (!moving);
		dx = m_x - x;
		dy = m_y - y;
	}
	else if (moving && FindItem() != 999)
		moving = 0;
}

void hMenuCore::Nav(void)
{
	if (GetAsyncKeyState(VK_INSERT) & 1) visible = (!visible);

	if (!visible)
		return;

	if (GetAsyncKeyState(VK_CONTROL)) {
		if (GetAsyncKeyState(VK_UP) & 1)
			if (GetAsyncKeyState(VK_DOWN) & 1)
				if (GetAsyncKeyState(VK_LEFT) & 1)
					if (GetAsyncKeyState(VK_RIGHT) & 1);
	}
	else {
		if (GetAsyncKeyState(VK_UP) & 1) {
			do {
				cur--;
				if (cur < 0)  cur = noitems - 1;
			} while (MENU[cur]->typ == hText);
		}
		else if (GetAsyncKeyState(VK_DOWN) & 1) {
			do {
				cur++;
				if (cur == noitems) cur = 0;
			} while (MENU[cur]->typ == hText);
		}
		else {
			int pos = cur;
			int dir = 0;

			if (GetAsyncKeyState(VK_LEFT) & 1 && MENU[cur]->var && *MENU[cur]->var > 0) dir = -1;
			if (GetAsyncKeyState(VK_RIGHT) & 1 && MENU[cur]->var && *MENU[cur]->var < (MENU[cur]->maxval - 1)) dir = 1;

			if (dir == 0 && (mouse_enabled == true))
			{
				GetCursorPos(&mpos);
				ScreenToClient(GetForegroundWindow(), &mpos);
				m_x = mpos.x;
				m_y = mpos.y;
				m_lm = GetAsyncKeyState(VK_LBUTTON) & 1;
				m_rm = GetAsyncKeyState(VK_RBUTTON) & 1;

				if ((m_lm || m_rm) && (pos = FindItem()) != -1)
				{
					if (pos != 999) {
						if (m_rm && *MENU[pos]->var > 0) dir = -1;
						if (m_lm && *MENU[pos]->var < (MENU[pos]->maxval - 1)) dir = 1;
					}
					else if (m_rm) {
						moving = (!moving);
						dx = m_x - x;
						dy = m_y - y;
					}
				}
			}
			if (dir) {
				*MENU[pos]->var += dir;
				if (MENU[pos]->typ == hFolder) noitems = 0;
				if (MENU[pos]->typ == hSubFd) noitems = 0;
			}
		}
	}
}