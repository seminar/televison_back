//----------------------------------------------------------------------------------------------------
// ID Code      : Ddc.h No.0000
// Update Note  : 
//
//----------------------------------------------------------------------------------------------------

#if(_DDC_TYPE != _DDC_NONE)

void DDCInit();
void DDCProc();

#if(_DDC_TYPE == _DDC_RTD_CODE)
void LoadCodeDDCToRTD(BYTE code *tVGADDC,BYTE ucRTDAddr);
#endif    //#if(DDC_TYPE == DDC_RTD_CODE)

#if(_DDC_TYPE == _DDC_MTV512)
void InitMTV512CodeDDC();
#endif  
       
#if(_DDC_TYPE == _DDC_MTV512 || _DDC_TYPE == _DDC_RTD2120)
void LoadCodeDDCToMCU(BYTE code *tDDC, BYTE xdata * ucMCUAddr);
#endif         
#endif    //#if(DDC_TYPE != DDC_NONE)
