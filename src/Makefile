CC=clang++
CFLAGS=-O3 -Wall 
SRCS=ArgsHandler.cpp Parser.cpp Expr.cpp ShiftExpr.cpp IncrementExpr.cpp InputExpr.cpp OutputExpr.cpp LoopExpr.cpp ArithmeticExpr.cpp DebugExpr.cpp BreakExpr.cpp brain.cpp
CONFIG=`llvm-config --cxxflags --ldflags --system-libs --libs core mcjit native nativecodegen`

all: build

build: $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) $(CONFIG) -o brain 

debug: $(SRCS)
	$(CC) -g $(CFLAGS) $(SRCS) $(CONFIG) -o brain

docker-build: $(SRCS)
	$(CC) $(CFLAGS) -D__cast_capital__=1  $(SRCS) $(CONFIG) -o brain

run: brain 
	./brain
