//----------------------------------------------------------------------------------------------------
// ID Code      : YPbPr.c No.0001
// Update Note  : 
//
//----------------------------------------------------------------------------------------------------

#define __YPBPR__

#include "Header\Include.h"


#if(_YPBPR_SUPPORT == _ON)

//--------------------------------------------------
// Description  : Search mode for YPbPr
// Input Value  : None
// Output Value : YPbPr Mode number
//--------------------------------------------------
BYTE CYPbPrSearchMode(void)
{
    BYTE cnt, modetemp = _MODE_NOSUPPORT;

#if (_SCALER_TYPE != _RTD2553V && _SCALER_TYPE != _RTD2546N && _SCALER_TYPE != _RTD2525L && _SCALER_TYPE != _RTD2547D)
    if(((bit)CScalerGetBit(_SYNC_SELECT_47, _BIT6)))
        return modetemp;
#endif

    for(cnt=0;cnt<_MAX_YPBPR_MODE;cnt++)
    {
        if(CYPbPrCompareMode(cnt) == _TRUE)
        {
            modetemp = cnt;
            break;
        }
    }

    return modetemp;
}

//--------------------------------------------------
// Description  : Compare mode in YPbPr mode table
// Input Value  : Mode number
// Output Value : Return _TRUE if get an available mode
//--------------------------------------------------
bit CYPbPrCompareMode(BYTE ucModeCnt)
{
    if(abs(stModeInfo.IVFreq - tYPBPR_MODE_TABLE[ucModeCnt].IVFreq) > tYPBPR_MODE_TABLE[ucModeCnt].IVFreqTolerance)
    {
        return _FALSE;
    }

    if(abs(stModeInfo.IHFreq - tYPBPR_MODE_TABLE[ucModeCnt].IHFreq) > tYPBPR_MODE_TABLE[ucModeCnt].IHFreqTolerance)
    {
        return _FALSE;
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : Get mode information for YPbPr
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CYPbPrGetModeInfo(void)
{
    stModeInfo.IHTotal = tYPBPR_MODE_TABLE[stModeInfo.ModeCurr].IHTotal;
    stModeInfo.IHStartPos = tYPBPR_MODE_TABLE[stModeInfo.ModeCurr].IHStartPos;
    stModeInfo.IHWidth = tYPBPR_MODE_TABLE[stModeInfo.ModeCurr].IHWidth;

    stModeInfo.IVStartPos = tYPBPR_MODE_TABLE[stModeInfo.ModeCurr].IVStartPos;
    stModeInfo.IVHeight = tYPBPR_MODE_TABLE[stModeInfo.ModeCurr].IVHeight;

    stModeUserData.Clock = stModeInfo.IHTotal;
    stModeUserData.Phase = 0;
    stModeUserData.HPosition = stModeInfo.IHStartPos;
    stModeUserData.VPosition = stModeInfo.IVStartPos;

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
#endif  // #if (_SCALER_TYPE == _RTD2547D)

    // Test
    stModeUserCenterData.CenterClock    = stModeInfo.IHTotal;
    stModeUserCenterData.CenterHPos     = stModeInfo.IHStartPos;
    stModeUserCenterData.CenterVPos     = stModeInfo.IVStartPos;
}

//--------------------------------------------------
// Description  : Start up settings for YPbPr
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CYPbPrStartUp(void)
{
    CScalerCodeW(tYPBPR_TABLE_SET_SCALER);

#if (_SCALER_TYPE != _RTD2553V && _SCALER_TYPE != _RTD2546N && _SCALER_TYPE != _RTD2525L && _SCALER_TYPE != _RTD2547D)
    switch(stModeInfo.ModeCurr)
    {
        case _YPBPR_MODE_576I:
        case _YPBPR_MODE_480I:
            CScalerSetByte(_CLAMP_CTRL0_5C, 0x00);
            break;

        case _YPBPR_MODE_576P:
        case _YPBPR_MODE_480P:
            break;
        case _YPBPR_MODE_720P:
        case _YPBPR_MODE_1080I_50:
        case _YPBPR_MODE_1080I60:
            CScalerSetByte(_CLAMP_CTRL0_5C, 0x00);
            CScalerSetByte(_ADC_VBIAS1_ED, 0x0D);
            break;
    }
#endif
}

//--------------------------------------------------
// Description  : Setup YPbPr mode
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CYPbPrSetupMode(void)
{
    WORD ustemp;
    BYTE temp;
    BYTE option = 0;

    // Get information from mode table, such as IHTotal, IHStartPos, IHWidth, IVStartPos, IVHeight.
    CYPbPrGetModeInfo();

    // Start up settings of VGA mode.
    CModeStartUpVGA();

    // Start up settings of YPbPR mode.
    CYPbPrStartUp();

    // Get scaling option, Capture window setup, Scaling setup, Display setup
    CModeSetupDisplay();
  
    CAdjustBrightness();
    CAdjustContrast();
    CAdjustBacklight();
    CEepromLoadAdcData(); //V307 modify
    CAdjustAdcGainOffset();
    CAdjustAdcClock(stModeUserData.Clock);
    CAdjustPhase(stModeUserData.Phase);
    CAdjustHPosition();
    CAdjustVPosition();
#if (_SCALER_TYPE == _RTD2547D)
    CScalerPageSelect(_PAGE0); //V401 modify
    CScalerSetBit(_P0_ADC_CTRL_A1, ~(_BIT5 | _BIT4), (ucAdcPGA << 4) & 0x30); //V401 modify
#elif (_SCALER_TYPE == _RTD2553V || _SCALER_TYPE == _RTD2546N || _SCALER_TYPE == _RTD2525L)
    CScalerSetDataPortBit(_ADC_ACCESS_PORT_DC, 0x00, ~(_BIT5 | _BIT4), (ucAdcPGA << 4) & 0x30); //V401 modify 
#else
    CScalerSetBit(_ADC_RGB_CTRL_DC, ~(_BIT5 | _BIT4), (ucAdcPGA << 4) & 0x30); //V401 modify
#endif

#if(_OSD_TYPE == _OSD007)
  #if(_IMAGE_COLOR_MODE)
    CSetColorMode(_GET_IMAGE_COLOR_MODE());
  #endif
#endif

#if (_SCALER_TYPE != _RTD2547D)
    CScalerSetBit(_POWER_ON_OFF_CTRL_C2, ~_BIT5, 0x00); //V304 modify
#endif

#if((_ADC_OFFSET_ADJUSTING == _ADJUST_BY_HW_OFF_LINE) && (_SCALER_TYPE == _RTD2525L || _SCALER_TYPE == _RTD2547D)) //V307 modify
    CAutoAdjustAdcOffset(); //V307 modify
    CEepromSaveAdcData(); //V307 modify
#endif  

    switch(stModeInfo.ModeCurr)
    {
        case _YPBPR_MODE_576I:
        case _YPBPR_MODE_480I:
        case _YPBPR_MODE_1080I50:
        case _YPBPR_MODE_1080I60:
#if (_SCALER_TYPE == _RTD2547D)
            CScalerSetBit(_SCALE_CTRL_32, ~_BIT7, _BIT7);
            CScalerPageSelect(_PAGE5);
            CScalerSetBit(_P5_SDRF_IN1_SDR_CTRL_B9, ~_BIT7, _BIT7);//For interlace mode odd field toggle
            CScalerSetBit(_VGIP_ODD_CTRL_13, ~_BIT0, _BIT0);
#else
            CScalerSetBit(_SCALE_CTRL_19, ~_BIT7, _BIT7);
            CScalerSetBit(_VGIP_ODD_CTRL_08, ~_BIT0, _BIT0);
#endif

#if (_SCALER_TYPE == _RTD2553V || _SCALER_TYPE == _RTD2546N || _SCALER_TYPE == _RTD2525L || _SCALER_TYPE == _RTD2547D) 
            CScalerRead(_IV_DV_DELAY_CLK_ODD_41, LENGTH(1), &temp, _NON_AUTOINC);
            ustemp = (WORD)temp * 16 + 16;
            if(ustemp > (stModeInfo.IHTotal / 2))
            {
                ustemp -= stModeInfo.IHTotal / 2;
                CScalerSetByte(_IV_DV_DELAY_CLK_EVEN_42, (ustemp - 16) / 16);
            }
            else
            {
#if (_SCALER_TYPE == _RTD2547D)
                CScalerSetByte(_IPV_ACT_STA_L_19, CScalerGetBit(_IPV_ACT_STA_L_19, 0xff) + 1);
#else
                CScalerSetByte(_IPV_ACT_STA_L_0E, CScalerGetBit(_IPV_ACT_STA_L_0E, 0xff) + 1);
#endif
                ustemp += stModeInfo.IHTotal;
                CScalerSetByte(_IV_DV_DELAY_CLK_ODD_41, (ustemp - 16) / 16);
                ustemp -= stModeInfo.IHTotal / 2;
                CScalerSetByte(_IV_DV_DELAY_CLK_EVEN_42, (ustemp - 16) / 16);
            } 
#else
  
            CScalerSetByte(_IPV_ACT_STA_L_0E, CScalerGetBit(_IPV_ACT_STA_L_0E, 0xff) + 1);
            CScalerRead(_IV_DV_DELAY_CLK_ODD_41, LENGTH(1), &temp, _NON_AUTOINC);
            ustemp = (WORD)temp * 16 + 16;
            ustemp += stModeInfo.IHTotal;
            CScalerSetByte(_IV_DV_DELAY_CLK_ODD_41, (ustemp - 16) / 16);
            ustemp -= stModeInfo.IHTotal / 2;
            CScalerSetByte(_IV_DV_DELAY_CLK_EVEN_42, (ustemp - 16) / 16);
#endif
            CScalerSetBit(_FS_DELAY_FINE_TUNING_43, ~(_BIT1), _BIT1);
            break;
    }

#if (_SCALER_TYPE == _RTD2547D)
    if(!GET_FRCTATUS())
    {
        CModeSetFIFOForFrameSync();

        pData[0] = CFrameSyncDo();

        if(pData[0] == 2)
        {
            CModeResetMode();
            return;
        }
    }
#else
    pData[0] = CFrameSyncDo();

    if(pData[0] == 2)
    {
        CModeResetMode();
        return;
    }
#endif


    CModeSetupEtcs(_FUNCTION_ENABLE);
}

#endif  // End of #if(_YPBPR_SUPPORT == _ON)
