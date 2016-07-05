### Detailed Brain TODOs

- [x] Fix file ```testscripts.c```. // Working on Linux. It needs to be tested on Mac.
- [x] Implement ```?```, ```:```, ```;```.
- [x] Ignore else's without if's.
- [x] Improve the methods IsBranch, IsTerminator and so on.
- [x] Code refactoring for the return methods inside the recursivity.
- [x] Code refactoring for the whole project. Improve readability (CodeGen params too).
- [x] Create verbose mode describe on https://github.com/luizperes/brain/issues/2
- [ ] Fix InputExpr .
- [ ] Implement optimization for empty whiles ```[ ]```. Ignore them (For Else too).
- [ ] Implement optimization for empty moves ```ShiftExpr(0)``` and ```IncrementExpr(0)```.
- [ ] Implement a ```delete comments``` option for the compiler.
- [ ] Implement a ```generate optimized code``` option for the compiler.
- [ ] Improve the ```return``` at the method ```Parser::isSkippable```. Check switch at the parser.
- [ ] Change module's name.
- [ ] Change the if and while.`if (*ptr != 0)`, not `if (*ptr > 0)` 
- [ ] Code's refactoring for the files brain.cpp and Parser.cpp.
- [ ] Make sure you are deleting objects from the heap.
- [ ] Implement ```@``` and ```$``` if decided to.
