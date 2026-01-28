#pragma once
#include <string>
#include <iostream>

#define MSG(X) std::cout << X << std::endl
#define MSG_DBG(X) std::cout << X << std::endl

class LoopLogger {
private:
	std::string m_buffer;
public:
	void log(std::string);
	// log formatted
	void logf(std::string, ...);
};