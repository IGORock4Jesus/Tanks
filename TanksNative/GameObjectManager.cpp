#include "GameObjectManager.h"
#include <atomic>
#include "exceptions.h"

namespace GameObjectManager
{
Node nodes[COUNT];

void Add(std::shared_ptr<GameObject> gameObject) {
	//bool expected{ false };
	for (size_t i = 0; i < COUNT; i++)
	{
		if (!nodes[i].gameObject) {
			nodes[i].gameObject = gameObject;
			return;
		}
	}
	throw EndOfMemoryException("Слишком маленький буфер для объектов. Попробуйте увеличить значение COUNT.");
}
void Destroy(std::shared_ptr<GameObject> gameObject) {
	for (size_t i = 0; i < COUNT; i++)
	{
		if (nodes[i].gameObject == gameObject) {
			nodes[i].gameObject = nullptr;
			gameObject->Destroy();
			return;
		}
	}
}
void Clear() {
	for (size_t i = 0; i < COUNT; i++)
	{
		if (nodes[i].gameObject) {
			nodes[i].gameObject->Destroy();
			nodes[i].gameObject = nullptr;
		}
	}
}
}

