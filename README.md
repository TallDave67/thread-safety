# Thread Safety (C++11)

This project demonstrates data modifications that are thread safe and those that are not thread safe in C++20.

Linux distro "Pop!_OS 20.10"

cmake version 3.16.3

Ubuntu clang version 11.0.0-2

## Steps

cd build

./doCmake.sh

make VERBOSE=1

./thread-safety

## History

dates: June 19 - 26, 2021

duration: 16 hours

### Code from Another Developer

These folks helped me along the way.

[cppreference.com - thread](https://en.cppreference.com/w/cpp/thread/thread)

[Thread Id as int](https://stackoverflow.com/questions/7432100/how-to-get-integer-thread-id-in-c11)

[Logging](https://stackoverflow.com/questions/48868895/synchronize-writing-to-log-in-a-multi-threading-process)

## Description

In this program there is 1 main thread that launches two sets of child thread pairs. Each pair shares a vector, and the threads do the same thing:

* Push some elements onto the vector
* Write a summary file
* Push some more elements onto the vector

The first thread pair also shares a mutex whereas the second pair does not.

## Output

Note that thread 1 is the main thread.

As you can see from the output, because the first set of child threads is using a shared mutex to gate access to their shared vector, the 3rd thread waits to make any additions until the 2nd thread is done adding elements to the shared vector.

With the second set of child threads the situation is different as no shared mutex is being used to protect access to the shared vector.  In the output you can see that when the 4th thread does its file IO, the OS context switches over to the 5th thread who is able to add elements to the shared vector before the 4th thread has completed his additions.

2021-06-27 08:30:31: ~/dev/moderncpp/thread-safety/main.cpp(15): main: starting main thread...

2021-06-27 08:30:31: ~/dev/moderncpp/thread-safety/main.cpp(25): main: starting child threads with safety...

2021-06-27 08:30:31: ~/dev/moderncpp/thread-safety/runnable.cpp(15): run: start thread 2

2021-06-27 08:30:31: ~/dev/moderncpp/thread-safety/runnable.cpp(43): vec_out: results for thread 2

> 200 201 202 203 204 205 206 207 208 209
 
2021-06-27 08:30:31: ~/dev/moderncpp/thread-safety/runnable.cpp(15): run: start thread 3

2021-06-27 08:30:31: ~/dev/moderncpp/thread-safety/runnable.cpp(43): vec_out: results for thread 3

> 200 201 202 203 204 205 206 207 208 209 300 301 302 303 304 305 306 307 308 309
 
2021-06-27 08:30:31: ~/dev/moderncpp/thread-safety/main.cpp(38): main: starting child threads without safety...

2021-06-27 08:30:31: ~/dev/moderncpp/thread-safety/runnable.cpp(15): run: start thread 4

2021-06-27 08:30:31: ~/dev/moderncpp/thread-safety/runnable.cpp(15): run: start thread 5

2021-06-27 08:30:31: ~/dev/moderncpp/thread-safety/runnable.cpp(43): vec_out: results for thread 4

> 400 401 402 403 404 500 501 502 503 504 405 406 407 408 409
 
2021-06-27 08:30:31: ~/dev/moderncpp/thread-safety/runnable.cpp(43): vec_out: results for thread 5

> 400 401 402 403 404 500 501 502 503 504 405 406 407 408 409 505 506 507 508 509

