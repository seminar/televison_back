////////////////////////////////////////////////////////////////////////////
//         Copyright of Vector Co.,Ltd.                                   //
//                                                                        //
//                                                                        //
//                     COsdFxCloseWindow function                         //
//   Ver: 0.00                                                            //
//   Creat file time: 2006.7.31                                           //
//   End modify time: 2006.7.31                                           //
//   For RTD2523B/RTD2553V/RTD2525L                                       //
////////////////////////////////////////////////////////////////////////////

#include "Header\Include.h"



//-------------------------------------------------------------
void COsdFxCloseWindow(BYTE ucWinID)
{

    pData[0]    = 0x81;
    pData[1]    = ucWinID * 4 + 3;
    pData[2]    = 0x00;
    CScalerWrite(_OSD_ADDR_MSB_90, 3, pData, _AUTOINC);
}


