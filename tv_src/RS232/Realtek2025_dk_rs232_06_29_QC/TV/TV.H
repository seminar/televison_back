
//=======================================================================================
//                                                                                      ]
//EEPROM address: 0xAC  0x50~0xFF    [ Save channel freq or tv sound and tv color type  ]
//EEPROM address: 0xAE  0x00~0xFC    [ Save channel freq or tv sound and tv color type  ]
//                      0xFE         [ Search max channel                               ]
//                      0xFF         [ User select search ch tv and sound type          ]
// Modify TV EEPROM address by EricLee 04-30-2007                                       ]
//=======================================================================================
// Definitions for max channel count

#define _TV_SYSTEM_EEPROM_ADDR       0xAC   // 24C16 Page 6
#define _TV_SYSTEM_START_ADDR        0x70   // Save tv system data start address

#define _MAX_CHANNEL_COUNT           ((WORD)((0xFF-_TV_SYSTEM_START_ADDR+0xFF-2)/3))

#define _TV_FREQ_EEPROM_ADDR0        0xAC   // 24C16 Page 6
#define _TV_FREQ_EP_START_ADDR0      (((_TV_SYSTEM_START_ADDR+_MAX_CHANNEL_COUNT)/2)*2 + 2) // Freq page6 start address
#define _TV_FREQ_EP0_TV_NUMBER       ((0xFF-_TV_FREQ_EP_START_ADDR0)/2)         // Page6 save tv channel total
#define _TV_FREQ_EEPROM_ADDR1        0xAE   // 24C16 Page 7
#define _TV_MAX_CHANNEL_EEPROM_ADDR  0xAE   // 24C16 Page 7
//#define EEPROM_SEARCH_TYPE_ADDR        0xFF
#define _MAX_CHANNEL_ADDR            0xFE

// Definitions for auto power down
#define _AUTO_POWER_DOWN             _ON
#if(_AUTO_POWER_DOWN)
#define _ONE_MINUTE_COUNT            60000  // On minute count 1ms*60000 = 1 minute
#endif

#define _SHOW_CH_TV_NUMBER         0x01
#define _SHOW_CH_TV_TYPE           0x02
#define _SHOW_CH_SOUND_TYPE        0x04
#define _GET_BLUE_BACKGROUND()     ((stSystemData.MonitorFlag & _BIT6) >> 6)
#define _SET_BLUE_BACKGROUND(x)    stSystemData.MonitorFlag = (stSystemData.MonitorFlag & (~_BIT6)) | (x << 6)
#define _GET_POWER_DOWN_TIME()     (stSystemData.MonitorFlag & 0x07)
#define _SET_POWER_DOWN_TIME(x)    stSystemData.MonitorFlag = (stSystemData.MonitorFlag & 0xf8) | x
#define _GET_INPUTCH_STATE()       ((stOsdUserData.OsdSettingFlag & 0x0c) >> 2)
#define _SET_INPUTCH_STATE(x)      stOsdUserData.OsdSettingFlag = (stOsdUserData.OsdSettingFlag & 0xf3) | (x << 2)

#define _GET_CATV_AIR()     ((stSystemData.MonitorFlag & _BIT5) >> 5)
#define _SET_CATV_AIR(x)    stSystemData.MonitorFlag = (stSystemData.MonitorFlag & (~_BIT5)) | (x << 5)

//add by chenlinfu
#if(_NTSC_SEARCH_TABLE)
#define MAX_CHANNEL_CATV			126
#define MAX_CHANNEL_AIR			70

#endif
//----------------------------------------------------------
//Definitions for change channel Method
#define _CHANGE_CHANNEL_M1   0   // Normal Method
#define _CHANGE_CHANNEL_M2   1

#define _CHANGE_CHANNEL_MTD  _CHANGE_CHANNEL_M2

//----------------------------------------------------------
//Definitions for change channel
#define _PREV_CHANNEL        0
#define _NEXT_CHANNEL        1


//----------------------------------------------------------
//Definitions for tuner mute on/off
#define _TUNER_MUTE_ON       1
#define _TUNER_MUTE_OFF      0

//----------------------------------------------------------
#define _TV_TYPE_SUPPORT     1       // Support this type
#define _TV_TYPE_NOT_SUPPORT 0       // Not support this type

//----------------------------------------------------------
//Definitions for TB1334
#define _SEARCH_CHANNEL_MODE 0x00
#define _NORMAL_MODE         0x80
#define _SPLIT_CARRIER       0
#define _INTER_CARRIER       1

//----------------------------------------------------------
// Definitions for TV chip
#define _TV_NONE             0       // 0:No tv chip
#define _TV_JS_6B1           1       // 1:EYTYANT JS_6B1/111 for PAL B/G,PAL I,PAL D/K,NTSC M/N           // Ready
#define _TV_JS_6B2           2       // 2:EYTYANT JS_6B2/121 for PAL B/G,PAL I,PAL D/K,SECAM L,SECAM L'   // Not ready
#define _TV_JS_6AM           3       // 3:EYTYANT JS_6AM for NTSC M/N only                                // Not ready
#define _TV_FQ1216ME         4       // 4:Philips FQ1216ME/I H-5
#define _TV_JS_6H2_122A2     5       // 5:JS-6H2/122A2-A2
#define _TV_TDQ_6F6          6       // 6:XuGuang TDQ-6F6/T126CW
#define _TNF_8337            7       // 7:TNF 8337-BFD
#define _TV_TDQ_G4X002A      8       // 8:Alps TDQG4X002A DVB+ATV

#if (_VIDEO_TV_SUPPORT)
#define _TV_CHIP              _TNF_8337
#else
#define _TV_CHIP              _TV_NONE
#endif

//----------------------------------------------------------
// Definitions for TV color
#if(_VIDEO_TV_SUPPORT)
#define _TV_NTSC_M            0x00    // 60Hz Sound 4.5M  NTSC M
#define _TV_NTSC_4_BG         0x01    // 60Hz Sound 5.5M  NTSC 4/BG
#define _TV_NTSC_4_DK         0x02    // 60Hz Sound 6.5M  NTSC 4/DK
#define _TV_NTSC_4_I          0x03    // 60Hz Sound 6.0M  NTSC 4/I
#define _TV_PAL_M             0x04    // 60Hz Sound 4.5M  PAL M

#define _TV_PAL_BG            0x05    // 50Hz Sound 5.5M  PAL B/G
#define _TV_PAL_I             0x06    // 50Hz Sound 6.0M  PAL I
#define _TV_PAL_DK            0x07    // 50Hz Sound 6.5M  PAL D/K
#define _TV_PAL_N             0x08    // 50Hz Sound 4.5M  PAL N

#define _TV_SECAM_BG          0x09    // 50Hz Sound 5.5M  SECAM B/G
#define _TV_SECAM_DK          0x0a    // 50Hz Sound 6.5M  SECAM D/K
#define _TV_SECAM_L           0x0b    // 50Hz Sound 6.5M  SECAM L
#define _TV_SECAM_LL          0x0c    // 50Hz Sound 6.5M  Secam L'

#endif

#define _TUNER_BP                20


#define _ADDR_TUNER              0xC0    // address select    
#define _VHF_LOW_BAND        (164.75 * _TUNER_BP + (WORD)(_PIF_FREQ * _TUNER_BP/1000)) 
#define _VHF_HIGH_BAND           (467.25 * _TUNER_BP + (WORD)(_PIF_FREQ * _TUNER_BP/1000)) 

#define _MAX_TV_TYPE             _TV_SECAM_L//_TV_PAL_DK
#define _MIN_TV_TYPE             _TV_NTSC_M//_TV_PAL_DK

#define _MAX_FREQ                ((864.25 * _TUNER_BP+ (WORD)(_PIF_FREQ* _TUNER_BP/1000)))
#define _MIN_FREQ                ((43* _TUNER_BP + (WORD)(_PIF_FREQ* _TUNER_BP/1000))  )

#if(_NTSC_SEARCH_TABLE)
#define _NORMAL_TV_TYPE          _TV_NTSC_M
#else
#define _NORMAL_TV_TYPE          _TV_PAL_I 
#endif


//----------------------------------------------------------
#if (_TV_CHIP == _TV_JS_6H2_122A2)  
#define _ADDR_9886            0x84    // For JS-6H2/122A2-A2
#else
#define _ADDR_9886            0x86    // Philips TDA9886 address select
#endif



extern BYTE idata ucTVType;
#if(_VIDEO_TV_SUPPORT)

#ifndef __TV__
#define __TV__
extern bit bChangeChannel;

extern BYTE xdata ucPrevChannel;
extern WORD xdata ucCurrentInputNumber;
extern BYTE xdata ucCurrentInputState;  // 0: no input number   1: input one number     2: input two number    3: input three number


void CForceBackGroundToBlack(void);

void gmi_CI2CWrite9886(BYTE ucTvType, const bit bTunerMute, BYTE ucMode);
void gmi_CSetTuner(BYTE ucTunerAddress, WORD Freq);
void CTvAutoSearch(void);
void CSetTVChannel(const BYTE ucCurrentChannel);
void CChangeChannel(bit bNext);

//void CPrevChannel(void);
//void CNextChannel(void);
BYTE CloadMaxChannelNumber(bit uctemp);
BYTE CloadMinChannelNumber(void);
void CManualSearch(const bit bSearchAction, const BYTE ucCurrentChannel);
void CTuningCurrentChannel(const bit bSearchAction, const BYTE ucCurrentChannel);
BYTE CLoadChannelSoundType(const BYTE ucCurrentChannel);
void CSaveChannelSoundType(const BYTE ucCurrentChannel, const BYTE ucSoundType);
BYTE CLoadChannelColorType(const BYTE ucCurrentChannel);
void CSaveChannelColorType(const BYTE ucCurrentChannel, const BYTE TVType);
WORD CLoadChannelFreq(const BYTE ucCurrentChannel);
void CSaveChannelFreq(const WORD iFreq, const BYTE ucCurrentChannel);
BYTE CLoadChannelSoundType(const BYTE ucCurrentChannel);
bit  CLoadChannelSkip(const BYTE ucCurrentChannel);
void CSaveChannelSkip(const bit bSkip, const BYTE ucCurrentChannel);
void CInitTV();
BYTE CDetectTVSignalType(void);
void CSaveChannelData(const WORD iFreq, const BYTE ucSound, const BYTE ucChannelNumber);

//WORD CLockChannelDown(WORD iCurrFreq);
//WORD CLockChannelUp(const WORD StartFreq);
WORD CLockChannel(WORD iStartFreq, const bit bCLockMode);

void CModeResetTVMode(void);
void CModeResetTVNtscToPal(void)  ;
#if(_VIDEO_CHIP == _VDC_TB1334)
BYTE bCurrentTVColorMode(void);
#endif
#endif    //#ifndef __TV__
extern void CModeResetTVNtscToPal(void)  ;
#endif 
