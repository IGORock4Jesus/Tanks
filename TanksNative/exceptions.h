#pragma once

#include <exception>
#include <string>


struct ArgumentOutOfRangeException : std::exception {
	ArgumentOutOfRangeException(std::string name)
		: std::exception(("�������� " + name + " ������� �� ����� ���������� ��������.").c_str()) {}
};

struct ArgumentNullException : std::exception {
	ArgumentNullException(std::string name)
		: std::exception(("�������� " + name + " ����� �������� nullptr.").c_str()) {}
};

struct EndOfMemoryException : std::exception {
	EndOfMemoryException(std::string message)
		: std::exception(message.c_str()) {}
};

