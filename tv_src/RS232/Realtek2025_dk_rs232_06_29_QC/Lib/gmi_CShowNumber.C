////////////////////////////////////////////////////////////////////////////
//         Copyright of Vector Co.,Ltd.                                   //
//                                                                        //
//                                                                        //
//                      CShowNumber function                              //
//   Ver: 0.00                                                            //
//   Creat file time: 2006.7.31                                           //
//   End modify time: 2006.7.31                                           //
//   For RTD2523B/RTD2553V/RTD2525L                                       //
////////////////////////////////////////////////////////////////////////////

#include "Header\Include.h"



//-------------------------------------------------------------
//----------------------------------------------------------- 
//  ucNumber:      0~65535
//  ucUserDefLong: 0   --> 自动计算ucNumber长度，有几位输出几位
//                 1~5 --> 输出1~5位，不足用0补
//  exp:           ucNumber = 12
//                 ucUserDefLong = 0    Output:  12
//                 ucUserDefLong = 3    Output:  012
//----------------------------------------------------------- 
void CShowNumber(const WORD ucNumber, BYTE ucUserDefLong)
{
    BYTE uctemp[5];
    
    uctemp[4] = (ucNumber / 10000) % 10;
    uctemp[3] = (ucNumber / 1000) % 10;
    uctemp[2] = (ucNumber / 100) % 10;
    uctemp[1] = (ucNumber / 10) % 10;
    uctemp[0] = ucNumber  % 10;
    
    if (ucUserDefLong)
        ucUserDefLong -= 1;     
    else    
    {
        for(pData[15] = 4; pData[15]>0;pData[15]--)
        {
            if(uctemp[pData[15]] != 0)
                break;          
        }
        
        ucUserDefLong = pData[15];
    }
    
    CScalerSendAddr(_OSD_DATA_PORT_92, _WRITE, _NON_AUTOINC);
    do
    {
        CScalerSendByte(uctemp[ucUserDefLong]+'0');
    }
    while(ucUserDefLong--);
    CScalerSendWriteStop();
}      


