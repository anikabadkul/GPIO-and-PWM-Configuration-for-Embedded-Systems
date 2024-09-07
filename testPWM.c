#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "togglePWM.c"
#include "configure_gpio_input.c"

int main(){
    // config pin 8
    int gpio_number = 67;
    configure_gpio_input(gpio_number);
    // path to button status
    char valuePath[40];
    sprintf(valuePath, "/sys/class/gpio/gpio%d/value", gpio_number);
    // 1 sec delay
    sleep(1);

    long count = 0;
    int state = 0;
    FILE *fp;
    togglePWM();
    while(1){
        fp = fopen(valuePath, "r");
        fscanf(fp, "%d", &state);

        
        if (state==0){
            // event occured
            count++;
            printf("pin interrupted %lu\n",count);
        }
    }
    fclose(fp);
    return 0;
}