#!/usr/bin/env bash

set -ue

SCRIPT_ROOT="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
LLVM_DIR="${SCRIPT_ROOT}/hwasanio-llvm-project"
BUILD_DIR="${SCRIPT_ROOT}/hwasanio-llvm-project/build"

echo "HWASANIO: Clone LLVM"
git clone https://github.com/Fraunhofer-AISEC/hwasanio-llvm-project.git hwasanio-llvm-project

mkdir -p "$BUILD_DIR"
cd $BUILD_DIR
cmake ../llvm/ -G Ninja -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_BUILD_TYPE=Release -DLLVM_ENABLE_LLD=ON -DLLVM_TARGETS_TO_BUILD='AArch64' -DLLVM_ENABLE_PROJECTS='clang;lld;compiler-rt'
cmake --build .
