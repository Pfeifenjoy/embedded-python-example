cmake_minimum_required(VERSION 3.20)
project(c-python)

# Libraries
add_executable(c-python
	src/main.cpp
)

target_include_directories(c-python PUBLIC
	$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
	$<INSTALL_INTERFACE:include>
)
target_compile_features(c-python PUBLIC cxx_std_17)
