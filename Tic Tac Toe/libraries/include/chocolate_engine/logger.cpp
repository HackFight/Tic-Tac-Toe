#pragma warning(disable  : 4996)
#include"logger.h"

void Logger::Ilog(LogLevel level, const string& message)
{
    time_t now = time(0);
    tm* timeinfo = localtime(&now);
    char timestamp[20];
    strftime(timestamp, sizeof(timestamp),
        "%Y-%m-%d %H:%M:%S", timeinfo);
    
    ostringstream logEntry;
    logEntry << "[" << timestamp << "] " << levelToString(level) << ": " << message << endl;
    
    cout << logEntry.str();
}

 string Logger::levelToString(LogLevel level)
 {
     switch (level) {
     case DEBUG:
        return "DEBUG";
     case INFO:
         return "INFO";
     case WARNING:
         return "WARNING";
     case ERROR:
         return "ERROR";
     case CRITICAL:
         return "CRITICAL";
     default:
         return "UNKNOWN";
     }
 }