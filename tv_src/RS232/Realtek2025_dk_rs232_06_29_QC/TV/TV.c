#include "Header\Include.h"

#if(_VIDEO_TV_SUPPORT)
bit bChangeChannel              = 0;
BYTE idata ucTVType             = _NORMAL_TV_TYPE;
BYTE xdata ucPrevChannel        = 0;
WORD xdata ucCurrentInputNumber = 0;
BYTE xdata ucCurrentInputState  = 0;

//add the NTSC table
#if(_NTSC_SEARCH_TABLE)
//-------------------------------------------------------------------------
WORD code tNTSC_AIR[MAX_CHANNEL_AIR] =
{
    ((55.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),    // 0
    ((55.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),    // 1
    ((55.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),    // 2
    ((61.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),    // 3
    ((67.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),   // 4
    ((77.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),    // 5
    ((83.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),    // 6
    ((175.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),  // 7
    ((181.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),   // 8
    ((187.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),   // 9
    ((193.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),   // 10
    ((199.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),   // 11
    ((205.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),  // 12
    ((211.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),  // 13
    ((471.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),   // 14
    ((477.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),   // 15
    ((483.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),  // 16
    ((489.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),   // 17
    ((495.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),   // 18
    ((501.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),   // 19
    ((507.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),   // 20
    ((513.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),   // 21
    ((519.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),   // 22
    ((525.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),   // 23
    ((531.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),   // 24
    ((537.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),   // 25
    ((543.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),  // 26
    ((549.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),   // 27
    ((555.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),   // 28
    ((561.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))), // 29
    ((567.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),   // 30
    ((573.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),  // 31
    ((579.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),   // 32
    ((585.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),   // 33
    ((591.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),   // 34
    ((597.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),   // 35
    ((603.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),   // 36
    ((609.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))), // 37
    ((615.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),  // 38
    ((621.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),  // 39
    ((627.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))), // 40
    ((633.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),   // 41
    ((639.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),   // 42
    ((645.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),  // 43
    ((651.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))), // 44
    ((657.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))), // 45
    ((663.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),  // 46
    ((669.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),  // 47
    ((675.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),   // 48
    ((681.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),   // 49
    ((687.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),  // 50
    ((693.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),   // 51
    ((699.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))), // 52
    ((705.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),   // 53
    ((711.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),   // 54
    ((717.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),  // 55
    ((723.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),  // 56
    ((729.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))), // 57
    ((735.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),   // 58
    ((741.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),   // 59
    ((747.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),  // 60
    ((753.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),  // 61
    ((759.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),   // 62
    ((765.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),   // 63
    ((771.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),   // 64
    ((777.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),  // 65
    ((783.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),  // 66
    ((789.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),  // 67
    ((795.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),   // 68
    ((801.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),  // 69
};                
                  
//-------------------------------------------------------------------------
WORD code tNTSC_CATV[MAX_CHANNEL_CATV] =
{                 
     ((55.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),   // 0 
     ((73.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),  // 1
     ((55.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),  // 2
     ((61.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),   // 3
     ((67.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),    // 4
     ((77.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),    // 5
     ((83.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),    // 6
     ((175.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),   // 7 
     ((181.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),   // 8 
     ((187.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),   // 9 
     ((193.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),  // 10
     ((199.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),   // 11
     ((205.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),  // 12
     ((211.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),   // 13
     ((121.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),  // 14 
     ((127.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),   // 15 
     ((133.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),  // 16
     ((139.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),  // 17
     ((145.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),   // 18
     ((151.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),   // 19
     ((157.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))), // 20
     ((163.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),   // 21
     ((169.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),  // 22
     ((217.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),  // 23
     ((223.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),  // 24
     ((229.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),   // 25
     ((235.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),  // 26
     ((241.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),   // 27
     ((247.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),   // 28
     ((253.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),   // 29
     ((259.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),  // 30
     ((265.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),   // 31
     ((271.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),  // 32
     ((277.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),   // 33
     ((283.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),   // 34
     ((289.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),   // 35
     ((295.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),   // 36
     ((301.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),  // 37
     ((307.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),   // 38
     ((313.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),  // 39
     ((319.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),   // 40
     ((325.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),   // 41
     ((331.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),  // 42
     ((337.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),   // 43
     ((343.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),  // 44
     ((349.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))), // 45
     ((355.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),   // 46
     ((361.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),   // 47
     ((367.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),  // 48
     ((373.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),   // 49
     ((379.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),  // 50
     ((385.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),   // 51
     ((391.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),  // 52
     ((397.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),  // 53
     ((403.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),   // 54
     ((409.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),  // 55
     ((415.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),  // 56
     ((421.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),   // 57
     ((427.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),   // 58
     ((433.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),  // 59
     ((439.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),  // 60
     ((445.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),   // 61
     ((451.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),   // 62
     ((457.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),  // 63
     ((463.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),   // 64
     ((469.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),   // 65
     ((475.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),   // 66
     ((481.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),  // 67
     ((487.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),  // 68
     ((493.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),  // 69
     ((499.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))), // 70
     ((505.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),  // 71
     ((511.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),   // 72
     ((517.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),   // 73
     ((523.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),   // 74
     ((529.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),   // 75
     ((535.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),  // 76
     ((541.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),   // 77
     ((547.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),  // 78
     ((553.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),  // 79
     ((559.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),   // 80
     ((565.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),  // 81
     ((571.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),   // 82
     ((577.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),  // 83
     ((583.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),  // 84
     ((589.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),  // 85
     ((595.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),   // 86
     ((601.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),   // 87
     ((607.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),  // 88
     ((613.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),  // 89
     ((619.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),  // 90
     ((625.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),   // 91
     ((631.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))), // 92
     ((637.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),  // 93
     ((643.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),  // 94
     ((91.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),    // 95
     ((97.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),    // 96
     ((103.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),   // 97
     ((109.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),  // 98
     ((115.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))), // 99
     ((649.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))), // 100
     ((655.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),   // 101
     ((661.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),  // 102
     ((667.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),  // 103
     ((673.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),  // 104
     ((679.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),  // 105
     ((685.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),   // 106
     ((691.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),   // 107
     ((697.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),  // 108
     ((703.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),   // 109
     ((709.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),   // 110
     ((715.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),   // 111
     ((721.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),   // 112
     ((727.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),  // 113
     ((733.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),   // 114
     ((739.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),   // 115
     ((745.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),   // 116
     ((751.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),   // 117
     ((757.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),   // 118
     ((763.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),  // 119
     ((769.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),   // 120
     ((775.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),  // 121
     ((781.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),  // 122
     ((787.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),   // 123
     ((793.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),  // 124
     ((799.25*_TUNER_BP+(_PIF_FREQ*_TUNER_BP/1000))),   // 125
};  
WORD code *ChanelTbl[]={tNTSC_CATV,tNTSC_AIR};
#endif

WORD CLoadChannelFreq(const BYTE ucCurrentChannel);
void CSaveChannelFreq(const WORD iFreq, const BYTE ucCurrentChannel);

#if(_VIDEO_CHIP == _VDC_TB1334)
//============================================================================== 
// ucTVColorMode:    _TV_NTSC_M,   _TV_NTSC_4_BG, _TV_NTSC_4_DK 
//                   _TV_NTSC_4_I, _TV_PAL_M  --> 60Hz
//                   ------------------------------------------
//                   _TV_PAL_BG,   _TV_PAL_I,     _TV_PAL_DK,
//                   _TV_PAL_N     --> 50Hz PAL
//                   ------------------------------------------
//                   _TV_SECAM_BG, _TV_SECAM_DK,  _TV_SECAM_L
//                   _TV_SECAM_LL  --> 50Hz SECAM
//-------------------------------------------------------------
// ucMode:       _SEARCH_CHANNEL_MODE/_NORMAL_MODE
// PifFreq:      45750/39500/38900/38000/34200/33900 KHz
//CarrierSelect: 0: Split carrier    1: Inter carrier
//============================================================================== 
extern void gmi_CSetIfMode(const BYTE ucTVColorMode, const BYTE ucMode, const WORD PifFreq, const BYTE CarrierSelect);


//============================================================================== 
BYTE bCurrentTVColorMode(void)
{
    switch(ucTVType)
    {
    case _TV_PAL_M     :    // 60Hz PAL M
    case _TV_NTSC_M    :    // 60Hz NTSC M
    case _TV_NTSC_4_BG :    // 60Hz NTSC 4/BG
    case _TV_NTSC_4_I  :    // 60Hz NTSC 4/I
    case _TV_NTSC_4_DK :    // 60Hz NTSC 4/DK
        return _60HZ;

    default:                // Normal sound
    case _TV_SECAM_BG  :    // 50Hz SECAM B/G
    case _TV_SECAM_DK  :    // 50Hz SECAM D/K
    case _TV_PAL_N     :    // 50Hz PAL N
    case _TV_PAL_BG    :    // 50Hz PAL B/G
    case _TV_PAL_I     :    // 50Hz PAL I
    case _TV_PAL_DK    :    // 50Hz PAL D/K
    case _TV_SECAM_L   :    // 50Hz SECAM L
    case _TV_SECAM_LL  :    // 50Hz Secam L'
        return _50HZ;
    } // end switch
}

//============================================================================== 
void CStartSearch(bit bStart)
{                           
    BYTE uctemp;

    if (bStart)
        uctemp = 0x00;
    else
        uctemp = 0x01;
       
    if (_60HZ == bCurrentTVColorMode())  // NTSC
        gmi_CI2CWriteVDCByte(0x15, 0x40 | uctemp); 
    else
        gmi_CI2CWriteVDCByte(0x15, 0x20 | uctemp); 


    if (!bStart)
        return;

    do
    {
        gmi_CI2CWriteVDCByte(0x20, 0x40);
        CI2cRead(0x88, 0x00, 3, pData);
        CTimerDelayXms(100);
    }
    while(pData[1] & 0x01);

    gmi_CI2CWriteVDCByte(0x20, 0x20);
} 

#endif // end #if(_VIDEO_CHIP == _VDC_TB1334)

BYTE CGetTVEepromAddr(const BYTE ucCurrentChannel)
{
    BYTE ucEeprom_Addr = (_TV_FREQ_EP0_TV_NUMBER < ucCurrentChannel) ? _TV_FREQ_EEPROM_ADDR1 : _TV_FREQ_EEPROM_ADDR0;

    return ucEeprom_Addr;
}

BYTE CGetTVStartAddr(const BYTE ucCurrentChannel)
{
    BYTE ucStart_Addr = (_TV_FREQ_EP0_TV_NUMBER < ucCurrentChannel) ? ((ucCurrentChannel - (_TV_FREQ_EP0_TV_NUMBER+1)) * 2)
                                                : (_TV_FREQ_EP_START_ADDR0 + (ucCurrentChannel * 2));

    return ucStart_Addr;
}

//==========================================================================
//
//==========================================================================
void CForceBackGroundToBlack(void)
{
#if(_CHANGE_SOURCE_BACKGROUCD_COLOR==_BACK_COLOR)					    	
		CAdjustBackgroundColor(0x00, 0x00, 0x00);     
#else
		CAdjustBackgroundColor(0x00, 0x00, 0xFF);     
#endif
    CScalerSetBit(_VDISP_CTRL_28, ~_BIT5, _BIT5);
    bChangeChannel = 1;
}

// ucMode: Search/Normal mode
void gmi_CI2CWrite9886(BYTE ucTvType, const bit bTunerMute, BYTE ucMode)
{
#if(_VIDEO_CHIP == _VDC_TB1334)

    gmi_CSetIfMode(ucTvType, ucMode, _PIF_FREQ, _CARRIER_SELECT); 

    if(bTunerMute)     
       MUTE_ON();
	else
       MUTE_OFF();

#else

    ucMode = ucMode;
/*
    if (_TV_PAL_BG > ucTvType) // NTSC 
    {
        pData[0] = 0x16;
        pData[1] = 0x30;
    }
    else    // Color PAL/SECAM/Other
    {
        pData[0] = 0xd6;
        pData[1] = 0x70;
    }

    pData[2] = 0x0c;
              */
    // Set TDA9886 B,C data
    switch(ucTvType)
    {
    case _TV_PAL_M     :    // 60Hz PAL M
    case _TV_NTSC_M    :    // 60Hz NTSC M
    case _TV_NTSC_4_BG :    // 60Hz NTSC 4/BG
    case _TV_NTSC_4_I  :    // 60Hz NTSC 4/I
    case _TV_NTSC_4_DK :    // 60Hz NTSC 4/DK
        pData[0] = _TDA9886_B_DATA_NTSC;
        pData[1] = _TDA9886_C_DATA_NTSC;
        break;

    default:                // Normal sound
    case _TV_SECAM_BG  :    // 50Hz SECAM B/G
    case _TV_SECAM_DK  :    // 50Hz SECAM D/K
    case _TV_PAL_N     :    // 50Hz PAL N
    case _TV_PAL_BG    :    // 50Hz PAL B/G
    case _TV_PAL_I     :    // 50Hz PAL I
    case _TV_PAL_DK    :    // 50Hz PAL D/K
        pData[0] = _TDA9886_B_DATA_PAL;
        pData[1] = _TDA9886_C_DATA_PAL;
        break;

#if(_TV_CHIP == _TV_JS_6B2 || _TV_CHIP == _TV_JS_6H2_122A2)
   case _TV_SECAM_L   :    // 50Hz SECAM L
        pData[0] = _TDA9886_B_DATA_SECAML;
        pData[1] = _TDA9886_C_DATA_SECAML;
        break;

    case _TV_SECAM_LL  :    // 50Hz Secam L'
        pData[0] = _TDA9886_B_DATA_SECAMLL;
        pData[1] = _TDA9886_C_DATA_SECAMLL;
        break;
#endif
    } // end switch

    if (bTunerMute)
       MUTE_ON();
//        pData[0] |= _BIT5;
    
    // Set TDA9886 E data
    switch(ucTvType)
    {
    case _TV_PAL_M     :    // Sound 4.5M  PAL M
    case _TV_NTSC_M    :    // Sound 4.5M  NTSC M
    case _TV_PAL_N     :    // Sound 4.5M  PAL N 
        pData[2] = _TDA9886_E_DATA_NTSC;
        break;

    case _TV_NTSC_4_BG :    // Sound 5.5M  NTSC 4/BG
    case _TV_PAL_BG    :    // Sound 5.5M  PAL B/G
    case _TV_SECAM_BG  :    // Sound 5.5M  SECAM B/G
        pData[2] = _TDA9886_E_DATA_PAL_BG;
        break;

    default:                // Normal sound
    case _TV_NTSC_4_I  :    // Sound 6.0M  NTSC 4/I
    case _TV_PAL_I     :    // Sound 6.0M  PAL I
        pData[2] = _TDA9886_E_DATA_PAL_I;
        break;

    case _TV_NTSC_4_DK :    // Sound 6.5M  NTSC 4/DK
    case _TV_PAL_DK    :    // Sound 6.5M  PAL D/K
    case _TV_SECAM_DK  :    // Sound 6.5M  SECAM D/K
        pData[2] = _TDA9886_E_DATA_PAL_DK;
        break;


#if(_TV_CHIP == _TV_JS_6B2 || _TV_CHIP == _TV_JS_6H2_122A2)
   case _TV_SECAM_L   :    // Sound 6.5M  SECAM L
        pData[2] = _TDA9886_E_DATA_SECAML;
        break;

    case _TV_SECAM_LL  :    // Sound 6.5M  Secam L'
        pData[2] = _TDA9886_E_DATA_SECAMLL;
        break;
#endif
    } // end switch
      
    CI2cWrite(_ADDR_9886,0x00,3, pData);  // Set TDA9886
#endif
}

//==========================================================================
//
//==========================================================================
void gmi_CSetTuner(BYTE ucTunerAddress, WORD Freq)
{	 
#if(_TV_CHIP == _TV_TDQ_G4X002A)

   pData[0] = 7;
   pData[1] = ucTunerAddress;
   ((WORD *)pData)[1] = Freq;
   pData[4] = 0x8A;//0x82; 
   
   if(Freq < _VHF_LOW_BAND)        // VHFLOW  
      pData[5]=0x65;     
   else if(Freq < _VHF_HIGH_BAND0) // VHFHIGH  
      pData[5]=0x66;     
   else if(Freq < _VHF_HIGH_BAND)   
      pData[5]=0xA6;     
   else if(Freq < _VHF_HIGH_BAND1)   
      pData[5]=0xAC;     
   else                           //Band select//UHF
      pData[5]=0xEC;   

   pData[6]=0xC6;     
   gmi_CI2CWriteTuner(pData);

#elif(_TV_CHIP == _TV_TDQ_6F6 || _TV_CHIP == _TNF_8337)
             
   pData[0] = 6;
   pData[1] = ucTunerAddress;
   ((WORD *)pData)[1] = Freq;
   pData[4] = 0xC8; // 0xCE 
   
   if(Freq < _VHF_LOW_BAND)  
      pData[5]=0x01;   // VHFLOW   
   else if(Freq < _VHF_HIGH_BAND)   
      pData[5]=0x02;  // VHFHIGH 
   else 
#if(_TV_CHIP == _TNF_8337)
      pData[5]=0x08;  //Band select//UHF 
#else
      pData[5]=0x04;  //Band select//UHF 
#endif

   gmi_CI2CWriteTuner(pData);

#else

#if(_TV_CHIP == _TV_FQ1216ME)
   pData[0] = 7;
#else
   pData[0] = 8;
#endif
   pData[1] = ucTunerAddress;
   ((WORD *)pData)[1] = Freq;

   pData[4] = 0x88;//0xc8; 
  
   if(Freq < _VHF_LOW_BAND)  
      pData[5]=0x01;   // VHFLOW   
   else if(Freq < _VHF_HIGH_BAND)
      pData[5]=0x02;  // VHFHIGH 
   else 
      pData[5]=0x04;  //Band select//UHF 
   pData[6]=0xd8;//0x98;
   pData[7]=0x60;

   gmi_CI2CWriteTuner(pData);
#endif
}

//==========================================================================
//
//==========================================================================
#if(_VIDEO_CHIP != _VDC_TB1334)
BYTE CDetectTVSignalType(void)
{
    BYTE ucTemp;

    for(ucTemp = 0; ucTemp < 4; ucTemp++)
    {
        if (gmi_CVideoCurrentColor(0) != 0x00 && gmi_CModeLocked())  // Horizontal Lock
             return 1;

        CTimerDelayXms(50);
    }

    // No video detected or h/v sync not locked
     return 0;  
}
#endif

//============================================================
//Output: Channel skip     0 --> no skip     1 --> skip
//============================================================
bit CLoadChannelSkip(const BYTE ucCurrentChannel)
{
    CI2cRead(ADDRESS(CGetTVEepromAddr(ucCurrentChannel)), CGetTVStartAddr(ucCurrentChannel)+1, LENGTH(1), pData);  // eric 0223

    if (pData[0] & 0x80)  // Channel skip
        return 1;
    else         // No skip
        return 0;
}

//============================================================
//
//============================================================
void CSaveChannelSkip(const bit bSkip, const BYTE ucCurrentChannel)
{
    WORD iFreq = CLoadChannelFreq(ucCurrentChannel);

    if (bSkip)
       CSaveChannelFreq((iFreq & 0x7fff) | 0x8000, ucCurrentChannel);
    else
       CSaveChannelFreq(iFreq & 0x7fff, ucCurrentChannel);
}

/*
//============================================================
//
//============================================================
BYTE CLoadSearchChannelType(void)
{
    CI2cRead(ADDRESS(EEPROM_TVSYSTEM_ADDR), EEPROM_SEARCH_TYPE_ADDR, LENGTH(1), pData);    // Read current channel freq

    return pData[0];
}

//============================================================
//
//============================================================
void CSaveSearchChannelType(const BYTE ucSearchType)
{
    pData[0] = ucSearchType;
    CI2cWrite(ADDRESS(EEPROM_TVSYSTEM_ADDR), EEPROM_SEARCH_TYPE_ADDR, LENGTH(1), pData);
}
   */
//============================================================
//Output: Channel freq
//============================================================
WORD CLoadChannelFreq(const BYTE ucCurrentChannel)
{
    WORD freq = 0;

    CI2cRead(ADDRESS(CGetTVEepromAddr(ucCurrentChannel)), CGetTVStartAddr(ucCurrentChannel), LENGTH(2), pData);  // eric 0223
    pData[1] &= 0x7f;

    freq = (256*pData[1]) + pData[0];

    if (_MAX_FREQ < freq)
        freq = _MAX_FREQ;
    else if(_MIN_FREQ > freq)
        freq = _MIN_FREQ;

    return freq;
}

//==========================================================================
//
//==========================================================================
void CSaveChannelFreq(const WORD iFreq, const BYTE ucCurrentChannel)
{
    pData[0] = iFreq & 0xff;
    pData[1] = (iFreq >> 8) & 0xff;
    CI2cWrite(ADDRESS(CGetTVEepromAddr(ucCurrentChannel)), CGetTVStartAddr(ucCurrentChannel), LENGTH(2), pData);  // eric 0223
  //  CI2cWrite(ADDRESS(ucEEPROM_ADDR), ucStart_Addr, LENGTH(2), pData);  // eric 0223
}

//============================================================
//Output: Channel color type
//============================================================
BYTE CLoadChannelColorType(const BYTE ucCurrentChannel)
{
    CI2cRead(ADDRESS(_TV_SYSTEM_EEPROM_ADDR), _TV_SYSTEM_START_ADDR+ucCurrentChannel, LENGTH(1), pData);    // Read current channel sound and tv system
    pData[0] = pData[0] >> 4; // tv type

    if (_MAX_TV_TYPE < pData[0])
        pData[0] = _NORMAL_TV_TYPE; // Set to normal PAL I 

    return pData[0];
}

//==========================================================================
//
//==========================================================================
void CSaveChannelColorType(const BYTE ucCurrentChannel, const BYTE TVType)
{
    pData[0] = (TVType << 4) | (CLoadChannelSoundType(ucCurrentChannel));
    CI2cWrite(ADDRESS(_TV_SYSTEM_EEPROM_ADDR), _TV_SYSTEM_START_ADDR+ucCurrentChannel, LENGTH(1), pData);
}

//============================================================
//Output: Channel sound type
//============================================================
BYTE CLoadChannelSoundType(const BYTE ucCurrentChannel)
{
    CI2cRead(ADDRESS(_TV_SYSTEM_EEPROM_ADDR), _TV_SYSTEM_START_ADDR+ucCurrentChannel, LENGTH(1), pData);    // Read current channel sound and tv system
    pData[0] = pData[0] & 0x03; // sound type

  //  if (_MAX_TV_SOUND_TYPE_NUM < pData[0])
    //    pData[0] = 1;  // Set to normal: 6.0M

    return pData[0];
}

//==========================================================================
//
//==========================================================================
void CSaveChannelSoundType(const BYTE ucCurrentChannel, const BYTE ucSoundType)
{
    pData[0] = (CLoadChannelColorType(ucCurrentChannel) << 4) | ucSoundType;
    CI2cWrite(ADDRESS(_TV_SYSTEM_EEPROM_ADDR), _TV_SYSTEM_START_ADDR+ucCurrentChannel, LENGTH(1), pData);
}

//==========================================================================
//
//==========================================================================
void CSaveChannelData(const WORD iFreq, const BYTE ucSound, const BYTE ucChannelNumber)
{
    CSaveChannelFreq(iFreq, ucChannelNumber);
    CTimerDelayXms(4);

    // Save sound and tv system
    pData[0] = (ucTVType<<4) | (ucSound & 0x03);
    CI2cWrite(ADDRESS(_TV_SYSTEM_EEPROM_ADDR), _TV_SYSTEM_START_ADDR+ucChannelNumber, LENGTH(1), pData);
    CTimerDelayXms(4);
}

//==========================================================================
//
//==========================================================================
void CSetTVChannel(const BYTE ucCurrentChannel)
{ 
#if(_NTSC_SEARCH_TABLE)

         BYTE ucMaxChannel = CloadMaxChannelNumber(0);
        BYTE ucMinChannel = CloadMinChannelNumber();
	  if( ucCurrentChannel>ucMinChannel)	
	        stVDCColor.CurrentChannel = (ucCurrentChannel > ucMaxChannel) ? ucMaxChannel : ucCurrentChannel;
        else
	        stVDCColor.CurrentChannel = ucMinChannel;

    	{
	if(_ABS(ChanelTbl[_GET_CATV_AIR()][ucCurrentChannel],CLoadChannelFreq(ucCurrentChannel))>50)
		CSaveChannelFreq(ChanelTbl[_GET_CATV_AIR()][ucCurrentChannel], ucCurrentChannel);
		gmi_CSetTuner(_ADDR_TUNER, CLoadChannelFreq(ucCurrentChannel));
		gmi_CI2CWrite9886(ucTVType, _TUNER_MUTE_ON, _NORMAL_MODE);//_NORMAL_MODE); // set tv system
    	}
#else
    {
        ucTVType = CLoadChannelColorType(ucCurrentChannel); // set tv system
       
        gmi_CSetTuner(_ADDR_TUNER, CLoadChannelFreq(ucCurrentChannel));
   // gmi_CI2CWrite9886(ucTVType, _TUNER_MUTE_OFF); // set tv system
    }
    gmi_CI2CWrite9886(ucTVType, _TUNER_MUTE_ON, _SEARCH_CHANNEL_MODE);//_NORMAL_MODE); // set tv system
  //  ucAudioState = 1;
#endif  
}

//==========================================================================
//
//==========================================================================
BYTE CloadMaxChannelNumber(bit uctemp)
{
#if(_NTSC_SEARCH_TABLE)
               uctemp=uctemp;
 		if(_GET_CATV_AIR())
		 return MAX_CHANNEL_AIR-1;	//AIR start from 2 chanel
	        else
		 return MAX_CHANNEL_CATV -1;	//CATV start from 1 chanel
#else
   if(uctemp)
		return _MAX_CHANNEL_COUNT;
   else
   	{
		CI2cRead(ADDRESS(_TV_MAX_CHANNEL_EEPROM_ADDR), _MAX_CHANNEL_ADDR, LENGTH(1), pData);    // Read search max channel
		if (_MAX_CHANNEL_COUNT < pData[0])
		{
			// Save search channel number
			pData[0] = 0;
			CI2cWrite(_TV_MAX_CHANNEL_EEPROM_ADDR, _MAX_CHANNEL_ADDR, 1, pData);

			pData[0] = CloadMinChannelNumber();//_MAX_CHANNEL_COUNT;
		}

		return pData[0];
   	}
#endif
}
BYTE CloadMinChannelNumber(void)
{
#if(_NTSC_SEARCH_TABLE)
 		if(_GET_CATV_AIR())
		 return 2;	//AIR start from 2 chanel
	      else
		 return 1;	//CATV start from 1 chanel	 
#else
   return 0;
#endif
}

//==========================================================================
//
//==========================================================================
void CModeResetTVMode(void)  // eric 1130 add for change tv channel bug
{        
#if(_VIDEO_CHIP == _VDC_TB1334)
    CLR_LIGHTPOWERSTATUS();
    CForceBackGroundToBlack();
    gmi_CSetVDCFreeRunMode(_VDC_FREE_RUN_MODE_TO_AUTO);
#else
    CForceBackGroundToBlack();
    CModeAutoMeasureOff();
    CMiscClearStatusRegister();
    CTimerCancelTimerEvent(CModeNoSignalEvent);

    CLR_FRAMESYNCSTATUS();

    stModeInfo.ModeCurr   = _MODE_NOSIGNAL;
    ucEvent0              = _INACTIVE_COUNTDOWN_EVENT;
 //   ucOsdState            = _MENU_NONE;
    ucOsdEventMsg         = _NONE_MSG;
    ucInputSyncType       = _NO_SYNC_STATE;
    ucVideoNoModeTime     = 0;
    VideoTurnOnLightCount = 0;
    stModeInfo.Polarity   = 0;
    stModeInfo.IHCount    = 0;
    stModeInfo.IHFreq     = 0;
    stModeInfo.IVTotal    = 0;
    stModeInfo.IVFreq     = 0;
    stModeInfo.IHWidth    = 0;
    stModeInfo.IVHeight   = 0;
    stModeInfo.IHSyncPulseCount = 0;
    VideoTurnOnLightCount = 0;

    RECODE_NONE_VIDEO();

    ucCurrState = _SEARCH_STATE;  
#endif
}      

void CModeResetTVNtscToPal(void)  //FOR TB1334  NTSC  TO  PAL  OR PAL TO NTSC
{
    CEepromSaveVedioColor();
    switch(ucTVType) 
    {
    case _TV_NTSC_M    :    // 60Hz Sound 4.5M  NTSC M
    case _TV_NTSC_4_BG :    // 60Hz Sound 5.5M  NTSC 4/BG 
    case _TV_NTSC_4_DK :    // 60Hz Sound 6.5M  NTSC 4/DK 
    case _TV_NTSC_4_I  :    // 60Hz Sound 6.0M  NTSC 4/I
    case _TV_PAL_M     :    // 60Hz Sound 4.5M  PAL M  
	if(!CHECK60HZ())    
		{
		 CModeSetFreeRun();
		ucVideoNoModeTime=253;
		Delay_Xms(200);
       	CScalerRead(_STATUS0_02, 1, pData, _NON_AUTOINC);//  xdl  20080816
	        pData[0]|=0x80;
              CScalerWrite(_STATUS0_02, 1, pData, _NON_AUTOINC);
		CModeResetMode();
		}
      break;
	
    case _TV_PAL_BG    :    // 50Hz Sound 5.5M  PAL B/G
    case _TV_PAL_I     :    // 50Hz Sound 6.0M  PAL I
    case _TV_PAL_DK    :    // 50Hz Sound 6.5M  PAL D/K
    case _TV_PAL_N     :    // 50Hz Sound 4.5M  PAL N 
    case _TV_SECAM_BG  :    // 50Hz Sound 5.5M  SECAM B/G
    case _TV_SECAM_DK  :    // 50Hz Sound 6.5M  SECAM D/K
    case _TV_SECAM_L   :    // 50Hz Sound 6.5M  SECAM L  
    case _TV_SECAM_LL  :    // 50Hz Sound 6.5M  Secam L' 
	if(CHECK60HZ())    
		{
		CModeSetFreeRun();
		ucVideoNoModeTime=253;
		Delay_Xms(200);
       	CScalerRead(_STATUS0_02, 1, pData, _NON_AUTOINC);//  xdl  20080816
	        pData[0]|=0x80;
              CScalerWrite(_STATUS0_02, 1, pData, _NON_AUTOINC);
		CModeResetMode();
		}
      break;
    } // end switch 

}
void CChangeChannel(bit bNext)
{
    BYTE ucmaxchannel = CloadMaxChannelNumber(0);

    if (stVDCColor.CurrentChannel > ucmaxchannel)
    {
        ucPrevChannel             = 0;
        stVDCColor.CurrentChannel = 0;
        return;
    }
              
    ucPrevChannel =  stVDCColor.CurrentChannel;
    MUTE_ON();
	
#if(_VIDEO_CHIP == _VDC_TB1334)
    CForceBackGroundToBlack();
	Delay_Xms(200);
    bChangeChannel = 1;
#else     
    CModeResetTVMode();

#endif    

	do
	{
       if (bNext)  // Change next channel
           stVDCColor.CurrentChannel = (stVDCColor.CurrentChannel == ucmaxchannel) ? 0 : (stVDCColor.CurrentChannel+1);
       else        // Change prev channel
           stVDCColor.CurrentChannel = (stVDCColor.CurrentChannel == 0) ? ucmaxchannel : (stVDCColor.CurrentChannel-1);
    
	   if (!CLoadChannelSkip(stVDCColor.CurrentChannel) || stVDCColor.CurrentChannel == ucPrevChannel)
	        break;
	}
	while(1);

    bChangeChannel = 1;
    CSetTVChannel(stVDCColor.CurrentChannel);  
    CShowTVNumber(stVDCColor.CurrentChannel, _SHOW_CH_TV_NUMBER | _SHOW_CH_TV_TYPE | _SHOW_CH_SOUND_TYPE);  //eric1221 mark
         _SET_CHANNEL_FOR_AUDIO(1);
   CModeResetTVNtscToPal();
}
 /*
void CPrevChannel(void)
{   
    ucPrevChannel =  stVDCColor.CurrentChannel;

    CForceBackGroundToBlack();
    bChangeChannel = 1;

	do
	{
       stVDCColor.CurrentChannel = (stVDCColor.CurrentChannel == 0) ? CloadMaxChannelNumber() : (stVDCColor.CurrentChannel-1);
    
	   if (!CLoadChannelSkip(stVDCColor.CurrentChannel) || stVDCColor.CurrentChannel == ucPrevChannel)
	        break;
	}
	while(1);

    CSetTVChannel(stVDCColor.CurrentChannel);
    CShowTVNumber(stVDCColor.CurrentChannel,_SHOW_CH_TV_NUMBER | _SHOW_CH_TV_TYPE | _SHOW_CH_SOUND_TYPE);
}

//==========================================================================
//
//==========================================================================
void CNextChannel(void)
{
    ucPrevChannel =  stVDCColor.CurrentChannel;

    CForceBackGroundToBlack();
    bChangeChannel = 1;

	do
	{
       stVDCColor.CurrentChannel = (stVDCColor.CurrentChannel == CloadMaxChannelNumber()) ? 0 : (stVDCColor.CurrentChannel+1);
    
	   if (!CLoadChannelSkip(stVDCColor.CurrentChannel) || stVDCColor.CurrentChannel == ucPrevChannel)
	        break;
	}
	while(1);

    CSetTVChannel(stVDCColor.CurrentChannel);
    CShowTVNumber(stVDCColor.CurrentChannel,_SHOW_CH_TV_NUMBER | _SHOW_CH_TV_TYPE | _SHOW_CH_SOUND_TYPE);
}
    */

//==========================================================================
//
//==========================================================================

#if(_NTSC_SEARCH_TABLE)
//==========================================================================
//
//==========================================================================
void CTvAutoSearch(void)
{
	BYTE ucSound = 0;
	WORD *temptr;
	BYTE ucmaxchannel = CloadMaxChannelNumber(0);
	BYTE ucminchannel = CloadMinChannelNumber();
	WORD iFreq        = _MIN_FREQ;
	BYTE ucNoChanel = 0x0ff;
	BYTE FirstChanel=1;
	WORD chann;
	BYTE i;
	temptr=ChanelTbl[_GET_CATV_AIR()];
	for(i=0;i<=ucmaxchannel;i++)
	CSaveChannelSkip(1, i);//060821

#if(_VIDEO_CHIP == _VDC_TB1334)
    CStartSearch(1);
#endif
    // Read color and sound type
    if (0 == ucmaxchannel)
    {
        ucSound  = 0; //CLoadChannelSoundType(0); // Not use sound type
        ucTVType = CLoadChannelColorType(0); 
    }
    else
    {
        ucSound  = 0; //CLoadChannelSoundType(stVDCColor.CurrentChannel); // Not use sound type 
        ucTVType = CLoadChannelColorType(stVDCColor.CurrentChannel); 
    }

    // Reset search max tv channel number
    pData[0] = ucminchannel; 
    CI2cWrite(_TV_MAX_CHANNEL_EEPROM_ADDR, _MAX_CHANNEL_ADDR, 1, pData);

    stVDCColor.CurrentChannel = ucminchannel;
	ucPrevChannel = ucminchannel;

    gmi_CI2CWrite9886(ucTVType, _TUNER_MUTE_ON, _SEARCH_CHANNEL_MODE);
    CTimerDelayXms(8);
		chann = ucminchannel;	 
#if(_VIDEO_CHIP == _VDC_TB1334)
    CStartSearch(0);
#endif
    CShowAutoSerachTotal(chann);   // Show search tv channel number
	CAdjustBackgroundColor(0x00, 0x00, 0xFF);     				
	 CScalerSetBit(_VDISP_CTRL_28, ~(_BIT5|_BIT3), _BIT5); // Set bluebackground off
    while(1)
    {
       chann=CLockChannel(chann,1);
	
        if(chann == 0x0ff)  
			break;
        CSaveChannelSkip(0, chann);
	 CSaveChannelData(temptr[chann] , ucSound , chann);
	 if(ucNoChanel==0x0ff)
	 {
	 	FirstChanel=chann;
	       ucNoChanel=0;
    	 }
	CAdjustBackgroundColor(0x00, 0x00, 0x00);     				
	CScalerSetBit(_VDISP_CTRL_28, ~(_BIT5|_BIT3), _BIT3); // Set bluebackground off
	 for(ucNoChanel=0;ucNoChanel<=100;ucNoChanel++)
	 	{
		    if (CKeyStopAutoSearch())
		      break; 
			CTimerDelayXms(5);
	 	}
	CAdjustBackgroundColor(0x00, 0x00, 0xFF);     				
	        CScalerSetBit(_VDISP_CTRL_28, ~(_BIT5|_BIT3), _BIT5); // Set bluebackground off
	       ucNoChanel=0;
              chann=chann+1;
    }  // End while
    


#if(_CHANGE_CHANNEL_MTD == _CHANGE_CHANNEL_M2)//0227 gmi
    {
        BYTE ucChannelCount = 0;

        chann--;
        for(ucChannelCount = chann; ucChannelCount < _MAX_CHANNEL_COUNT; ucChannelCount++)
        {
            CSaveChannelData((WORD)_MIN_FREQ | 0x8000, ucSound, ucChannelCount);
        }

    }
#endif
    // Save search channel number
    pData[0] = chann;
    CI2cWrite(_TV_MAX_CHANNEL_EEPROM_ADDR, _MAX_CHANNEL_ADDR, 1, pData);
    CSetTVChannel(FirstChanel);
	stVDCColor.CurrentChannel=FirstChanel;
    bChangeChannel = 1;
    // Save current channel
    CEepromSaveVedioColor();    

    #if(_IR_ENABLE)
    ucDetectIR_Cmd = 0;
    #endif

    if(stOsdUserData.OsdTimeout > 4)
    {
        CTimerReactiveTimerEvent(SEC(stOsdUserData.OsdTimeout),COsdDispOsdTimerEvent);
    }
    else
    {
        CTimerCancelTimerEvent(COsdDispOsdTimerEvent);
    }

    gmi_CI2CWrite9886(ucTVType, _TUNER_MUTE_OFF, _NORMAL_MODE); // set tv system
#if(_VIDEO_CHIP == _VDC_TB1334)
    CTimerDelayXms(100);
    if (gmi_CModeLocked())
        gmi_CSetVDCFreeRunMode(_VDC_FREE_RUN_MODE_TO_AUTO);
    else
        gmi_CSetVDCFreeRunMode((CHECK60HZ()) ? _VDC_FREE_RUN_MODE_TO_60HZ : _VDC_FREE_RUN_MODE_TO_50HZ);
#else
    CModeResetTVMode();   
#endif
}

WORD CLockChannel(WORD chann, const bit bCLockMode)
{

    WORD i   ,imax     = 0;
    BYTE SignalCounter,uccount  = 0;
    WORD *temptr;
    WORD iLockedFreq   = 0;
    BYTE IFState       = 0;
    BYTE ucTB1334Flag  = 0;
    WORD ucmaxchannel=CloadMaxChannelNumber(0);
	i=bCLockMode;
		if(_GET_CATV_AIR())
		imax = MAX_CHANNEL_AIR;	//AIR start from 2 chanel
	else
		imax = MAX_CHANNEL_CATV;	//CATV start from 1 chanel

    temptr=ChanelTbl[_GET_CATV_AIR()];
for(i =chann;i<imax;i++ )
	{
        CSaveChannelFreq(temptr[i], i);
        CSaveChannelColorType(i,ucTVType);
    	CShowAutoSerachTotal(i);	//show channel number
    	
        gmi_CSetTuner(_ADDR_TUNER, temptr[i]);

        CShowAutoSearchSliderInOSD(temptr[i]);	// show current frequency
		SignalCounter=0;	
	 	for(uccount = 0; uccount < 5; uccount++)
	  	{
			CTimerDelayXms(150);//150
		    if (CKeyStopAutoSearch())
		    	{
			CSaveChannelSkip(1, i);//060821
		       return 0x0ff; 
		    	}
			    CI2cRead(0x88, 0x00, 1, pData);
			    IFState = pData[0];
			IFState = (IFState) & (_BIT0|_BIT6);
			if(IFState==(_BIT0|_BIT6))
				SignalCounter++;
			if(SignalCounter >= 3)			
				return i;
	 	}

            if (temptr[i] > _MAX_FREQ)
            	{
		CSaveChannelSkip(1, i);//060821
                return 0x0ff;
            	}

	

	CSaveChannelSkip(1, i);//060821
	 		
        }
		

    return 0x0ff;  //Not Find Channel

}
#else
 /*
void CPrevChannel(void)
{   
    ucPrevChannel =  stVDCColor.CurrentChannel;

    CForceBackGroundToBlack();
    bChangeChannel = 1;

	do
	{
       stVDCColor.CurrentChannel = (stVDCColor.CurrentChannel == 0) ? CloadMaxChannelNumber() : (stVDCColor.CurrentChannel-1);
    
	   if (!CLoadChannelSkip(stVDCColor.CurrentChannel) || stVDCColor.CurrentChannel == ucPrevChannel)
	        break;
	}
	while(1);

    CSetTVChannel(stVDCColor.CurrentChannel);
    CShowTVNumber(stVDCColor.CurrentChannel,_SHOW_CH_TV_NUMBER | _SHOW_CH_TV_TYPE | _SHOW_CH_SOUND_TYPE);
}

//==========================================================================
//
//==========================================================================
void CNextChannel(void)
{
    ucPrevChannel =  stVDCColor.CurrentChannel;

    CForceBackGroundToBlack();
    bChangeChannel = 1;

	do
	{
       stVDCColor.CurrentChannel = (stVDCColor.CurrentChannel == CloadMaxChannelNumber()) ? 0 : (stVDCColor.CurrentChannel+1);
    
	   if (!CLoadChannelSkip(stVDCColor.CurrentChannel) || stVDCColor.CurrentChannel == ucPrevChannel)
	        break;
	}
	while(1);

    CSetTVChannel(stVDCColor.CurrentChannel);
    CShowTVNumber(stVDCColor.CurrentChannel,_SHOW_CH_TV_NUMBER | _SHOW_CH_TV_TYPE | _SHOW_CH_SOUND_TYPE);
}
    */

//==========================================================================
//
//==========================================================================
void CTvAutoSearch(void)
{
    BYTE ucSound = 0;
    BYTE ucPRG        = 0;
    BYTE ucmaxchannel = CloadMaxChannelNumber(0);
	BYTE ucminchannel = CloadMinChannelNumber();
    WORD iFreq        = _MIN_FREQ;
 	BYTE i,ucNoChanel;
	for(i=0;i<=ucmaxchannel;i++)
	CSaveChannelSkip(1, i);//060821
      
#if(_VIDEO_CHIP == _VDC_TB1334)
    CStartSearch(1);
#endif
    // Read color and sound type
    if (0 == ucmaxchannel)
    {
        ucSound  = 0; //CLoadChannelSoundType(0); // Not use sound type
        ucTVType = CLoadChannelColorType(0); 
    }
    else
    {
        ucSound  = 0; //CLoadChannelSoundType(stVDCColor.CurrentChannel); // Not use sound type 
        ucTVType = CLoadChannelColorType(stVDCColor.CurrentChannel); 
    }

    // Reset search max tv channel number
    pData[0] = ucminchannel; 
    CI2cWrite(_TV_MAX_CHANNEL_EEPROM_ADDR, _MAX_CHANNEL_ADDR, 1, pData);

    stVDCColor.CurrentChannel = ucminchannel;
	ucPrevChannel = ucminchannel;

    gmi_CI2CWrite9886(ucTVType, _TUNER_MUTE_ON, _SEARCH_CHANNEL_MODE);
    CTimerDelayXms(8);
#if(_VIDEO_CHIP == _VDC_TB1334)
    CStartSearch(0);
#endif
    CShowAutoSerachTotal(ucPRG);   // Show search tv channel number
  //   gmi_CSetVDCFreeRunMode(_VDC_FREE_RUN_MODE_TO_AUTO);
                   
	CAdjustBackgroundColor(0x00, 0x00, 0xFF);     				
	 CScalerSetBit(_VDISP_CTRL_28, ~(_BIT5|_BIT3), _BIT5); // Set bluebackground off

    while(1)
    {
        iFreq = CLockChannel(iFreq+40, 1); // CLockChannelUp(iFreq+20); 

        if(iFreq < 2)
        {
            ucPRG = (ucPRG == 0) ? 0 : (ucPRG - 1);
            break;
        }
	 CSaveChannelSkip(0, i); 
        CSaveChannelData(iFreq,ucSound,ucPRG);
	CAdjustBackgroundColor(0x00, 0x00, 0x00);     				
	CScalerSetBit(_VDISP_CTRL_28, ~(_BIT5|_BIT3), _BIT3); // Set bluebackground off
	 for(ucNoChanel=0;ucNoChanel<=100;ucNoChanel++)
	 	{
		    if (CKeyStopAutoSearch())
		      break; 
			CTimerDelayXms(5);
	 	}
	CAdjustBackgroundColor(0x00, 0x00, 0xFF);     				
	        CScalerSetBit(_VDISP_CTRL_28, ~(_BIT5|_BIT3), _BIT5); // Set bluebackground off
	       ucNoChanel=0;
        
        ucPRG++;
        if(ucPRG > _MAX_CHANNEL_COUNT)
        {
           ucPRG -= 1;
           break;
        }

        CShowAutoSerachTotal(ucPRG);  // Show search tv channel number

    }  // End while

#if(_CHANGE_CHANNEL_MTD == _CHANGE_CHANNEL_M2)//0227 gmi
    {
        BYTE ucChannelCount = 0;

        ucPRG++;
        for(ucChannelCount = ucPRG; ucChannelCount < _MAX_CHANNEL_COUNT; ucChannelCount++)
        {
            CSaveChannelData((WORD)_MIN_FREQ | 0x8000, ucSound, ucChannelCount);
        }

    }
#endif
    // Save search channel number
    pData[0] = ucPRG;
    CI2cWrite(_TV_MAX_CHANNEL_EEPROM_ADDR, _MAX_CHANNEL_ADDR, 1, pData);
    CSetTVChannel(ucminchannel);
    // Save current channel
    CEepromSaveVedioColor();    

    bChangeChannel = 1;

    #if(_IR_ENABLE)
    ucDetectIR_Cmd = 0;
    #endif

    if(stOsdUserData.OsdTimeout > 4)
    {
        CTimerReactiveTimerEvent(SEC(stOsdUserData.OsdTimeout),COsdDispOsdTimerEvent);
    }
    else
    {
        CTimerCancelTimerEvent(COsdDispOsdTimerEvent);
    }

    gmi_CI2CWrite9886(ucTVType, _TUNER_MUTE_OFF, _NORMAL_MODE); // set tv system
#if(_VIDEO_CHIP == _VDC_TB1334)
    CTimerDelayXms(100);
    if (gmi_CModeLocked())
        gmi_CSetVDCFreeRunMode(_VDC_FREE_RUN_MODE_TO_AUTO);
    else
        gmi_CSetVDCFreeRunMode((CHECK60HZ()) ? _VDC_FREE_RUN_MODE_TO_60HZ : _VDC_FREE_RUN_MODE_TO_50HZ);
#else
    CModeResetTVMode();   
#endif
}
//==========================================================================
//bSearchAction:   0 --> Search down
//                 1 --> Search up
//==========================================================================
void CManualSearch(const bit bSearchAction, const BYTE ucCurrentChannel)
{
    BYTE ucSound           = 0;
 //   BYTE ucmaxchannel      = CloadMaxChannelNumber();
    WORD iFreq             = 0;
    WORD ucSatrtSearchFreq = 0;     
     ucSatrtSearchFreq = CLoadChannelFreq(ucCurrentChannel);

#if(_VIDEO_CHIP == _VDC_TB1334)
    CStartSearch(1);
#endif

    gmi_CI2CWrite9886(ucTVType, _TUNER_MUTE_ON, _SEARCH_CHANNEL_MODE);
    CTimerDelayXms(100);
#if(_VIDEO_CHIP == _VDC_TB1334)
    gmi_CSetTuner(_ADDR_TUNER, _MIN_FREQ);
    CTimerDelayXms(100);
#endif
    gmi_CSetVDCFreeRunMode(_VDC_FREE_RUN_MODE_TO_AUTO);

    if (ucSatrtSearchFreq > _MAX_FREQ)
        ucSatrtSearchFreq = _MAX_FREQ;
    else if(ucSatrtSearchFreq < _MIN_FREQ)
        ucSatrtSearchFreq = _MIN_FREQ;

#if(_VIDEO_CHIP == _VDC_TB1334)
    CStartSearch(0);
#endif

    if (bSearchAction)
        iFreq = CLockChannel(ucSatrtSearchFreq + 40, 1);//  CLockChannelUp(ucSatrtSearchFreq + 5);
    else
        iFreq = CLockChannel(ucSatrtSearchFreq - 40, 0);//   CLockChannelDown(ucSatrtSearchFreq - 5);

    if (iFreq > 100)
        CSaveChannelData(iFreq,CLoadChannelSoundType(ucCurrentChannel),ucCurrentChannel);
  //  else  // eric 1214 modify for manual search channel
    CSetTVChannel(ucCurrentChannel);

#if(_OSD_TYPE == _OSD007)
    #if(_TV_SEARCH_SHOW_TYPE == _TV_SEARCH_SHOW_FREQ)
        CShowAutoSearchSliderInOSD(CLoadChannelFreq(stVDCColor.CurrentChannel));                         
    #endif
#endif

    CTimerDelayXms(50);
    if (gmi_CModeLocked())
    	{
	if(GET_BURNIN_STATE()==BURNIN_ON)                
		CScalerSetBit(_VDISP_CTRL_28, ~_BIT5, _BIT5); // Set bluebackground off
	else
		CScalerSetBit(_VDISP_CTRL_28, ~_BIT5, 0x00); // Set bluebackground off
    	}
    #if(_IR_ENABLE)
    ucDetectIR_Cmd = 0;
    #endif

    if(stOsdUserData.OsdTimeout > 4)
    {
        CTimerReactiveTimerEvent(SEC(stOsdUserData.OsdTimeout),COsdDispOsdTimerEvent);
    }
    else
    {
        CTimerCancelTimerEvent(COsdDispOsdTimerEvent);
    }

    gmi_CI2CWrite9886(ucTVType, _TUNER_MUTE_OFF, _NORMAL_MODE);
#if(_VIDEO_CHIP == _VDC_TB1334)
    CTimerDelayXms(100);
    if (gmi_CModeLocked())
        gmi_CSetVDCFreeRunMode(_VDC_FREE_RUN_MODE_TO_AUTO);
    else
        gmi_CSetVDCFreeRunMode((CHECK60HZ()) ? _VDC_FREE_RUN_MODE_TO_60HZ : _VDC_FREE_RUN_MODE_TO_50HZ);
#else
    CModeResetTVMode();   
#endif
}
#if(_VIDEO_CHIP == _VDC_TB1334)
#define _FLAG_RESET        0x00
#define _IF_H_LOCK         0x60
#define _AFT_W_OK          0x01
#define _AFT_C_LOWER       0x02
#define _AFT_C_UPPER       0x00

#define _SKIP_SIZE6        0x06
#define _SKIP_SIZE2        0x02
#define _SKIP_SIZE_NORMAL  0x01

#endif

WORD CLockChannel(WORD iStartFreq, const bit bCLockMode)
{

    WORD iLockedFreq   = 0;
    BYTE IFState       = 0;
    BYTE ucTB1334Flag  = 0;
                       
    while(1)
    {
        gmi_CSetTuner(_ADDR_TUNER, iStartFreq);


#if(_OSD_TYPE == _OSD007)

    #if(_TV_SEARCH_SHOW_TYPE == _TV_SEARCH_SHOW_FREQ)
        CShowAutoSearchSliderInOSD((iStartFreq));                         
    #else
        CShowAutoSearchSliderInOSD((BYTE)((iStartFreq-_MIN_FREQ)/168));
    #endif

#else

        CShowAutoSearchSliderInOSD((BYTE)((iStartFreq-_MIN_FREQ)/168));
 
#endif

       
		CTimerDelayXms(30);	 
				
  		CI2cRead(0x88, 0x00, 1, pData);
        IFState = pData[0];

        // Step1
        if ((IFState & _AFT_C_LOWER) == _AFT_C_LOWER)
             ucTB1334Flag |= 0x01;
        // Step4
        else if((IFState & _AFT_C_LOWER) == _AFT_C_UPPER)
             ucTB1334Flag |= 0x08;
        // Step2/3
        if ((IFState & _IF_H_LOCK) == _IF_H_LOCK)
        {   // Step2
            ucTB1334Flag |= 0x02;

            // Step3
            if ((IFState & _AFT_W_OK) == _AFT_W_OK)
               ucTB1334Flag |= 0x04;
        }
        else
            ucTB1334Flag = _FLAG_RESET;

        switch(ucTB1334Flag)
        {
        default:
            ucTB1334Flag = _FLAG_RESET;   
        case _FLAG_RESET: // IF&H not locked
        case 0x01:
            if (bCLockMode)  // Search up
                iStartFreq += _SKIP_SIZE6;
            else             // Search down
                iStartFreq -= _SKIP_SIZE2;
            break;

        case 0x03:    // IF&H locked
            iStartFreq = (bCLockMode) ? (iStartFreq + _SKIP_SIZE2) : (iStartFreq - _SKIP_SIZE2);
            break;
               
        case 0x07:    // IF&H locked & AFW-W OK
            if (bCLockMode)  // Search up
                iStartFreq += _SKIP_SIZE_NORMAL;
            else             // Search down
                return iStartFreq;
            break; 

//        case 0x07:    // IF&H locked & AFW-W OK
        case 0x0f:    // Channel lock complete  
            return iStartFreq;
        }

        if (CKeyStopAutoSearch())
           return 0; 
 
        if (bCLockMode) // Search up
        {
            if (iStartFreq > _MAX_FREQ)
                return 1;
        }
        else            // Search down
        {
            if (iStartFreq < _MIN_FREQ)
                return 1;
        }

    }
    return 1;  //Not Find Channel

}

#endif

//==========================================================================
//bSearchAction:   0 --> Tuning down
//                 1 --> Tuning up
//==========================================================================
void CTuningCurrentChannel(const bit bSearchAction, const BYTE ucCurrentChannel)
{
    bit bSkip  = CLoadChannelSkip(ucCurrentChannel);
    WORD iFreq = CLoadChannelFreq(ucCurrentChannel);

    if ((iFreq < _MIN_FREQ || iFreq > _MAX_FREQ) && 0 == CloadMaxChannelNumber(0))
        iFreq = _MIN_FREQ;

    if (bSearchAction) // Tuning up
    {
        if (iFreq < _MAX_FREQ)
            iFreq++;
    }
    else  // Tuning down
    {
        if (iFreq > _MIN_FREQ)
            iFreq--;
    }

    gmi_CSetTuner(_ADDR_TUNER, iFreq);
    CSaveChannelFreq((iFreq | ((bSkip) ? 0x8000 : 0x0000)), ucCurrentChannel);
}

//==========================================================================
//  bCLockMode --> 1: lock up         0 : lock down
//==========================================================================
//==========================================================================
void CInitTV()
{

//     TUNER_PWR_ON();
     CTimerDelayXms(50);
     CSetTVChannel(stVDCColor.CurrentChannel);
     ucPrevChannel = stVDCColor.CurrentChannel;
     ucVideoNoModeTime = 0;       
     gmi_CI2CWrite9886(ucTVType, _TUNER_MUTE_OFF, _NORMAL_MODE);
}

//==========================================================================
#endif
