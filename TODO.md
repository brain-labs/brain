### Detailed Brain TODOs

- [x] Fix file ```testscripts.c```.
  - [x] Linux.
  - [x] Mac.
- [x] Implement `?`, `:`, `;`.
- [x] Ignore else's without if's.
- [x] Improve the methods IsBranch, IsTerminator and so on.
- [x] Code refactoring for the return methods inside the recursivity.
- [x] Code refactoring for the whole project. Improve readability (CodeGen params too).
- [x] Create verbose mode describe on https://github.com/luizperes/brain/issues/2
- [x] Fix InputInstruction
- [x] Implement optimization for empty whiles `[ ]`. Ignore them (For Else too).
- [x] Implement optimization for empty moves `ShiftInstr(0)` and `IncrementInstruction(0)`.
- [x] Implement a `delete comments` option for the compiler.
- [x] Implement a `generate optimized code` option for the compiler.
- [x] Improve the `return` at the method `Parser::isSkippable`. Check switch at the parser.
- [x] Change module's name.
- [x] Change the if and while.`if (*ptr != 0)`, not `if (*ptr > 0)`. Although for is going to work only for positive numbers.
- [x] Code's refactoring:
  - [x] Move the content of brain.cpp to a boostrap file.
  - [x] Refactor parser.cpp.
- [x] Make sure you are deleting objects from the heap.
- [x] Implement `$` as a print for number / 100.
  - [x] Implement test cases for `$`
- [x] Allow the compiler to have cells larger than 100 x 4
- [x] Check if required functions (LLVM IR) are implemented.
- [x] Breaks are not working inside if (they are going back to the beginning of the loop)
- [x] Fix verbose mode and levels for the debug mode
- [x] Create install script. (remember to install the libs)
- [ ] Create a code generator file to store common code shared by the instructions.

# Documentation

- [x] Utils
- [x] Parser
- [x] Instructions
- [x] AST
