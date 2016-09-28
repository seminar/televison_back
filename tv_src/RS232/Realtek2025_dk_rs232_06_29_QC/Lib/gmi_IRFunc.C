////////////////////////////////////////////////////////////////////////////
//         Copyright of Vector Co.,Ltd.                                   //
//                                                                        //
//                                                                        //
//                              IR function                              //
//   Ver: 0.00                                                            //
//   Creat file time: 2006.7.31                                           //
//   End modify time: 2006.7.31                                           //
//   For RTD2523B/RTD2553V/RTD2525L                                       //
////////////////////////////////////////////////////////////////////////////

#include "Header\Include.h"


///////////////////////////////////////////////////////////////////////////////////////////////////////////////

//                                        IR FUNCTION

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
void gmi_CInitial_IR(void)
{
    //-----------------------------------
    //   add for IR
    //-----------------------------------
    // Initial INT0
    IT0     = 1;  // 0/1:  低电平/下降沿 触发
    PX0     = 0;  // 0/1:  低/高 优先级
    EX0     = 0;   // Disable external interrupt 0
}

void gmi_CStopIR(void)
{

    EX0 = 0;   // Disable external interrupt 0
}

void gmi_CStartIR(void)
{

    EX0 = 1;  // Enable external interrupt 0
}

void gmi_Delay_65us(void)
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

void gmi_IR_Delay(void)
{
    // Delay 365us
    do
    {
        // Delay 325us
        gmi_Delay_65us();
        gmi_Delay_65us();
        gmi_Delay_65us();
        gmi_Delay_65us();
        gmi_Delay_65us();
    
        // delay 40us
        Delay5us();
    
        Delay5us();
    
        Delay5us();
    
        Delay5us();
    
        Delay5us();
    
        Delay5us();
    
        Delay5us();
    
        Delay5us();
    }while(0);
}           


