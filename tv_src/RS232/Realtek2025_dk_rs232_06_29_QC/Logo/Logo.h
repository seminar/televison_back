#if(_LOGO_EN)

#if(_LOGO_TYPE == _LOGO_TYPE0)

#define LOGO_MOVE_EN          1


#else

#endif // #if(_LOGO_TYPE == _LOGO_TYPE0

#ifdef __LOGOC__

#if(_LOGO_TYPE == _LOGO_TYPE0)

//----------------------------------------------------------
BYTE code tLogoPALETTE[] =
{
	//-------------:Palette ----------
	0x00,0x00,0x00,    0xff,0x00,0x00,    
	0x00,0xff,0x00,    0x00,0x00,0xff,    
	0xFF,0xFF,0x00,    0x00,0xff,0xff,    
	0xff,0x00,0xff,    0xff,0xff,0xff,    
	
	0xFF,0x80,0x00,    0xC0,0xC0,0xC0,    
	0x33,0x6A,0xA5,    0x94,0xBD,0x35,    
	0xF3,0x94,0x28,    0x56,0xF0,0x6d,    
	0x9f,0xed,0xae,    0x80,0x80,0x80,    

};
//----------------------------------------------------------
void DrawLogo();

#else

bit bLogoOnScreen = 0;

void CLogoGo(void);

#endif // #if(_LOGO_TYPE == _LOGO_TYPE0)


#else

#if(_LOGO_TYPE == _LOGO_TYPE0)


//extern BYTE code ucFntLogo[];
extern void DrawLogo();

#else

extern bit bLogoOnScreen;
extern void CLogoGo(void);

#endif // #if(_LOGO_TYPE == _LOGO_TYPE0

#endif // #ifdef __LOGOC__

#endif   //#if(LOGO_EN)
