#include <client.h>
#include <gpio.h>

uint8_t* varCompartilhada;

#define DEV

void quit_handler(int sig){
    exit(0);
}

int main(int argc, char **argv)
{
#ifndef DEV
    if (!bcm2835_init())
	return 1;
#endif

    varCompartilhada = new uint8_t[14];

    signal(SIGINT, quit_handler);

    pthread_t client_tid, gpio_tid;
    pthread_create(&gpio_tid, NULL, gpio_handler, varCompartilhada);
    pthread_create(&client_tid, NULL, criaCliente, varCompartilhada);
    pthread_join(gpio_tid, NULL);
    pthread_join(client_tid, NULL);

    return 0;
}
