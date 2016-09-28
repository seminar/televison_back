#if(_FACTORY_MENU_EN)



#ifdef __MAIN__

//------------------------------------------------------------------------------
BYTE xdata sFacVersionCode[] = "2025V13C 090101";    //    ¸ü¸Ä°æ±¾ºÅ
BYTE xdata sFacVersion[] = "VERSION";
BYTE xdata sFacBright[]    = "BRIGHTNESS";
BYTE xdata sFacContrast[]  = "CONTRAST";
BYTE xdata sFacReset[]     = "RESET";
BYTE xdata sFacADCOffset[] = "ADC OFFSET";
BYTE xdata sFacADCGain[]   = "ADC GAIN";
BYTE xdata sFac9300K[]     = "9300K";
BYTE xdata sFac6500K[]     = "6500K";
BYTE xdata sFac5800K[]     = "5800K";
BYTE xdata sFacsRGB[]      = "SRGB";
BYTE xdata sFacUser[]      = "USER";
BYTE xdata sFacBurinIn[]   = "BURIN IN";
BYTE xdata sFacOsdLanguage[]= "OSD LANGUAGE";
BYTE xdata sFacPowerSet[]= "POWER SET";
BYTE xdata sFacPowerUp[]= "POWER UP  ";
BYTE xdata sFacPowerDown[]= "POWER DOWN";
BYTE xdata sFacPowerSave[]= "POWER SAVE";
BYTE xdata sFacLOGOEN[]      = "LOGOEN";
BYTE xdata sFacEMC[]      = "EMC";
BYTE xdata sFacExit[]      = "EXIT";
BYTE xdata sFacOn[]        = "ON";
#if(_LOGO_EN==_DISABLE)
BYTE xdata sFac_DISABLE[]        = "DISABLE";
#endif
BYTE xdata sFacOff[]       = "OFF";
//BYTE xdata sFacReturn[]    = "RETURN";

#else

extern BYTE xdata tFacPALETTE_0[];

extern BYTE xdata sFacVersionCode[];
extern BYTE xdata sFacVersion[];
extern BYTE xdata sFacBright[];
extern BYTE xdata sFacContrast[];
extern BYTE xdata sFacReset[];
extern BYTE xdata sFacADCOffset[];
extern BYTE xdata sFacADCGain[];
extern BYTE xdata sFac9300K[];
extern BYTE xdata sFac6500K[];
extern BYTE xdata sFac5800K[];
extern BYTE xdata sFacsRGB[];
extern BYTE xdata sFacUser[];
extern BYTE xdata sFacBurinIn[];
extern BYTE xdata sFacOsdLanguage[];
extern BYTE xdata sFacPowerSet[];
extern BYTE xdata sFacPowerUp[];
extern BYTE xdata sFacPowerDown[];
extern BYTE xdata sFacPowerSave[];
extern BYTE xdata sFacLOGOEN[];
extern BYTE xdata sFacEMC[];
extern BYTE xdata sFacExit[];
extern BYTE xdata sFacOn[];
#if(_LOGO_EN==_DISABLE)
extern BYTE xdata sFac_DISABLE[];
#endif
extern BYTE xdata sFacOff[];
//extern BYTE xdata sFacReturn[];

#endif

#endif        //#if(FACTORY_MENU_EN)
