#include "uart.h"

void UartInit (uint32_t baud)
{
	//GPIO CLOCK ENABLE
	RCC-> AHB1ENR |= BV(GPIO_UART_CLKEN);

	GPIOA-> AFR[0] |= BV(14) | BV(13) | BV(12) | BV(10) | BV(9) | BV(8);
	GPIOA-> MODER &= ~(BV(TX_PIN*2) | BV(RX_PIN*2));
	GPIOA-> MODER |= (BV(TX_PIN*2+1) | BV(RX_PIN*2+1));
	// UART CLOCK ENABLE
	RCC-> APB1ENR |= BV(UART_CLKEN);

	UART->CR1 = BV(USART_CR1_TE_Pos) | BV(USART_CR1_RE_Pos);

	UART->CR1 &= ~(BV(USART_CR1_M_Pos) | BV(USART_CR1_OVER8_Pos));

	UART->CR2 &= ~(BV(USART_CR2_STOP_0) | BV(USART_CR2_STOP_1));

	if(baud ==9600)
		UART->BRR = UBRR_9600;
	else if(baud == 38400)
		UART->BRR = UBRR_38400;
	else if(baud == 115200)
			UART->BRR = UBRR_115200;
	UART->CR1 |= BV(USART_CR1_UE_Pos);

}


void UartPutch(uint8_t ch)
{
	UART->DR = ch;
	while((UART->SR & BV(USART_SR_TXE_Pos))== 0)
		;

}

void UartPuts(char str[])
{
	for(int i=0; str[i]!= '\0'; i++)
		UartPutch((uint8_t)str[i]);
}

uint8_t UartGetch(void)
{
	while((UART->SR & BV(USART_SR_RXNE_Pos))== 0)
		;
	uint8_t ch = UART->DR;
	return ch;
}

void UartGets(char str[])
{
	char ch;
	int i=0;
	do
	{
		ch = UartGetch();
		str[i] = ch;
		i++;
	}while(ch != '\r');
	str[i++]= '\n';
	str[i]= '\0';
}
