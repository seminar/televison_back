//----------------------------------------------------------------------------------------------------
// ID Code      : Video.c No.0002
// Update Note  : 
//
//----------------------------------------------------------------------------------------------------

#define __VIDEO__

#include "Header\Include.h"


#if(_VIDEO_SUPPORT == _ON)  

//===============================================================
//                  RTD2612/3
#if(_VIDEO_CHIP == _VDC_RTD2612 || _VIDEO_CHIP == _VDC_RTD2613)
BYTE xdata ucTVPrevColor   = 0;
//BYTE xdata ucDifferentSignalCount = 0;

//#define _DEFERENT_SIGNAL_COUNT    6
#endif
//===============================================================


//===============================================================
//                  TB1334
// eric 0104 add for TB1334 PAL M/N
#if(_VIDEO_CHIP == _VDC_TB1334)

#define _TB1334_AUTO1             0
#define _TB1334_AUTO2             1
#define _TB1334_NO_COLOR_COUNT    50

BYTE xdata ucTB1334ColorLockCount = 0;
bit bSetAutoMode                  = _TB1334_AUTO1;


ModeTableType code tVIDEO_INPUTMODE_PRESET_TABLE[2] =
{
	{   // NTSC
        0 | _SYNC_HN_VN | _SYNC_HP_VN | _SYNC_HN_VP | _SYNC_HP_VP,          // Polarity Flags,
        692, 237,//231,                                                           // InputWidth, InputHeight,
        157, 600,                                                           // HFreq in kHz, VFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        858, 362,                                                           // HTotal, VTotal,
        137, 16,//20,                                                            // HStartPos, VStartPos,
        // 2547D +6, -4
        // 2023L -24,-4
    },  

	{   // PAL
        0 | _SYNC_HN_VN | _SYNC_HP_VN | _SYNC_HN_VP | _SYNC_HP_VP,          // Polarity Flags,
        686, 279,                                                           // InputWidth, InputHeight,
        157, 500,                                                           // HFreq in kHz, VFreq in Hz,
        _HFREQ_TOLERANCE, _VFREQ_TOLERANCE,                                 // HFreqTolerance in kHz, VFreqTolerance in Hz,
        864, 362,                                                           // HTotal, VTotal,
        152, 24,                                                            // HStartPos, VStartPos,
        // 2547D -0, -6
        // 2023L -28,-4
    },  
};
#endif
//===============================================================




//==============================================================================  
// Routine Name: void CPowerUpVDC(void)
// Input Value : Null
// Output Value: Null
// Description : Power up video decoder
//============================================================================== 
void CPowerUpVDC(void)
{
#if(_VIDEO_CHIP != _VDC_TB1334)
    bVDC_PWR    = _VDC_ON;
    CTimerDelayXms(40);
#endif
}

//==============================================================================  
// Routine Name: void CPowerDownVDC(void)
// Input Value : Null
// Output Value: Null
// Description : Power down video decoder
//============================================================================== 
void CPowerDownVDC(void)
{
#if(_VIDEO_CHIP != _VDC_TB1334)
    bVDC_PWR = _VDC_OFF;
#endif
    bVideoON = 0;
}

//==============================================================================  
// Routine Name: void CReset_VDC(void)
// Input Value : Null
// Output Value: Null
// Description : Reset video decoder
//============================================================================== 
void CReset_VDC(void)
{
#if(_VIDEO_CHIP != _VDC_TB1334)
    bVDC_RST=0;
    CTimerDelayXms(20);
    bVDC_RST=1;        
    CTimerDelayXms(10);
#endif

#if(_VIDEO_CHIP == _VDC_RTD2612 || _VIDEO_CHIP == _VDC_RTD2613)
    gmi_CI2CWriteVDCByte(0x3f, 0x01);
    CTimerDelayXms(10);
    gmi_CI2CWriteVDCByte(0x3f, 0x00);
#endif
}
//==============================================================================  

void gmi_CVDCOff(void)
{
#if(_VIDEO_CHIP != _VDC_TB1334)
    bVDC_PWR = _VDC_OFF;
    bVDC_RST = 0;
#endif
}

//==============================================================================  
// Routine Name: void CInit_VDC(void)
// Input Value : Null
// Output Value: Null
// Description : Initial video decoder
//============================================================================== 
void CInit_VDC(void)
{
    gmi_CInitialVDC();

    // eric 1031
    CInitInputSource(); 
}

//==============================================================================  
// Routine Name:void CVideoInitial(void)
// Input Value :Null
// Output Value:Null
// Description :Initialize Video Decoder (TW9906) 
//==============================================================================  
void CVideoInitial(void)
{
    CReset_VDC();
    CInit_VDC();  
}
 
//==============================================================================  
// Routine Name:
// Input Value :Null
// Output Value:Null
// Description :
//==============================================================================  
#if(_VIDEO_CHIP == _VDC_RTD2612 || _VIDEO_CHIP == _VDC_RTD2613)
// 0: AV/TV    1: SVIDEO/YCBCR
void CSelectAdpativeMode(BYTE ucSourceMode, BYTE ucColorMode)
{
    if (ucSourceMode) // SVIDEO/YCBCR
    {
        gmi_CI2CWriteVDCByte(0x03, 0x03);
        gmi_CI2CWriteVDCByte(0x91, 0x00);
    }
    else
    {
        switch(ucColorMode)
        {
        case 0x00:  // NTSC
            gmi_CI2CWriteVDCByte(0x03, 0x00);
            gmi_CI2CWriteVDCByte(0x91, 0x03);
            break;
    
        case 0x01:  // PAL BG/H/I
        case 0x02:  // PAL M
        case 0x03:  // PAL N
            gmi_CI2CWriteVDCByte(0x03, 0x02);
            gmi_CI2CWriteVDCByte(0x91, 0x13);
            break;
    
        case 0x04:  // SECAM
        case 0x05:  // NTSC 443
            gmi_CI2CWriteVDCByte(0x03, 0x03);
            gmi_CI2CWriteVDCByte(0x91, 0x03);
            break;
        }
    }
}

//==============================================================================  
void CSetRTD2610ColorMode(void)
{
    BYTE uctemp = 0;

#if(_VIDEO_TV_SUPPORT)

    if (_GET_INPUT_SOURCE() == _SOURCE_VIDEO_TV)
    {
        CAdjustSetSharpnessTable(tSU_COEF_TABLE[2], tSU_COEF_TABLE[2]);
        gmi_CI2CWriteVDCByte(0x80, 0x14);  // Set peaking
        switch(ucTVType)
        {
        case _TV_PAL_M     :    // 60Hz PAL M
            gmi_CI2CWriteVDCByte(0x00, 0x04 | (gmi_CI2CReadVDCByte(0x00) & 0x81));

            while(0xff != tVideoPALM[uctemp])
            {
                gmi_CI2CWriteVDCByte(tVideoPALM[uctemp], tVideoPALM[++uctemp]);
                uctemp++;
            }
            CSelectAdpativeMode(0, 0x02);
            break;
    
        case _TV_NTSC_M    :    // 60Hz NTSC M
        case _TV_NTSC_4_BG :    // 60Hz NTSC 4/BG
        case _TV_NTSC_4_I  :    // 60Hz NTSC 4/I
        case _TV_NTSC_4_DK :    // 60Hz NTSC 4/DK
            gmi_CI2CWriteVDCByte(0x00, 0x00 | (gmi_CI2CReadVDCByte(0x00) & 0x81));
    
            while(0xff != tVideoNTSC[uctemp])
            {
                gmi_CI2CWriteVDCByte(tVideoNTSC[uctemp], tVideoNTSC[++uctemp]);
                uctemp++;
            }
            CSelectAdpativeMode(0, 0x00);
            break;
    
        case _TV_PAL_N     :    // 50Hz PAL N
            gmi_CI2CWriteVDCByte(0x00, 0x36 | (gmi_CI2CReadVDCByte(0x00) & 0x81));

            while(0xff != tVideoPALN[uctemp])
            {
                gmi_CI2CWriteVDCByte(tVideoPALN[uctemp], tVideoPALN[++uctemp]);
                uctemp++;
            }
            CSelectAdpativeMode(0, 0x03);
            break;
    
        case _TV_PAL_BG    :    // 50Hz PAL B/G
        case _TV_PAL_I     :    // 50Hz PAL I
        case _TV_PAL_DK    :    // 50Hz PAL D/K
            gmi_CI2CWriteVDCByte(0x00, 0x32 | (gmi_CI2CReadVDCByte(0x00) & 0x81));

            while(0xff != tVideoPALBGHI[uctemp])
            {
                gmi_CI2CWriteVDCByte(tVideoPALBGHI[uctemp], tVideoPALBGHI[++uctemp]);
                uctemp++;
            }
            CSelectAdpativeMode(0, 0x01);
            break;
    
        case _TV_SECAM_BG  :    // 50Hz SECAM B/G
        case _TV_SECAM_DK  :    // 50Hz SECAM D/K
        case _TV_SECAM_L   :    // 50Hz SECAM L
        case _TV_SECAM_LL  :    // 50Hz Secam L'
            gmi_CI2CWriteVDCByte(0x00, 0x38 | (gmi_CI2CReadVDCByte(0x00) & 0x81));

            while(0xff != tVideoSECAM[uctemp])
            {
                gmi_CI2CWriteVDCByte(tVideoSECAM[uctemp], tVideoSECAM[++uctemp]);
                uctemp++;
            }
            CSelectAdpativeMode(0, 0x04);
            break;
        } // end switch
    }
    else   // Source AV/SV
#endif
    {
        BYTE ucRdata      = gmi_CI2CReadVDCByte(0x3c);
        BYTE ucFcState    = gmi_CI2CReadVDCByte(0x7D);
        BYTE ucSourceMode = 0; // Normal AV/TV
        BYTE ucSource1    = gmi_CI2CReadVDCByte(0x00);
        BYTE ucSource2    = gmi_CI2CReadVDCByte(0x01);

        CAdjustSetSharpnessTable(tSU_COEF_TABLE[0], tSU_COEF_TABLE[0]);
        gmi_CI2CWriteVDCByte(0x80, 0x15);  // Set peaking

        //if (_GET_INPUT_SOURCE() == _SOURCE_VIDEO_SV || _GET_INPUT_SOURCE() == _SOURCE_VIDEO_YUV)
        if ((ucSource1 & 0x01) || (ucSource2 & 0x40))
        {
            ucSourceMode = 1;
        }

        switch(ucRdata & 0x04)
        {
        case 0x04://PAL  625 scan lines detected
            gmi_CI2CWriteVDCByte(0x04, 0xdc);

            if ( (gmi_CI2CReadVDCByte(0x3B) & 0x02)
              && (ucFcState < 128 || ucFcState > 240)
              && !(ucRdata & 0x01)) // PAL N signal 
          //  if (0)//gmi_CI2CReadVDCByte(0x3b) & 0x02) // PAL N signal
            {
                gmi_CI2CWriteVDCByte(0x00, 0x36 | (gmi_CI2CReadVDCByte(0x00) & 0x81));

                while(0xff != tVideoPALN[uctemp])
                {
                    gmi_CI2CWriteVDCByte(tVideoPALN[uctemp], tVideoPALN[++uctemp]);
                    uctemp++;
                }
                CSelectAdpativeMode(ucSourceMode, 0x03);
            }
            else // PAL BGHI/SECAM
            {     
                BYTE ucVideoSecamStatus     = gmi_CI2CReadVDCByte(0x3c) & 0x02;

                if (ucVideoSecamStatus && ucFcState != 0xff)//(gmi_CI2CReadVDCByte(0x3c) & 0x02) && (gmi_CI2CReadVDCByte(0x7d) < 0x50)) // Secam signal
                {
                    gmi_CI2CWriteVDCByte(0x00, 0x38 | (gmi_CI2CReadVDCByte(0x00) & 0x81));

                    while(0xff != tVideoSECAM[uctemp])
                    {
                        gmi_CI2CWriteVDCByte(tVideoSECAM[uctemp], tVideoSECAM[++uctemp]);
                        uctemp++;
                    }
                    CSelectAdpativeMode(ucSourceMode, 0x04);
                }
                else  // Pal signal
                {
                    gmi_CI2CWriteVDCByte(0x00, 0x32 | (gmi_CI2CReadVDCByte(0x00) & 0x81));

                    while(0xff != tVideoPALBGHI[uctemp])
                    {
                        gmi_CI2CWriteVDCByte(tVideoPALBGHI[uctemp], tVideoPALBGHI[++uctemp]);
                        uctemp++;
                    }
                    CSelectAdpativeMode(ucSourceMode, 0x01);
                }
            }
            break;			
			
        case 0x00: // NTSC
            if(gmi_CI2CReadVDCByte(0x3b) & 0x02) // PAL M signal
            {
                gmi_CI2CWriteVDCByte(0x00, 0x04 | (gmi_CI2CReadVDCByte(0x00) & 0x81));

                while(0xff != tVideoPALM[uctemp])
                {
                    gmi_CI2CWriteVDCByte(tVideoPALM[uctemp], tVideoPALM[++uctemp]);
                    uctemp++;
                }
                CSelectAdpativeMode(ucSourceMode, 0x02);
            }
            else  // NTSC
            {
                gmi_CI2CWriteVDCByte(0x00, 0x00 | (gmi_CI2CReadVDCByte(0x00) & 0x81));
    
                while(0xff != tVideoNTSC[uctemp])
                {
                    gmi_CI2CWriteVDCByte(tVideoNTSC[uctemp], tVideoNTSC[++uctemp]);
                    uctemp++;
                }
                CSelectAdpativeMode(ucSourceMode, 0x00);
            }
            break;
        }  // End switch
    }

    if (_GET_INPUT_SOURCE() == _SOURCE_VIDEO_YUV)
        gmi_CI2CWriteVDCByte(0x01, (gmi_CI2CReadVDCByte(0x01)) | 0x40);           // Set input to YCrCb

}
#endif



//============================================================================== 
void CSetVideoColor(void)
{
    CEepromLoadAdcData();  // Eric 0606 add
    CAdjustAdcGainOffset();
    SET_COLOR_TEMP_TYPE(_CT_USER);
    CEepromLoadBriConData();
    CEepromLoadColorTempData();
    CAdjustContrast();
    CAdjustBrightness();
    CAdjustBacklight();
#if(_OSD_TYPE == _OSD007)
  #if(_IMAGE_COLOR_MODE)
    CSetColorMode(_GET_IMAGE_COLOR_MODE());
  #endif
#endif
    CSetVDCSaturation(stConBriData.Saturation);
    if (CHECK60HZ())     // NTSC
        gmi_CAdjustVDCHue(stConBriData.Hue);
    else
        gmi_CAdjustVDCHue(47);
    CAdjustVideoSharp();

#if(_VIDEO_VIVID_COLOR_SUPPORT)

//    SET_MZ_WINDOW_CFG_TYPE(_MZ_WINDOW_CFG_FULL);
  //  CAdjustHLWindow();
    CAccAdjustVividColorForVideo(2);
    if (_GET_INPUT_SOURCE() != _SOURCE_VIDEO_TV)
        CAdjustPeakingFilterForVideo(0);

#endif
}

//============================================================================== 
// Routine Name: void CVideoDisplaySet(void)
// Input Value : None
// Output Value: None
// Description : Display video set process
//==============================================================================  
#if(_VIDEO_CHIP != _VDC_TB1334)
void CVideoDisplaySet(void)
{
#if(_SET_VIDEO_MODE_METHOD == _TABLE) // Write table
    WORD iHtotal;

    CLR_LIGHTPOWERSTATUS();
    CScalerSetBit(_VDISP_CTRL_28, ~ _BIT5, (_BIT5 ));	
    CScalerCodeW(tVIDEO_TABLE_SET_SCALER);
    gmi_CSetMode(((CHECK60HZ()) ? 1 : 0), 1, 1);

    CScalerRead(_DH_TOTAL_H_2A, 2, pData, _AUTOINC);
    iHtotal = ((pData[0] << 8) | pData[1]) + 8;
    pData[0] = (HIBYTE(iHtotal) & 0x0f);
    pData[1] = (LOBYTE(iHtotal));
    CScalerWrite(_DH_TOTAL_H_2A, 2, pData, _AUTOINC);

  #if(_VIDEO_CHIP == _VDC_RTD2612)
    CTimerDelayXms(150);

    CSetRTD2610ColorMode();

    if (_GET_INPUT_SOURCE() == _SOURCE_VIDEO_TV)
        gmi_CI2CWriteVDCByte(0xe0, 0xff);
    else
        gmi_CI2CWriteVDCByte(0xe0, 0x00);


    gmi_CI2CWriteVDCByte(0x07, ((gmi_CI2CReadVDCByte(0x07)) & 0xCF) | 0x00);  // Disable blue background
    gmi_CI2CWriteVDCByte(0x3f, 0x01);
    CTimerDelayXms(10);
    gmi_CI2CWriteVDCByte(0x3f, 0x00);
  #endif

    CSetVideoColor();

  #if(_VIDEO_CHIP == _VDC_RTD2612)
    CTimerDelayXms(300);
  #endif
                

#else


    BYTE ucField = 0;
    WORD ustemp  = 0;
    BYTE ucScale = 0;
    
    if (CHECK60HZ())     // NTSC
    {
        ucField = 1;
        stDisplayInfo.DHTotal = Panel.NTSC_Htotal;
    }
    else                // PAL
    {
        ucField = 0;
        stDisplayInfo.DHTotal = Panel.PAL_Htotal;
    }  
     
#if(_VIDEO_CHIP == _VDC_RTD2612 || _VIDEO_CHIP == _VDC_RTD2613)
    CTimerDelayXms(150);

    CSetRTD2610ColorMode();

    if (_GET_INPUT_SOURCE() == _SOURCE_VIDEO_TV)
        gmi_CI2CWriteVDCByte(0xe0, 0xff);
    else
        gmi_CI2CWriteVDCByte(0xe0, 0x00);


    gmi_CI2CWriteVDCByte(0x07, ((gmi_CI2CReadVDCByte(0x07)) & 0xCF) | 0x00);  // Disable blue background
    gmi_CI2CWriteVDCByte(0x3f, 0x01);
    CTimerDelayXms(10);
    gmi_CI2CWriteVDCByte(0x3f, 0x00);
#endif

#if(_VIDEO_TV_SUPPORT)
    if (_GET_INPUT_SOURCE() == _SOURCE_VIDEO_TV)
    {
        gmi_CSetVDCFreeRunMode(ucField ? _VDC_FREE_RUN_MODE_TO_60HZ : _VDC_FREE_RUN_MODE_TO_50HZ);
    }
    else
        gmi_CSetVDCFreeRunMode(_VDC_FREE_RUN_MODE_TO_AUTO);
#endif

    CTimerDelayXms(150);
    CScalerCodeW(tVIDEO_TABLE_SET_SCALER);

#if (_SCALER_TYPE == _RTD2547D)
    CScalerPageSelect(_PAGE2);
    CScalerSetBit(_P2_POWER_ON_OFF_CTRL_A7, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00); //V307 modify
    CScalerSetBit(_P2_Z0_CALIBRATION_CTRL_AC, ~_BIT6, 0x00); //V305 modify
#else
    CScalerSetBit(_POWER_ON_OFF_CTRL_C2, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), 0x00); //V307 modify
    CScalerSetBit(_Z0_CALIBRATION_CTRL_C7, ~_BIT6, 0x00); //V307 modify
#endif

    // for change source if VGA have signal change VIDEO red/blue swap(PNL_IASX12G)
#if (_SCALER_TYPE != _RTD2547D)
    CScalerSetBit(_VGIP_DELAY_CTRL_07, ~(_BIT3), 0x00);   
#endif

    stModeInfo.IHTotal      = tVIDEO_TABLE_INPUT_INFO[ucField][0];
    stModeInfo.IHStartPos   = tVIDEO_TABLE_INPUT_INFO[ucField][1];
    stModeInfo.IHWidth      = tVIDEO_TABLE_INPUT_INFO[ucField][2];
    stModeInfo.IVStartPos   = tVIDEO_TABLE_INPUT_INFO[ucField][3];
    stModeInfo.IVHeight     = tVIDEO_TABLE_INPUT_INFO[ucField][4];
    
     stDisplayInfo.DHWidth   = CCalcPanelWdith();
    stDisplayInfo.DVHeight  = CCalcPanelDVEnd() - Panel.DVStartPos;
    stDisplayInfo.DVStartPos = Panel.DVStartPos;

    // Get scaling information
    ucScale = 0;
    if(stModeInfo.IVHeight < stDisplayInfo.DVHeight)        ucScale |= _BIT0;    // bit 0 : V scale-up
    if(stModeInfo.IVHeight > stDisplayInfo.DVHeight)        ucScale |= _BIT1;    // bit 1 : V scale-down
    if(stModeInfo.IHWidth < stDisplayInfo.DHWidth)          ucScale |= _BIT2;    // bit 2 : H scale-up
    if(stModeInfo.IHWidth > stDisplayInfo.DHWidth)          ucScale |= _BIT3;    // bit 3 : H scale-down
    
#if (_SCALER_TYPE == _RTD2547D)
 #if(_FRC_SUPPORT == _ON)
    ((DWORD *)pData)[0] = (DWORD)(stModeInfo.IHWidth) * (DWORD)(stModeInfo.IVHeight) * ((DWORD)stModeInfo.IVFreq + _PANEL_MAX_FRAME_RATE) / 10 / 85 * 100 / _MEMORY_BIT_NUM * 24;
    if(((DWORD *)pData)[0] > (DWORD)_MEMORY_SPEED * 1000000)
        CLR_FRCTATUS();
    else
        SET_FRCTATUS();
 #else
    CLR_FRCTATUS();
 #endif

#endif


    ucHStartBias = 0;
    ucVStartBias = 0;
    ucVStartBias = CAdjustIVS2DVSDelay(ucScale);

    if(ucVStartBias > stModeInfo.IVStartPos)
        ucVStartBias = stModeInfo.IVStartPos;

    //Set Capture Window  
    ustemp = stModeInfo.IHStartPos + _CAPTURE_HDELAY - (ucHStartBias + _PROGRAM_HDELAY);
    
#if (_SCALER_TYPE == _RTD2547D)
    CScalerSetBit(_IPH_ACT_STA_H_14, ~(_BIT2 | _BIT1 | _BIT0), HIBYTE(ustemp) & (_BIT2 | _BIT1 | _BIT0));
    CScalerSetByte(_IPH_ACT_STA_L_15, LOBYTE(ustemp));
    CScalerSetBit(_IPH_ACT_WID_H_16, ~(_BIT2 | _BIT1 | _BIT0), HIBYTE(stModeInfo.IHWidth) & (_BIT2 | _BIT1 | _BIT0));
    CScalerSetByte(_IPH_ACT_WID_L_17, LOBYTE(stModeInfo.IHWidth));
#else
    CScalerSetBit(_IPH_ACT_STA_H_09, ~(_BIT2 | _BIT1 | _BIT0), HIBYTE(ustemp) & (_BIT2 | _BIT1 | _BIT0));
    CScalerSetByte(_IPH_ACT_STA_L_0A, LOBYTE(ustemp));
    CScalerSetBit(_IPH_ACT_WID_H_0B, ~(_BIT2 | _BIT1 | _BIT0), HIBYTE(stModeInfo.IHWidth) & (_BIT2 | _BIT1 | _BIT0));
    CScalerSetByte(_IPH_ACT_WID_L_0C, LOBYTE(stModeInfo.IHWidth));
#endif    

    ustemp = stModeInfo.IVStartPos - (ucVStartBias + _PROGRAM_VDELAY);
    
#if (_SCALER_TYPE == _RTD2547D)
    CScalerSetBit(_IPV_ACT_STA_H_18, ~(_BIT2 | _BIT1 | _BIT0), HIBYTE(ustemp) & (_BIT2 | _BIT1 | _BIT0));
    CScalerSetByte(_IPV_ACT_STA_L_19, LOBYTE(ustemp));
    CScalerSetBit(_IPV_ACT_LEN_H_1A, ~(_BIT2 | _BIT1 | _BIT0), HIBYTE(stModeInfo.IVHeight) & (_BIT2 | _BIT1 | _BIT0));
    CScalerSetByte(_IPV_ACT_LEN_L_1B, LOBYTE(stModeInfo.IVHeight));
#else
    CScalerSetBit(_IPV_ACT_STA_H_0D, ~(_BIT2 | _BIT1 | _BIT0), HIBYTE(ustemp) & (_BIT2 | _BIT1 | _BIT0));
    CScalerSetByte(_IPV_ACT_STA_L_0E, LOBYTE(ustemp));
    CScalerSetBit(_IPV_ACT_LEN_H_0F, ~(_BIT2 | _BIT1 | _BIT0), HIBYTE(stModeInfo.IVHeight) & (_BIT2 | _BIT1 | _BIT0));
    CScalerSetByte(_IPV_ACT_LEN_L_10, LOBYTE(stModeInfo.IVHeight));
#endif     
 
    
    //Set DH_TOTAL
    pData[0] = (HIBYTE(stDisplayInfo.DHTotal) & 0x0f);
    pData[1] = (LOBYTE(stDisplayInfo.DHTotal));
#if (_SCALER_TYPE == _RTD2547D)
    CScalerSetByte(_DISP_ACCESS_PORT_2A, _DISP_DH_TOTAL_H_00);
    CScalerWrite(_DISP_DATA_PORT_2B, 2, pData, _NON_AUTOINC);
#else
    CScalerWrite(_DH_TOTAL_H_2A, 2, pData, _AUTOINC);
#endif

    if(ucField == 1)  // hill added to avoid framesync error
		stModeInfo.IVTotal = 264;   // set 60HZ 525 lines
    else if(ucField == 0)
		stModeInfo.IVTotal = 312;  // set 50Hz 625 lines

   ((WORD *)pData)[2] = _STD_DV_TOTAL;
	pData[0] = (HIBYTE(((WORD *)pData)[2]) & 0x0f);
	pData[1] = (LOBYTE(((WORD *)pData)[2]));
#if (_SCALER_TYPE == _RTD2547D)
    CScalerSetByte(_DISP_ACCESS_PORT_2A, _DISP_DV_TOTAL_H_0B);
    CScalerWrite(_DISP_DATA_PORT_2B, 2, pData, _NON_AUTOINC);
#else
    CScalerWrite(_DV_TOTAL_H_35, 2, pData, _AUTOINC);
#endif

    // Set internal input H sync delay
    CAdjustIHSDelay(ucHStartBias + _PROGRAM_HDELAY);
    
    // Set internal input V sync delay
    CAdjustIVSDelay(ucVStartBias + _PROGRAM_VDELAY);
              
    // Calculate and set display clock frequency
    stModeInfo.IHFreq = 157;    // For PAL and NTSC. We can use sync processor to measure the actual value.
    ((DWORD *)pData)[0] = (DWORD)(stDisplayInfo.DHTotal) * (DWORD)stModeInfo.IHFreq * (DWORD)(stDisplayInfo.DVHeight) / stModeInfo.IVHeight / 10;
#if (_SCALER_TYPE == _RTD2547D)
    CAdjustPLL(_DPLL, ((DWORD *)pData)[0]);
#else
    CAdjustDPLL(((DWORD *)pData)[0]);
#endif

    CModeSetScaling(ucScale);      // Set scaling 

    // Turn off full-line buffer
#if (_SCALER_TYPE == _RTD2547D)
    CScalerSetBit(_SCALE_CTRL_32, ~_BIT4, 0x00);
#else
    CScalerSetBit(_SCALE_CTRL_19, ~_BIT4, 0x00);
#endif
 
    CAdjustIVS2DVSDelay(ucScale);      // 0x05: ALL SCALE UP

    // Enable display timing
    CScalerSetBit(_VDISP_CTRL_28, ~(_BIT3 | _BIT1 | _BIT0), (_BIT3 | _BIT1 | _BIT0));

    CSetVideoColor();

    CPowerADCAPLLOff();

#if (_SCALER_TYPE == _RTD2547D)
    if(!GET_FRCTATUS())
    {
        CModeSetFIFOForFrameSync();
        pData[0] = CFrameSyncDo();
    }
#else
    pData[0] = CFrameSyncDo();
#endif

    SET_MODESTABLE();

    // Change to even/odd field frame sync
#if (_SCALER_TYPE == _RTD2547D)
    CScalerSetByte(_IPV_ACT_STA_L_19, CScalerGetBit(_IPV_ACT_STA_L_19, 0xff) + 1);
#else
    CScalerSetByte(_IPV_ACT_STA_L_0E, CScalerGetBit(_IPV_ACT_STA_L_0E, 0xff) + 1);
#endif
    CScalerRead(_IV_DV_DELAY_CLK_ODD_41, LENGTH(1), &ucScale, _NON_AUTOINC);
    ustemp = (WORD)ucScale * 16 + 16;
    ustemp += stModeInfo.IHTotal;
    CScalerSetByte(_IV_DV_DELAY_CLK_ODD_41, (ustemp - 16) / 16);
    ustemp -= stModeInfo.IHTotal / 2;
    CScalerSetByte(_IV_DV_DELAY_CLK_EVEN_42, (ustemp - 16) / 16);
    CScalerSetBit(_FS_DELAY_FINE_TUNING_43, ~(_BIT1), _BIT1);

#if (_SCALER_TYPE != _RTD2547D)
    CScalerSetBit(_POWER_ON_OFF_CTRL_C2, ~_BIT5, 0x00); //V304 modify
#endif

    CTimerDelayXms(100);
    CModeSetupEtcs(_FUNCTION_DISABLE);

#if(_VIDEO_CHIP == _VDC_RTD2612 || _VIDEO_CHIP == _VDC_RTD2613)
    CTimerDelayXms(300);
    CSetRTD2610ColorMode();
#endif

#endif

#if(_VIDEO_CHIP == _VDC_RTD2612 || _VIDEO_CHIP == _VDC_RTD2613)
    if (_GET_INPUT_SOURCE() == _SOURCE_VIDEO_TV)
    {
        if (ucTVType == _TV_SECAM_L) // Only for secam
        {
            gmi_CI2CWriteVDCByte(0x0F, 0x6C);
            gmi_CI2CWriteVDCByte(0x83, 0xEF);
        }
        else                         // Other color system
        {
            gmi_CI2CWriteVDCByte(0x0F, 0x2C);
            gmi_CI2CWriteVDCByte(0x83, 0x65);
        }
    }
#endif
}
#endif


//==============================================================================  
// Routine Name: bit CVideoFrameSyncDetect(void)
// Input Value : Null
// Output Value: 0 --> Frame sync ok      1 --> Frame sync wrong
// Description : Check frame sync or fram run
//============================================================================== 
#define VIDEO_FRAME_SYNC_ENABLE    0

bit CVideoFrameSyncDetect(void)
{
#if (!VIDEO_FRAME_SYNC_ENABLE)

#if(_VIDEO_CHIP == _VDC_TB1334)  // Check video color
// eric 0104 add for TB1334 PAL M/N

    if (_GET_INPUT_SOURCE() == _SOURCE_VIDEO_TV)
       ucTB1334ColorLockCount = 0;
    else
    {
        if (0x00 == gmi_CVideoCurrentColor(1))       // No signal or no color
        {
            ucTB1334ColorLockCount++;

            if (ucTB1334ColorLockCount > _TB1334_NO_COLOR_COUNT)
            {
                if (bSetAutoMode == _TB1334_AUTO1)
                {
                   if (_GET_INPUT_SOURCE() == _SOURCE_VIDEO_SV)
                       gmi_CI2CWriteVDCByte(0x06, 0x10);  // Auto2--> 358NTSC,M-PAL,N-PAL
                   else
                       gmi_CI2CWriteVDCByte(0x06, 0x12);  // Auto2--> 358NTSC,M-PAL,N-PAL
                  // gmi_CI2CWriteVDCByte(0x06, 0x12);  // Auto2--> 358NTSC,M-PAL,N-PAL
                   ucTB1334ColorLockCount = 0;
                   bSetAutoMode = _TB1334_AUTO2;   
                }
                else
                {
                   if (_GET_INPUT_SOURCE() == _SOURCE_VIDEO_SV)
                       gmi_CI2CWriteVDCByte(0x06, 0x00);  // Auto2--> 358NTSC,M-PAL,N-PAL
                   else
                       gmi_CI2CWriteVDCByte(0x06, 0x02);  // Auto2--> 358NTSC,M-PAL,N-PAL
                  // gmi_CI2CWriteVDCByte(0x06, 0x02);  // Auto 1--> 443PAL,358NTSC,SECA,443NTSC
                   ucTB1334ColorLockCount = 0;
                   bSetAutoMode = _TB1334_AUTO1;
                }

                CTimerDelayXms(6);
            }
        }
        else
            ucTB1334ColorLockCount = 0;
    }
#endif
           /*
#if(_VIDEO_CHIP == _VDC_RTD2612 || _VIDEO_CHIP == _VDC_RTD2613)
    if (CHECK50HZ() && _GET_INPUT_SOURCE() != _SOURCE_VIDEO_TV)
    {
       BYTE ucVideoSecamStatus     = gmi_CI2CReadVDCByte(0x3c) & 0x02;
       BYTE ucVideoSecamCordicFreq = gmi_CI2CReadVDCByte(0x7d); 
       BYTE ucCurrentColorMode     = (gmi_CI2CReadVDCByte(0x00)>>1) & 0x07;
 
       if (ucCurrentColorMode != 0x04)// PAL  
       {
           if (ucVideoSecamStatus && ucVideoSecamCordicFreq < 0x50)  // Current is Secam
               ucDifferentSignalCount++;
           else
               ucDifferentSignalCount = 0;
             //  return _TRUE;
       }
       else
       {
           if (!ucVideoSecamStatus && ucVideoSecamCordicFreq > 0x50)  // Current not Secam
               ucDifferentSignalCount++;
           else
               ucDifferentSignalCount = 0;
             //  return _TRUE;
       }

       if (ucDifferentSignalCount > _DEFERENT_SIGNAL_COUNT)
           return _TRUE;
    }
#endif   */

    return  _FALSE;
#else
    
    if(GET_POWERSTATUS() && GET_MODESTABLE())
    {
        CScalerRead(_STATUS0_02, 1, pData, _NON_AUTOINC);
        
        if((pData[0] & 0x03) == 0)
        {
            if((pData[0] & 0x80) == 0) // ADC PLL non lock
            {
                return _FALSE;
            }
        }
    }
    
    CLR_FRAMESYNCSTATUS();
    
    return _TRUE;
#endif
}

#if(_VIDEO_CHIP == _VDC_RTD2612 || _VIDEO_CHIP == _VDC_RTD2613)
//==============================================================================  
// Routine Name: 
// Input Value : Null
// Output Value: Null
// Description : 
//============================================================================== 
#if(_VIDEO_TV_SUPPORT)
void CCheckTVColor(void)
{
    if (ucTVType != ucTVPrevColor)
    {
        ucTVPrevColor = ucTVType;
        CSetRTD2610ColorMode();
    }
}
#endif
#endif

#if(_VIDEO_CHIP != _VDC_TB1334)
//==============================================================================  
// Routine Name: void CVideoModeHandler(void)
// Input Value : Null
// Output Value: Null
// Description : Video mode handler, the main control flow
//============================================================================== 
void CVideoModeHandler(void)
{           
    if(CPowerHandler())
    {
        ucCurrState = GET_POWERSTATUS() ? _INITIAL_STATE : _PWOFF_STATE;
    }
    
    if (!bVideoON && _PWOFF_STATE != ucCurrState && _SOURCE_CHANGE_STATE != ucCurrState)
    {
        bit bPrevPowerOff = (ucCurrState == _INITIAL_STATE) ? 1 : 0;

        bVideoON = 1;
        CPowerUpVDC();
        // Initial video settings
        CVideoInitial();
        ucCurrState = (1 == bPrevPowerOff) ? _INITIAL_STATE : _SEARCH_STATE; 
        return;
    }
    
    
    switch(ucCurrState)
    {
    case _PWOFF_STATE:
        ucCurrState = GET_POWERSTATUS() ? _INITIAL_STATE : _PWOFF_STATE;
        break;
        
    case _INITIAL_STATE:
#if(_LOGO_EN && _LOGO_TYPE == _LOGO_TYPE0)
           if(GET_LOGO_EN())
       DrawLogo();
#endif
        SET_FIRST_SHOW_NOTE();
        ucCurrState = _SEARCH_STATE; 
        break;
        
    case _SOURCE_CHANGE_STATE:
#if(_CHANGE_SOURCE_METHOD == _CHANGE_SOURCE_METHOD_0)
        CTimerDelayXms(20);
#endif
        break;

    case _SEARCH_STATE:
        if(gmi_CVideoSyncHandler())
        {
            if(gmi_CVideoModeChange())
            {
                // Mode stable. Initial display settings  switch to active/nosignal/nosupport state
                SET_READYFORDISPLAY();
                if(stModeInfo.ModeCurr == _MODE_NOSIGNAL)
                {
                    ucCurrState = _NOSIGNAL_STATE;
                }
                else if(stModeInfo.ModeCurr == _MODE_NOSUPPORT)
                {
                    CModeAutoMeasureOff();
                    ucCurrState = _NOSUPPORT_STATE;
                }
                else
                {
                    // add for if output not set ready not turn on backlight
                    VideoTurnOnLightCount++;

                    if (VideoTurnOnLightCount > 50 || _GET_INPUT_SOURCE() == _SOURCE_VIDEO_TV)
                    {                
                        VideoTurnOnLightCount = 0;

                        CVideoDisplaySet();
                        CModeAutoMeasureOff();
                        ucCurrState = _ACTIVE_STATE;

#if(_VIDEO_TV_SUPPORT)
                        ucVideoNoModeTime    = 0;
#endif
                    }
                }
            }
            else
            {
                // Still in search state
            }
            
            ucEvent0 = _INACTIVE_COUNTDOWN_EVENT;
        }
        else
        {
            CTimerCountDownEventProc(&ucEvent0, 5, CModeSyncTimeoutCountDownEvent);
        }
        break;
        
    case _ACTIVE_STATE:
        if(CVideoFrameSyncDetect())
        {
            CModeResetMode();
        }
        else
        {
            if (!gmi_CVideoIsExist())
            {
                CModeResetMode();
            }
            else
            {
#if(_VIDEO_CHIP == _VDC_RTD2612 || _VIDEO_CHIP == _VDC_RTD2613)
#if(_VIDEO_TV_SUPPORT)
                CCheckTVColor();
#endif
#endif
                if(GET_READYFORDISPLAY() == _TRUE)
                {
                    CLR_READYFORDISPLAY();
                    CLR_SOURCE_AUTOCHANGE();
                    SET_OSD_READYFORDISPLAY();
                    
                    CPowerPanelOn();

                    CAdjustBackgroundColor(0x00, 0x00, 0x00);
#if(_VIDEO_CHIP == _VDC_TB1334)
                    CAdjustDisableWatchDog(_WD_ALL);
#else
                    CAdjustEnableWatchDog(_WD_FRAMESYNC_APLL_NONLOCK);                                      
#endif

#if(_VIDEO_TV_SUPPORT)
                    ucVideoNoModeTime = 0;
#endif
                    CScalerSetBit(_VDISP_CTRL_28, ~(_BIT5 | _BIT3), (_BIT3)); // Set normal display
                }    
                
#if(_VIDEO_TV_SUPPORT)
                if (bChangeChannel)                
                {
                    if (GET_LIGHTPOWERSTATUS() == _OFF)
                    {  
                        bChangeChannel = 0;
                        CScalerSetBit(_VDISP_CTRL_28, ~(_BIT5 | _BIT3), (_BIT3)); // Set normal display
                        gmi_CI2CWrite9886(ucTVType, _TUNER_MUTE_OFF, _NORMAL_MODE);
                    }
                    else
                    {
                        VideoTurnOnLightCount++;
    
                        if (VideoTurnOnLightCount > 60)
                        {
                            CScalerSetBit(_VDISP_CTRL_28, ~(_BIT5 | _BIT3), (_BIT3)); // Set normal display
                         //   CAdjustBackgroundColor(0x00, 0x00, ((_GET_BLUE_BACKGROUND()) ? 0xff : 0x00));     
                            bChangeChannel        = 0;
                            VideoTurnOnLightCount = 0;
                        //    gmi_CI2CWrite9886(ucTVType, _TUNER_MUTE_OFF, _NORMAL_MODE);
                        }

                        break;
                    }  
                }
#endif
            }
        }

        VideoTurnOnLightCount++;
        if (VideoTurnOnLightCount < 5 && GET_LIGHTPOWERSTATUS() == _OFF)
            break;
        
        VideoTurnOnLightCount = 0;

        if (GET_LIGHTPOWERSTATUS() == _OFF)  
            CPowerLightPowerOn();
        break;
        
    case _NOSUPPORT_STATE:
        if(GET_READYFORDISPLAY() == _TRUE)
        {
            CLR_READYFORDISPLAY();
            CModeSetFreeRun();
            SET_OSD_READYFORDISPLAY();
        }
        
        if(CModeIsChange())
            CModeResetMode();
        
        break;
        
    case _NOSIGNAL_STATE: 
        if(GET_READYFORDISPLAY())
        {
            CLR_READYFORDISPLAY();
            SET_OSD_READYFORDISPLAY();
            CModeSetFreeRun();
        }
                              
        if(gmi_CSourceScanInputPortVideo()) 
        {
#if(_VIDEO_TV_SUPPORT)
            ucVideoNoModeTime = 253;
#endif
            CModeResetMode();
            ucCurrState   = _SEARCH_STATE;
        }        
        break;
        
    case _SLEEP_STATE:
        if(gmi_CSourceScanInputPortVideo())
        {
            CPowerLVDSOn();

            CModeResetMode();
            ucCurrState   = _SEARCH_STATE;
        }        
        break;
        
    default:
        break;
    }
}
#endif // #if(_VIDEO_CHIP != _VDC_TB1334)


//-----------------------------------------------------------
#if(_VIDEO_CHIP == _VDC_TB1334)
extern void gmi_CAdjVDCSharpness(unsigned char ucSharpness);
#endif

void CAdjustVideoSharp(void)
{
#if(_VIDEO_CHIP == _VDC_TB1334)
    if (_GET_VIDEO_SHARP() > 63)
    {
        _SET_VIDEO_SHARP(0x18);//_SHARP_DEF);
        ucOsdEventMsg = _SAVE_EE_VEDIOCOLOR_MSG;
    }

    gmi_CAdjVDCSharpness(_GET_VIDEO_SHARP());
#endif
}

// Eric add for TB1334
#if(_VIDEO_CHIP == _VDC_TB1334)
//==============================================================================  
//
//      CLoadTVNoSignalModeData
//
//==============================================================================  
#if(_VIDEO_TV_SUPPORT)
void CLoadTVNoSignalModeData(void)
{
    BYTE ucCurrent_Color = gmi_CVideoCurrentColor(0);

    switch(ucCurrent_Color)
    {
    case 0: // No color(TB1334) or no signal(Other VDC)
        ucCurrent_Color = bCurrentTVColorMode();
        break;

    case _VIDEO_COLOR_PAL:
        ucCurrent_Color = _50HZ;
        break;

    case _VIDEO_COLOR_NTSC:
        ucCurrent_Color = _60HZ;
        break;
    }          

    if (_60HZ == ucCurrent_Color)  // NTSC
    {
        RECODE60HZ();
        stModeInfo.ModeCurr         = 0;
        stModeInfo.Polarity         = 3;    // BIT0: H Polarity, Bit1: V Polarity
        stModeInfo.IHCount          = 1524; // Input Horizontal Count Numbers
        stModeInfo.IHSyncPulseCount = 49;   // Input Horizontal Sync Pulse Count Numbers
    }
    else
    {        
        RECODE50HZ(); 
        stModeInfo.ModeCurr         = 1;
        stModeInfo.Polarity         = 3;    // BIT0: H Polarity, Bit1: V Polarity
        stModeInfo.IHCount          = 1535; // Input Horizontal Count Numbers
        stModeInfo.IHSyncPulseCount = 48;   // Input Horizontal Sync Pulse Count Numbers
    }

    stModeInfo.IHFreq           = tVIDEO_INPUTMODE_PRESET_TABLE[stModeInfo.ModeCurr].IHFreq;      // Input Horizontal Frequency
    stModeInfo.IVFreq           = tVIDEO_INPUTMODE_PRESET_TABLE[stModeInfo.ModeCurr].IVFreq;      // Input Vertical Frequency
    stModeInfo.IHTotal          = tVIDEO_INPUTMODE_PRESET_TABLE[stModeInfo.ModeCurr].IHTotal;     // Input Horizontal Total Length
    stModeInfo.IVTotal          = tVIDEO_INPUTMODE_PRESET_TABLE[stModeInfo.ModeCurr].IVTotal;     // Input Vertical Total Length
    stModeInfo.IHWidth          = tVIDEO_INPUTMODE_PRESET_TABLE[stModeInfo.ModeCurr].IHWidth;     // Input Horizontal Width
    stModeInfo.IVHeight         = tVIDEO_INPUTMODE_PRESET_TABLE[stModeInfo.ModeCurr].IVHeight;    // Input Vertical Height
    stModeInfo.IHStartPos       = tVIDEO_INPUTMODE_PRESET_TABLE[stModeInfo.ModeCurr].IHStartPos;  // Input Horizontal Start Position
    stModeInfo.IVStartPos       = tVIDEO_INPUTMODE_PRESET_TABLE[stModeInfo.ModeCurr].IVStartPos;  // Input Vertical Start Position
}
#endif

//==============================================================================  
//
//      CSetVideoReady
//
//==============================================================================  
void CSetVideoReady(void)
{
    CAdjustDisableWatchDog(_WD_ALL);
    // Only for RTDxxxxV
#if(_SCALER_TYPE == _RTD2547D)
    CScalerSetBit(0x10, 0x0F, 0x00);
#else
    CScalerSetBit(0x05, 0x0F, 0x00);
    CScalerSetByte(0x4c, 0x02); 
    CScalerSetByte(0xDA, 0x00); 
    CScalerSetByte(0x6C, 0x00);
#endif

#if(_SCALER_TYPE == _RTD2023L)
    CScalerSetBit(0x06, ~(_BIT2 | _BIT4), (_BIT2 | _BIT4)); 
#endif


#if(_SCALER_TYPE != _RTD2547D)
    CScalerSetBit(_SYNC_INVERT_48, ~(_BIT6 | _BIT1), 0x00);
    CScalerSetBit(_SYNC_CTRL_49, ~(_BIT6 | _BIT5), 0x00);
#endif
}

//==============================================================================  
//
//      CLoadVideoModeData
//
//==============================================================================  
void CLoadVideoModeData(void)
{
    CLR_LIGHTPOWERSTATUS();
    switch(stModeInfo.ModeCurr)
    {
    case 0:     RECODE60HZ();    break;
    case 1:     RECODE50HZ();    break;
    }

    stModeUserData.HPosition    = tVIDEO_INPUTMODE_PRESET_TABLE[stModeInfo.ModeCurr].IHStartPos;
    stModeUserData.VPosition    = tVIDEO_INPUTMODE_PRESET_TABLE[stModeInfo.ModeCurr].IVStartPos;
    stModeUserData.Clock        = tVIDEO_INPUTMODE_PRESET_TABLE[stModeInfo.ModeCurr].IHTotal;
    stModeUserData.Phase        = 0;
}

//==============================================================================  
//
//      CVideoModeHandler
//
//==============================================================================  
void CVideoModeHandler(void)
{
    if (!bVideoON && _PWOFF_STATE != ucCurrState && _SOURCE_CHANGE_STATE != ucCurrState)
    {
        bit bPrevPowerOff = (ucCurrState == _INITIAL_STATE) ? 1 : 0;

        bVideoON = 1;
        CPowerUpVDC();
        // Initial video settings
        CVideoInitial();

        ucCurrState = (1 == bPrevPowerOff) ? _INITIAL_STATE : _SEARCH_STATE; 
    }
}



//==============================================================================  
//
//      CTVCheckChangeChannel
//
//==============================================================================  
#if(_VIDEO_TV_SUPPORT)
void CTVCheckChangeChannel(void)
{
    if (bChangeChannel)                
    {
        if (GET_LIGHTPOWERSTATUS() == _OFF)
        {  
            bChangeChannel = 0;
		                     if (gmi_CModeLocked())   //with signal
            CScalerSetBit(_VDISP_CTRL_28, ~(_BIT5 | _BIT3), (_BIT3)); // Set normal display
            gmi_CI2CWrite9886(ucTVType, _TUNER_MUTE_OFF, _NORMAL_MODE);
        }
        else
        {           
            VideoTurnOnLightCount++;
            if (VideoTurnOnLightCount > 60)
            {
		                     if (gmi_CModeLocked())   //with signal
                CScalerSetBit(_VDISP_CTRL_28, ~(_BIT5 | _BIT3), (_BIT3)); // Set normal display
             //   CAdjustBackgroundColor(0x00, 0x00, ((_GET_BLUE_BACKGROUND()) ? 0xff : 0x00));     
                bChangeChannel        = 0;
                VideoTurnOnLightCount = 0;
            //    gmi_CI2CWrite9886(ucTVType, _TUNER_MUTE_OFF, _NORMAL_MODE);
            }

        }  
    }
}
#endif  //#if(_VIDEO_TV_SUPPORT)

//==============================================================================  
//
//      CSetVideoBackLight
//
//==============================================================================  
void CSetVideoBackLight(void)
{ 
    if (GET_LIGHTPOWERSTATUS() == _OFF)
    {
        VideoTurnOnLightCount++;
        if (VideoTurnOnLightCount < 5)
            return;
        
        VideoTurnOnLightCount = 0;

        CPowerLightPowerOn();
    }  
}

//============================================================================== 
void CSetTB1334VideoMode(void)
{
    BYTE ucVDCBright;
    BYTE ucVDCCont;

    if (_GET_INPUT_SOURCE() != _SOURCE_VIDEO_TV)
    {
        if (0x00 == gmi_CVideoCurrentColor(1))      // No signal or no color
        {
            gmi_CI2CWriteVDCByte(0x06, 0x12);
            CTimerDelayXms(300);
            if (0x00 == gmi_CVideoCurrentColor(1))  // No signal or no color
                gmi_CI2CWriteVDCByte(0x06, 0x02);
        }
    }

    switch(_GET_INPUT_SOURCE())
    {
    case _SOURCE_VIDEO_AV:
        ucVDCBright = (CHECK60HZ()) ?  0x15 : 0x3e;
        //ucVDCBright = (CHECK60HZ()) ?  0x1C : 0x2A;
        ucVDCCont   = (CHECK60HZ()) ?  (0x5B+0x05) : (0x56+0x05);
        break;
    case _SOURCE_VIDEO_DVD:
    case _SOURCE_VIDEO_SV:
        ucVDCBright = (CHECK60HZ()) ?  0x16 : 0x24;
        ucVDCCont   = (CHECK60HZ()) ?  (0x4E+0x05) : (0x4A+0x05);
        break;

    case _SOURCE_VIDEO_TV:
        ucVDCBright = (CHECK60HZ()) ?  0x1C : 0x3f;
//        ucVDCBright = (CHECK60HZ()) ?  0x1C : 0x2A;
        ucVDCCont   = (CHECK60HZ()) ?  (0x5B+0x08) : (0x53);
       // ucVDCCont   = (CHECK60HZ()) ?  (0x5B+0x08) : (0x56+0x08);
        break;   
    }

    gmi_CI2CWriteVDCByte(0x00, ucVDCCont);   // Contrast
    gmi_CI2CWriteVDCByte(0x01, ucVDCBright); // Brightness


#if(_VIDEO_TV_SUPPORT)
    if (_GET_INPUT_SOURCE() == _SOURCE_VIDEO_TV)
    {
        ucTVType = CLoadChannelColorType(stVDCColor.CurrentChannel); 
       if(ucTVType==_TV_PAL_M||ucTVType==_TV_PAL_N)
        gmi_CI2CWriteVDCByte(0x06, 0x12);  // For input from RF

        gmi_CI2CWriteVDCByte(0x14, 0x00);  // For input from RF
        gmi_CSetVDCFreeRunMode((CHECK60HZ()) ? _VDC_FREE_RUN_MODE_TO_60HZ : _VDC_FREE_RUN_MODE_TO_50HZ);

        if (gmi_CModeLocked())
            gmi_CSetVDCFreeRunMode(_VDC_FREE_RUN_MODE_TO_AUTO);
        else
            gmi_CSetVDCFreeRunMode((CHECK60HZ()) ? _VDC_FREE_RUN_MODE_TO_60HZ : _VDC_FREE_RUN_MODE_TO_50HZ);
        gmi_CI2CWriteVDCByte(0x11, 0x20);  // TOF
        gmi_CI2CWriteVDCByte(0x0F, 0x00);  // For RF in
    }
    else
    {
        gmi_CI2CWriteVDCByte(0x14, 0x40);  // For input from AV/SV
        gmi_CSetVDCFreeRunMode(_VDC_FREE_RUN_MODE_TO_AUTO);

        gmi_CI2CWriteVDCByte(0x11, 0x00);  // BPF
        gmi_CI2CWriteVDCByte(0x0F, 0x80);  // For AV in
    }
#else
    gmi_CI2CWriteVDCByte(0x14, 0x40);      // For input from AV/SV
#endif // #if(_VIDEO_TV_SUPPORT)
}



#endif  //#if(_VIDEO_CHIP == _VDC_TB1334)


//============================================================================== 
void CSetVDCSaturation(const BYTE ucSaturation)	  		
{
#if(_VIDEO_CHIP == _VDC_TB1334)		 
     BYTE ucTemp = (ucSaturation < 52) ? (((WORD)ucSaturation*195)/100) : (((WORD)((ucSaturation-52) * 16)/100)+96);

    if (stSystemData.InputSource == _SOURCE_VIDEO_TV)
	   gmi_CI2CWriteVDCByte(0x02, ucTemp);
	else
#endif
       gmi_CAdjustVDCSaturation(stConBriData.Saturation);
    if(ucSaturation);
}


#endif  // #if(_VIDEO_SUPPORT == _ON)


