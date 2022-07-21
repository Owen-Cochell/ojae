# Add final binary:

add_executable(ojae-test main.cpp)

target_link_libraries(ojae-test ojae)

# Set compile options:

target_compile_options(ojae PRIVATE -Wall -Wextra)
target_compile_features(ojae-test PRIVATE cxx_std_17)
