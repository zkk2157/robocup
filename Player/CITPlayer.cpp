/*
 * CITPlayer.cpp
 *
 *  Created on: 2012-3-2
 *      Author: cit
 */

#include "CITPlayer.h"
extern Strategy behavior;
extern WorldModel wm;
extern BasicMotion basicMotion;
extern Cstandup CITstandup;
extern NewWalk newWalk; /// lr
extern Agent agent;
extern Say CITSay;
CITPlayer::CITPlayer()
{
	// TODO Auto-generated constructor stub
	doBeam = true;
	isContred = false;
}

CITPlayer::~CITPlayer()
{
	// TODO Auto-generated destructor stub
}
Action CITPlayer::Think()
{
	behavior.updateLocalVariables();
	stringstream ss("");

#ifdef AGENT_STRATEGY_OUTPUT

	/////cout<<"-----------------------------0---------------------   time:  "<<wm.GetCurrentGameTime()<<endl;

#endif
	TPlayMode localCurrentGameMode = wm.GetCurrentGameMode();
	Vector3 ps;
	//	cout << "localCurrentGameMode::";
	//	Cout::print(localCurrentGameMode);
	//	cout << endl;
	switch (localCurrentGameMode)
	{
	case PM_BeforeKickOff:
		if (!doBeam)
		{
			ss << basicMotion.InitStandUpPose();
		}
		else
		{
			wm.ChangeMyTeamIndex();
			TTeamIndex nowMyBeamTI = wm.GetMyTeamIndex();
			if (nowMyBeamTI == TI_LEFT)
			{
				cout << "OurBallRightAttackForm" << OurBallRightAttackForm
					 << endl;
				ss << agent.GetBeamParameter(emOurBallForm);
				isourStartball = true;
				Beam();
			}
			else
			{
				isourStartball = false;
				ss << agent.GetBeamParameter(emOppBallForm);
				Beam();
			}
		}
		break;
	case PM_KickOff_Our: /*!< 1 kick_off_left:     kick off for the left team  己方开球*/
						 //	case	PM_PlayOn:

		isourStartball = true;
		if (CITstandup.GetfallDown() == false)
		{
			CITstandup.doJudgeFallDown();
		}

		if (CITstandup.GetFallingDown() && !CITstandup.GetfallDown())
		{
			ss << basicMotion.StopAllMotion();
		}
		else if (CITstandup.GetfallDown() == true)
		{
			CITstandup.SetFallingDown(false);
			ss << CITstandup.StandUp();
		}
		else
		{
			if (!CITstandup.GetFallingDown() && !CITstandup.GetfallDown())
			{
				cout << "do not fall down" << endl;
				if (wm.GetMyNumber() == 2)
				{
					if (wm.GetMyDistanceToBall() > 1)
					{
						isContred = false;
					//	cout << "一次" << endl;
					}
				//	cout << "isContred = " << isContred << endl;   1
					if (!isContred)
					{
						if (wm.GetMyDistanceToBall() < 0.19)
						{
							KickOffstart = true;
					//		cout << "两次" << endl;
						}
						else
						{
							KickOffstart = false;
					//		cout << "三次" << endl;
						}
						basicMotion.SetTimeCounter(0);
						isContred = true;
					}

				//	cout << "KickOffstart = " << KickOffstart<< endl;   0
					//		cout<<"KickOffstart::"<<KickOffstart<<endl;
					if (KickOffstart)
					{
						//		ss << basicMotion.LeftFootShootingBall();
						//	 if (whetherStriker == false)
						//	if( behavior.whetherStriker==false)

						//		ss<<behavior.stopAndShoottingbeforekick();
						//ss << behavior.stopAndShoottingByNexus3D();   原本
						//		ss<< basicMotion.RoboCansLefttoRight();

					//	cout << "开始 1111 " << endl;
						ss << behavior.stopAndShoottingByTrajectory();
					}
					else
					{
						//						if(wm.GetCurrentGameTime()<7)
						//							ss << behavior.MainStrategy();
						//						else
						{
							//   behavior.HandleBall();
							//		 newWalk.CreateWalkGait(destination, angleToTurn, topSpeed);
							//	ss<< newWalk.CreateWalkGait(destination, angleToTurn, topSpeed);
							//	ss<<behavior.stopAndShoottingbeforekick();
							//		ss<<behavior.stopAndShoottingbeforekick();

							//	ss<<behavior.stopAndShoottingbeforekick();   //开球出界时的射门
							//	ss<<behavior.stopAndShoottingByNexus3D();//开球时球落在对方球门前   原本
							//		ss<<behavior.stopAndShootting();
						//	cout << "开始踢球 2222 "  << endl;
							ss << behavior.stopAndShoottingByTrajectory();
						}
					}
				}
				else
				{
					if (wm.GetMyNumber() == 1)
					{
						ss << behavior.MainStrategy();
					}
					else
					{
						ss << behavior.StopWhereAt();
					}
				}
			}
		}

		break;
	case PM_KickOff_Opp: /*!< 2 kick_off_right:    kick off for the right team 对方开球*/
		isourStartball = false;
		if (wm.GetMyNumber() != 2)
		{
			if (CITstandup.GetfallDown() == false)
			{
				CITstandup.doJudgeFallDown();
			}

			if (CITstandup.GetFallingDown() && !CITstandup.GetfallDown())
			{
				ss << basicMotion.StopAllMotion();
			}
			else if (CITstandup.GetfallDown() == true)
			{
				CITstandup.SetFallingDown(false);
				ss << CITstandup.StandUp();
			}
			else
			{
				///	ss<<standUpWithTurnHead()<<endl;
				if (wm.GetMyNumber() == 1)
				{
					ss << behavior.MainStrategy();
				}
				else
				{
					ss << basicMotion.InitStandUpPose();
				}
			}
		}
		else if (wm.GetMyNumber() == 2)
		{
			ss << behavior.MainStrategy();
		}

		break;

	case PM_PlayOn: /*!< 3 play_on:           regular game play */
		//	case PM_KickOff_Our:

#ifdef AGENT_STRATEGY_OUTPUT
		/////cout<<"PM_PlayOn"<<endl;
#endif
		if (!doBeam)
		{
			startplayontime = wm.GetCurrentGameTime();
		}
		doBeam = true;
		isContred = false;
		ss << behavior.MainStrategy();
		//	ss<<behavior.stopAndShoottingbeforekick();
		break;
	case PM_KickIn_Our: /*!< 4 KickIn_l:           KickIn left team 出界 己方踢球*/

		ss << behavior.MainStrategy();

		break;
	case PM_KickIn_Opp: /*!< 5 KickIn_r:           KickIn right team 出界 对方踢球*/

		ss << behavior.MainStrategy();

		break;
	case PM_CORNER_KICK_Our: /*!< 6 corner_kick_l:     corner kick left team   己方踢球*/
		ss << behavior.MainStrategy();
		break;
	case PM_CORNER_KICK_Opp: /*!< 7 corner_kick_r:     corner kick right team  角球 对方踢球*/

		ss << behavior.MainStrategy();

		break;
	case PM_GOAL_KICK_Our: /*!< 8 goal_kick_l:       goal kick for left team 己方踢球*/

		ss << behavior.MainStrategy();

		break;
	case PM_GOAL_KICK_Opp: /*!< 9 goal_kick_r:       goal kick for right team 门球 对方踢球*/

		ss << behavior.MainStrategy();

		break;
	case PM_OFFSIDE_Our: /*!< 10 offside_l:         offside for left team 越位*/

		ss << behavior.MainStrategy();

		break;
	case PM_OFFSIDE_Opp: /*!< 11 offside_r:         offside for right team  越位*/

		ss << behavior.MainStrategy();

		break;
	case PM_GameOver: /*!< 12 GameOver:         GameOver  */

		ss << basicMotion.StopAllMotion();
		break;
	case PM_Goal_Our: /// can beam   /*!< 13 Goal_l:         Goal for left team  己方进球*/
		newWalk.SetTurnHeadAngle(0);
		newWalk.hasFallDown = true;
		behavior.initShootControlParameter();
		behavior.initSplits();
		if (doBeam == true)
		{
			ss << agent.GetBeamParameter(emOppBallForm);
			doBeam = false;
		}
		else
		{
			ss << basicMotion.InitStandUpPose();
		}
		break;
	case PM_Goal_Opp: /// can beam /*!< 14 Goal_r:         Goal for right team  对方进球*/
		newWalk.SetTurnHeadAngle(0);
		newWalk.hasFallDown = true;
		behavior.initShootControlParameter();
		behavior.initSplits();
		if (doBeam == true)
		{
			ss << agent.GetBeamParameter(emOurBallForm);
			doBeam = false;
		}
		else
		{
			ss << basicMotion.InitStandUpPose();
		}
		break;
	case PM_FREE_KICK_Our: /*!< 16 free_kick_l:          free kick for left team */
		ss << behavior.MainStrategy();
		break;
	case PM_FREE_KICK_Opp: /*!< 16 free_kick_r:       free kick for right team */
		ss << behavior.MainStrategy();
		break;
	case PM_NONE: /*!< 17 no play mode, this must be the last entry */
		ss << behavior.MainStrategy();
		break;
	default:
		ss << behavior.MainStrategy();
		break;
	}
	ss << CITSay.ControlSay();
	return ss.str();
}
