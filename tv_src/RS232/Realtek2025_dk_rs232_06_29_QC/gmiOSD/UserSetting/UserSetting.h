//--------------------------------------------------
// Eeprom Version Code
//--------------------------------------------------
//更改软件版本号
#define _VERSION_CODE               0x33       /*变化范围0x00~0xFA */   

//*********************************************************************************************************
//**I:SOURCE 通道选择项设置项*****************************************************************************
//***************************************************************************************************
//通过设置下面变量_ON  _OFF 来开关通道
//
//注意不要把上面设置的默认SOURCE 关掉
//-------------------------------------------------------------
#define _VGA_SUPPORT_EN                                           _ON
#define _VIDEO_AV_SUPPORT_EN                                 _ON
#define _VIDEO_SV_SUPPORT_EN                                 _ON
#define _VIDEO_TV_SUPPORT_EN                                 _ON



//*********************************************************************************************************
//**通道切换背景颜色*****************************************************************************
//------------------------------------------------
//_CHANGE_SOURCE_BACKGROUCD_COLOR选择 _BACK_COLOR 通道切换关背光,且黑屏
//_CHANGE_SOURCE_BACKGROUCD_COLOR选择  _BLUE_COLOR    通道切换不关背光,且蓝屏
#define _BACK_COLOR     0
#define _BLUE_COLOR     1

#define _CHANGE_SOURCE_BACKGROUCD_COLOR       _BACK_COLOR

//*********************************************************************************************************
//**H:SOURCE 默认设置项*****************************************************************************
//------------------------------------------------
//  _SOURCE_VGA               //  _SOURCE_VIDEO_AV  //  _SOURCE_VIDEO_SV   //  _SOURCE_VIDEO_TV
// 程序烧入时, _NORMAL_SOURCE 设置什么通道就选择什么, 上面提供选择  
//---------------------------------------
#define _INPUTSOURCE                        _SOURCE_VIDEO_TV  


//*********************************************************************************************************
//**A: 灯设置项*****************************************************************************
//---------------------------------
//红灯   请在下面相应位置选择RedLED
//绿灯  请在下面相应位置选择GreenLED
//橙灯  请在下面相应位置选择OrangeLED
//灯灭  请在下面相应位置选择BlackLED
//--------------------------- 
#define    RedLED        0
#define    GreenLED      1
#define    OrangeLED     2
#define    BlackLED        3         
//-----------------------------------------------------------
//根据客户需求在下面选择每个状态需要的灯
//-----------------------------------------------------------
#define KeyPowerUpLED     /* 遥控按键开机灯的颜色*/     RedLED
#define PowerUpLED           /* 上电灯的颜色*/                                   RedLED
#define PowerDownLED      /* 关机灯的颜色*/                                    BlackLED
#define RunLED                   /* 运行(有信号与TV)灯的颜色*/        GreenLED
#define NosignalStateLED    /* 运行灯的颜色*/                                   RedLED


//*********************************************************************************************************
//**C: 按键设置项*****************************************************************************
//-------------------------------------------------
//  下面选择几键的按键
//当要用7键按键板时, _KEY_TYPE_OSD007 要选择_6KEY_SUPPORT
//当要用6键按键板时 ,_KEY_TYPE_OSD007 要选择_6KEY_SUPPORT 
//当要用5键按键板时 ,_KEY_TYPE_OSD007 要选择_5KEY_SUPPORT
//---------------------------------------------------
//        _DISABLE        //_ENABLE  
#define  _5KEY_SUPPORT       0
#define  _6KEY_SUPPORT       1
#define  _7KEY_SUPPORT       2    /*注意：与遥控器按键一样*/
#define  _KEY_TYPE_OSD007                               _7KEY_SUPPORT



//*********************************************************************************************************
//**D: 上电开机设置项*****************************************************************************
//---------------------------------
//上电关机POWERUPSTATE  设置为0,
//上电开机POWERUPSTATE 设置为1,
//上电保存POWERUPSTATE 设置为2,
//--------------------------- 
#define POWERUPSTATE                      2



//*********************************************************************************************************
//**E2: 语言选择设置项*****************************************************************************
//-----------------------------------------------------------
//需要的语言设置为1,不需要的设置为0.
//-----------------------------------------------------------
#define ENGLISH_EN                  1 //  1 : open_this_language  0: close_this_language
#define LNG_DEU_EN                  1 //  1 : open_this_language  0: close_this_language
#define LNG_FRA_EN                  1 //  1 : open_this_language  0: close_this_language
#define LNG_ITA_EN                  1 //  1 : open_this_language  0: close_this_language
#define LNG_SPA_EN                  1 //  1 : open_this_language  0: close_this_language
#define LNG_CHI_S_EN                1 //  1 : open_this_language  0: close_this_language
#define LNG_CHI_T_EN                1 //  1 : open_this_language  0: close_this_language
#define LNG_PORT_EN                 1 //  1 : open_this_language  0: close_this_language
#define LNG_RUSS_EN		            1 //  1 : open_this_language  0: close_this_language
#define LNG_KOREAN_EN               0 //  1 : open_this_language  0: close_this_language
#define LNG_ARABIC_EN               0 //  1 : open_this_language  0: close_this_language

//*********************************************************************************************************
//**E: 默认语言设置项*****************************************************************************
//---------------------------------------------------
//  设置默认语言
//----------------------------------------------------
#define _DEFAULT_ENG		 0    //  
#define _DEFAULT_DEU	       1
#define _DEFAULT_RUSS		 2
#define _DEFAULT_FRA		 3
#define _DEFAULT_ITA		 4
#define _DEFAULT_SPA		 5
#define _DEFAULT_CHI_S	      6
#define _DEFAULT_CHI_T		 7
#define _DEFAULT_PORT		 8
#define _DEFAULT_KOREAN		 9
#define _DEFAULT_ARABIC		 0x0a
//---------------------------------------------------
//例如 _LANGUAGE选择为_DEFAULT_ENG,则烧入代码后,默认为_DEFAULT_ENG(语言)
//----------------------------------------------------
#define _LANGUAGE                   _DEFAULT_ENG

//*********************************************************************************************************
//**G: 复位语言是否保存设置项*****************************************************************************
//-----------------------------------------
//如果LANGUAGE_SAVE_ENABLE设置为1,则复位后为上面的默认语言
//如果LANGUAGE_SAVE_ENABLE设置为0,则复位后为保存你现在设置的语言
//---------------------------------
#define LANGUAGE_SAVE_ENABLE               1


//***************************************************************************************************
//LOGO 功能***************************************************************
//***************************************************************************************************
//当要客户不要LOGO, _LOGO_ENABLE 要选择_DISABLE
//当要客户要LOGO,      _LOGO_ENABLE 要选择_ENABLE
//        _DISABLE        //_ENABLE  
//-----------------------------------------------------------
/*LOGO 开关设置*/#define _LOGO_EN                                    _DISABLE//
#define _LOGO_1_BIT           0         
#define _LOGO_2_BIT           1
/*LOGO     BIT设置*/#define _LOGO_BIT_SET                                 _LOGO_1_BIT
/*LOGO 宽度设置*/#define _LOGO_WIDTH                                 40
/*LOGO 高度设置*/#define _LOGO_HEIGHT                                4
/*LOGO 放大设置*/#define _LOGO_DOUBLE_OSD                       _DISABLE//
//设置LOGO颜色对应关系 0x00( 黑)    0x01(红 )     0x02( 绿)    0x03(蓝)   0x04(黄)
//                                                     0x05(青)          0x06(红紫色)        0x07( 白)
/*LOGO 字0 的颜色设置*/#define _LOGO_COLOR0                                    0x01       /*_LOGO_BIT_SET为_LOGO_2_BIT时，才起作用，变化范围0x00~0x0F */   
/*LOGO 字1 的颜色设置*/#define _LOGO_COLOR1                                    0x02       /*_LOGO_BIT_SET为_LOGO_2_BIT时，才起作用，变化范围0x00~0x0F */   
/*LOGO 字2 的颜色设置*/#define _LOGO_COLOR2                                    0x00     /*变化范围0x00~0x0F */   
/*LOGO 字的背景颜色设置*/#define _LOGO_COLOR3                            0x03       /*变化范围0x00~0x0F */   
/*画面的背景颜色设置*/#define LOGO_BackgroundColor_Red          0x00       /*变化范围0x00~0xFF */   
/*画面的背景颜色设置*/#define LOGO_BackgroundColor_Green      0x00       /*变化范围0x00~0xFF */   
/*画面的背景颜色设置*/#define LOGO_BackgroundColor_Blue         0xff       /*变化范围0x00~0xFF */   
/*LOGO 显示时间*/#define LOGO_TIMER_DELAY              12      /*单位ms*/

//-------------------------------------------------------------------
//下面是LOGO 菜单的位置调整
//-------------------------------------------------------------------
/*水平调整*/#define _LOGO_H_OFFSET          25   
/*垂直调整*/#define _LOGO_V_OFFSET           50

//*********************************************************************************************************
//**J:菜单位置设置项*****************************************************************************
//-------------------------------------------------------------------
//下面是左上角通道位置调整项, 直接改变后面的数字移动菜单
//-------------------------------------------------------------------
/*水平调整*/#define _LIFT_UP_H_OFFSET          0         /*一般不为负值*/
/*一般不要更改_OSD_HPOSITION_OFFSET,如果_SOURCE_H_OFFSET为0后,通道显示菜单还偏右就增加此值,但所有的OSD位置都要重新调整*/
/*水平调整*/#define _OSD_HPOSITION_OFFSET           1
//-------------------------------------------------------------------
//下面是主菜单位置调整项, 直接改变后面的数字移动菜单
//为负数水平向左或向上移动, 正数相反
//-------------------------------------------------------------------
/* 单倍垂直调整*/#define _MAINMENU_V_OFFSET          0                  /*数字变化范围  -50 到   50 */  
/* 单倍水平调整*/#define _MAINMENU_H_OFFSET          0                   /*数字变化范围  -50 到   50 */  
/* 双倍垂直调整*/#define _MAINMENU_DOUBLE_V_OFFSET          0       /*数字变化范围  -50 到   50 */  
/* 双倍水平调整*/#define _MAINMENU_DOUBLE_H_OFFSET         2        /*数字变化范围  -50 到   50 */     
//-------------------------------------------------------------------
//下面是右上角OSD位置调整项, 直接改变后面的数字移动菜单
//-------------------------------------------------------------------
/* 水平调整*/#define _RIGHT_UP_OSD_H_OFFSET          40      /*数字变化范围  0 到   100 */
//-------------------------------------------------------------------
//下面是无信号,自动调整位置调整项, 直接改变后面的数字移动菜单
//-------------------------------------------------------------------
/*单倍水平调整*/#define _AUTO_H_OFFSET          50         /*数字变化范围  0 到   100 */
/*单倍垂直调整*/#define _AUTO_V_OFFSET          50          /*数字变化范围  0 到   100 */
/*双倍水平调整*/#define _AUTO_DOUBLE_H_OFFSET          50         /*数字变化范围  0 到   100 */
/*双倍垂直调整*/#define _AUTO_DOUBLE_V_OFFSET          50          /*数字变化范围  0 到   100 */
//-------------------------------------------------------------------
//下面是无信号,自动调整位置调整项, 直接改变后面的数字移动菜单
//-------------------------------------------------------------------
/*单倍水平调整*/#define _VOLUME_H_OFFSET         50         /*数字变化范围  0 到   100 */
/*单倍垂直调整*/#define _VOLUME_V_OFFSET          100      /*数字变化范围  0 到   100 */
/* 双倍水平调整*/#define _VOLUME_DOUBLE_H_OFFSET         50         /*数字变化范围  0 到   100 */
/* 双倍垂直调整*/#define _VOLUME_DOUBLE_V_OFFSET          100      /*数字变化范围  0 到   100 */



//*********************************************************************************************************
//**J:TV设置项***************************************************************************
//_TV_TYPE_SUPPORT              _TV_TYPE_NOT_SUPPORT

#define _TV_NTSC_M_SUPPORT       _TV_TYPE_NOT_SUPPORT    // 60Hz Sound 4.5M  NTSC M
#define _TV_NTSC_4_BG_SUPPORT    _TV_TYPE_NOT_SUPPORT    // 60Hz Sound 5.5M  NTSC 4/BG
#define _TV_NTSC_4_DK_SUPPORT    _TV_TYPE_NOT_SUPPORT    // 60Hz Sound 6.5M  NTSC 4/DK
#define _TV_NTSC_4_I_SUPPORT     _TV_TYPE_NOT_SUPPORT    // 60Hz Sound 6.0M  NTSC 4/I
#define _TV_PAL_M_SUPPORT        _TV_TYPE_NOT_SUPPORT    // 60Hz Sound 4.5M  PAL M

#define _TV_PAL_BG_SUPPORT       _TV_TYPE_SUPPORT        // 50Hz Sound 5.5M  PAL B/G
#define _TV_PAL_I_SUPPORT        _TV_TYPE_SUPPORT        // 50Hz Sound 6.0M  PAL I
#define _TV_PAL_DK_SUPPORT       _TV_TYPE_SUPPORT        // 50Hz Sound 6.5M  PAL D/K
#define _TV_PAL_N_SUPPORT        _TV_TYPE_NOT_SUPPORT    // 50Hz Sound 4.5M  PAL N

#define _TV_SECAM_BG_SUPPORT     _TV_TYPE_SUPPORT    // 50Hz Sound 5.5M  SECAM B/G
#define _TV_SECAM_DK_SUPPORT     _TV_TYPE_SUPPORT    // 50Hz Sound 6.5M  SECAM D/K
#define _TV_SECAM_L_SUPPORT      _TV_TYPE_NOT_SUPPORT        // 50Hz Sound 6.5M  SECAM L
#define _TV_SECAM_LL_SUPPORT     _TV_TYPE_NOT_SUPPORT        // 50Hz Sound 6.5M  Secam L'
//------------------------------------
 //单声表_CARRIER_SELECT  选择_INTER_CARRIER  
 //双声表_CARRIER_SELECT  选择_SPLIT_CARRIER
//中频_PIF_FREQ直接选择
//-----------------------------------
//33400,33900,34200,38000,38900,45750 KHz
#define _PIF_FREQ               38000  // KHz  38900
//_SPLIT_CARRIER,_INTER_CARRIER 
#define _CARRIER_SELECT          _INTER_CARRIER
//-----------------------------------------------------
//_NTSC_SEARCH_TABLE 选择_ENABLE 为查表搜台
//_NTSC_SEARCH_TABLE 选择_DISABLE 为连续搜台,
//        _DISABLE        //_ENABLE  
#define _NTSC_SEARCH_TABLE       _DISABLE

/*
中频为38000MHZ 部分高频头型号：TNF8317、TDQ-6FT-116k1、 TDQ-6F6-116CW1 、 AFT16000、 AFT7W004、 AFT7W001 、 AFT7W001G、 AFT7W000G、 AFT1W005G 、 AFT1W000 .
中频为38900MHZ 部分高频头型号：TDTG-S122D 、 TDQ-6F6-W125、 TDQ-6F6-126CWA、AFT17009、 AFT13100、 AFT7W105G 、 AFT7W103 、 AFT7W100G、 AFT1W108G 、 AFT1W107G .
中频为45750MHZ 部分高频头型号：TNF5337、 TNF5331 、 AFT1L301 .

中频为38000MHZ 部分声表型号： SY3806 、 SY3809 、 SY3819 .
中频为38900MHZ 部分声表型号： SY8919、 SY8920、 SY8924 .
中频为45750MHZ 部分声表型号： SY4502 、 SY4504 .
*/
//     
//----------------------------------------------------
//   input tv number mode    
//---------------------------------------------
#define DirectnessInputNumber       1         //直接出入台
#define IndirectInputNumber            0        //先输入-/--  再输入台
#define _INPUT_NUMBER_MODE   IndirectInputNumber 


//*********************************************************************************************************
//设置IR_Test_EN 为_ENABLE  表示 此时为测试遥控码
//设置IR_Test_EN 为_DISABLE  表示 程序为正常运行
//        _DISABLE        //_ENABLE  
//测试完遥控码后,一定要把IR_Test_EN设置为_DISABLE
//*****************************************************************************
#define IR_Test_EN          _DISABLE


//*********************************************************************************************************
//设置DVD_EN  为_ENABLE  表示 此时为程序加入了DVD控制电路
//设置DVD_EN 为_DISABLE  表示 程序为正常运行
//        _DISABLE        //_ENABLE  
//*****************************************************************************
#define DVD_EN          _ENABLE

//----------------------------------------------------------
// 进入工厂菜单方法 : 在主菜单选择Reset时,
//用遥控器输入2025
//-----------------------------------------------------
//#define _UARTIR      _ENABLE          //为客户码设定的
//#define  _UARTTX    _DISABLE//为区别发送和接受的
//#define  _AT020

