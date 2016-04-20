all: build

build: Parser.cpp Expr.cpp ShiftExpr.cpp IncrementExpr.cpp InputExpr.cpp OutputExpr.cpp LoopExpr.cpp
	clang++ Parser.cpp Expr.cpp ShiftExpr.cpp IncrementExpr.cpp InputExpr.cpp OutputExpr.cpp LoopExpr.cpp brain.cpp -o brain 

run: brain 
	./brain
