//----------------------------------------------------------------------------------------------------
// ID Code      : Video.c No.0001
// Update Note  : 
//
//----------------------------------------------------------------------------------------------------

#define __UART__

#include "Header\Include.h"
#include "Rs232\Rs232.h"
#if(_RS232)
extern   void ProssMCU2DVDkeyHandle(BYTE Keycode);
bit fInUartMode = 0;

bit fUartStart = 0;
bit  fUartRxCmdSuccess = 0;
bit  fUartDebugLoop = 0;

BYTE xdata ucUartRxIndex = 1;
BYTE xdata ucUartRxCount = 0;
BYTE xdata pUartData[9];

BYTE code tEnterDebugMode[] = {0x01,0x02,0x03,0x04};
BYTE code tExitDebugMode[] = {0x04,0x03,0x02,0x01};
bit  SetPanellightState=0;
bit fInitCmdlength = 0;
BYTE code tOSDmenuCMD[] = {0xF0,0x55,0xFF};
BYTE code tOSDPowerCMD[] = {0x00,0x1f,0x01};

//----------------------------------------------------------------------------
void CUartInit(void)
{
	WORD usTemp = 0xFFFF - (UINT32)24000 * 1000 / 38400 / 32;
	// Initialize SBuf to zero
	SBUF = 0x00;

	// Set to 8051 UART mode 1, refer to Page 2-43
	SCON = 0x50;

	// Set the baudrate refer to Timer2, Page 2-37
	T2CON = 0x34;

	//	Timer2's value is 65536 - (crystal / baud * 32)), Page 2-43
	RCAP2L = LOBYTE(usTemp);
	RCAP2H = HIBYTE(usTemp);
	//RCAP2L = 0xd9;		// 19200			
	//RCAP2H = 0xff;		
	//RCAP2L = 0xf9;		// 115200			
	//RCAP2H = 0xff;	
	//RCAP2L = 0xD4;	//0FFh , 0D4h	//19200
	//RCAP2H = 0xFF;	//0FFh , 0D4h	//19200

#if(_ACPOWERON_RS232)
	CTimerActiveTimerEvent(SEC(1), CSwitchToUart);
#endif
}
//----------------------------------------------------------------------------
void CSwitchToUart(void)
{
	BYTE i;
	bit fTest = 0;

       MCU_PIN_SHARE1_FF01 = MCU_PINSHARE_FF01_DEF & (~_BIT0);
	
	//MCU_PIN_SHARE_CTRL00_FF96 |= 0xF8;
	ES = 1; // Enable UART's interrupt
	PS = 1; // Change UART's interrupt to high priority

	fInUartMode = 1;

    DebugPrintf("Swtich to Uart mode.\n",0x00);

    for(i=0;i<10;i++)
    {
//		bLED1 = fTest;
		fTest = ~fTest;
		CTimerDelayXms(20);		
    }
    
}
//----------------------------------------------------------------------------
void CSwitchToI2C(void)
{
	BYTE i;
	bit fTest = 0;
	
    DebugPrintf("Swtich to IIC mode.\n",0x00);
     MCU_PIN_SHARE1_FF01 = MCU_PINSHARE_FF01_DEF | _BIT0;
	//MCU_PIN_SHARE_CTRL00_FF96 &= 0x07;
	ES = 0; // Enable UART's interrupt
	PS = 0; // Change UART's interrupt to high priority	
	fInUartMode = 0;

    for(i=0;i<10;i++)
    {
//		bLED2 = fTest;
		fTest = ~fTest;
		CTimerDelayXms(20);		
    }	
}

//----------------------------------------------------------------------------
void DebugPrintf(const BYTE code* pstr,BYTE value)
{
	BYTE i;
	char *p = pstr;

	for (i =0x00; *p != '\0'; i++)
    {
		if(*p == '\n')
		{
			CUartPutCharToScr('\r');
			CUartPutCharToScr(*p);
       	}
        else if(*p == '%')
		{
			switch(*(p+1))
			{
				case 'd':
					i++;
					p++;
					CUartPutToScr(value,1);
					break;
				case 'x':
					i++;
					p++;
					CUartPutToScr(value,2);
					break;
				case 'c':
					i++;
					p++;
					CUartPutCharToScr(value);
					break;	
				default:
					CUartPutCharToScr(*p);
					break;
			}
        }
		else
		{
			CUartPutCharToScr(*p);
		}
		p++;
    }
}
//----------------------------------------------------------------------------
void CUartPutToScr(const BYTE ch,const BYTE mode)
{
	BYTE NO1[3];
	BYTE i,time;

	if(mode == 1) 
	{	//dec
		NO1[2] = ch / 100;
		NO1[1] = (ch % 100) / 10;
		NO1[0] = (ch % 100) % 10;
		
		if (NO1[2])					time = 3;
		else if (NO1[1])			time = 2;
		else						time = 1;

		for (i = 0; i < time; i++) 
		{
			CUartPutCharToScr(NO1[time - i - 1] + '0');
		}
	}
	else if (mode == 2) 
	{	//hex
		NO1[1] = (ch & 0x0F);
		NO1[0] = ((ch >> 4) & 0x0F);
		for (i = 0; i < 2; i++) 
		{

			if (NO1[i] > 9)
				time = NO1[i] - 10 + 'A';
			else
				time = NO1[i] + '0';	 	// transfer UART
			CUartPutCharToScr(time);
		}
	}

}
//----------------------------------------------------------------------------
void CUartPutCharToScr(BYTE ch)
{
	ES = 0;

	TI = 0;
	SBUF = ch; 			// transfer UART
	while (!TI);		// wait buffer completing.
	
	ES = 1;
}
//----------------------------------------------------------------------------


void CUartHandler(void)
{
	do
	{		
		if (!fUartRxCmdSuccess)
			continue;

		fUartRxCmdSuccess = 0;

		switch (pUartData[0])
		{	
			case UartCMD_DebugModeExit:
				UartCMDDebugModeExit();
				break;
			case UartCMD_DebugModeEnter:
				UartCMDDebugModeEnter();
				break;
			
			case UartCMD_CScalerRead:
				UartCMDScalerRead();
				break;

			case UartCMD_I2CRead:
				break;

			case UartCMD_CScalerWrite:
				UartCMDScalerWrite();
				break;
                     case UartCMD_RS232Control:
				UartCMDRS232Control();
				break;
			case UartCMD_I2CWrite:
				break;

		}

   	}
   	while(fUartDebugLoop);

}
//----------------------------------------------------------------------------
void UartCMDDebugModeExit(void)
{
	BYTE i;
	for(i=0;i<4;i++)
	{
		if(pUartData[i + 1] != tExitDebugMode[i])
			return;
	}

	CUartPutCharToScr(0x11);
	fUartDebugLoop = 0;
}
//----------------------------------------------------------------------------
void UartCMDDebugModeEnter(void)
{
	BYTE i;
	for(i=0;i<4;i++)
	{
		if(pUartData[i + 1] != tEnterDebugMode[i])
			return;
	}

	CUartPutCharToScr(0x10);
	fUartDebugLoop = 1;
}
//----------------------------------------------------------------------------
void UartCMDScalerRead(void)
{
	BYTE i;

	if (!pUartData[3])
		CScalerRead(pUartData[1], pUartData[2], pData, _AUTOINC);
	else
		CScalerRead(pUartData[1], pUartData[2], pData, _NON_AUTOINC);

	CUartPutCharToScr(pUartData[2]);
	for(i=0;i<pUartData[2];i++)
		CUartPutCharToScr(pData[i]);

}
//----------------------------------------------------------------------------
void UartCMDScalerWrite(void)
{
	CScalerSetByte(pUartData[1], pUartData[2]);
	CUartPutCharToScr(0x30);	// willy 050810 for sync RS232
}
//----------------------------------------------------------------------------
void UartCMDRS232Control(void) 
{
	BYTE i;

 if(fInitCmdlength)
 {
	for(i=0;i<3;i++)
	{
		if(pUartData[i + 1] != tOSDmenuCMD[i])
			return;
	}
	/*
      switch (pUartData[4])
		{	
			case UartCMD_MENU:
				
		          if(pUartData[5] != 0x2B)
				  return;
                         else
	               ucKeyMessage = _MENU_KEY_MESSAGE;
					 
                     // DebugPrintf("_MENU_KEY_MESSAGE.\n",0x01);
				break;

			case UartCMD_VOLUMELEFT:
				
			 if(pUartData[5] != 0x68)
				  return;
                         else
	               ucKeyMessage = _LEFT_KEY_MESSAGE;
						 
				break;

			case UartCMD_VOLUMERIGHT:
				
			 if(pUartData[5] != 0x60)
				  return;
                         else
			ucKeyMessage = _RIGHT_KEY_MESSAGE;
						 
				break;		

			case UartCMD_DOWN:
				
			 if(pUartData[5] != 0x27)
				  return;
                         else
	               ucKeyMessage = _DOWN_KEY_MESSAGE;
						 
				break;

			case UartCMD_UP:

			 if(pUartData[5] != 0x6D)
				  return;
                         else
	               ucKeyMessage = _UP_KEY_MESSAGE;
						 
                       //DebugPrintf("_UP_KEY_MESSAGE.\n",0x00);
				break;			

			case UartCMD_MUTE:

			 if(pUartData[5] != 0x20)
				  return;
                         else				  
	               ucKeyMessage = _MUTE_KEY_MESSAGE;
						 
				break;		

			case UartCMD_OK:

			 if(pUartData[5] != 0x64)
				  return;
                         else
	               ucKeyMessage = _ENTER_KEY_MESSAGE;
						 
				break;

			case UartCMD_SOURCE:

			 if(pUartData[5] != 0x3C)
				  return;
                         else
	               ucKeyMessage = _INPUT_KEY_MESSAGE;
						 
				break;

			case UartCMD_EXIT:

			 if(pUartData[5] != 0x23)
				  return;
                         else
	               ucKeyMessage = _EXIT_KEY_MESSAGE;
						 
				break;

			case UartCMD_CHINC:

			 if(pUartData[5] != 0x7F)
				  return;
                         else
	               ucKeyMessage = _IR_CHINC_KEY_MESSAGE;
						 
				break;

			case UartCMD_CHDEC:

			 if(pUartData[5] != 0x71)
				  return;
                         else
	               ucKeyMessage = _IR_CHDEC_KEY_MESSAGE;
						 
				break;

			case UartCMD_VOLINC:

			 if(pUartData[5] != 0x7C)
				  return;
                         else
	               ucKeyMessage = _IR_VOLINC_KEY_MESSAGE;
						 
				break;

			case UartCMD_VOLDEC:

			 if(pUartData[5] != 0x79)
				  return;
                         else
	               ucKeyMessage = _IR_VOLDEC_KEY_MESSAGE;
						 
				break;

			case UartCMD_SLEEP:

			 if(pUartData[5] != 0x3F)
				  return;
                         else
	               ucKeyMessage = IR_SLEEP_KEY_MESSAGE;
						 
				break;
	            case UartCMD_AV:
   			 if(pUartData[5] != 0xCD)
				  return;
                         else
	               ucKeyMessage = _IR_AVTYPE_KEY_MESSAGE;
						 
				break;             

			case UartCMD_VGA:

			 if(pUartData[5] != 0xE7)
				  return;
                         else
	               ucKeyMessage = _IR_VGATYPE_KEY_MESSAGE;
						 
				break;
		 case UartCMD_HDMI:

			 if(pUartData[5] != 0xE9)
				  return;
                         else
	               ucKeyMessage = _IR_HDMITYPE_KEY_MESSAGE;
						 
				break;	

		 case UartCMD_TV:

			 if(pUartData[5] != 0xE5)
				  return;
                         else
	               ucKeyMessage = _IR_TVTYPE_KEY_MESSAGE;
						 
				break;	

		 case UartCMD_DTV:

			 if(pUartData[5] != 0xE6)
				  return;
                         else
	               ucKeyMessage = _IR_DTVTYPE_KEY_MESSAGE;
						 
				break;	
                
			case UartCMD_POWERON:

			 if(pUartData[5] != 0x28)
				  return;
                         else
	               ucKeyMessage = _POWER_KEY_MESSAGE;
						 
				break;
//=================================================
// 下面是数字键
//=================================================

             		case UartCMD_NUM1:

			 if(pUartData[5] != 0x6A)
				  return;
                         else
	               ucKeyMessage = _NUM1_KEY_MESSAGE;
						 
				break;

			case UartCMD_NUM2:

			 if(pUartData[5] != 0x66)
				  return;
                         else
	               ucKeyMessage = _NUM2_KEY_MESSAGE;
						 
				break;

			case UartCMD_NUM3:

			 if(pUartData[5] != 0x62)
				  return;
                         else
	               ucKeyMessage = _NUM3_KEY_MESSAGE;
						 
				break;

			case UartCMD_NUM4:

			 if(pUartData[5] != 0x29)
				  return;
                         else
	               ucKeyMessage = _NUM4_KEY_MESSAGE;
						 
				break;

			case UartCMD_NUM5:

			 if(pUartData[5] != 0x25)
				  return;
                         else
	               ucKeyMessage = _NUM5_KEY_MESSAGE;
						 
				break;

			case UartCMD_NUM6:

			 if(pUartData[5] != 0x21)
				  return;
                         else
	               ucKeyMessage = _NUM6_KEY_MESSAGE;
						 
				break;

			case UartCMD_NUM7:

			 if(pUartData[5] != 0x69)
				  return;
                         else
	               ucKeyMessage = _NUM7_KEY_MESSAGE;
						 
				break;

			case UartCMD_NUM8:

			 if(pUartData[5] != 0x65)
				  return;
                         else
	               ucKeyMessage = _NUM8_KEY_MESSAGE;
						 
				break;

			case UartCMD_NUM9:

			 if(pUartData[5] != 0x61)
				  return;
                         else
	               ucKeyMessage = _NUM9_KEY_MESSAGE;
						 
				break;


			case UartCMD_NUM0:

			 if(pUartData[5] != 0x26)
				  return;
                         else
	               ucKeyMessage = _NUM0_KEY_MESSAGE;
						 
				break;

 
     case UartCMD_USB:

			 if(pUartData[5] != 0xFE)
				  return;
                         else
	               ucKeyMessage = _USB_KEY_MESSAGE;
						 
				break;

     case UartCMD_DVD:

			 if(pUartData[5] != 0xF9)
				  return;
                         else
	               ucKeyMessage = _DVD_KEY_MESSAGE;
						 
				break;



		    
      	}
*/


	    if(pUartData[5] != ~pUartData[4])
	    	{
		       DebugPrintf("if.\n",0x00);

				  return;
	    	}		  
           else
           {

		       DebugPrintf("else.\n",0x00);

	             ProssMCUTXHandle(pUartData[4]);
           }


		
		}
  else
  	{

	 	for(i=0;i<3;i++)
		{
			if(pUartData[i + 1] != tOSDPowerCMD[i])
				return;
		}

	 switch (pUartData[4])
         {
			         case UartCMD_POWERON:
						
			          if(pUartData[5] != 0x20)
					  return;
		                 else
				       {   

					        ucKeyMessage = _POWER_KEY_MESSAGE;
				                //DebugPrintf("_POWER_STATUS_ON_MESSAGE.\n",0x01);

		                 	}
								 
						break;


			         case UartCMD_POWEROFF:
						
			          if(pUartData[5] != 0x21)
					  return;
		                     else

					    ucKeyMessage = _POWER_KEY_MESSAGE ;


					 
					     break;
				
	       }

          

           
             ProssMCUTXHandlePOWER(ucKeyMessage);
	/*	ProssMCU2DVDkeyHandle(ucKeyMessage);	
              CUartPutCharToScr(0xbb);
		CUartPutCharToScr(0x00);
		CUartPutCharToScr(0x1f);
		CUartPutCharToScr(0x01);
	       CUartPutCharToScr(pUartData[4]);
	       CUartPutCharToScr(~pUartData[4]);

*/

			  
      }

	//CUartPutCharToScr(0x30);	

}
#endif


