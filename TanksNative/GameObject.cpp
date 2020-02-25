#include "GameObject.h"
#include "Renderer.h"


GameObject::GameObject()
	: _Depth{ &Depth::Action }
{
}

void GameObject::Render()
{
	Renderer::DrawSprite(_Position, _Depth->GetValue(), _Size, _TextureCoords);
}

void GameObject::Update(float elapsedTime)
{
}
