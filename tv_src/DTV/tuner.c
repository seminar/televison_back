ATV.
                    
        msAPI_Tuner_SetIF();-> msAPI_Tuner_SetIF_By_Freq_AudioStd(); ->MDrv_IFDM_SetIF(eIF_Freq);
        msAPI_SetTunerPLL();-> _SetTunerPLL();->devTunerSetFreq(U32 u32Freq); 
        或者：
        sAPI_Tuner_SetIF_By_Freq_AudioStd(); ->MDrv_IFDM_SetIF(eIF_Freq);
        _SetTunerPLL( u16TunerPll );->devTunerSetFreq(U32 u32Freq); 

        R840 TUNER:
        retb &= ATV_SetTune(u32Freq/1000,(RFBAND)0, m_eMode,(U8)m_OtherMode);
        |
        R840_SetPllData();
        R840_SetStandard();
        R840_SetFrequency();

 **************************************************************************************************************************
DTV.    
        MApp_ChannelChange_EnableChannel（）
        |
        MApp_ChannelChange_EnableChannel_ResetTunerAndDemod（）
        |
        msAPI_Tuner_Tune2RfCh();// DTV -T -C  T2
        |                                          
        DTV T2 :mdev_CofdmSetFrequency();     
        {
	        devDigitalTuner_SetFreq((double)(dwFrequency/1000.0), eBandWidth);    
	        MDrv_DMD_DVBT2_SetConfig(eInternDvbT2Bw, 0, g_plp_id);
		    MDrv_DMD_DVBT2_SetActive(ENABLE);
        }   
        DTV -T :devCOFDM_SetFrequency()          ->devDigitalTuner_SetFreq((double)(dwFrequency/1000.0), E_RF_CH_BAND_8MHz); 
        DTV -C :devQAM_SetFrequency()            ->devDigitalTuner_SetFreq((double)(dwFrequency/1000.0), eBandWidth);

        R840 TUNER:     
        bRet &= DTV_SetTune(Freq, eBandWidth, m_eMode);
        R840_SetPllData(stR840_Info);
        |
        R840_SetStandard();
        R840_SetFrequency();


*******************************************************************************************************************************
        MApi_DigiTuner_Tune2RfCh(sat,&TP,eAutoTune); // DTV -S2
        |
        _DigiTuner_CalculateIF(stSatInfor,pParam,&dmdParam);
        _DigiTuner_SetLNBPower(stSatInfor.eLNBPwrOnOff,pParam->u8Polarity,stSatInfor.bPorInvert);
        _DigiTuner_SwitchSatellite(stSatInfor,pParam->u8Polarity,bIsHiLOF);
        #if (SUPPORT_UNICABLE)
		if (_stSATParam.eLNBType == EN_LNBTYPE_UNICABLE)
		{
			FrontEnd_DVBS2_Set(_tunerParam.u32S2Frequency, _tunerParam.u16SymbolRate, _tunerParam.u8Polarity, &_stSATParam);
		}
		else
		#endif
        {
			if (MDrv_CofdmDmd_Restart(&dmdParam) == FALSE)
			{
				return FALSE;
			}
		}