#!/bin/sh

# set emscripten env
cd ~/bin/emsdk/
sh emsdk_env.sh

# create the wasm
emcc ~/GitHub/bumblestack-repos/bumblestack/src/c/*.c  -s TOTAL_MEMORY=1024MB \
-o ~/GitHub/bumblestack-repos/bumblestack/wasm-build/bumblestack.html \
-s ERROR_ON_UNDEFINED_SYMBOLS=0 \
-s EXPORTED_FUNCTIONS="['_main']" \
-s EXPORTED_RUNTIME_METHODS=["cwrap"] \
-Os --closure 1 \
-v