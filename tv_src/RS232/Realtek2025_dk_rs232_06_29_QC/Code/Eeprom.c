//----------------------------------------------------------------------------------------------------
// ID Code      : Eeprom.c No.0003
// Update Note  : 
//
//----------------------------------------------------------------------------------------------------

#define __EEPROM__

#include "Header\Include.h"


//--------------------------------------------------
// Description  : Eeprom check at firmware startup
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CEepromStartupCheck(void)
{
    bit bRCallAllData = 0;
    BYTE cnt;

    //This delay is for Eeprom power rising time when the connector plug in (VGA_5V or DVI_5V).
    CTimerDelayXms(20);

    for(cnt=0;cnt<2;cnt++)
    {
        CEepromRead(_EEPROM_PAGE3_BANK1 + 126, 2, pData);
        if((pData[0] == (_VERSION_CODE))&&(pData[1] == (POWERUPSTATE+(_NTSC_SEARCH_TABLE<<2) + (_INPUTSOURCE<<3))))    break;
    }

    if((pData[0] != (_VERSION_CODE))||(pData[1] != (POWERUPSTATE+(_NTSC_SEARCH_TABLE<<2) + (_INPUTSOURCE<<3))))
    {
        bRCallAllData = 1;
    }
    else
    {
        CEepromLoadSystemData();
        CEepromLoadOsdUserData();
        CEepromLoadAdcData();
        CEepromLoadBriConData();
        CEepromLoadColorTempData();
#if(_DDC_TYPE == _DDC_MTV512)
        CEepromLoadEDIDData();
#endif

        #if(_VIDEO_SUPPORT)
        CEepromLoadVedioColor();
        #endif    //#if(_VIDEO_SUPPORT)
    }

#if (_VIDEO_SUPPORT)
    if (stConBriData.Brightness > 100 || stConBriData.Contrast > 100 || stConBriData.Saturation > 100)
        bRCallAllData = 1;
#else
    if (stConBriData.Brightness > 100 || stConBriData.Contrast > 100)
        bRCallAllData = 1;
#endif

    if (bRCallAllData)
    {
        CEepromLoadDefault(1);

#if (_VIDEO_TV_SUPPORT)
        CRecallTVData();
#endif

        pData[0] = (_VERSION_CODE);
        pData[1] = (POWERUPSTATE+(_NTSC_SEARCH_TABLE<<2) + (_INPUTSOURCE<<3));
        CEepromWrite(_EEPROM_PAGE3_BANK1 + 126, 2, pData);
    }
	else
		{
#if(_NTSC_SEARCH_TABLE)
#if (_VIDEO_TV_SUPPORT)
          ucTVType=CLoadChannelColorType(stVDCColor.CurrentChannel);
        if(ucTVType!=_TV_NTSC_M&&ucTVType!=_TV_PAL_N&&ucTVType!=_TV_PAL_M)
        CRecallTVData();
#endif
#endif
    }
    _SET_POWER_DOWN_TIME(0);
}

//--------------------------------------------------
// Description  : Load eeprom default
// Input Value  : None
// Output Value : None
//--------------------------------------------------
#if (_VIDEO_TV_SUPPORT)
void CRecallTVData(void)
{
    BYTE ucCount = 0;

    // Reset Max channel number
    pData[0] = 0;
    CI2cWrite(_TV_MAX_CHANNEL_EEPROM_ADDR, _MAX_CHANNEL_ADDR, 1, pData);
  
    // Recall freq/tv type/sound type
    ucTVType = _NORMAL_TV_TYPE;
    for(ucCount = 0; ucCount < (_MAX_CHANNEL_COUNT+1); ucCount++)
    {
      //  CSaveChannelData(_MIN_FREQ | 0x8000, 0, ucCount);
        CSaveChannelData((WORD)_MAX_FREQ | 0x8000, 0, ucCount);
    } 
}
#endif

//--------------------------------------------------
// Description  : Load eeprom default
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CEepromLoadDefault(BYTE ucMode)
{

    BYTE ucInputSource = _GET_INPUT_SOURCE();


    StructModeUserFIFODataType stFIFOModeTemp;

	//when enable the Factory OSD, can not reset the factory data


    if (1)//1 == ucMode || ucInputSource == _SOURCE_VGA || ucInputSource == _SOURCE_DVI)
    {
        if((GET_MODE_SEARCH_TYPE() == _USER_MODE_TYPE) && (stModeInfo.ModeCurr < 16))
        {
            CEepromLoadUserFIFOModeData((stModeInfo.ModeCurr / 4), pData);
            stFIFOModeTemp.ModeNum = pData[(stModeInfo.ModeCurr % 4) * 4];
        }
    
        CEepromInitialModeData();
        CEepromInitialCenterModeData();
        CEepromInitialUserFIFOModeData();
    }

    CEepromLoadSystemDataDefault();
    CEepromLoadOsdUserDataDefault();
    CEepromLoadBriConDataDefault();

    if (1)//1 == ucMode || ucInputSource == _SOURCE_VGA || ucInputSource == _SOURCE_DVI)
    {
        CEepromLoadAdcDataDefault();
        CEepromLoadColorTempDataDefault();
    }

#if(_DDC_TYPE == _DDC_MTV512)
    CEepromLoadEDIDDataDefault();
#endif

#if(_VIDEO_SUPPORT)
    if (1)//1 == ucMode || ucInputSource != _SOURCE_VGA && ucInputSource != _SOURCE_DVI)
    {
        CEepromLoadVedioColorDefault();
    }
#endif

    if (1)//1 == ucMode || ucInputSource == _SOURCE_VGA || ucInputSource == _SOURCE_DVI)
    {
        if((GET_MODE_SEARCH_TYPE() == _USER_MODE_TYPE) && (stModeInfo.ModeCurr < 16))
        {
            if(stSystemData.UserFIFOMode >= 15)
                stSystemData.UserFIFOMode = 0;
            else
                stSystemData.UserFIFOMode++;
    
            stFIFOModeTemp.IHFreq  = stModeInfo.IHFreq;
            stFIFOModeTemp.IVFreq  = stModeInfo.IVFreq;
            CEepromSaveUserFIFOModeData(stFIFOModeTemp);
    
            stModeUserData.FirstAuto    = 0;
            stModeUserData.HPosition    = tINPUTMODE_PRESET_TABLE[stFIFOModeTemp.ModeNum].IHStartPos;
            stModeUserData.VPosition    = tINPUTMODE_PRESET_TABLE[stFIFOModeTemp.ModeNum].IVStartPos;
            stModeUserData.Clock        = tINPUTMODE_PRESET_TABLE[stFIFOModeTemp.ModeNum].IHTotal;
            stModeUserData.Phase        = 0;
            CEepromSaveModeData(stSystemData.UserFIFOMode);
    
            stModeInfo.ModeCurr = stSystemData.UserFIFOMode;
        }
        else if((GET_MODE_SEARCH_TYPE() == _PRESET_MODE_TYPE) && (stModeInfo.ModeCurr < _MAX_PRESET_MODE))
        {
            CEepromLoadModeData(stModeInfo.ModeCurr);
        }
    }

   if (0 == ucMode)
   {
       _SET_INPUT_SOURCE(ucInputSource);
       CEepromSaveSystemData();
   }
}

//--------------------------------------------------
// Description  : Eeprom write function
// Input Value  : usAddr        --> absolute address
//                usLength      --> Numbers of data we want to write
//                pWriteArray   --> Writing data array
// Output Value : Return _SUCCESS if succeed
//--------------------------------------------------
bit CEepromWrite(WORD usAddr, WORD usLength, BYTE *pWriteArray)
{
    return CI2cWrite(_EEPROM_ADDRESS + (BYTE)((usAddr & 0xff00) >> 7), (BYTE)(usAddr & 0x00ff), usLength, pWriteArray);
}

//--------------------------------------------------
// Description  : Eeprom read function
// Input Value  : usAddr        --> absolute address
//                usLength      --> Numbers of data we want to read
//                pReadArray    --> Result array
// Output Value : Return _SUCCESS if succeed
//--------------------------------------------------
bit CEepromRead(WORD usAddr, WORD usLength, BYTE *pReadArray)
{
    return CI2cRead(_EEPROM_ADDRESS + (BYTE)((usAddr & 0xff00) >> 7), (BYTE)(usAddr & 0x00ff), usLength, pReadArray);
}

//----------------------------------------------------------------------------------------------------

//--------------------------------------------------
// Description  : Save mode setting data, such as FirstAuto,
//                HPosition, VPosition, Clock and Phase.
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CEepromSaveModeData(BYTE ucMode)
{
    if(GET_MODE_SEARCH_TYPE() == _PRESET_MODE_TYPE)
    {
        CEepromWrite(_MODE_DATA_0_ADDRESS + (WORD)ucMode * 8, sizeof(StructModeUserDataType), &stModeUserData.FirstAuto);
    }
    else if(GET_MODE_SEARCH_TYPE() == _USER_MODE_TYPE)
    {
        CEepromWrite(_USER_FIFO_MODE_DATA_1_ADDRESS + (WORD)ucMode * 8, sizeof(StructModeUserDataType), &stModeUserData.FirstAuto);
    }
}

//--------------------------------------------------
// Description  : Load mode setting data, such as FirstAuto,
//                HPosition, VPosition, Clock and Phase.
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CEepromLoadModeData(BYTE ucMode)
{
    if(GET_MODE_SEARCH_TYPE() == _PRESET_MODE_TYPE)
    {
        if(CEepromRead(_MODE_DATA_0_ADDRESS + (WORD)ucMode * 8, sizeof(StructModeUserDataType), &stModeUserData.FirstAuto) == _FAIL)
        {
            stModeUserData.FirstAuto    = 0;
            stModeUserData.HPosition    = stModeInfo.IHStartPos;
            stModeUserData.VPosition    = stModeInfo.IVStartPos;
            stModeUserData.Clock        = stModeInfo.IHTotal;
            stModeUserData.Phase        = 0;
        }
    }
    else if(GET_MODE_SEARCH_TYPE() == _USER_MODE_TYPE)
    {
        if(CEepromRead(_USER_FIFO_MODE_DATA_1_ADDRESS + (WORD)ucMode * 8, sizeof(StructModeUserDataType), &stModeUserData.FirstAuto) == _FAIL)
        {
            stModeUserData.FirstAuto    = 0;
            stModeUserData.HPosition    = stModeInfo.IHStartPos;
            stModeUserData.VPosition    = stModeInfo.IVStartPos;
            stModeUserData.Clock        = stModeInfo.IHTotal;
            stModeUserData.Phase        = 0;
        }
    }
}

//--------------------------------------------------
// Description  : Initial mode setting data with defaults
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CEepromInitialModeData(void)
{
    BYTE modecnt, modetype;

    modetype = GET_MODE_SEARCH_TYPE();
    SET_MODE_SEARCH_TYPE(_PRESET_MODE_TYPE);

    for(modecnt=0;modecnt<_MAX_PRESET_MODE;modecnt++)
    {
        stModeUserData.FirstAuto    = 0;
        stModeUserData.HPosition    = tINPUTMODE_PRESET_TABLE[modecnt].IHStartPos;
        stModeUserData.VPosition    = tINPUTMODE_PRESET_TABLE[modecnt].IVStartPos;
        stModeUserData.Clock        = tINPUTMODE_PRESET_TABLE[modecnt].IHTotal;
        stModeUserData.Phase        = 0;

        CEepromSaveModeData(modecnt);
    }

    for(modecnt=0;modecnt<8;modecnt++)
    {
        CEepromWrite(_USER_FIFO_MODE_DATA_1_ADDRESS + (modecnt * 16), 16, tEEPROM_USER_FIFO_MODE_DEFAULT);
    }

    SET_MODE_SEARCH_TYPE(modetype);
}

//----------------------------------------------------------------------------------------------------

//--------------------------------------------------
// Description  : Save user FIFO mode data, such as ModeNum,
//                IHFreq, IVFreq.
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CEepromSaveUserFIFOModeData(StructModeUserFIFODataType stUserFIFOMode)
{
    stUserFIFOMode.IHFreq = ((stUserFIFOMode.IVFreq & 0x0f00) << 4) | (stUserFIFOMode.IHFreq & 0x0fff);
    stUserFIFOMode.IVFreq = ((stUserFIFOMode.IVFreq & 0x00ff) << 8);

    CEepromWrite(_USER_FIFO_MODE_DATA_0_ADDRESS + (stSystemData.UserFIFOMode * 4), 4, &stUserFIFOMode.ModeNum);
}

//--------------------------------------------------
// Description  : Load 4 sets of user FIFO mode data.
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CEepromLoadUserFIFOModeData(BYTE ucNum, BYTE *pArray)
{
    CEepromRead(_USER_FIFO_MODE_DATA_0_ADDRESS + (ucNum * 16), 16, pArray);
}

//--------------------------------------------------
// Description  : Initial user FIFO mode data with defaults
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CEepromInitialUserFIFOModeData(void)
{
    BYTE modecnt;

    for(modecnt=0;modecnt<4;modecnt++)
    {
        CEepromWrite(_USER_FIFO_MODE_DATA_0_ADDRESS + (modecnt * 16), 16, tEEPROM_USER_FIFO_MODE_DEFAULT);
    }
}

//----------------------------------------------------------------------------------------------------

//--------------------------------------------------
// Description  : 
//                
// Input Value  : 
// Output Value : None
//--------------------------------------------------
void CEepromSaveCenterModeData(BYTE ucMode)
{
    if(GET_MODE_SEARCH_TYPE() == _PRESET_MODE_TYPE)
    {
        CEepromWrite(_MODE_CENTER_DATA_ADDRESS + (WORD)ucMode * 8, sizeof(StructModeUserCenterDataType), (BYTE *)&stModeUserCenterData.CenterHPos);
    }
    else if(GET_MODE_SEARCH_TYPE() == _USER_MODE_TYPE)
    {
        CEepromWrite(_MODE_CENTER_DATA_ADDRESS + (WORD)_MAX_PRESET_MODE * 8 + (WORD)ucMode * 8, sizeof(StructModeUserCenterDataType), (BYTE *)&stModeUserCenterData.CenterHPos);
    }
}

//--------------------------------------------------
// Description  : 
//                
// Input Value  : 
// Output Value : None
//--------------------------------------------------
void CEepromLoadCenterModeData(BYTE ucMode)
{
    if(GET_MODE_SEARCH_TYPE() == _PRESET_MODE_TYPE)
    {
        if(CEepromRead(_MODE_CENTER_DATA_ADDRESS + (WORD)ucMode * 8, sizeof(StructModeUserCenterDataType), (BYTE *)&stModeUserCenterData.CenterHPos) == _FAIL)
        {
            stModeUserCenterData.CenterHPos     = stModeInfo.IHStartPos;
            stModeUserCenterData.CenterVPos     = stModeInfo.IVStartPos;
            stModeUserCenterData.CenterClock    = stModeInfo.IHTotal;
        }
    }
    else if(GET_MODE_SEARCH_TYPE() == _USER_MODE_TYPE)
    {
        if(CEepromRead(_MODE_CENTER_DATA_ADDRESS + (WORD)_MAX_PRESET_MODE * 8 + (WORD)ucMode * 8, sizeof(StructModeUserCenterDataType), (BYTE *)&stModeUserCenterData.CenterHPos) == _FAIL) //V308 modify
        {
            stModeUserCenterData.CenterHPos     = stModeInfo.IHStartPos;
            stModeUserCenterData.CenterVPos     = stModeInfo.IVStartPos;
            stModeUserCenterData.CenterClock    = stModeInfo.IHTotal;
        }
    }
}

//--------------------------------------------------
// Description  : Initial mode setting data with defaults
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CEepromInitialCenterModeData(void)
{
    BYTE modecnt, modetype;

    modetype = GET_MODE_SEARCH_TYPE();
    SET_MODE_SEARCH_TYPE(_PRESET_MODE_TYPE);

    for(modecnt=0;modecnt<_MAX_PRESET_MODE;modecnt++)
    {
        stModeUserCenterData.CenterHPos     = tINPUTMODE_PRESET_TABLE[modecnt].IHStartPos;
        stModeUserCenterData.CenterVPos     = tINPUTMODE_PRESET_TABLE[modecnt].IVStartPos;
        stModeUserCenterData.CenterClock    = tINPUTMODE_PRESET_TABLE[modecnt].IHTotal;

        CEepromSaveCenterModeData(modecnt);
    }
       
    for(modecnt=0;modecnt<8;modecnt++)
    {
        CEepromWrite(_MODE_CENTER_DATA_ADDRESS + (WORD)_MAX_PRESET_MODE * 8 + ((WORD)modecnt * 16), 16, tEEPROM_USER_FIFO_MODE_DEFAULT);
    }    

    SET_MODE_SEARCH_TYPE(modetype);
}

//----------------------------------------------------------------------------------------------------

//--------------------------------------------------
// Description  : Save system data
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CEepromSaveSystemData(void)
{
    CEepromWrite(_SYSTEM_DATA_ADDRESS, sizeof(StructSystemDataType), &stSystemData.MonitorFlag);
}

//--------------------------------------------------
// Description  : Load system data
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CEepromLoadSystemData(void)
{
    CEepromRead(_SYSTEM_DATA_ADDRESS, sizeof(StructSystemDataType), &stSystemData.MonitorFlag);
}

//--------------------------------------------------
// Description  : Load default system data
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CEepromLoadSystemDataDefault(void)
{
    CEepromWrite(_SYSTEM_DATA_ADDRESS, sizeof(StructSystemDataType), &tEEPROM_SYSTEM_DATA.MonitorFlag);
    stSystemData = tEEPROM_SYSTEM_DATA;
}

//----------------------------------------------------------------------------------------------------

//--------------------------------------------------
// Description  : Save OSD data
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CEepromSaveOsdUserData(void)
{
    CEepromWrite(_OSDUSER_DATA_ADDRESS, sizeof(StructOsdUserDataType), &stOsdUserData.OsdSettingFlag);
}

//--------------------------------------------------
// Description  : Load OSD data
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CEepromLoadOsdUserData(void)
{
    CEepromRead(_OSDUSER_DATA_ADDRESS, sizeof(StructOsdUserDataType), &stOsdUserData.OsdSettingFlag);
}

//--------------------------------------------------
// Description  : Load default OSD data
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CEepromLoadOsdUserDataDefault(void)
{
    CEepromWrite(_OSDUSER_DATA_ADDRESS, sizeof(StructOsdUserDataType), &tEEPROM_OSDUSER_DATA.OsdSettingFlag);
    stOsdUserData = tEEPROM_OSDUSER_DATA;
}

//----------------------------------------------------------------------------------------------------

//--------------------------------------------------
// Description  : Save ADC data
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CEepromSaveAdcData(void)
{

    if(_GET_INPUT_SOURCE() == _SOURCE_VGA) 
    {
        CEepromWrite(_VGA_ADC_DATA_ADDRESS, sizeof(StructAdcDataType), &stAdcData.AdcGain[_RED]);
        CEepromWrite(_VGA_ADC_DATA_ADDRESS + sizeof(StructAdcDataType), 1, &ucAdcPGA);
    }
    else if(_GET_INPUT_SOURCE() == _SOURCE_YPBPR)
    {
        CEepromWrite(_YPbPr_ADC_DATA_ADDRESS , sizeof(StructAdcDataType), &stAdcData.AdcGain[_RED]);
        CEepromWrite(_YPbPr_ADC_DATA_ADDRESS + sizeof(StructAdcDataType), 1, &ucAdcPGA);
    }
	else
    {
        CEepromWrite(_VIDEO_ADC_DATA_ADDRESS, sizeof(StructAdcDataType), &stAdcData.AdcGain[_RED]);
        CEepromWrite(_VIDEO_ADC_DATA_ADDRESS + sizeof(StructAdcDataType), 1, &ucAdcPGA);
    }
}

//--------------------------------------------------
// Description  : Load ADC data
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CEepromLoadAdcData(void)
{

    if(_GET_INPUT_SOURCE() == _SOURCE_VGA) 
    {
        CEepromRead(_VGA_ADC_DATA_ADDRESS, sizeof(StructAdcDataType), &stAdcData.AdcGain[_RED]);
        CEepromRead(_VGA_ADC_DATA_ADDRESS + sizeof(StructAdcDataType), 1, &ucAdcPGA);
    }
    else if(_GET_INPUT_SOURCE() == _SOURCE_YPBPR)
    {
        CEepromRead(_YPbPr_ADC_DATA_ADDRESS , sizeof(StructAdcDataType), &stAdcData.AdcGain[_RED]);
        CEepromRead(_YPbPr_ADC_DATA_ADDRESS + sizeof(StructAdcDataType), 1, &ucAdcPGA);
    }
    else
    {
        CEepromRead(_VIDEO_ADC_DATA_ADDRESS, sizeof(StructAdcDataType), &stAdcData.AdcGain[_RED]);
        CEepromRead(_VIDEO_ADC_DATA_ADDRESS + sizeof(StructAdcDataType), 1, &ucAdcPGA);
    }
}

//--------------------------------------------------
// Description  : Load default ADC data
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CEepromLoadAdcDataDefault(void)
{
    stAdcData = tEEPROM_ADC_DATA_VGA;
    ucAdcPGA = 0x05;

    CEepromWrite(_VGA_ADC_DATA_ADDRESS, sizeof(StructAdcDataType), &tEEPROM_ADC_DATA_VGA.AdcGain[_RED]);
    CEepromWrite(_VGA_ADC_DATA_ADDRESS + sizeof(StructAdcDataType), 1, &ucAdcPGA);
    stAdcData = tEEPROM_ADC_DATA_YPbPr;
    CEepromWrite(_YPbPr_ADC_DATA_ADDRESS , sizeof(StructAdcDataType), &tEEPROM_ADC_DATA_YPbPr.AdcGain[_RED]);
    CEepromWrite(_YPbPr_ADC_DATA_ADDRESS + sizeof(StructAdcDataType) , 1, &ucAdcPGA);
    stAdcData = tEEPROM_ADC_DATA_VIDEO;
    CEepromWrite(_VIDEO_ADC_DATA_ADDRESS , sizeof(StructAdcDataType), &tEEPROM_ADC_DATA_VIDEO.AdcGain[_RED]);
    CEepromWrite(_VIDEO_ADC_DATA_ADDRESS + sizeof(StructAdcDataType) , 1, &ucAdcPGA);

}

//----------------------------------------------------------------------------------------------------
//--------------------------------------------------
BYTE CGetInputSourceNum(BYTE ucInputSource)
{
    switch(ucInputSource)
    {
        default:
        case _SOURCE_YPBPR:
        case _SOURCE_VGA:
            return 0;

#if(_TMDS_SUPPORT || _HDMI_SUPPORT)
        case _SOURCE_DVI:
        case _SOURCE_HDMI:
            return 1;
#endif

#if(_VIDEO_SUPPORT)
        case _SOURCE_VIDEO_AV:
        case _SOURCE_VIDEO_SV:
      //  case _SOURCE_VIDEO_YUV:
        case _SOURCE_VIDEO_TV:
        case _SOURCE_VIDEO_SCART:
	 case _SOURCE_VIDEO_DVD:
            return 2;
#endif
   }
}

//--------------------------------------------------
// Description  : Save Brightness/Contrast data
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CEepromSaveBriConData(void)
{
 //   CEepromWrite(_BriConHueSat_PROC0_ADDRESS + (CGetInputSourceNum(_GET_INPUT_SOURCE())) * 2, 2, &stConBriData.Brightness);
    switch(_GET_INPUT_SOURCE())
    {
        case _SOURCE_VGA:
            CEepromWrite(_BriConHueSat_PROC0_ADDRESS + 0 * 4, 4, &stConBriData.Brightness);
            break;
        case _SOURCE_VIDEO_AV:
            CEepromWrite(_BriConHueSat_PROC0_ADDRESS + 1 * 4, 4, &stConBriData.Brightness);
            break;
        case _SOURCE_VIDEO_SV:
             CEepromWrite(_BriConHueSat_PROC0_ADDRESS + 2 * 4, 4, &stConBriData.Brightness);
            break;
        case _SOURCE_VIDEO_TV:
            CEepromWrite(_BriConHueSat_PROC0_ADDRESS + 3 * 4, 4, &stConBriData.Brightness);
            break;
       case _SOURCE_VIDEO_DVD:
       case _SOURCE_VIDEO_SCART:
            CEepromWrite(_BriConHueSat_PROC0_ADDRESS + 4 * 4, 4, &stConBriData.Brightness);
            break;
   }
	
}

//--------------------------------------------------
// Description  : Load Brightness/Contrast data
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CEepromLoadBriConData(void)
{
//    CEepromRead(_BriConHueSat_PROC0_ADDRESS + (CGetInputSourceNum(_GET_INPUT_SOURCE())) * 2, 2, &stConBriData.Brightness);
    switch(_GET_INPUT_SOURCE())
    {
        case _SOURCE_VGA:
            CEepromRead(_BriConHueSat_PROC0_ADDRESS + 0 * 4, 4, &stConBriData.Brightness);
            break;
        case _SOURCE_VIDEO_AV:
            CEepromRead(_BriConHueSat_PROC0_ADDRESS + 1 * 4, 4, &stConBriData.Brightness);
            break;
        case _SOURCE_VIDEO_SV:
             CEepromRead(_BriConHueSat_PROC0_ADDRESS + 2 * 4, 4, &stConBriData.Brightness);
            break;
        case _SOURCE_VIDEO_TV:
            CEepromRead(_BriConHueSat_PROC0_ADDRESS + 3 * 4, 4, &stConBriData.Brightness);
            break;
       case _SOURCE_VIDEO_DVD:
       case _SOURCE_VIDEO_SCART:
            CEepromRead(_BriConHueSat_PROC0_ADDRESS + 4 * 4, 4, &stConBriData.Brightness);
            break;
   }
    stSystemData.BackLight = BRIGHTNESS_GUAGE;
}

//--------------------------------------------------
// Description  : Load default Brightness/Contrast data
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CEepromLoadBriConDataDefault(void)
{
    CEepromWrite(_BriConHueSat_PROC0_ADDRESS, 4 * 5, &tEEPROM_COLOR_PROC0_DATA[0].Brightness);
    CEepromLoadBriConData();
}

//----------------------------------------------------------------------------------------------------

//--------------------------------------------------
// Description  : Save Color Temperature data
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CEepromSaveColorTempData(void)
{
    CEepromWrite(_COLORTEMP_DATA_ADDRESS + 9 * CGetInputSourceNum(_GET_INPUT_SOURCE()) + 3 * GET_COLOR_TEMP_TYPE(), 3, &stColorTempData.ColorTemp[_RED]);
}

//--------------------------------------------------
// Description  : Load Color Temperature data
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CEepromLoadColorTempData(void)
{
    CEepromRead(_COLORTEMP_DATA_ADDRESS + 9 * CGetInputSourceNum(_GET_INPUT_SOURCE()) + 3 * GET_COLOR_TEMP_TYPE(), 3, &stColorTempData.ColorTemp[_RED]);
}

//--------------------------------------------------
// Description  : Load default Color Temperature data
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CEepromLoadColorTempDataDefault(void)
{
    CEepromWrite(_COLORTEMP_DATA_ADDRESS, 9 * 3, &tEEPROM_COLORTEMP_DATA[0].ColorTemp9300Red);
    CEepromLoadColorTempData();
}

//----------------------------------------------------------------------------------------------------
#if(_DDC_TYPE == _DDC_MTV512)
/*
//--------------------------------------------------
// Description  : Load EDID data (MTV512)
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CEepromSaveEDIDData(void)
{
    CEepromWrite(_EDID0_ADDRESS, 128, &MCU_DDCRAM_0[0]);
    CEepromWrite(_EDID1_ADDRESS, 128, &MCU_DDCRAM_1[0]);
}
*/
//--------------------------------------------------
// Description  : Load EDID data (MTV512)
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CEepromLoadEDIDData(void)
{
#if((_MCU_TYPE == _MYSON_MTV512) || (_MCU_TYPE == _RTD_2120))

    CEepromRead(_EDID0_ADDRESS, 128, &MCU_DDCRAM_0[0]);
    CEepromRead(_EDID1_ADDRESS, 128, &MCU_DDCRAM_1[0]);

#endif

}

//--------------------------------------------------
// Description  : Load EDID data (MTV512)
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CEepromLoadEDIDDataDefault(void)
{
#if((_MCU_TYPE == _MYSON_MTV512) || (_MCU_TYPE == _RTD_2120))

    CEepromWrite(_EDID0_ADDRESS, 128, &tEDID_TABLE_VGA[0]);
    CEepromWrite(_EDID1_ADDRESS, 128, &tEDID_TABLE_DVI[0]);
    CEepromLoadEDIDData();

#endif
}
#endif  // End of #if(_MCU_TYPE == _MYSON_MTV512)
//----------------------------------------------------------------------------------------------------
#if(_VIDEO_SUPPORT)

void CEepromLoadVedioColor(void)
{
     CEepromRead(_VIDEO_DATA_ADDRESS, sizeof(StructVDCColor), &stVDCColor.CurrentChannel);
}
//----------------------------------------------------------------------------------------------------
void CEepromSaveVedioColor(void)
{
     CEepromWrite(_VIDEO_DATA_ADDRESS, sizeof(StructVDCColor), &stVDCColor.CurrentChannel);
}
//----------------------------------------------------------------------------------------------------
void CEepromLoadVedioColorDefault(void)
{
    stVDCColor = tVDCColorDefault;
    CEepromWrite(_VIDEO_DATA_ADDRESS, sizeof(StructVDCColor), &stVDCColor.CurrentChannel);
    CEepromLoadVedioColor();
}   
#endif    //#if(_VIDEO_SUPPORT)
//----------------------------------------------------------------------------------------------------



