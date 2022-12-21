#include <bcm2835.h>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <json.h>

using json = nlohmann::json;

#define MAXTIMINGS 100

class Gpio 
{
public:
    uint8_t state;
    uint8_t entrad;
    uint8_t gpioPin;
    Gpio(int gpioo, uint8_t entrad);
    void r_state(uint8_t* estados);
    void c_state();
    void d_all();
    uint8_t get_gpio();
    uint8_t get_state();

};

void *gpio_handler(void* args);

int readDHT(int type, int pin);

