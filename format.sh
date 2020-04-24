#!/bin/sh

find engine/include/*/*.h -type f -exec clang-format -i {} \;
find engine/src/*/*.cpp -type f -exec clang-format -i {} \;