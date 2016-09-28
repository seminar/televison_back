#include "Header\Include.h"

#if(_IR_ENABLE)   
BYTE ucDetectIR_Cmd = 0;
#if _UARTIR
BYTE uchh;
BYTE ucll;
#endif 
#define _NEW_IR_DELAY      1
//------------------------------------------------------------------------------
//
//                            IR Function
//
//------------------------------------------------------------------------------
#if(0)   // Realtek standard IR
void Detect_IR(void)
{
    BYTE ucIR_Seq    = 0xff;
    BYTE ucTemp = 0;
    BYTE ucIR_State = 0;
    BYTE ucIR_Cmd[1];
 
    while(1)
    {
        if (ucIR_State)
        {
            if (bIR_GPIO)
            {
                ucIR_Seq    = (ucIR_Seq << 1) | 0x01;
                if ((0xff == ucIR_Seq) && (ucIR_State & 0xfe))
                {
                    ucIR_State  = 0;    // Command timeout; Back to idle state
                    ((unsigned int *)ucIR_Cmd)[0]   = 0;
                    break; // Add
                }
            }
            else
            {
                if (1 < ucIR_State)
                {
    
                    if (ucIR_Seq & 0x01)
                    {
                        ((unsigned int *)ucIR_Cmd)[0]   = (((unsigned int *)ucIR_Cmd)[0] << 1)
                                                        | (0x07 != (ucIR_Seq & 0x07) ? 1 : 0);
                        if (23 == ++ucIR_State && CUSTOM_CODE != ((unsigned int *)ucIR_Cmd)[0])
                        {
                            ucIR_State  = 0;    // Customer code error; Back to idle state
                            ((unsigned int *)ucIR_Cmd)[0]   = 0;
                            break;  // Add
                        }
                        else if (39 == ucIR_State)
                        {
                            ucIR_State  = 0;    // Command complete; Back to idle state
                            break; // Add
                        }
                    }
                    else if (0x00 == (ucIR_Seq & 0xfe))
                    {
                        ucIR_State  = 0;    // Command crashed; Back to idle state
                        ((unsigned int *)ucIR_Cmd)[0]   = 0;
                        break;// Add
                    }
                }
                else                        // ucIR_State is 1
                {
                    if (0xff == ucIR_Seq)
                    {
                        ucIR_State  = 0x07; // Start to decode new command and clear old command
                        ((unsigned int *)ucIR_Cmd)[0]   = 0;
                    }
                    else
                    {
                        ucIR_State  = 0;    // Fire repeat command and reset to idle
                        break; // Add
                    }
                }
                ucIR_Seq    = ucIR_Seq << 1;
            }
        }
        else
        {
            if (bIR_GPIO)
            {
                ucTemp ++;
                if (ucTemp > 10) // Timeout break
                {
                    ucTemp = 0;
                    break;
                }
            }

    	    ucIR_Seq    = (ucIR_Seq << 1) | bIR_GPIO;
            if (0x07 == ucIR_Seq)   ucIR_State  = 1;    // Leader code detected,IR data start
        }
    
        gmi_IR_Delay();
    }
           
    ucDetectIR_Cmd = (1 < ucIR_State) ? 0 : ucIR_Cmd[0];
}


#else 


#if(_NEW_IR_DELAY)
void gmi_Delay_65us1(void)
{
    Delay5us();
    Delay5us();
    Delay5us();
    Delay5us();
    Delay5us();
    Delay5us();
    Delay5us();
    Delay5us();
    Delay5us();
    Delay5us();
    Delay5us();
    Delay5us();
    Delay5us();
}

void IR_Delay(void)
{
#if(_REMOTE_CONTROLLER == IR_CHUNGHOP_RMH02)

      gmi_IR_Delay();
#else

        gmi_Delay_65us1();
        gmi_Delay_65us1();
        gmi_Delay_65us1();
        gmi_Delay_65us1();
        gmi_Delay_65us1();
        gmi_Delay_65us1();
        Delay5us();
        Delay5us();
      //  gmi_Delay_65us1();
      //  gmi_Delay_65us1();
       // gmi_Delay_65us1();
     //   gmi_Delay_65us1();
      //  gmi_Delay_65us1();
     //   gmi_Delay_65us1();

#endif

}    
#endif

#define DETECT_TIMEOUT_COUNT         100// 70    // Detect IR timeout count  70*375us = 26250us = 26.250ms
#define DETECTED_ERROR_IR_COMMAND     220   // Detect error
#define DETECTED_IR_COMMAND_COMPLETE  230   // Detect complete
#define LEVEL_HIGH_TO_LEVEL_LOW       0x02  // HIGH->Low
#define LEVEL_LOW_TO_LEVEL_HIGH       0x01  // Low->HIGH
#define LEVEL_LOW_LOW                 0x00  // Low->Low
#define LEVEL_HIGH_HIGH               0x03  // High->High
#define START_LOW_COUNT               16    // IR start low level number
#define START_HIGH_COUNT              8     // IR start high level number
#define REPEAT_HIGHT_COUNT            4
#define COUNT_IR_DATA_1               3     // If high level < 2,IR data is 1     1*375us~2*275us
//-------------------------------------------------------------------------------
// IR msg: step 1: bL_Start                 (incept IR start low level)
//         step 2: ?bL_Start = 1 -> bH_Start(incept IR start high level)
//         step 3: ?bL_Start = 1  ?bH_Start = 1  -> rIRData(incept ir data)
void Detect_IR(void)
{        
    static BYTE rIRData        = 0; // Readed IR data

    BYTE IRStatus     = 0; // IR GPIO state
    BYTE CountWave    = 0; // IR level count    
    BYTE rIRDataCount = 0; // Read IR data count
    bit  bL_Start     = 0; // IR start low level sign    1: Detected low level
    bit  bH_Start     = 0; // IR start high level sign   1: Detected high level
    bit  bRH_Start    = 0; // Repeat command start
//    ucDetectIR_Cmd    = 0;
    
    while(DETECT_TIMEOUT_COUNT > CountWave)
    {
        IRStatus = (IRStatus << 1) | bIR_GPIO;  // Save IR prot current level
        
        switch(IRStatus & 0x03)
        {
        case LEVEL_LOW_TO_LEVEL_HIGH:   // Low->HIGH
            if(CountWave > START_LOW_COUNT)
               bL_Start = 1;

            CountWave = 0;
            break;

        case LEVEL_HIGH_TO_LEVEL_LOW:   // HIGH->LOW
            if(!bL_Start)                                                     // Error
               CountWave=0;
            else if(CountWave > START_HIGH_COUNT)                             // IR data begin 
            {
                bH_Start = 1;
                CountWave = 0;
            }
            else if(CountWave > REPEAT_HIGHT_COUNT && rIRDataCount == 0)      // IR Repeat
            {
                bRH_Start = 1;
				 SET_KEYREPEATENABLE();
                CountWave = DETECTED_IR_COMMAND_COMPLETE;
            }                                                                
            else if(bH_Start && bL_Start)                                    // Get IR Data 
            {
                if (rIRDataCount < 24)
                    rIRData = (rIRData << 1) | ((CountWave < COUNT_IR_DATA_1) ? 0x01 : 0x00);

                rIRDataCount++;
                CountWave = 0;
                
                switch(rIRDataCount)  // Check detect code
                {
                case 8:    // Custom code high 8bit
#if(IR_Test_EN== _ON)    
		      CUSTOM_CODE_STATE_H=rIRData;
#else

                       #ifdef _UARTIR
                        uchh=rIRData;
			  #endif 		   
			  if (rIRData != (CUSTOM_CODE >> 8)) // Custom code high 8bit error
                        CountWave = DETECTED_ERROR_IR_COMMAND;
#endif
                    break;
                    
                case 16:    // Custom code low 8bit
#if(IR_Test_EN== _ON)    
		      CUSTOM_CODE_STATE_L=rIRData;
#else
                   #ifdef _UARTIR
                   ucll=rIRData;
                    #endif 
			if (rIRData != (CUSTOM_CODE & 0xff)) // Custom code low 8bit error
                        CountWave = DETECTED_ERROR_IR_COMMAND;
#endif
                    break;
                    
                case 24:    // Detected IR command data
#if(IR_Test_EN== _ON)    
                    ucDetectIR_Cmd = rIRData;
			CMD_DATA_INFO=rIRData;		
#else
                    ucDetectIR_Cmd = rIRData;
#endif
                    break;       
                                 
                case 32:    // Detected IR command complete
                    CountWave = DETECTED_IR_COMMAND_COMPLETE;
                    break;
                }  // end switch(rIRDataCount)
            }  
            break;

        case LEVEL_LOW_LOW:
        case LEVEL_HIGH_HIGH:
            CountWave++;
            break;
        }
        if(CountWave == DETECTED_ERROR_IR_COMMAND) // Detected ir code error 
           ucDetectIR_Cmd = 0;

#if(_NEW_IR_DELAY)
        IR_Delay();
#else
        gmi_IR_Delay();
#endif
    }

#if(IR_Test_EN== _ON)    
           ucDetectIR_Cmd = 0;

  #else
    // 0711 add for IR key repeat
//--------------------------------------------------------------------------------------
		



//------------------------------------------------------------------------------------
    if(bRH_Start && GET_KEYREPEATENABLE())
    {
         ucDetectIR_Cmd = rIRData;               // Repeat ir key value

    }

    #endif
}
#endif

//----------------------------  IR function end  ----------------------------------------


void Int0_IR_Proc(void) interrupt 0 
{
    gmi_CStopIR();

    Detect_IR(); // Detect IR code
    
    gmi_CStartIR(); 
}
#endif
