#include "chip.h"
#include "ads1248.h"

static SSP_ConfigFormat 			ssp_format;
static uint8_t								rx_buf[BUFFER_SIZE];
static uint8_t								tx_buf[BUFFER_SIZE];
static volatile uint8_t				flag200ms;

/**********************************************************************************************/
/**********************************INTERRUPT FUNCTIONS******************************************/
/**********************************************************************************************/

//TO DO: Add interrupt routines
void FLEX_INT0_IRQHandler(void)
{
	Chip_PININT_ClearIntStatus(LPC_PININT, PININTCH(0));
}

void FLEX_INT1_IRQHandler(void)
{
	Chip_PININT_ClearIntStatus(LPC_PININT, PININTCH(1));
}

/**********************************************************************************************/
/************************************STATIC FUNCTIONS******************************************/
/**********************************************************************************************/
static uint32_t abs(int32_t data)
{
	if(data >= 0)
	{
		return data;
	}
	else
	{
		return (-1)*data;
	}
}

static void Chip_ADS1248_BufferInit()
{
	int i = 0;
	
	for(i = 0; i < BUFFER_SIZE; i++)
	{
		rx_buf[i] = 0x00;
		tx_buf[i] = 0x00;
	}
}


static int32_t GetTemperature(uint32_t data)
{
	uint32_t first, last, middle;
	
	if(data < 2893443)
	{
		return -30;
	}
	else if(data > 8106557)
	{
		return 400;
	}
	
	first = 0;
	last = LUT_SIZE -1;
	middle = (first+last)/2;
	
	while(first < last)
	{				
		if(TempLUT[middle] < data)
		{
			first = middle+1;
		}
		else if(TempLUT[middle] == data)
		{
			return middle;
		}
		else
		{
			last = middle-1;
		}
		
		middle = (first+last)/2;
	}
	
	if(abs(TempLUT[first-1]-data) < abs(TempLUT[first]-data))
	{
		return (first-1)-LUT_OFFSET;
	}
	else if(abs(TempLUT[first]-data) < abs(TempLUT[first+1]-data))
	{
		return first-LUT_OFFSET;
	}
	else
	{
		return (first+1)-LUT_OFFSET;
	}
}


/**********************************************************************************************/
/************************************PUBLIC FUNCTIONS******************************************/
/**********************************************************************************************/

void Chip_ADS1248_Init()
{
	Chip_SSP_DeInit(ADS_SSP);																													//Clear previous setup
	Chip_GPIO_Init(LPC_GPIO);																													//Init GPIO
	
	Chip_Clock_EnablePeriphClock(SYSCTL_CLOCK_IOCON);
	
	Chip_IOCON_PinMuxSet(LPC_IOCON, ADS_SCLK, IOCON_FUNC2); 													//SCLK
	Chip_IOCON_PinMuxSet(LPC_IOCON, ADS_MOSI, IOCON_FUNC2); 													//MOSI
	Chip_IOCON_PinMuxSet(LPC_IOCON, ADS_MISO, IOCON_FUNC2); 													//MISO
	Chip_IOCON_PinMuxSet(LPC_IOCON, ADS_nSSEL1, IOCON_FUNC0 | IOCON_MODE_PULLUP);			
	Chip_IOCON_PinMuxSet(LPC_IOCON, ADS_START1, IOCON_FUNC0 | IOCON_MODE_PULLUP); 		
	Chip_IOCON_PinMuxSet(LPC_IOCON, ADS_nRESET1,IOCON_FUNC0	| IOCON_MODE_PULLUP);
	Chip_IOCON_PinMuxSet(LPC_IOCON, ADS_nSSEL0, IOCON_FUNC0 | IOCON_MODE_PULLUP);			
	Chip_IOCON_PinMuxSet(LPC_IOCON, ADS_START0, IOCON_FUNC0 | IOCON_MODE_PULLUP); 		
	Chip_IOCON_PinMuxSet(LPC_IOCON, ADS_nRESET0,IOCON_FUNC0	| IOCON_MODE_PULLUP);
	Chip_IOCON_PinMuxSet(LPC_IOCON, ADS_nDRDY0, IOCON_FUNC0 | IOCON_MODE_PULLUP);
	Chip_IOCON_PinMuxSet(LPC_IOCON, ADS_nDRDY1, IOCON_FUNC0 | IOCON_MODE_PULLUP);
	
	Chip_GPIO_SetPinDIROutput(LPC_GPIO, ADS_nSSEL1);
	Chip_GPIO_SetPinDIROutput(LPC_GPIO, ADS_START1);
	Chip_GPIO_SetPinDIROutput(LPC_GPIO, ADS_nRESET1);	
	Chip_GPIO_SetPinDIROutput(LPC_GPIO, ADS_nSSEL0);
	Chip_GPIO_SetPinDIROutput(LPC_GPIO, ADS_START0);
	Chip_GPIO_SetPinDIROutput(LPC_GPIO, ADS_nRESET0);
	Chip_GPIO_SetPinDIRInput(LPC_GPIO,  ADS_nDRDY0);
	Chip_GPIO_SetPinDIRInput(LPC_GPIO,  ADS_nDRDY1);
	
	Chip_GPIO_SetPinOutHigh(LPC_GPIO, ADS_nSSEL1);
	Chip_GPIO_SetPinOutHigh(LPC_GPIO, ADS_nRESET1);
	Chip_GPIO_SetPinOutHigh(LPC_GPIO, ADS_START1);
	Chip_GPIO_SetPinOutHigh(LPC_GPIO, ADS_nSSEL0);
	Chip_GPIO_SetPinOutHigh(LPC_GPIO, ADS_nRESET0);
	Chip_GPIO_SetPinOutHigh(LPC_GPIO, ADS_START0);
			
	Chip_Clock_EnablePeriphClock(SYSCTL_CLOCK_PINT);
	Chip_SYSCTL_SetPinInterrupt(0, ADS_nDRDY0);
	Chip_PININT_SetPinModeEdge(LPC_PININT, PININTCH(0));
	Chip_PININT_EnableIntLow(LPC_PININT, PININTCH(0));
	Chip_SYSCTL_EnablePINTWakeup(0);
			
	Chip_Clock_EnablePeriphClock(SYSCTL_CLOCK_PINT);
	Chip_SYSCTL_SetPinInterrupt(1, ADS_nDRDY1);
	Chip_PININT_SetPinModeEdge(LPC_PININT, PININTCH(1));
	Chip_PININT_EnableIntLow(LPC_PININT, PININTCH(1));
	Chip_SYSCTL_EnablePINTWakeup(1);
		
	Chip_SSP_Init(ADS_SSP);	
	ssp_format.frameFormat = SSP_FRAMEFORMAT_SPI;																			//SPI Frame
	ssp_format.bits = SSP_BITS_8;																											//8bits 
	ssp_format.clockMode = SSP_CLOCK_CPHA1_CPOL0;																			//CPHA=1, CPOL=0	
	Chip_SSP_SetFormat(ADS_SSP, ssp_format.bits, ssp_format.frameFormat, ssp_format.clockMode);		
	Chip_SSP_Set_Mode(ADS_SSP, SSP_MODE_MASTER);
	
	Chip_SSP_SetClockRate(ADS_SSP, 1, 16);		
	Chip_Clock_SetSSP1ClockDiv(1);																										
	
	Chip_SSP_Enable(ADS_SSP);
}

uint8_t Chip_ADS1248_ReadRegister(uint8_t chip, uint8_t address)
{
	Chip_SSP_DATA_SETUP_T	xf_setup;
	
	xf_setup.length = BUFFER_SIZE;
	xf_setup.rx_cnt = 0;
	xf_setup.tx_cnt = 0;
	xf_setup.rx_data = rx_buf;
	xf_setup.tx_data = tx_buf;
	
	Chip_ADS1248_BufferInit();
	tx_buf[0] = (RREG | address);																											//Register address 0010 rrrr, 'r' being register address
	tx_buf[1] = 0;																																		//Num_of_bytes - 1
	
	if(chip == CHIP_U1)
	{
		Chip_GPIO_SetPinOutLow(LPC_GPIO, ADS_nSSEL0);																		  //Chip select Low(0)
		
		Chip_SSP_RWFrames_Blocking(ADS_SSP, &xf_setup);	
	
		Chip_GPIO_SetPinOutHigh(LPC_GPIO, ADS_nSSEL0);																		//Chip select High(1)
	}
	else
	{
		Chip_GPIO_SetPinOutLow(LPC_GPIO, ADS_nSSEL1);																		  //Chip select Low(0)
		
		Chip_SSP_RWFrames_Blocking(ADS_SSP, &xf_setup);	
	
		Chip_GPIO_SetPinOutHigh(LPC_GPIO, ADS_nSSEL1);																		//Chip select High(1)
	}
		
	return rx_buf[2];																																	//during transmission 2 rcv. bytes are junk, third is the reg. value
}

void Chip_ADS1248_WriteRegister(uint8_t chip, uint8_t address, uint8_t value)
{
	Chip_SSP_DATA_SETUP_T	xf_setup;
	
	xf_setup.length = BUFFER_SIZE;
	xf_setup.rx_cnt = 0;
	xf_setup.tx_cnt = 0;
	xf_setup.rx_data = rx_buf;
	xf_setup.tx_data = tx_buf;
	
	Chip_ADS1248_BufferInit();
	tx_buf[0] = (WREG | address);																											//Register address 0010 rrrr, 'r' being register address
	tx_buf[1] = 0;																																		//Num_of_bytes - 1
	tx_buf[2] = value;																																//Register value
	
	if(chip == CHIP_U1)
	{
		Chip_GPIO_SetPinOutLow(LPC_GPIO, ADS_nSSEL0);																		  //Chip select Low(0)
		
		Chip_SSP_RWFrames_Blocking(ADS_SSP, &xf_setup);	
	
		Chip_GPIO_SetPinOutHigh(LPC_GPIO, ADS_nSSEL0);																		//Chip select High(1)
	}
	else
	{
		Chip_GPIO_SetPinOutLow(LPC_GPIO, ADS_nSSEL1);																		  //Chip select Low(0)
		
		Chip_SSP_RWFrames_Blocking(ADS_SSP, &xf_setup);	
	
		Chip_GPIO_SetPinOutHigh(LPC_GPIO, ADS_nSSEL1);																		//Chip select High(1)
	}
		
	return;
}

void Chip_ADS1248_Selfocal(uint8_t chip)
{	
	Chip_SSP_DATA_SETUP_T	xf_setup;
	
	if(chip == CHIP_U1)
	{		
		Chip_ADS1248_BufferInit();		
		
		xf_setup.length = BUFFER_SIZE;
		xf_setup.rx_cnt = 0;
		xf_setup.tx_cnt = 0;
		xf_setup.rx_data = rx_buf;
		xf_setup.tx_data = tx_buf;
		tx_buf[0] = SYSGCAL;	
		
		Chip_GPIO_SetPinOutLow(LPC_GPIO, ADS_nSSEL0);
		
		Chip_SSP_RWFrames_Blocking(ADS_SSP, &xf_setup);
		
		NVIC_EnableIRQ(PIN_INT0_IRQn);
		
		while((Chip_PININT_GetIntStatus(LPC_PININT) && PININTCH(0)) != 1);
		Chip_PININT_ClearIntStatus(LPC_PININT, PININTCH(0));		
		
		NVIC_DisableIRQ(PIN_INT0_IRQn);																				 		
				
		Chip_GPIO_SetPinOutHigh(LPC_GPIO, ADS_nSSEL0);														
			
	}
	else
	{						
		Chip_ADS1248_BufferInit();		
		
		xf_setup.length = BUFFER_SIZE;
		xf_setup.rx_cnt = 0;
		xf_setup.tx_cnt = 0;
		xf_setup.rx_data = rx_buf;
		xf_setup.tx_data = tx_buf;				
		tx_buf[0] = SYSGCAL;	
		
		Chip_GPIO_SetPinOutLow(LPC_GPIO, ADS_nSSEL1);
		
		Chip_SSP_RWFrames_Blocking(ADS_SSP, &xf_setup);
		
		NVIC_EnableIRQ(PIN_INT1_IRQn);
		
		while((Chip_PININT_GetIntStatus(LPC_PININT) && PININTCH(1)) != 1);
		Chip_PININT_ClearIntStatus(LPC_PININT, PININTCH(1));		
		
		NVIC_DisableIRQ(PIN_INT1_IRQn);	
				
		Chip_GPIO_SetPinOutHigh(LPC_GPIO, ADS_nSSEL1);
		
	}
	
	return;
}

/*********************************************************************/

int32_t Chip_ADS1248_GetTemperature(uint8_t chip, uint8_t rtd)
{
	uint32_t temperatura_raw = 0;
	int32_t temperatura = 0;
	Chip_SSP_DATA_SETUP_T	xf_setup;
	
	if(chip == CHIP_U1)
	{			
		if(rtd == RTD_1)
		{
			Chip_ADS1248_WriteRegister(CHIP_U1, MUX0, 0x01);
			Chip_ADS1248_WriteRegister(CHIP_U1, VBIAS, 0x00);
			Chip_ADS1248_WriteRegister(CHIP_U1, MUX1, 0x30);
			Chip_ADS1248_WriteRegister(CHIP_U1, SYS0, 0x60);
			Chip_ADS1248_WriteRegister(CHIP_U1, IDAC0, 0x03);
			Chip_ADS1248_WriteRegister(CHIP_U1, IDAC1, 0xf8);
		}
		else
		{
//			Chip_ADS1248_WriteRegister(CHIP_U1, MUX0, 0x13);
//			Chip_ADS1248_WriteRegister(CHIP_U1, VBIAS, 0x00);
//			Chip_ADS1248_WriteRegister(CHIP_U1, MUX1, 0x30);
//			Chip_ADS1248_WriteRegister(CHIP_U1, SYS0, 0x40);
//			Chip_ADS1248_WriteRegister(CHIP_U1, IDAC0, 0x03);
//			Chip_ADS1248_WriteRegister(CHIP_U1, IDAC1, 0xf9);
		}
		
		temperatura_raw = Chip_ADS1248_ReadRegister(CHIP_U1, MUX0);
		temperatura_raw = Chip_ADS1248_ReadRegister(CHIP_U1, IDAC1);
		
		Chip_ADS1248_BufferInit();		
		
		xf_setup.length = BUFFER_SIZE;
		xf_setup.rx_cnt = 0;
		xf_setup.tx_cnt = 0;
		xf_setup.rx_data = rx_buf;
		xf_setup.tx_data = tx_buf;
		tx_buf[0] = RDATA;	
		
		Chip_GPIO_SetPinOutLow(LPC_GPIO, ADS_START0);
		NVIC_EnableIRQ(PIN_INT0_IRQn);
		
		while((Chip_PININT_GetIntStatus(LPC_PININT) && PININTCH(0)) != 1);
		Chip_PININT_ClearIntStatus(LPC_PININT, PININTCH(0));		
		
		NVIC_DisableIRQ(PIN_INT0_IRQn);
		
		Chip_GPIO_SetPinOutLow(LPC_GPIO, ADS_nSSEL0);																		  //Chip select Low(0)		
		Chip_SSP_RWFrames_Blocking(ADS_SSP, &xf_setup);		
		Chip_GPIO_SetPinOutHigh(LPC_GPIO, ADS_nSSEL0);																		//Chip select High(1)	
			
		Chip_GPIO_SetPinOutHigh(LPC_GPIO, ADS_START0);
	}
	else
	{		
		if(rtd == RTD_3)
		{
//			Chip_ADS1248_WriteRegister(CHIP_U3, MUX0, 0x01);
//			Chip_ADS1248_WriteRegister(CHIP_U3, VBIAS, 0x00);
//			Chip_ADS1248_WriteRegister(CHIP_U3, MUX1, 0x30);
//			Chip_ADS1248_WriteRegister(CHIP_U3, SYS0, 0x40);
//			Chip_ADS1248_WriteRegister(CHIP_U3, IDAC0, 0x03);
//			Chip_ADS1248_WriteRegister(CHIP_U3, IDAC1, 0xf8);		
		}
		else
		{
			Chip_ADS1248_WriteRegister(CHIP_U3, MUX0, 0x13);
			Chip_ADS1248_WriteRegister(CHIP_U3, VBIAS, 0x00);
			Chip_ADS1248_WriteRegister(CHIP_U3, MUX1, 0x30);
			Chip_ADS1248_WriteRegister(CHIP_U3, SYS0, 0x60);
			Chip_ADS1248_WriteRegister(CHIP_U3, IDAC0, 0x03);
			Chip_ADS1248_WriteRegister(CHIP_U3, IDAC1, 0xf9);	
		}
					
		Chip_ADS1248_BufferInit();		
		
		xf_setup.length = BUFFER_SIZE;
		xf_setup.rx_cnt = 0;
		xf_setup.tx_cnt = 0;
		xf_setup.rx_data = rx_buf;
		xf_setup.tx_data = tx_buf;				
		tx_buf[0] = RDATA;	
		
		Chip_GPIO_SetPinOutLow(LPC_GPIO, ADS_START1);
		NVIC_EnableIRQ(PIN_INT1_IRQn);
		
		while((Chip_PININT_GetIntStatus(LPC_PININT) && PININTCH(1)) != 1);
		Chip_PININT_ClearIntStatus(LPC_PININT, PININTCH(1));		
		
		NVIC_DisableIRQ(PIN_INT1_IRQn);
		
		Chip_GPIO_SetPinOutLow(LPC_GPIO, ADS_nSSEL1);																		  //Chip select Low(0)		
		Chip_SSP_RWFrames_Blocking(ADS_SSP, &xf_setup);		
		Chip_GPIO_SetPinOutHigh(LPC_GPIO, ADS_nSSEL1);
		
		Chip_GPIO_SetPinOutHigh(LPC_GPIO, ADS_START1);
	}
	
	
	temperatura_raw = ((rx_buf[1] << 16) & 0x00ff0000) | 
								((rx_buf[2] << 8) & 0x0000ff00) | 
								(rx_buf[3] & 0xff);
	temperatura = GetTemperature(temperatura_raw);	
	
	return temperatura;
}
