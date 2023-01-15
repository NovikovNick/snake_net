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

add_custom_command(TARGET SnakeNet POST_BUILD

	COMMAND  ${CMAKE_COMMAND} -E copy_if_different
	         ${CMAKE_CURRENT_SOURCE_DIR}/extern/ggpo/build/bin/x64/${CMAKE_BUILD_TYPE}/GGPO.dll
	         ${CMAKE_CURRENT_SOURCE_DIR}/out/build/x64-${CMAKE_BUILD_TYPE}
)

add_custom_command(TARGET SnakeNet POST_BUILD

	COMMAND  ${CMAKE_COMMAND} -E copy_if_different
	         ${CMAKE_CURRENT_SOURCE_DIR}/extern/ggpo/build/bin/x64/${CMAKE_BUILD_TYPE}/GGPO.pdb
	         ${CMAKE_CURRENT_SOURCE_DIR}/out/build/x64-${CMAKE_BUILD_TYPE}
)
