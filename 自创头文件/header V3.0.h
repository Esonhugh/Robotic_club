#include <MATRIX.h>

int left1 = 1;
int right1 = 2;
int left2 = 7;
int right2 = 8;
int speed1 = 50;
int speed2 = 75;

void port_define(int left_before,int left_after,int right_before,int right_after){
	left1 = left_before;
	left2 = left_after;
	right1 = right_before;
	right2 = right_after;
}

void speedmode(int fastspeed,int lowspeed){
	speed1 = fastspeed;
	speed2 = lowspeed;
}

//函数板块 MX_motor 第一个是端口号 第二个是速度大小
  void MX_motor(int port, int MX_V) {
    if (port == right1 or port == right2) {
      MX_V = -MX_V;
      //将右侧轮胎速度变为负值
    }
    MX_motorControl(port, 10, MX_V, 0);
  }
  
  
  //函数的速度转换模块
  int MX_speed(int outsideport,int outsidespeed){
	  if (outsideport == right1 or outsideport ==right2){
		  outsidespeed == -outsidespeed;
	  }
	  return (outsidespeed);
  }
  
  
  void stopmotor(){
	  MX_motor(left1, 0);
      MX_motor(right2, 0);
      MX_motor(left2, 0);
      MX_motor(right1, 0);
      MX_motorControl(left1, 22, 0, 0);
      MX_motorControl(right2, 22, 0, 0);
      MX_motorControl(left2, 22, 0, 0);
      MX_motorControl(right1, 22, 0, 0);
  }
  //转向模块
  void turnright() {
    MX_motor(left1, speed1);
    MX_motor(left2, speed1);
    MX_motor(right1, -speed1);
    MX_motor(right2, -speed1);
  }
  void turnleft() {
    MX_motor(left1, -speed1);
    MX_motor(left2, -speed1);
    MX_motor(right1, speed1);
    MX_motor(right2, speed1);
  }
  
  //平移模块
  void slideleft() {
    MX_motor(left1, -speed1);
    MX_motor(left2, speed1);
    MX_motor(right1, speed1);
    MX_motor(right2, -speed1);
  }
  void slideright() {
    MX_motor(left1, speed1);
    MX_motor(left2, -speed1);
    MX_motor(right1, -speed1);
    MX_motor(right2, speed1);
  }
  
  //前后移动模块
  void ahead() {
    MX_motor(left1, speed2);
    MX_motor(left2, speed2);
    MX_motor(right1, speed2);
    MX_motor(right2, speed2);
  }
  void back() {
    MX_motor(left1, -speed2);
    MX_motor(left2, -speed2);
    MX_motor(right1, -speed2);
    MX_motor(right2, -speed2);
  }
  //前左右和后左右平移模块
void slideleftbefore(){
	MX_motor(left1,0);
	MX_motor(right1,speed2);
	MX_motor(left2,speed2);
	MX_motor(right2,0);
}
 void sliderightbefore(){
	MX_motor(left1,speed2);
	MX_motor(right1,0);
	MX_motor(left2,0);
	MX_motor(right2,speed2);
} 
  void slideleftafter(){
	MX_motor(left1,-speed2);
	MX_motor(right1,0);
	MX_motor(left2,0);
	MX_motor(right2,-speeed2);
}
void sliderightafter(){
	MX_motor(left1,0);
	MX_motor(right1,-speed2);
	MX_motor(left2,-speed2);
	MX_motor(right2,0);
}
  
  
  //获取输入回复指令值
 int getinput(){
		int code1 = 0;
		int code = 0;
		int against = 0;
		if (MX_gamepadPress(LEFT)) {
			code = 1;
			against = 2;
		}
		if (MX_gamepadPress(RIGHT)) {
			code = 2;
		}
		if (MX_gamepadPress(UP)) {
			code = 3;
			against = 4;
		}
		if (MX_gamepadPress(DOWN)) {
			code = 4;
		}
		if (MX_gamepadPress(X)) {
			code = 5;
			against = 6;
		}
		if (MX_gamepadPress(Y)) {
			code = 6;
		}
		
		//平移方向加前后
		if  ( (MX_gamepadPress(X)) and (MX_gamepadPress(UP)) ) {
			code = 7; //左前
		}
		if  ( (MX_gamepadPress(Y)) and (MX_gamepadPress(UP)) ) {
			code = 8;  //右前
		}
		if  ( (MX_gamepadPress(X)) and (MX_gamepadPress(DOWN)) )  {
			code = 9;  //左后
		}
		if  ( (MX_gamepadPress(Y)) and (MX_gamepadPress(DOWN)) ) {
			code = 10;  //右后
		}

		if (code == against){
			code = 0;
		}
		
  return (code);
}
  
  
  void processWithCode(int code1){
	switch (code1){
    case 0:
      MX_motor(left1, 0);
      MX_motor(right2, 0);
      MX_motor(left2, 0);
      MX_motor(right1, 0);
      MX_motorControl(left1, 22, 0, 0);
      MX_motorControl(right2, 22, 0, 0);
      MX_motorControl(left2, 22, 0, 0);
      MX_motorControl(right1, 22, 0, 0);
	  stopmotor();
      break;
      
    case 1:
      turnleft();
      break;

    case 2:
      turnright();
      break;

    case 3:
      ahead();
      break;

    case 4:
      back();
      break;

    case 5:
      slideleft();
      break;

    case 6:
      slideright();
      break;
	
	
	case 7:
	  slideleftbefore();
	  break;
	  
	case 8:
	  sliderightbefore()
	  break;
	  
	case 9:
	  slideleftafter():
	  break:
	  
	case 10:
	  sliderightafter();
	  break;
	 
	  
    default:
    MX_motor(left1, 0);
    MX_motor(left2, 0);
    MX_motor(right1, 0);
    MX_motor(right2, 0);
    MX_motorControl(right1,22,0,0);
    MX_motorControl(left1,22,0,0);
    MX_motorControl(right2,22,0,0);
    MX_motorControl(left2,22,0,0);
	stopmotor();
      break;
      }
	  
  }
  
  
  //代理处理模块 需要前面大部分函数的支持
void process() {
  int code1 = 0;
  int code = 0;
  int against = 0;
  if (MX_gamepadPress(LEFT)) {
    code = 1;
    against = 2;
  }
  if (MX_gamepadPress(RIGHT)) {
    code = 2;
  }
  if (MX_gamepadPress(UP)) {
    code = 3;
    against = 4;
  }
  if (MX_gamepadPress(DOWN)) {
    code = 4;
  }
  if (MX_gamepadPress(X)) {
    code = 5;
    against = 6;
  }
  if (MX_gamepadPress(Y)) {
    code = 6;
  }
//平移方向加前后
		if  ( (MX_gamepadPress(X)) and (MX_gamepadPress(UP)) ) {
			code = 7; //左前
		}
		if  ( (MX_gamepadPress(Y)) and (MX_gamepadPress(UP)) ) {
			code = 8;  //右前
		}
		if  ( (MX_gamepadPress(X)) and (MX_gamepadPress(DOWN)) )  {
			code = 9;  //左后
		}
		if  ( (MX_gamepadPress(Y)) and (MX_gamepadPress(DOWN)) ) {
			code = 10;  //右后
		}
		
  code1 = code;
  //传递参数指令
  if (code == against) {
    code1 = 0;
  }
  
  switch (code1){
    case 0:
      MX_motor(left1, 0);
      MX_motor(right2, 0);
      MX_motor(left2, 0);
      MX_motor(right1, 0);
      MX_motorControl(left1, 22, 0, 0);
      MX_motorControl(right2, 22, 0, 0);
      MX_motorControl(left2, 22, 0, 0);
      MX_motorControl(right1, 22, 0, 0);
	  stopmotor();
      break;
      
    case 1:
      turnleft();
      break;

    case 2:
      turnright();
      break;

    case 3:
      ahead();
      break;

    case 4:
      back();
      break;

    case 5:
      slideleft();
      break;

    case 6:
      slideright();
      break;
	
	
	case 7:
	  slideleftbefore();
	  break;
	  
	case 8:
	  sliderightbefore()
	  break;
	  
	case 9:
	  slideleftafter():
	  break:
	  
	case 10:
	  sliderightafter();
	  break;
	 
	  
    default:
    MX_motor(left1, 0);
    MX_motor(left2, 0);
    MX_motor(right1, 0);
    MX_motor(right2, 0);
    MX_motorControl(right1,22,0,0);
    MX_motorControl(left1,22,0,0);
    MX_motorControl(right2,22,0,0);
    MX_motorControl(left2,22,0,0);
	stopmotor();
      break;
      }
}