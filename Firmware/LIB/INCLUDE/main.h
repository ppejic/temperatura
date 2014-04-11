#ifndef __MAIN_H
#define __MAIN_H

#include "chip.h"
#include "cmsis_os.h"
#include "app_usbd_cfg.h"
#include "cdc_vcom.h"
#include <stdio.h>
#include <string.h>

#define USB_RCV_DATA			0x0001
#define USB_SND_DATA			0x0002
#define ADS_TEMP_GET			0x0003
#define OS_DRDY0					0x0004
#define OS_DRDY1					0x0005
#define RX_STRING					8

typedef struct {                                
  int32_t    rtd1;                              
  int32_t    rtd2;                              
  int32_t    rtd3;                              
	int32_t    rtd4;
} T_MEAS;

const uint8_t rx_string[] = {'t', '1', 't', '2', 't', '3', 't', '4'};
const uint32_t OscRateIn = 12000000;
extern const  USBD_HW_API_T hw_api;
extern const  USBD_CORE_API_T core_api;
extern const  USBD_CDC_API_T cdc_api;

osThreadId get_temperature_id;
osThreadId rx_id;
osThreadId tx_id;

void GetTemperature (void const *argument);
void RX_Thread 			(void const *argument);
void TX_Thread 			(void const *argument);
USB_INTERFACE_DESCRIPTOR *find_IntfDesc(const uint8_t *pDesc, uint32_t intfClass);
void USB_Periph_Init(void);

#endif
