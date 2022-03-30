add_library(VisualizerLib STATIC queues.cpp gui.cpp)
target_link_libraries(VisualizerLib PRIVATE ImGui-SFML::ImGui-SFML)
target_include_directories(VisualizerLib PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../include")

add_executable(visualizer main.cpp)
target_link_libraries(visualizer PRIVATE VisualizerLib)
