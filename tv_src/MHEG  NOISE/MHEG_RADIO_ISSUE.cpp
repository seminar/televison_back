DTV -> RADIO  SCREEN MUTE SETTING:
1、Disable AV; 
    msAPI_Scaler_SetBlueScreen( ENABLE, E_XC_FREE_RUN_COLOR_BLACK, DEFAULT_SCREEN_UNMUTE_TIME, eWindow);
    msAPI_Scaler_SetScreenMute(E_SCREEN_MUTE_FREERUN, ENABLE, 0, eWindow);

2、MHEG Si:
   mapp_tv, tv monitor ,
   MApp_TV_MHEG_Loading_Monitor();
   {
   	...
   	        if (MAp_MpHEG5_CheckMHEG5Status() == SI_MHEG5_DATA_ONLY)
        {

                MApp_ZUI_ACT_StartupOSD(E_OSD_MESSAGE_BOX);
                MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_SHOW_LOADING_MHEG5_MSGBOX);
                MS_VE_Output_Ctrl OutputCtrl;
                // disable VE
                OutputCtrl.bEnable = FALSE;
                msAPI_VE_SetOutputCtrl(&OutputCtrl);
                //MW_AUD_SetSoundMute(SOUND_MUTE_ALL, E_MUTE_ON);
           
        }
   	...
   }
          .......  设置屏保类型为 AUDIO。
         && (msAPI_CM_GetCurrentServiceType() == E_SERVICETYPE_RADIO)
         && (SYS_SCREEN_SAVER_TYPE(eWindow)==EN_SCREENSAVER_NULL)
         && (MApp_SI_Get_PSISIVersion(E_VER_PMT)!=INVALID_VERSION_NUM)
		 && (enMVDVideoStatus != MVD_GOOD_VIDEO)
         && (MApi_AUDIO_IsMadLock())
            )
        {
            if (SYS_INPUT_SOURCE_TYPE(eWindow) == INPUT_SOURCE_DTV)
            {
                SYS_SCREEN_SAVER_TYPE(eWindow) = EN_SCREENSAVER_AUDIOONLY;
            }
        }

        ...........


   void MApp_MHEG5_BootingMonitor()
   {
   	    MApp_MHEG5_SetGoMHEG5Process(TRUE);//-> go into  MApp_VID_ProcessMailboxMsg( u8Msg);!!
   }

   
   MSG OSD 关闭后：
   MULTITASK 函数中进入：
   _MApp_MHEG5_Process();
   MApp_VID_ProcessMailboxMsg( u8Msg);

   MApp_ChannelChange_ChangeSpeciChannel();
   msAPI_Scaler_SetScreenMute( E_SCREEN_MUTE_MHEG5, DISABLE, 0 , MAIN_WINDOW);

   MHEG 才可以播放出来。


