//----------------------------------------------------------------------------------------------------
// ID Code      : Auto.c No.0003
// Update Note  : 
//
//----------------------------------------------------------------------------------------------------

#define __AUTO__

#include "Header\Include.h"


//--------------------------------------------------
// Description  : Auto clock, phase and H,V position
// Input Value  : None
// Output Value : _ERROR_SUCCESS if succeed
//--------------------------------------------------
BYTE CAutoDoAutoConfig(void)
{
    BYTE result, phasetemp;

#if(_IR_ENABLE)
    gmi_CStopIR();
#endif
    // Save current phase
    phasetemp = stModeUserData.Phase;

    // Clear the HW auto status to prevent some un-expected event happened
    CScalerSetByte(_AUTO_ADJ_CTRL1_7D, 0x00);

    CMiscClearStatusRegister();

    result  = CAutoDoAutoPosition();

    if(result == _ERROR_SUCCESS)
    {
        result  = CAutoDoAutoClock();

        if(result == _ERROR_SUCCESS)
        {
            result  = CAutoDoAutoPhase();

            if((result == _ERROR_SUCCESS) || (result == _ERROR_PHASE))
            {
                if(result == _ERROR_PHASE)
                {
                    stModeUserData.Phase = phasetemp;
                    CAdjustPhase(stModeUserData.Phase);
                }

                result  = CAutoDoAutoPosition();

                if(result != _ERROR_SUCCESS)
                {
                    stModeUserData.HPosition = stModeInfo.IHStartPos;
                    stModeUserData.VPosition = stModeInfo.IVStartPos;
                    CAdjustHPosition();
                    CAdjustVPosition();
                }
            }
            else
            {
                // If auto phase is failed, load phase setting before auto config
                stModeUserData.Phase = phasetemp;
                CAdjustPhase(stModeUserData.Phase);
            }
        }
        else
        {
            // If auto clock is failed, load default clock setting
            stModeUserData.Clock = stModeInfo.IHTotal;
            stModeUserData.HPosition = stModeInfo.IHStartPos;
            stModeUserData.VPosition = stModeInfo.IVStartPos;
            CAdjustAdcClock(stModeUserData.Clock);
            CAdjustHPosition();
            CAdjustVPosition();
        }
    }
    else
    {
        stModeUserData.HPosition = stModeInfo.IHStartPos;
        stModeUserData.VPosition = stModeInfo.IVStartPos;
        CAdjustHPosition();
        CAdjustVPosition();
    }

    if((result == _ERROR_SUCCESS) || (result == _ERROR_ABORT))
    {
        // Save auto result
        CEepromSaveModeData(stModeInfo.ModeCurr);
        CAdjustUpdateCenterData();
        CEepromSaveCenterModeData(stModeInfo.ModeCurr);
    }

    CMiscClearStatusRegister();
#if(_IR_ENABLE)  
    gmi_CStartIR();
#endif

    return result;
}

//--------------------------------------------------
// Description  : Auto color ( white balance )
// Input Value  : None
// Output Value : _ERROR_SUCCESS if succeed
//--------------------------------------------------
BYTE CAutoDoWhiteBalance(void)
{
    BYTE result;

    result = CAutoTuneBalance();

    if(result == _ERROR_SUCCESS)
    {
        CEepromSaveAdcData();
    }
    else
    {
        CEepromLoadAdcDataDefault();
    }

    return result;
}

//--------------------------------------------------
// Description  : Wait auto measure process completed
// Input Value  : None
// Output Value : Return result _ERROR_INPUT, _ERROR_SUCCESS
//--------------------------------------------------
BYTE CAutoWaitFinish(void)
{
    BYTE timeoutcnt, ivsevent;

    CMiscClearStatusRegister();

    // Auto timeout
    timeoutcnt   = (CScalerGetBit(_AUTO_ADJ_CTRL0_7A, _BIT1 | _BIT0) == 0x03) ? 150 : 50;

    // IVS timeout
    ivsevent     = 25;

    do
    {
        CTimerDelayXms(1);

        CScalerRead(_STATUS1_03, 1, pData, _NON_AUTOINC);

        if(pData[0] & _EVENT_IVS)
        {
            CScalerSetByte(_STATUS1_03, 0x00);
            ivsevent = 25;
        }
        else
        {
            ivsevent = ivsevent - 1;
        }

        if((ivsevent == 0) || (pData[0] & (_EVENT_UNDERFLOW | _EVENT_OVERFLOW)))
        {
            return _ERROR_INPUT;
        }

        // Power off while auto config--------
        CKeyCheckPowerKey();

        if(GET_POWERSWITCH())
            return _ERROR_INPUT;
        //------------------------------------

        CScalerRead(_AUTO_ADJ_CTRL1_7D, 1, pData, _NON_AUTOINC);
    }
    while((pData[0] & 0x01) && (--timeoutcnt));

    CScalerRead(_STATUS0_02, 1, pData, _NON_AUTOINC);
    CScalerSetByte(_STATUS0_02, 0x00);

    // Return non-zero value in Data[0] if :
    // 1. IVS or IHS changed
    // 2. Auto-Phase Tracking timeout
    return ((pData[0] & 0x63) || (0 == timeoutcnt)) ? _ERROR_INPUT : _ERROR_SUCCESS;
}

//--------------------------------------------------
// Description  : Wait for IVS process
// Input Value  : ucTimes   --> frames
// Output Value : Return underflow/overflow status
//--------------------------------------------------
BYTE CAutoWaitForIVS(BYTE ucTimes)
{
    BYTE timeoutcnt;

    timeoutcnt = 25;

    CScalerSetByte(_STATUS1_03, 0x00);
   	do
    {
        CTimerDelayXms(1);

        CScalerRead(_STATUS1_03, 1, pData, _NON_AUTOINC);        

        pData[0] &= (_EVENT_IVS | _EVENT_UNDERFLOW | _EVENT_OVERFLOW);

        if(((pData[0] & _EVENT_IVS) == _EVENT_IVS) && (ucTimes != 0))
        {
            CScalerSetByte(_STATUS1_03, 0x00);
            ucTimes--;
            timeoutcnt = 25;
        }
   	}
    while((ucTimes != 0) && (--timeoutcnt) && ((pData[0] & (_EVENT_UNDERFLOW | _EVENT_OVERFLOW)) == 0));

    return pData[0];
}

//--------------------------------------------------
// Description  : Measure position H
// Input Value  : ucNoiseMarginH    --> Noise margin for H
// Output Value : Measure status
//--------------------------------------------------
BYTE CAutoMeasurePositionH(BYTE ucNoiseMarginH)
{
    WORD lbound, rbound;

    rbound  = stModeUserData.Clock;                                               // Totol Clock Number
    lbound  = (DWORD)rbound * stModeInfo.IHSyncPulseCount / stModeInfo.IHCount;   // Clock number in HSYNC pulse

#if(_SCALER_TYPE == _RTD2547D)
    CScalerSetBit(_VGIP_HV_DELAY_1E, 0x0f, 0x50);
#else
    CScalerSetBit(_VGIP_HV_DELAY_13, 0x0f, 0x50);
#endif

    rbound  = (rbound + _MEASURE_HDEALY) - 2;

    rbound  = rbound - 32;

    lbound  = (lbound + 20 + _MEASURE_HDEALY) < stModeInfo.IHStartPos ? (lbound + 20 + _MEASURE_HDEALY) : 0x0001;

    lbound  = (lbound > 32) ? (lbound - 32) : 0x0001;

    ucNoiseMarginH  &= 0xfc;

    pData[0]    = ((lbound >> 4) & 0x70) | (HIBYTE(rbound) & 0x0f);
    pData[1]    = (LOBYTE(lbound));
    pData[2]    = (LOBYTE(rbound));
    CScalerWrite(_H_BOUNDARY_H_70, 3, pData, _AUTOINC);

    pData[0]    = ucNoiseMarginH;
    pData[1]    = ucNoiseMarginH;
    pData[2]    = ucNoiseMarginH;
    pData[3]    = 0x00;
    pData[4]    = 0x00;
    pData[5]    = 0x00;
    pData[6]    = 0x00;
    pData[7]    = 0x01;
    CScalerWrite(_RED_NOISE_MARGIN_76, 8, pData, _AUTOINC);

    pData[0]    = CAutoWaitFinish();

    if(pData[0] != _ERROR_SUCCESS)       return pData[0];

    CScalerRead(_H_START_END_H_81, 3, &pData[8], _AUTOINC);

    usHStartPos = (((WORD)(pData[8] & 0xf0 ) << 4) | (WORD)pData[9]) + 32;
    usHEndPos   = (((WORD)(pData[8] & 0x0f ) << 8) | (WORD)pData[10]) + 32;

    return _ERROR_SUCCESS;
}

//--------------------------------------------------
// Description  : Measure position V
// Input Value  : ucNoiseMarginV    --> Noise margin for V
// Output Value : Measure status
//--------------------------------------------------
BYTE CAutoMeasurePositionV(BYTE ucNoiseMarginV)
{
    WORD lbound, rbound;

    rbound  = stModeUserData.Clock;                                               // Totol Clock Number
    lbound  = (DWORD)rbound * stModeInfo.IHSyncPulseCount / stModeInfo.IHCount;   // Clock number in HSYNC pulse

#if(_SCALER_TYPE == _RTD2547D)
    CScalerSetBit(_VGIP_HV_DELAY_1E, 0x0f, 0x50);
#else
    CScalerSetBit(_VGIP_HV_DELAY_13, 0x0f, 0x50);
#endif

    rbound  = (rbound + _MEASURE_HDEALY) - 2;

    rbound  = rbound - 32;

    lbound  = (lbound + 20 + _MEASURE_HDEALY) < stModeInfo.IHStartPos ? (lbound + 20 + _MEASURE_HDEALY) : 0x0001;

    lbound  = (lbound > 32) ? (lbound - 32) : 0x0001;

    ucNoiseMarginV  &= 0xfc;

    pData[0]    = ((lbound >> 4) & 0x70) | (HIBYTE(rbound) & 0x0f);
    pData[1]    = (LOBYTE(lbound));
    pData[2]    = (LOBYTE(rbound));
    pData[3]    = (HIBYTE(stModeInfo.IVTotal - 1 + 3) & 0x0f);
    pData[4]    = (0x02);
    pData[5]    = (LOBYTE(stModeInfo.IVTotal - 1 + 3));
    CScalerWrite(_H_BOUNDARY_H_70, 6, pData, _AUTOINC);

    pData[0]    = ucNoiseMarginV;
    pData[1]    = ucNoiseMarginV;
    pData[2]    = ucNoiseMarginV;
    pData[3]    = 0x00;
    pData[4]    = 0x00;
    pData[5]    = 0x00;
    pData[6]    = 0x00;
    pData[7]    = 0x01;
    CScalerWrite(_RED_NOISE_MARGIN_76, 8, pData, _AUTOINC);

    pData[0]    = CAutoWaitFinish();

    if(pData[0] != _ERROR_SUCCESS)   return pData[0];

    CScalerRead(_V_START_END_H_7E, 3, &pData[8], _AUTOINC);

    usVStartPos = (((WORD)(pData[8] & 0xf0 ) << 4) | (WORD)pData[9]) + 3;
    usVEndPos   = (((WORD)(pData[8] & 0x0f ) << 8) | (WORD)pData[10]) + 3;

    // Check all black
    if(usVEndPos == 0x0000)         return  _ERROR_ABORT;

    // Update auto-tracking window vertical range
    pData[0]    = (pData[8] & 0x7f);
    pData[1]    = pData[9];
    pData[2]    = pData[10];
    CScalerWrite(_V_BOUNDARY_H_73, 3, pData, _AUTOINC);

    return _ERROR_SUCCESS;
}

//--------------------------------------------------
// Description  : Auto phase search function
// Input Value  : 
// Output Value : 
//--------------------------------------------------
DWORD CAutoPhaseSearch(BYTE ucSelColor, BYTE ucSelStep, BYTE ucSelStepNum, BYTE ucSelStepStart, BYTE *ucPhaseResult)
{
    DWORD maxsum;
    BYTE  count, best;

    CScalerSetByte(_AUTO_ADJ_CTRL1_7D, 0x00);
 
    CScalerSetBit(_AUTO_ADJ_CTRL0_7A, ~(_BIT1 | _BIT0), ucSelColor & 0x03);
   
    // Issac : Because H/W auto phase search may cause underflow at start and stop,
    //         frame-sync watch-dog must be disabled.
    //CAdjustDisableWatchDog(_WD_ALL);

    if(((DWORD)stModeInfo.IHFreq * stModeInfo.IHTotal / 1000) < 530)
    {
        ucSelStep += 1;
        ucSelStepStart *= 2;

#if (_SCALER_TYPE == _RTD2553V || _SCALER_TYPE == _RTD2546N || _SCALER_TYPE == _RTD2525L)
        if (ucSelStepStart >= 64)   CScalerSetBit(_PLL2_WD_A8, ~_BIT1, _BIT1);
#elif(_SCALER_TYPE == _RTD2547D)
        CScalerPageSelect(_PAGE1);
        if (ucSelStepStart >= 64)   CScalerSetBit(_P1_PLL2_WD_B1, ~_BIT1, _BIT1);
#else
        if (ucSelStepStart >= 64)   CScalerSetBit(_PLL2_WD_A8, ~_BIT1, 0);
#endif
    }

    CScalerSetByte(_HW_AUTO_PHASE_CTRL0_7B, (ucSelStep & 0x07) | (((ucSelStepNum - 1) & 0x1f) << 3));
    CScalerSetByte(_HW_AUTO_PHASE_CTRL1_7C, 0x00 | (ucSelStepStart & 0x3f));

    ucSelStep   = (0x01 << ucSelStep);
    ucSelColor  = ucSelStepStart + (ucSelStepNum) * ucSelStep;
    count       = ucSelStepStart;
    maxsum      = 0;
    best        = 0;

    // Issac : Using Wait_For_Event(EVENT_IVS) instead of Wait_For_IVS().
    //         Because H/W auto phase search may cause underflow at start and stop. 
    //         Wait_For_Event() will not check underflow/overflow.
    CScalerSetByte(_AUTO_ADJ_CTRL1_7D, 0x7b);

    CAutoWaitForIVS(1);

    do
    {
        if(CAutoWaitForIVS(((CScalerGetBit(_AUTO_ADJ_CTRL0_7A, _BIT1 | _BIT0) == 0x03) ? 3 : 1)) & (_EVENT_UNDERFLOW | _EVENT_OVERFLOW))
        {
            CScalerSetByte(_AUTO_ADJ_CTRL1_7D, 0x00);
#if (_SCALER_TYPE == _RTD2553V || _SCALER_TYPE == _RTD2546N || _SCALER_TYPE == _RTD2525L)
            CScalerSetBit(_PLL2_WD_A8, ~_BIT1, 0);
#elif(_SCALER_TYPE == _RTD2547D)
            CScalerPageSelect(_PAGE1);
            CScalerSetBit(_P1_PLL2_WD_B1, ~_BIT1, 0x00);
#else
            CScalerSetBit(_PLL2_WD_A8, ~_BIT1, _BIT1);
#endif

            return 0xffffffff;
        }

        CScalerRead(_AUTO_PHASE_3_84, 3, pData, _AUTOINC);

        pData[3]    = 0;

        if(((DWORD *)pData)[0] > maxsum)
        {
            maxsum  = ((DWORD *)pData)[0];
            best    = count;
        }

        count += ucSelStep;
    }
    while(count < ucSelColor);

    CScalerSetByte(_AUTO_ADJ_CTRL1_7D, 0x00);
#if (_SCALER_TYPE == _RTD2553V || _SCALER_TYPE == _RTD2546N || _SCALER_TYPE == _RTD2525L)
    CScalerSetBit(_PLL2_WD_A8, ~_BIT1, 0);
#elif(_SCALER_TYPE == _RTD2547D)
    CScalerPageSelect(_PAGE1);
    CScalerSetBit(_P1_PLL2_WD_B1, ~_BIT1, 0x00);
#else
    CScalerSetBit(_PLL2_WD_A8, ~_BIT1, _BIT1);
#endif

    CTimerWaitForEvent(_EVENT_IVS);

    pData[0] = CAutoWaitFinish();

    if(pData[0] != _ERROR_SUCCESS)  return 0xffffffff;

    if(((DWORD)stModeInfo.IHFreq * stModeInfo.IHTotal / 1000) < 530)
    {
        *ucPhaseResult = best / 2;
    }
    else
    {
        *ucPhaseResult = best;
    }

    return maxsum;
}

//--------------------------------------------------
// Description  : Get phase SOD information
// Input Value  : ucColor   --> Color we measure
// Output Value : Measure status
//--------------------------------------------------
BYTE CAutoReadPhaseInfo(BYTE ucColor)
{
    CScalerSetBit(_AUTO_ADJ_CTRL0_7A, ~(_BIT1 | _BIT0), ucColor & 0x03);
    CScalerSetByte(_AUTO_ADJ_CTRL1_7D, 0x3b);

    pData[0] = CAutoWaitFinish();

    if(_ERROR_SUCCESS != pData[0])  return pData[0];

    CScalerRead(_AUTO_PHASE_3_84, 4, pData, _AUTOINC);

    return _ERROR_SUCCESS;
}

//--------------------------------------------------
// Description  : Auto clock process
// Input Value  : None
// Output Value : Measure status
//--------------------------------------------------
BYTE CAutoDoAutoClock(void)
{
    BYTE    result, phase;
    WORD    count, delta, stop;
    DWORD   maxval;

    stModeUserData.Clock = stModeInfo.IHTotal;
    stModeUserData.Clock &= 0xfffc;
    CAdjustAdcClock(stModeUserData.Clock);

    result  = CAutoMeasurePositionV(_MIN_NOISE_MARGIN);

    if(result != _ERROR_SUCCESS)    return result;

    delta   = (stModeInfo.IHTotal - stModeInfo.IHWidth * 8 / 10) / 2;

    stop    = 0;
    count   = 10;

    do
    {
        // Measure Horizontal Start/End
        result      = CAutoMeasurePositionH(_MIN_NOISE_MARGIN + 0x10);

        if(result != _ERROR_SUCCESS)    return result;

        usHEndPos   = usHEndPos + 1 - usHStartPos;

        if(usHEndPos < stModeInfo.IHWidth)
        {
            if((stModeInfo.IHWidth - usHEndPos) >= (2 * delta))
            {
                stop    = 1;
            }
            else
            {
                usHStartPos = (DWORD)(stModeInfo.IHWidth - usHEndPos) * (stModeUserData.Clock)
                            / (DWORD)stModeInfo.IHWidth;

                if(usHStartPos <= 2)    break;

                usHStartPos = (usHStartPos + 2) & 0xfffc;

                //if((usHStartPos + stModeUserData.Clock - stModeInfo.IHTotal) > usDelta)
                if((usHStartPos + stModeUserData.Clock) > (delta + stModeInfo.IHTotal))
                {
                    stop    = 1;
                }
                else
                {
                    stModeUserData.Clock += usHStartPos;
                }
            }
        }
        else
        {
            if((usHEndPos - stModeInfo.IHWidth) >= (2 * delta))
            {
                stop    = 1;
            }
            else
            {
                usHStartPos = (DWORD)(usHEndPos - stModeInfo.IHWidth) * (stModeUserData.Clock)
                            / (DWORD)stModeInfo.IHWidth;

                if(usHStartPos <= 2)    break;

                usHStartPos = (usHStartPos + 2) & 0xfffc;

                //if((stModeInfo.IHTotal - (stModeUserData.Clock - usHStartPos)) > usDelta)
                if((usHStartPos + stModeInfo.IHTotal) > (delta + stModeUserData.Clock))
                {
                    stop    = 1;
                }
                else
                {
                    stModeUserData.Clock -= usHStartPos;
                }
            }
        }

        if(stop)   break;

        CAdjustAdcClock(stModeUserData.Clock);
    }
    while(--count);

    if((count == 0) || (stop == 1))   return _ERROR_ABORT;

    // Prevent from 1/2-line moire and smear effect.
    if((usHEndPos >= stModeInfo.IHWidth && (stModeUserData.Clock - stModeInfo.IHTotal) == 4)
       || (usHEndPos < stModeInfo.IHWidth && (stModeInfo.IHTotal - stModeUserData.Clock) == 4))
    {
        stModeUserData.Clock = stModeInfo.IHTotal;
        CAdjustAdcClock(stModeUserData.Clock);

        result    = CAutoMeasurePositionH(_MIN_NOISE_MARGIN + 0x10);

        if(result != _ERROR_SUCCESS)       return result;

        usHEndPos   = usHEndPos + 1 - usHStartPos;
    }

#if(_AUTO_CLOCK_PRECISION < 4)

    // Save 4N clock
    stop    = stModeUserData.Clock;

    stModeUserData.Clock += (stModeInfo.IHWidth >= usHEndPos) ? 4 : 2;

    CAdjustAdcClock(stModeUserData.Clock);

    // Set threshold for Clock Search
    CScalerSetByte(_DIFF_THRESHOLD_79, 0x18);

    count   = stop;
    maxval  = 0;
    delta   = 6;    // Initial value must be (N * AUTO_CLOCK_STEP)
    do
    {
        result    = CAutoMeasurePositionH(_MIN_NOISE_MARGIN + 0x10);

        if(result != _ERROR_SUCCESS)       return result;

        usHEndPos   = usHEndPos + 1 - usHStartPos;
        
        if(usHEndPos > (stModeInfo.IHWidth + 2))
        {
            ((DWORD *)pData)[0]   = 0;
        }
        else
        {
            ((DWORD *)pData)[0]   = CAutoPhaseSearch(_COLOR_SELECT, _HWAUTO_STEP_8, HWAUTOSTEPNUM(8), HWAUTOSTEPSTART(0), &phase);

            if (0xffffffffL == ((DWORD *)pData)[0])   return _ERROR_INPUT;
        }

        if(maxval < ((DWORD *)pData)[0])
        {
            maxval    = ((DWORD *)pData)[0];
            count     = stModeUserData.Clock;
        }

        if(delta == 0x00)
        {
            // Check if default clock is the best when clock searching range is larger than default.
            if(stModeUserData.Clock > stModeInfo.IHTotal)
            {
                stModeUserData.Clock = stModeInfo.IHTotal;
                CAdjustAdcClock(stModeUserData.Clock);
                continue;            
            }
            break;
        }

        delta                   -= _AUTO_CLOCK_PRECISION;
        stModeUserData.Clock    -= _AUTO_CLOCK_PRECISION;
        CAdjustAdcClock(stModeUserData.Clock);
    }
    while(_TRUE); 

    maxval = maxval / 3;

    stModeUserData.Clock    = (maxval > ((DWORD)stModeInfo.IHWidth << 10)) ? count : stop;
    CAdjustAdcClock(stModeUserData.Clock);

#endif

    return _ERROR_SUCCESS;
}

//--------------------------------------------------
// Description  : Auto phase process
// Input Value  : None
// Output Value : Measure status
//--------------------------------------------------
BYTE CAutoDoAutoPhase(void)
{
    BYTE  result, phase, best;
    DWORD maxsum, temp0, temp1, temp2;

    result = CAutoMeasurePositionH(_MIN_NOISE_MARGIN);
    if(_ERROR_SUCCESS != result)  return result;

    // Set threshold 0x80 for Phase Search
    CScalerSetByte(_DIFF_THRESHOLD_79, 0x80);

    maxsum  = CAutoPhaseSearch(_COLOR_SELECT, _HWAUTO_STEP_8, HWAUTOSTEPNUM(8), HWAUTOSTEPSTART(0), &result);
    if(maxsum == 0xffffffffL)     return _ERROR_INPUT;
    if(maxsum == 0)               return _ERROR_ABORT;

    if(maxsum < ((DWORD)stModeInfo.IVHeight * 1024 * 3 / 2))
    {
        // Decrease threshold to 0x40 for Phase Search
        CScalerSetByte(_DIFF_THRESHOLD_79, 0x40);

        maxsum  = CAutoPhaseSearch(_COLOR_SELECT, _HWAUTO_STEP_8, HWAUTOSTEPNUM(8), HWAUTOSTEPSTART(0), &result);
        if(maxsum == 0xffffffffL)     return _ERROR_INPUT;
        if(maxsum == 0)               return _ERROR_ABORT;

        if(maxsum < ((DWORD)stModeInfo.IVHeight * 1024 * 3 / 2))
            return _ERROR_PHASE;
    }

    // Issac:
    // Please do not delete these backup code below.
/*
    if(((DWORD)stModeInfo.IHFreq * stModeInfo.IHTotal / 1000) < 530)
    {
        BYTE  count, ucSelStep, ucSelColor;

        CScalerSetByte(_AUTO_ADJ_CTRL1_7D, 0x00);

        ucSelStep   = (0x01 << _HWAUTO_STEP_2);
        count       = ((result - 8) & 0x3f);
        ucSelColor  = count + (8 * ucSelStep);
        maxsum      = 0;
        best        = 0;

        do
        {
            CAdjustPhase(count);

            if(_ERROR_SUCCESS != CAutoReadPhaseInfo(_COLOR_SELECT))   return _ERROR_INPUT;

            if(((DWORD *)pData)[0] > maxsum)
            {
                maxsum  = ((DWORD *)pData)[0];
                best    = count;
            }

            count += ucSelStep;
        }
        while(count < ucSelColor);

        CScalerSetByte(_AUTO_ADJ_CTRL1_7D, 0x00);

        result = best & 0x3f;
    }
    else
*/
    {
        maxsum  = CAutoPhaseSearch(_COLOR_SELECT, _HWAUTO_STEP_2, HWAUTOSTEPNUM(8), HWAUTOSTEPSTART((result - 8) & 0x3f), &result);
        if(maxsum == 0xffffffffL)     return _ERROR_INPUT;
        if(maxsum == 0)               return _ERROR_ABORT;
    }

    // Search phase by weighting SOD
    phase   = (result - 3) & 0x3f;
    CAdjustPhase(phase);

    if(_ERROR_SUCCESS != CAutoReadPhaseInfo(_COLOR_SELECT))   return _ERROR_INPUT;
    temp0   = ((DWORD *)pData)[0];

    phase   = (phase + 1) & 0x3f;
    CAdjustPhase(phase);

    if(_ERROR_SUCCESS != CAutoReadPhaseInfo(_COLOR_SELECT))   return _ERROR_INPUT;
    temp1   = ((DWORD *)pData)[0];

    result  = (result + 3) & 0x3f;
    maxsum  = 0;
    do
    {
        phase   = (phase + 1) & 0x3f;
        CAdjustPhase(phase);

        if(_ERROR_SUCCESS != CAutoReadPhaseInfo(_COLOR_SELECT))   return _ERROR_INPUT;

        temp2   = ((DWORD *)pData)[0];

        ((DWORD *)pData)[0] = temp2 + temp1 + temp0
                              - ((temp1 > temp0 ? temp1 - temp0 : temp0 - temp1) / 2)
                              - ((temp1 > temp2 ? temp1 - temp2 : temp2 - temp1) / 2);

        if(((DWORD *)pData)[0] > maxsum)
        {
            maxsum  = ((DWORD *)pData)[0];
            best    = (phase - 1) & 0x3f;
        }

        temp0   = temp1;
        temp1   = temp2;
    }
    while(phase != result);

    stModeUserData.Phase    = best;
    CAdjustPhase(stModeUserData.Phase);

    CScalerSetByte(_DIFF_THRESHOLD_79, 0x40);

    return _ERROR_SUCCESS;
}

//--------------------------------------------------
// Description  : Auto position process
// Input Value  : None
// Output Value : Measure status
//--------------------------------------------------
BYTE CAutoDoAutoPosition(void)
{
    BYTE result;
    SWORD dtemp, ctemp, atemp;

    result  = CAutoMeasurePositionV(_MIN_NOISE_MARGIN);
    if(_ERROR_SUCCESS != result)    return result;

    result  = CAutoMeasurePositionH(_MIN_NOISE_MARGIN);
    if(_ERROR_SUCCESS != result)    return result;

    /////////////////////////////////
    // Calculate Vertical Position //
    /////////////////////////////////
#if(_SCALER_TYPE == _RTD2547D)
    CScalerRead(_IPV_ACT_STA_H_18, 2, pData, _AUTOINC);
    ctemp = (((WORD)(pData[0] & 0x07)) << 8) | pData[1];

    CScalerRead(_IVS_DELAY_1C, 1, pData, _AUTOINC);
    CScalerRead(_VGIP_HV_DELAY_1E, 1, &pData[1], _AUTOINC);
#else
    CScalerRead(_IPV_ACT_STA_H_0D, 2, pData, _AUTOINC);
    ctemp = (((WORD)(pData[0] & 0x07)) << 8) | pData[1];

    CScalerRead(_IVS_DELAY_11, 1, pData, _AUTOINC);
    CScalerRead(_VGIP_HV_DELAY_13, 1, &pData[1], _AUTOINC);
#endif
    dtemp = (((WORD)(pData[1] & _BIT1)) << 8) | pData[0];

    dtemp = usVStartPos - dtemp;

    atemp = (stModeInfo.IVHeight - (usVEndPos - usVStartPos + 1));

    if(atemp > 3)
        atemp = abs(usVEndPos - usVStartPos + 1 - stModeInfo.IVHeight) / 2;
    else
        atemp = 0;

    while(_TRUE)
    {
#if(_V_POSITION_DIRECTION == _V_POSITION_METHOD_0)
        if(abs(stModeUserData.VPosition + (ctemp - dtemp) - stModeInfo.IVStartPos + atemp) <= ucVStartBias)
        {
            stModeUserData.VPosition += ctemp - dtemp + atemp;
#endif

#if(_V_POSITION_DIRECTION == _V_POSITION_METHOD_1)
        if(abs(stModeUserData.VPosition - (ctemp - dtemp) - stModeInfo.IVStartPos - atemp) <= ucVStartBias)
        {
            stModeUserData.VPosition -= ctemp - dtemp + atemp;
#endif
            break;
        }
        else
        {
            stModeUserData.VPosition = stModeInfo.IVStartPos;
            break;
        }
    }

    CAdjustVPosition();

    ///////////////////////////////////
    // Calculate Horizontal Position //
    ///////////////////////////////////
#if(_SCALER_TYPE == _RTD2547D)
    CScalerRead(_IPH_ACT_STA_H_14, 2, pData, _AUTOINC);
    ctemp = (((WORD)(pData[0] & 0x07)) << 8) | pData[1];

    CScalerRead(_IHS_DELAY_1D, 2, pData, _AUTOINC);
#else
    CScalerRead(_IPH_ACT_STA_H_09, 2, pData, _AUTOINC);
    ctemp = (((WORD)(pData[0] & 0x07)) << 8) | pData[1];

    CScalerRead(_IHS_DELAY_12, 2, pData, _AUTOINC);
#endif
    dtemp = (((WORD)(pData[1] & _BIT0)) << 8) | pData[0];

    dtemp = usHStartPos - dtemp - 2;

    while(_TRUE)
    {
        if(abs(stModeUserData.HPosition + (ctemp - dtemp) - stModeInfo.IHStartPos) <= ucHStartBias)
        {
            stModeUserData.HPosition += ctemp - dtemp;
            break;
        }
        else
        {
            stModeUserData.HPosition = stModeInfo.IHStartPos;
            break;
        }
    }

    CAdjustHPosition();

    return _ERROR_SUCCESS;
}

//--------------------------------------------------
// Description  : Tune ADC gain and offset
// Input Value  : None
// Output Value : Measure status
//--------------------------------------------------
BYTE CAutoTuneBalance(void)
{                
    bit flag = 1;
    BYTE rev, result0, result1, color, count;

    for(count=0;count<3;count++)
    {
        stAdcData.AdcGain[count] = 0x80;
        stAdcData.AdcOffset[count] = 0x80;
    }

    CAdjustAdcGainOffset();

    rev = CAutoMeasurePositionV(_MIN_NOISE_MARGIN);
    if(rev != _ERROR_SUCCESS)    return rev;

    rev = CAutoMeasurePositionH(_MIN_NOISE_MARGIN);
    if(rev != _ERROR_SUCCESS)   return rev;

    if(CAutoMeasureColor(_BLUE, _MEASURE_COLORS_MAX, &rev) != _ERROR_SUCCESS)       return _ERROR_ABORT;
    if(rev < 0x60)              return _ERROR_ABORT;

    if(CAutoMeasureColor(_GREEN, _MEASURE_COLORS_MAX, &rev) != _ERROR_SUCCESS)      return _ERROR_ABORT;
    if(rev < 0x60)              return _ERROR_ABORT;

    if(CAutoMeasureColor(_RED, _MEASURE_COLORS_MAX, &rev) != _ERROR_SUCCESS)        return _ERROR_ABORT;
    if(rev < 0x60)              return _ERROR_ABORT;


    ucAdcPGA = 5;
#if(_SCALER_TYPE == _RTD2547D)
    CScalerPageSelect(_PAGE0); //V401 modify
    CScalerSetBit(_P0_ADC_CTRL_A1, ~(_BIT5 | _BIT4), (ucAdcPGA << 4) & 0x30); //V401 modify
#elif(_SCALER_TYPE == _RTD2553V || _SCALER_TYPE == _RTD2546N || _SCALER_TYPE == _RTD2525L)
    CScalerSetDataPortBit(_ADC_ACCESS_PORT_DC, 0x00, ~(_BIT5 | _BIT4), (ucAdcPGA << 4) & 0x30);
#else
    CScalerSetBit(_ADC_RGB_CTRL_DC, ~(_BIT5 | _BIT4), (ucAdcPGA << 4) & 0x30); //V401 modify
#endif
    CTimerDelayXms(1);

    color = _BLUE;

#if (_SCALER_TYPE == _RTD2553V || _SCALER_TYPE == _RTD2546N || _SCALER_TYPE == _RTD2525L || _SCALER_TYPE == _RTD2547D)
    while(flag)
    {
        count = 0x30;

        do
        {
            rev = CAutoTuneAdcGain(color, &result0);

            if(rev == _ERROR_ABORT)     return rev;
            if(rev == _ERROR_FINISH)    break;


#if(!(((_ADC_OFFSET_ADJUSTING == _ADJUST_BY_HW_ON_LINE) || (_ADC_OFFSET_ADJUSTING == _ADJUST_BY_HW_OFF_LINE)) && (_SCALER_TYPE == _RTD2525L || _SCALER_TYPE == _RTD2547D)))

            rev = CAutoTuneAdcOffset(color, &result1);

            if(rev == _ERROR_ABORT)     return rev;

 //YPbPr Auto Color
            if((_GET_INPUT_SOURCE() == _SOURCE_YPBPR) && (color != _GREEN))
                rev = _WHITEBALANCE_BR_MIN_LEVEL;
            else
                rev = _WHITEBALANCE_MIN_LEVEL;

            if((result0 == _WHITEBALANCE_MAX_LEVEL) && (result1 == rev))
                break;

            if((count > 8) && (result0 <= (_WHITEBALANCE_MAX_LEVEL + 1)) && (result0 >= (_WHITEBALANCE_MAX_LEVEL - 1))
                && (result1 <= (rev + 1)) && (result1 >= (rev - 1)))
            {
                count = 8;
            }
 //YPbPr Auto Color

#else
            if(result0 == _WHITEBALANCE_MAX_LEVEL)
                break;
    
             if((count > 8) && (result0 <= (_WHITEBALANCE_MAX_LEVEL + 1)) && (result0 >= (_WHITEBALANCE_MAX_LEVEL - 1)))
            {
                count = 8;
            }

#endif  // End of #if(!(((_ADC_OFFSET_ADJUSTING == _ADJUST_BY_HW_ON_LINE) || (_ADC_OFFSET_ADJUSTING == _ADJUST_BY_HW_OFF_LINE)) && (_SCALER_TYPE == _RTD2525L)))
        }
        while(--count);

        if(stAdcData.AdcGain[color] > 240) 
        {
            if(ucAdcPGA == 7)
            {
                if(color == _BLUE)
                    color = _GREEN;
                else if(color == _GREEN)
                    color = _RED;
                else
                    flag = 0;
            }
            else
            {
                color = _BLUE;
                ucAdcPGA = ucAdcPGA + 1;                            
            }

#if (_SCALER_TYPE == _RTD2547D)
            CScalerPageSelect(_PAGE0); //V401 modify
            CScalerSetBit(_P0_ADC_CTRL_A1, ~(_BIT5 | _BIT4), (ucAdcPGA << 4) & 0x30); //V401 modify  
#else
            CScalerSetDataPortBit(_ADC_ACCESS_PORT_DC, 0x00, ~(_BIT5 | _BIT4), (ucAdcPGA << 4) & 0x30);   
#endif
            CTimerDelayXms(1); 
        }
        else if(stAdcData.AdcGain[color] < 30) 
        {
            if(ucAdcPGA == 4)
            {
                if(color == _BLUE)
                    color = _GREEN;
                else if(color == _GREEN)
                    color = _RED;
                else
                    flag = 0;
            }
            else
            {
                color = _BLUE;
                ucAdcPGA = ucAdcPGA - 1; 
            }

#if (_SCALER_TYPE == _RTD2547D)
            CScalerPageSelect(_PAGE0); //V401 modify
            CScalerSetBit(_P0_ADC_CTRL_A1, ~(_BIT5 | _BIT4), (ucAdcPGA << 4) & 0x30); //V401 modify  
#else
            CScalerSetDataPortBit(_ADC_ACCESS_PORT_DC, 0x00, ~(_BIT5 | _BIT4), (ucAdcPGA << 4) & 0x30);
#endif
            CTimerDelayXms(1);
        } 
        else
        {
            if(color == _BLUE)
                color = _GREEN;
            else if(color == _GREEN)
                color = _RED;
            else
                flag = 0;
        }                                           
    }

#if(((_ADC_OFFSET_ADJUSTING == _ADJUST_BY_HW_ON_LINE) || (_ADC_OFFSET_ADJUSTING == _ADJUST_BY_HW_OFF_LINE)) && (_SCALER_TYPE == _RTD2525L || _SCALER_TYPE == _RTD2547D))

    result1 = CAutoAdjustAdcOffset();
    if(result1 == _ERROR_ABORT)     return result1;

#endif  // End of #if(((_ADC_OFFSET_ADJUSTING == _ADJUST_BY_HW_ON_LINE) || (_ADC_OFFSET_ADJUSTING == _ADJUST_BY_HW_OFF_LINE)) && (_SCALER_TYPE == _RTD2525L))

#else

    while(flag)
    {
        count = 0x30;

        do
        {
            rev = CAutoTuneAdcGain(color, &result0);

            if(rev == _ERROR_ABORT)     return rev;
            if(rev == _ERROR_FINISH)    break;

            rev = CAutoTuneAdcOffset(color, &result1);

            if(rev == _ERROR_ABORT)     return rev;

 //V307 modify
            if((_GET_INPUT_SOURCE() == _SOURCE_YPBPR) && (color != _GREEN))
                rev = _WHITEBALANCE_BR_MIN_LEVEL;
            else
                rev = _WHITEBALANCE_MIN_LEVEL;

            if((result0 == _WHITEBALANCE_MAX_LEVEL) && (result1 == rev))
                break;

            if((count > 8) && (result0 <= (_WHITEBALANCE_MAX_LEVEL + 1)) && (result0 >= (_WHITEBALANCE_MAX_LEVEL - 1))
                && (result1 <= (rev + 1)) && (result1 >= (rev - 1)))
            {
                count = 8;
            }
 //V307 modify

        }
        while(--count);

        if(stAdcData.AdcGain[color] > 240) 
        {
            if(ucAdcPGA == 7)
            {
                if(color == _BLUE)
                    color = _GREEN;
                else if(color == _GREEN)
                    color = _RED;
                else
                    flag = 0;
            }
            else
            {
                color = _BLUE;
                ucAdcPGA = ucAdcPGA + 1;                            
            }

            CScalerSetBit(_ADC_RGB_CTRL_DC, ~(_BIT5 | _BIT4), (ucAdcPGA << 4) & 0x30); //V401 modify   
            CTimerDelayXms(1); 
        }
        else if(stAdcData.AdcGain[color] < 30) 
        {
            if(ucAdcPGA == 4)
            {
                if(color == _BLUE)
                    color = _GREEN;
                else if(color == _GREEN)
                    color = _RED;
                else
                    flag = 0;
            }
            else
            {
                color = _BLUE;
                ucAdcPGA = ucAdcPGA - 1; 
            }

            CScalerSetBit(_ADC_RGB_CTRL_DC, ~(_BIT5 | _BIT4), (ucAdcPGA << 4) & 0x30); //V401 modify
            CTimerDelayXms(1);
        } 
        else
        {
            if(color == _BLUE)
                color = _GREEN;
            else if(color == _GREEN)
                color = _RED;
            else
                flag = 0;
        }                                           
    }
#endif

    if((stAdcData.AdcGain[_RED] == 0x00) || (stAdcData.AdcGain[_GREEN] == 0x00) || (stAdcData.AdcGain[_BLUE] == 0x00))
        return _ERROR_ABORT;
    else
        return _ERROR_SUCCESS;
}

//--------------------------------------------------
// Description  : Get max or min color value
// Input Value  : Measure information
// Output Value : Measure status
//--------------------------------------------------
BYTE CAutoMeasureColor(BYTE ucColor, BYTE ucPar, BYTE *pMargin)
{
    CScalerSetBit(_AUTO_ADJ_CTRL0_7A, ~(_BIT2 | _BIT1 | _BIT0), (ucColor == 3) ? ucColor : ( 2 - ucColor));

    if(ucPar == _MEASURE_COLORS_MIN)
    {
        pData[0] = 0x12;
        pData[1] = 0x80;
        pData[2] = 0x00;
        pData[3] = 0x00;
        pData[4] = (usVStartPos > 9) ? 9 : (usVStartPos - 1);
        pData[5] = pData[4] + 1;
    }
    else
    {
        pData[0] = ((usHStartPos >> 4) & 0x70) | (HIBYTE(usHEndPos) & 0x0f);
        pData[1] = (LOBYTE(usHStartPos));
        pData[2] = (LOBYTE(usHEndPos));
        pData[3] = ((usVStartPos >> 4) & 0x70) | (HIBYTE(usVEndPos) & 0x0f);
        pData[4] = (LOBYTE(usVStartPos));
        pData[5] = (LOBYTE(usVEndPos));
    }
    CScalerWrite(_H_BOUNDARY_H_70, 6, pData, _AUTOINC);

    CScalerSetByte(_AUTO_ADJ_CTRL1_7D, 0x01 | ((ucPar & 0x01) << 5));

    pData[0] = CAutoWaitFinish();

    if(pData[0] != _ERROR_SUCCESS)       return pData[0];

    CScalerRead(_AUTO_PHASE_0_87, 1, pMargin, _AUTOINC);

    if(ucPar == _MEASURE_COLORS_MIN)
        *pMargin ^= 0xff;

    return _ERROR_SUCCESS;
}

//--------------------------------------------------
// Description  : Adjust ADC gain
// Input Value  : Adjusting setting
// Output Value : Measure status
//--------------------------------------------------
BYTE CAutoTuneAdcGain(BYTE ucColor, BYTE *pMargin)
{
    BYTE temp;

    if(CAutoMeasureColor(ucColor, _MEASURE_COLORS_MAX, pMargin) != _ERROR_SUCCESS)
        return _ERROR_ABORT;

    if(*pMargin > _WHITEBALANCE_MAX_LEVEL)
    {
        temp  = *pMargin - _WHITEBALANCE_MAX_LEVEL;
                
        // Non-zero return value of Change_ADC_Gain() means ADC gain reaches maximum.
        if(CAutoChangeAdcGain(ucColor, temp, 0))                  // Increase Gain; Decrease Contrast
        {
            if(CAutoChangeAdcOffset(ucColor, 4, 0))               // Increase Offset; Decrease Brightness
                return _ERROR_FINISH;
        }
    }
    else if(*pMargin < _WHITEBALANCE_MAX_LEVEL)
    {
        temp  = _WHITEBALANCE_MAX_LEVEL - *pMargin;

        // Non-zero return value of Change_ADC_Gain() means ADC gain reaches minimum.
        if(CAutoChangeAdcGain(ucColor, temp, 1))                  // Decrease Gain; Increase Contrast
        {
            if(CAutoChangeAdcOffset(ucColor, 4, 1))               // Decrease Offset; Increase Brightness
                return _ERROR_FINISH;
        }
    }

    return _ERROR_SUCCESS;
}

#if (_SCALER_TYPE == _RTD2553V || _SCALER_TYPE == _RTD2546N || _SCALER_TYPE == _RTD2525L || _SCALER_TYPE == _RTD2547D)
#if(!(((_ADC_OFFSET_ADJUSTING == _ADJUST_BY_HW_ON_LINE) || (_ADC_OFFSET_ADJUSTING == _ADJUST_BY_HW_OFF_LINE)) && (_SCALER_TYPE == _RTD2525L || _SCALER_TYPE == _RTD2547D)))
//--------------------------------------------------
// Description  : Adjust ADC offset
// Input Value  : Adjusting setting
// Output Value : Measure status
//--------------------------------------------------
BYTE CAutoTuneAdcOffset(BYTE ucColor, BYTE *pMargin) //YPbPr Auto Color
{
    BYTE temp, level;

    if((_GET_INPUT_SOURCE() == _SOURCE_YPBPR) && (ucColor != _GREEN))
        level = _WHITEBALANCE_BR_MIN_LEVEL;
    else
        level = _WHITEBALANCE_MIN_LEVEL;

    if(CAutoMeasureColor(ucColor, _MEASURE_COLORS_MIN, pMargin) != _ERROR_SUCCESS)
        return _ERROR_ABORT;

    if(*pMargin > level)
    {
        temp = *pMargin - level;

        CAutoChangeAdcOffset(ucColor, ((temp > 8) ? 8 : temp), 0);     // Increase Offset; Decrease Brightness
    }
    else if(*pMargin < level)
    {
        temp = level - *pMargin;

        if((_GET_INPUT_SOURCE() == _SOURCE_YPBPR) && (ucColor != _GREEN))
        {
            CAutoChangeAdcOffset(ucColor, ((temp > 8) ? 8 : temp), 1);
        }
        else
        {
            if(*pMargin == 0)
                CAutoChangeAdcOffset(ucColor, temp + 4, 1);       // Decrease Offset; Increase Brightness
            else
                CAutoChangeAdcOffset(ucColor, temp, 1);           // Decrease Offset; Increase Brightness
        }
    }

    return _ERROR_SUCCESS;
}
#endif  //End of #if(!(((_ADC_OFFSET_ADJUSTING == _ADJUST_BY_HW_ON_LINE) || (_ADC_OFFSET_ADJUSTING == _ADJUST_BY_HW_OFF_LINE)) && (_SCALER_TYPE == _RTD2525L || _SCALER_TYPE == _RTD2547D)))

#else

//--------------------------------------------------
// Description  : Adjust ADC offset
// Input Value  : Adjusting setting
// Output Value : Measure status
//--------------------------------------------------
BYTE CAutoTuneAdcOffset(BYTE ucColor, BYTE *pMargin) //V307 modify
{
    BYTE temp, level;

    if((_GET_INPUT_SOURCE() == _SOURCE_YPBPR) && (ucColor != _GREEN))
        level = _WHITEBALANCE_BR_MIN_LEVEL;
    else
        level = _WHITEBALANCE_MIN_LEVEL;

    if(CAutoMeasureColor(ucColor, _MEASURE_COLORS_MIN, pMargin) != _ERROR_SUCCESS)
        return _ERROR_ABORT;

    if(*pMargin > level)
    {
        temp = *pMargin - level;

        CAutoChangeAdcOffset(ucColor, ((temp > 8) ? 8 : temp), 0);     // Increase Offset; Decrease Brightness
    }
    else if(*pMargin < level)
    {
        temp = level - *pMargin;

        if((_GET_INPUT_SOURCE() == _SOURCE_YPBPR) && (ucColor != _GREEN))
        {
            CAutoChangeAdcOffset(ucColor, ((temp > 8) ? 8 : temp), 1);
        }
        else
        {
            if(*pMargin == 0)
                CAutoChangeAdcOffset(ucColor, temp + 4, 1);       // Decrease Offset; Increase Brightness
            else
                CAutoChangeAdcOffset(ucColor, temp, 1);           // Decrease Offset; Increase Brightness
        }
    }

    return _ERROR_SUCCESS;
}

#endif
//--------------------------------------------------
// Description  : Change ADC gain
// Input Value  : Input information
// Output Value : Return 1 if overrange
//--------------------------------------------------
BYTE CAutoChangeAdcGain(BYTE ucColor, BYTE ucDelta, BYTE ucInc)
{
    BYTE overrange = 0;

    if(ucInc)
    {
        if(stAdcData.AdcGain[ucColor] >= ucDelta)
            stAdcData.AdcGain[ucColor] -= ucDelta;
        else
        {
            stAdcData.AdcGain[ucColor] = 0;
            overrange = 1;
        }
    }
    else
    {
        if ((0xff - ucDelta) >= stAdcData.AdcGain[ucColor])
            stAdcData.AdcGain[ucColor] += ucDelta;
        else
        {
            stAdcData.AdcGain[ucColor] = 0xff;
            overrange = 1;
        }
    }

    CAdjustAdcGain();
    
    return overrange;
}

//--------------------------------------------------
// Description  : Change ADC offset
// Input Value  : Input information
// Output Value : Return 1 if overrange
//--------------------------------------------------
BYTE CAutoChangeAdcOffset(BYTE ucColor, BYTE ucDelta, BYTE ucInc)
{
    BYTE overrange = 0;

    if(ucInc)
    {
        if(stAdcData.AdcOffset[ucColor] >= ucDelta)
            stAdcData.AdcOffset[ucColor] -= ucDelta;
        else
        {
            stAdcData.AdcOffset[ucColor] = 0;
            overrange = 1;
        }
    }
    else
    {
        if ((0xff - ucDelta) >= stAdcData.AdcOffset[ucColor])
            stAdcData.AdcOffset[ucColor] += ucDelta;
        else
        {
            stAdcData.AdcOffset[ucColor] = 0xff;
            overrange = 1;
        }
    }

    CAdjustAdcOffset();
    
    return overrange;
}

#if (_SCALER_TYPE == _RTD2553V || _SCALER_TYPE == _RTD2546N || _SCALER_TYPE == _RTD2525L || _SCALER_TYPE == _RTD2547D)
#if(((_ADC_OFFSET_ADJUSTING == _ADJUST_BY_HW_ON_LINE) || (_ADC_OFFSET_ADJUSTING == _ADJUST_BY_HW_OFF_LINE)) && (_SCALER_TYPE == _RTD2525L || _SCALER_TYPE == _RTD2547D))         
//--------------------------------------------------
// Description  : H/W Auto Adjust ADC offset
// Input Value  : None
// Output Value : Measure status
//--------------------------------------------------
BYTE CAutoAdjustAdcOffset(void)
{
    BYTE pABL[6],ablmode=0;
              
    pABL[0] = (((_GET_INPUT_SOURCE() == _SOURCE_YPBPR) ? 1 : 0) << 7) | (ablmode << 6) | (_ABL_REGION_IN_EACH_LINE << 4) | 0x00; //V307 modify  
    pABL[1] = (_LINE_AVERAGED << 6) | _START_POSITION_OF_ABL | 0x00;
    pABL[2] = (((_WHITEBALANCE_MIN_LEVEL -1) & 0x03) << 4) | (_LOCK_MARGIN << 2) | (BYTE)(_END_LINE_OF_ABL >> 8) | 0x00;
    pABL[3] = (BYTE)_END_LINE_OF_ABL | 0x00;
    pABL[4] = (_EQUAL_MARGIN << 6) | _START_POSITION_OF_ABL | 0x00;
    pABL[5] = (_LARGE_ERROR_MARGIN << 6) | (_MAX_FRAME_COUNT << 4) | _LINE_DELAY | 0x00l;
    
#if(_SCALER_TYPE == _RTD2547D)
    CScalerPageSelect(_PAGE0);
    CScalerWrite(_P0_AUTO_BLACK_LEVEL_CTRL1_C0, 6, pABL, _AUTOINC);    

    CScalerSetBit(_P0_AUTO_BLACK_LEVEL_CTRL1_C0, ~_BIT0, 0x00);
    CScalerSetBit(_P0_AUTO_BLACK_LEVEL_CTRL1_C0, ~_BIT0, _BIT0); //Enable ABL
#else
    CScalerSetByte(_ADC_ACCESS_PORT_DC,0x80);
    CScalerSetByte(_ADC_ACCESS_PORT_DC,0x98);
    CScalerWrite(_ADC_DATA_PORT_DD, 6, pABL, _NON_AUTOINC);    

    CScalerSetDataPortBit(_ADC_ACCESS_PORT_DC, 0x18, ~_BIT0, 0x00);
    CScalerSetDataPortBit(_ADC_ACCESS_PORT_DC, 0x18, ~_BIT0, _BIT0); //Enable ABL
#endif

    if(CTimerPollingEventProc(255, CMiscAutoAdjustAdcOffsetFlagPollingEvent))
    {
#if(_SCALER_TYPE == _RTD2547D)
        if(CScalerGetBit(_P0_AUTO_BLACK_LEVEL_CTRL1_C0, _BIT3 | _BIT2 | _BIT1) == 0x0E)
#else
        if(CScalerGetDataPortBit(_ADC_ACCESS_PORT_DC, 0x18, _BIT3 | _BIT2 | _BIT1) == 0x0E)
#endif
        {
#if(_SCALER_TYPE == _RTD2547D)
            CScalerRead(_P0_RED_OFFSET_A8, 3, pABL, _AUTOINC);
#else
            CScalerSetByte(_ADC_ACCESS_PORT_DC, 0x80);
            CScalerSetByte(_ADC_ACCESS_PORT_DC, 0x87);
            CScalerRead(_ADC_DATA_PORT_DD, 3, pABL, _NON_AUTOINC);
            CScalerSetByte(_ADC_ACCESS_PORT_DC, 0x00);
#endif

            stAdcData.AdcOffset[_RED] = pABL[0];
            stAdcData.AdcOffset[_GREEN] = pABL[1];
            stAdcData.AdcOffset[_BLUE] = pABL[2];

#if(_ADC_OFFSET_ADJUSTING == _ADJUST_BY_HW_ON_LINE)

            ablmode = 1;
            pABL[0] = (_ABL_MODE << 7) | (ablmode << 6) | (_ABL_REGION_IN_EACH_LINE << 4) | 0x00;
#if(_SCALER_TYPE == _RTD2547D)
            CScalerWrite(_P0_AUTO_BLACK_LEVEL_CTRL1_C0, 1, pABL, _NON_AUTOINC);
#else
            CScalerWrite(_ADC_DATA_PORT_DD, 1, pABL, _NON_AUTOINC);
#endif

#endif  // End of  #if(_ADC_OFFSET_ADJUSTING == _ADJUST_BY_HW_ON_LINE)

            return _ERROR_SUCCESS;
        }
        else
        {
            return _ERROR_ABORT;
        }
    }
    else
    {
        return _ERROR_ABORT;
    }
}

#endif  // End of #if(((_ADC_OFFSET_ADJUSTING == _ADJUST_BY_HW_ON_LINE) || (_ADC_OFFSET_ADJUSTING == _ADJUST_BY_HW_OFF_LINE)) && (_SCALER_TYPE == _RTD2525L || _SCALER_TYPE == _RTD2547D))
#endif  // end #if (_SCALER_TYPE == _RTD2553V || _SCALER_TYPE == _RTD2546N || _SCALER_TYPE == _RTD2525L || _SCALER_TYPE == _RTD2547D)


