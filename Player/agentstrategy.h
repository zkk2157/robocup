#ifndef SOCCERBOTBEHAVIOR_H
#define SOCCERBOTBEHAVIOR_H

/**
	\file agentstrategy.h
	@author Leisland <leisland@163.com>
 */
#include "../Stdafx.h"

#define AAA 35

using namespace std;


class Strategy// : public Behavior
{
	public:
		Strategy();

	protected:

		THingeJointSenseMap theoryJiontAngle;
		THingeJointSenseMap pastTheoryJiontAngle[2];
		THingeJointSenseMap redeemJiontAngle;


		//Action SetBeamCoordinate();
	private:
		void EstimateWhetherFallDown();
		//bool EstimateCanShoot();
		bool EstimateCanShoot();
		bool EstimateCanShooting();
		//Action StandUp();
		Action ShootBall();
		Action LeftShooting();
		Action PassBall();
		Action rightFootShootBall();
		Action prepareForShootting();
		Action prepareShootingForFreeKick();
		Action prepareShootingForFreeKickCIT();

		float CalculateHighAndDistanceByAngle(float thighAngle,float shankAngle,float &high,float &distance);
		
		//Action StandUpFromFront();
	
	private:

		bool gaitStoped;


		bool canShootBall,beginShoot,prepareShoot,finishShoot;
		bool rightFootCanShoot,leftFootCanShoot;
		bool beginPassBall,rightFootPass,leftFootPass;
		int counter;
		
		Role myRole,myLastCycleRole;
		///////////////////////////////////////////////////cch 2008-7-1////////////////////////////
	public:
		Action stopAndShootting();
		Action stopAndShoottingByNexus3D();
		Action stopAndShoottingbeforekick();
		Action stopAndShoottingByTrajectory();
		Role GetNowmyRole(){return myRole;}
		struct Jiont
		{
			string name;
			float angle;
			bool actionFinish;
		};
		
		//Jiont naoJiont[22];
		float distanceToBall[20];
		
	public:
		void JiontDataInit();
		void ClearJiontData();
		void ActionStateInit();
		Action CreateCommand();
		float GetCurrentJiontAngle(JointID J_ID);
	private:
		void HJAdjust(JointID J_ID,float objectAngle,float speed);
		void UJAdjust(JointID J_ID,float objectAngle,int anticipatedCycles);
	private:
		bool actionBegain;
		int actionTime;
		float maxSpeed;
		////////////////////////////////cch 2008-7-22////////////////////////////////////////////////
	public:
//		void ResetWalkAndStrategyData();
		Action MainStrategy();
		Action DoStrategy();
		Action DoHhuStrategy();
		Vector3 CalculateMyDestinationPoint();
		Role GetMyPlayRole();
		Action VanguardStrategy();
		Action ViceVanguard_1_Strategy();
		Action ViceVanguard_2_Strategy();
		Action ViceVanguard_3_Strategy();
		Action CentreForwardStrategy();
		Action LinebackerStrategy();
		Action GoalieStrategy();
		Action CentreForwardAction();
		Action ViceVanguard_1_Action();
		Action ViceVanguard_2_Action();
		Action ViceVanguard_3_Action();
		Action LinebackerAction();
		Action GoalieAction();
///		void GoalieBackToPositionSolution();
		void ResetVanguardStrategyData();
		void ResetViceVanguard_1_StrategyData();
		void ResetViceVanguard_2_StrategyData();
		void ResetCentreForwardStrategyData();
		void ResetLinebackerStrategyData();
		
///		void LinebackerBackToPositionSolution();
		bool IsBallInLinebackerControlArea();
		bool IsLinebackerBallCleared();
		
///		void CentreForwardBackToPositionSolution();
		bool IsBallInCentreForwardControlArea();
		bool IsCentreForwardBallCleared();
		bool IsAvoid();
		
		void FindBall();
//		void ClearFindBallData();
		
//		void InitStrategyData();
		void BehaviorDecision();
		void CalculateObjectPoint();
		Vector3 CalculateObjectPointDebug(Vector3& direction);
		void EstimateSpeedStrategy(float& angleToTurn);
		Vector3 CalculateDirectionPoint();
		bool OpponentAgentWillBlockMe(Vector3& direction);
		Vector3 CalculateSkewingBallCoordinate(float offsetOfDestination,Vector3& direction);
		Vector3 CalculateIntermediateDestination(float offsetOfDestination,Vector3& direction);
		Vector3 CalculateTerminalDestination();
		bool EstimateAdjustDestinationCalculateMethod(Vector3 intermediatePoint,Vector3 terminalPoint,float tempY);
		Action HandleBall();
		void EstimateHandleBallMethod();
		bool EstimateWhetherCanHandleBall();
		void RecoverData();
		Action GeneralWalk();
//		void WalkSolutions();

		void theNewWalkSolutions(Vector3& destination,float& angleToTurn,TopSpeed& topSpeed);
		void theWalkSolutions(Vector3& destination,float& angleToTurn,TopSpeed& topSpeed);

		HorizonMoveDirection GetHorizonMoveDirection();
		
		Action Walk(Vector3& destinationPoint);
		Action WalkTo(Vector3& destinationPoint,float& angleToTurn,SpeedStrategy& speedMethod);
		Action NaoWalk();
		Action HhuWalk();
		Action NEWWALK(Vector3& destination,float& angleToTurn,TopSpeed& topSpeed) ;   ///lr
		Action HhuVanguard();
//		void InitWalkData();
		void CreateGait();
		void NewCreateGait();
		void CalculateHorizontalMoveAngle();
		void CalculateTurnAngle(float& angle);
		void CalculateTurnHeadAngle();
		void CalculateTurnAngleDebug(Vector3& destination);
		
		void ExchangeLeg();
		float GetTurnAngle(Vector3& destination);
		void BackMyZMP(Vector3& myCoordinate,float offset);
		void CalculateWalkToSideAngle();
		void GetWalkSideDirection();
		void CalculateWalkAngle();
		Action GaitCommand();
		void GetJiontAngle(string legID,float high,float length);
		void RecordTheoryJiontAngle();
		void CalculateRedeemJiontAngle();
		void OutPutData(float a,float b,float c);
		bool IsGetToThePlannedPoint(Vector3& plannedPoint);
		bool myRoleChanged();
		void SortPlayerByDistanceToBall(PlayerVector& players);
	private:
		DecisionMotion decisionChoice;

		HorizonMoveDirection moveDirection;

		HorizonMoveSpeedStrategy moveStrategy;			///lr
		TopSpeed topSpeed;
 		TopHorizontalSpeed topHorizontalSpeed;
		bool getToDestinationCoordinate;
		bool walkToDestinationCoordinate;


		
		float standHigh;
		float leftStepHigh,leftStepLength;
		float rightStepHigh,rightStepLength;
		float stepIncrement;
		float minUpStepHigh,maxDownStepHigh;
		float upFootHigh,downFootHigh;
		float temperVariable;
		
		float rightThighAngle,rightShankAngle,rightFootAngle,rightAnkleAngle;
		float leftThighAngle,leftShankAngle,leftFootAngle,leftAnkleAngle;
		float turnLeftAngle,turnRightAngle;
		float rightArmAngle,leftArmAngle;
		float rightElbowAngle,leftElbowAngle;
		float rightCoxaAngle,leftCoxaAngle;
		float headUpDownAngle;
		float head1Angle;
		float head2Angle;
		float angleToTurn;
		float turnHeadAngleIncrement;
		float cycleTime;//the time of shift and swing and load foot
		float currentTime;
		int cycleNumber;
		int timer;
		
		int timeCounter;
		int pointer;
		
		float thighLength;
		float shankLength;
		
		//Vector3 destination,direction;
		Vector3 terminalPointOfAdjustAgentCoordinate;
		Vector3 currentCycleBallCoordinate;
		
		//bool walkBegain;
		bool controlLabel_1,controlLabel_2,controlLabel_3,controlLabel_4;
		bool leftFoot,rightFoot;
		bool walkToward,walkBackward;
		bool firstWalkToward,firstWalkBackward;
		bool firstStep;
		bool firstCreateCommand;
		bool turnHeadUpDown;
		bool turnHeadRightLeft;
		bool leftHorizontalMove,rightHrizontalMove;
		
		//turn head
		int turnHeadCounter;
		int turnHeadCounterClearZeroNum;
		int turnHeadTimes;
		bool firstTurnHead;
		bool turnHeadToLeft,turnHeadToRight;
		bool canStopTurnHead;
		bool beginFindBall;
		bool beginTurnHead;
		bool turnHeadEnable;
		bool beginTurnBody;
		bool turnBodyToFindBall;
		bool adjustBodyDirection;
		bool gotMyMoveDirection;
		
		bool turnQuickly,turnSlowly;
		bool firstQuicklyTurn,firstSlowlyTurn;
		bool speedUp,speedDown,quickSpeedDown;//lastCycleSpeedStrategy,currentCycleSpeedStrategy;
		SpeedStrategy lastCycleSpeedStrategy,currentCycleSpeedStrategy;
		WalkDirection walkDirection,currentCycleWalkDirection, lastCycleWalkDirection;

		bool changeDirection;
		bool walkToSide,walkToLeft,walkToRight;
		bool walkToPermanent;
		bool handleTheBallToSideline;
		bool canHandleBall;
		bool stepAtCurrentPlace;
		bool walkToTheBallDirectly;
		bool readyToShootBall;
		bool doNotChangeMyRole;
		//bool hasResetedWalkAndStrategyData;
		////debug turning
		bool recordPoint;
		bool turnToBallDirectly;
		bool blockHandleBallJudgement;
		bool handleToVirtualGoal;
		Vector3 lastStepCoordinate,currentStepCoordinate;
		float turnIncrement,maxTurnAngle;
		float turnAngle;
		HorizonMoveDirection myMoveDirection;
		bool goalieClearBall;
		bool goalieAtOwnGoal;
		bool linebackerAtOwnPosition;
		bool linebackerClearBall;
		//bool linebackerFollowBall;
		bool centreForwardClearBall;
		bool centreForwardAtOwnPosition;
		
		//
		int rightFootCounter;
		
	private://special timer definition
		Timer adjustMethodTimer,handleBallMethodTimer,shootTimer;
		//Timer estimateFallDirectionTimer;
		Timer stepAtCurrentPlaceTimer;
		int timeCounter_1,timeCounter_2;
	
	//the variables and methods of walk test
	private:
		float walkTest_upFootHigh,walkTest_downFootHigh;
		float walkTest_maxDistance,walkTest_minDistance;
		float walkTest_rightStepLength,walkTest_rightStepHigh;
		float walkTest_leftStepLength,walkTest_leftStepHigh;
		float walkTest_leftLegTurnAngle,walkTest_rightLegTurnAngle;
		float walkTest_distanceIncrement;
		int walkTest_counter,walkTest_stepCounter;
		int walkTest_cycle;
		bool walkTest_walkBegin;
		bool walkTest_speedUp,walkTest_speedDown;
		bool walkTest_walkForward,walkTest_walkBackward;
		
	private:
		Action NaoHandleBall();
		Action WalkTest();
		void WalkTest_WalkDataInit();
		//ljj add for judge falling down or falled down
		//void doJudgeFallDown();
/**           lr          */
		void EstimateAngleToTurn();

		void EstimateSpeedByTurnAngle();
		
//		void WalkSolutions_2();

//		void WalkSolutions_3();

		Action newShootBall();
	public:
		Vector3 WalkToDestinationCoordinate(Vector3 destination);

		Vector3 HandleBallGoalongwithOneOfTwoLine(Vector3 destination); ///by gaojin


		Vector3 HandleBallDestinationForShootBall(Vector3 destination);///add by gaojin

		//Vector3 SetHandleBallDestinateon(Vector3 destination);///add by gaojin,设置将要跑向的目标点

		bool WhetherBallAndMeInTwoLineArea();///add by gaojin

		Vector3 CalcDestinationIfOpponentBlockMe(Vector3 destination,int OpponentNumber);///add by gaojin

		Vector3 CalcDestinationIfTeamMateBlockMe(Vector3 destination,int teammateNumber);///add by gaojin

		OffensiveAndDefensiveRating OffensiveAndDefensiveDegree();///用于根据目前场上的状况，决定各种角色的人数 add by gaojin


		float CalculateMyDistanceToDestination(Vector3 myCoordinate,Vector3 destination);

		//Action StandUpFromBack();
		
		//Action DisposeFalling();

		//Action PreventForwardFallingDown();
	
		//Action PreventBackFallingDown();
		
		Action HalfStepWalk();
		
		Action ViceCentreForward_1_Strategy();
		
		Action ViceCentreForward_2_Strategy();
		
		Action ViceCentreForward_1_Action();
		
		Action ViceCentreForward_2_Action();
		
		Action ViceLinebacker_1_Strategy();
		
		Action ViceLinebacker_1_Action();

		Action ViceLinebacker_2_Strategy();
		
		Action ViceLinebacker_2_Action();
		
		bool WhetherUseHalfStepWalk();
		
		bool GetWhetherStriker();
		
		void SetWhetherStriker(bool res);
		void initSplits();
		float GetfallDownTurnHead(){return fallDownTurnHead;}
		void initHalfStepParameter();
		void initShootControlParameter();
		void turnHeadStrategy(float fallDownTurnHead);
		void updateLocalVariables();
	private:
		int checkCounter;

		Vector3 theBallCoordinate;
	
		bool whetherGetToDestination;
	
		bool turnHeadRight;
	
		Vector3 destination;
		
		bool initRole;
	
		Role newMyLastCycleRole;
	
		bool shortShootDistance;



		bool rigthFootShoot;

		bool centreForwardEstimateCanShoot();

		//bool justAfterStandUp;

		bool leftShootDistance;

		bool centreForwardEstimateCanShooting();



		int seeObjectChange;
		
		bool turnHeadMax;
		
		int recordDistanceCounter;
		float theSpeedOfBall;
		float myDistanceToBall;
		float lastCycleDistanceToBall;
		Action splitsToSaveBall();
		bool getDownToSaveBall;
		bool justAfterSplits;

		bool smallAngleSplit;
		
		void WalkSolutions();
		


		HorizonMoveDirection direction;
		
		//bool fallDownTurnHeadToFindTwoflags;
		
		bool whetherClearanceKick();

		bool whetherCanShoot();
		
		bool whetherCanShootForVanguard();///判断vanguard能否射门，不是为Striker设计，Striker还是使用WhetherCanShoot()来判断 by gaojin

		bool centreForwardWhetherCanShoot();
		
		float fallDownTurnHead;
		
		int oneStyleWalkTime;
		bool useHalfStepWalk;
		
		
		bool afterSplits;
		float beginShootAngle;
		float beginShootDistance;

		bool whetherOpponentInMyWayToGoal();
		Vector3 ALLanumRrunFormation();
		Vector3 DefenserunFormation();
		Vector3 AttackrunFormation();
		Vector3 NewRunFormation();
		Vector3 runFormation();
		
		Action standUpWithTurnHead();

		float approximate(float f);
		
		
		//bool firstBeamVanguard;
		
		//bool firstBeamPositionA;
		
		//bool firstBeamPositionB;

		//bool firstBeamPositionC;
		
		//bool firstBeamPositionD;
		
		
		int noFRPCount;
		
		bool initPass;
		
		PassDirection estimatePassDirection();
		
		Action dealFallingDown();
		
		Action kickOff();
		
		Vector3 standBetweenBallAndMyGoal(float distanceToBall);
		
		bool turnHeadRightChanged;
		
		Action passBall();
		
		Action goForwardToSaveBall();
		
		bool Penalty_Kick;
		

		
		/**       local variables for simplifies the code        */
		
		float localMyDistanceToBall;
		
		float localMyBodyAngleToBall;
		
		Vector3 my;
		Vector3 myCoordinate;
		Vector3 ball;
		Vector3 ballCoordinate;
		
		float localMyFaceAngleToBall;
		
		float localMyBodyAngleToXAxis;
		
		float localLastCyclesAverageBodyToXAngle;
		
		float localLastCyclesAverageBallMeToXAxisAngle;
		
		float localMyHeadAngleToXAxis;
		
		float localBodyToX;
		
		Vector3 localTheBallStopCoordinate;
		
		float localLastCyclesAverageBallGoalToXAxisAngle;
		
		bool localWhetherCanAttackOppGoal2;
		
		TPlayMode localCurrentGameMode;
		
		int localClosestToBallOpponentNumberByVision;
		
		float localClosestToBallOpponentDistanceByVision;
		
		float localLastCyclesAverageBallMeXDifference;
		
		float localLastCyclesAverageBallMeYDifference;
		
		float localFieldLength;
		
		float localFieldWidth;
		
		float localLastCyclesAverageTurnHeadAngle;
		
		float localCurrentJointAngleJID_HEAD_1;
		
		float localMyAngleToBall;
		
		Vector3 localBallCoordinateForRunFormation;
		
		bool localWhetherCanPassFront;
		
		void third(double x0, double y0, double x1, double y1);
		
		bool whetherStriker;
		
		float localLastCyclesAverageHorizontalTurnHeadAngle;
		
		bool whetherEnhanceDefence();
		
		string opponentTeamName[3];
		
		Action slideTackleToSaveBall();
		bool slidedToSaveBall;
		Direction slidedDirection;
	public:
		Action StopWhereAt();
		/*
		 * 矢量(point1-->point2)球距point2点length的点位置,isAdirection=true表示与(point1-->point2)同方向的点,反之则为反方向
		 */
		Vector3 Vector3Linelength(Vector3 point1,Vector3 point2,float length,bool isAdirection=true);
		/** end  */
		
	///	Vector3 runRobocanes
};
#endif

