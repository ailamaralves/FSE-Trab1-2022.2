all: 
	g++ client.cpp dht22.cpp gpio.cpp main.cpp -lbcm2835 -lpthread -I../inc -c
	g++ client.o dht22.o gpio.o main.o -lbcm2835 -lpthread -I../inc -o exec

run: 
	./exec

