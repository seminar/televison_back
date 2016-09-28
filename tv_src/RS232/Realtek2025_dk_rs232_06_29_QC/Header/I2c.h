//----------------------------------------------------------------------------------------------------
// ID Code      : I2c.h No.0000
// Update Note  : 
//
//----------------------------------------------------------------------------------------------------

//--------------------------------------------------
// Definitions of I2c.c
//--------------------------------------------------
#define _I2C_WRITE_SIZE                 16
#define _I2C_TIMEOUT_LIMIT              255

#define _I2C_BUSY                       0
#define _I2C_OK                         1

#define _I2C_WR                         0
#define _I2C_RD                         1


//----------------------------------------------------------------------------------------------------

#ifdef __I2C__

//--------------------------------------------------
// Global Variables
//--------------------------------------------------


//--------------------------------------------------
// Function Prototypes
//--------------------------------------------------
void SETI2CSDA(void);
void CLRI2CSDA(void);

void SETI2CSCL(void);
void CLRI2CSCL(void);

void Delay5us(void);
void Delay3us(void);
BYTE CI2cStart(BYTE ucDeviceAddr);
void CI2cStop(void);
BYTE CI2cGetAck(void);
void CI2cSendAck(void);
BYTE CI2cSendByte(BYTE ucValue);
BYTE CI2cGetByte(void);
bit CI2cRead(BYTE ucDeviceAddr, BYTE ucStartAddr, WORD usLength, BYTE *pReadArray);
bit CI2cWrite(BYTE ucDeviceAddr, BYTE ucStartAddr, WORD usLength, BYTE *pWriteArray);


#else

//--------------------------------------------------
// Extern Global Variables
//--------------------------------------------------


//--------------------------------------------------
// Extern Function Prototypes
//--------------------------------------------------
extern void SETI2CSDA(void);
extern void CLRI2CSDA(void);
extern void CHECKI2CSDA(void);

extern void SETI2CSCL(void);
extern void CLRI2CSCL(void);
extern void CHECKI2CSCL(void);

extern void Delay5us(void);
extern void Delay3us(void);
extern BYTE CI2cStart(BYTE ucDeviceAddr);
extern void CI2cStop(void);
extern BYTE CI2cGetAck(void);
extern void CI2cSendAck(void);
extern BYTE CI2cSendByte(BYTE ucValue);
extern BYTE CI2cGetByte(void);
extern bit CI2cRead(BYTE ucDeviceAddr, BYTE ucStartAddr, WORD usLength, BYTE *pReadArray);
extern bit CI2cWrite(BYTE ucDeviceAddr, BYTE ucStartAddr, WORD usLength, BYTE *pWriteArray);


#endif

/* 
//----------------------------------------------------------------------------------------------------

//--------------------------------------------------
// Macro of I2c.c
//--------------------------------------------------
#define SETI2CSDA()                 (bI2CSDA = _TRUE)
#define CLRI2CSDA()                 (bI2CSDA = _FALSE)
#define CHECKI2CSDA()               (bI2CSDA)

#define SETI2CSCL()                 (bI2CSCL = _TRUE)
#define CLRI2CSCL()                 (bI2CSCL = _FALSE)
#define CHECKI2CSCL()               (bI2CSCL)
*/
#define CHECKI2CSDA()               (bI2CSDA)
#define CHECKI2CSCL()               (bI2CSCL)
