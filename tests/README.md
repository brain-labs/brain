How things are tested over here?
================================

We use a suite of tests described in each `*.b` file. The `*.b` files are ran with Brain itself and the output of its code is compared against three other files that has the same name but different extensions: `*.cmp`, `*.cpm0` and `*.cmp1`. The first - `*.cmp` - contains only the code's execution output, the second - `*.cmp0` - contains the AST (Abstract Sytax Tree) with the flag `-O0` and the third one - `*.cmp1` - contains the AST optimized with `-O1` flag.


### In sum:

`brain file.b` is the `*.cmp`
`brain -O0 -emit-ast file.b` is the `*.cmp0`
`brain -O1 -emit-ast file.b` is the `*.cmp1`

### How to test?

Simply do `make test` in the root folder of Brain and it will automatically perform all the tests inside the `tests` folder.
