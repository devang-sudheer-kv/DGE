#include "file.h"

std::string readFile(const char* source)
{
	std::ifstream file(source);
	if (!file.is_open())
	{
		throw std::runtime_error("Failed to open file");
	}

	std::string str;
	std::string fileContents;
	str.reserve(50);
	fileContents.reserve(512);
	while (std::getline(file, str))
	{
		fileContents += str;
		fileContents.push_back('\n');
	}
	return fileContents;

}