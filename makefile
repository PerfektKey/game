
FLAGS=-std=c++20 -Wall -g
INC=-lsfml-graphics -lsfml-window -lsfml-system

make:
	g++ $(FLAGS) *.cpp -o main $(INC)
	./main
