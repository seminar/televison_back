////////////////////////////////////////////////////////////////////////////
//         Copyright of Vector Co.,Ltd.                                   //
//                                                                        //
//                                                                        //
//                           Gotoxy function                              //
//   Ver: 0.00                                                            //
//   Creat file time: 2006.7.31                                           //
//   End modify time: 2006.7.31                                           //
//   For RTD2523B/RTD2553V/RTD2525L                                       //
////////////////////////////////////////////////////////////////////////////

#include "Header\Include.h"


//-------------------------------------------------------------
void Gotoxy(BYTE x, BYTE y, BYTE TheByte)
{
     WORD iAddress = FONT_SELECT_ADDRESS + (y * ucCol_Count) + x;


     CScalerSendAddr(_OSD_ADDR_MSB_90, _WRITE, _AUTOINC);
     CScalerSendByte((BYTE)(((iAddress >> 8 ) & 0x0f) | TheByte));
     CScalerSendByte((BYTE)(iAddress & 0xff));
     CScalerSendWriteStop();
}


