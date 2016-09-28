#define __FAC_LCD_OSD__

#include "Header\Include.h"
#if(_FACTORY_MENU_EN)

//-----------------------------------------------------------
void COsdFacHandler()
{
    switch(ucOsdState)
    {
    case FAC_RESET:
    case FAC_ADC_OFFSET:
    case FAC_ADC_GAIN:
    case FAC_9300K:
    case FAC_6500K:
    case FAC_USER:
    case FAC_BRIGHTNESS:
    case FAC_CONTRAST:
    case FAC_BURIN_IN:
    case FAC_OSD_LANGUAGE:
    case FAC_POWER_SET:
    case FAC_LOGO_EN:
    case FAC_EMC:
    case FAC_EXIT:
        FMMainProc();
        break;
        
    case FAC_OFFSET_R:
    case FAC_OFFSET_G:
    case FAC_OFFSET_B:
        
    case FAC_GAIN_R:
    case FAC_GAIN_G:
    case FAC_GAIN_B:
        
    case FAC_9300_R:
    case FAC_9300_G:
    case FAC_9300_B:
        
    case FAC_6500_R:
    case FAC_6500_G:
    case FAC_6500_B:
        
    case FAC_USER_R:
    case FAC_USER_G:
    case FAC_USER_B:
        FMColorProc();
        break;
    }

    // In factory mode : not clear osd
   //     CTimerReactiveTimerEvent(SEC(stOsdUserData.OsdTimeout),COsdDispOsdTimerEvent);
}       
//-----------------------------------------------------------
void EnterFactoryMenu()
{   
         BYTE uctemp=0;
	if (ucCurrState == _SLEEP_STATE)
	{
	CModeResetMode();
	ucCurrState = _NOSIGNAL_STATE;
		if(GET_LIGHTPOWERSTATUS() == _OFF)
		{
	        CPowerPanelOn();
	        CPowerLightPowerOn();
		}
	}
	
	if (ucCurrState == _SLEEP_STATE&&ucCurrState == _NOSIGNAL_STATE)
		SET_OSD_READYFORDISPLAY();
	
	CTimerCancelTimerEvent(CModeNoSignalEvent);
	CTimerCancelTimerEvent(CModePowerSavingEvent);
	CTimerCancelTimerEvent(COsdDispOsdTimerEvent);
	CTimerCancelTimerEvent(CModeNoCableEvent);
	CTimerCancelTimerEvent(CModeNoSupportEvent);
	//CTimerCancelTimerEvent(CPowerDownEvent);

	// CAdjustColorPalette(tFacPALETTE_0);

	//Draw
	SetOSDRamAddress(FAC_ROW_COUNT,FAC_COL_WIDTH,FONT_BASE_ADDRESS);
	SetRowCmds(FAC_ROW_COUNT,FAC_COL_WIDTH);
	COsdFxCodeWrite(ucCloseAllWindow);
	CClearWindow(0x40);  // Clear window and set character color to black

	SetOSDDouble(0);

	// Init OSD Attrib & Clear Display & Set Color
	OSDClear(0, FAC_ROW_COUNT, 0, FAC_COL_WIDTH, 0x8C, BYTE_ATTRIB);     // Set as 1bit
	OSDClear(0, FAC_ROW_COUNT, 0, FAC_COL_WIDTH, 0x00, BYTE_DISPLAY);    // Clear Display
	OSDClear(0, FAC_ROW_COUNT, 0, FM_COL_R, 0x71,  BYTE_COLOR);
	OSDClear(0, FAC_ROW_COUNT, FM_COL_R,FAC_COL_WIDTH-FM_COL_R, 0x7B,  BYTE_COLOR);

	// Output Menu Item
	Gotoxy(1,uctemp++,BYTE_DISPLAY);
	Textout(sFacVersion);
	Gotoxy(1,uctemp++,BYTE_DISPLAY);
	Textout(sFacReset);
	Gotoxy(1,uctemp++,BYTE_DISPLAY);
	Textout(sFacADCOffset);
	Gotoxy(1,uctemp++,BYTE_DISPLAY);
	Textout(sFacADCGain);
	Gotoxy(1,uctemp++,BYTE_DISPLAY);
	Textout(sFac9300K);
	Gotoxy(1,uctemp++,BYTE_DISPLAY);
	Textout(sFac6500K);
	Gotoxy(1,uctemp++,BYTE_DISPLAY);
	Textout(sFacUser);
	Gotoxy(1,uctemp++,BYTE_DISPLAY);
	Textout(sFacBright);
	Gotoxy(1,uctemp++,BYTE_DISPLAY);
	Textout(sFacContrast);
	Gotoxy(1,uctemp++,BYTE_DISPLAY);
	Textout(sFacBurinIn);
	Gotoxy(1,uctemp++,BYTE_DISPLAY);
	Textout(sFacOsdLanguage);             	Gotoxy(FM_COL_R+1 ,uctemp-1,BYTE_DISPLAY);Textout((BYTE *)sLangName[_GET_FAC_OSD_LANGUAGE()]); 
	Gotoxy(1,uctemp++,BYTE_DISPLAY);  
	Textout(sFacPowerSet);                    	
	Gotoxy(FM_COL_R+1 ,uctemp-1,BYTE_DISPLAY);
       switch(_GET_FAC_POWER_SET())
       	{
              case 0:        Textout(sFacPowerDown);   break;       
              case 1:        Textout(sFacPowerUp);   break;       
              case 2:        Textout(sFacPowerSave);   break;     
       	}
	Gotoxy(1,uctemp++,BYTE_DISPLAY);
	Textout(sFacLOGOEN);
	Gotoxy(1,uctemp++,BYTE_DISPLAY);
	Textout(sFacEMC);
	Gotoxy(1,uctemp++,BYTE_DISPLAY);
	Textout(sFacExit);
	
       Gotoxy(FM_COL_R,0,BYTE_DISPLAY);
	Textout(sFacVersionCode);
	Gotoxy(FM_COL_R+1,1,BYTE_DISPLAY);
	OutputChar('R');
	Gotoxy(FM_COL_G+1,1,BYTE_DISPLAY);
	OutputChar('G');
	Gotoxy(FM_COL_B+1,1,BYTE_DISPLAY);
	OutputChar('B');

 	FMOutputAllData();

	OSDPosition(FAC_COL_WIDTH * 12,FAC_ROW_COUNT * 18,5,5,0x01);
	ucOsdState = FAC_RESET;
	FMItemState(1);

	COsdFxEnableOsd();
}

void OUTPUT_LOGO(void)
{
    OSDLine(FM_ROW_LOGO_EN, FM_COL_R+1, 5, 0x00, BYTE_DISPLAY);
    Gotoxy(FM_COL_R+1,FM_ROW_LOGO_EN,BYTE_DISPLAY);
#if(_LOGO_EN)
       if(GET_LOGO_EN())
	Textout(sFacOn);
	   else
	Textout(sFacOff);
#else
   	Textout(sFac_DISABLE);
#endif
       FMItemState(1);         // clear select state
}
void OUTPUT_EMC(void)
{
    OSDLine(FM_ROW_EMC, FM_COL_R+1, 5, 0x00, BYTE_DISPLAY);
    Gotoxy(FM_COL_R+1,FM_ROW_EMC,BYTE_DISPLAY);
       if(GET_EMC_EN())
	Textout(sFacOn);
	   else
	Textout(sFacOff);

       FMItemState(1);         // clear select state
}

//-----------------------------------------------------------
void FMOutputBurnInState()
{
    OSDLine(FM_ROW_BURIN_IN, FM_COL_R+1, 5, 0x00, BYTE_DISPLAY);
    Gotoxy(FM_COL_R+1,FM_ROW_BURIN_IN,BYTE_DISPLAY);
    if(GET_BURNIN_STATE() == BURNIN_ON)   
	{
	Textout(sFacOn);
	CScalerSetBit(_VDISP_CTRL_28, 0xff, _BIT5);
	//CAdjustBackgroundColor(0,0,0xff);	
        if (_ACTIVE_STATE == ucCurrState)
#if(RunLED==RedLED)			
		CPowerLedRed(); 
#elif(RunLED==GreenLED)			
		CPowerLedGreen(); 
#elif(RunLED==OrangeLED)			
		CPowerLedOrange(); 
#elif(RunLED==BlackLED)			
		CPowerLedBlack(); 
#endif	
       else
#if(NosignalStateLED==RedLED)			
		CPowerLedRed(); 
#elif(NosignalStateLED==GreenLED)			
		CPowerLedGreen(); 
#elif(NosignalStateLED==OrangeLED)			
		CPowerLedOrange(); 
#elif(NosignalStateLED==BlackLED)			
		CPowerLedBlack(); 
#endif
	}
    else 
    	{
	Textout(sFacOff);
        CAdjustBackgroundColor(0x00, 0x00, ((_GET_INPUT_SOURCE()) ? ((_GET_BLUE_BACKGROUND()) ? 0xff : 0x00) : 0x00));   
    	}
}
//-----------------------------------------------------------
void FMOutputAllData()
{
    BYTE i;
    
    //output adc data
    OUTPUT_OFFSET_R();
    OUTPUT_OFFSET_G();
    OUTPUT_OFFSET_B();
    OUTPUT_GAIN_R();
    OUTPUT_GAIN_G();
    OUTPUT_GAIN_B();
	
    for(i=0;i<(FM_ROW_USER-FM_ROW_ADC_OFFSET-1);i++)
    {
        SET_COLOR_TEMP_TYPE(i);
        CEepromLoadColorTempData();
        
        Gotoxy(FM_COL_R,4 + i,BYTE_DISPLAY);
        CShowNumber(stColorTempData.ColorTemp[_RED], 0);
        Gotoxy(FM_COL_G,4 + i,BYTE_DISPLAY);
        CShowNumber(stColorTempData.ColorTemp[_GREEN], 0);
        Gotoxy(FM_COL_B,4 + i,BYTE_DISPLAY);
        CShowNumber(stColorTempData.ColorTemp[_BLUE], 0);
    }
    OUTPUT_BIRGHT();
    OUTPUT_CONTRAST();
    FMOutputBurnInState();
    OUTPUT_LOGO();
    OUTPUT_EMC( );
}
//-----------------------------------------------------------
BYTE FMAINState(BYTE ucOsdState)    
{
	switch(ucOsdState)
		{
              case FAC_RESET:                 return FM_ROW_RESET;
              case FAC_ADC_OFFSET:       return FM_ROW_ADC_OFFSET;
              case FAC_ADC_GAIN:          return FM_ROW_ADC_GAIN;
              case FAC_9300K:                 return FM_ROW_9300K;
              case FAC_6500K:                 return FM_ROW_6500K;
              case FAC_USER:                  return FM_ROW_USER;
              case FAC_BRIGHTNESS:       return FM_ROW_BRIGHTNESS;
              case FAC_CONTRAST:           return FM_ROW_CONTRAST;
              case FAC_BURIN_IN:             return FM_ROW_BURIN_IN;
              case FAC_OSD_LANGUAGE:      return FM_ROW_OSD_LANGUAGE;
              case FAC_POWER_SET:            return FM_ROW_POWER_SET;
              case FAC_LOGO_EN:               return FM_ROW_LOGO_EN;
              case FAC_EMC:               return FM_ROW_EMC;
              case FAC_EXIT:                      return FM_ROW_EXIT;
		}
}
//-----------------------------------------------------------
void FMItemState(BYTE state)     // 1 : select state
{
    BYTE y;
    BYTE color;
    
    y = FMAINState(ucOsdState)  ;
    
    if(state)    color = 0x74;
    else         color = 0x71;
    OSDLine(y, 0, FM_COL_R, color, BYTE_COLOR);
}
//-----------------------------------------------------------
void FMMainProc()
{
    switch(ucKeyMessage)
    {
    case VK_F_LEFT:        FMMainMenu(_INC);       break;
    case VK_F_RIGHT:        FMMainMenu(_DEC);       break;
    case VK_F_UP:        FMMainLR(1);        break;
    case VK_F_DOWN:       FMMainLR(0);        break;
   }
}
//-----------------------------------------------------------
void FMMainMenu(BYTE ucMode)
{
    FMItemState(0);         // clear select state
    
    // Enter Sub Item
    switch(ucOsdState)
    {
    case FAC_RESET:
        DoReset();
        ucOsdState = FAC_RESET;
        FMOutputAllData();
        FMItemState(1);
	 SET_FAC_STATE(1);
	 SET_BURNIN_STATE(BURNIN_OFF);
	 ucOsdEventMsg=_BurnInRun_Out;
	 SET_NOSIGNAL_INFO(1);
     ucOsdEventMsg = _SAVE_EE_SYSTEMDATA_MSG;
        break;
        
    case FAC_ADC_OFFSET:
	  if(ucMode)	
	  	{
	        ucOsdState = FAC_OFFSET_R;
	        SUBITEM_STATE1(COL(FM_COL_R),ROW(FM_ROW_ADC_OFFSET),3);
	  	}
	  else
	  	{
	        ucOsdState = FAC_OFFSET_B;
	        SUBITEM_STATE1(COL(FM_COL_B),ROW(FM_ROW_ADC_OFFSET),3);
	  	}
        break;
        
    case FAC_ADC_GAIN:
	  if(ucMode)	
	  	{
              ucOsdState = FAC_GAIN_R;
              SUBITEM_STATE1(COL(FM_COL_R),ROW(FM_ROW_ADC_GAIN),3);
 	  	}
	  else
	  	{
	        ucOsdState = FAC_GAIN_B;
	        SUBITEM_STATE1(COL(FM_COL_B),ROW(FM_ROW_ADC_GAIN),3);
	  	}
       break;
        
    case FAC_9300K:
	  if(ucMode)	
	  	{
	        FMLoadColorTmp();
	        ucOsdState = FAC_9300_R;
	        SUBITEM_STATE1(COL(FM_COL_R),ROW(FM_ROW_9300K),3);
 	  	}
	  else
	  	{
	        FMLoadColorTmp();
	        ucOsdState = FAC_9300_B;
	        SUBITEM_STATE1(COL(FM_COL_B),ROW(FM_ROW_9300K),3);
	  	}
        break;
        
    case FAC_6500K:
	  if(ucMode)	
	  	{
	        FMLoadColorTmp();
	        ucOsdState = FAC_6500_R;
	        SUBITEM_STATE1(COL(FM_COL_R),ROW(FM_ROW_6500K),3);
 	  	}
	  else
	  	{
	        FMLoadColorTmp();
	        ucOsdState = FAC_6500_B;
	        SUBITEM_STATE1(COL(FM_COL_B),ROW(FM_ROW_6500K),3);
	  	}
        break;
                
    case FAC_USER:
 	  if(ucMode)	
	  	{
	        FMLoadColorTmp();
	        ucOsdState = FAC_USER_R;
	        SUBITEM_STATE1(COL(FM_COL_R),ROW(FM_ROW_USER),3);
 	  	}
	  else
	  	{
	        FMLoadColorTmp();
	        ucOsdState = FAC_USER_B;
	        SUBITEM_STATE1(COL(FM_COL_B),ROW(FM_ROW_USER),3);
	  	}
        break;
        
    case FAC_BRIGHTNESS:
    stConBriData.Brightness = ValueInRangeChange(0,255,stConBriData.Brightness,ucMode,0);
    OUTPUT_BIRGHT();
    ucOsdEventMsg = _SAVE_EE_BriConHueSat_MSG;
       FMItemState(1);         // clear select state
        break;
        
    case FAC_CONTRAST:
    stConBriData.Contrast = ValueInRangeChange(0,255,stConBriData.Contrast,ucMode,0);
    OUTPUT_CONTRAST();
    ucOsdEventMsg = _SAVE_EE_BriConHueSat_MSG;
       FMItemState(1);         // clear select state
        break;

    case FAC_BURIN_IN:
    if(GET_BURNIN_STATE() == BURNIN_ON)
    	{
        SET_BURNIN_STATE(BURNIN_OFF);
	 ucOsdEventMsg=_BurnInRun_Out;
    	}
    else 
	{
	SET_BURNIN_STATE(BURNIN_ON);
    	}
    FMOutputBurnInState();
       FMItemState(1);         // clear select state
     ucOsdEventMsg = _SAVE_EE_SYSTEMDATA_MSG;
        break;
       
    case FAC_OSD_LANGUAGE:
	OSDClear(FM_ROW_OSD_LANGUAGE, 1, 0, FAC_COL_WIDTH, 0x8C, BYTE_ATTRIB);     // Set as 1bit
	OSDClear(FM_ROW_OSD_LANGUAGE, 1, 0, FAC_COL_WIDTH, 0x00, BYTE_DISPLAY);    // Clear Display
	OSDClear(FM_ROW_OSD_LANGUAGE, 1, FM_COL_R,FAC_COL_WIDTH-FM_COL_R, 0x7B,  BYTE_COLOR);

       if(ucMode)
	_SET_FAC_OSD_LANGUAGE(GetPrevLanguage(_GET_FAC_OSD_LANGUAGE()));
	else
	_SET_FAC_OSD_LANGUAGE(GetNextLanguage(_GET_FAC_OSD_LANGUAGE()));
	SET_LANGUAGE(_GET_FAC_OSD_LANGUAGE());
	LoadLanguageFont();
        Gotoxy(COL(1) ,ROW(FM_ROW_OSD_LANGUAGE),BYTE_DISPLAY);
	Textout(sFacOsdLanguage);   
        Gotoxy(COL(FM_COL_R+1) ,ROW(FM_ROW_OSD_LANGUAGE),BYTE_DISPLAY);
	Textout((BYTE *)sLangName[_GET_FAC_OSD_LANGUAGE()]); 
        CEepromSaveOsdUserData();
       FMItemState(1);         // clear select state
        break;

    case FAC_POWER_SET:
    FMItemState(1);         // clear select state
           _SET_FAC_POWER_SET(ValueInRangeChange(0, 2, _GET_FAC_POWER_SET(), 1, 1));
		Gotoxy(COL(FM_COL_R+1) ,ROW(FM_ROW_POWER_SET),BYTE_DISPLAY);
        switch(_GET_FAC_POWER_SET())
       	{
              case 0:        Textout(sFacPowerDown);   break;       
              case 1:        Textout(sFacPowerUp);   break;       
              case 2:        Textout(sFacPowerSave);   break;     
        	}
         CEepromSaveOsdUserData();
      break;

    case FAC_LOGO_EN:
       if(GET_LOGO_EN())
    	{
        CLR_LOGO_EN();
    	}
    else 
	{
	SET_LOGO_EN( );
    	}
         OUTPUT_LOGO( );
     ucOsdEventMsg = _SAVE_EE_SYSTEMDATA_MSG;
       ucKeyMessage = _NONE_KEY_MESSAGE;
	   break;
    case FAC_EMC:
       if(GET_EMC_EN())
    	{
        CLR_EMC_EN();
	    CScalerSetBit(_SPREAD_SPECTRUM_B7, ~_BIT2, _BIT2);
	    CScalerSetBit(_SPREAD_SPECTRUM_B7, 0x0f, (_DCLK_SPREAD_RANGE << 4) & 0xf0);
	    CScalerSetBit(_SPREAD_SPECTRUM_B7, ~_BIT2, _BIT2);
	    CScalerSetBit(_SPREAD_SPECTRUM_B7, 0x0f, (_DCLK_SPREAD_RANGE << 4) & 0xf0);
    	}
    else 
	{
	    CScalerSetBit(_SPREAD_SPECTRUM_B7, ~_BIT2, _BIT2);
	    CScalerSetBit(_SPREAD_SPECTRUM_B7, 0xff, 0xff);
	    CScalerSetBit(_SPREAD_SPECTRUM_B7, ~_BIT2, _BIT2);
	    CScalerSetBit(_SPREAD_SPECTRUM_B7, 0xff, 0xff);
	SET_EMC_EN( );
    	}
         OUTPUT_EMC( );
     ucOsdEventMsg = _SAVE_EE_SYSTEMDATA_MSG;
       ucKeyMessage = _NONE_KEY_MESSAGE;
	   break;
    case FAC_EXIT:
	ucOsdState = _MENU_NONE;
	SET_FAC_STATE(0);
	COsdFxDisableOsd();       // Clear OSD
	if(GET_BURNIN_STATE()==BURNIN_ON)		
	SET_NOSIGNAL_INFO(1);
	else
		{
	SET_NOSIGNAL_INFO(0);
       SET_OSD_READYFORDISPLAY();						   																																																																				
	}
         CEepromSaveOsdUserData();
       ucKeyMessage = _NONE_KEY_MESSAGE;
	   break;
    }
}
BYTE FMAINStateOut(BYTE uctemp)    
{
	switch(uctemp)
		{
              case FM_ROW_RESET:                 return FAC_RESET;
              case FM_ROW_ADC_OFFSET:       return FAC_ADC_OFFSET;
              case FM_ROW_ADC_GAIN:          return FAC_ADC_GAIN;
              case FM_ROW_9300K:                 return FAC_9300K;
              case FM_ROW_6500K:                 return FAC_6500K;
              case FM_ROW_USER:                  return FAC_USER;
              case FM_ROW_BRIGHTNESS:       return FAC_BRIGHTNESS;
              case FM_ROW_CONTRAST:           return FAC_CONTRAST;
              case FM_ROW_BURIN_IN:             return FAC_BURIN_IN;
              case FM_ROW_OSD_LANGUAGE:      return FAC_OSD_LANGUAGE;
              case FM_ROW_POWER_SET:            return FAC_POWER_SET;
              case FM_ROW_LOGO_EN:               return FAC_LOGO_EN;
              case FM_ROW_EMC:               return FAC_EMC;
              case FM_ROW_EXIT:                      return FAC_EXIT;
		}
}

//-----------------------------------------------------------
void FMMainLR(BYTE LR)
{
BYTE   ucNumberMode=0;
BYTE   ucSearchMode=0;
 BYTE uctemp=FMAINState(ucOsdState);
    // Before select item change clear select
	FMItemState(0);
		uctemp = ValueInRangeChange(FM_ROW_RESET, FM_ROW_EXIT, uctemp, LR, 1);
	ucOsdState=FMAINStateOut(uctemp);
	//after select item change draw selec
	FMItemState(1);
      FMLoadColorTmp();
}

//-----------------------------------------------------------
void FMLoadColorTmp()
{
    switch(ucOsdState)
    {
    case FAC_9300K:
        SET_COLOR_TEMP_TYPE(_CT_9300);
        CEepromLoadColorTempData();
        CAdjustContrast();
        break;
        
    case FAC_6500K:
        SET_COLOR_TEMP_TYPE(_CT_6500);
        CEepromLoadColorTempData();
        CAdjustContrast();
        break;
        
        
    case FAC_USER:
        SET_COLOR_TEMP_TYPE(_CT_USER);
        CEepromLoadColorTempData();
        CAdjustContrast();
        break;         
    }
}

//-----------------------------------------------------------
void FMColorProc()
{
    switch(ucKeyMessage)
    {
    case VK_F_DOWN :        FMColorAdjLR(_INC);       break;
    case VK_F_UP:        FMColorAdjLR(_DEC);       break;
    case VK_F_LEFT:        FMColorLR(1);        break;
    case VK_F_RIGHT:       FMColorLR(0);        break;
    }
    
}

//-----------------------------------------------------------
//-----------------------------------------------------------
void FMColorLR(BYTE LR)
{
	 CLR_KEYREPEATENABLE();	
    switch(ucOsdState)
    {
    case FAC_OFFSET_R:
    case FAC_OFFSET_G:
    case FAC_OFFSET_B:
        FMColorState(FM_ROW_ADC_OFFSET,FAC_OFFSET_R,FM_STATE_CLR);
        ucOsdState = ValueInRangeChange(FAC_ADC_OFFSET,FAC_OFFSET_B,ucOsdState,LR,1);
        FMColorState(FM_ROW_ADC_OFFSET,FAC_OFFSET_R,FM_STATE_SELECT);
	 if(ucOsdState==FAC_ADC_OFFSET)
	 OSDLine(FM_ROW_ADC_OFFSET, 0, FM_COL_R, 0x74, BYTE_COLOR);
        break;
        
    case FAC_GAIN_R:
    case FAC_GAIN_G:
    case FAC_GAIN_B:
        FMColorState(FM_ROW_ADC_GAIN,FAC_GAIN_R,FM_STATE_CLR);
        ucOsdState = ValueInRangeChange(FAC_ADC_GAIN,FAC_GAIN_B,ucOsdState,LR,1);
        FMColorState(FM_ROW_ADC_GAIN,FAC_GAIN_R,FM_STATE_SELECT);
	 if(ucOsdState==FAC_ADC_GAIN)
	 OSDLine(FM_ROW_ADC_GAIN, 0, FM_COL_R, 0x74, BYTE_COLOR);
        break;
        
    case FAC_9300_R:
    case FAC_9300_G:
    case FAC_9300_B:
        FMColorState(FM_ROW_9300K,FAC_9300_R,FM_STATE_CLR);
        ucOsdState = ValueInRangeChange(FAC_9300K,FAC_9300_B,ucOsdState,LR,1);
        FMColorState(FM_ROW_9300K,FAC_9300_R,FM_STATE_SELECT);
	 if(ucOsdState==FAC_9300K)
	 OSDLine(FM_ROW_9300K, 0, FM_COL_R, 0x74, BYTE_COLOR);
        break;
        
    case FAC_6500_R:
    case FAC_6500_G:
    case FAC_6500_B:
        FMColorState(FM_ROW_6500K,FAC_6500_R,FM_STATE_CLR);
        ucOsdState = ValueInRangeChange(FAC_6500K,FAC_6500_B,ucOsdState,LR,1);
        FMColorState(FM_ROW_6500K,FAC_6500_R,FM_STATE_SELECT);
	 if(ucOsdState==FAC_6500K)
	 OSDLine(FM_ROW_6500K, 0, FM_COL_R, 0x74, BYTE_COLOR);
        break;
                
    case FAC_USER_R:
    case FAC_USER_G:
    case FAC_USER_B:
        FMColorState(FM_ROW_USER,FAC_USER_R,FM_STATE_CLR);
        ucOsdState = ValueInRangeChange(FAC_USER,FAC_USER_B,ucOsdState,LR,1);
        FMColorState(FM_ROW_USER,FAC_USER_R,FM_STATE_SELECT);
	 if(ucOsdState==FAC_USER)
	 OSDLine(FM_ROW_USER, 0, FM_COL_R, 0x74, BYTE_COLOR);
        break;
    }
}

//-----------------------------------------------------------
void FMColorState(BYTE y, BYTE Def_R, BYTE state)       // 0 : Clear   1 : Select  2 : Adjust
{
    BYTE x = (ucOsdState - Def_R) * 4 + FM_COL_R;
    BYTE len;
    
    if(ucOsdState - Def_R == 3)   // return item
        len = 6;
    else len = 3;
    if(state == 0)
        CLR_SUBITEM(x,y,len);
    else if(state == 1)
        SUBITEM_STATE1(x,y,len);
    else 
        SUBITEM_STATE2(x,y,len);
  }
//-----------------------------------------------------------
//-----------------------------------------------------------
void FMColorAdjLR(BYTE LR)
{
    // Change Value Only
    switch(ucOsdState)
    {
    case FAC_OFFSET_R:
	 SET_KEYREPEATENABLE();	
        stAdcData.AdcOffset[_RED] = ValueInRangeChange(0,255,stAdcData.AdcOffset[_RED],LR,0);
        CAdjustAdcOffset();
        ucOsdEventMsg = _SAVE_EE_ADCDATA_MSG;
        break;
        
    case FAC_OFFSET_G:
	 SET_KEYREPEATENABLE();	
        stAdcData.AdcOffset[_GREEN] = ValueInRangeChange(0,255,stAdcData.AdcOffset[_GREEN],LR,0);
        CAdjustAdcOffset();
        ucOsdEventMsg = _SAVE_EE_ADCDATA_MSG;
        break;
        
    case FAC_OFFSET_B:
	 SET_KEYREPEATENABLE();	
        stAdcData.AdcOffset[_BLUE] = ValueInRangeChange(0,255,stAdcData.AdcOffset[_BLUE],LR,0);
        CAdjustAdcOffset();
        ucOsdEventMsg = _SAVE_EE_ADCDATA_MSG;
        break;
        
    case FAC_GAIN_R:
	 SET_KEYREPEATENABLE();	
        stAdcData.AdcGain[_RED] = ValueInRangeChange(0,255,stAdcData.AdcGain[_RED],LR,0);
        CAdjustAdcGain();
        ucOsdEventMsg = _SAVE_EE_ADCDATA_MSG;
        break;
        
    case FAC_GAIN_G:
	 SET_KEYREPEATENABLE();	
        stAdcData.AdcGain[_GREEN] = ValueInRangeChange(0,255,stAdcData.AdcGain[_GREEN],LR,0);
        CAdjustAdcGain();
        ucOsdEventMsg = _SAVE_EE_ADCDATA_MSG;
        break;
        
    case FAC_GAIN_B:
	 SET_KEYREPEATENABLE();	
        stAdcData.AdcGain[_BLUE] = ValueInRangeChange(0,255,stAdcData.AdcGain[_BLUE],LR,0);
        CAdjustAdcGain();
        ucOsdEventMsg = _SAVE_EE_ADCDATA_MSG;
        break;
        
    case FAC_9300_R:
    case FAC_6500_R:
    case FAC_USER_R:
	 SET_KEYREPEATENABLE();	
        stColorTempData.ColorTemp[_RED] = ValueInRangeChange(0,255,stColorTempData.ColorTemp[_RED],LR,0);
        CAdjustContrast();
        ucOsdEventMsg = _SAVE_EE_COLORPROC1_MSG;
        break;
        
    case FAC_9300_G:
    case FAC_6500_G:
    case FAC_USER_G:
	 SET_KEYREPEATENABLE();	
        stColorTempData.ColorTemp[_GREEN] = ValueInRangeChange(0,255,stColorTempData.ColorTemp[_GREEN],LR,0);
        CAdjustContrast();
        ucOsdEventMsg = _SAVE_EE_COLORPROC1_MSG;
        break;
        
    case FAC_9300_B:
    case FAC_6500_B:
    case FAC_USER_B:
	 SET_KEYREPEATENABLE();	
        stColorTempData.ColorTemp[_BLUE] = ValueInRangeChange(0,255,stColorTempData.ColorTemp[_BLUE],LR,0);
        CAdjustContrast();
        ucOsdEventMsg = _SAVE_EE_COLORPROC1_MSG;
        break;
    }
    
    // Draw Curr Data
    switch(ucOsdState)
    {
    case FAC_OFFSET_R:    OUTPUT_OFFSET_R();    break;
    case FAC_OFFSET_G:    OUTPUT_OFFSET_G();    break;
    case FAC_OFFSET_B:    OUTPUT_OFFSET_B();    break;
    case FAC_GAIN_R:      OUTPUT_GAIN_R();      break;
    case FAC_GAIN_G:      OUTPUT_GAIN_G();      break;
    case FAC_GAIN_B:      OUTPUT_GAIN_B();      break;
    case FAC_9300_R:      OUTPUT_9300_R();      break;
    case FAC_9300_G:      OUTPUT_9300_G();      break;
    case FAC_9300_B:      OUTPUT_9300_B();      break;
    case FAC_6500_R:      OUTPUT_6500_R();      break;
    case FAC_6500_G:      OUTPUT_6500_G();      break;
    case FAC_6500_B:      OUTPUT_6500_B();      break;
    case FAC_USER_R:      OUTPUT_USER_R();      break;
    case FAC_USER_G:      OUTPUT_USER_G();      break;
    case FAC_USER_B:      OUTPUT_USER_B();      break;
    }
}
//-----------------------------------------------------------
#endif        //#if(FACTORY_MENU_EN)

