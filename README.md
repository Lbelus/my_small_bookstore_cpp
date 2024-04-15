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

Composants du projet :

- CLI : CLi et Tokenizer réalisé à partir d'un mélange de classes C++, de C et d'ASM;
- Systeme de gestion de la bibliotheque : Repose sur une FACTORY METHOD DESIGN PATTERN suivant les principes RAII;
- UNITESTS : Créés en utilisant le framework "Google Tests";
- Compilation : Le projet peut être compilé en utilisant CMake (simple, avec flags, avec unitest) ou Makefile (simple ou avec flags).

La FACTORY METHOD DESIGN PATTERN est une design pattern qui permet à une classe de déléguer l'instanciation des objets à ses sous-classes. Ce modèle implique une classe "créateur" avec une méthode pour créer des objets et des sous-classes "produit" qui spécifient le type d'objets à créer. Il permet au programme de créer des objets sans spécifier la classe exacte de l'objet qui sera créé.

```
        ┌───────────────────────────┐                                                              
        │Produit p = CreerProduit() │                                                              
        │ p.method()                │                                                              
        └───────┬───────────────────┘                                                              
                │                                                                                  
                │      ┌─────────────────────────┐               ┌──────────────────┐              
                │      │                         │               │                  │              
                │      │      Createur           │               │   Interface      │              
                │      ├─────────────────────────┼──────────────►│    Produit       │              
                └──────┤ ...                     │               ├──────────────────┤              
                       ├─────────────────────────┤               │  +method()       │              
                       │  +operation()           │               └─────────▲────────┘              
                       │  +CreerProduit():produit│                         │                       
                       └─────────────▲───────────┘                         │                       
                                     │                           ┌─────────┴─────────┐             
                 ┌───────────────────┴──┐                        │                   │             
                 │                      │                        │                   │             
       ┌─────────┴──────┐       ┌───────┴────────┐        ┌──────┴─────┐      ┌──────┴────┐        
       │CreateurConcretA│       │CreateurConcretB│        │ Produit    │      │ Produit   │        
       ├────────────────┤       ├────────────────┤        │  ConcretA  │      │  ConcretB │        
       │...             │       │...             │        └────────────┘      └───────────┘        
       ├────────────────┤       ├────────────────┤                                                 
       │+CreerProduit():│       │+CreerProduit():│                                                 
       │ produit        │       │ produit        │                                                 
       └────────┬───────┘       └────────────────┘                                                 
                │                                                                                  
      ┌─────────┴──────────────────┐                                                               
      │return new ProduitConcretA()│                                                               
      └────────────────────────────┘                                                               
                                                                                                   
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


## Setup rapide 
Depuis le dir ``racine`` du projet.

Avec Docker, construire et creer l'image:
```bash
docker build -t img_th_ran .
docker run -it -v /pathToDir/:/workspace/ --name cont_th_ran img_th_ran /bin/bash
```


Compiler et tester le projet avec CMake: 
```bash
bash scripts/sc_unitest.sh
cat build/GoogleTestLog.log
```
ou avec Makefile:
```bash
make
cat tests/test01.txt | ./thRandCli
```


## Usage

Saisir les commandes suivantes depuis la CLI

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



## Instruction avec detail:

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
