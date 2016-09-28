//----------------------------------------------------------------------------------------------------
// ID Code      : Source.c No.0004
// Update Note  : 
//
//----------------------------------------------------------------------------------------------------

#define __SOURCE__

#include "Header\Include.h"


//--------------------------------------------------
// Description  : Scan all input port and select active port
// Input Value  : None
// Output Value : Return _TRUE if the selected input source is exist
//--------------------------------------------------
bit CSourceHandler(void)
{   
#if(_AUTO_SCAN_SOURCE)
    bit bFirstScan = 0;
    BYTE cnt;
 
    for(cnt = _GET_INPUT_SOURCE(); ; cnt++)
    {
         if (cnt == (_INPUT_PORT_MAX+1))
         {
             bFirstScan = 1;
             cnt        = 0;
         }

         switch(cnt)
         {
#if(_VGA_SUPPORT)      
         case _SOURCE_VGA:
             CSourceScanInputPort(CGetSourcePortType(_SOURCE_VGA));
             break;
#endif  

#if(_TMDS_SUPPORT)
         case _SOURCE_DVI:
             CSourceScanInputPort(CGetSourcePortType(_SOURCE_DVI));
             break;
#endif  

#if(_HDMI_SUPPORT)
         case _SOURCE_HDMI:
             CSourceScanInputPort(CGetSourcePortType(_SOURCE_HDMI));
             break;
#endif  
 
#if(_YPBPR_SUPPORT)
         case _SOURCE_YPBPR:
             CSourceScanInputPort(CGetSourcePortType(_SOURCE_YPBPR));
             break;
#endif
        }

        if (1 == bInputSignalAvailable)
        {
            _SET_INPUT_SOURCE(cnt);

            return _TRUE;
        }
        else
        {
            if (!GET_SOURCE_AUTOCHANGE())
                return _FALSE;
                 
            if (1 == bFirstScan && _GET_INPUT_SOURCE() == cnt)
            {
                return _FALSE;
            }
        }    
    }

#else

    CSourceScanInputPort(CGetSourcePortType(_GET_INPUT_SOURCE()));

    if (0 == bInputSignalAvailable)
        return _FALSE;
    
    return _TRUE;
#endif
}

//--------------------------------------------------
// Description  : Return source input port type
// Input Value  : 
// Output Value : 
//--------------------------------------------------
BYTE CGetSourcePortType(BYTE ucSource)
{
    switch(ucSource)
    {
#if(_VGA_SUPPORT)
    case _SOURCE_VGA:         return _SOURCE_VGA_PORT_TYPE;
#endif

#if(_TMDS_SUPPORT)
    case _SOURCE_DVI:         return _SOURCE_DVI_PORT_TYPE;
#endif

#if(_HDMI_SUPPORT)
    case _SOURCE_HDMI:        return _SOURCE_HDMI_PORT_TYPE;
#endif
        
#if(_VIDEO_SUPPORT)
    case _SOURCE_VIDEO_AV:
    case _SOURCE_VIDEO_SV:
    case _SOURCE_VIDEO_YUV:
    case _SOURCE_VIDEO_DVD:
    case _SOURCE_VIDEO_TV:    
    case _SOURCE_VIDEO_SCART: return _SOURCE_VIDEO_PORT_TYPE;
#endif
        
#if(_YPBPR_SUPPORT)
    case _SOURCE_YPBPR:       return _SOURCE_YPBPR_PORT_TYPE;
#endif

    default:                  break;
    }

    return _NO_PORT;
}

//--------------------------------------------------
// Description  : Check connect pin and scan all input port to obtain if the signal is available
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CSourceScanInputPort(BYTE ucInputPort)
{
    switch(ucInputPort)
    {
#if(_YPBPR_SUPPORT == _ON)
        case _YPBPR_A0_PORT:
#endif
        case _DSUB_A0_PORT:
            if(CSourceScanInputPortVGA(_ANALOG_SOURCE_0))
            {
                if((bit)CScalerGetBit(_SYNC_SELECT_47, _BIT4))
                    bHsyncSelection = 1;
                else
                    bHsyncSelection = 0;

                bInputSignalAvailable = 1;
			}
            else
                bInputSignalAvailable = 0;

            break;

#if(_YPBPR_SUPPORT == _ON)
        case _YPBPR_A1_PORT:
#endif
        case _DSUB_A1_PORT:
            if(CSourceScanInputPortVGA(_ANALOG_SOURCE_1))
            {
                if((bit)CScalerGetBit(_SYNC_SELECT_47, _BIT4))
                    bHsyncSelection = 1;
                else
                    bHsyncSelection = 0;

                bInputSignalAvailable = 1;
            }
			else
                bInputSignalAvailable = 0;
            break;

#if((_TMDS_SUPPORT == _ON) || (_HDMI_SUPPORT == _ON))

        case _DVI_PORT:
        case _HDMI_PORT:
            if(CSourceScanInputPortDVI(_DE_ONLY_OFF))
                bInputSignalAvailable = 1;
#if(_DVI_DE_ONLY_SUPPORT == _ON)
            else if(CSourceScanInputPortDVI(_DE_ONLY_ON))
                bInputSignalAvailable = 1;
#endif
            else
                bInputSignalAvailable = 0;
            break;

        case _DVI_I_A0_PORT:
#if(_DVI_I_SOURCE_SWITCH_SUPPORT == _ON)
            if(GET_DVI_I_SOURCE_SWITCH())
#endif
            {
                if(CSourceScanInputPortDVI(_DE_ONLY_OFF))
                    bInputSignalAvailable = 1;
#if(_DVI_DE_ONLY_SUPPORT == _ON)
                else if(CSourceScanInputPortDVI(_DE_ONLY_ON))
                    bInputSignalAvailable = 1;
#endif
                else if(CSourceScanInputPortVGA(_ANALOG_SOURCE_0))
                {
                    if((bit)CScalerGetBit(_SYNC_SELECT_47, _BIT4))
                        bHsyncSelection = 1;
                    else
                        bHsyncSelection = 0;

                    bInputSignalAvailable = 1;
                }
                else
                    bInputSignalAvailable = 0;
            }
#if(_DVI_I_SOURCE_SWITCH_SUPPORT == _ON)
            else
            {
                if(CSourceScanInputPortVGA(_ANALOG_SOURCE_0))
                {
                    if((bit)CScalerGetBit(_SYNC_SELECT_47, _BIT4))
                        bHsyncSelection = 1;
                    else
                        bHsyncSelection = 0;

                    bInputSignalAvailable = 1;
                }
                else if(CSourceScanInputPortDVI(_DE_ONLY_OFF))
                    bInputSignalAvailable = 1;
#if(_DVI_DE_ONLY_SUPPORT == _ON)
                else if(CSourceScanInputPortDVI(_DE_ONLY_ON))
                    bInputSignalAvailable = 1;
#endif
                else
                    bInputSignalAvailable = 0;
            }
#endif
            break;

        case _DVI_I_A1_PORT:
#if(_DVI_I_SOURCE_SWITCH_SUPPORT == _ON)
            if(GET_DVI_I_SOURCE_SWITCH())
#endif
            {
                if(CSourceScanInputPortDVI(_DE_ONLY_OFF))
                    bInputSignalAvailable = 1;
#if(_DVI_DE_ONLY_SUPPORT == _ON)
                else if(CSourceScanInputPortDVI(_DE_ONLY_ON))
                    bInputSignalAvailable = 1;
#endif
                else if(CSourceScanInputPortVGA(_ANALOG_SOURCE_1))
                {
                    if((bit)CScalerGetBit(_SYNC_SELECT_47, _BIT4))
                        bHsyncSelection = 1;
                    else
                        bHsyncSelection = 0;

                    bInputSignalAvailable = 1;
                }
                else
                    bInputSignalAvailable = 0;
            }
#if(_DVI_I_SOURCE_SWITCH_SUPPORT == _ON)
            else
            {
                if(CSourceScanInputPortVGA(_ANALOG_SOURCE_1))
                {
                    if((bit)CScalerGetBit(_SYNC_SELECT_47, _BIT4))
                        bHsyncSelection = 1;
                    else
                        bHsyncSelection = 0;

                    bInputSignalAvailable = 1;
                }
                else if(CSourceScanInputPortDVI(_DE_ONLY_OFF))
                    bInputSignalAvailable = 1;
#if(_DVI_DE_ONLY_SUPPORT == _ON)
                else if(CSourceScanInputPortDVI(_DE_ONLY_ON))
                    bInputSignalAvailable = 1;
#endif
                else
                    bInputSignalAvailable = 0;
            }
#endif
            break;

#endif
 //   case _VIDEO_PORT:
//   //         CLR_INPUTSIGNAL_AVAILABLE(cnt);
 //       break;
    } 
}

//--------------------------------------------------
// Description  : Scan VGA input port to obtain if the signal is available
// Input Value  : Select analog source 0 or 1
// Output Value : Return _TRUE if the signal is available
//--------------------------------------------------
bit CSourceScanInputPortVGA(BYTE ucAnalogSource)
{
    BYTE cnt, synctypetemp = _NO_SYNC_STATE;
    
    CScalerSetBit(_SYNC_SELECT_47, ~_BIT4, 0x00);
    
#if (_SCALER_TYPE == _RTD2547D)

    ucAnalogSource = ucAnalogSource;

#else

    if(ucAnalogSource == _ANALOG_SOURCE_0)
    {
        CScalerSetBit(_SYNC_SELECT_47, ~(_BIT3 | _BIT2), 0x00);
#if (_SCALER_TYPE == _RTD2553V || _SCALER_TYPE == _RTD2546N || _SCALER_TYPE == _RTD2525L)
		CScalerSetDataPortBit(_ADC_ACCESS_PORT_DC, 0x00, ~_BIT3, 0x00);
#else
        CScalerSetBit(_ADC_RGB_CTRL_DC, ~_BIT3, 0x00);
#endif
    }
    else if(ucAnalogSource == _ANALOG_SOURCE_1)
    {
        CScalerSetBit(_SYNC_SELECT_47, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));
#if (_SCALER_TYPE == _RTD2553V || _SCALER_TYPE == _RTD2546N || _SCALER_TYPE == _RTD2525L)
		CScalerSetDataPortBit(_ADC_ACCESS_PORT_DC, 0x00, ~_BIT3, _BIT3);
#else
        CScalerSetBit(_ADC_RGB_CTRL_DC, ~_BIT3, _BIT3);
#endif    
    }
#endif  // #if (_SCALER_TYPE == _RTD2547D)  
    
    for(cnt=0;cnt<2;cnt++)
    {
#if (_SCALER_TYPE == _RTD2553V || _SCALER_TYPE == _RTD2546N || _SCALER_TYPE == _RTD2525L || _SCALER_TYPE == _RTD2547D)

 #if(_VIDEO_SUPPORT && _VIDEO_CHIP == _VDC_TB1334)
    if (bSourceVideo())
        synctypetemp = CSyncGetSyncTypeStepVGA();
    else
 #endif // #if(_VIDEO_SUPPORT && _VIDEO_CHIP == _VDC_TB1334)
    {
  #if(_HSYNC_TYPE_DETECTION == _NORMAL_RUN)
        synctypetemp = CSyncGetSyncTypeStepVGA();
  #elif(_HSYNC_TYPE_DETECTION == _AUTO_RUN)
        synctypetemp = CSyncGetSyncTypeAutoRun();
  #endif
    }

#else
        synctypetemp    = CSyncGetSyncTypeStep1VGA();
#endif
        
        if(((synctypetemp == _CS_STATE) || (synctypetemp == _SOY_STATE)) && ((bit)CScalerGetBit(_SYNC_SELECT_47, _BIT4)))
        {
#if (_SCALER_TYPE != _RTD2553V && _SCALER_TYPE != _RTD2546N && _SCALER_TYPE != _RTD2525L && _SCALER_TYPE != _RTD2547D)
            if((bit)CScalerGetBit(_DETECT_HSYNC_PERIOD_LSB_4B, _BIT7))
                CScalerSetBit(_SYNC_SELECT_47, ~_BIT6, _BIT6);
#endif
            
            CScalerSetBit(_SYNC_SELECT_47, ~_BIT0, 0x00);
            CAdjustSyncProcessorMeasureStart();
            
            if(CTimerPollingEventProc(60, CMiscModeMeasurePollingEvent))
            {
                if(CModeMeasureData())
                {
#if (_SCALER_TYPE == _RTD2553V || _SCALER_TYPE == _RTD2546N || _SCALER_TYPE == _RTD2525L || _SCALER_TYPE == _RTD2547D)
                    CScalerSetBit(_STABLE_MEASURE_4F, ~_BIT1, _BIT1);
#else
                    CScalerSetBit(_STABLE_COUNT_4F, ~_BIT4, _BIT4);
#endif
                    CScalerRead(_STABLE_PERIOD_H_50, 2, pData, _AUTOINC);
                    ((WORD *)pData)[1] = ((pData[0] & 0x07) << 8) | pData[1];
                    
                    if(((stModeInfo.IHSyncPulseCount * 7 / stModeInfo.IHCount) != 0) 
                        || (stModeInfo.IHSyncPulseCount < 4)
                        || (abs(stModeInfo.IHCount - ((WORD *)pData)[1]) > 4))
                    {
                        return _FALSE;
                    }
                }
                else
                {
                    return _FALSE;
                }
            }
            else
            {
                return _FALSE;
            }
        }
        
        if(synctypetemp != _NO_SYNC_STATE)
        {
            return _TRUE;
        }
        
        CScalerSetBit(_SYNC_SELECT_47, ~_BIT4, CScalerGetBit(_SYNC_SELECT_47, _BIT4) ^ _BIT4);
    }
    
    return _FALSE;
}

#if(_TMDS_SUPPORT == _ON || _HDMI_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Scan DVI input port to obtain if the signal is available
// Input Value  : None
// Output Value : Return _TRUE if the signal is available
//--------------------------------------------------
bit CSourceScanInputPortDVI(BYTE ucPar)
{             
    BYTE cnt0, cnt1;

#if (_SCALER_TYPE == _RTD2547D)

    CScalerPageSelect(_PAGE2);

    if(ucPar == _DE_ONLY_ON)
        CScalerSetBit(_P2_POWER_ON_OFF_CTRL_A7, ~_BIT7, _BIT7);
    else
        CScalerSetBit(_P2_POWER_ON_OFF_CTRL_A7, ~_BIT7, 0x00);

    CScalerRead(_P2_UP_DOWN_CTRL1_B6, 1, pData, _NON_AUTOINC);
    pData[0] &= 0xf0;

    if((pData[0] == 0xe0) | (pData[0] == 0x80) | (pData[0] == 0x60) | (pData[0] == 0x10))
        CScalerSetByte(_P2_RGB_PLL_SETTING_AE, 0x24);
    else if((pData[0] == 0x40) | (pData[0] == 0x30))
        CScalerSetByte(_P2_RGB_PLL_SETTING_AE, 0x2b);
    else
        CScalerSetByte(_P2_RGB_PLL_SETTING_AE, 0x24);

    CScalerSetBit(_P2_ANALOG_COMMON_CTRL2_AB, ~(_BIT3 | _BIT2), 0x00);
    CScalerSetBit(_P2_ANALOG_COMMON_CTRL2_AB, ~(_BIT6 | _BIT5 | _BIT4), _BIT6 | _BIT5 | _BIT4);

    for(cnt0=0;cnt0<2;cnt0++)
    {
        for(cnt1=0;cnt1<2;cnt1++)
        {
            CScalerSetByte(_P2_TMDS_CTRL_A4, 0xf8);
            CTimerDelayXms(25);

            CScalerRead(_P2_TMDS_CTRL_A4, 1, pData, _NON_AUTOINC);

            if(ucPar == _DE_ONLY_ON)
                pData[0] = ((pData[0] & 0xe0) == 0xe0) ? _TRUE : _FALSE;
            else
                pData[0] = ((pData[0] & 0xf8) == 0xf8) ? _TRUE : _FALSE;

            if(pData[0])
            {
                CScalerRead(_P2_UP_DOWN_CTRL1_B6, 1, pData, _NON_AUTOINC);
                pData[0] &= 0xf0;

                if((pData[0] == 0xe0) || (pData[0] == 0x80) || (pData[0] == 0x60) || (pData[0] == 0x40) || (pData[0] == 0x30))
                {
                    if(CGetSourcePortType(_GET_INPUT_SOURCE()) == _HDMI_PORT)
                    {
                        if(!CHdmiFormatDetect())
                        {
                            CAdjustDisableHDMIWatchDog(_WD_SET_AVMUTE_ENABLE | _WD_PACKET_VARIATION);
                            CScalerSetDataPortBit(_P2_HDMI_ADDR_PORT_C9, _P2_HDMI_AVMCR_30, ~_BIT3, _BIT3);//Enable DVI/HDMI video output
                        }

#if(_HDMI_SUPPORT == _ON)
                        if(!CHdmiVideoSetting())
                        {
                            return _FALSE;
                        }
#elif(_TMDS_SUPPORT == _ON) 
                        if(CHdmiFormatDetect())
                            return _FALSE;
                        else
                            CScalerSetDataPortBit(_P2_HDMI_ADDR_PORT_C9, _P2_HDMI_AVMCR_30, ~_BIT3, _BIT3);//Enable DVI/HDMI video output
#endif
                    }
                    else if(CGetSourcePortType(_GET_INPUT_SOURCE()) == _DVI_PORT)
                    {
                        if(CHdmiFormatDetect())
                        {
                            return _FALSE;
                        }
                        else
                        {
                            CAdjustDisableHDMIWatchDog(_WD_SET_AVMUTE_ENABLE | _WD_PACKET_VARIATION);
                            CScalerSetDataPortBit(_P2_HDMI_ADDR_PORT_C9, _P2_HDMI_AVMCR_30, ~_BIT3, _BIT3);//Enable DVI/HDMI video output
                        }
                    }
                    return _TRUE;
                }
            }
#if(_HDMI_SUPPORT == _ON)
            if(!CHdmiFormatDetect())
#endif    
            CScalerSetBit(_P2_ANALOG_COMMON_CTRL2_AB, ~(_BIT3 | _BIT2), _BIT2);
        }

        CScalerSetBit(_P2_ANALOG_COMMON_CTRL2_AB, ~(_BIT6 | _BIT5 | _BIT4), _BIT4);
        CScalerSetBit(_P2_ANALOG_COMMON_CTRL2_AB, ~(_BIT3 | _BIT2), 0x00);
    }

#else

    if(ucPar == _DE_ONLY_ON)
        CScalerSetBit(_POWER_ON_OFF_CTRL_C2, ~_BIT7, _BIT7);
    else
        CScalerSetBit(_POWER_ON_OFF_CTRL_C2, ~_BIT7, 0x00);

    CScalerRead(_UP_DOWN_CTRL1_D2, 1, pData, _NON_AUTOINC);
    pData[0] &= 0x0f;
    
    if((pData[0] == 0x0e) | (pData[0] == 0x08) | (pData[0] == 0x06) | (pData[0] == 0x01))
        CScalerSetByte(_RGB_PLL_SETTING_C9, 0x24);
    else if((pData[0] == 0x04) | (pData[0] == 0x03))
        CScalerSetByte(_RGB_PLL_SETTING_C9, 0x2b);
    else
        CScalerSetByte(_RGB_PLL_SETTING_C9, 0x24);
    
    CScalerSetBit(_TMDS_MEAS_RESULT0_BD, ~(_BIT2 | _BIT1), 0x00);
    CScalerSetBit(_ANALOG_COMMON_CTRL2_C6, 0x9f, 0x70);
    for(cnt0=0;cnt0<2;cnt0++)
    {
        for(cnt1=0;cnt1<2;cnt1++)
        {
            CScalerSetByte(_TMDS_CTRL_BF, 0x00);
            CTimerDelayXms(25);
            
            CScalerRead(_TMDS_CTRL_BF, 1, pData, _NON_AUTOINC);
            if((pData[0] & 0xf8) == 0xf8)
            {
                // Force to open DE-Only mode
                //CScalerSetBit(_POWER_ON_OFF_CTRL_C2, ~_BIT7, _BIT7);

                CScalerRead(_UP_DOWN_CTRL1_D2, 1, pData, _NON_AUTOINC);
                pData[0] &= 0x0f;

                if((pData[0] == 0x0e) || (pData[0] == 0x08) || (pData[0] == 0x06) || (pData[0] == 0x04) || (pData[0] == 0x03))
                    return _TRUE;
            }
            
            CScalerSetBit(_TMDS_MEAS_RESULT0_BD, ~(_BIT2 | _BIT1), _BIT1);
        }

#if((_TMDS_SUPPORT == _ON) && (_DVI_LONG_CABLE_SUPPORT == _ON))
        CScalerSetBit(_ANALOG_COMMON_CTRL2_C6, 0x9f, 0x10);
        CScalerSetBit(_TMDS_MEAS_RESULT0_BD, ~(_BIT2 | _BIT1), 0x00);
#else
        break;
#endif

    }
#endif    

    return _FALSE;  
}
#endif  // End of #if(_TMDS_SUPPORT == _ON)

//-----------------------------------------------------------
#if(_VIDEO_SUPPORT && _VIDEO_CHIP == _VDC_TB1334)
// return 1-> Video
bit bSourceVideo(void)
{
    if (_GET_INPUT_SOURCE() == _SOURCE_VGA  || 
        _GET_INPUT_SOURCE() == _SOURCE_DVI  || 
        _GET_INPUT_SOURCE() == _SOURCE_HDMI || 
        _GET_INPUT_SOURCE() == _SOURCE_YPBPR)
        return 0;

    return 1;
}
#endif
