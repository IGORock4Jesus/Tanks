#pragma once

#include <memory>

class GameObject;

namespace Scene {

void Clear();
void Add(std::shared_ptr<GameObject> gameObject);

void Render();
void Update(float elapsedTime);

}