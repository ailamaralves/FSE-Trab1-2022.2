#include <server.h>
#include <menu.h>

uint8_t* varCompartilhada;

int main(int argc, char **argv)
{
    pthread_t menu_tid;
    pthread_t server_tid; 
    varCompartilhada = new uint8_t[14];

    int r = pthread_create(&menu_tid, NULL, menu, varCompartilhada);
    int r2 = pthread_create(&server_tid, NULL, criaServidor, varCompartilhada);
    if(!pthread_join(menu_tid, NULL))
        kill(r2, SIGKILL);
    pthread_join(server_tid, NULL);

    return 0;
}
