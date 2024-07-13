#include "cheat.hpp"

void Cheat::Bhop()
{
	const auto localPlayerPawn = mem.Read<std::uintptr_t>(client + offsets::dwLocalPlayerPawn);

	if (!localPlayerPawn)
		return;

	const auto localPlayerFlags = mem.Read<std::uintptr_t>(localPlayerPawn + offsets::flags);

	if (GetAsyncKeyState(VK_SPACE) && (localPlayerFlags & (static_cast<unsigned long long>(1) << 0))) {

		mem.Write<std::uintptr_t>(client + offsets::forceJump, PLUS_JUMP);

		std::this_thread::sleep_for(std::chrono::milliseconds(4));

		mem.Write<std::uintptr_t>(client + offsets::forceJump, MINUS_JUMP);
	}
}

void Cheat::Aimbot()
{

	uintptr_t entityList = mem.Read<uintptr_t>(client + offsets::dwEntityList);

	if (!entityList)
		return;

	const auto localPlayerPawn = mem.Read<std::uintptr_t>(client + offsets::dwLocalPlayerPawn);

	if (!localPlayerPawn)
		return;

	int team = mem.Read<int>(localPlayerPawn + offsets::m_iTeamNum);

	Vector localEyePos = mem.Read<Vector>(localPlayerPawn + offsets::m_vOldOrigin) + mem.Read<Vector>(localPlayerPawn + offsets::m_vecViewOffset);


	float closestDistance = FLT_MAX;
	Vector enemyPos;

	uint32_t entitiesCount = 0;

	for (int i = 0; i < 64; i++)
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
		{
			continue;
		}

		if (localPlayerPawn == entityPawn)
		{
			continue;
		}


		if ((team == mem.Read<int>(entityPawn + offsets::m_iTeamNum)))
		{
			continue;
		}

		if (mem.Read<std::uint32_t>(entityPawn + offsets::m_iHealth) <= 0)
		{
			continue;
		}

		if (!mem.Read<bool>(entityPawn + offsets::m_entitySpottedState + offsets::m_bSpotted))
		{
			continue;
		}

		uintptr_t sceneNode = mem.Read<uintptr_t>(entityPawn + offsets::m_pGameSceneNode);

		uintptr_t boneMatrix = mem.Read<uintptr_t>(sceneNode + offsets::m_modelState + 0x80);

		Vector entityHeadPos = mem.Read<Vector>(boneMatrix + 6 * 32);

		ViewMatrix viewMatrix = mem.Read<ViewMatrix>(client + offsets::dwViewMatrix);

		Vector2 head2d = Vector2::WorldToScreen(viewMatrix, entityHeadPos, ScreenSize.x, ScreenSize.y);

		float pixelDistance = head2d.distance(ScreenCentre);
		
		++entitiesCount;



		if (pixelDistance < closestDistance)
		{
			closestDistance = pixelDistance;
			enemyPos = entityHeadPos;
		}

	}

	if (GetAsyncKeyState(VK_LMENU) && entitiesCount > 0)
	{
		Vector relativeAngle = (enemyPos - localEyePos).RelativeAngle();
		mem.Write<Vector>(client + offsets::dwViewAngles, relativeAngle);
	}


	std::this_thread::sleep_for(std::chrono::milliseconds(10));

}

void Cheat::Run()
{

	std::thread bhopThread([this]() {
		while (!done)
		{
			if(triggerBhop)
			{
				Bhop();
				std::this_thread::sleep_for(std::chrono::milliseconds(10));
			}
		}
	});

	std::thread aimbotThread([this]() {
		while (!done)
		{
			if (triggerAimbot)
			{
				Aimbot();
			}
		}
	});


	bhopThread.join();
	aimbotThread.join();
}