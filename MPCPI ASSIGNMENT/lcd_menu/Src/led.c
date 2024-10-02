
#include "led.h"
#include "stm32f4xx.h"

void LedInit(void) {
    // Enable GPIOA clock
    RCC->AHB1ENR |= BV(GPIO_LED_CLKEN);
    // Set GPIO pins to output mode
    GPIO_LED->MODER &= ~(BV(RED_LED_PIN*2) | BV(BLUE_LED_PIN*2));
    GPIO_LED->MODER |= (BV(RED_LED_PIN*2+1) | BV(BLUE_LED_PIN*2+1));
}

void turn_on_red_led(void) {
    GPIO_LED->BSRR = (1 << RED_LED_PIN);
}

void turn_off_red_led(void) {
    GPIO_LED->BSRR = (1 << (RED_LED_PIN + 16));
}

void turn_on_blue_led(void) {
    GPIO_LED->BSRR = (1 << BLUE_LED_PIN);
}

void turn_off_blue_led(void) {
    GPIO_LED->BSRR = (1 << (BLUE_LED_PIN + 16));
}
