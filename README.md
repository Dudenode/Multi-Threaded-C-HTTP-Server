Multi-Threaded C HTTP Server

A high-concurrency, modular HTTP server written in C. This project demonstrates systems programming principles, including thread pooling, mutex synchronization, POSIX signal handling for graceful shutdowns, and memory-safe execution verified by Valgrind.

Core Features
Custom Thread Pool: Handles concurrent client connections efficiently using pthread condition variables and mutex locks.

MIME-Type Routing: Dynamically serves files (.html, .pdf, .jpg) with correct HTTP headers.

Graceful Shutdown: Intercepts SIGINT signals to safely destroy listening sockets, broadcast wake-up signals to sleeping threads, and join all processes to prevent orphaned memory.

Zero Memory Leaks: Strictly profiled with Valgrind to ensure 0 bytes lost across all heap allocations.

Architecture
The codebase is decoupled into modular components:

server.c: Main execution loop, socket initialization, and signal interception.

threadpool.c: Worker thread logic, queue management, and synchronization.

http.c: HTTP request parsing and response generation.

error.c: Variadic error handling and thread-safe termination.

Performance Benchmarking
Load testing was conducted using ApacheBench (ab) with 10,000 requests and 100 concurrent users. The results were visualized using Python (Pandas and Matplotlib).

The thread pool maintains a flat ~1ms response time for the 95th percentile of traffic under sustained load.

Memory Profiling
The server was strictly tested for memory leaks using Valgrind. The graceful shutdown sequence ensures all thread local storage and heap allocations are cleanly freed.

==38179== HEAP SUMMARY:
==38179==     in use at exit: 0 bytes in 0 blocks
==38179==   total heap usage: 9 allocs, 9 frees, 3,200 bytes allocated
==38179== 
==38179== All heap blocks were freed -- no leaks are possible

Build and Run
Requirements:

GCC / Clang

Make

Instructions:

Clone the repository and compile the code:
make

Start the server:
./bin/server

(Optional) Run the functional Python test suite:
python3 tests/test.py
