#include "Robot.h"
#include <pthread.h>

//===============================================================
//执行器模块
// 1、电机速度
void SetMotor(int nPort, int nSpeed)
{
}
// 2、电机时间
void SetMotorTime(int nPort, int nSpeed, int nTime)
{
}
// 3、电机角度
void SetMotorEncoder(int nPort, int nSpeed,int nEncoder)
{
}
// 舵机控制
void SetServo(int nID, int nSpeed, int nAngle)
{
}
// 智能灯
void SmartLed(int nPort, int mModel, int nCycle, int nR, int nG, int nB)
{
}
// 4、数字输出
void SetDO(int nPort, int nEnable)
{
}
// 5、扬声器
void Play(char * mFileName)
{
}
//6、扬声器直到播放完毕
void PlayUntil(char * mFileName)
{
}
//7、延时
void Wait(float nTime)
{
}
//8、清除显示
void Clear()
{
}
//9、存储数据
void SetEE(int addressId,int value)
{
}
//10、读取数据
int GetEE(int addressId)
{
	return 0;
}
//11、拍照
void Camera(int pictureId)
{
}
//12、录音
void GetMicrophone(int recordId,int time)
{
}
//13、麦克风声音强度
int GetMic(){return 0;}
// 显示表情
void PrintfExpression(char *expression)
{
}

//传感器模块
//地面灰度、红外测距、超声测距、光敏、温度、读取模拟通道
int GetAI(int nPort)
{
	return 0;
}
int GetGray(int nPort)
{
	return 0;
}//灰度
int GetChannelGray(int nPort,int mChannel)
{
	return 0;
}
int CheckKey(int nkey)
{
	return 0;
}
int GetTouch(int nPort)
{
	return 0;
} //触碰
int GetUltraSonic(int nPort)
{
	return 0;
}//超声
int GetFlame(int nPort)
{
	return 0;
}//火焰
int GetTemperature(int nPort)
{
	return 0;
}//温度
int GetMagnet(int nPort)
{
	return 0;
}//磁敏
int GetLight(int nPort)
{
	return 0;
}//光敏
int GetHumidity(int nPort)
{
	return 0;
}//湿度
int GetInfrared(int nPort)
{
	return 0;
}//红外
int GetAngle(int nPort)
{
	return 0;
}//角度
int GetColor(int nPort)
{
	return 0;
}//颜色
//电量百分比
int GetBattery()
{
	return 0;
}
//复位运动传感器
void ResetMotionSensor()
{
}
//获取运动传感器
int GetMotionSensor(int nType,int nAxis)
{
	return 0;
}

//复位电机编码器
void ResetEncoder(int encoderId)
{
}
//获取电机编码器
int GetInstantEncoder(int encoderId)
{
	return 0;
}
//获取电机编码器
int GetEncoder(int encoderId)
{
	return 0;
}
//复位定时器
void ResetTimer(int timerId)
{
}
//获取定时器
int GetTimerMS(int timerId)
{
	return 0;
}

//设置发送指令
void setSendCmd(int cmd, int index, int value)
{
}
//获取发送指令
int getSendCmd(int cmd, int index)
{
	return 0;
}
//获取接收指令
int getRecvCmd(int cmd, int index)
{
	return 0;
}
//获取HID输入
int getHIDValue(int nVauleType)
{
	return 0;
}
//电机高级设置
void SetMotorOverTurn(int nAValue,int nBValue,int nCValue,int nDValue)
{
}
//巡线模块
//巡线初始化
void WER_InitRobot_5(int lPort, float fPower, int rPort, float rPower, int p1, int p2, int p3, int p4, int p5)
{
}
void WER_InitRobot(int lPort, float fPower, int rPort, float rPower, int p0)
{
}
//环境采集
void WER_Set_GrayscaleSensor(void)
{
}
//按时巡线
void WER_LineWay_T(int nSpeed, float nTime)
{
}
//路口巡线
void WER_LineWay_C(int nSpeed, int nType, float nTime)
{
}
//转弯
void WER_Around(int lSpeed, int rSpeed, int nPos)
{
}
//启动马达
void WER_SetMotor(int lSpeed, int rSpeed, float fTime)
{
}
void WER_SetMotor_T(int lSpeed, int rSpeed, float nTime)
{
}
void WER_SetMotor_E(int lSpeed, int rSpeed, int nEncPort, int nEncoder)
{
}
void WER_SetMotor_S(int lSpeed, int rSpeed, int lParam, int nSign, int rParam)
{
}
void WER_SetMotor_CS(int lSpeed, int rSpeed, int lParam,int lChannel, int nSign, int rParam)
{
}
//高级巡线
void WER_AdvancedWay_T(int nSpeed, float nTime)
{
}
void WER_AdvancedWay_E(int nSpeed, int nEncPort, int nEncoder)
{
}
void WER_AdvancedWay_S(int nSpeed, int lParam, int nSign, int rParam)
{
}
void WER_AdvancedWay_CS(int nSpeed, int lParam,int lChannel, int nSign, int rParam)
{
}

//math相关
int iseven(float x)
{
	return 0;
}
int isodd(float x)
{
	return 0;
}
int isprime(float x)
{
	return 0;
}
int isint(float x)
{
	return 0;
}
int ispositive(float x)
{
	return 0;
}
int isnegative(float x)
{
	return 0;
}
int isdivided(float x, float y)
{
	return 0;
}
int Random(int mMin,int mMax)
{
	return 0;
}
//创建线程/任务
int CreateTask(void* (*mTaskName)(void *) , void* arg)
{
	return 0;
}

//AI模块
//打开关闭AI识别
void AIOpen(char * type,int mCommand)
{
}
//获取AI识别结果
char * GetAICode(int nStart, char * AIFileName)
{
	return "";
}
//获取AI识别结果
int GetAIString(int nStart, char *nAIFileName,char *mResult, int mResultSize)
{
	return 0;
}
//获取二维码
char * GetQRCode(float nTime)
{
	return "";
}
int GetQRString(float nTime,char *mResult, int mResultSize)
{
	return 0;
}
//打印log信息
void LogPrint(const char *format, ...)
{
}

void Printf(const char *format, ...)
{
}
int range(int x,int xMin,int xMax)
{
	return 0;
}

float rangef(float x,float xMin,float xMax)
{
	return 0;
}




