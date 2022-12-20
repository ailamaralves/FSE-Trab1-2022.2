#include <client.h>

void comunicacaoServidorTCP(int socketClient, uint8_t* varCompartilhada)
{
    uint8_t buffer[14];
    int bytesRecebidos;
    int aux;

    while(1) {
        int aux;
        aux = send(socketClient, buffer, 14, 0);
        if(aux != 14){
	    	printf("Erro no envio: numero de bytes enviados diferente do esperado\n");
            break;
        }
        aux = recv(socketClient, buffer, 14, 0);
    	if(aux < 0){
            printf("Não recebeu o total de bytes enviados\n");
            break;
        }
        memcpy(varCompartilhada, buffer, 14);
        sleep(1);
        memcpy(buffer, varCompartilhada, 14);
    }
    return;

}

void *criaCliente(void* args){
    int socketClient;
    struct sockaddr_in serverAddr;
    struct sockaddr_in clientAddr;

    // Criar Socket
    if((socketClient = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
		printf("Erro no socket()\n");

    // Construir struct sockaddr_in
    memset(&serverAddr, 0, sizeof(serverAddr)); // Zerando a estrutura de dados
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = inet_addr(IP_SERVER);
	serverAddr.sin_port = htons(SERVER_PORT);

    // Connect
	if(connect(socketClient, (struct sockaddr *) &serverAddr, 
							sizeof(serverAddr)) < 0)
		printf("Erro no connect()\n");
    
    uint8_t* states = (uint8_t*)args;

    comunicacaoServidorTCP(socketClient, states);
    close(socketClient);
    return NULL; 
}
