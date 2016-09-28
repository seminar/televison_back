#define __DDCCI__
#include <string.h>
#include "Header\Include.h"

#define _MODE_FIRST                 252
#define _MODE_EXIST                 253
#define _MODE_NOSUPPORT             254
#define _MODE_NOSIGNAL              255

#define GET_COLOR_TEMP_TYPE()           (stSystemData.ColorTemp & (_BIT3 | _BIT2 | _BIT1 | _BIT0))
#define SET_COLOR_TEMP_TYPE(x)          (stSystemData.ColorTemp = ((stSystemData.ColorTemp & ~(_BIT3 | _BIT2 | _BIT1 | _BIT0)) | x))

sbit bDDCSCLVGA = P3^0;
#define bDDCSCLDVI    (_MCU_PORT56)
 //---------------------------------------------------------------------------------------
void Init_DDCCI()
{

#if(_MCU_TYPE == _MYSON_MTV312 || _MCU_TYPE == _MYSON_MTV512)

	MCU_IICCTR_F00         = 0x00;    // Enable IIC Interface and define ddc2 active at HSDA/HSCL
	MCU_INTEN_F04          = 0xc0;    // Detect WslvA1 IIC Stop Condition
	MCU_INTFLG_F48         = 0x00;    // Clear IIC Interrupt register
	MCU_CTRSLVB_F0A        = 0x00;    // Define IIC Protocal Slave Address Bit
    // Mark by eric 0615  move to initial mcu to initial this port
	MCU_DDCCTRA1_F06       = 0x00;    // Disable DDC1
	MCU_SLVA1ADR_F07       = 0x80 | (0xa0>>1);  // DDC Slave A1 address
	MCU_DDCCTRA2_F86       = 0x50;    // Enable DDC1 and DDCRAM 128 Access
	MCU_SLVA2ADR_F87       = 0x80 | (0xa0>>1);     // DDC Slave A2 address	
	MCU_SLVBADR_F09        = 0x80 | (0x6e>>1);

#elif(_MCU_TYPE == _RTD_2120)

	MCU_I2C_STATUS_FF2B    = 0x00;
	MCU_I2C_IRQ_CTRL_FF2C  = 0x0c;
	MCU_I2C_SET_SLAVE_FF27 = 0x6E;
    MCU_OPTION_FF38        = 0x80; 

#endif

	EX1 = 1;
}
//---------------------------------------------------------------------------------------
#if(_MCU_TYPE == _MYSON_MTV312 || _MCU_TYPE == _MYSON_MTV512)
void ReceiveEDIDINT1(void) interrupt 2
{
       unsigned char tempflag;

       tempflag = M512_IIC_INTFLG;

       EA  = 0;
       EX1 = 0;   	   	   
       if(tempflag & RCBI)	    // SLAVEB Interrupt
       {
            DDCCI_RxInt();
            M512_IIC_INTFLG = tempflag & (~RCBI);  //Clear DDCRAMA IIC Stop Interrupt detect
       }
       else if(tempflag & TXBI)	    // SLAVEB Interrupt
       {
            DDCCI_TxInt();
            M512_IIC_INTFLG = tempflag & (~TXBI);  //Clear DDCRAMA IIC Stop Interrupt detect
       }

       EX1 = 1;
       EA  = 1;
}
//---------------------------------------------------------------------------------------------
#elif(_MCU_TYPE == _RTD_2120)

void ReceiveEDIDINT1(void) interrupt 2
{
	BYTE tempflag;
	
	tempflag = MCU_I2C_STATUS_FF2B;
	EA  = 0;


    if(tempflag & DINI)	    // SLAVEB Interrupt
	{
		DDCCI_RxInt();
		MCU_I2C_STATUS_FF2B = tempflag & (~DINI);  //Clear DDCRAMA IIC Stop Interrupt detect
	}
	else if(tempflag & DOUTI)	    // SLAVEB Interrupt
	{
		DDCCI_TxInt();
		MCU_I2C_STATUS_FF2B = tempflag & (~DOUTI);  //Clear DDCRAMA IIC Stop Interrupt detect
    }
    EA  = 1;
}
#endif

void DDCCI_RxInt()
{
#if(_MCU_TYPE == _MYSON_MTV312 || _MCU_TYPE == _MYSON_MTV512)
     unsigned char rxByte = M512_IIC_TXRCBBUF;
#elif(_MCU_TYPE == _RTD_2120)
     unsigned char rxByte = MCU_I2C_DATA_IN_FF29;
#endif

     switch(rxStatus)
     {
            case DDC2B_CLEAR:

#if(_MCU_TYPE == _MYSON_MTV312 || _MCU_TYPE == _MYSON_MTV512)
                if (rxByte == DDC2B_SRC_ADDRESS)
                {
                     rxStatus = DDC2B_SRCADDRESS;
                     ucDDCCI_CheckSum = INITRxCK;
                     ucDDCCI_RxIndex  = 0;
                }

                break;

#elif(_MCU_TYPE == _RTD_2120)

                if ( MCU_I2C_SUB_IN_FF28 == DDC2B_SRC_ADDRESS )
                {
                    rxStatus = DDC2B_SRCADDRESS;
                    ucDDCCI_CheckSum = INITRxCK;
                }
                else
                {
                    DDCCI_InitRx();
                    break;
                }

#endif
            // getting the length...
            case DDC2B_SRCADDRESS:
                // get the length
                ucDDCCI_RxCount = rxByte & (~DDC2Bi_CONTROL_STATUS_FLAG);
                // ...and if yes save the received byte in the rxBuffer
                // and update the pointers...
                ucDDCCI_RxBuf[ucDDCCI_RxIndex++] = rxByte;
                ucDDCCI_CheckSum ^= rxByte;
                // ...set the receive body state...
                rxStatus = DDC2B_COMMAND;
                //...and if it is a NULL message...
                if (ucDDCCI_RxCount == 0)
                {
                        // ...wait for CK
                        //rxStatus++;// = DDC2B_RECBODY;
                        //rxStatus++;// = DDC2B_WAITFORCK;
                        rxStatus = DDC2B_WAITFORCK; 
                }

                else if(ucDDCCI_RxCount > RX_BUFFER_SIZE)
                {
                     DDCCI_InitRx();
                }
                break;
            // ...here we are getting the command...
            case DDC2B_COMMAND:
                // ...go to the recbody state
                rxStatus = DDC2B_RECBODY;
                // ...here we are getting the message body...
            case DDC2B_RECBODY:
                ucDDCCI_RxBuf[ucDDCCI_RxIndex++] = rxByte;
                ucDDCCI_CheckSum ^= rxByte;
                ucDDCCI_RxCount--;
                // ...and if this is the last byte in the message body...
                if (ucDDCCI_RxCount == 0)
                // ...set the wait for checksum flag
                    rxStatus = DDC2B_WAITFORCK;
                break;
            case DDC2B_WAITFORCK:
                // ...and if we have a checksum match...
                if (ucDDCCI_CheckSum == rxByte)
                {
                        // ...raise the completed flag - the buffer will be
                        // processed by the parser...
                        rxStatus = DDC2B_COMPLETED;
                }
                // ..else we have a checksum error...
                else
                {
                        // ...clear the rxState and the current buffer for a new message
                        DDCCI_InitRx();
                }
                break;
            default:
                DDCCI_InitRx();
                break;

     }
}
//---------------------------------------------------------------------------------------
void DDCCI_TxInt()
{
    WORD i = 0x200;

#if(DEBUG_ONLY)

    do
    {
        Delay5us();
    }
    while(bDDCSCLVGA && --i);

#else

    if(stSystemData.InputSource == _SOURCE_DVI)
    {
        do
        {
            Delay5us();
        }
        while(bDDCSCLDVI && --i);
    }
    else// if(GET_INPUTSOURCE_TYPE()==_SOURCE_VGA)
    {
        do
        {
            Delay5us();
        }
        while(bDDCSCLVGA && --i);   // For other source 
    }

#endif

    if (ucDDCCI_TxCount == 0)
    {
            txBufferPtr = &ucDDCCI_NullStr[0];
            ucDDCCI_TxCount = sizeof (ucDDCCI_NullStr);
    }
    // ...send out the current byte
    #if(_MCU_TYPE == _MYSON_MTV312 || _MCU_TYPE == _MYSON_MTV512)
    M512_IIC_TXRCBBUF = *txBufferPtr++;

    #elif(_MCU_TYPE == _RTD_2120)
    
    MCU_I2C_DATA_OUT_FF2A = *txBufferPtr++;
    #endif

    ucDDCCI_TxCount--;
}
//---------------------------------------------------------------------------------------
void DDCCI_InitRx(void)
{
	// clear the rxState...
	rxStatus = DDC2B_CLEAR;
	// ...and the current buffer for a new message
	ucDDCCI_RxIndex = 0;
}
//---------------------------------------------------------------------------------------
void DDC2Bi_InitTx (void)
{
	// initialize the transmit communication, so that either a valid...
	// ...or a NULL message is sent on a request from host
	txBufferPtr = &ucDDCCI_NullStr[0];
	ucDDCCI_TxCount = sizeof(ucDDCCI_NullStr) - 1;

#if(_MCU_TYPE == _MYSON_MTV312 || _MCU_TYPE == _MYSON_MTV512)
	M512_IIC_TXRCBBUF = *txBufferPtr++;
#elif(_MCU_TYPE == _RTD_2120)
    MCU_I2C_DATA_OUT_FF2A = *txBufferPtr++;
#endif
}
//---------------------------------------------------------------------------------------
void DDCCI_Command()
{
    do
	{
		if(rxStatus == DDC2B_COMPLETED)
		{
			DDCCI_Command_Do();
			DDCCI_InitRx();
		}
	}
	while(fDDCCI_Loop);
}
//---------------------------------------------------------------------------------------
void DDCCI_Command_Do()
{
    switch(ucDDCCI_RxBuf[COMMAND])
    {
		#if(DEBUG_ONLY == 0)
        case DDC2B_CMD_GetVCPFeature:             GetVCPFeature();             break;
        case DDC2B_CMD_SetVCPFeature:             SetVCPFeature();             break;
        case DDC2B_CMD_CapabilitiesRequest:       DDCCI_GetCapabilitiesRequest(); break;                            break;
        case DDC2B_CMD_GetTimingReport:           DDCCI_GetTimingReport();     break;
        //case DDC2B_CMD_NMV_GetVCPPage:		      DDCCI_GetVCPPage();	       break;
        //case DDC2B_CMD_NMV_GetPagedVCP:		      DDCCI_GetPagedVCP();	       break;
        //case DDC2B_CMD_NMV_SetPagedVCP:		      DDCCI_SetPagedVCP();	       break;
        //case DDC2B_CMD_SaveCurrentSettings:       DDCCI_SaveSetting();         break;
        //case DDC2B_CMD_NMV_EEPROM:                DDCCI_EEPRom_Cmd();        break;
		#endif	  //end debug only
        case DDC2B_CMD_DEBUG:                     DDCCI_Debug();               break;
        default:                                  DDC2Bi_InitTx();	           break;

    }
}
//---------------------------------------------------------------------------------------
void TxCommandReady()
{
     unsigned char ucChecksum,i,count;
     count = ucDDCCI_TxBuf[CI_LENGTH];
     ucDDCCI_TxBuf[CI_LENGTH] = count | 0x80;
     //ucDDCCI_TxCount += 2;
     ucChecksum = INITTxCK;
     for(i=0;i<=count;i++)
         ucChecksum ^= ucDDCCI_TxBuf[i];

     count++;

     ucDDCCI_TxBuf[count] = ucChecksum;
     count++;

     ucDDCCI_TxBuf[count] = 0x6e;
     count ++;
     
     ucDDCCI_TxBuf[count] = 0x6e;
     count ++;
     EA = 0;

     txBufferPtr = &ucDDCCI_TxBuf[CI_LENGTH];
     ucDDCCI_TxCount = count;
     // clear the expected flag
     //readExpected = 0;
     // set messageReady flag
#if(_MCU_TYPE == _RTD_2120)

     MCU_I2C_DATA_OUT_FF2A = 0x6e;

#else      // mtv512 
     M512_IIC_TXRCBBUF = 0x6e;
#endif

     messageReady = 1;
     EA = 1;

}
//---------------------------------------------------------------------------------------

#if(DEBUG_ONLY == 0)
void TxCommandGetTimingReportReady()
{
     unsigned char ucChecksum,i,count;
     count = ucDDCCI_TxBuf[CI_LENGTH];
    // ucDDCCI_TxBuf[CI_LENGTH] = count | 0x80;
     //ucDDCCI_TxCount += 2;
     ucChecksum = INITTxCK;
     for(i=0;i<=count;i++)
         ucChecksum ^= ucDDCCI_TxBuf[i];

     count++;

     ucDDCCI_TxBuf[count] = ucChecksum;
     count ++;

     ucDDCCI_TxBuf[count] = 0x6e;
     count ++;

     ucDDCCI_TxBuf[count] = 0x6e;
     count ++;

     EA = 0;

     txBufferPtr = &ucDDCCI_TxBuf[CI_LENGTH];
     ucDDCCI_TxCount = count;
     // clear the expected flag
     //readExpected = 0;
     // set messageReady flag

    count++;

    for(i=count;i>0;i--)
        ucDDCCI_TxBuf[i] = ucDDCCI_TxBuf[i - 1];
    
    ucDDCCI_TxBuf[0] = 0x6e;

#if(_MCU_TYPE == _RTD_2120)

    MCU_I2C_DATA_OUT_FF2A = *txBufferPtr++;

#else      // mtv512 

    M512_IIC_TXRCBBUF = *txBufferPtr++;

#endif


    //messageReady = 1;
    // re enable interrupts
    EA = 1;
}
#endif
//---------------------------------------------------------------------------------------
#define GETVCP_CMD     2


#if(DEBUG_ONLY == 0)

void GetVCPFeature()
{
     //ucVPC_Page = 0;
     ucDDCCI_TxBuf[CI_LENGTH]	= 0x08;
     ucDDCCI_TxBuf[COMMAND]	= DDC2B_CMD_GetVCPFeature_Reply;
     ucDDCCI_TxBuf[2]           = 0;                            // RC
     ucDDCCI_TxBuf[3]           = ucDDCCI_RxBuf[PARAMETER];     // CP
     ucDDCCI_TxBuf[4]           = 0;                            // TP
     switch(ucDDCCI_RxBuf[PARAMETER])
     {
         case DDC2B_CMD_VCP_Clock:              GetVPC_Clock(5);              break;
         case DDC2B_CMD_VCP_Brightness:         GetVPC_Bright(5);             break;
         case DDC2B_CMD_VCP_Contrast:           GetVPC_Contrast(5);           break;
         case DDC2B_CMD_VCP_RedGain:            GetVPC_RedGain(5);            break;
         case DDC2B_CMD_VCP_GreenGain:          GetVPC_GreenGain(5);          break;
         case DDC2B_CMD_VCP_BlueGain:           GetVPC_BlueGain(5);           break;
         case DDC2B_CMD_VCP_HPosition:          GetVPC_HPosition(5);          break;
         case DDC2B_CMD_VCP_VPosition:          GetVPC_VPosition(5);          break;
         case DDC2B_CMD_VCP_ClockPhase:         GetVPC_Phase(5);              break;
         case DDC2B_CMD_VCP_SelectColorPreset:  GetVPC_ColorTmp(5);           break;
         //case DDC2B_CMD_VCP_MonitorType:        GetMonitorType(5);            break;
           
         //case DDC2B_CMD_VCP_Language:       GetVPC_Language(5);           break;
         //case DDC2B_CMD_VCP_AudioVolume:	  GetVPC_Volume(5);		break;
         //case DDC2B_CMD_VCP_SSP:			  GetVPC_Specturm(5);		break;//Extend for DDL
         default:
              ucDDCCI_TxBuf[2]           = 1;                            // RC cmd not support
              ucDDCCI_TxBuf[4]           = 1;
              TxCommandReady();
              break;
     }

}
//---------------------------------------------------------------------------------------
void GetVPC_Clock(unsigned char BassAddr)            // Range : 78 ~ 178
{
     ucVPC_Page = 0;
     ucDDCCI_TxBuf[BassAddr]        = 0;                              // MH
     ucDDCCI_TxBuf[BassAddr + 1]    = 100;                            // ML
     ucDDCCI_TxBuf[BassAddr + 2]    = 0;
	 ucDDCCI_TxBuf[BassAddr + 3]	= ClockGuage();                   // SL
     TxCommandReady();
}
//---------------------------------------------------------------------------------------
void GetVPC_Bright(unsigned char BassAddr)           // Range : 0 ~ 100
{
     ucVPC_Page = 0;
     ucDDCCI_TxBuf[BassAddr]           = 0;                              // MH
     ucDDCCI_TxBuf[BassAddr + 1]           = 100;                            // ML
     ucDDCCI_TxBuf[BassAddr + 2]           = 0;                              // SH
     
	 ucDDCCI_TxBuf[BassAddr + 3] = stSystemData.BackLight;
     TxCommandReady();
}
//---------------------------------------------------------------------------------------
void GetVPC_Contrast(unsigned char BassAddr)         // Range : 0 ~ 100
{
     ucVPC_Page = 0;
     ucDDCCI_TxBuf[BassAddr]           = 0;                              // MH
     ucDDCCI_TxBuf[BassAddr + 1]           = 100;                            // ML
     ucDDCCI_TxBuf[BassAddr + 2]           = 0;                              // SH

     ucDDCCI_TxBuf[BassAddr + 3] = stConBriData.Contrast;
     TxCommandReady();
}
//---------------------------------------------------------------------------------------
void GetVPC_RedGain(unsigned char BassAddr)          // Range : 0 ~ 255
{
	ucVPC_Page = 0;
	ucDDCCI_TxBuf[BassAddr] = 0;					// MH
	ucDDCCI_TxBuf[BassAddr + 1]	= 0xff;			// ML
	ucDDCCI_TxBuf[BassAddr + 2]	= 0;				// SH
	ucDDCCI_TxBuf[BassAddr + 3]	= stColorTempData.ColorTemp[_RED];
    TxCommandReady();
}
//---------------------------------------------------------------------------------------
void GetVPC_GreenGain(unsigned char BassAddr)        // Range : 0 ~ 255
{
	ucVPC_Page = 0;
	ucDDCCI_TxBuf[BassAddr] = 0;					// MH

    ucDDCCI_TxBuf[BassAddr + 1]	= 0xff;			// ML
    ucDDCCI_TxBuf[BassAddr + 2]	= 0;			// SH
    ucDDCCI_TxBuf[BassAddr + 3]	= stColorTempData.ColorTemp[_GREEN];

    TxCommandReady();
}
//---------------------------------------------------------------------------------------
void GetVPC_BlueGain(unsigned char BassAddr)         // Range : 0 ~ 255
{
	ucVPC_Page = 0;
	ucDDCCI_TxBuf[BassAddr] = 0;				// MH

    ucDDCCI_TxBuf[BassAddr + 1]	= 0xff;			// ML
    ucDDCCI_TxBuf[BassAddr + 2]	= 0;			// SH
    ucDDCCI_TxBuf[BassAddr + 3]	= stColorTempData.ColorTemp[_BLUE];
    TxCommandReady();
}
//---------------------------------------------------------------------------------------
void GetVPC_HPosition(unsigned char BassAddr)        // Range : ucH_Min_Margin ~ ucH_Max_Margin
{
    WORD usTemp = _HPOSITION_BIAS * 2;
	ucVPC_Page = 0;
	ucDDCCI_TxBuf[BassAddr]	= (usTemp >> 8);					// MH
	ucDDCCI_TxBuf[BassAddr + 1]	= (usTemp & 0xff);				// ML
	ucDDCCI_TxBuf[BassAddr + 2]	= 0;				// SH
	ucDDCCI_TxBuf[BassAddr + 3] = stModeUserData.HPosition - (stModeUserCenterData.CenterHPos - _HPOSITION_BIAS);
    TxCommandReady();
}
//---------------------------------------------------------------------------------------
void GetVPC_VPosition(unsigned char BassAddr)        // Range : ucV_Min_Margin ~ (unsigned int)256 - ucV_Min_Margin
{
    WORD usTemp = _HPOSITION_BIAS * 2;
	
	ucVPC_Page = 0;
	ucDDCCI_TxBuf[BassAddr]	= (usTemp >> 8);					// MH
	ucDDCCI_TxBuf[BassAddr + 1]	= (usTemp & 0xff);
	ucDDCCI_TxBuf[BassAddr + 2]	= 0;				// SH
    ucDDCCI_TxBuf[BassAddr + 3] = stModeUserData.VPosition - (stModeUserCenterData.CenterVPos - _VPOSITION_BIAS);
	TxCommandReady();
}
//---------------------------------------------------------------------------------------
void GetVPC_Phase(unsigned char BassAddr)            // Range : 0 ~ 31
{
	//WORD Phasetemp;

	ucVPC_Page = 0;
	ucDDCCI_TxBuf[BassAddr]	= 0;					// MH
	ucDDCCI_TxBuf[BassAddr + 1]	= 100;				// ML
	ucDDCCI_TxBuf[BassAddr + 2]	= 0;				// SH
	//Phasetemp = stModeUserData.Phase;
	ucDDCCI_TxBuf[BassAddr + 3]	= PHASE_GUAGE;
	TxCommandReady();
}
//---------------------------------------------------------------------------------------
void GetVPC_ColorTmp(unsigned char BassAddr)
{
	ucVPC_Page = 0;
	ucDDCCI_TxBuf[BassAddr]	= 0;					// MH
	ucDDCCI_TxBuf[BassAddr + 1]	= 0x0b;				// ML
	ucDDCCI_TxBuf[BassAddr + 2]	= 0;				// SH
	switch(GET_COLOR_TEMP_TYPE() )
	{ 
        case _CT_5800:  ucDDCCI_TxBuf[BassAddr + 3] = 0x04;             break;
		case _CT_USER:  ucDDCCI_TxBuf[BassAddr + 3] = 0x0b;             break;
		case _CT_6500:	ucDDCCI_TxBuf[BassAddr + 3] = 0x08;             break;
		case _CT_9300:	ucDDCCI_TxBuf[BassAddr + 3] = 0x05;             break;
		default:		ucDDCCI_TxBuf[BassAddr + 3] = 0x0b;             break;
	}
	TxCommandReady();
}
//---------------------------------------------------------------------------------------

/*
void GetVPC_Language(unsigned char BassAddr)
{


     ucVPC_Page = 0;
     ucDDCCI_TxBuf[BassAddr]           = 0;                                 // MH
     ucDDCCI_TxBuf[BassAddr + 1]           = 0x0b;
     ucDDCCI_TxBuf[BassAddr + 2]           = 0;                                 // SH
     #if(DDCCI_ALL)
	 switch(GET_LANGUAGE)
     {
          case ENGLISH:         ucDDCCI_TxBuf[BassAddr + 3] = 0x01;     break;
          case CHINESE_S:       ucDDCCI_TxBuf[BassAddr + 3] = 0x0a;     break;
          case FRE:             ucDDCCI_TxBuf[BassAddr + 3] = 0x03;     break;
          case GER:             ucDDCCI_TxBuf[BassAddr + 3] = 0x02;     break;
          case ITA:             ucDDCCI_TxBuf[BassAddr + 3] = 0x06;     break;
          case SPA:             ucDDCCI_TxBuf[BassAddr + 3] = 0x04;     break;
          case POR:             ucDDCCI_TxBuf[BassAddr + 3] = 0x07;     break;
          case Pol:             ucDDCCI_TxBuf[BassAddr + 3] = 0x08;     break;
          case Russian:         ucDDCCI_TxBuf[BassAddr + 3] = 0x09;     break;
          case CHINESE_T:       ucDDCCI_TxBuf[BassAddr + 3] = 0x0b;     break;
          case JAPANESS:        ucDDCCI_TxBuf[BassAddr + 3] = 0x05;     break;
          default:              ucDDCCI_TxBuf[BassAddr + 3] = 0x01;     break;
     }
	 #endif

     TxCommandReady();
}
//---------------------------------------------------------------------------------------
/*
void GetVPC_Volume(unsigned char BassAddr)
{
	ucDDCCI_TxBuf[BassAddr]           = 0;                                 // MH
	ucDDCCI_TxBuf[BassAddr + 1]           = 100;
	ucDDCCI_TxBuf[BassAddr + 2]           = 0;                                 // SH
	ucDDCCI_TxBuf[BassAddr + 3] = stOsdUserData.Volume;
	TxCommandReady();

}
//---------------------------------------------------------------------------------------
void GetVPC_Specturm(unsigned char BassAddr)
{
	ucDDCCI_TxBuf[BassAddr]           = 0;                                 // MH
	ucDDCCI_TxBuf[BassAddr + 1]           = 15;
	ucDDCCI_TxBuf[BassAddr + 2]           = 0;                                 // SH
	ucDDCCI_TxBuf[BassAddr + 3] = 0;//stOsdUserData.OsdManagementFlag & 0x0f;
	TxCommandReady();

}
//---------------------------------------------------------------------------------------
*/
#define SETVCP_PARAM    4
void SetVCPFeature()
{
     switch(ucDDCCI_RxBuf[PARAMETER])
     {
         case DDC2B_CMD_VCP_ALLReset:           
		      //AnwerDDCCISet();
			  //SetVPC_ALLReset(ucDDCCI_RxBuf[SETVCP_PARAM]);         
			  break;
         case DDC2B_CMD_VCP_ColorReset:         
		      //AnwerDDCCISet();
		      //SetVPC_ColorReset(ucDDCCI_RxBuf[SETVCP_PARAM]);         
			  break;
         case DDC2B_CMD_VCP_Clock:
              //EA = 0;
              SetVPC_Clock(ucDDCCI_RxBuf[SETVCP_PARAM]);
              SetVPC_ClockDo();
              //EA = 1;
              break;
         case DDC2B_CMD_VCP_Brightness:
              SetVPC_Bright(ucDDCCI_RxBuf[SETVCP_PARAM]);
              SetVPC_BrightDo();
              break;
         case DDC2B_CMD_VCP_Contrast:
              SetVPC_Contrast(ucDDCCI_RxBuf[SETVCP_PARAM]);
              SetVPC_ContrastDo();
              break;
         case DDC2B_CMD_VCP_RedGain:
              SetVPC_RedGain(ucDDCCI_RxBuf[SETVCP_PARAM]);
              SetVPC_RedGainDo(ucDDCCI_RxBuf[SETVCP_PARAM]);
              break;
         case DDC2B_CMD_VCP_GreenGain:
              SetVPC_GreenGain(ucDDCCI_RxBuf[SETVCP_PARAM]);
              SetVPC_GreenGainDo(ucDDCCI_RxBuf[SETVCP_PARAM]);
              break;
         case DDC2B_CMD_VCP_BlueGain:
              SetVPC_BlueGain(ucDDCCI_RxBuf[SETVCP_PARAM]);
              SetVPC_BlueGainDo(ucDDCCI_RxBuf[SETVCP_PARAM]);
              break;

         case DDC2B_CMD_VCP_AutoSetUp:
              //CAutoDoAutoConfig();
              // Repeat
              ucOsdEventMsg = _DO_AUTO_CONFIG;
              break;

         case DDC2B_CMD_VCP_HPosition:
              SetVPC_HPosition(ucDDCCI_RxBuf[SETVCP_PARAM]);
              SetVPC_HPositionDo();
              break;
         case DDC2B_CMD_VCP_VPosition:
              SetVPC_VPosition(ucDDCCI_RxBuf[SETVCP_PARAM]);
              SetVPC_VPositionDo();
              break;
         case DDC2B_CMD_VCP_ClockPhase:
              SetVPC_Phase(ucDDCCI_RxBuf[SETVCP_PARAM]);
              SetVPC_PhaseDo();
              break;
         case DDC2B_CMD_VCP_SelectColorPreset:
              SetVPC_ColorTmp(ucDDCCI_RxBuf[SETVCP_PARAM]);
              SetVPC_ColorTmpDo();
              break;
         case DDC2B_CMD_VCP_Language:           
		      //SetVPC_Language(ucDDCCI_RxBuf[SETVCP_PARAM]);           
			  break;
     }
}
//---------------------------------------------------------------------------------------
/*
void SetVPC_ALLReset(unsigned char ucValue)
{
     ucVPC_Page = 0;
     //AnwerDDCCISet();

     if(ucValue)
     {
		 #if(DDCCI_ALL)
         Reset_Fac();
		 #endif
     }
}
//---------------------------------------------------------------------------------------
void SetVPC_ColorReset(unsigned char ucValue)
{
     ucVPC_Page = 0;
     //AnwerDDCCISet();
     if(ucValue)
     {
         #if(DDCCI_ALL)
		 Reset_User();
		 #endif
     }
}
//---------------------------------------------------------------------------------------
*/
void SetVPC_Clock(unsigned char ucValue)
{
	DWORD wClocktemp;
    WORD usClockMax = COsdFxGetAdcClockRange(_GET_CLOCKRANGE_MAX);
    WORD usClockMin = COsdFxGetAdcClockRange(_GET_CLOCKRANGE_MIN);

    ucVPC_Page = 0;
        
	wClocktemp = ucValue;
	wClocktemp = wClocktemp * ((DWORD)usClockMax - (DWORD)usClockMin) / (DWORD)100;
	stModeUserData.Clock = wClocktemp + usClockMin;
}
//---------------------------------------------------------------------------------------
void SetVPC_ClockDo()
{
	CAdjustAdcClock(stModeUserData.Clock);
    ucOsdEventMsg = _SAVE_EE_OSDUSERDATA_MSG;
}
//---------------------------------------------------------------------------------------
void SetVPC_Bright(unsigned char ucValue)           // Range : 0 ~ 100
{
     ucVPC_Page = 0;
     if(ucValue > 100)    return;
     stSystemData.BackLight = ucValue;
     stConBriData.Brightness = ucValue;
}
//---------------------------------------------------------------------------------------
void SetVPC_BrightDo()
{
    CAdjustBacklight();
    ucOsdEventMsg = _SAVE_EE_SYSTEMDATA_MSG;
}
//---------------------------------------------------------------------------------------
void SetVPC_Contrast(unsigned char ucValue)         // Range : 0 ~ 100
{
     ucVPC_Page = 0;
     if(ucValue > 100)    return;
     stConBriData.Contrast = ucValue;
}
//---------------------------------------------------------------------------------------
void SetVPC_ContrastDo()         // Range : 0 ~ 100
{
	CAdjustContrast();
    ucOsdEventMsg = _SAVE_EE_BriConHueSat_MSG;
}
//---------------------------------------------------------------------------------------
void SetVPC_RedGain(unsigned char ucValue)          // Range : 0 ~ 255
{
     ucVPC_Page = 0;
     stColorTempData.ColorTemp[_RED] = ucValue;
}
//---------------------------------------------------------------------------------------
void SetVPC_RedGainDo(unsigned char ucValue)          // Range : 0 ~ 255
{
	CAdjustContrast();
	ucValue = ucValue;
    ucOsdEventMsg = _SAVE_EE_COLORPROC1_MSG;
}
//---------------------------------------------------------------------------------------
void SetVPC_GreenGain(unsigned char ucValue)        // Range : 0 ~ 255
{
     ucVPC_Page = 0;
     stColorTempData.ColorTemp[_GREEN] = ucValue;
}
//---------------------------------------------------------------------------------------
void SetVPC_GreenGainDo(unsigned char ucValue)        // Range : 0 ~ 255
{
	CAdjustContrast();
	ucValue = ucValue;
    ucOsdEventMsg = _SAVE_EE_COLORPROC1_MSG;
}
//---------------------------------------------------------------------------------------
void SetVPC_BlueGain(unsigned char ucValue)         // Range : 0 ~ 255
{
     ucVPC_Page = 0;

     stColorTempData.ColorTemp[_BLUE] = ucValue;
}
//---------------------------------------------------------------------------------------
void SetVPC_BlueGainDo(unsigned char ucValue)         // Range : 0 ~ 255
{
	CAdjustContrast();
	ucValue = ucValue;
    ucOsdEventMsg = _SAVE_EE_COLORPROC1_MSG;
}
//---------------------------------------------------------------------------------------
void SetVPC_HPosition(WORD ucValue)
{
	if(ucValue > 100)		return;
	ucVPC_Page = 0;

    stModeUserData.HPosition = ucValue + (stModeUserCenterData.CenterHPos - _HPOSITION_BIAS);
}
//---------------------------------------------------------------------------------------
void SetVPC_HPositionDo()        // Range : ucH_Min_Margin ~ ucH_Max_Margin
{
	CAdjustHPosition();
    ucOsdEventMsg = _SAVE_EE_MODEUSERDATA_MSG;
}
//---------------------------------------------------------------------------------------
void SetVPC_VPosition(WORD ucValue)        // Range : ucV_Min_Margin ~ (unsigned int)256 - ucV_Min_Margin
{
	if(ucValue > 100)		return;
	ucVPC_Page = 0;
    
    stModeUserData.VPosition = ucValue + (stModeUserCenterData.CenterVPos - _VPOSITION_BIAS);
}
//---------------------------------------------------------------------------------------
void SetVPC_VPositionDo()        // Range : ucV_Min_Margin ~ (unsigned int)256 - ucV_Min_Margin
{
	CAdjustVPosition();
    ucOsdEventMsg = _SAVE_EE_MODEUSERDATA_MSG;
}
//---------------------------------------------------------------------------------------
void SetVPC_Phase(unsigned char ucValue)            // Range : 0 ~ 31
{
	WORD Phasetemp;
	if(ucValue > 100)		return;

	ucVPC_Page = 0;
	Phasetemp = (WORD)ucValue * 63 / 100;
	stModeUserData.Phase = Phasetemp;
}
//---------------------------------------------------------------------------------------
void SetVPC_PhaseDo()            // Range : 0 ~ 31
{
	CAdjustPhase(stModeUserData.Phase);
    ucOsdEventMsg = _SAVE_EE_MODEUSERDATA_MSG;
}
//---------------------------------------------------------------------------------------
void SetVPC_ColorTmp(unsigned char ucValue)
{
     ucVPC_Page = 0;
     ucValue=ucValue;
	 #if(DDCCI_ALL)
     switch(ucValue)
     {
          case 0x05:        SET_COLOR_TEMP_TYPE(_CT_6500);      break;
          case 0x04:        SET_COLOR_TEMP_TYPE(_CT_5800);      break;
          case 0x08:        SET_COLOR_TEMP_TYPE(_CT_9300);      break;
          case 0x0b:        SET_COLOR_TEMP_TYPE(_CT_USER);      break;
          default:          SET_COLOR_TEMP_TYPE(_CT_USER);      break;
     }
	 #endif
}
//---------------------------------------------------------------------------------------
void SetVPC_ColorTmpDo()
{
    CEepromLoadColorTempData();
    CAdjustContrast();
    ucOsdEventMsg = _SAVE_EE_SYSTEMDATA_MSG;
}
//---------------------------------------------------------------------------------------
unsigned char code sCpReqStr[] =
//"vcp(04 08 0E 10 12 14(04 05 08) 16 18 1A 20 30 3E 54 62 68 B6 C0 DF) type(LCD) mccs_ver(1.1) asset_eep(32) mpu(0.04) "; // accroding to HP John's SPEC removed 1E
"vcp(0E 10 12 14(04 05 08 0B) 16 18 1A 20 30 3E 54 62 68 B6 C0 DF) type(LCD) mccs_ver(1.1) asset_eep(32) mpu(0.04) "; // accroding to HP John's SPEC removed 1E

void DDCCI_GetCapabilitiesRequest()
{

    BYTE ucSendLen;
    BYTE i;
    WORD usStrLength,usOffset;

    usOffset = ucDDCCI_RxBuf[2];
    usOffset = (usOffset << 8) | ucDDCCI_RxBuf[3];
    
    usStrLength = sizeof(sCpReqStr);
    if (usOffset >= usStrLength)
    {
        ucSendLen = 0;
    }
    else
    {
        if(usStrLength >= usOffset + 12)
            ucSendLen = 12;
        else 
            ucSendLen = usStrLength - usOffset;
    }
        
    ucDDCCI_TxBuf[CI_LENGTH]    = ucSendLen;
    ucDDCCI_TxBuf[COMMAND]      = 0xe3;
    ucDDCCI_TxBuf[2]            = (unsigned char)(usOffset >> 8);
    ucDDCCI_TxBuf[3]            = (unsigned char)(usOffset );
    
    for(i=0;i<ucSendLen;i++)
    {
        ucDDCCI_TxBuf[4 + i] = sCpReqStr[i + usOffset];
    }

    TxCommandReady();
}
//---------------------------------------------------------------------------------------


void DDCCI_GetTimingReport()
{
	WORD dwTemp0 = stModeInfo.IHFreq * 10;
	WORD dwTemp2 = stModeInfo.IVFreq * 10;

	ucDDCCI_TxBuf[CI_LENGTH]	= 0x06;
	ucDDCCI_TxBuf[COMMAND]	    = 0x4e;
	ucDDCCI_TxBuf[2]	        = 0x00;
	// Calc SS : timing status byte
	if(_MODE_NOSUPPORT <= stModeInfo.ModeCurr)   ucDDCCI_TxBuf[2] |= 0x80;
	if((stModeInfo.Polarity & _BIT1))            ucDDCCI_TxBuf[2] |= 0x02;
	if((stModeInfo.Polarity & _BIT0))            ucDDCCI_TxBuf[2] |= 0x01;
	
	ucDDCCI_TxBuf[3]	        = HIBYTE(dwTemp0);
	ucDDCCI_TxBuf[4]	        = LOBYTE(dwTemp0);
	ucDDCCI_TxBuf[5]	        = HIBYTE(dwTemp2);
	ucDDCCI_TxBuf[6]	        = LOBYTE(dwTemp2);

	TxCommandGetTimingReportReady();
}
//---------------------------------------------------------------------------------------
/*
void DDCCI_GetVCPPage()
{
     ucDDCCI_TxBuf[CI_LENGTH]	= 0x03;
     ucDDCCI_TxBuf[COMMAND]	= 0xc5;
     ucDDCCI_TxBuf[2]           = ucVPC_Page;
     ucDDCCI_TxBuf[3]           = 2;
     TxCommandReady();
}
//---------------------------------------------------------------------------------------
void DDCCI_GetPagedVCP()
{
     //ucVPC_Page = 2;
     ucDDCCI_TxBuf[CI_LENGTH]	= 0x09;
     ucDDCCI_TxBuf[COMMAND]	= 0xc7;
     ucDDCCI_TxBuf[2]           = 0;                            // RC
     ucDDCCI_TxBuf[3]           = ucDDCCI_RxBuf[2];                            // VCCP
     ucDDCCI_TxBuf[4]           = ucDDCCI_RxBuf[3];             // CP
     ucDDCCI_TxBuf[5]           = 0;                            // TP  Momentary
     switch(ucDDCCI_RxBuf[3])
     {
         case DDC2B_CMD_VCP_Clock:              GetVPC_Clock(6);              break;
         case DDC2B_CMD_VCP_Brightness:         GetVPC_Bright(6);             break;
         case DDC2B_CMD_VCP_Contrast:           GetVPC_Contrast(6);           break;
         case DDC2B_CMD_VCP_RedGain:            GetVPC_RedGain(6);            break;
         case DDC2B_CMD_VCP_GreenGain:          GetVPC_GreenGain(6);          break;
         case DDC2B_CMD_VCP_BlueGain:           GetVPC_BlueGain(6);           break;
         case DDC2B_CMD_VCP_HPosition:          GetVPC_HPosition(6);          break;
         case DDC2B_CMD_VCP_VPosition:          GetVPC_VPosition(6);          break;
         case DDC2B_CMD_VCP_ClockPhase:         GetVPC_Phase(6);              break;
         case DDC2B_CMD_VCP_SelectColorPreset:  GetVPC_ColorTmp(6);           break;
         case DDC2B_CMD_VCP_MonitorType:        GetMonitorType(6);            break;
         //case DDC2B_CMD_VCP_Language:           GetVPC_Language(6);           break;
         //case DDC2B_CMD_VCP_OSDHPosition:       GetNMVVPC_OSDH();              break;
         //case DDC2B_CMD_VCP_OSDVPosition:       GetNMVVPC_OSDV();              break;
         default:
              ucDDCCI_TxBuf[2]           = 1;                            // RC cmd not support
              ucDDCCI_TxBuf[5]		     = 1;
			  TxCommandReady();
              break;
     }
}
//---------------------------------------------------------------------------------------
void DDCCI_SetPagedVCP()
{
     //ucVPC_Page = 2;
     ucDDCCI_TxBuf[CI_LENGTH]	= 0x09;
     ucDDCCI_TxBuf[COMMAND]		= 0xc7;
     ucDDCCI_TxBuf[2]           = 0;                            // RC
     ucDDCCI_TxBuf[3]           = ucDDCCI_RxBuf[2];                     // VCCP
     ucDDCCI_TxBuf[4]           = ucDDCCI_RxBuf[3];             // CP
     ucDDCCI_TxBuf[5]           = 0;                            // TP  Set parameter
     switch(ucDDCCI_RxBuf[3])
     {
         case DDC2B_CMD_VCP_ALLReset:
              AnwerDDCCISet();
              //SetVPC_ALLReset(ucDDCCI_RxBuf[5]);
              break;
         case DDC2B_CMD_VCP_ColorReset:
              AnwerDDCCISet();
              //SetVPC_ColorReset(ucDDCCI_RxBuf[5]);
              break;
         case DDC2B_CMD_VCP_Clock:
              SetVPC_Clock(ucDDCCI_RxBuf[5]);
              GetVPC_Clock(6);
              SetVPC_ClockDo();
              break;
         case DDC2B_CMD_VCP_Brightness:
              SetVPC_Bright(ucDDCCI_RxBuf[5]);
              GetVPC_Bright(6);
              SetVPC_BrightDo();
              break;
         case DDC2B_CMD_VCP_Contrast:
              SetVPC_Contrast(ucDDCCI_RxBuf[5]);
              GetVPC_Contrast(6);
              SetVPC_ContrastDo();
              break;
         case DDC2B_CMD_VCP_RedGain:
              SetVPC_RedGain(ucDDCCI_RxBuf[5]);
              GetVPC_RedGain(6);
              SetVPC_RedGainDo(ucDDCCI_RxBuf[5]);
              break;
         case DDC2B_CMD_VCP_GreenGain:
              SetVPC_GreenGain(ucDDCCI_RxBuf[5]);
              GetVPC_GreenGain(6);
              SetVPC_GreenGainDo(ucDDCCI_RxBuf[5]);
              break;
         case DDC2B_CMD_VCP_BlueGain:
              SetVPC_BlueGain(ucDDCCI_RxBuf[5]);
              GetVPC_BlueGain(6);
              SetVPC_BlueGainDo(ucDDCCI_RxBuf[5]);
              break;
         case DDC2B_CMD_VCP_AutoSetUp:
              CAutoDoAutoConfig();
              // Repeat
              break;
         case DDC2B_CMD_VCP_HPosition:
              SetVPC_HPosition((ucDDCCI_RxBuf[4] << 8) | ucDDCCI_RxBuf[5]);
              GetVPC_HPosition(6);
              SetVPC_HPositionDo();
              break;
         case DDC2B_CMD_VCP_VPosition:
              SetVPC_VPosition((ucDDCCI_RxBuf[4] << 8) | ucDDCCI_RxBuf[5]);
              GetVPC_VPosition(6);
              SetVPC_VPositionDo();
              break;
         case DDC2B_CMD_VCP_ClockPhase:
              SetVPC_Phase(ucDDCCI_RxBuf[5]);
              GetVPC_Phase(6);
              SetVPC_PhaseDo();
              break;
         case DDC2B_CMD_VCP_SelectColorPreset:
              SetVPC_ColorTmp(ucDDCCI_RxBuf[5]);
              //GetVPC_ColorTmp(6);
              SetVPC_ColorTmpDo();
              //SetVPC_PhaseDo();
              break;
         case DDC2B_CMD_VCP_Language:
              //SetVPC_Language(ucDDCCI_RxBuf[5]);
              //GetVPC_Language(6);
              break;
         case DDC2B_CMD_VCP_SAVECOLORTMPSTATE:
              AnwerDDCCISet();
              //SetVPC_SaveColorTmpState();
              break;
         case DDC2B_CMD_VCP_STOP:
              AnwerDDCCISet();
              fDDCCI_Loop = 1;
              break;
         case DDC2B_CMD_VCP_START:
              AnwerDDCCISet();
              fDDCCI_Loop = 0;
              break;
         case DDC2B_CMD_VCP_ContrastAuto:
              AnwerDDCCISet();
              //SetNMVVPC_Auto();
              break;
         case DDC2B_CMD_VCP_OSDHPosition:
              //SetNMVVPC_OSDH();
              //GetNMVVPC_OSDH();
              break;
         case DDC2B_CMD_VCP_OSDVPosition:
              //SetNMVVPC_OSDV();
              //GetNMVVPC_OSDV();
              break;

         default:
              ucDDCCI_TxBuf[2] = 1;                            // RC cmd not support
              ucDDCCI_TxBuf[5] = 1;
              TxCommandReady();
              break;
     }
}

//---------------------------------------------------------------------------------------

void AnwerDDCCISet()
{
     ucDDCCI_TxBuf[6]           = 0x00;
     ucDDCCI_TxBuf[7]           = 1;
     ucDDCCI_TxBuf[8]           = ucDDCCI_RxBuf[4];
     ucDDCCI_TxBuf[9]           = ucDDCCI_RxBuf[5];
     TxCommandReady();
}

//---------------------------------------------------------------------------------------
void GetMonitorType(unsigned char BassAddr)
{
     ucVPC_Page = 0;
     ucDDCCI_TxBuf[BassAddr]               = 0;                                 // MH
     ucDDCCI_TxBuf[BassAddr + 1]           = 3;
     ucDDCCI_TxBuf[BassAddr + 2]           = 0;                                 // SH
     ucDDCCI_TxBuf[BassAddr + 3]           = 3;                                 // TFT
     TxCommandReady();
}
//---------------------------------------------------------------------------------------


*/

/*
void GetNMVVPC_OSDH()          // Range : Data[0] ~ Data[1]
{
     ucVPC_Page = 2;
	 #if(DDCCI_ALL)
     Get_OSD_Margin();	 
     ucDDCCI_TxBuf[6]           = 0x00;
     ucDDCCI_TxBuf[7]           = Data[1] - Data[0];
     ucDDCCI_TxBuf[8]           = 0x00;
     ucDDCCI_TxBuf[9]           = stGUD1.OSD_POSH - Data[0];
	 #endif
     TxCommandReady();
}
//---------------------------------------------------------------------------------------
void GetNMVVPC_OSDV()           // Range : OSD_MIN ~ OSD_MAX
{
       ucVPC_Page = 2;
//     ucDDCCI_TxBuf[6]           = 0x00;
//     ucDDCCI_TxBuf[7]           = OSD_MAX - OSD_MIN;
//     ucDDCCI_TxBuf[8]           = 0x00;
//     ucDDCCI_TxBuf[9]           = stGUD1.OSD_POSV - OSD_MIN;
       TxCommandReady();
}
//---------------------------------------------------------------------------------------
void SetNMVVPC_Auto()
{
     ucVPC_Page = 2;
//     Auto_Balance();
}
//---------------------------------------------------------------------------------------
void SetNMVVPC_OSDH()          // Range : Data[0] ~ Data[1]
{
     ucVPC_Page = 2;
	 #if(DDCCI_ALL)
     Get_OSD_Margin();
     if(ucDDCCI_RxBuf[5] > Data[1] - Data[0])     return;
     stGUD1.OSD_POSH = ucDDCCI_RxBuf[5] + Data[0];
	 #endif
}
//---------------------------------------------------------------------------------------
void SetNMVVPC_OSDV()           // Range : OSD_MIN ~ OSD_MAX
{
     ucVPC_Page = 2;
//     if(ucDDCCI_RxBuf[5] > OSD_MAX - OSD_MIN)     return;
//     ucDDCCI_TxBuf[6]           = 0x00;
//     ucDDCCI_TxBuf[7]           = OSD_MAX - OSD_MIN;
//     ucDDCCI_TxBuf[8]           = 0x00;
//     ucDDCCI_TxBuf[9]           = stGUD1.OSD_POSV - OSD_MIN;
//     stGUD1.OSD_POSV = ucDDCCI_RxBuf[5] + OSD_MIN;
}
//---------------------------------------------------------------------------------------

void SetVPC_SaveColorTmpState()
{
     ucVPC_Page = 2;
     #if(DDCCI_ALL)
	 SET_SAVECOLORTMP(COLORTMP_SAVE);
     SAVE_COLORTMPSATE;
	 #endif
}
//---------------------------------------------------------------------------------------
*/

#endif  //end of DEBUG_ONLY


