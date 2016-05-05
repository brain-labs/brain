# Brain
A computer language based on Brainfuck.

### Technical Information
Brain is __not yet__ a Turing Complete language, once I'm limiting the ```memory``` to ```100 * 32 bytes```.

### Current Status
Brain is running just like __Brainfuck__ so far, so feel free to use it... (The final executable final is gonna be giant, because of LLVM).

### How
Brain is based on previous work [https://github.com/luizperes/BrainfuckInterpreter](https://github.com/luizperes/BrainfuckInterpreter) and [https://github.com/Lisapple/BF-Compiler-Tutorial-with-LLVM](https://github.com/Lisapple/BF-Compiler-Tutorial-with-LLVM), now trying to make something more serious: __Turing Complete__, faster, more features/commands and different types. 

### Information
__Brain__ wants to improve the performance of the Brainfuck programming language and extend it as well, as Brainfuck itself has a lack of data types and does not perform great control over variables when you need more than 8 bytes, when you want to make libraries and/or functions, when you want to use different models other than integers and so on.

The main idea of Brain is saving some operations in machine language, creating an instruction optmizer due to the excess of instructions that Brainfuck generates. Brain aims to implement current technology __(LLVM)__, making it easy to port it to different architectures.

In spite of implementing new commands and features, Brain tries to be **completely compatible** with Brainfuck.

### We need a new Brainfuck

We are in 2016, and for this reason, all languages have been updated and programming paradigms have changed in order to meet the necessity of improvement.

In this way, esoteric programmming languagues need to keep up with others! Let's do it!

### LICENSE
This project extends [GNU GPL v. 3](http://www.gnu.org/licenses/gpl-3.0.en.html), so be aware of that, regarding copying, modifying and (re)destributing.
