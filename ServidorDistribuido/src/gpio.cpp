#include <gpio.h>

#define DEV

Gpio::Gpio(json data){
    light1 = new Pin(data["outputs"][0], 0);
    light2 = new Pin(data["outputs"][1], 0);
    air = new Pin(data["outputs"][2], 0);
    projector = new Pin(data["outputs"][3], 0);
    alarmBuzz = new Pin(data["outputs"][4], 0);
    sPresence = new Pin(data["inputs"][0], 1);
    sSmoke = new Pin(data["inputs"][1], 1);
    sWindow = new Pin(data["inputs"][2], 1);
    sDoor = new Pin(data["inputs"][3], 1);
    sCountIn = new Pin(data["inputs"][4], 1);
    sCountOut = new Pin(data["inputs"][5], 1);
    sTempHumid = new Pin(data["sensor_temperatura"][0], 0);// 1-Wire
}

void Gpio::refreshAll(uint8_t* states){
    handle_smoke(states);
    light1->refreshState(&states[1]);
    light2->refreshState(&states[2]);
    air->refreshState(&states[3]);
    projector->refreshState(&states[4]);
    alarmBuzz->refreshState(&states[5]);
    sPresence->refreshState(&states[6]);
    sSmoke->refreshState(&states[7]);
    sWindow->refreshState(&states[8]);
    sDoor->refreshState(&states[9]);
    sCountIn->refreshState(&states[10]);
    sCountOut->refreshState(&states[11]);
    sTempHumid->refreshState(&states[12]);
}

void Gpio::handle_smoke(uint8_t * states){
    if(states[7]){
        states[5] = states[7];
    }
}

Pin::Pin(json jgpio, uint8_t isIn){
    // isIn value 1 to input, value 0 to output
    gpioPin = jgpio["gpio"];
    type = jgpio["type"];
    tag = jgpio["tag"];
    isInput = isIn;
#ifndef DEV
    bcm2835_gpio_fsel(gpioPin, (isInput? BCM2835_GPIO_FSEL_INPT : BCM2835_GPIO_FSEL_OUTP));
    if(isInput){
        state = bcm2835_gpio_lev(gpioPin);
    }else{
        state = 0x0;
    }
#else
    state = 0x1;
    showState();     
#endif
}

void Pin::changeState(){
    if(isInput) return;
    state = !state;
#ifndef DEV
    bcm2835_gpio_write(gpioPin, (uint8_t)state); 
#endif
}

void Pin::refreshState(uint8_t* stat){
    if(!isInput){
        if(*stat != state){
            changeState();
        }
    }else{
#ifndef DEV
        state = bcm2835_gpio_lev(gpioPin);
#endif
    } 

    *stat = state;
}

void Pin::showState(){
    printf("Sensor %s: %d\n", tag.data(), state);
}

uint8_t Pin::getGpioPin(){
    return gpioPin;
}

uint8_t Pin::getState(){
    return state;
}

void *gpio_handler(void* args){
    std::ifstream f("configuracao_sala_02.json");
    json data = json::parse(f);
    
    Gpio main_gpio(data);
    
    uint8_t* response = (uint8_t*)args;
    float* dht;
    while (1)
    {

        delay(200);
#ifndef DEV
	    readDHT(main_gpio.sTempHumid->getGpioPin(), response);
        printf("temp: %f, hum %f", response[12], response[13]);
#endif 
        main_gpio.refreshAll(response);
    }
}
