#include "stm32f0xx.h"

void SYS_CLOCK(void);
void GPIO_PINS(void);

int main(void) {

	// SETUP
	SYS_CLOCK();
	GPIO_PINS();

	// LOOP
	while(1) {
		HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_4);
		HAL_Delay(12);
	}
	return 0;
}

void SYS_CLOCK(void) {

	RCC_OscInitTypeDef OSC_CONF;

	OSC_CONF.OscillatorType = RCC_OSCILLATORTYPE_HSI; // Internal 8MHz oscillator
	OSC_CONF.HSIState = RCC_HSI_ON; // Enable HSI
	OSC_CONF.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT; // Default 8MHz configuration
	OSC_CONF.PLL.PLLState = RCC_PLL_NONE; // Not using frequency multiplier
	HAL_RCC_GetOscConfig(&OSC_CONF);

	RCC_ClkInitTypeDef CLK_CONF;
	CLK_CONF.ClockType = RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1;
	CLK_CONF.SYSCLKSource = RCC_SYSCLKSOURCE_HSI; // Clock source is the 8MHz oscillator
	CLK_CONF.AHBCLKDivider = RCC_SYSCLK_DIV1; // Divide system clock by 1, this clock is used by AHB Bus
	CLK_CONF.APB1CLKDivider = RCC_HCLK_DIV1; // Divide clock by 1, clock is used by TIMERS, RTC, UART, PWM, I2C
	HAL_RCC_ClockConfig(&CLK_CONF, 0);
}

void GPIO_PINS(void) {

	__HAL_RCC_GPIOA_CLK_ENABLE(); // Enable system clock to GPIOA

	GPIO_InitTypeDef GPIO_CONF;

	GPIO_CONF.Pin = GPIO_PIN_4; // PA4, Built-in LED
	GPIO_CONF.Mode = GPIO_MODE_OUTPUT_PP; // Push-pull output
	GPIO_CONF.Pull = GPIO_NOPULL; // NO PULL UP/DOWN RESISTOR
	GPIO_CONF.Speed = GPIO_SPEED_FREQ_MEDIUM; // 4-10MHz Speed
	HAL_GPIO_Init(GPIOA, &GPIO_CONF);
}
