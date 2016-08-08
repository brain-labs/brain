How things are tested over here?
================================

We use a suite of tests described in each `*.b`, `*.br` and `*.brain` files. The test script run Brain itself with the mentioned _Brain extensions_ and the output is compared against their compatible test files (i.e. `*.cmp`, `*.cpm0`, `*.cmp1`, `*.code`). 

- `*.cmp`  - contains the program's desired output
- `*.cmp0` - contains the desired AST (Abstract Sytax Tree) for the flag `-O0`
- `*.cmp1` - contains the desired AST optimized with `-O1` flag.
- `*.code` - contains the desired code optimized output (code with no spaces, comments or invalid operations) 

### Commands to check brain with its comparison files:

- `brain filename.b` can be checked if its match `file_name.cmp` file
- `brain -O0 -emit-ast filename.b` can be checked if its match `filename.cmp0` file
- `brain -O1 -emit-ast filename.b` can be checked if its match `filename.cmp1` file
- `brain -emit-code filename.b` can be checked if its match `filename.code` file

### How to test?

Simply do `make test` in the root folder of Brain and it will automatically perform all the tests inside the `tests` folder.

