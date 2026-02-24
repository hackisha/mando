#include "reg_map.h"
#include "GPIO.h"


void delay(unsigned int delay_cnt){
	volatile int counter = 0;
	while(counter < delay_cnt)
	{
		counter++;
	}
}

void GPIO_Write_Pin(GPIO_TypeDef *pGPIO_Type, unsigned short pin, GPIO_PinState state){
	unsigned int temp = 0x00U;
	unsigned int reg = 0x00U;
	unsigned int mode = 0x00u;
	//ODR
	reg = pGPIO_Type->ODR;
	temp = ~(GPIO_1BIT_POS_MASK << pin);
	reg &= temp;
	mode = state << pin;
	pGPIO_Type->ODR = reg|mode;
}

void GPIO_Init(GPIO_TypeDef *pGPIO_Type, unsigned short pin, GPIO_TypeDef *initVal){

	unsigned int position = pin;
	unsigned int temp = 0x00U;
	unsigned int reg = 0x00U;
	unsigned int mode = 0x00u;
	
	//PA5 Mode
	reg = pGPIO_Type -> MODER;
	temp = ~(GPIO_2BIT_POS_MASK << (position*2U)); //0xFFFFF3FF
	reg &= temp;
	mode = GPIO_MODE_OUTPUT << (position*2U);
	reg |= mode;
	pGPIO_Type->MODER = reg;
	
	//OTYPER
	reg = pGPIO_Type->OTYPER;
	temp = ~(GPIO_1BIT_POS_MASK << position);
	reg &= temp;
	mode = GPIO_OUTPUT_TYPE_0 << position;
	reg|=mode;
	pGPIO_Type->OTYPER = reg;
	
	//OSPEEDR
	reg = pGPIO_Type->OSPEEDR;
	temp = ~(GPIO_2BIT_POS_MASK << (position*2U)); //0xFFFFF3FF
	reg &= temp;
	mode = GPIO_SPEED_FREQ_VERY_HIGH << (position*2U); //very high mode - 2bit 0x00000C00
	reg |= mode;
	pGPIO_Type->OSPEEDR = reg;
	
	//OPUPDR
	reg = pGPIO_Type->PUPDR;
	temp = ~(0x03U << (position*2U)); //0xFFFFF3FF
	reg &= temp;
	mode = 0x0U << (position*2U);
	reg|=mode;
	pGPIO_Type->PUPDR = reg;
	
}
