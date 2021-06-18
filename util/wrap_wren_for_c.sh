#!/bin/sh

SCRIPT_ROOT=~/GitHub/bumblestack-repos/bumblestack/src/scripts
SRC_ROOT=~/GitHub/bumblestack-repos/bumblestack/src/vm

# wrap the json class in a c string in an include file
python ./util/wren_to_c_string.py  $SRC_ROOT/wren_json.inc $SCRIPT_ROOT/json.wren