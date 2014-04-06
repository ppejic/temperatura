#ifndef __ADS1248_H
#define __ADS1248_H

#include "chip.h"

#define COMMAND 					0
#define DATA		 					1
#define ADS_SSP           LPC_SSP1
#define BUFFER_SIZE				10
#define CHIP_U1						0x01
#define CHIP_U3						0x02
#define RTD_1							0x01
#define RTD_2							0x02
#define RTD_3							0x03
#define RTD_4							0x04

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

#define OS_DRDY_LOW				0x01

#define LUT_SIZE					431
#define LUT_OFFSET				30
const static uint32_t TempLUT[431] = 
{2893443
,2909836
,2926230
,2934426
,2950820
,2959016
,2975410
,2983607
,3000000
,3016393
,3024590
,3040984
,3049180
,3065574
,3073770
,3090164
,3106557
,3114754
,3131148
,3139344
,3155738
,3163934
,3180328
,3196721
,3204918
,3221311
,3229508
,3245902
,3254098
,3270492
,3278689
,3295082
,3311475
,3319672
,3336066
,3344262
,3360656
,3368852
,3385246
,3401639
,3409836
,3426230
,3434426
,3450820
,3459016
,3475410
,3483607
,3500000
,3516393
,3524590
,3540984
,3549180
,3565574
,3573770
,3590164
,3598361
,3614754
,3631148
,3639344
,3655738
,3663934
,3680328
,3688525
,3704918
,3713115
,3729508
,3737705
,3754098
,3770492
,3778689
,3795082
,3803279
,3819672
,3827869
,3844262
,3852459
,3868852
,3877049
,3893443
,3909836
,3918033
,3934426
,3942623
,3959016
,3967213
,3983607
,3991803
,4008197
,4016393
,4032787
,4040984
,4057377
,4073770
,4081967
,4098361
,4106557
,4122951
,4131148
,4147541
,4155738
,4172131
,4180328
,4196721
,4204918
,4221311
,4229508
,4245902
,4254098
,4270492
,4286885
,4295082
,4311475
,4319672
,4336066
,4344262
,4360656
,4368852
,4385246
,4393443
,4409836
,4418033
,4434426
,4442623
,4459016
,4467213
,4483607
,4491803
,4508197
,4516393
,4532787
,4540984
,4557377
,4573770
,4581967
,4598361
,4606557
,4622951
,4631148
,4647541
,4655738
,4672131
,4680328
,4696721
,4704918
,4721311
,4729508
,4745902
,4754098
,4770492
,4778689
,4795082
,4803279
,4819672
,4827869
,4844262
,4852459
,4868852
,4877049
,4893443
,4901639
,4918033
,4926230
,4942623
,4950820
,4967213
,4975410
,4991803
,5000000
,5016393
,5024590
,5040984
,5049180
,5065574
,5073770
,5090164
,5098361
,5114754
,5122951
,5139344
,5147541
,5163934
,5172131
,5188525
,5196721
,5213115
,5221311
,5237705
,5245902
,5262295
,5270492
,5286885
,5295082
,5311475
,5319672
,5336066
,5344262
,5360656
,5368852
,5385246
,5393443
,5409836
,5418033
,5434426
,5442623
,5450820
,5467213
,5475410
,5491803
,5500000
,5516393
,5524590
,5540984
,5549180
,5565574
,5573770
,5590164
,5598361
,5614754
,5622951
,5639344
,5647541
,5663934
,5672131
,5688525
,5696721
,5713115
,5721311
,5729508
,5745902
,5754098
,5770492
,5778689
,5795082
,5803279
,5819672
,5827869
,5844262
,5852459
,5868852
,5877049
,5893443
,5901639
,5909836
,5926230
,5934426
,5950820
,5959016
,5975410
,5983607
,6000000
,6008197
,6024590
,6032787
,6049180
,6057377
,6065574
,6081967
,6090164
,6106557
,6114754
,6131148
,6139344
,6155738
,6163934
,6180328
,6188525
,6196721
,6213115
,6221311
,6237705
,6245902
,6262295
,6270492
,6286885
,6295082
,6311475
,6319672
,6327869
,6344262
,6352459
,6368852
,6377049
,6393443
,6401639
,6418033
,6426230
,6434426
,6450820
,6459016
,6475410
,6483607
,6500000
,6508197
,6524590
,6532787
,6540984
,6557377
,6565574
,6581967
,6590164
,6606557
,6614754
,6631148
,6639344
,6647541
,6663934
,6672131
,6688525
,6696721
,6713115
,6721311
,6729508
,6745902
,6754098
,6770492
,6778689
,6795082
,6803279
,6811475
,6827869
,6836066
,6852459
,6860656
,6877049
,6885246
,6893443
,6909836
,6918033
,6934426
,6942623
,6959016
,6967213
,6975410
,6991803
,7000000
,7016393
,7024590
,7040984
,7049180
,7057377
,7073770
,7081967
,7098361
,7106557
,7114754
,7131148
,7139344
,7155738
,7163934
,7180328
,7188525
,7196721
,7213115
,7221311
,7237705
,7245902
,7254098
,7270492
,7278689
,7295082
,7303279
,7311475
,7327869
,7336066
,7352459
,7360656
,7377049
,7385246
,7393443
,7409836
,7418033
,7434426
,7442623
,7450820
,7467213
,7475410
,7491803
,7500000
,7508197
,7524590
,7532787
,7549180
,7557377
,7565574
,7581967
,7590164
,7606557
,7614754
,7622951
,7639344
,7647541
,7663934
,7672131
,7680328
,7696721
,7704918
,7721311
,7729508
,7737705
,7754098
,7762295
,7778689
,7786885
,7795082
,7811475
,7819672
,7827869
,7844262
,7852459
,7868852
,7877049
,7885246
,7901639
,7909836
,7926230
,7934426
,7942623
,7959016
,7967213
,7975410
,7991803
,8000000
,8016393
,8024590
,8032787
,8049180
,8057377
,8073770
,8081967
,8090164
,8106557};


void    						Chip_ADS1248_Init(void);
static void					Chip_ADS1248_BufferInit(void);					
uint8_t 						Chip_ADS1248_ReadRegister(uint8_t chip, uint8_t address);
void    						Chip_ADS1248_WriteRegister(uint8_t chip, uint8_t address, uint8_t value);

void								Chip_ADS1248_SetVBIAS(uint8_t chip, uint8_t value);

void    						Chip_ADS1248_SetBurnout(uint8_t chip, uint8_t value);
void    						Chip_ADS1248_SetPositiveInput(uint8_t chip, uint8_t value);
void    						Chip_ADS1248_SetNegativeInput(uint8_t chip, uint8_t value);

void    						Chip_ADS1248_SetInternalVref(uint8_t chip, uint8_t value);
void    						Chip_ADS1248_SetVrefInput(uint8_t chip, uint8_t value);
void    						Chip_ADS1248_MuxCal(uint8_t chip, uint8_t value);

void    						Chip_ADS1248_SetPGA(uint8_t chip, uint8_t value);
void    						Chip_ADS1248_SetSPS(uint8_t chip, uint8_t value);

void    						Chip_ADS1248_SetIdacValue(uint8_t chip, uint8_t value);

void    						Chip_ADS1248_SetIDAC1(uint8_t chip, uint8_t value);
void    						Chip_ADS1248_SetIDAC2(uint8_t chip, uint8_t value);
uint32_t						Chip_ADS1248_GetTemperature(uint8_t chip, uint8_t rtd);	
void 								Chip_ADS1248_SelfOffsetCal(uint8_t chip);

#endif
