
#include "Header\Include.h"


BYTE CGetADCData(BYTE ucADID)
{
    BYTE ucADCCurrData = 0; 
       
#if(_MCU_TYPE == _MYSON_MTV512 || _MCU_TYPE == _STK_6021)

    MCU_ADC_F10   = 0x80 | (0x01 << ucADID); // Enable ADC
    CTimerDelayXms(3);
    ucADCCurrData = (MCU_ADC_F10 & 0x3f);    // Read ADC data
    MCU_ADC_F10   = 0x00;                    // Disable ADC

#elif(_MCU_TYPE == _RTD_2120)

    BYTE xdata *p;

    MCU_ADC_CTRL_FF0B = 0x80;
    CTimerDelayXms(3);
    p = 0xFF0C + ucADID;
    ucADCCurrData = (*p) & 0xfc;
    ucADCCurrData >>= 2;

#endif


    return ucADCCurrData;
}


