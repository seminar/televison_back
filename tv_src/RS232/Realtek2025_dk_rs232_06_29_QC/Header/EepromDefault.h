//----------------------------------------------------------------------------------------------------
// ID Code      : EepromDefault.h No.0001
// Update Note  : 
//
//----------------------------------------------------------------------------------------------------

#ifdef __EEPROM__
//--------------------------------------------------
// System Data Default Value
//--------------------------------------------------
#define _MONITORFLAG                0xc0
//#define _INPUTSOURCE                0x00
#define _BACKLIGHT                  0x32
#define _COLORTEMP                  0x00   
#define _SHARPNESS                  0x02
#define _USERFIFOMODE               0x0f
#define _ODSELECTED                 0x40  // Delta Gain = _ODSELECTED/64
#define _FAC_STATE                       0


code StructSystemDataType tEEPROM_SYSTEM_DATA =
{
    _MONITORFLAG,
    _INPUTSOURCE,
    _BACKLIGHT,
    _COLORTEMP,
    _SHARPNESS,
    _USERFIFOMODE,
    _ODSELECTED,
    _FAC_STATE,
};

//--------------------------------------------------
// OSD User Data Default Value
//--------------------------------------------------
#define _OSD_SETTINGFLAG            0x00
#define _OSD_MANAGEMENTFLAG         0x02
#define _OSD_H_POSITION             0x32
#define _OSD_V_POSITION             0x32
#define _FacLANGUAGE                (_LANGUAGE|(POWERUPSTATE<<4))
#define _OSD_TIMEOUT                0x0a
#define _VOLUME                     0x32

#if (_SOUND_PROCESSOR == _ENABLE)
#define _BALANCE                    0x32
#define _BASS                       0x32
#define _TREBLE                     0x32
#define _SRS                        0x32
#define _BBE                        0x32
#endif

#if (_SCALER_TYPE == _RTD2553V || _SCALER_TYPE == _RTD2546N || _SCALER_TYPE == _RTD2525L)
#define _MZ_H_POSITION              0x00
#define _MZ_V_POSITION              0x00
#define _MZ_H_WIDTH                 0x280
#define _MZ_V_HEIGHT                0x200
#define _MZ_DCC                     0x84    //Six Axes Color
#define _MZ_ICM_RED_HUE             0x08
#define _MZ_ICM_RED_SAT             0x08
#define _MZ_ICM_GREEN_HUE           0x08
#define _MZ_ICM_GREEN_SAT           0x08
#define _MZ_ICM_BLUE_HUE            0x08
#define _MZ_ICM_BLUE_SAT            0x08
#define _MZ_COLOR_BRIGHTNESS        0x96
#define _MZ_COLOR_CONTRAST          0x80
#define _MZ_COLOR_PEAKING           0x00

//Six Axes Color
#define _MZ_ICM_YELLOW_HUE          0x08
#define _MZ_ICM_YELLOW_SAT          0x08
#define _MZ_ICM_CYAN_HUE            0x08
#define _MZ_ICM_CYAN_SAT            0x08
#define _MZ_ICM_MAGENTA_HUE         0x08
#define _MZ_ICM_MAGENTA_SAT         0x08
#endif

code StructOsdUserDataType tEEPROM_OSDUSER_DATA =
{
    _OSD_SETTINGFLAG,
    _OSD_MANAGEMENTFLAG,
    _OSD_H_POSITION,
    _OSD_V_POSITION,
    _LANGUAGE,
    _FacLANGUAGE,
    _OSD_TIMEOUT,
    _VOLUME,

#if (_SOUND_PROCESSOR == _ENABLE)
    _BALANCE,
    _BASS,
    _TREBLE,
    _SRS,
    _BBE,
#endif


#if (_SCALER_TYPE == _RTD2553V || _SCALER_TYPE == _RTD2546N || _SCALER_TYPE == _RTD2525L)
#if (_VGA_COLOR_SUPPORT)
    _MZ_H_POSITION,
    _MZ_V_POSITION,
    _MZ_H_WIDTH,
    _MZ_V_HEIGHT,
    _MZ_DCC,
    _MZ_ICM_RED_HUE,
    _MZ_ICM_RED_SAT,
    _MZ_ICM_GREEN_HUE,
    _MZ_ICM_GREEN_SAT,
    _MZ_ICM_BLUE_HUE,
    _MZ_ICM_BLUE_SAT,
    _MZ_COLOR_BRIGHTNESS,
    _MZ_COLOR_CONTRAST,
    _MZ_COLOR_PEAKING,

//Six Axes Color
    _MZ_ICM_YELLOW_HUE,
    _MZ_ICM_YELLOW_SAT,         
    _MZ_ICM_CYAN_HUE,        
    _MZ_ICM_CYAN_SAT,           
    _MZ_ICM_MAGENTA_HUE,        
    _MZ_ICM_MAGENTA_SAT, 

#endif       
#endif
};

//--------------------------------------------------
// ADC Gain/Offset Default Value
//--------------------------------------------------
#define VGA_ADC_GAIN_RED               0x80
#define VGA_ADC_GAIN_GREEN             0x80
#define VGA_ADC_GAIN_BLUE              0x80

#define VGA_ADC_OFFSET_RED             0x80
#define VGA_ADC_OFFSET_GREEN           0x80
#define VGA_ADC_OFFSET_BLUE            0x80


code StructAdcDataType tEEPROM_ADC_DATA_VGA =
{
    VGA_ADC_GAIN_RED,
    VGA_ADC_GAIN_GREEN,
    VGA_ADC_GAIN_BLUE,
    VGA_ADC_OFFSET_RED,
    VGA_ADC_OFFSET_GREEN,
    VGA_ADC_OFFSET_BLUE,
};
#define YPbPr_ADC_GAIN_RED               0x80
#define YPbPr_ADC_GAIN_GREEN             0x80
#define YPbPr_ADC_GAIN_BLUE              0x80

#define YPbPr_ADC_OFFSET_RED             0x80
#define YPbPr_ADC_OFFSET_GREEN           0x80
#define YPbPr_ADC_OFFSET_BLUE            0x80


code StructAdcDataType tEEPROM_ADC_DATA_YPbPr =
{
    YPbPr_ADC_GAIN_RED,
    YPbPr_ADC_GAIN_GREEN,
    YPbPr_ADC_GAIN_BLUE,
    YPbPr_ADC_OFFSET_RED,
    YPbPr_ADC_OFFSET_GREEN,
    YPbPr_ADC_OFFSET_BLUE,
};
#define VIDEO_ADC_GAIN_RED               0x9a
#define VIDEO_ADC_GAIN_GREEN             0xa0
#define VIDEO_ADC_GAIN_BLUE              0xab

#define VIDEO_ADC_OFFSET_RED             0x9a
#define VIDEO_ADC_OFFSET_GREEN           0x93
#define VIDEO_ADC_OFFSET_BLUE            0x97

code StructAdcDataType tEEPROM_ADC_DATA_VIDEO =
{
    VIDEO_ADC_GAIN_RED,
    VIDEO_ADC_GAIN_GREEN,
    VIDEO_ADC_GAIN_BLUE,
    VIDEO_ADC_OFFSET_RED,
    VIDEO_ADC_OFFSET_GREEN,
    VIDEO_ADC_OFFSET_BLUE,
};

//--------------------------------------------------
// Brightness/Contrast Default Value
//--------------------------------------------------
#define _BRIGHTNESS_VGA             0x32
#define _CONTRAST_VGA                0x32
#define _HUE_VGA                          0x32
#define _SATURATION_VGA            0x32

#define _BRIGHTNESS_AV             0x32
#define _CONTRAST_AV                0x32
#define _HUE_AV                          0x32
#define _SATURATION_AV           0x32

#define _BRIGHTNESS_SV            0x32
#define _CONTRAST_SV               0x32
#define _HUE_SV                         0x32
#define _SATURATION_SV          0x32

#define _BRIGHTNESS_TV             0x32
#define _CONTRAST_TV                0x32
#define _HUE_TV                         0x32
#define _SATURATION_TV            0x32

#define _BRIGHTNESS_DVD           0x32
#define _CONTRAST_DVD               0x32
#define _HUE_DVD                          0x32
#define _SATURATION_DVD            0x32

code StructColorProc0DataType tEEPROM_COLOR_PROC0_DATA[] =
{
    {
        _BRIGHTNESS_VGA,
        _CONTRAST_VGA,
        _HUE_VGA,
        _SATURATION_VGA,
    },

    {
        _BRIGHTNESS_AV,
        _CONTRAST_AV,
        _HUE_AV,
        _SATURATION_SV,
    },
    
    {
        _BRIGHTNESS_SV,
        _CONTRAST_SV,
        _HUE_SV,
        _SATURATION_SV,
    },

    {
        _BRIGHTNESS_TV,
        _CONTRAST_TV,
        _HUE_TV,
        _SATURATION_TV,
    },
    
    {
        _BRIGHTNESS_DVD,
        _CONTRAST_DVD,
        _HUE_DVD,
        _SATURATION_DVD,
    },
};

//--------------------------------------------------
// Color Temperature Default Value
//--------------------------------------------------
#define _CT9300_RED_VGA            0x80// 0x67
#define _CT9300_GREEN_VGA          0x80// 0x61
#define _CT9300_BLUE_VGA           0x80// 0x56   
#define _CT6500_RED_VGA             0x80//0x61
#define _CT6500_GREEN_VGA           0x80//0x60
#define _CT6500_BLUE_VGA            0x80//0x63
#define _CTUSER_RED_VGA             0x80
#define _CTUSER_GREEN_VGA           0x80
#define _CTUSER_BLUE_VGA            0x80

#define _CT9300_RED_DVI             0x67
#define _CT9300_GREEN_DVI           0x61
#define _CT9300_BLUE_DVI            0x56
#define _CT6500_RED_DVI             0x61
#define _CT6500_GREEN_DVI           0x60
#define _CT6500_BLUE_DVI            0x63
#define _CTUSER_RED_DVI             0x80
#define _CTUSER_GREEN_DVI           0x80
#define _CTUSER_BLUE_DVI            0x80

#define _CT9300_RED_VIDEO           0x80
#define _CT9300_GREEN_VIDEO         0x80
#define _CT9300_BLUE_VIDEO          0x80
#define _CT6500_RED_VIDEO           0x80
#define _CT6500_GREEN_VIDEO         0x80
#define _CT6500_BLUE_VIDEO          0x80
#define _CTUSER_RED_VIDEO           0x80
#define _CTUSER_GREEN_VIDEO         0x80
#define _CTUSER_BLUE_VIDEO          0x80

code StructColorTempDataType tEEPROM_COLORTEMP_DATA[] =
{
    {
        _CT9300_RED_VGA,
        _CT9300_GREEN_VGA,
        _CT9300_BLUE_VGA,
        _CT6500_RED_VGA,
        _CT6500_GREEN_VGA,
        _CT6500_BLUE_VGA,
        _CTUSER_RED_VGA,
        _CTUSER_GREEN_VGA,
        _CTUSER_BLUE_VGA,
    },

    {
        _CT9300_RED_DVI,
        _CT9300_GREEN_DVI,
        _CT9300_BLUE_DVI,
        _CT6500_RED_DVI,
        _CT6500_GREEN_DVI,
        _CT6500_BLUE_DVI,
        _CTUSER_RED_DVI,
        _CTUSER_GREEN_DVI,
        _CTUSER_BLUE_DVI,
    },

    {
        _CT9300_RED_VIDEO,
        _CT9300_GREEN_VIDEO,
        _CT9300_BLUE_VIDEO,
        _CT6500_RED_VIDEO,
        _CT6500_GREEN_VIDEO,
        _CT6500_BLUE_VIDEO,
        _CTUSER_RED_VIDEO,
        _CTUSER_GREEN_VIDEO,
        _CTUSER_BLUE_VIDEO,
    },
};

code BYTE tEEPROM_USER_FIFO_MODE_DEFAULT[] =
{
    0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
    0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
};


#if(_VIDEO_SUPPORT)

#if(_VIDEO_TV_SUPPORT)
#define _CURRENT_CHANNEL    1
#endif
#define _SHARP_DEF          0x18

code StructVDCColor tVDCColorDefault = 
{
#if(_VIDEO_TV_SUPPORT)
     _CURRENT_CHANNEL,
#endif
     _SHARP_DEF,
};

#endif //#if(_VIDEO_SUPPORT)



#else

extern code StructSystemDataType  tEEPROM_SYSTEM_DATA;
extern code StructOsdUserDataType tEEPROM_OSDUSER_DATA;
extern code StructAdcDataType     tEEPROM_ADC_DATA_VGA;
extern code StructAdcDataType     tEEPROM_ADC_DATA_YPbPr;
extern code StructAdcDataType     tEEPROM_ADC_DATA_VIDEO;
extern code StructColorProc0DataType tEEPROM_COLOR_PROC0_DATA[];
extern code StructColorTempDataType  tEEPROM_COLORTEMP_DATA[];
extern code BYTE tEEPROM_USER_FIFO_MODE_DEFAULT[];

#if(_VIDEO_SUPPORT)
extern code StructVDCColor tVDCColorDefault;
#endif //#if(_VIDEO_SUPPORT)

#endif

