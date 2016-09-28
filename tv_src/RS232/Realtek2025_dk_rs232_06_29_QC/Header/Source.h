//----------------------------------------------------------------------------------------------------
// ID Code      : Source.h No.0002
// Update Note  : 
//
//----------------------------------------------------------------------------------------------------

//--------------------------------------------------
// Definitions of
//--------------------------------------------------
#define _ANALOG_SOURCE_0                    0
#define _ANALOG_SOURCE_1                    1

#define _DE_ONLY_OFF                        0
#define _DE_ONLY_ON                         1


//----------------------------------------------------------------------------------------------------

#ifdef __SOURCE__

//--------------------------------------------------
// Global Variables
//--------------------------------------------------


//--------------------------------------------------
// Function Prototypes
//--------------------------------------------------
bit CSourceHandler(void);
void CSourceScanInputPort(BYTE ucInputPort);
bit CSourceScanInputPortVGA(BYTE ucAnalogSource);
bit CSourceScanInputPortDVI(BYTE ucPar);
void CSourceSwitchInputPort(BYTE ucSelect);
void CSourceSelectInputPort(void);

BYTE CGetSourcePortType(BYTE ucSource);
bit bSourceVideo(void);

#else

//--------------------------------------------------
// Extern Global Variables
//--------------------------------------------------


//--------------------------------------------------
// Extern Function Prototypes
//--------------------------------------------------
extern bit CSourceHandler(void);
extern bit CSourceScanInputPortDVI(BYTE ucPar);
extern bit bSourceVideo(void);

extern BYTE CGetSourcePortType(BYTE ucSource);
#endif


