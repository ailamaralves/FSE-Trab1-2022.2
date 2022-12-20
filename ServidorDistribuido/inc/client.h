#include <string>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <unistd.h>
#include <pthread.h>
#include <signal.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define MAXTIMINGS 100

#define IP_SERVER "127.0.0.1"
#define SERVER_PORT 10080
#define CLIENT_PORT 10180

//helpers
#define repeat(x) for(int it=0;it<x;it++)


void comunicacaoServidorTCP(int socketClient, uint8_t* varCompartilhada);

void *criaCliente(void* args);

void quit_handler(int sig);