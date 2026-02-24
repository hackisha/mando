#define PERIPH_BASE				(0x40000000UL)
#define AHBPERIPH_BASE		(PERIPH_BASE + 0x00020000UL)
#define RCC_BASE					(AHBPERIPH_BASE + 0x00001000UL)
#define RCC_GPIOA					*((volatile unsigned int*)(RCC_BASE + 0x0000002CUL))

#define GPIO_PA5PIN_BASE	(unsigned int)0x50000000U
#define GPIO_PA5PIN_MODE	(*((volatile unsigned int*)GPIO_PA5PIN_BASE))
#define GPIO_PA5PIN_OTYPE	(*((volatile unsigned int*)(GPIO_PA5PIN_BASE+0x00000004UL)))
#define GPIO_PA5PIN_OSPEEDR	(*((volatile unsigned int*)(GPIO_PA5PIN_BASE+0x00000008UL)))
#define GPIO_PA5PIN_OPUPDR	(*((volatile unsigned int*)(GPIO_PA5PIN_BASE+0x0000000CUL)))
#define GPIO_PA5PIN_IDR	(*((volatile unsigned int*)(GPIO_PA5PIN_BASE+0x00000010UL)))
#define GPIO_PA5PIN_ODR	(*((volatile unsigned int*)(GPIO_PA5PIN_BASE+0x00000014UL)))

// PA8? ?? GPIOA ????? ?? ??? ?? ??
#define GPIO_PA8PIN_ODR   GPIO_PA5PIN_ODR
	
//define Masking
#define GPIO_2BIT_POS_MASK		((unsigned int)0x00000003U)
#define GPIO_1BIT_POS_MASK		((unsigned int)0x00000001U)
#define GPIO_PIN_5_POS				5
#define GPIO_PIN_8_POS				8

//funcs
void delay(unsigned int delay_cnt);

int main(void)
{
	unsigned int pos5 = GPIO_PIN_5_POS;
	unsigned int pos8 = GPIO_PIN_8_POS;
	unsigned int temp = 0x00U;
	unsigned int reg_val = 0x00U;
	unsigned int reg = 0x00U;
	
	//RCC-GPIOA
	reg = RCC_GPIOA;
	RCC_GPIOA = (unsigned int)(reg|0x01U);
	
	//PA5 & PA8 Mode
	reg = GPIO_PA5PIN_MODE;
	reg &= ~(GPIO_2BIT_POS_MASK << (pos5*2U));
	reg &= ~(GPIO_2BIT_POS_MASK << (pos8*2U));
	// GPO Mode: 01
	reg |= (0x01U << (pos5*2U));
	reg |= (0x01U << (pos8*2U));
	GPIO_PA5PIN_MODE = reg;
	
	//PA5 & PA8 OTYPER
	reg = GPIO_PA5PIN_OTYPE;
	reg &= ~(GPIO_1BIT_POS_MASK << pos5);
	reg &= ~(GPIO_1BIT_POS_MASK << pos8);
	GPIO_PA5PIN_OTYPE = reg;
	
	//PA5 & PA8 OSPEEDR
	reg = GPIO_PA5PIN_OSPEEDR;
	reg &= ~(GPIO_2BIT_POS_MASK << (pos5*2U));
	reg &= ~(GPIO_2BIT_POS_MASK << (pos8*2U));
	reg |= (0x03U << (pos5*2U));
	reg |= (0x03U << (pos8*2U));
	GPIO_PA5PIN_OSPEEDR = reg;
	
	//PULL UP/DOWN
	reg = GPIO_PA5PIN_OPUPDR;
	reg &= ~(GPIO_2BIT_POS_MASK << (pos5*2U));
	reg &= ~(GPIO_2BIT_POS_MASK << (pos8*2U));

	unsigned int toggle_mask = (1U << pos5) | (1U << pos8);
	reg = GPIO_PA5PIN_ODR & ~toggle_mask;
	
	reg_val = (1U << pos5); 
	
	while (1)
	{

		GPIO_PA5PIN_ODR = reg | reg_val;
		
		delay(0x200000);
		
		reg_val = ~reg_val & toggle_mask;
	}
}

void delay(unsigned int delay_cnt){
	volatile int counter = 0;
	while(counter < delay_cnt)
	{
		counter++;
	}
}
