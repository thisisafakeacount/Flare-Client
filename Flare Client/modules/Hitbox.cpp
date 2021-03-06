#include "Hitbox.h"
#include "../LittleHacker.h"

Hitbox::Hitbox(HANDLE hProcess, std::vector<uintptr_t> EntityList, float widthValue, float heightValue) {
	for (int entity = 0; entity < EntityList.size(); entity++) {
		uintptr_t EntityWidthAddr = mem::FindAddr(hProcess, EntityList[entity], { Player::hitboxWidth });
		uintptr_t EntityHeightAddr = mem::FindAddr(hProcess, EntityList[entity], { Player::hitboxHeight });
		WriteProcessMemory(hProcess, (BYTE*)EntityWidthAddr, &widthValue, sizeof(widthValue), 0);
		WriteProcessMemory(hProcess, (BYTE*)EntityHeightAddr, &heightValue, sizeof(heightValue), 0);
	}
}