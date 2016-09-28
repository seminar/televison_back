////////////////////////////////////////////////////////////////////////////
//         Copyright of Vector Co.,Ltd.                                   //
//                                                                        //
//                                                                        //
//                       OutputChar function                              //
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
void OutputChar(BYTE C)
{
     CScalerSendAddr(_OSD_DATA_PORT_92, _WRITE, _NON_AUTOINC);
     CScalerSendByte(C);
     CScalerSendWriteStop();
}


