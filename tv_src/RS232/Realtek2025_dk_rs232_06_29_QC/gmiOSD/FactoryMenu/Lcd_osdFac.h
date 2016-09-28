#if(_FACTORY_MENU_EN)


#define FAC_RESET            0x81
#define FAC_BRIGHTNESS       0x89
#define FAC_CONTRAST         0x8a
#define FAC_BURIN_IN         0x8b
#define FAC_OSD_LANGUAGE      0x8c
#define FAC_POWER_SET      0x8d
#define FAC_LOGO_EN             0x8f
#define FAC_EMC             0x90
#define FAC_EXIT             0x91

#define FAC_ADC_OFFSET       149//0x82
#define FAC_OFFSET_R         150
#define FAC_OFFSET_G         151
#define FAC_OFFSET_B         152

#define FAC_ADC_GAIN         154//0x83
#define FAC_GAIN_R           155
#define FAC_GAIN_G           156
#define FAC_GAIN_B           157

#define FAC_9300K            159//149
#define FAC_9300_R           160
#define FAC_9300_G           161
#define FAC_9300_B           162

#define FAC_6500K            164//0x85
#define FAC_6500_R           165
#define FAC_6500_G           166
#define FAC_6500_B           167

#define FAC_USER             179//0x88
#define FAC_USER_R           180
#define FAC_USER_G           181
#define FAC_USER_B           182


#define OUTPUT_OFFSET_R()   OSDClear(FM_ROW_ADC_OFFSET, 1, FM_COL_R, 3 , 0x00, BYTE_DISPLAY); Gotoxy(FM_COL_R,FM_ROW_ADC_OFFSET,BYTE_DISPLAY);    \
                             CShowNumber(stAdcData.AdcOffset[_RED], 0)
#define OUTPUT_OFFSET_G()  OSDClear(FM_ROW_ADC_OFFSET, 1, FM_COL_G, 3 , 0x00, BYTE_DISPLAY);  Gotoxy(FM_COL_G,FM_ROW_ADC_OFFSET,BYTE_DISPLAY);    \
                             CShowNumber(stAdcData.AdcOffset[_GREEN], 0)
#define OUTPUT_OFFSET_B()   OSDClear(FM_ROW_ADC_OFFSET, 1, FM_COL_B, 3 , 0x00, BYTE_DISPLAY) ;Gotoxy(FM_COL_B,FM_ROW_ADC_OFFSET,BYTE_DISPLAY);    \
                             CShowNumber(stAdcData.AdcOffset[_BLUE], 0)

#define OUTPUT_GAIN_R()       OSDClear(FM_ROW_ADC_GAIN, 1, FM_COL_R, 3 , 0x00, BYTE_DISPLAY) ;Gotoxy(FM_COL_R,FM_ROW_ADC_GAIN,BYTE_DISPLAY);    \
                             CShowNumber(stAdcData.AdcGain[_RED], 0)
#define OUTPUT_GAIN_G()       OSDClear(FM_ROW_ADC_GAIN, 1, FM_COL_G, 3 , 0x00, BYTE_DISPLAY) ;Gotoxy(FM_COL_G,FM_ROW_ADC_GAIN,BYTE_DISPLAY);    \
                             CShowNumber(stAdcData.AdcGain[_GREEN], 0)
#define OUTPUT_GAIN_B()       OSDClear(FM_ROW_ADC_GAIN, 1, FM_COL_B, 3 , 0x00, BYTE_DISPLAY) ;Gotoxy(FM_COL_B,FM_ROW_ADC_GAIN,BYTE_DISPLAY);    \
                             CShowNumber(stAdcData.AdcGain[_BLUE], 0)

#define OUTPUT_9300_R()       OSDClear(FM_ROW_9300K, 1, FM_COL_R, 3 , 0x00, BYTE_DISPLAY) ;Gotoxy(FM_COL_R,FM_ROW_9300K,BYTE_DISPLAY);    \
                             CShowNumber(stColorTempData.ColorTemp[_RED], 0)
#define OUTPUT_9300_G()       OSDClear(FM_ROW_9300K, 1, FM_COL_G, 3 , 0x00, BYTE_DISPLAY) ;Gotoxy(FM_COL_G,FM_ROW_9300K,BYTE_DISPLAY);    \
                             CShowNumber(stColorTempData.ColorTemp[_GREEN], 0)
#define OUTPUT_9300_B()       OSDClear(FM_ROW_9300K, 1, FM_COL_B, 3 , 0x00, BYTE_DISPLAY) ;Gotoxy(FM_COL_B,FM_ROW_9300K,BYTE_DISPLAY);    \
                             CShowNumber(stColorTempData.ColorTemp[_BLUE], 0)

#define OUTPUT_6500_R()       OSDClear(FM_ROW_6500K, 1, FM_COL_R, 3 , 0x00, BYTE_DISPLAY) ;Gotoxy(FM_COL_R,FM_ROW_6500K,BYTE_DISPLAY);    \
                             CShowNumber(stColorTempData.ColorTemp[_RED], 0)
#define OUTPUT_6500_G()       OSDClear(FM_ROW_6500K, 1, FM_COL_G, 3 , 0x00, BYTE_DISPLAY) ;Gotoxy(FM_COL_G,FM_ROW_6500K,BYTE_DISPLAY);    \
                             CShowNumber(stColorTempData.ColorTemp[_GREEN], 0)
#define OUTPUT_6500_B()       OSDClear(FM_ROW_6500K, 1, FM_COL_B, 3 , 0x00, BYTE_DISPLAY) ;Gotoxy(FM_COL_B,FM_ROW_6500K,BYTE_DISPLAY);    \
                             CShowNumber(stColorTempData.ColorTemp[_BLUE], 0)

#define OUTPUT_USER_R()       OSDClear(FM_ROW_USER, 1, FM_COL_R, 3 , 0x00, BYTE_DISPLAY) ;Gotoxy(FM_COL_R,FM_ROW_USER,BYTE_DISPLAY);    \
                             CShowNumber(stColorTempData.ColorTemp[_RED], 0)
#define OUTPUT_USER_G()       OSDClear(FM_ROW_USER, 1, FM_COL_G, 3 , 0x00, BYTE_DISPLAY) ;Gotoxy(FM_COL_G,FM_ROW_USER,BYTE_DISPLAY);    \
                             CShowNumber(stColorTempData.ColorTemp[_GREEN], 0)
#define OUTPUT_USER_B()       OSDClear(FM_ROW_USER, 1, FM_COL_B, 3 , 0x00, BYTE_DISPLAY) ;Gotoxy(FM_COL_B,FM_ROW_USER,BYTE_DISPLAY);    \
                             CShowNumber(stColorTempData.ColorTemp[_BLUE], 0)

#define OUTPUT_BIRGHT()       OSDClear(FM_ROW_BRIGHTNESS, 1, FM_COL_R+1, 3 , 0x00, BYTE_DISPLAY) ;Gotoxy(FM_COL_R+1,FM_ROW_BRIGHTNESS,BYTE_DISPLAY);    \
                             CShowNumber(stConBriData.Brightness, 0)
#define OUTPUT_CONTRAST()     OSDClear(FM_ROW_CONTRAST, 1, FM_COL_R+1, 3 , 0x00, BYTE_DISPLAY) ;Gotoxy(FM_COL_R+1,FM_ROW_CONTRAST,BYTE_DISPLAY);    \
                             CShowNumber(stConBriData.Contrast, 0)

#define SUBITEM_STATE1(x,y,len)     OSDLine(y, x, len, 0x71, BYTE_COLOR)
#define SUBITEM_STATE2(x,y,len)     OSDLine(y, x, len, 0x74, BYTE_COLOR)
#define CLR_SUBITEM(x,y,len)        OSDLine(y, x, len, 0x7b, BYTE_COLOR)


// Row
#define FM_ROW_AUTO_COLOR_LINE          0
#define FM_ROW_RESET                    1
#define FM_ROW_ADC_OFFSET               2
#define FM_ROW_ADC_GAIN                 3
#define FM_ROW_9300K                    4
#define FM_ROW_6500K                    5
#define FM_ROW_USER                     6
#define FM_ROW_BRIGHTNESS               7
#define FM_ROW_CONTRAST                 8
#define FM_ROW_BURIN_IN                 9
#define FM_ROW_OSD_LANGUAGE              10
#define FM_ROW_POWER_SET              11
#define FM_ROW_LOGO_EN                     12
#define FM_ROW_EMC                     13
#define FM_ROW_EXIT                     14

// Col
#define FM_COL_R                    13
#define FM_COL_G                    FM_COL_R+4
#define FM_COL_B                    FM_COL_G+4
//#define FM_COL_RETURN               32

#define FM_STATE_CLR                0
#define FM_STATE_SELECT             1
#define FM_STATE_ADJUST             2

#define _DEC								0
#define _INC								1


#define FAC_ROW_COUNT    FM_ROW_EXIT+1
#define FAC_COL_WIDTH    29

#ifdef __FAC_LCD_OSD__


void COsdFacHandler();
void EnterFactoryMenu();

void FMMainProc();
void FMMainMenu(BYTE ucMode);
void FMMainLR(BYTE LR);

void FMColorProc();
void FMColorLR(BYTE LR);

void FMColorAdjLR(BYTE LR);

void FMBrightAdjProc();
void FMBrightAdjMenu();
void FMBrightAdjLR(BYTE LR);

void FMContrastAdjProc();
void FMContrastAdjMenu();
void FMContrastAdjLR(BYTE LR);

void FMBurnInAdjProc();
void FMBurnInAdjMenu();
void FMBurnInAdjLR();

void FMOutputBurnInState();
void FMOutputAllData();
void FMItemState(BYTE state);     // 1 : select state
void FMColorState(BYTE y,BYTE Def_R,BYTE state);
void FMLoadColorTmp();
#else

extern void COsdFacHandler();
extern void EnterFactoryMenu();

#endif  //#ifdef __FAC_LCD_OSD__

#endif  //#if(FACTORY_MENU_EN)
