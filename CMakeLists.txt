cmake_minimum_required(VERSION 3.23.2)
project(ojae VERSION 1.0.0 DESCRIPTION "A modular ASCII engine" HOMEPAGE_URL "https://github.com/Owen-Cochell/ojae" LANGUAGES CXX)

# Define our target and set properties:

add_library(ojae
    src/Demo.cpp
    src/FileHandler.cpp
    src/InputHandler.cpp
    src/TextureHandler.cpp
    src/TextRenderer.cpp
    src/BaseWindow.cpp
    src/Tilemap.cpp
)

target_include_directories(ojae
    PUBLIC
        $<INSTALL_INTERFACE:include/ojae>    
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/ojae>

    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# Find required libraies:

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(nlohmann_json REQUIRED)

target_link_libraries(ojae
    PUBLIC
        nlohmann_json::nlohmann_json
        SDL2::SDL2
        SDL2_image
)

# Set compile options:

target_compile_options(ojae PRIVATE -Wall -Wextra)
target_compile_features(ojae PRIVATE cxx_std_17)

# Add binaries in 'test':

add_subdirectory(tests)
