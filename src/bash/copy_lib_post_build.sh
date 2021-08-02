#!/bin/bash

DIR="$(cd "$(dirname "$0")" && pwd)"
echo "Running from $DIR..."

BUILD_DIR="./cmake-build-debug"
LIB_NAME="libbumblestack.so"
PY_DIR="./src/python/"

echo "Changing directory..."
cd ../..

cp $BUILD_DIR/$LIB_NAME $PY_DIR
echo "$LIB_NAME copied!"
