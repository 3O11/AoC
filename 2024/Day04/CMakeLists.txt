add_executable(2024D04 "Main.cpp")

target_compile_features(2024D04
    PRIVATE
    cxx_std_23
)

target_link_libraries(2024D04
    PRIVATE
    AoC_2024_Common
)
