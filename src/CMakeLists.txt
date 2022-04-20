add_library(VisualizerLib STATIC utils.cpp queues.cpp pushswap.cpp gui.cpp)

target_link_libraries(VisualizerLib PUBLIC ImGui-SFML::ImGui-SFML)
target_include_directories(VisualizerLib PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../include")
target_compile_features(VisualizerLib PRIVATE cxx_std_17)
target_compile_options(VisualizerLib PRIVATE
$<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
$<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic -Werror>
)

add_executable(visualizer main.cpp)
target_compile_features(visualizer PRIVATE cxx_std_17)
target_link_libraries(visualizer PRIVATE VisualizerLib)
