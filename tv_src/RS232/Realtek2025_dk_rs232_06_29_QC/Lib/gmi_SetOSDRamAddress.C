////////////////////////////////////////////////////////////////////////////
//         Copyright of Vector Co.,Ltd.                                   //
//                                                                        //
//                                                                        //
//                   SetOSDRamAddress function                            //
//   Ver: 0.00                                                            //
//   Creat file time: 2006.7.31                                           //
//   End modify time: 2006.7.31                                           //
//   For RTD2523B/RTD2553V/RTD2525L                                       //
////////////////////////////////////////////////////////////////////////////

#include "Header\Include.h"


//-------------------------------------------------------------
//                                                           //
//                       OSD function                        //
//                                                           //
//-------------------------------------------------------------
void SetOSDRamAddress(BYTE Row_Count, BYTE Col_Count, WORD iFntBaseAddr)
{
     WORD iFontSelectAddress;
     

     ucRow_Count = Row_Count;
     ucCol_Count = Col_Count;

     iFontSelectAddress = FONT_SELECT_ADDRESS;
     iFontBaseAddress = iFntBaseAddr;

     CScalerSendAddr(_OSD_ADDR_MSB_90, _WRITE, _AUTOINC);
     CScalerSendByte(0xc0);
     CScalerSendByte(0x04);
     CScalerSendWriteStop();

     CScalerSendAddr(_OSD_DATA_PORT_92, _WRITE, _NON_AUTOINC);
     CScalerSendByte(iFontSelectAddress & 0xff);
     CScalerSendByte(((iFontSelectAddress >> 4) & 0xf0) | (iFontBaseAddress & 0x0f));
     CScalerSendByte(((iFontBaseAddress >> 4) & 0xff));
     CScalerSendWriteStop();
}      
                     

