cmake_minimum_required(VERSION 3.29)
cmake_policy(SET CMP0002 NEW)

project(template)
include(.env.cmake)

# Engine sources
add_subdirectory(${Z0_PROJECT_DIR} external_lib_build)
set(Z0_INCLUDE_DIR ${Z0_PROJECT_DIR}/include)
set(Z0_SHADERS_DIR ${Z0_PROJECT_DIR}/src/z0/shaders)
set(Z0_SHADERS_BUILD_DIR ${Z0_PROJECT_DIR}/shaders)
set(Z0_SHARED_LIB ZeroZero)
set(Z0_LIB "${CMAKE_BINARY_DIR}/external_lib_build/lib${Z0_SHARED_LIB}.dll")

# Project sources
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(SHADERS_DIR ${SRC_DIR}/shaders)
set(SHADERS_BUILD_DIR ${CMAKE_CURRENT_SOURCE_DIR}/shaders)
file(MAKE_DIRECTORY ${SHADERS_BUILD_DIR})

include(FetchContent)
include(cmake/shaders.cmake)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_COMPILE_WARNING_AS_ERROR OFF)
set(CMAKE_CXX_EXTENSIONS OFF)

# compile GLSL shaders
file(GLOB_RECURSE GLSL_SOURCE_FILES
		"${SHADERS_DIR}/*.frag"
		"${SHADERS_DIR}/*.vert"
)
add_shaders(${PROJECT_NAME}_shaders ${SHADERS_BUILD_DIR}/myshaders ${Z0_SHADERS_DIR} ${GLSL_SOURCE_FILES})
add_custom_target(post_build ALL
	COMMAND ${CMAKE_COMMAND} -E echo "Post build step: copying shaders"
	COMMAND ${CMAKE_COMMAND} -E copy_directory ${Z0_SHADERS_BUILD_DIR} ${SHADERS_BUILD_DIR}
	COMMAND ${CMAKE_COMMAND} -E echo "Post build step: copying DLL"
	COMMAND ${CMAKE_COMMAND} -E copy ${Z0_LIB} ${CMAKE_BINARY_DIR}
)

add_executable(${PROJECT_NAME}
		${SRC_DIR}/main.cpp
)
target_sources(${PROJECT_NAME}
	PUBLIC
	FILE_SET CXX_MODULES
	FILES
		${SRC_DIR}/main.cppm
)

add_dependencies(${PROJECT_NAME} ${Z0_SHARED_LIB})
add_dependencies(post_build ${PROJECT_NAME})
target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDE_DIR} ${Z0_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} ${Z0_SHARED_LIB})

if(WIN32)
	set_target_properties(${PROJECT_NAME} PROPERTIES
		WIN32_EXECUTABLE TRUE
	)
endif()

include(cmake/libraries.cmake)
target_link_libraries(${PROJECT_NAME} std-cxx-modules)
