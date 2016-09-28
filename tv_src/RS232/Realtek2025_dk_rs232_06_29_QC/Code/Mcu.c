//----------------------------------------------------------------------------------------------------
// ID Code      : Mcu.c No.0002
// Update Note  : 
//
//----------------------------------------------------------------------------------------------------

#define __MCU__

#include  "Header\Include.h"
#if(_MCU_TYPE == _MYSON_MTV512 || _MCU_TYPE == _MYSON_MTV312 || _MCU_TYPE == _RTD_2120)
//--------------------------------------------------
//  MCU Initial
//--------------------------------------------------
void CMcuInitial(void)
{
#if(_MCU_TYPE == _RTD_2120)
    CKCON = 0x00;
#endif

    IE      = 0x00;                         // Disable all interrupts
    TMOD    = 0x11;                         // Program Timer0 & Timer1 to Mode#1
    TR0     = 0;                            // Stop Timer0
    TF0     = 0;                            // Clear Timer0 Overflow Bit
    TL0     = _TIMER0_COUNT_LBYTE;          // Load Timer0 low-byte   (for 1ms)
    TH0     = _TIMER0_COUNT_HBYTE;          // Load Timer0 high-byte  (for 1ms)
    TR1     = 0;                            // Stop Timer1
    TF1     = 0;                            // Clear Timer1 Overflow Bit

#if(_IR_ENABLE)
    gmi_CInitial_IR();
#endif

    // For MCU pad type control
    _MCU_PORT1_TYPE = _MCU_P1_TYPE_DEF;
    _MCU_PORT5_TYPE = _MCU_P5_TYPE_DEF;
    _MCU_PORT6_TYPE = _MCU_P6_TYPE_DEF;
   
    // For MCU pad mode control(input/output)
    _MCU_PORT5_I_O = _MCU_P5_MODE_DEF;
    _MCU_PORT6_I_O = _MCU_P6_MODE_DEF;
    _MCU_PORT7_I_O = _MCU_P7_MODE_DEF;
                             
#if(_MCU_TYPE == _MYSON_MTV512 || _MCU_TYPE == _MYSON_MTV312)

    _MCU_PORT7_TYPE = _MCU_P76_TYPE_DEF;
    MCU_PADMODE_F52 = _MCU_PADMODE_F52_DEF;

    MCU_OPTION_F56  = MCU_OPTION_F56_DEF;
    MCU_PADMODE_F5E = _MCU_PORT7_6_TYPE << 6;

    MCU_INTEN_F04   = MCU_INTEN_F04_DEF;                     // Detect WslvA1 IIC Stop Condition
    MCU_INTFLG_F03  = MCU_INTFLG_F03_DEF;                    // Clear IIC Interrupt register
    MCU_CTRSLVB_F0A = MCU_CTRSLVB_F0A_DEF;                   // Define IIC Protocal Slave Address Bit
    MCU_DDCCTRA1_F06 = MCU_DDCCTRA1_F06_DEF;                 // Enable DDC1 and DDCRAM 128 Access
    MCU_SLVA1ADR_F07 = MCU_SLVA1ADR_F07_DEF;                 // DDC Slave A1 address
    MCU_DDCCTRA2_F86 = MCU_DDCCTRA2_F86_DEF;                 // Enable DDC1 and DDCRAM 128 Access
    MCU_SLVA2ADR_F87 = MCU_SLVA2ADR_F87_DEF;                 //DDC Slave A2 address

#elif(_MCU_TYPE == _RTD_2120)

	MCU_PIN_SHARE1_FF01		= MCU_PINSHARE_FF01_DEF;		//P7.6 is P7.6, P3.1,p3.0 is IIC and set P3.3 to GPIO		
    MCU_ADC_DDC_ENA_FF20	= 0x07;
	MCU_DVI_DDC_ENA_FF23	= 0x07;
	MCU_I2C_IRQ_CTRL_FF2C   = 0x0c;

    // Enable MCU PWM
    MCU_PWM_CLK_CTRL_FF30   = 0x90;
     MCU_PWM_DIV_N_FF31 = 0x01;   
           //             MCU_PWM_DIV_N_FF31                    PWM FREQ
                                //  0x00                                          93.7KHz  
                              //    0x01                                           46.7KHz  
                              //    0x02                                            31.25KHz   
                               //   0x03                                            23.4KHz
    MCU_PWM_SRC_SELECT_FF35 = 0x00;  // eric 1227 add

#endif

/*
                      PNL1=1;
                      PNL2=1;
                      PNL3=0;
*/

#if(PowerUpLED==RedLED)			
		CPowerLedRed(); 
#elif(PowerUpLED==GreenLED)			
		CPowerLedGreen(); 
#elif(PowerUpLED==OrangeLED)			
		CPowerLedOrange(); 
#elif(PowerUpLED==BlackLED)			
		CPowerLedBlack(); 
#endif
	#if(DVD_EN)
        bDVD_PWR_OFF() ;
	#endif

    IE      = 0x82;                         // Enable interrupts of Timer0
}

#endif    //end #if(_MCU_TYPE == _MYSON_MTV512 || _MCU_TYPE == _MYSON_MTV312 || _MCU_TYPE == _RTD_2120)



#if(_MCU_TYPE == _STK_6021)

void CMcuInitial(void)
{
    IE      = 0x00;                         // Disable all interrupts
    TMOD    = 0x11;                         // Program Timer0 & Timer1 to Mode#1
    TR0     = 0;                            // Stop Timer0
    TF0     = 0;                            // Clear Timer0 Overflow Bit
    TL0     = _TIMER0_COUNT_LBYTE;          // Load Timer0 low-byte   (for 1ms)
    TH0     = _TIMER0_COUNT_HBYTE;          // Load Timer0 high-byte  (for 1ms)
    TR1     = 0;                            // Stop Timer1
    TF1     = 0;                            // Clear Timer1 Overflow Bit
    IE      = 0x8a;                         // Enable interrupts of Timer0
      
    MCU_PADOPT_F50 = MCU_PADOPT_F50_DEF;
    MCU_PADOPT_F51 = MCU_PADOPT_F51_DEF;
    MCU_PADOPT_F56 = MCU_PADOPT_F56_DEF;
#if(_IR_ENABLE)
    CInitial_IR();
#endif

#if(PowerUpLED==RedLED)			
		CPowerLedRed(); 
#elif(PowerUpLED==GreenLED)			
		CPowerLedGreen(); 
#elif(PowerUpLED==OrangeLED)			
		CPowerLedOrange(); 
#elif(PowerUpLED==BlackLED)			
		CPowerLedBlack(); 
#endif


}

#endif    //#if(_MCU_TYPE == _STK_6021)
