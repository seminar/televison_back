////////////////////////////////////////////////////////////////////////////
//         Copyright of Vector Co.,Ltd.                                   //
//                                                                        //
//                                                                        //
//                       SetOSDDouble function                              //
//   Ver: 0.00                                                            //
//   Creat file time: 2006.7.31                                           //
//   End modify time: 2006.7.31                                           //
//   For RTD2523B/RTD2553V/RTD2525L                                       //
////////////////////////////////////////////////////////////////////////////

#include "Header\Include.h"


//-------------------------------------------------------------
void SetOSDDouble(BYTE ucAttr)
{
     CScalerSendAddr(_OSD_ADDR_MSB_90, _WRITE, _AUTOINC);
     CScalerSendByte(0x40);
     CScalerSendByte(0x03);
     CScalerSendByte(ucAttr);
     CScalerSendWriteStop();
}


