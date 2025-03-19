#pragma once
#include <string>
#include <iostream>

enum LogLevel {
	INFO = 0,
	DEBUG = 1,
	ERROR = 2,
};

class Logger {
	public:
	void Trace(LogLevel level, std::string text);
};
