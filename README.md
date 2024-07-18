# my_small_bookstore_cpp
***

## Task

#### Test objectives
Develop a CLI in C++ that allows the management of a library containing books, comics, and their authors.

#### Goal
You will be able to:
- Add a book;
- Add an author;
- Search for the author of a given book;
- Search for the books of a given author;


To achieve this, the following C++ concepts should be prioritized: :
- Classes and inheritance;
- STL algorithms;
- STL containers;

#### Deliverable
Only the source code needs to be provided, not the executable.

## Description

Project components :

- CLI: Command Line Interface and Tokenizer implemented using a mix of C++ classes, C, and Assembly language;
- Library Management System: Based on a Factory Method Design Pattern following the RAII (Resource Acquisition Is Initialization) principles;
- UNITESTS : Created using the "Google Tests" framework;
- Compilation : The project can be compiled using CMake (simple, with flags, with unit tests) or Makefile (simple or with flags);

The Factory Method Design Pattern is a design pattern that allows a class to delegate the instantiation of objects to its subclasses. This pattern involves a "creator" class with a method for creating objects and "product" subclasses that specify the type of objects to be created. It allows the program to create objects without specifying the exact class of the object that will be created.

```scss
        ┌────────────────────────────┐                                                              
        │ Product p = CreateProduct()│                                                              
        │ p.method()                 │                                                              
        └───────┬────────────────────┘                                                              
                │                                                                                  
                │      ┌─────────────────────────┐               ┌──────────────────┐              
                │      │                         │               │                  │              
                │      │       Creator           │               │    Product       │              
                │      ├─────────────────────────┼──────────────►│    Interface     │              
                └──────┤ ...                     │               ├──────────────────┤              
                       ├─────────────────────────┤               │  +method()       │              
                       │ +operation()            │               └─────────▲────────┘              
                       │ +CreateProduct():product│                         │                       
                       └─────────────▲───────────┘                         │                       
                                     │                           ┌─────────┴─────────┐             
                 ┌───────────────────┴──┐                        │                   │             
                 │                      │                        │                   │             
       ┌─────────┴──────┐       ┌───────┴────────┐        ┌──────┴─────┐      ┌──────┴────┐        
       │ConcreteCreatorA│       │ConcreteCreatorB│        │ Product    │      │ Product   │        
       ├────────────────┤       ├────────────────┤        │ ConcreteA  │      │ ConcreteB │        
       │...             │       │...             │        └────────────┘      └───────────┘        
       ├────────────────┤       ├────────────────┤                                                 
       │+CreateProduct()│       │+CreateProduct()│                                                 
       │ :product       │       │ :product       │                                                 
       └────────┬───────┘       └────────────────┘                                                 
                │                                                                                  
      ┌─────────┴───────────────────┐                                                               
      │return new ConcreteProductA()│                                                               
      └─────────────────────────────┘                                                               

```

BNF:
```md 
<command>       ::= <add-command> | <list-command> | <find-command> | <rm-command> | <quit-command>

<add-command>   ::= "ADD" <SP> <type> <SP> <content> <CRLF>
<list-command>  ::= "LIST" <SP> <list-type> <CRLF>
<find-command>  ::= "FIND" <SP> <find-type> <SP> <title> | "FIND" <SP> <find-type> <SP> <author> <CRLF>
<rm-command>    ::= "RM" <SP> <list-type> <SP> <title> <SP> <author> | "RM" <SP> <list-type> <SP> <author> <CRLF>
<quit-command>  ::= "QUIT"

<type>          ::= "bd" | "livre" | "auteur"
<list-type>     ::= "books" | "auteurs"
<find-type>     ::= "books" | "auteurs"

<content>       ::= <title> <SP> <author> <SP> [<illustrator> | <pages>] | <author>

<title>         ::= '"' <string> '"'
<author>        ::= '"' <string> '"'
<illustrator>   ::= '"' <string> '"'
<pages>         ::= '"' <digit> '"'
<string>        ::= <char> { <char> }
<char>          ::= "a" | "b" | "c" | ... | "z" | "A" | "B" | "C" | ... | "Z" | <space> | other char
<digit>         ::= "0" | "1" | "2" | "3" | "4" | "5" | "6" | "7" | "8" | "9"
<SP>            ::= " "  
<CRLF>          ::= "\n"
```


## Quick Setup 
From the project ``root`` directory.

With Docker, build and create the image:
```bash
docker build -t img_bookshop .
docker run -it -v /pathToDir/:/workspace/ --name cont_bookshop img_bookshop /bin/bash
```


Compile and test the project with CMake:
```bash
bash scripts/sc_unitest.sh
cat build/GoogleTestLog.log
```
or with Makefile:
```bash
make
cat tests/test01.txt | ./thRandCli
```


## Usage

Enter the following commands from the CLI:

```md
ADD bd title author illustrator -> ADD bd "Lanfeust de Troy" "Christophe Arleston" "Didier Tarquin"
ADD livre title author pages    -> ADD livre "Bel-Ami" "Guy de Maupassant" "267"
ADD auteur author               -> ADD "Peyo"
LIST books                      -> LIST books
LIST auteur                     -> LIST auteur
FIND auteur title               -> FIND auteur "Lanfeust de Troy"
FIND books author               -> FIND books "Guy de Maupassant"
RM books title author           -> RM books "Bel-Ami" "Guy de Maupassant"
RM auteur author                -> RM auteur "Peyo"
QUIT                            -> QUIT
```



## Detailled instruction:

### Step 1. setup the Environment.
Using docker, from the ``project root`` dir.
- Build the image:
```bash
docker build -t img_th_ran .
```


- Run the container:
```bash
docker run -it -v /pathToDir/:/workspace/ --name cont_bookshop img_bookshop /bin/bash
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

### Step 3. Build and run some unitest

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
