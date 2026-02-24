#define PERIPH_BASE				(0x40000000UL)
#define AHBPERIPH_BASE		(PERIPH_BASE + 0x00020000UL)
#define RCC_BASE					(AHBPERIPH_BASE + 0x00001000UL)
#define RCC_IOPENR				*((volatile unsigned int*)(RCC_BASE + 0x0000002CUL))
#define RCC_GPIOA_EN 			(unsigned int)0x00000001U
#define RCC_GPIOB_EN 			(unsigned int)0x00000002U


#define GPIOA_BASE				((unsigned int)0x50000000UL)
#define GPIOA							(GPIO_TypeDef*) GPIOA_BASE
#define GPIOB_BASE				((unsigned int)0x50000400UL)
#define GPIOB							(GPIO_TypeDef*) GPIOB_BASE
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


typedef enum{
	GPIO_PIN_RESET = 0U,
	GPIO_PIN_SET
} GPIO_PinState;


//funcs
void delay(unsigned int delay_cnt);
void GPIO_Init(GPIO_TypeDef *pGPIO_Type, unsigned short pin, GPIO_TypeDef *initVal);
void GPIO_Write_Pin(GPIO_TypeDef *pGPIO_Type, unsigned short pin, GPIO_PinState state);


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


/*=================================functions================================*/
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
