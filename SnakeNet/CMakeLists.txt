set(CMAKE_CXX_STANDARD 20)

file(GLOB SNAKE_SRC "*.h" "*.cc")

# Change the character set to unicode.
add_definitions(-D_UNICODE -DUNICODE)

add_executable(SnakeNet WIN32 ${SNAKE_SRC} "ggpo_perfmon.h")
target_link_libraries(SnakeNet LINK_PUBLIC winmm.lib ws2_32.lib)
#target_compile_options(SnakeNet PRIVATE "/W4" "/WX")