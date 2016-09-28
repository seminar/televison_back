////////////////////////////////////////////////////////////////////////////
//         Copyright of Vector Co.,Ltd.                                   //
//                                                                        //
//                                                                        //
//                       Video Decoder function                           //
//   Ver: 6.20                                                            //
//   Create file time: 2006.5.15                                          //
//   End modify time: 2007.2.27                                           //
//   For RTD2523B/RTD2553V/RTD2525L                                       //
////////////////////////////////////////////////////////////////////////////



// Definitions for Vedio Decoder
#define _VDC_NONE          0   // 0:  No vedio decoder available

#define _VDC_TVP5146       1   // 1:  TVP5146 chip
#define _VDC_TVP5150       2   // 2:  TVP5150 chip

#define _VDC_3230          3   // 3:  MICRONAS3230 chip

#define _VDC_SAA7111       4   // 4:  SAA7111 chip
#define _VDC_SAA7113       5   // 5:  SAA7113 chip
#define _VDC_SAA7114       6   // 6:  SAA7114 chip
#define _VDC_SAA7115       7   // 7:  SAA7115 chip
#define _VDC_SAA7118       8   // 8:  SAA7118 chip

#define _VDC_TW9905        9   // 9:  TECHWELL TW9905 chip
#define _VDC_TW9906        10  // 10: TECHWELL TW9906 chip
#define _VDC_TW9908C       11  // 11: TECHWELL TW9908C chip
#define _VDC_TW9909        12  // 12: TECHWELL TW9909 chip
#define _VDC_TW9910        13  // 13: Techwell TW9910

#define _VDC_ADV7181B      14  // 14: Analog Devices ADV7181B
#define _VDC_ADV7180LQFP   15  // 15: Analog Devices ADV7180 LQFP 64 pin package
#define _VDC_ADV7180LFCSP  16  // 16: Analog Devices ADV7180 LFCSP 40 pin package

#define _VDC_RTD2612       17  // 17: Realtek RTD2612 chip
#define _VDC_RTD2613       18  // 18: Realtek RTD2613 chip

#define _VDC_TB1334        19  // 19: Toshiba TB1334

#define _VIDEO_CHIP        _VDC_TB1334


// definitions for public
#define _VDC_FREE_RUN_MODE_TO_AUTO     0
#define _VDC_FREE_RUN_MODE_TO_50HZ     1
#define _VDC_FREE_RUN_MODE_TO_60HZ     2


////////////////////////////////////// TVP 5146 ///////////////////////////////////////
#if(_VIDEO_CHIP == _VDC_TVP5146)
// Definitions for Vedio Decoder input channel
#define _CVBS_CHANNEL1A            0x01  // Vl_1_A  TVP5146 PIN80
#define _CVBS_CHANNEL1B            0x02  // Vl_1_B  TVP5146 PIN1
#define _CVBS_CHANNEL1C            0x03  // Vl_1_C  TVP5146 PIN2
#define _CVBS_CHANNEL2A            0x04  // Vl_2_A  TVP5146 PIN7
#define _CVBS_CHANNEL2B            0x05  // Vl_2_B  TVP5146 PIN8
#define _CVBS_CHANNEL2C            0x06  // Vl_2_C  TVP5146 PIN9
#define _CVBS_CHANNEL3A            0x07  // Vl_3_A  TVP5146 PIN16
#define _CVBS_CHANNEL3B            0x08  // Vl_3_B  TVP5146 PIN17
#define _CVBS_CHANNEL3C            0x09  // Vl_3_C  TVP5146 PIN18
#define _CVBS_CHANNEL4A            0x0a  // Vl_4_A  TVP5146 PIN23

#define _S_VIDEO_CHANNEL21A        0x0b  // Vl_2_A(Y),Vl_1_A(C)
#define _S_VIDEO_CHANNEL21B        0x0c  // Vl_2_B(Y),Vl_1_B(C)
#define _S_VIDEO_CHANNEL21C        0x0d  // Vl_2_C(Y),Vl_1_C(C)
#define _S_VIDEO_CHANNEL23A        0x0e  // Vl_2_A(Y),Vl_3_A(C)
#define _S_VIDEO_CHANNEL23B        0x0f  // Vl_2_B(Y),Vl_3_B(C)
#define _S_VIDEO_CHANNEL23C        0x10  // Vl_2_C(Y),Vl_3_C(C)
#define _S_VIDEO_CHANNEL41A        0x11  // Vl_4_A(Y),Vl_1_A(C)
#define _S_VIDEO_CHANNEL41B        0x12  // Vl_4_A(Y),Vl_1_B(C)
#define _S_VIDEO_CHANNEL41C        0x13  // Vl_4_A(Y),Vl_1_C(C)
#define _S_VIDEO_CHANNEL43A        0x14  // Vl_4_A(Y),Vl_3_A(C)
#define _S_VIDEO_CHANNEL43B        0x15  // Vl_4_A(Y),Vl_3_B(C)
#define _S_VIDEO_CHANNEL43C        0x16  // Vl_4_A(Y),Vl_3_C(C)

#define _RGB_CHANNEL123A           0x17  // Vl_1_A(B),Vl_2_A(G),Vl_3_A(R)
#define _RGB_CHANNEL123B           0x18  // Vl_1_B(B),Vl_2_B(G),Vl_3_B(R)
#define _RGB_CHANNEL123C           0x19  // Vl_1_C(B),Vl_2_C(G),Vl_3_C(R)

#define _YPbPr_CHANNEL123A         0x1a  // Vl_1_A(Pb),Vl_2_A(Y),Vl_3_A(Pr)
#define _YPbPr_CHANNEL123B         0x1b  // Vl_1_B(Pb),Vl_2_B(Y),Vl_3_B(Pr)
#define _YPbPr_CHANNEL123C         0x1c  // Vl_1_C(Pb),Vl_2_C(Y),Vl_3_C(Pr)

#define _SCART_RGB_CHANNEL1234A    0x1d  // Vl_1_A(B),Vl_2_A(G),Vl_3_A(R),Vl_4_A(CVBS)
#define _SCART_RGB_CHANNEL1234B    0x1e  // Vl_1_B(B),Vl_2_B(G),Vl_3_B(R),Vl_4_A(CVBS)
#define _SCART_RGB_CHANNEL1234C    0x1f  // Vl_1_C(B),Vl_2_C(G),Vl_3_C(R),Vl_4_A(CVBS)
#define _SCART_YPrPb_CHANNEL1234A  0x20  // Vl_1_A(Pb),Vl_2_A(Y),Vl_3_A(Pr),Vl_4_A(CVBS)
#define _SCART_YPrPb_CHANNEL1234B  0x21  // Vl_1_B(Pb),Vl_2_B(Y),Vl_3_B(Pr),Vl_4_A(CVBS)
#define _SCART_YPrPb_CHANNEL1234C  0x22  // Vl_1_C(Pb),Vl_2_C(Y),Vl_3_C(Pr),Vl_4_A(CVBS)

#define _NONE_INPUT                0x0f

#define _AV_CHANNEL                _CVBS_CHANNEL1A
#define _SV_CHANNEL                _S_VIDEO_CHANNEL21A
#define _TV_CHANNEL                _CVBS_CHANNEL1C


#define _VIDEODEVICE               0xba
///////////////////////////////////////////// TW9905 /////////////////////////////////////////
#elif(_VIDEO_CHIP == _VDC_TW9905)
// Definitions for Vedio Decoder input channel
#define _FC27_MODE                 0x40  // Inputcrystal clock frequency is 27MHZ(Normal)
#define _SQUARE_PIXEL_MODE         0x00  // Square pixel mode.Must use 24.54MHZ for 60HZ field rate source or 29.5MHz for 50Hz field rate source

#define _IF_COMPONENT              0x20  // Component video decoding
#define _IF_SVIDEO                 0x10  // S-video decoding
#define _IF_COMPOSITE              0x00  // Composite video decoding(Normal)

#define _MUX0_INPUT                0x00  // Route MUX0 input to MXOUT(Normal)
#define _MUX1_INPUT                0x04  // Route MUX1 input to MXOUT
#define _MUX2_INPUT                0x08  // Route MUX2 input to MXOUT
#define _MUX3_INPUT                0x0c  // Route MUX3 input to MXOUT
#define _MUX4_INPUT                0x80  // Route MUX4 input to MXOUT
#define _MUX5_INPUT                0x84  // Route MUX5 input to MXOUT

#define _CHROMA_CHANNEL_CIN0       0x00  // Select chroma channel input CIN0(Normal)
#define _CHROMA_CHANNEL_CIN1       0x02  // Select chroma channel input CIN1

#define _V_CHANNEL_PRIN0           0x00  // Select V channel input PRIN0(Normal)
#define _V_CHANNEL_PRIN1           0x01  // Select V channel input PRIN1

#define _NONE_INPUT                0x0f

#define _AV_CHANNEL                (_FC27_MODE | _IF_COMPOSITE | _MUX0_INPUT | _CHROMA_CHANNEL_CIN0 | _V_CHANNEL_PRIN0) // Fullerton demo set
#define _SV_CHANNEL                (_FC27_MODE | _IF_SVIDEO    | _MUX1_INPUT | _CHROMA_CHANNEL_CIN0 | _V_CHANNEL_PRIN0) // Fullerton demo set
#define _TV_CHANNEL                (_FC27_MODE | _IF_COMPOSITE | _MUX2_INPUT | _CHROMA_CHANNEL_CIN0 | _V_CHANNEL_PRIN0) // Fullerton demo set

#define _VIDEODEVICE               0x88

//////////////////////////////////////////////////// TW9906 //////////////////////////////////////////////////////////
#elif(_VIDEO_CHIP == _VDC_TW9906)
// Definitions for Vedio Decoder input channel
#define _FC27_MODE                 0x40  // Inputcrystal clock frequency is 27MHZ(Normal)
#define _SQUARE_PIXEL_MODE         0x00  // Square pixel mode.Must use 24.54MHZ for 60HZ field rate source or 29.5MHz for 50Hz field rate source

#define _IF_COMPONENT              0x20  // Component video decoding
#define _IF_SVIDEO                 0x10  // S-video decoding
#define _IF_COMPOSITE              0x00  // Composite video decoding(Normal)

#define _MUX0_INPUT                0x00  // Route MUX0 input to MXOUT(Normal)
#define _MUX1_INPUT                0x04  // Route MUX1 input to MXOUT
#define _MUX2_INPUT                0x08  // Route MUX2 input to MXOUT
#define _MUX3_INPUT                0x0c  // Route MUX3 input to MXOUT
#define _MUX4_VIN1_INPUT           0x80  // Route MUX4 or VIN1 input to MXOUT

#define _CHROMA_CHANNEL_CIN0       0x00  // Select chroma channel input CIN0(Normal)
#define _CHROMA_CHANNEL_CIN1       0x02  // Select chroma channel input CIN1

#define _V_CHANNEL_VIN0            0x00  // Select V channel input VIN0(Normal)
#define _V_CHANNEL_VIN1            0x01  // Select V channel input VIN1

#define _NONE_INPUT                0x0f

#define _AV_CHANNEL                (_FC27_MODE | _IF_COMPOSITE | _MUX1_INPUT | _CHROMA_CHANNEL_CIN0 | _V_CHANNEL_VIN0)
#define _SV_CHANNEL                (_FC27_MODE | _IF_SVIDEO    | _MUX2_INPUT | _CHROMA_CHANNEL_CIN0 | _V_CHANNEL_VIN0) 
#define _TV_CHANNEL                (_FC27_MODE | _IF_COMPOSITE | _MUX0_INPUT | _CHROMA_CHANNEL_CIN0 | _V_CHANNEL_VIN0)

#define _VIDEODEVICE               0x8a

//////////////////////////////////////////////////// TW9910 //////////////////////////////////////////////////////////
#elif(_VIDEO_CHIP == _VDC_TW9910)
// Definitions for Vedio Decoder input channel
#define _FC27_MODE                 0x40  // Inputcrystal clock frequency is 27MHZ(Normal)
#define _SQUARE_PIXEL_MODE         0x00  // Square pixel mode.Must use 24.54MHZ for 60HZ field rate source or 29.5MHz for 50Hz field rate source

#define _IF_COMPONENT              0x20  // Component video decoding
#define _IF_SVIDEO                 0x10  // S-video decoding
#define _IF_COMPOSITE              0x00  // Composite video decoding(Normal)

#define _MUX0_INPUT                0x00  // Route MUX0 input to MXOUT(Normal)
#define _MUX1_INPUT                0x04  // Route MUX1 input to MXOUT
#define _MUX2_INPUT                0x08  // Route MUX2 input to MXOUT
#define _MUX3_INPUT                0x0c  // Route MUX3 input to MXOUT

#define _NONE_INPUT                0x0f

#define _AV_CHANNEL                (_FC27_MODE | _IF_COMPOSITE | _MUX1_INPUT)
#define _SV_CHANNEL                (_FC27_MODE | _IF_SVIDEO    | _MUX0_INPUT) 
#define _TV_CHANNEL                (_FC27_MODE | _IF_COMPOSITE | _MUX2_INPUT)

#define _VIDEODEVICE               0x8a
///////////////////////////////////////////// TW9908C ///////////////////////////////////////////////////////
#elif(_VIDEO_CHIP == _VDC_TW9908C)
// Definitions for Vedio Decoder input channel
#define _FC27_MODE                 0x40  // Inputcrystal clock frequency is 27MHZ(Normal)
#define _SQUARE_PIXEL_MODE         0x00  // Square pixel mode.Must use 24.54MHZ for 60HZ field rate source or 29.5MHz for 50Hz field rate source

#define _IF_COMPONENT              0x20  // Component video decoding
#define _IF_SVIDEO                 0x10  // S-video decoding
#define _IF_COMPOSITE              0x00  // Composite video decoding(Normal)

#define _MUX0_INPUT                0x00  // Route MUX0 input to MXOUT(Normal)
#define _MUX1_INPUT                0x04  // Route MUX1 input to MXOUT
#define _MUX2_INPUT                0x08  // Route MUX2 input to MXOUT
#define _MUX3_INPUT                0x0c  // Route MUX3 input to MXOUT
#define _MUX4_INPUT                0x80  // Route MUX4 input to MXOUT
#define _MUX5_INPUT                0x84  // Route MUX5 input to MXOUT

#define _CHROMA_CHANNEL_CIN0       0x00  // Select chroma channel input CIN0(Normal)
#define _CHROMA_CHANNEL_CIN1       0x02  // Select chroma channel input CIN1
        
#define _FB0_INPUT                 0x00  // Select V channel input PRIN0(Normal)
#define _FB1_INPUT                 0x01  // Select V channel input PRIN1

#define _MIX_RGB_YC_OUTPUT_OFF     0x00
#define _MIX_RGB_OUTPUT_ON         0x01
#define _RGB_OUTPUT_ONLY           0x02
#define _YC_OUTPUT_ONLY            0x03

#define _NONE_INPUT                0x0f

#define _AV_CHANNEL                (_FC27_MODE | _IF_COMPOSITE | _MUX0_INPUT | _CHROMA_CHANNEL_CIN0 | _FB0_INPUT) 
#define _SV_CHANNEL                (_FC27_MODE | _IF_SVIDEO    | _MUX1_INPUT | _CHROMA_CHANNEL_CIN0 | _FB0_INPUT) 
#define _TV_CHANNEL                (_FC27_MODE | _IF_COMPOSITE | _MUX3_INPUT | _CHROMA_CHANNEL_CIN0 | _FB1_INPUT)
#define _YUV_CHANNEL               (_FC27_MODE | _IF_COMPONENT | _MUX4_INPUT | _CHROMA_CHANNEL_CIN0 | _FB0_INPUT) 
#define _SCART_CHANNEL             (_FC27_MODE | _IF_COMPOSITE | _MUX2_INPUT | _CHROMA_CHANNEL_CIN0 | _FB1_INPUT)

#define _VIDEODEVICE               0x8a

/////////////////////////////////////////////////// TW9909 /////////////////////////////////////////////////////
#elif(_VIDEO_CHIP == _VDC_TW9909)
// Definitions for Vedio Decoder input channel
#define _FC27_MODE                 0x40  // Inputcrystal clock frequency is 27MHZ(Normal)
#define _SQUARE_PIXEL_MODE         0x00  // Square pixel mode.Must use 24.54MHZ for 60HZ field rate source or 29.5MHz for 50Hz field rate source

#define _IF_PROGRESSIVE            0x30  // Progressive video decoding
#define _IF_COMPONENT              0x20  // Component video decoding
#define _IF_SVIDEO                 0x10  // S-video decoding
#define _IF_COMPOSITE              0x00  // Composite video decoding(Normal)

#define _MUX0_INPUT                0x00  // Route MUX0 input to MXOUT(Normal)
#define _MUX1_INPUT                0x04  // Route MUX1 input to MXOUT
#define _MUX2_INPUT                0x08  // Route MUX2 input to MXOUT
#define _MUX3_INPUT                0x0c  // Route MUX3 input to MXOUT
#define _MUX4_VIN1_INPUT           0x80  // Route MUX4 or VIN1 input to MXOUT

#define _CHROMA_CHANNEL_CIN0       0x00  // Select chroma channel input CIN0(Normal)
#define _CHROMA_CHANNEL_CIN1       0x02  // Select chroma channel input CIN1

#define _FB0_RIN0_GIN0_BIN0        0x00  // Select FB0/RIN0/GIN0/BIN0 channel input
#define _FB1_RIN1_GIN1_BIN1        0x01  // Select FB1/RIN1/GIN1/BIN1 channel input

#define _NONE_INPUT                0x0f

#define _AV_CHANNEL                (_FC27_MODE | _IF_COMPOSITE | _MUX0_INPUT | _CHROMA_CHANNEL_CIN0 | _FB0_RIN0_GIN0_BIN0)
#define _SV_CHANNEL                (_FC27_MODE | _IF_SVIDEO    | _MUX1_INPUT | _CHROMA_CHANNEL_CIN0 | _FB0_RIN0_GIN0_BIN0) 
#define _TV_CHANNEL                (_FC27_MODE | _IF_COMPOSITE | _MUX3_INPUT | _CHROMA_CHANNEL_CIN0 | _FB0_RIN0_GIN0_BIN0)
#define _YUV_CHANNEL               (_FC27_MODE | _IF_COMPOSITE | _MUX0_INPUT | _CHROMA_CHANNEL_CIN1 | _FB0_RIN0_GIN0_BIN0)

#define _VIDEODEVICE               0x8a
/////////////////////////////////////////////////// TVP 5150 /////////////////////////////////////////////////////
#elif(_VIDEO_CHIP == _VDC_TVP5150)
// Definitions for Vedio Decoder input channel
#define _CHANNEL_NONE              0x00
#define _CVBS_CIP1A                0x01
#define _CVBS_CIP1B                0x02
#define _S_VIDEO_12A               0x03

#define _NONE_INPUT                0x0f

#define _AV_CHANNEL                _CVBS_CIP1A
#define _SV_CHANNEL                _CHANNEL_NONE   // Not use
#define _TV_CHANNEL                _CVBS_CIP1B

#define _VIDEODEVICE               0xba   

//////////////////////////////////////////////////// ADV7181B //////////////////////////////////////////////////////////
#elif(_VIDEO_CHIP == _VDC_ADV7181B)
// Definitions for Vedio Decoder input channel
#define _FC27_MODE                 0x40  // Inputcrystal clock frequency is 27MHZ(Normal)
#define _SQUARE_PIXEL_MODE         0x00  // Square pixel mode.Must use 24.54MHZ for 60HZ field rate source or 29.5MHz for 50Hz field rate source

#define _IF_COMPONENT              0x20  // Component video decoding
#define _IF_SVIDEO                 0x10  // S-video decoding
#define _IF_COMPOSITE              0x00  // Composite video decoding(Normal)

#define _MUX0_INPUT                0x00  // Route MUX0 input to MXOUT(Normal)
#define _MUX1_INPUT                0x04  // Route MUX1 input to MXOUT
#define _MUX2_INPUT                0x08  // Route MUX2 input to MXOUT
#define _MUX3_INPUT                0x0c  // Route MUX3 input to MXOUT
#define _MUX4_VIN1_INPUT           0x80  // Route MUX4 or VIN1 input to MXOUT

#define _CHROMA_CHANNEL_CIN0       0x00  // Select chroma channel input CIN0(Normal)
#define _CHROMA_CHANNEL_CIN1       0x02  // Select chroma channel input CIN1

#define _V_CHANNEL_VIN0            0x00  // Select V channel input VIN0(Normal)
#define _V_CHANNEL_VIN1            0x01  // Select V channel input VIN1

#define _NONE_INPUT                0x0f

#define _AV_CHANNEL                1//(_FC27_MODE | _IF_COMPOSITE | _MUX1_INPUT | _CHROMA_CHANNEL_CIN0 | _V_CHANNEL_VIN0)
#define _SV_CHANNEL                2//(_FC27_MODE | _IF_SVIDEO    | _MUX2_INPUT | _CHROMA_CHANNEL_CIN0 | _V_CHANNEL_VIN0) 
#define _TV_CHANNEL                3//(_FC27_MODE | _IF_COMPOSITE | _MUX0_INPUT | _CHROMA_CHANNEL_CIN0 | _V_CHANNEL_VIN0)

#define _ADDRESS_40                0x40
#define _ADDRESS_41                0x41
#define _ADDRESS_42                0x42
#define _ADDRESS_43                0x43

#define _VIDEODEVICE                _ADDRESS_42
   
//////////////////////////////////////////////////// ADV7181B //////////////////////////////////////////////////////////
#elif(_VIDEO_CHIP == _VDC_ADV7180LQFP)
// Definitions for Vedio Decoder input channel
#define _IF_COMPOSITE              0x00  // Composite video decoding(Normal)
#define _IF_SVIDEO                 0x80  // S-video decoding

// Definitions for CVBS input or Y/C C channel input
#define _CVBS_AIN1_INPUT           0x01  // AIN1 input
#define _CVBS_AIN2_INPUT           0x02  // AIN2 input
#define _CVBS_AIN3_INPUT           0x03  // AIN3 input
#define _CVBS_AIN4_INPUT           0x04  // AIN4 input
#define _CVBS_AIN5_INPUT           0x05  // AIN5 input
#define _CVBS_AIN6_INPUT           0x06  // AIN6 input

// Definitions for Y/C Y channel input
#define _YC_AIN1_INPUT             0x10  // AIN1 input
#define _YC_AIN2_INPUT             0x20  // AIN2 input
#define _YC_AIN3_INPUT             0x30  // AIN3 input
#define _YC_AIN4_INPUT             0x40  // AIN4 input
#define _YC_AIN5_INPUT             0x50  // AIN5 input
#define _YC_AIN6_INPUT             0x60  // AIN6 input

#define _NONE_INPUT                0x0f

#define _AV_CHANNEL                1//(_IF_COMPOSITE | _AIN5_INPUT)
#define _SV_CHANNEL                2//(_IF_SVIDEO    | _YC_AIN1_INPUT | _CVBS_AIN4_INPUT)
#define _TV_CHANNEL                3//(_IF_COMPOSITE | _AIN6_INPUT)

#define _ADDRESS_40                0x40
#define _ADDRESS_41                0x41
#define _ADDRESS_42                0x42
#define _ADDRESS_43                0x43

#define _VIDEODEVICE                _ADDRESS_42

//////////////////////////////////////////////////// RTD2612 //////////////////////////////////////////////////////////
#elif(_VIDEO_CHIP == _VDC_RTD2612)
// Definitions for Vedio Decoder input channel
//--------------- ADC 0 ---------------
// ADC 0 only for Y
#define _ADC0_AI00_INPUT           0x00
#define _ADC0_AI01_INPUT           0x01

//--------------- ADC 1 ---------------
#define _ADC1_AI10_INPUT           0x02
#define _ADC1_AI11_INPUT           0x03
#define _ADC1_AI12_INPUT           0x04
#define _ADC1_AI13_INPUT           0x05

//--------------- ADC 2 ---------------
#define _ADC2_AI20_INPUT           0x06
#define _ADC2_AI21_INPUT           0x07
#define _ADC2_AI22_INPUT           0x08
#define _ADC2_AI23_INPUT           0x09

//--------------- ADC 3 ---------------
#define _ADC3_AI30_INPUT           0x0a
#define _ADC3_AI31_INPUT           0x0b
#define _ADC3_AI32_INPUT           0x0c
#define _ADC3_AI33_INPUT           0x0d

#define _NONE_INPUT                0x0f

//                                 |    Y input            |  C input         |
#define _AV_CHANNEL                (_ADC0_AI00_INPUT << 4) |  _NONE_INPUT
#define _SV_CHANNEL                (_ADC3_AI31_INPUT << 4) |  _ADC2_AI20_INPUT
#define _TV_CHANNEL                (_ADC3_AI33_INPUT << 4) |  _NONE_INPUT

//-------------- YCbCr ----------------
//                                 |    Y input            |  Cr input        |
#define _YCBCR_CHANNEL_Y_CR        (_ADC0_AI01_INPUT << 4) |  _ADC2_AI23_INPUT
//                                 |    Cb input
#define _YCBCR_CHANNEL_CB          _ADC1_AI13_INPUT

#define _VIDEODEVICE               0x40

//////////////////////////////////////////////////// RTD2613 //////////////////////////////////////////////////////////
#elif(_VIDEO_CHIP == _VDC_RTD2613)
// Definitions for Vedio Decoder input channel
//--------------- ADC 0 ---------------
// ADC 0 not use in S-VIDEO C
#define _ADC0_AI00_INPUT           0x00
#define _ADC0_AI01_INPUT           0x01

//--------------- ADC 1 ---------------
#define _ADC1_AI10_INPUT           0x02
#define _ADC1_AI11_INPUT           0x03
#define _ADC1_AI12_INPUT           0x04
#define _ADC1_AI13_INPUT           0x05

//--------------- ADC 2 ---------------
#define _ADC2_AI20_INPUT           0x06
#define _ADC2_AI21_INPUT           0x07
#define _ADC2_AI22_INPUT           0x08
#define _ADC2_AI23_INPUT           0x09

//--------------- ADC 3 ---------------
#define _ADC3_AI30_INPUT           0x0a
#define _ADC3_AI31_INPUT           0x0b
#define _ADC3_AI32_INPUT           0x0c
#define _ADC3_AI33_INPUT           0x0d

#define _NONE_INPUT                0x0f

//                                 |    Y input            |  C input         |
#define _AV_CHANNEL                (_ADC0_AI01_INPUT << 4) |  _NONE_INPUT
#define _SV_CHANNEL                (_ADC2_AI23_INPUT << 4) |  _ADC1_AI13_INPUT
#define _TV_CHANNEL                (_ADC3_AI33_INPUT << 4) |  _NONE_INPUT

//                                 |    Y input            |  Cr input        |
#define _YCBCR_CHANNEL_Y_CR        (_ADC0_AI01_INPUT << 4) |  _ADC2_AI23_INPUT
//                                 |    Cb input
#define _YCBCR_CHANNEL_CB          _ADC1_AI13_INPUT

#define _VIDEODEVICE               0x40


//////////////////////////////////////////////////// TB1334 //////////////////////////////////////////////////////////
#elif(_VIDEO_CHIP == _VDC_TB1334)
// Definitions for Vedio Decoder input channel
// Input for CVBS
#define _CVBS_V1_INPUT             0x00
#define _CVBS_V2_INPUT             0x20
#define _CVBS_V3_INPUT             0x40
#define _CVBS_V4_INPUT             0x60

// Input for C
#define _CHROMA_C1                 0x01
#define _CHROMA_C2                 0x02

// Input for YCbCr
#define _YCBCR2_INPUT              0x0A  // Y: V1/V2   Pin46 = 0 or Y: * Pin 46 = 1
#define _YCBCR3_INPUT              0x0B  // Y: V3      Pin46 = 0

// Input for SCART
#define _SCART_INPUT               0x0E

#define _NONE_INPUT                0x0f

//                                 |    Y input     |  C input         |
#if(CMOS_CHIP_TYPE==PCB_2025LV13)
#define _AV_CHANNEL                _CVBS_V2_INPUT   |  _NONE_INPUT
#define _YCBCR_CHANNEL             _CVBS_V3_INPUT   |  _YCBCR3_INPUT
#define _DVD_CHANNEL              _CVBS_V3_INPUT   |  _CHROMA_C1  
#else
#define _AV_CHANNEL                _CVBS_V3_INPUT   |  _NONE_INPUT
#define _YCBCR_CHANNEL             _CVBS_V2_INPUT   |  _YCBCR3_INPUT
#define _DVD_CHANNEL              _CVBS_V2_INPUT   |  _CHROMA_C1  
#endif
#define _SV_CHANNEL                _CVBS_V4_INPUT   |  _CHROMA_C2
#define _TV_CHANNEL                _CVBS_V1_INPUT   |  _NONE_INPUT
#define _SCART_CHANNEL             _CVBS_V4_INPUT   |  _SCART_INPUT

#define _VIDEODEVICE               0x88

////////////////////////////////////////////// VIDEO NONE ////////////////////////////////////////////////
#elif(_VIDEO_CHIP != _VDC_NONE)
    #error  Definitions Code Trapped 

#endif

#if(_VIDEO_CHIP != _VDC_NONE)
#ifndef __VIDEO_CHIP__
#define __VIDEO_CHIP__

/*
 _______________________________________________________________________________________________________________________
|                                                                                                                       |
|                            Function gmi_CVideoCurrentColor() return data explain                                       |
|_______________________________________________________________________________________________________________________|
|\          |             |             |             |          |          |          |          |          |          |
|  \ Return |             |             |             |          |          |          |          |          |          | 
|    \ data |    0x00     |    0x01     |    0x02     |   0x03   |   0x04   |   0x05   |  0x06    |  0x07    |  0x08    |
|VDC   \    |             |             |             |          |          |          |          |          |          |
|  CHIP  \  | (bMode:0/1) | (bMode:0/1) | (bMode:0/1) |(bMode:1) |(bMode:1) |(bMode:1) |(bMode:1) |(bMode:1) |(bMode:1) |
|__________\|_____________|_____________|_____________|__________|__________|__________|__________|__________|__________| 
|           |             |    NTSC     |    PAL      |          |          |          |          |          |          |
| TW9905    | No signal   |    (M)      |(B,D,G,H,I)  | SECAM    | NTSC4.43 | PAL M    | PAL CN   | PAL 60   | Reserved |
|___________|_____________|_____________|_____________|__________|__________|__________|__________|__________|__________|  
|           |             |    NTSC     |    PAL      |          |          |          |          |          |          |
| TW9906    | No signal   |    (M)      |(B,D,G,H,I)  | SECAM    | NTSC4.43 | PAL M    | PAL CN   | PAL 60   | Reserved |
|___________|_____________|_____________|_____________|__________|__________|__________|__________|__________|__________|  
|           |             |    NTSC     |    PAL      |          |          |          |          |          |          |
|           |             |    NTSC     |    PAL      |          |          |          |          |          |          |
| TW9910    | No signal   |    (M)      |(B,D,G,H,I)  | Reserved | Reserved | Reserved | Reserved | Reserved | Reserved |
|___________|_____________|_____________|_____________|__________|__________|__________|__________|__________|__________|  
|           |             |    NTSC     |    PAL      |          |          |          |          |          |          |
| TW9908C   | No signal   |    (M)      |(B,D,G,H,I)  | SECAM    | NTSC4.43 | PAL M    | PAL CN   | PAL 60   | Reserved |
|___________|_____________|_____________|_____________|__________|__________|__________|__________|__________|__________|
|           |             |    NTSC     |    PAL      |          |          |          |          |          |          |
| TVP5146   | No signal   |   (M,J)     |(B,D,G,H,I,N)| Reserved | Reserved | Reserved | Reserved | Reserved | Reserved |
|___________|_____________|_____________|_____________|__________|__________|__________|__________|__________|__________|
|           |             |    NTSC     |    PAL      |          |          |          |          |          |          |
| TVP5150   | No signal   |   (M,J)     |(B,D,G,H,I,N)| Reserved | Reserved | Reserved | Reserved | Reserved | Reserved |
|___________|_____________|_____________|_____________|__________|__________|__________|__________|__________|__________|
|           |             |bMode 0: NTSC|bMode 0: PAL |          |          |          |          |          |          |
| ADV7181B  | No signal   |   1: NTSC-MJ|  1 :NTSC-443|  PAL-M   |  PAL-60  | PAL-BGHID|   SECAM  |  PAL N   | SECAM 525|
|___________|_____________|_____________|_____________|__________|__________|__________|__________|__________|__________|
|           |             |             |             |          |          |          |          |          |          |
| RTD2612/3 | No signal   |    NTSC     |     PAL     | Reserved | Reserved | Reserved | Reserved | Reserved | Reserved |
|___________|_____________|_____________|_____________|__________|__________|__________|__________|__________|__________|
|           |             |             |             |          |          |          |          |          |          |
| TB1334    | No signal   |    NTSC     |     PAL     | Reserved | Reserved | Reserved | Reserved | Reserved | Reserved |
|___________|_____________|_____________|_____________|__________|__________|__________|__________|__________|__________|
|           |             |             |             |          |          |          |          |          |          |
|           |             |             |             |          |          |          |          |          |          |
|___________|_____________|_____________|_____________|__________|__________|__________|__________|__________|__________|
*/

extern unsigned char VideoDecAddress;

extern void gmi_CI2CWriteVDCByte(const unsigned char ucAddress, const unsigned char ucWriteValue);
extern unsigned char gmi_CI2CReadVDCByte(const unsigned char ucAddress);
extern unsigned char gmi_CVideoCurrentColor(bit bMode);
extern void gmi_CInitialVDC(void);
extern void gmi_CVDCOutputDisable(void);
extern bit gmi_CModeLocked(void);
extern void gmi_CSelectInputChannel(unsigned char ucYCrChannel, unsigned char ucCbChannel);
extern void gmi_CAdjustVDCBrightness(const unsigned char ucVDCBrightness);
extern void gmi_CAdjustVDCContrast(const unsigned char ucVDCContrast);
extern void gmi_CAdjustVDCSaturation(const unsigned char ucVDCSaturation);
extern void gmi_CAdjustVDCHue(const unsigned char ucVDCHue);
extern void gmi_CSetVDCFreeRunMode(const unsigned char ucMode);


#if(_VIDEO_CHIP == _VDC_TW9908C)
// State:  MIX_RGB_YC_OUTPUT_OFF  Output from Y/C channel input only
//         MIX_RGB_OUTPUT_ON      Output from mixing of RGB and YC channels controlled by FB
//         RGB_OUTPUT_ONLY        Output from RGB channel input only(RIN1,GIN1,BIN1,FB0/FB1) input 
//         YC_OUTPUT_ONLY         Output from Y/C channel input only(RIN0,GIN0,BIN0,MUX0/MUX1/MUX2/MUX3/MUX4/MUX5) input 
extern void gmi_CRGBandYUVCtrl(const unsigned char ucState);
extern void gmi_CSetYUVHue(const unsigned char ucVDCHue);   // Set Sub-channel YUV mode Hue 
#endif
#endif
#endif


#if(0)
//-------- TVP5146 reset function ------------
void Reset_VDC(void)
{
    bVideo_PW=0; //Video enable
    Delay_Xms(200);
    bVideo_RST = 0;
    Delay_Xms(20);
    bVideo_RST = 1;
    Delay_Xms(20);
}

//-------- TW9903 reset function ------------
void Reset_VDC(void)
{
    bVideo_PW=0; //Video enable
    Delay_Xms(200);
    bVideo_RST = 0;
    Delay_Xms(20);
    bVideo_RST = 1;
    Delay_Xms(100); // Must delay 100ms,if not TW9903 can`t work
}

//-------- TW9905/TW9906/TW9908C/TVP5150/TW9910/RTD2610 reset function ------------
void Reset_VDC(void)
{
    bVIDEO_RESET = 0;   // VIDEO DECODER RESET PIN
    Delay_Xms(20);
    bVIDEO_RESET = 1;
#if(VIDEO_CHIP == VDC_TW9906)  // ONLY FOR TW9906
    Delay_Xms(80);
#endif
}

//-------- ADV7180LQFP reset function ------------
void Reset_VDC(void)
{
    bVideo_PW = 1; //Video power up
    Delay_Xms(200);
    bVideo_RST = 0;
    Delay_Xms(20);
    bVideo_RST = 1;
}    

#endif
