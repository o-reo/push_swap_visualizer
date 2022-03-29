add_executable(visualizer main.cpp queues.cpp gui.cpp)
target_link_libraries(visualizer PRIVATE ImGui-SFML::ImGui-SFML)
