#define __DDCCIDBG__

#include <string.h>
#include "Header\Include.h"


void DDCCI_Debug()
{

     switch(ucDDCCI_RxBuf[2])
     {
        case DDC2B_CMD_DBG_READRTD:             DDCCI_DBG_Read_RTD();             break;
        case DDC2B_CMD_DBG_WRITERTD:            DDCCI_DBG_Write_RTD();            break;
        case DDC2B_CMD_DBG_READIIC:             DDCCI_DBG_Read_IIC();             break;
        case DDC2B_CMD_DBG_WRITEIIC:            DDCCI_DBG_Write_IIC();            break;
        case DDC2B_CMD_DBG_WRITERTDEX:          DDCCI_DBG_Write_RTDEX();          break;
        case DDC2B_CMD_DBG_STOP:                DDCCI_DBG_Stop();                 break;
        case DDC2B_CMD_DBG_RUN:                 DDCCI_DBG_Run();                  break;
        case DDC2B_CMD_DBG_READ512REG:          DDCCI_DBG_Read512Reg();           break;
        case DDC2B_CMD_DBG_WRITE512REG:         DDCCI_DBG_Write512Reg();          break;
        case DDC2B_CMD_DBG_VIRTUALKEY:          DDCCI_DBG_VirtualKey();           break;
   //     case DDC2B_CMD_DBG_CHGTOUART:           DDCCI_DBG_ChgUart();              break;
        case DDC2B_CMD_DBG_READ_RTD2120REG:     DDCCI_DBG_ReadRTD2120Reg();       break;
        case DDC2B_CMD_DBG_WRITE_RTD2120REG:    DDCCI_DBG_WriteRTD2120Reg();      break;

     }
}
//---------------------------------------------------------------------------------------
void DDCCI_DBG_Read_RTD()
{
     unsigned char i;

     ucDDCCI_TxBuf[CI_LENGTH] = ucDDCCI_RxBuf[4] + 2;
     ucDDCCI_TxBuf[COMMAND]	= DDC2B_CMD_DEBUG + 1;
     ucDDCCI_TxBuf[2] = DDC2B_CMD_DBG_READRTD;

     for(i=0;i<16;i++)
        pData[i] = 0;

     CScalerRead(ucDDCCI_RxBuf[3],ucDDCCI_RxBuf[4], pData, ucDDCCI_RxBuf[5]);
     //RTDRead(ucDDCCI_RxBuf[3],ucDDCCI_RxBuf[4],ucDDCCI_RxBuf[5]);
     for(i=0;i<ucDDCCI_RxBuf[4];i++)
         ucDDCCI_TxBuf[3 + i] = pData[i];
     TxCommandReady();
}

//---------------------------------------------------------------------------------------
void DDCCI_DBG_Write_RTD()
{
     ucDDCCI_TxBuf[CI_LENGTH]		= 2;
     ucDDCCI_TxBuf[COMMAND]		    = DDC2B_CMD_DEBUG + 1;
     ucDDCCI_TxBuf[2]		        = DDC2B_CMD_DBG_WRITERTD;
     RTDSetByte(ucDDCCI_RxBuf[3],ucDDCCI_RxBuf[4]);
     TxCommandReady();
}
//---------------------------------------------------------------------------------------
void DDCCI_DBG_Write_RTDEX()
{
     ucDDCCI_TxBuf[CI_LENGTH]		= 2;
     ucDDCCI_TxBuf[COMMAND]		    = DDC2B_CMD_DEBUG + 1;
     ucDDCCI_TxBuf[2]		        = DDC2B_CMD_DBG_WRITERTDEX;
     CScalerWrite(ucDDCCI_RxBuf[3], ucDDCCI_RxBuf[4], &ucDDCCI_RxBuf[6], ucDDCCI_RxBuf[5]);
     TxCommandReady();
}
//---------------------------------------------------------------------------------------
void DDCCI_DBG_Read_IIC()
{

     unsigned char i;
     ucDDCCI_TxBuf[CI_LENGTH]   = ucDDCCI_RxBuf[5] + 2;
     ucDDCCI_TxBuf[COMMAND]     = DDC2B_CMD_DEBUG + 1;
     ucDDCCI_TxBuf[2]           = DDC2B_CMD_DBG_READIIC;

     for(i=0;i<16;i++)
        pData[i] = 0;
     I2CRead(ucDDCCI_RxBuf[3],ucDDCCI_RxBuf[4],ucDDCCI_RxBuf[5]);
     for(i=0;i<ucDDCCI_RxBuf[5];i++)
         ucDDCCI_TxBuf[3 + i] = pData[i];
     TxCommandReady();
}
//---------------------------------------------------------------------------------------
void DDCCI_DBG_Write_IIC()
{
     // IIC WRITE
     pData[0] = 4;
     pData[1] = ucDDCCI_RxBuf[3];
     pData[2] = ucDDCCI_RxBuf[4];
     pData[3] = ucDDCCI_RxBuf[5];
     I2CWrite(pData);

     ucDDCCI_TxBuf[CI_LENGTH]		= 2;
     ucDDCCI_TxBuf[COMMAND]		= DDC2B_CMD_DEBUG + 1;
     ucDDCCI_TxBuf[2]		        = DDC2B_CMD_DBG_WRITEIIC;
     TxCommandReady();
}
//---------------------------------------------------------------------------------------
void I2CWrite(unsigned char *Array)
{
     CI2cWrite(Array[1], Array[2], Array[0] - 3, &Array[3]);
}
//---------------------------------------------------------------------------------------
void DDCCI_DBG_Stop()
{
     ucDDCCI_TxBuf[CI_LENGTH]              = 2;
     ucDDCCI_TxBuf[COMMAND]             = DDC2B_CMD_DEBUG + 1;
     ucDDCCI_TxBuf[2]                   = DDC2B_CMD_DBG_STOP;
     fDDCCI_Loop = 1;
     TxCommandReady();
}
//---------------------------------------------------------------------------------------
void DDCCI_DBG_Run()
{
     ucDDCCI_TxBuf[CI_LENGTH]           = 2;
     ucDDCCI_TxBuf[COMMAND]             = DDC2B_CMD_DEBUG + 1;
     ucDDCCI_TxBuf[2]                   = DDC2B_CMD_DBG_RUN;
     fDDCCI_Loop = 0;
     TxCommandReady();
}
//---------------------------------------------------------------------------------------
void DDCCI_DBG_VirtualKey()
{
     // Set Virtual Key
     ucVirtualKey = ucDDCCI_RxBuf[3];

     ucDDCCI_TxBuf[CI_LENGTH]           = 2;
     ucDDCCI_TxBuf[COMMAND]             = DDC2B_CMD_DEBUG + 1;
     ucDDCCI_TxBuf[2]                   = DDC2B_CMD_DBG_VIRTUALKEY;
     TxCommandReady();
}                     /*
//---------------------------------------------------------------------------------------
void DDCCI_DBG_ChgUart()
{
     //ucDDCCI_TxBuf[CI_LENGTH]           = 2;
     //ucDDCCI_TxBuf[COMMAND]             = DDC2B_CMD_DEBUG + 1;
     //ucDDCCI_TxBuf[2]                   = DDC2B_CMD_DBG_CHGTOUART;
     //TxCommandReady();
     
     #if(_RS232 == _ON)
     ChagneToUart();
     fDDCCI_Loop = 0;
     #endif
}         */
//---------------------------------------------------------------------------------------

void DDCCI_DBG_Read512Reg()
{
     unsigned char xdata *p;
     p = (0xf00 + ucDDCCI_RxBuf[3]);

     ucDDCCI_TxBuf[CI_LENGTH]           = 3;
     ucDDCCI_TxBuf[COMMAND]             = DDC2B_CMD_DEBUG + 1;
     ucDDCCI_TxBuf[2]                   = DDC2B_CMD_DBG_READ512REG;
     ucDDCCI_TxBuf[3]                   = *p;
     TxCommandReady();
}
//---------------------------------------------------------------------------------------
void DDCCI_DBG_Write512Reg()
{
     unsigned char xdata *p;
     p = (0xf00 + ucDDCCI_RxBuf[3]);
     *p = ucDDCCI_RxBuf[4];

     ucDDCCI_TxBuf[CI_LENGTH]           = 2;
     ucDDCCI_TxBuf[COMMAND]             = DDC2B_CMD_DEBUG + 1;
     ucDDCCI_TxBuf[2]                   = DDC2B_CMD_DBG_WRITE512REG;
     TxCommandReady();     
}
//---------------------------------------------------------------------------------------
void DDCCI_DBG_ReadRTD2120Reg()
{
     unsigned char xdata *p;
     p = (0xff00 + ucDDCCI_RxBuf[3]);

     ucDDCCI_TxBuf[CI_LENGTH]           = 3;
     ucDDCCI_TxBuf[COMMAND]             = DDC2B_CMD_DEBUG + 1;
     ucDDCCI_TxBuf[2]                   = DDC2B_CMD_DBG_READ_RTD2120REG;
     ucDDCCI_TxBuf[3]                   = *p;
     TxCommandReady();
}
//---------------------------------------------------------------------------------------
void DDCCI_DBG_WriteRTD2120Reg()
{
     unsigned char xdata *p;
     p = (0xff00 + ucDDCCI_RxBuf[3]);
     *p = ucDDCCI_RxBuf[4];

     ucDDCCI_TxBuf[CI_LENGTH]           = 2;
     ucDDCCI_TxBuf[COMMAND]             = DDC2B_CMD_DEBUG + 1;
     ucDDCCI_TxBuf[2]                   = DDC2B_CMD_DBG_WRITE_RTD2120REG;
     TxCommandReady();     
}
//---------------------------------------------------------------------------------------
void GetVirtualKey()
{
    if(ucKeyMessage == _NONE_KEY_MESSAGE)
    {
        ucKeyMessage = ucVirtualKey;
    }
    ucVirtualKey = _NONE_KEY_MESSAGE;
}
//---------------------------------------------------------------------------------------

