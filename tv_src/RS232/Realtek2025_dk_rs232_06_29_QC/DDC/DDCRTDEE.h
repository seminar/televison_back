#if(_DDC_TYPE == _DDC_RTD_CODE)

void RTDDDCProc(void);
void RTDDDCProc1(BYTE ucEEPRamAddr,BYTE ucRTDAddr);
void LoadEEDDCToRTD(BYTE ucEEPRamAddr,BYTE ucRTDAddr);
void SaveRTDDDCToEE(BYTE ucEEPRamAddr,BYTE ucRTDAddr);

#endif    //#if(DDC_TYPE == DDC_RTD_CODE)