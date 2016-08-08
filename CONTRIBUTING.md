# Contributing Guide

## Pull Requests

All the flow can be done that way (and recommended):

    hub fork
    git checkout -b dev origin/dev
    git checkout -b your-feature-branch
    git add --all
    git commit
    hub pull-request

## Branches

### Master

The main branch (stable) is the `master` branch. Just code compilable and passing the tests will be in that branch.

### Dev

The main development branch is `dev`. We can add another temporary branches while developing new features.

### Features Branchs

You would do that by creating (for instance) a new branch named `for-loop` (do not forget to branch the `dev` branch).

## Test System

The tests are done in two levels:

* compiling the compiler
* executing pre-written tests in `brain`

Any new code is very recommended to be tested in order to avoid underlying bugs.

## Versions

The main system of version is similar to the Python Development Team:

**v`B`.`F`.`M`**

- `B` => Big Changes
- `F` => Features
- `M` => Maintenance

Examples:

* `v0.7.1`
* `v1.0.0`

## Dependencies for Development

* C/C++ compiler
* [llvm](http://www.llvm.org)
* [git](https://git-scm.com/downloads)
* [llvm](http://llvm.org/releases/download.html)
* [hub](https://github.com/github/hub) **(wishful)**
* [pre-commit](http://pre-commit.com/) **(wishful)**
