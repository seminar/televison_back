//----------------------------------------------------------------------------------------------------
// ID Code      : Struct.h No.0001
// Update Note  : 
//
//----------------------------------------------------------------------------------------------------

//--------------------------------------------------
// Definitions of Color Temperature
//--------------------------------------------------
#define _DISPLAY_MODE_16_9              0
#define _DISPLAY_MODE_4_3               1

#if (_SCALER_TYPE == _RTD2553V || _SCALER_TYPE == _RTD2546N || _SCALER_TYPE == _RTD2525L)
//--------------------------------------------------
// Macro of 
//--------------------------------------------------
//*************** Six Axes Color ***************//

#define GET_MZ_DCC_TYPE()               (stOsdUserData.MZDCC & (_BIT2 | _BIT1 | _BIT0))
#define SET_MZ_DCC_TYPE(x)              (stOsdUserData.MZDCC = ((stOsdUserData.MZDCC & ~(_BIT2 | _BIT1 | _BIT0)) | x))

#define GET_MZ_WINDOW_CFG_TYPE()        ((stOsdUserData.MZDCC & (_BIT4 | _BIT3)) >> 3)
#define SET_MZ_WINDOW_CFG_TYPE(x)       (stOsdUserData.MZDCC = ((stOsdUserData.MZDCC & ~(_BIT4 | _BIT3)) | (x << 3)))

#define GET_SAC_DCC_TYPE()              ((stOsdUserData.MZDCC & (_BIT7 | _BIT6 | _BIT5)) >> 5)
#define SET_SAC_DCC_TYPE(x)             (stOsdUserData.MZDCC = ((stOsdUserData.MZDCC & ~(_BIT7 | _BIT6 | _BIT5)) | (x << 5)))

#define GET_MZ_ICM_ON_OFF_TYPE()        (stOsdUserData.OsdManagementFlag & _BIT0)
#define SET_MZ_ICM_ON_OFF_TYPE(x)       (stOsdUserData.OsdManagementFlag = ((stOsdUserData.OsdManagementFlag & ~(_BIT0)) | x))

#define GET_MZ_PEAKING_ON_OFF_TYPE()    ((stOsdUserData.OsdManagementFlag & (_BIT1)) >> 1)
#define SET_MZ_PEAKING_ON_OFF_TYPE(x)   (stOsdUserData.OsdManagementFlag = ((stOsdUserData.OsdManagementFlag & ~(_BIT1)) | (x << 1)))

#define _SAC_DCC_TEXT                   0
#define _SAC_DCC_MOVIE                  1
#define _SAC_DCC_GRAPHIC                2
#define _SAC_DCC_GAME                   3
#define _SAC_DCC_NORMAL                 4
#define _SAC_DCC_USER                   5

#define _MZ_ICM_YELLOW_HUE_MAX          16
#define _MZ_ICM_YELLOW_HUE_MIN          0
#define _MZ_ICM_YELLOW_SAT_MAX          16
#define _MZ_ICM_YELLOW_SAT_MIN          0
#define _MZ_ICM_CYAN_HUE_MAX            16
#define _MZ_ICM_CYAN_HUE_MIN            0
#define _MZ_ICM_CYAN_SAT_MAX            16
#define _MZ_ICM_CYAN_SAT_MIN            0
#define _MZ_ICM_MAGENTA_HUE_MAX         16
#define _MZ_ICM_MAGENTA_HUE_MIN         0
#define _MZ_ICM_MAGENTA_SAT_MAX         16
#define _MZ_ICM_MAGENTA_SAT_MIN         0

#define _MZ_DCC_TEXT                    0
#define _MZ_DCC_MOVIE                   1
#define _MZ_DCC_GRAPHIC                 2
#define _MZ_DCC_GAME                    3
#define _MZ_DCC_NORMAL                  4


//Six Axes Color
//--------------------------------------------------
// Vivid Color
//--------------------------------------------------
#define _V_RED                          0
#define _V_GREEN                        1
#define _V_BLUE                         2
#define _V_YELLOW                       3
#define _V_CYAN                         4
#define _V_MAGENTA                      5

#endif

#define GET_COLOR_TEMP_TYPE()           (stSystemData.ColorTemp & (_BIT3 | _BIT2 | _BIT1 | _BIT0))
#define SET_COLOR_TEMP_TYPE(x)          (stSystemData.ColorTemp = ((stSystemData.ColorTemp & ~(_BIT3 | _BIT2 | _BIT1 | _BIT0)) | x))

#define GET_DO_SHOW_NOTE()           ((stSystemData.ColorTemp&_BIT4)>>4)
#define SET_DO_SHOW_NOTE(x)          (stSystemData.ColorTemp = ((stSystemData.ColorTemp&~_BIT4)| (x<<4)))
#define STATE_MUTEON                    0x01
#define STATE_MUTEOFF                   0x00
#define GET_MUTE_STATE()                (stOsdUserData.OsdSettingFlag & STATE_MUTEON)
#define SET_MUTE_STATE(state)           stOsdUserData.OsdSettingFlag = (stOsdUserData.OsdSettingFlag & (~STATE_MUTEON)) | state

#define _OSD_DOUBLE_STATE               0x80 // OSD double height and double width
#define _OSD_NORMAL_STATE               0x00 // OSD normal height and normal width
#define _GET_OSD_DOUBLE_STATE()         (stOsdUserData.OsdSettingFlag & _BIT7)  
#define _SET_OSD_DOUBLE_STATE(state)    stOsdUserData.OsdSettingFlag = (stOsdUserData.OsdSettingFlag & (~_BIT7)) | state

#define BURNIN_ON                       _BIT0
#define BURNIN_OFF                      0x00
#define GET_BURNIN_STATE()              (bit)(stSystemData.FAC_STATE & BURNIN_ON)
#define SET_BURNIN_STATE(state)         stSystemData.FAC_STATE = (stSystemData.FAC_STATE & (~BURNIN_ON)) | state

#define GET_NOSIGNAL_INFO()              (bit)(stSystemData.FAC_STATE & _BIT3)
#define SET_NOSIGNAL_INFO(state)         stSystemData.FAC_STATE = (stSystemData.FAC_STATE & (~_BIT3)) | state<<3

#define GET_FAC_STATE()              ((bit)(stSystemData.FAC_STATE & _BIT1))
#define SET_FAC_STATE(state)         stSystemData.FAC_STATE = (stSystemData.FAC_STATE & (~_BIT1)) | state<<1

#define GET_MENU_STATE()              ((bit)(stSystemData.FAC_STATE & _BIT2))
#define SET_MENU_STATE()         stSystemData.FAC_STATE = (stSystemData.FAC_STATE & (~_BIT2)) |_BIT2
#define CLR_MENU_STATE()         stSystemData.FAC_STATE = (stSystemData.FAC_STATE & (~_BIT2)) 

#define GET_LOGO_EN()              ((bit)(stSystemData.FAC_STATE & _BIT4))
#define SET_LOGO_EN()         stSystemData.FAC_STATE = (stSystemData.FAC_STATE & (~_BIT4)) |_BIT4
#define CLR_LOGO_EN()         stSystemData.FAC_STATE = (stSystemData.FAC_STATE & (~_BIT4)) 

#define GET_EMC_EN()              ((bit)(stSystemData.FAC_STATE & _BIT5))
#define SET_EMC_EN()         stSystemData.FAC_STATE = (stSystemData.FAC_STATE & (~_BIT5)) |_BIT5
#define CLR_EMC_EN()         stSystemData.FAC_STATE = (stSystemData.FAC_STATE & (~_BIT5)) 

#define SET_SHARPNESS(value)            stSystemData.Sharpness = (stSystemData.Sharpness & 0xf0) | (value)
#define GET_SHARPNESS()                 (stSystemData.Sharpness & 0x0f) 

#define _SET_VIDEO_SHARP(value)         stVDCColor.VideoSharpness = value
#define _GET_VIDEO_SHARP()              stVDCColor.VideoSharpness

#define SET_GAMMA(value)                stSystemData.Sharpness = (stSystemData.Sharpness & 0x0f) | (value << 4)
#define GET_GAMMA()                     ((stSystemData.Sharpness & 0xf0) >> 4) 

#define _SET_INPUT_SOURCE(value)        (stSystemData.InputSource = value)
#define _GET_INPUT_SOURCE()             stSystemData.InputSource

// Image color
#define _SET_IMAGE_COLOR_MODE(value)    stOsdUserData.OsdManagementFlag = (stOsdUserData.OsdManagementFlag & 0xf8) | value
#define _GET_IMAGE_COLOR_MODE()         (stOsdUserData.OsdManagementFlag & 0x07)

// OSD Translucent
#define _SET_OSD_TRANSLUCENT(value)     stOsdUserData.OsdManagementFlag = (stOsdUserData.OsdManagementFlag & 0x1f) | (value << 5)
#define _GET_OSD_TRANSLUCENT()          (stOsdUserData.OsdManagementFlag >> 5)

// OSD Size
#define _SET_OSD_SIZE(value)            stOsdUserData.OsdManagementFlag = (stOsdUserData.OsdManagementFlag & 0xef) | (value << 4)
#define _GET_OSD_SIZE()                 ((stOsdUserData.OsdManagementFlag >> 4) & 0x01)

#define   DISPLAY_MODE_16_10      0
#define   DISPLAY_MODE_43         1
#define _SET_DISPLAY_MODE(x)            stOsdUserData.OsdSettingFlag = (stOsdUserData.OsdSettingFlag & 0xdf) | (x<<5)
#define _GET_DISPLAY_MODE()            ( (stOsdUserData.OsdSettingFlag >>5)&0X01)


#define _SET_FAC_OSD_LANGUAGE(x)            stOsdUserData.FacLanguage = (stOsdUserData.FacLanguage & 0xF0) | (x)
#define _GET_FAC_OSD_LANGUAGE()            ( stOsdUserData.FacLanguage &0x0F)

#define _SET_FAC_POWER_SET(x)            stOsdUserData.FacLanguage = (stOsdUserData.FacLanguage & 0x8F) | (x<<4)
#define _GET_FAC_POWER_SET()            ( (stOsdUserData.FacLanguage >>4)&0x07)


#define _SET_CHANNEL_FOR_AUDIO(x)            stOsdUserData.FacLanguage = (stOsdUserData.FacLanguage & 0x7F) | (x<<7)
#define _GET_CHANNEL_FOR_AUDIO()            ( (stOsdUserData.FacLanguage >>7)&0x01)

//--------------------------------------------------
// Struct Type
//--------------------------------------------------
typedef struct
{
    BYTE PolarityFlag;              //
    WORD IHWidth;                   // Input Horizontal Width
    WORD IVHeight;                  // Input Vertical Height
    WORD IHFreq;                    // Input Horizontal Frequency
    WORD IVFreq;                    // Input Vertical Frequency
    BYTE IHFreqTolerance;           // Input Horizontal Frequency Tolerance
    BYTE IVFreqTolerance;           // Input Vertical Frequency Tolerance
    WORD IHTotal;                   // Input Horizontal Total Length
    WORD IVTotal;                   // Input Vertical Total Length
    WORD IHStartPos;                // Input Horizontal Start Position
    WORD IVStartPos;                // Input Vertical Start Position

} ModeTableType;

typedef struct
{
    WORD DHTotal;                   // Display Horizontal Total Length
    WORD DHWidth;                   // Display Horizontal Width
    WORD DVHeight;                  // Display Vertical Height
    WORD DVStartPos;                // Display Vertical Start Position

} DisplayTableType;

typedef struct
{
    BYTE ModeCurr;                  // Input Mode
    BYTE Polarity;                  // BIT0: H Polarity, Bit1: V Polarity
    WORD IHFreq;                    // Input Horizontal Frequency
    WORD IVFreq;                    // Input Vertical Frequency
    WORD IHTotal;                   // Input Horizontal Total Length
    WORD IVTotal;                   // Input Vertical Total Length
    WORD IHWidth;                   // Input Horizontal Width
    WORD IVHeight;                  // Input Vertical Height
    WORD IHStartPos;                // Input Horizontal Start Position
    WORD IVStartPos;                // Input Vertical Start Position
    WORD IHCount;                   // Input Horizontal Count Numbers
    WORD IHSyncPulseCount;          // Input Horizontal Sync Pulse Count Numbers

} ModeInformationType;

typedef struct
{
    WORD PanelStyle:		2;		// Panel Style
    WORD PanelDepth:		1;		// 8 bit: 0; 6 bit: 1
    WORD EO_SWAP:		1;		// 1: Swap; 0: No swap
    WORD RB_SWAP:		1;		// 1: Swap; 0: No swap
    WORD ML_SWAP:		1;		// 1: Swap; 0: No swap
    WORD Double_Port:	1;		// 1: double; 0: single
    WORD RSDS_GC_SWAP: 1;		// 1: Swap; 0: No swap
    WORD RSDS_HL_SWAP:	1;		// 1: Swap; 0: No swap
    WORD RSDS_PN_SWAP:	1;		// 1: Swap; 0: No swap
    WORD DHS_MASK:		1;		// 1:MASK; 0: NO MASK
    WORD DVS_INVERT:	1;		// 1: INVERT; 0: NO INVERT
    WORD DHS_INVERT:	1;		// 1: INVERT; 0: NO INVERT
    WORD DEN_INVERT:	1;		// 1: INVERT; 0: NO INVERT
    
    WORD a;                
     WORD b;                   

    WORD DHStartPos;                // Display Horizontal Start Position
    WORD DHWidth;                   // Display Horizontal Width
    WORD c;                    

    WORD DHTotal;                   // Display Horizontal Total Clock Number in One Display Line
    //WORD DHTotalMax;                // Maxinum Display Horizontal Total Clock Number in One Display Line
    //WORD DHTotalMin;                // Mininum Display Horizontal Total Clock Number in One Display Line

    WORD DVStartPos;                // Display Vertical Start Position
    WORD DVHeight;                  // Display Vertical Height
    WORD d;                    

    WORD DVTotal;                   // Display Vertical Total Line Number in One Frame
    //WORD DVTotalMax;                // Maxinum Display Vertical Total Line Number in One Frame
    //WORD DVTotalMin;                // Mininum Display Vertical Total Line Number in One Frame

    BYTE DHSyncWidth;               // Display H Sync Width
    BYTE DVSyncHeight;              // Display V Sync Height

    WORD PixelClock;                // Typical Pixel Clock in MHz
    //WORD PixelClockMax;             // Maxinum Pixel Clock in MHz
    //WORD PixelClockMin;             // Mininum Pixel Clock in MHz

	WORD H_FREQ_Max;						//_H_FREQ_MAX
	WORD H_FREQ_Min;						//H_FREQ_Min
	WORD V_FREQ_Max;						//V_FREQ_Max
	WORD V_FREQ_Min;						//V_FREQ_Min
	BYTE DCLK_DELAY;						//DCLK DELAY

	WORD PAL_Htotal;						//PAL HTOTAL
	WORD NTSC_Htotal;						//NTSC HTOTAL

} PanelType;

typedef struct
{
    BYTE FirstAuto;                 // First Auto
    WORD HPosition;                 // Horizontal Position
    WORD VPosition;                 // Vertical Position
    WORD Clock;                     // Clock Adjust
    BYTE Phase;                     // Phase Adjust

} StructModeUserDataType;

typedef struct
{
    BYTE ModeNum;                   // Mode Number
    WORD IHFreq;                    // Input Horizontal Frequency
    WORD IVFreq;                    // Input Vertical Frequency

} StructModeUserFIFODataType;

typedef struct
{
    WORD CenterHPos;                // Horizontal Position
    WORD CenterVPos;                // Vertical Position
    WORD CenterClock;               // Clock Adjust

} StructModeUserCenterDataType;

typedef struct
{
    BYTE MonitorFlag;               // Bit 7: Monitor Power Status
                                    // Bit 6: Blue background 
                                    //        0: Off
                                    //        1: On
                                    // Bit 5: Reserved
                                    // Bit 4: Reserved
                                    // Bit 3: Reserved

                                    // Bit 2~Bit 0: Auto power down, if use auto power down,else not uset thisbit
                                    //        0: Auto ower down off
                                    //        1: 15 Minute
                                    //        2: 30 Minute
                                    //        3: 45 Minute
                                    //        4: 60 Minute

    BYTE InputSource;
    BYTE BackLight;
    BYTE ColorTemp;
    BYTE Sharpness;
    BYTE UserFIFOMode;
    BYTE ODTable;
#if(_FACTORY_MENU_EN)	
    BYTE FAC_STATE;
						//bit0-1:Power  bit2:BurnIn   bit4-7:language
#endif
	
} StructSystemDataType;



typedef struct
{
    BYTE OsdSettingFlag;            // Bit 7: OSD Double flag
                                    //     0: Normal
                                    //     1: Double
                                    // Bit 6: Reserved
                                    // Bit 5: Reserved
                                    // Bit 4: Reserved
                                    // Bit 3~Bit 2: Input channel state(Only for tv,if not tv,this bit Reserved)
                                    //        00: Input one channel   -
                                    //        01: Input two channel   --
                                    //        02: Input three channel ---  
                                    // Bit 1: BURN IN 1 : ON  0 : OFF
                                    // Bit 0: MUTE    1 : ON  0 : OFF

    BYTE OsdManagementFlag;         // Bit 7~Bit 5: OSD Translucent(if _ALPHA_BLENDING_ADJ on use bit7~bit5 else Reserved)
                                    //     0:  Translucent off   1~7: level 1~7
                                    // Bit 4: OSD Size(if _OSD_DISPLAY_SIZE_ADJ on use bit 4 else Reserved)
                                    //     0: Normal   1: OSD double
                                    // Bit 3: Reserved
                                    // if _IMAGE_COLOR_MODE == on use 0~2  else Reserved
                                    // Bit 2~0: Color Mode
                                    // 0: Mode0    1: Mode1   2: Mode2
                                    // 3: Mode3    4: Mode4   5: Mode5
    BYTE OsdHPos;
    BYTE OsdVPos;
    BYTE Language;
    BYTE FacLanguage;
    BYTE OsdTimeout;
    BYTE Volume;

#if (_SOUND_PROCESSOR == _ENABLE)
    BYTE Balance;
    BYTE Bass;
    BYTE Treble;
    BYTE SRS;
    BYTE BBE;
#endif

#if (_SCALER_TYPE == _RTD2553V || _SCALER_TYPE == _RTD2546N || _SCALER_TYPE == _RTD2525L)
#if (_VGA_COLOR_SUPPORT)
    WORD MZHPos;
    WORD MZVPos;
    WORD MZHWidth;
    WORD MZVHeight;
    BYTE MZDCC;
    BYTE MZICMRedHue;
    BYTE MZICMRedSat;
    BYTE MZICMGreenHue;
    BYTE MZICMGreenSat;
    BYTE MZICMBlueHue;
    BYTE MZICMBlueSat;
    BYTE MZBright;
    BYTE MZContrast;
    BYTE MZPeaking;
//Six Axes Color
    BYTE MZICMYellowHue;
    BYTE MZICMYellowSat;
    BYTE MZICMCyanHue;
    BYTE MZICMCyanSat;
    BYTE MZICMMagentaHue;
    BYTE MZICMMagentaSat;
#endif
#endif

} StructOsdUserDataType;

typedef struct
{
    BYTE AdcGain[3];
    BYTE AdcOffset[3];

} StructAdcDataType;

typedef struct
{
    BYTE Brightness;
    BYTE Contrast;
    BYTE Hue;
    BYTE Saturation;

} StructColorProc0DataType;

typedef struct
{
    BYTE ColorTemp[3];

} StructColorProc1DataType;

typedef struct
{
    BYTE ColorTemp9300Red;
    BYTE ColorTemp9300Green;
    BYTE ColorTemp9300Blue;
    BYTE ColorTemp6500Red;
    BYTE ColorTemp6500Green;
    BYTE ColorTemp6500Blue;
    BYTE ColorTempUserRed;
    BYTE ColorTempUserGreen;
    BYTE ColorTempUserBlue;

} StructColorTempDataType;


typedef struct
{
#if(_VIDEO_TV_SUPPORT)
    BYTE CurrentChannel;
#endif
    BYTE VideoSharpness;
}StructVDCColor;


//--------------------------------------------------
// Timer Struct
//--------------------------------------------------
struct CTimerEventTable
{
    DWORD Time;
    void (*Event)(void);
};

//--------------------------------------------------
// Extern Global Struct Variables
//--------------------------------------------------
extern StructModeUserDataType       xdata   stModeUserData;
extern StructModeUserCenterDataType xdata   stModeUserCenterData;
extern StructSystemDataType         idata   stSystemData;
extern StructOsdUserDataType        idata   stOsdUserData;
extern StructAdcDataType            idata   stAdcData;
extern StructColorProc0DataType     xdata   stConBriData;
extern StructColorProc1DataType     xdata   stColorTempData;

extern ModeInformationType          xdata   stModeInfo;
extern DisplayTableType             xdata   stDisplayInfo;

#if(_VIDEO_SUPPORT)
extern StructVDCColor               idata   stVDCColor;
#endif


