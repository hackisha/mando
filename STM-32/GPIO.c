#define PERIPH_BASE				(0x40000000UL)
#define AHBPERIPH_BASE		(PERIPH_BASE + 0x00020000UL)
#define RCC_BASE					(AHBPERIPH_BASE + 0x00001000UL)
#define RCC_IOPENR				*((volatile unsigned int*)(RCC_BASE + 0x0000002CUL))
#define RCC_GPIOA_EN 			(unsigned int)0x00000001U


#define GPIOA_BASE				((unsigned int)0x50000000UL)
#define GPIOA							(GPIO_TypeDef*) GPIOA_BASE
#define GPIO_PA5PIN_BASE	(unsigned int)0x50000000U
#define GPIO_PA5PIN_MODE	(*((volatile unsigned int*)GPIO_PA5PIN_BASE))
#define GPIO_PA5PIN_OTYPE	(*((volatile unsigned int*)(GPIO_PA5PIN_BASE+0x00000004UL)))
#define GPIO_PA5PIN_OSPEEDR	(*((volatile unsigned int*)(GPIO_PA5PIN_BASE+0x00000008UL)))
#define GPIO_PA5PIN_OPUPDR	(*((volatile unsigned int*)(GPIO_PA5PIN_BASE+0x0000000CUL)))
#define GPIO_PA5PIN_IDR	(*((volatile unsigned int*)(GPIO_PA5PIN_BASE+0x00000010UL)))
#define GPIO_PA5PIN_ODR	(*((volatile unsigned int*)(GPIO_PA5PIN_BASE+0x00000014UL)))

#define GPIO_PA8PIN_ODR   GPIO_PA5PIN_ODR
	
//define Masking
#define GPIO_2BIT_POS_MASK		((unsigned int)0x00000003U)
#define GPIO_1BIT_POS_MASK		((unsigned int)0x00000001U)
#define GPIO_PIN_5_POS				5
#define GPIO_PIN_8_POS				8

#define GPIO_MODE_OUTPUT			((unsigned int)0x00000001U)
#define GPIO_OUTPUT_TYPE_0		((unsigned int)0x00000000U)
#define GPIO_GPIO_NOPUPD			((unsigned int)0x00000000U)
#define GPIO_SPEED_FREQ_VERY_HIGH	((unsigned int)0x00000003U)
#define LED2_ON 							((unsigned int)0x00000001U)
#define LED2_OFF							((unsigned int)0x00000000U)
	

//funcs
void delay(unsigned int delay_cnt);

//Structure and Array

typedef struct{
	volatile unsigned int MODER;
	volatile unsigned int OTYPER;
	volatile unsigned int OSPEEDR;
	volatile unsigned int PUPDR;
	volatile unsigned int IDR;
	volatile unsigned int ODR;
	volatile unsigned int BSRR;
	volatile unsigned int LCKR;
	volatile unsigned int AFR[2];
	volatile unsigned int BRR;
}GPIO_TypeDef;


int main(void)
{

	unsigned int position = GPIO_PIN_5_POS;
	unsigned int temp = 0x00U;
	unsigned int reg_val = 0x00U;
	unsigned int reg = 0x00U;
	unsigned int mode = 0x00u;
	GPIO_TypeDef*GPIOA_reg = GPIOA;
	
	//RCC-GPIOA
	RCC_IOPENR |= RCC_GPIOA_EN;
	
	
	//PA5 Mode
	reg = GPIOA_reg -> MODER;
	temp = ~(GPIO_2BIT_POS_MASK << (position*2U)); //0xFFFFF3FF
	reg &= temp;
	mode = GPIO_MODE_OUTPUT << (position*2U);
	reg |= mode;
	GPIOA_reg->MODER = reg;
	
	//OTYPER
	reg = GPIOA_reg->OTYPER;
	temp = ~(GPIO_1BIT_POS_MASK << position);
	reg &= temp;
	mode = GPIO_OUTPUT_TYPE_0 << position;
	reg|=mode;
	GPIOA_reg->OTYPER = reg;
	//OSPEEDR
	reg = GPIOA_reg -> OSPEEDR;
	temp = ~(GPIO_2BIT_POS_MASK << (position*2U)); //0xFFFFF3FF
	reg &= temp;
	mode = GPIO_SPEED_FREQ_VERY_HIGH << (position*2U); //very high mode - 2bit 0x00000C00
	reg |= mode;
	GPIOA_reg->OSPEEDR = reg;
	//OPUPDR
	reg = GPIOA_reg->PUPDR;
	temp = ~(0x03U << (position*2U)); //0xFFFFF3FF
	reg &= temp;
	mode = 0x0U << (position*2U);
	reg|=mode;
	GPIOA_reg->PUPDR = reg;
	
	//ODR
	reg = GPIOA_reg->ODR; //GPIO_PA5pin_odr
	temp = ~(GPIO_1BIT_POS_MASK << position);
	reg &= temp;
	mode = LED2_ON << position;
	GPIOA_reg->ODR = reg | mode;
	
	while (1)
	{
		delay(0x20000);
		mode = ~mode&(GPIO_1BIT_POS_MASK << position);
		GPIOA_reg->ODR = reg|mode;
	}
}

void delay(unsigned int delay_cnt){
	volatile int counter = 0;
	while(counter < delay_cnt)
	{
		counter++;
	}
}
