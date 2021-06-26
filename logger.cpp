//logger.cpp
#include "logger.h"
#include <iostream>
#include <string>
#include "utility-time.hpp"

Logger::Logger(LogType _loglevel) : loglevel(_loglevel) {} 
Logger::~Logger() {}
  
void Logger::log(const std::string& sourceFile, const std::string& funcName, int lineNumber, std::string & logentry, LogType logtype)
{
  if(logtype <= loglevel)
  {
    const std::lock_guard<std::mutex> lock(log_mutex);
    std::string logline = utility::get_formatted_time() + ": " + sourceFile + "(" + std::to_string(lineNumber) + "): " + funcName + ": " + logentry;
    std::cout << logline << std::endl;
  }
}

