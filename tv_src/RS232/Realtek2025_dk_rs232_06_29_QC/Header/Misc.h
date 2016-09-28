//----------------------------------------------------------------------------------------------------
// ID Code      : Misc.h No.0000
// Update Note  : 
//
//----------------------------------------------------------------------------------------------------

//--------------------------------------------------
// Definitions of
//--------------------------------------------------


//----------------------------------------------------------------------------------------------------

#ifdef __MISC__

#if(_ISPACK && _ISPACK_TYPE == _ISPACK_RTD)
unsigned char xdata ucVirtualKey = _NONE_KEY_MESSAGE;
void GetVirtualKey(void);
#endif

//--------------------------------------------------
// Function Prototypes
//--------------------------------------------------
bit CMiscStableFlagPollingEvent(void);
bit CMiscModeMeasurePollingEvent(void);
bit CMiscAutoMeasurePollingEvent(void);
bit CMiscApplyDoubleBufferPollingEvent(void);
bit CMiscTMDSMeasureEvent(void);
bit CMiscTMDSCRCEvent(void);
void CMiscEnableDoubleBuffer(void);
void CMiscDisableDoubleBuffer(void);
void CMiscApplyDoubleBuffer(void);
void CMiscClearStatusRegister(void);
void CMiscSetPinShare(void);
void CMiscIspack(void);
void CMiscIspDebugProc(void);

#if (_SCALER_TYPE == _RTD2553V || _SCALER_TYPE == _RTD2546N || _SCALER_TYPE == _RTD2525L || _SCALER_TYPE == _RTD2547D)
bit CMiscScalerResetEvent(void);
bit CMiscHsyncTypeAutoRunFlagPollingEvent(void);
bit CMiscAutoAdjustAdcOffsetFlagPollingEvent(void);
#endif

#else

//--------------------------------------------------
// Extern Global Variables
//--------------------------------------------------



#if(_ISPACK && _ISPACK_TYPE == _ISPACK_RTD)
extern void GetVirtualKey(void);
#endif
//--------------------------------------------------
// Extern Function Prototypes
//--------------------------------------------------
extern bit CMiscStableFlagPollingEvent(void);
extern bit CMiscModeMeasurePollingEvent(void);
extern bit CMiscAutoMeasurePollingEvent(void);
extern bit CMiscTMDSMeasureEvent(void);
extern bit CMiscTMDSCRCEvent(void);
extern void CMiscEnableDoubleBuffer(void);
extern void CMiscDisableDoubleBuffer(void);
extern void CMiscApplyDoubleBuffer(void);
extern void CMiscClearStatusRegister(void);
extern void CMiscSetPinShare(void);
extern void CMiscIspDebugProc(void);

#if (_SCALER_TYPE == _RTD2553V || _SCALER_TYPE == _RTD2546N || _SCALER_TYPE == _RTD2525L || _SCALER_TYPE == _RTD2547D)
extern bit CMiscScalerResetEvent(void);
extern bit CMiscHsyncTypeAutoRunFlagPollingEvent(void);
extern bit CMiscAutoAdjustAdcOffsetFlagPollingEvent(void);
#endif

#endif


//----------------------------------------------------------------------------------------------------

