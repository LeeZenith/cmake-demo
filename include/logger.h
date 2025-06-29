#pragma once

#include <string>

namespace logger {
    enum class Level {
        DEBUG,
        INFO,
        WARNING,
        ERROR
    };

    void log(Level level, const std::string& message);
    void setLogLevel(Level level);
}