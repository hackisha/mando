void delay();

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
			*((unsigned int*)(0x50000000U + 0x00000014U)) = (unsigned int)0x20;
			delay();
			*((unsigned int*)(0x50000000U + 0x00000014U)) = (unsigned int)0x00;
			delay();
		}
}


void delay(){
	int volatile counter = 0;
	
	while(counter < 100000) // delay loop
	{
		counter++;
	}
}
