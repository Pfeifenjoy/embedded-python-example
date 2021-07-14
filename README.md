# Example Embedding Python in C

This small sample project which should demonstrate how you can embed python into C
and exchange send data to the python script.

## Requirements

- C++ Compiler e.g. Clang
- CMake

## Compilation

Run the following commands to run compile the sample.

```
mkdir build
cd build
cmake ..
make
```

## Execution

The sample python program is unser sample/sample.py.
It sums an array of elements. In this case the C++ Program which is unser `src/main.cpp` will
call the sum function of the sample program with an array of doubles.

Run the following command to execute it:

```
./build/c-python sample.sample sum
```
