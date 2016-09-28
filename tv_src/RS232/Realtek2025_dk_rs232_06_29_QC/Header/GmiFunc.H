////////////////////////////////////////////////////////////////////////////
//         Copyright of Vector Co.,Ltd.                                   //
//                                                                        //
//                                                                        //
//                              GMI function                              //
//   Ver: 6.00                                                            //
//   Creat file time: 2006.5.15                                           //
//   End modify time: 2007.1.31                                           //
//   For RTD2523B/RTD2553V/RTD2525L                                       //
////////////////////////////////////////////////////////////////////////////
#if(_SET_VIDEO_MODE_METHOD == _TABLE) // Write table
// ucVideoMode:   _60HZ,_50HZ     
// ucDisplayMode: _DISPLAY_MODE_16_9,_DISPLAY_MODE_4_3
// ucScalerType:  _RTD2533B,_RTD2553V,_RTD2525L,_RTD2547D,_RTD2023L
void gmi_CSetMode(BYTE ucVideoMode, BYTE ucDisplayMode, BYTE ucScalerType);
#endif

bit gmi_CVideoIsExist(void);
bit gmi_CVideoModeChange(void);
bit gmi_CSourceScanInputPortVideo(void);
bit gmi_CVideoSyncHandler(void);
BYTE gmi_CRead9886(void);

void gmi_CInitial_IR(void);
void gmi_CStopIR(void);
void gmi_CStartIR(void);
void gmi_IR_Delay(void);
void gmi_CI2CWriteTuner(BYTE *Array);

void SetOSDRamAddress(BYTE Row_Count, BYTE Col_Count, WORD iFntBaseAddr);
void DirectWOSDRam(WORD iAddress, WORD iLen, BYTE TheByte, BYTE Value);
void SetRowCmds(BYTE ucRowCnt, BYTE ucRowLenght);
void Gotoxy(BYTE x, BYTE y, BYTE TheByte);
void OutputChar(BYTE C);
void CShowNumber(const WORD ucNumber, BYTE ucUserDefLong);
void COsdFxCloseWindow(BYTE ucWinID);
WORD ValueInRangeChange(WORD ucMin, WORD ucMax, WORD ucCur, BYTE ucOption, BYTE ucLoop);
void SetOSDDouble(BYTE ucAttr);





