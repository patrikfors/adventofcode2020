add_executable(day1 day1.cpp input.cpp)
target_link_libraries(day1 
    PRIVATE
        fmt::fmt
        absl::flags
        absl::flags_parse
        spdlog::spdlog)
