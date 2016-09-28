//----------------------------------------------------------------------------------------------------
// ID Code      : Scaler.c No.0004
// Update Note  : 
//
//----------------------------------------------------------------------------------------------------

#define __SCALER__

#include "Header\Include.h"

#if(_SCALER_TYPE == _RTD2547D)
//--------------------------------------------------
// Description  : Page select for scalar(Only for CR[A1]~CR[DF])
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CScalerPageSelect(BYTE page)
{
	CScalerSetByte(_PAGE_SELECT_A0, (page & 0x07));
}
#endif

//--------------------------------------------------
// Description  : Initial settings for scaler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CScalerInitial(void)
{
    // Software reset for scaler
    CScalerSetBit(_HOST_CTRL_01, ~_BIT0, _BIT0);
    CTimerDelayXms(100);
    CScalerSetBit(_HOST_CTRL_01, ~_BIT0, 0x00);

    CScalerReset();

#if((_RESET_CHECK_SUPPORT == _ON) && (_SCALER_TYPE == _RTD2525L))
    CScalerSetBit(_HOST_CTRL_01, ~_BIT6, _BIT6);
#endif  
}

//--------------------------------------------------
// Description  : Reset scaler process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CScalerReset(void)
{
    // Wake scaler up
#if(_SCALER_TYPE == _RTD2553V || _SCALER_TYPE == _RTD2546N || _SCALER_TYPE == _RTD2525L) 
    CScalerSetBit(_HOST_CTRL_01, ~(_BIT2 | _BIT1 | _BIT0), 0x00); //V307 modify
#elif(_SCALER_TYPE == _RTD2547D)
    CScalerSetByte(_HOST_CTRL_01, 0x40);
#else
    CScalerSetByte(_HOST_CTRL_01, 0x00);
#endif

    CScalerCodeW(tSCALER_POWERUP_INITIAL);
 
#if(_SCALER_TYPE == _RTD2547D)
  #if (_HDMI_SUPPORT == _ON)
	if(_GET_INPUT_SOURCE() == _SOURCE_HDMI)
		CScalerCodeW(tSCALER_POWERUP_HDMI);		
	else
  #endif
        CScalerCodeW(tSCALER_POWERUP_DVI);
#endif

    CScalerSetBit(_DISP_TIMING_46, ~(_BIT4|_BIT5|_BIT6), Panel.DCLK_DELAY<<4);

    CMiscSetPinShare();

    CAdjustDisableWatchDog(_WD_ALL);

    CMiscClearStatusRegister();

    CScalerInitialDisplayInterface();

    CScalerInitialDisplayOutput();

    CModeSetFreeRun();

    CScalerEnableDisplayTiming();

    if(GET_POWERSTATUS())
    {
#if(_SCALER_TYPE == _RTD2547D)
        CScalerSetBit(_SYNC_TEST_MISC_5A, ~_BIT7, _BIT7);//For analog input detect interlace mode.
#endif
        // OSD power up initial
        CScalerCodeW(tOSD_POWERUP_INITIAL);

        CAdjustTMDSErrorCorrectionOn();
        CAdjustColorPalette(tPALETTE_0);
        CAdjustSRGB();
#if(_SCALER_TYPE == _RTD2547D)
        CAdjustGamma(_FULL_GAMMA_COMPRESS_TABLE, tGAMMA_R, tGAMMA_G, tGAMMA_B);
#else
        CAdjustGamma(_COMPACT_GAMMA_NORMAL_TABLE, tGAMMA_COMPACT1, tGAMMA_COMPACT1, tGAMMA_COMPACT1);
#endif

      if(Panel.PanelDepth)//  if((Panel.PanelConfig & _BIT7) == _DISP_18_BIT)  //0331 guo
            CAdjustDither(tDITHER_SEQ_TABLE_0, tDITHER_TABLE_10_TO_6);
        else// if((Panel.PanelConfig & _BIT7) == _DISP_24_BIT)  //0331 guo
            CAdjustDither(tDITHER_SEQ_TABLE_0, tDITHER_TABLE_10_TO_8);

#if(_SCALER_TYPE == _RTD2547D)
        CScalerSetBit(_IPH_ACT_WID_H_16, ~(_BIT6 | _BIT5 | _BIT4), ((_ADC_INPUT_SWAP_RG << 6) | (_ADC_INPUT_SWAP_RB << 5)| (_ADC_INPUT_SWAP_GB << 4)));
#else
        CScalerSetBit(_IPH_ACT_WID_H_0B, ~(_BIT6 | _BIT5 | _BIT4), ((_ADC_INPUT_SWAP_RG << 6) | (_ADC_INPUT_SWAP_RB << 5)| (_ADC_INPUT_SWAP_GB << 4)));
#endif

        CAdjustBrightness();
        CAdjustContrast();

    // Load HDMI EDID to Chip
#if(_HDMI_EDID == _ON)
        CScalerCodeW(tHDMI_EDID_DATA);
#endif

#if(_OD_SUPPORT == _ON)
        CMemoryLoadODLUT(_OD_TABLE_COMMON);
#endif


#if(_HDCP_SUPPORT == _ON)
        CAdjustHDCP();
#endif

    }
    else
    {
        CPowerDPLLOff();

#if(_SCALER_TYPE == _RTD2553V || _SCALER_TYPE == _RTD2546N || _SCALER_TYPE == _RTD2525L) 
        CScalerSetBit(_HOST_CTRL_01, ~_BIT1, _BIT1); //V307 modify
#elif(_SCALER_TYPE == _RTD2547D)
        CPowerMPLLOff();
        CScalerSetBit(_HOST_CTRL_01, ~_BIT1,(_BIT4 | _BIT1)); //V307 modify
#else
        CScalerSetByte(_HOST_CTRL_01, 0x02);
#endif
        CScalerDisableDisplayTiming();
    }
}

//--------------------------------------------------
// Description  : Initial display interface for TTL, LVDS and RSDS
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CScalerInitialDisplayInterface(void)
{
    switch(Panel.PanelStyle)
    {
        case _PANEL_TTL:
            CScalerCodeW(tTTL_INITIAL);
            break;

        case _PANEL_LVDS:
            CScalerCodeW(tLVDS_INITIAL);
     	    CScalerSetByte(_TCON_ADDR_PORT_8B, 0x7B);
            CScalerRead(_TCON_DATA_PORT_8C, 1, pData, _NON_AUTOINC);
            CScalerSetByte(_TCON_ADDR_PORT_8B, 0x7B);
		if(Panel.PanelDepth)
		    CScalerSetByte(_TCON_DATA_PORT_8C, (pData[0] & 0xfe)|0x01);   //LVDS_MAP2
		else
	     	CScalerSetByte(_TCON_DATA_PORT_8C, (pData[0] & 0xfe)|0x00);	//LVDS_MAP1
            break;

        case _PANEL_RSDS:
            CScalerCodeW(tLVDS_INITIAL);
            CScalerCodeW(tRSDS_INITIAL);
#if(_SCALER_TYPE == _RTD2547D)
            CScalerSetDataPortByte(_TCON_ADDR_PORT_8B, _TCON_RSDS_OUTPUT_CTRL0_C0, 0x40 | Panel.PanelConfig & (_BIT2 | _BIT1 | _BIT0));
            CScalerSetDataPortBit(_DISP_ACCESS_PORT_2A, _DISP_TIMING_20, ~_BIT0, _BIT0);
#else
            CScalerSetByte(_TCON_ADDR_PORT_8B, 0x02);
#if (_SCALER_TYPE == _RTD2553V || _SCALER_TYPE == _RTD2546N || _SCALER_TYPE == _RTD2525L)
            CScalerSetByte(_TCON_DATA_PORT_8C, 0x40 |((Panel.RSDS_GC_SWAP<<2)|(Panel.RSDS_GC_SWAP <1)| Panel.RSDS_GC_SWAP));
          //  CScalerSetByte(_TCON_DATA_PORT_8C, 0x40 | Panel.PanelConfig & (_BIT2 | _BIT1 | _BIT0));
            CScalerSetBit(_DISP_TIMING_46, ~_BIT0, _BIT0);
#else
            CScalerSetByte(_TCON_DATA_PORT_8C, (Panel.RSDS_GC_SWAP|Panel.RSDS_GC_SWAP | Panel.RSDS_GC_SWAP));
        // CScalerSetByte(_TCON_DATA_PORT_8C, Panel.PanelConfig & (_BIT2 | _BIT1 | _BIT0));
#endif
#endif // #if(_SCALER_TYPE == _RTD2528R)
            break;
    }
}

//--------------------------------------------------
// Description  : Initial display output from Panel.h settings
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CScalerInitialDisplayOutput(void)
{
    // Display signal control settings
    /*
    CScalerSetBit(_VDISP_CTRL_28, ~(_BIT4 | _BIT2), ((Panel.PanelConfig & _BIT7) >> 3) | ((Panel.PanelConfig & _BIT3) >> 1));
    CScalerSetByte(_VDISP_SIGINV_29, _DISPLAY_CTRL | (Panel.PanelConfig & (_BIT6 | _BIT5 | _BIT4)));
*/
    CScalerSetBit(_VDISP_CTRL_28, ~(_BIT4 | _BIT2), 0x00|(Panel.PanelDepth<<4)|(Panel.Double_Port<<2));//((Panel.PanelConfig & _BIT7) >> 3) | ((Panel.PanelConfig & _BIT3) >> 1));
    CScalerSetByte(_VDISP_SIGINV_29, (Panel.DHS_MASK<<7)|(Panel.EO_SWAP<<6)|(Panel.RB_SWAP<<5)\
									|(Panel.ML_SWAP<<4)|(Panel.DVS_INVERT<<2)|(Panel.DHS_INVERT<<1)|(Panel.DEN_INVERT));//Panel.Dis_Ctr | (Panel.PanelConfig & (_BIT6 | _BIT5 | _BIT4)));
}

//--------------------------------------------------
// Description  : Enable display output
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CScalerEnableDisplayOutput(void)
{
#if(_SCALER_TYPE == _RTD2547D)
    BYTE ucPanelStyle = 0;

    switch(Panel.PanelStyle)
    {
        case _PANEL_TTL:     ucPanelStyle = 0;        break;
        case _PANEL_RSDS:    ucPanelStyle = 2;        break;
        default:
        case _PANEL_LVDS:    ucPanelStyle = 1;        break;
        case _PANEL_COG:     ucPanelStyle = 3;        break;
    }

    CScalerGetDataPortByte(_TCON_ADDR_PORT_8B, _TCON_CTRL0_00, 1, pData, _NON_AUTOINC);
 //   CScalerSetDataPortByte(_TCON_ADDR_PORT_8B, _TCON_CTRL0_00, ((pData[0] & ~(_BIT3 | _BIT1 | _BIT0)) | (Panel.PanelStyle & (_BIT1 | _BIT0)) | _BIT3));
    CScalerSetDataPortByte(_TCON_ADDR_PORT_8B, _TCON_CTRL0_00, ((pData[0] & ~(_BIT3 | _BIT1 | _BIT0)) | (ucPanelStyle & (_BIT1 | _BIT0)) | _BIT3));
#else
    CScalerSetByte(_TCON_ADDR_PORT_8B, 0x00);
    CScalerRead(_TCON_DATA_PORT_8C, 1, pData, _NON_AUTOINC);
    CScalerSetByte(_TCON_ADDR_PORT_8B, 0x00);
    CScalerSetByte(_TCON_DATA_PORT_8C, (pData[0] & ~(_BIT1 | _BIT0)) | (Panel.PanelStyle & (_BIT1 | _BIT0)));
#endif
}


//--------------------------------------------------
// Description  : Disable display output
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CScalerDisableDisplayOutput(void)
{
#if(_SCALER_TYPE == _RTD2547D) 
    CScalerGetDataPortByte(_TCON_ADDR_PORT_8B, _TCON_CTRL0_00, 1, pData, _NON_AUTOINC);
    CScalerSetDataPortByte(_TCON_ADDR_PORT_8B, _TCON_CTRL0_00, (pData[0] & ~_BIT3));
#else
    CScalerSetByte(_TCON_ADDR_PORT_8B, 0x00);
    CScalerRead(_TCON_DATA_PORT_8C, 1, pData, _NON_AUTOINC);
    CScalerSetByte(_TCON_ADDR_PORT_8B, 0x00);
  //  CScalerSetByte(_TCON_DATA_PORT_8C, (pData[0] & ~(_BIT1 | _BIT0)) | (_PANEL_HZ & (_BIT1 | _BIT0)));
    CScalerSetByte(_TCON_DATA_PORT_8C, (pData[0] & ~(_BIT1 | _BIT0)) | (0x01 & (_BIT1 | _BIT0)));
#endif
}

//--------------------------------------------------
// Description  : Enable display
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CScalerEnableDisplayTiming(void)
{
    CScalerSetBit(_VDISP_CTRL_28, ~(_BIT6 | _BIT1), _BIT1);
    CScalerSetBit(_VDISP_CTRL_28, ~_BIT0, _BIT0);

    CScalerSetBit(_VDISP_CTRL_28, ~_BIT7, _BIT7);
    CScalerSetBit(_VDISP_CTRL_28, ~_BIT7, 0x00);
}


//--------------------------------------------------
// Description  : Disable display output
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CScalerDisableDisplayTiming(void)
{
/*
    if(Panel.PanelStyle == _PANEL_TTL)
    {
        CScalerSetBit(_VDISP_SIGINV_29, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
    }
*/
    CScalerSetBit(_VDISP_CTRL_28, ~(_BIT6 | _BIT1), _BIT6);
    CScalerSetBit(_VDISP_CTRL_28, ~_BIT0, 0x00);
}

#if(((_SCALER_TYPE == _RTD2023S) || (_SCALER_TYPE == _RTD2023S_VB)) && (_RESET_TYPE == _RESET_OUT))
//--------------------------------------------------
// Description  : High or low voltage reset action
// Input Value  : Select high or low reset
// Output Value : None
//--------------------------------------------------
void CScalerResetAction(bit bResetLevel)
{
    bSCALERRESET    = (bResetLevel ? _LOW : _HIGH);
    CTimerDelayXms(5);
    bSCALERRESET    = (bResetLevel ? _HIGH : _LOW);
    CTimerDelayXms(5);
    bSCALERRESET    = (bResetLevel ? _LOW : _HIGH);
    CTimerDelayXms(5);
}

//--------------------------------------------------
// Description  : Initial settings for RTD2023L/S scaler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CScalerResetInForRTD2023(void)
{
    CScalerResetAction(_HIGH);
}
#endif

#if(_RESET_TYPE == _RESET_IN)
//--------------------------------------------------
// Description  : High or low voltage reset action
// Input Value  : Select high or low reset
// Output Value : None
//--------------------------------------------------
void CScalerResetAction(bit bResetLevel)
{
    bSCALERRESET    = (bResetLevel ? _LOW : _HIGH);
    CTimerDelayXms(5);
    bSCALERRESET    = (bResetLevel ? _HIGH : _LOW);
    CTimerDelayXms(5);
    bSCALERRESET    = (bResetLevel ? _LOW : _HIGH);
    CTimerDelayXms(5);
}

//--------------------------------------------------
// Description  : Reset in from MCU
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CScalerResetInFromMCU(void)
{
    CScalerResetAction(_LOW);

    while(_TRUE)
    {
        if(!bLVRPOWERDETECT);
            break;
    }
}
#endif

//----------------------------------------------------------------------------------------------------
// Scaler communication basic function
//----------------------------------------------------------------------------------------------------
#if(_SCALER_TYPE == _RTD2525L) 
void CScalerSendReadStop(void)
{
    SETSCALERSDIO3(_HIGH);
    SETSCALERSDIO3(_LOW);
    SETSCALERSDIO3(_HIGH);

    SETSCALERSCLK();
}

void CScalerSendWriteStop(void)
{
    CLRSCALERSCLK();
    SETSCALERSCLK();

    SETSCALERSCLK();
    SETSCALERSDIO3(_HIGH);
    SETSCALERSDIO3(_LOW);
    SETSCALERSDIO3(_HIGH);
}

void CScalerSendByte(BYTE ucValue)
{
    SETSCALERSDIO3((bit)(ucValue & 0x01));
    CLRSCALERSCLK();
    SETSCALERSDIO3((bit)(ucValue & 0x02));
    SETSCALERSCLK();
    SETSCALERSDIO3((bit)(ucValue & 0x04));
    CLRSCALERSCLK();
    SETSCALERSDIO3((bit)(ucValue & 0x08));
    SETSCALERSCLK();
    SETSCALERSDIO3((bit)(ucValue & 0x10));
    CLRSCALERSCLK();
    SETSCALERSDIO3((bit)(ucValue & 0x20));
    SETSCALERSCLK();
    SETSCALERSDIO3((bit)(ucValue & 0x40));
    CLRSCALERSCLK();
    SETSCALERSDIO3((bit)(ucValue & 0x80));
    SETSCALERSCLK();
}

void CScalerSendAddr(BYTE ucAddr, bit bReadWrite, bit bAutoInc)
{
    SETSCALERSCLK();
    SETSCALERSDIO3(_HIGH);
    SETSCALERSDIO3(_LOW);
    SETSCALERSDIO3(_HIGH);

    CScalerSendByte(ucAddr);

    SETSCALERSDIO3(bReadWrite);
    CLRSCALERSCLK();
    SETSCALERSDIO3(bAutoInc);
    SETSCALERSCLK();

    SETSCALERSDIO3(_HIGH);
}

void CScalerSETSCLK(void) //V306 modify
{
    SETSCALERSCLK();
    SETSCALERSCLK();
    SETSCALERSCLK();
    SETSCALERSCLK();
    SETSCALERSCLK();
}

void CScalerCLRSCLK(void) //V306 modify
{
    CLRSCALERSCLK();
    CLRSCALERSCLK();
    CLRSCALERSCLK();
    CLRSCALERSCLK();
    CLRSCALERSCLK();
}

BYTE CScalerGetByte1(void)
{
    BYTE value = 0;

    CScalerCLRSCLK();
    if(GETSCALERSDIO3())
        value   |= 0x01;
    CScalerSETSCLK();
    if(GETSCALERSDIO3())
        value   |= 0x02;
    CScalerCLRSCLK();
    if(GETSCALERSDIO3())
        value   |= 0x04;
    CScalerSETSCLK();
    if(GETSCALERSDIO3())
        value   |= 0x08;
    CScalerCLRSCLK();
    if(GETSCALERSDIO3())
        value   |= 0x10;
    CScalerSETSCLK();
    if(GETSCALERSDIO3())
        value   |= 0x20;
    CScalerCLRSCLK();
    if(GETSCALERSDIO3())
        value   |= 0x40;
    CScalerSETSCLK();
    if(GETSCALERSDIO3())
        value   |= 0x80;

    CScalerCLRSCLK();

    return value;
}

BYTE CScalerGetByte2(void)
{
    BYTE value = 0;

    CScalerSETSCLK();
    if(GETSCALERSDIO3())
        value   |= 0x01;
    CScalerCLRSCLK();
    if(GETSCALERSDIO3())
        value   |= 0x02;
    CScalerSETSCLK();
    if(GETSCALERSDIO3())
        value   |= 0x04;
    CScalerCLRSCLK();
    if(GETSCALERSDIO3())
        value   |= 0x08;
    CScalerSETSCLK();
    if(GETSCALERSDIO3())
        value   |= 0x10;
    CScalerCLRSCLK();
    if(GETSCALERSDIO3())
        value   |= 0x20;
    CScalerSETSCLK();
    if(GETSCALERSDIO3())
        value   |= 0x40;
    CScalerCLRSCLK();
    if(GETSCALERSDIO3())
        value   |= 0x80;

    CScalerSETSCLK();

    return value;
}

#else

void CScalerSendReadStop(void)
{
#if(_HOST_INTERFACE == _PARALLEL_PORT)

    SETSCALERSCSB();
    SETSCALERSCLK();

#elif(_HOST_INTERFACE == _SERIAL_PORT)

    SETSCALERSCLK();
    SETSCALERSCSB();

#endif
}

void CScalerSendWriteStop(void)
{
#if(_HOST_INTERFACE == _PARALLEL_PORT)

    SETSCALERSCLK();
    SETSCALERSCSB();

#elif(_HOST_INTERFACE == _SERIAL_PORT)

    CLRSCALERSCLK();
    SETSCALERSCLK();

    SETSCALERSCLK();
    SETSCALERSCSB();

#endif
}

void CScalerSendAddr(BYTE ucAddr, bit bReadWrite, bit bAutoInc)
{
#if(_HOST_INTERFACE == _PARALLEL_PORT)

    CLRSCALERSCSB();

    SETSCALERSDIO0((bit)(ucAddr & 0x01));
    SETSCALERSDIO1((bit)(ucAddr & 0x02));
    SETSCALERSDIO2((bit)(ucAddr & 0x04));
    SETSCALERSDIO3((bit)(ucAddr & 0x08));
    CLRSCALERSCLK();

    SETSCALERSDIO0((bit)(ucAddr & 0x10));
    SETSCALERSDIO1((bit)(ucAddr & 0x20));
    SETSCALERSDIO2((bit)(ucAddr & 0x40));
    SETSCALERSDIO3((bit)(ucAddr & 0x80));
    SETSCALERSCLK();
    
    SETSCALERSDIO0(bReadWrite);
    SETSCALERSDIO1(bAutoInc);
    CLRSCALERSCLK();

    SETSCALERSDIO0(_HIGH);
    SETSCALERSDIO1(_HIGH);
    SETSCALERSDIO2(_HIGH);
    SETSCALERSDIO3(_HIGH);

#elif(_HOST_INTERFACE == _SERIAL_PORT)

    CLRSCALERSCSB();

    CScalerSendByte(ucAddr);

    SETSCALERSDIO3(bReadWrite);
    CLRSCALERSCLK();
    SETSCALERSDIO3(bAutoInc);
    SETSCALERSCLK();

    SETSCALERSDIO3(_HIGH);

#endif
}

void CScalerSendByte(BYTE ucValue)
{
#if(_HOST_INTERFACE == _PARALLEL_PORT)

    SETSCALERSDIO0((bit)(ucValue & 0x01));
    SETSCALERSDIO1((bit)(ucValue & 0x02));
    SETSCALERSDIO2((bit)(ucValue & 0x04));
    SETSCALERSDIO3((bit)(ucValue & 0x08));
    SETSCALERSCLK();

    SETSCALERSDIO0((bit)(ucValue & 0x10));
    SETSCALERSDIO1((bit)(ucValue & 0x20));
    SETSCALERSDIO2((bit)(ucValue & 0x40));
    SETSCALERSDIO3((bit)(ucValue & 0x80));
    CLRSCALERSCLK();

#elif(_HOST_INTERFACE == _SERIAL_PORT)

    SETSCALERSDIO3((bit)(ucValue & 0x01));
    CLRSCALERSCLK();
    SETSCALERSDIO3((bit)(ucValue & 0x02));
    SETSCALERSCLK();
    SETSCALERSDIO3((bit)(ucValue & 0x04));
    CLRSCALERSCLK();
    SETSCALERSDIO3((bit)(ucValue & 0x08));
    SETSCALERSCLK();
    SETSCALERSDIO3((bit)(ucValue & 0x10));
    CLRSCALERSCLK();
    SETSCALERSDIO3((bit)(ucValue & 0x20));
    SETSCALERSCLK();
    SETSCALERSDIO3((bit)(ucValue & 0x40));
    CLRSCALERSCLK();
    SETSCALERSDIO3((bit)(ucValue & 0x80));
    SETSCALERSCLK();

#endif
}

void CScalerSETSCLK(void) //V306 modify
{
    SETSCALERSCLK();
    SETSCALERSCLK();
    SETSCALERSCLK();
    SETSCALERSCLK();
    SETSCALERSCLK();
}

void CScalerCLRSCLK(void) //V306 modify
{
    CLRSCALERSCLK();
    CLRSCALERSCLK();
    CLRSCALERSCLK();
    CLRSCALERSCLK();
    CLRSCALERSCLK();
}

BYTE CScalerGetByte(void)
{
#if(_HOST_INTERFACE == _PARALLEL_PORT)

    BYTE value = 0;

    CScalerSETSCLK();
    if(GETSCALERSDIO0())
        value   |= 0x01;
    if(GETSCALERSDIO1())
        value   |= 0x02;
    if(GETSCALERSDIO2())
        value   |= 0x04;
    if(GETSCALERSDIO3())
        value   |= 0x08;
    CScalerCLRSCLK();
    if(GETSCALERSDIO0())
        value   |= 0x10;
    if(GETSCALERSDIO1())
        value   |= 0x20;
    if(GETSCALERSDIO2())
        value   |= 0x40;
    if(GETSCALERSDIO3())
        value   |= 0x80;

#elif(_HOST_INTERFACE == _SERIAL_PORT)

    BYTE value = 0;

    CScalerCLRSCLK();
    if(GETSCALERSDIO3())
        value   |= 0x01;
    CScalerSETSCLK();
    if(GETSCALERSDIO3())
        value   |= 0x02;
    CScalerCLRSCLK();
    if(GETSCALERSDIO3())
        value   |= 0x04;
    CScalerSETSCLK();
    if(GETSCALERSDIO3())
        value   |= 0x08;
    CScalerCLRSCLK();
    if(GETSCALERSDIO3())
        value   |= 0x10;
    CScalerSETSCLK();
    if(GETSCALERSDIO3())
        value   |= 0x20;
    CScalerCLRSCLK();
    if(GETSCALERSDIO3())
        value   |= 0x40;
    CScalerSETSCLK();
    if(GETSCALERSDIO3())
        value   |= 0x80;

#endif

    return value;
}

#endif

#if((_SCALER_TYPE == _RTD2023L) || (_SCALER_TYPE == _RTD2023S) || (_SCALER_TYPE == _RTD2023L_VB) || (_SCALER_TYPE == _RTD2023S_VB))
//--------------------------------------------------
// Description  : Initial settings for RTD2023L/S scaler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CScalerInitialForRTD2023(void)
{
    BYTE temp = 0;

    do
    {
        CScalerSetByte(0xcf, 0xf0);
        CTimerDelayXms(3);
        CScalerRead(_ID_REG_00, 1, &temp, _NON_AUTOINC);
    }
    while(!((temp == 0x11) || (temp == 0x21)));
}
#endif

//--------------------------------------------------
// Description  : Write a data array into registers of scaler
// Input Value  : ucAddr    --> Start address of register
//                ucLength  --> Numbers of data we want to write
//                pArray    --> Pointer of the writing data array
//                bAutoInc  --> Address auto increasing select
// Output Value : None
//--------------------------------------------------
void CScalerWrite(BYTE ucAddr, WORD usLength, BYTE *pArray, bit bAutoInc)
{
    if(usLength > 0)
    {
        CScalerSendAddr(ucAddr, _WRITE, bAutoInc);

        do
        {
            CScalerSendByte(*pArray++);

        }while(--usLength);

        CScalerSendWriteStop();
    }
}

//--------------------------------------------------
// Description  : Read data from registers of scaler and put it into an reading data array
// Input Value  : ucAddr    --> Start address of register
//                ucLength  --> Numbers of data we want to read
//                pArray    --> Pointer of the reading data array
//                bAutoInc  --> Address auto increasing select
// Output Value : None
//--------------------------------------------------
void CScalerRead(BYTE ucAddr, BYTE ucLength, BYTE *pArray, bit bAutoInc)
{
#if (_SCALER_TYPE == _RTD2553V || _SCALER_TYPE == _RTD2546N || _SCALER_TYPE == _RTD2525L)
    BYTE odd = 0;

    if(ucLength > 0)
    {
        CScalerSendAddr(ucAddr, _READ, bAutoInc);

        do
        {
#if(_SCALER_TYPE == _RTD2525L) //V306 modify
            *pArray++ = (odd==0) ? CScalerGetByte1() : CScalerGetByte2();
            odd = odd ^ 0x01; 
#else
            *pArray++ = CScalerGetByte();
#endif  
        }while(--ucLength);

        CScalerSendReadStop();
    }

#else

    if(ucLength > 0)
    {
        CScalerSendAddr(ucAddr, _READ, bAutoInc);

        do
        {
            *pArray++ = CScalerGetByte();

        }while(--ucLength);

        CScalerSendReadStop();
    }
#endif
}

//--------------------------------------------------
// Description  : Write a data array into registers of scaler
// Input Value  : ucAddr    --> Start address of register
//                ucLength  --> Numbers of data we want to write
//                pValue    --> Value we want to write
//                bAutoInc  --> Address auto increasing select
// Output Value : None
//--------------------------------------------------
void CScalerWriteAmount(BYTE ucAddr, WORD usLength, BYTE ucValue, bit bAutoInc)
{
    if(usLength > 0)
    {
        CScalerSendAddr(ucAddr, _WRITE, bAutoInc);

        do
        {
            CScalerSendByte(ucValue);

        }while(--usLength);

        CScalerSendWriteStop();
    }
}

//--------------------------------------------------
// Description  : Set the value into selected register
// Input Value  : ucAddr    --> Address of register
//                ucValue   --> Value we want to set
// Output Value : None
//--------------------------------------------------
void CScalerSetByte(BYTE ucAddr, BYTE ucValue)
{
    CScalerWrite(ucAddr, 1, &ucValue, _AUTOINC);
}

//--------------------------------------------------
// Description  : Set some bits of selected register
// Input Value  : ucAddr    --> Address of register
//                ucAnd     --> & operation
//                ucOr      --> | operation
// Output Value : None
//--------------------------------------------------
void CScalerSetBit(BYTE ucAddr, BYTE ucAnd, BYTE ucOr)
{
    BYTE value;

    CScalerRead(ucAddr, 1, &value, _AUTOINC);

    value   = (value & ucAnd) | ucOr;

    CScalerWrite(ucAddr, 1, &value, _AUTOINC);
}

#if (_SCALER_TYPE == _RTD2553V || _SCALER_TYPE == _RTD2546N || _SCALER_TYPE == _RTD2525L || _SCALER_TYPE == _RTD2547D)
//--------------------------------------------------
// Description  : Set the value into selected register in data port
// Input Value  : ucAddr    --> Access Port Address of register
//                ucValue1  --> Data Port Value we want to set
//                ucValue2  --> Data Value we want to set
// Output Value : None
//--------------------------------------------------
void CScalerSetDataPortByte(BYTE ucAddr, BYTE ucValue1, BYTE ucValue2)
{
#if(_SCALER_TYPE == _RTD2547D)
    if((ucAddr == _SD_ACCESS_PORT_24) || (ucAddr == _SU_ACCESS_PORT_33) ||
       (ucAddr == _HW_ACCESS_PORT_60) || (ucAddr == _CB_ACCESS_PORT_64) ||
       (ucAddr == _PC_ACCESS_PORT_9A) || (ucAddr == _CMDI_ACCESS_PORT_F0))
    {
        CScalerSetByte(ucAddr, 0x80);    
        ucValue1 = ucValue1 | 0x80;
    }
#else
    ucValue1 = ucValue1 | 0x80;
#endif

    CScalerWrite(ucAddr, 1, &ucValue1, _AUTOINC);
    CScalerWrite(ucAddr + 1, 1, &ucValue2, _AUTOINC);
    CScalerSetByte(ucAddr, 0x00);
}

#if (_SCALER_TYPE == _RTD2547D)
//--------------------------------------------------
// Description  : Get bytes from selected register in data port
// Input Value  : ucAddr    --> Access Port Address of register
//                ucValue   --> Data Port Address we want to Get
//                ucLength  --> Numbers of data we want to read
//                pArray    --> Pointer of the reading data array
//                bAutoInc  --> Address auto increasing select
// Output Value : None
//--------------------------------------------------
void CScalerGetDataPortByte(BYTE ucAddr, BYTE ucValue, BYTE ucLength, BYTE *pArray, bit bAutoInc)
{
    if(ucLength > 0)
    {
        if((ucAddr == _SD_ACCESS_PORT_24) || (ucAddr == _SU_ACCESS_PORT_33) ||
           (ucAddr == _HW_ACCESS_PORT_60) || (ucAddr == _CB_ACCESS_PORT_64) ||
           (ucAddr == _PC_ACCESS_PORT_9A) || (ucAddr == _CMDI_ACCESS_PORT_F0))
        {
            CScalerSetByte(ucAddr, 0x80);    
            ucValue = ucValue | 0x80;
        }

        CScalerSetByte(ucAddr, ucValue);    
        CScalerRead( ucAddr + 1, ucLength, pArray, bAutoInc);
    }        
}
#endif


//--------------------------------------------------
// Description  : Set some bits of selected register in data port
// Input Value  : ucAddr    --> Access Port Address of register
//                ucValue   --> Data Port Value we want to set
//                ucAnd     --> & operation
//                ucOr      --> | operation
// Output Value : None
//--------------------------------------------------
void CScalerSetDataPortBit(BYTE ucAddr, BYTE ucValue, BYTE ucAnd, BYTE ucOr)
{
    BYTE value;

#if (_SCALER_TYPE == _RTD2547D)

    if((ucAddr == _SD_ACCESS_PORT_24) || (ucAddr == _SU_ACCESS_PORT_33) ||
       (ucAddr == _HW_ACCESS_PORT_60) || (ucAddr == _CB_ACCESS_PORT_64) ||
       (ucAddr == _PC_ACCESS_PORT_9A) || (ucAddr == _CMDI_ACCESS_PORT_F0))
    {
        CScalerSetByte(ucAddr, 0x80);    
        ucValue = ucValue | 0x80;
    }
    
    CScalerWrite(ucAddr, 1, &ucValue, _AUTOINC);
    CScalerRead(ucAddr + 1, 1, &value, _AUTOINC);

    value   = (value & ucAnd) | ucOr;

    if((ucAddr == _SD_ACCESS_PORT_24) || (ucAddr == _SU_ACCESS_PORT_33) ||
       (ucAddr == _HW_ACCESS_PORT_60) || (ucAddr == _CB_ACCESS_PORT_64) ||
       (ucAddr == _PC_ACCESS_PORT_9A) || (ucAddr == _CMDI_ACCESS_PORT_F0))
    {
        CScalerSetByte(ucAddr, 0x80);    
        ucValue = ucValue | 0x80;
    }

    CScalerWrite(ucAddr, 1, &ucValue, _AUTOINC);
    CScalerWrite(ucAddr + 1, 1, &value, _AUTOINC);
    CScalerSetByte(ucAddr, 0x00);

#else

    ucValue = ucValue | 0x80;
    CScalerWrite(ucAddr, 1, &ucValue, _AUTOINC);
    CScalerRead(ucAddr + 1, 1, &value, _AUTOINC);

    value   = (value & ucAnd) | ucOr;

    ucValue = ucValue | 0x80;
    CScalerWrite(ucAddr, 1, &ucValue, _AUTOINC);
    CScalerWrite(ucAddr + 1, 1, &value, _AUTOINC);
    CScalerSetByte(ucAddr, 0x00);

#endif
}


#if(((_ADC_OFFSET_ADJUSTING == _ADJUST_BY_HW_ON_LINE) || (_ADC_OFFSET_ADJUSTING == _ADJUST_BY_HW_OFF_LINE)) && (_SCALER_TYPE == _RTD2525L))         
//--------------------------------------------------
// Description  : Get bits from selected register in data port
// Input Value  : ucAddr    --> Access Port Address of register
//                ucValue   --> Data Port Value we want to set
//                ucAnd     --> & operation
// Output Value : Value after & operation
//--------------------------------------------------
BYTE CScalerGetDataPortBit(BYTE ucAddr, BYTE ucValue, BYTE ucAnd)
{
    BYTE value;

    ucValue = ucValue | 0x80;
    CScalerWrite(ucAddr, 1, &ucValue, _AUTOINC);
    CScalerRead(ucAddr + 1, 1, &value, _AUTOINC);

    return (value & ucAnd);
}
#endif  // End of #if(((_ADC_OFFSET_ADJUSTING == _ADJUST_BY_HW_ON_LINE) || (_ADC_OFFSET_ADJUSTING == _ADJUST_BY_HW_OFF_LINE)) && (_SCALER_TYPE == _RTD2525L))

#endif
#if(_SCALER_TYPE == _RTD2525L)
//--------------------------------------------------
// Description  : Set some bits of selected register in data port
// Input Value  : ucAddr    --> Access Port Address of register
//                ucValue   --> Data Port Value we want to set
//                ucAnd     --> & operation
//                ucOr      --> | operation
// Output Value : None
//--------------------------------------------------
void CScalerSetDataPortBit2(BYTE ucAddr, BYTE ucValue, BYTE ucAnd, BYTE ucOr)
{
    BYTE value;

    CScalerWrite(ucAddr, 1, &ucValue, _AUTOINC);
    CScalerRead(ucAddr + 1, 1, &value, _AUTOINC);

    value   = (value & ucAnd) | ucOr;

    CScalerWrite(ucAddr, 1, &ucValue, _AUTOINC);
    CScalerWrite(ucAddr + 1, 1, &value, _AUTOINC);
}
#endif  //End of #if(_SCALER_TYPE == _RTD2525L)

//--------------------------------------------------
// Description  : Get bits from selected register
// Input Value  : ucAddr    --> Address of register
//                ucAnd     --> & operation
// Output Value : Value after & operation
//--------------------------------------------------
BYTE CScalerGetBit(BYTE ucAddr, BYTE ucAnd)
{
    BYTE value;

    CScalerRead(ucAddr, 1, &value, _AUTOINC);

    return (value & ucAnd);
}

//--------------------------------------------------
// Description  : Write a table into scaler
// Input Value  : pArray    --> Selected table which contains numbers, address auto increasing information, address of registers and values
// Output Value : None
//--------------------------------------------------
void CScalerCodeW(BYTE code *pArray)
{
    BYTE length;

    do
    {
        if((*pArray & 0xfc) == 0)
            return;

        length  = *pArray - 3;

        if((*(pArray + 1)) == _BURST)
        {
            CScalerSendAddr(*(pArray + 2), _WRITE, _NON_AUTOINC);

            pArray += 3;
            
            do
            {
                CScalerSendByte(*pArray);

            }while(--length);

            pArray++;
        }
        else if((*(pArray + 1) == _AUTOINC) || (*(pArray + 1) == _NON_AUTOINC))
        {
            CScalerSendAddr(*(pArray + 2), _WRITE, *(pArray + 1));

            pArray += 3;

            do
            {
                CScalerSendByte(*pArray++);

            }while(--length);

        }

        CScalerSendWriteStop();

    }while(_TRUE);
}

#if(_HARDWARE_LOAD_FONT == _ON)
//--------------------------------------------------
// Description  : Load OSD font into OSD SRAM
// Input Value  : pArray    --> Font table
//                usOffset  --> Offset of font base start address
// Output Value : None
//--------------------------------------------------
#if(_USE_RTD2120_EXTEND_32K_FOR_OSD == _ON)
void CScalerLoadHardwareVLCFont(BYTE xdata *pArray, WORD usOffset)
#else
void CScalerLoadHardwareVLCFont(BYTE code *pArray, WORD usOffset)
#endif
{
    WORD num;


    CScalerSetByte(_OSD_ADDR_MSB_90, 0xc0);
    CScalerSetByte(_OSD_ADDR_LSB_91, 0x05);
    CScalerWrite(_OSD_DATA_PORT_92, 8, pArray, _NON_AUTOINC);

    num = ((WORD)*(pArray + 8) << 8) | *(pArray + 9);

    usOffset = usOffset * 9;
    usOffset += _OSD_FONT_START_POSITION;

    CScalerSetByte(_OSD_ADDR_MSB_90, 0x80);
    CScalerSetByte(_OSD_ADDR_LSB_91, 0x07);
    CScalerSetByte(_OSD_DATA_PORT_92, 0x01);

    CScalerSendAddr(_OSD_ADDR_MSB_90, _WRITE, _AUTOINC);
    CScalerSendByte((HIBYTE(usOffset) & 0x000f) | 0xd0);
    CScalerSendByte(LOBYTE(usOffset));
	CScalerSendWriteStop();

    pArray += 10;

	CScalerSendAddr(_OSD_DATA_PORT_92, _WRITE, _NON_AUTOINC);

    for(usOffset=0;usOffset<num;usOffset++)
    {
        CScalerSendByte(*pArray++);
    }

	CScalerSendWriteStop();

    CScalerSetByte(_OSD_ADDR_MSB_90, 0x80);
    CScalerSetByte(_OSD_ADDR_LSB_91, 0x07);
    CScalerSetByte(_OSD_DATA_PORT_92, 0x00);
}
#endif  // End of #if(_HARDWARE_LOAD_FONT == _ON)

#if(_SOFTWARE_LOAD_FONT == _ON)
//--------------------------------------------------
// Description  : Load OSD font into OSD SRAM
// Input Value  : pArray    --> Font table
//                usOffset  --> Offset of font base start address
//                usLength  --> Font amounts we want to load (unit in 1 bit font)
//                ucPar     --> Choose normal or compress font table
// Output Value : None
//--------------------------------------------------
#if(_USE_RTD2120_EXTEND_32K_FOR_OSD == _ON)
void CScalerLoadFont(BYTE xdata *pArray, WORD usOffset, WORD usLength, BYTE ucPar)
#else
void CScalerLoadFont(BYTE code *pArray, WORD usOffset, WORD usLength, BYTE ucPar)
#endif
{
    BYTE temp0, temp1, temp2;

    if(usLength == 0)
        return;

    usOffset = usOffset * 9;
    usOffset += _OSD_FONT_START_POSITION;

    CScalerSendAddr(_OSD_ADDR_MSB_90, _WRITE, _AUTOINC);
    CScalerSendByte((HIBYTE(usOffset) & 0x000f) | 0xd0);
    CScalerSendByte(LOBYTE(usOffset));
	CScalerSendWriteStop();

    if(ucPar == _COMPRESS_FONT)
    {
        ucVLDCnt    = 0;
        ucVLDTemp   = 0;
        pvldarray   = (pArray + 16);

        for(temp0=0;temp0<16;temp0++)
            pData[temp0] = *(pArray + temp0);
    }

	CScalerSendAddr(_OSD_DATA_PORT_92, _WRITE, _NON_AUTOINC);
	do
	{
		for (usOffset=0;usOffset<9;usOffset++)
		{
            if(ucPar == _COMPRESS_FONT)
            {
                temp0   = CScalerGetVLD() << 4;
                temp0   |= CScalerGetVLD();
                temp1   = CScalerGetVLD() << 4;
                temp1   |= CScalerGetVLD();
                temp2   = CScalerGetVLD() << 4;
                temp2   |= CScalerGetVLD();
            }
            else
            {
                temp0 = *pArray++;
                temp1 = *pArray++;
                temp2 = *pArray++;
            }
			
            // Rearrange the byte order
            CScalerSendByte((temp1 << 4) | (temp2 & 0x0f));
            CScalerSendByte((temp2 & 0xf0) | (temp0 & 0x0f));
            CScalerSendByte((temp0 & 0xf0) | (temp1 >> 4));
        }
	}
	while(--usLength);

	CScalerSendWriteStop();
}
#endif

BYTE CScalerGetVLD(void)
{
	BYTE zerocnt = 0;

    while(!CScalerGetBitVLD())   zerocnt  += 1;

    if(zerocnt == 0)    return *(pData);

    switch(zerocnt)
    {
        case 1:
            return (CScalerGetBitVLD() ? *(pData + 1) : *(pData + 2));

        case 2:
            return (CScalerGetBitVLD() ? *(pData + 3) : *(pData + 4));

        case 3:
            return (CScalerGetBitVLD() ? *(pData + 5) : *(pData + 6));

        case 4:
            if (CScalerGetBitVLD())
            {
                return (CScalerGetBitVLD() ? *(pData + 7) : *(pData + 8));
            }
            else
            {           
                if (CScalerGetBitVLD())
                {
                    return (CScalerGetBitVLD() ? *(pData + 9) : *(pData + 10));
                }
                else
                {
                    return (CScalerGetBitVLD() ? *(pData + 11) : *(pData + 12));
                }
            }

        default:
            if (CScalerGetBitVLD())
            {
                return (CScalerGetBitVLD() ? *(pData + 13) : *(pData + 14));
            }
            else
            {
                CScalerGetBitVLD();    
            
                return *(pData + 15);
            }
    }
}

bit CScalerGetBitVLD(void)
{
    ucVLDTemp = ((ucVLDCnt & 0x07) == 0) ? *(pvldarray++) : (ucVLDTemp << 1);

    ucVLDCnt += 1;

    return (bit)(ucVLDTemp & 0x80);
}

