
add_executable(tests test_queues.cpp)
target_link_libraries(tests PRIVATE Catch2::Catch2 VisualizerLib)
target_include_directories(tests PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
