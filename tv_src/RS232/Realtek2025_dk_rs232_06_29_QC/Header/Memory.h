//----------------------------------------------------------------------------------------------------
// ID Code      : RTD2528R_Memory.h No.0000
// Update Note  : 
//
//----------------------------------------------------------------------------------------------------

//--------------------------------------------------
// Definitions of Compress Group Number
//--------------------------------------------------
#define _COMPRESS_GROUP_NUMBER          0x320   //800 pixel

//--------------------------------------------------
// Definitions of OD start address 
//--------------------------------------------------
#define _OD_START_ADDRESS               0x000000

//--------------------------------------------------
// Definitions of FRC address 
//--------------------------------------------------
#define _FRC_1ST_BLOCK_STA_ADDR         0x000000
#if(_MEMORY_SIZE < _MEMORY_64MB)
#define _FRC_2ND_BLOCK_STA_ADDR         0x200000
#else
#define _FRC_2ND_BLOCK_STA_ADDR         0x400000
#endif

//--------------------------------------------------
// Definitions of Low Bit Noise Reduction Threshold 
//--------------------------------------------------
#define _OD_LBNRT_ENABLE                _ON
#define _OD_LBNRT_MODE                  _NEWMODE
#define _OD_LBNRT_LEVEL                 1   // level-6

//--------------------------------------------------
// Definitions of OD Channel
//--------------------------------------------------
#define _OD_TABLE_SINGLY        0
#define _OD_TABLE_COMMON        3

#if(0)

#define _OD_TABLE_NULL          0
#define _OD_TABLE_LOW           1
#define _OD_TABLE_MIDDLE        2
#define _OD_TABLE_LARGE         3

#elif(1)

#define _OD_TABLE_MIDDLE        0

#endif
//----------------------------------------------------------------------------------------------------

#ifdef __RTD2547D_MEMORY__

#if(_OD_SUPPORT == _ON)

//--------------------------------------------------
// Global OD Table
//--------------------------------------------------

#if((_MCU_TYPE == _REALTEK_RTD2120) && (_RTD2120_96K_SUPPORT == _ON))

#if(0)

BYTE xdata tOD_TABLE_NULL[_OD_TABLE_NULL_EXTEND]                _at_ _OD_TABLE_NULL_EXTEND_ADDRESS;
BYTE xdata tOD_TABLE_LOW[_OD_TABLE_LOW_EXTEND]                  _at_ _OD_TABLE_LOW_EXTEND_ADDRESS;
BYTE xdata tOD_TABLE_MIDDLE[_OD_TABLE_MIDDLE_EXTEND]            _at_ _OD_TABLE_MIDDLE_EXTEND_ADDRESS;
BYTE xdata tOD_TABLE_LARGE[_OD_TABLE_LARGE_EXTEND]              _at_ _OD_TABLE_LARGE_EXTEND_ADDRESS;

code BYTE *tOD_TABLE[] =
{
    tOD_TABLE_NULL,     tOD_TABLE_LOW,     tOD_TABLE_MIDDLE,     tOD_TABLE_LARGE,
};

#elif(1)

BYTE xdata tOD_TABLE_MIDDLE[_OD_TABLE_MIDDLE_EXTEND]            _at_ _OD_TABLE_MIDDLE_EXTEND_ADDRESS;

code BYTE *tOD_TABLE[] =
{
    tOD_TABLE_MIDDLE,
};

#endif

#elif ((_MCU_TYPE != _REALTEK_RTD2120) || (_RTD2120_96K_SUPPORT == _OFF))

BYTE code tOD_TABLE_NULL[] = 
{
0x00,
};

BYTE code tOD_TABLE_LOW[] = 
{
0x00,
};

BYTE code tOD_TABLE_MIDDLE[] = 
{
0x00,
};

BYTE code tOD_TABLE_LARGE[] = 
{
0x00,
};

code BYTE *tOD_TABLE[] =
{
    tOD_TABLE_NULL,     tOD_TABLE_LOW,     tOD_TABLE_MIDDLE,     tOD_TABLE_LARGE,
};

#endif // end of #if((_MCU_TYPE != _REALTEK_RTD2120) || (_RTD2120_96K_SUPPORT == _OFF))

#endif //End of #if(_OD_SUPPORT == _ON)
//--------------------------------------------------
// Global Variables
//--------------------------------------------------
BYTE idata ucMemoryCtrl = 0;


//--------------------------------------------------
// Function Prototypes
//--------------------------------------------------
void CMemorySDRAMReset(void);
void CMemoryLoadODLUT(BYTE ucColor);
void CMemoryLoadODTable(BYTE *pChannelArray);
void CMemorySetODOnOff(BYTE ucSelect);
void CMemorySetODCompress(void);
void CMemorySetODFIFO(void);
void CMemoryControlForFRC(WORD ucHorSize, WORD ucVerSize);
void CMemoryCtrlForFRCInput(WORD ucHorSize, WORD ucVerSize);
void CMemoryCtrlForFRCDisplay(WORD ucHorSize, WORD ucVerSize);
DWORD CMemoryCalculateNumberAndRemain(DWORD ucTotalSize, BYTE ucLength, bit bDummy);
DWORD CMemoryCalculateLineStepAndBlockStep(WORD ucHorSize, WORD ucVerSize);

#else

//--------------------------------------------------
// Extern Global OD Table
//--------------------------------------------------
#if(_OD_SUPPORT == _ON)
extern code BYTE *tOD_TABLE[];
#endif //End of #if(_OD_SUPPORT == _ON)


//--------------------------------------------------
// Extern Global Variables
//--------------------------------------------------
extern BYTE idata ucMemoryCtrl;


//--------------------------------------------------
// Extern Function Prototypes
//--------------------------------------------------
extern void CMemorySDRAMReset(void);
extern void CMemoryLoadODLUT(BYTE ucColor);
extern void CMemoryLoadODTable(BYTE *pChannelArray);
extern void CMemorySetODOnOff(BYTE ucSelect);
extern void CMemorySetODCompress(void);
extern void CMemorySetODFIFO(void);
extern void CMemoryControlForFRC(WORD ucHorSize, WORD ucVerSize);
extern void CMemoryCtrlForFRCInput(WORD ucHorSize, WORD ucVerSize);
extern void CMemoryCtrlForFRCDisplay(WORD ucHorSize, WORD ucVerSize);
extern DWORD CMemoryCalculateNumberAndRemain(DWORD ucTotalSize, BYTE ucLength, bit bDummy);
extern DWORD CMemoryCalculateLineStepAndBlockStep(WORD ucHorSize, WORD ucVerSize);


#endif


//----------------------------------------------------------------------------------------------------

//--------------------------------------------------
// Macro of FRC Status
//--------------------------------------------------
#define GET_FRCTATUS()              (bit)(ucMemoryCtrl & _BIT0)
#define SET_FRCTATUS()              ucMemoryCtrl |= _BIT0
#define CLR_FRCTATUS()              ucMemoryCtrl &= ~_BIT0





//----------------------------------------------------------------------------------------------------


