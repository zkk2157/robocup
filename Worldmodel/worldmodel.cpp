# include "worldmodel.h"

#include <iomanip>                ///czg
extern Perceptor messageParser;
extern Agent agent;
using namespace MonitorDraw;
using namespace Sensor;
///NewWalk newWalk;   ///lr

#define canloc

#define USE_LINE
#define SOME_CHANGE_TO_LINE
extern MDrawer CITMDrawer;
extern Configure CITConf;
extern Hear CITHear;
WorldModel::WorldModel()
{
	//the soccer specification of Robocup 2010 in singapore
	FieldLength = 30.0;
	FieldWidth = 20.0;
	FieldHeight = 40.0;
	GoalWidth = 2.1;
	GoalDepth = 0.6;
	GoalHeight = 0.8;
	PenaltyLength = 1.8;
	PenaltyWidth = 3.9;

	//the new soccer specification for ChinaOpen 2008

	ballRadius = 0.042;

	agentTheta = 0;
	myBodyToXAxisAngle = 0.0f;
	/**lr*/
	myHeadToXAxisAngle = 0.0f;
	agentPhi = 0;

	ballCoordinate = Vector3(0, 0, 0);

	myMiddleGoalCoordinate = Vector3(0, 0, 0);
	opponentMiddleGoalCoordinate = Vector3(0, 0, 0);

	myCurrentGameMode = PM_NONE;
	lastCycleGameMode = PM_NONE;
	myTeamIndex = TI_NONE;
	myLocalizationMethod = LOCALIZATION_NULL;
	myGameTime = 0;
	myServerTime = 0;
	myOpponentTeamName = "";
	myNumber = 0;

	myTeamName = "";
	myBeamCoordinate = Vector3(0, 0, 0);
	myCoordinate = Vector3(0, 0, 0);

	fallDown = false;
	vanguardFallDown = false;
	canLocalizeDirect = false;
	localizeByTurnHead = false;
	torsoHeightCounter = 1;
	fallDirection = D_NONE;
	myDistanceToBall = 0;
	myTeamScore = 0;
	opponentTeamScore = 0;
	myTeammateAmount = 0;

	localizationFlag_1 = VO_NULL;
	localizationFlag_2 = VO_NULL;

	myAngleToOppGoal = 0; ///lr
	/**lr*/
// 	vanguardFallDown=false;
// 	ViceVanguard_1FallDown=false;
// 	ViceVanguard_2FallDown=false;
// 	
// 		
	times = 4; ///add by czg
	for (int i = 0; i <= PLAYERNUMBER; ++i)
	{
		myTeammate[i].teamName = "";
		myTeammate[i].number = 0;
		myTeammate[i].coordinate = Vector3(0, 0, 0);
		myTeammate[i].distanceToBall = 0;
		myTeammate[i].distanceToMe = 0;
		myTeammate[i].fallDown = false;

		myOpponentTeamPlayer[i].teamName = "";
		myOpponentTeamPlayer[i].number = 0;
		myOpponentTeamPlayer[i].coordinate = Vector3(0, 0, 0);
		myOpponentTeamPlayer[i].distanceToBall = 0;
		myOpponentTeamPlayer[i].distanceToMe = 0;
		myOpponentTeamPlayer[i].fallDown = false;
	}

	///////ljj 
	averageOfLastCyclesGYR = Vector3(0, 0, 0);
	averageOfLastCyclesFRP_Lc = Vector3(0, 0, 0);
	averageOfLastCyclesFRP_Rc = Vector3(0, 0, 0);
	averageOfLastCyclesFRP_Lf = Vector3(0, 0, 0);
	averageOfLastCyclesFRP_Rf = Vector3(0, 0, 0);

	for (int i = 0; i < getLastCycles; i++)
	{
		//GYR
		gyr_sensor[i].x = 0;
		gyr_sensor[i].y = 0;
		gyr_sensor[i].z = 0;
		//FRP
		//L
		frp_senseMap_L[i].c.x = 0;
		frp_senseMap_L[i].c.y = 0;
		frp_senseMap_L[i].c.z = 0;

		frp_senseMap_L[i].f.x = 0;
		frp_senseMap_L[i].f.y = 0;
		frp_senseMap_L[i].f.z = 0;
		//R
		frp_senseMap_R[i].c.x = 0;
		frp_senseMap_R[i].c.y = 0;
		frp_senseMap_R[i].c.z = 0;

		frp_senseMap_R[i].f.x = 0;
		frp_senseMap_R[i].f.y = 0;
		frp_senseMap_R[i].f.z = 0;

	}

	/**        lr         */
	lastCyclesAverageBallCoordinate = Vector3(0, 0, 0);
	lastCyclesAverageMyCoordinate = Vector3(0, 0, 0);

	for (int i = 0; i < LASTCYCLESOFBALL; i++)
	{
		lastCyclesBallCoordinate[i] = Vector3(0, 0, 0);
		//	lastCyclesBallCoordinate[i].y=0;
		//	lastCyclesBallCoordinate[i].z=0;
	}

	for (int i = 0; i < LASTCYCLESOFMINE; i++)
	{
		lastCyclesMyCoordinate[i] = Vector3(0, 0, 0);
		///	///cout<<"lastCyclesMyCoordinate["<<i<<"]:"<<lastCyclesMyCoordinate[i]<<endl;
		//	lastCyclesMyCoordinate[i].y=0;
		//	lastCyclesMyCoordinate[i].z=0;
	}

//	my.resize(10000);

	/**
	 lastCyclesAverageTurnHeadAngle=0;

	 for(int i=0;i<LAST_CYCLES_OF_TURN_HEAD_ANGLE;i++)
	 {
	 lastCyclesMyCoordinate[i]=0;
	 }
	 */
	///////////
	SetupVisionObjectToPlayerMap();
	for (int i = 0; i < 5; i++)
		frp_Stat[i] = 56;

	canDoLocalizationByTwoFlags = false;

	my.reserve(5);
	for (int i = 0; i < 5; i++)
	{
		my.push_back(Vector3(0, 0, 0)); //增加一个元素
	}

	for (int i = 0; i < 9; i++)
	{
		newTeammateCoordinate[i] = Vector3(0, 0, 0);
		newOpponentCoordinate[i] = Vector3(100, 100, 0);
		for (int j = 0; j < 22; j++)
		{
			TeammateCoordinate[i][j] = Vector3(0, 0, 0);
			OpponentCoordinate[i][j] = Vector3(100, 100, 0);
		}
	}

	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			lastCyclesAverageTeammateCoordinate[i][j] = Vector3(0, 0, 0);
			lastCyclesAverageOpponentCoordinate[i][j] = Vector3(0, 0, 0);
		}
	}

	QuFront_back = new Queue(24);
	QuSideLeft_right = new Queue(24);
	QuFRP_Z = new Queue(24);

	QuFRP_Y = new Queue(24);

	ballCoor_X = new Queue(19);
	ballCoor_Y = new Queue(19);

}
void WorldModel::SetupVisionObjectToPlayerMap()
{
	mVisionObjectToPlayerMap.clear();
	mVisionObjectToPlayerMap["tmmt_1"] = TMMT_1;
	mVisionObjectToPlayerMap["tmmt_2"] = TMMT_2;
	mVisionObjectToPlayerMap["tmmt_3"] = TMMT_3;
	mVisionObjectToPlayerMap["tmmt_4"] = TMMT_4;
	mVisionObjectToPlayerMap["tmmt_5"] = TMMT_5;
	mVisionObjectToPlayerMap["tmmt_6"] = TMMT_6;
	mVisionObjectToPlayerMap["tmmt_7"] = TMMT_7;
	mVisionObjectToPlayerMap["tmmt_8"] = TMMT_8;
	mVisionObjectToPlayerMap["tmmt_9"] = TMMT_9;
	mVisionObjectToPlayerMap["tmmt_10"] = TMMT_10;
	mVisionObjectToPlayerMap["tmmt_11"] = TMMT_11;

	mVisionObjectToPlayerMap["oppo_1"] = OPPO_1;
	mVisionObjectToPlayerMap["oppo_2"] = OPPO_2;
	mVisionObjectToPlayerMap["oppo_3"] = OPPO_3;
	mVisionObjectToPlayerMap["oppo_4"] = OPPO_4;
	mVisionObjectToPlayerMap["oppo_5"] = OPPO_5;
	mVisionObjectToPlayerMap["oppo_6"] = OPPO_6;
	mVisionObjectToPlayerMap["oppo_7"] = OPPO_7;
	mVisionObjectToPlayerMap["oppo_8"] = OPPO_8;
	mVisionObjectToPlayerMap["oppo_9"] = OPPO_9;
	mVisionObjectToPlayerMap["oppo_10"] = OPPO_10;
	mVisionObjectToPlayerMap["oppo_11"] = OPPO_11;
}
void WorldModel::UpdateWorldModel()
{
	ball = GetLastCyclesAverageBallCoordinate();
//cout<<"111"<<endl;
	ballCoordinate = ball;
	//cout<<"22"<<endl;
	myCoordinate = GetMyCoordinate();
	//cout<<"333"<<endl;
	positionANumber = 0;
	positionBNumber = 0;
	positionCNumber = 0;
	positionDNumber = 0;
	positionENumber = 0;
	//cout<<"before 	UpdateEnvironmentInformation();"<<endl;
	UpdateEnvironmentInformation();
	//cout<<"update 	UpdateEnvironmentInformation();"<<endl;
	UpdateWorldState();
	//cout<<"update UpdateWorldState"<<endl;
	//OutputData();
	//cout<<"update wm"<<endl;
}
void WorldModel::OutputData()
{
#if 0
	/////cout<<"my coordinate:"<<myCoordinate<<endl;
	/////cout<<"my number:  "<<GetMyNumber()<<endl;
	/////cout<<"current play mode: "<<GetCurrentGameMode()<<endl;
	/////cout<<"my team side:"<<GetMyTeamIndex()<<endl;
	/////cout<<"current game time:"<<GetCurrentGameTime()<<endl;
	/////cout<<"current server time:"<<GetCurrentServerTime()<<endl;
	/////cout<<"my opponent team name:"<<GetMyOpponentTeamName()<<endl;
	/////cout<<"my team name:"<<GetMyTeamName()<<endl;
	/////cout<<"my beam coordinate:"<<GetMyBeamCoordinate()<<endl;
	/////cout<<"ball coordinate:"<<GetBallCoordinate()<<endl;
	/////cout<<"my distance to ball:"<<GetMyDistanceToBall()<<endl;
	/////cout<<"me team score:"<<GetMyTeamScore()<<endl;
	/////cout<<"opponent team score:"<<GetOpponentTeamScore()<<endl;
#endif
#if 0
	/////cout<<"-------my teammate information---------"<<endl;
	for(int i=1;i<=11;++i)
	{
		if(myTeammate[i].number == 0)
		continue;
		else
		{
			///////cout<<"****the "<<i<<"th teammate****"<<endl;
			/////cout<<"team name: "<<myTeammate[i].teamName<<endl;
			/////cout<<"number: "<<myTeammate[i].number<<endl;
			/////cout<<"coordinate: "<<myTeammate[i].coordinate<<endl;
			/////cout<<"distance to ball: "<<myTeammate[i].distanceToBall<<endl;
			/////cout<<"distance to me: "<<myTeammate[i].distanceToMe<<endl;
		}
		/////cout<<"================="<<endl;
	}
	/////cout<<"--------end--------------"<<endl<<endl<<endl<<endl;
#endif
#if 0
	/////cout<<"-------my opponent team information---------"<<endl;
	for(int i=1;i<=11;++i)
	{
		if(myOpponentTeamPlayer[i].number == 0)
		continue;
		else
		{
			/////cout<<"team name: "<<myOpponentTeamPlayer[i].teamName<<endl;
			/////cout<<"number: "<<myOpponentTeamPlayer[i].number<<endl;
			/////cout<<"coordinate: "<<myOpponentTeamPlayer[i].coordinate<<endl;
			/////cout<<"distance to ball: "<<myOpponentTeamPlayer[i].distanceToBall<<endl;
			/////cout<<"distance to me: "<<myOpponentTeamPlayer[i].distanceToMe<<endl;
		}
		/////cout<<"================="<<endl;
	}
	/////cout<<"--------end--------------"<<endl<<endl<<endl<<endl;
#endif
#if 0
	/////cout<<"tmmt_1: "<<mObjectPosMap[TMMT_1]<<endl;
	/////cout<<"tmmt_2: "<<mObjectPosMap[TMMT_2]<<endl;
	/////cout<<"tmmt_3: "<<mObjectPosMap[TMMT_3]<<endl;
	/////cout<<"tmmt_4: "<<mObjectPosMap[TMMT_4]<<endl;
	/////cout<<"tmmt_5: "<<mObjectPosMap[TMMT_5]<<endl;
	/////cout<<"tmmt_6: "<<mObjectPosMap[TMMT_6]<<endl;
	/////cout<<"tmmt_7: "<<mObjectPosMap[TMMT_7]<<endl;
	/////cout<<"tmmt_8: "<<mObjectPosMap[TMMT_8]<<endl;
	/////cout<<"tmmt_9: "<<mObjectPosMap[TMMT_9]<<endl;
	/////cout<<"tmmt_10: "<<mObjectPosMap[TMMT_10]<<endl;
	/////cout<<"tmmt_11: "<<mObjectPosMap[TMMT_11]<<endl;
	/////cout<<"==================================="<<endl;
#endif
}
void WorldModel::UpdateEnvironmentInformation()
{
	UpdateSoccerFlagCoordinate();
	UpdateMiddleGoalCoordinate();
	UpdateTeamIndex();
	UpdateOpponentTeamName();
	UpdateMyTeamName();
	UpdateMyNumber();
//sim	UpdateMyBeamCoordinate();
}
void WorldModel::UpdateWorldState()
{
	RecordFlagSenseMsg();

///	updateLastCyclesAverageVerticalTurnHeadAngle();///lr

//sim	CalculateGyr();              ///czg
	//RecordTeammateSenseMsg();

//sim	EvaluateVisionSenseMsg();

	//EvaluateTeammateSenseMsg();

//sim	ConvertVisionInformation();

	UpdateGameMode();

	UpdateGameTime();

	UpdateServerTime();

	UpdateVanguard();

//sim	UpdateMyTeamScore();

//sim	UpdateOpponentTeamScore();

	Localization();

	UpdateMyBodyToXAxisAngle();

///	updateLastCyclesAverageBodyToXAngle();

	UpdateBallCoordinate();

	//      RecordTeammatePos();			///add by czg

//	RecordOpponentPos();			///add by czg

	UpdateMyDistanceToBall();

///	updateLastCyclesAverageAngleToBall();

	UpdateLastCyclesAverageGYR();

	UpdateLastCyclesAverageFRP();

	/**            lr          */

	updateLastCyclesAverageMyCoordinate();

	updateLastCyclesAverageBallCoordinate();

	updateMyBodyAngleToBall();

//sim	updateLastCyclesAverageBallMeToXAxisAngle();

	updateLastCyclesAverageBallGoalToXAxisAngle();

	updateVanguardNumberByVision();
	UpdateTeammateStandABCDE();

///	updateTheBodyBalanceState();

	updateLastCyclesAverageBallMeXYDifference();

///	updateClosestToBallOpponentNumberAndDistanceByVision();

///	updateClosestToBallTeammateNumberAndDistanceByVision();

///	updateClosestToMeOpponentNumberAndDistanceByVision();

///	updateClosestToVanguardOpponentNumberAndDistanceByVision();

//sim	updateMyTeamMateAndOpponentPositionOfMyTeamMate();

	updateTeammateCoordinate();

	updateLastCyclesAverageTeammateCoordinate();

	updateOpponentCoordinate();

	updateLastCyclesAverageOpponentCoordinate();

	UpdatePlayerHeadHigh();

//sim	updateDistanceAndAngleToBall();

	updateLastCyclesAverageHorizontalTurnHeadAngle();

///	updateRecordTeammateAndOpponentSenceMap();

///	UpdateViceVanguard_1();
///	JudgeFallDirection();
//	updateDestinationCoordinate();
///	updateLastCyclesAverageHeadAngle();
///	updateAngleBetweenBallMeAndBallOppGoal();

}
void WorldModel::UpdateSoccerFlagCoordinate()
{
	float x = FieldLength / 2.0;
	float yF = FieldWidth / 2.0;
	float yG = GoalWidth / 2.0;
	float z = 0.0;
	if (messageParser.GetMyTeamIndex() == TI_LEFT)
	{
		mObjectPosMap[VO_FLAG1_L] = Vector3(-x, yF, z);

		mObjectPosMap[VO_FLAG2_L] = Vector3(-x, -yF, z);

		mObjectPosMap[VO_FLAG1_R] = Vector3(x, yF, z);

		mObjectPosMap[VO_FLAG2_R] = Vector3(x, -yF, z);

		z = GoalHeight;
		mObjectPosMap[VO_GOAL1_L] = Vector3(-x, yG, z);

		mObjectPosMap[VO_GOAL2_L] = Vector3(-x, -yG, z);

		mObjectPosMap[VO_GOAL1_R] = Vector3(x, yG, z);

		mObjectPosMap[VO_GOAL2_R] = Vector3(x, -yG, z);

	}
	else
	{
		mObjectPosMap[VO_FLAG1_L] = Vector3(x, -yF, z);

		mObjectPosMap[VO_FLAG2_L] = Vector3(x, yF, z);

		mObjectPosMap[VO_FLAG1_R] = Vector3(-x, -yF, z);

		mObjectPosMap[VO_FLAG2_R] = Vector3(-x, yF, z);

		z = GoalHeight;
		mObjectPosMap[VO_GOAL1_L] = Vector3(x, -yG, z);

		mObjectPosMap[VO_GOAL2_L] = Vector3(x, yG, z);

		mObjectPosMap[VO_GOAL1_R] = Vector3(-x, -yG, z);

		mObjectPosMap[VO_GOAL2_R] = Vector3(-x, yG, z);
	}
}
void WorldModel::UpdateMiddleGoalCoordinate()
{
	float x;
	x = FieldLength / 2.0f;
	myMiddleGoalCoordinate = Vector3(-x, 0, 0);
	opponentMiddleGoalCoordinate = Vector3(x, 0, 0);
}
void WorldModel::UpdateTeamIndex()
{
	myTeamIndex = messageParser.GetMyTeamIndex();
}
void WorldModel::UpdateOpponentTeamName()
{
	myOpponentTeamName = messageParser.GetOpponetTeamName();
}

void WorldModel::UpdateMyTeamName()
{
	myTeamName = agent.GetTeamName();
}
void WorldModel::UpdateMyNumber()
{
	myNumber = messageParser.GetMyNumber();
}
void WorldModel::UpdateMyBeamCoordinate()
{
	myBeamCoordinate = agent.GetBeamPos();
}

void WorldModel::UpdateVanguard()
{
	if (!messageParser.ParsevanguardNum())
		return;
//	vanguardNum=vannumber;
	vanguardNum = messageParser.GetVanguardNumber();
//	/////cout<<"vanguardNum           "<<vanguardNum<<endl;
	vanguardFallDown = messageParser.vanguardFallDown;
	//vanguradLoseBall=messageParser.vanguradLoseBall;
}

void WorldModel::UpdateGameMode()
{
	if (myCurrentGameMode != messageParser.GetCurrentGameMode())
	{
		//cout << "Change myCurrentGameMode" << endl;
		lastCycleGameMode = myCurrentGameMode;
		myCurrentGameMode = messageParser.GetCurrentGameMode();
	}
	//lastCycleGameMode=myCurrentGameMode;
	//myCurrentGameMode=messageParser.GetCurrentGameMode();
}

void WorldModel::UpdateGameTime()
{
	myGameTime = messageParser.GetGameTime();
}
void WorldModel::UpdateServerTime()
{
	myServerTime = messageParser.GetServerTime();
}

void WorldModel::Localization() ///add by czg
{
#if 1
	useLineDoLocalization = false;
	//canLocalizeDirect=true;
	//localization with two flags
	VisionSense flag_1, flag_2;
	float d1 = 0.0f, d2 = 0.0f, d3 = 0.0f, phi1, phi2, jointangle, jointangle1;
	float x, y, theta, temp, flag_y;
	Vector3 pos1, pos2, vanpos;
	localizeSenseMap = messageParser.mVisionSenseMap;
	jointangle = GetCurrentJointAngle(JID_HEAD_2);
	jointangle1 = GetCurrentJointAngle(JID_HEAD_1);

	/////cout<<"jointangle1:"<<jointangle1<<endl;

#if 0
// 	VO_FLAG1_L =0,
// 	VO_FLAG2_L =1,
// 	VO_FLAG1_R =2,
// 	VO_FLAG2_R =3,
// 
// 	VO_GOAL1_L =4,
// 	VO_GOAL2_L =5,
// 	VO_GOAL1_R =6,
// 	VO_GOAL2_R =7,
#endif
	float Min = 100, Max;
	for (int i = 0; i < 8; i++)
		thetaindex[i] = 0;

	int k = 10, l = 10;
	/*
	 if( localizeSenseMap.count(VO_FLAG1_L) )
	 thetaindex[VO_FLAG1_L]=fabs(localizeSenseMap[VO_FLAG1_L].theta);
	 if( localizeSenseMap.count(VO_FLAG2_L) )
	 thetaindex[VO_FLAG2_L]=fabs(localizeSenseMap[VO_FLAG2_L].theta);
	 if( localizeSenseMap.count(VO_FLAG1_R) )
	 thetaindex[VO_FLAG1_R]=fabs(localizeSenseMap[VO_FLAG1_R].theta);
	 if( localizeSenseMap.count(VO_FLAG2_R) )
	 thetaindex[VO_FLAG2_R]=fabs(localizeSenseMap[VO_FLAG2_R].theta);



	 if( localizeSenseMap.count(VO_GOAL1_L) )
	 thetaindex[VO_GOAL1_L]=fabs(localizeSenseMap[VO_GOAL1_L].theta);
	 if( localizeSenseMap.count(VO_GOAL2_L) )
	 thetaindex[VO_GOAL2_L]=fabs(localizeSenseMap[VO_GOAL2_L].theta);
	 if( localizeSenseMap.count(VO_GOAL1_R) )
	 thetaindex[VO_GOAL1_R]=fabs(localizeSenseMap[VO_GOAL1_R].theta);
	 if( localizeSenseMap.count(VO_GOAL2_R) )
	 thetaindex[VO_GOAL2_R]=fabs(localizeSenseMap[VO_GOAL2_R].theta);
	 */
	if (localizeSenseMap[VO_FLAG1_L].phi != 0)
		thetaindex[VO_FLAG1_L] = fabs(localizeSenseMap[VO_FLAG1_L].theta);
	if (localizeSenseMap[VO_FLAG2_L].phi != 0)
		thetaindex[VO_FLAG2_L] = fabs(localizeSenseMap[VO_FLAG2_L].theta);
	if (localizeSenseMap[VO_FLAG1_R].phi != 0)
		thetaindex[VO_FLAG1_R] = fabs(localizeSenseMap[VO_FLAG1_R].theta);
	if (localizeSenseMap[VO_FLAG2_R].phi != 0)
		thetaindex[VO_FLAG2_R] = fabs(localizeSenseMap[VO_FLAG2_R].theta);

	if (localizeSenseMap[VO_GOAL1_L].phi != 0)
		thetaindex[VO_GOAL1_L] = fabs(localizeSenseMap[VO_GOAL1_L].theta);
	if (localizeSenseMap[VO_GOAL2_L].phi != 0)
		thetaindex[VO_GOAL2_L] = fabs(localizeSenseMap[VO_GOAL2_L].theta);
	if (localizeSenseMap[VO_GOAL1_R].phi != 0)
		thetaindex[VO_GOAL1_R] = fabs(localizeSenseMap[VO_GOAL1_R].theta);
	if (localizeSenseMap[VO_GOAL2_R].phi != 0)
		thetaindex[VO_GOAL2_R] = fabs(localizeSenseMap[VO_GOAL2_R].theta);
	for (int i = 0; i < 8; i++)
	{

		if (Min > thetaindex[i] && thetaindex[i] > 0)
		{
			Min = thetaindex[i];
			k = i;
		}
	}
	Min = 100;
	Max = -100;

	/*
	 if( localizeSenseMap.count(VO_FLAG1_L) )
	 thetaindex[VO_FLAG1_L]=localizeSenseMap[VO_FLAG1_L].theta;
	 if( localizeSenseMap.count(VO_FLAG2_L) )
	 thetaindex[VO_FLAG2_L]=localizeSenseMap[VO_FLAG2_L].theta;
	 if( localizeSenseMap.count(VO_FLAG1_R) )
	 thetaindex[VO_FLAG1_R]=localizeSenseMap[VO_FLAG1_R].theta;
	 if( localizeSenseMap.count(VO_FLAG2_R) )
	 thetaindex[VO_FLAG2_R]=localizeSenseMap[VO_FLAG2_R].theta;



	 if( localizeSenseMap.count(VO_GOAL1_L) )
	 thetaindex[VO_GOAL1_L]=localizeSenseMap[VO_GOAL1_L].theta;
	 if( localizeSenseMap.count(VO_GOAL2_L) )
	 thetaindex[VO_GOAL2_L]=localizeSenseMap[VO_GOAL2_L].theta;
	 if( localizeSenseMap.count(VO_GOAL1_R) )
	 thetaindex[VO_GOAL1_R]=localizeSenseMap[VO_GOAL1_R].theta;
	 if( localizeSenseMap.count(VO_GOAL2_R) )
	 thetaindex[VO_GOAL2_R]=localizeSenseMap[VO_GOAL2_R].theta;
	 */

	if (localizeSenseMap[VO_FLAG1_L].phi != 0)
		thetaindex[VO_FLAG1_L] = localizeSenseMap[VO_FLAG1_L].theta;
	if (localizeSenseMap[VO_FLAG2_L].phi != 0)
		thetaindex[VO_FLAG2_L] = localizeSenseMap[VO_FLAG2_L].theta;
	if (localizeSenseMap[VO_FLAG1_R].phi != 0)
		thetaindex[VO_FLAG1_R] = localizeSenseMap[VO_FLAG1_R].theta;
	if (localizeSenseMap[VO_FLAG2_R].phi != 0)
		thetaindex[VO_FLAG2_R] = localizeSenseMap[VO_FLAG2_R].theta;

	if (localizeSenseMap[VO_GOAL1_L].phi != 0)
		thetaindex[VO_GOAL1_L] = localizeSenseMap[VO_GOAL1_L].theta;
	if (localizeSenseMap[VO_GOAL2_L].phi != 0)
		thetaindex[VO_GOAL2_L] = localizeSenseMap[VO_GOAL2_L].theta;
	if (localizeSenseMap[VO_GOAL1_R].phi != 0)
		thetaindex[VO_GOAL1_R] = localizeSenseMap[VO_GOAL1_R].theta;
	if (localizeSenseMap[VO_GOAL2_R].phi != 0)
		thetaindex[VO_GOAL2_R] = localizeSenseMap[VO_GOAL2_R].theta;

	/*add by czg */
	for (int i = 0; i < 8; i++)
	{
		if (thetaindex[k] > 0)
		{
			if (Max < thetaindex[i] && i != k && thetaindex[i] < 0)
			{
				Max = thetaindex[i];
				l = i;
			}
		}
		else
		{
			if (Min > thetaindex[i] && i != k && thetaindex[i] > 0)
			{
				Min = thetaindex[i];
				l = i;
			}
		}
	}

	Max = -100;
	Min = 100;
	if (l == 10)
		for (int i = 0; i < 8; i++)
		{

			if (thetaindex[k] > 0)
			{
				if (Min > thetaindex[i] && i != k && thetaindex[i] > 0)
				{
					Min = thetaindex[i];
					l = i;
				}
			}
			else
			{
				if (Max < thetaindex[i] && i != k && thetaindex[i] < 0)
				{
					Max = thetaindex[i];
					l = i;
				}
			}
		}

	locflag[0] = k;
	locflag[1] = l;

#if 1				//add by czg
	if ((k == VO_GOAL1_R && l == VO_GOAL2_R)
			|| (l == VO_GOAL1_R && k == VO_GOAL2_R)) //1
	{ //localize by goal1_r and goal2_r
	  ///cout<<"localize by goal1_r and goal2_r"<<endl;
		flag_1 = localizeSenseMap[VO_GOAL1_R];
		flag_2 = localizeSenseMap[VO_GOAL2_R];
		localizationFlag_1 = VO_GOAL1_R;
		localizationFlag_2 = VO_GOAL2_R;

		lastCycleLocalizationFlag = localizationFlag_1; ///for turn head strategy

		phi1 = flag_1.phi;
		phi2 = flag_2.phi;
// 		///////cout<<"phi1"<<phi1<<endl;
// 		///////cout<<"phi2"<<phi2<<endl;
		phi1 = ConvertAngleIntoRadian(jointangle + phi1);
		phi2 = ConvertAngleIntoRadian(jointangle + phi2);

		d1 = flag_1.distance * cos(phi1);
		d2 = flag_2.distance * cos(phi2);
		d3 = GetGoalWidth();

// 		///////cout<<"d1	"<<d1<<endl;
// 		///////cout<<"d2	"<<d2<<endl;
// 		///////cout<<"d3	"<<d3<<endl;
		pos1 = mObjectPosMap[VO_GOAL1_R];
		pos2 = mObjectPosMap[VO_GOAL2_R];

		myLocalizationMethod = LOCALIZATION_RIGHT;
		canLocalizeDirect = true;

		canDoLocalizationByTwoFlags = true;
#ifdef canloc
		/////cout<<"localized by VO_GOAL1_R and VO_GOAL2_R"<<endl;
#endif
		if ((myBodyToXAxisAngle > -200) && (myBodyToXAxisAngle < 200))
		{
			gyroz = myBodyToXAxisAngle;
		}
	}
	else if ((k == VO_GOAL1_R && l == VO_FLAG1_R)
			|| (l == VO_GOAL1_R && k == VO_FLAG1_R)) //2
	{ //localize by goal1_r and flag1_r
	  ///cout<<"localize by goal1_r and flag1_r"<<endl;
#ifdef SOME_CHANGE_TO_LINE
		if (messageParser.mLineSenseMap[LI_SIDE_P].updated
				&& messageParser.mLineSenseMap[LI_GOAL_R].updated)
		{
			LocaLizationByLines(myCoordinate, LI_SIDE_P, LI_GOAL_R);
			myLocalizationMethod = LOCALIZATION_RIGHT;
			canLocalizeDirect = true;
			canDoLocalizationByTwoFlags = true;
			localizationFlag_1 = VO_GOAL1_R;
			localizationFlag_2 = VO_FLAG1_R;

			lastCycleLocalizationFlag = localizationFlag_1; ///for turn head strategy

			///cout<<"change to line location!!"<<endl;
			if (canLocalizeDirect)
			{
				///cout<<"I can localize my self directly! ~~~~~~~~ "<<"localizationFlag_1:"<<localizationFlag_1<<" ~~~~~~~~~~~~~~~~~~:-)"<<endl;
			}
			else
			{
				///cout<<"I can not localize my self directly! ~~~~~~~~~~~~~~~~~~~~~~:-("<<endl;
			}
			return;
		}
#endif
		flag_1 = localizeSenseMap[VO_GOAL1_R];
		flag_2 = localizeSenseMap[VO_FLAG1_R];
		localizationFlag_1 = VO_GOAL1_R;
		localizationFlag_2 = VO_FLAG1_R;

		lastCycleLocalizationFlag = localizationFlag_1; ///for turn head strategy

		phi1 = flag_1.phi;
		phi2 = flag_2.phi;

		phi1 = ConvertAngleIntoRadian(jointangle + phi1);
		phi2 = ConvertAngleIntoRadian(jointangle + phi2);

		d1 = flag_1.distance * cos(phi1);
		d2 = flag_2.distance * cos(phi2);
		d3 = (GetFieldWidth() / 2) - (GetGoalWidth() / 2);
		pos1 = mObjectPosMap[VO_GOAL1_R];

		pos2 = mObjectPosMap[VO_FLAG1_R];

		myLocalizationMethod = LOCALIZATION_RIGHT;
		canLocalizeDirect = true;

		canDoLocalizationByTwoFlags = true;
#ifdef canloc
		/////cout<<"localized by VO_GOAL1_R and VO_FLAG1_R"<<endl;
#endif
		if ((myBodyToXAxisAngle > -200) && (myBodyToXAxisAngle < 200))
		{
			gyroz = myBodyToXAxisAngle;
		}

	}
	else if ((k == VO_FLAG2_R && l == VO_GOAL2_R)
			|| (l == VO_FLAG2_R && k == VO_GOAL2_R)) //3
	{ //localize by goal2_r and flag2_rUpdateVanguard
	  ///cout<<"localize by goal2_r and flag2_r"<<endl;
#ifdef SOME_CHANGE_TO_LINE
		if (messageParser.mLineSenseMap[LI_SIDE_N].updated
				&& messageParser.mLineSenseMap[LI_GOAL_R].updated)
		{
			LocaLizationByLines(myCoordinate, LI_SIDE_N, LI_GOAL_R);
			myLocalizationMethod = LOCALIZATION_RIGHT;
			canLocalizeDirect = true;
			canDoLocalizationByTwoFlags = true;
			localizationFlag_1 = VO_GOAL2_R;
			localizationFlag_2 = VO_FLAG2_R;

			lastCycleLocalizationFlag = localizationFlag_1; ///for turn head strategy

			///cout<<"change to line location!!"<<endl;
			if (canLocalizeDirect)
			{
				///cout<<"I can localize my self directly! ~~~~~~~~ "<<"localizationFlag_1:"<<localizationFlag_1<<" ~~~~~~~~~~~~~~~~~~:-)"<<endl;
			}
			else
			{
				///cout<<"I can not localize my self directly! ~~~~~~~~~~~~~~~~~~~~~~:-("<<endl;
			}
			return;
		}
#endif
		flag_1 = localizeSenseMap[VO_GOAL2_R];
		flag_2 = localizeSenseMap[VO_FLAG2_R];
		localizationFlag_1 = VO_GOAL2_R;
		localizationFlag_2 = VO_FLAG2_R;

		lastCycleLocalizationFlag = localizationFlag_1; ///for turn head strategy

		phi1 = flag_1.phi;
		phi2 = flag_2.phi;

		phi1 = ConvertAngleIntoRadian(jointangle + phi1);
		phi2 = ConvertAngleIntoRadian(jointangle + phi2);

		d1 = flag_1.distance * cos(phi1);
		d2 = flag_2.distance * cos(phi2);
		d3 = (GetFieldWidth() / 2) - (GetGoalWidth() / 2);

		pos1 = mObjectPosMap[VO_GOAL2_R];

		pos2 = mObjectPosMap[VO_FLAG2_R];

		myLocalizationMethod = LOCALIZATION_RIGHT;
		canLocalizeDirect = true;

		canDoLocalizationByTwoFlags = true;
#ifdef canloc
		/////cout<<"localized by VO_GOAL2_R and VO_FLAG2_R"<<endl;
#endif
		if ((myBodyToXAxisAngle > -200) && (myBodyToXAxisAngle < 200))
		{
			gyroz = myBodyToXAxisAngle;
		}
	}
	else if ((k == VO_GOAL1_L && l == VO_GOAL2_L)
			|| (l == VO_GOAL1_L && k == VO_GOAL2_L)) //4
	{ //localize by goal1_l and goal2_l
	  ///cout<<"localize by goal1_l and goal2_l"<<endl;
		flag_1 = localizeSenseMap[VO_GOAL1_L];
		flag_2 = localizeSenseMap[VO_GOAL2_L];
		localizationFlag_1 = VO_GOAL1_L;
		localizationFlag_2 = VO_GOAL2_L;

		lastCycleLocalizationFlag = localizationFlag_1; ///for turn head strategy

		phi1 = flag_1.phi;
		phi2 = flag_2.phi;

		phi1 = ConvertAngleIntoRadian(jointangle + phi1);
		phi2 = ConvertAngleIntoRadian(jointangle + phi2);

		d1 = flag_1.distance * cos(phi1);
		d2 = flag_2.distance * cos(phi2);
		d3 = GetGoalWidth();

		pos1 = mObjectPosMap[VO_GOAL1_L];

		pos2 = mObjectPosMap[VO_GOAL2_L];

		myLocalizationMethod = LOCALIZATION_LEFT;
		canLocalizeDirect = true;

		canDoLocalizationByTwoFlags = true;
#ifdef canloc
		/////cout<<"localized by VO_GOAL1_L and VO_GOAL2_L"<<endl;
#endif
		if ((myBodyToXAxisAngle > -200) && (myBodyToXAxisAngle < 200))
		{
			gyroz = myBodyToXAxisAngle;
		}
	}
	else if ((k == VO_FLAG1_L && l == VO_GOAL1_L)
			|| (l == VO_FLAG1_L && k == VO_GOAL1_L)) //5
	{ //localize by flag1_l and goal1_l
	  ///cout<<"localize by flag1_l and goal1_l"<<endl;
#ifdef SOME_CHANGE_TO_LINE
		if (messageParser.mLineSenseMap[LI_SIDE_P].updated
				&& messageParser.mLineSenseMap[LI_GOAL_L].updated)
		{
			LocaLizationByLines(myCoordinate, LI_SIDE_P, LI_GOAL_L);
			myLocalizationMethod = LOCALIZATION_LEFT;
			canLocalizeDirect = true;
			canDoLocalizationByTwoFlags = true;
			localizationFlag_1 = VO_GOAL1_L;
			localizationFlag_2 = VO_FLAG1_L;

			lastCycleLocalizationFlag = localizationFlag_1; ///for turn head strategy

			///cout<<"change to line location!!"<<endl;
			if (canLocalizeDirect)
			{
				///cout<<"I can localize my self directly! ~~~~~~~~ "<<"localizationFlag_1:"<<localizationFlag_1<<" ~~~~~~~~~~~~~~~~~~:-)"<<endl;
			}
			else
			{
				///cout<<"I can not localize my self directly! ~~~~~~~~~~~~~~~~~~~~~~:-("<<endl;
			}
			return;
		}
#endif

		flag_1 = localizeSenseMap[VO_GOAL1_L];
		flag_2 = localizeSenseMap[VO_FLAG1_L];
		localizationFlag_1 = VO_GOAL1_L;
		localizationFlag_2 = VO_FLAG1_L;

		lastCycleLocalizationFlag = localizationFlag_1; ///for turn head strategy

		phi1 = flag_1.phi;
		phi2 = flag_2.phi;

		phi1 = ConvertAngleIntoRadian(jointangle + phi1);
		phi2 = ConvertAngleIntoRadian(jointangle + phi2);

		d1 = flag_1.distance * cos(phi1);
		d2 = flag_2.distance * cos(phi2);
		d3 = (GetFieldWidth() / 2) - (GetGoalWidth() / 2);

		pos1 = mObjectPosMap[VO_GOAL1_L];

		pos2 = mObjectPosMap[VO_FLAG1_L];

		myLocalizationMethod = LOCALIZATION_LEFT;
		canLocalizeDirect = true;

		canDoLocalizationByTwoFlags = true;
#ifdef canloc
		/////cout<<"localized by VO_FLAG1_L and VO_GOAL1_L"<<endl;
#endif
		if ((myBodyToXAxisAngle > -200) && (myBodyToXAxisAngle < 200))
		{
			gyroz = myBodyToXAxisAngle;
		}
	}
	else if ((k == VO_FLAG2_L && l == VO_GOAL2_L)
			|| (l == VO_FLAG2_L && k == VO_GOAL2_L)) //6
	{ //localize by flag2_l and goal2_l
	  ///cout<<"localize by flag2_l and goal2_l"<<endl;
#ifdef SOME_CHANGE_TO_LINE
		if (messageParser.mLineSenseMap[LI_SIDE_N].updated
				&& messageParser.mLineSenseMap[LI_GOAL_L].updated)
		{
			LocaLizationByLines(myCoordinate, LI_SIDE_N, LI_GOAL_L);
			myLocalizationMethod = LOCALIZATION_LEFT;
			canLocalizeDirect = true;
			canDoLocalizationByTwoFlags = true;
			localizationFlag_1 = VO_GOAL2_L;
			localizationFlag_2 = VO_FLAG2_L;

			lastCycleLocalizationFlag = localizationFlag_1; ///for turn head strategy

			///cout<<"change to line location!!"<<endl;
			if (canLocalizeDirect)
			{
				///cout<<"I can localize my self directly! ~~~~~~~~ "<<"localizationFlag_1:"<<localizationFlag_1<<" ~~~~~~~~~~~~~~~~~~:-)"<<endl;
			}
			else
			{
				///cout<<"I can not localize my self directly! ~~~~~~~~~~~~~~~~~~~~~~:-("<<endl;
			}
			return;
		}
#endif
		flag_1 = localizeSenseMap[VO_GOAL2_L];
		flag_2 = localizeSenseMap[VO_FLAG2_L];
		localizationFlag_1 = VO_GOAL2_L;
		localizationFlag_2 = VO_FLAG2_L;

		lastCycleLocalizationFlag = localizationFlag_1; ///for turn head strategy

		phi1 = flag_1.phi;
		phi2 = flag_2.phi;

		phi1 = ConvertAngleIntoRadian(jointangle + phi1);
		phi2 = ConvertAngleIntoRadian(jointangle + phi2);

		d1 = flag_1.distance * cos(phi1);
		d2 = flag_2.distance * cos(phi2);
		d3 = (GetFieldWidth() / 2) - (GetGoalWidth() / 2);

		pos1 = mObjectPosMap[VO_GOAL2_L];

		pos2 = mObjectPosMap[VO_FLAG2_L];

		myLocalizationMethod = LOCALIZATION_LEFT;
		canLocalizeDirect = true;

		canDoLocalizationByTwoFlags = true;
#ifdef canloc
		/////cout<<"localized by VO_FLAG2_L and VO_GOAL2_L"<<endl;
#endif
		if ((myBodyToXAxisAngle > -200) && (myBodyToXAxisAngle < 200))
		{
			gyroz = myBodyToXAxisAngle;
		}
	}
	else if ((k == VO_FLAG1_L && l == VO_FLAG1_R)
			|| (l == VO_FLAG1_L && k == VO_FLAG1_R)) //7
	{ //localize by flag1_l and flag1_r
	  ///cout<<"localize by flag1_l and flag1_r"<<endl;
#ifdef SOME_CHANGE_TO_LINE
		if (messageParser.mVisionSenseMap[VO_FLAG1_L].distance
				< messageParser.mVisionSenseMap[VO_FLAG1_R].distance)
		{
			if (messageParser.mLineSenseMap[LI_SIDE_P].updated
					&& messageParser.mLineSenseMap[LI_GOAL_L].updated)
			{
				LocaLizationByLines(myCoordinate, LI_SIDE_P, LI_GOAL_L);
				myLocalizationMethod = LOCALIZATION_TOP;
				canLocalizeDirect = true;
				canDoLocalizationByTwoFlags = true;
				localizationFlag_1 = VO_FLAG1_L;
				localizationFlag_2 = VO_FLAG1_R;

				lastCycleLocalizationFlag = localizationFlag_1; ///for turn head strategy

				///cout<<"change to line location!!"<<endl;
				if (canLocalizeDirect)
				{
					///cout<<"I can localize my self directly! ~~~~~~~~ "<<"localizationFlag_1:"<<localizationFlag_1<<" ~~~~~~~~~~~~~~~~~~:-)"<<endl;
				}
				else
				{
					///cout<<"I can not localize my self directly! ~~~~~~~~~~~~~~~~~~~~~~:-("<<endl;
				}
				return;
			}
		}
		else
		{
			if (messageParser.mLineSenseMap[LI_SIDE_P].updated
					&& messageParser.mLineSenseMap[LI_GOAL_R].updated)
			{
				LocaLizationByLines(myCoordinate, LI_SIDE_P, LI_GOAL_R);
				myLocalizationMethod = LOCALIZATION_TOP;
				canLocalizeDirect = true;
				canDoLocalizationByTwoFlags = true;
				localizationFlag_1 = VO_FLAG1_L;
				localizationFlag_2 = VO_FLAG1_R;

				lastCycleLocalizationFlag = localizationFlag_1; ///for turn head strategy

				///cout<<"change to line location!!"<<endl;
				if (canLocalizeDirect)
				{
					///cout<<"I can localize my self directly! ~~~~~~~~ "<<"localizationFlag_1:"<<localizationFlag_1<<" ~~~~~~~~~~~~~~~~~~:-)"<<endl;
				}
				else
				{
					///cout<<"I can not localize my self directly! ~~~~~~~~~~~~~~~~~~~~~~:-("<<endl;
				}
				return;
			}
		}
#endif

		flag_1 = localizeSenseMap[VO_FLAG1_L];
		flag_2 = localizeSenseMap[VO_FLAG1_R];
		localizationFlag_1 = VO_FLAG1_L;
		localizationFlag_2 = VO_FLAG1_R;

		lastCycleLocalizationFlag = localizationFlag_1; ///for turn head strategy

		phi1 = flag_1.phi;
		phi2 = flag_2.phi;

		phi1 = ConvertAngleIntoRadian(jointangle + phi1);
		phi2 = ConvertAngleIntoRadian(jointangle + phi2);

		d1 = flag_1.distance * cos(phi1);
		d2 = flag_2.distance * cos(phi2);
		d3 = GetFieldLength();

		pos1 = mObjectPosMap[VO_FLAG1_L];

		pos2 = mObjectPosMap[VO_FLAG1_R];

		myLocalizationMethod = LOCALIZATION_TOP;
		canLocalizeDirect = true;

		canDoLocalizationByTwoFlags = true;
#ifdef canloc
		/////cout<<"localized by VO_FLAG1_L and VO_FLAG1_R"<<endl;
#endif
		if ((myBodyToXAxisAngle > -200) && (myBodyToXAxisAngle < 200))
		{
			gyroz = myBodyToXAxisAngle;
		}
	}
	else if ((k == VO_FLAG2_L && l == VO_FLAG2_R)
			|| (l == VO_FLAG2_L && k == VO_FLAG2_R)) //8
	{ //localize by flag2_l and flag2_r
	  ///cout<<"localize by flag2_l and flag2_r"<<endl;
#ifdef SOME_CHANGE_TO_LINE
		if (messageParser.mVisionSenseMap[VO_FLAG2_L].distance
				< messageParser.mVisionSenseMap[VO_FLAG2_R].distance)
		{
			if (messageParser.mLineSenseMap[LI_SIDE_N].updated
					&& messageParser.mLineSenseMap[LI_GOAL_L].updated)
			{
				LocaLizationByLines(myCoordinate, LI_SIDE_N, LI_GOAL_L);
				myLocalizationMethod = LOCALIZATION_BOTTOM;
				canLocalizeDirect = true;
				canDoLocalizationByTwoFlags = true;
				localizationFlag_1 = VO_FLAG2_L;
				localizationFlag_2 = VO_FLAG2_R;

				lastCycleLocalizationFlag = localizationFlag_1; ///for turn head strategy

				///cout<<"change to line location!!"<<endl;
				if (canLocalizeDirect)
				{
					///cout<<"I can localize my self directly! ~~~~~~~~ "<<"localizationFlag_1:"<<localizationFlag_1<<" ~~~~~~~~~~~~~~~~~~:-)"<<endl;
				}
				else
				{
					///cout<<"I can not localize my self directly! ~~~~~~~~~~~~~~~~~~~~~~:-("<<endl;
				}
				return;
			}
		}
		else
		{
			if (messageParser.mLineSenseMap[LI_SIDE_N].updated
					&& messageParser.mLineSenseMap[LI_GOAL_R].updated)
			{
				LocaLizationByLines(myCoordinate, LI_SIDE_N, LI_GOAL_R);
				myLocalizationMethod = LOCALIZATION_BOTTOM;
				canLocalizeDirect = true;
				canDoLocalizationByTwoFlags = true;
				localizationFlag_1 = VO_FLAG2_L;
				localizationFlag_2 = VO_FLAG2_R;

				lastCycleLocalizationFlag = localizationFlag_1; ///for turn head strategy

				///cout<<"change to line location!!"<<endl;
				if (canLocalizeDirect)
				{
					///cout<<"I can localize my self directly! ~~~~~~~~ "<<"localizationFlag_1:"<<localizationFlag_1<<" ~~~~~~~~~~~~~~~~~~:-)"<<endl;
				}
				else
				{
					///cout<<"I can not localize my self directly! ~~~~~~~~~~~~~~~~~~~~~~:-("<<endl;
				}
				return;
			}
		}
#endif
		flag_1 = localizeSenseMap[VO_FLAG2_L];
		flag_2 = localizeSenseMap[VO_FLAG2_R];
		localizationFlag_1 = VO_FLAG2_L;
		localizationFlag_2 = VO_FLAG2_R;

		lastCycleLocalizationFlag = localizationFlag_1; ///for turn head strategy

		phi1 = flag_1.phi;
		phi2 = flag_2.phi;

		phi1 = ConvertAngleIntoRadian(jointangle + phi1);
		phi2 = ConvertAngleIntoRadian(jointangle + phi2);

		d1 = flag_1.distance * cos(phi1);
		d2 = flag_2.distance * cos(phi2);
		d3 = GetFieldLength();

		pos1 = mObjectPosMap[VO_FLAG2_L];

		pos2 = mObjectPosMap[VO_FLAG2_R];

		myLocalizationMethod = LOCALIZATION_BOTTOM;
		canLocalizeDirect = true;

		canDoLocalizationByTwoFlags = true;
#ifdef canloc
		/////cout<<"localized by VO_FLAG2_L and VO_FLAG2_R"<<endl;
#endif
		if ((myBodyToXAxisAngle > -200) && (myBodyToXAxisAngle < 200))
		{
			gyroz = myBodyToXAxisAngle;
		}
	}
	else if (localizeSenseMap[VO_GOAL1_R].distance
			+ localizeSenseMap[VO_GOAL2_R].distance
			+ localizeSenseMap[VO_FLAG1_R].distance
			+ localizeSenseMap[VO_FLAG2_R].distance != 0)
	{
		/////cout<<"localized by single right1111111111111111111111111111       k:   "<<k<<endl;
		/////cout<<"localizeSenseMap.count(VO_GOAL1_R):"<<localizeSenseMap.count(VO_GOAL1_R)<<endl;
		/////cout<<" localizeSenseMap.count(VO_GOAL2_R)"<< localizeSenseMap.count(VO_GOAL2_R)<<endl;
		/////cout<<" localizeSenseMap.count(VO_FLAG1_R) :"<< localizeSenseMap.count(VO_FLAG1_R)<<endl;
		/////cout<<" localizeSenseMap.count(VO_FLAG2_R):" << localizeSenseMap.count(VO_FLAG2_R)<<endl;

		/////cout<<"localizeSenseMap.count(VO_GOAL1_R).distance:"<<localizeSenseMap[VO_GOAL1_R].distance<<endl;
		/////cout<<" localizeSenseMap.count(VO_GOAL2_R).distance"<< localizeSenseMap[VO_GOAL2_R].distance<<endl;
		/////cout<<" localizeSenseMap.count(VO_FLAG1_R).distance :"<< localizeSenseMap[VO_FLAG1_R].distance<<endl;
		/////cout<<" localizeSenseMap.count(VO_FLAG2_R).distance:" << localizeSenseMap[VO_FLAG2_R].distance<<endl;
		if (k == VO_GOAL1_R)
		{
#ifdef USE_LINE
			if (messageParser.mLineSenseMap[LI_GOAL_R].updated)
			{
				LocaLizationByGoalLine(myCoordinate, LI_GOAL_R, VO_GOAL1_R);
				localizationFlag_1 = VO_GOAL1_R;

				lastCycleLocalizationFlag = localizationFlag_1; ///for turn head strategy

				canLocalizeDirect = true;
				canDoLocalizationByTwoFlags = false;
				myLocalizationMethod = LOCALIZATION_SINGL_RIGHT;
				///cout<<"localized by VO_GOAL1_R Coor:( "<<myCoordinate.x()<<" , "<<myCoordinate.y()<<" )"<<endl;
				if (canLocalizeDirect)
				{
					///cout<<"I can localize my self directly! ~~~~~~~~ "<<"localizationFlag_1:"<<localizationFlag_1<<" ~~~~~~~~~~~~~~~~~~:-)"<<endl;
				}
				else
				{
					///cout<<"I can not localize my self directly! ~~~~~~~~~~~~~~~~~~~~~~:-("<<endl;
				}
				return;
			}
#endif
			flag_1 = localizeSenseMap[VO_GOAL1_R];
			localizationFlag_1 = VO_GOAL1_R;

			lastCycleLocalizationFlag = localizationFlag_1; ///for turn head strategy

			flag_y = GetGoalWidth() / 2;
#ifdef canloc
			/////cout<<"localized by VO_GOAL1_R"<<endl;
#endif
		}
		else if (k == VO_GOAL2_R)
		{
#ifdef USE_LINE
			if (messageParser.mLineSenseMap[LI_GOAL_R].updated)
			{
				LocaLizationByGoalLine(myCoordinate, LI_GOAL_R, VO_GOAL2_R);
				localizationFlag_1 = VO_GOAL2_R;

				lastCycleLocalizationFlag = localizationFlag_1; ///for turn head strategy

				canLocalizeDirect = true;
				canDoLocalizationByTwoFlags = false;
				myLocalizationMethod = LOCALIZATION_SINGL_RIGHT;
				///cout<<"localized by VO_GOAL2_R Coor:( "<<myCoordinate.x()<<" , "<<myCoordinate.y()<<" )"<<endl;
				if (canLocalizeDirect)
				{
					///cout<<"I can localize my self directly! ~~~~~~~~ "<<"localizationFlag_1:"<<localizationFlag_1<<" ~~~~~~~~~~~~~~~~~~:-)"<<endl;
				}
				else
				{
					///cout<<"I can not localize my self directly! ~~~~~~~~~~~~~~~~~~~~~~:-("<<endl;
				}
				return;
			}
#endif
			flag_1 = localizeSenseMap[VO_GOAL2_R];
			localizationFlag_1 = VO_GOAL2_R;

			lastCycleLocalizationFlag = localizationFlag_1; ///for turn head strategy

			flag_y = -GetGoalWidth() / 2;
#ifdef canloc
			/////cout<<"localized by VO_GOAL2_R"<<endl;
#endif
		}
		else if (k == VO_FLAG1_R)
		{
#ifdef USE_LINE
			if (messageParser.mLineSenseMap[LI_SIDE_P].updated
					&& messageParser.mLineSenseMap[LI_GOAL_R].updated)
			{
				LocaLizationByLines(myCoordinate, LI_SIDE_P, LI_GOAL_R);
				localizationFlag_1 = VO_FLAG1_R;

				lastCycleLocalizationFlag = localizationFlag_1; ///for turn head strategy

				canLocalizeDirect = true;
				canDoLocalizationByTwoFlags = false;
				myLocalizationMethod = LOCALIZATION_SINGL_RIGHT;
				///cout<<"localized by VO_FLAG1_R Coor:( "<<myCoordinate.x()<<" , "<<myCoordinate.y()<<" )"<<endl;
				if (canLocalizeDirect)
				{
					///cout<<"I can localize my self directly! ~~~~~~~~ "<<"localizationFlag_1:"<<localizationFlag_1<<" ~~~~~~~~~~~~~~~~~~:-)"<<endl;
				}
				else
				{
					///cout<<"I can not localize my self directly! ~~~~~~~~~~~~~~~~~~~~~~:-("<<endl;
				}
				return;
			}
#endif
			flag_1 = localizeSenseMap[VO_FLAG1_R];
			localizationFlag_1 = VO_FLAG1_R;

			lastCycleLocalizationFlag = localizationFlag_1; ///for turn head strategy

			flag_y = GetFieldWidth() / 2;
#ifdef canloc
			/////cout<<"localized by VO_FLAG1_R"<<endl;
#endif
		}
		else if (k == VO_FLAG2_R)
		{
#ifdef USE_LINE
			if (messageParser.mLineSenseMap[LI_SIDE_N].updated
					&& messageParser.mLineSenseMap[LI_GOAL_R].updated)
			{
				LocaLizationByLines(myCoordinate, LI_SIDE_N, LI_GOAL_R);
				localizationFlag_1 = VO_FLAG2_R;

				lastCycleLocalizationFlag = localizationFlag_1; ///for turn head strategy

				canLocalizeDirect = true;
				canDoLocalizationByTwoFlags = false;
				myLocalizationMethod = LOCALIZATION_SINGL_RIGHT;
				///cout<<"localized by VO_FLAG2_R Coor:( "<<myCoordinate.x()<<" , "<<myCoordinate.y()<<" )"<<endl;
				if (canLocalizeDirect)
				{
					///cout<<"I can localize my self directly! ~~~~~~~~ "<<"localizationFlag_1:"<<localizationFlag_1<<" ~~~~~~~~~~~~~~~~~~:-)"<<endl;
				}
				else
				{
					///cout<<"I can not localize my self directly! ~~~~~~~~~~~~~~~~~~~~~~:-("<<endl;
				}
				return;
			}
#endif
			flag_1 = localizeSenseMap[VO_FLAG2_R];
			localizationFlag_1 = VO_FLAG2_R;

			lastCycleLocalizationFlag = localizationFlag_1; ///for turn head strategy

			flag_y = -GetFieldWidth() / 2;
#ifdef canloc
			/////cout<<"localized by VO_FLAG2_R"<<endl;
#endif
		}
		///cout<<"   GYR localization!!!"<<endl;
		phi1 = flag_1.phi;

		theta = flag_1.theta;
		phi1 = ConvertAngleIntoRadian(jointangle + phi1);

		if (flag_1.distance < 2)
		{
			d1 = flag_1.distance * cos(phi1);
		}
		else if (flag_1.distance >= 2)
		{
			d1 = flag_1.distance;
		}

		/////cout<<"right single BodyTox:"<<BodyToX<<endl;
		/////cout<<"right single theta:"<<theta<<endl;
		/////cout<<"right single jointAngle1:"<<jointangle1<<endl;
		/////cout<<"right single temp:"<<BodyToX+theta+jointangle1<<endl;

		if (myTeamIndex == TI_LEFT)
		{
			temp = (BodyToX + theta + jointangle1) * PI / 180;
		}
		else if (myTeamIndex == TI_RIGHT)
		{

			if (BodyToX + jointangle1 > 90)
			{
				/////cout<<"RIGHT_____1"<<endl;
				BodyToX = 180 - BodyToX - jointangle1;
				temp = (BodyToX - theta) * PI / 180;
			}
			else if (BodyToX + jointangle1 < -90)
			{
				/////cout<<"RIGHT_____2"<<endl;
				BodyToX = -180 - BodyToX - jointangle1;
				temp = (BodyToX - theta) * PI / 180;
			}
			else if (BodyToX + jointangle1 <= 90 && BodyToX + jointangle1 >= 0)
			{
				/////cout<<"RIGHT_____3"<<endl;
				temp = (180 - (BodyToX + jointangle1 + theta)) * PI / 180;
			}
			else if (BodyToX + jointangle1 >= -90 && BodyToX + jointangle1 <= 0)
			{
				/////cout<<"RIGHT____4"<<endl;
				temp = (-180 - (BodyToX + jointangle1 + theta)) * PI / 180;
			}
			/////cout<<"RIGHT_temp:"<<temp<<endl;
		}

		x = GetFieldLength() / 2 - d1 * cos(temp);
		if (myTeamIndex == TI_LEFT)
		{
			y = flag_y - d1 * sin(temp);
		}
		else
		{
			y = -flag_y - d1 * sin(temp);
		}
		///	y=flag_y-d1*sin(temp);
		canLocalizeDirect = true;
		canDoLocalizationByTwoFlags = false;
		myLocalizationMethod = LOCALIZATION_SINGL_RIGHT;
		myCoordinate.x(x);

		/////cout<<"111BodyToX:"<<BodyToX<<"  x:  "<<x<<"   y:  "<<y<<" d1:  "<<d1<<"  temp: "<<temp<<endl;
		/*
		 if(x<15&&x>-15)
		 {
		 myCoordinate.x(x);
		 ////////cout<<"notnan nan nan nan nan nan nan nan111111"<<endl;
		 }
		 else
		 {
		 canLocalizeDirect=false;
		 canDoLocalizationByTwoFlags=false;

		 Vector3 my=GetMyCoordinate();
		 myCoordinate.x(my.x());
		 /////cout<<"NAN nan nan nan nan nan nan nan nan11112222222"<<endl;
		 if ((messageParser.GetVanPos(vanpos)) && (myNumber==messageParser.GetVanguardNumber()))
		 {
		 myCoordinate.x(vanpos.x());
		 lastCyclesAverageMyCoordinate.x(vanpos.x());
		 //	canLocalizeDirect=true;
		 //	#ifdef canloc
		 //	/////cout<<"localized by Hearing"<<endl;
		 //	#endif
		 /////cout<<"#########nan nan na222222222n listen my pos:"<<myCoordinate<<endl;
		 }
		 }
		 */
		if (myTeamIndex == TI_RIGHT)
		{
			myCoordinate.x(-myCoordinate.x());
		}
		myCoordinate.y(y);
		myCoordinate.z(0.47);

		for (TVisionSenseMap::iterator iter = localizeSenseMap.begin();
				iter != localizeSenseMap.end(); iter++)
				{
			///cout<<"loacllizeSenseMap["<<iter->first<<"]:"<<(*iter).second.distance<<endl;
		}

		///////cout<<"{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{"<<endl;
	}
	else if (localizeSenseMap[VO_GOAL1_L].distance
			+ localizeSenseMap[VO_GOAL2_L].distance
			+ localizeSenseMap[VO_FLAG1_L].distance
			+ localizeSenseMap[VO_FLAG2_L].distance != 0)
	{
		/////cout<<"localized by single left22222222222222222222           k  "<<k<<endl;
		/////cout<<" localizeSenseMap.count(VO_GOAL1_L) :"<<localizeSenseMap.count(VO_GOAL1_L)<<endl;
		/////cout<<" localizeSenseMap.count(VO_GOAL2_L):"<< localizeSenseMap.count(VO_GOAL2_L)<<endl;
		/////cout<<" localizeSenseMap.count(VO_FLAG1_L) :"<<localizeSenseMap.count(VO_FLAG1_L) <<endl;
		/////cout<<" localizeSenseMap.count(VO_FLAG2_L):"<<localizeSenseMap.count(VO_FLAG2_L)<<endl;

		/////cout<<" localizeSenseMap.count(VO_GOAL1_L)distance :"<<localizeSenseMap[VO_GOAL1_L].distance<<endl;
		/////cout<<" localizeSenseMap.count(VO_GOAL2_L)distance:"<< localizeSenseMap[VO_GOAL2_L].distance<<endl;
		/////cout<<" localizeSenseMap.count(VO_FLAG1_L)distance :"<<localizeSenseMap[VO_FLAG1_L].distance <<endl;
		/////cout<<" localizeSenseMap.count(VO_FLAG2_L)distance:"<<localizeSenseMap[VO_FLAG2_L].distance<<endl;

		if (k == VO_GOAL1_L)
		{
#ifdef USE_LINE
			if (messageParser.mLineSenseMap[LI_GOAL_L].updated)
			{
				LocaLizationByGoalLine(myCoordinate, LI_GOAL_L, VO_GOAL1_L);
				localizationFlag_1 = VO_GOAL1_L;

				lastCycleLocalizationFlag = localizationFlag_1; ///for turn head strategy

				canLocalizeDirect = true;
				canDoLocalizationByTwoFlags = false;
				myLocalizationMethod = LOCALIZATION_SINGL_LEFT;
				///cout<<"localized by VO_GOAL1_L Coor:( "<<myCoordinate.x()<<" , "<<myCoordinate.y()<<" )"<<endl;
				if (canLocalizeDirect)
				{
					///cout<<"I can localize my self directly! ~~~~~~~~ "<<"localizationFlag_1:"<<localizationFlag_1<<" ~~~~~~~~~~~~~~~~~~:-)"<<endl;
				}
				else
				{
					///cout<<"I can not localize my self directly! ~~~~~~~~~~~~~~~~~~~~~~:-("<<endl;
				}
				return;
			}
#endif
			flag_1 = localizeSenseMap[VO_GOAL1_L];
			localizationFlag_1 = VO_GOAL1_L;

			lastCycleLocalizationFlag = localizationFlag_1; ///for turn head strategy

			flag_y = GetGoalWidth() / 2;
#ifdef canloc
			/////cout<<"localized by VO_GOAL1_L"<<endl;
#endif
		}
		else if (k == VO_GOAL2_L)
		{
#ifdef USE_LINE
			if (messageParser.mLineSenseMap[LI_GOAL_L].updated)
			{
				LocaLizationByGoalLine(myCoordinate, LI_GOAL_L, VO_GOAL2_L);
				localizationFlag_1 = VO_GOAL2_L;

				lastCycleLocalizationFlag = localizationFlag_1; ///for turn head strategy

				canLocalizeDirect = true;
				canDoLocalizationByTwoFlags = false;
				myLocalizationMethod = LOCALIZATION_SINGL_LEFT;
				///cout<<"localized by VO_GOAL2_L Coor:( "<<myCoordinate.x()<<" , "<<myCoordinate.y()<<" )"<<endl;
				if (canLocalizeDirect)
				{
					///cout<<"I can localize my self directly! ~~~~~~~~ "<<"localizationFlag_1:"<<localizationFlag_1<<" ~~~~~~~~~~~~~~~~~~:-)"<<endl;
				}
				else
				{
					///cout<<"I can not localize my self directly! ~~~~~~~~~~~~~~~~~~~~~~:-("<<endl;
				}
				return;
			}
#endif
			flag_1 = localizeSenseMap[VO_GOAL2_L];
			localizationFlag_1 = VO_GOAL2_L;

			lastCycleLocalizationFlag = localizationFlag_1; ///for turn head strategy

			flag_y = -GetGoalWidth() / 2;
#ifdef canloc
			/////cout<<"localized by VO_GOAL2_L"<<endl;
#endif
		}
		else if (k == VO_FLAG1_L)
		{
#ifdef USE_LINE
			if (messageParser.mLineSenseMap[LI_SIDE_P].updated
					&& messageParser.mLineSenseMap[LI_GOAL_L].updated)
			{
				LocaLizationByLines(myCoordinate, LI_SIDE_P, LI_GOAL_L);
				localizationFlag_1 = VO_FLAG1_L;

				lastCycleLocalizationFlag = localizationFlag_1; ///for turn head strategy

				canLocalizeDirect = true;
				canDoLocalizationByTwoFlags = false;
				myLocalizationMethod = LOCALIZATION_SINGL_LEFT;
				///cout<<"localized by VO_FLAG1_L Coor:( "<<myCoordinate.x()<<" , "<<myCoordinate.y()<<" )"<<endl;
				if (canLocalizeDirect)
				{
					///cout<<"I can localize my self directly! ~~~~~~~~ "<<"localizationFlag_1:"<<localizationFlag_1<<" ~~~~~~~~~~~~~~~~~~:-)"<<endl;
				}
				else
				{
					///cout<<"I can not localize my self directly! ~~~~~~~~~~~~~~~~~~~~~~:-("<<endl;
				}
				return;
			}
#endif
			flag_1 = localizeSenseMap[VO_FLAG1_L];
			localizationFlag_1 = VO_FLAG1_L;

			lastCycleLocalizationFlag = localizationFlag_1; ///for turn head strategy

			flag_y = GetFieldWidth() / 2;
#ifdef canloc
			/////cout<<"localized by VO_FLAG1_L"<<endl;
#endif
		}
		else if (k == VO_FLAG2_L)
		{
#ifdef USE_LINE
			if (messageParser.mLineSenseMap[LI_SIDE_N].updated
					&& messageParser.mLineSenseMap[LI_GOAL_L].updated)
			{
				LocaLizationByLines(myCoordinate, LI_SIDE_N, LI_GOAL_L);
				localizationFlag_1 = VO_FLAG2_L;

				lastCycleLocalizationFlag = localizationFlag_1; ///for turn head strategy

				canLocalizeDirect = true;
				canDoLocalizationByTwoFlags = false;
				myLocalizationMethod = LOCALIZATION_SINGL_LEFT;
				///cout<<"localized by VO_FLAG2_L Coor:( "<<myCoordinate.x()<<" , "<<myCoordinate.y()<<" )"<<endl;

				if (canLocalizeDirect)
				{
					///cout<<"I can localize my self directly! ~~~~~~~~ "<<"localizationFlag_1:"<<localizationFlag_1<<" ~~~~~~~~~~~~~~~~~~:-)"<<endl;
				}
				else
				{
					///cout<<"I can not localize my self directly! ~~~~~~~~~~~~~~~~~~~~~~:-("<<endl;
				}

				return;
			}
#endif
			flag_1 = localizeSenseMap[VO_FLAG2_L];
			localizationFlag_1 = VO_FLAG2_L;

			lastCycleLocalizationFlag = localizationFlag_1; ///for turn head strategy

			flag_y = -GetFieldWidth() / 2;
#ifdef canloc
			/////cout<<"localized by VO_FLAG2_L"<<endl;
#endif
		}
		///cout<<"   GYR localization!!!"<<endl;
		phi1 = flag_1.phi;
		theta = flag_1.theta;
		phi1 = ConvertAngleIntoRadian(jointangle + phi1);

		if (flag_1.distance < 2)
		{
			d1 = flag_1.distance * cos(phi1);
		}
		else if (flag_1.distance >= 2)
		{
			d1 = flag_1.distance;
		}

		/////cout<<"left single BodyTox:"<<BodyToX<<endl;
		/////cout<<"left single theta:"<<theta<<endl;
		/////cout<<"left single jointAngle1:"<<jointangle1<<endl;
		/////cout<<"left single temp:"<<BodyToX+theta+jointangle1<<endl;

		if (myTeamIndex == TI_RIGHT)
		{
			temp = (BodyToX + theta + jointangle1) * PI / 180;
			/////cout<<"TI_RIGHT temp:"<<temp<<endl;
		}
		else if (myTeamIndex == TI_LEFT)
		{

			if (BodyToX + jointangle1 > 90)
			{
				/////cout<<"LEFT_____1"<<endl;
				BodyToX = 180 - BodyToX - jointangle1;
				temp = (BodyToX - theta) * PI / 180;
			}
			else if (BodyToX + jointangle1 < -90)
			{
				/////cout<<"LEFT_____2"<<endl;
				BodyToX = -180 - BodyToX - jointangle1;
				temp = (BodyToX - theta) * PI / 180;
			}
			else if (BodyToX + jointangle1 <= 90 && BodyToX + jointangle1 >= 0)
			{
				/////cout<<"LEFT_____3"<<endl;
				temp = (180 - (BodyToX + jointangle1 + theta)) * PI / 180;
			}
			else if (BodyToX + jointangle1 >= -90 && BodyToX + jointangle1 <= 0)
			{
				/////cout<<"LEFT____4"<<endl;
				temp = (-180 - (BodyToX + jointangle1 + theta)) * PI / 180;
			}
		}
		//	temp=(BodyToX-theta)*PI/180;
		x = -GetFieldLength() / 2 + d1 * cos(temp);
		if (myTeamIndex == TI_LEFT)
		{
			y = flag_y - d1 * sin(temp);
		}
		else
		{
			y = -flag_y - d1 * sin(temp);
		}
		canLocalizeDirect = true;
		canDoLocalizationByTwoFlags = false;
		myLocalizationMethod = LOCALIZATION_SINGL_LEFT;

		/////cout<<"222BodyToX:"<<BodyToX<<"  x:  "<<x<<"   y:  "<<y<<" d1:  "<<d1<<"  temp: "<<temp<<endl;
		myCoordinate.x(x);
		/*
		 if(x<15&&x>-15)
		 {
		 myCoordinate.x(x);
		 ////////cout<<"not nan nan nan nan nan nan nan nan33333333333"<<endl;
		 }
		 else
		 {
		 canLocalizeDirect=false;
		 canDoLocalizationByTwoFlags=false;
		 /////cout<<"NAN nan nan nan nan nan nan nan n44444444444441"<<endl;
		 Vector3 my=GetMyCoordinate();
		 myCoordinate.x(my.x());
		 if ((messageParser.GetVanPos(vanpos)) && (myNumber==messageParser.GetVanguardNumber()))
		 {
		 myCoordinate.x(vanpos.x());
		 lastCyclesAverageMyCoordinate.x(vanpos.x());
		 //	canLocalizeDirect=true;
		 //	#ifdef canloc
		 //	/////cout<<"localized by Hearing"<<endl;
		 //	#endif
		 /////cout<<"NAN nan nan nan nan nan nan nan nan15555555555555"<<endl;
		 ///////cout<<"#########nan nan nan listen my pos:"<<myCoordinate<<endl;
		 }
		 }
		 */
		if (myTeamIndex == TI_RIGHT)
		{
			myCoordinate.x(-myCoordinate.x());
		}
		myCoordinate.y(y);
		myCoordinate.z(0.47);

		for (TVisionSenseMap::iterator iter = localizeSenseMap.begin();
				iter != localizeSenseMap.end(); iter++)
				{
			///cout<<"loacllizeSenseMap["<<iter->first<<"]:"<<(*iter).second.distance<<endl;
		}

		///////cout<<"}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}"<<endl;
	}
// 	else if ((messageParser.GetVanPos(vanpos)) )
// 	{
// 		canLocalizeDirect=false;
//
//
// 		canDoLocalizationByTwoFlags=false;
//
// 	}
	else
	{
		/////cout<<"I can not see anythingAnd can not hearing too"<<endl;
		localizationFlag_1 = VO_NULL;
		localizationFlag_2 = VO_NULL;
		canLocalizeDirect = false;

		canDoLocalizationByTwoFlags = false;

		localizeByTurnHead = true;
		myLocalizationMethod = LOCALIZATION_TURNHEAD;
		//	///////cout<<"I can not localize myself! :-("<<endl;
	}

	//	///////cout<<"the body height is		"<<BodyHeight<<endl;
	//calculate my coordinate
	switch (myLocalizationMethod)
	{
	case LOCALIZATION_LEFT:
		if (fabs(d1 - d2) > d3)
		{
			/////cout<<"the value will be NAN!!!"<<endl;
		}

		/////cout<<"d1:  "<<d1<<"   d2:   "<<d2<<"   d3:   "<<d3<<endl;
		/////cout<<"pos1:  "<<pos1<<"  pos2:  "<<pos2<<endl;
		LocalizationByLeftFieldFlags(d1, d2, d3, pos1, pos2);
		localizeByTurnHeadSenseMap.clear();
		break;
	case LOCALIZATION_RIGHT:
		if (fabs(d1 - d2) > d3)
		{
			/////cout<<"the value will be NAN!!!"<<endl;
		}

		/////cout<<"d1:  "<<d1<<"   d2:   "<<d2<<"   d3:   "<<d3<<endl;
		/////cout<<"pos1:  "<<pos1<<"  pos2:  "<<pos2<<endl;
		LocalizationByRightFieldFlags(d1, d2, d3, pos1, pos2);
		localizeByTurnHeadSenseMap.clear();
		break;
	case LOCALIZATION_TOP:
		if (fabs(d1 - d2) > d3)
		{
			/////cout<<"the value will be NAN!!!"<<endl;
		}
		/////cout<<"d1:  "<<d1<<"   d2:   "<<d2<<"   d3:   "<<d3<<endl;
		/////cout<<"pos1:  "<<pos1<<"  pos2:  "<<pos2<<endl;
		LocalizationByTopFieldFlags(d1, d2, d3, pos1, pos2);
		localizeByTurnHeadSenseMap.clear();
		break;
	case LOCALIZATION_BOTTOM:
		if (fabs(d1 - d2) > d3)
		{
			/////cout<<"the value will be NAN!!!"<<endl;
		}
		/////cout<<"d1:  "<<d1<<"   d2:   "<<d2<<"   d3:   "<<d3<<endl;
		/////cout<<"pos1:  "<<pos1<<"  pos2:  "<<pos2<<endl;
		LocalizationByBottomFieldFlags(d1, d2, d3, pos1, pos2);
		localizeByTurnHeadSenseMap.clear();
		break;
	case LOCALIZATION_TURNHEAD:
		RecordFlagSenseMsg();
		break;
	case LOCALIZATION_SINGL_RIGHT:
		localizeByTurnHeadSenseMap.clear();
		break;
	case LOCALIZATION_SINGL_LEFT:
		localizeByTurnHeadSenseMap.clear();
		break;
	case LOCALIZATION_NULL:
		break;
	default:
		break;
	}
#endif		//add by czg
#endif
	/*		if((myCoordinate.x()<9) && (myCoordinate.x()>-9) && (myCoordinate.y()<6) && (myCoordinate.y()>-6))
	 {

	 }
	 else
	 {
	 ///////cout<<"not (myCoordinate.x()<9) && (myCoordinate.x()>-9) && (myCoordinate.y()<6) && (myCoordinate.y()>-6)"<<endl;
	 if ((messageParser.GetVanPos(vanpos)) && (myNumber==messageParser.GetVanguardNumber()))
	 {
	 myCoordinate=vanpos;
	 canLocalizeDirect=true;
	 #ifdef canloc
	 ///////cout<<"localized by Hearing"<<endl;
	 #endif
	 ///////cout<<"#######################my pos:"<<myCoordinate<<endl;
	 }
	 else
	 {
	 canLocalizeDirect=false;
	 }
	 }
	 */
#if 1
	if (canLocalizeDirect)
	{
		///cout<<"I can localize my self directly! ~~~~~~~~ "<<"localizationFlag_1:"<<localizationFlag_1<<" ~~~~~~~~~~~~~~~~~~:-)"<<endl;
	}
	else
	{
		///cout<<"I can not localize my self directly! ~~~~~~~~~~~~~~~~~~~~~~:-("<<endl;
	}
	if (CITConf.DrawerBug)
	{
		if (GetMyNumber() != 0)
		{
			string n1 = GetMyTeamName() + "Coordinate.My."
					+ Convert::ToString(GetMyNumber());
			RGBDraw rgb(0.45, 0.9, 0);
		//	cout << "n1-------::" << n1 << endl;
			CITMDrawer.drawPoint(myCoordinate, 5, rgb, &n1);
			CITMDrawer.UpdateDrawer(&n1);

			if (this->GetMyNumber() == 3)
			{
				Vector3 one = GetfutureBallCoordinate(1);
				Vector3 two = GetfutureBallCoordinate(2);
				Vector3 ten = GetfutureBallCoordinate(10);
				Vector3 tweny = GetfutureBallCoordinate(20);
				string n1 = GetMyTeamName() + "future.Ball.one"
						+ Convert::ToString(GetMyNumber());
				RGBDraw rgb(0.45, 0.9, 1);
				CITMDrawer.drawPoint(one, 5, rgb, &n1);
				CITMDrawer.UpdateDrawer(&n1);

				n1 = GetMyTeamName() + "future.Ball.two"
						+ Convert::ToString(GetMyNumber());
				CITMDrawer.drawPoint(two, 5, rgb, &n1);
				CITMDrawer.UpdateDrawer(&n1);

				n1 = GetMyTeamName() + "future.Ball.ten"
						+ Convert::ToString(GetMyNumber());

				CITMDrawer.drawPoint(ten, 5, rgb, &n1);
				CITMDrawer.UpdateDrawer(&n1);

				n1 = GetMyTeamName() + "future.Ball.tweny"
						+ Convert::ToString(GetMyNumber());

				CITMDrawer.drawPoint(tweny, 5, rgb, &n1);
				CITMDrawer.UpdateDrawer(&n1);
			}
		}
	}

	if (canDoLocalizationByTwoFlags)
	{
		///cout<<"I can localize my self With Two Flags! ____________________________:-)"<<endl;
	}
	else
	{
		///cout<<"I can not localize my self With Two Flags! ____________________________:-("<<endl;
	}
#endif
#if 0
	///////cout<<"-------------------------------"<<endl;
	///////cout<<"d1:"<<d1<<endl;
	///////cout<<"d2:"<<d2<<endl;
	///////cout<<"diff:"<<pos2.y()-pos1.y()<<endl;
	///////cout<<"pos1:"<<pos1<<endl;
	///////cout<<"pos2:"<<pos2<<endl;
	///////cout<<"my pos:"<<myCoordinate<<endl;

	//
	//VisionSense teammateSense=messageParser.GetVisionPolarCoordinate( TMMT_2 );
	//Vector3 localTeammatePos=ConvertPolarCoordinatesIntoDecareCoordinates(teammateSense);
	//Vector3 teammatePos=myCoordinate+localTeammatePos;

	/////////cout<<"my num 2 teammate pos:"<<teammatePos<<endl;
#endif
}

void WorldModel::LocalizationByRightFieldFlags(float &d1, float &d2, float &d3,
		Vector3 &pos1, Vector3 &pos2)
{
	//calculate my position

	if (d3 >= d1 && d3 >= d2) ///to avoid nan
	{
		if (d3 > fabs(d1 + d2))
			d3 = fabs(d1 + d2);
	}
	else
	{
		if (fabs(d1 - d2) > d3)
		{
			d3 = fabs(d1 - d2);
		}
	}

	float theta = 0;
	theta = acos((d1 * d1 + d3 * d3 - d2 * d2) / (2 * d1 * d3));
	if (theta > 90)
	{
		theta = 180 - 90;
	}

	/////cout<<"theta:"<<theta<<endl;

	//x axis
	float height = 0;
	height = d1 * sin(theta);

	/////cout<<"height:"<<height<<endl;

	myCoordinate.x(GetFieldLength() / 2 - height);

	/////cout<<"myCoordinate.x():"<<myCoordinate.x()<<endl;

	if (myTeamIndex == TI_RIGHT)
	{
		myCoordinate.x(-myCoordinate.x());
	}

	//y axis
	float y = 0;
	y = ((d1 * d1 - d2 * d2) - (pos1.y() * pos1.y() - pos2.y() * pos2.y()))
			/ (2 * (pos2.y() - pos1.y()));
	myCoordinate.y(y);
	if (myTeamIndex == TI_RIGHT)
	{
///			myCoordinate.y( -myCoordinate.y() );
	}
	myCoordinate.z(0.47);
}

void WorldModel::LocalizationByLeftFieldFlags(float &d1, float &d2, float &d3,
		Vector3 &pos1, Vector3 &pos2)
{

	if (d3 >= d1 && d3 >= d2) ///to avoid nan
	{
		if (d3 > fabs(d1 + d2))
			d3 = fabs(d1 + d2);
	}
	else
	{
		if (fabs(d1 - d2) > d3)
		{
			d3 = fabs(d1 - d2);
		}
	}

	//calculate my position
	float theta = 0;
	theta = acos((d1 * d1 + d3 * d3 - d2 * d2) / (2 * d1 * d3));
	if (theta > 90)
	{
		theta = 180 - 90;
	}

	///////cout<<"theta:"<<theta<<endl;

	//x axis
	float height = 0;
	height = d1 * sin(theta);

	myCoordinate.x(height - GetFieldLength() / 2);
	///cout<<"#########################################"<<endl;
	if (myTeamIndex == TI_RIGHT)
	{
		///cout<<"#########################################111111111111"<<endl;
		myCoordinate.x(-myCoordinate.x());
	}

	//y axis
	float y = 0;
	y = ((d1 * d1 - d2 * d2) - (pos1.y() * pos1.y() - pos2.y() * pos2.y()))
			/ (2 * (pos2.y() - pos1.y()));
	myCoordinate.y(y);
	if (myTeamIndex == TI_RIGHT)
	{
		///cout<<"#########################################22222222222222"<<endl;
///			myCoordinate.y( -myCoordinate.y() );
	}
	myCoordinate.z(0.47);
}

void WorldModel::LocalizationByTopFieldFlags(float &d1, float &d2, float &d3,
		Vector3 &pos1, Vector3 &pos2)
{

	if (d3 >= d1 && d3 >= d2) ///to avoid nan
	{
		if (d3 > fabs(d1 + d2))
			d3 = fabs(d1 + d2);
	}
	else
	{
		if (fabs(d1 - d2) > d3)
		{
			d3 = fabs(d1 - d2);
		}
	}

	//calculate my position
	float theta = 0;
	theta = acos((d1 * d1 + d3 * d3 - d2 * d2) / (2 * d1 * d3));
	if (theta > 90)
	{
		theta = 180 - 90;
	}

	///////cout<<"theta:"<<theta<<endl;

	//y axis
	float height = 0;
	height = d1 * sin(theta);

	myCoordinate.y(GetFieldWidth() / 2 - height);
	if (myTeamIndex == TI_RIGHT)
	{
		myCoordinate.y(-myCoordinate.y());
	}

	//x axis
	float x = 0;
	x = ((d1 * d1 - d2 * d2)) / (2 * (pos2.x() - pos1.x()));
	myCoordinate.x(x);
	if (myTeamIndex == TI_RIGHT)
	{
		///		myCoordinate.x( -myCoordinate.x() );
	}
	myCoordinate.z(0.47);
}

void WorldModel::LocalizationByBottomFieldFlags(float &d1, float &d2, float &d3,
		Vector3 &pos1, Vector3 &pos2)
{

	if (d3 >= d1 && d3 >= d2) ///to avoid nan
	{
		if (d3 > fabs(d1 + d2))
			d3 = fabs(d1 + d2);
	}
	else
	{
		if (fabs(d1 - d2) > d3)
		{
			d3 = fabs(d1 - d2);
		}
	}

	//calculate my position
	float theta = 0;
	theta = acos((d1 * d1 + d3 * d3 - d2 * d2) / (2 * d1 * d3));
	if (theta > 90)
	{
		theta = 180 - 90;
	}

	///////cout<<"theta:"<<theta<<endl;

	//y axis
	float height = 0;
	height = d1 * sin(theta);

	myCoordinate.y(height - GetFieldWidth() / 2);
	if (myTeamIndex == TI_RIGHT)
	{
		myCoordinate.y(-myCoordinate.y());
	}

	//x axis
	float x = 0;
	x = ((d1 * d1 - d2 * d2)) / (2 * (pos2.x() - pos1.x()));
	myCoordinate.x(x);
	if (myTeamIndex == TI_RIGHT)
	{
		///		myCoordinate.x( -myCoordinate.x() );
	}
	myCoordinate.z(0.47);
}

void WorldModel::UpdateMyBodyToXAxisAngle()
{
	//myBodyToXAxisAngle
	///	Vector3 myCoordinate=GetMyCoordinate();
	if (canDoLocalizationByTwoFlags == true
			|| (canLocalizeDirect == true && useLineDoLocalization == true))
	{
		Vector3 flagPos = mObjectPosMap[localizationFlag_1];
		float angle = 0.0f;
		float slope = (myCoordinate.y() - flagPos.y())
				/ (myCoordinate.x() - flagPos.x());
		angle = atan(slope) * 180 / PI;

		///cout<<"++++++++++++++++++++"<<endl;
		///cout<<"atan(slope)*180/PI:"<<atan(slope)*180/PI<<endl;
		///cout<<"myCoordinate:"<<myCoordinate<<endl;
		///cout<<"flagPos:"<<flagPos<<endl;

		if (GetMyTeamIndex() == TI_LEFT)
		{
			if (IsLeftFieldFlag(localizationFlag_1))
			{
				if (angle > 0)
				{
					myBodyToXAxisAngle = (angle
							- GetMyAngleToFlag(localizationFlag_1)) + 180.0;
					if (fabs(myBodyToXAxisAngle) > 180.0)
						myBodyToXAxisAngle = myBodyToXAxisAngle - 360.0;
				}
				else //angle<=0
				{
					myBodyToXAxisAngle = 180.0
							- (GetMyAngleToFlag(localizationFlag_1) - angle);
					if (fabs(myBodyToXAxisAngle) > 180.0)
						myBodyToXAxisAngle = myBodyToXAxisAngle - 360.0;
				}
			}
			else //( ! IsLeftFieldFlag(localizationFlag_1) )
			{
				myBodyToXAxisAngle = angle
						- GetMyAngleToFlag(localizationFlag_1);
			}
		}
		else if (GetMyTeamIndex() == TI_RIGHT)
		{
			if (IsLeftFieldFlag(localizationFlag_1))
			{
				myBodyToXAxisAngle = angle
						- GetMyAngleToFlag(localizationFlag_1);
			}
			else
			{
				if (angle > 0)
				{
					myBodyToXAxisAngle = 180.0
							- (GetMyAngleToFlag(localizationFlag_1) - angle);
					if (fabs(myBodyToXAxisAngle) > 180.0)
						myBodyToXAxisAngle = myBodyToXAxisAngle - 360.0;
				}
				else //angle<=0
				{
					myBodyToXAxisAngle = (angle
							- GetMyAngleToFlag(localizationFlag_1)) + 180.0;
					if (fabs(myBodyToXAxisAngle) > 180.0)
						myBodyToXAxisAngle = myBodyToXAxisAngle - 360.0;
				}
			}
		}

		float headAngle = GetCurrentJointAngle(JID_HEAD_1);
		/**lr*/
		myHeadToXAxisAngle = myBodyToXAxisAngle;

		myBodyToXAxisAngle = myBodyToXAxisAngle - headAngle; //above the myBodyRoXAxisAngle is actually the vision angle,but here ,the myBodyToXAxisAngle is correct

		//	myBodyToXAxisAngle=angle-GetMyAngleToFlag(localizationFlag_1);
	} //if( canLocalizeDirect==true )
	else ///if(canLocalizeDirect==false)
	{
		myBodyToXAxisAngle = GetBodyToX();
		///cout<<"IIIIIIIIIIIIIIIIIIIII haven't update myBodyToXAxisAngle"<<endl;
	}
}

bool WorldModel::IsLeftFieldFlag(VisionObject obj)
{
	bool res = false;
	if (obj == VO_FLAG1_L || obj == VO_FLAG2_L || obj == VO_GOAL1_L
			|| obj == VO_GOAL2_L)
	{
		res = true;
	}

	return res;
}

bool WorldModel::GetMyBodyAngleToXAxis(float& angle)
{
	angle = myBodyToXAxisAngle;
	return canLocalizeDirect;
}
/**lr*/
bool WorldModel::GetMyHeadAngleToXAxis(float& angle)
{
	angle = myHeadToXAxisAngle;
	return canLocalizeDirect;
}

void WorldModel::RecordFlagSenseMsg()
{
	//localizeByTurnHeadSenseMap
	TVisionSenseMap::iterator iter;
	for (iter = messageParser.mVisionSenseMap.begin();
			iter != messageParser.mVisionSenseMap.end(); iter++)
			{
		iter->second.senseTime = GetCurrentGameTime();
		historySenseMap[iter->first] = iter->second;

		//if( !localizeByTurnHeadSenseMap.count(iter->first) )
		{
			switch (iter->first)
			{
			case VO_FLAG1_L:
				iter->second.senseTime = GetCurrentGameTime();
				localizeByTurnHeadSenseMap[VO_FLAG1_L] = (*iter).second;
				break;
			case VO_FLAG2_L:
				iter->second.senseTime = GetCurrentGameTime();
				//localizeByTurnHeadSenseMap.insert(*iter);
				localizeByTurnHeadSenseMap[VO_FLAG2_L] = (*iter).second;
				break;
			case VO_FLAG1_R:
				iter->second.senseTime = GetCurrentGameTime();
				//localizeByTurnHeadSenseMap.insert(*iter);
				localizeByTurnHeadSenseMap[VO_FLAG1_R] = (*iter).second;
				break;
			case VO_FLAG2_R:
				iter->second.senseTime = GetCurrentGameTime();
				//localizeByTurnHeadSenseMap.insert(*iter);
				localizeByTurnHeadSenseMap[VO_FLAG2_R] = (*iter).second;
				break;
			default:
				break;
			}
		}
	}

	//localizeSenseMap=localizeByTurnHeadSenseMap;
	///////cout<<"turn head sense map size:"<<localizeByTurnHeadSenseMap.size()<<endl;
}

void WorldModel::RecordTeammateSenseMsg() //maybe it doesn't work
{
	//myTeammateHistorySenseMap;
	TPlayerSenseMap::iterator iter;
	for (iter = messageParser.mTeamMateSenseMap.begin();
			iter != messageParser.mTeamMateSenseMap.end(); iter++)
			{
		iter->second.senseTime = GetCurrentGameTime();
		myTeammateHistorySenseMap[iter->first] = iter->second;
	}
}

void WorldModel::EvaluateVisionSenseMsg() //maybe it doesn't work
{
	float believeTime = 0.5;
	TVisionSenseMap::iterator iter;
	for (iter = historySenseMap.begin(); iter != historySenseMap.end(); iter++)
	{
		if ((GetCurrentGameTime() - historySenseMap[iter->first].senseTime)
				> believeTime)
		{
			historySenseMap.erase(iter->first);
		}

		if (historySenseMap.empty())
		{
			break;
		}
	}
}

void WorldModel::EvaluateTeammateSenseMsg()
{
	float believeTime = 1.0;
	TPlayerSenseMap::iterator iter;
	for (iter = myTeammateHistorySenseMap.begin();
			iter != myTeammateHistorySenseMap.end(); iter++)
			{
		if ((GetCurrentGameTime()
				- myTeammateHistorySenseMap[iter->first].senseTime)
				> believeTime)
		{
			myTeammateHistorySenseMap.erase(iter->first);
		}

		if (myTeammateHistorySenseMap.empty())
		{
			break;
		}
	}

	//	/////cout<<"my teammate num:"<<myTeammateHistorySenseMap.size()<<endl;
}

bool WorldModel::CanDoLocalization()
{
	bool res = false;
	if (messageParser.mVisionSenseMap.count(VO_FLAG2_L)
			&& messageParser.mVisionSenseMap.count(VO_FLAG1_L)
			&& messageParser.mVisionSenseMap.count(VO_FLAG1_R))
	{
		res = true;
	}
	else if (messageParser.mVisionSenseMap.count(VO_FLAG1_L)
			&& messageParser.mVisionSenseMap.count(VO_FLAG2_L)
			&& messageParser.mVisionSenseMap.count(VO_FLAG2_R))
	{
		res = true;
	}
	else if (messageParser.mVisionSenseMap.count(VO_FLAG1_L)
			&& messageParser.mVisionSenseMap.count(VO_FLAG1_R)
			&& messageParser.mVisionSenseMap.count(VO_FLAG2_R))
	{
		res = true;
	}
	else if (messageParser.mVisionSenseMap.count(VO_FLAG1_R)
			&& messageParser.mVisionSenseMap.count(VO_FLAG2_R)
			&& messageParser.mVisionSenseMap.count(VO_FLAG2_L))
	{
		res = true;
	}
	else
	{
		res = false;
	}

	return res;
}

/*
 void WorldModel::UpdateOtherPlayerCoordinate(VisionObject obj1,VisionObject obj2,VisionObject obj3,float d1,float d2,float d3)///useless
 {
 float data[ 3 ][ 4 ];
 Vector3 vectorX ,vectorY ,vectorZ ;
 Vector3 vector;

 vector = mObjectPosMap[ obj1 ] - myCoordinate;
 data[ 0 ][ 0 ] = vector.x();
 data[ 0 ][ 1 ] = vector.y();
 data[ 0 ][ 2 ] = vector.z();

 vector = mObjectPosMap[ obj2 ] - myCoordinate;
 data[ 1 ][ 0 ] = vector.x();
 data[ 1 ][ 1 ] = vector.y();
 data[ 1 ][ 2 ] = vector.z();

 vector = mObjectPosMap[ obj3 ] - myCoordinate;
 data[ 2 ][ 0 ] = vector.x();
 data[ 2 ][ 1 ] = vector.y();
 data[ 2 ][ 2 ] = vector.z();

 vector = mObjectVectorMap[ obj1 ];
 ///////cout<<"obj1 vector:"<<vector<<endl;
 data[ 0 ][ 3 ] = d1 * vector.getCosAngX();

 vector = mObjectVectorMap[ obj2 ];
 ///////cout<<"obj2 vector:"<<vector<<endl;
 data[ 1 ][ 3 ] = d2 * vector.getCosAngX();

 vector = mObjectVectorMap[ obj3 ];
 ///////cout<<"obj3 vector:"<<vector<<endl;
 data[ 2 ][ 3 ] = d3 * vector.getCosAngX();


 vectorX = Equation ( data );

 vector = mObjectVectorMap[ obj1 ];
 data[ 0 ][ 3 ] = d1 * vector.getCosAngY();

 vector = mObjectVectorMap[ obj2 ];
 data[ 1 ][ 3 ] = d2 * vector.getCosAngY();


 vector = mObjectVectorMap[ obj3 ];
 data[ 2 ][ 3 ] = d3 * vector.getCosAngY();


 vectorY = Equation ( data );

 vector = mObjectVectorMap[ obj1 ];
 data[ 0 ][ 3 ] = d1 * vector.getCosAngZ();

 vector = mObjectVectorMap[ obj2 ];
 data[ 1 ][ 3 ] = d2 * vector.getCosAngZ();

 vector = mObjectVectorMap[ obj3 ];
 data[ 2 ][ 3 ] = d3 * vector.getCosAngZ();

 vectorZ = Equation ( data );

 //------------the pos of object on the filed -----------------//

 float F_G[4][4]=
 {
 {vectorX.x(),vectorY.x(),vectorZ.x(),myCoordinate.x()},
 {vectorX.y(),vectorY.y(),vectorZ.y(),myCoordinate.y()},
 {vectorX.z(),vectorY.z(),vectorZ.z(),myCoordinate.z()},
 {0,0,0,1}
 };


 float F[4],G[4];
 Vector3 p1,p2;

 for( VisionObject object= VO_BALL; object<=OPPO_11;object=VisionObject(object+1))
 {
 if( mObjectVectorMap.count(object) )
 {
 p1=mObjectVectorMap[object];
 /////cout<<"p1:"<<p1<<endl;

 if((p1.x()+p1.y()+p1.z()) == 0)
 mObjectPosMap[object]=p1;
 else
 {
 //if(object==VO_BALL)
 //	/////cout<<"calculate ball coordinate"<<endl;
 F[0]=p1.x();
 F[1]=p1.y();
 F[2]=p1.z();
 F[3]=1.0;
 Matrix(F_G,F,G);
 p2.x( G[0]);
 p2.y( G[1]);
 p2.z( G[2]);
 mObjectPosMap[object]=p2;
 }
 }
 }

 agentTheta = atan2Deg( vectorX.y() , vectorX.x() );
 agentPhi = asinDeg( vectorX.z() / vectorX.mod() );
 }
 */
Vector3 WorldModel::Equation(float mdata[3][4]) ///useless
{
	float exchangeData[4] =
	{ 0 };
	float data[3][4];
	Vector3 result;
	int line, row, max;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			data[i][j] = mdata[i][j];
		}
	}
	for (line = 0; line < 3; line++)
	{
		for (row = line + 1, max = line; row < 3; row++)
		{
			if (fabs(data[row][line]) > fabs(data[max][line]))
				max = row;
		}
		if (max != line)
		{
			for (int i = line; i < 4; i++)
			{
				exchangeData[i] = data[line][i];
				data[line][i] = data[max][i];
				data[max][i] = exchangeData[i];
			}
		}

		for (int i = line + 1; i < 3; i++)
		{
			float data_i_line;
			data_i_line = data[i][line];
			for (int j = line; j < 4; j++)
			{
				data[i][j] -= data[line][j] * data_i_line / data[line][line];
			}
		}
	}
	for (int i = 2; i >= 0; i--)
	{
		for (int j = 3; j > i; j--)
		{
			data[i][3] -= data[i][j] * data[j][3];
		}
		data[i][3] /= data[i][i];

		if (fabs(data[i][3]) < 0.0001f)
		{
			data[i][3] = 0.0;
		}
	}
	float mod = sqrt(sqr(data[0][3]) + sqr(data[1][3]) + sqr(data[2][3]));
	if (fabs(mod - 1) > 0.1)
	{
		for (int i = 0; i < 3; i++)
		{
			data[i][3] /= mod;
		}
	}
	result.x(data[0][3]);
	result.y(data[1][3]);
	result.z(data[2][3]);
	return result;
}

/*
 * ljj add for stand up information
 */

//
void WorldModel::UpdateLastCyclesAverageGYR()
{
	QuFront_back->removedQueue(messageParser.GetGYR().x);
	QuSideLeft_right->removedQueue(messageParser.GetGYR().y);
}

Vector3 WorldModel::getAverageOfLastCyclesGYR()
{
	return averageOfLastCyclesGYR;
}

void WorldModel::UpdateLastCyclesAverageFRP()
{
	QuFRP_Z->removedQueue(
			messageParser.GetFRP(FID_LEFT).f.z
					+ messageParser.GetFRP(FID_RIGHT).f.z);
	QuFRP_Y->removedQueue(
			messageParser.GetFRP(FID_LEFT).f.y
					+ messageParser.GetFRP(FID_RIGHT).f.y);

}
Vector3 WorldModel::getAverageOfLastCyclesFRP_Lf()
{
	return averageOfLastCyclesFRP_Lf;
}
Vector3 WorldModel::getAverageOfLastCyclesFRP_Lc()
{
	return averageOfLastCyclesFRP_Lc;
}
Vector3 WorldModel::getAverageOfLastCyclesFRP_Rf()
{
	return averageOfLastCyclesFRP_Rf;
}
Vector3 WorldModel::getAverageOfLastCyclesFRP_Rc()
{
	return averageOfLastCyclesFRP_Rc;
}

void WorldModel::UpdateBallCoordinate() ///                 czg
{
#if 1
	/////cout.setf(/////cout.showpoint);
	setprecision(6);
	setiosflags(ios::fixed);
	if (CanDoLocalizationDirectly() && CanSeeTheBall())
	{
		VisionSense ballSense = messageParser.GetVisionPolarCoordinate(VO_BALL);
		//  		/////cout<<"ballSense.distance    "<<ballSense.distance<<endl;
		//  		/////cout<<"ballSense.theta    "<<ballSense.theta<<endl;
		// 		/////cout<<"ballSense.phi    "<<ballSense.phi<<endl;
		float myAngleToXCoordinate, temp, theta;
		///		GetMyBodyAngleToXAxis(myAngleToXCoordinate);//
		///		myAngleToXCoordinate=GetBodyToX();
		myAngleToXCoordinate = GetMyBodyAngleToXAxis();
		///cout<<"@@@@@@@@@@@@@GetMyBodyAngleToXAxis():"<<GetMyBodyAngleToXAxis()<<"GetBodyToX():"<<GetBodyToX()<<endl;

		float headAngle = GetCurrentJointAngle(JID_HEAD_2); //
		float headAngle1 = GetCurrentJointAngle(JID_HEAD_1); //
		theta = ConvertAngleIntoRadian(myAngleToXCoordinate + headAngle1);
		// 		/////cout<<"headAngle"<<headAngle<<endl;
		headAngle = -ConvertAngleIntoRadian(headAngle);
		/////cout<<"theta		"<<theta<<endl;

		temp = theta;
		//		/////cout<<"temp			"<<temp<<endl;
		Vector3 localBallCoordinate =
				ConvertPolarCoordinatesIntoDecareCoordinates(ballSense);
		Vector3 tempBallCoordinate, temp1BallCoordinate;
		// 		/////cout<<"localBallCoordinate 1             "<<localBallCoordinate<<endl;

		tempBallCoordinate.x(
				cos(headAngle) * cos(temp) * localBallCoordinate.x()
						- sin(temp) * localBallCoordinate.y()
						+ sin(headAngle) * cos(temp) * localBallCoordinate.z());
		tempBallCoordinate.y(
				sin(temp) * cos(headAngle) * localBallCoordinate.x()
						+ cos(temp) * localBallCoordinate.y()
						+ sin(temp) * sin(headAngle) * localBallCoordinate.z());
		tempBallCoordinate.z(
				-sin(headAngle) * localBallCoordinate.x()
						+ cos(headAngle) * localBallCoordinate.z()); //旋转矩阵

		///		float myBodyAngleToXAxis=GetBodyToX();
		float myBodyAngleToXAxis = GetMyBodyAngleToXAxis();
		float ballAngleToXAxis = myBodyAngleToXAxis + headAngle1;
		float disToBall = GetMyDistanceToBall();
		Vector3 Ball =
				Vector3(
						(myCoordinate.x()
								+ disToBall * cos(ballAngleToXAxis * PI / 180)), myCoordinate.y()+disToBall*sin(ballAngleToXAxis*PI/180),0);

		//cout << "Ball:" << Ball << endl;

		BallSaveCoordinate.insert(tempBallCoordinate);
		ballCoordinate = myCoordinate + tempBallCoordinate;

		if (CITConf.DrawerBug)
		{
			if (GetMyNumber() != 0)
			{
				string n1 = GetMyTeamName() + "Coordinate.Ball."
						+ Convert::ToString(GetMyNumber());
				RGBDraw rgb(1, 0.9, 0.6);
			//	cout << "n1-------::" << n1 << endl;
				CITMDrawer.drawPoint(ballCoordinate, 5, rgb, &n1);
				CITMDrawer.UpdateDrawer(&n1);
			}
		}
		///cout<<"ballCoordinate:"<<ballCoordinate<<endl;

#if 0
		if(ballCoordinate.x()>GetFieldLength()/2)
		{
			ballCoordinate.x(GetFieldLength()/2);
			///	///cout<<"ballCoordinate.x("<<GetFieldLength()/2<<")"<<endl;
		}
		else if(ballCoordinate.x()<-GetFieldLength()/2)
		{
			ballCoordinate.x(-GetFieldLength()/2);
			///	///cout<<"ballCoordinate.x(-"<<GetFieldLength()/2<<")"<<endl;
		}
		else if(ballCoordinate.y()<-GetFieldWidth()/2)
		{
			ballCoordinate.y(-GetFieldWidth()/2);
			///	///cout<<"ballCoordinate.y(-"<<GetFieldWidth()/2<<")"<<endl;
		}
		else if(ballCoordinate.y()>GetFieldWidth()/2)
		{
			ballCoordinate.y(GetFieldWidth()/2);
			///	///cout<<"ballCoordinate.y("<<GetFieldWidth()/2<<")"<<endl;
		}
#endif

	}
#endif

}

void WorldModel::UpdateMyDistanceToBall() ///this value should be accurately
{
	float theta, distance, temp;
	float headAngle = GetCurrentJointAngle(JID_HEAD_2); //

	if (messageParser.mVisionSenseMap.count(VO_BALL))
	{
		distance = messageParser.mVisionSenseMap[VO_BALL].distance;
		theta = messageParser.mVisionSenseMap[VO_BALL].phi;
		temp = ConvertAngleIntoRadian(-headAngle - theta);
		myDistanceToBall = distance * cos(temp);

	}

}

void WorldModel::UpdateMyTeamScore()
{
	if (lastCycleGameMode == PM_Goal_Our
			&& lastCycleGameMode != myCurrentGameMode)
		myTeamScore++;
}

void WorldModel::UpdateOpponentTeamScore()
{
	if (lastCycleGameMode == PM_Goal_Opp
			&& lastCycleGameMode != myCurrentGameMode)
		opponentTeamScore++;
}

void WorldModel::UpdatePlayerInformation() ///right now useless
{
	ClearPlayerInformation();
	UpdateMyTeammateInformation();
	UpdateOpponentTeamPlayerInformation();
}
void WorldModel::ClearPlayerInformation() ///right now useless
{
	for (int i = 0; i <= PLAYERNUMBER; ++i)
	{
		myTeammate[i].teamName = "";
		myTeammate[i].number = 0;
		myTeammate[i].coordinate = Vector3(0, 0, 0);
		myTeammate[i].distanceToBall = 0;
		myTeammate[i].distanceToMe = 0;
		myTeammate[i].fallDown = false;

		myOpponentTeamPlayer[i].teamName = "";
		myOpponentTeamPlayer[i].number = 0;
		myOpponentTeamPlayer[i].coordinate = Vector3(0, 0, 0);
		myOpponentTeamPlayer[i].distanceToBall = 0;
		myOpponentTeamPlayer[i].distanceToMe = 0;
		myOpponentTeamPlayer[i].fallDown = false;
	}
}
void WorldModel::UpdateMyTeammateInformation() ///right now useless
{
	int counter = 1;
	Vector3 temp_1, temp_2;
	for (int i = 1; i <= PLAYERNUMBER; ++i)
	{
		if (messageParser.teammate[i] == 1 && messageParser.teammate[0] != 0)
		{
			myTeammate[counter].teamName = myTeamName;
			myTeammate[counter].number = i;
			stringstream ss("");
			ss << "tmmt_" << i;

			TVisionObjectMap::iterator iter = mVisionObjectToPlayerMap.find(
					ss.str());
			VisionObject flag = (*iter).second;

			myTeammate[counter].coordinate = mObjectPosMap[flag];

			//calculate distance to ball
			temp_1 = myTeammate[counter].coordinate;
			temp_1.z(0);
			temp_2 = ballCoordinate;
			temp_2.z(0);
			myTeammate[counter].distanceToBall = temp_1.getDistanceTo(temp_2);

			//calculate distance to me
			temp_2 = myCoordinate;
			temp_2.z(0);
			myTeammate[counter].distanceToMe = temp_1.getDistanceTo(temp_2);

			//judge if has fallen down
			if (myTeammate[counter].coordinate.z() <= 0.2)
				myTeammate[counter].fallDown = true;

			counter++;
		}
	}
}
void WorldModel::UpdateOpponentTeamPlayerInformation() ///right now useless
{
	int counter = 1;
	Vector3 temp_1, temp_2;
	for (int i = 1; i <= PLAYERNUMBER; ++i)
	{
		if (messageParser.opponentPlayer[i] == 1
				&& messageParser.opponentPlayer[0] != 0)
		{
			myOpponentTeamPlayer[counter].teamName = myOpponentTeamName;
			myOpponentTeamPlayer[counter].number = i;

			stringstream ss("");
			ss << "oppo_" << i;

			TVisionObjectMap::iterator iter = mVisionObjectToPlayerMap.find(
					ss.str());
			VisionObject flag = (*iter).second;

			myOpponentTeamPlayer[counter].coordinate = mObjectPosMap[flag];
			temp_1 = myOpponentTeamPlayer[counter].coordinate;
			temp_1.z(0);
			temp_2 = ballCoordinate;
			temp_2.z(0);
			myOpponentTeamPlayer[counter].distanceToBall = temp_1.getDistanceTo(
					temp_2);
			temp_2 = myCoordinate;
			temp_2.z(0);
			myOpponentTeamPlayer[counter].distanceToMe = temp_1.getDistanceTo(
					temp_2);

			if (myOpponentTeamPlayer[counter].coordinate.z() <= 0.2)
				myOpponentTeamPlayer[counter].fallDown = true;

			counter++;
		}
	}
}

void WorldModel::GetRole(string& str, Role& role, bool& state) ///useless
{
	if (str == "V")
	{
		role = ROLE_VANGUARD;
		state = false;
	}
	else if (str == "VD")
	{
		role = ROLE_VANGUARD;
		state = true;
	}
	else if (str == "V1")
	{
		role = ROLE_VICE_VANGUARD_1;
		state = false;
	}
	else if (str == "V1D")
	{
		role = ROLE_VICE_VANGUARD_1;
		state = true;
	}
	else if (str == "V2")
	{
		role = ROLE_VICE_VANGUARD_2;
		state = false;
	}
	else if (str == "V2D")
	{
		role = ROLE_VICE_VANGUARD_2;
		state = true;
	}
	else if (str == "CF")
	{
		role = ROLE_CENTRE_FORWARD;
		state = false;
	}
	else if (str == "CFD")
	{
		role = ROLE_CENTRE_FORWARD;
		state = true;
	}
	else if (str == "LB")
	{
		role = ROLE_LINEBACKER;
		state = false;
	}
	else if (str == "LBD")
	{
		role = ROLE_LINEBACKER;
		state = true;
	}
	else
	{
		role = ROLE_NULL;
		state = false;
	}
}

void WorldModel::ConvertVisionInformation() ///this part works,read it carefully
{
	///mObjectVectorMap.clear();
	////////cout<<"check whether this part working"<<endl;
	for (TVisionSenseMap::iterator iter = messageParser.mVisionSenseMap.begin(); //messageParser.mVisionSenseMap.find(VO_FLAG1_L);
	iter != messageParser.mVisionSenseMap.end(); iter++)
	{
		VisionObject vo = (*iter).first;

		mObjectVectorMap[vo] = ConvertPolarCoordinatesIntoDecareCoordinates(
				(*iter).second);
	}

//	/////cout<<"local object sense size:"<<mObjectVectorMap.size()<<endl;
}

Vector3 WorldModel::ConvertPolarCoordinatesIntoDecareCoordinates(
		VisionSense& visionInformation)
{
	float theta = ConvertAngleIntoRadian(visionInformation.theta);
	float phi = ConvertAngleIntoRadian(visionInformation.phi);

	float x, y, z;

	x = visionInformation.distance * cos(phi) * cos(theta);
	y = visionInformation.distance * cos(phi) * sin(theta);
	z = visionInformation.distance * sin(phi);

	return GetApproximateValue(Vector3(x, y, z));
}
Vector3 WorldModel::GetApproximateValue(Vector3 Vector)
{
	return Vector3(

	(fabs(Vector.x()) < EPS) ? 0:Vector.x(),

	(fabs(Vector.y())<EPS) ? 0:Vector.y(),

	(fabs(Vector.z())<EPS) ? 0:Vector.z()

	);}
float WorldModel::ConvertAngleIntoRadian(float angle)
{
	return angle * PI / 180;
}

Vector3 WorldModel::GetObjectCoordinate(VisionObject object)
{
	return mObjectPosMap[object];
}

VisionSense WorldModel::GetObjectPolarCoordinate(VisionObject object)
{
	VisionSense vo;
	if (messageParser.mVisionSenseMap.count(object))
	{
		vo = messageParser.mVisionSenseMap[object];
	}

	return vo;
}

Vector3 WorldModel::GetMyMiddleGoalCoordinate()
{
	return myMiddleGoalCoordinate;
}

Vector3 WorldModel::GetOpponentMiddleGoalCoordinate()
{
	return opponentMiddleGoalCoordinate;
}

float WorldModel::GetFieldLength()
{
	return FieldLength;
}

float WorldModel::GetFieldWidth()
{
	return FieldWidth;
}

float WorldModel::GetFieldHeight()
{
	return FieldHeight;
}
float WorldModel::GetGoalWidth()
{
	return GoalWidth;
}
float WorldModel::GetGoalDepth()
{
	return GoalDepth;
}
float WorldModel::GetGoalHeight()
{
	return GoalHeight;
}

float WorldModel::GetPenaltyLength()
{
	return PenaltyLength;
}

float WorldModel::GetPenaltyWidth()
{
	return PenaltyWidth;
}

float WorldModel::GetMyAngleToXCoordinate() ///useless
{
	VisionObject obj = VO_NULL;
	TVisionSenseMap::iterator iter;
	for (iter = messageParser.mVisionSenseMap.begin();
			iter != messageParser.mVisionSenseMap.end(); ++iter)
			{
		obj = (*iter).first;
		if (IsFlag(obj))
		{
			break;
		}
	}

	if (obj != VO_NULL)
	{
		float K = (mObjectPosMap[obj].y() - myCoordinate.y())
				/ (mObjectPosMap[obj].x() - myCoordinate.x());
		float theta = atan(K);
		theta = theta * 180 / PI;

		agentTheta = messageParser.mVisionSenseMap[obj].theta - theta;
	}

	return agentTheta;
}

bool WorldModel::CanIdoDefendingMotion() ///this part will be very useful in the future
{
	bool res = true;

	float defendingRadius_1 = 0.6f, defendingRadius_2 = 1.2f;
	int agentInRadius_1_num = 0, agentInRadius_2_num = 0;
	float myAngleToBall = messageParser.GetVisionPolarCoordinate(VO_BALL).theta;
	float angle = 0, myAngleToAgent = 0;
	for (TPlayerSenseMap::iterator iter =
			messageParser.mTeamMateSenseMap.begin();
			iter != messageParser.mTeamMateSenseMap.end(); ++iter)
			{
		myAngleToAgent = (*iter).second.head.theta;
		if ((myAngleToBall * myAngleToAgent) < 0)
		{
			angle = fabs(myAngleToBall) + fabs(myAngleToAgent);
		}
		else
		{
			angle = fabs(myAngleToBall - myAngleToAgent);
		}

		float dis = 0;
		dis = sqrt(
				myDistanceToBall * myDistanceToBall
						+ (*iter).second.head.distance
								* (*iter).second.head.distance
						- cos(angle * PI / 180) * 2 * myDistanceToBall
								* (*iter).second.head.distance);

		if (dis <= defendingRadius_1)
		{
			agentInRadius_1_num++;
		}

		if (dis <= defendingRadius_2)
		{
			agentInRadius_2_num++;
		}
	}

	if (agentInRadius_1_num >= 2)
		res = false;

	if (agentInRadius_2_num >= 3)
		res = false;

	return res;
}

bool WorldModel::IsFlag(VisionObject obj)
{
	bool res = false;
	switch (obj)
	{
	case VO_FLAG1_L:
		res = true;
		break;
	case VO_FLAG2_L:
		res = true;
		break;
	case VO_GOAL1_L:
		res = true;
		break;
	case VO_GOAL2_L:
		res = true;
		break;
	case VO_FLAG1_R:
		res = true;
		break;
	case VO_FLAG2_R:
		res = true;
		break;
	case VO_GOAL1_R:
		res = true;
		break;
	case VO_GOAL2_R:
		res = true;
		break;
	default:
		break;
	}

	return res;
}

float WorldModel::GetBallRadius()
{
	return ballRadius;
}
int WorldModel::GetMyNumber()
{
	return myNumber;
}

int WorldModel::GetVanguardNumber()
{
	return vanguardNum;
}

TPlayMode WorldModel::GetCurrentGameMode()
{
	return myCurrentGameMode;
}
TTeamIndex WorldModel::GetMyTeamIndex()
{
	return myTeamIndex;
}
void WorldModel::ChangeMyTeamIndex()
{
	messageParser.ChangeMyTeamIndex();
	UpdateTeamIndex();
}
float WorldModel::GetCurrentGameTime()
{
	return myGameTime;
}
float WorldModel::GetCurrentServerTime()
{
	return myServerTime;
}
string WorldModel::GetMyOpponentTeamName()
{
	return myOpponentTeamName;
}
string WorldModel::GetMyTeamName()
{
	return myTeamName;
}
Vector3 WorldModel::GetMyBeamCoordinate()
{
	return myBeamCoordinate;
}
Vector3 WorldModel::GetMyCoordinate()
{
///	if(CanLocalizeDirect==true)
//	cout<<"canLocalizeDirect"<<endl;
//	cout<<canLocalizeDirect<<endl;

	if(this->canLocalizeDirect)
	{
		return myCoordinate;
	}
	else
	{
		return this->GetLastCyclesAverageMyCoordinate();
	}

}
Vector3 WorldModel::GetBallCoordinate()
{
	if(this->CanSeeTheBall())
	{
		return ballCoordinate;
	}
	else
	{
		return this->GetLastCyclesAverageBallCoordinate();
	}
}

bool WorldModel::IsVanguardFallDown()
{
	return vanguardFallDown;
}

bool WorldModel::CanDoLocalizationDirectly()
{
	return canLocalizeDirect;
}

void WorldModel::JudgeFallDirection() ///useless
{
	/**lr*/ ///judge fallDirection one more time
	/////cout<<"---------------------------getAverageOfLastCyclesGYR().x(): "<<getAverageOfLastCyclesGYR().x()<<endl;
	if (getAverageOfLastCyclesGYR().x() > 200)
	{
		fallDirection = D_BACK;
		/////cout<<"----------getAverageOfLastCyclesGYR().x()>250: "<<getAverageOfLastCyclesGYR().x()<<endl;
	}
	else if (getAverageOfLastCyclesGYR().x() < -200)
	{
		fallDirection = D_FORWARD;
		/////cout<<"----------getAverageOfLastCyclesGYR().x()<250"<<getAverageOfLastCyclesGYR().x()<<endl;
	}
}

FallDirection WorldModel::GetMyFallDirection()
{
	return fallDirection;
}
float WorldModel::GetMyDistanceToBall()
{
	return myDistanceToBall;
}

float WorldModel::GetMyAngleToBall()
{
	//return messageParser.GetVisionPolarCoordinate(VO_BALL).theta;
	return historySenseMap[VO_BALL].theta;
}

float WorldModel::GetMyDistanceToFlag(VisionObject obj)
{
	float dis = 0;
	if (messageParser.mVisionSenseMap.count(obj))
	{
		dis = messageParser.mVisionSenseMap[obj].distance;
	}

	return dis;
}

float WorldModel::GetMyAngleToFlag(VisionObject obj)
{
	float angle = 0;
	if (messageParser.mVisionSenseMap[obj].phi != 0)
	{
		angle = messageParser.mVisionSenseMap[obj].theta;
	}

	return angle;
}

float WorldModel::GetMyDistanceToTeammate(int num)
{
	float dis = 0;
	for (TPlayerSenseMap::iterator iter =
			messageParser.mTeamMateSenseMap.begin();
			iter != messageParser.mTeamMateSenseMap.end(); ++iter)
			{
		if (num == (*iter).second.unum)
		{
			dis = (*iter).second.head.distance;
			break;
		}
	}

	return dis;
}

float WorldModel::GetMyAngleToTeammate(int num)
{
	float angle = 0;
	for (TPlayerSenseMap::iterator iter =
			messageParser.mTeamMateSenseMap.begin();
			iter != messageParser.mTeamMateSenseMap.end(); ++iter)
			{
		if (num == (*iter).second.unum)
		{
			angle = (*iter).second.head.theta;
			break;
		}
	}

	return angle;
}

bool WorldModel::GetGoalieToBallDistance(float& dis)
{
	bool res = false;

	if (GetMyNumber() == 1) //myself is goalie!!!
	{
		dis = GetMyDistanceToBall();
		res = true;
		return res;
	}

	float mDisToGoalie, mAngleToGoalie;
	for (TPlayerSenseMap::iterator iter = RecordTeamMateSenseMap.begin();
			iter != RecordTeamMateSenseMap.end(); ++iter)
			{
		if (1 == (*iter).second.unum && (*iter).second.head.distance != 0) //goalie's team number is 1
		{

			mDisToGoalie = (*iter).second.head.distance;
			mAngleToGoalie = (*iter).second.head.theta;

			res = true;
			break;
		}
	}

	float myAngleToBall = GetMyAngleToBall(), myDistanceToBall =
			GetMyDistanceToBall();
	float angle;
	if ((myAngleToBall * mAngleToGoalie) < 0)
	{
		angle = fabs(myAngleToBall) + fabs(mAngleToGoalie);
	}
	else
	{
		angle = fabs(myAngleToBall - mAngleToGoalie);
	}
	dis = sqrt(
			myDistanceToBall * myDistanceToBall + mDisToGoalie * mDisToGoalie
					- cos(angle * PI / 180) * 2 * myDistanceToBall
							* mDisToGoalie);

	return res;
}

bool WorldModel::GetVanguardToBallDistance(float& dis)
{
	bool res = false;
	if (!CanSeeTheBall())
	{
		return false;
	}

	if (!CanSeeMyTeammate(GetVanguardNumber()))
	{
		return false;
	}

	float mDisToVanguard, mAngleToVanguard;
	for (TPlayerSenseMap::iterator iter =
			messageParser.mTeamMateSenseMap.begin();
			iter != messageParser.mTeamMateSenseMap.end(); ++iter)
			{
		if (GetVanguardNumber() == (*iter).second.unum)
		{
			mDisToVanguard = (*iter).second.head.distance;
			mAngleToVanguard = (*iter).second.head.theta;
			res = true;
			break;
		}
	}

	float myAngleToBall = GetMyAngleToBall(), myDistanceToBall =
			GetMyDistanceToBall();
	float angle;
	if ((myAngleToBall * mAngleToVanguard) < 0)
	{
		angle = fabs(myAngleToBall) + fabs(mAngleToVanguard);
	}
	else
	{
		angle = fabs(myAngleToBall - mAngleToVanguard);
	}
	dis = sqrt(
			myDistanceToBall * myDistanceToBall
					+ mDisToVanguard * mDisToVanguard
					- cos(angle * PI / 180) * 2 * myDistanceToBall
							* mDisToVanguard);

	return res;
}

int WorldModel::GetMyTeamScore()
{
	return myTeamScore;
}
int WorldModel::GetOpponentTeamScore()
{
	return opponentTeamScore;
}

bool WorldModel::WhetherFaceToOpponentField()
{
	float angle = agentTheta;
	if (fabs(angle) < 60)
		return true;
	else
		return false;
}
bool WorldModel::IsGameModeChanged()
{
	if (myCurrentGameMode != lastCycleGameMode)
		return true;
	else
		return false;
}

bool WorldModel::CanSeeTheBall()
{
	bool res = false;
	if (messageParser.mVisionSenseMap[VO_BALL].phi != 0)
	{
		res = true;
	}

	return res;
}

bool WorldModel::CanSeeTheOppGoal()
{
	bool res = false;
	if (myTeamIndex == TI_LEFT)
	{
		if (messageParser.mVisionSenseMap.count(VO_GOAL1_R)
				|| messageParser.mVisionSenseMap.count(VO_GOAL2_R))
			res = true;
	}
	else if (myTeamIndex == TI_RIGHT)
	{
		if (messageParser.mVisionSenseMap.count(VO_GOAL1_L)
				|| messageParser.mVisionSenseMap.count(VO_GOAL2_L))
			res = true;
	}

	return res;
}

bool WorldModel::CanSeeMyOwnGoal()
{
	bool res = false;
	if (myTeamIndex == TI_LEFT)
	{
		if (messageParser.mVisionSenseMap.count(VO_GOAL1_L)
				|| messageParser.mVisionSenseMap.count(VO_GOAL2_L))
			res = true;
	}
	else if (myTeamIndex == TI_RIGHT)
	{
		if (messageParser.mVisionSenseMap.count(VO_GOAL1_R)
				|| messageParser.mVisionSenseMap.count(VO_GOAL2_R))
			res = true;
	}

	return res;
}

bool WorldModel::CanSeeMyHalfFieldFlag()
{
	bool res = false;
	if (myTeamIndex == TI_LEFT)
	{
		if (messageParser.mVisionSenseMap.count(VO_GOAL1_L)
				|| messageParser.mVisionSenseMap.count(VO_GOAL2_L))
			res = true;

		if (messageParser.mVisionSenseMap.count(VO_FLAG1_L)
				|| messageParser.mVisionSenseMap.count(VO_FLAG2_L))
			res = true;
	}
	else if (myTeamIndex == TI_RIGHT)
	{

		if (messageParser.mVisionSenseMap.count(VO_GOAL1_R)
				|| messageParser.mVisionSenseMap.count(VO_GOAL2_R))
			res = true;

		if (messageParser.mVisionSenseMap.count(VO_FLAG1_R)
				|| messageParser.mVisionSenseMap.count(VO_FLAG2_R))
			res = true;
	}

	return res;
}

bool WorldModel::CanSeeOppHalfFieldFlag()
{
	bool res = false;
	if (myTeamIndex == TI_LEFT)
	{
		if (messageParser.mVisionSenseMap.count(VO_GOAL1_R)
				|| messageParser.mVisionSenseMap.count(VO_GOAL2_R))
			res = true;

		if (messageParser.mVisionSenseMap.count(VO_FLAG1_R)
				|| messageParser.mVisionSenseMap.count(VO_FLAG2_R))
			res = true;
	}
	else if (myTeamIndex == TI_RIGHT)
	{
		if (messageParser.mVisionSenseMap.count(VO_GOAL1_L)
				|| messageParser.mVisionSenseMap.count(VO_GOAL2_L))
			res = true;

		if (messageParser.mVisionSenseMap.count(VO_FLAG1_L)
				|| messageParser.mVisionSenseMap.count(VO_FLAG2_L))
			res = true;
	}

	return res;
}

bool WorldModel::CanSeeTheFlag(VisionObject obj)
{
	bool res = false;
	if (messageParser.mVisionSenseMap.count(obj))
	{
		res = true;
	}

	return res;
}

bool WorldModel::CanSeeMyTeammate(int unum)
{
	bool res = false;
	for (TPlayerSenseMap::iterator iter =
			messageParser.mTeamMateSenseMap.begin();
			iter != messageParser.mTeamMateSenseMap.end(); ++iter)
			{
		if (unum == (*iter).second.unum)
		{
			res = true;
			break;
		}
	}

	return res;
}

bool WorldModel::DoesVanguardCanHandleBall()
{
	bool res = true; //default:vanguard can handle ball
	if (!CanSeeTheBall())
	{
		return false;
	}

	if (!CanSeeMyTeammate(vanguardNum))
	{
		return false;
	}

	float mAngleToVanguard = 0.0f, mAngleToBall = 0.0f;
	float mDisToVanguard = 0.0f, mDisToBall = 0.0f;
	mAngleToVanguard = GetMyAngleToTeammate(vanguardNum);
	mAngleToBall = GetMyAngleToBall();
	mDisToVanguard = GetMyDistanceToTeammate(vanguardNum);
	mDisToBall = GetMyDistanceToBall();

	float angle;
	if ((mAngleToVanguard * mAngleToBall) < 0)
	{
		angle = fabs(mAngleToVanguard) + fabs(mAngleToBall);
	}
	else
	{
		angle = fabs(mAngleToVanguard - mAngleToBall);
	}
	float disOfBallToVanguard = 0;
	disOfBallToVanguard = sqrt(
			mDisToBall * mDisToBall + mDisToVanguard * mDisToVanguard
					- cos(angle * PI / 180) * 2 * mDisToBall * mDisToVanguard);
	//if( disOfBallToVanguard<=0.4 )
	//	return false;
	float judgeAngle = acos(
			(mDisToBall * mDisToBall + disOfBallToVanguard * disOfBallToVanguard
					- mDisToVanguard * mDisToVanguard)
					/ (2 * mDisToBall * disOfBallToVanguard));
	judgeAngle = judgeAngle * 180 / PI;

	if (judgeAngle > 120)
		res = false;

	if (judgeAngle > 90 && disOfBallToVanguard >= 0.4)
		res = false;

	return res;
}

bool WorldModel::IsBallInMyOwnPenaltyArea()
{
	bool res = false;
//	int count=0;        ///       lr add for the judgement below
	for (TVisionSenseMap::iterator iter = messageParser.mVisionSenseMap.begin();
			iter != messageParser.mVisionSenseMap.end(); ++iter)
			{
		float angle = 0, angleToBall = GetMyAngleToBall(), angleToFlag =
				iter->second.theta;
		if ((angleToBall * angleToFlag) < 0)
		{
			angle = fabs(angleToBall) + fabs(angleToFlag);
		}
		else
		{
			angle = fabs(angleToBall - angleToFlag);
		}

		float dis = 0, disToBall = GetMyDistanceToBall(), disToFlag =
				iter->second.distance;
		dis = sqrt(
				disToBall * disToBall + disToFlag * disToFlag
						- cos(angle * PI / 180) * 2 * disToBall * disToFlag);

		float compareDis = 0;
		if (GetMyTeamIndex() == TI_LEFT)
		{
			if (iter->first == VO_FLAG1_R || iter->first == VO_FLAG2_R)
			{
				float d1 = FieldLength - PenaltyLength, d2 = FieldWidth / 2
						- PenaltyWidth / 2;
				compareDis = sqrt(d1 * d1 + d2 * d2);
			}

			if (iter->first == VO_GOAL1_R || iter->first == VO_GOAL2_R)
			{
				compareDis = FieldLength - PenaltyLength;
			}

			if (iter->first == VO_FLAG1_L || iter->first == VO_FLAG2_L)
			{
				compareDis = FieldWidth / 2 - PenaltyWidth / 2;
			}
		}
		else if (GetMyTeamIndex() == TI_RIGHT)
		{
			if (iter->first == VO_FLAG1_L || iter->first == VO_FLAG2_L)
			{
				float d1 = FieldLength - PenaltyLength, d2 = FieldWidth / 2
						- PenaltyWidth / 2;
				compareDis = sqrt(d1 * d1 + d2 * d2);
			}

			if (iter->first == VO_GOAL1_L || iter->first == VO_GOAL2_L)
			{
				compareDis = FieldLength - PenaltyLength;
			}

			if (iter->first == VO_FLAG1_R || iter->first == VO_FLAG2_R)
			{
				compareDis = FieldWidth / 2 - PenaltyWidth / 2;
			}
		}
		/**      i don't know it why can not work successfully without this judgement      */
///		count++;
///		/////cout<<"dis:           "<<dis<<"    compareDis:     "<<compareDis<<endl;
		if (compareDis > 10)
		{
			if (dis > compareDis)
			{
//				/////cout<<"222222222222333"<<endl;
				res = true;
				break;
			}
		}
//		else
//			count=0;

///		if( dis>compareDis )		/// old version
///		{
///			res=true;
///			break;
///		}
		/**           end         */
	}

	if (res == false)
	{
		if (GetMyTeamIndex() == TI_LEFT)
		{
			if (messageParser.mVisionSenseMap.count(VO_BALL))
			{
				if (messageParser.mVisionSenseMap.count(VO_GOAL1_L)
						|| messageParser.mVisionSenseMap.count(VO_GOAL2_L))
				{
//					/////cout<<"3333333333333333444"<<endl;
					res = true;
				}
			}
		}
		else if (GetMyTeamIndex() == TI_RIGHT)
		{
			if (messageParser.mVisionSenseMap.count(VO_BALL))
			{
				if (messageParser.mVisionSenseMap.count(VO_GOAL1_R)
						|| messageParser.mVisionSenseMap.count(VO_GOAL2_R))
				{
//					/////cout<<"55555555555555666"<<endl;
					res = true;
				}
			}
		}
	}
	else
	{
		if (GetMyTeamIndex() == TI_LEFT)
		{
			if (messageParser.mVisionSenseMap.count(VO_GOAL1_L)
					|| messageParser.mVisionSenseMap.count(VO_GOAL2_L))
			{
				if (!messageParser.mVisionSenseMap.count(VO_BALL))
					res = false;
			}
		}
		else if (GetMyTeamIndex() == TI_RIGHT)
		{
			if (messageParser.mVisionSenseMap.count(VO_GOAL1_R)
					|| messageParser.mVisionSenseMap.count(VO_GOAL2_R))
			{
				if (!messageParser.mVisionSenseMap.count(VO_BALL))
					res = false;
			}
		}
	}

	if (!messageParser.mVisionSenseMap.count(VO_BALL)) //can not see my ball
		res = false;
//	/////cout<<"res:  "<<res<<endl;
//	/////cout<<"true: "<<true<<"   false:   "<<false<<endl;
	return res;
}

void WorldModel::GetMyTeammateVector(PlayerVector& playerVector) ///i don't know what's the meaning of this two parts///right useless
{
	playerVector.clear();
	for (int i = 1; i <= PLAYERNUMBER; ++i)
	{
		if (myTeammate[i].number == 0)
			continue;
		else
		{
			playerVector.push_back(myTeammate[i]);
		}
	}
}
void WorldModel::GeyMyOpponentPlayerVector(PlayerVector& playerVector) ///i don't know what's the meaning of this two parts///right useless
{
	playerVector.clear();
	for (int i = 1; i <= PLAYERNUMBER; ++i)
	{
		if (myOpponentTeamPlayer[i].number == 0)
			continue;
		else
		{
			playerVector.push_back(myOpponentTeamPlayer[i]);
		}
	}
}

int WorldModel::GetTheMinDistanceToBallTeammateNum()
{
	int num = GetMyNumber();
	float minDis = myDistanceToBall;
	float myAngleToBall = messageParser.GetVisionPolarCoordinate(VO_BALL).theta;
	float angle = 0, myAngleToAgent = 0;
	for (TPlayerSenseMap::iterator iter =
			messageParser.mTeamMateSenseMap.begin();
			iter != messageParser.mTeamMateSenseMap.end(); ++iter)
			{
		myAngleToAgent = (*iter).second.head.theta;
		if ((myAngleToBall * myAngleToAgent) < 0)
		{
			angle = fabs(myAngleToBall) + fabs(myAngleToAgent);
		}
		else
		{
			angle = fabs(myAngleToBall - myAngleToAgent);
		}

		float dis = 0;
		dis = sqrt(
				myDistanceToBall * myDistanceToBall
						+ (*iter).second.head.distance
								* (*iter).second.head.distance
						- cos(angle * PI / 180) * 2 * myDistanceToBall
								* (*iter).second.head.distance);

		if (dis < minDis)
		{
			minDis = dis;
			num = (*iter).second.unum;
		}
	}

	/////cout<<"qweqweqwe num:"<<num<<endl;
	/////cout<<"qweqewqe minDis:"<<minDis<<endl;
	return num;
}

bool WorldModel::GetMyDistanceToBallSortedIndex(int& index)
{
	index = 1;
	float myAngleToBall = messageParser.GetVisionPolarCoordinate(VO_BALL).theta;
	float angle = 0, myAngleToAgent = 0;

	for (TPlayerSenseMap::iterator iter =
			messageParser.mTeamMateSenseMap.begin();
			iter != messageParser.mTeamMateSenseMap.end(); ++iter)
			{
		myAngleToAgent = (*iter).second.head.theta;
		if ((myAngleToBall * myAngleToAgent) < 0)
		{
			angle = fabs(myAngleToBall) + fabs(myAngleToAgent);
		}
		else
		{
			angle = fabs(myAngleToBall - myAngleToAgent);
		}

		float dis = 0;
		dis = sqrt(
				myDistanceToBall * myDistanceToBall
						+ (*iter).second.head.distance
								* (*iter).second.head.distance
						- cos(angle * PI / 180) * 2 * myDistanceToBall
								* (*iter).second.head.distance);
		float adjust;
		adjust = getClosenessToBallMeasure((*iter).second.unum);
		dis = dis + adjust;

		Vector3 teammateCoordinate = GetTeammateCoordinate((*iter).second.unum);
		///cout<<"teammateCoordinate:  "<<(*iter).second.unum<<"   :   "<<teammateCoordinate<<" 0.2*GetFieldLength()/2:"<<0.2*GetFieldLength()/2<<endl;
		int myNumber = GetMyNumber();
		if (dis < (myDistanceToBall + getClosenessToBallMeasure(myNumber))
				&& (*iter).second.unum != 1) ///changed by gaojin
		{
			int temp = index;
			if ((*iter).second.unum == 5
					&& teammateCoordinate.x() < 0.2 * GetFieldLength() / 2)
			{
				///cout<<"index=index5"<<endl;
				index = temp;
			}
			else if ((*iter).second.unum == 6
					&& teammateCoordinate.x() < 0.2 * GetFieldLength() / 2)
			{
				///cout<<"index=index6"<<endl;
				index = temp;
			}
			else if ((*iter).second.unum == 7
					&& teammateCoordinate.x() < 0.2 * GetFieldLength() / 2)
			{
				///cout<<"index=index7"<<endl;
				index = temp;
			}
			else if ((*iter).second.unum == 8
					&& teammateCoordinate.x() < 0.2 * GetFieldLength() / 2)
			{
				///cout<<"index=index8"<<endl;
				index = temp;
			}
			else if ((*iter).second.unum == 9
					&& teammateCoordinate.x() < 0.2 * GetFieldLength() / 2)
			{
				///cout<<"index=index9"<<endl;
				index = temp;
			}
			else
			{
				///cout<<"index++"<<endl;
				index++;
			}
		}
	}

	return index;
}

int WorldModel::GetMyTeammateAmount() ///useless
{
// 	if(!messageParser.mTeamMateSenseMap.empty())
// 	{
// 		myTeammateAmount=messageParser.mTeamMateSenseMap.size();
// 	}
	myTeammateAmount = myTeammateHistorySenseMap.size();
	return myTeammateAmount;
}

float WorldModel::GetCurrentJointAngle(JointID id)
{
	return messageParser.GetCurrentJiontAngle(id);
}

std::string WorldModel::GetEncapsulatedWords(std::string words)
{
	std::stringstream ss("");
	if (CanSeeTheBall())
	{
///		ss<<"sk"<<GetMyNumber()<<" | "<<words<<"|"<<"B"<<rint(GetMyDistanceToBall()*100)*0.01;

		if (GetCurrentGameTime() < 10)
		{
			ss << "s" << GetMyNumber() << "T00" << GetCurrentGameTime() + 0.01
					<< words;
		}
		else if (GetCurrentGameTime() >= 10 && GetCurrentGameTime() < 100)
		{
			ss << "s" << GetMyNumber() << "T0" << GetCurrentGameTime() + 0.01
					<< words;
		}
		else if (GetCurrentGameTime() >= 100)
		{
			ss << "s" << GetMyNumber() << "T" << GetCurrentGameTime() + 0.01
					<< words;
		}

		//	ss<<"s"<<GetMyNumber()<<"T"<<GetCurrentGameTime()<<words;
	}
	else
	{
		if (GetCurrentGameTime() < 10)
		{
			ss << "s" << GetMyNumber() << "T00" << GetCurrentGameTime()
					<< words;
		}
		else if (GetCurrentGameTime() > 10 && GetCurrentGameTime() < 100)
		{
			ss << "s" << GetMyNumber() << "T0" << GetCurrentGameTime() << words;
		}
		else if (GetCurrentGameTime() > 100)
		{
			ss << "s" << GetMyNumber() << "T" << GetCurrentGameTime() << words;
		}
		else if (GetCurrentGameTime() == 10)
		{
			ss << "s" << GetMyNumber() << "T010.00" << words;
		}
		else if (GetCurrentGameTime() == 100)
		{
			ss << "s" << GetMyNumber() << "T100.00" << words;
		}
	}

	return ss.str();
}

Vector3 WorldModel::GetVanPosition() ///add by czg	useless
{
	Vector3 VanCoordinate(0, 0, 0);
	float Distance, Angle, temp, x, y, angle;
	if (!(GetMyBodyAngleToXAxis(angle)))
		return VanCoordinate;
	Distance = GetMyDistanceToTeammate(GetVanguardNumber());
	Angle = GetMyAngleToTeammate(GetVanguardNumber());
	temp = ConvertAngleIntoRadian(angle + Angle);
	x = Distance * cos(temp);
	y = Distance * sin(temp);
	VanCoordinate.x(myCoordinate.x() + x);
	VanCoordinate.y(myCoordinate.y() + y);
	VanCoordinate.z(0.47);
//	/////cout<<"time is      "<<GetCurrentGameTime()<<endl;
//	/////cout<<"2	VanCoordinate              "<<VanCoordinate<<endl;
	return VanCoordinate;
}

void WorldModel::CalculateGyr() ///add by czg
{
	static float gyrox = 0, gyroy = 0;

	gyr[0] = 0;
	gyr[1] = 0;
	gyr[2] = 0;
	SGYRSensor gyrSensor = messageParser.GetGYR();
	for (int i = 0; i < times - 1; i++)
	{
		gyr_x[i] = gyr_x[i + 1];
		gyr_y[i] = gyr_y[i + 1];
		gyr_z[i] = gyr_z[i + 1];
	}
	gyr_x[times - 1] = gyrSensor.x;
	gyr_y[times - 1] = gyrSensor.y;
	gyr_z[times - 1] = gyrSensor.z;

	for (int i = 1; i < times; i++)
	{
		gyr[0] = gyr[0] + (gyr_x[i - 1] + gyr_x[i]) * 0.01;
		gyr[1] = gyr[1] + (gyr_y[i - 1] + gyr_y[i]) * 0.01;
		gyr[2] = gyr[2] + (gyr_z[i - 1] + gyr_z[i]) * 0.01;
	}
	int i = times;

	if (messageParser.GetCurrentGameMode() == PM_Goal_Our
			|| messageParser.GetCurrentGameMode() == PM_Goal_Opp)
	{
		gyrox = 0;
		gyroy = 0;
		gyroz = 0;
	}
//		/////cout<<"myBodyToXAxisAngle		"<<myBodyToXAxisAngle<<endl;
	if (fabs(myCoordinate.x() - mytempCoordinate.x()) > 0.3
			&& canLocalizeDirect)
	{

		//	gyroz=myBodyToXAxisAngle;

		///////cout<<"-------------------------gyroz  changed by myBodyToXAxisAngle----------------------"<<endl;
	}
	gyrox = gyrox + (gyr_x[i - 2] + gyr_x[i - 1]) * 0.01;
	gyroy = gyroy + (gyr_y[i - 2] + gyr_y[i - 1]) * 0.01;
	gyroz = gyroz + (gyr_z[i - 2] + gyr_z[i - 1]) * 0.01;

	if (gyroz > 180)
		gyroz = gyroz - 360;
	if (gyroz < -180)
		gyroz = gyroz + 360;

	BodyToX = gyroz;
	///cout<<"GYR:***************************************************"<<BodyToX<<endl;
}

int * WorldModel::GetLocFlag() ///add by czg
{
	return locflag;
}
float * WorldModel::GetLocThetaindex() ///add by czg
{
	return thetaindex;
}

void WorldModel::RecordTeammatePos() ///add by czg
{
	static int teammatecount = 1;
	//int temp;
	Vector3 middle;
	for (TPlayerSenseMap::iterator iter =
			messageParser.mTeamMateSenseMap.begin();
			iter != messageParser.mTeamMateSenseMap.end(); ++iter)
			{
		if (CanDoLocalizationDirectly())
		{
			VisionSense TeammateSense = (*iter).second.head;

			float myAngleToXCoordinate, temp, theta;
			GetMyBodyAngleToXAxis(myAngleToXCoordinate);
			theta = ConvertAngleIntoRadian(myAngleToXCoordinate);
			float headAngle = GetCurrentJointAngle(JID_HEAD_2);

			headAngle = -ConvertAngleIntoRadian(headAngle);

			temp = theta;

			Vector3 localTeammateCoordinate =
					ConvertPolarCoordinatesIntoDecareCoordinates(TeammateSense);
			Vector3 tempTeammateCoordinate;

			tempTeammateCoordinate.x(
					cos(headAngle) * cos(temp) * localTeammateCoordinate.x()
							- sin(temp) * localTeammateCoordinate.y()
							+ sin(headAngle) * cos(temp)
									* localTeammateCoordinate.z());
			tempTeammateCoordinate.y(
					sin(temp) * cos(headAngle) * localTeammateCoordinate.x()
							+ cos(temp) * localTeammateCoordinate.y()
							+ sin(temp) * sin(headAngle)
									* localTeammateCoordinate.z());
			tempTeammateCoordinate.z(
					-sin(headAngle) * localTeammateCoordinate.x()
							+ cos(headAngle) * localTeammateCoordinate.z()); //旋转矩阵

			TeammateCoordinate[iter->first - 8 - 1][teammatecount] =
					myCoordinate + tempTeammateCoordinate;
			///cout<<"RRRRRRRRRTeammateNum is "<<iter->first-8<<" iter->first: "<<iter->first<<" postion is"<<TeammateCoordinate[iter->first-8-1][teammatecount]<<"teammatecount"<<teammatecount<<endl;
			if (teammatecount == RecordTimes + 1)
			{
				for (int i = 1; i <= RecordTimes; i++)
				{
					middle += TeammateCoordinate[iter->first - 8 - 1][i];
					TeammateCoordinate[iter->first - 8 - 1][i] =
							TeammateCoordinate[iter->first - 8 - 1][i + 1];

				}
				TeammateCoordinate[iter->first - 8 - 1][teammatecount] = middle
						/ RecordTimes;
				///cout<<"LLLLLLLLLLLTeammateNum is "<<iter->first-8<<" iter->first: "<<iter->first<<" postion is"<<TeammateCoordinate[iter->first-8-1][teammatecount]<<"teammatecount"<<teammatecount<<endl;
				teammatecount = RecordTimes;
			}
			teammatecount++;
		}
	}
}
void WorldModel::RecordOpponentPos() ///add by czg
{
	static int opponentcount = 1;
	//int temp;
	for (TPlayerSenseMap::iterator iter =
			messageParser.mOpponentSenseMap.begin();
			iter != messageParser.mOpponentSenseMap.end(); ++iter)
			{
		if (CanDoLocalizationDirectly())
		{
			VisionSense OpponentSense = (*iter).second.head;

			float myAngleToXCoordinate, temp, theta;
			GetMyBodyAngleToXAxis(myAngleToXCoordinate);
			theta = ConvertAngleIntoRadian(myAngleToXCoordinate);
			float headAngle = GetCurrentJointAngle(JID_HEAD_2);

			headAngle = -ConvertAngleIntoRadian(headAngle);

			temp = theta;

			Vector3 localOpponentCoordinate =
					ConvertPolarCoordinatesIntoDecareCoordinates(OpponentSense);
			Vector3 tempOpponentCoordinate;

			tempOpponentCoordinate.x(
					cos(headAngle) * cos(temp) * localOpponentCoordinate.x()
							- sin(temp) * localOpponentCoordinate.y()
							+ sin(headAngle) * cos(temp)
									* localOpponentCoordinate.z());
			tempOpponentCoordinate.y(
					sin(temp) * cos(headAngle) * localOpponentCoordinate.x()
							+ cos(temp) * localOpponentCoordinate.y()
							+ sin(temp) * sin(headAngle)
									* localOpponentCoordinate.z());
			tempOpponentCoordinate.z(
					-sin(headAngle) * localOpponentCoordinate.x()
							+ cos(headAngle) * localOpponentCoordinate.z()); //旋转矩阵

			OpponentCoordinate[iter->first - 19 - 1][opponentcount] =
					myCoordinate + tempOpponentCoordinate;
			///cout<<"rrrrrrrrrrOpponentNum is "<<iter->first-19<<"postion is  "<<OpponentCoordinate[iter->first-19-1][opponentcount]<<endl;
			if (opponentcount == RecordTimes + 1)
			{
				for (int i = 1; i <= RecordTimes; i++)
				{
					OpponentCoordinate[iter->first - 19 - 1][i] =
							OpponentCoordinate[iter->first - 19 - 1][i + 1];
				}
				opponentcount = RecordTimes;
			}
			opponentcount++;

		}
	}
}
/**              lr               */

float WorldModel::GetMyBodyAngleToXAxis()
{
	return myBodyToXAxisAngle;
}

float WorldModel::GetMyHeadAngleToXAxis()
{
	return myHeadToXAxisAngle;
}

float WorldModel::GetAngleBetweenBallMeAndXAxis()
{
	float angleBetweenBallMeAndXAxis;
	angleBetweenBallMeAndXAxis=CITMath::GetTwoPointWithXangle(GetMyCoordinate(),GetBallCoordinate());
	return angleBetweenBallMeAndXAxis;
}

float WorldModel::GetAngleBetweenBallMeAndBallOppGoal()
{
	return angleBetweenBallMeAndBallOppGoal;
}

bool WorldModel::IsOppTeamKick()
{
	bool res = false;
	switch (GetCurrentGameMode())
	{
	case PM_KickIn_Opp:
		res = true;

		break;
	case PM_CORNER_KICK_Opp:
		res = true;
		break;
	case PM_GOAL_KICK_Opp:
		res = true;
		break;
	case PM_FREE_KICK_Opp:
		res = true;
		break;
	}

	return res;
}

void WorldModel::updateLastCyclesAverageBallCoordinate()
{
	static int point = 0;

//	static int point2=0;
//	static int point3=0;
	if (CanSeeTheBall())
	{
		if (whetherLastCycleSeeBall == false)
		{
			for (int i = 0; i < LASTCYCLESOFBALL; i++)
				lastCyclesBallCoordinate[i] = GetBallCoordinate();

// 		  for(int i=0;i<LAST_CYCLES_OF_BALL_FOR_RUN_FORMATION;i++)
// 		    lastCyclesBallCoordinateForRunFormation[i]=GetBallCoordinate();
		}
		else
		{
			lastCyclesBallCoordinate[point % LASTCYCLESOFBALL] =
					GetBallCoordinate();

// 		  if(point2%10==0)
// 		  {
// 		    ///cout<<"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"<<endl;
// 		    lastCyclesBallCoordinateForRunFormation[point3%LAST_CYCLES_OF_BALL_FOR_RUN_FORMATION]=GetBallCoordinate();
// 		    point3++;
// 		  }
		}

		///cout<<"BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB"<<endl;
		//	///cout<<"can  see ball lastCyclesBallCoordinate[ "<<point%LASTCYCLESOFBALL<<" ]"<<endl;
		whetherLastCycleSeeBall = true;
	}
	else
	{
		whetherLastCycleSeeBall = false;
		lastCyclesBallCoordinate[point % LASTCYCLESOFBALL] =
				GetLastCyclesAverageBallCoordinate();
		//	lastCyclesBallCoordinateForRunFormation[point2%LAST_CYCLES_OF_BALL_FOR_RUN_FORMATION]=GetLastCyclesAverageBallCoordinate();
//		/////cout<<"can not see ball lastCyclesBallCoordinate[ "<<point%LASTCYCLESOFBALL<<" ]"<<endl;
	}
	point++;
//	point2++;

	Vector3 ball;
	Vector3 middle = Vector3(0, 0, 0);
	for (int i = 0; i < LASTCYCLESOFBALL; i++)
	{
		//	ball=Vector3( lastCyclesBallCoordinate[i].x,lastCyclesBallCoordinate[i].y,lastCyclesBallCoordinate[i].z   );
		///cout<<"lastCyclesBallCoordinate["<<i<<"]:"<<lastCyclesBallCoordinate[i]<<endl;
		ball = lastCyclesBallCoordinate[i];
		if (fabs(ball.x() - lastCyclesAverageBallCoordinate.x()) > 0.1)
		{
//			/////cout<<"DDDDDDDDDDDlastCyclesBallCoordinate[  " <<i<<"  ]:   "<<lastCyclesBallCoordinate[i]<<endl;
		}
		else if (fabs(ball.y() - lastCyclesAverageBallCoordinate.y()) > 0.1)
		{
//			/////cout<<"EEEEEEEEEEElastCyclesBallCoordinate[  " <<i<<"  ]:   "<<lastCyclesBallCoordinate[i]<<endl;
		}
		middle += ball;
	}
	lastCyclesAverageBallCoordinate = middle / LASTCYCLESOFBALL;

// 	Vector3 middle2,ball2;
// 	for(int i=0;i<LAST_CYCLES_OF_BALL_FOR_RUN_FORMATION;i++)
// 	{
// 	  ///cout<<"lastCyclesBallCoordinateForRunFormation["<<i<<"]:"<<lastCyclesBallCoordinateForRunFormation[i]<<endl;
// 	  ball2=lastCyclesBallCoordinateForRunFormation[i];
// 	  middle2+=ball2;
// 	}
// 	lastCyclesAverageBallCoordinateForRunFormation=middle2/LAST_CYCLES_OF_BALL_FOR_RUN_FORMATION;
//	/////cout<<"FFFFFFFFFFlastCyclesAverageBallCoordinate:    "<<lastCyclesAverageBallCoordinate<<endl;
}

Vector3 WorldModel::GetLastCyclesAverageBallCoordinate()
{
	return lastCyclesAverageBallCoordinate;
}
Vector3 WorldModel::GetfutureBallCoordinate(int numcycles)
{
	return BallSaveCoordinate.GetAverageAcc() * numcycles
			+ BallSaveCoordinate.GetLastVal() + lastCyclesAverageBallCoordinate;
}

void WorldModel::updateLastCyclesAverageMyCoordinate()
{
	static int point = 0;

	if (canDoLocalizationByTwoFlags)
	{
		///cout<<"11"<<endl;
		if (whetherLastCycleDoLocalizationByTwoFlags == false)
		{
			///cout<<"22"<<endl;
			for (int i = 0; i < LASTCYCLESOFMINE; i++)
				lastCyclesMyCoordinate[i] = GetMyCoordinate();
		}
		else
		{
			///cout<<"33"<<endl;
			lastCyclesMyCoordinate[point % LASTCYCLESOFMINE] =
					GetMyCoordinate();
		}
		///cout<<"44"<<endl;
		whetherLastCycleDoLocalizationByTwoFlags = true;
	}
	else
	{
		///cout<<"55"<<endl;
		whetherLastCycleDoLocalizationByTwoFlags = false;
		lastCyclesMyCoordinate[point % LASTCYCLESOFMINE] = GetMyCoordinate(); ///GetMyCoordinate();
	}

	point++;

	Vector3 my;
	Vector3 middle = Vector3(0, 0, 0);

	for (int i = 0; i < LASTCYCLESOFMINE; i++)
	{
		//	my=Vector3(lastCyclesMyCoordinate[i].x,lastCyclesMyCoordinate[i].y,lastCyclesMyCoordinate[i].z  );
		my = lastCyclesMyCoordinate[i];
		///	///cout<<"lastCyclesMyCoordinate["<<i<<"]:"<<lastCyclesMyCoordinate[i]<<endl;
		if (fabs(my.x() - lastCyclesAverageMyCoordinate.x()) > 10
				|| fabs(my.y() - lastCyclesAverageMyCoordinate.y()) > 10
				|| fabs(my.z() - lastCyclesAverageMyCoordinate.z()) > 10)
		{

			//		///cout<<"AAAAAAAAlastCyclesMyCoordinate[  " <<i<<"  ]:   "<<lastCyclesMyCoordinate[i]<<endl;
			//		my=lastCyclesAverageMyCoordinate;

		}
		else /// if( GetCurrentGameMode()!=PM_BeforeKickOff&&fabs(my.y()-lastCyclesAverageMyCoordinate.y())>0.2 &&fabs(my.y()-lastCyclesAverageMyCoordinate.y())<0.5  )
		{
			//		///cout<<"BBBBBBBBlastCyclesMyCoordinate[  " <<i<<"  ]:   "<<lastCyclesMyCoordinate[i]<<endl;
			///	my=lastCyclesAverageMyCoordinate;

		}
		middle += my;
	}

	lastCyclesAverageMyCoordinate = middle / LASTCYCLESOFMINE;

//	/////cout<<"CCCCCCCCClastCyclesAverageMyCoordinate :    "<<lastCyclesAverageMyCoordinate<<endl;
}

/*
 void WorldModel::updateLastCyclesAverageMyCoordinate()
 {
 static int point=0;
 ///	my.reserve(100);
 ///cout<<"my.capacity():"<<my.capacity()<<"  my.max_size:"<<my.max_size()<<"  my.size():"<<my.size()<<endl;
 if(canDoLocalizationByTwoFlags)
 {
 ///cout<<"11"<<endl;
 if(whetherLastCycleDoLocalizationByTwoFlags==false)
 {
 ///cout<<"22"<<endl;
 for(int i=0;i<LASTCYCLESOFMINE;i++)
 my.insert(my.begin()+i,GetMyCoordinate());
 }
 else
 {
 ///cout<<"33"<<endl;
 my.insert(my.begin()+point%LASTCYCLESOFMINE,GetMyCoordinate());
 }
 ///cout<<"44"<<endl;
 whetherLastCycleDoLocalizationByTwoFlags=true;
 }
 else
 {
 ///cout<<"55"<<endl;
 whetherLastCycleDoLocalizationByTwoFlags=false;
 my.insert(my.begin()+point%LASTCYCLESOFMINE,GetMyCoordinate());
 }

 point++;

 Vector3 myy;
 Vector3 middle=Vector3(0,0,0);

 for(int i=0;i<LASTCYCLESOFMINE;i++)
 {
 //	my=Vector3(lastCyclesMyCoordinate[i].x,lastCyclesMyCoordinate[i].y,lastCyclesMyCoordinate[i].z  );
 //	myy=my.at(my.begin()+i);
 myy=my[i];
 ///cout<<"my["<<i<<"]:"<<my[i]<<endl;
 if( GetCurrentGameMode()!=PM_BeforeKickOff&&fabs(myy.x()-lastCyclesAverageMyCoordinate.x())>0.16 &&fabs(myy.x()-lastCyclesAverageMyCoordinate.x())<0.4  )
 {

 //			/////cout<<"AAAAAAAAlastCyclesMyCoordinate[  " <<i<<"  ]:   "<<lastCyclesMyCoordinate[i]<<endl;
 ///	my=lastCyclesAverageMyCoordinate;

 }
 else if( GetCurrentGameMode()!=PM_BeforeKickOff&&fabs(myy.y()-lastCyclesAverageMyCoordinate.y())>0.2 &&fabs(myy.y()-lastCyclesAverageMyCoordinate.y())<0.5  )
 {
 //			/////cout<<"BBBBBBBBlastCyclesMyCoordinate[  " <<i<<"  ]:   "<<lastCyclesMyCoordinate[i]<<endl;
 ///	my=lastCyclesAverageMyCoordinate;

 }
 middle+=myy;
 }

 lastCyclesAverageMyCoordinate=middle/LASTCYCLESOFMINE;


 //	/////cout<<"CCCCCCCCClastCyclesAverageMyCoordinate :    "<<lastCyclesAverageMyCoordinate<<endl;
 }

 */
Vector3 WorldModel::GetLastCyclesAverageMyCoordinate()
{
	return lastCyclesAverageMyCoordinate;
}

void WorldModel::updateMyBodyAngleToBall()
{
	float angle = GetMyAngleToBall();
	myBodyAngleToBall = angle + GetCurrentJointAngle(JID_HEAD_1);
}

float WorldModel::GetMyBodyAngleToBall()
{
	return myBodyAngleToBall;
}

bool WorldModel::WhetherCanAttackOppGoal2()
{

//	Vector3 myCoordiante = GetMyCoordinate();

	if (GetMyTeamIndex() == TI_LEFT)
	{
		/////cout<<"messageParser.mVisionSenseMap.count(VO_GOAL1_R) +2R: "<<messageParser.mVisionSenseMap.count(VO_GOAL1_R)+messageParser.mVisionSenseMap.count(VO_GOAL2_R) <<endl;
		///cout<<"messageParser.mVisionSenseMap.count(VO_GOAL1_R) : "<<messageParser.mVisionSenseMap.count(VO_GOAL1_R) <<endl;
		///cout<<"messageParser.mVisionSenseMap.count(VO_GOAL2_R) : "<<messageParser.mVisionSenseMap.count(VO_GOAL2_R) <<endl;
		///cout<<"messageParser.mVisionSenseMap[VO_GOAL1_R].theta:  "<<messageParser.mVisionSenseMap[VO_GOAL1_R].theta<<endl;
		///cout<<"messageParser.mVisionSenseMap[VO_GOAL2_R].theta:  "<<messageParser.mVisionSenseMap[VO_GOAL2_R].theta<<endl;
		///cout<<"messageParser.mVisionSenseMap[VO_GOAL1_R].phi:  "<<messageParser.mVisionSenseMap[VO_GOAL1_R].phi<<endl;
		///cout<<"messageParser.mVisionSenseMap[VO_GOAL2_R].phi:  "<<messageParser.mVisionSenseMap[VO_GOAL2_R].phi<<endl;
		if (myCoordinate.x() < 5 * CELL_LENGTH)
		{
			if (messageParser.mVisionSenseMap[VO_GOAL1_R].phi != 0
					&& messageParser.mVisionSenseMap[VO_GOAL2_R].phi != 0)
			{
				if (messageParser.mVisionSenseMap[VO_GOAL1_R].theta
						* messageParser.mVisionSenseMap[VO_GOAL2_R].theta < 0)
				{
					///cout<<"a-------------------"<<endl;
					return true;
				}
				else if (fabs(messageParser.mVisionSenseMap[VO_GOAL1_R].theta)
						< 30
						|| fabs(messageParser.mVisionSenseMap[VO_GOAL2_R].theta)
								< 30)
				{
					///cout<<"b-------------------"<<endl;
					return true;
				}
				else
				{
					///cout<<"false-------------1"<<endl;
					return false;
				}

			}
			else if (messageParser.mVisionSenseMap[VO_GOAL1_R].phi == 0
					&& messageParser.mVisionSenseMap[VO_GOAL2_R].phi != 0)
			{
				if (fabs(messageParser.mVisionSenseMap[VO_GOAL2_R].theta) < 30)
				{
					///cout<<"c-------------------"<<endl;
					return true;
				}
				else
				{
					///cout<<"false-------------2"<<endl;
					return false;
				}
			}
			else if (messageParser.mVisionSenseMap[VO_GOAL1_R].phi != 0
					&& messageParser.mVisionSenseMap[VO_GOAL2_R].phi == 0)
			{
				if (fabs(messageParser.mVisionSenseMap[VO_GOAL1_R].theta) < 30)
				{
					///cout<<"c-------------------"<<endl;
					return true;
				}
				else
				{
					///cout<<"false-------------2"<<endl;
					return false;
				}
			}

		}
		else if (myCoordinate.x() >= 5 * CELL_LENGTH
				&& myCoordinate.x() <= 7 * CELL_LENGTH)
		{
			if (messageParser.mVisionSenseMap[VO_GOAL1_R].phi != 0
					&& messageParser.mVisionSenseMap[VO_GOAL2_R].phi != 0)
			{
				float angleBetweenTwoGoal =
						fabs(
								messageParser.mVisionSenseMap[VO_GOAL1_R].theta
										+ messageParser.mVisionSenseMap[VO_GOAL2_R].theta);
				if (fabs(messageParser.mVisionSenseMap[VO_GOAL1_R].theta)
						> 0.3 * angleBetweenTwoGoal
						&& fabs(messageParser.mVisionSenseMap[VO_GOAL2_R].theta)
								> 0.3 * angleBetweenTwoGoal
						&& messageParser.mVisionSenseMap[VO_GOAL2_R].theta
								* messageParser.mVisionSenseMap[VO_GOAL1_R].theta
								< 0)
				{
					///cout<<"y------------------------"<<endl;
					return true;
				}
				else
				{
					///cout<<"y false------------------"<<endl;
					return false;
				}
				/*
				 if(fabs(ball.y())<2*CELL_LENGTH)
				 {

				 if(messageParser.mVisionSenseMap[VO_GOAL1_R].distance<messageParser.mVisionSenseMap[VO_GOAL2_R].distance)
				 {
				 if(messageParser.mVisionSenseMap[VO_GOAL1_R].theta*messageParser.mVisionSenseMap[VO_GOAL2_R].theta<0&&messageParser.mVisionSenseMap[VO_GOAL1_R].theta>15)
				 {
				 ///cout<<"e-------------------"<<endl;
				 return true;
				 }
				 else
				 {
				 ///cout<<"false-------------4"<<endl;
				 return false;
				 }
				 }
				 else
				 {
				 if(messageParser.mVisionSenseMap[VO_GOAL1_R].theta*messageParser.mVisionSenseMap[VO_GOAL2_R].theta<0&&messageParser.mVisionSenseMap[VO_GOAL2_R].theta<-15)
				 {
				 ///cout<<"e222-------------------"<<endl;
				 return true;
				 }
				 else
				 {
				 ///cout<<"false222-------------4"<<endl;
				 return false;
				 }

				 }
				 }
				 else if(fabs(ball.y())>=2*CELL_LENGTH)
				 {
				 if(messageParser.mVisionSenseMap[VO_GOAL1_R].theta*messageParser.mVisionSenseMap[VO_GOAL2_R].theta<0&&(messageParser.mVisionSenseMap[VO_GOAL1_R].theta>15||messageParser.mVisionSenseMap[VO_GOAL2_R].theta<-15))
				 {
				 ///cout<<"e33333-------------------"<<endl;
				 return true;
				 }
				 else
				 {
				 ///cout<<"false33333333-------------4"<<endl;
				 return false;
				 }
				 }*/
			}
			else if (messageParser.mVisionSenseMap[VO_GOAL1_R].phi != 0
					&& messageParser.mVisionSenseMap[VO_GOAL2_R].phi == 0)
			{
				if ((messageParser.mVisionSenseMap[VO_GOAL1_R].theta) > 15)
				{
					///cout<<"g-------------------"<<endl;
					return true;
				}
				else
				{
					///cout<<"false-------------5"<<endl;
					return false;
				}
			}
			else if (messageParser.mVisionSenseMap[VO_GOAL1_R].phi == 0
					&& messageParser.mVisionSenseMap[VO_GOAL2_R].phi != 0)
			{
				if ((messageParser.mVisionSenseMap[VO_GOAL2_R].theta) < -15)
				{
					///cout<<"g-------------------"<<endl;
					return true;
				}
				else
				{
					///cout<<"false-------------5"<<endl;
					return false;
				}
			}
		}
		else if (myCoordinate.x() > 7 * CELL_LENGTH)
		{
			if (messageParser.mVisionSenseMap[VO_GOAL1_R].phi != 0
					&& messageParser.mVisionSenseMap[VO_GOAL2_R].phi != 0)
			{
				if (messageParser.mVisionSenseMap[VO_GOAL1_R].theta
						* messageParser.mVisionSenseMap[VO_GOAL2_R].theta < 0)
				{
					///cout<<"i-------------------"<<endl;
					return true;
				}
				else
				{
					///cout<<"false-------------7"<<endl;
					return false;
				}
			}
			else if (messageParser.mVisionSenseMap[VO_GOAL1_R].phi == 0
					&& messageParser.mVisionSenseMap[VO_GOAL2_R].phi != 0)
			{
				if (messageParser.mVisionSenseMap[VO_GOAL2_R].theta < -15)
				{
					///cout<<"j-------------------"<<endl;
					return true;
				}
				else
				{
					///cout<<"false-------------8"<<endl;
					return false;
				}
			}
			else if (messageParser.mVisionSenseMap[VO_GOAL1_R].phi != 0
					&& messageParser.mVisionSenseMap[VO_GOAL2_R].phi == 0)
			{
				if (messageParser.mVisionSenseMap[VO_GOAL1_R].theta > 15)
				{
					///cout<<"j-------------------"<<endl;
					return true;
				}
				else
				{
					///cout<<"false-------------8"<<endl;
					return false;
				}
			}
		}
		///cout<<"false-------------10"<<endl;
		return false;

	}
	else if (GetMyTeamIndex() == TI_RIGHT)
	{
		/////cout<<"messageParser.mVisionSenseMap.count(VO_GOAL1_R) +2R: "<<messageParser.mVisionSenseMap.count(VO_GOAL1_R)+messageParser.mVisionSenseMap.count(VO_GOAL2_R) <<endl;
		///cout<<"messageParser.mVisionSenseMap.count(VO_GOAL1_L) : "<<messageParser.mVisionSenseMap.count(VO_GOAL1_L) <<endl;
		///cout<<"messageParser.mVisionSenseMap.count(VO_GOAL2_L) : "<<messageParser.mVisionSenseMap.count(VO_GOAL2_L) <<endl;
		///cout<<"messageParser.mVisionSenseMap[VO_GOAL1_L].theta:  "<<messageParser.mVisionSenseMap[VO_GOAL1_L].theta<<endl;
		///cout<<"messageParser.mVisionSenseMap[VO_GOAL2_L].theta:  "<<messageParser.mVisionSenseMap[VO_GOAL2_L].theta<<endl;
		///cout<<"messageParser.mVisionSenseMap[VO_GOAL1_L].phi:  "<<messageParser.mVisionSenseMap[VO_GOAL1_L].phi<<endl;
		///cout<<"messageParser.mVisionSenseMap[VO_GOAL2_L].phi:  "<<messageParser.mVisionSenseMap[VO_GOAL2_L].phi<<endl;
		if (myCoordinate.x() < 5 * CELL_LENGTH)
		{
			if (messageParser.mVisionSenseMap[VO_GOAL1_L].phi != 0
					&& messageParser.mVisionSenseMap[VO_GOAL2_L].phi != 0)
			{
				if (messageParser.mVisionSenseMap[VO_GOAL1_L].theta
						* messageParser.mVisionSenseMap[VO_GOAL2_L].theta < 0)
				{
					///cout<<"a-------------------"<<endl;
					return true;
				}
				else if (fabs(messageParser.mVisionSenseMap[VO_GOAL1_L].theta)
						< 30
						|| fabs(messageParser.mVisionSenseMap[VO_GOAL2_L].theta)
								< 30)
				{
					///cout<<"b-------------------"<<endl;
					return true;
				}
				else
				{
					///cout<<"false-------------1"<<endl;
					return false;
				}

			}
			else if (messageParser.mVisionSenseMap[VO_GOAL1_L].phi == 0
					&& messageParser.mVisionSenseMap[VO_GOAL2_L].phi != 0)
			{
				if (fabs(messageParser.mVisionSenseMap[VO_GOAL2_L].theta) < 30)
				{
					///cout<<"c-------------------"<<endl;
					return true;
				}
				else
				{
					///cout<<"false-------------2"<<endl;
					return false;
				}
			}
			else if (messageParser.mVisionSenseMap[VO_GOAL1_L].phi != 0
					&& messageParser.mVisionSenseMap[VO_GOAL2_L].phi == 0)
			{
				if (fabs(messageParser.mVisionSenseMap[VO_GOAL1_L].theta) < 30)
				{
					///cout<<"c-------------------"<<endl;
					return true;
				}
				else
				{
					///cout<<"false-------------2"<<endl;
					return false;
				}
			}

		}
		else if (myCoordinate.x() >= 5 * CELL_LENGTH
				&& myCoordinate.x() <= 7 * CELL_LENGTH)
		{
			if (messageParser.mVisionSenseMap[VO_GOAL1_L].phi != 0
					&& messageParser.mVisionSenseMap[VO_GOAL2_L].phi != 0)
			{

				float angleBetweenTwoGoal =
						fabs(
								messageParser.mVisionSenseMap[VO_GOAL1_L].theta
										+ messageParser.mVisionSenseMap[VO_GOAL2_L].theta);
				if (fabs(messageParser.mVisionSenseMap[VO_GOAL1_L].theta)
						> 0.3 * angleBetweenTwoGoal
						&& fabs(messageParser.mVisionSenseMap[VO_GOAL2_L].theta)
								> 0.3 * angleBetweenTwoGoal
						&& messageParser.mVisionSenseMap[VO_GOAL2_L].theta
								* messageParser.mVisionSenseMap[VO_GOAL1_L].theta
								< 0)
				{
					///cout<<"y2------------------------"<<endl;
					return true;
				}
				else
				{
					///cout<<"y2 false------------------"<<endl;
					return false;
				}

				/*
				 if(fabs(ball.y())<2*CELL_LENGTH)
				 {
				 if(messageParser.mVisionSenseMap[VO_GOAL1_L].distance<messageParser.mVisionSenseMap[VO_GOAL2_L].distance)
				 {
				 if(messageParser.mVisionSenseMap[VO_GOAL1_L].theta*messageParser.mVisionSenseMap[VO_GOAL2_L].theta<0&&(messageParser.mVisionSenseMap[VO_GOAL1_L].theta<-15))
				 {
				 ///cout<<"e-------------------"<<endl;
				 return true;
				 }
				 else
				 {
				 ///cout<<"false-------------4"<<endl;
				 return false;
				 }
				 }
				 else
				 {
				 if(messageParser.mVisionSenseMap[VO_GOAL1_L].theta*messageParser.mVisionSenseMap[VO_GOAL2_L].theta<0&&(messageParser.mVisionSenseMap[VO_GOAL2_L].theta>15))
				 {
				 ///cout<<"e222-------------------"<<endl;
				 return true;
				 }
				 else
				 {
				 ///cout<<"false2222-------------4"<<endl;
				 return false;
				 }

				 }
				 }
				 else if(fabs(ball.y())>=2*CELL_LENGTH)
				 {
				 if(messageParser.mVisionSenseMap[VO_GOAL1_L].theta*messageParser.mVisionSenseMap[VO_GOAL2_L].theta<0&&(messageParser.mVisionSenseMap[VO_GOAL1_L].theta<-15||messageParser.mVisionSenseMap[VO_GOAL2_L].theta>15))
				 {
				 ///cout<<"e3333-------------------"<<endl;
				 return true;
				 }
				 else
				 {
				 ///cout<<"false33333333-------------4"<<endl;
				 return false;
				 }
				 }*/
			}
			else if (messageParser.mVisionSenseMap[VO_GOAL1_L].phi != 0
					&& messageParser.mVisionSenseMap[VO_GOAL2_L].phi == 0)
			{
				if ((messageParser.mVisionSenseMap[VO_GOAL1_L].theta) < -15)
				{
					///cout<<"g-------------------"<<endl;
					return true;
				}
				else
				{
					///cout<<"false-------------5"<<endl;
					return false;
				}
			}
			else if (messageParser.mVisionSenseMap[VO_GOAL1_L].phi == 0
					&& messageParser.mVisionSenseMap[VO_GOAL2_L].phi != 0)
			{
				if ((messageParser.mVisionSenseMap[VO_GOAL2_L].theta) > 15)
				{
					///cout<<"g-------------------"<<endl;
					return true;
				}
				else
				{
					///cout<<"false-------------5"<<endl;
					return false;
				}
			}
		}
		else if (myCoordinate.x() > 7 * CELL_LENGTH)
		{
			if (messageParser.mVisionSenseMap[VO_GOAL1_L].phi != 0
					&& messageParser.mVisionSenseMap[VO_GOAL2_L].phi != 0)
			{
				if (messageParser.mVisionSenseMap[VO_GOAL1_L].theta
						* messageParser.mVisionSenseMap[VO_GOAL2_L].theta < 0)
				{
					///cout<<"i-------------------"<<endl;
					return true;
				}
				else
				{
					///cout<<"false-------------7"<<endl;
					return false;
				}
			}
			else if (messageParser.mVisionSenseMap[VO_GOAL1_L].phi == 0
					&& messageParser.mVisionSenseMap[VO_GOAL2_L].phi != 0)
			{
				if (messageParser.mVisionSenseMap[VO_GOAL2_L].theta > 15)
				{
					///cout<<"j-------------------"<<endl;
					return true;
				}
				else
				{
					///cout<<"false-------------8"<<endl;
					return false;
				}
			}
			else if (messageParser.mVisionSenseMap[VO_GOAL1_L].phi != 0
					&& messageParser.mVisionSenseMap[VO_GOAL2_L].phi == 0)
			{
				if (messageParser.mVisionSenseMap[VO_GOAL1_L].theta < -15)
				{
					///cout<<"j-------------------"<<endl;
					return true;
				}
				else
				{
					///cout<<"false-------------8"<<endl;
					return false;
				}
			}
		}
		///cout<<"false-------------10"<<endl;
		return false;

	}
	return false;
}

bool WorldModel::WhetherCanAttackOppGoal()
{

	float ballMeToXAxisAngle, ballGoalToXAxisAngle;//,bodyToX;
	ballMeToXAxisAngle = GetLastCyclesAverageBallMeToXAxisAngle();
	ballGoalToXAxisAngle = GetLastCyclesAverageBallGoalToXAxisAngle();
//	float bodyToX = GetLastCyclesAverageBodyToXAngle();
	/////cout<<"$$$$$$$$$$bodyToX=GetLastCyclesAverageBodyToXAngle():  "<<bodyToX<<endl;

///	Vector3 ballCoordinate=GetLastCyclesAverageBallCoordinate();
///	Vector3 myCoordinate=GetMyCoordinate();

	/////cout<<"$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ballMeToXAxisAngle:    "<<ballMeToXAxisAngle<<endl;
	/////cout<<"%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%ballGoalToXAxisAngle:    "<<ballGoalToXAxisAngle<<endl;
	/////cout<<"$$$$$$$$$$$$$$$$$$ballMeToXAxisAngle-ballGoalToXAxisAngle:   "<<ballMeToXAxisAngle-ballGoalToXAxisAngle<<endl;
	if (GetMyDistanceToBall() > 0.7)
	{
		if (fabs(ballMeToXAxisAngle - ballGoalToXAxisAngle) < 10)
		{
			if (GetMyTeamIndex() == TI_LEFT)
			{
				if (ballCoordinate.x() > myCoordinate.x())
				{
					/////cout<<"111111YESYESYESYESYESYESYESYESYESYESYESYESYESYESYES"<<endl;
					return true;
				}
			}
			else if (GetMyTeamIndex() == TI_RIGHT)
			{
				if (ballCoordinate.x() < myCoordinate.x())
				{
					/////cout<<"2222222YESYESYESYESYESYESYESYESYESYESYESYESYESYESYES"<<endl;
					return true;
				}
			}
		}
		else if (fabs(ballMeToXAxisAngle - ballGoalToXAxisAngle) > 10)
		{
			/////cout<<"NONONONONONNONONONONONONONONONONONONONONONONONON"<<endl;
			return false;
		}
	}
	else if (GetMyDistanceToBall() <= 0.7 && GetMyDistanceToBall() >= 0.3)
	{
		if (fabs(ballMeToXAxisAngle - ballGoalToXAxisAngle) < 45) /// && fabs( GetMyBodyAngleToBall() ) <20  )
		{
			///		/////cout<<"fabs(ballMeToXAxisAngle-ballGoalToXAxisAngle)<45:  "<<fabs(ballMeToXAxisAngle-ballGoalToXAxisAngle)<<endl;
			///		/////cout<<"fabs( GetMyBodyAngleToBall() ) <20:  "<<fabs( GetMyBodyAngleToBall() )<<endl;
			if (GetMyTeamIndex() == TI_LEFT)
			{
				if (ballCoordinate.x() > myCoordinate.x())
				{
					/////cout<<"3333333YESYESYESYESYESYESYESYESYESYESYESYESYESYESYES"<<endl;
					return true;
				}
			}
			else if (GetMyTeamIndex() == TI_RIGHT)
			{
				if (ballCoordinate.x() < myCoordinate.x())
				{
					/////cout<<"444444YESYESYESYESYESYESYESYESYESYESYESYESYESYESYES"<<endl;
					return true;
				}
			}
		}
	}
	else if (GetMyDistanceToBall() < 0.3)
	{
		if (fabs(ballMeToXAxisAngle - ballGoalToXAxisAngle) < 70) ///&& fabs( GetMyBodyAngleToBall() )<30 )
		{
			///		/////cout<<"fabs(ballMeToXAxisAngle-ballGoalToXAxisAngle)<60:  "<<fabs(ballMeToXAxisAngle-ballGoalToXAxisAngle)<<endl;
			///		/////cout<<"fabs( GetMyBodyAngleToBall() ) <30:  "<<fabs( GetMyBodyAngleToBall() )<<endl;
			if (GetMyTeamIndex() == TI_LEFT)
			{
				if (ballCoordinate.x() > myCoordinate.x())
				{
					/////cout<<"5555555YESYESYESYESYESYESYESYESYESYESYESYESYESYESYES"<<endl;
					return true;
				}
			}
			else if (GetMyTeamIndex() == TI_RIGHT)
			{
				if (ballCoordinate.x() < myCoordinate.x())
				{
					/////cout<<"666666YESYESYESYESYESYESYESYESYESYESYESYESYESYESYES"<<endl;
					return true;
				}
			}
		}
	}
	/////cout<<"77777777777777NONONONONONONONONOOONONONONONONONONONONONON"<<endl;
	return false;

}

void WorldModel::updateLastCyclesAverageBallMeToXAxisAngle()
{
	static int point = 0;
	if (CanSeeTheBall() == true)
	{
		///	Vector3 ballCoordinate=GetLastCyclesAverageBallCoordinate();
		///	Vector3 myCoordinate=GetMyCoordinate();

		float ballMeToXAxisAngle;
		if (ballCoordinate.x() > myCoordinate.x())
		{
			ballMeToXAxisAngle = atan(
					(ballCoordinate.y()
							- myCoordinate.y()
									/ (ballCoordinate.x() - myCoordinate.x()) ))
					* 180 / 3.14;
			/////cout<<"11111111111111111111111111111111ballMeToXAxisAngle: "<<ballMeToXAxisAngle<<endl;
		}
		else if (ballCoordinate.x() <= myCoordinate.x())
		{
			if (ballCoordinate.y() > myCoordinate.y())
			{
				ballMeToXAxisAngle = 180
						- atan(
								(ballCoordinate.y()
										- myCoordinate.y()
												/ (ballCoordinate.x()
														- myCoordinate.x()) ))
								* 180 / 3.14;
				/////cout<<"22222222222222222222222ballMeToXAxisAngle:  "<<ballMeToXAxisAngle<<endl;
			}
			else if (ballCoordinate.y() <= myCoordinate.y())
			{
				ballMeToXAxisAngle = -180
						- atan(
								(ballCoordinate.y()
										- myCoordinate.y()
												/ (ballCoordinate.x()
														- myCoordinate.x()) ))
								* 180 / 3.14;
				/////cout<<"333333333333333333333333ballMeToXAxisAngle:   "<<ballMeToXAxisAngle<<endl;
			}

		}

		lastCyclesAverageBallMeToXAxisAngleArray[point
				% LAST_CYCLES_OF_BALL_ME_TO_XAXIS_ANGLE] = ballMeToXAxisAngle;
	}
	else if (CanSeeTheBall() == false)
	{
		lastCyclesAverageBallMeToXAxisAngleArray[point
				% LAST_CYCLES_OF_BALL_ME_TO_XAXIS_ANGLE] =
				GetLastCyclesAverageBallMeToXAxisAngle();
	}

	point++;

	float totalAngle = 0;

	for (int i = 0; i < LAST_CYCLES_OF_BALL_ME_TO_XAXIS_ANGLE; i++)
	{
		totalAngle += lastCyclesAverageBallMeToXAxisAngleArray[i];
	}

	lastCyclesAverageBallMeToXAxisAngle = totalAngle
			/ LAST_CYCLES_OF_BALL_ME_TO_XAXIS_ANGLE;
}

float WorldModel::GetLastCyclesAverageBallMeToXAxisAngle()
{
	return lastCyclesAverageBallMeToXAxisAngle;
}

void WorldModel::updateLastCyclesAverageBallGoalToXAxisAngle()
{
	static int point = 0;
	if (CanSeeTheBall() == true)
	{
		///	Vector3 ballCoordinate=GetLastCyclesAverageBallCoordinate();
		//	Vector3 myCoordinate=GetMyCoordinate();

		float ballGoalToXAxisAngle;

		if (GetMyTeamIndex() == TI_LEFT)
		{
			ballGoalToXAxisAngle = atan(
					(ballCoordinate.y()
							/ (ballCoordinate.x() - FieldLength / 2) )) * 180
					/ 3.14;
		}
		else if (GetMyTeamIndex() == TI_RIGHT)
		{
			ballGoalToXAxisAngle = atan(
					(ballCoordinate.y()
							/ (ballCoordinate.x() - FieldLength / 2) )) * 180
					/ 3.14;
			///	ballGoalToXAxisAngle=atan(   (ballCoordinate.y()/(ballCoordinate.x()-(-FieldLength/2)  )  )     )*180/3.14;
		}

		lastCyclesAverageBallGoalToXAxisAngleArray[point
				% LAST_CYCLES_OF_BALL_GOAL_TO_XAXIS_ANGLE] =
				ballGoalToXAxisAngle;
	}
	else if (CanSeeTheBall() == false)
	{
		lastCyclesAverageBallGoalToXAxisAngleArray[point
				% LAST_CYCLES_OF_BALL_GOAL_TO_XAXIS_ANGLE] =
				GetLastCyclesAverageBallGoalToXAxisAngle();
	}

	point++;

	float totalAngle = 0;

	for (int i = 0; i < LAST_CYCLES_OF_BALL_GOAL_TO_XAXIS_ANGLE; i++)
	{
		totalAngle += lastCyclesAverageBallGoalToXAxisAngleArray[i];
	}

	lastCyclesAverageBallGoalToXAxisAngle = totalAngle
			/ LAST_CYCLES_OF_BALL_GOAL_TO_XAXIS_ANGLE;
}

float WorldModel::GetLastCyclesAverageBallGoalToXAxisAngle()
{
	return lastCyclesAverageBallGoalToXAxisAngle;
}

float WorldModel::ConvertRadianIntoAngle(float angle)
{
	return angle * 180 / PI;
}

float WorldModel::GetBodyToX()
{
	return gyroz;
///	return BodyToX;
}

void WorldModel::updateLastCyclesAverageBodyToXAngle()
{
	static int point = 0;

	lastCyclesAverageBodyToXAngleArray[point % LAST_CYCLES_OF_BODY_TO_X] =
			GetMyBodyAngleToXAxis();

	point++;

	float totalAngle = 0;

	for (int i = 0; i < LAST_CYCLES_OF_BODY_TO_X; i++)
	{
		totalAngle += lastCyclesAverageBodyToXAngleArray[i];
	}

	lastCyclesAverageBodyToXAngle = totalAngle / LAST_CYCLES_OF_BODY_TO_X;
}

float WorldModel::GetLastCyclesAverageBodyToXAngle()
{
	return lastCyclesAverageBodyToXAngle;
}

float WorldModel::GetMyDistanceToDestination(Vector3& destinationCoordinate)
{
///	Vector3 myCoordinate=GetMyCoordinate();
	return sqrt(
			(destinationCoordinate.x() - myCoordinate.x())
					* (destinationCoordinate.x() - myCoordinate.x())
					+ (destinationCoordinate.y() - myCoordinate.y())
							* (destinationCoordinate.y() - myCoordinate.y()));
}

float WorldModel::GetMyAngleToDestination(Vector3& destination)
{
///	Vector3 myCoordinate=GetMyCoordinate();
	float angle = atan(
			(destination.y() - myCoordinate.y())
					/ (destination.x() - myCoordinate.x())) / PI * 180;
	if (myCoordinate.x() > destination.x()
			&& myCoordinate.y() > destination.y())
	{
		angle = angle - 180;
	}
	else if (myCoordinate.x() > destination.x()
			&& myCoordinate.y() < destination.y())
	{
		angle = angle + 180;
	}

	/////cout<<"AAAAAAAAAAAAAAAAAAAAAAAAangle:"<<angle<<endl;
	float angleToX = GetBodyToX();
	/////cout<<"BBBBBBBBBBBBBBBBBBBBBBBangleToX:"<<angleToX<<endl;
	angle = angle - angleToX;
	if (angle > 180)
	{
		angle -= 180;
	}
	else if (angle < -180)
	{
		angle += 180;
	}
	return (angle);
}

void WorldModel::UpdateViceVanguard_1() ///useless
{
//	if(!messageParser.ParsevanguardNum())
//	return;
//	vanguardNum=vannumber;
//	vanguardNum=messageParser.GetVanguardNumber();
//	/////cout<<"vanguardNum           "<<vanguardNum<<endl;
	ViceVanguard_1FallDown = messageParser.ViceVanguard_1FallDown;
	//vanguradLoseBall=messageParser.vanguradLoseBall;
}

bool WorldModel::IsViceVanguard_1FallDown() //useless
{
	return ViceVanguard_1FallDown;
}
#if 0
bool WorldModel::WhetherCanShoot()
{

	//return true;
///	Vector3 myCoordinate=GetMyCoordinate();
	if(IsTheBallOutOfShootArea())
	{
		///cout<<"IsTheBallOutOfShootArea()"<<endl;
		return false;
	}
	if((myCoordinate.x()>7.2&&fabs(myCoordinate.y())<3.5)||GetMyDistanceToBall()>0.9)
	{
		return false;
	}
	else
	{
		if( GetMyTeamIndex()==TI_LEFT )
		{
			if(fabs(GetMyBodyAngleToBall())<45&&messageParser.mVisionSenseMap[VO_GOAL1_R].phi!=0&&messageParser.mVisionSenseMap[VO_GOAL2_R].phi!=0)
			{
				float dis1=messageParser.mVisionSenseMap[VO_GOAL1_R].distance;
				float dis2=messageParser.mVisionSenseMap[VO_GOAL2_R].distance;
				/////cout<<"			dis 1 ="<<dis1<<"		dis 2 ="<<dis2<<endl;
				if(dis1>dis2)
				{

					if(dis2<1.8)
					return false;

					if(dis2<5.4)
					{
						/////cout<<"11111111111"<<endl;
						return true;
					}
					else
					return false;
				}
				else
				{
					if(dis1<1.8)
					return false;

					if(dis1<5.4)
					{
						/////cout<<"222222222"<<endl;
						return true;
					}
					else
					return false;
				}
			}
			else if(messageParser.mVisionSenseMap[VO_GOAL1_R].phi!=0)
			{
				if(messageParser.mVisionSenseMap[VO_GOAL1_R].distance<5.4&&messageParser.mVisionSenseMap[VO_GOAL1_R].distance>1.8)
				{
					/////cout<<"		dis 1 ="<<messageParser.mVisionSenseMap[VO_GOAL1_R].distance<<endl;
					return true;
				}
				else
				return false;
			}
			else if(messageParser.mVisionSenseMap[VO_GOAL2_R].phi!=0)
			{
				if(messageParser.mVisionSenseMap[VO_GOAL2_R].distance<5.4&&messageParser.mVisionSenseMap[VO_GOAL2_R].distance>1.8)
				{
					///cout<<"		dis 2 ="<<messageParser.mVisionSenseMap[VO_GOAL2_R].distance<<endl;
					return true;
				}
				else
				return false;
			}
			else
			return false;
		}
		else
		{
			if(fabs(GetMyBodyAngleToBall())<45&&messageParser.mVisionSenseMap[VO_GOAL1_L].phi!=0&&messageParser.mVisionSenseMap[VO_GOAL2_L].phi!=0)
			{
				float dis1=messageParser.mVisionSenseMap[VO_GOAL1_L].distance;
				float dis2=messageParser.mVisionSenseMap[VO_GOAL2_L].distance;
				if(dis1>dis2)
				{

					if(dis2<1.8)
					return false;

					if(dis2<5.4)
					{
						/////cout<<"11111111111"<<endl;
						return true;
					}
					else
					return false;
				}
				else
				{
					if(dis1<1.8)
					return false;

					if(dis1<5.4)
					{
						/////cout<<"222222222"<<endl;
						return true;
					}
					else
					return false;
				}
			}
			else if(messageParser.mVisionSenseMap[VO_GOAL1_L].phi!=0)
			{
				if(messageParser.mVisionSenseMap[VO_GOAL1_L].distance<5.5&&messageParser.mVisionSenseMap[VO_GOAL1_L].distance>1.8)
				return true;
				else
				return false;
			}
			else if(messageParser.mVisionSenseMap[VO_GOAL2_L].phi!=0)
			{
				if(messageParser.mVisionSenseMap[VO_GOAL2_L].distance<5.5&&messageParser.mVisionSenseMap[VO_GOAL2_L].distance>1.8)
				return true;
				else
				return false;
			}
			else
			return false;
		}

	}

}

bool WorldModel::CentreForwardWeatherCanShoot()
{
	if(!CanSeeTheBall())
	{
		///cout<<"can not see the ball"<<endl;
		return false;
	}
	if(GetMyDistanceToBall()<0.135)
	{
		///cout<<"GetMyDistanceToBall()<0.135"<<endl;
		return false;
	}
	if(GetMyDistanceToBall()<0.2&&fabs(GetMyBodyAngleToBall())>35)
	{
		///cout<<"GetMyDistanceToBall()<0.2&&fabs(GetMyBodyAngleToBall())>35"<<endl;
		return false;
	}
	Vector3 my=GetMyCoordinate();
	float angleToX=GetBodyToX();
	///cout<<"CentreForwardWeatherCanShoot()_GetMyCoordinate():"<<GetMyCoordinate()<<endl;
	///cout<<"CentreForwardWeatherCanShoot()_GetBodyToX():"<<GetBodyToX()<<endl;
	if(fabs(my.y())<3&&fabs(angleToX)<90)
	{
		return true;
	}
	else
	{
		return false;
	}
}
#endif

bool WorldModel::MyDistanceToBallSmallerThanMyDistanceToAnyTeammate()
{
	bool result = true;
	for (TPlayerSenseMap::iterator iter =
			messageParser.mTeamMateSenseMap.begin();
			iter != messageParser.mTeamMateSenseMap.end(); ++iter)
			{
		if (myDistanceToBall > (*iter).second.head.distance
				&& (*iter).second.unum != GetMyNumber())
		{
			result = false;
		}
	}
	if (CITHear.GetnowSayNumber() != GetMyNumber())
	{
//		cout << "changed for backlinker" << endl;
		result = false;
	}
	return result;
}

bool WorldModel::GetCentreForwardToBallDistance(float& dis)
{
	bool res = false;
///	Vector3 myCoordinate=GetMyCoordinate();
	if (myCoordinate.x() > 0)
	{
		return res;
	}

	if (GetMyNumber() == 5 || GetMyNumber() == 6 || GetMyNumber() == 7)
	{
		dis = GetMyDistanceToBall();
		res = true;
		return res;
	}

	float mDisToCentreForward, mAngleToCentreForward;
	for (TPlayerSenseMap::iterator iter =
			messageParser.mTeamMateSenseMap.begin();
			iter != messageParser.mTeamMateSenseMap.end(); ++iter)
			{
		if (5 == (*iter).second.unum || 6 == (*iter).second.unum
				|| 7 == (*iter).second.unum)
		{
			mDisToCentreForward = (*iter).second.head.distance;
			mAngleToCentreForward = (*iter).second.head.theta;
			res = true;
			break;
		}
	}

	float myAngleToBall = GetMyAngleToBall(), myDistanceToBall =
			GetMyDistanceToBall();
	float angle;
	if ((myAngleToBall * mAngleToCentreForward) < 0)
	{
		angle = fabs(myAngleToBall) + fabs(mAngleToCentreForward);
	}
	else
	{
		angle = fabs(myAngleToBall - mAngleToCentreForward);
	}
	dis = sqrt(
			myDistanceToBall * myDistanceToBall
					+ mDisToCentreForward * mDisToCentreForward
					- cos(angle * PI / 180) * 2 * myDistanceToBall
							* mDisToCentreForward);

	return res;
}

bool WorldModel::GetLineBackerToBallDistance(float& dis)
{
	bool res = false;
///	Vector3 myCoordinate=GetMyCoordinate();

	if (myCoordinate.x() > 0)
	{
		return res;
	}

	if (GetMyNumber() == 8 || GetMyNumber() == 9) //myself is goalie!!!
	{
		dis = GetMyDistanceToBall();
		res = true;
		return res;
	}

	float mDisToLineBacker, mAngleToLineBacker;
	for (TPlayerSenseMap::iterator iter =
			messageParser.mTeamMateSenseMap.begin();
			iter != messageParser.mTeamMateSenseMap.end(); ++iter)
			{
		if (8 == (*iter).second.unum || 9 == (*iter).second.unum) //goalie's team number is 1
		{
			mDisToLineBacker = (*iter).second.head.distance;
			mAngleToLineBacker = (*iter).second.head.theta;
			res = true;
			break;
		}
	}

	float myAngleToBall = GetMyAngleToBall(), myDistanceToBall =
			GetMyDistanceToBall();
	float angle;
	if ((myAngleToBall * mAngleToLineBacker) < 0)
	{
		angle = fabs(myAngleToBall) + fabs(mAngleToLineBacker);
	}
	else
	{
		angle = fabs(myAngleToBall - mAngleToLineBacker);
	}
	dis = sqrt(
			myDistanceToBall * myDistanceToBall
					+ mDisToLineBacker * mDisToLineBacker
					- cos(angle * PI / 180) * 2 * myDistanceToBall
							* mDisToLineBacker);

	return res;
}
bool WorldModel::whetherTeamatMyDes(Vector3 Des)
{
	bool result = false;
	for (TPlayerSenseMap::iterator iter =
				messageParser.mTeamMateSenseMap.begin();
				iter != messageParser.mTeamMateSenseMap.end(); ++iter)
				{
				if ((*iter).second.unum != GetMyNumber())
				{
					    Vector3 Teamcoo=this->GetNewTeammateCoordinate((*iter).second.unum);
						if((Des-Teamcoo).xymod()<0.5*CELL_LENGTH)
						{
							result=true;
						}
				}
				}
	return result;
}
bool WorldModel::WhetherMyTeammatesBlockMe()
{
	bool result = false;

	float mDisToMostCloseTeammate = 10;
	float mAngleToMostCloseTeammate = 60;
	for (TPlayerSenseMap::iterator iter =
			messageParser.mTeamMateSenseMap.begin();
			iter != messageParser.mTeamMateSenseMap.end(); ++iter)
			{
		if ((*iter).second.unum != GetMyNumber())
		{
			/////cout<<"(*iter).second.unum:"<<(*iter).second.unum<<endl;
			/////cout<<"(*iter).second.head.distance:"<<(*iter).second.head.distance<<endl;
			/////cout<<"(*iter).second.rLowerArm.distance:"<<(*iter).second.rLowerArm.distance<<endl;
			/////cout<<"(*iter).second.lLowerArm.distance:"<<(*iter).second.lLowerArm.distance<<endl;
			/////cout<<"(*iter).second.rFoot.distance:"<<(*iter).second.rFoot.distance<<endl;
			/////cout<<"(*iter).second.lFoot.distance:"<<(*iter).second.lFoot.distance<<endl<<endl;
			/////cout<<"fabs((*iter).second.head.theta):"<<fabs((*iter).second.head.theta)<<endl;
			/////cout<<"fabs((*iter).second.rLowerArm.theta):"<<fabs((*iter).second.rLowerArm.theta)<<endl;
			/////cout<<"fabs((*iter).second.lLowerArm.theta):"<<fabs((*iter).second.lLowerArm.theta)<<endl;
			/////cout<<"fabs((*iter).second.rFoot.theta):"<<fabs((*iter).second.rFoot.theta)<<endl;
			/////cout<<"fabs((*iter).second.lFoot.theta):"<<fabs((*iter).second.lFoot.theta)<<endl;

			/////cout<<"((*iter).second.head.phi):"<<((*iter).second.head.phi)<<endl;
			/////cout<<"(*iter).second.rFoot.phi:"<<(*iter).second.rFoot.phi<<endl;
			/////cout<<"(*iter).second.lFoot.phi:"<<(*iter).second.lFoot.phi<<endl<<endl;

			/////cout<<"GetCurrentJointAngle(JID_HEAD_2):"<<GetCurrentJointAngle(JID_HEAD_2)<<endl;
			/////cout<<"GetLastCyclesAverageVerticalTurnHeadAngle:"<<GetLastCyclesAverageVerticalTurnHeadAngle()<<endl;

			/////cout<<"fabs((*iter).second.head.phi+GetLastCyclesAverageVerticalTurnHeadAngle):"<<fabs(((*iter).second.head.phi)+GetLastCyclesAverageVerticalTurnHeadAngle())<<endl;
			/////cout<<"fabs((*iter).second.rFoot.phi+GetLastCyclesAverageVerticalTurnHeadAngle):"<<fabs((*iter).second.rFoot.phi+GetLastCyclesAverageVerticalTurnHeadAngle())<<endl;
			/////cout<<"fabs((*iter).second.rFoot.phi+GetLastCyclesAverageVerticalTurnHeadAngle):"<<fabs((*iter).second.rFoot.phi+GetLastCyclesAverageVerticalTurnHeadAngle())<<endl;
			/////cout<<"fabs((*iter).second.head.phi-(*iter).second.rFoot.phi):"<<fabs((*iter).second.head.phi-(*iter).second.rFoot.phi)<<endl;
			if ((*iter).second.head.distance < mDisToMostCloseTeammate
					&& (*iter).second.head.distance != 0)
			{
				mDisToMostCloseTeammate = (*iter).second.head.distance;
			}
			if ((*iter).second.rLowerArm.distance < mDisToMostCloseTeammate
					&& (*iter).second.rLowerArm.distance != 0)
			{
				mDisToMostCloseTeammate = (*iter).second.rLowerArm.distance;
			}
			if ((*iter).second.lLowerArm.distance < mDisToMostCloseTeammate
					&& (*iter).second.lLowerArm.distance != 0)
			{
				mDisToMostCloseTeammate = (*iter).second.lLowerArm.distance;
			}
			if ((*iter).second.rFoot.distance < mDisToMostCloseTeammate
					&& (*iter).second.rFoot.distance != 0)
			{
				mDisToMostCloseTeammate = (*iter).second.rFoot.distance;
			}
			if ((*iter).second.lFoot.distance < mDisToMostCloseTeammate
					&& (*iter).second.lFoot.distance != 0)
			{
				mDisToMostCloseTeammate = (*iter).second.lFoot.distance;
			}

			if (fabs((*iter).second.head.theta) < mAngleToMostCloseTeammate
					&& fabs((*iter).second.head.theta) != 0)
			{
				mAngleToMostCloseTeammate = fabs((*iter).second.head.theta);
			}
			if (fabs((*iter).second.rLowerArm.theta) < mAngleToMostCloseTeammate
					&& fabs((*iter).second.rLowerArm.theta) != 0)
			{
				mAngleToMostCloseTeammate = fabs(
						(*iter).second.rLowerArm.theta);
			}
			if (fabs((*iter).second.lLowerArm.theta) < mAngleToMostCloseTeammate
					&& fabs((*iter).second.lLowerArm.theta) != 0)
			{
				mAngleToMostCloseTeammate = fabs(
						(*iter).second.lLowerArm.theta);
			}
			if (fabs((*iter).second.rFoot.theta) < mAngleToMostCloseTeammate
					&& fabs((*iter).second.rFoot.theta) != 0)
			{
				mAngleToMostCloseTeammate = fabs((*iter).second.rFoot.theta);
			}
			if (fabs((*iter).second.lFoot.theta) < mAngleToMostCloseTeammate
					&& fabs((*iter).second.lFoot.theta) != 0)
			{
				mAngleToMostCloseTeammate = fabs((*iter).second.lFoot.theta);
			}

			if (mDisToMostCloseTeammate < 0.8 && mAngleToMostCloseTeammate < 25)
			{
				result = true;
				break;
			}
			/////cout<<"mDisToMostCloseTeammate:"<<mDisToMostCloseTeammate<<endl;
			/////cout<<"mAngleToMostCloseTeammate:"<<mAngleToMostCloseTeammate<<endl;
			mDisToMostCloseTeammate = 10;
			mAngleToMostCloseTeammate = 60;
		}
	}

	return result;

}

bool WorldModel::WhetherMyTeammatesBlockMe(int& teammateNumber)
{
	bool result = false;

	float mDisToMostCloseTeammate = 10;
	float mAngleToMostCloseTeammate = 60;
	for (TPlayerSenseMap::iterator iter =
			messageParser.mTeamMateSenseMap.begin();
			iter != messageParser.mTeamMateSenseMap.end(); ++iter)
			{
		if ((*iter).second.unum != GetMyNumber())
		{
			/////cout<<"(*iter).second.unum:"<<(*iter).second.unum<<endl;
			/////cout<<"(*iter).second.head.distance:"<<(*iter).second.head.distance<<endl;
			/////cout<<"(*iter).second.rLowerArm.distance:"<<(*iter).second.rLowerArm.distance<<endl;
			/////cout<<"(*iter).second.lLowerArm.distance:"<<(*iter).second.lLowerArm.distance<<endl;
			/////cout<<"(*iter).second.rFoot.distance:"<<(*iter).second.rFoot.distance<<endl;
			/////cout<<"(*iter).second.lFoot.distance:"<<(*iter).second.lFoot.distance<<endl<<endl;
			/////cout<<"fabs((*iter).second.head.theta):"<<fabs((*iter).second.head.theta)<<endl;
			/////cout<<"fabs((*iter).second.rLowerArm.theta):"<<fabs((*iter).second.rLowerArm.theta)<<endl;
			/////cout<<"fabs((*iter).second.lLowerArm.theta):"<<fabs((*iter).second.lLowerArm.theta)<<endl;
			/////cout<<"fabs((*iter).second.rFoot.theta):"<<fabs((*iter).second.rFoot.theta)<<endl;
			/////cout<<"fabs((*iter).second.lFoot.theta):"<<fabs((*iter).second.lFoot.theta)<<endl;

			/////cout<<"((*iter).second.head.phi):"<<((*iter).second.head.phi)<<endl;
			/////cout<<"(*iter).second.rFoot.phi:"<<(*iter).second.rFoot.phi<<endl;
			/////cout<<"(*iter).second.lFoot.phi:"<<(*iter).second.lFoot.phi<<endl<<endl;

			/////cout<<"GetCurrentJointAngle(JID_HEAD_2):"<<GetCurrentJointAngle(JID_HEAD_2)<<endl;
			/////cout<<"GetLastCyclesAverageVerticalTurnHeadAngle:"<<GetLastCyclesAverageVerticalTurnHeadAngle()<<endl;

			/////cout<<"fabs((*iter).second.head.phi+GetLastCyclesAverageVerticalTurnHeadAngle):"<<fabs(((*iter).second.head.phi)+GetLastCyclesAverageVerticalTurnHeadAngle())<<endl;
			/////cout<<"fabs((*iter).second.rFoot.phi+GetLastCyclesAverageVerticalTurnHeadAngle):"<<fabs((*iter).second.rFoot.phi+GetLastCyclesAverageVerticalTurnHeadAngle())<<endl;
			/////cout<<"fabs((*iter).second.rFoot.phi+GetLastCyclesAverageVerticalTurnHeadAngle):"<<fabs((*iter).second.rFoot.phi+GetLastCyclesAverageVerticalTurnHeadAngle())<<endl;
			/////cout<<"fabs((*iter).second.head.phi-(*iter).second.rFoot.phi):"<<fabs((*iter).second.head.phi-(*iter).second.rFoot.phi)<<endl;
			if ((*iter).second.head.distance < mDisToMostCloseTeammate
					&& (*iter).second.head.distance != 0)
			{
				mDisToMostCloseTeammate = (*iter).second.head.distance;
			}
			if ((*iter).second.rLowerArm.distance < mDisToMostCloseTeammate
					&& (*iter).second.rLowerArm.distance != 0)
			{
				mDisToMostCloseTeammate = (*iter).second.rLowerArm.distance;
			}
			if ((*iter).second.lLowerArm.distance < mDisToMostCloseTeammate
					&& (*iter).second.lLowerArm.distance != 0)
			{
				mDisToMostCloseTeammate = (*iter).second.lLowerArm.distance;
			}
			if ((*iter).second.rFoot.distance < mDisToMostCloseTeammate
					&& (*iter).second.rFoot.distance != 0)
			{
				mDisToMostCloseTeammate = (*iter).second.rFoot.distance;
			}
			if ((*iter).second.lFoot.distance < mDisToMostCloseTeammate
					&& (*iter).second.lFoot.distance != 0)
			{
				mDisToMostCloseTeammate = (*iter).second.lFoot.distance;
			}

			if (fabs((*iter).second.head.theta) < mAngleToMostCloseTeammate
					&& fabs((*iter).second.head.theta) != 0)
			{
				mAngleToMostCloseTeammate = fabs((*iter).second.head.theta);
			}
			if (fabs((*iter).second.rLowerArm.theta) < mAngleToMostCloseTeammate
					&& fabs((*iter).second.rLowerArm.theta) != 0)
			{
				mAngleToMostCloseTeammate = fabs(
						(*iter).second.rLowerArm.theta);
			}
			if (fabs((*iter).second.lLowerArm.theta) < mAngleToMostCloseTeammate
					&& fabs((*iter).second.lLowerArm.theta) != 0)
			{
				mAngleToMostCloseTeammate = fabs(
						(*iter).second.lLowerArm.theta);
			}
			if (fabs((*iter).second.rFoot.theta) < mAngleToMostCloseTeammate
					&& fabs((*iter).second.rFoot.theta) != 0)
			{
				mAngleToMostCloseTeammate = fabs((*iter).second.rFoot.theta);
			}
			if (fabs((*iter).second.lFoot.theta) < mAngleToMostCloseTeammate
					&& fabs((*iter).second.lFoot.theta) != 0)
			{
				mAngleToMostCloseTeammate = fabs((*iter).second.lFoot.theta);
			}

			if (mDisToMostCloseTeammate < 0.5 * CELL_LENGTH
					&& mAngleToMostCloseTeammate < 25)
			{
				result = true;
				teammateNumber = (*iter).second.unum;
				break;
			}
			/////cout<<"mDisToMostCloseTeammate:"<<mDisToMostCloseTeammate<<endl;
			/////cout<<"mAngleToMostCloseTeammate:"<<mAngleToMostCloseTeammate<<endl;
			mDisToMostCloseTeammate = 10;
			mAngleToMostCloseTeammate = 60;
		}
	}

	return result;

}

bool WorldModel::WhetherOpponentBlockMe(int& OpponentNumber)
{
	bool result = false;

	float mDisToMostCloseOpponent = 10;
	float mAngleToMostCloseOpponent = 60;
	for (TPlayerSenseMap::iterator iter =
			messageParser.mOpponentSenseMap.begin();
			iter != messageParser.mOpponentSenseMap.end(); ++iter)
			{

		//cout<<"(*iter).second.unum:"<<(*iter).second.unum<<endl;
		//cout<<"(*iter).second.head.distance:"<<(*iter).second.head.distance<<endl;
		//cout<<"(*iter).second.rLowerArm.distance:"<<(*iter).second.rLowerArm.distance<<endl;
		//cout<<"(*iter).second.lLowerArm.distance:"<<(*iter).second.lLowerArm.distance<<endl;
		//cout<<"(*iter).second.rFoot.distance:"<<(*iter).second.rFoot.distance<<endl;
		//cout<<"(*iter).second.lFoot.distance:"<<(*iter).second.lFoot.distance<<endl<<endl;
		//cout<<"fabs((*iter).second.head.theta):"<<fabs((*iter).second.head.theta)<<endl;
		//cout<<"fabs((*iter).second.rLowerArm.theta):"<<fabs((*iter).second.rLowerArm.theta)<<endl;
		//cout<<"fabs((*iter).second.lLowerArm.theta):"<<fabs((*iter).second.lLowerArm.theta)<<endl;
		//cout<<"fabs((*iter).second.rFoot.theta):"<<fabs((*iter).second.rFoot.theta)<<endl;
		//cout<<"fabs((*iter).second.lFoot.theta):"<<fabs((*iter).second.lFoot.theta)<<endl;

		//cout<<"((*iter).second.head.phi):"<<((*iter).second.head.phi)<<endl;
		//cout<<"(*iter).second.rFoot.phi:"<<(*iter).second.rFoot.phi<<endl;
		//cout<<"(*iter).second.lFoot.phi:"<<(*iter).second.lFoot.phi<<endl<<endl;

		//cout<<"GetCurrentJointAngle(JID_HEAD_2):"<<GetCurrentJointAngle(JID_HEAD_2)<<endl;
		//cout<<"GetLastCyclesAverageVerticalTurnHeadAngle:"<<GetLastCyclesAverageVerticalTurnHeadAngle()<<endl;
		//cout<<"fabs((*iter).second.head.phi+GetLastCyclesAverageVerticalTurnHeadAngle):"<<fabs(((*iter).second.head.phi)+GetLastCyclesAverageVerticalTurnHeadAngle())<<endl;
		//cout<<"fabs((*iter).second.rFoot.phi+GetLastCyclesAverageVerticalTurnHeadAngle):"<<fabs((*iter).second.rFoot.phi+GetLastCyclesAverageVerticalTurnHeadAngle())<<endl;
		//cout<<"fabs((*iter).second.rFoot.phi+GetLastCyclesAverageVerticalTurnHeadAngle):"<<fabs((*iter).second.rFoot.phi+GetLastCyclesAverageVerticalTurnHeadAngle())<<endl;
		//cout<<"fabs((*iter).second.head.phi-(*iter).second.rFoot.phi):"<<fabs((*iter).second.head.phi-(*iter).second.rFoot.phi)<<endl;

		if ((*iter).second.head.distance < mDisToMostCloseOpponent
				&& (*iter).second.head.distance != 0)
		{
			mDisToMostCloseOpponent = (*iter).second.head.distance;
		}
		if ((*iter).second.rLowerArm.distance < mDisToMostCloseOpponent
				&& (*iter).second.rLowerArm.distance != 0)
		{
			mDisToMostCloseOpponent = (*iter).second.rLowerArm.distance;
		}
		if ((*iter).second.lLowerArm.distance < mDisToMostCloseOpponent
				&& (*iter).second.lLowerArm.distance != 0)
		{
			mDisToMostCloseOpponent = (*iter).second.lLowerArm.distance;
		}
		if ((*iter).second.rFoot.distance < mDisToMostCloseOpponent
				&& (*iter).second.rFoot.distance != 0)
		{
			mDisToMostCloseOpponent = (*iter).second.rFoot.distance;
		}
		if ((*iter).second.lFoot.distance < mDisToMostCloseOpponent
				&& (*iter).second.lFoot.distance != 0)
		{
			mDisToMostCloseOpponent = (*iter).second.lFoot.distance;
		}

		if (fabs((*iter).second.head.theta) < mAngleToMostCloseOpponent
				&& fabs((*iter).second.head.theta) != 0)
		{
			mAngleToMostCloseOpponent = fabs((*iter).second.head.theta);
		}
		if (fabs((*iter).second.rLowerArm.theta) < mAngleToMostCloseOpponent
				&& fabs((*iter).second.rLowerArm.theta) != 0)
		{
			mAngleToMostCloseOpponent = fabs((*iter).second.rLowerArm.theta);
		}
		if (fabs((*iter).second.lLowerArm.theta) < mAngleToMostCloseOpponent
				&& fabs((*iter).second.lLowerArm.theta) != 0)
		{
			mAngleToMostCloseOpponent = fabs((*iter).second.lLowerArm.theta);
		}
		if (fabs((*iter).second.rFoot.theta) < mAngleToMostCloseOpponent
				&& fabs((*iter).second.rFoot.theta) != 0)
		{
			mAngleToMostCloseOpponent = fabs((*iter).second.rFoot.theta);
		}
		if (fabs((*iter).second.lFoot.theta) < mAngleToMostCloseOpponent
				&& fabs((*iter).second.lFoot.theta) != 0)
		{
			mAngleToMostCloseOpponent = fabs((*iter).second.lFoot.theta);
		}
		if (mDisToMostCloseOpponent < 1.25 * CELL_LENGTH
				&& mAngleToMostCloseOpponent < 25) ///changed by gaojin
		{
			result = true;
			OpponentNumber = (*iter).second.unum;
			break;
		}
		/////cout<<"mDisToMostCloseTeammate:"<<mDisToMostCloseTeammate<<endl;
		/////cout<<"mAngleToMostCloseTeammate:"<<mAngleToMostCloseTeammate<<endl;
		mDisToMostCloseOpponent = 10;
		mAngleToMostCloseOpponent = 60;

	}
	return result;

}

float WorldModel::WhetherOpponentInMyWayToDestination(
		Vector3 opponentCoordinate, Vector3 myCoordinate, Vector3 destination)
{
	float myToOpponent = sqrt(
			(myCoordinate.x() - opponentCoordinate.x())
					* (myCoordinate.x() - opponentCoordinate.x())
					+ (myCoordinate.y() - opponentCoordinate.y())
							* (myCoordinate.y() - opponentCoordinate.y()));
	float myToDestination = sqrt(
			(myCoordinate.x() - destination.x())
					* (myCoordinate.x() - destination.x())
					+ (myCoordinate.y() - destination.y())
							* (myCoordinate.y() - destination.y()));
	float OpponentToDestination = sqrt(
			(destination.x() - opponentCoordinate.x())
					* (destination.x() - opponentCoordinate.x())
					+ (destination.y() - opponentCoordinate.y())
							* (destination.y() - opponentCoordinate.y()));

	float angle = acos(
			(myToOpponent * myToOpponent + myToDestination * myToDestination
					- OpponentToDestination * OpponentToDestination) / 2
					/ myToOpponent / myToDestination);
	angle = angle / PI * 180;

	if (myToOpponent >= myToDestination || myToDestination < 0.3 * CELL_LENGTH)
	{
		angle = 90;
	}

	///cout<<"~~~~~~~~~~~~~~~~~~~~~~angle:"<<angle<<endl;
	return angle;
}

void WorldModel::updateLastCyclesAverageVerticalTurnHeadAngle() ///useless
{
	static int point = 0;
	if (CanSeeTheBall())
	{
		lastCyclesVerticalTurnHeadAngle[point % LAST_CYCLES_OF_TURN_HEAD_ANGLE] =
				GetCurrentJointAngle(JID_HEAD_2);
	}
	else
	{
		lastCyclesVerticalTurnHeadAngle[point % LAST_CYCLES_OF_TURN_HEAD_ANGLE] =
				GetLastCyclesAverageVerticalTurnHeadAngle();
	}
	point++;

	float angle;
	float totalAngle;
	for (int i = 0; i < LAST_CYCLES_OF_TURN_HEAD_ANGLE; i++)
	{
		//	ball=Vector3( lastCyclesBallCoordinate[i].x,lastCyclesBallCoordinate[i].y,lastCyclesBallCoordinate[i].z   );
		angle = lastCyclesVerticalTurnHeadAngle[i];
///		if(fabs(ball.x()-lastCyclesAverageBallCoordinate.x())>0.1)
		{
//			/////cout<<"DDDDDDDDDDDlastCyclesBallCoordinate[  " <<i<<"  ]:   "<<lastCyclesBallCoordinate[i]<<endl;
		}
///		else if(fabs(ball.y()-lastCyclesAverageBallCoordinate.y())>0.1)
		{
//			/////cout<<"EEEEEEEEEEElastCyclesBallCoordinate[  " <<i<<"  ]:   "<<lastCyclesBallCoordinate[i]<<endl;
		}
		totalAngle += angle;
	}
	lastCyclesAverageVerticalTurnHeadAngle = totalAngle
			/ LAST_CYCLES_OF_TURN_HEAD_ANGLE;
	/////cout<<"QQQQQQQQQQQlastCyclesAverageVerticalTurnHeadAngle:    "<<lastCyclesAverageVerticalTurnHeadAngle<<endl;
}

float WorldModel::GetLastCyclesAverageVerticalTurnHeadAngle()
{
	return lastCyclesAverageVerticalTurnHeadAngle;
}

void WorldModel::updateVanguardNumberByVision()
{
///	int number;
	float dis = 40;
	float myDisToTeammate, myAngleToTeammate, distance;
	float myAngleToBall = GetMyAngleToBall(), myDistanceToBall =
			GetMyDistanceToBall();
	float angle;
	for (TPlayerSenseMap::iterator iter =
			messageParser.mTeamMateSenseMap.begin();
			iter != messageParser.mTeamMateSenseMap.end(); ++iter)
			{
		if ((*iter).second.unum != 1&& (*iter).second.unum !=CITHear.GetTheLastPlayerNum())
		{
			myDisToTeammate = (*iter).second.head.distance;
			myAngleToTeammate = (*iter).second.head.theta;
			if ((myAngleToBall * myAngleToTeammate) < 0)
			{
				angle = fabs(myAngleToBall) + fabs(myAngleToTeammate);
			}
			else
			{
				angle = fabs(myAngleToBall - myAngleToTeammate);
			}
			distance = sqrt(
					myDistanceToBall * myDistanceToBall
							+ myDisToTeammate * myDisToTeammate
							- cos(angle * PI / 180) * 2 * myDistanceToBall
									* myDisToTeammate);
			if (distance < dis)
			{
				vanguardNumberByVision = (*iter).second.unum;
				dis = distance;
			}
		}
	}
	/////cout<<"I see Vanguard number:"<<vanguardNumberByVision<<endl;
///	return vanguardNumberByVision;
}

int WorldModel::GetVanguardNumberByVision()
{
	return vanguardNumberByVision;
}

bool WorldModel::WhetherVanguardDownByVision()
{
	return CITHear.IsStandByHear(GetVanguardNumberByVision());
}

void WorldModel::updateTheBodyBalanceState()
{
	gyr_Stat[stat_Counter] = getAverageOfLastCyclesGYR().mod();
	frp_Stat[stat_Counter] = getAverageOfLastCyclesFRP_Lf().z()
			+ getAverageOfLastCyclesFRP_Rf().z();
	stat_Counter++;
	if (stat_Counter == 5)
		stat_Counter = 0;
	frpz = frp_Stat[0] + frp_Stat[1] + frp_Stat[2] + frp_Stat[3] + frp_Stat[4];
	gyrmod = gyr_Stat[0] + gyr_Stat[1] + gyr_Stat[2] + gyr_Stat[3]
			+ gyr_Stat[4];
	/////cout<<"				frpz  ="<<frpz<<"		gyrmod ="<<gyrmod<<endl;
	if (frpz < 200 && gyrmod > 250)
	{
		/////cout<<"		is		Body		Imbalance	state!!!!"<<endl;
		isBodyImbalance = true;
	}

	if (frpz > 250 && gyrmod < 200)
	{
		/////cout<<"		is		Body		good	state!!!!"<<endl;
		isBodyImbalance = false;
	}
	if (getAverageOfLastCyclesFRP_Lc().y() + getAverageOfLastCyclesFRP_Rc().y()
			> 0)
	{
		fallDirection = D_FORWARD;
	}
	else
	{
		fallDirection = D_BACK;
	}
}
bool WorldModel::isBodyInDangerousState()
{
	return isBodyImbalance;
}

Vector3 WorldModel::GetTeammateCoordinate(int num)
{
	///return Vector3(0,0,0);
	if (num > 0)
	{
		return TeammateCoordinate[num - 1][21];
	}
	else
	{
		return Vector3(0, 0, 0);
	}
}

Vector3 WorldModel::GetOpponentCoordinate(int num)
{
	/// return Vector3(0,0,0);
	if (num > 0)
	{
		return OpponentCoordinate[num - 1][21];
	}
	else
	{
		return Vector3(0, 0, 0);
	}
}

void WorldModel::updateLastCyclesAverageBallMeXYDifference()
{
	static int point = 0;
///	Vector3 ball=GetLastCyclesAverageBallCoordinate();
	Vector3 my = GetMyCoordinate();
	if (CanSeeTheBall())
	{
		lastCyclesAverageBallMeXDifferenceArray[point % 5] = ball.x() - my.x();
		lastCyclesAverageBallMeYDifferenceArray[point % 5] = ball.y() - my.y();
	}
	else
	{
		lastCyclesAverageBallMeXDifferenceArray[point % 5] =
				lastCyclesAverageBallMeXDifference;
		lastCyclesAverageBallMeYDifferenceArray[point % 5] =
				lastCyclesAverageBallMeYDifference;
	}
	point++;

	//float angle;
	//float totalAngle;
	for (int i = 0; i < 5; i++)
	{
		lastCyclesAverageBallMeXDifference +=
				lastCyclesAverageBallMeXDifferenceArray[i];
		lastCyclesAverageBallMeYDifference +=
				lastCyclesAverageBallMeYDifferenceArray[i];
	}
	lastCyclesAverageBallMeXDifference = lastCyclesAverageBallMeXDifference / 5;
	lastCyclesAverageBallMeYDifference = lastCyclesAverageBallMeYDifference / 5;
}

float WorldModel::GetLastCyclesAverageBallMeXDifference()
{
	Vector3 ball=GetLastCyclesAverageBallCoordinate();
	Vector3 my = GetMyCoordinate();
	if (lastCyclesAverageBallMeXDifference > -10
			&& lastCyclesAverageBallMeXDifference)

		return lastCyclesAverageBallMeXDifference;
	else
		return ball.x() - my.x();
}

float WorldModel::GetLastCyclesAverageBallMeYDifference()
{
	return lastCyclesAverageBallMeYDifference;
}

void WorldModel::updateClosestToBallOpponentNumberAndDistanceByVision()
{
///	int number;
///	float dis=40;
	closestToBallOpponentDistanceByVision = 40;
	float myDisToOpponent, myAngleToOpponent, distance;
	float myAngleToBall = GetMyAngleToBall(), myDistanceToBall =
			GetMyDistanceToBall();
	float angle;
	for (TPlayerSenseMap::iterator iter =
			messageParser.mOpponentSenseMap.begin();
			iter != messageParser.mOpponentSenseMap.end(); ++iter)
			{

		myDisToOpponent = (*iter).second.head.distance;
		myAngleToOpponent = (*iter).second.head.theta;
		if (myAngleToOpponent != 0)
		{
			if ((myAngleToBall * myAngleToOpponent) < 0)
			{
				angle = fabs(myAngleToBall) + fabs(myAngleToOpponent);
				///cout<<"myAngleToBall:"<<myAngleToBall<<endl;
				///cout<<"myAngleToOpponent:"<<myAngleToOpponent<<endl;
				///cout<<"angle1:"<<angle<<endl;
			}
			else
			{
				angle = fabs(myAngleToBall - myAngleToOpponent);
				///cout<<"myAngleToBall:"<<myAngleToBall<<endl;
				///cout<<"myAngleToOpponent:"<<myAngleToOpponent<<endl;
				///cout<<"angle2:"<<angle<<endl;
			}
			///cout<<"myDistanceToBall:"<<myDistanceToBall<<endl;
			///cout<<"myDisToOpponent:"<<myDisToOpponent<<endl;
			distance = sqrt(
					myDistanceToBall * myDistanceToBall
							+ myDisToOpponent * myDisToOpponent
							- cos(angle * PI / 180) * 2 * myDistanceToBall
									* myDisToOpponent);
			///cout<<"opponent number:"<<(*iter).second.unum<<"distance to ball:"<<distance<<endl;
			if (distance < closestToBallOpponentDistanceByVision)
			{
				closestToBallOpponentNumberByVision = (*iter).second.unum;
				closestToBallOpponentDistanceByVision = distance;
			}
		}
	}
	/////cout<<"I see Vanguard number:"<<vanguardNumberByVision<<endl;
///	return vanguardNumberByVision;
}

int WorldModel::GetClosestToBallOpponentNumberByVision()
{
	closestToBallOpponentDistanceByVision = 40;
	float myDisToOpponent, myAngleToOpponent, distance;
	float myAngleToBall = GetMyAngleToBall(), myDistanceToBall =
			GetMyDistanceToBall();
	float angle;
	for (TPlayerSenseMap::iterator iter =
			messageParser.mOpponentSenseMap.begin();
			iter != messageParser.mOpponentSenseMap.end(); ++iter)
			{

		myDisToOpponent = (*iter).second.head.distance;
		myAngleToOpponent = (*iter).second.head.theta;
		if (myAngleToOpponent != 0)
		{
			if ((myAngleToBall * myAngleToOpponent) < 0)
			{
				angle = fabs(myAngleToBall) + fabs(myAngleToOpponent);
//			///cout<<"myAngleToBall:"<<myAngleToBall<<endl;
//			///cout<<"myAngleToOpponent:"<<myAngleToOpponent<<endl;
//			///cout<<"angle1:"<<angle<<endl;
			}
			else
			{
				angle = fabs(myAngleToBall - myAngleToOpponent);
//			///cout<<"myAngleToBall:"<<myAngleToBall<<endl;
//			///cout<<"myAngleToOpponent:"<<myAngleToOpponent<<endl;
//			///cout<<"angle2:"<<angle<<endl;
			}
//		///cout<<"myDistanceToBall:"<<myDistanceToBall<<endl;
//		///cout<<"myDisToOpponent:"<<myDisToOpponent<<endl;
			distance = sqrt(
					myDistanceToBall * myDistanceToBall
							+ myDisToOpponent * myDisToOpponent
							- cos(angle * PI / 180) * 2 * myDistanceToBall
									* myDisToOpponent);
//		///cout<<"opponent number:"<<(*iter).second.unum<<"distance to ball:"<<distance<<endl;
			if (distance < closestToBallOpponentDistanceByVision)
			{
				closestToBallOpponentNumberByVision = (*iter).second.unum;
				closestToBallOpponentDistanceByVision = distance;
			}
		}
	}

	return closestToBallOpponentNumberByVision;
}

float WorldModel::GetClosestToBallOpponentDistanceByVision()
{
	closestToBallOpponentDistanceByVision = 40;
	float myDisToOpponent, myAngleToOpponent, distance;
	float myAngleToBall = GetMyAngleToBall(), myDistanceToBall =
			GetMyDistanceToBall();
	float angle;
	for (TPlayerSenseMap::iterator iter =
			messageParser.mOpponentSenseMap.begin();
			iter != messageParser.mOpponentSenseMap.end(); ++iter)
			{

		myDisToOpponent = (*iter).second.head.distance;
		myAngleToOpponent = (*iter).second.head.theta;
		if (myAngleToOpponent != 0)
		{
			if ((myAngleToBall * myAngleToOpponent) < 0)
			{
				angle = fabs(myAngleToBall) + fabs(myAngleToOpponent);
//			///cout<<"myAngleToBall:"<<myAngleToBall<<endl;
//			///cout<<"myAngleToOpponent:"<<myAngleToOpponent<<endl;
//			///cout<<"angle1:"<<angle<<endl;
			}
			else
			{
				angle = fabs(myAngleToBall - myAngleToOpponent);
//			///cout<<"myAngleToBall:"<<myAngleToBall<<endl;
//			///cout<<"myAngleToOpponent:"<<myAngleToOpponent<<endl;
//			///cout<<"angle2:"<<angle<<endl;
			}
//		///cout<<"myDistanceToBall:"<<myDistanceToBall<<endl;
//		///cout<<"myDisToOpponent:"<<myDisToOpponent<<endl;
			distance = sqrt(
					myDistanceToBall * myDistanceToBall
							+ myDisToOpponent * myDisToOpponent
							- cos(angle * PI / 180) * 2 * myDistanceToBall
									* myDisToOpponent);
//		///cout<<"opponent number:"<<(*iter).second.unum<<"distance to ball:"<<distance<<endl;
			if (distance < closestToBallOpponentDistanceByVision)
			{
				closestToBallOpponentNumberByVision = (*iter).second.unum;
				closestToBallOpponentDistanceByVision = distance;
			}
		}
	}
	return closestToBallOpponentDistanceByVision;
}

void WorldModel::updateClosestToMeOpponentNumberAndDistanceByVision()
{

	closestToMeOpponentDistanceByVision = 40;
	float myDisToOpponent;
	for (TPlayerSenseMap::iterator iter =
			messageParser.mOpponentSenseMap.begin();
			iter != messageParser.mOpponentSenseMap.end(); ++iter)
			{

		myDisToOpponent = (*iter).second.head.distance;
		if (myDisToOpponent < closestToMeOpponentDistanceByVision)
		{
			closestToMeOpponentNumberByVision = (*iter).second.unum;
			closestToMeOpponentDistanceByVision = myDisToOpponent;
		}

	}
}

int WorldModel::GetClosestToMeOpponentNumberByVision()
{
	closestToMeOpponentDistanceByVision = 40;
	float myDisToOpponent;
	for (TPlayerSenseMap::iterator iter =
			messageParser.mOpponentSenseMap.begin();
			iter != messageParser.mOpponentSenseMap.end(); ++iter)
			{

		myDisToOpponent = (*iter).second.head.distance;
		if (myDisToOpponent < closestToMeOpponentDistanceByVision)
		{
			closestToMeOpponentNumberByVision = (*iter).second.unum;
			closestToMeOpponentDistanceByVision = myDisToOpponent;
		}

	}
	return closestToMeOpponentNumberByVision;
}
int WorldModel::GetClosestToMeTeamNumberByVision()
{
	float closestToMeTeamDistanceByVision = 40;
	float myDisToTeam;
	for (TPlayerSenseMap::iterator iter =
			messageParser.mTeamMateSenseMap.begin();
			iter != messageParser.mTeamMateSenseMap.end(); ++iter)
			{
		myDisToTeam = (*iter).second.head.distance;
		if (myDisToTeam < closestToMeTeamDistanceByVision)
		{
			if ((*iter).second.unum != GetMyNumber())
			{
				closestToMeTeamNumberByVision = (*iter).second.unum;
				closestToMeTeamDistanceByVision = myDisToTeam;
			}
		}
	}
	return closestToMeTeamNumberByVision;
}
int WorldModel::GetNextClosestToMeTeamNumberByVision()
{
	float nextclosestToMeTeamDistanceByVision = 40;
	float myDisToTeam;
	int ClosestToMeTeamNumber = GetClosestToMeTeamNumberByVision();
	for (TPlayerSenseMap::iterator iter =
			messageParser.mTeamMateSenseMap.begin();
			iter != messageParser.mTeamMateSenseMap.end(); ++iter)
			{
		myDisToTeam = (*iter).second.head.distance;
		if (myDisToTeam < nextclosestToMeTeamDistanceByVision)
		{
			if ((*iter).second.unum != GetMyNumber()
					&& (*iter).second.unum != ClosestToMeTeamNumber)
			{
				nextclosestToMeTeamNumberByVision = (*iter).second.unum;
				nextclosestToMeTeamDistanceByVision = myDisToTeam;
			}
		}
	}
	return nextclosestToMeTeamNumberByVision;
}
float WorldModel::GetClosestToMeOpponentDistanceByVision()
{
	closestToMeOpponentDistanceByVision = 40;
	float myDisToOpponent;
	for (TPlayerSenseMap::iterator iter =
			messageParser.mOpponentSenseMap.begin();
			iter != messageParser.mOpponentSenseMap.end(); ++iter)
			{

		myDisToOpponent = (*iter).second.head.distance;
		if (myDisToOpponent < closestToMeOpponentDistanceByVision)
		{
			closestToMeOpponentNumberByVision = (*iter).second.unum;
			closestToMeOpponentDistanceByVision = myDisToOpponent;
		}

	}
	return closestToMeOpponentDistanceByVision;
}

bool WorldModel::CanDoLocalizationByTwoFlags()
{
	return canDoLocalizationByTwoFlags;
}

HorizonMoveDirection WorldModel::GetAdjustToGoalDirection()
{
	HorizonMoveDirection direction = HORIZONMOVE_NULL;

	if (GetMyTeamIndex() == TI_LEFT)
	{
		if (messageParser.mVisionSenseMap.count(VO_FLAG1_L)
				&& messageParser.mVisionSenseMap.count(VO_FLAG2_L))
		{
			if (fabs(messageParser.mVisionSenseMap[VO_FLAG1_L].theta)
					> fabs(messageParser.mVisionSenseMap[VO_FLAG2_L].theta))
			{
				direction = HORIZONMOVE_RIGHT;
			}
			else
			{
				direction = HORIZONMOVE_LEFT;
			}
		}
		else if (messageParser.mVisionSenseMap.count(VO_FLAG1_L))
		{
			//direction=HORIZONMOVE_RIGHT;
			direction = HORIZONMOVE_LEFT;
		}
		else if (messageParser.mVisionSenseMap.count(VO_FLAG2_L))
		{
			//direction=HORIZONMOVE_LEFT;
			direction = HORIZONMOVE_RIGHT;
		}
		else if (messageParser.mVisionSenseMap.count(VO_GOAL1_L)
				&& messageParser.mVisionSenseMap.count(VO_GOAL2_L))
		{
			if (fabs(messageParser.mVisionSenseMap[VO_GOAL1_L].theta)
					> fabs(messageParser.mVisionSenseMap[VO_GOAL2_L].theta))
			{
				direction = HORIZONMOVE_RIGHT;
			}
			else
			{
				direction = HORIZONMOVE_LEFT;
			}
		}
		else if (messageParser.mVisionSenseMap.count(VO_GOAL1_L))
		{
			//direction=HORIZONMOVE_RIGHT;
			direction = HORIZONMOVE_LEFT;
		}
		else if (messageParser.mVisionSenseMap.count(VO_GOAL2_L))
		{
			//direction=HORIZONMOVE_LEFT;
			direction = HORIZONMOVE_RIGHT;
		}
		else
		{
			if (messageParser.mVisionSenseMap.count(VO_FLAG1_R))
			{
				direction = HORIZONMOVE_LEFT;
			}

			if (messageParser.mVisionSenseMap.count(VO_FLAG2_R))
			{
				direction = HORIZONMOVE_RIGHT;
			}
		}
	}
	else if (GetMyTeamIndex() == TI_RIGHT)
	{
		if (messageParser.mVisionSenseMap.count(VO_FLAG1_R)
				&& messageParser.mVisionSenseMap.count(VO_FLAG2_R))
		{
			if (fabs(messageParser.mVisionSenseMap[VO_FLAG1_R].theta)
					> fabs(messageParser.mVisionSenseMap[VO_FLAG2_R].theta))
			{
				direction = HORIZONMOVE_LEFT;
			}
			else
			{
				direction = HORIZONMOVE_RIGHT;
			}
		}
		else if (messageParser.mVisionSenseMap.count(VO_FLAG1_R))
		{
			direction = HORIZONMOVE_RIGHT;
			//direction=HORIZONMOVE_LEFT;
		}
		else if (messageParser.mVisionSenseMap.count(VO_FLAG2_R))
		{
			direction = HORIZONMOVE_LEFT;
			//direction=HORIZONMOVE_RIGHT;
		}
		else if (messageParser.mVisionSenseMap.count(VO_GOAL1_R)
				&& messageParser.mVisionSenseMap.count(VO_GOAL2_R))
		{
			if (fabs(messageParser.mVisionSenseMap[VO_GOAL1_R].theta)
					> fabs(messageParser.mVisionSenseMap[VO_GOAL2_R].theta))
			{
				direction = HORIZONMOVE_LEFT;
			}
			else
			{
				direction = HORIZONMOVE_RIGHT;
			}
		}
		else if (messageParser.mVisionSenseMap.count(VO_GOAL1_R))
		{
			direction = HORIZONMOVE_RIGHT;
			//direction=HORIZONMOVE_LEFT;
		}
		else if (messageParser.mVisionSenseMap.count(VO_GOAL2_R))
		{
			direction = HORIZONMOVE_LEFT;
			//direction=HORIZONMOVE_RIGHT;
		}
		else
		{
			if (messageParser.mVisionSenseMap.count(VO_FLAG1_L))
			{
				direction = HORIZONMOVE_RIGHT;
			}

			if (messageParser.mVisionSenseMap.count(VO_FLAG2_L))
			{
				direction = HORIZONMOVE_LEFT;
			}
		}
	}

	return direction;
}

bool WorldModel::CanAttackOppGoal()
{
	bool res = false;
	float believeTime = 2;
	float dis1 = GetFieldLength(), dis2 = GetFieldLength();
	if (GetMyTeamIndex() == TI_LEFT)
	{

		if (messageParser.mVisionSenseMap.count(VO_GOAL1_R))
		{
			dis1 = messageParser.mVisionSenseMap[VO_GOAL1_R].distance;
			if (dis1 > GetFieldLength() / 2)
			{
				if (fabs(messageParser.mVisionSenseMap[VO_GOAL1_R].theta) < 40)
				{
					res = true;
				}
			}
			else if (dis1 > GetFieldLength() / 4)
			{
				if (fabs(messageParser.mVisionSenseMap[VO_GOAL1_R].theta) < 20)
				{
					res = true;
				}
			}
			else if (dis1 > GetGoalWidth() / 2)
			{
				if (messageParser.mVisionSenseMap[VO_GOAL1_R].theta > 10)
				{
					res = true;
				}
			}
			else if (dis1 < GetGoalWidth() / 2)
			{
				if (messageParser.mVisionSenseMap[VO_GOAL1_R].theta > 5)
				{
					res = true;
				}
			}
		}

		if (messageParser.mVisionSenseMap.count(VO_GOAL2_R))
		{
			dis2 = messageParser.mVisionSenseMap[VO_GOAL2_R].distance;
			if (dis2 > GetFieldLength() / 2)
			{
				if (fabs(messageParser.mVisionSenseMap[VO_GOAL2_R].theta) < 40)
				{
					res = true;
				}
			}
			else if (dis2 > GetFieldLength() / 4)
			{
				if (fabs(messageParser.mVisionSenseMap[VO_GOAL2_R].theta) < 20)
				{
					res = true;
				}
			}
			else if (dis2 > GetGoalWidth() / 2)
			{
				if (messageParser.mVisionSenseMap[VO_GOAL2_R].theta < -10)
				{
					res = true;
				}
			}
			else if (dis2 < GetGoalWidth() / 2)
			{
				if (messageParser.mVisionSenseMap[VO_GOAL2_R].theta < -5)
				{
					res = true;
				}
			}
		}

		if (messageParser.mVisionSenseMap.count(VO_GOAL1_R)
				&& messageParser.mVisionSenseMap.count(VO_GOAL2_R)) //can see goal_1 and goal_2
		{
			float angle1, angle2;
			angle1 = messageParser.mVisionSenseMap[VO_GOAL1_R].theta;
			angle2 = messageParser.mVisionSenseMap[VO_GOAL2_R].theta;

			if ((angle1 * angle2) <= 0 && fabs(angle1) > 10
					&& fabs(angle2) > 10)
				res = true;
		}
#if 1
		if (!messageParser.mVisionSenseMap.count(VO_GOAL1_R)
				&& !messageParser.mVisionSenseMap.count(VO_GOAL2_R))
		{
			float theta1 = 0, theta2 = 0;
			if ((GetCurrentGameTime() - historySenseMap[VO_GOAL1_R].senseTime)
					< believeTime)
			{
				dis1 = historySenseMap[VO_GOAL1_R].distance;
				theta1 = historySenseMap[VO_GOAL1_R].theta;

				if (dis1 < GetGoalWidth() / 2 && theta1 > 5)
					res = true;
			}

			if ((GetCurrentGameTime() - historySenseMap[VO_GOAL2_R].senseTime)
					< believeTime)
			{
				dis2 = historySenseMap[VO_GOAL2_R].distance;
				theta2 = historySenseMap[VO_GOAL2_R].theta;

				if (dis2 < GetGoalWidth() / 2 && theta2 < -5)
					res = true;
			}

			if ((theta1 * theta2) < 0 && theta1 > 10 && theta2 < -10)
				res = true;
		}
#endif
	}
	else if (GetMyTeamIndex() == TI_RIGHT)
	{

		if (messageParser.mVisionSenseMap.count(VO_GOAL1_L))
		{
			dis1 = messageParser.mVisionSenseMap[VO_GOAL1_L].distance;
			if (dis1 > GetFieldLength() / 2)
			{
				if (fabs(messageParser.mVisionSenseMap[VO_GOAL1_L].theta) < 40)
				{
					res = true;
				}
			}
			else if (dis1 > GetFieldLength() / 4)
			{
				if (fabs(messageParser.mVisionSenseMap[VO_GOAL1_L].theta) < 20)
				{
					res = true;
				}
			}
			else if (dis1 > GetGoalWidth() / 2)
			{
				if (messageParser.mVisionSenseMap[VO_GOAL1_L].theta < -10)
				{
					res = true;
				}
			}
			else if (dis1 < GetGoalWidth() / 2)
			{
				if (messageParser.mVisionSenseMap[VO_GOAL1_L].theta < -5)
				{
					res = true;
				}
			}

		}

		if (messageParser.mVisionSenseMap.count(VO_GOAL2_L))
		{
			dis2 = messageParser.mVisionSenseMap[VO_GOAL2_L].distance;
			if (dis2 > GetFieldLength() / 2)
			{
				if (fabs(messageParser.mVisionSenseMap[VO_GOAL2_L].theta) < 40)
				{
					res = true;
				}
			}
			else if (dis2 > GetFieldLength() / 4)
			{
				if (fabs(messageParser.mVisionSenseMap[VO_GOAL2_L].theta) < 20)
				{
					res = true;
				}
			}
			else if (dis2 > GetGoalWidth() / 2)
			{
				if (messageParser.mVisionSenseMap[VO_GOAL2_L].theta > 10)
				{
					res = true;
				}
			}
			else if (dis2 < GetGoalWidth() / 2)
			{
				if (messageParser.mVisionSenseMap[VO_GOAL2_L].theta > 5)
				{
					res = true;
				}
			}
		}

		if (messageParser.mVisionSenseMap.count(VO_GOAL1_L)
				&& messageParser.mVisionSenseMap.count(VO_GOAL2_L))
		{
			float angle1, angle2;
			angle1 = messageParser.mVisionSenseMap[VO_GOAL1_L].theta;
			angle2 = messageParser.mVisionSenseMap[VO_GOAL2_L].theta;

			if ((angle1 * angle2) <= 0 && fabs(angle1) > 10
					&& fabs(angle2) > 10)
				res = true;
		}
#if 1
		if (!messageParser.mVisionSenseMap.count(VO_GOAL1_L)
				&& !messageParser.mVisionSenseMap.count(VO_GOAL2_L))
		{
			float theta1 = 0, theta2 = 0;
			if ((GetCurrentGameTime() - historySenseMap[VO_GOAL1_L].senseTime)
					< believeTime)
			{
				dis1 = historySenseMap[VO_GOAL1_L].distance;
				theta1 = historySenseMap[VO_GOAL1_L].theta;

				if (dis1 < GetGoalWidth() / 2 && theta1 < -5)
					res = true;
			}

			if ((GetCurrentGameTime() - historySenseMap[VO_GOAL2_L].senseTime)
					< believeTime)
			{
				dis2 = historySenseMap[VO_GOAL2_L].distance;
				theta2 = historySenseMap[VO_GOAL2_L].theta;

				if (dis2 < GetGoalWidth() / 2 && theta2 > 5)
					res = true;
			}

			if ((theta1 * theta2) < 0 && theta1 < -10 && theta2 > 10)
				res = true;
		}
#endif
	}

	return res;
}

bool WorldModel::dangerousDistanceToOpp()
{
	for (TPlayerSenseMap::iterator iter =
			messageParser.mOpponentSenseMap.begin();
			iter != messageParser.mOpponentSenseMap.end(); ++iter)
			{
		if ((*iter).second.head.distance < 0.6)
		{
			return true;
		}
		/////cout<<"time :"<<GetCurrentGameTime()<<"		number :"<<(*iter).second.unum<<"	distance :"<<(*iter).second.head.distance<<"		angle :"
		//<<(*iter).second.head.theta<<"	phi :"<<(*iter).second.head.phi<<endl;
	}
	return false;
}

void WorldModel::updateClosestToVanguardOpponentNumberAndDistanceByVision()
{
///	int number;
	float dis = 40;
	float myDistanceToVanguard, myAngleToVanguard, distance;
	float myAngleToOpponent, myDistanceToOpponent, angle;

	for (TPlayerSenseMap::iterator iter =
			messageParser.mTeamMateSenseMap.begin();
			iter != messageParser.mTeamMateSenseMap.end(); ++iter)
			{
		if ((*iter).second.unum == GetVanguardNumberByVision()
				&& (*iter).second.head.distance != 0)
		{
			myDistanceToVanguard = (*iter).second.head.distance;
			myAngleToVanguard = (*iter).second.head.theta;
		}
	}

	for (TPlayerSenseMap::iterator iter =
			messageParser.mOpponentSenseMap.begin();
			iter != messageParser.mOpponentSenseMap.end(); ++iter)
			{
		myAngleToOpponent = (*iter).second.head.theta;
		myDistanceToOpponent = (*iter).second.head.distance;

		if ((myAngleToOpponent * myAngleToVanguard) < 0)
		{
			angle = fabs(myAngleToOpponent) + fabs(myAngleToVanguard);
		}
		else
		{
			angle = fabs(myAngleToVanguard - myAngleToOpponent);
		}
		distance = sqrt(
				myDistanceToVanguard * myDistanceToVanguard
						+ myDistanceToOpponent * myDistanceToOpponent
						- cos(angle * PI / 180) * 2 * myDistanceToVanguard
								* myDistanceToOpponent);
		if (distance < dis)
		{
			closestToVanguardOpponentNumber = (*iter).second.unum;
			dis = distance;
		}
	}
	closestToVanguardOpponentDistance = dis;

	/////cout<<"I see Vanguard number:"<<vanguardNumberByVision<<endl;
///	return vanguardNumberByVision;
}

int WorldModel::GetClosestToVanguardOpponentNumberByVision()
{
	float dis = 40;
	float myDistanceToVanguard, myAngleToVanguard, distance;
	float myAngleToOpponent, myDistanceToOpponent, angle;

	for (TPlayerSenseMap::iterator iter =
			messageParser.mTeamMateSenseMap.begin();
			iter != messageParser.mTeamMateSenseMap.end(); ++iter)
			{
		if ((*iter).second.unum == GetVanguardNumberByVision()
				&& (*iter).second.head.distance != 0)
		{
			myDistanceToVanguard = (*iter).second.head.distance;
			myAngleToVanguard = (*iter).second.head.theta;
		}
	}

	for (TPlayerSenseMap::iterator iter =
			messageParser.mOpponentSenseMap.begin();
			iter != messageParser.mOpponentSenseMap.end(); ++iter)
			{
		myAngleToOpponent = (*iter).second.head.theta;
		myDistanceToOpponent = (*iter).second.head.distance;

		if ((myAngleToOpponent * myAngleToVanguard) < 0)
		{
			angle = fabs(myAngleToOpponent) + fabs(myAngleToVanguard);
		}
		else
		{
			angle = fabs(myAngleToVanguard - myAngleToOpponent);
		}
		distance = sqrt(
				myDistanceToVanguard * myDistanceToVanguard
						+ myDistanceToOpponent * myDistanceToOpponent
						- cos(angle * PI / 180) * 2 * myDistanceToVanguard
								* myDistanceToOpponent);
		if (distance < dis)
		{
			closestToVanguardOpponentNumber = (*iter).second.unum;
			dis = distance;
		}
	}
	closestToVanguardOpponentDistance = dis;

	return closestToVanguardOpponentNumber;
}

float WorldModel::GetClosestToVanguardOpponentDistanceByVision()
{
	float dis = 40;
	float myDistanceToVanguard, myAngleToVanguard, distance;
	float myAngleToOpponent, myDistanceToOpponent, angle;

	for (TPlayerSenseMap::iterator iter =
			messageParser.mTeamMateSenseMap.begin();
			iter != messageParser.mTeamMateSenseMap.end(); ++iter)
			{
		if ((*iter).second.unum == GetVanguardNumberByVision()
				&& (*iter).second.head.distance != 0)
		{
			myDistanceToVanguard = (*iter).second.head.distance;
			myAngleToVanguard = (*iter).second.head.theta;
		}
	}

	for (TPlayerSenseMap::iterator iter =
			messageParser.mOpponentSenseMap.begin();
			iter != messageParser.mOpponentSenseMap.end(); ++iter)
			{
		myAngleToOpponent = (*iter).second.head.theta;
		myDistanceToOpponent = (*iter).second.head.distance;

		if ((myAngleToOpponent * myAngleToVanguard) < 0)
		{
			angle = fabs(myAngleToOpponent) + fabs(myAngleToVanguard);
		}
		else
		{
			angle = fabs(myAngleToVanguard - myAngleToOpponent);
		}
		distance = sqrt(
				myDistanceToVanguard * myDistanceToVanguard
						+ myDistanceToOpponent * myDistanceToOpponent
						- cos(angle * PI / 180) * 2 * myDistanceToVanguard
								* myDistanceToOpponent);
		if (distance < dis)
		{
			closestToVanguardOpponentNumber = (*iter).second.unum;
			dis = distance;
		}
	}
	closestToVanguardOpponentDistance = dis;

	return closestToVanguardOpponentDistance;
}

bool WorldModel::IsTheBallOutOfShootArea()
{
	if (!CanSeeTheBall())
	{
// 		///cout<<"can not see the ball"<<endl;
		return true;
	}
	if (GetMyDistanceToBall() < 0.135)
	{
// 	      ///cout<<"GetMyDistanceToBall()<0.135"<<endl;
//		return true;
	}
	if (GetMyDistanceToBall() < 0.2 && fabs(GetMyBodyAngleToBall()) > 35)
	{
// 	      ///cout<<"GetMyDistanceToBall()<0.2&&fabs(GetMyBodyAngleToBall())>35"<<endl;
		return true;
	}

	if (GetMyTeamIndex() == TI_LEFT)
	{
		if (GetMyDistanceToBall() < 0.35
				&& (messageParser.mVisionSenseMap[VO_GOAL1_R].phi == 0
						|| messageParser.mVisionSenseMap[VO_GOAL2_R].phi == 0))
		{
// 	      ///cout<<"GetMyDistanceToBall()<0.35&&(messageParser.mVisionSenseMap[VO_GOAL1_R].phi==0||messageParser.mVisionSenseMap[VO_GOAL2_R].phi==0))"<<endl;
			return true;
		}
	}
	else
	{
		if (GetMyDistanceToBall() < 0.35
				&& (messageParser.mVisionSenseMap[VO_GOAL1_L].phi == 0
						|| messageParser.mVisionSenseMap[VO_GOAL2_L].phi == 0))
		{
// 	      ///cout<<"GetMyDistanceToBall()<0.35&&(messageParser.mVisionSenseMap[VO_GOAL1_R].phi==0||messageParser.mVisionSenseMap[VO_GOAL2_R].phi==0))"<<endl;
			return true;
		}
	}

	if (GetMyTeamIndex() == TI_LEFT)
	{
		if ((messageParser.mVisionSenseMap[VO_GOAL1_R].distance
				- GetMyDistanceToBall()) < 1.8
				|| (messageParser.mVisionSenseMap[VO_GOAL2_R].distance
						- GetMyDistanceToBall()) < 1.8)
			return true;
	}
	else
	{
		if ((messageParser.mVisionSenseMap[VO_GOAL1_L].distance
				- GetMyDistanceToBall()) < 1.8
				|| (messageParser.mVisionSenseMap[VO_GOAL2_L].distance
						- GetMyDistanceToBall()) < 1.8)
			return true;

	}
	return false;
}

bool WorldModel::GetMyDistanceToMyGoalCenterSortedIndex(int& index)
{
	index = 1;
	Vector3 GoalCenter = Vector3(-GetFieldLength() / 2, 0, 0);
	float myDisTogoalCenter = (GetMyCoordinate() - GoalCenter).xymod();
	for (int i = 1; i <= PLAYERNUMBER; i++)
	{
		float teamdisToCenter =
				(GetNewTeammateCoordinate(i) - GoalCenter).xymod();
		if (teamdisToCenter > myDisTogoalCenter)
		{
			index++;
		}
	}
	return index;
}
bool WorldModel::GetMyDistanceToBallSortedIndexOld(int& index)
{
	index = 1;
	float myAngleToBall = messageParser.GetVisionPolarCoordinate(VO_BALL).theta;
	float angle = 0, myAngleToAgent = 0;

	for (TPlayerSenseMap::iterator iter =
			messageParser.mTeamMateSenseMap.begin();
			iter != messageParser.mTeamMateSenseMap.end(); ++iter)
			{
		///cout<<"88888888888888888888(*iter).second.unum:"<<(*iter).second.unum<<endl;
		///cout<<"88888888888888888888(*iter).second.head.distance:"<<(*iter).second.head.distance<<endl;
		myAngleToAgent = (*iter).second.head.theta;
		if ((myAngleToBall * myAngleToAgent) < 0)
		{
			angle = fabs(myAngleToBall) + fabs(myAngleToAgent);
		}
		else
		{
			angle = fabs(myAngleToBall - myAngleToAgent);
		}

		float dis = 0;
		dis = sqrt(
				myDistanceToBall * myDistanceToBall
						+ (*iter).second.head.distance
								* (*iter).second.head.distance
						- cos(angle * PI / 180) * 2 * myDistanceToBall
								* (*iter).second.head.distance);
		//	float adjust;
		//	adjust=getClosenessToBallMeasure((*iter).second.unum);
		//	dis=dis+adjust;
		///	Vector3 teammateCoordinate=GetTeammateCoordinate((*iter).second.unum);
		///	///cout<<"teammateCoordinate:  "<<(*iter).second.unum<<"   :   "<<teammateCoordinate<<endl;
		//	int myNumber=GetMyNumber();
		if (dis < (myDistanceToBall) && (*iter).second.unum != 1) ///changed by gaojin
		{
			///cout<<"index++"<<endl;
			index++;
		}
	}
	return index;
}

void WorldModel::updateMyTeamMateAndOpponentPositionOfMyTeamMate()
{
///	int number;
	float myDistanceToTeamMate, myAngleToTeamMate, distance;
	int teamMateNum = 0;
	float myAngleToOpponent, myDistanceToOpponent, angle;
	string sayMessage("000000000"); //say message   0-9bit stand for cit3d num 0-9;  1:front a opponent;  2:left a opponent;  3:back a opponent;  4:right a oppnent
	//					        5:front a teammate;  6:left a teamate;  7:back a teammate;  8:right a teamate

	for (TPlayerSenseMap::iterator iter =
			messageParser.mTeamMateSenseMap.begin();
			iter != messageParser.mTeamMateSenseMap.end(); ++iter)
			{
		if ((*iter).second.head.distance == 0)
			continue;
		myDistanceToTeamMate = (*iter).second.head.distance;
		myAngleToTeamMate = (*iter).second.head.theta;
		teamMateNum = (*iter).second.unum;
		for (TPlayerSenseMap::iterator iter2 =
				messageParser.mTeamMateSenseMap.begin();
				iter2 != messageParser.mTeamMateSenseMap.end(); ++iter2)
				{
			if ((*iter2).second.head.distance == 0
					|| (*iter2).second.unum == teamMateNum)
				continue;
			myAngleToOpponent = (*iter2).second.head.theta;
			myDistanceToOpponent = (*iter2).second.head.distance;
			angle = fabs(myAngleToOpponent - myAngleToTeamMate);
			distance = myDistanceToTeamMate * myDistanceToTeamMate
					+ myDistanceToOpponent * myDistanceToOpponent
					- cos(angle * PI / 180) * 2 * myDistanceToTeamMate
							* myDistanceToOpponent;

			if (distance < 0.9)
			{
				float angle1 = myAngleToTeamMate + GetMyHeadAngleToXAxis();
				float angle2 = myAngleToOpponent + GetMyHeadAngleToXAxis();
				if (angle1 > 0 && angle2 > 0 && angle1 < 90 && angle2 < 90)
				{
					float k = (myDistanceToTeamMate * sin(angle1 * PI / 180)
							- myDistanceToOpponent * sin(angle2 * PI / 180))
							/ (myDistanceToTeamMate * cos(angle1 * PI / 180)
									- myDistanceToOpponent
											* cos(angle2 * PI / 180));
					if (k > 0)
					{
						if (myDistanceToTeamMate > myDistanceToOpponent)
						{
							if (k > 1)
							{
								sayMessage[teamMateNum - 1] = '8';
							}
							else
							{
								sayMessage[teamMateNum - 1] = '7';
							}
						}
						else
						{
							if (k > 1)
							{
								sayMessage[teamMateNum - 1] = '6';
							}
							else
							{
								sayMessage[teamMateNum - 1] = '5';
							}
						}
					}
					else
					{
						if (myAngleToTeamMate < myAngleToOpponent)
						{
							if (k < -1)
							{
								sayMessage[teamMateNum - 1] = '6';
							}
							else
							{
								sayMessage[teamMateNum - 1] = '7';
							}
						}
						else
						{
							if (k < -1)
							{
								sayMessage[teamMateNum - 1] = '8';
							}
							else
							{
								sayMessage[teamMateNum - 1] = '5';
							}
						}
					}
				}

				if (angle1 < 0 && angle2 < 0 && angle1 > -90 && angle2 > -90)
				{
					float k = (myDistanceToTeamMate * sin(angle1 * PI / 180)
							- myDistanceToOpponent * sin(angle2 * PI / 180))
							/ (myDistanceToTeamMate * cos(angle1 * PI / 180)
									- myDistanceToOpponent
											* cos(angle2 * PI / 180));
					if (k < 0)
					{
						if (myDistanceToTeamMate > myDistanceToOpponent)
						{
							if (k < -1)
							{
								sayMessage[teamMateNum - 1] = '6';
							}
							else
							{
								sayMessage[teamMateNum - 1] = '7';
							}
						}
						else
						{
							if (k < -1)
							{
								sayMessage[teamMateNum - 1] = '8';
							}
							else
							{
								sayMessage[teamMateNum - 1] = '5';
							}
						}
					}
					else
					{
						if (myAngleToTeamMate < myAngleToOpponent)
						{
							if (k > 1)
							{
								sayMessage[teamMateNum - 1] = '6';
							}
							else
							{
								sayMessage[teamMateNum - 1] = '5';
							}
						}
						else
						{
							if (k > 1)
							{
								sayMessage[teamMateNum - 1] = '8';
							}
							else
							{
								sayMessage[teamMateNum - 1] = '7';
							}
						}

					}
				}

// ///cout<<"teamate :"<<teamMateNum<<"  To friends :"<<(*iter2).second.unum<<"  angle1 :"<<myAngleToTeamMate<<"  angle 2:"<<myAngleToOpponent<<"	distance1 :"<<myDistanceToTeamMate<<"	distance2 :"<<myDistanceToOpponent<<" dis :"<<distance<<endl;			  
// // 			    ///cout<<"teamate :"<<teamMateNum<<"  x:"<<GetTeammateCoordinate(teamMateNum).x()<<"  To friends :"<<(*iter2).second.unum<<"  x:"<<GetTeammateCoordinate((*iter2).second.unum).x()<<endl;
			}
		}

		for (TPlayerSenseMap::iterator iter1 =
				messageParser.mOpponentSenseMap.begin();
				iter1 != messageParser.mOpponentSenseMap.end(); ++iter1)
				{
			if ((*iter1).second.head.distance == 0)
				continue;
			myAngleToOpponent = (*iter1).second.head.theta;
			myDistanceToOpponent = (*iter1).second.head.distance;
			angle = fabs(myAngleToOpponent - myAngleToTeamMate);
			distance = myDistanceToTeamMate * myDistanceToTeamMate
					+ myDistanceToOpponent * myDistanceToOpponent
					- cos(angle * PI / 180) * 2 * myDistanceToTeamMate
							* myDistanceToOpponent;

			if (distance < 0.9)
			{
				float angle1 = myAngleToTeamMate + GetMyHeadAngleToXAxis();
				float angle2 = myAngleToOpponent + GetMyHeadAngleToXAxis();
				if (angle1 > 0 && angle2 > 0 && angle1 < 90 && angle2 < 90)
				{
					float k = (myDistanceToTeamMate * sin(angle1 * PI / 180)
							- myDistanceToOpponent * sin(angle2 * PI / 180))
							/ (myDistanceToTeamMate * cos(angle1 * PI / 180)
									- myDistanceToOpponent
											* cos(angle2 * PI / 180));
					if (k > 0)
					{
						if (myDistanceToTeamMate > myDistanceToOpponent)
						{
							if (k > 1)
							{
								sayMessage[teamMateNum - 1] = '4';
							}
							else
							{
								sayMessage[teamMateNum - 1] = '3';
							}
						}
						else
						{
							if (k > 1)
							{
								sayMessage[teamMateNum - 1] = '2';
							}
							else
							{
								sayMessage[teamMateNum - 1] = '1';
							}
						}
					}
					else
					{
						if (myAngleToTeamMate < myAngleToOpponent)
						{
							if (k < -1)
							{
								sayMessage[teamMateNum - 1] = '2';
							}
							else
							{
								sayMessage[teamMateNum - 1] = '3';
							}
						}
						else
						{
							if (k < -1)
							{
								sayMessage[teamMateNum - 1] = '4';
							}
							else
							{
								sayMessage[teamMateNum - 1] = '1';
							}
						}
					}
				}

				if (angle1 < 0 && angle2 < 0 && angle1 > -90 && angle2 > -90)
				{
					float k = (myDistanceToTeamMate * sin(angle1 * PI / 180)
							- myDistanceToOpponent * sin(angle2 * PI / 180))
							/ (myDistanceToTeamMate * cos(angle1 * PI / 180)
									- myDistanceToOpponent
											* cos(angle2 * PI / 180));
					if (k < 0)
					{
						if (myDistanceToTeamMate > myDistanceToOpponent)
						{
							if (k < -1)
							{
								sayMessage[teamMateNum - 1] = '2';
							}
							else
							{
								sayMessage[teamMateNum - 1] = '3';
							}
						}
						else
						{
							if (k < -1)
							{
								sayMessage[teamMateNum - 1] = '4';
							}
							else
							{
								sayMessage[teamMateNum - 1] = '1';
							}
						}
					}
					else
					{
						if (myAngleToTeamMate < myAngleToOpponent)
						{
							if (k > 1)
							{
								sayMessage[teamMateNum - 1] = '2';
							}
							else
							{
								sayMessage[teamMateNum - 1] = '1';
							}
						}
						else
						{
							if (k > 1)
							{
								sayMessage[teamMateNum - 1] = '4';
							}
							else
							{
								sayMessage[teamMateNum - 1] = '3';
							}
						}

					}
				}

			}
		}
	}
	//if(sayMessage!="000000000")
	//  ///cout<<"time :"<<GetCurrentGameTime()<<"		sayMessage :"<<sayMessage<<endl;
	messageToSayAboutPositon = sayMessage;
}
string WorldModel::GetTheMessageToSayAboutMyTeamMatePositon()
{
	return messageToSayAboutPositon;
}
bool WorldModel::EstimateWhetherUseHalfWalk()
{
	for (TPlayerSenseMap::iterator iter1 =
			messageParser.mOpponentSenseMap.begin();
			iter1 != messageParser.mOpponentSenseMap.end(); ++iter1)
			{
		if ((*iter1).second.head.distance == 0)
			continue;
		float myBodyAngleToOpponent = (*iter1).second.head.theta
				+ GetCurrentJointAngle(JID_HEAD_1);
		float myDistanceToOpponent = (*iter1).second.head.distance;
		if (fabs(myBodyAngleToOpponent) < 35 && myDistanceToOpponent < 0.8
				&& CanSeeTheBall() && fabs(GetMyBodyAngleToBall()) < 35)
		{
			return true;
		}
		else if (fabs(myBodyAngleToOpponent) < 50 && myDistanceToOpponent < 0.42
				&& CanSeeTheBall() && fabs(GetMyBodyAngleToBall()) < 40)
		{
			return true;
		}
	}
	return false;
}
bool WorldModel::WhetherFaceToOppGoal()
{
	if (GetMyTeamIndex() == TI_LEFT)
	{
		if (messageParser.mVisionSenseMap[VO_GOAL2_R].phi != 0
				|| messageParser.mVisionSenseMap[VO_GOAL1_R].phi != 0)
			return true;
		else
			return false;
	}
	else
	{
		if (messageParser.mVisionSenseMap[VO_GOAL2_L].phi != 0
				|| messageParser.mVisionSenseMap[VO_GOAL1_L].phi != 0)
			return true;
		else
			return false;

	}
}

float WorldModel::GetMyDistanceToOpponent(int num)
{
	float dis = 0;
	for (TPlayerSenseMap::iterator iter =
			messageParser.mOpponentSenseMap.begin();
			iter != messageParser.mOpponentSenseMap.end(); ++iter)
			{
		if (num == (*iter).second.unum && (*iter).second.head.distance != 0)
		{
			dis = (*iter).second.head.distance;
			break;
		}
	}

	return dis;
}

float WorldModel::GetMyHeadAngleToOpponent(int num)
{
	float angle = 0;
	for (TPlayerSenseMap::iterator iter =
			messageParser.mOpponentSenseMap.begin();
			iter != messageParser.mOpponentSenseMap.end(); ++iter)
			{
		if (num == (*iter).second.unum && (*iter).second.head.distance != 0)
		{
			angle = (*iter).second.head.theta;
			break;
		}
	}

	return angle;
}

float WorldModel::GetMyBodyAngleToOpponent(int num)
{
	float angle = 0;
	for (TPlayerSenseMap::iterator iter =
			messageParser.mOpponentSenseMap.begin();
			iter != messageParser.mOpponentSenseMap.end(); ++iter)
			{
		if (num == (*iter).second.unum && (*iter).second.head.distance != 0)
		{
			angle = (*iter).second.head.theta;
			break;
		}
	}
	angle = angle + GetCurrentJointAngle(JID_HEAD_1);

	return angle;
}

float WorldModel::GetMyBodyAngleToTeammate(int num)
{
	float angle = 0;
	for (TPlayerSenseMap::iterator iter =
			messageParser.mOpponentSenseMap.begin();
			iter != messageParser.mOpponentSenseMap.end(); ++iter)
			{
		if (num == (*iter).second.unum && (*iter).second.head.distance != 0)
		{
			angle = (*iter).second.head.theta;
			break;
		}
	}
	angle = angle + GetCurrentJointAngle(JID_HEAD_1);
	return angle;
}
void WorldModel::UpdateTeammateStandABCDE()
{
	Vector3 teammateCoordinate;
	float dis = 100;
	Vector3 destination;
	//	int vanguardnum = GetVanguardNumberByVision();
	if (ball.x() > 0)
	{//CDABE
		isTeammateStandCToBall = false;
		destination = GetPositionCoordinate(Position_C);
		dis = 100;
		for (TPlayerSenseMap::iterator iter =
				messageParser.mTeamMateSenseMap.begin();
				iter != messageParser.mTeamMateSenseMap.end(); ++iter)
				{
			if ((*iter).second.unum != 1
					&& (*iter).second.unum != GetVanguardNumberByVision())
			{
				if ((*iter).second.unum != GetMyNumber())
				{
					teammateCoordinate = GetNewTeammateCoordinate(
							(*iter).second.unum);
				}
				else
				{
					teammateCoordinate = GetMyCoordinate();
				}

				if ((destination - teammateCoordinate).xymod() < dis)
				{
					positionCNumber = (*iter).second.unum;
					dis = (destination - teammateCoordinate).xymod();
					isTeammateStandCToBall = true;
				}
			}
		}
		isTeammateStandDToBall = false;
		destination = GetPositionCoordinate(Position_D);
		dis = 100;
		for (TPlayerSenseMap::iterator iter =
				messageParser.mTeamMateSenseMap.begin();
				iter != messageParser.mTeamMateSenseMap.end(); ++iter)
				{
			if ((*iter).second.unum != 1
					&& (*iter).second.unum != GetVanguardNumberByVision())
			{
				if ((*iter).second.unum != positionCNumber)
				{
					if ((*iter).second.unum != GetMyNumber())
					{
						teammateCoordinate = GetNewTeammateCoordinate(
								(*iter).second.unum);
					}
					else
					{
						teammateCoordinate = GetMyCoordinate();
					}

					if (GetDistanceBetweenTwoCoordinate(teammateCoordinate,
							destination) < dis)
					{
						positionDNumber = (*iter).second.unum;
						dis = GetDistanceBetweenTwoCoordinate(
								teammateCoordinate, destination);
					}
					isTeammateStandDToBall = true;
				}
			}
		}
		isTeammateStandAToBall = false;
				destination = GetPositionCoordinate(Position_A);
				dis = 100;
				for (TPlayerSenseMap::iterator iter =
						messageParser.mTeamMateSenseMap.begin();
						iter != messageParser.mTeamMateSenseMap.end(); ++iter)
						{
					if ((*iter).second.unum != 1
							&& (*iter).second.unum != GetVanguardNumberByVision())
					{
						if ((*iter).second.unum != positionDNumber
								&& (*iter).second.unum != positionCNumber
								)
						{
							if ((*iter).second.unum != GetMyNumber())
							{
								teammateCoordinate = GetNewTeammateCoordinate(
										(*iter).second.unum);
							}
							else
							{
								teammateCoordinate = GetMyCoordinate();
							}

							if (GetDistanceBetweenTwoCoordinate(teammateCoordinate,
									destination) < dis)
							{
								positionANumber = (*iter).second.unum;
								dis = GetDistanceBetweenTwoCoordinate(
										teammateCoordinate, destination);
							}
							isTeammateStandAToBall = true;
						}
					}
				}
		isTeammateStandBToBall = false;
		destination = GetPositionCoordinate(Position_B);
		dis = 100;
		for (TPlayerSenseMap::iterator iter =
				messageParser.mTeamMateSenseMap.begin();
				iter != messageParser.mTeamMateSenseMap.end(); ++iter)
				{
			if ((*iter).second.unum != 1
					&& (*iter).second.unum != GetVanguardNumberByVision())
			{
				if ((*iter).second.unum != positionDNumber
						&& (*iter).second.unum != positionCNumber
						&& (*iter).second.unum != positionANumber)
				{
					if ((*iter).second.unum != GetMyNumber())
					{
						teammateCoordinate = GetNewTeammateCoordinate(
								(*iter).second.unum);
					}
					else
					{
						teammateCoordinate = GetMyCoordinate();
					}

					if (GetDistanceBetweenTwoCoordinate(teammateCoordinate,
							destination) < dis)
					{
						positionBNumber = (*iter).second.unum;
						dis = GetDistanceBetweenTwoCoordinate(
								teammateCoordinate, destination);
					}
					isTeammateStandBToBall = true;
				}
			}
		}

	}
	else
	{//DCBAE
		isTeammateStandDToBall = false;
		destination = GetPositionCoordinate(Position_D);
		dis = 100;
		for (TPlayerSenseMap::iterator iter =
				messageParser.mTeamMateSenseMap.begin();
				iter != messageParser.mTeamMateSenseMap.end(); ++iter)
				{
			if ((*iter).second.unum != 1
					&& (*iter).second.unum != GetVanguardNumberByVision())
			{
				if ((*iter).second.unum != GetMyNumber())
				{
					teammateCoordinate = GetNewTeammateCoordinate(
							(*iter).second.unum);
				}
				else
				{
					teammateCoordinate = GetMyCoordinate();
				}

				if ((destination - teammateCoordinate).xymod() < dis)
				{
					positionDNumber = (*iter).second.unum;
					dis = (destination - teammateCoordinate).xymod();
					isTeammateStandDToBall = true;
				}
			}
		}
		isTeammateStandCToBall = false;
		destination = GetPositionCoordinate(Position_C);
		dis = 100;
		for (TPlayerSenseMap::iterator iter =
				messageParser.mTeamMateSenseMap.begin();
				iter != messageParser.mTeamMateSenseMap.end(); ++iter)
				{
			if ((*iter).second.unum != 1
					&& (*iter).second.unum != GetVanguardNumberByVision())
			{
				if ((*iter).second.unum != positionDNumber)
				{
					if ((*iter).second.unum != GetMyNumber())
					{
						teammateCoordinate = GetNewTeammateCoordinate(
								(*iter).second.unum);
					}
					else
					{
						teammateCoordinate = GetMyCoordinate();
					}

					if (GetDistanceBetweenTwoCoordinate(teammateCoordinate,
							destination) < dis)
					{
						positionCNumber = (*iter).second.unum;
						dis = GetDistanceBetweenTwoCoordinate(
								teammateCoordinate, destination);
					}
					isTeammateStandCToBall = true;
				}
			}
		}
		isTeammateStandBToBall = false;
		destination = GetPositionCoordinate(Position_B);
		dis = 100;
		for (TPlayerSenseMap::iterator iter =
				messageParser.mTeamMateSenseMap.begin();
				iter != messageParser.mTeamMateSenseMap.end(); ++iter)
				{
			if ((*iter).second.unum != 1
					&& (*iter).second.unum != GetVanguardNumberByVision())
			{
				if ((*iter).second.unum != positionDNumber
						&& (*iter).second.unum != positionCNumber)
				{
					if ((*iter).second.unum != GetMyNumber())
					{
						teammateCoordinate = GetNewTeammateCoordinate(
								(*iter).second.unum);
					}
					else
					{
						teammateCoordinate = GetMyCoordinate();
					}

					if (GetDistanceBetweenTwoCoordinate(teammateCoordinate,
							destination) < dis)
					{
						positionBNumber = (*iter).second.unum;
						dis = GetDistanceBetweenTwoCoordinate(
								teammateCoordinate, destination);
					}
					isTeammateStandBToBall = true;
				}
			}
		}
		isTeammateStandAToBall = false;
		destination = GetPositionCoordinate(Position_A);
		dis = 100;
		for (TPlayerSenseMap::iterator iter =
				messageParser.mTeamMateSenseMap.begin();
				iter != messageParser.mTeamMateSenseMap.end(); ++iter)
				{
			if ((*iter).second.unum != 1
					&& (*iter).second.unum != GetVanguardNumberByVision())
			{
				if ((*iter).second.unum != positionDNumber
						&& (*iter).second.unum != positionCNumber
						&& (*iter).second.unum != positionBNumber)
				{
					if ((*iter).second.unum != GetMyNumber())
					{
						teammateCoordinate = GetNewTeammateCoordinate(
								(*iter).second.unum);
					}
					else
					{
						teammateCoordinate = GetMyCoordinate();
					}

					if (GetDistanceBetweenTwoCoordinate(teammateCoordinate,
							destination) < dis)
					{
						positionANumber = (*iter).second.unum;
						dis = GetDistanceBetweenTwoCoordinate(
								teammateCoordinate, destination);
					}
					isTeammateStandAToBall = true;
				}
			}
		}

	}
	isTeammateStandEToBall = false;
				destination = GetPositionCoordinate(Position_E);
				dis = 100;
				for (TPlayerSenseMap::iterator iter =
						messageParser.mTeamMateSenseMap.begin();
						iter != messageParser.mTeamMateSenseMap.end(); ++iter)
						{
					if ((*iter).second.unum != 1
							&& (*iter).second.unum != GetVanguardNumberByVision())
					{
						if ((*iter).second.unum != positionDNumber
								&& (*iter).second.unum != positionCNumber
								&& (*iter).second.unum != positionBNumber
								&& (*iter).second.unum != positionENumber)
						{
							if ((*iter).second.unum != GetMyNumber())
							{
								teammateCoordinate = GetNewTeammateCoordinate(
										(*iter).second.unum);
							}
							else
							{
								teammateCoordinate = GetMyCoordinate();
							}

							if (GetDistanceBetweenTwoCoordinate(teammateCoordinate,
									destination) < dis)
							{
								positionENumber = (*iter).second.unum;
								dis = GetDistanceBetweenTwoCoordinate(
										teammateCoordinate, destination);
							}
							isTeammateStandEToBall = true;
						}
					}
				}
}
#if 1
bool WorldModel::WhetherTeammateStandNortheastToBall()
{
	return isTeammateStandDToBall;
}
bool WorldModel::WhetherTeammateStandBackToBall()
{
	return isTeammateStandEToBall;
}
bool WorldModel::WhetherTeammateStandNorthwestToBall()
{
	return isTeammateStandAToBall;
}

bool WorldModel::WhetherTeammateStandSoutheastToBall()
{
	return isTeammateStandCToBall;
}

bool WorldModel::WhetherTeammateStandSouthwestToBall()
{
	return isTeammateStandBToBall;
}

#endif

void WorldModel::updateTeammateCoordinate()
{
	Vector3 myCoordinate=GetMyCoordinate();
	float angle;

//	Vector3 ball=GetLastCyclesAverageBallCoordinate();

	for (TPlayerSenseMap::iterator iter =
			messageParser.mTeamMateSenseMap.begin();
			iter != messageParser.mTeamMateSenseMap.end(); ++iter)
			{
		if ((*iter).second.unum != GetMyNumber() && CanDoLocalizationDirectly()
				&& (*iter).second.head.distance != 0)
		{
			angle = (*iter).second.head.theta + GetCurrentJointAngle(JID_HEAD_1)
					+ GetMyBodyAngleToXAxis();
///	  ///cout<<"XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX"<<endl;
			///cout<<"(*iter).second.head.theta:"<<(*iter).second.head.theta<<endl;
			///cout<<"(*iter).second.head.distance:"<<(*iter).second.head.distance<<endl;
			///cout<<"GetCurrentJointAngle(JID_HEAD_1):"<<GetCurrentJointAngle(JID_HEAD_1)<<endl;
			///cout<<"GetMyBodyAngleToXAxis():"<<GetMyBodyAngleToXAxis()<<endl;
			///cout<<"angle:"<<angle<<"sin(30):"<<sin(30)<<"sin(30*PI/180):"<<sin(30*PI/180)<<endl;
			newTeammateCoordinate[(*iter).second.unum - 1] = Vector3(
					myCoordinate.x()
							+ (*iter).second.head.distance
									* cos(angle * PI / 180),
					myCoordinate.y()
							+ (*iter).second.head.distance
									* sin(angle * PI / 180), myCoordinate.z());
		//	cout<<"newTeammateCoordinate["<<(*iter).second.unum<<"]:"<<newTeammateCoordinate[(*iter).second.unum-1]<<endl;

///	  if(fabs(newTeammateCoordinate[(*iter).second.unum-1].x()-ball.x())>0.5&&fabs(newTeammateCoordinate[(*iter).second.unum-1].y()-ball.y())>0.5)
			{
///	    ///cout<<"vanguardAwayFromball"<<endl;
			}

		}
	}
}

void WorldModel::updateOpponentCoordinate()
{
	float angle;

	for (TPlayerSenseMap::iterator iter =
			messageParser.mOpponentSenseMap.begin();
			iter != messageParser.mOpponentSenseMap.end(); ++iter)
			{
		if (CanDoLocalizationDirectly() && (*iter).second.head.distance != 0)
		{
			angle = (*iter).second.head.theta + GetCurrentJointAngle(JID_HEAD_1)
					+ GetMyBodyAngleToXAxis();

			///cout<<"(*iter).second.head.theta:"<<(*iter).second.head.theta<<endl;
			///cout<<"(*iter).second.head.distance:"<<(*iter).second.head.distance<<endl;
			///cout<<"GetCurrentJointAngle(JID_HEAD_1):"<<GetCurrentJointAngle(JID_HEAD_1)<<endl;
			///cout<<"GetMyBodyAngleToXAxis():"<<GetMyBodyAngleToXAxis()<<endl;
			///cout<<"angle:"<<angle<<"sin(30):"<<sin(30)<<"sin(30*PI/180):"<<sin(30*PI/180)<<endl;
			newOpponentCoordinate[(*iter).second.unum - 1] = Vector3(
					myCoordinate.x()
							+ (*iter).second.head.distance
									* cos(angle * PI / 180),
					myCoordinate.y()
							+ (*iter).second.head.distance
									* sin(angle * PI / 180), myCoordinate.z());
		//	cout<<"newOpponentCoordinate["<<(*iter).second.unum<<"]:"<<newOpponentCoordinate[(*iter).second.unum-1]<<endl;

		}
	}
}

void WorldModel::updateLastCyclesAverageTeammateCoordinate()
{
	static int point1 = 0;
	static int point2 = 0;
	static int point3 = 0;
	static int point4 = 0;
	static int point5 = 0;
	static int point6 = 0;
	static int point7 = 0;
	static int point8 = 0;
	static int point9 = 0;
	Vector3 middle, test;
	//cout<<"updateLastCyclesAverageTeammateCoordinate"<<endl;
	for (TPlayerSenseMap::iterator iter =
			messageParser.mTeamMateSenseMap.begin();
			iter != messageParser.mTeamMateSenseMap.end(); ++iter)
			{
		///cout<<"(*iter).second.unum:"<<(*iter).second.unum<<endl;

		if ((*iter).second.unum == 1 && (*iter).second.unum != GetMyNumber()
				&& (*iter).second.head.distance != 0)
		{

			test = GetNewTeammateCoordinate((*iter).second.unum);
			/*		  if(newAverageTeammateCoordinate[(*iter).second.unum-1].z()==0)
			 {
			 for(int i=0;i<20;i++)
			 {
			 lastCyclesAverageTeammateCoordinate[(*iter).second.unum-1][i]=test;
			 }

			 newAverageTeammateCoordinate[(*iter).second.unum-1]=test;

			 }
			 else
			 {
			 if(fabs(test.x()-newAverageTeammateCoordinate[(*iter).second.unum-1].x())<0.5&&fabs(test.y()-newAverageTeammateCoordinate[(*iter).second.unum-1].y())<0.5)*/
			{
				lastCyclesAverageTeammateCoordinate[(*iter).second.unum - 1][point1
						% LAST_CYCLES_OF_LOCATE_TEAMMATE] = test;
				point1++;
			}
			middle = Vector3(0, 0, 0);
			for (int i = 0; i < LAST_CYCLES_OF_LOCATE_TEAMMATE; i++)
			{
				middle +=
						lastCyclesAverageTeammateCoordinate[(*iter).second.unum
								- 1][i];
				//	  ///cout<<"lastCyclesAverageTeammateCoordinate["<<(*iter).second.unum<<"]["<<i<<"]:"<<lastCyclesAverageTeammateCoordinate[(*iter).second.unum-1][i]<<endl;
			}
			newAverageTeammateCoordinate[(*iter).second.unum - 1] = middle
					/ LAST_CYCLES_OF_LOCATE_TEAMMATE;
			///cout<<"newAverageTeammateCoordinate["<<(*iter).second.unum<<"]:"<<newAverageTeammateCoordinate[(*iter).second.unum-1]<<endl;
//		  }
		}
		else if ((*iter).second.unum == 2
				&& (*iter).second.unum != GetMyNumber()
				&& (*iter).second.head.distance != 0)
		{
			///   ///cout<<"QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ"<<endl;
			test = GetNewTeammateCoordinate((*iter).second.unum);
			/*		  if(newAverageTeammateCoordinate[(*iter).second.unum-1].z()==0)
			 {
			 for(int i=0;i<20;i++)
			 {
			 lastCyclesAverageTeammateCoordinate[(*iter).second.unum-1][i]=test;
			 }

			 newAverageTeammateCoordinate[(*iter).second.unum-1]=test;

			 }
			 else
			 {
			 if(fabs(test.x()-newAverageTeammateCoordinate[(*iter).second.unum-1].x())<0.5&&fabs(test.y()-newAverageTeammateCoordinate[(*iter).second.unum-1].y())<0.5)*/
			{
				lastCyclesAverageTeammateCoordinate[(*iter).second.unum - 1][point2
						% LAST_CYCLES_OF_LOCATE_TEAMMATE] = test;
				point2++;
			}
			middle = Vector3(0, 0, 0);
			for (int i = 0; i < LAST_CYCLES_OF_LOCATE_TEAMMATE; i++)
			{
				middle +=
						lastCyclesAverageTeammateCoordinate[(*iter).second.unum
								- 1][i];
				//	  ///cout<<"lastCyclesAverageTeammateCoordinate["<<(*iter).second.unum<<"]["<<i<<"]:"<<lastCyclesAverageTeammateCoordinate[(*iter).second.unum-1][i]<<endl;
			}
			newAverageTeammateCoordinate[(*iter).second.unum - 1] = middle
					/ LAST_CYCLES_OF_LOCATE_TEAMMATE;
			///cout<<"newAverageTeammateCoordinate["<<(*iter).second.unum<<"]:"<<newAverageTeammateCoordinate[(*iter).second.unum-1]<<endl;
//		  }
		}
		else if ((*iter).second.unum == 3
				&& (*iter).second.unum != GetMyNumber()
				&& (*iter).second.head.distance != 0)
		{
			///   ///cout<<"QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ"<<endl;
			test = GetNewTeammateCoordinate((*iter).second.unum);
			//  if(newAverageTeammateCoordinate[(*iter).second.unum-1].z()==0)
// 		  {
// 		      for(int i=0;i<20;i++)
// 		      {
// 			  lastCyclesAverageTeammateCoordinate[(*iter).second.unum-1][i]=test;
// 		      }
//
// 		      newAverageTeammateCoordinate[(*iter).second.unum-1]=test;
//
// 		  }
// 		  else
// 		  {
//		      if(fabs(test.x()-newAverageTeammateCoordinate[(*iter).second.unum-1].x())<0.5&&fabs(test.y()-newAverageTeammateCoordinate[(*iter).second.unum-1].y())<0.5)
			{
				lastCyclesAverageTeammateCoordinate[(*iter).second.unum - 1][point3
						% LAST_CYCLES_OF_LOCATE_TEAMMATE] = test;
				point3++;
			}
			middle = Vector3(0, 0, 0);
			for (int i = 0; i < LAST_CYCLES_OF_LOCATE_TEAMMATE; i++)
			{
				middle +=
						lastCyclesAverageTeammateCoordinate[(*iter).second.unum
								- 1][i];
				//  ///cout<<"lastCyclesAverageTeammateCoordinate["<<(*iter).second.unum<<"]["<<i<<"]:"<<lastCyclesAverageTeammateCoordinate[(*iter).second.unum-1][i]<<endl;
			}
			newAverageTeammateCoordinate[(*iter).second.unum - 1] = middle
					/ LAST_CYCLES_OF_LOCATE_TEAMMATE;
			///cout<<"newAverageTeammateCoordinate["<<(*iter).second.unum<<"]:"<<newAverageTeammateCoordinate[(*iter).second.unum-1]<<endl;
//		  }
		}
		else if ((*iter).second.unum == 4
				&& (*iter).second.unum != GetMyNumber()
				&& (*iter).second.head.distance != 0)
		{
			///   ///cout<<"QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ"<<endl;
			test = GetNewTeammateCoordinate((*iter).second.unum);
			/*		  if(newAverageTeammateCoordinate[(*iter).second.unum-1].z()==0)
			 {
			 for(int i=0;i<20;i++)
			 {
			 lastCyclesAverageTeammateCoordinate[(*iter).second.unum-1][i]=test;
			 }

			 newAverageTeammateCoordinate[(*iter).second.unum-1]=test;

			 }
			 else
			 {
			 if(fabs(test.x()-newAverageTeammateCoordinate[(*iter).second.unum-1].x())<0.5&&fabs(test.y()-newAverageTeammateCoordinate[(*iter).second.unum-1].y())<0.5)*/
			{
				lastCyclesAverageTeammateCoordinate[(*iter).second.unum - 1][point4
						% LAST_CYCLES_OF_LOCATE_TEAMMATE] = test;
				point4++;
			}
			middle = Vector3(0, 0, 0);
			for (int i = 0; i < LAST_CYCLES_OF_LOCATE_TEAMMATE; i++)
			{
				middle +=
						lastCyclesAverageTeammateCoordinate[(*iter).second.unum
								- 1][i];
				//  ///cout<<"lastCyclesAverageTeammateCoordinate["<<(*iter).second.unum<<"]["<<i<<"]:"<<lastCyclesAverageTeammateCoordinate[(*iter).second.unum-1][i]<<endl;
			}
			newAverageTeammateCoordinate[(*iter).second.unum - 1] = middle
					/ LAST_CYCLES_OF_LOCATE_TEAMMATE;
			///cout<<"newAverageTeammateCoordinate["<<(*iter).second.unum<<"]:"<<newAverageTeammateCoordinate[(*iter).second.unum-1]<<endl;
//		  }
		}
		else if ((*iter).second.unum == 5
				&& (*iter).second.unum != GetMyNumber()
				&& (*iter).second.head.distance != 0)
		{
			///   ///cout<<"QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ"<<endl;
			test = GetNewTeammateCoordinate((*iter).second.unum);
			/*		  if(newAverageTeammateCoordinate[(*iter).second.unum-1].z()==0)
			 {
			 for(int i=0;i<20;i++)
			 {
			 lastCyclesAverageTeammateCoordinate[(*iter).second.unum-1][i]=test;
			 }

			 newAverageTeammateCoordinate[(*iter).second.unum-1]=test;

			 }
			 else
			 {
			 if(fabs(test.x()-newAverageTeammateCoordinate[(*iter).second.unum-1].x())<0.5&&fabs(test.y()-newAverageTeammateCoordinate[(*iter).second.unum-1].y())<0.5)*/
			{
				lastCyclesAverageTeammateCoordinate[(*iter).second.unum - 1][point5
						% LAST_CYCLES_OF_LOCATE_TEAMMATE] = test;
				point5++;
			}
			middle = Vector3(0, 0, 0);
			for (int i = 0; i < LAST_CYCLES_OF_LOCATE_TEAMMATE; i++)
			{
				middle +=
						lastCyclesAverageTeammateCoordinate[(*iter).second.unum
								- 1][i];
				//  ///cout<<"lastCyclesAverageTeammateCoordinate["<<(*iter).second.unum<<"]["<<i<<"]:"<<lastCyclesAverageTeammateCoordinate[(*iter).second.unum-1][i]<<endl;
			}
			newAverageTeammateCoordinate[(*iter).second.unum - 1] = middle
					/ LAST_CYCLES_OF_LOCATE_TEAMMATE;
			///cout<<"newAverageTeammateCoordinate["<<(*iter).second.unum<<"]:"<<newAverageTeammateCoordinate[(*iter).second.unum-1]<<endl;
///		  }
		}
		else if ((*iter).second.unum == 6
				&& (*iter).second.unum != GetMyNumber()
				&& (*iter).second.head.distance != 0)
		{
			///   ///cout<<"QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ"<<endl;
			test = GetNewTeammateCoordinate((*iter).second.unum);
			/*		  if(newAverageTeammateCoordinate[(*iter).second.unum-1].z()==0)
			 {
			 for(int i=0;i<20;i++)
			 {
			 lastCyclesAverageTeammateCoordinate[(*iter).second.unum-1][i]=test;
			 }

			 newAverageTeammateCoordinate[(*iter).second.unum-1]=test;

			 }
			 else
			 {
			 if(fabs(test.x()-newAverageTeammateCoordinate[(*iter).second.unum-1].x())<0.5&&fabs(test.y()-newAverageTeammateCoordinate[(*iter).second.unum-1].y())<0.5)*/
			{
				lastCyclesAverageTeammateCoordinate[(*iter).second.unum - 1][point6
						% LAST_CYCLES_OF_LOCATE_TEAMMATE] = test;
				point6++;
			}
			middle = Vector3(0, 0, 0);
			for (int i = 0; i < LAST_CYCLES_OF_LOCATE_TEAMMATE; i++)
			{
				middle +=
						lastCyclesAverageTeammateCoordinate[(*iter).second.unum
								- 1][i];
				//	  ///cout<<"lastCyclesAverageTeammateCoordinate["<<(*iter).second.unum<<"]["<<i<<"]:"<<lastCyclesAverageTeammateCoordinate[(*iter).second.unum-1][i]<<endl;
			}
			newAverageTeammateCoordinate[(*iter).second.unum - 1] = middle
					/ LAST_CYCLES_OF_LOCATE_TEAMMATE;
			///cout<<"newAverageTeammateCoordinate["<<(*iter).second.unum<<"]:"<<newAverageTeammateCoordinate[(*iter).second.unum-1]<<endl;
///		  }
		}
		else if ((*iter).second.unum == 7
				&& (*iter).second.unum != GetMyNumber()
				&& (*iter).second.head.distance != 0)
		{
			///   ///cout<<"QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ"<<endl;
			test = GetNewTeammateCoordinate((*iter).second.unum);
			/*		  if(newAverageTeammateCoordinate[(*iter).second.unum-1].z()==0)
			 {
			 for(int i=0;i<20;i++)
			 {
			 lastCyclesAverageTeammateCoordinate[(*iter).second.unum-1][i]=test;
			 }

			 newAverageTeammateCoordinate[(*iter).second.unum-1]=test;

			 }
			 else
			 {
			 if(fabs(test.x()-newAverageTeammateCoordinate[(*iter).second.unum-1].x())<0.5&&fabs(test.y()-newAverageTeammateCoordinate[(*iter).second.unum-1].y())<0.5)*/
			{
				lastCyclesAverageTeammateCoordinate[(*iter).second.unum - 1][point7
						% LAST_CYCLES_OF_LOCATE_TEAMMATE] = test;
				point7++;
			}
			middle = Vector3(0, 0, 0);
			for (int i = 0; i < LAST_CYCLES_OF_LOCATE_TEAMMATE; i++)
			{
				middle +=
						lastCyclesAverageTeammateCoordinate[(*iter).second.unum
								- 1][i];
				//	  ///cout<<"lastCyclesAverageTeammateCoordinate["<<(*iter).second.unum<<"]["<<i<<"]:"<<lastCyclesAverageTeammateCoordinate[(*iter).second.unum-1][i]<<endl;
			}
			newAverageTeammateCoordinate[(*iter).second.unum - 1] = middle
					/ LAST_CYCLES_OF_LOCATE_TEAMMATE;
			///cout<<"newAverageTeammateCoordinate["<<(*iter).second.unum<<"]:"<<newAverageTeammateCoordinate[(*iter).second.unum-1]<<endl;
//		  }
		}
		else if ((*iter).second.unum == 8
				&& (*iter).second.unum != GetMyNumber()
				&& (*iter).second.head.distance != 0)
		{
			///   ///cout<<"QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ"<<endl;
			test = GetNewTeammateCoordinate((*iter).second.unum);
			/*		  if(newAverageTeammateCoordinate[(*iter).second.unum-1].z()==0)
			 {
			 for(int i=0;i<20;i++)
			 {
			 lastCyclesAverageTeammateCoordinate[(*iter).second.unum-1][i]=test;
			 }

			 newAverageTeammateCoordinate[(*iter).second.unum-1]=test;

			 }
			 else
			 {
			 if(fabs(test.x()-newAverageTeammateCoordinate[(*iter).second.unum-1].x())<0.5&&fabs(test.y()-newAverageTeammateCoordinate[(*iter).second.unum-1].y())<0.5)*/
			{
				lastCyclesAverageTeammateCoordinate[(*iter).second.unum - 1][point8
						% LAST_CYCLES_OF_LOCATE_TEAMMATE] = test;
				point8++;
			}
			middle = Vector3(0, 0, 0);
			for (int i = 0; i < LAST_CYCLES_OF_LOCATE_TEAMMATE; i++)
			{
				middle +=
						lastCyclesAverageTeammateCoordinate[(*iter).second.unum
								- 1][i];
				//	  ///cout<<"lastCyclesAverageTeammateCoordinate["<<(*iter).second.unum<<"]["<<i<<"]:"<<lastCyclesAverageTeammateCoordinate[(*iter).second.unum-1][i]<<endl;
			}
			newAverageTeammateCoordinate[(*iter).second.unum - 1] = middle
					/ LAST_CYCLES_OF_LOCATE_TEAMMATE;
			///cout<<"newAverageTeammateCoordinate["<<(*iter).second.unum<<"]:"<<newAverageTeammateCoordinate[(*iter).second.unum-1]<<endl;
///		  }
		}
		else if ((*iter).second.unum == 9
				&& (*iter).second.unum != GetMyNumber()
				&& (*iter).second.head.distance != 0)
		{
			///   ///cout<<"QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ"<<endl;
			test = GetNewTeammateCoordinate((*iter).second.unum);
			/*		  if(newAverageTeammateCoordinate[(*iter).second.unum-1].z()==0)
			 {
			 for(int i=0;i<20;i++)
			 {
			 lastCyclesAverageTeammateCoordinate[(*iter).second.unum-1][i]=test;
			 }

			 newAverageTeammateCoordinate[(*iter).second.unum-1]=test;

			 }
			 else
			 {
			 if(fabs(test.x()-newAverageTeammateCoordinate[(*iter).second.unum-1].x())<0.5&&fabs(test.y()-newAverageTeammateCoordinate[(*iter).second.unum-1].y())<0.5)*/
			{
				lastCyclesAverageTeammateCoordinate[(*iter).second.unum - 1][point9
						% LAST_CYCLES_OF_LOCATE_TEAMMATE] = test;
				point9++;
			}
			middle = Vector3(0, 0, 0);
			for (int i = 0; i < LAST_CYCLES_OF_LOCATE_TEAMMATE; i++)
			{
				middle +=
						lastCyclesAverageTeammateCoordinate[(*iter).second.unum
								- 1][i];
				//	  ///cout<<"lastCyclesAverageTeammateCoordinate["<<(*iter).second.unum<<"]["<<i<<"]:"<<lastCyclesAverageTeammateCoordinate[(*iter).second.unum-1][i]<<endl;
			}
			newAverageTeammateCoordinate[(*iter).second.unum - 1] = middle
					/ LAST_CYCLES_OF_LOCATE_TEAMMATE;
			///cout<<"newAverageTeammateCoordinate["<<(*iter).second.unum<<"]:"<<newAverageTeammateCoordinate[(*iter).second.unum-1]<<endl;
//		  }
		}

	}

}

void WorldModel::updateLastCyclesAverageOpponentCoordinate()
{

}

Vector3 WorldModel::GetNewTeammateCoordinate(int num)
{
	return newTeammateCoordinate[num - 1];
}

Vector3 WorldModel::GetNewOpponentCoordinate(int num)
{
	return newOpponentCoordinate[num - 1];
}

Vector3 WorldModel::GetNewAverageTeammateCoordinate(int num)
{
	//cout<<"newTeammateCoordinate num::"<<num<<"::"<<newTeammateCoordinate[num - 1]<<endl;
	//cout<<"newAverageTeammateCoordinate num::"<<num<<"::"<<newAverageTeammateCoordinate[num - 1]<<endl;
	return newAverageTeammateCoordinate[num - 1];
}

Vector3 WorldModel::GetNewAverageOpponentCoordinate(int num)
{
	return newAverageOpponentCoordinate[num - 1];
}

int WorldModel::GetPositionANumber()
{
	return positionANumber;
}

int WorldModel::GetPositionBNumber()
{
	return positionBNumber;
}

int WorldModel::GetPositionCNumber()
{
	return positionCNumber;
}

int WorldModel::GetPositionDNumber()
{
	return positionDNumber;
}
int WorldModel::GetPositionENumber()
{
	return positionENumber;
}
bool WorldModel::IsFallingDown_test()
{
	/////cout<<"IsFallingDown_test!!!"<<endl;
	if (fabs(QuFRP_Z->AvrageQueue()) < 5 && messageParser.GetACC().z < 4)
	{
		/////cout<<"falling down!!!"<<endl;
		/////////cout<<"i stand on the ground,but i do not know!!!"<<endl;
		if (QuFRP_Z->AvrageQueue() > 0)
		{
			fallDirection = D_BACK;
			return true;
		}
		else
		{
			fallDirection = D_FORWARD;
			return true;
		}
	}

	if (QuFront_back->AvrageQueue() > 72
			|| fabs(QuSideLeft_right->AvrageQueue()) > 85
			|| QuFront_back->AvrageQueue() < -80)
	{
		/////cout<<"falling down QuFront_back"<<endl;

		if ((fabs(QuFront_back->AvrageQueue())
				> fabs(QuSideLeft_right->AvrageQueue()))
				&& (QuFront_back->AvrageQueue() < 0))
		{
			if (QuSideLeft_right->AvrageQueue() < -50)
			{
				/////////cout<<"falling down!!!! eve GYR X:"<<QuFront_back->AvrageQueue()<<"	eve GYR Y:"<<QuSideLeft_right->AvrageQueue()<<endl;
				fallDirection = D_LEFT;
				return true;
			}
			else if (QuSideLeft_right->AvrageQueue() > 50)
			{
				/////////cout<<"falling down!!!! eve GYR X:"<<QuFront_back->AvrageQueue()<<"	eve GYR Y:"<<QuSideLeft_right->AvrageQueue()<<endl;
				fallDirection = D_RIGHT;
				return true;
			}
			else
			{
				fallDirection = D_FORWARD;
				return true;
			}
		}
		else if ((fabs(QuFront_back->AvrageQueue())
				> fabs(QuSideLeft_right->AvrageQueue()))
				&& (QuFront_back->AvrageQueue() > 0))
		{
			if (QuSideLeft_right->AvrageQueue() < -35)
			{
				/////////cout<<"falling down!!!! eve GYR X:"<<QuFront_back->AvrageQueue()<<"	eve GYR Y:"<<QuSideLeft_right->AvrageQueue()<<endl;
				fallDirection = D_LEFT;
				return true;
			}
			else if (QuSideLeft_right->AvrageQueue() > 35)
			{
				/////////cout<<"falling down!!!! eve GYR X:"<<QuFront_back->AvrageQueue()<<"	eve GYR Y:"<<QuSideLeft_right->AvrageQueue()<<endl;
				fallDirection = D_RIGHT;
				return true;
			}
			else
			{
				fallDirection = D_BACK;
				return true;
			}
		}
		else if ((fabs(QuFront_back->AvrageQueue())
				< fabs(QuSideLeft_right->AvrageQueue()))
				&& QuSideLeft_right->AvrageQueue() > 0)
		{
			/////////cout<<"falling down!!!! eve GYR X:"<<QuFront_back->AvrageQueue()<<"	eve GYR Y:"<<QuSideLeft_right->AvrageQueue()<<endl;
			fallDirection = D_RIGHT;
			return true;
		}
		else if ((fabs(QuFront_back->AvrageQueue())
				< fabs(QuSideLeft_right->AvrageQueue()))
				&& QuSideLeft_right->AvrageQueue() < 0)
		{
			/////////cout<<"falling down!!!! eve GYR X:"<<QuFront_back->AvrageQueue()<<"	eve GYR Y:"<<QuSideLeft_right->AvrageQueue()<<endl;
			fallDirection = D_LEFT;
			return true;
		}
	}
	//return false;
	else
	{
		fallDirection = D_NONE;
		return false;
	}
	return false;
}
bool WorldModel::whetherStandedUp()
{
	/////////cout<<"whetherStandedUp!!!"<<endl;
	if (fabs(QuFRP_Z->AvrageQueue()) < 15)
	{
		if (messageParser.GetACC().y < 0)
		{
			fallDirection = D_FORWARD;
			/////cout<<"fall failed fall forward!!!"<<endl;
		}
		else
		{
			fallDirection = D_BACK;
			/////cout<<"fall failed fall back!!!"<<endl;

		}
		return false;
	}
	else
	{
		QuFront_back->Clean();
		QuSideLeft_right->Clean();
		//	///cout<<"stand up!!!"<<endl;
		return true;
	}
}

bool WorldModel::IsFallDown_test()
{
	/////cout<<"Is Fall Down_test() :"<<(fabs(QuFront_back->AvrageQueue())+fabs(QuSideLeft_right->AvrageQueue()))<<endl;
	if (fabs(QuFront_back->AvrageQueue())
			+ fabs(QuSideLeft_right->AvrageQueue()) < 70)
	{
		if (QuFRP_Y->AvrageQueue() < 0)
		{
			fallDirection = D_FORWARD;
		}
		else
		{
			fallDirection = D_BACK;
		}
		return true;
	}
	else
		return false;
///this part means the down rate is lowwer than 30,means it has completely fall down
}

void WorldModel::UpdatePlayerHeadHigh() //VisionObject player)
{
	for (TPlayerSenseMap::iterator iter =
			messageParser.mOpponentSenseMap.begin();
			iter != messageParser.mOpponentSenseMap.end(); ++iter)
			{
		if ((*iter).second.head.distance != 0)
		{
			float dis3 =
					fabs(
							(*iter).second.rFoot.distance
									* sin(
											fabs(
													-messageParser.mHingeJointSenseMap[JID_HEAD_2].angle
															- (*iter).second.rFoot.phi)
													* PI / 180)
									- (*iter).second.head.distance
											* sin(
													fabs(
															-messageParser.mHingeJointSenseMap[JID_HEAD_2].angle
																	- (*iter).second.head.phi)
															* PI / 180));
			playerHeadHigh[(*iter).first].removedQueue(dis3);
		}
		else
		{
			if (playerHeadHigh[(*iter).first].AvrageQueue() != 0.45)
				playerHeadHigh[(*iter).first].removedQueue(0.45);
		}
	}

	for (TPlayerSenseMap::iterator iter1 =
			messageParser.mTeamMateSenseMap.begin();
			iter1 != messageParser.mTeamMateSenseMap.end(); ++iter1)
			{
		if ((*iter1).second.head.distance != 0)
		{
			float dis3 =
					fabs(
							(*iter1).second.rFoot.distance
									* sin(
											fabs(
													-messageParser.mHingeJointSenseMap[JID_HEAD_2].angle
															- (*iter1).second.rFoot.phi)
													* PI / 180)
									- (*iter1).second.head.distance
											* sin(
													fabs(
															-messageParser.mHingeJointSenseMap[JID_HEAD_2].angle
																	- (*iter1).second.head.phi)
															* PI / 180));
			playerHeadHigh[(*iter1).first].removedQueue(dis3);
		}
		else
		{
			if (playerHeadHigh[(*iter1).first].AvrageQueue() != 0.45)
				playerHeadHigh[(*iter1).first].removedQueue(0.45);
		}
	}
}

bool WorldModel::PlayerWhetherFallDown(VisionObject player) ///whether the player fall down
{
	if (playerHeadHigh[player].AvrageQueue() < 0.1)
	{
		return true;
	}
	else
	{
		return false;
	}
}

float WorldModel::GetDistanceBetweenTwoCoordinate(Vector3 A, Vector3 B)
{
	float dis;
	dis = sqrt(
			(A.x() - B.x()) * (A.x() - B.x())
					+ (A.y() - B.y()) * (A.y() - B.y()));
	return dis;
}

bool WorldModel::WhetherCanPassFront()
{
	bool res = true;
	float myDisToOpponent, myAngleToOpponent, distance;
	float myAngleToBall = GetMyAngleToBall(), myDistanceToBall =
			GetMyDistanceToBall();
	float angle;
	for (TPlayerSenseMap::iterator iter =
			messageParser.mOpponentSenseMap.begin();
			iter != messageParser.mOpponentSenseMap.end(); ++iter)
			{

		myDisToOpponent = (*iter).second.head.distance;
		myAngleToOpponent = (*iter).second.head.theta;
		if (myAngleToOpponent != 0)
		{
			if ((myAngleToBall * myAngleToOpponent) < 0)
			{
				angle = fabs(myAngleToBall) + fabs(myAngleToOpponent);

			}
			else
			{
				angle = fabs(myAngleToBall - myAngleToOpponent);

			}

			distance = sqrt(
					myDistanceToBall * myDistanceToBall
							+ myDisToOpponent * myDisToOpponent
							- cos(angle * PI / 180) * 2 * myDistanceToBall
									* myDisToOpponent);

			///cout<<"inside WhetherCanPassFront:"<<endl;

			///cout<<"opponentnum:"<<(*iter).second.unum<<endl;
			///cout<<"disToball:"<<distance<<endl;
			///cout<<"myAngleToOpponent:"<<myAngleToOpponent<<endl;

			if (distance < 1 * CELL_LENGTH && fabs(myAngleToOpponent) < 20)
			{
				///cout<<"opponentnum:"<<(*iter).second.unum<<endl;
				///cout<<"disToball:"<<distance<<endl;
				///cout<<"myAngleToOpponent:"<<myAngleToOpponent<<endl;
				res = false;
			}
			else if (distance >= 1 * CELL_LENGTH && distance < 2 * CELL_LENGTH
					&& fabs(myAngleToOpponent) < 10)
			{
				///cout<<"opponentnum:"<<(*iter).second.unum<<endl;
				///cout<<"disToball:"<<distance<<endl;
				///cout<<"myAngleToOpponent:"<<myAngleToOpponent<<endl;
				res = false;
			}
// 		else if(distance>=2*CELL_LENGTH&&distance<3*CELL_LENGTH&&fabs(myAngleToOpponent)<10)
// 		{
// 		      ///cout<<"opponentnum:"<<(*iter).second.unum<<endl;
// 		///cout<<"disToball:"<<distance<<endl;
// 		///cout<<"myAngleToOpponent:"<<myAngleToOpponent<<endl;
// 			res=false;
// 		}
		}
	}
	return res;
}

void WorldModel::updateClosestToBallTeammateNumberAndDistanceByVision()
{
///	int number;
///	float dis=40;
	closestToBallTeammateNumberByVision = 0;
	closestToBallTeammateDistanceByVision = 40;
	float myDisToTeammate, myAngleToTeammate, distance;
	float myAngleToBall = GetMyAngleToBall(), myDistanceToBall =
			GetMyDistanceToBall();
	float angle;
	for (TPlayerSenseMap::iterator iter =
			messageParser.mTeamMateSenseMap.begin();
			iter != messageParser.mTeamMateSenseMap.end(); ++iter)
			{

		myDisToTeammate = (*iter).second.head.distance;
		myAngleToTeammate = (*iter).second.head.theta;
		if (myAngleToTeammate != 0)
		{
			if ((myAngleToBall * myAngleToTeammate) < 0)
			{
				angle = fabs(myAngleToBall) + fabs(myAngleToTeammate);
				///cout<<"myAngleToBall:"<<myAngleToBall<<endl;
				///cout<<"myAngleToTeammate:"<<myAngleToTeammate<<endl;
				///cout<<"angle1:"<<angle<<endl;
			}
			else
			{
				angle = fabs(myAngleToBall - myAngleToTeammate);
				///cout<<"myAngleToBall:"<<myAngleToBall<<endl;
				///cout<<"myAngleToTeammate:"<<myAngleToTeammate<<endl;
				///cout<<"angle2:"<<angle<<endl;
			}
			///cout<<"myDistanceToBall:"<<myDistanceToBall<<endl;
			///cout<<"myDisToTeammate:"<<myDisToTeammate<<endl;
			distance = sqrt(
					myDistanceToBall * myDistanceToBall
							+ myDisToTeammate * myDisToTeammate
							- cos(angle * PI / 180) * 2 * myDistanceToBall
									* myDisToTeammate);
			///cout<<"Teammate number:"<<(*iter).second.unum<<"distance to ball:"<<distance<<endl;
			if (distance < closestToBallTeammateDistanceByVision)
			{
				closestToBallTeammateNumberByVision = (*iter).second.unum;
				closestToBallTeammateDistanceByVision = distance;
			}
		}
	}
	/////cout<<"I see Vanguard number:"<<vanguardNumberByVision<<endl;
///	return vanguardNumberByVision;
}

int WorldModel::GetClosestToBallTeammateNumberByVision()
{
	closestToBallTeammateNumberByVision = 0;
	closestToBallTeammateDistanceByVision = 40;
	float myDisToTeammate, myAngleToTeammate, distance;
	float myAngleToBall = GetMyAngleToBall(), myDistanceToBall =
			GetMyDistanceToBall();
	float angle;
	for (TPlayerSenseMap::iterator iter =
			messageParser.mTeamMateSenseMap.begin();
			iter != messageParser.mTeamMateSenseMap.end(); ++iter)
			{

		myDisToTeammate = (*iter).second.head.distance;
		myAngleToTeammate = (*iter).second.head.theta;
		if (myAngleToTeammate != 0)
		{
			if ((myAngleToBall * myAngleToTeammate) < 0)
			{
				angle = fabs(myAngleToBall) + fabs(myAngleToTeammate);
//			///cout<<"myAngleToBall:"<<myAngleToBall<<endl;
//			///cout<<"myAngleToTeammate:"<<myAngleToTeammate<<endl;
//			///cout<<"angle1:"<<angle<<endl;
			}
			else
			{
				angle = fabs(myAngleToBall - myAngleToTeammate);
//			///cout<<"myAngleToBall:"<<myAngleToBall<<endl;
//			///cout<<"myAngleToTeammate:"<<myAngleToTeammate<<endl;
//			///cout<<"angle2:"<<angle<<endl;
			}
//		///cout<<"myDistanceToBall:"<<myDistanceToBall<<endl;
//		///cout<<"myDisToTeammate:"<<myDisToTeammate<<endl;
			distance = sqrt(
					myDistanceToBall * myDistanceToBall
							+ myDisToTeammate * myDisToTeammate
							- cos(angle * PI / 180) * 2 * myDistanceToBall
									* myDisToTeammate);
//		///cout<<"Teammate number:"<<(*iter).second.unum<<"distance to ball:"<<distance<<endl;
			if (distance < closestToBallTeammateDistanceByVision)
			{
				closestToBallTeammateNumberByVision = (*iter).second.unum;
				closestToBallTeammateDistanceByVision = distance;
			}
		}
	}
	return closestToBallTeammateNumberByVision;
}

float WorldModel::GetClosestToBallTeammateDistanceByVision()
{
	closestToBallTeammateNumberByVision = 0;
	closestToBallTeammateDistanceByVision = 40;
	float myDisToTeammate, myAngleToTeammate, distance;
	float myAngleToBall = GetMyAngleToBall(), myDistanceToBall =
			GetMyDistanceToBall();
	float angle;
	for (TPlayerSenseMap::iterator iter =
			messageParser.mTeamMateSenseMap.begin();
			iter != messageParser.mTeamMateSenseMap.end(); ++iter)
			{

		myDisToTeammate = (*iter).second.head.distance;
		myAngleToTeammate = (*iter).second.head.theta;
		if (myAngleToTeammate != 0)
		{
			if ((myAngleToBall * myAngleToTeammate) < 0)
			{
				angle = fabs(myAngleToBall) + fabs(myAngleToTeammate);
//			///cout<<"myAngleToBall:"<<myAngleToBall<<endl;
//			///cout<<"myAngleToTeammate:"<<myAngleToTeammate<<endl;
//			///cout<<"angle1:"<<angle<<endl;
			}
			else
			{
				angle = fabs(myAngleToBall - myAngleToTeammate);
//			///cout<<"myAngleToBall:"<<myAngleToBall<<endl;
//			///cout<<"myAngleToTeammate:"<<myAngleToTeammate<<endl;
//			///cout<<"angle2:"<<angle<<endl;
			}
//		///cout<<"myDistanceToBall:"<<myDistanceToBall<<endl;
//		///cout<<"myDisToTeammate:"<<myDisToTeammate<<endl;
			distance = sqrt(
					myDistanceToBall * myDistanceToBall
							+ myDisToTeammate * myDisToTeammate
							- cos(angle * PI / 180) * 2 * myDistanceToBall
									* myDisToTeammate);
//		///cout<<"Teammate number:"<<(*iter).second.unum<<"distance to ball:"<<distance<<endl;
			if (distance < closestToBallTeammateDistanceByVision)
			{
				closestToBallTeammateNumberByVision = (*iter).second.unum;
				closestToBallTeammateDistanceByVision = distance;
			}
		}
	}
	return closestToBallTeammateDistanceByVision;
}

void WorldModel::updateLastCyclesAverageAngleToBall()
{
	static int point = 0;
	float total = 0;
	if (CanSeeTheBall())
	{
		lastCyclesAverageAngleToBallArray[point % 15] = GetMyAngleToBall();
	}
	else if (!CanSeeTheBall())
	{
		for (int i = 0; i < 15; i++)
		{
			lastCyclesAverageAngleToBallArray[i] = 0;
		}
	}

	for (int i = 0; i < 15; i++)
	{
		total += lastCyclesAverageAngleToBallArray[i];
	}
	lastCyclesAverageAngleToBall = total / 15;
	point++;
}

float WorldModel::GetLastCyclesAverageAngleToBall()
{
	return lastCyclesAverageAngleToBall;
}

#if 1
Vector3 WorldModel::GetPositionCoordinateForAttack(Position p)
{
	Vector3 destination;

	/// Vector3 ball=GetTheBallStopCoordinate();

	/// Vector3 ball=GetLastCyclesAverageBallCoordinateForRunFormation();

	if (CanSeeTheBall())
	{
		if (GetCurrentGameMode() != PM_CORNER_KICK_Our
				&& GetCurrentGameMode() != PM_GOAL_KICK_Opp)
		{
			if (ball.x() > -5* CELL_LENGTH && ball.x() < 6* CELL_LENGTH)
			{
				///cout<<"middle"<<endl;
				if (p == Position_A)
				{
					///cout<<"A"<<endl;
					if (ball.y() > 4 * CELL_LENGTH)
					{
						///cout<<"1"<<endl;
						destination = Vector3(ball.x() - 2 * FORMCELL_LENGTH
								,5 * FORMCELL_LENGTH,0);
					}
					else if (ball.y() < -4 * CELL_LENGTH)
					{
						///cout<<"2"<<endl;
						destination = Vector3(ball.x() - 2 * FORMCELL_LENGTH
								,-3 * FORMCELL_LENGTH,0);
					}
					else
					{
						///cout<<"3"<<endl;
						if (ball.y() >= 0)
						{
							destination = Vector3(ball.x() - 1 * FORMCELL_LENGTH
									,ball.y() + 0 * FORMCELL_LENGTH,0);

							if (GetClosestToBallOpponentDistanceByVision()
									< 0.4 * FORMCELL_LENGTH)
							{
								///cout<<"GetClosestToBallOpponentDistanceByVision()<0.4*CELL_LENGTH:A"<<endl;
								destination = Vector3(ball.x() - 1 * FORMCELL_LENGTH
										,ball.y() + 0 * FORMCELL_LENGTH,0);
							}

						}
						else
						{
							destination = Vector3(ball.x() - 2 * FORMCELL_LENGTH
									,ball.y() + FORMCELL_LENGTH,0);

							if (GetClosestToBallOpponentDistanceByVision()
									< 0.4 * FORMCELL_LENGTH)
							{
								///cout<<"GetClosestToBallOpponentDistanceByVision()<0.4*CELL_LENGTH:B"<<endl;
								destination = Vector3(
										ball.x() - 2.5 * FORMCELL_LENGTH
										,ball.y() + 0 * FORMCELL_LENGTH,0);
							}

						}

					}
				}
				else if (p == Position_B)
				{
					///cout<<"B"<<endl;
					if (ball.y() > 4 * CELL_LENGTH)
					{
						///cout<<"1"<<endl;
						destination = Vector3(ball.x() - 2 * FORMCELL_LENGTH
								,3 * FORMCELL_LENGTH,0);
					}
					else if (ball.y() < -4 * CELL_LENGTH)
					{
						///cout<<"2"<<endl;
						destination = Vector3(ball.x() - 2 * FORMCELL_LENGTH
								,-5 * FORMCELL_LENGTH,0);
					}
					else
					{
						///cout<<"3"<<endl;
						if (ball.y() >= 0)
						{
							destination = Vector3(ball.x() - 2 * FORMCELL_LENGTH
									,ball.y() - FORMCELL_LENGTH,0);

							if (GetClosestToBallOpponentDistanceByVision()
									< 0.4 * FORMCELL_LENGTH)
							{
								///cout<<"GetClosestToBallOpponentDistanceByVision()<0.4*CELL_LENGTH:C"<<endl;
								destination = Vector3(
										ball.x() - 2.5 * FORMCELL_LENGTH
										,ball.y() + 0 * FORMCELL_LENGTH,0);
							}

						}
						else
						{
							destination = Vector3(ball.x() - 1 * FORMCELL_LENGTH
									,ball.y() - 0 * FORMCELL_LENGTH,0);

							if (GetClosestToBallOpponentDistanceByVision()
									< 0.4 * FORMCELL_LENGTH)
							{
								///cout<<"GetClosestToBallOpponentDistanceByVision()<0.4*CELL_LENGTH:D"<<endl;
								destination = Vector3(ball.x() - 1 * FORMCELL_LENGTH
										,ball.y() + 0 * FORMCELL_LENGTH,0);
							}

						}
					}
				}
				else if (p == Position_C)
				{
					///cout<<"C"<<endl;
					if (ball.y() > 3.5 * CELL_LENGTH)
					{
						///cout<<"1"<<endl;
						destination = Vector3(ball.x() + 2 * FORMCELL_LENGTH
								,1 * FORMCELL_LENGTH,0);
					}
					else if (ball.y() < -3.5 * CELL_LENGTH)
					{
						///cout<<"2"<<endl;
						destination = Vector3(ball.x() + 1 * FORMCELL_LENGTH
								,-5 * FORMCELL_LENGTH,0);
					}
					else
					{
						///cout<<"3"<<endl;
						if (ball.y() >= 0)
						{
							destination = Vector3(ball.x() + 2 * FORMCELL_LENGTH
									,ball.y() - 2 * FORMCELL_LENGTH,0);
						}
						else
						{
							destination = Vector3(ball.x() + 1 * FORMCELL_LENGTH
									,ball.y() - 2 * FORMCELL_LENGTH,0);
						}
					}
				}
				else if (p == Position_D)
				{
					///cout<<"D"<<endl;
					if (ball.y() > 3.5 * CELL_LENGTH)
					{
						///cout<<"1"<<endl;
						destination = Vector3(ball.x() + 1 * FORMCELL_LENGTH
								,5 * FORMCELL_LENGTH,0);
					}
					else if (ball.y() < -3.5 * CELL_LENGTH)
					{
						///cout<<"2"<<endl;
						destination = Vector3(ball.x() + 2 * FORMCELL_LENGTH
								,-1 * FORMCELL_LENGTH,0);
					}
					else
					{
						///cout<<"3"<<endl;
						if (ball.y() >= 0)
						{
							destination = Vector3(ball.x() + 1 * FORMCELL_LENGTH
									,ball.y() + 2 * FORMCELL_LENGTH,0);
						}
						else
						{
							destination = Vector3(ball.x() + 2 * FORMCELL_LENGTH
									,ball.y() + 2 * FORMCELL_LENGTH,0);
						}
					}
				}
				else
				{
					///cout<<"4"<<endl;
					destination = myCoordinate;
				}
			}
			else if (ball.x() >= 6 * CELL_LENGTH)
			{
				///cout<<"Forward"<<endl;
				if (p == Position_A)
				{
					///cout<<"A"<<endl;
					if (ball.y() > 4 * CELL_LENGTH)
					{
						///cout<<"1"<<endl;
						destination = Vector3(ball.x() - 2 * FORMCELL_LENGTH
								,5 * CELL_LENGTH,0);
					}
					else if (ball.y() < -4 * CELL_LENGTH)
					{
						///cout<<"2"<<endl;
						destination = Vector3(ball.x() - 2 * FORMCELL_LENGTH
								,-3 * CELL_LENGTH,0);
					}
					else
					{
						///cout<<"3"<<endl;
						if (ball.y() >= 0)
						{
							destination = Vector3(ball.x() - 1.2 * FORMCELL_LENGTH
									,ball.y() + 0.5 * CELL_LENGTH,0);
						}
						else if (ball.y() < 0)
						{
							destination = Vector3(ball.x() - 2 * FORMCELL_LENGTH
									,ball.y() + CELL_LENGTH,0);
						}
					}
				}
				else if (p == Position_B)
				{
					///cout<<"B"<<endl;
					if (ball.y() > 4 * CELL_LENGTH)
					{
						///cout<<"1"<<endl;
						destination = Vector3(ball.x() - 2 * FORMCELL_LENGTH
								,3 * CELL_LENGTH,0);
					}
					else if (ball.y() < -4 * CELL_LENGTH)
					{
						///cout<<"2"<<endl;
						destination = Vector3(ball.x() - 2 * FORMCELL_LENGTH
								,-5 * CELL_LENGTH,0);
					}
					else
					{
						///cout<<"3"<<endl;
						if (ball.y() >= 0)
						{
							destination = Vector3(ball.x() - 2 * FORMCELL_LENGTH
									,ball.y() - CELL_LENGTH,0);
						}
						else if (ball.y() < 0)
						{
							destination = Vector3(ball.x() - 1.2 * FORMCELL_LENGTH
									,ball.y() - 0.5 * CELL_LENGTH,0);
						}
					}
				}
				else if (p == Position_C)
				{
					///cout<<"C"<<endl;
					if (ball.y() > 3 * CELL_LENGTH)
					{
						///cout<<"1"<<endl;
						destination = Vector3(7 * CELL_LENGTH,0 * CELL_LENGTH
								,0);
					}
					else if (ball.y() < -3 * CELL_LENGTH)
					{
						///cout<<"2"<<endl;
						destination = Vector3(7 * CELL_LENGTH,-4 * CELL_LENGTH
								,0);
					}
					else
					{
						///cout<<"3"<<endl;
						destination = Vector3(7 * CELL_LENGTH
								,ball.y() - 2 * FORMCELL_LENGTH,0);
					}
					///	  destination=Vector3(ball.x()+2*CELL_LENGTH,ball.y()-2*CELL_LENGTH,0);

				}
				else if (p == Position_D)
				{
					///cout<<"D"<<endl;
					if (ball.y() > 3 * CELL_LENGTH)
					{
						///cout<<"1"<<endl;
						destination = Vector3(7 * CELL_LENGTH,4 * CELL_LENGTH
								,0);
					}
					else if (ball.y() < -3 * CELL_LENGTH)
					{
						///cout<<"2"<<endl;
						destination = Vector3(7 * CELL_LENGTH,0 * CELL_LENGTH
								,0);
					}
					else
					{
						///cout<<"3"<<endl;
						destination = Vector3(7 * CELL_LENGTH
								,ball.y() + 2 * FORMCELL_LENGTH,0);
					}
					///	  destination=Vector3(ball.x()+2*CELL_LENGTH,ball.y()+2*CELL_LENGTH,0);

				}

				else
				{
					///cout<<"4"<<endl;
					destination = myCoordinate;
				}

				if (ball.x() >= 7 * CELL_LENGTH)
				{
					if (p == Position_A)
					{
						///cout<<"A"<<endl;
						if (ball.y() > 3 * CELL_LENGTH)
						{
							///cout<<"1"<<endl;
							destination = Vector3(6 * CELL_LENGTH
									,4 * CELL_LENGTH,0);
						}
						else if (ball.y() < -3 * CELL_LENGTH)
						{
							///cout<<"2"<<endl;
							destination = Vector3(6.5 * CELL_LENGTH
									,-2 * CELL_LENGTH,0);
						}
						else
						{
							///cout<<"3"<<endl;
							destination = Vector3(6.5 * CELL_LENGTH
									,ball.y() + FORMCELL_LENGTH,0);
						}
					}
					else if (p == Position_B)
					{
						///cout<<"B"<<endl;
						if (ball.y() > 3 * CELL_LENGTH)
						{
							///cout<<"1"<<endl;
							destination = Vector3(6 * CELL_LENGTH
									,2 * CELL_LENGTH,0);
						}
						else if (ball.y() < -3 * CELL_LENGTH)
						{
							///cout<<"2"<<endl;
							destination = Vector3(6.5 * CELL_LENGTH
									,-4 * CELL_LENGTH,0);
						}
						else
						{
							///cout<<"3"<<endl;
							destination = Vector3(6 * CELL_LENGTH
									,ball.y() - FORMCELL_LENGTH,0);
						}
					}
					else if (p == Position_C)
					{
						///cout<<"C"<<endl;
						if (ball.y() > 3 * CELL_LENGTH)
						{
							///cout<<"1"<<endl;
							destination = Vector3(8 * CELL_LENGTH
									,0 * CELL_LENGTH,0);
						}
						else if (ball.y() < -3 * CELL_LENGTH)
						{
							///cout<<"2"<<endl;
							destination = Vector3(8 * CELL_LENGTH
									,-4 * CELL_LENGTH,0);
						}
						else
						{
							///cout<<"3"<<endl;
							destination = Vector3(8 * CELL_LENGTH
									,ball.y() - 1.5 * FORMCELL_LENGTH,0);
						}

						if (GetCurrentGameMode() == PM_PlayOn
								&& fabs(ball.y()) < 2 * CELL_LENGTH)
						{
							///cout<<"4"<<endl;
							destination = Vector3(ball.x() - 1.2 * FORMCELL_LENGTH
									,ball.y() - 1.3 * FORMCELL_LENGTH,0);
						}

						///	  destination=Vector3(ball.x()+2*CELL_LENGTH,ball.y()-2*CELL_LENGTH,0);

					}
					else if (p == Position_D)
					{
						///cout<<"D"<<endl;
						if (ball.y() > 3 * CELL_LENGTH)
						{
							///cout<<"1"<<endl;
							destination = Vector3(8 * CELL_LENGTH
									,4 * CELL_LENGTH,0);
						}
						else if (ball.y() < -3 * CELL_LENGTH)
						{
							///cout<<"2"<<endl;
							destination = Vector3(8* CELL_LENGTH
									,0 * CELL_LENGTH,0);
						}
						else
						{
							///cout<<"3"<<endl;
							destination = Vector3(8 * CELL_LENGTH
									,ball.y() + 1.5 * FORMCELL_LENGTH,0);
						}

						if (GetCurrentGameMode() == PM_PlayOn
								&& fabs(ball.y()) < 2 * CELL_LENGTH)
						{
							///cout<<"4"<<endl;
							destination = Vector3(ball.x() - 1.2 * FORMCELL_LENGTH
									,ball.y() + 1.3 * FORMCELL_LENGTH,0);

						}
						///	  destination=Vector3(ball.x()+2*CELL_LENGTH,ball.y()+2*CELL_LENGTH,0);

					}
					else
					{
						///cout<<"4"<<endl;
						destination = myCoordinate;
					}

				}

			}
			else if (ball.x() <= -5 * CELL_LENGTH)
			{
				///cout<<"BackWard"<<endl;
				if (p == Position_A)
				{
					///cout<<"A"<<endl;
					if (ball.y() > 2 * CELL_LENGTH)
					{
						///cout<<"1"<<endl;
						destination = Vector3(-6 * CELL_LENGTH,3 * CELL_LENGTH
								,0);
					}
					else if (ball.y() < -2 * CELL_LENGTH)
					{
						destination = Vector3(-6 * CELL_LENGTH,-1 * CELL_LENGTH
								,0);
					}
					else
					{
						if (ball.y() >= 0)
						{
							destination = Vector3(-6 * CELL_LENGTH
									,ball.y() + 0 * FORMCELL_LENGTH,0);
						}
						else if (ball.y() < 0)
						{
							destination = Vector3(-6 * CELL_LENGTH
									,ball.y() + 1 * FORMCELL_LENGTH,0);
						}
					}
					/*
					 if(ball.x()<=-7*CELL_LENGTH)
					 {
					 if(ball.y()>1*CELL_LENGTH)
					 {
					 ///cout<<"1"<<endl;
					 destination=Vector3(-8.8*CELL_LENGTH,1.5*CELL_LENGTH,0);
					 }
					 else if(ball.y()<-1*CELL_LENGTH)
					 {
					 destination=Vector3(-8.8*CELL_LENGTH,0*CELL_LENGTH,0);
					 }
					 else
					 {
					 destination=Vector3(-8.8*CELL_LENGTH,ball.y()+1*CELL_LENGTH,0);
					 }
					 }*/
				}
				else if (p == Position_B)
				{
					///cout<<"B"<<endl;
					if (ball.y() > 2 * CELL_LENGTH)
					{
						///cout<<"1"<<endl;
						destination = Vector3(-6 * CELL_LENGTH,1 * CELL_LENGTH
								,0);
					}
					else if (ball.y() < -2 * CELL_LENGTH)
					{
						destination = Vector3(-6 * CELL_LENGTH,-3 * CELL_LENGTH
								,0);
					}
					else
					{
						if (ball.y() >= 0)
						{
							destination = Vector3(-6 * CELL_LENGTH
									,ball.y() - 1 * FORMCELL_LENGTH,0);
						}
						else if (ball.y() < 0)
						{
							destination = Vector3(-6 * CELL_LENGTH
									,ball.y() - 0 * FORMCELL_LENGTH,0);
						}
					}

					/*
					 if(ball.x()<=-7*CELL_LENGTH)
					 {
					 if(ball.y()>1*CELL_LENGTH)
					 {
					 ///cout<<"1"<<endl;
					 destination=Vector3(-8.8*CELL_LENGTH,0*CELL_LENGTH,0);
					 }
					 else if(ball.y()<-1*CELL_LENGTH)
					 {
					 destination=Vector3(-8.8*CELL_LENGTH,-1.5*CELL_LENGTH,0);
					 }
					 else
					 {
					 destination=Vector3(-8.8*CELL_LENGTH,ball.y()-1*CELL_LENGTH,0);
					 }
					 }*/
				}
				else if (p == Position_C)
				{
					///cout<<"c"<<endl;
					destination = Vector3(ball.x() + 2 * FORMCELL_LENGTH
							,ball.y() - 2 * FORMCELL_LENGTH,0);
					if (ball.y() > 1 * CELL_LENGTH)
					{
						///cout<<"1"<<endl;
						destination = Vector3(ball.x() + 2 * FORMCELL_LENGTH
								,-1 * FORMCELL_LENGTH,0);
					}
					else if (ball.y() < -1 * CELL_LENGTH)
					{
						destination = Vector3(ball.x() + 2 * FORMCELL_LENGTH
								,-2 * FORMCELL_LENGTH,0);
					}
					else
					{
						destination = Vector3(ball.x() + 2 * FORMCELL_LENGTH
								,ball.y() - 2 * FORMCELL_LENGTH,0);
					}

					if (ball.x() < -7 * CELL_LENGTH)
					{
						destination = Vector3(-5 * CELL_LENGTH
								,ball.y() - 2 * FORMCELL_LENGTH,0);
						if (ball.y() > 1 * CELL_LENGTH)
						{
							///cout<<"1"<<endl;
							destination = Vector3(-5 * CELL_LENGTH
									,-1 * CELL_LENGTH,0);
						}
						else if (ball.y() < -1 * CELL_LENGTH)
						{
							destination = Vector3(-5 * CELL_LENGTH
									,-2 * CELL_LENGTH,0);
						}
						else
						{
							destination = Vector3(-5 * CELL_LENGTH
									,ball.y() - 2 * FORMCELL_LENGTH,0);
						}
					}

				}
				else if (p == Position_D)
				{
					///cout<<"d"<<endl;
					destination = Vector3(ball.x() + 2 * FORMCELL_LENGTH
							,ball.y() + 2 * FORMCELL_LENGTH,0);
					if (ball.y() > 1 * CELL_LENGTH)
					{
						///cout<<"1"<<endl;
						destination = Vector3(ball.x() + 2 * FORMCELL_LENGTH
								,2 * CELL_LENGTH,0);
					}
					else if (ball.y() < -1 * CELL_LENGTH)
					{
						destination = Vector3(ball.x() + 2 * CELL_LENGTH
								,1 * CELL_LENGTH,0);
					}
					else
					{
						destination = Vector3(ball.x() + 2 * FORMCELL_LENGTH
								,ball.y() + 2 * FORMCELL_LENGTH,0);
					}

					if (ball.x() < -7 * CELL_LENGTH)
					{
						destination = Vector3(-5 * CELL_LENGTH
								,ball.y() + 2 * CELL_LENGTH,0);
						if (ball.y() > 1 * CELL_LENGTH)
						{
							///cout<<"1"<<endl;
							destination = Vector3(-5 * CELL_LENGTH
									,2 * CELL_LENGTH,0);
						}
						else if (ball.y() < -1 * CELL_LENGTH)
						{
							destination = Vector3(-5 * CELL_LENGTH
									,1 * CELL_LENGTH,0);
						}
						else
						{
							destination = Vector3(-5 * CELL_LENGTH
									,ball.y() + 2 * CELL_LENGTH,0);
						}
					}
				}
			}
		}
		else if (GetCurrentGameMode() == PM_CORNER_KICK_Our
				|| GetCurrentGameMode() == PM_GOAL_KICK_Opp)
		{
			///cout<<"GetCurrentGameMode()==PM_CORNER_KICK_Our||GetCurrentGameMode()==PM_GOAL_KICK_Opp"<<endl;
			if (p == Position_A)
			{
				///cout<<"A"<<endl;
				if (ball.y() > 3 * CELL_LENGTH)
				{
					///cout<<"1"<<endl;
					destination = Vector3(6* CELL_LENGTH,4 * FORMCELL_LENGTH,0);
				}
				else if (ball.y() < -3 * CELL_LENGTH)
				{
					///cout<<"2"<<endl;
					destination = Vector3(6 * CELL_LENGTH,-2 * FORMCELL_LENGTH,0);
				}
				else
				{
					///cout<<"3"<<endl;
					destination = Vector3(6 * CELL_LENGTH,1.5 * FORMCELL_LENGTH
							,0);
				}
			}
			else if (p == Position_B)
			{
				///cout<<"B"<<endl;
				if (ball.y() > 3 * CELL_LENGTH)
				{
					///cout<<"1"<<endl;
					destination = Vector3(6* CELL_LENGTH,2 * FORMCELL_LENGTH,0);
				}
				else if (ball.y() < -3 * CELL_LENGTH)
				{
					///cout<<"2"<<endl;
					destination = Vector3(6* CELL_LENGTH,-4 * FORMCELL_LENGTH,0);
				}
				else
				{
					///cout<<"3"<<endl;
					destination = Vector3(6 * CELL_LENGTH,-1.5 * FORMCELL_LENGTH
							,0);
				}
			}
			else if (p == Position_C)
			{
				///cout<<"C"<<endl;
				if (ball.y() > 3 * CELL_LENGTH)
				{
					///cout<<"1"<<endl;
					destination = Vector3(7.5 * CELL_LENGTH,0 * FORMCELL_LENGTH,0);
				}
				else if (ball.y() < -3 * CELL_LENGTH)
				{
					///cout<<"2"<<endl;
					destination = Vector3(7.5 * CELL_LENGTH,-4 * FORMCELL_LENGTH,0);
				}
				else
				{
					///cout<<"3"<<endl;
					destination = Vector3(7.5 * CELL_LENGTH,-3 * FORMCELL_LENGTH,0);
				}
				///	  destination=Vector3(ball.x()+2*CELL_LENGTH,ball.y()-2*CELL_LENGTH,0);

			}
			else if (p == Position_D)
			{
				///cout<<"D"<<endl;
				if (ball.y() > 3 * CELL_LENGTH)
				{
					///cout<<"1"<<endl;
					destination = Vector3(7.5 * CELL_LENGTH,4 * FORMCELL_LENGTH,0);
				}
				else if (ball.y() < -3 * CELL_LENGTH)
				{
					///cout<<"2"<<endl;
					destination = Vector3(7.5* CELL_LENGTH,0 * FORMCELL_LENGTH,0);
				}
				else
				{
					///cout<<"3"<<endl;
					destination = Vector3(7.5 * CELL_LENGTH,+3 * FORMCELL_LENGTH,0);
				}
				///	  destination=Vector3(ball.x()+2*CELL_LENGTH,ball.y()+2*CELL_LENGTH,0);

			}
			else
			{
				///cout<<"4"<<endl;
				destination = myCoordinate;
			}

		}
		else
		{
			///cout<<"4"<<endl;
			destination = myCoordinate;
		}

	}
	else if (!CanSeeTheBall())
	{
		destination = myCoordinate;
	}
	if(p ==Position_E)
	{

		if(ball.x()>3*CELL_LENGTH)
		{
			destination = Vector3(ball.x()-5.5 * FORMCELL_LENGTH,ball.y() ,0);
		}
		else if(ball.x()>-3*CELL_LENGTH)
		{
			destination = Vector3(ball.x()-4 * FORMCELL_LENGTH,ball.y() ,0);
		}
		else
		{
			destination = myCoordinate;
		}
	}
	return destination;

}
#endif
#if 1
Vector3 WorldModel::GetPositionCoordinate(Position p)
{
	return GetPositionCoordinateForAttack(p);
}
Vector3 WorldModel::GetPositionCoordinateForDefense(Position p)
{
	Vector3 destination;

	/// Vector3 ball=GetTheBallStopCoordinate();

	/// Vector3 ball=GetLastCyclesAverageBallCoordinateForRunFormation();

	if (CanSeeTheBall())
	{
		if (GetCurrentGameMode() != PM_CORNER_KICK_Our
				&& GetCurrentGameMode() != PM_GOAL_KICK_Opp)
		{
			if (ball.x() > -5 * CELL_LENGTH && ball.x() < 5 * CELL_LENGTH)
			{
				///cout<<"middle"<<endl;
				if (p == Position_A)
				{
					///cout<<"A"<<endl;
					if (ball.y() > 4 * CELL_LENGTH)
					{
						///cout<<"1"<<endl;
						///destination=Vector3(ball.x()-2*CELL_LENGTH,5*CELL_LENGTH,0);
						destination = Vector3(ball.x() - 3 * CELL_LENGTH
						, ball.y() - 1.0 * CELL_LENGTH,0); ///changed by gaojin
					}
					else if (ball.y() < -4 * CELL_LENGTH)
					{
						///cout<<"2"<<endl;
						///destination=Vector3(ball.x()-2*CELL_LENGTH,-3*CELL_LENGTH,0);
						destination = Vector3(ball.x() - 2.5 * CELL_LENGTH
						, ball.y() + 2.0 * CELL_LENGTH,0); ///changed by gaojin
					}
					else
					{
						///cout<<"3"<<endl;
						/*if(ball.y()>=0)
						 {
						 destination=Vector3(ball.x()-1*CELL_LENGTH,ball.y()+0*CELL_LENGTH,0);

						 if(GetClosestToBallOpponentDistanceByVision()<0.4*CELL_LENGTH)
						 {
						 ///cout<<"GetClosestToBallOpponentDistanceByVision()<0.4*CELL_LENGTH:A"<<endl;
						 destination=Vector3(ball.x()-1*CELL_LENGTH,ball.y()+0*CELL_LENGTH,0);
						 }


						 }
						 else
						 {
						 destination=Vector3(ball.x()-2*CELL_LENGTH,ball.y()+CELL_LENGTH,0);

						 if(GetClosestToBallOpponentDistanceByVision()<0.4*CELL_LENGTH)
						 {
						 ///cout<<"GetClosestToBallOpponentDistanceByVision()<0.4*CELL_LENGTH:B"<<endl;
						 destination=Vector3(ball.x()-2.5*CELL_LENGTH,ball.y()+0*CELL_LENGTH,0);
						 }

						 }*////changed by gaojin
						/*add by gaojin*/
						destination = Vector3(ball.x() - 2.0 * CELL_LENGTH
						, ball.y() + 1.0 * CELL_LENGTH,0);
						if (GetClosestToBallOpponentDistanceByVision()
								< 0.4 * CELL_LENGTH)
						{
							destination = Vector3(ball.x() - 2.0 * CELL_LENGTH
							, ball.y() + 0.5 * CELL_LENGTH,0);
						}
						////////////////////////////////////////////
					}
				}
				else if (p == Position_B)
				{
					///cout<<"B"<<endl;
					if (ball.y() > 4 * CELL_LENGTH)
					{
						///cout<<"1"<<endl;
						//destination=Vector3(ball.x()-2*CELL_LENGTH,3*CELL_LENGTH,0);///changed by gaojin
						destination = Vector3(ball.x() - 2.5 * CELL_LENGTH
						, ball.y() - 2.0 * CELL_LENGTH,0);
					}
					else if (ball.y() < -4 * CELL_LENGTH)
					{
						///cout<<"2"<<endl;
						//destination=Vector3(ball.x()-2*CELL_LENGTH,-5*CELL_LENGTH,0);///changed by gaojin
						destination = Vector3(ball.x() - 3.0 * CELL_LENGTH
						, ball.y() + 1.0 * CELL_LENGTH,0);
					}
					else
					{
						///cout<<"3"<<endl;
						/*if(ball.y()>=0)
						 {
						 destination=Vector3(ball.x()-2*CELL_LENGTH,ball.y()-CELL_LENGTH,0);

						 if(GetClosestToBallOpponentDistanceByVision()<0.4*CELL_LENGTH)
						 {
						 ///cout<<"GetClosestToBallOpponentDistanceByVision()<0.4*CELL_LENGTH:C"<<endl;
						 destination=Vector3(ball.x()-2.5*CELL_LENGTH,ball.y()+0*CELL_LENGTH,0);
						 }

						 }
						 else
						 {
						 destination=Vector3(ball.x()-1*CELL_LENGTH,ball.y()-0*CELL_LENGTH,0);

						 if(GetClosestToBallOpponentDistanceByVision()<0.4*CELL_LENGTH)
						 {
						 ///cout<<"GetClosestToBallOpponentDistanceByVision()<0.4*CELL_LENGTH:D"<<endl;
						 destination=Vector3(ball.x()-1*CELL_LENGTH,ball.y()+0*CELL_LENGTH,0);
						 }

						 }*///changed by gaojin
						/*add by gaojin*/
						destination = Vector3(ball.x() - 2.0 * CELL_LENGTH
						, ball.y() - 1.0 * CELL_LENGTH,0);
						if (GetClosestToBallOpponentDistanceByVision()
								< 0.4 * CELL_LENGTH)
						{
							///cout<<"GetClosestToBallOpponentDistanceByVision()<0.4*CELL_LENGTH:D"<<endl;
							destination = Vector3(ball.x() - 2.0 * CELL_LENGTH
							, ball.y() - 0.5 * CELL_LENGTH,0);
						}
						////////////////////////////
					}
				}
				else if (p == Position_C)
				{
					///cout<<"C"<<endl;
					if (ball.y() > 3 * CELL_LENGTH)
					{
						///cout<<"1"<<endl;
						//destination=Vector3(ball.x()+2*CELL_LENGTH,1*CELL_LENGTH,0);changed by gaojin
						destination = Vector3(ball.x() - 1.5 * CELL_LENGTH
						, ball.y() - 1.5 * CELL_LENGTH,0);

					}
					else if (ball.y() < -3 * CELL_LENGTH)
					{
						///cout<<"2"<<endl;
						//destination=Vector3(ball.x()+1*CELL_LENGTH,-5*CELL_LENGTH,0);///changed by gaojin
						destination = Vector3(ball.x() - 2.0 * CELL_LENGTH
						, ball.y() + 1.0 * CELL_LENGTH,0);
					}
					else
					{
						///cout<<"3"<<endl;
						if (ball.y() >= 0)
						{
							destination = Vector3(ball.x() + 2 * CELL_LENGTH
							, ball.y() - 2 * CELL_LENGTH,0);
						}
						else
						{
							destination = Vector3(ball.x() + 1 * CELL_LENGTH
							, ball.y() - 2 * CELL_LENGTH,0);
						}
					}
				}
				else if (p == Position_D)
				{
					///cout<<"D"<<endl;
					if (ball.y() > 3 * CELL_LENGTH)
					{
						///cout<<"1"<<endl;
						//destination=Vector3(ball.x()+1*CELL_LENGTH,5*CELL_LENGTH,0);
						destination = Vector3(ball.x() - 2 * CELL_LENGTH
						, ball.y() - 1.0 * CELL_LENGTH,0); ///changed by gaojin
					}
					else if (ball.y() < -3 * CELL_LENGTH)
					{
						///cout<<"2"<<endl;
						//destination=Vector3(ball.x()+2*CELL_LENGTH,-1*CELL_LENGTH,0);
						destination = Vector3(ball.x() - 1.5 * CELL_LENGTH
						, ball.y() + 1.5 * CELL_LENGTH,0); ///changed by gaojin
					}
					else
					{
						///cout<<"3"<<endl;
						if (ball.y() >= 0)
						{
							destination = Vector3(ball.x() + 1 * CELL_LENGTH
							, ball.y() + 2 * CELL_LENGTH,0);
						}
						else
						{
							destination = Vector3(ball.x() + 2 * CELL_LENGTH
							, ball.y() + 2 * CELL_LENGTH,0);
						}
					}
				}
				else
				{
					///cout<<"4"<<endl;
					destination = myCoordinate;
				}
			}
			else if (ball.x() >= 5 * CELL_LENGTH)
			{
				///cout<<"Forward"<<endl;
				if (p == Position_A)
				{
					///cout<<"A"<<endl;
					if (ball.y() > 4 * CELL_LENGTH)
					{
						///cout<<"1"<<endl;
						//destination=Vector3(ball.x()-2*CELL_LENGTH,5*CELL_LENGTH,0);changed by gaojin
						destination = Vector3(ball.x() - 3 * CELL_LENGTH
						, ball.y() - 1.0 * CELL_LENGTH,0); ///changed by gaojin
					}
					else if (ball.y() < -4 * CELL_LENGTH)
					{
						///cout<<"2"<<endl;
						//destination=Vector3(ball.x()-2*CELL_LENGTH,ball.y-0.5*CELL_LENGTH,0);changed by gaojin
						destination = Vector3(ball.x() - 2.5 * CELL_LENGTH
						, ball.y() + 2.0 * CELL_LENGTH,0); ///changed by gaojin
					}
					else
					{
						///cout<<"3"<<endl;
						if (ball.y() >= 0)
						{
							destination = Vector3(ball.x() - 1.2 * CELL_LENGTH
							, ball.y() + 0.5 * CELL_LENGTH,0);
						}
						else if (ball.y() < 0)
						{
							destination = Vector3(ball.x() - 2 * CELL_LENGTH
							, ball.y() + CELL_LENGTH,0);
						}
					}
				}
				else if (p == Position_B)
				{
					///cout<<"B"<<endl;
					if (ball.y() > 4 * CELL_LENGTH)
					{
						///cout<<"1"<<endl;
						//destination=Vector3(ball.x()-2*CELL_LENGTH,3*CELL_LENGTH,0);changed by gaojin
						destination = Vector3(ball.x() - 2.5 * CELL_LENGTH
						, ball.y() - 2.0 * CELL_LENGTH,0);
					}
					else if (ball.y() < -4 * CELL_LENGTH)
					{
						///cout<<"2"<<endl;
						//destination=Vector3(ball.x()-2*CELL_LENGTH,-5*CELL_LENGTH,0);changed by gaojin
						destination = Vector3(ball.x() - 3.0 * CELL_LENGTH
						, ball.y() + 1.0 * CELL_LENGTH,0);
					}
					else
					{
						///cout<<"3"<<endl;
						if (ball.y() >= 0)
						{
							destination = Vector3(ball.x() - 2 * CELL_LENGTH
							, ball.y() - CELL_LENGTH,0);
						}
						else if (ball.y() < 0)
						{
							destination = Vector3(ball.x() - 1.2 * CELL_LENGTH
							, ball.y() - 0.5 * CELL_LENGTH,0);
						}
					}
				}
				else if (p == Position_C)
				{
					///cout<<"C"<<endl;
					if (ball.y() > 3 * CELL_LENGTH)
					{
						///cout<<"1"<<endl;
						destination = Vector3(6.5 * CELL_LENGTH,0 * CELL_LENGTH
								,0);
					}
					else if (ball.y() < -3 * CELL_LENGTH)
					{
						///cout<<"2"<<endl;
						destination = Vector3(6.5 * CELL_LENGTH,-4 * CELL_LENGTH
								,0);
					}
					else
					{
						///cout<<"3"<<endl;
						destination = Vector3(6.5 * CELL_LENGTH
						, ball.y() - 2 * CELL_LENGTH,0);
					}
					///	  destination=Vector3(ball.x()+2*CELL_LENGTH,ball.y()-2*CELL_LENGTH,0);

				}
				else if (p == Position_D)
				{
					///cout<<"D"<<endl;
					if (ball.y() > 3 * CELL_LENGTH)
					{
						///cout<<"1"<<endl;
						destination = Vector3(6.5 * CELL_LENGTH,4 * CELL_LENGTH
								,0);
					}
					else if (ball.y() < -3 * CELL_LENGTH)
					{
						///cout<<"2"<<endl;
						destination = Vector3(6.5 * CELL_LENGTH,0 * CELL_LENGTH
								,0);
					}
					else
					{
						///cout<<"3"<<endl;
						destination = Vector3(6.5 * CELL_LENGTH
						, ball.y() + 2 * CELL_LENGTH,0);
					}
					///	  destination=Vector3(ball.x()+2*CELL_LENGTH,ball.y()+2*CELL_LENGTH,0);

				}
				else
				{
					///cout<<"4"<<endl;
					destination = myCoordinate;
				}
				if (ball.x() >= 7 * CELL_LENGTH)
				{
					if (p == Position_A)
					{
						///cout<<"A"<<endl;
						if (ball.y() > 3 * CELL_LENGTH)
						{
							///cout<<"1"<<endl;
							destination = Vector3(5 * CELL_LENGTH
							, 4 * CELL_LENGTH,0);
						}
						else if (ball.y() < -3 * CELL_LENGTH)
						{
							///cout<<"2"<<endl;
							destination = Vector3(5 * CELL_LENGTH
							, -2 * CELL_LENGTH,0);
						}
						else
						{
							///cout<<"3"<<endl;
							destination = Vector3(5 * CELL_LENGTH
							, ball.y() + CELL_LENGTH,0);
						}
					}
					else if (p == Position_B)
					{
						///cout<<"B"<<endl;
						if (ball.y() > 3 * CELL_LENGTH)
						{
							///cout<<"1"<<endl;
							destination = Vector3(5 * CELL_LENGTH
							, 2 * CELL_LENGTH,0);
						}
						else if (ball.y() < -3 * CELL_LENGTH)
						{
							///cout<<"2"<<endl;
							destination = Vector3(5 * CELL_LENGTH
							, -4 * CELL_LENGTH,0);
						}
						else
						{
							///cout<<"3"<<endl;
							destination = Vector3(5 * CELL_LENGTH
							, ball.y() - CELL_LENGTH,0);
						}
					}
					else if (p == Position_C)
					{
						///cout<<"C"<<endl;
						if (ball.y() > 3 * CELL_LENGTH)
						{
							///cout<<"1"<<endl;
							destination = Vector3(6 * CELL_LENGTH
							, 0 * CELL_LENGTH,0);
						}
						else if (ball.y() < -3 * CELL_LENGTH)
						{
							///cout<<"2"<<endl;
							destination = Vector3(6 * CELL_LENGTH
							, -4 * CELL_LENGTH,0);
						}
						else
						{
							///cout<<"3"<<endl;
							destination = Vector3(6 * CELL_LENGTH
							, ball.y() - 1.5 * CELL_LENGTH,0);
						}

						if (GetCurrentGameMode() == PM_PlayOn
								&& fabs(ball.y()) < 2 * CELL_LENGTH)
						{
							///cout<<"4"<<endl;
							destination = Vector3(ball.x() - 1.2 * CELL_LENGTH
							, ball.y() - 1.3 * CELL_LENGTH,0);

						}

						///	  destination=Vector3(ball.x()+2*CELL_LENGTH,ball.y()-2*CELL_LENGTH,0);

					}
					else if (p == Position_D)
					{
						///cout<<"D"<<endl;
						if (ball.y() > 3 * CELL_LENGTH)
						{
							///cout<<"1"<<endl;
							destination = Vector3(6 * CELL_LENGTH
							, 4 * CELL_LENGTH,0);
						}
						else if (ball.y() < -3 * CELL_LENGTH)
						{
							///cout<<"2"<<endl;
							destination = Vector3(6 * CELL_LENGTH
							, 0 * CELL_LENGTH,0);
						}
						else
						{
							///cout<<"3"<<endl;
							destination = Vector3(6 * CELL_LENGTH
							, ball.y() + 1.5 * CELL_LENGTH,0);
						}

						if (GetCurrentGameMode() == PM_PlayOn
								&& fabs(ball.y()) < 2 * CELL_LENGTH)
						{
							///cout<<"4"<<endl;
							destination = Vector3(ball.x() - 1.2 * CELL_LENGTH
							, ball.y() + 1.3 * CELL_LENGTH,0);
						}
						///	  destination=Vector3(ball.x()+2*CELL_LENGTH,ball.y()+2*CELL_LENGTH,0);

					}
					else
					{
						///cout<<"4"<<endl;
						destination = myCoordinate;
					}
				}

			}
			else if (ball.x() <= -5 * CELL_LENGTH)
			{
				///cout<<"BackWard"<<endl;
				if (p == Position_A)
				{
					/*
					 ///cout<<"A"<<endl;
					 if(ball.y()>2*CELL_LENGTH)
					 {
					 ///cout<<"1"<<endl;
					 destination=Vector3(-6*CELL_LENGTH,3*CELL_LENGTH,0);
					 }
					 else if(ball.y()<-2*CELL_LENGTH)
					 {
					 destination=Vector3(-6*CELL_LENGTH,-1*CELL_LENGTH,0);
					 }
					 else
					 {
					 if(ball.y()>=0)
					 {
					 destination=Vector3(-6*CELL_LENGTH,ball.y()+0*CELL_LENGTH,0);
					 }
					 else if(ball.y()<0)
					 {
					 destination=Vector3(-6*CELL_LENGTH,ball.y()+1*CELL_LENGTH,0);
					 }
					 }
					 */
					/*
					 if(ball.x()<=-7*CELL_LENGTH)
					 {
					 if(ball.y()>1*CELL_LENGTH)
					 {
					 ///cout<<"1"<<endl;
					 destination=Vector3(-8.8*CELL_LENGTH,1.5*CELL_LENGTH,0);
					 }
					 else if(ball.y()<-1*CELL_LENGTH)
					 {
					 destination=Vector3(-8.8*CELL_LENGTH,0*CELL_LENGTH,0);
					 }
					 else
					 {
					 destination=Vector3(-8.8*CELL_LENGTH,ball.y()+1*CELL_LENGTH,0);
					 }
					 }*/
					if (this->GetBallToMyGoalDistance() > 2.5 * CELL_LENGTH)
					{
						Vector3 Center = (ball
								+ Vector3(-this->GetFieldLength() / 2, 0, 0))
								/ 2;
						destination = Vector3(Center.x(),
								Center.y() + 0.5 * CELL_LENGTH,0);
					}
					else
					{
						destination = Vector3(-8 * CELL_LENGTH,CELL_LENGTH,0);
					}

				}
				else if (p == Position_B)
				{
					///cout<<"B"<<endl;
					if (this->GetBallToMyGoalDistance() > 2.5 * CELL_LENGTH)
					{
						Vector3 Center = (ball
								+ Vector3(-this->GetFieldLength() / 2, 0, 0))
								/ 2;
						destination = Vector3(Center.x(),
								Center.y() - 0.5 * CELL_LENGTH,0);
					}
					else
					{
						destination = Vector3(-8 * CELL_LENGTH,-CELL_LENGTH,0);
					}

					/*
					 if(ball.x()<=-7*CELL_LENGTH)
					 {
					 if(ball.y()>1*CELL_LENGTH)
					 {
					 ///cout<<"1"<<endl;
					 destination=Vector3(-8.8*CELL_LENGTH,0*CELL_LENGTH,0);
					 }
					 else if(ball.y()<-1*CELL_LENGTH)
					 {
					 destination=Vector3(-8.8*CELL_LENGTH,-1.5*CELL_LENGTH,0);
					 }
					 else
					 {
					 destination=Vector3(-8.8*CELL_LENGTH,ball.y()-1*CELL_LENGTH,0);
					 }
					 }*/
				}
				else if (p == Position_C)
				{
					///cout<<"c"<<endl;
					destination = Vector3(ball.x() + 2 * CELL_LENGTH
					, ball.y() - 2 * CELL_LENGTH,0);
					if (ball.y() > 2 * CELL_LENGTH)
					{
						///cout<<"1"<<endl;
						destination = Vector3(ball.x() + 2 * CELL_LENGTH
						, 1 * CELL_LENGTH,0);
					}
					else
					{
						destination = Vector3(ball.x() + 2 * CELL_LENGTH
						, ball.y() - 2 * CELL_LENGTH,0);
					}

					if (ball.x() < -7 * CELL_LENGTH)
					{
						destination = Vector3(-5.5 * CELL_LENGTH
						, ball.y() - 2 * CELL_LENGTH,0);
						if (ball.y() > 1 * CELL_LENGTH)
						{
							///cout<<"1"<<endl;
							destination = Vector3(-5.5 * CELL_LENGTH
							, -1 * CELL_LENGTH,0);
						}
						else if (ball.y() < -1 * CELL_LENGTH)
						{
							destination = Vector3(-5.5 * CELL_LENGTH
							, -2 * CELL_LENGTH,0);
						}
						else
						{
							destination = Vector3(-5.5 * CELL_LENGTH
							, ball.y() - 2 * CELL_LENGTH,0);
						}
					}

				}
				else if (p == Position_D)
				{
					///cout<<"d"<<endl;
					destination = Vector3(ball.x() + 2 * CELL_LENGTH
					, ball.y() + 2 * CELL_LENGTH,0);
					if (ball.y() < -2 * CELL_LENGTH)
					{
						destination = Vector3(ball.x() + 2 * CELL_LENGTH
						, -2 * CELL_LENGTH,0);
					}
					else
					{
						destination = Vector3(ball.x() + 2 * CELL_LENGTH
						, ball.y() + 2 * CELL_LENGTH,0);
					}

					if (ball.x() < -7 * CELL_LENGTH)
					{
						destination = Vector3(-5.5 * CELL_LENGTH
						, ball.y() + 2 * CELL_LENGTH,0);
						if (ball.y() > 1 * CELL_LENGTH)
						{
							///cout<<"1"<<endl;
							destination = Vector3(-5.5 * CELL_LENGTH
							, 2 * CELL_LENGTH,0);
						}
						else if (ball.y() < -1 * CELL_LENGTH)
						{
							destination = Vector3(-5.5 * CELL_LENGTH
							, 1 * CELL_LENGTH,0);
						}
						else
						{
							destination = Vector3(-5.5 * CELL_LENGTH
							, ball.y() + 2 * CELL_LENGTH,0);
						}
					}
				}
			}
		}
		else if (GetCurrentGameMode() == PM_CORNER_KICK_Our
				|| GetCurrentGameMode() == PM_GOAL_KICK_Opp)
		{
			///cout<<"GetCurrentGameMode()==PM_CORNER_KICK_Our||GetCurrentGameMode()==PM_GOAL_KICK_Opp"<<endl;
			if (p == Position_A)
			{
				///cout<<"A"<<endl;
				if (ball.y() > 3 * CELL_LENGTH)
				{
					///cout<<"1"<<endl;
					destination = Vector3(3.5 * CELL_LENGTH,4 * CELL_LENGTH,0);
				}
				else if (ball.y() < -3 * CELL_LENGTH)
				{
					///cout<<"2"<<endl;
					destination = Vector3(3.5 * CELL_LENGTH,-2 * CELL_LENGTH,0);
				}
				else
				{
					///cout<<"3"<<endl;
					destination = Vector3(3.5 * CELL_LENGTH,1.5 * CELL_LENGTH
							,0);
				}
			}
			else if (p == Position_B)
			{
				///cout<<"B"<<endl;
				if (ball.y() > 3 * CELL_LENGTH)
				{
					///cout<<"1"<<endl;
					destination = Vector3(3.5 * CELL_LENGTH,2 * CELL_LENGTH,0);
				}
				else if (ball.y() < -3 * CELL_LENGTH)
				{
					///cout<<"2"<<endl;
					destination = Vector3(3.5 * CELL_LENGTH,-4 * CELL_LENGTH,0);
				}
				else
				{
					///cout<<"3"<<endl;
					destination = Vector3(3.5 * CELL_LENGTH,-1.5 * CELL_LENGTH
							,0);
				}
			}
			else if (p == Position_C)
			{
				///cout<<"C"<<endl;
				if (ball.y() > 3 * CELL_LENGTH)
				{
					///cout<<"1"<<endl;
					destination = Vector3(6 * CELL_LENGTH,0 * CELL_LENGTH,0);
				}
				else if (ball.y() < -3 * CELL_LENGTH)
				{
					///cout<<"2"<<endl;
					destination = Vector3(6 * CELL_LENGTH,-4 * CELL_LENGTH,0);
				}
				else
				{
					///cout<<"3"<<endl;
					destination = Vector3(6 * CELL_LENGTH,-3 * CELL_LENGTH,0);
				}
				///	  destination=Vector3(ball.x()+2*CELL_LENGTH,ball.y()-2*CELL_LENGTH,0);

			}
			else if (p == Position_D)
			{
				///cout<<"D"<<endl;
				if (ball.y() > 3 * CELL_LENGTH)
				{
					///cout<<"1"<<endl;
					destination = Vector3(6 * CELL_LENGTH,4 * CELL_LENGTH,0);
				}
				else if (ball.y() < -3 * CELL_LENGTH)
				{
					///cout<<"2"<<endl;
					destination = Vector3(6 * CELL_LENGTH,0 * CELL_LENGTH,0);
				}
				else
				{
					///cout<<"3"<<endl;
					destination = Vector3(6 * CELL_LENGTH,+3 * CELL_LENGTH,0);
				}
				///	  destination=Vector3(ball.x()+2*CELL_LENGTH,ball.y()+2*CELL_LENGTH,0);

			}
			else
			{
				///cout<<"4"<<endl;
				destination = myCoordinate;
			}

		}
		else
		{
			///cout<<"4"<<endl;
			destination = myCoordinate;
		}

	}
	else if (!CanSeeTheBall())
	{
		destination = myCoordinate;
	}
	if(p ==Position_E)
	{

		if(ball.x()>3*CELL_LENGTH)
		{
			destination = Vector3(ball.x()-5.5 * CELL_LENGTH,ball.y() ,0);
		}
		else if(ball.x()>-3*CELL_LENGTH)
		{
			destination = Vector3(ball.x()-3 * CELL_LENGTH,ball.y() ,0);
		}
		else
		{
			destination = myCoordinate;
		}
	}
	return destination;

}

#endif

float WorldModel::WhetherTeammateInMyWayToDestination(
		Vector3 teammateCoordinate, Vector3 myCoordinate, Vector3 destination)
{
	float myToTeammate = (myCoordinate-teammateCoordinate).xymod();
	float myToDestination =(destination-myCoordinate).xymod();
	float teammateToDestination =(teammateCoordinate-destination).xymod();
	float angle = acos(
			(myToTeammate * myToTeammate + myToDestination * myToDestination
					- teammateToDestination * teammateToDestination) / 2
					/ myToTeammate / myToDestination);
	angle = angle / PI * 180;
//	cout<<"teammateCoordinate::"<<teammateCoordinate<<endl;
//	cout<<"myCoordinate::"<<myCoordinate<<endl;
//	cout<<"destination::"<<destination<<endl;
//	cout<<"angle::"<<angle<<endl;
	if (myToTeammate >= myToDestination)
	{
//		cout<<"myToTeammate >= myToDestination && myToDestination < 0.3 * CELL_LENGTH"<<endl;
		angle = 90;
	}

	///cout<<"~~~~~~~~~~~~~~~~~~~~~~angle:"<<angle<<endl;
	return angle;
}



float WorldModel::WhetherTeammateInMyWayToDestinationVANGUARD(
		Vector3 teammateCoordinate, Vector3 myCoordinate, Vector3 destination)
{
	float myToTeammate = (myCoordinate-teammateCoordinate).xymod();
	float myToDestination =(destination-myCoordinate).xymod();
	float teammateToDestination =(teammateCoordinate-destination).xymod();
	float angle = acos(
			( teammateToDestination * teammateToDestination + myToDestination * myToDestination
					-myToTeammate * myToTeammate ) / 2
					/ teammateToDestination / myToDestination);
	angle = angle / PI * 180;
//	cout<<"teammateCoordinate::"<<teammateCoordinate<<endl;
//	cout<<"myCoordinate::"<<myCoordinate<<endl;
//	cout<<"destination::"<<destination<<endl;
//	cout<<"angle::"<<angle<<endl;
	/*if (myToTeammate >= myToDestination)
	{
//		cout<<"myToTeammate >= myToDestination && myToDestination < 0.3 * CELL_LENGTH"<<endl;
		angle = 90;
	}*/

	///cout<<"~~~~~~~~~~~~~~~~~~~~~~angle:"<<angle<<endl;
	return angle;
}

















void WorldModel::updateDistanceAndAngleToBall()
{
	ballCoor_X->removedQueue(lastCyclesAverageBallCoordinate.x());
	ballCoor_Y->removedQueue(lastCyclesAverageBallCoordinate.y());
}

Vector3 WorldModel::GetTheBallStopCoordinate() ///forecast the postion where the ball stoped,by the speed of  ball
{
	float x = lastCyclesAverageBallCoordinate.x()
			+ (ballCoor_X->GetRear() - ballCoor_X->GetFront()) * (2.546 / 1.2);
	float y =
			lastCyclesAverageBallCoordinate.y()
					+ (ballCoor_Y->GetRear() - ballCoor_Y->GetFront())
							* (2.266 / 1.166);
	Vector3 pos(x, y, 0);
	return pos;
}

void WorldModel::updateRecordTeammateAndOpponentSenceMap()
{
	static int count = 0;
	count++;

	for (TPlayerSenseMap::iterator iter =
			messageParser.mTeamMateSenseMap.begin();
			iter != messageParser.mTeamMateSenseMap.end(); ++iter)
			{
		if ((*iter).first == TMMT_1 && (*iter).second.head.distance != 0)
		{
			RecordTeamMateSenseMap[(*iter).first] = (*iter).second;
		}
		else if ((*iter).first == TMMT_2 && (*iter).second.head.distance != 0)
		{
			RecordTeamMateSenseMap[(*iter).first] = (*iter).second;
		}
		else if ((*iter).first == TMMT_3 && (*iter).second.head.distance != 0)
		{
			RecordTeamMateSenseMap[(*iter).first] = (*iter).second;
		}
		else if ((*iter).first == TMMT_4 && (*iter).second.head.distance != 0)
		{
			RecordTeamMateSenseMap[(*iter).first] = (*iter).second;
		}
		else if ((*iter).first == TMMT_5 && (*iter).second.head.distance != 0)
		{
			RecordTeamMateSenseMap[(*iter).first] = (*iter).second;
		}
		else if ((*iter).first == TMMT_6 && (*iter).second.head.distance != 0)
		{
			RecordTeamMateSenseMap[(*iter).first] = (*iter).second;
		}
		else if ((*iter).first == TMMT_7 && (*iter).second.head.distance != 0)
		{
			RecordTeamMateSenseMap[(*iter).first] = (*iter).second;
		}
		else if ((*iter).first == TMMT_8 && (*iter).second.head.distance != 0)
		{
			RecordTeamMateSenseMap[(*iter).first] = (*iter).second;
		}
		else if ((*iter).first == TMMT_9 && (*iter).second.head.distance != 0)
		{
			RecordTeamMateSenseMap[(*iter).first] = (*iter).second;
		}

///	  RecordTeamMateSenseMap=messageParser.mTeamMateSenseMap;

		///cout<<"0000000000000000000000000(*iter).second.unum:"<<(*iter).second.unum<<endl;
		///cout<<"0000000000000000000000000(*iter).second.head.distance:"<<(*iter).second.head.distance<<endl;
	}
///cout<<"4444444444444444444444444444444444444444444444444444444444444444444444444"<<endl;
	for (TPlayerSenseMap::iterator iter = RecordTeamMateSenseMap.begin();
			iter != RecordTeamMateSenseMap.end(); ++iter)
			{
		///cout<<"1111111111111111111111111(*iter).second.unum:"<<(*iter).second.unum<<endl;
		///cout<<"1111111111111111111111111(*iter).second.head.distance:"<<(*iter).second.head.distance<<endl;
	}

	if (count > 150)
	{
		RecordTeamMateSenseMap.clear();
		count = 0;
	}

///cout<<"555555555555555555555555555555555555555555555555555555555555555555555555555"<<endl;

}

float WorldModel::GetMyBodyAngleToCloserTeammate()
{

	///cout<<"enter GetMyBodyAngleToCloserTeammate:"<<endl<<endl;
	float angleToMyHead, angleToMyBody = 1000;
	float angleOfTurnHead = GetCurrentJointAngle(JID_HEAD_1);

///	int number;
///	float dis=40;
	float closerToBallTeammateDistanceByVision = 40;
	float myDisToTeammate, myAngleToTeammate, distance;
	float myAngleToBall = GetMyAngleToBall(), myDistanceToBall =
			GetMyDistanceToBall();
	float angle;
	for (TPlayerSenseMap::iterator iter =
			messageParser.mTeamMateSenseMap.begin();
			iter != messageParser.mTeamMateSenseMap.end(); ++iter)
			{

		myDisToTeammate = (*iter).second.head.distance;
		myAngleToTeammate = (*iter).second.head.theta;
		if (myAngleToTeammate != 0 && myDisToTeammate != 0)
		{
			if ((myAngleToBall * myAngleToTeammate) < 0)
			{
				angle = fabs(myAngleToBall) + fabs(myAngleToTeammate);
				///cout<<"myAngleToBall:"<<myAngleToBall<<endl;
				///cout<<"myAngleToTeammate:"<<myAngleToTeammate<<endl;
				///cout<<"angle1:"<<angle<<endl;
			}
			else
			{
				angle = fabs(myAngleToBall - myAngleToTeammate);
				///cout<<"myAngleToBall:"<<myAngleToBall<<endl;
				///cout<<"myAngleToTeammate:"<<myAngleToTeammate<<endl;
				///cout<<"angle2:"<<angle<<endl;
			}
			///cout<<"myDistanceToBall:"<<myDistanceToBall<<endl;
			///cout<<"myDisToTeammate:"<<myDisToTeammate<<endl;
			distance = sqrt(
					myDistanceToBall * myDistanceToBall
							+ myDisToTeammate * myDisToTeammate
							- cos(angle * PI / 180) * 2 * myDistanceToBall
									* myDisToTeammate);
			///cout<<"Teammate number:"<<(*iter).second.unum<<"distance to ball:"<<distance<<endl;
			if (distance < closerToBallTeammateDistanceByVision
					&& distance > CELL_LENGTH)
			{

				angleToMyHead = myAngleToTeammate;
				angleToMyBody = angleToMyHead + angleOfTurnHead;
				distance = closerToBallTeammateDistanceByVision;
				///cout<<"iter->second.unum:"<<iter->second.unum<<"angleToMyBody:"<<angleToMyBody<<endl;
				//	closestToBallTeammateNumberByVision=(*iter).second.unum;
				//	closestToBallTeammateDistanceByVision=distance;

			}
		}
	}

	///cout<<"final angleToMyBody:"<<angleToMyBody<<endl;
	return angleToMyBody;

	/////cout<<"I see Vanguard number:"<<vanguardNumberByVision<<endl;
///	return vanguardNumberByVision;

}

void WorldModel::LocaLizationByLines(Vector3 &myCoordinate, VisionObject line1,
		VisionObject line2)
{
	/// my distance to line1 one side and another side 
	useLineDoLocalization = true;
	float dis1 = sqrt(
			messageParser.mLineSenseMap[line1].distance1
					* messageParser.mLineSenseMap[line1].distance1
					- 0.45 * 0.45);
	float dis2 = sqrt(
			messageParser.mLineSenseMap[line1].distance2
					* messageParser.mLineSenseMap[line1].distance2
					- 0.45 * 0.45);
	;
	///////cout<<"dis1 ="<<dis1<<"		dis 2="<<dis2<<endl;
//	float lineAngle1=fabs(messageParser.mLineSenseMap[line1].theta1*cosDeg((messageParser.mLineSenseMap[line1].phi1))*cosDeg((-messageParser.mHingeJointSenseMap[JID_HEAD_2].angle-messageParser.mLineSenseMap[line1].phi1))-messageParser.mLineSenseMap[line1].theta2*cosDeg((messageParser.mLineSenseMap[line1].phi2))*cosDeg((-messageParser.mHingeJointSenseMap[JID_HEAD_2].angle-messageParser.mLineSenseMap[line1].phi2)));
	float lineAngle1 =
			fabs(
					asinDeg(
							sinDeg(messageParser.mLineSenseMap[line1].theta1)
									* sinDeg(
											90
													- messageParser.mLineSenseMap[line1].phi1))
							- asinDeg(
									sinDeg(
											messageParser.mLineSenseMap[line1].theta2)
											* sinDeg(
													90
															- messageParser.mLineSenseMap[line1].phi2)));

	float lineLength1 = sqrt(
			dis1 * dis1 + dis2 * dis2 - 2 * dis1 * dis2 * cosDeg(lineAngle1));
	float disToSideL1 = sinDeg(lineAngle1) * dis1 * dis2 / lineLength1;

	/// my distance to line2 one side and another side 
	float dis3 = sqrt(
			messageParser.mLineSenseMap[line2].distance1
					* messageParser.mLineSenseMap[line2].distance1
					- 0.45 * 0.45);
	float dis4 = sqrt(
			messageParser.mLineSenseMap[line2].distance2
					* messageParser.mLineSenseMap[line2].distance2
					- 0.45 * 0.45);
	;
	///////cout<<"dis1 ="<<dis1<<"		dis 2="<<dis2<<endl;
	//float lineAngle2=fabs(messageParser.mLineSenseMap[line2].theta1*cosDeg((messageParser.mLineSenseMap[line2].phi1))-messageParser.mLineSenseMap[line2].theta2*cosDeg((messageParser.mLineSenseMap[line2].phi2)));
	float lineAngle2 =
			fabs(
					asinDeg(
							sinDeg(messageParser.mLineSenseMap[line2].theta1)
									* sinDeg(
											90
													- messageParser.mLineSenseMap[line2].phi1))
							- asinDeg(
									sinDeg(
											messageParser.mLineSenseMap[line2].theta2)
											* sinDeg(
													90
															- messageParser.mLineSenseMap[line2].phi2)));
	float lineLength2 = sqrt(
			dis3 * dis3 + dis4 * dis4 - 2 * dis3 * dis4 * cosDeg(lineAngle2));
	float disToSideL2 = sinDeg(lineAngle2) * dis3 * dis4 / lineLength2;
	///cout<<" my distance to line1 :"<<disToSideL1<<"   my distance to line 2:"<<disToSideL2<<endl;
	/// distance to coordinate

	if (line1 == LI_SIDE_P && line2 == LI_GOAL_R)
	{
		myCoordinate.y(GetFieldWidth() / 2 - disToSideL1);
		myCoordinate.x(GetFieldLength() / 2 - disToSideL2);
	}
	else if (line2 == LI_SIDE_P && line1 == LI_GOAL_R)
	{
		myCoordinate.y(GetFieldWidth() / 2 - disToSideL2);
		myCoordinate.x(GetFieldLength() / 2 - disToSideL1);
	}
	else if (line2 == LI_SIDE_N && line1 == LI_GOAL_R)
	{
		myCoordinate.y(-GetFieldWidth() / 2 + disToSideL2);
		myCoordinate.x(GetFieldLength() / 2 - disToSideL1);
	}
	else if (line1 == LI_SIDE_N && line2 == LI_GOAL_R)
	{
		myCoordinate.y(-GetFieldWidth() / 2 + disToSideL1);
		myCoordinate.x(GetFieldLength() / 2 - disToSideL2);
		//   ///cout<<"1111"<<endl;
	}
	///left side 
	else if (line1 == LI_SIDE_P && line2 == LI_GOAL_L)
	{
		myCoordinate.y(GetFieldWidth() / 2 - disToSideL1);
		myCoordinate.x(-GetFieldLength() / 2 + disToSideL2);
	}
	else if (line2 == LI_SIDE_P && line1 == LI_GOAL_L)
	{
		myCoordinate.y(GetFieldWidth() / 2 - disToSideL2);
		myCoordinate.x(-GetFieldLength() / 2 + disToSideL1);
	}
	else if (line2 == LI_SIDE_N && line1 == LI_GOAL_L)
	{
		myCoordinate.y(-GetFieldWidth() / 2 + disToSideL2);
		myCoordinate.x(-GetFieldLength() / 2 + disToSideL1);
	}
	else if (line1 == LI_SIDE_N && line2 == LI_GOAL_L)
	{
		myCoordinate.y(-GetFieldWidth() / 2 + disToSideL1);
		myCoordinate.x(-GetFieldLength() / 2 + disToSideL2);
	}

	if (GetMyTeamIndex() == TI_RIGHT)
	{
		myCoordinate.x(-myCoordinate.x());
		myCoordinate.y(-myCoordinate.y());
	}
	///cout<<"   use line location!!"<<endl;
	/////cout<<"  coor :("<<myCoordinate.x()<<" , "<<myCoordinate.y()<<" )"<<endl;
}

void WorldModel::LocaLizationByGoalLine(Vector3& myCoordinate,
		VisionObject line, VisionObject flag)
{
	float dis = sqrt(
			messageParser.mVisionSenseMap[flag].distance
					* messageParser.mVisionSenseMap[flag].distance
					- 0.45 * 0.45); /// my dis to flag
	float angle, dis1;

	int whichPoint;
	if (messageParser.mLineSenseMap[line].distance1
			< messageParser.mLineSenseMap[line].distance2)
	{
		dis1 = sqrt(
				messageParser.mLineSenseMap[line].distance1
						* messageParser.mLineSenseMap[line].distance1
						- 0.45 * 0.45); // my dis to line , one side
		angle =
				fabs(
						asinDeg(
								sinDeg(messageParser.mLineSenseMap[line].theta1)
										* sinDeg(
												90
														- messageParser.mLineSenseMap[line].phi1))
								- asinDeg(
										sinDeg(
												messageParser.mVisionSenseMap[flag].theta)
												* sinDeg(
														90
																- messageParser.mVisionSenseMap[flag].phi)));
		if (messageParser.mLineSenseMap[line].theta1
				> messageParser.mLineSenseMap[line].theta2)
			whichPoint = 1; ///left side
		else
			whichPoint = 2; ///right side
	}
	else
	{
		dis1 = sqrt(
				messageParser.mLineSenseMap[line].distance2
						* messageParser.mLineSenseMap[line].distance2
						- 0.45 * 0.45); // my dis to line , one side
		angle =
				fabs(
						asinDeg(
								sinDeg(messageParser.mLineSenseMap[line].theta2)
										* sinDeg(
												90
														- messageParser.mLineSenseMap[line].phi2))
								- asinDeg(
										sinDeg(
												messageParser.mVisionSenseMap[flag].theta)
												* sinDeg(
														90
																- messageParser.mVisionSenseMap[flag].phi)));
		if (messageParser.mLineSenseMap[line].theta2
				> messageParser.mLineSenseMap[line].theta1)
			whichPoint = 1; ///in left side
		else
			whichPoint = 2; /// in right side
	}
	float partlen = sqrt(
			dis * dis + dis1 * dis1 - 2 * dis * dis1 * cosDeg(angle)); /// part len of line
	float baseangle = asinDeg(dis * sinDeg(angle) / partlen);
	float theta = asinDeg(dis1 * sinDeg(angle) / partlen); /// key angle to figure out coordinate

	float x, y;
	y = dis * cosDeg(theta);
	x = dis * sinDeg(theta);
	if (baseangle + angle < 90)
	{
		y = -fabs(y);
	}
	/////cout<<"theta :"<<theta<<"  x:"<<x<<"   y:"<<y<<endl;
	/////cout<<"angle to flag"<<messageParser.mVisionSenseMap[flag].theta<<"line theta 1:"<<messageParser.mLineSenseMap[line].theta1<<"   line theta2 :"<<messageParser.mLineSenseMap[line].theta2<<"	which :"<<whichPoint<<endl;
	if (flag == VO_GOAL1_R)
	{
		if (whichPoint == 1)
		{
			myCoordinate.y(GetGoalWidth() / 2 + y);
			myCoordinate.x(GetFieldLength() / 2 - x);
//		  ///cout<<"  111 "<<endl;
		}
		else
		{
			myCoordinate.y(GetGoalWidth() / 2 - y);
			myCoordinate.x(GetFieldLength() / 2 - x);
//		    ///cout<<"  222 "<<endl;
		}
	}
	else if (flag == VO_GOAL2_R)
	{
		if (whichPoint == 1)
		{
			myCoordinate.y(-GetGoalWidth() / 2 + y);
			myCoordinate.x(GetFieldLength() / 2 - x);
//		    ///cout<<"  333 "<<endl;
		}
		else
		{
			myCoordinate.y(-GetGoalWidth() / 2 - y);
			myCoordinate.x(GetFieldLength() / 2 - x);
//		    ///cout<<"  444 "<<endl;
		}
	}
	else if (flag == VO_GOAL1_L)
	{
		if (whichPoint == 1)
		{
			myCoordinate.y(GetGoalWidth() / 2 - y);
			myCoordinate.x(-GetFieldLength() / 2 + x);
//		    ///cout<<"  555 "<<endl;
		}
		else
		{
			myCoordinate.y(GetGoalWidth() / 2 + y);
			myCoordinate.x(-GetFieldLength() / 2 + x);
//		    ///cout<<"  666 "<<endl;
		}
	}
	else if (flag == VO_GOAL2_L)
	{
		if (whichPoint == 1)
		{
			myCoordinate.y(-GetGoalWidth() / 2 - y);
			myCoordinate.x(-GetFieldLength() / 2 + x);
//		    ///cout<<"  777 "<<endl;
		}
		else
		{
			myCoordinate.y(-GetGoalWidth() / 2 + y);
			myCoordinate.x(-GetFieldLength() / 2 + x);
//		    ///cout<<"  888 "<<endl;
		}
	}

	if (GetMyTeamIndex() == TI_RIGHT)
	{
		myCoordinate.y(-myCoordinate.y());
		myCoordinate.x(-myCoordinate.x());
	}
	/////cout<<"use goal location!!  line:"<<line<<   "flag :"<<flag<<endl;
	/////cout<<"  my new position :("<<myCoordinate.x()<<" , "<<myCoordinate.y()<<" )  (by one goal flag!)"<<endl;

}

float WorldModel::GetBallToMyGoalDistance()
{
	float L = GetFieldLength() / 2;
	///cout<<"GetBallToMyGoalDistance:"<<sqrt(ball.y()*ball.y()+(ball.x()+L)*(ball.x()+L))<<endl;
	return sqrt(ball.y() * ball.y() + (ball.x() + L) * (ball.x() + L));

}

VisionObject WorldModel::GetLastCycleLocalizationFlag()
{
	return lastCycleLocalizationFlag;
}

bool WorldModel::WhetherDecideToPassBall()
{
	bool res = false;
	for (TPlayerSenseMap::iterator iter1 =
			messageParser.mOpponentSenseMap.begin();
			iter1 != messageParser.mOpponentSenseMap.end(); ++iter1)
			{
		if ((*iter1).second.head.distance != 0)
		{
			float myBodyAngleToOpponent = (*iter1).second.head.theta
					+ GetCurrentJointAngle(JID_HEAD_1);
			float myDistanceToOpponent = (*iter1).second.head.distance;

			///cout<<"inside WhetherDecideToPassBall:"<<endl;

			if (fabs(myBodyAngleToOpponent) < 35
					&& myDistanceToOpponent < 2.5 * CELL_LENGTH
					&& CanSeeTheBall())
			{
				///cout<<"myBodyAngleToOpponent:"<<myBodyAngleToOpponent<<" aa"<<(*iter1).second.unum<<"aa "<<(*iter1).second.head.theta<<endl;
				///cout<<"myDistanceToOpponent:"<<(*iter1).second.head.distance<<endl;
				res = true;
			}
			///	    else if(fabs(myBodyAngleToOpponent)<35&&myDistanceToOpponent<0.42&&CanSeeTheBall())
			{
				///	  res=true;
			}
		}
	}
	return res;
}

bool WorldModel::WhetherCanTurnToOpponentGoal()
{
	bool res = true;
	for (TPlayerSenseMap::iterator iter =
			messageParser.mOpponentSenseMap.begin();
			iter != messageParser.mOpponentSenseMap.end(); ++iter)
			{
		if ((*iter).second.head.distance != 0 && (*iter).second.head.theta != 0)
		{
			Vector3 opponentCoordinate = GetNewOpponentCoordinate(
					(*iter).second.unum);

			if (fabs(opponentCoordinate.y() - ball.y()) < 0.5 * CELL_LENGTH
					&& opponentCoordinate.x() - ball.x() < 1 * CELL_LENGTH
					&& opponentCoordinate.x() - ball.x() > -0.5 * CELL_LENGTH)
			{
				///cout<<"inside WhetherToTurnToOpponentGoal opponentCoordinate:"<<opponentCoordinate<<" ball: "<<ball<<endl;
				res = false;
			}

		}
	}
	return res;
}

float WorldModel::getDistanceOppenentToBall(int num)
{
	for (TPlayerSenseMap::iterator iter =
			messageParser.mOpponentSenseMap.begin();
			iter != messageParser.mOpponentSenseMap.end(); ++iter)
			{
		if ((*iter).second.unum == num)
		{
			return sqrt(
					(*iter).second.head.distance * (*iter).second.head.distance
							+ myDistanceToBall * myDistanceToBall
							- cos(
									fabs(
											(*iter).second.head.theta
													- GetMyAngleToBall()) * PI
											/ 180) * 2
									* (*iter).second.head.distance
									* myDistanceToBall);
		}
	}
	return 0;
}

Vector3 WorldModel::GetLastCyclesAverageBallCoordinateForRunFormation()
{
	return lastCyclesAverageBallCoordinateForRunFormation;
}

float WorldModel::GetDestinationMeToXAxisAngle(Vector3 destination)
{
	float destinationMeToXAxisAngle;
	if (destination.x() > myCoordinate.x())
	{
		destinationMeToXAxisAngle = atan(
				(destination.y()
						- myCoordinate.y()
								/ (destination.x() - myCoordinate.x()) )) * 180
				/ 3.14;
		///cout<<"11111111111111111111111111111111destinationMeToXAxisAngle: "<<destinationMeToXAxisAngle<<endl;
	}
	else if (destination.x() <= myCoordinate.x())
	{
		if (destination.y() > myCoordinate.y())
		{
			destinationMeToXAxisAngle = 180
					- atan(
							(destination.y()
									- myCoordinate.y()
											/ (destination.x()
													- myCoordinate.x()) )) * 180
							/ 3.14;
			///cout<<"22222222222222222222222destinationMeToXAxisAngle:  "<<destinationMeToXAxisAngle<<endl;
		}
		else if (destination.y() <= myCoordinate.y())
		{
			destinationMeToXAxisAngle = -180
					- atan(
							(destination.y()
									- myCoordinate.y()
											/ (destination.x()
													- myCoordinate.x()) )) * 180
							/ 3.14;
			///cout<<"333333333333333333333333destinationMeToXAxisAngle:   "<<destinationMeToXAxisAngle<<endl;
		}

	}
	return destinationMeToXAxisAngle;

}

float WorldModel::GetDestinationBallToXAxisAngle(Vector3 destination) ///add by gaojin
{
	float destinationBallToXAxisAngle;
	if (destination.x() > ballCoordinate.x())
	{
		destinationBallToXAxisAngle = atan(
				(destination.y()
						- ballCoordinate.y()
								/ (destination.x() - ballCoordinate.x()) ))
				* 180 / 3.14;
		///cout<<"11111111111111111111111111111111destinationMeToXAxisAngle: "<<destinationMeToXAxisAngle<<endl;
	}
	else if (destination.x() <= ballCoordinate.x())
	{
		if (destination.y() > ballCoordinate.y())
		{
			destinationBallToXAxisAngle = 180
					- atan(
							(destination.y()
									- ballCoordinate.y()
											/ (destination.x()
													- ballCoordinate.x()) ))
							* 180 / 3.14;
			///cout<<"22222222222222222222222destinationMeToXAxisAngle:  "<<destinationMeToXAxisAngle<<endl;
		}
		else if (destination.y() <= ballCoordinate.y())
		{
			destinationBallToXAxisAngle = -180
					- atan(
							(destination.y()
									- ballCoordinate.y()
											/ (destination.x()
													- ballCoordinate.x()) ))
							* 180 / 3.14;
			///cout<<"333333333333333333333333destinationMeToXAxisAngle:   "<<destinationMeToXAxisAngle<<endl;
		}

	}
	return destinationBallToXAxisAngle;
}

void WorldModel::updateLastCyclesAverageHorizontalTurnHeadAngle()
{
	static int point = 0;

	lastCyclesAverageHorizontalTurnHeadAngleArray[point % 5] =
			GetCurrentJointAngle(JID_HEAD_1);

	point++;

	float angle;
	for (int i = 0; i < LAST_CYCLES_OF_TURN_HEAD_ANGLE; i++)
	{
		angle += lastCyclesAverageHorizontalTurnHeadAngleArray[i];
		///cout<<"lastCyclesAverageHorizantalTurnHeadAngleArray["<<i<<"]:"<<lastCyclesAverageHorizontalTurnHeadAngleArray[i]<<endl;
	}
	lastCyclesAverageHorizontalTurnHeadAngle = angle / 5;
	///cout<<"QQQQQQQQQQQlastCyclesAverageHorizontalTurnHeadAngle:    "<<lastCyclesAverageHorizontalTurnHeadAngle<<endl;
}

float WorldModel::GetLastCyclesAverageHorizontalTurnHeadAngle()
{
	return lastCyclesAverageHorizontalTurnHeadAngle;
}
// an agent is to the ball.
float WorldModel::getClosenessToBallMeasure(int number) // Function for computing the adjusted distance for our team (in meters)
{
	VisionObject player;
	switch (number)
	{
	case 1:
		player = TMMT_1;
		break;
	case 2:
		player = TMMT_2;
		break;
	case 3:
		player = TMMT_3;
		break;
	case 4:
		player = TMMT_4;
		break;
	case 5:
		player = TMMT_5;
		break;
	case 6:
		player = TMMT_6;
		break;
	case 7:
		player = TMMT_7;
		break;
	case 8:
		player = TMMT_8;
		break;
	case 9:
		player = TMMT_9;
		break;
	case 10:
		player = TMMT_10;
		break;
	case 11:
		player = TMMT_11;
		break;
	default:
		cout << "some error in adjust!!!" << endl;
	}
	float agentDistToNearestPost;
	float ballDistToNearestPost;
	float agentDistanceToBall;
	Vector3 ball = GetLastCyclesAverageBallCoordinate();
	Vector3 agentCoordinate = GetNewTeammateCoordinate(number);

	// Goalie should not be closest if ball is not in own goal box
	if (number == 1 && !IsBallInMyOwnPenaltyArea())
	{
		return 1000;
	}
	// Adjustment value to add to distance agent is from ball
	float adjust = 0.0;
	// Agent has fallen but not right on top of ball
	agentDistanceToBall = GetDistanceBetweenTwoCoordinate(ball,
			agentCoordinate);
	if (PlayerWhetherFallDown(player) && agentDistanceToBall > 0.65)
	{
		adjust += 1.5; // Added distance for having fallen
	}
	// Ball is to the sides of the goals

	float halfGoalWidth = GetGoalWidth() / 2;
	float halfFieldLength = GetFieldLength() / 2;
	float halfFieldWidth = GetFieldWidth() / 2;

	Vector3 nearestPost;
	if (fabs(ball.y()) > halfGoalWidth)
	{
		// Ball close to own goal
		if (ball.x() < -halfFieldLength + (halfFieldWidth - halfGoalWidth))
		{
			if (ball.y() > 0)
			{
				nearestPost = Vector3(-halfFieldLength, halfGoalWidth, 0);
			}
			else
			{
				nearestPost = Vector3(-halfFieldLength, -halfGoalWidth, 0);
			}

			// Agent is in front of ball

			agentDistToNearestPost = sqrt(
					(agentCoordinate.x() - nearestPost.x())
							* (agentCoordinate.x() - nearestPost.x())
							+ (agentCoordinate.y() - nearestPost.y())
									* (agentCoordinate.y() - nearestPost.y()));
			ballDistToNearestPost = sqrt(
					(ball.x() - nearestPost.x()) * (ball.x() - nearestPost.x())
							+ (ball.y() - nearestPost.y())
									* (ball.y() - nearestPost.y()));

			if (agentDistToNearestPost > ballDistToNearestPost)
			{
				adjust += 1.0; // Added distance to walk around ball
			}
		}
		// Ball close to opponent’s goal
		else if (ball.x() > halfFieldLength - (halfFieldWidth - halfGoalWidth))
		{
			if (ball.y() > 0)
			{
				nearestPost = Vector3(halfFieldLength, halfGoalWidth, 0);
			}
			else
			{
				nearestPost = Vector3(halfFieldLength, -halfGoalWidth, 0);
			}

			// Agent is in front of ball
			agentDistToNearestPost = sqrt(
					(agentCoordinate.x() - nearestPost.x())
							* (agentCoordinate.x() - nearestPost.x())
							+ (agentCoordinate.y() - nearestPost.y())
									* (agentCoordinate.y() - nearestPost.y()));
			ballDistToNearestPost = sqrt(
					(ball.x() - nearestPost.x()) * (ball.x() - nearestPost.x())
							+ (ball.y() - nearestPost.y())
									* (ball.y() - nearestPost.y()));
			if (agentDistToNearestPost < ballDistToNearestPost)
			{
				adjust += 1.0; // Added distance to walk around ball
			}

		}
	}
	// Agent is in front of ball
	else if (agentCoordinate.x() >= ball.x())
	{
		adjust += 1.0; // Added distance to walk around ball
	}

	//cout <<"here is adjust::"<<adjust<<endl;
	return adjust;
}

