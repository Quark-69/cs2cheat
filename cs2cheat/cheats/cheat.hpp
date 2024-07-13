#pragma once

#include <thread>
#include <iostream>

#include "../mem/memory.hpp"
#include "../math/Vector.h"


extern bool triggerBhop;
extern bool triggerAimbot;
extern bool aimOnTeam;
extern bool done;
extern float aimbotFOV;

extern Vector2 ScreenSize;
extern Vector2 ScreenCentre;


namespace offsets
{

	//cheatengine
	constexpr std::ptrdiff_t forceJump = 0x181C670;

	//offsets.hpp
	constexpr std::ptrdiff_t dwEntityList = 0x19BDD58;
	constexpr std::ptrdiff_t dwViewMatrix = 0x1A1FCB0;
	constexpr std::ptrdiff_t dwLocalPlayerPawn = 0x1823A08;
	constexpr std::ptrdiff_t dwViewAngles = 0x1A2D228;

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
}

class Cheat
{

private:
	Memory mem;
	std::uintptr_t client = 0;

	static constexpr uint32_t PLUS_JUMP = 65537;
	static constexpr uint32_t MINUS_JUMP = 256;

public:
	Cheat(const std::string& processName)
		:mem(processName)
	{
		client = mem.GetModuleAddress("client.dll");
	}

	void Bhop();

	void Aimbot();


	void Run();


	void Log() const
	{
		std::cout << "Client address: " << std::hex << client <<  std::dec << std::endl;
	}

};