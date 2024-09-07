// this file contains functions related to configuring a PWM pin on the BBB
#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

// configure mode
void configure_pin(char* pin_number, char* mode){
    if(!vfork()){
        // creates envirorment ot execute shell command
        int ret = execl("/usr/bin/config-pin", "config-pin", pin_number, mode, NULL);
        if (ret < 0){
            printf("Failed to configure pin \n");
            exit(-1);
        }
    }
}

// set PWM Period
void set_pwm_duty_cycle(char* pwmchip, char* channel, char* duty_cycle){
    // export filepath
    char PWMDutyCycle[60];
    sprintf(PWMDutyCycle, "/sys/class/pwm/%s/pwm-4:%s/duty_cycle", pwmchip, channel);
    // configure device
    FILE* fp = fopen(PWMDutyCycle, "w");
    fwrite(duty_cycle, sizeof(char), strlen(duty_cycle), fp);
    fclose(fp);
}

// set period
void set_pwm_period(char* pwmchip, char* channel, char* period){
    long duty_cycle_long;
    int period_int;
    // read old duty cycle
    char PWMDutyCycle[60], duty_cycle_str[20];
    sprintf(PWMDutyCycle, "/sys/class/pwm/%s/pwm-4:%s/period",pwmchip, channel);
    FILE* fp = fopen(PWMDutyCycle, "r");
    fscanf(fp, "%ld", &duty_cycle_long);
    fclose(fp);

    period_int = atol(period);
    // if old duty cycle is creater than new period we must
    // update the dummy_duty_cycle to aviod errors
    if ( duty_cycle_long >= period_int){
        duty_cycle_long = period_int/2;
        // change long to char 
        sprintf(duty_cycle_str, "%ld", duty_cycle_long);
        // set dummy cycle
        set_pwm_duty_cycle(pwmchip, channel, duty_cycle_str);
    }

    //export filepath
    char PWMPeriod[60];
    sprintf(PWMPeriod, "/sys/class/pwm/%s/pwm-4:%s/period", pwmchip, channel);
    fp = fopen(PWMPeriod, "w");
    fwrite(period, sizeof(char), strlen(period), fp);
    fclose(fp);
}

//start PWM
void start_pwm(char* pin_number, char* pwmchip, char* channel, char* period, char* duty_cycle){
        /* Input:
        pin_number: pin_number to generate PWM on pwmchip: the device folder to generate PWM
        channel: pwm device channel perod: pwm period duty_cycle: pwm duty cycle */
        
        // configure the pin in PWM mod
        configure_pin(pin_number, "pwm");

        //export PWM Device
        FILE* fp;
        char PWMExport[40];
        sprintf(PWMExport, "/sys/class/pwm/%s/export", pwmchip);
        fp = fopen(PWMExport, "w");
        fwrite(channel, sizeof(char), sizeof(channel), fp);
        fclose(fp);

        // configure PWM Period
        set_pwm_period(pwmchip, channel, period);
        // configure PWM Duty Cycle
        set_pwm_duty_cycle(pwmchip, channel, duty_cycle);
        // enable PWM
        char PWMEnable[40];
        sprintf(PWMEnable, "/sys/class/pwm/%s/pwm-4:%s/enable", pwmchip, channel);
        // configure generating PWM
        fp = fopen(PWMEnable, "w");
        fwrite("1", sizeof(char), 1, fp);
        fclose(fp);
}

void stop_pwm(char* pin_number, char* pwmchip, char* channel){
    char PWMDisable[40];
    sprintf(PWMDisable, "/sys/class/pwm/%s/pwm-4:%s/enable", pwmchip, channel);

    // stop generating PWM
    FILE* fp = fopen(PWMDisable, "w");
    fwrite("0", sizeof(char), 1, fp);
    fclose(fp);
}



