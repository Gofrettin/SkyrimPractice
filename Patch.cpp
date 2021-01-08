#include "Patch.h"

Patch::Patch() {
	this->Target = 0;
	this->Length = 0;
	this->Active = false;
	this->oldBytes = nullptr;
	this->newBytes = nullptr;
	this->oldprotect = 0;
}

Patch::~Patch() {
	this->Remove();
}

void Patch::CreatePatch(uintptr_t Target, BYTE* newBytes, bool Active) {
	this->Target = Target;
	this->newBytes = newBytes;
	this->Length = sizeof(newBytes);
	this->oldBytes = new byte[this->Length];
	if (Active)
		this->Activate();
}

bool Patch::Activate() {
	if (!this->Target || !this->oldBytes || !this->newBytes || !this->Length)
		return false;
	if (!this->Active) {
		VirtualProtect((void*)this->Target, this->Length, PAGE_EXECUTE_READWRITE, &oldprotect);
		memcpy(this->oldBytes, (void*)this->Target, this->Length);
		memcpy((void*)this->Target, this->newBytes, this->Length);
		VirtualProtect((void*)this->Target, this->Length, oldprotect, &oldprotect);
		this->Active = true;
	}
	return this->Active;
}

bool Patch::Deactivate() {
	if (!this->Target || !this->oldBytes || !this->newBytes || !this->Length)
		return false;
	if (this->Active) {
		VirtualProtect((void*)this->Target, this->Length, PAGE_EXECUTE_READWRITE, &oldprotect);
		memcpy((void*)this->Target, this->oldBytes, this->Length);
		VirtualProtect((void*)this->Target, this->Length, oldprotect, &oldprotect);
		this->Active = false;
	}
	return !this->Active;

}

bool Patch::Remove() {
	if (this->Deactivate()) {
		this->Target = 0;
		this->Length = 0;
		this->Active = false;
		delete[] this->oldBytes;
		this->oldBytes = nullptr;
		this->newBytes = nullptr;
		this->oldprotect = 0;
	}
	return !this->Active;
}
