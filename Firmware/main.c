//#include "main.h"
//#include "chip.h"
//#include "ads1248.h"
//#include "cmsis_os.h"

//osThreadDef(threadX, osPriorityNormal, 1, 0);

//void threadX (void const *argument) {
//  for (;;) {
//    /* Wait for completion of do-this */
//    osSignalWait(0x0004, osWaitForever); /* do-that */
//    /* Pause for 20 ms until signaling event to main thread */
//    osDelay(20);
//    /* Indicate to main thread completion of do-that */
//    osSignalSet(main_id, 0x0004);
//  }
//}

//void TIMER16_0_IRQHandler()
//{
//	if(Chip_TIMER_MatchPending(LPC_TIMER16_0, 0))
//	{
//		Chip_TIMER_ClearMatch(LPC_TIMER16_0, 0);
//		LPC_TIMER16_0->TC = 0;
//		Chip_GPIO_SetPinToggle(LPC_GPIO, 1, 31);
//	}
//}

//int main()
//{
//	uint8_t idac = 0;
//			
//	main_id = osThreadGetId();
//	
//	threadX_id = osThreadCreate(osThread(threadX), NULL);
//	
//	Chip_ADS1248_Init();
//		
////	Chip_Clock_EnablePeriphClock(SYSCTL_CLOCK_CT16B0);
////	Chip_IOCON_PinMuxSet(LPC_IOCON, 1, 31, IOCON_FUNC0);
////	Chip_GPIO_SetPinDIROutput(LPC_GPIO, 1, 31);
////	Chip_GPIO_SetPinOutHigh(LPC_GPIO, 1, 31);
////	
////	Chip_TIMER_Reset(LPC_TIMER16_0);
////	Chip_TIMER_PrescaleSet(LPC_TIMER16_0, 1000);
////	Chip_TIMER_SetMatch(LPC_TIMER16_0, 0, 10000);
////	Chip_TIMER_MatchEnableInt(LPC_TIMER16_0, 0);	
////	
////	Chip_TIMER_Enable(LPC_TIMER16_0);
////	NVIC_EnableIRQ(TIMER_16_0_IRQn);
//	
//	while(1)
//	{
////		Chip_ADS1248_WriteRegister(SYS0, 0x70);
////		idac = Chip_ADS1248_ReadRegister(SYS0);
////		idac = 0;
////		
////		Chip_ADS1248_WriteRegister(MUX0, 0x03);
////		idac = Chip_ADS1248_ReadRegister(MUX0);
////		idac = 0;
//		
//		if(idac) __NOP();
//	}
//	
//	return 0;
//}
