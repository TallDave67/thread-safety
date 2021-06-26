//runnable.h
#ifndef _RUNNABLE_H_
#define _RUNNABLE_H_

#include <vector>
#include <memory>
#include "logger.h"

class Runnable {

public:
  Runnable(std::shared_ptr< std::vector<size_t> > p);
  ~Runnable();
  
  void run(size_t logical_thread_id, Logger & logger);
 
private:
  void file_out(size_t logical_thread_id);
  void vec_out(size_t logical_thread_id, std::vector<size_t> & vec, Logger & logger);
 
private:
  const size_t partition_size = 100;
  const size_t num_partitions = 5;
  std::shared_ptr< std::vector<size_t> > p;
};

#endif
