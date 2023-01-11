set(CMAKE_CXX_STANDARD 20)

file(GLOB SNAKE_SRC "*.h" "*.cc")

add_executable(SnakeNet ${SNAKE_SRC})
#target_link_libraries(VectorWar LINK_PUBLIC GGPO winmm.lib ws2_32.lib)
#target_compile_options(VectorWar PRIVATE "/W4" "/WX")