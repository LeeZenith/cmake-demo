#include "logger.h"
#include <iostream>

namespace logger {
    static Level currentLevel = Level::INFO;

    void log(Level level, const std::string& message) {
        if(level < currentLevel) {
            return;
        }

        const char* levelStr = "";
        switch(level) {
            case Level::DEBUG: levelStr = "DEBUG"; break;
            case Level::INFO: levelStr = "INFO"; break;
            case Level::WARNING: levelStr = "WARNING"; break;
            case Level::ERROR: levelStr = "ERROR"; break;
        }

        std::cout << "[" << levelStr << "] " << message << std::endl;
    }

    void setLogLevel(Level level) {
        currentLevel = level;
    }
}