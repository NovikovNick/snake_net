cmake_minimum_required (VERSION 3.8)

project ("SnakeNet")

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(extern/GGPO)

file(GLOB SNAKE_SRC "./src/*.h" "./src/*.cpp")

include_directories(
	./src/
)

# Change the character set to unicode.
add_definitions(-D_UNICODE -DUNICODE)

add_executable(SnakeNet WIN32 ${SNAKE_SRC})
target_link_libraries(SnakeNet LINK_PUBLIC winmm.lib ws2_32.lib)
target_link_libraries(SnakeNet PRIVATE GGPO)
#target_compile_options(SnakeNet PRIVATE "/W4" "/WX")
