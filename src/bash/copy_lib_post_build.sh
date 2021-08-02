#!/bin/bash

BUILD_DIR="./cmake-build-debug"
LIB_NAME="libbumblestack.so"
PY_DIR="./src/python/"

echo "Hello!"
cp $BUILD_DIR/$LIB_NAME PY_DIR
