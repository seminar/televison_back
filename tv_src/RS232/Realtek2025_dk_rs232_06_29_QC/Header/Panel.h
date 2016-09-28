//----------------------------------------------------------------------------------------------------
// ID Code      : Panel.h No.0001
//
//----------------------------------------------------------------------------------------------------
// Panel Type
//--------------------------------------------------
#define _CMO_LVDS_17                    0          //1280x1024 LVDS
#define _AU_RSDS_17                     1          //1280x1024 RSDS 
#define _AU_LVDS_15                     2          //1024x768  LVDS
#define _PNL_LQ150U1                    3          //1600x1200 LVDS
#define _PNL_IASX12G                    4          //1400x1050 LVDS
#define _PNL_XG09                       5
#define _PNL_TTL_757                    6          // Toshiba 480x234 TTL panel
#define _PNL_LQ15X01K                   7          // Sharp 1024x768 TTL panel
#define _PNL_LTM150XHT01                8          // SamSung 1024x768 TTL panel
#define _PNL_HSD090IF41                 9          // HannStar HSD090IF41 800x480 TCON panel
#define _PNL_HSD23                      10         // HanStar 1280x768 LVDS 23" panel
#define _PNL_TTL_SHARP8                 11         // Sharp 640x480 8" panel  
#define _PNL_LVDS_LTN121XG_L03          12
#define _PNL_LVDS_AU_B121EW01           13
#define _PNL_CLAA320WA01                14         // Chi Mei 1366x768 signal LVDS panel
#define _PNL_1680X1050                  15         // 1680x1050 doublue LVDS panel
#define _PNL_LVDS_SAMSUNG_LTM170W1_L01  16         // Samsung 1280x768 LVDS 17" Panel
#define _PNL_TMDS_LG_LM201W01           17         // LG 1680x1050 20.1" TMDS panel(BXD)
#define _PNL_M190MWW1                   18         // Mindtech 1440x900 LVDS


#define _PANEL_TYPE                     _CMO_LVDS_17
//--------------------------------------------------

#if(_PANEL_TYPE == _PNL_TMDS_LG_LM201W01)
#include "Panel\PNL_LG_LM201W01.h"

// For TMDS panel
#define _SII164_INIT_SUPPORT           _ON  //_ON,OFF

#ifdef _SII164_INIT_SUPPORT
// SiI164 CONFIG
//sbit b164SW                 		   = P3^5;//_MCU_PORT65
#define _ADDR_SiI164                   0x70   //SiI164 I2C address
#endif
#endif

#if(_PANEL_TYPE == _PNL_LVDS_SAMSUNG_LTM170W1_L01)
#include "Panel\PNL_LTM170W1_L01.h"
#endif

#if(_PANEL_TYPE == _PNL_HSD23)
#include "Panel\PNL_LVDS23.h"
#endif

#if(_PANEL_TYPE == _PNL_CLAA320WA01)
#include "Panel\PNL_CLAA320WA01.h"
#endif

#if(_PANEL_TYPE == _PNL_1680X1050)
#include "Panel\PNL_LVDS1680X1050.h"
#endif

#if(_PANEL_TYPE == _PNL_M190MWW1)
#include "Panel\PNL_M190MWW1.h"
#endif

#if(_PANEL_TYPE == _CMO_LVDS_17)
#include "Panel\PNL_LVDS17.h"
#endif

#if(_PANEL_TYPE == _AU_RSDS_17)
#include "Panel\PNL_RSDS17.h"
#endif

#if(_PANEL_TYPE == _PNL_LVDS_AU_B121EW01)
#include "Panel\PNL_121_W.h"
#endif

#if(_PANEL_TYPE == _AU_LVDS_15)
#include "Panel\PNL_LVDS15.h"
#endif

#if(_PANEL_TYPE == _PNL_LVDS_LTN121XG_L03)
#include "Panel\PNL_LTN121XG_L03.h"
#endif

#if(_PANEL_TYPE == _PNL_LQ150U1)
#include "Panel\PNL_LQ150U1.h"
#endif

#if(_PANEL_TYPE == _PNL_IASX12G)
#include "Panel\PNL_IASX12G.h"
#endif

#if(_PANEL_TYPE == _PNL_XG09)
#include "Panel\PNL_XG09.h"
#endif

#if(_PANEL_TYPE == _PNL_TTL_757)
#include "Panel\PNL_TTL_757.h"
#endif

#if(_PANEL_TYPE == _PNL_LQ15X01K)
#include "Panel\PNL_LQ15X01K.h"
#endif

#if(_PANEL_TYPE == _PNL_LTM150XHT01)
#include "Panel\PNL_LTM150XHT01.H"
#endif

#if(_PANEL_TYPE == _PNL_HSD090IF41)
#include "Panel\PNL_HSD090IF41.H"
#endif

#if(_PANEL_TYPE == _PNL_TTL_SHARP8)
#include "Panel\PNL_TTL_SHARP8.h"
#endif

//--------------------------------------------------

