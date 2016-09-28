//----------------------------------------------------------------------------------------------------
// ID Code      : Mode.c No.0004
// Update Note  : 
//
//----------------------------------------------------------------------------------------------------

#define __MODE__

#include "Header\Include.h"

#if(_VIDEO_SUPPORT && _VIDEO_CHIP == _VDC_TB1334)
extern void CTB1334VideoMode(BYTE ucVideoMode, BYTE ucScalerType);
bit TVLockSignalFlag = 0;
#endif


//--------------------------------------------------
// Description  : Mode handler, the main control flow
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CModeHandler(void)
{  
    if(CPowerHandler())
    {
        ucCurrState = GET_POWERSTATUS() ? _INITIAL_STATE : _PWOFF_STATE;
    }
	
#if(_VIDEO_SUPPORT && _VIDEO_CHIP == _VDC_TB1334)
    if (bSourceVideo())
       CVideoModeHandler();
#endif



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
            if(CSyncHandler())
            {     
                // Source and sync OK
                if(CModeDetect())
                {

#if(_SCALER_TYPE == _RTD2547D)
                    CModeInterlaceCheck();
#endif                
                    // Mode stable. Initial display settings  switch to active/nosignal/nosupport state
                    SET_READYFORDISPLAY();
                    if(stModeInfo.ModeCurr == _MODE_NOSIGNAL)
                    {
                        ucCurrState = _NOSIGNAL_STATE;
                    }
#if(_SCALER_TYPE == _RTD2547D)
    #if(_FRC_SUPPORT == _ON)
                    else if((stModeInfo.ModeCurr == _MODE_NOSUPPORT) || ((stModeInfo.ModeCurr > _MODE_1440x900_75HZ) && (stModeInfo.IVFreq > (_PANEL_MAX_FRAME_RATE + 5))))
    #else
                    else if(stModeInfo.ModeCurr == _MODE_NOSUPPORT)
    #endif
#else
                    else if(stModeInfo.ModeCurr == _MODE_NOSUPPORT)
#endif
                    {
                        CModeAutoMeasureOn();
                        ucCurrState = _NOSUPPORT_STATE;
                    }
                    else
                    {   
#if(_SCALER_TYPE == _RTD2547D)
    #if((_OD_SUPPORT == _ON) || (_FRC_SUPPORT == _ON))
                        CMemorySDRAMReset();
    #endif
#endif

#if(_VIDEO_SUPPORT && _VIDEO_CHIP == _VDC_TB1334)
                    if (bSourceVideo())
                        CLoadVideoModeData();
#endif

                        CModeDisplayActiveMode();
                        CModeAutoMeasureOn();
#if(_SCALER_TYPE == _RTD2547D)
    #if(_HDMI_SUPPORT == _ON)
                        if(CHdmiFormatDetect() && (CGetSourcePortType(stSystemData.InputSource) == _HDMI_PORT))//Input source is the HDMI format.
                        {
                            CHdmiAudioFirstTracking();
                        }
                        CTimerActiveTimerEvent(SEC(0.5), CHdmiAudioWaitingFlagReadyEven);
    #endif
#endif
                        ucCurrState = _ACTIVE_STATE;
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
        /*
            if(GET_FIRST_LOADFONT() == _TRUE)
            {
                CLR_FIRST_LOADFONT();
                COsdDispFirstTimeLoadFont();
            } */
#if(_DDC_TYPE != _DDC_NONE)
            DDCInit();
#endif    
            break;

        case _ACTIVE_STATE:
   #if(_SCALER_TYPE == _RTD2547D)
            if(bFrameSyncDet() &&  (!GET_FRCTATUS()))
   #else
            if(bFrameSyncDet())
   #endif
            {
                CModeResetMode();
            }
            else
            {
			
                if(bModeIsChange())
                {
                    CModeResetMode();
                }
                else
                { 
                    CModeSetDisplayReady();                                                                  
                }
                  #if(_VIDEO_SUPPORT && _VIDEO_CHIP == _VDC_TB1334)
                      if(_GET_INPUT_SOURCE()==_SOURCE_VIDEO_TV)
                          {
		                     if (gmi_CModeLocked())   //with signal
		                     	{
                                              MUTE_OFF();
 					        if(GET_BURNIN_STATE() != BURNIN_ON)
 					        	{
                                             CAdjustBackgroundColor(0x00, 0x00,0x00);   
                                              CScalerSetBit(_VDISP_CTRL_28, ~(_BIT5 | _BIT3), (_BIT3)); // Set normal display
 					        	}
                                             gmi_CI2CWrite9886(ucTVType, _TUNER_MUTE_OFF, _NORMAL_MODE);
                                             TVLockSignalFlag = 1;
		                     	}
                                   else
                                  	{
                                             MUTE_ON();
					    if(GET_BURNIN_STATE() != BURNIN_ON)
					    	{
	   					      if(_GET_BLUE_BACKGROUND())
							{
	                                             CAdjustBackgroundColor(0x00, 0x00, 0xff);   
					                 CScalerSetBit(_VDISP_CTRL_28, ~(_BIT5 | _BIT3), (_BIT5)); 
							}
						  else
						  	{
							CAdjustBackgroundColor(0x00, 0x00, 0x00);     				
							CScalerSetBit(_VDISP_CTRL_28, ~(_BIT5 |_BIT3),  0x00 );			
						  	}
					    	}
                                              gmi_CI2CWrite9886(ucTVType, _TUNER_MUTE_ON, _NORMAL_MODE);
                                             TVLockSignalFlag = 0;
					 }
                          }
                   #endif
				
            }
#if(_VIDEO_SUPPORT && _VIDEO_CHIP == _VDC_TB1334)
            if (bSourceVideo())
               CSetVideoBackLight();
       if(_GET_INPUT_SOURCE() == _SOURCE_VIDEO_TV)
       {
        if (gmi_CModeLocked() )//with signal
              {  MUTE_OFF();
                  if(!TVLockSignalFlag)
                  	{
                 CModeResetMode();
                 TVLockSignalFlag = 1;
                  	}
								
                MUTE_OFF();				
                gmi_CSetVDCFreeRunMode(_VDC_FREE_RUN_MODE_TO_AUTO);
                gmi_CI2CWrite9886(ucTVType, _TUNER_MUTE_OFF, _NORMAL_MODE);
              }
              
              else
              {
                  if(TVLockSignalFlag)
                  	{
               CModeResetMode();
                TVLockSignalFlag = 0;
                  	}
                MUTE_ON();
                gmi_CSetVDCFreeRunMode((CHECK60HZ()) ? _VDC_FREE_RUN_MODE_TO_60HZ : _VDC_FREE_RUN_MODE_TO_50HZ);
                gmi_CI2CWrite9886(ucTVType, _TUNER_MUTE_ON, _NORMAL_MODE);
              }
			  
               if(CHECK60HZ())
                   SAW_HIGH();
	        else
                   SAW_LOW();
         }

#endif

            break;

        case _NOSUPPORT_STATE:
            if(GET_READYFORDISPLAY() == _TRUE)
            {
                CLR_READYFORDISPLAY();
                SET_OSD_READYFORDISPLAY();
                CModeSetFreeRun();
            }

            if(CModeConnectIsChange() || CModeIsChange())
                CModeResetMode();

            break;

        case _NOSIGNAL_STATE:
            if(GET_READYFORDISPLAY() == _TRUE)
            {
                CLR_READYFORDISPLAY();
                SET_OSD_READYFORDISPLAY();
                CModeSetFreeRun();
#if(_SCALER_TYPE == _RTD2547D && _HDMI_SUPPORT)
				if ((CGetSourcePortType(stSystemData.InputSource) == _HDMI_PORT)) 
				{
					CScalerPageSelect(_PAGE2);
					CScalerSetBit(_P2_Z0_CALIBRATION_CTRL_AC, ~_BIT6, 0x00);
					CTimerDelayXms(500);
					CScalerSetBit(_P2_Z0_CALIBRATION_CTRL_AC, ~_BIT6, _BIT6);
				}
#endif				
            }

#if(_VIDEO_SUPPORT && _VIDEO_CHIP == _VDC_TB1334)
            if (bSourceVideo()) 
            {
                if (gmi_CSourceScanInputPortVideo())
                {
  #if(_VIDEO_TV_SUPPORT)
                    ucVideoNoModeTime = 253;
  #endif
                    CModeResetMode();
                }
            }        
            else
#endif
            {
                if(CModeConnectIsChange() || CSourceHandler())
                    CModeResetMode();
            }

            break;

        case _SLEEP_STATE:
#if(_VIDEO_SUPPORT && _VIDEO_CHIP == _VDC_TB1334)
            if (bSourceVideo()) 
            {
                if(gmi_CSourceScanInputPortVideo())
                {
                    CPowerLVDSOn();
        
                    CModeResetMode();
                }        
            }        
            else
#endif
            {
                if(CModeConnectIsChange() || CSourceHandler())
                {
    #if (_OUTPUT_BUS == _PANEL_TTL)   // For sleep up color error bug
                    CPowerLVDSOn();
    #endif
    
                    CModeResetMode();
                }
            }
            break;

        default:
            break;
    }
}

//----------------------------------------------------------------------------------------------------
// Measure Functions
//----------------------------------------------------------------------------------------------------

//--------------------------------------------------
// Description  : Check measure ready process
// Input Value  : None
// Output Value : Return _TRUE if measure finished, _FALSE if timeout
//--------------------------------------------------
bit CModeMeasureReady(void)
{
    CScalerSetBit(_SYNC_SELECT_47, ~_BIT0, 0x00);
    CAdjustSyncProcessorMeasureStart();

    if(CTimerPollingEventProc(60, CMiscModeMeasurePollingEvent))
    {
        return _TRUE;
    }
    else
    {
        CScalerSetBit(_MEAS_HS_PERIOD_H_52, ~_BIT5, 0x00);
        return _FALSE;
    }
}
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

    // Pop up measurement result
    CScalerSetBit(_MEAS_HS_PERIOD_H_52, ~_BIT6, _BIT6);

#if((_SCALER_TYPE == _RTD2553V) || (_SCALER_TYPE == _RTD2546N)) 

    CScalerRead(_MEAS_HS_PERIOD_H_52, 7, &pData[8], _AUTOINC);
    // Calculate measurement result
    ((WORD *)pData)[0] = ((pData[8] & 0x1f) << 8) | pData[9];
    ((WORD *)pData)[1] = ((pData[10] & 0x1f) << 8) | pData[11];
    ((WORD *)pData)[2] = ((pData[12] & 0x0f) << 8) | pData[13];
    ((WORD *)pData)[3] = ((pData[12] & 0xf0) << 4) | pData[14];

#elif(_SCALER_TYPE == _RTD2525L || _SCALER_TYPE == _RTD2547D)

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
} 
//----------------------------------------------------------------------------------------------------
// Mode Detect Functions
//----------------------------------------------------------------------------------------------------


//--------------------------------------------------
// Description  : Mode detect process
// Input Value  : None
// Output Value : Return _TRUE if we get a stable mode
//--------------------------------------------------
bit CModeDetect(void)
{
    switch(CGetSourcePortType(_GET_INPUT_SOURCE()))
    {
        case _DSUB_A0_PORT:
        case _DSUB_A1_PORT:
#if((_TMDS_SUPPORT == _ON) || (_HDMI_SUPPORT == _ON))
        case _DVI_PORT:
        case _DVI_I_A0_PORT:
        case _DVI_I_A1_PORT:
        case _HDMI_PORT:
#endif

#if(_YPBPR_SUPPORT == _ON)
        case _YPBPR_A0_PORT:
        case _YPBPR_A1_PORT:
#endif
                        
#if(_VIDEO_SUPPORT && _VIDEO_CHIP == _VDC_TB1334)
            if (bSourceVideo())
            {
                if (gmi_CVideoModeChange())
                {               
                    switch(VideoType)
                    {
                    case _60HZ:     
                        stModeInfo.ModeCurr = 0;    
                        break;

                    case _50HZ:
                        stModeInfo.ModeCurr = 1;    
                        break;
                    }
                
                
                    stModeUserData.HPosition    = tVIDEO_INPUTMODE_PRESET_TABLE[stModeInfo.ModeCurr].IHStartPos;
                    stModeUserData.VPosition    = tVIDEO_INPUTMODE_PRESET_TABLE[stModeInfo.ModeCurr].IVStartPos;
                    stModeUserData.Clock        = tVIDEO_INPUTMODE_PRESET_TABLE[stModeInfo.ModeCurr].IHTotal;
                    stModeUserData.Phase        = 0;

                    return _TRUE;
                }
            }
            else
#endif   

            {
                if(CModeDetectCommon()) 
                    return _TRUE;
            }
            break;

 /*       case _SOURCE_VIDEO8: 

#if(_VIDEO_SUPPORT)
            if (CModeDetectCommon())
            {
                if (gmi_CVideoModeChange())
			        return _TRUE;
            }
#endif
			break;*/
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Mode detect process for VGA and DVI
// Input Value  : None
// Output Value : Return _TRUE if we get a stable mode
//--------------------------------------------------
bit CModeDetectCommon(void)
{
    BYTE modetemp = _MODE_NOSIGNAL;
    BYTE polaritytemp;
    WORD hcount, vtotal;

    if(CModeMeasureReady())
    {
        polaritytemp    = stModeInfo.Polarity;
        hcount          = stModeInfo.IHCount;
        vtotal          = stModeInfo.IVTotal;

        // Get measure results and decide " modetemp = _MODE_NOSIGNAL/_MODE_NOSUPPORT/_MODE_EXIST "
        if(CModeMeasureData())
        {
            CSyncModifyPolarityVGA();

            stModeInfo.ModeCurr = _MODE_NOSIGNAL;

            if(abs(stModeInfo.IHCount - hcount) <= 1)
                stModeInfo.IHCount = hcount;

            if(abs(stModeInfo.IVTotal - vtotal) <= 2) 
                stModeInfo.IVTotal = vtotal;

            if((stModeInfo.IHCount != hcount) || (stModeInfo.IVTotal != vtotal) || (stModeInfo.Polarity != polaritytemp))
            {
                modetemp    = _MODE_NOSIGNAL;
            }
            else
            {
                if((stModeInfo.IHFreq < Panel.H_FREQ_Min) || (stModeInfo.IHFreq > Panel.H_FREQ_Max) || (stModeInfo.IVFreq < Panel.V_FREQ_Min) || (stModeInfo.IVFreq >Panel.V_FREQ_Max))
		//if((stModeInfo.IHFreq < _H_FREQ_MIN) || (stModeInfo.IHFreq > _H_FREQ_MAX) || (stModeInfo.IVFreq < _V_FREQ_MIN) || (stModeInfo.IVFreq > _V_FREQ_MAX))
                {
                    modetemp    = _MODE_NOSUPPORT;
                }
                else
                {
//                    if(((GET_INPUTPORT_TYPE(_GET_INPUT_SOURCE()) == _YPBPR_A0_PORT) || (GET_INPUTPORT_TYPE(_GET_INPUT_SOURCE()) == _YPBPR_A1_PORT)) && ((bit)CScalerGetBit(_SYNC_SELECT_47, _BIT6)))
//                        modetemp    = _MODE_NOSUPPORT;
//                    else
                        modetemp    = _MODE_EXIST;
                }
            }
        }
        else
        {
            modetemp    = _MODE_NOSIGNAL;
        }

        // Wait mode stable and decide the mode type for current source
        if(modetemp != ucModeFound)
        {
            ucModeFound = modetemp;
            ucEvent1 = _INACTIVE_COUNTDOWN_EVENT;
            CLR_MODESTABLE();
            CTimerCountDownEventProc(&ucEvent1, 3, CModeStableCountDownEvent);

            return _FALSE;
        }
        else
        {
            CTimerCountDownEventProc(&ucEvent1, 3, CModeStableCountDownEvent);

            if(GET_MODESTABLE())
            {
                if(ucModeFound == _MODE_EXIST)
                {
                    stModeInfo.ModeCurr = CModeSearchDisplayMode();
                }
                else
                {
                    stModeInfo.ModeCurr = ucModeFound;
                }

                return _TRUE;
            }
            else
            {
                return _FALSE;
            }
        }
    }
    else
    {
        return _FALSE;
    }
}

//--------------------------------------------------
// Description  : Check if mode is changed
// Input Value  : None
// Output Value : Return _TRUE if mode is changed
//--------------------------------------------------
bit CModeIsChange(void)
{
    BYTE polaritytemp;
    WORD hcount, vtotal;

    polaritytemp    = stModeInfo.Polarity;
    hcount          = stModeInfo.IHCount;
    vtotal          = stModeInfo.IVTotal;

    if((CGetSourcePortType(_GET_INPUT_SOURCE()) == _DSUB_A0_PORT || CGetSourcePortType(_GET_INPUT_SOURCE()) == _DSUB_A1_PORT))
    {
#if (_SCALER_TYPE == _RTD2553V || _SCALER_TYPE == _RTD2546N || _SCALER_TYPE == _RTD2525L || _SCALER_TYPE == _RTD2547D)
        if(CScalerGetBit(_HSYNC_TYPE_DETECTION_FLAG_4E, _BIT6 | _BIT5))
#else
        if(CScalerGetBit(_STABLE_PERIOD_H_50, _BIT6 | _BIT5))
#endif
            return _TRUE;
    }
    if(CModeMeasureData())
    {
        if(abs(stModeInfo.IHCount - hcount) <= 1)
            stModeInfo.IHCount = hcount;

        if(abs(stModeInfo.IVTotal - vtotal) <= 2)
            stModeInfo.IVTotal = vtotal;

        if((stModeInfo.IHCount != hcount) || (stModeInfo.IVTotal != vtotal) || (stModeInfo.Polarity != polaritytemp))
        {
            return _TRUE;
        }
        else
        {
            return _FALSE;
        }
    }
    else
    {
        return _TRUE;
    }
}

//--------------------------------------------------
// Description  : Search display mode process
// Input Value  : None
// Output Value : Mode number
//--------------------------------------------------
BYTE CModeSearchDisplayMode(void)
{
    BYTE modetemp;

    switch(CGetSourcePortType(_GET_INPUT_SOURCE()))
    {
        case _DSUB_A0_PORT:
        case _DSUB_A1_PORT:
            modetemp    = CModeSearchModeVGA();
            break;

#if(_YPBPR_SUPPORT == _ON)

        case _YPBPR_A0_PORT:
        case _YPBPR_A1_PORT:
            modetemp    = CYPbPrSearchMode();
            break;

#endif

#if((_TMDS_SUPPORT == _ON) || (_HDMI_SUPPORT == _ON))

        case _DVI_PORT:
        case _DVI_I_A0_PORT:
        case _DVI_I_A1_PORT:
        case _HDMI_PORT:
            modetemp    = CModeSearchModeDVI();
            break;

#endif
    //    case _SOURCE_VIDEO8:
        //    break;
    }

    return modetemp;
}

//--------------------------------------------------
// Description  : Search mode for VGA
// Input Value  : None
// Output Value : Mode number
//--------------------------------------------------
BYTE CModeSearchModeVGA(void)
{
    BYTE modecnt;

    SET_MODE_SEARCH_TYPE(_PRESET_MODE_TYPE);
      
    for(modecnt=0;modecnt<_MAX_PRESET_MODE;modecnt++)
    {
        if(CModeComparePresetModeVGA(modecnt))
        {

		 	
           if(modecnt==_MODE_1024x768_60HZ&&(stModeInfo.IHSyncPulseCount>=30&&stModeInfo.IHSyncPulseCount<=38))
                    return _MODE_1360X768_60HZ;
		   else
            return modecnt;
        }
    }

#if(_VIDEO_SUPPORT && _VIDEO_CHIP == _VDC_TB1334)
    if (!bSourceVideo())        
#endif
    {
        modecnt = CModeSearchAcceptiveModeVGA();
    }

    if((modecnt == _MODE_NOSIGNAL) || (modecnt == _MODE_NOSUPPORT))
        return modecnt;
 
    SET_MODE_SEARCH_TYPE(_USER_MODE_TYPE);

#if(_VIDEO_SUPPORT && _VIDEO_CHIP == _VDC_TB1334)
    if (!bSourceVideo())
#endif
    {
        modecnt = CModeCheckFIFOModeVGA(modecnt);
    }

    return modecnt;
}

//--------------------------------------------------
// Description  : Compare preset VGA mode
// Input Value  : Mode number
// Output Value : Return _TRUE if the input mode number is correspondence
//--------------------------------------------------
bit CModeComparePresetModeVGA(BYTE ucModeCnt)
{
    BYTE polarity, polaritytemp;

#if (_SCALER_TYPE == _RTD2553V || _SCALER_TYPE == _RTD2546N || _SCALER_TYPE == _RTD2525L || _SCALER_TYPE == _RTD2547D)

#if(_VIDEO_SUPPORT && _VIDEO_CHIP == _VDC_TB1334)
    if (bSourceVideo())
    {
        polarity = stModeInfo.Polarity;
        if((bit)CScalerGetBit(_SYNC_INVERT_48, _BIT3))
            polarity = (polarity ^ _BIT0);
    }
    else
#endif  // #if(_VIDEO_SUPPORT && _VIDEO_CHIP == _VDC_TB1334)
    {
  #if(_HSYNC_TYPE_DETECTION == _AUTO_RUN)

        polarity = (stModeInfo.Polarity & ~_BIT0) | (ucStablePol & _BIT0);

  #endif	//End of #if(_HSYNC_TYPE_DETECTION == _AUTO_RUN)


  #if(_HSYNC_TYPE_DETECTION == _NORMAL_RUN)
    
        polarity = stModeInfo.Polarity;
        if((bit)CScalerGetBit(_SYNC_INVERT_48, _BIT3))
            polarity = (polarity ^ _BIT0);

  #endif	// End of #if(_HSYNC_TYPE_DETECTION == _NORMAL_RUN)
    }

#else
    polarity = stModeInfo.Polarity;

    if((bit)CScalerGetBit(_SYNC_INVERT_48, _BIT3))
        polarity = (polarity ^ _BIT0);
#endif

#if(_VIDEO_SUPPORT && _VIDEO_CHIP == _VDC_TB1334)
    if (!bSourceVideo())
#endif
    {        
        if(abs(stModeInfo.IVFreq - tINPUTMODE_PRESET_TABLE[ucModeCnt].IVFreq) > tINPUTMODE_PRESET_TABLE[ucModeCnt].IVFreqTolerance)
        {
            return _FALSE;
        }
    }
#if(_VIDEO_SUPPORT && _VIDEO_CHIP == _VDC_TB1334)
    else
    {
        if(abs(stModeInfo.IVFreq - tVIDEO_INPUTMODE_PRESET_TABLE[ucModeCnt].IVFreq) > tVIDEO_INPUTMODE_PRESET_TABLE[ucModeCnt].IVFreqTolerance)
        {
            return _FALSE;
        }
    }
#endif

#if(_VIDEO_SUPPORT && _VIDEO_CHIP == _VDC_TB1334)
    if (!bSourceVideo())
#endif
    {        
        if(abs(stModeInfo.IHFreq - tINPUTMODE_PRESET_TABLE[ucModeCnt].IHFreq) > tINPUTMODE_PRESET_TABLE[ucModeCnt].IHFreqTolerance)
        {
            return _FALSE;
        }
    }
#if(_VIDEO_SUPPORT && _VIDEO_CHIP == _VDC_TB1334)
    else
    {
        if(abs(stModeInfo.IHFreq - tVIDEO_INPUTMODE_PRESET_TABLE[ucModeCnt].IHFreq) > tVIDEO_INPUTMODE_PRESET_TABLE[ucModeCnt].IHFreqTolerance)
        {
            return _FALSE;
        }
    }
#endif

    if((bit)(polarity & _BIT0))
    {
        if((bit)(polarity & _BIT1))
            polaritytemp    = _SYNC_HP_VP;
        else
            polaritytemp    = _SYNC_HP_VN;
    }
    else
    {
        if((bit)(polarity & _BIT1))
            polaritytemp    = _SYNC_HN_VP;
        else
            polaritytemp    = _SYNC_HN_VN;
    }

#if(_VIDEO_SUPPORT && _VIDEO_CHIP == _VDC_TB1334)
    if (!bSourceVideo())
#endif
    {        
        if((polaritytemp & tINPUTMODE_PRESET_TABLE[ucModeCnt].PolarityFlag) == 0x00)
            return _FALSE;
    }
#if(_VIDEO_SUPPORT && _VIDEO_CHIP == _VDC_TB1334)
    else
    {
        if((polaritytemp & tVIDEO_INPUTMODE_PRESET_TABLE[ucModeCnt].PolarityFlag) == 0x00)
            return _FALSE;
    }
#endif

    return _TRUE;

}

//--------------------------------------------------
// Description  : Search an acceptive mode
// Input Value  : None
// Output Value : Mode number
//--------------------------------------------------
BYTE CModeSearchAcceptiveModeVGA(void)
{
    BYTE acceptivemode = _MODE_NOSUPPORT;

    if(stModeInfo.IVTotal < 420)
    {

    }
    else if(stModeInfo.IVTotal < 488)                   // 720x400 Mode : Vertical Line < 488
    {
        if(stModeInfo.IVFreq < 740)
            acceptivemode = _MODE_720x400_70HZ;
        else if(stModeInfo.IVFreq < 790)
            acceptivemode = _MODE_720x400_70HZ;
        else
            acceptivemode = _MODE_720x400_85HZ;
    }
    else if(stModeInfo.IVTotal < 610)              // 640x480 Mode : 488 <= Vertical Line < 610
    {
        if(stModeInfo.IVFreq < 640)
            acceptivemode = _MODE_640x480_60HZ;
        else if(stModeInfo.IVFreq < 690)
            acceptivemode = _MODE_640x480_66HZ;
        else if(stModeInfo.IVFreq < 740)
            acceptivemode = _MODE_640x480_72HZ;
        else if(stModeInfo.IVFreq < 790)
            acceptivemode = _MODE_640x480_75HZ;
        else
            acceptivemode = _MODE_640x480_85HZ;
	}
    else if(stModeInfo.IVTotal < 660)              // 800x600 Mode : 610 <= Vertical Line < 660
    {
        if(stModeInfo.IVFreq < 580)
            acceptivemode = _MODE_800x600_56HZ;
        else if(stModeInfo.IVFreq < 660)
            acceptivemode = _MODE_800x600_60HZ;
        else if(stModeInfo.IVFreq < 740)
            acceptivemode = _MODE_800x600_72HZ;
        else if(stModeInfo.IVFreq < 790)
            acceptivemode = _MODE_800x600_75HZ;
        else
            acceptivemode = _MODE_800x600_85HZ;
	}
    else if(stModeInfo.IVTotal < 732)              // 832x624 Mode : 660 <= Vertical Line < 732
    {
        if(stModeInfo.IVFreq < 740)
            acceptivemode = _MODE_800x600_72HZ;
        else
            acceptivemode = _MODE_832x624_75HZ;
	}
    else if(stModeInfo.IVTotal < 780)              // 1280x720 Mode : 732 <= Vertical Line < 780
    {
        if(stModeInfo.IVFreq < 740)
            acceptivemode = _MODE_1280x720_60HZ;
        else
            acceptivemode = _MODE_1280x720_75HZ;
	}
    else if(stModeInfo.IVTotal < 881)              // 1024x768 Mode : 780 <= Vertical Line < 881
    {
        if(stModeInfo.IVFreq < 650)
            //acceptivemode = _MODE_1024x768_60HZ;
            acceptivemode = _MODE_1280x768_60HZ;
        else if(stModeInfo.IVFreq < 730)
            acceptivemode = _MODE_1024x768_70HZ;
        else if(stModeInfo.IVFreq < 790)
            acceptivemode = _MODE_1024x768_75HZ;
        else
            acceptivemode = _MODE_1024x768_85HZ;
	}
    else if(stModeInfo.IVTotal < 932)              // 1152x864/870 Mode : 881 <= Vertical Line < 932
    {
        if((stModeInfo.IHFreq > 679) && (stModeInfo.IHFreq < 697))
        {
            acceptivemode = _MODE_1152x870_75HZ;
        }
        else
        {
            if(stModeInfo.IVFreq < 650)
                acceptivemode = _MODE_1152x864_60HZ;
            else if(stModeInfo.IVFreq < 740)
                acceptivemode = _MODE_1152x864_70HZ;
            else if(stModeInfo.IVFreq < 790)
                acceptivemode = _MODE_1152x864_75HZ;
            else
                acceptivemode = _MODE_1152x864_85HZ;
        }
    }
    else if(stModeInfo.IVTotal < 975)
    {
        if(stModeInfo.IVFreq < 680)
            acceptivemode = _MODE_1152x900_66HZ;
	}
    else if(stModeInfo.IVTotal < 1040)
    {
        if(stModeInfo.IVFreq < 650)
            acceptivemode = _MODE_1280x960_60HZ;
        else
            acceptivemode = _MODE_1280x960_75HZ;
	}
    else if(stModeInfo.IVTotal < 1100)             // 1280x1024 Mode :
    {
        if(stModeInfo.IVFreq < 680)
            acceptivemode = _MODE_1280x1024_60HZ;
        else if(stModeInfo.IVFreq < 720)
            acceptivemode = _MODE_1280x1024_70HZ;
        else if(stModeInfo.IVFreq < 780)
            acceptivemode = _MODE_1280x1024_75HZ;
        else
            acceptivemode = _MODE_1280x1024_85HZ;
	}
    else if(stModeInfo.IVTotal < 1300)             // 1600x1200 Mode :
    {
        if(stModeInfo.IVFreq < 630)
            acceptivemode = _MODE_1600x1200_60HZ;
        else if(stModeInfo.IVFreq < 680)
            acceptivemode = _MODE_1600x1200_65HZ;
        else if(stModeInfo.IVFreq < 720)
            acceptivemode = _MODE_1600x1200_70HZ;
        else if(stModeInfo.IVFreq < 780)
            acceptivemode = _MODE_1600x1200_75HZ;
        else
            acceptivemode = _MODE_1600x1200_85HZ;
    }

    return acceptivemode;
}

//--------------------------------------------------
// Description  : Check FIFO mode for VGA
// Input Value  : Mode number
// Output Value : FIFO mode number
//--------------------------------------------------
BYTE CModeCheckFIFOModeVGA(BYTE ucModeCnt)
{
    BYTE cnt0, cnt1;
    StructModeUserFIFODataType stFIFOModeTemp;

    for(cnt0=0;cnt0<4;cnt0++)
    {
        CEepromLoadUserFIFOModeData(cnt0, pData);

        for(cnt1=0;cnt1<4;cnt1++)
        {
            if(CModeCompareFIFOModeVGA(cnt1, ucModeCnt) == _TRUE)
            {
                return (cnt0 * 4 + cnt1);
            }
        }
    }

    if(stSystemData.UserFIFOMode >= 15)
        stSystemData.UserFIFOMode = 0;
    else
        stSystemData.UserFIFOMode++;

    stFIFOModeTemp.ModeNum = ucModeCnt;
    stFIFOModeTemp.IHFreq  = stModeInfo.IHFreq;
    stFIFOModeTemp.IVFreq  = stModeInfo.IVFreq;
    CEepromSaveUserFIFOModeData(stFIFOModeTemp);

    stModeUserData.FirstAuto    = 0;
    stModeUserData.HPosition    = tINPUTMODE_PRESET_TABLE[ucModeCnt].IHStartPos;
    stModeUserData.VPosition    = tINPUTMODE_PRESET_TABLE[ucModeCnt].IVStartPos;
    stModeUserData.Clock        = tINPUTMODE_PRESET_TABLE[ucModeCnt].IHTotal;
    stModeUserData.Phase        = 0;
    CEepromSaveModeData(stSystemData.UserFIFOMode);

    CEepromSaveSystemData();

    return stSystemData.UserFIFOMode;
}

//--------------------------------------------------
// Description  : Compare mode in FIFO memory
// Input Value  : Mode number and FIFO mode number
// Output Value : _TRUE if both are correspondence
//--------------------------------------------------
bit CModeCompareFIFOModeVGA(BYTE ucNum, BYTE ucModeCnt)
{
    StructModeUserFIFODataType stFIFOModeTemp;

    stFIFOModeTemp.ModeNum = (pData[ucNum * 4]);
    stFIFOModeTemp.IHFreq  = ((WORD)(pData[ucNum * 4 + 1] & 0x0f) << 8) | pData[ucNum * 4 + 2];
    stFIFOModeTemp.IVFreq  = ((WORD)(pData[ucNum * 4 + 1] & 0xf0) << 4) | pData[ucNum * 4 + 3];

    if(stFIFOModeTemp.ModeNum != ucModeCnt)
        return _FALSE;

    if(abs(stModeInfo.IVFreq - stFIFOModeTemp.IVFreq) > tINPUTMODE_PRESET_TABLE[ucModeCnt].IVFreqTolerance)
        return _FALSE;

    if(abs(stModeInfo.IHFreq - stFIFOModeTemp.IHFreq) > tINPUTMODE_PRESET_TABLE[ucModeCnt].IHFreqTolerance)
        return _FALSE;

    return _TRUE;
}

#if((_TMDS_SUPPORT == _ON) || (_HDMI_SUPPORT == _ON))
//--------------------------------------------------
// Description  : Search mode for DVI
// Input Value  : None
// Output Value : Mode number
//--------------------------------------------------
BYTE CModeSearchModeDVI(void)
{
    BYTE modecnt = 0;

    CScalerSetBit(_SYNC_SELECT_47, ~_BIT0, _BIT0);
    CAdjustSyncProcessorMeasureStart();

    if(CTimerPollingEventProc(60, CMiscModeMeasurePollingEvent))
    {          
        CScalerSetBit(_MEAS_HS_PERIOD_H_52, ~_BIT6, _BIT6);

#if((_SCALER_TYPE == _RTD2553V) || (_SCALER_TYPE == _RTD2546N)) 

        CScalerRead(_MEAS_HS_PERIOD_H_52, 7, &pData[8], _AUTOINC);

        ((WORD *)pData)[0] = ((WORD)(pData[8] & 0x1f) << 8) | pData[9];
        ((WORD *)pData)[1] = ((WORD)(pData[10] & 0x1f) << 8) | pData[11];
        ((WORD *)pData)[2] = ((WORD)(pData[12] & 0x0f) << 8) | pData[13];

#elif(_SCALER_TYPE == _RTD2525L)

        CScalerSetBit(_MEAS_VS_HIGH_PERIOD_L_58, ~_BIT0, 0x00); //V305 modify
        CScalerRead(_MEAS_HS_PERIOD_H_52, 6, &pData[8], _AUTOINC);

        ((WORD *)pData)[0] = ((pData[8] & 0x1f) << 8) | pData[9]; //V305 modify 
        ((WORD *)pData)[1] = ((pData[10] & 0x1f) << 8) | pData[11]; //V305 modify 
        ((WORD *)pData)[2] = ((pData[12] & 0xf0) << 4) | pData[13];

#elif(_SCALER_TYPE == _RTD2547D)

        CScalerSetBit(_MEAS_VS_HIGH_PERIOD_L_58, ~_BIT0, 0x00);
        CScalerRead(_MEAS_HS_PERIOD_H_52, 6, &pData[8], _AUTOINC);

        ((WORD *)pData)[0] = ((WORD)(pData[8] & 0x1f) << 8) | pData[9];
        ((WORD *)pData)[1] = ((WORD)(pData[10] & 0x1f) << 8) | pData[11];
        ((WORD *)pData)[2] = ((WORD)(pData[12] & 0xf0) << 4) | pData[13];

#else

        CScalerRead(_MEAS_HS_PERIOD_H_52, 7, &pData[8], _AUTOINC);

        ((WORD *)pData)[0] = ((WORD)(pData[8] & 0x1f) << 8) | pData[9];
        ((WORD *)pData)[1] = ((WORD)(pData[10] & 0x1f) << 8) | pData[11];
        ((WORD *)pData)[2] = ((WORD)(pData[12] & 0x0f) << 8) | pData[13];

#endif  // End of #if((_SCALER_TYPE == _RTD2553V) || (_SCALER_TYPE == _RTD2546N))

        if((((WORD *)pData)[0] >=  0x0fff) || (((WORD *)pData)[1] >= 0x0fff) || (((WORD *)pData)[0] == 0) || (((WORD *)pData)[1] == 0)  || (bit)(pData[10] & _BIT5))
        {
            modecnt = _MODE_NOSUPPORT;
        }
        else
        {
            // Save IH_TOTAL
            stModeInfo.IHTotal  = ((WORD *)pData)[0] + 1;

            // Save input data enable width and height
            stModeInfo.IVHeight = ((WORD *)pData)[1] + 1;
            stModeInfo.IHWidth  = ((WORD *)pData)[2] + 1;

            for(modecnt=0;modecnt<_MAX_PRESET_MODE;modecnt++)
            {                 
                if(CModeCompareModeDVI(modecnt))
                {
#if(_TMDS_SHRINK_SUPPORT == _ON) //Ming-Yen
                    if(CGetSourcePortType(_GET_INPUT_SOURCE()) == _HDMI_PORT)
                    {
                        stModeInfo.IVHeight = stModeInfo.IVHeight - (_TMDS_SHRINK_RANGE * 2); 
                        stModeInfo.IHWidth = stModeInfo.IHWidth - (_TMDS_SHRINK_RANGE * 2); 
                    }
#endif  // End of  #if(_TMDS_SHRINK_SUPPORT == _ON)
                    break;
                }
            }
        }
    }
    else
    {
        CScalerSetBit(_MEAS_HS_PERIOD_H_52, ~_BIT5, 0x00);
        modecnt = _MODE_NOSUPPORT;
    }

    CScalerSetBit(_SYNC_SELECT_47, ~_BIT0, 0x00);

    // We don't support input image less than 350 active lines
    if(stModeInfo.IVHeight < 350)
    {
        modecnt = _MODE_NOSUPPORT;
    }
    // If no mode found, set to mode 0
    else if(modecnt >= _MAX_PRESET_MODE)
    {
        modecnt = 0;
    }

#if(_SCALER_TYPE == _RTD2547D)

    // We don't support input image large than 2048 active pixel
    if((stModeInfo.IHWidth > 2048))
        modecnt = _MODE_NOSUPPORT;

  #if(_FRC_SUPPORT == _ON)
    ((DWORD *)pData)[0] = (DWORD)(stModeInfo.IHWidth) * (DWORD)(stModeInfo.IVHeight) * ((DWORD)stModeInfo.IVFreq + _PANEL_MAX_FRAME_RATE) / 10 / 85 * 100 / _MEMORY_BIT_NUM * 24;
    if(((DWORD *)pData)[0] > (DWORD)_MEMORY_SPEED * 1000000)//Frame Sync
        CLR_FRCTATUS();
    else//FRC
        SET_FRCTATUS();
  #else
    CLR_FRCTATUS();
  #endif  

#endif

    return modecnt;
}
         
//--------------------------------------------------
// Description  : Compare mode for DVI
// Input Value  : Mode number
// Output Value : Retrun _TRUE if it's correspondence
//--------------------------------------------------
bit CModeCompareModeDVI(BYTE ucModeCnt)
{
    if(stModeInfo.IHWidth != tINPUTMODE_PRESET_TABLE[ucModeCnt].IHWidth)
        return _FALSE;

    if(stModeInfo.IVHeight != tINPUTMODE_PRESET_TABLE[ucModeCnt].IVHeight)
        return _FALSE;

    if(abs(stModeInfo.IVFreq - tINPUTMODE_PRESET_TABLE[ucModeCnt].IVFreq) > tINPUTMODE_PRESET_TABLE[ucModeCnt].IVFreqTolerance)
        return _FALSE;

    return _TRUE;
}                           
#endif  // End of #if((_TMDS_SUPPORT == _ON) || (_HDMI_SUPPORT == _ON))

//----------------------------------------------------------------------------------------------------
// Mode Display Functions
//----------------------------------------------------------------------------------------------------

//--------------------------------------------------
// Description  : Display active mode process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CModeDisplayActiveMode(void)
{
    switch(CGetSourcePortType(_GET_INPUT_SOURCE()))
    {
        case _DSUB_A0_PORT:
#if (_VIDEO_SUPPORT == _ON && _SCALER_TYPE == _RTD2553V)  // eric 1219 move
            CScalerSetBit(_VSYNC_COUNTER_LEVEL_MSB_4C, ~_BIT3, _BIT3);
#endif
        case _DSUB_A1_PORT:
            CModeSetupModeVGA();
            break;

#if(_YPBPR_SUPPORT == _ON)

        case _YPBPR_A0_PORT:
        case _YPBPR_A1_PORT:
            CYPbPrSetupMode();
            break;

#endif

#if((_TMDS_SUPPORT == _ON) || (_HDMI_SUPPORT == _ON))

        case _DVI_PORT:
        case _DVI_I_A0_PORT:
        case _DVI_I_A1_PORT:
        case _HDMI_PORT:
            CModeSetupModeDVI();
            break;
#endif

/*        case _SOURCE_VIDEO8:
#if(_VIDEO_SUPPORT)
            CVideoDisplaySet(1); 
#endif          
            break;*/
    }

}


//--------------------------------------------------
// Description  : Setup VGA mode
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CModeSetupModeVGA(void)
{
    BYTE option = 0;
    if (bSourceVideo())
    {
#if(_VIDEO_SUPPORT && _VIDEO_CHIP == _VDC_TB1334)
        CSetTB1334VideoMode();
#endif
    }
    // Get information from mode table, such as IHTotal, IHStartPos, IHWidth, IVStartPos, IVHeight.
    CModeGetModeTableInfo();

    // Start up settings of VGA mode.
    CModeStartUpVGA();

    // Get scaling option, Capture window setup, Scaling setup, Display setup
    CModeSetupDisplay();

#if(_VIDEO_SUPPORT && _VIDEO_CHIP == _VDC_TB1334)
    if (bSourceVideo())
        CLoadVideoModeData();
    else
#endif
    // Load mode user data from eeprom
    CEepromLoadModeData(stModeInfo.ModeCurr);

#if(_VIDEO_SUPPORT && _VIDEO_CHIP == _VDC_TB1334)
    if (bSourceVideo())
       CSetVideoColor();
    else
#endif
    {
        // Setup color processing
        CModeSetupColorProcess();
    
        CAdjustBacklight();
        CEepromLoadAdcData(); // eric add
        CAdjustAdcGainOffset();
    }
    CAdjustAdcClock(stModeUserData.Clock);

//V308 modify
#if(_SCALER_TYPE == _RTD2525L)
    if((bit)CScalerGetBit(_SYNC_SELECT_47, _BIT4))
    {
        CScalerSetDataPortBit(_ADC_ACCESS_PORT_DC, 0x0c, ~_BIT7, _BIT7);
        CScalerSetByte(_ADC_ACCESS_PORT_DC,0x8e); 
        CScalerSetByte(_ADC_DATA_PORT_DD,0x00);
        CTimerDelayXms(20);    
    }
#endif
//V308 modify

    CAdjustPhase(stModeUserData.Phase);
    CAdjustHPosition();
    CModeModifyVTotal();
    CAdjustVPosition();

#if (_SCALER_TYPE == _RTD2553V || _SCALER_TYPE == _RTD2546N || _SCALER_TYPE == _RTD2525L || _SCALER_TYPE == _RTD2547D)
  #if (_SCALER_TYPE == _RTD2547D)
    CScalerPageSelect(_PAGE0); //V401 modify
    CScalerSetBit(_P0_ADC_CTRL_A1, ~(_BIT5 | _BIT4), (ucAdcPGA << 4) & 0x30); //V401 modify 
  #else
    CScalerSetDataPortBit(_ADC_ACCESS_PORT_DC, 0x00, ~(_BIT5 | _BIT4), (ucAdcPGA << 4) & 0x30); //V401 modify 
  #endif
#if ((_ADC_OFFSET_ADJUSTING == _ADJUST_BY_HW_OFF_LINE) && (_SCALER_TYPE == _RTD2525L || _SCALER_TYPE == _RTD2547D))
    CAutoAdjustAdcOffset();
    CEepromSaveAdcData();
//    COsdDispShowFactoryModeValue();
#endif 
#else 
    CScalerSetBit(_ADC_RGB_CTRL_DC, ~(_BIT5 | _BIT4), (ucAdcPGA << 4) & 0x30); //V401 modify 
#endif

#if(_VIDEO_SUPPORT && _VIDEO_CHIP == _VDC_TB1334)
    if (bSourceVideo())
    {
       CTB1334VideoMode(VideoType, _SCALER_TYPE);              
    }
#endif

#if(_SCALER_TYPE == _RTD2547D)
    if(!GET_FRCTATUS())
    {
        CModeSetFIFOForFrameSync();

        pData[0] = CFrameSyncDo();
#else
    pData[0] = CFrameSyncDo();
    {
#endif

#if(_VIDEO_SUPPORT && _VIDEO_CHIP == _VDC_TB1334)
    if (!bSourceVideo())
#endif
        {
            if(pData[0] == 2)
            {
                CModeResetMode();
                return;
            }
        }
    }

    CModeSetupEtcs(_FUNCTION_ENABLE);
}

#if((_TMDS_SUPPORT == _ON) || (_HDMI_SUPPORT == _ON))
//--------------------------------------------------
// Description  : Setup mode DVI
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CModeSetupModeDVI(void)
{
    BYTE option = 0;
#if(_SCALER_TYPE == _RTD2547D)
    WORD ustemp;
    BYTE temp;
#endif

    // Do initial settings of DVI mode.
    CModeStartUpDVI();

    // Get scaling option, Capture window setup, Scaling setup, Display setup
    CModeSetupDisplay();

    // Setup color processing
    CModeSetupColorProcess();

    CAdjustBacklight();

#if(_SCALER_TYPE == _RTD2547D)  

    CAdjustPeakingFilterForVideo(0); // Disable HDMI peaking

    //For Digital Interlace Mode Compensation
    CScalerPageSelect(_PAGE2);

    //Issac 2006-09-12
    if(GET_INTERLACE_MODE())
    {
        CScalerSetBit(_SCALE_CTRL_32, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
        CScalerPageSelect(_PAGE5);
        CScalerSetBit(_P5_SDRF_IN1_SDR_CTRL_B9, ~_BIT7, _BIT7);//For interlace mode odd field toggle

        // Issac added for interlaced mode last-line compensation 2006-08-29
        CScalerRead(_IV_DV_DELAY_CLK_ODD_41, LENGTH(1), &temp, _NON_AUTOINC);
        ustemp = (WORD)temp * 16 + 16;
        ustemp += stModeInfo.IHTotal / 2;
        CScalerSetByte(_IV_DV_DELAY_CLK_EVEN_42, ((ustemp + 8) / 16) - 1);

        CScalerSetBit(_FS_DELAY_FINE_TUNING_43, ~_BIT1, _BIT1);
        // End of Issac's modification
    }

    if(!GET_FRCTATUS())
    {
        CModeSetFIFOForFrameSync();

#else
    {
#endif
        pData[0] = CFrameSyncDo();
    
        if(pData[0] == 2)
        {
            CModeResetMode();
            return;
        }
    }

#if(((_TMDS_SUPPORT == _ON) || (_HDMI_SUPPORT == _ON)) && (_DVI_LONG_CABLE_SUPPORT == _ON))

    CAdjustTMDSCRCCheck();

#endif

    CAdjustTMDSCaptureCheck();

#if(_TMDS_SHRINK_SUPPORT == _ON) //Ming-Yen
    if(CGetSourcePortType(_GET_INPUT_SOURCE()) == _HDMI_PORT && stModeInfo.ModeCurr != 0)
    {
 #if(_SCALER_TYPE == _RTD2547D)
        CScalerSetByte(_IPH_ACT_STA_L_15, _TMDS_SHRINK_RANGE);
        CScalerSetByte(_IPV_ACT_STA_L_19, _TMDS_SHRINK_RANGE);
        CScalerSetByte(_IVS2DVS_DELAY_LINES_40, _TMDS_SHRINK_RANGE);
 #else
        CScalerSetByte(_IPH_ACT_STA_L_0A, _TMDS_SHRINK_RANGE);
        CScalerSetByte(_IPV_ACT_STA_L_0E, _TMDS_SHRINK_RANGE);
        CScalerSetByte(_IVS2DVS_DELAY_LINES_40, _TMDS_SHRINK_RANGE);
 #endif
    }

#endif  // End of #if(_TMDS_SHRINK_SUPPORT == _ON)

    CModeSetupEtcs(_FUNCTION_DISABLE);
}
#endif  // End of #if((_TMDS_SUPPORT == _ON) || (_HDMI_SUPPORT == _ON))

//--------------------------------------------------
// Description  : Setup display
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CModeSetupDisplay(void)
{
    BYTE option = 0;

    // Get scaling option
    option = CModeGetScaleSetting();

    // Capture window setup
    CModeSetCaptureWindow(option);

    // Scaling setup
    CModeSetScaling(option);

    // Display setup
    CModeSetDisplay(option);
}

//--------------------------------------------------
// Description  : Setup contrast and brightness
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CModeSetupColorProcess(void)
{
    if(_GET_INPUT_SOURCE() == _SOURCE_VGA)
        CEepromLoadAdcData(); //V403 modify  

    CEepromLoadBriConData();
    CEepromLoadColorTempData();
    CAdjustBrightness();
    CAdjustContrast();
#if(_OSD_TYPE == _OSD007)
  #if(_IMAGE_COLOR_MODE)
    CSetColorMode(_GET_IMAGE_COLOR_MODE());
  #endif
#endif

#if(_SCALER_TYPE == _RTD2547D && _VGA_COLOR_SUPPORT)

    CScalerSetDataPortBit(_HW_ACCESS_PORT_60, _HW_WINDOW_CTRL0_0C, ~(_BIT7 | _BIT6 | _BIT3 | _BIT2), (_BIT7 | _BIT6 | _BIT2));
    CScalerSetDataPortBit(_HW_ACCESS_PORT_60, _HW_WINDOW_CTRL1_0D, ~(_BIT7 | _BIT6), _BIT6);
    CAdjustHLWindowBrightness(stOsdUserData.MZBright);
    CAdjustHLWindowContrast(stOsdUserData.MZContrast);

    if(GET_MZ_WINDOW_CFG_TYPE() == _MZ_WINDOW_CFG_WINDOW)
        CAdjustNormalizeFactor(stOsdUserData.MZHWidth, stOsdUserData.MZVHeight);

    CAdjustHLWindow();

#else

#if (_SCALER_TYPE == _RTD2553V || _SCALER_TYPE == _RTD2546N || _SCALER_TYPE == _RTD2525L)
#if (_VGA_COLOR_SUPPORT)
    CScalerSetDataPortBit(_HW_ACCESS_PORT_60, 0x0c, ~(_BIT7 | _BIT6 | _BIT3 | _BIT2), (_BIT7 | _BIT6 | _BIT2));
    CAdjustHLWindowBrightness(stOsdUserData.MZBright);
    CAdjustHLWindowContrast(stOsdUserData.MZContrast);

//    if(GET_MZ_WINDOW_CFG_TYPE() == _MZ_WINDOW_CFG_WINDOW)
//        CAdjustNormalizeFactor(stOsdUserData.MZHWidth, stOsdUserData.MZVHeight);

//    CAdjustHLWindow();

    CSetSACMode(GET_SAC_DCC_TYPE());

    if((GET_MZ_ICM_ON_OFF_TYPE() == _ON) && (GET_SAC_DCC_TYPE() == _SAC_DCC_USER))
    {
        CAdjustMZHueSat(0);
        CAdjustMZHueSat(1);
        CAdjustMZHueSat(2);
        CAdjustMZHueSat(3);
        CAdjustMZHueSat(4);
        CAdjustMZHueSat(5);
    }     

    if(GET_MZ_PEAKING_ON_OFF_TYPE() == _ON)
        CAdjustHLWindowPeaking(stOsdUserData.MZPeaking);   

#else
    
    // Disable vivid color
    CScalerSetByte(0x26, 0x00);  // Disable peaking
    CScalerSetByte(0xE4, 0x00);  // Disable DCC

#endif // end #if (_VGA_COLOR_SUPPORT)
#endif // #if (_SCALER_TYPE == _RTD2553V || _SCALER_TYPE == _RTD2546N || _SCALER_TYPE == _RTD2525L)
        
#endif // #if(_SCALER_TYPE == _RTD2547D)

}

//--------------------------------------------------
// Description  : Get mode information from mode table
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CModeGetModeTableInfo(void)
{
    BYTE modetemp;

#if(_VIDEO_SUPPORT && _VIDEO_CHIP == _VDC_TB1334)
    if(GET_MODE_SEARCH_TYPE() == _PRESET_MODE_TYPE || bSourceVideo())
#else
    if(GET_MODE_SEARCH_TYPE() == _PRESET_MODE_TYPE)
#endif
    {
        modetemp = stModeInfo.ModeCurr;
    }
    else if(GET_MODE_SEARCH_TYPE() == _USER_MODE_TYPE)
    {
        CEepromLoadUserFIFOModeData((stModeInfo.ModeCurr / 4), pData);

        modetemp = pData[(stModeInfo.ModeCurr % 4) * 4];
    }

#if(_VIDEO_SUPPORT && _VIDEO_CHIP == _VDC_TB1334)
    if (!bSourceVideo())
#endif
    {        
        stModeInfo.IHTotal = tINPUTMODE_PRESET_TABLE[modetemp].IHTotal;
        stModeInfo.IHStartPos = tINPUTMODE_PRESET_TABLE[modetemp].IHStartPos;
        stModeInfo.IHWidth = tINPUTMODE_PRESET_TABLE[modetemp].IHWidth;
    
        stModeInfo.IVStartPos = tINPUTMODE_PRESET_TABLE[modetemp].IVStartPos;
        stModeInfo.IVHeight = tINPUTMODE_PRESET_TABLE[modetemp].IVHeight;
        CEepromLoadCenterModeData(stModeInfo.ModeCurr);
    }
#if(_VIDEO_SUPPORT && _VIDEO_CHIP == _VDC_TB1334)
    else
    {
        stModeInfo.IHTotal = tVIDEO_INPUTMODE_PRESET_TABLE[modetemp].IHTotal;
        stModeInfo.IHStartPos = tVIDEO_INPUTMODE_PRESET_TABLE[modetemp].IHStartPos;
        stModeInfo.IHWidth = tVIDEO_INPUTMODE_PRESET_TABLE[modetemp].IHWidth;
    
        stModeInfo.IVStartPos = tVIDEO_INPUTMODE_PRESET_TABLE[modetemp].IVStartPos;
        stModeInfo.IVHeight = tVIDEO_INPUTMODE_PRESET_TABLE[modetemp].IVHeight;

        stModeUserCenterData.CenterHPos     = stModeInfo.IHStartPos;
        stModeUserCenterData.CenterVPos     = stModeInfo.IVStartPos;
        stModeUserCenterData.CenterClock    = stModeInfo.IHTotal;
    }
#endif


#if(_SCALER_TYPE == _RTD2547D)

  #if(_FRC_SUPPORT == _ON)
    ((DWORD *)pData)[0] = (DWORD)(stModeInfo.IHWidth) * (DWORD)(stModeInfo.IVHeight) * ((DWORD)stModeInfo.IVFreq + _PANEL_MAX_FRAME_RATE) / 10 / 85 * 100 / _MEMORY_BIT_NUM * 24;
    if(((DWORD *)pData)[0] > (DWORD)_MEMORY_SPEED * 1000000)//Frame Sync
        CLR_FRCTATUS();
    else//FRC
        SET_FRCTATUS();
  #else
    CLR_FRCTATUS();
  #endif
#endif
}
 
#if((_TMDS_SUPPORT == _ON) || (_HDMI_SUPPORT == _ON))
//--------------------------------------------------
// Description  : Startup settings for DVI
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CModeStartUpDVI(void)
{
#if(_SCALER_TYPE == _RTD2525L)
    CScalerSetBit(_VSYNC_COUNTER_LEVEL_MSB_4C, ~_BIT3, _BIT3);
#endif

#if(_SCALER_TYPE == _RTD2547D)
    CScalerSetBit(_VGIP_HV_DELAY_1E, 0x0f, 0x00);

    CScalerSetBit(_VGIP_CTRL_10, ~(_BIT3 | _BIT2 | _BIT0), (_BIT2 | _BIT0));
#else
    CScalerSetBit(_VGIP_HV_DELAY_13, 0x0f, 0x00);

    CScalerSetBit(_VGIP_CTRL_05, ~(_BIT3 | _BIT2 | _BIT0), (_BIT2 | _BIT0));
#endif

    CTimerWaitForEvent(_EVENT_IVS);

    pData[0]    = HIBYTE(stModeInfo.IHTotal - 2);
    pData[1]    = 0x02;
    pData[2]    = LOBYTE(stModeInfo.IHTotal - 2);
    pData[3]    = HIBYTE(stModeInfo.IVTotal - 2);
    pData[4]    = 0x02;
    pData[5]    = LOBYTE(stModeInfo.IVTotal - 2);
    pData[6]    = 0x00;
    pData[7]    = 0x00;
    pData[8]    = 0x00;
    pData[9]    = 0x00;
    pData[10]   = 0x03;
    pData[11]   = 0x00;
    pData[12]   = 0x00;
    pData[13]   = 0x81;
    CScalerWrite(_H_BOUNDARY_H_70, 14, pData, _AUTOINC);

    if(CTimerPollingEventProc(255, CMiscAutoMeasurePollingEvent))
    {
        CScalerRead(_V_START_END_H_7E, 6, pData, _AUTOINC);

        // IDEN horizontal Start
#if (_SCALER_TYPE == _RTD2553V || _SCALER_TYPE == _RTD2546N || _SCALER_TYPE == _RTD2525L)
        stModeInfo.IHStartPos = ((((WORD)pData[3] & 0xf0) << 4) | (WORD)pData[4]) - ((CScalerGetBit(_POWER_ON_OFF_CTRL_C2, _BIT7) == _BIT7) ? 16-14 : 18-14);
#elif(_SCALER_TYPE == _RTD2547D)
        CScalerPageSelect(_PAGE2);
        stModeInfo.IHStartPos = ((((WORD)pData[3] & 0xf0) << 4) | (WORD)pData[4]) - ((CScalerGetBit(_P2_POWER_ON_OFF_CTRL_A7, _BIT7) == _BIT7) ? 16-14 : 18-14);
#else
        stModeInfo.IHStartPos = ((((WORD)pData[3] & 0xf0) << 4) | (WORD)pData[4]) - ((CScalerGetBit(_POWER_ON_OFF_CTRL_C2, _BIT7) == _BIT7) ? 16 : 18);
#endif

        // IDEN vertical Start
        stModeInfo.IVStartPos = (((WORD)pData[0] & 0xf0) << 4) | (WORD)pData[1];
    }
    else
    {
        CScalerSetByte(_AUTO_ADJ_CTRL1_7D, 0x00);
        CModeResetMode();
    }
}
#endif  // End of #if((_TMDS_SUPPORT == _ON) || (_HDMI_SUPPORT == _ON)

//--------------------------------------------------
// Description  : Get scaling information
// Input Value  : None
// Output Value : Scaling information
//--------------------------------------------------
BYTE CModeGetScaleSetting(void)
{
    BYTE  option = 0;
#if(_SCALER_TYPE == _RTD2547D)
    DWORD ivheight;
#endif

#if(_DISP_INFO_BY_MODE == _ON)

    BYTE modetemp;


#if(_VIDEO_SUPPORT && _VIDEO_CHIP == _VDC_TB1334)
    if(GET_MODE_SEARCH_TYPE() == _PRESET_MODE_TYPE || bSourceVideo())
#else
    if(GET_MODE_SEARCH_TYPE() == _PRESET_MODE_TYPE)
#endif
    {
        modetemp = stModeInfo.ModeCurr;
    }
    else if(GET_MODE_SEARCH_TYPE() == _USER_MODE_TYPE)
    {
        CEepromLoadUserFIFOModeData((stModeInfo.ModeCurr / 4), pData);

        modetemp = pData[(stModeInfo.ModeCurr % 4) * 4];
    }

    stDisplayInfo = tDISPLAY_PRESET_TABLE[modetemp];

    // Modify Display Vertical Start Position
    stDisplayInfo.DVStartPos = (DWORD)35 * 2 * stDisplayInfo.DVHeight / stModeInfo.IVHeight / 10;
    stDisplayInfo.DVStartPos = ((stDisplayInfo.DVStartPos >> 1) + (stDisplayInfo.DVStartPos & 0x01));
    if(stDisplayInfo.DVStartPos < 6)
        stDisplayInfo.DVStartPos = 6;

    // Modify OSD Reference Position
#if(_SCALER_TYPE == _RTD2547D)
    CScalerSetDataPortByte(_DISP_ACCESS_PORT_2A, _DISP_OSD_REFERENCE_DEN_21, stDisplayInfo.DVStartPos - 4);
#else
    CScalerSetByte(_OSD_REFERENCE_DEN_1E, stDisplayInfo.DVStartPos - 4);
#endif

    ((WORD *)pData)[4] = (Panel.DHWidth - stDisplayInfo.DHWidth) / 2 + Panel.DHStartPos;

    pData[0]    = pData[8] & 0x0f;
    pData[1]    = pData[9];

    ((WORD *)pData)[5] = ((WORD *)pData)[4] + stDisplayInfo.DHWidth;

    pData[2]    = pData[10] & 0x0f;
    pData[3]    = pData[11];

    CScalerWrite(_DH_ACT_STA_H_2F, 4, pData, _AUTOINC);

#else
    stDisplayInfo.DHWidth   = CCalcPanelWdith();//Panel[ucPanelSelect]->DHWidth;
   // stDisplayInfo.DHWidth = Panel.DHWidth;
    stDisplayInfo.DVHeight = Panel.DVHeight;
   // stDisplayInfo.DHTotal = Panel.DHTotal;
    stDisplayInfo.DHTotal = CCalcPanelDHTota();

    // Modify Display Vertical Start Position
    stDisplayInfo.DVStartPos = (DWORD)35 * 2 * stDisplayInfo.DVHeight / stModeInfo.IVHeight / 10;
    stDisplayInfo.DVStartPos = ((stDisplayInfo.DVStartPos >> 1) + (stDisplayInfo.DVStartPos & 0x01));
    if(stDisplayInfo.DVStartPos < 6)
        stDisplayInfo.DVStartPos = 6;

    // Modify OSD Reference Position
#if(_SCALER_TYPE == _RTD2547D)
    CScalerSetDataPortByte(_DISP_ACCESS_PORT_2A, _DISP_OSD_REFERENCE_DEN_21, stDisplayInfo.DVStartPos - 4);
#else
    CScalerSetByte(_OSD_REFERENCE_DEN_1E, stDisplayInfo.DVStartPos - 4);
#endif

#endif

/*   // eric 0228 mark for 1080i mode
    // This F/W do not support V scale-up(or bypass) and H scale-down simultaneously
    if((stDisplayInfo.DVHeight >= stModeInfo.IVHeight) && (stDisplayInfo.DHWidth < stModeInfo.IHWidth))
    {
        stModeInfo.IHWidth = stDisplayInfo.DHWidth;
    } */

#if(_SCALER_TYPE == _RTD2547D)

  #if(_FIELD_MERGE_SUPPORT == _ON)
    {
        DWORD imagesize = 0;
    
        if(GET_INTERLACE_MODE())
        {
            imagesize = (DWORD)stModeInfo.IHWidth * stModeInfo.IVHeight * 3 * 8 * 4 / 1000000;
            if(_MEMORY_SIZE > imagesize)
                SET_FIELDMERGE_MODE();
            else
                CLR_FIELDMERGE_MODE();      
        }
        else
            CLR_FIELDMERGE_MODE();
    }
    if(GET_FIELDMERGE_MODE())
        ivheight = stModeInfo.IVHeight * 2;
    else
        ivheight = stModeInfo.IVHeight;
  #else
        ivheight = stModeInfo.IVHeight;
  #endif

    if(ivheight < stDisplayInfo.DVHeight)                   option |= _BIT0;    // bit 0 : V scale-up
    if(ivheight > stDisplayInfo.DVHeight)                   option |= _BIT1;    // bit 1 : V scale-down

#else

    if(stModeInfo.IVHeight < stDisplayInfo.DVHeight)        option |= _BIT0;    // bit 0 : V scale-up
    if(stModeInfo.IVHeight > stDisplayInfo.DVHeight)        option |= _BIT1;    // bit 1 : V scale-down
#endif

    if(stModeInfo.IHWidth < stDisplayInfo.DHWidth)          option |= _BIT2;    // bit 2 : H scale-up
    if(stModeInfo.IHWidth > stDisplayInfo.DHWidth)          option |= _BIT3;    // bit 3 : H scale-down

    return option;
}

//--------------------------------------------------
// Description  : Set capture window
// Input Value  : Scaling information
// Output Value : None
//--------------------------------------------------
void CModeSetCaptureWindow(BYTE ucOption)
{
    WORD ustemp;

    if(_GET_INPUT_SOURCE() == _SOURCE_VGA)
        ucHStartBias = 100;
    else if(_GET_INPUT_SOURCE() == _SOURCE_DVI || _GET_INPUT_SOURCE() == _SOURCE_HDMI)  //V306 modify
        ucHStartBias = 50;
    else
        ucHStartBias = 100;

#if(_SCALER_TYPE == _RTD2547D)
    if(GET_FRCTATUS())
    {
        ucVStartBias = stModeInfo.IVStartPos > (_PROGRAM_VDELAY + 4) ? stModeInfo.IVStartPos - (_PROGRAM_VDELAY + 4) : 0;
    }
    else
#endif
    {
        ucVStartBias = 0;
        ucVStartBias = CAdjustIVS2DVSDelay(ucOption);
    }

    if(ucVStartBias > stModeInfo.IVStartPos)
        ucVStartBias = stModeInfo.IVStartPos;

    // Set capture window
    ustemp = stModeInfo.IHStartPos + _CAPTURE_HDELAY - (ucHStartBias + _PROGRAM_HDELAY);

#if(_SCALER_TYPE == _RTD2547D)
    CScalerSetBit(_IPH_ACT_STA_H_14, ~(_BIT2 | _BIT1 | _BIT0), HIBYTE(ustemp) & (_BIT2 | _BIT1 | _BIT0));
    CScalerSetByte(_IPH_ACT_STA_L_15, LOBYTE(ustemp));
    CScalerSetBit(_IPH_ACT_WID_H_16, ~(_BIT2 | _BIT1 | _BIT0), HIBYTE(stModeInfo.IHWidth) & (_BIT2 | _BIT1 | _BIT0));
    CScalerSetByte(_IPH_ACT_WID_L_17, LOBYTE(stModeInfo.IHWidth));

    ustemp = stModeInfo.IVStartPos - (ucVStartBias + _PROGRAM_VDELAY);

    CScalerSetBit(_IPV_ACT_STA_H_18, ~(_BIT2 | _BIT1 | _BIT0), HIBYTE(ustemp) & (_BIT2 | _BIT1 | _BIT0));
    CScalerSetByte(_IPV_ACT_STA_L_19, LOBYTE(ustemp));
    CScalerSetBit(_IPV_ACT_LEN_H_1A, ~(_BIT2 | _BIT1 | _BIT0), HIBYTE(stModeInfo.IVHeight) & (_BIT2 | _BIT1 | _BIT0));
    CScalerSetByte(_IPV_ACT_LEN_L_1B, LOBYTE(stModeInfo.IVHeight));

    // Set internal input H sync delay
    CAdjustIHSDelay(ucHStartBias + _PROGRAM_HDELAY);

    // Set internal input V sync delay
    CAdjustIVSDelay(ucVStartBias + _PROGRAM_VDELAY);
#else
    CScalerSetBit(_IPH_ACT_STA_H_09, ~(_BIT2 | _BIT1 | _BIT0), HIBYTE(ustemp) & (_BIT2 | _BIT1 | _BIT0));
    CScalerSetByte(_IPH_ACT_STA_L_0A, LOBYTE(ustemp));
    CScalerSetBit(_IPH_ACT_WID_H_0B, ~(_BIT2 | _BIT1 | _BIT0), HIBYTE(stModeInfo.IHWidth) & (_BIT2 | _BIT1 | _BIT0));
    CScalerSetByte(_IPH_ACT_WID_L_0C, LOBYTE(stModeInfo.IHWidth));

    ustemp = stModeInfo.IVStartPos - (ucVStartBias + _PROGRAM_VDELAY);

    CScalerSetBit(_IPV_ACT_STA_H_0D, ~(_BIT2 | _BIT1 | _BIT0), HIBYTE(ustemp) & (_BIT2 | _BIT1 | _BIT0));
    CScalerSetByte(_IPV_ACT_STA_L_0E, LOBYTE(ustemp));
    CScalerSetBit(_IPV_ACT_LEN_H_0F, ~(_BIT2 | _BIT1 | _BIT0), HIBYTE(stModeInfo.IVHeight) & (_BIT2 | _BIT1 | _BIT0));
    CScalerSetByte(_IPV_ACT_LEN_L_10, LOBYTE(stModeInfo.IVHeight));
#endif

    // Set internal input H sync delay
    CAdjustIHSDelay(ucHStartBias + _PROGRAM_HDELAY);

    // Set internal input V sync delay
    CAdjustIVSDelay(ucVStartBias + _PROGRAM_VDELAY);
}

//--------------------------------------------------
// Description  : Set display
// Input Value  : Scaling information
// Output Value : None
//--------------------------------------------------
void CModeSetDisplay(BYTE ucOption)
{
    // Disable spread spectrum
#if(_SCALER_TYPE == _RTD2547D)
    CAdjustDclkSpreadSpectrumRange(0);
#else
    CAdjustSpreadSpectrumRange(0);
#endif

    // Calculate and set display clock frequency
    ((DWORD *)pData)[0] = (DWORD)(stDisplayInfo.DHTotal) * (DWORD)stModeInfo.IHFreq * (DWORD)(stDisplayInfo.DVHeight) / stModeInfo.IVHeight / 10;

#if(_SCALER_TYPE == _RTD2547D)

#if(_FRC_SUPPORT == _ON)
    if(GET_FRCTATUS())
    {
        // Calculate and set display clock frequency for FRC mode
        ((DWORD *)pData)[0] = (DWORD)(stDisplayInfo.DHTotal) * (DWORD)stModeInfo.IHFreq * (DWORD)(Panel.DVTotal) / stModeInfo.IVTotal / 10;

        if(stModeInfo.IVFreq > (_PANEL_MAX_FRAME_RATE + 5))
        {
            ((DWORD *)pData)[0] = (DWORD)(Panel.DHTotal) * (Panel.DVTotal) * (_PANEL_MAX_FRAME_RATE / 10) / 1000;
            CAdjustPLL(_DPLL, ((DWORD *)pData)[0]);
        }
        else if(((DWORD *)pData)[0] >= (DWORD)Panel.PixelClockMax * 1000)
            CAdjustPLL(_DPLL, (DWORD)Panel.PixelClockMax * 1000);
        else
            CAdjustPLL(_DPLL, ((DWORD *)pData)[0] - 100);
    }
    else
        CAdjustPLL(_DPLL, ((DWORD *)pData)[0]);
#else
    CAdjustPLL(_DPLL, ((DWORD *)pData)[0]);
#endif

    // Set DH_TOTAL
    pData[0] = (HIBYTE(stDisplayInfo.DHTotal - 4) & 0x0f);
    pData[1] = (LOBYTE(stDisplayInfo.DHTotal - 4));
    CScalerSetByte(_DISP_ACCESS_PORT_2A, _DISP_DH_TOTAL_H_00);
    CScalerWrite(_DISP_DATA_PORT_2B, 2, pData, _NON_AUTOINC);

    // Calculate DV_TOTAL setting for watchdog
    ((WORD *)pData)[2] = (DWORD)stModeInfo.IVTotal * (DWORD)(stDisplayInfo.DVHeight) / stModeInfo.IVHeight + 64;
    pData[0] = (HIBYTE(((WORD *)pData)[2]) & 0x0f);
    pData[1] = (LOBYTE(((WORD *)pData)[2]));
    CScalerSetByte(_DISP_ACCESS_PORT_2A, _DISP_DV_TOTAL_H_0B);
    CScalerWrite(_DISP_DATA_PORT_2B, 2, pData, _NON_AUTOINC);

#else

    CAdjustDPLL(((DWORD *)pData)[0]);

    // Set DH_TOTAL
    pData[0] = (HIBYTE(stDisplayInfo.DHTotal - 4) & 0x0f);
    pData[1] = (LOBYTE(stDisplayInfo.DHTotal - 4));
    CScalerWrite(_DH_TOTAL_H_2A, 2, pData, _AUTOINC);

    // Calculate DV_TOTAL setting for watchdog
    ((WORD *)pData)[2] = (DWORD)stModeInfo.IVTotal * (DWORD)(stDisplayInfo.DVHeight) / stModeInfo.IVHeight + 64;
	pData[0] = (HIBYTE(((WORD *)pData)[2]) & 0x0f);
	pData[1] = (LOBYTE(((WORD *)pData)[2]));
    CScalerWrite(_DV_TOTAL_H_35, 2, pData, _AUTOINC);

#endif // #if(_SCALER_TYPE == _RTD2547D)

    // Display vertical start/end
    // andy modify for panel
    //((WORD *)pData)[4] = stDisplayInfo.DVStartPos;
    ((WORD *)pData)[4] = Panel.DVStartPos;
    ((WORD *)pData)[5] = ((WORD *)pData)[4] + stDisplayInfo.DVHeight;

    pData[0] = HIBYTE(((WORD *)pData)[4]);
    pData[1] = LOBYTE(((WORD *)pData)[4]);
    pData[2] = HIBYTE(((WORD *)pData)[4]);
    pData[3] = LOBYTE(((WORD *)pData)[4]);
    pData[4] = HIBYTE(((WORD *)pData)[5]);
    pData[5] = LOBYTE(((WORD *)pData)[5]);
    pData[6] = HIBYTE(((WORD *)pData)[5]);
    pData[7] = LOBYTE(((WORD *)pData)[5]);
                                  
#if(_SCALER_TYPE == _RTD2547D)

    CScalerSetByte(_DISP_ACCESS_PORT_2A, (0x80 | _DISP_DV_BKGD_STA_H_0E));
    CScalerWrite(_DISP_DATA_PORT_2B, 8, pData, _NON_AUTOINC);
    CScalerSetByte(_DISP_ACCESS_PORT_2A, 0x00);

    // Turn off full-line buffer
    CScalerSetBit(_SCALE_CTRL_32, ~_BIT4, 0x00);

    if(GET_FRCTATUS())
    {
        // Enable display timing
        CScalerSetBit(_VDISP_CTRL_28, ~(_BIT5 | _BIT3 | _BIT1 | _BIT0), (_BIT5 | _BIT1 | _BIT0));
    }
    else

#else

    CScalerWrite(_DV_BKGD_STA_H_38, 8, pData, _AUTOINC);

    // Turn off full-line buffer
    CScalerSetBit(_SCALE_CTRL_19, ~_BIT4, 0x00);

#endif

    {
        CAdjustIVS2DVSDelay(ucOption);
    
        // Enable display timing
        CScalerSetBit(_VDISP_CTRL_28, ~(_BIT5 | _BIT3 | _BIT1 | _BIT0), (_BIT5 | _BIT3 | _BIT1 | _BIT0));
    }

    CMiscClearStatusRegister();
}

//--------------------------------------------------
// Description  : Modify IVTotal
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CModeModifyVTotal(void)
{
/*
    BYTE ucTemp;

    // Force to stop auto-tracking function
    CScalerSetByte(_AUTO_ADJ_CTRL_7F, 0x00);

    CScalerSetByte(_STATUS0_01, 0x00);   // Clear Status

    ucTemp  = 8;             // Tracking timeout 80ms
    do
    {
        CTimerDelayXms(10);
        CScalerRead(_STATUS0_01, 1, pData, _NON_AUTOINC);  // Read Status

        // V101C corrected
        if(pData[0] & 0x80)
            CScalerSetByte(_STATUS0_01, 0x00);   // Clear Status
        else
            break;
    }
    while(--ucTemp);

    // Measure actual number of scan line in each frame
    CScalerCodeW(tMEASURE_IVS);

    ucTemp  = 50;    // Tracking timeout 50ms
    do
    {   
        CTimerDelayXms(1);
        CScalerRead(_AUTO_ADJ_CTRL_7F, 0x01, pData, _NON_AUTOINC);
    }
    while((pData[0] & 0x01) && (--ucTemp));

    CScalerSetByte(_AUTO_ADJ_CTRL_7F, 0x00);
    
    if(ucTemp)
    {
        CScalerRead(_VER_START_80, 0x04, pData, _AUTOINC);
        pData[0]    = pData[3] & 0x0f;
        pData[1]    = pData[2];

        stModeInfo.IVTotal   = stModeInfo.IVTotal < ((WORD *)pData)[0] ? ((WORD *)pData)[0] : stModeInfo.IVTotal;
    }
*/
}

//----------------------------------------------------------------------------------------------------
// Other Mode Functions
//----------------------------------------------------------------------------------------------------

//--------------------------------------------------
// Description  : Reset mode
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CModeResetMode(void)
{         
    CLR_KEYREPEATENABLE();
#if(DVD_EN)
   if(_GET_INPUT_SOURCE() != _SOURCE_VIDEO_DVD)
   {
	#if(DVD_EN)
        bDVD_PWR_OFF() ;
	#endif
	   //	bDVD_PWR = 1;
		bDVDON = 0;
	}
#endif
   
#if(_VIDEO_SUPPORT == _ON)
    if (bVideoON && 
        (_GET_INPUT_SOURCE() == _SOURCE_VGA || 
         _GET_INPUT_SOURCE() == _SOURCE_DVI || 
         _GET_INPUT_SOURCE() == _SOURCE_HDMI || 
         _GET_INPUT_SOURCE() == _SOURCE_YPBPR))  // Prev source is video
    {
        gmi_CVDCOutputDisable();
        CPowerDownVDC();
        bVideoON = 0;
    } 
#if(_VIDEO_TV_SUPPORT)
    if (_GET_INPUT_SOURCE() == _SOURCE_VIDEO_TV)
    {
        ucVideoNoModeTime++;

        if (ucVideoNoModeTime < 250)
            return;
    }                                                                  

    ucVideoNoModeTime = 0;
#endif
#endif


    CLR_LIGHTPOWERSTATUS();
     MUTE_ON();  //guo 0814

    CAdjustDisableWatchDog(_WD_ALL);

#if(_SCALER_TYPE == _RTD2547D)

#if(_HDMI_SUPPORT == _ON)
	if(1)//CHdmiFormatDetect())//Input source is the HDMI format.
	{
        CScalerPageSelect(_PAGE2);
        CAdjustDisableHDMIWatchDog(_WD_AUDIO_FOR_TMDS_CLOCK | _WD_PACKET_VARIATION);
    
        //cyc:For 2880 input width.
    //    CScalerSetDataPortBit(_P2_HDMI_ADDR_PORT_C9, _P2_HDMI_VCR_50, 0xf0, 0x00);
    //    CScalerSetDataPortBit(_P2_HDMI_ADDR_PORT_C9, _P2_HDMI_ACRCR_51, ~_BIT2, 0x00);
        CScalerSetDataPortByte(_P2_HDMI_ADDR_PORT_C9, _P2_HDMI_AOCR_62, 0x00);//Disable SPDIF/I2S Output
	}
#endif
           
    CScalerSetByte(_HOST_CTRL_01, 0x40);
    CScalerSetBit(_VGIP_CTRL_10, ~(_BIT1 | _BIT0), 0x00);
    CScalerSetByte(_VGIP_SIGINV_11, 0x00);
    CScalerSetBit(_SYNC_TEST_MISC_5A, ~_BIT7, _BIT7);//For analog input detect interlace mode.
    CScalerPageSelect(_PAGE2);
    CScalerSetBit(_P2_POWER_ON_OFF_CTRL_A7, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT3 | _BIT2 | _BIT1 | _BIT0);
    CScalerSetBit(_P2_Z0_CALIBRATION_CTRL_AC, ~_BIT6, _BIT6);
             
#else

#if(_SCALER_TYPE == _RTD2553V || _SCALER_TYPE == _RTD2546N || _SCALER_TYPE == _RTD2525L) 
    CScalerSetBit(_HOST_CTRL_01, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
#else
    CScalerSetByte(_HOST_CTRL_01, 0x00);
#endif
    
    CScalerSetBit(_VGIP_CTRL_05, ~(_BIT1 | _BIT0), 0x00);
    CScalerSetByte(_VGIP_SIGINV_06, 0x00);

#if (_SCALER_TYPE == _RTD2525L)
    CScalerSetDataPortBit(_ADC_ACCESS_PORT_DC, 0x0c, ~_BIT7, 0x00);
    CScalerSetByte(_ADC_ACCESS_PORT_DC,0x8e);
    CScalerSetByte(_ADC_DATA_PORT_DD,0x00);
#endif


    CScalerSetBit(_POWER_ON_OFF_CTRL_C2, ~_BIT5, _BIT5);
    CScalerSetBit(_Z0_CALIBRATION_CTRL_C7, ~_BIT6, _BIT6);

#if (_VIDEO_SUPPORT == _ON)

    #if(_SCALER_TYPE == _RTD2553V || _SCALER_TYPE == _RTD2546N || _SCALER_TYPE == _RTD2525L) 
        if (_DSUB_A0_PORT == CGetSourcePortType(_GET_INPUT_SOURCE()))
            CScalerSetBit(_VSYNC_COUNTER_LEVEL_MSB_4C, ~_BIT3, _BIT3);
    #else

    #if(_SCALER_TYPE != _RTD2023L) 
    CScalerSetBit(_VSYNC_COUNTER_LEVEL_MSB_4C, ~_BIT5, _BIT5);
    #endif

    #endif

#endif // #if (_VIDEO_SUPPORT == _ON)
#endif // #if(_SCALER_TYPE == _RTD2547D)

    CModeSetFreeRun();

    if(GET_PANELPOWERSTATUS() == _OFF)
    {
        CScalerEnableDisplayTiming();
    }

    COsdFxDisableOsd();


    CModeAutoMeasureOff();
    CAdjustTMDSErrorCorrectionOn();
    CPowerPWMOn();
    CMiscClearStatusRegister();

#if(_SCALER_TYPE == _RTD2547D)   
    if(_GET_INPUT_SOURCE() == _SOURCE_VGA)
    {
        CScalerSetDataPortByte(_SYNC_PROC_ACCESS_PORT_5C, _SYNC_G_CLAMP_START_00, 0x04);
        CScalerSetDataPortByte(_SYNC_PROC_ACCESS_PORT_5C, _SYNC_G_CLAMP_END_01, 0x10);
        CScalerSetDataPortByte(_SYNC_PROC_ACCESS_PORT_5C, _SYNC_BR_CLAMP_START_02, 0x04);
        CScalerSetDataPortByte(_SYNC_PROC_ACCESS_PORT_5C, _SYNC_BR_CLAMP_END_03, 0x10);
        CScalerSetDataPortBit(_SYNC_PROC_ACCESS_PORT_5C, _SYNC_CLAMP_CTRL0_04, ~(_BIT7 | _BIT6), 0x00);
    }
#endif


    CTimerCancelTimerEvent(CModeNoSignalEvent);
    CTimerCancelTimerEvent(CModeNoCableEvent);
    CTimerCancelTimerEvent(CModeNoSupportEvent);
    CTimerCancelTimerEvent(CModePowerSavingEvent);
    CTimerCancelTimerEvent(COsdDispOsdTimerEvent);

    CLR_FIRST_ADCCLOCK();
    CLR_USE_TRANSITION_RESULT();
    CLR_FRAMESYNCSTATUS();
    CLR_MODESTABLE();
    ucInputSyncType = _NO_SYNC_STATE;

#if(_SCALER_TYPE == _RTD2547D)   
    CLR_INTERLACE_MODE();
 #if(_FRC_SUPPORT == _ON)
    CLR_FRCTATUS();
  #if(_FIELD_MERGE_SUPPORT == _ON)
    CLR_FIELDMERGE_MODE();
  #endif
 #endif

 #if(_HDMI_SUPPORT == _ON)
    CLR_HDMIINPUT();    
    CLR_AUDIOPLLLOCKREADY();
    CLR_AVRESUME();
    CLR_AUDIOWAITINGTIMEOUT();
 #endif
#endif

    // add for YPbPr 1080i change to 720p show mode not support
#if(_SCALER_TYPE != _RTD2547D)   
#if(_YPBPR_SUPPORT)
    if (_GET_INPUT_SOURCE() == _SOURCE_YPBPR)
        CAdjustGamma(_COMPACT_GAMMA_NORMAL_TABLE, tGAMMA_COMPACT1, tGAMMA_COMPACT1, tGAMMA_COMPACT1);
#endif
#endif // #if(_SCALER_TYPE != _RTD2547D)   


#if(_NEW_YPBPR && _YPBPR_SUPPORT)
  	if(_GET_INPUT_SOURCE() == _SOURCE_YPBPR)
    {
   #if(_SCALER_TYPE == _RTD2547D)   
   /*
        CScalerSetByte(_P0_ADC_RED_CTL_A2,0xC0); 
        CScalerSetByte(_P0_ADC_GREEN_CTL_A3,0x40); 
        CScalerSetByte(_P0_ADC_BLUE_CTL_A4,0xC0); 
                        
        CScalerSetByte(_P0_SOG0_CTRL_AB,0x20);
        CScalerSetByte(_P0_SOG1_CTRL_AC,0x20);*/
   #else
        CScalerSetDataPortBit(_ADC_ACCESS_PORT_DC, 0x0C, ~_BIT7, 0x00);
        CScalerSetByte(_ADC_ACCESS_PORT_DC,0x81); 
        CScalerSetByte(_ADC_DATA_PORT_DD,0x40); 
        CScalerSetByte(_ADC_DATA_PORT_DD,0x40); 
        CScalerSetByte(_ADC_DATA_PORT_DD,0x40); 
                        
        CScalerSetByte(_ADC_ACCESS_PORT_DC, 0x8A);
        CScalerSetByte(_ADC_DATA_PORT_DD,0x25);
        CScalerSetByte(_ADC_ACCESS_PORT_DC, 0x8B);
        CScalerSetByte(_ADC_DATA_PORT_DD,0x25);
                          
        CScalerSetByte(_ADC_ACCESS_PORT_DC,0x8e);
        CScalerSetByte(_ADC_DATA_PORT_DD,0x04);
        CScalerSetByte(_ADC_ACCESS_PORT_DC,0x8c);
        CScalerSetByte(_ADC_DATA_PORT_DD,0x3f);  
   #endif
    }
#endif

    CScalerSetBit(_VDISP_CTRL_28, ~(_BIT5 | _BIT3), (_BIT5));
#if(_CHANGE_SOURCE_BACKGROUCD_COLOR==_BACK_COLOR)					    	
		CAdjustBackgroundColor(0x00, 0x00, 0x00);     
#else
		CAdjustBackgroundColor(0x00, 0x00, 0xFF);     
#endif
    SET_FIRST_LOADFONT();  // eric 0606 add


#if(_HDMI_SUPPORT == _ON)
    SET_PRE_VGA_CONNECT(bVGACONNECT);
    SET_PRE_HDMI_CONNECT(bHDMICONNECT);
#elif(_TMDS_SUPPORT == _ON)
    SET_PRE_VGA_CONNECT(bVGACONNECT);
    SET_PRE_DVI_CONNECT(bDVICONNECT);
#else
    SET_PRE_VGA_CONNECT(bVGACONNECT);
#endif

    stModeInfo.ModeCurr = _MODE_NOSIGNAL;
    ucModeFound         = _MODE_FIRST;
    ucEvent0            = _INACTIVE_COUNTDOWN_EVENT;
    ucEvent1            = _INACTIVE_COUNTDOWN_EVENT;
    ucOsdState          = _MENU_NONE;
    ucOsdEventMsg       = _NONE_MSG;

    ucOSDAdjTemp        = 0;
    stModeInfo.Polarity = 0;
    stModeInfo.IHCount  = 0;
    stModeInfo.IHFreq   = 0;
    stModeInfo.IVTotal  = 0;
    stModeInfo.IVFreq   = 0;
    stModeInfo.IHWidth  = 0;
    stModeInfo.IVHeight = 0;
    stModeInfo.IHSyncPulseCount = 0;

#if(_VIDEO_SUPPORT)
    RECODE_NONE_VIDEO();
    VideoTurnOnLightCount = 0;
#endif

#ifdef _SII164_INIT_SUPPORT
    //b164SW = 0;
	//CTimerDelayXms(200);
	//b164SW = 1;
    CModeInitSiI164();
#endif

#if(_DDC_TYPE != _DDC_NONE)
    DDCInit();
#endif    
    SET_FIRST_SHOW_NOTE();

      if (_GET_INPUT_SOURCE() == _SOURCE_VIDEO_TV)
      	{
    CTimerDelayXms(50);
CScalerSetBit(_SYNC_INVERT_48, ~(_BIT6 | _BIT1), (_BIT4 | _BIT2));
    CTimerDelayXms(50);
CScalerSetBit(_SYNC_CTRL_49, ~(_BIT5 | _BIT6), (_BIT2 | _BIT1));
      	}
    ucCurrState = _SEARCH_STATE; 
}

//--------------------------------------------------
// Description  : Free run mode setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CModeSetFreeRun(void)
{ 
	    WORD ucDHStart =CCalcPanelDHSta();
	    WORD ucDHEnd   = CCalcPanelDHEnd(0);
    CMiscDisableDoubleBuffer();

#if(_SCALER_TYPE == _RTD2547D)   
    // Enabl MPLL
    CAdjustPLL(_MPLL, (DWORD)_MEMORY_SPEED * 1000);
    // Enable the Mclk spread spectrum function
    CAdjustMclkSpreadSpectrumRange(_MCLK_SPREAD_RANGE);

    CAdjustPLL(_DPLL, (DWORD)Panel.PixelClock * 1000);
#else
    CAdjustDPLL((DWORD)Panel.PixelClock * 1000);
#endif

    CScalerSetBit(_VDISP_CTRL_28, ~(_BIT5 | _BIT3 | _BIT1 | _BIT0), (_BIT5 | _BIT1 | _BIT0));

	    pData[0]    = (HIBYTE(Panel.DHTotal - 4) & 0x0f);
	    pData[1]    = (LOBYTE(Panel.DHTotal - 4));
	    pData[2]    = (Panel.DHSyncWidth);
	    pData[3]    = (HIBYTE(Panel.DHStartPos) & 0x0f);
	    pData[4]    = (LOBYTE(Panel.DHStartPos));
	    pData[5]    = (HIBYTE(ucDHStart) & 0x0f);
	    pData[6]    = (LOBYTE(ucDHStart));
	    pData[7]    = (HIBYTE(ucDHEnd) & 0x0f);
	    pData[8]    = (LOBYTE(ucDHEnd));
	    pData[9]    = (HIBYTE(CCalcPanelDHEnd(1)) & 0x0f);
	    pData[10]   = (LOBYTE(CCalcPanelDHEnd(1)));

#if(_SCALER_TYPE == _RTD2547D)   
    CScalerSetByte(_DISP_ACCESS_PORT_2A, _DISP_DH_TOTAL_H_00);
    CScalerWrite(_DISP_DATA_PORT_2B, 11, pData, _NON_AUTOINC);
#else
    CScalerWrite(_DH_TOTAL_H_2A, 11, pData, _AUTOINC);
#endif

    pData[0]    = (HIBYTE(Panel.DVTotal) & 0x0f);
    pData[1]    = (LOBYTE(Panel.DVTotal));
    pData[2]    = (Panel.DVSyncHeight);
    pData[3]    = (HIBYTE(Panel.DVStartPos) & 0x0f);
    pData[4]    = (LOBYTE(Panel.DVStartPos));
    pData[5]    = (HIBYTE(Panel.DVStartPos) & 0x0f);
    pData[6]    = (LOBYTE(Panel.DVStartPos));
    pData[7]    = (HIBYTE(CCalcPanelDVEnd()) & 0x0f);
    pData[8]    = (LOBYTE(CCalcPanelDVEnd()));
    pData[9]    = (HIBYTE(CCalcPanelDVEnd()) & 0x0f);
    pData[10]   = (LOBYTE(CCalcPanelDVEnd()));

#if(_SCALER_TYPE == _RTD2547D)   
    CScalerSetByte(_DISP_ACCESS_PORT_2A, _DISP_DV_TOTAL_H_0B);
    CScalerWrite(_DISP_DATA_PORT_2B, 11, pData, _NON_AUTOINC);
#else
    CScalerWrite(_DV_TOTAL_H_35, 11, pData, _AUTOINC);
#endif

    pData[0]    = ((Panel.DHTotal >> 4) & 0xf0) | (HIBYTE(Panel.DVTotal) & 0x0f);
    pData[1]    = LOBYTE(Panel.DVTotal);
    pData[2]    = LOBYTE(Panel.DHTotal);

#if(_SCALER_TYPE == _RTD2547D)   
    CScalerPageSelect(_PAGE1);
    CScalerWrite(_P1_FIXED_LAST_LINE_MSB_BF, 3, pData, _AUTOINC);
#else
    CScalerWrite(_FIXED_LAST_LINE_MSB_B8, 3, pData, _AUTOINC);
#endif
}

//--------------------------------------------------
// Description  : Check if the connector status is changed
// Input Value  : None
// Output Value : Return _TRUE if the connector status changed
//--------------------------------------------------
bit CModeConnectIsChange(void)
{

#if(_HDMI_SUPPORT == _ON)

    if((bVGACONNECT != GET_PRE_VGA_CONNECT()) || (bHDMICONNECT != GET_PRE_HDMI_CONNECT()))
    {
        SET_PRE_VGA_CONNECT(bVGACONNECT);
        SET_PRE_HDMI_CONNECT(bHDMICONNECT);
        return _TRUE;
    }

    SET_PRE_VGA_CONNECT(bVGACONNECT);
    SET_PRE_HDMI_CONNECT(bHDMICONNECT);

#elif(_TMDS_SUPPORT == _ON)

    if((bVGACONNECT != GET_PRE_VGA_CONNECT()) || (bDVICONNECT != GET_PRE_DVI_CONNECT()))
    {
        SET_PRE_VGA_CONNECT(bVGACONNECT);
        SET_PRE_DVI_CONNECT(bDVICONNECT);
        return _TRUE;
    }

    SET_PRE_VGA_CONNECT(bVGACONNECT);
    SET_PRE_DVI_CONNECT(bDVICONNECT);

#else

    if((bVGACONNECT != GET_PRE_VGA_CONNECT()))
    {
        SET_PRE_VGA_CONNECT(bVGACONNECT);
        return _TRUE;
    }

    SET_PRE_VGA_CONNECT(bVGACONNECT);

#endif

    return _FALSE;
}

//--------------------------------------------------
// Description  : Enable online measure
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CModeAutoMeasureOn(void)
{
    CScalerSetBit(_MEAS_HS_PERIOD_H_52, ~_BIT7, _BIT7);
    CTimerDelayXms(40); //V304 modify
}

//--------------------------------------------------
// Description  : Disable online measure
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CModeAutoMeasureOff(void)
{
    CScalerSetBit(_MEAS_HS_PERIOD_H_52, ~_BIT7, 0x00);
}

//----------------------------------------------------------------------------------------------------
// Mode Events
//----------------------------------------------------------------------------------------------------

//--------------------------------------------------
// Description  : No signal timeout count down event
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CModeSyncTimeoutCountDownEvent(void)
{
#if(_VIDEO_SUPPORT && _VIDEO_CHIP == _VDC_TB1334 && _VIDEO_TV_SUPPORT)
    if (_GET_INPUT_SOURCE() == _SOURCE_VIDEO_TV)
    {               
        CLoadTVNoSignalModeData();
        CLoadVideoModeData();
        SET_READYFORDISPLAY();
        CModeDisplayActiveMode();
        CModeAutoMeasureOn();
        ucCurrState = _ACTIVE_STATE;
    }
    else
#endif
    {
        ucCurrState = _NOSIGNAL_STATE;
        stModeInfo.ModeCurr = _MODE_NOSIGNAL;
        SET_READYFORDISPLAY();
    }
}

//--------------------------------------------------
// Description  : Mode stable count down event
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CModeStableCountDownEvent(void)
{
    SET_MODESTABLE();
}

//--------------------------------------------------
// Description  : No signal event
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CModeNoSignalEvent(void)
{
    ucOsdEventMsg = _SHOW_NOSIGNAL_MSG;
}
//--------------------------------------------------
// Description  : No cable event
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CModeNoCableEvent(void)
{
    ucOsdEventMsg = _SHOW_NOCABLE_MSG;
}

//--------------------------------------------------
// Description  : No support event
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CModeNoSupportEvent(void)
{
    ucOsdEventMsg = _SHOW_NOSUPPORT_MSG;
}

//--------------------------------------------------
// Description  : Power saving event
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CModePowerSavingEvent(void)
{
#if(_BURNIN_EN)
if(GET_BURNIN_STATE()==BURNIN_OFF)	
#endif
	{
#if(_AUTO_SLEEP_POWERDOWN == _OFF)
#if(_SCALER_TYPE == _RTD2547D)   
    CScalerPageSelect(_PAGE2);
    CScalerSetBit(_P2_POWER_ON_OFF_CTRL_A7, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT4);
    CScalerSetBit(_P2_Z0_CALIBRATION_CTRL_AC, ~_BIT6, _BIT6);
#endif
    CPowerPanelOff();
    CScalerSetBit(_VDISP_CTRL_28, ~(_BIT3 | _BIT0), 0x00);
    CPowerADCAPLLOff();
    CPowerLVDSOff();
    CPowerDPLLOff();
#if(_SCALER_TYPE == _RTD2547D)   
    CPowerMPLLOff();
#endif
    CPowerPWMOff();
    CScalerDisableDisplayTiming();
#if(_SCALER_TYPE == _RTD2547D)   
    CScalerSetBit(_HOST_CTRL_01, ~_BIT1, _BIT1);
#endif
    ucCurrState = _SLEEP_STATE;

#else
	//modify for auto power off 2007/08/29
	SET_POWERSWITCH();
#endif
	}
}


#ifdef _SII164_INIT_SUPPORT
//--------------------------------------------------
// Description  : Initialize SiI164 after power up or reset
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CModeInitSiI164(void)
{
    pData[0] = 0xF7;
	pData[1] = 0x8E;
	pData[2] = 0xFF;
	pData[3] = 0x00;
    CI2cWrite(_ADDR_SiI164, 0x08, 1, &pData[0]);
    CI2cWrite(_ADDR_SiI164, 0x09, 1, &pData[1]);
    CI2cWrite(_ADDR_SiI164, 0x0A, 1, &pData[2]);
    CI2cWrite(_ADDR_SiI164, 0x0C, 1, &pData[3]);	   
}
#endif

#if(_SCALER_TYPE == _RTD2547D)   
//--------------------------------------------------
// Description  : Check HDMI Input Status
// Input Value  : None
// Output Value : None
//--------------------------------------------------
#if((_HDMI_SUPPORT == _ON) || (_TMDS_SUPPORT == _ON))
void CModeHdmiStablePolling(void)
{
    if(CGetSourcePortType(_GET_INPUT_SOURCE()) == _DVI_PORT)
    {
        if(CHdmiFormatDetect())
            CModeResetMode();                        
    }
#if(_HDMI_SUPPORT == _ON)
    else if(CGetSourcePortType(_GET_INPUT_SOURCE()) == _HDMI_PORT)
    {
        if(CHdmiFormatDetect())//Input source is the HDMI format.
        {
            if(!GET_HDMIINPUT())
                CModeResetMode();
            else
            {
                if(GET_AUDIOWAITINGTIMEOUT())
                CHdmiEnableAudioOutput();
            }
        }
        else
        {
            if(GET_HDMIINPUT())
                CModeResetMode();
        }
    }
#endif
}
#endif // #if((_HDMI_SUPPORT == _ON) || (_TMDS_SUPPORT == _ON))

//--------------------------------------------------
// Description  : Display FIFO Setting for Frame Sync Mode
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CModeSetFIFOForFrameSync(void)
{
    CScalerPageSelect(_PAGE5);
    CScalerSetByte(_P5_SDRF_MN_DISP_CTRL_CF,0x05);
    CTimerDelayXms(100);
    CScalerSetByte(_P5_SDRF_MN_SDR_STATUS_D0,0x10);
}

//--------------------------------------------------
// Description  : Check input signal for interlace
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CModeInterlaceCheck(void)
{
    switch(_GET_INPUT_SOURCE())
    {
        case _SOURCE_VGA:
#if(_YPBPR_SUPPORT == _ON)
        case _SOURCE_YPBPR:
#endif
            CTimerDelayXms(50);            
            CScalerRead(_IPV_ACT_LEN_H_1A, 1, pData, _NON_AUTOINC);
            if(pData[0] & 0x20)
                SET_INTERLACE_MODE();
            else
                CLR_INTERLACE_MODE();

            CScalerSetBit(_SYNC_TEST_MISC_5A, ~_BIT7, 0x00);//Disable Test Mode

            break;

#if(_VIDEO_SUPPORT == _ON)
    case _SOURCE_VIDEO_AV:
    case _SOURCE_VIDEO_SV:
    case _SOURCE_VIDEO_YUV:
    case _SOURCE_VIDEO_DVD:
    case _SOURCE_VIDEO_SCART:
#endif
#if((_TMDS_SUPPORT == _ON) || (_HDMI_SUPPORT == _ON))
        case _SOURCE_DVI:
        case _SOURCE_HDMI:
#endif
#if((_TMDS_SUPPORT == _ON) || (_HDMI_SUPPORT == _ON) || (_VIDEO_SUPPORT == _ON))
            CScalerPageSelect(_PAGE2);
            CScalerSetDataPortBit(_P2_HDMI_ADDR_PORT_C9, _P2_HDMI_VCR_50, ~_BIT6, _BIT6);
            CTimerDelayXms(50);

            CScalerGetDataPortByte(_P2_HDMI_ADDR_PORT_C9, _P2_HDMI_VCR_50, 1, pData, _NON_AUTOINC);
            if((pData[0] & 0x40) == 0x40)
                SET_INTERLACE_MODE();
            else
                CLR_INTERLACE_MODE();

            break;
#endif
    }
}
#endif // #if(_SCALER_TYPE == _RTD2547D)   
       
//==============================================================================  
// eric 0126 add for RTD2547D
//==============================================================================  
void CModeSetDisplayReady(void)
{
#if(_SCALER_TYPE == _RTD2547D)
 #if((_HDMI_SUPPORT == _ON) || (_TMDS_SUPPORT == _ON))
    CModeHdmiStablePolling();
 #endif
#endif // end #if(_SCALER_TYPE == _RTD2547D)

    if(GET_READYFORDISPLAY() == _TRUE)
    {  
        CLR_READYFORDISPLAY();
        SET_OSD_READYFORDISPLAY();
        CLR_SOURCE_AUTOCHANGE();
#if(_SCALER_TYPE == _RTD2547D)
 #if(_OD_SUPPORT == _ON)
        CMemorySetODCompress();
        CMemorySetODFIFO();
        CMemorySetODOnOff(_ON);
 #endif

 #if (_HDMI_SUPPORT == _ON)
		if ((CGetSourcePortType(stSystemData.InputSource) == _HDMI_PORT)) 
        {
    		CScalerPageSelect(_PAGE2);
    		CScalerSetDataPortBit(_P2_HDMI_ADDR_PORT_C9, _P2_HDMI_VWDSR_41, ~_BIT0, _BIT0);//Enable packet variation Watch Dog
        }
 #endif
#endif  // #if(_SCALER_TYPE == _RTD2547D)

        CPowerPanelOn();

#if(_VIDEO_SUPPORT && _VIDEO_CHIP == _VDC_TB1334)
    if (bSourceVideo())
            CSetVideoReady();
        else
#endif
            CSetVGAReady();
	if(GET_BURNIN_STATE()==BURNIN_OFF)
	{
	       if((gmi_CModeLocked()&&_GET_INPUT_SOURCE()==_SOURCE_VIDEO_TV)||_GET_INPUT_SOURCE()!=_SOURCE_VIDEO_TV)
	       	{
	       	if(_GET_CHANNEL_FOR_AUDIO()&&_GET_INPUT_SOURCE()==_SOURCE_VIDEO_TV)
	       		{
	                     CSetVolume();
	       		}
			_SET_CHANNEL_FOR_AUDIO(0);
			CAdjustBackgroundColor(0x00, 0x00, 0x00);     				
			CScalerSetBit(_VDISP_CTRL_28, ~(_BIT5 |_BIT3),  _BIT3 );
	       	}
	}
    }
     
    if((stModeUserData.FirstAuto == 0)      && 
       (_GET_INPUT_SOURCE() == _SOURCE_VGA) &&  
       (ucOsdState == _MENU_NONE)) 
    {
        stModeUserData.FirstAuto = 1;
        ucOsdEventMsg = _DO_AUTO_CONFIG;
        CLR_FIRST_SHOW_NOTE();
    }
                                                

#if(_VIDEO_SUPPORT && _VIDEO_CHIP == _VDC_TB1334 && _VIDEO_TV_SUPPORT)
    if (_GET_INPUT_SOURCE() == _SOURCE_VIDEO_TV)
       CTVCheckChangeChannel();
#endif
}

//==============================================================================  
//
//    CSetVGAReady
//
//==============================================================================  
void CSetVGAReady(void)
{
#if(_SCALER_TYPE == _RTD2547D)
    if(GET_FRCTATUS())
        CAdjustEnableWatchDog(_WD_FRAMESYNC_APLL_NONLOCK);
    else
        CAdjustEnableWatchDog(_WD_ALL);

#if(_HDMI_SUPPORT == _ON)
    CScalerPageSelect(_PAGE2);
    if(CGetSourcePortType(_GET_INPUT_SOURCE()) == _HDMI_PORT)
        CAdjustEnableHDMIWatchDog(_WD_PACKET_VARIATION);//Enable packet variation Watch Dog
    else
        CAdjustDisableHDMIWatchDog(_WD_PACKET_VARIATION);//Disable packet variation Watch Dog
#endif  // #if(_HDMI_SUPPORT == _ON)

#else

    CAdjustEnableWatchDog(_WD_ALL);

#endif  // #if(_SCALER_TYPE == _RTD2547D)
}

//==============================================================================  
//
//   bFrameSyncDet 
//
//==============================================================================  
bit bFrameSyncDet(void)
{                  
#if(_VIDEO_SUPPORT && _VIDEO_CHIP == _VDC_TB1334)
    if (bSourceVideo())
       return CVideoFrameSyncDetect();
    else
#endif
       return CFrameSyncDetect();
}                       

//==============================================================================  
//
//   bModeIsChange 
//
//==============================================================================  
bit bModeIsChange(void)
{                          
#if(_VIDEO_SUPPORT && _VIDEO_CHIP == _VDC_TB1334)
    if (bSourceVideo())
       return !gmi_CVideoIsExist(); 
    else
#endif
       return CModeIsChange();
}

//---------------------------------------------
WORD CCalcPanelWdith(void)
{
	 if(Panel.DHWidth > (Panel.DVHeight * 4/3))  //yang 1229
	 	{
		 if(_GET_DISPLAY_MODE() == DISPLAY_MODE_43)
		     {
					return Panel.DVHeight * 4 / 3;
		     }
		     else		
		 return Panel.DHWidth;
	 	}
	 else
		 return Panel.DHWidth;

}
//----------------------------------------------------------
WORD CCalcPanelDHSta(void)
{

	WORD usWidth = CCalcPanelWdith();
	return Panel.DHStartPos + (Panel.DHWidth - usWidth) / 2;
}
//---------------------------------------------
WORD CCalcPanelDHEnd(BYTE uctemp)
{
      if(uctemp)
      	{
	return Panel.DHStartPos + Panel.DHWidth;
      	}
	  else
      	{
	WORD usWidth = CCalcPanelWdith();
	return Panel.DHStartPos + Panel.DHWidth - (Panel.DHWidth - usWidth) / 2;
      	}
}
//---------------------------------------------
WORD CCalcPanelDHTota(void)
{
	if (bSourceVideo())
		{
		if (CHECK60HZ())     // NTSC
			return    Panel.NTSC_Htotal;
		else                // PAL
			return    Panel.PAL_Htotal;
		}
	else
		{
		return   Panel.DHTotal;    
		}
}
//---------------------------------------------
WORD CCalcPanelDVEnd(void)
{
	return Panel.DVStartPos + Panel.DVHeight;
}
//---------------------------------------------

