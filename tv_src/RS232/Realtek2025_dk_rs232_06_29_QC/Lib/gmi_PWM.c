
#include "Header\Include.h"


//------------------------------------------------------------
//                MCU DAC function
//------------------------------------------------------------
void CSetMCUPWM(BYTE PWMId, BYTE Value)
{
    BYTE xdata *p;


#if(_MCU_TYPE == _MYSON_MTV512)

    p = 0xF20 + PWMId;

#elif(_MCU_TYPE == _RTD_2120)
    
    p = 0xFF32 + PWMId;

#endif

    *p = Value;
}

//-------------------------------------------------
void CSetPWM(BYTE PWMId, BYTE Value)
{

     switch(PWMId)
     {
         case _SCALAR_PWM0:             // Scalar PWM
         case _SCALAR_PWM1:
         case _SCALAR_PWM2:
             pData[0] = PWMId << 6;     // PWM ID
             pData[1] = 0x01;
             pData[2] = Value;
             CScalerWrite(_OSD_ADDR_MSB_90,3,pData,_AUTOINC);
             break;

#if(_MCU_TYPE == _MYSON_MTV512 || _MCU_TYPE == _RTD_2120)
         case _MCU_PWM0:
         case _MCU_PWM1:
         case _MCU_PWM2:
              CSetMCUPWM(PWMId - _MCU_PWM0,Value);
              break;

         case _MCU_PWM3:
         case _MCU_PWM4:
         case _MCU_PWM5:
              CSetMCUPWM(PWMId - _MCU_PWM3,Value);
              break;
#endif
     }
}
//-------------------------------------------------

