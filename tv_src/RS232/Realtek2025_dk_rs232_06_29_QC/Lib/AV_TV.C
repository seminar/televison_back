////////////////////////////////////////////////////////////////////////////
//         Copyright of Vector Co.,Ltd.                                   //
//                                                                        //
//                                                                        //
//                              AV TV function                            //
//   Ver: 0.00                                                            //
//   Creat file time: 2006.7.31                                           //
//   End modify time: 2006.7.31                                           //
//   For RTD2523B/RTD2553V/RTD2525L                                       //
////////////////////////////////////////////////////////////////////////////

#include "Header\Include.h"

#define _VIDEO_READY         1  // 0: no video
#define _TV_READY            1  // 0: no tv
#define _SMALL_SOURCE_CODE   0  // 1: small source


//////////////////////////////////////////////////////////////////////////////////////////////////
//
//                            VIDEO FUNCTION
//
//////////////////////////////////////////////////////////////////////////////////////////////////

bit bBuleBackGround = 0;  // 0: Blue back ground off      1: Blue back ground on
BYTE ucTVNoModeTime = 0;

#if(_VIDEO_READY)
#if(_TV_READY)

#define _TV_CHANGE_MODE_TIME_  90

BYTE ucTVChangeModeTime = 0;

//==============================================================================  
// Routine Name: 
// Input Value :  _BLUE_BACK_GROUND_DISABLE --> off
//                _BLUE_BACK_GROUND_ENABLE: --> on
// Output Value: 
// Description :  Set bule background on/off
//============================================================================== 
#define _BLUE_BACK_GROUND_ENABLE        1
#define _BLUE_BACK_GROUND_DISABLE       0
#define _SIGNAL_READY_STATE             1
#define _NO_SIGNAL_STATE                0
#define _NO_MODE_TIME_COUNT             250
void CSetBlueBackGround(const bit bOnOff)
{
    bBuleBackGround = bOnOff;

    if (_BLUE_BACK_GROUND_ENABLE == bOnOff)
    {
        CScalerSetBit(0x28, ~_BIT5, _BIT5); // Set force to background color enable
#if(_CHANGE_SOURCE_BACKGROUCD_COLOR==_BACK_COLOR)					    	
		CAdjustBackgroundColor(0x00, 0x00, 0x00);     
#else
		CAdjustBackgroundColor(0x00, 0x00, 0xFF);     
#endif
   }
    else
    {
        CScalerSetBit(0x28, ~_BIT5, 0x00); // Set force to background color disable
    }
}

//==============================================================================  
// Routine Name: 
// Input Value :  _SIGNAL_READY_STATE/_NO_SIGNAL_STATE 
// Output Value: 
// Description :  Bule background on/off handler
//============================================================================== 
void CBlueBackGroundHandler(const bit bSignalState)
{
    if (!((stSystemData.MonitorFlag & _BIT6) >> 6))  // Blue backgournd disable
    {
        ucTVNoModeTime = 0;

        if (bBuleBackGround) // Blue background was enable,so set blue background disable
            CSetBlueBackGround(_BLUE_BACK_GROUND_DISABLE);

    }
    else
    {
        if (_SIGNAL_READY_STATE == bSignalState)  
        {
            if (_BLUE_BACK_GROUND_ENABLE == bBuleBackGround)  // Blue background was enable
            {
                ucTVNoModeTime++;

                if (ucTVNoModeTime > _NO_MODE_TIME_COUNT)
                {
                   ucTVNoModeTime = 0;
                   CSetBlueBackGround(_BLUE_BACK_GROUND_DISABLE);
               }
            }
            else
                ucTVNoModeTime = 0;
        }
        else  // No signal state
        {
            if (_BLUE_BACK_GROUND_DISABLE == bBuleBackGround) // Blue background was disable
            {
                ucTVNoModeTime++;

                if (ucTVNoModeTime > _NO_MODE_TIME_COUNT)
                {
                    ucTVNoModeTime = 0;
                    CSetBlueBackGround(_BLUE_BACK_GROUND_ENABLE);
                }
            }
            else
                ucTVNoModeTime = 0;
        }
    }
}

//==============================================================================  
BYTE CGetCurrentTvColor(void)
{
    switch(ucTVType) 
    {
    case _TV_NTSC_M    :    // 60Hz Sound 4.5M  NTSC M
    case _TV_NTSC_4_BG :    // 60Hz Sound 5.5M  NTSC 4/BG 
    case _TV_NTSC_4_DK :    // 60Hz Sound 6.5M  NTSC 4/DK 
    case _TV_NTSC_4_I  :    // 60Hz Sound 6.0M  NTSC 4/I
    case _TV_PAL_M     :    // 60Hz Sound 4.5M  PAL M  
        return _60HZ;

    case _TV_PAL_BG    :    // 50Hz Sound 5.5M  PAL B/G
    case _TV_PAL_I     :    // 50Hz Sound 6.0M  PAL I
    case _TV_PAL_DK    :    // 50Hz Sound 6.5M  PAL D/K
    case _TV_PAL_N     :    // 50Hz Sound 4.5M  PAL N 
    case _TV_SECAM_BG  :    // 50Hz Sound 5.5M  SECAM B/G
    case _TV_SECAM_DK  :    // 50Hz Sound 6.5M  SECAM D/K
    case _TV_SECAM_L   :    // 50Hz Sound 6.5M  SECAM L  
    case _TV_SECAM_LL  :    // 50Hz Sound 6.5M  Secam L' 
        return _50HZ;
    } // end switch 

    return 0;
}
#endif

//==============================================================================  
// Routine Name: bit CVideoIsExist(bit InputChannel)
// Input Value : Null
// Output Value: 0->Non-Exist  / 1->Exist
// Description : Check Video Channel if Signal Exist
//============================================================================== 
bit gmi_CVideoIsExist(void)
{
    // eric add for TB1334 change channel not blue screen
    if (bChangeChannel)
       bBuleBackGround = _BLUE_BACK_GROUND_DISABLE;

    if(!gmi_CModeLocked()) // No Locked 
    {
#if(_TV_READY)
        if (stSystemData.InputSource != _SOURCE_VIDEO_TV)
            return _FALSE;

        {
            BYTE ucCurrentColor = CGetCurrentTvColor();  // Modify by eric 0825
    
            CBlueBackGroundHandler(_NO_SIGNAL_STATE);


            if(ucCurrentColor == VideoType)
            {
                stModeInfo.ModeCurr = _VIDEO_EXIST;
                ucTVChangeModeTime  = 0;
                return _TRUE;
            }
        }
#endif
        return _FALSE;
    }        
  
    {
        BYTE ucCurrent_Color = gmi_CVideoCurrentColor(0);
        
        switch(ucCurrent_Color)
        {
        case 0: // No color(TB1334) or no signal(Other VDC)
            stModeInfo.ModeCurr = _VIDEO_EXIST;
            return _TRUE;

        case _VIDEO_COLOR_PAL:
            ucCurrent_Color = _50HZ;
            break;

        case _VIDEO_COLOR_NTSC:
            ucCurrent_Color = _60HZ;
            break;
        }
//-------------------------------------------------------------
        
#if(_TV_READY)
        CBlueBackGroundHandler(_SIGNAL_READY_STATE);
#endif

        if(ucCurrent_Color == VideoType)
        {
#if(_TV_READY)
            ucTVChangeModeTime  = 0;
#endif
            stModeInfo.ModeCurr = _VIDEO_EXIST;
            return _TRUE;
        }

#if(_TV_READY)
        ucTVChangeModeTime++;

        if (stSystemData.InputSource != _SOURCE_VIDEO_TV || ucTVChangeModeTime > _TV_CHANGE_MODE_TIME_ || bChangeChannel)
#endif
            return _FALSE;
    }
}     /*
#undef _BLUE_BACK_GROUND_ENABLE        
#undef _BLUE_BACK_GROUND_DISABLE       
#undef _SIGNAL_READY_STATE             
#undef _NO_SIGNAL_STATE                
#undef _NO_MODE_TIME_COUNT             
        */
//==============================================================================  
// Routine Name: bit CVideoModeChange(void)
// Input Value : Null
// Output Value: 0 --> Mode not changed     1 --> Mode changed
// Description : Set current mode rate
//============================================================================== 
bit gmi_CVideoModeChange(void)
{
    bit bTVModeNoLocked = 0;

  
    ucTVNoModeTime  = 0;
    bBuleBackGround = 0;

    if (!gmi_CModeLocked()) // No Locked 
    {
#if(_TV_READY)
        if (stSystemData.InputSource == _SOURCE_VIDEO_TV)
            bTVModeNoLocked = 1;
        else
#endif
        {
            stModeInfo.ModeCurr = _MODE_NOSIGNAL;
            RECODE_NONE_VIDEO();
            return _FALSE;
        }
    }
    
    {
        BYTE ucCurrentColor = (_VIDEO_COLOR_PAL == gmi_CVideoCurrentColor(0)) ? _50HZ : _60HZ;

#if(_TV_READY)
        if (stSystemData.InputSource == _SOURCE_VIDEO_TV && bTVModeNoLocked)
            ucCurrentColor = CGetCurrentTvColor();  // Modify by eric 0825
#endif
        
        if (_50HZ == ucCurrentColor)
            RECODE50HZ();
        else //if (_VIDEO_COLOR_NTSC == ucCurrent_Color)
            RECODE60HZ();
    }
    
    if (VideoType != 0)
    {
        stModeInfo.ModeCurr = _VIDEO_EXIST;
        return _TRUE;
    }
    else
    {
        stModeInfo.ModeCurr = _VIDEO_NOT_EXIST;
        RECODE_NONE_VIDEO();
        return _FALSE;
    }
}

//==============================================================================  
// Routine Name: bit CSourceScanInputPortVideo()
// Input Value : Null
// Output Value: 0 --> Video no locked       1 --> Video locked
// Description : Check video signal
//============================================================================== 
bit gmi_CSourceScanInputPortVideo(void)  // eric 0505
{

    if (gmi_CModeLocked() || stSystemData.InputSource == _SOURCE_VIDEO_TV) // eric 0506 modify
        return _TRUE;
    else
        return _FALSE;   
}

//==============================================================================  
// Routine Name: bit CVideoSyncHandler(void)
// Input Value : Null
// Output Value: 0 --> Sync error      1 --> Sync ok
// Description : Check input sync
//============================================================================== 
bit gmi_CVideoSyncHandler(void)
{
    ucTVNoModeTime  = 0;
    bBuleBackGround = 0;

   	if (stSystemData.InputSource == _SOURCE_VIDEO_TV && !((stSystemData.MonitorFlag & _BIT6) >> 6))
	{
#if(!_SMALL_SOURCE_CODE)
        ucInputSyncType = _VIDEO8_STATE;
        bInputSignalAvailable = 1;
#endif
        CScalerSetBit(_SYNC_CTRL_49, ~(_BIT1 | _BIT0), _BIT0);
        return _TRUE;
	}	 
    
    if (gmi_CSourceScanInputPortVideo())
    {
#if(_SMALL_SOURCE_CODE)
         return _TRUE;
#else
         ucInputSyncType = _VIDEO8_STATE;
         bInputSignalAvailable = 1;
#endif
    }
    else
    {
#if(_SMALL_SOURCE_CODE)
         return _FALSE;
#else
         ucInputSyncType = _NO_SYNC_STATE;
         bInputSignalAvailable = 0;
#endif
    }


#if(!_SMALL_SOURCE_CODE)
    if(ucInputSyncType == _NO_SYNC_STATE)
    {
         return _FALSE;
    }
    else
    {
        CScalerSetBit(_SYNC_CTRL_49, ~(_BIT1 | _BIT0), _BIT0);
        return _TRUE;
    }
#endif
}
#endif




