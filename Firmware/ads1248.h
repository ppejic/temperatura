#ifndef __ADS1248_H
#define __ADS1248_H

#include "chip.h"

#define COMMAND 					0
#define DATA		 					1
#define ADS_SSP           LPC_SSP1
#define BUFFER_SIZE				10

/*****************ADS1248 SSP********************************************/
#define ADS_nSSEL0				1, 23
#define ADS_nSSEL1				1, 26

#define ADS_nDRDY0				0, 18
#define ADS_nDRDY1				0, 2

#define ADS_START0				0, 23
#define ADS_START1				1, 27

#define ADS_nRESET0				0, 20
#define ADS_nRESET1				0, 21

#define ADS_SCLK					1, 20
#define ADS_MISO 					1, 21
#define ADS_MOSI 					1, 22

/*****************ADS1248 Register description***************************/
#define MUX0 							0x00
#define VBIAS 						0x01
#define MUX1 							0x02
#define SYS0 							0x03
#define OFC0 							0x04
#define OFC1 							0x05
#define OFC2 							0x06
#define FSC0 							0x07
#define FSC1 							0x08
#define FSC2 							0x09
#define IDAC0 						0x0A
#define IDAC1 						0x0B
#define GPIOCFG 					0x0C
#define GPIODIR 					0x0D
#define GPIODAT						0x0E

/*****************ADS1248 Command description***************************/
#define WAKEUP						0x00																					//Exit sleep mode
#define SLEEP						  0x02																					//Enter sleep mode
#define SYNC							0x04																					//Synchronize the A/D conversion
#define RESET 				 		0x06																					//Reset to power-up values 
#define NOP								0xFF																					//No operation	
#define RDATA							0x12																					//Read data once 
#define RDATAC						0x14																					//Read data continuously 
#define SDATAC						0x16																					//Stop reading data continuously 
#define RREG							(0x02 << 4)																		//Read from register rrrr
#define WREG							(0x04 << 4)																		//Write to register rrrr
#define SYSOCAL						0x60																					//System offset calibration
#define SYSGCAL						0x61																					//System gain calibration
#define SELFOCAL					0x62																					//Exit sleep mode

/*****************ADS1248 VBIAS register parameters**********************/
#define VBIAS_OFF					0x00
#define VBIAS0						(0x01 << 0)
#define VBIAS1						(0x01 << 1)
#define VBIAS2						(0x01 << 2)
#define VBIAS3						(0x01 << 3)
#define VBIAS4						(0x01 << 4)
#define VBIAS5						(0x01 << 5)
#define VBIAS6						(0x01 << 6)
#define VBIAS7						(0x01 << 7)

/*****************ADS1248 MUX0 register parameters***********************/
#define BURNOUT_OFF				0x00	
#define BURNOUT_05U				0x01
#define BURNOUT_2U				0x02
#define BURNOUT_10U				0x03
#define AIN0							0x00
#define AIN1							0x01
#define AIN2							0x02
#define AIN3							0x03
#define AIN4							0x04
#define AIN5							0x05
#define AIN6							0x06
#define AIN7							0x07

/*****************ADS1248 MUX1 register parameters***********************/
#define INTERNAL_OFF			0x00
#define INTERNAL_ON 			0x01
#define INTERNAL_SLEEP		0x02
#define REF0							0x00
#define REF1							0x01
#define ONBOARD						0x02
#define ONBOARD_REF0   		0x03
#define SYS_NORMAL   			0x00
#define SYS_OFFSET   			0x01
#define SYS_GAIN   				0x02
#define SYS_TEMP_DIODE   	0x03
#define SYS_REF1   				0x04
#define SYS_REF0   				0x05
#define SYS_AVDD   				0x06
#define SYS_DVDD   				0x07

/*****************ADS1248 SYS0 register parameters***********************/
#define PGA1							0x00
#define PGA2							0x01
#define PGA4							0x02
#define PGA8							0x03
#define PGA16							0x04
#define PGA32							0x05
#define PGA64							0x06
#define PGA128						0x07
#define SPS5							0x00
#define SPS10							0x01
#define SPS20						  0x02
#define SPS40							0x03
#define SPS80						  0x04
#define SPS160						0x05
#define SPS320						0x06
#define SPS640						0x07
#define SPS1000						0x08
#define SPS2000						0x09

/*****************ADS1248 IDAC0 register parameters**********************/
#define IDAC_OFF					0x00
#define IDAC_50U					0x01
#define IDAC_100U					0x02
#define IDAC_250U					0x03
#define IDAC_500U					0x04
#define IDAC_750U					0x05
#define IDAC_1000U				0x06
#define IDAC_1500U				0x07

/*****************ADS1248 IDAC1 register parameters**********************/
#define IOUT1							0x08
#define IOUT2							0x09
#define DISCONNECT				0x0F


void    						Chip_ADS1248_Init(void);
static void					Chip_ADS1248_BufferInit(void);					
uint8_t 						Chip_ADS1248_ReadRegister(uint8_t address);
void    						Chip_ADS1248_WriteRegister(uint8_t address, uint8_t value);

void								Chip_ADS1248_SetVBIAS(uint8_t value);

void    						Chip_ADS1248_SetBurnout(uint8_t value);
void    						Chip_ADS1248_SetPositiveInput(uint8_t value);
void    						Chip_ADS1248_SetNegativeInput(uint8_t value);

bool    						Chip_ADS1248_GetClkStat(void);
void    						Chip_ADS1248_SetInternalVref(uint8_t value);
void    						Chip_ADS1248_SetVrefInput(uint8_t value);
void    						Chip_ADS1248_MuxCal(uint8_t value);

void    						Chip_ADS1248_SetPGA(uint8_t value);
void    						Chip_ADS1248_SetSPS(uint8_t value);

void    						Chip_ADS1248_SetIdacValue(uint8_t value);

void    						Chip_ADS1248_SetIDAC1(uint8_t value);
void    						Chip_ADS1248_SetIDAC2(uint8_t value);
uint32_t						Chip_ADS1248_GetData(void);	

#endif
