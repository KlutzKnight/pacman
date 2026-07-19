set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(SDL3 REQUIRED)
find_package(SDL3_image REQUIRED)

add_executable(pacman)

target_sources(pacman
  PRIVATE
    main.cpp
    game/Game.cpp
    core/AssetManager.cpp
    entities/Entity.cpp
    entities/Player.cpp
    entities/Ghost.cpp
    game/Map.cpp
    game/Navigation.cpp
)

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
    ${PROJECT_SOURCE_DIR}/include/core
    ${PROJECT_SOURCE_DIR}/include/entities
    ${PROJECT_SOURCE_DIR}/include/game
)
