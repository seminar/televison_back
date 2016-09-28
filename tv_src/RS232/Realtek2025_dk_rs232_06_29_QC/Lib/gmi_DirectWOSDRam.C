////////////////////////////////////////////////////////////////////////////
//         Copyright of Vector Co.,Ltd.                                   //
//                                                                        //
//                                                                        //
//                              GMI function                              //
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
                     
//-------------------------------------------------------------
void DirectWOSDRam(WORD iAddress, WORD iLen, BYTE TheByte, BYTE Value)
{

     CScalerSendAddr(_OSD_ADDR_MSB_90, _WRITE, _AUTOINC);
     CScalerSendByte(TheByte | ((iAddress >> 8) & 0x0f));
     CScalerSendByte((BYTE)(iAddress & 0xff));
     CScalerSendWriteStop();

     if(TheByte == ALL_BYTE)  
        iLen *= 3;

     CScalerSendAddr(_OSD_DATA_PORT_92, _WRITE, _NON_AUTOINC);

     while(iLen)
     {
         CScalerSendByte(Value);
         iLen--;
     }
     CScalerSendWriteStop();
}




