#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "pwmConfig.c"


void togglePWM(){

    char pin_number[32] = "P9_16";
    char pwmchip[32] = "pwmchip4";
    char channel[32] = "1";
    char period[32] = "1000000000";
    char duty_cycle[32] = "500000";

    stop_pwm(pin_number, pwmchip, channel);
    
    //  Make sure pwm pin and channel are cleared fist
    start_pwm(pin_number, pwmchip, channel, period, duty_cycle); // start pwm
    // wait 60 seconds
    sleep(60);

    stop_pwm(pin_number, pwmchip, channel);
}