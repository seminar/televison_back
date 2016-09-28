////////////////////////////////////////////////////////////////////////////
//         Copyright of Vector Co.,Ltd.                                   //
//                                                                        //
//                                                                        //
//                     ValueInRangeChange function                        //
//   Ver: 0.00                                                            //
//   Creat file time: 2006.7.31                                           //
//   End modify time: 2006.7.31                                           //
//   For RTD2523B/RTD2553V/RTD2525L                                       //
////////////////////////////////////////////////////////////////////////////

#include "Header\Include.h"



//-------------------------------------------------------------
WORD ValueInRangeChange(WORD ucMin, WORD ucMax, WORD ucCur, BYTE ucOption, BYTE ucLoop)
{
    WORD R;

    if(ucOption)
    {
        if(ucCur >= ucMax)
        {
            if(ucLoop == 0)    return ucMax;
            else               return ucMin;
        }
        R = ucCur+1;
    }
    else
    {
        if(ucCur <= ucMin)
        {
            if(ucLoop == 0)    return ucMin;
            else               return ucMax;
        }
        R = ucCur-1;
    }
    return R;
}


