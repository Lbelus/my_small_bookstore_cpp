rm -r build/
cmake -S . -B build -DENABLE_CFLAGS=ON
cd build && make