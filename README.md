<p align="center">
  <a href="">
    <img alt="Logo" src="https://brain-labs.github.io/brain-visualizer/img/brain.png" width="100px">
  </a>
</p>

# Brain
[![Build Status](https://travis-ci.org/brain-labs/brain.svg?branch=master)](https://travis-ci.org/brain-labs/brain)

A computer language based on Brainfuck.

## Table of Contents

- [About](#about)
- [Documentation](#documentation)
- [Current Status](#current-status)
- __How to build Brain__
  - [How to build LLVM (Required)](#how-to-build-llvm)
  - [How to install pre-commit(Optional)](#how-to-install-pre-commit)
  - [How to build Brain and compile/run files](#how-to-build-brain-and-run-files)
- [How it has been built](#how-it-has-been-built)
- [Technical Information](#technical-information)
- [Compiler Options](#compiler-options)
- [Applications for real life](#applications-on-real-life)
- [Help the Project](#help)
- [License](#license)

### About
__Brain__ wants to improve the performance of the Brainfuck programming language and extend it as well, as Brainfuck itself has a lack of flexibility and does not perform great control over complex computations. __Brain__ is open to new model represetantion and allows programmers to extend its capability by attaching `LLVM IR` to its code.

One of the main ideas of __Brain__ is saving some operations in machine language, creating an instruction optmizer due to the excess of instructions that Brainfuck would generate. Brain aims to implement it by using current technology __(LLVM)__.

In spite of implementing new commands and features, __Brain__ is **completely compatible** with Brainfuck (but the opposite is not true).

### Documentation

You can check this repository documentation on https://brain-labs.github.io/brain/docs/html/index.html

### Current Status
Brain is stable on its tag [version 1.0](https://github.com/luizperes/brain/blob/v1.0/README.md)

Obs.: To use __Project Status__ (the "Kanban" below), please visit:`https://github.com/luizperes/status-projects/blob/master/README.md` and `http://luizperes.github.io/status-projects/`

| Project Name                        | Status                                    | Technology  | Priority |  Deadline    |
| ----------------------------------- |:-----------------------------------------:| ----------- | :------: |  :--------:  |
| [Brain 1.0](#brain)         | ![Progress](http://progressed.io/bar/100)  | C/C++/LLVM  | Low      |              |
| [Brain 1.1](#brain) | ![Progress](http://progressed.io/bar/0)  | C/C++/LLVM  | Low      |              |

| To Do | In Progress | Done  |
| :---: | :---------: | :---: |
|![PostIt](http://api.ideiadoluiz.com.br/postit/?title=%20%2311&desc=Implement%20Brain%20Commands(@)%20v1.1)|![PostIt](http://api.ideiadoluiz.com.br/postit/?title=%20%239&desc=Implement%20REPL%20v1.1)|![PostIt](http://api.ideiadoluiz.com.br/postit/?title=%20%233&desc=Make%20--debug%20and%20--help%20flags.%20Implement%20input%20files.) ![PostIt](http://api.ideiadoluiz.com.br/postit/?title=%20%232&desc=Implement%20Brainfuck%20commands.)|
|![PostIt](http://api.ideiadoluiz.com.br/postit/?title=%20%2310&desc=Implement%20Command%20(^)%20v.1.1)|| ![PostIt](http://api.ideiadoluiz.com.br/postit/?title=%20%231&desc=Make%20Brainfuck%20compatible%20with%20LLVM.)![PostIt](http://api.ideiadoluiz.com.br/postit/?title=%20%234&desc=Think%20about%20new%20commands.)
|||![PostIt](http://api.ideiadoluiz.com.br/postit/?title=%20%235&desc=Optmize%20generated%20code.%20Include%20-O0%20and%20-O1%20options.)![PostIt](http://api.ideiadoluiz.com.br/postit/?title=%20%236&desc=Implement%20First%20Brain%20Commands%20(*,%20/%20%).)|
|||![PostIt](http://api.ideiadoluiz.com.br/postit/?title=%20%237&desc=Implement%20First%20Brain%20Commands%20({,%20},%20?,%20:,%20;,%20!,%20$).)![PostIt](http://api.ideiadoluiz.com.br/postit/?title=%20%238&desc=Code%20Refactoring.)|

### TODO List
If you want to check the micro TODO list, please see this [issue](https://github.com/luizperes/brain/issues/12).

### How to build LLVM
__Brain__ runs on the top of __LLVM__, thus, you are required to install the lastest versions of LLVM. You can do that by following this http://llvm.org/releases/download.html

### How to install pre-commit
This project uses __pre-commit__ to help us to check our commits in order to minimize bugs and other problems on the project, therefore is strongly recommended that you use it, if you are intending to contribute to the project. For that, you can install by:

if you have `pip` installed:

__Mac__
```
brew install pre-commit
```
__Linux__
```
sudo pip install pre-commit
```
After that, go to where Brain lives:
```
$ cd /path/to/brain
$ pre-commit install
```
More information about that [here](http://pre-commit.com/)

### How to build Brain and run files
To build it, after [installing LLVM](#how-to-build-llvm), execute:
```
$ cd /path/to/brain/src
$ make
```
You can also change the compiler (tested on `g++` and `clang++`) on the `Makefile` inside the `src` directory.

After running `make` on it, you can execute:`./brain your_brain_file.b`. Please check the [current status](#current-status) of the project.

### How it has been built
Brain is based on previous work [https://github.com/luizperes/BrainfuckInterpreter](https://github.com/luizperes/BrainfuckInterpreter) and [https://github.com/Lisapple/BF-Compiler-Tutorial-with-LLVM](https://github.com/Lisapple/BF-Compiler-Tutorial-with-LLVM), now trying to make something more serious: __Turing Complete__, faster, more features/commands and different types.

### Technical Information
Brain is now a Turing Complete language. You can now extend the tape size by using the flag `--size=<tape size>`.

### Commands
__Implemented__
- `>` increment the data pointer (to point to the next cell to the righ.
- `<` decrement the data pointer (to point to the next cell to the left).
- `+` increment (increase by one) the value at the data pointer.
- `-` decrement (decrease by one) the value at the data pointer.
- `.` output the value at the data pointer.
- `,` accept one value of input, storing its value in the value at the data pointer.
- `[` if the value at the data pointer is zero, then instead of moving the instruction pointer forward to the next command, jump it forward to the command after the matching ] command.
- `]` jump to its correspondent [ .
- `*` multiply `*ptr` with `*(ptr-1)`. Store result in *ptr _// format: 2 3 *_
- `/` divide `*ptr` with `*(ptr-1)`. Store the result in *ptr _// format: 2 3 /_
- `%` divide `*ptr` with `*(ptr-1)`. Store the remainder in *ptr _// format: 2 3 %_
- `#` prints out the current debug information.
- `{` (__for__ loop) iterates `'value-at-the-data-pointer' times` and needs to be closed with a matching } command. It __does not decrease__ the `value` at the data pointer. It will __only__ work for positive values.
- `}` jump to its correspondent { .
- `!` (__break__) jumps to the end of a loop (__[ ]__ or __{ }__)
- `?` if the value at the data pointer is `zero` , jumps to the block with `:` or `;` and executes the commands one by one up to its correlative `;`, otherwise, it executes the code until it finds a `:` or `;`.
- `:` it works as an `otherwise` (or `else`) for `?`.
- `;` ends a statement.
- `$` prints out the value at the data pointer **divided** by 100.

__Not Implemented__
- `@` calls a function according to the value at the data pointer.
- `^` move the data pointer (jump) on the tape. _Ex.: ++++++++++^ // the data pointer will jump to cell 10._

Example of the instructions above:

- __if-then__: `? +++ ;` _// if (*ptr) { *ptr += 3; }_
- ___if-else___: `? +++ : --- ;` _// if (*ptr) { *ptr += 3; } else { *ptr -= 3; }_
- __for__: `++++ { commands }` _// makes four iterations 4 through 0 (excluded)_
- __float numbers__: `++>+********$` __cell 0__`[2]` __cell 1__`[256]` _// '$' prints out 256 / 100_
- __break loop__: `+[+++++!]` _// *ptr = 1; while(*ptr) { *ptr += 5; break; }_

### Compiler Options

- `--version`	Shows the current version of Brain
- `--size=<number>`	Sets the number of cells used by the interpreter
- `-emit-llvm`	Emits LLVM IR code for the given input
- `-emit-ast`	Emits the AST for the given input
- `-emit-code`	Emits an optimized code for the given input
- `-v`		Uses verbose mode for the output
- `-O0`		Generates output code with no optmizations
- `-O1`		Optimizes Brain generated output code (Default)

### Applications on real life

  - Artificial Intelligence/ Machine Learning
  - Send commands to Arduino
  - Easy support to primitive processors

### Help
Feel free to send your pull requests. :)

### LICENSE
This project extends [GNU GPL v. 3](http://www.gnu.org/licenses/gpl-3.0.en.html), so be aware of that, regarding copying, modifying and (re)destributing.

