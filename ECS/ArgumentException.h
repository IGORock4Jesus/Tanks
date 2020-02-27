#pragma once

#include <exception>
#include <string>

class ArgumentExcpection : std::exception
{
	const std::string argumentName;

public:
	ArgumentExcpection()
		: ArgumentExcpection("")
	{
	}
	ArgumentExcpection(const std::string& name)
		: std::exception("Неправельный аргумент"),
		argumentName(name) {
	}
};