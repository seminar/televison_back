#define __LOGOC__

#include "Header\Include.h"

#if(_LOGO_EN) 

#if(_LOGO_TYPE == _LOGO_TYPE0)
/*
//-------------------------------------------
void COsdFxChange2bitColor(BYTE row_start, BYTE height, BYTE col_start, BYTE width, BYTE ucColor0, BYTE ucColor1, BYTE ucColor2, BYTE ucColor3)
{    
    BYTE  temp; 
    temp = 0xa0 | ((ucColor3 & 0x07) << 1) | ((ucColor0 & 0x04) >> 2)|((ucColor3 & 0x08) <<3)|((ucColor1 & 0x08) << 1);   
    OSDClear(row_start, height, col_start, width, temp, THE_BYTE0);   
    temp = ((ucColor0 & 0x03) << 6) | ((ucColor2 & 0x07) << 3) | (ucColor1 & 0x07);   
    OSDClear(row_start, height, col_start, width, temp, THE_BYTE2);
}
*/
	//-------------------------------------------
	void DrawLogo()
       {     
	BYTE i,j,n;              
	CAdjustColorPalette(tLogoPALETTE);  
       CAdjustBackgroundColor(LOGO_BackgroundColor_Red, LOGO_BackgroundColor_Green, LOGO_BackgroundColor_Blue);
     
#if(_LOGO_BIT_SET==_LOGO_2_BIT)
     //Draw
     SetOSDRamAddress(_LOGO_HEIGHT,
                      _LOGO_WIDTH,
                      _LOGO_HEIGHT*2 * _LOGO_WIDTH*2 + _LOGO_HEIGHT*2 + 1);
     CScalerLoadFont(ucFntLogo,0x00,_LOGO_HEIGHT*2 * _LOGO_WIDTH*2,_COMPRESS_FONT);
     SetRowCmds(_LOGO_HEIGHT,_LOGO_WIDTH);
     COsdFxCodeWrite(ucCloseAllWindow);

    // Init osd
    // insert code to here
	OSDClear(ROW(0), HEIGHT(_LOGO_HEIGHT*2), COL(0), WIDTH(_LOGO_WIDTH*2),(((_LOGO_COLOR0&0x07)<<1)|((_LOGO_COLOR1&_BIT2)>>2)|0xA0), BYTE_ATTRIB);
	//OSDClear(ROW(0), HEIGHT(_LOGO_HEIGHT*2), COL(0), WIDTH(_LOGO_WIDTH*2), 0x00, BYTE_DISPLAY);
	OSDClear(ROW(0), HEIGHT(_LOGO_HEIGHT*2), COL(0), WIDTH(_LOGO_WIDTH*2), (((_LOGO_COLOR1&0x03)<<6)|((_LOGO_COLOR2&0x07)<<3)|(_LOGO_COLOR3&0x07)), BYTE_COLOR);
#else
     //Draw
     SetOSDRamAddress(_LOGO_HEIGHT,
                      _LOGO_WIDTH,
                      _LOGO_HEIGHT * _LOGO_WIDTH + _LOGO_HEIGHT + 1);
     CScalerLoadFont(ucFntLogo,0x00,_LOGO_HEIGHT * _LOGO_WIDTH,_COMPRESS_FONT);
     SetRowCmds(_LOGO_HEIGHT,_LOGO_WIDTH);
     COsdFxCodeWrite(ucCloseAllWindow);

    // Init osd
    // insert code to here
	OSDClear(ROW(0), HEIGHT(_LOGO_HEIGHT), COL(0), WIDTH(_LOGO_WIDTH), 0x8C, BYTE_ATTRIB);
	//OSDClear(ROW(0), HEIGHT(_LOGO_HEIGHT), COL(0), WIDTH(_LOGO_WIDTH), 0x00, BYTE_DISPLAY);
	OSDClear(ROW(0), HEIGHT(_LOGO_HEIGHT), COL(0), WIDTH(_LOGO_WIDTH), (((_LOGO_COLOR2&0x0f)<<4)|(_LOGO_COLOR3&0x0f)), BYTE_COLOR);
#endif
     

     n = 0;
     for(i=0;i<_LOGO_HEIGHT;i++)
     {
         Gotoxy(0,i,BYTE_DISPLAY);
         CScalerSendAddr(_OSD_DATA_PORT_92, _WRITE, _NON_AUTOINC);
         for(j=0;j<_LOGO_WIDTH;j++)
         {
             CScalerSendByte(n);
             n++;
         }
         CScalerSendWriteStop();
     }
     OSDPosition(_LOGO_WIDTH  ,_LOGO_HEIGHT ,_LOGO_H_OFFSET,_LOGO_V_OFFSET,0x01);
#if(_LOGO_DOUBLE_OSD)
     SetOSDDouble(OSD_DOUBLE_HEIGHT_ENABLE | OSD_DOUBLE_WIDTH_ENABLE);
#else
     SetOSDDouble(0x0c);
#endif
     COsdFxEnableOsd();
     CPowerPanelOn();
     CPowerLightPowerOn();
	for(i=0;i<=LOGO_TIMER_DELAY;i++)
     CTimerDelayXms(250);
      COsdFxDisableOsd();
     CAdjustColorPalette(tPALETTE_0);
}
//-------------------------------------------

#else

void OSDPosition1(WORD usOsdActWidth, WORD usOsdActHeight, BYTE ucHPos, BYTE ucVPos, BYTE ucPar)
{
    if(ucHPos > 100)
        ucHPos = 50;

    if(ucVPos > 100)
        ucVPos = 50;

    usOsdActWidth  = 3 + ((DWORD)(ucHPos)*((CCalcPanelDHEnd() - Panel.DHStartPos)/4 -usOsdActWidth/4 - 4)) / 100;
    usOsdActHeight = 2 + ((DWORD)(ucVPos)*((CCalcPanelDVEnd() - Panel.DVStartPos)/4 - usOsdActHeight/4 - 6)) / 100;

    CScalerSetBit(_OSD_SCRAMBLE_93, 0xf8, 0x02);

    pData[0] = CScalerGetBit(_OVERLAY_CTRL_6C, _BIT0);

    pData[0] = (pData[0] == 0x00) ? 0xc0 : 0xe0;
    pData[1] = 0x00;
    CScalerWrite(_OSD_ADDR_MSB_90, 2, pData, _AUTOINC);

    pData[0] = usOsdActHeight >> 1;
    pData[1] = (BYTE)(usOsdActWidth >> 2);
    pData[2] = ((BYTE)(usOsdActWidth & 0x0003) << 6) | ((usOsdActHeight & 0x01) << 5) | ucPar;
    CScalerWrite(_OSD_DATA_PORT_92, 3, pData, _NON_AUTOINC);
 
    CTimerWaitForEvent(_EVENT_DEN_STOP);
    CTimerWaitForEvent(_EVENT_DEN_STOP);
    CScalerSetBit(_OSD_SCRAMBLE_93, 0xf8, 0x05);
}

WORD xdata iXpos       = 40;
BYTE xdata ucCount     = 0;
BYTE xdata ucLogoColor = 0x01;


void CLogoGo(void)
{
    // Time delay
    ucCount++;
    if (ucCount < 150)
        return;
    
    if (0 == bLogoOnScreen)
    {
        BYTE ucTemp;

        COsdFxDisableOsd();
        COsdFxCodeWrite(ucCloseAllWindow);
        SetOSDRamAddress(_LOGO_HEIGHT, _LOGO_WIDTH, FONT_BASE_ADDRESS);
        SetRowCmds(_LOGO_HEIGHT, _LOGO_WIDTH);
        CClearWindow(0x40);  // Clear window and set character color to black
        OSDPosition1(200, 1, 0, 46, 0x03);
        SetOSDDouble(OSD_DOUBLE_HEIGHT_ENABLE | OSD_DOUBLE_WIDTH_ENABLE);
        DirectWOSDRam(0x01, 0x01, THE_BYTE0, 0x80|0x03);  // Row 0 character double height and width
        OSDClear(1, 1, 0, 50, 0x00, BYTE_DISPLAY);
        OSDLine(1, 1, 50, 0x00|(ucLogoColor<<4), BYTE_COLOR);
        // Draw window
        COsdFxDrawWindow(XSTART(0), YSTART(8),  XEND(_DISP_WID), YEND(8+40), tOSD_LOGO1_WINDOW_STYLE);

        pData[0] = 0x40;
        pData[1] = 0x03;
        pData[2] = 0x0f | 0xa0;
        CScalerWrite(_OSD_ADDR_MSB_90,3,pData,_AUTOINC);

        CScalerRead(_OVERLAY_CTRL_6C, 1, &ucTemp, _NON_AUTOINC);
        ucTemp = (ucTemp & 0xe3) | (6 << 2);
        CScalerSetByte(_OVERLAY_CTRL_6C, ucTemp);

        CLeftAlignTextout((BYTE *)sLogo1, iXpos, 1);
        bLogoOnScreen = 1;
        CTimerCancelTimerEvent(COsdDispOsdTimerEvent);
        COsdFxEnableOsd();
        return;
    }     
                      
  
    // Clear display
    OSDLine(1, 0, 50, 0x00, BYTE_DISPLAY);
    ucCount = 0;

    if (iXpos == 0)  
    {
        iXpos = 40;
        // Change color
        if(ucLogoColor == 0x0f)
           ucLogoColor = 0x01;
        ucLogoColor++;
    }

    // Set color
    OSDLine(1, 0, 50, 0x00|(ucLogoColor<<4), BYTE_COLOR);

    iXpos--;

    CLeftAlignTextout((BYTE *)sLogo1, iXpos, 1);
}

#endif // #if(_LOGO_TYPE == _LOGO_TYPE0)
#endif // #if(_LOGO_EN) 
