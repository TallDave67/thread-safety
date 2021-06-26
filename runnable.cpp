//runnable.cpp
#include "runnable.h"
#include <string>
#include <algorithm>
#include <fstream>
#include "logger-log-type.h"
#include "logger-call.h"

Runnable::Runnable(std::shared_ptr< std::vector<size_t> > _p) : p(_p) {}
Runnable::~Runnable() {}
  
void Runnable::run(size_t logical_thread_id, Logger & logger)
{
  std::string logentry = "start thread " + std::to_string(logical_thread_id);
  LOG(logentry, LogType::info);
  for(size_t i = 0; i < num_partitions; i++)
  {
    p->push_back(logical_thread_id*partition_size + i);
  }
  file_out(logical_thread_id);
  for(size_t i = 0; i < num_partitions; i++)
  {
    p->push_back(logical_thread_id*partition_size + num_partitions + i);
  }
  vec_out(logical_thread_id, *p, logger);
}

void Runnable::file_out(size_t logical_thread_id)
{
  std::string logical_thread_id_as_string = std::to_string( logical_thread_id );
  std::string filename = "file_for_thread" + logical_thread_id_as_string + ".txt";
  std::ofstream thread_file;
  thread_file.open (filename);
  thread_file << "This is a summary of thread " << logical_thread_id_as_string << ".\n";
  thread_file.close();
}

void Runnable::vec_out(size_t logical_thread_id, std::vector<size_t> & vec, Logger & logger)
{
  std::string logentry = "results for thread " + std::to_string(logical_thread_id) + "\n";
  auto append = [&logentry](size_t val) { const std::string logitem = " " + std::to_string(val); logentry += logitem; };
  std::for_each(vec.begin(), vec.end(), append);
  LOG(logentry, LogType::info);
}
