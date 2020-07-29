# Autocorrect
A lightweight, fast and stable CLI autocorrect from a dictionary of words and their frequency

## Prerequisites
Make sure to have:
- `CMake` ([installation guide](https://cmake.org/install/))
- `Doxygen` 1.18 or above ([installation guide](https://www.doxygen.nl/manual/install.html))

## Installation
- Create a `build` directory and move into it
``` sh
sh$ mkdir build
sh$ cd build
```
- Generate the Makefile with `CMake`
``` sh
sh$ cmake ..
```
- Generate the two binaries `TextMiningCompiler` and `TextMiningApp` in the root directory and go back to it
``` sh
sh$ make
sh$ cd ..
```

## Usage
- Create the dictionary of words:
``` sh
./TextMiningCompiler /path/to/words.txt /path/to/dict.bin
```
- Find all words at a distance 0, 1, 2 of `test`:
``` sh
sh$ echo "approx 0 test" | ./TextMiningApp /path/to/dict.bin
...
sh$ echo "approx 1 test" | ./TextMiningApp /path/to/dict.bin
...
sh$ echo "approx 2 test" | ./TextMiningApp /path/to/dict.bin
...
```
- The same as before but in a singe command:
``` sh
sh$ echo "approx 0 test\napprox 1 test\napprox 2 test" | ./TextMiningApp path/to/dict.bin
```
- Using the output of a cat command:
``` sh
sh$ cat test.txt | ./TextMininApp /path/to/dict.bin
```
- Run the testsuite:
``` sh
sh$ cd build
sh$ make check
[ 57%] Built target TextMiningCompiler
[100%] Built target TextMiningApp
Please choose your os: [osx / linux64]
linux64
[INFO] Compiling words.txt...
[INFO] REF compiling words.txt...
approx 1 prison
>> [SUCCESS]
...
```
- Generate the documentation and display it in browser
``` sh
sh$ cd build
sh$ make doc
...
sh$ cd ../doc
sh$ firefox html/index.html
...
```

## Q&A?

### The architecture ?

### Testing ?

### Avez-vous détecté des cas où la correction par distance ne fonctionnait pas (même avec une distance élevée) ?

### Data structure
Trie ou Patricia trie
PK ? ..

### Proposez un réglage automatique de la distance pour un programme qui prend juste une chaîne de caractères en entrée, donner le processus d’évaluation ainsi que les résultats

### Improving the preformance ?

### Que manque-t-il à votre correcteur orthographique pour qu’il soit à l’état de l’art ?
