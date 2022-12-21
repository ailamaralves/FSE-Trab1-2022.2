all: 
	g++ server.cpp menu.cpp main.cpp -lncurses -lpthread -I../inc -c
	g++ server.o menu.o main.o -lncurses -lpthread -I../inc -o exec

menu: 
	g++ menu.cpp -lncurses -lpthread -I../inc -o menu

run: 
	./exec


