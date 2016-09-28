
#include "Rs232\Rs232.h"
#if(_IR_ENABLE)
//----------------------------------------
// Definitions of IR custom code
//----------------------------------------
#define IR_CHUNGHOP_RMH02           0   
#define IR_OTHER                             1   
#define IR_TTL757                            2 
#define IR_OM                                   3   
#define IR_DK                                   4
#define IR_DVD                                 5
#define IR_DK_QC                                  6

#define _REMOTE_CONTROLLER                 IR_DK_QC

#if(_REMOTE_CONTROLLER == IR_CHUNGHOP_RMH02)
#define CUSTOM_CODE     	0xfb04
#elif(_REMOTE_CONTROLLER == IR_OTHER)
#define CUSTOM_CODE     	0xff00
#elif(_REMOTE_CONTROLLER == IR_TTL757)
#define CUSTOM_CODE     	0x9e29
#elif(_REMOTE_CONTROLLER == IR_OM)
#define CUSTOM_CODE     	0xff20
#elif(_REMOTE_CONTROLLER == IR_DK)
#define CUSTOM_CODE     	0x7f80
#elif(_REMOTE_CONTROLLER == IR_DVD)
#define CUSTOM_CODE     	0xff20
#elif(_REMOTE_CONTROLLER == IR_DK_QC)
#define CUSTOM_CODE     	         0x03EF                //0xEF10//0x7f80

#endif

//--------------------------------------------------
// Definitions of IR Key Data
//--------------------------------------------------
#if(_REMOTE_CONTROLLER == IR_CHUNGHOP_RMH02)
// Only for CHUNGHOP RM-H02 REMOTE
#define IR_FUNC_POWER               0xb7
#define IR_FUNC_SOURCE              0x0f
#define IR_FUNC_UP                  0x15
#define IR_FUNC_DOWN                0x95
#define IR_FUNC_LEFT                0x57
#define IR_FUNC_RIGHT               0x27
#define IR_FUNC_MENU                0x77
#define IR_FUNC_VOLINC              0xa7
#define IR_FUNC_VOLDEC              0x87
#define IR_FUNC_CHINC               0x28
#define IR_FUNC_CHDEC               0x07

#define IR_FUNC_SLEEP               0x17
#define IR_FUNC_RETURN              0x35
#define IR_FUNC_TV_SYSTEM           0xe5 //制式
#define IR_FUNC_PIP                 0x75 //画中画
#define IR_FUNC_SHOW                0xc7
#define IR_FUNC_MUTE                0xf7
#define IR_FUNC_INPUTCH             0x2f
#define IR_FUNC_OK                  0xc5

#define IR_FUNC_NUM0                0xff
#define IR_FUNC_NUM1                0x7f
#define IR_FUNC_NUM2                0xbf
#define IR_FUNC_NUM3                0x3f
#define IR_FUNC_NUM4                0xdf
#define IR_FUNC_NUM5                0x5f
#define IR_FUNC_NUM6                0x9f
#define IR_FUNC_NUM7                0x1f
#define IR_FUNC_NUM8                0xef
#define IR_FUNC_NUM9                0x6f

#elif(_REMOTE_CONTROLLER == IR_OTHER)
// Only for KX TV REMOTE
#define IR_FUNC_POWER               0xB7
#define IR_FUNC_SOURCE              0x8D
#define IR_FUNC_UP                  0x4F
#define IR_FUNC_DOWN                0x17
#define IR_FUNC_LEFT                0x5F
#define IR_FUNC_RIGHT               0xCF
#define IR_FUNC_MENU                0xBF
/*
#define IR_FUNC_VOLINC              0x5F
#define IR_FUNC_VOLDEC              0x30
#define IR_FUNC_CHINC               0x17
#define IR_FUNC_CHDEC               0x4F
*/
#define IR_FUNC_SLEEP               0xF7
#define IR_FUNC_RETURN              0x55
#define IR_FUNC_TV_SYSTEM           0xe5 //制式
#define IR_FUNC_PIP                 0x75 //画中画
#define IR_FUNC_SHOW                0x97
#define IR_FUNC_MUTE                0x27
#define IR_FUNC_INPUTCH             0x6f
#define IR_FUNC_OK                  0xc5

#define IR_FUNC_NUM0                0x95
#define IR_FUNC_NUM1                0xBD
#define IR_FUNC_NUM2                0x3D
#define IR_FUNC_NUM3                0x0F
#define IR_FUNC_NUM4                0x87
#define IR_FUNC_NUM5                0x47
#define IR_FUNC_NUM6                0xC7
#define IR_FUNC_NUM7                0xE7
#define IR_FUNC_NUM8                0x5D
#define IR_FUNC_NUM9                0xCD

#elif(_REMOTE_CONTROLLER == IR_TTL757)
// Only for IR_TTL757 REMOTE
#define IR_FUNC_POWER               0xb7
#define IR_FUNC_SOURCE              0x0f
#define IR_FUNC_UP                  0x95
#define IR_FUNC_DOWN                0x15
#define IR_FUNC_LEFT                0x0df//  IR_TTL757
#define IR_FUNC_RIGHT               0x9f//  IR_TTL757
#define IR_FUNC_MENU                0x5f//  IR_TTL757
//#define IR_FUNC_OK                  0x97  Can not use
#define IR_FUNC_VOLINC              0xa7
#define IR_FUNC_VOLDEC              0x87
#define IR_FUNC_CHINC               0x27
#define IR_FUNC_CHDEC               0x07

#define IR_FUNC_SLEEP               0x8f
#define IR_FUNC_RETURN              0xb5
#define IR_FUNC_TV_SYSTEM           0xe5 // P.N.S
#define IR_FUNC_SOUND               0x37 // I/II
#define IR_FUNC_NORMAL              0xd5 // ->*<-
#define IR_FUNC_SOUND_SYSTEM        0x47 // A
#define IR_FUNC_PIP                 0x75
#define IR_FUNC_SHOW                0x97
#define IR_FUNC_MUTE                0xf7
#define IR_FUNC_INPUTCH             0x2f

#define IR_FUNC_NUM0                0xff
#define IR_FUNC_NUM1                0x7f
#define IR_FUNC_NUM2                0xbf
#define IR_FUNC_NUM3                0x3f
#define IR_FUNC_NUM4                0xe0//  IR_TTL757
#define IR_FUNC_NUM5                0xe1//  IR_TTL757
#define IR_FUNC_NUM6                0xe2//  IR_TTL757
#define IR_FUNC_NUM7                0x1f
#define IR_FUNC_NUM8                0xef
#define IR_FUNC_NUM9                0x6f

#elif(_REMOTE_CONTROLLER == IR_OM)

#define IR_FUNC_POWER               0xAF
#define IR_FUNC_SOURCE              0x7D
#define IR_FUNC_UP                  0x8F  // Not use
#define IR_FUNC_DOWN                0x2F  // Not use
#define IR_FUNC_LEFT                0x77
#define IR_FUNC_RIGHT               0xF7
#define IR_FUNC_MENU                0x4F
#define IR_FUNC_VOLINC              0x57
#define IR_FUNC_VOLDEC              0xC7
 #define IR_FUNC_OK              0xAD
 #define IR_FUNC_EXIT               0xCD
 #define IR_FUNC_AV            0xCE
 #define IR_FUNC_SV              0xC9
 #define IR_FUNC_VGA             0xC8
 #define IR_FUNC_TV              0xCB
 #define IR_FUNC_DVD             0xCA

#define IR_FUNC_SLEEP               0xCF // Not use
#define IR_FUNC_RETURN              0x47
#define IR_FUNC_TV_SYSTEM           0xe5  // Not use
#define IR_FUNC_SOUND               0x37  // Not use
#define IR_FUNC_NORMAL              0xd5  // Not use
#define IR_FUNC_SOUND_SYSTEM        0xB7  // Not use
#define IR_FUNC_IMAGE                 0x67  // Not use
#define IR_FUNC_SHOW                0xBD  // Not use
#define IR_FUNC_MUTE                0x0F 
#define IR_FUNC_INPUTCH             0x5D

#define IR_FUNC_NUM0                0xFF
#define IR_FUNC_NUM1                0x7F
#define IR_FUNC_NUM2                0xBF
#define IR_FUNC_NUM3                0x3F
#define IR_FUNC_NUM4                0xDF
#define IR_FUNC_NUM5                0x5F
#define IR_FUNC_NUM6                0x9F
#define IR_FUNC_NUM7                0x1F
#define IR_FUNC_NUM8                0xEF
#define IR_FUNC_NUM9                0x6F

#elif(_REMOTE_CONTROLLER == IR_DK)
#define IR_FUNC_POWER               0x07
#define IR_FUNC_SOURCE              0xAF
//#define IR_FUNC_LEFT                0x9f // CH -
//#define IR_FUNC_RIGHT               0xbf // CH +
//#define IR_FUNC_MENU                0xff
//#define IR_FUNC_VOLINC              0xdf
//#define IR_FUNC_VOLDEC              0x1f
                                    
#if(_USE_UD_LR_KEY_MSG)
#define IR_FUNC_LEFT                0x1F 
#define IR_FUNC_RIGHT               0xDF
#define IR_FUNC_DOWN                0xBF
#define IR_FUNC_UP                  0x9F
#else
#define IR_FUNC_LEFT                0xdf // CH -
#define IR_FUNC_RIGHT               0x1f // CH +
#define IR_FUNC_CHINC               0xbf
#define IR_FUNC_CHDEC               0x9f
#endif
//#define IR_FUNC_CHINC               0xbe
//#define IR_FUNC_CHDEC               0x9e
#define IR_FUNC_MENU                0xFF
#define IR_FUNC_EXIT                0xFE
#define IR_FUNC_OK                  0x3F

//#define IR_FUNC_SLEEP               0x8f  // Not use
#define IR_FUNC_RETURN              0x0F
#define IR_FUNC_TV_SYSTEM           0xe5  // Not use
//#define IR_FUNC_SOUND               0x37  // Not use
#define IR_FUNC_NORMAL              0xd5  // Not use
#define IR_FUNC_SOUND_SYSTEM        0xAB  // Not use
#define IR_FUNC_PIP                 0x75  // Not use
#define IR_FUNC_SHOW                0x2F  // Not use
#define IR_FUNC_MUTE                0xC7  
#define IR_FUNC_INPUTCH             0xEF
//#define IR_FUNC_CALL                0x3f
#define IR_FUNC_IMAGE               0x8F

 #define IR_FUNC_AV            0xCE
 #define IR_FUNC_SV              0xC9
 #define IR_FUNC_VGA             0xC8
 #define IR_FUNC_TV              0xCB
 #define IR_FUNC_DVD             0xCA

#define IR_FUNC_NUM0                0xCF
#define IR_FUNC_NUM1                0xE7
#define IR_FUNC_NUM2                0xA7
#define IR_FUNC_NUM3                0x27
#define IR_FUNC_NUM4                0xD7
#define IR_FUNC_NUM5                0x97
#define IR_FUNC_NUM6                0x17
#define IR_FUNC_NUM7                0xF7
#define IR_FUNC_NUM8                0xB7
#define IR_FUNC_NUM9                0x37
#elif(_REMOTE_CONTROLLER == IR_DK_QC)
#define IR_FUNC_POWER               0x14
#define IR_FUNC_MUTE                0x04 

#define IR_FUNC_NUM0                0x64
#define IR_FUNC_NUM1                0x56
#define IR_FUNC_NUM2                0x66
#define IR_FUNC_NUM3                0x46
#define IR_FUNC_NUM4                0x94
#define IR_FUNC_NUM5                0xA4
#define IR_FUNC_NUM6                0x84
#define IR_FUNC_NUM7                0x96
#define IR_FUNC_NUM8                0xA6
#define IR_FUNC_NUM9                0x86
#define IR_FUNC_RETURN              0x44
#define IR_FUNC_VOLINC               0x3E
#define IR_FUNC_VOLDEC               0x9E
#define IR_FUNC_CHINC               0xFE
#define IR_FUNC_CHDEC               0x8e
#define IR_FUNC_ZOOM                0XBE
#define IR_FUNC_MST                0x7E                           
#if(_USE_UD_LR_KEY_MSG)
#define IR_FUNC_LEFT                0x16 
#define IR_FUNC_RIGHT               0x06
#define IR_FUNC_DOWN                0xE4
#define IR_FUNC_UP                  0xB6
#else
#define IR_FUNC_LEFT                0xdf // CH -
#define IR_FUNC_RIGHT               0x1f // CH +
#define IR_FUNC_CHINC               0xbf
#define IR_FUNC_CHDEC               0x9f
#endif
#define IR_FUNC_MENU                0xD4
#define IR_FUNC_EXIT                0xC4
#define IR_FUNC_SOURCE              0x3C
#define IR_FUNC_OK                  0x26
#define IR_FUNC_PMODE            0xBC
#define IR_FUNC_SMODE            0x7C
#define IR_FUNC_SLEEP            0xFC
#define IR_FUNC_FAV            0x1C
#define IR_FUNC_FAV_PLUS              0X9C
#define IR_FUNC_FAV_MINUS            0X5C
#define IR_FUNC_EPG               0XDC
#define IR_FUNC_TEXT                  0X2C
#define IR_FUNC_HOLD                  0XAC
#define IR_FUNC_AUDIO                  0X6C
#define IR_FUNC_SUBT                  0XEC
#define IR_FUNC_INDEX                 0X0C
#define IR_FUNC_SIZE                 0X8C
#define IR_FUNC_REVEAL                 0X4C
#define IR_FUNC_SUBP                 0XCC
#define IR_FUNC_RED                0X87
#define IR_FUNC_GRENN                0X8B
#define IR_FUNC_YELLOW               0X8F
#define IR_FUNC_BULE               0X93

#define IR_FUNC_INPUTCH             0xD7 // Not use
#define IR_FUNC_IMAGE               0xDB // Not use
 #define IR_FUNC_AV            0xD3 // Not use
 #define IR_FUNC_SV              0xD2 // Not use
 #define IR_FUNC_VGA             0xD1 // Not use
 #define IR_FUNC_TV              0xD0 // Not use
 #define IR_FUNC_DVD             0x95 // Not use
#define IR_FUNC_TV_SYSTEM        0x99  // Not use
#define IR_FUNC_SHOW                0xD6// Not use
#define IR_FUNC_HDMI             0xC0 // Not use
#define IR_FUNC_DTV             0xC1 // Not use


#elif(_REMOTE_CONTROLLER == IR_DVD)

#define IR_FUNC_POWER               0xaf
#define IR_FUNC_SOURCE              0x7d
#define IR_FUNC_VOLINC              0xe5
#define IR_FUNC_VOLDEC              0x2d
                                    
#define IR_FUNC_LEFT                0x2d
#define IR_FUNC_RIGHT               0xe5
#define IR_FUNC_DOWN                0x07
#define IR_FUNC_UP                  0x87

#define IR_FUNC_CHINC               0x07
#define IR_FUNC_CHDEC               0x87
#define IR_FUNC_MENU                0x4f

#define IR_FUNC_SLEEP               0xcf  // Not use
#define IR_FUNC_RETURN              0x47
#define IR_FUNC_SHOW                0xbd // Not use
#define IR_FUNC_MUTE                0x0f 
#define IR_FUNC_INPUTCH             0x5d
#define IR_FUNC_IMAGE               0x8e
 #define IR_FUNC_AV            0xCE
 #define IR_FUNC_SV              0xC9
 #define IR_FUNC_VGA             0xC8
 #define IR_FUNC_TV              0xCB
 #define IR_FUNC_DVD             0xCA

#define IR_FUNC_NUM0                0xff
#define IR_FUNC_NUM1                0x7f
#define IR_FUNC_NUM2                0xbf
#define IR_FUNC_NUM3                0x3f
#define IR_FUNC_NUM4                0xdf
#define IR_FUNC_NUM5                0x5f
#define IR_FUNC_NUM6                0x9f
#define IR_FUNC_NUM7                0x1f
#define IR_FUNC_NUM8                0xef
#define IR_FUNC_NUM9                0x6f
#if(DVD_EN)
        #define  IR_DVD_KEY_DVD_EJECT  0xcd
        #define  IR_DVD_KEY_RECALL         0x48//
        #define  IR_DVD_KEY_MTS               0xfd
        #define  IR_DVD_KEY_DVD_MENU    0x27
        #define  IR_DVD_KEY_PIP             0x4d//
        #define  IR_DVD_KEY_UP             0x2f 
        #define  IR_DVD_KEY_DOWN        0x8f
        #define  IR_DVD_KEY_LEFT            0xf7
        #define  IR_DVD_KEY_RIGHT         0x77
        #define  IR_DVD_KEY_DVD_SLOW  0xa7//
        #define  IR_DVD_KEY_TTX_LIST     0xc7
        #define  IR_DVD_KEY_TTX             0xdd
        #define  IR_DVD_KEY_TTX_HOLD      0x9d
        #define  IR_DVD_KEY_TTX_CANCEL   0x57
        #define  IR_DVD_KEY_TTX_INDEX       0x37
        #define  IR_DVD_KEY_MENU                0x28//
        #define  IR_DVD_KEY_TTX_SUBTITLE    0xd7
        #define  IR_DVD_KEY_DVD_SELECT      0xad
        #define  IR_DVD_KEY_TTX_SIZE           0x3d
        #define  IR_DVD_KEY_TTX_REVEAL       0x1d
        #define  IR_DVD_KEY_TTX_RED              0x97
        #define  IR_DVD_KEY_TTX_GREEN           0x17
        #define  IR_DVD_KEY_TTX_YELLOW         0xe7
        #define  IR_DVD_KEY_TTX_CYAN            0x67
	 #define IR_DVD_KEY_REPEAT            0x8d
#endif	 
#endif

#ifndef __IR__
#define __IR__

extern BYTE ucDetectIR_Cmd;
#if _UARTIR
extern BYTE uchh;
extern BYTE ucll;
#endif 
extern void CStopIR(void);
extern void CStartIR(void);
extern void CInitial_IR(void);
#endif
#endif
