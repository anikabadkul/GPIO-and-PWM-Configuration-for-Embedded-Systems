#include "configure_gpio_input.c"
#include "pwmConfig.c"

int main() {
    // Define variables for PWM pin, PWM chip, and channel
    char pin_number[32] = "P9_16";
    char pwmchip[32] = "pwmchip4";
    char channel[32] = "1";

    // GPIO numbers for buttons, indicating physical pin connections
    int gpio_number1 = 67; // GPIO number for the first button
    int gpio_number2 = 69; // GPIO number for the second button

    // Configure both GPIO pins as inputs
    configure_gpio_input(gpio_number1);
    configure_gpio_input(gpio_number2);

    // Prepare file paths to read button states
    char valuePath1[40];
    char valuePath2[40];
    sprintf(valuePath1, "/sys/class/gpio/gpio%d/value", gpio_number1);
    sprintf(valuePath2, "/sys/class/gpio/gpio%d/value", gpio_number2);

    // Wait before the first readings to stabilize the input
    sleep(1);

    // Declare variables to store the state of each button
    int state1, state2;
    FILE *fp1, *fp2;

    // Main loop to continuously monitor button states and control PWM
    while(1) {
        // Open value files for both buttons
        fp1 = fopen(valuePath1, "r");
        fp2 = fopen(valuePath2, "r");

        // Check if the files were successfully opened
        if (fp1 == NULL || fp2 == NULL) {
            perror("Error opening value file");
            // Exit if we cannot read the GPIO state
            exit(EXIT_FAILURE);
        }

        // Read the state of each button
        fscanf(fp1, "%d", &state1);
        fscanf(fp2, "%d", &state2);

        // Close the files after reading the values
        fclose(fp1);
        fclose(fp2);

        // Check the state of the first button
        if (state1 == 0) {
            // If pressed, configure PWM with specific duty cycle and period
            char duty_cycle[32] = "500000000";
            char period[32] = "100000000";
            printf("Button 1 pressed\n");
            start_pwm(pin_number, pwmchip, channel, period, duty_cycle);
            usleep(100000); // Short pulse
            stop_pwm(pin_number, pwmchip, channel);
        }

        // Check the state of the second button
        if (state2 == 0) {
            // If pressed, configure PWM with a different duty cycle and period
            char duty_cycle[32] = "500000";
            char period[32] = "1000000";
            printf("Button 2 pressed\n");
            start_pwm(pin_number, pwmchip, channel, period, duty_cycle);
            usleep(100000); // Short pulse
            stop_pwm(pin_number, pwmchip, channel);
        }
    }
}
