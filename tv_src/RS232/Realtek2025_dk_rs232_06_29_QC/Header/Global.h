//----------------------------------------------------------------------------------------------------
// ID Code      : Global.h No.0002
// Update Note  : 
//
//----------------------------------------------------------------------------------------------------

//--------------------------------------------------
// Data Type Redefine
//--------------------------------------------------
typedef unsigned char BYTE;
typedef char          SBYTE;
typedef unsigned int  WORD;
typedef	int           SWORD;
typedef unsigned long DWORD;
typedef long          SDWORD;
typedef unsigned long UINT32;

//--------------------------------------------------
// Definations of Physical Boolean
//--------------------------------------------------
#define _TRUE                           1
#define _FALSE                          0
#define _HIGH                           1
#define _LOW                            0
#define _ENABLE                         1
#define _DISABLE                        0
#define _READ                           1
#define _WRITE                          0
#define _ON                             1
#define _OFF                            0
#define _SUCCESS                        1
#define _FAIL                           0
#define _STABLE                         1
#define _UNSTABLE                       0
#define _POSITIVE                       1
#define _NEGATIVE                       0
#define _NEWMODE                        1
#define _OLDMODE                        0


//--------------------------------------------------
// Definitions of Bits
//--------------------------------------------------
#define _BIT0                           0x0001
#define _BIT1                           0x0002
#define _BIT2                           0x0004
#define _BIT3                           0x0008
#define _BIT4                           0x0010
#define _BIT5                           0x0020
#define _BIT6                           0x0040
#define _BIT7                           0x0080
#define _BIT8                           0x0100
#define _BIT9                           0x0200
#define _BIT10                          0x0400
#define _BIT11                          0x0800
#define _BIT12                          0x1000
#define _BIT13                          0x2000
#define _BIT14                          0x4000
#define _BIT15                          0x8000


//--------------------------------------------------
// Definitions of Page
//--------------------------------------------------
#define _PAGE0                          0
#define _PAGE1                          1
#define _PAGE2                          2
#define _PAGE3                          3
#define _PAGE4                          4
#define _PAGE5                          5
#define _PAGE6                          6
#define _PAGE7                          7

//--------------------------------------------------
// Definitions of Input Source Type
//--------------------------------------------------
#define _SOURCE_VGA                     0
#define _SOURCE_DVI                     1
#define _SOURCE_VIDEO_AV                2
#define _SOURCE_VIDEO_SV                3
#define _SOURCE_VIDEO_DVD             4
//#define _SOURCE_VIDEO_YUV               4
#define _SOURCE_VIDEO_TV                5
#define _SOURCE_VIDEO_SCART             6
#define _SOURCE_HDMI                    7
#define _SOURCE_YPBPR                   8
#define _SOURCE_NONE                    9

#define _SOURCE_VIDEO_YUV              10

//--------------------------------------------------
// Definitions of ModeHandler State
//--------------------------------------------------
#define _PWOFF_STATE                    0
#define _INITIAL_STATE                  1
#define _SEARCH_STATE                   2
#define _ACTIVE_STATE                   3
#define _NOSUPPORT_STATE                4
#define _NOSIGNAL_STATE                 5
#define _SLEEP_STATE                    6
#define _SOURCE_CHANGE_STATE            7

//--------------------------------------------------
// Definitions of Input Sync Type State
//--------------------------------------------------
#define _NO_SYNC_STATE                  0
#define _SS_STATE                       1
#define _CS_STATE                       2
#define _SOG_STATE                      3
#define _SOY_STATE                      4
#define _DSS_STATE                      5
#define _VIDEO8_STATE                   6


//--------------------------------------------------
// Definitions of Mode Search Type
//--------------------------------------------------
#define _PRESET_MODE_TYPE               0
#define _USER_MODE_TYPE                 1


//--------------------------------------------------
// Definitions of Waiting Events
//--------------------------------------------------
#define _EVENT_IVS                      0x01
#define _EVENT_IEN_START                0x02
#define _EVENT_IEN_STOP                 0x04
#define _EVENT_DVS                      0x08
#define _EVENT_DEN_START                0x10
#define _EVENT_DEN_STOP                 0x20
#define _EVENT_UNDERFLOW                0x40
#define _EVENT_OVERFLOW                 0x80


//--------------------------------------------------
// Definations of Scaler Write/Read Type
//--------------------------------------------------
#define _NON_AUTOINC                    1
#define _AUTOINC                        0
#define _BURST                          2
#define _END                            0


//--------------------------------------------------
// Definations of Load OSD Font Table Type
//--------------------------------------------------
#define _NORMAL_FONT                    0x00
#define _COMPRESS_FONT                  0x01


//--------------------------------------------------
// Definations of Red/Green/Blue
//--------------------------------------------------
#define _RED                            0
#define _GREEN                          1
#define _BLUE                           2


//--------------------------------------------------
// Definitions of Display Delay
//--------------------------------------------------
#define _CAPTURE_HDELAY                 3

#define _PROGRAM_HDELAY                 10
#define _PROGRAM_VDELAY                 2

#define _MEASURE_HDEALY                 7


//--------------------------------------------------
// Global Macros
//--------------------------------------------------
#define LOBYTE(w)                       ((BYTE)(w))
#define HIBYTE(w)                       ((BYTE)(((WORD)(w) >> 8) & 0x00FF))
#define SEC(x)                          (100 * x)


//--------------------------------------------------
// Definitions of Scaler Type
//--------------------------------------------------
#define _RTD2533B                       0   
#define _RTD2023L                       1   
#define _RTD2023S                       2   
#define _RTD2023L_VB                    3   
#define _RTD2023S_VB                    4   
#define _RTD2553V                       5   
#define _RTD2546N                       6
#define _RTD2525L                       7 
#define _RTD2547D                       8

//--------------------------------------------------
// Definitions of Reset Type
//--------------------------------------------------
#define _RESET_IN                       0   // MCU reset Scaler
#define _RESET_OUT                      1   // Scaler reset MCU

//--------------------------------------------------
// Definations of Input Port Types
//--------------------------------------------------
#define _NO_PORT                        0
#define _DSUB_A0_PORT                   1
#define _DSUB_A1_PORT                   2
#define _DVI_PORT                       3
#define _DVI_I_A0_PORT                  4
#define _DVI_I_A1_PORT                  5
#define _VIDEO8_PORT                    6
#define _VIDEO_2ND_ADC_PORT             7
#define _YPBPR_A0_PORT                  8
#define _YPBPR_A1_PORT                  9
#define _HDMI_PORT                      10

//--------------------------------------------------
// Definations of Host Interface (Parallel/Serial Port)
//--------------------------------------------------
#define _SERIAL_PORT                    0
#define _PARALLEL_PORT                  1

//--------------------------------------------------
// Definations of RTD/MCU Crystal Frequency in KHz
//--------------------------------------------------
#define _XTAL12000K                     12000
#define _XTAL24576K                     24576
#define _XTAL24000K                     24000

//--------------------------------------------------
// Definations of Video Input Selection
//--------------------------------------------------
#define _VIDEO_8_IN                     0
#define _VIDEO_16_IN                    1

//--------------------------------------------------
// Definations of Last Line Finetune Method
//--------------------------------------------------
#define _LAST_LINE_METHOD_NONE          0 
#define _LAST_LINE_METHOD_0             1
#define _LAST_LINE_METHOD_1             2
#define _LAST_LINE_METHOD_2             3

//--------------------------------------------------
// Definations of Adjusting Vertical Position Direction Method
//--------------------------------------------------
#define _V_POSITION_METHOD_0            0
#define _V_POSITION_METHOD_1            1

//--------------------------------------------------
// RTD2553V Set Method of Hsync Type Detection for Analog Input 
//--------------------------------------------------
#define _NORMAL_RUN                     0     
#define _AUTO_RUN			            1

//--------------------------------------------------
// Definitions of DDC Type
//--------------------------------------------------
#define _DDC_NONE                       0
#define _DDC_RTD_CODE                   1
#define _DCC_RTD_EEPROM                 2
#define _DDC_MTV512                     3
#define _DDC_RTD2120                    4


//--------------------------------------------------
// Definitions of MCU Type
//--------------------------------------------------
#define _MYSON_MTV312                   0
#define _MYSON_MTV512                   1
#define _STK_6021                       2
#define _RTD_2120                       3

//--------------------------------------------------
// Definitions of Key Type
//--------------------------------------------------
#define _KEY_NORMAL                     0
#define _KEY_ADC                        1

//--------------------------------------------------
// Definitions for volume PWM setting
//--------------------------------------------------
#define _SOUND_PWM                      0
#define _SOUND_SC7313                   1

//--------------------------------------------------
// Definitions of DAC
//--------------------------------------------------
// For scalar
#define _SCALAR_PWM0                    0
#define _SCALAR_PWM1                    1
#define _SCALAR_PWM2                    2
// For MCU
#define _MCU_PWM0                       3
#define _MCU_PWM1                       4
#define _MCU_PWM2                       5
#define _MCU_PWM3                       6
#define _MCU_PWM4                       7
#define _MCU_PWM5                       8


//--------------------------------------------------
// Definitions for Panel Settings
//--------------------------------------------------
#define _PANEL_TTL                      0
#define _PANEL_HZ                       1
#define _PANEL_LVDS                     2
#define _PANEL_RSDS                     3
#define _PANEL_COG                      4
  
//--------------------------------------------------
// Definations of PLL Type
//--------------------------------------------------
#define _DPLL                           0
#define _MPLL                           1

