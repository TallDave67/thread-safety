#!/bin/sh
export CC=/usr/bin/clang-11
export CXX=/usr/bin/clang++-11
cmake -DCMAKE_USER_MAKE_RULES_OVERRIDE=./ClangOverrides.txt -D_CMAKE_TOOLCHAIN_PREFIX=llvm- ../
