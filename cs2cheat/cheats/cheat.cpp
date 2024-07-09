#include "cheat.hpp"

void Cheat::Bhop()
{
	const auto localPlayerPawn = mem.Read<std::uintptr_t>(client + offsets::localPlayerPawn);

	if (!localPlayerPawn)
		return;

	const auto localPlayerFlags = mem.Read<std::uintptr_t>(localPlayerPawn + offsets::flags);

	if (GetAsyncKeyState(VK_SPACE) && (localPlayerFlags & (static_cast<unsigned long long>(1) << 0))) {

		mem.Write<std::uintptr_t>(client + offsets::forceJump, 65537);

		std::this_thread::sleep_for(std::chrono::milliseconds(1));

		mem.Write<std::uintptr_t>(client + offsets::forceJump, 256);
	}
}

void Cheat::Aimbot()
{
	uintptr_t entityList = mem.Read<uintptr_t>(client + offsets::dwEntityList);

	if(!entityList)
		return;

	const auto localPlayerPawn = mem.Read<std::uintptr_t>(client + offsets::localPlayerPawn);

	if (!localPlayerPawn)	
		return;

	int team = mem.Read<int>(localPlayerPawn + offsets::m_iTeamNum);

	Vector localEyePos = mem.Read<Vector>(localPlayerPawn + offsets::m_vOldOrigin) + mem.Read<Vector>(localPlayerPawn + offsets::m_vecViewOffset);


	float closestDistance = FLT_MAX;
	Vector enemyPos;

	bool spotted = false;

	for(int i = 0; i < 64; i++)
	{

		uintptr_t listEntry = mem.Read<uintptr_t>(entityList + ((static_cast<unsigned long long>(8 * (i & 0x7ff) >> 9)) + 16));
	
		if (!listEntry)
			continue;
		
		uintptr_t entityController = mem.Read<uintptr_t>(listEntry + static_cast<unsigned long long>(120) * (i & 0x1ff));
	
		if (!entityController)
			continue;

		uintptr_t entityControllerPawn = mem.Read<uintptr_t>(entityController + offsets::m_hPlayerPawn);
	
		if (!entityControllerPawn)
			continue;

		uintptr_t entityPawn = mem.Read<uintptr_t>(listEntry + 120 * (entityControllerPawn & 0x1ff));

		if (!entityPawn)
			continue;
		
			
		if(team == mem.Read<int>(entityPawn + offsets::m_iTeamNum) && !aimOnTeam)
			continue;

		if(mem.Read<std::uint32_t>(entityPawn + offsets::m_iHealth) <= 0)
			continue;

		if (!mem.Read<bool>(entityPawn + offsets::m_entitySpottedState + offsets::m_bSpotted))
		{
			continue;
		}
		

		Vector entityEyePos = mem.Read<Vector>(entityPawn + offsets::m_vOldOrigin) + mem.Read<Vector>(entityPawn + offsets::m_vecViewOffset);



		float currentDistance = localEyePos.distance(entityEyePos);

		if (currentDistance < closestDistance)
		{

			if (mem.Read<bool>(entityPawn + offsets::m_entitySpottedState + offsets::m_bSpotted))
			{
				closestDistance = currentDistance;
				enemyPos = entityEyePos;
				spotted = true;
			}
		}

	}

	if(GetAsyncKeyState(VK_LMENU) && spotted)
	{
		Vector relativeAngle = (enemyPos - localEyePos).RelativeAngle();
		mem.Write<Vector>(client + offsets::dwViewAngles, relativeAngle);
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
}



void Cheat::Run()
{
	if(triggerBhop)
		Bhop();

	if(triggerAimbot)
		Aimbot();

	std::this_thread::sleep_for(std::chrono::milliseconds(1));
}