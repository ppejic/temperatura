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
#define WAKEUP						0x01																					//Exit sleep mode
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
{2890686
,2903602
,2916516
,2929425
,2942330
,2955232
,2968130
,2981024
,2993915
,3006801
,3019684
,3032563
,3045438
,3058309
,3071177
,3084040
,3096900
,3109757
,3122609
,3135457
,3148302
,3161143
,3173980
,3186813
,3199643
,3212469
,3225290
,3238109
,3250923
,3263733
,3276540
,3289343
,3302142
,3314937
,3327729
,3340516
,3353300
,3366080
,3378857
,3391629
,3404398
,3417163
,3429924
,3442681
,3455434
,3468184
,3480930
,3493672
,3506410
,3519145
,3531875
,3544602
,3557325
,3570044
,3582760
,3595471
,3608179
,3620883
,3633583
,3646280
,3658973
,3671661
,3684346
,3697028
,3709705
,3722379
,3735048
,3747714
,3760377
,3773035
,3785690
,3798340
,3810987
,3823631
,3836270
,3848906
,3861537
,3874165
,3886790
,3899410
,3912027
,3924639
,3937248
,3949853
,3962455
,3975052
,3987646
,4000236
,4012822
,4025405
,4037983
,4050558
,4063129
,4075696
,4088259
,4100819
,4113375
,4125927
,4138475
,4151019
,4163560
,4176096
,4188629
,4201159
,4213684
,4226205
,4238723
,4251237
,4263747
,4276253
,4288756
,4301255
,4313750
,4326241
,4338728
,4351212
,4363691
,4376167
,4388639
,4401108
,4413572
,4426033
,4438490
,4450943
,4463392
,4475837
,4488279
,4500717
,4513151
,4525581
,4538008
,4550431
,4562849
,4575264
,4587676
,4600083
,4612487
,4624887
,4637283
,4649675
,4662063
,4674448
,4686829
,4699206
,4711579
,4723949
,4736314
,4748676
,4761034
,4773388
,4785739
,4798086
,4810428
,4822767
,4835103
,4847434
,4859762
,4872085
,4884406
,4896722
,4909034
,4921343
,4933648
,4945949
,4958246
,4970539
,4982829
,4995115
,5007397
,5019675
,5031949
,5044220
,5056487
,5068750
,5081009
,5093264
,5105516
,5117763
,5130007
,5142248
,5154484
,5166717
,5178945
,5191170
,5203391
,5215609
,5227822
,5240032
,5252238
,5264440
,5276639
,5288833
,5301024
,5313211
,5325394
,5337573
,5349749
,5361921
,5374088
,5386253
,5398413
,5410569
,5422722
,5434871
,5447016
,5459158
,5471295
,5483429
,5495559
,5507685
,5519807
,5531926
,5544040
,5556151
,5568258
,5580362
,5592461
,5604557
,5616649
,5628737
,5640821
,5652902
,5664978
,5677051
,5689120
,5701185
,5713247
,5725305
,5737358
,5749409
,5761455
,5773497
,5785536
,5797571
,5809602
,5821629
,5833653
,5845672
,5857688
,5869700
,5881708
,5893713
,5905713
,5917710
,5929703
,5941693
,5953678
,5965660
,5977637
,5989611
,6001582
,6013548
,6025511
,6037470
,6049425
,6061376
,6073323
,6085267
,6097207
,6109143
,6121075
,6133003
,6144928
,6156849
,6168766
,6180679
,6192588
,6204494
,6216396
,6228293
,6240188
,6252078
,6263965
,6275847
,6287726
,6299602
,6311473
,6323340
,6335204
,6347064
,6358920
,6370773
,6382621
,6394466
,6406307
,6418144
,6429977
,6441807
,6453633
,6465455
,6477273
,6489087
,6500898
,6512704
,6524507
,6536307
,6548102
,6559893
,6571681
,6583465
,6595245
,6607021
,6618794
,6630563
,6642328
,6654089
,6665846
,6677600
,6689349
,6701095
,6712837
,6724576
,6736310
,6748041
,6759768
,6771491
,6783210
,6794925
,6806637
,6818345
,6830049
,6841749
,6853446
,6865139
,6876827
,6888512
,6900194
,6911871
,6923545
,6935215
,6946881
,6958543
,6970201
,6981856
,6993507
,7005154
,7016797
,7028437
,7040072
,7051704
,7063332
,7074956
,7086577
,7098193
,7109806
,7121415
,7133021
,7144622
,7156220
,7167813
,7179403
,7190990
,7202572
,7214151
,7225725
,7237296
,7248864
,7260427
,7271987
,7283542
,7295094
,7306643
,7318187
,7329728
,7341264
,7352797
,7364327
,7375852
,7387373
,7398891
,7410405
,7421915
,7433422
,7444924
,7456423
,7467918
,7479409
,7490897
,7502380
,7513860
,7525336
,7536808
,7548276
,7559741
,7571202
,7582659
,7594112
,7605561
,7617007
,7628448
,7639886
,7651320
,7662751
,7674177
,7685600
,7697019
,7708434
,7719845
,7731253
,7742657
,7754056
,7765453
,7776845
,7788233
,7799618
,7810999
,7822376
,7833749
,7845119
,7856485
,7867846
,7879204
,7890559
,7901909
,7913256
,7924599
,7935938
,7947273
,7958605
,7969932
,7981256
,7992576
,8003892
,8015205
,8026514
,8037818
,8049120
,8060417
,8071710
,8083000
,8094286};


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
int32_t							Chip_ADS1248_GetTemperature(uint8_t chip, uint8_t rtd);	
void 								Chip_ADS1248_SelfOffsetCal(uint8_t chip);

#endif
