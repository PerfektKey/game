
FLAGS=-std=c++20 -Wall -g
INC=-lsfml-graphics -lsfml-window -lsfml-system

make:
	g++ $(FLAGS) main.cpp source/*.cpp -o main $(INC)
	./main
test:
	g++ $(FLAGS) test.cpp source/*.cpp -o test $(INC)
	./test
