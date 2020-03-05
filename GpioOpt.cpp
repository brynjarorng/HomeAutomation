#include "GpioOpt.h"

using namespace std;

#define DELAY 100 
#define RED 0
#define GREEN 3
#define BLUE 2
#define YELLOW 1
#define OFF 0
#define ON 1
#define NUM_OUTPUTS 4

GpioOpt::GpioOpt() {
    // Setup wiringPi and all outputs
    wiringPiSetup();
    pinMode(RED, OUTPUT);
    pinMode(GREEN, OUTPUT);
    pinMode(BLUE, OUTPUT);
    pinMode(YELLOW, OUTPUT);

    // Add all colors to array
    gpio_list = new int[NUM_OUTPUTS];

    // Put lights into the list
    gpio_list[0] = RED;
    gpio_list[1] = YELLOW;
    gpio_list[2] = BLUE;
    gpio_list[3] = GREEN;

    // Turn all lights off
    turn_all_off();
}

GpioOpt::~GpioOpt() {
    turn_all_off();
    delete[] gpio_list;
}

void GpioOpt::blink(int pin, int del)
{
        digitalWrite(pin, ON);
        delay(del);
        digitalWrite(pin, OFF);
}

// Turn all lights on
void GpioOpt::turn_all_on()
{
    for (int i = 0; i < NUM_OUTPUTS; i++)
    {
        digitalWrite(gpio_list[i], ON);
    }
}

// Turn all lights off
void GpioOpt::turn_all_off()
{
    for (int i = 0; i < NUM_OUTPUTS; i++)
    {
        digitalWrite(gpio_list[i], OFF);
    }
}

