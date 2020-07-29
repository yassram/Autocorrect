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

## Authors
- Yassir Ramdani: yassir.ramdani@epita.fr
- Mamoune El Habbari: mamoune.el-habbari@epita.fr

## Q&A?

### Design Choice
The project can be divided into two distinct parts: the compiler and the app.
For the compiler part, we chose to use a classic Trie data structure to rearrange the word dictionary. The compiler does only one thing: from a dictionary file, it extracts all the words as well as their frequencies and then it inserts them into the Trie. This Trie is then compiled into a binary file where instead of pointers we use offsets that indicate where a subtrie ends. for every node of the Trie, four pieces of information are coded into the binary file: the value of the node, the frequency of the word (if a word is formed), the number of children and the offset to the next node. In the binary file, the children of a node are situated just after it.
As for the app, the binary file is set up into a stream and we extract the information we compiled. Given a word and a distance, we run through the file and determine which words may or may not be retained using the Damerau-Levenshtein algorithm. This words are then displayed in the standard output in a JSON format.

### Testing
We created a testsuite that we added to the project. It does a simple diff between the output of the ref and the output of our own program.
On top of that we tested that the app does not use more than 512MB of RAM as well as tested how long the compilation takes and how long it takes to compute the approximate matches of the requested word and it turns out that our program is faster than the ref.

### Cases where distance-based spell checking does not work
There are cases where the correct words do not exist in our dictionary and thus obviously cannot be suggested by the program.
There are also cases where the correct words sound the same phonetically but are written substantially differently and so even with a high distance they are not detected.

### Data Structure
In this project we used a Trie data structure. We chose a classic Trie instead of a Patricia Trie because it was easier to manipulate, easier to implement and it allowed us to focus our effort into the App.

### Automatic Distance Setting
If we consider very short words with for example 2 our 3 letters, it would make very little sense to choose a distance of 3. Obviously, the distance should be based on the number of letters in the word. A good distance would be: distance = floor(len(word) / 3)

### Improving Performance
When it comes to the app, we have pretty good performances since we measured faster timings than the ref.
However there are still several areas we could be improving on. First, using a more compact data structure such as a Patricia Tree would greatly improve resource usage. Furthermore, We can also think about parallelizing seeing as how a tree data structure can be divided into its branches. Finally, some branches are not worth checking when you compare its length to the length of the word we are currently checking.

### A State-Of-The-Art Spell Checker
A state-of-the-art spell checker does many things that our program does not:
- taking into account keyboard mistakes
- taking into account accents
- taking into account grammar errors
- taking into account phonetical errors
