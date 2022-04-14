include(FetchContent)

FetchContent_Declare(
    sfml
    URL https://github.com/SFML/SFML/releases/download/2.5.1/SFML-2.5.1-sources.zip
)

FetchContent_Declare(
  imgui
  GIT_REPOSITORY https://github.com/ocornut/imgui
  GIT_TAG 35b1148efb839381b84de9290d9caf0b66ad7d03
)

FetchContent_MakeAvailable(imgui)

FetchContent_Declare(
  imgui-sfml
  GIT_REPOSITORY https://github.com/eliasdaler/imgui-sfml
  GIT_TAG 82dc2033e51b8323857c3ae1cf1f458b3a933c35
)

add_subdirectory(imgui-sfml)
add_subdirectory(sfml)

FetchContent_Declare(
  catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v2.13.7
)

add_subdirectory(catch2)
