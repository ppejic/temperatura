#include "main.h"
#include "ads1248.h"
#include "app_usbd_cfg.h"
#include "cdc_usb.h"
#include "cdc_vcom.h"

//osThreadDef(threadX, osPriorityNormal, 1, 0);

void TIMER16_0_IRQHandler()
{
	if(Chip_TIMER_MatchPending(LPC_TIMER16_0, 0))
	{
		Chip_TIMER_ClearMatch(LPC_TIMER16_0, 0);
		LPC_TIMER16_0->TC = 0;
		Chip_GPIO_SetPinToggle(LPC_GPIO, 1, 31);
	}
}

int main()
{
	uint8_t idac = 0;
				
	Chip_ADS1248_Init();
	USB_Periph_Init();		
	
//	Chip_Clock_EnablePeriphClock(SYSCTL_CLOCK_CT16B0);
//	Chip_IOCON_PinMuxSet(LPC_IOCON, 1, 31, IOCON_FUNC0);
//	Chip_GPIO_SetPinDIROutput(LPC_GPIO, 1, 31);
//	Chip_GPIO_SetPinOutHigh(LPC_GPIO, 1, 31);
//	
//	Chip_TIMER_Reset(LPC_TIMER16_0);
//	Chip_TIMER_PrescaleSet(LPC_TIMER16_0, 1000);
//	Chip_TIMER_SetMatch(LPC_TIMER16_0, 0, 10000);
//	Chip_TIMER_MatchEnableInt(LPC_TIMER16_0, 0);	
//	
//	Chip_TIMER_Enable(LPC_TIMER16_0);
//	NVIC_EnableIRQ(TIMER_16_0_IRQn);
	
	while(1)
	{
//		Chip_ADS1248_WriteRegister(SYS0, 0x70);
//		idac = Chip_ADS1248_ReadRegister(SYS0);
//		idac = 0;
//		
//		Chip_ADS1248_WriteRegister(MUX0, 0x03);
//		idac = Chip_ADS1248_ReadRegister(MUX0);
//		idac = 0;
		__WFI();
		if(idac) __NOP();
	}
	
	return 0;
}
