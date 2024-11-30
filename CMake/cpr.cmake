if(NOT TARGET cpr::cpr)
    include(FetchContent)

    FetchContent_Declare(
        cpr
        GIT_REPOSITORY https://github.com/libcpr/cpr.git
        GIT_TAG        1.11.1
    )

    set(USE_LIBIDN2 OFF CACHE BOOL "" FORCE)
    set(BUILD_SHARED_LIBS OFF)

    FetchContent_MakeAvailable(
        cpr
    )
endif()
