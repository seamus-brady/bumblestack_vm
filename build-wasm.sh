#!/bin/sh

EMSDK_ROOT=lib/emsdk
C_SRC_ROOT=src/vm
WEB_SRC_ROOT=src/web
WASM_BUILD_ROOT=./build/wasm
DIST_ROOT=./build/dist

# set emscripten env
cd $EMSDK_ROOT
. ./emsdk_env.sh
cd ../..

# create the wasm
emcc $C_SRC_ROOT/*.c  -DWASM_ONLY_FUNCTIONALITY_ENABLED \
-s TOTAL_MEMORY=1024MB \
-o $WASM_BUILD_ROOT/bumblevm.html \
-s ERROR_ON_UNDEFINED_SYMBOLS=0 \
-s EXPORTED_FUNCTIONS="['_main']" \
-s EXPORTED_RUNTIME_METHODS=["cwrap"] \
-v
#-Oz --closure 1 \

# copy the files
cp -R $WEB_SRC_ROOT/assets $DIST_ROOT/assets
cp -R $WEB_SRC_ROOT/index.html $DIST_ROOT
cp $WASM_BUILD_ROOT/bumblevm.js $DIST_ROOT/assets
cp $WASM_BUILD_ROOT/bumblevm.wasm $DIST_ROOT/assets