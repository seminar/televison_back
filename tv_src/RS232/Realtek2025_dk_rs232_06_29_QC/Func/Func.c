#define __FUNCC__

#include "Header\Include.h"

#if((_VIDEO_CHIP == _VDC_TB1334) && (_SCALER_TYPE == _RTD2023L || _SCALER_TYPE == _RTD2525L || _SCALER_TYPE == _RTD2547D))
extern void gmi_ChangeInputToVGA(void);
#endif

//---------------------------------------------
#if(VOLUME_CTRL_TYPE == _SOUND_PWM)
//---------------------------------------------
void MUTE_ON()
{                                    
    // Set Mute
    if(_VOLUME_INV)         CSetPWM(bVOLUME_PWM,0xff);
    else                    CSetPWM(bVOLUME_PWM,0x00);

    bMUTE = _MUTE_ON;
}

//---------------------------------------------
void MUTE_OFF(void)
{
    bMUTE = _MUTE_OFF;
}
/*
//---------------------------------------------
WORD code VOL_PWE[]=
{
1,
2,	
8,
13,
17,
22,
27,
30,
33,
36,

39,
41,	
43,
45,
46,
48,
50,
52,
54,
56,

57,
58,	
59,
60,
61,
62,
63,
64,
65,
65,

67,
68,
69,
70,
74,
77,
80,
83,
86,
89,

92,
96,
107,
111,
114,
118,
122,
126,
130,
134,


138,//50,
120+18,//50,
120+18,//50,
122+18,//50,
122+18,//50,
122+18,//50,
124+18,//50,
124+18,//50,
124+18,//50,
126+18,//50,

126+18,//50,
126+18,//50,
128+18,//50,
128+18,//50,
128+18,//50,
131+18,//50,
131+18,//50,
134+18,//50,
134+18,//50,
134+18,//50,

137+18,
137+18,
137+18,
139+18,
139+18,
139+18,
141+18,
141+18,
141+18,
144+18,

144+18,
144+18,
144+18,
145+18,
145+18,
145+18,
145+18,
146+18,
146+18,
146+18,

147+18,
147+18,
147+18,
148+18,
148+18,
167,
167,
167,
168,
168,

168,

};
*/
#define CPWM_volume_1       184
#define CPWM_volume_25      160
#define CPWM_volume_75       80
#define CPWM_volume_100     35
#define CPWM_TV_volume_100     28


void CSetVolume()
{
    WORD iVolume;

    if((stOsdUserData.Volume == 0) || (GET_MUTE_STATE() == STATE_MUTEON))
    {
         if(_VOLUME_INV)         CSetPWM(bVOLUME_PWM,0xff);
         else                    CSetPWM(bVOLUME_PWM,0x00);
         return;
    }
	
	   
         if(_GET_INPUT_SOURCE()==_SOURCE_VIDEO_TV)
         	{
         	if(stOsdUserData.Volume<=25)
         		{
	               iVolume = (25*CPWM_volume_1 +(CPWM_volume_25-CPWM_volume_1)*(stOsdUserData.Volume))/25 ;
         		}
		else
			{
			if(stOsdUserData.Volume<=75)
		               iVolume = (50*CPWM_volume_25 +(CPWM_volume_75-CPWM_volume_25)*(stOsdUserData.Volume-25))/50 ;
			else
		               iVolume = (25*CPWM_volume_75 +(CPWM_TV_volume_100-CPWM_volume_75)*(stOsdUserData.Volume-75))/25 ;
			}
         	}		 
	 else
	 	{
         	if(stOsdUserData.Volume<=25)
         		{
	               iVolume = (25*CPWM_volume_1 +(CPWM_volume_25-CPWM_volume_1)*(stOsdUserData.Volume))/25 ;
         		}
		else
			{
			if(stOsdUserData.Volume<=75)
		               iVolume = (50*CPWM_volume_25 +(CPWM_volume_75-CPWM_volume_25)*(stOsdUserData.Volume-25))/50 ;
			else
		               iVolume = (25*CPWM_volume_75 +(CPWM_volume_100-CPWM_volume_75)*(stOsdUserData.Volume-75))/25 ;
			}
	 	}
	 
    CSetPWM(bVOLUME_PWM,iVolume);
}
//---------------------------------------------
#endif    // #if(VOLUME_CTRL_TYPE == _SOUND_PWM)

#if(VOLUME_CTRL_TYPE == _SOUND_SC7313)
//---------------------------------------------
void MUTE_ON()
{
    CSetSc7313Volume(0);
    CSc7313MuteOn();
}

//---------------------------------------------
void MUTE_OFF(void)
{
    bMUTE = _MUTE_OFF;
}
//---------------------------------------------
void CSetVolume()
{
     if((GET_MUTE_STATE() == STATE_MUTEON) || (stOsdUserData.Volume == 0))
     {
         MUTE_ON();
         return;
     }
    
     CSetSc7313Volume(stOsdUserData.Volume);

     if (bMUTE)
         MUTE_OFF();
}

//---------------------------------------------
#endif          //#if(VOLUME_CTRL_TYPE == _SOUND_SC7313)

//---------------------------------------------

void CInitSoundChannel()
{
     MUTE_ON();

     switch(_GET_INPUT_SOURCE())
     {
#if(_VGA_SUPPORT)
         case _SOURCE_VGA:
   #if(VOLUME_CTRL_TYPE == _SOUND_SC7313)
             CSelect7313SoundChannel(0x01);
   #elif(VOLUME_CTRL_TYPE == _SOUND_PWM)  
             _AUDIO_A = 1;
             _AUDIO_B = 0;                      
   #endif
             break;
                     
         case _SOURCE_HDMI:
         case _SOURCE_DVI:              
   #if(VOLUME_CTRL_TYPE == _SOUND_SC7313)
             CSelect7313SoundChannel(0x01);
   #elif(VOLUME_CTRL_TYPE == _SOUND_PWM)  
             _AUDIO_A = 0;
             _AUDIO_B = 1;                      
   #endif
             break;
#endif

#if(_VIDEO_SUPPORT)
         case _SOURCE_VIDEO_AV:
         case _SOURCE_VIDEO_SV:        
   #if(VOLUME_CTRL_TYPE == _SOUND_SC7313)
             CSelect7313SoundChannel(0x02);
   #elif(VOLUME_CTRL_TYPE == _SOUND_PWM)  
             _AUDIO_A = 0;
             _AUDIO_B = 0;                      
   #endif
             break;
#endif
  
         case _SOURCE_VIDEO_YUV:
   #if(VOLUME_CTRL_TYPE == _SOUND_SC7313)
             CSelect7313SoundChannel(0x03);  // Only for PT2314
   #elif(VOLUME_CTRL_TYPE == _SOUND_PWM)  
          //   _AUDIO_A = 0;
            // _AUDIO_B = 0;                      
   #endif
        break;

#if(_VIDEO_TV_SUPPORT)
         case _SOURCE_VIDEO_TV:        
   #if(VOLUME_CTRL_TYPE == _SOUND_SC7313)
             CSelect7313SoundChannel(0x00);
   #elif(VOLUME_CTRL_TYPE == _SOUND_PWM)  
             _AUDIO_A = 0;
             _AUDIO_B = 1;                      
   #endif
             break;
#endif

#if(_VIDEO_SCART_SUPPORT)
        case _SOURCE_VIDEO_SCART:
   #if(VOLUME_CTRL_TYPE == _SOUND_SC7313)
             CSelect7313SoundChannel(0x00);
   #elif(VOLUME_CTRL_TYPE == _SOUND_PWM)  
             _AUDIO_A = 1;
             _AUDIO_B = 0;                      
   #endif
            break;                  
#endif 

#if(DVD_EN)
         case _SOURCE_VIDEO_DVD:        
  
             _AUDIO_A = 1;
             _AUDIO_B = 1;                      
            break;                  
#endif 
     }
}

WORD code ucSourceMask = (_VGA_SUPPORT_EN << _SOURCE_VGA)                 | 
                         (_TMDS_SUPPORT << _SOURCE_DVI)                |
                         (_HDMI_SUPPORT << _SOURCE_HDMI)               |
                         (_VIDEO_AV_SUPPORT_EN << _SOURCE_VIDEO_AV)       |
                         (_VIDEO_SV_SUPPORT_EN << _SOURCE_VIDEO_SV)       |
#if(DVD_EN)                         
                         (1 << _SOURCE_VIDEO_DVD) |
#else
                         (0 << _SOURCE_VIDEO_DVD) |
#endif
                         (_VIDEO_TV_SUPPORT_EN << _SOURCE_VIDEO_TV)       |
                         (_VIDEO_SCART_SUPPORT << _SOURCE_VIDEO_SCART) |
                         (_YPBPR_SUPPORT << _SOURCE_YPBPR);

void ChangeSource(void)//BYTE ucCurrentSource)
{
     bit bSourceChange = 0;
     WORD i;
     WORD ucMask = ucSourceMask >> (_GET_INPUT_SOURCE() + 1);

     //Find next source   
     for(i = _GET_INPUT_SOURCE() + 1; i < _INPUT_PORT_MAX; i++)
     {
         if(ucMask & 0x01)
         {
             _SET_INPUT_SOURCE(i);
             bSourceChange = 1;
             break;
         }
         ucMask >>= 1;
     }

     if (0 == bSourceChange) // Source not change
     {
         ucMask = ucSourceMask;
         for(i = 0; i < _GET_INPUT_SOURCE(); i++)
         {
             if(ucMask & 0x01)     
             {         
                 _SET_INPUT_SOURCE(i);
                 bSourceChange = 1;
                 break;
             }
             ucMask >>= 1;
         }
     }
	 
#if(_CHANGE_SOURCE_BACKGROUCD_COLOR == _BLUE_COLOR)
            CAdjustBackgroundColor(0x00, 0x00, 0xff);
#else
            CAdjustBackgroundColor(0x00, 0x00, 0x00);
#endif
            CScalerSetBit(_VDISP_CTRL_28, ~(_BIT5 | _BIT3), (_BIT5)); // Set normal display
            MUTE_ON();

#if(_CHANGE_SOURCE_METHOD == _CHANGE_SOURCE_METHOD_1)
     CInitInputSource();
#endif
}
//---------------------------------------------
void CInitInputSource()
{
#if(_VIDEO_SUPPORT == _ON)  // Only use for video8

  #if(_VIDEO_TV_SUPPORT)
//    TUNER_PWR_OFF();
  #endif
	#if(DVD_EN)
        bDVD_PWR_OFF() ;
	#endif
#if(_VIDEO_SUPPORT && _VIDEO_CHIP == _VDC_TB1334)
    gmi_CI2CWriteVDCByte(0x0D, 0x02);
    VideoDecAddress = 0;  // Only select 0,for TB1334 source AV/SV
#endif


    switch(_GET_INPUT_SOURCE()) 
    {
    case _SOURCE_VGA:
	#if(DVD_EN)
        bDVD_PWR_OFF() ;
	#endif
#if((_VIDEO_CHIP == _VDC_TB1334) && (_SCALER_TYPE == _RTD2023L || _SCALER_TYPE == _RTD2525L || _SCALER_TYPE == _RTD2547D))
  #if(_SCALER_TYPE == _RTD2547D)
        CScalerSetBit(_IPH_ACT_WID_H_16, ~(_BIT6 | _BIT5 | _BIT4), ((_ADC_INPUT_SWAP_RG << 6) | (_ADC_INPUT_SWAP_RB << 5) | (_ADC_INPUT_SWAP_GB << 4)));
  #else
        CScalerSetBit(_IPH_ACT_WID_H_0B, ~(_BIT6 | _BIT5 | _BIT4), ((_ADC_INPUT_SWAP_RG << 6) | (_ADC_INPUT_SWAP_RB << 5) | (_ADC_INPUT_SWAP_GB << 4)));
  #endif

        gmi_ChangeInputToVGA();
#endif
        break;

#if(_SCALER_TYPE == _RTD2547D)
    case _SOURCE_YPBPR:
    #if(_VIDEO_CHIP == _VDC_TB1334)
        CScalerSetBit(_IPH_ACT_WID_H_16, ~(_BIT6 | _BIT5 | _BIT4), ((_ADC_INPUT_SWAP_RG << 6) | (_ADC_INPUT_SWAP_RB << 5) | (_ADC_INPUT_SWAP_GB << 4)));
        gmi_ChangeInputToVGA();
    #endif

        break;
#endif

    case _SOURCE_VIDEO_AV:
	#if(DVD_EN)
        bDVD_PWR_OFF() ;
	#endif
        if (bVideoON)
        {
            gmi_CSelectInputChannel(_AV_CHANNEL, _NONE_INPUT); // Select input channel AV
#if(_VIDEO_SUPPORT && _VIDEO_CHIP == _VDC_TB1334)
  //          CTimerDelayXms(50);  
#endif
        }
        break;

    case _SOURCE_VIDEO_SV:
	#if(DVD_EN)
        bDVD_PWR_OFF() ;
	#endif
        if (bVideoON)
            gmi_CSelectInputChannel(_SV_CHANNEL, _NONE_INPUT); // Select input channel SV
        break;

#if(_VIDEO_YUV_SUPPORT)
    case _SOURCE_VIDEO_YUV:
	#if(DVD_EN)
        bDVD_PWR_OFF() ;
	#endif
        if (bVideoON)
        {
  #if(_VIDEO_CHIP == _VDC_RTD2612)
    #if(_UART_TEST_MODE)
            gmi_CSelectInputChannel(_AV_CHANNEL, _NONE_INPUT); // Select input channel AV
    #else
        
            gmi_CSelectInputChannel(_YCBCR_CHANNEL_Y_CR, _YCBCR_CHANNEL_CB); // Select input channel SV
    #endif
  #elif(_VIDEO_CHIP == _VDC_TB1334)
            gmi_CSelectInputChannel(_YCBCR_CHANNEL, _NONE_INPUT); // Select input channel AV
  #endif   
        }
        break;
#endif

#if(_VIDEO_TV_SUPPORT)
    case _SOURCE_VIDEO_TV:
	#if(DVD_EN)
        bDVD_PWR_OFF() ;
	#endif
 #if(_VIDEO_CHIP == _VDC_TB1334)
        VideoDecAddress = 1; // Only select 1,for TB1334 source TV
 #endif
    CTimerDelayXms(50);
    CScalerSetBit(_SYNC_INVERT_48, ~(_BIT6 | _BIT1), (_BIT4 | _BIT2));
    CTimerDelayXms(50);
    CScalerSetBit(_SYNC_CTRL_49, ~_BIT6, 0x00);
        CInitTV();             
        if (bVideoON)
            gmi_CSelectInputChannel(_TV_CHANNEL, _NONE_INPUT); // Select input channel TV
        break;
#endif

#if(_VIDEO_SCART_SUPPORT)
    case _SOURCE_VIDEO_SCART:
	#if(DVD_EN)
        bDVD_PWR_OFF() ;
	#endif
        if (bVideoON)
            gmi_CSelectInputChannel(_SCART_CHANNEL, _NONE_INPUT); // Select input channel TV
        break;                  
#endif 
#if(DVD_EN)
    case _SOURCE_VIDEO_DVD:
         bDVD_PWR_ON();
        gmi_CSelectInputChannel(_DVD_CHANNEL,_NONE_INPUT); // Select input channel DVD
        break;
#endif

#if(_HDMI_SUPPORT == _ON)
    case _SOURCE_HDMI:
        CScalerSetByte(_YUV2RGB_CTRL_9C, 0x00);
        break;
#endif
    }       

#if(_VIDEO_TV_SUPPORT)
    ucVideoNoModeTime = 253;
#endif

#if(_AUTO_POWER_DOWN && _VIDEO_TV_SUPPORT)
 #if(_CHANGE_SOURCE_STORE_A_P_T == _DISABLE)
    ucMinuteCount       = 0;
    ucAutoPowerDownTime = _GET_POWER_DOWN_TIME() * 15;
    if (0 == ucAutoPowerDownTime) // Auto power down time off
    {
        ucAutoPowerDownTime = 0xff;
    }
 #endif   // end #if(_CHANGE_SOURCE_STORE_A_P_T == _DISABLE)
#endif    //#if(_AUTO_POWER_DOWN && _VIDEO_TV_SUPPORT)
#endif    //#if(_VIDEO_SUPPORT == _ON)  // Only use for video8
    
    CInitSoundChannel();

   CEepromLoadBriConData();
   CEepromLoadAdcData();
CEepromLoadColorTempData();
	}
//---------------------------------------------

