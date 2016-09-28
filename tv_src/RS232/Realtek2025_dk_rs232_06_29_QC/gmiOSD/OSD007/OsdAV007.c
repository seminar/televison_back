#define __OSDAV007___

#include "Header\Include.h"

#if(_OSD_TYPE == _OSD007)

#if(_VIDEO_SUPPORT)

//------------------------------------------------------------   
void MAVNoneProc(void)
{
    switch(ucKeyMessage)
    {
#if(_MENU_FUNC == _MENU_EXIT_ITEM)
        case VK_ENTER:       
#endif
        case VK_MENU:        MPublicNoneMenu();   break;
        case VK_LEFT:        MAVNoneLR(0);        break;
        case VK_RIGHT:       MAVNoneLR(1);        break;

#if(_IR_ENABLE)        
        case VK_IR_MUTE:
            SSetMuteState();
            ucOsdEventMsg = _SAVE_EE_OSDUSERDATA_MSG;
            break;
            
#if(_USE_UD_LR_KEY_MSG && _REMOTE_CONTROLLER != IR_CHUNGHOP_RMH02)
        case VK_F_LEFT:
        case VK_F_RIGHT:
#endif
        case VK_IR_VOLDEC:
        case VK_IR_VOLINC:
            GotoAdjustVolume(); 
            break;

        case VK_IR_DISPLAY:
            CDisplayCurrentSourceMessage();
            break;
#if(_IMAGE_COLOR_MODE)
        case _IR_IMAGE_KEY_MESSAGE:
            CGotoAdjImage();
            break;
#endif
#if(_AUTO_POWER_DOWN)
        case VK_IR_SLEEP:
            CGotoAdjSleep();
            break;
#endif
#endif
    }
}

//------------------------------------------------------------
void MAVNoneLR(BYTE LR)
{
    GotoAdjustVolume();
    LR = 0;  
}

//------------------------------------------------------------


//--------- AV HUE proc ----------------------------------
void MAVHueAdjProc(void)
{
    switch(ucKeyMessage)
    {
        // Move item
#if(_USE_UD_LR_KEY_MSG)
        case VK_F_UP:
        case VK_F_DOWN:
            MAVHueMenu();
            COsdProc();
            break;
#endif

        // Exit item
#if(_MENU_FUNC == _MENU_EXIT_ITEM)
        case VK_ENTER:
        case VK_AUTO:
	#endif
          case VK_IR_EXIT:
        case VK_MENU:        MAVHueMenu();       break;

        // Adjust
#if(_USE_UD_LR_KEY_MSG)
        case VK_F_LEFT:
#endif
        case VK_LEFT:        MAVHueLR(1);        break;

        // Adjust
#if(_USE_UD_LR_KEY_MSG)
        case VK_F_RIGHT:
#endif
        case VK_RIGHT:       MAVHueLR(0);        break;
           
        // Other key
        default:             COthterKeyAction(); break;
    }
}

//------------------------------------------------------------
void MAVHueMenu(void)
{
    ucOsdState = MENU_AV_HUE;
    CClearMsg(_CLEAR_AND_EXIT_SUB_ITEM);
}

//------------------------------------------------------------
void MAVHueLR(BYTE  LR)
{
    SET_KEYREPEATENABLE();     
    stConBriData.Hue = ValueInRangeChange(0,100,stConBriData.Hue,LR,0);
    SLIDER1(HUE_GUAGE);
    gmi_CAdjustVDCHue(stConBriData.Hue);
    ucOsdEventMsg = _SAVE_EE_BriConHueSat_MSG;
}

//--------- AV Saturation proc ----------------------------------
void MAVSaturationAdjProc(void)
{
    switch(ucKeyMessage)
    {
        // Move item
#if(_USE_UD_LR_KEY_MSG)
        case VK_F_UP:
        case VK_F_DOWN:
            MAVSaturationMenu();
            COsdProc();
            break;
#endif

        // Exit item
#if(_MENU_FUNC == _MENU_EXIT_ITEM)
        case VK_ENTER:       
#endif
        case VK_AUTO:
        case VK_IR_EXIT:
        case VK_MENU:        MAVSaturationMenu();       break;

        // Adjust
#if(_USE_UD_LR_KEY_MSG)
        case VK_F_LEFT:
#endif
        case VK_LEFT:        MAVSaturationLR(1);        break;

        // Adjust
#if(_USE_UD_LR_KEY_MSG)
        case VK_F_RIGHT:
#endif
        case VK_RIGHT:       MAVSaturationLR(0);        break;
           
        default:             COthterKeyAction();        break;
    }
}

//------------------------------------------------------------
void MAVSaturationMenu(void)
{
    ucOsdState = MENU_AV_SATURATION;
    CClearMsg(_CLEAR_AND_EXIT_SUB_ITEM);
}

//------------------------------------------------------------
void MAVSaturationLR(BYTE  LR)
{
    SET_KEYREPEATENABLE();
    stConBriData.Saturation = ValueInRangeChange(0,100,stConBriData.Saturation,LR,0);
    SLIDER1(SATURATION_GUAGE);
    CSetVDCSaturation(stConBriData.Saturation);
    ucOsdEventMsg = _SAVE_EE_BriConHueSat_MSG;
}

#endif  //#if(_VIDEO_AV_SUPPORT || _VIDEO_SV_SUPPORT || _VIDEO_TV_SUPPORT)

#endif  //#if(OSD_TYPE == OSD007)
