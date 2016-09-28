//----------------------------------------------------------------------------------------------------
// ID Code      : Scaler.h No.0002
// Update Note  : 
//
//----------------------------------------------------------------------------------------------------

//--------------------------------------------------
// Definitions of Scaler
//--------------------------------------------------

//----------------------------------------------------------------------------------------------------

#ifdef __SCALER__

//--------------------------------------------------
// Global Variables
//--------------------------------------------------
BYTE data ucVLDCnt, ucVLDTemp;
#if(_USE_RTD2120_EXTEND_32K_FOR_OSD == _ON)
BYTE *pvldarray;
#else
BYTE code *pvldarray;
#endif


//--------------------------------------------------
// Function Prototypes
//--------------------------------------------------
void CScalerInitial(void);
void CScalerResetAction(bit bResetLevel);
void CScalerResetInFromMCU(void);
void CScalerReset(void);
void CScalerInitialDisplayInterface(void);
void CScalerInitialDisplayOutput(void);
void CScalerEnableDisplayOutput(void);
void CScalerDisableDisplayOutput(void);
void CScalerEnableDisplayTiming(void);
void CScalerDisableDisplayTiming(void);
void CScalerSendReadStop(void);
void CScalerSendWriteStop(void);
void CScalerSendAddr(BYTE ucAddr, bit bReadWrite, bit bAutoInc);
void CScalerSendByte(BYTE ucValue);
void CScalerWrite(BYTE ucAddr, WORD usLength, BYTE *pArray, bit bAutoInc);
void CScalerRead(BYTE ucAddr, BYTE ucLength, BYTE *pArray, bit bAutoInc);
void CScalerWriteAmount(BYTE ucAddr, WORD usLength, BYTE ucValue, bit bAutoInc);
void CScalerSetByte(BYTE ucAddr, BYTE ucValue);
void CScalerSetBit(BYTE ucAddr, BYTE ucAnd, BYTE ucOr);
BYTE CScalerGetBit(BYTE ucAddr, BYTE ucAnd);
void CScalerCodeW(BYTE code *pArray);
#if(_USE_RTD2120_EXTEND_32K_FOR_OSD == _ON)
void CScalerLoadFont(BYTE xdata *pArray, WORD usOffset, WORD usLength, BYTE ucPar);
#else
void CScalerLoadFont(BYTE code *pArray, WORD usOffset, WORD usLength, BYTE ucPar);
#endif
BYTE CScalerGetVLD(void);
bit CScalerGetBitVLD(void);

#if (_SCALER_TYPE == _RTD2553V || _SCALER_TYPE == _RTD2546N || _SCALER_TYPE == _RTD2525L || _SCALER_TYPE == _RTD2547D)
void CScalerSetDataPortByte(BYTE ucAddr, BYTE ucValue1, BYTE ucValue2);
void CScalerSetDataPortBit2(BYTE ucAddr, BYTE ucValue, BYTE ucAnd, BYTE ucOr);
void CScalerSetDataPortBit(BYTE ucAddr, BYTE ucValue, BYTE ucAnd, BYTE ucOr);
#if (_SCALER_TYPE == _RTD2547D)
void CScalerGetDataPortByte(BYTE ucAddr, BYTE ucValue, BYTE ucLength, BYTE *pArray, bit bAutoInc);
void CScalerPageSelect(BYTE page);
#endif
#if(_USE_RTD2120_EXTEND_32K_FOR_OSD == _ON)
void CScalerLoadHardwareVLCFont(BYTE xdata *pArray, WORD usOffset);
#else
void CScalerLoadHardwareVLCFont(BYTE code *pArray, WORD usOffset);
#endif

#if(((_ADC_OFFSET_ADJUSTING == _ADJUST_BY_HW_ON_LINE) || (_ADC_OFFSET_ADJUSTING == _ADJUST_BY_HW_OFF_LINE)) && (_SCALER_TYPE == _RTD2525L))         
BYTE CScalerGetDataPortBit(BYTE ucAddr, BYTE ucValue, BYTE ucAnd);
#endif
#else
void CScalerInitialForRTD2023(void);
void CScalerResetInForRTD2023(void);
#endif

#else

//--------------------------------------------------
// Extern Global Variables
//--------------------------------------------------
extern BYTE data ucVLDCnt, ucVLDTemp;
#if(_USE_RTD2120_EXTEND_32K_FOR_OSD == _ON)
extern BYTE *pvldarray;
#else
extern BYTE code *pvldarray;
#endif

//--------------------------------------------------
// Extern Function Prototypes
//--------------------------------------------------
extern void CScalerInitial(void);
extern void CScalerResetInFromMCU(void);
extern void CScalerReset(void);
extern void CScalerInitialForRTD2023(void);
extern void CScalerResetInForRTD2023(void);
extern void CScalerEnableDisplayOutput(void);
extern void CScalerDisableDisplayOutput(void);
extern void CScalerEnableDisplayTiming(void);
extern void CScalerDisableDisplayTiming(void);
extern void CScalerSendReadStop(void);
extern void CScalerSendWriteStop(void);
extern void CScalerSendAddr(BYTE ucAddr, bit bReadWrite, bit bAutoInc);
extern void CScalerSendByte(BYTE ucValue);
extern void CScalerWrite(BYTE ucAddr, WORD usLength, BYTE *pArray, bit bAutoInc);
extern void CScalerRead(BYTE ucAddr, BYTE ucLength, BYTE *pArray, bit bAutoInc);
extern void CScalerWriteAmount(BYTE ucAddr, WORD usLength, BYTE ucValue, bit bAutoInc);
extern void CScalerSetByte(BYTE ucAddr, BYTE ucValue);
extern void CScalerSetBit(BYTE ucAddr, BYTE ucAnd, BYTE ucOr);
extern BYTE CScalerGetBit(BYTE ucAddr, BYTE ucAnd);
extern void CScalerCodeW(BYTE code *pArray);
#if(_USE_RTD2120_EXTEND_32K_FOR_OSD == _ON)
extern void CScalerLoadFont(BYTE xdata *pArray, WORD usOffset, WORD usLength, BYTE ucPar);
#else
extern void CScalerLoadFont(BYTE code *pArray, WORD usOffset, WORD usLength, BYTE ucPar);
#endif
extern BYTE CScalerGetVLD(void);
extern bit CScalerGetBitVLD(void);

#if (_SCALER_TYPE == _RTD2553V || _SCALER_TYPE == _RTD2546N || _SCALER_TYPE == _RTD2525L || _SCALER_TYPE == _RTD2547D)
extern void CScalerSetDataPortByte(BYTE ucAddr, BYTE ucValue1, BYTE ucValue2);
extern void CScalerSetDataPortBit2(BYTE ucAddr, BYTE ucValue, BYTE ucAnd, BYTE ucOr);
extern void CScalerSetDataPortBit(BYTE ucAddr, BYTE ucValue, BYTE ucAnd, BYTE ucOr);
#if (_SCALER_TYPE == _RTD2547D)
extern void CScalerGetDataPortByte(BYTE ucAddr, BYTE ucValue, BYTE ucLength, BYTE *pArray, bit bAutoInc);
extern void CScalerPageSelect(BYTE page);
#endif
#if(_USE_RTD2120_EXTEND_32K_FOR_OSD == _ON)
extern void CScalerLoadHardwareVLCFont(BYTE xdata *pArray, WORD usOffset);
#else
extern void CScalerLoadHardwareVLCFont(BYTE code *pArray, WORD usOffset);
#endif
#if(((_ADC_OFFSET_ADJUSTING == _ADJUST_BY_HW_ON_LINE) || (_ADC_OFFSET_ADJUSTING == _ADJUST_BY_HW_OFF_LINE)) && (_SCALER_TYPE == _RTD2525L))         
extern BYTE CScalerGetDataPortBit(BYTE ucAddr, BYTE ucValue, BYTE ucAnd);
#endif
#else
extern void CScalerInitialForRTD2023(void);
extern void CScalerResetInForRTD2023(void);
#endif

extern BYTE CScalerGetByte(void);

#endif


//----------------------------------------------------------------------------------------------------

//--------------------------------------------------
// Macro of Scaler.c
//--------------------------------------------------
#define SETSCALERSCLK()             (bSCALERSCLK = _TRUE)
#define CLRSCALERSCLK()             (bSCALERSCLK = _FALSE)

#define SETSCALERSCSB()             (bSCALERSCSB = _TRUE)
#define CLRSCALERSCSB()             (bSCALERSCSB = _FALSE)

#define SETSCALERSDIO3(x)           (bSCALERSDIO3 = x)
#define GETSCALERSDIO3()            (bSCALERSDIO3)

#if(_HOST_INTERFACE == _PARALLEL_PORT)

#define SETSCALERSDIO0(x)           (bSCALERSDIO0 = x)
#define GETSCALERSDIO0()            (bSCALERSDIO0)
#define SETSCALERSDIO1(x)           (bSCALERSDIO1 = x)
#define GETSCALERSDIO1()            (bSCALERSDIO1)
#define SETSCALERSDIO2(x)           (bSCALERSDIO2 = x)
#define GETSCALERSDIO2()            (bSCALERSDIO2)

#endif



