#ifndef LOGGER_H
#define LOGGER_H

#include <ctime>
#include <fstream>
#include <iostream>
#include <sstream>
using namespace std;

enum LogLevel { DEBUG, INFO, WARNING, ERROR, CRITICAL };

class Logger {

public:
	static void log(LogLevel level, const string& message) { return Get().Ilog(level, message); }

private:
    void Ilog(LogLevel level, const string& message);

	string levelToString(LogLevel level);

public:
	Logger(const Logger&) = delete;

	static Logger& Get()
	{
		static Logger instance;
		return instance;
	}

private:
	Logger() {}
};

#endif
