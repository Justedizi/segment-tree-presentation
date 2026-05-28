cmake_minimum_required(VERSION 3.14)
project(SegmentTreeKadane CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 1. Tworzymy lokalną bibliotekę z pliku .cpp
add_library(segment_tree_lib src/segment_tree.cpp)

# 2. Twój główny program
add_executable(segment_tree_main src/main.cpp)
target_link_libraries(segment_tree_main PRIVATE segment_tree_lib)

# --- KONFIGURACJA GOOGLE BENCHMARK ---
include(FetchContent)
FetchContent_Declare(
  googlebenchmark
  GIT_REPOSITORY https://github.com/google/benchmark.git
  GIT_TAG        v1.8.3
)
set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googlebenchmark)

# 3. Program z benchmarkami
add_executable(segment_tree_benchmark src/benchmark.cpp)
# Linkujemy naszą logikę drzewa oraz biblioteki Google Benchmark
target_link_libraries(segment_tree_benchmark PRIVATE segment_tree_lib benchmark::benchmark benchmark::benchmark_main)
