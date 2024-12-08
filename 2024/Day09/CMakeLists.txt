add_executable(2024D09 "Main.cpp")

target_compile_features(2024D09
    PRIVATE
    cxx_std_23
)

target_link_libraries(2024D09
    PRIVATE
    AoC_2024_Common
)
