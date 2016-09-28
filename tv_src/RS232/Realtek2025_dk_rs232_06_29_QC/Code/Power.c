//----------------------------------------------------------------------------------------------------
// ID Code      : Power.c No.0003
// Update Note  : 
//
//----------------------------------------------------------------------------------------------------

#define __POWER__

#include "Header\Include.h"


//--------------------------------------------------
// Description  : Check if the power status changed
// Input Value  : None
// Output Value : Return _TRUE if power status is changed, _FALSE if not
//--------------------------------------------------
bit CPowerHandler(void)
{
#if(_AUTO_POWER_DOWN && _VIDEO_TV_SUPPORT)
    if(GET_POWERSWITCH() || ucAutoPowerDownTime == 0)
#else
    if(GET_POWERSWITCH())
#endif 
    {
        CPowerControl();
        CLR_POWERSWITCH();

        return _TRUE;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Execute power up/down process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CPowerControl(void)
{
    CModeResetMode();

#if(_AUTO_POWER_DOWN && _VIDEO_TV_SUPPORT)
    if(GET_POWERSTATUS() || ucAutoPowerDownTime == 0)       // Power Down Process
#else
    if(GET_POWERSTATUS())       // Power Down Process
#endif
    {
        CLR_KEYREPEATENABLE(); // Add for IR key repat problem
        CLR_POWERSTATUS();
        CPowerPanelOff();
        CPowerADCAPLLOff();
        CPowerLVDSOff();
        CPowerDPLLOff();
#if(_SCALER_TYPE == _RTD2547D)
        CPowerMPLLOff();
#endif
        CPowerPWMOff();
        CScalerDisableDisplayTiming();
        CPowerTMDSOff();
#if(_SCALER_TYPE == _RTD2553V || _SCALER_TYPE == _RTD2546N || _SCALER_TYPE == _RTD2525L) 
        CScalerSetBit(_HOST_CTRL_01, ~_BIT1, _BIT1); //V307 modify
#elif(_SCALER_TYPE == _RTD2547D)
        CScalerSetByte(_HOST_CTRL_01, 0x46);
#else
        CScalerSetByte(_HOST_CTRL_01, 0x02);
#endif

#if(_AUTO_POWER_DOWN && _VIDEO_TV_SUPPORT)
        ucAutoPowerDownTime = 0xff;
#endif

#if(_AUTO_POWER_DOWN && _VIDEO_TV_SUPPORT)
        if (_GET_INPUT_SOURCE() == _SOURCE_VIDEO_TV && ucAutoPowerDownTime == 0)
        {
          //  ucAutoPowerDownTime = 0xff;
        }
        else
#endif
        {
            CEepromSaveSystemData();
        }


#if(_VIDEO_SUPPORT)
        CPowerDownVDC();
        SET_MUTE_STATE(_MUTE_OFF);
    #if (_VIDEO_TV_SUPPORT)
    //    TUNER_PWR_OFF();
    #endif
#endif
#if(DVD_EN)
	     bDVD_PWR_OFF();//0208
#endif
    SET_MUTE_STATE(_MUTE_OFF);
    CEepromSaveOsdUserData();
#if(PowerDownLED==RedLED)			
		CPowerLedRed(); 
#elif(PowerDownLED==GreenLED)			
		CPowerLedGreen(); 
#elif(PowerDownLED==OrangeLED)			
		CPowerLedOrange(); 
#elif(PowerDownLED==BlackLED)			
		CPowerLedBlack(); 
#endif

    }
    else                        // Power Up Process
    {
#if(KeyPowerUpLED==RedLED)			
		CPowerLedRed(); 
#elif(KeyPowerUpLED==GreenLED)			
		CPowerLedGreen(); 
#elif(KeyPowerUpLED==OrangeLED)			
		CPowerLedOrange(); 
#elif(KeyPowerUpLED==BlackLED)			
		CPowerLedBlack(); 
#endif
#if(_AUTO_POWER_DOWN && _VIDEO_TV_SUPPORT)
		//when power on clear the auto power down
		_SET_POWER_DOWN_TIME(0);
        ucMinuteCount       = 0;
        ucAutoPowerDownTime = _GET_POWER_DOWN_TIME() * 15;
        if (0 == ucAutoPowerDownTime) // Auto power down time off
        {
            ucAutoPowerDownTime = 0xff;
        }

        ucVideoNoModeTime = 253;
#endif                                 

        CLR_KEYREPEATENABLE(); // Add for IR key repat problem
#if(_SCALER_TYPE != _RTD2547D)
        CModeResetMode();    // eric Marked by add RTD2547D
#endif
        SET_POWERSTATUS();
	CLR_POWERSWITCH() ;
        CScalerInitial();
   _SET_POWER_DOWN_TIME(0);
        CEepromSaveSystemData();

#if(_VIDEO_SUPPORT)
        bVideoON = 0;
#endif
#if(DVD_EN)
	     bDVD_PWR_OFF();//0208
#endif

  SET_MUTE_STATE(_MUTE_OFF);
    CEepromSaveOsdUserData();
   // if (_GET_INPUT_SOURCE() == _SOURCE_VIDEO_TV)
    {
        ucVideoNoModeTime=255;
		CModeResetMode();
}
   if(_GET_INPUT_SOURCE()==_SOURCE_VIDEO_DVD)
	bDVD_PWR_ON();
   	   SET_DO_SHOW_NOTE(0);
    }
}

//--------------------------------------------------
// Description  : Set panel on process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CPowerPanelOn(void)
{
    if(GET_PANELPOWERSTATUS() == _OFF)
    {
        CPowerPanelPowerOn();
        CTimerDelayXms(40);
        CPowerDisplayPortOn();
        CScalerEnableDisplayOutput();
        //CTimerDelayXms(80);
    }
   CTimerDelayXms(200);//modify by chenlinfu

#if(_VIDEO_SUPPORT)
    if (_GET_INPUT_SOURCE() == _SOURCE_VGA  || 
        _GET_INPUT_SOURCE() == _SOURCE_DVI  || 
        _GET_INPUT_SOURCE() == _SOURCE_HDMI || 
        _GET_INPUT_SOURCE() == _SOURCE_YPBPR) 
#endif
        CPowerLightPowerOn();

    CMiscClearStatusRegister();
}

//--------------------------------------------------
// Description  : Set panel off process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CPowerPanelOff(void)
{
    MUTE_ON();

    CPowerLightPowerOff();
    CTimerDelayXms(120);
    CScalerDisableDisplayOutput();
    CPowerPanelPowerOff();
    CTimerDelayXms(40);
    CPowerDisplayPortOff();

    // The delay below is to prevent from short period between panel OFF and next ON
    CTimerDelayXms(250);
}

//--------------------------------------------------
// Description  : Set panel power on
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CPowerPanelPowerOn(void)
{
    PANELPOWER_UP();
    SET_PANELPOWERSTATUS();
}

//--------------------------------------------------
// Description  : Set panel power off
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CPowerPanelPowerOff(void)
{
    PANELPOWER_DOWN();
    CLR_PANELPOWERSTATUS();
}
//--------------------------------------------------
// Description  : Set backlight power on
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CPowerLightPowerOn(void)
{
    LIGHTPOWER_UP();
    SET_LIGHTPOWERSTATUS();
}

//--------------------------------------------------
// Description  : Set backlight power off
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CPowerLightPowerOff(void)
{
    LIGHTPOWER_DOWN();
    CLR_LIGHTPOWERSTATUS();
}

//--------------------------------------------------
// Description  : Power on display port
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CPowerDisplayPortOn(void)
{
    switch(Panel.PanelStyle)
    {
        case _PANEL_TTL:
            CPowerLVDSOn();
            break;

        case _PANEL_LVDS:
            CPowerLVDSOn();
            break;

        case _PANEL_RSDS:
            CPowerRSDSOn();
            break;
    }
}

//--------------------------------------------------
// Description  : Power off display port
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CPowerDisplayPortOff(void)
{
    switch(Panel.PanelStyle)
    {
        case _PANEL_TTL:
                CPowerLVDSOff();
            break;

        case _PANEL_LVDS:
            CPowerLVDSOff();
            break;

        case _PANEL_RSDS:
            CPowerRSDSOff();
            break;
    }
}

//--------------------------------------------------
// Description  : Power on LVDS
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CPowerLVDSOn(void)
{    
#if(_SCALER_TYPE == _RTD2547D)
    CScalerSetDataPortByte(_TCON_ADDR_PORT_8B, _TCON_LVDS_CTRL0_A0, 0x30);
#else
    CScalerSetByte(_TCON_ADDR_PORT_8B, _LVDS_CTRL0_78);

#if (_SCALER_TYPE == _RTD2553V || _SCALER_TYPE == _RTD2546N || _SCALER_TYPE == _RTD2525L)
    CScalerSetByte(_TCON_DATA_PORT_8C, 0x30);
#else
    CScalerSetByte(_TCON_DATA_PORT_8C, 0xf0);
#endif
#endif // #if(_SCALER_TYPE == _RTD2547D)
}

//--------------------------------------------------
// Description  : Power off LVDS
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CPowerLVDSOff(void)
{
#if(_SCALER_TYPE == _RTD2547D)
    CScalerSetDataPortByte(_TCON_ADDR_PORT_8B, _TCON_LVDS_CTRL0_A0, 0x00);
#else
    CScalerSetByte(_TCON_ADDR_PORT_8B, _LVDS_CTRL0_78);
    CScalerSetByte(_TCON_DATA_PORT_8C, 0x00);
#endif
}

//--------------------------------------------------
// Description  : Power on RSDS
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CPowerRSDSOn(void)
{
    CPowerLVDSOn();
#if(_SCALER_TYPE == _RTD2547D)
    CScalerSetDataPortByte(_TCON_ADDR_PORT_8B, _TCON_CTRL0_00, 0xc6);//for 8-bit RSDS panel
    CTimerDelayXms(40);
    CScalerSetDataPortByte(_TCON_ADDR_PORT_8B, _TCON_CTRL0_00, 0x86);
#else
    CScalerSetByte(_TCON_ADDR_PORT_8B, 0x00);
    CScalerSetByte(_TCON_DATA_PORT_8C, 0xc3);
    CTimerDelayXms(40);
    CScalerSetByte(_TCON_ADDR_PORT_8B, 0x00);
    CScalerSetByte(_TCON_DATA_PORT_8C, 0x83);
#endif
}

//--------------------------------------------------
// Description  : Power off RSDS
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CPowerRSDSOff(void)
{
    CPowerLVDSOff();
#if(_SCALER_TYPE == _RTD2547D)
    CScalerSetDataPortByte(_TCON_ADDR_PORT_8B, _TCON_CTRL0_00, 0x41);
#else
    CScalerSetByte(_TCON_ADDR_PORT_8B, 0x00);
    CScalerSetByte(_TCON_DATA_PORT_8C, 0x41);
#endif
}

//--------------------------------------------------
// Description  : Power on ADC and APLL
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CPowerADCAPLLOn(void)
{
#if(_SCALER_TYPE == _RTD2547D)

    CScalerPageSelect(_PAGE1);
    CScalerSetBit(_P1_PLL1_N_AB, ~_BIT7, 0x00);     // Power up PLL1
    CScalerSetBit(_P1_PLL2_WD_B1, ~_BIT0, 0x00);    // Power up PLL2

    CScalerPageSelect(_PAGE0);
    CScalerSetBit(_P0_ADC_POWER_AD, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));    // Power up ADC

#else

    CScalerSetBit(_PLL1_N_A2, ~_BIT7, 0x00);                                                // Power up PLL1
    CScalerSetBit(_PLL2_WD_A8, ~_BIT0, 0x00);                                               // Power up PLL2
    
#if (_SCALER_TYPE == _RTD2553V || _SCALER_TYPE == _RTD2546N || _SCALER_TYPE == _RTD2525L)                                                               
	CScalerSetDataPortBit(_ADC_ACCESS_PORT_DC, 0x0c, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));    // Power up ADC
#else
    CScalerSetBit(_ADC_POWER_CTRL_E8, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));   // Power up ADC
#endif
#endif  // #if(_SCALER_TYPE == _RTD2547D)
}

//--------------------------------------------------
// Description  : Power off ADC and APLL
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CPowerADCAPLLOff(void)
{
#if(_SCALER_TYPE == _RTD2547D)

    CScalerPageSelect(_PAGE1);
    CScalerSetBit(_P1_PLL1_N_AB, ~_BIT7, _BIT7);     // Power down PLL1
    CScalerSetBit(_P1_PLL2_WD_B1, ~_BIT0, _BIT0);    // Power down PLL2

    CScalerPageSelect(_PAGE0);
    CScalerSetBit(_P0_ADC_POWER_AD, ~(_BIT2 | _BIT1 | _BIT0), 0x00);    // Power down ADC

#else

    CScalerSetBit(_PLL1_N_A2, ~_BIT7, _BIT7);                                               // Power down PLL1
    CScalerSetBit(_PLL2_WD_A8, ~_BIT0, _BIT0);                                              // Power down PLL2
#if (_SCALER_TYPE == _RTD2553V || _SCALER_TYPE == _RTD2546N || _SCALER_TYPE == _RTD2525L)
	CScalerSetDataPortBit(_ADC_ACCESS_PORT_DC, 0x0c, ~(_BIT2 | _BIT1 | _BIT0), 0x00);                       // Power down ADC
#else
    CScalerSetBit(_ADC_POWER_CTRL_E8, ~(_BIT2 | _BIT1 | _BIT0), 0x00);                      // Power down ADC
#endif

#endif // #if(_SCALER_TYPE == _RTD2547D)
}

#if((_TMDS_SUPPORT == _ON) || (_HDMI_SUPPORT == _ON))
//--------------------------------------------------
// Description  : Power on TMDS
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CPowerTMDSOn(void)
{
#if (_SCALER_TYPE != _RTD2553V && _SCALER_TYPE != _RTD2546N && _SCALER_TYPE != _RTD2525L && _SCALER_TYPE != _RTD2547D)
    CScalerSetBit(_DEVICE_KEY_BIST_PATTERN_D7, ~_BIT7, _BIT7);
#endif
    CScalerSetBit(_SYNC_CTRL_49, ~(_BIT1 | _BIT0), 0x00);
}
#endif

//--------------------------------------------------
// Description  : Power off TMDS
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CPowerTMDSOff(void)
{
#if(_SCALER_TYPE == _RTD2547D)

    CScalerPageSelect(_PAGE2);
    CScalerSetBit(_P2_Z0_CALIBRATION_CTRL_AC, ~_BIT6, 0x00);
    CScalerSetBit(_P2_TMDS_OUTPUT_CTRL_A6, ~_BIT7, 0x00);

#else

    CScalerSetBit(_Z0_CALIBRATION_CTRL_C7, ~_BIT6, 0x00);
    CScalerSetBit(_TMDS_OUTPUT_CTRL_C1, ~_BIT7, 0x00);
#if (_SCALER_TYPE != _RTD2553V && _SCALER_TYPE != _RTD2546N && _SCALER_TYPE != _RTD2525L)
    CScalerSetBit(_DEVICE_KEY_BIST_PATTERN_D7, ~_BIT7, 0x00);
#endif

#endif
}

//--------------------------------------------------
// Description  : Power off ADC and APLL
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CPowerDPLLOff(void)
{
#if(_SCALER_TYPE == _RTD2547D)
    CScalerPageSelect(_PAGE1);
    CScalerSetBit(_P1_DPLL_N_B8, ~_BIT7, _BIT7);  // Power down DPLL
#else
    CScalerSetBit(_DPLL_N_AF, ~_BIT7, _BIT7);                                               // Power down DPLL
#endif
}

#if(_SCALER_TYPE == _RTD2547D)
//--------------------------------------------------
// Description  : Power off MPLL
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CPowerMPLLOff(void)
{
    CScalerPageSelect(_PAGE1);
    CScalerSetBit(_P1_MPLL_N_C9, ~_BIT7, _BIT7);  // Power down MPLL
}
#endif

//--------------------------------------------------
// Description  : Power on PWM
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CPowerPWMOn(void)
{
    pData[0] = 0x40;
    pData[1] = 0x02;
    pData[2] = 0x10;
    CScalerWrite(_OSD_ADDR_MSB_90, 3, pData, _AUTOINC);
}

//--------------------------------------------------
// Description  : Power off PWM
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CPowerPWMOff(void)
{
    pData[0] = 0x40;
    pData[1] = 0x02;
    pData[2] = 0x00;
    CScalerWrite(_OSD_ADDR_MSB_90, 3, pData, _AUTOINC);
}


//---------------------------------------------------------------------------
#if(PowerUpLED==GreenLED||PowerDownLED==GreenLED||RunLED==GreenLED||NosignalStateLED==GreenLED)
//eric 20070531
void CPowerLedGreen(void)
{
	REDLED_OFF();
	GREENLED_ON();
}
#endif
//---------------------------------------------------------------------------
#if(PowerUpLED==RedLED||PowerDownLED==RedLED||RunLED==RedLED||NosignalStateLED==RedLED)

void CPowerLedRed(void)
{
	REDLED_ON();
	GREENLED_OFF();
}
#endif
//---------------------------------------------------------------------------

#if(PowerUpLED==OrangeLED||PowerDownLED==OrangeLED||RunLED==OrangeLED||NosignalStateLED==OrangeLED)
void CPowerLedOrange(void)
{
	REDLED_ON();
	GREENLED_ON();
}
#endif
//---------------------------------------------------------------------------

#if(PowerUpLED==BlackLED||PowerDownLED==BlackLED||RunLED==BlackLED||NosignalStateLED==BlackLED)
void CPowerLedBlack(void)
{
	REDLED_OFF();
	GREENLED_OFF();
}
#endif

