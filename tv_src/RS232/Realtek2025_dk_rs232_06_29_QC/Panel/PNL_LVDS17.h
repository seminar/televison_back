
// _PANEL_TTL,_PANEL_HZ,_PANEL_LVDS,
// _PANEL_RSDS,_PANEL_COG
#define _OUTPUT_BUS                     _PANEL_LVDS

//--------------------------------------------------
#define _DISP_24_BIT                    (0 << 7)
#define _DISP_18_BIT                    (1 << 7)

#define _DISP_BIT                       _DISP_24_BIT

//--------------------------------------------------
#define _DISP_EO_SWAP                   (1 << 6)
#define _DISP_RB_SWAP                   0//(1 << 5)
#define _DISP_ML_SWAP                   0//(1 << 4)

//--------------------------------------------------
#define _DISP_SINGLE_PORT               (0 << 3)
#define _DISP_DOUBLE_PORT               (1 << 3)

#define _DISPLAY_PORT                   _DISP_DOUBLE_PORT

//--------------------------------------------------
#define _RSDS_GC_SWAP                   0//(1 << 2)
#define _RSDS_HL_SWAP                   0//(1 << 1)
#define _RSDS_PN_SWAP                   0//(1 << 0)

//--------------------------------------------------
#define _DISP_WID                       1280
#define _DISP_LEN                       1024

#define _DH_ACT_STA_POS                 32
#define _DH_ACT_END_POS                 (_DISP_WID + _DH_ACT_STA_POS)

#define _DV_ACT_STA_POS                 16
#define _DV_ACT_END_POS                 (_DISP_LEN + _DV_ACT_STA_POS)

//--------------------------------------------------
#define _LVDS_MAP1                      0x00
#define _LVDS_MAP2                      0x01

#define _LVDS_MAP                       _LVDS_MAP1

//--------------------------------------------------
#define _STD_DH_TOTAL                   1440
#define _MAX_DH_TOTAL                   2044
#define _MIN_DH_TOTAL                   1380

#define _STD_DV_TOTAL                   1072
#define _MAX_DV_TOTAL                   1272
#define _MIN_DV_TOTAL                   1034

#define _STD_PIXCEL_CLOCK               108
#define _MAX_PIXCEL_CLOCK               170
#define _MIN_PIXCEL_CLOCK               100

#define _HSYNC_WIDTH                    16
#define _VSYNC_HEIGHT                   3

#define _FREE_RUN_DCLK                  ((DWORD)_STD_PIXCEL_CLOCK * 1000) //((DWORD)(138 - 10) * 1000)

//--------------------------------------------------
// Definitions for Display VIDEO/TV Signal
//--------------------------------------------------
#define _VIDEO_60_DH_TOTAL              _STD_DH_TOTAL
#define _VIDEO_50_DH_TOTAL              _STD_DH_TOTAL
#define _NTSC_DCLK                      95600
#define _PAL_DCLK                       80570
#define _INPUT_SYNC_POLARITY            0x15

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
#define _V_FREQ_MIN                     470             // Unit in 0.1 HZ

#ifdef __MAIN__

//--------------------------------------------------
// Display Interface Initial
//--------------------------------------------------
BYTE code tTTL_INITIAL[] =
{
    #if(_OUTPUT_BUS == _PANEL_TTL)    
    
#if (_SCALER_TYPE == _RTD2547D)
    5,  _AUTOINC,       _TCON_ADDR_PORT_8B,             _TCON_CTRL0_00,0x00,

    4,  _NON_AUTOINC,   _DISP_ACCESS_PORT_2A,           _DISP_TIMING_20,
    4,  _NON_AUTOINC,   _DISP_DATA_PORT_2B,             0x02,
#else
    5,  _AUTOINC,       _TCON_ADDR_PORT_8B,             0x00,0x00,
    4,  _NON_AUTOINC,   _DISP_TIMING_46,                0x02,
#endif

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

#elif (_SCALER_TYPE == _RTD2547D)

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

#if (_SCALER_TYPE == _RTD2547D)

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
BYTE code tEDID_TABLE_VGA[9][128] =
{
//1920x1200  VGA 20080510 <0>
{
 0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x46,0xC1,0x18,0x00,0x01,0x00,0x00,0x00
,0x17,0x11,0x01,0x03,0x08,0x34,0x20,0x78,0x2A,0xEE,0x91,0xA3,0x54,0x4C,0x99,0x26
,0x0F,0x50,0x54,0xA7,0x0B,0x00,0xA9,0x40,0x61,0x40,0x81,0xC0,0x81,0x80,0x81,0x8A
,0x81,0x8C,0x71,0x40,0xD1,0xC0,0x7D,0x4B,0x80,0xA0,0x72,0xB0,0x2D,0x40,0x50,0x98
,0x36,0x00,0x9A,0x00,0x11,0x00,0x00,0x1C,0xF0,0x0A,0xD0,0xB4,0x20,0xE0,0x2D,0x10
,0x12,0x6C,0xA2,0x00,0x98,0x32,0x11,0x00,0x00,0x1E,0x08,0x39,0x80,0x00,0x71,0x38
,0x26,0x40,0x30,0x20,0x36,0x00,0x81,0x91,0x21,0x00,0x00,0x18,0x00,0x00,0x00,0xFF
,0x00,0x4C,0x43,0x44,0x20,0x4D,0x4F,0x4E,0x0A,0x20,0x20,0x20,0x20,0x20,0x00,0x59,
},
{
	// 1920x1080    <1>
 0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x1E,0x6D,0x7E,0xC3,0xB6,0xCF,0x00,0x00
,0x03,0x12,0x01,0x03,0x0D,0x46,0x27,0x78,0xEA,0xD9,0xB0,0xA3,0x57,0x49,0x9C,0x25
,0x11,0x49,0x4B,0xA5,0x4E,0x00,0x81,0x80,0x01,0x01,0xA9,0x40,0xD1,0xC0,0x01,0x01
,0x01,0x01,0x01,0x01,0x01,0x01,0x1A,0x36,0x80,0xA0,0x70,0x38,0x1F,0x40,0x30,0x20
,0x35,0x00,0xBC,0x86,0x21,0x00,0x00,0x1A,0x66,0x21,0x50,0xA0,0x51,0x00,0x1E,0x30
,0x48,0x88,0x35,0x00,0xBC,0x86,0x21,0x00,0x00,0x1A,0x00,0x00,0x00,0xFD,0x00,0x3A
,0x4B,0x1F,0x3D,0x0F,0x00,0x0A,0x20,0x20,0x20,0x20,0x20,0x20,0x00,0x00,0x00,0xFC
,0x00,0x4C,0x47,0x20,0x54,0x56,0x0A,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x01,0x0A,
},
{
	//1680X1050 VGA      <2>
 0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x58,0xE1,0x01,0x00,0x01,0x00,0x00,0x00
,0x1D,0x10,0x01,0x03,0x0C,0x00,0x00,0x00,0x8A,0x00,0x13,0xA0,0x57,0x49,0x9B,0x26
,0x10,0x48,0x4E,0xAD,0xCF,0x00,0x45,0x4A,0x61,0x4C,0x81,0x80,0x95,0x00,0x81,0x8A
,0x81,0x8C,0xB3,0x00,0x01,0x01,0x21,0x39,0x90,0x40,0x62,0x1A,0x25,0x40,0x68,0xB8
,0x16,0x00,0xD9,0x28,0x11,0x00,0x00,0x00,0x00,0x00,0x00,0xFC,0x00,0x41,0x4E,0x41
,0x4C,0x4F,0x47,0x0A,0x0A,0x0A,0x0A,0x0A,0x0A,0x0A,0x00,0x00,0x00,0xFD,0x00,0x3C
,0x4B,0x3C,0x50,0x0F,0x00,0x0A,0x20,0x20,0x20,0x20,0x20,0x20,0x0E,0x21,0x50,0xA0
,0x51,0x00,0x1B,0x30,0x40,0x72,0x15,0x00,0xD0,0x00,0x01,0x00,0x00,0x06,0x00,0xA6,
},
{
//1440X900   VGA  OK   <3>
 0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x51,0xF0,0x20,0x09,0x64,0x00,0x00,0x00
,0x1E,0x10,0x01,0x03,0x0C,0x2B,0x1B,0x78,0x8A,0xF0,0x65,0x98,0x57,0x51,0x91,0x27
,0x02,0x05,0x05,0xAD,0xCF,0x00,0x81,0x80,0x81,0xC0,0x01,0x01,0x01,0x01,0x01,0x01
,0x01,0x01,0x01,0x01,0x01,0x01,0xCC,0x29,0xA0,0xD0,0x51,0x84,0x22,0x30,0x50,0x98
,0x36,0x00,0x00,0x00,0x00,0x00,0x00,0x1C,0x00,0x00,0x00,0x10,0x00,0x3F,0x30,0x50
,0x3F,0x0A,0x0A,0x0A,0x0A,0x0A,0x0A,0x0A,0x0A,0x0A,0xC4,0x22,0xA0,0xA0,0x50,0x84
,0x1A,0x30,0x30,0x20,0x36,0x00,0x00,0x00,0x00,0x00,0x00,0x1A,0x00,0x00,0x00,0xFC
,0x00,0x41,0x6E,0x61,0x6C,0x6F,0x67,0x0A,0x0A,0x0A,0x0A,0x0A,0x0A,0x0A,0x20,0xC9,
},
{
//_1366_768   VGA  OK    <4>

0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x15,0xCD,0xD2,0x0F,0x01,0x01,0x01,0x01,
0x00,0x10,0x01,0x03,0x68,0x52,0x2E,0x78,0x2A,0x4A,0xEA,0xA4,0x56,0x47,0x9B,0x24,
0x12,0x48,0x4A,0x2F,0xCE,0x00,0x31,0x59,0x45,0x59,0x01,0x01,0x01,0x01,0x01,0x01,
0x01,0x01,0x01,0x01,0x01,0x01,0x1B,0x21,0x50,0xA0,0x51,0x00,0x1E,0x30,0x48,0x88,
0x35,0x00,0x00,0x00,0x00,0x00,0x00,0x1E,0x0E,0x1F,0x00,0x80,0x51,0x00,0x1E,0x30,
0x40,0x80,0x37,0x00,0x00,0x00,0x00,0x00,0x00,0x1C,0x00,0x00,0x00,0xFD,0x00,0x37,
0x56,0x1F,0x3D,0x09,0x00,0x0A,0x20,0x20,0x20,0x20,0x20,0x20,0x00,0x00,0x00,0xFC,
0x00,0x45,0x4E,0x4D,0x41,0x52,0x20,0x4C,0x43,0x44,0x54,0x56,0x0A,0x0A,0x00,0x72,
},
{
//_1280_1024   VGA  OK   <5>
 0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x58,0xE1,0x01,0x00,0x01,0x00,0x00,0x00
,0x17,0x12,0x01,0x03,0x08,0x34,0x20,0x78,0x01,0xEE,0x91,0xA3,0x54,0x4C,0x99,0x26
,0x0F,0x50,0x54,0xAF,0xCF,0x00,0x81,0x80,0x81,0x8A,0x81,0x8C,0x01,0x01,0x01,0x01
,0x01,0x01,0x01,0x01,0x01,0x01,0x94,0x2A,0x00,0xB0,0x51,0x00,0x24,0x40,0x50,0x88
,0x17,0x00,0x9A,0x00,0x11,0x00,0x00,0x04,0x00,0x00,0x00,0x10,0x00,0x00,0x16,0x30
,0x30,0x20,0x25,0x00,0xD0,0x00,0x01,0x00,0x00,0x1E,0x00,0x00,0x00,0x10,0x00,0x38
,0x26,0x40,0x30,0x20,0x35,0x00,0x81,0x91,0x21,0x00,0x00,0x1C,0x00,0x00,0x00,0xFF
,0x00,0x41,0x6E,0x61,0x6C,0x6F,0x67,0x0A,0x0A,0x0A,0x0A,0x0A,0x0A,0x0A,0x00,0x60,
},
{
//_1280_800   VGA  OK   <6>
 0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x4F,0x2D,0x15,0x00,0x38,0x56,0x4C,0x05
,0x2F,0x0F,0x01,0x03,0x68,0x00,0x00,0xFF,0xEA,0xBB,0xB9,0xA3,0x52,0x46,0x98,0x24
,0x0F,0x48,0x4C,0xAF,0xCE,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01
,0x01,0x01,0x01,0x01,0x01,0x01,0xD0,0x20,0x00,0x98,0x51,0x20,0x1E,0x30,0xD0,0x80
,0x47,0x04,0x68,0x22,0x11,0x00,0x00,0x1C,0x48,0x26,0x00,0x98,0x51,0x20,0x1E,0x30
,0xD0,0x80,0x47,0x04,0x68,0x22,0x11,0x00,0x00,0x1C,0x36,0x29,0x00,0x98,0x51,0x20
,0x1E,0x30,0xD0,0x80,0x47,0x04,0x68,0x22,0x11,0x00,0x00,0x1C,0x00,0x00,0x00,0xFC
,0x00,0x4C,0x4D,0x31,0x35,0x58,0x44,0x0A,0x0A,0x0A,0x0A,0x0A,0x0A,0x0A,0x00,0xD2,
},
{
//1024X768           <7>
 0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x58,0xE1,0x62,0x26,0x01,0x00,0x00,0x00
,0x0B,0x12,0x01,0x03,0x0C,0x34,0x20,0x78,0xEF,0xC3,0x95,0xA3,0x59,0x4B,0x95,0x24
,0x13,0x50,0x54,0xBF,0xCE,0x00,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01
,0x01,0x01,0x01,0x01,0x01,0x01,0x64,0x19,0x00,0x40,0x41,0x00,0x26,0x30,0x18,0x88
,0x36,0x00,0x08,0x40,0x21,0x00,0x00,0x18,0x00,0x00,0x00,0x10,0x00,0x1A,0x27,0x40
,0x68,0xB0,0x36,0x00,0xE0,0x2C,0x11,0x00,0x00,0x1C,0x00,0x00,0x00,0x10,0x00,0xB0
,0x23,0x40,0x30,0x20,0x36,0x00,0x08,0x40,0x21,0x00,0x00,0x1A,0x00,0x00,0x00,0xFC
,0x00,0x41,0x6E,0x61,0x67,0x6F,0x6C,0x0A,0x0A,0x0A,0x0A,0x0A,0x0A,0x0A,0x00,0x2D,
},
{
//800X600           <8>
 0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x58,0xE1,0x62,0x26,0x01,0x00,0x00,0x00
,0x0B,0x12,0x01,0x03,0x0C,0x34,0x20,0x78,0xEF,0xC3,0x95,0xA3,0x59,0x4B,0x95,0x24
,0x13,0x50,0x54,0xBF,0xC0,0x00,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01
,0x01,0x01,0x01,0x01,0x01,0x01,0xA0,0x0F,0x20,0x00,0x31,0x58,0x1C,0x20,0x28,0x80
,0x14,0x00,0x08,0x40,0x21,0x00,0x00,0x1E,0x00,0x00,0x00,0x10,0x00,0x1A,0x27,0x40
,0x68,0xB0,0x36,0x00,0xE0,0x2C,0x11,0x00,0x00,0x1C,0x00,0x00,0x00,0x10,0x00,0xB0
,0x23,0x40,0x30,0x20,0x36,0x00,0x08,0x40,0x21,0x00,0x00,0x1A,0x00,0x00,0x00,0xFC
,0x00,0x41,0x6E,0x61,0x67,0x6F,0x6C,0x0A,0x0A,0x0A,0x0A,0x0A,0x0A,0x0A,0x00,0x0F,
},
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

//--------------------------------------------------
//PanelType xdata Panel;
PanelType xdata Panel;
BYTE PanelIndex;
code PanelType PanelArray[] =
{   
#if(1)
    //00        OUT 1280x1024 double 8 bit 2lvds
 {	
		2,                      // Panel Style  TTL\HZ\LVDS\RSDS: 0,1,2,3
		//0x50,                   // Panel Configuration 18/24 bit 1/0 bit7; EO/RB/ML SWAP, doub/sgl 1/0, RSDS GC/HL/PN SWAP :BIT7~BIT0
		//0x80,					//display ctr DHS_MASK:BIT7, DVS/DHS/DEN invert: bit2,bit1, bit0

		0,			//panel depth 1: 6 BIT; 0: 8BIT
		1,			//EO SWAP 1: SWAP; 0: NO SWAP
		0,			//RB SWAP 1: SWAP; 0: NO SWAP
		0,			//ML SWAP 1: SWAP; 0: NO SWAP

		1,			//Double port 1: double; 0: single
		0,			//RSDS GC SWAP 1: SWAP; 0: NO SWAP
		0,			//RSDS HL SWAP 1: SWAP; 0: NO SWAP
		0,			//RSDS PN SWAP 1: SWAP; 0: NO SWAP

		1,			//DHS MASK  0: The first DHS after DVS is active (Default); 1: The first DHS after DVS is inactive 
		0,			//DVS INVERT 1: INVERT; 0: NO INVERT
		0,			//DHS INVERT 1: INVERT; 0: NO INVERT
		0,			//DEN INVERT 1: INVERT; 0; NO INVERT

		0,		//_43DHStartPos
		0,		//_43DHWidth

		32,                     // Display Horizontal Start Position
		1280,                   // Display Horizontal Width
		1280+32,                   // Display Horizontal End Position

		1444,//1024,//1080,//1050,                   // Display Horizontal Total Clock Number in One Display Line
		//1100,                   // Maxinum Display Horizontal Total Clock Number in One Display Line
		//900,                   // Mininum Display Horizontal Total Clock Number in One Display Line

		16,                     // Display Vertical Start Position
		1024,                    // Display Vertical Height
		1024+16,                    // Display Vertical End Position

		1200,                    // Display Vertical Total Line Number in One Frame
		//700,                    // Maxinum Display Vertical Total Line Number in One Frame
		//620,                    // Mininum Display Vertical Total Line Number in One Frame

		16,                     // Display H Sync Width
		2,                      // Display V Sync Height

		80,// 50,//38,//50,                     // Typical Pixel Clock in MHz
		//100,                    // Maxinum Pixel Clock in MHz
		//40,                     // Mininum Pixel Clock in MHz

		930,						//H_freq_max
		200,						//H_freq_min
		890,						//V_freq_max
		490,						//V_freq_min
		7,							//DCLK_DELAY

		1444,//1024,//1325,       //PAL HTOTAL
		1444,//1024,//1056
   },
//06  1366x768    single 8 bit
{		
		2,                      // Panel Style  TTL\HZ\LVDS\RSDS: 0,1,2,3
		//0x48,                   // Panel Configuration 18/24 bit 1/0 bit7; EO/RB/ML SWAP, 
		                              //doub/sgl 1/0, RSDS GC/HL/PN SWAP :BIT7~BIT0
		//0x00,					//display ctr DHS_MASK:BIT7, DVS/DHS/DEN invert: bit2,bit1, bit0

		0,			//panel depth 1: 6 BIT; 0: 8BIT
		1,			//EO SWAP 1: SWAP; 0: NO SWAP
		0,			//RB SWAP 1: SWAP; 0: NO SWAP
		0,			//ML SWAP 1: SWAP; 0: NO SWAP

		0,//       		//Double port 1: double; 0: single
		0,			//RSDS GC SWAP 1: SWAP; 0: NO SWAP
		0,			//RSDS HL SWAP 1: SWAP; 0: NO SWAP
		0,			//RSDS PN SWAP 1: SWAP; 0: NO SWAP

		0,			//DHS MASK  0: The first DHS after DVS is active (Default); 1: The first DHS after DVS is inactive 
		0,			//DVS INVERT 1: INVERT; 0: NO INVERT
		0,			//DHS INVERT 1: INVERT; 0: NO INVERT
		0,			//DEN INVERT 1: INVERT; 0; NO INVERT

		0,		//_43DHStartPos
		0,		//_43DHWidth

		32,                 // Display Horizontal Start Position
		1366,//1280,                       // Display Horizontal Width
		1398,//1312,                 // Display Horizontal End Position

		1600,//1440,                   // Display Horizontal Total Clock Number in One Display Line
		//_MAX_DH_TOTAL,                	 // Maxinum Display Horizontal Total Clock Number in One Display Line
		//_MIN_DH_TOTAL,                   // Mininum Display Horizontal Total Clock Number in One Display Line

		16,                 // Display Vertical Start Position
		768,//1024,                       // Display Vertical Height
		784,//1040,                 // Display Vertical End Position

		806,//1072,                   // Display Vertical Total Line Number in One Frame
		//_MAX_DV_TOTAL,                   // Maxinum Display Vertical Total Line Number in One Frame
		//_MIN_DV_TOTAL,                   // Mininum Display Vertical Total Line Number in One Frame

		16,                    // Display H Sync Width
		3,                   // Display V Sync Height

		80,//135,               // Typical Pixel Clock in MHz
		// _MAX_PIXCEL_CLOCK,               // Maxinum Pixel Clock in MHz
		// _MIN_PIXCEL_CLOCK,               // Mininum Pixel Clock in MHz

		830,						//H_freq_max
		100,						//H_freq_min
		770,						//V_freq_max
		490,						//V_freq_min
		0,							//DCLK_DELAY

		1600,//                            //PAL HTOTAL
		1600,// 
 },	 
    //00        OUT 1280x1024 double 8 bit 2lvds
 {	
		2,                      // Panel Style  TTL\HZ\LVDS\RSDS: 0,1,2,3
		//0x50,                   // Panel Configuration 18/24 bit 1/0 bit7; EO/RB/ML SWAP, doub/sgl 1/0, RSDS GC/HL/PN SWAP :BIT7~BIT0
		//0x80,					//display ctr DHS_MASK:BIT7, DVS/DHS/DEN invert: bit2,bit1, bit0

		0,			//panel depth 1: 6 BIT; 0: 8BIT
		1,			//EO SWAP 1: SWAP; 0: NO SWAP
		0,			//RB SWAP 1: SWAP; 0: NO SWAP
		0,			//ML SWAP 1: SWAP; 0: NO SWAP

		1,			//Double port 1: double; 0: single
		0,			//RSDS GC SWAP 1: SWAP; 0: NO SWAP
		0,			//RSDS HL SWAP 1: SWAP; 0: NO SWAP
		0,			//RSDS PN SWAP 1: SWAP; 0: NO SWAP

		1,			//DHS MASK  0: The first DHS after DVS is active (Default); 1: The first DHS after DVS is inactive 
		0,			//DVS INVERT 1: INVERT; 0: NO INVERT
		0,			//DHS INVERT 1: INVERT; 0: NO INVERT
		0,			//DEN INVERT 1: INVERT; 0; NO INVERT

		0,		//_43DHStartPos
		0,		//_43DHWidth

		32,                     // Display Horizontal Start Position
		1280,                   // Display Horizontal Width
		1280+32,                   // Display Horizontal End Position

		1444,//1024,//1080,//1050,                   // Display Horizontal Total Clock Number in One Display Line
		//1100,                   // Maxinum Display Horizontal Total Clock Number in One Display Line
		//900,                   // Mininum Display Horizontal Total Clock Number in One Display Line

		16,                     // Display Vertical Start Position
		1024,                    // Display Vertical Height
		1024+16,                    // Display Vertical End Position

		1200,                    // Display Vertical Total Line Number in One Frame
		//700,                    // Maxinum Display Vertical Total Line Number in One Frame
		//620,                    // Mininum Display Vertical Total Line Number in One Frame

		16,                     // Display H Sync Width
		2,                      // Display V Sync Height

		80,// 50,//38,//50,                     // Typical Pixel Clock in MHz
		//100,                    // Maxinum Pixel Clock in MHz
		//40,                     // Mininum Pixel Clock in MHz

		930,						//H_freq_max
		200,						//H_freq_min
		890,						//V_freq_max
		490,						//V_freq_min
		7,							//DCLK_DELAY

		1444,//1024,//1325,       //PAL HTOTAL
		1444,//1024,//1056
   },

	//01 XG09/LC150XN01(12V) 1024X768/ single 8 bit
 {		
		2,          // Panel Style  TTL\HZ\LVDS\RSDS: 0,1,2,3

		0,			//panel depth 1: 6 BIT; 0: 8BIT
		1,			//EO SWAP 1: SWAP; 0: NO SWAP
		0,			//RB SWAP 1: SWAP; 0: NO SWAP
		0,			//ML SWAP 1: SWAP; 0: NO SWAP

		0,			//Double port 1: double; 0: single
		0,			//RSDS GC SWAP 1: SWAP; 0: NO SWAP
		0,			//RSDS HL SWAP 1: SWAP; 0: NO SWAP
		0,			//RSDS PN SWAP 1: SWAP; 0: NO SWAP

		1,			//DHS MASK  0: The first DHS after DVS is active (Default); 1: The first DHS after DVS is inactive 
		0,			//DVS INVERT 1: INVERT; 0: NO INVERT
		0,			//DHS INVERT 1: INVERT; 0: NO INVERT
		0,			//DEN INVERT 1: INVERT; 0; NO INVERT

		0,		//_43DHStartPos
		0,		//_43DHWidth

		32,                     // Display Horizontal Start Position
		1024,                   // Display Horizontal Width
		1056,                   // Display Horizontal End Position

		1152,                   // Display Horizontal Total Clock Number in One Display Line
		//1308,                   // Maxinum Display Horizontal Total Clock Number in One Display Line
		//1100,                   // Mininum Display Horizontal Total Clock Number in One Display Line

		12,                     // Display Vertical Start Position
		768,                    // Display Vertical Height
		780,                    // Display Vertical End Position

		864,                    // Display Vertical Total Line Number in One Frame
		//900,                    // Maxinum Display Vertical Total Line Number in One Frame
		//800,                    // Mininum Display Vertical Total Line Number in One Frame

		16,                     // Display H Sync Width
		3,                      // Display V Sync Height

		65,//94,                     // Typical Pixel Clock in MHz
		//100,                    // Maxinum Pixel Clock in MHz
		//60,                     // Mininum Pixel Clock in MHz

		930,						//H_freq_max
		200,						//H_freq_min
		890,						//V_freq_max
		490,						//V_freq_min
		0,							//DCLK_DELAY

		1229,//1485,       //PAL HTOTAL
		1200,//1390
 },

//02 LTM150XH005R 1024x768/ single 6 bit
{
		2,          // Panel Style  TTL\HZ\LVDS\RSDS: 0,1,2,3

		1,			//panel depth 1: 6 BIT; 0: 8BIT
		1,			//EO SWAP 1: SWAP; 0: NO SWAP
		0,			//RB SWAP 1: SWAP; 0: NO SWAP
		0,			//ML SWAP 1: SWAP; 0: NO SWAP

		0,			//Double port 1: double; 0: single
		0,			//RSDS GC SWAP 1: SWAP; 0: NO SWAP
		0,			//RSDS HL SWAP 1: SWAP; 0: NO SWAP
		0,			//RSDS PN SWAP 1: SWAP; 0: NO SWAP

		0,			//DHS MASK  0: The first DHS after DVS is active (Default); 1: The first DHS after DVS is inactive 
		1,//0,			//DVS INVERT 1: INVERT; 0: NO INVERT
		1,//0,			//DHS INVERT 1: INVERT; 0: NO INVERT
		0,			//DEN INVERT 1: INVERT; 0; NO INVERT

		0,		//_43DHStartPos
		0,		//_43DHWidth

		32,                     // Display Horizontal Start Position
		1024,                   // Display Horizontal Width
		1056,                   // Display Horizontal End Position

		1344,// 1305,                   // Display Horizontal Total Clock Number in One Display Line
		//1360,                   // Maxinum Display Horizontal Total Clock Number in One Display Line
		//1100,                   // Mininum Display Horizontal Total Clock Number in One Display Line

		16,//26,                     // Display Vertical Start Position
		768,                    // Display Vertical Height
		784,//794,                    // Display Vertical End Position

		820,                    // Display Vertical Total Line Number in One Frame
		//900,                    // Maxinum Display Vertical Total Line Number in One Frame
		//800,                    // Mininum Display Vertical Total Line Number in One Frame

		20,//16,                     // Display H Sync Width
		1,                      // Display V Sync Height

		65,//94,//85,                     // Typical Pixel Clock in MHz
		//100,                    // Maxinum Pixel Clock in MHz
		//60,                     // Mininum Pixel Clock in MHz

		930,						//H_freq_max
		200,						//H_freq_min
		890,						//V_freq_max
		490,						//V_freq_min
		0,							//DCLK_DELAY

		1380,//1485,       //PAL HTOTAL
		1380//1390
  },

//03 LTA104S1-L01 800x600 / single 6 bit
{
		2,                      // Panel Style  TTL\HZ\LVDS\RSDS: 0,1,2,3
		//0xc0,                   // Panel Configuration 18/24 bit 1/0 bit7; EO/RB/ML SWAP, doub/sgl 1/0, RSDS GC/HL/PN SWAP :BIT7~BIT0
		//0x06,					//display ctr DHS_MASK:BIT7, DVS/DHS/DEN invert: bit2,bit1, bit0

		1,			//panel depth 1: 6 BIT; 0: 8BIT
		1,			//EO SWAP 1: SWAP; 0: NO SWAP
		0,			//RB SWAP 1: SWAP; 0: NO SWAP
		0,			//ML SWAP 1: SWAP; 0: NO SWAP

		0,			//Double port 1: double; 0: single
		0,			//RSDS GC SWAP 1: SWAP; 0: NO SWAP
		0,			//RSDS HL SWAP 1: SWAP; 0: NO SWAP
		0,			//RSDS PN SWAP 1: SWAP; 0: NO SWAP

		0,			//DHS MASK  0: The first DHS after DVS is active (Default); 1: The first DHS after DVS is inactive 
		1,			//DVS INVERT 1: INVERT; 0: NO INVERT
		1,			//DHS INVERT 1: INVERT; 0: NO INVERT
		0,			//DEN INVERT 1: INVERT; 0; NO INVERT

		0,		//_43DHStartPos
		0,		//_43DHWidth

		60,//16,//60,                     // Display Horizontal Start Position
		800,                    // Display Horizontal Width
		860,//816,                    // Display Horizontal End Position

		1056,//960,                 	// Display Horizontal Total Clock Number in One Display Line
		//1060,                   // Maxinum Display Horizontal Total Clock Number in One Display Line
		//940,                    // Mininum Display Horizontal Total Clock Number in One Display Line

		15,                     // Display Vertical Start Position
		600,                    // Display Vertical Height
		615,                    // Display Vertical End Position

		625,//650,                    // Display Vertical Total Line Number in One Frame
		//850,                    // Maxinum Display Vertical Total Line Number in One Frame
		//640,                    // Mininum Display Vertical Total Line Number in One Frame

		16,                     // Display H Sync Width
		3,                      // Display V Sync Height

		45,//94,                     // Typical Pixel Clock in MHz
		//100,                    // Maxinum Pixel Clock in MHz
		//60,                     // Mininum Pixel Clock in MHz

		930,						//H_freq_max
		200,						//H_freq_min
		890,						//V_freq_max
		490,						//V_freq_min
		2,							//DCLK_DELAY

		1024,       //PAL HTOTAL
		1024
},

//04  1280x800 single 6 bit lvds
{
		2,                      // Panel Style  TTL\HZ\LVDS\RSDS: 0,1,2,3
		//0x48,                   // Panel Configuration 18/24 bit 1/0 bit7; EO/RB/ML SWAP, 
		//doub/sgl 1/0, RSDS GC/HL/PN SWAP :BIT7~BIT0
		//0x00,					//display ctr DHS_MASK:BIT7, DVS/DHS/DEN invert: bit2,bit1, bit0

		1,//0,			//panel depth 1: 6 BIT; 0: 8BIT
		1,			//EO SWAP 1: SWAP; 0: NO SWAP
		0,			//RB SWAP 1: SWAP; 0: NO SWAP
		0,			//ML SWAP 1: SWAP; 0: NO SWAP

		0,                  //Double port 1: double; 0: single
		0,			//RSDS GC SWAP 1: SWAP; 0: NO SWAP
		0,			//RSDS HL SWAP 1: SWAP; 0: NO SWAP
		0,			//RSDS PN SWAP 1: SWAP; 0: NO SWAP

		0,			//DHS MASK  0: The first DHS after DVS is active (Default); 1: The first DHS after DVS is inactive 
		1,//0,			//DVS INVERT 1: INVERT; 0: NO INVERT
		1,//0,			//DHS INVERT 1: INVERT; 0: NO INVERT
		0,			//DEN INVERT 1: INVERT; 0; NO INVERT

		0,		//_43DHStartPos
		0,		//_43DHWidth

		60,//32,                 // Display Horizontal Start Position
		1280,                       // Display Horizontal Width
		1340,//1312,                 // Display Horizontal End Position

		1500,//1440,                   // Display Horizontal Total Clock Number in One Display Line
		//_MAX_DH_TOTAL,                	 // Maxinum Display Horizontal Total Clock Number in One Display Line
		//_MIN_DH_TOTAL,                   // Mininum Display Horizontal Total Clock Number in One Display Line

		18,//16,                 // Display Vertical Start Position
		800,//1024,                       // Display Vertical Height
		818,//1040,                 // Display Vertical End Position

		835,//1072,                   // Display Vertical Total Line Number in One Frame
		//_MAX_DV_TOTAL,                   // Maxinum Display Vertical Total Line Number in One Frame
		//_MIN_DV_TOTAL,                   // Mininum Display Vertical Total Line Number in One Frame

		16,                    // Display H Sync Width
		3,                   // Display V Sync Height

		75,//135,               // Typical Pixel Clock in MHz
		// _MAX_PIXCEL_CLOCK,               // Maxinum Pixel Clock in MHz
		// _MIN_PIXCEL_CLOCK,               // Mininum Pixel Clock in MHz

		830,						//H_freq_max
		100,						//H_freq_min
		770,						//V_freq_max
		490,						//V_freq_min
		2,//0,							//DCLK_DELAY

		1400,//1485,       //PAL HTOTAL
		1392,//
},	   

// 05 2lvds 1400x1050 double 6 bit
{	
		2,                      // Panel Style  TTL\HZ\LVDS\RSDS: 0,1,2,3

		1,			//panel depth 1: 6 BIT; 0: 8BIT
		1,			//EO SWAP 1: SWAP; 0: NO SWAP
		0,			//RB SWAP 1: SWAP; 0: NO SWAP
		0,			//ML SWAP 1: SWAP; 0: NO SWAP

		1,			//Double port 1: double; 0: single
		0,			//RSDS GC SWAP 1: SWAP; 0: NO SWAP
		0,			//RSDS HL SWAP 1: SWAP; 0: NO SWAP
		0,			//RSDS PN SWAP 1: SWAP; 0: NO SWAP

		0,			//DHS MASK  0: The first DHS after DVS is active (Default); 1: The first DHS after DVS is inactive 
		0,			//DVS INVERT 1: INVERT; 0: NO INVERT
		0,			//DHS INVERT 1: INVERT; 0: NO INVERT
		0,			//DEN INVERT 1: INVERT; 0; NO INVERT

		0,		 	//_43DHStartPos
		0,			//_43DHWidth

		32,                     // Display Horizontal Start Position
		1400,//1440,                   // Display Horizontal Width
		1432,//1472,                   // Display Horizontal End Position

		1560,//1680,                   // Display Horizontal Total Clock Number in One Display Line
		//2044,                   // Maxinum Display Horizontal Total Clock Number in One Display Line
		//1380,                   // Mininum Display Horizontal Total Clock Number in One Display Line

		5,//17,//16,                     // Display Vertical Start Position
		1050,//900,                   // Display Vertical Height
		1055,//1067,//916,                   // Display Vertical End Position

		1080,//1100,//930,//940,                   // Display Vertical Total Line Number in One Frame
		//1272,                   // Maxinum Display Vertical Total Line Number in One Frame
		//1040,                   // Mininum Display Vertical Total Line Number in One Frame

		16,                     // Display H Sync Width
		3,                      // Display V Sync Height

		85,                    // Typical Pixel Clock in MHz
		//140,                    // Maxinum Pixel Clock in MHz
		//100,                    // Mininum Pixel Clock in MHz

		930,						//H_freq_max
		200,						//H_freq_min
		890,						//V_freq_max
		490,						//V_freq_min
		5,							//DCLK_DELAY

		1700,       //PAL HTOTAL
		1560
},

 //06 LVDS    1440X900 double 6 bit
{	
		2,          // Panel Style  TTL\HZ\LVDS\RSDS: 0,1,2,3

		0,			//panel depth 1: 6 BIT; 0: 8BIT
		1,			//EO SWAP 1: SWAP; 0: NO SWAP
		0,			//RB SWAP 1: SWAP; 0: NO SWAP
		0,			//ML SWAP 1: SWAP; 0: NO SWAP

		1,			//Double port 1: double; 0: single
		0,			//RSDS GC SWAP 1: SWAP; 0: NO SWAP
		0,			//RSDS HL SWAP 1: SWAP; 0: NO SWAP
		0,			//RSDS PN SWAP 1: SWAP; 0: NO SWAP

		0,			//DHS MASK  0: The first DHS after DVS is active (Default); 1: The first DHS after DVS is inactive 
		0,			//DVS INVERT 1: INVERT; 0: NO INVERT
		0,			//DHS INVERT 1: INVERT; 0: NO INVERT
		0,			//DEN INVERT 1: INVERT; 0; NO INVERT

		0,		//_43DHStartPos
		0,		//_43DHWidth

		32,                     // Display Horizontal Start Position
		1440,                   // Display Horizontal Width
		1472,                   // Display Horizontal End Position

		1680,                   // Display Horizontal Total Clock Number in One Display Line
		//2044,                   // Maxinum Display Horizontal Total Clock Number in One Display Line
		//1380,                   // Mininum Display Horizontal Total Clock Number in One Display Line

		17,//16,                     // Display Vertical Start Position
		900,                   // Display Vertical Height
		916,                   // Display Vertical End Position

		930,//940,                   // Display Vertical Total Line Number in One Frame
		//1272,                   // Maxinum Display Vertical Total Line Number in One Frame
		//1040,                   // Mininum Display Vertical Total Line Number in One Frame

		16,                     // Display H Sync Width
		3,                      // Display V Sync Height

		85,                    // Typical Pixel Clock in MHz
		//140,                    // Maxinum Pixel Clock in MHz
		//100,                    // Mininum Pixel Clock in MHz

		930,						//H_freq_max
		200,						//H_freq_min
		890,						//V_freq_max
		490,						//V_freq_min
		5,							//DCLK_DELAY

		1700, //PAL HTOTAL
		1680
},
	 
 // LVDS 07 HSD190MGW1 1440X900 double 8 bit
 {	
		2,          // Panel Style  TTL\HZ\LVDS\RSDS: 0,1,2,3

		0,			//panel depth 1: 6 BIT; 0: 8BIT
		1,			//EO SWAP 1: SWAP; 0: NO SWAP
		0,			//RB SWAP 1: SWAP; 0: NO SWAP
		0,			//ML SWAP 1: SWAP; 0: NO SWAP

		1,			//Double port 1: double; 0: single
		0,			//RSDS GC SWAP 1: SWAP; 0: NO SWAP
		0,			//RSDS HL SWAP 1: SWAP; 0: NO SWAP
		0,			//RSDS PN SWAP 1: SWAP; 0: NO SWAP

		0,			//DHS MASK  0: The first DHS after DVS is active (Default); 1: The first DHS after DVS is inactive 
		0,			//DVS INVERT 1: INVERT; 0: NO INVERT
		0,			//DHS INVERT 1: INVERT; 0: NO INVERT
		0,			//DEN INVERT 1: INVERT; 0; NO INVERT

		0,		//_43DHStartPos
		0,		//_43DHWidth

		32,                     // Display Horizontal Start Position
		1440,                   // Display Horizontal Width
		1472,                   // Display Horizontal End Position

		1680,                   // Display Horizontal Total Clock Number in One Display Line
		//2044,                   // Maxinum Display Horizontal Total Clock Number in One Display Line
		//1380,                   // Mininum Display Horizontal Total Clock Number in One Display Line

		17,//16,                     // Display Vertical Start Position
		900,                   // Display Vertical Height
		916,                   // Display Vertical End Position

		930,//940,                   // Display Vertical Total Line Number in One Frame
		//1272,                   // Maxinum Display Vertical Total Line Number in One Frame
		//1040,                   // Mininum Display Vertical Total Line Number in One Frame

		16,                     // Display H Sync Width
		3,                      // Display V Sync Height

		85,                    // Typical Pixel Clock in MHz
		//140,                    // Maxinum Pixel Clock in MHz
		//100,                    // Mininum Pixel Clock in MHz

		930,						//H_freq_max
		200,						//H_freq_min
		890,						//V_freq_max
		490,						//V_freq_min
		5,							//DCLK_DELAY

		1700, //PAL HTOTAL
		1680
},

 //08  lvds  640x480 
{
		2,                      // Panel Style  TTL\HZ\LVDS\RSDS: 0,1,2,3
		//0xc0,                   // Panel Configuration 18/24 bit 1/0 bit7; EO/RB/ML SWAP, doub/sgl 1/0, RSDS GC/HL/PN SWAP :BIT7~BIT0
		//0x06,					//display ctr DHS_MASK:BIT7, DVS/DHS/DEN invert: bit2,bit1, bit0

		1,			//panel depth 1: 6 BIT; 0: 8BIT
		1,			//EO SWAP 1: SWAP; 0: NO SWAP
		0,			//RB SWAP 1: SWAP; 0: NO SWAP
		0,			//ML SWAP 1: SWAP; 0: NO SWAP

		0,			//Double port 1: double; 0: single
		0,			//RSDS GC SWAP 1: SWAP; 0: NO SWAP
		0,			//RSDS HL SWAP 1: SWAP; 0: NO SWAP
		0,			//RSDS PN SWAP 1: SWAP; 0: NO SWAP

		0,			//DHS MASK  0: The first DHS after DVS is active (Default); 1: The first DHS after DVS is inactive 
		1,			//DVS INVERT 1: INVERT; 0: NO INVERT
		1,			//DHS INVERT 1: INVERT; 0: NO INVERT
		0,			//DEN INVERT 1: INVERT; 0; NO INVERT

		0,		//_43DHStartPos
		0,		//_43DHWidth

		32,//60,//75,                     // Display Horizontal Start Position
		640,//800,                   // Display Horizontal Width
		672,//700,//875,                   // Display Horizontal End Position

		750,//1056,                   // Display Horizontal Total Clock Number in One Display Line
		//1164,                   // Maxinum Display Horizontal Total Clock Number in One Display Line
		//924,                   // Mininum Display Horizontal Total Clock Number in One Display Line

		20,//25,                     // Display Vertical Start Position
		480,//600,                   // Display Vertical Height
		500,//505,//625,                   // Display Vertical End Position

		500,//650,                   // Display Vertical Total Line Number in One Frame
		//757,                   // Maxinum Display Vertical Total Line Number in One Frame
		//614,                   // Mininum Display Vertical Total Line Number in One Frame

		16,                     // Display H Sync Width
		1,                      // Display V Sync Height

		40,                    // Typical Pixel Clock in MHz
		//100,                    // Maxinum Pixel Clock in MHz
		//40,                    // Mininum Pixel Clock in MHz

		930,						//H_freq_max
		200,						//H_freq_min
		890,						//V_freq_max
		490,						//V_freq_min
		2,					      //DCLK_DELAY

		860,//1100,                     //PAL HTOTAL
		840,//1050
},
	 
//09        OUT 1280x1024 2lvds   6bit
 {	
		2,                      // Panel Style  TTL\HZ\LVDS\RSDS: 0,1,2,3
		//0x50,                   // Panel Configuration 18/24 bit 1/0 bit7; EO/RB/ML SWAP, doub/sgl 1/0, RSDS GC/HL/PN SWAP :BIT7~BIT0
		//0x80,					//display ctr DHS_MASK:BIT7, DVS/DHS/DEN invert: bit2,bit1, bit0

		1,			//panel depth 1: 6 BIT; 0: 8BIT
		1,			//EO SWAP 1: SWAP; 0: NO SWAP
		0,			//RB SWAP 1: SWAP; 0: NO SWAP
		0,			//ML SWAP 1: SWAP; 0: NO SWAP

		1,			//Double port 1: double; 0: single
		0,			//RSDS GC SWAP 1: SWAP; 0: NO SWAP
		0,			//RSDS HL SWAP 1: SWAP; 0: NO SWAP
		0,			//RSDS PN SWAP 1: SWAP; 0: NO SWAP

		1,			//DHS MASK  0: The first DHS after DVS is active (Default); 1: The first DHS after DVS is inactive 
		0,			//DVS INVERT 1: INVERT; 0: NO INVERT
		0,			//DHS INVERT 1: INVERT; 0: NO INVERT
		0,			//DEN INVERT 1: INVERT; 0; NO INVERT

		0,		//_43DHStartPos
		0,		//_43DHWidth

		32,                     // Display Horizontal Start Position
		1280,                   // Display Horizontal Width
		1280+32,                   // Display Horizontal End Position

		1444,//1024,//1080,//1050,                   // Display Horizontal Total Clock Number in One Display Line
		//1100,                   // Maxinum Display Horizontal Total Clock Number in One Display Line
		//900,                   // Mininum Display Horizontal Total Clock Number in One Display Line

		16,                     // Display Vertical Start Position
		1024,                    // Display Vertical Height
		1024+16,                    // Display Vertical End Position

		1200,                    // Display Vertical Total Line Number in One Frame
		//700,                    // Maxinum Display Vertical Total Line Number in One Frame
		//620,                    // Mininum Display Vertical Total Line Number in One Frame

		16,                     // Display H Sync Width
		2,                      // Display V Sync Height

		80,// 50,//38,//50,                     // Typical Pixel Clock in MHz
		//100,                    // Maxinum Pixel Clock in MHz
		//40,                     // Mininum Pixel Clock in MHz

		930,						//H_freq_max
		200,						//H_freq_min
		890,						//V_freq_max
		490,						//V_freq_min
		7,							//DCLK_DELAY

		1460,//                                //PAL HTOTAL
		1440,//1024,//1056
},
   
//10  lvds    1280x768/ single 8 bit
{		
		2,          // Panel Style  TTL\HZ\LVDS\RSDS: 0,1,2,3

		0,			//panel depth 1: 6 BIT; 0: 8BIT
		1,			//EO SWAP 1: SWAP; 0: NO SWAP
		0,			//RB SWAP 1: SWAP; 0: NO SWAP
		0,			//ML SWAP 1: SWAP; 0: NO SWAP

		0,			//Double port 1: double; 0: single
		0,			//RSDS GC SWAP 1: SWAP; 0: NO SWAP
		0,			//RSDS HL SWAP 1: SWAP; 0: NO SWAP
		0,			//RSDS PN SWAP 1: SWAP; 0: NO SWAP

		0,			//DHS MASK  0: The first DHS after DVS is active (Default); 1: The first DHS after DVS is inactive 
		0,			//DVS INVERT 1: INVERT; 0: NO INVERT
		0,			//DHS INVERT 1: INVERT; 0: NO INVERT
		0,			//DEN INVERT 1: INVERT; 0; NO INVERT

		0,		//_43DHStartPos
		0,		//_43DHWidth

		32,                     // Display Horizontal Start Position
		1280,                   // Display Horizontal Width
		1312,                   // Display Horizontal End Position

		1440,//1305,                   // Display Horizontal Total Clock Number in One Display Line
		//1360,                   // Maxinum Display Horizontal Total Clock Number in One Display Line
		//1100,                   // Mininum Display Horizontal Total Clock Number in One Display Line

		16,//26,                     // Display Vertical Start Position
		768,                    // Display Vertical Height
		784,//794,                    // Display Vertical End Position

		800,//820,                    // Display Vertical Total Line Number in One Frame
		//900,                    // Maxinum Display Vertical Total Line Number in One Frame
		//800,                    // Mininum Display Vertical Total Line Number in One Frame

		20,//16,                     // Display H Sync Width
		1,                      // Display V Sync Height

		65,//94,//85,                     // Typical Pixel Clock in MHz
		//100,                    // Maxinum Pixel Clock in MHz
		//60,                     // Mininum Pixel Clock in MHz

		930,						//H_freq_max
		200,						//H_freq_min
		890,						//V_freq_max
		490,						//V_freq_min
		0,							//DCLK_DELAY

		1480,//1485,                               //PAL HTOTAL
		1460//1390
},

//11 lvds        1280x768/ single 6 bit
{		
		2,          // Panel Style  TTL\HZ\LVDS\RSDS: 0,1,2,3

		1,			//panel depth 1: 6 BIT; 0: 8BIT
		1,			//EO SWAP 1: SWAP; 0: NO SWAP
		0,			//RB SWAP 1: SWAP; 0: NO SWAP
		0,			//ML SWAP 1: SWAP; 0: NO SWAP

		0,			//Double port 1: double; 0: single
		0,			//RSDS GC SWAP 1: SWAP; 0: NO SWAP
		0,			//RSDS HL SWAP 1: SWAP; 0: NO SWAP
		0,			//RSDS PN SWAP 1: SWAP; 0: NO SWAP

		0,			//DHS MASK  0: The first DHS after DVS is active (Default); 1: The first DHS after DVS is inactive 
		0,			//DVS INVERT 1: INVERT; 0: NO INVERT
		0,			//DHS INVERT 1: INVERT; 0: NO INVERT
		0,			//DEN INVERT 1: INVERT; 0; NO INVERT

		0,		//_43DHStartPos
		0,		//_43DHWidth

		32,                     // Display Horizontal Start Position
		1280,                   // Display Horizontal Width
		1312,                   // Display Horizontal End Position

		1440,//1305,                   // Display Horizontal Total Clock Number in One Display Line
		//1360,                   // Maxinum Display Horizontal Total Clock Number in One Display Line
		//1100,                   // Mininum Display Horizontal Total Clock Number in One Display Line

		16,//26,                     // Display Vertical Start Position
		768,                    // Display Vertical Height
		784,//794,                    // Display Vertical End Position

		800,//820,                    // Display Vertical Total Line Number in One Frame
		//900,                    // Maxinum Display Vertical Total Line Number in One Frame
		//800,                    // Mininum Display Vertical Total Line Number in One Frame

		20,//16,                     // Display H Sync Width
		1,                      // Display V Sync Height

		65,//94,//85,                     // Typical Pixel Clock in MHz
		//100,                    // Maxinum Pixel Clock in MHz
		//60,                     // Mininum Pixel Clock in MHz

		930,						//H_freq_max
		200,						//H_freq_min
		890,						//V_freq_max
		490,						//V_freq_min
		0,							//DCLK_DELAY

		1480,//1485,                               //PAL HTOTAL
		1460//1390
},

//12 lvds  1280x720 8bit 
{	
		2,          // Panel Style  TTL\HZ\LVDS\RSDS: 0,1,2,3

		0,			//panel depth 1: 6 BIT; 0: 8BIT
		1,			//EO SWAP 1: SWAP; 0: NO SWAP
		0,			//RB SWAP 1: SWAP; 0: NO SWAP
		0,			//ML SWAP 1: SWAP; 0: NO SWAP

		0,			//Double port 1: double; 0: single
		0,			//RSDS GC SWAP 1: SWAP; 0: NO SWAP
		0,			//RSDS HL SWAP 1: SWAP; 0: NO SWAP
		0,			//RSDS PN SWAP 1: SWAP; 0: NO SWAP

		1,			//DHS MASK  0: The first DHS after DVS is active (Default); 1: The first DHS after DVS is inactive 
		0,			//DVS INVERT 1: INVERT; 0: NO INVERT
		0,			//DHS INVERT 1: INVERT; 0: NO INVERT
		0,			//DEN INVERT 1: INVERT; 0; NO INVERT

		0,		//_43DHStartPos
		0,		//_43DHWidth

		32,                     // Display Horizontal Start Position
		1280,//1024,                   // Display Horizontal Width
		1312,//1056,                   // Display Horizontal End Position

		1340,//1152,                   // Display Horizontal Total Clock Number in One Display Line
		//1308,                   // Maxinum Display Horizontal Total Clock Number in One Display Line
		//1100,                   // Mininum Display Horizontal Total Clock Number in One Display Line

		16,//12,                     // Display Vertical Start Position
		720,//768,                    // Display Vertical Height
		736,//732,//780,                    // Display Vertical End Position

		801,//732,//864,                    // Display Vertical Total Line Number in One Frame
		//900,                    // Maxinum Display Vertical Total Line Number in One Frame
		//800,                    // Mininum Display Vertical Total Line Number in One Frame

		16,                     // Display H Sync Width
		3,                      // Display V Sync Height

		65,                     // Typical Pixel Clock in MHz
		//100,                    // Maxinum Pixel Clock in MHz
		//60,                     // Mininum Pixel Clock in MHz

		930,						//H_freq_max
		200,						//H_freq_min
		890,						//V_freq_max
		490,						//V_freq_min
		0,						//DCLK_DELAY

		1440,                               //PAL HTOTAL
		1370
 },

//13 lvds  1280x720 6bit 
{		
		2,          // Panel Style  TTL\HZ\LVDS\RSDS: 0,1,2,3

		1,			//panel depth 1: 6 BIT; 0: 8BIT
		1,			//EO SWAP 1: SWAP; 0: NO SWAP
		0,			//RB SWAP 1: SWAP; 0: NO SWAP
		0,			//ML SWAP 1: SWAP; 0: NO SWAP

		0,			//Double port 1: double; 0: single
		0,			//RSDS GC SWAP 1: SWAP; 0: NO SWAP
		0,			//RSDS HL SWAP 1: SWAP; 0: NO SWAP
		0,			//RSDS PN SWAP 1: SWAP; 0: NO SWAP

		1,			//DHS MASK  0: The first DHS after DVS is active (Default); 1: The first DHS after DVS is inactive 
		0,			//DVS INVERT 1: INVERT; 0: NO INVERT
		0,			//DHS INVERT 1: INVERT; 0: NO INVERT
		0,			//DEN INVERT 1: INVERT; 0; NO INVERT

		0,		//_43DHStartPos
		0,		//_43DHWidth

		32,                     // Display Horizontal Start Position
		1280,//1024,                   // Display Horizontal Width
		1312,//1056,                   // Display Horizontal End Position

		1340,//1152,                   // Display Horizontal Total Clock Number in One Display Line
		//1308,                   // Maxinum Display Horizontal Total Clock Number in One Display Line
		//1100,                   // Mininum Display Horizontal Total Clock Number in One Display Line

		16,//12,                     // Display Vertical Start Position
		720,//768,                    // Display Vertical Height
		736,//732,//780,                    // Display Vertical End Position

		801,//732,//864,                    // Display Vertical Total Line Number in One Frame
		//900,                    // Maxinum Display Vertical Total Line Number in One Frame
		//800,                    // Mininum Display Vertical Total Line Number in One Frame

		16,                     // Display H Sync Width
		3,                      // Display V Sync Height

		65,                     // Typical Pixel Clock in MHz
		//100,                    // Maxinum Pixel Clock in MHz
		//60,                     // Mininum Pixel Clock in MHz

		930,						//H_freq_max
		200,						//H_freq_min
		890,						//V_freq_max
		490,						//V_freq_min
		0,							//DCLK_DELAY

		1440,                               //PAL HTOTAL
		1360
},

//14  lvds 1280x854    single 6 bit
{
		2,                      // Panel Style  TTL\HZ\LVDS\RSDS: 0,1,2,3
		//0xc0,                   // Panel Configuration 18/24 bit 1/0 bit7; EO/RB/ML SWAP, doub/sgl 1/0, RSDS GC/HL/PN SWAP :BIT7~BIT0
		//0X00,					//display ctr DHS_MASK:BIT7, DVS/DHS/DEN invert: bit2,bit1, bit0

		1,			//panel depth 1: 6 BIT; 0: 8BIT
		1,			//EO SWAP 1: SWAP; 0: NO SWAP
		0,			//RB SWAP 1: SWAP; 0: NO SWAP
		0,			//ML SWAP 1: SWAP; 0: NO SWAP

		0,			//Double port 1: double; 0: single
		0,			//RSDS GC SWAP 1: SWAP; 0: NO SWAP
		0,			//RSDS HL SWAP 1: SWAP; 0: NO SWAP
		0,			//RSDS PN SWAP 1: SWAP; 0: NO SWAP

		0,			//DHS MASK  0: The first DHS after DVS is active (Default); 1: The first DHS after DVS is inactive 
		0,			//DVS INVERT 1: INVERT; 0: NO INVERT
		0,			//DHS INVERT 1: INVERT; 0: NO INVERT
		0,			//DEN INVERT 1: INVERT; 0; NO INVERT

		0,		//_43DHStartPos
		0,		//_43DHWidth

		32,//72,//60,                     // Display Horizontal Start Position
		1280,//1024,                   // Display Horizontal Width
		1312,//1056,//1096,//1084,                   // Display Horizontal End Position

		1400,//1344,//1305,//1300,//1280,                   // Display Horizontal Total Clock Number in One Display Line
		//1360,                   // Maxinum Display Horizontal Total Clock Number in One Display Line
		//1100,                   // Mininum Display Horizontal Total Clock Number in One Display Line

		16,//26,                     // Display Vertical Start Position
		854,//800,//768,                    // Display Vertical Height
		870,//784,//794,                    // Display Vertical End Position

		870,//800,//820,                    // Display Vertical Total Line Number in One Frame
		//900,                    // Maxinum Display Vertical Total Line Number in One Frame
		//800,                    // Mininum Display Vertical Total Line Number in One Frame

		20,//16,                     // Display H Sync Width
		1,                      // Display V Sync Height

		85,//85,                     // Typical Pixel Clock in MHz
		//100,                    // Maxinum Pixel Clock in MHz
		//60,                     // Mininum Pixel Clock in MHz

		930,						//H_freq_max
		200,						//H_freq_min
		890,						//V_freq_max
		490,						//V_freq_min
		0,						 //DCLK_DELAY


		1440,                               //PAL HTOTAL
		1380
},

//15  lvds 1152x768     single 6 bit
{
		2,                      // Panel Style  TTL\HZ\LVDS\RSDS: 0,1,2,3
		//0xc0,                   // Panel Configuration 18/24 bit 1/0 bit7; EO/RB/ML SWAP, doub/sgl 1/0, RSDS GC/HL/PN SWAP :BIT7~BIT0
		//0X00,					//display ctr DHS_MASK:BIT7, DVS/DHS/DEN invert: bit2,bit1, bit0

		1,			//panel depth 1: 6 BIT; 0: 8BIT
		1,			//EO SWAP 1: SWAP; 0: NO SWAP
		0,			//RB SWAP 1: SWAP; 0: NO SWAP
		0,			//ML SWAP 1: SWAP; 0: NO SWAP

		0,			//Double port 1: double; 0: single
		0,			//RSDS GC SWAP 1: SWAP; 0: NO SWAP
		0,			//RSDS HL SWAP 1: SWAP; 0: NO SWAP
		0,			//RSDS PN SWAP 1: SWAP; 0: NO SWAP

		0,			//DHS MASK  0: The first DHS after DVS is active (Default); 1: The first DHS after DVS is inactive 
		0,			//DVS INVERT 1: INVERT; 0: NO INVERT
		0,			//DHS INVERT 1: INVERT; 0: NO INVERT
		0,			//DEN INVERT 1: INVERT; 0; NO INVERT

		0,		//_43DHStartPos
		0,		//_43DHWidth

		32,                      // Display Horizontal Start Position
		1152,                   // Display Horizontal Width
		1184,                   // Display Horizontal End Position

		1356,                       // Display Horizontal Total Clock Number in One Display Line
		//1360,                   // Maxinum Display Horizontal Total Clock Number in One Display Line
		//1100,                   // Mininum Display Horizontal Total Clock Number in One Display Line

		16,//26,                     // Display Vertical Start Position
		768,                          // Display Vertical Height
		784,//794,          / Display Vertical End Position

		806,//800,//820,                    // Display Vertical Total Line Number in One Frame
		//900,                    // Maxinum Display Vertical Total Line Number in One Frame
		//800,                    // Mininum Display Vertical Total Line Number in One Frame

		16,                     // Display H Sync Width
		2,                      // Display V Sync Height

		75,//85,                     // Typical Pixel Clock in MHz
		//100,                    // Maxinum Pixel Clock in MHz
		//60,                     // Mininum Pixel Clock in MHz

		930,						//H_freq_max
		200,						//H_freq_min
		890,						//V_freq_max
		490,						//V_freq_min
		0,						 //DCLK_DELAY

		1420,                               //PAL HTOTAL
		1380
},

#else

// 00  lvds 1680x1050 double 8bit
{		
		2,          // Panel Style  TTL\HZ\LVDS\RSDS: 0,1,2,3

		0,			//panel depth 1: 6 BIT; 0: 8BIT
		1,			//EO SWAP 1: SWAP; 0: NO SWAP
		0,			//RB SWAP 1: SWAP; 0: NO SWAP
		0,			//ML SWAP 1: SWAP; 0: NO SWAP

		1,			//Double port 1: double; 0: single
		0,			//RSDS GC SWAP 1: SWAP; 0: NO SWAP
		0,			//RSDS HL SWAP 1: SWAP; 0: NO SWAP
		0,			//RSDS PN SWAP 1: SWAP; 0: NO SWAP

		0,			//DHS MASK  0: The first DHS after DVS is active (Default); 1: The first DHS after DVS is inactive 
		0,			//DVS INVERT 1: INVERT; 0: NO INVERT
		0,			//DHS INVERT 1: INVERT; 0: NO INVERT
		0,			//DEN INVERT 1: INVERT; 0; NO INVERT

		0,		//_43DHStartPos
		0,		//_43DHWidth

		32,//18,                     // Display Horizontal Start Position
		1680,//     1920,                   // Display Horizontal Width
		1712,//1698,//1700,//     1952,                   // Display Horizontal End Position

		1840,//1900,//1840,//1750,//  1900,//    2350,//2000,// 1152,                   // Display Horizontal Total Clock Number in One Display Line
		//1308,                   // Maxinum Display Horizontal Total Clock Number in One Display Line
		//1100,                   // Mininum Display Horizontal Total Clock Number in One Display Line

		16,//30,                     // Display Vertical Start Position
		1050,//    1200,// 768,                    // Display Vertical Height
		1066,//    1216,//1212,// 780,                    // Display Vertical End Position

		1120,//1272,//  1100,//   1500,//   864,                    // Display Vertical Total Line Number in One Frame
		//900,                    // Maxinum Display Vertical Total Line Number in One Frame
		//800,                    // Mininum Display Vertical Total Line Number in One Frame

		16,                     // Display H Sync Width
		3,                      // Display V Sync Height

		120,//  84,                     // Typical Pixel Clock in MHz
		//100,                    // Maxinum Pixel Clock in MHz
		//60,                     // Mininum Pixel Clock in MHz

		930,						//H_freq_max
		100,						//H_freq_min
		890,						//V_freq_max
		490,						//V_freq_min
		0,//0,//,//0,							//DCLK_DELAY

		1900,//                              //PAL HTOTAL
		1840,//	 
 },

// 01  lvds 1680x1050 double 6bit
{
		2,          // Panel Style  TTL\HZ\LVDS\RSDS: 0,1,2,3

		1,			//panel depth 1: 6 BIT; 0: 8BIT
		1,			//EO SWAP 1: SWAP; 0: NO SWAP
		0,			//RB SWAP 1: SWAP; 0: NO SWAP
		0,			//ML SWAP 1: SWAP; 0: NO SWAP

		1,			//Double port 1: double; 0: single
		0,			//RSDS GC SWAP 1: SWAP; 0: NO SWAP
		0,			//RSDS HL SWAP 1: SWAP; 0: NO SWAP
		0,			//RSDS PN SWAP 1: SWAP; 0: NO SWAP

		0,			//DHS MASK  0: The first DHS after DVS is active (Default); 1: The first DHS after DVS is inactive 
		0,			//DVS INVERT 1: INVERT; 0: NO INVERT
		0,			//DHS INVERT 1: INVERT; 0: NO INVERT
		0,			//DEN INVERT 1: INVERT; 0; NO INVERT

		0,		//_43DHStartPos
		0,		//_43DHWidth

		32,//18,                     // Display Horizontal Start Position
		1680,//     1920,                   // Display Horizontal Width
		1712,//1698,//1700,//     1952,                   // Display Horizontal End Position

		1840,//1900,//1840,//1750,//  1900,//    2350,//2000,// 1152,                   // Display Horizontal Total Clock Number in One Display Line
		//1308,                   // Maxinum Display Horizontal Total Clock Number in One Display Line
		//1100,                   // Mininum Display Horizontal Total Clock Number in One Display Line

		16,//30,                     // Display Vertical Start Position
		1050,//    1200,// 768,                    // Display Vertical Height
		1066,//    1216,//1212,// 780,                    // Display Vertical End Position

		1120,//1272,//  1100,//   1500,//   864,                    // Display Vertical Total Line Number in One Frame
		//900,                    // Maxinum Display Vertical Total Line Number in One Frame
		//800,                    // Mininum Display Vertical Total Line Number in One Frame

		16,                     // Display H Sync Width
		3,                      // Display V Sync Height

		120,//  84,                     // Typical Pixel Clock in MHz
		//100,                    // Maxinum Pixel Clock in MHz
		//60,                     // Mininum Pixel Clock in MHz

		930,						//H_freq_max
		100,						//H_freq_min
		890,						//V_freq_max
		490,						//V_freq_min
		0,//0,//,//0,							//DCLK_DELAY

		1900,//                              //PAL HTOTAL
		1840,//	 
},

//02  LTM240M2/ 1920X1200/ double 8 bit
{		
		2,          // Panel Style  TTL\HZ\LVDS\RSDS: 0,1,2,3

		1,			//panel depth 1: 6 BIT; 0: 8BIT
		1,			//EO SWAP 1: SWAP; 0: NO SWAP
		0,			//RB SWAP 1: SWAP; 0: NO SWAP
		0,			//ML SWAP 1: SWAP; 0: NO SWAP

		1,			//Double port 1: double; 0: single
		0,			//RSDS GC SWAP 1: SWAP; 0: NO SWAP
		0,			//RSDS HL SWAP 1: SWAP; 0: NO SWAP
		0,			//RSDS PN SWAP 1: SWAP; 0: NO SWAP

		1,			//DHS MASK  0: The first DHS after DVS is active (Default); 1: The first DHS after DVS is inactive 
		0,			//DVS INVERT 1: INVERT; 0: NO INVERT
		0,			//DHS INVERT 1: INVERT; 0: NO INVERT
		0,			//DEN INVERT 1: INVERT; 0; NO INVERT

		290,		//_43DHStartPos
		1600,		//_43DHWidth

		128,//  32,                     // Display Horizontal Start Position
		1920,                   // Display Horizontal Width
		2048,//   1952,                   // Display Horizontal End Position

		2100,//2100,//   2020,//2000,// 1152,                   // Display Horizontal Total Clock Number in One Display Line
		//1308,                   // Maxinum Display Horizontal Total Clock Number in One Display Line
		//1100,                   // Mininum Display Horizontal Total Clock Number in One Display Line

		16,//12,// 12,                     // Display Vertical Start Position
		1200,// 768,                    // Display Vertical Height
		1216,//1212,// 780,                    // Display Vertical End Position

		1500,//   864,                    // Display Vertical Total Line Number in One Frame
		//900,                    // Maxinum Display Vertical Total Line Number in One Frame
		//800,                    // Mininum Display Vertical Total Line Number in One Frame

		16,                     // Display H Sync Width
		3,                      // Display V Sync Height

		135,                      // Typical Pixel Clock in MHz
		//100,                    // Maxinum Pixel Clock in MHz
		//60,                     // Mininum Pixel Clock in MHz

		930,						//H_freq_max
		200,						//H_freq_min
		890,						//V_freq_max
		490,						//V_freq_min
		0,							//DCLK_DELAY

		2080,                             //PAL HTOTAL
		2080
},

 //03  LVDS 1920X1200/ double 6bit
{		
		2,          // Panel Style  TTL\HZ\LVDS\RSDS: 0,1,2,3

		1,			//panel depth 1: 6 BIT; 0: 8BIT
		1,			//EO SWAP 1: SWAP; 0: NO SWAP
		0,			//RB SWAP 1: SWAP; 0: NO SWAP
		0,			//ML SWAP 1: SWAP; 0: NO SWAP

		1,			//Double port 1: double; 0: single
		0,			//RSDS GC SWAP 1: SWAP; 0: NO SWAP
		0,			//RSDS HL SWAP 1: SWAP; 0: NO SWAP
		0,			//RSDS PN SWAP 1: SWAP; 0: NO SWAP

		1,			//DHS MASK  0: The first DHS after DVS is active (Default); 1: The first DHS after DVS is inactive 
		0,			//DVS INVERT 1: INVERT; 0: NO INVERT
		0,			//DHS INVERT 1: INVERT; 0: NO INVERT
		0,			//DEN INVERT 1: INVERT; 0; NO INVERT

		0,		//_43DHStartPos
		0,		//_43DHWidth

		32,                     // Display Horizontal Start Position
		1920,                   // Display Horizontal Width
		1952,                   // Display Horizontal End Position

		1980,//2000,// 1152,                   // Display Horizontal Total Clock Number in One Display Line
		//1308,                   // Maxinum Display Horizontal Total Clock Number in One Display Line
		//1100,                   // Mininum Display Horizontal Total Clock Number in One Display Line

		12,// 12,                     // Display Vertical Start Position
		1200,// 768,                    // Display Vertical Height
		1212,//1212,// 780,                    // Display Vertical End Position

		1500,//   864,                    // Display Vertical Total Line Number in One Frame
		//900,                    // Maxinum Display Vertical Total Line Number in One Frame
		//800,                    // Mininum Display Vertical Total Line Number in One Frame

		16,                     // Display H Sync Width
		3,                      // Display V Sync Height

		135,                     // Typical Pixel Clock in MHz
		//100,                    // Maxinum Pixel Clock in MHz
		//60,                     // Mininum Pixel Clock in MHz

		930,						//H_freq_max
		200,						//H_freq_min
		890,						//V_freq_max
		490,						//V_freq_min
		0,							//DCLK_DELAY

		2080,                             //PAL HTOTAL
		2080
},

//04  lvds 1600x1200  double 8 bit
{		
		2,                      // Panel Style  TTL\HZ\LVDS\RSDS: 0,1,2,3
		//0x48,                   // Panel Configuration 18/24 bit 1/0 bit7; EO/RB/ML SWAP, 
		                              //doub/sgl 1/0, RSDS GC/HL/PN SWAP :BIT7~BIT0
		//0x00,					//display ctr DHS_MASK:BIT7, DVS/DHS/DEN invert: bit2,bit1, bit0

		0,			//panel depth 1: 6 BIT; 0: 8BIT
		1,			//EO SWAP 1: SWAP; 0: NO SWAP
		0,			//RB SWAP 1: SWAP; 0: NO SWAP
		0,			//ML SWAP 1: SWAP; 0: NO SWAP

		1,			//Double port 1: double; 0: single
		0,			//RSDS GC SWAP 1: SWAP; 0: NO SWAP
		0,			//RSDS HL SWAP 1: SWAP; 0: NO SWAP
		0,			//RSDS PN SWAP 1: SWAP; 0: NO SWAP

		0,			//DHS MASK  0: The first DHS after DVS is active (Default); 1: The first DHS after DVS is inactive 
		0,			//DVS INVERT 1: INVERT; 0: NO INVERT
		0,			//DHS INVERT 1: INVERT; 0: NO INVERT
		0,			//DEN INVERT 1: INVERT; 0; NO INVERT

		0,		//_43DHStartPos
		0,		//_43DHWidth

		32,                 // Display Horizontal Start Position
		1600,//1280,                       // Display Horizontal Width
		1632,//1312,                 // Display Horizontal End Position

		1800,// 1700,//1600,//1440,                   // Display Horizontal Total Clock Number in One Display Line
		//_MAX_DH_TOTAL,                	 // Maxinum Display Horizontal Total Clock Number in One Display Line
		//_MIN_DH_TOTAL,                   // Mininum Display Horizontal Total Clock Number in One Display Line

		16,                 // Display Vertical Start Position
		1200,//1024,                       // Display Vertical Height
		1216,//1040,                 // Display Vertical End Position

		1220,//1070,                   // Display Vertical Total Line Number in One Frame
		//_MAX_DV_TOTAL,                   // Maxinum Display Vertical Total Line Number in One Frame
		//_MIN_DV_TOTAL,                   // Mininum Display Vertical Total Line Number in One Frame

		16,                    // Display H Sync Width
		3,                   // Display V Sync Height

		120,//90,//100,//135,               // Typical Pixel Clock in MHz
		// _MAX_PIXCEL_CLOCK,               // Maxinum Pixel Clock in MHz
		// _MIN_PIXCEL_CLOCK,               // Mininum Pixel Clock in MHz

		830,						//H_freq_max
		100,						//H_freq_min
		770,						//V_freq_max
		490,						//V_freq_min
		0,							//DCLK_DELAY

		1860,//                            //PAL HTOTAL
		1800,// 
},

//05  LVDS  1600x1200  double 6 bit
{		
		2,                      // Panel Style  TTL\HZ\LVDS\RSDS: 0,1,2,3
		//0x48,                   // Panel Configuration 18/24 bit 1/0 bit7; EO/RB/ML SWAP, 
			                       //doub/sgl 1/0, RSDS GC/HL/PN SWAP :BIT7~BIT0
		//0x00,			  //display ctr DHS_MASK:BIT7, DVS/DHS/DEN invert: bit2,bit1, bit0

		1,// 		//panel depth 1: 6 BIT; 0: 8BIT
		1,			//EO SWAP 1: SWAP; 0: NO SWAP
		0,			//RB SWAP 1: SWAP; 0: NO SWAP
		0,			//ML SWAP 1: SWAP; 0: NO SWAP

		1,			//Double port 1: double; 0: single
		0,			//RSDS GC SWAP 1: SWAP; 0: NO SWAP
		0,			//RSDS HL SWAP 1: SWAP; 0: NO SWAP
		0,			//RSDS PN SWAP 1: SWAP; 0: NO SWAP

		0,			//DHS MASK  0: The first DHS after DVS is active (Default); 1: The first DHS after DVS is inactive 
		0,			//DVS INVERT 1: INVERT; 0: NO INVERT
		0,			//DHS INVERT 1: INVERT; 0: NO INVERT
		0,			//DEN INVERT 1: INVERT; 0; NO INVERT

		0,		//_43DHStartPos
		0,		//_43DHWidth

		32,                 // Display Horizontal Start Position
		1600,//1280,                       // Display Horizontal Width
		1632,//1312,                 // Display Horizontal End Position

		1800,// 1700,//1600,//1440,                   // Display Horizontal Total Clock Number in One Display Line
		//_MAX_DH_TOTAL,                	 // Maxinum Display Horizontal Total Clock Number in One Display Line
		//_MIN_DH_TOTAL,                   // Mininum Display Horizontal Total Clock Number in One Display Line

		16,                 // Display Vertical Start Position
		1200,//1024,                       // Display Vertical Height
		1216,//1040,                 // Display Vertical End Position

		1220,//1070,                   // Display Vertical Total Line Number in One Frame
		//_MAX_DV_TOTAL,                   // Maxinum Display Vertical Total Line Number in One Frame
		//_MIN_DV_TOTAL,                   // Mininum Display Vertical Total Line Number in One Frame

		16,                    // Display H Sync Width
		3,                   // Display V Sync Height

		120,//90,//100,//135,               // Typical Pixel Clock in MHz
		// _MAX_PIXCEL_CLOCK,               // Maxinum Pixel Clock in MHz
		// _MIN_PIXCEL_CLOCK,               // Mininum Pixel Clock in MHz

		830,						//H_freq_max
		100,						//H_freq_min
		770,						//V_freq_max
		490,						//V_freq_min
		0,							//DCLK_DELAY

		1860,//                            //PAL HTOTAL
		1800,// 
},
	   
//06  1366x768    single 8 bit
{		
		2,                      // Panel Style  TTL\HZ\LVDS\RSDS: 0,1,2,3
		//0x48,                   // Panel Configuration 18/24 bit 1/0 bit7; EO/RB/ML SWAP, 
		                              //doub/sgl 1/0, RSDS GC/HL/PN SWAP :BIT7~BIT0
		//0x00,					//display ctr DHS_MASK:BIT7, DVS/DHS/DEN invert: bit2,bit1, bit0

		0,			//panel depth 1: 6 BIT; 0: 8BIT
		1,			//EO SWAP 1: SWAP; 0: NO SWAP
		0,			//RB SWAP 1: SWAP; 0: NO SWAP
		0,			//ML SWAP 1: SWAP; 0: NO SWAP

		0,//       		//Double port 1: double; 0: single
		0,			//RSDS GC SWAP 1: SWAP; 0: NO SWAP
		0,			//RSDS HL SWAP 1: SWAP; 0: NO SWAP
		0,			//RSDS PN SWAP 1: SWAP; 0: NO SWAP

		0,			//DHS MASK  0: The first DHS after DVS is active (Default); 1: The first DHS after DVS is inactive 
		0,			//DVS INVERT 1: INVERT; 0: NO INVERT
		0,			//DHS INVERT 1: INVERT; 0: NO INVERT
		0,			//DEN INVERT 1: INVERT; 0; NO INVERT

		0,		//_43DHStartPos
		0,		//_43DHWidth

		32,                 // Display Horizontal Start Position
		1366,//1280,                       // Display Horizontal Width
		1398,//1312,                 // Display Horizontal End Position

		1600,//1440,                   // Display Horizontal Total Clock Number in One Display Line
		//_MAX_DH_TOTAL,                	 // Maxinum Display Horizontal Total Clock Number in One Display Line
		//_MIN_DH_TOTAL,                   // Mininum Display Horizontal Total Clock Number in One Display Line

		16,                 // Display Vertical Start Position
		768,//1024,                       // Display Vertical Height
		784,//1040,                 // Display Vertical End Position

		806,//1072,                   // Display Vertical Total Line Number in One Frame
		//_MAX_DV_TOTAL,                   // Maxinum Display Vertical Total Line Number in One Frame
		//_MIN_DV_TOTAL,                   // Mininum Display Vertical Total Line Number in One Frame

		16,                    // Display H Sync Width
		3,                   // Display V Sync Height

		80,//135,               // Typical Pixel Clock in MHz
		// _MAX_PIXCEL_CLOCK,               // Maxinum Pixel Clock in MHz
		// _MIN_PIXCEL_CLOCK,               // Mininum Pixel Clock in MHz

		830,						//H_freq_max
		100,						//H_freq_min
		770,						//V_freq_max
		490,						//V_freq_min
		0,							//DCLK_DELAY

		1600,//                            //PAL HTOTAL
		1600,// 
 },	  
	  
//07  1366x768      single 6 bit   
{
		2,                      // Panel Style  TTL\HZ\LVDS\RSDS: 0,1,2,3
		//0x48,                   // Panel Configuration 18/24 bit 1/0 bit7; EO/RB/ML SWAP, 
				//doub/sgl 1/0, RSDS GC/HL/PN SWAP :BIT7~BIT0
		//0x00,					//display ctr DHS_MASK:BIT7, DVS/DHS/DEN invert: bit2,bit1, bit0

		1,			//panel depth 1: 6 BIT; 0: 8BIT
		1,			//EO SWAP 1: SWAP; 0: NO SWAP
		0,			//RB SWAP 1: SWAP; 0: NO SWAP
		0,			//ML SWAP 1: SWAP; 0: NO SWAP

		0,//       		//Double port 1: double; 0: single
		0,			//RSDS GC SWAP 1: SWAP; 0: NO SWAP
		0,			//RSDS HL SWAP 1: SWAP; 0: NO SWAP
		0,			//RSDS PN SWAP 1: SWAP; 0: NO SWAP

		0,			//DHS MASK  0: The first DHS after DVS is active (Default); 1: The first DHS after DVS is inactive 
		0,			//DVS INVERT 1: INVERT; 0: NO INVERT
		0,			//DHS INVERT 1: INVERT; 0: NO INVERT
		0,			//DEN INVERT 1: INVERT; 0; NO INVERT

		0,		//_43DHStartPos
		0,		//_43DHWidth

		32,                 // Display Horizontal Start Position
		1366,//1280,                       // Display Horizontal Width
		1398,//1312,                 // Display Horizontal End Position

		1600,//1440,                   // Display Horizontal Total Clock Number in One Display Line
		//_MAX_DH_TOTAL,                	 // Maxinum Display Horizontal Total Clock Number in One Display Line
		//_MIN_DH_TOTAL,                   // Mininum Display Horizontal Total Clock Number in One Display Line

		16,                 // Display Vertical Start Position
		768,//1024,                       // Display Vertical Height
		784,//1040,                 // Display Vertical End Position

		806,//1072,                   // Display Vertical Total Line Number in One Frame
		//_MAX_DV_TOTAL,                   // Maxinum Display Vertical Total Line Number in One Frame
		//_MIN_DV_TOTAL,                   // Mininum Display Vertical Total Line Number in One Frame

		16,                    // Display H Sync Width
		3,                   // Display V Sync Height

		80,//135,               // Typical Pixel Clock in MHz
		// _MAX_PIXCEL_CLOCK,               // Maxinum Pixel Clock in MHz
		// _MIN_PIXCEL_CLOCK,               // Mininum Pixel Clock in MHz

		830,						//H_freq_max
		100,						//H_freq_min
		770,						//V_freq_max
		490,						//V_freq_min
		0,							//DCLK_DELAY

		1600,//                            //PAL HTOTAL
		1600,// 
 },	  

 	//08 LTM150XH005R 1024x600/ single 6 bit
{		
		2,          // Panel Style  TTL\HZ\LVDS\RSDS: 0,1,2,3

		1,			//panel depth 1: 6 BIT; 0: 8BIT
		1,			//EO SWAP 1: SWAP; 0: NO SWAP
		0,			//RB SWAP 1: SWAP; 0: NO SWAP
		0,			//ML SWAP 1: SWAP; 0: NO SWAP

		0,			//Double port 1: double; 0: single
		0,			//RSDS GC SWAP 1: SWAP; 0: NO SWAP
		0,			//RSDS HL SWAP 1: SWAP; 0: NO SWAP
		0,			//RSDS PN SWAP 1: SWAP; 0: NO SWAP

		0,			//DHS MASK  0: The first DHS after DVS is active (Default); 1: The first DHS after DVS is inactive 
		1,//0,			//DVS INVERT 1: INVERT; 0: NO INVERT
		1,//0,			//DHS INVERT 1: INVERT; 0: NO INVERT
		0,			//DEN INVERT 1: INVERT; 0; NO INVERT

		0,		//_43DHStartPos
		0,		//_43DHWidth

		32,                     // Display Horizontal Start Position
		1024,                   // Display Horizontal Width
		1056,                   // Display Horizontal End Position

		1344,// 1305,                   // Display Horizontal Total Clock Number in One Display Line
		//1360,                   // Maxinum Display Horizontal Total Clock Number in One Display Line
		//1100,                   // Mininum Display Horizontal Total Clock Number in One Display Line

		16,//26,                     // Display Vertical Start Position
		600,                    // Display Vertical Height
		600+16,//794,                    // Display Vertical End Position

		640,                    // Display Vertical Total Line Number in One Frame
		//900,                    // Maxinum Display Vertical Total Line Number in One Frame
		//800,                    // Mininum Display Vertical Total Line Number in One Frame

		20,//16,                     // Display H Sync Width
		1,                      // Display V Sync Height

		65,//94,//85,                     // Typical Pixel Clock in MHz
		//100,                    // Maxinum Pixel Clock in MHz
		//60,                     // Mininum Pixel Clock in MHz

		930,						//H_freq_max
		200,						//H_freq_min
		890,						//V_freq_max
		490,						//V_freq_min
		0,							//DCLK_DELAY

		1350,//                            //PAL HTOTAL
		1320,// 
  },

// 09 lvds   8060 lvds  single 6bit
{	
		2,                      // Panel Style  TTL\HZ\LVDS\RSDS: 0,1,2,3
		//0x50,                   // Panel Configuration 18/24 bit 1/0 bit7; EO/RB/ML SWAP, doub/sgl 1/0, RSDS GC/HL/PN SWAP :BIT7~BIT0
		//0x06,					//display ctr DHS_MASK:BIT7, DVS/DHS/DEN invert: bit2,bit1, bit0

		0,			//panel depth 1: 6 BIT; 0: 8BIT
		1,			//EO SWAP 1: SWAP; 0: NO SWAP
		0,			//RB SWAP 1: SWAP; 0: NO SWAP
		1,			//ML SWAP 1: SWAP; 0: NO SWAP

		0,			//Double port 1: double; 0: single
		0,			//RSDS GC SWAP 1: SWAP; 0: NO SWAP
		0,			//RSDS HL SWAP 1: SWAP; 0: NO SWAP
		0,			//RSDS PN SWAP 1: SWAP; 0: NO SWAP

		0,			//DHS MASK  0: The first DHS after DVS is active (Default); 1: The first DHS after DVS is inactive 
		1,			//DVS INVERT 1: INVERT; 0: NO INVERT
		1,			//DHS INVERT 1: INVERT; 0: NO INVERT
		0,			//DEN INVERT 1: INVERT; 0; NO INVERT

		0,		//_43DHStartPos
		0,		//_43DHWidth

		70,                     // Display Horizontal Start Position
		800,                   // Display Horizontal Width
		870,                   // Display Horizontal End Position

		1056,                   // Display Horizontal Total Clock Number in One Display Line
		//1100,                   // Maxinum Display Horizontal Total Clock Number in One Display Line
		//900,                   // Mininum Display Horizontal Total Clock Number in One Display Line

		26,//20,                     // Display Vertical Start Position
		600,                    // Display Vertical Height
		626,//625,//620,                    // Display Vertical End Position

		626,//650,                    // Display Vertical Total Line Number in One Frame
		//700,                    // Maxinum Display Vertical Total Line Number in One Frame
		//620,                    // Mininum Display Vertical Total Line Number in One Frame

		20,                     // Display H Sync Width
		3,                      // Display V Sync Height

		45,                     // Typical Pixel Clock in MHz
		//100,                    // Maxinum Pixel Clock in MHz
		//40,                     // Mininum Pixel Clock in MHz

		930,						//H_freq_max
		200,						//H_freq_min
		890,						//V_freq_max
		490,						//V_freq_min
		2,							//DCLK_DELAY

		920,//                            //PAL HTOTAL
		900,// 
 },

//10 LVDS  TX18D11VM1CAA 800X480/ single 6 bit  7"
{		
		2,                      // Panel Style  TTL\HZ\LVDS\RSDS: 0,1,2,3

		0,			//panel depth 1: 6 BIT; 0: 8BIT
		1,			//EO SWAP 1: SWAP; 0: NO SWAP
		0,			//RB SWAP 1: SWAP; 0: NO SWAP
		1,			//ML SWAP 1: SWAP; 0: NO SWAP

		0,			//Double port 1: double; 0: single
		0,			//RSDS GC SWAP 1: SWAP; 0: NO SWAP
		0,			//RSDS HL SWAP 1: SWAP; 0: NO SWAP
		0,			//RSDS PN SWAP 1: SWAP; 0: NO SWAP

		0,			//DHS MASK  0: The first DHS after DVS is active (Default); 1: The first DHS after DVS is inactive 
		0,			//DVS INVERT 1: INVERT; 0: NO INVERT
		0,			//DHS INVERT 1: INVERT; 0: NO INVERT
		0,			//DEN INVERT 1: INVERT; 0; NO INVERT

		0,		//_43DHStartPos
		0,		//_43DHWidth

		54,//32,                     // Display Horizontal Start Position
		800,                   // Display Horizontal Width
		854, //1056,                   // Display Horizontal End Position

		1056,                   // Display Horizontal Total Clock Number in One Display Line
		//1308,                   // Maxinum Display Horizontal Total Clock Number in One Display Line
		//1100,                   // Mininum Display Horizontal Total Clock Number in One Display Line

		16,                     // Display Vertical Start Position
		480,                    // Display Vertical Height
		496,                    // Display Vertical End Position

		525,                    // Display Vertical Total Line Number in One Frame
		//1000,                    // Maxinum Display Vertical Total Line Number in One Frame
		//325,                    // Mininum Display Vertical Total Line Number in One Frame

		16,//16,                     // Display H Sync Width
		2,//3,                      // Display V Sync Height

		30,                     // Typical Pixel Clock in MHz
		//100,                    // Maxinum Pixel Clock in MHz
		//60,                     // Mininum Pixel Clock in MHz

		930,						//H_freq_max
		200,						//H_freq_min
		890,						//V_freq_max
		490,						//V_freq_min
		4,							//DCLK_DELAY

		1044,//                            //PAL HTOTAL
		1024,// 
},
	
 //11  LVDS   640X480 20"  single 8 bit
{
		2,          // Panel Style  TTL\HZ\LVDS\RSDS: 0,1,2,3

		0,			//panel depth 1: 6 BIT; 0: 8BIT
		1,			//EO SWAP 1: SWAP; 0: NO SWAP
		0,			//RB SWAP 1: SWAP; 0: NO SWAP
		1,			//ML SWAP 1: SWAP; 0: NO SWAP

		0,			//Double port 1: double; 0: single
		0,			//RSDS GC SWAP 1: SWAP; 0: NO SWAP
		0,			//RSDS HL SWAP 1: SWAP; 0: NO SWAP
		0,			//RSDS PN SWAP 1: SWAP; 0: NO SWAP

		0,			//DHS MASK  0: The first DHS after DVS is active (Default); 1: The first DHS after DVS is inactive 
		1,			//DVS INVERT 1: INVERT; 0: NO INVERT
		1,			//DHS INVERT 1: INVERT; 0: NO INVERT
		0,			//DEN INVERT 1: INVERT; 0; NO INVERT

		0,		//_43DHStartPos
		0,		//_43DHWidth

		30,//32,                       // Display Horizontal Start Position
		640,                     // Display Horizontal Width
		670,//1056,                     // Display Horizontal End Position

		711,//810,//780,                     // Display Horizontal Total Clock Number in One Display Line
		//1360,                     // Maxinum Display Horizontal Total Clock Number in One Display Line
		//1100,                     // Mininum Display Horizontal Total Clock Number in One Display Line

		16,                       // Display Vertical Start Position
		480,                      // Display Vertical Height
		496,                      // Display Vertical End Position

		515,//540,                      // Display Vertical Total Line Number in One Frame
		//900,                      // Maxinum Display Vertical Total Line Number in One Frame
		//800,                      // Mininum Display Vertical Total Line Number in One Frame

		12,//16,                       // Display H Sync Width
		4,//                     // Display V Sync Height

		25,//40,//20,                       // Typical Pixel Clock in MHz
		//100,                      // Maxinum Pixel Clock in MHz
		//60,                       // Mininum Pixel Clock in MHz

		930,						//H_freq_max
		200,						//H_freq_min
		890,						//V_freq_max
		490,						//V_freq_min
		2,							//DCLK_DELAY

		812,                             //PAL HTOTAL
		786, 
},	

#endif

};

//--------------------------------------------------
WORD code tVIDEO_TABLE_INPUT_INFO[][5] =
{
    // IHTotal, IHStart, IHWidth, IVStart, IVHeight
    {    864,     25,     666,     30,     270 },  // 50HZ 
    //{    858,     27,     640,     30,     224 },  // 60HZ
	{    858,     27,     640,     27,     226 },  // 60HZ
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
extern BYTE code tEDID_TABLE_VGA[9][128];
#endif
#if (_TMDS_SUPPORT)
extern BYTE code tEDID_TABLE_DVI[];
#endif

WORD code tVIDEO_TABLE_INPUT_INFO[][5];

extern PanelType xdata Panel;

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
