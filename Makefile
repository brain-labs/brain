CC=clang++
GCC=g++
CFLAGS=-O3 -Wall -std=c++1y
CFLAGS-DEBUG=-O0 -Wall
BIN=./bin

MKLIB=sudo bash ./libs/install.sh ./libs
MKTST=bash ./tests/test_scripts.sh ./tests
MKBIN=mkdir -p bin && $(MKLIB)
ROOT=src

SRCS=$(ROOT)/utils/ArgsOptions.cpp $(ROOT)/utils/ArgsHandler.cpp $(ROOT)/utils/Bootstrap.cpp $(ROOT)/parser/Parser.cpp $(ROOT)/ast/general/ASTInfo.cpp $(ROOT)/ast/expr/Expr.cpp $(ROOT)/ast/expr/ShiftExpr.cpp $(ROOT)/ast/expr/IncrementExpr.cpp $(ROOT)/ast/expr/InputExpr.cpp $(ROOT)/ast/expr/OutputExpr.cpp $(ROOT)/ast/expr/LoopExpr.cpp $(ROOT)/ast/expr/ArithmeticExpr.cpp $(ROOT)/ast/expr/DebugExpr.cpp $(ROOT)/ast/expr/BreakExpr.cpp $(ROOT)/ast/expr/IfExpr.cpp $(ROOT)/main.cpp
CONFIG=`llvm-config --cxxflags --ldflags --system-libs --libs core mcjit native nativecodegen irreader linker`

all: build

build: $(SRCS)
	$(MKBIN) && $(CC) $(CFLAGS) $(SRCS) $(CONFIG) -o $(BIN)/brain

build-gcc: $(SRCS)
	$(MKBIN) && $(GCC) $(CFLAGS) $(SRCS) $(CONFIG) -o $(BIN)/brain

debug: $(SRCS)
	$(MKBIN) && $(CC) -g $(CFLAGS-DEBUG) $(SRCS) $(CONFIG) -o $(BIN)/brain_debug

debug-gcc: $(SRCS)
	$(MKBIN) && $(GCC) -g $(CFLAGS-DEBUG) $(SRCS) $(CONFIG) -o $(BIN)/brain_debug

build-libs:
	$(MKLIB)

tests:
	$(MKTST)

.PHONY: tests
