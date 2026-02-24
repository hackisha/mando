#define PERIPH_BASE				(0x40000000UL)
#define AHBPERIPH_BASE		(PERIPH_BASE + 0x00020000UL)
#define RCC_BASE					(AHBPERIPH_BASE + 0x00001000UL)
#define RCC_GPIOA					*((volatile unsigned int*)(RCC_BASE + 0x0000002CUL))

#define GPIO_PA8PIN_BASE	(unsigned int)0x80000000U
#define GPIO_PA8PIN_MODE	(*((volatile unsigned int*)GPIO_PA5PIN_BASE))
#define GPIO_PA8PIN_OTYPE	(*((volatile unsigned int*)(GPIO_PA5PIN_BASE+0x00000004UL)))
#define GPIO_PA8PIN_OSPEEDR	(*((volatile unsigned int*)(GPIO_PA5PIN_BASE+0x00000008UL)))
#define GPIO_PA8PIN_OPUPDR	(*((volatile unsigned int*)(GPIO_PA5PIN_BASE+0x0000000CUL)))
#define GPIO_PA8PIN_IDR	(*((volatile unsigned int*)(GPIO_PA5PIN_BASE+0x00000010UL)))
#define GPIO_PA8PIN_ODR	(*((volatile unsigned int*)(GPIO_PA5PIN_BASE+0x00000014UL)))

#define GPIO_PA5PIN_BASE	(unsigned int)0x50000000U
#define GPIO_PA5PIN_MODE	(*((volatile unsigned int*)GPIO_PA5PIN_BASE))
#define GPIO_PA5PIN_OTYPE	(*((volatile unsigned int*)(GPIO_PA5PIN_BASE+0x00000004UL)))
#define GPIO_PA5PIN_OSPEEDR	(*((volatile unsigned int*)(GPIO_PA5PIN_BASE+0x00000008UL)))
#define GPIO_PA5PIN_OPUPDR	(*((volatile unsigned int*)(GPIO_PA5PIN_BASE+0x0000000CUL)))
#define GPIO_PA5PIN_IDR	(*((volatile unsigned int*)(GPIO_PA5PIN_BASE+0x00000010UL)))
#define GPIO_PA5PIN_ODR	(*((volatile unsigned int*)(GPIO_PA5PIN_BASE+0x00000014UL)))
	
//define Masking
#define GPIO_2BIT_POS_MASK		((unsigned int)0x00000003U)
#define GPIO_1BIT_POS_MASK		((unsigned int)0x00000001U)
#define GPIO_PIN_5_POS				5
#define GPIO_PIN_8_POS				8
//funcs
void delay(unsigned int delay_cnt);


int main(void)
{
	unsigned int position = GPIO_PIN_5_POS;
	unsigned int temp = 0x00U;
	unsigned int reg_val = 0x00U;
	unsigned int reg = 0x00U;
	
	//RCC-GPIOA
	reg = RCC_GPIOA;
	RCC_GPIOA = (unsigned int)(reg|0x01U);
	
	//PA5 Mode
	reg = GPIO_PA5PIN_MODE;
	temp = ~(GPIO_2BIT_POS_MASK << (position*2U)); //0xFFFFF3FF
	reg &= temp;
	// GPO Mode: 01
	reg_val = 0x01U << (position*2U); //output type - 1bit
	reg |= reg_val;
	GPIO_PA5PIN_MODE = reg;
	
	//PA5 OTYPER
	//GPIO_PA5PIN_OTYPE = 0;
	reg = GPIO_PA5PIN_OTYPE;
	temp = ~(GPIO_1BIT_POS_MASK << position); //~0x20 ==> 0xFFFFFFDF
	reg &= temp;
	reg_val = 0x0U << position;
	reg |= reg_val;
	GPIO_PA5PIN_OTYPE = reg;
	
	//PA5 OSPEEDR
	//GPIO_PA5PIN_OSPEEDR = (unsigned int)0x0C000C00;
	reg = GPIO_PA5PIN_OSPEEDR;
	temp = ~(GPIO_2BIT_POS_MASK << (position*2U)); //0xFFFFF3FF
	reg &= temp;
	reg_val = 0x03U << (position*2U); //very high mode - 2bit 0x00000C00
	reg|=reg_val;
	GPIO_PA5PIN_OSPEEDR = reg;
	
	//PULL UP/DOWN
	//GPIO PA5PIN_OPUPDR = (unsigned int)0x24000000;
	reg = GPIO_PA5PIN_OPUPDR;
	temp = ~(GPIO_2BIT_POS_MASK << (position*2U)); //0xFFFFF3FF
	reg &= temp;
	reg_val = 0x0U << (position*2U); //No pull up - pull down - 2bit 0x24000000
	reg |= reg_val;
	GPIO_PA5PIN_OPUPDR = reg;
	
	//ODR - 1bit
	//GPIO_PA5PIN_ODR = (unsigned char)0x20;
	reg = GPIO_PA5PIN_ODR;
	//~0x20 ==> 0xFFFFFFDF
	temp = ~(GPIO_1BIT_POS_MASK << position);
	reg &= temp;
	
	//LED On value
	reg_val = 0x01 << position;
	
	GPIO_PA5PIN_ODR = reg|reg_val;
	
	while (1)
		{
			//ODR
			//LEDL Off Value
			reg_val = ~reg_val&(GPIO_1BIT_POS_MASK << position);
			GPIO_PA5PIN_ODR = reg|reg_val;
		
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
