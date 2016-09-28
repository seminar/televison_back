//----------------------------------------------------------------------------------------------------
// ID Code      : Key.c No.0001
// Update Note  : 
//
//----------------------------------------------------------------------------------------------------

#define __KEY__

#include "Header\Include.h"
#include "Rs232\Rs232.h"
#if(DVD_EN)

void   Delay10us(WORD uctemp)// 0.56ms
{  
	while( uctemp --)
		{
	        Delay3us();
	        Delay3us();
	        Delay5us();
		}
}

void SendByteData(BYTE ucValue)
{
           BYTE cnt;
            for(cnt=0;cnt<8;cnt++)
		   {
		   PNL0=0;
		  Delay10us(49);// 
		  PNL0=1;	   
		  
		if(ucValue&_BIT0)
		Delay10us(140); // "1"  
		else
		Delay10us(61);  //"0"  
		    
		ucValue=ucValue>>1;
		   }

}

void Trs2DVDIrSend(BYTE IRData)
{
//_MCU_PORT6_7_MODE        _MCU_PAD_IS_OUTPUT 
MCU_PORT6_OE_FF04 = MCU_PORT6_OE_FF04 |(1 << 7);
    gmi_CStopIR();

                 PNL0=0;	   
		  Delay10us(781);// 
                PNL0=1;
		  Delay10us(382);// 

		 Trs2DVDIrSendHead();
		SendByteData(IRData);
		//SendByteData(~IRData); 
		   PNL0=0;
			Delay10us(56); 
		   PNL0=1;
			
    gmi_CStartIR(); 
//_MCU_PORT6_7_MODE        _MCU_PAD_IS_INPUT 
MCU_PORT6_OE_FF04 = MCU_PORT6_OE_FF04 &(~_BIT7);


  Delay10us(3124);// 


MCU_PORT6_OE_FF04 = MCU_PORT6_OE_FF04 |(1 << 7);
    gmi_CStopIR();

 
		 Trs2DVDIrSendHead();
		SendByteData(IRData);
		//SendByteData(~IRData); 
		   PNL0=0;
			Delay10us(56); 
		   PNL0=1;
			
            gmi_CStartIR(); 
//_MCU_PORT6_7_MODE        _MCU_PAD_IS_INPUT 
MCU_PORT6_OE_FF04 = MCU_PORT6_OE_FF04 &(~_BIT7);


 Delay10us(3124);// 


MCU_PORT6_OE_FF04 = MCU_PORT6_OE_FF04 |(1 << 7);
    gmi_CStopIR();

 
		 Trs2DVDIrSendHead();
		SendByteData(IRData);
		//SendByteData(~IRData); 
		   PNL0=0;
			Delay10us(56); 
		   PNL0=1;
			
            gmi_CStartIR(); 
//_MCU_PORT6_7_MODE        _MCU_PAD_IS_INPUT 
MCU_PORT6_OE_FF04 = MCU_PORT6_OE_FF04 &(~_BIT7);
		
}
#if 0
void ProssMCU2DVDkeyHandle(BYTE Keycode)
{
   switch(Keycode)
   {
     case KEY_0:
	Trs2DVDIrSend(0x00); // DVD_KEY0
	break;
    /* case KEY_1:
	 Trs2DVDIrSend(0x01); //DVD_KEY1
	break;
     case KEY_2:
	 Trs2DVDIrSend(0x02); // DVD_KEY2
	break;
     case KEY_3:
	 Trs2DVDIrSend(0x03); // DVD_KEY3
	break;
     case KEY_4:
	 Trs2DVDIrSend(0x04); // DVD_KEY4
	break;
     case KEY_5:
	 Trs2DVDIrSend(0x05); // DVD_KEY5
	break;
     case KEY_6:
	 Trs2DVDIrSend(0x06); // DVD_KEY6
	break;
     case KEY_7:
	 Trs2DVDIrSend(0x07); // DVD_KEY7
	break;
     case KEY_8:
	 Trs2DVDIrSend(0x08); // DVD_KEY8
	break;
     case KEY_9:
	 Trs2DVDIrSend(0x09); //DVD_KEY9
	break;

     case KEY_POWER:
      Trs2DVDIrSend(0x1f); //DVD POWER MEMORY DISC CONTENT.
	 break;
    case KEY_DVD_EJECT:
	 Trs2DVDIrSend(0x0a); // Open/Close
	break;
     case KEY_RECALL:
	 Trs2DVDIrSend(0x1a); //Playing Repeat
	break;
     case KEY_MTS:
	 Trs2DVDIrSend(0x34); //L/R Channel switch
	break;
     case KEY_DVD_MENU:
	 Trs2DVDIrSend(0x32); // Root Menu
	break;
     case KEY_TTX_MIX:
	 Trs2DVDIrSend(0x18); //Display Playing Infor.
	break;
     case KEY_PIP:
	 Trs2DVDIrSend(0x19);// Repeat A-B
     case KEY_REPEAT:
	 Trs2DVDIrSend(0x1a);// Repeat A-B
	break;
     case KEY_UP:
	 Trs2DVDIrSend(0x21); //DVD_UP
	break;
     case KEY_DOWN:
	 Trs2DVDIrSend(0x22); // DVD_DOWN
	break;
     case KEY_LEFT:
	 Trs2DVDIrSend(0x23); //DVD_LEFT
	break;
     case KEY_RIGHT:
	 Trs2DVDIrSend(0x24);// DVD_RIGHT
	break;
     case KEY_DVD_SLOW:
	 Trs2DVDIrSend(0x0c);  // RESERVE.
	break;
     case KEY_TTX_LIST:
	 Trs2DVDIrSend(0x35); // USB PORT SELET
	break;
     case KEY_TTX:
	 Trs2DVDIrSend(0x2a); // DVD Play/Pause
	break;
     case KEY_TTX_HOLD:
	 Trs2DVDIrSend(0x12); // DVD Stop
	break;
     case KEY_TTX_CANCEL:
	 Trs2DVDIrSend(0x13); // DVD Sound Language Switch.
	break;
     case KEY_TTX_INDEX:
	 Trs2DVDIrSend(0x31); // DVD Setup
	break;

     case KEY_MENU:
	 Trs2DVDIrSend(0x36); // DVD EXIT Setup Menu
	break;
     case KEY_TTX_SUBTITLE:
	 Trs2DVDIrSend(0x2b); //DVD_SubTitle 
	break;
   case KEY_DVD_SELECT:
	 Trs2DVDIrSend(0x2e); //DVD_SELECT
	break;
     case KEY_TTX_SIZE:
	 Trs2DVDIrSend(0x2f); //Title Menu
	break;
     case KEY_TTX_REVEAL:
	 Trs2DVDIrSend(0x1c); //GOTO ???÷??·?
	break;
     case KEY_TTX_RED:
	 Trs2DVDIrSend(0x16); // Prev Title
	break;
     case KEY_TTX_GREEN:  
	 Trs2DVDIrSend(0x17); // Next Title
	break;
     case KEY_TTX_YELLOW:
	 Trs2DVDIrSend(0x14); // Backward
	break;
     case KEY_TTX_CYAN:
	 Trs2DVDIrSend(0x15); // Forward
	break;
	default:
	break;*/
   }
}
#else 
void ProssMCU2DVDkeyHandle(BYTE Keycode)
{

#if( _UARTTX)
   switch(Keycode)
   {
/*     case _MENU_KEY_MESSAGE:
	Trs2DVDIrSend(0x4e);   //
	break;

     case _RIGHT_KEY_MESSAGE:
	Trs2DVDIrSend(0x05);  //
	break;
	
     case _LEFT_KEY_MESSAGE:
	Trs2DVDIrSend(0x0c); //
	break;
	
     case _UP_KEY_MESSAGE:
	Trs2DVDIrSend(0x17);  //
	break;
	
     case _DOWN_KEY_MESSAGE:
	Trs2DVDIrSend(0x0d); //
	break; 
	
     case _MUTE_KEY_MESSAGE:
	Trs2DVDIrSend(0x14); // 0x1C
	break; 

    case _ENTER_KEY_MESSAGE:
	Trs2DVDIrSend(0x02); //
	break; 

    case _INPUT_KEY_MESSAGE:// 
	Trs2DVDIrSend(0x01); 
	break; 
	
    case _POWER_KEY_MESSAGE:// 
	Trs2DVDIrSend(0x0b); 
	break; 
//============================================
// 下面是数字键
//============================================

     case _NUM1_KEY_MESSAGE:// 
	Trs2DVDIrSend(0x42); 
	break;
	
     case _NUM2_KEY_MESSAGE:// 
	Trs2DVDIrSend(0x43); 
	break;

     case _NUM3_KEY_MESSAGE:// 
	Trs2DVDIrSend(0x0f); 
	break;

     case _NUM4_KEY_MESSAGE:// 
	Trs2DVDIrSend(0x1e); 
	break;

     case _NUM5_KEY_MESSAGE:// 
	Trs2DVDIrSend(0x1d); 
	break;

     case _NUM6_KEY_MESSAGE:// 
	Trs2DVDIrSend(0x1c); 
	break;

     case _NUM7_KEY_MESSAGE:// 
	Trs2DVDIrSend(0x18); 
	break;

     case _NUM8_KEY_MESSAGE:// 
	Trs2DVDIrSend(0x45); 
	break;

   /  case _NUM9_KEY_MESSAGE:// 
	Trs2DVDIrSend(0x4c); 
	break;

     case _NUM0_KEY_MESSAGE:// 
	Trs2DVDIrSend(0x56); 
	break;
*/
	
     	default:
	break;
   }
     
#else
//***********************************************************************

//=====================================================
//上面发的值 转化为ir 码值注意发送方不能编译下面的
// 不然会形成互发码值
//=======================	==============================
   switch(Keycode)
   {
/*    case IR_FUNC_MENU:
	Trs2DVDIrSend(0x8D);   //
	break;

    case IR_FUNC_RIGHT:
	Trs2DVDIrSend(0x5F);  //
	break;
	
     case IR_FUNC_LEFT:
	Trs2DVDIrSend(0xCF); 
	break;
	
     case IR_FUNC_UP:
	Trs2DVDIrSend(0x17);  //
	break;
	
     case IR_FUNC_DOWN:
	Trs2DVDIrSend(0x4F); 
	break; 

     case IR_FUNC_MUTE:
	Trs2DVDIrSend(0xD7);  
	break;

     case IR_FUNC_OK:
	Trs2DVDIrSend(0xBF); 
	break;

    case IR_FUNC_SOURCE:
	Trs2DVDIrSend(0x7f);  
	break;
	
     case IR_FUNC_POWER:
	Trs2DVDIrSend(0x2F);  //
	break;
//===============================	
// 下面是数字键
//===============================

     case IR_FUNC_NUM1:
	Trs2DVDIrSend(0xBD);  //
	break;
	
     case IR_FUNC_NUM2:
	Trs2DVDIrSend(0x3D);  //
	break;

     case IR_FUNC_NUM3:
	Trs2DVDIrSend(0x0F);  //
	break;

     case IR_FUNC_NUM4:
	Trs2DVDIrSend(0x87);  //
	break;

     case IR_FUNC_NUM5:
	Trs2DVDIrSend(0x47);  //
	break;

     case IR_FUNC_NUM6:
	Trs2DVDIrSend(0xC7);  //
	break;

     case IR_FUNC_NUM7:
	Trs2DVDIrSend(0xE7);  //
	break;

     case IR_FUNC_NUM8:
	Trs2DVDIrSend(0x5D);  //
	break;

     case IR_FUNC_NUM9:
	Trs2DVDIrSend(0xCD);  //
	break;

     case IR_FUNC_NUM0:
	Trs2DVDIrSend(0x95);  //
	break;
*/
     	default:
	break;

   }
   #endif
}
#endif
#endif

  #if(_FACTORY_MENU_EN)
//--------------------------------------------------
// Description  : get BurnIn state and process the key
// Input Value  : None
// Output Value : false or true
//--------------------------------------------------

bit getFACState(void)
{
      // BYTE uctemp=0xff;
	static BYTE ucFacKeyInfo=_BIT0;
         switch(ucFacKeyInfo)    
         	{
         	/*
           case  _BIT0: if(ucDetectIR_Cmd==IR_FUNC_NUM1) ucFacKeyInfo=_BIT1 ; else ucFacKeyInfo=_BIT0 ; break;			
           case  _BIT1: if(ucDetectIR_Cmd==IR_FUNC_NUM2) ucFacKeyInfo=_BIT2 ; else  ucFacKeyInfo=_BIT0 ; break;			
           case  _BIT2: if(ucDetectIR_Cmd==IR_FUNC_NUM3) ucFacKeyInfo=_BIT3 ; else  ucFacKeyInfo=_BIT0 ; break;			
           case  _BIT3: if(ucDetectIR_Cmd==IR_FUNC_NUM4) ucFacKeyInfo=_BIT4 ; else  ucFacKeyInfo=_BIT0 ; break;			
*/
         }
		 
         switch(ucDetectIR_Cmd)    
         	{
       /*  	//caimingan
           case  IR_FUNC_NUM0: // uctemp=0;ucDetectIR_Cmd=0; break;
           case  IR_FUNC_NUM1: //uctemp=1;ucDetectIR_Cmd=0; break;
           case  IR_FUNC_NUM2:// uctemp=2;ucDetectIR_Cmd=0; break;
           case  IR_FUNC_NUM3:// uctemp=3;ucDetectIR_Cmd=0; break;
           case  IR_FUNC_NUM4: //uctemp=4;ucDetectIR_Cmd=0; break;
           case  IR_FUNC_NUM5: //uctemp=5;ucDetectIR_Cmd=0; break;
           case  IR_FUNC_NUM6: //uctemp=6;ucDetectIR_Cmd=0; break;
           case  IR_FUNC_NUM7: //uctemp=7;ucDetectIR_Cmd=0; break;
           case  IR_FUNC_NUM8: //uctemp=8;ucDetectIR_Cmd=0; break;
           case  IR_FUNC_NUM9: //uctemp=9;ucDetectIR_Cmd=0; break;
           */
		   ucDetectIR_Cmd=0;break;
         	}
/*		 
#if(_RS232 == _ON)
   //  debug info
   if(uctemp!=0xff)
   	{
		CUartPrintf("KeyMessage:",uctemp);
		CUartPrintf("ucFacKeyInfo:",ucFacKeyInfo);
   	}
#endif	
*/
	if(ucFacKeyInfo == _BIT4)
		{ucFacKeyInfo=_BIT0;
	        return _TRUE;
		}
	
	return _FALSE;
}    
#endif
//--------------------------------------------------
// Description  : Key scan process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CKeyHandler(void)
{
    // Clear the key message
    ucKeyMessage = _NONE_KEY_MESSAGE;
    
    if(CKeyScanReady())// || _ACTIVE_STATE != ucCurrState)
    {
        // Store previous key state
        ucKeyStatePrev = ucKeyStateCurr;
        
        // Get current key state
        ucKeyStateCurr = CKeyScan();


        // Power key process, return if power key is pressed
        if(CKeyPowerKeyProc())
            return;
        
        // Convert key state to key message, store in (ucKeyNotify)
        CKeyMessageProc();
    }
    
#if(_ISPACK && _ISPACK_TYPE == _ISPACK_MCU)
    GetVirtualKey();
#endif
}

//--------------------------------------------------
// Description  : Check power key process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CKeyCheckPowerKey(void)
{
    // Store previous key state
    ucKeyStatePrev = ucKeyStateCurr;
    
    // Get current key state
    ucKeyStateCurr = CKeyScan();
    
    // Power key process
    CKeyPowerKeyProc();
}

//--------------------------------------------------
// Description  : Initial key status
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CKeyInitial(void)
{
    CLR_KEYSCANREADY();
    CLR_KEYSCANSTART();
}

//--------------------------------------------------
// Description  : Key scan ready process. We wait 0.02 sec in order to keep the keypad debounce
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit CKeyScanReady(void)
{
    if(GET_KEYSCANSTART() && GET_KEYSCANREADY())
    {
        return _TRUE;
    }
    else if(!GET_KEYSCANSTART())
    {
        // Wait 0.02 sec in order to keep the keypad debounce
        SET_KEYSCANSTART();
        CTimerReactiveTimerEvent(SEC(0.02), CKeyScanReadyTimerEvent);
        
        return _FALSE;
    }
    else
    {
        return _FALSE;
    }  
}

//--------------------------------------------------
// Description  : Key scan ready timer event
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CKeyScanReadyTimerEvent(void)
{
    SET_KEYSCANREADY();
}

//--------------------------------------------------
// Description  : Key repeat enable timer event
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CKeyRepeatEnableTimerEvent(void)
{
    SET_KEYREPEATSTART();
}

//--------------------------------------------------
// Description  : Key message translation
// Input Value  : ucKeyMask     --> Key mask
//                ucKeyMsg      --> Key message
// Output Value : None
//--------------------------------------------------
void CKeyMessageConvert(BYTE ucKeyMask, BYTE ucKeyMsg)
{
    if((ucKeyStatePrev ^ ucKeyStateCurr) == ucKeyMask)
    {
        ucKeyMessage = ucKeyMsg;
    }
    else
    { 
        if(GET_KEYREPEATENABLE())
        {
            if(GET_KEYREPEATSTART())
            {
                ucKeyMessage = ucKeyMsg;
            }
            else
            {
                CTimerActiveTimerEvent(SEC(_KEY_REPEAT_START_TIME),CKeyRepeatEnableTimerEvent);
            }
        }
    }
}

//--------------------------------------------------
// Description  : Power key process
// Input Value  : None
// Output Value : Return _TRUE if power key is pressed
//--------------------------------------------------
bit CKeyPowerKeyProc(void)
{
    if(ucKeyStateCurr == _POWER_KEY_MASK)
    {
        if((ucKeyStatePrev ^ ucKeyStateCurr) == _POWER_KEY_MASK)
        {
            CTimerDelayXms(25);
            ucKeyStateCurr = CKeyScan();
            
            if((ucKeyStatePrev ^ ucKeyStateCurr) == _POWER_KEY_MASK)
            {
                CKeyPowerKeyMix();
                SET_POWERSWITCH();
                return _TRUE;
            }
        }
    }
    
    return _FALSE;
}
                                 
//--------------------------------------------------
// Description  : Get key status
// Input Value  : None
// Output Value : Return Key status
//--------------------------------------------------
BYTE CKeyScan(void)
{
    BYTE ucKeyState = _NONE_KEY_MASK; 
   
#if(_KEY_TYPE == _KEY_ADC)  // MTV512 & STK6021 ADC Key
    BYTE ucADC0 = CGetADCData(ADC_ID);    //Get ADC0 Value
    BYTE ucADC1 = CGetADCData(ADC_ID);    //Get ADC1 Value

    if(_ABS(ucADC0,ucADC1) < 3)
    {
        if(_ABS(ucADC0,bNONE_KEY) < 3)          ucKeyState = _NONE_KEY_MASK;  // No key in
        else if(_ABS(ucADC0,bRIGHT_KEY) < 3)    ucKeyState = _RIGHT_KEY_MASK;
        else if(_ABS(ucADC0,bLEFT_KEY) < 3)     ucKeyState = _LEFT_KEY_MASK;
        else if(_ABS(ucADC0,bEXIT_KEY) < 3)     ucKeyState = _EXIT_KEY_MASK;
        else if(_ABS(ucADC0,bMENU_KEY) < 3)     ucKeyState = _MENU_KEY_MASK;
        else if(_ABS(ucADC0,bPOWER_KEY) < 3)    ucKeyState = _POWER_KEY_MASK;
    }   
#else // KEY_NORMAL
    if(!bPOWER_KEY)        ucKeyState    = ucKeyState | _POWER_KEY_MASK;
    if(!bRIGHT_KEY)        ucKeyState    = ucKeyState | _RIGHT_KEY_MASK;
    if(!bLEFT_KEY)         ucKeyState    = ucKeyState | _LEFT_KEY_MASK;
    if(!bEXIT_KEY)         ucKeyState    = ucKeyState | _EXIT_KEY_MASK;
    if(!bMENU_KEY)         ucKeyState    = ucKeyState | _MENU_KEY_MASK;
    if(!bCH_DEC_KEY)         ucKeyState    = ucKeyState | _CH_DEC_KEY_MASK;
    if(!bCH_INC_KEY)           ucKeyState    = ucKeyState | _CH_INC_KEY_MASK;
#endif

    if(ucKeyState != _NONE_KEY_MASK)
    	{
       CKeyInitial();
	//CUartPrintf("ucKeyState:",ucKeyState);
    DebugPrintf("ucKeyState=========\n",ucKeyState);
    	}
    
    return ucKeyState;
}
//--------------------------------------------------
// Description  : We can add some settings here while combo key with power key
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CKeyPowerKeyMix(void)
{
 /*   switch(ucKeyStateCurr)
    {
    case _POWER_RIGHT_KEY_MASK:
        ucOsdEventMsg = _ENTER_FACTORY_MODE_MSG;
        break;
        
    case _POWER_MENU_KEY_MASK:
        break;
        
    case _POWER_LEFT_RIGHT_KEY_MASK:
        break;
    } */
}

//--------------------------------------------------
// Description  : Convert keypad status into key message, stores in ucKeyNotify
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void CKeyMessageProc(void)
{          
//------------------------------------------------------------------------------
BYTE value,getvalue;


//-------------------------------------------------------------------------------
		switch(ucKeyStateCurr)
    {
    /*
    case _MENU_KEY_MASK:
        CKeyMessageConvert(_MENU_KEY_MASK, _MENU_KEY_MESSAGE);        
        break;
        
    case _RIGHT_KEY_MASK:
        CKeyMessageConvert(_RIGHT_KEY_MASK, _RIGHT_KEY_MESSAGE);
        break;
        
    case _LEFT_KEY_MASK:
        CKeyMessageConvert(_LEFT_KEY_MASK, _LEFT_KEY_MESSAGE);
        break;
        
    case _EXIT_KEY_MASK:
        CKeyMessageConvert(_EXIT_KEY_MASK, _EXIT_KEY_MESSAGE);
*/
#if(_OSD_TYPE ==  _OSD007)
#if(_MENU_FUNC == _MENU_EXIT_ITEM)
        if (ucKeyMessage == _EXIT_KEY_MESSAGE)
        {
           switch(ucOsdState)
           {
               case _MENU_NONE:
#if(_VIDEO_TV_SUPPORT)
               case MENU_SHOW_MESSAGE_SATAE:
#endif

               case ITEM_SHORTCUT_INPUTCH_NUM:
               case MENU_VOLUME_SP:
               case MENU_SHOW_MUTE_STATE:
               case MENU_SHOW_MSG_STATE:
                   break;

               default:
                   ucKeyMessage = _IR_MENU_KEY_MESSAGE;
                   break;
           }
        }
#endif
#endif  // end #if(_OSD_TYPE ==  _OSD003)
        break;

#if(_KEY_TYPE_OSD007==_6KEY_SUPPORT)
    case _CH_INC_KEY_MASK:
        CKeyMessageConvert(_CH_INC_KEY_MASK, _IR_CHINC_KEY_MESSAGE);
        break;
    case _CH_DEC_KEY_MASK:
        CKeyMessageConvert(_CH_DEC_KEY_MASK, _IR_CHDEC_KEY_MESSAGE);
        break;
#endif

#if(_KEY_TYPE_OSD007==_7KEY_SUPPORT)
    case _CH_INC_KEY_MASK:
        CKeyMessageConvert(_CH_INC_KEY_MASK, _IR_DOWN_KEY_MESSAGE);
        break;
    case _CH_DEC_KEY_MASK:
        CKeyMessageConvert(_CH_DEC_KEY_MASK, _IR_UP_KEY_MESSAGE);
        break;
#endif
    default:
#if(_IR_ENABLE)        
#if(_REMOTE_CONTROLLER != IR_DVD)
 #if(_FACTORY_MENU_EN)
		// get burn in state if true return
	if((ucDetectIR_Cmd!=0)&&(GET_FAC_STATE()==0)&&(MENU_SUB_RESET == ucOsdState|| ucCurrState==_SLEEP_STATE|| ucCurrState==_NOSIGNAL_STATE))	
		{
			if(getFACState())
			{
			if(ucCurrState==_PWOFF_STATE)
			SET_POWERSWITCH();
  		       SET_FAC_STATE(1);
			ucOsdEventMsg= _FAC_FOR_IN;
			return;
			}
		}
#endif	
 #if _UARTIR

//-------------------------------------------------------------------------------
 /*     if(ucDetectIR_Cmd!=0)
     {
          // temp=0x01;
			getvalue=0x00;		 
			value=ucDetectIR_Cmd;
			// CUartPutCharToScr(value);

			for(i=0;i<8;i++)
         	{
          	// CUartPutCharToScr(~value);

                if(_BIT0&value)
                 {
                       getvalue++;
                	}	
					getvalue=getvalue<<1;
					CUartPutCharToScr(getvalue);
					value=value>>1;
					CUartPutCharToScr	(value);		 
         	}
				 getvalue=~getvalue;

            // CUartPutCharToScr(getvalue);

				Trs2DVDIrSend(getvalue);   //




						 
     	}
*/

   if(ucDetectIR_Cmd!=0)
   	{
            value=ucDetectIR_Cmd;
            getvalue=0x00;
            if(_BIT0&value)
             	{
                 getvalue=getvalue+128;
				}
            if(_BIT1&value)
             	{
                 getvalue=getvalue+64;
				}
            if(_BIT2&value)
             	{
                 getvalue=getvalue+32;
				}
			 if(_BIT3&value)
             	{
                 getvalue=getvalue+16;
				}
			if(_BIT4&value)
             	{
                 getvalue=getvalue+8;
				}
			 if(_BIT5&value)
             	{
                 getvalue=getvalue+4;
				}
			if(_BIT6&value)
             	{
                 getvalue=getvalue+2;
				}
			if(_BIT7&value)
             	{
                 getvalue=getvalue+1;
				}
              getvalue=~getvalue;
             Trs2DVDIrSend(getvalue);


	 }




 //------------------------------------------------------------------------------  

 // ProssMCUIRHandle(ucDetectIR_Cmd);
/*       if(ucDetectIR_Cmd!=0)    
	        {
       
                    //CPowerPanelOff();
			ProssMCU2DVDkeyHandle(ucDetectIR_Cmd);// 遥控码发送
	           //  DebugPrintf("_MENU_KEY_MESSAGE.\n",0x01);
	              CUartPutCharToScr(0xA0);
			CUartPutCharToScr(0x55);
			CUartPutCharToScr(0xF0);
			CUartPutCharToScr(0xFF);
		      CUartPutCharToScr(uchh);
			  uchh=0;
		      CUartPutCharToScr(ucll); 
			  ucll=0;
		      CUartPutCharToScr(ucDetectIR_Cmd);
		      CUartPutCharToScr(~ucDetectIR_Cmd);  
	      	 }

         if((ucDetectIR_Cmd==0)&&(uchh==0x7f))
         	{

			ProssMCU2DVDkeyHandle(ucDetectIR_Cmd);// 遥控码发送
	           //  DebugPrintf("_MENU_KEY_MESSAGE.\n",0x01);
	              CUartPutCharToScr(0xA0);
			CUartPutCharToScr(0x55);
			CUartPutCharToScr(0xF0);
			CUartPutCharToScr(0xFF);;
		      CUartPutCharToScr(uchh);
			  uchh=0;
		      CUartPutCharToScr(ucll); 
			  ucll=0;
		      CUartPutCharToScr(ucDetectIR_Cmd);
		      CUartPutCharToScr(~ucDetectIR_Cmd);  
	      	 }

			
         	
		 





  /*    switch(ucDetectIR_Cmd)
        {
      case IR_FUNC_MENU: 
	  	CUartPutCharToScr(IR_FUNC_MENU);
              break;
                         
      case IR_FUNC_LEFT: 
	  	CUartPutCharToScr(IR_FUNC_LEFT);
              break;   

      case IR_FUNC_RIGHT: 
	  	CUartPutCharToScr(IR_FUNC_RIGHT);
              break;     

      case IR_FUNC_UP: 
	  	CUartPutCharToScr(IR_FUNC_UP);
              break;

       case IR_FUNC_DOWN: 
	  	CUartPutCharToScr(IR_FUNC_DOWN);
              break;

         }

*/
                        
    #endif

        switch(ucDetectIR_Cmd)
        {
        // Stand key
//-----------------------------------------------------------------------------------------
#if (_DISIRTRIS)


        
#if(_OSD_TYPE ==  _OSD007)
#if(_MENU_FUNC == _MENU_EXIT_ITEM)
        case IR_FUNC_MENU:  
	  if(GET_FAC_STATE())
			{
			SET_FAC_STATE(0);
			ucDetectIR_Cmd=0;
			if(GET_BURNIN_STATE()==BURNIN_OFF)
				{
			       SET_NOSIGNAL_INFO(0);
				SET_OSD_READYFORDISPLAY();
				}
                       COsdFxDisableOsd();
			 }		
	else  	
			ucKeyMessage = _IR_MENU_KEY_MESSAGE;      break;
#else
        case IR_FUNC_MENU:      ucKeyMessage = _MENU_KEY_MESSAGE;         break;
#endif
#else
        case IR_FUNC_MENU:      ucKeyMessage = _MENU_KEY_MESSAGE;         break;
#endif // end #if(_OSD_TYPE ==  _OSD007)
        case IR_FUNC_SOURCE:    ucKeyMessage = _EXIT_KEY_MESSAGE;         break;
         case IR_FUNC_OK:    ucKeyMessage = _IR_OK_KEY_MESSAGE;         break;
         case IR_FUNC_EXIT:    ucKeyMessage = _IR_EXIT_KEY_MESSAGE;         break;
        case IR_FUNC_TV:    ucKeyMessage = _IR_VGATYPE_KEY_MESSAGE;         break;
         case IR_FUNC_AV:    ucKeyMessage = _IR_AVTYPE_KEY_MESSAGE;         break;
         case IR_FUNC_SV:    ucKeyMessage = _IR_SVTYPE_KEY_MESSAGE;         break;
         case IR_FUNC_VGA:    ucKeyMessage = _IR_SCARTTYPE_KEY_MESSAGE;         break;
         case IR_FUNC_DVD:    ucKeyMessage = _IR_TVTYPE_KEY_MESSAGE;         break;
         case IR_FUNC_HDMI:    ucKeyMessage = _IR_HDMITYPE_KEY_MESSAGE;         break;
         case IR_FUNC_DTV:    ucKeyMessage = _IR_DTVTYPE_KEY_MESSAGE;         break;

#if(_USE_UD_LR_KEY_MSG)
        case IR_FUNC_LEFT:      ucKeyMessage = _IR_LEFT_KEY_MESSAGE;      break;
        case IR_FUNC_RIGHT:     ucKeyMessage = _IR_RIGHT_KEY_MESSAGE;     break;
        case IR_FUNC_UP:        ucKeyMessage = _IR_UP_KEY_MESSAGE;        break;
        case IR_FUNC_DOWN:      ucKeyMessage = _IR_DOWN_KEY_MESSAGE;      break;
#else
        case IR_FUNC_LEFT:      
#if(_VIDEO_TV_SUPPORT)
            if (ucOsdState == _MENU_NONE ||  ucOsdState == MENU_SHOW_MESSAGE_SATAE)
                ucKeyMessage = _IR_VOLDEC_KEY_MESSAGE;         
            else                      
#endif                               
                ucKeyMessage = _LEFT_KEY_MESSAGE;
            break;

        case IR_FUNC_RIGHT:     
#if(_VIDEO_TV_SUPPORT)
            if (ucOsdState == _MENU_NONE ||  ucOsdState == MENU_SHOW_MESSAGE_SATAE)
                ucKeyMessage = _IR_VOLDEC_KEY_MESSAGE;         
            else
#endif
                ucKeyMessage = _RIGHT_KEY_MESSAGE;
            break;
#endif
     
        // Other key
        case IR_FUNC_POWER:
            CKeyPowerKeyMix();
            SET_POWERSWITCH();
            break;

//        case IR_FUNC_UP:         ucKeyMessage = _IR_UP_KEY_MESSAGE;       break;
  //      case IR_FUNC_DOWN:       ucKeyMessage = _IR_DOWN_KEY_MESSAGE;     break;
#if(_REMOTE_CONTROLLER == IR_CHUNGHOP_RMH02)
          case IR_FUNC_VOLINC:     ucKeyMessage = _IR_VOLINC_KEY_MESSAGE;   break;
          case IR_FUNC_VOLDEC:     ucKeyMessage = _IR_VOLDEC_KEY_MESSAGE;   break;
#endif
#if(!_USE_UD_LR_KEY_MSG || _REMOTE_CONTROLLER == IR_CHUNGHOP_RMH02)
        case IR_FUNC_CHINC:      ucKeyMessage = _IR_CHINC_KEY_MESSAGE;    break;
        case IR_FUNC_CHDEC:      ucKeyMessage = _IR_CHDEC_KEY_MESSAGE;    break;
#endif
        case IR_FUNC_RETURN:     ucKeyMessage = _IR_RETURN_KEY_MESSAGE;   break;
        case IR_FUNC_TV_SYSTEM:  ucKeyMessage = _IR_TVTYPE_KEY_MESSAGE;   break;
      //  case IR_FUNC_SOUND:      ucKeyMessage = _IR_SOUND_KEY_MESSAGE;    break;
        case IR_FUNC_SHOW:       ucKeyMessage = _IR_DISPLAY_KEY_MESSAGE;  break;
        case IR_FUNC_MUTE:       ucKeyMessage = _IR_MUTE_KEY_MESSAGE;     break;
       case IR_FUNC_INPUTCH:    ucKeyMessage = _IR_INPUTCH_KEY_MESSAGE;  break;
        case IR_FUNC_IMAGE:      ucKeyMessage = _IR_IMAGE_KEY_MESSAGE;    break;
    
        case IR_FUNC_NUM0:       ucKeyMessage = _IR_NUM0_KEY_MESSAGE;     break;
        case IR_FUNC_NUM1:       ucKeyMessage = _IR_NUM1_KEY_MESSAGE;     break;
        case IR_FUNC_NUM2:       ucKeyMessage = _IR_NUM2_KEY_MESSAGE;     break;
        case IR_FUNC_NUM3:       ucKeyMessage = _IR_NUM3_KEY_MESSAGE;     break;
        case IR_FUNC_NUM4:       ucKeyMessage = _IR_NUM4_KEY_MESSAGE;     break;
        case IR_FUNC_NUM5:       ucKeyMessage = _IR_NUM5_KEY_MESSAGE;     break;
        case IR_FUNC_NUM6:       ucKeyMessage = _IR_NUM6_KEY_MESSAGE;     break;
        case IR_FUNC_NUM7:       ucKeyMessage = _IR_NUM7_KEY_MESSAGE;     break;
        case IR_FUNC_NUM8:       ucKeyMessage = _IR_NUM8_KEY_MESSAGE;     break;
        case IR_FUNC_NUM9:       ucKeyMessage = _IR_NUM9_KEY_MESSAGE;     break;

        
#endif
//-----------------------------------------------------------------------------------------

        default:                 ucKeyMessage = _NONE_KEY_MESSAGE;        break;
        }

#elif(_REMOTE_CONTROLLER == IR_DVD)  //xdl  20080408

 #if(_FACTORY_MENU_EN)
		// get burn in state if true return
	if((ucDetectIR_Cmd!=0)&&(GET_FAC_STATE()==0)&&(MENU_SUB_RESET == ucOsdState|| ucCurrState==_SLEEP_STATE|| ucCurrState==_NOSIGNAL_STATE))	
		{
			if(getFACState())
			{
			if(ucCurrState==_PWOFF_STATE)
			SET_POWERSWITCH();
			COsdDispOsdTimerEvent();
  		       SET_FAC_STATE(1);
			ucOsdEventMsg= _FAC_FOR_IN;
			return;
			}
		}
#endif	

        switch(ucDetectIR_Cmd)
        {
        // Stand key
#if(_OSD_TYPE ==  _OSD007)

#if(_MENU_FUNC == _MENU_EXIT_ITEM)
        case IR_FUNC_MENU:  
	  if(GET_FAC_STATE())
			{
			SET_FAC_STATE(0);
			ucDetectIR_Cmd=0;
			if(GET_BURNIN_STATE()==BURNIN_OFF)
				{
			       SET_NOSIGNAL_INFO(0);
				SET_OSD_READYFORDISPLAY();
				}
			 }		
	else  	
			ucKeyMessage = _IR_MENU_KEY_MESSAGE;      break;
#else
        case IR_FUNC_MENU:      ucKeyMessage = _MENU_KEY_MESSAGE;         break;
#endif

#else
        case IR_FUNC_MENU:      ucKeyMessage = _MENU_KEY_MESSAGE;         break;
#endif // end #if(_OSD_TYPE ==  _OSD007)
       case IR_FUNC_SOURCE:    ucKeyMessage = _EXIT_KEY_MESSAGE;         break;
      //  case IR_FUNC_SOURCE:    ucKeyMessage = _SOURCE_KEY_MESSAGE;         break;

#if(_USE_UD_LR_KEY_MSG)
        case IR_FUNC_LEFT:      ucKeyMessage = _IR_LEFT_KEY_MESSAGE;      break;
        case IR_FUNC_RIGHT:     ucKeyMessage = _IR_RIGHT_KEY_MESSAGE;     break;
        case IR_FUNC_UP:        ucKeyMessage = _IR_UP_KEY_MESSAGE;        break;
        case IR_FUNC_DOWN:      ucKeyMessage = _IR_DOWN_KEY_MESSAGE;      break;
#else
        case IR_FUNC_LEFT:      
#if(_VIDEO_TV_SUPPORT)
            if (ucOsdState == _MENU_NONE ||  ucOsdState == MENU_SHOW_MESSAGE_SATAE)
                ucKeyMessage = _IR_VOLDEC_KEY_MESSAGE;         
            else                      
#endif                               
                ucKeyMessage = _LEFT_KEY_MESSAGE;
            break;

        case IR_FUNC_RIGHT:     
#if(_VIDEO_TV_SUPPORT)
            if (ucOsdState == _MENU_NONE ||  ucOsdState == MENU_SHOW_MESSAGE_SATAE)
                ucKeyMessage = _IR_VOLDEC_KEY_MESSAGE;         
            else
#endif
                ucKeyMessage = _RIGHT_KEY_MESSAGE;
            break;
#endif
     
        // Other key
        case IR_FUNC_POWER:
            CKeyPowerKeyMix();
            SET_POWERSWITCH();
            break;
#if(DVD_EN)
//        case IR_FUNC_UP:         ucKeyMessage = _IR_UP_KEY_MESSAGE;       break;
  //      case IR_FUNC_DOWN:       ucKeyMessage = _IR_DOWN_KEY_MESSAGE;     break;
        case IR_FUNC_RETURN:     ucKeyMessage = _IR_RETURN_KEY_MESSAGE;   break;
 //       case IR_FUNC_TV_SYSTEM:  ucKeyMessage = _IR_TVTYPE_KEY_MESSAGE;   break;
         case IR_FUNC_SHOW:       ucKeyMessage = _IR_DISPLAY_KEY_MESSAGE;     Keycode= KEY_TTX_MIX ; break;
        case IR_FUNC_MUTE:       ucKeyMessage = _IR_MUTE_KEY_MESSAGE;     break;
        case IR_FUNC_INPUTCH:    ucKeyMessage = _IR_INPUTCH_KEY_MESSAGE;  break;
        case IR_FUNC_IMAGE:      ucKeyMessage = _IR_IMAGE_KEY_MESSAGE;    break;
 //       case IR_FUNC_SOUND:      Keycode= KEY_9;    break;
 //       case IR_FUNC_OK:         Keycode= KEY_9;       break;
    
        case IR_FUNC_NUM0:       ucKeyMessage = _IR_NUM0_KEY_MESSAGE;  Keycode= KEY_0;   break;
        case IR_FUNC_NUM1:       ucKeyMessage = _IR_NUM1_KEY_MESSAGE;  Keycode= KEY_1;   break;
        case IR_FUNC_NUM2:       ucKeyMessage = _IR_NUM2_KEY_MESSAGE;  Keycode= KEY_2;   break;
        case IR_FUNC_NUM3:       ucKeyMessage = _IR_NUM3_KEY_MESSAGE;  Keycode= KEY_3;   break;
        case IR_FUNC_NUM4:       ucKeyMessage = _IR_NUM4_KEY_MESSAGE;  Keycode= KEY_4;   break;
        case IR_FUNC_NUM5:       ucKeyMessage = _IR_NUM5_KEY_MESSAGE;  Keycode= KEY_5;   break;
        case IR_FUNC_NUM6:       ucKeyMessage = _IR_NUM6_KEY_MESSAGE;  Keycode= KEY_6;   break;
        case IR_FUNC_NUM7:       ucKeyMessage = _IR_NUM7_KEY_MESSAGE;  Keycode= KEY_7;   break;
        case IR_FUNC_NUM8:       ucKeyMessage = _IR_NUM8_KEY_MESSAGE;  Keycode= KEY_8;   break;
        case IR_FUNC_NUM9:       ucKeyMessage = _IR_NUM9_KEY_MESSAGE; Keycode= KEY_9;   break;
        case IR_DVD_KEY_DVD_EJECT   :              Keycode= KEY_DVD_EJECT ;        break;
        case IR_DVD_KEY_RECALL         :               Keycode= KEY_RECALL ;               break;
        case IR_DVD_KEY_MTS               :               Keycode= KEY_MTS ;                  break;
        case IR_DVD_KEY_DVD_MENU    :               Keycode= KEY_DVD_MENU ;        break;
             
        case IR_DVD_KEY_PIP              :               Keycode= KEY_PIP;                        break;
        case IR_DVD_KEY_UP               :               Keycode= KEY_UP  ;                       break;
        case IR_DVD_KEY_DOWN          :               Keycode= KEY_DOWN ;                  break;
        case IR_DVD_KEY_LEFT            :               Keycode= KEY_LEFT ;                       break;
        case IR_DVD_KEY_RIGHT          :               Keycode= KEY_RIGHT;                     break;
        case IR_DVD_KEY_DVD_SLOW   :               Keycode= KEY_DVD_SLOW;              break;
        case IR_DVD_KEY_TTX_LIST      :               Keycode= KEY_TTX_LIST  ;                break;
        case IR_DVD_KEY_TTX              :               Keycode= KEY_TTX;                             break;
        case IR_DVD_KEY_TTX_HOLD      :               Keycode= KEY_TTX_HOLD ;                break;
        case IR_DVD_KEY_TTX_CANCEL    :               Keycode= KEY_TTX_CANCEL;        break;
        case IR_DVD_KEY_TTX_INDEX        :               Keycode= KEY_TTX_INDEX ;        break;
        case IR_DVD_KEY_MENU                :               Keycode= KEY_MENU;                       break;
        case IR_DVD_KEY_TTX_SUBTITLE    :               Keycode= KEY_TTX_SUBTITLE ;        break;
        case IR_DVD_KEY_DVD_SELECT      :               Keycode= KEY_DVD_SELECT;        break;
        case IR_DVD_KEY_TTX_SIZE            :               Keycode= KEY_TTX_SIZE;                break;
        case IR_DVD_KEY_TTX_REVEAL         :               Keycode= KEY_TTX_REVEAL;        break;
        case IR_DVD_KEY_TTX_RED               :               Keycode= KEY_TTX_RED;              break;
        case IR_DVD_KEY_TTX_GREEN            :               Keycode= KEY_TTX_GREEN ;        break;
        case IR_DVD_KEY_TTX_YELLOW          :               Keycode= KEY_TTX_YELLOW;        break;
        case IR_DVD_KEY_TTX_CYAN             :               Keycode= KEY_TTX_CYAN ;        break;
        case IR_DVD_KEY_REPEAT            :               Keycode= KEY_REPEAT ;        break;
#endif		

        default:                 ucKeyMessage = _NONE_KEY_MESSAGE;                                break;
        }
#endif

        ucDetectIR_Cmd = 0;

        if (ucKeyMessage == _NONE_KEY_MESSAGE)
#endif        
        {
            CLR_KEYREPEATSTART();
            CTimerCancelTimerEvent(CKeyRepeatEnableTimerEvent);
        }
        break;
    }
#if(DVD_EN)
     if(_GET_INPUT_SOURCE()==_SOURCE_VIDEO_DVD&&Keycode!= 0xff)
     	{
             ProssMCU2DVDkeyHandle(Keycode);
			 	Keycode= 0xff;
     	}
#endif	 

    if (ucCurrState == _PWOFF_STATE)    // in power off mode not use key,but not include power key
        ucKeyMessage = _NONE_KEY_MESSAGE;
}
