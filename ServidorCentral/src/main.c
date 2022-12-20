#include <stdio.h>
#include <stdlib.h>

#include <wiringPi.h>

// Define the pins used to connect to the sensors
#define DHT22 04

// Function prototypes
void read_humidity_temp();

int main(void) {
    // Initialize the wiringPi library
    wiringPiSetup();

    // Set the pins used to connect to the sensors as inputs
    pinMode(DHT22, INPUT);

    // Print a menu and wait for user input
    int choice;
    while (1) {

        printf("\nMenu:\n");
        printf("1. Lâmpada 1\n");
        printf("2. Lâmpada 2\n");
        printf("3. Ar-condicionado\n");
        printf("4. Projetor\n");
        printf("5. Alarme\n");
        printf("6. Sensor presença\n");
        printf("7. Sensor fumaça\n");
        printf("8. Sensor janela\n");
        printf("9. Sensor porta\n");
        printf("10. Contagem pessoas entrada\n");
        printf("11. Contagem pessoas entrada\n");
        printf("12. Temperatura e umidada\n");
        printf("13. Sair\n");
        printf("Digite uma opção: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                read_humidity_sensor();
                break;

            case 2:
                read_temperature_sensor();
                break;

            case 3:
                read_temperature_sensor();
                break;    

            case 4:
                read_humidity_sensor();
                break;

            case 5:
                read_temperature_sensor();
                break;

            case 6:
                read_temperature_sensor();
                break;

            case 7:
                read_humidity_sensor();
                break;

            case 8:
                read_temperature_sensor();
                break;

            case 9:
                read_temperature_sensor();
                break;

            case 10:
                read_humidity_sensor();
                break;

            case 11:
                read_temperature_sensor();
                break;

            case 12:
                read_temperature_sensor();
                break;

            case 13
                return 0;

            default:
                printf("Opção inválida.\n");
                break;
        }
    }
}

void read_humidity_temp() {
    // Read the humidity sensor and print the result
    int temperature = digitalRead(TEMPERATURE_SENSOR_PIN);
    int humidity = digitalRead(HUMIDITY_SENSOR_PIN);
    printf("Temperature: %d\n Umidade: %d\n", temperature, humidity);
}

