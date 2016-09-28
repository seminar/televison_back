//----------------------------------------------------------------------------------------------------
// ID Code      : Misc.c No.0003
// Update Note  : 
//
//----------------------------------------------------------------------------------------------------

#define __MISC__

#include "Header\Include.h"


//----------------------------------------------------------------------------------------------------
// Polling Events
//----------------------------------------------------------------------------------------------------

#if (_SCALER_TYPE == _RTD2553V || _SCALER_TYPE == _RTD2546N || _SCALER_TYPE == _RTD2525L || _SCALER_TYPE == _RTD2547D)
#if(_RESET_TYPE == _RESET_IN)
//--------------------------------------------------
// Description  : Scaler Reset polling event
// Input Value  : None
// Output Value : Return _TRUE if Scaler Reset finished
//--------------------------------------------------
bit CMiscScalerResetEvent(void)
{
    if(!(bit)CScalerGetBit(bSCALERRESET, _BIT0))
    {
        return _TRUE;
    }
    else
    {
        return _FALSE;
    }
}
#endif  // End of #if(_RESET_TYPE == _RESET_IN)

#if(((_ADC_OFFSET_ADJUSTING == _ADJUST_BY_HW_ON_LINE) || (_ADC_OFFSET_ADJUSTING == _ADJUST_BY_HW_OFF_LINE)) && (_SCALER_TYPE == _RTD2525L || _SCALER_TYPE == _RTD2547D))         
//--------------------------------------------------
// Description  : H/W Auto Adjust ADC offset flag polling event
// Input Value  : None
// Output Value : Return _TRUE if event occurs
//--------------------------------------------------
bit CMiscAutoAdjustAdcOffsetFlagPollingEvent(void)
{
#if(_SCALER_TYPE == _RTD2547D)
    if(!(bit)CScalerGetBit(_P0_AUTO_BLACK_LEVEL_CTRL1_C0, _BIT0))
#else
    if(!(bit)CScalerGetDataPortBit(_ADC_ACCESS_PORT_DC, 0x18, _BIT0))
#endif
    {
        return _TRUE;
    }
    else
    {
        return _FALSE;
    }       
}           
#endif  // End of #if(((_ADC_OFFSET_ADJUSTING == _ADJUST_BY_HW_ON_LINE) || (_ADC_OFFSET_ADJUSTING == _ADJUST_BY_HW_OFF_LINE)) && (_SCALER_TYPE == _RTD2525L || _SCALER_TYPE == _RTD2547D))

#endif

//--------------------------------------------------
// Description  : Stable flag polling event
// Input Value  : None
// Output Value : Return _TRUE if event occurs
//--------------------------------------------------
#if(!_NEW_YPBPR || !_YPBPR_SUPPORT || _SCALER_TYPE == _RTD2525L || _SCALER_TYPE == _RTD2547D)
bit CMiscStableFlagPollingEvent(void)
{
#if (_SCALER_TYPE == _RTD2553V || _SCALER_TYPE == _RTD2546N || _SCALER_TYPE == _RTD2525L || _SCALER_TYPE == _RTD2547D)
    if((bit)CScalerGetBit(_STABLE_MEASURE_4F, _BIT7))
#else
    if((bit)CScalerGetBit(_STABLE_PERIOD_H_50, _BIT4))
#endif
    {
        return _TRUE;
    }
    else
    {
        return _FALSE;
    }
}
#endif

#if (_SCALER_TYPE == _RTD2553V || _SCALER_TYPE == _RTD2546N || _SCALER_TYPE == _RTD2525L || _SCALER_TYPE == _RTD2547D)
#if(_HSYNC_TYPE_DETECTION == _AUTO_RUN)
//--------------------------------------------------
// Description  : Hsync Type Detection Auto Run flag polling event
// Input Value  : None
// Output Value : Return _TRUE if event occurs
//--------------------------------------------------
bit CMiscHsyncTypeAutoRunFlagPollingEvent(void)
{
    if((bit)CScalerGetBit(_VSYNC_COUNTER_LEVEL_MSB_4C, _BIT7))
    {
        return _TRUE;
    }
    else
    {
        return _FALSE;
    }
}
#endif	// End of #if(_HSYNC_TYPE_DETECTION == _AUTO_RUN)
#endif

//--------------------------------------------------
// Description  : Measure start/end polling event
// Input Value  : None
// Output Value : Return _TRUE if measure finished
//--------------------------------------------------
bit CMiscModeMeasurePollingEvent(void)
{
    if(!(bit)CScalerGetBit(_MEAS_HS_PERIOD_H_52, _BIT5))
    {
        return _TRUE;
    }
    else
    {
        return _FALSE;
    }
}

#if((_TMDS_SUPPORT == _ON) || (_HDMI_SUPPORT == _ON))
//--------------------------------------------------
// Description  : Auto measure start/end polling event
// Input Value  : None
// Output Value : Return _TRUE if auto measure finished
//--------------------------------------------------
bit CMiscAutoMeasurePollingEvent(void)
{
    if(!(bit)CScalerGetBit(_AUTO_ADJ_CTRL1_7D, _BIT0))
    {
        return _TRUE;
    }
    else
    {
        return _FALSE;
    }
}
#endif

//--------------------------------------------------
// Description  : Apply double buffer polling event
// Input Value  : None
// Output Value : Return _TRUE if apply double buffer finished
//--------------------------------------------------
bit CMiscApplyDoubleBufferPollingEvent(void)
{
#if(_SCALER_TYPE == _RTD2547D)
    if(!(bit)CScalerGetBit(_VGIP_CTRL_10, _BIT5))
#else
    if(!(bit)CScalerGetBit(_VGIP_CTRL_05, _BIT5))
#endif
    {
        return _TRUE;
    }
    else
    {
        return _FALSE;
    }
}

#if(((_TMDS_SUPPORT == _ON) || (_HDMI_SUPPORT == _ON)) && (_DVI_LONG_CABLE_SUPPORT == _ON))
//--------------------------------------------------
// Description  : TMDS transition measure polling event
// Input Value  : None
// Output Value : Return _TRUE if measure finished
//--------------------------------------------------
bit CMiscTMDSMeasureEvent(void)
{
#if(_SCALER_TYPE == _RTD2547D)
    CScalerPageSelect(_PAGE2);
    if(!(bit)CScalerGetBit(_P2_TMDS_MEAS_RESULT0_A2, _BIT7))
#else
    if(!(bit)CScalerGetBit(_TMDS_MEAS_RESULT0_BD, _BIT7))
#endif
    {
        return _TRUE;
    }
    else
    {
        return _FALSE;
    }
}

//--------------------------------------------------
// Description  : TMDS CRC measure polling event
// Input Value  : None
// Output Value : Return _TRUE if CRC measure finished
//--------------------------------------------------
bit CMiscTMDSCRCEvent(void)
{
#if(_SCALER_TYPE == _RTD2547D)
    CScalerPageSelect(_PAGE2);
    if(!(bit)CScalerGetBit(_P2_TMDS_CTRL_A4, _BIT0))
#else
    if(!(bit)CScalerGetBit(_POWER_ON_OFF_CTRL_C2, _BIT0))
#endif
    {
        return _TRUE;
    }
    else
    {
        return _FALSE;
    }
}
#endif  // End of #if(((_TMDS_SUPPORT == _ON) || (_HDMI_SUPPORT == _ON)) && (_DVI_LONG_CABLE_SUPPORT == _ON))

//----------------------------------------------------------------------------------------------------
// Misc Functions
//----------------------------------------------------------------------------------------------------

//--------------------------------------------------
// Description  : Enable double buffer
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CMiscEnableDoubleBuffer(void)
{
#if(_SCALER_TYPE == _RTD2547D)
    CScalerSetBit(_VGIP_CTRL_10, ~_BIT4, _BIT4);
#else
    CScalerSetBit(_VGIP_CTRL_05, ~_BIT4, _BIT4);
#endif
}

//--------------------------------------------------
// Description  : Disable double buffer
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CMiscDisableDoubleBuffer(void)
{
#if(_SCALER_TYPE == _RTD2547D)
    CScalerSetBit(_VGIP_CTRL_10, ~_BIT4, 0x00);
#else
    CScalerSetBit(_VGIP_CTRL_05, ~_BIT4, 0x00);
#endif
}

//--------------------------------------------------
// Description  : Apply double buffer
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CMiscApplyDoubleBuffer(void)
{
#if(_SCALER_TYPE == _RTD2547D)
    if((bit)CScalerGetBit(_VGIP_CTRL_10, _BIT4))
    {
        CScalerSetBit(_VGIP_CTRL_10, ~_BIT5, _BIT5);
#else
    if((bit)CScalerGetBit(_VGIP_CTRL_05, _BIT4))
    {
        CScalerSetBit(_VGIP_CTRL_05, ~_BIT5, _BIT5);
#endif
        CTimerPollingEventProc(60, CMiscApplyDoubleBufferPollingEvent);
    }
}

//--------------------------------------------------
// Description  : Clear status Reg[02] and Reg[03]
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CMiscClearStatusRegister(void)
{
    CScalerSetByte(_STATUS0_02, 0x00);
    CScalerSetByte(_STATUS1_03, 0x00);
}

//--------------------------------------------------
// Description  : Set pin share
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CMiscSetPinShare(void)
{        
#if(_SCALER_TYPE == _RTD2547D)

    pData[0] = _MAIN_TYPE;
#if(_VIDEO_SUPPORT == _OFF)

    pData[1] = (((BYTE)_PIN_V8_ENABLE<<7) | (_PIN_V16_ENABLE<<6) | (_PIN_42<<4) | (_PIN_43<<3) | (_PIN_44<<2) | (_PIN_48));
    pData[2] = (((BYTE)_PIN_49<<6) | (_PIN_50<<4) | (_PIN_51<<2) | (_PIN_52));

#else

#if((_VIDEO_IN == _VIDEO_8_IN) || (_VIDEO_IN == _VIDEO_16_IN))
    pData[1] = (((BYTE)_PIN_V8_ENABLE<<7) | (_PIN_V16_ENABLE<<6));
    pData[2] = 0x00;
#endif

#endif
    pData[3] = (((BYTE)_PIN_53<<6) | (_PIN_54<<4) | (_PIN_55<<2) | (_PIN_56));
    pData[4] = (((BYTE)_PIN_57<<6) | (_PIN_58<<4) | (_PIN_59<<2) | (_PIN_56to59));
    pData[5] = ((BYTE)_PIN_62to65<<6);
    pData[6] = 0x00;
    pData[7] = 0x00;
    pData[8] = 0x00;
    pData[9] = 0x00;
    pData[10] = (((BYTE)_PIN_187<<6) | (_PIN_188<<4) | (_PIN_189<<2) | (_PIN_190));
    pData[11] = (((BYTE)_PIN_194<<6) | (_PIN_195<<4) | (_PIN_196<<2) | (_PIN_197));
    pData[12] = (((BYTE)_PIN_187_EN<<7) | (_PIN_188_EN<<6) | (_PIN_189_EN<<5) | (_PIN_190_EN<<4) | (_PIN_194_EN<<3) | (_PIN_195_EN<<2) | (_PIN_196_EN<<1) | (_PIN_197_EN));
    pData[13] = (((BYTE)_PIN_187_LEVEL<<7) | (_PIN_188_LEVEL<<6) | (_PIN_189_LEVEL<<5) | (_PIN_190_LEVEL<<4) | (_PIN_194_LEVEL<<3) | (_PIN_195_LEVEL<<2) | (_PIN_196_LEVEL<<1) | (_PIN_197_LEVEL));
    pData[14] = (((BYTE)_PIN_204to205<<6) | (_PIN_198<<4) | (_PIN_199<<2) | (_PIN_200));//Select to DDC2 for HDCP

    CScalerSetByte(_PS_ACCESS_PORT_8D, _PS_CTRL00_00);
    CScalerWrite(_PS_DATA_PORT_8E, 15, pData, _NON_AUTOINC);

    pData[0] = (((BYTE)_PIN_DRIVING_27to34<<4) | (_PIN_DRIVING_38to45));
    pData[1] = (((BYTE)_PIN_DRIVING_48to52<<4) | (_PIN_DRIVING_53to55));
    pData[2] = (((BYTE)_PIN_DRIVING_56to59<<4) | (_PIN_DRIVING_62to65));
    pData[3] = (((BYTE)_PIN_DRIVING_68to75_79to90<<4) | (_PIN_DRIVING_91to94_97to104));
    pData[4] = (((BYTE)_PIN_DRIVING_105to109<<4) | (_PIN_DRIVING_110));
    pData[5] = (((BYTE)_PIN_DRIVING_113to123<<4) | (_PIN_DRIVING_124to125));
    pData[6] = (((BYTE)_PIN_DRIVING_129to134<<4) | (_PIN_DRIVING_135to144_147to156_159to168));
    pData[7] = (((BYTE)_PIN_DRIVING_169to186<<4) | (_PIN_DRIVING_187to197));
    pData[8] = (((BYTE)_PIN_DRIVING_198to200<<4) | (_PIN_DRIVING_204to205));

    CScalerSetByte(_PS_ACCESS_PORT_8D, _PS_PIN_DRIVING_CTRL0_20);
    CScalerWrite(_PS_DATA_PORT_8E, 9, pData, _NON_AUTOINC);    

#endif // end #if(_SCALER_TYPE == _RTD2547D)

#if (_SCALER_TYPE == _RTD2553V)
    pData[0] = ((BYTE)_PIN_V16_FUNC << 2) | (_PIN_48);
    pData[1] = ((BYTE)_PIN_42 << 6) | (_PIN_43 << 4) | (_PIN_44 << 2) | (_PIN_45);
    pData[2] = ((BYTE)_PIN_3 << 6) | (_PIN_4 << 4) | (_PIN_110 << 3) | (_PIN_111);
    pData[3] = ((BYTE)_PIN_V16_FUNC << 7) | (_PIN_49 << 5) | (_PIN_52_53 << 4) | (_PIN_54 << 2) | (_PIN_55_56_57 << 1) | (_PIN_50_51) ;
    pData[4] = ((BYTE)_PIN_122 << 6) | (_PIN_112_113_114 << 4) | (_PIN_115_118_119 << 3) | (_PIN_120_121) ;

    CScalerSetByte(_PS_ACCESS_PORT_8D, 0x00);
    CScalerWrite(_PS_DATA_PORT_8E, 5, pData, _NON_AUTOINC);

#elif(_SCALER_TYPE == _RTD2525L)

    CScalerSetByte(_PS_ACCESS_PORT_8D, 0x00);
    CScalerSetByte(_PS_DATA_PORT_8E, (_PIN_43 << 6) | (_PIN_44 << 5) | 0x00);

#elif(_SCALER_TYPE == _RTD2533B)

    pData[0] = (_PIN_3 << 6) | (_PIN_4 << 4) | (_PIN_48 << 2) | (_PIN_49);
    pData[1] = (_PIN_50_51 << 7);
    pData[1] |= (_PIN_52_53 << 6); 
    pData[1] |= (_PIN_54 << 4);
    pData[1] |= (_PIN_55_56_57 << 3);
    pData[1] |= (_PIN_122_FUNC << 2);
    pData[1] |= (_PIN_110 << 1);
    pData[2] = (_PIN_111 << 6);
    pData[2] |= (_PIN_112_113_114 << 4);
    pData[2] |= (_PIN_115_118_119 << 3);
    pData[2] |= (_PIN_120_121 << 1);
    pData[2] |= (_PIN_122);

    CScalerWrite(_PIN_SHARE_CTRL0_8D, 3, pData, _AUTOINC);

#endif

#if((_SCALER_TYPE == _RTD2023L) || (_SCALER_TYPE == _RTD2023S) || (_SCALER_TYPE == _RTD2023L_VB) || (_SCALER_TYPE == _RTD2023S_VB))

    CScalerSetBit(_PIN_SHARE_CTRL0_8D, 
                  ~(_BIT7 | _BIT6), 
                  ((_PIN_21_TO_40 << 7) | (_PIN_16_17_OR_43_44 << 6)));

#endif



#if (_SCALER_TYPE == _RTD2546N)
 
    pData[0] = ((BYTE)_PIN_V16_FUNC << 2) | (_PIN_53);
    pData[1] = ((BYTE)_PIN_44 << 6) | (_PIN_45 << 4) | (_PIN_46 << 2) | (_PIN_47);
    pData[2] = ((BYTE)_PIN_4 << 6) | (_PIN_5 << 4);
    pData[3] = ((BYTE)_PIN_V16_FUNC << 7) | (_PIN_54 << 5) | (_PIN_55_56);
    pData[4] = ((BYTE)_PIN_113_114 << 4);
 
    CScalerSetByte(_PS_ACCESS_PORT_8D, 0x00);
    CScalerWrite(_PS_DATA_PORT_8E, 5, pData, _NON_AUTOINC);
 
#endif
}

//----------------------------------------------------------------------------------------------------
// Debug Functions
//----------------------------------------------------------------------------------------------------

#if(_ISPACK && _ISPACK_TYPE == _ISPACK_RTD)
//--------------------------------------------------
// Description  : ISP process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CMiscIspack(void)
{
    BYTE ddcdata2in, ddcdata3in;
    BYTE halt = 0;

    do
    {
        CScalerRead(_DDC_STATUS_F8, 1, pData, _NON_AUTOINC);

        if((pData[0] & 0x04) != 0)                      // data latched
        {
            CScalerRead(_DDC_SUB_IN_F5, 2, pData, _AUTOINC);
            CScalerSetByte(_DDC_STATUS_F8, 0x00);

            if((pData[0] & 0x80) != 0)                  // run or halt command
            {
                halt = pData[1];
            }
            else if((pData[0] & 0x10) == 0x10)          // Andy Ext. cmd
            {
                 switch(pData[0] & 0x0f)
                 {
                      case 0:                           // Virtual Key
                           ucVirtualKey = pData[1];
                           break;
                      case 1:                           // read stk & MTV512 xdata
                           {
                                unsigned char xdata *p;
                                p = (0xf00 + pData[1]);
                                CScalerSetByte(_DDC_CTRL_F7, 0x0A);
                                CScalerSetByte(_DDC_DATA_IN_F6, *p);
                                CScalerSetByte(_DDC_CTRL_F7, 0x08);                                
                                break;
                           }
                      case 2:                           // write stk & MTV512 xdata
                           {
                                unsigned char xdata *p;
                                p = (0xf00 + ddcdata2in);
                                *p = pData[1];
                                break;
                           }   
                      case 3:                           // read rtd2120 xdata
                           {
                                unsigned char xdata *p;
                                p = (0xff00 + pData[1]);
                                CScalerSetByte(_DDC_CTRL_F7, 0x0A);
                                CScalerSetByte(_DDC_DATA_IN_F6, *p);
                                CScalerSetByte(_DDC_CTRL_F7, 0x08);                                
                                break;
                           }
                      case 4:                           // write rtd2120 xdata
                           {
                                unsigned char xdata *p;
                                p = (0xff00 + ddcdata2in);
                                *p = pData[1];
                                break;
                           }                         
                      case 5:                          // change to uart mode 
                           #if(_RS232 == _ON)
                           ChagneToUart();
                           CUartPutString("MCU : ENTER UART MODE.");
                           halt = 0;
                           #endif

                           break;
                      default:
                           break;
                 }
            }
            else if((pData[0] & 0x40) == 0x40)          // read command
            {
                switch(pData[0] & 0x0f)
                {
                    case(0x04) :                        // read eeprom
                    {
                        CI2cRead(ddcdata2in, pData[1], 1, &pData[13]);
                        CScalerSetByte(_DDC_CTRL_F7, 0x0A);
                        CScalerSetByte(_DDC_DATA_IN_F6, pData[13]);
                        CScalerSetByte(_DDC_CTRL_F7, 0x08);
                    }
                    break;

                    case(0x01):                         //read scalar
                    {
                        CScalerRead(pData[1], 1, &pData[13], _NON_AUTOINC);
                        CScalerSetBit(_DDC_CTRL_F7, ~_BIT2, _BIT2);         //reset index
                        CScalerSetBit(_DDC_CTRL_F7, ~_BIT1, _BIT1);         //change to MCU write
                        CScalerSetByte(_DDC_DATA_IN_F6,pData[13]);
                        CScalerSetBit(_DDC_CTRL_F7, ~_BIT1, 0x00);          //change to pc write        
                        CScalerSetBit(_DDC_CTRL_F7, ~_BIT2, _BIT2);         //reset index
                    }
                    break;               
                }
            }
            else //if((pData[0] & 0x20) == 0x20)             
            {
                switch (pData[0] & 0x0F)                //Write command
                {
                    case 0x00:
                        CScalerSetByte(ddcdata2in, pData[1]);
                        break; 

                    case 0x01:
                    case 0x02:                          // for RTD & I2c Device
                        ddcdata2in = pData[1];
                        break;

                    case 0x06:
                    case 0x03:                          // for I2c Device
                    case 0x08:
                        ddcdata3in = pData[1];
                        break;

                    case 0x04 :                         // for I2c Device
                        CI2cWrite(ddcdata2in, pData[1], 1, &ddcdata3in);
                        break;
                }
            }
        }
    }
    while(halt == 1);

}
//--------------------------------------------------
void GetVirtualKey(void)
{
    if(ucKeyMessage == _NONE_KEY_MESSAGE)
    {
        ucKeyMessage = ucVirtualKey;
    }
    ucVirtualKey = _NONE_KEY_MESSAGE;
}
//--------------------------------------------------
#endif   //#if(ISPACK_TYPE == ISPACK_RTD)


//--------------------------------------------------
// Description  : Debug tool process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CMiscIspDebugProc(void)
{
    #if(_ISPACK && _ISPACK_TYPE == _ISPACK_RTD)
    CMiscIspack();
	#endif

	#if(_ISPACK && _ISPACK_MCU == _ISPACK_TYPE)
	DDCCI_Command();
	#endif

    #if(_RS232 == _ON)
    CUartHandler();
    #endif
}


