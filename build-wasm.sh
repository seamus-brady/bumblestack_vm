#!/bin/sh

EMSDK_ROOT=~/bin/emsdk
SRC_ROOT=~/GitHub/bumblestack-repos/bumblestack/src/vm
WASM_BUILD_ROOT=~/GitHub/bumblestack-repos/bumblestack/wasm-build

# set emscripten env
cd ~/bin/emsdk
. ./emsdk_env.sh

# create the wasm
emcc $SRC_ROOT/*.c  -s TOTAL_MEMORY=1024MB \
-o $WASM_BUILD_ROOT/bumblestack.html \
-s ERROR_ON_UNDEFINED_SYMBOLS=0 \
-s EXPORTED_FUNCTIONS="['_main']" \
-s EXPORTED_RUNTIME_METHODS=["cwrap"] \
-Oz --closure 1 \
-v