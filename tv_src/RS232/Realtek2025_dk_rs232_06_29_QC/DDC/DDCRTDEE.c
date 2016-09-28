#include "Header\Include.h"


#if(_DDC_TYPE == _DCC_RTD_EEPROM)
//--------------------------------------------------------
void RTDDDCProc(void)
{
     #if(_VGA_SUPPORT)
     RTDDDCProc1(_EDID0_ADDRESS,_DDC_ENABLE_FA);
     #endif

     #if(_TMDS_SUPPORT)
     RTDDDCProc1(_EDID1_ADDRESS,_DDC_DVI_ENABLE_FD);
     #endif
}

//--------------------------------------------------------
void RTDDDCProc1(BYTE ucEEPRamAddr,BYTE ucRTDAddr)
{
     CScalerRead(ucRTDAddr, 1, pData, _NON_AUTOINC);
     if(pData[0] & 0x10)
     {          
          CTimerDelayXms(250);
          CTimerDelayXms(250);
          CTimerDelayXms(250);
          CTimerDelayXms(250);
          CTimerDelayXms(250);

          SaveRTDDDCToEE(ucEEPRamAddr,ucRTDAddr);
          CScalerSetByte(ucRTDAddr, 0x0d);    // Enable  DDC
     }
}

//--------------------------------------------------------
void LoadEEDDCToRTD(BYTE ucEEPRamAddr,BYTE ucRTDAddr)
{
     BYTE i;

     CScalerSetByte(ucRTDAddr, 0x00);    // Disable  DDC
     CScalerSetByte(ucRTDAddr + 1, 0x00);     // Set DDC Index

     // Write 128 Byte DDC Infomation
     for(i=0;i<8;i++)
     {
          CEepromRead(ucEEPRamAddr + (i * 16), 16 , pData);
          CScalerWrite(ucRTDAddr + 2, 16, pData, _NON_AUTOINC);
     }
     CScalerSetByte(ucRTDAddr, 0x0d);    // Enable  DDC

}

//--------------------------------------------------------
void SaveRTDDDCToEE(BYTE ucEEPRamAddr,BYTE ucRTDAddr)
{
     BYTE i;

     CScalerSetByte(ucRTDAddr, 0x00);         // Disable  DDC
     CScalerSetByte(ucRTDAddr + 1, 0x00);     // Set DDC Index

     // Write 128 Byte DDC Infomation
     for(i=0;i<8;i++)
     {
          CScalerRead(ucRTDAddr + 2, 16, pData, _NON_AUTOINC);
          CEepromWrite(ucEEPRamAddr + (i * 16), 16, pData);
     }
     CScalerSetByte(ucRTDAddr, 0x0d);          // Enable  DDC
}
//--------------------------------------------------------
#endif    //#if(DDC_TYPE == DDC_RTD_CODE)
