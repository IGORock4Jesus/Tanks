#pragma once

#include <exception>
#include <string>


struct ArgumentOutOfRangeException : std::exception {
	ArgumentOutOfRangeException(std::string name)
		: std::exception(("Аргумент " + name + " выходит за рамки допустимых значений.").c_str()) {}
};

struct ArgumentNullException : std::exception {
	ArgumentNullException(std::string name)
		: std::exception(("Аргумент " + name + " имеет значение nullptr.").c_str()) {}
};

struct EndOfMemoryException : std::exception {
	EndOfMemoryException(std::string message)
		: std::exception(message.c_str()) {}
};

