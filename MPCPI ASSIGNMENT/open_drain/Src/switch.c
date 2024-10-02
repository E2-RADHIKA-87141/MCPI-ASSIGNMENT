#include "switch.h"

void SwitchInit(void)
{
	RCC->AHB1ENR |= BV(GPIO_SWITCH_CLKEN);

	GPIO_SWITCH-> MODER &= ~(BV(SWITCH_PIN*2) | BV(SWITCH_PIN*2+1));
	GPIO_SWITCH-> PUPDR &= ~(BV(SWITCH_PIN*2+1) | BV(SWITCH_PIN*2));
}

int SwitchIsPressed(void)
{
	uint32_t idr= GPIO_SWITCH-> IDR;
	if((idr & BV(SWITCH_PIN))== 0)
		return 0;

	return 1;
}
