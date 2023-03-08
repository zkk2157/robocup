#ifndef PlayerVISION_H
#define PlayerVISION_H
#define REMBER_Player_NUMBER 50
#define ACC_NUMBER REMBER_Player_NUMBER/2
#define ERROR_OF_Player 0.15
#define Cycle_Time 0.02
#define BaseReferenceCyclesOfAngleToMe 2
#define BaseReferenceCycles 10
#define DIFFERENT_SEE_AS_A_SPEED 0.05
#define DIFFERENT_SEE_AS_A_ACC 0.005
#define DIFFERENT_SEE_AS_A_Degree 3
#define HeadHighOfDown 0.1//在世界模型中的原定义
#define H_headHighNum 20
#include "worldmodel.h"
#include "../Sensor/perceptor.h"
#include "../Utility/Geometry.h"
#include "../Utility/Types.h"
namespace pla
{

class PlayerInfo
{
private:
	///表明是何物体
	int m_iNum; //表示队员号。防止存储出错,num=0表示是球
	bool m_bIsMyteam; //是否是我方球员
	float timetosee;
	///Coordinate
	Vector3 m_vPlayerCoordinate[REMBER_Player_NUMBER];
	int m_iPCflag;
	float m_distanceOfPlayerToBall;
	Queue *m_qHeadHigh;
public:
	PlayerInfo();
	void SetInfor(int num);
	int GetTeamNum();
	bool IsMyteam();
	void insert(PlayerVisionInfo vision);
	Vector3 GetPlayerDirectlyCoordinate();

	float GetDistanceOfPlayerToMe();
	float GetLastAverageDistanceOfPlayerToMe();

	float GetLastAverageDistanceOfPlayerToBall();
	float GetDistanceOfPlayerToAVector(Vector3 dis);

	float GetTimeOfLastSee(); //得到最后得到准确球位置的时间
	Vector3 GetLastAverageCoordinate(); //得到最近几个周期物体的平均位置

	bool isPlayerfallDown();
	friend ostream& operator<<(ostream& os, PlayerInfo PV);
private:
	Vector3 CalculatePlayerDirectlyCoordinate(PlayerVisionInfo vision);
	float mGetheadHigh(PlayerVisionInfo vision);
	float GetDistanceOfPlayerToBall(PlayerVisionInfo vision);
	void mPCflagIncrease();
	int mgetBackPCFlag(int num);
};

}
#endif // PlayerVISION_H
