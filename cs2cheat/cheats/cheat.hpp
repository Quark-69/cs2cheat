#pragma once

#include <thread>
#include <iostream>

#include "../mem/memory.hpp"
#include "../math/Vector.h"


extern bool triggerBhop;
extern bool triggerAimbot;
extern bool aimOnTeam;


namespace offsets
{
	constexpr auto localPlayerPawn = 0x1823A08;
	constexpr auto flags = 0x3CC;
	constexpr auto forceJump = 0x181C670;

	constexpr auto dwEntityList = 0x19BDD78;
	constexpr auto dwViewMatrix = 0x1A1FCD0;
	constexpr auto m_hPawn = 0x5FC;
	constexpr auto m_iHealth = 0x324;
	constexpr auto m_iTeamNum = 0x3C3;
	constexpr auto m_vOldOrigin = 0x1274;

	constexpr auto m_entitySpottedState = 0x2288;

	constexpr auto m_vecViewOffset = 0xC50;

	constexpr std::ptrdiff_t m_hPlayerPawn = 0x7DC;

	constexpr std::ptrdiff_t dwViewAngles = 0x1A2D248;

	constexpr std::ptrdiff_t m_bSpottedByMask = 0xC;

	constexpr std::ptrdiff_t m_bSpotted = 0x8;
}

class Cheat
{

private:
	Memory mem;
	std::uintptr_t client = 0;

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
		std::cout << "Client at: " << std::hex << client <<  std::dec << std::endl;
	}

};