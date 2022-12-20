#include <unistd.h>
#include <cliente.h>
#include <gpio.h>

void gpio_init() {
  wiringPiSetup();
}

void toggle(int item, int status) {
  pinMode(item, OUTPUT);
  digitalWrite(item, status);
}

void all_off() {
  // Lâmpada Salas 01 e 03
  pinMode(L_01, OUTPUT);
  digitalWrite(L_01, LOW);

  pinMode(L_02, OUTPUT);
  digitalWrite(L_02, LOW);
  
  // Ar-condicionado 
  pinMode(AC, OUTPUT);
  digitalWrite(AC, LOW);
}


void handle_pres1(void) {
  char* message = "1";
  printf("Alteração em: Sensor de Presença\n");
  enviaServidor(message);
}

void handle_pres2(void) {
  char* message = "2";
  printf("Alteração em: Sensor de Fumaça\n");
  enviaServidor(message);
}

void handle_abr1(void) {
  char* message = "3";
  printf("Alteração em: Sensor de Janela\n");
  enviaServidor(message);
}

void handle_abr2(void) {
  char* message = "4";
  printf("Alteração em: Sensor de Porta\n");
  enviaServidor(message);
}

void handle_abr3(void) {
  char* message = "5";
  printf("Alteração em: Sensor de Contagem de Pessoas Entrada \n");
  enviaServidor(message);
}

void handle_abr4(void) {
  char* message = "6";
  printf("Alteração em: Sensor de Contagem de Pessoas Saída \n");
  enviaServidor(message);
}

void handle_abr5(void) {
  char* message = "7";
  printf("Alteração em: Sensor de Temperatura/Umidade \n");
  enviaServidor(message);
}


void* gpio_handler() {
  // Sensor de Presença
  pinMode(SPres, OUTPUT);
  wiringPiISR(SPres, INT_EDGE_BOTH, &handle_pres1);

  // Sensor de Fumaça
  pinMode(SFum, OUTPUT);
  wiringPiISR(SFum, INT_EDGE_BOTH, &handle_pres2);

  // Sensor de Janela
  pinMode(SJan, OUTPUT);
  wiringPiISR(Sjan, INT_EDGE_BOTH, &handle_abr1);

  // Sensor de Porta
  pinMode(SPor, OUTPUT);
  wiringPiISR(Spor, INT_EDGE_BOTH, &handle_abr2);
  
  // Sensor de Contagem de Pessoas Entrada
  pinMode(SC_IN, OUTPUT);
  wiringPiISR(SC_IN, INT_EDGE_BOTH, &handle_abr3);

  // Sensor de Contagem de Pessoas Saída
  pinMode(SC_OUT, OUTPUT);
  wiringPiISR(SC_OUT, INT_EDGE_BOTH, &handle_abr4);

  // Sensor de Temperatura/Umidade
  pinMode(DHT22, OUTPUT);
  wiringPiISR(DHT22, INT_EDGE_BOTH, &handle_abr5);

  for(;;) {
    sleep(1);
  }
}
 
