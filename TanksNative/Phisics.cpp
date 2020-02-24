#include "Phisics.h"
#include "GameObjectManager.h"


namespace Phisics
{

bool Test(std::shared_ptr<GameObject>& a, std::shared_ptr<GameObject>& b) {
	auto aPos = a->GetPosition(),
		bPos = b->GetPosition(),
		aSize = a->GetSize(),
		bSize = b->GetSize();

	if (aPos.x > bPos.x + bSize.x)
		return false;
	if (bPos.x > aPos.x + aSize.x)
		return false;
	if (aPos.y > bPos.y + bSize.y)
		return false;
	if (bPos.y > aPos.y + aSize.y)
		return false;
	return true;
}

void Update() {
	// пока проверяем каждый с каждым
	for (size_t ai = 0; ai < GameObjectManager::COUNT; ai++)
	{
		auto& a = GameObjectManager::nodes[ai].gameObject;
		if (a) {
			for (size_t bi = ai + 1; bi < GameObjectManager::COUNT; bi++)
			{
				auto& b = GameObjectManager::nodes[bi].gameObject;

				if (!b || a == b) continue;

				if (Test(a, b)) {
					a->Collision(b);
					b->Collision(a);
				}
			}
		}
	}
}

}

