
// _PANEL_TTL,_PANEL_HZ,_PANEL_LVDS,
// _PANEL_RSDS,_PANEL_COG
#define _OUTPUT_BUS                     _PANEL_TTL
//--------------------------------------------------
#define _DISP_24_BIT                    (0 << 7)
#define _DISP_18_BIT                    (1 << 7)

#define _DISP_BIT                       _DISP_18_BIT 
//--------------------------------------------------
#define _DISP_EO_SWAP                   0//(1 << 6)
#define _DISP_RB_SWAP                   (1 << 5)
#define _DISP_ML_SWAP                   (1 << 4)
//--------------------------------------------------
#define _DISP_SINGLE_PORT               (0 << 3)
#define _DISP_DOUBLE_PORT               (1 << 3)

#define _DISPLAY_PORT                   _DISP_SINGLE_PORT
//--------------------------------------------------
#define _RSDS_GC_SWAP                   0//(1 << 2)
#define _RSDS_HL_SWAP                   0//(1 << 1)
#define _RSDS_PN_SWAP                   0//(1 << 0)
//--------------------------------------------------
#define _DISP_WID                       640
#define _DISP_LEN                       480 

#define _DH_ACT_STA_POS                 53  
#define _DH_ACT_END_POS                 (_DISP_WID + _DH_ACT_STA_POS)

#define _DV_ACT_STA_POS                 25//38 
#define _DV_ACT_END_POS                 (_DISP_LEN + _DV_ACT_STA_POS)
//--------------------------------------------------
#define _LVDS_MAP1                      0x00
#define _LVDS_MAP2                      0x01

#define _LVDS_MAP                       _LVDS_MAP1
//--------------------------------------------------
#define _STD_DH_TOTAL                   780
#define _MAX_DH_TOTAL                   960
#define _MIN_DH_TOTAL                   680

#define _STD_DV_TOTAL                   560
#define _MAX_DV_TOTAL                   600
#define _MIN_DV_TOTAL                   530

#define _STD_PIXCEL_CLOCK               7 
#define _MAX_PIXCEL_CLOCK               8 
#define _MIN_PIXCEL_CLOCK               6  

#define _HSYNC_WIDTH                    19
#define _VSYNC_HEIGHT                   3

#define _FREE_RUN_DCLK                  22000  // NTSC_DCLK
//--------------------------------------------------
// Definitions for Display VIDEO/TV Signal
//--------------------------------------------------
#define _VIDEO_60_DH_TOTAL              _STD_DH_TOTAL
#define _VIDEO_50_DH_TOTAL              _STD_DH_TOTAL
#define _NTSC_DCLK                      23433 
#define _PAL_DCLK                       21000 
#define _PAL_SCALING                    0x09
#define _NTSC_SCALING                   0x09
#define _INPUT_SYNC_POLARITY            0x45

//--------------------------------------------------
// Definitions for First DHS Masking
//--------------------------------------------------
#define _DHS_MASK                       0//(1 << 7)


//--------------------------------------------------
// Definitions for Display Signal
//--------------------------------------------------
#define _DVS_INVERT                     (_DISABLE << 2)
#define _DHS_INVERT                     (_DISABLE << 1)
#define _DEN_INVERT                     (_DISABLE)

#define _DISPLAY_INVERT                 (_DVS_INVERT | _DHS_INVERT | _DEN_INVERT)


//--------------------------------------------------
// Definitions for Display Control
//--------------------------------------------------
#define _DISPLAY_CTRL                   (_DHS_MASK | _DISPLAY_INVERT)

//--------------------------------------------------
// Support Timing
//--------------------------------------------------
#define _H_FREQ_MAX                     930             // Unit in 0.1 kHZ
#define _H_FREQ_MIN                     100             // Unit in 0.1 kHZ
#define _V_FREQ_MAX                     890             // Unit in 0.1 HZ
#define _V_FREQ_MIN                     490             // Unit in 0.1 HZ

#ifdef __MAIN__

//--------------------------------------------------
// Display Interface Initial
//--------------------------------------------------
BYTE code tTTL_INITIAL[] =
{        
    #if(_OUTPUT_BUS == _PANEL_TTL)    
#if (_SCALER_TYPE == _RTD2528R)
#else
 /*   5,  _AUTOINC,       _TCON_ADDR_PORT_8B,             0x00,0x40,
    
    4,  _NON_AUTOINC,   _PIN_SHARE_CTRL0_8D,            0x02,

    4,  _NON_AUTOINC,   _PIN_SHARE_CTRL1_8E,            0x52,  
    
    5,  _AUTOINC,       _TCON_ADDR_PORT_8B,             0x01,0x3e,

    5,  _AUTOINC,       _TCON_ADDR_PORT_8B,             0x78,0xf0,
   */  
    #endif 
    // Please Set pin share in PCB file
    5,  _AUTOINC,       _TCON_ADDR_PORT_8B,             0x00,0xc0,      

    5,  _AUTOINC,       _TCON_ADDR_PORT_8B,             0x00,0x40,  
      
    5,  _AUTOINC,       _TCON_ADDR_PORT_8B,             0x01,0x3e,

    5,  _AUTOINC,       _TCON_ADDR_PORT_8B,             0x78,0xf0,           // POWER UP LVDS
 
    4,  _NON_AUTOINC,   _TCON_ADDR_PORT_8B,             0x58,
    10, _NON_AUTOINC,   _TCON_DATA_PORT_8C,             0x00,0x00,0x0f,_DH_ACT_STA_POS,0x22,(_DH_ACT_STA_POS+_HSYNC_WIDTH/2),0xc0,
 
    4,  _NON_AUTOINC,   _TCON_ADDR_PORT_8B,             0x60,
    10, _NON_AUTOINC,   _TCON_DATA_PORT_8C,             0x00,0x30,0x60,0x00,0x00,_HSYNC_WIDTH+1,0xC1,
 
    5,  _AUTOINC,       _TCON_ADDR_PORT_8B,             0x00,0xc0,      
#endif

    _END
}; 

//--------------------------------------------------
BYTE code tLVDS_INITIAL[] =
{
#if(_SCALER_TYPE == _RTD2553V || _SCALER_TYPE == _RTD2546N)       // RTD2553V

    5,  _AUTOINC,       _TCON_ADDR_PORT_8B,             0x00,0x02,
    5,  _AUTOINC,       _TCON_ADDR_PORT_8B,             0x01,0x08,
    4,  _NON_AUTOINC,   _TCON_ADDR_PORT_8B,             _LVDS_CTRL0_78,
    9,  _NON_AUTOINC,   _TCON_DATA_PORT_8C,             0x00,0x15,0x05,0x1c | _LVDS_MAP,0x80,0x80,

#elif (_SCALER_TYPE == _RTD2528R)

    5,  _AUTOINC,       _TCON_ADDR_PORT_8B,             _TCON_CTRL0_00,0x01,
    4,  _NON_AUTOINC,   _TCON_ADDR_PORT_8B,             _TCON_LVDS_CTRL0_A0,
    9,  _NON_AUTOINC,   _TCON_DATA_PORT_8C,             0x00,0x14,0x85,0x1c,0x80,0x80,

#elif(_SCALER_TYPE == _RTD2525L)     // RTD2525L

    5,  _AUTOINC,       _TCON_ADDR_PORT_8B,             0x00,0x02,
    5,  _AUTOINC,       _TCON_ADDR_PORT_8B,             0x01,0x28,
    4,  _NON_AUTOINC,   _TCON_ADDR_PORT_8B,             _LVDS_CTRL0_78,
    9,  _NON_AUTOINC,   _TCON_DATA_PORT_8C,             0x00,0x15,0x05,0x1c | _LVDS_MAP,0x80,0x80,

#elif(_SCALER_TYPE == _RTD2533B)     // RTD2523B

    5,  _AUTOINC,       _TCON_ADDR_PORT_8B,             0x00,0x02,
    5,  _AUTOINC,       _TCON_ADDR_PORT_8B,             0x01,0x04,
    4,  _NON_AUTOINC,   _TCON_ADDR_PORT_8B,             _LVDS_CTRL0_78,
    9,  _NON_AUTOINC,   _TCON_DATA_PORT_8C,             0x00,0x04,0x13,0x12 | _LVDS_MAP,0x80,0x80,

#elif(_SCALER_TYPE == _RTD2023L)     // RTD2023L

    5,  _AUTOINC,       _TCON_ADDR_PORT_8B,             0x00,0x02,
    5,  _AUTOINC,       _TCON_ADDR_PORT_8B,             0x01,0x14,
    4,  _NON_AUTOINC,   _TCON_ADDR_PORT_8B,             _LVDS_CTRL0_78,
    9,  _NON_AUTOINC,   _TCON_DATA_PORT_8C,             0x00,0x0f,0x05,0x1c | _LVDS_MAP,0x80,0x80, //V307 modify

#elif(_SCALER_TYPE == _RTD2023L_VB)  // RTD2023L VB

    5,  _AUTOINC,       _TCON_ADDR_PORT_8B,             0x00,0x02,
    5,  _AUTOINC,       _TCON_ADDR_PORT_8B,             0x01,0x12,
    4,  _NON_AUTOINC,   _TCON_ADDR_PORT_8B,             _LVDS_CTRL0_78,
    9,  _NON_AUTOINC,   _TCON_DATA_PORT_8C,             0x00,0x0e,0x06,0x1c | _LVDS_MAP,0x80,0x80,

#elif(_SCALER_TYPE == _RTD2023S)     // RTD2023S

    5,  _AUTOINC,       _TCON_ADDR_PORT_8B,             0x00,0x02,
    5,  _AUTOINC,       _TCON_ADDR_PORT_8B,             0x01,0x14,
    4,  _NON_AUTOINC,   _TCON_ADDR_PORT_8B,             _LVDS_CTRL0_78,
    9,  _NON_AUTOINC,   _TCON_DATA_PORT_8C,             0x00,0x0f,0x05,0x1c | _LVDS_MAP,0x80,0x80,

#elif(_SCALER_TYPE == _RTD2023S_VB)  // RTD2023S VB

    5,  _AUTOINC,       _TCON_ADDR_PORT_8B,             0x00,0x02,
    5,  _AUTOINC,       _TCON_ADDR_PORT_8B,             0x01,0x12, //V307 modify
    4,  _NON_AUTOINC,   _TCON_ADDR_PORT_8B,             _LVDS_CTRL0_78,
    9,  _NON_AUTOINC,   _TCON_DATA_PORT_8C,             0x00,0x0e,0x06,0x1c | _LVDS_MAP,0x80,0x80, //V307 modify

#else                                // Error scaler
    #error  Error scaler definition, add new initial code in panel
#endif

    _END
};

//--------------------------------------------------
BYTE code tRSDS_INITIAL[] =
{
    #if(_OUTPUT_BUS == _PANEL_RSDS)

#if (_SCALER_TYPE == _RTD2528R)

    5,  _AUTOINC,       _TCON_ADDR_PORT_8B,             _TCON_CTRL0_00,0x82,
    5,  _AUTOINC,       _TCON_ADDR_PORT_8B,             _TCON_CTRL1_01,0x1e,
    5,  _AUTOINC,       _TCON_ADDR_PORT_8B,             _TCON_RSDS_INTERLEAVING_H_C1,0x0a,
    5,  _AUTOINC,       _TCON_ADDR_PORT_8B,             _TCON_RSDS_INTERLEAVING_L_C2,0x7f,

    // YCLK TCON0	 TCON13
    4,  _NON_AUTOINC,   _TCON_ADDR_PORT_8B,             _TCON_TCON13_V_STA_LSB_70,
    10, _NON_AUTOINC,   _TCON_DATA_PORT_8C,             0x0c,0x40,0x0c,0xf4,0x21,0x94,0x80,

    // FXDIO TCON1	 TCON3
    4,  _NON_AUTOINC,   _TCON_ADDR_PORT_8B,             _TCON_TCON3_V_STA_LSB_20,
    10, _NON_AUTOINC,   _TCON_DATA_PORT_8C,             0x0c,0x40,0x0c,0xab,0x22,0xaf,0x80,

    // YOE TCON3 	 TCON12
    4,  _NON_AUTOINC,   _TCON_ADDR_PORT_8B,             _TCON_TCON12_V_STA_LSB_68,
    10, _NON_AUTOINC,   _TCON_DATA_PORT_8C,             0x0c,0x40,0x0c,0x94,0x52,0x14,0x80,

    // POL TCON7	 TCON6 test
    //4,  _NON_AUTOINC,   _TCON_ADDR_PORT_8B,             _TCON_TCON6_V_STA_LSB_38,
    //10, _NON_AUTOINC,   _TCON_DATA_PORT_8C,             0x0c,0x40,0x0d,0x00,0x00,0x01,0x88,

    // POL TCON7	 TCON7
    4,  _NON_AUTOINC,   _TCON_ADDR_PORT_8B,             _TCON_TCON7_V_STA_LSB_40,
    10, _NON_AUTOINC,   _TCON_DATA_PORT_8C,             0x0c,0x40,0x0d,0x00,0x00,0x01,0x88,

    // BXDIO TCON11	 TCON9
    4,  _NON_AUTOINC,   _TCON_ADDR_PORT_8B,             _TCON_TCON9_V_STA_LSB_50,
    10, _NON_AUTOINC,   _TCON_DATA_PORT_8C,             0x0c,0x40,0x0c,0xab,0x22,0xaf,0x80,

    // YDIO TCON12	 TCON1
    4,  _NON_AUTOINC,   _TCON_ADDR_PORT_8B,             _TCON_TCON1_V_STA_LSB_10,
    10, _NON_AUTOINC,   _TCON_DATA_PORT_8C,             0x0c,0x00,0x0e,0xd0,0x33,0xd7,0x88,

    // XSTB TCON13	 TCON2
    4,  _NON_AUTOINC,   _TCON_ADDR_PORT_8B,             _TCON_TCON2_V_STA_LSB_18,
    10, _NON_AUTOINC,   _TCON_DATA_PORT_8C,             0x0c,0x40,0x0c,0x35,0x22,0xac,0x80,

#else

    5,  _AUTOINC,       _TCON_ADDR_PORT_8B,             0x00,0x83,
    5,  _AUTOINC,       _TCON_ADDR_PORT_8B,             0x01,0x14,
    5,  _AUTOINC,       _TCON_ADDR_PORT_8B,             0x06,0x06,
    5,  _AUTOINC,       _TCON_ADDR_PORT_8B,             0x07,0x7f,

    // YCLK TCON0
    4,  _NON_AUTOINC,   _TCON_ADDR_PORT_8B,             0x08,
    10, _NON_AUTOINC,   _TCON_DATA_PORT_8C,             0x0c,0x40,0x0c,0xf4,0x21,0x94,0x80,

    // FXDIO TCON1
    4,  _NON_AUTOINC,   _TCON_ADDR_PORT_8B,             0x10,
    10, _NON_AUTOINC,   _TCON_DATA_PORT_8C,             0x0c,0x40,0x0c,0xab,0x22,0xaf,0x80,

    // YOE TCON3 
    4,  _NON_AUTOINC,   _TCON_ADDR_PORT_8B,             0x20,
    10, _NON_AUTOINC,   _TCON_DATA_PORT_8C,             0x0c,0x40,0x0c,0x94,0x52,0x14,0x80,

    // POL TCON7
    4,  _NON_AUTOINC,   _TCON_ADDR_PORT_8B,             0x40,
    10, _NON_AUTOINC,   _TCON_DATA_PORT_8C,             0x0c,0x40,0x0d,0x00,0x00,0x01,0x88,

    // BXDIO TCON11
    4,  _NON_AUTOINC,   _TCON_ADDR_PORT_8B,             0x60,
    10, _NON_AUTOINC,   _TCON_DATA_PORT_8C,             0x0c,0x40,0x0c,0xab,0x22,0xaf,0x80,

    // YDIO TCON12
    4,  _NON_AUTOINC,   _TCON_ADDR_PORT_8B,             0x68,
    10, _NON_AUTOINC,   _TCON_DATA_PORT_8C,             0x0c,0x00,0x0e,0xd0,0x33,0xd7,0x88,

    // XSTB TCON13
    4,  _NON_AUTOINC,   _TCON_ADDR_PORT_8B,             0x70,
    10, _NON_AUTOINC,   _TCON_DATA_PORT_8C,             0x0c,0x40,0x0c,0x35,0x22,0xac,0x80,
#endif
    #endif

    _END
};
//--------------------------------------------------
// EDID Table
//--------------------------------------------------
#if(_VGA_SUPPORT)
BYTE code tEDID_TABLE_VGA[] =
{
    0x00,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0x4a,0x8b,0x00,0x00,0x01,0x01,0x01,0x01,
    0x1e,0x0c,0x01,0x01,0x0e,0x24,0x1b,0x78,0xe8,0x8a,0x01,0x9a,0x58,0x52,0x8b,0x28,
    0x1e,0x50,0x54,0xff,0xff,0x80,0x61,0x40,0x61,0x4f,0x61,0x59,0x71,0x4f,0x81,0x40,
    0x81,0x59,0x81,0x99,0xa9,0x40,0x00,0x00,0x00,0xfc,0x00,0x31,0x37,0x27,0x27,0x20,
    0x4c,0x43,0x44,0x0a,0x20,0x20,0x20,0x20,0x00,0x00,0x00,0xfc,0x00,0x4d,0x6f,0x6e,
    0x69,0x74,0x6f,0x72,0x0a,0x20,0x20,0x20,0x20,0x20,0x00,0x00,0x00,0xfd,0x00,0x2b,
    0x55,0x14,0x5c,0x0e,0x00,0x0a,0x20,0x20,0x20,0x20,0x20,0x20,0x00,0x00,0x00,0xff,
    0x00,0x30,0x30,0x30,0x30,0x30,0x31,0x0a,0x20,0x20,0x20,0x20,0x20,0x20,0x00,0xbd,
};
#endif

#if (_TMDS_SUPPORT)
BYTE code tEDID_TABLE_DVI[] =
{
    0x00,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0x26,0xCD,0x68,0x46,0x00,0x00,0x00,0x00,
    0x23,0x0c,0x01,0x03,0x81,0x24,0x1D,0x78,0xeF,0x0D,0xC2,0xa0,0x57,0x47,0x98,0x27,
    0x12,0x48,0x4F,0xBF,0xEF,0x00,0x81,0x80,0x81,0x8F,0x61,0x40,0x61,0x59,0x45,0x40,
    0x45,0x59,0x31,0x40,0x31,0x59,0xBC,0x34,0x00,0x98,0x51,0x00,0x2A,0x40,0x10,0x90,
    0x13,0x00,0x68,0x22,0x11,0x00,0x00,0x1e,0x00,0x00,0x00,0xFF,0x00,0x30,0x0A,0x20,
    0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x00,0x00,0x00,0xFC,0x00,0x41,
    0x53,0x34,0x36,0x33,0x37,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x00,0x00,0x00,0xFD,
    0x00,0x38,0x55,0x18,0x50,0x0E,0x00,0x0A,0x20,0x20,0x20,0x20,0x20,0x20,0x00,0x06,
};
#endif

code PanelType Panel =
{        
        _OUTPUT_BUS,                                        // Panel Style
                                                           
        _DISPLAY_PORT | _DISP_BIT |                            // Panel Configuration
        _DISP_EO_SWAP | _DISP_RB_SWAP | _DISP_ML_SWAP | 
        _DISPLAY_PORT | 
        _RSDS_GC_SWAP | _RSDS_HL_SWAP | _RSDS_PN_SWAP,


        _DH_ACT_STA_POS,                                         // Display Horizontal Start Position
        _DISP_WID,                                               // Display Horizontal Width
        _DH_ACT_END_POS,                                         // Display Horizontal End Position

        _STD_DH_TOTAL,                                           // Display Horizontal Total Clock Number in One Display Line
        _MAX_DH_TOTAL,                                           // Maxinum Display Horizontal Total Clock Number in One Display Line
        _MIN_DH_TOTAL,                                           // Mininum Display Horizontal Total Clock Number in One Display Line

        _DV_ACT_STA_POS,                                         // Display Vertical Start Position
        _DISP_LEN,                                               // Display Vertical Height
        _DV_ACT_END_POS,                                         // Display Vertical End Position

        _STD_DV_TOTAL,                                           // Display Vertical Total Line Number in One Frame
        _MAX_DV_TOTAL,                                           // Maxinum Display Vertical Total Line Number in One Frame
        _MIN_DV_TOTAL,                                           // Mininum Display Vertical Total Line Number in One Frame

        _HSYNC_WIDTH,                                            // Display H Sync Width
        _VSYNC_HEIGHT,                                           // Display V Sync Height

        _STD_PIXCEL_CLOCK,                                       // Typical Pixel Clock in MHz
        _MAX_PIXCEL_CLOCK,                                       // Maxinum Pixel Clock in MHz
        _MIN_PIXCEL_CLOCK                                        // Mininum Pixel Clock in MHz
}; 


//--------------------------------------------------

WORD code tVIDEO_TABLE_INPUT_INFO[][5] =
{
    // IHTotal, IHStart, IHWidth, IVStart, IVHeight
    {    864,     25,     666,     30,     270 },  // 50HZ 
    {    858,     27,     640,     30,     224 },  // 60HZ
};


#if(_SET_VIDEO_MODE_METHOD == _TABLE) // Write table

//-----------------------------------------------------------
//
//                 PAL  16:9
//
//-----------------------------------------------------------

BYTE code tPAL_16_9[] =
{   
   0x00,
};

// Scaling factor CR[1A], Not 2547D
BYTE code tPAL_SCALING_FACTOR_1A_16_9[] =
{
   0x00,
};

// Saling down CR[24]  for 2553V/2525L/2547D
BYTE code tPAL_SCALING_DOWN_24_16_9[] =
{
   0x00,
};

// Only for RTD2547D
BYTE code tPAL_PAGE1_16_9[] =
{
   0x00,
};

BYTE code tPAL_DISP_FORMAT_2A_16_9[] =
{
   0x00,
};

BYTE code tPAL_FIFO_WINDOW_30_16_9[] =
{
   0x00,
};

BYTE code tPAL_SF_ACCESS_PORT_33_16_9[] =
{
   0x00,
};

//-----------------------------------------------------------
//
//                PAL   4:3
//
//-----------------------------------------------------------
BYTE code tPAL_4_3[] =
{                  
   0x00,
};

// Scaling factor CR[1A], Not 2547D
BYTE code tPAL_SCALING_FACTOR_1A_4_3[] =
{
   0x00,
};

// Saling down CR[24]  for 2553V/2525L/2547D
BYTE code tPAL_SCALING_DOWN_24_4_3[] =
{
   0x00,
};

// Only for RTD2547D
BYTE code tPAL_PAGE1_4_3[] =
{
   0x00,
};

BYTE code tPAL_DISP_FORMAT_2A_4_3[] =
{
   0x00,
};

BYTE code tPAL_FIFO_WINDOW_30_4_3[] =
{
   0x00,
};

BYTE code tPAL_SF_ACCESS_PORT_33_4_3[] =
{
   0x00,
};

//-----------------------------------------------------------
//
//                NTSC   16:9
//
//-----------------------------------------------------------
BYTE code tNTSC_16_9[] =
{     
   0x00,
};

// Scaling factor CR[1A], Not 2547D
BYTE code tNTSC_SCALING_FACTOR_1A_16_9[] =
{
   0x00,
};

// Saling down CR[24]  for 2553V/2525L/2547D
BYTE code tNTSC_SCALING_DOWN_24_16_9[] =
{
   0x00,
};

// Only for RTD2547D
BYTE code tNTSC_PAGE1_16_9[] =
{
   0x00,
};

BYTE code tNTSC_DISP_FORMAT_2A_16_9[] =
{
   0x00,
};

BYTE code tNTSC_FIFO_WINDOW_30_16_9[] =
{
   0x00,
};

BYTE code tNTSC_SF_ACCESS_PORT_33_16_9[] =
{
   0x00,
};

//-----------------------------------------------------------
//
//                NTSC   4:3
//
//-----------------------------------------------------------
BYTE code tNTSC_4_3[] =
{
   0x00,
};


// Scaling factor CR[1A], Not 2547D
BYTE code tNTSC_SCALING_FACTOR_1A_4_3[] =
{
   0x00,
};

// Saling down CR[24]  for 2553V/2525L/2547D
BYTE code tNTSC_SCALING_DOWN_24_4_3[] =
{
   0x00,
};

// Only for RTD2547D
BYTE code tNTSC_PAGE1_4_3[] =
{
   0x00,
};

BYTE code tNTSC_DISP_FORMAT_2A_4_3[] =
{
   0x00,
};

BYTE code tNTSC_FIFO_WINDOW_30_4_3[] =
{
   0x00,
};

BYTE code tNTSC_SF_ACCESS_PORT_33_4_3[] =
{
   0x00,
};


#endif //#if(_SET_VIDEO_MODE_METHOD == _TABLE) // Write table


#else

extern BYTE code tTTL_INITIAL[];
extern BYTE code tLVDS_INITIAL[];
extern BYTE code tRSDS_INITIAL[];

#if(_VGA_SUPPORT)
extern BYTE code tEDID_TABLE_VGA[];
#endif
#if (_TMDS_SUPPORT)
extern BYTE code tEDID_TABLE_DVI[];
#endif

WORD code tVIDEO_TABLE_INPUT_INFO[][5];

extern code PanelType Panel;

#if(_SET_VIDEO_MODE_METHOD == _TABLE) // Write table
extern BYTE code tPAL_16_9[];
extern BYTE code tPAL_4_3[];
extern BYTE code tNTSC_16_9[];
extern BYTE code tNTSC_4_3[];
extern BYTE code tPAL_SCALING_FACTOR_1A_16_9[];
extern BYTE code tPAL_SCALING_FACTOR_1A_4_3[];
extern BYTE code tNTSC_SCALING_FACTOR_1A_16_9[];
extern BYTE code tNTSC_SCALING_FACTOR_1A_4_3[];

// _SCALER_TYPE == _RTD2553V || _SCALER_TYPE == _RTD2546N || _SCALER_TYPE == _RTD2525L
extern BYTE code tPAL_SCALING_DOWN_24_16_9[];
extern BYTE code tPAL_SCALING_DOWN_24_4_3[];
extern BYTE code tNTSC_SCALING_DOWN_24_16_9[];
extern BYTE code tNTSC_SCALING_DOWN_24_4_3[];
#endif //#if(_SET_VIDEO_MODE_METHOD == _TABLE) // Write table

// For RTD2547D
extern BYTE code tNTSC_PAGE1_4_3[];
extern BYTE code tNTSC_PAGE1_16_9[];
extern BYTE code tNTSC_DISP_FORMAT_2A_4_3[];
extern BYTE code tNTSC_DISP_FORMAT_2A_16_9[];
extern BYTE code tNTSC_FIFO_WINDOW_30_4_3[];
extern BYTE code tNTSC_FIFO_WINDOW_30_16_9[];
extern BYTE code tNTSC_SF_ACCESS_PORT_33_4_3[];
extern BYTE code tNTSC_SF_ACCESS_PORT_33_16_9[];
extern BYTE code tPAL_PAGE1_4_3[];
extern BYTE code tPAL_PAGE1_16_9[];
extern BYTE code tPAL_DISP_FORMAT_2A_4_3[];
extern BYTE code tPAL_DISP_FORMAT_2A_16_9[];
extern BYTE code tPAL_FIFO_WINDOW_30_4_3[];
extern BYTE code tPAL_FIFO_WINDOW_30_16_9[];
extern BYTE code tPAL_SF_ACCESS_PORT_33_4_3[];
extern BYTE code tPAL_SF_ACCESS_PORT_33_16_9[];
#endif
//-------------------------------------------------------------
