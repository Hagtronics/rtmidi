cmake_minimum_required(VERSION 3.0)
project(myMidi)
add_executable(${PROJECT_NAME} myMidi.cpp)
target_link_libraries(${PROJECT_NAME} rtmidi)