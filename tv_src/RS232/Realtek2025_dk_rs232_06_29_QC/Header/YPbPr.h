//----------------------------------------------------------------------------------------------------
// ID Code      : YPbPr.h No.0001
// Update Note  : 
//
//----------------------------------------------------------------------------------------------------
                        
#if(_YPBPR_SUPPORT == _ON)

//--------------------------------------------------
// Definitions of
//--------------------------------------------------
#define _MAX_YPBPR_MODE             10

#define _YPBPR_MODE_576I            0
#define _YPBPR_MODE_480I            1
#define _YPBPR_MODE_576P            2
#define _YPBPR_MODE_480P            3
#define _YPBPR_MODE_720P50          4
#define _YPBPR_MODE_720P60          5
#define _YPBPR_MODE_1080I50         6
#define _YPBPR_MODE_1080I60         7
#define _YPBPR_MODE_1080P50         8
#define _YPBPR_MODE_1080P60         9

//----------------------------------------------------------------------------------------------------

#ifdef __YPBPR__

//--------------------------------------------------
// YPbPr Tables
//--------------------------------------------------
ModeTableType code tYPBPR_MODE_TABLE[_MAX_YPBPR_MODE] =
{
    //--------------------------------------------------
    // YPbPr Modes
    //--------------------------------------------------
    {   // Mode 0 : 720 x 576i x 50 Hz
        0 | _SYNC_HN_VN | _SYNC_HP_VN | _SYNC_HN_VP | _SYNC_HP_VP,          // Polarity Flags,
        734, 272,                                                           // InputWidth, InputHeight,
        156, 500,                                                           // HFreq in kHz, VFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        964, 312,                                                           // HTotal, VTotal,
        143, 31,                                                            // HStartPos, VStartPos,
    },

    {   // Mode 1 : 720 x 480i x 60 Hz
        0 | _SYNC_HN_VN | _SYNC_HP_VN | _SYNC_HN_VP | _SYNC_HP_VP,          // Polarity Flags,
        704, 224,                                                           // InputWidth, InputHeight,
        157, 600,                                                           // HFreq in kHz, VFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        858, 262,                                                           // HTotal, VTotal,
        129, 27,                                                            // HStartPos, VStartPos,
    },

    {   // Mode 2 : 720 x 576p x 50 Hz
        0 | _SYNC_HN_VN | _SYNC_HP_VN | _SYNC_HN_VP | _SYNC_HP_VP,          // Polarity Flags,
        704, 560,                                                           // InputWidth, InputHeight,
        312, 500,                                                           // HFreq in kHz, VFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        864, 624,                                                           // HTotal, VTotal,
        141, 48,                                                            // HStartPos, VStartPos,
    },

    {   // Mode 3 : 720 x 480p x 60 Hz
        0 | _SYNC_HN_VN | _SYNC_HP_VN | _SYNC_HN_VP | _SYNC_HP_VP,          // Polarity Flags,
        704, 464,                                                           // InputWidth, InputHeight,
        315, 600,                                                           // HFreq in kHz, VFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        858, 526,                                                           // HTotal, VTotal,
        131, 45,                                                            // HStartPos, VStartPos,
    },

    {   // Mode 4 : 1280 x 720p x 50 Hz
        0 | _SYNC_HN_VN | _SYNC_HP_VN | _SYNC_HN_VP | _SYNC_HP_VP,          // Polarity Flags,
        1248, 704,                                                          // InputWidth, InputHeight,
        376, 502,                                                           // HFreq in kHz, VFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        1980, 750,                                                          // HTotal, VTotal,
        300, 25,                                                            // HStartPos, VStartPos,
    },

    {   // Mode 5 : 1280 x 720p x 60 Hz
        0 | _SYNC_HN_VN | _SYNC_HP_VN | _SYNC_HN_VP | _SYNC_HP_VP,          // Polarity Flags,
        1248, 704,                                                          // InputWidth, InputHeight,
        450, 600,                                                           // HFreq in kHz, VFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        1650, 750,                                                          // HTotal, VTotal,
        311, 33,                                                            // HStartPos, VStartPos,
    },

    {   // Mode 6 : 1920 x 1080i x 50 Hz
        0 | _SYNC_HN_VN | _SYNC_HP_VN | _SYNC_HN_VP | _SYNC_HP_VP,          // Polarity Flags,
        1920, 524,                                                          // InputWidth, InputHeight,
        281, 500,                                                           // HFreq in kHz, VFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        2640, 562,                                                          // HTotal, VTotal,
        237, 27,                                                            // HStartPos, VStartPos,
    },

    {   // Mode 7 : 1920 x 1080i x 60 Hz
        0 | _SYNC_HN_VN | _SYNC_HP_VN | _SYNC_HN_VP | _SYNC_HP_VP,          // Polarity Flags,
        1920,524,                                                           // InputWidth, InputHeight,
        337, 600,                                                           // HFreq in kHz, VFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        2200,562,                                                           // HTotal, VTotal,
        237, 33,                                                            // HStartPos, VStartPos,
    },

    {   //# Mode 8 : 1920 x 1080p x 50 Hz
        0 | _SYNC_HN_VN | _SYNC_HP_VN | _SYNC_HN_VP | _SYNC_HP_VP,          // Polarity Flags,
        1920, 1080,                                                    		// InputWidth, InputHeight,
        563, 501,                                                           // HFreq in kHz, VFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        2640, 1125,                                                         // HTotal, VTotal,
        237, 41,                                                      		// HStartPos, VStartPos,
    },

    {   //# Mode 9 : 1920 x 1080p x 60 Hz
        0 | _SYNC_HN_VN | _SYNC_HP_VN | _SYNC_HN_VP | _SYNC_HP_VP,          // Polarity Flags,
        1920, 1080,                                                    		// InputWidth, InputHeight,
        678, 603,                                                           // HFreq in kHz, VFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        2200, 562,                                                          // HTotal, VTotal,
        237, 41,                                                       		// HStartPos, VStartPos,
    },
};

BYTE code tYPBPR_TABLE_SET_SCALER[] =
{
#if (_SCALER_TYPE == _RTD2547D)

    4,  _NON_AUTOINC,   _PAGE_SELECT_A0,                _PAGE0,
    6,  _AUTOINC,       _P0_ADC_RED_CTL_A2,             0xc0,0x40,0xc0,//V305 modify

    4,  _NON_AUTOINC,   _P0_ADC_V_BAIS1_B2,             0x0d,

    4,  _NON_AUTOINC,   _SYNC_PROC_ACCESS_PORT_5C,      _SYNC_G_CLAMP_START_00,
    11,  _NON_AUTOINC,  _SYNC_PROC_DATA_PORT_5D,        0x10,0x18,0x10,0x18,0x02,0x01,0x02,0x21,

//V304 modify
    4,  _NON_AUTOINC,   _CB_ACCESS_PORT_64,             0x80,
    9,  _NON_AUTOINC,   _CB_DATA_PORT_65,               0x7e,0x7e,0x7e,0x80,0x80,0x80,
    4,  _NON_AUTOINC,   _CB_ACCESS_PORT_64,             0x00,
    4,  _NON_AUTOINC,   _PAGE_SELECT_A0,                _PAGE0,
    9,  _AUTOINC,       _P0_RED_GAIN_A5,                0x80,0x80,0x80,0x80,0x80,0x80,

    4,  _NON_AUTOINC,   _YUV2RGB_CTRL_9C,               0x08,
    21, _NON_AUTOINC,   _YUV_RGB_COEF_DATA_9D,          0x04,0x00,0x00,0x00,0x06,0x60,
                                                        0x04,0x00,0xfe,0x70,0xfc,0xc0,
                                                        0x04,0x00,0x08,0x10,0x00,0x00,

	4,  _NON_AUTOINC,   _YUV2RGB_CTRL_9C,               0x07,

#else

#if(0)//_NEW_YPBPR)
	4,  _NON_AUTOINC,  	_ADC_ACCESS_PORT_DC,            0x81,
    6,  _NON_AUTOINC,   _ADC_DATA_PORT_DD,              0xA0,0x20,0xA0,

    4,  _NON_AUTOINC,   _ADC_ACCESS_PORT_DC,            0x00,
    4,  _NON_AUTOINC,   _ADC_ACCESS_PORT_DC,            0x80,
    4,  _NON_AUTOINC,   _ADC_ACCESS_PORT_DC,            0x91,
    4,  _NON_AUTOINC,   _ADC_DATA_PORT_DD,              0x0d,
    4,  _NON_AUTOINC,   _ADC_ACCESS_PORT_DC,            0x00,
    4,  _NON_AUTOINC,   _ADC_ACCESS_PORT_DC,            0x8c,
    4,  _NON_AUTOINC,   _ADC_DATA_PORT_DD,              0x3f,

    4,  _NON_AUTOINC,   _CLAMP_CTRL0_5C,                0x02,
    5,  _AUTOINC,   	_CLAMP_START_5A, 				0x12,0x16, //	0x10,0x20,

    5,  _AUTOINC,       _YUV2RGB_CTRL_89,               0x08,0x05,
    5,  _AUTOINC,       _YUV2RGB_CTRL_89,               0x28,0x80,
    5,  _AUTOINC,       _YUV2RGB_CTRL_89,               0x48,0x01,
    5,  _AUTOINC,       _YUV2RGB_CTRL_89,               0x68,0x40,
    5,  _AUTOINC,       _YUV2RGB_CTRL_89,               0x88,0x00,
    5,  _AUTOINC,       _YUV2RGB_CTRL_89,               0xa8,0xa0,
    5,  _AUTOINC,       _YUV2RGB_CTRL_89,               0xc8,0x07,
    5,  _AUTOINC,       _YUV2RGB_CTRL_89,               0xe8,0x00,

	4,  _NON_AUTOINC,   _YUV2RGB_CTRL_89,               0x07,

#else


#if ((_SCALER_TYPE == _RTD2553V) || (_SCALER_TYPE == _RTD2546N) || (_SCALER_TYPE == _RTD2525L))
    4,  _NON_AUTOINC,  	_ADC_ACCESS_PORT_DC,            0x81,

#if(_SCALER_TYPE == _RTD2525L) 
    6,  _NON_AUTOINC,   _ADC_DATA_PORT_DD,              0xc0,0x20,0xc0, //V305 modify
#else
    6,  _NON_AUTOINC,   _ADC_DATA_PORT_DD,              0xc0,0x40,0xc0,
#endif

    4,  _NON_AUTOINC,   _ADC_ACCESS_PORT_DC,            0x00,

  //  4,  _NON_AUTOINC,   _ADC_ACCESS_PORT_DC,            0x80,
    4,  _NON_AUTOINC,   _ADC_ACCESS_PORT_DC,            0x91,
    4,  _NON_AUTOINC,   _ADC_DATA_PORT_DD,              0x0d,
 //   4,  _NON_AUTOINC,   _ADC_ACCESS_PORT_DC,            0x00,

#if((_SCALER_TYPE == _RTD2553V) || (_SCALER_TYPE == _RTD2546N))

    4,  _NON_AUTOINC,   _CLAMP_CTRL0_5C,                0x02,
    5,  _AUTOINC,       _CLAMP_START_5A,                0x10,0x18,

#elif(_SCALER_TYPE == _RTD2525L)

    4,  _NON_AUTOINC,   _SYNC_PROC_ACCESS_PORT_5C,      0x00,
   11,  _NON_AUTOINC,   _SYNC_PROC_DATA_PORT_5D,        0x10,0x18,0x10,0x18,0x02,0x01,0x02,0x21,

#endif

#else

#if(0)
    6,  _AUTOINC,   _ADC_RED_CTRL_DD,               0xc0,0x40,0xc0,

    4,  _AUTOINC,   _ADC_VBIAS1_ED,                 0x0D,

    4,  _AUTOINC,   _CLAMP_CTRL0_5C,                0x00,

    5,  _AUTOINC,   _CLAMP_START_5A,                0x10,0x18,
#else
    6,  _AUTOINC,   _ADC_RED_CTRL_DD,               0xc0,0x40,0xc0,
 
    4,  _AUTOINC,   _ADC_VBIAS1_ED,                 0x2d,
 
    4,  _AUTOINC,   _CLAMP_CTRL0_5C,                0x40,
 
    5,  _AUTOINC,   _CLAMP_START_5A,                0x10,0x18,
#endif                    
#endif

    5,  _AUTOINC,   _YUV2RGB_CTRL_89,               0x08,0x05,
    5,  _AUTOINC,   _YUV2RGB_CTRL_89,               0x28,0x9c,
    5,  _AUTOINC,   _YUV2RGB_CTRL_89,               0x48,0x01,
    5,  _AUTOINC,   _YUV2RGB_CTRL_89,               0x68,0x25,
    5,  _AUTOINC,   _YUV2RGB_CTRL_89,               0x88,0x00,
    5,  _AUTOINC,   _YUV2RGB_CTRL_89,               0xa8,0xaa,
    5,  _AUTOINC,   _YUV2RGB_CTRL_89,               0xc8,0x07,
    5,  _AUTOINC,   _YUV2RGB_CTRL_89,               0xe8,0x17,
    
	4,  _NON_AUTOINC,   _YUV2RGB_CTRL_89,               0x05,
#endif
#endif // #if (_SCALER_TYPE == _RTD2547D)

    _END
};


//--------------------------------------------------
// Global Variables
//--------------------------------------------------


//--------------------------------------------------
// Function Prototypes
//--------------------------------------------------
BYTE CYPbPrSearchMode(void);
bit CYPbPrCompareMode(BYTE ucModeCnt);
void CYPbPrGetModeInfo(void);
void CYPbPrStartUp(void);
void CYPbPrSetupMode(void);


#else

//--------------------------------------------------
// Extern Global Variables
//--------------------------------------------------
extern ModeTableType code tYPBPR_MODE_TABLE[_MAX_YPBPR_MODE];

//--------------------------------------------------
// Extern Function Prototypes
//--------------------------------------------------
extern BYTE CYPbPrSearchMode(void);
extern void CYPbPrSetupMode(void);


#endif


//----------------------------------------------------------------------------------------------------

#endif  // End of #if(_YPBPR_SUPPORT == _ON)
