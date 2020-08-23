#include <MATRIX.h>

// 速度初始定义 端口定义 am 后轮 bm 前轮 lm左轮 rm右轮
int AM=12; 
int BM=1;
int LM=7;
int RM=6;
int speed1 = 60;//实际执行速度
int speed = 60; //默认速度
int condition_before;


void MX_R(int port,int speedrun){
    MX_motorControl(port,10,speedrun,0);
}

void qian(){
MX_R(AM,0);
MX_R(BM,0);
MX_R(LM,speed1);
MX_R(RM,-speed1);
}
//前进

void hou(){
MX_R(AM,0);
MX_R(BM,0);
MX_R(LM,-speed1);
MX_R(RM,speed1);
}
//后退

void zuo(){
MX_R(AM,speed1);
MX_R(BM,-speed1);
MX_R(LM,0);
MX_R(RM,0);
}
//左平移

void you(){
MX_R(AM,-speed1);
MX_R(BM,speed1);
MX_R(LM,0);
MX_R(RM,0);
}
//右平移

void qianzuo(){
MX_R(AM,speed1);
MX_R(BM,-speed1);
MX_R(LM,speed1);
MX_R(RM,-speed1);
}
//前左平移

void qianyou(){
MX_R(AM,-speed1);
MX_R(BM,speed1);
MX_R(LM,speed1);
MX_R(RM,-speed1);
}
//前右平移

void houzuo(){
MX_R(AM,speed1);
MX_R(BM,-speed1);
MX_R(LM,-speed1);
MX_R(RM,speed1);
}
//后左平移

void houyou(){
MX_R(AM,-speed1);
MX_R(BM,speed1);
MX_R(LM,-speed1);
MX_R(RM,speed1);
}
//后右平移

void shunshizheng(){
MX_R(AM,speed1);
MX_R(BM,speed1);
MX_R(LM,speed1);
MX_R(RM,speed1);
}
//顺时针转动

void nishizheng() {
MX_R(AM,-speed1);
MX_R(BM,-speed1);
MX_R(LM,-speed1);
MX_R(RM,-speed1);
}
//逆时针转动

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
//强行停止电机





void all_directions(){
MX_R(LM,MX_gamepadLeftY*0.5*1);
MX_R(RM,MX_gamepadLeftY*-0.5*1);
MX_R(AM,MX_gamepadLeftX*-0.5*1);
MX_R(BM,MX_gamepadLeftX*0.5*1);
}

int getgamepadinput(){
int code = 0;
int defend =0;
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
code = 0;
}
return (code);
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
    case 7:
    qianzuo();
    break;
    case 8:
    qianyou();
    break;
    case 9:
    houzuo();
    break;
    case 10:
    houyou();
    break;
    default:
    break;
    }
}

void function_choice(){
int chosen_number = 0;

                if (MX_gamepadPress(B)) {
                   chosen_number =1;
                 }
                else if(MX_gamepadPress(A)){
                   chosen_number =2;
                 }
                if (MX_gamepadPress(X)) {
                  chosen_number =3;
                 }
                if (MX_gamepadPress(Y)){
                  chosen_number =4;
                }

switch(chosen_number){
  case 1:action();break;
  case 2:all_directions();break;
  case 3:stopmotor();break;
  case 4:MX_motorControl(AM,21,0,0);MX_motorControl(BM,21,0,0);MX_motorControl(RM,21,0,0);MX_motorControl(LM,21,0,0);break;
  default: break;
}
}

void action(){
int docode = getgamepadinput();
if(docode != condition_before){
	speed1 = 100;
}
process(docode);

condition_before = docode;
speed1 = speed;
}