#pragma once
#include "Utils.h"
#include "Detour.h"
#include "Patch.h"
#include "Vector.h"
#include "Reclass.h"
#include <numbers>

#define M_PI		3.14159265358979323846264338327950288
#define M_RADPI		57.295779513082f
#define RAD2DEG(x)  ((float)(x)*(float)(180.f/M_PI))
#define DEG2RAD(x)  ((float)(x)*(float)(M_PI/180.f))
#define BOUND_VALUE (var,min,max) if((var)>(max)){(var)=(max);};if((var)<(min)){(var)=(min);}

//Menu
hMenuCore* hMenu;
IDirect3DDevice9* hDevice;
ID3DXFont* pFont;

//Menu Items & Chars
int hMenuItem[50];
int hMenuFolder[40];
int hMenuSettings[10];

//Menu Options
const char* hOpt[] = { "[Off]", "[On]" };
const char* hFld[] = { "[+]", "[-]" };

//Others
extern bool mouse_enabled;
extern bool menu_move;
extern bool menu_exit;

//Memory Patches
Patch DupePatch;

//Menu Settings
void hSettings() {
	if (hMenuSettings[2]) {
		mouse_enabled = true;
	}
	else {
		mouse_enabled = false;
	}
	if (hMenuSettings[3]) {
		menu_move = true;
	}
	else {
		menu_move = false;
	}
	if (hMenuSettings[4]) {
		hMenu->DisableAllMenuItems();
		for (int i = 0; i <= (ARRAYSIZE(hMenuItem) - 1); i++)
			hMenuItem[i] = 0;
		for (int i = 0; i <= (ARRAYSIZE(hMenuFolder) - 1); i++)
			hMenuFolder[i] = 0;
		for (int i = 0; i <= (ARRAYSIZE(hMenuSettings) - 1); i++)
			hMenuSettings[i] = 0;
	}
	if (hMenuSettings[5]) {
		menu_exit = true;
	}
}

bool WorldToScreen(Vector3 pos, Vector2& screen, float matrix[16], int windowWidth, int windowHeight) {
	//Matrix-vector Product, multiplying world(eye) coordinates by projection matrix = clipCoords
	Vector4 clipCoords(
		pos[0] * matrix[0] + pos[1] * matrix[1] + pos[2] * matrix[2] + matrix[3],//x
		pos[0] * matrix[4] + pos[1] * matrix[5] + pos[2] * matrix[6] + matrix[7],//y
		pos[0] * matrix[8] + pos[1] * matrix[9] + pos[2] * matrix[10] + matrix[11],//z
		pos[0] * matrix[12] + pos[1] * matrix[13] + pos[2] * matrix[14] + matrix[15]//w
	);
	if (clipCoords[3] < 0.1f)
		return false;
	//perspective division, dividing by clip.W = Normalized Device Coordinates
	Vector3 NDC(
		clipCoords[0] / clipCoords[3],//x
		clipCoords[1] / clipCoords[3],//y
		clipCoords[2] / clipCoords[3] //z
	);
	screen[0] = (windowWidth / 2 * NDC[0]) + (NDC[0] + windowWidth / 2);//x
	screen[1] = -(windowHeight / 2 * NDC[1]) + (NDC[1] + windowHeight / 2);//y
	return true;
}

D3DXCOLOR Rainbow(float alpha) {
	static uint32_t cnt = 0;
	float freq = .0005f;
	D3DXCOLOR color = D3DXCOLOR(
		(std::sin(freq * cnt + 0) * 127.f + 128.f) / 255.f,//R
		(std::sin(freq * cnt + 2) * 127.f + 128.f) / 255.f,//G
		(std::sin(freq * cnt + 4) * 127.f + 128.f) / 255.f,//B
		alpha);
	if (cnt++ >= (uint32_t)-1) cnt = 0;
	return color;
}

Vector2 RotatePoint(Vector2 pointToRotate, Vector2 centerPoint, float angle, bool angleInRadians = true) {
	if (!angleInRadians)
		angle = DEG2RAD(angle);
	float cosTheta = (float)cos(angle);
	float sinTheta = (float)sin(angle);
	Vector2 returnVec(
		-(cosTheta * (pointToRotate.at(0) - centerPoint.at(0)) + sinTheta * (pointToRotate.at(1) - centerPoint.at(1))),
		-(sinTheta * (pointToRotate.at(0) - centerPoint.at(0)) - cosTheta * (pointToRotate.at(1) - centerPoint.at(1)))
	);
	returnVec += centerPoint;
	return returnVec;
}

Vector2 ScaleToRadar(playerent* entity, playerent* localPlayer, Vector2 localPlayerViewAngles, int radarx, int radary, int radarw, int radarh, float radarDistance) {
	Vector2 radarCentre((radarx + radarw / 2) - 2, (radary + radarh / 2) - 2);
	Vector2 enemyPos2D(entity->coords[0], entity->coords[1]);
	Vector2 localPos2D(localPlayer->coords[0], localPlayer->coords[1]);
	Vector2 screenPos = localPos2D - enemyPos2D;
	float distance = screenPos.get_length() * (0.02f * radarDistance);//Distance
	// distance = min(distance, m_x); circle radar
	Vector2 screen = screenPos.normalized();
	screen *= distance;
	screen += radarCentre;
	return RotatePoint(screen, radarCentre, -1 * localPlayerViewAngles.at(1), false);
}

int FrameRate() {
	static int iFps, iLastFps;
	static float flLastTickCount, flTickCount;
	flTickCount = clock() * 0.001f;
	iFps++;
	if ((flTickCount - flLastTickCount) >= 1.0f) {
		flLastTickCount = flTickCount;
		iLastFps = iFps;
		iFps = 0;
	}
	return iLastFps;
}

int GetHeightInPixels() {
	TEXTMETRICA txtmet;
	pFont->GetTextMetrics(&txtmet);
	return  txtmet.tmHeight;
}

int GetLengthInPixels(LPCSTR TextToDraw) {
	TEXTMETRICA txtmet;
	pFont->GetTextMetrics(&txtmet);
	int size = 0;
	for (int i = 0; TextToDraw[i] != '\0'; i++) {
		size++;
	}
	//return size * (txtmet.tmAveCharWidth + 1);
	return size * (txtmet.tmAveCharWidth - 1);
}

//Cheats
void hBuildHacks(IDirect3DDevice9* pDevice) {
	D3DVIEWPORT9 viewPort;
	pDevice->GetViewport(&viewPort);
	if (hMenuItem[1]) {
		float ScreenCenterX = viewPort.Width / 2 - 1;
		float ScreenCenterY = viewPort.Height / 2 - 1;

		hMenu->hDrawRectangle(ScreenCenterX - 15, ScreenCenterY - 1, 11, 2, 1, D3DXCOLOR(0.0, 0.0, 0.0, 1.0), pDevice);//Left line Border
		hMenu->hDrawBox(ScreenCenterX - 14, ScreenCenterY, 10, 1, D3DXCOLOR(1.0, 0.0, 0.0, 1.0), pDevice);//Left line

		hMenu->hDrawRectangle(ScreenCenterX + 4, ScreenCenterY - 1, 11, 2, 1, D3DXCOLOR(0.0, 0.0, 0.0, 1.0), pDevice);//Right line Border
		hMenu->hDrawBox(ScreenCenterX + 5, ScreenCenterY, 10, 1, D3DXCOLOR(1.0, 0.0, 0.0, 1.0), pDevice);//Right line

		hMenu->hDrawRectangle(ScreenCenterX - 1, ScreenCenterY - 15, 2, 11, 1, D3DXCOLOR(0.0, 0.0, 0.0, 1.0), pDevice);//Top line Border
		hMenu->hDrawBox(ScreenCenterX, ScreenCenterY - 14, 1, 10, D3DXCOLOR(1.0, 0.0, 0.0, 1.0), pDevice);//Top line

		hMenu->hDrawRectangle(ScreenCenterX - 1, ScreenCenterY + 4, 2, 11, 1, D3DXCOLOR(0.0, 0.0, 0.0, 1.0), pDevice);//Bottom line Border
		hMenu->hDrawBox(ScreenCenterX, ScreenCenterY + 5, 1, 10, D3DXCOLOR(1.0, 0.0, 0.0, 1.0), pDevice);//Bottom line

		hMenu->hDrawRectangle(ScreenCenterX - 1, ScreenCenterY - 1, 2, 2, 1, D3DXCOLOR(0.0, 0.0, 0.0, 1.0), pDevice);//Point Border
		hMenu->hDrawBox(ScreenCenterX, ScreenCenterY, 1, 1, D3DXCOLOR(1.0, 0.0, 0.0, 1.0), pDevice);//Point
	}
	if (hMenuItem[2]) {		//On
		if (esp_firsttime) {
			for (int i = 0; i < 254; i++) {
				ents[i] = 0;
			}
		}
		if (*(DWORD*)LoadingScreen == 1) {
			for (int i = 0; i < 254; i++) {
				ents[i] = 0;
			}
			*(DWORD*)LoadingScreen = 0;
		}
		memcpy(&Matrix, (PBYTE*)ViewMatrix, sizeof(Matrix));
		for (int i = 0; i < 254; i++) {
			if (ents[i] != 0) {
				if (ents[i] != 0) {
					if ((ents[i]->ValidCheck1 == 0) || (ents[i]->ValidCheck2 == 0) || (ents[i]->ValidCheck3 == 0) || (ents[i]->ValidCheck4 == 0) || (ents[i]->nameptr == 0)) {
						ents[i] = 0;
						break;
					}
				}
				Vector2 vScreen;
				if (WorldToScreen(ents[i]->coords, vScreen, Matrix, viewPort.Width, viewPort.Height)) {
					if (ents[i] != 0) {
						std::string espString = std::string(ents[i]->nameptr->name) + "[" + std::to_string((int)(LocalPlayer->coords.get_distance((ents[i]->coords)) / 100)) + "m]";
						hMenu->DrawTextShadow((CHAR*)espString.c_str(), vScreen[0] - (GetLengthInPixels(espString.c_str()) / 2), vScreen[1], Rainbow(255), pFont);
					}
				}
			}
		}
		esp_firsttime = false;
	}
	else {		//Off
		if (!esp_firsttime)
			esp_firsttime = true;
	}

	if (hMenuItem[3]) {		//On
		Vector4 radarDimensions;// 0->x, 1->y, 2->width, 3->height
		int titleBarOffset = 12;
		if (hMenu->visible) {
			radarDimensions[0] = hMenu->x - 5 + hMenu->totwidth;
			radarDimensions[1] = hMenu->y + 5;
			radarDimensions[2] = 157;
			radarDimensions[3] = 157;
		}
		else {
			radarDimensions[0] = hMenu->x - 7;
			radarDimensions[1] = hMenu->y + 5;
			radarDimensions[2] = 157;
			radarDimensions[3] = 157;
		}
		hMenu->hDrawBox(radarDimensions[0] + 2, radarDimensions[1] - (2 + titleBarOffset), radarDimensions[2] - 4, 1 + titleBarOffset, hTransparent, pDevice);//Title Box
		hMenu->hDrawRectangle(radarDimensions[0] + 1, radarDimensions[1] - (3 + titleBarOffset), radarDimensions[2] - 2, 2 + titleBarOffset, 1, hWhite, pDevice);//White Border
		//hMenu->DrawTextShadow((CHAR*)("Radar - Player: " + AddrToHexString(LocalPlayerPtr)).c_str(), radarDimensions[0] + 2, radarDimensions[1] - (3 + titleBarOffset), D3DCOLOR_RGBA(255, 255, 255, 255), pFont);//Old Title Text
		std::string frameRate = "Radar-FrameRate:" + std::to_string(FrameRate());
		hMenu->DrawTextShadow((CHAR*)(frameRate.c_str()), radarDimensions[0] + 2, radarDimensions[1] - (3 + titleBarOffset), D3DCOLOR_RGBA(255, 255, 255, 255), pFont);//Title Text
		hMenu->hDrawBox(radarDimensions[0] + 1, radarDimensions[1] + 1, radarDimensions[2] - 1, radarDimensions[3] - 1, hTransparent, pDevice);//Radar Body Box
		hMenu->hDrawRectangle(radarDimensions[0] + 1, radarDimensions[1] + 1, radarDimensions[2] - 2, radarDimensions[3] - 2, 1, hWhite, pDevice);//Radar Border Box
		hMenu->hDrawRectangle(radarDimensions[0] + 1, radarDimensions[1] + 1 + (radarDimensions[3] / 2), radarDimensions[2] - 2, 0, 1, hWhite, pDevice);//x Axis
		hMenu->hDrawRectangle(radarDimensions[0] + 1 + (radarDimensions[2] / 2), radarDimensions[1] + 1, 0, radarDimensions[3] - 2, 1, hWhite, pDevice);//y Axis
		if (radar_firsttime) {
			for (int i = 0; i < 254; i++) {
				ents[i] = 0;
			}
		}
		if (*(DWORD*)LoadingScreen == 1) {
			for (int i = 0; i < 254; i++) {
				ents[i] = 0;
			}
			*(DWORD*)LoadingScreen = 0;
		}
		for (int i = 0; i < 254; i++) {
			if (ents[i] != 0) {
				if (ents[i] != 0) {
					if ((ents[i]->ValidCheck1 == 0) || (ents[i]->ValidCheck2 == 0) || (ents[i]->ValidCheck3 == 0) || (ents[i]->ValidCheck4 == 0) || (ents[i]->nameptr == 0)) {
						ents[i] = 0;
						break;
					}
				}
				if (ents[i]->nameptr->name != LocalPlayer->nameptr->name) {
					Vector2 viewAngles(RAD2DEG(*(float*)(LocalPlayerPtr + 0x28)), RAD2DEG(*(float*)(LocalPlayerPtr + 0x30)));
					Vector2 screenPos = ScaleToRadar(ents[i], LocalPlayer, viewAngles, radarDimensions[0], radarDimensions[1], radarDimensions[2], radarDimensions[3], 1.0f);
					if (screenPos[0] > radarDimensions[0] && screenPos[0] < (radarDimensions[0] + radarDimensions[2] - 5) && screenPos[1] > radarDimensions[1] && screenPos[1] < radarDimensions[1] + radarDimensions[3] - 5)
						hMenu->hDrawBox(screenPos[0] + 3, screenPos[1] + 3, 2, 2, hRed, pDevice);
				}
			}
		}
		radar_firsttime = false;

	}
	else {		//Off
		if (!radar_firsttime) {
			radar_firsttime = true;
		}
	}
	if (hMenuItem[4]) {		//On
		DupePatch.Activate();
	}
	else {		//Off
		DupePatch.Deactivate();
	}
	if (hMenuItem[5]) {		//On
		if (!godModeActive)
		{
			*(int*)GodMode = 256;
			godModeActive = true;
		}
	}
	else {		//Off
		if (godModeActive) {
			*(int*)GodMode = 0;
			godModeActive = false;
		}
	}
	if (hMenuItem[6]) {		//On
		if (!noGravityModeActive) {
			*(float*)Gravity = 0.0f;
			noGravityModeActive = true;
		}
	}
	else {		//Off
		if (noGravityModeActive) {
			*(float*)Gravity = 1.350000024f;
			noGravityModeActive = false;
		}
	}
	if (hMenuItem[7]) {		//On
		Vector3 relPos(0.0f, 0.0f, 0.0f);
		if (GetAsyncKeyState(VK_NUMPAD8))//FORWARDS
		{
			relPos[0] += 2.0f;
		}
		if (GetAsyncKeyState(VK_NUMPAD2))//BACKWARDS
		{
			relPos[0] -= 2.0f;
		}
		if (GetAsyncKeyState(VK_NUMPAD6))//RIGHT
		{
			relPos[1] += 2.0f;
		}
		if (GetAsyncKeyState(VK_NUMPAD4))//LEFT
		{
			relPos[1] -= 2.0f;
		}
		if (GetAsyncKeyState(VK_NUMPAD5))//UP
		{
			relPos[2] += 2.0f;
		}
		if (GetAsyncKeyState(VK_NUMPAD0))//DOWN
		{
			relPos[2] -= 2.0f;
		}
		Vector3 newPos(
			(*(float*)(ViewMatrix)) * relPos[1] + (*(float*)(ViewMatrix + 0x10)) * relPos[2] + (*(float*)(ViewMatrix + 0x20)) * relPos[0],
			(*(float*)(ViewMatrix + 0x4)) * relPos[1] + (*(float*)(ViewMatrix + 0x14)) * relPos[2] + (*(float*)(ViewMatrix + 0x24)) * relPos[0],
			(*(float*)(ViewMatrix + 0x8)) * relPos[1] + (*(float*)(ViewMatrix + 0x18)) * relPos[2] + (*(float*)(ViewMatrix + 0x28)) * relPos[0]
		);
		Axis = zAxisptr + 0xE0;
		*(Vector3*)Axis += newPos;
		Sleep(1);
	}
	else {		//Off
	}
	if (hMenuItem[8]) {		//On
		if (GetAsyncKeyState(VK_NUMPAD1)) {
			Axis = zAxisptr + 0xE0;
			Vector3 WP = *(Vector3*)0x01B40298;//WaypointPtr
			WP /= 70;
			if (WP != lastTpPos) {
				*(Vector3*)Axis = WP;
				lastTpPos = WP;
			}
		}
	}
	else {		//Of
	}
}