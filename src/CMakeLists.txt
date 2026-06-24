find_package(SDL3 REQUIRED)
find_package(SDL3_image REQUIRED)

add_executable(pacman)

target_sources(pacman
  PRIVATE
    main.cpp
    Player.cpp
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

target_link_libraries(pacman PRIVATE SDL3::SDL3 SDL3_image::SDL3_image)
target_include_directories(pacman
  PRIVATE
    ${PROJECT_SOURCE_DIR}/include
)