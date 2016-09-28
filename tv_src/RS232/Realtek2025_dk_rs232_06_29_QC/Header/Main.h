//----------------------------------------------------------------------------------------------------
// ID Code      : Main.h No.0000
// Update Note  : 
//
//----------------------------------------------------------------------------------------------------

//--------------------------------------------------
// Definitions of
//--------------------------------------------------


//----------------------------------------------------------------------------------------------------

#ifdef __MAIN__

//--------------------------------------------------
// Global Variables
//--------------------------------------------------
BYTE data pData[16];
BYTE    Keycode  =0xff;
#if(IR_Test_EN== _ON)    
BYTE data CUSTOM_CODE_STATE_H=0;
BYTE data CUSTOM_CODE_STATE_L=0;
BYTE data CMD_DATA_INFO=0;
#endif
/*
#if(_RS232==_ON)
bit ShowVideoInfo=0;
bit ShowVideoInfo_av=0;
bit ShowVideoInfo_sv=0;
BYTE data ucOsdState_INFO=0;
BYTE data ucKeyMessage_INFO=0;
 #endif
 */
//--------------------------------------------------
// Function Prototypes
//--------------------------------------------------
void CMainUserInitial();
bit CMainDetectSystemPower(void);
bit CMainResetCheck(void); //V306 modify
void CMainSystemInitial(void);


#else

//--------------------------------------------------
// Extern Global Variables
//--------------------------------------------------
extern BYTE data pData[16];
#if(IR_Test_EN== _ON)    
extern BYTE data CUSTOM_CODE_STATE_H;
extern BYTE data CUSTOM_CODE_STATE_L;
extern BYTE data CMD_DATA_INFO;
#endif
extern  BYTE Keycode;

/*
#if(_RS232==_ON)
extern bit ShowVideoInfo;
extern bit ShowVideoInfo_av;
extern bit ShowVideoInfo_sv;
extern BYTE data ucOsdState_INFO;
extern BYTE data ucKeyMessage_INFO;

#endif
*/
//--------------------------------------------------
// Extern Function Prototypes
//--------------------------------------------------


#endif


//----------------------------------------------------------------------------------------------------

