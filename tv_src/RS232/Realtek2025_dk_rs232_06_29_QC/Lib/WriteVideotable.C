////////////////////////////////////////////////////////////////////////////
//         Copyright of Vector Co.,Ltd.                                   //
//                                                                        //
//                                                                        //
//                              WriteVideotable                           //
//   Ver: 5.00                                                            //
//   Creat file time: 2006.8.24                                           //
//   End modify time: 2006.11.08                                          //
//   For RTD2523B/RTD2553V/RTD2525L                                       //
////////////////////////////////////////////////////////////////////////////

#include "Header\Include.h"


extern void CTimerDelayXms(WORD usNum);

void CWriteAllReg(BYTE ucScalerType, BYTE ucVideoMode, BYTE ucDisplayMode)
{
    bit bRegCtrl = 0;
    BYTE ucCount = 0;

    for(ucCount = 0; ucCount < 0xFF; ucCount++)
    {
       bRegCtrl = 1;

       switch(ucCount)
       {
          // For RTD2547D
          case 0x2A:
          case 0x2B:
          case 0x30:
          case 0x31:
          case 0x33:
          case 0x34:
          case 0x8D:
          case 0x8E:
          case 0x8B:
          case 0x8C:
              if (ucScalerType == _RTD2547D)
                  bRegCtrl = 0;
              break;

          case 0x90:  //_OSD_ADDR_MSB_90:
          case 0x91:  //_OSD_ADDR_LSB_91:
          case 0x92:  //_OSD_DATA_PORT_92:
          case 0x6C:  //_OVERLAY_CTRL_6C:
          case 0x6D:  //_BGND_COLOR_CTRL_6D:
          case 0x6E:  //_OVERLAY_LUT_ADDR_6E:
          case 0x6F:  //_COLOR_LUT_PORT_6F:
              bRegCtrl = 0;
              break;
       }

       if (bRegCtrl)
       {
          if (ucVideoMode == 60)     // NTSC
          {
              if (ucDisplayMode == 0x00)  // 16:9
                 CScalerSetByte(ucCount, tNTSC_16_9[ucCount]);
              else
                 CScalerSetByte(ucCount, tNTSC_4_3[ucCount]);
          }
          else
          {
              if (ucDisplayMode == 0x00)  // 16:9
                 CScalerSetByte(ucCount, tPAL_16_9[ucCount]);
              else
                 CScalerSetByte(ucCount, tPAL_4_3[ucCount]);
          }
       }
    }
              
    // Select RTD2547D page1
    if (ucScalerType == _RTD2547D)
    {
        CScalerSetByte(0xA0, 0x01);
        if (ucVideoMode == 60)     // NTSC
        {
            if (ucDisplayMode == 0x00)  // 16:9
               CScalerWrite(0xA0, 0x5F, tNTSC_PAGE1_16_9, _AUTOINC);
            else
               CScalerWrite(0xA0, 0x5F, tNTSC_PAGE1_4_3, _AUTOINC);
        }
        else
        {
            if (ucDisplayMode == 0x00)  // 16:9
               CScalerWrite(0xA0, 0x5F, tPAL_PAGE1_16_9, _AUTOINC);
            else
               CScalerWrite(0xA0, 0x5F, tPAL_PAGE1_4_3, _AUTOINC);
        }
    }      
}
       
//-----------------------------------------------------------------------

void CSetScalingFactor(BYTE ucVideoMode, BYTE ucDisplayMode)
{
    // Set scaling
    CScalerSetByte(0x1A, 0x80);
    if (ucVideoMode == 60)     // NTSC
    {
        if (ucDisplayMode == 0x00)  // 16:9
           CScalerWrite(0x1B, 6, tNTSC_SCALING_FACTOR_1A_16_9, _NON_AUTOINC);
        else
           CScalerWrite(0x1B, 6, tNTSC_SCALING_FACTOR_1A_4_3, _NON_AUTOINC);
    }
    else
    {
        if (ucDisplayMode == 0x00)  // 16:9
           CScalerWrite(0x1B, 6, tPAL_SCALING_FACTOR_1A_16_9, _NON_AUTOINC);
        else
           CScalerWrite(0x1B, 6, tPAL_SCALING_FACTOR_1A_4_3, _NON_AUTOINC);
    }
    CScalerSetByte(0x1A, 0x00);
}
//-----------------------------------------------------------------------

void CSetRtdVScalingDown(BYTE ucVideoMode, BYTE ucDisplayMode, BYTE ucCount)
{
    CScalerSetByte(0x24, 0x80); // _SD_ACCESS_PORT_24
    if (ucVideoMode == 60)     // NTSC
    {
        if (ucDisplayMode == 0x00)  // 16:9
           CScalerWrite(0x25, ucCount, tNTSC_SCALING_DOWN_24_16_9, _NON_AUTOINC);
        else
           CScalerWrite(0x25, ucCount, tNTSC_SCALING_DOWN_24_4_3, _NON_AUTOINC);
    }
    else
    {
        if (ucDisplayMode == 0x00)  // 16:9
           CScalerWrite(0x25, ucCount, tPAL_SCALING_DOWN_24_16_9, _NON_AUTOINC);
        else
           CScalerWrite(0x25, ucCount, tPAL_SCALING_DOWN_24_4_3, _NON_AUTOINC);
    }
    CScalerSetByte(0x24, 0x00);
}
//-----------------------------------------------------------------------

// For RTD2547D
void CSetDisplayFormat(BYTE ucVideoMode, BYTE ucDisplayMode)
{
    CScalerSetByte(0x2A, 0x00); 
    if (ucVideoMode == 60)     // NTSC
    {
        if (ucDisplayMode == 0x00)  // 16:9
           CScalerWrite(0x2B, 0x23, tNTSC_DISP_FORMAT_2A_16_9, _NON_AUTOINC);
        else
           CScalerWrite(0x2B, 0x23, tNTSC_DISP_FORMAT_2A_4_3, _NON_AUTOINC);
    }
    else
    {
        if (ucDisplayMode == 0x00)  // 16:9
           CScalerWrite(0x2B, 0x23, tPAL_DISP_FORMAT_2A_16_9, _NON_AUTOINC);
        else
           CScalerWrite(0x2B, 0x23, tPAL_DISP_FORMAT_2A_4_3, _NON_AUTOINC);
    }
}
//-----------------------------------------------------------------------

// FIFO window
void CSetFIFOWindow(BYTE ucVideoMode, BYTE ucDisplayMode)
{
    CScalerSetByte(0x30, 0x00); 
    if (ucVideoMode == 60)     // NTSC
    {
        if (ucDisplayMode == 0x00)  // 16:9
           CScalerWrite(0x31, 0x12, tNTSC_FIFO_WINDOW_30_16_9, _NON_AUTOINC);
        else
           CScalerWrite(0x31, 0x12, tNTSC_FIFO_WINDOW_30_4_3, _NON_AUTOINC);
    }                             
    else
    {
        if (ucDisplayMode == 0x00)  // 16:9
           CScalerWrite(0x31, 0x12, tPAL_FIFO_WINDOW_30_16_9, _NON_AUTOINC);
        else
           CScalerWrite(0x31, 0x12, tPAL_FIFO_WINDOW_30_4_3, _NON_AUTOINC);
    }
}
//-----------------------------------------------------------------------


// SF access port
void CSetSFAccessPort(BYTE ucVideoMode, BYTE ucDisplayMode)
{
    CScalerSetByte(0x33, 0x80);
    if (ucVideoMode == 60)     // NTSC
    {
        if (ucDisplayMode == 0x00)  // 16:9
           CScalerWrite(0x34, 0x11, tNTSC_SF_ACCESS_PORT_33_16_9, _NON_AUTOINC);
        else
           CScalerWrite(0x34, 0x11, tNTSC_SF_ACCESS_PORT_33_4_3, _NON_AUTOINC);
    }                             
    else
    {
        if (ucDisplayMode == 0x00)  // 16:9
           CScalerWrite(0x34, 0x11, tPAL_SF_ACCESS_PORT_33_16_9, _NON_AUTOINC);
        else
           CScalerWrite(0x34, 0x11, tPAL_SF_ACCESS_PORT_33_4_3, _NON_AUTOINC);
    }
    CScalerSetByte(0x33, 0x00);
}
//-----------------------------------------------------------------------

void CTB1334VideoMode(BYTE ucVideoMode, BYTE ucScalerType)
{
    WORD ustemp,ModeIHTotal;
    BYTE temp;

    ModeIHTotal = (ucVideoMode == 60) ? 858 : 864;

    if (ucScalerType == _RTD2547D)
    {
        CScalerSetBit(0x32, ~_BIT7, _BIT7);
        CScalerSetByte(0xA0, (5 & 0x07));
        CScalerSetBit(0xB9, ~_BIT7, _BIT7);//For interlace mode odd field toggle
        CScalerSetBit(0x13, ~_BIT0, _BIT0);
    }
    else
    {
        CScalerSetBit(0x19, ~_BIT7, _BIT7);
        CScalerSetBit(0x08, ~_BIT0, _BIT0);
    }
             
    // Change to even/odd field frame sync
    if (ucScalerType == _RTD2547D)   
       CScalerSetByte(0x19, CScalerGetBit(0x19, 0xff) + 1);              
    else
       CScalerSetByte(0x0E, CScalerGetBit(0x0E, 0xff) + 1);   

    CScalerRead(0x41, 1, &temp, _NON_AUTOINC);
    ustemp = (WORD)temp * 16 + 16;
    ustemp += ModeIHTotal;
    CScalerSetByte(0x41, (ustemp - 16) / 16);
    ustemp -= ModeIHTotal / 2;
    CScalerSetByte(0x42, (ustemp - 16) / 16);
    CScalerSetBit(0x43, ~(_BIT1), _BIT1);
                                                
    if (ucScalerType == _RTD2547D)
    {
        CScalerSetByte(0xA0, (5 & 0x07));
        CScalerSetByte(0xCF,0x05);
        CTimerDelayXms(100);
        CScalerSetByte(0xD0,0x10);
    }
    else
        CScalerSetBit(0xC2, ~_BIT5, 0x00); //V304 modify    

}

void gmi_CSetMode(BYTE ucVideoMode, BYTE ucDisplayMode, BYTE ucScalerType)
{
    BYTE value;


    // Select RTD2547D page0
    if (ucScalerType == _RTD2547D)
       CScalerSetByte(0xA0, (0 & 0x07));

    // Set ADC input to ADC1
    if (ucScalerType == _RTD2553V || ucScalerType == _RTD2525L)
    {                     
      //  CScalerSetDataPortBit(0xDC, 0x00, ~_BIT3, _BIT3);
        
        CScalerSetByte(0xDC, 0x80);
        CScalerRead(0xDD, 1, &value, _AUTOINC);
        
        value |= _BIT3;
        
        CScalerSetByte(0xDC, 0x80);
        CScalerSetByte(0xDD, value);
        CScalerSetByte(0xDC, 0x00);
    }

    //--------------------------------------------------
    // 256 regsister
    CWriteAllReg(ucScalerType, ucVideoMode, ucDisplayMode);


    //--------------------------------------------------
    // Scaling factor
    if (ucScalerType != _RTD2547D)
       CSetScalingFactor(ucVideoMode, ucDisplayMode);

    //--------------------------------------------------
    // Scaling V scaling down
    if (ucScalerType == _RTD2553V || ucScalerType == _RTD2525L || ucScalerType == _RTD2547D)
    {
        BYTE ucCount = 0x0D; // Normal to 2553V/2525L

        if(ucScalerType == _RTD2547D)
           ucCount = 0x14;

        CSetRtdVScalingDown(ucVideoMode, ucDisplayMode, ucCount);
    }
                     
    //--------------------------------------------------
    if (ucScalerType == _RTD2547D)
    {
        // Display format
        CSetDisplayFormat(ucVideoMode, ucDisplayMode);

        // FIFO window
        CSetFIFOWindow(ucVideoMode, ucDisplayMode);

        // SF access port
        CSetSFAccessPort(ucVideoMode, ucDisplayMode);
    }
                       
    // Write coefficient for sharpness
    CAdjustSharpness();

    //--------------------------------------------------
    // Power up ADC
    if (ucScalerType == _RTD2553V || ucScalerType == _RTD2525L)  // RTD2553V/RTD2525L
    {
	  // CScalerSetDataPortBit(_ADC_ACCESS_PORT_DC, 0x0c, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));        
        CScalerSetByte(0xDC, 0x8C);
        CScalerRead(0xDD, 1, &value, _AUTOINC);
        
        value = value | _BIT2 | _BIT1 | _BIT0;
        
        CScalerSetByte(0xDC, 0x8C);
        CScalerSetByte(0xDD, value);
        CScalerSetByte(0xDC, 0x00);
    }

    // Read source video8 or vga
    if (ucScalerType == _RTD2547D)
       CScalerRead(0x10, 1, &value, _AUTOINC);
    else
       CScalerRead(0x05, 1, &value, _AUTOINC);
    if ((value & 0x0C) == 0x00)             // VGA  only for TB334 write table
    {
        CTB1334VideoMode(ucVideoMode, ucScalerType);
    }
}

