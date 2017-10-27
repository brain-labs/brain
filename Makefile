# Having trouble to build your makefile?
#
# To build the versions 3.8 or 3.9, you can write:
# make build-3.8
# or
# make build-3.9
#
# For the other versions, you can simply pass the CC, GCC and LLVM_CONFIG depending on your clang/LLVM config.
# For example:
#
# make C=clang-3.7 CC=clang++-3.7 LLVM_CONFIG=llvm-config-3.7
#
# For the tests and installing the libraries you can do:
# make install C=clang-3.8
# and
# make tests C=clang-3.8

CC=clang++
GCC=g++
CLANG=clang
LLVM_CONFIG=llvm-config

CFLAGS=-O3 -Wall -Wno-unknown-warning-option -std=c++1y
CFLAGS-DEBUG=-O0 -Wno-unknown-warning-option -Wall
BIN=./bin

SUDO=sudo
MKLIB=bash ./libs/install.sh ./libs $(CLANG)
MKTST=bash ./tests/test_scripts.sh ./tests $(CLANG)
MKBIN=mkdir -p bin
ROOT=src

SRCS=$(ROOT)/utils/ArgsOptions.cpp $(ROOT)/utils/ArgsHandler.cpp $(ROOT)/utils/Bootstrap.cpp $(ROOT)/parser/Parser.cpp $(ROOT)/ast/general/ASTInfo.cpp $(ROOT)/ast/expr/Expr.cpp $(ROOT)/ast/expr/ShiftExpr.cpp $(ROOT)/ast/expr/IncrementExpr.cpp $(ROOT)/ast/expr/InputExpr.cpp $(ROOT)/ast/expr/OutputExpr.cpp $(ROOT)/ast/expr/LoopExpr.cpp $(ROOT)/ast/expr/ArithmeticExpr.cpp $(ROOT)/ast/expr/DebugExpr.cpp $(ROOT)/ast/expr/BreakExpr.cpp $(ROOT)/ast/expr/IfExpr.cpp $(ROOT)/ast/expr/FloatExpr.cpp $(ROOT)/main.cpp
CONFIG=`$(LLVM_CONFIG) --cxxflags --ldflags --system-libs --libs core mcjit native nativecodegen irreader linker`

all: build

build: $(SRCS)
	$(MKBIN) && $(CC) $(CFLAGS) $(SRCS) $(CONFIG) -o $(BIN)/brain
	rm *.dwo

build-gcc: $(SRCS)
	$(MKBIN) && $(GCC) $(CFLAGS) $(SRCS) $(CONFIG) -o $(BIN)/brain
	rm *.dwo

build-travis: $(SRCS)
	$(MKBIN) && $(CC) $(CFLAGS) -DINCOMPATIBLE_LLVM $(SRCS) $(CONFIG) -o $(BIN)/brain

build-3.8: CC=clang++-3.8
build-3.8: LLVM_CONFIG=llvm-config-3.8
build-3.8: all

build-3.9: CC=clang++-3.9
build-3.9: LLVM_CONFIG=llvm-config-3.9
build-3.9: all

debug: $(SRCS)
	$(MKBIN) && $(CC) -g $(CFLAGS-DEBUG) $(SRCS) $(CONFIG) -o $(BIN)/brain_debug
	mv *.dwo bin/

debug-gcc: $(SRCS)
	$(MKBIN) && $(GCC) -g $(CFLAGS-DEBUG) $(SRCS) $(CONFIG) -o $(BIN)/brain_debug

build-libs:
	$(MKLIB)

tests:
	$(MKTST)

install:
	$(MKLIB)

.PHONY: tests
