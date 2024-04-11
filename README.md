# take_home_randstad_01


## Installation

### Step 1. setup the Environment.
Using docker, from the ``project root`` dir.
- Build the image:
```bash
docker build -t img_th_ran .
```


- Run the container:
```bash
docker run -it -v /pathToDir/:/workspace/ --name cont_th_ran img_th_ran /bin/bash
```

### Step 2. Build the CLI and run some manual tests.
from the ``project root`` dir.


#### With CMake:
- Generate the build:
```bash
cmake -S . -B build -DENABLE_GTEST=OFF
```

- Compile:
```bash
cd build && make
```

- Run the program:
```bash
./build/thRandCli
```

#### With Makefile:
- Compile:
```bash
make
```
- Run the program:
```bash
./thRandCli
```

- clean the bin:
```bash
make clean
```