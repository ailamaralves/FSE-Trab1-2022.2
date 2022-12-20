#include <bcm2835.h>
#include <bits/stdc++.h>
#include <ncurses.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <pthread.h>

#define OFFLINEVALUE 0xff

#define CLIENT_IP "0.0.0.0"
#define SERVER_PORT 10080
#define CLIENT_PORT 10180

//helpers
#define repeat(x) for(int it=0;it<x;it++)

void* criaServidor(void *arg);

void comunicacaoClienteTCP(int socketCliente, uint8_t* varCompartilhada);