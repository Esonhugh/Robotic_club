#include <MATRIX.h>
void MX_R(int port,int speedrun){
MX_motorController(port,10,speedrun,0);
}
int AM=12;
int BM=1;
int LM=7;
int RM=6;
int speed1 = 25;
//如果左边正转为前进 则右轮为后退，前轮为右，后轮为左
void qian(){
MX_R(AM,0);
MX_R(BM,0);
MX_R(LM,speed1);
MX_R(RM,-speed1);
}
void hou(){
MX_R(AM,0);
MX_R(BM,0);
MX_R(LM,-speed1);
MX_R(RM,speed1);
}
void zuo(){
MX_R(AM,-speed1);
MX_R(BM,speed1);
MX_R(LM,0);
MX_R(RM,0);
}
void you(){
MX_R(AM,speed1);
MX_R(BM,-speed1);
MX_R(LM,0);
MX_R(RM,0);
}
void shunshizheng(){
MX_R(AM,speed1);
MX_R(BM,speed1);
MX_R(LM,speed1);
MX_R(RM,speed1);
}
void nishizheng() {
MX_R(AM,-speed1);
MX_R(BM,-speed1);
MX_R(LM,-speed1);
MX_R(RM,-speed1);
}
void stopmotor(){
MX_R(AM,0);
MX_R(BM,0);
MX_R(LM,0);
MX_R(RM,0);
MX_motorControl(AM,22,0,0);
MX_motorControl(BM,22,0,0);
MX_motorControl(LM,22,0,0);
MX_motorControl(RM,22,0,0);
}
void all_directions(){
MX_R(LM,MX_gamepadLeftY*0.5);
MX_R(RM,MX_gamepadLeftY*-0.5);
MX_R(AM,MX_gamepadLeftX*-0.5);
MX_R(BM,MX_gamepadLeftX*0.5);
}
int getgamepadinput(){
int code = 0;
int defend =0;
int codeout = code;
if (MX_gamepadPress(LEFT)){
code = 1;
defend =code +1;
}
if (MX_gamepadPress(RIGHT)){
code =2;
}
if (MX_gamepadPress(UP)){
code =3;
defend =code +1;
}
if (MX_gamepadPress(DOWN)){
code =4;
}
if (MX_gamepadPress(L1)){
code =5;
defend =code +1;
}
if (MX_gamepadPress(R1)){
code =6;
}
if (MX_gamepadPress(UP) and MX_gamepadPress(LEFT)){
code =7;
defend =code +1;
}
if (MX_gamepadPress(UP) and MX_gamepadPress(RIGHT)){
code =8;
}
if (MX_gamepadPress(DOWN) and MX_gamepadPress(LEFT)){
code =9;
defend =code +1;
}
if (MX_gamepadPress(DOWN) and MX_gamepadPress(RIGHT)){
code =10;
}
if (code == defend){
code =0;
}
codeout = code;
code =0;
return (codeout);
}
}
void process(int codedo){
  switch (codedo){
    case 0:
	  stopmotor();
      break;   
    case 1:
      zuo();
      break;
    case 2:
      you();
      break;
    case 3:
      qian();
      break;
    case 4:
      hou();
      break;
    case 5:
      nishizheng();
      break;
    case 6:
      shunshizheng();
      break;
    default:
	  stopmotor();
      break;
      }
}
void robort_action(){
	process(getgamepadinput(););
}