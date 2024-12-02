include(${PROJECT_SOURCE_DIR}/CMake/cpr.cmake)

add_executable(2024D03 "Main.cpp")

target_compile_features(2024D03
    PRIVATE
    cxx_std_23
)

target_link_libraries(2024D03
    PRIVATE
    AoC_2024_Common
)
