//----------------------------------------------------------------------------------------------------
// ID Code      : Mode.c No.0004
// Update Note  : 
//
//----------------------------------------------------------------------------------------------------

#include "Header\Include.h"



//----------------------------------------------------------------------------------------------------
// Measure Functions
//----------------------------------------------------------------------------------------------------
       /*
//--------------------------------------------------
// Description  : Get measure data and convert into system information
// Input Value  : None
// Output Value : Return _TRUE if success, _FALSE if the measurement result is wrong
//--------------------------------------------------
bit CModeMeasureData(void)
{

    // Read measurement status bit
    CScalerRead(_MEAS_HS_PERIOD_H_52, 3, &pData[8], _AUTOINC);

    if((bit)(pData[8] & _BIT4) || (bit)(pData[10] & _BIT4) || (bit)(pData[10] & _BIT5))
        return _FALSE;

    CScalerSetBit(_MEAS_HS_PERIOD_H_52, ~_BIT6, _BIT6);

#if((_SCALER_TYPE == _RTD2553V) || (_SCALER_TYPE == _RTD2546N)) 

    CScalerRead(_MEAS_HS_PERIOD_H_52, 7, &pData[8], _AUTOINC);
    // Calculate measurement result
    ((WORD *)pData)[0] = ((pData[8] & 0x1f) << 8) | pData[9];
    ((WORD *)pData)[1] = ((pData[10] & 0x1f) << 8) | pData[11];
    ((WORD *)pData)[2] = ((pData[12] & 0x0f) << 8) | pData[13];
    ((WORD *)pData)[3] = ((pData[12] & 0xf0) << 4) | pData[14];

#elif(_SCALER_TYPE == _RTD2525L)

    CScalerSetBit(_MEAS_VS_HIGH_PERIOD_L_58, ~_BIT0, 0x00); //V305 modify 
    CScalerRead(_MEAS_HS_PERIOD_H_52, 6, &pData[8], _AUTOINC);
    // Calculate measurement result
    ((WORD *)pData)[0] = ((pData[8] & 0x1f) << 8) | pData[9]; //V305 modify 
    ((WORD *)pData)[1] = ((pData[10] & 0x1f) << 8) | pData[11]; //V305 modify 
    ((WORD *)pData)[2] = ((pData[12] & 0xf0) << 4) | pData[13]; //V305 modify 

#else

    // Pop up measurement result
    CScalerRead(_MEAS_HS_PERIOD_H_52, 7, &pData[8], _AUTOINC);

    // Calculate measurement result
    ((WORD *)pData)[0] = ((pData[8] & 0x1f) << 8) | pData[9];
    ((WORD *)pData)[1] = ((pData[10] & 0x1f) << 8) | pData[11];
    ((WORD *)pData)[2] = ((pData[12] & 0x0f) << 8) | pData[13];
    ((WORD *)pData)[3] = ((pData[12] & 0xf0) << 4) | pData[14];

#endif  // End of #if((_SCALER_TYPE == _RTD2553V) || (_SCALER_TYPE == _RTD2546N))


    if((((WORD *)pData)[0] >=  0x07ff) || (((WORD *)pData)[1] >= 0x07ff) || (((WORD *)pData)[0] == 0) || (((WORD *)pData)[1] == 0))
    {
        // The measurement result is out of range
        return _FALSE;
    }
    else
    {
        // Store measurement results in global system variable
        stModeInfo.Polarity = (pData[10] & 0xc0) >> 6;
        stModeInfo.IHCount = ((WORD *)pData)[0];
        stModeInfo.IHFreq = (WORD)((DWORD)_RTD_XTAL * 10 * 2 / stModeInfo.IHCount);
        stModeInfo.IHFreq = (stModeInfo.IHFreq >> 1) + (stModeInfo.IHFreq & 0x01);
        stModeInfo.IVTotal = ((WORD *)pData)[1];
        stModeInfo.IVFreq = (WORD)((DWORD)(stModeInfo.IHFreq) * 1000 * 2 / stModeInfo.IVTotal);
        stModeInfo.IVFreq = (stModeInfo.IVFreq >> 1) + (stModeInfo.IVFreq & 0x01);
        stModeInfo.IHSyncPulseCount = ((WORD *)pData)[2];

        return _TRUE;
    }
}         */

//----------------------------------------------------------------------------------------------------
// Mode Display Functions
//----------------------------------------------------------------------------------------------------

//--------------------------------------------------
// Description  : Setup other setings for display
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CModeSetupEtcs(BYTE ucPar)
{
    CMiscEnableDoubleBuffer();


    //    if((bit)CScalerGetBit(_VDISP_CTRL_28, _BIT3))
             CScalerSetBit(_VDISP_CTRL_28, ~_BIT3, _BIT3);

#if(_SCALER_TYPE == _RTD2525L)
    CAdjustDigitalFilter(_PHASE_ACCESS_PORT, _PHASE_THD_0, _DIV_VALUE_1, ucPar);
#else
    CAdjustDigitalFilter(_PHASE_ACCESS_PORT, _PHASE_THD_0, _DIV_VALUE_2, ucPar);
#endif

#if(_SCALER_TYPE != _RTD2547D)
    CAdjustDigitalFilter(_YPBPR_ACCESS_PORT, _YPBPR_ENABLE, _DIV_VALUE_0, ucPar);
#endif

#if (_SCALER_TYPE == _RTD2553V || _SCALER_TYPE == _RTD2546N || _SCALER_TYPE == _RTD2525L || _SCALER_TYPE == _RTD2547D)
    CAdjustDigitalFilter(_NEG_SMEAR_ACCESS_PORT, _SMEAR_RING_THD_4, _DIV_VALUE_1, ucPar); //KEN 2005/09/23
#endif
    CAdjustDigitalFilter(_MISMATCH_ACCESS_PORT, _MISMATCH_THD_0, _DIV_VALUE_0, ucPar);

#if(_SCALER_TYPE == _RTD2547D)
    CAdjustDigitalFilter(_NOISE_REDUCTION_PORT, _NOISE_REDUCTION_THD_7, _DIV_VALUE_0, ucPar);
    CAdjustDigitalFilter(_YPBPR_ACCESS_PORT, _YPBPR_ENABLE, _DIV_VALUE_0, ucPar);
#endif

    CMiscClearStatusRegister();
}

//--------------------------------------------------
// Description  : Startup settings for VGA
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CModeStartUpVGA(void)
{
    WORD pixelclock;

       /*
#if (_SCALER_TYPE == _RTD2525L)
    CScalerSetByte(_ADC_ACCESS_PORT_DC,0x8e); //V304 modify
    CScalerSetByte(_ADC_DATA_PORT_DD,0x00); //V304 modify
#endif   */

#if(_SCALER_TYPE == _RTD2547D)

    CScalerPageSelect(_PAGE2);
    CScalerSetBit(_P2_POWER_ON_OFF_CTRL_A7, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00); //V304 modify bit4 and V307 modify bit3~bit0
    CScalerSetBit(_P2_Z0_CALIBRATION_CTRL_AC, ~_BIT6, 0x00); //V307 modify
    
    // To imporve the FIFO efficiency only when input data rate is slow, and display data rate is high.
    CScalerSetBit(_VGIP_CTRL_10, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);

#else

    CScalerSetBit(_POWER_ON_OFF_CTRL_C2, ~_BIT5, 0x00); //V304 modify
    CScalerSetBit(_POWER_ON_OFF_CTRL_C2, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1), 0x00); //V307 modify
    CScalerSetBit(_Z0_CALIBRATION_CTRL_C7, ~_BIT6, 0x00); //V307 modify

    CScalerSetBit(_VGIP_CTRL_05, ~(_BIT3 | _BIT2 | _BIT0), _BIT0);
#endif 

    // Calculate pixel clock rate (round to MHz)
    pixelclock  = (((DWORD)stModeInfo.IHFreq * (DWORD)stModeInfo.IHTotal) * 2 / (1000 * 10));
    pixelclock  = (pixelclock >> 1) + (pixelclock & 0x01);
 
#if(_SCALER_TYPE == _RTD2547D)

    // ADC differential mode and Set ADC bandwidth to reduce high frequency noise 
    CScalerPageSelect(_PAGE0);
    if(pixelclock < 38)
        CScalerSetBit(_P0_ADC_CTRL_A1, ~(_BIT2 | _BIT1 | _BIT0), _BIT2);                    //75MHz
    else if(pixelclock < 68)
        CScalerSetBit(_P0_ADC_CTRL_A1, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT0));          //150MHz
    else if(pixelclock < 160)
        CScalerSetBit(_P0_ADC_CTRL_A1, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1));          //300MHz
    else
        CScalerSetBit(_P0_ADC_CTRL_A1, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));  //500MHz

    CScalerPageSelect(_PAGE1);
    // Phase interpolation control load modified.   Marvin 0812
    if(pixelclock < 50)
        CScalerSetBit(_P1_PLL2_PHASE_INTERPOLATION_B6, ~(_BIT7 | _BIT6), 0x00);
    else
        CScalerSetBit(_P1_PLL2_PHASE_INTERPOLATION_B6, ~(_BIT7 | _BIT6), _BIT6);

    // Fine-tune R/G/B delay and enable the ADC frame-modulation
    CScalerPageSelect(_PAGE0);
	CScalerSetByte(_P0_ADC_RED_CTL_A2, 0x40 | (_ADC_FINE_TUNE_DELAY_RED & 0x07));
	CScalerSetByte(_P0_ADC_GREEN_CTL_A3, 0x40 | (_ADC_FINE_TUNE_DELAY_GREEN & 0x07));
	CScalerSetByte(_P0_ADC_BLUE_CTL_A4, 0x40 | (_ADC_FINE_TUNE_DELAY_BLUE & 0x07));

	CScalerSetByte(_P0_ADC_V_BAIS1_B2, 0x0d);
    CScalerSetByte(_YUV2RGB_CTRL_9C, 0x00);

    // HSYNC positive/negtive tracking
    CScalerPageSelect(_PAGE1);
    CScalerSetBit(_P1_PLL_DIV_CTRL_A1, ~_BIT6, 0x00);

#else
    // To imporve the FIFO efficiency only when input data rate is slow, and display data rate is high.
    CScalerSetBit(_VGIP_CTRL_05, ~(_BIT3 | _BIT2 | _BIT1), 0x00);

    // ADC differential mode and Set ADC bandwidth to reduce high frequency noise 
#if (_SCALER_TYPE == _RTD2553V || _SCALER_TYPE == _RTD2546N || _SCALER_TYPE == _RTD2525L)
/*             Realtek
    if(pixelclock < 38)
        CScalerSetDataPortBit(_ADC_ACCESS_PORT_DC, 0x00, ~(_BIT2 | _BIT1 | _BIT0), _BIT2);                    //75MHz
    else if(pixelclock < 68)
        CScalerSetDataPortBit(_ADC_ACCESS_PORT_DC, 0x00, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT0));          //150MHz
    else if(pixelclock < 160)
        CScalerSetDataPortBit(_ADC_ACCESS_PORT_DC, 0x00, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1));          //300MHz
    else
        CScalerSetDataPortBit(_ADC_ACCESS_PORT_DC, 0x00, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));  //500MHz
*/
    if(pixelclock < 38)
        CScalerSetDataPortBit(_ADC_ACCESS_PORT_DC, 0x00, ~(_BIT1 | _BIT0), 0x00);
    else if(pixelclock < 68)
        CScalerSetDataPortBit(_ADC_ACCESS_PORT_DC, 0x00, ~(_BIT1 | _BIT0), (_BIT0));
    else if(pixelclock < 160)
        CScalerSetDataPortBit(_ADC_ACCESS_PORT_DC, 0x00, ~(_BIT1 | _BIT0), (_BIT1));          //300MHz
    else
        CScalerSetDataPortBit(_ADC_ACCESS_PORT_DC, 0x00, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));  //500MHz
        
#else
    if(pixelclock < 34)
        CScalerSetBit(_ADC_RGB_CTRL_DC, ~(_BIT1 | _BIT0), 0x00);
    else if(pixelclock < 68)
        CScalerSetBit(_ADC_RGB_CTRL_DC, ~(_BIT1 | _BIT0), (_BIT0));
    else if(pixelclock < 160)
        CScalerSetBit(_ADC_RGB_CTRL_DC, ~(_BIT1 | _BIT0), (_BIT1));             //300MHz
    else
        CScalerSetBit(_ADC_RGB_CTRL_DC, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));     //500MHz
#endif
 
    // Phase interpolation control load modified.   Marvin 0812
    if(pixelclock < 50)
        CScalerSetBit(_PLL2_PHASE_INTERPOLATION_AD, ~(_BIT7 | _BIT6), 0x00);
    else
        CScalerSetBit(_PLL2_PHASE_INTERPOLATION_AD, ~(_BIT7 | _BIT6), _BIT6);
 
    // Fine-tune R/G/B delay and enable the ADC frame-modulation
#if (_SCALER_TYPE == _RTD2553V || _SCALER_TYPE == _RTD2546N || _SCALER_TYPE == _RTD2525L)
	CScalerSetDataPortByte(_ADC_ACCESS_PORT_DC, 0x01, 0x40 | (_ADC_FINE_TUNE_DELAY_RED & 0x07));
#if(_SCALER_TYPE == _RTD2525L)  
	CScalerSetDataPortByte(_ADC_ACCESS_PORT_DC, 0x02, 0x20 | (_ADC_FINE_TUNE_DELAY_GREEN & 0x07));
#else
	CScalerSetDataPortByte(_ADC_ACCESS_PORT_DC, 0x02, 0x40 | (_ADC_FINE_TUNE_DELAY_GREEN & 0x07));
#endif
	CScalerSetDataPortByte(_ADC_ACCESS_PORT_DC, 0x03, 0x40 | (_ADC_FINE_TUNE_DELAY_BLUE & 0x07));

	CScalerSetDataPortByte(_ADC_ACCESS_PORT_DC, 0x11, 0x0d);
#else
    CScalerSetByte(_ADC_RED_CTRL_DD, 0x40 | (_ADC_FINE_TUNE_DELAY_RED & 0x07));
    CScalerSetByte(_ADC_GRN_CTRL_DE, 0x40 | (_ADC_FINE_TUNE_DELAY_GREEN & 0x07));
    CScalerSetByte(_ADC_BLU_CTRL_DF, 0x40 | (_ADC_FINE_TUNE_DELAY_BLUE & 0x07));
    CScalerSetByte(_ADC_VBIAS1_ED, 0x0d);
#endif
    CScalerSetByte(_YUV2RGB_CTRL_89, 0x00);

    // HSYNC positive/negtive tracking
    CScalerSetBit(_PLL_DIV_CTRL_98, ~_BIT6, 0x00);

#endif // #if(_SCALER_TYPE == _RTD2547D)
}

//--------------------------------------------------
// Description  : Set scaling factor settings
// Input Value  : Scaling information
// Output Value : None
//--------------------------------------------------
void CModeSetScaling(BYTE ucOption)
{
#if(_SCALER_TYPE == _RTD2547D)

  #if(_FIELD_MERGE_SUPPORT == _ON)
    if(GET_FIELDMERGE_MODE())
        stModeInfo.IVHeight = stModeInfo.IVHeight * 2;
  #endif

#endif

    // Set window size before scale up
    if(ucOption & _BIT3)
    {
        // H scale-down
        pData[0] = (BYTE)((stDisplayInfo.DHWidth >> 4) & 0x70);
        pData[1] = LOBYTE(stDisplayInfo.DHWidth);
    }
    else
    {
        // No H scale-down
        pData[0] = (BYTE)((stModeInfo.IHWidth >> 4) & 0x70);
        pData[1] = LOBYTE(stModeInfo.IHWidth);
    }

    if(ucOption & _BIT1)
    {
        // V scale-down
        pData[0] = pData[0] | (HIBYTE(stDisplayInfo.DVHeight) & 0x07);
        pData[2] = LOBYTE(stDisplayInfo.DVHeight);
    }
    else
    {
        // No V scale-down
        pData[0] = pData[0] | (HIBYTE(stModeInfo.IVHeight) & 0x07);
        pData[2] = LOBYTE(stModeInfo.IVHeight);
    }

#if(_SCALER_TYPE != _RTD2547D)
    CScalerWrite(_DWRWL_H_BSU_14, 3, pData, _AUTOINC);
#endif

#if (_SCALER_TYPE == _RTD2553V || _SCALER_TYPE == _RTD2546N || _SCALER_TYPE == _RTD2525L)
    // Set FIFO Frequency (For RTD2553V)
    CScalerSetByte(_FIFO_FREQUENCY_22, 0x00);
#endif

#if(_SCALER_TYPE == _RTD2547D)
   
    CScalerSetByte(_FIFO_ACCESS_PORT_30, _FIFO_DWRWL_H_BSU_00);
    CScalerWrite(_FIFO_DATA_PORT_31, 3, pData, _NON_AUTOINC);

  #if(_FRC_SUPPORT == _ON)
    ((WORD *)pData)[2] = ((pData[0] & 0x70) << 4) | pData[1];
    ((WORD *)pData)[3] = ((pData[0] & 0x07) << 8) | pData[2];

    if(GET_FRCTATUS())
    {
  #if(_FIELD_MERGE_SUPPORT == _ON)
        if(GET_FIELDMERGE_MODE())
        {
            CMemoryControlForFRC(((WORD *)pData)[2], ((WORD *)pData)[3] / 2);
        }
        else
        CMemoryControlForFRC(((WORD *)pData)[2], ((WORD *)pData)[3]);
  #else
        CMemoryControlForFRC(((WORD *)pData)[2], ((WORD *)pData)[3]);
  #endif // #if(_FIELD_MERGE_SUPPORT == _ON)
    }
    else
    {
        CScalerPageSelect(_PAGE5);
        CScalerSetByte(_P5_SDRF_MN_PRERD_VST_H_BC, 0x00);
        CScalerSetByte(_P5_SDRF_MN_PRERD_VST_L_BD, 0x00);
    }
  #endif  // #if(_FRC_SUPPORT == _ON)

#endif //    #if(_SCALER_TYPE == _RTD2547D)

    // Write coefficient for sharpness
    CAdjustSharpness();

    // Config scaling
#if (_SCALER_TYPE == _RTD2553V || _SCALER_TYPE == _RTD2546N || _SCALER_TYPE == _RTD2525L || _SCALER_TYPE == _RTD2547D)
    if(ucOption & _BIT1)
        CScalerSetBit(_SCALE_DOWN_CTRL_23, ~_BIT0, _BIT0);          // Turn on V scale-down
    else
        CScalerSetBit(_SCALE_DOWN_CTRL_23, ~_BIT0, 0x00);           // Turn off V scale-down

    if(ucOption & _BIT3)
        CScalerSetBit(_SCALE_DOWN_CTRL_23, ~_BIT1, _BIT1);          // Turn on H scale-down
    else
        CScalerSetBit(_SCALE_DOWN_CTRL_23, ~_BIT1, 0x00);           // Turn off H scale-down
#else
    if(ucOption & _BIT1)
        CScalerSetBit(_SCALE_DOWN_CTRL_22, ~_BIT0, _BIT0);          // Turn on V scale-down
    else
        CScalerSetBit(_SCALE_DOWN_CTRL_22, ~_BIT0, 0x00);           // Turn off V scale-down

    if(ucOption & _BIT3)
        CScalerSetBit(_SCALE_DOWN_CTRL_22, ~_BIT1, _BIT1);          // Turn on H scale-down
    else
        CScalerSetBit(_SCALE_DOWN_CTRL_22, ~_BIT1, 0x00);           // Turn off H scale-down
#endif

#if(_SCALER_TYPE == _RTD2547D)
    if(ucOption & _BIT0)
        CScalerSetBit(_SCALE_CTRL_32, ~_BIT1, _BIT1);               // Turn on V scale-up
    else
        CScalerSetBit(_SCALE_CTRL_32, ~_BIT1, 0x00);                // Turn off V scale-up

    if(ucOption & _BIT2)
        CScalerSetBit(_SCALE_CTRL_32, ~_BIT0, _BIT0);               // Turn on H scale-up
    else
        CScalerSetBit(_SCALE_CTRL_32, ~_BIT0, 0x00);                // Turn off H scale-up
#else
    if(ucOption & _BIT0)
        CScalerSetBit(_SCALE_CTRL_19, ~_BIT1, _BIT1);               // Turn on V scale-up
    else
        CScalerSetBit(_SCALE_CTRL_19, ~_BIT1, 0x00);                // Turn off V scale-up

    if(ucOption & _BIT2)
        CScalerSetBit(_SCALE_CTRL_19, ~_BIT0, _BIT0);               // Turn on H scale-up
    else
        CScalerSetBit(_SCALE_CTRL_19, ~_BIT0, 0x00);                // Turn off H scale-up
#endif

    // Set scale-down coefficient
#if (_SCALER_TYPE == _RTD2553V || _SCALER_TYPE == _RTD2546N || _SCALER_TYPE == _RTD2525L || _SCALER_TYPE == _RTD2547D)
    if(ucOption & _BIT3)    // H scale-down
    {
        // Data[12~15]
        ((DWORD *)pData)[3] = (DWORD)1 * 1048576 * stModeInfo.IHWidth;
        ((DWORD *)pData)[3] = (((DWORD *)pData)[3] % stDisplayInfo.DHWidth) ? ((((DWORD *)pData)[3] / stDisplayInfo.DHWidth) + 1) : (((DWORD *)pData)[3] / stDisplayInfo.DHWidth);

        // H scale-down factor
        pData[4] = ((((DWORD *)pData)[3] * 16 / 1048576 - 16) & 0x3f);
        pData[5] = ((((DWORD *)pData)[3] >> 16) & 0xff);
        pData[6] = ((((DWORD *)pData)[3] >> 8) & 0xff);
        pData[7] = ((((DWORD *)pData)[3]) & 0xff);

    }
    else
    {
        pData[4] = 0x00;
        pData[5] = 0x10;
        pData[6] = 0x00;
        pData[7] = 0x00;
    }

    if(ucOption & _BIT1)    // V scale-down
    {
        // Data[12~15]
        ((DWORD *)pData)[3] = (DWORD)2 * 131072 * stModeInfo.IVHeight / stDisplayInfo.DVHeight;
        ((DWORD *)pData)[3] = (((DWORD *)pData)[3] >> 1) + (((DWORD *)pData)[3] & 0x01);

        // V scale-down factor
        pData[0] = ((((DWORD *)pData)[3] * 16 / 131072 - 16) & 0x3f);
        pData[1] = ((((DWORD *)pData)[3] >> 16) & 0x07);
        pData[2] = ((((DWORD *)pData)[3] >> 8) & 0xff);
        pData[3] = ((((DWORD *)pData)[3]) & 0xff);

        CScalerSetBit(_SCALE_DOWN_CTRL_23, ~_BIT2, 0x00);    // Diable V scale-down compensation
    }
    else
    {
        pData[0] = 0x00;
        pData[1] = 0x02;
        pData[2] = 0x00;
        pData[3] = 0x00;

        CScalerSetBit(_SCALE_DOWN_CTRL_23, ~_BIT2, 0x00);    // Diable V scale-down compensation
    }

    CScalerSetByte(_SD_ACCESS_PORT_24, 0x80);
    CScalerWrite(_SD_DATA_PORT_25, 8, pData, _NON_AUTOINC);
    CScalerSetByte(_SD_ACCESS_PORT_24, 0x00);

#else

    if(ucOption & _BIT3)    // H scale-down
    {
        // Data[12~15]
        ((DWORD *)pData)[3] = (DWORD)131072 * stModeInfo.IHWidth;
        ((DWORD *)pData)[3] = (((DWORD *)pData)[3] % stDisplayInfo.DHWidth) ? ((((DWORD *)pData)[3] / stDisplayInfo.DHWidth) + 1) : (((DWORD *)pData)[3] / stDisplayInfo.DHWidth);


        // H scale-down factor
        pData[0] = ((((DWORD *)pData)[3] >> 16) & 0x07);
        pData[0] |= ((((DWORD *)pData)[3] * 16 / 131072 - 16) << 3);
        pData[1] = ((((DWORD *)pData)[3] >> 8) & 0xff);
        pData[2] = ((((DWORD *)pData)[3]) & 0xff);

        //CScalerSetBit(_VGIP_CTRL_04, 0xff, 0x40);    // Enable H scale-down compensation
    }
    else
    {
        pData[0] = 0x02;
        pData[1] = 0x00;
        pData[2] = 0x00;

        //CScalerSetBit(_VGIP_CTRL_04, 0xbf, 0x00);    // Diable H scale-down compensation
    }

    if(ucOption & _BIT1)    // V scale-down
    {
        // Data[12~15]
        ((DWORD *)pData)[3] = (DWORD)2 * 4096 * stModeInfo.IVHeight / stDisplayInfo.DVHeight;
        ((DWORD *)pData)[3] = (((DWORD *)pData)[3] >> 1) + (((DWORD *)pData)[3] & 0x01);

        // V scale-down factor
        pData[3] = ((((DWORD *)pData)[3] >> 8) & 0xff);
        pData[4] = ((((DWORD *)pData)[3]) & 0xff);

        CScalerSetBit(_SCALE_DOWN_CTRL_22, ~_BIT2, 0x00);    // Diable V scale-down compensation
    }
    else
    {
        pData[3] = 0x10;
        pData[4] = 0x00;

        CScalerSetBit(_SCALE_DOWN_CTRL_22, ~_BIT2, 0x00);    // Diable V scale-down compensation
    }

    CScalerWrite(_H_SCALE_DOWN_H_23, 5, pData, _AUTOINC);
#endif

    // Set scale-up coefficient
    if(ucOption & _BIT2)    // H scale-up
    {
        // Data[12~15]
        ((DWORD *)pData)[3] = (DWORD)2 * 1048576 * stModeInfo.IHWidth / stDisplayInfo.DHWidth;
        ((DWORD *)pData)[3] = (((DWORD *)pData)[3] >> 1) + (((DWORD *)pData)[3] & 0x01);

        pData[0] = ((((DWORD *)pData)[3] >> 16) & 0x0f);
        pData[1] = ((((DWORD *)pData)[3] >> 8) & 0xff);
        pData[2] = ((((DWORD *)pData)[3]) & 0xff);
    }
    else
    {
        pData[0] = 0x0f;
        pData[1] = 0xff;
        pData[2] = 0xff;
    }

    if(ucOption & _BIT0)    // V scale-up
    {
        // Data[12~15]
        ((DWORD *)pData)[3] = (DWORD)2 * 1048576 * stModeInfo.IVHeight / stDisplayInfo.DVHeight;
        ((DWORD *)pData)[3] = (((DWORD *)pData)[3] >> 1) + (((DWORD *)pData)[3] & 0x01);

        pData[3] = ((((DWORD *)pData)[3] >> 16) & 0x0f);
        pData[4] = ((((DWORD *)pData)[3] >> 8) & 0xff);
        pData[5] = ((((DWORD *)pData)[3]) & 0xff);
    }
    else
    {
        pData[3] = 0x0f;
        pData[4] = 0xff;
        pData[5] = 0xff;
    }

#if(_SCALER_TYPE == _RTD2547D)
    CScalerSetByte(_SU_ACCESS_PORT_33, 0x80);
    CScalerWrite(_SU_DATA_PORT_34, 6, pData, _NON_AUTOINC);
    CScalerSetByte(_SU_ACCESS_PORT_33, 0x00);
#else
    CScalerSetByte(_SF_ACCESS_PORT_1A, 0x80);
    CScalerWrite(_SF_DATA_PORT_1B, 6, pData, _NON_AUTOINC);
    CScalerSetByte(_SF_ACCESS_PORT_1A, 0x00);
#endif
}


