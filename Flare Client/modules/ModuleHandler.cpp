#include "ModuleHandler.h"

using namespace std;

int GuiLoaderTicker = 0;

bool ModuleHandler::jetpackToggle = false;
bool ModuleHandler::aimbotToggle = false;
bool ModuleHandler::hitboxToggle = false;
bool ModuleHandler::triggerbotToggle = false; 
bool ModuleHandler::airJumpToggle = false;
bool ModuleHandler::airaccspeedToggle = false;
bool ModuleHandler::noslowdownToggle = false;
bool ModuleHandler::nowebToggle = false;
bool ModuleHandler::noknockbackToggle = false;
bool ModuleHandler::nofallToggle = false;
bool ModuleHandler::gamemodeToggle = false;
bool ModuleHandler::instabreakToggle = false;
bool ModuleHandler::playerspeedToggle = false;
bool ModuleHandler::phaseToggle = false;
bool ModuleHandler::scaffoldToggle = false;
bool ModuleHandler::nowaterToggle = false;
bool ModuleHandler::jesusToggle = false;
bool ModuleHandler::bhopToggle = false;
bool ModuleHandler::criticalsToggle = false;
bool ModuleHandler::flightToggle = false;
bool ModuleHandler::tpauraToggle = false;
bool ModuleHandler::stepAssistToggle = false;
bool ModuleHandler::nopacketToggle = false;
bool ModuleHandler::freecamToggle = false;
bool ModuleHandler::servercrasherToggle = false;
bool ModuleHandler::coordinatesToggle = false;
bool ModuleHandler::noClipToggle = false;
bool ModuleHandler::clicktpToggle = false;
bool ModuleHandler::autoSprintToggle = false;
bool ModuleHandler::espToggle = false;

float ModuleHandler::hitboxWidthFloat = 6.f;
float ModuleHandler::hitboxHeightFloat = 3.f;
float ModuleHandler::airAccelerationSpeed = 0.1;
float ModuleHandler::playerSpeedVal = 0.45;
float ModuleHandler::teleportX = 0;
float ModuleHandler::teleportY = 0;
float ModuleHandler::teleportZ = 0;
float ModuleHandler::jesusVal = 0.2;
float ModuleHandler::bhopVal = 0.2;
float ModuleHandler::tpauraRange = 24;
int ModuleHandler::tpauraSkips = 10;
float ModuleHandler::jetpackVal = 1.0f;

int ModuleHandler::gamemodeVal = 1;

int discordPresenceTick;
int ModuleHandler::drpDisplayName = 0;

#include <fstream>
ifstream File;

//Discord Stuff
int discordEmbedUpdateTick;

ModuleHandler::ModuleHandler(HANDLE hProcess, HWND host) {
	if (FindWindowA(NULL, "Minecraft") == NULL) exit(3);

	uintptr_t LocalPlayer = Player::LocalPlayer();

	vector<uintptr_t> EntityListArr = EntityList::EntityListHandler(hProcess, LocalPlayer);

	string playerUsername;
	int movement;
	ReadProcessMemory(hProcess, (BYTE*)mem::FindAddr(hProcess, LocalPlayer, { 0x32C }), &movement, sizeof(movement), 0);
	ReadProcessMemory(hProcess, (BYTE*)mem::FindAddr(hProcess, LocalPlayer, { 0x9E8 }), &playerUsername, sizeof(playerUsername), 0);

	discordPresenceTick += 1;

	char connectedServer[20];
	ReadProcessMemory(hProcess, (BYTE*)pointers::connectedServerIP(), &connectedServer, sizeof(connectedServer), 0);

	char* serverIP = NULL;

	for (char A = '1'; A < 'Z'; A++) { //Check for valid char for first character of IP - Simple logic so we don't get odd chars when on single player
		if (toupper(connectedServer[0]) == A) serverIP = (char*)connectedServer;
	}

	if (discordPresenceTick > 200) {
		if (playerUsername.length() > 0) {
			char* c = new char[playerUsername.length() + 1];
			strcpy(c, playerUsername.c_str());
			switch (ModuleHandler::drpDisplayName) {
			case 0:
				if (serverIP != NULL) {
					Discord::Update(c, (char*)serverIP, EntityListArr.size());
				}
				else {
					Discord::Update(c, (char*)"World", EntityListArr.size());
				}
			break;

			case 1:
				if (serverIP != NULL) {
					Discord::Update((char*)"Currently In Game", (char*)serverIP, EntityListArr.size());
				}
				else {
					Discord::Update((char*)"Currently In Game", (char*)"World", EntityListArr.size());
				}
			break;
			}
		}
		else if (playerUsername.length() < 1) {
			Discord::Update((char*)"Minecraft", (char*)"Main Menu", 0);
		}
		discordPresenceTick = 0;
	}

	GuiLoaderTicker += 1;

	/*if (GetAsyncKeyState(VK_F8)) {
		if (GuiLoaderTicker > 60) {
			if (GuiLoader::windowToggle) {
				GuiLoader::windowToggle = false;
			}
			else if (!GuiLoader::windowToggle) {
				GuiLoader::windowToggle = true;
			}
			GuiLoaderTicker = 0;
		}
	}*/

	KeybindHandler::KeybindHandler(host);

	if (ModuleHandler::jetpackToggle) {
		float vect[3], pitch, yaw;
		ReadProcessMemory(hProcess, (BYTE*)mem::FindAddr(hProcess, LocalPlayer, { Player::currentPitch }), &pitch, sizeof(pitch), 0);
		ReadProcessMemory(hProcess, (BYTE*)mem::FindAddr(hProcess, LocalPlayer, { Player::currentYaw }), &yaw, sizeof(yaw), 0);
		ModuleHandler::directionalVector(vect, (yaw + 89.f) * 3.141592653589793 / 178, pitch * 3.141592653589793 / 178);
		float X = ModuleHandler::jetpackVal * vect[0];
		float Y = ModuleHandler::jetpackVal * -vect[1];
		float Z = ModuleHandler::jetpackVal * vect[2];
		WriteProcessMemory(hProcess, (BYTE*)mem::FindAddr(hProcess, LocalPlayer, { Player::velocityX }), &X, sizeof(X), 0);
		WriteProcessMemory(hProcess, (BYTE*)mem::FindAddr(hProcess, LocalPlayer, { Player::velocityY }), &Y, sizeof(Y), 0);
		WriteProcessMemory(hProcess, (BYTE*)mem::FindAddr(hProcess, LocalPlayer, { Player::velocityZ }), &Z, sizeof(Z), 0);
		ModuleHandler::jetpackToggle = false;
	}

	if (ModuleHandler::aimbotToggle) {
		Aimbot::Aimbot(hProcess);
	}
	if (ModuleHandler::hitboxToggle) {
		Hitbox::Hitbox(hProcess, EntityListArr, ModuleHandler::hitboxWidthFloat, ModuleHandler::hitboxHeightFloat);
	}
	else if (!ModuleHandler::hitboxToggle) {
		Hitbox::Hitbox(hProcess, EntityListArr, 0.6, 1.8);
	}
	if (ModuleHandler::triggerbotToggle) {
		TriggerBot::TriggerBot(hProcess, 'N');
	}
	else if (!ModuleHandler::triggerbotToggle) {
		TriggerBot::TriggerBot(hProcess, 'F');
	}
	if (ModuleHandler::airJumpToggle) {
		AirJump::AirJump(hProcess, LocalPlayer);
	}
	if (ModuleHandler::airaccspeedToggle) {
		AirAccelerationSpeed::AirAccelerationSpeed(hProcess, LocalPlayer, ModuleHandler::airAccelerationSpeed);
	}
	if (ModuleHandler::noslowdownToggle) {
		NoSlowDown::NoSlowDown(hProcess, 'N');
	}
	else if (!ModuleHandler::noslowdownToggle) {
		NoSlowDown::NoSlowDown(hProcess, 'F');
	}
	if (ModuleHandler::nowebToggle) {
		NoWeb::NoWeb(hProcess, 'N');
	}
	else if (!ModuleHandler::nowebToggle) {
		NoWeb::NoWeb(hProcess, 'F');
	}
	if (ModuleHandler::noknockbackToggle) {
		NoKnockBack::NoKnockBack(hProcess, 'N');
	}
	else if (!ModuleHandler::noknockbackToggle) {
		NoKnockBack::NoKnockBack(hProcess, 'F');
	}
	if (ModuleHandler::nofallToggle) {
		NoFall::NoFall(hProcess, LocalPlayer);
	}
	if (ModuleHandler::gamemodeToggle) {
		Gamemode::Gamemode(hProcess, LocalPlayer, ModuleHandler::gamemodeVal, 1);
	}
	else if (!ModuleHandler::gamemodeToggle) {
		Gamemode::Gamemode(hProcess, LocalPlayer, ModuleHandler::gamemodeVal, 0);
	}
	if (ModuleHandler::instabreakToggle) {
		Instabreak::Instabreak(hProcess, 1);
	}
	else if (!ModuleHandler::instabreakToggle) {
		Instabreak::Instabreak(hProcess, 0);
	}
	if (ModuleHandler::playerspeedToggle) {
		PlayerSpeed::PlayerSpeed(hProcess, ModuleHandler::playerSpeedVal, 1);
	}
	else if (!ModuleHandler::playerspeedToggle) {
		PlayerSpeed::PlayerSpeed(hProcess, ModuleHandler::playerSpeedVal, 0);
	}
	if (ModuleHandler::phaseToggle) {
		Phase::Phase(hProcess, LocalPlayer, 'E');
	}
	else if (!ModuleHandler::phaseToggle) {
		Phase::Phase(hProcess, LocalPlayer, 'F');
	}
	if (ModuleHandler::scaffoldToggle) {
		Scaffold::Scaffold(hProcess, 1);
	}
	else if (!ModuleHandler::scaffoldToggle) {
		Scaffold::Scaffold(hProcess, 0);
	}
	if (ModuleHandler::nowaterToggle) {
		NoWater::NoWater(hProcess, 0);
	}
	else if (!ModuleHandler::nowaterToggle) {
		NoWater::NoWater(hProcess, 'F');
	}
	if (ModuleHandler::jesusToggle) {
		Jesus::Jesus(hProcess, LocalPlayer, ModuleHandler::jesusVal);
	}
	if (ModuleHandler::bhopToggle) {
		BHOP::BHOP(hProcess, LocalPlayer, ModuleHandler::bhopVal);
	}
	if (ModuleHandler::criticalsToggle) {
		Criticals::Criticals(hProcess, 'P');
	}
	else if (!ModuleHandler::criticalsToggle) {
		Criticals::Criticals(hProcess, 'F');
	}
	if (ModuleHandler::flightToggle) {
		Flight::Flight(hProcess, LocalPlayer, 1);
	}
	else if (!ModuleHandler::flightToggle) {
		Flight::Flight(hProcess, LocalPlayer, 0);
	}
	if (ModuleHandler::tpauraToggle) {
		TpAura::TpAura(hProcess, LocalPlayer, EntityListArr, 0, ModuleHandler::tpauraRange, ModuleHandler::tpauraSkips);
	}
	else if (!ModuleHandler::tpauraToggle) {
		TpAura::TpAura(hProcess, LocalPlayer, EntityListArr, 1, ModuleHandler::tpauraRange, ModuleHandler::tpauraSkips);
	}
	if (ModuleHandler::stepAssistToggle) {
		StepAssist::StepAssist(hProcess, LocalPlayer, 1);
	}
	else if (!ModuleHandler::stepAssistToggle) {
		StepAssist::StepAssist(hProcess, LocalPlayer, 0);
	}
	if (ModuleHandler::nopacketToggle) {
		NoPacket::NoPacket(hProcess, 'N');
	}
	else if (!ModuleHandler::nopacketToggle) {
		NoPacket::NoPacket(hProcess, 'F');
	}
	if (ModuleHandler::freecamToggle) {
		FreeCam::FreeCam(hProcess, 'N');
	}
	else if (!ModuleHandler::freecamToggle) {
		FreeCam::FreeCam(hProcess, 'F');
	}
	if (ModuleHandler::servercrasherToggle) {
		ServerCrasher::ServerCrasher(hProcess, 'N');
	}
	else if (!ModuleHandler::servercrasherToggle) {
		ServerCrasher::ServerCrasher(hProcess, 'F');
	}
	if (ModuleHandler::coordinatesToggle) {
		Coordinates::Coordinates(hProcess, 1);
	}
	else if (!ModuleHandler::coordinatesToggle) {
		Coordinates::Coordinates(hProcess, 0);
	}
	if (ModuleHandler::noClipToggle) {
		NoClip::NoClip(hProcess, 1);
	}
	else if (!ModuleHandler::noClipToggle) {
		NoClip::NoClip(hProcess, 0);
	}
	if (ModuleHandler::clicktpToggle) {
		ClickTP::ClickTP(hProcess, LocalPlayer);
	}
	if (ModuleHandler::autoSprintToggle) {
		AutoSprint::AutoSprint(hProcess, 1);
	}
	else if (!ModuleHandler::autoSprintToggle) {
		AutoSprint::AutoSprint(hProcess, 0);
	}
	if (ModuleHandler::espToggle) {
		Esp::Esp(hProcess, EntityListArr);
	}
}