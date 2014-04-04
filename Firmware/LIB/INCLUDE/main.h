#ifndef __MAIN_H
#define __MAIN_H

#include "chip.h"
#include "cdc_usb.h"
//#include "cmsis_os.h"

const uint32_t OscRateIn = 12000000;

//osThreadId main_id;
//osThreadId threadX_id;


void threadX(void const* argument);

#endif
