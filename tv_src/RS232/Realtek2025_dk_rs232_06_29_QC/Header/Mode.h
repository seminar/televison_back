//----------------------------------------------------------------------------------------------------
// ID Code      : Mode.h No.0002
// Update Note  : 
//
//----------------------------------------------------------------------------------------------------

//--------------------------------------------------
// Definitions of
//--------------------------------------------------


//----------------------------------------------------------------------------------------------------

#ifdef __MODE__

//--------------------------------------------------
// Global Variables
//--------------------------------------------------
BYTE idata ucCurrState = _PWOFF_STATE;
BYTE idata ucModeControl = 0;
BYTE idata ucEvent0 = 255;
BYTE idata ucEvent1 = 255;
BYTE idata ucModeFound;
BYTE idata ucHStartBias;
BYTE idata ucVStartBias;


//--------------------------------------------------
// Function Prototypes
//--------------------------------------------------
void CModeHandler(void);
bit CModeMeasureReady(void);
bit CModeMeasureData(void);
bit CModeDetect(void);
bit CModeDetectCommon(void);
bit CModeIsChange(void);
BYTE CModeSearchDisplayMode(void);
BYTE CModeSearchModeVGA(void);
bit CModeComparePresetModeVGA(BYTE ucModeCnt);
BYTE CModeSearchAcceptiveModeVGA(void);
BYTE CModeCheckFIFOModeVGA(BYTE ucModeCnt);
bit CModeCompareFIFOModeVGA(BYTE ucNum, BYTE ucModeCnt);
BYTE CModeSearchModeDVI(void);
bit CModeCompareModeDVI(BYTE ucModeCnt);
void CModeDisplayActiveMode(void);
void CModeSetupModeVGA(void);
void CModeSetupModeDVI(void);
void CModeSetupDisplay(void);
void CModeSetupColorProcess(void);
void CModeSetupEtcs(BYTE ucPar);
void CModeGetModeTableInfo(void);
void CModeStartUpVGA(void);
void CModeStartUpDVI(void);
BYTE CModeGetScaleSetting(void);
void CModeSetCaptureWindow(BYTE ucOption);
void CModeSetScaling(BYTE ucOption);
void CModeSetDisplay(BYTE ucOption);
void CModeModifyVTotal(void);
void CModeResetMode(void);
void CModeSetFreeRun(void);
bit CModeConnectIsChange(void);
void CModeAutoMeasureOn(void);
void CModeAutoMeasureOff(void);
void CModeSyncTimeoutCountDownEvent(void);
void CModeStableCountDownEvent(void);
void CModePowerSavingEvent(void);
void CModeNoSignalEvent(void);
void CModeNoCableEvent(void);
void CModeNoSupportEvent(void);
                   
#ifdef _SII164_INIT_SUPPORT
void CModeInitSiI164(void);
#endif

#if (_SCALER_TYPE == _RTD2547D)
void CModeSetFIFOForFrameSync(void);
void CModeHdmiStablePolling(void);
void CModeInterlaceCheck(void);
#endif

void CModeSetDisplayReady(void);

bit bModeIsChange(void);
bit bFrameSyncDet(void);
void CSetVGAReady(void);
bit bSyncHandler(void);
bit bModeDetect(void);


#else

//--------------------------------------------------
// Extern Global Variables
//--------------------------------------------------
extern BYTE idata ucCurrState;
extern BYTE idata ucModeControl;
extern BYTE idata ucHStartBias;
extern BYTE idata ucVStartBias;

extern BYTE idata ucEvent0;


//--------------------------------------------------
// Extern Function Prototypes
//--------------------------------------------------
extern void CModeHandler(void);
extern bit CModeMeasureReady(void);
extern bit CModeMeasureData(void);
extern bit CModeIsChange(void);
extern void CModeSetScaling(BYTE ucOption);
extern void CModeResetMode(void);
extern void CModeSetFreeRun(void);
extern void CModeSyncTimeoutCountDownEvent(void);
extern void CModeStableCountDownEvent(void);
extern void CModeSetupDisplay(void);
extern void CModeSetupColorProcess(void);
extern void CModeSetupEtcs(BYTE ucPar);
extern void CModeStartUpVGA(void);
extern void CModeSetupModeVGA(void);

extern void CModeAutoMeasureOn(void);
extern void CModeAutoMeasureOff(void);
extern void CModePowerSavingEvent(void);
extern void CModeNoSignalEvent(void);
extern void CModeNoCableEvent(void);
extern void CModeNoSupportEvent(void);

#ifdef _SII164_INIT_SUPPORT
extern void CModeInitSiI164(void);
#endif


#if (_SCALER_TYPE == _RTD2547D)
extern void CModeSetFIFOForFrameSync(void);
extern void CModeHdmiStablePolling(void);
extern void CModeInterlaceCheck(void);
#endif

#endif


//----------------------------------------------------------------------------------------------------
/*
//--------------------------------------------------
// Macro of Sync Processor Measure Ready Flag
//--------------------------------------------------
#define GET_MEASUREREADY()          (bit)(ucModeControl & _BIT0)
#define SET_MEASUREREADY()          ucModeControl |= _BIT0
#define CLR_MEASUREREADY()          ucModeControl &= ~_BIT0


//--------------------------------------------------
// Macro of Sync Processor Measure Start Flag
//--------------------------------------------------
#define GET_MEASURESTART()          (bit)(ucModeControl & _BIT1)
#define SET_MEASURESTART()          ucModeControl |= _BIT1
#define CLR_MEASURESTART()          ucModeControl &= ~_BIT1
*/

//--------------------------------------------------
// Macro of Start Display for show note flag  // add by eric 1221
//--------------------------------------------------
#define GET_FIRST_SHOW_NOTE()       (bit)(ucModeControl & _BIT0)
#define SET_FIRST_SHOW_NOTE()        ucModeControl |= _BIT0
#define CLR_FIRST_SHOW_NOTE()        ucModeControl &= ~_BIT0

//--------------------------------------------------
// Macro of Start Display for OSD Flow
//--------------------------------------------------
#define GET_OSD_READYFORDISPLAY()   (bit)(ucModeControl & _BIT1)
#define SET_OSD_READYFORDISPLAY()   ucModeControl |= _BIT1
#define CLR_OSD_READYFORDISPLAY()   ucModeControl &= ~_BIT1


//--------------------------------------------------
// Macro of Mode Stable Flag
//--------------------------------------------------
#define GET_MODESTABLE()            ((bit)(ucModeControl & _BIT2))
#define SET_MODESTABLE()            (ucModeControl |= _BIT2)
#define CLR_MODESTABLE()            (ucModeControl &= ~_BIT2)


//--------------------------------------------------
// Macro of Frame Sync Status
//--------------------------------------------------
#define GET_FRAMESYNCSTATUS()       ((bit)(ucModeControl & _BIT3))
#define SET_FRAMESYNCSTATUS()       (ucModeControl |= _BIT3)
#define CLR_FRAMESYNCSTATUS()       (ucModeControl &= ~_BIT3)


//--------------------------------------------------
// Macro of Input Source Type
//--------------------------------------------------
//#define GET_INPUTSOURCE_TYPE()       ((ucModeControl & (_BIT4 | _BIT5 | _BIT6)) >> 4)
//#define SET_INPUTSOURCE_TYPE(x)      (ucModeControl = ((ucModeControl & ~(_BIT4 | _BIT5 | _BIT6)) | (x << 4)))


//--------------------------------------------------
// Macro of Start Display
//--------------------------------------------------
#define GET_READYFORDISPLAY()       ((bit)(ucModeControl & _BIT7))
#define SET_READYFORDISPLAY()       (ucModeControl |= _BIT7)
#define CLR_READYFORDISPLAY()       (ucModeControl &= ~_BIT7)


//--------------------------------------------------
// Macro of Color Temperature
//--------------------------------------------------
#define GET_COLOR_TEMP_TYPE()        (stSystemData.ColorTemp & (_BIT3 | _BIT2 | _BIT1 | _BIT0))
#define SET_COLOR_TEMP_TYPE(x)       (stSystemData.ColorTemp = ((stSystemData.ColorTemp & ~(_BIT3 | _BIT2 | _BIT1 | _BIT0)) | x))




//----------------------------------------------------------------------------------------------------

