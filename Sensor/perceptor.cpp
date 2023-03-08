# include "perceptor.h"
# include "../Agent/agent.h"
using namespace Sensor;
extern Agent agent;
extern Hear CITHear;

Perceptor::Perceptor()
{
	InitVariable();

	SetupMapContainer();
}
void Perceptor::InitVariable()
{
	currentGameMode = PM_NONE;
	mTeamIndex = TI_NONE;
	gameTime = 0;
	serverTime = 0;
	hearmessagecount = 0;
	number = 0;
	vanguardNum = 0;
	opponentTeamName = "";

	bodyPartName[0] = "head";
	bodyPartName[1] = "rlowerarm";
	bodyPartName[2] = "llowerarm";
	bodyPartName[3] = "rfoot";
	bodyPartName[4] = "lfoot";

	for (int i = 0; i < 20; ++i)
	{
		myHearing[i].hearTime = 0;
		myHearing[i].direction = "";
		myHearing[i].words = "";
	}
	for (int i = 0; i <= PLAYERNUMBER; ++i)
	{
		opponentPlayer[i] = 0;
		teammate[i] = 0;
	}

	/** lr*/
	notHeardVanguardCount = 0;

	notHeardViceVanguard_1Count = 0;

	vanguardUseHalfStepWalk = false;

	//whetherCanTurnToOpponentGoal=true;
}

void Perceptor::SetupMapContainer()
{
	SetupJointIDMap();
	SetupFootIDMap();
	SetupVisionObjectMap();
	SetupVisionPlayerMap();
	SetupGameStateMap(TI_RIGHT);
}
void Perceptor::SetupJointIDMap()
{
#if 1
	mJointIDMap.clear();

	mJointIDMap["hj1"] = JID_HEAD_1;
	mJointIDMap["hj2"] = JID_HEAD_2;

	mJointIDMap["llj1"] = JID_LLEG_1;
	mJointIDMap["rlj1"] = JID_RLEG_1;
	mJointIDMap["llj2"] = JID_LLEG_2;
	mJointIDMap["rlj2"] = JID_RLEG_2;
	mJointIDMap["llj3"] = JID_LLEG_3;
	mJointIDMap["rlj3"] = JID_RLEG_3;
	mJointIDMap["llj4"] = JID_LLEG_4;
	mJointIDMap["rlj4"] = JID_RLEG_4;
	mJointIDMap["llj5"] = JID_LLEG_5;
	mJointIDMap["rlj5"] = JID_RLEG_5;
	mJointIDMap["llj6"] = JID_LLEG_6;
	mJointIDMap["rlj6"] = JID_RLEG_6;

	mJointIDMap["laj1"] = JID_LARM_1;
	mJointIDMap["raj1"] = JID_RARM_1;
	mJointIDMap["laj2"] = JID_LARM_2;
	mJointIDMap["raj2"] = JID_RARM_2;
	mJointIDMap["laj3"] = JID_LARM_3;
	mJointIDMap["raj3"] = JID_RARM_3;
	mJointIDMap["laj4"] = JID_LARM_4;
	mJointIDMap["raj4"] = JID_RARM_4;
#endif
}
void Perceptor::SetupFootIDMap()
{
	mFootIDMap["lf"] = FID_LEFT;
	mFootIDMap["rf"] = FID_RIGHT;
}
void Perceptor::SetupVisionObjectMap()
{
#if 1
	mVisionObjectMap.clear();

	mVisionObjectMap["F1L"] = VO_FLAG1_L;
	mVisionObjectMap["F1R"] = VO_FLAG1_R;
	mVisionObjectMap["F2L"] = VO_FLAG2_L;
	mVisionObjectMap["F2R"] = VO_FLAG2_R;

	mVisionObjectMap["G1L"] = VO_GOAL1_L;
	mVisionObjectMap["G1R"] = VO_GOAL1_R;
	mVisionObjectMap["G2L"] = VO_GOAL2_L;
	mVisionObjectMap["G2R"] = VO_GOAL2_R;

	mVisionObjectMap["B"] = VO_BALL;

	mVisionObjectMap["GLine_L"] = LI_GOAL_L; /// the goal line in left side
	mVisionObjectMap["GLine_R"] = LI_GOAL_R; /// the goal line in right side

	mVisionObjectMap["SLine_P"] = LI_SIDE_P; ///the side line ,in Y >0 side 
	mVisionObjectMap["SLine_N"] = LI_SIDE_N; ///the side line ,in Y<0 side

	mVisionObjectMap["PLine_L"] = LI_PENA_L; ///penalty area line,in left side
	mVisionObjectMap["PLine_R"] = LI_PENA_R; ///penalty area line,in right side

	mVisionObjectMap["PLine_1L"] = LI_PENA_SIDE1_L;
	mVisionObjectMap["PLine_2L"] = LI_PENA_SIDE2_L;

	mVisionObjectMap["PLine_1R"] = LI_PENA_SIDE1_R;
	mVisionObjectMap["PLine_2R"] = LI_PENA_SIDE2_R;

	mVisionObjectMap["MLine"] = LI_MID; ///middle line

#endif
}
void Perceptor::SetupVisionPlayerMap()
{
#if 1
	mVisionPlayerMap.clear();

	mVisionPlayerMap["Ptm1"] = TMMT_1;
	mVisionPlayerMap["Ptm2"] = TMMT_2;
	mVisionPlayerMap["Ptm3"] = TMMT_3;
	mVisionPlayerMap["Ptm4"] = TMMT_4;
	mVisionPlayerMap["Ptm5"] = TMMT_5;
	mVisionPlayerMap["Ptm6"] = TMMT_6;
	mVisionPlayerMap["Ptm7"] = TMMT_7;
	mVisionPlayerMap["Ptm8"] = TMMT_8;
	mVisionPlayerMap["Ptm9"] = TMMT_9;
	mVisionPlayerMap["Ptm10"] = TMMT_10;
	mVisionPlayerMap["Ptm11"] = TMMT_11;

	mVisionPlayerMap["Pop1"] = OPPO_1;
	mVisionPlayerMap["Pop2"] = OPPO_2;
	mVisionPlayerMap["Pop3"] = OPPO_3;
	mVisionPlayerMap["Pop4"] = OPPO_4;
	mVisionPlayerMap["Pop5"] = OPPO_5;
	mVisionPlayerMap["Pop6"] = OPPO_6;
	mVisionPlayerMap["Pop7"] = OPPO_7;
	mVisionPlayerMap["Pop8"] = OPPO_8;
	mVisionPlayerMap["Pop9"] = OPPO_9;
	mVisionPlayerMap["Pop10"] = OPPO_10;
	mVisionPlayerMap["Pop11"] = OPPO_11;
#endif
}
void Perceptor::SetupGameStateMap(TTeamIndex teamindex) //why here is teamindex but below is mTeamIndex?????????
{
	///////cout<<"mTeamIndex"<<endl;
	mPlayModeMap.clear();
	if (mTeamIndex == TI_LEFT)
	{
		///////cout<<"mTeamIndex==TI_LEFT"<<endl;
		mPlayModeMap["BeforeKickOff"] = PM_BeforeKickOff;

		mPlayModeMap["KickOff_Left"] = PM_KickOff_Our;

		mPlayModeMap["KickOff_Right"] = PM_KickOff_Opp;

		mPlayModeMap["PlayOn"] = PM_PlayOn;

		mPlayModeMap["KickIn_Left"] = PM_KickIn_Our;

		mPlayModeMap["KickIn_Right"] = PM_KickIn_Opp;

		mPlayModeMap["Goal_Left"] = PM_Goal_Our;

		mPlayModeMap["Goal_Right"] = PM_Goal_Opp;

		mPlayModeMap["GameOver"] = PM_GameOver;

		mPlayModeMap["corner_kick_left"] = PM_CORNER_KICK_Our;

		mPlayModeMap["corner_kick_right"] = PM_CORNER_KICK_Opp;

		mPlayModeMap["goal_kick_left"] = PM_GOAL_KICK_Our;

		mPlayModeMap["goal_kick_right"] = PM_GOAL_KICK_Opp;

		mPlayModeMap["free_kick_left"] = PM_FREE_KICK_Our;

		mPlayModeMap["free_kick_right"] = PM_FREE_KICK_Opp;
		return;

	}
	else
	{

		///////cout<<"mTeamIndex==TI_RIGHT"<<endl;

		mPlayModeMap["BeforeKickOff"] = PM_BeforeKickOff;

		mPlayModeMap["KickOff_Left"] = PM_KickOff_Opp;

		mPlayModeMap["KickOff_Right"] = PM_KickOff_Our;

		mPlayModeMap["PlayOn"] = PM_PlayOn;

		mPlayModeMap["KickIn_Left"] = PM_KickIn_Opp;

		mPlayModeMap["KickIn_Right"] = PM_KickIn_Our;

		mPlayModeMap["Goal_Left"] = PM_Goal_Opp;

		mPlayModeMap["Goal_Right"] = PM_Goal_Our;

		mPlayModeMap["GameOver"] = PM_GameOver;

		mPlayModeMap["corner_kick_left"] = PM_CORNER_KICK_Opp;

		mPlayModeMap["corner_kick_right"] = PM_CORNER_KICK_Our;

		mPlayModeMap["goal_kick_left"] = PM_GOAL_KICK_Opp;

		mPlayModeMap["goal_kick_right"] = PM_GOAL_KICK_Our;

		mPlayModeMap["free_kick_left"] = PM_FREE_KICK_Opp;

		mPlayModeMap["free_kick_right"] = PM_FREE_KICK_Our;
	}

	return;
}
//////////main////
void Perceptor::ParseMsg(string& input)
{
	ClearData();
	int pointer = 0; //pointer for Perceptors string
	int numm;
	while (true) //loop for parse entire Perceptors string
	{
		/*! if our pointer was longer than Perceptors string break pars*/
		if (((unsigned int) pointer > (input.length() - 1)))
			break;
		/**Time perceptor**/
		string result = getWord(pointer, input, false);
		if (result.compare("time") == 0)
		{
			result = getWord(pointer, input, false);
			serverTime = getNum(pointer, input);
			/////////////cout<<"serverTime :"<<serverTime<<endl;
		}
		/**Game state perceptor**/
		if (result.compare("GS") == 0)
		{
			result = getWord(pointer, input, false);
			if (result.compare("unum") == 0)
			{

				number = getNum(pointer, input);
				// ///////cout<<" set unum: "<<number<<endl;
				if (mTeamIndex == TI_NONE)
				{
					setTeamSide(pointer, input);
					SetupGameStateMap(mTeamIndex);
					//    ///////cout<<"set ti side"<<endl;
				}
				/////////////cout<<"my number :"<<number<<endl;
			}

		}
		if (result.compare("t") == 0)
					{
						gameTime = getNum(pointer, input);

						//  ///cout<<" game time :"<<gameTime<<endl;
					}
					/////////cout<<" game time :"<<gameTime<<endl;
		if (result.compare("sl") == 0)
					{
						numm = getNum(pointer, input);

						//  ///cout<<" game time :"<<gameTime<<endl;
					}
					/////////cout<<" game time :"<<gameTime<<endl;
		if (result.compare("sr") == 0)
					{
						numm = getNum(pointer, input);

						//  ///cout<<" game time :"<<gameTime<<endl;
					}
					/////////cout<<" game time :"<<gameTime<<endl;
		/**PlayMode perceptor**/
		if (result.compare("pm") == 0)
		{
			setPlayMode(pointer, input);
		}
		/**Gyroscope perceptor**/
		if (result.compare("GYR") == 0)
		{
			gyrSensor.x = getNum(pointer, input);
			gyrSensor.y = getNum(pointer, input);
			gyrSensor.z = getNum(pointer, input);
			/////////////cout<<"gyrSensor ("<<gyrSensor.x<<" , "<<gyrSensor.y<<" , "<<gyrSensor.z<<")"<<endl;
		}

		if (result.compare("ACC") == 0)
		{
			accSensor.x = getNum(pointer, input);
			accSensor.y = getNum(pointer, input);
			accSensor.z = getNum(pointer, input);
			///////////cout<<"ACCSensor  (   "<<accSensor.x<<"    ,    "<<accSensor.y<<"   ,   "<<accSensor.z<<"   )"<<endl;
		}
		/**See perceptor**/
		if (result.compare("See") == 0)
		{
			// /////cout<<"		see !!!"<<endl;
			mVisionSenseMap.clear(); //clear vision data of flags
			mTeamMateSenseMap.clear(); //clear vision data of my teammates
			mOpponentSenseMap.clear(); //clear vision data of my opponents
			clearLineRecord();
			mLineSenseMap.clear();
			std::string tmpString = "";
			do
			{
				if (result.compare("G1L") == 0)
				{
					setGoal(pointer, input, result);
				}
				else if (result.compare("G2L") == 0)
				{
					setGoal(pointer, input, result);
				}
				else if (result.compare("G2R") == 0)
				{
					setGoal(pointer, input, result);
				}
				else if (result.compare("G1R") == 0)
				{
					setGoal(pointer, input, result);
				}
				else if (result.compare("F1L") == 0)
				{
					setFlag(pointer, input, result);
				}
				else if (result.compare("F2L") == 0)
				{
					setFlag(pointer, input, result);
				}
				else if (result.compare("F1R") == 0)
				{
					setFlag(pointer, input, result);
				}
				else if (result.compare("F2R") == 0)
				{
					setFlag(pointer, input, result);
				}
				else if (result.compare("B") == 0)
				{
					setBall(pointer, input);
					// ///////cout<<"set ball"<<endl;
				}
				else if (result.compare("P") == 0)
				{
					setPlayer(pointer, input);
				}
				else if (result.compare("L") == 0)
				{
					recordLineInfo(pointer, input);
					// tmpString=getWord( pointer, input, false );
				}
				/// agar hinge joint o player ra getword kard  digar nabayad an ra getword kard

				//    if (tmpString != "HJ" && tmpString != "P"&& tmpString != "L"&& tmpString != "B"&&tmpString != "G1L"&&tmpString != "G2L"&&tmpString != "F1L"&&tmpString != "F2L") /// 
				//  {
				result = getWord(pointer, input, false);
				//	  tmpString="";
//		  /////////cout<<"result = getWord(pointer, input, false) :"<<result<<endl;
//	      }
//	      else
//	      {
//		  result = tmpString;
//		  tmpString="";
				/////////cout<<"result = tmpString :"<<result<<endl;
//	      }
			} while ((result.compare("HJ") != 0)
					&& ((unsigned int) pointer < input.length() - 1)); //end of See do

			recognizeWhichLine(); /// a see a lot of lines , i must recognize them.

		} //End of See If
		  //  ///////////cout<<"!!!!end while !!!"<<endl;
		/**frp perceptor**/
		if (result.compare("FRP") == 0)
		{
			result = getWord(pointer, input, false);
			result = getWord(pointer, input, false);
			if (result.compare("rf") == 0)
			{
				setFRP(pointer, input, result);
			}
			else if (result.compare("lf") == 0)
			{
				setFRP(pointer, input, result);
			}
		} //end of FRP if
		/**HingJoint perceptor**/
		if (result.compare("HJ") == 0)
		{
			result = getWord(pointer, input, false);
			result = getWord(pointer, input, false);
			setHJoint(pointer, input, result);
		} //end of HJ if

		if (result.compare("hear") == 0)
		{
			setHear(pointer, input, result);
		} //end of HJ if
	} //End of while
//cout<<"end prase"<<endl;
}

void Perceptor::ClearData()
{
	//clear FRP
	myFRPSenseMap[FID_LEFT].c.x = 0.0;
	myFRPSenseMap[FID_LEFT].c.y = 0.0;
	myFRPSenseMap[FID_LEFT].c.z = 0.0;

	myFRPSenseMap[FID_LEFT].f.x = 0.0;
	myFRPSenseMap[FID_LEFT].f.y = 0.0;
	myFRPSenseMap[FID_LEFT].f.z = 0.0;

	myFRPSenseMap[FID_RIGHT].c.x = 0.0;
	myFRPSenseMap[FID_RIGHT].c.y = 0.0;
	myFRPSenseMap[FID_RIGHT].c.z = 0.0;

	myFRPSenseMap[FID_RIGHT].f.x = 0.0;
	myFRPSenseMap[FID_RIGHT].f.y = 0.0;
	myFRPSenseMap[FID_RIGHT].f.z = 0.0;

	//clear hear counter
	hearmessagecount = 0;
	//
//	vanguardNum=0;
	CanGetVanPos = false;
	//
//	vanguardFallDown=false;

	mHearMessageVector.clear();
	//clear see
}

void Perceptor::OutputParseResult()
{
#if 0
	for( HearMessageVector::iterator iter=mHearMessageVector.begin();iter!=mHearMessageVector.end();++iter)
	{
		///////////////cout<<"hear --direction:"<<iter->direction<<" words:"<<iter->words<<endl;
	}
#endif
#if 0
	///////////////cout<<"-----------------parse message-----------------"<<endl;
	///////////////cout<<"serverTime: "<<serverTime<<" gameTime: "<<gameTime;
	///////////////cout<<" currentGameMode:"<<currentGameMode<<endl;
	///////////////cout<<"GYR: x:"<<gyrSensor.x<<" y: "<<gyrSensor.y<<" z: "<<gyrSensor.z<<endl<<endl;
	///////////////cout<<"----------------------vision part-----------------"<<endl;

	///////////////cout<<"left flag 1:"<<mVisionSenseMap[VO_FLAG1_L].distance<<"\t"<<mVisionSenseMap[VO_FLAG1_L].theta
	<<"\t"<<mVisionSenseMap[VO_FLAG1_L].phi<<endl;
	///////////////cout<<"left flag 2:"<<mVisionSenseMap[VO_FLAG2_L].distance<<"\t"<<mVisionSenseMap[VO_FLAG2_L].theta<<"\t"<<mVisionSenseMap[VO_FLAG2_L].phi<<endl;
	///////////////cout<<"right flag 1:"<<mVisionSenseMap[VO_FLAG1_R].distance<<"\t"<<mVisionSenseMap[VO_FLAG1_R].theta<<"\t"<<mVisionSenseMap[VO_FLAG1_R].phi<<endl;
	///////////////cout<<"right flag 2:"<<mVisionSenseMap[VO_FLAG2_R].distance<<"\t"<<mVisionSenseMap[VO_FLAG2_R].theta<<"\t"<<mVisionSenseMap[VO_FLAG2_R].phi<<endl;
	///////////////cout<<"left goal 1:"<<mVisionSenseMap[VO_GOAL1_L].distance<<"\t"<<mVisionSenseMap[VO_GOAL1_L].theta<<"\t"<<mVisionSenseMap[VO_GOAL1_L].phi<<endl;
	///////////////cout<<"left goal 2:"<<mVisionSenseMap[VO_GOAL2_L].distance<<"\t"<<mVisionSenseMap[VO_GOAL2_L].theta<<"\t"<<mVisionSenseMap[VO_GOAL2_L].phi<<endl;
	///////////////cout<<"right goal 1:"<<mVisionSenseMap[VO_GOAL1_R].distance<<"\t"<<mVisionSenseMap[VO_GOAL1_R].theta<<"\t"<<mVisionSenseMap[VO_GOAL1_R].phi<<endl;
	///////////////cout<<"right goal 2:"<<mVisionSenseMap[VO_GOAL2_R].distance<<"\t"<<mVisionSenseMap[VO_GOAL2_R].theta<<"\t"<<mVisionSenseMap[VO_GOAL2_R].phi<<endl;
	///////////////cout<<"ball:"<<mVisionSenseMap[VO_BALL].distance<<"\t"<<mVisionSenseMap[VO_BALL].theta<<"\t"<<mVisionSenseMap[VO_BALL].phi<<endl;	

	///////////////cout<<endl<<endl<<"-------------------FRP part-------------------"<<endl;

	///////////////cout<<"left foot: c:("<<myFRPSenseMap[FID_LEFT].c.x<<" , "<<myFRPSenseMap[FID_LEFT].c.y<<" , "<<myFRPSenseMap[FID_LEFT].c.z<<")";
	///////////////cout<<"f:("<<myFRPSenseMap[FID_LEFT].f.x<<" , "<<myFRPSenseMap[FID_LEFT].f.y<<" , "<<myFRPSenseMap[FID_LEFT].f.z<<")";
	///////////////cout<<endl;

	///////////////cout<<"right foot: c:("<<myFRPSenseMap[FID_RIGHT].c.x<<" , "<<myFRPSenseMap[FID_RIGHT].c.y<<" , "<<myFRPSenseMap[FID_RIGHT].c.z<<")";
	///////////////cout<<"f:("<<myFRPSenseMap[FID_RIGHT].f.x<<" , "<<myFRPSenseMap[FID_RIGHT].f.y<<" , "<<myFRPSenseMap[FID_RIGHT].f.z<<")";
	///////////////cout<<endl;

	///////////////cout<<"-------------------------jiont part------------------------"<<endl;
	///////////////cout<<"head 1:"<<GetCurrentJiontAngle(JID_HEAD_1)<<endl;
	///////////////cout<<"head 2:"<<GetCurrentJiontAngle(JID_HEAD_2)<<endl;
	///////////////cout<<"r ram 1:"<<GetCurrentJiontAngle(JID_RARM_1)<<endl;
	///////////////cout<<"r ram 2:"<<GetCurrentJiontAngle(JID_RARM_2)<<endl;
	///////////////cout<<"r ram 3:"<<GetCurrentJiontAngle(JID_RARM_3)<<endl;
	///////////////cout<<"r ram 4:"<<GetCurrentJiontAngle(JID_RARM_4)<<endl;
	///////////////cout<<"r leg 1:"<<GetCurrentJiontAngle(JID_RLEG_1)<<endl;
	///////////////cout<<"r leg 2:"<<GetCurrentJiontAngle(JID_RLEG_2)<<endl;
	///////////////cout<<"r leg 3:"<<GetCurrentJiontAngle(JID_RLEG_3)<<endl;
	///////////////cout<<"r leg 4:"<<GetCurrentJiontAngle(JID_RLEG_4)<<endl;
	///////////////cout<<"r leg 5:"<<GetCurrentJiontAngle(JID_RLEG_5)<<endl;
	///////////////cout<<"r leg 6:"<<GetCurrentJiontAngle(JID_RLEG_6)<<endl;
	///////////////cout<<"l ram 1:"<<GetCurrentJiontAngle(JID_LARM_1)<<endl;
	///////////////cout<<"l ram 2:"<<GetCurrentJiontAngle(JID_LARM_2)<<endl;
	///////////////cout<<"l ram 3:"<<GetCurrentJiontAngle(JID_LARM_3)<<endl;
	///////////////cout<<"l ram 4:"<<GetCurrentJiontAngle(JID_LARM_4)<<endl;
	///////////////cout<<"l leg 1:"<<GetCurrentJiontAngle(JID_LLEG_1)<<endl;
	///////////////cout<<"l leg 2:"<<GetCurrentJiontAngle(JID_LLEG_2)<<endl;
	///////////////cout<<"l leg 3:"<<GetCurrentJiontAngle(JID_LLEG_3)<<endl;
	///////////////cout<<"l leg 4:"<<GetCurrentJiontAngle(JID_LLEG_4)<<endl;
	///////////////cout<<"l leg 5:"<<GetCurrentJiontAngle(JID_LLEG_5)<<endl;
	///////////////cout<<"l leg 6:"<<GetCurrentJiontAngle(JID_LLEG_6)<<endl;
	///////////////cout<<"-----------------team index---------------------"<<endl;
	if(mTeamIndex == TI_LEFT)
	///////////////cout<<"my team index is left!"<<endl;
	else
	///////////////cout<<"my team index is right!"<<endl;
	/*
	 ///////////////cout<<"-----------------opponet player--------------"<<endl;
	 ///////////////cout<<"player id:1>>"<<mVisionSenseMap[OPPO_1].distance<<"\t"<<mVisionSenseMap[OPPO_1].theta<<"\t"<<mVisionSenseMap[OPPO_1].phi<<endl;
	 ///////////////cout<<"---------------team meate----------------"<<endl;
	 ///////////////cout<<"player id:5>>"<<mVisionSenseMap[TMMT_5].distance<<"\t"<<mVisionSenseMap[TMMT_5].theta<<"\t"<<mVisionSenseMap[TMMT_5].phi<<endl;*/

#endif
#if 0
	///////////////cout<<"-----------teammate------------"<<endl;
	///////////////cout<<"number of my teammates:"<<teammate[0]<<endl;
	for(int i=1;i<=11;++i)
	{
		if(teammate[i] == 1)
		///////////////cout<<"number:"<<i<<endl;
	}
	///////////////cout<<"-----------opponent team------------"<<endl;
	///////////////cout<<"number of opponent player:"<<opponentPlayer[0]<<endl;
	for(int i=1;i<=11;++i)
	{
		if(opponentPlayer[i] == 1)
		///////////////cout<<"number:"<<i<<endl;
	}
#endif
	//////////////////cout<<"=====================end======================="<<endl;
}

void Perceptor::ClearPlayerRecord()
{
	for (int i = 0; i <= PLAYERNUMBER; ++i)
	{
		opponentPlayer[i] = 0;
		teammate[i] = 0;
	}
}

THingeJointSenseMap Perceptor::GetCurrentJointMap()
{
	return mHingeJointSenseMap;
}

float Perceptor::GetCurrentJiontAngle(JointID J_ID)
{
	return mHingeJointSenseMap[J_ID].angle;
}
SGYRSensor Perceptor::GetGYR()
{
	return gyrSensor;
}

FRPerceptor Perceptor::GetFRP(FootID vo)
{
	return myFRPSenseMap[vo];
}

VisionSense Perceptor::GetVisionPolarCoordinate(VisionObject flagName)
{
	VisionSense vs;
	if (mVisionSenseMap.count(flagName))
	{
		vs = mVisionSenseMap[flagName];
	}

	return vs;
}
float Perceptor::GetServerTime()
{
	return serverTime;
}
float Perceptor::GetGameTime()
{
	return gameTime;
}
TPlayMode Perceptor::GetCurrentGameMode()
{
	return currentGameMode;
}
TTeamIndex Perceptor::GetMyTeamIndex()
{
	return mTeamIndex;
}
void Perceptor::ChangeMyTeamIndex()
{
	if(mTeamIndex==TI_LEFT)
	{
		mTeamIndex=TI_RIGHT;
	}
	else
	{
		mTeamIndex=TI_LEFT;
	}
}
string Perceptor::GetOpponetTeamName()
{
	return opponentTeamName;
}
int Perceptor::GetMyNumber()
{
	return number;
}

bool Perceptor::GetVanPos(Vector3 &vanpos) ///czg
{
	vanpos = VanPos;
	return CanGetVanPos;;
}
int Perceptor::GetVanguardNumber() ///add by czg
{
	return vanguardNum;
}
bool Perceptor::ParsevanguardNum() ///add by czg
{
	float myAngleToBall = GetVisionPolarCoordinate(VO_BALL).theta;
	float myDistanceToBall = GetVisionPolarCoordinate(VO_BALL).distance;
	float angle = 0, myAngleToAgent = 0, mindistance = 100.0f;

	for (TPlayerSenseMap::iterator iter = mTeamMateSenseMap.begin();
			iter != mTeamMateSenseMap.end(); ++iter)
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
						- cos(angle * PI_180) * 2 * myDistanceToBall
								* (*iter).second.head.distance);
		if (dis < mindistance)
		{
			mindistance = dis;
			vanguardNum = (*iter).second.unum;
		}
	}
	if (!mVisionSenseMap.count(VO_BALL))
		return false;
	return true;
//		/////////////cout<<"czg----vanguardNum:                   "<<vanguardNum<<endl;
}

bool Perceptor::GetIsVanguardStand()
{
	return isVanguardStand;
}
bool Perceptor::GetIsViceVanguard_1Stand()
{
	return isViceVanguard_1Stand;
}

void Perceptor::SetIsVanguardStand(bool stand)
{
	isVanguardStand = stand;
}
void Perceptor::SetIsViceVanguard_1Stand(bool stand)
{
	isViceVanguard_1Stand = stand;
}

int Perceptor::GetVanguardNumberByHear()
{
	return vanguardNumber;
}

int Perceptor::GetViceVanguard_1NumberByHear()
{
	return viceVanguard_1Number;
}

bool Perceptor::WhetherVanguardUseHalfStepWalk()
{
	return vanguardUseHalfStepWalk;
}

int Perceptor::GetHearVanguardNumber()
{
	return hearVanguardNumber;
}

void Perceptor::recordMyAroundInfo(char info)
{
	switch (info)
	{
	case '0':
		playerAroundMe = ARROUND_NULL;
		//  ///////////cout<<"ARROUND_NULL"<<endl;
		break;

	case '1':
		playerAroundMe = OPPONENT_FRONT;
		///////////cout<<"time :"<<gameTime<<"		OPPONENT_FRONT"<<endl;
		break;

	case '2':
		playerAroundMe = OPPONENT_LEFT;
		///////////cout<<"time :"<<gameTime<<"OPPONENT_LEFT"<<endl;
		break;

	case '3':
		playerAroundMe = OPPONENT_BACK;
		///////////cout<<"time :"<<gameTime<<"OPPONENT_BACK"<<endl;
		break;

	case '4':
		playerAroundMe = OPPONENT_RIGHT;
		///////////cout<<"time :"<<gameTime<<"OPPONENT_RIGHT"<<endl;
		break;

	case '5':
		playerAroundMe = TEAMMATE_FRONT;
		///////////cout<<"time :"<<gameTime<<"TEAMMATE_FRONT"<<endl;
		break;

	case '6':
		playerAroundMe = TEAMMATE_LEFT;
		///////////cout<<"time :"<<gameTime<<"TEAMMATE_LEFT"<<endl;
		break;

	case '7':
		playerAroundMe = TEAMMATE_BACK;
		///////////cout<<"time :"<<gameTime<<"TEAMMATE_BACK"<<endl;
		break;

	case '8':
		playerAroundMe = TEAMMATE_RIGHT;
		///////////cout<<"time :"<<gameTime<<"TEAMMATE_RIGHT"<<endl;
		break;

	default:
		playerAroundMe = ARROUND_NULL;
		// ///////////cout<<"ARROUND_NULL"<<endl;
	}
}
string Perceptor::getWord(int& pointer, string& input, bool let)
{
	string word(32, ' ');
	while ((!(isChar(input[pointer])))
			&& ((unsigned int) pointer < input.length()))
	{
		pointer++;
	}
	int index = 0;
	while (((input[pointer] != ' ' && input[pointer] != ')')
			|| (let && input[pointer] != ')'))
			&& ((unsigned int) pointer < input.length()))
	{
		word[index] = input[pointer];
		pointer++;
		index++;
	}
	word.resize(index);

	///////////cout<<"word :"<<word<<endl;
	return (word);
} //end of getWord

///this function return the value of one perceptor
//05
float Perceptor::getNum(int& pointer, string& input)
{
	while ((!(isNum(input[pointer]))) && (input[pointer] != '-')
			&& ((unsigned int) pointer < input.length()))
	{
		pointer++;
	}
	short int sign = 1;
	if (input[pointer] == '-')
	{
		pointer++;
		sign = -1;
	}

	float tempFloat = 0.0;
	float divPoint = 1.0;

	bool point = false;
	while ((isNum(input[pointer])) && ((unsigned int) pointer < input.length()))
	{
		if (input[pointer] == 46) // is .
		{
			point = true;
		}
		else
		{
			tempFloat = (tempFloat * 10.0) + (input[pointer] - 48);
			if (point == true)
			{
				divPoint *= 10.0;
			}
		}
		pointer++;
	}
	return (sign * tempFloat / divPoint);
} //end of getNum

void Perceptor::setTeamSide(int & pointer, string& input)
{
	std::string result = getWord(pointer, input, false);
	if (result == "team")
	{
		result = getWord(pointer, input, false);
		if (result == "left")
		{
			mTeamIndex = TI_LEFT;
			///////////cout<<"set TI_LEFT"<<endl;
		}
		else if (result == "right")
		{
			mTeamIndex = TI_RIGHT;
			///////////cout<<"set TI_RIGHT"<<endl;
		}
		else
		{
			mTeamIndex = TI_NONE;
			//  /////////cout<<"set TI_None"<<endl;
		}
	}
}

void Perceptor::setPlayMode(int& pointer, string& input)
{
	std::string PMName = getWord(pointer, input, false);
	///////cout<<"PMName:"<<PMName<<endl;
	TPlayModeMap::iterator iter = mPlayModeMap.find(PMName);
	if (iter == mPlayModeMap.end())
	{
		//std:://///////cout<<"Play Mode sense error"<<std::endl;
		return;
	}
	currentGameMode = (TPlayMode) (*iter).second;
	///////cout<<"currentGameMode :"<<currentGameMode<<endl;
}

void Perceptor::setFlag(int& pointer, string& input, string& name)
{
	// VisionSense sense;
	TVisionObjectMap::iterator iter = mVisionObjectMap.find(name);
	if (iter == mVisionObjectMap.end())
	{
		//std::///////////cout<<"Flags sense error"<<std::endl;
		return;
	}
	VisionObject VO = (*iter).second;

	mVisionSenseMap[VO].distance = getNum(pointer, input);
	mVisionSenseMap[VO].theta = getNum(pointer, input);
	mVisionSenseMap[VO].phi = getNum(pointer, input);
	mVisionSenseMap[VO].senseTime = gameTime;
	mVisionSenseMap[VO].updated = true;

	///////////cout<<"name "<<name<<"	("<<mVisionSenseMap[VO].distance<<" , "<<mVisionSenseMap[VO].theta<<" , "<<mVisionSenseMap[VO].phi<<endl;

}

void Perceptor::setGoal(int& pointer, string& input, string& name)
{
	// VisionSense sense;
	TVisionObjectMap::iterator iter = mVisionObjectMap.find(name);
	if (iter == mVisionObjectMap.end())
	{
		//std:://///////cout<<"Goal Flags sense error"<<std::endl;
		return;
	}
	VisionObject VO = (*iter).second;
	mVisionSenseMap[VO].distance = getNum(pointer, input);
	mVisionSenseMap[VO].theta = getNum(pointer, input);
	mVisionSenseMap[VO].phi = getNum(pointer, input);
	mVisionSenseMap[VO].senseTime = gameTime;
	mVisionSenseMap[VO].updated = true;

	// mVisionSenseMap[VO].theta=getMyAngleToFlag(VO);   /// to the real horiz angle 

	// /////////cout<<"name "<<name<<"	("<<mVisionSenseMap[VO].distance<<" , "<<mVisionSenseMap[VO].theta<<" , "<<mVisionSenseMap[VO].phi<<endl;
}

void Perceptor::setBall(int& pointer, string& input)
{
	// VisionSense sense;
	string name = "B";

	///////cout<<"enter setBall(int& pointer, string& input)"<<endl;

	TVisionObjectMap::iterator iter = mVisionObjectMap.find(name);
	if (iter == mVisionObjectMap.end())
	{
		///////cout<<"Ball sense error"<<std::endl;
		return;
	}

	VisionObject VO = (*iter).second;
	mVisionSenseMap[VO].distance = getNum(pointer, input);
	mVisionSenseMap[VO].theta = getNum(pointer, input);
	mVisionSenseMap[VO].phi = getNum(pointer, input);
	mVisionSenseMap[VO].senseTime = gameTime;
	mVisionSenseMap[VO].updated = true;

	//mVisionSenseMap[VO].theta=getMyAngleToFlag(VO);   /// to the real horiz angle 

	///////cout<<"name "<<name<<"	theta: "<<mVisionSenseMap[VO].theta<<endl;
	///////cout<<"name "<<name<<"	phi: "<<mVisionSenseMap[VO].phi<<endl;
	///////cout<<"name "<<name<<"	distance: "<<mVisionSenseMap[VO].distance<<endl;
	///////cout<<"name "<<name<<"	senseTime: "<<mVisionSenseMap[VO].senseTime<<endl;
}

void Perceptor::setPlayer(int& pointer, string& input)
{

	ClearPlayerRecord();
	std::string teamName;
	stringstream playerName;
	int id;

	std::string tmpPerceptors = "";

	getWord(pointer, input, false);
	teamName = getWord(pointer, input, false);

	id = (int) getNum(pointer, input);

	bool isMyTeammate = true;

	if (teamName != agent.GetTeamName())
	{
		isMyTeammate = false;
		opponentTeamName = teamName;
		playerName << "op";
		playerName << id;
		opponentPlayer[id] = 1;
		opponentPlayer[0]++;
		/////////////cout<<"opp-"<<id;
	}
	else
	{
		playerName << "tm";
		playerName << id;
		teammate[id] = 1;
		teammate[0]++;

		/////////////cout<<"teamate 	"<<id;
	}
	string name;
	name = 'P' + playerName.str();
	playerName.str("");

	TVisionPlayerMap::iterator iter = mVisionPlayerMap.find(name);
	if (iter == mVisionPlayerMap.end())
	{
		/////////////cout<<"Find Player Error!"<<endl;
		return;
	}

	VisionObject vo = (*iter).second;

	PlayerVisionInfo playerPos;
	int lastPoint;
	do
	{
		///head perceptors
		if (tmpPerceptors == "head")
		{

			playerPos.head.distance = getNum(pointer, input);
			playerPos.head.theta = getNum(pointer, input);
			playerPos.head.phi = getNum(pointer, input);
			playerPos.head.updated = true;
			playerPos.head.senseTime = gameTime;
		}
		///right arm perceptors	      

		else if (tmpPerceptors == "rlowerarm")
		{
			playerPos.rLowerArm.distance = getNum(pointer, input);
			playerPos.rLowerArm.theta = getNum(pointer, input);
			playerPos.rLowerArm.phi = getNum(pointer, input);
			playerPos.rLowerArm.updated = true;
			playerPos.rLowerArm.senseTime = gameTime;

		}

		///left arm perceptors

		else if (tmpPerceptors == "llowerarm")
		{
			playerPos.lLowerArm.distance = getNum(pointer, input);
			playerPos.lLowerArm.theta = getNum(pointer, input);
			playerPos.lLowerArm.phi = getNum(pointer, input);
			playerPos.lLowerArm.updated = true;
			playerPos.lLowerArm.senseTime = gameTime;

		}

		///right foot perceptors
		else if (tmpPerceptors == "rfoot")
		{
			playerPos.rFoot.distance = getNum(pointer, input);
			playerPos.rFoot.theta = getNum(pointer, input);
			playerPos.rFoot.phi = getNum(pointer, input);
			playerPos.rFoot.updated = true;
			playerPos.rFoot.senseTime = gameTime;

		}

		///left foot perceptors

		else if (tmpPerceptors == "lfoot")
		{
			playerPos.lFoot.distance = getNum(pointer, input);
			playerPos.lFoot.theta = getNum(pointer, input);
			playerPos.lFoot.phi = getNum(pointer, input);
			playerPos.lFoot.updated = true;
			playerPos.lFoot.senseTime = gameTime;

		}
		lastPoint = pointer;
		tmpPerceptors = getWord(pointer, input, false);
	} while (((tmpPerceptors.compare("head") == 0)
			|| (tmpPerceptors.compare("rlowerarm") == 0)
			|| (tmpPerceptors.compare("llowerarm") == 0)
			|| (tmpPerceptors.compare("rfoot") == 0)
			|| (tmpPerceptors.compare("lfoot") == 0))
			&& ((unsigned int) pointer < input.length() - 1)); //end of See do

	pointer = lastPoint; ///go to last pointer

	if (isMyTeammate)
	{
		mTeamMateSenseMap[vo] = playerPos;
		mTeamMateSenseMap[vo].teamName = teamName;
		mTeamMateSenseMap[vo].unum = id;
		mTeamMateSenseMap[vo].senseTime = gameTime;
		// ///cout<<"teamname :"<<mTeamMateSenseMap[vo].teamName<<"num :"<<mTeamMateSenseMap[vo].unum<<"head dis :"<<mTeamMateSenseMap[vo].head.distance<<endl;
	}
	else
	{
		mOpponentSenseMap[vo] = playerPos;
		mOpponentSenseMap[vo].teamName = teamName;
		mOpponentSenseMap[vo].unum = id;
		mOpponentSenseMap[vo].senseTime = gameTime;

		/////////////cout<<"teamname :"<<mOpponentSenseMap[vo].teamName<<"num :"<<mOpponentSenseMap[vo].unum<<"head dis :"<<mOpponentSenseMap[vo].head.distance<<endl;

	}
	//return tmpPerceptors;
}

void Perceptor::setFRP(int& pointer, string& input, string& name)
{
	/////////////cout<<"frp name:"<<name<<endl;
	TFootIDMap::iterator iter = mFootIDMap.find(name);

	if (iter == mFootIDMap.end())
	{
		//std:://///////cout<<"FRP sense error"<<std::endl;
		return;
	}
	FootID FRP = (*iter).second;
	myFRPSenseMap[FRP].c.x = getNum(pointer, input);
	myFRPSenseMap[FRP].c.y = getNum(pointer, input);
	myFRPSenseMap[FRP].c.z = getNum(pointer, input);
	myFRPSenseMap[FRP].f.x = getNum(pointer, input);
	myFRPSenseMap[FRP].f.y = getNum(pointer, input);
	myFRPSenseMap[FRP].f.z = getNum(pointer, input);

	/////////cout<<(*iter).first<<"  ("<<myFRPSenseMap[FRP].f.x<<" , "<<myFRPSenseMap[FRP].f.y<<" , "<<myFRPSenseMap[FRP].f.z<<" )"<<endl;

}

bool Perceptor::isChar(char chr)
{
	if (((chr >= 65) && (chr <= 90)) || //A..Z
			(((chr >= 97) && (chr <= 122))) || //a..z
			(chr == 95)) // _
	{
		return true;
	}
	else
		return false;
} //end of isChar

bool Perceptor::isNum(char chr)
{
	if (((chr >= 48) && (chr <= 57)) || //0..9
			(chr == 46)) // .
	{
		return true;
	}
	else
		return false;
} //end of isNum

void Perceptor::setHJoint(int& pointer, string& input, string& name)
{
	TJointIDMap::iterator iter = mJointIDMap.find(name);
	if (iter == mJointIDMap.end())
	{
		//  std:://///////cout<<"HJoint sense error"<<std::endl;
		return;
	}
	JointID VO = (*iter).second;
	mHingeJointSenseMap[VO].angle = getNum(pointer, input);
//  ///cout<<" "<<name<<":"<<mHingeJointSenseMap[VO].angle;
}

void Perceptor::setHear(int& pointer, string& input, string& name)
{
	string hearteamname= getWord(pointer, input, false);
	float hearTime = getNum(pointer, input);
	if (input[pointer + 1] == 's')
	{
		name = getWord(pointer, input, false);

		// /////////cout<<"hear myself!!! next:"<<result<<endl;
		name = getWord(pointer, input, false);

		///cout<<" time :"<<gameTime<<" hear time :"<<name<<endl;
		CITHear.ParseMyHearInfo(name);

		///////////cout<<"hear myself!!! next:"<<name<<endl;
	}
	else
	{
		stringstream aa("");
		HearingSense hearMsg;
		hearMsg.hearTime = hearTime;
		aa << getNum(pointer, input);
		hearMsg.direction = aa.str();
		hearMsg.words = getWord(pointer, input, false);
		mHearMessageVector.push_back(hearMsg);
		CITHear.ParseHearInfo(hearMsg.words);
		///////////cout<<"hearMsg.direction :"<<hearMsg.direction<<"	hearMsg.hearTime :"<<hearMsg.hearTime<<" hearMsg.words :"<<hearMsg.words<<endl;
	}
}

void Perceptor::clearLineRecord()
{

	for (int i = 0; i < 21; i++)
	{
		lineRecord[i].distance1 = 0;
		lineRecord[i].distance2 = 0;
		lineRecord[i].theta1 = 0;
		lineRecord[i].theta2 = 0;
		lineRecord[i].phi1 = 0;
		lineRecord[i].phi2 = 0;
		lineRecord[i].updated = false;
		lineRecord[i].senseTime = 0;
	}
}

void Perceptor::recordLineInfo(int& pointer, string& input)
{
	for (int i = 0; i < 21; i++)
	{
		if (lineRecord[i].updated == false)
		{
			lineRecord[i].distance1 = getNum(pointer, input);
			lineRecord[i].theta1 = getNum(pointer, input);
			lineRecord[i].phi1 = getNum(pointer, input);

			lineRecord[i].distance2 = getNum(pointer, input);
			lineRecord[i].theta2 = getNum(pointer, input);
			lineRecord[i].phi2 = getNum(pointer, input);

			lineRecord[i].updated = true;
			lineRecord[i].senseTime = gameTime;
			//  /////////cout<<"record line point1  ("<<lineRecord[i].distance1<<" , "<<lineRecord[i].theta1<<" , "<<lineRecord[i].phi1<<" )";
			///////////cout<<"  ("<<lineRecord[i].distance2<<" , "<<lineRecord[i].theta2<<" , "<<lineRecord[i].phi2<<" )"<<endl;
			return;
		}
	}
}

void Perceptor::recognizeWhichLine() ///recognize the Line by flags,only includes P N GL GR lines 
{
	if (lineRecord[1].updated == false) /// i only saw one line, only one line seems useless
	{
		return;
	}
#if 1
	if (mVisionSenseMap[VO_FLAG1_R].updated == true) /// when i saw flag 1 right
	{
		for (int i = 0; lineRecord[i].updated == true; i++) ///each line i saw 
				{
			if (lineRecord[i].senseTime == 0)
			{
				continue;
			}
			if (abs(mVisionSenseMap[VO_FLAG1_R].theta - lineRecord[i].theta1)
					< 0.3
					&& fabs(
							mVisionSenseMap[VO_FLAG1_R].distance
									- lineRecord[i].distance1) < 0.13)
			{
				if (lineRecord[i].theta2 > mVisionSenseMap[VO_FLAG1_R].theta)
				{
					mLineSenseMap[LI_SIDE_P] = lineRecord[i];
					mLineSenseMap[LI_SIDE_P].updated = true;
					lineRecord[i].senseTime = 0; /// next time i will not scan this line by this value
// 				  /////cout<<"line :"<<lineRecord[i].distance1<<","<<lineRecord[i].theta1<<","<<lineRecord[i].phi1<<"  is :"<<"LI_SIDE_P"<<endl;
				}
				else /// it is the goal line!
				{

					mLineSenseMap[LI_GOAL_R] = lineRecord[i];
					mLineSenseMap[LI_GOAL_R].updated = true;
					lineRecord[i].senseTime = 0;
// 				/////cout<<"line :"<<lineRecord[i].distance1<<","<<lineRecord[i].theta1<<","<<lineRecord[i].phi1<<"  is :"<<"LI_GOAL_R"<<endl;
				}
			}
			if (abs(mVisionSenseMap[VO_FLAG1_R].theta - lineRecord[i].theta2)
					< 0.3
					&& fabs(
							mVisionSenseMap[VO_FLAG1_R].distance
									- lineRecord[i].distance2) < 0.13)
			{
				/// if its second side 's angle > flag angle. oh it is the side line 
				if (lineRecord[i].theta1 > mVisionSenseMap[VO_FLAG1_R].theta)
				{
					mLineSenseMap[LI_SIDE_P] = lineRecord[i];
					mLineSenseMap[LI_SIDE_P].updated = true;
					lineRecord[i].senseTime = 0;
// 				/////cout<<"line :"<<lineRecord[i].distance1<<","<<lineRecord[i].theta1<<","<<lineRecord[i].phi1<<"  is :"<<"LI_SIDE_P"<<endl;
				}
				else /// it is the goal line!
				{
					mLineSenseMap[LI_GOAL_R] = lineRecord[i];
					lineRecord[i].senseTime = 0;
					mLineSenseMap[LI_GOAL_R].updated = true;
// 				/////cout<<"line :"<<lineRecord[i].distance1<<","<<lineRecord[i].theta1<<","<<lineRecord[i].phi1<<"  is :"<<"LI_GOAL_R"<<endl;
				}
			}
		}
	}

	if (mVisionSenseMap[VO_FLAG2_R].updated == true) /// when i saw flag 2 right
	{
		for (int i = 0; lineRecord[i].updated == true; i++) ///each line i saw 
				{
			if (lineRecord[i].senseTime == 0)
			{
				continue;
			}
			if (abs(mVisionSenseMap[VO_FLAG2_R].theta - lineRecord[i].theta1)
					< 0.3
					&& fabs(
							mVisionSenseMap[VO_FLAG2_R].distance
									- lineRecord[i].distance1) < 0.13)
			{
				if (lineRecord[i].theta2 > mVisionSenseMap[VO_FLAG2_R].theta)
				{
					if (mLineSenseMap[LI_GOAL_R].updated == false)
					{
						mLineSenseMap[LI_GOAL_R] = lineRecord[i];
						mLineSenseMap[LI_GOAL_R].updated = true;
						lineRecord[i].senseTime = 0;

					}
//				/////cout<<"line :"<<lineRecord[i].distance1<<","<<lineRecord[i].theta1<<","<<lineRecord[i].phi1<<"  is :"<<"LI_GOAL_R"<<endl;
				}
				else /// it is the goal line!
				{
					if (mLineSenseMap[LI_SIDE_N].updated == false)
					{
						mLineSenseMap[LI_SIDE_N] = lineRecord[i];
						mLineSenseMap[LI_SIDE_N].updated = true;
						lineRecord[i].senseTime = 0;
					}
//				/////cout<<"line :"<<lineRecord[i].distance1<<","<<lineRecord[i].theta1<<","<<lineRecord[i].phi1<<"  is :"<<"LI_SIDE_N"<<endl;
				}
			}
			if (abs(mVisionSenseMap[VO_FLAG2_R].theta - lineRecord[i].theta2)
					< 0.3
					&& fabs(
							mVisionSenseMap[VO_FLAG2_R].distance
									- lineRecord[i].distance2) < 0.13)
			{
				/// if its second side 's angle > flag angle. oh it is the side line 
				if (lineRecord[i].theta1 > mVisionSenseMap[VO_FLAG2_R].theta)
				{
					if (mLineSenseMap[LI_GOAL_R].updated == false)
					{
						mLineSenseMap[LI_GOAL_R] = lineRecord[i];
						mLineSenseMap[LI_GOAL_R].updated = true;
						lineRecord[i].senseTime = 0;
					}
//				/////cout<<"line :"<<lineRecord[i].distance1<<","<<lineRecord[i].theta1<<","<<lineRecord[i].phi1<<"  is :"<<"LI_GOAL_R"<<endl;
				}
				else /// it is the goal line!
				{
					if (mLineSenseMap[LI_SIDE_N].updated == false)
					{
						mLineSenseMap[LI_SIDE_N] = lineRecord[i];
						mLineSenseMap[LI_SIDE_N].updated = true;
						lineRecord[i].senseTime = 0;
					}
//				/////cout<<"line :"<<lineRecord[i].distance1<<","<<lineRecord[i].theta1<<","<<lineRecord[i].phi1<<"  is :"<<"LI_SIDE_N"<<endl;
				}
			}
		}
	}

	if (mVisionSenseMap[VO_FLAG1_L].updated == true) /// when i saw flag 1 left
	{

		for (int i = 0; lineRecord[i].updated == true; i++) ///each line i saw 
				{
			if (lineRecord[i].senseTime == 0)
			{
				continue;
			}
			if (abs(mVisionSenseMap[VO_FLAG1_L].theta - lineRecord[i].theta1)
					< 0.3
					&& fabs(
							mVisionSenseMap[VO_FLAG1_L].distance
									- lineRecord[i].distance1) < 0.13)
			{
				if (lineRecord[i].theta2 > mVisionSenseMap[VO_FLAG1_L].theta)
				{
					if (mLineSenseMap[LI_GOAL_L].updated == false)
					{
						mLineSenseMap[LI_GOAL_L] = lineRecord[i];
						mLineSenseMap[LI_GOAL_L].updated = true;
						lineRecord[i].senseTime = 0;
					}
					/////////cout<<"line :"<<lineRecord[i].distance1<<","<<lineRecord[i].theta1<<","<<lineRecord[i].phi1<<"  is :"<<"LI_GOAL_L"<<endl;
				}
				else /// it is the goal line!
				{
					if (mLineSenseMap[LI_SIDE_P].updated == false)
					{
						mLineSenseMap[LI_SIDE_P] = lineRecord[i];
						mLineSenseMap[LI_SIDE_P].updated = true;
						lineRecord[i].senseTime = 0;
					}
					/////////cout<<"line :"<<lineRecord[i].distance1<<","<<lineRecord[i].theta1<<","<<lineRecord[i].phi1<<"  is :"<<"LI_SIDE_P"<<endl;
				}
			}
			if (abs(mVisionSenseMap[VO_FLAG1_L].theta - lineRecord[i].theta2)
					< 0.3
					&& fabs(
							mVisionSenseMap[VO_FLAG1_L].distance
									- lineRecord[i].distance2) < 0.13)
			{
				/// if its second side 's angle > flag angle. oh it is the side line 
				if (lineRecord[i].theta1 > mVisionSenseMap[VO_FLAG1_L].theta)
				{
					if (mLineSenseMap[LI_GOAL_L].updated == false)
					{
						mLineSenseMap[LI_GOAL_L] = lineRecord[i];
						mLineSenseMap[LI_GOAL_L].updated = true;
						lineRecord[i].senseTime = 0;
					}
					/////////cout<<"line :"<<lineRecord[i].distance1<<","<<lineRecord[i].theta1<<","<<lineRecord[i].phi1<<"  is :"<<"LI_GOAL_L"<<endl;
				}
				else /// it is the goal line!
				{
					if (mLineSenseMap[LI_SIDE_P].updated == false)
					{
						mLineSenseMap[LI_SIDE_P] = lineRecord[i];
						mLineSenseMap[LI_SIDE_P].updated = true;
						lineRecord[i].senseTime = 0;
					}
					/////////cout<<"line :"<<lineRecord[i].distance1<<","<<lineRecord[i].theta1<<","<<lineRecord[i].phi1<<"  is :"<<"LI_SIDE_P"<<endl;
				}
			}
		}
	}

	if (mVisionSenseMap[VO_FLAG2_L].updated == true) /// when i saw flag 2 left
	{

		for (int i = 0; lineRecord[i].updated == true; i++) ///each line i saw 
				{
			if (lineRecord[i].senseTime == 0)
			{
				continue;
			}
			if (abs(mVisionSenseMap[VO_FLAG2_L].theta - lineRecord[i].theta1)
					< 0.3
					&& fabs(
							mVisionSenseMap[VO_FLAG2_L].distance
									- lineRecord[i].distance1) < 0.13)
			{
				if (lineRecord[i].theta2 < mVisionSenseMap[VO_FLAG2_L].theta)
				{
					if (mLineSenseMap[LI_GOAL_L].updated == false)
					{
						mLineSenseMap[LI_GOAL_L] = lineRecord[i];
						mLineSenseMap[LI_GOAL_L].updated = true;
						lineRecord[i].senseTime = 0;
					}
					/////////cout<<"line :"<<lineRecord[i].distance1<<","<<lineRecord[i].theta1<<","<<lineRecord[i].phi1<<"  is :"<<"LI_GOAL_L"<<endl;
				}
				else /// it is the goal line!
				{
					if (mLineSenseMap[LI_SIDE_N].updated == false)
					{
						mLineSenseMap[LI_SIDE_N] = lineRecord[i];
						mLineSenseMap[LI_SIDE_N].updated = true;
						lineRecord[i].senseTime = 0;
					}
					/////////cout<<"line :"<<lineRecord[i].distance1<<","<<lineRecord[i].theta1<<","<<lineRecord[i].phi1<<"  is :"<<"LI_SIDE_N"<<endl;
				}
			}
			if (abs(mVisionSenseMap[VO_FLAG2_L].theta - lineRecord[i].theta2)
					< 0.3
					&& fabs(
							mVisionSenseMap[VO_FLAG2_L].distance
									- lineRecord[i].distance2) < 0.13)
			{
				/// if its second side 's angle > flag angle. oh it is the side line 
				if (lineRecord[i].theta1 < mVisionSenseMap[VO_FLAG2_L].theta)
				{
					if (mLineSenseMap[LI_GOAL_L].updated == false)
					{
						mLineSenseMap[LI_GOAL_L] = lineRecord[i];
						mLineSenseMap[LI_GOAL_L].updated = true;
						lineRecord[i].senseTime = 0;
					}
					/////////cout<<"line :"<<lineRecord[i].distance1<<","<<lineRecord[i].theta1<<","<<lineRecord[i].phi1<<"  is :"<<"LI_GOAL_L"<<endl;
				}
				else /// it is the goal line!
				{
					if (mLineSenseMap[LI_SIDE_N].updated == false)
					{
						mLineSenseMap[LI_SIDE_N] = lineRecord[i];
						mLineSenseMap[LI_SIDE_N].updated = true;
						lineRecord[i].senseTime = 0;
					}
					/////////cout<<"line :"<<lineRecord[i].distance1<<","<<lineRecord[i].theta1<<","<<lineRecord[i].phi1<<"  is :"<<"LI_SIDE_N"<<endl;
				}
			}
		}
	}
#endif
#if 1
	///use flag vo_goal1_r to recognize the lines
	if (mLineSenseMap[LI_GOAL_R].updated == false)
	{
		if ((mVisionSenseMap[VO_GOAL1_R].updated == true
				&& mVisionSenseMap[VO_GOAL2_R].updated == false)
				|| (mVisionSenseMap[VO_GOAL1_R].updated == true
						&& mVisionSenseMap[VO_GOAL2_R].updated == true
						&& (mVisionSenseMap[VO_GOAL1_R].distance
								< mVisionSenseMap[VO_GOAL2_R].distance)))
		{
			/////////cout<<"use VO_GOAL1_R!!!"<<endl;
			int maybeGoalLineMark = 0;
// 			int maybePenaltyLine_1_Mark=0;
// 			int maybePenaltyLine_2_Mark=0;
			for (int i = 0; lineRecord[i].updated == true; i++) ///each line i saw 
					{
				if (lineRecord[i].senseTime == 0)
				{
					continue;
				}
				float lineLength =
						sqrt(
								lineRecord[i].distance1
										* lineRecord[i].distance1
										+ lineRecord[i].distance2
												* lineRecord[i].distance2
										- 2 * lineRecord[i].distance1
												* lineRecord[i].distance2
												* cos(
														fabs(
																lineRecord[i].theta1
																		- lineRecord[i].theta2)
																* PI_180));
				float linePartLength1 =
						sqrt(
								lineRecord[i].distance1
										* lineRecord[i].distance1
										+ mVisionSenseMap[VO_GOAL1_R].distance
												* mVisionSenseMap[VO_GOAL1_R].distance
										- 2
												* mVisionSenseMap[VO_GOAL1_R].distance
												* lineRecord[i].distance1
												* cos(
														fabs(
																mVisionSenseMap[VO_GOAL1_R].theta
																		- lineRecord[i].theta1)
																* PI_180));
				float linePartLength2 =
						sqrt(
								lineRecord[i].distance2
										* lineRecord[i].distance2
										+ mVisionSenseMap[VO_GOAL1_R].distance
												* mVisionSenseMap[VO_GOAL1_R].distance
										- 2
												* mVisionSenseMap[VO_GOAL1_R].distance
												* lineRecord[i].distance2
												* cos(
														fabs(
																mVisionSenseMap[VO_GOAL1_R].theta
																		- lineRecord[i].theta2)
																* PI_180));
				/////////cout<<"lineLength  :"<<lineLength<<"  linePartLength1 :"<<linePartLength1<<"  linePartLength2 :"<<linePartLength2<<endl;
				if (fabs(lineLength - linePartLength2 - linePartLength1) < 0.3) ///maybe i saw the goal line
				{
					if (mLineSenseMap[LI_GOAL_R].updated == false)
					{
						mLineSenseMap[LI_GOAL_R] = lineRecord[i];
						mLineSenseMap[LI_GOAL_R].updated = true;
						lineRecord[i].senseTime = 0;
						maybeGoalLineMark++;
						/////////cout<<"recognize goal line R (by vo_goal1_r):"<<i<<endl;
					}
				}
			}
			if (maybeGoalLineMark >= 2) /// two or more goal lines,it must be something wrong,must not use  
			{
				mLineSenseMap[LI_GOAL_R].distance1 = 0;
				mLineSenseMap[LI_GOAL_R].distance2 = 0;
				mLineSenseMap[LI_GOAL_R].phi1 = 0;
				mLineSenseMap[LI_GOAL_R].phi2 = 0;
				mLineSenseMap[LI_GOAL_R].theta1 = 0;
				mLineSenseMap[LI_GOAL_R].theta2 = 0;
				mLineSenseMap[LI_GOAL_R].updated = false;
				mLineSenseMap[LI_GOAL_R].senseTime = 0;
				/////////cout<<"two or more goal lines,it must be something wrong,must not use"<<endl;
			}
		}
		else if ((mVisionSenseMap[VO_GOAL1_R].updated == false
				&& mVisionSenseMap[VO_GOAL2_R].updated == true)
				|| (mVisionSenseMap[VO_GOAL1_R].updated == true
						&& mVisionSenseMap[VO_GOAL2_R].updated == true
						&& (mVisionSenseMap[VO_GOAL1_R].distance
								> mVisionSenseMap[VO_GOAL2_R].distance)))
		{
			/////////cout<<"use VO_GOAL2_R!!!"<<endl;
			int maybeGoalLineMark = 0;
// 			int maybePenaltyLine_1_Mark=0;
// 			int maybePenaltyLine_2_Mark=0;
			for (int i = 0; lineRecord[i].updated == true; i++) ///each line i saw 
					{
				if (lineRecord[i].senseTime == 0)
				{
					continue;
				}
				float lineLength =
						sqrt(
								lineRecord[i].distance1
										* lineRecord[i].distance1
										+ lineRecord[i].distance2
												* lineRecord[i].distance2
										- 2 * lineRecord[i].distance1
												* lineRecord[i].distance2
												* cos(
														fabs(
																lineRecord[i].theta1
																		- lineRecord[i].theta2)
																* PI_180));
				float linePartLength1 =
						sqrt(
								lineRecord[i].distance1
										* lineRecord[i].distance1
										+ mVisionSenseMap[VO_GOAL2_R].distance
												* mVisionSenseMap[VO_GOAL2_R].distance
										- 2
												* mVisionSenseMap[VO_GOAL2_R].distance
												* lineRecord[i].distance1
												* cos(
														fabs(
																mVisionSenseMap[VO_GOAL2_R].theta
																		- lineRecord[i].theta1)
																* PI_180));
				float linePartLength2 =
						sqrt(
								lineRecord[i].distance2
										* lineRecord[i].distance2
										+ mVisionSenseMap[VO_GOAL2_R].distance
												* mVisionSenseMap[VO_GOAL2_R].distance
										- 2
												* mVisionSenseMap[VO_GOAL2_R].distance
												* lineRecord[i].distance2
												* cos(
														fabs(
																mVisionSenseMap[VO_GOAL2_R].theta
																		- lineRecord[i].theta2)
																* PI_180));
				/////////cout<<"lineLength  :"<<lineLength<<"  linePartLength1 :"<<linePartLength1<<"  linePartLength2 :"<<linePartLength2<<endl;
				if (fabs(lineLength - linePartLength2 - linePartLength1) < 0.3) ///maybe i saw the goal line
				{
					if (mLineSenseMap[LI_GOAL_R].updated == false)
					{
						mLineSenseMap[LI_GOAL_R] = lineRecord[i];
						mLineSenseMap[LI_GOAL_R].updated = true;
						lineRecord[i].senseTime = 0;
						maybeGoalLineMark++;
						/////////cout<<"recognize goal line R (by vo_goal1_r):"<<i<<endl;
					}
				}

			}
			if (maybeGoalLineMark >= 2) /// two or more goal lines,it must be something wrong,must not use  
			{
				mLineSenseMap[LI_GOAL_R].distance1 = 0;
				mLineSenseMap[LI_GOAL_R].distance2 = 0;
				mLineSenseMap[LI_GOAL_R].phi1 = 0;
				mLineSenseMap[LI_GOAL_R].phi2 = 0;
				mLineSenseMap[LI_GOAL_R].theta1 = 0;
				mLineSenseMap[LI_GOAL_R].theta2 = 0;
				mLineSenseMap[LI_GOAL_R].updated = false;
				mLineSenseMap[LI_GOAL_R].senseTime = 0;
				/////////cout<<"two or more goal lines,it must be something wrong,must not use"<<endl;
			}
		}
	}

	if (mLineSenseMap[LI_GOAL_L].updated == false)
	{
		if ((mVisionSenseMap[VO_GOAL1_L].updated == true
				&& mVisionSenseMap[VO_GOAL2_L].updated == false)
				|| (mVisionSenseMap[VO_GOAL1_L].updated == true
						&& mVisionSenseMap[VO_GOAL2_L].updated == true
						&& (mVisionSenseMap[VO_GOAL1_L].distance
								< mVisionSenseMap[VO_GOAL2_L].distance)))
		{
			/////////cout<<"use VO_GOAL1_L!!!"<<endl;
			int maybeGoalLineMark = 0;
// 			int maybePenaltyLine_1_Mark=0;
// 			int maybePenaltyLine_2_Mark=0;
			for (int i = 0; lineRecord[i].updated == true; i++) ///each line i saw 
					{
				if (lineRecord[i].senseTime == 0)
				{
					continue;
				}
				float lineLength =
						sqrt(
								lineRecord[i].distance1
										* lineRecord[i].distance1
										+ lineRecord[i].distance2
												* lineRecord[i].distance2
										- 2 * lineRecord[i].distance1
												* lineRecord[i].distance2
												* cos(
														fabs(
																lineRecord[i].theta1
																		- lineRecord[i].theta2)
																* PI_180));
				float linePartLength1 =
						sqrt(
								lineRecord[i].distance1
										* lineRecord[i].distance1
										+ mVisionSenseMap[VO_GOAL1_L].distance
												* mVisionSenseMap[VO_GOAL1_L].distance
										- 2
												* mVisionSenseMap[VO_GOAL1_L].distance
												* lineRecord[i].distance1
												* cos(
														fabs(
																mVisionSenseMap[VO_GOAL1_L].theta
																		- lineRecord[i].theta1)
																* PI_180));
				float linePartLength2 =
						sqrt(
								lineRecord[i].distance2
										* lineRecord[i].distance2
										+ mVisionSenseMap[VO_GOAL1_L].distance
												* mVisionSenseMap[VO_GOAL1_L].distance
										- 2
												* mVisionSenseMap[VO_GOAL1_L].distance
												* lineRecord[i].distance2
												* cos(
														fabs(
																mVisionSenseMap[VO_GOAL1_L].theta
																		- lineRecord[i].theta2)
																* PI_180));
				/////////cout<<"lineLength  :"<<lineLength<<"  linePartLength1 :"<<linePartLength1<<"  linePartLength2 :"<<linePartLength2<<endl;
				if (fabs(lineLength - linePartLength2 - linePartLength1) < 0.3) ///maybe i saw the goal line
				{
					if (mLineSenseMap[LI_GOAL_L].updated == false)
					{
						mLineSenseMap[LI_GOAL_L] = lineRecord[i];
						mLineSenseMap[LI_GOAL_L].updated = true;
						lineRecord[i].senseTime = 0;
						maybeGoalLineMark++;
						/////////cout<<"recognize goal line R (by vo_goal1_r):"<<i<<endl;
					}
				}
			}
			if (maybeGoalLineMark >= 2) /// two or more goal lines,it must be something wrong,must not use  
			{
				mLineSenseMap[LI_GOAL_L].distance1 = 0;
				mLineSenseMap[LI_GOAL_L].distance2 = 0;
				mLineSenseMap[LI_GOAL_L].phi1 = 0;
				mLineSenseMap[LI_GOAL_L].phi2 = 0;
				mLineSenseMap[LI_GOAL_L].theta1 = 0;
				mLineSenseMap[LI_GOAL_L].theta2 = 0;
				mLineSenseMap[LI_GOAL_L].updated = false;
				mLineSenseMap[LI_GOAL_L].senseTime = 0;
				/////////cout<<"two or more goal lines,it must be something wrong,must not use"<<endl;
			}
		}
		else if ((mVisionSenseMap[VO_GOAL1_L].updated == false
				&& mVisionSenseMap[VO_GOAL2_L].updated == true)
				|| (mVisionSenseMap[VO_GOAL1_L].updated == true
						&& mVisionSenseMap[VO_GOAL2_L].updated == true
						&& (mVisionSenseMap[VO_GOAL1_L].distance
								> mVisionSenseMap[VO_GOAL2_L].distance)))
		{
			/////////cout<<"use VO_GOAL2_L!!!"<<endl;
			int maybeGoalLineMark = 0;
// 			int maybePenaltyLine_1_Mark=0;
// 			int maybePenaltyLine_2_Mark=0;
			for (int i = 0; lineRecord[i].updated == true; i++) ///each line i saw 
					{
				if (lineRecord[i].senseTime == 0)
				{
					continue;
				}
				float lineLength =
						sqrt(
								lineRecord[i].distance1
										* lineRecord[i].distance1
										+ lineRecord[i].distance2
												* lineRecord[i].distance2
										- 2 * lineRecord[i].distance1
												* lineRecord[i].distance2
												* cos(
														fabs(
																lineRecord[i].theta1
																		- lineRecord[i].theta2)
																* PI_180));
				float linePartLength1 =
						sqrt(
								lineRecord[i].distance1
										* lineRecord[i].distance1
										+ mVisionSenseMap[VO_GOAL2_L].distance
												* mVisionSenseMap[VO_GOAL2_L].distance
										- 2
												* mVisionSenseMap[VO_GOAL2_L].distance
												* lineRecord[i].distance1
												* cos(
														fabs(
																mVisionSenseMap[VO_GOAL2_L].theta
																		- lineRecord[i].theta1)
																* PI_180));
				float linePartLength2 =
						sqrt(
								lineRecord[i].distance2
										* lineRecord[i].distance2
										+ mVisionSenseMap[VO_GOAL2_L].distance
												* mVisionSenseMap[VO_GOAL2_L].distance
										- 2
												* mVisionSenseMap[VO_GOAL2_L].distance
												* lineRecord[i].distance2
												* cos(
														fabs(
																mVisionSenseMap[VO_GOAL2_L].theta
																		- lineRecord[i].theta2)
																* PI_180));
				/////////cout<<"lineLength  :"<<lineLength<<"  linePartLength1 :"<<linePartLength1<<"  linePartLength2 :"<<linePartLength2<<endl;
				if (fabs(lineLength - linePartLength2 - linePartLength1) < 0.3) ///maybe i saw the goal line
				{
					if (mLineSenseMap[LI_GOAL_L].updated == false)
					{
						mLineSenseMap[LI_GOAL_L] = lineRecord[i];
						mLineSenseMap[LI_GOAL_L].updated = true;
						lineRecord[i].senseTime = 0;
						maybeGoalLineMark++;
						/////////cout<<"recognize goal line R (by vo_goal1_r):"<<i<<endl;
					}
				}

			}
			if (maybeGoalLineMark >= 2) /// two or more goal lines,it must be something wrong,must not use  
			{
				mLineSenseMap[LI_GOAL_L].distance1 = 0;
				mLineSenseMap[LI_GOAL_L].distance2 = 0;
				mLineSenseMap[LI_GOAL_L].phi1 = 0;
				mLineSenseMap[LI_GOAL_L].phi2 = 0;
				mLineSenseMap[LI_GOAL_L].theta1 = 0;
				mLineSenseMap[LI_GOAL_L].theta2 = 0;
				mLineSenseMap[LI_GOAL_L].updated = false;
				mLineSenseMap[LI_GOAL_L].senseTime = 0;
				/////////cout<<"two or more goal lines,it must be something wrong,must not use"<<endl;
			}
		}
	}
#endif
}

float Perceptor::getMyDistanceflag(VisionObject ob) ///this value should be accurately
{
	//return sqrt(mVisionSenseMap[ob].distance*mVisionSenseMap[ob].distance-0.45*0.45);
	return mVisionSenseMap[ob].distance
			* cosDeg(
					(-mHingeJointSenseMap[JID_HEAD_2].angle
							- mVisionSenseMap[ob].phi));
}
float Perceptor::getMyDistanceLine(VisionObject ob, int whichOne) ///this value should be accurately
{
	if (whichOne == 1)
	{
		return mLineSenseMap[ob].distance1
				* cosDeg(
						(-mHingeJointSenseMap[JID_HEAD_2].angle
								- mLineSenseMap[ob].phi1));
	}
	else if (whichOne == 2)
	{
		return mLineSenseMap[ob].distance2
				* cosDeg(
						(-mHingeJointSenseMap[JID_HEAD_2].angle
								- mLineSenseMap[ob].phi2));
	}
	else
	{
		return 0;
	}
}
// float ParseMessage::getMyAngleToFlag(VisionObject ob)///this value should be accurately
// {
// 	return asinDeg(sinDeg(mVisionSenseMap[ob].theta)*sinDeg(90-mVisionSenseMap[ob].phi));    
// }
// float ParseMessage::getMyAngleToLine(VisionObject ob,int whichOne)///this value should be accurately
// {
// 	if(whichOne==1)
// 	{
// 	      	return asinDeg(sinDeg(mLineSenseMap[ob].theta1)*sinDeg(90-mLineSenseMap[ob].phi1));    
// 	}
// 	else if(whichOne==2)
// 	{
// 	      return asinDeg(sinDeg(mLineSenseMap[ob].theta2)*sinDeg(90-mLineSenseMap[ob].phi2));
// 	}
// 	else
// 	{
// 	      return 0;
// 	}
// }
ACCSensor Perceptor::GetACC()
{
	return accSensor;
}

bool Perceptor::GetWhetherPositionAStand()
{
	return positionAStand;
}

bool Perceptor::GetWhetherPositionBStand()
{
	return positionBStand;
}

bool Perceptor::GetWhetherPositionCStand()
{
	return positionCStand;
}

bool Perceptor::GetWhetherPositionDStand()
{
	return positionDStand;
}

bool Perceptor::GetWhetherPositionEStand()
{
	return positionEStand;
}

int Perceptor::GetPositionANumberByHear()
{
	return positionANumberByHear;
}

int Perceptor::GetPositionBNumberByHear()
{
	return positionBNumberByHear;
}

int Perceptor::GetPositionCNumberByHear()
{
	return positionCNumberByHear;
}

int Perceptor::GetPositionDNumberByHear()
{
	return positionDNumberByHear;
}
int Perceptor::GetPositionENumberByHear()
{
	return positionENumberByHear;
}
bool Perceptor::GetWhetherBallBeforeVanguard()
{
	return whetherBallBeforeVanguard;
}

bool Perceptor::WhetherCanTurnToOpponentGoal()
{
	return whetherCanTurnToOpponentGoal;
}

