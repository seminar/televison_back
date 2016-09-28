////////////////////////////////////////////////////////////////////////////
//         Copyright of Vector Co.,Ltd.                                   //
//                                                                        //
//                                                                        //
//                       SetRowCmds function                              //
//   Ver: 0.00                                                            //
//   Creat file time: 2006.7.31                                           //
//   End modify time: 2006.7.31                                           //
//   For RTD2523B/RTD2553V/RTD2525L                                       //
////////////////////////////////////////////////////////////////////////////

#include "Header\Include.h"


void SetRowCmds(BYTE ucRowCnt, BYTE ucRowLenght)
{

    // Row Command Byte 0
    // 0x80
    //   Character border/shadow      000: None
    //   Double character width         0: 0x01
    //   Double character height        0: 0x01
    DirectWOSDRam(0x00, ucRowCnt, THE_BYTE0, 0x80);

    //Row End Command
    OutputChar(0x00);

    // Row Command Byte 1
    //    0x90
    //    Row height (1~32) : 18
    //    Column space        : 0
    DirectWOSDRam(0x00,ucRowCnt,THE_BYTE1,0x88);

    // Row Command Byte 2
    DirectWOSDRam(0x00,ucRowCnt,THE_BYTE2,ucRowLenght);  
}

