//----------------------------------------------------------------------------------------------------
// ID Code      : Include.h No.0001
// Update Note  : 
//
//----------------------------------------------------------------------------------------------------

#include "reg52.h"
#include "intrins.h"
#include "math.h"
#include "string.h"

#include "gmiOSD\UserSetting\UserSetting.H"
#include "Header\Global.h"
#include "Header\Maindef.h"
#include "Pcb\Pcb.h"
#include "Header\VideoDec.h"

#include "Header\GmiFunc.h"
#include "Header\Struct.h"
#include "Header\ScalerDef.h"
#include "Header\Panel.h"



#include "Header\Scaler.h"
#include "Header\Mode.h"
#include "Header\Hdmi.h"
#include "Header\Memory.h"
#include "Header\ModeTable.h"
#include "Header\Power.h"
#include "Header\Timer.h"
#include "Header\FrameSync.h"
#include "Header\Eeprom.h"
#include "Header\Mcu.h"
#include "Header\Key.h"
#include "Header\I2c.h"
#include "Header\EepromDefault.h"
#include "Header\Sync.h"
#include "Header\Main.h"
#include "Header\SystemTable.h"
#include "Header\Source.h"
#include "Header\Misc.h"
#include "Header\Adjust.h"
#include "Header\Auto.h"
#include "Header\Video.h"
#include "Header\Uart.h"
#include "Header\YPbPr.h"

#include "DDC\DDC.H"
#include "DDC\DDCRTDEE.H"

#include "DDCCI\DDCCI.H"
#include "DDCCI\DDCCIDBG.H"

#include "Language\Langage.h"


#include "gmiOSD\gmiOSDFunc.h"    //new osd func

#include "FUNC\FUNC.h"

#include "LOGO\LOGO.h"

//TV
#include "TV\TV.H"

//Factory menu
#include "gmiOSD\FactoryMenu\Lcd_osdFac.h"
#include "gmiOSD\FactoryMenu\OsdFac.h"


//OSD07
#if(_OSD_TYPE == _OSD007)
#if(_USE_RTD2120_EXTEND_32K_FOR_OSD)
#include "gmiOSD\OSD007\RTD2120Extend\RTD2120OSDExtend.H"
#endif
#endif
#include "gmiOSD\OSD007\OsdPub007.H"
#include "gmiOSD\OSD007\OSDVGA007.H"
#include "gmiOSD\OSD007\OSDAV007.H"
#include "gmiOSD\OSD007\OSDTV007.H"

#include "IR\IR.h"


