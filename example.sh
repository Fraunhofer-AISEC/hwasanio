#!/usr/bin/env bash

set -ue

cd example
mkdir -p build

../hwasanio-llvm-project/build/bin/clang -fsanitize=hwaddress -fuse-ld=lld test-hwasanio.c -o build/test-hwasanio

# Run binary
echo "## Executing binary with intra-object violation ##"
./build/test-hwasanio 0