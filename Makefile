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

CFLAGS=-O3 -Wall -Wno-unknown-warning-option -std=c++14
CFLAGS-DEBUG=-O0 -Wall -Wno-unknown-warning-option -std=c++14 -DIS_DEBUG
BIN=./bin

SUDO=sudo
MKLIB=bash ./libs/install.sh ./libs $(CLANG)
MKTST=bash ./tests/test_scripts.sh ./tests $(CLANG)
MKBIN=mkdir -p bin
ROOT=src
CLEANUP=rm -f *.dwo

SRCS=$(ROOT)/utils/ArgsOptions.cpp $(ROOT)/utils/ArgsHandler.cpp $(ROOT)/utils/Bootstrap.cpp $(ROOT)/parser/Parser.cpp $(ROOT)/ast/general/ASTInfo.cpp $(ROOT)/ast/instr/Instr.cpp $(ROOT)/ast/instr/ShiftInstr.cpp $(ROOT)/ast/instr/IncrementInstr.cpp $(ROOT)/ast/instr/InputInstr.cpp $(ROOT)/ast/instr/OutputInstr.cpp $(ROOT)/ast/instr/LoopInstr.cpp $(ROOT)/ast/instr/ArithmeticInstr.cpp $(ROOT)/ast/instr/DebugInstr.cpp $(ROOT)/ast/instr/BreakInstr.cpp $(ROOT)/ast/instr/IfInstr.cpp $(ROOT)/ast/instr/FloatInstr.cpp $(ROOT)/ast/instr/MovInstr.cpp $(ROOT)/main.cpp
CONFIG=`$(LLVM_CONFIG) --cxxflags --ldflags --system-libs --libs core mcjit native nativecodegen irreader linker`

all: build

build: $(SRCS)
	$(MKBIN) && $(CC) $(CFLAGS) $(SRCS) $(CONFIG) -o $(BIN)/brain
	$(CLEANUP)

build-gcc: $(SRCS)
	$(MKBIN) && $(GCC) $(CFLAGS) $(SRCS) $(CONFIG) -o $(BIN)/brain
	$(CLEANUP)

build-travis: $(SRCS)
	$(MKBIN) && $(CC) $(CFLAGS) -DINCOMPATIBLE_LLVM $(SRCS) $(CONFIG) -o $(BIN)/brain

build-3.8: CC=clang++-3.8
build-3.8: LLVM_CONFIG=llvm-config-3.8
build-3.8: all

build-3.9: CC=clang++-3.9 
build-3.9: LLVM_CONFIG=llvm-config-3.9
build-3.9: all

build-4.0: CC=clang++-4.0
build-4.0: LLVM_CONFIG=llvm-config-4.0
build-4.0: all

build-5.0: CC=clang++-5.0
build-5.0: LLVM_CONFIG=llvm-config-5.0
build-5.0: all

build-6.0: CC=clang++-6.0
build-6.0: LLVM_CONFIG=llvm-config-6.0
build-6.0: all

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
