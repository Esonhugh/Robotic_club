/* MX900 program by Semia 
   系统程序，请勿修改。
*/
	
///////////////////////////XBOX手柄
#include <XBOXUSB.h>
#include <avr/pgmspace.h>

#ifdef dobogusinclude
#include <spi4teensy3.h>
#include <SPI.h>
#endif

#include<math.h>
#include <EEPROM.h>

#ifndef _MX900_h_
#define _MX900_h_

USB Usb;
XBOXUSB Xbox(&Usb);

#define uchar unsigned char
#define uint unsigned int
#define ulong unsigned long
///////////////////////////端口定义
#define MX_digitalIO_1  46 // PWM
#define MX_digitalIO_2  4 // PWM
#define MX_digitalIO_3  12 // PWM
#define MX_digitalIO_4  6 // PWM
#define MX_digitalIO_5  7 // PWM
#define MX_digitalIO_6  8 // PWM
#define MX_digitalIO_7  45 // PWM
#define MX_digitalIO_8  44 // PWM
#define MX_digitalIO_9  39 //-
#define MX_digitalIO_10 29 //-
#define MX_digitalIO_11 28 //-
#define MX_digitalIO_12 27 //-
#define MX_buzzerIO 24
#define MX_screenBusy 2 //INT0
#define MX_analogIO_1 A2 
#define MX_analogIO_2 A1
#define MX_analogIO_3 A0
#define MX_analogIO_4 A3
#define MX_analogIO_5 A4
#define MX_analogIO_6 A5
#define MX_analogIO_7 A12
#define MX_analogIO_8 A13
#define MX_analogIO_9 A11
#define MX_analogIO_10 A10
#define MX_analogIO_11 A9
#define MX_analogIO_12 A8
#define MX_battery A7
#define MX_batterySafety A6

////////////////////////////本土化语句

#define MX_runUSB Usb.Task
#define MX_gamepadConnected() Xbox.Xbox360Connected
#define MX_gamepadRightX Xbox.getAnalogHat(RightHatX)/328
#define MX_gamepadRightY Xbox.getAnalogHat(RightHatY)/328
#define MX_gamepadLeftX Xbox.getAnalogHat(LeftHatX)/328
#define MX_gamepadLeftY Xbox.getAnalogHat(LeftHatY)/328
#define MX_gamepadClick Xbox.getButtonClick
#define MX_gamepadPress Xbox.getButtonPress
#define MX_waitButtonUp() while(!MX_screenGetButton())
#define Home Xbox
#define PL 1
#define BOX 2
#define BOXF 3
#define CIR 1
#define CIRF 2
#define CBOX 1
#define CBOXF 2
#define Size12 12
#define Size16 16
#define Size24 24
#define Size32 32
#define Size48 48
#define Size64 64
#define GetOFF 0
#define GetXY 1
#define GetButton 2
#define MXangle 1
#define MXspeed 2
#define MXvoltage 3
#define MXcurrent 4
#define MXtemperature 5
#define MXrestart 6
////////////////////////////全局变量
long MX_motorAngleN;//电机角度
int MX_motorDataN;//电机其他数据
uint MX_screenTouchX;
uint MX_screenTouchY;
byte MX_receive[5];//接收数据变量
uchar MX_screen_function;
uint MX_screen_X1;
uint MX_screen_Y1;
uint MX_screen_X2;
uint MX_screen_Y2;
uchar MX_screen_C;//颜色号（0~63）
uint MX_screen_Color;//颜色值 0~65535
uint MX_screen_Pn;//第几幅画（0~512）
uint MX_screen_r;//圆半径
uchar MX_screen_char1;//临时uchar变量
uchar MX_screen_char2;
uchar MX_screenButtonN;
long MX_screenInputWholeNumber;
float MX_screenInputDecimalNumber;
uchar MX_S_n;//显示界面所用变量
bool MX_screenButtonBuzzer=1;//是否打开按键蜂鸣器
uchar MX_screenMenuNum=1;
bool MX_screenMenuLoop=1;//主目录循环标志
bool MX_screenMenuLoop2=1;//子目录循环标志
bool MX_screenMenuLoop3=1;
long MX_screenWholeNum_n;//输入数字变量
//读取外部设备信息
unsigned int MX_IDcode;//硬件ID，1为高速电机
unsigned char MX_version_h;//固件版本号，高位
unsigned char MX_version_l;//固件版本号，低位
unsigned char MX_menuMain_last;//目录的上一次序号，用于点选dock栏选项时减少刷新
long MX_screenBatteryV_n;//用于记录时间，使电量显示间隔刷新
int MX_dataSize1;//用于屏幕发送数据时测量数据长度
int MX_dataSize2; 
char MX_sendChar;//用于屏幕擦送数据时的临时存储
bool MX_PortView_turnOff;//用于记录查看端口中界面结束跳出，跳出的一轮直接按导致跳出的按键编号执行，而不重新读取按键
/*屏幕显示数据，存储于ROM中*/
//端口查看页面的上下两排端口，显示port 1-12状态
const char MX_ScreenMessage_Port1Init[] PROGMEM  = {"SBC(34);CBOF(173,430,260,470,5,34);BTN(5,173,430,260,470,0);PS24(1,181,437,'Port 1',36,0);"};//Port 1 初始化，未连接 
const char MX_ScreenMessage_Port2Init[] PROGMEM  = {"SBC(34);CBOF(270,430,357,470,5,34);BTN(6,270,430,357,470,0);PS24(1,278,437,'Port 2',36,0);"};//Port 2 初始化，未连接
const char MX_ScreenMessage_Port3Init[] PROGMEM  = {"SBC(34);CBOF(367,430,454,470,5,34);BTN(7,367,430,454,470,0);PS24(1,375,437,'Port 3',36,0);"};//Port 3 初始化，未连接 
const char MX_ScreenMessage_Port4Init[] PROGMEM  = {"SBC(34);CBOF(464,430,551,470,5,34);BTN(8,464,430,551,470,0);PS24(1,472,437,'Port 4',36,0);"};//Port 4 初始化，未连接
const char MX_ScreenMessage_Port5Init[] PROGMEM  = {"SBC(34);CBOF(561,430,648,470,5,34);BTN(9,561,430,648,470,0);PS24(1,569,437,'Port 5',36,0);"};//Port 5 初始化，未连接
const char MX_ScreenMessage_Port6Init[] PROGMEM  = {"SBC(34);CBOF(658,430,745,470,5,34);BTN(10,658,430,745,470,0);PS24(1,666,437,'Port 6',36,0);"};//Port 6 初始化，未连接
const char MX_ScreenMessage_Port7Init[] PROGMEM  = {"SBC(34);CBOF(658,81,745,121,5,34);BTN(11,658,81,745,121,0);PS24(1,666,88,'Port 7',36,0);"};//Port 7 初始化，未连接
const char MX_ScreenMessage_Port8Init[] PROGMEM  = {"SBC(34);CBOF(561,81,648,121,5,34);BTN(12,561,81,648,121,0);PS24(1,569,88,'Port 8',36,0);"};//Port 8 初始化，未连接
const char MX_ScreenMessage_Port9Init[] PROGMEM  = {"SBC(34);CBOF(464,81,551,121,5,34);BTN(13,464,81,551,121,0);PS24(1,472,88,'Port 9',36,0);"};//Port 9 初始化，未连接
const char MX_ScreenMessage_Port10Init[] PROGMEM  = {"SBC(34);CBOF(367,81,454,121,5,34);BTN(14,367,81,454,121,0);PS24(1,370,88,'Port 10',36,0);"};//Port 10 初始化，未连接
const char MX_ScreenMessage_Port11Init[] PROGMEM  = {"SBC(34);CBOF(270,81,357,121,5,34);BTN(15,270,81,357,121,0);PS24(1,273,88,'Port 11',36,0);"};//Port 11 初始化，未连接
const char MX_ScreenMessage_Port12Init[] PROGMEM  = {"SBC(34);CBOF(173,81,260,121,5,34);BTN(16,173,81,260,121,0);PS24(1,176,88,'Port 12',36,0);"};//Port 12 初始化，未连接
const char MX_ScreenMessage_PortUSBInit[] PROGMEM  = {"SBC(34);CBOF(755,420,842,470,5,34);BTN(17,755,420,842,470,0);PS32(1,775,431,'USB',36,0);"};//Port USB 初始化，未连接

const char MX_ScreenMessage_Port1Lightup[] PROGMEM  = {"SBC(35);CBOF(173,430,260,470,5,35);PS24(1,181,437,'Port 1',16,0);"};//Port 1 选中 
const char MX_ScreenMessage_Port2Lightup[] PROGMEM  = {"SBC(35);CBOF(270,430,357,470,5,35);PS24(1,278,437,'Port 2',16,0);"};//Port 2 选中 
const char MX_ScreenMessage_Port3Lightup[] PROGMEM  = {"SBC(35);CBOF(367,430,454,470,5,35);PS24(1,375,437,'Port 3',16,0);"};//Port 3 选中 
const char MX_ScreenMessage_Port4Lightup[] PROGMEM  = {"SBC(35);CBOF(464,430,551,470,5,35);PS24(1,472,437,'Port 4',16,0);"};//Port 4 选中 
const char MX_ScreenMessage_Port5Lightup[] PROGMEM  = {"SBC(35);CBOF(561,430,648,470,5,35);PS24(1,569,437,'Port 5',16,0);"};//Port 5 初始化，未连接
const char MX_ScreenMessage_Port6Lightup[] PROGMEM  = {"SBC(35);CBOF(658,430,745,470,5,35);PS24(1,666,437,'Port 6',16,0);"};//Port 6 初始化，未连接
const char MX_ScreenMessage_Port7Lightup[] PROGMEM  = {"SBC(35);CBOF(658,81,745,121,5,35);PS24(1,666,88,'Port 7',16,0);"};//Port 7 初始化，未连接
const char MX_ScreenMessage_Port8Lightup[] PROGMEM  = {"SBC(35);CBOF(561,81,648,121,5,35);PS24(1,569,88,'Port 8',16,0);"};//Port 8 初始化，未连接
const char MX_ScreenMessage_Port9Lightup[] PROGMEM  = {"SBC(35);CBOF(464,81,551,121,5,35);PS24(1,472,88,'Port 9',16,0);"};//Port 9 初始化，未连接
const char MX_ScreenMessage_Port10Lightup[] PROGMEM  = {"SBC(35);CBOF(367,81,454,121,5,35);PS24(1,370,88,'Port 10',16,0);"};//Port 10 初始化，未连接
const char MX_ScreenMessage_Port11Lightup[] PROGMEM  = {"SBC(35);CBOF(270,81,357,121,5,35);PS24(1,273,88,'Port 11',16,0);"};//Port 11 初始化，未连接
const char MX_ScreenMessage_Port12Lightup[] PROGMEM  = {"SBC(35);CBOF(173,81,260,121,5,35);PS24(1,176,88,'Port 12',16,0);"};//Port 12 初始化，未连接
const char MX_ScreenMessage_PortUSBLightup[] PROGMEM  = {"SBC(35);CBOF(755,420,842,470,5,35);PS32(1,775,431,'USB',16,0);"};//Port USB 初始化，未连接

///////////////////////////弹射器控制程序
void MX_relayControl(unsigned char MX_motorControl_port)
{
  switch(MX_motorControl_port)//端口号
  {
  case 1:{MX_motorControl_port=MX_digitalIO_1;}break;
  case 2:{MX_motorControl_port=MX_digitalIO_2;}break;
  case 3:{MX_motorControl_port=MX_digitalIO_3;}break;
  case 4:{MX_motorControl_port=MX_digitalIO_4;}break;
  case 5:{MX_motorControl_port=MX_digitalIO_5;}break;
  case 6:{MX_motorControl_port=MX_digitalIO_6;}break;
  case 7:{MX_motorControl_port=MX_digitalIO_7;}break;
  case 8:{MX_motorControl_port=MX_digitalIO_8;}break;
  case 9:{MX_motorControl_port=MX_digitalIO_9;}break;
  case 10:{MX_motorControl_port=MX_digitalIO_10;}break;
  case 11:{MX_motorControl_port=MX_digitalIO_11;}break;
  case 12:{MX_motorControl_port=MX_digitalIO_12;}break;
  }
  digitalWrite(MX_motorControl_port,LOW);//通讯标志位置低，通知开始发送
  if(MX_motorControl_port==MX_digitalIO_6)
  { Serial1.write(0xa5);
    Serial1.write(1);Serial1.write(9);Serial1.write(9);Serial1.write(1);
    Serial1.write(6);
    Serial1.write(1);Serial1.write(5);//发送全部内容  
  }
  else
  {
    Serial3.write(0xa5);
    Serial3.write(1);Serial3.write(9);Serial3.write(9);Serial3.write(1);
    Serial3.write(6);
    Serial3.write(1);Serial3.write(5);//发送全部内容  
  }
  delayMicroseconds(800);
  digitalWrite(MX_motorControl_port,HIGH); //通讯标志位置高，通知结束发送
}
///////////////////////////电机控制程序
void MX_motorControl(unsigned char MX_motorControl_port,unsigned char MX_motorControl_function,char MX_motorControl_content1,long MX_motorControl_content2)
{ byte MX_motorControl_send[7];//发送数据
  switch(MX_motorControl_port)//端口号
  {
	case 1:{MX_motorControl_port=MX_digitalIO_1;}break;
	case 2:{MX_motorControl_port=MX_digitalIO_2;}break;
	case 3:{MX_motorControl_port=MX_digitalIO_3;}break;
	case 4:{MX_motorControl_port=MX_digitalIO_4;}break;
	case 5:{MX_motorControl_port=MX_digitalIO_5;}break;
	case 6:{MX_motorControl_port=MX_digitalIO_6;}break;
	case 7:{MX_motorControl_port=MX_digitalIO_7;}break;
	case 8:{MX_motorControl_port=MX_digitalIO_8;}break;
	case 9:{MX_motorControl_port=MX_digitalIO_9;}break;
	case 10:{MX_motorControl_port=MX_digitalIO_10;}break;
	case 11:{MX_motorControl_port=MX_digitalIO_11;}break;
	case 12:{MX_motorControl_port=MX_digitalIO_12;}break;
  }
  digitalWrite(MX_motorControl_port,LOW);//通讯标志位置低，通知开始发送
  MX_motorControl_send[0]=0xa5; //发送起始位
  MX_motorControl_send[1]=MX_motorControl_function; //功能位
  MX_motorControl_send[2]=MX_motorControl_content1;//内容位1
  MX_motorControl_send[3]=MX_motorControl_content2>>24;//内容位2
  MX_motorControl_send[4]=MX_motorControl_content2>>16;
  MX_motorControl_send[5]=MX_motorControl_content2>>8; 
  MX_motorControl_send[6]=MX_motorControl_content2;
  MX_motorControl_send[7]=MX_motorControl_send[1]^MX_motorControl_send[2]^MX_motorControl_send[3]^MX_motorControl_send[4]^MX_motorControl_send[5]^MX_motorControl_send[6];//校验位
  if(MX_motorControl_port==MX_digitalIO_6)
  {
    Serial1.write(MX_motorControl_send[0]);Serial1.write(MX_motorControl_send[1]);
    Serial1.write(MX_motorControl_send[2]);Serial1.write(MX_motorControl_send[3]);
    Serial1.write(MX_motorControl_send[4]);Serial1.write(MX_motorControl_send[5]);
    Serial1.write(MX_motorControl_send[6]);Serial1.write(MX_motorControl_send[7]);//发送全部内容  
  }
  else
  {
    Serial3.write(MX_motorControl_send[0]);Serial3.write(MX_motorControl_send[1]);
    Serial3.write(MX_motorControl_send[2]);Serial3.write(MX_motorControl_send[3]);
    Serial3.write(MX_motorControl_send[4]);Serial3.write(MX_motorControl_send[5]);
    Serial3.write(MX_motorControl_send[6]);Serial3.write(MX_motorControl_send[7]);//发送全部内容
  }
  delayMicroseconds(1000);
  digitalWrite(MX_motorControl_port,HIGH); //通讯标志位置高，通知结束发送
 }
 //等待端口完成
void MX_motorWait(unsigned char MX_motorControl_port)
{
  switch(MX_motorControl_port)
  {
    case 1:{while(analogRead(MX_analogIO_1)<500);}break;
    case 2:{while(analogRead(MX_analogIO_2)<500);}break;
    case 3:{while(analogRead(MX_analogIO_3)<500);}break;
    case 4:{while(analogRead(MX_analogIO_4)<500);}break;
    case 5:{while(analogRead(MX_analogIO_5)<500);}break;
    case 6:{while(analogRead(MX_analogIO_6)<500);}break;
    case 7:{while(analogRead(MX_analogIO_7)<500);}break;
    case 8:{while(analogRead(MX_analogIO_8)<500);}break;
    case 9:{while(analogRead(MX_analogIO_9)<500);}break;
    case 10:{while(analogRead(MX_analogIO_10)<500);}break;
    case 11:{while(analogRead(MX_analogIO_11)<500);}break;
    case 12:{while(analogRead(MX_analogIO_12)<500);}break;
  }
}
 //获取硬件信息，1.硬件ID（类型）2.固件版本 3.生产日期
bool MX_hardwareInfo(unsigned char MX_motorControl_port)
 {
    switch(MX_motorControl_port)//端口号
    {
      case 1:{MX_motorControl_port=MX_digitalIO_1;}break;
      case 2:{MX_motorControl_port=MX_digitalIO_2;}break;
      case 3:{MX_motorControl_port=MX_digitalIO_3;}break;
      case 4:{MX_motorControl_port=MX_digitalIO_4;}break;
      case 5:{MX_motorControl_port=MX_digitalIO_5;}break;
      case 6:{MX_motorControl_port=MX_digitalIO_6;}break;
      case 7:{MX_motorControl_port=MX_digitalIO_7;}break;
      case 8:{MX_motorControl_port=MX_digitalIO_8;}break;
      case 9:{MX_motorControl_port=MX_digitalIO_9;}break;
      case 10:{MX_motorControl_port=MX_digitalIO_10;}break;
      case 11:{MX_motorControl_port=MX_digitalIO_11;}break;
      case 12:{MX_motorControl_port=MX_digitalIO_12;}break;
    }    
    unsigned char MX_motorData_wait=0xff;
    digitalWrite(MX_motorControl_port,LOW);//通讯标志位置低，通知开始发送
    if(MX_motorControl_port==MX_digitalIO_6)
    {
      Serial1.write(0xa5);Serial1.write(0xa5);
      Serial1.write(0xa5);Serial1.write(0xa5);
      Serial1.write(0xa5);Serial1.write(0xa5);
      Serial1.write(0xa5);Serial1.write(0xa5);
  delay(1);//等待1ms
  digitalWrite(MX_motorControl_port,HIGH); //通讯标志位置高，通知结束发送
      while(MX_motorData_wait>0)
      {
        MX_motorData_wait--;
        if(Serial1.available()>5)
        {MX_motorData_wait=0;}
      }
        if(Serial1.available()>5)
        {
          if(Serial1.read()==0xa5) 
          {         
            MX_receive[0]=Serial1.read();
            MX_receive[1]=Serial1.read();
            MX_receive[2]=Serial1.read();
            MX_receive[3]=Serial1.read();
            MX_receive[4]=Serial1.read();
            if(MX_receive[4]==MX_receive[0]^MX_receive[1]^MX_receive[2]^MX_receive[3])
            { 
              MX_IDcode=MX_receive[0]*256+MX_receive[1];//硬件ID，1为高速电机
              MX_version_h=MX_receive[2];//固件版本号，高位
              MX_version_l=MX_receive[3];//固件版本号，低位
              return 1;
            }
          }
        }
    }
    else
    {
      Serial3.write(0xa5);Serial3.write(0xa5);
      Serial3.write(0xa5);Serial3.write(0xa5);
      Serial3.write(0xa5);Serial3.write(0xa5);
      Serial3.write(0xa5);Serial3.write(0xa5);
  delay(1);//等待1ms
  digitalWrite(MX_motorControl_port,HIGH); //通讯标志位置高，通知结束发送
      while(MX_motorData_wait>0)
      {
        MX_motorData_wait--;
        if(Serial3.available()>5)
        {MX_motorData_wait=0;}
      }
        if(Serial3.available()>5)
        {
          if(Serial3.read()==0xa5) 
          {         
            MX_receive[0]=Serial3.read();
            MX_receive[1]=Serial3.read();
            MX_receive[2]=Serial3.read();
            MX_receive[3]=Serial3.read();
            MX_receive[4]=Serial3.read();
            if(MX_receive[4]==MX_receive[0]^MX_receive[1]^MX_receive[2]^MX_receive[3])
            { 
              MX_IDcode=MX_receive[0]*256+MX_receive[1];//硬件ID，1为高速电机
              MX_version_h=MX_receive[1];//固件版本号，高位
              MX_version_l=MX_receive[2];//固件版本号，低位
              return 1;
            }
          }
        }
    }      
  return 0;
}
bool MX_motorData(unsigned char MX_motorData_port,unsigned char MX_motorData_function)//返回6则读取成功，值在motor_inf_content
{    
    unsigned char MX_motorData_wait=0xff;
    while(Serial1.read()>= 0);while(Serial3.read()>= 0);
    MX_motorControl(MX_motorData_port,23,MX_motorData_function,0);
  if(MX_motorData_port==6)
  {
    while(MX_motorData_wait>0)
    {
      MX_motorData_wait--;
      if(MX_motorData_function>1 && Serial1.available()>2)
        {MX_motorData_wait=0;}
      else if(Serial1.available()>4)
        {MX_motorData_wait=0;}
    }
    if(MX_motorData_function>1 && Serial1.available()>2)//获取其他数据，类型char
    {
      if(Serial1.read()==0xa5) 
      {         
        MX_receive[0]=Serial1.read();
        MX_receive[1]=Serial1.read();
        MX_receive[2]=Serial1.read();
        if(MX_receive[2]==MX_receive[0]^MX_receive[1])
        { 
          MX_motorDataN=0;
          MX_motorDataN=MX_receive[0];
          MX_motorDataN=MX_motorDataN<<8|MX_receive[1];
          while(Serial1.read()>= 0);
          return 1;//获取信息成功
        } 
        else  {while(Serial1.read()>= 0);return 0;}//校验失败
      }
      else {while(Serial1.read()>= 0);return 0;}//未获取起始位
    } 
    else if(Serial1.available()>4)//获取1号数据，角度，类型long
    {
      if(Serial1.read()==0xa5) 
      {         
        MX_receive[0]=Serial1.read();
        MX_receive[1]=Serial1.read();
        MX_receive[2]=Serial1.read();
        MX_receive[3]=Serial1.read();
        MX_receive[4]=Serial1.read();
        if(MX_receive[4]==MX_receive[0]^MX_receive[1]^MX_receive[2]^MX_receive[3])
        { 
          MX_motorAngleN=0;
          MX_motorAngleN=MX_receive[0];
          MX_motorAngleN=MX_motorAngleN<<8|MX_receive[1];
          MX_motorAngleN=MX_motorAngleN<<8|MX_receive[2];
          MX_motorAngleN=MX_motorAngleN<<8|MX_receive[3]; 
          while(Serial1.read()>= 0);
          return 1;//获取信息成功
        } 
        else {while(Serial1.read()>= 0);return 0;}//校验失败
      }
      else {while(Serial1.read()>= 0);return 0;}//未获取起始位
    } 
    else  {while(Serial1.read()>= 0);return 0;}//等待超时      
  }
  else
  {
    while(MX_motorData_wait>0)
    {
      MX_motorData_wait--;
      if(MX_motorData_function>1 && Serial3.available()>2)
        {MX_motorData_wait=0;}
      else if(Serial3.available()>4)
        {MX_motorData_wait=0;}
    }
    if(MX_motorData_function>1 && Serial3.available()>2)//获取其他数据，类型char
    {
      if(Serial3.read()==0xa5) 
      {         
        MX_receive[0]=Serial3.read();
        MX_receive[1]=Serial3.read();
        MX_receive[2]=Serial3.read();
        if(MX_receive[2]==MX_receive[0]^MX_receive[1])
        { 
          MX_motorDataN=0;
          MX_motorDataN=MX_receive[0];
          MX_motorDataN=MX_motorDataN<<8|MX_receive[1];
          while(Serial3.read()>= 0);
          return 1;//获取信息成功
        } 
        else  {while(Serial3.read()>= 0);return 0;}//校验失败
      }
      else {while(Serial3.read()>= 0);return 0;}//未获取起始位
    } 
    else if(Serial3.available()>4)//获取1号数据，角度，类型long
    {
      if(Serial3.read()==0xa5) 
      {         
        MX_receive[0]=Serial3.read();
        MX_receive[1]=Serial3.read();
        MX_receive[2]=Serial3.read();
        MX_receive[3]=Serial3.read();
        MX_receive[4]=Serial3.read();
        if(MX_receive[4]==MX_receive[0]^MX_receive[1]^MX_receive[2]^MX_receive[3])
        { 
          MX_motorAngleN=0;
          MX_motorAngleN=MX_receive[0];
          MX_motorAngleN=MX_motorAngleN<<8|MX_receive[1];
          MX_motorAngleN=MX_motorAngleN<<8|MX_receive[2];
          MX_motorAngleN=MX_motorAngleN<<8|MX_receive[3]; 
          while(Serial3.read()>= 0);
          return 1;//获取信息成功
        } 
        else {while(Serial3.read()>= 0);return 0;}//校验失败
      }
      else {while(Serial3.read()>= 0);return 0;}//未获取起始位
    } 
    else  {while(Serial3.read()>= 0);return 0;}//等待超时  
  } 
}
//清屏
void MX_screenCLS(uchar MX_screen_C)
{
	Serial2.print("CLS(");
	Serial2.print(MX_screen_C);
	Serial2.println(");");
	while(!digitalRead(MX_screenBusy));
	while(digitalRead(MX_screenBusy));
}
//画方块
void MX_screenBox(uchar MX_screen_function,uint MX_screen_X1,uint MX_screen_Y1,uint MX_screen_X2,uint MX_screen_Y2,uchar MX_screen_C)
{
  	switch (MX_screen_function)
  	{
		case 1:
		{Serial2.print("PL("); 	}break;
		case 2:
		{Serial2.print("BOX(");	}break;
		case 3:
		{Serial2.print("BOXF(");}break;	
	}
	Serial2.print(MX_screen_X1);Serial2.print(",");
	Serial2.print(MX_screen_Y1);Serial2.print(",");
	Serial2.print(MX_screen_X2);Serial2.print(",");
	Serial2.print(MX_screen_Y2);Serial2.print(",");
	Serial2.print(MX_screen_C);Serial2.println(");");
	while(!digitalRead(MX_screenBusy));
	while(digitalRead(MX_screenBusy));
}
void MX_screenCircle(uchar MX_screen_function,uint MX_screen_X1,uint MX_screen_Y1,uint MX_screen_r,uchar MX_screen_C)
{
  	switch (MX_screen_function)
  	{
		case 1:
		{Serial2.print("CIR("); 	}break;
		case 2:
		{Serial2.print("CIRF(");	}break;
	}
	Serial2.print(MX_screen_X1);Serial2.print(",");
	Serial2.print(MX_screen_Y1);Serial2.print(",");
	Serial2.print(MX_screen_r);Serial2.print(",");
	Serial2.print(MX_screen_C);Serial2.println(");");
	while(!digitalRead(MX_screenBusy));
	while(digitalRead(MX_screenBusy));
}
void MX_screenCircleBox(uchar MX_screen_function,uint MX_screen_X1,uint MX_screen_Y1,uint MX_screen_X2,uint MX_screen_Y2,uint MX_screen_r,uchar MX_screen_C)
{
  	switch (MX_screen_function)
  	{
		case 1:
		{Serial2.print("CBOX("); 	}break;
		case 2:
		{Serial2.print("CBOF(");	}break;
	}
	Serial2.print(MX_screen_X1);Serial2.print(",");
	Serial2.print(MX_screen_Y1);Serial2.print(",");
	Serial2.print(MX_screen_X2);Serial2.print(",");
	Serial2.print(MX_screen_Y2);Serial2.print(",");
	Serial2.print(MX_screen_r);Serial2.print(",");	
	Serial2.print(MX_screen_C);Serial2.println(");");
	while(!digitalRead(MX_screenBusy));
	while(digitalRead(MX_screenBusy));
}
void MX_screenWord(uchar MX_screen_function,char *MX_screenWord,uint MX_screen_X1,uint MX_screen_Y1,uchar MX_screen_C,uint MX_screen_X2)
{
	switch (MX_screen_function)
  	{
		case 16:
		{Serial2.print("PS16"); 	}break;
		case 24:
		{Serial2.print("PS24(");	}break;
		case 32:
		{Serial2.print("PS32(");	}break;
		case 48:
		{Serial2.print("PS48(");	}break;
		case 64:
		{Serial2.print("PS64(");	}break;
	}
	Serial2.print("0,");
	Serial2.print(MX_screen_X1);Serial2.print(",");
	Serial2.print(MX_screen_Y1);Serial2.print(",'");
	for(*MX_screenWord;*MX_screenWord!=0;*MX_screenWord++)
	{	Serial2.print(*MX_screenWord);	}
	Serial2.print("',");
	Serial2.print(MX_screen_C);Serial2.print(",");	
	Serial2.print(MX_screen_X2);Serial2.println(");");
	while(!digitalRead(MX_screenBusy));
	while(digitalRead(MX_screenBusy));
}
void MX_screenDecimalNum(uchar MX_screen_function,double MX_screenDecimalNum_n,uint MX_screen_X1,uint MX_screen_Y1,uchar MX_screen_C,uint MX_screen_X2)
{
	switch (MX_screen_function)
  	{
		case 16:
		{Serial2.print("PS16"); MX_screen_function=8;	}break;
		case 24:
		{Serial2.print("PS24(");MX_screen_function=12;	}break;
		case 32:
		{Serial2.print("PS32(");MX_screen_function=16;	}break;
		case 48:
		{Serial2.print("PS48(");MX_screen_function=24;	}break;
		case 64:
		{Serial2.print("PS64(");MX_screen_function=32;	}break;
	}
	Serial2.print("0,");
	
	uchar MX_screen_char2=0;//所显示的字符的长度
	while(MX_screenDecimalNum_n/pow(10,MX_screen_char2)>10)
	{MX_screen_char2++;}MX_screen_char2++;
	
	Serial2.print(MX_screen_X1);Serial2.print(",");
	Serial2.print(MX_screen_Y1);Serial2.print(",'");

	MX_screen_char2=MX_screen_X2-MX_screen_char2-2;
	while(MX_screen_char2--)
	{Serial2.print(" ");}
	
	Serial2.print(MX_screenDecimalNum_n);Serial2.print("',");
	Serial2.print(MX_screen_C);Serial2.print(",");	
	Serial2.print(MX_screen_X2);Serial2.println(");");
	while(!digitalRead(MX_screenBusy));
	while(digitalRead(MX_screenBusy));
}
void MX_screenWholeNum(uchar MX_screen_function,long MX_screenWholeNum_n,uint MX_screen_X1,uint MX_screen_Y1,uchar MX_screen_C,uint MX_screen_X2)
{
	switch (MX_screen_function)
  	{
		case 16:
		{Serial2.print("PS16"); }break;
		case 24:
		{Serial2.print("PS24(");}break;
		case 32:
		{Serial2.print("PS32(");}break;
		case 48:
		{Serial2.print("PS48(");}break;
		case 64:
		{Serial2.print("PS64(");}break;
	}
	Serial2.print("0,");
	
	MX_screen_char2=0;//所显示的字符的长度
  if(MX_screenWholeNum_n>=0)//判断如果输入负数，则变成正数，再计算数位长度
  {
    while(MX_screenWholeNum_n/pow(10,MX_screen_char2)>9)
	  {MX_screen_char2++;}
	}
	else
	{    
	  while(MX_screenWholeNum_n*-1/pow(10,MX_screen_char2)>9)
   {MX_screen_char2++;}
   }
   MX_screen_char2++;
   
	Serial2.print(MX_screen_X1);Serial2.print(",");
	Serial2.print(MX_screen_Y1);Serial2.print(",'");
  //补空格
	MX_screen_char2=MX_screen_X2-MX_screen_char2;
  while(MX_screen_char2--)
	{Serial2.print(" ");}
  
	Serial2.print(MX_screenWholeNum_n);Serial2.print(" ',");
	Serial2.print(MX_screen_C);Serial2.print(",");	
	Serial2.print(MX_screen_X2);Serial2.println(");");
	while(!digitalRead(MX_screenBusy));
	while(digitalRead(MX_screenBusy));
}

void MX_screenPassages(uchar MX_screen_function,char *MX_screenWord2,uint MX_screen_X1,uint MX_screen_Y1,uchar MX_screen_C,uint MX_screen_X2,uint MX_screen_Y2)
{
	switch (MX_screen_function)
  	{
		case 12:
		{Serial2.print("BS12("); 	}break;
		case 16:
		{Serial2.print("BS16(");	}break;
		case 24:
		{Serial2.print("BS24(");	}break;
	}
	Serial2.print(MX_screen_X1);Serial2.print(",");
	Serial2.print(MX_screen_Y1);Serial2.print(",");
	Serial2.print(MX_screen_X2);Serial2.print(",");
	Serial2.print(MX_screen_Y2);Serial2.print(",'");
	for(*MX_screenWord2;*MX_screenWord2!=0;*MX_screenWord2++)
	{	Serial2.print(*MX_screenWord2);	}
	Serial2.print("',");
	Serial2.print(MX_screen_C);Serial2.println(");");	

	while(!digitalRead(MX_screenBusy));
	while(digitalRead(MX_screenBusy));
}
void MX_screenBackColor(uchar MX_screen_C)
{
	Serial2.print("SBC(");
	Serial2.print(MX_screen_C);Serial2.println(");");
	while(!digitalRead(MX_screenBusy));
	while(digitalRead(MX_screenBusy));
}
void MX_screenSetColor(uchar MX_screen_char1,uchar MX_screen_function,uchar MX_screen_C,uchar MX_screen_char2)
{
	uint MX_screenSetColor_c;
	MX_screenSetColor_c=((MX_screen_function << 8) & 0xf800)+((MX_screen_C << 3) & 0x07e0)+(MX_screen_char2 >> 3);
	Serial2.print("SCC(");
	Serial2.print(MX_screen_char1);Serial2.print(",");	
	Serial2.print(MX_screenSetColor_c);Serial2.println(");");
	while(!digitalRead(MX_screenBusy));
	while(digitalRead(MX_screenBusy));	
}
uchar MX_batteryLevel()
{
	uint MX_batteryLevel_n = analogRead(MX_battery);
	if(MX_batteryLevel_n>881)
		return 11;
	else if(MX_batteryLevel_n>850)
		return 10;
	else if(MX_batteryLevel_n>836)
		return 9;
	else if(MX_batteryLevel_n>819)
		return 8;
	else if(MX_batteryLevel_n>805)
		return 7;
	else if(MX_batteryLevel_n>793)
		return 6;
	else if(MX_batteryLevel_n>780)
		return 5;
	else if(MX_batteryLevel_n>776)
		return 4;
	else if(MX_batteryLevel_n>772)
		return 3;
	else if(MX_batteryLevel_n>764)
		return 2;
	else if(MX_batteryLevel_n>737)
		return 1;
	else
		return 0;	
}
void MX_screenGraph(uint MX_screen_X1,uint MX_screen_Y1,uint MX_screen_X2,uint MX_screen_Y2,uchar MX_screen_char1,uchar MX_screen_char2)
{
	Serial2.print("DQX(");
	Serial2.print(MX_screen_X1);	Serial2.print(",");	
	Serial2.print(MX_screen_Y1);	Serial2.print(",");	
	Serial2.print(MX_screen_char1);	Serial2.print(",");	
	Serial2.print(MX_screen_Y2);	Serial2.print(",");	
	Serial2.print(MX_screen_X2);	Serial2.print(",");	
	Serial2.print(MX_screen_char2);	Serial2.println(");");
	while(!digitalRead(MX_screenBusy));
	while(digitalRead(MX_screenBusy));	
}
void MX_screenGraphReflash()
{
	Serial2.println("RQX();");
	while(!digitalRead(MX_screenBusy));
	while(digitalRead(MX_screenBusy));	
}
void MX_screenGraphData(uchar MX_screen_char1)
{
	Serial2.print("Q");
	Serial2.print(MX_screen_char1);Serial2.println(";");
	while(!digitalRead(MX_screenBusy));
	while(digitalRead(MX_screenBusy));	
}
void MX_screenGraphDR(uchar MX_screen_char1)
{
	Serial2.print("S");
	Serial2.print(MX_screen_char1);Serial2.println(";");
	while(!digitalRead(MX_screenBusy));
	while(digitalRead(MX_screenBusy));	
}
void MX_screenPicture(uint MX_screen_X1,uint MX_screen_Y1,uint MX_screen_X2)
{
	Serial2.print("PIC(");
	Serial2.print(MX_screen_X1);	Serial2.print(",");	
	Serial2.print(MX_screen_Y1);	Serial2.print(",");	
	Serial2.print(MX_screen_X2);	Serial2.println(");");
	while(!digitalRead(MX_screenBusy));
	while(digitalRead(MX_screenBusy));		
}
void MX_screenBackPicture(uint MX_screen_X1,uint MX_screen_Y1,uchar MX_screen_char1,uint MX_screen_X2)
{
	Serial2.print("BPIC(");
	Serial2.print(MX_screen_char1);	Serial2.print(",");	
	Serial2.print(MX_screen_X1);	Serial2.print(",");	
	Serial2.print(MX_screen_Y1);	Serial2.print(",");	
	Serial2.print(MX_screen_X2);	Serial2.println(");");
	while(!digitalRead(MX_screenBusy));
	while(digitalRead(MX_screenBusy));			
}
void MX_screenBackIco(uint MX_screen_X1,uint MX_screen_Y1,uint MX_screen_X2,uchar MX_screen_char1,uchar MX_screen_char2,uint MX_screen_Y2)
{
	Serial2.print("ICON(");
	Serial2.print(MX_screen_X1);	Serial2.print(",");	
	Serial2.print(MX_screen_Y1);	Serial2.print(",");
	Serial2.print(MX_screen_X2);	Serial2.print(",");
	Serial2.print(MX_screen_char1);	Serial2.print(",");
	Serial2.print(MX_screen_char2);	Serial2.print(",");
	Serial2.print(MX_screen_Y2);	Serial2.println(");");
	while(!digitalRead(MX_screenBusy));
	while(digitalRead(MX_screenBusy));			
}
void MX_screenIcon(uint MX_screen_X1,uint MX_screen_Y1,uint MX_screen_X2)
{
	MX_screen_char1=MX_screen_X2/50+1;
 	MX_screen_X2=MX_screen_X2%50;

	Serial2.print("ICON(");
	Serial2.print(MX_screen_X1);	Serial2.print(",");	
	Serial2.print(MX_screen_Y1);	Serial2.print(",");
	Serial2.print(MX_screen_char1);	Serial2.print(",5,10,");
	Serial2.print(MX_screen_X2);	Serial2.println(");");
	while(!digitalRead(MX_screenBusy));
	while(digitalRead(MX_screenBusy));	
}
void MX_screenClock(uchar MX_screen_char1,uint MX_screen_X1,uint MX_screen_Y1,uchar MX_screen_C,uchar MX_screen_char2)
{

	Serial2.print("SHTM(");
	Serial2.print(MX_screen_char1);	Serial2.print(",");
	Serial2.print(MX_screen_X1);	Serial2.print(",");	
	Serial2.print(MX_screen_Y1);	Serial2.print(",");
	Serial2.print(MX_screen_C);		Serial2.print(",");	
	Serial2.print(MX_screen_char2);	Serial2.println(");");
	while(!digitalRead(MX_screenBusy));
	while(digitalRead(MX_screenBusy));	
}
void MX_screenClockSet(uchar MX_screen_char1,uchar MX_screen_char2,uchar MX_screen_C)
{
	Serial2.print("STIM(");
	Serial2.print(MX_screen_char1);	Serial2.print(",");
	Serial2.print(MX_screen_char2);	Serial2.print(",");
	Serial2.print(MX_screen_C);		Serial2.println(");");
	while(!digitalRead(MX_screenBusy));
	while(digitalRead(MX_screenBusy));		
}
void MX_screenAutoClockSet()
{
	if(millis()/3600000<24)
		MX_screenClockSet(millis()/3600000,millis()%3600000/60000,millis()%60000/1000);
	else
		MX_screenClockSet(millis()%86400000/3600000,millis()%3600000/60000,millis()%60000/1000);
}
void MX_screenBattery()
{
if(millis()>MX_screenBatteryV_n)
{ 
  if(MX_screenBatteryV_n<500)
  {Serial2.print("CBOF(766,21,831,61,7,34);");}
  MX_screenBatteryV_n+=300;
	Serial2.print("ICON(768,23,2,5,1,");
	if(MX_batteryLevel()>8)
	   Serial2.print("4");
	else if(MX_batteryLevel()>5)
	   Serial2.print("3");
	else if(MX_batteryLevel()>3)
	   Serial2.print("2");	  
	else if(MX_batteryLevel()>1)
	   Serial2.print("1");	  
	else
	   Serial2.print("0");
	Serial2.println(");");	 
	while(!digitalRead(MX_screenBusy));
	while(digitalRead(MX_screenBusy));	
}
}
void MX_screenBatteryV()
{
  if(millis()>MX_screenBatteryV_n)
  { 
    MX_screenAutoClockSet();
    MX_screenBatteryV_n+=300;
    Serial2.print("SBC(34);PS32(1,678,25,'");  
    Serial2.print((float)analogRead(MX_battery)*15/1024);  
    Serial2.print("',36,0);ICON(768,23,2,5,1,");   
  if(MX_batteryLevel()>8)
     Serial2.print("4");
  else if(MX_batteryLevel()>5)
     Serial2.print("3");
  else if(MX_batteryLevel()>3)
     Serial2.print("2");    
  else if(MX_batteryLevel()>1)
     Serial2.print("1");    
  else
     Serial2.print("0");
  Serial2.println(");");   
  while(!digitalRead(MX_screenBusy));
  while(digitalRead(MX_screenBusy));  
    
  }
}
void MX_screenCutPicture(uint MX_screen_X1,uint MX_screen_Y1,uint MX_screen_Pn,uint MX_screen_X2,uint MX_screen_Y2,uint MX_screen_r,uint MX_screen_Color)
{
	Serial2.print("CPIC(");
	Serial2.print(MX_screen_X1);	Serial2.print(",");	
	Serial2.print(MX_screen_Y1);	Serial2.print(",");
	Serial2.print(MX_screen_Pn);	Serial2.print(",");
	Serial2.print(MX_screen_X2);	Serial2.print(",");
	Serial2.print(MX_screen_Y2);	Serial2.print(",");
	Serial2.print(MX_screen_r);		Serial2.print(",");
	Serial2.print(MX_screen_Color);	Serial2.println(");");
	while(!digitalRead(MX_screenBusy));
	while(digitalRead(MX_screenBusy));			
}
void MX_screenTerm(void)
{
  Serial2.println("TERM");
  while(!digitalRead(MX_screenBusy));
  while(digitalRead(MX_screenBusy));      
}
void MX_screenSPG(uchar MX_screen_char1)
{
	Serial2.print("SPG(");
	Serial2.print(MX_screen_char1);	Serial2.println(");");	
	while(!digitalRead(MX_screenBusy));
	while(digitalRead(MX_screenBusy));		
}
void MX_screenDirection(uchar MX_screen_char1)
{
	Serial2.print("DR");
	Serial2.print(MX_screen_char1);	Serial2.println(");");	
	while(!digitalRead(MX_screenBusy));
	while(digitalRead(MX_screenBusy));		
}

void MX_screenMoveTo(uint MX_screen_X1,uint MX_screen_Y1)
{
	Serial2.print("SXY(");
	Serial2.print(MX_screen_X1);	Serial2.print(",");	
	Serial2.print(MX_screen_Y1);	Serial2.println(");");
	while(!digitalRead(MX_screenBusy));
	while(digitalRead(MX_screenBusy));	

}
void MX_screenMove()
{
	Serial2.println("SXY(0,0);");
	while(!digitalRead(MX_screenBusy));
	while(digitalRead(MX_screenBusy));		

}
void MX_screenLum(uchar MX_screen_char1)
{
	Serial2.print("SEBL(");
	if(MX_screen_char1==0)
		Serial2.print("1");	
	else
		Serial2.print(MX_screen_char1);
	Serial2.println(");");
	while(!digitalRead(MX_screenBusy));
	while(digitalRead(MX_screenBusy));		
}
void MX_screenCalibration()
{
	Serial2.println("TPST(854,480);");
	while(!digitalRead(MX_screenBusy));
	while(digitalRead(MX_screenBusy));	
}
void MX_screenTouchMode(uchar MX_screen_char1)
{
	Serial2.print("TPN(");
	Serial2.print(MX_screen_char1);Serial2.println(");");
	while(!digitalRead(MX_screenBusy));
	while(digitalRead(MX_screenBusy));	
}
bool MX_screenGetXY()
{
  if(Serial2.available()>11)
    {
      if(Serial2.find("[TP:"))
      {
         MX_screenTouchX=Serial2.parseInt();
         if(Serial2.find(","))
         {
          MX_screenTouchY=Serial2.parseInt();
            if(Serial2.find("]"))
            {
              while(Serial.read()>= 0);
              return 1;
            }
         }
      }
  }
  while(Serial.read()>= 0);
  return 0;
}
void MX_screenDraw(uchar MX_screen_char1)
{
	Serial2.print("TPOW(");
	Serial2.print(MX_screen_char1);Serial2.println(");");
	while(!digitalRead(MX_screenBusy));
	while(digitalRead(MX_screenBusy));		
}
void MX_screenButton(uchar MX_screen_C,uint MX_screen_X1,uint MX_screen_Y1,uint MX_screen_X2,uint MX_screen_Y2,uchar MX_screen_char1)
{
	Serial2.print("BTN(");
	Serial2.print(MX_screen_C);		Serial2.print(",");	
	Serial2.print(MX_screen_X1);	Serial2.print(",");	
	Serial2.print(MX_screen_Y1);	Serial2.print(",");
	Serial2.print(MX_screen_X2);	Serial2.print(",");
	Serial2.print(MX_screen_Y2);	Serial2.print(",");
	Serial2.print(MX_screen_char1);	Serial2.println(",0);");
	while(!digitalRead(MX_screenBusy));
	while(digitalRead(MX_screenBusy));		
}
bool MX_screenGetButton()
{
    while(Serial2.read()!=0x5b && Serial2.available()>0);
  delay(1);
  if(Serial2.available()>4)
  {
     if(Serial2.find("BN:"))
     {
       MX_screenButtonN=Serial2.parseInt();  
       if(Serial2.find("]"))
       {
		      if(MX_screenButtonN!=0)
		      {
		  	      if(MX_screenButtonBuzzer==1)
		  	     {
		  		      digitalWrite(MX_buzzerIO,0);
		  		      delay(1);digitalWrite(MX_buzzerIO,1);
			        }
             delay(10);
             while(Serial.read()>= 0);
			       return 1;
		      }
       }
     }
  }
  while(Serial.read()>= 0);
  return 0;
}
bool MX_screenGetOBJ2()
{
  Serial2.print("GVAL(2);");Serial2.print(MX_screen_char1);Serial2.print(");");
  Serial2.println();while(!digitalRead(MX_screenBusy));while(digitalRead(MX_screenBusy));
  while(Serial2.read()!=0x28 && Serial2.available()>0);
  delay(1);
  if(Serial2.available()>4)
  {
    if(Serial2.find("O2:"))
    {
      MX_screenButtonN=Serial2.parseInt();
      if(Serial2.find(")"))
      {return 1;}
    }
  }
  return 0;
}
bool MX_screenGetButtonPress()
{       
    while(Serial2.read()!=0x5b && Serial2.available()>0);
  delay(1);
  if(Serial2.available()>4)
  {
     if(Serial2.find("BS:"))
     {
       MX_screenButtonN=Serial2.parseInt();  
       if(Serial2.find("]"))
       {
         if(MX_screenButtonN!=0)
          {
              if(MX_screenButtonBuzzer==1)
             {
                digitalWrite(MX_buzzerIO,0);
                delay(1);digitalWrite(MX_buzzerIO,1);
              }
             delay(10);
             while(Serial.read()>= 0);
             return 1;
          }
       }
     }
  }
  while(Serial.read()>= 0);
  return 0;
}
void MX_screenNumKeyboard(uchar MX_screen_C)
{
  Serial2.print("BOX(0,0,185,232,");Serial2.print(MX_screen_C);Serial2.print(");PL(186,0,186,232,");Serial2.print(MX_screen_C);
  Serial2.print(");PL(0,233,186,233,");Serial2.print(MX_screen_C);Serial2.print(");PL(5,47,179,47,");Serial2.print(MX_screen_C);
  Serial2.print(");TSIN(32,15,11,179,9,1,");Serial2.print(MX_screen_C);Serial2.print(");");

  Serial2.print("DS32(17,57,'7',");Serial2.print(MX_screen_C);Serial2.print(");DS32(64,57,'8',");Serial2.print(MX_screen_C);
  Serial2.print(");DS32(109,57,'9',");Serial2.print(MX_screen_C);Serial2.print(");DS16(145,64,'\xC9\xBE\xB3\xFD',");Serial2.print(MX_screen_C);Serial2.print(");");
  Serial2.print("BTN(28,5,52,45,92,0,55);BTN(29,50,52,90,92,0,56);BTN(30,95,52,135,92,0,57);BTN(31,140,52,180,92,0,1);");
  Serial2.print("BOX(5,52,45,92,");Serial2.print(MX_screen_C);Serial2.print(");BOX(50,52,90,92,");Serial2.print(MX_screen_C);Serial2.print(");BOX(95,52,135,92,");Serial2.print(MX_screen_C);Serial2.print(");BOX(140,52,180,92,");Serial2.print(MX_screen_C);Serial2.print(");");

  Serial2.print("DS32(16,103,'4',");Serial2.print(MX_screen_C);Serial2.print(");DS32(62,103,'5',");Serial2.print(MX_screen_C);
  Serial2.print(");DS32(108,103,'6',");Serial2.print(MX_screen_C);Serial2.print(");DS16(145,109,'\xC7\xE5\xBF\xD5',");Serial2.print(MX_screen_C);Serial2.print(");");
  Serial2.print("BTN(24,5,97,45,137,0,52);BTN(25,50,97,90,137,0,53);BTN(26,95,97,135,137,0,54);BTN(27,140,97,180,137,0,2);");
  Serial2.print("BOX(5,97,45,137,");Serial2.print(MX_screen_C);Serial2.print(");BOX(50,97,90,137,");Serial2.print(MX_screen_C);Serial2.print(");BOX(95,97,135,137,");Serial2.print(MX_screen_C);Serial2.print(");BOX(140,97,180,137,");Serial2.print(MX_screen_C);Serial2.println(");");

  while(!digitalRead(MX_screenBusy));
  while(digitalRead(MX_screenBusy));  

  Serial2.print("DS32(16,148,'1',");Serial2.print(MX_screen_C);Serial2.print(");DS32(62,148,'2',");Serial2.print(MX_screen_C);
  Serial2.print(");DS32(108,148,'3',");Serial2.print(MX_screen_C);Serial2.print(");DS16(145,154,'\xC8\xA1\xCF\xFB',");Serial2.print(MX_screen_C);Serial2.print(");");
  Serial2.print("BTN(20,5,142,45,182,0,49);BTN(21,50,142,90,182,0,50);BTN(22,95,142,135,182,0,51);BTN(23,140,142,180,182,0,13);");
  Serial2.print("BOX(5,142,45,182,");Serial2.print(MX_screen_C);Serial2.print(");BOX(50,142,90,182,");Serial2.print(MX_screen_C);Serial2.print(");BOX(95,142,135,182,");Serial2.print(MX_screen_C);Serial2.print(");BOX(140,142,180,182,");Serial2.print(MX_screen_C);Serial2.print(");");

  Serial2.print("DS32(39,193,'0',");Serial2.print(MX_screen_C);Serial2.print(");");
  Serial2.print("DS16(145,199,'\xC8\xB7\xC8\xCF',");Serial2.print(MX_screen_C);Serial2.print(");");
  Serial2.print("BTN(17,5,187,90,227,0,48);BTN(19,140,187,180,227,0,13);");  
  Serial2.print("BOX(5,187,90,227,");Serial2.print(MX_screen_C);Serial2.print(");BOX(140,187,180,227,");Serial2.print(MX_screen_C);Serial2.println(");"); 
	while(!digitalRead(MX_screenBusy));
	while(digitalRead(MX_screenBusy));	

}

bool MX_screenInputWholeNum(uint MX_screen_X1,uint MX_screen_Y1,uchar MX_screen_char1,uchar MX_screen_char2)
{
  MX_screenTouchMode(GetButton);  
  Serial2.print("SXY(");Serial2.print(MX_screen_X1);Serial2.print(",");Serial2.print(MX_screen_Y1);Serial2.print(");");
  MX_screenNumKeyboard(MX_screen_char1);
  Serial2.print("BTN(18,95,187,135,227,0,0);");
  Serial2.print("BOX(95,187,135,227,");Serial2.print(MX_screen_char1);Serial2.print(");");
  Serial2.println("SXY(0,0);");
  while(!digitalRead(MX_screenBusy));
  while(digitalRead(MX_screenBusy));    
  
  while(!Serial2.find("{"));
  MX_screenInputWholeNumber=Serial2.parseInt();

  Serial2.print("BOXF(");Serial2.print(MX_screen_X1-1);Serial2.print(",");Serial2.print(MX_screen_Y1-1);Serial2.print(",");
  Serial2.print(MX_screen_X1+187);Serial2.print(",");Serial2.print(MX_screen_Y1+234);Serial2.print(",");Serial2.print(MX_screen_char2);Serial2.print(");"); 
  Serial2.print("BTN(17,0,0,1,0,0,0);BTN(18,0,0,1,0,0,0);BTN(19,0,0,1,0,0,0);BTN(20,0,0,1,0,0,0);BTN(21,0,0,1,0,0,0);BTN(22,0,0,1,0,0,0);BTN(23,0,0,1,0,0,0);BTN(24,0,0,1,0,0,0);");
  Serial2.println("BTN(25,0,0,1,0,0,0);BTN(26,0,0,1,0,0,0);BTN(27,0,0,1,0,0,0);BTN(28,0,0,1,0,0,0);BTN(29,0,0,1,0,0,0);BTN(30,0,0,1,0,0,0);BTN(31,0,0,1,0,0,0);");
  while(!digitalRead(MX_screenBusy));
  while(digitalRead(MX_screenBusy));  

  if(Serial2.find("}[BN:"))
  {
    if(Serial2.parseInt()==19)
    {
    	while(Serial.read()>= 0);
      	return 1;
     }
  }
  else 
  {
	while(Serial.read()>= 0);
	return 0;
  }
  
}
bool MX_screenInputDecimalNum(uint MX_screen_X1,uint MX_screen_Y1,uchar MX_screen_char1,uchar MX_screen_char2)
{
  MX_screenTouchMode(GetButton);  
  Serial2.print("SXY(");Serial2.print(MX_screen_X1);Serial2.print(",");Serial2.print(MX_screen_Y1);Serial2.print(");");
  MX_screenNumKeyboard(MX_screen_char1);
  Serial2.print("BTN(18,95,187,135,227,0,46);");Serial2.print("BOX(95,187,135,227,");Serial2.print(MX_screen_char1);Serial2.print(");");
  Serial2.print("DS32(111,193,'.',");Serial2.print(MX_screen_char1);Serial2.print(");");
  Serial2.println("SXY(0,0);");
  while(!digitalRead(MX_screenBusy));
  while(digitalRead(MX_screenBusy));    
  
  while(!Serial2.find("{"));
  MX_screenInputDecimalNumber=Serial2.parseFloat();

  Serial2.print("BOXF(");Serial2.print(MX_screen_X1-1);Serial2.print(",");Serial2.print(MX_screen_Y1-1);Serial2.print(",");
  Serial2.print(MX_screen_X1+187);Serial2.print(",");Serial2.print(MX_screen_Y1+234);Serial2.print(",");Serial2.print(MX_screen_char2);Serial2.print(");"); 
  Serial2.print("BTN(17,0,0,1,0,0,0);BTN(18,0,0,1,0,0,0);BTN(19,0,0,1,0,0,0);BTN(20,0,0,1,0,0,0);BTN(21,0,0,1,0,0,0);BTN(22,0,0,1,0,0,0);BTN(23,0,0,1,0,0,0);BTN(24,0,0,1,0,0,0);");
  Serial2.println("BTN(25,0,0,1,0,0,0);BTN(26,0,0,1,0,0,0);BTN(27,0,0,1,0,0,0);BTN(28,0,0,1,0,0,0);BTN(29,0,0,1,0,0,0);BTN(30,0,0,1,0,0,0);BTN(31,0,0,1,0,0,0);");
  while(!digitalRead(MX_screenBusy));
  while(digitalRead(MX_screenBusy));  
  
  if(Serial2.find("}[BN:"))
  {
    if(Serial2.parseInt()==19)
    {
      while(Serial.read()>= 0);
      return 1;
     }
  }
  else 
  {
	while(Serial.read()>= 0);
	return 0;
  }
}
void MX_screenDeleteButtons()
{
  for(uchar MX_screen_char1=1;MX_screen_char1<17;MX_screen_char1++)
  {Serial2.print("BTN(");Serial2.print(MX_screen_char1);Serial2.print(",0,0,1,0,0,0);");}
  Serial2.println();    
}

void MX_screenMenuHome()
{
 MX_screenCLS(63);  
 MX_screenBattery();MX_screenBatteryV();
 //机器人-我的程序-1
 MX_screenIcon(48,50,275);
 MX_screenButton(1,48,50,148,150,0);
 MX_screenWord(Size16,"\xCE\xD2\xB5\xC4\xB3\xCC\xD0\xF2",66,153,33,0);
 //工具篮子-示例程序-2
 MX_screenIcon(212,50,218);
 MX_screenButton(2,212,50,312,150,0);
 MX_screenWord(Size16,"\xCA\xBE\xC0\xFD\xB3\xCC\xD0\xF2",230,153,33,0);
 //USB口-查看端口-3
 MX_screenIcon(376,50,89);
 MX_screenWord(Size16,"\xB2\xE9\xBF\xB4\xB6\xCB\xBF\xDA",396,153,33,0);
 MX_screenButton(3,376,50,476,150,0);
 //调音器-设置-4
 MX_screenIcon(540,50,311);
 MX_screenButton(4,540,50,640,150,0);
 MX_screenWord(Size16,"\xC9\xE8\xD6\xC3",573,153,33,0);
 //书-编程指南-5
 MX_screenIcon(704,50,446);
 MX_screenButton(5,704,50,804,150,0);
 MX_screenWord(Size16,"\xB1\xE0\xB3\xCC\xD6\xB8\xC4\xCF",720,153,33,0);
 //ABC-编程素材-6
 MX_screenIcon(48,190,447);
 MX_screenButton(6,48,190,148,290,0); 
 MX_screenWord(Size16,"\xCB\xD8\xB2\xC4\xBF\xE2",74,293,33,0);
 //身份卡-关于-7
 MX_screenIcon(213,190,390);
 MX_screenButton(7,213,190,313,290,0); 
 MX_screenWord(Size16,"\xB9\xD8\xD3\xDA",244,293,33,0);

 //MX_screenIcon(48,330,153);MX_screenWord(Size16,"test",66,433,33,0);//指纹-预留测试 

 MX_screenCircle(CIRF,426,464,3,0);
  
 MX_screenWord(Size24,"MX900",15,10,33,0);
 MX_screenClock(Size24,394,10,33,26); 
 MX_screenBattery();
 MX_screenBatteryV();    
}
void MX_screenMenu_about()
{    MX_screenCLS(63);MX_screenBattery();MX_screenBatteryV();
  MX_screenWord(Size24,"\xA3\xBC\xB7\xB5\xBB\xD8",15,13,0,0);//返回
  MX_screenWord(Size48,"\xB9\xD8\xD3\xDA",380,0,0,0);//关于
  MX_screenCircleBox(CBOX,8,6,100,40,5,0);MX_screenCircleBox(CBOX,8,6,101,41,5,0);
  MX_screenButton(1,8,5,101,41,0);
  Serial2.println("PS48(0,200,100,'MX900 \xBB\xFA\xC6\xF7\xC8\xCB\xBF\xD8\xD6\xC6\xC6\xF7',0);PS24(0,350,170,'Beta1-20180310',0);PS32(0,300,210,'E-mail:*****@semia.com',0);PIC(320,260,13);");  
  while(!digitalRead(MX_screenBusy));
  while(digitalRead(MX_screenBusy));  
  while(MX_screenGetButton()==0)
  {MX_screenBattery();MX_screenBatteryV();}
}
void MX_screenMenu_library()
{
  MX_screenCLS(63);MX_screenBattery();MX_screenBatteryV();
  MX_screenWord(Size24,"\xA3\xBC\xB7\xB5\xBB\xD8",15,13,0,0);//返回-1
  MX_screenWord(Size48,"\xCB\xD8\xB2\xC4\xBF\xE2",360,0,0,0);//素材库
  MX_screenCircleBox(CBOX,8,6,100,40,5,0);MX_screenCircleBox(CBOX,8,6,101,41,5,0);
  MX_screenButton(1,8,5,101,41,0); 
  MX_screenWord(Size24,"\xC9\xCF\xD2\xBB\xD2\xB3",20,439,0,0);//上一页-2
  MX_screenCircleBox(CBOX,10,430,100,470,5,0);
  MX_screenButton(2,10,430,100,470,0); 
  MX_screenWord(Size24,"\xCF\xC2\xD2\xBB\xD2\xB3",764,439,0,0);//下一页-3
  MX_screenCircleBox(CBOX,754,430,844,470,5,0);  
  MX_screenButton(3,754,430,844,470,0); 
  uchar MX_screenMenu_library_x,MX_screenMenu_library_y;
  uint MX_screenMenu_library_n=0;
  MX_screenMenuLoop2=1;MX_screenMenuNum=1;
  while(MX_screenMenuLoop2)
  {
    if(MX_screenMenuNum==1)
    { MX_screenMenu_library_n=0;
      MX_screenBox(BOXF,0,60,854,415,26);//清除部分区域
      MX_screenBox(BOXF,101,430,750,470,26);//清除部分区域
      MX_screenWord(Size24,"\xD1\xD5\xC9\xAB\xBA\xC5    ",140,13,0,0);//颜色号
      MX_screenWord(Size16,"(30~63\xBF\xC9\xD7\xD4\xB6\xA8\xD2\xE5)",213,21,0,0);//颜色号     
      for(MX_screenMenu_library_y=0;MX_screenMenu_library_y<4;MX_screenMenu_library_y++)
      {
        for(MX_screenMenu_library_x=0;MX_screenMenu_library_x<16;MX_screenMenu_library_x++)
        {
          MX_screenCircleBox(CBOXF,MX_screenMenu_library_x*50+27,MX_screenMenu_library_y*80+90,MX_screenMenu_library_x*50+67,MX_screenMenu_library_y*80+130,5,MX_screenMenu_library_n);
          MX_screenCircleBox(CBOX,MX_screenMenu_library_x*50+27,MX_screenMenu_library_y*80+90,MX_screenMenu_library_x*50+67,MX_screenMenu_library_y*80+130,5,0);
          MX_screenWholeNum(Size16,MX_screenMenu_library_n,MX_screenMenu_library_x*50+38,MX_screenMenu_library_y*80+139,0,2);
          MX_screenMenu_library_n++;
        }
      }
      while(MX_screenGetButton()==0)
      {MX_screenBattery();MX_screenBatteryV();} 
      if(MX_screenButtonN==1)
        {MX_screenMenuLoop2=0;}
      else if(MX_screenButtonN==3)
        {MX_screenMenuNum++;}
    }
    else
    { MX_screenBox(BOXF,0,60,854,415,26);
      MX_screenWord(Size24,"\xCF\xB5\xCD\xB3\xCD\xBC\xB1\xEA         ",140,13,0,0);//系统图标
      MX_screenMenu_library_n=(MX_screenMenuNum-2)*24;
      for(MX_screenMenu_library_y=0;MX_screenMenu_library_y<3;MX_screenMenu_library_y++)
      {
        for(MX_screenMenu_library_x=0;MX_screenMenu_library_x<8;MX_screenMenu_library_x++)
        { 
          if( MX_screenMenu_library_n<500)
          {
            MX_screenIcon(MX_screenMenu_library_x*100+27,MX_screenMenu_library_y*120+60,MX_screenMenu_library_n);
            MX_screenWholeNum(Size16,MX_screenMenu_library_n,MX_screenMenu_library_x*100+67,MX_screenMenu_library_y*120+160,0,3);
            MX_screenMenu_library_n++;          
          }
        }
      }
      for(MX_screenMenu_library_n=0;MX_screenMenu_library_n<21;MX_screenMenu_library_n++)
      {
        if(MX_screenMenuNum-2 == MX_screenMenu_library_n)
        {MX_screenCircle(CIRF,MX_screenMenu_library_n*29+133,450,3,0);}
        else
        MX_screenCircle(CIRF,MX_screenMenu_library_n*29+133,450,3,27);
      }
      while(MX_screenGetButton()==0)
      {MX_screenBattery();MX_screenBatteryV();} 
      if(MX_screenButtonN==1)
        {MX_screenMenuLoop2=0;}
      else if(MX_screenButtonN==2)
        {MX_screenMenuNum--;}   
      else if(MX_screenButtonN==3)
        {MX_screenMenuNum++;if(MX_screenMenuNum>22)MX_screenMenuNum=22;}      
    }
  }
}

///////////////////////////端口电机数据查看
void MX_menuPortView_motor(uchar MX_screen_char1)
{
  const static char MX_ScreenMessage_menuPortView_motor1[] PROGMEM  = {"SBC(0);CBOF(264,163,739,392,5,0);CBOX(264,163,739,392,5,35);SBC(0);PS24(1,279,178,'\xB8\xDF\xCB\xD9\xB5\xE7\xBB\xFA',16,0);PS24(1,279,217,'\xBD\xC7\xB6\xC8\xA3\xBA          \xB6\xC8',36,0);PS24(1,279,256,'\xCB\xD9\xB6\xC8\xA3\xBA     \xC8\xA6/\xB7\xD6\xD6\xD3',36,0);"}; //方框、高速电机、角度、速度 
  MX_dataSize2=strlen_P(MX_ScreenMessage_menuPortView_motor1);for (MX_dataSize1 = 0; MX_dataSize1 < MX_dataSize2; MX_dataSize1++)
    {MX_sendChar =  pgm_read_byte_near(MX_ScreenMessage_menuPortView_motor1 + MX_dataSize1);Serial2.print(MX_sendChar);}
  const static char MX_ScreenMessage_menuPortView_motor2[] PROGMEM  = {"PS24(1,279,295,'\xCE\xC2\xB6\xC8\xA3\xBA      \xC9\xE3\xCA\xCF\xB6\xC8',36,0);PS24(1,515,217,'\xB9\xA9\xB5\xE7\xB5\xE7\xD1\xB9\xA3\xBA      \xB7\xFC',36,0);PS24(1,515,256,'\xB5\xE7\xBB\xFA\xB5\xE7\xC1\xF7\xA3\xBA    \xBA\xC1\xB0\xB2',36,0);"}; //温度、电压、电流
  MX_dataSize2=strlen_P(MX_ScreenMessage_menuPortView_motor2);for (MX_dataSize1 = 0; MX_dataSize1 < MX_dataSize2; MX_dataSize1++)
    {MX_sendChar =  pgm_read_byte_near(MX_ScreenMessage_menuPortView_motor2 + MX_dataSize1);Serial2.print(MX_sendChar);}    
  const static char MX_ScreenMessage_menuPortView_motor3[] PROGMEM  = {"PS24(1,515,295,'\xB5\xE7\xBB\xFA\xB9\xA6\xC2\xCA\xA3\xBA  \xB0\xD9\xB7\xD6\xB1\xC8',36,0);SBC(35);CBOF(264,343,739,392,5,35);BOXF(264,343,739,348,35);PS24(1,279,355,'\xB5\xE7\xBB\xFA\xD5\xFD\xD7\xAA',16,0);TPN(4);BTN(18,264,323,384,412,0);"}; //功率、电机正转
  MX_dataSize2=strlen_P(MX_ScreenMessage_menuPortView_motor3);for (MX_dataSize1 = 0; MX_dataSize1 < MX_dataSize2; MX_dataSize1++)
    {MX_sendChar =  pgm_read_byte_near(MX_ScreenMessage_menuPortView_motor3 + MX_dataSize1);Serial2.print(MX_sendChar);}    
  const static char MX_ScreenMessage_menuPortView_motor4[] PROGMEM  = {"PS24(1,395,355,'\xB5\xE7\xBB\xFA\xB7\xB4\xD7\xAA',16,0);BTN(19,385,323,505,412,0);NOBJ(2,510,349,729,386);SOP1(2,32,16,35,1);SLID(2,30,30,0,0);"}; //电机反转、滑块
  MX_dataSize2=strlen_P(MX_ScreenMessage_menuPortView_motor4);for (MX_dataSize1 = 0; MX_dataSize1 < MX_dataSize2; MX_dataSize1++)
    {MX_sendChar =  pgm_read_byte_near(MX_ScreenMessage_menuPortView_motor4 + MX_dataSize1);Serial2.print(MX_sendChar);}
  Serial2.println();while(!digitalRead(MX_screenBusy));while(digitalRead(MX_screenBusy));
  MX_screenMenuLoop3=1;
  while(MX_screenMenuLoop3)
  {   
    MX_screenBatteryV();//刷新时间及电量显示
    Serial2.print("SBC(0);");
    if(MX_motorData(MX_screen_char1,MXangle))//MX_IDcode MXangle,MXspeed,MXvoltage,MXcurrent,MXtemperature,MXrestart
      {Serial2.print("PS24(1,350,217,'");Serial2.print(MX_motorAngleN);Serial2.print("      ',36,446);");}
   if(MX_motorData(MX_screen_char1,MXspeed))
      {Serial2.print("PS24(1,350,256,'");Serial2.print(MX_motorDataN);Serial2.print("   ',36,398);");}
   if(MX_motorData(MX_screen_char1,MXtemperature))
      {Serial2.print("PS24(1,350,295,'");Serial2.print(MX_motorDataN);Serial2.print("  ',36,0);");}
   if(MX_motorData(MX_screen_char1,MXvoltage))
      {Serial2.print("PS24(1,626,217,'");Serial2.print((float)MX_motorDataN*15/1024);Serial2.print("',36,0);");}
   if(MX_motorData(MX_screen_char1,MXcurrent))
      {Serial2.print("PS24(1,626,256,'");Serial2.print(MX_motorDataN*10);Serial2.print("  ',36,684);");}
   if(MX_motorData(MX_screen_char1,7))
      {Serial2.print("PS24(1,622,295,'");Serial2.print((int)(MX_motorDataN/2.56));Serial2.print("  ',36,658);");}                           
    Serial2.println();while(!digitalRead(MX_screenBusy));while(digitalRead(MX_screenBusy)); 
    if(MX_screenGetButtonPress())  
    {
      if(MX_screenButtonN==18)
      { MX_screenGetOBJ2();
        MX_motorControl(MX_screen_char1,10,MX_screenButtonN,0);
        while(!MX_screenGetButton())
        {
     MX_screenBatteryV();//刷新时间及电量显示
    Serial2.print("SBC(0);");
    if(MX_motorData(MX_screen_char1,MXangle))//MX_IDcode MXangle,MXspeed,MXvoltage,MXcurrent,MXtemperature,MXrestart
      {Serial2.print("PS24(1,350,217,'");Serial2.print(MX_motorAngleN);Serial2.print("      ',36,446);");}
   if(MX_motorData(MX_screen_char1,MXspeed))
      {Serial2.print("PS24(1,350,256,'");Serial2.print(MX_motorDataN);Serial2.print("   ',36,398);");}
   if(MX_motorData(MX_screen_char1,MXtemperature))
      {Serial2.print("PS24(1,350,295,'");Serial2.print(MX_motorDataN);Serial2.print("  ',36,0);");}
   if(MX_motorData(MX_screen_char1,MXvoltage))
      {Serial2.print("PS24(1,626,217,'");Serial2.print((float)MX_motorDataN*15/1024);Serial2.print("',36,0);");}
   if(MX_motorData(MX_screen_char1,MXcurrent))
      {Serial2.print("PS24(1,626,256,'");Serial2.print(MX_motorDataN*10);Serial2.print("  ',36,684);");}
   if(MX_motorData(MX_screen_char1,7))
      {Serial2.print("PS24(1,622,295,'");Serial2.print((int)(MX_motorDataN/2.56));Serial2.print("  ',36,658);");}                           
    Serial2.println();while(!digitalRead(MX_screenBusy));while(digitalRead(MX_screenBusy));       
        }
        MX_motorControl(MX_screen_char1,10,0,0);
      }
      else if(MX_screenButtonN==19)
      { MX_screenGetOBJ2();
        MX_motorControl(MX_screen_char1,10,MX_screenButtonN*-1 ,0);
        while(!MX_screenGetButton())
        {
     MX_screenBatteryV();//刷新时间及电量显示
    Serial2.print("SBC(0);");
    if(MX_motorData(MX_screen_char1,MXangle))//MX_IDcode MXangle,MXspeed,MXvoltage,MXcurrent,MXtemperature,MXrestart
      {Serial2.print("PS24(1,350,217,'");Serial2.print(MX_motorAngleN);Serial2.print("      ',36,446);");}
   if(MX_motorData(MX_screen_char1,MXspeed))
      {Serial2.print("PS24(1,350,256,'");Serial2.print(MX_motorDataN);Serial2.print("   ',36,398);");}
   if(MX_motorData(MX_screen_char1,MXtemperature))
      {Serial2.print("PS24(1,350,295,'");Serial2.print(MX_motorDataN);Serial2.print("  ',36,0);");}
   if(MX_motorData(MX_screen_char1,MXvoltage))
      {Serial2.print("PS24(1,626,217,'");Serial2.print((float)MX_motorDataN*15/1024);Serial2.print("',36,0);");}
   if(MX_motorData(MX_screen_char1,MXcurrent))
      {Serial2.print("PS24(1,626,256,'");Serial2.print(MX_motorDataN*10);Serial2.print("  ',36,684);");}
   if(MX_motorData(MX_screen_char1,7))
      {Serial2.print("PS24(1,622,295,'");Serial2.print((int)(MX_motorDataN/2.56));Serial2.print("  ',36,658);");}                           
    Serial2.println();while(!digitalRead(MX_screenBusy));while(digitalRead(MX_screenBusy));        
        }
        MX_motorControl(MX_screen_char1,10,0,0);
      }
      else//按下其他按键。
      {
        MX_screenMenuLoop3=0;Serial2.print("TPN(2);");
        Serial2.println();while(!digitalRead(MX_screenBusy));while(digitalRead(MX_screenBusy));     
      }
    } 
  }
}
//用于选择，并显示队伍颜色、队员号码，参赛必备
void MX_teamFlag()
{
  uchar MX_teamColor,MX_teamNum;
  const static char MX_ScreenMessage_example3wheels1[] PROGMEM  = {"CLS(0);CBOF(10,10,843,71,6,34);SHTM(32,27,28,16,34);PIC(122,17,6);SBC(34);PS24(1,565,28,'\xB5\xE7\xB3\xD8\xB5\xE7\xD1\xB9\xA3\xBA',36,0);PS32(1,740,25,'V',36,0);"};
    MX_dataSize2=strlen_P(MX_ScreenMessage_example3wheels1);for (MX_dataSize1 = 0; MX_dataSize1 < MX_dataSize2; MX_dataSize1++)
  {MX_sendChar =  pgm_read_byte_near(MX_ScreenMessage_example3wheels1 + MX_dataSize1);Serial2.print(MX_sendChar);}

  const static char MX_ScreenMessage_example3wheels3[] PROGMEM  = {"SBC(0);DS24(234,140,'\xD1\xA1\xD4\xF1\xD5\xF3\xD3\xAA:',36,0);BTN(1,360,140,450,193,4,0);PS32(1,375,151,'\xBA\xEC\xB6\xD3',1,0);BTN(3,480,140,570,193,4,0);PS32(1,495,151,'\xC0\xB6\xB6\xD3',3,0);"}; 
    MX_dataSize2=strlen_P(MX_ScreenMessage_example3wheels3);for (MX_dataSize1 = 0; MX_dataSize1 < MX_dataSize2; MX_dataSize1++)
  {MX_sendChar =  pgm_read_byte_near(MX_ScreenMessage_example3wheels3 + MX_dataSize1);Serial2.print(MX_sendChar);}
  Serial2.println();while(!digitalRead(MX_screenBusy));while(digitalRead(MX_screenBusy));    
  while(!MX_screenGetButton())MX_screenBatteryV(); 
    MX_teamColor=MX_screenButtonN;
  const static char MX_ScreenMessage_example3wheels4[] PROGMEM  = {"SBC(0);BOXF(360,299,700,359,0);DS24(234,299,'\xD1\xA1\xD4\xF1\xBA\xC5\xC2\xEB:',36,0);BTN(1,360,299,420,359,4,0);DS48(380,308,'1',16,0);BTN(2,430,299,490,359,4,0);DS48(450,308,'2',16,0);BTN(3,500,299,560,359,4,0);DS48(520,308,'3',16,0);BTN(4,570,299,630,359,4,0);DS48(590,308,'4',16,0);BTN(5,640,299,700,359,4,0);DS48(660,308,'5',16,0);"}; 
    MX_dataSize2=strlen_P(MX_ScreenMessage_example3wheels4);for (MX_dataSize1 = 0; MX_dataSize1 < MX_dataSize2; MX_dataSize1++)
  {MX_sendChar =  pgm_read_byte_near(MX_ScreenMessage_example3wheels4 + MX_dataSize1);Serial2.print(MX_sendChar);}
  Serial2.println();while(!digitalRead(MX_screenBusy));while(digitalRead(MX_screenBusy));    
  while(!MX_screenGetButton())MX_screenBatteryV();
    MX_teamNum=MX_screenButtonN;
  Serial2.print("CLS(");Serial2.print(MX_teamColor);Serial2.print(");");Serial2.print("DSD(48,335,50,'");Serial2.print(MX_teamNum);Serial2.print("',11,11,16);"); 
  const static char MX_ScreenMessage_example3wheels5[] PROGMEM  = {"CBOF(10,10,843,71,6,34);SHTM(32,27,28,16,34);PIC(122,17,6);SBC(34);PS24(1,565,28,'\xB5\xE7\xB3\xD8\xB5\xE7\xD1\xB9\xA3\xBA',36,0);PS32(1,740,25,'V',36,0);"}; //顶部栏无需刷新的元素
    MX_dataSize2=strlen_P(MX_ScreenMessage_example3wheels5);for (MX_dataSize1 = 0; MX_dataSize1 < MX_dataSize2; MX_dataSize1++)
  {MX_sendChar =  pgm_read_byte_near(MX_ScreenMessage_example3wheels5 + MX_dataSize1);Serial2.print(MX_sendChar);}   
  Serial2.println();while(!digitalRead(MX_screenBusy));while(digitalRead(MX_screenBusy));    
}
////////////////////示例程序：两轮驱动
void MX_example2Wheel()
{
  uchar MX_remoteSafety;
  const static char MX_ScreenMessage_example3wheels5[] PROGMEM  = {"CLS();CBOF(10,10,843,71,6,34);SHTM(32,27,28,16,34);PIC(122,17,6);SBC(34);PS24(1,565,28,'\xB5\xE7\xB3\xD8\xB5\xE7\xD1\xB9\xA3\xBA',36,0);PS32(1,740,25,'V',36,0);SBC(0);ICON(255,175,11,3,1,0);PS24(1,440,185,'\xC1\xBD\xC2\xD6\xC7\xFD\xB6\xAF\xBB\xFA\xC6\xF7\xC8\xCB',16,0);PS16(1,440,225,'\xD7\xF3\xC2\xD6 - Port 1',35,0);PS16(1,440,250,'\xD3\xD2\xC2\xD6 - Port 2',35,0);"}; //顶部栏无需刷新的元素
    MX_dataSize2=strlen_P(MX_ScreenMessage_example3wheels5);for (MX_dataSize1 = 0; MX_dataSize1 < MX_dataSize2; MX_dataSize1++)
  {MX_sendChar =  pgm_read_byte_near(MX_ScreenMessage_example3wheels5 + MX_dataSize1);Serial2.print(MX_sendChar);}
  while(1)
  {       
    MX_screenBatteryV();//刷新时间及电量显示
    MX_runUSB();
   if(MX_gamepadConnected())
   { 
    MX_remoteSafety=0;
    MX_motorControl(1,10,(MX_gamepadRightY*-1+MX_gamepadRightX*-0.3)*0.8,0);MX_motorControl(2,10,(MX_gamepadRightY+MX_gamepadRightX*-0.3)*0.8,0);
   }
    else
    {
      if(MX_remoteSafety<30)MX_remoteSafety++;
    }
    if(MX_remoteSafety==20)
    {
        MX_motorControl(1,22,0,0);MX_motorControl(2,22,0,0);
    }
  }    
}
////////////////////////////遥控：足球机器人
void MX_exampleFootball()
{
  uchar MX_teamColor,MX_teamNum,MX_remoteSafety;//选择队伍颜色和队伍号的变量
  int MX_exampleFootball_motor1,MX_exampleFootball_motor2;
  int MX_exampleFootball_motor1abs,MX_exampleFootball_motor2abs;
  const static char MX_ScreenMessage_example3wheels1[] PROGMEM  = {"CLS(0);CBOF(10,10,843,71,6,34);SHTM(32,27,28,16,34);PIC(122,17,6);SBC(34);PS24(1,565,28,'\xB5\xE7\xB3\xD8\xB5\xE7\xD1\xB9\xA3\xBA',36,0);PS32(1,740,25,'V',36,0);"};
    MX_dataSize2=strlen_P(MX_ScreenMessage_example3wheels1);for (MX_dataSize1 = 0; MX_dataSize1 < MX_dataSize2; MX_dataSize1++)
  {MX_sendChar =  pgm_read_byte_near(MX_ScreenMessage_example3wheels1 + MX_dataSize1);Serial2.print(MX_sendChar);}
  const static char MX_ScreenMessage_example3wheels2[] PROGMEM  = {"SBC(0);ICON(60,110,11,3,1,2);DS32(234,111,'\xD7\xE3\xC7\xF2\xBB\xFA\xC6\xF7\xC8\xCB',16,0);DS24(234,165,'\xB6\xCB\xBF\xDA\xC1\xAC\xBD\xD3:',35,0);DS24(360,165,'\xD7\xF3\xC7\xFD\xB6\xAF\xC2\xD6 - Port 1   \xD3\xD2\xC7\xFD\xB6\xAF\xC2\xD6 - Port 2',35,0);DS24(360,205,'\xD7\xF3\xB4\xF8\xC7\xF2\xC2\xD6 - Port 3   \xD3\xD2\xB4\xF8\xC7\xF2\xC2\xD6 - Port 4',35,0);DS24(360,245,'  \xB5\xAF\xC9\xE4\xC6\xF7 - Port 5',35,0);"}; 
    MX_dataSize2=strlen_P(MX_ScreenMessage_example3wheels2);for (MX_dataSize1 = 0; MX_dataSize1 < MX_dataSize2; MX_dataSize1++)
  {MX_sendChar =  pgm_read_byte_near(MX_ScreenMessage_example3wheels2 + MX_dataSize1);Serial2.print(MX_sendChar);}
  const static char MX_ScreenMessage_example3wheels3[] PROGMEM  = {"DS24(234,299,'\xD1\xA1\xD4\xF1\xD5\xF3\xD3\xAA:',36,0);BTN(1,360,299,450,352,4,0);PS32(1,375,310,'\xBA\xEC\xB6\xD3',1,0);BTN(3,480,299,570,352,4,0);PS32(1,495,310,'\xC0\xB6\xB6\xD3',3,0);"}; 
    MX_dataSize2=strlen_P(MX_ScreenMessage_example3wheels3);for (MX_dataSize1 = 0; MX_dataSize1 < MX_dataSize2; MX_dataSize1++)
  {MX_sendChar =  pgm_read_byte_near(MX_ScreenMessage_example3wheels3 + MX_dataSize1);Serial2.print(MX_sendChar);}
  Serial2.println();while(!digitalRead(MX_screenBusy));while(digitalRead(MX_screenBusy));    
  while(!MX_screenGetButton())MX_screenBatteryV(); 
    MX_teamColor=MX_screenButtonN;
  const static char MX_ScreenMessage_example3wheels4[] PROGMEM  = {"SBC(0);BOXF(360,299,700,359,0);DS24(234,299,'\xD1\xA1\xD4\xF1\xBA\xC5\xC2\xEB:',36,0);BTN(1,360,299,420,359,4,0);DS48(380,308,'1',16,0);BTN(2,430,299,490,359,4,0);DS48(450,308,'2',16,0);BTN(3,500,299,560,359,4,0);DS48(520,308,'3',16,0);BTN(4,570,299,630,359,4,0);DS48(590,308,'4',16,0);BTN(5,640,299,700,359,4,0);DS48(660,308,'5',16,0);"}; 
    MX_dataSize2=strlen_P(MX_ScreenMessage_example3wheels4);for (MX_dataSize1 = 0; MX_dataSize1 < MX_dataSize2; MX_dataSize1++)
  {MX_sendChar =  pgm_read_byte_near(MX_ScreenMessage_example3wheels4 + MX_dataSize1);Serial2.print(MX_sendChar);}
  Serial2.println();while(!digitalRead(MX_screenBusy));while(digitalRead(MX_screenBusy));    
  while(!MX_screenGetButton())MX_screenBatteryV();
    MX_teamNum=MX_screenButtonN;
  Serial2.print("CLS(");Serial2.print(MX_teamColor);Serial2.print(");");Serial2.print("DSD(48,335,50,'");Serial2.print(MX_teamNum);Serial2.print("',11,11,16);"); 
  const static char MX_ScreenMessage_example3wheels5[] PROGMEM  = {"CBOF(10,10,843,71,6,34);SHTM(32,27,28,16,34);PIC(122,17,6);SBC(34);PS24(1,565,28,'\xB5\xE7\xB3\xD8\xB5\xE7\xD1\xB9\xA3\xBA',36,0);PS32(1,740,25,'V',36,0);"}; //顶部栏无需刷新的元素
    MX_dataSize2=strlen_P(MX_ScreenMessage_example3wheels5);for (MX_dataSize1 = 0; MX_dataSize1 < MX_dataSize2; MX_dataSize1++)
  {MX_sendChar =  pgm_read_byte_near(MX_ScreenMessage_example3wheels5 + MX_dataSize1);Serial2.print(MX_sendChar);}
  while(1)
  {       
    MX_screenBatteryV();//刷新时间及电量显示
    MX_runUSB();
   if(MX_gamepadConnected())
   { 
    MX_remoteSafety=0;
    MX_exampleFootball_motor1=MX_gamepadRightY*-1+MX_gamepadRightX*-0.1+(MX_gamepadPress(L2)-MX_gamepadPress(R2))*0.1;
    MX_exampleFootball_motor2=MX_gamepadRightY+MX_gamepadRightX*-0.1+(MX_gamepadPress(L2)-MX_gamepadPress(R2))*0.1;
    MX_exampleFootball_motor1+=MX_gamepadLeftY+MX_gamepadLeftX*-0.1;
    MX_exampleFootball_motor2+=MX_gamepadLeftY*-1+MX_gamepadLeftX*-0.1;
    MX_exampleFootball_motor1abs=abs(MX_exampleFootball_motor1);
    MX_exampleFootball_motor2abs=abs(MX_exampleFootball_motor2);
    
    if(MX_exampleFootball_motor1abs>100 && MX_exampleFootball_motor1abs>MX_exampleFootball_motor2abs)
    {
      MX_exampleFootball_motor1=(int)(MX_exampleFootball_motor1*(100/(float)MX_exampleFootball_motor1abs));
      MX_exampleFootball_motor2=(int)(MX_exampleFootball_motor2*(100/(float)MX_exampleFootball_motor1abs));
    }
    else if(MX_exampleFootball_motor2abs>100 && MX_exampleFootball_motor2abs>MX_exampleFootball_motor1abs)
    {
      MX_exampleFootball_motor1=(int)(MX_exampleFootball_motor1*(100/(float)MX_exampleFootball_motor2abs));
      MX_exampleFootball_motor2=(int)(MX_exampleFootball_motor2*(100/(float)MX_exampleFootball_motor2abs));
    }
    
    MX_motorControl(1,10,MX_exampleFootball_motor1,0);MX_motorControl(2,10,MX_exampleFootball_motor2,0);

    if(MX_gamepadClick(L1))
    {
      MX_motorControl(3,0,-100,0);MX_motorControl(4,0,10,0);
    }
    if(MX_gamepadClick(R1))
    {
      MX_motorControl(3,0,-10,0);MX_motorControl(4,0,100,0);
    }    
    if(MX_gamepadClick(A))
    {
      MX_relayControl(6);MX_motorControl(3,22,0,0);MX_motorControl(4,22,0,0);
    }
    
    if(MX_gamepadClick(Y))
    {
      MX_motorControl(3,22,0,0);MX_motorControl(4,22,0,0);
    }   
  }
    else
    {
      if(MX_remoteSafety<30)MX_remoteSafety++;
    }
    if(MX_remoteSafety==20)
    {
        MX_motorControl(1,22,0,0);MX_motorControl(2,22,0,0);
    }
  }  
}
////////////////////////////遥控：三轮全向
void MX_example3wheels()
{ 
  uchar MX_teamColor,MX_teamNum,MX_remoteSafety;//选择队伍颜色和队伍号的变量
  int MX_example3wheels_motor1,MX_example3wheels_motor2,MX_example3wheels_motor3;
  int MX_example3wheels_motor1abs,MX_example3wheels_motor2abs,MX_example3wheels_motor3abs;
  const static char MX_ScreenMessage_example3wheels1[] PROGMEM  = {"CLS(0);CBOF(10,10,843,71,6,34);SHTM(32,27,28,16,34);PIC(122,17,6);SBC(34);PS24(1,565,28,'\xB5\xE7\xB3\xD8\xB5\xE7\xD1\xB9\xA3\xBA',36,0);PS32(1,740,25,'V',36,0);"};
    MX_dataSize2=strlen_P(MX_ScreenMessage_example3wheels1);for (MX_dataSize1 = 0; MX_dataSize1 < MX_dataSize2; MX_dataSize1++)
  {MX_sendChar =  pgm_read_byte_near(MX_ScreenMessage_example3wheels1 + MX_dataSize1);Serial2.print(MX_sendChar);}
  const static char MX_ScreenMessage_example3wheels2[] PROGMEM  = {"SBC(0);ICON(60,110,11,3,1,1);DS32(234,111,'\xC8\xFD\xC2\xD6\xC8\xAB\xCF\xF2\xBB\xFA\xC6\xF7\xC8\xCB',16,0);DS24(234,165,'\xB6\xCB\xBF\xDA\xC1\xAC\xBD\xD3:',35,0);DS24(360,165,'\xD7\xF3\xC7\xB0\xC2\xD6 - Port 9',35,0);DS24(360,205,'\xD3\xD2\xC7\xB0\xC2\xD6 - Port 7',35,0);DS24(360,245,'  \xBA\xF3\xC2\xD6 - Port 8',35,0);"}; 
    MX_dataSize2=strlen_P(MX_ScreenMessage_example3wheels2);for (MX_dataSize1 = 0; MX_dataSize1 < MX_dataSize2; MX_dataSize1++)
  {MX_sendChar =  pgm_read_byte_near(MX_ScreenMessage_example3wheels2 + MX_dataSize1);Serial2.print(MX_sendChar);}
  const static char MX_ScreenMessage_example3wheels3[] PROGMEM  = {"DS24(234,299,'\xD1\xA1\xD4\xF1\xD5\xF3\xD3\xAA:',36,0);BTN(1,360,299,450,352,4,0);PS32(1,375,310,'\xBA\xEC\xB6\xD3',1,0);BTN(3,480,299,570,352,4,0);PS32(1,495,310,'\xC0\xB6\xB6\xD3',3,0);"}; 
    MX_dataSize2=strlen_P(MX_ScreenMessage_example3wheels3);for (MX_dataSize1 = 0; MX_dataSize1 < MX_dataSize2; MX_dataSize1++)
  {MX_sendChar =  pgm_read_byte_near(MX_ScreenMessage_example3wheels3 + MX_dataSize1);Serial2.print(MX_sendChar);}
  Serial2.println();while(!digitalRead(MX_screenBusy));while(digitalRead(MX_screenBusy));    
  while(!MX_screenGetButton())MX_screenBatteryV(); 
    MX_teamColor=MX_screenButtonN;
  const static char MX_ScreenMessage_example3wheels4[] PROGMEM  = {"SBC(0);BOXF(360,299,700,359,0);DS24(234,299,'\xD1\xA1\xD4\xF1\xBA\xC5\xC2\xEB:',36,0);BTN(1,360,299,420,359,4,0);DS48(380,308,'1',16,0);BTN(2,430,299,490,359,4,0);DS48(450,308,'2',16,0);BTN(3,500,299,560,359,4,0);DS48(520,308,'3',16,0);BTN(4,570,299,630,359,4,0);DS48(590,308,'4',16,0);BTN(5,640,299,700,359,4,0);DS48(660,308,'5',16,0);"}; 
    MX_dataSize2=strlen_P(MX_ScreenMessage_example3wheels4);for (MX_dataSize1 = 0; MX_dataSize1 < MX_dataSize2; MX_dataSize1++)
  {MX_sendChar =  pgm_read_byte_near(MX_ScreenMessage_example3wheels4 + MX_dataSize1);Serial2.print(MX_sendChar);}
  Serial2.println();while(!digitalRead(MX_screenBusy));while(digitalRead(MX_screenBusy));    
  while(!MX_screenGetButton())MX_screenBatteryV();
    MX_teamNum=MX_screenButtonN;
  Serial2.print("CLS(");Serial2.print(MX_teamColor);Serial2.print(");");Serial2.print("DSD(48,335,50,'");Serial2.print(MX_teamNum);Serial2.print("',11,11,16);"); 
  const static char MX_ScreenMessage_example3wheels5[] PROGMEM  = {"CBOF(10,10,843,71,6,34);SHTM(32,27,28,16,34);PIC(122,17,6);SBC(34);PS24(1,565,28,'\xB5\xE7\xB3\xD8\xB5\xE7\xD1\xB9\xA3\xBA',36,0);PS32(1,740,25,'V',36,0);"}; //顶部栏无需刷新的元素
    MX_dataSize2=strlen_P(MX_ScreenMessage_example3wheels5);for (MX_dataSize1 = 0; MX_dataSize1 < MX_dataSize2; MX_dataSize1++)
  {MX_sendChar =  pgm_read_byte_near(MX_ScreenMessage_example3wheels5 + MX_dataSize1);Serial2.print(MX_sendChar);}
  while(1)
  {       
    MX_screenBatteryV();//刷新时间及电量显示
    MX_runUSB();
    if(MX_gamepadConnected())
    { MX_remoteSafety=0;
      MX_example3wheels_motor1=MX_gamepadRightY*-1+MX_gamepadRightX*-0.5+MX_gamepadLeftX*-0.5+(MX_gamepadPress(L2)-MX_gamepadPress(R2))*0.1;
      MX_example3wheels_motor2=MX_gamepadRightY+MX_gamepadRightX*-0.5+MX_gamepadLeftX*-0.5+(MX_gamepadPress(L2)-MX_gamepadPress(R2))*0.1;
      MX_example3wheels_motor3=MX_gamepadRightX+MX_gamepadLeftX*-0.5+(MX_gamepadPress(L2)-MX_gamepadPress(R2))*0.1;
      MX_example3wheels_motor1*=0.6;
      MX_example3wheels_motor2*=0.6;
      MX_example3wheels_motor3*=0.6;      
      MX_example3wheels_motor1abs=abs(MX_example3wheels_motor1);
      MX_example3wheels_motor2abs=abs(MX_example3wheels_motor2);
      MX_example3wheels_motor3abs=abs(MX_example3wheels_motor3);
      
      if(MX_example3wheels_motor1abs>100 || MX_example3wheels_motor2abs>100 || MX_example3wheels_motor3abs>100)
      {
          if(MX_example3wheels_motor1abs>MX_example3wheels_motor2abs && MX_example3wheels_motor1abs>MX_example3wheels_motor3abs)
          {
            MX_example3wheels_motor1=MX_example3wheels_motor1*(100/(float)MX_example3wheels_motor1abs);
            MX_example3wheels_motor2=MX_example3wheels_motor2*(100/(float)MX_example3wheels_motor1abs);
            MX_example3wheels_motor3=MX_example3wheels_motor3*(100/(float)MX_example3wheels_motor1abs);
          }
          else if(MX_example3wheels_motor2abs>MX_example3wheels_motor1abs && MX_example3wheels_motor2abs>MX_example3wheels_motor3abs)
          {
            MX_example3wheels_motor1=MX_example3wheels_motor1*(100/(float)MX_example3wheels_motor2abs);
            MX_example3wheels_motor2=MX_example3wheels_motor2*(100/(float)MX_example3wheels_motor2abs);
            MX_example3wheels_motor3=MX_example3wheels_motor3*(100/(float)MX_example3wheels_motor2abs);
          }
          else if(MX_example3wheels_motor3abs>MX_example3wheels_motor1abs && MX_example3wheels_motor3abs>MX_example3wheels_motor2abs)
          {
            MX_example3wheels_motor1=MX_example3wheels_motor1*(100/(float)MX_example3wheels_motor3abs);
            MX_example3wheels_motor2=MX_example3wheels_motor2*(100/(float)MX_example3wheels_motor3abs);
            MX_example3wheels_motor3=MX_example3wheels_motor3*(100/(float)MX_example3wheels_motor3abs);
          }
      }
      MX_motorControl(9,10,MX_example3wheels_motor1,0);MX_motorControl(7,10,MX_example3wheels_motor2,0);MX_motorControl(8,10,MX_example3wheels_motor3,0);
    }
    else
    {
      if(MX_remoteSafety<30)MX_remoteSafety++;
    }
    if(MX_remoteSafety==20)
    {
        MX_motorControl(9,22,0,0);MX_motorControl(7,22,0,0);MX_motorControl(8,22,0,0);
    }
  }  
}
///////////////////////////手柄
void MX_menuGamePad()
{
  Serial2.print("SBC(0);PS24(1,380,250,'\xD5\xFD\xD4\xDA\xCB\xD1\xCB\xF7USB\xC9\xE8\xB1\xB8...',16,0);");//搜索中提示  
  Serial2.print("\r\n");while(!digitalRead(MX_screenBusy));while(digitalRead(MX_screenBusy));   
  
  do{Usb.Init();delay(400);MX_runUSB();delay(5);MX_screenBatteryV();}//刷新时间及电量显示
  while(!MX_screenGetButton() && !MX_gamepadConnected());
  if(MX_gamepadConnected())
  {
    Serial2.print("CBOF(264,163,739,392,5,0);CBOX(264,163,739,392,5,16);CIR(501,260,15,16);PS24(1,455,190,'\xCE\xDE\xCF\xDF\xCA\xD6\xB1\xFA',16,0);");//首次显示不变的部分  
    Serial2.print("CIR(334,280,40,16);CIR(569,330,40,16);");//左右摇杆的圆圈
    Serial2.print("\r\n");while(!digitalRead(MX_screenBusy));while(digitalRead(MX_screenBusy));  
    while(!MX_screenGetButton())
    {   MX_screenBatteryV();//刷新时间及电量显示
        MX_runUSB();
        if(MX_gamepadConnected())
        { 
          Serial2.print("CIRF(334,280,38,0);CIRF(");Serial2.print(MX_gamepadLeftX/4+334);Serial2.print(",");Serial2.print(280-MX_gamepadLeftY/4);Serial2.print(",4,16);");//左摇杆
          Serial2.print("CIRF(569,330,38,0);CIRF(");Serial2.print(MX_gamepadRightX/4+569);Serial2.print(",");Serial2.print(330-MX_gamepadRightY/4);Serial2.print(",4,16);");//右摇杆
          Serial2.print("SBC(0);PS16(1,310,182,'L2:"); Serial2.print(MX_gamepadPress(L2));Serial2.print("  ',16,0);CBOX(299,178,369,198,5,16);");//L2
          Serial2.print("PS16(1,645,182,'R2:"); Serial2.print(MX_gamepadPress(R2));Serial2.print("  ',16,0);CBOX(634,178,704,198,5,16);");//R2
          Serial2.print("CBOX(299,208,369,228,5,");Serial2.print(MX_gamepadPress(L1)*11+16);Serial2.print(");PS16(1,328,212,'L1',");Serial2.print(MX_gamepadPress(L1)*11+16);Serial2.print(",0);");//L1
          Serial2.print("CBOX(634,208,704,228,5,");Serial2.print(MX_gamepadPress(R1)*11+16);Serial2.print(");PS16(1,663,212,'R1',");Serial2.print(MX_gamepadPress(R1)*11+16);Serial2.print(",0);");//R1
          Serial2.print("CBOX(420,250,470,270,5,");Serial2.print(MX_gamepadPress(BACK)*11+16);Serial2.print(");PS16(1,430,253,'BACK',");Serial2.print(MX_gamepadPress(BACK)*11+16);Serial2.print(",0);");//BACK
          Serial2.print("CBOX(530,250,580,270,5,");Serial2.print(MX_gamepadPress(START)*11+16);Serial2.print(");PS16(1,536,253,'START',");Serial2.print(MX_gamepadPress(START)*11+16);Serial2.print(",0);");//START
          Serial2.print("CIR(644,280,15,");Serial2.print(MX_gamepadPress(X)*11+16);Serial2.print(");PS24(1,639,267,'X',");Serial2.print(MX_gamepadPress(X)*11+16);Serial2.print(",0);");//X
          Serial2.print("CIR(694,280,15,");Serial2.print(MX_gamepadPress(B)*11+16);Serial2.print(");PS24(1,689,267,'B',");Serial2.print(MX_gamepadPress(B)*11+16);Serial2.print(",0);");//B
          Serial2.print("CIR(669,255,15,");Serial2.print(MX_gamepadPress(Y)*11+16);Serial2.print(");PS24(1,664,242,'Y',");Serial2.print(MX_gamepadPress(Y)*11+16);Serial2.print(",0);");//B
          Serial2.print("CIR(669,305,15,");Serial2.print(MX_gamepadPress(A)*11+16);Serial2.print(");PS24(1,664,292,'A',");Serial2.print(MX_gamepadPress(A)*11+16);Serial2.print(",0);");//B
          Serial2.print("CBOX(440,318,481,342,5,");Serial2.print(MX_gamepadPress(RIGHT)*11+16);Serial2.print(");PS16(1,441,323,'RIGHT',");Serial2.print(MX_gamepadPress(RIGHT)*11+16);Serial2.print(",0);");//RIGHT
          Serial2.print("CBOX(387,318,428,342,5,");Serial2.print(MX_gamepadPress(LEFT)*11+16);Serial2.print(");PS16(1,392,323,'LEFT',");Serial2.print(MX_gamepadPress(LEFT)*11+16);Serial2.print(",0);");//RIGHT
          Serial2.print("CBOX(415,290,453,314,5,");Serial2.print(MX_gamepadPress(UP)*11+16);Serial2.print(");PS16(1,419,296,' UP',");Serial2.print(MX_gamepadPress(UP)*11+16);Serial2.print(",0);");//RIGHT
          Serial2.print("CBOX(415,346,453,370,5,");Serial2.print(MX_gamepadPress(DOWN)*11+16);Serial2.print(");PS16(1,419,352,'DOWN',");Serial2.print(MX_gamepadPress(DOWN)*11+16);Serial2.print(",0);");//RIGHT
          Serial2.println();while(!digitalRead(MX_screenBusy));while(digitalRead(MX_screenBusy));  
        }
    }  
    Serial2.print("CBOF(264,163,739,392,5,0);"); //清除手柄界面
    Serial2.println();while(!digitalRead(MX_screenBusy));while(digitalRead(MX_screenBusy));        
  }
}

///////////////////////////菜单界面子函数，0：基础显示内容，1-4，切换为1-4菜单
void MX_menuMain(uchar MX_menuMain_n)
{
  switch(MX_menuMain_last)//上一次的菜单序号，用于消除高亮选择
  {
    case  1://反选开始
    {
        Serial2.print("CBOF(10,10,163,125,6,34);BOXF(10,109,163,125,34);");//覆盖dock栏内容
        Serial2.print("SBC(34);ICON(53,15,8,4,1,0);PS24(1,62,85,'\xBF\xAA\xCA\xBC',36,0);ICON(70,115,9,3,2,2);");//恢复dock栏显示
        Serial2.print("BOXF(260,200,738,360,0);");//清除中间区域
    }break;
    case  2://反选遥控
    {        
        Serial2.print("BOXF(10,125,163,240,34);");//覆盖dock栏内容
        Serial2.print("SBC(34);ICON(53,128,8,4,1,1);PS24(1,62,193,'\xD2\xA3\xBF\xD8',36,0);ICON(70,227,9,3,2,02);");;//恢复dock栏显示
        Serial2.print("BOXF(237,175,754,355,0);");//清除中间区域
    }break;
    case  3://反选端口
    {
        Serial2.print("BOXF(10,240,163,355,34);");//覆盖dock栏内容
        Serial2.print("SBC(34);ICON(53,242,8,4,1,2);PS24(1,62,310,'\xB6\xCB\xBF\xDA',36,0);ICON(70,343,9,3,2,2);BOXF(172,80,845,475,0);");//恢复dock栏显示
         Serial2.print("BOXF(172,80,845,475,0);");//清除中间区域    
        for(uchar MX_screen_char1=5;MX_screen_char1<18;MX_screen_char1++)//清除多余按键  
          {Serial2.print("BTN(");Serial2.print(MX_screen_char1);Serial2.print(",0,0,1,0,0,0);");}
        Serial2.println();while(!digitalRead(MX_screenBusy));while(digitalRead(MX_screenBusy));   
    }break;
    case  4://反选设置
    {
        Serial2.print("CBOF(10,355,163,470,6,34);BOXF(10,355,163,360,34);");//覆盖dock栏内容
        Serial2.print("SBC(34);ICON(53,360,8,4,1,3);PS24(1,62,428,'\xC9\xE8\xD6\xC3',36,0);ICON(70,460,9,3,2,2);");//恢复dock栏显示
        Serial2.print("BOXF(240,98,790,446,0);");//清除中间区域
        Serial2.print("BTN(8,0,0,1,0,0,0);BTN(9,0,0,1,0,0,0);");//清除多余按键        

    }break;
  }
  switch(MX_menuMain_n)
  {
    case 0:
    {          
        const static char MX_ScreenMessage_menuMainInit1[] PROGMEM  = {"CLS();TPN(4);SCC(34,16904);SCC(35,29582);SCC(36,54938);"}; //清屏.设置触摸模式：高级.设置所需颜色. 
          MX_dataSize2=strlen_P(MX_ScreenMessage_menuMainInit1);for (MX_dataSize1 = 0; MX_dataSize1 < MX_dataSize2; MX_dataSize1++)
              {MX_sendChar =  pgm_read_byte_near(MX_ScreenMessage_menuMainInit1 + MX_dataSize1);Serial2.print(MX_sendChar);}
        const static char MX_ScreenMessage_menuMainInit2[] PROGMEM  = {"BTN(1,10,10,163,125,0);BTN(2,10,125,163,240,0);BTN(3,10,240,163,355,0);BTN(4,10,355,163,470,0);"}; //设置dock栏按键，1-4
          MX_dataSize2=strlen_P(MX_ScreenMessage_menuMainInit2);for (MX_dataSize1 = 0; MX_dataSize1 < MX_dataSize2; MX_dataSize1++)
              {MX_sendChar =  pgm_read_byte_near(MX_ScreenMessage_menuMainInit2 + MX_dataSize1);Serial2.print(MX_sendChar);}
        const static char MX_ScreenMessage_menuMainInit3[] PROGMEM  = {"CBOF(173,10,843,71,6,34);SHTM(32,190,28,16,34);PIC(285,17,6);SBC(34);PS24(1,565,28,'\xB5\xE7\xB3\xD8\xB5\xE7\xD1\xB9\xA3\xBA',36,0);PS32(1,740,25,'V',36,0);"}; //顶部栏无需刷新的元素
          MX_dataSize2=strlen_P(MX_ScreenMessage_menuMainInit3);for (MX_dataSize1 = 0; MX_dataSize1 < MX_dataSize2; MX_dataSize1++)
              {MX_sendChar =  pgm_read_byte_near(MX_ScreenMessage_menuMainInit3 + MX_dataSize1);Serial2.print(MX_sendChar);}
        const static char MX_ScreenMessage_menuMainInit4[] PROGMEM  = {"CBOF(10,10,163,470,6,34);SBC(34);ICON(53,15,8,4,1,0);PS24(1,62,85,'\xBF\xAA\xCA\xBC',36,0);ICON(70,115,9,3,2,2);ICON(53,128,8,4,1,1);PS24(1,62,193,'\xD2\xA3\xBF\xD8',36,0);ICON(70,227,9,3,2,02);ICON(53,242,8,4,1,2);PS24(1,62,310,'\xB6\xCB\xBF\xDA',36,0);ICON(70,343,9,3,2,2);ICON(53,360,8,4,1,3);PS24(1,62,428,'\xC9\xE8\xD6\xC3',36,0);ICON(70,460,9,3,2,2);"}; //没有任何选中的完整的dock栏
          MX_dataSize2=strlen_P(MX_ScreenMessage_menuMainInit4);for (MX_dataSize1 = 0; MX_dataSize1 < MX_dataSize2; MX_dataSize1++)
              {MX_sendChar =  pgm_read_byte_near(MX_ScreenMessage_menuMainInit4 + MX_dataSize1);Serial2.print(MX_sendChar);}
        Serial2.println();while(!digitalRead(MX_screenBusy));while(digitalRead(MX_screenBusy));     
    }break;  
    case 1://选中开始
    {    
      const static char MX_ScreenMessage_menuMainStart1[] PROGMEM  = {"CBOF(10,10,163,125,6,35);BOXF(10,109,163,125,35);SBC(35);ICON(53,15,7,4,1,0);PS24(1,62,85,'\xBF\xAA\xCA\xBC',16,0);ICON(70,115,9,3,2,1);"}; //dock栏中，被选中的开始
      MX_dataSize2=strlen_P(MX_ScreenMessage_menuMainStart1);for (MX_dataSize1 = 0; MX_dataSize1 < MX_dataSize2; MX_dataSize1++)
        {MX_sendChar =  pgm_read_byte_near(MX_ScreenMessage_menuMainStart1 + MX_dataSize1);Serial2.print(MX_sendChar);}
      const static char MX_ScreenMessage_menuMainStart2[] PROGMEM  = {"SBC(0);ICON(260,200,10,3,1,0);PS24(1,266,332,'\xD4\xCB\xD0\xD0\xB3\xCC\xD0\xF2',36,0);ICON(439,205,10,3,1,1);PS24(1,445,337,'\xC4\xA3\xD0\xCD\xB7\xB6\xC0\xFD',36,0);ICON(629,200,10,3,1,2);PS24(1,635,332,'\xCA\xB5\xD1\xE9\xC4\xA3\xCA\xBD',36,0);"};//运行程序、模型范例、实验模式
      MX_dataSize2=strlen_P(MX_ScreenMessage_menuMainStart2);for (MX_dataSize1 = 0; MX_dataSize1 < MX_dataSize2; MX_dataSize1++)
        {MX_sendChar =  pgm_read_byte_near(MX_ScreenMessage_menuMainStart2 + MX_dataSize1);Serial2.print(MX_sendChar);}
      const static char MX_ScreenMessage_menuMainStart3[] PROGMEM  = {"BTN(5,260,200,369,359,0);BTN(6,440,200,550,359,0);BTN(7,629,200,738,359,0);"};//按键
      MX_dataSize2=strlen_P(MX_ScreenMessage_menuMainStart3);for (MX_dataSize1 = 0; MX_dataSize1 < MX_dataSize2; MX_dataSize1++)
        {MX_sendChar =  pgm_read_byte_near(MX_ScreenMessage_menuMainStart3 + MX_dataSize1);Serial2.print(MX_sendChar);}
        Serial2.println();while(!digitalRead(MX_screenBusy));while(digitalRead(MX_screenBusy));    
    }break;  
    case 2://选中遥控
    {
      const static char MX_ScreenMessage_menuMainRemote1[] PROGMEM  = {"BOXF(10,125,163,240,35);SBC(35);ICON(53,128,7,4,1,1);PS24(1,62,193,'\xD2\xA3\xBF\xD8',16,0);ICON(70,227,9,3,2,1);"}; //dock栏中，被选中的遥控
      MX_dataSize2=strlen_P(MX_ScreenMessage_menuMainRemote1);for (MX_dataSize1 = 0; MX_dataSize1 < MX_dataSize2; MX_dataSize1++)
        {MX_sendChar =  pgm_read_byte_near(MX_ScreenMessage_menuMainRemote1 + MX_dataSize1);Serial2.print(MX_sendChar);}
      const static char MX_ScreenMessage_menuMainRemote2[] PROGMEM  = {"SBC(0);ICON(237,175,11,3,1,0);PS24(1,255,325,'\xC1\xBD\xC2\xD6\xC7\xFD\xB6\xAF',36,0);ICON(430,175,11,3,1,1);PS24(1,446,325,'\xC8\xFD\xC2\xD6\xC8\xAB\xCF\xF2',36,0);ICON(624,175,11,3,1,2);PS24(1,630,325,'\xD7\xE3\xC7\xF2\xBB\xFA\xC6\xF7\xC8\xCB',36,0);"}; //两轮驱动、三轮全向、足球机器人
      MX_dataSize2=strlen_P(MX_ScreenMessage_menuMainRemote2);for (MX_dataSize1 = 0; MX_dataSize1 < MX_dataSize2; MX_dataSize1++)
        {MX_sendChar =  pgm_read_byte_near(MX_ScreenMessage_menuMainRemote2 + MX_dataSize1);Serial2.print(MX_sendChar);}
      const static char MX_ScreenMessage_menuMainRemote3[] PROGMEM  = {"BTN(5,237,175,367,355,0);BTN(6,430,175,560,355,0);BTN(7,624,175,754,355,0);"}; //按键
      MX_dataSize2=strlen_P(MX_ScreenMessage_menuMainRemote3);for (MX_dataSize1 = 0; MX_dataSize1 < MX_dataSize2; MX_dataSize1++)
        {MX_sendChar =  pgm_read_byte_near(MX_ScreenMessage_menuMainRemote3 + MX_dataSize1);Serial2.print(MX_sendChar);}
      Serial2.println();while(!digitalRead(MX_screenBusy));while(digitalRead(MX_screenBusy));    
    }break;  
    case 3://选中端口
    {
        Serial2.print("CBOF(264,163,739,392,5,0);");//清除中间区域    
        Serial2.println();while(!digitalRead(MX_screenBusy));while(digitalRead(MX_screenBusy));   
        Serial2.print("BOXF(10,240,163,355,35);");
        Serial2.print("SBC(35);ICON(53,242,7,4,1,2);PS24(1,62,310,'\xB6\xCB\xBF\xDA',16,0);ICON(70,343,9,3,2,1);");
        Serial2.print("\r\n");
        while(!digitalRead(MX_screenBusy));
        while(digitalRead(MX_screenBusy));    
    }break;  
    case 4://选中设置
    {
        Serial2.print("CBOF(10,355,163,470,6,35);BOXF(10,355,163,360,35);");
        Serial2.print("SBC(35);ICON(53,360,7,4,1,3);PS24(1,62,428,'\xC9\xE8\xD6\xC3',16,0);ICON(70,460,9,3,2,1);");
        Serial2.print("SBC(0);PS24(1,325,119,'\xC6\xC1\xC4\xBB\xC1\xC1\xB6\xC8',16,2);PL(240,167,790,167,35);PL(750,132,730,117,16);PL(750,132,730,147,16);ICON(255,115,12,4,1,");//屏幕亮度
        if(EEPROM.read(0)<21)Serial2.print("0");//显示亮度
        else if(EEPROM.read(0)<41)Serial2.print("1");
        else if(EEPROM.read(0)<61)Serial2.print("2");
        else Serial2.print("3");
        Serial2.print(");PS24(1,325,192,'\xB4\xA5\xC3\xFE\xD0\xA3\xD7\xBC',16,2);ICON(251,185,13,5,1,2);PL(240,237,790,237,35);PL(750,202,730,187,16);PL(750,202,730,217,16);");//触摸校准
        Serial2.print("PS24(1,325,262,'\xB0\xB4\xBC\xFC\xD2\xF4',16,2);PL(240,307,790,307,35);PL(750,272,730,257,16);PL(750,272,730,287,16);");//按键音
        if(MX_screenButtonBuzzer) Serial2.print("ICON(251,255,13,5,1,0);");
        else Serial2.print("ICON(251,255,13,5,1,1);");
        Serial2.print("PS24(1,325,332,'\xB0\xEF\xD6\xFA',16,2);ICON(251,325,13,5,1,3);PL(240,377,790,377,35);PL(750,342,730,327,16);PL(750,342,730,357,16);");//帮助
        Serial2.print("PS24(1,325,402,'\xB9\xD8\xD3\xDA',16,2);ICON(251,395,13,5,1,4);PL(750,412,730,397,16);PL(750,412,730,427,16);");//关于
        Serial2.print("BTN(5,240,98,790,166,0);BTN(6,240,168,790,236,0);BTN(7,240,238,790,306,0);BTN(8,240,308,790,376,0);BTN(9,240,378,790,446,0);");//设置按键
        Serial2.print("\r\n");
        while(!digitalRead(MX_screenBusy));
        while(digitalRead(MX_screenBusy));    
    }break;  
    
  }
  MX_menuMain_last=MX_menuMain_n;
}
void MX_menuPortInit()
{
              
       Serial2.print("CBOF(264,163,739,392,5,0);");//清除中间区域  
          MX_dataSize2=strlen_P(MX_ScreenMessage_Port1Init);for (MX_dataSize1 = 0; MX_dataSize1 < MX_dataSize2; MX_dataSize1++)//Port 1 未连接
              {MX_sendChar =  pgm_read_byte_near(MX_ScreenMessage_Port1Init + MX_dataSize1);Serial2.print(MX_sendChar);}
           MX_dataSize2=strlen_P(MX_ScreenMessage_Port2Init);for (MX_dataSize1 = 0; MX_dataSize1 < MX_dataSize2; MX_dataSize1++)//Port 2 未连接
              {MX_sendChar =  pgm_read_byte_near(MX_ScreenMessage_Port2Init + MX_dataSize1);Serial2.print(MX_sendChar);}
          MX_dataSize2=strlen_P(MX_ScreenMessage_Port3Init);for (MX_dataSize1 = 0; MX_dataSize1 < MX_dataSize2; MX_dataSize1++)//Port 3 未连接
              {MX_sendChar =  pgm_read_byte_near(MX_ScreenMessage_Port3Init + MX_dataSize1);Serial2.print(MX_sendChar);}
          MX_dataSize2=strlen_P(MX_ScreenMessage_Port4Init);for (MX_dataSize1 = 0; MX_dataSize1 < MX_dataSize2; MX_dataSize1++)//Port 4 未连接
              {MX_sendChar =  pgm_read_byte_near(MX_ScreenMessage_Port4Init + MX_dataSize1);Serial2.print(MX_sendChar);}          
          MX_dataSize2=strlen_P(MX_ScreenMessage_Port5Init);for (MX_dataSize1 = 0; MX_dataSize1 < MX_dataSize2; MX_dataSize1++)//Port 5 未连接
              {MX_sendChar =  pgm_read_byte_near(MX_ScreenMessage_Port5Init + MX_dataSize1);Serial2.print(MX_sendChar);}
          MX_dataSize2=strlen_P(MX_ScreenMessage_Port6Init);for (MX_dataSize1 = 0; MX_dataSize1 < MX_dataSize2; MX_dataSize1++)//Port 6 未连接
              {MX_sendChar =  pgm_read_byte_near(MX_ScreenMessage_Port6Init + MX_dataSize1);Serial2.print(MX_sendChar);}  
          MX_dataSize2=strlen_P(MX_ScreenMessage_PortUSBInit);for (MX_dataSize1 = 0; MX_dataSize1 < MX_dataSize2; MX_dataSize1++)//Port USB 未连接
              {MX_sendChar =  pgm_read_byte_near(MX_ScreenMessage_PortUSBInit + MX_dataSize1);Serial2.print(MX_sendChar);}   
          Serial2.println();while(!digitalRead(MX_screenBusy));while(digitalRead(MX_screenBusy)); 
               
          MX_dataSize2=strlen_P(MX_ScreenMessage_Port7Init);for (MX_dataSize1 = 0; MX_dataSize1 < MX_dataSize2; MX_dataSize1++)//Port 7 未连接
              {MX_sendChar =  pgm_read_byte_near(MX_ScreenMessage_Port7Init + MX_dataSize1);Serial2.print(MX_sendChar);}
           MX_dataSize2=strlen_P(MX_ScreenMessage_Port8Init);for (MX_dataSize1 = 0; MX_dataSize1 < MX_dataSize2; MX_dataSize1++)//Port 8 未连接
              {MX_sendChar =  pgm_read_byte_near(MX_ScreenMessage_Port8Init + MX_dataSize1);Serial2.print(MX_sendChar);}
          MX_dataSize2=strlen_P(MX_ScreenMessage_Port9Init);for (MX_dataSize1 = 0; MX_dataSize1 < MX_dataSize2; MX_dataSize1++)//Port 9 未连接
              {MX_sendChar =  pgm_read_byte_near(MX_ScreenMessage_Port9Init + MX_dataSize1);Serial2.print(MX_sendChar);}
          MX_dataSize2=strlen_P(MX_ScreenMessage_Port10Init);for (MX_dataSize1 = 0; MX_dataSize1 < MX_dataSize2; MX_dataSize1++)//Port 10 未连接
              {MX_sendChar =  pgm_read_byte_near(MX_ScreenMessage_Port10Init + MX_dataSize1);Serial2.print(MX_sendChar);}          
          MX_dataSize2=strlen_P(MX_ScreenMessage_Port11Init);for (MX_dataSize1 = 0; MX_dataSize1 < MX_dataSize2; MX_dataSize1++)//Port 11 未连接
              {MX_sendChar =  pgm_read_byte_near(MX_ScreenMessage_Port11Init + MX_dataSize1);Serial2.print(MX_sendChar);}
          MX_dataSize2=strlen_P(MX_ScreenMessage_Port12Init);for (MX_dataSize1 = 0; MX_dataSize1 < MX_dataSize2; MX_dataSize1++)//Port 12 未连接
              {MX_sendChar =  pgm_read_byte_near(MX_ScreenMessage_Port12Init + MX_dataSize1);Serial2.print(MX_sendChar);}  
        Serial2.println();while(!digitalRead(MX_screenBusy));while(digitalRead(MX_screenBusy));    
  }
MX_Init()
{ 
  Serial.begin(115200);//下载
  Serial1.begin(115200);//端口6
  Serial2.begin(115200);//屏幕
  Serial3.begin(115200);//IO端口
  Serial.println("SN:KOA5F28612A7AD B:115200 RC:854X480 GPU V5.70 B0301 F:C217 H24:1 H32:1 H48:1 GBK16:0 GBK24:0 GBK32:0");
    
  Usb.Init();//初始化USB HOST
  delay(1);
  
  pinMode(MX_digitalIO_1,OUTPUT); 
  pinMode(MX_digitalIO_2,OUTPUT); 
  pinMode(MX_digitalIO_3,OUTPUT); 
  pinMode(MX_digitalIO_4,OUTPUT);
  pinMode(MX_digitalIO_5,OUTPUT); 
  pinMode(MX_digitalIO_6,OUTPUT); 
  pinMode(MX_digitalIO_7,OUTPUT);  
  pinMode(MX_digitalIO_8,OUTPUT);
  pinMode(MX_digitalIO_9,OUTPUT);
  pinMode(MX_digitalIO_10,OUTPUT);  
  pinMode(MX_digitalIO_11,OUTPUT);
  pinMode(MX_digitalIO_12,OUTPUT);
  pinMode(MX_buzzerIO,OUTPUT);
  pinMode(MX_screenBusy,INPUT);
  digitalWrite(MX_buzzerIO,HIGH);
  digitalWrite(MX_digitalIO_1,HIGH);
  digitalWrite(MX_digitalIO_2,HIGH);
  digitalWrite(MX_digitalIO_3,HIGH);
  digitalWrite(MX_digitalIO_4,HIGH);
  digitalWrite(MX_digitalIO_5,HIGH);
  digitalWrite(MX_digitalIO_6,HIGH);
  digitalWrite(MX_digitalIO_7,HIGH);
  digitalWrite(MX_digitalIO_8,HIGH);
  digitalWrite(MX_digitalIO_9,HIGH);
  digitalWrite(MX_digitalIO_10,HIGH);
  digitalWrite(MX_digitalIO_11,HIGH);
  digitalWrite(MX_digitalIO_12,HIGH);
    
  pinMode(14,OUTPUT);//TX3
  pinMode(15,INPUT);//RX3

/*  uchar MX_screen_setcolorN=0;
  for(int MX_screen_setcolorB =255;MX_screen_setcolorB>=0;MX_screen_setcolorB-=127)
{
  for(int MX_screen_setcolorG=255;MX_screen_setcolorG>=0;MX_screen_setcolorG-=127)
  {
    for(int MX_screen_setcolorR=255;MX_screen_setcolorR>=0;MX_screen_setcolorR-=127)
    {
      MX_screenSetColor(MX_screen_setcolorN,MX_screen_setcolorR,MX_screen_setcolorG,MX_screen_setcolorB);
      MX_screen_setcolorN++;
    }
  }
}
  MX_screenSetColor(29,220,220,220);
  MX_screenSetColor(28,180,180,180);
  MX_screenSetColor(27,140,140,140); 
  MX_screenCLS(26);  
  MX_screenBackColor(26);
Serial2.println("PIC(320,150,13);");//显示系统logo
while(!digitalRead(MX_screenBusy));
while(digitalRead(MX_screenBusy));	*/

MX_screenButtonBuzzer=EEPROM.read(1);//设置按键音
if(EEPROM.read(0)==0)EEPROM.write(0,80);//防止EEPROM数据初值等于0
MX_screenLum(EEPROM.read(0));//设置亮度

Serial2.println("STDM;");//关闭系统演示
while(!digitalRead(MX_screenBusy));
while(digitalRead(MX_screenBusy));	
MX_screenTouchMode(GetButton);
//停止所有电机
    MX_motorControl(1,22,0,0);
    MX_motorControl(2,22,0,0);
    MX_motorControl(3,22,0,0);
    MX_motorControl(4,22,0,0);
    MX_motorControl(5,22,0,0);
    MX_motorControl(6,20,0,0);
    MX_motorControl(7,22,0,0);
    MX_motorControl(8,22,0,0);
    MX_motorControl(9,22,0,0);
    MX_motorControl(10,22,0,0);
    MX_motorControl(11,22,0,0);
    MX_motorControl(12,22,0,0);
    MX_menuMain(0);
while(MX_screenMenuLoop)
{
  switch(MX_screenMenuNum)
  {
     case 1://开始
     {  MX_screenMenuLoop2=1;
        MX_menuMain(1);
        while(MX_screenMenuLoop2)
        { MX_screenBatteryV();//刷新时间及电量显示
          if(MX_screenGetButton())
          {
            if(MX_screenButtonN<5 && MX_screenButtonN!=1)
            {
              MX_screenMenuNum=MX_screenButtonN; 
              MX_screenMenuLoop2=0;
            }
            else if(MX_screenButtonN==5)
            {MX_screenMenuLoop=MX_screenMenuLoop2=0;}
          }
        }  
      }break; 
     case 2://遥控
     {  MX_screenMenuLoop2=1;
        MX_menuMain(2);
        while(MX_screenMenuLoop2)
        {
          MX_screenBatteryV();//刷新时间及电量显示
          if(MX_screenGetButton())
          {
            if(MX_screenButtonN<5 && MX_screenButtonN!=2)
            {
              MX_screenMenuNum=MX_screenButtonN;
              MX_screenMenuLoop2=0;
            }    
            else if(MX_screenButtonN==5)
            { MX_example2Wheel();}
            else if(MX_screenButtonN==6)
            {MX_example3wheels();}
            else if(MX_screenButtonN==7)
            {MX_exampleFootball();}
          }
        }   
      }break; 
     case 3://端口
     {  MX_screenMenuLoop2=1;
        MX_menuMain(3); 
        MX_menuPortInit();
        while(MX_screenMenuLoop2)
        {
          MX_screenBatteryV();//刷新时间及电量显示
          if(MX_screenGetButton() || MX_PortView_turnOff)//如果识别到按键则执行对应内容。如果是刚从手柄预览界面跳出
          { MX_PortView_turnOff=0;
            if(MX_screenButtonN<5 && MX_screenButtonN!=3)
            {
              MX_screenMenuNum=MX_screenButtonN;
              MX_screenMenuLoop2=0;
            }
            else if(MX_screenButtonN==17)//Port USB
            {
                MX_dataSize2=strlen_P(MX_ScreenMessage_PortUSBLightup);for (MX_dataSize1 = 0; MX_dataSize1 < MX_dataSize2; MX_dataSize1++)//USB高亮
                {MX_sendChar =  pgm_read_byte_near(MX_ScreenMessage_PortUSBLightup + MX_dataSize1);Serial2.print(MX_sendChar);}
                MX_menuGamePad();MX_PortView_turnOff=1;//执行手柄查看界面，查看完毕后置跳出预览界面位
                MX_menuPortInit();//初始化按键高亮
            }
            else
            {
              switch(MX_screenButtonN-4)//显示高亮
              {
                case 1:{MX_dataSize2=strlen_P(MX_ScreenMessage_Port1Lightup);for (MX_dataSize1 = 0; MX_dataSize1 < MX_dataSize2; MX_dataSize1++){MX_sendChar =  pgm_read_byte_near(MX_ScreenMessage_Port1Lightup + MX_dataSize1);Serial2.print(MX_sendChar);}}break;  
                case 2:{MX_dataSize2=strlen_P(MX_ScreenMessage_Port2Lightup);for (MX_dataSize1 = 0; MX_dataSize1 < MX_dataSize2; MX_dataSize1++){MX_sendChar =  pgm_read_byte_near(MX_ScreenMessage_Port2Lightup + MX_dataSize1);Serial2.print(MX_sendChar);}}break;  
                case 3:{MX_dataSize2=strlen_P(MX_ScreenMessage_Port3Lightup);for (MX_dataSize1 = 0; MX_dataSize1 < MX_dataSize2; MX_dataSize1++){MX_sendChar =  pgm_read_byte_near(MX_ScreenMessage_Port3Lightup + MX_dataSize1);Serial2.print(MX_sendChar);}}break;  
                case 4:{MX_dataSize2=strlen_P(MX_ScreenMessage_Port4Lightup);for (MX_dataSize1 = 0; MX_dataSize1 < MX_dataSize2; MX_dataSize1++){MX_sendChar =  pgm_read_byte_near(MX_ScreenMessage_Port4Lightup + MX_dataSize1);Serial2.print(MX_sendChar);}}break;  
                case 5:{MX_dataSize2=strlen_P(MX_ScreenMessage_Port5Lightup);for (MX_dataSize1 = 0; MX_dataSize1 < MX_dataSize2; MX_dataSize1++){MX_sendChar =  pgm_read_byte_near(MX_ScreenMessage_Port5Lightup + MX_dataSize1);Serial2.print(MX_sendChar);}}break;  
                case 6:{MX_dataSize2=strlen_P(MX_ScreenMessage_Port6Lightup);for (MX_dataSize1 = 0; MX_dataSize1 < MX_dataSize2; MX_dataSize1++){MX_sendChar =  pgm_read_byte_near(MX_ScreenMessage_Port6Lightup + MX_dataSize1);Serial2.print(MX_sendChar);}}break;  
                case 7:{MX_dataSize2=strlen_P(MX_ScreenMessage_Port7Lightup);for (MX_dataSize1 = 0; MX_dataSize1 < MX_dataSize2; MX_dataSize1++){MX_sendChar =  pgm_read_byte_near(MX_ScreenMessage_Port7Lightup + MX_dataSize1);Serial2.print(MX_sendChar);}}break;  
                case 8:{MX_dataSize2=strlen_P(MX_ScreenMessage_Port8Lightup);for (MX_dataSize1 = 0; MX_dataSize1 < MX_dataSize2; MX_dataSize1++){MX_sendChar =  pgm_read_byte_near(MX_ScreenMessage_Port8Lightup + MX_dataSize1);Serial2.print(MX_sendChar);}}break;  
                case 9:{MX_dataSize2=strlen_P(MX_ScreenMessage_Port9Lightup);for (MX_dataSize1 = 0; MX_dataSize1 < MX_dataSize2; MX_dataSize1++){MX_sendChar =  pgm_read_byte_near(MX_ScreenMessage_Port9Lightup + MX_dataSize1);Serial2.print(MX_sendChar);}}break;  
                case 10:{MX_dataSize2=strlen_P(MX_ScreenMessage_Port10Lightup);for (MX_dataSize1 = 0; MX_dataSize1 < MX_dataSize2; MX_dataSize1++){MX_sendChar =  pgm_read_byte_near(MX_ScreenMessage_Port10Lightup + MX_dataSize1);Serial2.print(MX_sendChar);}}break;  
                case 11:{MX_dataSize2=strlen_P(MX_ScreenMessage_Port11Lightup);for (MX_dataSize1 = 0; MX_dataSize1 < MX_dataSize2; MX_dataSize1++){MX_sendChar =  pgm_read_byte_near(MX_ScreenMessage_Port11Lightup + MX_dataSize1);Serial2.print(MX_sendChar);}}break;  
                case 12:{MX_dataSize2=strlen_P(MX_ScreenMessage_Port12Lightup);for (MX_dataSize1 = 0; MX_dataSize1 < MX_dataSize2; MX_dataSize1++){MX_sendChar =  pgm_read_byte_near(MX_ScreenMessage_Port12Lightup + MX_dataSize1);Serial2.print(MX_sendChar);}}break;                  
              }
              Serial2.print("SBC(0);PS24(1,380,250,'\xD5\xFD\xD4\xDA\xCB\xD1\xCB\xF7\xC9\xE8\xB1\xB8...',16,0);");//正在搜索设备...
              Serial2.println();while(!digitalRead(MX_screenBusy));while(digitalRead(MX_screenBusy));
              MX_PortView_turnOff=1;
              while(!MX_screenGetButton() && MX_PortView_turnOff)
              {  
                if(MX_hardwareInfo(MX_screenButtonN-4))
                  MX_PortView_turnOff=0;
              }
              if(!MX_PortView_turnOff)//MX_PortView_turnOff==0,证明刚才检测到设备
              {
                if(MX_IDcode==1)//如果设备号是1，则运行查看电机
                {      
                  Serial2.print("SBC(0);PS24(1,400,178,'V");Serial2.print(MX_version_h);Serial2.print(".");Serial2.print(MX_version_l);Serial2.print("',16,0);"); 
                  MX_menuPortView_motor(MX_screenButtonN-4);
                }
              } 
              MX_menuPortInit();            
            }
          }
        }    
      }break; 
     case 4://设置
     {
        MX_screenMenuLoop2=1;
        MX_menuMain(4);
        while(MX_screenMenuLoop2)
        {
          MX_screenBatteryV();//刷新时间及电量显示
          if(MX_screenGetButton())//如果有按键按下
          {
            if(MX_screenButtonN<5 && MX_screenButtonN!=4)//按下dock栏按键
            {
              MX_screenMenuNum=MX_screenButtonN;
              MX_screenMenuLoop2=0;
            }    
            switch(MX_screenButtonN)//按下其他按键
            {
              case 5://屏幕亮度
              {
                if(EEPROM.read(0)<21)
                {EEPROM.write(0,40);MX_screenLum(40);Serial2.println("ICON(255,115,12,4,1,1);");}
                else if(EEPROM.read(0)<41)
                {EEPROM.write(0,60);MX_screenLum(60);Serial2.println("ICON(255,115,12,4,1,2);");}
                else if(EEPROM.read(0)<61)
                {EEPROM.write(0,80);MX_screenLum(80);Serial2.println("ICON(255,115,12,4,1,3);");}
                else
                {EEPROM.write(0,20);MX_screenLum(20);Serial2.println("ICON(255,115,12,4,1,0);");}
                while(!digitalRead(MX_screenBusy));
                while(digitalRead(MX_screenBusy));  
              }break; 
              case 6://触摸校准
              { 
                Serial2.print("SBC(35);CBOF(399,199,602,342,5,34);CBOF(400,200,600,340,5,35);PS24(1,420,225,'\xD6\xB4\xD0\xD0\xB4\xA5\xC3\xFE\xD0\xA3\xD7\xBC\xA3\xBF',36,2);");//执行触摸校准？
                Serial2.print("BTN(7,420,275,480,315,2,0);PS24(1,438,283,'\xCA\xC7',36,2);BTN(8,515,275,575,315,2,0);PS24(1,533,283,'\xB7\xF1',36,2);");//是 否
                Serial2.print("\r\n");
                while(!digitalRead(MX_screenBusy));
                while(digitalRead(MX_screenBusy)); 
                MX_screenMenuLoop3=1;
                while(MX_screenMenuLoop3)
                { MX_screenBatteryV();//刷新时间及电量显示
                  if(MX_screenGetButton())//如果有按键按下
                  {
                    if(MX_screenButtonN==8)//如果按下否，则返回设置菜单
                    {
                        MX_screenMenuNum=4;MX_screenMenuLoop3=0;MX_screenMenuLoop2=0;
                    }
                    else if(MX_screenButtonN==7)//如果按下否，则返回设置菜单
                    {
                        MX_screenCLS(0);
                        MX_screenCalibration();delay(50);
                        while(Serial2.read()>=0);
                        while((Serial2.available()<1));//等待再一次有触摸反馈
                        MX_menuMain(0);//初始化菜单显示
                        MX_screenMenuNum=4;MX_screenMenuLoop3=0;MX_screenMenuLoop2=0;//显示到设置页面
                    }
                  }   
                }
              }break; 
              case 7://按键音
              {
                if(MX_screenButtonBuzzer)
                {
                  MX_screenButtonBuzzer=0;EEPROM.write(1,0);//设置按键音
                  Serial2.print("ICON(251,255,13,5,1,1);");
                }
                else
                {
                  MX_screenButtonBuzzer=1;EEPROM.write(1,1);//设置按键音
                  Serial2.print("ICON(251,255,13,5,1,0);");                    
                }
                Serial2.print("\r\n");while(!digitalRead(MX_screenBusy));while(digitalRead(MX_screenBusy)); 
              }break; 
              case 8://帮助
              {
                Serial2.print("BOXF(240,98,790,446,0);");//清空设置区内容
                Serial2.print("SBC(0);DS32(240,143,'\xB0\xEF\xD6\xFA\xCE\xC4\xB5\xB5\xBC\xB0\xCF\xE0\xB9\xD8\xC8\xED\xBC\xFE\xCF\xC2\xD4\xD8\xB5\xD8\xD6\xB7\xA3\xBA',16,0);DS32(240,194,'http://download.semia.com',16,0);MKQR(240,250,16,6,'http://download.semia.com');");//帮助内容               
                Serial2.print("BTN(5,0,0,1,0,0,0);BTN(6,0,0,1,0,0,0);BTN(7,0,0,1,0,0,0);BTN(8,0,0,1,0,0,0);BTN(9,0,0,1,0,0,0);");//清除按键
                Serial2.print("\r\n");while(!digitalRead(MX_screenBusy));while(digitalRead(MX_screenBusy));                 
                delay(50);while(Serial2.read()>=0);
                while((Serial2.available()<4));//等待再一次有触摸反馈
                if(MX_screenButtonBuzzer==1)//播放按键音
                {
                  digitalWrite(MX_buzzerIO,0);
                  delay(1);digitalWrite(MX_buzzerIO,1);
                }
                delay(200);while(Serial2.read()>=0);
                MX_screenMenuNum=4;MX_screenMenuLoop2=0;//显示到设置页面
              }break;
              case 9://关于
              {
                Serial2.print("BOXF(240,98,790,446,0);");//清空设置区内容
                Serial2.print("SBC(0);DS32(240,143,'MX-900\xBD\xF0\xCA\xF4\xBB\xFA\xC6\xF7\xC8\xCB\xCC\xD7\xD7\xB0 V1.0',16,0);DS24(240,205,'\xD2\xE2\xBC\xFB\xB7\xB4\xC0\xA1\xA3\xBAliuhao@semia.com',16,0);PIC(240,260,1);");//关于内容               
                Serial2.print("BTN(5,0,0,1,0,0,0);BTN(6,0,0,1,0,0,0);BTN(7,0,0,1,0,0,0);BTN(8,0,0,1,0,0,0);BTN(9,0,0,1,0,0,0);");//清除按键
                Serial2.print("\r\n");while(!digitalRead(MX_screenBusy));while(digitalRead(MX_screenBusy));                 
                delay(50);while(Serial2.read()>=0);
                while((Serial2.available()<4));//等待再一次有触摸反馈
                if(MX_screenButtonBuzzer==1)//播放按键音
                {
                  digitalWrite(MX_buzzerIO,0);
                  delay(1);digitalWrite(MX_buzzerIO,1);
                }
                delay(200);while(Serial2.read()>=0);
                MX_screenMenuNum=4;MX_screenMenuLoop2=0;//显示到设置页面
              }break;
                            
            }
          }
        }    
      }break; 
      
  }    
}
  Serial2.print("CLS();AGIF(0,370,180,14,28,1,1);PS24(1,362,280,'\xD4\xCB\xD0\xD0\xD6\xD0...',16,0);");//运行中...
  Serial2.println();while(!digitalRead(MX_screenBusy));while(digitalRead(MX_screenBusy)); 
}
#endif



