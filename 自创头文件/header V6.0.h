#include <MATRIX.h>
//定义头文件 比赛专用

void MX_R(int port,int speedrun){
MX_motorControl(port,10,speedrun,0);
}
//定义电机速度函数 为了缩减使用代码

int AM=12;
int BM=1;
int LM=7;
int RM=6;
int speed1 = 50;
int speed_first = 50;
bool LM_direction1 = true; //如果左轮正转为前进 为true
// 速度初始定义 端口定义 am 后轮 bm 前轮 lm左轮 rm右轮

void setting(int BM1,int AM1,int LM1,int RM1,bool LM_direction,int speedpower){
AM=AM1;
BM=BM1;
LM=LM1;
RM=RM1;
if (LM_direction == false){	
speedpower = -speedpower;
LM_direction1 = false;
}
speed1=speedpower;
}
//修改参数函数  

void turning(){
int a =11;
if (MX_gamepadPress(L1)){
a = 5;
defenda=a+1;
}
if (MX_gamepadPress(R1)){
a =6;
}
if (a == defenda){
a = 0;
}
process(a);
}
//独立出来的转向模块

void freshspeed(){
int speed0 = speed_first;
if (MX_gamepadPress(L2) != 0 or MX_gamepadPress(R2) != 0){
	if (MX_gamepadPress(L2) != 0 and MX_gamepadPress(R2) == 0){
		speed0 = MX_gamepadPress(L2);
	}
	if (MX_gamepadPress(R2) != 0 and MX_gamepadPress(L2) == 0){
		speed0 = MX_gamepadPress(R2);
	}
	if (MX_gamepadPress(L2) != 0 and MX_gamepadPress(R2) != 0){
		speed0 = ( MX_gamepadPress(R2) + MX_gamepadPress(L2) )*0.5
	}
}
if (LM_direction1 == false){
	speed0 = -speed0;
}
speed1 = speed0;
}
//刷新电机默认速度

//如果左边正转为前进 则右轮为后退，前轮为右，后轮为左

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

void all_directions(int k=1){
	if (LM_direction1 == false){
		k=-1;
	}
MX_R(LM,MX_gamepadLeftY*0.5*k);
MX_R(RM,MX_gamepadLeftY*-0.5*k);
MX_R(AM,MX_gamepadLeftX*-0.5*k);
MX_R(BM,MX_gamepadLeftX*0.5*k);
}
//全向移动代码

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
//获取手柄输入情况

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
//执行情况

void robort_action(){
  process(getgamepadinput());
}
//自动