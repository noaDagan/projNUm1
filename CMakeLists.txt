cmake_minimum_required(VERSION 3.12)
project(projectNum2)

set(CMAKE_CXX_FLAGS "-std=c++14 -pthread")
#set(CMAKE_CXX_STANDARD 14)

add_executable(projectNum2 main.cpp Server.h MySerialServer.cpp MySerialServer.h ClientHandler.h MyTestClientHandler.cpp MyTestClientHandler.h Solver.h CacheManager.h FileCacheManager.cpp FileCacheManager.h StringReverse.cpp StringReverse.h Problem.cpp Problem.h Solution.cpp Solution.h State.h "  Searchable.h" Searcher.h)