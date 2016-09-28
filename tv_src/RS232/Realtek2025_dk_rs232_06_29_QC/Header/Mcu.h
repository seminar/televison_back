//----------------------------------------------------------------------------------------------------
// ID Code      : Mcu.h No.0001
// Update Note  : 
//
//----------------------------------------------------------------------------------------------------

//--------------------------------------------------
// Definitions of Crystal Frequency
//--------------------------------------------------
#define _MCU_INST_CYCLE             ((DWORD)1000000 * 12 / _MCU_XTAL)

//--------------------------------------------------
// Timer Period (unit: ns)
//--------------------------------------------------
#define _10MS_PERIOD                (DWORD)10000000
#define _1MS_PERIOD                 (DWORD)1000000
#define _HALF_MS_PERIOD             (DWORD)500000

//--------------------------------------------------
// Timer0 Settings (1ms)
//--------------------------------------------------
#define _TIMER0_COUNT_NUM           (0xFFFF - (_1MS_PERIOD / _MCU_INST_CYCLE) + 35)
#define _TIMER0_COUNT_LBYTE         (_TIMER0_COUNT_NUM & 0x00FF)
#define _TIMER0_COUNT_HBYTE         (_TIMER0_COUNT_NUM >> 8)


//--------------------------------------------------
// Definitions of mcu I/O pin
//--------------------------------------------------
//   ----------------  MTV512  -----------------
#if(_MCU_TYPE == _MYSON_MTV512)
// For MCU port 5 regsister
#define _MCU_PORT50                 MCU_PORT5_F30[0]       // P5.0
#define _MCU_PORT51                 MCU_PORT5_F30[1]       // P5.1
#define _MCU_PORT52                 MCU_PORT5_F30[2]       // P5.2
#define _MCU_PORT53                 MCU_PORT5_F30[3]       // P5.3
#define _MCU_PORT54                 MCU_PORT5_F30[4]       // P5.4
#define _MCU_PORT55                 MCU_PORT5_F30[5]       // P5.5
#define _MCU_PORT56                 MCU_PORT5_F30[6]       // P5.6
#define _MCU_PORT57                 MCU_PORT5_F30[7]       // P5.7

// For MCU port 6 regsister
#define _MCU_PORT60                 MCU_PORT6_F38[0]       // P6.0
#define _MCU_PORT61                 MCU_PORT6_F38[1]       // P6.1
#define _MCU_PORT62                 MCU_PORT6_F38[2]       // P6.2
#define _MCU_PORT63                 MCU_PORT6_F38[3]       // P6.3
#define _MCU_PORT64                 MCU_PORT6_F38[4]       // P6.4
#define _MCU_PORT65                 MCU_PORT6_F38[5]       // P6.5
#define _MCU_PORT66                 MCU_PORT6_F38[6]       // P6.6
#define _MCU_PORT67                 MCU_PORT6_F38[7]       // P6.7

// For MCU port 7 regsister
#define _MCU_PORT76                 MCU_PORT7_F76[0]       // P7.6
#define _MCU_PORT77                 MCU_PORT7_F76[1]       // P7.7

// For MCU pad type control
#define _MCU_PORT1_TYPE             MCU_PADMODE_F55        // Port 1 type
#define _MCU_PORT5_TYPE             MCU_PADMODE_F51        // Port 5 type
#define _MCU_PORT6_TYPE             MCU_PADMODE_F50        // Port 6 type
#define _MCU_PORT7_TYPE             MCU_PADMODE_F5E        // Port 7 type

// For MCU pad mode control(input/output)
#define _MCU_PORT5_I_O              MCU_PADMODE_F53        // Port 5 Input/Output control
#define _MCU_PORT6_I_O              MCU_PADMODE_F54        // Port 6 Input/Output control
#define _MCU_PORT7_I_O              MCU_PADMODE_F5F        // Port 7 Input/Output control

//   ---------------  RTD2120S  --------------
#elif(_MCU_TYPE == _RTD_2120)

// For MCU port 5 regsister
#define _MCU_PORT50                 MCU_PORT50_FF50[0]     // P5.0
#define _MCU_PORT51                 MCU_PORT50_FF50[1]     // P5.1
#define _MCU_PORT52                 MCU_PORT50_FF50[2]     // P5.2
#define _MCU_PORT53                 MCU_PORT50_FF50[3]     // P5.3
#define _MCU_PORT54                 MCU_PORT50_FF50[4]     // P5.4
#define _MCU_PORT55                 MCU_PORT50_FF50[5]     // P5.5
#define _MCU_PORT56                 MCU_PORT50_FF50[6]     // P5.6
#define _MCU_PORT57                 MCU_PORT50_FF50[7]     // P5.7

// For MCU port 6 regsister
#define _MCU_PORT60                 MCU_PORT60_FF58[0]     // P6.0
#define _MCU_PORT61                 MCU_PORT60_FF58[1]     // P6.1
#define _MCU_PORT62                 MCU_PORT60_FF58[2]     // P6.2
#define _MCU_PORT63                 MCU_PORT60_FF58[3]     // P6.3
#define _MCU_PORT64                 MCU_PORT60_FF58[4]     // P6.4
#define _MCU_PORT65                 MCU_PORT60_FF58[5]     // P6.5
#define _MCU_PORT66                 MCU_PORT60_FF58[6]     // P6.6
#define _MCU_PORT67                 MCU_PORT60_FF58[7]     // P6.7

// For MCU port 7 regsister
#define _MCU_PORT76                 MCU_PORT76_77_FF60[0]  // P7.6
#define _MCU_PORT77                 MCU_PORT76_77_FF60[1]  // P7.7

// For MCU pad type control
#define _MCU_PORT1_TYPE             MCU_PORT1_TYPE_FF09    // Port 1 type
#define _MCU_PORT5_TYPE             MCU_PIN_SHARE0_FF00    // Port 5 type
#define _MCU_PORT6_TYPE             MCU_PIN_SHARE2_FF02    // Port 6 type

// For MCU pad mode control(input/output)
#define _MCU_PORT5_I_O              MCU_PORT5_OE_FF03      // Port 5 Input/Output control
#define _MCU_PORT6_I_O              MCU_PORT6_OE_FF04      // Port 6 Input/Output control
#define _MCU_PORT7_I_O              MCU_PORT7_OE_FF05      // Port 7 Input/Output control
#endif


//--------------------------------------------------
//                  MCU CONFIG
//--------------------------------------------------
#if(_MCU_TYPE == _MYSON_MTV512 || _MCU_TYPE == _MYSON_MTV312 || _MCU_TYPE == _RTD_2120)
// Public
#if(_MCU_TYPE == _MYSON_MTV512 || _MCU_TYPE == _MYSON_MTV312)
#define _MCU_PAD5_IS_DAC         0     //  DAC
#define _MCU_PAD5_IS_IO          1     //  MCU I/O
#elif(_MCU_TYPE == _RTD_2120)
#define _MCU_PAD5_IS_DAC         1     //  DAC
#define _MCU_PAD5_IS_IO          0     //  MCU I/O
#endif
#define _MCU_PAD6_IS_ADC         1     //  P6.0~P6.3  ADC
#define _MCU_PAD6_IS_IO          0     //  P6.0~P6.3  I/O
#define _MCU_PAD_56_57_IS_IIC2   1     //  P5.6/P5.7  IIC1
#define _MCU_PAD_56_57_IS_IO     0     //  MCU I/O
#define _MCU_PAD_P66_IS_CLK1     1     //  P6.6
#define _MCU_PAD_P66_IS_IO       0     //  MCU I/O
#define _MCU_PAD_P67_IS_IO       0     //  MCU I/O
#define _MCU_PAD_P76_IS_CLK2     1     //  P7.6
#define _MCU_PAD_P76_IS_IO       0     //  MCU I/O
#define _MCU_PAD_P77_IS_IO       1     //  P7.7    I/O  Only for MTV512/MTV312
#define _MCU_PAD_P77_IS_RESERVED 0     //  Reserved
#define _MCU_PAD_P30_31_IS_IIC1  1     //  P3.0/P3.1  IIC1
#define _MCU_PAD_P30_31_IS_IO    0     //  I/O / RX/TX
#define _MCU_PAD_IS_INPUT        0     //  Input
#define _MCU_PAD_IS_OUTPUT       1     //  Output
#define _MCU_PAD_P1_STD_IO       0     //  P1 is 8051 standard I/O
#define _MCU_PAD_P1_CMOS_OUT     1     //  P1 is Push-Pull output

#if(_MCU_TYPE == _MYSON_MTV512 || _MCU_TYPE == _MYSON_MTV312) // MTV512/MTV312
#define _MCU_P5_TYPE_DEF        ((_MCU_PORT5_5_TYPE << 5) | (_MCU_PORT5_4_TYPE << 4) \  
                                |(_MCU_PORT5_3_TYPE << 3) | (_MCU_PORT5_2_TYPE << 2) \
                                |(_MCU_PORT5_1_TYPE << 1) | (_MCU_PORT5_0_TYPE))

#define _MCU_P6_TYPE_DEF        ((_MCU_PORT6_3_TYPE << 3) | (_MCU_PORT6_2_TYPE << 2) \
                                |(_MCU_PORT6_1_TYPE << 1) | (_MCU_PORT6_0_TYPE))


#define _MCU_PADMODE_F52_DEF    ((_MCU_PAD_P30_31_IS_IIC1 << 7) | (_MCU_PORT5_6_TYPE << 5) \
                                |(_MCU_PORT6_6_TYPE << 4))

#define _MCU_P76_TYPE_DEF       (_MCU_PAD_P76_IS_IO << 6)
        
#elif(_MCU_TYPE == _RTD_2120)                                // RTD2120S

#define _MCU_P5_TYPE_DEF        ((_MCU_PORT5_6_TYPE << 6) | (_MCU_PORT5_5_TYPE << 5) \  
                                |(_MCU_PORT5_4_TYPE << 4) | (_MCU_PORT5_3_TYPE << 3) \
                                |(_MCU_PORT5_2_TYPE << 2) | (_MCU_PORT5_1_TYPE << 1) \
                                |(_MCU_PORT5_0_TYPE))

#define _MCU_P6_TYPE_DEF        ((_MCU_PORT6_6_TYPE << 4) | (_MCU_PORT6_3_TYPE << 3) \  
                                |(_MCU_PORT6_2_TYPE << 2) | (_MCU_PORT6_1_TYPE << 1) \
                                |(_MCU_PORT6_0_TYPE))
#endif

#define _MCU_P1_TYPE_DEF        ((_MCU_PORT1_7_TYPE << 7) | (_MCU_PORT1_6_TYPE << 6) \
                                |(_MCU_PORT1_5_TYPE << 5) | (_MCU_PORT1_4_TYPE << 4) \
                                |(_MCU_PORT1_3_TYPE << 3) | (_MCU_PORT1_2_TYPE << 2) \
                                |(_MCU_PORT1_1_TYPE << 1) | (_MCU_PORT1_0_TYPE))

#define _MCU_P5_MODE_DEF        ((_MCU_PORT5_7_MODE << 7) | (_MCU_PORT5_6_MODE << 6) \
                                |(_MCU_PORT5_5_MODE << 5) | (_MCU_PORT5_4_MODE << 4) \
                                |(_MCU_PORT5_3_MODE << 3) | (_MCU_PORT5_2_MODE << 2) \
                                |(_MCU_PORT5_1_MODE << 1) | (_MCU_PORT5_0_MODE))

#define _MCU_P6_MODE_DEF        ((_MCU_PORT6_7_MODE << 7) | (_MCU_PORT6_6_MODE << 6) \
                                |(_MCU_PORT6_5_MODE << 5) | (_MCU_PORT6_4_MODE << 4) \
                                |(_MCU_PORT6_3_MODE << 3) | (_MCU_PORT6_2_MODE << 2) \
                                |(_MCU_PORT6_1_MODE << 1) | (_MCU_PORT6_0_MODE))

#define _MCU_P7_MODE_DEF        ((_MCU_PORT7_7_MODE << 7) | (_MCU_PORT7_6_MODE << 6))
               
#endif

//----------------------------------------------------------------------------------------------------

#ifdef __MCU__

//--------------------------------------------------
// Global Variables
//--------------------------------------------------
#if(_MCU_TYPE == _MYSON_MTV312)

BYTE xdata MCU_PADMODE_F50          _at_ 0xF50;
BYTE xdata MCU_PADMODE_F51          _at_ 0xF51;
BYTE xdata MCU_PADMODE_F52          _at_ 0xF52;
BYTE xdata MCU_PADMODE_F53          _at_ 0xF53;
BYTE xdata MCU_PADMODE_F54          _at_ 0xF54;
BYTE xdata MCU_PADMODE_F55          _at_ 0xF55;
BYTE xdata MCU_OPTION_F56           _at_ 0xF56;
BYTE xdata MCU_PORT4_F58[3]         _at_ 0xF58;
BYTE xdata MCU_PORT5_F30[7]         _at_ 0xF30;
BYTE xdata MCU_PORT6_F38[8]         _at_ 0xF38;
BYTE xdata MCU_DAC_F20[14]          _at_ 0xF20;
BYTE xdata MCU_HVSTUS_F40           _at_ 0xF40;
BYTE xdata MCU_HCNTH_F41            _at_ 0xF41;
BYTE xdata MCU_HCNTL_F42            _at_ 0xF42;
BYTE xdata MCU_VCNTH_F43            _at_ 0xF43;
BYTE xdata MCU_VCNTL_F44            _at_ 0xF44;
BYTE xdata MCU_INTFLG_F48           _at_ 0xF48;
BYTE xdata MCU_INTEN_F49            _at_ 0xF49;
BYTE xdata MCU_IICCTR_F00           _at_ 0xF00;
BYTE xdata MCU_IICSTUS_F01          _at_ 0xF01;
BYTE xdata MCU_INTFLG_F03           _at_ 0xF03;
BYTE xdata MCU_INTEN_F04            _at_ 0xF04;
BYTE xdata MCU_MBUF_F05             _at_ 0xF05;
BYTE xdata MCU_DDCCTR_F06           _at_ 0xF06;
BYTE xdata MCU_SLVAADR_F07          _at_ 0xF07;
BYTE xdata MCU_RCTXBBUF_F08         _at_ 0xF08;
BYTE xdata MCU_SLVBADR_F09          _at_ 0xF09;
BYTE xdata MCU_ADC_F10              _at_ 0xF10;
BYTE xdata MCU_WDT_F18              _at_ 0xF18;
BYTE xdata MCU_ISPSLV_F0B           _at_ 0xF0B;
BYTE xdata MCU_ISPEN_F0C            _at_ 0xF0C;

#elif(_MCU_TYPE == _MYSON_MTV512)
#if (_DDC_TYPE == _DDC_MTV512)
#if(_VGA_SUPPORT)
BYTE xdata MCU_DDCRAM_0[128]        _at_ 0xE00;
#endif
#if(_TMDS_SUPPORT)
BYTE xdata MCU_DDCRAM_1[128]        _at_ 0xE80;
#endif
#endif
BYTE xdata MCU_PADMODE_F50          _at_ 0xF50;
BYTE xdata MCU_PADMODE_F51          _at_ 0xF51;
BYTE xdata MCU_PADMODE_F52          _at_ 0xF52;
BYTE xdata MCU_PADMODE_F53          _at_ 0xF53;
BYTE xdata MCU_PADMODE_F54          _at_ 0xF54;
BYTE xdata MCU_PADMODE_F55          _at_ 0xF55;
BYTE xdata MCU_OPTION_F56           _at_ 0xF56;
BYTE xdata MCU_PADMODE_F5E          _at_ 0xF5E;
BYTE xdata MCU_PADMODE_F5F          _at_ 0xF5F;
BYTE xdata MCU_PORT5_F30[8]         _at_ 0xF30;
BYTE xdata MCU_PORT6_F38[8]         _at_ 0xF38;
BYTE xdata MCU_PORT7_F76[2]         _at_ 0xF76;
BYTE xdata MCU_DAC_F20[5]           _at_ 0xF20;
BYTE xdata MCU_IICCTR_F00           _at_ 0xF00;
BYTE xdata MCU_IICSTUS_F01          _at_ 0xF01;
BYTE xdata MCU_INTFLG_F03           _at_ 0xF03;
BYTE xdata MCU_INTEN_F04            _at_ 0xF04;
BYTE xdata MCU_DDCCTRA1_F06         _at_ 0xF06;
BYTE xdata MCU_SLVA1ADR_F07         _at_ 0xF07;
BYTE xdata MCU_RCTXBBUF_F08         _at_ 0xF08;
BYTE xdata MCU_SLVBADR_F09          _at_ 0xF09;
BYTE xdata MCU_CTRSLVB_F0A          _at_ 0xF0A;
BYTE xdata MCU_DDCCTRA2_F86         _at_ 0xF86;
BYTE xdata MCU_SLVA2ADR_F87         _at_ 0xF87;
BYTE xdata MCU_ADC_F10              _at_ 0xF10;
BYTE xdata MCU_WDT_F18              _at_ 0xF18;
BYTE xdata MCU_ETCTR_F88            _at_ 0xF88;
BYTE xdata MCU_ETMOD_F89            _at_ 0xF89;
BYTE xdata MCU_THET_F8A             _at_ 0xF8A;
BYTE xdata MCU_TLET_F8B             _at_ 0xF8B;
BYTE xdata MCU_RCAPETH_F8C          _at_ 0xF8C;
BYTE xdata MCU_RCAPETL_F8D          _at_ 0xF8D;
BYTE xdata MCU_EINT1PEN_F8E         _at_ 0xF8E;
BYTE xdata MCU_INTFLG_F48           _at_ 0xF48;
BYTE xdata MCU_INTFLG_F49           _at_ 0xF49;

#elif(_MCU_TYPE == _RTD_2120)

sfr CKCON   = 0x8E;

#if(_MEMORY_LOCATION == _FLASH)
BYTE xdata MCU_FLASH[1024 * (_END_PAGE - _START_PAGE + 2)]  _at_ (_START_PAGE * 1024);
#endif

#if (_DDC_TYPE == _DDC_RTD2120)
#if(_VGA_SUPPORT)
BYTE xdata MCU_DDCRAM_0[128]        _at_ 0xF900;
#endif
#if(_TMDS_SUPPORT)
BYTE xdata MCU_DDCRAM_1[128]        _at_ 0xF980;
#endif
#endif

BYTE xdata MCU_PIN_SHARE0_FF00      _at_ 0xFF00;
BYTE xdata MCU_PIN_SHARE1_FF01      _at_ 0xFF01;
BYTE xdata MCU_PIN_SHARE2_FF02      _at_ 0xFF02;
BYTE xdata MCU_PORT5_OE_FF03        _at_ 0xFF03;
BYTE xdata MCU_PORT6_OE_FF04        _at_ 0xFF04;
BYTE xdata MCU_PORT7_OE_FF05        _at_ 0xFF05;
BYTE xdata MCU_PORT1_TYPE_FF09      _at_ 0xFF09;

BYTE xdata MCU_PORT50_FF50[8]       _at_ 0xFF50;
BYTE xdata MCU_PORT60_FF58[8]       _at_ 0xFF58;
BYTE xdata MCU_PORT76_77_FF60[2]    _at_ 0xFF60;

BYTE xdata MCU_LVRST_CTRL_FF0A      _at_ 0xFF0A;
BYTE xdata MCU_ADC_CTRL_FF0B        _at_ 0xFF0B;
BYTE xdata MCU_ADC0_RESULT_FF0C     _at_ 0xFF0C;
BYTE xdata MCU_ADC1_RESULT_FF0D     _at_ 0xFF0D;
BYTE xdata MCU_ADC2_RESULT_FF0E     _at_ 0xFF0E;
BYTE xdata MCU_ADC3_RESULT_FF0F     _at_ 0xFF0F;

BYTE xdata MCU_PLL_CTRL_FF10        _at_ 0xFF10;
BYTE xdata MCU_PLL_FILTER_CTRL_FF11 _at_ 0xFF11;
BYTE xdata MCU_PLL_M_N_DIV_FF12     _at_ 0xFF12;
BYTE xdata MCU_REGULATOR_CTRL_FF13  _at_ 0xFF13;

BYTE xdata MCU_ADC_DDC_ENA_FF20     _at_ 0xFF20;
BYTE xdata MCU_ADC_DDC_CTRL_FF21    _at_ 0xFF21;
BYTE xdata MCU_DVI_DDC_ENA_FF23     _at_ 0xFF23;
BYTE xdata MCU_DVI_DDC_CTRL_FF24    _at_ 0xFF24;
BYTE xdata MCU_DDCRAM_CTRL_FF26     _at_ 0xFF26;

BYTE xdata MCU_I2C_SET_SLAVE_FF27   _at_ 0xFF27;
BYTE xdata MCU_I2C_SUB_IN_FF28      _at_ 0xFF28;
BYTE xdata MCU_I2C_DATA_IN_FF29     _at_ 0xFF29;
BYTE xdata MCU_I2C_DATA_OUT_FF2A    _at_ 0xFF2A;
BYTE xdata MCU_I2C_STATUS_FF2B      _at_ 0xFF2B;
BYTE xdata MCU_I2C_IRQ_CTRL_FF2C    _at_ 0xFF2C;

BYTE xdata MCU_PWM_CLK_CTRL_FF30    _at_ 0xFF30;
BYTE xdata MCU_PWM_DIV_N_FF31       _at_ 0xFF31;
BYTE xdata MCU_PWM0_DUTY_WIDTH_FF32 _at_ 0xFF32;
BYTE xdata MCU_PWM1_DUTY_WIDTH_FF33 _at_ 0xFF33;
BYTE xdata MCU_PWM2_DUTY_WIDTH_FF34 _at_ 0xFF34;
BYTE xdata MCU_PWM_SRC_SELECT_FF35  _at_ 0xFF35;
BYTE xdata MCU_WATCHDOG_TIMER_FF36  _at_ 0xFF36;

BYTE xdata MCU_ISP_SLAVE_ADDR_FF37  _at_ 0xFF37;
BYTE xdata MCU_OPTION_FF38          _at_ 0xFF38;

BYTE xdata MCU_FC_PAGE_ERASE_FF39   _at_ 0xFF39;
BYTE xdata MCU_RAM_TEST_FF3A        _at_ 0xFF3A;
BYTE xdata MCU_FC_MASS_ERASE0_FF90  _at_ 0xFF90;
BYTE xdata MCU_FC_PAGE_ERASE1_FF91  _at_ 0xFF91;
BYTE xdata MCU_FC_PR_CRC_ISP0_FF92  _at_ 0xFF92;
BYTE xdata MCU_FC_PR_CRC_ISP1_FF93  _at_ 0xFF93;
BYTE xdata MCU_FC_PD_ISP_FF94       _at_ 0xFF94;
BYTE xdata MCU_FC_R_CRC_ISP0_FFA0   _at_ 0xFFA0;
BYTE xdata MCU_FC_R_CRC_ISP1_FFA1   _at_ 0xFFA1;
BYTE xdata MCU_F_R_CRC_ISP0_FFA2    _at_ 0xFFA2;
BYTE xdata MCU_F_R_CRC_ISP1_FFA3    _at_ 0xFFA3;
BYTE xdata MCU_FT_CTRL1_FFB0        _at_ 0xFFB0;
BYTE xdata MCU_FT_CTRL2_FFB1        _at_ 0xFFB1;
BYTE xdata MCU_FT_CTRL3_FFB2        _at_ 0xFFB2;
BYTE xdata MCU_FT_CTRL4_FFB3        _at_ 0xFFB3;
BYTE xdata MCU_FT_CTRL5_FFB4        _at_ 0xFFB4;
BYTE xdata MCU_DEBUG_MODE_CTRL_FFC0 _at_ 0xFFC0;

#elif(_MCU_TYPE == _STK_6021)

BYTE xdata MCU_PADOPT_F50              _at_ 0xF50;
BYTE xdata MCU_PADOPT_F51              _at_ 0xF51;
BYTE xdata MCU_PADOPT_F56              _at_ 0xF56;
BYTE xdata MCU_ADC_F10                 _at_ 0xF10;
BYTE xdata MCU_DAC_F20[5]              _at_ 0xF20;

#else

    #error  Error MCU definition, add new definition in mcu.h

#endif
//--------------------------------------------------
// Function Prototypes
//--------------------------------------------------
void CMcuInitial(void);


#else

//--------------------------------------------------
// Extern Global Variables
//--------------------------------------------------
#if(_MCU_TYPE == _MYSON_MTV312)

extern BYTE xdata MCU_PADMODE_F50;
extern BYTE xdata MCU_PADMODE_F51;
extern BYTE xdata MCU_PADMODE_F52;
extern BYTE xdata MCU_PADMODE_F53;
extern BYTE xdata MCU_PADMODE_F54;
extern BYTE xdata MCU_PADMODE_F55;
extern BYTE xdata MCU_OPTION_F56;
extern BYTE xdata MCU_PORT4_F58[3];
extern BYTE xdata MCU_PORT5_F30[7];
extern BYTE xdata MCU_PORT6_F38[8];
extern BYTE xdata MCU_DAC_F20[14];
extern BYTE xdata MCU_HVSTUS_F40;
extern BYTE xdata MCU_HCNTH_F41;
extern BYTE xdata MCU_HCNTL_F42;
extern BYTE xdata MCU_VCNTH_F43;
extern BYTE xdata MCU_VCNTL_F44;
extern BYTE xdata MCU_HCTRL_F40[5];
extern BYTE xdata MCU_INTFLG_F48;
extern BYTE xdata MCU_INTEN_F49;
extern BYTE xdata MCU_IICCTR_F00;
extern BYTE xdata MCU_IICSTUS_F01;
extern BYTE xdata MCU_INTFLG_F03;
extern BYTE xdata MCU_INTEN_F04;
extern BYTE xdata MCU_MBUF_F05;
extern BYTE xdata MCU_DDCCTR_F06;
extern BYTE xdata MCU_SLVAADR_F07;
extern BYTE xdata MCU_RCTXBBUF_F08;
extern BYTE xdata MCU_SLVBADR_F07;
extern BYTE xdata MCU_ADC_F10;
extern BYTE xdata MCU_WDT_F18;
extern BYTE xdata MCU_ISPSLV_F0B;
extern BYTE xdata MCU_ISPEN_F0C;

#elif(_MCU_TYPE == _MYSON_MTV512)

#if (_DDC_TYPE == _DDC_MTV512)
#if(_VGA_SUPPORT)
extern BYTE xdata MCU_DDCRAM_0[128];
#endif
#if(_TMDS_SUPPORT)
extern BYTE xdata MCU_DDCRAM_1[128];
#endif
#endif
extern BYTE xdata MCU_PADMODE_F50;
extern BYTE xdata MCU_PADMODE_F51;
extern BYTE xdata MCU_PADMODE_F52;
extern BYTE xdata MCU_PADMODE_F53;
extern BYTE xdata MCU_PADMODE_F54;
extern BYTE xdata MCU_PADMODE_F55;
extern BYTE xdata MCU_OPTION_F56;
extern BYTE xdata MCU_PADMODE_F5E;
extern BYTE xdata MCU_PADMODE_F5F;
extern BYTE xdata MCU_PORT5_F30[8];
extern BYTE xdata MCU_PORT6_F38[8];
extern BYTE xdata MCU_PORT7_F76[2];
extern BYTE xdata MCU_DAC_F20[5];
extern BYTE xdata MCU_IICCTR_F00;
extern BYTE xdata MCU_IICSTUS_F01;
extern BYTE xdata MCU_INTFLG_F03;
extern BYTE xdata MCU_INTEN_F04;
extern BYTE xdata MCU_DDCCTRA1_F06;
extern BYTE xdata MCU_SLVA1ADR_F07;
extern BYTE xdata MCU_RCTXBBUF_F08;
extern BYTE xdata MCU_SLVBADR_F09;
extern BYTE xdata MCU_CTRSLVB_F0A;
extern BYTE xdata MCU_DDCCTRA2_F86;
extern BYTE xdata MCU_SLVA2ADR_F87;
extern BYTE xdata MCU_ADC_F10;
extern BYTE xdata MCU_WDT_F18;
extern BYTE xdata MCU_ETCTR_F88;
extern BYTE xdata MCU_ETMOD_F89;
extern BYTE xdata MCU_THET_F8A;
extern BYTE xdata MCU_TLET_F8B;
extern BYTE xdata MCU_RCAPETH_F8C;
extern BYTE xdata MCU_RCAPETL_F8D;
extern BYTE xdata MCU_EINT1PEN_F8E;
extern BYTE xdata MCU_INTFLG_F48;
extern BYTE xdata MCU_INTFLG_F49;

#elif(_MCU_TYPE == _RTD_2120)

#if(_MEMORY_LOCATION == _FLASH)
extern BYTE xdata MCU_FLASH[1024 * (_END_PAGE - _START_PAGE + 2)];
#endif

#if (_DDC_TYPE == _DDC_RTD2120)
#if(_VGA_SUPPORT)
extern BYTE xdata MCU_DDCRAM_0[128];
#endif
#if(_TMDS_SUPPORT)
extern BYTE xdata MCU_DDCRAM_1[128];
#endif
#endif

extern BYTE xdata MCU_PIN_SHARE0_FF00;
extern BYTE xdata MCU_PIN_SHARE1_FF01;
extern BYTE xdata MCU_PIN_SHARE2_FF02;
extern BYTE xdata MCU_PORT5_OE_FF03;
extern BYTE xdata MCU_PORT6_OE_FF04;
extern BYTE xdata MCU_PORT7_OE_FF05;
extern BYTE xdata MCU_PORT1_TYPE_FF09;

extern BYTE xdata MCU_PORT50_FF50[8];
extern BYTE xdata MCU_PORT60_FF58[8];
extern BYTE xdata MCU_PORT76_77_FF60[2];

extern BYTE xdata MCU_LVRST_CTRL_FF0A;
extern BYTE xdata MCU_ADC_CTRL_FF0B;
extern BYTE xdata MCU_ADC0_RESULT_FF0C;
extern BYTE xdata MCU_ADC1_RESULT_FF0D;
extern BYTE xdata MCU_ADC2_RESULT_FF0E;
extern BYTE xdata MCU_ADC3_RESULT_FF0F;

extern BYTE xdata MCU_PLL_CTRL_FF10;
extern BYTE xdata MCU_PLL_FILTER_CTRL_FF11;
extern BYTE xdata MCU_PLL_M_N_DIV_FF12;
extern BYTE xdata MCU_REGULATOR_CTRL_FF13;

extern BYTE xdata MCU_ADC_DDC_ENA_FF20;
extern BYTE xdata MCU_ADC_DDC_CTRL_FF21;
extern BYTE xdata MCU_DVI_DDC_ENA_FF23;
extern BYTE xdata MCU_DVI_DDC_CTRL_FF24;
extern BYTE xdata MCU_DDCRAM_CTRL_FF26;

extern BYTE xdata MCU_I2C_SET_SLAVE_FF27;
extern BYTE xdata MCU_I2C_SUB_IN_FF28;
extern BYTE xdata MCU_I2C_DATA_IN_FF29;
extern BYTE xdata MCU_I2C_DATA_OUT_FF2A;
extern BYTE xdata MCU_I2C_STATUS_FF2B;
extern BYTE xdata MCU_I2C_IRQ_CTRL_FF2C;

extern BYTE xdata MCU_PWM_CLK_CTRL_FF30;
extern BYTE xdata MCU_PWM_DIV_N_FF31;
extern BYTE xdata MCU_PWM0_DUTY_WIDTH_FF32;
extern BYTE xdata MCU_PWM1_DUTY_WIDTH_FF33;
extern BYTE xdata MCU_PWM2_DUTY_WIDTH_FF34;
extern BYTE xdata MCU_PWM_SRC_SELECT_FF35;
extern BYTE xdata MCU_WATCHDOG_TIMER_FF36;

extern BYTE xdata MCU_ISP_SLAVE_ADDR_FF37;
extern BYTE xdata MCU_OPTION_FF38;

extern BYTE xdata MCU_FC_PAGE_ERASE_FF39;
extern BYTE xdata MCU_RAM_TEST_FF3A;
extern BYTE xdata MCU_FC_MASS_ERASE0_FF90;
extern BYTE xdata MCU_FC_PAGE_ERASE1_FF91;
extern BYTE xdata MCU_FC_PR_CRC_ISP0_FF92;
extern BYTE xdata MCU_FC_PR_CRC_ISP1_FF93;
extern BYTE xdata MCU_FC_PD_ISP_FF94;
extern BYTE xdata MCU_FC_R_CRC_ISP0_FFA0;
extern BYTE xdata MCU_FC_R_CRC_ISP1_FFA1;
extern BYTE xdata MCU_F_R_CRC_ISP0_FFA2;
extern BYTE xdata MCU_F_R_CRC_ISP1_FFA3;
extern BYTE xdata MCU_FT_CTRL1_FFB0;
extern BYTE xdata MCU_FT_CTRL2_FFB1;
extern BYTE xdata MCU_FT_CTRL3_FFB2;
extern BYTE xdata MCU_FT_CTRL4_FFB3;
extern BYTE xdata MCU_FT_CTRL5_FFB4;
extern BYTE xdata MCU_DEBUG_MODE_CTRL_FFC0;


#elif(_MCU_TYPE == _STK_6021)

extern BYTE xdata MCU_PADOPT0;
extern BYTE xdata MCU_PADOPT1;
extern BYTE xdata MCU_PADOPT2;
extern BYTE xdata MCU_ADC_F10;
extern BYTE xdata MCU_DAC_F20[5];

#endif
//--------------------------------------------------
// Extern Function Prototypes
//--------------------------------------------------
extern void CMcuInitial(void);


#endif


//----------------------------------------------------------------------------------------------------

