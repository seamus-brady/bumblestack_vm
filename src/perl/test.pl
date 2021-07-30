use strict;
use warnings FATAL => 'all';

use FFI::Platypus 1.00;

FFI::Platypus
    ->new(
    api => 1,
    lib => '/home/seamus/GitHub/bumblestack-repos/bumblestack_vm/cmake-build-debug/libbumblestack.so')
    ->attach(main =>  ['int', 'char[]']);
main([], 0);
puts("hello world");