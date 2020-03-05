#include <unistd.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <iostream>


class GpioOpt {
    public:
        GpioOpt();
        ~GpioOpt();
        void blink(int pin, int del);
        void turn_all_on();                 // Turn all LEDS on
        void turn_all_off();                // Turn all LEDS off

        int *gpio_list;                     // Pointer to the list containing all LED ids, Maybe use IENUM?
};
