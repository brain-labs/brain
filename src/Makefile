CC=clang++
CFLAGS=-O3 -Wall
SRCS=Parser.cpp Expr.cpp ShiftExpr.cpp IncrementExpr.cpp InputExpr.cpp OutputExpr.cpp LoopExpr.cpp
CONFIG=`llvm-config --ldflags --system-libs --libs core executionengine interpreter mc support nativecodegen` cxxflags="-stdlib=libstdc++" linkflags="-stdlib=libstdc++"

all: build

build: $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) $(CONFIG) brain.cpp -o brain 

run: brain 
	./brain
