//thread-manager.h
#ifndef _THREAD_MANAGER_H_
#define _THREAD_MANAGER_H_

#include <cstddef>
#include <map>
#include <mutex>
#include <string>
#include "logger-log-type.h"
#include "logger-call.h"

template <typename TRunnable, typename TLogger>
class ThreadManager {

public:
  ThreadManager(TLogger & _logger) : logger(_logger), last_logical_thread_id(0) {};
  ~ThreadManager() {};
  
  size_t thread_set_logical_id(size_t thread_id)
  {
    const std::lock_guard<std::mutex> lock(logical_thread_id_mutex);
    std::string logentry = "thread_id " + std::to_string(thread_id);
    LOG(logentry, LogType::debug);
    last_logical_thread_id++;
    std::map<size_t, size_t>::iterator it = physical_to_logical_thread_map.find(thread_id);
    if (it != physical_to_logical_thread_map.end())
    {
      it->second = last_logical_thread_id;
      logentry = "remap from " + std::to_string(it->second) + " to " + std::to_string(last_logical_thread_id);
      LOG(logentry, LogType::verbose);
    }
    else
    {
      physical_to_logical_thread_map.insert ( std::pair<size_t, size_t>(thread_id, last_logical_thread_id) );
      logentry = "map to " + std::to_string(last_logical_thread_id);
      LOG(logentry, LogType::verbose);
    } 

    logentry = "logical_thread_id " + std::to_string(last_logical_thread_id);
    LOG(logentry, LogType::debug);
    return last_logical_thread_id;
  }

  size_t thread_get_logical_id(size_t thread_id)
  {
    const std::lock_guard<std::mutex> lock(logical_thread_id_mutex);
    std::string logentry = "thread_id " + std::to_string(thread_id);
    LOG(logentry, LogType::debug);
    std::map<size_t, size_t>::iterator it = physical_to_logical_thread_map.find(thread_id);
    if (it != physical_to_logical_thread_map.end())
    {
      logentry = "mapped to " + std::to_string(it->second);
      LOG(logentry, LogType::debug);
      return it->second;
    }
    else
    {
      logentry = "not mapped";
      LOG(logentry, LogType::debug);
      return 0;
    } 
  }
   
  void run_thread_safe(TRunnable & runnable)
  {
    const std::lock_guard<std::mutex> lock(run_thread_safe_mutex);
    size_t thread_id = std::hash<std::thread::id>()(std::this_thread::get_id());
    runnable.run(thread_set_logical_id(thread_id), logger);
  }

  void run_thread_safe_not(TRunnable & runnable)
  {
    size_t thread_id = std::hash<std::thread::id>()(std::this_thread::get_id());
    runnable.run(thread_set_logical_id(thread_id), logger);
  }
 
private:
  TLogger & logger;
  //
  size_t last_logical_thread_id;
  std::map<size_t, size_t> physical_to_logical_thread_map;
  std::mutex logical_thread_id_mutex;
  //
  std::mutex run_thread_safe_mutex;

};

#endif
