include(${PROJECT_SOURCE_DIR}/CMake/cpr.cmake)

add_library(AoC_2024_Common STATIC)

target_compile_features(AoC_2024_Common
    PRIVATE
    cxx_std_23
)

target_link_libraries(AoC_2024_Common
    PRIVATE
    cpr::cpr
)

target_include_directories(AoC_2024_Common
    PUBLIC
    "Include"
)

target_sources(AoC_2024_Common
    PRIVATE
    "Source/InputGetter.cpp"
)
