//----------------------------------------------------------------------------------------------------
// ID Code      : Timer.c No.0001
// Update Note  : 
//
//----------------------------------------------------------------------------------------------------

#define __TIMER__

#include "Header\Include.h"


//--------------------------------------------------
// Description  : Check if it's time to execute events
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CTimerHandler(void)
{
    BYTE timereventcnt;

    for(timereventcnt=0;timereventcnt<_MAX_EVENT_AMOUNT;timereventcnt++)
    {
        if(TimerEvent[timereventcnt].Time == 0)
        {
            bTimer0Ctrl = _TRUE;
            TimerEvent[timereventcnt].Time = _INACTIVE_TIMER_EVENT;
            bTimer0Ctrl = _FALSE;
            (*TimerEvent[timereventcnt].Event)();
        }
    }
}

//--------------------------------------------------
// Description  : Set up a timer for an event. If the event is exist, 
//                this function is ignored and do not change the executing time.
// Input Value  : usTime    --> Unit in 10ms, range in 0.01 ~ 655.3 sec
//                Event     --> Execute Event while timeup
// Output Value : None
//--------------------------------------------------
void CTimerActiveTimerEvent(DWORD usTime, void (*Event)())
{
    BYTE timereventcnt;

    for(timereventcnt=0;timereventcnt<_MAX_EVENT_AMOUNT;timereventcnt++)
    {
        if((TimerEvent[timereventcnt].Time != _INACTIVE_TIMER_EVENT) && (TimerEvent[timereventcnt].Event == Event))
            return;
    }

    for(timereventcnt=0;timereventcnt<_MAX_EVENT_AMOUNT;timereventcnt++)
    {
        if(TimerEvent[timereventcnt].Time == _INACTIVE_TIMER_EVENT)
        {
            bTimer0Ctrl = _TRUE;
            TimerEvent[timereventcnt].Time = usTime;
            bTimer0Ctrl = _FALSE;
            TimerEvent[timereventcnt].Event = Event;
            break;
        }
    }
}

//--------------------------------------------------
// Description  : Reactive a timer for an event. If the event is exist,
//                this function will reset the executing time and restart.
// Input Value  : usTime    --> Unit in 10ms, range in 0.01 ~ 655.3 sec
//                Event     --> Execute Event while timeup
// Output Value : None
//--------------------------------------------------
void CTimerReactiveTimerEvent(DWORD usTime, void (*Event)())
{
    BYTE timereventcnt;

    for(timereventcnt=0;timereventcnt<_MAX_EVENT_AMOUNT;timereventcnt++)
    {
        if((TimerEvent[timereventcnt].Time != _INACTIVE_TIMER_EVENT) && (TimerEvent[timereventcnt].Event == Event))
        {
            bTimer0Ctrl = _TRUE;
            TimerEvent[timereventcnt].Time = usTime;
            bTimer0Ctrl = _FALSE;
            return;
        }
    }

    CTimerActiveTimerEvent(usTime, Event);
}

//--------------------------------------------------
// Description  : Cancel an event
// Input Value  : Event     --> Event which we want to cancel
// Output Value : None
//--------------------------------------------------
void CTimerCancelTimerEvent(void (*Event)())
{
    BYTE timereventcnt;

    for(timereventcnt=0;timereventcnt<_MAX_EVENT_AMOUNT;timereventcnt++)
    {
        if(TimerEvent[timereventcnt].Event == Event)
        {
            bTimer0Ctrl = _TRUE;
            TimerEvent[timereventcnt].Time = _INACTIVE_TIMER_EVENT;
            bTimer0Ctrl = _FALSE;
        }
    }
}

//--------------------------------------------------
// Description  : Initial timer and events. We have to run this function at firmware startup
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CTimerInitialTimerEvent(void)
{
    BYTE timereventcnt;

    for(timereventcnt=0;timereventcnt<_MAX_EVENT_AMOUNT;timereventcnt++)
    {
        TimerEvent[timereventcnt].Time = _INACTIVE_TIMER_EVENT;
    }

    TR0 = 1;
}

//--------------------------------------------------
// Description  : Decrease timer counts while 10ms Interrupt is up
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CTimerDecreaseTimerCnt(void)
{
    BYTE timerdeccnt;

    for(timerdeccnt=0;timerdeccnt<_MAX_EVENT_AMOUNT;timerdeccnt++)
    {
        if((TimerEvent[timerdeccnt].Time != _INACTIVE_TIMER_EVENT) && (TimerEvent[timerdeccnt].Time != 0))
        {
            TimerEvent[timerdeccnt].Time--;
        }
    }
}

//----------------------------------------------------------------------------------------------------
// Description  : Count down event process
// Input Value  : pEventCnt --> Event counter
//                ucWaitCnt --> Count down number (Max: 254)
//                Event     --> Execute Event while counter is zero
// Output Value : None
//----------------------------------------------------------------------------------------------------
void CTimerCountDownEventProc(BYTE *pEventCnt, BYTE ucWaitCnt, void (*Event)(void))
{
    if(*pEventCnt == _INACTIVE_COUNTDOWN_EVENT)
    {
        *pEventCnt = ucWaitCnt;
    }
    else if(*pEventCnt == 0)
    {
        *pEventCnt = _INACTIVE_COUNTDOWN_EVENT;
        Event();
    }
    else
    {
        *pEventCnt = *pEventCnt - 1;
    }
}

//----------------------------------------------------------------------------------------------------
// Description  : Polling Event Process
// Input Value  : ucTimeout --> Timeout number (Max: 255 ms)
//                Event     --> Polling event. This event has to return _TRUE or _FALSE
// Output Value : Return _TRUE while polling success, _FALSE for timeout
//----------------------------------------------------------------------------------------------------
bit CTimerPollingEventProc(BYTE ucTimeout, bit (*Event)(void))
{
    do
    {
        CTimerDelayXms(1);

        if(Event())
        {
            return _TRUE;
        }
    }
    while(--ucTimeout);

    return _FALSE;
}

//--------------------------------------------------
// Description  : Hold program for 0 ~ 65535 ms
// Input Value  : usNum     --> Delay time
// Output Value : None
//--------------------------------------------------
void CTimerDelayXms(WORD usNum)
{
    if(usNum)
    {
        bNotifyTimer0Int = _FALSE;

        while(_TRUE)
        {
            if(bNotifyTimer0Int)
            {
                bNotifyTimer0Int = _FALSE;

                if(--usNum)
                    TR0 = _ON;
                else
                    return;
            }
        }
    }
}

//--------------------------------------------------
// Description  : Hold until the specified event occurs
// Input Value  : ucEvent   --> Specified event
// Output Value : Return _TRUE while timeout
//--------------------------------------------------
bit CTimerWaitForEvent(BYTE ucEvent)
{
    BYTE temp;
    BYTE timeoutcnt = 30;                   // 30ms timeout

    CScalerSetByte(_STATUS1_03, 0x00);      // Clear status (status register will be cleared after write)

    bNotifyTimer0Int = _FALSE;

    do
    {
        if(bNotifyTimer0Int)
        {
            bNotifyTimer0Int  = _FALSE;

            if(--timeoutcnt)
                TR0 = _ON;
        }

        CScalerRead(_STATUS1_03, 1, &temp, _NON_AUTOINC);
      
        temp &= ucEvent;
    }
    while((temp == 0) && (timeoutcnt != 0));

    return timeoutcnt ? _FALSE : _TRUE;
}

