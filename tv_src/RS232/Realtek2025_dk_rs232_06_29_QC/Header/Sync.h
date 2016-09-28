//----------------------------------------------------------------------------------------------------
// ID Code      : Sync.h No.0001
// Update Note  : 
//
//----------------------------------------------------------------------------------------------------

//--------------------------------------------------
// Definitions of
//--------------------------------------------------


//----------------------------------------------------------------------------------------------------

#ifdef __SYNC__

//--------------------------------------------------
// Global Variables
//--------------------------------------------------
bit bHsyncSelection        = 0; // 1 --> select
bit bInputSignalAvailable  = 0; // 1 --> signal ok

BYTE idata ucInputSyncType = 0;
BYTE idata ucInputPortType = 0;

#if (_SCALER_TYPE == _RTD2553V || _SCALER_TYPE == _RTD2546N || _SCALER_TYPE == _RTD2525L || _SCALER_TYPE == _RTD2547D)
BYTE idata ucStablePol; //Ming-Yen
#endif
                
//--------------------------------------------------
// Function Prototypes
//--------------------------------------------------
bit CSyncHandler(void);
void CSyncInitialSyncProcessor(void);
BYTE CSyncMeasureSyncType(void);
BYTE CSyncSearchSyncTypeVGA(void);
BYTE CSyncGetSyncTypeStep1VGA(void);
BYTE CSyncGetSyncTypeStep2VGA(void);
BYTE CSyncCheckSOY(void);
void CSyncModifyPolarityVGA(void);
void CDisableVideoSetting(void);
BYTE CSyncSearchSyncTypeDVI(void);

#if(_HSYNC_TYPE_DETECTION == _NORMAL_RUN || (_VIDEO_SUPPORT && _VIDEO_CHIP == _VDC_TB1334))
BYTE CSyncGetSyncTypeStepVGA(void);
#endif

#if (_SCALER_TYPE == _RTD2553V || _SCALER_TYPE == _RTD2546N || _SCALER_TYPE == _RTD2525L || _SCALER_TYPE == _RTD2547D)
BYTE CSyncGetSyncTypeAutoRun(void);
#else
BYTE CSyncGetSyncTypeStep1VGA(void);
BYTE CSyncGetSyncTypeStep2VGA(void);
BYTE CSyncCheckSOY(void);
#endif


#else

//--------------------------------------------------
// Extern Global Variables
//--------------------------------------------------
extern bit bHsyncSelection;
extern bit bInputSignalAvailable;
     
extern BYTE idata ucInputSyncType;
extern BYTE idata ucInputPortType;

#if (_SCALER_TYPE == _RTD2553V || _SCALER_TYPE == _RTD2546N || _SCALER_TYPE == _RTD2525L || _SCALER_TYPE == _RTD2547D)
extern BYTE idata ucStablePol;  //Ming-Yen
#endif  

//--------------------------------------------------
// Extern Function Prototypes
//--------------------------------------------------
extern bit CSyncHandler(void);
extern void CSyncInitialSyncProcessor(void);
extern void CSyncModifyPolarityVGA(void);

#if(_HSYNC_TYPE_DETECTION == _NORMAL_RUN || (_VIDEO_SUPPORT && _VIDEO_CHIP == _VDC_TB1334))
extern BYTE CSyncGetSyncTypeStepVGA(void);
#endif

#if (_SCALER_TYPE == _RTD2553V || _SCALER_TYPE == _RTD2546N || _SCALER_TYPE == _RTD2525L || _SCALER_TYPE == _RTD2547D)
extern BYTE CSyncGetSyncTypeAutoRun(void);
#else
extern BYTE CSyncGetSyncTypeStep1VGA(void);
extern BYTE CSyncGetSyncTypeStep2VGA(void);
#endif
#endif
//----------------------------------------------------------------------------------------------------
//--------------------------------------------------
// Macro of Source Auto Change
//--------------------------------------------------
#define GET_SOURCE_AUTOCHANGE()         ((bit)(ucInputSyncType & _BIT7))
#define SET_SOURCE_AUTOCHANGE()         (ucInputSyncType |= _BIT7)
#define CLR_SOURCE_AUTOCHANGE()         (ucInputSyncType &= ~_BIT7)


//--------------------------------------------------
// Macro of DVII Source Switch
//--------------------------------------------------
#define GET_DVI_I_SOURCE_SWITCH()       ((bit)(stSystemData.MonitorFlag & _BIT6))
#define SET_DVI_I_DVI_SWITCH()          (stSystemData.MonitorFlag |= _BIT6)
#define CLR_DVI_I_VGA_SWITCH()          (stSystemData.MonitorFlag &= ~_BIT6)


//--------------------------------------------------
// Macro of Interlace Mode Check
//--------------------------------------------------
#define GET_INTERLACE_MODE(x)           ((bit)(ucInputSyncType & _BIT4))
#define SET_INTERLACE_MODE(x)           (ucInputSyncType |= _BIT4)
#define CLR_INTERLACE_MODE(x)           (ucInputSyncType &= ~_BIT4)


//--------------------------------------------------
// Macro of Field Merge Check
//--------------------------------------------------
#define GET_FIELDMERGE_MODE(x)          ((bit)(ucInputSyncType & _BIT5))
#define SET_FIELDMERGE_MODE(x)          (ucInputSyncType |= _BIT5)
#define CLR_FIELDMERGE_MODE(x)          (ucInputSyncType &= ~_BIT5)

