all: build

build: Parser.cpp Expr.cpp ShiftExpr.cpp IncrementExpr.cpp
	clang++ Parser.cpp Expr.cpp ShiftExpr.cpp IncrementExpr.cpp brain.cpp -o brain 

run: brain 
	./brain
