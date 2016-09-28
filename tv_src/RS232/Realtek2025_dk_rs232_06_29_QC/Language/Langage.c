#include "Header\Include.h"


#if(_NEW_OSD_FUNC)

//----------------------------------------------------------------------------
BYTE GetNextLanguage(BYTE CurrIndex)
{
     BYTE i;
     WORD iMask = usLANGUAGE_MASK;

     iMask >>= (CurrIndex+1);

     for(i=CurrIndex+1;i<16;i++)
     {
         if(iMask&0x01)
         {
             return i;
         }
         iMask >>= 1;
     }

     //???????????Next Langage
     iMask = usLANGUAGE_MASK;
     for(i=0;i<CurrIndex;i++)
     {
         if(iMask&0x01)
         {
             return i;
         }
         iMask >>= 1;
     }
     return CurrIndex;
}

//----------------------------------------------------------------------------
BYTE GetPrevLanguage(BYTE CurrIndex)
{
     char i;
     WORD iMask = usLANGUAGE_MASK;

     iMask <<= (16 - CurrIndex);

     for(i=CurrIndex - 1;i>=0;i--)
     {
         if(iMask & 0x8000)
         {
             return i;
         }
         iMask <<= 1;
     }

     //???????????Prev Langage
     iMask = usLANGUAGE_MASK;
     for(i=15;i>=CurrIndex;i--)
     {
         if(iMask & 0x8000)
         {
             return i;
         }
         iMask <<= 1;
     }
     return CurrIndex;
}

//----------------------------------------------------------------------------
BYTE CheckLanguage()
{
     BYTE ucLanguage = GET_LANGUAGE;
     WORD iMask      = usLANGUAGE_MASK;

     iMask >>= ucLanguage;

     if(iMask & 0x01)
     {
         return ucLanguage;
     }
     else
     {
         ucLanguage = FirstLanguage();
         SET_LANGUAGE(ucLanguage);

         return ucLanguage;
     }
}

//----------------------------------------------------------------------------
BYTE FirstLanguage()
{
     BYTE i;
     WORD iMask = usLANGUAGE_MASK;

     for(i=0;i<16;i++)
     {
         if(iMask&0x01)
         {
             return i;
         }
         iMask >>= 1;
     }
     return 255;
}

//----------------------------------------------------------------------------
#endif //#if(NEW_OSD_FUNC)
