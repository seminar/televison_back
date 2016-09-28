//----------------------------------------------------------------------------------------------------
// ID Code      : Int.c No.0002
// Update Note  : 
//
//----------------------------------------------------------------------------------------------------

#include "Header\Include.h"

//--------------------------------------------------
// Timer0 Interrupt (1ms)
//--------------------------------------------------
void IntProcTimer0(void) interrupt 1
{
    TR0 = _ON;
    TL0 = _TIMER0_COUNT_LBYTE;
    TH0 = _TIMER0_COUNT_HBYTE;

    bNotifyTimer0Int = _TRUE;

    if(--ucTimer0Cnt)
    {

    }
    else
    {
        if(bTimer0Ctrl == _FALSE)
        {
            CTimerDecreaseTimerCnt();
            ucTimer0Cnt = 10;
        }
    }

#if(_AUTO_POWER_DOWN && _VIDEO_TV_SUPPORT)
    if (0x00 != ucAutoPowerDownTime && 0xff != ucAutoPowerDownTime)
    {
        ucMinuteCount++;
        if (ucMinuteCount == _ONE_MINUTE_COUNT)  // 1 minute
        {
            ucAutoPowerDownTime--;
            ucMinuteCount = 0;
        }
    }
#endif
}
/*
#if(_RS232 == _ON)

//-------------------------------------------------------------------------------------------------------------------
// UART interrupt function (4)
//-------------------------------------------------------------------------------------------------------------------
void IntProcUart(void)  interrupt 4
{
    if(TI)
        TI = 0;

    if(RI)
    {
        if(!bUartCommandStart)
        {
            pUartData[0] = SBUF;
            switch(pUartData[0])
            {
                case 0x5a:
                case 0x5b:
                case 0x5c:
                case 0x5d:
                case 0x41:
                    bUartCommandStart = _TRUE;
                    ucUartCommandNum = 1;
					break;
                default:
                    bUartCommandStart = _FALSE;
                    break;
            }
        }
        else
        {
            if(ucUartCommandNum < 5)
            {
                pUartData[ucUartCommandNum] = SBUF;
                ucUartCommandNum++;
                if(ucUartCommandNum == 5)
                {
                    bUartCommandStart = _FALSE;
                    bUartCommandSuccess = _TRUE;
                    ucUartCommandNum = 1;
                }
            }
        }

        RI = 0;
    }
}

#endif*/


#if(_RS232)
//--------------------------------------------------
void UartRxData(void)
{
	if (fUartStart == 0) 
	{
		pUartData[0] = SBUF;
		fUartStart = 1;
		switch(pUartData[0])
		{
			case UartCMD_DebugModeEnter:  		// Enter debug mode
			case UartCMD_DebugModeExit:  		// Exit debug mode
				ucUartRxCount = 4;
				break;
			case UartCMD_CScalerRead:  			// Read RTD2553V
			case UartCMD_I2CRead:  				// Read I2C
			case UartCMD_I2CWrite:  			// Write I2C
				ucUartRxCount = 3;
				break;
			case UartCMD_CScalerWrite:  		// Write RTD2553V
				ucUartRxCount = 2;
				break;
			default:
				fUartStart = 0;
				break;


	              case UartCMD_RS232Control:  		//leo add for  RS232 
			if(pUartData[2] == 0x1f)
				{
				ucUartRxCount = 5;
			      fInitCmdlength = 0;
				}
			else
				{
				ucUartRxCount = 5;
			       fInitCmdlength =1;
				}
				break;
		}

		ucUartRxIndex = 1;
	}
	else 
	{
		pUartData[ucUartRxIndex] = SBUF;
		ucUartRxIndex++;
		if (ucUartRxIndex > ucUartRxCount)
		{
			fUartRxCmdSuccess = 1;
			fUartStart = 0;
		}
	}
}

//--------------------------------------------------
void IntProcUart(void) interrupt 4
{
	ES = 0; // disable uart interrupt.
	if (TI) 
	{
		TI = 0;
	}
	else if (RI) 
	{
		UartRxData();
		RI = 0;
	}
	ES = 1;
}


#endif

