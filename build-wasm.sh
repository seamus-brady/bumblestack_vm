#!/bin/sh

# set emscripten env
cd ~/bin/emsdk/
sh emsdk_env.sh

# create the wasm
emcc ~/GitHub/bumblestack-repos/bumblestack/src/c/*.c \
-I~/GitHub/bumblestack-repos/bumblestack/src/c/gravity/compiler  \
-I~/GitHub/bumblestack-repos/bumblestack/src/c/gravity/optionals \
-I~/GitHub/bumblestack-repos/bumblestack/src/c/gravity/runtime \
-I~/GitHub/bumblestack-repos/bumblestack/src/c/gravity/shared \
-I~/GitHub/bumblestack-repos/bumblestack/src/c/gravity/utils \
-s TOTAL_MEMORY=1024MB \
-o ~/GitHub/bumblestack-repos/bumblestack/wasm-build/bumblestack.html \
-s ERROR_ON_UNDEFINED_SYMBOLS=0 \
-s EXPORTED_FUNCTIONS="['_main']" \
-s EXPORTED_RUNTIME_METHODS=["cwrap"] \
-Os --closure 1 \
-v