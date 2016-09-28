//----------------------------------------------------------------------------------------------------
// Copyright of Realtek SemiConductor Corp. 
// Model   : RTD2533B & RTD2023LS
// Version : V3.00 (10.18.2005)
// 
//----------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------
// ID Code      : Main.c No.0002
// Update Note  : 
//
//----------------------------------------------------------------------------------------------------

#define __MAIN__

#include "Header\Include.h"


void CMainUserInitial(void)
{
	// User can make some initial settings at firmware startup
    CLR_KEYREPEATENABLE();
    CLR_PANELPOWERSTATUS();
    CLR_LIGHTPOWERSTATUS();
    CLR_FRAMESYNCSTATUS();
    CLR_POWERSWITCH();
    CLR_FIRST_ADCCLOCK();

	
#if(_HDMI_SUPPORT == _ON)
    CLR_HDMIINPUT();    
    CLR_AUDIOPLLLOCKREADY();
    CLR_AVRESUME();
    CLR_AUDIOWAITINGTIMEOUT();
#endif

    SET_FIRST_LOADFONT();
#if(_AUTO_SCAN_SOURCE)
    SET_SOURCE_AUTOCHANGE();
#endif
    
    SET_PRE_VGA_CONNECT(bVGACONNECT);
#if(_HDMI_SUPPORT == _ON)
    SET_PRE_HDMI_CONNECT(bHDMICONNECT);
#elif(_TMDS_SUPPORT == _ON)
    SET_PRE_DVI_CONNECT(bDVICONNECT);
#endif

#if(_SCALER_TYPE == _RTD2547D)
    CLR_INTERLACE_MODE();
#if(_FRC_SUPPORT == _ON)
    CLR_FRCTATUS();
#if(_FIELD_MERGE_SUPPORT == _ON)
    CLR_FIELDMERGE_MODE();
#endif
#endif
#endif
    CLR_USE_TRANSITION_RESULT();
    ucCurrState = _PWOFF_STATE;
#if(_AUTO_POWER_DOWN && _VIDEO_TV_SUPPORT)
    ucMinuteCount       = 0;
    ucAutoPowerDownTime = _GET_POWER_DOWN_TIME() * 15;
    if (0 == ucAutoPowerDownTime || !GET_POWERSTATUS()) // Auto power down time off
    {
        ucAutoPowerDownTime = 0xff;
    }
#endif
   
#if(_OSD_TYPE == _OSD007)
 #if(_OFF == _OSD_POSITION_ADJ_CTRL)
    stOsdUserData.OsdHPos = 50;
    stOsdUserData.OsdVPos = 50;
 #endif
#endif

if(Panel.DHWidth<=1024&&Panel.DVHeight<=768)
	_SET_OSD_SIZE(0);
}


//------------------------------------------------------------
bit CMainDetectSystemPower(void)
{
#if(_RESET_TYPE == _RESET_IN)

    if(!bLVRPOWERDETECT);
        return _FALSE;

#endif

#if(_SYSTEMPOWER_DETECT_SUPPORT == _ON)

    // It's an example F/W for RTD2120.
    MCU_ADC_CTRL_FF0B = 0x80;
    while((MCU_ADC_CTRL_FF0B & _BIT7) != 0x00);

    if((bSYSTEMPOWERDETECT & 0xfc) < 0xe0)
        return _FALSE;

#endif

    return _TRUE;
}


//------------------------------------------------------------
bit CMainResetCheck(void) //V306 modify
{
#if((_RESET_CHECK_SUPPORT == _ON) && (_SCALER_TYPE == _RTD2525L))

    // The Reset Check for RTD2525L.
    while(!GETSCALERSDIO3())
    {
        if(bSCALERSCLK)
            CLRSCALERSCLK();
        else
            SETSCALERSCLK();
    }

    CScalerRead(_ID_REG_00, 1, pData, _NON_AUTOINC);

    if((pData[0] != 0x31) || (!((bit)CScalerGetBit(_HOST_CTRL_01, _BIT6))))
        return _FALSE;

#endif  // End of #if((_RESET_CHECK_SUPPORT == _ON) && (_SCALER_TYPE == _RTD2525L))

    return _TRUE;
}

//------------------------------------------------------------
// eric 1227 add for check input source
void CCheckInputSource(void)
{
    bit bErrInputSource = 0;

    switch(_GET_INPUT_SOURCE())
    {
#if(!_VGA_SUPPORT)
    case _SOURCE_VGA:
        bErrInputSource = 1;
        break;
#endif

#if(!_TMDS_SUPPORT)
    case _SOURCE_DVI:
        bErrInputSource = 1;
        break;
#endif 
   
#if(!_HDMI_SUPPORT)
    case _SOURCE_HDMI:
        bErrInputSource = 1;
        break;
#endif    

#if(!_VIDEO_SUPPORT)
    case _SOURCE_VIDEO_AV:
    case _SOURCE_VIDEO_SV:
   // case _SOURCE_VIDEO_YUV:
    case _SOURCE_VIDEO_SCART:
    case _SOURCE_VIDEO_DVD:
        bErrInputSource = 1;
        break;
#endif  
  
#if(!_VIDEO_TV_SUPPORT)
    case _SOURCE_VIDEO_TV:
        bErrInputSource = 1;
        break;
#endif

#if(!_YPBPR_SUPPORT)
    case _SOURCE_YPBPR:
        bErrInputSource = 1;
        break;
#endif
    }
           
    if (bErrInputSource)
    {
        _SET_INPUT_SOURCE(_NORMAL_SOURCE);
        CEepromSaveSystemData();
    }
}
//------------------------------------------------------------
void CMainSystemInitial(void)
{

    // Initial MCU
    CMcuInitial();
	pData[3]=PNL3;
	pData[2]=PNL2;
	pData[1]=PNL1;
	
#if(DVD_EN)
	PanelIndex=((pData[1])<<2)|((pData[2])<<1)|((pData[3])<<0);
	PanelIndex=(~PanelIndex)&0x07;
#else
	PanelIndex=(PNL0<<3)|((pData[1])<<2)|((pData[2])<<1)|((pData[3])<<0);
	PanelIndex=(~PanelIndex)&0x0f;
#endif
       Panel=PanelArray[PanelIndex];
       Panel=PanelArray[PanelIndex];
#if(_IR_ENABLE)
    gmi_CStopIR();
#endif
    // Initial timer events
    CTimerInitialTimerEvent();

    MUTE_ON();
    CPowerLightPowerOff();
    CPowerPanelPowerOff();
    CLR_LIGHTPOWERSTATUS();
#if (_VIDEO_TV_SUPPORT)
//    TUNER_PWR_OFF();                 //
#endif

#if(_VIDEO_SUPPORT == _ON)
 #if(_VIDEO_CHIP == _VDC_TB1334)
    VideoDecAddress = 0;  // Only select 0,for TB1334 source AV/SV
 #else
    VideoDecAddress = _VIDEODEVICE;
 #endif
    gmi_CVDCOff();
#endif
        
    // Check eeprom and load eeprom settings
    CEepromStartupCheck();
    CCheckInputSource();  // eric 1227 add for check input source


#if(_VIDEO_TV_SUPPORT)
    ucVideoNoModeTime = 252;
#endif    //#if(_VIDEO_TV_SUPPORT)

    while(!CMainDetectSystemPower()); //V306 modify

#ifdef _SII164_INIT_SUPPORT
    CModeInitSiI164();
#endif

    // Scaler reset
#if(((_SCALER_TYPE == _RTD2023S) || (_SCALER_TYPE == _RTD2023S_VB) || (_SCALER_TYPE == _RTD2547D)) && (_RESET_TYPE == _RESET_IN))
    CScalerResetInForRTD2023();
#endif

#if((_SCALER_TYPE == _RTD2023L) || (_SCALER_TYPE == _RTD2023S) || (_SCALER_TYPE == _RTD2023L_VB) || (_SCALER_TYPE == _RTD2023S_VB))
    CScalerInitialForRTD2023();
#endif
    // Initial scaler settings
    CScalerInitial();
    
    // Initial key scan status
    CKeyInitial();
    
    // Initial source input port settings
//    CSourceInitialInputPort();

    // DAC Chip reset
#if(_SCALER_TYPE == _RTD2547D) 
#if(_DAC_SUPPORT == _ON)
    CHdmiResetDAC();
#endif
#endif

    // Initial user settings
    CMainUserInitial();

    //CVideoInitial();
    CInitInputSource();

#if(_RS232)
	CUartInit();
#endif
    
    // Add ddcci debug
#if(_ISPACK && _ISPACK_MCU == _ISPACK_TYPE)
    Init_DDCCI();
#endif

#if(_DDC_TYPE != _DDC_NONE)
    DDCInit();
#endif    

#if(_NEW_OSD_FUNC == 1)
    CheckLanguage();
#endif
    
    // Enable IR interrupt
#if(_IR_ENABLE)
    gmi_CStartIR();
#endif

#if(IR_Test_EN== _ON)    
	   _SET_INPUT_SOURCE(_SOURCE_VIDEO_TV);
          SET_POWERSTATUS();
#endif

	 CAdjustColorPalette(tPALETTE_0);
	// _SET_INPUT_SOURCE(_SOURCE_VIDEO_TV);//_SOURCE_VIDEO_AV;//_SOURCE_VGA; //_SOURCE_VIDEO_AV
	 _SET_OSD_DOUBLE_STATE(_OSD_NORMAL_STATE);//_OSD_DOUBLE_STATE, _OSD_NORMAL_STATE
	 SET_FAC_STATE(0);
  if(GET_BURNIN_STATE()==BURNIN_ON&&GET_POWERSTATUS()==0)
	{
	SET_NOSIGNAL_INFO(0);
	SET_POWERSWITCH();
	}	
if(_GET_FAC_POWER_SET()==0)
		CLR_POWERSTATUS();
else if (_GET_FAC_POWER_SET()==1)
{
   if(!GET_POWERSTATUS())
              SET_POWERSWITCH();
}

          SET_MUTE_STATE(STATE_MUTEOFF);
          SET_BURNIN_STATE(BURNIN_OFF);
   	   SET_DO_SHOW_NOTE(0);
	   _SET_CHANNEL_FOR_AUDIO(0);
	   	   _SET_INPUT_SOURCE(_SOURCE_VIDEO_TV);

}
//--------------------------------------------------
// Main Process
//--------------------------------------------------
void main(void)
{
	bit temp = 0;
    do
    {
        CMainSystemInitial();
	//-----------------------------------------------------------------------------
        MCU_PORT6_OE_FF04 = MCU_PORT6_OE_FF04 &(~_BIT7);
   //------------------------------------------------------------------------------				
        while(CMainDetectSystemPower() && CMainResetCheck()) //V306 modify
        {
            //CMiscIspDebugProc();

            #if(_DDC_TYPE != _DDC_NONE)
            DDCProc();
            #endif

            CTimerHandler();
            CKeyHandler();
            CMiscIspDebugProc();
			
#if(_VIDEO_SUPPORT && _VIDEO_CHIP != _VDC_TB1334)
            if (_GET_INPUT_SOURCE() != _SOURCE_VGA && 
                _GET_INPUT_SOURCE() != _SOURCE_DVI && 
                _GET_INPUT_SOURCE() != _SOURCE_HDMI && 
                _GET_INPUT_SOURCE() != _SOURCE_YPBPR)
            {        
                CVideoModeHandler();
            }
            else
#endif
				if (temp)
					{
            CModeHandler();
            COsdHandler();
					}

        }

    }
    while(_TRUE);
}
//--------------------------------------------------
