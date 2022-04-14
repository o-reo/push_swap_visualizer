cmake_minimum_required(VERSION 3.16)
project(push_swap_visualizer
  LANGUAGES CXX
  VERSION 1.0
)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(dependencies)
add_subdirectory(src)
add_subdirectory(tests)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/imgui.ini ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/imgui.ini COPYONLY)
