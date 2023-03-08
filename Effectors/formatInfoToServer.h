#ifndef READDATA_H
#define READDATA_H
/**
 \file readdata.h
 @author Lian
 */
#include "../Stdafx.h"

class FormatInfoToServer
{
public:
	FormatInfoToServer();

	Action AllStop();
	Action AllStopExceptHead();
	//Read the array value for action
///两个角度之差
	Action ReadDataA(Angle Data);
	Action ReadDataA(Angle Data, float gain);
	Action ReadDataA(Angle Data, float gian, float Rdistance, float Rhigh,
			float Ldistance, float Lhigh);

/// 1.02/gain内平均速度
	///	Action ReadData(Angle Data ,const float gain=3);

/// Count个周期里直接到达角度，要求达到的减去当前的
	Action ReadData_Count(Angle Data, int Count);
	Action AdjustByMaxSpeed(Angle Data);

/// 一个周期里直接到达角度，要求达到的减去当前的，设定以后取得的当前角度均为上次要求达到的(YUCE)，加修正
	Action ReadDataD(Angle Data, float Rdistance, float Rhigh, float Ldistance,
			float Lhigh, float Rleg1, float Lleg1, float Rleg3, float Lleg3,
			float Rleg6, float Lleg6);

	Action ReadDataMax(Angle Data);
private:
	Vector3 approximate(Vector3 Vector);
	float approximate(float f);
	void AdjustParameter(float & angle);

	bool turnHeadRight;

	bool beginTurnHead;

public:
	bool beginReadData;
	int readDataCounter;

	float Head1a;
	float Head2a;
	float Larm1a;
	float Larm2a;
	float Larm3a;
	float Larm4a;
	float Rarm1a;
	float Rarm2a;
	float Rarm3a;
	float Rarm4a;
	float Lleg1a;
	float Lleg2a;
	float Lleg3a;
	float Lleg4a;
	float Lleg5a;
	float Lleg6a;
	float Rleg1a;
	float Rleg2a;
	float Rleg3a;
	float Rleg4a;
	float Rleg5a;
	float Rleg6a;

public:
	Action ReadData_MaxSpeed(Angle Data);

	void TurnHeadToFocusBall();

	float turnHeadAngle;

	void ReadData_Add(Angle Data, Angle & sendAngle);

};
#endif

