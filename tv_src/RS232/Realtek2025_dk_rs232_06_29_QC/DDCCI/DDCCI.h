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

#define DDCCI_ALL            1
#define DEBUG_ONLY           1

// define for mtv512
#define TXBI	0x80
#define RCBI	0x40

// define for rtd2120
#define DOUTI                   0x08
#define DINI                    0x04
#define SUBI                    0x02
#define SLVI                    0x01

#define STOPI                   0x10

#define	DDC2B_CLEAR                     0
#define	DDC2B_SRCADDRESS                1
#define	DDC2B_COMMAND                   2
#define	DDC2B_RECBODY                   3
#define	DDC2B_WAITFORCK                 4
#define	DDC2B_COMPLETED                 5

// DDC2Bi standard definitions
#define	DDC2B_DEST_ADDRESS              0x6e
#define	DDC2B_SRC_ADDRESS               0x51
#define	DDC2Bi_PROTOCOL_ID		0x01
#define	DDC2Bi_CONTROL_STATUS_FLAG	0x80

#define	INITRxCK                        (DDC2B_SRC_ADDRESS ^ DDC2B_DEST_ADDRESS)
#define	INITTxCK                        (0x50 ^ DDC2B_DEST_ADDRESS)

// receive/transmit buffer syntax defines
#define	CI_LENGTH                       0
#define	COMMAND                         1
#define	PARAMETER                       2

#define DDC2B_MSGON                     1

//DDC2Bi commands
#define DDC2B_CMD_DEBUG                                 0xC2
#define DDC2B_CMD_GetVCPFeature                         0x01
#define DDC2B_CMD_GetVCPFeature_Reply                   0x02
#define DDC2B_CMD_SetVCPFeature                         0x03
#define DDC2B_CMD_SaveCurrentSettings                   0x0C
#define DDC2B_CMD_CapabilitiesRequest                   0xF3
#define DDC2B_CMD_CapabilitiesRequest_Reply             0xE3
#define DDC2B_CMD_GetTimingReport                       0x07

#define DDC2B_CMD_VCP_ALLReset				0x04
#define DDC2B_CMD_VCP_GeometryReset			0x06
#define DDC2B_CMD_VCP_ColorReset			0x08
#define DDC2B_CMD_VCP_Clock			      	0x0E
#define DDC2B_CMD_VCP_Brightness			0x10
#define DDC2B_CMD_VCP_Contrast				0x12
#define DDC2B_CMD_VCP_SelectColorPreset	                0x14
#define DDC2B_CMD_VCP_RedGain				0x16
#define DDC2B_CMD_VCP_GreenGain				0x18
#define DDC2B_CMD_VCP_BlueGain				0x1A
#define DDC2B_CMD_VCP_AutoSetUp				0x1E
#define DDC2B_CMD_VCP_HPosition				0x20
#define DDC2B_CMD_VCP_VPosition				0x30
#define DDC2B_CMD_VCP_HPosOSD				0x38
#define DDC2B_CMD_VCP_VPosOSD				0x39
#define DDC2B_CMD_VCP_ClockPhase			0x3E
#define DDC2B_CMD_VCP_ColorTemp				0x54
#define DDC2B_CMD_VCP_AudioVolume			0x62
#define DDC2B_CMD_VCP_Language				0x68
#define DDC2B_CMD_VCP_TVSaturation			0x8A
#define DDC2B_CMD_VCP_TVSharpness			0x8C
#define DDC2B_CMD_VCP_RED				0x9B
#define DDC2B_CMD_VCP_YELLOW				0x9C
#define DDC2B_CMD_VCP_GREEN				0x9D
#define DDC2B_CMD_VCP_CYAN				0x9E
#define DDC2B_CMD_VCP_BLUE				0x9F
#define DDC2B_CMD_VCP_MAGENDA				0xA0
#define DDC2B_CMD_VCP_SyncType				0xA8
#define DDC2B_CMD_VCP_RGBodering			0xB4
#define DDC2B_CMD_VCP_MonitorType			0xB6
#define DDC2B_CMD_VCP_PowerStatus			0xD6
#define DDC2B_CMD_VCP_ControlLock			0xE3



//NMV Custom commands
#define DDC2B_CMD_NMV_GetVCPPage            0xC4
#define DDC2B_CMD_NMV_GetVCPPage_Reply	    0xC5
#define DDC2B_CMD_NMV_GetPagedVCP	    0xC6
#define DDC2B_CMD_NMV_GetPagedVCP_Reply	    0xC7
#define DDC2B_CMD_NMV_SetPagedVCP	    0xC8
#define DDC2B_CMD_NMV_SetPagedVCP_Reply	    0xC7
#define DDC2B_CMD_NMV_EEPROM		    0xC0
#define DDC2B_CMD_NMV_EEPROM_Reply	    0xC1

//NMV EEPROM commands
#define DDC2B_CMD_NMV_EEPROMWrite		0x02
#define DDC2B_CMD_NMV_EEPROMRead		0x09
#define DDC2B_CMD_NMV_ModeChangeRequest	        0x11
#define DDC2B_CMD_NMV_AssetRead			0x0B
#define DDC2B_CMD_NMV_AssetWrite		0x0E


#define DDC2B_CMD_VCP_ContrastAuto		0x37
#define DDC2B_CMD_VCP_OSDHPosition		0x38
#define DDC2B_CMD_VCP_OSDVPosition		0x39
#define DDC2B_CMD_VCP_COLORCHANGED		0x3B
#define DDC2B_CMD_VCP_HOURSTOTAL		0x47
#define DDC2B_CMD_VCP_HOURSON			0x64
#define DDC2B_CMD_VCP_HOURSOFF			0x65


//andy define cmd 1
#define DDC2B_CMD_VCP_SAVECOLORTMPSTATE		0xa1
#define DDC2B_CMD_VCP_STOP			0xa2
#define DDC2B_CMD_VCP_START			0xa3

#define RGain_Offset                             20
#define GGain_Offset                             20
#define BGain_Offset                             0

//----------Andy---------------------------------
#define M512_IIC_CTR         MCU_IICCTR_F00
#define M512_IIC_INTEN       MCU_INTEN_F04
#define M512_INTFLG          MCU_INTFLG_F48
#define M512_CTRSLVB         MCU_CTRSLVB_F0A
#define M512_PadMode2        MCU_PADMODE_F52
#define M512_IIC_TXRCABUF    MCU_DDCCTRA1_F06
#define M512_IIC_SLVAADR     MCU_SLVA1ADR_F07
#define M512_DDCCTRA2        MCU_DDCCTRA2_F86
#define M512_SLVA2ADR        MCU_SLVA2ADR_F87
#define M512_IIC_SLVBADR     MCU_SLVBADR_F09
#define M512_IIC_INTFLG	     MCU_INTFLG_F03
#define M512_IIC_TXRCBBUF    MCU_RCTXBBUF_F08

#define Delay_Xms(x)                   CTimerDelayXms(x)
#define RTDRead(index, count, inc)     CScalerRead(index, count, pData, inc)
#define RTDSetByte(Addr,Value)	       CScalerSetByte(Addr,Value)
#define I2CRead(Addr,Index,Count)      CI2cRead(Addr,Index,Count, pData)
#define Data			       pData


#define RX_BUFFER_SIZE                  32
#define TX_BUFFER_SIZE                  32


#ifdef __DDCCI__

unsigned char xdata rxStatus = DDC2B_CLEAR;
unsigned char xdata ucDDCCI_CheckSum = 0;
unsigned char xdata ucDDCCI_RxCount  = 0;
unsigned char xdata ucDDCCI_RxIndex  = 0;
unsigned char xdata ucDDCCI_TxCount  = 0;
unsigned char xdata ddc2biTimeout = 30;
unsigned char xdata ucDDCCI_NullStr[4] = {0x6e,0x80,0xbe,0x6e};
unsigned char xdata ucDDCCI_RxBuf[RX_BUFFER_SIZE];// _at_ RX_BUF_ADDR;
unsigned char xdata ucDDCCI_TxBuf[TX_BUFFER_SIZE];// _at_ 0xF832;//(RX_BUF_ADDR + RX_BUFFER_SIZE);

unsigned char xdata ucVPC_Page   = 0;
bit txStatus     = DDC2B_CLEAR;
bit readExpected = 0;
bit messageReady = 1;
bit fDDCCI_Loop  = 0;

unsigned char xdata *txBufferPtr;

void DDCCI_RxInt();
void DDCCI_TxInt();
void DDCCI_InitRx(void);
void DDC2Bi_InitTx(void);
void TxCommandReady();
void DDCCI_Command();
void DDCCI_Command_Do();
void GetVCPFeature();
void SetVCPFeature();


void GetVPC_Clock(unsigned char BassAddr);
void GetVPC_Bright(unsigned char BassAddr);
void GetVPC_Contrast(unsigned char BassAddr);
void GetVPC_RedGain(unsigned char BassAddr);
void GetVPC_GreenGain(unsigned char BassAddr);
void GetVPC_BlueGain(unsigned char BassAddr);
void GetVPC_HPosition(unsigned char BassAddr);
void GetVPC_VPosition(unsigned char BassAddr);
void GetVPC_Phase(unsigned char BassAddr);
void GetVPC_ColorTmp(unsigned char BassAddr);
void GetMonitorType(unsigned char BassAddr);
void GetVPC_Language(unsigned char BassAddr);

void SetVPC_ALLReset(unsigned char ucValue);
void SetVPC_ColorReset(unsigned char ucValue);
void SetVPC_Clock(unsigned char ucValue);
void SetVPC_ClockDo();
void SetVPC_Bright(unsigned char ucValue);
void SetVPC_BrightDo();
void SetVPC_Contrast(unsigned char ucValue);
void SetVPC_ContrastDo();
void SetVPC_RedGain(unsigned char ucValue);
void SetVPC_RedGainDo(unsigned char ucValue);
void SetVPC_GreenGain(unsigned char ucValue);
void SetVPC_GreenGainDo(unsigned char ucValue);
void SetVPC_BlueGain(unsigned char ucValue);
void SetVPC_BlueGainDo(unsigned char ucValue);
void SetVPC_HPosition(unsigned int ucValue);
void SetVPC_HPositionDo();
void SetVPC_VPosition(unsigned int ucValue);
void SetVPC_VPositionDo();
void SetVPC_Phase(unsigned char ucValue);
void SetVPC_PhaseDo();
void SetVPC_ColorTmp(unsigned char ucValue);   //VCP(14(05 08 0B))
void SetVPC_ColorTmpDo();
void SetVPC_Language(unsigned char ucValue);
// Andy add
void SetVPC_SaveColorTmpState();

void DDCCI_SaveSetting();
void DDCCI_EEPRom_Cmd();
void DDCCI_ModeChg();
void DDCCI_EEProm_Read();
void DDCCI_EEProm_Write();

void DDCCI_GetTimingReport();
void DDCCI_GetCapabilitiesRequest();
void DDCCI_GetVCPPage();

void DDCCI_GetPagedVCP();
void DDCCI_SetPagedVCP();
void GetNMVVPC_OSDH();
void GetNMVVPC_OSDV();
void SetNMVVPC_Auto();
void SetNMVVPC_OSDH();
void SetNMVVPC_OSDV();
void AnwerDDCCISet();

void I2CWrite(unsigned char *Array);


#else

extern unsigned char xdata rxStatus;
extern unsigned char xdata ucDDCCI_CheckSum;
extern unsigned char xdata ucDDCCI_RxCount;
extern unsigned char xdata ucDDCCI_RxIndex;
extern unsigned char xdata ucDDCCI_TxCount;
extern unsigned char xdata ddc2biTimeout;
extern unsigned char xdata ucDDCCI_NullStr[4];
extern unsigned char xdata ucDDCCI_RxBuf[RX_BUFFER_SIZE];
extern unsigned char xdata ucDDCCI_TxBuf[RX_BUFFER_SIZE];

extern unsigned char xdata ucVPC_Page;
extern bit txStatus;
extern bit readExpected;
extern bit messageReady;
extern bit fDDCCI_Loop;

extern void DDCCI_Command();
extern void Init_DDCCI();
extern void TxCommandReady();
extern void I2CWrite(unsigned char *Array);

extern void DDCCI_RxInt();
extern void DDCCI_TxInt();
#endif

#endif
