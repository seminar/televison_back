#ifndef __LANGUAGE__
#define __LANGUAGE__

#define GET_LANGUAGE           stOsdUserData.Language
#define SET_LANGUAGE(value)    stOsdUserData.Language = value 

#if(_NEW_OSD_FUNC)


BYTE GetNextLanguage(BYTE CurrIndex);
BYTE GetPrevLanguage(BYTE CurrIndex);
BYTE CheckLanguage();
BYTE FirstLanguage();

#endif  //#if(NEW_OSD_FUNC)

#endif
