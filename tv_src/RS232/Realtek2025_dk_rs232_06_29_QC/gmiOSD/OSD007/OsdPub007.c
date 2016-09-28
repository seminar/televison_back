#define __OSD007_LCD_OSD__

#include "Header\Include.h"

#if(_OSD_TYPE == _OSD007)
#if(IR_Test_EN== _ON)    
	extern void Display_IR(); 
#endif

//-----------------------------------------------------------
void COsdHandler(void)
{    

    COsdSystemFlowProc();
    COsdEventMsgProc();


    if (_PWOFF_STATE == ucCurrState) 
        return;
    
	
            switch(ucKeyMessage)
            {
                case VK_SOURCE:
                case VK_IR_TV:
                case VK_IR_AV:
		  case VK_IR_SV:
		  case VK_IR_SCART:
		  case VK_IR_VGA:
		  case VK_AUTO:
	             switch(ucCurrState)
	            {
	                case _ACTIVE_STATE:
	                case _NOSUPPORT_STATE:
	                case _NOSIGNAL_STATE:
	                case _SLEEP_STATE:
	                case _SOURCE_CHANGE_STATE:
	                        CSourceChange();
	                       return;
                       default:   break;
		   	}
			return; 
                default:   break;				 
            	}		 

#if(_CHANGE_SOURCE_METHOD == _CHANGE_SOURCE_METHOD_0)
    if (ucChangeSourceCount)
        CChangeSourceHandler();
#endif   

#if(_FACTORY_MENU_EN)
#if( _BURNIN_EN)		
          if(GET_BURNIN_STATE()==BURNIN_ON)
          	{
             BurnInRun();
          	}			
#endif		 
	if(GET_FAC_STATE()==1)
		    COsdFacHandler();
#endif

#if(_VIDEO_TV_SUPPORT)
    if ((_GET_INPUT_SOURCE() == _SOURCE_VIDEO_TV || ucCurrState == _ACTIVE_STATE) &&GET_FAC_STATE()==0)
#else
    if ((ucCurrState == _ACTIVE_STATE) &&GET_FAC_STATE()==0)
#endif
    {          
        COsdProc();

        if (bRCallOSD)
        {
            bRCallOSD = 0;
            COsdProc();
        }

#if(_VIDEO_TV_SUPPORT)
        if (ucKeyMessage != _NONE_KEY_MESSAGE && ucOsdState != MENU_SHOW_MUTE_STATE && !bChangeChannel)
#else
        if (ucKeyMessage != _NONE_KEY_MESSAGE && ucOsdState != MENU_SHOW_MUTE_STATE)
#endif
        {
#if(_IR_ENABLE)        
            switch(ucKeyMessage)
            {
                case VK_IR_DISPLAY:
                case VK_IR_MUTE:
                case _IR_IMAGE_KEY_MESSAGE:
		  case VK_IR_SLEEP:
                    CTimerReactiveTimerEvent(SEC(5),COsdDispOsdTimerEvent);
                    return;

                default:
                    if(stOsdUserData.OsdTimeout > 4)
                    {
                        CTimerReactiveTimerEvent(SEC(stOsdUserData.OsdTimeout),COsdDispOsdTimerEvent);
                    }
                    else
                    {
                       CTimerCancelTimerEvent(COsdDispOsdTimerEvent);
                    }
            }
#endif
    }  
   if(GET_MUTE_STATE() == STATE_MUTEON &&ucOsdState==MENU_SHOW_MUTE_STATE)
    	{
    COsdFxEnableOsd();
    	}
    if (ucOsdState == 255)
       NotUseFunc();
}
#if(IR_Test_EN== _ON)    
        Display_IR(); 
#endif
}
//-----------------------------------------------------------

void CSourceChange(void)
{
#if(_CHANGE_SOURCE_METHOD == _CHANGE_SOURCE_METHOD_0)

    
    ChangeSource();

    if (!ucChangeSourceCount)
    {
        MUTE_ON();

        if (_SLEEP_STATE == ucCurrState)
            CPowerLVDSOn();
        
  #if(_VIDEO_TV_SUPPORT)
        ucVideoNoModeTime = 252;
  #endif        
        CModeResetMode();
    }
    
    ucChangeSourceCount = 1;
    ucOsdEventMsg       = _DO_SHOW_NOTE;
   	   SET_DO_SHOW_NOTE(0);
    ucCurrState         = _SOURCE_CHANGE_STATE;
    #if(_IR_ENABLE)
    ucDetectIR_Cmd = 0;
    #endif

#elif(_CHANGE_SOURCE_METHOD == _CHANGE_SOURCE_METHOD_1)

    if (_SLEEP_STATE == ucCurrState)
        CPowerLVDSOn();
        
    ChangeSource();
//    COsdDispFirstTimeLoadFont();

  #if(_VIDEO_TV_SUPPORT)
    ucVideoNoModeTime = 252;
  #endif        
    CModeResetMode();

    //SET_FIRST_SHOW_NOTE();
    ucOsdEventMsg  = _CHANGE_SOURCE_MSG;
    ucCurrState    = _SOURCE_CHANGE_STATE;
    #if(_IR_ENABLE)
    ucDetectIR_Cmd = 0;
    #endif

#endif  // #if(_CHANGE_SOURCE_METHOD == _CHANGE_SOURCE_METHOD_0)

}
//-----------------------------------------------------------

#if(_CHANGE_SOURCE_METHOD == _CHANGE_SOURCE_METHOD_0)

void CChangeSourceHandler(void)
{
    ucChangeSourceCount++;
#if(DVD_EN)
   if(_GET_INPUT_SOURCE() != _SOURCE_VIDEO_DVD)
   {
	   	bDVD_PWR_OFF();
		bDVDON = 1;
	}
#endif
                          
    if (_CHANGE_SOURCE_TIME < ucChangeSourceCount)
    {          
#if(_VIDEO_SUPPORT == _ON)
        if (bVideoON && 
            (_GET_INPUT_SOURCE() == _SOURCE_VGA || 
            _GET_INPUT_SOURCE() == _SOURCE_DVI  || 
            _GET_INPUT_SOURCE() == _SOURCE_HDMI || 
            _GET_INPUT_SOURCE() == _SOURCE_YPBPR))  // Prev source is video
        {
            gmi_CVDCOutputDisable();
            CPowerDownVDC();
            bVideoON = 0;
        } 
#endif   
 
        ucOsdEventMsg       = _CHANGE_SOURCE_MSG;
        ucChangeSourceCount = 0;
        CInitInputSource();
     //   COsdDispFirstTimeLoadFont();
    }
}      
#endif
//-----------------------------------------------------------

void COsdSystemFlowProc(void)
{
    switch(ucCurrState)
    {
    case _PWOFF_STATE:
        break;
        
    case _INITIAL_STATE:
        break;
        
    case _SEARCH_STATE:
        if(GET_FIRST_LOADFONT() == _TRUE)
        {
            CLR_FIRST_LOADFONT();
            COsdDispFirstTimeLoadFont();
        }
        break;
        
    case _ACTIVE_STATE:
        if(GET_OSD_READYFORDISPLAY() == _TRUE)
        {         
            CLR_OSD_READYFORDISPLAY();
/*
#if(_CHANGE_SOURCE_BACKGROUCD_COLOR==_BACK_COLOR)					    	
		CAdjustBackgroundColor(0x00, 0x00, 0x00);     
#else
		CAdjustBackgroundColor(0x00, 0x00, 0xFF);     
#endif
*/

	     MUTE_OFF();
#if(RunLED==RedLED)			
		CPowerLedRed(); 
#elif(RunLED==GreenLED)			
		CPowerLedGreen(); 
#elif(RunLED==OrangeLED)			
		CPowerLedOrange(); 
#elif(RunLED==BlackLED)			
		CPowerLedBlack(); 
#endif
            
            if (GET_FIRST_SHOW_NOTE())
            {
                ucOsdEventMsg = _DO_SHOW_NOTE;
                CLR_FIRST_SHOW_NOTE();
            }
#if(_VIDEO_TV_SUPPORT)
            else if (_GET_INPUT_SOURCE() == _SOURCE_VIDEO_TV && 0 == bChangeChannel)
                CShowTVNumber(stVDCColor.CurrentChannel,_SHOW_CH_TV_NUMBER | _SHOW_CH_TV_TYPE | _SHOW_CH_SOUND_TYPE);
#endif

#if(_VIDEO_CHIP == _VDC_TB1334)
            if (_GET_INPUT_SOURCE() != _SOURCE_VIDEO_TV)
#endif
            CSetVolume();
        }

#if(_VIDEO_CHIP == _VDC_TB1334)
        CAudioCtrl(); 
#endif
        break;
        
    case _NOSUPPORT_STATE:
		if(GET_NOSIGNAL_INFO()==1)
		return;
        if(GET_OSD_READYFORDISPLAY() == _TRUE)
        {
#if(NosignalStateLED==RedLED)			
		CPowerLedRed(); 
#elif(NosignalStateLED==GreenLED)			
		CPowerLedGreen(); 
#elif(NosignalStateLED==OrangeLED)			
		CPowerLedOrange(); 
#elif(NosignalStateLED==BlackLED)			
		CPowerLedBlack(); 
#endif
            CLR_OSD_READYFORDISPLAY();

#if(_CHANGE_SOURCE_BACKGROUCD_COLOR==_BACK_COLOR)					    	
		CAdjustBackgroundColor(0x00, 0x00, 0x00);     
#else
		CAdjustBackgroundColor(0x00, 0x00, 0xFF);     
#endif
		ucOsdEventMsg = _DO_SHOW_NOTE; 
            
            CTimerReactiveTimerEvent(SEC(1), CModeNoSupportEvent);
		#if(_AUTO_SLEEP_POWERDOWN == _ON)
			CTimerActiveTimerEvent(90000, CModePowerSavingEvent);
		#else
			CTimerActiveTimerEvent(SEC(6), CModePowerSavingEvent);
		#endif
        }
        
        break;
        
    case _NOSIGNAL_STATE:
		if(GET_NOSIGNAL_INFO()==1)
		return;
        if(GET_OSD_READYFORDISPLAY() == _TRUE)
        {
#if(NosignalStateLED==RedLED)			
		CPowerLedRed(); 
#elif(NosignalStateLED==GreenLED)			
		CPowerLedGreen(); 
#elif(NosignalStateLED==OrangeLED)			
		CPowerLedOrange(); 
#elif(NosignalStateLED==BlackLED)			
		CPowerLedBlack(); 
#endif
            CLR_OSD_READYFORDISPLAY();
            
#if(_AUTO_SCAN_SOURCE) 
            SET_SOURCE_AUTOCHANGE();
#endif
            
#if(_CHANGE_SOURCE_BACKGROUCD_COLOR==_BACK_COLOR)					    	
		CAdjustBackgroundColor(0x00, 0x00, 0x00);     
#else
		CAdjustBackgroundColor(0x00, 0x00, 0xFF);     
#endif
		ucOsdEventMsg	 = _DO_SHOW_NOTE;
            
#if(_HDMI_SUPPORT == _ON)
            if((bVGACONNECT && _SOURCE_VGA ==_GET_INPUT_SOURCE()) || (bHDMICONNECT && _SOURCE_HDMI ==_GET_INPUT_SOURCE()))
#elif(_TMDS_SUPPORT == _ON)
            if((bVGACONNECT && _SOURCE_VGA ==_GET_INPUT_SOURCE()) || (bDVICONNECT && _SOURCE_DVI ==_GET_INPUT_SOURCE()))
#else
            if((bVGACONNECT && _SOURCE_VGA ==_GET_INPUT_SOURCE()))
#endif
            {
                CTimerReactiveTimerEvent(SEC(1), CModeNoCableEvent);
            }
            else
            {
                CTimerReactiveTimerEvent(SEC(1), CModeNoSignalEvent);
             }    
//#if(!_BURNIN_EN)  
                CTimerActiveTimerEvent(SEC(6), CModePowerSavingEvent);
//#endif
           
            }
        
        break;
        
    case _SLEEP_STATE:
        break;
        
    default:
        break;
    }
}

//-----------------------------------------------------------

void COsdProc(void)
{               
#if(_VIDEO_TV_SUPPORT)           
    if (MENU_SHOW_MESSAGE_SATAE == ucOsdState)
    {
        if (_NONE_KEY_MESSAGE != ucKeyMessage)
            ucOsdState = _MENU_NONE;
        else
            return;
    }
#endif

    switch(ucOsdState)
    {
        case MENU_SHOW_MUTE_STATE:
        case MENU_SHOW_MSG_STATE:
        case _MENU_NONE:                    MPubNoneProc();           break;

        //==================== Main item ===========================
        case MENU_MAIN_COLOR:        // Public color item
#if(_VGA_SUPPORT || _YPBPR_SUPPORT)                   
        case MENU_MAIN_PICTURE:      // VGA picture item
#endif
#if(_VIDEO_TV_SUPPORT)           
        case MENU_MAIN_TV_FUNC:      // TV function item
#endif
        case MENU_MAIN_OSD_FUNC:     // Public OSD function item
        case MENU_MAIN_SOUND:        // Public Sound item
        case MENU_MAIN_OTHER:        // Public other item
        case MENU_MAIN_EXIT:         // Public exit item
            MMainItemProc();       
            break;
    


        //======================= Sub item =========================

        //---------------- Public Color Sub item -------------------
        case MENU_ITEM_BRIGHT:       // Public <Brightness>
        case MENU_ITEM_CONTRAST:     // Public <Contrast>
#if(_TMDS_SUPPORT || _VGA_SUPPORT || _HDMI_SUPPORT)
        case MENU_ITEM_COLOR_TEMP:   // VGA/DVI/HDMI <Color temp>
#endif

#if(_VIDEO_SUPPORT)
        case MENU_AV_SATURATION:     // Video <Saturation>
        case MENU_AV_HUE:            // Video <Hue>
#endif
        case MENU_SUB_COLOR_CLOSE:   // Public <Close> 
            MColorSubItemProc();
            break;

        //------------------ TV function sub item -------------------
#if(_VIDEO_TV_SUPPORT)
        case MENU_AUTO_SEARCH:       // TV <Auto search>
        case MENU_MANUAL_SEARCH:     // TV <Manual search> 
        case MENU_TUNING:            // TV <Tunning>
        case MENU_CHANNEL:           // TV <Channel>
        case MENU_TV_SYSTEM:         // TV <TV system>
        case MENU_SWAP:              // TV <Swap>
        case MENU_SKIP:              // TV <Skip>
        case MENU_SUB_TV_FUNC_CLOSE: // TV <Close>
            MTVFuncSubItemProc();
            break;
#endif
    
        //------------- VGA/DVI/HDMI Color sub temp sub item -------------
#if(_TMDS_SUPPORT || _VGA_SUPPORT || _HDMI_SUPPORT)           
#if(_COLOR_TEMP)
        case MENU_SUB_CT_9300:       // VGA/DVI/HDMI <9300>
        case MENU_SUB_CT_6500:       // VGA/DVI/HDMI <6500>
        case MENU_SUB_CT_5800:       // VGA/DVI/HDMI <5800>
        case MENU_SUB_CT_SRGB:       // VGA/DVI/HDMI <SRGB>
        case MENU_SUB_CT_USER:       // VGA/DVI/HDMI <User>
        case MENU_SUB_CT_CLOSE:      // VGA/DVI/HDMI <close>
            MColorTempSubItemProc();
            break;

        case MENU_SUB_CT_R:          // VGA/DVI/HDMI <R>
        case MENU_SUB_CT_G:          // VGA/DVI/HDMI <G>
        case MENU_SUB_CT_B:          // VGA/DVI/HDMI <B>
            MColorTempUserItemProc();
            break;
#endif
#endif
    
       //------------------- VGA pciture sub item -------------------
#if(_VGA_SUPPORT  || _YPBPR_SUPPORT)
        case MENU_ITEM_AUTO:         // VGA <Auto>
#if(_VGA_SUPPORT)
        case MENU_ITEM_AUTO_COLOR:
        case MENU_ITEM_HPOS:         // VGA <H position>
        case MENU_ITEM_VPOS:         // VGA <V position>
        case MENU_ITEM_PHASE:        // VGA <Phase>
        case MENU_ITEM_CLOCK:        // VGA <Clock>
#endif
        case MENU_SUB_PICTURE_CLOSE: // VGA <Close>
            MPictureSubItemProc();
            break;
#endif
    
        //------------- Public OSD function sub item ----------------
        case MENU_SUB_LANGUAGE:        // Public <Language>
        case MENU_SUB_H_POSITION:      // Public <OSD H position>
        case MENU_SUB_V_POSITION:      // Public <OSD V position>
        case MENU_SUB_OSD_TIMEOUT:     // Public <OSD timeout>
        case MENU_SUB_OSD_TRANSLUCENT: // Public <OSD Translucent>
        case MENU_SUB_OSD_SIZE:        // public <OSD Size>
	 case MENU_SUB_DISMODE:			// 16:9-4:3 display
        case MENU_SUB_OSD_CLOSE:       // Public <Close>
            MOSDSubItemProc();
            break;

        //---------------- Public Sound sub item ---------------------
        case MENU_SUB_VOLUME:        // Public <Volume>
        case MENU_SUB_MUTE:          // Public <Mute>
#if(_SOUND_PROCESSOR == _ENABLE)
        case MENU_SUB_BALANCE:       // Public <Balance>
        case MENU_SUB_BASS:          // Public <Bass>
        case MENU_SUB_TREBLE:        // Public <Treble>
        case MENU_SUB_SRS:           // Public <SRS>
        case MENU_SUB_BBE:           // Public <BBE>
#endif  
        case MENU_SUB_SOUND_CLOSE:   // Public <Close>
            MSoundSubItemProc();
            break;

        //------------------ Public Other sub item --------------------
        case MENU_SUB_RESET:         // Public <Reset>
        case MENU_SUB_BLUE:          // Public <Blue>
#if(_AUTO_POWER_DOWN)
        case MENU_SUB_AUTO_POWER:    // Public <Auto power down>
#endif
        case MENU_SUB_COLOR_MODE:    // Public <Color Mode>
        case MENU_SUB_SHARP:         // Public <Sharp>
        case MENU_SUB_OTHER_CLOSE:   // Public <Close>
            MOtherSubItemProc();
            break;
    

        //======================= Sub item adjust proc =====================

        //------------------- Public Color adj proc ----------------------
        case MENU_SUB_BRIGH_ADJ:     // Public <Brightness> adj     
            MBrightAdjProc();            
            break;
        case MENU_SUB_CONTRAST_ADJ:  // Public <Contrast> adj     
            MContrastAdjProc();          
            break;
#if(_VIDEO_SUPPORT)
        case MENU_AV_SATURATION_ADJ: // Video <Saturation> adj   
            MAVSaturationAdjProc();      
            break;
        case MENU_AV_HUE_ADJ:        // Video <Hue> adj      
            MAVHueAdjProc();             
            break;
#endif


        //----------------------- VGA Picture adj proc -------------------
#if(_VGA_SUPPORT)
        case MENU_SUB_PHASE_ADJ:     // VGA <Phase> adj     
            MPhaseAdjProc();        
            break;
        case MENU_SUB_CLOCK_ADJ:     // VGA <Clock> adj    
            MClockAdjProc();        
            break;
        case MENU_SUB_HPOS_ADJ:      // VGA <H position> adj    
            MHPosAdjProc();         
            break;
        case MENU_SUB_VPOS_ADJ:      // VGA <V position> adj    
            MVPosAdjProc();         
            break;
#endif

        //---------------------- TV function adj proc --------------------
#if(_VIDEO_TV_SUPPORT)
        case MENU_AUTO_SEARCH_ADJ:   // TV <Auto search> adj     
            MAutoSearchAdjProc();        
            break;
        case MENU_MANUAL_SEARCH_ADJ: // TV <Manual search> adj    
            MManualSearchAdjProc();      
            break;
        case MENU_TUNING_ADJ:        // TV <Tunning> adj    
            MTuningAdjProc();            
            break;
        case MENU_TV_SYSTEM_ADJ:     // TV <TV system> adj    
            MTVSystemAdjProc();          
            break;
 //       case MENU_SOUND_SYSTEM_ADJ:  // TV <Sound system> adj <Not use>     
   //         MSoundSystemAdjProc();       
     //       break;
        case MENU_CHANNEL_ADJ:       // TV <Channel> adj    
   #if(_KEY_TYPE_OSD007== _5KEY_SUPPORT)//0228 guo
   	 case MENU_CHANEL_SP:
   #endif
            MChannelAdjProc();           
            break;
        case MENU_SWAP_ADJ:          // TV <Swap> adj      
            MSwapAdjProc();               
            break;
        case MENU_SKIP_ADJ:          // TV <Skip> adj    
            MSkipAdjProc();              
            break;
#endif

        //----------------------- Public OSD adj proc ---------------------
        case MENU_SUB_OSDLANGUAGE_ADJ:   // Public <Language> adj 
            MLanguageAdjProc();     
            break;
#if(_OSD_POSITION_ADJ_CTRL)
        case MENU_SUB_OSDH_POSITION_ADJ: // Public <OSD H position> adj
            MOSDHPositionAdjProc(); 
            break;
        case MENU_SUB_OSDV_POSITION_ADJ: // Public <OSD V position> adj
            MOSDVPositionAdjProc(); 
            break;
#endif
#if(_OSD_TIMEOUT_ADJ_CTRL)
        case MENU_SUB_OSD_TIMEOUT_ADJ:   // Public <OSD timeout> adj
            MOSDTimeoutAdjProc();   
            break;
#endif
#if(_ALPHA_BLENDING_ADJ)
        case MENU_SUB_OSD_TRANS_ADJ:    // Public <OSD Translucent> adj
            MOSDTranslucentAdjProc();   
            break;
#endif
#if(_OSD_DISPLAY_SIZE_ADJ)
if(Panel.DHWidth>1024||Panel.DVHeight>768)
     	{
        case MENU_SUB_OSD_SIZE_ADJ:    // Public <OSD Size> adj
            MOSDSizeAdjProc();   
            break;
     	}
#endif

        #if(_DISPLAY_SIZE_ADJ)
         if(Panel.DHWidth > (Panel.DVHeight * 4/3)) 
         	{
 	          case MENU_SUB_DISPMODE_ADJ:    // Public <OSD Size> adj
                  MDispModeAdjProc();   
                  break;
         	}
        #endif
        //---------------------- Public Ohter adj proc --------------------
#if(_BLUE_BACKGROUND_FUNC == _ENABLE)
        case MENU_BLUE_ADJ:              // Public <Blue> adj 
            MBlueAdjProc();              
            break;
#endif

#if(_AUTO_POWER_DOWN)
        case MENU_AUTO_POWER_DOWN_ADJ:   // Public <Auto power down> adj
            MAutoPowerDownAdjProc();     
            break;
#endif

#if(_IMAGE_COLOR_MODE)
        case MENU_COLOR_MODE_ADJ:        // Public <Color mode> adj
            MColorModeAdjProc();
            break;
#endif

#if(_SHARPNESS_ADJ)
        case MENU_SHARP_ADJ:             // Public <Sharp> adj
            MSharpAdjProc();
            break;
#endif

        //--------------------- Public Sound adj porc ---------------------
        case MENU_SUB_VOL_ADJ:           // Public <Volume> adj
        case MENU_VOLUME_SP:
            MVolumeAdjProc();            
            break;
        case MENU_SUB_MUTE_ADJ:          // Public <Mute> adj
            MMuteAdjProc();              
            break;
#if(_SOUND_PROCESSOR == _ENABLE)
        case MENU_SUB_BALANCE_ADJ:       // Public <Balance> adj
            MBalanceAdjProc();           
            break;
        case MENU_SUB_BASS_ADJ:          // Public <Bass> adj
            MBassAdjProc();              
            break;
        case MENU_SUB_TREBLE_ADJ:        // Public <Treble> adj
            MTrebleAdjProc();            
            break;
        case MENU_SUB_SRS_ADJ:           // Public <SRS> adj
            MSRSAdjProc();               
            break;
        case MENU_SUB_BBE_ADJ:           // Public <BBE> adj
            MBBEAdjProc();               
            break;
#endif

        //------------------ TV Input ch number adj proc -----------------
#if(_VIDEO_TV_SUPPORT)
   #if(_IR_ENABLE)        
        case ITEM_SHORTCUT_INPUTCH_NUM:  
#if(_INPUT_NUMBER_MODE==DirectnessInputNumber)
	SDirectnessInputCHNumber();
#endif	

#if(_INPUT_NUMBER_MODE==IndirectInputNumber)			
			SInputCHNumber();    
#endif        
                   break;
   #endif        
#endif


        //======================== Peaking coring function =====================
#if(_VGA_COLOR_SUPPORT)
        //---------------------- Vivid color item ------------------------
        case MENU_SAC_DCC_TEXT:               // DCC <Text>
        case MENU_SAC_DCC_MOVIE:              // DCC <Movie>
        case MENU_SAC_DCC_GRAPHIC:            // DCC <Graphic>
        case MENU_SAC_DCC_GAME:               // DCC <Game>
        case MENU_SAC_DCC_NORMAL:             // DCC <Normal>
        case MENU_SAC_DCC_USER:               // DCC <User>
        case MENU_SAC_DCC_CLOSE:              // DCC <Exit>
            MVividColorItemProc();
            break;
    
        //---------------------- Vivid color sub item --------------------
        case MENU_USER_ITEM_DCC:              // Vivid Color <DCC>
        case MENU_USER_ITEM_ICM:              // Vivid Color <ICM>
        case MENU_USER_ITEM_COLOR:            // Vivid Color <Color>
        case MENU_USER_ITEM_CLOSE:            // Vivid Color <Exit>
            MVividColorSubProc();
            break;
       
        //--------------------- Vivid color DCC adj ---------------------
        case MENU_DCC_ITEM_TEXT:              // DCC <Text>
        case MENU_DCC_ITEM_MOVIE:             // DCC <Movie>
        case MENU_DCC_ITEM_GRAPHIC:           // DCC <Graphic>
        case MENU_DCC_ITEM_GAME:              // DCC <Game>
        case MENU_DCC_ITEM_NORMAL:            // DCC <Normal>
            MDCCAdjProc();
            break;
    
        //--------------------------- ICM item ---------------------------
        case MENU_ICM_ITEM_RED:               // ICM <Red>
        case MENU_ICM_ITEM_GREEN:             // ICM <Green>
        case MENU_ICM_ITEM_BLUE:              // ICM <Blue>
        case MENU_ICM_ITEM_YELLOW:            // ICM <Yellow>
        case MENU_ICM_ITEM_CYAN:              // ICM <Cyan>
        case MENU_ICM_ITEM_MAGENTA:           // ICM <Magenta>
        case MENU_ICM_ITEM_ON_OFF:            // ICM <ICM>
        case MENU_ICM_ITEM_CLOSE:             // ICM <Exit>
            MICMItemProc();
            break;
    
        //------------------------ ICM R/G/B item ------------------------
        case MENU_ICM_SUB_R_HUE:              // ICM R <Hue>
        case MENU_ICM_SUB_R_SAT:              // ICM R <Saturation>
        case MENU_ICM_SUB_R_CLOSE:            // ICM R <Close>
        case MENU_ICM_SUB_G_HUE:              // ICM G <Hue>
        case MENU_ICM_SUB_G_SAT:              // ICM G <Saturation>
        case MENU_ICM_SUB_G_CLOSE:            // ICM G <Close>
        case MENU_ICM_SUB_B_HUE:              // ICM B <Hue>
        case MENU_ICM_SUB_B_SAT:              // ICM B <Saturation>
        case MENU_ICM_SUB_B_CLOSE:            // ICM B <Close>
        case MENU_ICM_SUB_Y_HUE:              // ICM Y <Hue>
        case MENU_ICM_SUB_Y_SAT:              // ICM Y <Saturation>
        case MENU_ICM_SUB_Y_CLOSE:            // ICM Y <Close>
        case MENU_ICM_SUB_C_HUE:              // ICM C <Hue>
        case MENU_ICM_SUB_C_SAT:              // ICM C <Saturation>
        case MENU_ICM_SUB_C_CLOSE:            // ICM C <Close>
        case MENU_ICM_SUB_M_HUE:              // ICM M <Hue>
        case MENU_ICM_SUB_M_SAT:              // ICM M <Saturation>
        case MENU_ICM_SUB_M_CLOSE:            // ICM M <Close>
            MICMSubRGBItemAdjProc();
            break;
    
        //-------------------- ICM R/G/B color adj page --------------------
        case MENU_ICM_R_HUE_ADJ:              // ICM R adj <Hue>
        case MENU_ICM_R_SAT_ADJ:              // ICM R adj <Saturation>
        case MENU_ICM_G_HUE_ADJ:              // ICM G adj <Hue>
        case MENU_ICM_G_SAT_ADJ:              // ICM G adj <Saturation>
        case MENU_ICM_B_HUE_ADJ:              // ICM B adj <Hue>
        case MENU_ICM_B_SAT_ADJ:              // ICM B adj <Saturation>
        case MENU_ICM_Y_HUE_ADJ:              // ICM Y adj <Hue>
        case MENU_ICM_Y_SAT_ADJ:              // ICM Y adj <Saturation>
        case MENU_ICM_C_HUE_ADJ:              // ICM C adj <Hue>
        case MENU_ICM_C_SAT_ADJ:              // ICM C adj <Saturation>
        case MENU_ICM_M_HUE_ADJ:              // ICM M adj <Hue>
        case MENU_ICM_M_SAT_ADJ:              // ICM M adj <Saturation>
            MICMSubRGBColorAdjProc();
            break;
       
        //-------------------------- Vivid color ---------------------------
        case MENU_COLOR_ITEM_BRIGHTNESS:      // Color <Brightness>
        case MENU_COLOR_ITEM_CONTRAST:        // Color <Contrast>
        case MENU_COLOR_ITEM_PEAKING:         // Color <Peaking>
        case MENU_COLOR_ITEM_CLOSE:           // Color <Exit>
            MDCCColorAdjProc();
            break;
    
        //------------------ Vivid bright/Contrast adj proc ----------------
        case MENU_COLOR_ITEM_BRIGHT_ADJ:      // Color adj <Brightness>
        case MENU_COLOR_ITEM_CON_ADJ:         // Color adj <Contrast>
        case MENU_COLOR_ITEM_PEAK_ADJ:        // Color adj <Peaking>
            MDCCColorBCAdjProc();
            break;
#endif
    
#if(_IMAGE_COLOR_MODE)//0228 guo
        case MENU_IMAGE_ADJ:
            MImageAdj();
            break;
#endif
#if(_AUTO_POWER_DOWN)
        case SLEEP_TIME_ADJ:
            MSleepTimeAdj();
            break;
#endif
        default:                              break;
            
    }    



}

//-----------------------------------------------------------
void MPubNoneProc(void)
{
    switch(_GET_INPUT_SOURCE())
    {
#if(_TMDS_SUPPORT || _VGA_SUPPORT || _YPBPR_SUPPORT || _HDMI_SUPPORT)
    case _SOURCE_YPBPR:
    case _SOURCE_VGA:
    case _SOURCE_DVI:
    case _SOURCE_HDMI:
        MNoneProc();
        break;
#endif    
        
#if(_VIDEO_SUPPORT)
#if(_VIDEO_YUV_SUPPORT)
    case _SOURCE_VIDEO_YUV:
#endif
#if(DVD_EN)
    case _SOURCE_VIDEO_DVD:
#endif
    case _SOURCE_VIDEO_AV:
    case _SOURCE_VIDEO_SV:
    case _SOURCE_VIDEO_SCART:
        MAVNoneProc();
        break;
#endif    
       
#if(_VIDEO_TV_SUPPORT)
    case _SOURCE_VIDEO_TV:
        MTVNoneProc();
        break;
#endif
    }
         
    if (_MENU_NONE == ucOsdState && _NONE_MSG == ucOsdEventMsg)// && GET_MUTE_STATE() == STATE_MUTEON && ucOsdState != MENU_SHOW_MUTE_STATE)
    {
#if(_IR_ENABLE)        
  #if(_VIDEO_TV_SUPPORT)
        if (GET_MUTE_STATE() == STATE_MUTEON && ucOsdState != MENU_SHOW_MUTE_STATE && !bChangeChannel)
  #else
        if (GET_MUTE_STATE() == STATE_MUTEON && ucOsdState != MENU_SHOW_MUTE_STATE)
  #endif
           DrawMuteState();
#else
        if (0)
        {
        }
#endif // end #if(_IR_ENABLE)
#if(_AUTO_POWER_DOWN)
        else if(0xff != ucAutoPowerDownTime && 0 != _GET_POWER_DOWN_TIME())
           CShowTimer(); // Show auto power down timer
#endif

#if(_LOGO_EN && _LOGO_TYPE == _LOGO_TYPE1)
        else if (ucCurrState == _ACTIVE_STATE)
        {
            CLogoGo(); 
        }
#endif
    } 
}


//-----------------------------------------------------------
void COthterKeyAction(void)
{
    if (_NONE_KEY_MESSAGE != ucKeyMessage)
    {
        switch(ucKeyMessage)
        {
#if(_IR_ENABLE)        
  #if(_USE_UD_LR_KEY_MSG)
            case VK_F_LEFT:
            case VK_F_RIGHT:
            case VK_F_UP:
            case VK_F_DOWN:
  #endif
            case VK_MENU:
            case _IR_MENU_KEY_MESSAGE:
            case VK_IR_DISPLAY:
            case VK_IR_MUTE:
            case VK_IR_VOLDEC:
            case VK_IR_VOLINC:
#if(_AUTO_POWER_DOWN)
		case VK_IR_SLEEP:
#endif              
                break;
//0228 guo
            case _IR_IMAGE_KEY_MESSAGE:
                if (_GET_INPUT_SOURCE() == _SOURCE_VGA)
                   return;
                else
                   break;
            case VK_IR_CHINC:
            case VK_IR_CHDEC:
            case VK_IR_NUM0:
            case VK_IR_NUM1:
            case VK_IR_NUM2:
            case VK_IR_NUM3:
            case VK_IR_NUM4:
            case VK_IR_NUM5:
            case VK_IR_NUM6:
            case VK_IR_NUM7:
            case VK_IR_NUM8:
            case VK_IR_NUM9:
#if(_INPUT_NUMBER_MODE!=DirectnessInputNumber)				
            case VK_IR_INPUTCH:
#endif				
            case VK_IR_RETURN:
                if (_SOURCE_VIDEO_TV != _GET_INPUT_SOURCE())  // TV key
                    return;
    
                break;
#endif
            default:
                return;
        }

        CLR_KEYREPEATENABLE();
        ucOsdState = _MENU_NONE;
        bRCallOSD  = 1;
       // COsdProc();
    }
}

//------------------------------------------------------------
void MPublicNoneMenu(void)
{           
    InitOSDFrame();
    CDrawColorPage();
    ucOsdState = MENU_MAIN_COLOR;
    CShowSelectMainItemWindow(_FIRST_ITEM);

    COsdFxEnableOsd();
}

//------------------------------------------------------------
void MMainItemProc(void)
{
    switch(ucKeyMessage)
    {
        //  Select item
#if(_USE_UD_LR_KEY_MSG)
        case VK_F_UP:
        case VK_F_DOWN:
#endif
#if(_KEY_TYPE_OSD007!=_7KEY_SUPPORT)
        case VK_MENU:       
#endif
        case VK_IR_OK:       
			MMainItemMenu();       break;

        // Move item
#if(_USE_UD_LR_KEY_MSG)
        case VK_F_LEFT:
#endif
        case VK_LEFT:        MMainItemLR(1);        break;
        // Move item
#if(_USE_UD_LR_KEY_MSG)
        case VK_F_RIGHT:
#endif
        case VK_RIGHT:       MMainItemLR(0);        break;

        // Exit item
#if(_MENU_FUNC == _MENU_EXIT_ITEM)
        case VK_ENTER:   
#endif
#if(_KEY_TYPE_OSD007==_7KEY_SUPPORT)
        case VK_MENU:       
#endif
        case VK_AUTO:
        case VK_IR_EXIT:
    COsdFxDisableOsd();    break;
        // Default
        default:             COthterKeyAction();    break;
    }
}

//------------------------------------------------------------
void MMainItemMenu(void)
{       
    // Enter Sub Item
    switch(ucOsdState)
    {
        case MENU_MAIN_COLOR: 
            ucOsdState = MENU_ITEM_BRIGHT;      
            break;

#if(_VGA_SUPPORT || _YPBPR_SUPPORT)
        case MENU_MAIN_PICTURE:
            ucOsdState= MENU_ITEM_AUTO;      
            break;
#endif
            
#if(_VIDEO_TV_SUPPORT)
        case MENU_MAIN_TV_FUNC:
            ucOsdState= MENU_AUTO_SEARCH;      
            break;
#endif
            
        case MENU_MAIN_OSD_FUNC:
            ucOsdState= MENU_SUB_LANGUAGE;      
            break;

        case MENU_MAIN_SOUND:
            ucOsdState= MENU_SUB_VOLUME;      
            break;

        case MENU_MAIN_OTHER:
            ucOsdState= MENU_SUB_RESET;      
            break;

        case MENU_MAIN_EXIT:
            COsdFxDisableOsd();
//			ucOsdState = MENU_SUB_EXIT_CLOSE;
            break;

    }

    CSetItemWindowState(_SELECT_MAIN_WINDOW, _SELECT_STATE);
    CShowSubItemWindow(_FIRST_ITEM);
}

//------------------------------------------------------------
void MMainItemLR(BYTE  LR)
{  
    BYTE ucTemp = 0;

    CClearSubItem();

    if(LR)
    {     
        switch(ucOsdState)
        {
            case MENU_MAIN_COLOR:
                switch(_GET_INPUT_SOURCE())
                {
#if(_VGA_SUPPORT || _YPBPR_SUPPORT)
                    case _SOURCE_VGA:
                    case _SOURCE_YPBPR:
                        ucOsdState = MENU_MAIN_PICTURE;      
                        break;
#endif

                    case _SOURCE_DVI:
                    case _SOURCE_HDMI:
                    case _SOURCE_VIDEO_AV:
                    case _SOURCE_VIDEO_SV:
                   #if(DVD_EN)
                       case _SOURCE_VIDEO_DVD:
                   #endif
                    case _SOURCE_VIDEO_SCART:
                        ucOsdState = MENU_MAIN_OSD_FUNC;      
                        break;

#if(_VIDEO_TV_SUPPORT)
                    case _SOURCE_VIDEO_TV:
                        ucOsdState = MENU_MAIN_TV_FUNC;      
                        break;
#endif
                }
                break;

            case MENU_MAIN_PICTURE:        
            case MENU_MAIN_TV_FUNC:        ucOsdState = MENU_MAIN_OSD_FUNC;     break;
            case MENU_MAIN_OSD_FUNC:       ucOsdState = MENU_MAIN_SOUND;        break;
            case MENU_MAIN_SOUND:          ucOsdState = MENU_MAIN_OTHER;        break;
            case MENU_MAIN_OTHER:          ucOsdState = MENU_MAIN_EXIT;         break;
            case MENU_MAIN_EXIT:           ucOsdState = MENU_MAIN_COLOR;        break;
        }  
    }
    else
    {
        switch(ucOsdState)
        {
            case MENU_MAIN_COLOR:          ucOsdState = MENU_MAIN_EXIT;         break;
            case MENU_MAIN_PICTURE:
            case MENU_MAIN_TV_FUNC:        ucOsdState = MENU_MAIN_COLOR;        break;
            case MENU_MAIN_OSD_FUNC:       
                switch(_GET_INPUT_SOURCE())
                {
#if(_VGA_SUPPORT || _YPBPR_SUPPORT || _HDMI_SUPPORT)
                    case _SOURCE_VGA:
                    case _SOURCE_YPBPR:
                        ucOsdState = MENU_MAIN_PICTURE;      
                        break;
#endif

                    case _SOURCE_DVI:
                    case _SOURCE_HDMI:
                    case _SOURCE_VIDEO_AV:
                    case _SOURCE_VIDEO_SV:
                  //  case _SOURCE_VIDEO_YUV:
                      #if(DVD_EN)
                           case _SOURCE_VIDEO_DVD:
                      #endif
                    case _SOURCE_VIDEO_SCART:
                        ucOsdState = MENU_MAIN_COLOR;      
                        break;

#if(_VIDEO_TV_SUPPORT)
                    case _SOURCE_VIDEO_TV:
                        ucOsdState = MENU_MAIN_TV_FUNC;      
                        break;
#endif
                }
                break;            

            case MENU_MAIN_SOUND:          ucOsdState = MENU_MAIN_OSD_FUNC;     break;
            case MENU_MAIN_OTHER:          ucOsdState = MENU_MAIN_SOUND;        break;
            case MENU_MAIN_EXIT:           ucOsdState = MENU_MAIN_OTHER;        break;
        }
    }
    
    if (_GET_INPUT_SOURCE() == _SOURCE_VIDEO_AV       || _GET_INPUT_SOURCE() == _SOURCE_VIDEO_SV
          || _GET_INPUT_SOURCE() == _SOURCE_VIDEO_YUV || _GET_INPUT_SOURCE() == _SOURCE_DVI
          || _GET_INPUT_SOURCE() == _SOURCE_HDMI      || _GET_INPUT_SOURCE() == _SOURCE_VIDEO_SCART)  // eric 0718
        ucTemp = 1; 
    else
        ucTemp = 0;

    switch(ucOsdState)
    {
        case MENU_MAIN_COLOR:
            CDrawColorPage();
            ucTemp = 0;
            break;

#if(_VGA_SUPPORT || _YPBPR_SUPPORT)
        case MENU_MAIN_PICTURE:
            CDrawPicturePage();
            ucTemp = 1;
            break;
#endif

#if(_VIDEO_TV_SUPPORT)
        case MENU_MAIN_TV_FUNC:
            CDrawTVFunction();
            ucTemp = 1;
            break;
#endif

        case MENU_MAIN_OSD_FUNC:
            CDrawOSDFuncPage();

            if (ucTemp)
               ucTemp = 1;
            else
               ucTemp = 2;
            break;

        case MENU_MAIN_SOUND:
            CDrawSoundPage();
            if (ucTemp)
               ucTemp = 2;
            else
               ucTemp = 3;
            break;

        case MENU_MAIN_OTHER:
            CDrawOtherFuncPage();
            if (ucTemp)
               ucTemp = 3;
            else
               ucTemp = 4;
            break;

        case MENU_MAIN_EXIT:
            CDrawExitPage();
            if (ucTemp)
               ucTemp = 4;
            else
               ucTemp = 5;
            break;
    }   
    
    CShowSelectMainItemWindow(ucTemp);
}

//-----------------------------------------------------------
void COsdDispFirstTimeLoadFont(void)
{    
    //Before First Time Load Font Disable OSD
    COsdFxDisableOsd();
    
    //Load Public Fonts
    SetOSDRamAddress(ROW_COUNT,COL_WIDTH,FONT_BASE_ADDRESS);
    
#if(_HARDWARE_LOAD_FONT == _ON)

    CScalerLoadHardwareVLCFont(tFntGlobal, 0x00);
    
    // Load 4 bit icon
    CScalerLoadHardwareVLCFont(tFntIcon4Bit, (_4BIT_ICON_COLOR_ADDR*4));  // icon
    if (_SOURCE_VIDEO_TV == _GET_INPUT_SOURCE())
        CScalerLoadHardwareVLCFont(tFntIcon4BitTvFunc, (_4BIT_ICON_TV_FUNC_ADDR*4));  // TV function icon

#else

    CScalerLoadFont(tFntGlobal,0x00,0x7B,_COMPRESS_FONT);
    
    // Load 4 bit icon
    CScalerLoadFont(tFntIcon4Bit, (_4BIT_ICON_COLOR_ADDR*4), (6*_4BIT_ICON_SIZE*4), _COMPRESS_FONT);  // icon
    if (_SOURCE_VIDEO_TV == _GET_INPUT_SOURCE())
        CScalerLoadFont(tFntIcon4BitTvFunc, (_4BIT_ICON_TV_FUNC_ADDR*4), (_4BIT_ICON_SIZE*4), _COMPRESS_FONT);  // TV function icon

#endif

    //Load Languege Font
    LoadLanguageFont();
}
//-----------------------------------------------------------
void LoadLanguageFont()
{   
    switch(GET_LANGUAGE)
    {
    case LNG_CHI_S:
#if(LNG_CHI_S_EN == 1)
#if(_HARDWARE_LOAD_FONT == _ON)

        CScalerLoadHardwareVLCFont(tFntChiPublic, 0x7B);
        CScalerLoadHardwareVLCFont(tFntChi_S, 0xA8);

#else

        CScalerLoadFont(tFntChiPublic, 0x7B, 45, _COMPRESS_FONT);
        CScalerLoadFont(tFntChi_S, 0xA8, 45, _COMPRESS_FONT);

#endif
#endif
        break;

#if(LNG_ARABIC_EN)
     case LNG_ARABIC:
        CScalerLoadFont(tFntARABIC, 0x7B, 60, _COMPRESS_FONT);
        break;
#endif

    case LNG_CHI_T:
#if(LNG_CHI_T_EN == 1)
#if(_HARDWARE_LOAD_FONT == _ON)

        CScalerLoadHardwareVLCFont(tFntChiPublic, 0x7B);
        CScalerLoadHardwareVLCFont(tFntChi_T, 0xa8);

#else

        CScalerLoadFont(tFntChiPublic, 0x7B, 45, _COMPRESS_FONT);
        CScalerLoadFont(tFntChi_T, 0xa8, 45, _COMPRESS_FONT);

#endif
#endif
        break;
#if(LNG_RUSS_EN)
 	case LNG_RUSS:
		CScalerLoadFont(tFntRuss, 0x7B, 64, _COMPRESS_FONT);
		break;
#endif
		
#if(LNG_KOREAN_EN )
 	case LNG_KOREAN:
		CScalerLoadFont(tFntKorean, 0x80,82, _COMPRESS_FONT);
		break;
#endif		

    }  
}
//-----------------------------------------------------------
void COsdDispOsdTimerEvent(void)
{
    COsdFxDisableOsd();
}

//-----------------------------------------------------------
void COsdEventMsgProc(void)
{
    switch(ucOsdEventMsg)
    {
    case _SHOW_NOSIGNAL_MSG:
    case _SHOW_NOCABLE_MSG:
    case _SHOW_NOSUPPORT_MSG:
       ucOsdState = 0;
#if(_BURNIN_EN)
         if(GET_BURNIN_STATE()==BURNIN_ON)
         	{
	  	   CTimerCancelTimerEvent(CModePowerSavingEvent);				
	          InitBurnIn();
         	}
		 else
#endif    
         if(GET_BURNIN_STATE()!=BURNIN_ON)
	{
        MUTE_ON();
        HintDialog();
	}        break;
        
    case _SAVE_EE_MODEUSERDATA_MSG:
        CEepromSaveModeData(stModeInfo.ModeCurr);
        break;
        
    case _SAVE_EE_SYSTEMDATA_MSG:
        CEepromSaveSystemData();
        break;
        
    case _SAVE_EE_OSDUSERDATA_MSG:
        CEepromSaveOsdUserData();
        break;
        
    case _SAVE_EE_ADCDATA_MSG:
        CEepromSaveAdcData();
        break;
        
    case _SAVE_EE_BriConHueSat_MSG:
        CEepromSaveBriConData();
        break;
        
    case _SAVE_EE_COLORPROC1_MSG:
        CEepromSaveColorTempData();
        break;
#if(_VIDEO_SUPPORT)
    case _SAVE_EE_VEDIOCOLOR_MSG:
        CEepromSaveVedioColor();
        break;
#endif
    case _ENTER_FACTORY_MODE_MSG:
        //stOsdUserData.OsdSettingFlag |= _BIT7;
        break;
        
    case _CHANGE_SOURCE_MSG:
            CModeResetMode();
        	CLR_SOURCE_AUTOCHANGE();
        	CEepromSaveSystemData();
              ShowNote();
           // CPowerLightPowerOn();
          // SET_FIRST_SHOW_NOTE();
        ucCurrState = _SEARCH_STATE;
        break;
        
    case _DO_AUTO_CONFIG:
#if(_VGA_SUPPORT)
              DoAuto();
#endif
        break;   
        
    case _DO_SHOW_NOTE:
        ShowNote();
        break;
		
    case _BurnInRun_Out:
			CScalerSetBit(_VDISP_CTRL_28, ~_BIT5,0x00 );
		          if (_NOSIGNAL_STATE == ucCurrState||_NOSUPPORT_STATE == ucCurrState) 
		          	{
				CScalerSetBit(_VDISP_CTRL_28, ~_BIT5,_BIT5 );
                CAdjustBackgroundColor(0x00, 0x00, (_GET_INPUT_SOURCE() == _SOURCE_VIDEO_TV) ? ((_GET_BLUE_BACKGROUND()) ? 0xFF: 0x00) : 0x00);
		          	}
                   if(GET_FAC_STATE()==0)
                    CEepromSaveOsdUserData();
		
        break;
		
#if(_INPUT_NUMBER_MODE==DirectnessInputNumber )		
    case _CHANGE_NUMBER_MSG:
	 if(ucPrevChannel !=  stVDCColor.CurrentChannel)
 		{
       MUTE_ON();
        ucOsdState = _MENU_NONE;
        CModeResetTVMode();
        CTimerDelayXms(200);
		if(stVDCColor.CurrentChannel>CloadMaxChannelNumber(0))
	          	stVDCColor.CurrentChannel =CloadMaxChannelNumber(0);
		else
		if(stVDCColor.CurrentChannel<CloadMinChannelNumber())
	          	stVDCColor.CurrentChannel =CloadMinChannelNumber();
        CSetTVChannel(stVDCColor.CurrentChannel);
        SET_OSD_READYFORDISPLAY();
        gmi_CI2CWrite9886(ucTVType, _TUNER_MUTE_OFF, _NORMAL_MODE);
        bChangeChannel = 0;
        CEepromSaveVedioColor();
	 	}
	 else
       CShowTVNumber(stVDCColor.CurrentChannel, _SHOW_CH_TV_NUMBER | _SHOW_CH_TV_TYPE | _SHOW_CH_SOUND_TYPE);  //eric1221 mark
       break;
#endif

    case _FAC_FOR_IN: 
		  EnterFactoryMenu();
		  SET_NOSIGNAL_INFO(1);
        break;
      
    default:
        break;
    }
    
    ucOsdEventMsg = _NONE_MSG;
}

//----------------------------------------------------------------------------------------------------
void ShowMode(void)
{
    if (ucCurrState == _NOSIGNAL_STATE) 
        return;
    
    switch(_GET_INPUT_SOURCE())
    {
    case _SOURCE_VGA:
    case _SOURCE_DVI:
    case _SOURCE_HDMI:
        //display display size
        Gotoxy(5,_MESSAGE_V_POSITION,0x50);
        OutputDisplaySize();
        //display refresh
        Gotoxy(17,_MESSAGE_V_POSITION,0x50);
        OutputChar('@');          
        OutputChar(0x00);            
        OutputRefrushRate();  
        break; 

#if(_YPBPR_SUPPORT)
    case _SOURCE_YPBPR:
        if (stModeInfo.ModeCurr < _MAX_YPBPR_MODE)
           CenterTextout((BYTE *)sYPbPrMode[stModeInfo.ModeCurr],15,_MESSAGE_V_POSITION);
        break;
#endif

#if(_VIDEO_SUPPORT)
    case _SOURCE_VIDEO_AV:
    case _SOURCE_VIDEO_SV:
  //  case _SOURCE_VIDEO_YUV:
	case _SOURCE_VIDEO_DVD:
    case _SOURCE_VIDEO_SCART:
        if(CHECK60HZ())
            CenterTextout(sNTSC,14,_MESSAGE_V_POSITION);
        else
            CenterTextout(sPAL,14,_MESSAGE_V_POSITION);
        break;

  #if(_VIDEO_TV_SUPPORT) 
    case _SOURCE_VIDEO_TV:
#if(_NTSC_SEARCH_TABLE)
        CenterTextout((BYTE *)sCATV_AIR[_GET_CATV_AIR()], 14, _MESSAGE_V_POSITION);
#else
        CenterTextout((BYTE *)sTVType[ucTVType], 14, _MESSAGE_V_POSITION);
#endif
		break;
  #endif
#endif
    }
}

//---------------------------------------------------------------------------------------------------------------------
void OSDSlider(BYTE row, BYTE col, BYTE length, BYTE value, BYTE range,
               BYTE color, bit bMode)
{
    WORD bound;
    BYTE i,c;
    
    OSDLine(row, col, length + 6, color, THE_BYTE2);   // Set Slider Attribute. 4 extra columns for space/numbers/space
    bound   = length * value;
    Gotoxy(col,row,THE_BYTE1);
    OutputChar(0x21);          // Left Border
    
    for (i = 1; i <= length; i++)
    {
        if (bound)
        {
            if(bound >= range)
            {
                c       = 0x28;
                bound   = bound - range;
            }
            else
            {
                color   = (bound << 4) / range;
                bound   = 0;
                if (4 > color)                    c = 0x23;
                else if (7 > color)               c = 0x24;
                else if (10 > color)              c = 0x25;
                else if (13 > color)              c = 0x26;
                else                              c = 0x27;
            }
        }
        else
        {
            c = 0x22;
        }
        OutputChar(c);
    }
    OutputChar(0x29);    // Right Border
    OutputChar(0x00);

    if (_SHOW_PERCENT == bMode)
    {
        CShowNumber(value, 0);    //百分比显示在右边
        OutputChar(0x2a);
        if (value < 100)
           OutputChar(0x00);
    }
}

//---------------------------------------------------------------------------
void DispIcon(BYTE x, BYTE y, BYTE ucIconBaseAddr)
{
    Gotoxy(x, y, BYTE_DISPLAY);
    
    pData[0] = ucIconBaseAddr;
    pData[1] = ucIconBaseAddr + 1;
    pData[2] = ucIconBaseAddr + 2;
    CScalerWrite(_OSD_DATA_PORT_92, 3, pData, _NON_AUTOINC);
    
    Gotoxy(x, y + 1, BYTE_DISPLAY);
    pData[0] = ucIconBaseAddr + 3;
    pData[1] = ucIconBaseAddr + 4;
    pData[2] = ucIconBaseAddr + 5;
    CScalerWrite(_OSD_DATA_PORT_92, 3, pData, _NON_AUTOINC);
}
//---------------------------------------------------------------------------

void NotUseFunc()
{ 
 //   SetOSDRamAddress(0,0,0);
   // DirectWOSDRam(0,0,0,0);
 //   SetRowCmds(0,0);
    //  Gotoxy(0,0,0);
 //   OutputChar(0);
//    Textout(0);
//    PrintfDec(0);
    //    OSDPosition(0,0,0,0,0);
    //  OSDLine(0,0,0,0,0);
    //    OSDClear(0,0,0, 0,0,0);
  //  OutputDisplaySize();       //在当前的位置输出显示尺寸
 //   OutputRefrushRate();       //在当前的位置输出刷新频率
    //    COsdFxCodeWrite(0);
    //  COsdFxDisableOsd();
    //   COsdFxDrawWindow(0,0,0,0,0);
//    StrLen(0);
    //    ValueInRangeChange(0,0,0,0,0);
  //  CAutoDoAutoConfig();
    CAutoDoWhiteBalance();
#if(_VGA_SUPPORT)
    DoAuto();
#endif
    //   CEepromSaveOsdUserData();
    //    CEepromSaveBriConData();
  //  CEepromSaveColorTempData();
 //   CScalerLoadFont(0, 0, 0, 0);
    //  ShowMode();
    //   OSDSlider(0, 0, 0, 0, 0,0);   
   // GetNextLanguage(0);
//    GetPrevLanguage(0);
  //  CheckLanguage();
  //  FirstLanguage();
   //   COsdFxEnableOsd();
  //  DoReset();
 //   VPosGuage();
  //  HPosGuage();
 //   ClockGuage();
  //  COsdFxCloseWindow(0);
//    GotoAdjustBrightness();
 //   gmi_CInitial_IR();
 //   gmi_CStopIR();
//    gmi_CStartIR();
//    gmi_IR_Delay();
//    RightAlignTextOut(0,0,0);
 //   CShowNumber(0,0);
 //   CDrawColorPage();
//    CDrawOSDFuncPage();
  //  CDrawSoundPage();
  //  CDrawOtherFuncPage();
  //  GetVirtualKey();
  //  ShowMode();
  #if(_IR_ENABLE)
    gmi_IR_Delay();
  #endif
#if(_VIDEO_TV_SUPPORT)
 //   CTvAutoSearch();
    gmi_CRead9886();
//    gmi_CI2CWriteTuner(pData);
#endif

#if(_VIDEO_SUPPORT && _VIDEO_CHIP == _VDC_TB1334)
    gmi_CSetMode(VideoType, _DISPLAY_MODE_4_3, _SCALER_TYPE);  
    gmi_CVideoSyncHandler();
    gmi_CVideoModeChange();
#endif
}

//----------------------------------------------------------------------------------------------------
void CClearWindow(BYTE ucCharacterColor)
{
    OSDClear(0, ROW_COUNT, 0, COL_WIDTH, 0x8C, THE_BYTE0);
    OSDClear(0, ROW_COUNT, 0, COL_WIDTH, 0x00, THE_BYTE1);
    OSDClear(0, ROW_COUNT, 0, COL_WIDTH, ucCharacterColor, THE_BYTE2);
}

//----------------------------------------------------------------------------------------------------
void CInitOSDMainFrame(void)
{        
    COsdFxDisableOsd();
    COsdFxCodeWrite(ucCloseAllWindow);
    SetOSDRamAddress(ROW_COUNT,COL_WIDTH,FONT_BASE_ADDRESS);
    SetRowCmds(ROW_COUNT,COL_WIDTH);

#if(_ALPHA_BLENDING_ADJ || _OSD_DISPLAY_SIZE_ADJ)
if(Panel.DHWidth>1024||Panel.DVHeight>768)
       CSetOSDTransAndSize();
#endif

#if(_LOGO_EN && _LOGO_TYPE == _LOGO_TYPE1)
    COsdDispFirstTimeLoadFont();                 
#endif

    CClearWindow(0x40);  // Clear window and set character color to black
}



//----------------------------------------------------------------------------------------------------
void InitOSDFrame(void)
{    
    BYTE ucTemp = 0;
   
    CInitOSDMainFrame();

     if (_GET_OSD_SIZE()) 
        OSDPosition(_OSD_DOUBLE_WIDTH(_MAIN_WINDOW_WIDTH), _OSD_DOUBLE_HEIGHT(_MAIN_WINDOW_HEIGHT), stOsdUserData.OsdHPos+(_MAINMENU_DOUBLE_H_OFFSET), stOsdUserData.OsdVPos+(_MAINMENU_DOUBLE_V_OFFSET), 0x03);
      else
        OSDPosition(_MAIN_WINDOW_WIDTH, _MAIN_WINDOW_HEIGHT, stOsdUserData.OsdHPos+(_MAINMENU_H_OFFSET), stOsdUserData.OsdVPos+(_MAINMENU_V_OFFSET), 0x03);
    SetOSDDouble((_GET_OSD_SIZE() ? 0x03 : 0x00)  | OSD_WINDOWCHAR_BLENDING);   
    // Set item shadow
#if(_OSD_SHADOW_FUNC == _ENABLE)
    DirectWOSDRam(0x04, ROW_COUNT-0x04, THE_BYTE0, (0x80 | 0x18));
#endif
#if(!_OSD_DISPLAY_SIZE_ADJ && !_ALPHA_BLENDING_ADJ)
    pData[0] = 0x40;
    pData[1] = 0x03;
    pData[2] = 0xa0;
    CScalerWrite(_OSD_ADDR_MSB_90,3,pData,_AUTOINC);
#else
if(Panel.DHWidth<=1024&&Panel.DVHeight<=768)
     	{
    pData[0] = 0x40;
    pData[1] = 0x03;
    pData[2] = 0xa0;
    CScalerWrite(_OSD_ADDR_MSB_90,3,pData,_AUTOINC);
     	}
#endif

    // Draw window
    COsdFxDrawWindow(XSTART(_MAIN_WINDOW_H_POS),                  YSTART(_MAIN_WINDOW_V_POS), 
                     XEND(_MAIN_WINDOW_H_POS+_MAIN_WINDOW_WIDTH), YEND(_MAIN_WINDOW_V_POS+_MAIN_WINDOW_HEIGHT), 
                     tOSD_MAIN_WINDOW_STYLE);

    COsdFxDrawWindow(XSTART(_LINE_WINDOW_H_POS),                  YSTART(_LINE_WINDOW_V_POS),
                     XEND(_LINE_WINDOW_H_POS+_LINE_WINDOW_WIDTH), YEND(_LINE_WINDOW_V_POS+_LINE_WINDOW_HEIGHT), 
                     tOSD_LINE_WINDOW_STYLE);

    // Init Char Cmd
    // Set row 1/2 to 4bit
    OSDClear(1, 2, 0, COL_WIDTH-1, 0x90, BYTE_ATTRIB);

    // Set row height to 31, and col space to 0
    DirectWOSDRam(3, 1, THE_BYTE1, 0xf8); // Row 3
    // Set row height to 22, and col space to 0
    DirectWOSDRam(4, 9, THE_BYTE1, 0xb0); // Row 4 ~ (4+9)

    // Show 4bit Icon
    CShow4BitIcon();
    ShowMode();
    CLR_KEYREPEATENABLE();

}

//----------------------------------------------------------------------------------------------------
void CShow4BitIcon(void)
{
    BYTE uctemp;

    switch(_GET_INPUT_SOURCE())
    {
#if(_VGA_SUPPORT || _YPBPR_SUPPORT)
    case _SOURCE_VGA:
    case _SOURCE_YPBPR:
        for(uctemp = 0; uctemp < 6; uctemp++)
        {
            DispIcon(1+(4*uctemp), 1, _4BIT_ICON_COLOR_ADDR+(uctemp*6));
        } 
        break;
#endif

#if(_TMDS_SUPPORT || _VIDEO_AV_SUPPORT || _VIDEO_SV_SUPPORT || _VIDEO_YUV_SUPPORT || _HDMI_SUPPORT ||DVD_EN)                                    
    case _SOURCE_DVI:
    case _SOURCE_HDMI:
    case _SOURCE_VIDEO_AV:
    case _SOURCE_VIDEO_SV:
    //case _SOURCE_VIDEO_YUV:
   case _SOURCE_VIDEO_DVD:
    case _SOURCE_VIDEO_SCART:
        DispIcon(1+(4*0), 1, _4BIT_ICON_COLOR_ADDR+(0*6));
        DispIcon(1+(4*1), 1, _4BIT_ICON_COLOR_ADDR+(2*6));
        DispIcon(1+(4*2), 1, _4BIT_ICON_COLOR_ADDR+(3*6));
        DispIcon(1+(4*3), 1, _4BIT_ICON_COLOR_ADDR+(4*6));
        DispIcon(1+(4*4), 1, _4BIT_ICON_COLOR_ADDR+(5*6));

        break;
#endif // end #if(_TMDS_SUPPORT || _VIDEO_AV_SUPPORT || _VIDEO_SV_SUPPORT || _VIDEO_YUV_SUPPORT || _HDMI_SUPPORT || _VIDEO_SCART_SUPPORT)                                    

#if(_VIDEO_TV_SUPPORT)
    case _SOURCE_VIDEO_TV:
        for(uctemp = 0; uctemp < 6; uctemp++)
        {
            DispIcon(1+(4*uctemp), 1, _4BIT_ICON_COLOR_ADDR+(uctemp*6));
        } 
        break;
#endif  // end #if(_VIDEO_TV_SUPPORT)
    }
}     


//----------------------------------------------------------------------------------------------------
void CShowSelectMainItemWindow(BYTE ucItem)
{
    COsdFxDrawWindow(XSTART(16+(ucItem*48)), YSTART(12), XEND(64+(ucItem*48)), YEND(58), tOSD_SELECT_MAIN_WINDOW_STYLE);
}

//----------------------------------------------------------------------------------------------------
void CShowSubItemWindow(BYTE ucItem)
{
    OSDClear(4, 8, 1, COL_WIDTH-1, 0x40, BYTE_COLOR);            // Clear item color
    OSDClear((4+ucItem), 1, 1, COL_WIDTH-1, 0x10, BYTE_COLOR);   // Set current sub item character color to white
    COsdFxDrawWindow(XSTART(18), YSTART(81+(ucItem*23)), XEND(206), YEND(81+24+(ucItem*23)), tOSD_SELECT_SUB_WINDOW_STYLE);
}

//----------------------------------------------------------------------------------------------------
// Set window to select or move state
void CSetItemWindowState(BYTE ucWinNumber, BYTE ucItemState)
{
    pData[0]    = 0x81;
    pData[1]    = (BYTE)(ucWinNumber * 4+3);
    pData[2]    = SHADOW_BORDER_EN(1) | WINDOW_TYPE(ucItemState) | WINDOW_ENABLE(1);
    CScalerWrite(_OSD_ADDR_MSB_90, 3, pData, _AUTOINC);
}

//----------------------------------------------------------------------------------------------------
void CExitToMainItem(BYTE ucMainItem)
{
    OSDClear(4, 8, 1, COL_WIDTH-1, 0x40, BYTE_COLOR);  // Clear item color
    COsdFxCloseWindow(_SELECT_SUB_WINDOW);    // Disable sub item window
    ShowMode();
    ucOsdState = ucMainItem;

    CSetItemWindowState(_SELECT_MAIN_WINDOW, _MOVE_STATE); // Set main item window to move state
}

//----------------------------------------------------------------------------------------------------
void CGotoNextSubItem(BYTE ucItem)
{
    CShowSubItemWindow(ucItem);
    CLR_KEYREPEATENABLE();
}

//----------------------------------------------------------------------------------------------------
void CClearSubItem(void)
{   // Clear item character
    OSDClear(4, 8, 1, COL_WIDTH - 2, 0x00, BYTE_DISPLAY);
    OSDClear(4, 8, 1, COL_WIDTH - 2, 0x8C, BYTE_ATTRIB);
}

//----------------------------------------------------------------------------------------------------
void CClearMsg(BYTE ucMode)
{
    // Set Character width to 12 
    OSDLine(_MESSAGE_V_POSITION, 1, COL_WIDTH - 1, 0x8c, BYTE_ATTRIB);
    OSDClear(_MESSAGE_V_POSITION, 1, 1, COL_WIDTH - 2, 0x00, BYTE_DISPLAY);
    CLR_KEYREPEATENABLE();
    
    switch(ucMode)
    {
        case _CLEAR_AND_SELECT_SUB_ITEM:
            CSetItemWindowState(_SELECT_SUB_WINDOW, _SELECT_STATE);
            break;

        case _CLEAR_AND_EXIT_SUB_ITEM:
            CSetItemWindowState(_SELECT_SUB_WINDOW, _MOVE_STATE);
            ShowMode();
            break;

        case _CLEAR_MSG_ONLY:
            break;
    }
}

//----------------------------------------------------------------------------------------------------
void CDrawColorPage(void)
{                     
    BYTE uctemp = 4;
	

    CLeftAlignTextout((BYTE *)sBright[GET_LANGUAGE], 1, uctemp++);          // "Brightness"
    CLeftAlignTextout((BYTE *)sContrast[GET_LANGUAGE], 1, uctemp++);        // "Contrast"

    uctemp = uctemp;

    switch(_GET_INPUT_SOURCE())
    {
#if(_VGA_SUPPORT || _TMDS_SUPPORT || _YPBPR_SUPPORT || _HDMI_SUPPORT)
    case _SOURCE_VGA:
    case _SOURCE_DVI:
    case _SOURCE_HDMI:
    case _SOURCE_YPBPR:
    #if(_COLOR_TEMP)
        if (_SOURCE_YPBPR != _GET_INPUT_SOURCE())
        {
            CLeftAlignTextout((BYTE *)sColorTemp[GET_LANGUAGE], 1, uctemp++);   // "Color Temp."
            uctemp = uctemp;
        }
        else
            uctemp = uctemp;
    #else
        uctemp = uctemp;
    #endif
        break;
#endif

#if(_VIDEO_SUPPORT)                                    
    case _SOURCE_VIDEO_AV:
    case _SOURCE_VIDEO_SV:
  //  case _SOURCE_VIDEO_YUV:
    case _SOURCE_VIDEO_TV:
    case _SOURCE_VIDEO_SCART:
    case _SOURCE_VIDEO_DVD:
        CLeftAlignTextout((BYTE *)sSaturation[GET_LANGUAGE], 1, uctemp++);  // "Saturation"
        if(CHECK60HZ())
        CLeftAlignTextout((BYTE *)sHue[GET_LANGUAGE], 1, uctemp++);         // "Hue"
            uctemp = uctemp;
        break;
#endif
    }

    CLeftAlignTextout((BYTE *)sExit[GET_LANGUAGE], 1, uctemp);    // "Exit"

}

//----------------------------------------------------------------------------------------------------
void CDrawOSDFuncPage(void)
{
    BYTE uctemp = 4;

    CLeftAlignTextout((BYTE *)sLanguage[GET_LANGUAGE], 1, uctemp++);       // "Language"

#if(_OSD_POSITION_ADJ_CTRL)
    CLeftAlignTextout((BYTE *)sOSDHPosition[GET_LANGUAGE], 1, uctemp++);       // "OSD H Position"
    CLeftAlignTextout((BYTE *)sOSDVPosition[GET_LANGUAGE], 1, uctemp++);       // "OSD V Position"
#else
#endif
    
#if(_OSD_TIMEOUT_ADJ_CTRL)
    CLeftAlignTextout((BYTE *)sOSDTimeOut[GET_LANGUAGE], 1, uctemp++);     // "OSD Timeout"
#endif

#if(_ALPHA_BLENDING_ADJ == _ON)
    CLeftAlignTextout((BYTE *)sOSDTranslucent[GET_LANGUAGE], 1, uctemp++); // "OSD Translucent"
#endif

#if(_OSD_DISPLAY_SIZE_ADJ == _ON)
if(Panel.DHWidth>1024||Panel.DVHeight>768)
     	{
         CLeftAlignTextout((BYTE *)sOSDSize[GET_LANGUAGE], 1, uctemp++);        // "OSD Size"

     }
#endif
   #if(_DISPLAY_SIZE_ADJ)
        if(Panel.DHWidth > (Panel.DVHeight * 4/3)) 
 	//if(!((_GET_INPUT_SOURCE()==_SOURCE_VGA)||(_GET_INPUT_SOURCE()==_SOURCE_DVI)))
    	{
          CLeftAlignTextout((BYTE *)sDispMode[GET_LANGUAGE], 1, uctemp++);        // "OSD Size"
    	}
#endif

    CLeftAlignTextout((BYTE *)sExit[GET_LANGUAGE], 1, uctemp++);           // "Exit"
}

//----------------------------------------------------------------------------------------------------
void CDrawSoundPage(void)
{
    CLeftAlignTextout((BYTE *)sVolume[GET_LANGUAGE], 1, 4);          // "Volume"
    CLeftAlignTextout((BYTE *)sMute[GET_LANGUAGE], 1, 5);            // "Mute"

#if(_SOUND_PROCESSOR == _ENABLE)
    CLeftAlignTextout((BYTE *)sBalance[GET_LANGUAGE], 1, 6);         // "Balance"
    CLeftAlignTextout((BYTE *)sBass[GET_LANGUAGE], 1, 7);            // "Bass"
    CLeftAlignTextout((BYTE *)sTreble[GET_LANGUAGE], 1, 8);          // "Treble"
    CLeftAlignTextout((BYTE *)sSRS[GET_LANGUAGE], 1, 9);             // "SRS"
    CLeftAlignTextout((BYTE *)sBBE[GET_LANGUAGE], 1, 10);            // "BBE"
    CLeftAlignTextout((BYTE *)sExit[GET_LANGUAGE], 1, 11);           // "Exit"
#else
    CLeftAlignTextout((BYTE *)sExit[GET_LANGUAGE], 1, 6);            // "Exit"
#endif
}
//----------------------------------------------------------------------------------------------------

#if(_VGA_COLOR_SUPPORT)
void CDrawVividColorPage(void)
{         
    CClearVColorItem();                                             
    CLeftAlignTextout((BYTE *)sText, 1, 1);                // "Text"
    CLeftAlignTextout((BYTE *)sMovie, 1, 2);               // "Movie"
    CLeftAlignTextout((BYTE *)sGraphic, 1, 3);             // "Graphic"
    CLeftAlignTextout((BYTE *)sGame, 1, 4);                // "Game"
    CLeftAlignTextout((BYTE *)sNormal, 1, 5);              // "Normal"
    CLeftAlignTextout((BYTE *)sUser, 1, 6);                // "User"
    CLeftAlignTextout((BYTE *)sExit[GET_LANGUAGE], 1, 7);  // "Exit"
    

}
//----------------------------------------------------------------------------------------------------
void CDrawVividColorSubPage(void)
{
    CClearVColorItem();
    CLeftAlignTextout((BYTE *)sVividColor, 3, 1);          // "Vivid Color"
    CLeftAlignTextout((BYTE *)sDCC, 4, 3);                 // "DCC"
    CLeftAlignTextout((BYTE *)sICM, 4, 4);                 // "ICM"
    CLeftAlignTextout((BYTE *)sColor, 4, 5);               // "Color"
    CLeftAlignTextout((BYTE *)sExit[GET_LANGUAGE], 4, 6);  // "Exit" 
}

//----------------------------------------------------------------------------------------------------
void CDrawDCCPage(void)
{
    CClearVColorItem();
    CLeftAlignTextout((BYTE *)sText, 3, 1);                // "Text"
    CLeftAlignTextout((BYTE *)sMovie, 3, 2);               // "Movie"
    CLeftAlignTextout((BYTE *)sGraphic, 3, 3);             // "Graphic"
    CLeftAlignTextout((BYTE *)sGame, 3, 4);                // "Game"
    CLeftAlignTextout((BYTE *)sDCCNormal, 3, 5);           // "DCC Normal"
}

//----------------------------------------------------------------------------------------------------
void CDrawICMPage(void)
{
    CClearVColorItem(); 
    CLeftAlignTextout((BYTE *)sRed, 1, 1);                  // "Red"
    CLeftAlignTextout((BYTE *)sGreen, 1, 2);                // "Green"
    CLeftAlignTextout((BYTE *)sBlue_ENG, 1, 3);             // "Blue"
    CLeftAlignTextout((BYTE *)sYellow, 1, 4);               // "Yellow"
    CLeftAlignTextout((BYTE *)sCyan, 1, 5);                 // "Cyan"
    CLeftAlignTextout((BYTE *)sMagenta, 1, 6);              // "Magenta"                                
    CLeftAlignTextout((BYTE *)sICM, 1, 7);                  // "ICM"
    CenterTextout((BYTE *)sOn_Off[GET_MZ_ICM_ON_OFF_TYPE()][GET_LANGUAGE], 8, 7);
    CLeftAlignTextout((BYTE *)sExit[GET_LANGUAGE], 1, 8);   // "Exit"  
}

//----------------------------------------------------------------------------------------------------
void CDrawVividSubColorPage(void)
{
    CClearVColorItem();
    CLeftAlignTextout((BYTE *)sBright[GET_LANGUAGE], 1, 1);    // "Bright"
    Gotoxy(13, 1, BYTE_DISPLAY);         
    CShowNumber(stOsdUserData.MZBright, 0);

    CLeftAlignTextout((BYTE *)sContrast[GET_LANGUAGE], 1, 3);  // "Contrast"
    Gotoxy(12, 3, BYTE_DISPLAY);         
    CShowNumber(stOsdUserData.MZContrast, 0);

    CLeftAlignTextout((BYTE *)sPeaking, 1, 5);                 // "Peaking"
    Gotoxy(12, 5, BYTE_DISPLAY);         
    CShowNumber(stOsdUserData.MZPeaking, 0);

    CLeftAlignTextout((BYTE *)sExit[GET_LANGUAGE], 1, 7);      // "Exit"
}

//----------------------------------------------------------------------------------------------------
void CDrawICMColorAdjPage(void)
{
    CClearVColorItem();
    CLeftAlignTextout((BYTE *)sHue[GET_LANGUAGE], 1, 2);         // "Hue"
    CLeftAlignTextout((BYTE *)sSaturation[GET_LANGUAGE], 1, 4);  // "Saturation"
    CLeftAlignTextout((BYTE *)sExit[GET_LANGUAGE], 1, 6);        // "Exit"

}
#endif

//----------------------------------------------------------------------------------------------------
void CDrawOtherFuncPage(void)
{
    BYTE uctemp = 5;
    CLeftAlignTextout((BYTE *)sReset[GET_LANGUAGE], 1, 4);           // "Reset"
/* for close blue adjust by chenlinfu 2007/09/28
#if(_BLUE_BACKGROUND_FUNC == _ENABLE)
    CLeftAlignTextout((BYTE *)sBlue[GET_LANGUAGE], 1, 5);            // "Blue"
    uctemp++;
#endif
*/
#if(_AUTO_POWER_DOWN)
    CLeftAlignTextout((BYTE *)sAutoPowerDown[GET_LANGUAGE], 1, uctemp);   // "Auto power down"
    uctemp++;
#endif
          
#if(_IMAGE_COLOR_MODE)
    CLeftAlignTextout((BYTE *)sColorMode[GET_LANGUAGE], 1, uctemp);  // "Color mode"
    uctemp++;
#endif
           
#if(_SHARPNESS_ADJ)
    CLeftAlignTextout((BYTE *)sSharp[GET_LANGUAGE], 1, uctemp);      // "Sharp"
    uctemp++;
#endif      

    CLeftAlignTextout((BYTE *)sExit[GET_LANGUAGE], 1, uctemp);       // "Exit"
}   

//----------------------------------------------------------------------------------------------------
void CDrawExitPage(void)
{
    CLeftAlignTextout((BYTE *)sExit[GET_LANGUAGE], 1, 4);            // "Exit"
}

//----------------------------------------------------------------------------------------------------
//   Color Sub item
void MColorSubItemProc(void)
{
    switch(ucKeyMessage)
    {
        // Select item
#if(_USE_UD_LR_KEY_MSG)
        case VK_F_LEFT:
        case VK_F_RIGHT:
#endif
#if(_KEY_TYPE_OSD007==_7KEY_SUPPORT)
        case VK_RIGHT:        
        case VK_LEFT:     
#else
        case VK_MENU:    
#endif
        case VK_IR_OK:    
			MColorSubItemMenu();               break;

        // Move item
#if(_USE_UD_LR_KEY_MSG)
        case VK_F_UP:
#endif
#if(_KEY_TYPE_OSD007!=_7KEY_SUPPORT)
        case VK_RIGHT:        
#endif
			MColorSubItemLR(1);                break;

        // Move item
#if(_USE_UD_LR_KEY_MSG)
        case VK_F_DOWN:
#endif
#if(_KEY_TYPE_OSD007!=_7KEY_SUPPORT)
        case VK_LEFT:      
#endif
			MColorSubItemLR(0);                break;

        // Exit item
#if(_MENU_FUNC == _MENU_EXIT_ITEM)
        case VK_ENTER:      
#endif
#if(_KEY_TYPE_OSD007==_7KEY_SUPPORT)
        case VK_MENU:    
#endif
        case VK_AUTO:
        case VK_IR_EXIT:
         CExitToMainItem(MENU_MAIN_COLOR);  break;
        // Other key
        default:             COthterKeyAction();                break;
    }
}

//----------------------------------------------------------------------------------------------------
void MColorSubItemMenu(void)
{      
    CClearMsg(_CLEAR_AND_SELECT_SUB_ITEM);

    switch(ucOsdState)
    {
        case MENU_ITEM_BRIGHT:  
            SLIDER1(BRIGHTNESS_GUAGE);
            ucOsdState = MENU_SUB_BRIGH_ADJ;     
            _SET_IMAGE_COLOR_MODE(3); // Mode user  //0228 guo
            CEepromSaveOsdUserData();
            break;

        case MENU_ITEM_CONTRAST:       
            SLIDER1(CONTRAST_GUAGE);
            ucOsdState = MENU_SUB_CONTRAST_ADJ;   
            _SET_IMAGE_COLOR_MODE(3); // Mode user //0228 guo
            CEepromSaveOsdUserData();
            break;

#if(_VGA_SUPPORT || _TMDS_SUPPORT || _YPBPR_SUPPORT)
   #if(_COLOR_TEMP)
        case MENU_ITEM_COLOR_TEMP:
            CClearSubItem();
            CDrawColorTempSubItem();
            {
                BYTE ucTemp = GET_COLOR_TEMP_TYPE();

                switch(ucTemp)
                {
                    case 0:
                        ucOsdState = MENU_SUB_CT_9300;        
                        break;

                    case 1:
                        ucOsdState = MENU_SUB_CT_6500;        
                        break;

                    case 2:
                        ucOsdState = MENU_SUB_CT_USER;        
                        break;

                    default:
                        ucOsdState = MENU_SUB_CT_USER; 
                        SET_COLOR_TEMP_TYPE(_CT_USER);
                        break;
                }

                CShowSubItemWindow(ucTemp);
            }
            break;
   #endif
#endif

#if(_VIDEO_SUPPORT)
        case MENU_AV_SATURATION:
            SLIDER1(SATURATION_GUAGE);
            ucOsdState = MENU_AV_SATURATION_ADJ;
            _SET_IMAGE_COLOR_MODE(3); // Mode user //0228 guo
            CEepromSaveOsdUserData();
            break;

        case MENU_AV_HUE:
            SLIDER1(HUE_GUAGE);
            ucOsdState = MENU_AV_HUE_ADJ;
            break;
#endif

        case MENU_SUB_COLOR_CLOSE:
            CExitToMainItem(MENU_MAIN_COLOR);
            break;
    }
}

//----------------------------------------------------------------------------------------------------
void MColorSubItemLR(BYTE LR)
{
    BYTE ucTemp = 0;

    if(LR)
    {
        switch(ucOsdState)
        {
            case MENU_ITEM_BRIGHT:         ucOsdState = MENU_ITEM_CONTRAST;     break;
            case MENU_ITEM_CONTRAST:
            
#if(_VIDEO_SUPPORT)
   #if(_COLOR_TEMP)
                if (CGetInputSourceNum(_GET_INPUT_SOURCE()) == 2)  // Source video
                    ucOsdState = MENU_AV_SATURATION;
                else
                    ucOsdState = (_SOURCE_YPBPR == _GET_INPUT_SOURCE()) ? MENU_SUB_COLOR_CLOSE : MENU_ITEM_COLOR_TEMP;
//                ucOsdState = (CGetInputSourceNum(_GET_INPUT_SOURCE()) == 2) ? MENU_AV_SATURATION : MENU_ITEM_COLOR_TEMP;
   #else
                ucOsdState = (CGetInputSourceNum(_GET_INPUT_SOURCE()) == 2) ? MENU_AV_SATURATION : MENU_SUB_COLOR_CLOSE;
   #endif
#else
   #if(_COLOR_TEMP)
                ucOsdState = MENU_ITEM_COLOR_TEMP;
   #else
                ucOsdState = MENU_SUB_COLOR_CLOSE;
   #endif
#endif           
                break;

#if(_VIDEO_SUPPORT)
            case MENU_AV_SATURATION:       
                           
                   if(CHECK60HZ())
				ucOsdState = MENU_AV_HUE;    
		    else
			      ucOsdState = MENU_SUB_COLOR_CLOSE; 
			  break;
            case MENU_AV_HUE:              ucOsdState = MENU_SUB_COLOR_CLOSE;   break;
#endif

            case MENU_ITEM_COLOR_TEMP:     ucOsdState = MENU_SUB_COLOR_CLOSE;   break;
            case MENU_SUB_COLOR_CLOSE:     ucOsdState = MENU_ITEM_BRIGHT;       break;
        }
    }
    else
    {
        switch(ucOsdState)
        {
            case MENU_ITEM_BRIGHT:         ucOsdState = MENU_SUB_COLOR_CLOSE;   break;
            case MENU_ITEM_CONTRAST:       ucOsdState = MENU_ITEM_BRIGHT;       break;
            case MENU_ITEM_COLOR_TEMP:     ucOsdState = MENU_ITEM_CONTRAST;     break;

#if(_VIDEO_SUPPORT)
            case MENU_AV_SATURATION:       ucOsdState = MENU_ITEM_CONTRAST;     break;
            case MENU_AV_HUE:              ucOsdState = MENU_AV_SATURATION;     break;
            case MENU_SUB_COLOR_CLOSE:
   #if(_COLOR_TEMP)
                if (CGetInputSourceNum(_GET_INPUT_SOURCE()) == 2)  // Source video
                	{
        if((CHECK60HZ()))
                ucOsdState = (CGetInputSourceNum(_GET_INPUT_SOURCE()) == 2) ? MENU_AV_HUE : MENU_ITEM_COLOR_TEMP;
        else
                ucOsdState = (CGetInputSourceNum(_GET_INPUT_SOURCE()) == 2) ? MENU_AV_SATURATION : MENU_ITEM_COLOR_TEMP;
                	}
				
                    //ucOsdState = MENU_AV_HUE;
                else
                    ucOsdState = (_SOURCE_YPBPR == _GET_INPUT_SOURCE()) ? MENU_ITEM_CONTRAST : MENU_ITEM_COLOR_TEMP;

              //  ucOsdState = (CGetInputSourceNum(_GET_INPUT_SOURCE()) == 2) ? MENU_AV_HUE : MENU_ITEM_COLOR_TEMP;
   #else
        if(CHECK60HZ())
                ucOsdState = (CGetInputSourceNum(_GET_INPUT_SOURCE()) == 2) ? MENU_AV_HUE : MENU_AV_SATURATION;
        else
                ucOsdState = (CGetInputSourceNum(_GET_INPUT_SOURCE()) == 2) ? MENU_AV_SATURATION : MENU_ITEM_CONTRAST;
   #endif
                break;
#else
   #if(_COLOR_TEMP)
            case MENU_SUB_COLOR_CLOSE:     ucOsdState = MENU_ITEM_COLOR_TEMP;   break;
   #else
            case MENU_SUB_COLOR_CLOSE:     ucOsdState = MENU_ITEM_CONTRAST;     break;
   #endif
#endif
        }
    }
    
    switch(ucOsdState)
    {      
        case MENU_ITEM_BRIGHT:
            ucTemp = 0;      
            break;

        case MENU_ITEM_CONTRAST:
            ucTemp = 1;      
            break;

#if(_VIDEO_SUPPORT)
        case MENU_AV_SATURATION:
            ucTemp = 2;
            break;

        if(CHECK60HZ())
        	{
        case MENU_AV_HUE:
            ucTemp = 3;
            break;
        	}
#endif

#if(_COLOR_TEMP)
        case MENU_ITEM_COLOR_TEMP:
            ucTemp = 2;      
            break;
#endif

        case MENU_SUB_COLOR_CLOSE:
#if(_VIDEO_SUPPORT)
    #if(_COLOR_TEMP)
            if (CGetInputSourceNum(_GET_INPUT_SOURCE()) == 2)  // Source video
                ucTemp = 4;
            else
                ucTemp = (_SOURCE_YPBPR == _GET_INPUT_SOURCE()) ? 2 : 3;
//            ucTemp = (CGetInputSourceNum(_GET_INPUT_SOURCE()) == 2) ? 4 : 3; 
    #else
        if(CHECK60HZ())
            ucTemp = (CGetInputSourceNum(_GET_INPUT_SOURCE()) == 2) ? 4 : 2; 
		else
            ucTemp = (CGetInputSourceNum(_GET_INPUT_SOURCE()) == 2) ? 3 : 2; 
    #endif
#else
    #if(_COLOR_TEMP)
            ucTemp = 3;      
    #else
            ucTemp = 2;      
    #endif
#endif     
            break;
    }   
    
    CGotoNextSubItem(ucTemp);
}


//----------------------------------------------------------------------------------------------------
//   OSD Sub item
void MOSDSubItemProc(void)
{
    switch(ucKeyMessage)
    {
        // Select item
#if(_USE_UD_LR_KEY_MSG)
        case VK_F_LEFT:
        case VK_F_RIGHT:
#endif
#if(_KEY_TYPE_OSD007==_7KEY_SUPPORT)
        case VK_RIGHT:        
        case VK_LEFT:     
#else
        case VK_MENU:     
#endif
        case VK_IR_OK:     
			MOSDSubItemMenu();                    break;

        // Move item
#if(_USE_UD_LR_KEY_MSG)
        case VK_F_UP:
#endif
#if(_KEY_TYPE_OSD007!=_7KEY_SUPPORT)
        case VK_RIGHT:        
#endif
			MOSDSubItemLR(1);                     break;

        // Move item
#if(_USE_UD_LR_KEY_MSG)
        case VK_F_DOWN:
#endif
#if(_KEY_TYPE_OSD007!=_7KEY_SUPPORT)
        case VK_LEFT:       
#endif
			MOSDSubItemLR(0);                     break;

        // Exit item
#if(_MENU_FUNC == _MENU_EXIT_ITEM)
        case VK_ENTER:       
#endif
#if(_KEY_TYPE_OSD007==_7KEY_SUPPORT)
        case VK_MENU:     
#endif
        case VK_AUTO:
        case VK_IR_EXIT:
        CExitToMainItem(MENU_MAIN_OSD_FUNC);  break;
        // Other key
        default:             COthterKeyAction();                   break;
    }
}

//----------------------------------------------------------------------------------------------------
void MOSDSubItemMenu(void)
{
    CClearMsg(_CLEAR_AND_SELECT_SUB_ITEM);

    switch(ucOsdState)
    {
        case MENU_SUB_LANGUAGE:
            CenterTextout((BYTE *)sLangName[GET_LANGUAGE], 14, _MESSAGE_V_POSITION);
            ucOsdState = MENU_SUB_OSDLANGUAGE_ADJ;     
            break;

#if(_OSD_POSITION_ADJ_CTRL)
        case MENU_SUB_H_POSITION:       
            SLIDER1(stOsdUserData.OsdHPos);
            ucOsdState = MENU_SUB_OSDH_POSITION_ADJ;   
            break;

        case MENU_SUB_V_POSITION:     
            SLIDER1(stOsdUserData.OsdVPos);
            ucOsdState = MENU_SUB_OSDV_POSITION_ADJ;   
            break;
#endif

#if(_OSD_TIMEOUT_ADJ_CTRL)
        case MENU_SUB_OSD_TIMEOUT:  
            if (stOsdUserData.OsdTimeout < 5)
            {
                CenterTextout((BYTE *)sOn_Off[0][GET_LANGUAGE], 14, _MESSAGE_V_POSITION);
            }
            else
            {
                Gotoxy(14, _MESSAGE_V_POSITION, BYTE_DISPLAY);
                CShowNumber(stOsdUserData.OsdTimeout, 0);
            }
            ucOsdState = MENU_SUB_OSD_TIMEOUT_ADJ;   
            break;
#endif

#if(_ALPHA_BLENDING_ADJ)
        case MENU_SUB_OSD_TRANSLUCENT:
            if (0 == _GET_OSD_TRANSLUCENT())
            {
                CenterTextout((BYTE *)sOn_Off[0][GET_LANGUAGE], 14, _MESSAGE_V_POSITION);
            }
            else
            {
                Gotoxy(14, _MESSAGE_V_POSITION, BYTE_DISPLAY);
                CShowNumber(_GET_OSD_TRANSLUCENT(), 0);
            }
            ucOsdState = MENU_SUB_OSD_TRANS_ADJ;   
            break;
#endif

#if(_OSD_DISPLAY_SIZE_ADJ)
if(Panel.DHWidth>1024||Panel.DVHeight>768)
     	{
        case MENU_SUB_OSD_SIZE:
            CenterTextout((BYTE *)sOn_Off[_GET_OSD_SIZE()][GET_LANGUAGE], 14, _MESSAGE_V_POSITION);
            ucOsdState = MENU_SUB_OSD_SIZE_ADJ;   
            break;
     	}
#endif

      #if(_DISPLAY_SIZE_ADJ)
	   if(Panel.DHWidth > (Panel.DVHeight * 4/3)) 
	   	{
	     case MENU_SUB_DISMODE:
                   CenterTextout((BYTE *)sDisp_mode[_GET_DISPLAY_MODE()], 14, _MESSAGE_V_POSITION);
                   ucOsdState = MENU_SUB_DISPMODE_ADJ;     
            break;
	   	}
#endif

        case MENU_SUB_OSD_CLOSE:
            CExitToMainItem(MENU_MAIN_OSD_FUNC);
            break;
    }
}

//----------------------------------------------------------------------------------------------------
bit bOSDItemSupport(BYTE ucOSDItem)
{
    switch(ucOSDItem)
    {
        case MENU_SUB_LANGUAGE:
        case MENU_SUB_OSD_CLOSE:
            return 1;
      #if(_DISPLAY_SIZE_ADJ)
		case MENU_SUB_DISMODE:
	   if(Panel.DHWidth > (Panel.DVHeight * 4/3)) 
            return 1;
	    else
            return 0;
     #endif

#if(_OSD_POSITION_ADJ_CTRL)
        case MENU_SUB_H_POSITION:
        case MENU_SUB_V_POSITION:
            return 1;
#endif

#if(_OSD_TIMEOUT_ADJ_CTRL)
        case MENU_SUB_OSD_TIMEOUT:
            return 1;
#endif

#if(_ALPHA_BLENDING_ADJ)
        case MENU_SUB_OSD_TRANSLUCENT:
            return 1;
#endif

#if(_OSD_DISPLAY_SIZE_ADJ)
        case MENU_SUB_OSD_SIZE:
if(Panel.DHWidth>1024||Panel.DVHeight>768)
            return 1;
	 else
            return 0;
#endif
    } 
    
    return 0;
}

//----------------------------------------------------------------------------------------------------
void MOSDSubItemLR(BYTE LR)
{
    BYTE ucTemp  = 0;
    BYTE ucItem  = 0;
    
    // Search next item
    while(1)
    {
        ucOsdState = ValueInRangeChange(MENU_SUB_LANGUAGE, MENU_SUB_OSD_CLOSE, ucOsdState, LR, 1);

        if (bOSDItemSupport(ucOsdState))
            break; 
    }

    // Search item position
    ucTemp = MENU_SUB_LANGUAGE;
    while(1)
    {
        if (ucOsdState == ucTemp)
           break;

        ucTemp = ValueInRangeChange(MENU_SUB_LANGUAGE, MENU_SUB_OSD_CLOSE,ucTemp, 1, 1);

        if (bOSDItemSupport(ucTemp))
           ucItem++;
    }

    CGotoNextSubItem(ucItem);
}


//----------------------------------------------------------------------------------------------------
#if(_OSD_POSITION_ADJ_CTRL)
// OSD H position
void MOSDHPositionAdjProc(void)
{
    switch(ucKeyMessage)
    {
        // Move item
#if(_USE_UD_LR_KEY_MSG)
        case VK_F_UP:
        case VK_F_DOWN:
            MOSDHPositionAdjMenu();
            COsdProc();
            break;
#endif

        // Exit item
#if(_MENU_FUNC == _MENU_EXIT_ITEM)
        case VK_ENTER: 
#endif
        case VK_AUTO:
        case VK_IR_EXIT:
        case VK_MENU:        MOSDHPositionAdjMenu();       break;

        // Adjust
#if(_USE_UD_LR_KEY_MSG)
        case VK_F_LEFT:
#endif
        case VK_LEFT:        MOSDHPositionAdjLR(1);        break;
    
        // Adjust
#if(_USE_UD_LR_KEY_MSG)
        case VK_F_RIGHT:
#endif
        case VK_RIGHT:       MOSDHPositionAdjLR(0);        break;
               
        // Other key
        default:             COthterKeyAction();      break;
    }
}

//----------------------------------------------------------------------------------------------------
void MOSDHPositionAdjMenu(void)
{
    ucOsdState = MENU_SUB_H_POSITION;
    CClearMsg(_CLEAR_AND_EXIT_SUB_ITEM);
}

//----------------------------------------------------------------------------------------------------
void MOSDHPositionAdjLR(BYTE LR)
{
    SET_KEYREPEATENABLE();
    stOsdUserData.OsdHPos = ValueInRangeChange(0, 100, stOsdUserData.OsdHPos, LR, 0);
    SLIDER1(stOsdUserData.OsdHPos);
    SetOSDDouble((_GET_OSD_SIZE() ? 0x03 : 0x00)  | OSD_WINDOWCHAR_BLENDING);   
     if (_GET_OSD_SIZE()) 
        OSDPosition(_OSD_DOUBLE_WIDTH(_MAIN_WINDOW_WIDTH), _OSD_DOUBLE_HEIGHT(_MAIN_WINDOW_HEIGHT), stOsdUserData.OsdHPos+(_MAINMENU_DOUBLE_H_OFFSET), stOsdUserData.OsdVPos+(_MAINMENU_DOUBLE_V_OFFSET), 0x03);
      else
        OSDPosition(_MAIN_WINDOW_WIDTH, _MAIN_WINDOW_HEIGHT, stOsdUserData.OsdHPos+(_MAINMENU_H_OFFSET), stOsdUserData.OsdVPos+(_MAINMENU_V_OFFSET), 0x03);

    ucOsdEventMsg = _SAVE_EE_OSDUSERDATA_MSG;
}

//----------------------------------------------------------------------------------------------------

// OSD V position
void MOSDVPositionAdjProc(void)
{
    switch(ucKeyMessage)
    {
        // Move item
#if(_USE_UD_LR_KEY_MSG)
        case VK_F_UP:
        case VK_F_DOWN:
            MOSDVPositionAdjMenu();
            COsdProc();
            break;
#endif

        // Exit item
#if(_MENU_FUNC == _MENU_EXIT_ITEM)
        case VK_ENTER: 
#endif
        case VK_AUTO:
        case VK_IR_EXIT:
        case VK_MENU:        MOSDVPositionAdjMenu();       break;

        // Adjust
#if(_USE_UD_LR_KEY_MSG)
        case VK_F_LEFT:
#endif
        case VK_LEFT:        MOSDVPositionAdjLR(1);        break;
    
        // Adjust
#if(_USE_UD_LR_KEY_MSG)
        case VK_F_RIGHT:
#endif
        case VK_RIGHT:       MOSDVPositionAdjLR(0);        break;
                
        // Other key
        default:             COthterKeyAction();           break;
    }
}

//----------------------------------------------------------------------------------------------------
void MOSDVPositionAdjMenu(void)
{
    ucOsdState = MENU_SUB_V_POSITION;
    CClearMsg(_CLEAR_AND_EXIT_SUB_ITEM);
}

//----------------------------------------------------------------------------------------------------
void MOSDVPositionAdjLR(BYTE LR)
{
    SET_KEYREPEATENABLE();
    stOsdUserData.OsdVPos = ValueInRangeChange(0, 100, stOsdUserData.OsdVPos, LR, 0);
    SLIDER1(stOsdUserData.OsdVPos);
     if (_GET_OSD_SIZE()) 
        OSDPosition(_OSD_DOUBLE_WIDTH(_MAIN_WINDOW_WIDTH), _OSD_DOUBLE_HEIGHT(_MAIN_WINDOW_HEIGHT), stOsdUserData.OsdHPos+(_MAINMENU_DOUBLE_H_OFFSET), stOsdUserData.OsdVPos+(_MAINMENU_DOUBLE_V_OFFSET), 0x03);
      else
        OSDPosition(_MAIN_WINDOW_WIDTH, _MAIN_WINDOW_HEIGHT, stOsdUserData.OsdHPos+(_MAINMENU_H_OFFSET), stOsdUserData.OsdVPos+(_MAINMENU_V_OFFSET), 0x03);
    SetOSDDouble((_GET_OSD_SIZE() ? 0x03 : 0x00)  | OSD_WINDOWCHAR_BLENDING);   

    ucOsdEventMsg = _SAVE_EE_OSDUSERDATA_MSG;
}

#endif
//----------------------------------------------------------------------------------------------------

#if(_OSD_TIMEOUT_ADJ_CTRL)
// OSD timeout
void MOSDTimeoutAdjProc(void)
{
    switch(ucKeyMessage)
    {
        // Move item
#if(_USE_UD_LR_KEY_MSG)
        case VK_F_UP:
        case VK_F_DOWN:
            MOSDTimeoutAdjMenu();
            COsdProc();
            break;
#endif

        // Exit item
#if(_MENU_FUNC == _MENU_EXIT_ITEM)
        case VK_ENTER: 
#endif
        case VK_AUTO:
        case VK_IR_EXIT:
        case VK_MENU:        MOSDTimeoutAdjMenu();       break;

        // Adjust
#if(_USE_UD_LR_KEY_MSG)
        case VK_F_LEFT:
#endif
        case VK_LEFT:        MOSDTimeoutAdjLR(1);        break;

        // Adjust
#if(_USE_UD_LR_KEY_MSG)
        case VK_F_RIGHT:
#endif
        case VK_RIGHT:       MOSDTimeoutAdjLR(0);        break;
           
        // Other key
        default:             COthterKeyAction();         break;
    }
}

//----------------------------------------------------------------------------------------------------
void MOSDTimeoutAdjMenu(void)
{
    ucOsdState = MENU_SUB_OSD_TIMEOUT;
    CClearMsg(_CLEAR_AND_EXIT_SUB_ITEM);
}

//----------------------------------------------------------------------------------------------------
void MOSDTimeoutAdjLR(BYTE LR)
{
    SET_KEYREPEATENABLE();
    CClearMsg(_CLEAR_MSG_ONLY);

    stOsdUserData.OsdTimeout = ValueInRangeChange(4, 30, stOsdUserData.OsdTimeout, LR, 1);

    if (stOsdUserData.OsdTimeout == 4)
    {
        CenterTextout((BYTE *)sOn_Off[0][GET_LANGUAGE], 14, _MESSAGE_V_POSITION);
    }
    else
    {
        Gotoxy(14, _MESSAGE_V_POSITION, BYTE_DISPLAY);
        CShowNumber(stOsdUserData.OsdTimeout, 0);
    }

    ucOsdEventMsg = _SAVE_EE_OSDUSERDATA_MSG;
}

#endif
//----------------------------------------------------------------------------------------------------

#if(_ALPHA_BLENDING_ADJ)
// OSD Translucent sub item
void MOSDTranslucentAdjProc(void)
{
    switch(ucKeyMessage)
    {
        // Move item
#if(_USE_UD_LR_KEY_MSG)
        case VK_F_UP:
        case VK_F_DOWN:
            MOSDTranslucentAdjMenu();
            COsdProc();
            break;
#endif

        // Exit item
#if(_MENU_FUNC == _MENU_EXIT_ITEM)
        case VK_ENTER: 
#endif
        case VK_AUTO:
        case VK_IR_EXIT:
        case VK_MENU:        MOSDTranslucentAdjMenu();       break;


        // Adjust
#if(_USE_UD_LR_KEY_MSG)
        case VK_F_LEFT:
#endif
        case VK_LEFT:        MOSDTranslucentAdjLR(1);        break;

        // Adjust
#if(_USE_UD_LR_KEY_MSG)
        case VK_F_RIGHT:
#endif
        case VK_RIGHT:       MOSDTranslucentAdjLR(0);        break;
            
        // Other key
        default:             COthterKeyAction();             break;
    }
}

//----------------------------------------------------------------------------------------------------
void MOSDTranslucentAdjMenu(void)
{
    ucOsdState = MENU_SUB_OSD_TRANSLUCENT;
    CClearMsg(_CLEAR_AND_EXIT_SUB_ITEM);
}

//----------------------------------------------------------------------------------------------------
void MOSDTranslucentAdjLR(BYTE LR)
{
    BYTE ucTemp = _GET_OSD_TRANSLUCENT();

    CClearMsg(_CLEAR_MSG_ONLY);

    ucTemp = ValueInRangeChange(0, 7, ucTemp, LR, 1);

    _SET_OSD_TRANSLUCENT(ucTemp);
    CSetOSDTransAndSize();

    if (ucTemp == 0)
    {
        CenterTextout((BYTE *)sOn_Off[0][GET_LANGUAGE], 14, _MESSAGE_V_POSITION);
    }
    else
    {
        Gotoxy(14, _MESSAGE_V_POSITION, BYTE_DISPLAY);
        CShowNumber(ucTemp, 0);
    }

    ucOsdEventMsg = _SAVE_EE_OSDUSERDATA_MSG;
}

#endif

//----------------------------------------------------------------------------------------------------
#if(_ALPHA_BLENDING_ADJ || _OSD_DISPLAY_SIZE_ADJ)
void CSetOSDTransAndSize(void)
{
    BYTE ucTemp      = 0;
    BYTE ucTransMode = _GET_OSD_TRANSLUCENT();
#if(_OSD_DISPLAY_SIZE_ADJ)
    BYTE ucOSDSize   = _GET_OSD_SIZE();
#endif

    switch(ucTransMode)
    {
        case 0:  // Disable osd translucent
            pData[0] = 0x40;
            pData[1] = 0x03;
#if(_OSD_DISPLAY_SIZE_ADJ)
if(Panel.DHWidth>1024||Panel.DVHeight>768)
            pData[2] = ((ucOSDSize) ? 0x03 : 0x00) | 0xa0;
    else
            pData[2] = 0xa0;
#else
            pData[2] = 0xa0;
#endif
            CScalerWrite(_OSD_ADDR_MSB_90,3,pData,_AUTOINC);
            break;

        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
            pData[0] = 0x40;
            pData[1] = 0x03;
#if(_OSD_DISPLAY_SIZE_ADJ)
            pData[2] = ((ucOSDSize) ? 0x0f : 0x0c) | 0xa0;
#else
            pData[2] = 0x0c | 0xa0;
#endif
            CScalerWrite(_OSD_ADDR_MSB_90,3,pData,_AUTOINC);

            CScalerRead(_OVERLAY_CTRL_6C, 1, &ucTemp, _NON_AUTOINC);
            ucTemp = (ucTemp & 0xe3) | (ucTransMode << 2);
            CScalerSetByte(_OVERLAY_CTRL_6C, ucTemp);
            break;
    }
}
#endif

#if(_OSD_DISPLAY_SIZE_ADJ)
//--------- OSD Size proc ----------------------------------
void MOSDSizeAdjProc(void)
{
    switch(ucKeyMessage)
    {
        // Move item
#if(_USE_UD_LR_KEY_MSG)
        case VK_F_UP:
        case VK_F_DOWN:
            MOSDSizeAdjMenu();
            COsdProc();
            break;
#endif

        // Exit item
#if(_MENU_FUNC == _MENU_EXIT_ITEM)
        case VK_ENTER: 
#endif
        case VK_AUTO:
        case VK_IR_EXIT:
        case VK_MENU:        MOSDSizeAdjMenu();       break;

        // Adjust
#if(_USE_UD_LR_KEY_MSG)
        case VK_F_LEFT:
#endif
        case VK_LEFT:        MOSDSizeAdjLR(1);        break;

        // Adjust
#if(_USE_UD_LR_KEY_MSG)
        case VK_F_RIGHT:
#endif
        case VK_RIGHT:       MOSDSizeAdjLR(0);        break;
            
        // Other key
        default:             COthterKeyAction();      break;
    }
}

//----------------------------------------------------------------------------------------------------
void MOSDSizeAdjMenu(void)
{
    ucOsdState = MENU_SUB_OSD_SIZE;
    CClearMsg(_CLEAR_AND_EXIT_SUB_ITEM);
}

//----------------------------------------------------------------------------------------------------
void MOSDSizeAdjLR(BYTE LR)
{   
    CClearMsg(_CLEAR_MSG_ONLY);

    LR = _GET_OSD_SIZE();
    
    LR = 1 - LR;

    // Disable OSD
    CTimerWaitForEvent(_EVENT_DEN_STOP);
    CScalerSetBit(_OVERLAY_CTRL_6C, ~_BIT0, 0x00);
    
    _SET_OSD_SIZE(LR);
     if (_GET_OSD_SIZE()) 
        OSDPosition(_OSD_DOUBLE_WIDTH(_MAIN_WINDOW_WIDTH), _OSD_DOUBLE_HEIGHT(_MAIN_WINDOW_HEIGHT), stOsdUserData.OsdHPos+(_MAINMENU_DOUBLE_H_OFFSET), stOsdUserData.OsdVPos+(_MAINMENU_DOUBLE_V_OFFSET), 0x03);
      else
        OSDPosition(_MAIN_WINDOW_WIDTH, _MAIN_WINDOW_HEIGHT, stOsdUserData.OsdHPos+(_MAINMENU_H_OFFSET), stOsdUserData.OsdVPos+(_MAINMENU_V_OFFSET), 0x03);
    SetOSDDouble((_GET_OSD_SIZE() ? 0x03 : 0x00)  | OSD_WINDOWCHAR_BLENDING);   
    CSetOSDTransAndSize();

    // Enable OSD
    CTimerWaitForEvent(_EVENT_DEN_STOP);
    CScalerSetBit(_OVERLAY_CTRL_6C, ~_BIT0, _BIT0);

    CenterTextout((BYTE *)sOn_Off[LR][GET_LANGUAGE], 14, _MESSAGE_V_POSITION);

    ucOsdEventMsg = _SAVE_EE_OSDUSERDATA_MSG;
}

#endif

//----------------------------------------------------------------------------------------------------
//   Sound Sub item
void MSoundSubItemProc(void)
{
    switch(ucKeyMessage)
    {
        // Select item
#if(_USE_UD_LR_KEY_MSG)
        case VK_F_LEFT:
        case VK_F_RIGHT:
        //    MSoundSubItemMenu();
          //  break;
#endif
#if(_KEY_TYPE_OSD007==_7KEY_SUPPORT)
        case VK_RIGHT:        
        case VK_LEFT:     
#else
        case VK_MENU:      
#endif
        case VK_IR_OK:      
			MSoundSubItemMenu();               break;

        // Move item
#if(_USE_UD_LR_KEY_MSG)
        case VK_F_UP:
#endif
#if(_KEY_TYPE_OSD007!=_7KEY_SUPPORT)
        case VK_RIGHT:       
#endif
			MSoundSubItemLR(1);                break;

        // Move item
#if(_USE_UD_LR_KEY_MSG)
        case VK_F_DOWN:
#endif
#if(_KEY_TYPE_OSD007!=_7KEY_SUPPORT)
        case VK_LEFT:       
#endif
			MSoundSubItemLR(0);                break;

        // Exit item
#if(_MENU_FUNC == _MENU_EXIT_ITEM)
        case VK_ENTER:      
#endif
#if(_KEY_TYPE_OSD007==_7KEY_SUPPORT)
        case VK_MENU:      
#endif
        case VK_AUTO:
        case VK_IR_EXIT:
            CExitToMainItem(MENU_MAIN_SOUND);  break; 
        // Other key
        default:             COthterKeyAction();                break;
    }
}

//----------------------------------------------------------------------------------------------------
void MSoundSubItemMenu(void)
{
    BYTE ucTemp = 0;

    CClearMsg(_CLEAR_AND_SELECT_SUB_ITEM);

    switch(ucOsdState)
    {
        case MENU_SUB_VOLUME:
            ucTemp = stOsdUserData.Volume;
            ucOsdState = MENU_SUB_VOL_ADJ;     
            break;

        case MENU_SUB_MUTE: 
            CenterTextout((BYTE *)sOn_Off[(GET_MUTE_STATE() == STATE_MUTEON) ? 1 : 0][GET_LANGUAGE], 14, _MESSAGE_V_POSITION);
            ucOsdState = MENU_SUB_MUTE_ADJ;     
            return;  // Not show slider

#if(_SOUND_PROCESSOR == _ENABLE)
        case MENU_SUB_BALANCE:
            ucTemp = stOsdUserData.Balance;
            ucOsdState = MENU_SUB_BALANCE_ADJ;     
            break;

        case MENU_SUB_BASS:
            ucTemp = stOsdUserData.Bass;
            ucOsdState = MENU_SUB_BASS_ADJ;     
            break;

        case MENU_SUB_TREBLE:
            ucTemp = stOsdUserData.Treble;
            ucOsdState = MENU_SUB_TREBLE_ADJ;     
            break;

        case MENU_SUB_SRS:
            ucTemp = stOsdUserData.SRS;
            ucOsdState = MENU_SUB_SRS_ADJ;     
            break;

        case MENU_SUB_BBE:
            ucTemp = stOsdUserData.BBE;
            ucOsdState = MENU_SUB_BBE_ADJ;     
            break;
#endif

        case MENU_SUB_SOUND_CLOSE: 
            CExitToMainItem(MENU_MAIN_SOUND);
            return;
    }

    SLIDER1(ucTemp);
}

//----------------------------------------------------------------------------------------------------
void MSoundSubItemLR(BYTE LR)
{            
#if(_SOUND_PROCESSOR == _DISABLE)
    BYTE ucTemp = 0;

#else

    ucOsdState = ValueInRangeChange(MENU_SUB_VOLUME, MENU_SUB_SOUND_CLOSE, ucOsdState, LR, 1);

#endif
    
#if(_SOUND_PROCESSOR == _DISABLE)
    if(LR)
    {
        switch(ucOsdState)
        {
            case MENU_SUB_VOLUME:      ucOsdState = MENU_SUB_MUTE;        break;

#if(_SOUND_PROCESSOR == _ENABLE)
            case MENU_SUB_MUTE:        ucOsdState = MENU_SUB_BALANCE;     break;
            case MENU_SUB_BALANCE:     ucOsdState = MENU_SUB_BASS;        break;
            case MENU_SUB_BASS:        ucOsdState = MENU_SUB_TREBLE;      break;
            case MENU_SUB_TREBLE:      ucOsdState = MENU_SUB_SRS;         break;
            case MENU_SUB_SRS:         ucOsdState = MENU_SUB_BBE;         break;
            case MENU_SUB_BBE:         ucOsdState = MENU_SUB_SOUND_CLOSE; break;
#else
            case MENU_SUB_MUTE:        ucOsdState = MENU_SUB_SOUND_CLOSE; break;
#endif

            case MENU_SUB_SOUND_CLOSE: ucOsdState = MENU_SUB_VOLUME;      break;
        }
    }
    else
    {
        switch(ucOsdState)
        {
            case MENU_SUB_VOLUME:      ucOsdState = MENU_SUB_SOUND_CLOSE; break;
            case MENU_SUB_MUTE:        ucOsdState = MENU_SUB_VOLUME;      break;

#if(_SOUND_PROCESSOR == _ENABLE)
            case MENU_SUB_BALANCE:     ucOsdState = MENU_SUB_MUTE;        break;
            case MENU_SUB_BASS:        ucOsdState = MENU_SUB_BALANCE;     break;
            case MENU_SUB_TREBLE:      ucOsdState = MENU_SUB_BASS;        break;
            case MENU_SUB_SRS:         ucOsdState = MENU_SUB_TREBLE;      break;
            case MENU_SUB_BBE:         ucOsdState = MENU_SUB_SRS;         break;
            case MENU_SUB_SOUND_CLOSE: ucOsdState = MENU_SUB_BBE;         break;
#else
            case MENU_SUB_SOUND_CLOSE: ucOsdState = MENU_SUB_MUTE;        break;
#endif
        }
    }   
    
    switch(ucOsdState)
    {      
        case MENU_SUB_VOLUME:  
            ucTemp = 0;      
            break;

        case MENU_SUB_MUTE: 
            ucTemp = 1;      
            break;

#if(_SOUND_PROCESSOR == _ENABLE)
        case MENU_SUB_BALANCE:
            ucTemp = 2;      
            break;

        case MENU_SUB_BASS:
            ucTemp = 3;      
            break;

        case MENU_SUB_TREBLE:
            ucTemp = 4;      
            break;

        case MENU_SUB_SRS:
            ucTemp = 5;      
            break;

        case MENU_SUB_BBE:
            ucTemp = 6;      
            break;
#endif

        case MENU_SUB_SOUND_CLOSE:
#if(_SOUND_PROCESSOR == _ENABLE)
            ucTemp = 7;
#else
            ucTemp = 2;
#endif      
            break;
    }
     
    CGotoNextSubItem(ucTemp);

#else
       
    CGotoNextSubItem(ucOsdState - MENU_SUB_VOLUME);

#endif  // end #if(_SOUND_PROCESSOR == _DISABLE) 
}
//----------------------------------------------------------------------------------------------------

#if(_VGA_COLOR_SUPPORT)
void CClearVColorItem(void)
{
    OSDClear(1, 8, 1, 20, 0x00, BYTE_DISPLAY);
    OSDClear(1, 8, 1, 20, 0x8C, BYTE_ATTRIB);
}
//----------------------------------------------------------------------------------------------------

void CShowVColorSubItemWindow(BYTE ucItem)
{
    OSDClear(1, 8, 1, 20, 0x40, BYTE_COLOR);           // Clear item color
    OSDClear((1+ucItem), 1, 1, 20, 0x10, BYTE_COLOR); // Set current sub item character color to white
}
//----------------------------------------------------------------------------------------------------
      
void CShowVColorSelectSubItemWindow(BYTE ucItem)
{
    OSDClear(1, 8, 1, 20, 0x40, BYTE_COLOR);           // Clear item color
    OSDClear((1+ucItem), 1, 1, 20, 0x20, BYTE_COLOR); // Set current sub item character color to red
}       
//----------------------------------------------------------------------------------------------------

void CGotoAdjustVColor(void)
{
    CInitOSDMainFrame();

     if (_GET_OSD_SIZE()) 
        OSDPosition(_OSD_DOUBLE_WIDTH(_VCOLOR_WINDOW_WIDTH), _OSD_DOUBLE_HEIGHT(_VCOLOR_WINDOW_HEIGHT), _AUTO_H_OFFSET, _AUTO_V_OFFSET, 0x03);
      else
       OSDPosition(_VCOLOR_WINDOW_WIDTH, _VCOLOR_WINDOW_HEIGHT, _AUTO_DOUBLE_H_OFFSET, _AUTO_DOUBLE_V_OFFSET, 0x03);
     SetOSDDouble((_GET_OSD_SIZE() ? 0x03 : 0x00)  | OSD_WINDOWCHAR_BLENDING);   

    // Set row height to 22, and col space to 0
    DirectWOSDRam(1, 7, THE_BYTE1, 0xf0); // Row 1 ~ (1+7)

    // Draw window
    COsdFxDrawWindow(XSTART(_VCOLOR_WINDOW_H_POS), YSTART(_VCOLOR_WINDOW_V_POS), XEND(_VCOLOR_WINDOW_WIDTH), YEND(_VCOLOR_WINDOW_HEIGHT), tOSD_MINI_WINDOW_STYLE);  
    CDrawVividColorPage();
    CShowVColorSubItemWindow(GET_SAC_DCC_TYPE());

    COsdFxEnableOsd();
    ucOsdState = MENU_SAC_DCC_TEXT + GET_SAC_DCC_TYPE();
}

//----------------------------------------------------------------------------------------------------
// Vivid color page
//----------------------------------------------------------------------------------------------------
void MVividColorItemProc(void)
{
    switch(ucKeyMessage)
    {
        // Select item
#if(_USE_UD_LR_KEY_MSG)
        case VK_F_LEFT:
        case VK_F_RIGHT:
#endif
        case VK_MENU:        MVividColorItemMenu();                   break;

        // Move item
#if(_USE_UD_LR_KEY_MSG)
        case VK_F_UP:
#endif
        case VK_RIGHT:        MVividColorItemLR(1);                    break;

        // Move item
#if(_USE_UD_LR_KEY_MSG)
        case VK_F_DOWN:
#endif
        case VK_LEFT:       MVividColorItemLR(0);                    break;

        // Exit item
#if(_MENU_FUNC == _MENU_EXIT_ITEM)
        case VK_ENTER:       
#endif
        case VK_AUTO:
            COsdFxDisableOsd();                      break;
        // Other key
        default:             COthterKeyAction();                      break;
    }
}

//----------------------------------------------------------------------------------------------------
void MVividColorItemMenu(void)
{
    BYTE ucTemp = 0;

    switch(ucOsdState)
    {
        case MENU_SAC_DCC_TEXT:               // DCC <Text>
        case MENU_SAC_DCC_MOVIE:              // DCC <Movie>
        case MENU_SAC_DCC_GRAPHIC:            // DCC <Graphic>
        case MENU_SAC_DCC_GAME:               // DCC <Game>
        case MENU_SAC_DCC_NORMAL:             // DCC <Normal>
        case MENU_SAC_DCC_CLOSE:              // DCC <Exit>
            COsdFxDisableOsd();
            break;

        case MENU_SAC_DCC_USER:               // DCC <User>
            CDrawVividColorSubPage();
            ucOsdState = MENU_USER_ITEM_DCC;  
            CShowVColorSubItemWindow(_FIRST_ITEM+2);
            break;
    }
}

//----------------------------------------------------------------------------------------------------
void MVividColorItemLR(BYTE LR)
{
    ucOsdState = ValueInRangeChange(MENU_SAC_DCC_TEXT, MENU_SAC_DCC_CLOSE, ucOsdState, LR, 1);
    
    CShowVColorSubItemWindow(ucOsdState - MENU_SAC_DCC_TEXT);

    switch(ucOsdState)
    {
        case MENU_SAC_DCC_TEXT:        CSetSACMode(_SAC_DCC_TEXT);    break;
        case MENU_SAC_DCC_MOVIE:       CSetSACMode(_SAC_DCC_MOVIE);   break;
        case MENU_SAC_DCC_GRAPHIC:     CSetSACMode(_SAC_DCC_GRAPHIC); break;
        case MENU_SAC_DCC_GAME:        CSetSACMode(_SAC_DCC_GAME);    break;
        case MENU_SAC_DCC_NORMAL:      CSetSACMode(_SAC_DCC_NORMAL);  break;
        case MENU_SAC_DCC_USER:        CSetSACMode(_SAC_DCC_USER);    break;
        case MENU_SAC_DCC_CLOSE:                                      break; // DCC <Exit>
    }

    ucOsdEventMsg = _SAVE_EE_OSDUSERDATA_MSG;
}

//----------------------------------------------------------------------------------------------------
// Vivid color sub page
//----------------------------------------------------------------------------------------------------
void MVividColorSubProc(void)
{
    switch(ucKeyMessage)
    {
        // Select item
#if(_USE_UD_LR_KEY_MSG)
        case VK_F_LEFT:
        case VK_F_RIGHT:
#endif
        case VK_MENU:        MVividColorSubMenu();        break; 

        // Move item
#if(_USE_UD_LR_KEY_MSG)
        case VK_F_UP:
#endif
        case VK_RIGHT:        MVividColorSubLR(1);         break;

        // Move item
#if(_USE_UD_LR_KEY_MSG)
        case VK_F_DOWN:
#endif
        case VK_LEFT:       MVividColorSubLR(0);         break;

        // Exit item
#if(_MENU_FUNC == _MENU_EXIT_ITEM)
        case VK_ENTER:      
            CDrawVividColorPage();
            ucOsdState = MENU_SAC_DCC_USER;
            CShowVColorSubItemWindow(ucOsdState - MENU_SAC_DCC_TEXT);
#endif
            
        // Other key
        default:             COthterKeyAction();          break;
    }
}

//----------------------------------------------------------------------------------------------------
void MVividColorSubMenu(void)
{
    switch(ucOsdState)
    {
        case MENU_USER_ITEM_DCC:              // Vivid Color <DCC>
            CDrawDCCPage();
            ucOsdState = MENU_DCC_ITEM_TEXT + GET_MZ_DCC_TYPE();
            CShowVColorSubItemWindow(GET_MZ_DCC_TYPE());
            break;

        case MENU_USER_ITEM_ICM:              // Vivid Color <ICM>
            CDrawICMPage();
            ucOsdState = MENU_ICM_ITEM_ON_OFF;
            CShowVColorSubItemWindow(MENU_ICM_ITEM_ON_OFF - MENU_ICM_ITEM_RED);
            break;

        case MENU_USER_ITEM_COLOR:            // Vivid Color <Color>
            CDrawVividSubColorPage();
            ucOsdState = MENU_COLOR_ITEM_BRIGHTNESS;
            CShowVColorSubItemWindow(_FIRST_ITEM);
            break;

        case MENU_USER_ITEM_CLOSE:            // Vivid Color <Exit>
            CDrawVividColorPage();
            ucOsdState = MENU_SAC_DCC_USER;
            CShowVColorSubItemWindow(MENU_SAC_DCC_USER - MENU_SAC_DCC_TEXT);
            break;
    }
}

//----------------------------------------------------------------------------------------------------
void MVividColorSubLR(BYTE LR)
{
    ucOsdState = ValueInRangeChange(MENU_USER_ITEM_DCC, MENU_USER_ITEM_CLOSE, ucOsdState, LR, 1);
       
    CShowVColorSubItemWindow(ucOsdState - MENU_USER_ITEM_DCC + 2);
}

//----------------------------------------------------------------------------------------------------
// DCC page
//----------------------------------------------------------------------------------------------------
void MDCCAdjProc(void)
{
    switch(ucKeyMessage)
    {
        // Select item
#if(_USE_UD_LR_KEY_MSG)
        case VK_F_LEFT:
        case VK_F_RIGHT:
#endif
        case VK_MENU:        MDCCAdjMenu();                         break;

        // Move item
#if(_USE_UD_LR_KEY_MSG)
        case VK_F_UP:
#endif
        case VK_LEFT:        MDCCAdjLR(1);           break;

        // Move item
#if(_USE_UD_LR_KEY_MSG)
        case VK_F_DOWN:
#endif
        case VK_RIGHT:       MDCCAdjLR(0);           break;

        // Exit item
#if(_MENU_FUNC == _MENU_EXIT_ITEM)
        case VK_ENTER:       
            CDrawVividColorSubPage();
            ucOsdState = MENU_USER_ITEM_DCC;  
            CShowVColorSubItemWindow(_FIRST_ITEM+2);
#endif
            
        // Other key
        default:             COthterKeyAction();     break;
    }
}

//----------------------------------------------------------------------------------------------------
void MDCCAdjMenu(void)
{
    switch(ucOsdState)
    {
        case MENU_DCC_ITEM_TEXT:
        case MENU_DCC_ITEM_MOVIE:
        case MENU_DCC_ITEM_GRAPHIC:
        case MENU_DCC_ITEM_GAME:
        case MENU_DCC_ITEM_NORMAL:
            CDrawVividColorSubPage();
            ucOsdState = MENU_USER_ITEM_DCC;  
            CShowVColorSubItemWindow(_FIRST_ITEM+2);
            break;
    }
}

//----------------------------------------------------------------------------------------------------
void MDCCAdjLR(BYTE LR)
{
    BYTE uctemp =0;

    ucOsdState = ValueInRangeChange(MENU_DCC_ITEM_TEXT, MENU_DCC_ITEM_NORMAL, ucOsdState, LR, 1);
    
    uctemp = ucOsdState - MENU_DCC_ITEM_TEXT;  // DCC type
    SET_MZ_DCC_TYPE(uctemp);

    if(uctemp < _MZ_DCC_NORMAL)
    {
        CAdjustFillDCCTable(tDCC_CONTROL[GET_MZ_DCC_TYPE()], tDCC_USERCURVE[GET_MZ_DCC_TYPE()]);
        CScalerSetBit(_DCC_CTRL0_E4, ~_BIT7, _BIT7);
    }
    else if(uctemp == _MZ_DCC_NORMAL)
    {
        if (GET_MZ_ICM_ON_OFF_TYPE() == _OFF)
           CAdjustDisableHLWindow(); 

        CScalerSetBit(_DCC_CTRL0_E4, ~_BIT7, 0x00);
    }
   
    CShowVColorSubItemWindow(ucOsdState - MENU_DCC_ITEM_TEXT);

    ucOsdEventMsg = _SAVE_EE_OSDUSERDATA_MSG;
}

//----------------------------------------------------------------------------------------------------
// ICM page
//----------------------------------------------------------------------------------------------------
void MICMItemProc(void)
{
    switch(ucKeyMessage)
    {
        // Select item
#if(_USE_UD_LR_KEY_MSG)
        case VK_F_LEFT:
        case VK_F_RIGHT:
#endif
        case VK_MENU:        MICMItemMenu();                          break;

        // Move item
#if(_USE_UD_LR_KEY_MSG)
        case VK_F_UP:
#endif
        case VK_LEFT:        MICMItemLR(1);          break;

        // Move item
#if(_USE_UD_LR_KEY_MSG)
        case VK_F_DOWN:
#endif
        case VK_RIGHT:       MICMItemLR(0);          break;

        // Exit item
#if(_MENU_FUNC == _MENU_EXIT_ITEM)
        case VK_ENTER:       
            CDrawVividColorSubPage();
            ucOsdState = MENU_USER_ITEM_ICM;  
            CShowVColorSubItemWindow(3);
#endif
            
        // Other key
        default:             COthterKeyAction();     break;
    }
}

//----------------------------------------------------------------------------------------------------
void MICMItemMenu(void)
{
    BYTE ucHue = 0;
    BYTE ucSat = 0;

    switch(ucOsdState)
    {
        case MENU_ICM_ITEM_RED: 
            ucHue = stOsdUserData.MZICMRedHue;
            ucSat = stOsdUserData.MZICMRedSat;
            ucOsdState = MENU_ICM_SUB_R_HUE;
            break;

        case MENU_ICM_ITEM_GREEN:      
            ucHue = stOsdUserData.MZICMGreenHue;
            ucSat = stOsdUserData.MZICMGreenSat;
            ucOsdState = MENU_ICM_SUB_G_HUE;     
            break;

        case MENU_ICM_ITEM_BLUE:       
            ucHue = stOsdUserData.MZICMBlueHue;
            ucSat = stOsdUserData.MZICMBlueSat;
            ucOsdState = MENU_ICM_SUB_B_HUE;     
            break;
            
        case MENU_ICM_ITEM_YELLOW: 
            ucHue = stOsdUserData.MZICMYellowHue;
            ucSat = stOsdUserData.MZICMYellowSat;
            ucOsdState = MENU_ICM_SUB_Y_HUE;
            break;

        case MENU_ICM_ITEM_CYAN:      
            ucHue = stOsdUserData.MZICMCyanHue;
            ucSat = stOsdUserData.MZICMCyanSat;
            ucOsdState = MENU_ICM_SUB_C_HUE;     
            break;

        case MENU_ICM_ITEM_MAGENTA:       
            ucHue = stOsdUserData.MZICMMagentaHue;
            ucSat = stOsdUserData.MZICMMagentaSat;
            ucOsdState = MENU_ICM_SUB_M_HUE;     
            break;
            
        case MENU_ICM_ITEM_ON_OFF:
            if (GET_MZ_ICM_ON_OFF_TYPE())  // ICM on
            {
                SET_MZ_ICM_ON_OFF_TYPE(_OFF);
                CScalerSetBit(_ICM_CTRL_E0, ~_BIT7, 0x00);
            }
            else
            {
                SET_MZ_ICM_ON_OFF_TYPE(_ON);
                CScalerSetBit(_ICM_CTRL_E0, ~_BIT7, _BIT7);
            }
            CenterTextout((BYTE *)sOn_Off[GET_MZ_ICM_ON_OFF_TYPE()][GET_LANGUAGE], 8, 7);
            OutputChar(0x00);
            ucOsdEventMsg = _SAVE_EE_OSDUSERDATA_MSG;
            return;

        case MENU_ICM_ITEM_CLOSE:
            CDrawVividColorSubPage();
            ucOsdState = MENU_USER_ITEM_ICM;  
            CShowVColorSubItemWindow(3);
            return;
    }

    CDrawICMColorAdjPage();
    CShowVColorSubItemWindow(_FIRST_ITEM+1);

    Gotoxy(11,2,BYTE_DISPLAY);         
    CShowNumber(ucHue, 0);
    Gotoxy(14,4,BYTE_DISPLAY);         
    CShowNumber(ucSat, 0);
}

//----------------------------------------------------------------------------------------------------
void MICMItemLR(BYTE LR)
{
    if (GET_MZ_ICM_ON_OFF_TYPE() == _OFF && (ucOsdState == MENU_ICM_ITEM_ON_OFF || ucOsdState == MENU_ICM_ITEM_CLOSE))
    {
        ucOsdState = (ucOsdState == MENU_ICM_ITEM_ON_OFF) ? MENU_ICM_ITEM_CLOSE : MENU_ICM_ITEM_ON_OFF;
    }
    else
        ucOsdState = ValueInRangeChange(MENU_ICM_ITEM_RED, MENU_ICM_ITEM_CLOSE, ucOsdState, LR, 1);

      
    CShowVColorSubItemWindow(ucOsdState - MENU_ICM_ITEM_RED);
}

//----------------------------------------------------------------------------------------------------
// ICM R/G/B item page
//----------------------------------------------------------------------------------------------------
void MICMSubRGBItemAdjProc(void)
{
    switch(ucKeyMessage)
    {
        // Select item
#if(_USE_UD_LR_KEY_MSG)
        case VK_F_LEFT:
        case VK_F_RIGHT:
#endif
        case VK_MENU:        MICMSubRGBItemAdjMenu();     break;

        // Move item
#if(_USE_UD_LR_KEY_MSG)
        case VK_F_UP:
#endif
        case VK_LEFT:        MICMSubRGBItemAdjLR(1);      break;

        // Move item
#if(_USE_UD_LR_KEY_MSG)
        case VK_F_DOWN:
#endif
        case VK_RIGHT:       MICMSubRGBItemAdjLR(0);      break;

        // Exit item
#if(_MENU_FUNC == _MENU_EXIT_ITEM)
        case VK_ENTER:       
            switch(ucOsdState)
            {
                //-------------  Red --------------
                case MENU_ICM_SUB_R_HUE:
                case MENU_ICM_SUB_R_SAT:
                case MENU_ICM_SUB_R_CLOSE:
                    CExitToICMPage(MENU_ICM_ITEM_RED);
                    break;
        
                //------------- Green -------------
                case MENU_ICM_SUB_G_HUE:
                case MENU_ICM_SUB_G_SAT:
                case MENU_ICM_SUB_G_CLOSE:
                    CExitToICMPage(MENU_ICM_ITEM_GREEN);
                    break;
        
                //-------------- Blue -------------
                case MENU_ICM_SUB_B_HUE:
                case MENU_ICM_SUB_B_SAT:
                case MENU_ICM_SUB_B_CLOSE:
                    CExitToICMPage(MENU_ICM_ITEM_BLUE);
                    break;

                //------------ Yellow -------------
                case MENU_ICM_SUB_Y_HUE:
                case MENU_ICM_SUB_Y_SAT:
                case MENU_ICM_SUB_Y_CLOSE:
                    CExitToICMPage(MENU_ICM_ITEM_YELLOW);
                    break;
        
                //-------------_ Cyan -------------
                case MENU_ICM_SUB_C_HUE:
                case MENU_ICM_SUB_C_SAT:
                case MENU_ICM_SUB_C_CLOSE:
                    CExitToICMPage(MENU_ICM_ITEM_CYAN);
                    break;
        
                //------------ Magenta ------------
                case MENU_ICM_SUB_M_HUE:
                case MENU_ICM_SUB_M_SAT:
                case MENU_ICM_SUB_M_CLOSE:
                    CExitToICMPage(MENU_ICM_ITEM_MAGENTA);
                    break;
            }
#endif
            
        // Other key
        default:             COthterKeyAction();          break;
    }
}

//----------------------------------------------------------------------------------------------------
void CExitToICMPage(const BYTE ucExitToItem)
{
    CDrawICMPage();
    ucOsdState = ucExitToItem;
    CShowVColorSubItemWindow(ucOsdState - MENU_ICM_ITEM_RED);
}

void MICMSubRGBItemAdjMenu(void)
{
    BYTE ucTemp       = 0;

    switch(ucOsdState)
    {
        //-------------  Red --------------------
        case MENU_ICM_SUB_R_HUE:
            ucOsdState   = MENU_ICM_R_HUE_ADJ;
            ucTemp       = 1;
            break;

        case MENU_ICM_SUB_R_SAT:
            ucOsdState   = MENU_ICM_R_SAT_ADJ;
            ucTemp       = 3;
            break;

        case MENU_ICM_SUB_R_CLOSE:
            CExitToICMPage(MENU_ICM_ITEM_RED);
            return;

        //------------- Green -------------
        case MENU_ICM_SUB_G_HUE:
            ucOsdState   = MENU_ICM_G_HUE_ADJ;
            ucTemp       = 1;
            break;

        case MENU_ICM_SUB_G_SAT:
            ucOsdState   = MENU_ICM_G_SAT_ADJ;
            ucTemp       = 3;
            break;

        case MENU_ICM_SUB_G_CLOSE:
            CExitToICMPage(MENU_ICM_ITEM_GREEN);
            return;

        //-------------- Blue ---------------
        case MENU_ICM_SUB_B_HUE:
            ucOsdState   = MENU_ICM_B_HUE_ADJ;
            ucTemp       = 1;
            break;

        case MENU_ICM_SUB_B_SAT:
            ucOsdState   = MENU_ICM_B_SAT_ADJ;
            ucTemp       = 3;
            break;

        case MENU_ICM_SUB_B_CLOSE:
            CExitToICMPage(MENU_ICM_ITEM_BLUE);
            return;

        //------------- Yellow ---------------
        case MENU_ICM_SUB_Y_HUE:
            ucOsdState   = MENU_ICM_Y_HUE_ADJ;
            ucTemp       = 1;
            break;

        case MENU_ICM_SUB_Y_SAT:
            ucOsdState   = MENU_ICM_Y_SAT_ADJ;
            ucTemp       = 3;
            break;

        case MENU_ICM_SUB_Y_CLOSE:
            CExitToICMPage(MENU_ICM_ITEM_YELLOW);
            return;

        //-------------- Cyan ---------------
        case MENU_ICM_SUB_C_HUE:
            ucOsdState   = MENU_ICM_C_HUE_ADJ;
            ucTemp       = 1;
            break;

        case MENU_ICM_SUB_C_SAT:
            ucOsdState   = MENU_ICM_C_SAT_ADJ;
            ucTemp       = 3;
            break;

        case MENU_ICM_SUB_C_CLOSE:
            CExitToICMPage(MENU_ICM_ITEM_CYAN);
            return;

        //------------- Magenta --------------
        case MENU_ICM_SUB_M_HUE:
            ucOsdState   = MENU_ICM_M_HUE_ADJ;
            ucTemp       = 1;
            break;

        case MENU_ICM_SUB_M_SAT:
            ucOsdState   = MENU_ICM_M_SAT_ADJ;
            ucTemp       = 3;
            break;

        case MENU_ICM_SUB_M_CLOSE:
            CExitToICMPage(MENU_ICM_ITEM_MAGENTA);
            return;
    }

    CShowVColorSelectSubItemWindow(ucTemp); 
}

//----------------------------------------------------------------------------------------------------
void MICMSubRGBItemAdjLR(BYTE LR)
{
    BYTE ucTemp = 0;

    if(LR)
    {
        switch(ucOsdState)
        {
            case MENU_ICM_SUB_R_HUE:           ucOsdState = MENU_ICM_SUB_R_SAT;     break;
            case MENU_ICM_SUB_R_SAT:           ucOsdState = MENU_ICM_SUB_R_CLOSE;   break;
            case MENU_ICM_SUB_R_CLOSE:         ucOsdState = MENU_ICM_SUB_R_HUE;     break;

            case MENU_ICM_SUB_G_HUE:           ucOsdState = MENU_ICM_SUB_G_SAT;     break;
            case MENU_ICM_SUB_G_SAT:           ucOsdState = MENU_ICM_SUB_G_CLOSE;   break;
            case MENU_ICM_SUB_G_CLOSE:         ucOsdState = MENU_ICM_SUB_G_HUE;     break;

            case MENU_ICM_SUB_B_HUE:           ucOsdState = MENU_ICM_SUB_B_SAT;     break;
            case MENU_ICM_SUB_B_SAT:           ucOsdState = MENU_ICM_SUB_B_CLOSE;   break;
            case MENU_ICM_SUB_B_CLOSE:         ucOsdState = MENU_ICM_SUB_B_HUE;     break;

            case MENU_ICM_SUB_Y_HUE:           ucOsdState = MENU_ICM_SUB_Y_SAT;     break;
            case MENU_ICM_SUB_Y_SAT:           ucOsdState = MENU_ICM_SUB_Y_CLOSE;   break;
            case MENU_ICM_SUB_Y_CLOSE:         ucOsdState = MENU_ICM_SUB_Y_HUE;     break;

            case MENU_ICM_SUB_C_HUE:           ucOsdState = MENU_ICM_SUB_C_SAT;     break;
            case MENU_ICM_SUB_C_SAT:           ucOsdState = MENU_ICM_SUB_C_CLOSE;   break;
            case MENU_ICM_SUB_C_CLOSE:         ucOsdState = MENU_ICM_SUB_C_HUE;     break;

            case MENU_ICM_SUB_M_HUE:           ucOsdState = MENU_ICM_SUB_M_SAT;     break;
            case MENU_ICM_SUB_M_SAT:           ucOsdState = MENU_ICM_SUB_M_CLOSE;   break;
            case MENU_ICM_SUB_M_CLOSE:         ucOsdState = MENU_ICM_SUB_M_HUE;     break;
        }
    }
    else
    {
        switch(ucOsdState)
        {
            case MENU_ICM_SUB_R_HUE:           ucOsdState = MENU_ICM_SUB_R_CLOSE;   break;
            case MENU_ICM_SUB_R_SAT:           ucOsdState = MENU_ICM_SUB_R_HUE;     break;
            case MENU_ICM_SUB_R_CLOSE:         ucOsdState = MENU_ICM_SUB_R_SAT;     break;

            case MENU_ICM_SUB_G_HUE:           ucOsdState = MENU_ICM_SUB_G_CLOSE;   break;
            case MENU_ICM_SUB_G_SAT:           ucOsdState = MENU_ICM_SUB_G_HUE;     break;
            case MENU_ICM_SUB_G_CLOSE:         ucOsdState = MENU_ICM_SUB_G_SAT;     break;

            case MENU_ICM_SUB_B_HUE:           ucOsdState = MENU_ICM_SUB_B_CLOSE;   break;
            case MENU_ICM_SUB_B_SAT:           ucOsdState = MENU_ICM_SUB_B_HUE;     break;
            case MENU_ICM_SUB_B_CLOSE:         ucOsdState = MENU_ICM_SUB_B_SAT;     break;

            case MENU_ICM_SUB_Y_HUE:           ucOsdState = MENU_ICM_SUB_Y_CLOSE;   break;
            case MENU_ICM_SUB_Y_SAT:           ucOsdState = MENU_ICM_SUB_Y_HUE;     break;
            case MENU_ICM_SUB_Y_CLOSE:         ucOsdState = MENU_ICM_SUB_Y_SAT;     break;

            case MENU_ICM_SUB_C_HUE:           ucOsdState = MENU_ICM_SUB_C_CLOSE;   break;
            case MENU_ICM_SUB_C_SAT:           ucOsdState = MENU_ICM_SUB_C_HUE;     break;
            case MENU_ICM_SUB_C_CLOSE:         ucOsdState = MENU_ICM_SUB_C_SAT;     break;

            case MENU_ICM_SUB_M_HUE:           ucOsdState = MENU_ICM_SUB_M_CLOSE;   break;
            case MENU_ICM_SUB_M_SAT:           ucOsdState = MENU_ICM_SUB_M_HUE;     break;
            case MENU_ICM_SUB_M_CLOSE:         ucOsdState = MENU_ICM_SUB_M_SAT;     break;
        }
    }
    
    switch(ucOsdState)
    {      
        case MENU_ICM_SUB_R_HUE:
        case MENU_ICM_SUB_G_HUE:
        case MENU_ICM_SUB_B_HUE:
        case MENU_ICM_SUB_Y_HUE:
        case MENU_ICM_SUB_C_HUE:
        case MENU_ICM_SUB_M_HUE:
            ucTemp = 1;      
            break;

        case MENU_ICM_SUB_R_SAT:
        case MENU_ICM_SUB_G_SAT:
        case MENU_ICM_SUB_B_SAT:
        case MENU_ICM_SUB_Y_SAT:
        case MENU_ICM_SUB_C_SAT:
        case MENU_ICM_SUB_M_SAT:
            ucTemp = 3;      
            break;

        case MENU_ICM_SUB_R_CLOSE:
        case MENU_ICM_SUB_G_CLOSE:
        case MENU_ICM_SUB_B_CLOSE:
        case MENU_ICM_SUB_Y_CLOSE:
        case MENU_ICM_SUB_C_CLOSE:
        case MENU_ICM_SUB_M_CLOSE:
            ucTemp = 5;      
            break;
    }   
    
    CShowVColorSubItemWindow(ucTemp);
}

//----------------------------------------------------------------------------------------------------
// ICM R/G/B color item page
//----------------------------------------------------------------------------------------------------
void MICMSubRGBColorAdjProc(void)
{
    switch(ucKeyMessage)
    {
        // Move item
#if(_USE_UD_LR_KEY_MSG)
        case VK_F_UP:
        case VK_F_DOWN:
            MICMSubRGBColorAdjMenu();
            COsdProc();
            break;
#endif

        // Exit item
#if(_MENU_FUNC == _MENU_EXIT_ITEM)
        case VK_ENTER: 
#endif
        case VK_MENU:        MICMSubRGBColorAdjMenu();     break;

        // Adjust
#if(_USE_UD_LR_KEY_MSG)
        case VK_F_LEFT:
#endif
        case VK_LEFT:        MICMSubRGBColorAdjLR(1);      break;

        // Adjust
#if(_USE_UD_LR_KEY_MSG)
        case VK_F_RIGHT:
#endif
        case VK_RIGHT:       MICMSubRGBColorAdjLR(0);      break;
            
        // Other key
        default:             COthterKeyAction();           break;
    }
}
//----------------------------------------------------------------------------------------------------

void CExitAdjState(const BYTE ucSubItem, const BYTE ucBarPos)
{
    ucOsdState = ucSubItem;
    CShowVColorSubItemWindow(ucBarPos); 
}
//----------------------------------------------------------------------------------------------------

void MICMSubRGBColorAdjMenu(void)
{
    CLR_KEYREPEATENABLE();

    switch(ucOsdState)
    {
        case MENU_ICM_R_HUE_ADJ:
            CExitAdjState(MENU_ICM_SUB_R_HUE, 1);
            break;

        case MENU_ICM_R_SAT_ADJ:
            CExitAdjState(MENU_ICM_SUB_R_SAT, 3);
            break;

        case MENU_ICM_G_HUE_ADJ:
            CExitAdjState(MENU_ICM_SUB_G_HUE, 1);
            break;

        case MENU_ICM_G_SAT_ADJ:
            CExitAdjState(MENU_ICM_SUB_G_SAT, 3);
            break;

        case MENU_ICM_B_HUE_ADJ:
            CExitAdjState(MENU_ICM_SUB_B_HUE, 1);
            break;

        case MENU_ICM_B_SAT_ADJ:
            CExitAdjState(MENU_ICM_SUB_B_SAT, 3);
            break;

        case MENU_ICM_Y_HUE_ADJ:
            CExitAdjState(MENU_ICM_SUB_Y_HUE, 1);
            break;

        case MENU_ICM_Y_SAT_ADJ:
            CExitAdjState(MENU_ICM_SUB_Y_SAT, 3);
            break;

        case MENU_ICM_C_HUE_ADJ:
            CExitAdjState(MENU_ICM_SUB_C_HUE, 1);
            break;

        case MENU_ICM_C_SAT_ADJ:
            CExitAdjState(MENU_ICM_SUB_C_SAT, 3);
            break;

        case MENU_ICM_M_HUE_ADJ:
            CExitAdjState(MENU_ICM_SUB_M_HUE, 1);
            break;

        case MENU_ICM_M_SAT_ADJ:
            CExitAdjState(MENU_ICM_SUB_M_SAT, 3);
            break;
    }
}
//----------------------------------------------------------------------------------------------------

void MICMSubRGBColorAdjLR(BYTE LR)
{             
    BYTE ucAdjResult = 0;
    BYTE ucAdjMode   = 0;
    BYTE ucShowPos   = 0;

    SET_KEYREPEATENABLE();

    switch(ucOsdState)
    {
    case MENU_ICM_R_HUE_ADJ:
        stOsdUserData.MZICMRedHue = ValueInRangeChange(_MZ_ICM_RED_HUE_MIN, _MZ_ICM_RED_HUE_MAX, stOsdUserData.MZICMRedHue, LR, 0);
        ucAdjMode   = _V_RED;
        ucAdjResult = stOsdUserData.MZICMRedHue;
        break;

    case MENU_ICM_R_SAT_ADJ:
        stOsdUserData.MZICMRedSat = ValueInRangeChange(_MZ_ICM_RED_SAT_MIN, _MZ_ICM_RED_SAT_MAX, stOsdUserData.MZICMRedSat, LR, 0);
        ucAdjMode   = _V_RED;
        ucAdjResult = stOsdUserData.MZICMRedSat;
        ucShowPos   = 1;
        break;

    case MENU_ICM_G_HUE_ADJ:
        stOsdUserData.MZICMGreenHue = ValueInRangeChange(_MZ_ICM_GREEN_HUE_MIN, _MZ_ICM_GREEN_HUE_MAX, stOsdUserData.MZICMGreenHue, LR, 0);
        ucAdjMode   = _V_GREEN;
        ucAdjResult = stOsdUserData.MZICMGreenHue;
        break;

    case MENU_ICM_G_SAT_ADJ:
        stOsdUserData.MZICMGreenSat = ValueInRangeChange(_MZ_ICM_GREEN_SAT_MIN, _MZ_ICM_GREEN_SAT_MAX, stOsdUserData.MZICMGreenSat, LR, 0);
        ucAdjMode   = _V_GREEN;
        ucAdjResult = stOsdUserData.MZICMGreenSat;
        ucShowPos   = 1;
        break;

    case MENU_ICM_B_HUE_ADJ:
        stOsdUserData.MZICMBlueHue = ValueInRangeChange(_MZ_ICM_BLUE_HUE_MIN, _MZ_ICM_BLUE_HUE_MAX, stOsdUserData.MZICMBlueHue, LR, 0);
        ucAdjMode   = _V_BLUE;
        ucAdjResult = stOsdUserData.MZICMBlueHue;
        break;

    case MENU_ICM_B_SAT_ADJ:
        stOsdUserData.MZICMBlueSat = ValueInRangeChange(_MZ_ICM_BLUE_SAT_MIN, _MZ_ICM_BLUE_SAT_MAX, stOsdUserData.MZICMBlueSat, LR, 0);
        ucAdjMode   = _V_BLUE;
        ucAdjResult = stOsdUserData.MZICMBlueSat;
        ucShowPos   = 1;
        break;

    case MENU_ICM_Y_HUE_ADJ:
        stOsdUserData.MZICMYellowHue = ValueInRangeChange(_MZ_ICM_YELLOW_HUE_MIN, _MZ_ICM_YELLOW_HUE_MAX, stOsdUserData.MZICMYellowHue, LR, 0);
        ucAdjMode   = _V_YELLOW;
        ucAdjResult = stOsdUserData.MZICMYellowHue;
        break;

    case MENU_ICM_Y_SAT_ADJ:
        stOsdUserData.MZICMYellowSat = ValueInRangeChange(_MZ_ICM_RED_SAT_MIN, _MZ_ICM_RED_SAT_MAX, stOsdUserData.MZICMYellowSat, LR, 0);
        ucAdjMode   = _V_YELLOW;
        ucAdjResult = stOsdUserData.MZICMYellowSat;
        ucShowPos   = 1;
        break;

    case MENU_ICM_C_HUE_ADJ:
        stOsdUserData.MZICMCyanHue = ValueInRangeChange(_MZ_ICM_CYAN_HUE_MIN, _MZ_ICM_CYAN_HUE_MAX, stOsdUserData.MZICMCyanHue, LR, 0);
        ucAdjMode   = _V_CYAN;
        ucAdjResult = stOsdUserData.MZICMCyanHue;
        break;

    case MENU_ICM_C_SAT_ADJ:
        stOsdUserData.MZICMCyanSat = ValueInRangeChange(_MZ_ICM_CYAN_SAT_MIN, _MZ_ICM_CYAN_SAT_MAX, stOsdUserData.MZICMCyanSat, LR, 0);
        ucAdjMode   = _V_CYAN;
        ucAdjResult = stOsdUserData.MZICMCyanSat;
        ucShowPos   = 1;
        break;

    case MENU_ICM_M_HUE_ADJ:
        stOsdUserData.MZICMMagentaHue = ValueInRangeChange(_MZ_ICM_MAGENTA_HUE_MIN, _MZ_ICM_MAGENTA_HUE_MAX, stOsdUserData.MZICMMagentaHue, LR, 0);
        ucAdjMode   = _V_MAGENTA;
        ucAdjResult = stOsdUserData.MZICMMagentaHue;
        break;

    case MENU_ICM_M_SAT_ADJ:
        stOsdUserData.MZICMMagentaSat = ValueInRangeChange(_MZ_ICM_MAGENTA_SAT_MIN, _MZ_ICM_MAGENTA_SAT_MAX, stOsdUserData.MZICMMagentaSat, LR, 0);
        ucAdjMode   = _V_MAGENTA;
        ucAdjResult = stOsdUserData.MZICMMagentaSat;
        ucShowPos   = 1;
        break;
    } 
 
    CAdjustMZHueSat(ucAdjMode);

    if (0 == ucShowPos)  // Adj HUE
    {
        Gotoxy(11, 2, BYTE_DISPLAY);         
        CShowNumber(ucAdjResult, 0);
        OutputChar(' ');
    }
    else
    {
        Gotoxy(14, 4, BYTE_DISPLAY);         
        CShowNumber(ucAdjResult, 0);
        OutputChar(' ');
    }

    ucOsdEventMsg = _SAVE_EE_OSDUSERDATA_MSG;
}

//----------------------------------------------------------------------------------------------------
// DCC Color adj proc
//----------------------------------------------------------------------------------------------------
void MDCCColorAdjProc(void)
{
    switch(ucKeyMessage)
    {
        // Select item
#if(_USE_UD_LR_KEY_MSG)
        case VK_F_LEFT:
        case VK_F_RIGHT:
#endif
        case VK_MENU:        MDCCColorAdjMenu();       break;

        // Move item
#if(_USE_UD_LR_KEY_MSG)
        case VK_F_UP:
#endif
        case VK_LEFT:        MDCCColorAdjLR(1);        break;

        // Move item
#if(_USE_UD_LR_KEY_MSG)
        case VK_F_DOWN:
#endif
        case VK_RIGHT:       MDCCColorAdjLR(0);        break;

        // Exit item
#if(_MENU_FUNC == _MENU_EXIT_ITEM)
        case VK_ENTER:
            CDrawVividColorSubPage();
            ucOsdState = MENU_USER_ITEM_COLOR;  
            CShowVColorSubItemWindow(_FIRST_ITEM+4);
            break;
#endif
            
        // Other key
        default:             COthterKeyAction();         break;
    }
}

//----------------------------------------------------------------------------------------------------
void MDCCColorAdjMenu(void)
{
    switch(ucOsdState)
    {      
        case MENU_COLOR_ITEM_BRIGHTNESS:
            ucOsdState = MENU_COLOR_ITEM_BRIGHT_ADJ;
            break;

        case MENU_COLOR_ITEM_CONTRAST:
            ucOsdState = MENU_COLOR_ITEM_CON_ADJ;
            break;

        case MENU_COLOR_ITEM_PEAKING:
            ucOsdState = MENU_COLOR_ITEM_PEAK_ADJ;
            break;

        case MENU_COLOR_ITEM_CLOSE:
            CDrawVividColorSubPage();
            ucOsdState = MENU_USER_ITEM_COLOR;  
            CShowVColorSubItemWindow(_FIRST_ITEM+4);
            return;
    }  

    CShowVColorSelectSubItemWindow((ucOsdState - MENU_COLOR_ITEM_BRIGHT_ADJ)*2);
}

//----------------------------------------------------------------------------------------------------
void MDCCColorAdjLR(BYTE  LR)
{   
    ucOsdState = ValueInRangeChange(MENU_COLOR_ITEM_BRIGHTNESS, MENU_COLOR_ITEM_CLOSE, ucOsdState, LR, 1);

    CShowVColorSubItemWindow((ucOsdState - MENU_COLOR_ITEM_BRIGHTNESS)*2);
}

//----------------------------------------------------------------------------------------------------
// Vivid color bright/contrast adj proc
//----------------------------------------------------------------------------------------------------
void MDCCColorBCAdjProc(void)
{
    switch(ucKeyMessage)
    {
        // Move item
#if(_USE_UD_LR_KEY_MSG)
        case VK_F_UP:
        case VK_F_DOWN:
            MDCCColorBCAdjMenu();
            COsdProc();
            break;
#endif

        // Exit item
#if(_MENU_FUNC == _MENU_EXIT_ITEM)
        case VK_ENTER: 
#endif
        case VK_MENU:        MDCCColorBCAdjMenu();       break;

        // Adjust
#if(_USE_UD_LR_KEY_MSG)
        case VK_F_LEFT:
#endif
        case VK_LEFT:        MDCCColorBCAdjLR(1);        break;

        // Adjust
#if(_USE_UD_LR_KEY_MSG)
        case VK_F_RIGHT:
#endif
        case VK_RIGHT:       MDCCColorBCAdjLR(0);        break;
           
        // Other key
        default:             COthterKeyAction();         break;
    }
}

//----------------------------------------------------------------------------------------------------
void MDCCColorBCAdjMenu(void)
{
    CLR_KEYREPEATENABLE();

    switch(ucOsdState)
    {
        case MENU_COLOR_ITEM_BRIGHT_ADJ:   CExitAdjState(MENU_COLOR_ITEM_BRIGHTNESS, 0);  break;
        case MENU_COLOR_ITEM_CON_ADJ:      CExitAdjState(MENU_COLOR_ITEM_CONTRAST, 2);    break;
        case MENU_COLOR_ITEM_PEAK_ADJ:     CExitAdjState(MENU_COLOR_ITEM_PEAKING, 4);     break;
    }
}

//----------------------------------------------------------------------------------------------------
void MDCCColorBCAdjLR(BYTE  LR)
{    
    SET_KEYREPEATENABLE();

    switch(ucOsdState)
    {
        case MENU_COLOR_ITEM_BRIGHT_ADJ:
            stOsdUserData.MZBright = ValueInRangeChange(0, 255, stOsdUserData.MZBright, LR, 0);
            CAdjustHLWindowBrightness(stOsdUserData.MZBright);

            Gotoxy(13, 1, BYTE_DISPLAY);         
            CShowNumber(stOsdUserData.MZBright, 0);
            OutputChar(' ');
            break;

        case MENU_COLOR_ITEM_CON_ADJ:
            stOsdUserData.MZContrast = ValueInRangeChange(0, 255, stOsdUserData.MZContrast, LR, 0);
            CAdjustHLWindowContrast(stOsdUserData.MZContrast);

            Gotoxy(12, 3, BYTE_DISPLAY);         
            CShowNumber(stOsdUserData.MZContrast, 0);
            OutputChar(' ');
            break;

        case MENU_COLOR_ITEM_PEAK_ADJ:
            stOsdUserData.MZPeaking = ValueInRangeChange(_MZ_COLOR_PEAKING_MIN, _MZ_COLOR_PEAKING_MAX, stOsdUserData.MZPeaking, LR, 0);
            CAdjustHLWindowPeaking(stOsdUserData.MZPeaking);

            Gotoxy(12, 5, BYTE_DISPLAY);         
            CShowNumber(stOsdUserData.MZPeaking, 0);
            OutputChar(' ');
            break;
    }      

    ucOsdEventMsg = _SAVE_EE_OSDUSERDATA_MSG;
}

#endif

//----------------------------------------------------------------------------------------------------
//   Other Sub item
void MOtherSubItemProc(void)
{
    switch(ucKeyMessage)
    {
        // Select item
#if(_USE_UD_LR_KEY_MSG)
        case VK_F_LEFT:
        case VK_F_RIGHT:
#endif
#if(_KEY_TYPE_OSD007==_7KEY_SUPPORT)
        case VK_RIGHT:        
        case VK_LEFT:     
#else
        case VK_MENU:       
#endif
        case VK_IR_OK:       
			MOtherSubItemMenu();               break;

        // Move item
#if(_USE_UD_LR_KEY_MSG)
        case VK_F_UP:
#endif
#if(_KEY_TYPE_OSD007!=_7KEY_SUPPORT)
        case VK_RIGHT:        
#endif
			MOtherSubItemLR(1);                break;

        // Move item
#if(_USE_UD_LR_KEY_MSG)
        case VK_F_DOWN:
#endif
#if(_KEY_TYPE_OSD007!=_7KEY_SUPPORT)
        case VK_LEFT:     
#endif
			MOtherSubItemLR(0);                break;

        // Exit item
#if(_MENU_FUNC == _MENU_EXIT_ITEM)
        case VK_ENTER:       
#endif
#if(_KEY_TYPE_OSD007 == _7KEY_SUPPORT)
        case VK_MENU:  
#endif			
        case VK_AUTO:
        case VK_IR_EXIT:
            CExitToMainItem(MENU_MAIN_OTHER);  break;
        // Other key
        default:             COthterKeyAction();                break;
    }
}

//----------------------------------------------------------------------------------------------------
void MOtherSubItemMenu(void)
{
    CClearMsg(_CLEAR_MSG_ONLY);
    CSetItemWindowState(_SELECT_SUB_WINDOW, _SELECT_STATE);

    switch(ucOsdState)
    {
        case MENU_SUB_RESET:
            DoReset();
            if (_SOURCE_VGA == _GET_INPUT_SOURCE())
            {
               // CAutoDoWhiteBalance();
                CAutoDoAutoConfig();
            }

            CSetItemWindowState(_SELECT_SUB_WINDOW, _MOVE_STATE);
            ShowMode();
            
            
            break;

#if(_BLUE_BACKGROUND_FUNC == _ENABLE)
        case MENU_SUB_BLUE: 
            CenterTextout((BYTE *)sOn_Off[_GET_BLUE_BACKGROUND()][GET_LANGUAGE], 14, _MESSAGE_V_POSITION);
            ucOsdState = MENU_BLUE_ADJ;     
            break;
#endif

#if(_AUTO_POWER_DOWN)
        case MENU_SUB_AUTO_POWER:
            {
                BYTE ucTemp = _GET_POWER_DOWN_TIME();
    
                if (0 == ucTemp) // Auto power down time off
                   CenterTextout((BYTE *)sOn_Off[0][GET_LANGUAGE], 14, _MESSAGE_V_POSITION);
                else
                {
                   Gotoxy(13, _MESSAGE_V_POSITION, BYTE_DISPLAY);
                   CShowNumber((ucTemp * 15), 0);    
                }
            }
            ucOsdState = MENU_AUTO_POWER_DOWN_ADJ;     
            break;
#endif

#if(_IMAGE_COLOR_MODE)
        case MENU_SUB_COLOR_MODE: 
            CDrawColorModeState(_GET_IMAGE_COLOR_MODE());
            ucOsdState = MENU_COLOR_MODE_ADJ;     
            break;
#endif

#if(_SHARPNESS_ADJ)
        case MENU_SUB_SHARP:
            Gotoxy(13, _MESSAGE_V_POSITION, BYTE_DISPLAY);
#if(_VIDEO_SUPPORT)  // Source video
            if (_GET_INPUT_SOURCE() != _SOURCE_VGA   && 
                _GET_INPUT_SOURCE() != _SOURCE_DVI   && 
                _GET_INPUT_SOURCE() != _SOURCE_YPBPR &&
                _GET_INPUT_SOURCE() != _SOURCE_HDMI)
                CShowNumber(_GET_VIDEO_SHARP(), 0);    
            else
#endif   
            CShowNumber(GET_SHARPNESS(), 0);    
            ucOsdState = MENU_SHARP_ADJ;
            break;
#endif

        case MENU_SUB_OTHER_CLOSE:
            CExitToMainItem(MENU_MAIN_OTHER);
            break;
    }
}

//----------------------------------------------------------------------------------------------------
bit bOtherItemSupport(BYTE ucOSDItem)
{
    switch(ucOSDItem)
    {
        case MENU_SUB_RESET:  
        case MENU_SUB_OTHER_CLOSE:
            return 1;
/*	for close blue adjust by chenlinfu 2007/09/28
#if(_BLUE_BACKGROUND_FUNC == _ENABLE)
        case MENU_SUB_BLUE: 
            return 1;
#endif
*/
#if(_AUTO_POWER_DOWN)
        case MENU_SUB_AUTO_POWER:
            return 1;
#endif

#if(_IMAGE_COLOR_MODE)
        case MENU_SUB_COLOR_MODE:
            return 1;
#endif

#if(_SHARPNESS_ADJ)
        case MENU_SUB_SHARP:
            return 1;
#endif
    }

    return 0;
}

//----------------------------------------------------------------------------------------------------
void MOtherSubItemLR(BYTE LR)
{
    BYTE ucTemp  = 0;
    BYTE ucItem  = 0;
    
    // Search next item
    while(1)
    {
        ucOsdState = ValueInRangeChange(MENU_SUB_RESET, MENU_SUB_OTHER_CLOSE, ucOsdState, LR, 1);

        if (bOtherItemSupport(ucOsdState))
            break; 
    }

    // Search item position
    ucTemp = MENU_SUB_RESET;
    while(1)
    {
        if (ucOsdState == ucTemp)
           break;

        ucTemp = ValueInRangeChange(MENU_SUB_RESET, MENU_SUB_OTHER_CLOSE,ucTemp, 1, 1);

        if (bOtherItemSupport(ucTemp))
           ucItem++;

    }

    CGotoNextSubItem(ucItem);
}

//--------- Color mode proc ----------------------------------
#if(_IMAGE_COLOR_MODE)
void MColorModeAdjProc(void)
{             
    switch(ucKeyMessage)
    {
        // Move item
#if(_USE_UD_LR_KEY_MSG)
        case VK_F_UP:
        case VK_F_DOWN:
            MColorModeAdjMenu();
            COsdProc();
            break;
#endif

        // Exit item
#if(_MENU_FUNC == _MENU_EXIT_ITEM)
        case VK_ENTER: 
#endif
        case VK_AUTO:
        case VK_MENU:        MColorModeAdjMenu();       break;

        // Adjust
#if(_USE_UD_LR_KEY_MSG)
        case VK_F_LEFT:
#endif
        case VK_LEFT:        MColorModeAdjLR(1);        break;

        // Adjust
#if(_USE_UD_LR_KEY_MSG)
        case VK_F_RIGHT:
#endif
        case VK_RIGHT:       MColorModeAdjLR(0);        break;
           
        // Other key
        default:             COthterKeyAction();        break;
    }
}
//----------------------------------------------------------------------------------------------------
void MColorModeAdjMenu(void)
{
    ucOsdState = MENU_SUB_COLOR_MODE;
    CClearMsg(_CLEAR_AND_EXIT_SUB_ITEM);
}

//----------------------------------------------------------------------------------------------------
void MColorModeAdjLR(BYTE LR)
{
    BYTE ucTemp = _GET_IMAGE_COLOR_MODE();

    ucTemp = ValueInRangeChange(0, 3, ucTemp, LR, 1);
    _SET_IMAGE_COLOR_MODE(ucTemp);
    CSetColorMode(ucTemp);

    CClearMsg(_CLEAR_MSG_ONLY);
    CDrawColorModeState(ucTemp);
   
    ucOsdEventMsg = _SAVE_EE_OSDUSERDATA_MSG;
}

//----------------------------------------------------------------------------------------------------
void CDrawColorModeState(BYTE ucColorModeState)
{
    BYTE ucPosH = 14;
    BYTE ucPosV = _MESSAGE_V_POSITION;

    if (MENU_IMAGE_ADJ == ucOsdState)
    {
        ucPosH = 0;
        ucPosV = 0;
    	}
    switch(ucColorModeState)
    {
        case 0:  // Subdued
            CenterTextout((BYTE *)sColorMode0[GET_LANGUAGE], ucPosH, ucPosV);
            break;

        case 1:  // Lightful
            CenterTextout((BYTE *)sColorMode1[GET_LANGUAGE], ucPosH, ucPosV);
            break;

        case 2:  // Standard
            CenterTextout((BYTE *)sColorMode2[GET_LANGUAGE], ucPosH, ucPosV);
            break;

        case 3:  // User
            CenterTextout((BYTE *)sColorMode3[GET_LANGUAGE], ucPosH, ucPosV);
            break;

        case 4:
            CenterTextout((BYTE *)sColorMode4[GET_LANGUAGE], ucPosH, ucPosV);
            break;

        case 5:
            CenterTextout((BYTE *)sColorMode5[GET_LANGUAGE], ucPosH, ucPosV);
            break;
    }
}

//----------------------------------------------------------------------------------------------------
void CSetColorMode(BYTE ucMode)
{
    switch(ucMode)
    {
        case 0:
            BRIGHTNESS_GUAGE = 45;
            CONTRAST_GUAGE   = 55;
            SATURATION_GUAGE = 60;
            break;

        case 1:
            BRIGHTNESS_GUAGE = 60;
            CONTRAST_GUAGE   = 60;
            SATURATION_GUAGE = 60;
            break;

        case 2:
            BRIGHTNESS_GUAGE = 50;
            CONTRAST_GUAGE   = 50;
            SATURATION_GUAGE = 50;
            break;

        case 3:
            CEepromLoadBriConData();
            CEepromLoadVedioColor();
            break;

        case 4:
            break;

        case 5:
            break;
    }
    CAdjustBrightness();
    CAdjustContrast();
    gmi_CAdjustVDCSaturation(stConBriData.Saturation);
}
void CGotoAdjImage(void)
{                 
    COsdFxDisableOsd();
    SetOSDRamAddress(ROW_COUNT,COL_WIDTH,FONT_BASE_ADDRESS);
    SetRowCmds(ROW_COUNT,COL_WIDTH);
    COsdFxCodeWrite(ucCloseAllWindow);
    SetRowCmds(ROW_COUNT,COL_WIDTH);

     SetOSDDouble(0x03  | OSD_WINDOWCHAR_BLENDING);   

     if (_GET_OSD_SIZE()) 
        OSDPosition(_OSD_DOUBLE_WIDTH(220), _OSD_DOUBLE_HEIGHT(54), _LIFT_UP_H_OFFSET, 1, 0x03);
      else
       OSDPosition(220, 54, _LIFT_UP_H_OFFSET, 1, 0x03);

    CClearWindow(0x20);

#if(_AUTO_POWER_DOWN)
    bTimerOnScreen = 0;
#endif

    ucOsdState = MENU_IMAGE_ADJ;

    CDrawColorModeState(_GET_IMAGE_COLOR_MODE());

    COsdFxEnableOsd();
}
//----------------------------------------------------------------------------------------------------
void MImageAdj(void)
{
    switch(ucKeyMessage)
    {
        case _IR_IMAGE_KEY_MESSAGE:
            OSDClear(0, 1, 1, COL_WIDTH - 2, 0x00, BYTE_DISPLAY);
            MColorModeAdjLR(1);
            break;

        default:
            COthterKeyAction();
            break;
    }
}
//----------------------------------------------------------------------------------------------------

#endif

//--------- Sharp adj proc ----------------------------------
#if(_SHARPNESS_ADJ)
void MSharpAdjProc(void)
{             
    switch(ucKeyMessage)
    {
        // Move item
#if(_USE_UD_LR_KEY_MSG)
        case VK_F_UP:
        case VK_F_DOWN:
            MSharpAdjMenu();
            COsdProc();
            break;
#endif

        // Exit item
#if(_MENU_FUNC == _MENU_EXIT_ITEM)
        case VK_ENTER: 
#endif
        case VK_AUTO:
        case VK_IR_EXIT:
        case VK_MENU:        MSharpAdjMenu();       break;

        // Adjust
#if(_USE_UD_LR_KEY_MSG)
        case VK_F_LEFT:
#endif
        case VK_LEFT:        
			MSharpAdjLR(1);        break;

        // Adjust
#if(_USE_UD_LR_KEY_MSG)
        case VK_F_RIGHT:
#endif
        case VK_RIGHT:  
			MSharpAdjLR(0);        break;
           
        // Other key
        default:             COthterKeyAction();    break;
    }
}
//----------------------------------------------------------------------------------------------------
void MSharpAdjMenu(void)
{
    ucOsdState = MENU_SUB_SHARP;
    CClearMsg(_CLEAR_AND_EXIT_SUB_ITEM);
}

//----------------------------------------------------------------------------------------------------
void MSharpAdjLR(BYTE LR)
{
    BYTE ucTemp = GET_SHARPNESS(); // Default to VGA sharpness
    BYTE ucMax  = 4;

#if(_VIDEO_SUPPORT)  // Source video
    if (_GET_INPUT_SOURCE() != _SOURCE_VGA  && 
        _GET_INPUT_SOURCE() != _SOURCE_DVI  && 
        _GET_INPUT_SOURCE() != _SOURCE_HDMI && 
        _GET_INPUT_SOURCE() != _SOURCE_YPBPR)
    {
        ucTemp = _GET_VIDEO_SHARP();
        ucMax  = 63;
    }
else
#endif   
    {
        ucTemp = GET_SHARPNESS();
        ucMax  = 4;
    }
if(ucTemp>ucMax)
	ucTemp=ucMax;
    ucTemp = ValueInRangeChange(0, ucMax, ucTemp, LR, 0);

    CClearMsg(_CLEAR_MSG_ONLY);

    Gotoxy(13, _MESSAGE_V_POSITION, BYTE_DISPLAY);
#if(_VIDEO_SUPPORT)  // Source video
    if (_GET_INPUT_SOURCE() != _SOURCE_VGA  && 
        _GET_INPUT_SOURCE() != _SOURCE_DVI  && 
        _GET_INPUT_SOURCE() != _SOURCE_HDMI && 
        _GET_INPUT_SOURCE() != _SOURCE_YPBPR)
    {
        _SET_VIDEO_SHARP(ucTemp);
        CShowNumber(_GET_VIDEO_SHARP(), 0);    
        CAdjustVideoSharp();
        ucOsdEventMsg = _SAVE_EE_VEDIOCOLOR_MSG;
    }
    else
#endif
    {   // VGA/DVI/HDMI/YPBPR sharpness
        SET_SHARPNESS(ucTemp);
        CShowNumber(GET_SHARPNESS(), 0); 
        CAdjustSharpness();
        ucOsdEventMsg = _SAVE_EE_SYSTEMDATA_MSG;  
    }
   
}

#endif

//----------------------------------------------------------------------------------------------------
#if(_IR_ENABLE)        
void DrawMuteState(void)
{
    COsdFxDisableOsd();
    SetOSDRamAddress(ROW_COUNT,COL_WIDTH,FONT_BASE_ADDRESS);
    SetRowCmds(ROW_COUNT,COL_WIDTH);
    COsdFxCodeWrite(ucCloseAllWindow);
    CClearWindow(0x20);

    SetOSDDouble(OSD_DOUBLE_WIDTH_ENABLE| OSD_DOUBLE_HEIGHT_ENABLE);   
     //if (_GET_OSD_SIZE()) 
      //  OSDPosition(_OSD_DOUBLE_WIDTH(55), _OSD_DOUBLE_HEIGHT(30), _RIGHT_UP_OSD_H_OFFSET, 1, 0x03);
      //else
       OSDPosition(55, 30, _RIGHT_UP_OSD_H_OFFSET, 1, 0x03);


#if(_AUTO_POWER_DOWN)
    bTimerOnScreen = 0;
#endif

    if (GET_MUTE_STATE() == STATE_MUTEON)
    {
#if(_HARDWARE_LOAD_FONT == _ON)

        CScalerLoadHardwareVLCFont(tFntIconMute, 0x10);

#else

        CScalerLoadFont(tFntIconMute, 0x10, 6, _COMPRESS_FONT);

#endif
        CTimerCancelTimerEvent(COsdDispOsdTimerEvent);
        ucOsdState = MENU_SHOW_MUTE_STATE;
    }
    else
    {
#if(_HARDWARE_LOAD_FONT == _ON)

        CScalerLoadHardwareVLCFont(tFntIconSpker, 0x10);

#else

        CScalerLoadFont(tFntIconSpker, 0x10, 6, _COMPRESS_FONT);

#endif
        ucOsdState = MENU_SHOW_MSG_STATE;
        CTimerReactiveTimerEvent(SEC(5),COsdDispOsdTimerEvent);
    }

    DispIcon(1,0,0x10);   

    COsdFxEnableOsd();
}
#endif


//--------- brightness proc ----------------------------------
void MBrightAdjProc(void)
{
    switch(ucKeyMessage)
    {
        // Move item
#if(_USE_UD_LR_KEY_MSG)
        case VK_F_UP:
        case VK_F_DOWN:
            MBrightAdjMenu();
            COsdProc();
            break;
#endif

        // Exit item
#if(_MENU_FUNC == _MENU_EXIT_ITEM)
        case VK_ENTER: 
#endif
        case VK_AUTO:
        case VK_IR_EXIT:
        case VK_MENU:        MBrightAdjMenu();       break;

        // Adjust
#if(_USE_UD_LR_KEY_MSG)
        case VK_F_LEFT:
#endif
        case VK_LEFT:        MBrightAdjLR(1);        break;

        // Adjust
#if(_USE_UD_LR_KEY_MSG)
        case VK_F_RIGHT:
#endif
        case VK_RIGHT:       MBrightAdjLR(0);        break;
            
        // Other key
        default:             COthterKeyAction();     break;
    }
}

//----------------------------------------------------------------------------------------------------
void MBrightAdjMenu(void)
{
    ucOsdState = MENU_ITEM_BRIGHT;
    CClearMsg(_CLEAR_AND_EXIT_SUB_ITEM);
}

//----------------------------------------------------------------------------------------------------
void MBrightAdjLR(BYTE  LR)
{   
    SET_KEYREPEATENABLE();
    BRIGHTNESS_GUAGE = ValueInRangeChange(0, 100, BRIGHTNESS_GUAGE, LR, 0);
    SLIDER1(BRIGHTNESS_GUAGE);
    CAdjustBrightness();
    
    stSystemData.BackLight = BRIGHTNESS_GUAGE;
    CAdjustBacklight();
    CEepromSaveSystemData();
    ucOsdEventMsg = _SAVE_EE_BriConHueSat_MSG;                       
}


//--------- CONTRAST ADJUST PROC ----------------------------------
void MContrastAdjProc(void)
{
    switch(ucKeyMessage)
    {
        // Move item
#if(_USE_UD_LR_KEY_MSG)
        case VK_F_UP:
        case VK_F_DOWN:
            MContrastAdjMenu();
            COsdProc();
            break;
#endif

        // Exit item
#if(_MENU_FUNC == _MENU_EXIT_ITEM)
        case VK_ENTER: 
#endif
        case VK_AUTO:
         case VK_IR_EXIT:
        case VK_MENU:        MContrastAdjMenu();       break;

        // Adjust
#if(_USE_UD_LR_KEY_MSG)
        case VK_F_LEFT:
#endif
        case VK_LEFT:        MContrastAdjLR(1);        break;

        // Adjust
#if(_USE_UD_LR_KEY_MSG)
        case VK_F_RIGHT:
#endif
        case VK_RIGHT:       MContrastAdjLR(0);        break;

        // Other key
        default:             COthterKeyAction();       break;
    }
}

//----------------------------------------------------------------------------------------------------
void MContrastAdjMenu(void)
{
    ucOsdState = MENU_ITEM_CONTRAST;
    CClearMsg(_CLEAR_AND_EXIT_SUB_ITEM);
}

//----------------------------------------------------------------------------------------------------
void MContrastAdjLR(BYTE  LR)
{   
    SET_KEYREPEATENABLE();
    CONTRAST_GUAGE = ValueInRangeChange(0, 100, CONTRAST_GUAGE, LR, 0);
    SLIDER1(CONTRAST_GUAGE);
    CAdjustContrast();
    ucOsdEventMsg = _SAVE_EE_BriConHueSat_MSG;     
}

//--------- LANGUAGE ADJUST PROC ----------------------------------
void MLanguageAdjProc(void)
{
    switch(ucKeyMessage)
    {
        // Move item
#if(_USE_UD_LR_KEY_MSG)
        case VK_F_UP:
        case VK_F_DOWN:
            MLanguageAdjMenu();
            COsdProc();
            break;
#endif

        // Exit item
#if(_MENU_FUNC == _MENU_EXIT_ITEM)
        case VK_ENTER: 
#endif
        case VK_AUTO:
        case VK_IR_EXIT:
        case VK_MENU:        MLanguageAdjMenu();       break;

        // Adjust
#if(_USE_UD_LR_KEY_MSG)
        case VK_F_LEFT:
#endif
        case VK_LEFT:        MLanguageAdjLR(1);        break;

        // Adjust
#if(_USE_UD_LR_KEY_MSG)
        case VK_F_RIGHT:
#endif
        case VK_RIGHT:       MLanguageAdjLR(0);        break;
            
        // Other key
        default:             COthterKeyAction();       break;
    }
}

//----------------------------------------------------------------------------------------------------
void MLanguageAdjMenu(void)
{
    ucOsdState = MENU_SUB_LANGUAGE;
    CClearMsg(_CLEAR_AND_EXIT_SUB_ITEM);        
}

//----------------------------------------------------------------------------------------------------
void MLanguageAdjLR(BYTE  LR)
{
    BYTE ucLng = GET_LANGUAGE;
    
    if (LR) 
        ucLng = GetNextLanguage(ucLng);
    else   
        ucLng = GetPrevLanguage(ucLng);
    
    SET_LANGUAGE(ucLng);
    // Redraw
    CClearSubItem();
    CClearMsg(_CLEAR_MSG_ONLY);
    
    // Load Font
    LoadLanguageFont();
    CDrawOSDFuncPage();
    CenterTextout((BYTE *)sLangName[GET_LANGUAGE], 14, _MESSAGE_V_POSITION);
    ucOsdEventMsg = _SAVE_EE_OSDUSERDATA_MSG;
}
#if(_DISPLAY_SIZE_ADJ)
 //--------- 16:9-4:3 PROC ----------------------------------
void MDispModeAdjProc(void)
{
    switch(ucKeyMessage)
    {
        // Move item
#if(_USE_UD_LR_KEY_MSG)
        case VK_F_UP:
        case VK_F_DOWN:
            MDispModeAdjMenu();
            COsdProc();
            break;
#endif

        // Exit item
#if(_MENU_FUNC == _MENU_EXIT_ITEM)
        case VK_ENTER: 
#endif
        case VK_IR_EXIT:
        case VK_MENU:        MDispModeAdjMenu();       break;

        // Adjust
#if(_USE_UD_LR_KEY_MSG)
        case VK_F_LEFT:
#endif
        case VK_LEFT:        MDispModeAdjLR(1);        break;

        // Adjust
#if(_USE_UD_LR_KEY_MSG)
        case VK_F_RIGHT:
#endif
        case VK_RIGHT:       MDispModeAdjLR(0);        break;

        // Other key
        default:             COthterKeyAction();   break;
    }
}

//----------------------------------------------------------------------------------------------------
void MDispModeAdjMenu(void)
{
    ucOsdState = MENU_SUB_DISMODE;
    CClearMsg(_CLEAR_AND_EXIT_SUB_ITEM);
}

//----------------------------------------------------------------------------------------------------
void MDispModeAdjLR(BYTE LR)
{   
	LR =LR;
    CClearMsg(_CLEAR_AND_SELECT_SUB_ITEM);
	if(_GET_INPUT_SOURCE()==_SOURCE_VIDEO_TV)
           gmi_CI2CWrite9886(ucTVType, _TUNER_MUTE_ON, _NORMAL_MODE);

   if(_GET_DISPLAY_MODE()== DISPLAY_MODE_16_10)
    _SET_DISPLAY_MODE(DISPLAY_MODE_43);
   else    
    _SET_DISPLAY_MODE(DISPLAY_MODE_16_10);
	CEepromSaveOsdUserData();
 	bVideoON = 0;
 	ucVideoNoModeTime = 252;
 	CModeResetMode();   
	if(_GET_INPUT_SOURCE()==_SOURCE_VIDEO_TV)
           gmi_CI2CWrite9886(ucTVType, _TUNER_MUTE_OFF, _NORMAL_MODE);
      CenterTextout((BYTE *)sDisp_mode[_GET_DISPLAY_MODE()], 14, _MESSAGE_V_POSITION);
  //   ucChangeSourceCount = 1;
 //   ucOsdEventMsg       = _DO_SHOW_NOTE;
//    ucCurrState         = _SOURCE_CHANGE_STATE;
    #if(_IR_ENABLE)
     ucDetectIR_Cmd = 0;
    #endif
	 MUTE_ON();
#if(_CHANGE_SOURCE_BACKGROUCD_COLOR==_BACK_COLOR)					    	
		CAdjustBackgroundColor(0x00, 0x00, 0x00);     
#else
		CAdjustBackgroundColor(0x00, 0x00, 0xFF);     
#endif
		CScalerSetBit(_VDISP_CTRL_28, ~(_BIT5), _BIT5);
		COsdFxDisableOsd();
}

#endif
//--------- Volume adjust proc ----------------------------------
void MVolumeAdjProc()
{
    switch(ucKeyMessage)
    {
        // Move item
#if(_USE_UD_LR_KEY_MSG)
        case VK_F_UP:
        case VK_F_DOWN:
            MVolumeAdjMenu();
            if (ucOsdState == MENU_SUB_VOLUME)
               COsdProc();
            break;
#endif

        // Exit item
#if(_MENU_FUNC == _MENU_EXIT_ITEM)
        case VK_ENTER: 
#endif
        case VK_AUTO:
        case VK_IR_EXIT:
        case VK_MENU:        MVolumeAdjMenu();       break;

        // Adjust
#if(_USE_UD_LR_KEY_MSG)
        case VK_F_LEFT:
#endif
#if(_IR_ENABLE)
        case VK_IR_VOLINC:
#endif
        case VK_LEFT:        MVolumeAdjLR(1);        break;

        // Adjust
#if(_USE_UD_LR_KEY_MSG)
        case VK_F_RIGHT:
#endif
#if(_IR_ENABLE)
        case VK_IR_VOLDEC:
#endif
        case VK_RIGHT:       MVolumeAdjLR(0);        break;
            
        // Other key
        default:             COthterKeyAction();     break;
    }
}

//----------------------------------------------------------------------------------------------------
void MVolumeAdjMenu(void)
{
    if (MENU_VOLUME_SP == ucOsdState)
    {
        COsdFxDisableOsd();
        CTimerDelayXms(100);
#if(_IR_ENABLE)        
        ucDetectIR_Cmd = 0;
#endif
    }
    else
    {
        ucOsdState = MENU_SUB_VOLUME;
        CClearMsg(_CLEAR_AND_EXIT_SUB_ITEM);        
    }
}

//----------------------------------------------------------------------------------------------------
void MVolumeAdjLR(BYTE  LR)
{
    SET_MUTE_STATE(STATE_MUTEOFF);
    SET_KEYREPEATENABLE();
    stOsdUserData.Volume = ValueInRangeChange(0,100,stOsdUserData.Volume,LR,0);

    if (MENU_VOLUME_SP == ucOsdState)
       OSDSlider(3, 1, 10, stOsdUserData.Volume, 100, 0x40, _SHOW_PERCENT);
    else
       SLIDER1(stOsdUserData.Volume);
    CSetVolume();
    ucOsdEventMsg = _SAVE_EE_OSDUSERDATA_MSG;
	//add by chenlinfu 2007/10/18
	CTimerReactiveTimerEvent(SEC(stOsdUserData.OsdTimeout),COsdDispOsdTimerEvent);
}

//--------- Mute PROC ----------------------------------
void MMuteAdjProc(void)
{
    switch(ucKeyMessage)
    {
        // Move item
#if(_USE_UD_LR_KEY_MSG)
        case VK_F_UP:
        case VK_F_DOWN:
            MMuteAdjMenu();
            COsdProc();
            break;
#endif

        // Exit item
#if(_MENU_FUNC == _MENU_EXIT_ITEM)
        case VK_ENTER: 
#endif
        case VK_AUTO:
         case VK_IR_EXIT:
        case VK_MENU:        MMuteAdjMenu();       break;

        // Adjust
#if(_USE_UD_LR_KEY_MSG)
        case VK_F_LEFT:
#endif
        case VK_LEFT:        MMuteAdjLR(1);        break;

        // Adjust
#if(_USE_UD_LR_KEY_MSG)
        case VK_F_RIGHT:
#endif
        case VK_RIGHT:       MMuteAdjLR(0);        break;

        // Other key
        default:             COthterKeyAction();   break;
    }
}

//----------------------------------------------------------------------------------------------------
void MMuteAdjMenu(void)
{
    ucOsdState = MENU_SUB_MUTE;
    CClearMsg(_CLEAR_AND_EXIT_SUB_ITEM);
}

//----------------------------------------------------------------------------------------------------
void MMuteAdjLR(BYTE LR)
{   
    CClearMsg(_CLEAR_MSG_ONLY);

    LR = GET_MUTE_STATE();
    
    LR = 1 - LR;
    
    SET_MUTE_STATE(LR);
    CSetVolume();   
    CenterTextout((BYTE *)sOn_Off[LR][GET_LANGUAGE], 14, _MESSAGE_V_POSITION);
    ucOsdEventMsg = _SAVE_EE_OSDUSERDATA_MSG;
}

#if(_SOUND_PROCESSOR == _ENABLE)
//--------- Balance adjust proc ----------------------------------
void MBalanceAdjProc(void)
{
    switch(ucKeyMessage)
    {
        // Move item
#if(_USE_UD_LR_KEY_MSG)
        case VK_F_UP:
        case VK_F_DOWN:
            MBalanceAdjMenu();
            COsdProc();
            break;
#endif

        // Exit item
#if(_MENU_FUNC == _MENU_EXIT_ITEM)
        case VK_ENTER: 
#endif
        case VK_IR_EXIT:
        case VK_MENU:        MBalanceAdjMenu();       break;

        // Adjust
#if(_USE_UD_LR_KEY_MSG)
        case VK_F_LEFT:
#endif
        case VK_LEFT:        MBalanceAdjLR(1);        break;

        // Adjust
#if(_USE_UD_LR_KEY_MSG)
        case VK_F_RIGHT:
#endif
        case VK_RIGHT:       MBalanceAdjLR(0);        break;
            
        // Other key
        default:             COthterKeyAction();      break;
    }
}

//----------------------------------------------------------------------------------------------------
void MBalanceAdjMenu(void)
{
    ucOsdState = MENU_SUB_BALANCE;
    CClearMsg(_CLEAR_AND_EXIT_SUB_ITEM);        
}

//----------------------------------------------------------------------------------------------------
void MBalanceAdjLR(BYTE  LR)
{
    SET_KEYREPEATENABLE();
    stOsdUserData.Balance = ValueInRangeChange(0,100,stOsdUserData.Balance,LR,0);
    SLIDER1(stOsdUserData.Balance);
    CSetVolume();
    ucOsdEventMsg = _SAVE_EE_OSDUSERDATA_MSG;
}

//--------- Bass adjust proc ----------------------------------
void MBassAdjProc(void)
{
    switch(ucKeyMessage)
    {
        // Move item
#if(_USE_UD_LR_KEY_MSG)
        case VK_F_UP:
        case VK_F_DOWN:
            MBassAdjMenu();
            COsdProc();
            break;
#endif

        // Exit item
#if(_MENU_FUNC == _MENU_EXIT_ITEM)
        case VK_ENTER: 
#endif
        case VK_IR_EXIT:
        case VK_MENU:        MBassAdjMenu();       break;

        // Adjust
#if(_USE_UD_LR_KEY_MSG)
        case VK_F_LEFT:
#endif
        case VK_LEFT:        MBassAdjLR(1);        break;

        // Adjust
#if(_USE_UD_LR_KEY_MSG)
        case VK_F_RIGHT:
#endif
        case VK_RIGHT:       MBassAdjLR(0);        break;

        // Other key
        default:             COthterKeyAction();   break;
    }
}

//----------------------------------------------------------------------------------------------------
void MBassAdjMenu(void)
{
    ucOsdState = MENU_SUB_BASS;
    CClearMsg(_CLEAR_AND_EXIT_SUB_ITEM);        
}

//----------------------------------------------------------------------------------------------------
void MBassAdjLR(BYTE  LR)
{
    SET_KEYREPEATENABLE();
    stOsdUserData.Bass = ValueInRangeChange(0,100,stOsdUserData.Bass,LR,0);
    SLIDER1(stOsdUserData.Bass);
    CSetVolume();
    ucOsdEventMsg = _SAVE_EE_OSDUSERDATA_MSG;
}


//--------- Treble adjust proc ----------------------------------
void MTrebleAdjProc(void)
{
    switch(ucKeyMessage)
    {
        // Move item
#if(_USE_UD_LR_KEY_MSG)
        case VK_F_UP:
        case VK_F_DOWN:
            MTrebleAdjMenu();
            COsdProc();
            break;
#endif

        // Exit item
#if(_MENU_FUNC == _MENU_EXIT_ITEM)
        case VK_ENTER: 
#endif
        case VK_IR_EXIT:
        case VK_MENU:        MTrebleAdjMenu();       break;

        // Adjust
#if(_USE_UD_LR_KEY_MSG)
        case VK_F_LEFT:
#endif
        case VK_LEFT:        MTrebleAdjLR(1);        break;

        // Adjust
#if(_USE_UD_LR_KEY_MSG)
        case VK_F_RIGHT:
#endif
        case VK_RIGHT:       MTrebleAdjLR(0);        break;

        // Other key
        default:             COthterKeyAction();     break;
    }
}

//----------------------------------------------------------------------------------------------------
void MTrebleAdjMenu(void)
{
    ucOsdState = MENU_SUB_TREBLE;
    CClearMsg(_CLEAR_AND_EXIT_SUB_ITEM);        
}

//----------------------------------------------------------------------------------------------------
void MTrebleAdjLR(BYTE  LR)
{
    SET_KEYREPEATENABLE();
    stOsdUserData.Treble = ValueInRangeChange(0,100,stOsdUserData.Treble,LR,0);
    SLIDER1(stOsdUserData.Treble);
    CSetVolume();
    ucOsdEventMsg = _SAVE_EE_OSDUSERDATA_MSG;
}

//--------- SRS adjust proc ----------------------------------
void MSRSAdjProc(void)
{
    switch(ucKeyMessage)
    {
        // Move item
#if(_USE_UD_LR_KEY_MSG)
        case VK_F_UP:
        case VK_F_DOWN:
            MSRSAdjMenu();
            COsdProc();
            break;
#endif

        // Exit item
#if(_MENU_FUNC == _MENU_EXIT_ITEM)
        case VK_ENTER: 
#endif
        case VK_IR_EXIT:
        case VK_MENU:        MSRSAdjMenu();       break;

        // Adjust
#if(_USE_UD_LR_KEY_MSG)
        case VK_F_LEFT:
#endif
        case VK_LEFT:        MSRSAdjLR(1);        break;

        // Adjust
#if(_USE_UD_LR_KEY_MSG)
        case VK_F_RIGHT:
#endif
        case VK_RIGHT:       MSRSAdjLR(0);        break;

        // Other key
        default:             COthterKeyAction();  break;
    }
}

//----------------------------------------------------------------------------------------------------
void MSRSAdjMenu(void)
{
    ucOsdState = MENU_SUB_SRS;
    CClearMsg(_CLEAR_AND_EXIT_SUB_ITEM);        
}

//----------------------------------------------------------------------------------------------------
void MSRSAdjLR(BYTE  LR)
{
    SET_KEYREPEATENABLE();
    stOsdUserData.SRS = ValueInRangeChange(0,100,stOsdUserData.SRS,LR,0);
    SLIDER1(stOsdUserData.SRS);
    CSetVolume();
    ucOsdEventMsg = _SAVE_EE_OSDUSERDATA_MSG;
}

//--------- BBE adjust proc ----------------------------------
void MBBEAdjProc(void)
{
    switch(ucKeyMessage)
    {
        // Move item
#if(_USE_UD_LR_KEY_MSG)
        case VK_F_UP:
        case VK_F_DOWN:
            MBBEAdjMenu();
            COsdProc();
            break;
#endif

        // Exit item
#if(_MENU_FUNC == _MENU_EXIT_ITEM)
        case VK_ENTER: 
#endif
         case VK_IR_EXIT:
        case VK_MENU:        MBBEAdjMenu();       break;

        // Adjust
#if(_USE_UD_LR_KEY_MSG)
        case VK_F_LEFT:
#endif
        case VK_LEFT:        MBBEAdjLR(1);        break;

        // Adjust
#if(_USE_UD_LR_KEY_MSG)
        case VK_F_RIGHT:
#endif
        case VK_RIGHT:       MBBEAdjLR(0);        break;

        // Other key
        default:             COthterKeyAction();  break;
    }
}

//----------------------------------------------------------------------------------------------------
void MBBEAdjMenu(void)
{
    ucOsdState = MENU_SUB_BBE;
    CClearMsg(_CLEAR_AND_EXIT_SUB_ITEM);        
}

//----------------------------------------------------------------------------------------------------
void MBBEAdjLR(BYTE  LR)
{
    SET_KEYREPEATENABLE();
    stOsdUserData.BBE = ValueInRangeChange(0,100,stOsdUserData.BBE,LR,0);
    SLIDER1(stOsdUserData.BBE);
    CSetVolume();
    ucOsdEventMsg = _SAVE_EE_OSDUSERDATA_MSG;
}

#endif



#if(_AUTO_POWER_DOWN)
void CGotoAdjSleep(void)
{    
	BYTE i; 
    //CInitOSDMainFrame();
    //SetOSDDouble(OSD_DOUBLE_HEIGHT_ENABLE | OSD_DOUBLE_WIDTH_ENABLE);

    COsdFxDisableOsd();
    SetOSDRamAddress(ROW_COUNT,COL_WIDTH,FONT_BASE_ADDRESS);
    //SetOSDDouble(OSD_DOUBLE_HEIGHT_ENABLE | OSD_DOUBLE_WIDTH_ENABLE);
    SetRowCmds(ROW_COUNT,COL_WIDTH);
    COsdFxCodeWrite(ucCloseAllWindow);
	CClearWindow(0x20);
     if (_GET_OSD_SIZE()) 
        OSDPosition(_OSD_DOUBLE_WIDTH(220), _OSD_DOUBLE_HEIGHT(54), _LIFT_UP_H_OFFSET, 1, 0x03);
      else
       OSDPosition(220, 54, _LIFT_UP_H_OFFSET, 1, 0x03);
	SetOSDDouble(0x03 | OSD_WINDOWCHAR_BLENDING);   
        DirectWOSDRam(0x00, 0x03, THE_BYTE0, 0x80|0x03);  // Row 0~2 character double height and width

    ucOsdState = SLEEP_TIME_ADJ;
    CenterTextout(sSLEEP_TIME, 7, 0);
if(_GET_POWER_DOWN_TIME()!=0)
{		 // Clear item character


	//reset char width to 12 pixel
	Gotoxy(13, 0, BYTE_ATTRIB);
	CScalerSendAddr(_OSD_DATA_PORT_92, _WRITE, _NON_AUTOINC);
	for(i=0;i<3;i++)	
	CScalerSendByte(0x8c);
	CScalerSendWriteStop();
	
	Gotoxy(13, 0, BYTE_DISPLAY);
    CShowNumber((_GET_POWER_DOWN_TIME()*15),0);
}
else
	CenterTextout((BYTE *)sOn_Off[0][GET_LANGUAGE], 14, 0);

    COsdFxEnableOsd();
}
//----------------------------------------------------------------------------------------------------
void MSleepTimeAdj(void)
{
    switch(ucKeyMessage)
    {  
        case VK_IR_SLEEP:
            OSDClear(0, 15, 1, COL_WIDTH, 0x00, BYTE_DISPLAY);
            MAutoPowerDownAdjLR(1);
            break;

        default:
            COthterKeyAction();
            break;
    	}
}
//--------- AutoPowerDown PROC ----------------------------------
void MAutoPowerDownAdjProc(void)
{
    switch(ucKeyMessage)
    {
        // Move item
#if(_USE_UD_LR_KEY_MSG)
        case VK_F_UP:
        case VK_F_DOWN:
            MAutoPowerDownAdjMenu();
            COsdProc();
            break;
#endif

        // Exit item
#if(_MENU_FUNC == _MENU_EXIT_ITEM)
        case VK_ENTER: 
#endif
        case VK_AUTO:
        case VK_IR_EXIT:
        case VK_MENU:        MAutoPowerDownAdjMenu();       break;

        // Adjust
#if(_USE_UD_LR_KEY_MSG)
        case VK_F_LEFT:
#endif
        case VK_LEFT:        MAutoPowerDownAdjLR(1);        break;

        // Adjust
#if(_USE_UD_LR_KEY_MSG)
        case VK_F_RIGHT:
#endif
        case VK_RIGHT:       MAutoPowerDownAdjLR(0);        break;

        // Other key
        default:             COthterKeyAction();            break;
    }
}

//----------------------------------------------------------------------------------------------------
void MAutoPowerDownAdjMenu(void)
{
    ucOsdState = MENU_SUB_AUTO_POWER;
    CClearMsg(_CLEAR_AND_EXIT_SUB_ITEM);
}

//----------------------------------------------------------------------------------------------------
void MAutoPowerDownAdjLR(BYTE LR)
{
    BYTE i,ucTemp = _GET_POWER_DOWN_TIME();
	BYTE ucXPos=13;
	BYTE ucYPos = _MESSAGE_V_POSITION;
	
	if(ucOsdState == SLEEP_TIME_ADJ)
	{
		ucXPos=13;
		ucYPos =0;

	//reset char width to 12 pixel
	Gotoxy(13, 0, BYTE_ATTRIB);
	CScalerSendAddr(_OSD_DATA_PORT_92, _WRITE, _NON_AUTOINC);
	for(i=0;i<3;i++)	
	CScalerSendByte(0x8c);
	CScalerSendWriteStop();
	}
    
    CClearMsg(_CLEAR_MSG_ONLY);

    ucTemp = ValueInRangeChange(0,4,ucTemp,LR,1);
    
    _SET_POWER_DOWN_TIME(ucTemp);
    CEepromSaveSystemData(); // Save Adjust result
    
    ucAutoPowerDownTime = ucTemp * 15;
    if (0 == ucAutoPowerDownTime) // Auto power down time off
    {
        ucAutoPowerDownTime = 0xff;
    }
    
    ucMinuteCount       = 0;  // Reset count
    
	if(ucOsdState == SLEEP_TIME_ADJ)

		{
			CenterTextout(sSLEEP_TIME, 7, 0);
		    if (0 == _GET_POWER_DOWN_TIME() ) // Auto power down time off
		       CenterTextout((BYTE *)sOn_Off[0][GET_LANGUAGE], 14, 0);//_MESSAGE_V_POSITION);
		    else
		    {
		       Gotoxy(13, 0, BYTE_DISPLAY);
		       CShowNumber((_GET_POWER_DOWN_TIME()  * 15), 0);    
		    }
		}
	else
		{
		    if (0 == _GET_POWER_DOWN_TIME() ) // Auto power down time off
		       CenterTextout((BYTE *)sOn_Off[0][GET_LANGUAGE], 14, _MESSAGE_V_POSITION);//_MESSAGE_V_POSITION);
		    else
		    {
		       Gotoxy(13, _MESSAGE_V_POSITION, BYTE_DISPLAY);
		       CShowNumber((_GET_POWER_DOWN_TIME() * 15), 0);    
		    }
		}
    LR = 0;
}

#endif

#if(_BLUE_BACKGROUND_FUNC == _ENABLE)
//--------- Blue proc ----------------------------------
void MBlueAdjProc(void)
{
    switch(ucKeyMessage)
    {
        // Move item
#if(_USE_UD_LR_KEY_MSG)
        case VK_F_UP:
        case VK_F_DOWN:
            MBlueAdjMenu();
            COsdProc();
            break;
#endif

        // Exit item
#if(_MENU_FUNC == _MENU_EXIT_ITEM)
        case VK_ENTER: 
#endif
        case VK_AUTO:
        case VK_IR_EXIT:
        case VK_MENU:        MBlueAdjMenu();       break;

        // Adjust
#if(_USE_UD_LR_KEY_MSG)
        case VK_F_LEFT:
#endif
        case VK_LEFT:        MBlueAdjLR(1);        break;

        // Adjust
#if(_USE_UD_LR_KEY_MSG)
        case VK_F_RIGHT:
#endif
        case VK_RIGHT:       MBlueAdjLR(0);        break;

        // Other key
        default:             COthterKeyAction();   break;
    }
}

//----------------------------------------------------------------------------------------------------
void MBlueAdjMenu(void)
{
    ucOsdState = MENU_SUB_BLUE;
    CClearMsg(_CLEAR_AND_EXIT_SUB_ITEM);
}

//----------------------------------------------------------------------------------------------------
void MBlueAdjLR(BYTE LR)
{   
         LR = LR;
    CClearMsg(_CLEAR_MSG_ONLY);

	 if( _GET_BLUE_BACKGROUND())
	 	{
    	       _SET_BLUE_BACKGROUND(0);
		 LR= 0;
	 	}
        else
        	{
 	     _SET_BLUE_BACKGROUND(1);
		 LR= 1;
        	}
                CAdjustBackgroundColor(0x00, 0x00, (_GET_INPUT_SOURCE() == _SOURCE_VIDEO_TV) ? ((_GET_BLUE_BACKGROUND()) ? 0xFF: 0x00) : 0x00);
   
    CEepromSaveSystemData(); // Save Adjust result
    CenterTextout((BYTE *)sOn_Off[LR][GET_LANGUAGE], 14, _MESSAGE_V_POSITION);
}

//----------------------------------------------------------------------------------------------------
#endif


//----------------------------------------------------------------------------------------------------
void GotoAdjustVolume(void)
{ 
    CInitOSDMainFrame();
#if(_HARDWARE_LOAD_FONT == _ON)

        CScalerLoadHardwareVLCFont(tFntIconSpker, 0x10);

#else

    CScalerLoadFont(tFntIconSpker, 0x10, 6, _COMPRESS_FONT);

#endif

     if (_GET_OSD_SIZE()) 
        OSDPosition(_OSD_DOUBLE_WIDTH(_VOLUME_WINDOW_WIDTH), _OSD_DOUBLE_HEIGHT(_VOLUME_WINDOW_HEIGHT), _VOLUME_DOUBLE_H_OFFSET, _VOLUME_DOUBLE_V_OFFSET, 0x03);
      else
       OSDPosition(_VOLUME_WINDOW_WIDTH, _VOLUME_WINDOW_HEIGHT, _VOLUME_H_OFFSET, _VOLUME_V_OFFSET, 0x03);

    SetOSDDouble((_GET_OSD_SIZE() ? 0x03 : 0x00)  | OSD_WINDOWCHAR_BLENDING);   

    // Draw window
    COsdFxDrawWindow(XSTART(_VOLUME_WINDOW_H_POS), YSTART(_VOLUME_WINDOW_V_POS), XEND(_VOLUME_WINDOW_WIDTH), YEND(_VOLUME_WINDOW_HEIGHT), tOSD_MINI_WINDOW_STYLE);

    if (STATE_MUTEON == GET_MUTE_STATE()) // Current mute on,so set mute off
    {
        SET_MUTE_STATE(STATE_MUTEOFF);
        CSetVolume();
    }

    DispIcon(1, 1, 0x10);
    OSDSlider(3, 1, 10, stOsdUserData.Volume, 100, 0x40, _SHOW_PERCENT);
    
    
    COsdFxEnableOsd();
    ucOsdState = MENU_VOLUME_SP;
}

#if(_KEY_TYPE_OSD007== _5KEY_SUPPORT)
//----------------------------------------------------------------------------------------------------
void GotoAdjustChanel(void)
{ 
    CInitOSDMainFrame();

    SetOSDDouble((_GET_OSD_SIZE() ? 0x03 : 0x00)  | OSD_WINDOWCHAR_BLENDING);   

     if (_GET_OSD_SIZE()) 
        OSDPosition(_OSD_DOUBLE_WIDTH(_VOLUME_WINDOW_WIDTH), _OSD_DOUBLE_HEIGHT(_VOLUME_WINDOW_HEIGHT), _VOLUME_DOUBLE_H_OFFSET, _VOLUME_DOUBLE_V_OFFSET, 0x03);
      else
       OSDPosition(_VOLUME_WINDOW_WIDTH, _VOLUME_WINDOW_HEIGHT, _VOLUME_H_OFFSET, _VOLUME_V_OFFSET, 0x03);


    // Draw window
    COsdFxDrawWindow(XSTART(_VOLUME_WINDOW_H_POS), YSTART(_VOLUME_WINDOW_V_POS), XEND(_VOLUME_WINDOW_WIDTH), YEND(_VOLUME_WINDOW_HEIGHT), tOSD_MINI_WINDOW_STYLE);
#if(_NTSC_SEARCH_TABLE)
     CLeftAlignTextout((BYTE *)sCATV_AIR[_GET_CATV_AIR()], 4, 2);
 #else
   CLeftAlignTextout((BYTE *)sTV, 4, 2);    //060815
#endif
   
   OSDLine(2, 10, 14, 0x8c, BYTE_ATTRIB);
   OSDClear(2, 1, 10, 14, 0x00, BYTE_DISPLAY);
   CLR_KEYREPEATENABLE();
   
   Gotoxy(9, 2, BYTE_DISPLAY);
  if(stVDCColor.CurrentChannel<10)
  	{
  	        OutputChar(0x00);           
  	        OutputChar(0x00);           
  	}
  else if(stVDCColor.CurrentChannel<100)
  	        OutputChar(0x00);            
   CShowNumber(stVDCColor.CurrentChannel, 0);
 
   ucTVType=CLoadChannelColorType(stVDCColor.CurrentChannel);
        CLeftAlignTextout((BYTE  *)sTVType[ucTVType], 14, 2);

   
    COsdFxEnableOsd();
    ucOsdState = MENU_CHANEL_SP;
}
#endif
//----------------------------------------------------------------------------------------------------
#if(_IR_ENABLE)        
void SSetMuteState(void)
{
    BYTE ucMuteCurrent = GET_MUTE_STATE();
    
    
    if (STATE_MUTEON == ucMuteCurrent) // Current mute on,so set mute off
    {
        SET_MUTE_STATE(STATE_MUTEOFF);
    }
    else
    {
        SET_MUTE_STATE(STATE_MUTEON);
    }

    DrawMuteState();
    
    CSetVolume();
}
#endif

//----------------------------------------------------------------------------------------------------
#if(_AUTO_POWER_DOWN)
void CShowTimer(void)
{
    BYTE ucCurrentMin = ucAutoPowerDownTime - 1;
    BYTE ucCurrentSec = 59 - (BYTE)(ucMinuteCount/1000);
    
    if (!bTimerOnScreen)
    {
        COsdFxDisableOsd();
        SetOSDRamAddress(ROW_COUNT,COL_WIDTH,FONT_BASE_ADDRESS);
        SetOSDDouble(OSD_DOUBLE_HEIGHT_ENABLE | OSD_DOUBLE_WIDTH_ENABLE);
        SetRowCmds(ROW_COUNT,COL_WIDTH);
        COsdFxCodeWrite(ucCloseAllWindow);
        CClearWindow(0x20);

     //if (_GET_OSD_SIZE()) 
     //   OSDPosition(_OSD_DOUBLE_WIDTH(55), _OSD_DOUBLE_HEIGHT(30), _RIGHT_UP_OSD_H_OFFSET, 1, 0x03);
     // else
       OSDPosition(55, 30, _RIGHT_UP_OSD_H_OFFSET, 1, 0x03);

        COsdFxEnableOsd();
        bTimerOnScreen = 1;
    }

    COsdFxEnableOsd();
	
    Gotoxy(1,0,BYTE_DISPLAY);         
    CShowNumber(ucAutoPowerDownTime - 1, 2);
    OutputChar(0x3a);  // Show ":"
    CShowNumber(59 - (BYTE)(ucMinuteCount/1000), 2);
    
    
    CTimerReactiveTimerEvent(SEC(stOsdUserData.OsdTimeout),COsdDispOsdTimerEvent);
}
#endif


#if(_VIDEO_CHIP == _VDC_TB1334)
//----------------------------------------------------------------------------------------------------
void CAudioCtrl(void)
{
    if (_GET_INPUT_SOURCE() != _SOURCE_VIDEO_TV)
        return;
 /*
  #if(_VIDEO_TV_SUPPORT)
    if (bChangeChannel)
        return;
  #endif
*/
    if (ucAudioState != 0)
        ucAudioState++;

    if (ucAudioState < 5)
        return;
        
    if (!gmi_CModeLocked())  // TV no signal
        MUTE_ON();
    else
        CSetVolume();

    ucAudioState = 1;
}
#endif

//----------------------------------------------------------------------------------------------------

void HintDialog(void)
{
    CInitOSDMainFrame();
	

     SetOSDDouble((_GET_OSD_SIZE() ? 0x03 : 0x00)  | OSD_WINDOWCHAR_BLENDING);   
     if (_GET_OSD_SIZE()) 
        OSDPosition(_OSD_DOUBLE_WIDTH(_HINT_WINDOW_H_END), _OSD_DOUBLE_HEIGHT(_HINT_WINDOW_V_END), _AUTO_H_OFFSET, _AUTO_V_OFFSET, 0x03);
      else
       OSDPosition(_HINT_WINDOW_H_END, _HINT_WINDOW_V_END, _AUTO_DOUBLE_H_OFFSET, _AUTO_DOUBLE_V_OFFSET, 0x03);

    COsdFxDrawWindow(XSTART(_HINT_WINDOW_H_POS), YSTART(_HINT_WINDOW_V_POS), XEND(_HINT_WINDOW_H_END), YEND(_HINT_WINDOW_V_END), tOSD_MINI_WINDOW_STYLE);

    switch(ucOsdEventMsg)
    {
        case _SHOW_NOSIGNAL_MSG:
            CenterTextout((BYTE *)sNoSignal[GET_LANGUAGE], 10, 2);
            break;

        case _SHOW_NOSUPPORT_MSG:
            CenterTextout((BYTE *)sNotSupport[GET_LANGUAGE], 10, 2);
            break;

        case _SHOW_NOCABLE_MSG:
            CenterTextout((BYTE *)sNoCable[GET_LANGUAGE], 10, 2);
            CTimerCancelTimerEvent(COsdDispOsdTimerEvent);
            break;
    }
   
    COsdFxEnableOsd();
    
    if(GET_PANELPOWERSTATUS() == _OFF)
        CPowerPanelOn();
    if (GET_LIGHTPOWERSTATUS() == _OFF)  
        CPowerLightPowerOn(); 
}
//----------------------------------------------------------------------------------------------------
void CShowCurrentSourceTitle(BYTE ucHpos, BYTE ucVpos)
{
    switch(_GET_INPUT_SOURCE())
    {
        case _SOURCE_VGA:             CLeftAlignTextout(sVGA, ucHpos, ucVpos);             break;
        case _SOURCE_DVI:             CLeftAlignTextout(sDVI, ucHpos, ucVpos);             break;
        case _SOURCE_HDMI:            CLeftAlignTextout(sHDMI, ucHpos, ucVpos);            break;
        case _SOURCE_VIDEO_AV:        CLeftAlignTextout(sVIDEO, ucHpos, ucVpos);           break;
        case _SOURCE_VIDEO_SV:        CLeftAlignTextout(sSVIDEO, ucHpos, ucVpos);          break;
        case _SOURCE_VIDEO_YUV:       CLeftAlignTextout(sYUV, ucHpos, ucVpos);             break;    
        case _SOURCE_VIDEO_TV:        CLeftAlignTextout(sTV, ucHpos, ucVpos);              break;
        case _SOURCE_YPBPR:           CLeftAlignTextout(sYPBPR, ucHpos, ucVpos);           break;
        case _SOURCE_VIDEO_SCART:     CLeftAlignTextout(sSCART, ucHpos, ucVpos);           break;
        case _SOURCE_VIDEO_DVD:      CLeftAlignTextout(sDVD, ucHpos, ucVpos);           break;
    }
}

#if(_IR_ENABLE)        
//----------------------------------------------------------------------------------------------------
void CDisplayCurrentSourceMessage(void)
{
    CInitOSDMainFrame();
    SetOSDDouble( 0x03 );   

     if (_GET_OSD_SIZE()) 
        OSDPosition(_OSD_DOUBLE_WIDTH(220), _OSD_DOUBLE_HEIGHT(54), _LIFT_UP_H_OFFSET, 1, 0x03);
      else
       OSDPosition(220, 54, _LIFT_UP_H_OFFSET, 1, 0x03);

    OSDClear(0, 4, 0, 25, 0x20, BYTE_COLOR);  // Set message color to red

    CShowCurrentSourceTitle(1, 0);
    switch(_GET_INPUT_SOURCE())
    {
    case _SOURCE_VGA:
    case _SOURCE_DVI:
    case _SOURCE_HDMI:
        //display display size
        Gotoxy(1, 2, 0x50);
        OutputDisplaySize();
        //display refresh
        Gotoxy(12, 2, 0x50);
        OutputChar('@');          
        OutputChar(0x00);            
        OutputRefrushRate();             
        break; 

#if(_YPBPR_SUPPORT)
    case _SOURCE_YPBPR:
        if (stModeInfo.ModeCurr < _MAX_YPBPR_MODE)
           CLeftAlignTextout((BYTE *)sYPbPrMode[stModeInfo.ModeCurr], 0, 2);
        break;
#endif

#if(_VIDEO_SUPPORT)
    case _SOURCE_VIDEO_AV:
    case _SOURCE_VIDEO_SV:
    case _SOURCE_VIDEO_YUV:
    case _SOURCE_VIDEO_SCART:
        case _SOURCE_VIDEO_DVD:   
        if(CHECK60HZ())
            CLeftAlignTextout(sNTSC, 1, 2);
        else
            CLeftAlignTextout(sPAL, 1, 2);
        break;
#endif

#if(_VIDEO_TV_SUPPORT)
    case _SOURCE_VIDEO_TV:
        Gotoxy(1, 1, BYTE_DISPLAY);         
        CShowNumber(stVDCColor.CurrentChannel, 0);
#if(_NTSC_SEARCH_TABLE)
        CLeftAlignTextout((BYTE *)sCATV_AIR[_GET_CATV_AIR()],1,2);
        CLeftAlignTextout((BYTE *)sTVType[ucTVType],1,3);
#else		
        CLeftAlignTextout((BYTE *)sTVType[ucTVType],1,2);
#endif
        break;
#endif
    }

    CTimerReactiveTimerEvent(SEC(5),COsdDispOsdTimerEvent);
    COsdFxEnableOsd();         
#if(_AUTO_POWER_DOWN)
    bTimerOnScreen = 0;
#endif

    ucOsdState     = MENU_SHOW_MESSAGE_SATAE;
}
#endif

//----------------------------------------------------------------------------------------------------
void ShowNote(void)
{
   if(GET_DO_SHOW_NOTE()==0)
   	{
    CInitOSDMainFrame();
    SetOSDDouble(OSD_DOUBLE_HEIGHT_ENABLE | OSD_DOUBLE_WIDTH_ENABLE);


     if (_GET_OSD_SIZE()) 
        OSDPosition(_OSD_DOUBLE_WIDTH(220), _OSD_DOUBLE_HEIGHT(54), _LIFT_UP_H_OFFSET, 1, 0x03);
      else
       OSDPosition(220, 54, _LIFT_UP_H_OFFSET, 1, 0x03);

    OSDLine(0, 0, 10, 0x20, BYTE_COLOR);
    CShowCurrentSourceTitle(0, 0);
    
    COsdFxEnableOsd();         
    CTimerReactiveTimerEvent(SEC(10),COsdDispOsdTimerEvent);
      
    if(GET_PANELPOWERSTATUS() == _OFF)
        CPowerPanelOn();
    if (GET_LIGHTPOWERSTATUS() == _OFF)  
        CPowerLightPowerOn(); 
        
	SET_DO_SHOW_NOTE(1);
   	}
    ucOsdState = MENU_SHOW_MSG_STATE;
}
//---------------------------------------------------------------------------------------------------------------------

#if(IR_Test_EN== _ON)    
void PrintfHex(BYTE Value)
{
     BYTE h,l,t;

     t = (Value & 0x0f);
     if (t < 10)    
        l = t + '0';
     else       
        l = t -10 + 'A';

     t = (Value >> 4) & 0x0f;

     if (t < 10) 
        h = t + '0';
     else     
        h = t - 10 + 'A';

     CScalerSendAddr(_OSD_DATA_PORT_92, _WRITE, _NON_AUTOINC);
     CScalerSendByte(h);
     CScalerSendByte(l);
     CScalerSendWriteStop();
}

void Display_IR(void)//LastLanguage()
{
	Gotoxy(2, 12, BYTE_DISPLAY);
	PrintfHex(CUSTOM_CODE_STATE_H);PrintfHex(CUSTOM_CODE_STATE_L);

	Gotoxy(2,13,BYTE_DISPLAY);
	PrintfHex(CMD_DATA_INFO);

     COsdFxEnableOsd();

}
#endif

//---------------------------------------------------------------------------------------------------------------------
#endif        //#if(OSD_TYPE == OSD03)
