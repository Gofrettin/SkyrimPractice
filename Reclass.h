#pragma once

std::string PROCESS_NAME = "TESV.exe";
MODULEINFO modInfo;

bool esp_firsttime = true;
bool radar_firsttime = true;
bool alreadyThere = false;
bool godModeActive = false;
bool noGravityModeActive = false;

int ix;

DWORD LocalPlayerPtr;
DWORD ViewMatrix;
DWORD Waypoint;
DWORD GodMode;
DWORD Gravity;
DWORD EntityObjStart;
DWORD EntlistJmpBack;
DWORD LoadingScreen;
DWORD noclipJmpBack;
DWORD Axis;
DWORD zAxisptr;
Vector3 lastTpPos;

float Matrix[16];

// Generated using ReClass 2016

class playerent;
class nameptrClass;
class boneptr1Class;
class boneptr2Class;
class boneptr3Class;
class boneptr3Class;
class boneptr3Class;
class HealthPtr1Class;
class HealthPtr2Class;
class HealthPtr3Class;

class playerent
{
public:
	char pad_0x0000[0x24]; //0x0000
	nameptrClass* nameptr; //0x0024 
	char pad_0x0028[0xC]; //0x0028
	Vector3 coords; //0x0034 
	DWORD ValidCheck1; //0x0040 
	DWORD ValidCheck2; //0x0044 
	DWORD ValidCheck3; //0x0048 
	DWORD ValidCheck4; //0x004C 
	char pad_0x0050[0x38]; //0x0050
	HealthPtr1Class* HealthPtr1; //0x0088 
	char pad_0x008C[0xFC]; //0x008C
	boneptr1Class* boneptr1; //0x0188 
	char pad_0x018C[0x2B4]; //0x018C

}; //Size=0x0440


class HealthPtr1Class
{
public:
	char pad_0x0000[0x30]; //0x0000
	HealthPtr2Class* HealthPtr2; //0x0030 

}; //Size=0x0034

class HealthPtr2Class
{
public:
	char pad_0x0000[0x30]; //0x0000
	HealthPtr3Class* HealthPtr3; //0x0030 

}; //Size=0x0034

class HealthPtr3Class
{
public:
	char pad_0x0000[0x1C]; //0x0000
	float Health; //0x001C 

}; //Size=0x0020

class nameptrClass
{
public:
	char pad_0x0000[0x88]; //0x0000
	char* name; //0x0088 
	char pad_0x008C[0x378]; //0x008C

}; //Size=0x0404

class boneptr1Class
{
public:
	char pad_0x0000[0x4]; //0x0000
	boneptr2Class* boneptr2; //0x0004 

}; //Size=0x0008

class boneptr2Class
{
public:
	char pad_0x0000[0xC0]; //0x0000
	boneptr3Class* boneptr3; //0x00C0 

}; //Size=0x00C4

class boneptr3Class
{
public:
	char pad_0x0000[0x74]; //0x0000
	char* humanoidvalidation; //0x0074 
	char pad_0x0078[0x58]; //0x0078
	Vector3 Pelv; //0x00D0 
	char pad_0x00DC[0x6C]; //0x00DC
	Vector3 LThg; //0x0148 
	char pad_0x0154[0x6C]; //0x0154
	Vector3 LClf; //0x01C0 
	char pad_0x01CC[0x6C]; //0x01CC
	Vector3 LFoot; //0x0238 
	char pad_0x0244[0x6C]; //0x0244
	Vector3 LToe0; //0x02B0 
	char pad_0x02BC[0x6C]; //0x02BC
	Vector3 RThg; //0x0328 
	char pad_0x0334[0x6C]; //0x0334
	Vector3 RClf; //0x03A0 
	char pad_0x03AC[0x6C]; //0x03AC
	Vector3 RFoot; //0x0418 
	char pad_0x0424[0x6C]; //0x0424
	Vector3 RToe0; //0x0490 
	char pad_0x049C[0x6C]; //0x049C
	Vector3 WeapDagger; //0x0508 
	char pad_0x0514[0x6C]; //0x0514
	Vector3 WeapAxe; //0x0580 
	char pad_0x058C[0x6C]; //0x058C
	Vector3 WeapSword; //0x05F8 
	char pad_0x0604[0x6C]; //0x0604
	Vector3 WeapMace; //0x0670 
	char pad_0x067C[0x6C]; //0x067C
	Vector3 SkirtFBone1; //0x06E8 
	char pad_0x06F4[0x6C]; //0x06F4
	Vector3 SkirtFBone2; //0x0760 
	char pad_0x076C[0x6C]; //0x076C
	Vector3 SkirtFBone3; //0x07D8 
	char pad_0x07E4[0x6C]; //0x07E4
	Vector3 SkirtBBone1; //0x0850 
	char pad_0x085C[0x6C]; //0x085C
	Vector3 SkirtBBone2; //0x08C8 
	char pad_0x08D4[0x6C]; //0x08D4
	Vector3 SkirtBBone3; //0x0940 
	char pad_0x094C[0x6C]; //0x094C
	Vector3 SkirtLBone1; //0x09B8 
	char pad_0x09C4[0x6C]; //0x09C4
	Vector3 SkirtLBone2; //0x0A30 
	char pad_0x0A3C[0x6C]; //0x0A3C
	Vector3 SkirtLBone3; //0x0AA8 
	char pad_0x0AB4[0x6C]; //0x0AB4
	Vector3 SkirtRBone1; //0x0B20 
	char pad_0x0B2C[0x6C]; //0x0B2C
	Vector3 SkirtRBone2; //0x0B98 
	char pad_0x0BA4[0x6C]; //0x0BA4
	Vector3 SkirtRBone3; //0x0C10 
	char pad_0x0C1C[0x6C]; //0x0C1C
	Vector3 Spn0; //0x0C88 
	char pad_0x0C94[0x6C]; //0x0C94
	Vector3 Spn1; //0x0D00 
	char pad_0x0D0C[0x6C]; //0x0D0C
	Vector3 Spn2; //0x0D78 
	char pad_0x0D84[0x6C]; //0x0D84
	Vector3 Neck; //0x0DF0 
	char pad_0x0DFC[0x6C]; //0x0DFC
	Vector3 Head; //0x0E68 
	char pad_0x0E74[0x6C]; //0x0E74
	Vector3 HMagNode; //0x0EE0 
	char pad_0x0EEC[0x6C]; //0x0EEC
	Vector3 EyeBone; //0x0F58 
	char pad_0x0F64[0x6C]; //0x0F64
	Vector3 RClv; //0x0FD0 
	char pad_0x0FDC[0x6C]; //0x0FDC
	Vector3 RUarm; //0x1048 
	char pad_0x1054[0x6C]; //0x1054
	Vector3 RFarm; //0x10C0 
	char pad_0x10CC[0x6C]; //0x10CC
	Vector3 RHnd; //0x1138 
	char pad_0x1144[0x6C]; //0x1144
	Vector3 RFinger0; //0x11B0 
	char pad_0x11BC[0x6C]; //0x11BC
	Vector3 RFinger1; //0x1228 
	char pad_0x1234[0x6C]; //0x1234
	Vector3 RFinger2; //0x12A0 
	char pad_0x12AC[0x6C]; //0x12AC
	Vector3 RFinger10; //0x1318 
	char pad_0x1324[0x6C]; //0x1324
	Vector3 RFinger11; //0x1390 
	char pad_0x139C[0x6C]; //0x139C
	Vector3 RFinger12; //0x1408 
	char pad_0x1414[0x6C]; //0x1414
	Vector3 RFinger20; //0x1480 
	char pad_0x148C[0x6C]; //0x148C
	Vector3 RFinger21; //0x14F8 
	char pad_0x1504[0x6C]; //0x1504
	Vector3 RFinger22; //0x1570 
	char pad_0x157C[0x6C]; //0x157C
	Vector3 RFinger30; //0x15E8 
	char pad_0x15F4[0x6C]; //0x15F4
	Vector3 RFinger31; //0x1660 
	char pad_0x166C[0x6C]; //0x166C
	Vector3 RFinger32; //0x16D8 
	char pad_0x16E4[0x6C]; //0x16E4
	Vector3 RFinger40; //0x1750 
	char pad_0x175C[0x6C]; //0x175C
	Vector3 RFinger41; //0x17C8 
	char pad_0x17D4[0x6C]; //0x17D4
	Vector3 RFinger42; //0x1840 
	char pad_0x184C[0x6C]; //0x184C
	Vector3 RMagNode; //0x18B8 
	char pad_0x18C4[0x6C]; //0x18C4
	Vector3 Weapon; //0x1930 
	char pad_0x193C[0x6C]; //0x193C
	Vector3 AnimObjectR; //0x19A8 
	char pad_0x19B4[0x6C]; //0x19B4
	Vector3 RFarmTwist1; //0x1A20 
	char pad_0x1A2C[0x6C]; //0x1A2C
	Vector3 RFarmTwist2; //0x1A98 
	char pad_0x1AA4[0x6C]; //0x1AA4
	Vector3 RUarmTwist1; //0x1B10 
	char pad_0x1B1C[0x6C]; //0x1B1C
	Vector3 RUarmTwist2; //0x1B88 
	char pad_0x1B94[0x6C]; //0x1B94
	Vector3 Rpauldron; //0x1C00 
	char pad_0x1C0C[0x6C]; //0x1C0C
	Vector3 LClv; //0x1C78 
	char pad_0x1C84[0x6C]; //0x1C84
	Vector3 LUarm; //0x1CF0 
	char pad_0x1CFC[0x6C]; //0x1CFC
	Vector3 LFarm; //0x1D68 
	char pad_0x1D74[0x6C]; //0x1D74
	Vector3 LHnd; //0x1DE0 
	char pad_0x1DEC[0x6C]; //0x1DEC
	Vector3 LFinger0; //0x1E58 
	char pad_0x1E64[0x6C]; //0x1E64
	Vector3 LFinger1; //0x1ED0 
	char pad_0x1EDC[0x6C]; //0x1EDC
	Vector3 LFinger2; //0x1F48 
	char pad_0x1F54[0x6C]; //0x1F54
	Vector3 LFinger10; //0x1FC0 
	char pad_0x1FCC[0x6C]; //0x1FCC
	Vector3 LFinger11; //0x2038 
	char pad_0x2044[0x6C]; //0x2044
	Vector3 LFinger12; //0x20B0 
	char pad_0x20BC[0x6C]; //0x20BC
	Vector3 LFinger20; //0x2128 
	char pad_0x2134[0x6C]; //0x2134
	Vector3 LFinger21; //0x21A0 
	char pad_0x21AC[0x6C]; //0x21AC
	Vector3 LFinger22; //0x2218 
	char pad_0x2224[0x6C]; //0x2224
	Vector3 LFinger30; //0x2290 
	char pad_0x229C[0x6C]; //0x229C
	Vector3 LFinger31; //0x2308 
	char pad_0x2314[0x6C]; //0x2314
	Vector3 LFinger32; //0x2380 
	char pad_0x238C[0x6C]; //0x238C
	Vector3 LFinger40; //0x23F8 
	char pad_0x2404[0x6C]; //0x2404
	Vector3 LFinger41; //0x2470 
	char pad_0x247C[0x6C]; //0x247C
	Vector3 LFinger42; //0x24E8 
	char pad_0x24F4[0x6C]; //0x24F4
	Vector3 LMagNode; //0x2560 
	char pad_0x256C[0x6C]; //0x256C
	Vector3 bShield; //0x25D8 
	char pad_0x25E4[0x6C]; //0x25E4
	Vector3 AnimObjectL; //0x2650 
	char pad_0x265C[0x6C]; //0x265C
	Vector3 LFarmTwist1; //0x26C8 
	char pad_0x26D4[0x6C]; //0x26D4
	Vector3 LFarmTwist2; //0x2740 
	char pad_0x274C[0x6C]; //0x274C
	Vector3 LUarmTwist1; //0x27B8 
	char pad_0x27C4[0x6C]; //0x27C4
	Vector3 LUarmTwist2; //0x2830 
	char pad_0x283C[0x6C]; //0x283C
	Vector3 LPauldron; //0x28A8 
	char pad_0x28B4[0x6C]; //0x28B4
	Vector3 WeapBack; //0x2920 
	char pad_0x292C[0x6C]; //0x292C
	Vector3 WeapBow; //0x2998 
	char pad_0x29A4[0x6C]; //0x29A4
	Vector3 WeapQuiver; //0x2A10 
	char pad_0x2A1C[0x6C]; //0x2A1C
	Vector3 MagicEffectsNode; //0x2A88 
	char pad_0x2A94[0x6C]; //0x2A94
	Vector3 CameraControl; //0x2B00 
	char pad_0x2B0C[0x6C]; //0x2B0C
	Vector3 AnimObjectA; //0x2B78 
	char pad_0x2B84[0x6C]; //0x2B84
	Vector3 AnimObjectB; //0x2BF0 
	char pad_0x2BFC[0x3FC]; //0x2BFC

}; //Size=0x2FF8

playerent* ents[255];
playerent* entsptr;
playerent* LocalPlayer;

__declspec(naked) void nocliphook()
{
	__asm {
		mov zAxisptr, esi
		mov edx, [edx + 0x78]
		fld dword ptr[edx + 0x0C]
		pushad
	}

	__asm {
		popad
		jmp[noclipJmpBack]
	}
}

__declspec(naked) void entityhook()
{
	__asm {
		mov edx, [esi + 0x34]
		mov eax, [esi + 0x38]
		mov EntityObjStart, esi
		pushad
	}

	__asm {
		mov eax, EntityObjStart
		mov[entsptr], eax
	}

	if (entsptr == nullptr)
	{
		goto GIVE_UP;
	}

	alreadyThere = false;

	for (ix = 0; ix < 254; ix++)
	{
		if (ents[ix] == entsptr)
		{
			alreadyThere = true;
			break;
		}
	}

	if (alreadyThere)
	{
		goto GIVE_UP;
	}
	else
	{
		for (ix = 0; ix < 254; ix++)
		{
			if (ents[ix] == 0)
			{
				ents[ix] = entsptr;
				break;
			}
		}
	}

GIVE_UP:
	__asm {
		popad
		jmp[EntlistJmpBack]
	}
}