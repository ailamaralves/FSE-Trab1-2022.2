#include <gpio.h>

Gpio::Gpio(int gpioo, uint8_t entrad){
    // isIn value 1 to input, value 0 to output
    gpioPin = (uint8_t)gpioo;
    entrada = entrad;
    bcm2835_gpio_fsel(gpioPin, (entrada? BCM2835_GPIO_FSEL_INPT : BCM2835_GPIO_FSEL_OUTP));
    if(entrada){
        state = bcm2835_gpio_lev(gpioPin);
    }else{
        state = 0x0;
    }
}

void Gpio::c_state(){
    if(entrada) return;
    state = !state;
    bcm2835_gpio_write(gpioPin, (uint8_t)state); 
}

void Gpio::r_state(uint8_t* estados){
    if(!entrada){
        if(*estados != state){
            c_state();
        }
    }else{
        state = bcm2835_gpio_lev(gpioPin);
    } 

    *estados = state;
}

uint8_t Gpio::get_gpio(){
    return gpioPin;
}

uint8_t Gpio::get_state(){
    return state;
}

void Gpio::tem_fumaca(uint8_t fumaca){
    if(fumaca){
        state = 1;
    }
}

void *gpio_handler(void* args){
    std::ifstream f("sala_02.json");
    json data = json::parse(f);
    
    Gpio luz_1(data["outputs"][0]["gpio"], 0);
    Gpio luz_2(data["outputs"][1]["gpio"], 0);
    Gpio ar(data["outputs"][2]["gpio"], 0);
    Gpio projetor(data["outputs"][3]["gpio"], 0);
    Gpio alarme(data["outputs"][4]["gpio"], 0);
    Gpio s_presenca(data["inputs"][0]["gpio"], 1);
    Gpio s_fumaca(data["inputs"][1]["gpio"], 1);
    Gpio s_janela(data["inputs"][2]["gpio"], 1);
    Gpio s_porta(data["inputs"][3]["gpio"], 1);
    Gpio s_c_In(data["inputs"][4]["gpio"], 1);
    Gpio s_c_Out(data["inputs"][5]["gpio"], 1);
    Gpio s_temperatura(data["sensor_temperatura"][0]["gpio"], 1);
    Gpio s_umidade(data["sensor_temperatura"][0]["gpio"], 1);
    
    uint8_t* estados = (uint8_t*)args;

    while (1)
    {

        delay(200);
	    // readDHT();
        alarme.tem_fumaca(estados[6]);
        luz_1.r_state(&estados[0]);
        luz_2.r_state(&estados[1]);
        ar.r_state(&estados[2]);
        projetor.r_state(&estados[3]);
        alarme.r_state(&estados[4]);
        s_presenca.r_state(&estados[5]);
        s_fumaca.r_state(&estados[6]);
        s_janela.r_state(&estados[7]);
        s_porta.r_state(&estados[8]);
        s_c_In.r_state(&estados[9]);
        s_c_Out.r_state(&estados[10]);
    }
}
