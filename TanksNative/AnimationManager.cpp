#include "AnimationManager.h"
#include <map>
#include <vector>
#include <mutex>
#include <list>


namespace AnimationManager {

std::list<std::shared_ptr<Animation>> animations;
std::mutex locker;

float GetValue(std::shared_ptr<Animation> anim)
{
	if (anim->frames.size() == 0)
		return 0.0f;
	else if (anim->frames.size() == 1)
		return anim->frames.begin()->second;

	if (anim->cursor <= anim->frames.begin()->first)
		return anim->frames.begin()->second;
	else if (anim->cursor >= anim->frames.rbegin()->first)
		return anim->frames.rbegin()->second;

	auto begin = anim->frames.begin();
	while (anim->cursor < begin->first)
		begin++;

	auto end = anim->frames.rbegin();
	while (anim->cursor > end->first)
		end++;

	float av = (anim->cursor - begin->first) / (end->first - begin->first);

	float val = begin->second + (end->second - begin->second) * av;

	return val;
}

void AnimationManager::Update(float elapsedTime)
{
	std::vector<std::shared_ptr<Animation>> forRemove;

	{
		std::lock_guard guard{ locker };

		for (auto anim : animations)
		{
			anim->cursor += elapsedTime;

			float newValue = GetValue(anim);

			anim->callback(newValue);

			if (anim->cursor >= anim->length)
			{
				if (anim->looped)
					anim->cursor -= anim->length;
				else
					forRemove.push_back(anim);
			}
		}
	}

	for (auto item : forRemove)
	{
		animations.remove(item);
	}
}


void AnimationManager::Add(std::shared_ptr<Animation> animation)
{
	std::lock_guard guard{ locker };
	animations.push_back(animation);
}

}