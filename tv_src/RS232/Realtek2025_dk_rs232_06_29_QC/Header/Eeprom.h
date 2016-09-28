//----------------------------------------------------------------------------------------------------
// ID Code      : Eeprom.h No.0000
// Update Note  : 
//
//----------------------------------------------------------------------------------------------------

//--------------------------------------------------
// Definitions of EEPROM 2404/2416
//--------------------------------------------------
#define _EEPROM_ADDRESS                 0xA0


//--------------------------------------------------
// Definitions of Eeprom Data Address
//--------------------------------------------------
#define _EEPROM_PAGE0_BANK0             0
#define _EEPROM_PAGE0_BANK1             128
#define _EEPROM_PAGE1_BANK0             256
#define _EEPROM_PAGE1_BANK1             384
#define _EEPROM_PAGE2_BANK0             512
#define _EEPROM_PAGE2_BANK1             640
#define _EEPROM_PAGE3_BANK0             768
#define _EEPROM_PAGE3_BANK1             896
#define _EEPROM_PAGE4_BANK0             1024
#define _EEPROM_PAGE4_BANK1             1152
#define _EEPROM_PAGE5_BANK0             1280
#define _EEPROM_PAGE5_BANK1             1408
#define _EEPROM_PAGE6_BANK0             1536
#define _EEPROM_PAGE6_BANK1             1664
#define _EEPROM_PAGE7_BANK0             1792
#define _EEPROM_PAGE7_BANK1             1920

#define _EDID0_ADDRESS                  (_EEPROM_PAGE2_BANK0)
#define _EDID1_ADDRESS                  (_EEPROM_PAGE2_BANK1)
#define _MODE_DATA_0_ADDRESS            (_EEPROM_PAGE0_BANK0)
#define _USER_FIFO_MODE_DATA_0_ADDRESS  (_EEPROM_PAGE1_BANK1 + 64)
#define _USER_FIFO_MODE_DATA_1_ADDRESS  (_EEPROM_PAGE3_BANK0)
#define _USER_DATA_ADDRESS              (_EEPROM_PAGE3_BANK1)

#define _SYSTEM_DATA_ADDRESS            (_USER_DATA_ADDRESS + 0)
#define _OSDUSER_DATA_ADDRESS           (_SYSTEM_DATA_ADDRESS + sizeof(StructSystemDataType))
#define _VGA_ADC_DATA_ADDRESS               (_OSDUSER_DATA_ADDRESS + sizeof(StructOsdUserDataType))
#define _YPbPr_ADC_DATA_ADDRESS               (_VGA_ADC_DATA_ADDRESS + sizeof(StructAdcDataType) + 2)
#define _VIDEO_ADC_DATA_ADDRESS               (_YPbPr_ADC_DATA_ADDRESS +sizeof(StructAdcDataType)  + 2)
#define _BriConHueSat_PROC0_ADDRESS            (_VIDEO_ADC_DATA_ADDRESS + sizeof(StructAdcDataType)+ 2) //V307 modify
#define _COLORTEMP_DATA_ADDRESS         (_BriConHueSat_PROC0_ADDRESS + (sizeof(StructColorProc0DataType)) * 5)
#define _VIDEO_DATA_ADDRESS             (_COLORTEMP_DATA_ADDRESS + (sizeof(StructColorTempDataType)) * 3)
#define _MODE_CENTER_DATA_ADDRESS       (_EEPROM_PAGE4_BANK0)



//--------------------------------------------------
// Definitions of Flash Page Index for RTD2120S
//--------------------------------------------------
#define _PRESET                        0    
#define _AUTO_PRESET                   1
#define _FIFO                          2
#define _USER                          3
#define _AUTO_USER                     4
#define _GLOBAL                        5
#define _EDID                         31

#define _START_PAGE                    0 //(0~20)
#define _END_PAGE                     30 //(25~30)
//----------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------

#ifdef __EEPROM__

//--------------------------------------------------
// Global Variables
//--------------------------------------------------


//--------------------------------------------------
// Function Prototypes
//--------------------------------------------------
void CEepromStartupCheck(void);
void CRecallTVData(void);
void CEepromLoadDefault(BYTE ucMode);
bit CEepromWrite(WORD usAddr, WORD usLength, BYTE *pWriteArray);
bit CEepromRead(WORD usAddr, WORD usLength, BYTE *pReadArray);
void CEepromSaveModeData(BYTE ucMode);
void CEepromLoadModeData(BYTE ucMode);
void CEepromInitialModeData(void);
void CEepromSaveUserFIFOModeData(StructModeUserFIFODataType stUserFIFOMode);
void CEepromLoadUserFIFOModeData(BYTE ucNum, BYTE *pArray);
void CEepromInitialUserFIFOModeData(void);
void CEepromSaveCenterModeData(BYTE ucMode);
void CEepromLoadCenterModeData(BYTE ucMode);
void CEepromInitialCenterModeData(void);
void CEepromSaveSystemData(void);
void CEepromLoadSystemData(void);
void CEepromLoadSystemDataDefault(void);
void CEepromSaveOsdUserData(void);
void CEepromLoadOsdUserData(void);
void CEepromLoadOsdUserDataDefault(void);
void CEepromSaveAdcData(void);
void CEepromLoadAdcData(void);
void CEepromLoadAdcDataDefault(void);
void CEepromSaveBriConData(void);
void CEepromLoadBriConData(void);
void CEepromLoadBriConDataDefault(void);
void CEepromSaveColorTempData(void);
void CEepromLoadColorTempData(void);
void CEepromLoadColorTempDataDefault(void);
void CEepromSaveEDIDData(void);
void CEepromLoadEDIDData(void);
void CEepromLoadEDIDDataDefault(void);

#if(_VIDEO_SUPPORT)
void CEepromLoadVedioColor(void);
void CEepromSaveVedioColor(void);
void CEepromLoadVedioColorDefault(void);
#endif   //#if(_VIDEO_SUPPORT)

#else

//--------------------------------------------------
// Extern Global Variables
//--------------------------------------------------


//--------------------------------------------------
// Extern Function Prototypes
//--------------------------------------------------
extern void CRecallTVData(void);
extern void CEepromStartupCheck(void);
extern void CEepromLoadDefault(BYTE ucMode);
extern bit CEepromWrite(WORD usAddr, WORD usLength, BYTE *pWriteArray);
extern bit CEepromRead(WORD usAddr, WORD usLength, BYTE *pReadArray);
extern void CEepromSaveModeData(BYTE ucMode);
extern void CEepromLoadModeData(BYTE ucMode);
extern void CEepromInitialModeData(void);
extern void CEepromSaveUserFIFOModeData(StructModeUserFIFODataType stUserFIFOMode);
extern void CEepromLoadUserFIFOModeData(BYTE ucNum, BYTE *pArray);
extern void CEepromInitialUserFIFOModeData(void);
extern void CEepromSaveCenterModeData(BYTE ucMode);
extern void CEepromLoadCenterModeData(BYTE ucMode);
extern void CEepromInitialCenterModeData(void);
extern void CEepromSaveSystemData(void);
extern void CEepromLoadSystemData(void);
extern void CEepromLoadSystemDataDefault(void);
extern void CEepromSaveOsdUserData(void);
extern void CEepromLoadOsdUserData(void);
extern void CEepromLoadOsdUserDataDefault(void);
extern void CEepromSaveAdcData(void);
extern void CEepromLoadAdcData(void);
extern void CEepromLoadAdcDataDefault(void);
extern void CEepromSaveBriConData(void);
extern void CEepromLoadBriConData(void);
extern void CEepromLoadBriConDataDefault(void);
extern void CEepromSaveColorTempData(void);
extern void CEepromLoadColorTempData(void);
extern void CEepromLoadColorTempDataDefault(void);
extern void CEepromSaveEDIDData(void);
extern void CEepromLoadEDIDData(void);
extern void CEepromLoadEDIDDataDefault(void);

extern BYTE CGetInputSourceNum(BYTE ucInputSource);

#if(_VIDEO_SUPPORT)
extern void CEepromLoadVedioColor(void);
extern void CEepromSaveVedioColor(void);
extern void CEepromLoadVedioColorDefault(void);
#endif    //#if(_VIDEO_SUPPORT)

#endif
//----------------------------------------------------------------------------------------------------

