////////////////////////////////////////////////////////////////////////////
//         Copyright of Vector Co.,Ltd.                                   //
//                                                                        //
//                                                                        //
//                            Tuner function                              //
//   Ver: 0.00                                                            //
//   Creat file time: 2006.7.31                                           //
//   End modify time: 2006.7.31                                           //
//   For RTD2523B/RTD2553V/RTD2525L                                       //
////////////////////////////////////////////////////////////////////////////

#include "Header\Include.h"



//==========================================================================
//                      Tuner FUNCTION
//==========================================================================
void gmi_Delay5us(void)
{
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    _nop_();
}

//==========================================================================
//
//==========================================================================
// For write tuner
void gmi_CI2CSendByte(BYTE ucSendData)
{
    BYTE m;

    for (m = 0; m < 8; m++)
    {
        if((bit)(ucSendData & 0x80))
            SETI2CSDA();
        else
            CLRI2CSDA();

	    gmi_Delay5us();

        SETI2CSCL();
        gmi_Delay5us();

        CLRI2CSCL();

        ucSendData    = ucSendData << 1;
    }
          
    SETI2CSDA();
    SETI2CSCL();
    gmi_Delay5us();

    CLRI2CSCL();
    gmi_Delay5us();
} 

//==========================================================================
//
//==========================================================================
BYTE gmi_CRead9886(void)
{	
    CI2cStart(_ADDR_9886 | _I2C_RD);			 
    pData[0] = CI2cGetByte();
    CI2cStop();
			   
    return pData[0];
}  

//==========================================================================
//
//==========================================================================
void gmi_CI2CWriteTuner(BYTE *Array)
{
    BYTE ucTemp = 0;

    SETI2CSCL();
    CLRI2CSDA();
    gmi_Delay5us();
    CLRI2CSCL();

    for(ucTemp = 1; ucTemp < Array[0]; ucTemp++)
    {
        gmi_CI2CSendByte(Array[ucTemp]);
    }

    CI2cStop();
}

