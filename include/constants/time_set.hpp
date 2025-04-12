#pragma once

#include <ctime>

extern time_t current_time;
extern struct tm timeinfo_data;
extern struct tm* timeinfo;

const int SEKOLAH_ID = 91100000;  // 5 zeros

inline void time_init() {
    current_time = time(0);
    timeinfo = &timeinfo_data;

#if defined(_WIN32)
    localtime_s(timeinfo, &current_time);
#else
    localtime_r(&current_time, timeinfo);
#endif
}