#include "configure_gpio_input.c"

int main() {
    // configure pin P8_8 as input with internal pull-up enabled
    int gpio_number1 = 67;
    int gpio_number2 = 69;
    configure_gpio_input(gpio_number1);
    // file path to read button status
    char valuePath1[40];
    char valuePath2[40];
    sprintf(valuePath1, "/sys/class/gpio/gpio%d/value", gpio_number1);
    sprintf(valuePath2, "/sys/class/gpio/gpio%d/value", gpio_number2);    
    // wait before first readings to avoid faulty readings
    sleep(1);
    int state1, state2;
    FILE *fp1, *fp2;
    // loop to monitor events
    while(1) {
        fp1 = fopen(valuePath1, "r");
        fp2 = fopen(valuePath2, "r");
        fscanf(fp1,"%d", &state1);
        fscanf(fp2,"%d", &state2);
        fclose(fp1);
        fclose(fp2);

        if (fp1 == NULL) {
            perror("Error opening value file");
            exit(EXIT_FAILURE);
        }
        // default state is 1 since buttons are configured with
        // internal pull-up resistors. So, reading 0 means button
        // is pressed
        
        // event detected
        if (state1 == 0) {
            printf("Button to GPIO67 pressed\n");
        }
        if (state2 ==0 ){
            printf("Button to GPIO69 pressed \n");
        }
    }
}

