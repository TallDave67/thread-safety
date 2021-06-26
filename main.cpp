// main.cpp
#include <functional>
#include <thread>
#include <string>
#include "thread-manager.hpp"
#include "runnable.h"
#include "logger.h"
#include "logger-call.h"

int main() {
  Logger logger(LogType::info);
  ThreadManager<Runnable, Logger> thread_manager(logger);
  
  std::string logentry = "starting main thread...";
  LOG(logentry, LogType::info);
  size_t thread_id = std::hash<std::thread::id>()(std::this_thread::get_id());  
  thread_manager.thread_set_logical_id(thread_id);
  
  // threads with safety
  auto p_thread_safe = std::make_shared<std::vector<size_t>>();
  Runnable r1(p_thread_safe);
  Runnable r2(p_thread_safe);
  
  logentry = "starting child threads with safety...";
  LOG(logentry, LogType::info);
  std::thread t1(&ThreadManager<Runnable, Logger>::run_thread_safe, &thread_manager, std::ref(r1));
  std::thread t2(&ThreadManager<Runnable, Logger>::run_thread_safe, &thread_manager, std::ref(r2));
   
  t1.join();
  t2.join();
    
  // threads without safety
  auto p_thread_safe_not = std::make_shared<std::vector<size_t>>();
  Runnable r3(p_thread_safe_not);
  Runnable r4(p_thread_safe_not);
  
  logentry = "starting child threads without safety...";
  LOG(logentry, LogType::info);
  std::thread t3(&ThreadManager<Runnable, Logger>::run_thread_safe_not, &thread_manager, std::ref(r3));
  std::thread t4(&ThreadManager<Runnable, Logger>::run_thread_safe_not, &thread_manager, std::ref(r4));
    
  t3.join();
  t4.join();

  return 0;
}
