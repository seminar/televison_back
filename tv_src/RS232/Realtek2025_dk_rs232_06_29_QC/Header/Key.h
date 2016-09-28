//----------------------------------------------------------------------------------------------------
// ID Code      : Key.h No.0000
// Update Note  : 
//
//----------------------------------------------------------------------------------------------------

//--------------------------------------------------
// Definitions of Key Repeat Start Time (Unit in sec)
//--------------------------------------------------
#define _KEY_REPEAT_START_TIME      0.5

//--------------------------------------------------
// Definitions of Key Mask
//--------------------------------------------------
#define _NONE_KEY_MASK              0x00
#define _POWER_KEY_MASK             0x01
#define _MENU_KEY_MASK              0x02
#define _RIGHT_KEY_MASK             0x03
#define _LEFT_KEY_MASK              0x04
#define _EXIT_KEY_MASK              0x06
#define _CH_INC_KEY_MASK            0x07
#define _CH_DEC_KEY_MASK            0x08
#define _FAC_KEY_MASK               0x09
//#define _IR_KEY_MASK                0x09
  /*
#define _POWER_RIGHT_KEY_MASK       (_POWER_KEY_MASK | _RIGHT_KEY_MASK)
#define _POWER_MENU_KEY_MASK        (_POWER_KEY_MASK | _MENU_KEY_MASK)
#define _POWER_LEFT_RIGHT_KEY_MASK  (_POWER_KEY_MASK | _LEFT_KEY_MASK | _RIGHT_KEY_MASK)
    */


//--------------------------------------------------
// Definitions of Key Message
//--------------------------------------------------
#define _MENU_KEY_MESSAGE           0x00
#define _RIGHT_KEY_MESSAGE          0x01
#define _LEFT_KEY_MESSAGE            0x02

#define _UP_KEY_MESSAGE                0xA6
#define _DOWN_KEY_MESSAGE           0xA7
#define _MUTE_KEY_MESSAGE            0xA8
#define _ENTER_KEY_MESSAGE          0xa9
#define _POWER_KEY_MESSAGE         0xaa
#define _INPUT_KEY_MESSAGE          0xab
//==========================
//下面是数字键
//==========================
#define  _NUM1_KEY_MESSAGE      0xac
#define  _NUM2_KEY_MESSAGE      0xad
#define  _NUM3_KEY_MESSAGE      0xae
#define  _NUM4_KEY_MESSAGE      0xaf
#define  _NUM5_KEY_MESSAGE      0xb0
#define  _NUM6_KEY_MESSAGE      0xb1
#define  _NUM7_KEY_MESSAGE      0xb2
#define  _NUM8_KEY_MESSAGE      0xb3
#define  _NUM9_KEY_MESSAGE      0xb4
#define  _NUM0_KEY_MESSAGE      0xb5
#define  _USB_KEY_MESSAGE        0xb6
#define  _DVD_KEY_MESSAGE        0xb7




#define _EXIT_KEY_MESSAGE           0x03
#define _CH_INC_KEY_MESSAGE         0x04
#define _CH_DEC_KEY_MESSAGE         0x05
#define _NONE_KEY_MESSAGE           0x08
#define _FAC_KEY_MESSAGE               0x09

#define _IR_MENU_KEY_MESSAGE          0x10
#define _IR_RIGHT_KEY_MESSAGE         0x11
#define _IR_LEFT_KEY_MESSAGE           0x12
#define _IR_SOURCE_KEY_MESSAGE      0x13
#define _IR_UP_KEY_MESSAGE               0x14
#define _IR_DOWN_KEY_MESSAGE         0x15
#define _IR_POWER_KEY_MESSAGE       0x16

#define _IR_VOLINC_KEY_MESSAGE      0x18
#define _IR_VOLDEC_KEY_MESSAGE      0x19
#define _IR_CHINC_KEY_MESSAGE       0x1a
#define _IR_CHDEC_KEY_MESSAGE       0x1b
#define _IR_DISPLAY_KEY_MESSAGE     0x1c
#define _IR_MUTE_KEY_MESSAGE        0x1d
#define _IR_SOUND_KEY_MESSAGE       0x1e
#define _IR_TVTYPE_KEY_MESSAGE      0x1f
#define _IR_RETURN_KEY_MESSAGE      0x20
#define _IR_INPUTCH_KEY_MESSAGE     0x21
//#define _IR_OK_KEY_MESSAGE          0x22
#define _IR_IMAGE_KEY_MESSAGE       0x22
#define _IR_ENTER_KEY_MESSAGE       0x24
#define _IR_VGATYPE_KEY_MESSAGE      0x25
#define _IR_AVTYPE_KEY_MESSAGE      0x26
#define _IR_SVTYPE_KEY_MESSAGE      0x27
#define _IR_SCARTTYPE_KEY_MESSAGE      0x28
#define IR_SLEEP_KEY_MESSAGE                0x29
#define _IR_HDMITYPE_KEY_MESSAGE      0x3C
#define _IR_DTVTYPE_KEY_MESSAGE      0x3D

#define _IR_NUM0_KEY_MESSAGE        0x30
#define _IR_NUM1_KEY_MESSAGE        0x31
#define _IR_NUM2_KEY_MESSAGE        0x32
#define _IR_NUM3_KEY_MESSAGE        0x33
#define _IR_NUM4_KEY_MESSAGE        0x34
#define _IR_NUM5_KEY_MESSAGE        0x35
#define _IR_NUM6_KEY_MESSAGE        0x36
#define _IR_NUM7_KEY_MESSAGE        0x37
#define _IR_NUM8_KEY_MESSAGE        0x38
#define _IR_NUM9_KEY_MESSAGE        0x39

#define _IR_OK_KEY_MESSAGE       0x3A
#define _IR_EXIT_KEY_MESSAGE       0x3B
#define _AUTO_KEY_MESSAGE           0xA5
#define _KEY_AMOUNT                 4
#if(DVD_EN)
#define KEY_0                0x00
#define KEY_1                0x01
#define KEY_2                0x02
#define KEY_3                0x03
#define KEY_4                0x04
#define KEY_5                0x05
#define KEY_6                0x06
#define KEY_7                0x07
#define KEY_8                0x08
#define KEY_9                0x09
#define KEY_POWER                      0x0a
#define KEY_DVD_EJECT                0x0b
#define KEY_RECALL                      0x0c
#define  KEY_MTS                           0x0d
#define  KEY_DVD_MENU                0x0e
#define  KEY_TTX_MIX                    0x0f
#define  KEY_PIP                             0x10
#define  KEY_UP                                0x11
#define  KEY_DOWN                           0x12
#define  KEY_LEFT                               0x13
#define  KEY_RIGHT                           0x14
#define  KEY_DVD_SLOW                    0x15
#define  KEY_TTX_LIST                       0x16
#define  KEY_TTX                                 0x17
#define  KEY_TTX_HOLD                       0x18
#define  KEY_TTX_CANCEL                     0x19
#define  KEY_TTX_INDEX                      0x1a
#define  KEY_MENU                                0x1b
#define  KEY_TTX_SUBTITLE                0x1c
#define   KEY_DVD_SELECT                  0x1d
#define  KEY_TTX_SIZE                       0x1e
#define  KEY_TTX_REVEAL                      0x1f
#define  KEY_TTX_RED                         0x20
#define  KEY_TTX_GREEN                      0x21
#define  KEY_TTX_YELLOW                      0x22
#define  KEY_TTX_CYAN                        0x23
#define  KEY_REPEAT                        0x24
#endif


//----------------------------------------------------------------------------------------------------

#ifdef __KEY__

//--------------------------------------------------
// Global Variables
//--------------------------------------------------
BYTE idata ucKeyControl;
BYTE idata ucKeyMessage;
BYTE idata ucKeyStatePrev;
BYTE idata ucKeyStateCurr;

#if(_BURNIN_EN)	
bit  ucBurninState=0;
#endif
//--------------------------------------------------
// Function Prototypes
//--------------------------------------------------
void CKeyHandler(void);
void CKeyCheckPowerKey(void);
void CKeyInitial(void);
bit CKeyScanReady(void);
void CKeyScanReadyTimerEvent(void);
void CKeyRepeatEnableTimerEvent(void);
void CKeyMessageConvert(BYTE ucKeyMask, BYTE ucKeyMsg);
BYTE CKeyScan(void);
void CKeyPowerKeyMix(void);
bit CKeyPowerKeyProc(void);
void CKeyMessageProc(void);
bit Burn_key(void);
#else

//--------------------------------------------------
// Extern Global Variables
//--------------------------------------------------
extern BYTE idata ucKeyControl;
extern BYTE idata ucKeyMessage;


//--------------------------------------------------
// Extern Function Prototypes
//--------------------------------------------------
extern void CKeyHandler(void);
extern void CKeyCheckPowerKey(void);
extern void CKeyInitial(void);
extern BYTE CKeyScan(void);

extern void CKeyPowerKeyMix(void);
extern bit Burn_key(void);

extern bit ucBurninState;
#endif


//----------------------------------------------------------------------------------------------------

//--------------------------------------------------
// Macro of Key Scan Ready Flag
//--------------------------------------------------
#define GET_KEYSCANREADY()          ((bit)(ucKeyControl & _BIT0))
#define SET_KEYSCANREADY()          (ucKeyControl |= _BIT0)
#define CLR_KEYSCANREADY()          (ucKeyControl &= ~_BIT0)


//--------------------------------------------------
// Macro of Key Scan Start Flag
//--------------------------------------------------
#define GET_KEYSCANSTART()          ((bit)(ucKeyControl & _BIT1))
#define SET_KEYSCANSTART()          (ucKeyControl |= _BIT1)
#define CLR_KEYSCANSTART()          (ucKeyControl &= ~_BIT1)


//--------------------------------------------------
// Macro of Key Repeat Start
//--------------------------------------------------
#define GET_KEYREPEATSTART()        (bit)(ucKeyControl & _BIT2)
#define SET_KEYREPEATSTART()        ucKeyControl |= _BIT2
#define CLR_KEYREPEATSTART()        ucKeyControl &= ~_BIT2


//--------------------------------------------------
// Macro of Key Repeat Function Enable
// If you want to use repeat function, please set this flag. If not, please clear it.
//--------------------------------------------------
#define GET_KEYREPEATENABLE()       (bit)(ucKeyControl & _BIT3)
#define SET_KEYREPEATENABLE()       ucKeyControl |= _BIT3
#define CLR_KEYREPEATENABLE()       ucKeyControl &= ~_BIT3


//----------------------------------------------------------------------------------------------------

