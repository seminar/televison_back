#define __OSDTV007___

#include "Header\Include.h"

#if(_OSD_TYPE == _OSD007)

#if(_VIDEO_TV_SUPPORT) 
//------------------------------------------------------------
void MTVNoneProc(void)
{
    switch(ucKeyMessage)
    {
#if(_MENU_FUNC == _MENU_EXIT_ITEM)
        case VK_ENTER: 
#endif
        case VK_MENU:        MPublicNoneMenu();             break;
        case VK_LEFT:        MTVNoneLR(0);                  break;
        case VK_RIGHT:       MTVNoneLR(1);                  break;
        
#if(_IR_ENABLE)        
        case VK_IR_MUTE:
            SSetMuteState();
            ucOsdEventMsg = _SAVE_EE_OSDUSERDATA_MSG;
            break;

#if(_USE_UD_LR_KEY_MSG && _REMOTE_CONTROLLER != IR_CHUNGHOP_RMH02)
        case VK_F_LEFT:
        case VK_F_RIGHT:
#endif
        case VK_IR_VOLDEC:
        case VK_IR_VOLINC:
            GotoAdjustVolume(); 
            break;
            
        case VK_IR_DISPLAY:
            CDisplayCurrentSourceMessage();
          //  CShowTVNumber(stVDCColor.CurrentChannel,_SHOW_CH_TV_NUMBER | _SHOW_CH_TV_TYPE | _SHOW_CH_SOUND_TYPE);
            break;
                
#if(_USE_UD_LR_KEY_MSG && _REMOTE_CONTROLLER != IR_CHUNGHOP_RMH02)
        case VK_F_DOWN:
#endif
        case VK_IR_CHINC:
            CChangeChannel(_NEXT_CHANNEL); // Next channel
            ucOsdEventMsg = _SAVE_EE_VEDIOCOLOR_MSG;
            break;
                    
#if(_USE_UD_LR_KEY_MSG && _REMOTE_CONTROLLER != IR_CHUNGHOP_RMH02)
        case VK_F_UP:
#endif
        case VK_IR_CHDEC:
            CChangeChannel(_PREV_CHANNEL); // Prev channel
            ucOsdEventMsg = _SAVE_EE_VEDIOCOLOR_MSG;
            break;
            
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

            STVInputCHNumber();
            break;
			
#if(_INPUT_NUMBER_MODE==IndirectInputNumber)
        case VK_IR_INPUTCH: 
             STVInputCHEnter();
			break;
#endif
        case VK_IR_RETURN:   STVReturnCH();                  break; 
#if(_IMAGE_COLOR_MODE)
        case _IR_IMAGE_KEY_MESSAGE:
            CGotoAdjImage();
            break;
#endif
#if(_AUTO_POWER_DOWN)
        case VK_IR_SLEEP:
            CGotoAdjSleep();
            break;
#endif
#endif
    }
    
}

//------------------------------------------------------------
void MTVNoneLR(BYTE LR)
{
#if(0)
    if(LR)
    {
        CChangeChannel(_PREV_CHANNEL);  // Prev channel
    }
    else
    {
        CChangeChannel(_NEXT_CHANNEL);  // Next channel
    }
    
    ucOsdEventMsg = _SAVE_EE_VEDIOCOLOR_MSG; 
#else
#if(_KEY_TYPE_OSD007== _5KEY_SUPPORT)
    if(LR==0)
    GotoAdjustChanel();
	else
    GotoAdjustVolume();
#else
	LR=LR;
    GotoAdjustVolume();
#endif
#endif
}  

//------------------------------------------------------------

#if(_IR_ENABLE)        
//----------- Shortcut key proc ---------------------------
#define _INPUT_NO_NUMBER       0
#define _INPUT_ONE_NUMBER      1
#define _INPUT_TWO_NUMBER      2
#define _INPUT_THREE_NUMBER    3
#if(_INPUT_NUMBER_MODE==DirectnessInputNumber)
//---------------------------------------------------------
void CHANGE_NUMBER_EVENT(void)
{
              ucPrevChannel =  stVDCColor.CurrentChannel;
              stVDCColor.CurrentChannel = (ucCurrentInputNumber > CloadMaxChannelNumber(0)) ? CloadMaxChannelNumber(0) : ucCurrentInputNumber;
		_SET_INPUTCH_STATE(0);
       	ucCurrentInputNumber=0;
               _SET_CHANNEL_FOR_AUDIO(1);
              ucOsdEventMsg=  _CHANGE_NUMBER_MSG;
}
//---------------------------------------------------------------------
void SDirectnessInputCHNumber(void)
{
	BYTE ucInputState = _GET_INPUTCH_STATE() ;

    switch(ucKeyMessage)
    {
        // Exit item
#if(_MENU_FUNC == _MENU_EXIT_ITEM)
        case VK_ENTER: 
		_SET_INPUTCH_STATE(0);
		ucCurrentInputNumber=0;
		CTimerCancelTimerEvent(CHANGE_NUMBER_EVENT);
		COsdFxDisableOsd();
            break;
#else
        case VK_MENU:
		_SET_INPUTCH_STATE(0);
		ucCurrentInputNumber=0;
		COsdFxDisableOsd();
		CTimerCancelTimerEvent(CHANGE_NUMBER_EVENT);
		MTVNoneProc();
            break;
#endif
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
		ucInputState = ValueInRangeChange(0, 3, ucInputState, 1, 1);
		_SET_INPUTCH_STATE(ucInputState);
	if(_GET_INPUTCH_STATE()==0)
		{
		ucInputState = ValueInRangeChange(0, 3, ucInputState, 1, 1);
		_SET_INPUTCH_STATE(ucInputState);
		ucCurrentInputNumber=0;
		}
  	if(ucOsdState!= ITEM_SHORTCUT_INPUTCH_NUM)	
	{
		ucCurrentInputNumber=(ucKeyMessage & 0x0f)+ucCurrentInputNumber*10;
		CInitOSDMainFrame();
		SetOSDDouble(OSD_DOUBLE_WIDTH_ENABLE| OSD_DOUBLE_HEIGHT_ENABLE);   

		OSDPosition(55, 30, _RIGHT_UP_OSD_H_OFFSET, 1, 0x03);
		OSDClear(0, 4, 0, 53, 0x20, BYTE_COLOR);  // Set message color to red
		Gotoxy(1,0,BYTE_DISPLAY);  
		CShowNumber(ucCurrentInputNumber, 0);
		CTimerReactiveTimerEvent(SEC(2), CHANGE_NUMBER_EVENT);
		COsdFxEnableOsd();         
#if(_AUTO_POWER_DOWN)
		bTimerOnScreen = 0;
#endif
         	_SET_INPUTCH_STATE(1);
		ucOsdState     = ITEM_SHORTCUT_INPUTCH_NUM;
	}
	else if(ucOsdState== ITEM_SHORTCUT_INPUTCH_NUM)
	{
	if(ucCurrentInputNumber==0&&(ucKeyMessage & 0x0f)==0)
		_SET_INPUTCH_STATE(0);
	if(ucCurrentInputNumber==0&&(ucKeyMessage & 0x0f)!=0)
		_SET_INPUTCH_STATE(1);
	        
             ucCurrentInputNumber=(ucKeyMessage & 0x0f)+ucCurrentInputNumber*10;
              OSDClear(0, 2, 1, 10 , 0x00, BYTE_DISPLAY);
		Gotoxy(1,0,BYTE_DISPLAY);         
		CShowNumber(ucCurrentInputNumber, 0);

		CTimerCancelTimerEvent(CHANGE_NUMBER_EVENT);
		CTimerReactiveTimerEvent(SEC(2), CHANGE_NUMBER_EVENT);
	}
        break;
        default:
            COthterKeyAction();
                break;
    }  

}
#endif
#if(_INPUT_NUMBER_MODE==IndirectInputNumber)
void STVInputCHEnter(void)
{
    BYTE ucInputState = _GET_INPUTCH_STATE() + 1;
    
    iInputCHCount = _INPUT_CH_TIMEOUT_COUNT;
    // Reset input number and state
    ucCurrentInputNumber = 0;
    ucCurrentInputState  = _INPUT_NO_NUMBER;  // 0: no input number   1: input one number     2: input two number    3: input three number
    
    if (ucInputState > 3)
    {   // Input state err reset input state to input one channel -
        ucInputState = 1;
        _SET_INPUTCH_STATE(0);
        CEepromSaveOsdUserData();
    }
    
    COsdFxDisableOsd();
    SetOSDRamAddress(ROW_COUNT,COL_WIDTH,FONT_BASE_ADDRESS);
    SetOSDDouble(OSD_DOUBLE_HEIGHT_ENABLE | OSD_DOUBLE_WIDTH_ENABLE);
    SetRowCmds(ROW_COUNT,COL_WIDTH);
    COsdFxCodeWrite(ucCloseAllWindow);
    CClearWindow(0x20);


    // if (_GET_OSD_SIZE()) 
   //     OSDPosition(_OSD_DOUBLE_WIDTH(55), _OSD_DOUBLE_HEIGHT(30), _RIGHT_UP_OSD_H_OFFSET, 1, 0x03);
   //   else
       OSDPosition(55, 30, _RIGHT_UP_OSD_H_OFFSET, 1, 0x03);

//    OSDPosition(30,30,38,1,0x01);
    
    Gotoxy(1, 0, BYTE_DISPLAY);         
    for(;ucInputState > 0;ucInputState--)
        OutputChar(0x2d);  // Show "-"
    
    COsdFxEnableOsd();
    CTimerReactiveTimerEvent(SEC(stOsdUserData.OsdTimeout),COsdDispOsdTimerEvent);
    ucOsdState = ITEM_SHORTCUT_INPUTCH_NUM;
}
//---------------------------------------------------------
void SInputCHNumber(void)
{
    BYTE ucInputState = _GET_INPUTCH_STATE() + 1;
    
    if (iInputCHCount > 0)
        iInputCHCount--;

    switch(ucKeyMessage)
    {
        // Exit item
#if(_MENU_FUNC == _MENU_EXIT_ITEM)
        case VK_ENTER: 
    //    case VK_AUTO:
            COsdFxDisableOsd();
            break;
#else
        case VK_MENU:
            COsdFxDisableOsd();
            MTVNoneProc();
            break;
#endif
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
            iInputCHCount = _INPUT_CH_TIMEOUT_COUNT;
            SInceptNumber(ucKeyMessage & 0x0f);
            break;
            
        case VK_IR_INPUTCH:
            iInputCHCount = _INPUT_CH_TIMEOUT_COUNT;
            ucInputState = ValueInRangeChange(1, 3, ucInputState, 1, 1);
            _SET_INPUTCH_STATE(ucInputState-1);
            CEepromSaveOsdUserData();
            
            // Reset input number and state
            ucCurrentInputNumber = 0;
            ucCurrentInputState  = 0;  // 0: no input number   1: input one number     2: input two number    3: input three number
            break;
            
        default:
            COthterKeyAction();
            
            if (ucOsdState != ITEM_SHORTCUT_INPUTCH_NUM)
                return;
            else           
                break;
    }  
    
    SShowCurrentInputState(ucInputState);
    
    if (ucInputState == ucCurrentInputState || iInputCHCount == 0)
    {
        BYTE ucMaxChannel = CloadMaxChannelNumber(1);
        BYTE ucTemp=CLoadChannelColorType(stVDCColor.CurrentChannel);
        
        iInputCHCount = _INPUT_CH_TIMEOUT_COUNT;
        if (ucCurrentInputState == 0)
        {
            COsdFxDisableOsd();
            return;
        }

        MUTE_ON();
      //  CForceBackGroundToBlack();
        ucOsdState = _MENU_NONE;
        CModeResetTVMode();
        CTimerDelayXms(200);
        
        ucPrevChannel =  stVDCColor.CurrentChannel;
	  if(ucCurrentInputNumber>=CloadMinChannelNumber())	
	        stVDCColor.CurrentChannel = (ucCurrentInputNumber > ucMaxChannel) ? ucMaxChannel : ucCurrentInputNumber;
        else
	        stVDCColor.CurrentChannel = CloadMinChannelNumber();
        CSetTVChannel(stVDCColor.CurrentChannel);
        CShowTVNumber(stVDCColor.CurrentChannel,_SHOW_CH_TV_NUMBER | _SHOW_CH_TV_TYPE | _SHOW_CH_SOUND_TYPE);
        gmi_CI2CWrite9886(ucTVType, _TUNER_MUTE_OFF, _NORMAL_MODE);
        bChangeChannel = 1;
		
         CModeResetTVNtscToPal();
        ucOsdEventMsg = _SAVE_EE_VEDIOCOLOR_MSG;
         _SET_CHANNEL_FOR_AUDIO(1);
    }
}

//---------------------------------------------------------
void SInceptNumber(const WORD ucNumber)
{
    switch(ucCurrentInputState)
    { 
        case _INPUT_NO_NUMBER: // not input number
            ucCurrentInputNumber = ucNumber;
            ucCurrentInputState  = _INPUT_ONE_NUMBER;
            break;
            
        case _INPUT_ONE_NUMBER: // Input on number alrady
        case _INPUT_TWO_NUMBER: // Input two number alrady
            ucCurrentInputNumber = (ucCurrentInputNumber*10) + ucNumber;
            ucCurrentInputState  = (ucCurrentInputState == _INPUT_TWO_NUMBER) ? _INPUT_THREE_NUMBER : _INPUT_TWO_NUMBER;
            break;
            /*
            case _INPUT_TWO_NUMBER: // Input two number alrady
            ucCurrentInputNumber = (ucCurrentInputNumber*10) + ucNumber;
            ucCurrentInputState  = _INPUT_THREE_NUMBER;
            break;*/
    }
}

//---------------------------------------------------------
void SShowCurrentInputState(WORD ucInputState)
{
    Gotoxy(1, 0, BYTE_DISPLAY); 
    
    switch(ucCurrentInputState)
    {
        case _INPUT_NO_NUMBER: // not input number
            for(;ucInputState > 0;ucInputState--)
                OutputChar(0x2d);  // Show "-"
            OutputChar(0x00);  // Show " "
            OutputChar(0x00);  // Show " "
            break;
            
        case _INPUT_ONE_NUMBER: // Input on number alrady
            CShowNumber(ucCurrentInputNumber,1);
            break;
            
        case _INPUT_TWO_NUMBER: // Input two number alrady
            CShowNumber(ucCurrentInputNumber,2);
            break;
            
        case _INPUT_THREE_NUMBER: // Input three number alrady
            CShowNumber(ucCurrentInputNumber,3);
            break;
    }
}
#endif
//---------------------------------------------------------
void STVInputCHNumber(void)
{
#if(_INPUT_NUMBER_MODE==IndirectInputNumber)			
		 STVInputCHEnter();
		 ucOsdState = ITEM_SHORTCUT_INPUTCH_NUM;
		SInputCHNumber();
#endif
     
#if(_INPUT_NUMBER_MODE==DirectnessInputNumber)
	SDirectnessInputCHNumber();
#endif	
}

//---------------------------------------------------------
void STVReturnCH(void)
{
    pData[0]                  = stVDCColor.CurrentChannel;
    stVDCColor.CurrentChannel = ucPrevChannel;
    ucPrevChannel             = pData[0];
    
    MUTE_ON();
    CModeResetTVMode();
    CSetTVChannel(stVDCColor.CurrentChannel);
    CShowTVNumber(stVDCColor.CurrentChannel, _SHOW_CH_TV_NUMBER | _SHOW_CH_TV_TYPE | _SHOW_CH_SOUND_TYPE);
    ucOsdEventMsg = _SAVE_EE_VEDIOCOLOR_MSG;
    bChangeChannel = 1;
}
#endif

//------------------------------------------------------------
void CDrawTVFunction(void)
{   BYTE uctemp=4;

    CLeftAlignTextout((BYTE *)sAutoSearch[GET_LANGUAGE], 1, uctemp++);       // "Auto Search"
#if(_NTSC_SEARCH_TABLE)
    CLeftAlignTextout((BYTE *)sCATVAIR[GET_LANGUAGE], 1, uctemp++);         // "TV System"

#else
    CLeftAlignTextout((BYTE *)sManualSearch[GET_LANGUAGE], 1, uctemp++);     // "Manual Search"
 #endif
   CLeftAlignTextout((BYTE *)sTuning[GET_LANGUAGE], 1, uctemp++);           // "Tuning"
    CLeftAlignTextout((BYTE *)sChannel[GET_LANGUAGE], 1, uctemp++);          // "Channel"
    CLeftAlignTextout((BYTE *)sTVSystem[GET_LANGUAGE], 1, uctemp++);         // "TV System"
#if(!_NTSC_SEARCH_TABLE)
    CLeftAlignTextout((BYTE *)sSwap[GET_LANGUAGE], 1, uctemp++);             // "Swap"
#endif
    CLeftAlignTextout((BYTE *)sSkip[GET_LANGUAGE], 1, uctemp++);            // "Skip"
    CLeftAlignTextout((BYTE *)sExit[GET_LANGUAGE], 1, uctemp++);            // "Exit"
}

//----------------------------------------------------------------------------------------------------
//   TV function Sub item
void MTVFuncSubItemProc(void)
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
			MTVFuncSubItemMenu();                break;

        // Move item
#if(_USE_UD_LR_KEY_MSG)
        case VK_F_UP:
#endif
#if(_KEY_TYPE_OSD007!=_7KEY_SUPPORT)
        case VK_RIGHT:       
#endif
			MTVFuncSubItemLR(1);                 break;

        // Move item
#if(_USE_UD_LR_KEY_MSG)
        case VK_F_DOWN:
#endif
#if(_KEY_TYPE_OSD007!=_7KEY_SUPPORT)
        case VK_LEFT:    
#endif
			MTVFuncSubItemLR(0);                 break;

        // Exit item
#if(_MENU_FUNC == _MENU_EXIT_ITEM)
        case VK_ENTER:      
#endif
#if(_KEY_TYPE_OSD007==_7KEY_SUPPORT)
        case VK_MENU:    
#endif
       case VK_AUTO:
       case VK_IR_EXIT:
             CExitToMainItem(MENU_MAIN_TV_FUNC);  break;
        // Other key
        default:             COthterKeyAction();                  break;
    }
}

//----------------------------------------------------------------------------------------------------
#if(_TV_SEARCH_SHOW_TYPE == _TV_SEARCH_SHOW_FREQ)
void CShowFreq(WORD iFreqN)
{
    DWORD lFreqTemp = 0;

    // Get PIF freq
    lFreqTemp = (((float)iFreqN/_TUNER_BP) - ((float)_PIF_FREQ/1000))*100;

    Gotoxy(10, _MESSAGE_V_POSITION, BYTE_DISPLAY); 
    iFreqN = lFreqTemp/100;  // MHz  
    CShowNumber(iFreqN, 0);
    OutputChar(0x2E); // "."

    iFreqN = lFreqTemp%100;  // KHz
    CShowNumber(iFreqN, 2);

    OutputChar('M');
    OutputChar('H');
    OutputChar('z');
    OutputChar(0x00); // " "
}

void CShowCurrentChannelFreq(void)
{
    WORD iFreq = 0;

    iFreq = CLoadChannelFreq(stVDCColor.CurrentChannel);
    CShowFreq(iFreq);
}
#endif

//----------------------------------------------------------------------------------------------------
void MTVFuncSubItemMenu(void)
{
    CClearMsg(_CLEAR_AND_SELECT_SUB_ITEM);

    Gotoxy(14, _MESSAGE_V_POSITION, BYTE_DISPLAY);

    switch(ucOsdState)
    {
        case MENU_AUTO_SEARCH:
#if(_NTSC_SEARCH_TABLE)				
        CTvAutoSearchCATVA_AIR();
#else			
	 CTvAutoSearch();
#endif
         COsdDispOsdTimerEvent();
         //   CClearMsg(_CLEAR_AND_EXIT_SUB_ITEM);
            break;

        case MENU_MANUAL_SEARCH:       
#if(_NTSC_SEARCH_TABLE)
      CenterTextout((BYTE *)sTVType[ucTVType], 10, _MESSAGE_V_POSITION);
       CenterTextout((BYTE *)sCATV_AIR[_GET_CATV_AIR()], 18, _MESSAGE_V_POSITION);
#else
            CShowCurrentChannelFreq();
#endif
            ucOsdState = MENU_MANUAL_SEARCH_ADJ;   
            break;

        case MENU_TUNING:
#if(_TV_SEARCH_SHOW_TYPE == _TV_SEARCH_SHOW_FREQ)
            CShowCurrentChannelFreq();
#endif
            ucOsdState = MENU_TUNING_ADJ;        
            break;

        case MENU_CHANNEL:     
    Gotoxy(10,_MESSAGE_V_POSITION,BYTE_DISPLAY);
    CShowNumber(stVDCColor.CurrentChannel, 0);
    CenterTextout((BYTE *)sTVType[ucTVType], 18, _MESSAGE_V_POSITION);
            ucOsdState = MENU_CHANNEL_ADJ;        
            break;

        case MENU_TV_SYSTEM: 
#if(_NTSC_SEARCH_TABLE)
      CenterTextout((BYTE *)sTVType[ucTVType], 10, _MESSAGE_V_POSITION);
       CenterTextout((BYTE *)sCATV_AIR[_GET_CATV_AIR()], 18, _MESSAGE_V_POSITION);
#else
            CenterTextout((BYTE *)sTVType[ucTVType], 14, _MESSAGE_V_POSITION);
#endif
              ucOSDAdjTemp = ucTVType;
		ucOsdState   = MENU_TV_SYSTEM_ADJ; 
            break;

            /*
        case MENU_SOUND_SYSTEM:  // Not use
            break;
                     */
        case MENU_SWAP:     
            CShowNumber(stVDCColor.CurrentChannel, 0);
            ucPrevChannel = stVDCColor.CurrentChannel;
            ucOsdState = MENU_SWAP_ADJ;        
            break;

        case MENU_SKIP: 
            ucOsdState = CLoadChannelSkip(stVDCColor.CurrentChannel);
            CenterTextout((BYTE *)sOn_Off[ucOsdState][GET_LANGUAGE],15,_MESSAGE_V_POSITION);
            ucOsdState = MENU_SKIP_ADJ;        
            break;

        case MENU_SUB_TV_FUNC_CLOSE: 
            CExitToMainItem(MENU_MAIN_TV_FUNC); 
            break;
    }        
}

//----------------------------------------------------------------------------------------------------
void MTVFuncSubItemLR(BYTE LR)
{
   BYTE  uctemp;
    ucOsdState = ValueInRangeChange(MENU_AUTO_SEARCH, MENU_SUB_TV_FUNC_CLOSE, ucOsdState, LR, 1);
	
#if(_NTSC_SEARCH_TABLE)
    if(ucOsdState==MENU_SWAP)
    ucOsdState = ValueInRangeChange(MENU_AUTO_SEARCH, MENU_SUB_TV_FUNC_CLOSE, ucOsdState, LR, 1);
     if(ucOsdState>=MENU_SWAP)		
	uctemp=ucOsdState - MENU_AUTO_SEARCH-1;
     else
#endif
	uctemp=ucOsdState - MENU_AUTO_SEARCH;
    CGotoNextSubItem(uctemp);
}



//--------- TVSystem adjust proc ----------------------------------
void MTVSystemAdjProc(void)
{
    switch(ucKeyMessage)
    {
        // Move item
#if(_USE_UD_LR_KEY_MSG)
        case VK_F_UP:
        case VK_F_DOWN:
            MTVSystemAdjMenu();
            COsdProc();
            break;
#endif

        // Exit item
#if(_MENU_FUNC == _MENU_EXIT_ITEM)
        case VK_ENTER: 
#endif
        case VK_AUTO:
        case VK_IR_EXIT:
        case VK_MENU:        MTVSystemAdjMenu();       break;

        // Adjust
#if(_USE_UD_LR_KEY_MSG)
        case VK_F_LEFT:
#endif
        case VK_LEFT:        MTVSystemAdjLR(1);        break;

        // Adjust
#if(_USE_UD_LR_KEY_MSG)
        case VK_F_RIGHT:
#endif
        case VK_RIGHT:       MTVSystemAdjLR(0);        break;

        // Other key
        default:             COthterKeyAction();       break;
    }
}

//----------------------------------------------------------------------------------------------------
void MTVSystemAdjMenu(void)
{
    ucOsdState = MENU_TV_SYSTEM;
    CClearMsg(_CLEAR_AND_EXIT_SUB_ITEM);
}
//----------------------------------------------------------------------------------------------------
bit BSearchedTVType(BYTE ucTvType)
{
#if(_NTSC_SEARCH_TABLE)
    switch(ucTvType) 
    {
        case _TV_NTSC_M    :    
            return 1;
            break;
        
        case _TV_PAL_M :    
            return 1;
            break;
        
        case _TV_PAL_N :    
            return 1;
            break;
    	}
#else

    switch(ucTvType) 
    {
        case _TV_NTSC_M    :    // 60Hz Sound 4.5M  NTSC M
#if(_TV_NTSC_M_SUPPORT)
            return 1;
#endif
            break;
        
        case _TV_NTSC_4_BG :    // 60Hz Sound 5.5M  NTSC 4/BG 
#if(_TV_NTSC_4_BG_SUPPORT)
            return 1;
#endif 
            break;
        
        case _TV_NTSC_4_DK :    // 60Hz Sound 6.5M  NTSC 4/DK 
#if(_TV_NTSC_4_DK_SUPPORT)
            return 1;
#endif
            break;
        
        case _TV_NTSC_4_I  :    // 60Hz Sound 6.0M  NTSC 4/I
#if(_TV_NTSC_4_I_SUPPORT)
            return 1;
#endif
            break;
        
        case _TV_PAL_M     :    // 60Hz Sound 4.5M  PAL M  
#if(_TV_PAL_M_SUPPORT)
            return 1;
#endif
            break;
        
        case _TV_PAL_BG    :    // 50Hz Sound 5.5M  PAL B/G
#if(_TV_PAL_BG_SUPPORT)
            return 1;
#endif
            break;
        
        case _TV_PAL_I     :    // 50Hz Sound 6.0M  PAL I
#if(_TV_PAL_I_SUPPORT)
            return 1;
#endif
            break;
        
        case _TV_PAL_DK    :    // 50Hz Sound 6.5M  PAL D/K
#if(_TV_PAL_DK_SUPPORT)
            return 1;
#endif
            break;
        
        case _TV_PAL_N     :    // 50Hz Sound 4.5M  PAL N 
#if(_TV_PAL_N_SUPPORT)
            return 1;
#endif
            break;
        
        case _TV_SECAM_BG  :    // 50Hz Sound 5.5M  SECAM B/G
#if(_TV_SECAM_BG_SUPPORT)
            return 1;
#endif
            break;
        
        case _TV_SECAM_DK  :    // 50Hz Sound 6.5M  SECAM D/K
#if(_TV_SECAM_DK_SUPPORT)
            return 1;
#endif
            break;
        
        case _TV_SECAM_L   :    // 50Hz Sound 6.5M  SECAM L  
#if(_TV_SECAM_L_SUPPORT)
            return 1;
#endif
            break;
        
        case _TV_SECAM_LL  :    // 50Hz Sound 6.5M  Secam L' 
#if(_TV_SECAM_LL_SUPPORT)
            return 1;
#endif
            break;
    } // end switch 
#endif    
    return 0;
}

//----------------------------------------------------------------------------------------------------
void MTVSystemAdjLR(BYTE LR)
{
    for(pData[15] = 0; pData[15] < (_MAX_TV_TYPE + 1); pData[15]++)
    {
        ucTVType = ValueInRangeChange(0, _MAX_TV_TYPE, ucTVType, LR, 1);
        
        if (BSearchedTVType(ucTVType))
            break;
    }
    
    CClearMsg(_CLEAR_MSG_ONLY);
#if(_NTSC_SEARCH_TABLE)
      CenterTextout((BYTE *)sTVType[ucTVType], 10, _MESSAGE_V_POSITION);
       CenterTextout((BYTE *)sCATV_AIR[_GET_CATV_AIR()], 18, _MESSAGE_V_POSITION);
#else
    CenterTextout((BYTE *)sTVType[ucTVType], 14, _MESSAGE_V_POSITION);
#endif
    
    // Save adjust result        
    CSaveChannelColorType(stVDCColor.CurrentChannel, ucTVType);
    
    gmi_CI2CWrite9886(ucTVType, _TUNER_MUTE_OFF, _NORMAL_MODE); // set 9886
}

/*
//--------- Sound System ADJUST PROC ----------------------------------
void MSoundSystemAdjProc(void)
{
    switch(ucKeyMessage)
    {
    case VK_MENU:        MSoundSystemAdjMenu();       break;
    case VK_LEFT:        MSoundSystemAdjLR(1);        break;
    case VK_RIGHT:       MSoundSystemAdjLR(0);        break;
    case VK_ENTER:       MSoundSystemAdjEnter();      break;
        
    default:             COthterKeyAction();          break;
    }
}

//----------------------------------------------------------------------------------------------------
void MSoundSystemAdjMenu(void)
{
    ucOsdState = MENU_SOUND_SYSTEM;
    CClearMsg(_CLEAR_AND_EXIT_SUB_ITEM);
}

//----------------------------------------------------------------------------------------------------
void MSoundSystemAdjLR(BYTE LR)
{
    BYTE ucSoundType = CLoadChannelSoundType(stVDCColor.CurrentChannel);
    
    ucSoundType = ValueInRangeChange(0, 3, ucSoundType, LR, 1);
    
    Gotoxy(14, _MESSAGE_V_POSITION, BYTE_DISPLAY);
    Textout((BYTE *)sTVSoundType[ucSoundType]);
    
    // Save adjust result
    CSaveChannelSoundType(stVDCColor.CurrentChannel, ucSoundType);
    
    //    gmi_CWrite9886(ucSoundType); // set 9886
}

//----------------------------------------------------------------------------------------------------
void MSoundSystemAdjEnter(void)
{
}
//----------------------------------------------------------------------------------------------------
  */


//--------- Auto Search PROC ----------------------------------
void MAutoSearchAdjProc(void)
{
    switch(ucKeyMessage)
    {
        // Move item
#if(_USE_UD_LR_KEY_MSG)
        case VK_F_UP:
        case VK_F_DOWN:
            MAutoSearchAdjMenu();
            COsdProc();
            break;
#endif

        // Exit item
#if(_MENU_FUNC == _MENU_EXIT_ITEM)
        case VK_ENTER: 
#endif
        case VK_AUTO:
        case VK_IR_EXIT:
        case VK_MENU:        MAutoSearchAdjMenu();       break;

        // Adjust
#if(_USE_UD_LR_KEY_MSG)
        case VK_F_LEFT:
#endif
        case VK_LEFT:        MAutoSearchAdjLR(1);        break;

        // Adjust
#if(_USE_UD_LR_KEY_MSG)
        case VK_F_RIGHT:
#endif
        case VK_RIGHT:       MAutoSearchAdjLR(0);        break;

        // Other key
        default:             COthterKeyAction();         break;
    }
}

//----------------------------------------------------------------------------------------------------
void MAutoSearchAdjMenu(void)
{
    ucOsdState = MENU_AUTO_SEARCH;
    CClearMsg(_CLEAR_AND_EXIT_SUB_ITEM);
}

//----------------------------------------------------------------------------------------------------
void MAutoSearchAdjLR(BYTE LR)
{
    LR = 0;
}

//----------------------------------------------------------------------------------------------------
#if(_TV_SEARCH_SHOW_TYPE == _TV_SEARCH_SHOW_SLIDER)
void CShowAutoSearchSliderInOSD(BYTE ucCurrentValue)
{
    SLIDER1(ucCurrentValue);
}
#endif

#if(_TV_SEARCH_SHOW_TYPE == _TV_SEARCH_SHOW_FREQ)
void CShowAutoSearchSliderInOSD(WORD ucCurrentValue)
{
    CShowFreq(ucCurrentValue);
}                           
#endif

//----------------------------------------------------------------------------------------------------
void CShowAutoSerachTotal(BYTE ucSearchTotal)
{
    Gotoxy(3, _MESSAGE_V_POSITION, BYTE_DISPLAY);
    CShowNumber(ucSearchTotal, 0);
}

//----------------------------------------------------------------------------------------------------

#define _STOP_AUTO_SEARCH_KEY_REPT_COUNT       4
bit CKeyStopAutoSearch(void)
{
    BYTE ucKeyRepCount = 0;
    BYTE ucNokeyCount  = 0;

#if(_MENU_FUNC == _MENU_EXIT_ITEM)
  #if(_IR_ENABLE)
    if (ucDetectIR_Cmd == IR_FUNC_MENU)
  #endif
#else
    if (ucKeyMessage == _MENU_KEY_MESSAGE)
#endif
{
    	ucKeyMessage = _NONE_KEY_MESSAGE;
	 ucDetectIR_Cmd = 0;
        return 1;
}

    if (_MENU_KEY_MASK == CKeyScan())
    {
        ucOSDAdjTemp++;
    }    
    else
    {
        ucOSDAdjTemp = 0;
    }    

    if (ucOSDAdjTemp > _STOP_AUTO_SEARCH_KEY_REPT_COUNT)
    {
        ucOSDAdjTemp = 0;
    	ucKeyMessage = _NONE_KEY_MESSAGE;
	ucDetectIR_Cmd = 0;
        return 1;
    }
    if (_POWER_KEY_MASK == CKeyScan()||ucDetectIR_Cmd==IR_FUNC_POWER)
    	{
    	ucKeyMessage = _NONE_KEY_MESSAGE;
	ucDetectIR_Cmd = 0;
	SET_POWERSWITCH();
        return 1;
    	}
    return 0; // Continue auto search
}

//----------------------------------------------------------------------------------------------------

//--------- Manual Search proc ----------------------------------
void MManualSearchAdjProc(void)
{
    switch(ucKeyMessage)
    {
        // Move item
#if(_USE_UD_LR_KEY_MSG)
        case VK_F_UP:
        case VK_F_DOWN:
            MManualSearchAdjMenu();
            COsdProc();
            break;
#endif

        // Exit item
#if(_MENU_FUNC == _MENU_EXIT_ITEM)
        case VK_ENTER: 
#endif
        case VK_AUTO:
        case VK_IR_EXIT:
        case VK_MENU:        MManualSearchAdjMenu();       break;

        // Adjust
#if(_USE_UD_LR_KEY_MSG)
        case VK_F_LEFT:
#endif
        case VK_LEFT:        MManualSearchAdjLR(1);        break;

        // Adjust
#if(_USE_UD_LR_KEY_MSG)
        case VK_F_RIGHT:
#endif
        case VK_RIGHT:       MManualSearchAdjLR(0);        break;

        // Other key
        default:             COthterKeyAction();           break;
    }
}

//----------------------------------------------------------------------------------------------------
void MManualSearchAdjMenu(void)
{
    ucOsdState = MENU_MANUAL_SEARCH;
    CClearMsg(_CLEAR_AND_EXIT_SUB_ITEM);
}

//----------------------------------------------------------------------------------------------------
void MManualSearchAdjLR(BYTE LR)
{
#if(_NTSC_SEARCH_TABLE)

    CClearMsg(_CLEAR_MSG_ONLY);

    LR = _GET_CATV_AIR();
    
    LR = 1 - LR;
    
    _SET_CATV_AIR(LR);
    CEepromSaveSystemData(); // Save Adjust result

            CenterTextout((BYTE *)sTVType[ucTVType], 10, _MESSAGE_V_POSITION);
            CenterTextout((BYTE *)sCATV_AIR[_GET_CATV_AIR()], 18, _MESSAGE_V_POSITION);


	CAdjustBackgroundColor(0x00, 0x00, 0xFF);     				
	 CScalerSetBit(_VDISP_CTRL_28, ~_BIT5, _BIT5); // Set bluebackground off

#else	   
    CManualSearch((bit)LR,stVDCColor.CurrentChannel);
    CTimerDelayXms(200);
#endif
}

//--------- Tuning proc ----------------------------------
void MTuningAdjProc(void)
{
    switch(ucKeyMessage)
    {
        // Move item
#if(_USE_UD_LR_KEY_MSG)
        case VK_F_UP:
        case VK_F_DOWN:
            MTuningAdjMenu();
            COsdProc();
            break;
#endif

        // Exit item
#if(_MENU_FUNC == _MENU_EXIT_ITEM)
        case VK_ENTER: 
#endif
        case VK_AUTO:
         case VK_IR_EXIT:
        case VK_MENU:        MTuningAdjMenu();       break;

        // Adjust
#if(_USE_UD_LR_KEY_MSG)
        case VK_F_LEFT:
#endif
        case VK_LEFT:        MTuningAdjLR(1);        break;

        // Adjust
#if(_USE_UD_LR_KEY_MSG)
        case VK_F_RIGHT:
#endif
        case VK_RIGHT:       MTuningAdjLR(0);        break;

        // Other key
        default:             COthterKeyAction();     break;
    }
}

//----------------------------------------------------------------------------------------------------
void MTuningAdjMenu(void)
{
    ucOsdState = MENU_TUNING;
    CClearMsg(_CLEAR_AND_EXIT_SUB_ITEM);
#if(_VIDEO_CHIP == _VDC_TB1334)
    CTimerDelayXms(100);
    if (gmi_CModeLocked())
        gmi_CSetVDCFreeRunMode(_VDC_FREE_RUN_MODE_TO_AUTO);
    else
        gmi_CSetVDCFreeRunMode((CHECK60HZ()) ? _VDC_FREE_RUN_MODE_TO_60HZ : _VDC_FREE_RUN_MODE_TO_50HZ);
#endif
}

//----------------------------------------------------------------------------------------------------
void MTuningAdjLR(BYTE LR)
{
    SET_KEYREPEATENABLE();
                               
#if(_TV_SEARCH_SHOW_TYPE != _TV_SEARCH_SHOW_FREQ)
    Gotoxy(14, _MESSAGE_V_POSITION, BYTE_DISPLAY);
    Textout((BYTE *)sTuningState[LR]);
#endif

    CTuningCurrentChannel((bit)LR,stVDCColor.CurrentChannel);
    CSaveChannelFreq(CLoadChannelFreq(stVDCColor.CurrentChannel), stVDCColor.CurrentChannel);

#if(_TV_SEARCH_SHOW_TYPE == _TV_SEARCH_SHOW_FREQ)
    CShowCurrentChannelFreq();
#endif              
}

//--------- Channel PROC ----------------------------------
void MChannelAdjProc(void)
{             
    switch(ucKeyMessage)
    {
        // Move item
#if(_USE_UD_LR_KEY_MSG)
        case VK_F_UP:
        case VK_F_DOWN:
            MChannelAdjMenu();
            COsdProc();
            break;
#endif

        // Exit item
#if(_MENU_FUNC == _MENU_EXIT_ITEM)
        case VK_ENTER: 
#endif
        case VK_AUTO:
        case VK_IR_EXIT:
        case VK_MENU:        MChannelAdjMenu();       break;

        // Adjust
#if(_USE_UD_LR_KEY_MSG)
        case VK_F_LEFT:
#endif
        case VK_LEFT:        MChannelAdjLR(1);        break;

        // Adjust
#if(_USE_UD_LR_KEY_MSG)
        case VK_F_RIGHT:
#endif
        case VK_RIGHT:       MChannelAdjLR(0);        break;

        // Other key
        default:             COthterKeyAction();      break;
    }
}
//----------------------------------------------------------------------------------------------------
void MChannelAdjMenu(void)
{
#if(_KEY_TYPE_OSD007== _5KEY_SUPPORT)
   if(ucOsdState==MENU_CHANEL_SP)
    	{
	  COsdFxDisableOsd();
         CTimerDelayXms(100);
    	}
     else
     	{
    ucOsdState = MENU_CHANNEL;
    CClearMsg(_CLEAR_AND_EXIT_SUB_ITEM);
     	}
#else
    ucOsdState = MENU_CHANNEL;
    CClearMsg(_CLEAR_AND_EXIT_SUB_ITEM);
#endif
}

//----------------------------------------------------------------------------------------------------
void MChannelAdjLR(BYTE LR)
{
    BYTE ucmaxchannel = CloadMaxChannelNumber(1);
    BYTE ucminchannel = CloadMinChannelNumber();
    BYTE ucTemp=CLoadChannelColorType(stVDCColor.CurrentChannel);
    stVDCColor.CurrentChannel = ValueInRangeChange(ucminchannel,ucmaxchannel,stVDCColor.CurrentChannel,LR,1);
	// Remove "Ta" noise when change channel  060731
    gmi_CI2CWrite9886(CLoadChannelColorType(stVDCColor.CurrentChannel),_TUNER_MUTE_ON,_NORMAL_MODE);
    CModeResetTVMode();
 
    //CAdjustBackgroundColor(0x00, 0x00, 0x00);     
   // CScalerSetBit(_VDISP_CTRL_28, ~_BIT5, _BIT5);
   // bChangeChannel = 1;

    CClearMsg(_CLEAR_MSG_ONLY);
#if(_KEY_TYPE_OSD007== _5KEY_SUPPORT)
  if(ucOsdState == MENU_CHANEL_SP)	
  	{
     OSDClear(0, 4, 0, COL_WIDTH - 2, 0x00, BYTE_DISPLAY);
    OSDClear(4, 8, 1, COL_WIDTH - 2, 0x8C, BYTE_ATTRIB);
     CSetTVChannel(stVDCColor.CurrentChannel);
#if(_NTSC_SEARCH_TABLE)
     CLeftAlignTextout((BYTE *)sCATV_AIR[_GET_CATV_AIR()], 4, 2);
 #else
    CLeftAlignTextout((BYTE *)sTV, 4, 2);    //060815
#endif
   
   Gotoxy(9, 2, BYTE_DISPLAY);
   CShowNumber(stVDCColor.CurrentChannel, 0);
   
        ucTVType=CLoadChannelColorType(stVDCColor.CurrentChannel);
        CLeftAlignTextout((BYTE  *)sTVType[ucTVType], 14, 2);
  	}
    else
#endif		
{
    CSetTVChannel(stVDCColor.CurrentChannel);
    
    Gotoxy(10,_MESSAGE_V_POSITION,BYTE_DISPLAY);
    CShowNumber(stVDCColor.CurrentChannel, 0);
    CenterTextout((BYTE *)sTVType[ucTVType], 18, _MESSAGE_V_POSITION);
}
    // Save current channel
    CEepromSaveVedioColor();    
    //gmi_CI2CWrite9886(CLoadChannelColorType(stVDCColor.CurrentChannel),_TUNER_MUTE_OFF,_NORMAL_MODE);
    _SET_CHANNEL_FOR_AUDIO(1);
    CModeResetTVNtscToPal();

}


//--------- Swap PROC ----------------------------------
void MSwapAdjProc(void)
{
    switch(ucKeyMessage)
    {
        // Move item
#if(_USE_UD_LR_KEY_MSG)
        case VK_F_UP:
        case VK_F_DOWN:
            MSwapAdjMenu();
            COsdProc();
            break;
#endif

        // Exit item
#if(_MENU_FUNC == _MENU_EXIT_ITEM)
        case VK_ENTER: 
#endif
        case VK_AUTO:
        case VK_IR_EXIT:
        case VK_MENU:        MSwapAdjMenu();       break;


        // Adjust
#if(_USE_UD_LR_KEY_MSG)
        case VK_F_LEFT:
#endif
        case VK_LEFT:        MSwapAdjLR(1);        break;

        // Adjust
#if(_USE_UD_LR_KEY_MSG)
        case VK_F_RIGHT:
#endif
        case VK_RIGHT:       MSwapAdjLR(0);        break;

        // Other key
        default:             COthterKeyAction();   break;
    }
}

//----------------------------------------------------------------------------------------------------
void MSwapAdjMenu(void)
{
    WORD ucSwapFreq        = CLoadChannelFreq(stVDCColor.CurrentChannel);
    BYTE ucSwapColorSystem = CLoadChannelColorType(stVDCColor.CurrentChannel);
    BYTE ucSwapSoundSystem = CLoadChannelSoundType(stVDCColor.CurrentChannel);
    BYTE ucSwapSkipSysytem= CLoadChannelSkip(stVDCColor.CurrentChannel);

#if(_CHANGE_SOURCE_BACKGROUCD_COLOR == _BLUE_COLOR)
            CAdjustBackgroundColor(0x00, 0x00, 0xff);
#else
            CAdjustBackgroundColor(0x00, 0x00, 0x00);
#endif
    CScalerSetBit(_VDISP_CTRL_28, ~_BIT5, _BIT5);

    bChangeChannel = 1;
    
    CSaveChannelFreq(CLoadChannelFreq(ucPrevChannel), stVDCColor.CurrentChannel);
    CSaveChannelColorType( stVDCColor.CurrentChannel,CLoadChannelColorType(ucPrevChannel));
    CSaveChannelSoundType( stVDCColor.CurrentChannel,CLoadChannelSoundType(ucPrevChannel));
    CSaveChannelSkip(CLoadChannelSkip(ucPrevChannel),stVDCColor.CurrentChannel);
	
    CSaveChannelFreq(ucSwapFreq, ucPrevChannel);
    CSaveChannelColorType(ucPrevChannel,ucSwapColorSystem);
    CSaveChannelSoundType(ucPrevChannel,ucSwapSoundSystem);  
    CSaveChannelSkip(ucSwapSkipSysytem,ucPrevChannel);
    
    CSetTVChannel(stVDCColor.CurrentChannel);
    
    ucOsdState = MENU_SWAP;
    CClearMsg(_CLEAR_MSG_ONLY);
    ShowMode();
    CSetItemWindowState(_SELECT_SUB_WINDOW, _MOVE_STATE);
}

//----------------------------------------------------------------------------------------------------
void MSwapAdjLR(BYTE LR)
{
    CClearMsg(_CLEAR_MSG_ONLY);

    stVDCColor.CurrentChannel = ValueInRangeChange(CloadMinChannelNumber(),CloadMaxChannelNumber(0),stVDCColor.CurrentChannel,LR,1);
    
    
    CSetTVChannel(stVDCColor.CurrentChannel);
    
    
    Gotoxy(14,_MESSAGE_V_POSITION,BYTE_DISPLAY);
    CShowNumber(stVDCColor.CurrentChannel, 0);
}

//--------- Skip PROC ----------------------------------
void MSkipAdjProc(void)
{
    switch(ucKeyMessage)
    {
        // Move item
#if(_USE_UD_LR_KEY_MSG)
        case VK_F_UP:
        case VK_F_DOWN:
            MSkipAdjMenu();
            COsdProc();
            break;
#endif

        // Exit item
#if(_MENU_FUNC == _MENU_EXIT_ITEM)
        case VK_ENTER: 
#endif
        case VK_AUTO:
        case VK_IR_EXIT:
        case VK_MENU:        MSkipAdjMenu();       break;

        // Adjust
#if(_USE_UD_LR_KEY_MSG)
        case VK_F_LEFT:
#endif
        case VK_LEFT:        MSkipAdjLR(1);        break;

        // Adjust
#if(_USE_UD_LR_KEY_MSG)
        case VK_F_RIGHT:
#endif
        case VK_RIGHT:       MSkipAdjLR(0);        break;

        // Other key
        default:             COthterKeyAction();   break;
    }
}

//----------------------------------------------------------------------------------------------------
void MSkipAdjMenu(void)
{
    ucOsdState = MENU_SKIP;
    CClearMsg(_CLEAR_AND_EXIT_SUB_ITEM);
}

//----------------------------------------------------------------------------------------------------
void MSkipAdjLR(BYTE LR)
{
    CClearMsg(_CLEAR_MSG_ONLY);

    LR = CLoadChannelSkip(stVDCColor.CurrentChannel);
    
    LR = 1 - LR;
    
    // Save current channel skip state
    CSaveChannelSkip((bit)LR, stVDCColor.CurrentChannel);
    
    CenterTextout((BYTE *)sOn_Off[LR][GET_LANGUAGE],15,_MESSAGE_V_POSITION);
}

//----------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------
//
// ucOption:   0x01: Only show ucTvNumber          _SHOW_CH_TV_NUMBER
//             0x02: Show tv type                  _SHOW_CH_TV_TYPE
//             0x04: Show sound type               _SHOW_CH_SOUND_TYPE
//
//-------------------------------------------------------------------------
void CShowTVNumber(const BYTE ucTvNumber, const BYTE ucOption)
{
    BYTE y;

    CInitOSDMainFrame();
    SetOSDDouble(OSD_DOUBLE_HEIGHT_ENABLE | OSD_DOUBLE_WIDTH_ENABLE);
   //  if (_GET_OSD_SIZE()) 
   //     OSDPosition(_OSD_DOUBLE_WIDTH(55), _OSD_DOUBLE_HEIGHT(30), _RIGHT_UP_OSD_H_OFFSET, 1, 0x03);
   //   else
       OSDPosition(55, 30, _RIGHT_UP_OSD_H_OFFSET, 1, 0x03);
    
#if(_AUTO_POWER_DOWN)
    bTimerOnScreen = 0;
#endif
    ucOsdState     = MENU_SHOW_MESSAGE_SATAE;
    
    OSDLine(0, 0, 10, 0x20, BYTE_COLOR);
    OSDLine(1, 0, 10, 0x20, BYTE_COLOR);
    OSDLine(2, 0, 10, 0x20, BYTE_COLOR);

    y = 0;
    if(ucOption & _SHOW_CH_TV_NUMBER)
    {
        Gotoxy(1,y,BYTE_DISPLAY);    
        CShowNumber(ucTvNumber, 0);
        y++;
    }
    if(ucOption & _SHOW_CH_TV_TYPE)
    {
#if(_NTSC_SEARCH_TABLE)
         CLeftAlignTextout((BYTE *)sCATV_AIR[_GET_CATV_AIR()], 1, y++);
        CLeftAlignTextout((BYTE *)sTVType[ucTVType],1,y);
#else
        CLeftAlignTextout((BYTE *)sTVType[ucTVType],1,y);
#endif
        y++;
    }
/*  if(ucOption & _SHOW_CH_SOUND_TYPE)
    {
    RightAlignTextOut((BYTE *)sTVSoundType[CLoadChannelSoundType(stVDCColor.CurrentChannel)], 8, y);
    y++;
}*/

    COsdFxEnableOsd();  
    CTimerReactiveTimerEvent(SEC(10),COsdDispOsdTimerEvent);
}

//-------------------------------------------------------------------------



#endif  //#if(_VIDEO_TV_SUPPORT)
#endif  //#if(OSD_TYPE == OSD007)
