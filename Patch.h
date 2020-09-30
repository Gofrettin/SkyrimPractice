#pragma once

#ifndef PATCH_H
#define PATCH_H

#include <Windows.h>

class Patch {
private:
	uintptr_t Target;
	uintptr_t Length;
	bool Active;
	BYTE* oldBytes;
	BYTE* newBytes;
	DWORD oldprotect;

public:
	Patch();
	~Patch();
	void CreatePatch(uintptr_t Target, BYTE* newBytes, bool Active);
	bool Activate();
	bool Deactivate();
	bool Remove();
};
#endif