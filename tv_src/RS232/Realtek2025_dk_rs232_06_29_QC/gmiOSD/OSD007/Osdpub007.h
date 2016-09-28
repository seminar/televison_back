#if(_OSD_TYPE == _OSD007)

#define _BACKLIGHT_MAX                  255
#define _BACKLIGHT_MIN                  0

#if(_VGA_COLOR_SUPPORT)
//--------------------------------------------------
// Definitions of Vivid Color
//--------------------------------------------------
#define _MZ_ICM_RED_HUE_MAX             16
#define _MZ_ICM_RED_HUE_MIN             0
#define _MZ_ICM_RED_SAT_MAX             16
#define _MZ_ICM_RED_SAT_MIN             0
#define _MZ_ICM_GREEN_HUE_MAX           16
#define _MZ_ICM_GREEN_HUE_MIN           0
#define _MZ_ICM_GREEN_SAT_MAX           16
#define _MZ_ICM_GREEN_SAT_MIN           0
#define _MZ_ICM_BLUE_HUE_MAX            16
#define _MZ_ICM_BLUE_HUE_MIN            0
#define _MZ_ICM_BLUE_SAT_MAX            16
#define _MZ_ICM_BLUE_SAT_MIN            0
#define _MZ_ICM_YELLOW_HUE_MAX          16
#define _MZ_ICM_YELLOW_HUE_MIN          0
#define _MZ_ICM_YELLOW_SAT_MAX          16
#define _MZ_ICM_YELLOW_SAT_MIN          0
#define _MZ_ICM_CYAN_HUE_MAX            16
#define _MZ_ICM_CYAN_HUE_MIN            0
#define _MZ_ICM_CYAN_SAT_MAX            16
#define _MZ_ICM_CYAN_SAT_MIN            0
#define _MZ_ICM_MAGENTA_HUE_MAX         16
#define _MZ_ICM_MAGENTA_HUE_MIN         0
#define _MZ_ICM_MAGENTA_SAT_MAX         16
#define _MZ_ICM_MAGENTA_SAT_MIN         0

#define _MZ_COLOR_BRIGHTNESS_MAX        255
#define _MZ_COLOR_BRIGHTNESS_MIN        0
#define _MZ_COLOR_CONTRAST_MAX          255
#define _MZ_COLOR_CONTRAST_MIN          0
#define _MZ_COLOR_PEAKING_MAX          	126
#define _MZ_COLOR_PEAKING_MIN          	0

#define _MZ_WINDOW_CFG_DISABLE          0
#define _MZ_WINDOW_CFG_FULL             1
#define _MZ_WINDOW_CFG_DEMO             2
#define _MZ_WINDOW_CFG_WINDOW           3
#endif


//----------------------------------------
//   Definition for osd slider
//----------------------------------------
#define _NOT_SHOW_PERCENT               0
#define _SHOW_PERCENT                   1


//----------------------------------------
//   Definition for use window
//----------------------------------------
#define _MAIN_WINDOW                    0
#define _LINE_WINDOW                    1
#define _SELECT_MAIN_WINDOW             2
#define _SELECT_SUB_WINDOW              3

#define _MOVE_STATE                     WT_3DBUTTON_TYPE1
#define _SELECT_STATE                   WT_3DBUTTON_TYPE2
// Main window
#define _MAIN_WINDOW_H_POS              8
#define _MAIN_WINDOW_V_POS              6
#define _MAIN_WINDOW_WIDTH              352
#define _MAIN_WINDOW_HEIGHT             326
// Line window
#define _LINE_WINDOW_H_POS              _MAIN_WINDOW_H_POS
#define _LINE_WINDOW_V_POS              63
#define _LINE_WINDOW_WIDTH              _MAIN_WINDOW_WIDTH
#define _LINE_WINDOW_HEIGHT             4
// Hint window
#define _HINT_WINDOW_H_POS              8
#define _HINT_WINDOW_V_POS              4
#define _HINT_WINDOW_H_END              262
#define _HINT_WINDOW_V_END              80
// Main Window double
#define _MAIN_OSD_DOUBLE_WIDTH          1018
#define _MAIN_OSD_DOUBLE_HEIGHT         836
// Volume window
#define _VOLUME_WINDOW_H_POS            8
#define _VOLUME_WINDOW_V_POS            14
#define _VOLUME_WINDOW_WIDTH            262
#define _VOLUME_WINDOW_HEIGHT           74
// Volume window double
#define _VOLUME_OSD_DOUBLE_WIDTH        918
#define _VOLUME_OSD_DOUBLE_HEIGHT       576
// Vivid Color window
#define _VCOLOR_WINDOW_H_POS            8
#define _VCOLOR_WINDOW_V_POS            0
#define _VCOLOR_WINDOW_WIDTH            (_VCOLOR_WINDOW_H_POS + 170)
#define _VCOLOR_WINDOW_HEIGHT           (_VCOLOR_WINDOW_V_POS + 270)
// Vivid Color window double
#define _VCOLOR_OSD_DOUBLE_WIDTH        918
#define _VCOLOR_OSD_DOUBLE_HEIGHT       576


//----------------------------------------
//   Definition for clear sub msg
//----------------------------------------
#define _CLEAR_MSG_ONLY                 0
#define _CLEAR_AND_SELECT_SUB_ITEM      1
#define _CLEAR_AND_EXIT_SUB_ITEM        2

//----------------------------------------
//     4Bit icon address define
//----------------------------------------
#define _4BIT_ICON_SIZE                 0x06
#define _4BIT_ICON_COLOR_ADDR           0x38
#define _4BIT_ICON_TV_FUNC_ADDR         (_4BIT_ICON_COLOR_ADDR+_4BIT_ICON_SIZE)
#define _4BIT_ICON_PEAKING_POS          4

//----------------------------------------
//     Definition for color temp processor
//----------------------------------------
#define _COLOR_TEMP                  _DISABLE        // _ENABLE,  _DISABLE


//----------------------------------------
//     Definition for OSD adj 
//----------------------------------------
// For OSD position
#define _OSD_POSITION_ADJ_CTRL       _OFF            // _ON, _OFF
// For OSD timeout
#define _OSD_TIMEOUT_ADJ_CTRL        _OFF            // _ON, _OFF
// For Alpha blending level
#define _ALPHA_BLENDING_ADJ          _OFF            // _ON, _OFF
// For OSD display size
#define _OSD_DISPLAY_SIZE_ADJ        _ON// _ON, _OFF

#define _DISPLAY_SIZE_ADJ        _ON// _ON, _OFF

//----------------------------------------
//     Definition for image color mode
//----------------------------------------
#define _IMAGE_COLOR_MODE            _ON           // _ON, _OFF

//----------------------------------------
//     Definition for image color mode
//----------------------------------------
#define _SHARPNESS_ADJ               _OFF// _ON, _OFF

//----------------------------------------
//     Definition for blue background function
//----------------------------------------
#define _BLUE_BACKGROUND_FUNC        _ENABLE        // _ENABLE,  _DISABLE

//----------------------------------------
//     Definition for OSD shadow
//----------------------------------------
#define _OSD_SHADOW_FUNC             _DISABLE       // _ENABLE,  _DISABLE

//----------------------------------------
//     Definition for message show position
//----------------------------------------
#define _MESSAGE_V_POSITION          14

//----------------------------------------
//     Definition for key message
//----------------------------------------
#define _USE_UD_LR_KEY_MSG           _ENABLE        // _ENABLE,  _DISABLE

//----------------------------------------
//     Definition for OSD english letterform
//----------------------------------------
#define FONT_COMIC_SANS_MS_12        0
#define FONT_REALTEK                 1

#define ENGLISH_FONT                 FONT_REALTEK

//----------------------------------------
//     Definition for show tv search freq
//----------------------------------------
#define _TV_SEARCH_SHOW_SLIDER       0
#define _TV_SEARCH_SHOW_FREQ         1

#define _TV_SEARCH_SHOW_TYPE         _TV_SEARCH_SHOW_FREQ

//----------------------------------------
//     Definition for menu key
//----------------------------------------
#define _MENU_NORMAL                 0
#define _MENU_EXIT_ITEM              1

#define _MENU_FUNC                   _MENU_EXIT_ITEM

//----------------------------------------
//     Definition for change source store
//     auto power down time
//----------------------------------------
#define _CHANGE_SOURCE_STORE_A_P_T   _ENABLE        // _ENABLE,  _DISABLE

//----------------------------------------
// For TV input channel timeout
//----------------------------------------
#define _INPUT_CH_TIMEOUT_COUNT      800

#define _FIRST_ITEM                  0

//---- language type define--------------
#define ENGLISH                     0
#define LNG_DEU                     1
#define LNG_RUSS	2
#define LNG_FRA                    3
#define LNG_ITA        4
#define LNG_SPA        5
#define LNG_CHI_S      6
#define LNG_CHI_T      7
#define LNG_PORT                   8
#define LNG_KOREAN     9
#define LNG_ARABIC		10		//add the Arabic Language

//---- menu define ----------------------
#define _MENU_NONE                  0

#define MENU_MAIN_COLOR             1
#define MENU_MAIN_PICTURE           2       // VGA use
#define MENU_MAIN_TV_FUNC           3
#define MENU_MAIN_OSD_FUNC          4
#define MENU_MAIN_SOUND             5
#define MENU_MAIN_OTHER             6
#define MENU_MAIN_EXIT              7

//-------------- Color page -------------
// Sub item
#define MENU_ITEM_BRIGHT            10 
#define MENU_ITEM_CONTRAST          11 
#define MENU_ITEM_COLOR_TEMP        12 
#define MENU_AV_SATURATION          13
#define MENU_AV_HUE                 14
#define MENU_SUB_COLOR_CLOSE        15 
// Adjust item
#define MENU_SUB_BRIGH_ADJ          16
#define MENU_SUB_CONTRAST_ADJ       17
#define MENU_AV_SATURATION_ADJ      18
#define MENU_AV_HUE_ADJ             19

//----------- Color temp page -----------
#define MENU_SUB_CT_9300            20 
#define MENU_SUB_CT_6500            21

#define MENU_SUB_CT_5800            24 
#define MENU_SUB_CT_SRGB            25 

#define MENU_SUB_CT_USER            22
#define MENU_SUB_CT_CLOSE           23 
#define MENU_SUB_CT_R               26 
#define MENU_SUB_CT_G               27 
#define MENU_SUB_CT_B               28 

//----- Color temp user R/G/B adjust ----
#define MENU_SUB_CT_R_ADJ           29
#define MENU_SUB_CT_G_ADJ           30
#define MENU_SUB_CT_B_ADJ           31


//------------- Picture page ------------
#define MENU_ITEM_AUTO              32 
#define MENU_ITEM_AUTO_COLOR        33
#define MENU_ITEM_HPOS              34 
#define MENU_ITEM_VPOS              35 
#define MENU_ITEM_PHASE             36 
#define MENU_ITEM_CLOCK             37 
#define MENU_SUB_PICTURE_CLOSE      38 
//------------- Picture adj -------------
#define MENU_SUB_PHASE_ADJ          39
#define MENU_SUB_CLOCK_ADJ          40
#define MENU_SUB_HPOS_ADJ           41
#define MENU_SUB_VPOS_ADJ           42


//-------------- Sound page -------------
#define MENU_SUB_VOLUME             43 
#define MENU_SUB_MUTE               44 
#define MENU_SUB_BALANCE            45 
#define MENU_SUB_BASS               46 
#define MENU_SUB_TREBLE             47 
#define MENU_SUB_SRS                48 
#define MENU_SUB_BBE                49 
#define MENU_SUB_SOUND_CLOSE        50 
//-------------- Sound adj --------------
#define MENU_SUB_VOL_ADJ            51
#define MENU_SUB_MUTE_ADJ           52
#define MENU_SUB_BALANCE_ADJ        53
#define MENU_SUB_BASS_ADJ           54
#define MENU_SUB_TREBLE_ADJ         55
#define MENU_SUB_SRS_ADJ            56
#define MENU_SUB_BBE_ADJ            57


//----------- OSD function --------------
#define MENU_SUB_LANGUAGE           58 
#define MENU_SUB_H_POSITION         59 
#define MENU_SUB_V_POSITION         60 
#define MENU_SUB_OSD_TIMEOUT        61 
#define MENU_SUB_OSD_TRANSLUCENT    62
#define MENU_SUB_OSD_SIZE           63      
#define MENU_SUB_DISMODE			64     
#define MENU_SUB_OSD_CLOSE          65
//-------------- OSD adj ----------------
#define MENU_SUB_OSDLANGUAGE_ADJ    66
#define MENU_SUB_OSDH_POSITION_ADJ  67
#define MENU_SUB_OSDV_POSITION_ADJ  68
#define MENU_SUB_OSD_TIMEOUT_ADJ    69
#define MENU_SUB_OSD_TRANS_ADJ      70
#define MENU_SUB_DISPMODE_ADJ		71
#define MENU_SUB_OSD_SIZE_ADJ      72 

//--------------- Other -----------------
#define MENU_SUB_RESET              75
#define MENU_SUB_BLUE               76
#define MENU_SUB_AUTO_POWER         77
#define MENU_SUB_COLOR_MODE         78 
#define MENU_SUB_SHARP              79
#define MENU_SUB_OTHER_CLOSE        80 
//------------- Other adj ---------------
#define MENU_BLUE_ADJ               81
#define MENU_AUTO_POWER_DOWN_ADJ    82
#define MENU_COLOR_MODE_ADJ         83
#define MENU_SHARP_ADJ              84



//----------- TV function --------------

#define MENU_AUTO_SEARCH            90
#define MENU_MANUAL_SEARCH          91
#define MENU_TUNING                 92
#define MENU_CHANNEL                93
#define MENU_TV_SYSTEM              94
//#define MENU_SOUND_SYSTEM           79
#define MENU_SWAP                   95
#define MENU_SKIP                   96
#define MENU_SUB_TV_FUNC_CLOSE      97
//--------- TV function adj ------------
#define MENU_AUTO_SEARCH_ADJ      98
#define MENU_MANUAL_SEARCH_ADJ      99
#define MENU_TUNING_ADJ             100
#define MENU_CHANNEL_ADJ            101
#define MENU_TV_SYSTEM_ADJ          102
#define MENU_SOUND_SYSTEM_ADJ      103
#define MENU_SWAP_ADJ              104
#define MENU_SKIP_ADJ               105


#if(_VGA_COLOR_SUPPORT == _ON)
//   DCC item
#define MENU_SAC_DCC_TEXT           97
#define MENU_SAC_DCC_MOVIE          98
#define MENU_SAC_DCC_GRAPHIC        99
#define MENU_SAC_DCC_GAME           100
#define MENU_SAC_DCC_NORMAL         101
#define MENU_SAC_DCC_USER           102
#define MENU_SAC_DCC_CLOSE          103

//   User item
#define MENU_USER_ITEM_DCC          104
#define MENU_USER_ITEM_ICM          105
#define MENU_USER_ITEM_COLOR        106
#define MENU_USER_ITEM_CLOSE        107

//   DCC item
#define MENU_DCC_ITEM_TEXT          109
#define MENU_DCC_ITEM_MOVIE         110
#define MENU_DCC_ITEM_GRAPHIC       111
#define MENU_DCC_ITEM_GAME          112
#define MENU_DCC_ITEM_NORMAL        113

//   ICM item
#define MENU_ICM_ITEM_RED           115
#define MENU_ICM_ITEM_GREEN         116
#define MENU_ICM_ITEM_BLUE          117
#define MENU_ICM_ITEM_YELLOW        118
#define MENU_ICM_ITEM_CYAN          119
#define MENU_ICM_ITEM_MAGENTA       120
#define MENU_ICM_ITEM_ON_OFF        121
#define MENU_ICM_ITEM_CLOSE         122

//   ICM sub item
#define MENU_ICM_SUB_R_HUE          130
#define MENU_ICM_SUB_R_SAT          131
#define MENU_ICM_SUB_R_CLOSE        132
#define MENU_ICM_SUB_G_HUE          133
#define MENU_ICM_SUB_G_SAT          134
#define MENU_ICM_SUB_G_CLOSE        135
#define MENU_ICM_SUB_B_HUE          136
#define MENU_ICM_SUB_B_SAT          137
#define MENU_ICM_SUB_B_CLOSE        138
#define MENU_ICM_SUB_Y_HUE          139
#define MENU_ICM_SUB_Y_SAT          140
#define MENU_ICM_SUB_Y_CLOSE        141
#define MENU_ICM_SUB_C_HUE          142
#define MENU_ICM_SUB_C_SAT          143
#define MENU_ICM_SUB_C_CLOSE        144
#define MENU_ICM_SUB_M_HUE          145
#define MENU_ICM_SUB_M_SAT          146
#define MENU_ICM_SUB_M_CLOSE        147

//   ICM R/G/B/Y/C/M adj item
#define MENU_ICM_R_HUE_ADJ          150
#define MENU_ICM_R_SAT_ADJ          151
#define MENU_ICM_G_HUE_ADJ          152
#define MENU_ICM_G_SAT_ADJ          153
#define MENU_ICM_B_HUE_ADJ          154
#define MENU_ICM_B_SAT_ADJ          155
#define MENU_ICM_Y_HUE_ADJ          156
#define MENU_ICM_Y_SAT_ADJ          157
#define MENU_ICM_C_HUE_ADJ          158
#define MENU_ICM_C_SAT_ADJ          159
#define MENU_ICM_M_HUE_ADJ          160
#define MENU_ICM_M_SAT_ADJ          161

//   Color item
#define MENU_COLOR_ITEM_BRIGHTNESS  164
#define MENU_COLOR_ITEM_CONTRAST    165
#define MENU_COLOR_ITEM_PEAKING     166
#define MENU_COLOR_ITEM_CLOSE       167

//   Color item adj
#define MENU_COLOR_ITEM_BRIGHT_ADJ  168
#define MENU_COLOR_ITEM_CON_ADJ     169
#define MENU_COLOR_ITEM_PEAK_ADJ    170

#endif


#define MENU_IMAGE_ADJ              180
#define SLEEP_TIME_ADJ              181

#if(1)//_VIDEO_TV_SUPPORT)
#define MENU_SHOW_MESSAGE_SATAE     200
#endif

#define ITEM_SHORTCUT_INPUTCH_NUM   201
#define MENU_VOLUME_SP              202
#define MENU_SHOW_MUTE_STATE        203
#define MENU_SHOW_MSG_STATE         204
#define MENU_CHANEL_SP              		205

#define SLIDER1(value)       OSDSlider(_MESSAGE_V_POSITION, 6, 10, value, 100, 0x40, _SHOW_PERCENT)
#define SLIDER2(value)       OSDSlider(_MESSAGE_V_POSITION, 6, 10, value, 255, 0x40, _SHOW_PERCENT)

#define BRIGHTNESS_GUAGE     stConBriData.Brightness// * 100 / 255
#define CONTRAST_GUAGE       stConBriData.Contrast// * 100 / 255  

#define HUE_GUAGE            stConBriData.Hue
#define SATURATION_GUAGE     stConBriData.Saturation



#define VK_MENU            _MENU_KEY_MESSAGE
#define VK_LEFT            _RIGHT_KEY_MESSAGE
#define VK_RIGHT           _LEFT_KEY_MESSAGE
#define VK_SOURCE          _EXIT_KEY_MESSAGE
//#define VK_EXIT          _EXIT_KEY_MESSAGE

//#define VK_SOURCE          _SOURCE_KEY_MESSAGE
#define VK_AUTO          _AUTO_KEY_MESSAGE
#define VK_ENTER           _IR_MENU_KEY_MESSAGE
#define VK_FAC                   _FAC_KEY_MESSAGE

#if(_USE_UD_LR_KEY_MSG)
#define VK_F_UP            _IR_UP_KEY_MESSAGE
#define VK_F_DOWN          _IR_DOWN_KEY_MESSAGE
#define VK_F_LEFT          _IR_LEFT_KEY_MESSAGE
#define VK_F_RIGHT         _IR_RIGHT_KEY_MESSAGE
#endif

#define VK_IR_OK              _IR_OK_KEY_MESSAGE
#define VK_IR_EXIT           _IR_EXIT_KEY_MESSAGE
#define VK_IR_VOLINC       _IR_VOLINC_KEY_MESSAGE
#define VK_IR_VOLDEC       _IR_VOLDEC_KEY_MESSAGE
#define VK_IR_CHINC        _IR_CHINC_KEY_MESSAGE
#define VK_IR_CHDEC        _IR_CHDEC_KEY_MESSAGE
#define VK_IR_MUTE         _IR_MUTE_KEY_MESSAGE
#define VK_IR_RETURN       _IR_RETURN_KEY_MESSAGE
#define VK_IR_DISPLAY      _IR_DISPLAY_KEY_MESSAGE
#define VK_IR_INPUTCH      _IR_INPUTCH_KEY_MESSAGE
#define VK_IR_TV                _IR_TVTYPE_KEY_MESSAGE
#define VK_IR_VGA             _IR_VGATYPE_KEY_MESSAGE
#define VK_IR_AV               _IR_AVTYPE_KEY_MESSAGE
#define VK_IR_SV            _IR_SVTYPE_KEY_MESSAGE
#define VK_IR_SCART          _IR_SCARTTYPE_KEY_MESSAGE
#define VK_IR_SLEEP         IR_SLEEP_KEY_MESSAGE

#define VK_IR_NUM0         _IR_NUM0_KEY_MESSAGE
#define VK_IR_NUM1         _IR_NUM1_KEY_MESSAGE
#define VK_IR_NUM2         _IR_NUM2_KEY_MESSAGE
#define VK_IR_NUM3         _IR_NUM3_KEY_MESSAGE
#define VK_IR_NUM4         _IR_NUM4_KEY_MESSAGE
#define VK_IR_NUM5         _IR_NUM5_KEY_MESSAGE
#define VK_IR_NUM6         _IR_NUM6_KEY_MESSAGE
#define VK_IR_NUM7         _IR_NUM7_KEY_MESSAGE
#define VK_IR_NUM8         _IR_NUM8_KEY_MESSAGE
#define VK_IR_NUM9         _IR_NUM9_KEY_MESSAGE


#ifdef __OSD007_LCD_OSD__
bit bRCallOSD              = 0;
#if(_CHANGE_SOURCE_METHOD == _CHANGE_SOURCE_METHOD_0)
BYTE ucChangeSourceCount   = 0;
#endif
WORD code usLANGUAGE_MASK  =  ( ENGLISH_EN   << ENGLISH ) |
                              ( LNG_DEU_EN   << LNG_DEU ) |
                              ( LNG_RUSS_EN<<LNG_RUSS)|
                              ( LNG_FRA_EN   << LNG_FRA ) |
                              ( LNG_ITA_EN   << LNG_ITA ) |
                              ( LNG_SPA_EN   << LNG_SPA ) |
                              ( LNG_CHI_S_EN << LNG_CHI_S ) |
                              ( LNG_CHI_T_EN << LNG_CHI_T )|
                              (LNG_PORT_EN << LNG_PORT)	|
                             ( LNG_KOREAN_EN <<LNG_KOREAN) |
                             (LNG_ARABIC_EN << LNG_ARABIC);
                              
#if(_AUTO_POWER_DOWN)
bit bTimerOnScreen       = 0;
WORD ucMinuteCount       = 0;
BYTE ucAutoPowerDownTime = 0;
#endif
#if(_VIDEO_TV_SUPPORT) 
WORD iInputCHCount       = _INPUT_CH_TIMEOUT_COUNT;
#endif

#if(_VIDEO_CHIP == _VDC_TB1334)
BYTE ucAudioState        = 1;
#endif
BYTE xdata ucOSDAdjTemp  = 0;

void COsdHandler(void);
void COsdSystemFlowProc(void);
void COsdProc(void);
void CChangeSourceHandler(void);
void CSourceChange(void);
void COthterKeyAction(void);
void COsdDispFirstTimeLoadFont(void);
void COsdEventMsgProc(void);
void COsdDispOsdTimerEvent(void);
void LoadLanguageFont(void);
void OSDSlider(BYTE row, BYTE col, BYTE length, BYTE value, BYTE range,
                      BYTE color, bit bMode);
void DispIcon(BYTE x,BYTE y,BYTE ucIconBaseAddr);
#if(_VIDEO_CHIP == _VDC_TB1334)
void CAudioCtrl(void);
#endif
void ShowMode(void);

void NotUseFunc();

void CShow4BitIcon(void);
void CClearWindow(BYTE ucCharacterColor);
void CInitOSDMainFrame(void);
void InitOSDFrame();
void ShowPageIndex(BYTE ucIndex,BYTE ucMaxPage);

#if(_IR_ENABLE)        
void SSetMuteState(void);
void DrawMuteState(void);
#endif


void CClearSubItem(void);
void CClearMsg(BYTE ucMode);
void CShowSelectMainItemWindow(BYTE ucItem);
void CShowSubItemWindow(BYTE ucItem);
void CSetItemWindowState(BYTE ucWinNumber, BYTE ucItemState);
void CExitToMainItem(BYTE ucMainItem);
void CGotoNextSubItem(BYTE ucItem);
void CDrawColorPage(void);
void CDrawOSDFuncPage(void);
void CDrawSoundPage(void);
void CDrawOtherFuncPage(void);
void CDrawExitPage(void);
#if(_VGA_COLOR_SUPPORT)
void CDrawVividColorPage(void);
void CDrawVividColorSubPage(void);
void CDrawDCCPage(void);
void CDrawICMPage(void);
void CDrawVividSubColorPage(void);
#endif

void MPublicNoneMenu(void);
void MPubNoneProc(void);

void MMainItemProc(void);
void MMainItemMenu(void);
void MMainItemLR(BYTE  LR);


// Color page
void MColorSubItemProc(void);
void MColorSubItemMenu(void);
void MColorSubItemLR(BYTE LR);


// OSD Sub item
void MOSDSubItemProc(void);
void MOSDSubItemMenu(void);
void MOSDSubItemLR(BYTE LR);

// OSD language
void MLanguageAdjProc(void);
void MLanguageAdjMenu(void);
void MLanguageAdjLR(BYTE  LR);

#if(_OSD_POSITION_ADJ_CTRL)
// OSD H position sub item
void MOSDHPositionAdjProc(void);
void MOSDHPositionAdjMenu(void);
void MOSDHPositionAdjLR(BYTE LR);

// OSD V position sub item
void MOSDVPositionAdjProc(void);
void MOSDVPositionAdjMenu(void);
void MOSDVPositionAdjLR(BYTE LR);
#endif  

#if(_OSD_TIMEOUT_ADJ_CTRL)
// OSD Timeout sub item
void MOSDTimeoutAdjProc(void);
void MOSDTimeoutAdjMenu(void);
void MOSDTimeoutAdjLR(BYTE LR);
#endif

#if(_ALPHA_BLENDING_ADJ)
// OSD Translucent sub item
void MOSDTranslucentAdjProc(void);
void MOSDTranslucentAdjMenu(void);
void MOSDTranslucentAdjLR(BYTE LR);
#endif

#if(_ALPHA_BLENDING_ADJ || _OSD_DISPLAY_SIZE_ADJ)
void CSetOSDTransAndSize(void);
#endif

#if(_OSD_DISPLAY_SIZE_ADJ)
// OSD Size sub item
void MOSDSizeAdjProc(void);
void MOSDSizeAdjMenu(void);
void MOSDSizeAdjLR(BYTE LR);
#endif

// Sound page
void MSoundSubItemProc(void);
void MSoundSubItemMenu(void);
void MSoundSubItemLR(BYTE LR);

#if(_VGA_COLOR_SUPPORT)
void CExitToSubItem(BYTE ucSubItem, BYTE ucCurrentSelectSubWindow);

void CClearVColorItem(void);
void CGotoAdjustVColor(void);
void CShowVColorSubItemWindow(BYTE ucItem);
void CShowVColorSelectSubItemWindow(BYTE ucItem);


// Vivid color
void MVividColorItemProc(void);
void MVividColorItemMenu(void);
void MVividColorItemLR(BYTE LR);

// Window color sub page
void MVividColorSubProc(void);
void MVividColorSubMenu(void);
void MVividColorSubLR(BYTE LR);

// DCC page
void MDCCAdjProc(void);
void MDCCAdjMenu(void);
void MDCCAdjLR(BYTE LR);

// ICM page
void MICMItemProc(void);
void MICMItemMenu(void);
void MICMItemLR(BYTE LR);

// ICM R/G/B/C/Y/M item page
void MICMSubRGBItemAdjProc(void);
void MICMSubRGBItemAdjMenu(void);
void MICMSubRGBItemAdjLR(BYTE LR);
void CExitToICMPage(const BYTE ucExitToItem);

// ICM R/G/BC/Y/M color item page
void MICMSubRGBColorAdjProc(void);
void MICMSubRGBColorAdjMenu(void);
void MICMSubRGBColorAdjLR(BYTE LR);

// DCC color
void MDCCColorAdjProc(void);
void MDCCColorAdjMenu(void);
void MDCCColorAdjLR(BYTE  LR);

void MDCCColorBCAdjProc(void);
void MDCCColorBCAdjMenu(void);
void MDCCColorBCAdjLR(BYTE  LR);

#endif  // end #if(_VGA_COLOR_SUPPORT)

// Other page
void MOtherSubItemProc(void);
void MOtherSubItemMenu(void);
void MOtherSubItemLR(BYTE LR);

void MDispModeAdjProc(void);
void MDispModeAdjMenu(void);
void MDispModeAdjLR(BYTE LR);
// Color brightness
void MBrightAdjProc(void);
void MBrightAdjMenu(void);
void MBrightAdjLR(BYTE  LR);

// Color contrast
void MContrastAdjProc(void);
void MContrastAdjMenu(void);
void MContrastAdjLR(BYTE  LR);

//  Volume proc
void MVolumeAdjProc(void);
void MVolumeAdjMenu(void);
void MVolumeAdjLR(BYTE  LR);

//  Mute proc
void MMuteAdjProc(void);
void MMuteAdjMenu(void);
void MMuteAdjLR(BYTE LR);

#if(_SOUND_PROCESSOR == _ENABLE)
//  Balance proc
void MBalanceAdjProc(void);
void MBalanceAdjMenu(void);
void MBalanceAdjLR(BYTE  LR);

//  Bass proc
void MBassAdjProc(void);
void MBassAdjMenu(void);
void MBassAdjLR(BYTE  LR);

//  Treble proc
void MTrebleAdjProc(void);
void MTrebleAdjMenu(void);
void MTrebleAdjLR(BYTE  LR);

//  SRS proc
void MSRSAdjProc(void);
void MSRSAdjMenu(void);
void MSRSAdjLR(BYTE  LR);

//  BBE proc
void MBBEAdjProc(void);
void MBBEAdjMenu(void);
void MBBEAdjLR(BYTE  LR);
#endif

//  Other auto power down
#if(_AUTO_POWER_DOWN)
void MAutoPowerDownAdjProc(void);
void MAutoPowerDownAdjMenu(void);
void MAutoPowerDownAdjLR(BYTE LR);
void MSleepTimeAdj(void);
void CGotoAdjSleep(void);
#endif
//  Other auto power down

// Other color mode
#if(_IMAGE_COLOR_MODE)
void MColorModeAdjProc(void);
void MColorModeAdjMenu(void);
void MColorModeAdjLR(BYTE LR);
void CGotoAdjImage(void);
void MImageAdj(void);

void CDrawColorModeState(BYTE ucColorModeState);
void CSetColorMode(BYTE ucMode);
#endif

// Other sharp
#if(_SHARPNESS_ADJ)
void MSharpAdjProc(void);
void MSharpAdjMenu(void);
void MSharpAdjLR(BYTE LR);
#endif

#if(_BLUE_BACKGROUND_FUNC == _ENABLE)
void MBlueAdjProc(void);
void MBlueAdjMenu(void);
void MBlueAdjLR(BYTE  LR);
#endif

void CShowTimer(void);
void HintDialog(void);
void CShowCurrentSourceTitle(BYTE ucHpos, BYTE ucVpos);
void ShowNote(void);
void CDisplayCurrentSourceMessage(void);

#else

extern WORD code usLANGUAGE_MASK;
extern BYTE ucAudioState;

#if(_AUTO_POWER_DOWN)
extern bit bTimerOnScreen;
extern WORD ucMinuteCount;
extern BYTE ucAutoPowerDownTime;
#endif

#if(_VIDEO_TV_SUPPORT) 
extern WORD iInputCHCount;
#endif
extern BYTE xdata ucOSDAdjTemp;

extern void COsdHandler(void);
extern void COsdProc(void);
extern void COthterKeyAction(void);
extern void COsdDispFirstTimeLoadFont(void);
extern void COsdEventMsgProc(void);
extern void COsdDispOsdTimerEvent(void);
extern void LoadLanguageFont(void);
extern void OSDSlider(BYTE row, BYTE col, BYTE length, BYTE value, BYTE range,
                      BYTE color, bit bMode);
#if(_VGA_COLOR_SUPPORT)
extern void CGotoAdjustVColor(void);
#endif
extern void ShowMode(void);
extern void DispIcon(BYTE x,BYTE y,BYTE ucIconBaseAddr);

extern void CClearWindow(BYTE ucCharacterColor);
extern void CInitOSDMainFrame(void);
extern void InitOSDFrame(void);

extern void CClearSubItem(void);
extern void CClearMsg(BYTE ucMode);
extern void CShowSelectMainItemWindow(BYTE ucItem);
extern void CShowSubItemWindow(BYTE ucItem);
extern void CSetItemWindowState(BYTE ucWinNumber, BYTE ucItemState);
extern void CExitToMainItem(BYTE ucMainItem);
extern void CGotoNextSubItem(BYTE ucItem);
extern void CDrawColorPage(void);

extern void MPublicNoneMenu(void);



#if(_ALPHA_BLENDING_ADJ || _OSD_DISPLAY_SIZE_ADJ)
extern void CSetOSDTransAndSize(void);
#endif
#if(_IR_ENABLE)        
extern void SSetMuteState(void);
#endif

#if(_IMAGE_COLOR_MODE)
extern void CSetColorMode(BYTE ucMode);
extern void CGotoAdjImage(void);

#endif

extern void GotoAdjustVolume(void);
#if(_KEY_TYPE_OSD007== _5KEY_SUPPORT)
extern void GotoAdjustChanel(void);
#endif 

#if(_AUTO_POWER_DOWN)
extern void MAutoPowerDownAdjProc(void);
extern void MAutoPowerDownAdjMenu(void);
extern void MAutoPowerDownAdjLR(BYTE LR);
extern void MSleepTimeAdj(void);
extern void CGotoAdjSleep(void);
#endif

extern void HintDialog(void);

extern void ShowNote(void);
extern void CDisplayCurrentSourceMessage(void);

#endif  //#ifdef __OSD007_LCD_OSD__
extern void CDrawOtherFuncPage(void);

#endif  //#if(OSD_TYPE == OSD007)
