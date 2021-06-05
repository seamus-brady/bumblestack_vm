#!/bin/bash

# you must run the following command first to build the generator after uncommenting CMakeLists.txt:
# cmake CMakeLists.txt

echo "Outputting ruletable.c"
cmake-build-debug/bin/generate > ./src/c/ruletable.c
echo "Done!"