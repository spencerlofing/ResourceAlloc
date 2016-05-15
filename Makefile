ResourceAlloc: main.o person.o week.o task.o tokenizer.o date.o TreeNode.o BSTExpr.o exprtoken.o
	g++ -std=c++11 -g -Wall main.o person.o week.o task.o tokenizer.o date.o TreeNode.o BSTExpr.o exprtoken.o -o ResourceAlloc
main.o: main.cpp person.h week.h task.h tokenizer.h
	g++ -std=c++11 -g -Wall -c main.cpp
person.o: person.cpp person.h week.h task.h
	g++ -std=c++11 -g -Wall -c person.cpp
week.o: week.cpp week.h task.h
	g++ -std=c++11 -g -Wall -c week.cpp
task.o: task.cpp task.h date.h BSTExpr.h
	g++ -std=c++11 -g -Wall -c task.cpp
tokenizer.o: tokenizer.h tokenizer.cpp
	g++ -std=c++11 -g -Wall -c tokenizer.cpp
date.o: date.h date.cpp
	g++ -std=c++11 -g -Wall -c date.cpp
TreeNode.o: TreeNode.h TreeNode.cpp
	g++ -std=c++11 -g -Wall -c TreeNode.cpp
BSTExpr.o: BSTExpr.h BSTExpr.cpp exprtoken.h task.h TreeNode.h
	g++ -std=c++11 -g -Wall -c BSTExpr.cpp
exprtoken.o: exprtoken.h exprtoken.cpp
	g++ -std=c++11 -g -Wall -c exprtoken.cpp
clean: 
	rm *.o ResourceAlloc
	echo clean done
