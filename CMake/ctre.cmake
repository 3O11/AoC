if(NOT TARGET ctre)
    include(FetchContent)

    FetchContent_Declare(
        ctre
        GIT_REPOSITORY https://github.com/hanickadot/compile-time-regular-expressions
        GIT_TAG        v3.9.0
    )

    FetchContent_MakeAvailable(
        ctre
    )
endif()
