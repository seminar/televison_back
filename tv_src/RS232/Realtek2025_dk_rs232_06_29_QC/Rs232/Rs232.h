








#define _UARTIR      _ENABLE          //为客户码设定的
#define  _UARTTX    _ENABLE//为区别发送和接受的
#define  _DISIRTRIS    _DISABLE//为区别发送和接受的

//-----------------遥控器型号定义---------------------------------
#define  IR_AT020     0
#define  IR_AT002     1
#define  IR_TOPTECH  2 

#define IR_TYPE           IR_TOPTECH 






//---------------------------------------------------------------------------------------
extern void ProssMCUIRHandle(BYTE Keycode);
extern void ProssMCUTXHandle(BYTE Keycode);
extern void ProssMCU2DVDkeyHandle(BYTE Keycode);
extern void Trs2DVDIrSend(BYTE IRData);
extern void ProssMCUTXHandlePOWER(BYTE Keycode);// 2011_07_11
extern void Trs2DVDIrSendHead(void );
extern void SendByteData(BYTE ucValue);













