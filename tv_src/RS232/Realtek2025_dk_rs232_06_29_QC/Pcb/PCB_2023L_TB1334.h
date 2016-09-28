//----------------------------------------------------------------------------------------------------
// ID Code      : Pcb.h No.0001
// Update Note  : 
//
//----------------------------------------------------------------------------------------------------
#include "Rs232\Rs232.h"
#define _MCU_TYPE                       _RTD_2120      // _MYSON_MTV512,_RTD_2120,_MYSON_MTV312,_STK_6021
#define _KEY_TYPE                       _KEY_NORMAL    // _KEY_NORMAL,_KEY_ADC
#define _SCALER_TYPE                    _RTD2525L      // _RTD2533B,_RTD2553V,_RTD2546N,_RTD2525L,_RTD2528R,_RTD2023L,_RTD2023S,_RTD2023L_VB,_RTD2023S_VB
#define _HOST_INTERFACE                 _SERIAL_PORT   // _SERIAL_PORT,_PARALLEL_PORT

#define _RTD_XTAL                       _XTAL24000K    // _XTAL12000K,_XTAL24576K,_XTAL24000K
#define _MCU_XTAL                       _XTAL24000K

//--------------------------------------------------
// Definitions of IR Key ctrl
//--------------------------------------------------
#define _IR_ENABLE                      _ON

//--------------------------------------------------
// TMDS Supported
//--------------------------------------------------
#define _TMDS_SUPPORT                   _OFF
#define _VGA_SUPPORT                    _ON


//--------------------------------------------------
// Video Supported
//--------------------------------------------------
#define _VIDEO_SUPPORT                  _ON

#define _VIDEO_AV_SUPPORT               _ON
#define _VIDEO_SV_SUPPORT               _ON
#define _VIDEO_YUV_SUPPORT              _OFF  // Not ready
#define _VIDEO_TV_SUPPORT               _ON
#define _VIDEO_SCART_SUPPORT            _OFF
//--------------------------------------------------
// YPbPr Supported
//--------------------------------------------------
#define _YPBPR_SUPPORT                  _OFF

//----------------------------------------------------------------------------------------------------
// RTD2528R Advance Settings
//----------------------------------------------------------------------------------------------------
//--------------------------------------------------
// HDMI Supported
//--------------------------------------------------
#define _HDMI_SUPPORT                   _OFF


//--------------------------------------------------
// DAC Chip Supported
//--------------------------------------------------
#if(_HDMI_SUPPORT == _ON)
#define _DAC_SUPPORT                    _ON
#else
#define _DAC_SUPPORT                    _OFF
#endif


//--------------------------------------------------
// On Chip EDID Supported
//--------------------------------------------------
#if(_HDMI_SUPPORT == _ON)
#define _HDMI_EDID                      _OFF
#else
#define _HDMI_EDID                      _OFF
#endif

//--------------------------------------------------
// Definitions of MAIN_TYPE
//--------------------------------------------------
#define _MAIN_TYPE_DISABLE              0   //000: Disable All Output Pins (PWM, TCON, SDRAM, Display, etc.) 
#define _MAIN_TYPE_1                    1   //001: Configure IC as MCM128 with internal 1Mx16 SDRAM0.
#define _MAIN_TYPE_2                    2   //010: Configure IC as QFP128. No SDRAM is in use.
#define _MAIN_TYPE_3                    3   //011: Configure IC as QFP128. Only SDRAM1 (1Mx16) is in use.
#define _MAIN_TYPE_4                    4   //100: Configure IC as QFP128. Both SDRAM0 and SDRAM1 are in use.
#define _MAIN_TYPE_5                    5   //101: Reserved. (QFP208 w/o SDRAM)
#define _MAIN_TYPE_6                    6   //110: Configure IC as QFP208. Only SDRAM1 (1Mx16 or 2Mx32) is in use.
#define _MAIN_TYPE_7                    7   //111: Configure IC as QFP208. Both SDRAM0 and SDRAM1 are in use.

#define _MAIN_TYPE                      _MAIN_TYPE_1


//--------------------------------------------------
// Over Driving Supported
//--------------------------------------------------
#define _OD_SUPPORT                     _OFF


//--------------------------------------------------
// Frame Rate Conversion Supported
//--------------------------------------------------
#define _FRC_SUPPORT                    _OFF


//--------------------------------------------------
// Field Merge Supported (Need to definition when _FRC_SUPPORT = _ON)
//--------------------------------------------------
#define _FIELD_MERGE_SUPPORT            _OFF


//--------------------------------------------------
// Maximum Panel Frame Rate (Need to definition when _FRC_SUPPORT = _ON)
//--------------------------------------------------
#define _PANEL_MAX_FRAME_RATE           600     // Unit in 0.1 HZ


//--------------------------------------------------
// Memory Config
//--------------------------------------------------
#define _NO_MEMORY                      0
#define _1M_16BIT_1PCE                  1
#define _1M_16BIT_2PCE                  2
#define _2M_32BIT_1PCE                  3
#define _2M_32BIT_2PCE                  4

#define _MEMORY_CONFIG                  _NO_MEMORY


//--------------------------------------------------
// Memory Size
//--------------------------------------------------
#define _MEMORY_16MB                    16
#define _MEMORY_32MB                    32
#define _MEMORY_64MB                    64
#define _MEMORY_128MB                   128


//--------------------------------------------------
// Config of Memory Bus Width & Memory Size
//--------------------------------------------------
#if(_MEMORY_CONFIG == _NO_MEMORY)
#define _MEMORY_BUS_WIDTH               0
#define _MEMORY_SIZE                    0
#define _MEMORY_BIT_NUM                 0
#elif(_MEMORY_CONFIG == _1M_16BIT_1PCE)
#define _MEMORY_BUS_WIDTH               16
#define _MEMORY_SIZE                    _MEMORY_16MB
#define _MEMORY_BIT_NUM                 16
#elif(_MEMORY_CONFIG == _1M_16BIT_2PCE)
#define _MEMORY_BUS_WIDTH               32
#define _MEMORY_SIZE                    _MEMORY_32MB
#define _MEMORY_BIT_NUM                 16
#elif(_MEMORY_CONFIG == _2M_32BIT_1PCE)
#define _MEMORY_BUS_WIDTH               32
#define _MEMORY_SIZE                    _MEMORY_64MB
#define _MEMORY_BIT_NUM                 32
#elif(_MEMORY_CONFIG == _2M_32BIT_2PCE)
#define _MEMORY_BUS_WIDTH               64
#define _MEMORY_SIZE                    _MEMORY_128MB
#define _MEMORY_BIT_NUM                 32
#endif


//--------------------------------------------------
// Memory Speed
//--------------------------------------------------
#define _100MHZ                         100
#define _120MHZ                         120
#define _166MHZ                         166
#define _171MHZ                         171
#define _200MHZ                         200

#define _MEMORY_SPEED                   _166MHZ


//--------------------------------------------------
// Definitions of MPLL N Code
//--------------------------------------------------
#define _MPLL_N_CODE                    16


//--------------------------------------------------
// Set MClk Spread Spectrum Range
//--------------------------------------------------
#define _MCLK_SPREAD_RANGE              0   //0~15, 0¡÷disable, 15¡÷7.5%


//--------------------------------------------------
// Compress On or Off
//--------------------------------------------------
#define _OD_COMPRESSION                 _OFF

#define _OD_RES_6BIT                    6
#define _OD_RES_5BIT                    5

#define _OD_BIT_RESOLUTION              _OD_RES_6BIT


//--------------------------------------------------
// Definitions of SDRAM Latency
//--------------------------------------------------
#define _ROW_WR_DELAY                   2  //0~1:Resered, 2~5:2~5 MCLK, 6~7:Resered
#define _ROW_RD_DELAY                   2  //0~1:Resered, 2~5:2~5 MCLK, 6~7:Resered

#define _SDR_ROW_DELAY                  ((_ROW_WR_DELAY << 3) | (_ROW_RD_DELAY))

#define _SDR_COL_DELAY                  ((2 << 5) | 0x04)  //0~1:Resered, 2~3:2~3 MCLK, 4~7:Resered


//--------------------------------------------------
// Definitions of Clock/Latch Delay
//--------------------------------------------------
#define _CLOCK_INV                      0x00  //Bit3:Inversion bit
#define _CLOCK_DELAY                    0     //Bit0~2:0~7 CLK Delay.

#define _SDR_CLOCK_DELAY                (_CLOCK_INV | _CLOCK_DELAY)

//--------------------------------------------------
// Video Supported
//--------------------------------------------------
#define _VIDEO_OUT_SUPPORT              _OFF


//--------------------------------------------------
// Video Output Selection
//--------------------------------------------------
#define _VIDEO_16_OUT                   0
#define _VIDEO_24_OUT                   1

#define _VIDEO_OUT                      _VIDEO_16_OUT


//--------------------------------------------------
// Audio PLL Lock Mode
//--------------------------------------------------
#define _HARDWARE_TRACKING              0
#define _N_CTS                          1

#define _AUDIO_LOCK_MODE                _N_CTS


//--------------------------------------------------

//-------------------------------------------------
// Defination for normal input source
//-------------------------------------------------
/*
_SOURCE_VGA,      _SOURCE_DVI
_SOURCE_VIDEO_AV, _SOURCE_VIDEO_SV
_SOURCE_VIDEO_TV, _SOURCE_VIDEO_YUV
_SOURCE_YPBPR
*/
#define _NORMAL_SOURCE                  _SOURCE_VGA


//--------------------------------------------------
// Definations of Input Port Types
//--------------------------------------------------
/*
    _NO_PORT,                                           --> No port
    _DSUB_A0_PORT,  _DSUB_A1_PORT,                      --> Dsub input port
    _DVI_PORT,      _DVI_I_A0_PORT,     _DVI_I_A1_PORT, --> DVI input port
    _VIDEO8_PORT,   _VIDEO_2ND_ADC_PORT,                --> Video input port
    _YPBPR_A0_PORT, _YPBPR_A1_PORT                      --> YPbPr input port
    _HDMI_PORT,                                         --> HDMI input port
*/
#define _SOURCE_VGA_PORT_TYPE           _DSUB_A0_PORT
#define _SOURCE_DVI_PORT_TYPE           _DVI_PORT
#define _SOURCE_HDMI_PORT_TYPE          _HDMI_PORT
#define _SOURCE_VIDEO_PORT_TYPE       _DSUB_A1_PORT//  _VIDEO8_PORT
#define _SOURCE_YPBPR_PORT_TYPE         _YPBPR_A0_PORT

//-------------------------------------------------
// Definitions for Scaler video input port
//-------------------------------------------------   
#define _VIDEO8_MSB_LSB_SWAP_ENABLE     0x80
#define _VIDEO8_MSB_LSB_SWAP_DISABLE    0x00

#define _VIDEO8_MSB_LSB_SWAP            _VIDEO8_MSB_LSB_SWAP_DISABLE//_VIDEO8_MSB_LSB_SWAP_ENABLE

// For RTD2525L/RTD2553V
#define _VIDEO_IN                       _VIDEO_8_IN    // _VIDEO_8_IN, _VIDEO_16_IN

//-------------------------------------------------
// Definitions for backlight PWM
//-------------------------------------------------
/*
_SCALAR_PWM0, _SCALAR_PWM1, _SCALAR_PWM2
// For MCU
_MCU_PWM0,    _MCU_PWM1,    _MCU_PWM2,   _MCU_PWM3
_MCU_PWM4,    _MCU_PWM5 
*/
#define _BACKLIGHT_PWM                  _MCU_PWM1
#define _BACKLIGHT_PWM_INVERSE          _ENABLE        // _ENABLE,  _DISABLE

//--------------------------------------------------
// Definitions for GPIO Control
//--------------------------------------------------
#define _PANEL_ON                       1   // Power on  state for LCD panel 
#define _PANEL_OFF                      0   // Power off state for LCD panel

#define _LIGHT_ON                       0   // Power on  state for backlight inverter
#define _LIGHT_OFF                      1   // Power off state for backlight inverter

#define _VDC_ON                         0   // Power on  state for video decoder
#define _VDC_OFF                        1   // Power off state for video decoder

#define _LVDS_ON                        0   // Power on  state for LVDS Tx
#define _LVDS_OFF                       1   // Power off state for LVDS Tx

//--------------------------------------------------
// Pin Share
//--------------------------------------------------
#if (_SCALER_TYPE == _RTD2553V)
#define _PIN_V16_FUNC                   (1 & 0x01)     // 0 ~ 1 (0: V16_Y7 ~ V16_Y0, 1: normal output)
#define _PIN_48                         (1 & 0x03)     // 0 ~ 3

#define _PIN_42                         (2 & 0x03)     // 0 ~ 3
#define _PIN_43                         (1 & 0x01)     // 0 ~ 1
#define _PIN_44                         (2 & 0x03)     // 0 ~ 3
#define _PIN_45                         (2 & 0x03)     // 0 ~ 3

#define _PIN_3                          (2 & 0x03)     // 0 ~ 3
#define _PIN_4                          (2 & 0x03)     // 0 ~ 3
#define _PIN_110                        (1 & 0x01)     // 0 ~ 1
#define _PIN_111                        (3 & 0x03)     // 0 ~ 3

#define _PIN_49                         (0 & 0x03)     // 0 ~ 3
#define _PIN_52_53                      (0 & 0x01)     // 0 ~ 1
#define _PIN_54                         (0 & 0x03)     // 0 ~ 3
#define _PIN_55_56_57                   (0 & 0x01)     // 0 ~ 1
#define _PIN_50_51                      (0 & 0x01)     // 0 ~ 1

#define _PIN_122                        (0 & 0x01)     // 0 ~ 1
#define _PIN_112_113_114                (3 & 0x03)     // 0 ~ 3
#define _PIN_115_118_119                (1 & 0x01)     // 0 ~ 1
#define _PIN_120_121                    (3 & 0x03)     // 0 ~ 3

#elif(_SCALER_TYPE == _RTD2546N)

#define _PIN_V16_FUNC                   (1 & 0x01)  // 0 ~ 1 (0: V16_Y7 ~ V16_Y0, 1: normal output)
#define _PIN_53                         (1 & 0x03)  // 0 ~ 3
 
#define _PIN_44                         (2 & 0x03)  // 0 ~ 3
#define _PIN_45                         (1 & 0x01)  // 0 ~ 1
#define _PIN_46                         (2 & 0x03)  // 0 ~ 3
#define _PIN_47                         (2 & 0x03)  // 0 ~ 3
 
#define _PIN_4                          (1 & 0x03)  // 0 ~ 3
#define _PIN_5                          (1 & 0x03)  // 0 ~ 3
 
#define _PIN_54                         (0 & 0x03)  // 0 ~ 3
#define _PIN_55_56                      (0 & 0x01)  // 0 ~ 1
 
#define _PIN_113_114                    (2 & 0x03)  // 0 ~ 3

#elif(_SCALER_TYPE == _RTD2525L)

//--------------------------------------------------
// RTD2525L Pin Share
//--------------------------------------------------
#define _PIN_43                         (0 & 0x03)     // 0 ~ 3
#define _PIN_44                         (1 & 0x01)     // 0 ~ 1

#elif(_SCALER_TYPE == _RTD2528R)

//--------------------------------------------------
// RTD2549T Pin Share 
//--------------------------------------------------

#if(_VIDEO_SUPPORT == _OFF)
#define _PIN_V8_ENABLE              (0 & 0x01)  // 0 ~ 1 (0: Disable, 1: Enable) Pin 42~52 for Video-8 Input
#define _PIN_V16_ENABLE             (0 & 0x01)  // 0 ~ 1 (0: Disable, 1: Enable) Pin 31~52 for Video-16 Input 
#define _PIN_42                     (0 & 0x01)  // 0 ~ 1 (0: Hi-Z, 1: PWM0) Effective only if _PIN_V8_ENABLE = Disable and _PIN_V16_ENABLE = Disable
#define _PIN_43                     (0 & 0x01)  // 0 ~ 1 (0: Hi-Z, 1: PWM1) Effective only if _PIN_V8_ENABLE = Disable and _PIN_V16_ENABLE = Disable
#define _PIN_44                     (0 & 0x01)  // 0 ~ 1 (0: Hi-Z, 1: PWM2) Effective only if _PIN_V8_ENABLE = Disable and _PIN_V16_ENABLE = Disable
#define _PIN_48                     (0 & 0x03)  // 0 ~ 3 (0: Hi-Z, 1: TCON0, 2: TCON1, 3: Reserved) Effective only if _PIN_V8_ENABLE = Disable and _PIN_V16_ENABLE = Disable
#define _PIN_49                     (0 & 0x03)  // 0 ~ 3 (0: Hi-Z, 1: TCON4, 2: TCON5, 3: Reserved) Effective only if _PIN_V8_ENABLE = Disable and _PIN_V16_ENABLE = Disable
#define _PIN_50                     (0 & 0x03)  // 0 ~ 3 (0: Hi-Z, 1: TCON7, 2: TCON8, 3: Reserved) Effective only if _PIN_V8_ENABLE = Disable and _PIN_V16_ENABLE = Disable
#define _PIN_51                     (0 & 0x03)  // 0 ~ 3 (0: Hi-Z, 1: TCON9, 2: TCON10, 3: Reserved) Effective only if _PIN_V8_ENABLE = Disable and _PIN_V16_ENABLE = Disable
#define _PIN_52                     (0 & 0x03)  // 0 ~ 3 (0: Hi-Z, 1: TCON12, 2: TCON13, 3: Reserved) Effective only if _PIN_V8_ENABLE = Disable and _PIN_V16_ENABLE = Disable
#else

#if(_VIDEO_IN == _VIDEO_8_IN)
#define _PIN_V8_ENABLE              (1 & 0x01)  // 0 ~ 1 (0: Disable, 1: Enable) Pin 42~52 for Video-8 Input
#define _PIN_V16_ENABLE             (0 & 0x01)  // 0 ~ 1 (0: Disable, 1: Enable) Pin 31~52 for Video-16 Input 
#endif

#if(_VIDEO_IN == _VIDEO_16_IN)
#define _PIN_V8_ENABLE              (0 & 0x01)  // 0 ~ 1 (0: Disable, 1: Enable) Pin 42~52 for Video-8 Input
#define _PIN_V16_ENABLE             (1 & 0x01)  // 0 ~ 1 (0: Disable, 1: Enable) Pin 31~52 for Video-16 Input 
#endif
#endif

#define _PIN_53                     (3 & 0x03)  // 0 ~ 3 (0: Hi-Z, 1: PWM0, 2: TCON2, 3: MCLK(I2S))
#define _PIN_54                     (3 & 0x03)  // 0 ~ 3 (0: Hi-Z, 1: PWM1, 2: TCON3, 3: SCLK(I2S))
#define _PIN_55                     (3 & 0x03)  // 0 ~ 3 (0: Hi-Z, 1: PWM2, 2: TCON11, 3: WS(I2S))
#define _PIN_56                     (3 & 0x03)  // 0 ~ 3 (0: Hi-Z, 1: TCON6, 2: TCON7, 3: SD0(I2S)/SPDIF3(Selected By CR8E-04[1:0]))
#define _PIN_57                     (3 & 0x03)  // 0 ~ 3 (0: Hi-Z, 1: TCON0, 2: TCON9, 3: SD1(I2S)/SPDIF2(Selected By CR8E-04[1:0]))
#define _PIN_58                     (3 & 0x03)  // 0 ~ 3 (0: Hi-Z, 1: TCON1, 2: TCON8, 3: SD2(I2S)/SPDIF1(Selected By CR8E-04[1:0]))
#define _PIN_59                     (3 & 0x03)  // 0 ~ 3 (0: Hi-Z, 1: TCON2, 2: TCON12, 3: SD3(I2S)/SPDIF0(Selected By CR8E-04[1:0]))
#define _PIN_56to59                 (0 & 0x03)  // 0 ~ 3 (0: SD0/SD1/SD2/SD3,
                                                //        1: SD0/SD1/SD2/SPDIF0
                                                //        2: SD0/SPDIF2/SPDIF1/SPDIF0
                                                //        3: SPDIF3/SPDIF2/SPDIF1/SPDIF0
#define _PIN_62to65                 (2 & 0x03)  // 0 ~ 3 (0: ALL Hi-Z,
                                                //        1: Pin62(Hi-Z),Pin63~Pin65(PWM0~3)
                                                //        2: Pin62(SPDIF0),Pin63~Pin65(SPDIF1~3)
                                                //        3: Pin62(SPDIF0),Pin63~Pin65(PWM0~3)
#define _PIN_187                    (0 & 0x03)  // 0 ~ 3 (0: GPO(Controlled By CR8E-[0C][0D]), 1: TCON0, 2: TCON1, 3: ECLK(For TTL))
#define _PIN_188                    (0 & 0x03)  // 0 ~ 3 (0: GPO(Controlled By CR8E-[0C][0D]), 1: TCON1, 2: TCON2, 3: DENA(For TTL))
#define _PIN_189                    (0 & 0x03)  // 0 ~ 3 (0: GPO(Controlled By CR8E-[0C][0D]), 1: TCON3, 2: TCON4, 3: DHS(For TTL))
#define _PIN_190                    (0 & 0x03)  // 0 ~ 3 (0: GPO(Controlled By CR8E-[0C][0D]), 1: TCON5, 2: TCON6, 3: DVS(For TTL))
#define _PIN_194                    (0 & 0x03)  // 0 ~ 3 (0: GPO(Controlled By CR8E-[0C][0D]), 1: TCON7, 2: TCON8, 3: OCLK(For TTL))
#define _PIN_195                    (0 & 0x03)  // 0 ~ 3 (0: GPO(Controlled By CR8E-[0C][0D]), 1: TCON8, 2: TCON9, 3: PWM2)
#define _PIN_196                    (0 & 0x03)  // 0 ~ 3 (0: GPO(Controlled By CR8E-[0C][0D]), 1: TCON10, 2: TCON11, 3: PWM1)
#define _PIN_197                    (0 & 0x03)  // 0 ~ 3 (0: GPO(Controlled By CR8E-[0C][0D]), 1: TCON12, 2: TCON13, 3: PWM0)

#define _PIN_187_EN                 (0 & 0x01)  // 0 ~ 1 (0: Hi-Z, 1: Output Level Controlled By CR8E-[0D])
#define _PIN_188_EN                 (0 & 0x01)  // 0 ~ 1 (0: Hi-Z, 1: Output Level Controlled By CR8E-[0D])
#define _PIN_189_EN                 (0 & 0x01)  // 0 ~ 1 (0: Hi-Z, 1: Output Level Controlled By CR8E-[0D])
#define _PIN_190_EN                 (0 & 0x01)  // 0 ~ 1 (0: Hi-Z, 1: Output Level Controlled By CR8E-[0D])
#define _PIN_194_EN                 (0 & 0x01)  // 0 ~ 1 (0: Hi-Z, 1: Output Level Controlled By CR8E-[0D])
#define _PIN_195_EN                 (0 & 0x01)  // 0 ~ 1 (0: Hi-Z, 1: Output Level Controlled By CR8E-[0D])
#define _PIN_196_EN                 (0 & 0x01)  // 0 ~ 1 (0: Hi-Z, 1: Output Level Controlled By CR8E-[0D])
#define _PIN_197_EN                 (0 & 0x01)  // 0 ~ 1 (0: Hi-Z, 1: Output Level Controlled By CR8E-[0D])

#define _PIN_187_LEVEL              (0 & 0x01)  // 0 ~ 1 (0: Low, 1: High)
#define _PIN_188_LEVEL              (0 & 0x01)  // 0 ~ 1 (0: Low, 1: High)
#define _PIN_189_LEVEL              (0 & 0x01)  // 0 ~ 1 (0: Low, 1: High)
#define _PIN_190_LEVEL              (0 & 0x01)  // 0 ~ 1 (0: Low, 1: High)
#define _PIN_194_LEVEL              (0 & 0x01)  // 0 ~ 1 (0: Low, 1: High)
#define _PIN_195_LEVEL              (0 & 0x01)  // 0 ~ 1 (0: Low, 1: High)
#define _PIN_196_LEVEL              (0 & 0x01)  // 0 ~ 1 (0: Low, 1: High)
#define _PIN_197_LEVEL              (0 & 0x01)  // 0 ~ 1 (0: Low, 1: High)

#define _PIN_204to205               (0 & 0x03)  // 0 ~ 3 (0: DDC2SDA/DDC2SCL(Open Drain I/O), 1: PWM1/PWM0, 2: TCON6/TCON4, 3: Reserved)
#define _PIN_198                    (0 & 0x03)  // 0 ~ 3 (0: Hi-Z, 1: PWM2, 2: TCON12, 3: Reserved)#Power On Latch
#define _PIN_199                    (0 & 0x03)  // 0 ~ 3 (0: Hi-Z, 1: PWM1, 2: TCON10, 3: Reserved)#Power On Latch
#define _PIN_200                    (0 & 0x03)  // 0 ~ 3 (0: Hi-Z, 1: PWM0, 2: TCON8, 3: Reserved)#Power On Latch

#define _PIN_DRIVING_27to34                     (0x0c & 0x0f)  // 0 ~ f (Bit7:Schmitt Trigger, Bit6:Slew Rate, Bit5:Driving Current)
#define _PIN_DRIVING_38to45                     (0x0c & 0x0f)  // 0 ~ f (Bit3:Schmitt Trigger, Bit2:Slew Rate, Bit1:Driving Current)
#define _PIN_DRIVING_48to52                     (0x0c & 0x0f)  // 0 ~ f (Bit7:Schmitt Trigger, Bit6:Slew Rate, Bit5:Driving Current)
#define _PIN_DRIVING_53to55                     (0x0c & 0x0f)  // 0 ~ f (Bit3:Schmitt Trigger, Bit2:Slew Rate, Bit1:Driving Current)
#define _PIN_DRIVING_56to59                     (0x0c & 0x0f)  // 0 ~ f (Bit7:Schmitt Trigger, Bit6:Slew Rate, Bit5:Driving Current)
#define _PIN_DRIVING_62to65                     (0x0c & 0x0f)  // 0 ~ f (Bit3:Schmitt Trigger, Bit2:Slew Rate, Bit1:Driving Current)
#define _PIN_DRIVING_68to75_79to90              (0x0c & 0x0f)  // 0 ~ f (Bit7:Schmitt Trigger, Bit6:Slew Rate, Bit5:Driving Current)
#define _PIN_DRIVING_91to94_97to104             (0x0c & 0x0f)  // 0 ~ f (Bit3:Schmitt Trigger, Bit2:Slew Rate, Bit[1:0]:Driving Current)
#define _PIN_DRIVING_105to109                   (0x0c & 0x0f)  // 0 ~ f (Bit7:Schmitt Trigger, Bit6:Slew Rate, Bit5:Driving Current)
#define _PIN_DRIVING_110                        (0x0c & 0x0f)  // 0 ~ f (Bit3:Schmitt Trigger, Bit2:Slew Rate, Bit1:Driving Current)
#define _PIN_DRIVING_113to123                   (0x0c & 0x0f)  // 0 ~ f (Bit7:Schmitt Trigger, Bit6:Slew Rate, Bit5:Driving Current)
#define _PIN_DRIVING_124to125                   (0x0c & 0x0f)  // 0 ~ f (Bit3:Schmitt Trigger, Bit2:Slew Rate, Bit1:Driving Current)
#define _PIN_DRIVING_129to134                   (0x0c & 0x0f)  // 0 ~ f (Bit7:Schmitt Trigger, Bit6:Slew Rate, Bit[5:4]:Driving Current)
#define _PIN_DRIVING_135to144_147to156_159to168 (0x0e & 0x0f)  // 0 ~ f (Bit3:Schmitt Trigger, Bit2:Slew Rate, Bit[1:0]:Driving Current)
#define _PIN_DRIVING_169to186                   (0x0e & 0x0f)  // 0 ~ f (Bit7:Schmitt Trigger, Bit6:Slew Rate, Bit[5:4]:Driving Current)
#define _PIN_DRIVING_187to197                   (0x0c & 0x0f)  // 0 ~ f (Bit3:Schmitt Trigger, Bit2:Slew Rate, Bit1:Driving Current)
#define _PIN_DRIVING_198to200                   (0x0c & 0x0f)  // 0 ~ f (Bit7:Schmitt Trigger, Bit6:Slew Rate, Bit5:Driving Current)
#define _PIN_DRIVING_204to205                   (0x0c & 0x0f)  // 0 ~ f (Bit3:Schmitt Trigger, Bit2:Slew Rate, Bit1:Driving Current)

#elif(_SCALER_TYPE == _RTD2533B)

#define _PIN_3                          (2 & 0x03)     // 0 ~ 3
#define _PIN_4                          (2 & 0x03)     // 0 ~ 3
#define _PIN_48                         (2 & 0x03)     // 0 ~ 3
#define _PIN_49                         (3 & 0x03)     // 0 ~ 3  

#define _PIN_50_51                      (0 & 0x01)     // 0 ~ 1
#define _PIN_52_53                      (0 & 0x01)     // 0 ~ 1
#define _PIN_54                         (0 & 0x03)     // 0 ~ 3
#define _PIN_55_56_57                   (0 & 0x01)     // 0 ~ 1
#define _PIN_122_FUNC                   (0 & 0x01)     // 0 ~ 1
#define _PIN_110                        (1 & 0x01)     // 0 ~ 1
            
#define _PIN_111                        (0 & 0x03)     // 0 ~ 3
#define _PIN_112_113_114                (0 & 0x03)     // 0 ~ 3
#define _PIN_115_118_119                (0 & 0x01)     // 0 ~ 1
#define _PIN_120_121                    (2 & 0x03)     // 0 ~ 3     // set 120 & 121 As DVI DDC
#define _PIN_122                        (0 & 0x01)     // 0 ~ 1
#elif((_SCALER_TYPE == _RTD2023L) || (_SCALER_TYPE == _RTD2023S) || (_SCALER_TYPE == _RTD2023L_VB) || (_SCALER_TYPE == _RTD2023S_VB))

// Define for 2023S & 2023L                                    
#define _PIN_21_TO_40                   (0 & 0x03)    // 0 ~ 1      // Swap
#define _PIN_16_17_OR_43_44             (0 & 0x03)    // 0 ~ 1      // Pwm 1 2   0 : not use
#endif

// REG 46 DEFINE
//#define _DCLK_DELAY                  Panel.DCLK_DELAY//   0           // ( 0 ~ 7 )
#define _ABCLK_EN                       0           // ACLK/BCLK Output Enable ( Only used in 6 bit TTL/smart panel, otherwise, use DCLK)
#define _ACLK_POLARITY_INV              0           // ACLK(6 bit)/DCLK(8 bit) Polarity Inverted
#define _DCLK_EN                        0           // DCLK Output Enable (Only been used in TTL 8 bit mode)
#define _BCLK_POLARITY_INV              0           // BCLK(6 bit) Polarity Inverted


#define _ADC_DEFFERENTIAL              1 // ADC use the defferential mode            1 : Defferential   0: Single ended,

//--------------------------------------------------
// Scaler 1.8V definition
//--------------------------------------------------
#if(0)
'Careful'
#endif
#define _TYPE_REGULATOR                 0
#define _TYPE_BJT                       1
#define _SCALER_18V_POWER_TYPE          _TYPE_BJT

//--------------------------------------------------
// MCU Pin Assignment
//--------------------------------------------------
sbit bI2CSDA                            = P1^0;
sbit bI2CSCL                            = P1^1;
sbit bPANELPOWER                        = P1^2;
sbit bSCALERSDIO3                       = P1^5;
//sbit bSCALERSCSB                        = P1^4;
sbit bSCALERSCLK                        = P1^6;
sbit bLIGHTPOWER                        = P1^3;


#define bVGACONNECT                     (_MCU_PORT50) 
/*
#if(_HDMI_SUPPORT)
sbit bHDMICONNECT                       = P3^4;
#endif
#if(_TMDS_SUPPORT)
sbit bDVICONNECT                        = P3^4;
#endif
*/
sbit bIR_GPIO                           = P3^2;

//--------------------------------------------------
//            LED definitions
//--------------------------------------------------
#define bLED_GREEN                      (_MCU_PORT66)
#define bLED_RED                        (_MCU_PORT67)

#define GREENLED_ON()                   bLED_GREEN = 1
#define GREENLED_OFF()                  bLED_GREEN = 0
#define REDLED_ON()                     bLED_RED   = 1
#define REDLED_OFF()                    bLED_RED   = 0


sbit PNL3                        =(P3^3);
sbit PNL2                        =(P3^4);
sbit PNL1                      =(P3^5);
#if(DVD_EN)
    #if(_UARTTX)
          #define PNL0                      (_MCU_PORT67)
  #else
          #define PNL0                      (_MCU_PORT77)
  #endif
#else
#define PNL0                      (_MCU_PORT77 & 0x01)
#endif

#define SAW                        (_MCU_PORT56) 
#define SAW_HIGH()              SAW=1
#define SAW_LOW()               SAW=0        
//--------------------------------------------------


//--------------------------------------------------
//            VDC definitions
//--------------------------------------------------
sbit bDVD_POWER                           = P1^4;
#define bDVD_PWR_ON()              bDVD_POWER=0
#define bDVD_PWR_OFF()              bDVD_POWER=1

//#define bVDC_PWR                        (_MCU_PORT56)
//#define bVDC_RST                        (_MCU_PORT57) 


//--------------------------------------------------
//            Key definitions
//--------------------------------------------------
#if(_KEY_TYPE != _KEY_ADC)
sbit bPOWER_KEY                                 = P1^7;
//#define bPOWER_KEY                      (_MCU_PORT60 & 0x01)
#define bMENU_KEY                       (_MCU_PORT62 & 0x01)
#define bCH_INC_KEY                         (_MCU_PORT61 & 0x01)
#define bCH_DEC_KEY                       (_MCU_PORT60 & 0x01)
#define bRIGHT_KEY                      (_MCU_PORT65 & 0x01)
#define bLEFT_KEY                       (_MCU_PORT64 & 0x01)
#define bEXIT_KEY                       (_MCU_PORT63 & 0x01)


#else //(KEY_TYPE = KEY_ADC)            ADC Value
#define ADC_ID                          0    // ADC0

#define bNONE_KEY                       63   // Not touch key AD value
#define bPOWER_KEY                      8
#define bMENU_KEY                       36
#define bEXIT_KEY                       30
#define bLEFT_KEY                       15
#define bRIGHT_KEY                      23
#endif   //#if(KEY_TYPE != KEY_ADC)

//--------------------------------------------------
//            Tuner definitions
//--------------------------------------------------
/*
sbit bTUNER_PW                          = P3^4;
#define TUNER_PWR_ON()                  bTUNER_PW = 1
#define TUNER_PWR_OFF()                 bTUNER_PW = 0
*/
#define TUNER_PWR_ON()                1
#define TUNER_PWR_OFF()                  0
//--------------------------------------------------
//            Audio definitions
//--------------------------------------------------
#define VOLUME_CTRL_TYPE                _SOUND_PWM          // _SOUND_SC7313,_SOUND_PWM
                                      
#define bMUTE                             ( _MCU_PORT55)

#define _MUTE_ON          1
#define _MUTE_OFF        0

//----------------------------------------
//     Definition for sound processor
//----------------------------------------
#define _SOUND_PROCESSOR                _OFF            // _ON, _OFF


#if(VOLUME_CTRL_TYPE == _SOUND_PWM)                                 
#if(_MCU_TYPE == _MYSON_MTV512 || _MCU_TYPE == _RTD_2120)
/*
_SCALAR_PWM0, _SCALAR_PWM1, _SCALAR_PWM2
// For MCU
_MCU_PWM0,    _MCU_PWM1,    _MCU_PWM2,   _MCU_PWM3
_MCU_PWM4,    _MCU_PWM5 
*/
#define bVOLUME_PWM                     _MCU_PWM2  //MTV512 DA2
#endif
                
#define _MAX_VOLUME                     180//164
#define _MIN_VOLUME                     28
#define _VOLUME_INV                     1


#define _AUDIO_A                        (_MCU_PORT53)
#define _AUDIO_B                        (_MCU_PORT54)
#endif // SOUND_PWM

#if(VOLUME_CTRL_TYPE == _SOUND_SC7313)
#define _ADDR_7313                      0x88

#endif      //#if(VOLUME_CTRL_TYPE == _SOUND_SC7313)


//--------------------------------------------------
//                  MCU CONFIG
//--------------------------------------------------
#if(_MCU_TYPE == _MYSON_MTV512 || _MCU_TYPE == _MYSON_MTV312 || _MCU_TYPE == _RTD_2120)

//-------- Set port 5 type ------------
// _MCU_PAD5_IS_DAC,_MCU_PAD5_IS_IO
#define _MCU_PORT5_0_TYPE        _MCU_PAD5_IS_IO          // P5.0   
#define _MCU_PORT5_1_TYPE        _MCU_PAD5_IS_DAC         // P5.1  
#define _MCU_PORT5_2_TYPE        _MCU_PAD5_IS_DAC         // P5.2  
#define _MCU_PORT5_3_TYPE        _MCU_PAD5_IS_IO          // P5.3  
#define _MCU_PORT5_4_TYPE        _MCU_PAD5_IS_IO          // P5.4  
#define _MCU_PORT5_5_TYPE        _MCU_PAD5_IS_IO          // P5.5  
//  _MCU_PAD_56_57_IS_IIC2,_MCU_PAD_56_57_IS_IO           // For DVI DDC
#define _MCU_PORT5_6_TYPE        _MCU_PAD_56_57_IS_IO     // P5.6 
                                
//-------- Set port 6 type ------------
//  _MCU_PAD6_IS_ADC,_MCU_PAD6_IS_IO
#define _MCU_PORT6_0_TYPE        _MCU_PAD6_IS_IO          // P6.0
#define _MCU_PORT6_1_TYPE        _MCU_PAD6_IS_IO          // P6.1
#define _MCU_PORT6_2_TYPE        _MCU_PAD6_IS_IO          // P6.2
#define _MCU_PORT6_3_TYPE        _MCU_PAD6_IS_IO          // P6.3
//  _MCU_PAD_P66_IS_CLK1,_MCU_PAD_P66_IS_IO    // For CLK output

#define _MCU_PORT6_6_TYPE        _MCU_PAD_P66_IS_IO       // P6.6
#define _MCU_PORT6_7_TYPE        _MCU_PAD_P67_IS_IO       // p6.7
//-------- Set port 5/6 mode ------------
//  _MCU_PAD_IS_INPUT,_MCU_PAD_IS_OUTPUT
#define _MCU_PORT5_0_MODE        _MCU_PAD_IS_INPUT        // P5.0 
#define _MCU_PORT5_1_MODE        _MCU_PAD_IS_OUTPUT       // P5.1
#define _MCU_PORT5_2_MODE        _MCU_PAD_IS_OUTPUT       // P5.2
#define _MCU_PORT5_3_MODE        _MCU_PAD_IS_OUTPUT       // P5.3
#define _MCU_PORT5_4_MODE        _MCU_PAD_IS_OUTPUT       // P5.4
#define _MCU_PORT5_5_MODE        _MCU_PAD_IS_OUTPUT       // P5.5
#define _MCU_PORT5_6_MODE        _MCU_PAD_IS_OUTPUT       // P5.6
#define _MCU_PORT5_7_MODE        _MCU_PAD_IS_OUTPUT       // P5.7
#define _MCU_PORT6_0_MODE        _MCU_PAD_IS_INPUT        // P6.0
#define _MCU_PORT6_1_MODE        _MCU_PAD_IS_INPUT        // P6.1
#define _MCU_PORT6_2_MODE        _MCU_PAD_IS_INPUT        // P6.2
#define _MCU_PORT6_3_MODE        _MCU_PAD_IS_INPUT        // P6.3
#define _MCU_PORT6_4_MODE        _MCU_PAD_IS_INPUT        // P6.4
#define _MCU_PORT6_5_MODE        _MCU_PAD_IS_INPUT        // P6.5
#define _MCU_PORT6_6_MODE        _MCU_PAD_IS_OUTPUT        // P6.6
#define _MCU_PORT6_7_MODE        _MCU_PAD_IS_INPUT        // P6.7

//-------- Set port 7 type(MTV512 only) -----------
#define _MCU_PORT7_6_TYPE        _MCU_PAD_P76_IS_CLK2       // P7.6   _MCU_PAD_P76_IS_CLK2,_MCU_PAD_P76_IS_IO
#define _MCU_PORT7_7_TYPE        _MCU_PAD_P77_IS_IO       // P7.7   _MCU_PAD_P77_IS_IO,_MCU_PAD_P77_IS_RESERVED

//-------- Set port 7 mode ------------
#define _MCU_PORT7_6_MODE        _MCU_PAD_IS_OUTPUT       // P7.6   _MCU_PAD_IS_INPUT,_MCU_PAD_IS_OUTPUT
#if(DVD_EN)
#define _MCU_PORT7_7_MODE        _MCU_PAD_IS_OUTPUT       // P7.7   _MCU_PAD_IS_INPUT,_MCU_PAD_IS_OUTPUT
#else
#define _MCU_PORT7_7_MODE        _MCU_PAD_IS_INPUT       // P7.7   _MCU_PAD_IS_INPUT,_MCU_PAD_IS_OUTPUT
#endif
//-------- Set P3.0/P3.1 type ---------
#define _MCU_P30_P31_TYPE        _MCU_PAD_P30_31_IS_IIC1  // P3.0/P3.1  _MCU_PAD_P30_31_IS_IIC1,_MCU_PAD_P30_31_IS_IO

//-------- Set port 1 type ------------
#define _MCU_PORT1_0_TYPE        _MCU_PAD_P1_STD_IO       // P1.0   _MCU_PAD_P1_STD_IO,_MCU_PAD_P1_CMOS_OUT
#define _MCU_PORT1_1_TYPE        _MCU_PAD_P1_STD_IO       // P1.1   _MCU_PAD_P1_STD_IO,_MCU_PAD_P1_CMOS_OUT
#define _MCU_PORT1_2_TYPE        _MCU_PAD_P1_STD_IO       // P1.2   _MCU_PAD_P1_STD_IO,_MCU_PAD_P1_CMOS_OUT
#define _MCU_PORT1_3_TYPE        _MCU_PAD_P1_STD_IO       // P1.3   _MCU_PAD_P1_STD_IO,_MCU_PAD_P1_CMOS_OUT
#define _MCU_PORT1_4_TYPE        _MCU_PAD_P1_STD_IO       // P1.4   _MCU_PAD_P1_STD_IO,_MCU_PAD_P1_CMOS_OUT
#define _MCU_PORT1_5_TYPE        _MCU_PAD_P1_STD_IO       // P1.5   _MCU_PAD_P1_STD_IO,_MCU_PAD_P1_CMOS_OUT
#define _MCU_PORT1_6_TYPE        _MCU_PAD_P1_STD_IO       // P1.6   _MCU_PAD_P1_STD_IO,_MCU_PAD_P1_CMOS_OUT
#define _MCU_PORT1_7_TYPE        _MCU_PAD_P1_STD_IO       // P1.7   _MCU_PAD_P1_STD_IO,_MCU_PAD_P1_CMOS_OUT

                                      



#if(_MCU_TYPE == _MYSON_MTV512 || _MCU_TYPE == _MYSON_MTV312)
#define	MCU_OPTION_F56_DEF     (0x00 | _MCU_PORT7_7_TYPE)

#define	MCU_IICCTR_F00_DEF     0xC0                     // Enable IIC Interface and define ddc2 active at HSDA/HSCL
#define	MCU_INTEN_F04_DEF      0x04                     // Detect WslvA1 IIC Stop Condition
#define	MCU_INTFLG_F03_DEF     0x00                     // Clear IIC Interrupt register
#define	MCU_CTRSLVB_F0A_DEF    0x00                     // Define IIC Protocal Slave Address Bit
#define	MCU_DDCCTRA1_F06_DEF   0xD0                    // Enable DDC1 and DDCRAM 128 Access
#define	MCU_SLVA1ADR_F07_DEF   (0x80 | (0xA0 >> 1))    // DDC Slave A1 address
#define	MCU_DDCCTRA2_F86_DEF   0xD0                    // Enable DDC1 and DDCRAM 128 Access
#define	MCU_SLVA2ADR_F87_DEF   (0x80 | (0xA0 >> 1))    //DDC Slave A2 address 

#elif(_MCU_TYPE == _RTD_2120)

#define MCU_PINSHARE_FF01_DEF  (0x41 | (_MCU_PORT7_6_TYPE << 1))

#endif
#endif // end #if(_MCU_TYPE == _MYSON_MTV512 || _MCU_TYPE == _MYSON_MTV312 || _MCU_TYPE == _RTD_2120)




//--------------------------------------------------
// Definitions of ADC Input Swap Settings
//--------------------------------------------------
#define _ADC_INPUT_SWAP_RG              _OFF
#define _ADC_INPUT_SWAP_RB              _OFF
#define _ADC_INPUT_SWAP_GB              _OFF


