#pragma once

#include <thread>
#include <iostream>

#include "../mem/memory.hpp"
#include "../math/Vector.h"


extern bool triggerBhop;
extern bool triggerAimbot;
extern bool aimOnTeam;
extern bool done;
extern bool recoilControl;

extern Vector2 ScreenSize;
extern Vector2 ScreenCentre;


namespace offsets
{

	//cheatengine
	constexpr std::ptrdiff_t forceJump = 0x181D670;

	//offsets.hpp
	constexpr std::ptrdiff_t dwCSGOInput = 0x1A28E30;
	constexpr std::ptrdiff_t dwEntityList = 0x19BEEB0;
	constexpr std::ptrdiff_t dwGameEntitySystem = 0x1ADDBC8;
	constexpr std::ptrdiff_t dwGameEntitySystem_highestEntityIndex = 0x1510;
	constexpr std::ptrdiff_t dwGameRules = 0x1A1C668;
	constexpr std::ptrdiff_t dwGlobalVars = 0x1818638;
	constexpr std::ptrdiff_t dwGlowManager = 0x1A1BD50;
	constexpr std::ptrdiff_t dwLocalPlayerController = 0x1A0E9A8;
	constexpr std::ptrdiff_t dwLocalPlayerPawn = 0x1824A08;
	constexpr std::ptrdiff_t dwPlantedC4 = 0x1A261A8;
	constexpr std::ptrdiff_t dwPrediction = 0x18248C0;
	constexpr std::ptrdiff_t dwSensitivity = 0x1A1D338;
	constexpr std::ptrdiff_t dwSensitivity_sensitivity = 0x40;
	constexpr std::ptrdiff_t dwViewAngles = 0x1A2E248;
	constexpr std::ptrdiff_t dwViewMatrix = 0x1A20CD0;
	constexpr std::ptrdiff_t dwViewRender = 0x1A21468;
	constexpr std::ptrdiff_t dwWeaponC4 = 0x19C2940;

	//client.dll.hpp
	constexpr std::ptrdiff_t flags = 0x3CC;
	constexpr std::ptrdiff_t m_iHealth = 0x324;
	constexpr std::ptrdiff_t m_hPawn = 0x5FC;
	constexpr std::ptrdiff_t m_iTeamNum = 0x3C3;
	constexpr std::ptrdiff_t m_vOldOrigin = 0x1274;
	constexpr std::ptrdiff_t m_bSpotted = 0x8;
	constexpr std::ptrdiff_t m_entitySpottedState = 0x2288;
	constexpr std::ptrdiff_t m_vecViewOffset = 0xC50;
	constexpr std::ptrdiff_t m_hPlayerPawn = 0x7DC;
	constexpr std::ptrdiff_t m_modelState = 0x170;
	constexpr std::ptrdiff_t m_pGameSceneNode = 0x308;

	constexpr std::ptrdiff_t m_aimPunchAngle = 0x14CC;

	constexpr std::ptrdiff_t m_iShotsFired = 0x22B4;
}

class Cheat
{

private:
	Memory mem;
	std::uintptr_t client = 0;
	std::uintptr_t engine2 = 0;

	static constexpr uint32_t PLUS_JUMP = 65537;
	static constexpr uint32_t MINUS_JUMP = 256;

	Vector2 oldAimPunch;

public:
	Cheat(const std::string& processName)
		:mem(processName)
	{
		client = mem.GetModuleAddress("client.dll");
	}

	void Bhop();

	void Aimbot();

	void RecoilControl();


	void Run();


};