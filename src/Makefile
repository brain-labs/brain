all: build

build: Parser.cpp Expr.cpp ShiftExpr.cpp IncrementExpr.cpp InputExpr.cpp OutputExpr.cpp
	clang++ Parser.cpp Expr.cpp ShiftExpr.cpp IncrementExpr.cpp InputExpr.cpp OutputExpr.cpp brain.cpp -o brain 

run: brain 
	./brain
