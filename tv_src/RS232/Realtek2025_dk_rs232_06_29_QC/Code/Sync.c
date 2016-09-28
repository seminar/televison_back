//----------------------------------------------------------------------------------------------------
// ID Code      : Sync.c No.0004
// Update Note  : 
//
//----------------------------------------------------------------------------------------------------

#define __SYNC__

#include "Header\Include.h"


//--------------------------------------------------
// Description  : Measure sync type
// Input Value  : None
// Output Value : Return _TRUE if succeed
//--------------------------------------------------
bit CSyncHandler(void)
{
#if(_VIDEO_TV_SUPPORT && _VIDEO_CHIP == _VDC_TB1334)
    if (bSourceVideo())
    {
        if (_GET_INPUT_SOURCE() != _SOURCE_VIDEO_TV)
        {
            if (!gmi_CModeLocked())
            {
                ucInputSyncType = _NO_SYNC_STATE; 
                return _FALSE;
            }
        }
    }
#endif

    if(ucInputSyncType == _NO_SYNC_STATE)
    {
        if(!CSourceHandler())  
        {
            ucInputSyncType = _NO_SYNC_STATE; 
            return _FALSE;
        }
        
#if (_SCALER_TYPE == _RTD2547D)
		CTimerDelayXms(3);
#endif
        ucInputSyncType = CSyncMeasureSyncType();
        switch(ucInputSyncType)
        {
            case _NO_SYNC_STATE:
          //      SET_INPUTSOURCE_TYPE(_SOURCE_NONE);
                return _FALSE;

            case _SS_STATE:
            case _CS_STATE:
            case _SOG_STATE:
             //   SET_INPUTSOURCE_TYPE(_SOURCE_VGA);
                return _TRUE;

#if(_YPBPR_SUPPORT == _ON)

            case _SOY_STATE:
             //   SET_INPUTSOURCE_TYPE(_SOURCE_YPBPR);
                return _TRUE;

#endif


#if((_TMDS_SUPPORT == _ON) || (_HDMI_SUPPORT == _ON))

            case _DSS_STATE:
#if(_HDMI_SUPPORT == _ON)
        //        if(CHdmiFormatDetect())//Input source is the HDMI format.                
          //          SET_INPUTSOURCE_TYPE(_SOURCE_DVI);
            //    else
#endif
             //   SET_INPUTSOURCE_TYPE(_SOURCE_DVI);
                return _TRUE;

#endif
 //       case _VIDEO8_STATE:
           // SET_INPUTSOURCE_TYPE(_SOURCE_VIDEO8);
   //         return _TRUE;
            default:
                ucInputSyncType = _NO_SYNC_STATE;
          //      SET_INPUTSOURCE_TYPE(_SOURCE_NONE);
                return _FALSE;

        }
    }
    else
    {
        switch(CGetSourcePortType(_GET_INPUT_SOURCE()))
        {
#if(_YPBPR_SUPPORT == _ON)
            case _YPBPR_A0_PORT:
            case _YPBPR_A1_PORT:
#endif
            case _DSUB_A0_PORT:
            case _DSUB_A1_PORT:
                CScalerSetBit(_SYNC_CTRL_49, ~(_BIT1 | _BIT0), _BIT1);
                break;

#if((_TMDS_SUPPORT == _ON) || (_HDMI_SUPPORT == _ON))

            case _DVI_PORT:
            case _HDMI_PORT:
            case _DVI_I_A0_PORT:
            case _DVI_I_A1_PORT: 
                CScalerSetBit(_SYNC_CTRL_49, ~(_BIT1 | _BIT0), 0x00);
                break;

#endif
    //    case _SOURCE_VIDEO8:
     ///       CScalerSetBit(_SYNC_CTRL_49, ~(_BIT1 | _BIT0), _BIT0);
      //      break;
        }
        return _TRUE;
    }
}

//--------------------------------------------------
// Description  : Measure sync type
// Input Value  : None
// Output Value : Return sync type we measured
//--------------------------------------------------
BYTE CSyncMeasureSyncType(void)
{
    BYTE synctypetemp;
    
    switch(CGetSourcePortType(_GET_INPUT_SOURCE()))
    {
#if(_YPBPR_SUPPORT == _ON)
        case _YPBPR_A0_PORT:
#endif
        case _DSUB_A0_PORT:
#if (_SCALER_TYPE != _RTD2547D)
#if ((_SCALER_TYPE == _RTD2553V) || (_SCALER_TYPE == _RTD2525L) || (_SCALER_TYPE == _RTD2546N))
#if((_SCALER_TYPE == _RTD2553V) || (_SCALER_TYPE == _RTD2546N))
            CScalerSetBit(_SYNC_SELECT_47, ~(_BIT3 | _BIT2), 0x00);
			CScalerSetDataPortBit(_ADC_ACCESS_PORT_DC, 0x00, ~_BIT3, 0x00);
#else
            CScalerSetDataPortBit(_ADC_ACCESS_PORT_DC, 0x00, ~_BIT3, _BIT3);
#endif
#else
            CScalerSetBit(_SYNC_SELECT_47, ~(_BIT3 | _BIT2), 0x00);
            CScalerSetBit(_ADC_RGB_CTRL_DC, ~_BIT3, 0x00);
#endif
#endif // #if (_SCALER_TYPE != _RTD2547D)

            CScalerSetBit(_SYNC_SELECT_47, ~_BIT4, ((BYTE)bHsyncSelection << 4));
            synctypetemp    = CSyncSearchSyncTypeVGA();
            break;

#if (_SCALER_TYPE != _RTD2547D)
#if(_YPBPR_SUPPORT == _ON)
        case _YPBPR_A1_PORT:
#endif
        case _DSUB_A1_PORT:
            CScalerSetBit(_SYNC_SELECT_47, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));
#if (_SCALER_TYPE == _RTD2553V || _SCALER_TYPE == _RTD2546N || _SCALER_TYPE == _RTD2525L)
			CScalerSetDataPortBit(_ADC_ACCESS_PORT_DC, 0x00, ~_BIT3, _BIT3);
#else
            CScalerSetBit(_ADC_RGB_CTRL_DC, ~_BIT3, _BIT3);
#endif
            CScalerSetBit(_SYNC_SELECT_47, ~_BIT4, ((BYTE)bHsyncSelection << 4));
            synctypetemp    = CSyncSearchSyncTypeVGA();
            break;
#endif // #if (_SCALER_TYPE != _RTD2547D)

#if((_TMDS_SUPPORT == _ON) || (_HDMI_SUPPORT == _ON))

        case _DVI_PORT:
        case _HDMI_PORT:
            synctypetemp    = CSyncSearchSyncTypeDVI();
            break;

        case _DVI_I_A0_PORT:

#if(_DVI_I_SOURCE_SWITCH_SUPPORT == _ON)
            if(GET_DVI_I_SOURCE_SWITCH())
#endif
            {
                synctypetemp    = CSyncSearchSyncTypeDVI();

                if(synctypetemp == _NO_SYNC_STATE)
                {
#if (_SCALER_TYPE != _RTD2547D)
                    CScalerSetBit(_SYNC_SELECT_47, ~(_BIT3 | _BIT2), 0x00);

#if (_SCALER_TYPE == _RTD2553V || _SCALER_TYPE == _RTD2546N || _SCALER_TYPE == _RTD2525L)
					CScalerSetDataPortBit(_ADC_ACCESS_PORT_DC, 0x00, ~_BIT3, 0x00);
#else
                    CScalerSetBit(_ADC_RGB_CTRL_DC, ~_BIT3, 0x00);
#endif
#endif // #if (_SCALER_TYPE != _RTD2547D)

                    CScalerSetBit(_SYNC_SELECT_47, ~_BIT4, ((BYTE)bHsyncSelection << 4));
                    synctypetemp    = CSyncSearchSyncTypeVGA();
                }
            }
#if(_DVI_I_SOURCE_SWITCH_SUPPORT == _ON)
            else
            {
#if (_SCALER_TYPE != _RTD2547D)
                CScalerSetBit(_SYNC_SELECT_47, ~(_BIT3 | _BIT2), 0x00);
#if (_SCALER_TYPE == _RTD2553V || _SCALER_TYPE == _RTD2546N || _SCALER_TYPE == _RTD2525L)
				CScalerSetDataPortBit(_ADC_ACCESS_PORT_DC, 0x00, ~_BIT3, 0x00);
#else
                CScalerSetBit(_ADC_RGB_CTRL_DC, ~_BIT3, 0x00);
#endif
#endif // #if (_SCALER_TYPE != _RTD2547D)

                CScalerSetBit(_SYNC_SELECT_47, ~_BIT4, ((BYTE)bHsyncSelection << 4));
                synctypetemp    = CSyncSearchSyncTypeVGA();

                if(synctypetemp == _NO_SYNC_STATE)
                {
                    synctypetemp    = CSyncSearchSyncTypeDVI();
                }
            }
#endif
            break;

#if (_SCALER_TYPE != _RTD2547D)
        case _DVI_I_A1_PORT:
#if(_DVI_I_SOURCE_SWITCH_SUPPORT == _ON)
            if(GET_DVI_I_SOURCE_SWITCH())
#endif
            {
                synctypetemp    = CSyncSearchSyncTypeDVI();

                if(synctypetemp == _NO_SYNC_STATE)
                {
                    CScalerSetBit(_SYNC_SELECT_47, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));
#if (_SCALER_TYPE == _RTD2553V || _SCALER_TYPE == _RTD2546N || _SCALER_TYPE == _RTD2525L)
					CScalerSetDataPortBit(_ADC_ACCESS_PORT_DC, 0x00, ~_BIT3, _BIT3);
#else
                    CScalerSetBit(_ADC_RGB_CTRL_DC, ~_BIT3, _BIT3);
#endif
                    CScalerSetBit(_SYNC_SELECT_47, ~_BIT4, ((BYTE)bHsyncSelection << 4));
                    synctypetemp    = CSyncSearchSyncTypeVGA();
                }
            }
#if(_DVI_I_SOURCE_SWITCH_SUPPORT == _ON)
            else
            {
                CScalerSetBit(_SYNC_SELECT_47, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));
#if (_SCALER_TYPE == _RTD2553V || _SCALER_TYPE == _RTD2546N || _SCALER_TYPE == _RTD2525L)
				CScalerSetDataPortBit(_ADC_ACCESS_PORT_DC, 0x00, ~_BIT3, _BIT3);
#else
                CScalerSetBit(_ADC_RGB_CTRL_DC, ~_BIT3, _BIT3);
#endif
                CScalerSetBit(_SYNC_SELECT_47, ~_BIT4, ((BYTE)bHsyncSelection << 4));
                synctypetemp    = CSyncSearchSyncTypeVGA();

                if(synctypetemp == _NO_SYNC_STATE)
                {
                    synctypetemp    = CSyncSearchSyncTypeDVI();
                }
            }
#endif
            break;
#endif // #if (_SCALER_TYPE != _RTD2547D)

#endif
 //   case _VIDEO_PORT:
  //      synctypetemp    = _VIDEO8_STATE;
  //      break;
    }
    
#if (_SCALER_TYPE == _RTD2553V || _SCALER_TYPE == _RTD2546N || _SCALER_TYPE == _RTD2525L || _SCALER_TYPE == _RTD2547D)

    // Modify polarity
    #if(_HSYNC_TYPE_DETECTION == _AUTO_RUN)
        if(synctypetemp != _VIDEO8_STATE)    
    #endif	// End of #if(_HSYNC_TYPE_DETECTION == _AUTO_RUN)
    #if(_HSYNC_TYPE_DETECTION == _NORMAL_RUN)
        if((synctypetemp != _VIDEO8_STATE) && (synctypetemp != _SS_STATE))   
    #endif	// End of #if(_HSYNC_TYPE_DETECTION == _NORMAL_RUN)

#else

    if((synctypetemp != _SS_STATE) && (synctypetemp != _VIDEO8_STATE))
#endif
    {
 #if(_VIDEO_SUPPORT && _VIDEO_CHIP == _VDC_TB1334 && _HSYNC_TYPE_DETECTION == _AUTO_RUN)
        if((bSourceVideo() && synctypetemp == _SS_STATE))
            return synctypetemp;
 #endif

        CAdjustSyncProcessorMeasureStart();
        if(CTimerPollingEventProc(60, CMiscModeMeasurePollingEvent))
        {
            if(CModeMeasureData())
            {
                CSyncModifyPolarityVGA();
            }
            else
            {
                synctypetemp = _NO_SYNC_STATE;
            }
        }
        else
        {
            synctypetemp = _NO_SYNC_STATE;
        }
    }

    return synctypetemp;
}

//--------------------------------------------------
// Description  : Search VGA sync type
// Input Value  : None
// Output Value : Return sync type
//--------------------------------------------------
BYTE CSyncSearchSyncTypeVGA(void)
{
#define _SYNCTYPE_CONFIRM_TIMES   3
    
    BYTE synctypeprev, synctypecurr, cnt;
    
    cnt = _SYNCTYPE_CONFIRM_TIMES;
    do
    {
#if (_SCALER_TYPE == _RTD2553V || _SCALER_TYPE == _RTD2546N || _SCALER_TYPE == _RTD2525L || _SCALER_TYPE == _RTD2547D)

 #if(_VIDEO_SUPPORT && _VIDEO_CHIP == _VDC_TB1334)
    if (bSourceVideo())
        synctypecurr = CSyncGetSyncTypeStepVGA();
    else
 #endif // #if(_VIDEO_SUPPORT && _VIDEO_CHIP == _VDC_TB1334)
    {
    #if(_HSYNC_TYPE_DETECTION == _NORMAL_RUN)
        synctypecurr = CSyncGetSyncTypeStepVGA();
    #elif(_HSYNC_TYPE_DETECTION == _AUTO_RUN)
        synctypecurr = CSyncGetSyncTypeAutoRun();
    #endif
    }
#else
        synctypecurr = CSyncGetSyncTypeStep1VGA();
#endif

        if(cnt == _SYNCTYPE_CONFIRM_TIMES)
        {
            synctypeprev = synctypecurr;
            continue;
        }
        
        if(synctypecurr != synctypeprev)
        {
            return _NO_SYNC_STATE;
        }
        
    }
    while(--cnt);
    
    return synctypecurr;
    
#undef _SYNCTYPE_CONFIRM_TIMES
}


#if (_SCALER_TYPE == _RTD2553V || _SCALER_TYPE == _RTD2546N || _SCALER_TYPE == _RTD2525L || _SCALER_TYPE == _RTD2547D)
#if(_HSYNC_TYPE_DETECTION == _NORMAL_RUN || _TMDS_SUPPORT == _ON || (_VIDEO_SUPPORT && _VIDEO_CHIP == _VDC_TB1334))// || _HDMI_SUPPORT == _ON)
//--------------------------------------------------
// Description  : 
// Input Value  : None
// Output Value : 
//--------------------------------------------------
void CDisableVideoSetting(void)
{   // eric 1124 add for change source TV -> DVI always in search state
    // Disable video settings
#if (_SCALER_TYPE == _RTD2547D)
    CScalerPageSelect(_PAGE0);
    CScalerSetByte(_P0_ADC_POWER_AD, 0x18);
    CScalerSetByte(_VGIP_ODD_CTRL_13, 0x00);
    CScalerSetByte(_YUV2RGB_CTRL_9C, 0x00);
    CScalerSetBit(_IPH_ACT_WID_H_16, ~(_BIT7 | _BIT3), 0x00);
    CScalerSetBit(_SCALE_CTRL_32, ~_BIT7, 0x00);
#else
    CScalerSetByte(_VGIP_ODD_CTRL_08, 0x00);
    CScalerSetByte(_YUV2RGB_CTRL_89, 0x00);
    CScalerSetBit(_IPH_ACT_WID_H_0B, ~(_BIT7 | _BIT3), 0x00);
    CScalerSetBit(_SCALE_CTRL_19, ~_BIT7, 0x00);
#endif
    CScalerSetBit(_SYNC_CTRL_49, ~(_BIT2 | _BIT1 | _BIT0), _BIT2 | _BIT1);
    CScalerSetBit(_SYNC_INVERT_48, ~(_BIT4 | _BIT2), (_BIT4 | _BIT2));
                   /*
    if((bit)CScalerGetBit(_SYNC_SELECT_47, _BIT4)) //V304 modify
    {
        CScalerSetByte(_ADC_ACCESS_PORT_DC,0x8e);
        CScalerSetByte(_ADC_DATA_PORT_DD,0x04);
    }                */
}
#endif

#else

//--------------------------------------------------
// Description  : 
// Input Value  : None
// Output Value : 
//--------------------------------------------------
void CDisableVideoSetting(void)
{   // eric 1124 add for change source TV -> DVI always in search state
    // Disable video settings
    CScalerSetByte(_VGIP_ODD_CTRL_08, 0x00);
    CScalerSetByte(_YUV2RGB_CTRL_89, 0x00);
    CScalerSetBit(_IPH_ACT_WID_H_0B, ~(_BIT7 | _BIT3), 0x00);
    CScalerSetBit(_SCALE_CTRL_19, ~_BIT7, 0x00);
    CScalerSetBit(_CLAMP_CTRL0_5C, ~_BIT6, 0x00);
    CScalerSetByte(_CLAMP_START_5A, 0x04);
    CScalerSetByte(_CLAMP_END_5B, 0x10);

   // if((bit)CScalerGetBit(_SYNC_SELECT_47, _BIT4)) //V304 modify
     //   CScalerSetByte(_ADC_TEST_EA,0x04);
}
#endif

#if (_SCALER_TYPE == _RTD2553V || _SCALER_TYPE == _RTD2546N || _SCALER_TYPE == _RTD2525L || _SCALER_TYPE == _RTD2547D)
#if(_HSYNC_TYPE_DETECTION == _NORMAL_RUN || (_VIDEO_SUPPORT && _VIDEO_CHIP == _VDC_TB1334))
//--------------------------------------------------
// Description  : 
// Input Value  : None
// Output Value : 
//--------------------------------------------------
BYTE CSyncGetSyncTypeStepVGA(void)
{
    BYTE flag, cnt = 0;

#if(_SCALER_TYPE != _RTD2547D)
    CScalerSetDataPortByte(_ADC_ACCESS_PORT_DC, 0x0c, 0x38);
#endif
    /*
    CScalerSetByte(_VGIP_ODD_CTRL_08, 0x00);
    CScalerSetByte(_YUV2RGB_CTRL_89, 0x00);
    CScalerSetBit(_IPH_ACT_WID_H_0B, ~(_BIT7 | _BIT3), 0x00);
    CScalerSetBit(_SCALE_CTRL_19, ~_BIT7, 0x00);
    CScalerSetBit(_SYNC_CTRL_49, ~(_BIT2 | _BIT1 | _BIT0), _BIT2 | _BIT1);
    CScalerSetBit(_SYNC_INVERT_48, ~(_BIT4 | _BIT2), (_BIT4 | _BIT2));

    if((bit)CScalerGetBit(_SYNC_SELECT_47, _BIT4)) //V304 modify
    {
        CScalerSetByte(_ADC_ACCESS_PORT_DC,0x8e);
        CScalerSetByte(_ADC_DATA_PORT_DD,0x04);
    }       */
    CDisableVideoSetting();

#if(_SCALER_TYPE == _RTD2553V || _SCALER_TYPE == _RTD2546N)

    CScalerSetBit(_VSYNC_COUNTER_LEVEL_MSB_4C, ~_BIT3, 0x00);
    CScalerSetBit(_CLAMP_CTRL0_5C, ~_BIT6, 0x00);
    CScalerSetByte(_CLAMP_START_5A, 0x04);
    CScalerSetByte(_CLAMP_END_5B, 0x10);

#elif(_SCALER_TYPE == _RTD2525L)

    CScalerSetByte(_SYNC_PROC_ACCESS_PORT_5C,0x00);
    CScalerSetByte(_SYNC_PROC_DATA_PORT_5D,0x04);
    CScalerSetByte(_SYNC_PROC_ACCESS_PORT_5C,0x01);
    CScalerSetByte(_SYNC_PROC_DATA_PORT_5D,0x10);
    CScalerSetByte(_SYNC_PROC_ACCESS_PORT_5C,0x02);
    CScalerSetByte(_SYNC_PROC_DATA_PORT_5D,0x04);
    CScalerSetByte(_SYNC_PROC_ACCESS_PORT_5C,0x03);
    CScalerSetByte(_SYNC_PROC_DATA_PORT_5D,0x10);
    CScalerSetDataPortBit2(_SYNC_PROC_ACCESS_PORT_5C, 0x04, ~(_BIT7 | _BIT6), 0x00);

#endif

    CScalerSetBit(_SYNC_SELECT_47, ~_BIT5, _BIT5);  //Enable De-composite circuit

    do
    {
        CScalerSetBit(_STABLE_MEASURE_4F, ~_BIT0, 0x00);
        CScalerSetBit(_STABLE_MEASURE_4F, ~_BIT0, _BIT0);


        if(!CTimerPollingEventProc(20, CMiscStableFlagPollingEvent))
        {
            if((bit)CScalerGetBit(_HSYNC_TYPE_DETECTION_FLAG_4E, _BIT7))
            {
                return _NO_SYNC_STATE;	//No signal
            }
            else
            {
                return _NO_SYNC_STATE;	//Not support
            }
        }

        CScalerSetBit(_STABLE_MEASURE_4F, ~_BIT1, _BIT1);

        if(!(bit)CScalerGetBit(_STABLE_MEASURE_4F, _BIT6))
        {
            CScalerSetBit(_SYNC_INVERT_48, ~_BIT3, CScalerGetBit(_SYNC_INVERT_48, _BIT3) ^ _BIT3);
            cnt++;
        }
        else
        {
            break;
        }

        if(cnt >= 2)
            return _NO_SYNC_STATE;
    }
    while(_TRUE);

    // Get stable period
    CScalerRead(_STABLE_PERIOD_H_50, 2, pData, _AUTOINC);
    ((WORD *)pData)[1] = ((pData[0] & 0x07) << 8) | pData[1];
    CScalerSetBit(_VSYNC_COUNTER_LEVEL_MSB_4C, ~(_BIT2 | _BIT1 | _BIT0), (BYTE)(((WORD *)pData)[1] >> 9) & 0x07);
    CScalerSetByte(_VSYNC_COUNTER_LEVEL_LSB_4D, (BYTE)(((WORD *)pData)[1] >> 1));

    CScalerSetByte(_HSYNC_TYPE_DETECTION_FLAG_4E, 0xff);
    CTimerDelayXms(40);
	flag = CScalerGetBit(_HSYNC_TYPE_DETECTION_FLAG_4E, 0xff);

    if((bit)(flag & _BIT6) || (bit)(flag & _BIT5) || (bit)(flag & _BIT3))
    {
        return _NO_SYNC_STATE;
    }
	else if((bit)(flag & _BIT1))  // Composite-Sync
	{
		CScalerSetBit(_SYNC_CTRL_49, ~(_BIT6 | _BIT5 | _BIT2), (_BIT6 | _BIT5 | _BIT2));

		if((bit)(flag & _BIT0))	  // Not SOY signal
		{
			CScalerSetBit(_SYNC_INVERT_48, ~(_BIT6 | _BIT1), (_BIT6 | _BIT1));

			if((bit)(flag & _BIT2))	  
				return _CS_STATE;  //CS with Equalizer
			else
				return _CS_STATE;  //OR-Type & XOR-Type CS
		}
		else
		{
		   	CScalerSetBit(_SYNC_INVERT_48, ~(_BIT6 | _BIT1), 0x00);

			if((bit)(flag & _BIT2))	  
				return _SOY_STATE;  //YPbPr
			else
#if(_YPBPR_SUPPORT == _ON)
                if((bit)CScalerGetBit(_SYNC_SELECT_47, _BIT4))
                    return _SOY_STATE;
                else
            	    return _CS_STATE;
#else
                return _CS_STATE;
#endif  //End of #if(_YPBPR_SUPPORT == _ON)
		}
	}
	else
	{
    	// Check if Hsync only
	   	CScalerSetBit(_SYNC_CTRL_49, ~(_BIT6 | _BIT5 | _BIT2), _BIT2);		
		CScalerSetBit(_SYNC_SELECT_47, ~_BIT5, 0x00);  //Disable De-composite circuit
    	CAdjustSyncProcessorMeasureStart();
    	if(CTimerPollingEventProc(60, CMiscModeMeasurePollingEvent))
    	{
        	if(CModeMeasureData())
        	{
            	CSyncModifyPolarityVGA();
            	return _SS_STATE;
        	}
        	else
        	{
            	return _NO_SYNC_STATE;
        	}
    	}
    	else
    	{
        	return _NO_SYNC_STATE;
    	}
	}
}
#endif	// End of #if(_HSYNC_TYPE_DETECTION == _NORMAL_RUN)

#else
//--------------------------------------------------
// Description  : Get VGA sync type (step 1)
// Input Value  : None
// Output Value : Return sync type
//--------------------------------------------------
BYTE CSyncGetSyncTypeStep1VGA(void)
{
    BYTE cnt = 0;

    // Enable ADC bandgap and SOG power
    CScalerSetByte(_ADC_POWER_CTRL_E8, 0x38);

    // Disable video settings
    CDisableVideoSetting();
    /*
    CScalerSetByte(_VGIP_ODD_CTRL_08, 0x00);
    CScalerSetByte(_YUV2RGB_CTRL_89, 0x00);
    CScalerSetBit(_IPH_ACT_WID_H_0B, ~(_BIT7 | _BIT3), 0x00);
    CScalerSetBit(_SCALE_CTRL_19, ~_BIT7, 0x00);
    CScalerSetBit(_CLAMP_CTRL0_5C, ~_BIT6, 0x00);
    */

    CScalerSetByte(_SYNC_CTRL_49, 0x06);
    CScalerSetBit(_SYNC_INVERT_48, ~(_BIT4 | _BIT2), (_BIT4 | _BIT2));
#if (_SCALER_TYPE != _RTD2553V && _SCALER_TYPE != _RTD2546N && _SCALER_TYPE != _RTD2525L)

    CScalerSetBit(_STABLE_COUNT_4F, ~_BIT0, 0x00);
    CScalerSetBit(_STABLE_COUNT_4F, ~_BIT0, _BIT0);
    if(!CTimerPollingEventProc(20, CMiscStableFlagPollingEvent))
    {
       if((bit)CScalerGetBit(_STABLE_PERIOD_H_50, _BIT7))
       {
            return _NO_SYNC_STATE;	//No signal
       }
       else
       {
            return _NO_SYNC_STATE;	//Not support
       }
    }
    CScalerSetBit(_STABLE_COUNT_4F, ~_BIT4, _BIT4);

    // Set 1/4 period for Fix-Length of polarity measure method
    CScalerRead(_STABLE_PERIOD_H_50, 2, pData, _AUTOINC);
    ((WORD *)pData)[1] = ((pData[0] & 0x07) << 8) | pData[1];
    CScalerSetByte(_SYNC_POLARITY_PERIOD_COUNT_4E, (BYTE)(((WORD *)pData)[1] >> 3));
    CScalerSetBit(_STABLE_COUNT_4F, ~_BIT0, 0x00);

#endif
    CScalerSetBit(_STABLE_COUNT_4F, ~_BIT1, _BIT1);
    do
    {
        CScalerSetBit(_STABLE_COUNT_4F, ~_BIT0, 0x00);
        CScalerSetBit(_STABLE_COUNT_4F, ~_BIT0, _BIT0);
        CScalerSetBit(_STABLE_PERIOD_H_50, ~_BIT4, 0x00);
        
        if(!CTimerPollingEventProc(20, CMiscStableFlagPollingEvent))
        {
            if((bit)CScalerGetBit(_STABLE_PERIOD_H_50, _BIT7))
            {
                return _NO_SYNC_STATE;
            }
            else
            {
                return _NO_SYNC_STATE;
            }
        }
        
        CScalerSetBit(_STABLE_COUNT_4F, ~_BIT4, _BIT4);
        
        if(!(bit)CScalerGetBit(_STABLE_PERIOD_H_50, _BIT3))
        {
            CScalerSetBit(_SYNC_INVERT_48, ~_BIT3, CScalerGetBit(_SYNC_INVERT_48, _BIT3) ^ _BIT3);
            cnt++;
        }
        else
        {
            break;
        }
        
        if(cnt >= 2)
            return _NO_SYNC_STATE;
    }
    while(_TRUE);

    // Get stable period
    CScalerRead(_STABLE_PERIOD_H_50, 2, pData, _AUTOINC);
    ((WORD *)pData)[1] = ((pData[0] & 0x07) << 8) | pData[1];
    CScalerSetBit(_VSYNC_COUNTER_LEVEL_MSB_4C, ~(_BIT2 | _BIT1 | _BIT0), (BYTE)(((WORD *)pData)[1] >> 9) & 0x07);
    CScalerSetByte(_VSYNC_COUNTER_LEVEL_LSB_4D, (BYTE)(((WORD *)pData)[1] >> 1));

    CScalerSetBit(_VSYNC_COUNTER_LEVEL_MSB_4C, ~_BIT4, 0x00);
    CScalerSetBit(_SYNC_SELECT_47, ~(_BIT6 | _BIT5), _BIT5);
    CScalerSetBit(_STABLE_COUNT_4F, ~_BIT6, 0x00);
    
    CScalerSetBit(_DETECT_HSYNC_PERIOD_LSB_4B, ~_BIT7, 0x00);
    
    CTimerDelayXms(40);
    
    if((bit)CScalerGetBit(_STABLE_COUNT_4F, _BIT6))
    {
        if((bit)CScalerGetBit(_STABLE_PERIOD_H_50, _BIT6))
        {
            return _NO_SYNC_STATE;
        }
        else
        {
            CScalerSetBit(_SYNC_CTRL_49, ~(_BIT6 | _BIT5), (_BIT6 | _BIT5));

            return CSyncGetSyncTypeStep2VGA();
        }
    }
    
    CScalerSetBit(_SYNC_CTRL_49, ~(_BIT6 | _BIT5), 0x00);
    
    CAdjustSyncProcessorMeasureStart();
    
    if(CTimerPollingEventProc(60, CMiscModeMeasurePollingEvent))
    {
        if(CModeMeasureData())
        {
            CSyncModifyPolarityVGA();
            return _SS_STATE;
        }
        else
        {
            return _NO_SYNC_STATE;
        }
    }
    else
    {
        return _NO_SYNC_STATE;
    }
}

//--------------------------------------------------
// Description  : Get VGA sync type (step 2, for Composite sync)
// Input Value  : None
// Output Value : Return sync type
//--------------------------------------------------
BYTE CSyncGetSyncTypeStep2VGA(void)
{
    if((bit)CScalerGetBit(_DETECT_HSYNC_PERIOD_LSB_4B, _BIT7))
    {
        CScalerSetBit(_SYNC_SELECT_47, ~_BIT6, _BIT6);
        
        CScalerSetBit(_SYNC_INVERT_48, ~(_BIT6 | _BIT1), (_BIT6 | _BIT1));
        CScalerSetBit(_CLAMP_CTRL1_5D, ~_BIT6, 0x00);
        CScalerSetBit(_SYNC_CTRL_49, ~_BIT2, _BIT2);
        
        CTimerDelayXms(40);
        
        return _CS_STATE;
    }
    
    CScalerSetBit(_VSYNC_COUNTER_LEVEL_MSB_4C, ~_BIT3, _BIT3);
    CScalerRead(_DETECT_HSYNC_PERIOD_MSB_4A, 2, pData, _AUTOINC);
    ((WORD *)pData)[1] = (pData[0] << 3) | (pData[1] & 0x07);
    
    CScalerSetBit(_STABLE_COUNT_4F, ~_BIT4, _BIT4);
    CScalerRead(_STABLE_PERIOD_H_50, 2, pData, _AUTOINC);
    ((WORD *)pData)[2] = ((pData[0] & 0x07) << 8) | pData[1];
    
    if(abs(((WORD *)pData)[1] - ((WORD *)pData)[2]) <= 1)
    {
        return CSyncCheckSOY();
    }
    else
    {
        CScalerSetBit(_SYNC_SELECT_47, ~_BIT6, _BIT6);
        CScalerSetBit(_SYNC_INVERT_48, ~(_BIT6 | _BIT1), (_BIT6 | _BIT1));
        CScalerSetBit(_CLAMP_CTRL1_5D, ~_BIT6, 0x00);
        CScalerSetBit(_SYNC_CTRL_49, ~_BIT2, _BIT2);

        CTimerDelayXms(40);

        return _CS_STATE;
    }
}

//--------------------------------------------------
// Description  : Check Sync between seration CS and SOY
// Input Value  : None
// Output Value : None
//--------------------------------------------------
BYTE CSyncCheckSOY(void)
{
    WORD vtotaltemp;
    BYTE firstfail = 0;

    CScalerSetBit(_SYNC_CTRL_49, ~_BIT2, _BIT2);
    CScalerSetBit(_CLAMP_CTRL1_5D, ~_BIT6, 0x00);
    CScalerSetBit(_SYNC_SELECT_47, ~_BIT6, _BIT6);
    CScalerSetBit(_SYNC_INVERT_48, ~(_BIT6 | _BIT1), (_BIT6 | _BIT1));

    CAdjustSyncProcessorMeasureStart();
    if(CTimerPollingEventProc(60, CMiscModeMeasurePollingEvent))
    {
        if(CModeMeasureData())
        {
            vtotaltemp = stModeInfo.IVTotal;
        }
        else
        {
            firstfail = 1;
            //return _NO_SYNC_STATE;
        }
    }
    else
    {
        firstfail = 1;
        //return _NO_SYNC_STATE;
    }

    CScalerSetBit(_SYNC_SELECT_47, ~_BIT6, 0x00);
    CScalerSetBit(_SYNC_INVERT_48, ~(_BIT6 | _BIT1), 0x00);

    CAdjustSyncProcessorMeasureStart();
    if(CTimerPollingEventProc(60, CMiscModeMeasurePollingEvent))
    {
        if(CModeMeasureData())
        {

#if(_YPBPR_SUPPORT == _ON)
            return _SOY_STATE;
#else
            if(abs(vtotaltemp - stModeInfo.IVTotal) <= 1)
            {
                return _SOY_STATE;
            }
            else
            {
                CScalerSetBit(_SYNC_SELECT_47, ~_BIT6, _BIT6);
                CScalerSetBit(_SYNC_INVERT_48, ~(_BIT6 | _BIT1), (_BIT6 | _BIT1));
                return _CS_STATE;
            }
#endif  // End of #if(_YPBPR_SUPPORT == _ON)

        }
        else
        {
            if(firstfail == 1)
                return _NO_SYNC_STATE;
            else
            {
                CScalerSetBit(_SYNC_SELECT_47, ~_BIT6, _BIT6);
                CScalerSetBit(_SYNC_INVERT_48, ~(_BIT6 | _BIT1), (_BIT6 | _BIT1));

                return _CS_STATE;
            }
        }
    }
    else
    {
        if(firstfail == 1)
            return _NO_SYNC_STATE;
        else
        {
            CScalerSetBit(_SYNC_SELECT_47, ~_BIT6, _BIT6);
            CScalerSetBit(_SYNC_INVERT_48, ~(_BIT6 | _BIT1), (_BIT6 | _BIT1));

            return _CS_STATE;
        }
    }
}
#endif

//--------------------------------------------------
// Description  : Modify VGA sync polarity
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CSyncModifyPolarityVGA(void)
{
    BYTE polarity;

#if (_SCALER_TYPE == _RTD2547D)
    polarity = CScalerGetBit(_VGIP_SIGINV_11, 0xff);
#else
    polarity = CScalerGetBit(_VGIP_SIGINV_06, 0xff);
#endif

    polarity &= ~(_BIT3 | _BIT2);

    if(!(bit)(stModeInfo.Polarity & _BIT0))
    {
        polarity |= _BIT2;
    }
    
    if(!(bit)(stModeInfo.Polarity & _BIT1))
    {
        polarity |= _BIT3;
    }
    
#if (_SCALER_TYPE == _RTD2547D)
    CScalerSetByte(_VGIP_SIGINV_11, polarity);
#else
    CScalerSetByte(_VGIP_SIGINV_06, polarity);
#endif
}

#if((_TMDS_SUPPORT == _ON) || (_HDMI_SUPPORT == _ON))
//--------------------------------------------------
// Description  : Search DVI sync type
// Input Value  : None
// Output Value : Return sync type
//--------------------------------------------------
BYTE CSyncSearchSyncTypeDVI(void)
{
    BYTE synctypetemp = _DSS_STATE;
    
    // Disable video settings
#if (_SCALER_TYPE == _RTD2547D)   
    CScalerSetByte(_VGIP_ODD_CTRL_13, 0x00);
    
    if(!CHdmiFormatDetect())
       	CScalerSetByte(_YUV2RGB_CTRL_9C, 0x00);
    
    CScalerSetBit(_IPH_ACT_WID_H_16, ~(_BIT7 | _BIT3), 0x00);
    CScalerSetBit(_SCALE_CTRL_32, ~_BIT7, 0x00);
  //  CScalerSetBit(_VSYNC_COUNTER_LEVEL_MSB_4C, ~_BIT3, 0x00);
#else
    CDisableVideoSetting();
#endif

    CPowerADCAPLLOff();
#if (_SCALER_TYPE == _RTD2547D)
    CScalerPageSelect(_PAGE2);

    if(!CSourceScanInputPortDVI((bit)CScalerGetBit(_P2_POWER_ON_OFF_CTRL_A7, _BIT7)))
#else    
    if(!CSourceScanInputPortDVI((bit)CScalerGetBit(_POWER_ON_OFF_CTRL_C2, _BIT7)))
#endif
        return _NO_SYNC_STATE;

#if(((_TMDS_SUPPORT == _ON) || (_HDMI_SUPPORT == _ON)) && (_DVI_LONG_CABLE_SUPPORT == _ON))

    if(CAdjustTMDSEqualizer() == _FALSE)
        return _NO_SYNC_STATE;

#endif

    CPowerTMDSOn();
    
    return synctypetemp; 
}
#endif  // End of #if((_TMDS_SUPPORT == _ON) || (_HDMI_SUPPORT == _ON))



#if (_SCALER_TYPE == _RTD2553V || _SCALER_TYPE == _RTD2546N || _SCALER_TYPE == _RTD2525L || _SCALER_TYPE == _RTD2547D)
#if(_HSYNC_TYPE_DETECTION == _AUTO_RUN)

#if(_NEW_YPBPR && _YPBPR_SUPPORT && _SCALER_TYPE != _RTD2547D)

BYTE xdata SyncLevelOffset = 0;

#define SOGSyncLevel 		0x25
#define MinSOGSyncLevel		0x16

void CYPbPrAutoSOY(void)
{
    // For YPbPr eric 1017
    CScalerSetByte(_ADC_ACCESS_PORT_DC,0x8e);
    CScalerSetByte(_ADC_DATA_PORT_DD,0x04);

	if((SOGSyncLevel - SyncLevelOffset) < MinSOGSyncLevel)		
    	SyncLevelOffset = 0;
           
	if(CGetSourcePortType(_GET_INPUT_SOURCE()) == _YPBPR_A0_PORT)
	    CScalerSetDataPortByte(_ADC_ACCESS_PORT_DC, 0x0A, SOGSyncLevel - SyncLevelOffset);	// SOG0 Sync level
	else
	    CScalerSetDataPortByte(_ADC_ACCESS_PORT_DC, 0x0B, SOGSyncLevel - SyncLevelOffset);	// SOG1 Sync level
	         
}

BYTE CSyncGetSyncTypeAutoRun(void)
{
	BYTE flag;

    CScalerSetDataPortByte(_ADC_ACCESS_PORT_DC, 0x0c, 0x38);	// SOG0/SOG1 power on, band-gap power on
    CScalerSetByte(_VGIP_ODD_CTRL_08, 0x00);						// VGIP odd control
    CScalerSetByte(_YUV2RGB_CTRL_89, 0x00);						// Disable YUV to RGB convertion
    CScalerSetBit(_IPH_ACT_WID_H_0B, ~(_BIT7 | _BIT3), 0x00);		// Single colok
    CScalerSetBit(_SCALE_CTRL_19, ~_BIT7, 0x00);					// Disable video compensation
    CScalerSetBit(_VSYNC_COUNTER_LEVEL_MSB_4C, ~_BIT3, 0x00);	// Switch 2nd ADC/video8 as 2nd ADC
    CScalerSetBit(_VSYNC_COUNTER_LEVEL_MSB_4C, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);
    CScalerSetBit(_SYNC_CTRL_49, ~(_BIT2 | _BIT1 |_BIT0), _BIT2 | _BIT1);		// Select SeHS or DeHS
    CScalerSetBit(_VSYNC_COUNTER_LEVEL_MSB_4C, ~_BIT3, 0x00);
    CScalerSetBit(_CLAMP_CTRL0_5C, ~_BIT6, 0x00);					// Clamp trigger edge as leading edge

    CScalerSetByte(_CLAMP_START_5A, 0x04);
    CScalerSetByte(_CLAMP_END_5B, 0x10);


	CScalerSetBit(_SYNC_SELECT_47, ~_BIT6, 0x00);
	CScalerSetBit(_SYNC_SELECT_47, ~_BIT6, _BIT6); 				//Enable hsync type detection auto run

	if(CTimerPollingEventProc(90, CMiscHsyncTypeAutoRunFlagPollingEvent))
	{
        flag = (CScalerGetBit(_VSYNC_COUNTER_LEVEL_MSB_4C, 0xff) & 0x70) >> 4;
        ucStablePol = ~(CScalerGetBit(_STABLE_PERIOD_H_50, _BIT6) >> 6); //Get Hsync Polarity

#if(_YPBPR_SUPPORT)
    	if(_GET_INPUT_SOURCE() == _SOURCE_YPBPR)
        {
    		if((flag == 0)||(flag == 1))
            {	// No-signal or Not-support
    			SyncLevelOffset++;
    			CYPbPrAutoSOY();		// Adjust SOG sync level
    		}	
    	}
#endif // #if(_YPBPR_SUPPORT)

		switch(flag)
    	{
            case 0:		// No Signal
                return _NO_SYNC_STATE;
            
            case 1:		// Not Support
                return _NO_SYNC_STATE;
            
            case 2:		// YPbPr-Type CS
                return _SOY_STATE;
            
            case 3:		// Serration-Type CS
#if(_YPBPR_SUPPORT == _ON)
                if((bit)CScalerGetBit(_SYNC_SELECT_47, _BIT4))
                    return _SOY_STATE;
                else
                    return _CS_STATE;
#else
                    return _CS_STATE;
#endif  //End of #if(_YPBPR_SUPPORT == _ON)
            
            case 4:		// CS with Equalizer
                return _CS_STATE;
            
            case 5:		// OR-Type & XOR-Type CS
                return _CS_STATE;
            
            case 6:		// Separate Sync
                return _SS_STATE;
            
            default:	// Hsync only
                return _NO_SYNC_STATE;
    		}

	}
	else
	{
    	return _NO_SYNC_STATE;
	}

}

#else   

#if(_YPBPR_SUPPORT == _ON && _SCALER_TYPE != _RTD2547D)
/*
BYTE xdata SyncLevelOffset = 0;

#define SOGSyncLevel 		0x20
#define MinSOGSyncLevel		0x16

void CYPbPrAutoSOY(void)
{
    // For YPbPr eric 1017
    CScalerSetByte(_ADC_ACCESS_PORT_DC,0x8e);
    CScalerSetByte(_ADC_DATA_PORT_DD,0x04);

	if((SOGSyncLevel - SyncLevelOffset) < MinSOGSyncLevel)		
    	SyncLevelOffset = 0;
           
	if(CGetSourcePortType(_GET_INPUT_SOURCE()) == _YPBPR_A0_PORT)
	    CScalerSetDataPortByte(_ADC_ACCESS_PORT_DC, 0x0A, SOGSyncLevel - SyncLevelOffset);	// SOG0 Sync level
	else
	    CScalerSetDataPortByte(_ADC_ACCESS_PORT_DC, 0x0B, SOGSyncLevel - SyncLevelOffset);	// SOG1 Sync level
	         
}*/
#endif
    
//-------------------------------------------------------------------
// Description  : Get VGA sync type by Hsync Type Detection Auto Run
// Input Value  : None
// Output Value : Return sync type
//-------------------------------------------------------------------
BYTE CSyncGetSyncTypeAutoRun(void)
{
    BYTE flag;

#if (_SCALER_TYPE == _RTD2547D)

    CScalerPageSelect(_PAGE0);
    CScalerSetByte(_P0_ADC_POWER_AD, 0x18);
    CScalerSetByte(_VGIP_ODD_CTRL_13, 0x00);
    CScalerSetBit(_IPH_ACT_WID_H_16, ~(_BIT7 | _BIT3), 0x00);
    CScalerSetBit(_SCALE_CTRL_32, ~_BIT7, 0x00);
    CScalerSetBit(_SYNC_CTRL_49, ~(_BIT2 | _BIT1 | _BIT0), _BIT2 | _BIT1);
    CScalerSetByte(_YUV2RGB_CTRL_9C, 0x00);

#else

	CScalerSetDataPortByte(_ADC_ACCESS_PORT_DC, 0x0c, 0x38);
    CScalerSetByte(_VGIP_ODD_CTRL_08, 0x00);
    CScalerSetByte(_YUV2RGB_CTRL_89, 0x00);
    CScalerSetBit(_IPH_ACT_WID_H_0B, ~(_BIT7 | _BIT3), 0x00);
    CScalerSetBit(_SCALE_CTRL_19, ~_BIT7, 0x00);
    CScalerSetBit(_SYNC_CTRL_49, ~(_BIT2 | _BIT1 | _BIT0), _BIT2 | _BIT1);
#if(_SCALER_TYPE == _RTD2553V || _SCALER_TYPE == _RTD2546N)

   	CScalerSetBit(_VSYNC_COUNTER_LEVEL_MSB_4C, ~_BIT3, 0x00);
    CScalerSetBit(_CLAMP_CTRL0_5C, ~_BIT6, 0x00);
    CScalerSetByte(_CLAMP_START_5A, 0x04);
    CScalerSetByte(_CLAMP_END_5B, 0x10);

#elif(_SCALER_TYPE == _RTD2525L)

    CScalerSetByte(_ADC_ACCESS_PORT_DC,0x8e);
    CScalerSetByte(_ADC_DATA_PORT_DD,0x00);
    CScalerSetByte(_SYNC_PROC_ACCESS_PORT_5C,0x00);
    CScalerSetByte(_SYNC_PROC_DATA_PORT_5D,0x04);
    CScalerSetByte(_SYNC_PROC_ACCESS_PORT_5C,0x01);
    CScalerSetByte(_SYNC_PROC_DATA_PORT_5D,0x10);
    CScalerSetByte(_SYNC_PROC_ACCESS_PORT_5C,0x02);
    CScalerSetByte(_SYNC_PROC_DATA_PORT_5D,0x04);
    CScalerSetByte(_SYNC_PROC_ACCESS_PORT_5C,0x03);
    CScalerSetByte(_SYNC_PROC_DATA_PORT_5D,0x10);
    CScalerSetDataPortBit2(_SYNC_PROC_ACCESS_PORT_5C, 0x04, ~(_BIT7 | _BIT6), 0x00);


#endif
#endif // #if (_SCALER_TYPE == _RTD2547D)


    if((bit)CScalerGetBit(_SYNC_SELECT_47, _BIT4)) //V304 modify
    {
#if (_SCALER_TYPE == _RTD2547D)
        CScalerPageSelect(_PAGE0);
        CScalerSetByte(_P0_ADC_TEST_CTRL_AF, 0x04);
#else
        CScalerSetByte(_ADC_ACCESS_PORT_DC,0x8e);
        CScalerSetByte(_ADC_DATA_PORT_DD,0x04);
#endif
    }
    
    CScalerSetBit(_STABLE_MEASURE_4F, ~_BIT0, 0x00);
    CScalerSetBit(_STABLE_MEASURE_4F, ~_BIT0, _BIT0);
    if(!CTimerPollingEventProc(20, CMiscStableFlagPollingEvent))
    {
       if((bit)CScalerGetBit(_HSYNC_TYPE_DETECTION_FLAG_4E, _BIT7))
       {
            return _NO_SYNC_STATE;	//No signal
       }
       else
       {
            return _NO_SYNC_STATE;	//Not support
       }
    }
    CScalerSetBit(_STABLE_MEASURE_4F, ~_BIT1, _BIT1);

    // Get stable period
    CScalerRead(_STABLE_PERIOD_H_50, 2, pData, _AUTOINC);
    ((WORD *)pData)[1] = ((pData[0] & 0x07) << 8) | pData[1];
   	CScalerSetBit(_VSYNC_COUNTER_LEVEL_MSB_4C, ~(_BIT2 | _BIT1 | _BIT0), (BYTE)(((WORD *)pData)[1] >> 9) & 0x07);
    CScalerSetByte(_VSYNC_COUNTER_LEVEL_LSB_4D, (BYTE)(((WORD *)pData)[1] >> 1));
    CScalerSetBit(_STABLE_MEASURE_4F, ~_BIT0, 0x00);

    CScalerSetBit(_SYNC_SELECT_47, ~_BIT6, 0x00); 
    CScalerSetBit(_SYNC_SELECT_47, ~_BIT6, _BIT6); //Enable Hsync Type Detection Auto Run

    if(CTimerPollingEventProc(90, CMiscHsyncTypeAutoRunFlagPollingEvent))
    {
        flag = (CScalerGetBit(_VSYNC_COUNTER_LEVEL_MSB_4C, 0xff) & 0x70) >> 4;
   		ucStablePol = ~(CScalerGetBit(_STABLE_PERIOD_H_50, _BIT6) >> 6); //Get Hsync Polarity
             /*
#if(_YPBPR_SUPPORT)
    	if(_GET_INPUT_SOURCE() == _SOURCE_YPBPR)
        {
    		if((flag == 0)||(flag == 1))
            {	// No-signal or Not-support
    			SyncLevelOffset++;
    			CYPbPrAutoSOY();		// Adjust SOG sync level
    		}	
    	}
#endif // #if(_YPBPR_SUPPORT)
            */
		switch(flag)
        {
            case 0:		// No Signal
        	return _NO_SYNC_STATE;

            case 1:		// Not Support
        	return _NO_SYNC_STATE;

            case 2:		// YPbPr-Type CS
        	return _SOY_STATE;

            case 3:		// Serration-Type CS
            {
#if(_YPBPR_SUPPORT == _ON)
                switch(CGetSourcePortType(_GET_INPUT_SOURCE()))
                {
                    case _DSUB_A0_PORT:
                    case _DSUB_A1_PORT:
            	        return _CS_STATE;
                    case _YPBPR_A0_PORT:
                    case _YPBPR_A1_PORT:
                        return _SOY_STATE;
                    default:
            	        return _CS_STATE;
                }
#else
                return _CS_STATE;
#endif  //End of #if(_YPBPR_SUPPORT == _ON)
            }

            case 4:		// CS with Equalizer
        	return _CS_STATE;

            case 5:		// OR-Type & XOR-Type CS
        	return _CS_STATE;

            case 6:		// Separate Sync
    	    return _SS_STATE;

            default:	// Hsync only
        	return _NO_SYNC_STATE;
    	}

	}
    else
    {
        return _NO_SYNC_STATE;
    }

}
#endif // new ypbpr
#endif	// End of #if(_HSYNC_TYPE_DETECTION == _AUTO_RUN)
#endif


