#include "LocalPlayer.h"

/* Pointers */

uintptr_t Player::LocalPlayer() {
	return mem::FindAddr(mem::hProcess, mem::moduleBase + 0x02FEE4B0, { 0xA8, 0x10, 0x40, 0x0 });
}

uintptr_t pointers::UI() {
	return mem::FindAddr(mem::hProcess, mem::moduleBase + 0x02FA94F0, { 0x200, 0x128, 0x40, 0x8, 0x248 });
}

uintptr_t pointers::entityFacing() {
	return mem::FindAddr(mem::hProcess, mem::moduleBase + 0x02FEE4B0, { 0xA8, 0x20, 0x38, 0x728, 0x0, 0x870 });
}

uintptr_t pointers::attackSwing() {
	return mem::moduleBase + 0x102460E;
}

uintptr_t pointers::playerSpeed() {
	return mem::FindAddr(mem::hProcess, mem::moduleBase + 0x03016010, { 0x30, 0xF0, 0x410, 0x18, 0xE0, 0x8, 0x9C });
}

uintptr_t pointers::canPlaceBlock() {
	return mem::FindAddr(mem::hProcess, mem::moduleBase + 0x03016010, { 0x30, 0x88, 0x30, 0x6E8, 0x0, 0x850 });
}

uintptr_t pointers::blockFace() {
	return mem::moduleBase + 0x5D2412;
}

uintptr_t pointers::blockCoordX() {
	return mem::FindAddr(mem::hProcess, mem::moduleBase + 0x03016010, { 0x30, 0x88, 0x30, 0x6E8, 0x0, 0x858 });
}

uintptr_t pointers::blockCoordY() {
	return mem::FindAddr(mem::hProcess, mem::moduleBase + 0x03016010, { 0x30, 0x88, 0x30, 0x6E8, 0x0, 0x85C });
}

uintptr_t pointers::blockCoordZ() {
	return mem::FindAddr(mem::hProcess, mem::moduleBase + 0x03016010, { 0x30, 0x88, 0x30, 0x6E8, 0x0, 0x860 });
}

uintptr_t pointers::serverCrashPacket() {
	return mem::moduleBase + 0xFD1E2B;
}

uintptr_t pointers::criticalsPacket() {
	return mem::moduleBase + 0xFD1E56;
}

uintptr_t pointers::movementPacket() {
	return mem::moduleBase + 0xF9508B;
}

uintptr_t pointers::noPacket() {
	return mem::moduleBase + 0xF984ED;
}

uintptr_t pointers::webTick() {
	return mem::moduleBase + 0x12073A5;
}

uintptr_t pointers::noSlowDownOne() {
	return mem::moduleBase + 0x1A5B9F9;
}

uintptr_t pointers::noSlowDownTwo() {
	return mem::moduleBase + 0xF72506;
}

uintptr_t pointers::knockBackX() {
	return mem::moduleBase + 0x1210362;
}

uintptr_t pointers::knockBackY() {
	return mem::moduleBase + 0x121036B;
}

uintptr_t pointers::knockBackZ() {
	return mem::moduleBase + 0x1210374;
}

uintptr_t pointers::inWaterTick() {
	return mem::moduleBase + 0x121883D;
}

uintptr_t pointers::showCoords() {
	return mem::moduleBase + 0x5FF84D;
}

uintptr_t pointers::groundCollision() {
	return mem::moduleBase + 0x1898F92;
}

uintptr_t pointers::connectedServerIP() {
	return mem::FindAddr(mem::hProcess, mem::moduleBase + 0x03016010, { 0x30, 0x68, 0xC0, 0x18, 0x360, 0x0 });
}

uintptr_t pointers::SprintInstruction() {
	return mem::moduleBase + 0x1A5B8F0;
}

uintptr_t pointers::mousePitch() {
	return mem::FindAddr(mem::hProcess, mem::moduleBase + 0x03016010, { 0x30, 0xE0, 0x28, 0x30, 0x168, 0x0, 0x14 });
}

uintptr_t pointers::mouseYaw() {
	return mem::FindAddr(mem::hProcess, mem::moduleBase + 0x03016010, { 0x30, 0xE0, 0x28, 0x30, 0x168, 0x0, 0x10 });
}

/* Bytes */

BYTE* gameBytes::SCAFFOLDBYTES = (BYTE*)"\x41\x88\x86\x54\x08\x00\x00";
BYTE* gameBytes::SERVERCRASHERBYTES = (BYTE*)"\xFF\x50\x58\xF2\x0F\x10\x00";
BYTE* gameBytes::NOPACKETBYTES = (BYTE*)"\x80\xB8\x31\x03\x00\x00\x00";
BYTE* gameBytes::WEBTICKBYTES = (BYTE*)"\xF3\x0F\x11\x89\x38\x02\x00\x00";
BYTE* gameBytes::NOSLOWDOWN1BYTES = (BYTE*)"\xF3\x0F\x11\x46\x0C";
BYTE* gameBytes::NOSLOWDOWN2BYTES = (BYTE*)"\xF3\x0F\x11\x46\x0C";
BYTE* gameBytes::NOKNOCKBACKXBYTES = (BYTE*)"\x89\x81\x6C\x04\x00\x00";
BYTE* gameBytes::NOKNOCKBACKYBYTES = (BYTE*)"\x89\x81\x70\x04\x00\x00";
BYTE* gameBytes::NOKNOCKBACKZBYTES = (BYTE*)"\x89\x81\x74\x04\x00\x00";
BYTE* gameBytes::INWATERBYTES = (BYTE*)"\xC6\x83\x3D\x02\x00\x00\x01";
BYTE* gameBytes::COORDINATESONBYTES = (BYTE*)"\x90\x90\x90\x90\x74\x07";
BYTE* gameBytes::COORDINATEOFFBYTES = (BYTE*)"\x80\x78\x04\x00\x74\x07";
BYTE* gameBytes::GROUNDCOLLISIONBYTES = (BYTE*)"\xF3\x41\x0F\x5C\x19";
BYTE* gameBytes::CRITICALSPATCHBYTES = (BYTE*)"\xB8\x00\x00\x00\x00\x90\x90";
BYTE* gameBytes::CRITICALSFIXBYTES = (BYTE*)"\x0F\xB6\x86\x78\x01\x00\x00";
BYTE* gameBytes::SPRINTINSTRUCTIONBYTES = (BYTE*)"\x44\x0F\x2F\x66\x0C";

/* Local Player Offsets */

unsigned int Player::airJump = 0x178;
unsigned int Player::onGround = 0x17C;
unsigned int Player::isFlying = 0xA88;
unsigned int Player::isInWater = 0x23D;
unsigned int Player::currentGamemode = 0x1D9C;
unsigned int Player::viewCreativeItems = 0xAA0;
unsigned int Player::airAcceleration = 0x8A4;
unsigned int Player::hitboxWidth = 0x44C;
unsigned int Player::hitboxHeight = 0x450;
unsigned int Player::isFalling = 0x194;
unsigned int Player::velocityX = 0x46C;
unsigned int Player::velocityY = 0x470;
unsigned int Player::velocityZ = 0x474;
unsigned int Player::currentX1 = 0x430;
unsigned int Player::currentX2 = 0x43C;
unsigned int Player::currentY1 = 0x434;
unsigned int Player::currentY2 = 0x440;
unsigned int Player::currentZ1 = 0x438;
unsigned int Player::currentZ2 = 0x444;
unsigned int Player::currentX3 = 0x454;
unsigned int Player::currentY3 = 0x458;
unsigned int Player::currentZ3 = 0x45C;
unsigned int Player::currentUsername = 0x9E8;
unsigned int Player::currentPitch = 0xF0;
unsigned int Player::currentYaw = 0xF4;
unsigned int Player::stepAssist = 0x220;
unsigned int Player::dimensionID = 0xBC;
unsigned int Player::movedTick = 0x32C;