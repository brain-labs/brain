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
- [x] Fix InputExpression
- [x] Implement optimization for empty whiles `[ ]`. Ignore them (For Else too).
- [x] Implement optimization for empty moves `ShiftExpr(0)` and `IncrementExpression(0)`.
- [ ] Implement a `delete comments` option for the compiler.
- [ ] Implement a `generate optimized code` option for the compiler.
- [ ] Improve the `return` at the method `Parser::isSkippable`. Check switch at the parser.
- [ ] Change module's name.
- [x] Change the if and while.`if (*ptr != 0)`, not `if (*ptr > 0)`. Although for is going to work only for positive numbers.
- [ ] Code's refactoring:
  - [ ] Move the content of brain.cpp to a boostrap file.
  - [ ] Refactor parser.cpp.
- [ ] Make sure you are deleting objects from the heap.
- [ ] Implement `@` for function calls
- [ ] Implement `$` as a print for number / 100.
- [ ] Allow the compiler to have cells larger than 100 x 4
- [ ] Check if required functions (LLVM IR) are implemented.
- [ ] Breaks are not working inside if (they are going back to the beginning of the loop)
- [ ] Fix verbose mode and levels for the debug mode
- [ ] Create install script. (remember to install the libs)

# Documentation

- [ ] Utils
- [ ] Parser
- [ ] Expressions
- [ ] AST
