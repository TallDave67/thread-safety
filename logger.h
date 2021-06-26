//logger.h
#ifndef _LOGGER_H_
#define _LOGGER_H_

#include <string>
#include <mutex>
#include "logger-log-type.h"

class Logger {

public:
  Logger(LogType loglevel);
  ~Logger();
  
  void log(const std::string& sourceFile, const std::string& funcName, int lineNumber, std::string & logline, LogType logtype);
  
private:
  LogType loglevel;
  std::mutex log_mutex;
};

#endif
