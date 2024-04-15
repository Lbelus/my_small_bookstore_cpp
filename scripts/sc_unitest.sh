rm -r build/
cmake -S . -B build -DENABLE_GTEST=ON
cmake --build build
cd build && ctest