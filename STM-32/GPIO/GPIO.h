#ifndef __GPIO_H__
#define __GPIO_H__

#include "reg_map.h"

void delay(unsigned int delay_cnt);
void GPIO_Init(GPIO_TypeDef *pGPIO_Type, unsigned short pin, GPIO_TypeDef *initVal);
void GPIO_Write_Pin(GPIO_TypeDef *pGPIO_Type, unsigned short pin, GPIO_PinState state);


#endif
