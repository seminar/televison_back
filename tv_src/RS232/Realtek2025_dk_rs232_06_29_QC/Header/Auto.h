//----------------------------------------------------------------------------------------------------
// ID Code      : Auto.h No.0001
// Update Note  : 
//
//----------------------------------------------------------------------------------------------------

//--------------------------------------------------
// Minumum Noise Margin
//--------------------------------------------------
#define _MIN_NOISE_MARGIN         0x50//  0x30//0506


//--------------------------------------------------
// Color Source Select for Detection
//--------------------------------------------------
#define _COLORS_BLUE                0x00
#define _COLORS_GREEN               0x01
#define _COLORS_RED                 0x02
#define _COLORS_ALL                 0x03

#define _COLOR_SELECT               _COLORS_ALL

//--------------------------------------------------
// Definations of Measure Color
//--------------------------------------------------
#define _MEASURE_COLORS_MIN         0x00
#define _MEASURE_COLORS_MAX         0x01


//--------------------------------------------------
// White Balance Max/Min Level Settings
//--------------------------------------------------
#if (_SCALER_TYPE == _RTD2553V || _SCALER_TYPE == _RTD2546N || _SCALER_TYPE == _RTD2525L || _SCALER_TYPE == _RTD2547D)
#define _WHITEBALANCE_MAX_LEVEL     250 //KEN 2005/09/23
#else
#define _WHITEBALANCE_MAX_LEVEL     242
#endif
#define _WHITEBALANCE_MIN_LEVEL     2
#define _WHITEBALANCE_BR_MIN_LEVEL  128 //V307 modify


//--------------------------------------------------
// Setting of Auto Black Level
//--------------------------------------------------
#if (_SCALER_TYPE == _RTD2553V || _SCALER_TYPE == _RTD2546N || _SCALER_TYPE == _RTD2525L || _SCALER_TYPE == _RTD2547D)
//--------------------------------------------------              
#define _ON_OFF_LINE_ABL_MODE       0   //0:off-line mode, 1:on-line mode
#define _ABL_REGION_IN_EACH_LINE    0   //(N+1)*16 pixels, N=0~3
#define _LINE_AVERAGED              2   //N=0~3, 0¡÷8, 1¡÷16, 2¡÷32, 3¡÷64 //V307 modify
#define _LOCK_MARGIN                0   //N=0~3, 0¡÷1, 1¡÷2, 2¡÷4, 3¡÷6
#define _START_LINE_OF_ABL          4   //Start line of ABL after the leading edge of Vsync
#define _END_LINE_OF_ABL          512   //The last line of ABL which is counted by double-line
#define _EQUAL_MARGIN               3   //N=0~3 //V307 modify
#define _START_POSITION_OF_ABL      4   //Start position of ABL in each line (0~63)
#define _LARGE_ERROR_MARGIN         3   //(N+1)*2, N=0~3
#define _MAX_FRAME_COUNT            0   //N=0~3, 0¡÷4, 1¡÷5, 2¡÷6, 3¡÷7 //V307 modify
#define _LINE_DELAY                 0   //(N+1)*16 lines, N=0~7

#define _ADJUST_BY_HW_ON_LINE           2   //Enable Auto Black Level of H/W in On-line Mode
#endif
//--------------------------------------------------
// Hardware Auto Phase Step
//--------------------------------------------------
#define _HWAUTO_STEP_1              0x00
#define _HWAUTO_STEP_2              0x01
#define _HWAUTO_STEP_4              0x02
#define _HWAUTO_STEP_8              0x03
#define _HWAUTO_STEP_16             0x04

#define _HWAUTO_STEP                _HWAUTO_STEP_2


//--------------------------------------------------
// Auto Clock Precision (Unit in Clock Number)
//--------------------------------------------------
#define _AUTO_CLOCK_PRECISION_1     1
#define _AUTO_CLOCK_PRECISION_2     2

#define _AUTO_CLOCK_PRECISION       _AUTO_CLOCK_PRECISION_2


//--------------------------------------------------
// Definitions of Auto Function
//--------------------------------------------------
#define _ERROR_SUCCESS              0x00
#define _ERROR_FINISH               0x40
#define _ERROR_ABORT                0x80
#define _ERROR_INPUT                0xff
#define _ERROR_PHASE                0xfe


//----------------------------------------------------------------------------------------------------

#ifdef __AUTO__

//--------------------------------------------------
// Global Variables
//--------------------------------------------------
BYTE idata ucAdcPGA; //V401 modify
WORD idata usHStartPos;
WORD idata usHEndPos;
WORD idata usVStartPos;
WORD idata usVEndPos;


//--------------------------------------------------
// Function Prototypes
//--------------------------------------------------
BYTE CAutoDoAutoConfig(void);
BYTE CAutoWaitFinish(void);
BYTE CAutoWaitForIVS(BYTE ucTimes);
BYTE CAutoMeasurePositionH(BYTE ucNoiseMarginH);
BYTE CAutoMeasurePositionV(BYTE ucNoiseMarginV);
DWORD CAutoPhaseSearch(BYTE ucSelColor, BYTE ucSelStep, BYTE ucSelStepNum, BYTE ucSelStepStart, BYTE *ucPhaseResult);
BYTE CAutoReadPhaseInfo(BYTE ucColor);
BYTE CAutoDoAutoClock(void);
BYTE CAutoDoAutoPhase(void);
BYTE CAutoDoAutoPosition(void);
BYTE CAutoDoWhiteBalance(void);
BYTE CAutoTuneBalance(void);
BYTE CAutoMeasureColor(BYTE ucColor, BYTE ucPar, BYTE *pMargin);
BYTE CAutoTuneAdcGain(BYTE ucColor, BYTE *pMargin);
BYTE CAutoTuneAdcOffset(BYTE ucColor, BYTE *pMargin);
BYTE CAutoChangeAdcGain(BYTE ucColor, BYTE ucDelta, BYTE ucInc);
BYTE CAutoChangeAdcOffset(BYTE ucColor, BYTE ucDelta, BYTE ucInc);

#if (_SCALER_TYPE == _RTD2553V || _SCALER_TYPE == _RTD2546N || _SCALER_TYPE == _RTD2525L || _SCALER_TYPE == _RTD2547D)
#if(((_ADC_OFFSET_ADJUSTING == _ADJUST_BY_HW_ON_LINE) || (_ADC_OFFSET_ADJUSTING == _ADJUST_BY_HW_OFF_LINE)) && (_SCALER_TYPE == _RTD2525L || _SCALER_TYPE == _RTD2547D))         
BYTE CAutoAdjustAdcOffset(void);
#endif
#endif

#else

//--------------------------------------------------
// Extern Global Variables
//--------------------------------------------------
extern BYTE idata ucAdcPGA; //V401 modify


//--------------------------------------------------
// Extern Function Prototypes
//--------------------------------------------------
extern BYTE CAutoDoAutoConfig(void);
extern BYTE CAutoDoWhiteBalance(void);

#if (_SCALER_TYPE == _RTD2553V || _SCALER_TYPE == _RTD2546N || _SCALER_TYPE == _RTD2525L || _SCALER_TYPE == _RTD2547D)
#if(((_ADC_OFFSET_ADJUSTING == _ADJUST_BY_HW_ON_LINE) || (_ADC_OFFSET_ADJUSTING == _ADJUST_BY_HW_OFF_LINE)) && (_SCALER_TYPE == _RTD2525L || _SCALER_TYPE == _RTD2547D))         
extern BYTE CAutoAdjustAdcOffset(void);
#endif
#endif

#endif


//----------------------------------------------------------------------------------------------------


#define HWAUTOSTEPNUM(x)                    (x)
#define HWAUTOSTEPSTART(x)                  (x)
