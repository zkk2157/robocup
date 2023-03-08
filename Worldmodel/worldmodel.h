#ifndef WORLDMODEL_H
#define WORLDMODEL_H
/**        czg       */
# define RecordTimes 20

#include "../Stdafx.h"
/**
 \file worldmodel.h
 @author Leisland <leisland@163.com>
 */

/**
 \class WorldModel is one of the important classes in our code.During every cycle,according to the message from server,it will
 update the environment information and world state of the game,all these data will decide the agent's motion.(editor:leisland date:2008-8-20)
 */

class WorldModel
{
public:
	/**construct function will initialise the basic data of world model*/
	WorldModel();

	/**update the information of world model*/
	void UpdateWorldModel();

	/**output the data of world model,when you debug the source code of world model,this function will be useful*/
	void OutputData();

	/**get the coordinate of object by the corresponding object name,when call this function,you must pass the object name to it*/
	Vector3 GetObjectCoordinate(VisionObject object);

	/**get the polar coordinate of object,the coordinate is sense message from server*/
	VisionSense GetObjectPolarCoordinate(VisionObject object);

	/**get our middle goal's coordinate,actually ,the returned value will be the same whenever you call it,because our goal's location will not change once the game start. :-)*/
	Vector3 GetMyMiddleGoalCoordinate();

	/**get opponent middle goal coordinate,again,the returned value will also be the same during the game*/
	Vector3 GetOpponentMiddleGoalCoordinate();

	/**get the length of soccer*/
	float GetFieldLength();

	/**get the width of soccer*/
	float GetFieldWidth();

	/**get the height of soccer*/
	float GetFieldHeight();

	/**get the width of goal*/
	float GetGoalWidth();

	/**get the depth of goal*/
	float GetGoalDepth();

	/**get the height of goal*/
	float GetGoalHeight();

	/**get the length of penalty*/
	float GetPenaltyLength();

	/**get the width of penalty*/
	float GetPenaltyWidth();

	/**get the angle between my direction line and the x coordinate*/
	float GetMyAngleToXCoordinate();

	//
	bool GetMyBodyAngleToXAxis(float& angle);
	/**lr*/
	bool GetMyHeadAngleToXAxis(float& angle);

	/**get radius of the ball*/
	float GetBallRadius();

	/**get the number of mine*/
	int GetMyNumber();

	/**get vanguard's number*/
	int GetVanguardNumber();

	/**get current game mode*/
	TPlayMode GetCurrentGameMode();

	/**get the team index of my team*/
	TTeamIndex GetMyTeamIndex();
	void ChangeMyTeamIndex();
	/**get the passed time of the game*/
	float GetCurrentGameTime();

	/**get the passed time of the simspark server*/
	float GetCurrentServerTime();

	/**get the opponent team's name*/
	string GetMyOpponentTeamName();

	/**get my team's name*/
	string GetMyTeamName();

	/**get my beam coordinate*/
	Vector3 GetMyBeamCoordinate();

	/**get the current coordinate of mine*/
	Vector3 GetMyCoordinate();

	/**get current ball coordinate*/
	Vector3 GetBallCoordinate();

	/***/
	bool CanDoLocalizationDirectly();

	/***/
	bool CanDoLocalization();

	/***/
	bool IsBallInMyOwnPenaltyArea();

	/***/
	bool IsVanguardFallDown();

	/***/
	bool IsVanguardLostBall();

	//ljj add comments for fall down 20100801
	/**获取前N个周期，身体的平均旋转速度*/
	Vector3 getAverageOfLastCyclesGYR();

	/**获取前N个周期，左脚的平均受力大小*/
	Vector3 getAverageOfLastCyclesFRP_Lf();

	/**获取前N个周期，右脚的平均受力大小*/
	Vector3 getAverageOfLastCyclesFRP_Rf();

	/**获取前N个周期，左脚的平均受力位置*/
	Vector3 getAverageOfLastCyclesFRP_Lc();

	/**获取前N个周期，右脚后端的平均受力位置*/
	Vector3 getAverageOfLastCyclesFRP_Rc();

	/**判断是否正在跌倒*/
	bool IsFallingDown_test();

	/**判断是否完全跌倒*/
	bool IsFallDown_test();

	//ljj end

	/**If face to the opponent team's field*/
	bool WhetherFaceToOpponentField();

	/**If the game mode has changed,return true,or, return false*/
	bool IsGameModeChanged();

	/**if the agent can not see the ball,the return value is false*/
	bool CanSeeTheBall();

	/***/
	bool CanSeeTheOppGoal();

	/***/
	bool CanSeeAllTheOppGoal();

	/***/
	bool CanSeeMyOwnGoal();

	/***/
	bool CanSeeMyHalfFieldFlag();

	/***/
	bool CanSeeOppHalfFieldFlag();

	/***/
	bool CanSeeTheFlag(VisionObject obj);

	/***/
	bool CanSeeMyTeammate(int unum);

	/***/
	bool CanIdoDefendingMotion();

	/***/
	bool IsLeftFieldFlag(VisionObject obj);

	/***/
	bool IsOppTeamKick();

	/**get my fall direction*/
	FallDirection GetMyFallDirection();

	/**get my distance to ball*/
	float GetMyDistanceToBall();

	/**get the angle of my direction to ball*/
	float GetMyAngleToBall();

	/**get my distance to a specific flag*/
	float GetMyDistanceToFlag(VisionObject obj);

	/**get my angle to a specific flag*/
	float GetMyAngleToFlag(VisionObject obj);

	/**get my distance to my teammate*/
	float GetMyDistanceToTeammate(int num);

	/**get my angle to my teammate*/
	float GetMyAngleToTeammate(int num);

	/**get distance of goalie to ball*/
	bool GetGoalieToBallDistance(float& dis);

	/**get distance of vanguard to ball*/
	bool GetVanguardToBallDistance(float& dis);

	/**get my team's score*/
	int GetMyTeamScore();

	/**get opponent team's score*/
	int GetOpponentTeamScore();

	/**get my teammate amount(in my vision area)*/
	int GetMyTeammateAmount();

	/**get my teammate vector,this vector contains all my teammates' information*/
	void GetMyTeammateVector(PlayerVector& playerVector);

	/**get my opponent team vector,this vector contains all my opponent team players' information*/
	void GeyMyOpponentPlayerVector(PlayerVector& playerVector);

	/**get current angle of specific joint*/
	float GetCurrentJointAngle(JointID id);

	/***/
	int GetTheMinDistanceToBallTeammateNum();

	/***/
	bool GetMyDistanceToBallSortedIndex(int& index);

	/***/
	bool DoesVanguardCanHandleBall();

	/**encapsulates spoken words*/
	string GetEncapsulatedWords(string words);

	/**              add by czg     */
	Vector3 GetVanPosition();

	void CalculateGyr();

	int *GetLocFlag();

	float *GetLocThetaindex();

	void RecordTeammatePos();

	void RecordOpponentPos();
//		void initMyCoordinate(Vector3 val){MySaveCoordinate.init()}
private:
	SaveCoordinate BallSaveCoordinate;
	Queue *QuFront_back;

	Queue *QuSideLeft_right;

	Queue *QuFRP_Z;

	Queue *QuFRP_Y;

	Queue *ballCoor_X;
	Queue *ballCoor_Y;

	/**update the environment information of world model*/
	void UpdateEnvironmentInformation();

	/**update the world state of world model*/
	void UpdateWorldState();

	/**update eight flags's coordinate*/
	void UpdateSoccerFlagCoordinate();

	/**update the coordinate of middle goal*/
	void UpdateMiddleGoalCoordinate();

	/**update team index*/
	void UpdateTeamIndex();

	/**update opponent team's name*/
	void UpdateOpponentTeamName();

	/**update my team name*/
	void UpdateMyTeamName();

	/**update my beam coordinate*/
	void UpdateMyBeamCoordinate();

	/**update my number*/
	void UpdateMyNumber();

	/**update my team's vanguard's number*/
	void UpdateVanguard();

	/**update the current mode of game*/
	void UpdateGameMode();

	/**update the passed time of game*/
	void UpdateGameTime();

	/**update the passed time of simspark server*/
	void UpdateServerTime();

	/**update the coordinate of mine*/
	void UpdateMyCoordinate();

	/**update my body to X axis angle*/
	void UpdateMyBodyToXAxisAngle();

	/**update other player's coordinate,including my teammate and opponent team's players*/
	void UpdateOtherPlayerCoordinate(VisionObject obj1, VisionObject obj2,
			VisionObject obj3, float d1, float d2, float d3);

	/**update the current coordinate of ball*/
	void UpdateBallCoordinate();

	/**update distance between myself and the ball*/
	void UpdateMyDistanceToBall();

	/**update my team's score*/
	void UpdateMyTeamScore();

	/**update the opponent team's score*/
	void UpdateOpponentTeamScore();

	/**update the information of players,including the player's number ,coordinate and so on*/
	void UpdatePlayerInformation();

	/**update my teammate information*/
	void UpdateMyTeammateInformation();

	/**update opponent team player's information*/
	void UpdateOpponentTeamPlayerInformation();

//ljj add comments 20100801
	/**更新前N个周期的身体平均旋转速度*/
	void UpdateLastCyclesAverageGYR();

	/**保存前N个周期的身体旋转速度数组*/
	SGYRSensor gyr_sensor[getLastCycles];
	Vector3 averageOfLastCyclesGYR;

	/**更新脚上前N个周期的反作用力*/
	void UpdateLastCyclesAverageFRP();

	/**保存前N个周期的脚部反作用力数组*/
	FRPerceptor frp_senseMap_L[getLastCycles];
	FRPerceptor frp_senseMap_R[getLastCycles];

	/**前N个周期，脚部反作用力的平均大小和位置*/
	Vector3 averageOfLastCyclesFRP_Lf;
	Vector3 averageOfLastCyclesFRP_Rf;
	Vector3 averageOfLastCyclesFRP_Lc;
	Vector3 averageOfLastCyclesFRP_Rc;
	//ljj end

	/**clear out the information of players,when the new cycle start,this function will be called*/
	void ClearPlayerInformation();

	/**estimate I'm whether have falled down*/
	void EstimateWhetherFallDown();

	/**calculation of fieldnormal*/
///		void UpdateMyFieldNormal();
	/**calculate my coordinate*/
	void Localization();

	/***/
	void LocalizationByRightFieldFlags(float &d1, float &d2, float &d3,
			Vector3 &pos1, Vector3 &pos2);

	/***/
	void LocalizationByLeftFieldFlags(float &d1, float &d2, float &d3,
			Vector3 &pos1, Vector3 &pos2);

	/***/
	void LocalizationByTopFieldFlags(float &d1, float &d2, float &d3,
			Vector3 &pos1, Vector3 &pos2);

	/***/
	void LocalizationByBottomFieldFlags(float &d1, float &d2, float &d3,
			Vector3 &pos1, Vector3 &pos2);

	/***/
	void RecordFlagSenseMsg();

	/***/
	void RecordTeammateSenseMsg();

	/***/
	void EvaluateVisionSenseMsg();

	/***/
	void EvaluateTeammateSenseMsg();

	/**estimate my falled direction*/
	void EstimateFallDirection();

	/**convert the information of my vision*/
	void ConvertVisionInformation();

	/**convert the polar coordinate into decare coordinate,because the decare coordinate will be easy to calculate some parameters*/
	Vector3 ConvertPolarCoordinatesIntoDecareCoordinates(
			VisionSense& visionInformation);

	/**convert the polar coordinate into decare coordinate*/
///		Vector3 PolarToCartesian(Vector3& polar);
	/**amend the Vector value*/
	Vector3 GetApproximateValue(Vector3 Vector);

	/**conver angle into radian*/
	float ConvertAngleIntoRadian(float angle);

	/**array calculation*/
	Vector3 Equation(float mdata[3][4]);

	/**set up the map container of VisionOjbect*/
	void SetupVisionObjectToPlayerMap();

	/***/
	bool IsFlag(VisionObject obj);

	/***/
	void GetRole(string& str, Role& role, bool& state);
private:
	/**map object ot Descartes coordinate*/
	TObjectPosMap mObjectPosMap;

	/**map object to vector*/
	TObjectVectorMap mObjectVectorMap;

	/**map object to player*/
	TVisionObjectMap mVisionObjectToPlayerMap;

	/**the middle coordinate of my team's goal*/
	Vector3 myMiddleGoalCoordinate;

	/**the middle coordinate of opponet team's goal*/
	Vector3 opponentMiddleGoalCoordinate;

	/**teh basic parameters of soccer*/
	float FieldLength; //length of soccer

	float FieldWidth; //width of soccer

	float FieldHeight; //height of soccer

	float GoalWidth; //width of goal

	float GoalDepth; //depth of goal

	float GoalHeight; //height of goal

	float PenaltyLength;

	float PenaltyWidth;

	/**the angle of my direction to x coordinate*/
	float agentTheta;

	/**the angle of my direction to x coordinate*/
	float myBodyToXAxisAngle;

	/**lr*/
	float myHeadToXAxisAngle;

	/**the angle of my body to the ground*/
	float agentPhi;

	/**the radius of ball*/
	float ballRadius;

	/**my play number*/
	int myNumber;

	/**my team's vanguard number*/
	int vanguardNum;

	/**current play mode*/
	TPlayMode myCurrentGameMode;

	/**last cycle play mode*/
	TPlayMode lastCycleGameMode;

	/**my team's side*/
	TTeamIndex myTeamIndex;

	/**localization method*/
	localizationOption myLocalizationMethod;

	/**the passed time of game*/
	float myGameTime;

	/**the passed time of simspark server*/
	float myServerTime;

	/**oppenet team's name*/
	string myOpponentTeamName;

	/**my team name*/
	string myTeamName;

	/**my beam coordinate*/
	Vector3 myBeamCoordinate;

	/**my current coordiante*/
	Vector3 myCoordinate;

	/**my field noraml*/
	Vector3 myFieldNormal;

	/**current ball coordinate*/
	Vector3 ballCoordinate;

	/**whether fall down,if the value is true,that means I'm falling down now*/
	bool fallDown;

	/***/
	bool vanguardFallDown;

	/***/
	bool vanguradLoseBall;

	/**the height of agent's torso*/
	FloatVector torsoHeight;

	/**counter of vector:torsoHeight*/
	int torsoHeightCounter;

	/**my fall direction*/
	FallDirection fallDirection;

	/***/
	bool canLocalizeDirect;

	/***/
	bool localizeByTurnHead;

	/***/
	TVisionSenseMap localizeSenseMap;

	/***/
	TVisionSenseMap localizeByTurnHeadSenseMap;

	/***/
	TVisionSenseMap historySenseMap;

	/***/
	TPlayerSenseMap myTeammateHistorySenseMap;

	/***/
	VisionObject localizationFlag_1;

	/***/
	VisionObject localizationFlag_2;

	/**the amount of my teammate(In my vision area)*/
	int myTeammateAmount;

	/**my distance to ball*/
	float myDistanceToBall;

	/**the total score of my team*/
	int myTeamScore;

	/**the total score of opponet team*/
	int opponentTeamScore;

	/**all my teammate's information*/
	Player myTeammate[PLAYERNUMBER + 1];

	/**all my opponent team player's information*/
Player	myOpponentTeamPlayer[PLAYERNUMBER+1];

	/**my teammate role information*/
	PlayerSayInfoVector myHeardMsgFromTeammate;

	/**         add by czg		*/
	int times;
	float gyr_x[100];
	float gyr_y[100];
	float gyr_z[100];
	float gyr[3];

	float gyr_Stat[5];
	int stat_Counter;
	float frp_Stat[5];
	int forwardSlantTime;
	int backwardSlantTime;
	void updateTheBodyBalanceState();
	bool isBodyImbalance;

	float BodyToX;
	Vector3 mytempCoordinate;
	Vector3 balltempCoordinate;
	int locflag[2];

	Vector3 TeammateCoordinate[PLAYERNUMBER][22];
	Vector3 OpponentCoordinate[PLAYERNUMBER][22];

	Vector3 lastCyclesBallCoordinate[LASTCYCLESOFBALL];

	Vector3 lastCyclesMyCoordinate[LASTCYCLESOFMINE];

	Vector3 lastCyclesBallCoordinateForRunFormation[LAST_CYCLES_OF_BALL_FOR_RUN_FORMATION];

	float lastCyclesTurnHeadAngle[LAST_CYCLES_OF_TURN_HEAD_ANGLE];
	float lastCyclesAverageBallMeToXAxisAngleArray[LAST_CYCLES_OF_BALL_ME_TO_XAXIS_ANGLE];
	float lastCyclesAverageBallGoalToXAxisAngleArray[LAST_CYCLES_OF_BALL_GOAL_TO_XAXIS_ANGLE];
	float lastCyclesAverageBodyToXAngleArray[LAST_CYCLES_OF_BODY_TO_X];
	float lastCyclesVerticalTurnHeadAngle[LAST_CYCLES_OF_TURN_HEAD_ANGLE];
	float lastCyclesAverageBallMeYDifferenceArray[5];
	float lastCyclesAverageBallMeXDifferenceArray[5];

	Vector3 newTeammateCoordinate[PLAYERNUMBER];
	Vector3 newOpponentCoordinate[PLAYERNUMBER];

	Vector3 lastCyclesAverageTeammateCoordinate[PLAYERNUMBER][LAST_CYCLES_OF_LOCATE_TEAMMATE];
	Vector3 lastCyclesAverageOpponentCoordinate[PLAYERNUMBER][20];

	Vector3 newAverageTeammateCoordinate[PLAYERNUMBER];
	Vector3 newAverageOpponentCoordinate[PLAYERNUMBER];

	std::vector<Vector3> my;

	float thetaindex[8];
	float gyroz;
	/**       lr     */

	float myAngleToOppGoal;

	//float angleBetweenBallMeAndXAxis;

	float angleBetweenBallMeAndBallOppGoal;
private:

	void updateLastCyclesAverageBallCoordinate();

	void updateLastCyclesAverageMyCoordinate();
public:

	float GetMyBodyAngleToXAxis();

	float GetMyHeadAngleToXAxis(); ///   lr

	float GetAngleBetweenBallMeAndXAxis();

	float GetAngleBetweenBallMeAndBallOppGoal();

///		bool NewCanAttackOppGoal();
	Vector3 GetfutureBallCoordinate(int numcycles);
	Vector3 GetLastCyclesAverageBallCoordinate();

	Vector3 GetLastCyclesAverageMyCoordinate();

	Vector3 GetLastCyclesAverageBallCoordinateForRunFormation();

private:
	Vector3 lastCyclesAverageBallCoordinate;

	Vector3 lastCyclesAverageMyCoordinate;

	Vector3 lastCyclesAverageBallCoordinateForRunFormation;

	void updateMyBodyAngleToBall();

private:
	float myBodyAngleToBall;

	float lastCyclesAverageTurnHeadAngle;

	void updateLastCyclesAverageHeadAngle();

	void updateLastCyclesAverageBallMeToXAxisAngle();

	void updateLastCyclesAverageBallGoalToXAxisAngle();

	float lastCyclesAverageBallMeToXAxisAngle;

	float lastCyclesAverageBallGoalToXAxisAngle;

	void updateLastCyclesAverageBodyToXAngle();

	float lastCyclesAverageBodyToXAngle;

//		void updateDestinationCoordinate();
	bool ViceVanguard_1FallDown;
// 
// 		bool ViceVanguard_2FallDown;
// 
	void UpdateViceVanguard_1();

	float lastCyclesAverageVerticalTurnHeadAngle;

	void updateLastCyclesAverageVerticalTurnHeadAngle();

	void updateVanguardNumberByVision();

	int vanguardNumberByVision;

	void updateLastCyclesAverageBallMeXYDifference();

	float lastCyclesAverageBallMeXDifference;

	float lastCyclesAverageBallMeYDifference;

	void updateClosestToBallOpponentNumberAndDistanceByVision();
	int closestToBallOpponentNumberByVision;
	float closestToBallOpponentDistanceByVision;

	void updateClosestToMeOpponentNumberAndDistanceByVision();
	int closestToMeOpponentNumberByVision;
	int closestToMeTeamNumberByVision;
	int nextclosestToMeTeamNumberByVision;
	float closestToMeOpponentDistanceByVision;
	float closestToMeTeamDistanceByVision;
	bool canDoLocalizationByTwoFlags;

	bool whetherLastCycleSeeBall;

	bool whetherLastCycleDoLocalizationByTwoFlags;

	int closestToVanguardOpponentNumber;

	float closestToVanguardOpponentDistance;

	void updateMyTeamMateAndOpponentPositionOfMyTeamMate();

	string messageToSayAboutPositon;

	void updateTeammateCoordinate();
	void updateOpponentCoordinate();

	void updateLastCyclesAverageTeammateCoordinate();
	void updateLastCyclesAverageOpponentCoordinate();

	int positionANumber;
	int positionBNumber;
	int positionCNumber;
	int positionDNumber;
	int positionENumber;

	bool isTeammateStandAToBall;
	bool isTeammateStandBToBall;
	bool isTeammateStandCToBall;
	bool isTeammateStandDToBall;
	bool isTeammateStandEToBall;
	Vector3 ball;

	PlayerHeadHigh playerHeadHigh;

	void UpdatePlayerHeadHigh();

	int closestToBallTeammateNumberByVision;
	float closestToBallTeammateDistanceByVision;

	void updateClosestToBallTeammateNumberAndDistanceByVision();

	void updateLastCyclesAverageAngleToBall();

	float lastCyclesAverageAngleToBall;
	float lastCyclesAverageAngleToBallArray[15];

	void updateDistanceAndAngleToBall();

	void updateRecordTeammateAndOpponentSenceMap();

	VisionObject lastCycleLocalizationFlag;

	void updateLastCyclesAverageHorizontalTurnHeadAngle();

	float lastCyclesAverageHorizontalTurnHeadAngleArray[5];

	float lastCyclesAverageHorizontalTurnHeadAngle;

	bool useLineDoLocalization;

	float getClosenessToBallMeasure(int number);///add by gaojin

public:
	float GetMyBodyAngleToBall();

	bool NewCanAttackOppGoal();

	float GetLastCyclesAverageTurnHeadAngle();

	bool WhetherCanAttackOppGoal2();
	bool WhetherCanAttackOppGoal();

	float GetLastCyclesAverageBallMeToXAxisAngle();

	float GetLastCyclesAverageBallGoalToXAxisAngle();

	float ConvertRadianIntoAngle( float angle);

	float GetBodyToX();

	float GetLastCyclesAverageBodyToXAngle();

	float GetMyDistanceToDestination(Vector3& destination);

	void JudgeFallDirection();

	float GetMyAngleToDestination(Vector3& destination);

	bool IsViceVanguard_1FallDown();

	bool IsViceVanguard_2FallDown();

	void SetViceVanguard_1FallDown(bool fallDown);

	///	bool WhetherCanShoot();

	///	bool CentreForwardWeatherCanShoot();

	int sssCounter;

	float FRP_Z1;
	float FRP_Z2;
	float FRP_Z3;

	float GYR1;
	float GYR2;
	float GYR3;

	float FRP_Y1;
	float FRP_Y2;
	float FRP_Y3;

	bool whetherStandedUp();

	float frpz,frpy;

	float gyrmod;

	bool MyDistanceToBallSmallerThanMyDistanceToAnyTeammate();

	bool GetCentreForwardToBallDistance(float& dis);

	bool GetLineBackerToBallDistance(float& dis);

	bool WhetherMyTeammatesBlockMe();
bool whetherTeamatMyDes(Vector3 Des);
	bool WhetherMyTeammatesBlockMe(int& teammateNumber);

	bool WhetherOpponentBlockMe(int& OpponentNumber);///by gaojin

	float WhetherOpponentInMyWayToDestination(Vector3 opponentCoordinate,Vector3 myCoordinate,Vector3 destination);

	void updateNowFallDirection();

	float GetLastCyclesAverageVerticalTurnHeadAngle();

	int GetVanguardNumberByVision();

	bool WhetherVanguardDownByVision();

	bool isBodyInDangerousState();

	Vector3 GetTeammateCoordinate(int num);

	Vector3 GetOpponentCoordinate(int num);

	float GetLastCyclesAverageBallMeXDifference();

	float GetLastCyclesAverageBallMeYDifference();

	int GetClosestToBallOpponentNumberByVision();
	float GetClosestToBallOpponentDistanceByVision();

	int GetClosestToMeTeamNumberByVision();
	int GetNextClosestToMeTeamNumberByVision();
	int GetClosestToMeOpponentNumberByVision();
	float GetClosestToMeOpponentDistanceByVision();

	bool CanDoLocalizationByTwoFlags();

	void SetFallDrection(FallDirection d);

	HorizonMoveDirection GetAdjustToGoalDirection();

	bool CanAttackOppGoal();

	bool dangerousDistanceToOpp();

	void updateClosestToVanguardOpponentNumberAndDistanceByVision();

	int GetClosestToVanguardOpponentNumberByVision();

	float GetClosestToVanguardOpponentDistanceByVision();

	bool IsTheBallOutOfShootArea();
	bool GetMyDistanceToMyGoalCenterSortedIndex(int& index);
	bool GetMyDistanceToBallSortedIndexOld(int& index);

	string GetTheMessageToSayAboutMyTeamMatePositon();

	bool EstimateWhetherUseHalfWalk();
	bool WhetherFaceToOppGoal();

	float GetMyDistanceToOpponent(int num);
	float GetMyHeadAngleToOpponent(int num);

	float GetMyBodyAngleToOpponent(int num);

	float GetMyBodyAngleToTeammate(int num);

public:
	void UpdateTeammateStandABCDE();

	bool WhetherTeammateStandNortheastToBall();
	bool WhetherTeammateStandBackToBall();
	bool WhetherTeammateStandNorthwestToBall();

	bool WhetherTeammateStandSoutheastToBall();

	bool WhetherTeammateStandSouthwestToBall();

	Vector3 GetNewTeammateCoordinate(int num);
	Vector3 GetNewOpponentCoordinate(int num);

	Vector3 GetNewAverageTeammateCoordinate(int num);
	Vector3 GetNewAverageOpponentCoordinate(int num);

	int GetPositionANumber();
	int GetPositionBNumber();
	int GetPositionCNumber();
	int GetPositionDNumber();
	int GetPositionENumber();
	float GetDistanceBetweenTwoCoordinate(Vector3,Vector3);

	bool PlayerWhetherFallDown(VisionObject player);

	bool WhetherCanPassFront();

	int GetClosestToBallTeammateNumberByVision();

	float GetClosestToBallTeammateDistanceByVision();

	float GetLastCyclesAverageAngleToBall();

	Vector3 GetPositionCoordinate(Position p);
	Vector3 GetPositionCoordinateForDefense(Position p);
	Vector3 GetPositionCoordinateForAttack(Position p);

	float WhetherTeammateInMyWayToDestination(Vector3 teammateCoordinate,Vector3 myCoordinate,Vector3 destination);
	float WhetherTeammateInMyWayToDestinationVANGUARD(Vector3 teammateCoordinate,Vector3 myCoordinate,Vector3 destination);

	Vector3 GetTheBallStopCoordinate();

	TPlayerSenseMap RecordTeamMateSenseMap;
	TPlayerSenseMap RecordOpponentSenseMap;

	float GetMyBodyAngleToCloserTeammate();

	void LocaLizationByLines(Vector3 &myCoordinate,VisionObject line1,VisionObject line2);

	void LocaLizationByGoalLine(Vector3& myCoordinate, VisionObject line ,VisionObject flag);

	float GetBallToMyGoalDistance();

	VisionObject GetLastCycleLocalizationFlag();

	bool WhetherDecideToPassBall();

	bool WhetherCanTurnToOpponentGoal();

	float getDistanceOppenentToBall(int num);

	float GetDestinationMeToXAxisAngle(Vector3 destination);

	float GetDestinationBallToXAxisAngle(Vector3 destination);///add by gaojin

	float GetLastCyclesAverageHorizontalTurnHeadAngle();

	///	TPlayerSenseMap TeamMateSenseMap;
}; //end class WorldModel

#endif//WORLDMODEL_H
