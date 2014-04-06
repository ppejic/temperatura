//#include "chip.h" 
//#include "main.h"
//#include "cmsis_os.h"
//#include <stdio.h>
//#include <string.h>
//#include "app_usbd_cfg.h"
//#include "cdc_vcom.h"
//#include "cdc_usb.h"

///* Since this example only uses CDC class link functions for that clas only */
//static const  USBD_API_T g_usbApi = {
//	&hw_api,
//	&core_api,
//	0,
//	0,
//	0,
//	&cdc_api,
//	0,
//	0x02221101,
//};

//const USBD_API_T *g_pUsbApi = &g_usbApi;
//static USBD_HANDLE_T g_hUsb;
//static uint8_t g_rxBuff[256];

///**
// * @brief	Handle interrupt from USB0
// * @return	Nothing
// */
//void USB_IRQHandler(void)
//{
//	uint32_t rdCnt = 0;
//	
//	USBD_API->hw->ISR(g_hUsb);
//	
//	osSignalSet(read_usb_id, USB_RCV_DATA);
//}

///* Initialize pin and clocks for USB0/USB1 port */
//static void usb_pin_clk_init(void)
//{
//	/* enable USB main clock */
//	Chip_Clock_SetUSBClockSource(SYSCTL_USBCLKSRC_PLLOUT, 1);
//	/* Enable AHB clock to the USB block and USB RAM. */
//	Chip_Clock_EnablePeriphClock(SYSCTL_CLOCK_USB);
//	Chip_Clock_EnablePeriphClock(SYSCTL_CLOCK_USBRAM);
//	/* power UP USB Phy */
//	Chip_SYSCTL_PowerUp(SYSCTL_POWERDOWN_USBPAD_PD);
//	
//	/* Enable IOCON clock */
//	Chip_Clock_EnablePeriphClock(SYSCTL_CLOCK_IOCON);

//	Chip_IOCON_PinMuxSet(LPC_IOCON, 0,  3, (IOCON_FUNC1 | IOCON_MODE_INACT)); 		/* PIO0_3 used for USB_VBUS */
//	Chip_IOCON_PinMuxSet(LPC_IOCON, 0,  6,  (IOCON_FUNC1 | IOCON_MODE_INACT));		/* PIO0_6 used for USB_CONNECT */
//}

///* Find the address of interface descriptor for given class type. */
//USB_INTERFACE_DESCRIPTOR *find_IntfDesc(const uint8_t *pDesc, uint32_t intfClass)
//{
//	USB_COMMON_DESCRIPTOR *pD;
//	USB_INTERFACE_DESCRIPTOR *pIntfDesc = 0;
//	uint32_t next_desc_adr;

//	pD = (USB_COMMON_DESCRIPTOR *) pDesc;
//	next_desc_adr = (uint32_t) pDesc;

//	while (pD->bLength) {
//		/* is it interface descriptor */
//		if (pD->bDescriptorType == USB_INTERFACE_DESCRIPTOR_TYPE) {

//			pIntfDesc = (USB_INTERFACE_DESCRIPTOR *) pD;
//			/* did we find the right interface descriptor */
//			if (pIntfDesc->bInterfaceClass == intfClass) {
//				break;
//			}
//		}
//		pIntfDesc = 0;
//		next_desc_adr = (uint32_t) pD + pD->bLength;
//		pD = (USB_COMMON_DESCRIPTOR *) next_desc_adr;
//	}

//	return pIntfDesc;
//}

///**
// * @brief	main routine for blinky example
// * @return	Function should not exit.
// */
//void USB_Periph_Init(void)
//{
//	USBD_API_INIT_PARAM_T usb_param;
//	USB_CORE_DESCS_T desc;
//	ErrorCode_t ret = LPC_OK;
//	
//	/* enable clocks and pinmux */
//	usb_pin_clk_init();

//	/* initilize call back structures */
//	memset((void *) &usb_param, 0, sizeof(USBD_API_INIT_PARAM_T));
//	usb_param.usb_reg_base = LPC_USB0_BASE;
//	usb_param.max_num_ep = 3;
//	usb_param.mem_base = USB_STACK_MEM_BASE;
//	usb_param.mem_size = USB_STACK_MEM_SIZE;

//	/* Set the USB descriptors */
//	desc.device_desc = (uint8_t *) &USB_DeviceDescriptor[0];
//	desc.string_desc = (uint8_t *) &USB_StringDescriptor[0];
//	/* Note, to pass USBCV test full-speed only devices should have both
//	   descriptor arrays point to same location and device_qualifier set to 0.
//	 */
//	desc.high_speed_desc = (uint8_t *) &USB_FsConfigDescriptor[0];
//	desc.full_speed_desc = (uint8_t *) &USB_FsConfigDescriptor[0];
//	desc.device_qualifier = 0;

//	/* USB Initialization */
//	ret = USBD_API->hw->Init(&g_hUsb, &desc, &usb_param);
//	if (ret == LPC_OK) {
//		/* Init VCOM interface */
//		ret = vcom_init(g_hUsb, &desc, &usb_param);
//		if (ret == LPC_OK) {
//			/*  enable USB interrrupts */
//			NVIC_EnableIRQ(USB0_IRQn);
//			/* now connect */
//			USBD_API->hw->Connect(g_hUsb, 1);
//		}
//	}
//}
