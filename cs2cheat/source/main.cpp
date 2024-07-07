#include "memory.hpp"

#include <thread>
#include <iostream>

namespace offsets
{
	constexpr auto localPlayerPawn = 0x1823A08;
	constexpr auto flags = 0x3CC;
	constexpr auto forceJump = 0x181C670;
}

int main()
{
	const auto mem = Memory("cs2.exe");

	const auto client = mem.GetModuleAddress("client.dll");

	if(!client)
	{
		std::cout << "Failed to get client.dll" << std::endl;
		return 1;
	}
	else
	{
		std::cout << "Loaded client.dll at: " << std::hex << client << std::dec << std::endl;
	}

	while (true)
	{
		
		std::this_thread::sleep_for(std::chrono::milliseconds(1));

		const auto localPlayerPawn = mem.Read<std::uintptr_t>(client + offsets::localPlayerPawn);

		if (!localPlayerPawn)
			continue;

		const auto localPlayerFlags = mem.Read<std::uintptr_t>(localPlayerPawn + offsets::flags);

		// bhop
		if (GetAsyncKeyState(VK_SPACE) && (localPlayerFlags & (static_cast<unsigned long long>(1) << 0))) {

			mem.Write<std::uintptr_t>(client + offsets::forceJump, 65537);

			std::this_thread::sleep_for(std::chrono::milliseconds(1));

			mem.Write<std::uintptr_t>(client + offsets::forceJump, 256);
		}
	}
}