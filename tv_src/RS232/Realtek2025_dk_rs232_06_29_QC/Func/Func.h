
#define _ABS(VALUE1,VALUE2)      (VALUE1 > VALUE2 ? (VALUE1) - (VALUE2) : (VALUE2) - (VALUE1))


#ifdef __FUNCC__
#else
#endif

#if(VOLUME_CTRL_TYPE == _SOUND_SC7313)
void CSc7313MuteOn(void);
void CSetSc7313Volume(BYTE ucVolume);
void CSelect7313SoundChannel(BYTE ucChannel);

#endif

void CSetVolume();
void ChangeSource(void);
void CInitInputSource();
BYTE CGetADCData(BYTE ucADID);
void MUTE_ON();
void MUTE_OFF(void);
void CSetPWM(BYTE PWMId, BYTE Value);
#if(_MCU_TYPE == _MYSON_MTV512 || _MCU_TYPE == _RTD_2120)
void SetMCUPWM(BYTE PWMId, BYTE Value);
#endif
void CInitSoundChannel();


