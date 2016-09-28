#if(_OSD_TYPE == _OSD007)


#if(_VIDEO_TV_SUPPORT)
//--------------------------------------------------

void OSDTVProc(void);
bit CSearchedTVType(BYTE uctvtype);
void MTVNoneProc(void);
void MTVNoneLR(BYTE LR);

#if(_IR_ENABLE)        
//------- Shorcut key proc ------------------------------------
void STVInputCHEnter(void);
void SInputCHNumber(void);
void SDirectnessInputCHNumber(void);
void SInceptNumber(const WORD ucNumber);
void SShowCurrentInputState(WORD ucInputState);

void STVInputCHNumber(void);
void STVReturnCH(void);
#endif

void CDrawTVFunction(void);

//   TV function Sub item
void MTVFuncSubItemProc(void);
void MTVFuncSubItemMenu(void);
void MTVFuncSubItemLR(BYTE LR);

void MTVSystemAdjProc(void);
void MTVSystemAdjMenu(void);
void MTVSystemAdjLR(BYTE  LR);
/*
void MSoundSystemAdjProc(void);
void MSoundSystemAdjMenu(void);
void MSoundSystemAdjLR(BYTE  LR);
void MSoundSystemAdjEnter(void);
                   */
void MAutoSearchAdjProc(void);
void MAutoSearchAdjMenu(void);
void MAutoSearchAdjLR(BYTE  LR);

void MManualSearchAdjProc(void);
void MManualSearchAdjMenu(void);
void MManualSearchAdjLR(BYTE  LR);

void MTuningAdjProc(void);
void MTuningAdjMenu(void);
void MTuningAdjLR(BYTE  LR);

void MChannelAdjProc(void);
void MChannelAdjMenu(void);
void MChannelAdjLR(BYTE  LR);

void MSwapAdjProc(void);
void MSwapAdjMenu(void);
void MSwapAdjLR(BYTE  LR);

void MSkipAdjProc(void);
void MSkipAdjMenu(void);
void MSkipAdjLR(BYTE  LR);

#if(_AUTO_POWER_DOWN)
void MAutoPowerDownAdjProc(void);
void MAutoPowerDownAdjMenu(void);
void MAutoPowerDownAdjLR(BYTE  LR);
#endif

#if(_TV_SEARCH_SHOW_TYPE == _TV_SEARCH_SHOW_FREQ)
void CShowAutoSearchSliderInOSD(WORD ucCurrentValue);
#else
void CShowAutoSearchSliderInOSD(BYTE ucCurrentValue);
#endif

void CShowAutoSerachTotal(BYTE ucSearchTotal);
bit CKeyStopAutoSearch(void);
void CShowTVNumber(const BYTE ucTvNumber, const BYTE ucOption);
extern bit CSearchedTVType(BYTE uctvtype);
extern void SInputCHNumber(void);
extern void SDirectnessInputCHNumber(void);

//--------------------------------------------------
#endif  //#if(_VIDEO_Sound_SUPPORT)

#endif  //#if(OSD_TYPE == OSD007)

