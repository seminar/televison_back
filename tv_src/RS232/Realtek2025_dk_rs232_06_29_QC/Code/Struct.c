//----------------------------------------------------------------------------------------------------
// ID Code      : Struct.c No.0000
// Update Note  : 
//
//----------------------------------------------------------------------------------------------------

#include "Header\Include.h"


//--------------------------------------------------
// Global Variables
//--------------------------------------------------
StructModeUserDataType          xdata   stModeUserData;
StructModeUserCenterDataType    xdata   stModeUserCenterData;
StructSystemDataType            idata   stSystemData;
StructOsdUserDataType           idata   stOsdUserData;
StructAdcDataType               idata   stAdcData;
StructColorProc0DataType        xdata   stConBriData;
StructColorProc1DataType        xdata   stColorTempData;


ModeInformationType             xdata   stModeInfo;
DisplayTableType                xdata   stDisplayInfo;

#if(_VIDEO_SUPPORT)
StructVDCColor                  idata   stVDCColor;
#endif

