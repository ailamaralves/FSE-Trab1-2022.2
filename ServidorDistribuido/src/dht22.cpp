//  How to access GPIO registers from C-code on the Raspberry-Pi
//  Example program
//  15-January-2012
//  Dom and Gert
//

/*
$ wget http://www.open.com.au/mikem/bcm2835/bcm2835-1.8.tar.gz
$ tar -zxvf bcm2835-1.8.tar.gz
$ cd bcm2835-1.8
$ ./configure
$ make
$ sudo make install

Then compile the Adafruit_DHT program with

gcc DHT.c -l bcm2835 -std=gnu99 -o DHT
*/

// Access from ARM Running Linux

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <fcntl.h>
#include <assert.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <bcm2835.h>
#include <unistd.h>

#define MAXTIMINGS 100

//#define DEBUG

// #define DHT
int readDHT(int type, int pin);

int readDHT(int pin, uint8_t* response) {

    int bits[250], data[100];
    int bitidx = 0;
    int counter = 0;
    int laststate = HIGH;
    int j=0;

    // Set GPIO pin to output
    bcm2835_gpio_fsel(pin, BCM2835_GPIO_FSEL_OUTP);

    bcm2835_gpio_write(pin, HIGH);
    usleep(500000);  // 500 ms
    bcm2835_gpio_write(pin, LOW);
    usleep(20000);

    bcm2835_gpio_fsel(pin, BCM2835_GPIO_FSEL_INPT);

    data[0] = data[1] = data[2] = data[3] = data[4] = 0;

    // wait for pin to drop?
    while (bcm2835_gpio_lev(pin) == 1) {
        usleep(1);
    }

    // read data!
    for (int i=0; i< MAXTIMINGS; i++) {
        counter = 0;
        while ( bcm2835_gpio_lev(pin) == laststate) {
        counter++;
        //nanosleep(1);		// overclocking might change this?
            if (counter == 1000)
        break;
        }
        laststate = bcm2835_gpio_lev(pin);
        if (counter == 1000) break;
        bits[bitidx++] = counter;

        if ((i>3) && (i%2 == 0)) {
        // shove each bit into the storage bytes
        data[j/8] <<= 1;
        if (counter > 200)
            data[j/8] |= 1;
        j++;
        }
    }


#ifdef DEBUG
    for (int i=3; i<bitidx; i+=2) {
        printf("bit %d: %d\n", i-3, bits[i]);
        printf("bit %d: %d (%d)\n", i-2, bits[i+1], bits[i+1] > 200);
    }
#endif

    if ((j >= 39) &&
        (data[4] == ((data[0] + data[1] + data[2] + data[3]) & 0xFF)) ) {
        // yay!
        float f[2];
        response[12] = data[0] * 256 + data[1];
        response[12] /= 10;

        response[13] = (data[2] & 0x7F)* 256 + data[3];
            response[13] /= 10.0;
            if (data[2] & 0x80)  response[13] *= -1;
        printf("Temperatura: %f Himidade: %f\n", response[12], response[13]);

        return 1;
    }

  return 0;
}
