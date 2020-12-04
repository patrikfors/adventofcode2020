add_library(common INTERFACE)
target_compile_features(common INTERFACE c_std_11)
target_compile_features(common INTERFACE cxx_std_17)
target_compile_options(common INTERFACE -Wall)

add_executable(day1 day1.cpp input.cpp)
target_link_libraries(day1 
    PRIVATE
        fmt::fmt
        absl::flags
        absl::flags_parse
        spdlog::spdlog)

add_executable(day2 day2.cpp input.cpp)
target_link_libraries(day2 
    PRIVATE
        fmt::fmt
        absl::flags
        absl::flags_parse
        spdlog::spdlog)

add_executable(day3 day3.cpp input.cpp)
target_link_libraries(day3
    PRIVATE
        fmt::fmt
        absl::flags
        absl::flags_parse
        spdlog::spdlog)       


add_executable(day4 day4.cpp input.cpp)
target_link_libraries(day4
    PRIVATE
        fmt::fmt
        absl::flags
        absl::flags_parse
        spdlog::spdlog)       
