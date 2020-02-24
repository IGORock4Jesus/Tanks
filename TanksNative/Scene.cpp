#include "Scene.h"
#include <list>
#include <queue>
#include <atomic>
#include "GameObject.h"
#include "Phisics.h"
#include "GameObjectManager.h"


namespace Scene {



void Clear() {
	GameObjectManager::Clear();
}

void Add(std::shared_ptr<GameObject> gameObject) {
	if (!gameObject)
		return;
	GameObjectManager::Add(gameObject);
}

void Render() {
	for (auto& node : GameObjectManager::nodes) {
		if(node.gameObject)
			node.gameObject->Render();
	}
}
void Update(float elapsedTime) {
	for (auto& node : GameObjectManager::nodes) {
		if(node.gameObject)
			node.gameObject->Update(elapsedTime);
	}

	Phisics::Update();
}

}