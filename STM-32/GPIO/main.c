#include "reg_map.h"
#include "GPIO.h"

int main(void)
{
	GPIO_TypeDef initVal;
	GPIO_PinState pin_state = GPIO_PIN_RESET;
	
	//RCC-GPIOA
	RCC_IOPENR |= (RCC_GPIOA_EN | RCC_GPIOB_EN);
	initVal.MODER = GPIO_MODE_OUTPUT;
	initVal.OTYPER = GPIO_OUTPUT_TYPE_0;
	initVal.OSPEEDR = GPIO_SPEED_FREQ_VERY_HIGH;
	initVal.PUPDR = GPIO_GPIO_NOPUPD;
	
	GPIO_Init(GPIOA, GPIO_PIN_5_POS, &initVal);
	GPIO_Init(GPIOA, GPIO_PIN_8_POS, &initVal);
	GPIO_Init(GPIOB, GPIO_PIN_5_POS, &initVal);
	
	GPIO_Write_Pin(GPIOA, GPIO_PIN_5_POS, pin_state);
	GPIO_Write_Pin(GPIOA, GPIO_PIN_8_POS, pin_state);
	GPIO_Write_Pin(GPIOB, GPIO_PIN_5_POS, pin_state);
	
	while (1)
	{
		pin_state = (GPIO_PinState)(!pin_state);
		GPIO_Write_Pin(GPIOA, GPIO_PIN_5_POS, pin_state);
		GPIO_Write_Pin(GPIOA, GPIO_PIN_8_POS, (!pin_state));
		GPIO_Write_Pin(GPIOB, GPIO_PIN_5_POS, pin_state);
		delay(0x20000);
	}
}
