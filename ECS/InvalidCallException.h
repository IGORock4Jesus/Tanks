#pragma once

#include <exception>

struct InvalidCallException : std::exception
{
	InvalidCallException()
		: std::exception("Неправильный вызов метода. В текущем состоянии объекта, вызвать данный метод нельзя.")
	{
			
	}

	InvalidCallException(const char* message)
		: std::exception(message)
	{
			
	}
};
