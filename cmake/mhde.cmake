message(STATUS "Fetching MHDE...")
FetchContent_Declare(
    mhde
    GIT_REPOSITORY https://github.com/Jasper1467/mhde.git
    GIT_TAG        582de81626f72fa288582368d9681315ce8c292f
    GIT_PROGRESS   TRUE
)
FetchContent_MakeAvailable(mhde)
