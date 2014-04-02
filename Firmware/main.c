#include "chip.h"
#include "ads1248.h"

const uint32_t OscRateIn = 12000000;

int main()
{
	uint8_t idac = 0;
			
	//Chip_ADS1248_Init();
		
	while(1)
	{
//		Chip_ADS1248_WriteRegister(SYS0, 0x70);
//		idac = Chip_ADS1248_ReadRegister(SYS0);
//		idac = 0;
//		
//		Chip_ADS1248_WriteRegister(MUX0, 0x03);
//		idac = Chip_ADS1248_ReadRegister(MUX0);
//		idac = 0;
		
		if(idac) __NOP();
	}
	
	return 0;
}
