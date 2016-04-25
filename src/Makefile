CC=clang++
CFLAGS=-O3 -Wall
SRCS=Parser.cpp Expr.cpp ShiftExpr.cpp IncrementExpr.cpp InputExpr.cpp OutputExpr.cpp LoopExpr.cpp brain.cpp
CONFIG=`llvm-config --cxxflags --ldflags --system-libs --libs core mcjit native nativecodegen`

all: build

build: $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) $(CONFIG) -o brain 

run: brain 
	./brain
