#include "UpdateManager.h"
#include <thread>
#include <Windows.h>
#include "ECS.h"
#include "AnimationManager.h"
#include "Input.h"


namespace UpdateManager
{
std::thread thread;
bool enabled;

void StartThread() {
	DWORD oldTime = timeGetTime();
	while (enabled)
	{
		DWORD newTime = timeGetTime();
		float elapsedTime = (newTime - oldTime) * 0.001f;
		oldTime = newTime;

		Input::Update();

		ECS::Update(elapsedTime);

		AnimationManager::Update(elapsedTime);		

		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
}
void Start() {
	if (enabled)return;
	enabled = true;
	thread = std::thread(StartThread);
}
void Stop() {
	if (!enabled)return;
	enabled = false;
	if (thread.joinable())
		thread.join();
}
}
