cmake_minimum_required(VERSION 3.15)

project(YLP LANGUAGES C CXX)

include(FetchContent)
include(cmake/imgui.cmake)
include(cmake/json.cmake)
include(cmake/luajit.cmake)
include(cmake/sol3.cmake)

set(CMAKE_CXX_STANDARD 20)
set(SRC_DIR "${PROJECT_SOURCE_DIR}/src")

file(GLOB LUA_LIB_HEADERS "${SRC_DIR}/core/lua_scripting/libs/*.hpp")
set(LUA_LIB_LOADER "${SRC_DIR}/core/lua_scripting/lib_loader.hpp")

if(EXISTS "${LUA_LIB_LOADER}")
    file(REMOVE "${LUA_LIB_LOADER}")
endif()

file(WRITE "${LUA_LIB_LOADER}" "// CMake auto-generated file\n\n#pragma once\n\n")
foreach(LIB ${LUA_LIB_HEADERS})
    get_filename_component(LIB_NAME "${LIB}" NAME)
    file(APPEND "${LUA_LIB_LOADER}" "#include \"libs/${LIB_NAME}\"\n")
endforeach()

file(GLOB_RECURSE SRC_FILES
    "${SRC_DIR}/**.h"
    "${SRC_DIR}/**.hpp"
    "${SRC_DIR}/**.cpp"
    "${SRC_DIR}/*.rc"
)

add_executable(${PROJECT_NAME} ${SRC_FILES})

message(STATUS "Searching for required package: OpenGL...")
find_package(OpenGL REQUIRED)

message(STATUS "Setting up precompiled headers...")
target_precompile_headers(${PROJECT_NAME} PUBLIC "${SRC_DIR}/common.hpp")

message(STATUS "Setting up include directories...")
target_include_directories(${PROJECT_NAME} PRIVATE
    "${SRC_DIR}"
    "${imgui_SOURCE_DIR}"
	"${luajit_SOURCE_DIR}/src"
    "${luajit_BINARY_DIR}/src"
)

message(STATUS "Setting up linked libraries...")
target_link_libraries(${PROJECT_NAME} PRIVATE
	imgui
	OpenGL::GL
	nlohmann_json::nlohmann_json
	sol2::sol2
	libluajit
)
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

message(STATUS "Adding compile definitions...")
add_compile_definitions(
	"_CRT_SECURE_NO_WARNINGS"
	"NOMINMAX"
	"WIN32_LEAN_AND_MEAN"
)

if (WIN32)
    message(STATUS "Setting up Win32 properties...")
    set_target_properties(${PROJECT_NAME} PROPERTIES WIN32_EXECUTABLE TRUE)
endif()

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(${PROJECT_NAME} PRIVATE DEBUG)
endif()
