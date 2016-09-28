#if(_VIDEO_SUPPORT == _ON)

//----------------------------------------------------------------------------------------------------

//--------------------------------------------------
// Definitions of
//--------------------------------------------------
#define _50HZ                       50
#define _60HZ                       60
#define _AV                         0
#define _SV                         1
#define _VIDEO_NOT_EXIST            _MODE_NOSIGNAL
#define _VIDEO_EXIST                _MODE_EXIST
#define _VideoLatch                 0x01
#define _VideoIclkDelay             0x00

#define _VIDEO_COLOR_NTSC           0x01
#define _VIDEO_COLOR_PAL            0x02

//----------------------------------------------------------------------------------------------------

#ifdef __VIDEO__
//--------------------------------------------------
// Video Tables
//--------------------------------------------------
#if(_VIDEO_CHIP == _VDC_RTD2612 || _VIDEO_CHIP == _VDC_RTD2613)
BYTE code tVideoPALM[] =
{
    0x01, 0x05, 
    0x18, 0x21,
    0x19, 0xe6,
    0x1a, 0xef, 
    0x1b, 0xa4, 
    0x2e, 0x82, 
    0x30, 0x22, 
    0x31, 0x4f, 
    0x82, 0x4a, 

    0xff,  //end
};

BYTE code tVideoNTSC[] =
{
    0x01, 0x09, 
    0x04, 0xdd, 
    0x18, 0x21, 
    0x19, 0xf0, 
    0x1a, 0x7c, 
    0x1b, 0x1f, 
    0x2e, 0x82, 
    0x30, 0x12, 
    0x31, 0x61, 
    0x82, 0x42, 

    0xff,  //end
};

BYTE code tVideoPALN[] =
{
    0x01, 0x04, 
    0x18, 0x21, 
    0x19, 0xf6, 
    0x1a, 0x94, 
    0x1b, 0x46, 
    0x2e, 0x8a, 
    0x30, 0x2a, 
    0x31, 0xc1, 
    0x82, 0x4a, 

    0xff,  //end
};

BYTE code tVideoPALBGHI[] =
{
    0x01, 0x04, 
    0x18, 0x2a, 
    0x19, 0x09, 
    0x1a, 0x8a, 
    0x1b, 0xcb, 
    0x2e, 0x84, 
    0x30, 0x2a, 
    0x31, 0xb9, 
    0x82, 0x6a,    //

    0xff,  //end
};

BYTE code tVideoSECAM[] =
{
    0x01, 0x00, 
    0x18, 0x28, 
    0x19, 0xa3, 
    0x1a, 0x3b, 
    0x1b, 0xb2, 
    0x2e, 0x88, 
    0x30, 0x84, 
    0x31, 0x61, 
    0x82, 0x42, 

    0xff,  //end
};

#endif

#if(_VIDEO_CHIP != _VDC_TB1334)
BYTE code tVIDEO_TABLE_SET_SCALER[] =
{                   
#if (_SCALER_TYPE == _RTD2547D)

    5,  _AUTOINC,       _VGIP_CTRL_10,              0x09,_INPUT_SYNC_POLARITY,//0x11,
    4,  _NON_AUTOINC,   _VGIP_DELAY_CTRL_12,        0x00,//new add
    4,  _NON_AUTOINC,   _VGIP_ODD_CTRL_13,          0x4f,
    4,  _NON_AUTOINC,   _IPH_ACT_WID_H_16,          (0x00 | _VIDEO8_MSB_LSB_SWAP),
    4,  _NON_AUTOINC,   _SCALE_CTRL_32,             0x80,
    4,  _NON_AUTOINC,   _VSYNC_COUNTER_LEVEL_MSB_4C,0x03,
    4,  _NON_AUTOINC,   _SYNC_CTRL_49,              0x05,

    // 9CH
    4,  _NON_AUTOINC,   _YUV2RGB_CTRL_9C,           0x08,
    21, _NON_AUTOINC,   _YUV_RGB_COEF_DATA_9D,      0x04,0x00,0x00,0x00,0x05,0x80,
                                                    0x04,0x00,0xfe,0xa0,0xfd,0x40,
                                                    0x04,0x00,0x07,0x00,0x00,0x00,
/*
	5,  _AUTOINC,       _YUV2RGB_CTRL_9C,           0x08,0x05,
    5,  _AUTOINC,       _YUV2RGB_CTRL_9C,           0x28,0x80,
    5,  _AUTOINC,       _YUV2RGB_CTRL_9C,           0x48,0x01,
    5,  _AUTOINC,       _YUV2RGB_CTRL_9C,           0x68,0x40,
    5,  _AUTOINC,       _YUV2RGB_CTRL_9C,           0x88,0x00,
    5,  _AUTOINC,       _YUV2RGB_CTRL_9C,           0xa8,0xa0,
    5,  _AUTOINC,       _YUV2RGB_CTRL_9C,           0xc8,0x07,
    5,  _AUTOINC,       _YUV2RGB_CTRL_9C,           0xe8,0x00,
*/
	4,  _NON_AUTOINC,   _YUV2RGB_CTRL_9C,           0x07,
#if(_VIDEO_IN == _VIDEO_16_IN)
    4,  _NON_AUTOINC,   _IPV_ACT_STA_H_18,          0xf0,
//cyc:not yet finished    4,  _NON_AUTOINC,   _PS_ACCESS_PORT_8D,         0x00,
//cyc:not yet finished    5,  _NON_AUTOINC,   _PS_DATA_PORT_8E,           0x00,0x00,
#elif(_VIDEO_IN == _VIDEO_8_IN)
    4,  _NON_AUTOINC,   _IPH_ACT_WID_H_16,          (0x0A | _VIDEO8_MSB_LSB_SWAP),
    4,  _NON_AUTOINC,   _IPV_ACT_STA_H_18,          0x00,
#endif  // End of #if(_VIDEO_IN == _VIDEO_16_IN)

	4,  _NON_AUTOINC,   _PAGE_SELECT_A0,          	0x05, 	//for video-compensation
	4,  _NON_AUTOINC,   _P5_SDRF_IN1_SDR_CTRL_B9,  	0x82,

#else
                                              
#if (_SCALER_TYPE == _RTD2525L)

    4,  _NON_AUTOINC,   _VSYNC_COUNTER_LEVEL_MSB_4C,0x03,

#else

  #if (_SOURCE_VIDEO_PORT_TYPE == _VIDEO_2ND_ADC_PORT)  
 
    #if (_SCALER_TYPE == _RTD2553V)
    4,  _NON_AUTOINC,   _VSYNC_COUNTER_LEVEL_MSB_4C,0x03,
    #elif (_SCALER_TYPE == _RTD2533B)
    4,  _NON_AUTOINC,   _VSYNC_COUNTER_LEVEL_MSB_4C,0x03, 
    #endif   // end #if (_SCALER_TYPE == _RTD2553V)

  #else

    #if (_SCALER_TYPE == _RTD2553V)
    4,  _NON_AUTOINC,   _VSYNC_COUNTER_LEVEL_MSB_4C,0x0b,
    #elif (_SCALER_TYPE == _RTD2533B)
    4,  _NON_AUTOINC,   _VSYNC_COUNTER_LEVEL_MSB_4C,0x23, 
    #endif   // end #if (_SCALER_TYPE == _RTD2553V)

  #endif     // end #if (_SOURCE_VIDEO_PORT_TYPE == _VIDEO_2ND_ADC_PORT) 

#endif       // end #if (_SCALER_TYPE == _RTD2525L)

    5,  _AUTOINC,       _VGIP_CTRL_05,               0x09,_INPUT_SYNC_POLARITY, 
 //   4,  _NON_AUTOINC,   _VGIP_ODD_CTRL_08,           0x4f,
    4,  _NON_AUTOINC,   _VGIP_ODD_CTRL_08,           0x4d,
    4,  _NON_AUTOINC,   _IPH_ACT_WID_H_0B,           (0x08 | _VIDEO8_MSB_LSB_SWAP),
    4,  _NON_AUTOINC,   _SCALE_CTRL_19,              0x80,
 //   4,  _NON_AUTOINC,   _SYNC_CTRL_49,               0x05,

    // 89H
    5,  _AUTOINC,       _YUV2RGB_CTRL_89,            0x08,0x06,
    5,  _AUTOINC,       _YUV2RGB_CTRL_89,            0x28,0x62,
    5,  _AUTOINC,       _YUV2RGB_CTRL_89,            0x48,0x00,
    5,  _AUTOINC,       _YUV2RGB_CTRL_89,            0x68,0xbf,
    5,  _AUTOINC,       _YUV2RGB_CTRL_89,            0x88,0x00,
    5,  _AUTOINC,       _YUV2RGB_CTRL_89,            0xa8,0x6f,
    5,  _AUTOINC,       _YUV2RGB_CTRL_89,            0xc8,0x08,
    5,  _AUTOINC,       _YUV2RGB_CTRL_89,            0xe8,0x12,
    
	4,  _NON_AUTOINC,   _YUV2RGB_CTRL_89,            0x07,

#if (_SCALER_TYPE == _RTD2553V || _SCALER_TYPE == _RTD2525L)
#if(_VIDEO_IN == _VIDEO_16_IN)                    
    4,  _NON_AUTOINC,   _IPV_ACT_STA_H_0D,          0xf0,
    4,  _NON_AUTOINC,   _PS_ACCESS_PORT_8D,         0x00,
    5,  _NON_AUTOINC,   _PS_DATA_PORT_8E,           0x00,0x00,
#elif(_VIDEO_IN == _VIDEO_8_IN)
//    4,  _NON_AUTOINC,   _IPH_ACT_WID_H_0B,          0x08, //V304 modify
    4,  _AUTOINC,       _IPV_ACT_STA_H_0D,          0x00,  
#endif  // End of #if(_VIDEO_IN == _VIDEO_16_IN)         
#endif
#endif //#if (_SCALER_TYPE == _RTD2547D)

    _END
};
#endif



//--------------------------------------------------
// Global Variables
//--------------------------------------------------
bit bVideoON               = 0;
bit bDVDON					=0;
BYTE VideoTurnOnLightCount = 0;
BYTE xdata VideoType       = 0;

#if(_VIDEO_TV_SUPPORT)
BYTE ucVideoNoModeTime = 0; 
#endif
//--------------------------------------------------
// Function Prototypes
//--------------------------------------------------
void CAdjustVideoSharp(void);
void CSetVDCSaturation(const BYTE ucSaturation);

#else

//--------------------------------------------------
// Extern Global Variables
//--------------------------------------------------
extern bit bVideoON;
extern bit bDVDON;
extern BYTE VideoTurnOnLightCount;
extern BYTE xdata VideoType;            


#if(_VIDEO_TV_SUPPORT)
extern BYTE ucVideoNoModeTime;
#endif

#if(_VIDEO_SUPPORT && _VIDEO_CHIP == _VDC_TB1334)
extern ModeTableType code tVIDEO_INPUTMODE_PRESET_TABLE[2];
#endif

//--------------------------------------------------
// Extern Function Prototypes
//--------------------------------------------------
extern void gmi_CVDCOff(void);
extern void CReset_VDC(void);
extern void CPowerDownVDC(void);
extern void CDisableVideo(void);
extern void CVideoModeHandler(void);  
extern void CVideoDisplaySet(void);
extern void CSetRTD2610ColorMode(void);
extern void CAccAdjustVividColor(BYTE mode);
extern void CAdjustPeakingFilter1(SBYTE ucPeaking);
extern void CAdjustVideoSharp(void);
extern void CSetVDCSaturation(const BYTE ucSaturation);

#if(_VIDEO_CHIP == _VDC_TB1334)
extern bit CVideoFrameSyncDetect(void);
extern void CLoadTVNoSignalModeData(void);
extern void CSetVideoReady(void);
extern void CLoadVideoModeData(void);
extern void CSetVideoColor(void);
extern void CTVCheckChangeChannel(void);
extern void CSetVideoBackLight(void);
extern void CSetTB1334VideoMode(void);
extern void CVideoInitial(void);
#endif

#endif


//----------------------------------------------------------------------------------------------------

//--------------------------------------------------
// Macro of Input Sync Type
//--------------------------------------------------
#define ADDRESS(x)                  (x)
#define CHECK60HZ()                 (VideoType == _60HZ)
#define RECODE60HZ()                (VideoType = _60HZ)
#define CHECK50HZ()                 (VideoType == _50HZ)
#define RECODE50HZ()                (VideoType = _50HZ)
#define CHECK_NONE_VIDEO()          (VideoType == 0)
#define RECODE_NONE_VIDEO()         (VideoType = 0) 

#endif  // #if(_VIDEO_SUPPORT == _ON)
