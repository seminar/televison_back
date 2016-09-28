////////////////////////////////////////////////////////////////////////////
//         Copyright of Vector Co.,Ltd.                                   //
//                                                                        //
//                                                                        //
//                  Analog/Video/TV source code                           //
//   Ver: V402b                                                            //
//   Create file time: 2006.5.15                                          //
//   End modify time:  2007.3.27                                          //
//   For RTD2523B/RTD2525L/RTD2553V/RTD2547D                              //
////////////////////////////////////////////////////////////////////////////

//----------------------------------------------------------------------------------------------------
// Basic Settings
//----------------------------------------------------------------------------------------------------


//--------------------------------------------------
// Debug Tool
//--------------------------------------------------
#define _ISPACK                          _ON
#define _RS232                       _ON//   _OFF
#define _GRS232						 	_ON


#define _ACPOWERON_RS232        _ON
#define _SUPPORTDDCCI                   _ON

#define _ISPACK_RTD                     0               //MUST OPEN _ISPACK
#define _ISPACK_MCU                     1			    //Must Open _ISPACK & SUPPORTDDCCI

#define _ISPACK_TYPE                    _ISPACK_MCU

#define _OSD_NORMAL					    0    // MUST CLOSE NEW_OSD_FUNC
#define _OSD001                         1    // A Empty OSD Templet    MUST OPEN NEW_OSD_FUNC
#define _OSD002                         2    // MUST OPEN NEW_OSD_FUNC
#define _OSD003                         3
#define _OSD004                         4    // not ready yet.
#define _OSD005                         5    // Rows OSD
#define _OSD006                         6    // TTL 757 Pannel
#define _OSD007                         7    // Ready

#define _OSD_TYPE 					    _OSD007

#if(_OSD_TYPE != _OSD_NORMAL) 
#define _NEW_OSD_FUNC					_ENABLE   // _ENABLE,_DISABLE    <Use new osd functions set to "_ENABLE">
#else
#define _NEW_OSD_FUNC					_DISABLE   // _ENABLE,_DISABLE
#endif

// MUST BE USE NEW_OSD_FUNC
#define _FACTORY_MENU_EN                1               // FONT BASE ADDRESS MSET BE MORE THAN (15 * 30 + 15 + 1) = 466(0x1d2)
#define _BURNIN_EN                      1

//_ON is for auto power down,_OFF is for auto sleep 
// add by chenlinfu 2007/10/18
#define _AUTO_SLEEP_POWERDOWN	_OFF		//_ON  _OFF

//--------------------------------------------------
// For logo type
//--------------------------------------------------
#define _LOGO_TYPE0                     0
#define _LOGO_TYPE1                     1

#define _LOGO_TYPE                      _LOGO_TYPE0


#define _NEW_YPBPR                      1

/*
_DDC_NONE,   
_DDC_RTD_CODE, _DCC_RTD_EEPROM, 
_DDC_MTV512, _DDC_RTD2120
*/
#define _DDC_TYPE                       _DDC_NONE//_DDC_RTD2120

//--------------------------------------------------
// Scalar Reset Type
//--------------------------------------------------
// _RESET_IN    <MCU reset Scaler>
// _RESET_OUT   <Scaler reset MCU>
#define _RESET_TYPE                     _RESET_OUT


//--------------------------------------------------
// Definations of Input Port Max Numbers 
//--------------------------------------------------
#define _INPUT_PORT_MAX                 _SOURCE_NONE

//--------------------------------------------------
// Definations of no signal auto change source function
//--------------------------------------------------
#define _AUTO_SCAN_SOURCE               _DISABLE   // _ENABLE,_DISABLE

//--------------------------------------------------
// For change source method
//--------------------------------------------------
#define _CHANGE_SOURCE_METHOD_0         0
#define _CHANGE_SOURCE_METHOD_1         1

#define _CHANGE_SOURCE_METHOD           _CHANGE_SOURCE_METHOD_0

// For _CHANGE_SOURCE_METHOD_0 delay time  20*_CHANGE_SOURCE_TIME
#define _CHANGE_SOURCE_TIME             60

//----------------------------------------------------------------------------------------------------
// Advance Settings
//----------------------------------------------------------------------------------------------------


//--------------------------------------------------
// Definitions of APLL1 M/N Code
//--------------------------------------------------
#define _APLL1_M_CODE                   25
#define _APLL1_N_CODE                   2


//--------------------------------------------------
// Definitions of DDS P Code
//--------------------------------------------------
#define _DDS_P_CODE                     23

//--------------------------------------------------
// Definitions of APLL Fast Lock
//--------------------------------------------------
#define _APLL_FAST_LOCK                 _ON

//--------------------------------------------------
// Definitions of DPLL N Code
//--------------------------------------------------
#define _DPLL_N_CODE                    8//16


//--------------------------------------------------
// Definitions of DPLL N Code
//--------------------------------------------------
#define _M2PLL_USE                      _OFF
#define _M2PLL_XTAL                     _XTAL12000K
#define _RTD_M2PLL_RATIO                (_RTD_XTAL / _M2PLL_XTAL)


//--------------------------------------------------
// Definitions of ADC Fine Tune Delay (Value == 0 ~ 7)
//--------------------------------------------------
#define _ADC_FINE_TUNE_DELAY_RED        0
#define _ADC_FINE_TUNE_DELAY_GREEN      0
#define _ADC_FINE_TUNE_DELAY_BLUE       0



//--------------------------------------------------
// DVI Long Cable Supported
//--------------------------------------------------
#define _DVI_LONG_CABLE_SUPPORT         _ON


//--------------------------------------------------
// HDCP Supported
//--------------------------------------------------
#define _HDCP_SUPPORT                   _ON

//--------------------------------------------------
// Peaking Filter and Coring Control Supported
//--------------------------------------------------
#define _VGA_COLOR_SUPPORT              _OFF    // _ON,_OFF

#define _VIDEO_VIVID_COLOR_SUPPORT      _ON    // _ON,_OFF


//--------------------------------------------------
// YPbPr Supported
//--------------------------------------------------
#define _DVI_DE_ONLY_SUPPORT            _OFF


//--------------------------------------------------
// DVI Long Cable Supported
//--------------------------------------------------
#define _DVI_I_SOURCE_SWITCH_SUPPORT    _OFF

//--------------------------------------------------
// Set Different Display Information by Mode
//--------------------------------------------------
#define _DISP_INFO_BY_MODE              _OFF


//--------------------------------------------------
// Set DClk Spread Spectrum Range
//--------------------------------------------------
#define _DCLK_SPREAD_RANGE              0


//--------------------------------------------------
// System Power Detection Support
//--------------------------------------------------
#define _SYSTEMPOWER_DETECT_SUPPORT     _OFF


//--------------------------------------------------
// Set Last Line Finetune Method
//--------------------------------------------------
/*
_LAST_LINE_METHOD_NONE, _LAST_LINE_METHOD_0
_LAST_LINE_METHOD_1,    _LAST_LINE_METHOD_2
*/
#define _LAST_LINE_FINETUNE             _LAST_LINE_METHOD_2
#define _LAST_LINE_TARGET               400 // For _LAST_LINE_METHOD_2


//--------------------------------------------------
// Set Adjusting Vertical Position Direction Method
//--------------------------------------------------
// _V_POSITION_METHOD_0, _V_POSITION_METHOD_1
#define _V_POSITION_DIRECTION           _V_POSITION_METHOD_0


//--------------------------------------------------
// RTD2553V Set Method of Hsync Type Detection for Analog Input 
//--------------------------------------------------
// _NORMAL_RUN, _AUTO_RUN
#define _HSYNC_TYPE_DETECTION           _AUTO_RUN

//----------------------------------------------------------------------------------------------------
// RTD2120 MCU or RTD2556N Advance Settings
//----------------------------------------------------------------------------------------------------

//--------------------------------------------------
// RTD2120 96K Support
//--------------------------------------------------
#define _USE_RTD2120_EXTEND_32K_FOR_OSD  _ON      // Use RTD2120 96K for OSD


//--------------------------------------------------
// Memory Location
//--------------------------------------------------
#define _EEPROM                         0
#define _FLASH                          1

#define _MEMORY_LOCATION                _EEPROM


//--------------------------------------------------
// Software Load Font Supported
//--------------------------------------------------
#define _SOFTWARE_LOAD_FONT             _ON

//--------------------------------------------------
// RTD2553V Hardware Load Font Supported (Only No Swap)
//--------------------------------------------------
#define _HARDWARE_LOAD_FONT             _OFF



//----------------------------------------------------------------------------------------------------
// RTD2525L Advance Settings
//----------------------------------------------------------------------------------------------------

//--------------------------------------------------
// RTD2525L/RTD2528R Set Adjusting ADC offset Method
//--------------------------------------------------
#define _ADJUST_BY_FW                   0   //Adjust ADC offset by F/W
#define _ADJUST_BY_HW_OFF_LINE          1   //Enable Auto Black Level of H/W in Off-line Mode
#define _ADJUST_BY_HW_ON_LINE           2   //Enable Auto Black Level of H/W in On-line Mode  // This mode not use

#define _ADC_OFFSET_ADJUSTING           _ADJUST_BY_FW



//--------------------------------------------------
// RTD2525L System Power Detection Support
//--------------------------------------------------
#define _RESET_CHECK_SUPPORT            _OFF


//--------------------------------------------------
// For video display video set method
//--------------------------------------------------
#define _PROGRAM_AUTO                   0 // Normal
#define _TABLE                          1
#define _SET_VIDEO_MODE_METHOD          _TABLE

//----------------------------------------------------------------------------------------------------
// Other Advance Settings
//----------------------------------------------------------------------------------------------------

//--------------------------------------------------
// TMDS Shrink Support
//--------------------------------------------------
#define _TMDS_SHRINK_SUPPORT            _OFF
#define _TMDS_SHRINK_RANGE              20





