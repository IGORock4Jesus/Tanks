#pragma once

#include <map>
#include <vector>

#include "Entity.h"
#include "System.h"

namespace ECS
{
class SystemManager {
	std::vector<System*> systems;

public:
	template <typename _System>
	void Add(_System* system) {
		static_assert(std::is_base_of_v<System, _System>, "������� ������ ���� ����������� �� ������ System, ������ �� ��� ���������� TSystem.");
		systems.push_back(system);
	}

	/*template <typename _System>
	_System* Get() {
		static_assert(std::is_base_of_v<System, _System>, "������� ������ ���� ����������� �� ������ System, ������ �� ��� ���������� TSystem.");
		for (auto& s : systems) {
		}
	}*/
};
}