cmake_minimum_required (VERSION 3.8)

project ("SnakeNet")

set(CMAKE_CXX_STANDARD 20)

# Boost
set(BOOST_ROOT "C:\\local\\boost_1_80_0")
find_package(Boost REQUIRED COMPONENTS unit_test_framework)
add_definitions( -DBOOST_ALL_NO_LIB )
add_definitions( -DBOOST_ALL_DYN_LINK )
   
include_directories(${Boost_INCLUDE_DIRS})

# GGPO
set(GGPO_BINARY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/extern/ggpo/build/bin/x64/Release)
add_subdirectory(extern/GGPO)

file(GLOB VECTOR_WAR_SRC "./src/*.h" "./src/*.cpp")
file(GLOB SNAKE_SRC "./src/v2/*.h" "./src/v2/*.cc")

include_directories(
	./src/
	./src/v2/
)

# Change the character set to unicode.
add_definitions(-D_UNICODE -DUNICODE)

# unit tests
add_executable(grid_cell_unit_test "test/grid_cell.cc" ${SNAKE_SRC})
target_include_directories(grid_cell_unit_test PRIVATE Boost::unit_test_framework)

add_executable(game_state_unit_test "test/game_state.cc" ${SNAKE_SRC})
target_include_directories(game_state_unit_test PRIVATE Boost::unit_test_framework)

# bin
add_executable(SnakeNet WIN32 ${VECTOR_WAR_SRC} ${SNAKE_SRC})
target_link_libraries(SnakeNet LINK_PUBLIC winmm.lib ws2_32.lib)
target_link_libraries(SnakeNet PRIVATE GGPO)

add_custom_command(TARGET SnakeNet POST_BUILD
	COMMAND  ${CMAKE_COMMAND} -E copy_if_different ${GGPO_BINARY_DIR}/GGPO.dll ${CMAKE_CURRENT_BINARY_DIR}
)

add_custom_command(TARGET SnakeNet POST_BUILD
	COMMAND  ${CMAKE_COMMAND} -E copy_if_different ${GGPO_BINARY_DIR}/GGPO.pdb ${CMAKE_CURRENT_BINARY_DIR}
)

