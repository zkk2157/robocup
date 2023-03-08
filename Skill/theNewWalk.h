#ifndef THENEWWALK_H
#define THENEWWALK_H

#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <utility>
# include <iostream>

# include "math.h"

#include "../Stdafx.h"

using namespace std;
using namespace boost::numeric::ublas;

#define G 9.86

class NewWalk
{
public:
	bool hasFallDown;
	NewWalk();
	void changeBody_P(FallDirection direct);
	Action CreateWalkGait(Vector3& destination, float& angleToTurn,
			TopSpeed& topSpeed);

	bool UseNewWalk;
	int walkCounter; ///feng
	float ax;

private:
	void InitHalfStepWalkData();
	void InitNewWalkData();
	std::string readNewWalkData();
	///  void InitNewWalkData();
	u Rfoot,Lfoot,uLINK[14];
	void updateTime();
	void updatePV();
	void updateshootPV();
	void updatePBPV1();
    void updatepbPV();
	void receiveJointInfo(); ///feng
	///this part should be private,but for test,use them as public
	void preparation();
	void FindMother(int j);
	float norm(boost::numeric::ublas::vector<float> w);
	boost::numeric::ublas::matrix<float> Rodrigues(
			boost::numeric::ublas::vector<float> w, float dt);
	void ForwardKinematics(int j);
	float TotalMass(int j);
	std::vector<int> FindRoute(int to);
	boost::numeric::ublas::vector<float> cross(
			boost::numeric::ublas::vector<float> a,
			boost::numeric::ublas::vector<float> b);
	boost::numeric::ublas::matrix<float> CalcJacobian(std::vector<int> idx);
	float trace(boost::numeric::ublas::matrix<float> R);
	boost::numeric::ublas::vector<float> rot2omega(
			boost::numeric::ublas::matrix<float> R);
	void swap(float &a, float &b);
	boost::numeric::ublas::matrix<float> DinV(
			boost::numeric::ublas::matrix<float> A, int n);
	boost::numeric::ublas::matrix<float> CalcVWerr(u Cref, u Cnow);
	float norm2(matrix<float> err);
	void rightDivide(boost::numeric::ublas::matrix<float> J,
			boost::numeric::ublas::matrix<float> err, float d[]);
	void MoveJoints(std::vector<int> idx, float dq[]);

	boost::numeric::ublas::matrix<float> Rroll(float phi);
	boost::numeric::ublas::matrix<float> Rpitch(float theta);
	float sign(float a);
	void IK_leg(u body, float D, float A, float B, u foot);

	void InverseKinematicsAll(int to, u Target); //J\err==pinv(J)*err==(J'*J)^-1*J'*err
	void ForwardVelocity(int j);
	boost::numeric::ublas::vector<float> calcMC(int j);
	boost::numeric::ublas::vector<float> calcCoM();

	boost::numeric::ublas::vector<float> calcP(int j);
	boost::numeric::ublas::matrix<float> change(matrix<float> a);
	boost::numeric::ublas::matrix<float> change1(matrix<float> a);
	float MULTIP(matrix<float> a,matrix<float> b,int n);
	boost::numeric::ublas::matrix<float> MULTIP1(matrix<float> a,matrix<float> b);
	float MULTIP2(float a[],float b[],int n);
	boost::numeric::ublas::matrix<float> Add(matrix<float> a,matrix<float> b,float u);
	boost::numeric::ublas::vector<float> calcL(int j);
	std::pair<float, float> calcZMP(boost::numeric::ublas::vector<float> com,
			boost::numeric::ublas::vector<float> dP,
			boost::numeric::ublas::vector<float> dL, float zmpz);
	std::pair<std::vector<float>, std::vector<float> > getZMP();

	std::pair<float, float> LIPMmy(float t, float org, float x0, float Tc,
			float dx0);
	std::pair<float, float> LIPMmy2(float t, float org, float x0, float Tc,
			float dx0, float b, float T);
	std::pair<float, float> LIPMmy3(float t,float org,float x0,float Tc,
							float dx0,float Ts		);
	std::pair<float,float> LIPMmy4(float x,float v,float a,float t,float Zc,float c1);
	std::pair<float,float> LIPMmy5(float x,float v,float a,float t,float Zc,float c1);
private:
	int CountinReadData;
	int i_ReceivedCount;
	int i_SendedCount;
	float adjustAngle;
	float px;
	float vx;
	float py;
	float vy;
	float HIP;
		float THIGH;
		float SHANK;
		float BODYHEIGHT;
	boost::numeric::ublas::vector<float> com;
	boost::numeric::ublas::vector<float> oldFoot, oldRFoot, oldLFoot;
	boost::numeric::ublas::vector<float> P, V, P1, L, L1, dP, dL;

	std::vector<boost::numeric::ublas::vector<float> > com_m;
	std::pair<std::vector<float>, std::vector<float> > zmp_m;
	std::pair<float, float> zmp;

	float Zc;
	float Tc;
	float cx0;
	float cy0;
	float vx0;
	float vx1;
	float vy0;
	float vy1;
	float Dtime;
	float EndTime;
	int tsize;
	int leftTsize;
	int rightTsize;
	float datak;
	float datakk;
	float eachFoot;
	float footLength;
	float footDisc;

	float zmpx;
	float zmpy;

	float zmpz;
		int k;
		float cx;
		float vxx;
		float vyy;
		float ay;
		float kk;
		float kky;
		float nk;
		float y0;
		float y1;
		float Ty;
		float Ty2;
		float Tx;
		float x0;
		float x1;
	/**         feng           */
	float horizMoveLength;
	float turnAngle;
	float nextX;
	float nextY;
	float walkMark;
	float Sx;
	float Sy;

	bool firstStep;
	bool leftStep;
	bool rightStep;
	bool init;
	bool initFirst;

	bool firstReadDate; ///feng

	int sendCount; ///feng

	float FOOTX[13];

	float time[13];

	float arangle2;
	float arangle3;
	float arangle4;
	float arangle5;
	float arangle6;

	float alangle2;
	float alangle3;
	float alangle4;
	float alangle5;
	float alangle6;

	float rangle2;
	float rangle3;
	float rangle4;
	float rangle5;
	float rangle6;

	float langle2;
	float langle3;
	float langle4;
	float langle5;
	float langle6;

	float mrangle2;
	float mrangle3;
	float mrangle4;
	float mrangle5;
	float mrangle6;

	float mlangle2;
	float mlangle3;
	float mlangle4;
	float mlangle5;
	float mlangle6;

// 		float Head1a;
// 		float Head2a;
// 		float Larm1a;
// 		float Larm2a;
// 		float Larm3a;
// 		float Larm4a;
// 		float Lleg1a;
// 		float Lleg2a;
// 		float Lleg3a;
// 		float Lleg4a;
// 		float Lleg5a;
// 		float Lleg6a;
// 		float Rarm1a;
// 		float Rarm2a;
// 		float Rarm3a;
// 		float Rarm4a;
// 		float Rleg1a;
// 		float Rleg2a;
// 		float Rleg3a;
// 		float Rleg4a;
// 		float Rleg5a;
// 		float Rleg6a;

	Angle sendAngle;

	THingeJointSenseMap Sended_mHingeJointSenseMap;
	THingeJointSenseMap Received_mHingeJointSenseMap;
	THingeJointSenseMap Forecast_mHingeJointSenseMap;
	THingeJointSenseMap Delay_mHingeJointSenseMap;

	THingeJointSenseMap Sended_mHingeJointSenseMap1;
	THingeJointSenseMap Sended_mHingeJointSenseMap2;
	THingeJointSenseMap Sended_mHingeJointSenseMap3;

	THingeJointSenseMap Received_mHingeJointSenseMap1;
	THingeJointSenseMap Received_mHingeJointSenseMap2;
	THingeJointSenseMap Received_mHingeJointSenseMap3;

	THingeJointSenseMap mHingeJointSenseMap;

	bool judgeFallDown;

private:
	void updateWalkDirection(WalkDirection& walkDirection);

	void updateSpeedStrategy(SpeedStrategy& speedStrategy,
			DecisionMotion& decisionChoice, WalkDirection& walkDirection,
			TopSpeed& topSpeed);

	void updateHorizontalMoveSpeed(HorizonMoveDirection& moveDirection,
			HorizonMoveSpeedStrategy& moveStrategy,
			TopHorizontalSpeed& topHorizontalSpeed);

	void CalculateHorizontalMoveAngle(HorizonMoveDirection& moveDirection);

	void updateTurnAngle(float& angle);

	void calculateAction(double tarAngle[3][22]); //for shoot 

	void updateShootTime(); //for shoot
	void initShootParameter(); //for shoot
	string shootAction();
private:
	//////////////used for half step
	float upFootHigh;
	float downFootHigh;
	float Ldistance;
	float Rdistance;
	float Lhigh;
	float Rhigh;
	float stepIncrement;
	void Record_Received_JointSense(); ///实际到达的角度
	void Record_Sended_JointSense(); ///预测将要达到的角度
	bool IsFirstinReadData;

	float standHigh;
	float minUpStepHigh;
	float maxDownStepHigh;

private:

	int whichFoot; //for shoot   1 rightfoot   &&  2  left leftfoot
	float increaseHigh; //stand higher for  shoot
	float whetherWalkForward;

	float footWidth;

	float turnLeftAngle;

	float turnRightAngle;

	bool turnQuickly;

	bool turnSlowly;

	string sHead1;

	string sHead2;

	float rightCoxaAngle;
	float leftCoxaAngle;
	float rightAnkleAngle;
	float leftAnkleAngle;

	void exchangeArms();

	float swingLeftAngle;
	float swingRightAngle;

	float swingLeftAngle2;
	float swingRightAngle2;
	float bodyForerakeAngle;
	float legForerakeAngle;
	float horizonForerakeAngle;

	float NAO_A;
	float NAO_B;

public:
	int GetWalkCounter();

	float GetFootLength();

	void SetFootLength(float foot);

	float GetFootWidth();
	void SetFootWidth(float foot);
	Action HalfStepGait(WalkDirection& walkDirection, float& angle,
			SpeedStrategy& currentCycleSpeedStrategy,
			HorizonMoveDirection& horizonMoveDirection, float& HeadTurnAngle); //half step powered by cai

	///bool leftHorizontalMove,rightHrizontalMove;

private:
	std::string HalfStepActualize(); //half step powered by cai

	float turnHeadAngle;

	float lastCyclesAverageTurnHeadAngle;

	float lastCyclesTurnHeadAngle[LAST_CYCLES_OF_TURN_HEAD_ANGLE];

	void updateLastCyclesAverageTurnHeadAngle();

	float speed;

	float bodyAngleToDestination;

	void updateShootParameter(int leftShootDistance);
	void updateShootParameterForFreeKick(int leftShootDistance);
	void updateShootParameterForKickCIT(int leftShootDistance);

	float lastCycleFootLength;
	float lastCycleFootWidth;

	float lastCyclesAverageVerticalTurnHeadAngle;

	float lastCyclesVerticalTurnHeadAngle[LAST_CYCLES_OF_TURN_HEAD_ANGLE];

	void updateLastCyclesAverageVerticalTurnHeadAngle();

	void adjustMySpeedByBodyState();

	void adjustMyBarycenterToProtectMyself();

	void CalculateTurnAngle(float& angle);
	void CalculateHorizontalMoveAngle();
	void CalculateTurnHeadAngle();

	Action prepareForShoot_HalfStep(int footSelect);

	bool nowForPass;
	bool nowForPass2;
	bool nowForPass3;
	bool nowForPass4;
	bool justAfterPass;
	bool justAfterPass3;

	int mark11;
public:
	float GetTurnHeadAngle();

	void SetTurnHeadAngle(float angle);

	float GetLastCyclesAverageTurnHeadAngle();

	void updateBodyAngleToDestination(Vector3& destination);
	void updateFootLengthWidth(TopSpeed& topSpeed);

	void SetBodyAngleToDestination(float angle);

	float GetBodyAngleToDestination();

	Action PrePareForShoot(int shortShootDistance);
	Action PrepareForFreeKick(int shortShootDistance);
	Action PrepareForFreeKickCIT(int shortShootDistance);

	float GetLastCyclesAverageVerticalTurnHeadAngle();

	int WhichFootRaised();

	Action PassBall(PassDirection passDirection);
	void initPass();
	bool whetherCanQuitPassProcess();

	void addPassMotion();

	float lasss;
};

#endif

