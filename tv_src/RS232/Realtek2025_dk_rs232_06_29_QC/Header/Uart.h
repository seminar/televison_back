

#if(_RS232)

#define UartCMD_OFFSET1 			0x00
#define UartCMD_OFFSET2 			0xB0
#define UartCMD_OFFSET				UartCMD_OFFSET2

#define UartCMD_DebugModeEnter		(0x10 + UartCMD_OFFSET)
#define UartCMD_DebugModeExit		(0x11 + UartCMD_OFFSET)
#define UartCMD_CScalerRead			(0x20 + UartCMD_OFFSET)
#define UartCMD_CScalerWrite		(0x30 + UartCMD_OFFSET)
#define UartCMD_I2CRead				(0x21 + UartCMD_OFFSET)
#define UartCMD_I2CWrite 			(0x31 + UartCMD_OFFSET)

// not use
#define UartCMD_24C32Read       	(0x26 + UartCMD_OFFSET)
#define UartCMD_24C32Write      	(0x36 + UartCMD_OFFSET)
#define UartCMD_TunerRead			(0x24 + UartCMD_OFFSET)
#define UartCMD_TunerWrite			(0x34 + UartCMD_OFFSET)
#define UartCMD_FlashRead			(0x25 + UartCMD_OFFSET)

#define UartCMD_RS232Control		0xA0  
#define UartCMD_MUTE 		              0xDF  // EB
#define UartCMD_MENU 			       0xD4  // 2B
#define UartCMD_VOLUMERIGHT 		0x9F  // FA
#define UartCMD_OK			              0x9B  // FD
#define UartCMD_DOWN			       0xD8 // F2
#define UartCMD_UP 			              0x92  // E8
#define UartCMD_VOLUMELEFT 	    	0x97  // F3
#define UartCMD_SOURCE 			       0xC3  // FE
#define UartCMD_NUM1                          0x95  // BD
#define UartCMD_NUM2                          0x99  // BC
#define UartCMD_NUM3                          0x9D  // F0
#define UartCMD_NUM4                          0xD6  // E1
#define UartCMD_NUM5                          0xDA  // E2
#define UartCMD_NUM6                          0xDE // E3
#define UartCMD_NUM7                          0x96  // E7
#define UartCMD_NUM8                          0x9A  // BA
#define UartCMD_NUM9                          0x9E  // B3
#define UartCMD_NUM0                           0xD9 // A9
#define UartCMD_POWERON 	              0xD7  // F4
#define UartCMD_EXIT 	              0xDC  // F4
#define UartCMD_VOLINC              0x83  // F4
#define UartCMD_VOLDEC	              0x86  // F4
#define UartCMD_CHINC	              0x80  // F4
#define UartCMD_CHDEC	              0x8E  // F4
#define UartCMD_SLEEP	              0xC0  // F4
#define UartCMD_AV	              0x32  // F4
#define UartCMD_VGA	              0x18 // F4
#define UartCMD_HDMI              0x16 // F4
#define UartCMD_TV              0x1A // F4
#define UartCMD_DTV              0x19 // F4
#define UartCMD_DVD              0x06 // F4

#define UartCMD_POWERSTTATUSON	0xA3
#define UartCMD_POWERSTTATUSOFF 	0xA2
#define UartCMD_POWEROFF	              0x01



extern bit fInUartMode;

extern bit  fUartStart;
extern bit  fUartRxCmdSuccess;
extern bit  fUartDebugLoop;

extern BYTE xdata ucUartRxIndex;
extern BYTE xdata ucUartRxCount;
extern BYTE xdata pUartData[9];
extern bit fInitCmdlength;

void CUartInit(void);
void CSwitchToUart(void);
void CSwitchToI2C(void);
/*
void CUartPrintf(char *pStr,WORD usValue);
void CUartPrintfHex(BYTE ucValue);
void CUartPrintfDec(WORD usValue);
void CUartPutCharToScr(BYTE ch);
*/
void DebugPrintf(const BYTE code* pstr,BYTE value);
void CUartPutToScr(const BYTE ch,const BYTE mode);
void CUartPutCharToScr(BYTE ch);
void CUartHandler(void);
void UartCMDDebugModeExit(void);
void UartCMDDebugModeEnter(void);
void UartCMDScalerRead(void);
void UartCMDScalerWrite(void);
void UartCMDRS232Control(void);

#endif

