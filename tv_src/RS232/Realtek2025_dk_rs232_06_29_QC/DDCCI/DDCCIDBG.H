////////////////////////////////////////////////////////////////////////////
//         Copyright of Vector Co.,Ltd.                                   //
//                                                                        //
//                                                                        //
//                           DDCCI  Definitions                           //
//   Ver: 5.00                                                            //
//   Create file time: 2006.5.15                                          //
//   End modify time: 2007.3.28                                           //
//   For RTD2523B/RTD2525L/RTD2553V                                       //
////////////////////////////////////////////////////////////////////////////
#if(_SUPPORTDDCCI)

#define DDC2B_CMD_DBG_READRTD                   0xa1
#define DDC2B_CMD_DBG_WRITERTD                  0xa2
#define DDC2B_CMD_DBG_READIIC                   0xa3
#define DDC2B_CMD_DBG_WRITEIIC                  0xa4
#define DDC2B_CMD_DBG_WRITERTDEX                0xa5

#define DDC2B_CMD_DBG_STOP                      0xa9
#define DDC2B_CMD_DBG_RUN                       0xaa
//#define DDC2B_CMD_DBG_GETDBGSTR                 0xab
//#define DDC2B_CMD_DBG_CUSTOM_CMD                0xac
#define DDC2B_CMD_DBG_SET_PARAM                 0xad

#define DDC2B_CMD_DBG_READ512REG                0xae
#define DDC2B_CMD_DBG_WRITE512REG               0xaf


#define DDC2B_CMD_DBG_VIRTUALKEY                0xb0

#define DDC2B_CMD_DBG_CHGTOUART                 0xb1
#define DDC2B_CMD_DBG_READ_RTD2120REG           0xb2
#define DDC2B_CMD_DBG_WRITE_RTD2120REG          0xb3


#ifdef __DDCCIDBG__

unsigned char xdata ucVirtualKey = _NONE_KEY_MESSAGE;


void DDCCI_Debug();
void DDCCI_DBG_Read_RTD();
void DDCCI_DBG_Write_RTD();
void DDCCI_DBG_Read_IIC();
void DDCCI_DBG_Write_IIC();
void DDCCI_DBG_Write_RTDEX();
void DDCCI_DBG_Stop();
void DDCCI_DBG_Run();

void DDCCI_DBG_VirtualKey();
void DDCCI_DBG_Read512Reg();
void DDCCI_DBG_Write512Reg();
void GetVirtualKey();
void DDCCI_DBG_ChgUart();
void DDCCI_DBG_ReadRTD2120Reg();
void DDCCI_DBG_WriteRTD2120Reg();


#endif    //#ifdef __DDCCIDBG__

extern unsigned char xdata ucVirtualKey;

extern void DDCCI_Debug();
extern void GetVirtualKey();

#endif    //#if(SUPPORTDDCCI)
