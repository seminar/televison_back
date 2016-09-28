#include "Header\Include.h"
#include "Rs232\Rs232.h"
//extern ProssMCU2DVDkeyHandle(Keycode);
#if (_REMOTE_CONTROLLER==IR_DK_QC)
void ProssMCU2DVDkeyHandleIR(BYTE Keycode)
{
	
//=====================================================
//上面发的值 转化为ir 码值注意发送方不能编译下面的
// 不然会形成互发码值
//=======================	==============================
   switch(Keycode)
   {
    case IR_FUNC_POWER:
	Trs2DVDIrSend(0xD7);   //
	break;

    case IR_FUNC_MUTE:
	Trs2DVDIrSend(0xDF);  //
	break;

//===============================	
// 下面是数字键
//===============================

     case IR_FUNC_NUM1:
	Trs2DVDIrSend(0x95);  //
	break;
	
     case IR_FUNC_NUM2:
	Trs2DVDIrSend(0x99);  //
	break;

     case IR_FUNC_NUM3:
	Trs2DVDIrSend(0x9D);  //
	break;

     case IR_FUNC_NUM4:
	Trs2DVDIrSend(0xD6);  //
	break;

     case IR_FUNC_NUM5:
	Trs2DVDIrSend(0xDA);  //
	break;

     case IR_FUNC_NUM6:
	Trs2DVDIrSend(0xDE);  //
	break;

     case IR_FUNC_NUM7:
	Trs2DVDIrSend(0x96);  //
	break;

     case IR_FUNC_NUM8:
	Trs2DVDIrSend(0x9A);  //
	break;

     case IR_FUNC_NUM9:
	Trs2DVDIrSend(0x9E);  //
	break;

     case IR_FUNC_NUM0:
	Trs2DVDIrSend(0xD9);  //
	break;
    
     case IR_FUNC_RETURN:
	Trs2DVDIrSend(0xDD); 
	break;
    
     case IR_FUNC_VOLINC :
	Trs2DVDIrSend(0x83); 
	break;
    
     case IR_FUNC_VOLDEC:
	Trs2DVDIrSend(0x86); 
	break;
    
     case IR_FUNC_CHINC:
	Trs2DVDIrSend(0x80); 
	break;

     case IR_FUNC_CHDEC:
	Trs2DVDIrSend(0x8E); 
	break;

     case IR_FUNC_ZOOM:
	Trs2DVDIrSend(0x82); 
	break;

     case IR_FUNC_MST:
	Trs2DVDIrSend(0x81); 
	break;

     case IR_FUNC_LEFT:
	Trs2DVDIrSend(0x97); 
	break;

     case IR_FUNC_RIGHT:
	Trs2DVDIrSend(0x9f); 
	break;

     case IR_FUNC_UP:
	Trs2DVDIrSend(0x92); 
	break;
    
     case IR_FUNC_DOWN:
	Trs2DVDIrSend(0xd8); 
	break;   

      case IR_FUNC_OK:
	Trs2DVDIrSend(0x9b); 
	break;   

      case IR_FUNC_MENU:
	Trs2DVDIrSend(0xd4); 
	break;   

      case IR_FUNC_EXIT:
	Trs2DVDIrSend(0xdc); 
	break;

      case IR_FUNC_SOURCE:
	Trs2DVDIrSend(0xc3); 
	break;

      case IR_FUNC_PMODE:
	Trs2DVDIrSend(0xc2); 
	break;

      case IR_FUNC_SMODE:
	Trs2DVDIrSend(0xc1); 
	break;

      case IR_FUNC_SLEEP:
	Trs2DVDIrSend(0xc0); 
	break;

      case IR_FUNC_FAV:
	Trs2DVDIrSend(0xc7); 
	break;

      case IR_FUNC_FAV_PLUS:
	Trs2DVDIrSend(0xc6); 
	break;

      case IR_FUNC_FAV_MINUS:
	Trs2DVDIrSend(0xc5); 
	break;   

      case IR_FUNC_EPG:
	Trs2DVDIrSend(0x89); 
	break;   

      case IR_FUNC_TEXT:
	Trs2DVDIrSend(0xcb); 
	break; 

      case IR_FUNC_HOLD:
	Trs2DVDIrSend(0xCA); 
	break; 

      case IR_FUNC_AUDIO:
	Trs2DVDIrSend(0xC9); 
	break; 


      case IR_FUNC_SUBT:
	Trs2DVDIrSend(0xC8); 
	break; 

      case IR_FUNC_INDEX:
	Trs2DVDIrSend(0xCF); 
	break; 

      case IR_FUNC_SIZE:
	Trs2DVDIrSend(0xCE); 
	break; 

      case IR_FUNC_REVEAL:
	Trs2DVDIrSend(0xCD); 
	break; 

      case IR_FUNC_SUBP:
	Trs2DVDIrSend(0xCC); 
	break; 

      case IR_FUNC_RED:
	Trs2DVDIrSend(0xD3); 
	break; 

       case IR_FUNC_GRENN:
	Trs2DVDIrSend(0xD2); 
	break; 

      case IR_FUNC_YELLOW:
	Trs2DVDIrSend(0xD1); 
	break; 

      case IR_FUNC_BULE:
	Trs2DVDIrSend(0xD0); 
	break; 


    
     	default:
	break;

   }


}

void ProssMCUIRHandle(BYTE Keycode)
{ 
        if(Keycode!=0)    
	        {
       
                    //CPowerPanelOff();
			ProssMCU2DVDkeyHandleIR(Keycode);// 遥控码发送
	           //  DebugPrintf("_MENU_KEY_MESSAGE.\n",0x01);
	              CUartPutCharToScr(pUartData[0]);
			CUartPutCharToScr(pUartData[2]);
			CUartPutCharToScr(pUartData[1]);
			CUartPutCharToScr(pUartData[3]);
		      CUartPutCharToScr(uchh);
			  uchh=0;
		      CUartPutCharToScr(ucll); 
			  ucll=0;
		      CUartPutCharToScr(Keycode);
		      CUartPutCharToScr(~Keycode);  
	      	 }

         if((Keycode==0)&&(uchh==0x7f))
         	{

			ProssMCU2DVDkeyHandleIR(Keycode);// 遥控码发送
	           //  DebugPrintf("_MENU_KEY_MESSAGE.\n",0x01);
	              CUartPutCharToScr(0xA0);
			CUartPutCharToScr(0x55);
			CUartPutCharToScr(0xF0);
			CUartPutCharToScr(0xFF);;
		      CUartPutCharToScr(uchh);
			  uchh=0;
		      CUartPutCharToScr(ucll); 
			  ucll=0;
		      CUartPutCharToScr(Keycode);
		      CUartPutCharToScr(~Keycode);  
	      	 }



}


//---------------------------------------------------------------------------------------
void ProssMCU2DVDkeyHandleTX(BYTE Keycode)
{

  switch(Keycode)
   {
     case _MENU_KEY_MESSAGE:
	Trs2DVDIrSend(0xD4);   //
	break;

     case _RIGHT_KEY_MESSAGE:
	Trs2DVDIrSend(0x9F);  //
	break;
	
     case _LEFT_KEY_MESSAGE:
	Trs2DVDIrSend(0x97); //
	break;
	
     case _UP_KEY_MESSAGE:
	Trs2DVDIrSend(0x92);  //
	break;
	
     case _DOWN_KEY_MESSAGE:
	Trs2DVDIrSend(0xD8); //
	break; 
	
     case _MUTE_KEY_MESSAGE:
	Trs2DVDIrSend(0xDF); // 0x1C
	break; 

    case _ENTER_KEY_MESSAGE:
	Trs2DVDIrSend(0x9B); //
	break; 

    case _INPUT_KEY_MESSAGE:// 
	Trs2DVDIrSend(0xC3); 
	break; 

    case _EXIT_KEY_MESSAGE:// 
	Trs2DVDIrSend(0xDC); 
	break; 

    case _IR_VOLINC_KEY_MESSAGE:// 
	Trs2DVDIrSend(0x83); 
	break; 

        case _IR_VOLDEC_KEY_MESSAGE:// 
	Trs2DVDIrSend(0x86); 
	break; 

        case _IR_CHINC_KEY_MESSAGE:// 
	Trs2DVDIrSend(0x80); 
	break; 

        case _IR_CHDEC_KEY_MESSAGE:// 
	Trs2DVDIrSend(0x8E); 
	break; 

        case IR_SLEEP_KEY_MESSAGE:// 
	Trs2DVDIrSend(0xC0); 
	break;

        case _IR_AVTYPE_KEY_MESSAGE:// 
	Trs2DVDIrSend(0x32); 
	break;

        case _IR_VGATYPE_KEY_MESSAGE:// 
	Trs2DVDIrSend(0x18); 
	break;

        case _IR_HDMITYPE_KEY_MESSAGE:// 
	Trs2DVDIrSend(0x16); 
	break;

        case _IR_TVTYPE_KEY_MESSAGE:// 
	Trs2DVDIrSend(0x1A); 
	break;

        case _IR_DTVTYPE_KEY_MESSAGE:// 
	Trs2DVDIrSend(0x19); 
	break;
    
    case _POWER_KEY_MESSAGE:// 
	Trs2DVDIrSend(0xD7); 
	break; 
//============================================
// 下面是数字键
//============================================

     case _NUM1_KEY_MESSAGE:// 
	Trs2DVDIrSend(0x95); 
	break;
	
     case _NUM2_KEY_MESSAGE:// 
	Trs2DVDIrSend(0x99); 
	break;

     case _NUM3_KEY_MESSAGE:// 
	Trs2DVDIrSend(0x9D); 
	break;

     case _NUM4_KEY_MESSAGE:// 
	Trs2DVDIrSend(0xD6); 
	break;

     case _NUM5_KEY_MESSAGE:// 
	Trs2DVDIrSend(0xDA); 
	break;

     case _NUM6_KEY_MESSAGE:// 
	Trs2DVDIrSend(0xDE); 
	break;

     case _NUM7_KEY_MESSAGE:// 
	Trs2DVDIrSend(0x96); 
	break;

     case _NUM8_KEY_MESSAGE:// 
	Trs2DVDIrSend(0x9A); 
	break;

     case _NUM9_KEY_MESSAGE:// 
	Trs2DVDIrSend(0x9E); 
	break;

     case _NUM0_KEY_MESSAGE:// 
	Trs2DVDIrSend(0xD9); 
	break;


   case _USB_KEY_MESSAGE:// 
	Trs2DVDIrSend(0x01); 
	break;


	 case _DVD_KEY_MESSAGE:// 
	Trs2DVDIrSend(0x06); 
	break;

	
     	default:
	break;


  	}

}

void ProssMCUTXHandle(BYTE Keycode)
{

   	//	ProssMCU2DVDkeyHandleTX(Keycode);
   	          Trs2DVDIrSend(Keycode);
              CUartPutCharToScr(pUartData[0]);
		CUartPutCharToScr(pUartData[2]);
		CUartPutCharToScr(pUartData[1]);
		CUartPutCharToScr(pUartData[3]);
	       CUartPutCharToScr(pUartData[4]);
	       CUartPutCharToScr(~pUartData[4]);





}

void ProssMCUTXHandlePOWER(BYTE Keycode)
{

             ProssMCU2DVDkeyHandleTX(Keycode);	
              CUartPutCharToScr(0xbb);
		CUartPutCharToScr(0x00);
		CUartPutCharToScr(0x1f);
		CUartPutCharToScr(0x01);
	       CUartPutCharToScr(pUartData[4]);
	       CUartPutCharToScr(~pUartData[4]);




}

#endif 


void Trs2DVDIrSendHead(void )
{


         #if(IR_TYPE==IR_AT020)
		     SendByteData(0x20);                               // DVB HEADER_CODE0 01
		     SendByteData(0xdf);                               // DVB HEADER_CODE1 fe
         #elif(IR_TYPE==IR_AT002)
		      SendByteData(0x20);                              
		      SendByteData(0xdf); 
	   #else 
                  SendByteData(0x03);
		  //  SendByteData(0xf7);
		 #endif	



}













