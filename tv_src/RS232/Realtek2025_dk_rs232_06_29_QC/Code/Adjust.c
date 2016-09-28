//----------------------------------------------------------------------------------------------------
// ID Code      : Adjust.c No.0004
// Update Note  : 
//
//----------------------------------------------------------------------------------------------------

#define __ADJUST__

#include "Header\Include.h"


//--------------------------------------------------
// Description  : Adjust IHS delay
// Input Value  : IHS delay
// Output Value : None
//--------------------------------------------------
void CAdjustIHSDelay(WORD usIHSDelay)
{
#if(_SCALER_TYPE == _RTD2547D)
    CScalerSetBit(_VGIP_HV_DELAY_1E, ~_BIT0, HIBYTE(usIHSDelay) & _BIT0);
    CScalerSetByte(_IHS_DELAY_1D, LOBYTE(usIHSDelay));
#else
    CScalerSetBit(_VGIP_HV_DELAY_13, ~_BIT0, HIBYTE(usIHSDelay) & _BIT0);
    CScalerSetByte(_IHS_DELAY_12, LOBYTE(usIHSDelay));
#endif    
}

//--------------------------------------------------
// Description  : Adjust IVS delay
// Input Value  : IVS delay
// Output Value : None
//--------------------------------------------------
void CAdjustIVSDelay(WORD usIVSDelay)
{
#if(_SCALER_TYPE == _RTD2547D)
    CScalerSetBit(_VGIP_HV_DELAY_1E, ~_BIT1, (usIVSDelay >> 7) & _BIT1);
    CScalerSetByte(_IVS_DELAY_1C, LOBYTE(usIVSDelay));
#else
    CScalerSetBit(_VGIP_HV_DELAY_13, ~_BIT1, (usIVSDelay >> 7) & _BIT1);
    CScalerSetByte(_IVS_DELAY_11, LOBYTE(usIVSDelay));
#endif    
}

//--------------------------------------------------
// Description  : Adjust Dclk offset
// Input Value  : Dclk offset
// Output Value : None
//--------------------------------------------------
void CAdjustDclkOffset(WORD usDclkOffset)
{
#if(_SCALER_TYPE == _RTD2547D)
    CScalerPageSelect(_PAGE1);
    CScalerSetBit(_P1_DCLK_FINE_TUNE_OFFSET_MSB_BC, 0xf0, HIBYTE(usDclkOffset) & 0x0f);
    CScalerSetByte(_P1_DCLK_FINE_TUNE_OFFSET_LSB_BD, LOBYTE(usDclkOffset));
    CScalerSetBit(_P1_DCLK_SPREAD_SPECTRUM_BE, ~_BIT2, _BIT2);
#else
    CScalerSetBit(_DCLK_FINE_TUNE_OFFSET_MSB_B5, 0xf0, HIBYTE(usDclkOffset) & 0x0f);
    CScalerSetByte(_DCLK_FINE_TUNE_OFFSET_LSB_B6, LOBYTE(usDclkOffset));
    CScalerSetBit(_SPREAD_SPECTRUM_B7, ~_BIT2, _BIT2);
#endif    
}

#if(_SCALER_TYPE == _RTD2547D)
//--------------------------------------------------
// Description  : Adjust Mclk offset
// Input Value  : Mclk offset
// Output Value : None
//--------------------------------------------------
void CAdjustMclkOffset(WORD usMclkOffset)
{
    CScalerPageSelect(_PAGE1);
    CScalerSetBit(_P1_MCLK_FINE_TUNE_OFFSET_MSB_CD, 0xf0, HIBYTE(usMclkOffset) & 0x0f);
    CScalerSetByte(_P1_MCLK_FINE_TUNE_OFFSET_LSB_CE, LOBYTE(usMclkOffset));
    CScalerSetBit(_P1_MCLK_SPREAD_SPECTRUM_CF, ~_BIT2, _BIT2);
}

//--------------------------------------------------
// Description  : Adjust DCLK spread spectrum range
// Input Value  : DPLL Spread spectrum range
// Output Value : None
//--------------------------------------------------
void CAdjustDclkSpreadSpectrumRange(BYTE ucSpreadRange)
{
    CScalerPageSelect(_PAGE1);
	if(GET_EMC_EN())
		{
	    CScalerSetBit(_P1_DCLK_SPREAD_SPECTRUM_BE, 0xff, 0xfF);
	    CScalerSetBit(_P1_DCLK_SPREAD_SPECTRUM_BE, ~_BIT2, _BIT2);
		}
	else
		{
	    CScalerSetBit(_P1_DCLK_SPREAD_SPECTRUM_BE, 0x0f, (ucSpreadRange << 4) & 0xf0);
	    CScalerSetBit(_P1_DCLK_SPREAD_SPECTRUM_BE, ~_BIT2, _BIT2);
		}
}

//--------------------------------------------------
// Description  : Adjust MCLK spread spectrum range
// Input Value  : MPLL Spread spectrum range
// Output Value : None
//--------------------------------------------------
void CAdjustMclkSpreadSpectrumRange(BYTE ucSpreadRange)
{
    CScalerPageSelect(_PAGE1);
    CScalerSetBit(_P1_MCLK_SPREAD_SPECTRUM_CF, 0x0f, (ucSpreadRange << 4) & 0xf0);
    CScalerSetBit(_P1_MCLK_SPREAD_SPECTRUM_CF, ~_BIT2, _BIT2);
}

#else

//--------------------------------------------------
// Description  : Adjust spread spectrum range
// Input Value  : Spread spectrum range
// Output Value : None
//--------------------------------------------------
void CAdjustSpreadSpectrumRange(BYTE ucSpreadRange)
{
	if(GET_EMC_EN())
		{
	    CScalerSetBit(_SPREAD_SPECTRUM_B7, ~_BIT2, _BIT2);
	    CScalerSetBit(_SPREAD_SPECTRUM_B7, 0xff, 0xff);
	    CScalerSetBit(_SPREAD_SPECTRUM_B7, ~_BIT2, _BIT2);
	    CScalerSetBit(_SPREAD_SPECTRUM_B7, 0xff, 0xff);
		}
	else
		{
	    CScalerSetBit(_SPREAD_SPECTRUM_B7, 0x0f, (ucSpreadRange << 4) & 0xf0);
	    CScalerSetBit(_SPREAD_SPECTRUM_B7, ~_BIT2, _BIT2);
		}
}
#endif // end #if(_SCALER_TYPE == _RTD2547D)
  

//--------------------------------------------------
// Description  : Sync processor measure start
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CAdjustSyncProcessorMeasureStart(void)
{
    CScalerSetBit(_MEAS_HS_PERIOD_H_52, ~_BIT5, _BIT5);
}

//--------------------------------------------------
// Description  : Turn on the error correction function
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CAdjustTMDSErrorCorrectionOn(void)
{
#if(_SCALER_TYPE == _RTD2547D)
    CScalerPageSelect(_PAGE2);
    CScalerSetBit(_P2_UP_DOWN_CTRL2_B7, ~(_BIT7 | _BIT6 | _BIT5), _BIT7);
#else
    CScalerSetBit(_UP_DOWN_CTRL3_D4, 0x3f, 0xc0);
#endif
}


#if(((_TMDS_SUPPORT == _ON) || (_HDMI_SUPPORT == _ON)) && (_DVI_LONG_CABLE_SUPPORT == _ON))
//--------------------------------------------------
// Description  : Measure TMDS transition result
// Input Value  : ucType    --> _TMDS_MEASURE_AVE, _TMDS_MEASURE_MAX, _TMDS_MEASURE_MIN
//                ucSelect  --> _TMDS_MEASURE_HSYNC_BE, _TMDS_MEASURE_HSYNC_AF, _TMDS_MEASURE_DE_BE, _TMDS_MEASURE_DE_AF
// Output Value : Transition result
//--------------------------------------------------
BYTE CAdjustTMDSMeasure(BYTE ucType, BYTE ucSelect)
{
    BYTE result;

#if(_SCALER_TYPE == _RTD2547D)
    CScalerPageSelect(_PAGE2);
    CScalerSetBit(_P2_TMDS_MEAS_RESULT0_A2, ~(_BIT6 | _BIT5), (ucType << 5));
    CScalerSetBit(_P2_TMDS_MEAS_RESULT0_A2, ~(_BIT7 | _BIT4 | _BIT3), (_BIT7 | (ucSelect << 3)));

    if(CTimerPollingEventProc(60, CMiscTMDSMeasureEvent) == _FALSE)
    {
        CScalerSetBit(_P2_TMDS_MEAS_RESULT0_A2, ~_BIT7, 0x00);
        return 0xff;
    }

    CScalerRead(_P2_TMDS_MEAS_RESULT1_A3, 1, &result, _NON_AUTOINC);
#else
    CScalerSetBit(_TMDS_MEAS_RESULT0_BD, ~(_BIT6 | _BIT5), (ucType << 5));
    CScalerSetBit(_TMDS_MEAS_RESULT0_BD, ~(_BIT7 | _BIT4 | _BIT3), (_BIT7 | (ucSelect << 3)));

    if(CTimerPollingEventProc(60, CMiscTMDSMeasureEvent) == _FALSE)
    {
        CScalerSetBit(_TMDS_MEAS_RESULT0_BD, ~_BIT7, 0x00);
        return 0xff;
    }

    CScalerRead(_TMDS_MEAS_RESULT1_BE, 1, &result, _NON_AUTOINC);
#endif

    return (result & 0x7f);
}

//--------------------------------------------------
// Description  : TMDS CRC check process before displaying
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CAdjustTMDSCRCCheck(void)
{
    BYTE temp0, temp1;
    DWORD dsod0, dsod1;

    if(GET_FRAMESYNCSTATUS())
    {
        CTimerDelayXms(20);

        temp0 = 0;
        temp0 += CAdjustTMDSCRC(&pData[8]);
        temp0 += CAdjustTMDSCRC(&pData[12]);
        dsod0 = abs(((DWORD *)pData)[2] - ((DWORD *)pData)[3]);

        if(temp0 < 2)
        {
#if(_SCALER_TYPE == _RTD2547D)
            CScalerPageSelect(_PAGE2);
            CScalerSetBit(_P2_ANALOG_COMMON_CTRL2_AB, ~(_BIT5 | _BIT6), CScalerGetBit(_P2_ANALOG_COMMON_CTRL2_AB, (_BIT6 | _BIT5)) ^ (_BIT5 | _BIT6));
#else
            CScalerSetBit(_ANALOG_COMMON_CTRL2_C6, ~(_BIT5 | _BIT6), CScalerGetBit(_ANALOG_COMMON_CTRL2_C6, (_BIT6 | _BIT5)) ^ (_BIT5 | _BIT6));
#endif

            temp1 = 0;
            temp1 += CAdjustTMDSCRC(&pData[8]);
            temp1 += CAdjustTMDSCRC(&pData[12]);
            dsod1 = abs(((DWORD *)pData)[2] - ((DWORD *)pData)[3]);

            if(temp1 < 2)
            {
                if(GET_USE_TRANSITION_RESULT())
                {
#if(_SCALER_TYPE == _RTD2547D)
                    CScalerSetBit(_P2_ANALOG_COMMON_CTRL2_AB, ~(_BIT5 | _BIT6), CScalerGetBit(_P2_ANALOG_COMMON_CTRL2_AB, (_BIT6 | _BIT5)) ^ (_BIT5 | _BIT6));
#else
                    CScalerSetBit(_ANALOG_COMMON_CTRL2_C6, ~(_BIT5 | _BIT6), CScalerGetBit(_ANALOG_COMMON_CTRL2_C6, (_BIT6 | _BIT5)) ^ (_BIT5 | _BIT6));
#endif
                }
                else
                {
                    if(dsod0 <= dsod1)
#if(_SCALER_TYPE == _RTD2547D)
                        CScalerSetBit(_P2_ANALOG_COMMON_CTRL2_AB, ~(_BIT5 | _BIT6), CScalerGetBit(_P2_ANALOG_COMMON_CTRL2_AB, (_BIT6 | _BIT5)) ^ (_BIT5 | _BIT6));
#else
                        CScalerSetBit(_ANALOG_COMMON_CTRL2_C6, ~(_BIT5 | _BIT6), CScalerGetBit(_ANALOG_COMMON_CTRL2_C6, (_BIT6 | _BIT5)) ^ (_BIT5 | _BIT6));
#endif
                }
            }
            else
            {
                //CModeSetDigitalCapture();
            }
        }
        else
        {
            //CModeSetDigitalCapture();
        }
    }
}

//--------------------------------------------------
// Description  : Get TMDS transition difference 
// Input Value  : ucPar     --> _MEASURE_HSYNC or _MEASURE_DE
// Output Value : Transition difference result
//--------------------------------------------------
BYTE CAdjustTMDSEqualizerCheck(BYTE ucPar)
{
    BYTE result0, result1;

    if(ucPar == _MEASURE_HSYNC)
    {
        result0 = CAdjustTMDSMeasure(_TMDS_MEASURE_MAX, _TMDS_MEASURE_HSYNC_BE);
        if(result0 == 0xff)     return 0xff;
        else if(result0 < 6)    return 0xfe;

        result1 = CAdjustTMDSMeasure(_TMDS_MEASURE_MIN, _TMDS_MEASURE_HSYNC_AF);
        if(result1 == 0xff)     return 0xff;
        else if(result1 < 6)    return 0xfe;
    }
    else if(ucPar == _MEASURE_DE)
    {
        result0 = CAdjustTMDSMeasure(_TMDS_MEASURE_MAX, _TMDS_MEASURE_DE_BE);
        if(result0 == 0xff)     return 0xff;
        else if(result0 < 6)    return 0xfe;

        result1 = CAdjustTMDSMeasure(_TMDS_MEASURE_MAX, _TMDS_MEASURE_DE_AF);
        if(result1 == 0xff)     return 0xff;
        else if(result1 < 6)    return 0xfe;
    }

    result0 = abs(result0 - result1);

    if(result0 <= 2)
        result0 = 0;

    return result0;
}

//--------------------------------------------------
// Description  : Adjust TMDS equalizer setting
// Input Value  : None
// Output Value : return _TRUE if success
//--------------------------------------------------
bit CAdjustTMDSEqualizer(void)
{
    BYTE cnt, result0, result1;

    CLR_USE_TRANSITION_RESULT();

#if(_SCALER_TYPE == _RTD2547D)
    CScalerPageSelect(_PAGE2);
    CScalerSetByte(_P2_TMDS_MEAS_SELECT_A1, 0x21);
    CScalerSetBit(_P2_TMDS_MEAS_RESULT0_A2, ~(_BIT6 | _BIT5), _BIT5);
#else
    CScalerSetByte(_TMDS_MEAS_SELECT_BC, 0x21);
    CScalerSetBit(_TMDS_MEAS_RESULT0_BD, 0x9f, 0x20);
#endif

    cnt = 1;
    do
    {
#if(_SCALER_TYPE == _RTD2547D)
        CScalerSetBit(_P2_TMDS_MEAS_SELECT_A1, 0xf0, (cnt%16));
#else
        CScalerSetBit(_TMDS_MEAS_SELECT_BC, 0xf0, (cnt%16));
#endif

        result0 = CAdjustTMDSMeasure(_TMDS_MEASURE_MAX, _TMDS_MEASURE_DE_BE);
        if(result0 == 0xff)
            return _FALSE;

        if(result0 > 80)
            break;

        cnt++;
    }
    while(cnt <= 16);

    cnt = 0;

#if(_SCALER_TYPE == _RTD2547D)
    CScalerPageSelect(_PAGE2);
    CScalerSetBit(_P2_ANALOG_COMMON_CTRL2_AB, ~(_BIT6 | _BIT5 | _BIT4), 0x00);
#else
    CScalerSetBit(_ANALOG_COMMON_CTRL2_C6, 0x8f, 0x00);
#endif
    result0 = CAdjustTMDSEqualizerCheck(_MEASURE_HSYNC);
    if(result0 == 0xff)     return _FALSE;
    if(result0 == 0xfe)     cnt += 1;

#if(_SCALER_TYPE == _RTD2547D)
    CScalerPageSelect(_PAGE2);
    CScalerSetBit(_P2_ANALOG_COMMON_CTRL2_AB, ~(_BIT6 | _BIT5 | _BIT4), _BIT4);
#else
    CScalerSetBit(_ANALOG_COMMON_CTRL2_C6, 0x8f, 0x10);
#endif
    result1 = CAdjustTMDSEqualizerCheck(_MEASURE_HSYNC);
    if(result1 == 0xff)     return _FALSE;
    if(result1 == 0xfe)     cnt += 2;

    if((abs(result0 - result1) <= 2) || (cnt != 0))
    {
        cnt = 0;

#if(_SCALER_TYPE == _RTD2547D)
        CScalerSetBit(_P2_ANALOG_COMMON_CTRL2_AB, ~(_BIT6 | _BIT5 | _BIT4), 0x00);
#else
        CScalerSetBit(_ANALOG_COMMON_CTRL2_C6, 0x8f, 0x00);
#endif
        result0 = CAdjustTMDSEqualizerCheck(_MEASURE_DE);
        if(result0 == 0xff)     return _FALSE;
        if(result0 == 0xfe)     cnt += 1;

#if(_SCALER_TYPE == _RTD2547D)
        CScalerSetBit(_P2_ANALOG_COMMON_CTRL2_AB, ~(_BIT6 | _BIT5 | _BIT4), _BIT4);
#else
        CScalerSetBit(_ANALOG_COMMON_CTRL2_C6, 0x8f, 0x10);
#endif
        result1 = CAdjustTMDSEqualizerCheck(_MEASURE_DE);
        if(result1 == 0xff)     return _FALSE;
        if(result1 == 0xfe)     cnt += 2;
    }

    if((result0 <= result1) || (cnt >= 2))
#if(_SCALER_TYPE == _RTD2547D)
        CScalerSetBit(_P2_ANALOG_COMMON_CTRL2_AB, ~(_BIT6 | _BIT5 | _BIT4), (_BIT6 | _BIT5 | _BIT4));
#else
        CScalerSetBit(_ANALOG_COMMON_CTRL2_C6, 0x8f, 0x70);
#endif

    if(abs(result0 - result1) > 2)
        SET_USE_TRANSITION_RESULT();

    return _TRUE;
}
#endif  // End of #if(((_TMDS_SUPPORT == _ON) || (_HDMI_SUPPORT == _ON)) && (_DVI_LONG_CABLE_SUPPORT == _ON))


#if((_TMDS_SUPPORT == _ON) || (_HDMI_SUPPORT == _ON))
//--------------------------------------------------
// Description  : Set digital mode capture
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CAdjustSetDigitalCapture(void)
{
#if(_SCALER_TYPE == _RTD2547D)
    CScalerSetBit(_VGIP_CTRL_10, ~_BIT1, _BIT1);
    CScalerSetBit(_IPH_ACT_STA_H_14, 0xf8, 0x00);
    CScalerSetByte(_IPH_ACT_STA_L_15, 0x00);
    CScalerSetByte(_IPV_ACT_STA_H_18, 0x00);
    CScalerSetByte(_IPV_ACT_STA_L_19, 0x00);
#else
    CScalerSetBit(_VGIP_CTRL_05, ~_BIT1, _BIT1);
    CScalerSetBit(_IPH_ACT_STA_H_09, 0xf8, 0x00);
    CScalerSetByte(_IPH_ACT_STA_L_0A, 0x00);
    CScalerSetByte(_IPV_ACT_STA_H_0D, 0x00);
    CScalerSetByte(_IPV_ACT_STA_L_0E, 0x00);
#endif
}

#if(((_TMDS_SUPPORT == _ON) || (_HDMI_SUPPORT == _ON)) && (_DVI_LONG_CABLE_SUPPORT == _ON))
//--------------------------------------------------
// Description  : Measure TMDS CRC value
// Input Value  : None
// Output Value : CRC value, DWORD data type
//--------------------------------------------------
DWORD CAdjustTMDSCRCMeasure(void)
{
    BYTE result[4];

    result[0] = 0;
#if(_SCALER_TYPE == _RTD2547D)
    CScalerPageSelect(_PAGE2);
    CScalerSetBit(_P2_TMDS_CTRL_A4, ~_BIT0, 0x00);
    CScalerSetBit(_P2_TMDS_CTRL_A4, ~_BIT0, _BIT0);
#else
    CScalerSetBit(_POWER_ON_OFF_CTRL_C2, ~_BIT0, 0x00);
    CScalerSetBit(_POWER_ON_OFF_CTRL_C2, ~_BIT0, _BIT0);
#endif

    if(CTimerPollingEventProc(60, CMiscTMDSCRCEvent) == _FALSE)
    {
#if(_SCALER_TYPE == _RTD2547D)
        CScalerSetBit(_P2_TMDS_CTRL_A4, ~_BIT0, 0x00);
#else
        CScalerSetBit(_POWER_ON_OFF_CTRL_C2, ~_BIT0, 0x00);
#endif
        return 0xffffffffl;
    }

    CTimerDelayXms(20);

#if(_SCALER_TYPE == _RTD2547D)
    CScalerRead(_P2_CRC_OUTPUT_BYTE_2_A5, 3, &result[1], _NON_AUTOINC);
#else
    CScalerRead(_CRC_OUTPUT_BYTE_2_C0, 3, &result[1], _NON_AUTOINC);
#endif

    return ((DWORD *)result)[0];
}

//--------------------------------------------------
// Description  : Do two times CRC check and get phase SOD value
// Input Value  : pArray    --> SOD value buffer
// Output Value : Return 0 if CRCs are not the same or CRCs == 0
//--------------------------------------------------
BYTE CAdjustTMDSCRC(BYTE *pArray)
{
    BYTE temp;

    CScalerSetByte(_AUTO_ADJ_CTRL1_7D, 0x3b);
    CScalerSetByte(_STATUS0_02, 0x00);

    ((DWORD *)pData)[0] = CAdjustTMDSCRCMeasure();
    ((DWORD *)pData)[1] = CAdjustTMDSCRCMeasure();

    CScalerRead(_STATUS0_02, 1, &temp, _NON_AUTOINC);
    CScalerRead(_AUTO_PHASE_3_84, 4, pArray, _AUTOINC);

    if((((DWORD *)pData)[0] != ((DWORD *)pData)[1]) || ((temp & 0x03) != 0) || (((DWORD *)pData)[0] == 0) || (((DWORD *)pData)[1] == 0))
        return 0;
    else
        return 1;
}
#endif

//--------------------------------------------------
// Description  : TMDS digital/analog capture check process before displaying
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CAdjustTMDSCaptureCheck(void)
{         /*
    BYTE temp0;
    WORD ihstartpos, ivstartpos;

    if(GET_FRAMESYNCSTATUS())
    {
        CScalerRead(_IPH_ACT_STA_H_09, 2, pData, _AUTOINC);
        ihstartpos = (((WORD)(pData[0] & 0x07)) << 8) | pData[1];
        CScalerRead(_IPV_ACT_STA_H_0D, 2, pData, _AUTOINC);
        ivstartpos = (((WORD)(pData[0] & 0x07)) << 8) | pData[1];

        CAdjustTMDSErrorCorrectionOff();
        CAdjustSetDigitalCapture();
        CTimerDelayXms(20);

        temp0 = 0;
        temp0 += CAdjustTMDSCRC(&pData[8]);
        temp0 += CAdjustTMDSCRC(&pData[12]);

        if(temp0 < 2)
        {
            CAdjustTMDSErrorCorrectionOn();
            CScalerSetBit(_VGIP_CTRL_05, ~_BIT1, 0x00);
            CScalerSetBit(_IPH_ACT_STA_H_09, 0xf8, (BYTE)(ihstartpos >> 8));
            CScalerSetByte(_IPH_ACT_STA_L_0A, (BYTE)ihstartpos);
            CScalerSetByte(_IPV_ACT_STA_H_0D, (BYTE)(ivstartpos >> 8));
            CScalerSetByte(_IPV_ACT_STA_L_0E, (BYTE)ivstartpos);
            CTimerDelayXms(20);
        }
    }  */

    if(GET_FRAMESYNCSTATUS())
    {
        CAdjustSetDigitalCapture();
        CTimerDelayXms(20);
    }
}
#endif  // End of #if((_TMDS_SUPPORT == _ON) || (_HDMI_SUPPORT == _ON))

#if(_HDCP_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Adjust HDCP key
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CAdjustHDCP(void)
{
#if(_SCALER_TYPE == _RTD2547D)
    CScalerPageSelect(_PAGE2);
    CScalerSetByte(_P2_HDCP_CTRL_C0, 0x06);
    CScalerCodeW(tHDCP_CTRL);
    CScalerWrite(_P2_DEVICE_KEY_ACCESS_PORT_C1, 320, tHDCP_KEY_TABLE_0, _NON_AUTOINC);
    CScalerSetByte(_P2_HDCP_CTRL_C0, 0x01);
#else
    CScalerSetByte(_HDCP_CTRL_D5, 0x06);
    CScalerCodeW(tHDCP_CTRL);
    CScalerWrite(_DEVICE_KEY_ACCESS_PORT_D6, 320, tHDCP_KEY_TABLE_0, _NON_AUTOINC);
    CScalerSetByte(_HDCP_CTRL_D5, 0x01);
#endif
}
#endif

//--------------------------------------------------
// Description  : Enable watch dog
// Input Value  : ucPar --> Parameter for watch dog
// Output Value : None
//--------------------------------------------------
void CAdjustEnableWatchDog(BYTE ucPar)
{
#if(_SCALER_TYPE == _RTD2547D)
    if(GET_FRAMESYNCSTATUS() ||  GET_FRCTATUS())
    {
        CScalerSetByte(_WATCH_DOG_CTRL0_0C, 0x00);
        CMiscClearStatusRegister();
        CScalerSetBit(_WATCH_DOG_CTRL0_0C, ~ucPar, 0x06 | ucPar);  //Ming-Yen
    }
#else
    if(GET_FRAMESYNCSTATUS())
    {
        CScalerSetByte(_WATCHDOG_CTRL1_DA, 0x00);
        CMiscClearStatusRegister();
        CScalerSetBit(_WATCHDOG_CTRL1_DA, ~ucPar, 0x06 | ucPar);
    }
#endif
}

//--------------------------------------------------
// Description  : Disable watch dog
// Input Value  : ucPar --> Parameter for watch dog
// Output Value : None
//--------------------------------------------------
void CAdjustDisableWatchDog(BYTE ucPar)
{
    BYTE temp;

#if(_SCALER_TYPE == _RTD2547D)
    CScalerSetBit(_WATCH_DOG_CTRL0_0C, ~ucPar, 0x00);

    temp = CScalerGetBit(_WATCH_DOG_CTRL0_0C, (_BIT5 | _BIT4 | _BIT3));

    if(temp == 0x00)
        CScalerSetByte(_WATCH_DOG_CTRL0_0C, 0x00);
#else
    CScalerSetBit(_WATCHDOG_CTRL1_DA, ~ucPar, 0x00);

    temp = CScalerGetBit(_WATCHDOG_CTRL1_DA, (_BIT5 | _BIT4 | _BIT3));

    if(temp == 0x00)
        CScalerSetByte(_WATCHDOG_CTRL1_DA, 0x00);
#endif
}

#if(_SCALER_TYPE == _RTD2547D && _HDMI_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Enable HDMI watch dog
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CAdjustEnableHDMIWatchDog(BYTE ucPar)
{
if((ucPar & _WD_SET_AVMUTE_ENABLE) == 0x01)
    CScalerSetDataPortBit(_P2_HDMI_ADDR_PORT_C9, _P2_HDMI_WDCR0_31, ~_BIT7, _BIT7); //Enable Set_AVMute Watch Dog

if((ucPar & _WD_AUDIO_FOR_TMDS_CLOCK) == 0x02)
    CScalerSetDataPortBit(_P2_HDMI_ADDR_PORT_C9, _P2_HDMI_WDCR1_32, ~_BIT7, _BIT7);//Enable Audio Watch Dog for TMDS clock

if((ucPar & _WD_PACKET_VARIATION) == 0x04)
    CScalerSetDataPortBit(_P2_HDMI_ADDR_PORT_C9, _P2_HDMI_VWDSR_41, ~_BIT0, _BIT0);//Enable packet variation Watch Dog
}

//--------------------------------------------------
// Description  : Disable HDMI watch dog
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CAdjustDisableHDMIWatchDog(BYTE ucPar)
{
if((ucPar & _WD_SET_AVMUTE_ENABLE) == 0x01)
    CScalerSetDataPortBit(_P2_HDMI_ADDR_PORT_C9, _P2_HDMI_WDCR0_31, ~_BIT7, 0x00); //Disable Set_AVMute Watch Dog

if((ucPar & _WD_AUDIO_FOR_TMDS_CLOCK) == 0x02)
    CScalerSetDataPortBit(_P2_HDMI_ADDR_PORT_C9, _P2_HDMI_WDCR1_32, ~_BIT7, 0x00);//Disable Audio Watch Dog for TMDS clock

if((ucPar & _WD_PACKET_VARIATION) == 0x04)
    CScalerSetDataPortBit(_P2_HDMI_ADDR_PORT_C9, _P2_HDMI_VWDSR_41, ~_BIT0, 0x00);//Disable packet variation Watch Dog
}
#endif  // end #if(_SCALER_TYPE == _RTD2547D)


//--------------------------------------------------
// Description  : Adjust sRGB function ( Not ready )
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CAdjustSRGB(void)
{

}

//--------------------------------------------------
// Description  : Adjust gamma
// Input Value  : Gamma table type and gamma tables
// Output Value : None
//--------------------------------------------------
void CAdjustGamma(BYTE ucGammaTableType, BYTE *pGammaTableArrayR, BYTE *pGammaTableArrayG, BYTE *pGammaTableArrayB)
{
    WORD cnt;
    BYTE i, temp;

    if((ucGammaTableType == _COMPACT_GAMMA_NORMAL_TABLE) || (ucGammaTableType == _FULL_GAMMA_NORMAL_TABLE))
    {
        CScalerSetByte(_GAMMA_CTRL_67, 0x80 | ucGammaTableType);
        CScalerWrite(_GAMMA_PORT_66, ((ucGammaTableType == _COMPACT_GAMMA_NORMAL_TABLE) ? 256 : 384), pGammaTableArrayR, _NON_AUTOINC);
        CScalerSetByte(_GAMMA_CTRL_67, 0x90 | ucGammaTableType);
        CScalerWrite(_GAMMA_PORT_66, ((ucGammaTableType == _COMPACT_GAMMA_NORMAL_TABLE) ? 256 : 384), pGammaTableArrayG, _NON_AUTOINC);
        CScalerSetByte(_GAMMA_CTRL_67, 0xa0 | ucGammaTableType);
        CScalerWrite(_GAMMA_PORT_66, ((ucGammaTableType == _COMPACT_GAMMA_NORMAL_TABLE) ? 256 : 384), pGammaTableArrayB, _NON_AUTOINC);
        CScalerSetByte(_GAMMA_CTRL_67, 0x40);
    }
    else if((ucGammaTableType == _COMPACT_GAMMA_COMPRESS_TABLE) || (ucGammaTableType == _FULL_GAMMA_COMPRESS_TABLE))
    {
        for(i=0;i<3;i++)
        {
            ucVLDCnt    = 0;
            ucVLDTemp   = 0;

            if(i == 0)
            {
                CScalerSetByte(_GAMMA_CTRL_67, 0x80 | (ucGammaTableType % 2));
                pvldarray   = (pGammaTableArrayR + 16);
            }
            else if(i == 1)
            {
                CScalerSetByte(_GAMMA_CTRL_67, 0x90 | (ucGammaTableType % 2));
                pvldarray   = (pGammaTableArrayG + 16);
            }
            else
            {
                CScalerSetByte(_GAMMA_CTRL_67, 0xa0 | (ucGammaTableType % 2));
                pvldarray   = (pGammaTableArrayB + 16);
            }

            for(temp=0;temp<16;temp++)
                pData[temp] = *(pvldarray + temp - 16);

            for(cnt=0;cnt<((ucGammaTableType == _COMPACT_GAMMA_COMPRESS_TABLE) ? 256 : 384);cnt++)
            {
                temp    = CScalerGetVLD() << 4;
                temp    |= CScalerGetVLD();
                CScalerSetByte(_GAMMA_PORT_66, temp);
            }
        }

        CScalerSetByte(_GAMMA_CTRL_67, 0x40);
    }
}

//--------------------------------------------------
// Description  : Set dithering
// Input Value  : Dithering tables
// Output Value : None
//--------------------------------------------------
void CAdjustDither(BYTE *pDitherSeqTable, BYTE * pDitherTable)
{
    CScalerSetBit(_DITHERING_CTRL_6B, ~(_BIT7 | _BIT6), _BIT7);
    CScalerWrite(_DITHERING_SEQUENCE_TABLE_69, 24, pDitherSeqTable, _NON_AUTOINC);
    CScalerSetBit(_DITHERING_CTRL_6B, ~(_BIT7 | _BIT6), _BIT6);
    CScalerWrite(_DITHERING_TABLE_ACCESS_PORT_6A, 24, pDitherTable, _NON_AUTOINC);
#if(_SCALER_TYPE == _RTD2547D)
    CScalerSetByte(_DITHERING_CTRL_6B, 0x28);
#else
    CScalerSetByte(_DITHERING_CTRL_6B, 0x38);
#endif
}

//--------------------------------------------------
// Description  : Adjust sharpness
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CAdjustSharpness(void)
{
    CAdjustSetSharpnessTable(tSU_COEF_TABLE[stSystemData.Sharpness & 0x0f], tSU_COEF_TABLE[stSystemData.Sharpness & 0x0f]);
}

//--------------------------------------------------
// Description  : Set Sharpness Table
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CAdjustSetSharpnessTable(BYTE code *pArray0, BYTE code *pArray1)
{
#if(_SCALER_TYPE == _RTD2547D)
    CScalerSetByte(_FILTER_CTRL_35, 0xb0);
    CScalerWrite(_FILTER_ACCESS_PORT_36, 128, pArray0, _NON_AUTOINC);
    CScalerSetByte(_FILTER_CTRL_35, 0xc0);
    CScalerWrite(_FILTER_ACCESS_PORT_36, 128, pArray1, _NON_AUTOINC);
    CScalerSetByte(_FILTER_CTRL_35, 0x00);
#else
    CScalerSetByte(_FILTER_CTRL_1C, 0xb0);
    CScalerWrite(_FILTER_PORT_1D, 128, pArray0, _NON_AUTOINC);
    CScalerSetByte(_FILTER_CTRL_1C, 0xc0);
    CScalerWrite(_FILTER_PORT_1D, 128, pArray1, _NON_AUTOINC);
    CScalerSetByte(_FILTER_CTRL_1C, 0x00);
#endif
}

//--------------------------------------------------
// Description  : Adjust color precessing brightness
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CAdjustBrightness(void)
{
    WORD iBright = (WORD)stConBriData.Brightness * 200 / 100+25;

    switch(_GET_INPUT_SOURCE())
    {
    case _SOURCE_VGA:
        pData[0] = pData[1] = pData[2] = ((iBright > 2)? (iBright - 2) : iBright);
        break;

    case _SOURCE_DVI:
    case _SOURCE_HDMI:
    case _SOURCE_VIDEO_AV:
    case _SOURCE_VIDEO_SV:
    case _SOURCE_VIDEO_DVD:   
   // case _SOURCE_VIDEO_YUV:
    case _SOURCE_VIDEO_TV: 
    case _SOURCE_YPBPR:    
    case _SOURCE_VIDEO_SCART:
        pData[0] = pData[1] = pData[2] = iBright;
        break;
    }

#if (_SCALER_TYPE == _RTD2553V || _SCALER_TYPE == _RTD2546N || _SCALER_TYPE == _RTD2525L || _SCALER_TYPE == _RTD2547D)
    CScalerSetByte(_CB_ACCESS_PORT_64, 0x80);
    CScalerWrite(_CB_DATA_PORT_65, 3, pData, _NON_AUTOINC);
    CScalerSetByte(_CB_ACCESS_PORT_64, 0x00);
#else
    CScalerWrite(_BRI_RED_COE_60, 3, pData, _AUTOINC);
#endif
}

//--------------------------------------------------
// Description  : Adjust color processing contrast
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CAdjustContrast(void)
{
    BYTE cnt;
    WORD iContrast = (WORD)stConBriData.Contrast +83;

    for(cnt=0;cnt<3;cnt++)
        pData[cnt] = (((WORD)stColorTempData.ColorTemp[cnt] * iContrast / 128) > 255) ? 255 : (BYTE)((WORD)stColorTempData.ColorTemp[cnt] * iContrast / 128);

#if (_SCALER_TYPE == _RTD2553V || _SCALER_TYPE == _RTD2546N || _SCALER_TYPE == _RTD2525L || _SCALER_TYPE == _RTD2547D)
    CScalerSetByte(_CB_ACCESS_PORT_64, 0x83);
    CScalerWrite(_CB_DATA_PORT_65, 3, pData, _NON_AUTOINC);
    CScalerSetByte(_CB_ACCESS_PORT_64, 0x00);
#else
    CScalerWrite(_CTS_RED_COE_63, 3, pData, _AUTOINC);
#endif
}

//--------------------------------------------------
// Description  : Adjust backlight
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CAdjustBacklight(void)
{
    BYTE ucLight = (WORD)(_BACKLIGHT_MAX - _BACKLIGHT_MIN) * stSystemData.BackLight/100;

#if(_BACKLIGHT_PWM_INVERSE == _ENABLE)

    ucLight = _BACKLIGHT_MAX - ucLight;

#else

    ucLight = _BACKLIGHT_MIN + ucLight;

#endif

    CSetPWM(_BACKLIGHT_PWM, ucLight);
}

//--------------------------------------------------
// Description  : Adjust ADC gain
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CAdjustAdcGain(void)
{
#if (_SCALER_TYPE == _RTD2553V || _SCALER_TYPE == _RTD2546N || _SCALER_TYPE == _RTD2525L || _SCALER_TYPE == _RTD2547D)

#if(_ADC_INPUT_SWAP_RG == _ON)

    pData[1] = stAdcData.AdcGain[_RED];
    pData[0] = stAdcData.AdcGain[_GREEN];
    pData[2] = stAdcData.AdcGain[_BLUE];

#elif(_ADC_INPUT_SWAP_RB == _ON)

    pData[2] = stAdcData.AdcGain[_RED];
    pData[1] = stAdcData.AdcGain[_GREEN];
    pData[0] = stAdcData.AdcGain[_BLUE];

#elif(_ADC_INPUT_SWAP_GB == _ON)

    pData[0] = stAdcData.AdcGain[_RED];
    pData[2] = stAdcData.AdcGain[_GREEN];
    pData[1] = stAdcData.AdcGain[_BLUE];

#else

    pData[0] = stAdcData.AdcGain[_RED];
    pData[1] = stAdcData.AdcGain[_GREEN];
    pData[2] = stAdcData.AdcGain[_BLUE];

#endif

  #if(_SCALER_TYPE == _RTD2547D)
    CScalerPageSelect(_PAGE0);
    CScalerWrite(_P0_RED_GAIN_A5, 3, pData, _AUTOINC);
  #else
    CScalerSetByte(_ADC_ACCESS_PORT_DC, 0x80);
    CScalerSetByte(_ADC_ACCESS_PORT_DC, 0x84);
    CScalerWrite(_ADC_DATA_PORT_DD, 3, pData, _NON_AUTOINC);
    CScalerSetByte(_ADC_ACCESS_PORT_DC, 0x00);
  #endif // end #if(_SCALER_TYPE == _RTD2547D)
#else

#if(_ADC_INPUT_SWAP_RG == _ON)

    CScalerSetByte(_GRN_GAIN_E1, stAdcData.AdcGain[_RED]);
    CScalerSetByte(_RED_GAIN_E0, stAdcData.AdcGain[_GREEN]);
    CScalerSetByte(_BLU_GAIN_E2, stAdcData.AdcGain[_BLUE]);

#elif(_ADC_INPUT_SWAP_RB == _ON)

    CScalerSetByte(_BLU_GAIN_E2, stAdcData.AdcGain[_RED]);
    CScalerSetByte(_GRN_GAIN_E1, stAdcData.AdcGain[_GREEN]);
    CScalerSetByte(_RED_GAIN_E0, stAdcData.AdcGain[_BLUE]);

#elif(_ADC_INPUT_SWAP_GB == _ON)

    CScalerSetByte(_RED_GAIN_E0, stAdcData.AdcGain[_RED]);
    CScalerSetByte(_BLU_GAIN_E2, stAdcData.AdcGain[_GREEN]);
    CScalerSetByte(_GRN_GAIN_E1, stAdcData.AdcGain[_BLUE]);

#else

    CScalerSetByte(_RED_GAIN_E0, stAdcData.AdcGain[_RED]);
    CScalerSetByte(_GRN_GAIN_E1, stAdcData.AdcGain[_GREEN]);
    CScalerSetByte(_BLU_GAIN_E2, stAdcData.AdcGain[_BLUE]);

#endif

#endif
}

//--------------------------------------------------
// Description  : Adjust ADC offset
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CAdjustAdcOffset(void)
{
#if (_SCALER_TYPE == _RTD2553V || _SCALER_TYPE == _RTD2546N || _SCALER_TYPE == _RTD2525L || _SCALER_TYPE == _RTD2547D)

#if(_ADC_INPUT_SWAP_RG == _ON)

    pData[4] = stAdcData.AdcOffset[_RED];
    pData[3] = stAdcData.AdcOffset[_GREEN];
    pData[5] = stAdcData.AdcOffset[_BLUE];

#elif(_ADC_INPUT_SWAP_RB == _ON)

    pData[5] = stAdcData.AdcOffset[_RED];
    pData[4] = stAdcData.AdcOffset[_GREEN];
    pData[3] = stAdcData.AdcOffset[_BLUE];

#elif(_ADC_INPUT_SWAP_GB == _ON)

    pData[3] = stAdcData.AdcOffset[_RED];
    pData[5] = stAdcData.AdcOffset[_GREEN];
    pData[4] = stAdcData.AdcOffset[_BLUE];

#else

    pData[3] = stAdcData.AdcOffset[_RED];
    pData[4] = stAdcData.AdcOffset[_GREEN];
    pData[5] = stAdcData.AdcOffset[_BLUE];

#endif

  #if(_SCALER_TYPE == _RTD2547D)
    CScalerPageSelect(_PAGE0);
    CScalerWrite(_P0_RED_OFFSET_A8, 3, &pData[3], _AUTOINC);
  #else
    CScalerSetByte(_ADC_ACCESS_PORT_DC, 0x80);
    CScalerSetByte(_ADC_ACCESS_PORT_DC, 0x87);
    CScalerWrite(_ADC_DATA_PORT_DD, 3, &pData[3], _NON_AUTOINC);
    CScalerSetByte(_ADC_ACCESS_PORT_DC, 0x00);
  #endif // end #if(_SCALER_TYPE == _RTD2547D)

#else

#if(_ADC_INPUT_SWAP_RG == _ON)

    CScalerSetByte(_GRN_OFFSET_E4, stAdcData.AdcOffset[_RED]);
    CScalerSetByte(_RED_OFFSET_E3, stAdcData.AdcOffset[_GREEN]);
    CScalerSetByte(_BLU_OFFSET_E5, stAdcData.AdcOffset[_BLUE]);

#elif(_ADC_INPUT_SWAP_RB == _ON)

    CScalerSetByte(_BLU_OFFSET_E5, stAdcData.AdcOffset[_RED]);
    CScalerSetByte(_GRN_OFFSET_E4, stAdcData.AdcOffset[_GREEN]);
    CScalerSetByte(_RED_OFFSET_E3, stAdcData.AdcOffset[_BLUE]);

#elif(_ADC_INPUT_SWAP_GB == _ON)

    CScalerSetByte(_RED_OFFSET_E3, stAdcData.AdcOffset[_RED]);
    CScalerSetByte(_BLU_OFFSET_E5, stAdcData.AdcOffset[_GREEN]);
    CScalerSetByte(_GRN_OFFSET_E4, stAdcData.AdcOffset[_BLUE]);

#else

    CScalerSetByte(_RED_OFFSET_E3, stAdcData.AdcOffset[_RED]);
    CScalerSetByte(_GRN_OFFSET_E4, stAdcData.AdcOffset[_GREEN]);
    CScalerSetByte(_BLU_OFFSET_E5, stAdcData.AdcOffset[_BLUE]);

#endif

#endif
}

//--------------------------------------------------
// Description  : Adjust ADC gain and offset
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CAdjustAdcGainOffset(void)
{
    CAdjustAdcGain();
    CAdjustAdcOffset();
}

//--------------------------------------------------
// Description  : Adjust background color
// Input Value  : Red, green and blue color settings
// Output Value : None
//--------------------------------------------------
void CAdjustBackgroundColor(BYTE ucRed, BYTE ucGreen, BYTE ucBlue)
{
    CScalerSetBit(_OVERLAY_CTRL_6C, ~_BIT5, 0x00);
    CScalerSetBit(_OVERLAY_CTRL_6C, ~_BIT5, _BIT5);

    CScalerSetByte(_BGND_COLOR_CTRL_6D, ucRed);
    CScalerSetByte(_BGND_COLOR_CTRL_6D, ucGreen);
    CScalerSetByte(_BGND_COLOR_CTRL_6D, ucBlue);

    CScalerSetBit(_OVERLAY_CTRL_6C, ~_BIT5, 0x00);
}

//--------------------------------------------------
// Description  : Apply color palette setting
// Input Value  : Color palette table
// Output Value : None
//--------------------------------------------------
void CAdjustColorPalette(BYTE *pColorPaletteArray)
{
    CScalerSetByte(_OVERLAY_LUT_ADDR_6E, 0x80);

    CScalerWrite(_COLOR_LUT_PORT_6F, 48, pColorPaletteArray, _NON_AUTOINC);

    CScalerSetByte(_OVERLAY_LUT_ADDR_6E, 0x00);
}

//--------------------------------------------------
// Description  : Calculate the suitable IVS to DVS delay
//                CR[38] : IVS to DVS delay in IHS lines
//                CR[1E] : IVS to DVS delay in ICLK * 16
// Input Value  : Scaling setting
// Output Value : IV to DV delay lines
//--------------------------------------------------
BYTE CAdjustIVS2DVSDelay(BYTE ucOption)
{
		// andy modify for panel
	    ((DWORD *)pData)[0] = ((DWORD)stDisplayInfo.DHTotal * Panel.DVStartPos) + CCalcPanelDHSta();
	    //((DWORD *)pData)[0] = ((DWORD)stDisplayInfo.DHTotal * stDisplayInfo.DVStartPos) + Panel.DHStartPos;
	    ((DWORD *)pData)[0] = ((DWORD *)pData)[0] * stModeInfo.IVHeight / stDisplayInfo.DVHeight * stModeInfo.IHTotal / stDisplayInfo.DHTotal;
	    ((DWORD *)pData)[1] = ((DWORD)stModeInfo.IHTotal * (stModeInfo.IVStartPos - (ucVStartBias + _PROGRAM_VDELAY))) + stModeInfo.IHStartPos - (ucHStartBias + _PROGRAM_HDELAY);

    if(ucOption & _BIT0)
    {
        // V scale-up. Target 2.50 IHS delay
        // Reg[40] = 0 ==> Delay 1 line
        ((DWORD *)pData)[1] += (stModeInfo.IHTotal * 1) + 640;

    }
    else
    {
        if (ucOption & _BIT1)
        {
            // V scale-down. Target 1.75 IHS delay
            ((DWORD *)pData)[1]  += stModeInfo.IHTotal + ((DWORD)640 * stModeInfo.IVHeight / stDisplayInfo.DVHeight);
        }
        else
        {
            // V no scaling. Target 1.50 IHS delay
            ((DWORD *)pData)[1]  += stModeInfo.IHTotal + 640;
        }

#if (_SCALER_TYPE == _RTD2553V || _SCALER_TYPE == _RTD2546N || _SCALER_TYPE == _RTD2525L)
        if(stModeInfo.IHWidth <= 1680) 
        {
            // Turn on full-line buffer
            ((DWORD *)pData)[1]  += stModeInfo.IHTotal;
            CScalerSetBit(_SCALE_CTRL_19, ~_BIT4, _BIT4);
        }
        else
        {
            ((DWORD *)pData)[1]  += 640;
        }
#else
        // Turn on full-line buffer
        ((DWORD *)pData)[1]  += stModeInfo.IHTotal;
  #if(_SCALER_TYPE == _RTD2547D)
        CScalerSetBit(_SCALE_CTRL_32, ~_BIT4, _BIT4);
  #else
        CScalerSetBit(_SCALE_CTRL_19, ~_BIT4, _BIT4);
  #endif
#endif
    }

    if (((DWORD *)pData)[0] > ((DWORD *)pData)[1])
    {
        // You should never get into this code ....
    }

    ((DWORD *)pData)[0]  = ((DWORD *)pData)[1] - ((DWORD *)pData)[0];

    pData[14] = ((DWORD *)pData)[0] / stModeInfo.IHTotal;
    pData[15] = (((DWORD *)pData)[0] - ((DWORD)stModeInfo.IHTotal * pData[14])) / 16;

    CScalerSetBit(_FS_DELAY_FINE_TUNING_43, ~_BIT1, 0x00);
    CScalerSetByte(_IVS2DVS_DELAY_LINES_40, pData[14]);
    CScalerSetByte(_IV_DV_DELAY_CLK_ODD_41, pData[15]);

    return pData[14];
}

#if(_SCALER_TYPE == _RTD2547D)
//--------------------------------------------------
// Description  : Set display clock (Dclk) frequency in kHz
// Input Value  : ulFreq    --> Target Dclk frequency
// Output Value : None
//--------------------------------------------------
void CAdjustPLL(bit ucSelection, DWORD ulFreq)
{
    WORD mcode;
    BYTE div;

    // We want to set DPLL offset to middle(2048), so the target DPLL M/N setting should be 16/15 of target frequency.
    mcode   = ulFreq * 8 * (ucSelection ? _MPLL_N_CODE : _DPLL_N_CODE) * 16 / ((DWORD)_RTD_XTAL * 15);

    if(mcode > 255)
    {
        div     = 1;                            // Output DPLL for DCLK
        mcode   = (mcode + 2) >> 2;             // Round to integer
    }
    else
    {
        div     = 2;                            // Output DPLL/2 for DCLK
        mcode   = (mcode + 1) >> 1;             // Round to integer
    }

    // Original Formula : M_Code/Ich = 36.67 must be constant
    // Ich   = M_Code * 100 / 3667
    // Ich   = 1u + D0[0]*1u + D0[1]*2u + D0[2]*4u + D0[3]*8u (A)

    // Calculate the Ich,
    pData[5]    = ((WORD)mcode * 100 / 3667) - 1;
    pData[6]    = 0x00;

    if(pData[5] >= 8)
    {
        pData[5]    -= 8;
        pData[6]    |= 0x08; //V307 modify
    }

    if(pData[5] >= 4)
    {
        pData[5]    -= 4;
        pData[6]    |= 0x04;
    }

    if(pData[5] >= 2)
    {
        pData[5]    -= 2;
        pData[6]    |= 0x02;
    }

    if(pData[5] >= 1)
    {
        pData[5]    -= 1;
        pData[6]    |= 0x01;
    }
    
    pData[0]    = mcode - 2;
#if(_M2PLL_USE == _ON)
    pData[1]    = ((1 == div) ? 0x00 : 0x10) | (((ucSelection ? _MPLL_N_CODE : _DPLL_N_CODE) / _RTD_M2PLL_RATIO) - 2);
#else
    pData[1]    = ((1 == div) ? 0x00 : 0x10) | ((ucSelection ? _MPLL_N_CODE : _DPLL_N_CODE) - 2);
#endif
    pData[2]    = 0x80 | pData[6];
    pData[3]    = 0x17;

    CScalerPageSelect(_PAGE1);
    CScalerWrite((ucSelection ? _P1_MPLL_M_C8 : _P1_DPLL_M_B7), 4, pData, _AUTOINC);

    //V306 modify
    CScalerSetBit((ucSelection ? _P1_MPLL_MISC_CC : _P1_DPLL_OTHER_BB), ~_BIT1, _BIT1);
    if((bit)CScalerGetBit((ucSelection ? _P1_MPLL_N_C9 : _P1_DPLL_N_B8), _BIT7))
    {
        CScalerSetBit((ucSelection ? _P1_MPLL_N_C9 : _P1_DPLL_N_B8), ~_BIT6, _BIT6);
        CTimerDelayXms(2);
        CScalerSetBit((ucSelection ? _P1_MPLL_N_C9 : _P1_DPLL_N_B8), ~_BIT6, 0x00);
    } //V306 modify

    // Dclk frequency in Hz
    ((DWORD *)pData)[0] = (DWORD)_RTD_XTAL * 1000 / (div * 2) * mcode / (ucSelection ? _MPLL_N_CODE : _DPLL_N_CODE);

    // Offset resolution (Dclk / 2^15) in Hz
    ((DWORD *)pData)[1] = ((DWORD *)pData)[0] >> 15;

    // Target frequency of Dclk in Hz
    mcode       = (((DWORD *)pData)[0] - (ulFreq * 1000)) / ((DWORD *)pData)[1];
    mcode       = mcode & 0x0fff;

    if(ucSelection == _DPLL)
        //Enable DDS spread spectrum output function
        CScalerSetBit(_P1_FIXED_LAST_LINE_CTRL_C2, ~_BIT0, _BIT0);

    if(ucSelection == _DPLL)
        CAdjustDclkOffset(mcode);
    else
        CAdjustMclkOffset(mcode);
}

#elif(_SCALER_TYPE == _RTD2533B)

//--------------------------------------------------
// Description  : Set display clock (Dclk) frequency in kHz
// Input Value  : ulFreq    --> Target Dclk frequency
// Output Value : None
//--------------------------------------------------
void CAdjustDPLL(DWORD ulFreq)
{
    WORD mcode;
    BYTE div;

    // We want to set DPLL offset to middle(2048), so the target DPLL M/N setting should be 16/15 of target frequency.
    mcode   = ulFreq * 8 * _DPLL_N_CODE * 16 / ((DWORD)_RTD_XTAL * 15);

    if(mcode > 255)
    {
        div     = 1;                            // Output DPLL for DCLK
        mcode   = (mcode + 2) >> 2;             // Round to integer
    }
    else
    {
        div     = 2;                            // Output DPLL/2 for DCLK
        mcode   = (mcode + 1) >> 1;             // Round to integer
    }

    // Original Formula : M_Code/Ich = 17.6 must be constant
    // Ich   = M_Code * 10 / 176
    // 2*Ich = M_Code * 20 / 176 , set D0[5] to 0, then I = 2 * Ich
    // I     = 2 * Ich = 2.5u + D0[0]*2.5u + D0[1]*5u + D0[2]*10u + D0[3]*20u + D0[4]*30u (A)
    // 2*I   = 4 * Ich = 5u + D0[0]*5u + D0[1]*10u + D0[2]*20u + D0[3]*40u + D0[4]*60u (A)

    // Calculate the 4 * Ich,
    pData[5]    = ((WORD)mcode * 4 * 10 / 176) - 5;
    pData[6]    = 0x00;
    
    if(pData[5] >= 60)
    {
        pData[5]    -= 60;
        pData[6]    |= 0x10;
    }

    if(pData[5] >= 40)
    {
        pData[5]    -= 40;
        pData[6]    |= 0x08;
    }

    if(pData[5] >= 20)
    {
        pData[5]    -= 20;
        pData[6]    |= 0x04;
    }

    if(pData[5] >= 10)
    {
        pData[5]    -= 10;
        pData[6]    |= 0x02;
    }

    if(pData[5] >= 5)
    {
        pData[5]    -= 5;
        pData[6]    |= 0x01;
    }

    pData[0]    = mcode - 2;
#if(_M2PLL_USE == _ON)
    pData[1]    = ((1 == div) ? 0x00 : 0x10) | ((_DPLL_N_CODE / _RTD_M2PLL_RATIO) - 2);
#else
    pData[1]    = ((1 == div) ? 0x00 : 0x10) | (_DPLL_N_CODE - 2);
#endif
    pData[2]    = 0x40 | pData[6];
    pData[3]    = 0x0f;
    CScalerWrite(_DPLL_M_AE, 4, pData, _AUTOINC);

    // Dclk frequency in Hz
    ((DWORD *)pData)[0] = (DWORD)_RTD_XTAL * 1000 / (div * 2) * mcode / _DPLL_N_CODE;

    // Offset resolution (Dclk / 2^15) in Hz
    ((DWORD *)pData)[1] = ((DWORD *)pData)[0] >> 15;

    // Target frequency of Dclk in Hz
    mcode       = (((DWORD *)pData)[0] - (ulFreq * 1000)) / ((DWORD *)pData)[1];
    mcode       = mcode & 0x0fff;

    //Enable DDS spread spectrum output function
    CScalerSetBit(_FIXED_LAST_LINE_CTRL_BB, ~_BIT0, _BIT0);

    CAdjustDclkOffset(mcode);
}

#elif((_SCALER_TYPE == _RTD2023L) || (_SCALER_TYPE == _RTD2023S) || (_SCALER_TYPE == _RTD2023L_VB) || (_SCALER_TYPE == _RTD2023S_VB))

//--------------------------------------------------
// Description  : Set display clock (Dclk) frequency in kHz
// Input Value  : ulFreq    --> Target Dclk frequency
// Output Value : None
//--------------------------------------------------
void CAdjustDPLL(DWORD ulFreq)
{
    WORD mcode;
    BYTE div;

    // We want to set DPLL offset to middle(2048), so the target DPLL M/N setting should be 16/15 of target frequency.
    mcode   = ulFreq * 8 * _DPLL_N_CODE * 16 / ((DWORD)_RTD_XTAL * 15);

    if(mcode > 255)
    {
        div     = 1;                            // Output DPLL for DCLK
        mcode   = (mcode + 2) >> 2;             // Round to integer
    }
    else
    {
        div     = 2;                            // Output DPLL/2 for DCLK
        mcode   = (mcode + 1) >> 1;             // Round to integer
    }

    // Original Formula : M_Code/Ich = 17.6 must be constant
    // Ich   = M_Code * 10 / 176
    // Ich   = 1u + D0[0]*1u + D0[1]*2u + D0[2]*4u + D0[3]*8u (A)

    // Calculate the 4 * Ich,
    pData[5]    = ((WORD)mcode * 10 / 344) - 1; //V305 modify
    pData[6]    = 0x00;
    
    if(pData[5] >= 8)
    {
        pData[5]    -= 8;
        pData[6]    |= 0x08; //V307 modify
    }

    if(pData[5] >= 4)
    {
        pData[5]    -= 4;
        pData[6]    |= 0x04;
    }

    if(pData[5] >= 2)
    {
        pData[5]    -= 2;
        pData[6]    |= 0x02;
    }

    if(pData[5] >= 1)
    {
        pData[5]    -= 1;
        pData[6]    |= 0x01;
    }

    pData[0]    = mcode - 2;
#if(_M2PLL_USE == _ON)
    pData[1]    = ((1 == div) ? 0x00 : 0x10) | ((_DPLL_N_CODE / _RTD_M2PLL_RATIO) - 2);
#else
    pData[1]    = ((1 == div) ? 0x00 : 0x10) | (_DPLL_N_CODE - 2);
#endif
    pData[2]    = 0x80 | pData[6];  //V306 modify
    pData[3]    = 0x17; //V306 modify
    CScalerWrite(_DPLL_M_AE, 4, pData, _AUTOINC);

    //V306 modify
    CScalerSetBit(_PLL_OTHER_B4, ~_BIT1, _BIT1);
    if((bit)CScalerGetBit(_DPLL_WD_B1, _BIT7))
    {
        CScalerSetBit(_DPLL_WD_B1, ~_BIT6, _BIT6);
        CTimerDelayXms(2);
        CScalerSetBit(_DPLL_WD_B1, ~_BIT6, 0);
    } //V306 modify

    // Dclk frequency in Hz
    ((DWORD *)pData)[0] = (DWORD)_RTD_XTAL * 1000 / (div * 2) * mcode / _DPLL_N_CODE;

    // Offset resolution (Dclk / 2^15) in Hz
    ((DWORD *)pData)[1] = ((DWORD *)pData)[0] >> 15;

    // Target frequency of Dclk in Hz
    mcode       = (((DWORD *)pData)[0] - (ulFreq * 1000)) / ((DWORD *)pData)[1];
    mcode       = mcode & 0x0fff;

    //Enable DDS spread spectrum output function
    CScalerSetBit(_FIXED_LAST_LINE_CTRL_BB, ~_BIT0, _BIT0);

    CAdjustDclkOffset(mcode);
}

#elif (_SCALER_TYPE == _RTD2553V || _SCALER_TYPE == _RTD2546N || _SCALER_TYPE == _RTD2525L)

//--------------------------------------------------
// Description  : Set display clock (Dclk) frequency in kHz
// Input Value  : ulFreq    --> Target Dclk frequency
// Output Value : None
//--------------------------------------------------
void CAdjustDPLL(DWORD ulFreq)
{
    WORD mcode;
    BYTE div;

    // We want to set DPLL offset to middle(2048), so the target DPLL M/N setting should be 16/15 of target frequency.
    mcode   = ulFreq * 8 * _DPLL_N_CODE * 16 / ((DWORD)_RTD_XTAL * 15);

    if(mcode > 255)
    {
        div     = 1;                            // Output DPLL for DCLK
        mcode   = (mcode + 2) >> 2;             // Round to integer
    }
    else
    {
        div     = 2;                            // Output DPLL/2 for DCLK
        mcode   = (mcode + 1) >> 1;             // Round to integer
    }

    // Original Formula : M_Code/Ich = 36.67 must be constant
    // Ich   = M_Code * 100 / 3667
    // Ich   = 1u + D0[0]*1u + D0[1]*2u + D0[2]*4u + D0[3]*8u (A)

    // Calculate the Ich,
    pData[5]    = ((WORD)mcode * 100 / 3667) - 1;
    pData[6]    = 0x00;

    if(pData[5] >= 8)
    {
        pData[5]    -= 8;
        pData[6]    |= 0x80;
    }

    if(pData[5] >= 4)
    {
        pData[5]    -= 4;
        pData[6]    |= 0x04;
    }

    if(pData[5] >= 2)
    {
        pData[5]    -= 2;
        pData[6]    |= 0x02;
    }

    if(pData[5] >= 1)
    {
        pData[5]    -= 1;
        pData[6]    |= 0x01;
    }
    
    pData[0]    = mcode - 2;
#if(_M2PLL_USE == _ON)
    pData[1]    = ((1 == div) ? 0x00 : 0x10) | ((_DPLL_N_CODE / _RTD_M2PLL_RATIO) - 2);
#else
    pData[1]    = ((1 == div) ? 0x00 : 0x10) | (_DPLL_N_CODE - 2);
#endif
    pData[2]    = 0x80 | pData[6];
    pData[3]    = 0x17;
    CScalerWrite(_DPLL_M_AE, 4, pData, _AUTOINC);

    //V306 modify
    CScalerSetBit(_DPLL_OTHER_B2, ~_BIT1, _BIT1);
    if((bit)CScalerGetBit(_DPLL_WD_B1, _BIT7))
    {
        CScalerSetBit(_DPLL_WD_B1, ~_BIT6, _BIT6);
        CTimerDelayXms(2);
        CScalerSetBit(_DPLL_WD_B1, ~_BIT6, 0);
    } //V306 modify


    // Dclk frequency in Hz
    ((DWORD *)pData)[0] = (DWORD)_RTD_XTAL * 1000 / (div * 2) * mcode / _DPLL_N_CODE;

    // Offset resolution (Dclk / 2^15) in Hz
    ((DWORD *)pData)[1] = ((DWORD *)pData)[0] >> 15;

    // Target frequency of Dclk in Hz
    mcode       = (((DWORD *)pData)[0] - (ulFreq * 1000)) / ((DWORD *)pData)[1];
    mcode       = mcode & 0x0fff;

    //Enable DDS spread spectrum output function
    CScalerSetBit(_FIXED_LAST_LINE_CTRL_BB, ~_BIT0, _BIT0);

    CAdjustDclkOffset(mcode);
}


#endif

//--------------------------------------------------
// Description  : 
// Input Value  : 
// Output Value : 
//--------------------------------------------------
void CAdjustUpdateCenterData(void)
{
    WORD delta;

    stModeUserCenterData.CenterHPos     = stModeUserData.HPosition;
    stModeUserCenterData.CenterVPos     = stModeUserData.VPosition;

    CAdjustCheckAdcClockRange(stModeUserData.Clock, &delta);

    if(delta < _CLOCK_BIAS)
    {
        stModeUserCenterData.CenterClock = stModeInfo.IHTotal;
    }
    else
    {
        if(stModeUserData.Clock < stModeInfo.IHTotal)
        {
            if((stModeUserData.Clock - stModeInfo.IHTotal + delta) < _CLOCK_BIAS)
            {
                stModeUserCenterData.CenterClock = stModeInfo.IHTotal - delta + _CLOCK_BIAS;
            }
            else
            {
                stModeUserCenterData.CenterClock = stModeUserData.Clock;
            }
        }
        else
        {
            if((stModeInfo.IHTotal + delta - stModeUserData.Clock) < _CLOCK_BIAS)
            {
                stModeUserCenterData.CenterClock = stModeInfo.IHTotal + delta - _CLOCK_BIAS;
            }
            else
            {
                stModeUserCenterData.CenterClock = stModeUserData.Clock;
            }
        }
    }
}

//--------------------------------------------------
// Description  : Check if the ADC clock (IHTotal) is out of range. Range = (BackPorch + FrontPorch) * 2 / 5 .
// Input Value  : usClock   --> ADC Clock (IHTotal)
// Output Value : Return _TRUE if not out of range
//--------------------------------------------------
bit CAdjustCheckAdcClockRange(WORD usClock, WORD *delta)
{
    *delta   = (stModeInfo.IHTotal - stModeInfo.IHWidth * 8 / 10) / 2;

    if((usClock > stModeInfo.IHTotal) && ((usClock - stModeInfo.IHTotal) > *delta))
        return _FALSE;

    if((usClock <= stModeInfo.IHTotal) && ((stModeInfo.IHTotal - usClock) > *delta))
        return _FALSE;

    return _TRUE;
}

//--------------------------------------------------
// Description  : Set ADC clock (IHTotal)
// Input Value  : usClock   --> Target ADC clock
// Output Value : None
//--------------------------------------------------
void CAdjustAdcClock(WORD usClock)
{
    BYTE mcode, ncode, temp0, temp1;
    WORD delta;

    CAdjustEnableWatchDog(_WD_DV_TIMEOUT);

    if(!CAdjustCheckAdcClockRange(usClock, &delta))
        usClock = stModeInfo.IHTotal;

#if(_SCALER_TYPE == _RTD2547D)
    CScalerPageSelect(_PAGE1);
#endif

#if (_SCALER_TYPE == _RTD2553V || _SCALER_TYPE == _RTD2546N || _SCALER_TYPE == _RTD2525L || _SCALER_TYPE == _RTD2547D)
    pData[0]    = 0x04; //Select phase 32 for RTD2553V
#else
    pData[0]    = 0x0c;
#endif
    pData[1]    = 0x4f;
    pData[2]    = 0x24;
    pData[3]    = 0x00 | _DDS_P_CODE;
#if(_SCALER_TYPE == _RTD2547D)
    CScalerWrite(_P1_PLL_DIV_CTRL_A1, 4, pData, _AUTOINC);
#else
    CScalerWrite(_PLL_DIV_CTRL_98, 4, pData, _AUTOINC);
#endif

#if(_M2PLL_USE == _ON)
    pData[0]    = ((_APLL1_M_CODE * _RTD_M2PLL_RATIO) - 2);
#else
    pData[0]    = (_APLL1_M_CODE - 2);
#endif
    pData[1]    = (_APLL1_N_CODE - 2);
    pData[2]    = 0x37;
#if(_SCALER_TYPE == _RTD2547D)
    CScalerWrite(_P1_PLL1_M_AA, 3, pData, _AUTOINC);
#else
    CScalerWrite(_PLL1_M_A1, 3, pData, _AUTOINC);
#endif

    // usClock * 2 -------------------------------------
    if(((DWORD)stModeInfo.IHFreq * stModeInfo.IHTotal / 1000) < 530)
    {
        usClock = usClock * 2 * 2;
    }
    else
    {
        usClock = usClock * 2;
    }
    //--------------------------------------------------

    ((WORD *)pData)[2]  = 100;

    temp1   = 11;

    do
    {
        temp0   = ((DWORD)31 * _APLL1_N_CODE * temp1 * usClock)
                  / ((DWORD)32 * _APLL1_M_CODE * stModeInfo.IHCount);

        ((WORD *)pData)[0] = ((DWORD)3100 * _APLL1_N_CODE * temp1 * usClock)
                             / ((DWORD)_APLL1_M_CODE * temp0 * stModeInfo.IHCount);

        if(((WORD *)pData)[0] > 3240)
        {
            ((WORD *)pData)[0] = ((WORD *)pData)[0] - 3200;

            if(((WORD *)pData)[0] <= ((WORD *)pData)[2])
            {
                ((WORD *)pData)[2] = ((WORD *)pData)[0];
 
                mcode   = temp0;
                ncode   = temp1;
            }

            ((WORD *)pData)[1]  = ((DWORD)3100 * _APLL1_N_CODE * temp1 * usClock)
                                  / ((DWORD)_APLL1_M_CODE * (temp0 + 1) * stModeInfo.IHCount);
            ((WORD *)pData)[1]  = 3200 > ((WORD *)pData)[1] ? 3200 - ((WORD *)pData)[1] : ((WORD *)pData)[1] - 3200;
            
            if(((WORD *)pData)[1] < 40)
            {
                mcode   = temp0 + 1;
                ncode   = temp1;
                break;
            }

            if(((WORD *)pData)[1] <= ((WORD *)pData)[2])
            {
                ((WORD *)pData)[2] = ((WORD *)pData)[1];

                mcode   = temp0 + 1;
                ncode   = temp1;
            }
        }
        else
        {
            mcode   = temp0;
            ncode   = temp1;
            break;
        }
    }
    while(++temp1 < 48);

    if(((DWORD)stModeInfo.IHFreq * stModeInfo.IHTotal / 1000) < 530)
    {
        usClock     = (usClock / 2 / 2);
    }
    else
    {
        usClock     = (usClock / 2);
    }

#if(_APLL_FAST_LOCK)

    if(GET_FIRST_ADCCLOCK())
    {
#if(_SCALER_TYPE == _RTD2547D)
        CScalerPageSelect(_PAGE1);
        CScalerRead(_P1_PLL2_M_AE, 2, &pData[14], _AUTOINC);
        pData[14] = pData[14] + 2;      // Old M code
        pData[15] = pData[15] + 2;      // Old N code

        CScalerRead(_P1_PLLDIV_H_B2, 2, &pData[12], _AUTOINC);
        ((WORD *)pData)[6] = ((((WORD)(pData[12] & 0x0f)) << 8) | pData[13]) + 1;
        
        CScalerSetByte(_P1_FAST_PLL_CTRL_A8, 0x00);
        CScalerSetByte(_P1_FAST_PLL_CTRL_A8, 0x07);
        CScalerRead(_P1_FAST_PLL_ISUM_A9, 4, pData, _NON_AUTOINC);
#else
        CScalerRead(_PLL2_M_A5, 2, &pData[14], _AUTOINC);
        pData[14] = pData[14] + 2;      // Old M code
        pData[15] = pData[15] + 2;      // Old N code

        CScalerRead(_PLLDIV_H_A9, 2, &pData[12], _AUTOINC);
        ((WORD *)pData)[6] = ((((WORD)(pData[12] & 0x0f)) << 8) | pData[13]) + 1;

        CScalerSetByte(_FAST_PLL_CTRL_9F, 0x00);
        CScalerSetByte(_FAST_PLL_CTRL_9F, 0x07);
        CScalerRead(_FAST_PLL_ISUM_A0, 4, pData, _NON_AUTOINC);
#endif

        ((DWORD *)pData)[1] = (DWORD)pData[15] * mcode * (DWORD)((WORD *)pData)[6]; // H Up
        ((DWORD *)pData)[2] = (DWORD)ncode * pData[14] * usClock;   // H Down
        ((DWORD *)pData)[0] = ((DWORD *)pData)[0] / ((DWORD *)pData)[2] * ((DWORD *)pData)[1];

        if(((DWORD *)pData)[2] > ((DWORD *)pData)[1])
            ((DWORD *)pData)[0] += (DWORD)4294967295 / ((DWORD *)pData)[2] * 16 * (((DWORD *)pData)[2] - ((DWORD *)pData)[1]);
        else
            ((DWORD *)pData)[0] -= (DWORD)4294967295 / ((DWORD *)pData)[2] * 16 * (((DWORD *)pData)[1] - ((DWORD *)pData)[2]);

#if(_SCALER_TYPE == _RTD2547D)
        CScalerSetByte(_P1_FAST_PLL_CTRL_A8, 0x20);
        CScalerSetByte(_P1_FAST_PLL_CTRL_A8, 0x22);
        CScalerWrite(_P1_FAST_PLL_ISUM_A9, 4, pData, _NON_AUTOINC);
#else
        CScalerSetByte(_FAST_PLL_CTRL_9F, 0x20);
        CScalerSetByte(_FAST_PLL_CTRL_9F, 0x22);
        CScalerWrite(_FAST_PLL_ISUM_A0, 4, pData, _NON_AUTOINC);
#endif
    }

#endif

#if(_SCALER_TYPE == _RTD2547D)
    CScalerPageSelect(_PAGE1);
    if(((DWORD)stModeInfo.IHFreq * stModeInfo.IHTotal / 1000) < 530)
    {
        CScalerSetBit(_P1_PLLDIV_H_B2, 0xe0, 0x10 | (HIBYTE(usClock - 1) & 0x0f));
    }
    else
    {
        CScalerSetBit(_P1_PLLDIV_H_B2, 0xe0, 0x00 | HIBYTE(usClock - 1) & 0x0f);
    }

    CScalerSetByte(_P1_PLLDIV_L_B3, LOBYTE(usClock - 1));
    CScalerSetByte(_P1_PLL2_M_AE, mcode - 2);
    CScalerSetByte(_P1_PLL2_N_AF, ncode - 2);
#else
    if(((DWORD)stModeInfo.IHFreq * stModeInfo.IHTotal / 1000) < 530)
    {
        CScalerSetBit(_PLLDIV_H_A9, 0xe0, 0x10 | (HIBYTE(usClock - 1) & 0x0f));
    }
    else
    {
        CScalerSetBit(_PLLDIV_H_A9, 0xe0, 0x00 | HIBYTE(usClock - 1) & 0x0f);
    }

    CScalerSetByte(_PLLDIV_L_AA, LOBYTE(usClock - 1));
    CScalerSetByte(_PLL2_M_A5, mcode - 2);
    CScalerSetByte(_PLL2_N_A6, ncode - 2);
#endif

    // Original Formula : Icp/M2_Code = 0.4 must be constant
    // Icp   = M2_Code * 4 / 10
    // Icp   = 2.5u + A7[0]*2.5u + A7[1]*5u + A7[2]*10u + A7[3]*20u + A7[4]*30u (A)
    // 2*Icp = 5u + A7[0]*5u + A7[1]*10u + A7[2]*20u + A7[3]*40u + A7[4]*60u (A)

    // Calculate the 2*Icp,
    pData[5]    = (((WORD)mcode * 4 / 10) < 5) ? 0 : ((WORD)mcode * 4 / 10) - 5;
    pData[6]    = 0x00;
    
    if(pData[5] >= 60)
    {
        pData[5]    -= 60;
        pData[6]    |= 0x10;
    }

    if(pData[5] >= 40)
    {
        pData[5]    -= 40;
        pData[6]    |= 0x08;
    }

    if(pData[5] >= 20)
    {
        pData[5]    -= 20;
        pData[6]    |= 0x04;
    }

    if(pData[5] >= 10)
    {
        pData[5]    -= 10;
        pData[6]    |= 0x02;
    }

    if(pData[5] >= 5)
    {
        pData[5]    -= 5;
        pData[6]    |= 0x01;
    }

    // Larger charge pump current (+2)
    pData[6] += 2;
#if(_SCALER_TYPE == _RTD2547D)
    CScalerSetBit(_P1_PLL2_CRNT_B0, 0xe0, pData[6]);
#else
    CScalerSetBit(_PLL2_CRNT_A7, 0xe0, pData[6]);
#endif

    if(GET_FIRST_ADCCLOCK())
    {

    }
    else
    {
        CPowerADCAPLLOn();
#if(_SCALER_TYPE == _RTD2547D)
        CScalerPageSelect(_PAGE1);
        CScalerSetByte(_P1_I_CODE_M_A3, 0x20);
#else
        CScalerSetByte(_I_CODE_M_9A, 0x20);
#endif
        CTimerWaitForEvent(_EVENT_IVS);
        CTimerWaitForEvent(_EVENT_IVS);
#if(_SCALER_TYPE == _RTD2547D)
        CScalerSetByte(_P1_I_CODE_M_A3, 0x24);
#else
        CScalerSetByte(_I_CODE_M_9A, 0x24);
#endif
        SET_FIRST_ADCCLOCK();
    }

#if(_APLL_FAST_LOCK)

    if(GET_FIRST_ADCCLOCK())
    {
#if(_SCALER_TYPE == _RTD2547D)
        CScalerPageSelect(_PAGE1);
        CScalerSetByte(_P1_FAST_PLL_CTRL_A8, 0x68);
#else
        CScalerSetByte(_FAST_PLL_CTRL_9F, 0x68);
#endif
    }

#endif

    CTimerWaitForEvent(_EVENT_IEN_STOP);
    CTimerWaitForEvent(_EVENT_IEN_STOP);
#if(_SCALER_TYPE == _RTD2547D)
    CScalerPageSelect(_PAGE1);
    CScalerSetByte(_P1_FAST_PLL_CTRL_A8, 0x00);
#else
    CScalerSetByte(_FAST_PLL_CTRL_9F, 0x00);
#endif

    CMiscClearStatusRegister();

    CAdjustEnableWatchDog(_WD_ALL);
}

//--------------------------------------------------
// Description  : Set phase
// Input Value  : ucPhase   --> Target phase, ucPhase = N, N = 0 ~ 63
// Output Value : None
//--------------------------------------------------
void CAdjustPhase(BYTE ucPhase)
{
    BYTE ctrl;
    WORD select; //V306 modify

    CAdjustEnableWatchDog(_WD_DV_TIMEOUT_APLL_NONLOCK);

    ucPhase = ucPhase & 0x3f;

    // Code below is to select stable HSYNC latch edge.
    // There is about 6.0736ns delay for RTD2323 between input clock into ADC and output from ADC.
    // Calculating the corresponding phase delay for 6.0736ns 
    // Original Formula :
	// select = 64 * 6.0736 * ulRate / 1000000;

#if (_SCALER_TYPE == _RTD2553V || _SCALER_TYPE == _RTD2546N || _SCALER_TYPE == _RTD2525L)
    // There is about 2.025ns/2.579ns delay for RTD2553V/RTD2525L between input clock into ADC and output from ADC.
    // Calculating the corresponding phase delay for 2.025ns/2.579ns     
    // Original Formula :
	// select = 64 * 2.025 * ulRate / 1000000; for RTD2553V series
    // select = 64 * 2.579 * ulRate / 1000000; for RTD2525L series

    select      = (DWORD)_RTD_XTAL * stModeInfo.IHTotal / stModeInfo.IHCount * ((_SCALER_TYPE == _RTD2525L) ? 165 : 130) / 1000000; //V307 modify
#elif(_SCALER_TYPE == _RTD2547D)
    // There is about 2.025ns delay for RTD2528R between input clock into ADC and output from ADC.
    // Calculating the corresponding phase delay for 2.025ns 
    // Original Formula :
	// select = 64 * 0.015 * ulRate / 1000000;

    select      = (DWORD)_RTD_XTAL * stModeInfo.IHTotal / stModeInfo.IHCount * 1 / 1000000;
#else
    select      = (DWORD)_RTD_XTAL * stModeInfo.IHTotal / stModeInfo.IHCount * 389 / 1000000;
#endif

    select      = (select <= 64) ? (64 - select) : (128 - select);

    // Calculate the absolute value from the selected phase to transition
    pData[0]    = (ucPhase >= select) ? ucPhase - select : select - ucPhase;
    ctrl        = (pData[0] > 12 && pData[0] < 52) ? 0x00 : 0x01;

    if((stModeInfo.IHStartPos < stModeUserData.HPosition) && ((stModeUserData.HPosition - stModeInfo.IHStartPos) > ucHStartBias))
        stModeUserData.HPosition = stModeInfo.IHStartPos + ucHStartBias;

    if((stModeInfo.IHStartPos > stModeUserData.HPosition) && ((stModeInfo.IHStartPos - stModeUserData.HPosition) > ucHStartBias))
        stModeUserData.HPosition = stModeInfo.IHStartPos - ucHStartBias;

//    pData[0]    = ucHStartBias + stModeInfo.IHStartPos - stModeUserData.HPosition  + _PROGRAM_HDELAY;
    ((WORD *)pData)[0]  = ucHStartBias + stModeInfo.IHStartPos - stModeUserData.HPosition  + _PROGRAM_HDELAY; //V306 modify

    // Compensate the H position shift due to the phase select
    if (select > 12)
        select  = ((ucPhase + 12) < select) ? (((WORD *)pData)[0] - 1) : ((WORD *)pData)[0]; //V306 modify
    else
        select  = (ucPhase < (select + 52)) ? (((WORD *)pData)[0] - 1) : ((WORD *)pData)[0]; //V306 modify

#if(_SCALER_TYPE == _RTD2547D)
    CScalerPageSelect(_PAGE1);
    CScalerSetBit(_P1_PLLDIV_H_B2, ~_BIT6, _BIT6);
#else
    CScalerSetBit(_PLLDIV_H_A9, ~_BIT6, _BIT6);
#endif

    if(((DWORD)stModeInfo.IHFreq * stModeInfo.IHTotal / 1000) < 530)
    {
#if(_SCALER_TYPE == _RTD2547D)
        CScalerSetBit(_P1_PLLPHASE_CTRL1_B5, 0x80, ucPhase * 2);           // Set phase
#else
        CScalerSetBit(_PLLPHASE_CTRL1_AC, 0x80, ucPhase * 2);           // Set phase
#endif
    }
    else
    {
#if(_SCALER_TYPE == _RTD2547D)
        CScalerSetBit(_P1_PLLPHASE_CTRL1_B5, 0x80, ucPhase);               // Set phase
#else
        CScalerSetBit(_PLLPHASE_CTRL1_AC, 0x80, ucPhase);               // Set phase
#endif
    }

    CAdjustIHSDelay(select);                                        // Compensate IHS delay
#if(_SCALER_TYPE == _RTD2547D)
    CScalerSetBit(_VGIP_DELAY_CTRL_12, ~_BIT3, (ctrl << 3));        // Select a correct edge to latch the stable data
#else
    CScalerSetBit(_VGIP_DELAY_CTRL_07, ~_BIT3, (ctrl << 3));        // Select a correct edge to latch the stable data
#endif

    CMiscApplyDoubleBuffer();

    CMiscClearStatusRegister();

    CAdjustEnableWatchDog(_WD_ALL);
}

//--------------------------------------------------
// Description  : Set H Position
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CAdjustHPosition(void)
{
    // Update IHS delay according to phase
    CAdjustPhase(stModeUserData.Phase);
}

//--------------------------------------------------
// Description  : Set V Position
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CAdjustVPosition(void)
{
    CAdjustEnableWatchDog(_WD_APLL_NONLOCK);

    if((stModeInfo.IVStartPos < stModeUserData.VPosition) && ((stModeUserData.VPosition - stModeInfo.IVStartPos) > ucVStartBias))
        stModeUserData.VPosition = stModeInfo.IVStartPos + ucVStartBias;

    if((stModeInfo.IVStartPos > stModeUserData.VPosition) && ((stModeInfo.IVStartPos - stModeUserData.VPosition) > ucVStartBias))
        stModeUserData.VPosition = stModeInfo.IVStartPos - ucVStartBias;

#if(_V_POSITION_DIRECTION == _V_POSITION_METHOD_0)

    CAdjustIVSDelay(ucVStartBias + stModeInfo.IVStartPos - stModeUserData.VPosition + _PROGRAM_VDELAY);

#endif

#if(_V_POSITION_DIRECTION == _V_POSITION_METHOD_1)

    CAdjustIVSDelay(ucVStartBias - (stModeInfo.IVStartPos - stModeUserData.VPosition) + _PROGRAM_VDELAY);

#endif

    CMiscApplyDoubleBuffer();

    CTimerWaitForEvent(_EVENT_DEN_STOP);
    CTimerWaitForEvent(_EVENT_DEN_START);

    CMiscClearStatusRegister();

    CAdjustEnableWatchDog(_WD_ALL);
}

//--------------------------------------------------
// Description  : Adjust Digital Filter
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CAdjustDigitalFilter(BYTE ucAccess, BYTE ucOffset, BYTE ucDiv, BYTE ucEnable)
{
#if (_SCALER_TYPE == _RTD2553V || _SCALER_TYPE == _RTD2546N || _SCALER_TYPE == _RTD2525L || _SCALER_TYPE == _RTD2547D)
    pData[0] = ((ucAccess & 0x0f) << 4) | 0x00;
#else
    pData[0] = ((ucAccess & 0x07) << 5) | 0x00;
#endif

    if(ucAccess == _YPBPR_ACCESS_PORT)
    {
        pData[1] = ((ucOffset & 0x07) << 5) | 0x10;
    }
    else
    {
        pData[1] = ((ucEnable & 0x01) << 7) | ((ucOffset & 0x07) << 4) | ((ucDiv & 0x03) << 2);
    }

#if(_SCALER_TYPE == _RTD2547D)
    CScalerWrite(_DIGITAL_FILTER_CTRL_98, 2, pData, _AUTOINC);

    CScalerSetByte(_DIGITAL_FILTER_CTRL_98, 0x00);
#else
    CScalerWrite(_DIGITAL_FILTER_CTRL_17, 2, pData, _AUTOINC);

    CScalerSetByte(_DIGITAL_FILTER_CTRL_17, 0x00);
#endif
}

#if (_SCALER_TYPE == _RTD2553V || _SCALER_TYPE == _RTD2546N || _SCALER_TYPE == _RTD2525L)
#if (_VGA_COLOR_SUPPORT)
/*
void CAdjustEnableHLWindow(void)
{
    CScalerSetBit(_HW_ACCESS_PORT_60, ~_BIT6, _BIT6);
    CAdjustHLWindowBrightness(stOsdUserData.MZBright);
    CAdjustHLWindowContrast(stOsdUserData.MZContrast);
    CAdjustMZHueSat(0);
    CAdjustMZHueSat(1);
    CAdjustMZHueSat(2);
    CAdjustFillDCCTable(tDCC_CONTROL[GET_MZ_DCC_TYPE()], tDCC_USERCURVE[GET_MZ_DCC_TYPE()]);
}

void CAdjustDisableHLWindow(void)
{
    CAdjustMZHueSat(0);
    CAdjustMZHueSat(1);
    CAdjustMZHueSat(2);
    CAdjustFillDCCTable(tDCC_CONTROL[GET_MZ_DCC_TYPE()], tDCC_USERCURVE[GET_MZ_DCC_TYPE()]);
    CScalerSetBit(_HW_ACCESS_PORT_60, ~_BIT6, 0x00);
}

void CAdjustHLWindow(void)
{
    if(GET_MZ_WINDOW_CFG_TYPE() == _MZ_WINDOW_CFG_DISABLE)
    {
        CAdjustDisableHLWindow();
    }
    else if(GET_MZ_WINDOW_CFG_TYPE() == _MZ_WINDOW_CFG_FULL)
    {
        CAdjustHLWindowHV(0, stDisplayInfo.DHWidth, 0, stDisplayInfo.DVHeight);
        CAdjustNormalizeFactor(stDisplayInfo.DHWidth, stDisplayInfo.DVHeight);
        CAdjustEnableHLWindow();
    }
    else if(GET_MZ_WINDOW_CFG_TYPE() == _MZ_WINDOW_CFG_DEMO)
    {
        CAdjustHLWindowHV(0, stDisplayInfo.DHWidth / 2, 0, stDisplayInfo.DVHeight);
        CAdjustNormalizeFactor(stDisplayInfo.DHWidth / 2, stDisplayInfo.DVHeight);
        CAdjustEnableHLWindow();
    }
    else if(GET_MZ_WINDOW_CFG_TYPE() == _MZ_WINDOW_CFG_WINDOW)
    {
        CAdjustHLWindowHV(stOsdUserData.MZHPos, stOsdUserData.MZHWidth, stOsdUserData.MZVPos, stOsdUserData.MZVHeight);
        CAdjustNormalizeFactor(stOsdUserData.MZHWidth, stOsdUserData.MZVHeight);
        CAdjustEnableHLWindow();
    }
}

void CAdjustHLWindowHV(WORD usHPos, WORD usHWidth, WORD usVPos, WORD usVHeight)
{
    if(usHWidth == 0 || usVHeight == 0)
        return;

    CScalerSetBit(_HW_ACCESS_PORT_60, ~(_BIT7 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT7);

    pData[0] = ((usHPos >> 8) & 0x07);
    pData[1] = (BYTE)(usHPos);
    pData[2] = (((usHPos + usHWidth) >> 8) & 0x07);
    pData[3] = (BYTE)(usHPos + usHWidth);
    pData[4] = ((usVPos >> 8) & 0x07);
    pData[5] = (BYTE)(usVPos);
    pData[6] = (((usVPos + usVHeight) >> 8) & 0x07);
    pData[7] = (BYTE)(usVPos + usVHeight);

    CTimerWaitForEvent(_EVENT_DEN_STOP);

    CScalerWrite(_HW_DATA_PORT_61, 8, pData, _NON_AUTOINC);

    CScalerSetBit(_HW_ACCESS_PORT_60, ~(_BIT7 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
}

//
void CAdjustHLWindowHVBorder(BYTE ucBorderWidth, BYTE ucRed, BYTE ucGreen, BYTE ucBlue)
{
    CScalerSetBit(_HW_ACCESS_PORT_60, ~(_BIT7 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT7 | 0x08);

    pData[0] = (ucBorderWidth & 0x0f);
    pData[1] = (ucRed & 0x3f);
    pData[2] = (ucGreen & 0x3f);
    pData[3] = (ucBlue & 0x3f);

    CScalerWrite(_HW_DATA_PORT_61, 4, pData, _NON_AUTOINC);

    CScalerSetBit(_HW_ACCESS_PORT_60, ~(_BIT7 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
}
//

void CAdjustHLWindowBrightness(BYTE ucValue)
{
    if(GET_MZ_WINDOW_CFG_TYPE() == _MZ_WINDOW_CFG_FULL)
        ucValue = 128;

    CScalerSetBit(_CB_ACCESS_PORT_64, ~(_BIT7 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT7 | 0x06);

    pData[0] = pData[1] = pData[2] = ucValue;

    CScalerWrite(_CB_DATA_PORT_65, 3, pData, _NON_AUTOINC);

    CScalerSetByte(_CB_ACCESS_PORT_64, 0x00);
}

void CAdjustHLWindowContrast(BYTE ucValue)
{
    if(GET_MZ_WINDOW_CFG_TYPE() == _MZ_WINDOW_CFG_FULL)
        ucValue = 128;

    CScalerSetBit(_CB_ACCESS_PORT_64, ~(_BIT7 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT7 | 0x09);

    pData[0] = pData[1] = pData[2] = ucValue;

    CScalerWrite(_CB_DATA_PORT_65, 3, pData, _NON_AUTOINC);

    CScalerSetByte(_CB_ACCESS_PORT_64, 0x00);
}

void CAdjustNormalizeFactor(WORD usHWidth, WORD usVHeight)
{
    ((DWORD *)pData)[0] = (DWORD)4194304 * 255 / usHWidth / usVHeight;

    CScalerSetBit(_DCC_CTRL0_E4, ~(_BIT1 | _BIT0), 0x00);

    CScalerSetByte(_DCC_ACCESS_PORT_E6, 0x00);

    ((DWORD *)pData)[0] &= 0x3fffff;

    CScalerWrite(_DCC_DATA_PORT_E7, 3, &pData[1], _NON_AUTOINC);
}

//--------------------------------------------------
// Description    : Fill DCC table , then enable DCC function
// Input Value   : pControlTable, pUserCurveTable, both parameters accroding to Vivid color software.
// Output Value : None
//--------------------------------------------------
void CAdjustFillDCCTable(BYTE *pControlTable, BYTE *pUserCurveTable)
{
    BYTE i;
        
    // switch to page 0
    CScalerRead(_DCC_CTRL0_E4, 1, &i, _NON_AUTOINC);
    i = i & 0xfc;   
    CScalerSetByte(_DCC_CTRL0_E4, i);      

    // fill DCC control table
    CScalerSetByte(_DCC_ACCESS_PORT_E6, 0x03);
    for (i =0; i<9; i++)
    {
        CScalerSetByte(_DCC_DATA_PORT_E7, *pControlTable);
        pControlTable++;
    }

    // switch to page 1
    CScalerRead(_DCC_CTRL0_E4, 1, &i, _NON_AUTOINC);
    i = (i & 0xfc) | 0x01;
    CScalerSetByte(_DCC_CTRL0_E4, i);
    
    // fill DCC user curve table
    CScalerSetByte(_DCC_ACCESS_PORT_E6, 0x00); 
    for (i=0; i<20; i++)
    {                
        CScalerSetByte(_DCC_DATA_PORT_E7, *pUserCurveTable);
        pUserCurveTable++;
    }

    // enable DCC func when _EVENT_DEN_STOP
    CTimerWaitForEvent(_EVENT_DEN_STOP);

    if((GET_MZ_DCC_TYPE() == _MZ_DCC_NORMAL) || (GET_MZ_WINDOW_CFG_TYPE() == _MZ_WINDOW_CFG_DISABLE))
    {
        CScalerSetByte(_DCC_CTRL0_E4, 0x2c);
    }
    else
    {
        CScalerSetByte(_DCC_CTRL0_E4, 0xac);
    }

    CScalerSetByte(_DCC_CTRL1_E5, 0x80);
}

BYTE code SatPlus[8]  = { 41, 44, 43, 39, 31, 22, 11, 0 }; // by 1/256
BYTE code SatMinus[8] = { 24, 35, 40, 41, 36, 28, 16, 0 }; // by 1/256

int CAdjustColorGammaCal(BYTE color, BYTE n) // n = 1~8
{
    int temp = (color == 0) ? stOsdUserData.MZICMRedSat : (color == 1) ? stOsdUserData.MZICMGreenSat : stOsdUserData.MZICMBlueSat;

    temp *= 2;

    if (temp >= 16)
    {
        return ((int)(512*n) + (int)((temp-16)*(int)SatPlus[n-1])) / 64 ;
    }
    else
    {
        return ((int)(512*n) - (int)((16-temp)*(int)SatMinus[n-1])) / 64 ;
    }
}

void CAdjustHueSatSet(BYTE color, SWORD TempU1, SWORD TempU2, SWORD TempV1, SWORD TempV2)
{
    BYTE i;
    SWORD u,v;

    CScalerSetByte(0xe1,(color & 0x0f));
    CScalerSetByte(0xe2,0x00);

    if((color & 0x0f) == 0)
    {
        CScalerSetByte(0xe3,0x02);
        CScalerSetByte(0xe3,0xd2);
        CScalerSetByte(0xe3,0xee);
    }
    else if((color & 0x0f) == 1)
    {
        CScalerSetByte(0xe3,0x08);
        CScalerSetByte(0xe3,0x00);
        CScalerSetByte(0xe3,0xee);
    }
    else if((color & 0x0f) == 2)
    {
        CScalerSetByte(0xe3,0x0d);
        CScalerSetByte(0xe3,0x2e);
        CScalerSetByte(0xe3,0xbe);
    }

    
    CScalerSetByte(0xe1,(color & 0x0f));
    CScalerSetByte(0xe2,((color & 0xf0)+0x03));	

    for(i=1; i<9; i++)
    {
        u = ((TempU1+TempU2)*CAdjustColorGammaCal(color, i)/64) - ((TempU1*i)/8);
        v = ((TempV1+TempV2)*CAdjustColorGammaCal(color, i)/64) - ((TempV1*i)/8);

        CScalerSetByte(0xe3,u);
        CScalerSetByte(0xe3,v);
    }
//
    for(i=1; i<33; i++)
    {
        CScalerSetByte(0xe3,0x00);
    }
//
    CScalerSetByte(0xe0,0xdc);
}

void CAdjustMZComboHueSat(BYTE ucVar, SWORD sTempU1, SWORD sTempV1, SWORD sConst0, SWORD sConst1, SWORD sConst2, SWORD sConst3, BYTE ucPar)
{
    SWORD sTempU2, sTempV2;

    if(ucVar < 8)
    {
        sTempU2 = (SWORD)(sConst0) * (8 - ucVar) / 8;
        sTempV2 = (SWORD)(sConst1) * (8 - ucVar) / 8;
    }
    else
    {
        sTempU2 = (SWORD)(sConst2) * (ucVar - 8) / 8;
        sTempV2 = (SWORD)(sConst3) * (ucVar - 8) / 8;
    }

    CAdjustHueSatSet(ucPar, sTempU1, sTempU2, sTempV1, sTempV2);
}

void CAdjustMZHueSat(BYTE color)
{
    if(color == 0)
    {
        CAdjustMZComboHueSat(stOsdUserData.MZICMRedHue, 255, 510, (64 - 8), (-128 + 16), (-128 + 16), (-48), 0x00);

        CAdjustMZComboHueSat(stOsdUserData.MZICMRedHue, 437, 146, (64 - 8), (-128 + 16), (-64 + 8), (128 - 16), 0x10);

        CAdjustMZComboHueSat(stOsdUserData.MZICMRedHue, -170, 510, (128 - 16), (-48), (-128 + 16), (-48), 0x20);

	}
    else if(color == 1)
    {
        CAdjustMZComboHueSat(stOsdUserData.MZICMGreenHue, -510, 0, (64 - 8), (128 - 16), (64 - 8), (-128 + 16), 0x01);

        CAdjustMZComboHueSat(stOsdUserData.MZICMGreenHue, -340, 340, (64 - 8), (128 - 16), (-64 + 8), (-128 + 16), 0x11);

        CAdjustMZComboHueSat(stOsdUserData.MZICMGreenHue, -340, -340, (-64 + 8), (128 - 16), (64 - 8), (-128 + 16), 0x21);

	}
    else if(color == 2)
    {
        CAdjustMZComboHueSat(stOsdUserData.MZICMBlueHue, 255, -510, (-128 + 16), (48), (64 - 8), (128 - 16), 0x02);

        CAdjustMZComboHueSat(stOsdUserData.MZICMBlueHue, -170, -510, (-128 + 16), (48), (128 - 16), (48), 0x12);

        CAdjustMZComboHueSat(stOsdUserData.MZICMBlueHue, 355, -310, (-64 + 8), (-128 + 16), (64 - 8), (128 - 16), 0x22);
	}

    if((GET_MZ_ICM_ON_OFF_TYPE() == _ON) && (GET_MZ_WINDOW_CFG_TYPE() != _MZ_WINDOW_CFG_DISABLE))
        CScalerSetBit(_ICM_CTRL_E0, ~_BIT7, _BIT7);
    else
        CScalerSetBit(_ICM_CTRL_E0, ~_BIT7, 0x00);
}
*/

//--------------------------------------------------
// Description  : 
// Input Value  : 
// Output Value : 
//--------------------------------------------------
void CAdjustHLWindowPeaking(BYTE ucValue)
{
	CAdjustPeakingFilter(ucValue);

//Six Axes Color
    if(ucValue == 0)
        SET_MZ_PEAKING_ON_OFF_TYPE(_OFF);
    else
        SET_MZ_PEAKING_ON_OFF_TYPE(_ON);
}

//--------------------------------------------------
// Description  : Adjust Peaking Filter and Coring Control
// Input Value  : Coefficient C0 of Peaking Filter
// Output Value : None
//--------------------------------------------------
void CAdjustPeakingFilter(SBYTE ucPeaking)
{
	if(ucPeaking > 126)
		ucPeaking = 126;
	if(ucPeaking < 14 && ucPeaking > 0)
		ucPeaking = 14;

	pData[0] = ((ucPeaking +1) >> 1) << 1;

    switch(_GET_INPUT_SOURCE())
    {
        case _SOURCE_VGA:
        case _SOURCE_DVI:
        case _SOURCE_HDMI:
			if((bit)(ucPeaking & 0x01))
			{
				pData[1] = (SWORD)-63 * pData[0] / 126;
				pData[2] = 0;
			}
			else
			{
				pData[1] = (SWORD)-64 * pData[0] / 126;
				pData[2] = 2;
			}
            break;

        case _SOURCE_VIDEO_AV:
        case _SOURCE_VIDEO_SV:
        //case _SOURCE_VIDEO_YUV:
        case _SOURCE_VIDEO_TV:
        case _SOURCE_YPBPR:
        case _SOURCE_VIDEO_SCART:
	 case _SOURCE_VIDEO_DVD:
			if((bit)(ucPeaking & 0x01))
			{
				pData[1] = (SWORD)-72 * pData[0] / 126;
				pData[2] = (SWORD)-(pData[0] + 2*pData[1]) / 2;
			}
			else
			{
				pData[1] = (SWORD)-73 * pData[0] / 126;
				pData[2] = (SWORD)-(pData[0] + 2*pData[1]) / 2;
			}
	        break;
	}

	pData[3] = (BYTE)_CORING_MIN;
	pData[4] = (BYTE)_CORING_MAX_POS;
	pData[5] = (SBYTE)_CORING_MAX_NEG; 

    CScalerSetByte(_PC_ACCESS_PORT_26, 0x80);
    CScalerWrite(_PC_DATA_PORT_27, 6, pData, _NON_AUTOINC);
    CScalerSetByte(_PC_ACCESS_PORT_26, 0x40);
}


//*************** Six Axes Color ***************//


void CAdjustAccessICMTable(BYTE ucNum)
{
    BYTE i=0;

    if(ucNum == _SAC_DCC_GRAPHIC)    
    {
        for (i=0; i<5; i++)
        {            
            CScalerSetByte(_ICM_SEL_E1, (0x00 + i));
            CScalerSetByte(_ICM_ACCESS_PORT_E2, 0x00);
            CScalerWrite(_ICM_DATA_PORT_E3, 51, tICM_SAC_PHOTO[i], _NON_AUTOINC);
        }
        CScalerSetByte(_ICM_CTRL_E0, 0xdf);    
    }
    else
    {
        for (i=0; i<4; i++)
        {            
            CScalerSetByte(_ICM_SEL_E1, (0x00 + i));
            CScalerSetByte(_ICM_ACCESS_PORT_E2, 0x00);
            CScalerWrite(_ICM_DATA_PORT_E3, 51, tICM_SAC[ucNum * 4 + i], _NON_AUTOINC);
        }
        CScalerSetByte(_ICM_CTRL_E0, 0xde);
    }

}
//--------------------------------------------------
// Description    : Fill DCC table , then enable DCC function
// Input Value   : pControlTable, pUserCurveTable, both parameters accroding to Vivid color software.
// Output Value : None
//--------------------------------------------------
void CAdjustFillDCCTable(BYTE *pControlTable, BYTE *pUserCurveTable)
{
    BYTE i;
        
    // switch to page 0
    CScalerRead(_DCC_CTRL0_E4, 1, &i, _NON_AUTOINC);
    i = i & 0xfc;   
    CScalerSetByte(_DCC_CTRL0_E4, i);      

    // fill DCC control table
    CScalerSetByte(_DCC_ACCESS_PORT_E6, 0x03);
    for (i =0; i<9; i++)
    {
        CScalerSetByte(_DCC_DATA_PORT_E7, *pControlTable);
        pControlTable++;
    }

    // switch to page 1
    CScalerRead(_DCC_CTRL0_E4, 1, &i, _NON_AUTOINC);
    i = (i & 0xfc) | 0x01;
    CScalerSetByte(_DCC_CTRL0_E4, i);
    
    // fill DCC user curve table
    CScalerSetByte(_DCC_ACCESS_PORT_E6, 0x00); 
    for (i=0; i<20; i++)
    {                
        CScalerSetByte(_DCC_DATA_PORT_E7, *pUserCurveTable);
        pUserCurveTable++;
    }

    // enable DCC func when _EVENT_DEN_STOP
    CTimerWaitForEvent(_EVENT_DEN_STOP);

    if(((GET_MZ_DCC_TYPE() == _MZ_DCC_NORMAL) || (GET_MZ_WINDOW_CFG_TYPE() == _MZ_WINDOW_CFG_DISABLE)))
    {
        CScalerSetByte(_DCC_CTRL0_E4, 0x2c);
    }
    else
    {
        CScalerSetByte(_DCC_CTRL0_E4, 0xac);
    }

    CScalerSetByte(_DCC_CTRL1_E5, 0x80);
}


BYTE code SatPlus[8]  = { 61, 64, 63, 59, 51, 40, 28, 0 }; // by 1/256
BYTE code SatMinus[8] = { 44, 45, 60, 61, 56, 48, 26, 0 }; // by 1/256


void CAdjustEnableHLWindow(void)
{
    CScalerSetBit(_HW_ACCESS_PORT_60, ~_BIT6, _BIT6);
    CScalerSetBit(_ICM_CTRL_E0, ~_BIT7, _BIT7);
    CScalerSetBit(_DCC_CTRL0_E4, ~_BIT7, _BIT7);
    CAdjustHLWindowBrightness(stOsdUserData.MZBright);
    CAdjustHLWindowContrast(stOsdUserData.MZContrast);
//    CAdjustMZHueSat(0);
//    CAdjustMZHueSat(1);
//    CAdjustMZHueSat(2);
//    CAdjustFillDCCTable(tDCC_CONTROL[GET_MZ_DCC_TYPE()], tDCC_USERCURVE[GET_MZ_DCC_TYPE()]);
}

void CAdjustDisableHLWindow(void)
{
//    CAdjustMZHueSat(0);
//    CAdjustMZHueSat(1);
//    CAdjustMZHueSat(2);
    CAdjustFillDCCTable(tDCC_CONTROL[GET_MZ_DCC_TYPE()], tDCC_USERCURVE[GET_MZ_DCC_TYPE()]);
    CScalerSetBit(_HW_ACCESS_PORT_60, ~_BIT6, 0x00);
    CScalerSetBit(_ICM_CTRL_E0, ~_BIT7, 0x00);
    CScalerSetBit(_DCC_CTRL0_E4, ~_BIT7, 0x00);
}

void CAdjustHLWindow(void)
{
    if((GET_SAC_DCC_TYPE() == _SAC_DCC_NORMAL) || ((GET_SAC_DCC_TYPE() == _SAC_DCC_USER) && (GET_MZ_DCC_TYPE() == _MZ_DCC_NORMAL) && (GET_MZ_ICM_ON_OFF_TYPE() == _OFF)))
        SET_MZ_WINDOW_CFG_TYPE(_MZ_WINDOW_CFG_DISABLE);
    else
        SET_MZ_WINDOW_CFG_TYPE(_MZ_WINDOW_CFG_FULL);

    if(GET_MZ_WINDOW_CFG_TYPE() == _MZ_WINDOW_CFG_DISABLE)
    {
        CAdjustDisableHLWindow();
    }
    else if(GET_MZ_WINDOW_CFG_TYPE() == _MZ_WINDOW_CFG_FULL)
    {
        CAdjustHLWindowHV(0, stDisplayInfo.DHWidth, 0, stDisplayInfo.DVHeight);
        CAdjustNormalizeFactor(stDisplayInfo.DHWidth, stDisplayInfo.DVHeight);

        if(GET_SAC_DCC_TYPE() == _SAC_DCC_NORMAL)
            CAdjustDisableHLWindow();
        else
            CAdjustEnableHLWindow(); 
    }
/*
    else if(GET_MZ_WINDOW_CFG_TYPE() == _MZ_WINDOW_CFG_DEMO)
    {
        CAdjustHLWindowHV(0, stDisplayInfo.DHWidth / 2, 0, stDisplayInfo.DVHeight);
        CAdjustNormalizeFactor(stDisplayInfo.DHWidth / 2, stDisplayInfo.DVHeight);
        CAdjustEnableHLWindow();
    }
    else if(GET_MZ_WINDOW_CFG_TYPE() == _MZ_WINDOW_CFG_WINDOW)
    {
        CAdjustHLWindowHV(stOsdUserData.MZHPos, stOsdUserData.MZHWidth, stOsdUserData.MZVPos, stOsdUserData.MZVHeight);
        CAdjustNormalizeFactor(stOsdUserData.MZHWidth, stOsdUserData.MZVHeight);
        CAdjustEnableHLWindow();
    }
*/
}

void CAdjustHLWindowHV(WORD usHPos, WORD usHWidth, WORD usVPos, WORD usVHeight)
{
    if(usHWidth == 0 || usVHeight == 0)
        return;

    CScalerSetBit(_HW_ACCESS_PORT_60, ~(_BIT7 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT7);

    pData[0] = ((usHPos >> 8) & 0x07);
    pData[1] = (BYTE)(usHPos);
    pData[2] = (((usHPos + usHWidth) >> 8) & 0x07);
    pData[3] = (BYTE)(usHPos + usHWidth);
    pData[4] = ((usVPos >> 8) & 0x07);
    pData[5] = (BYTE)(usVPos);
    pData[6] = (((usVPos + usVHeight) >> 8) & 0x07);
    pData[7] = (BYTE)(usVPos + usVHeight);

    CTimerWaitForEvent(_EVENT_DEN_STOP);

    CScalerWrite(_HW_DATA_PORT_61, 8, pData, _NON_AUTOINC);

    CScalerSetBit(_HW_ACCESS_PORT_60, ~(_BIT7 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
}

void CAdjustNormalizeFactor(WORD usHWidth, WORD usVHeight)
{
    ((DWORD *)pData)[0] = (DWORD)4194304 * 255 / usHWidth / usVHeight;

    CScalerSetBit(_DCC_CTRL0_E4, ~(_BIT1 | _BIT0), 0x00);

    CScalerSetByte(_DCC_ACCESS_PORT_E6, 0x00);

    ((DWORD *)pData)[0] &= 0x3fffff;

    CScalerWrite(_DCC_DATA_PORT_E7, 3, &pData[1], _NON_AUTOINC);
}

void CAdjustHLWindowBrightness(BYTE ucValue)
{
    if(GET_MZ_WINDOW_CFG_TYPE() == _MZ_WINDOW_CFG_FULL)
        ucValue = 128;

    CScalerSetBit(_CB_ACCESS_PORT_64, ~(_BIT7 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT7 | 0x06);

    pData[0] = pData[1] = pData[2] = ucValue;

    CScalerWrite(_CB_DATA_PORT_65, 3, pData, _NON_AUTOINC);

    CScalerSetByte(_CB_ACCESS_PORT_64, 0x00);
}

void CAdjustHLWindowContrast(BYTE ucValue)
{
    if(GET_MZ_WINDOW_CFG_TYPE() == _MZ_WINDOW_CFG_FULL)
        ucValue = 128;

    CScalerSetBit(_CB_ACCESS_PORT_64, ~(_BIT7 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT7 | 0x09);

    pData[0] = pData[1] = pData[2] = ucValue;

    CScalerWrite(_CB_DATA_PORT_65, 3, pData, _NON_AUTOINC);

    CScalerSetByte(_CB_ACCESS_PORT_64, 0x00);
}

int CAdjustColorGammaCal(BYTE color, BYTE n) 
{
   int temp;
    switch(color&0x0f)
	{
	    case _V_RED: // CM0
            if(( color & 0xf0 ) == 0x00)
     		    temp = stOsdUserData.MZICMRedSat;
            else if(( color & 0xf0 ) == 0x10) 
                temp = stOsdUserData.MZICMRedSat/2 + stOsdUserData.MZICMMagentaSat ;
            else if(( color & 0xf0 ) == 0x20)
                temp = (stOsdUserData.MZICMRedSat + stOsdUserData.MZICMYellowSat)/2 ;
		break;

		case _V_GREEN: // CM1
		    if(( color & 0xf0 ) == 0x00)
			    temp = stOsdUserData.MZICMYellowSat;
            else if(( color & 0xf0 ) == 0x10) 
			    temp = (stOsdUserData.MZICMRedSat + stOsdUserData.MZICMYellowSat)/2 ;
            else if(( color & 0xf0 ) == 0x20)
         	    temp = (stOsdUserData.MZICMGreenSat + stOsdUserData.MZICMYellowSat)/2 ;			    
		break;

		case _V_BLUE: // CM2 
		    if(( color & 0xf0 ) == 0x00)
			    temp = stOsdUserData.MZICMGreenSat ;
            else if(( color & 0xf0 ) == 0x10)
                temp = (stOsdUserData.MZICMGreenSat + stOsdUserData.MZICMYellowSat)/2 ;
            else if(( color & 0xf0 ) == 0x20)
			    temp = (stOsdUserData.MZICMGreenSat + stOsdUserData.MZICMCyanSat)/2 ;
		break;

		case _V_YELLOW: // CM3
		    if(( color & 0xf0 ) == 0x00)
			    temp = stOsdUserData.MZICMCyanSat ;
            else if(( color & 0xf0 ) == 0x10)
			    temp = stOsdUserData.MZICMGreenSat + stOsdUserData.MZICMCyanSat/2 ;
            else if(( color & 0xf0 ) == 0x20)
			    temp = stOsdUserData.MZICMCyanSat/4 + stOsdUserData.MZICMBlueSat;

		break;

		case _V_CYAN: //CM4
		    if(( color & 0xf0 ) == 0x00)
                temp = stOsdUserData.MZICMBlueSat/2 + stOsdUserData.MZICMMagentaSat; 
            else if(( color & 0xf0 ) == 0x10) 
			    temp = stOsdUserData.MZICMCyanSat/4 + stOsdUserData.MZICMBlueSat;  
            else if(( color & 0xf0 ) == 0x20)
			    temp = stOsdUserData.MZICMRedSat/2 +  stOsdUserData.MZICMMagentaSat;
		break;

	}
    temp *= 2;

    if (temp >= 16)
    {
        return ((int)(512*n) + (int)((temp-16)*(int)SatPlus[n-1])) / 64 ;
    }
    else
    {
        return ((int)(512*n) - (int)((16-temp)*(int)SatMinus[n-1])) / 64 ;
    }
}

void CAdjustHueSatSet(BYTE color, SWORD TempU1, SWORD TempU2, SWORD TempV1, SWORD TempV2)
{
    BYTE i;
    SWORD u,v;
    
    CScalerSetByte(0xe1,(color & 0x0f));
    CScalerSetByte(0xe2,0x00);

    if((color & 0x0f) == _V_RED) //CM0
    {
        CScalerSetByte(0xe3,0x03);
        CScalerSetByte(0xe3,0x00);
		CScalerSetByte(0xe3,0x8c);
    }
    else if((color & 0x0f) == _V_GREEN) //CM1
    {
        CScalerSetByte(0xe3,0x05);
        CScalerSetByte(0xe3,0x00);
        CScalerSetByte(0xe3,0x88);
    }
    else if((color & 0x0f) == _V_YELLOW) //CM3
    {
        CScalerSetByte(0xe3,0x0b);
        CScalerSetByte(0xe3,0x00);
		CScalerSetByte(0xe3,0xc8);
    }
    else if((color & 0x0f) == _V_CYAN) //CM4
    {
        CScalerSetByte(0xe3,0x0f);
		CScalerSetByte(0xe3,0x00);
		CScalerSetByte(0xe3,0xcc);
    }
	else if(((color & 0x0f) == _V_BLUE)) // CM2
    {
        CScalerSetByte(0xe3,0x08);
        CScalerSetByte(0xe3,0x00);
		CScalerSetByte(0xe3,0xcc);
    }

    
    CScalerSetByte(0xe1,(color & 0x0f));
    CScalerSetByte(0xe2,((color & 0xf0)+0x03));	

    for(i=1; i<9; i++)
    {
        u = ((TempU1+TempU2)*CAdjustColorGammaCal(color, i)/64) - ((TempU1*i)/8);
        v = ((TempV1+TempV2)*CAdjustColorGammaCal(color, i)/64) - ((TempV1*i)/8);

		if(u>127)
	        u=127;
		else if(u<-128) 
		    u=-128;

		if(v>127)
	        v=127;
		else if(v<-128) 
		    v=-128;

        CScalerSetByte(0xe3,u);
        CScalerSetByte(0xe3,v);
    }

    CScalerSetByte(0xe0,0xdf);
}

void CAdjustMZComboHueSat(BYTE ucVar, SWORD sTempU1, SWORD sTempV1, SWORD sConst0, SWORD sConst1, SWORD sConst2, SWORD sConst3, BYTE ucPar)
{
    SWORD sTempU2, sTempV2;

    if(ucVar < 8)
    {
        sTempU2 = (SWORD)(sConst0) * (8 - ucVar) / 8;
        sTempV2 = (SWORD)(sConst1) * (8 - ucVar) / 8;
    }
    else
    {
        sTempU2 = (SWORD)(sConst2) * (ucVar - 8) / 8;
        sTempV2 = (SWORD)(sConst3) * (ucVar - 8) / 8;
    }

    CAdjustHueSatSet(ucPar, sTempU1, sTempU2, sTempV1, sTempV2);
}

void CAdjustMZHueSat(BYTE color)
{
    if((GET_SAC_DCC_TYPE() == _SAC_DCC_NORMAL) || ((GET_SAC_DCC_TYPE() == _SAC_DCC_USER) && (GET_MZ_DCC_TYPE() == _MZ_DCC_NORMAL) && (GET_MZ_ICM_ON_OFF_TYPE() == _OFF)))
        SET_MZ_WINDOW_CFG_TYPE(_MZ_WINDOW_CFG_DISABLE);
    else
        SET_MZ_WINDOW_CFG_TYPE(_MZ_WINDOW_CFG_FULL);

    if(color == _V_RED)
    {
    	// CM0 master ---1
        CAdjustMZComboHueSat(stOsdUserData.MZICMRedHue, 255, 510, (64 - 8), (-128 + 16), (-128 + 16), (-48), 0x00); 
        // CM0 right  ---2                             //U,  V,   the maximum u v can adjust,the field to modify                                     
        CAdjustMZComboHueSat(stOsdUserData.MZICMRedHue/2 + stOsdUserData.MZICMMagentaHue, 422, 175, (64 - 8), (-128 + 16), (-64 + 8), (128 - 16), 0x10); 
        // CM0 left   ---3
        CAdjustMZComboHueSat((stOsdUserData.MZICMRedHue + stOsdUserData.MZICMYellowHue)/2, 0, 510, (128 - 16), (-48), (-128 + 16), (-48), 0x20); 
        // CM1 right  ---5
        CAdjustMZComboHueSat((stOsdUserData.MZICMRedHue + stOsdUserData.MZICMYellowHue)/2, 0, 510, (128 - 16), (-48), (-128 + 16), (-48), 0x11); 
        // CM4 left   ---15
        CAdjustMZComboHueSat(stOsdUserData.MZICMRedHue/2 + stOsdUserData.MZICMMagentaHue, 422, 175, (64 - 8), (-128 + 16), (-64 + 8), (128 - 16), 0x24);          

    }
    else if(color == _V_GREEN)
    {     
    	// CM1 left   ---6
        CAdjustMZComboHueSat((stOsdUserData.MZICMYellowHue + stOsdUserData.MZICMGreenHue)/2 , -340, 340, (64 - 8), (128 - 16), (-64 + 8), (-128 + 16), 0x21);   
        // CM2 master ---7			
	    CAdjustMZComboHueSat(stOsdUserData.MZICMGreenHue, -510, 0, (64 - 8), (128 - 16), (64 - 8), (-128 + 16), 0x02);
        // CM2 right  ---8
        CAdjustMZComboHueSat((stOsdUserData.MZICMYellowHue + stOsdUserData.MZICMGreenHue)/2 , -340, 340, (64 - 8), (128 - 16), (-64 + 8), (-128 + 16), 0x12);
        // CM2 left   ---9
        CAdjustMZComboHueSat((stOsdUserData.MZICMGreenHue + stOsdUserData.MZICMCyanHue)/2, -340, -340, (-64 + 8), (128 - 16), (64 - 8), (-128 + 16), 0x22);        
        // CM3 right  ---11          
        CAdjustMZComboHueSat((stOsdUserData.MZICMGreenHue + stOsdUserData.MZICMCyanHue)/2, -340, -340, (-64 + 8), (128 - 16), (64 - 8), (-128 + 16), 0x23);
	}
    else if(color == _V_YELLOW)
    {
    	// CM1 master ---4
        CAdjustMZComboHueSat(stOsdUserData.MZICMYellowHue, -255, 510, (128 - 16), (-48), (-64 + 8), (-128 + 16), 0x01);
        // CM1 right  ---5
        CAdjustMZComboHueSat((stOsdUserData.MZICMRedHue + stOsdUserData.MZICMYellowHue)/2, 0, 510, (128 - 16), (-48), (-128 + 16), (-48), 0x11);         
        // CM1 left   ---6
        CAdjustMZComboHueSat((stOsdUserData.MZICMYellowHue + stOsdUserData.MZICMGreenHue)/2 , -340, 340, (64 - 8), (128 - 16), (-64 + 8), (-128 + 16), 0x21);
        // CM0 left   ---3
        CAdjustMZComboHueSat((stOsdUserData.MZICMRedHue + stOsdUserData.MZICMYellowHue)/2, 0, 510, (128 - 16), (-48), (-128 + 16), (-48), 0x20); 
        // CM2 right  ---8
        CAdjustMZComboHueSat((stOsdUserData.MZICMYellowHue + stOsdUserData.MZICMGreenHue)/2 , -340, 340, (64 - 8), (128 - 16), (-64 + 8), (-128 + 16), 0x12);
    }
    else if(color == _V_CYAN)
    {
    	// CM3 master ---10
        CAdjustMZComboHueSat(stOsdUserData.MZICMCyanHue, -255, -510, (-64 + 8), (128-16), (128 - 16), (48), 0x03);
        // CM3 right  ---11
        CAdjustMZComboHueSat((stOsdUserData.MZICMGreenHue + stOsdUserData.MZICMCyanHue)/2, -340, -340, (-64 + 8), (128 - 16), (64 - 8), (-128 + 16), 0x13);
        // CM3 left   ---12
        CAdjustMZComboHueSat(stOsdUserData.MZICMCyanHue/4 + stOsdUserData.MZICMBlueHue, 255, -510, (-128 + 16), (48), (128 - 16), (48), 0x23);
        // CM2 left   ---9
        CAdjustMZComboHueSat((stOsdUserData.MZICMGreenHue + stOsdUserData.MZICMCyanHue)/2, -340, -340, (-64 + 8), (128 - 16), (64 - 8), (-128 + 16), 0x22);
	    // CM4 right  ---14
  	    CAdjustMZComboHueSat(stOsdUserData.MZICMCyanHue/4 + stOsdUserData.MZICMBlueHue, 255, -510, (-128 + 16), (48), (128 - 16), (48), 0x14);
    }
    else if(color == _V_BLUE)
    {
    	// CM3 left   ---12
        CAdjustMZComboHueSat(stOsdUserData.MZICMCyanHue/4 + stOsdUserData.MZICMBlueHue, 255, -510, (-128 + 16), (48), (128 - 16), (48), 0x23);
        // CM4 master ---13        
        CAdjustMZComboHueSat(stOsdUserData.MZICMBlueHue/2 + stOsdUserData.MZICMMagentaHue, 422, -175, (-64 + 8),(-128 + 16), (64 - 8), (128 - 16), 0x04);
        // CM4 right  ---14
	    CAdjustMZComboHueSat(stOsdUserData.MZICMCyanHue/4 + stOsdUserData.MZICMBlueHue, 255, -510, (-128 + 16), (48), (128 - 16), (48), 0x14);
	
        //CAdjustMZComboHueSat(stOsdUserData.MZICMBlueHue, 255, -510, (-128 + 16), (48), (64 - 8), (128 - 16), 0x02);
        //CAdjustMZComboHueSat(stOsdUserData.MZICMBlueHue, 139, -510, (-128 + 16), (48), (128 - 16), (48), 0x12);
        //CAdjustMZComboHueSat(stOsdUserData.MZICMBlueHue, 310, -400, (-64 + 8), (-128 + 16), (64 - 8), (128 - 16), 0x22);
        //CAdjustMZComboHueSat(0, 139, -510, 0, 0, 0, 0, 0x02);
        //CAdjustMZComboHueSat(stOsdUserData.MZICMBlueHue, 255, -510, (-128 + 16), (48), (64 - 8), (128 - 16), 0x12);
    }
    else if(color == _V_MAGENTA)
    {
    	// CM0 right  ---2
    	CAdjustMZComboHueSat(stOsdUserData.MZICMRedHue/2 + stOsdUserData.MZICMMagentaHue, 422, 175, (64 - 8), (-128 + 16), (-64 + 8), (128 - 16), 0x10); 
    	// CM4 master ---13        
        CAdjustMZComboHueSat(stOsdUserData.MZICMBlueHue/2 + stOsdUserData.MZICMMagentaHue, 422, -175, (-64 + 8),(-128 + 16), (64 - 8), (128 - 16), 0x04);
        // CM4 left   ---15
        CAdjustMZComboHueSat(stOsdUserData.MZICMRedHue/2 + stOsdUserData.MZICMMagentaHue, 422, 175, (64 - 8), (-128 + 16), (-64 + 8), (128 - 16), 0x24);
        
        //CAdjustMZComboHueSat(0, 139, -510, 0, 0, 0, 0, 0x02);
        //CAdjustMZComboHueSat(stOsdUserData.MZICMMagentaHue, 510, 0, (-64 + 8), (128 - 16), (-64 + 8), (-128 + 16), 0x22);		
    }

    if((GET_MZ_ICM_ON_OFF_TYPE() == _ON) && (GET_MZ_WINDOW_CFG_TYPE() != _MZ_WINDOW_CFG_DISABLE))
        CScalerSetBit(_ICM_CTRL_E0, ~_BIT7, _BIT7);
    else
        CScalerSetBit(_ICM_CTRL_E0, ~_BIT7, 0x00);
}

void CSetSACMode(BYTE DDCtype)
{
    SET_SAC_DCC_TYPE(DDCtype);

	if(DDCtype == _SAC_DCC_NORMAL)
    {
	    CAdjustHLWindow();
    }
	else if(DDCtype == _SAC_DCC_USER)
	{
        if(GET_MZ_ICM_ON_OFF_TYPE() == _ON)
        {
            CAdjustMZHueSat(0);
            CAdjustMZHueSat(1);
            CAdjustMZHueSat(2);
            CAdjustMZHueSat(3);
            CAdjustMZHueSat(4);
            CAdjustMZHueSat(5);
            CScalerSetBit(_ICM_CTRL_E0, ~_BIT7, 0x80);
        }
        else
		{
            CScalerSetBit(_ICM_CTRL_E0, ~_BIT7, 0x00);
        }

        if(GET_MZ_DCC_TYPE() == _MZ_DCC_NORMAL)
        {
            CScalerSetByte(_DCC_CTRL0_E4, 0x2c);
            if(GET_MZ_ICM_ON_OFF_TYPE() == _OFF)
                CAdjustHLWindow();
        }
        else
        {
            CAdjustHLWindow();
            CAdjustFillDCCTable(tDCC_CONTROL[GET_MZ_DCC_TYPE()], tDCC_USERCURVE[GET_MZ_DCC_TYPE()]);
        }
	}
	else
	{
        CAdjustFillDCCTable(tDCC_CONTROL[GET_SAC_DCC_TYPE()], tDCC_USERCURVE[GET_SAC_DCC_TYPE()]);
        CAdjustAccessICMTable(GET_SAC_DCC_TYPE());
	    CAdjustHLWindow();
	}
}
#endif // end #if (_VGA_COLOR_SUPPORT)



#endif // #if (_SCALER_TYPE == _RTD2553V || _SCALER_TYPE == _RTD2546N || _SCALER_TYPE == _RTD2525L)


#if(_SCALER_TYPE == _RTD2547D && _VGA_COLOR_SUPPORT)
// Description  : Enable Highlight Window
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CAdjustEnableHLWindow(void)
{
    CScalerSetBit(_HW_ACCESS_PORT_60, ~_BIT6, _BIT6);
    CAdjustHLWindowBrightness(stOsdUserData.MZBright);
    CAdjustHLWindowContrast(stOsdUserData.MZContrast);
    if(GET_MZ_MODE_TYPE() == _MZ_MODE_USER)
    {
        CAdjustMZHueSat(0);
        CAdjustMZHueSat(1);
        CAdjustMZHueSat(2);
        CAdjustFillDCCTable(tDCC_CONTROL[GET_MZ_DCC_TYPE()], tDCC_USERCURVE[GET_MZ_DCC_TYPE()]);
    }
    else
    {
        CAdjustFillICMTable(GET_MZ_MODE_TYPE());
        CAdjustFillDCCTable(tDCC_CONTROL[GET_MZ_MODE_TYPE()], tDCC_USERCURVE[GET_MZ_MODE_TYPE()]);
    }
}

//--------------------------------------------------
// Description  : Disable Highlight Window
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CAdjustDisableHLWindow(void)
{
    CAdjustMZHueSat(0);
    CAdjustMZHueSat(1);
    CAdjustMZHueSat(2);
    CAdjustFillDCCTable(tDCC_CONTROL[GET_MZ_DCC_TYPE()], tDCC_USERCURVE[GET_MZ_DCC_TYPE()]);
    CScalerSetBit(_HW_ACCESS_PORT_60, ~_BIT6, 0x00);
}

//--------------------------------------------------
// Description  : Adjust Highlight Window
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CAdjustHLWindow(void)
{
    if(GET_MZ_WINDOW_CFG_TYPE() == _MZ_WINDOW_CFG_DISABLE)
    {
        CAdjustDisableHLWindow();
    }
    else if(GET_MZ_WINDOW_CFG_TYPE() == _MZ_WINDOW_CFG_FULL)
    {
        CAdjustHLWindowHV(0, stDisplayInfo.DHWidth, 0, stDisplayInfo.DVHeight);
        CAdjustNormalizeFactor(stDisplayInfo.DHWidth, stDisplayInfo.DVHeight);
        CAdjustEnableHLWindow();
    }
    else if(GET_MZ_WINDOW_CFG_TYPE() == _MZ_WINDOW_CFG_DEMO)
    {
        CAdjustHLWindowHV(0, stDisplayInfo.DHWidth / 2, 0, stDisplayInfo.DVHeight);
        CAdjustNormalizeFactor(stDisplayInfo.DHWidth / 2, stDisplayInfo.DVHeight);
        CAdjustEnableHLWindow();
    }
    else if(GET_MZ_WINDOW_CFG_TYPE() == _MZ_WINDOW_CFG_WINDOW)
    {
        CAdjustHLWindowHV(stOsdUserData.MZHPos, stOsdUserData.MZHWidth, stOsdUserData.MZVPos, stOsdUserData.MZVHeight);
        CAdjustNormalizeFactor(stOsdUserData.MZHWidth, stOsdUserData.MZVHeight);
        CAdjustEnableHLWindow();
    }
}

//--------------------------------------------------
// Description  : Adjust Highlight Window Size
// Input Value  : usHPos, usHWidth, usVPos, usVHeight
// Output Value : None
//--------------------------------------------------
void CAdjustHLWindowHV(WORD usHPos, WORD usHWidth, WORD usVPos, WORD usVHeight)
{
    if(usHWidth == 0 || usVHeight == 0)
        return;

    CScalerSetBit(_HW_ACCESS_PORT_60, ~(_BIT7 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT7);

    pData[0] = ((usHPos >> 8) & 0x07);
    pData[1] = (BYTE)(usHPos);
    pData[2] = (((usHPos + usHWidth) >> 8) & 0x07);
    pData[3] = (BYTE)(usHPos + usHWidth);
    pData[4] = ((usVPos >> 8) & 0x07);
    pData[5] = (BYTE)(usVPos);
    pData[6] = (((usVPos + usVHeight) >> 8) & 0x07);
    pData[7] = (BYTE)(usVPos + usVHeight);

    CTimerWaitForEvent(_EVENT_DEN_STOP);

    CScalerWrite(_HW_DATA_PORT_61, 8, pData, _NON_AUTOINC);

    CScalerSetBit(_HW_ACCESS_PORT_60, ~(_BIT7 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
}

//--------------------------------------------------
// Description  : Adjust Brightness Value For Highlight Window
// Input Value  : ucValue
// Output Value : None
//--------------------------------------------------
void CAdjustHLWindowBrightness(BYTE ucValue)
{
    if(GET_MZ_WINDOW_CFG_TYPE() == _MZ_WINDOW_CFG_FULL)
        ucValue = 128;

    CScalerSetBit(_CB_ACCESS_PORT_64, ~(_BIT7 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | _BIT2 | _BIT1));

    pData[0] = pData[1] = pData[2] = ucValue;

    CScalerWrite(_CB_DATA_PORT_65, 3, pData, _NON_AUTOINC);

    CScalerSetByte(_CB_ACCESS_PORT_64, 0x00);
}

//--------------------------------------------------
// Description  : Adjust Contrast Value For Highlight Window
// Input Value  : ucValue
// Output Value : None
//--------------------------------------------------
void CAdjustHLWindowContrast(BYTE ucValue)
{
    if(GET_MZ_WINDOW_CFG_TYPE() == _MZ_WINDOW_CFG_FULL)
        ucValue = 128;

    CScalerSetBit(_CB_ACCESS_PORT_64, ~(_BIT7 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | _BIT3 | _BIT0));

    pData[0] = pData[1] = pData[2] = ucValue;

    CScalerWrite(_CB_DATA_PORT_65, 3, pData, _NON_AUTOINC);

    CScalerSetByte(_CB_ACCESS_PORT_64, 0x00);
}

//--------------------------------------------------
// Description  : Adjust Normalize Factor
// Input Value  : usHWidth, usVHeight)
// Output Value : None
//--------------------------------------------------
void CAdjustNormalizeFactor(WORD usHWidth, WORD usVHeight)
{
    ((DWORD *)pData)[0] = (DWORD)4194304 * 255 / usHWidth / usVHeight;

    CScalerSetBit(_DCC_CTRL0_E4, ~(_BIT1 | _BIT0), _PAGE0);

    CScalerSetByte(_DCC_ACCESS_PORT_E6, _DCC_P0_NOR_FACTOR_H_00);

    ((DWORD *)pData)[0] &= 0x3fffff;

    CScalerWrite(_DCC_DATA_PORT_E7, 3, &pData[1], _NON_AUTOINC);
}

//--------------------------------------------------
// Description    : Fill DCC table , then enable DCC function
// Input Value   : pControlTable, pUserCurveTable, both parameters accroding to Vivid color software.
// Output Value : None
//--------------------------------------------------
void CAdjustFillDCCTable(BYTE *pControlTable, BYTE *pUserCurveTable)
{
    BYTE i;
        
    // switch to page 0
    CScalerRead(_DCC_CTRL0_E4, 1, &i, _NON_AUTOINC);
    i = (i & 0xfc) | _PAGE0;   
    CScalerSetByte(_DCC_CTRL0_E4, i);      

    // fill DCC control table
    CScalerSetByte(_DCC_ACCESS_PORT_E6, 0x03);
    for (i =0; i<9; i++)
    {
        CScalerSetByte(_DCC_DATA_PORT_E7, *pControlTable);
        pControlTable++;
    }

    // switch to page 1
    CScalerRead(_DCC_CTRL0_E4, 1, &i, _NON_AUTOINC);
    i = (i & 0xfc) | _PAGE1;
    CScalerSetByte(_DCC_CTRL0_E4, i);
    
    // fill DCC user curve table
    CScalerSetByte(_DCC_ACCESS_PORT_E6, 0x00); 
    for (i=0; i<20; i++)
    {                
        CScalerSetByte(_DCC_DATA_PORT_E7, *pUserCurveTable);
        pUserCurveTable++;
    }

    // enable DCC func when _EVENT_DEN_STOP
    CTimerWaitForEvent(_EVENT_DEN_STOP);

    if(((GET_MZ_DCC_TYPE() == _MZ_DCC_NORMAL) && (GET_MZ_MODE_TYPE() == _MZ_MODE_USER)) || (GET_MZ_WINDOW_CFG_TYPE() == _MZ_WINDOW_CFG_DISABLE))
    {
        CScalerSetByte(_DCC_CTRL0_E4, 0x2c);
    }
    else
    {
        CScalerSetByte(_DCC_CTRL0_E4, 0xac);
    }

    CScalerSetByte(_DCC_CTRL1_E5, 0x80);
}

BYTE code SatPlus[8]  = { 41, 44, 43, 39, 31, 22, 11, 0 }; // by 1/256
BYTE code SatMinus[8] = { 24, 35, 40, 41, 36, 28, 16, 0 }; // by 1/256

int CAdjustColorGammaCal(BYTE color, BYTE n) // n = 1~8
{
    int temp = (color == 0) ? stOsdUserData.MZICMRedSat : (color == 1) ? stOsdUserData.MZICMGreenSat : stOsdUserData.MZICMBlueSat;

    temp *= 2;

    if (temp >= 16)
    {
        return ((int)(512*n) + (int)((temp-16)*(int)SatPlus[n-1])) / 64 ;
    }
    else
    {
        return ((int)(512*n) - (int)((16-temp)*(int)SatMinus[n-1])) / 64 ;
    }
}

void CAdjustHueSatSet(BYTE color, SWORD TempU1, SWORD TempU2, SWORD TempV1, SWORD TempV2)
{
    BYTE i;
    SWORD u,v;

    CScalerSetByte(_ICM_SEL_E1,(color & 0x0f));
    CScalerSetByte(_ICM_ACCESS_PORT_E2,0x00);

    if((color & 0x0f) == 0)
    {
        CScalerSetByte(_ICM_DATA_PORT_E3,0x02);
        CScalerSetByte(_ICM_DATA_PORT_E3,0xd2);
        CScalerSetByte(_ICM_DATA_PORT_E3,0xee);
    }
    else if((color & 0x0f) == 1)
    {
        CScalerSetByte(_ICM_DATA_PORT_E3,0x08);
        CScalerSetByte(_ICM_DATA_PORT_E3,0x00);
        CScalerSetByte(_ICM_DATA_PORT_E3,0xee);
    }
    else if((color & 0x0f) == 2)
    {
        CScalerSetByte(_ICM_DATA_PORT_E3,0x0d);
        CScalerSetByte(_ICM_DATA_PORT_E3,0x2e);
        CScalerSetByte(_ICM_DATA_PORT_E3,0xbe);
    }

    
    CScalerSetByte(_ICM_SEL_E1,(color & 0x0f));
    CScalerSetByte(_ICM_ACCESS_PORT_E2,((color & 0xf0)+0x03));	

    for(i=1; i<9; i++)
    {
        u = ((TempU1+TempU2)*CAdjustColorGammaCal(color, i)/64) - ((TempU1*i)/8);
        v = ((TempV1+TempV2)*CAdjustColorGammaCal(color, i)/64) - ((TempV1*i)/8);

        CScalerSetByte(_ICM_DATA_PORT_E3,u);
        CScalerSetByte(_ICM_DATA_PORT_E3,v);
    }
	/*
    for(i=1; i<33; i++)
    {
        CScalerSetByte(0xe3,0x00);
    }
*/
    CScalerSetByte(_ICM_CTRL_E0,0xdc);
}

void CAdjustMZComboHueSat(BYTE ucVar, SWORD sTempU1, SWORD sTempV1, SWORD sConst0, SWORD sConst1, SWORD sConst2, SWORD sConst3, BYTE ucPar)
{
    SWORD sTempU2, sTempV2;

    if(ucVar < 8)
    {
        sTempU2 = (SWORD)(sConst0) * (8 - ucVar) / 8;
        sTempV2 = (SWORD)(sConst1) * (8 - ucVar) / 8;
    }
    else
    {
        sTempU2 = (SWORD)(sConst2) * (ucVar - 8) / 8;
        sTempV2 = (SWORD)(sConst3) * (ucVar - 8) / 8;
    }

    CAdjustHueSatSet(ucPar, sTempU1, sTempU2, sTempV1, sTempV2);
}

void CAdjustMZHueSat(BYTE color)
{
    if(color == 0)
    {
        CAdjustMZComboHueSat(stOsdUserData.MZICMRedHue, 255, 510, (64 - 8), (-128 + 16), (-128 + 16), (-48), 0x00);

        CAdjustMZComboHueSat(stOsdUserData.MZICMRedHue, 437, 146, (64 - 8), (-128 + 16), (-64 + 8), (128 - 16), 0x10);

        CAdjustMZComboHueSat(stOsdUserData.MZICMRedHue, -170, 510, (128 - 16), (-48), (-128 + 16), (-48), 0x20);

	}
    else if(color == 1)
    {
        CAdjustMZComboHueSat(stOsdUserData.MZICMGreenHue, -510, 0, (64 - 8), (128 - 16), (64 - 8), (-128 + 16), 0x01);

        CAdjustMZComboHueSat(stOsdUserData.MZICMGreenHue, -340, 340, (64 - 8), (128 - 16), (-64 + 8), (-128 + 16), 0x11);

        CAdjustMZComboHueSat(stOsdUserData.MZICMGreenHue, -340, -340, (-64 + 8), (128 - 16), (64 - 8), (-128 + 16), 0x21);

	}
    else if(color == 2)
    {
        CAdjustMZComboHueSat(stOsdUserData.MZICMBlueHue, 255, -510, (-128 + 16), (48), (64 - 8), (128 - 16), 0x02);

        CAdjustMZComboHueSat(stOsdUserData.MZICMBlueHue, -170, -510, (-128 + 16), (48), (128 - 16), (48), 0x12);

        CAdjustMZComboHueSat(stOsdUserData.MZICMBlueHue, 355, -310, (-64 + 8), (-128 + 16), (64 - 8), (128 - 16), 0x22);
	}

    if((GET_MZ_ICM_ON_OFF_TYPE() == _ON) && (GET_MZ_WINDOW_CFG_TYPE() != _MZ_WINDOW_CFG_DISABLE))
        CScalerSetBit(_ICM_CTRL_E0, ~_BIT7, _BIT7);
    else
        CScalerSetBit(_ICM_CTRL_E0, ~_BIT7, 0x00);
}

//--------------------------------------------------
// Description      : Fill ICM table , then enable ICM function
// Input Value      : None
// Output Value     : None
//--------------------------------------------------
void CAdjustFillICMTable(BYTE ucNum)
{
    BYTE i=0;

    for (i=0; i<4; i++)
    {            
        CScalerSetByte(_ICM_SEL_E1, (0x00 + i));
        CScalerSetByte(_ICM_ACCESS_PORT_E2, 0x00);
        CScalerWrite(_ICM_DATA_PORT_E3, 51, tICM_TABLE[ucNum * 4 + i], _NON_AUTOINC);
    }

    if(ucNum == _MZ_MODE_MOVIE)
        CScalerSetByte(_ICM_CTRL_E0, 0xde);
    if(ucNum == _MZ_MODE_TEXT)
        CScalerSetByte(_ICM_CTRL_E0, 0xc0);
    if(ucNum == _MZ_MODE_PHOTO)
        CScalerSetByte(_ICM_CTRL_E0, 0xdc);
}

#if (_OD_SUPPORT == _ON)
//--------------------------------------------------
// Description  : 
// Input Value  : OD Delta Gain = ucValue/64
// Output Value : 
//--------------------------------------------------
void CAdjustODeltaGain(BYTE ucValue)
{
    CScalerPageSelect(_PAGE3);
    CScalerSetByte(_P3_LS_DELTA_GAIN_B1, (ucValue & 0x7F));
}
#endif  //End if #if (_OD_SUPPORT == _ON)

#endif  // #if(_SCALER_TYPE == _RTD2547D && _VGA_COLOR_SUPPORT)



#if(_VIDEO_VIVID_COLOR_SUPPORT)
//============================================================================== 
static BYTE code TDCC_Control1[] =
{
	0x00,  0x03,  0x30, // Do not modify these three bytes
	0x84,  0x66,  0xc3,
	0x7c,  0xce,  0x1e,
	0x10,  0x10,  0x14,
};

static BYTE code TDCC_UserCurve1[] =
{
	0x05,  0x10,  0x1f,  0x30,
	0x43,  0x57,  0x6d,  0x80,
	0x95,  0xa9,  0xbd,  0xce,
	0xe0,  0xed,  0xf7,  0x10,  0x00,
	0x80,  0x14,  0x34,
};

static BYTE code TDCC_Control2[] =	// sony mode
{
	0x00,  0x03,  0x30,
	0x84,  0x66,  0xc3,
	0x00,  0xe6,  0x1e,  
	0x10,  0x00,  0xff,

/*
	0x00,  0x03,  0x30,
	0x84,  0x66,  0xc3,
	0x5c,  0xce,  0x1e,
	0x10,  0x10,  0x14,
*/	
};

static BYTE code TDCC_UserCurve2[] =	// sony mode
{
	0x0c,  0x1a,  0x2c,  0x40,  
	0x50,  0x60,  0x70,  0x80,  
	0x90,  0xa0,  0xb0,  0xc0,  
	0xd0,  0xe0,  0xf0,  0x10,  0x00,
	0x50,  0x14,  0x34,
/*
	0x0e,  0x1d,  0x2d,  0x3d,
	0x4d,  0x5d,  0x6d,  0x7d,
	0x8e,  0x9d,  0xad,  0xbc,
	0xca,  0xdb,  0xeb,  0x10,  0x00,
	0x41,  0x14,  0x34,
*/	
};

static BYTE code TDCC_Control3[] =
{
	0x00,  0x03,  0x30,
	0x84,  0x66,  0xc3,
	0x7c,  0xce,  0x1e,
	0x10,  0x10,  0x14,
};


static BYTE code TDCC_UserCurve3[] =
{
	0x0f,  0x1d,  0x2d,  0x3e,
	0x4b,  0x5c,  0x6d,  0x80,
	0x91,  0xa2,  0xb3,  0xc4,
	0xd4,  0xe3,  0xf2,  0x10,  0x00,
	0x5d,  0x14,  0x30,
};


static BYTE code TDCC_Control4[] =
{
	0x00,  0x03,  0x30,
	0x84,  0x66,  0xc3,
	0x64,  0xce,  0x1e,
	0x10,  0x10,  0x14,
};

static BYTE code TDCC_UserCurve4[] =
{
	0x18,  0x2c,  0x3f,  0x50,
	0x61,  0x73,  0x85,  0x99,
	0xad,  0xc0,  0xd2,  0xe0,
	0xeb,  0xf5,  0xfc,  0x10,  0x00,
	0x64,  0x14,  0x3a,
};

code BYTE *TDCC_Control12[4] =
{
	TDCC_Control2, TDCC_Control3, TDCC_Control1, TDCC_Control4
};

code BYTE  *TDCC_UserCurve12[4] =
{
	TDCC_UserCurve2, TDCC_UserCurve3, TDCC_UserCurve1, TDCC_UserCurve4
};

void CAccAdjustVividColorForVideo(BYTE mode)
{
	BYTE *DCCContol,*DCCCurve;
	BYTE i,j;
  

	switch (mode) {
		case  0:		// disable DCC and ICM
			CScalerSetByte(_DCC_CTRL0_E4, 0x00);  //disable dcc, page0
			CScalerSetByte(_DCC_CTRL1_E5, 0x00);  //disable
			//CScalerSetByte(_ICM_CTRL_E0, 0x00);  //disable icm
			return;
			//break;

		case 1:
			DCCContol = TDCC_Control12[0];
			DCCCurve =  TDCC_UserCurve12[0];
			break;
		case 2:
			DCCContol = TDCC_Control12[1];
			DCCCurve =  TDCC_UserCurve12[1];
			break;
		case 3:
			DCCContol = TDCC_Control12[2];
			DCCCurve =  TDCC_UserCurve12[2];
			break;
		case 4:
			DCCContol = TDCC_Control12[3];
			DCCCurve =  TDCC_UserCurve12[3];
			break;

		default :
			break;
	}

	CScalerRead(_DCC_CTRL0_E4, 1, &i, _NON_AUTOINC);
	i = i & 0xfc;
	CScalerRead(_DCC_CTRL1_E5, 1, &j, _NON_AUTOINC);
	CScalerSetByte(_DCC_CTRL0_E4, i);
	CScalerSetByte(_DCC_CTRL1_E5, j);

	CScalerSetByte(_DCC_ACCESS_PORT_E6, 0x00);
	for (i=0; i<12; i++) {
		CScalerSetByte(_DCC_DATA_PORT_E7, *DCCContol );
		DCCContol++;
	}

	CScalerRead(_DCC_CTRL0_E4, 1, &i, _NON_AUTOINC);
	i = (i & 0xfc) | 0x01;
	CScalerSetByte(_DCC_CTRL0_E4, i);

	CScalerSetByte(_DCC_ACCESS_PORT_E6, 0x00);
	for (i=0; i<20; i++) {
		CScalerSetByte(_DCC_DATA_PORT_E7, *DCCCurve);
		DCCCurve++;
	}

	CTimerWaitForEvent(_EVENT_DEN_STOP);
	CScalerSetByte(_DCC_CTRL0_E4, 0xac);  //enable dcc
	//CScalerSetByte(_DCC_CTRL1_E5, 0x80);
	CScalerSetByte(_DCC_CTRL1_E5, 0x00);

	CScalerSetByte(_HW_ACCESS_PORT_60, 0x00);         // disable Hightlight Window
} 
            
void CAdjustPeakingFilterForVideo(SBYTE ucPeaking)
{
#if(_SCALER_TYPE == _RTD2547D)
	BYTE code PeakingCoeff[][3] =
	{
		//Peaking_Coef0,  Peaking_Coef1,  Peaking_Coef2,  Coring_Min,  Coring_Max_Pos,  Coring_Max_Neg ,

		//level=1 :
		0x08, 0x00, 0xFC, 0x00, 0x28, 0xF8,
		//level=2 :
		0x0C, 0x00, 0xFA, 0x00, 0x28, 0xF8,
		//level=3 :
		0x10, 0x00, 0xF8, 0x00, 0x28, 0xF8,
		//level=4 :
	     	0x18, 0x00, 0xF4, 0x00, 0x28, 0xF8,	//3
		//level=5 :
		0x20, 0x00, 0xF0, 0x00, 0x28, 0xF8,
		//level=6 :
		0x28, 0x00, 0xEC, 0x00, 0x28, 0xF8,
		//level=7 :
		0x30, 0x00, 0xE8, 0x00, 0x28, 0xF8,
		//level=8 :
		0x38, 0x00, 0xE4, 0x00, 0x28, 0xF8,
		//level=9 :
		0x40, 0x00, 0xE0, 0x00, 0x28, 0xF8,
		//level=10 :
		0x46, 0x00, 0xDD, 0x00, 0x28, 0xF8,
		//level=11 :
		0x4E, 0x00, 0xD9, 0x00, 0x28, 0xF8,
		//level=12 :
		0x56, 0x00, 0xD5, 0x00, 0x28, 0xF8,
		//level=13 :
		0x5E, 0x00, 0xD1, 0x00, 0x28, 0xF8,
		//level=14 :
		0x66, 0x00, 0xCD, 0x00, 0x28, 0xF8,
		//level=15 :
		0x6E, 0x00, 0xC9, 0x00, 0x28, 0xF8,
		//level=16 :
		0x76, 0x00, 0xC5, 0x00, 0x28, 0xF8,
   };
#else
	BYTE code PeakingCoeff[][3] =
	{
		0x08,    2,    0xFa, //0
	 	0x10,    2,    0xF6,//1                  
		0x18,    2,    0xF2,//2   
		0x20,    4,    0xec,//3
		0x28,    4,    0xE8,//4
		0x30,    4,    0xE4, //5
		0x38,    5,    0xdf, //6
		0x40,    5,    0xdb,//7
		0x46,    5,    0xD9,//8
		0x4E,    5,    0xD4,//9
		0x56,    5,    0xD0,//10
		0x5E,    6,    0xcb,//11
		0x66,    6,    0xC7,//12
		0x6E,    6,    0xC2,//13
		0x76,    6,    0xbf,//14
		0x7E,    6,    0xbb,//15
	};
#endif

	BYTE Peaking = ucPeaking%16;                                          

	if((_GET_INPUT_SOURCE()==_SOURCE_VGA) || (_GET_INPUT_SOURCE()==_SOURCE_DVI) || (_GET_INPUT_SOURCE()==_SOURCE_HDMI))
    {
    			
#if(_SCALER_TYPE == _RTD2547D)
		    CScalerSetByte(_PC_ACCESS_PORT_9A, 0x00);
#else
		    CScalerSetByte(_PC_ACCESS_PORT_26, 0x00);
#endif
			return;
	}
    else
    {		
	
#if(_SCALER_TYPE == _RTD2547D)
		pData[0] = PeakingCoeff[ucPeaking][0];
		pData[1] = PeakingCoeff[ucPeaking][1];// PeakingCoeff[ucPeaking][2]
		pData[2] = PeakingCoeff[ucPeaking][2];// PeakingCoeff[ucPeaking][1]
	    pData[3] = PeakingCoeff[ucPeaking][3];
		pData[4] = PeakingCoeff[ucPeaking][4];
    	pData[5] = PeakingCoeff[ucPeaking][5];

    	CScalerSetByte(_PC_ACCESS_PORT_9A, 0x80);
    	CScalerWrite(_PC_DATA_PORT_9B, 6, pData, _NON_AUTOINC);
    	CScalerSetByte(_PC_ACCESS_PORT_9A, 0x40);
#else
		pData[0] = PeakingCoeff[ucPeaking][0];
		pData[1] = PeakingCoeff[ucPeaking][1];// PeakingCoeff[ucPeaking][2]
		pData[2] = PeakingCoeff[ucPeaking][2];// PeakingCoeff[ucPeaking][1]
	    pData[3] = 0x12;	//
		pData[4] = 0x80;	//(¢DOAa)
    	pData[5] = 0xF8;	//(?AAa)

    	CScalerSetByte(_PC_ACCESS_PORT_26, 0x80);
    	CScalerWrite(_PC_DATA_PORT_27, 6, pData, _NON_AUTOINC);
    	CScalerSetByte(_PC_ACCESS_PORT_26, 0x40);
#endif

	}	

}      
#endif  // #if(_VIDEO_VIVID_COLOR_SUPPORT)
