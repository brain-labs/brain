CC=clang++
GCC=g++
CFLAGS=-O3 -Wall -std=c++1y
CFLAGS-DEBUG=-O0 -Wall  
BIN=./bin
MKLIB=sudo bash ../libs/install.sh ../libs
MKBIN=mkdir -p bin && $(MKLIB) 
SRCS=utils/ArgsOptions.cpp utils/ArgsHandler.cpp utils/Bootstrap.cpp parser/Parser.cpp ast/general/ASTInfo.cpp ast/expr/Expression.cpp ast/expr/ShiftExpr.cpp ast/expr/IncrementExpr.cpp ast/expr/InputExpr.cpp ast/expr/OutputExpr.cpp ast/expr/LoopExpr.cpp ast/expr/ArithmeticExpr.cpp ast/expr/DebugExpr.cpp ast/expr/BreakExpr.cpp ast/expr/IfExpr.cpp main.cpp
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
