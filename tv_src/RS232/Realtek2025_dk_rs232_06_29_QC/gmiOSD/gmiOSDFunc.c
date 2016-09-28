#define __OSD_FUNC__
#include "Header\Include.h"

#if(_NEW_OSD_FUNC)
 
#if(_OSD_TYPE == _OSD007)
//---------------------------------------------------------------------------
// Set Character width
#if(_USE_RTD2120_EXTEND_32K_FOR_OSD == _ON)
void CSetCharacterWidth(const BYTE x, const BYTE y, const BYTE xdata *Text)
#else
void CSetCharacterWidth(const BYTE x, const BYTE y, const BYTE code *Text)
#endif
{          
    BYTE ucLength    = StrLen(Text);
    BYTE ucCharWidth = 12;
    BYTE ucCWidthCount = 0;
    BYTE uctemp = 0;

    uctemp = ucLength;
    Gotoxy(x,y,BYTE_ATTRIB);

    CScalerSendAddr(_OSD_DATA_PORT_92, _WRITE, _NON_AUTOINC);
    while(ucLength--)
    {
         if (*Text < 0x7B)     // Font public
            ucCharWidth = tFntGlobalPixelWidth[*Text] | 0x80;
	 else
	   {
	     if( (GET_LANGUAGE == LNG_CHI_S)|| (GET_LANGUAGE == LNG_CHI_T))
	     {
                if(*Text < 0xA8) // Font chinese public
               ucCharWidth = tFntGlobalChiWidth[(*Text) - 0x7B] | 0x80;
               else
                 {                     // Font chinese s
                   if (GET_LANGUAGE == LNG_CHI_S)
                        ucCharWidth = tFntGlobalChiSWidth[(*Text) - 0xA8] | 0x80;
                    else if (GET_LANGUAGE == LNG_CHI_T)              // Font chinese t
                        ucCharWidth = tFntGlobalChiTWidth[(*Text) - 0xA8] | 0x80;
                 }
	       }
	  else if( (GET_LANGUAGE == LNG_KOREAN)|| (GET_LANGUAGE == LNG_RUSS))
                        ucCharWidth = 12 | 0x80;
	  else if(GET_LANGUAGE==LNG_ARABIC)
	  	        ucCharWidth = tFntGlobalARABICWidth[(*Text) - 0x7B] | 0x80;;
	 }
         CScalerSendByte(ucCharWidth);
         Text++;
    }
    CScalerSendWriteStop(); 

#if(1) // eric 1226 add   
    if (ucCWidthCount)
    {
        // BYTE0
        Gotoxy(uctemp+x,y,THE_BYTE0);
        OutputChar(0x40);
    
        // BYTE 1
        Gotoxy(uctemp+x,y,THE_BYTE1);
        OutputChar(ucCWidthCount);
    }
#endif

}
#endif
 
//---------------------------------------------------------------------------
#if(_USE_RTD2120_EXTEND_32K_FOR_OSD == _ON)
void Textout(BYTE xdata *Text)
#else
void Textout(BYTE code *Text)
#endif
{
     CScalerSendAddr(_OSD_DATA_PORT_92, _WRITE, _NON_AUTOINC);
     while(*Text != 0)
     {
          CScalerSendByte(*Text);
          Text++;
     }
     CScalerSendWriteStop();
}
         
//---------------------------------------------------------------------------
#if(_USE_RTD2120_EXTEND_32K_FOR_OSD == _ON)
void CenterTextout(BYTE xdata *Text, BYTE x, BYTE y)
#else
void CenterTextout(BYTE code *Text, BYTE x, BYTE y)
#endif
{
    BYTE Len = StrLen(Text);

	if(Len/2 >= x)
	{
		x = 0;
	}
	else
	{
		x = x - Len/2;
	}

     Gotoxy(x,y,THE_BYTE1);
     Textout(Text); 

#if(_OSD_TYPE == _OSD007)
     CSetCharacterWidth(x, y, Text);
#endif
}

//---------------------------------------------------------------------------
#if(_USE_RTD2120_EXTEND_32K_FOR_OSD == _ON)
void CLeftAlignTextout(BYTE xdata *Text, BYTE x, BYTE y)
#else
void CLeftAlignTextout(BYTE code *Text, BYTE x, BYTE y)
#endif
{
    Gotoxy(x,y,THE_BYTE1);
    Textout(Text);

#if(_OSD_TYPE == _OSD007)
    CSetCharacterWidth(x, y, Text);
#endif
}

//-------------------------------------------------------------------------------------------------------
// OSD_Position : Restore OSD position according to global settings
// para : OSD font parameter
// OSD_GLOBAL_BLINK    : 0x10
// OSD_DISP_ZONE_LEFT  : 0x04
// OSD_DISP_ZONE_RIGHT : 0x08
// OSD_ROTATE          : 0x02
// OSD_ENABLE          : 0x01
//---------------------------------------------------------------------------
void OSDPosition(WORD usOsdActWidth, WORD usOsdActHeight, BYTE ucHPos, BYTE ucVPos, BYTE ucPar)
{
    if(ucHPos > 100)
        ucHPos = 50;

    if(ucVPos > 100)
        ucVPos = 50;

    usOsdActWidth  = _OSD_HPOSITION_OFFSET + Panel.DHStartPos / 4 + ((DWORD)(ucHPos)*((Panel.DHWidth )/4 -usOsdActWidth/4 - 4)) / 100;
    usOsdActHeight = _OSD_VPOSITION_OFFSET + Panel.DVStartPos / 4 + ((DWORD)(ucVPos)*((CCalcPanelDVEnd() - Panel.DVStartPos)/4 - usOsdActHeight/4 - 6)) / 100;

    CScalerSetBit(_OSD_SCRAMBLE_93, 0xf8, 0x02);

    pData[0] = CScalerGetBit(_OVERLAY_CTRL_6C, _BIT0);

    pData[0] = (pData[0] == 0x00) ? 0xc0 : 0xe0;
    pData[1] = 0x00;
    CScalerWrite(_OSD_ADDR_MSB_90, 2, pData, _AUTOINC);

    pData[0] = usOsdActHeight >> 1;
    pData[1] = (BYTE)(usOsdActWidth >> 2);
    pData[2] = ((BYTE)(usOsdActWidth & 0x0003) << 6) | ((usOsdActHeight & 0x01) << 5) | ucPar;
    CScalerWrite(_OSD_DATA_PORT_92, 3, pData, _NON_AUTOINC);
 
    CTimerWaitForEvent(_EVENT_DEN_STOP);
    CTimerWaitForEvent(_EVENT_DEN_STOP);
    CScalerSetBit(_OSD_SCRAMBLE_93, 0xf8, 0x05);
}

//---------------------------------------------------------------------------
void OSDLine(BYTE row, BYTE col, BYTE length, BYTE value, BYTE TheByte)
{
    Gotoxy(col,row,TheByte);

    if(TheByte == ALL_BYTE)    
       length *= 3;

    CScalerSendAddr(_OSD_DATA_PORT_92, _WRITE, _NON_AUTOINC);
    while(length)
    {
         CScalerSendByte(value);
         length--;
    }
    CScalerSendWriteStop();
}

//---------------------------------------------------------------------------
void OSDClear(BYTE row_start, BYTE height,
              BYTE col_start, BYTE width,
              BYTE Value, BYTE indicate)
{
    if (height)
    {
        do
        {
            OSDLine(row_start, col_start, width, Value, indicate);
            row_start++;
        }
        while (--height);
    }
}

//---------------------------------------------------------------------------
void OutputDisplaySize()
{
    CShowNumber(stModeInfo.IHWidth, 0);
    OutputChar(0x00);  // " "
    OutputChar(0x5b);  // "X"
    OutputChar(0x00);  // " "
    CShowNumber(stModeInfo.IVHeight, 0);
}

//---------------------------------------------------------------------------------------------------------------------
void OutputRefrushRate()
{
    CShowNumber((stModeInfo.IVFreq/10), 0);
    OutputChar('H');  // " "
    OutputChar('Z');  // " "
}

//---------------------------------------------------------------------------------------------------------------------
void COsdFxCodeWrite(BYTE code *pArray)
{
    BYTE cnt, temp;

    CScalerWrite(_OSD_ADDR_MSB_90, 2, pArray, _AUTOINC);
    pArray += 2;

    cnt = 0;

    while(_TRUE)
    {
        if(*pArray == _EXT_)
        {
            CScalerWrite(_OSD_DATA_PORT_92, cnt, pArray - cnt, _NON_AUTOINC);
            cnt = 0;

            if(*(pArray + 1) > 3)
                return;

            temp = _EXT_ + *(pArray + 1);

            if(*(pArray + 2) == _REPEAT_)
            {
                CScalerWriteAmount(_OSD_DATA_PORT_92, *(pArray + 3), temp, _NON_AUTOINC);
                pArray += 4;
            }
            else
            {
                CScalerWrite(_OSD_DATA_PORT_92, 1, &temp, _NON_AUTOINC);
                pArray += 2;
            }
        }
        else if(*pArray == _REPEAT_)
        {
            CScalerWrite(_OSD_DATA_PORT_92, cnt, pArray - cnt, _NON_AUTOINC);

            CScalerWriteAmount(_OSD_DATA_PORT_92, *(pArray + 1) - 1, *(pArray - 1), _NON_AUTOINC);

            pArray += 2;
            cnt = 0;
        }
        else if(*pArray == _NEXT_)
        {
            CScalerWrite(_OSD_DATA_PORT_92, cnt, pArray - cnt, _NON_AUTOINC);
            pArray++;
            cnt = 0;

            if(*(pArray + 1) != _END_)
            {
                CScalerWrite(_OSD_ADDR_MSB_90, 2, pArray, _AUTOINC);
                pArray += 2;
            }
            else
            {
                break;
            }
        }
        else if(*(pArray) == _END_)
        {
            CScalerWrite(_OSD_DATA_PORT_92, cnt, pArray - cnt, _NON_AUTOINC);
            break;
        }
        else
        {
            pArray++;
            cnt++;
        }
    }
}

//--------------------------------------------------
//--------------------------------------------------
void COsdFxEnableOsd(void)
{
    CTimerWaitForEvent(_EVENT_DEN_STOP);
    CScalerSetBit(_OVERLAY_CTRL_6C, ~_BIT0, _BIT0);
	SET_DO_SHOW_NOTE(0);
}

//--------------------------------------------------
void COsdFxDisableOsd(void)
{
    CTimerWaitForEvent(_EVENT_DEN_STOP);
    CScalerSetBit(_OVERLAY_CTRL_6C, ~_BIT0, 0x00);
    OSDClear(0, ROW_COUNT, 0 , COL_WIDTH, 0x00, BYTE_DISPLAY);
    CLR_KEYREPEATENABLE();

    ucOsdState   = _MENU_NONE;  // eric 1220 add for osd position err
    ucOSDAdjTemp = 0;
#if(_AUTO_POWER_DOWN && _VIDEO_TV_SUPPORT)
    bTimerOnScreen = 0;
#endif    

#if(_LOGO_EN && _LOGO_TYPE == _LOGO_TYPE1)
    bLogoOnScreen = 0;
#endif            
}

//--------------------------------------------------
void COsdFxDrawWindow(WORD usXStart, WORD usYStart, WORD usXEnd, WORD usYEnd, BYTE *pStyle)
{
    BYTE cnt0, cnt1;

    cnt0    = CScalerGetBit(_OVERLAY_CTRL_6C, _BIT0);

    pData[0]    = (cnt0 == 0x00) ? 0xc1 : 0xe1;
    pData[1]    = ((*(pStyle)) * 4) + 1;
    CScalerWrite(_OSD_ADDR_MSB_90, 2, pData, _AUTOINC);

    pData[0]    = ((usXStart & 0x03F) << 2);
    pData[1]    = (((usYStart & 0x007) << 5) | ((usXStart & 0x7C0) >> 6));
    pData[2]    = (usYStart >> 3);
    pData[3]    = ((usXEnd & 0x03F) << 2);
    pData[4]    = (((usYEnd & 0x007) << 5) | ((usXEnd & 0x7C0) >> 6));
    pData[5]    = (usYEnd >> 3);
    CScalerWrite(_OSD_DATA_PORT_92, 6, pData, _NON_AUTOINC);

    CTimerDelayXms(40);

    for(cnt1=0;cnt1<2;cnt1++)
    {	
        pData[0]    = 0xc1;
        pData[1]    = ((*(pStyle)) * 4) + (cnt1 * 3);
        CScalerWrite(_OSD_ADDR_MSB_90, 2, pData, _AUTOINC);

        for(cnt0=0;cnt0<3;cnt0++)
            pData[cnt0]   = (*(pStyle + ((cnt1 * 3) + cnt0) + 1));

        CScalerWrite(_OSD_DATA_PORT_92, 3, pData, _NON_AUTOINC);
    }
}

#if(_VGA_SUPPORT)
//--------------------------------------------------
WORD COsdFxGetAdcClockRange(BYTE ucPar)
{
    WORD delta;

    if(ucPar == _GET_CLOCKRANGE_MAX)
    {
        CAdjustCheckAdcClockRange(stModeUserCenterData.CenterClock, &delta);

        if(delta > _CLOCK_BIAS)
            return (stModeUserCenterData.CenterClock + _CLOCK_BIAS);
        else
            return (stModeUserCenterData.CenterClock + delta);
    }
    else if(ucPar == _GET_CLOCKRANGE_MIN)
    {
        CAdjustCheckAdcClockRange(stModeUserCenterData.CenterClock, &delta);

        if(delta > _CLOCK_BIAS)
            return (stModeUserCenterData.CenterClock - _CLOCK_BIAS);
        else
            return (stModeUserCenterData.CenterClock - delta);
    }
}
#endif

//---------------------------------------------------------------------------
#if(_USE_RTD2120_EXTEND_32K_FOR_OSD == _ON)
BYTE StrLen(BYTE xdata *Str)
#else
BYTE StrLen(BYTE code *Str)
#endif
{
    BYTE i = 0;

    while(*Str != 0)
    {
        i++;
        Str++;
    }

    return i;
}

//----------------------------------------------------------------------------------------------------
#if(_VGA_SUPPORT)
BYTE ClockGuage(void)
{
      WORD iMin;
      WORD  iTmp;

      iMin = COsdFxGetAdcClockRange(_GET_CLOCKRANGE_MIN);
      iTmp = (stModeUserData.Clock - iMin) * 100 / (COsdFxGetAdcClockRange(_GET_CLOCKRANGE_MAX) - iMin);

      return (BYTE)iTmp;
}

//----------------------------------------------------------------------------------------------------
BYTE HPosGuage(void)
{
      WORD ucMin = stModeUserCenterData.CenterHPos - _HPOSITION_BIAS;
      WORD iTmp  = (stModeUserData.HPosition - ucMin) * 100 / (_HPOSITION_BIAS * 2);

      return (BYTE)iTmp;
}

//----------------------------------------------------------------------------------------------------
BYTE VPosGuage(void)
{
      WORD ucMin = stModeUserCenterData.CenterVPos - _VPOSITION_BIAS;
      WORD iTmp  = (stModeUserData.VPosition - ucMin) * 100 / (_VPOSITION_BIAS * 2);

      return (BYTE)iTmp;
}
#endif

//----------------------------------------------------------------------------------------------------
void DoReset()
{
     BYTE ucLanguage = GET_LANGUAGE;
     BYTE ucFacLanguage = _GET_FAC_OSD_LANGUAGE();
   // BYTE ucVolume=stOsdUserData.Volume;
	BYTE ucDispMode=_GET_DISPLAY_MODE();
	//BYTE unOsdMode=_GET_OSD_SIZE();
#if(_VIDEO_TV_SUPPORT)
    BYTE ucCurrentChannel = stVDCColor.CurrentChannel;
    BYTE ChannelColorType= CLoadChannelColorType(stVDCColor.CurrentChannel);
#endif

    CEepromLoadDefault(0);

#if(_VIDEO_SUPPORT)
    if (CGetInputSourceNum(_GET_INPUT_SOURCE()) == 2)  // Source video
    {
        BYTE ucField = (CHECK60HZ()) ? 1 : 0;
        stModeInfo.IHTotal      = tVIDEO_TABLE_INPUT_INFO[ucField][0];
        stModeInfo.IHStartPos   = tVIDEO_TABLE_INPUT_INFO[ucField][1];
        stModeInfo.IHWidth      = tVIDEO_TABLE_INPUT_INFO[ucField][2];
        stModeInfo.IVStartPos   = tVIDEO_TABLE_INPUT_INFO[ucField][3];
        stModeInfo.IVHeight     = tVIDEO_TABLE_INPUT_INFO[ucField][4];
        
        stDisplayInfo.DHWidth   = CCalcPanelDHEnd(1)  - Panel.DHStartPos;
        stDisplayInfo.DVHeight  = CCalcPanelDVEnd() - Panel.DVStartPos;
        stDisplayInfo.DVStartPos = Panel.DVStartPos;
    }
#endif

#if(LANGUAGE_SAVE_ENABLE)
     if(GET_LANGUAGE  !=ucFacLanguage)
     	{
	_SET_FAC_OSD_LANGUAGE(ucFacLanguage);
	SET_LANGUAGE(ucFacLanguage);
	LoadLanguageFont();
     	}
#else
        SET_LANGUAGE(ucLanguage);
#endif
	//stOsdUserData.Volume=ucVolume;
#if(_VIDEO_TV_SUPPORT)
    stVDCColor.CurrentChannel = ucCurrentChannel;
    CSaveChannelColorType(stVDCColor.CurrentChannel, ChannelColorType);
#endif
    CEepromSaveOsdUserData();
    CEepromSaveSystemData();
	
    CAdjustBrightness();
    CAdjustContrast();
    CAdjustBacklight();
	
#if(_FACTORY_MENU_EN)
	if(ucOsdState == FAC_RESET)
         return;
#endif	

#if(_VIDEO_SUPPORT)
    switch(_GET_INPUT_SOURCE())
    {
        case _SOURCE_VIDEO_AV:
        case _SOURCE_VIDEO_SV:
        case _SOURCE_VIDEO_YUV:
        case _SOURCE_VIDEO_TV:
        case _SOURCE_VIDEO_SCART:
        case _SOURCE_VIDEO_DVD:
            SET_COLOR_TEMP_TYPE(_CT_USER);
            CEepromLoadBriConData();
            CEepromLoadColorTempData();
            CSetVDCSaturation(stConBriData.Saturation);
            if (CHECK60HZ())     // NTSC
                gmi_CAdjustVDCHue(stConBriData.Hue);
            else
                gmi_CAdjustVDCHue(50);
            break;
    }
#endif
#if(_OSD_TYPE == _OSD007)
  #if(_IMAGE_COLOR_MODE)
    CSetColorMode(_GET_IMAGE_COLOR_MODE());
  #endif
#endif

#if (_VIDEO_TV_SUPPORT)
        CRecallTVData();
#endif

    if (_GET_INPUT_SOURCE() == _SOURCE_VGA || _GET_INPUT_SOURCE() == _SOURCE_DVI)
    {
        CAdjustAdcGainOffset();

        if (_GET_INPUT_SOURCE() == _SOURCE_VGA)
        {
            CAdjustAdcClock(stModeUserData.Clock);
            CAdjustPhase(stModeUserData.Phase);
            CAdjustHPosition();
            CAdjustVPosition();
        }
       
    }
/*
#if(_OSD_TYPE == _OSD007)
  #if(_ALPHA_BLENDING_ADJ || _OSD_DISPLAY_SIZE_ADJ)
  if((Panel.DHWidth>=1024)&&(Panel.DVHeight>=850)) //0411
    CSetOSDTransAndSize();
  #endif
     if (_GET_OSD_SIZE()) 
        OSDPosition(_OSD_DOUBLE_WIDTH(_MAIN_WINDOW_WIDTH), _OSD_DOUBLE_HEIGHT(_MAIN_WINDOW_HEIGHT), stOsdUserData.OsdHPos+(_MAINMENU_DOUBLE_H_OFFSET), stOsdUserData.OsdVPos+(_MAINMENU_DOUBLE_V_OFFSET), 0x03);
      else
        OSDPosition(_MAIN_WINDOW_WIDTH, _MAIN_WINDOW_HEIGHT, stOsdUserData.OsdHPos+(_MAINMENU_H_OFFSET), stOsdUserData.OsdVPos+(_MAINMENU_V_OFFSET), 0x03);

#endif

{
#if(_VIDEO_SUPPORT)
    switch(_GET_INPUT_SOURCE())
    {
        case _SOURCE_VIDEO_AV:
        case _SOURCE_VIDEO_SV:
        case _SOURCE_VIDEO_YUV:
        case _SOURCE_VIDEO_TV:
        case _SOURCE_VIDEO_SCART:
    case _SOURCE_VIDEO_DVD:
                   CSetVideoColor();break;
             default: break;
}
#endif

}

    CClearSubItem();

    CDrawOtherFuncPage();
*/
  if(ucDispMode!=_GET_DISPLAY_MODE())
  	{
       _SET_DISPLAY_MODE(0);
	CEepromSaveOsdUserData();
  	}
  
     _SET_INPUT_SOURCE(_SOURCE_VIDEO_TV);
    ucOsdEventMsg       = _DO_SHOW_NOTE;
    SET_DO_SHOW_NOTE(0);
    ucCurrState         = _SOURCE_CHANGE_STATE;
    #if(_IR_ENABLE)
    ucDetectIR_Cmd = 0;
    #endif
#if(_CHANGE_SOURCE_BACKGROUCD_COLOR == _BLUE_COLOR)
            CAdjustBackgroundColor(0x00, 0x00, 0xff);
#else
            CAdjustBackgroundColor(0x00, 0x00, 0x00);
#endif
            CScalerSetBit(_VDISP_CTRL_28, ~(_BIT5 | _BIT3), (_BIT5)); // Set normal display
            MUTE_ON();
	bVideoON = 0;
	ucVideoNoModeTime = 252;
    CEepromSaveOsdUserData();
    CEepromSaveSystemData();
	CModeResetMode();   
    ucAudioState = 1;

}

//---------------------------------------------
#if(_BURNIN_EN)
bit ucInitBurnIn=1;	
void InitBurnIn()
{     
     CModeSetFreeRun();
     CAdjustBackgroundColor(0x00,0x00,0x00);
     CPowerPanelOn();
}

//---------------------------------------------
void BurnInRun()
{
     static BYTE ucBurnInColor = 0;
	 static BYTE ucBurnInRunCount = 0;
	static bit     ucBurnInLed=0;
     BYTE R = 0;
     BYTE G = 0;
     BYTE B = 0;

	 ucBurnInRunCount++;
	 if(ucBurnInRunCount < 100)
	 {

	 	return;
	 }
	 ucBurnInRunCount = 0;

     if(ucBurnInColor & 0x80)
     {
         if(ucBurnInColor & 0x01)     R = 0xff;
         if(ucBurnInColor & 0x02)     G = 0xff;
         if(ucBurnInColor & 0x04)     B = 0xff;
     }
     else
     {
         if(ucBurnInColor & 0x01)     R = 0x7f;
         if(ucBurnInColor & 0x02)     G = 0x7f;
         if(ucBurnInColor & 0x04)     B = 0x7f;
     }
     CAdjustBackgroundColor(R,G,B);
     ucBurnInColor++;
	 CScalerSetBit(_VDISP_CTRL_28, ~_BIT5, _BIT5);
	if(ucBurnInLed)
		{
	ucBurnInLed=0;	
	 CPowerLedRed();
		}
       else		
       	{
	ucBurnInLed=1;	
	 CPowerLedGreen(); 
       	}
}
//---------------------------------------------

#endif   // if(BURNIN_EN)

#endif        //#if(OSD_TYPE == OSD01)





/*  OSD Window Templet
//BASE ADDRESS + 000 Shadow/Border/Gradient
SB_THICKNESS(1) | SB_HEIGHT(1) ,
SHADOW_COLOR(1) | BORDER_COLOR(2),
R_GRADIENT_POLARITY_DEC |
  G_GRADIENT_POLARITY_INC |
  B_GRADIENT_POLARITY_DEC |
  GRADIENT_LEVEL(1) |
  R_COLOR_GRADIENT_EN(1) |
  G_COLOR_GRADIENT_EN(1) |
  B_COLOR_GRADIENT_EN(1),

//BASE ADDRESS + 001 START POSITION
W_START_POS(10,300),
//BASE ADDRESS + 002 END POSITION
W_END_POS(20,350),

//BASE ADDRESS + 003  Control
RESERVED,
GRADIENT_PER_LEVEL(2) | WINDOW_COLOR(3),

GRADIENT_FUNCTION_EN(1) |
  GRADIENT_DIRECTION_HOR |
  SHADOW_BORDER_EN(1) |
  WINDOW_TYPE(WT_3DBUTTON_TYPE1) |
  WINDOW_ENABLE(1),

*/

