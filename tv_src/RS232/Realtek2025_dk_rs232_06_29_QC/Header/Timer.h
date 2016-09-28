//----------------------------------------------------------------------------------------------------
// ID Code      : Timer.h No.0000
// Update Note  : 
//
//----------------------------------------------------------------------------------------------------

//--------------------------------------------------
// Definitions of Timer.c
//--------------------------------------------------
#define _MAX_EVENT_AMOUNT           5
#define _INACTIVE_TIMER_EVENT       0xFFFFFFFF
#define _INACTIVE_COUNTDOWN_EVENT   0xFF


//----------------------------------------------------------------------------------------------------

#ifdef __TIMER__

//--------------------------------------------------
// Global Variables
//--------------------------------------------------
struct CTimerEventTable idata TimerEvent[_MAX_EVENT_AMOUNT];
BYTE data ucTimer0Cnt = 0;
bit bNotifyTimer0Int;
bit bTimer0Ctrl = _FALSE;


//--------------------------------------------------
// Function Prototypes
//--------------------------------------------------
void CTimerHandler(void);
void CTimerActiveTimerEvent(DWORD usTime, void (*Event)());
void CTimerReactiveTimerEvent(DWORD usTime, void (*Event)());
void CTimerCancelTimerEvent(void (*Event)());
void CTimerInitialTimerEvent(void);
void CTimerDecreaseTimerCnt(void);
void CTimerCountDownEventProc(BYTE *pEventCnt, BYTE ucWaitCnt, void (*Event)(void));
bit CTimerPollingEventProc(BYTE ucTimeout, bit (*Event)(void));
void CTimerDelayXms(WORD usNum);
bit CTimerWaitForEvent(BYTE ucEvent);


#else

//--------------------------------------------------
// Extern Global Variables
//--------------------------------------------------
extern struct CTimerEventTable idata TimerEvent[_MAX_EVENT_AMOUNT];
extern BYTE data ucTimer0Cnt;
extern bit bNotifyTimer0Int;
extern bit bTimer0Ctrl;


//--------------------------------------------------
// Extern Function Prototypes
//--------------------------------------------------
extern void CTimerHandler(void);
extern void CTimerActiveTimerEvent(DWORD usTime, void (*Event)());
extern void CTimerReactiveTimerEvent(DWORD usTime, void (*Event)());
extern void CTimerCancelTimerEvent(void (*Event)());
extern void CTimerInitialTimerEvent(void);
extern void CTimerDecreaseTimerCnt(void);
extern void CTimerCountDownEventProc(BYTE *pEventCnt, BYTE ucWaitCnt, void (*Event)(void));
extern bit CTimerPollingEventProc(BYTE ucTimeout, bit (*Event)(void));
extern void CTimerDelayXms(WORD usNum);
extern bit CTimerWaitForEvent(BYTE ucEvent);


#endif


//----------------------------------------------------------------------------------------------------

