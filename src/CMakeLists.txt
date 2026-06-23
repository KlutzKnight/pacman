find_package(SDL3 REQUIRED)

add_executable(pacman)

target_sources(pacman
  PRIVATE
    main.cpp
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

target_compile_options(pacman
  PRIVATE 
    -Wall
    -Wextra
    -Wpedantic
    -Wconversion
    -Wsign-conversion
    -Wshadow
)

target_link_libraries(pacman PRIVATE SDL3::SDL3)