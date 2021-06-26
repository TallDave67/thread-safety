#ifndef _UTILITY_TIME_H_
#define _UTILITY_TIME_H_

#include <stdio.h>
#include <time.h>   
#include <string>

namespace utility {

  inline std::string get_formatted_time()
  {
    time_t rawtime;
    struct tm * timeinfo;
    const int timestamp_length = 20;
    char buffer [timestamp_length];

    time (&rawtime);
    timeinfo = localtime (&rawtime);
    strftime (buffer, timestamp_length, "%Y-%m-%d %H:%M:%S", timeinfo);
    
    std::string timestamp = buffer;
    return timestamp;
  }
}

#endif
