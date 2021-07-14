cmake_minimum_required(VERSION 3.20)
project(c-python)

find_package(PythonLibs 3.9 REQUIRED)
find_package(PythonInterp 3.9 REQUIRED)

# Libraries
add_executable(c-python
	src/main.cpp
)

target_include_directories(c-python PUBLIC
	$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
	$<INSTALL_INTERFACE:include>
)
target_link_libraries(c-python ${PYTHON_LIBRARIES})
target_include_directories(c-python PRIVATE ${PYTHON_INCLUDE_DIR})
target_compile_features(c-python PUBLIC cxx_std_17)
