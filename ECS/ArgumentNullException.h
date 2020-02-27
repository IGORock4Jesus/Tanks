#pragma once

#include <exception>
#include <string>

struct ArgumentNullException : std::exception
{
	ArgumentNullException()
		: std::exception("�������� ����� �������� nullptr.")
	{
	}
	ArgumentNullException(const std::string& name)
		: std::exception(("�������� " + name + " ����� �������� nullptr.").c_str())
	{
	}
};