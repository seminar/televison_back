//----------------------------------------------------------------------------------------------------
// ID Code      : Adjust.h No.0002
// Update Note  : 
//
//----------------------------------------------------------------------------------------------------

//--------------------------------------------------
// Definitions of Digital Filter
//--------------------------------------------------
#define _DISABLE_PORT                   0
#define _PHASE_ACCESS_PORT              1
#define _NEG_SMEAR_ACCESS_PORT          2
#define _POS_SMEAR_ACCESS_PORT          3
#define _NEG_RING_ACCESS_PORT           4
#define _POS_RING_ACCESS_PORT           5
#define _MISMATCH_ACCESS_PORT           6
#define _YPBPR_ACCESS_PORT              7
#define _NOISE_REDUCTION_PORT           8

#define _YPBPR_DISABLE                  0
#define _YPBPR_ENABLE                   7

#define _FUNCTION_DISABLE               0
#define _FUNCTION_ENABLE                1

#define _PHASE_THD_0                    0
#define _PHASE_THD_1                    1
#define _PHASE_THD_2                    2
#define _PHASE_THD_3                    3
#define _PHASE_THD_4                    4
#define _PHASE_THD_5                    5
#define _PHASE_THD_6                    6
#define _PHASE_THD_7                    7

#define _SMEAR_RING_THD_0               0
#define _SMEAR_RING_THD_1               1
#define _SMEAR_RING_THD_2               2
#define _SMEAR_RING_THD_3               3
#define _SMEAR_RING_THD_4               4
#define _SMEAR_RING_THD_5               5
#define _SMEAR_RING_THD_6               6
#define _SMEAR_RING_THD_7               7

#define _MISMATCH_THD_0                 0
#define _MISMATCH_THD_1                 1

#define _NOISE_REDUCTION_THD_0          0
#define _NOISE_REDUCTION_THD_1          1
#define _NOISE_REDUCTION_THD_2          2
#define _NOISE_REDUCTION_THD_3          3
#define _NOISE_REDUCTION_THD_4          4
#define _NOISE_REDUCTION_THD_5          5
#define _NOISE_REDUCTION_THD_6          6
#define _NOISE_REDUCTION_THD_7          7

#define _DIV_VALUE_0                    0
#define _DIV_VALUE_1                    1
#define _DIV_VALUE_2                    2
#define _DIV_VALUE_3                    3


//--------------------------------------------------
// Definitions of Coring Type
//--------------------------------------------------
#define _CORING_MIN                     3   // (0~5)
#define _CORING_MAX_POS                 50  // (50~60)
#define _CORING_MAX_NEG                 -50 // (-50~-60)


//--------------------------------------------------
// Definitions of Gamma Table Type
//--------------------------------------------------
#define _COMPACT_GAMMA_NORMAL_TABLE     0
#define _FULL_GAMMA_NORMAL_TABLE        1
#define _COMPACT_GAMMA_COMPRESS_TABLE   2
#define _FULL_GAMMA_COMPRESS_TABLE      3


//--------------------------------------------------
// Definitions of TMDS Measurement
//--------------------------------------------------
#define _TMDS_MEASURE_HSYNC_BE          0x00
#define _TMDS_MEASURE_HSYNC_AF          0x01
#define _TMDS_MEASURE_DE_BE             0x02
#define _TMDS_MEASURE_DE_AF             0x03

#define _TMDS_MEASURE_AVE               0x00
#define _TMDS_MEASURE_MAX               0x01
#define _TMDS_MEASURE_MIN               0x02

#define _MEASURE_HSYNC                  0
#define _MEASURE_DE                     1


//--------------------------------------------------
// Definations of Watch Dogs
//--------------------------------------------------
#define _WD_DV_TIMEOUT                  0x20
#define _WD_APLL_NONLOCK                0x10
#define _WD_FRAMESYNC                   0x08
#define _WD_DV_TIMEOUT_APLL_NONLOCK     (_WD_DV_TIMEOUT | _WD_APLL_NONLOCK)
#define _WD_FRAMESYNC_APLL_NONLOCK      (_WD_APLL_NONLOCK | _WD_FRAMESYNC)
#define _WD_ALL                         (_WD_DV_TIMEOUT | _WD_APLL_NONLOCK | _WD_FRAMESYNC)

//--------------------------------------------------
// Definations of HDMI Watch Dog Control
//--------------------------------------------------
#define _WD_SET_AVMUTE_ENABLE           0x01
#define _WD_AUDIO_FOR_TMDS_CLOCK        0x02
#define _WD_PACKET_VARIATION            0x04

//----------------------------------------------------------------------------------------------------

#ifdef __ADJUST__

//--------------------------------------------------
// Global Variables
//--------------------------------------------------
BYTE idata ucAdjustCtrl = 0;


//--------------------------------------------------
// Function Prototypes
//--------------------------------------------------
void CAdjustIHSDelay(WORD usIHSDelay);
void CAdjustIVSDelay(WORD usIVSDelay);
void CAdjustDclkOffset(WORD usDclkOffset);

#if (_SCALER_TYPE == _RTD2547D)
void CAdjustMclkOffset(WORD usMclkOffset);
void CAdjustDclkSpreadSpectrumRange(BYTE ucSpreadRange);
void CAdjustMclkSpreadSpectrumRange(BYTE ucSpreadRange);
void CAdjustEnableHDMIWatchDog(BYTE ucPar);
void CAdjustDisableHDMIWatchDog(BYTE ucPar);
void CAdjustPLL(bit ucSelection, DWORD ulFreq);
void CAdjustFillICMTable(BYTE ucNum);
void CAdjustODeltaGain(BYTE ucValue);
#else
void CAdjustSpreadSpectrumRange(BYTE ucSpreadRange);
void CAdjustDPLL(DWORD ulFreq);
#endif

void CAdjustSyncProcessorMeasureStart(void);
void CAdjustTMDSErrorCorrectionOn(void);
#if(_TMDS_SUPPORT == _ON || _HDMI_SUPPORT)
void CAdjustTMDSErrorCorrectionOff(void);
#endif
BYTE CAdjustTMDSMeasure(BYTE ucType, BYTE ucSelect);
DWORD CAdjustTMDSCRCMeasure(void);
void CAdjustTMDSCRCCheck(void);
BYTE CAdjustTMDSEqualizerCheck(BYTE ucPar);
bit CAdjustTMDSEqualizer(void);
BYTE CAdjustTMDSCRC(BYTE *pArray);
void CAdjustSetDigitalCapture(void);
void CAdjustTMDSCaptureCheck(void);
void CAdjustHDCP(void);
void CAdjustEnableWatchDog(BYTE ucPar);
void CAdjustDisableWatchDog(BYTE ucPar);
void CAdjustSRGB(void);
void CAdjustGamma(BYTE ucGammaTableType, BYTE *pGammaTableArrayR, BYTE *pGammaTableArrayG, BYTE *pGammaTableArrayB);
void CAdjustDither(BYTE *pDitherSeqTable, BYTE * pDitherTable);
void CAdjustSharpness(void);
void CAdjustSetSharpnessTable(BYTE code *pArray0, BYTE code *pArray1);
void CAdjustBrightness(void);
void CAdjustContrast(void);
void CAdjustBacklight(void);
void CAdjustAdcGain(void);
void CAdjustAdcOffset(void);
void CAdjustAdcGainOffset(void);
void CAdjustBackgroundColor(BYTE ucRed, BYTE ucGreen, BYTE ucBlue);
void CAdjustColorPalette(BYTE *pColorPaletteArray);
BYTE CAdjustIVS2DVSDelay(BYTE ucOption);
void CAdjustUpdateCenterData(void);
bit CAdjustCheckAdcClockRange(WORD usClock, WORD *delta);
void CAdjustAdcClock(WORD usClock);
void CAdjustPhase(BYTE ucPhase);
void CAdjustHPosition(void);
void CAdjustVPosition(void);
void CAdjustDigitalFilter(BYTE ucAccess, BYTE ucOffset, BYTE ucDiv, BYTE ucEnable);

#if (_SCALER_TYPE == _RTD2553V || _SCALER_TYPE == _RTD2546N || _SCALER_TYPE == _RTD2525L)
#if (_VGA_COLOR_SUPPORT)
void CAdjustEnableHLWindow(void);
void CAdjustDisableHLWindow(void);
void CAdjustHLWindow(void);
void CAdjustHLWindowHV(WORD usHPos, WORD usHWidth, WORD usVPos, WORD usVHeight);
void CAdjustHLWindowHVBorder(BYTE ucBorderWidth, BYTE ucRed, BYTE ucGreen, BYTE ucBlue);
void CAdjustHLWindowBrightness(BYTE ucValue);
void CAdjustHLWindowContrast(BYTE ucValue);
void CAdjustHLWindowPeaking(BYTE ucValue);
void CAdjustNormalizeFactor(WORD usHWidth, WORD usVHeight);
void CAdjustFillDCCTable(BYTE *pControlTable, BYTE *pUserCurveTable);
void CAdjustMZHueSat(BYTE color);
void CAdjustPeakingFilter(SBYTE ucPeaking);
void CAdjustAccessICMTable(BYTE ucNum); //Six Axes Color
void CSetSACMode(BYTE DDCtype);
#endif // end #if (_VGA_COLOR_SUPPORT)
#endif

#else

//--------------------------------------------------
// Extern Global Variables
//--------------------------------------------------
extern BYTE idata ucAdjustCtrl;


//--------------------------------------------------
// Extern Function Prototypes
//--------------------------------------------------
extern void CAdjustIHSDelay(WORD usIHSDelay);
extern void CAdjustIVSDelay(WORD usIVSDelay);
extern void CAdjustDclkOffset(WORD usDclkOffset);

#if (_SCALER_TYPE == _RTD2547D)
extern void CAdjustMclkOffset(WORD usMclkOffset);
extern void CAdjustDclkSpreadSpectrumRange(BYTE ucSpreadRange);
extern void CAdjustMclkSpreadSpectrumRange(BYTE ucSpreadRange);
extern void CAdjustEnableHDMIWatchDog(BYTE ucPar);
extern void CAdjustDisableHDMIWatchDog(BYTE ucPar);
extern void CAdjustPLL(bit ucSelection, DWORD ulFreq);
extern void CAdjustFillICMTable(BYTE ucNum);
extern void CAdjustODeltaGain(BYTE ucValue);
#else
extern void CAdjustSpreadSpectrumRange(BYTE ucSpreadRange);
extern void CAdjustDPLL(DWORD ulFreq);
#endif

extern void CAdjustSyncProcessorMeasureStart(void);
extern void CAdjustTMDSErrorCorrectionOn(void);
#if(_TMDS_SUPPORT == _ON || _HDMI_SUPPORT)
extern void CAdjustTMDSErrorCorrectionOff(void);
#endif
extern DWORD CAdjustTMDSCRCMeasure(void);
extern void CAdjustTMDSCRCCheck(void);
extern bit CAdjustTMDSEqualizer(void);
extern void CAdjustSetDigitalCapture(void);
extern void CAdjustTMDSCaptureCheck(void);
extern void CAdjustEnableWatchDog(BYTE ucPar);
extern void CAdjustDisableWatchDog(BYTE ucPar);
extern void CAdjustHDCP(void);
extern void CAdjustSRGB(void);
extern void CAdjustGamma(BYTE ucGammaTableType, BYTE *pGammaTableArrayR, BYTE *pGammaTableArrayG, BYTE *pGammaTableArrayB);
extern void CAdjustDither(BYTE *pDitherSeqTable, BYTE * pDitherTable);
extern void CAdjustSharpness(void);
extern void CAdjustSetSharpnessTable(BYTE code *pArray0, BYTE code *pArray1);
extern void CAdjustBrightness(void);
extern void CAdjustContrast(void);
extern void CAdjustBacklight(void);
extern void CAdjustAdcGain(void);
extern void CAdjustAdcOffset(void);
extern void CAdjustAdcGainOffset(void);
extern void CAdjustBackgroundColor(BYTE ucRed, BYTE ucGreen, BYTE ucBlue);
extern void CAdjustColorPalette(BYTE *pColorPaletteArray);
extern BYTE CAdjustIVS2DVSDelay(BYTE ucOption);
extern void CAdjustUpdateCenterData(void);
extern bit CAdjustCheckAdcClockRange(WORD usClock, WORD *delta);
extern void CAdjustAdcClock(WORD usClock);
extern void CAdjustPhase(BYTE ucPhase);
extern void CAdjustHPosition(void);
extern void CAdjustVPosition(void);
extern void CAdjustDigitalFilter(BYTE ucAccess, BYTE ucOffset, BYTE ucDiv, BYTE ucEnable);

#if (_SCALER_TYPE == _RTD2553V || _SCALER_TYPE == _RTD2546N || _SCALER_TYPE == _RTD2525L)
#if (_VGA_COLOR_SUPPORT)
extern void CAdjustEnableHLWindow(void);
extern void CAdjustDisableHLWindow(void);
extern void CAdjustHLWindow(void);
extern void CAdjustHLWindowHV(WORD usHPos, WORD usHWidth, WORD usVPos, WORD usVHeight);
extern void CAdjustHLWindowHVBorder(BYTE ucBorderWidth, BYTE ucRed, BYTE ucGreen, BYTE ucBlue);
extern void CAdjustHLWindowBrightness(BYTE ucValue);
extern void CAdjustHLWindowContrast(BYTE ucValue);
extern void CAdjustHLWindowPeaking(BYTE ucValue);
extern void CAdjustNormalizeFactor(WORD usHWidth, WORD usVHeight);
extern void CAdjustFillDCCTable(BYTE *pControlTable, BYTE *pUserCurveTable);
extern void CAdjustMZHueSat(BYTE color);
extern void CAdjustPeakingFilter(SBYTE ucPeaking);
extern void CAdjustAccessICMTable(BYTE ucNum); //Six Axes Color
extern void CSetSACMode(BYTE DDCtype);
#endif // end #if (_VGA_COLOR_SUPPORT)


#endif  //#if (_SCALER_TYPE == _RTD2553V || _SCALER_TYPE == _RTD2546N || _SCALER_TYPE == _RTD2525L)

#if(_VIDEO_VIVID_COLOR_SUPPORT)
extern void CAccAdjustVividColorForVideo(BYTE mode);
extern void CAdjustPeakingFilterForVideo(SBYTE ucPeaking);
#endif  // #if(_VIDEO_VIVID_COLOR_SUPPORT)

#endif


//----------------------------------------------------------------------------------------------------

//--------------------------------------------------
// Macro of Start Display
//--------------------------------------------------
#define GET_FIRST_ADCCLOCK()        ((bit)(ucAdjustCtrl & _BIT0))
#define SET_FIRST_ADCCLOCK()        (ucAdjustCtrl |= _BIT0)
#define CLR_FIRST_ADCCLOCK()        (ucAdjustCtrl &= ~_BIT0)


//--------------------------------------------------
// Macro of Mode Search Type
//--------------------------------------------------
#define GET_MODE_SEARCH_TYPE()      ((bit)(ucAdjustCtrl & _BIT1))
#define SET_MODE_SEARCH_TYPE(x)     (ucAdjustCtrl = ((ucAdjustCtrl & ~(_BIT1)) | (x << 1)))


//--------------------------------------------------
// Macro of DVI Use Transition Result Flag
//--------------------------------------------------
#define GET_USE_TRANSITION_RESULT() ((bit)(ucAdjustCtrl & _BIT2))
#define SET_USE_TRANSITION_RESULT() (ucAdjustCtrl |= _BIT2)
#define CLR_USE_TRANSITION_RESULT() (ucAdjustCtrl &= ~_BIT2)

