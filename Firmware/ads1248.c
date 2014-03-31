#include "chip.h"
#include "ads1248.h"

static SSP_ConfigFormat 			ssp_format;
static uint8_t								rx_buf[BUFFER_SIZE];
static uint8_t								tx_buf[BUFFER_SIZE];

static void Chip_ADS1248_BufferInit()
{
	int i = 0;
	
	for(i = 0; i < BUFFER_SIZE; i++)
	{
		rx_buf[i] = 0x00;
		tx_buf[i] = 0x00;
	}
}

void Chip_ADS1248_Init()
{
	Chip_SSP_DeInit(ADS_SSP);																													//Clear previous setup
	Chip_GPIO_Init(LPC_GPIO);																													//Init GPIO
	
	Chip_Clock_EnablePeriphClock(SYSCTL_CLOCK_IOCON);
	
	Chip_IOCON_PinMuxSet(LPC_IOCON, ADS_SCLK, IOCON_FUNC2); 													//SCLK
	Chip_IOCON_PinMuxSet(LPC_IOCON, ADS_MOSI, IOCON_FUNC2); 													//MOSI
	Chip_IOCON_PinMuxSet(LPC_IOCON, ADS_MISO, IOCON_FUNC2); 													//MISO
	Chip_IOCON_PinMuxSet(LPC_IOCON, ADS_nSSEL1, IOCON_FUNC0 | IOCON_MODE_PULLUP);			//nSSEL1, PULLUP
	Chip_IOCON_PinMuxSet(LPC_IOCON, ADS_START1, IOCON_FUNC0 | IOCON_MODE_PULLUP); 		
	Chip_IOCON_PinMuxSet(LPC_IOCON, ADS_nRESET1, IOCON_FUNC0	| IOCON_MODE_PULLUP);
	Chip_IOCON_PinMuxSet(LPC_IOCON, ADS_nSSEL0, IOCON_FUNC0 | IOCON_MODE_PULLUP);			
	Chip_IOCON_PinMuxSet(LPC_IOCON, ADS_START0, IOCON_FUNC0 | IOCON_MODE_PULLUP); 		
	Chip_IOCON_PinMuxSet(LPC_IOCON, ADS_nRESET0, IOCON_FUNC0	| IOCON_MODE_PULLUP);	
	
	Chip_GPIO_SetPinDIROutput(LPC_GPIO, ADS_nSSEL1);
	Chip_GPIO_SetPinDIROutput(LPC_GPIO, ADS_START1);
	Chip_GPIO_SetPinDIROutput(LPC_GPIO, ADS_nRESET1);	
	Chip_GPIO_SetPinDIROutput(LPC_GPIO, ADS_nSSEL0);
	Chip_GPIO_SetPinDIROutput(LPC_GPIO, ADS_START0);
	Chip_GPIO_SetPinDIROutput(LPC_GPIO, ADS_nRESET0);
	
	Chip_GPIO_SetPinOutHigh(LPC_GPIO, ADS_nSSEL1);
	Chip_GPIO_SetPinOutHigh(LPC_GPIO, ADS_nRESET1);
	Chip_GPIO_SetPinOutHigh(LPC_GPIO, ADS_START1);
	Chip_GPIO_SetPinOutHigh(LPC_GPIO, ADS_nSSEL0);
	Chip_GPIO_SetPinOutHigh(LPC_GPIO, ADS_nRESET0);
	Chip_GPIO_SetPinOutHigh(LPC_GPIO, ADS_START0);
		
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

uint8_t Chip_ADS1248_ReadRegister(uint8_t address)
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
	
	Chip_GPIO_SetPinOutLow(LPC_GPIO, ADS_nSSEL1);																		  //Chip select Low(0)
		
	Chip_SSP_RWFrames_Blocking(ADS_SSP, &xf_setup);	
	
	Chip_GPIO_SetPinOutHigh(LPC_GPIO, ADS_nSSEL1);																		//Chip select High(1)
		
	return rx_buf[2];																																	//during transmission 2 rcv. bytes are junk, third is the reg. value
}

void Chip_ADS1248_WriteRegister(uint8_t address, uint8_t value)
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
	
	Chip_GPIO_SetPinOutLow(LPC_GPIO, ADS_nSSEL1);																		  //Chip select Low(0)
		
	Chip_SSP_RWFrames_Blocking(ADS_SSP, &xf_setup);	
	
	Chip_GPIO_SetPinOutHigh(LPC_GPIO, ADS_nSSEL1);																		//Chip select High(1)
		
	return;
}

/***************************VBIAS*************************************/

void Chip_ADS1248_SetVBIAS(uint8_t value)
{
	if(value != VBIAS_OFF && value != VBIAS0 && value != VBIAS1 && value != VBIAS2 && value != VBIAS3 
		&& value != VBIAS4 && value != VBIAS5 && value != VBIAS6 && value != VBIAS7)
	{
		return;
	}
	
	Chip_ADS1248_WriteRegister(VBIAS, value);
	
	return;
}

/***************************MUX0*************************************/
void Chip_ADS1248_SetNegativeInput(uint8_t value)
{
	uint8_t mux0 = 0;
	
	if(value != AIN0 && value != AIN1 && value != AIN2 && value != AIN3 
		&& value != AIN4 && value != AIN5 && value != AIN6 && value != AIN7)
	{
		return;
	}
	
	mux0 = Chip_ADS1248_ReadRegister(MUX0);
	mux0 |= value;
	Chip_ADS1248_WriteRegister(MUX0, mux0);
	
	return;
}

void Chip_ADS1248_SetPositiveInput(uint8_t value)
{
	uint8_t mux0 = 0;
	
	if(value != AIN0 && value != AIN1 && value != AIN2 && value != AIN3 
		&& value != AIN4 && value != AIN5 && value != AIN6 && value != AIN7)
	{
		return;
	}
	
	mux0 = Chip_ADS1248_ReadRegister(MUX0);
	mux0 |= (value << 3);
	Chip_ADS1248_WriteRegister(MUX0, mux0);
	
	return;
}

void Chip_ADS1248_SetBurnout(uint8_t value)
{
	uint8_t mux0 = 0;
	
	if(value != BURNOUT_OFF && value != BURNOUT_05U && value != BURNOUT_2U && value != BURNOUT_10U)
	{
		return;
	}
	
	mux0 = Chip_ADS1248_ReadRegister(MUX0);
	mux0 |= (value << 6);
	Chip_ADS1248_WriteRegister(MUX0, mux0);
	
	return;
}

/***************************MUX1*************************************/

bool Chip_ADS1248_GetClkStat(void)
{
	uint8_t mux1 = 0;
	
	return (mux1 & 0x07) ? TRUE : FALSE;
}

void Chip_ADS1248_SetInternalVref(uint8_t value)
{
	uint8_t mux1 = 0;
	
	if(value != INTERNAL_OFF && value != INTERNAL_ON && value != INTERNAL_SLEEP)
	{
		return;
	}	
	
	mux1 = Chip_ADS1248_ReadRegister(MUX1);
	mux1 |= value << 5;
	
	Chip_ADS1248_WriteRegister(MUX1, mux1);
	
	return;
}

void Chip_ADS1248_SetVrefInput(uint8_t value)
{
	uint8_t mux1 = 0;
	
	if(value != REF0 && value != REF1 && value != ONBOARD && value != ONBOARD_REF0)
	{
		return;
	}
	
	mux1 = Chip_ADS1248_ReadRegister(MUX1);
	mux1 |= value << 3;
	
	Chip_ADS1248_WriteRegister(MUX1, mux1);
	
	return;
}

void Chip_ADS1248_MuxCal(uint8_t value)
{
	uint8_t mux1 = 0;
	
	if(value != SYS_NORMAL && value != SYS_OFFSET && value != SYS_GAIN && value != SYS_TEMP_DIODE 
		&& value != SYS_REF1 && value != SYS_REF0 && value != SYS_AVDD && value != SYS_DVDD)
	{
		return;
	}
	
	mux1 = Chip_ADS1248_ReadRegister(MUX1);
	mux1 |= value;
	
	Chip_ADS1248_WriteRegister(MUX1, mux1);
	
	return;
}

/***************************SYS0*************************************/
void Chip_ADS1248_SetPGA(uint8_t value)
{
	uint8_t sys0 = 0;
	
	if(value != PGA1 && value != PGA2 && value != PGA4 && value != PGA8 
		&& value != PGA16 && value != PGA32 && value != PGA64 && value != PGA128)
	{
		return;
	}
	
	sys0 = Chip_ADS1248_ReadRegister(SYS0);
	sys0 |= value << 4;
	
	Chip_ADS1248_WriteRegister(SYS0, sys0);
	
	return;	
}

void Chip_ADS1248_SetSPS(uint8_t value)
{
	uint8_t sys0 = 0;
	
	if(value != SPS5 && value != SPS10 && value != SPS20 && value != SPS40 
		&& value != SPS80 && value != SPS160 && value != SPS320 && value != SPS640 
		&& value != SPS1000 && value != SPS2000)
	{
		return;
	}
	
	sys0 = Chip_ADS1248_ReadRegister(SYS0);
	sys0 |= value;
	
	Chip_ADS1248_WriteRegister(SYS0, sys0);
	
	return;
}

/***************************IDAC0************************************/
void Chip_ADS1248_SetIdacValue(uint8_t value)
{
	uint8_t idac0 = 0;
	
	if(value != IDAC_OFF && value != IDAC_50U && value != IDAC_100U && value != IDAC_250U 
		&& value != IDAC_500U && value != IDAC_750U && value != IDAC_1000U && value != IDAC_1500U)
	{
		return;
	}
	
	idac0 = Chip_ADS1248_ReadRegister(IDAC0);
	idac0 |= value;
	
	Chip_ADS1248_WriteRegister(IDAC0, idac0);
	
	return;
}

/***************************IDAC1************************************/
void Chip_ADS1248_SetIDAC1(uint8_t value)
{
	uint8_t idac1 = 0;
	
	if(value != AIN0 && value != AIN1 && value != AIN2 && value != AIN3 
		&& value != AIN4 && value != AIN5 && value != AIN6 && value != AIN7
		&& value != IOUT1 && value != IOUT2 && value != DISCONNECT)
	{
		return;
	}
	
	idac1 = Chip_ADS1248_ReadRegister(IDAC1);
	idac1 |= value << 4;
	
	Chip_ADS1248_WriteRegister(IDAC1, idac1);
	
	return;
}
	
void Chip_ADS1248_SetIDAC2(uint8_t value)
{
	uint8_t idac1 = 0;
	
	if(value != AIN0 && value != AIN1 && value != AIN2 && value != AIN3 
		&& value != AIN4 && value != AIN5 && value != AIN6 && value != AIN7
		&& value != IOUT1 && value != IOUT2 && value != DISCONNECT)
	{
		return;
	}
	
	idac1 = Chip_ADS1248_ReadRegister(IDAC1);
	idac1 |= value;
	
	Chip_ADS1248_WriteRegister(IDAC1, idac1);
	
	return;
}

/*********************************************************************/
uint32_t Chip_ADS1248_GetData(void)
{
	
	
	
	return 0;
}
