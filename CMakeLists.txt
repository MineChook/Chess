cmake_minimum_required(VERSION 3.20)
project(ChessAnalysis)

set(LIB_DIR "${CMAKE_SOURCE_DIR}/Dependencies")

add_library(glad ${LIB_DIR}/Glad/src/glad.c)
target_include_directories(glad PUBLIC ${LIB_DIR}/Glad/include)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# macOS: build for Apple Silicon
if(APPLE)
    set(CMAKE_OSX_ARCHITECTURES "arm64" CACHE STRING "Build architectures for macOS" FORCE)
endif()

add_executable(ChessAnalysis src/Main.cpp
        src/game/Game.cpp
        src/game/Game.h
        src/game/GameState.cpp
        src/game/calculations/Engine.cpp
        src/game/helpers/ChessPosition.cpp
        src/game/helpers/ChessPosition.h
        src/game/helpers/Color.h
        src/game/calculations/Engine.h
        src/game/helpers/BitboardHelpers.h
        src/resources/shader/Shaders.h
        src/resources/shader/Shaders.cpp
        src/game/helpers/Move.cpp
        src/game/helpers/Move.h
)

# Fetch and build GLFW cross-platform
include(FetchContent)
FetchContent_Declare(
  glfw
  GIT_REPOSITORY https://github.com/glfw/glfw.git
  GIT_TAG 3.4
)
FetchContent_Declare(
        spdlog
        GIT_REPOSITORY https://github.com/gabime/spdlog.git
        GIT_TAG v1.13.0 # Use desired version
)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(glfw)
FetchContent_MakeAvailable(spdlog)

# OpenGL (for glClear, etc.)
find_package(OpenGL REQUIRED)

# Ensure GLFW does not include system OpenGL headers (so it won't clash with glad)
target_compile_definitions(ChessAnalysis PRIVATE GLFW_INCLUDE_NONE)

# Link: GLFW carries platform deps; OpenGL is imported target
# Link glad as well (no code changes required in Main.cpp)
target_link_libraries(ChessAnalysis PRIVATE glfw OpenGL::GL glad)
target_link_libraries(ChessAnalysis PRIVATE spdlog::spdlog)

# Provide the source directory to the app so it can find resources at runtime
# This avoids issues with relative paths when running from a build directory
if (APPLE OR UNIX OR WIN32)
    target_compile_definitions(ChessAnalysis PRIVATE PROJECT_SOURCE_DIR="${CMAKE_SOURCE_DIR}")
endif()

# Include GLFW headers for better IDE support
target_include_directories(ChessAnalysis PRIVATE 
    ${glfw_SOURCE_DIR}/include
    ${spdlog_SOURCE_DIR}/include
)
