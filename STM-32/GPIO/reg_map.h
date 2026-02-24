#ifndef __REG_MAP_H__
#define __REG_MAP_H__

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

#endif
