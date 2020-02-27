#pragma once

#include <exception>
#include <string>

struct ArgumentNullException : std::exception
{
	ArgumentNullException()
		: std::exception("Аргумент имеет значение nullptr.")
	{
	}
	ArgumentNullException(const std::string& name)
		: std::exception(("Аргумент " + name + " имеет значение nullptr.").c_str())
	{
	}
};