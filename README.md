# Brain
A computer language based on Brainfuck.

### Information
__Brain__ wants to improve the performance of the Brainfuck programming language and extend it as well, as Brainfuck itself has a lack of data types and does not perform great control over variables, as well as when you want to make libraries and/or functions and when you want to use different models other than characters integers.

One of the main ideas of __Brain__ is saving some operations in machine language, creating an instruction optmizer due to the excess of instructions that Brainfuck would generate. Brain aims to implement it by using current technology __(LLVM)__.

In spite of implementing new commands and features, __Brain__ tries to be **completely compatible** with Brainfuck.

### How it has been built
Brain is based on previous work [https://github.com/luizperes/BrainfuckInterpreter](https://github.com/luizperes/BrainfuckInterpreter) and [https://github.com/Lisapple/BF-Compiler-Tutorial-with-LLVM](https://github.com/Lisapple/BF-Compiler-Tutorial-with-LLVM), now trying to make something more serious: __Turing Complete__, faster, more features/commands and different types. 

### Technical Information
Brain is __not yet__ a Turing Complete language, once I'm limiting its ```memory``` to ```100 * 32 bytes``` for now (only for testing purposes). Later on I will think in a way to allocate memory as needed instead.

### Current Status
Brain is running just like __Brainfuck__ so far, so feel free to use its tag [version 0.5](https://github.com/luizperes/brain/blob/v0.5/README.md)

### How to run your Brain files
It is as simple as: ```./brain your_brain_file.b```

### Project Status

To use __Project Status__, please visit:```https://github.com/luizperes/status-projects/blob/master/README.md``` and ```http://luizperes.github.io/status-projects/```

| Project Name                        | Status                                    | Technology  | Priority |  Deadline    |
| ----------------------------------- |:-----------------------------------------:| ----------- | :------: |  :--------:  |
| [Brain](#brain)         | ![Progress](http://progressed.io/bar/50)  | C/C++/LLVM  | Low      |              |

| To Do | In Progress | Done  |
| :---: | :---------: | :---: |
|![PostIt](http://api.ideiadoluiz.com.br/postit/?title=%20%237&desc=Implement%20Brain%20Commands.)|![PostIt](http://api.ideiadoluiz.com.br/postit/?title=%20%236&desc=Implement%20First%20Brain%20Commands%20(*,%20/%20%).)|![PostIt](http://api.ideiadoluiz.com.br/postit/?title=%20%233&desc=Make%20--debug%20and%20--help%20flags.%20Implement%20input%20files.) ![PostIt](http://api.ideiadoluiz.com.br/postit/?title=%20%232&desc=Implement%20Brainfuck%20commands.)|
||| ![PostIt](http://api.ideiadoluiz.com.br/postit/?title=%20%231&desc=Make%20Brainfuck%20compatible%20with%20LLVM.)![PostIt](http://api.ideiadoluiz.com.br/postit/?title=%20%234&desc=Think%20about%20new%20commands.)
|||![PostIt](http://api.ideiadoluiz.com.br/postit/?title=%20%235&desc=Optmize%20generated%20code.%20Include%20-O0%20and%20-O1%20options.)|

### Commands
__Implemented__
- ```>``` increment the data pointer (to point to the next cell to the right).
- ```<``` decrement the data pointer (to point to the next cell to the left).
- ```+``` increment (increase by one) the value at the data pointer. 
- ```-``` decrement (decrease by one) the value at the data pointer.
- ```.``` output the value at the data pointer.
- ```,``` accept one value of input, storing its value in the value at the data pointer.
- ```[``` if the value at the data pointer is zero, then instead of moving the instruction pointer forward to the next command, jump it forward to the command after the matching ] command.
- ```]``` jump to its correspondent [ .

__Not Implemented__
- ```#``` prints out the current debug information.
- ```{``` (__for__ loop) iterates ```'value-at-the-data-pointer' times``` and needs to be closed with a matching } command.
- ```}``` jump to its correspondent { . It also drecreases the value at the data pointer.
- ```!``` (__break__) jumps to the end of a loop (__[ ]__ or __{ }__)
- ```?``` if the value at the data pointer is ```0```, jumps to the block with ```:``` or ```;``` and executes the commands one by one up to its correlative ```;```, otherwise, it executes the code until it finds a ```:``` or ```;```.
- ```:``` it works as an ```otherwise``` (or ```else```) for ```?```.
- ```;``` ends a statement.

__Thinking About__
- ```$``` cast the value at the data pointer back and forth to ```float``` and ```int```.
- ```@``` include other __Brain__ files.
- ```*``` multiply ```*ptr``` with *(ptr-1). Store result in *ptr _// format: 2 3 *_
- ```/``` divide ```*ptr``` with *(ptr-1). Store the result in *ptr _// format: 2 3 /_
- ```%``` divide ```*ptr``` with *(ptr-1). Store the remainder in *ptr _// format: 2 3 %_

Example of the instructions above: 
- ___if-else___: ```? +++ : --- ;``` _// if (*ptr) { *ptr += 3; } else { *ptr -= 3; }_
- __for__: ```++++ { commands }``` _// makes four iterations 4 through 0 (excluded)_

### Compiler Options

- ```--help``` or ```-help```: Lists all compiler options.
- ```-emit-llvm```: Dumps the LLVM IR code before executing the output.
- ```-emit-expr```: Dumps the Expressions generated before executing the output.
- ```-O0```: Generates output code with no optmizations.
- ```-O1```: Optimizes Brain generated output code (Default).

### Help
Feel free to send your pull requests. :)

### LICENSE
This project extends [GNU GPL v. 3](http://www.gnu.org/licenses/gpl-3.0.en.html), so be aware of that, regarding copying, modifying and (re)destributing.

