cmake_minimum_required(VERSION 3.10)
project(process_scheduler_simulator)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

# C++ executable
add_executable(process_scheduler src/main.cpp src/process.cpp src/process_scheduler.cpp src/cli_parser.cpp)

target_include_directories(process_scheduler PUBLIC
    /Users/masoom/Developer/Process Scheduler 2/Process-Scheduler-Simulator/include
)

# Python script - copy to build directory
add_custom_command(TARGET process_scheduler POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/scripts/plot_results.py $<TARGET_FILE_DIR:process_scheduler>
    COMMENT "Copying Python script to build directory"
)
