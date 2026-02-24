int main(void)
{
    *((unsigned int*)0x4002102C) = (unsigned int)0x01;
    *((unsigned int*)0x50000000U) = 0xEBFFF4FF;
    *((unsigned int*)(0x50000000U + 0x04U)) = 0;
    *((unsigned int*)(0x50000000U + 0x08U)) = (unsigned int)0x0C000C00;
    *((unsigned int*)(0x50000000U + 0x0CU)) = (unsigned int)0x24000000;

		volatile int counter = 0;
    while (1)
    {
			*((unsigned int*)(0x50000000U + 0x00000014U)) = (unsigned int)0x20;
			
			counter = 0;
			while(counter < 100000)
			{
				counter++;
			}
			
			*((unsigned int*)(0x50000000U + 0x00000014U)) = (unsigned int)0x00;
			counter = 0;
			while(counter < 100000)
			{
				counter++;
			}
		}
}
