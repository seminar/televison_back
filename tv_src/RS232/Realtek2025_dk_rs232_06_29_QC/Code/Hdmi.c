//----------------------------------------------------------------------------------------------------
// ID Code      : RTD2528R_Hdmi.c No.0000
// Update Note  : 
//
//----------------------------------------------------------------------------------------------------

#define __RTD2547D_HDMI__

#include "Header\Include.h"

#if(_SCALER_TYPE == _RTD2547D)


#if((_HDMI_SUPPORT == _ON) || (_TMDS_SUPPORT == _ON))

//--------------------------------------------------
// Description  : Detect DVI/HDMI input format
// Input Value  : None
// Output Value : Return _FALSE if Input Format isn't HDMI, _TRUE while Input Format is HDMI
//--------------------------------------------------
bit CHdmiFormatDetect(void)
{
    CScalerPageSelect(_PAGE2);
    CScalerRead(_P2_HDMI_SR_CB, 1, pData, _NON_AUTOINC);

    if((pData[0] & 0x01) == 0x01)//Input source is the HDMI format.
        return _TRUE; 
    else                   
        return _FALSE; 
}
#endif

#if(_HDMI_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Detect Audio Lock status
// Input Value  : None
// Output Value : Return _FALSE if Audio Lock is ok, _TRUE while Audio mislock, FIFO underflow/overflow
//--------------------------------------------------
bit CHdmiAudioFIFODetect(void)
{
    CScalerPageSelect(_PAGE2);
    CScalerRead(_P2_HDMI_SR_CB, 1, pData, _NON_AUTOINC);

    if((pData[0] & 0x06) == 0)
        return _FALSE;

    return _TRUE;
}

//--------------------------------------------------
// Description  : HDMI Video Setting
// Input Value  : None
// Output Value : Return _FALSE if Set_AVMute is true, _TRUE while Video Setting is OK.
//--------------------------------------------------
bit CHdmiVideoSetting(void)
{                 
    CScalerPageSelect(_PAGE2);
    CScalerSetDataPortBit(_P2_HDMI_ADDR_PORT_C9, _P2_HDMI_SCR_00, ~(_BIT1 | _BIT0), _BIT1);//Set HDMI/DVI decide condition
    CTimerDelayXms(50);

    if(CHdmiFormatDetect())//Input source is the HDMI format.
    { 
        SET_HDMIINPUT();

        CScalerSetBit(_P2_ANALOG_COMMON_CTRL2_AB, ~(_BIT3 | _BIT2), 0x00);

#if(_HDCP_SUPPORT == _ON)
        CScalerSetDataPortByte(_P2_HDCP_ADDR_PORT_C3, 0x40, 0x93);//Change to HDCP1.1 for HDMI
#endif
//HDMI Video & Audio Part
        CScalerRead(_P2_HDMI_SR_CB, 1, pData, _NON_AUTOINC);
        if(!(bit)(pData[0] & 0x40))//For Clear_AVMute
        {
            SET_AVRESUME();//Audio WD can't action, when Set_AVMute happen.
            CAdjustDisableHDMIWatchDog(_WD_SET_AVMUTE_ENABLE);//Disable Set_AVMute Watch Dog
            CScalerSetDataPortBit(_P2_HDMI_ADDR_PORT_C9, _P2_HDMI_AVMCR_30, ~_BIT3, _BIT3);//Enable DVI/HDMI video output
            CAdjustEnableHDMIWatchDog(_WD_SET_AVMUTE_ENABLE);//Enable Set_AVMute Watch Dog
        }
        else
        {
            CTimerDelayXms(100);//For AV_Mute Delay
            CLR_AVRESUME();
            return _FALSE;
        }

//HDMI Video Part
        CScalerRead(_P2_HDMI_GPVS_CC, 1, pData, _NON_AUTOINC);
//        if(((bit)(pData[0] & 0x01)) || GET_VIDEOMODECHANGE())//For HDMI switch between RGB/YCbCr
        if((bit)(pData[0] & 0x01))
        {
//            CLR_VIDEOMODECHANGE();
            CScalerSetBit(_P2_HDMI_GPVS_CC, ~_BIT0, _BIT0);
            CScalerGetDataPortByte(_P2_HDMI_PSAP_CD, 0x00, 1, pData, _NON_AUTOINC);
            if((pData[0] & 0x23) == 0)//Check BCH data(Package error flag)
            {
                CScalerGetDataPortByte(_P2_HDMI_PSAP_CD, 0x04, 2, pData, _NON_AUTOINC);

                if((bit)(pData[0] & 0x40) != (bit)(pData[0] & 0x20))//For HDMI switch between RGB/YUV
                {
                    if((pData[0] & 0x20) == 0x20)
                        CScalerSetBit(_VGIP_ODD_CTRL_13, ~_BIT3, _BIT3);//For 4:2:2
                    else if((pData[0] & 0x40) == 0x40)
                        CScalerSetBit(_VGIP_ODD_CTRL_13, ~_BIT3, 0x00);//For 4:4:4
    
                    if((pData[1] & 0xc0) != 0xc0)//For HDMI switch between ITU601/ITU709
                    {
                        CScalerSetByte(_YUV2RGB_CTRL_9C, 0x08);
               
                        if((bit)(pData[1] & 0x40))
                        {
                            CScalerCodeW(tHDMI_YPBPR_ITU601);
                        }
                        else
                        {
                            CScalerCodeW(tHDMI_YPBPR_ITU709);
                        }
                        CScalerSetByte(_YUV2RGB_CTRL_9C, 0x05);
                    }
                }
                else if(!(bit)(pData[0] & 0x60))
                {
                    CScalerSetByte(_YUV2RGB_CTRL_9C, 0x00);
                    CScalerSetBit(_VGIP_ODD_CTRL_13, ~_BIT3, 0x00);
                }
            }
        }
    }
    else
    {
        CLR_HDMIINPUT();
        CScalerSetDataPortBit(_P2_HDMI_ADDR_PORT_C9, _P2_HDMI_AVMCR_30, ~_BIT3, _BIT3);//Enable DVI/HDMI video output
        CScalerSetDataPortByte(_P2_HDCP_ADDR_PORT_C3, 0x40, 0x91);// Change to HDCP1.0 for DVI    
        CScalerSetByte(_YUV2RGB_CTRL_9C, 0x00);
        CScalerSetBit(_VGIP_ODD_CTRL_13, ~_BIT3, 0x00);
    }
    return _TRUE;
}

//--------------------------------------------------
// Description  : Setting Audio Frequence Mode 
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CHdmiAudioFirstTracking(void)
{
    BYTE coeff = 0, s = 0, o = 1;
    WORD a = 1024, b = 0, m = 0;
    DWORD cts = 0, n = 0, freq = 0;

    CScalerPageSelect(_PAGE2);
    CScalerRead(_P2_HDMI_SR_CB, 1, pData, _NON_AUTOINC);

    if((CHdmiAudioFIFODetect() || GET_AVRESUME()) && (!(bit)(pData[0] & 0x40)))//For HDMI audio pll setting
    {   
        CLR_AVRESUME();

        CScalerSetDataPortBit(_P2_HDMI_ADDR_PORT_C9, _P2_HDMI_WDCR0_31, ~(_BIT2 | _BIT1), 0x00);//Disable Audio Watch Dog
	    CScalerSetDataPortByte(_P2_HDMI_ADDR_PORT_C9, _P2_HDMI_PSCR_15, 0x00);//Disable FIFO Trend
	    CScalerSetDataPortByte(_P2_HDMI_ADDR_PORT_C9, _P2_HDMI_CMCR_10, 0x50);//Update Double Buffer
        CScalerSetBit(_P2_HDMI_APC_C8, ~_BIT0, _BIT0);//HDMI Address Auto Increase Enable

        CScalerSetDataPortBit(_P2_HDMI_ADDR_PORT_C9, _P2_HDMI_ACRCR_51, ~_BIT1, _BIT1);
        CScalerSetDataPortBit(_P2_HDMI_ADDR_PORT_C9, _P2_HDMI_NTX1024TR0_28, ~_BIT3, _BIT3);
        CTimerDelayXms(2);

        CScalerGetDataPortByte(_P2_HDMI_ADDR_PORT_C9, _P2_HDMI_ACRSR0_52, 5, pData, _NON_AUTOINC);
        cts = ((DWORD)pData[0] << 12) | ((DWORD)pData[1] << 4) | (((DWORD)pData[2] >> 4) & 0x0f);
        n =   (((DWORD)pData[2] & 0x0f) << 16) | ((DWORD)pData[3] << 8) | (DWORD)pData[4];

        CScalerGetDataPortByte(_P2_HDMI_ADDR_PORT_C9, _P2_HDMI_NTX1024TR0_28, 2, pData, _NON_AUTOINC);
        b = (((WORD)pData[0] & 0x07) << 8) | (WORD)pData[1];

        // Fa = (a*Fx*n)/(b*cts*128) = (1024*Fx*n)/(b*cts*128) = (8*Fx*n)/(b*cts)
        // calculate freq in 0.1kHz unit
        freq = (DWORD)8 * 2 * 10000 * _RTD_XTAL / cts * n / ((DWORD)b * 1000);  
        freq = (freq >> 1) + (freq & 0x01);

        if((freq >= 318) && (freq <= 322))
        {
            coeff = _AUDIO_MCK_32000;
            freq  = 32000;
            ucAudioRate = 0;
        }
        else if((freq >= 438) && (freq <= 444))
        {
            coeff = _AUDIO_MCK_44100;
            freq  = 44100;
            ucAudioRate = 0;
        }
        else if((freq >= 476) && (freq <= 484))
        {
            coeff = _AUDIO_MCK_48000;
            freq  = 48000;
            ucAudioRate = 0;
        }
        else if((freq >= 877) && (freq <= 887))
        {
            coeff = _AUDIO_MCK_88200;
            freq  = 88200;
            ucAudioRate = 1;
        }
        else if((freq >= 955) && (freq <= 965))
        {
            coeff = _AUDIO_MCK_96000;
            freq  = 96000;
            ucAudioRate = 1;
        }
        else if((freq >= 1754) && (freq <= 1774))
        {
            coeff = _AUDIO_MCK_176400;
            freq  = 176400;
            ucAudioRate = 2;
        }
        else if((freq >= 1910) && (freq <= 1930))
        {
            coeff = _AUDIO_MCK_192000;
            freq  = 192000;
            ucAudioRate = 2;
        }
        else 
        {
            SET_AVRESUME();
        }

        if(!GET_AVRESUME())
        {
            do
            {
                s = s + 4;
                ((DWORD *)pData)[0] = (DWORD)128 * freq * coeff * s;
            }
            while (((DWORD *)pData)[0] < 180000000);

            o = 1; 
            m = ((DWORD *)pData)[0] * 2 / ((DWORD)_RTD_XTAL * 1000);
            //m = (DWORD)2 * 128 * freq * coeff * s / _RTD_XTAL / 1000;
            //m = (m >> 1) + (m & 0x01);
            m = m + 1;
            s = s / (o * 2);

            CScalerSetDataPortByte(_P2_HDMI_ADDR_PORT_C9, _P2_HDMI_AAPNR_2D, 0x08);  // Disable SDM

            CScalerSetDataPortByte(_P2_HDMI_ADDR_PORT_C9, _P2_HDMI_MCAPR_11, (m - 2));
            CScalerSetDataPortByte(_P2_HDMI_ADDR_PORT_C9, _P2_HDMI_SCAPR_12, (coeff == _AUDIO_256_TIMES) ? ((s / 2) | 0x80) : (s / 2));

#if(_AUDIO_LOCK_MODE == _HARDWARE_TRACKING)

            // Calculate D code
            ((DWORD *)pData)[1] = (DWORD)1000 * _RTD_XTAL * m / 2;  // PLL freq
            if (((DWORD *)pData)[0] > ((DWORD *)pData)[1])
            {
                a = (((DWORD *)pData)[0] - ((DWORD *)pData)[1]) * 128 / (((DWORD *)pData)[1] / 2048);
      
                a = 0xffff - a;
            }
            else
            {
                a = (((DWORD *)pData)[1] - ((DWORD *)pData)[0]) * 128 / (((DWORD *)pData)[1] / 2048);

                a += 100; // MUST for compatibility
            }

            CScalerSetDataPortByte(_P2_HDMI_ADDR_PORT_C9, _P2_HDMI_DCAPR0_13, a >> 8);
            CScalerSetDataPortByte(_P2_HDMI_ADDR_PORT_C9, _P2_HDMI_DCAPR1_14, a & 0xff);
#endif
            CScalerSetDataPortBit(_P2_HDMI_ADDR_PORT_C9, _P2_HDMI_DPCR0_38, ~(_BIT5 | _BIT4), (o << 4));

            // Calculate Ich for audio PLL
            pData[0] = (m < 5) ? 0 : ((m / 5) - 1);
            CScalerSetDataPortByte(_P2_HDMI_ADDR_PORT_C9, _P2_HDMI_DPCR1_39, pData[0] | 0x80);

            CScalerSetDataPortByte(_P2_HDMI_ADDR_PORT_C9, _P2_HDMI_DPCR3_3B, 0x03); // Enable K and enable VCOSTART
    
            CScalerSetDataPortByte(_P2_HDMI_ADDR_PORT_C9, _P2_HDMI_CMCR_10, 0x50);  //Enable Double Buffer for K/M/S/D/O

            CScalerSetDataPortBit(_P2_HDMI_ADDR_PORT_C9, _P2_HDMI_DPCR0_38, ~(_BIT7 | _BIT6), 0x00);    // Enable PLL
            CTimerDelayXms(1);

#if(_AUDIO_LOCK_MODE == _HARDWARE_TRACKING)
            do
            {
                CScalerSetDataPortByte(_P2_HDMI_ADDR_PORT_C9, _P2_HDMI_AAPNR_2D, 0x00);  // Disable SDM
                CScalerSetDataPortByte(_P2_HDMI_ADDR_PORT_C9, _P2_HDMI_AAPNR_2D, 0x02);  // Enable SDM
                CTimerDelayXms(1);
                CScalerGetDataPortByte(_P2_HDMI_ADDR_PORT_C9, _P2_HDMI_DPCR3_3B + 1, 2, pData, _NON_AUTOINC);
            }
            while((((a >> 8) & 0xff) != pData[0]) || (((a >> 0) & 0xff) != pData[1]));
#endif
            CScalerSetDataPortByte(_P2_HDMI_ADDR_PORT_C9, _P2_HDMI_AOCR_62, 0x00);//Disable SPDIF/I2S Output
            CAdjustDisableHDMIWatchDog(_WD_SET_AVMUTE_ENABLE);//Disable Set_AVMute Watch Dog
            CScalerSetDataPortBit(_P2_HDMI_ADDR_PORT_C9, _P2_HDMI_AVMCR_30, ~_BIT5, _BIT5);//Enable Audio Output
            CAdjustEnableHDMIWatchDog(_WD_SET_AVMUTE_ENABLE);//Enable Set_AVMute Watch Dog

#if(_AUDIO_LOCK_MODE == _HARDWARE_TRACKING)
            //H/W FIFO Tracking
            CScalerSetDataPortByte(_P2_HDMI_ADDR_PORT_C9, _P2_HDMI_PSCR_15, 0x04);//Enable boundary tracking
    	    CScalerSetDataPortByte(_P2_HDMI_ADDR_PORT_C9, _P2_HDMI_ICBPSR1_25, 0x01);//Set I code 
	        CScalerSetDataPortByte(_P2_HDMI_ADDR_PORT_C9, _P2_HDMI_PCBPSR1_27, 0x01);//Set P code
	        CScalerSetDataPortByte(_P2_HDMI_ADDR_PORT_C9, _P2_HDMI_STBPR_2A, 0x80);//Set Boundary Tracking Update Response Time
	        CScalerSetDataPortByte(_P2_HDMI_ADDR_PORT_C9, _P2_HDMI_AAPNR_2D, 0xC2);

    	    CScalerSetDataPortByte(_P2_HDMI_ADDR_PORT_C9, _P2_HDMI_FBR_1B, 0xe2);//0xe5 for DVR team ?
            CScalerSetDataPortBit(_P2_HDMI_ADDR_PORT_C9, _P2_HDMI_WDCR0_31, ~_BIT5, _BIT5);//Enable FIFO Tracking

    	    CScalerSetDataPortByte(_P2_HDMI_ADDR_PORT_C9, _P2_HDMI_CMCR_10, 0x50);//update double buffer

            CScalerSetByte(_P2_HDMI_SR_CB, 0x07);//Write 1 clear
	
            //Fine tune
	        CScalerSetDataPortByte(_P2_HDMI_ADDR_PORT_C9, _P2_HDMI_PSCR_15, 0xEC);//Enable FIFO Trend
    	    CScalerSetDataPortByte(_P2_HDMI_ADDR_PORT_C9, _P2_HDMI_FTR_1A, 0x03);
	        CScalerSetDataPortByte(_P2_HDMI_ADDR_PORT_C9, _P2_HDMI_ICTPSR1_21, 0x07);
	        CScalerSetDataPortByte(_P2_HDMI_ADDR_PORT_C9, _P2_HDMI_CMCR_10, 0x50);//Update Double Buffer
#else
            CScalerSetDataPortByte(_P2_HDMI_ADDR_PORT_C9, _P2_HDMI_PSCR_15, 0xfe);//Enable N/CTS tracking
            CScalerSetDataPortByte(_P2_HDMI_ADDR_PORT_C9, 0x1d, 0x05);//Set I code 
            CScalerSetDataPortByte(_P2_HDMI_ADDR_PORT_C9, 0x1f, 0x9F);//Set P code
            CScalerSetDataPortByte(_P2_HDMI_ADDR_PORT_C9, _P2_HDMI_AAPNR_2D, 0x02);
            CScalerSetDataPortByte(_P2_HDMI_ADDR_PORT_C9, _P2_HDMI_CMCR_10, 0x50);//update double buffer
#endif
            SET_AUDIOWAITINGFLAG();
        }
        else
        {
            CLR_AUDIOWAITINGFLAG();
            CLR_AUDIOPLLLOCKREADY();
        }
    }
    else
    {
        CLR_AUDIOPLLLOCKREADY();
    }
}

//--------------------------------------------------
// Description  : Enable Audio Output
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CHdmiEnableAudioOutput(void)
{
    CLR_AUDIOWAITINGTIMEOUT();

    if(GET_AUDIOWAITINGFLAG())
    {
        CScalerSetByte(_P2_HDMI_SR_CB, 0x07);//Write 1 clear
        CLR_AUDIOWAITINGFLAG();
        SET_AUDIOPLLLOCKREADY();
    }
    else
    {
        if (CHdmiAudioFIFODetect() || GET_AVRESUME())//For HDMI audio pll setting
        {
            CHdmiAudioFirstTracking();
            CLR_AUDIOPLLLOCKREADY();
        }
        else if (GET_AUDIOPLLLOCKREADY())
        {
            CLR_AUDIOPLLLOCKREADY();

            CScalerSetDataPortByte(_P2_HDMI_ADDR_PORT_C9, _P2_HDMI_AOCR_62, 0xff);//Enable SPDIF/I2S Output

#if(_AUDIO_LOCK_MODE == _HARDWARE_TRACKING)
            CScalerSetDataPortByte(_P2_HDMI_ADDR_PORT_C9, _P2_HDMI_AFCR_03, 0x26);//Enable Audio FIFO
#else
            CScalerSetDataPortByte(_P2_HDMI_ADDR_PORT_C9, _P2_HDMI_AFCR_03, 0x40);//Enable Audio FIFO
#endif
            CScalerSetDataPortBit(_P2_HDMI_ADDR_PORT_C9, _P2_HDMI_WDCR0_31, ~(_BIT2 | _BIT1), (_BIT2 | _BIT1));//Enable Audio Watch Dog
            CAdjustEnableHDMIWatchDog(_WD_AUDIO_FOR_TMDS_CLOCK);//Enable Audio Watch Dog for TMDS clock

#if(_DAC_SUPPORT == _ON)
            CHdmiAdjustDACSampleRate(ucAudioRate);
#endif
        }
    }
    CTimerActiveTimerEvent(SEC(0.5), CHdmiAudioWaitingFlagReadyEven);
}

//--------------------------------------------------
// Description  : Audio Waiting Time Flag Ready
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CHdmiAudioWaitingFlagReadyEven(void)
{
    SET_AUDIOWAITINGTIMEOUT();
}

#if(_DAC_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Reset DAC Chip
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CHdmiResetDAC(void)
{
/*
    bAUDIOM1 = _LOW;
    bAUDIOM2 = _LOW;

    bAUDIORESET = _HIGH;
    CTimerDelayXms(5);
    bAUDIORESET = _LOW;
    CTimerDelayXms(5);
    bAUDIORESET = _HIGH;*/
}

//--------------------------------------------------
// Description  : Adjust DAC Sample Rate 
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CHdmiAdjustDACSampleRate(BYTE ucModeType)
{
    pData[0] = 0x20;
    pData[1] = (0x90 | ucModeType);
    CI2cWrite(0x20, 0x0c, 1, &pData[0]);
    CI2cWrite(0x20, 0x01, 1, &pData[1]);
}
#endif //End of #if(_DAC_SUPPORT == _ON)

#endif //End of #if(_HDMI_SUPPORT == _ON)


#endif  // End of #if(_SCALER_TYPE == _RTD2547D)
