

#include "switch_intr.h"

void SwitchInit(void) {
	// Enable GPIO clock
	RCC->AHB1ENR |= BV(SWITCH_GPIO_CLKEN);
	// Set gpio mode as input
    GPIOA-> MODER &= ~BV(SWITCH_PIN*2+1)|BV(SWITCH_PIN*2);
	// enable falling edge detection (in FTSR)
   // GPIOA-> PUPDR &= BV(SWITCH_PIN*2)|BV(SWITCH_PIN*2);
	// enable (unmask) exti interrupt (in IMR)
    EXTI->FTSR |= BV(SWITCH_EXTI);
	// select exti interrupt (in SYSCFG->EXTICRx) -- EXTI0 --> EXTICR1[3:0] = 0000
    EXTI->IMR |= BV(SWITCH_EXTI);
	// enable exti in NVIC (ISER or NVIC_EnableIRQ())
    SYSCFG->EXTICR[0] &= ~(BV(3)|BV(2)|BV(1)|BV(0));
    // EXTI0_IRQn
    NVIC_EnableIRQ(EXTI0_IRQn);
}
volatile uint32_t SwitchExtiFlag = 0;
int SwitchIntrCount =0;
		// intr handler(ISR) written with exactly same name as of handler fn name in vector table.
// it overrides the WEAK function written in startup.S
void EXTI0_IRQHandler(void) {
	// acknowledge the interrupt
	EXTI->PR |= BV(SWITCH_EXTI);
	SwitchExtiFlag = 1;

    }









