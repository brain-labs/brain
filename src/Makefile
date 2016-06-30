CC=clang++
CFLAGS=-O3 -Wall 
BIN=./bin
MKBIN=mkdir -p bin
SRCS=utils/ArgsOptions.cpp utils/ArgsHandler.cpp parser/Parser.cpp ast/expr/Expr.cpp ast/expr/ShiftExpr.cpp ast/expr/IncrementExpr.cpp ast/expr/InputExpr.cpp ast/expr/OutputExpr.cpp ast/expr/LoopExpr.cpp ast/expr/ArithmeticExpr.cpp ast/expr/DebugExpr.cpp ast/expr/BreakExpr.cpp ast/expr/IfExpr.cpp brain.cpp
CONFIG=`llvm-config --cxxflags --ldflags --system-libs --libs core mcjit native nativecodegen`

all: build

build: $(SRCS)
	$(MKBIN) && $(CC) $(CFLAGS) $(SRCS) $(CONFIG) -o $(BIN)/brain 

debug: $(SRCS)
	$(MKBIN) && $(CC) -g $(CFLAGS) $(SRCS) $(CONFIG) -o $(BIN)/brain

docker-build: $(SRCS)
	$(CC) $(CFLAGS) -D__cast_capital__=1  $(SRCS) $(CONFIG) -o brain

