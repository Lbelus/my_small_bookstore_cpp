# take_home_randstad_01
***

## Task

#### Objectif du test
Développer une application console en C++ permettant la gestion d’une bibliothèque contenant des livres, des BDs
et leurs auteurs.

#### Mission
En saisie dans la console, il sera possible :
- D’ajouter un livre
- D’ajouter un auteur
- De rechercher l’auteur d’un livre donné
- De rechercher les livres d’un auteur donné


Pour se faire il faut privilégier l’usage des notions
C++ suivantes :
- Classes et héritage
- Algorithmes STL
- Conteneurs STL


#### Livrable
Seul le code source est à fournir, pas l’exécutable.

## Description

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

### Step 2. Build and run the program
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
or
```bash
cat tests/test01.txt | ./thRandCli
```

- Clean the bin:
```bash
make clean
```

### Step 3. Build and some unitest

#### With CMake:

From the ``project root`` dir.
- Generate the build:
```bash
cmake -S . -B build -DENABLE_GTEST=ON
```

- Compile:
```bash
cmake --build build
```
- Run the tests:
```bash
cd build && ctest
```

- Consult the test logs: 

```bash
cat build/GoogleTestLog.log
```
