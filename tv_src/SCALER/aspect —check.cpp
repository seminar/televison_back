
SCALER FOR TV SETTING

// This Enum is for UI part, dont use it for Core (Kernel)
typedef enum
{
    EN_AspectRatio_Min,
    //EN_AspectRatio_Full,
    EN_AspectRatio_16X9 = EN_AspectRatio_Min,
    EN_AspectRatio_JustScan,
    EN_AspectRatio_Original,
    EN_AspectRatio_4X3,
    EN_AspectRatio_14X9,
    EN_AspectRatio_Zoom1,
    EN_AspectRatio_Zoom2,
    EN_AspectRatio_Panorama,
    EN_AspectRatio_Num,
} EN_MENU_AspectRatio;

//UI中设置：
ST_VIDEO.eAspectRatio = EN_AspectRatio_4X3;
MApp_Scaler_Setting_SetVDScale(ST_VIDEO.eAspectRatio, MAIN_WINDOW);

//该函数具体功能如下：
/// Aspect Ratio Type ==========================================================

typedef enum
{
    /* general */
    VIDEOSCREEN_MIN,                        ///< Video Screen Min
    VIDEOSCREEN_PROGRAM = VIDEOSCREEN_MIN, ///< according AFD or WSS setting
    VIDEOSCREEN_NORMAL,                 ///< Video Screen Normal
    VIDEOSCREEN_FULL,                      ///< video full panel resolution
    VIDEOSCREEN_ZOOM,                   ///< Video Screen Zoom
    VIDEOSCREEN_CINEMA,                 ///< Video Screen Cinema
#ifdef ATSC_SYSTEM
    VIDEOSCREEN_WIDE1,
    VIDEOSCREEN_WIDE2,
#endif
    /* specific options for 4:3 panel */
    VIDEOSCREEN_LETTERBOX,          ///< Video Screen Letterbox
    /* specific options for wide panel */
    VIDEOSCREEN_16by9_SUBTITLE,     ///< Video Screen 16:9 subtitle
    VIDEOSCREEN_PANORAMA,           ///< Video Screen Panorama
    /* others */
    VIDEOSCREEN_14by9,                        ///< 14:9
    VIDEOSCREEN_WSS_16by9,                    ///< WSS 16:9
    VIDEOSCREEN_WSS_14by9_LETTERBOX_CENTER,   ///< WSS: 0001 14:9 Letterbox Center
    VIDEOSCREEN_WSS_14by9_LETTERBOX_TOP,      ///< WSS: 0010 14:9 Letterbox Top
    VIDEOSCREEN_WSS_16by9_LETTERBOX_CENTER,   ///< WSS: 1011 16:9 Letterbox Center
    VIDEOSCREEN_WSS_16by9_LETTERBOX_TOP,      ///< WSS: 0100 16:9 Letterbox Top
    VIDEOSCREEN_ZOOM1,                        ///< Video Screen Zoom1
    VIDEOSCREEN_ZOOM2,                        ///< Video Screen Zoom2
    VIDEOSCREEN_JUSTSCAN,                     ///< Video Screen Justscan
    VIDEOSCREEN_SCENE4_3to16_9,               ///< Video Screen Scene 4:3 to 16:9
    VIDEOSCREEN_SCENE16_9to4_3,               ///< Video Screen Scene 16:9 to 4:3
    VIDEOSCREEN_SCENE4_3to16_9_WITH_CCO,      ///< Video Screen Scene 4:3 to 16:9 with CCO
    VIDEOSCREEN_SCENE4_3to4_3_WITH_CCO,       ///< Video Screen Scene 4:3 to 4:3 with CCO
    VIDEOSCREEN_SCENE4_3to16_9_WITH_LB,       ///< Video Screen Scene 4:3 to 16:9 with LB
    VIDEOSCREEN_SCENE4_3to4_3_WITH_LB,        ///< Video Screen Scene 4:3 to 4:3 with LB
    VIDEOSCREEN_ORIGIN,
    VIDEOSCREEN_PROGRAM_16X9,
    VIDEOSCREEN_PROGRAM_4X3,
    VIDEOSCREEN_PROGRAM_14X9,
    #if ENABLE_WSS_1011_WRONG
    VIDEOSCREEN_WSS_ABOVE16by9_LETTERBOX_TOP,
    #endif

    VIDEOSCREEN_MM_KEEP_RATIO_AND_SCALE,    // Keep source H/V ratio and scale to fit panel
    VIDEOSCREEN_MM_FULL,    // H and V scale to fit panel
    VIDEOSCREEN_MM_1_1,     // Bypass scale
    VIDEOSCREEN_MM_16_9,    // Display window: H:V=16:9
    VIDEOSCREEN_MM_4_3,     // Display window: H:V=4:3
    VIDEOSCREEN_MM_ZOOM1,   // TO BE defined
    VIDEOSCREEN_MM_ZOOM2,   // TO BE defined
    VIDEOSCREEN_MM_CAL_BY_VIDEOPLAYER,
#if ENABLE_3D_PROCESS
    VIDEOSCREEN_3D_FULL,
    VIDEOSCREEN_3D_AUTO,
    VIDEOSCREEN_3D_CENTER,
#endif
    VIDEOSCREEN_NUMS,       //< numbers of video screen type
}EN_ASPECT_RATIO_TYPE;


enVideoScreen = MApp_Scaler_GetAspectRatio(eAspect);
stSystemInfo[MAIN_WINDOW].enAspectRatio = enVideoScreen;

//prescaler PQ setting at here !!!
MApp_Scaler_SetWindow(NULL, NULL, NULL,
                       enVideoScreen, SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW), MAIN_WINDOW);

MApp_Picture_Setting_SetColor(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW), MAIN_WINDOW);

//************************************************************************************************
//该函数功能：
MApp_Scaler_SetWindow(NULL, NULL, NULL,
                       enVideoScreen, SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW), MAIN_WINDOW);


static U8 _MApp_Scaler_Aspect_Ratio_Remapping(EN_ASPECT_RATIO_TYPE enVideoScreen)
{
    U8 u8_AR_NUM;

    switch(enVideoScreen)
    {
        case VIDEOSCREEN_FULL:
            u8_AR_NUM = E_AR_16x9;
            break;
        case VIDEOSCREEN_NORMAL:
            u8_AR_NUM = E_AR_4x3;
            break;
//        case VIDEOSCREEN_FULL:
//            u8_AR_NUM = E_AR_AUTO;
            break;
        case VIDEOSCREEN_PANORAMA:
            u8_AR_NUM = E_AR_Panorama;
            break;
        case VIDEOSCREEN_JUSTSCAN:
            u8_AR_NUM = E_AR_JustScan;
            break;
        case VIDEOSCREEN_ZOOM2:
            u8_AR_NUM = E_AR_Zoom2;
            break;
        case VIDEOSCREEN_ZOOM1:
            u8_AR_NUM = E_AR_Zoom1;
            break;
        default:
            u8_AR_NUM = E_AR_AUTO;
            break;
    }
    MSG(printf("Scaler aspect ratio remap: %u -> %u \n", enVideoScreen, u8_AR_NUM));

    printf(" \033[1;33;44m ffstest :Scaler aspect ratio remap: %u -> %u \033[0m\n", enVideoScreen, u8_AR_NUM);
    return u8_AR_NUM;

}

UI (4x3)           -> VIDEOSCREEN_NORMAL     ->  E_AR_4x3         ;
UI (16x9)          -> VIDEOSCREEN_FULL       ->  E_AR_16x9        ;
UI (auto)          -> VIDEOSCREEN_FULL       ->  E_AR_16x9        ;
UI (Justscan)      -> VIDEOSCREEN_JUSTSCAN   ->  E_AR_JustScan    ; 
UI (dtv.Panorama)  -> VIDEOSCREEN_PANORAMA   ->  E_AR_Panorama    ;
UI (zoom1)         -> VIDEOSCREEN_ZOOM1      ->  E_AR_Zoom1       ;
UI (zoom2)         -> VIDEOSCREEN_ZOOM2      ->  E_AR_Zoom2       ;


MS_WINDOW_TYPE stCapWin;        ///<Capture window
MS_WINDOW_TYPE stDispWin;       ///<Display window
MS_WINDOW_TYPE stCropWin;       ///<Crop window


         if( IsSrcTypeAnalog(enInputSourceType) || IsSrcTypeHDMI(enInputSourceType))
        {
            _MApp_Scaler_ProgAnalogWin(enInputSourceType, &g_PcadcModeSetting[eWindow], u8AspectRatio,
                                        MApi_XC_PCMonitor_GetSyncStatus(eWindow), &stXC_SetWin_Info[eWindow], eWindow);
            u16AlignX = ANALOG_CROP_ALIGN_X;
            u16AlignY = ANALOG_CROP_ALIGN_Y;
        }
        else if( IsSrcTypeATV(enInputSourceType) )
        {
            _MApp_Scaler_ProgDigitalWin( enInputSourceType, mvideo_vd_get_videosystem(), u8AspectRatio, &stXC_SetWin_Info[eWindow], eWindow );
            u16AlignX = DIGITAL_CROP_ALIGN_X;
            u16AlignY = DIGITAL_CROP_ALIGN_Y;
        }
        else if( IsSrcTypeDigitalVD(enInputSourceType) )
        {
            _MApp_Scaler_ProgDigitalWin( enInputSourceType, mvideo_vd_get_videosystem(), u8AspectRatio, &stXC_SetWin_Info[eWindow], eWindow );
            u16AlignX = DIGITAL_CROP_ALIGN_X;
            u16AlignY = DIGITAL_CROP_ALIGN_Y;
        }
        else if( IsSrcTypeDTV(enInputSourceType) )
        {
            MDrv_MVOP_GetOutputTiming(&stMVOPTiming);
            _MApp_Scaler_ProgMVDWin(eWindow, enInputSourceType, &stMVOPTiming, &stXC_SetWin_Info[eWindow]);
            _MApp_Scaler_CropCodecSrcWin(&gstVidStatus, &stXC_SetWin_Info[eWindow]);
            u16AlignX = DTV_CROP_ALIGN_X;
            u16AlignY = DTV_CROP_ALIGN_Y;
        }
    #if ((ENABLE_DMP) || (DISPLAY_LOGO))
        else
        {
            MDrv_MVOP_GetOutputTiming(&stMVOPTiming);
            _MApp_Scaler_ProgMVDWin(eWindow, enInputSourceType, &stMVOPTiming, &stXC_SetWin_Info[eWindow]);

            _MApp_Scaler_CropCodecSrcWin(&gstVidStatus, &stXC_SetWin_Info[eWindow]);
            u16AlignX = MEDIA_CROP_ALIGN_X;
            u16AlignY = MEDIA_CROP_ALIGN_Y;
        }
    #endif // #if ((ENABLE_DMP) || (DISPLAY_LOGO))

// 以上此部分代码 计算 Capture window。

//CROPWINDOW DEFAULT VALUE:
stXC_SetWin_Info[eWindow].stCropWin.x = 0;
stXC_SetWin_Info[eWindow].stCropWin.y = 0;
stXC_SetWin_Info[eWindow].stCropWin.width = stXC_SetWin_Info[eWindow].stCapWin.width;
stXC_SetWin_Info[eWindow].stCropWin.height= stXC_SetWin_Info[eWindow].stCapWin.height;


MApp_Scaler_Adjust_AspectRatio(eWindow, enVideoScreen, &stXC_SetWin_Info[eWindow].stCropWin, &stXC_SetWin_Info[eWindow].stDispWin, &tSrcRatioInfo,!IsSrcTypeDTV(enInputSourceType));	// adjust CropWin according to aspect ratio
//此函数计算 CROPWINDOW  DISPLAYWINDOW. 主要计算DISPLAYWINDOW VALUE.





