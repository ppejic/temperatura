#include "main.h"
#include "ads1248.h"
#include "app_usbd_cfg.h"
#include "cdc_vcom.h"

static const  USBD_API_T g_usbApi = {
	&hw_api,
	&core_api,
	0,
	0,
	0,
	&cdc_api,
	0,
	0x02221101,
};

const USBD_API_T *g_pUsbApi = &g_usbApi;
USBD_HANDLE_T g_hUsb;
static uint8_t g_rxBuff[256];

osMailQDef(mail, 2, T_MEAS);
osMailQId  mail;

osThreadDef(GetTemperature, osPriorityNormal, 1, 0);
osThreadDef(RX_Thread, osPriorityNormal, 1, 0);
osThreadDef(TX_Thread, osPriorityNormal, 1, 0);

void FLEX_INT0_IRQHandler(void)
{
	Chip_PININT_ClearIntStatus(LPC_PININT, PININTCH(0));
	osSignalSet(get_temperature_id, OS_DRDY0);
}

void FLEX_INT1_IRQHandler(void)
{
	Chip_PININT_ClearIntStatus(LPC_PININT, PININTCH(1));
	osSignalSet(get_temperature_id, OS_DRDY1);
}

void USB_IRQHandler(void)
{	
	USBD_API->hw->ISR(g_hUsb);
	
	osSignalSet(rx_id, USB_RCV_DATA);
}

void TX_Thread (void const *argument)
{
	T_MEAS  *rptr;
  osEvent  evt;
	
	while(1)
	{
		evt = osMailGet(mail, osWaitForever); 
		if(evt.status == osEventMail)
		{
			rptr = evt.value.p;
			vcom_write(&g_rxBuff[0], 256);
			osMailFree(mail, rptr);
		}
	}
}

void GetTemperature(void const *argument)
{
	T_MEAS *mptr;
	
	Chip_ADS1248_Init();
	Chip_ADS1248_SelfOffsetCal(CHIP_U1);
	Chip_ADS1248_SelfOffsetCal(CHIP_U3);
	
	while(1)
	{
		osSignalWait(ADS_TEMP_GET, osWaitForever);
		
		mptr=osMailAlloc(mail, osWaitForever);
		mptr->rtd1 = Chip_ADS1248_GetTemperature(CHIP_U1, RTD_1);
		mptr->rtd2 = Chip_ADS1248_GetTemperature(CHIP_U1, RTD_2);
		mptr->rtd3 = Chip_ADS1248_GetTemperature(CHIP_U3, RTD_3);
		mptr->rtd4 = Chip_ADS1248_GetTemperature(CHIP_U3, RTD_4);
		
		osMailPut(mail, mptr);
		osThreadYield();
	}
}


void RX_Thread(void const *argument)
{
	uint32_t rdCnt = 0;
	uint8_t i = 0;	
	uint8_t string_match = 1;
	
	USB_Periph_Init();
	
	while(1)
	{
		osSignalWait(USB_RCV_DATA, osWaitForever);

		rdCnt = vcom_bread(&g_rxBuff[0], 256);
		
		if(rdCnt) 
		{
			//check if the received string is "t1t2t3t4"
			string_match = 1;
			for(i = 0; i < RX_STRING; i++)
			{
				if(g_rxBuff[i] != rx_string[i])
				{
					string_match = 0;
					break;
				}
			}
			
			//if the strings match signal GetTemperature() thread
			if(string_match == 1)
			{
				osSignalSet(get_temperature_id, ADS_TEMP_GET);
			}
			
			osThreadYield();
		}
	}
}

int main()
{		
	osKernelInitialize();
				
	get_temperature_id = osThreadCreate(osThread(GetTemperature),NULL);  
	rx_id = osThreadCreate(osThread(RX_Thread),NULL);  
	tx_id	= osThreadCreate(osThread(TX_Thread),NULL);
	
	osKernelStart();	
}

static void usb_pin_clk_init(void)
{
	/* enable USB main clock */
	Chip_Clock_SetUSBClockSource(SYSCTL_USBCLKSRC_PLLOUT, 1);
	/* Enable AHB clock to the USB block and USB RAM. */
	Chip_Clock_EnablePeriphClock(SYSCTL_CLOCK_USB);
	Chip_Clock_EnablePeriphClock(SYSCTL_CLOCK_USBRAM);
	/* power UP USB Phy */
	Chip_SYSCTL_PowerUp(SYSCTL_POWERDOWN_USBPAD_PD);
	
	/* Enable IOCON clock */
	Chip_Clock_EnablePeriphClock(SYSCTL_CLOCK_IOCON);

	Chip_IOCON_PinMuxSet(LPC_IOCON, 0,  3, (IOCON_FUNC1 | IOCON_MODE_INACT)); 		/* PIO0_3 used for USB_VBUS */
	Chip_IOCON_PinMuxSet(LPC_IOCON, 0,  6,  (IOCON_FUNC1 | IOCON_MODE_INACT));		/* PIO0_6 used for USB_CONNECT */
}

USB_INTERFACE_DESCRIPTOR *find_IntfDesc(const uint8_t *pDesc, uint32_t intfClass)
{
	USB_COMMON_DESCRIPTOR *pD;
	USB_INTERFACE_DESCRIPTOR *pIntfDesc = 0;
	uint32_t next_desc_adr;

	pD = (USB_COMMON_DESCRIPTOR *) pDesc;
	next_desc_adr = (uint32_t) pDesc;

	while (pD->bLength) {
		/* is it interface descriptor */
		if (pD->bDescriptorType == USB_INTERFACE_DESCRIPTOR_TYPE) {

			pIntfDesc = (USB_INTERFACE_DESCRIPTOR *) pD;
			/* did we find the right interface descriptor */
			if (pIntfDesc->bInterfaceClass == intfClass) {
				break;
			}
		}
		pIntfDesc = 0;
		next_desc_adr = (uint32_t) pD + pD->bLength;
		pD = (USB_COMMON_DESCRIPTOR *) next_desc_adr;
	}

	return pIntfDesc;
}

void USB_Periph_Init(void)
{
	USBD_API_INIT_PARAM_T usb_param;
	USB_CORE_DESCS_T desc;
	ErrorCode_t ret = LPC_OK;
	
	/* enable clocks and pinmux */
	usb_pin_clk_init();

	/* initilize call back structures */
	memset((void *) &usb_param, 0, sizeof(USBD_API_INIT_PARAM_T));
	usb_param.usb_reg_base = LPC_USB0_BASE;
	usb_param.max_num_ep = 3;
	usb_param.mem_base = USB_STACK_MEM_BASE;
	usb_param.mem_size = USB_STACK_MEM_SIZE;

	/* Set the USB descriptors */
	desc.device_desc = (uint8_t *) &USB_DeviceDescriptor[0];
	desc.string_desc = (uint8_t *) &USB_StringDescriptor[0];
	/* Note, to pass USBCV test full-speed only devices should have both
	   descriptor arrays point to same location and device_qualifier set to 0.
	 */
	desc.high_speed_desc = (uint8_t *) &USB_FsConfigDescriptor[0];
	desc.full_speed_desc = (uint8_t *) &USB_FsConfigDescriptor[0];
	desc.device_qualifier = 0;

	/* USB Initialization */
	ret = USBD_API->hw->Init(&g_hUsb, &desc, &usb_param);
	if (ret == LPC_OK) {
		/* Init VCOM interface */
		ret = vcom_init(g_hUsb, &desc, &usb_param);
		if (ret == LPC_OK) {
			/*  enable USB interrrupts */
			NVIC_EnableIRQ(USB0_IRQn);
			/* now connect */
			USBD_API->hw->Connect(g_hUsb, 1);
		}
	}
}
