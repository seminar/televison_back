////////////////////////////////////////////////////////////////////////////
//         Copyright of Vector Co.,Ltd.                                   //
//                                                                        //
//                                                                        //
//                       Video Decoder function                           //
//   Ver: 6.20                                                            //
//   Create file time: 2006.10.6                                          //
//   End modify time: 2007.2.27                                           //
//   For RTD2523B/RTD2553V/RTD2525L                                       //
////////////////////////////////////////////////////////////////////////////
#include "Header\Include.h"


#if(_VIDEO_CHIP == _VDC_TB1334)

#define _TB1334_VIDEODEVICE               0x88

void CNotUseFunc(void);

unsigned char VideoDecAddress = 0;


//==============================================================================  
// Input Value : Null
// Output Value: Null
// Description : 
//============================================================================== 
void Nop(void)  // Delay 8us
{
    _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_();
    _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_();
    _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_();
}

//==============================================================================  
// Input Value : Null
// Output Value: Null
// Description : 
//============================================================================== 
void gmi_CDelay80Us(void)  // Delay 80us
{
    do
    {
        Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
        Nop();
        Nop();
        Nop();
    }while(0);   
}  
unsigned char code tInitialVDCdata[] =
{           
       0x4A,0x26, 0x40, 0x14, 0x40, 0x01, 0x02, 0x00,
       0x00,0x00, 0x40, 0x80, 0x9f, 0x6e, 0x0c, 0x80, 
     0x31,0x00, 0x04, 0x87, 0x40, 0x00, 0xc0, 0x88,
     0x20,0x00, 0x58, 0x40, 0x20, 0x20, 0x10, 0x10,
     0x40,0x00, 0x01,   
};

void gmi_CI2CWriteVDCByte(const unsigned char ucAddress, const unsigned char ucWriteValue)
{
    unsigned char ucTemp[1];

    ucTemp[0] = ucWriteValue;
    CI2cWrite(_TB1334_VIDEODEVICE, ucAddress, 1, ucTemp);  
}

unsigned char gmi_CI2CReadVDCByte(const unsigned char ucAddress)
{
    unsigned char ucTemp[3] = 0;


    CI2cRead(_TB1334_VIDEODEVICE, 0x00, 3, ucTemp);

    switch(ucAddress)
    {
    case 0x00:   return ucTemp[0];
    case 0x01:   return ucTemp[1];
    case 0x02:   return ucTemp[2];
    }
}

unsigned char gmi_CVideoCurrentColor(bit bMode)
{
    unsigned char ucTemp[3] = 0;

    CI2cRead(_TB1334_VIDEODEVICE, 0x00, 3, ucTemp);


    if (((ucTemp[0] & 0x40) != 0x40 && VideoDecAddress == 1) || // TV
        ((ucTemp[0] & 0x20) != 0x20 && VideoDecAddress == 0))   // AV/SV
        return 0;               
    else   
    {     //  eric 1205 mdify for tv change mode 
        if (!bMode)
        {
           if (ucTemp[1]&0x80)  // 60Hz
               return 0x01;
           else
               return 0x02;
        }   

        ucTemp[0] = (ucTemp[0] >> 2) & 0x07;
        switch(ucTemp[0])
        {
            case 0x00:  // No color
            case 0x07:  // N/A     
                return 0x00;

            case 0x02:  // PAL M
            case 0x04:  // NTSC 358
            case 0x05:  // NTSC 443
                return 0x01; // 60Hz


            case 0x01:  // PAL 4.43 
            case 0x03:  // PAL N   
            case 0x06:  // SECAM   
                return 0x02; // 50Hz
        }
    }

    bMode = 0;
}

void gmi_CInitialVDC(void)
{
    unsigned char uctemp[3];

    CI2cRead(_TB1334_VIDEODEVICE, 0x00, 3, uctemp);
    do
    {
        gmi_CDelay80Us();gmi_CDelay80Us();gmi_CDelay80Us();gmi_CDelay80Us();gmi_CDelay80Us();
        gmi_CDelay80Us();gmi_CDelay80Us();gmi_CDelay80Us();gmi_CDelay80Us();gmi_CDelay80Us();
        CI2cRead(_TB1334_VIDEODEVICE, 0x00, 3, uctemp);
    }while((uctemp[0] & 0x80));
                          
    for(uctemp[0] = 0x00; uctemp[0] < 0x23; uctemp[0]++)
    {
        gmi_CI2CWriteVDCByte(uctemp[0], tInitialVDCdata[uctemp[0]]);
        gmi_CDelay80Us();
    }
                            
    gmi_CDelay80Us();gmi_CDelay80Us();gmi_CDelay80Us();gmi_CDelay80Us();gmi_CDelay80Us();
    gmi_CDelay80Us();gmi_CDelay80Us();gmi_CDelay80Us();gmi_CDelay80Us();gmi_CDelay80Us();

    uctemp[0] = 0;

	if(1 == uctemp[0])  
	{
       CNotUseFunc();
	}
}

//==============================================================================  
// Input Value : Null
// Output Value: Null
// Description : 
//============================================================================== 
void gmi_CSetVDCFreeRunMode(const unsigned char ucMode)  // eric 0308 add
{
    unsigned char uctemp;

    switch(ucMode)
    {
    default:
    case _VDC_FREE_RUN_MODE_TO_AUTO: // Set output coast frequency to auto mode
        uctemp = 0x00 | 0x01;
        break;

    case _VDC_FREE_RUN_MODE_TO_60HZ: // Set output coast frequency to 60 HZ mode
        uctemp = (0x02 << 5) | 0x01;
        break;

    case _VDC_FREE_RUN_MODE_TO_50HZ:  // Set output coast frequency to 50HZ mode
        uctemp = (0x01 << 5) | 0x01;
        break;
    }

    gmi_CI2CWriteVDCByte(0x15, uctemp); // Set output coast frequency to 50HZ mode   
}

//==============================================================================  
// Routine Name: 
// Input Value : 
// Output Value: 
// Description : 
//============================================================================== 
void gmi_CVDCOutputDisable(void)
{

}

//==============================================================================  
// Routine Name: bit CModeLocked(void)
// Input Value : Null
// Output Value: 0 --> No locked       1 --> Locked
// Description : Check video lock
//============================================================================== 
bit gmi_CModeLocked(void)
{                    
    unsigned char ucTemp = gmi_CI2CReadVDCByte(0x00);
    

    if (((ucTemp & 0x40) != 0x40 && VideoDecAddress == 1) || 
        ((ucTemp & 0x20) != 0x20 && VideoDecAddress == 0))   
        return 0;               
    else
        return 1;  // Signal detected
    
}


//-------------------------------------------
// 
//       
//-------------------------------------------
void gmi_CSelectInputChannel(unsigned char ucYCrChannel, unsigned char ucCbChannel)
{                                                              
    unsigned char uctemp = 0;
    
     
     uctemp = (ucYCrChannel & 0xf0) | 0x03;
                        
     ucYCrChannel &= 0x0f;
     if (ucYCrChannel != 0x0f)  
     {
         switch(ucYCrChannel)
         {
         case _YCBCR2_INPUT:
         case _YCBCR3_INPUT:
             gmi_CI2CWriteVDCByte(0x06, 0x02);  
             uctemp |= 0x04;
             break;

         case _SCART_INPUT:
             gmi_CI2CWriteVDCByte(0x06, 0x02); 
             uctemp &= 0xFD;  
             break;

         default:
             uctemp |= 0x10;        
    
             if (ucYCrChannel == _CHROMA_C1)
                 ucYCrChannel = 0x20;
             else
                 ucYCrChannel = 0xA0;
    
             gmi_CI2CWriteVDCByte(0x1D, ucYCrChannel); 
    
             gmi_CI2CWriteVDCByte(0x03, 0x60);  
             gmi_CI2CWriteVDCByte(0x06, 0x00);  
             break;
         }
     }
     else 
     {                  
         gmi_CI2CWriteVDCByte(0x06, 0x02);  
         uctemp |= 0x08;
     }     

     gmi_CI2CWriteVDCByte(0x07, uctemp);    
     ucCbChannel = ucCbChannel;
}

//==============================================================================  
// Input Value : Null
// Output Value: Null
// Description : 
//============================================================================== 
void gmi_CAdjustVDCBrightness(const unsigned char ucVDCBrightness)
{


    gmi_CI2CWriteVDCByte(0x01, (unsigned int)(ucVDCBrightness*0x7F)/100);  // Set VDC brightness
}

//==============================================================================  
// Input Value : Null
// Output Value: Null
// Description : 
//============================================================================== 
void gmi_CAdjustVDCContrast(const unsigned char ucVDCContrast)
{

    gmi_CI2CWriteVDCByte(0x00, (((unsigned int)ucVDCContrast*0x7F)/100)); // Set VDC contrast
}

//==============================================================================  
// Input Value : Null
// Output Value: Null
// Description : 
//============================================================================== 
void gmi_CAdjustVDCSaturation(const unsigned char ucVDCSaturation)
{

    gmi_CI2CWriteVDCByte(0x02, (((unsigned int)ucVDCSaturation*0x7F)/100)); // Set VDC saturation
}

//==============================================================================  
// Input Value : Null
// Output Value: Null
// Description : 
//============================================================================== 
void gmi_CAdjustVDCHue(const unsigned char ucVDCHue)
{
    unsigned char uctemp = gmi_CVideoCurrentColor(0);
    unsigned char temp = 0;

    temp = (unsigned int)(ucVDCHue*0x7F)/100;
    uctemp = (uctemp == 1) ? 0x00 : 0x80;

    gmi_CI2CWriteVDCByte(0x04, temp | uctemp);  // Set VDC HUE
}

//==============================================================================  
//                              TV

// Definitions for TV color
#define _LIB_TV_NTSC_M             0x00    // 60Hz Sound 4.5M  NTSC M
#define _LIB_TV_NTSC_4_BG          0x01    // 60Hz Sound 5.5M  NTSC 4/BG
#define _LIB_TV_NTSC_4_DK          0x02    // 60Hz Sound 6.5M  NTSC 4/DK
#define _LIB_TV_NTSC_4_I           0x03    // 60Hz Sound 6.0M  NTSC 4/I
#define _LIB_TV_PAL_M              0x04    // 60Hz Sound 4.5M  PAL M

#define _LIB_TV_PAL_BG             0x05    // 50Hz Sound 5.5M  PAL B/G
#define _LIB_TV_PAL_I              0x06    // 50Hz Sound 6.0M  PAL I
#define _LIB_TV_PAL_DK             0x07    // 50Hz Sound 6.5M  PAL D/K
#define _LIB_TV_PAL_N              0x08    // 50Hz Sound 4.5M  PAL N

#define _LIB_TV_SECAM_BG           0x09    // 50Hz Sound 5.5M  SECAM B/G
#define _LIB_TV_SECAM_DK           0x0a    // 50Hz Sound 6.5M  SECAM D/K
#define _LIB_TV_SECAM_L            0x0b    // 50Hz Sound 6.5M  SECAM L
#define _LIB_TV_SECAM_LL           0x0c    // 50Hz Sound 6.5M  Secam L'

// Pif freq
#define _PIF_45_75_MHZ             0x00
#define _PIF_39_5_MHZ              0x20
#define _PIF_38_9_MHZ              0x40
#define _PIF_38_0_MHZ              0x60
#define _PIF_34_2_MHZ              0x80
#define _PIF_33_9_MHZ              0xA0

//============================================================================== 
// ucMode:  _SEARCH_CHANNEL_MODE/_NORMAL_MODE
// _SEARCH_CHANNEL_MODE 0x00
// _NORMAL_MODE         0x80
//============================================================================== 
void CSetPifFreq(const unsigned char ucAFTMode, const unsigned int PifFreq)
{
    unsigned char ucTemp = (ucAFTMode == 0x00) ? 0x00 : 0x02;
             
    ucTemp |= 0x0C;
    switch(PifFreq)
    {
    case 45750:       ucTemp |= _PIF_45_75_MHZ;       break;
    case 39500:       ucTemp |= _PIF_39_5_MHZ;        break;
    case 38900:       ucTemp |= _PIF_38_9_MHZ;        break;
    case 38000:       ucTemp |= _PIF_38_0_MHZ;        break;
    case 34200:       ucTemp |= _PIF_34_2_MHZ;        break;
    case 33900:       ucTemp |= _PIF_33_9_MHZ;        break;
    }

    gmi_CI2CWriteVDCByte(0x0D, ucTemp); 
        
}

//============================================================================== 
// bSelect:      0: -> PAL           1: SECAM L
//CarrierSelect: 0: Split carrier    1: Inter carrier
//============================================================================== 
void CSelectPalOrSecamL(bit bSelect, const unsigned char ucAFTMode, const unsigned char CarrierSelect)
{
    if (bSelect)  
    {
        gmi_CI2CWriteVDCByte(0x0C, 0x07);  
        if (ucAFTMode == 0x00)  
           gmi_CI2CWriteVDCByte(0x12, 0x07); 
        else                   
           gmi_CI2CWriteVDCByte(0x12, 0x05); 
        gmi_CI2CWriteVDCByte(0x1A, 0x18);  
    }
    else  // PAL
    {
        if (CarrierSelect)
            gmi_CI2CWriteVDCByte(0x0C, 0x9F);  
        else
            gmi_CI2CWriteVDCByte(0x0C, 0x1F);  
        gmi_CI2CWriteVDCByte(0x12, 0x00);  
        gmi_CI2CWriteVDCByte(0x1A, 0x58);  
    }
}

//============================================================================== 
// ucMode->_NORMAL_MODE->AFT-S range of the AFT-W read narrow
//       ->_SEARCH_CHANNEL_MODE->AFT-S range of the AFT-W read wide
//
//============================================================================== 
void CSetSIFFreq(const unsigned char SifFreq, const unsigned char ucAFTMode)
{
    gmi_CI2CWriteVDCByte(0x0E, 0x08 | ucAFTMode | (SifFreq << 1));
}

//============================================================================== 
// ucTVColorMode:    _TV_NTSC_M,   _TV_NTSC_4_BG, _TV_NTSC_4_DK 
//                   _TV_NTSC_4_I, _TV_PAL_M  --> 60Hz
//                   ------------------------------------------
//                   _TV_PAL_BG,   _TV_PAL_I,     _TV_PAL_DK,
//                   _TV_PAL_N     --> 50Hz PAL
//                   ------------------------------------------
//                   _TV_SECAM_BG, _TV_SECAM_DK,  _TV_SECAM_L
//                   _TV_SECAM_LL  --> 50Hz SECAM
//-------------------------------------------------------------
// ucMode:       _SEARCH_CHANNEL_MODE/_NORMAL_MODE
// PifFreq:      45750/39500/38900/38000/34200/33900 KHz
//CarrierSelect: 0: Split carrier    1: Inter carrier
//============================================================================== 
void gmi_CSetIfMode(const unsigned char ucTVColorMode, const unsigned char ucMode, const unsigned int PifFreq, const unsigned char CarrierSelect)
{
    switch(ucTVColorMode)
    {
    default:                // Normal sound
    case _LIB_TV_NTSC_M    :    // 60Hz NTSC M
    case _LIB_TV_NTSC_4_BG :    // 60Hz NTSC 4/BG
    case _LIB_TV_NTSC_4_I  :    // 60Hz NTSC 4/I
    case _LIB_TV_NTSC_4_DK :    // 60Hz NTSC 4/DK
    case _LIB_TV_PAL_BG    :    // 50Hz PAL B/G
    case _LIB_TV_PAL_I     :    // 50Hz PAL I
    case _LIB_TV_PAL_DK    :    // 50Hz PAL D/K
    case _LIB_TV_SECAM_L   :    // 50Hz SECAM L
    case _LIB_TV_SECAM_LL  :    // 50Hz Secam L'
   		gmi_CI2CWriteVDCByte(0x06, 0x02);  
        break;

    case _LIB_TV_PAL_M     :    // 60Hz PAL M
    case _LIB_TV_PAL_N     :    // 50Hz PAL N
   		gmi_CI2CWriteVDCByte(0x06, 0x12); 
        break;
    } // end switch

    switch(ucTVColorMode)   // Sound
    {
    case _LIB_TV_PAL_M     :    // Sound 4.5M  PAL M
    case _LIB_TV_NTSC_M    :    // Sound 4.5M  NTSC M
    case _LIB_TV_PAL_N     :    // Sound 4.5M  PAL N 
        CSelectPalOrSecamL(0, ucMode, CarrierSelect);  
        CSetSIFFreq(0x03, ucMode);
        break;

    case _LIB_TV_NTSC_4_BG :    // Sound 5.5M  NTSC 4/BG
    case _LIB_TV_PAL_BG    :    // Sound 5.5M  PAL B/G
    case _LIB_TV_SECAM_BG  :    // Sound 5.5M  SECAM B/G
        CSelectPalOrSecamL(0, ucMode, CarrierSelect);
        CSetSIFFreq(0x00, ucMode);
        break;

    default:                // Normal sound
    case _LIB_TV_NTSC_4_I  :    // Sound 6.0M  NTSC 4/I
    case _LIB_TV_PAL_I     :    // Sound 6.0M  PAL I
        CSelectPalOrSecamL(0, ucMode, CarrierSelect);
        CSetSIFFreq(0x01, ucMode);
        break;

    case _LIB_TV_NTSC_4_DK :    // Sound 6.5M  NTSC 4/DK
    case _LIB_TV_PAL_DK    :    // Sound 6.5M  PAL D/K
    case _LIB_TV_SECAM_DK  :    // Sound 6.5M  SECAM D/K
        CSelectPalOrSecamL(0, ucMode, CarrierSelect);
        CSetSIFFreq(0x02, ucMode);
        break;

    case _LIB_TV_SECAM_L   :    // Sound 6.5M  SECAM L
    case _LIB_TV_SECAM_LL  :    // Sound 6.5M  Secam L'
        CSelectPalOrSecamL(1, ucMode, CarrierSelect);
        CSetSIFFreq(0x02, ucMode);
        break;
    }

    CSetPifFreq(ucMode, PifFreq);
}

//----------------------------------------------------------------
void gmi_ChangeInputToVGA(void)
{
    unsigned char uctemp[3];


    CI2cRead(_TB1334_VIDEODEVICE, 0x00, 3, uctemp);
    do
    {
        gmi_CDelay80Us();gmi_CDelay80Us();gmi_CDelay80Us();gmi_CDelay80Us();gmi_CDelay80Us();
        gmi_CDelay80Us();gmi_CDelay80Us();gmi_CDelay80Us();gmi_CDelay80Us();gmi_CDelay80Us();
        CI2cRead(_TB1334_VIDEODEVICE, 0x00, 3, uctemp);
    }while((uctemp[0] & 0x80));
                          
    for(uctemp[0] = 0x00; uctemp[0] < 0x23; uctemp[0]++)
    {
        gmi_CI2CWriteVDCByte(uctemp[0], tInitialVDCdata[uctemp[0]]);
        gmi_CDelay80Us();
    }
                            
    gmi_CDelay80Us();gmi_CDelay80Us();gmi_CDelay80Us();gmi_CDelay80Us();gmi_CDelay80Us();
    gmi_CDelay80Us();gmi_CDelay80Us();gmi_CDelay80Us();gmi_CDelay80Us();gmi_CDelay80Us();

	gmi_CI2CWriteVDCByte(0x06, 0x06);   
}

//----------------------------------------------------------------
void gmi_CAdjVDCSharpness(unsigned char ucSharpness)
{
    if (ucSharpness > 63)
        ucSharpness = 7;
    gmi_CI2CWriteVDCByte(0x03, ucSharpness);
}

void CNotUseFunc(void)
{
  //  gmi_CI2CWriteVDCByte(0x00, 0x00);
  //  gmi_CI2CReadVDCByte(0x00);
    gmi_CVideoCurrentColor(0);
  //  gmi_CInitialVDC();
    gmi_CSelectInputChannel(0x00,0);
    gmi_CAdjustVDCBrightness(50);
    gmi_CAdjustVDCContrast(50);
    gmi_CAdjustVDCSaturation(50);
    gmi_CAdjustVDCHue(50);
    gmi_CDelay80Us();
    gmi_CSetVDCFreeRunMode(_VDC_FREE_RUN_MODE_TO_AUTO);
    gmi_CSetIfMode(1, 1, 1, 1);
#if(_VIDEO_CHIP == _VDC_TW9908C)
    gmi_CRGBandYUVCtrl(50);
    gmi_CSetYUVHue(50);   // Set Sub-channel YUV mode Hue 
#endif
    gmi_CModeLocked();
    gmi_ChangeInputToVGA();
    gmi_CVDCOutputDisable();
    gmi_CAdjVDCSharpness(0x07);
}

#endif
