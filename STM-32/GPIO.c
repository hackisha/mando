#define PERIPH_BASE				(0x40000000UL)
#define AHBPERIPH_BASE		(PERIPH_BASE + 0x00020000UL)
#define RCC_BASE					(AHBPERIPH_BASE + 0x00001000UL
#define RCC_GPIOA					*((volatile unsigned int*)(RCC_BASE + 0x0000002CUL))

#define GPIO_PA5PIN_BASE	(unsigned int)0x50000000U
#define GPIO_PA5PIN_MODE	(*((volatile unsigned int*)GPIO_PA5PIN_BASE))
#define GPIO_PA5PIN_OTYPE	(*((volatile unsigned int*)(GPIO_PA5PIN_BASE+0x00000004UL)))
#define GPIO_PA5PIN_OSPEEDR	(*((volatile unsigned int*)(GPIO_PA5PIN_BASE+0x00000008UL)))
#define GPIO_PA5PIN_OPUPDR	(*((volatile unsigned int*)(GPIO_PA5PIN_BASE+0x0000000CUL)))
#define GPIO_PA5PIN_IDR	(*((volatile unsigned int*)(GPIO_PA5PIN_BASE+0x00000010UL)))
#define GPIO_PA5PIN_ODR	(*((volatile unsigned int*)(GPIO_PA5PIN_BASE+0x00000014UL)))
	
void delay(unsigned int delay_cnt);


int main(void)
{
	
	//RCC-GPIOA(GPIO's A port)
	*((unsigned int*)0x4002102C) = (unsigned int)0x01;
	
	//GPIOA-Reg
	*((unsigned int*)0x50000000U) = 0xEBFFF4FF;
	
	//OTYPER
	*((unsigned int*)(0x50000000U + 0x04U)) = 0;
	
	//OSPEEDR
	*((unsigned int*)(0x50000000U + 0x08U)) = (unsigned int)0x0C000C00;
	
	//PULL UP/DOWN
	*((unsigned int*)(0x50000000U + 0x0CU)) = (unsigned int)0x24000000;

	//ODR(OUT PUT DATA Register)
	*((unsigned int*)(0x50000000U + 0x00000014U)) = (unsigned int)0x20;
			

    while (1)
    {
			GPIO_PA5PIN_ODR = (unsigned char)0x20;
			delay(0x200000);
			GPIO_PA5PIN_ODR = (unsigned char)0x00;
			delay(0x200000);
		}
}


void delay(unsigned int delay_cnt){
	volatile int counter = 0;
	
	while(counter < delay_cnt) // delay loop
	{
		counter++;
	}
}
