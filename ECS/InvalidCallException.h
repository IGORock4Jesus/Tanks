#pragma once

#include <exception>

struct InvalidCallException : std::exception
{
	InvalidCallException()
		: std::exception("������������ ����� ������. � ������� ��������� �������, ������� ������ ����� ������.")
	{
			
	}

	InvalidCallException(const char* message)
		: std::exception(message)
	{
			
	}
};
