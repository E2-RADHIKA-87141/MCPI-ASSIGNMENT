#include "uart.h"
#include "stm32f4xx.h"

void UartInit(uint32_t baud) {
    // Enable UART clock
    RCC->APB1ENR |= BV(UART_CLKEN);
    // Set UART pins to alternate function mode
    GPIO_UART->MODER &= ~(BV(UART_TX_PIN*2) | BV(UART_RX_PIN*2));
    GPIO_UART->MODER |= (BV(UART_TX_PIN*2+1) | BV(UART_RX_PIN*2+1));
    // Initialize UART registers
    USART2->BRR = baud;
    USART2->CR1 |= USART_CR1_UE; // Enable USART
    USART2->CR1 |= USART_CR1_TE; // Enable transmitter
    USART2->CR1 |= USART_CR1_RE; // Enable receiver
}

void UartPutch(uint8_t ch) {
    while (!(USART2->SR & USART_SR_TXE)); // Wait for transmit data register empty
    USART2->DR = ch;
}

void UartPuts(char str[]) {
    while (*str) {
        UartPutch(*str++);
    }
}

uint8_t UartGetch(void) {
    while (!(USART2->SR & USART_SR_RXNE)); // Wait for read data register not empty
    return USART2->DR;
}

void UartGets(char str[]) {
    while (1) {
        *str = UartGetch();
        if (*str == '\r' || *str == '\n') {
            *str = '\0';
            break;
        }
        str++;
    }
}
