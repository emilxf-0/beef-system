cmake_minimum_required(VERSION 3.10)

project(BeefSystem)

find_package(SDL2 CONFIG REQUIRED)
find_package(SDL2_image CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)

set(SOURCES 
CharacterEntity.cpp
Collision.cpp
Controller.cpp
Game.cpp
GameObject.cpp
Input.cpp
main.cpp
Map.cpp
TextureManager.cpp
TimerComponent.cpp
TrafficLightEntity.cpp
TraitComponent.cpp
Vector2D.cpp
 "ImportData.cpp")


add_executable(BeefSystem main.cpp ${SOURCES})

target_include_directories(BeefSystem PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")

message(STATUS "MY_VARIABLE=${CMAKE_SOURCE_DIR}")

# Copy the assets to the build directory during build
add_custom_target(copy_assets
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/assets ${CMAKE_BINARY_DIR}/assets
)

# Copy assets before building the main executable
add_custom_command(
    TARGET BeefSystem POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/assets
    $<TARGET_FILE_DIR:BeefSystem>/assets
    DEPENDS copy_assets
)

target_link_libraries(BeefSystem PRIVATE SDL2::SDL2 SDL2::SDL2main SDL2_image::SDL2_image nlohmann_json::nlohmann_json)