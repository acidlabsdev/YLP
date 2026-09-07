message(STATUS "Setting up LuaJIT 2.1")
set(LUAJIT_BUILD_TOOL OFF)
set(LUAJIT_FORCE_UTF8_FOPEN ON)

FetchContent_Declare(
    luajit
    GIT_REPOSITORY https://github.com/WohlSoft/LuaJIT.git
    GIT_TAG dfcb8651f12670438fa7bf8f4063c4adf5461f01
    GIT_PROGRESS TRUE
)
FetchContent_MakeAvailable(luajit)

target_compile_definitions(libluajit PRIVATE
    "_CRT_SECURE_NO_WARNINGS"
    "LUAJIT_ENABLE_LUA52COMPAT"
)
