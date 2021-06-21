#!/bin/sh

EMSDK_ROOT=lib/emsdk
SRC_ROOT=src/vm
WASM_BUILD_ROOT=./wasm-build

# set emscripten env
cd $EMSDK_ROOT
. ./emsdk_env.sh
cd ../..
pwd

# create the wasm
emcc $SRC_ROOT/*.c  -s TOTAL_MEMORY=1024MB \
-o $WASM_BUILD_ROOT/bumblestack.html \
-s ERROR_ON_UNDEFINED_SYMBOLS=0 \
-s EXPORTED_FUNCTIONS="['_main']" \
-s EXPORTED_RUNTIME_METHODS=["cwrap"] \
-Oz --closure 1 \
-v