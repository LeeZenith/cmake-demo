#include "logger.h"
#include <stdio.h>
#include <time.h>

void log_message(const char* message) {
    time_t now;
    time(&now);
    printf("[LOG] %s: %s\n", ctime(&now), message);
}