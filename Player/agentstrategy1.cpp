#include "agentstrategy.h"
#define KEEP_ONE_STYLE_WALK 120

#define MIN_VALUE 0.03
#define MID_VALUE 0.12
#define MAX_VALUE 1
//#define AGENT_STRATEGY_OUTPUT
using namespace std;
using namespace boost;
using namespace Sensor;
using namespace MonitorDraw;
extern Agent agent;
extern Perceptor messageParser;
extern WorldModel wm;
extern JointEffector mp;
extern Logger myLogger;
extern CITPlayer player;
Cstandup CITstandup;
NewWalk newWalk; ///lr
BasicMotion basicMotion;
extern Strategy behavior;
Hear CITHear;
Say CITSay;
extern Configure CITConf;
extern MDrawer CITMDrawer;
Strategy::Strategy()
{

	decisionChoice = DO_NOTHING;
	walkToward = true;
	walkBackward = false;

	canShootBall = false;
	beginShoot = false;

	prepareShoot = false;
	finishShoot = true;

	rightFootCanShoot = false;
	leftFootCanShoot = false;
	beginPassBall = true;
	rightFootPass = false;
	leftFootPass = false;

	firstWalkToward = true;
	firstWalkBackward = true;
	controlLabel_1 = true;
	controlLabel_2 = true;
	controlLabel_3 = true;
	controlLabel_4 = true;
	counter = 0;
	rightFootCounter = 0;

//	InitStrategyData();
	walkTest_walkBegin = true;
	myMoveDirection = HORIZONMOVE_NULL;

	doNotChangeMyRole = false;

	walkToDestinationCoordinate = true; ///lr
	checkCounter = 0;

	turnHeadRight = true; ///lr

	initRole = false;

	turnHeadMax = false;

	fallDownTurnHead = 0;

	initPass = false;

	turnHeadRightChanged = false;

	whetherStriker = false;
	//hasResetedWalkAndStrategyData=false;

	opponentTeamName[0] = "CIT3D";
	opponentTeamName[1] = "";
	opponentTeamName[2] = "B";

}

///////////////////////////////////////////////////////////////////////////////////////////////
Action Strategy::MainStrategy()
{

	//cout<<"time:"<<wm.GetCurrentGameTime()<<"  dis:"<<wm.GetMyDistanceToBall()<<"   body angle:"<<wm.GetMyBodyAngleToBall()<<"   distance:"<<wm.getDistanceOppenentToBall(wm.GetClosestToBallOpponentNumberByVision())<<endl;
	stringstream ss("");
	//analyze the soccer state and decide my role
	if (doNotChangeMyRole == false)
	{
		myRole = GetMyPlayRole();
	}
	switch (myRole)
	{
	case ROLE_VANGUARD: //前锋
	{
#ifdef AGENT_STRATEGY_OUTPUT
		cout << "num:" << wm.GetMyNumber() << ",I am vanguard!!!" << endl;
#endif
		return VanguardStrategy();
		break;
	}
	case ROLE_VICE_VANGUARD_1: //小副前锋1
#ifdef AGENT_STRATEGY_OUTPUT
		cout << "num:" << wm.GetMyNumber() << ",I am vice vanguard 1 !!!"<< endl;
#endif
		return ViceVanguard_1_Strategy();
		break;
	case ROLE_VICE_VANGUARD_3: //大副前锋3
#ifdef AGENT_STRATEGY_OUTPUT
		cout << "num:" << wm.GetMyNumber() << ",I am vice vanguard 2 !!!"
				<< endl;
#endif
		return ViceVanguard_3_Strategy();
		break;
	case ROLE_VICE_VANGUARD_2: //大副前锋2
#ifdef AGENT_STRATEGY_OUTPUT
		cout << "num:" << wm.GetMyNumber() << ",I am vice vanguard 2 !!!"
				<< endl;
#endif
		return ViceVanguard_2_Strategy();
		break;
	case ROLE_CENTRE_FORWARD: //中卫
#ifdef AGENT_STRATEGY_OUTPUT
		cout << "num:" << wm.GetMyNumber()
				<< ",I am centre forward!!!ROLE_CENTRE_FORWARD" << endl;
#endif
		return CentreForwardStrategy();
		break;
	case ROLE_VICE_CENTRE_FORWARD_1: //中卫
#ifdef AGENT_STRATEGY_OUTPUT
		cout << "num:" << wm.GetMyNumber()
				<< ",I am centre forward!!!ROLE_VICE_CENTRE_FORWARD_1" << endl;
#endif
		return ViceCentreForward_1_Strategy();
		break;
	case ROLE_VICE_CENTRE_FORWARD_2: //中卫
#ifdef AGENT_STRATEGY_OUTPUT
		cout << "num:" << wm.GetMyNumber()
				<< ",I am centre forward!!!ROLE_VICE_CENTRE_FORWARD_2" << endl;
#endif
		return ViceCentreForward_2_Strategy();
		break;
	case ROLE_LINEBACKER: //后卫
#ifdef AGENT_STRATEGY_OUTPUT
		cout << "num:" << wm.GetMyNumber()
				<< ",I am linebacker!!!ROLE_LINEBACKER" << endl;
#endif
		return LinebackerStrategy();
		break;
	case ROLE_VICE_LINEBACKER_1: //后卫
#ifdef AGENT_STRATEGY_OUTPUT
		cout << "num:" << wm.GetMyNumber()
				<< ",I am linebacker!!!ROLE_VICE_LINEBACKER_1" << endl;
#endif
		return ViceLinebacker_1_Strategy();
		break;
	case ROLE_VICE_LINEBACKER_2: //后卫
#ifdef AGENT_STRATEGY_OUTPUT
		cout << "num:" << wm.GetMyNumber()
				<< ",I am linebacker!!!ROLE_VICE_LINEBACKER_2" << endl;
#endif
		return ViceLinebacker_2_Strategy();
		break;
	case ROLE_GOALIE: //守门员
#ifdef AGENT_STRATEGY_OUTPUT
		cout << "num:" << wm.GetMyNumber() << ",I am goalie!!!ROLE_GOALIE"
				<< endl;
#endif
		return GoalieStrategy();
		break;
	case ROLE_NULL:
		return basicMotion.StopAllMotion();
		break;
	default:
		return VanguardStrategy();
	}

	return ss.str();

}

#if 1
Role Strategy::GetMyPlayRole()
{
	CITHear.print();
	Role myRole = ROLE_NULL;
///	Vector3 myCoordinate=wm.GetMyCoordinate();

	int mDisToBallIndex = 1;
	if (!wm.GetMyDistanceToBallSortedIndexOld(mDisToBallIndex))
	{
		mDisToBallIndex = 1; //default index is 1,that is the default role is vanguard!
	}

	if (whetherEnhanceDefence() == false)
		{
	#ifdef AGENT_STRATEGY_OUTPUT
			cout << "whetherEnhanceDefence()==false" << endl;
	#endif
			if (wm.GetMyNumber() == 1) //1号固定为守门员
			{
				myRole = ROLE_GOALIE;
			}
			else if (wm.GetMyNumber() == PLAYERNUMBER) ///&&myCoordinate.x()<0.2*wm.GetFieldLength()/2)
			{
				myRole = ROLE_LINEBACKER;
				//	myRole=ROLE_CENTRE_FORWARD;
				//	cout<<"myRole=ROLE_VICE_LINEBACKER_1"<<endl;
			}
			else //其他队员角色依据球场形势而分配
			{
	//     		int mDisToBallIndex=1;
	// 		if( !wm.GetMyDistanceToBallSortedIndexOld(mDisToBallIndex) )
	// 		{
	// 			mDisToBallIndex=1;//default index is 1,that is the default role is vanguard!
	// 		}
	#ifdef AGENT_STRATEGY_OUTPUT
				cout << "mDisToBallIndex:" << mDisToBallIndex << endl;
	#endif
				if (mDisToBallIndex == 1)
				{
					myRole = ROLE_VANGUARD;
				}
				else if (mDisToBallIndex == 2 ||mDisToBallIndex == 3)
				{
					myRole = ROLE_VICE_VANGUARD_1;
				}
				else if (  mDisToBallIndex == 4
						|| mDisToBallIndex == 5|| mDisToBallIndex == 6)
				{
					myRole = ROLE_VICE_VANGUARD_2;
				}
				else if (mDisToBallIndex == 7)
				{
					myRole = ROLE_CENTRE_FORWARD;
				}
				else if (mDisToBallIndex == 8)
				{
					myRole = ROLE_VICE_CENTRE_FORWARD_1;
				}
				else if (mDisToBallIndex == 9)
				{
					myRole = ROLE_VICE_CENTRE_FORWARD_2;
				}
				else if(mDisToBallIndex == 10)
				{
					myRole = ROLE_VICE_LINEBACKER_2;
				}
				else if(mDisToBallIndex == 11)
				{
					myRole =ROLE_VICE_LINEBACKER_1;
				}
			}
		}
	else if (whetherEnhanceDefence() == true)
	{
#ifdef AGENT_STRATEGY_OUTPUT
		cout << "whetherEnhanceDefence()==true" << endl;
#endif
		if (wm.GetMyNumber() == 1) //1号固定为守门员
		{
			myRole = ROLE_GOALIE;
		}
		else if (wm.GetMyNumber() ==PLAYERNUMBER-2 && ball.x() > -3.5 * CELL_LENGTH
				&& mDisToBallIndex != 1) ///&&myCoordinate.x()<0.2*wm.GetFieldLength()/2)
		{
			myRole = ROLE_VICE_LINEBACKER_2;
			//	myRole=ROLE_CENTRE_FORWARD;
			//	cout<<"myRole=ROLE_VICE_CENTRE_FORWARD_2"<<endl;
		}
		else if (wm.GetMyNumber() == PLAYERNUMBER-1 && ball.x() > -4.5 * CELL_LENGTH
				&& mDisToBallIndex != 1) ///&&myCoordinate.x()<0.2*wm.GetFieldLength()/2)
		{
			myRole = ROLE_VICE_LINEBACKER_1;
			//	myRole=ROLE_CENTRE_FORWARD;
			//	cout<<"myRole=ROLE_LINEBACKER"<<endl;
		}
		else if (wm.GetMyNumber() ==PLAYERNUMBER
				&& mDisToBallIndex != 1) ///&&myCoordinate.x()<0.2*wm.GetFieldLength()/2)
		{
			myRole = ROLE_LINEBACKER;
			//	myRole=ROLE_CENTRE_FORWARD;
			//	cout<<"myRole=ROLE_VICE_LINEBACKER_1"<<endl;
		}
		else //其他队员角色依据球场形势而分配
		{
//     		int mDisToBallIndex=1;
// 		if( !wm.GetMyDistanceToBallSortedIndexOld(mDisToBallIndex) )
// 		{
// 			mDisToBallIndex=1;//default index is 1,that is the default role is vanguard!
// 		}
#ifdef AGENT_STRATEGY_OUTPUT
			cout << "mDisToBallIndex:" << mDisToBallIndex << endl;
#endif
			if (mDisToBallIndex == 1)
			{
				myRole = ROLE_VANGUARD;
			}
			else if (mDisToBallIndex == 2||mDisToBallIndex == 3)
			{
				myRole = ROLE_VICE_VANGUARD_1;
			}
			else if (  mDisToBallIndex == 4
					|| mDisToBallIndex == 5|| mDisToBallIndex == 6)
			{
				myRole = ROLE_VICE_VANGUARD_2;
			}
			else if (mDisToBallIndex == 7)
			{
				myRole = ROLE_CENTRE_FORWARD;
			}
			else if (mDisToBallIndex == 8)
			{
				myRole = ROLE_VICE_CENTRE_FORWARD_1;
			}
			else if (mDisToBallIndex == 9)
			{
				myRole = ROLE_VICE_CENTRE_FORWARD_2;
			}
			else if(mDisToBallIndex == 10)
			{
				myRole = ROLE_VICE_LINEBACKER_2;
			}
			else if(mDisToBallIndex == 11)
			{
				myRole =ROLE_VICE_LINEBACKER_1;
			}

		}
	}
	if (wm.GetMyNumber() != 1) //1号固定为守门员
	{
		if (myRole == ROLE_VICE_VANGUARD_1)
		{
			float dis;
			if (wm.GetVanguardToBallDistance(dis))
			{
#ifdef AGENT_STRATEGY_OUTPUT
				cout << " wm.IsVanguardFallDown():" << wm.IsVanguardFallDown()
									<< endl;
#endif

				if (wm.IsVanguardFallDown()
						&& localMyDistanceToBall
						< wm.GetMyDistanceToTeammate(wm.GetVanguardNumber())
						&& dis > 0.5)
				{
					myRole = ROLE_VANGUARD;
#ifdef AGENT_STRATEGY_OUTPUT
					cout << "I change my role0000000000000000000000000000011111111"
							<< endl;
#endif

				}

				if (wm.IsVanguardFallDown() && dis > 0.6 * CELL_LENGTH)
				{
					myRole = ROLE_VANGUARD;
#ifdef  AGENT_STRATEGY_OUTPUT
					cout
					<< "I change my role000000000000000000000000000001111111122222222222222"
					<< endl;
#endif

				}
#ifdef AGENT_STRATEGY_OUTPUT
				cout << "I change my role000000000000000000000000000002222222222"
						<< endl;
#endif

				if (localMyDistanceToBall
						< wm.GetMyDistanceToTeammate(wm.GetVanguardNumber())
						&& dis > 0.7)
				{
#ifdef AGENT_STRATEGY_OUTPUT
					cout
					<< "I change my role00000000000000000000000000000444444444444"
					<< endl;
#endif
					myRole = ROLE_VANGUARD;
					//		wm.SetViceVanguard_1FallDown(1);
				}

				if (localWhetherCanAttackOppGoal2 == true
						&& localMyDistanceToBall
						< wm.GetMyDistanceToTeammate(wm.GetVanguardNumber())
						&& dis > 0.5 && localMyDistanceToBall < CELL_LENGTH)
				{
#ifdef AGENT_STRATEGY_OUTPUT
					cout << "I change my role00000000000000000000000000000555555555"
							<< endl;
#endif
					myRole = ROLE_VANGUARD;
				}
			}
		}

		if (myRole == ROLE_VICE_VANGUARD_1 && mDisToBallIndex == 3)
		{

			if (wm.GetClosestToBallTeammateDistanceByVision() > 0.5 * CELL_LENGTH
					&& localMyDistanceToBall
					< wm.GetMyDistanceToTeammate(
							wm.GetClosestToBallTeammateNumberByVision()))
			{
#ifdef AGENT_STRATEGY_OUTPUT
				cout << "I change my role000000000000000000000000000005555555555555"
						<< endl;
#endif
				myRole = ROLE_VANGUARD;
			}
		}
		if (myRole == ROLE_VICE_VANGUARD_2 && mDisToBallIndex == 4)
				{

					if (wm.GetClosestToBallTeammateDistanceByVision() > 0.5 * CELL_LENGTH
							&& localMyDistanceToBall
							< wm.GetMyDistanceToTeammate(
									wm.GetClosestToBallTeammateNumberByVision()))
					{
		#ifdef AGENT_STRATEGY_OUTPUT
						cout << "I change my role000000000000000000000000000005555555555555"
								<< endl;
		#endif
						myRole = ROLE_VANGUARD;
					}
				}
		if (myRole == ROLE_VICE_VANGUARD_2 && mDisToBallIndex == 5)
						{

							if (wm.GetClosestToBallTeammateDistanceByVision() > 0.5 * CELL_LENGTH
									&& localMyDistanceToBall
									< wm.GetMyDistanceToTeammate(
											wm.GetClosestToBallTeammateNumberByVision()))
							{
				#ifdef AGENT_STRATEGY_OUTPUT
								cout << "I change my role000000000000000000000000000005555555555555"
										<< endl;
				#endif
								myRole = ROLE_VANGUARD;
							}
						}
		if (myRole == ROLE_VICE_VANGUARD_2 && mDisToBallIndex == 6)
								{

									if (wm.GetClosestToBallTeammateDistanceByVision() > 0.5 * CELL_LENGTH
											&& localMyDistanceToBall
											< wm.GetMyDistanceToTeammate(
													wm.GetClosestToBallTeammateNumberByVision()))
									{
						#ifdef AGENT_STRATEGY_OUTPUT
										cout << "I change my role000000000000000000000000000005555555555555"
												<< endl;
						#endif
										myRole = ROLE_VANGUARD;
									}
								}
#ifdef AGENT_STRATEGY_OUTPUT
	////cout<<"myRole:"<<myRole<<endl;
#endif

	if (wm.GetMyNumber() == CITHear.GetNowVanguardnum())
	{
#ifdef AGENT_STRATEGY_OUTPUT
		cout<<"I am The Vanguard"<<endl;
#endif
		myRole = ROLE_VANGUARD;
	}
#ifdef AGENT_STRATEGY_OUTPUT
	cout<<"CITHear.GetNowVanguardnum()::"<<CITHear.GetNowVanguardnum()<<endl;
#endif
	if (myRole == ROLE_VANGUARD && wm.GetMyNumber() != CITHear.GetNowVanguardnum())
	{
#ifdef AGENT_STRATEGY_OUTPUT
		cout << "there is new Vanguard change by hear" << endl;
#endif
		if(ball.x()>-8*CELL_LENGTH)
		{
			myRole = ROLE_VICE_VANGUARD_2;
		}
		else
		{
			myRole = ROLE_VICE_LINEBACKER_2;
		}
		if(ball.x()<-CELL_LENGTH&&ball.x()>-5*CELL_LENGTH)
		{
#ifdef AGENT_STRATEGY_OUTPUT
			   cout<<"mDisToBallIndex"<<mDisToBallIndex<<endl;
#endif
				if(mDisToBallIndex==1&&CITHear.VanNumdifference())
				{
#ifdef AGENT_STRATEGY_OUTPUT
					cout<<"CITHear.VanNumdifference()"<<CITHear.VanNumdifference()<<endl;
#endif
					myRole = ROLE_VANGUARD;
				}
		}
	}

	if(!CITHear.IsStandByHear( CITHear.GetNowVanguardnum()))
	{
//		cout<<"Vanguard down!!!"<<endl;
//		cout<<"mDisToBallIndex::"<<mDisToBallIndex<<endl;
		if(mDisToBallIndex == 2&&myRole!=ROLE_VICE_LINEBACKER_2)
		{
			myRole = ROLE_VANGUARD;
		}
	}
	if (ball.x() < -1.5 * CELL_LENGTH&&myRole!=ROLE_VANGUARD)
	{
		if(wm.GetMyNumber()==wm.GetPositionBNumber()||
				wm.GetMyNumber()==wm.GetPositionANumber()||myRole==ROLE_VICE_VANGUARD_1)
		{
//			cout<<"wm.GetMyNumber()!=wm.GetPositionBNumber()||GetMyNumber()!=wm.GetPositionANumber()"<<endl;
			myRole =ROLE_VICE_LINEBACKER_2;
		}
	}
	if(CITHear.GetClosestToGoaile()==wm.GetMyNumber())
	{
//		cout<<"CITHear.GetClosestToGoaile()==wm.GetMyNumber()"<<endl;
		myRole =ROLE_LINEBACKER;
	}
	//	if(CITHear.GetNextClosestToGoaile()==wm.GetMyNumber())
	//	{
	//		cout<<"CITHear.GetNextClosestToGoaile()==wm.GetMyNumber()"<<endl;
	//		myRole =ROLE_VICE_LINEBACKER_1;
	//	}
	//	if(ball.x()<0)
	//	{
	//		if((myRole==ROLE_VICE_LINEBACKER_1||myRole==ROLE_VICE_LINEBACKER_2)&&
	//			(wm.GetMyNumber()!=wm.GetPositionANumber()||
	//					wm.GetMyNumber()!=wm.GetPositionBNumber()||
	//					wm.GetMyNumber()!=wm.GetPositionCNumber()||
	//					wm.GetMyNumber()!=wm.GetPositionDNumber()))
	//		{
	//			cout<<"(myRole==ROLE_VICE_LINEBACKER_1||myRole==ROLE_VICE_LINEBACKER_2)wm.GetMyNumber()!=wm.GetPositionANumber()"<<endl;
	//			myRole=ROLE_CENTRE_FORWARD;
	//		}
	//	}
	}
	if(GetWhetherStriker())
	{
		myRole = ROLE_VANGUARD;
	}
	if(wm.GetCurrentGameTime()<player.startplayontime+5)
	{
		if(player.isourStartball)
		{
			if(wm.GetMyNumber()==2)
			{
				myRole = ROLE_VICE_VANGUARD_2;
			}
			if(wm.GetMyNumber()==4)
			{
				myRole = ROLE_VANGUARD;
			}
		}
	}
	return myRole;
}
#endif

bool Strategy::myRoleChanged()
{
	bool flag = false;
	if (myLastCycleRole != ROLE_NULL && myLastCycleRole != myRole)
		flag = true;
	else
		flag = false;

	myLastCycleRole = myRole;
	return flag;
}
bool Strategy::IsAvoid()
{
if (myRole == ROLE_VANGUARD)
{
	int teammateNumber;
		if (wm.WhetherMyTeammatesBlockMe(teammateNumber) == true)
		{
			Vector3 teammateCoordinate = wm.GetNewTeammateCoordinate(
					teammateNumber);
			float angle = wm.WhetherTeammateInMyWayToDestination(teammateCoordinate,
					my, destination);
	#ifdef AGENT_STRATEGY_OUTPUT
			cout<<"teammateNumber::"<<teammateNumber<<endl;
			cout<<"angle::"<<angle<<endl;
			cout<<"(teammateCoordinate-wm.GetMyCoordinate()).xymod()::"<<(teammateCoordinate-wm.GetMyCoordinate()).xymod()<<endl;
	#endif
			if (angle<25&&((teammateCoordinate-wm.GetMyCoordinate()).xymod()<0.3)&&wm.GetMyDistanceToBall()<0.8)
			{

				if((ball.x()>teammateCoordinate.x()&&teammateCoordinate.x()>my.x())
										||	(ball.x()<teammateCoordinate.x()&&teammateCoordinate.x()<my.x())
										||(ball.x()<my.x()&&teammateCoordinate.x()<ball.x()))
									{
								return true;
			}
			///return basicMotion.InitStandUpPose();

		}

			}
		if (
														(wm.GetClosestToBallOpponentDistanceByVision()<0.8 &&wm.GetClosestToBallTeammateDistanceByVision()<0.5
														&&wm.GetMyDistanceToBall()<0.8&&wm.IsVanguardFallDown()
														//&&wm.GetMyDistanceToBall()< CELL_LENGTH
														)||(wm.GetClosestToBallOpponentDistanceByVision()>0.8*CELL_LENGTH&&wm.GetClosestToBallTeammateDistanceByVision()<0.6
																&&	wm.GetMyDistanceToBall()<0.8*CELL_LENGTH))
												{
												return true;

												}


	////////////////////////////
}
return false;
}

void Strategy::SortPlayerByDistanceToBall(PlayerVector& players) ///useless
{
	if (players.size() != 0 && players.size() != 1)
	{
		//select sort
		PlayerVector::iterator iterMin = players.begin(), iterFlag = iterMin;
		for (PlayerVector::iterator iter = players.begin();
				iter != players.end() - 1; ++iter)
				{
			iterMin = iter;
			for (iterFlag = iter + 1; iterFlag != players.end(); ++iterFlag)
				if ((*iterFlag).distanceToBall < (*iterMin).distanceToBall)
					iterMin = iterFlag;

			if (iterMin != iter)
			{
				Player tempPlayer;
				tempPlayer = (*iterMin);
				(*iterMin) = (*iter);
				(*iter) = tempPlayer;
			}
		}
	}
}

void Strategy::BehaviorDecision()
{
	if (slidedToSaveBall)
	{
		decisionChoice = SLIDE_TACKLE;
		return;
	}
#ifdef AGENT_STRATEGY_OUTPUT
	cout << "&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&GetVanguardNumberByVision():"
			<< wm.GetVanguardNumberByVision() << endl;
	cout
			<< "&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&GetClosestToVanguardOpponentNumberByVision:"
			<< wm.GetClosestToVanguardOpponentNumberByVision() << endl;
	cout
			<< "&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&GetClosestToVanguardOpponentDistanceByVision:"
			<< wm.GetClosestToVanguardOpponentDistanceByVision() << endl;
	cout << "&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&.WhetherVanguardUseHalfStepWalk():"
			<< messageParser.WhetherVanguardUseHalfStepWalk() << endl;
	cout << "&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&.GetHearVanguardNumber():"
			<< messageParser.GetHearVanguardNumber() << endl;
	cout << "GetClosestToBallOpponentNumberByVision:"
			<< wm.GetClosestToBallOpponentNumberByVision() << endl;
	cout << "GetClosestToBallOpponentDistanceByVision:"
			<< wm.GetClosestToBallOpponentDistanceByVision() << endl;
	cout << "GetClosestToMeOpponentNumberByVision:"
			<< wm.GetClosestToMeOpponentNumberByVision() << endl;
	cout << "GetClosestToMeOpponentDistanceByVision:"
			<< wm.GetClosestToMeOpponentDistanceByVision() << endl;
#endif
	decisionChoice = DO_NOTHING;

	int mDisToBallIndex;
	wm.GetMyDistanceToBallSortedIndex(mDisToBallIndex);
///	Vector3 my=wm.GetMyCoordinate();
///	Vector3 ball=wm.GetLastCyclesAverageBallCoordinate();
	if (finishShoot == true)
	{
		if (myRole == ROLE_VANGUARD)
		{
			decisionChoice = HANDLE_BALL;
#if 1
			if (wm.CanSeeTheBall() && wm.CanDoLocalizationDirectly())
			{

#ifdef AGENT_STRATEGY_OUTPUT
				cout << "~1" << endl;
#endif
				if (whetherStriker == false)
				{

					if (ball.x() < 5 * CELL_LENGTH)
					{
						if ((localMyDistanceToBall < 0.6&& fabs(localMyBodyAngleToBall) < 20
								&& localClosestToBallOpponentDistanceByVision
										< 2 * CELL_LENGTH
										&& wm.WhetherDecideToPassBall() == true&& wm.GetClosestToMeOpponentDistanceByVision()>0.3 && wm.GetClosestToMeOpponentDistanceByVision()<2*CELL_LENGTH
										)||(localMyDistanceToBall < 0.65 && fabs(localMyBodyAngleToBall) < 20&& ball.x() < -8 * CELL_LENGTH&&wm.GetMyBodyAngleToXAxis()<90&&wm.GetMyBodyAngleToXAxis()>-90
												))
						{
#ifdef AGENT_STRATEGY_OUTPUT
							cout << "~2" << endl;
#endif
							decisionChoice = PASS_BALL;
						}
					}

					if (ball.x() >= 5 * CELL_LENGTH
							&& fabs(ball.y()) < 2 * CELL_LENGTH)
					{
#ifdef AGENT_STRATEGY_OUTPUT
						cout << "~3" << endl;
#endif
						if (localMyDistanceToBall < 0.6
								&& fabs(localMyBodyAngleToBall) < 20
								&& localWhetherCanAttackOppGoal2 == true
								&& localWhetherCanPassFront == true
								&& fabs(
										localLastCyclesAverageHorizontalTurnHeadAngle)
										< 1)
						{
#ifdef AGENT_STRATEGY_OUTPUT
							cout << "~4" << endl;
#endif
							//decisionChoice = PASS_BALL;
							decisionChoice = HANDLE_BALL;
						}
					}

					if (ball.x() >= 5 * CELL_LENGTH
							&& fabs(ball.y()) >= 2 * CELL_LENGTH)
					{
						if (ball.x() <= 7 * CELL_LENGTH)
						{
							if (ball.y() > 0)
							{
								if (localMyDistanceToBall < 0.6
										&& fabs(localMyBodyAngleToBall) < 20
										&& (messageParser.GetWhetherPositionCStand()
												== true
												|| messageParser.GetWhetherPositionBStand()
														== true)
										&& localMyBodyAngleToXAxis < 25
										&& localMyBodyAngleToXAxis > -135)
								{
#ifdef AGENT_STRATEGY_OUTPUT
									cout << "~13" << endl;
#endif
									//decisionChoice = PASS_BALL;
									decisionChoice = HANDLE_BALL;
								}
							}
							else if (ball.y() <= 0)
							{
								if (localMyDistanceToBall < 0.6
										&& fabs(localMyBodyAngleToBall) < 20
										&& (messageParser.GetWhetherPositionDStand()
												== true
												|| messageParser.GetWhetherPositionAStand()
														== true)
										&& localMyBodyAngleToXAxis > -25
										&& localMyBodyAngleToXAxis < 135)
								{
#ifdef AGENT_STRATEGY_OUTPUT
									cout << "~14" << endl;
#endif
								//	decisionChoice = PASS_BALL;
									decisionChoice = HANDLE_BALL;
								}
							}
						}
						else if (ball.x() > 7 * CELL_LENGTH)
						{decisionChoice = HANDLE_BALL;
							if (ball.y() > 0)
							{
								if (localMyDistanceToBall < 0.6
										&& fabs(localMyBodyAngleToBall) < 20
										&& (messageParser.GetWhetherPositionCStand()
												== true
												|| messageParser.GetWhetherPositionBStand()
														== true)
										&& localMyBodyAngleToXAxis < 0
										&& localMyBodyAngleToXAxis > -180)
								{
#ifdef AGENT_STRATEGY_OUTPUT
									cout << "~15" << endl;
#endif
									//decisionChoice = PASS_BALL;
									decisionChoice = HANDLE_BALL;
								}
								else if (fabs(ballCoordinate.y())
										> 3.5 * CELL_LENGTH
										&& localMyDistanceToBall < 0.6
										&& fabs(localMyBodyAngleToBall) < 20
										&& (messageParser.GetWhetherPositionCStand()
												== true
												|| messageParser.GetWhetherPositionBStand()
														== true))
								{
									//decisionChoice = PASS_BALL;前传，踢出界
									decisionChoice = HANDLE_BALL;
									cout << "kick the ball out of area!!!"
											<< endl;
								} ///add by gaojin
							}
							else if (ball.y() < 0)
							{decisionChoice = HANDLE_BALL;
								if (localMyDistanceToBall < 0.6
										&& fabs(localMyBodyAngleToBall) < 20
										&& (messageParser.GetWhetherPositionDStand()
												== true
												|| messageParser.GetWhetherPositionAStand()
														== true)
										&& localMyBodyAngleToXAxis > 0
										&& localMyBodyAngleToXAxis < 180)
								{
#ifdef AGENT_STRATEGY_OUTPUT
									cout << "~16" << endl;
#endif
								//	decisionChoice = PASS_BALL;
									decisionChoice = HANDLE_BALL;
								}
								else if (fabs(ballCoordinate.y())
										< -3.5 * CELL_LENGTH
										&& localMyDistanceToBall < 0.6
										&& fabs(localMyBodyAngleToBall) < 20
										&& (messageParser.GetWhetherPositionDStand()
												== true
												|| messageParser.GetWhetherPositionAStand()
														== true))
								{
								//	decisionChoice = PASS_BALL; 前传，踢出界
									decisionChoice = HANDLE_BALL;
									//cout << "kick the ball out of area!!!"	<< endl;
								} ///add by gaojin
							}
						}
					}

					{
						if (prepareShoot == false)
						{

//							prepareShoot = whetherCanShoot();
							if(wm.GetMyOpponentTeamName()=="apollo3d")
							{
								cout<<"apollo3d not need SHOOT_BALL"<<endl;
								prepareShoot=false;
							}
							else
							{
//								prepareShoot = whetherCanShootForVanguard();
								prepareShoot = whetherCanShoot();  //change by kb
							}
							if (prepareShoot == true)
							{
								if (wm.GetMyBodyAngleToBall() > 0)
								{
									leftShootDistance = true;
								}
								else
								{
									leftShootDistance = false;
								}
							}
						}
						else /*if(wm.GetClosestToBallOpponentDistanceByVision()>1.0 * CELL_LENGTH
						 && ballCoordinate.x() < 7.0 * CELL_LENGTH)*/
						{
#ifdef AGENT_STRATEGY_OUTPUT
							cout << "decisionChoice = SHOOT_BALL" << endl;
#endif
							decisionChoice = SHOOT_BALL;
#ifdef AGENT_STRATEGY_OUTPUT
							cout << "here is shoot ball" << endl;
#endif
						}
					} ///如果满足射门条件，就射门 add by gaojin
				}
				else if (whetherStriker == true)
				{
					if (ball.x() > 7.15 * CELL_LENGTH)
					{
						if (ball.x() >= 5.5 * CELL_LENGTH
								&& fabs(ball.y()) < 1.8 * CELL_LENGTH)
						{
#ifdef AGENT_STRATEGY_OUTPUT
							cout << "~3.1" << endl;
#endif
							if (localMyDistanceToBall < 0.6
									&& fabs(localMyBodyAngleToBall) < 20
									&& localWhetherCanAttackOppGoal2 == true
									&& localWhetherCanPassFront == true
									&& fabs(
											localLastCyclesAverageHorizontalTurnHeadAngle)
											< 1)
							{
#ifdef AGENT_STRATEGY_OUTPUT
								cout << "~4.1" << endl;
#endif
								decisionChoice = PASS_BALL;
							}
						}
					}
					else
					{
						if (prepareShoot == false)
						{
							prepareShoot = whetherCanShoot();
							if (prepareShoot == true)
							{
								if (wm.GetMyBodyAngleToBall() > 0)
								{
									leftShootDistance = true;
								}
								else
								{
									leftShootDistance = false;
								}
							}
						}
						else
						{
#ifdef AGENT_STRATEGY_OUTPUT
							cout << "shoot222" << endl;
#endif
							decisionChoice = SHOOT_BALL;
#ifdef AGENT_STRATEGY_OUTPUT
							cout << "decisionChoice = SHOOT_BALL" << endl;
#endif
						}
					}

					/*
					 if(ball.x()>=8*CELL_LENGTH&&fabs(ball.y())>=2*CELL_LENGTH&&(fabs(ball.y())/fabs(ball.x())<8.0))
					 {
					 if(ball.y()>0)
					 {
					 if(localMyDistanceToBall<0.6&&fabs(localMyBodyAngleToBall)<20&&localMyBodyAngleToXAxis<0&&localMyBodyAngleToXAxis>-135)
					 {
					 cout<<"~13"<<endl;
					 decisionChoice=PASS_BALL;
					 }
					 }
					 else if(ball.y()<=0)
					 {
					 if(localMyDistanceToBall<0.6&&fabs(localMyBodyAngleToBall)<20&&localMyBodyAngleToXAxis>0&&localMyBodyAngleToXAxis<135)
					 {
					 cout<<"~14"<<endl;
					 decisionChoice=PASS_BALL;
					 }
					 }
					 }
					 */
				}

			}

#endif

		}
		else if (myRole == ROLE_GOALIE)
		{
			decisionChoice = WALK_TO_MY_POSITION;
//			if(ball.x()<-8*CELL_LENGTH&&fabs(ball.y())<1&&wm.IsVanguardFallDown()==false
//					&&wm.GetMyDistanceToBall()>wm.GetClosestToBallTeammateDistanceByVision()-0.4)
//			{
//			        	   decisionChoice = DO_NOTHING;
//			}
//			else if(ball.x()<-8*CELL_LENGTH&&fabs(ball.y())<1
//					&&wm.GetClosestToBallOpponentDistanceByVision()>0.5*CELL_LENGTH
//					&&wm.GetMyDistanceToBall()<=wm.GetClosestToBallTeammateDistanceByVision())
//			{
//
//				decisionChoice = SHOOT_BALL;
//			}
			/*
			 if(getDownToSaveBall==false)
			 ///		if((mDisToBallIndex==1|| wm.MyDistanceToBallSmallerThanMyDistanceToAnyTeammate()==true)&&my.x()<1&&ball.x()<-8.5&&fabs(ball.y())<2.5&&wm.GetClosestToBallOpponentDistanceByVision()>0.5)
			 {
			 if(prepareShoot==false&&wm.EstimateWhetherUseHalfWalk()==false)
			 {
			 prepareShoot=whetherCanShoot();
			 ////cout<<"goalie prepareShoot=wm.CentreForwardWeatherCanShoot()"<<endl;
			 if(prepareShoot==true)
			 {
			 if(wm.GetMyBodyAngleToBall()>0)
			 {
			 leftShootDistance=true;
			 }
			 else
			 {
			 leftShootDistance=false;
			 }
			 }
			 }
			 else
			 {
			 ////cout<<"			golia	can shoot"<<endl;
			 decisionChoice=SHOOT_BALL;
			 }
			 }
			 */
		}
		else if (myRole == ROLE_CENTRE_FORWARD
				|| myRole == ROLE_VICE_CENTRE_FORWARD_1
				|| myRole == ROLE_VICE_CENTRE_FORWARD_2
				|| myRole == ROLE_LINEBACKER
				|| myRole == ROLE_VICE_LINEBACKER_1)
		{
			decisionChoice = WALK_TO_MY_POSITION;
			/*
			 ///		if((mDisToBallIndex==1|| wm.MyDistanceToBallSmallerThanMyDistanceToAnyTeammate()==true)&&my.x()<1&&wm.GetClosestToBallOpponentDistanceByVision()>0.5&&wm.GetMyDistanceToBall()<0.5&&fabs(wm.GetMyBodyAngleToBall())<25)
			 {
			 if(prepareShoot==false&&wm.EstimateWhetherUseHalfWalk()==false)
			 {
			 prepareShoot=whetherCanShoot();
			 cout<<"prepareShoot=wm.CentreForwardWeatherCanShoot()"<<endl;
			 if(prepareShoot==true)
			 {
			 if(wm.GetMyBodyAngleToBall()>0)
			 {
			 leftShootDistance=true;
			 }
			 else
			 {
			 leftShootDistance=false;
			 }
			 }
			 }
			 else
			 {
			 cout<<"				can shoot"<<endl;
			 decisionChoice=SHOOT_BALL;
			 }
			 }
			 */
		}
		else
		{
			decisionChoice = WALK_TO_MY_POSITION;
		}
	}
	else
	{
#ifdef AGENT_STRATEGY_OUTPUT
		cout << "shoot333" << endl;
#endif
		decisionChoice = SHOOT_BALL;
#ifdef AGENT_STRATEGY_OUTPUT
		cout << "decisionChoice = SHOOT_BALL" << endl;
#endif
	}

#if 1//ljj
	if (CITstandup.GetfallDown() == false && getDownToSaveBall == false
			&& CITstandup.GetfinishStandUpMotion() && !CITstandup.GetfallDown())
	{
		CITstandup.doJudgeFallDown();
	}
	if (CITstandup.GetFallingDown() && !CITstandup.GetfallDown()
			&& getDownToSaveBall == false)
	{
		if (wm.GetMyFallDirection() == D_FORWARD
				|| wm.GetMyFallDirection() == D_BACK)
		{
			decisionChoice = PREVENT_FALLING_DOWN;
			//cout<<"decisionChoice=PREVENT_FALLING_DOWN;"<<endl;
		}
		else
		{
			decisionChoice = ALL_STOP_FOR_STAND_UP;
			//cout<<"decisionChoice=ALL_STOP_FOR_STAND_UP;"<<endl;
		}
// 		if(justAfterStandUp)
// 		{
// 			decisionChoice=ALL_STOP_FOR_STAND_UP;
// 			//////cout<<"just after stand up !! decisionChoice=ALL_STOP_FOR_STAND_UP;"<<endl;
// 		}
	}
	else if (CITstandup.GetfallDown() == true && getDownToSaveBall == false)
	{
		//////cout<<"decisionChoice=STAND_UP;"<<endl;
		//justAfterStandUp=false;
		decisionChoice = STAND_UP;
	}
#endif

#ifdef AGENT_STRATEGY_OUTPUT
	cout << "decisionChoice:" << decisionChoice << endl;
#endif
}
Action Strategy::VanguardStrategy()
{
	stringstream ss("");
	//analyze the soccer state,and decide my action
	BehaviorDecision();
#ifdef AGENT_STRATEGY_OUTPUT
	cout << "       vanguard :       " << wm.GetMyNumber() << endl;
#endif
	switch (decisionChoice)
	{
	case HANDLE_BALL:
#ifdef AGENT_STRATEGY_OUTPUT
		cout << "HANDLE_BALL" << endl;
#endif
		ss << HandleBall();
		break;

	case ALL_STOP_FOR_STAND_UP:
#ifdef AGENT_STRATEGY_OUTPUT
		cout << "ALL_STOP_FOR_STAND_UP" << endl;
#endif
		ss << CITstandup.dealFallingDown();

		break;

	case PREVENT_FALLING_DOWN:
#ifdef AGENT_STRATEGY_OUTPUT
		cout << "PREVENT_FALLING_DOWN" << endl;
#endif
		ss << CITstandup.DisposeFalling();
		//cout<<"DisposeFalling!!!"<<endl;
		break;

	case STAND_UP:
#ifdef AGENT_STRATEGY_OUTPUT
		cout << "STAND_UP" << endl;
#endif
		ss << CITstandup.StandUp(); //do get up motion
		break;

	case SLIDE_TACKLE:
#ifdef AGENT_STRATEGY_OUTPUT
		cout << "SLIDE_TACKLE" << endl;
#endif
		ss << slideTackleToSaveBall();
		break;

	case SHOOT_BALL:
#ifdef AGENT_STRATEGY_OUTPUT
		cout << "stopAndShootting" << endl;
#endif
		ss << stopAndShootting();
		break;
	case PASS_BALL:
#ifdef AGENT_STRATEGY_OUTPUT
		cout << "PASS_BALL" << endl;
#endif
		ss << passBall();
		break;
	case DO_NOTHING:
#ifdef AGENT_STRATEGY_OUTPUT
		cout << "DO_NOTHING" << endl;
#endif
		ss << basicMotion.StopAllMotion();
		break;

	default:
#ifdef AGENT_STRATEGY_OUTPUT
		cout << "deafult" << endl;
#endif
		ss << HandleBall(); //walk and handle ball
		break;
	}
	return ss.str();
}

Action Strategy::ViceVanguard_1_Strategy()
{
	stringstream ss("");

	BehaviorDecision();
#ifdef AGENT_STRATEGY_OUTPUT
	cout << "       Vicevanguard_1 :       " << wm.GetMyNumber() << endl;
#endif

	switch (decisionChoice)
	{
	case WALK_TO_MY_POSITION:
		ss << ViceVanguard_1_Action();
		break;
	case ALL_STOP_FOR_STAND_UP:
		///	ss<<readData.AllStop();
		ss << CITstandup.dealFallingDown();
		break;

	case PREVENT_FALLING_DOWN:
		ss << CITstandup.DisposeFalling();
		//cout<<"DisposeFalling!!!"<<endl;
		break;

	case STAND_UP:
		ss << CITstandup.StandUp(); //do get up motion
		break;
	case SLIDE_TACKLE:
		ss << slideTackleToSaveBall();
		break;
	case DO_NOTHING:
		ss << basicMotion.StopAllMotion();
		break;
	default:
		ss << basicMotion.StopAllMotion();
	}

	//say sth to my teammates
///	string sayMsg;

	if (decisionChoice == STAND_UP || decisionChoice == ALL_STOP_FOR_STAND_UP)
	{
//		sayMsg="IV1D";
	}
	else
	{
//		sayMsg="IV1S";
	}
///	if(wm.GetTheMessageToSayAboutMyTeamMatePositon()!="000000000")
//	    ss<<mp.Say(wm.GetEncapsulatedWords(sayMsg+wm.GetTheMessageToSayAboutMyTeamMatePositon()));
//	else
//	  ss<<mp.Say(wm.GetEncapsulatedWords(sayMsg));

//	ss<<mp.Say(wm.GetEncapsulatedWords("ViceVanguard_1"));

	//sayMsg=wm.GetEncapsulatedWords(sayMsg);
	////cout<<"sayMsg:"<<sayMsg<<endl;
	//ss<<mp.Say(sayMsg);

	return ss.str();
}

Action Strategy::ViceVanguard_1_Action()
{

	destination = runFormation();
//	destination = Vector3(ball.x()-1*1.66 ,ball.y()+1.5*CELL_LENGTH	,0);
//	if(ball.x()<my.x() && ball.x()>-7*CELL_LENGTH)
//		destination = Vector3(ball.x() ,ball.y()	,0);
 if ( !wm.CanDoLocalizationDirectly())
	{

		ball = WalkToDestinationCoordinate(
				wm.GetLastCyclesAverageBallCoordinate());
	}

	if (wm.GetMyDistanceToDestination(ball) > 2) ///need do some impove
	{
//				cout
//						<< "Walk to destination Coordinate111111111111111111111111111!!!!"
//						<< endl;

		///	destination=WalkToDestinationCoordinate(destinationCoordinate);

	//	angleToTurn = localMyBodyAngleToBall;
		topSpeed==MAX_SPEED;

		angleToTurn=wm.GetMyAngleToDestination(destination);

		if (fabs(angleToTurn) < 70)
		{
	//		angleToTurn = localMyBodyAngleToBall;
			angleToTurn=wm.GetMyAngleToDestination(destination);
		}
		else
		{
			//angleToTurn = -localMyBodyAngleToXAxis;
		//	angleToTurn = localMyBodyAngleToBall;
			angleToTurn=wm.GetMyAngleToDestination(destination);

		}

	}
	else if (wm.GetMyDistanceToDestination(ball) > 0.7
			&& wm.GetMyDistanceToDestination(ball) <= 2) ///need do some impove
	{
//				cout
//						<< "Walk to destination Coordinate2222222222222222211111111111111!!!!"
//						<< endl;

		///	destination=WalkToDestinationCoordinate(destinationCoordinate);
		angleToTurn = localMyBodyAngleToBall;
		topSpeed==MAX_SPEED;

		///	angleToTurn=wm.GetMyAngleToDestination(destination);
		if (fabs(angleToTurn) < 70)
		{
			angleToTurn = localMyBodyAngleToBall;
		}
		else
		{
			angleToTurn = -localMyBodyAngleToXAxis;
		}

		//	angleToTurn=-wm.GetMyBodyAngleToXAxis();
	}
	else if (wm.GetMyDistanceToDestination(ball) <= 0.7)
	{
#ifdef AGENT_STRATEGY_OUTPUT
		cout << "2222222222222222222222222222222222222222222!!!"
				<< endl;
#endif
		if (fabs(localMyBodyAngleToBall) < 25)
		{
#ifdef AGENT_STRATEGY_OUTPUT
			cout << "fabs(wm.GetMyBodyAngleToBall() )<30 " << endl;
			angleToTurn = localMyBodyAngleToBall;

			cout << "AAAAA11111111111111wm.GetMyBodyAngleToXAxis():    "
					<< localMyBodyAngleToXAxis << endl;
			cout
					<< "AAAAA22222222222wm.GetLastCyclesAverageBallGoalToXAxisAngle(): "
					<< localLastCyclesAverageBallGoalToXAxisAngle
					<< endl;
			cout << "AAAAA33333333angleToTurn:  " << angleToTurn
					<< endl;
#endif
			if (localWhetherCanAttackOppGoal2 == false)
			{

			//	destination = WalkToDestinationCoordinate(
			//			destinationCoordinate);

#ifdef AGENT_STRATEGY_OUTPUT
				cout << "AAAAAA33333333333333333333333333333333"
						<< endl;
#endif

			}
			else ///if(wm.WhetherCanAttackOppGoal2()==true)         ///can not use,otherwish,it will execute two times
			{
				//	angleToTurn=wm.GetLastCyclesAverageBallGoalToXAxisAngle()-wm.GetMyBodyAngleToXAxis();
				///	destination=wm.GetLastCyclesAverageBallCoordinate();
			//	destination = ballCoordinate;
				topSpeed = MAX_SPEED;

				if (fabs(angleToTurn) > 20)
				{
					topSpeed = MIN_SPEED;
				}
#ifdef AGENT_STRATEGY_OUTPUT
				cout << "AAAAAA44444444444444444444444444444444444"
						<< endl;
#endif
			}

		}
		else if (fabs(localMyBodyAngleToBall) >= 25)
		{
			//angleToTurn = localLastCyclesAverageBallGoalToXAxisAngle
				//	- localMyBodyAngleToXAxis;
			angleToTurn=localMyBodyAngleToBall;
#ifdef AGENT_STRATEGY_OUTPUT
			cout
					<< "BBBBBBB11111111111111wm.GetMyBodyAngleToXAxis():    "
					<< localMyBodyAngleToXAxis << endl;
			cout
					<< "BBBBBB22222222222wm.GetLastCyclesAverageBallGoalToXAxisAngle(): "
					<< localLastCyclesAverageBallGoalToXAxisAngle
					<< endl;
			cout << "BBBBBB33333333angleToTurn:  " << angleToTurn
					<< endl;
#endif
			if (localWhetherCanAttackOppGoal2 == false)
			{

				//	angleToTurn=0;
	//			destination = WalkToDestinationCoordinate(
		//				destinationCoordinate);
#ifdef AGENT_STRATEGY_OUTPUT
				cout << "BBBBBB33333333333333333333333333333333"
						<< endl;
#endif

			}
			else ///if(wm.WhetherCanAttackOppGoal2()==true)         ///can not use,otherwish,it will execute two times
			{
				//	angleToTurn=wm.GetLastCyclesAverageBallGoalToXAxisAngle()-wm.GetMyBodyAngleToXAxis();
			//	destination = ballCoordinate;

				topSpeed = MAX_SPEED;
#ifdef AGENT_STRATEGY_OUTPUT
				cout << "BBBBBB44444444444444444444444444444444444"
						<< endl;
#endif
			}

		}

	}
	///	Vector3 teammateCoordinate=wm.GetNewAverageTeammateCoordinate(wm.GetClosestToBallTeammateNumberByVision());

	/* cout<<"########################################################"<<endl;
	 cout<<"wm.GetClosestToBallTeammateNumberByVision():"<<wm.GetClosestToBallTeammateNumberByVision()<<endl;
	 cout<<"teammateCoordinate:"<<teammateCoordinate<<endl;
	 cout<<"my:"<<my<<endl;
	 cout<<"destination:"<<destination<<endl;*/

/*	int teammateNumber;
	if (wm.WhetherMyTeammatesBlockMe(teammateNumber) == true)
	{
		Vector3 teammateCoordinate = wm.GetNewTeammateCoordinate(
				teammateNumber);
		float angle = wm.WhetherTeammateInMyWayToDestination(teammateCoordinate,
				my, destination);
#ifdef AGENT_STRATEGY_OUTPUT
		cout<<"teammateNumber::"<<teammateNumber<<endl;
		cout<<"angle::"<<angle<<endl;
		cout<<"(teammateCoordinate-wm.GetMyCoordinate()).xymod()::"<<(teammateCoordinate-wm.GetMyCoordinate()).xymod()<<endl;
#endif
		if (angle<30&&(teammateCoordinate-wm.GetMyCoordinate()).xymod()<1)
		{
			destination=Vector3Linelength(teammateCoordinate,wm.GetMyCoordinate(),0.5*CELL_LENGTH);
#ifdef AGENT_STRATEGY_OUTPUT
			cout << "wm.WhetherMyTeammatesBlockMe()==true" << endl;
#endif
	//		destination = Vector3(destination.x() + 0.1, destination.y() + 0.1,
	//				destination.z());
#ifdef AGENT_STRATEGY_OUTPUT
			cout<<"change destination!!!!"<<endl;
#endif
			topSpeed = MIDMIN_SPEED;
		}
		///return basicMotion.InitStandUpPose();
	}*/
	int teammateNumber;
		if (wm.WhetherMyTeammatesBlockMe(teammateNumber) == true)
		{
			Vector3 teammateCoordinate = wm.GetNewTeammateCoordinate(
					teammateNumber);
			float angle = wm.WhetherTeammateInMyWayToDestination(teammateCoordinate,
					my, destination);
	#ifdef AGENT_STRATEGY_OUTPUT
			cout<<"teammateNumber::"<<teammateNumber<<endl;
			cout<<"angle::"<<angle<<endl;
			cout<<"(teammateCoordinate-wm.GetMyCoordinate()).xymod()::"<<(teammateCoordinate-wm.GetMyCoordinate()).xymod()<<endl;
	#endif
			if(((teammateCoordinate-wm.GetMyCoordinate()).xymod()<0.7) && wm.CanSeeMyTeammate(teammateNumber))
		{
								//angleToTurn = -localMyBodyAngleToXAxis;
								angleToTurn = localLastCyclesAverageBallGoalToXAxisAngle
														- localMyBodyAngleToXAxis;
								  topSpeed =MIN_SPEED;
		}
	//		WhetherMyTeammatesBlockMe
			if (angle<20&&((teammateCoordinate-wm.GetMyCoordinate()).xymod()<0.7)&&wm.GetMyDistanceToBall()<0.8*CELL_LENGTH)
			{

				if((ball.x()>teammateCoordinate.x()&&teammateCoordinate.x()>my.x())
										||	(ball.x()<teammateCoordinate.x()&&teammateCoordinate.x()<my.x())
										||(ball.x()<my.x()&&teammateCoordinate.x()<ball.x()))
									{
									angleToTurn = localMyBodyAngleToBall;
													                               topSpeed =NULL_SPEED;
							//	topSpeed==AVOID_SPEED;
													                                    destination = ballCoordinate;
													                                    if(behavior.IsAvoid()==true)
													                                    	topSpeed=AVOID_SPEED;
													                                    return NEWWALK(destination, angleToTurn, topSpeed);}
			}
			///return basicMotion.InitStandUpPose();

		}
	else ////changed by gaojin
	{
#ifdef AGENT_STRATEGY_OUTPUT
		cout << "wm.WhetherMyTeammatesBlockMe()==false" << endl;
#endif
		theNewWalkSolutions(destination, angleToTurn, topSpeed);
	}
	if(ballCoordinate.x()<myCoordinate.x())
				{destination = ballCoordinate;
				//angleToTurn = localMyBodyAngleToBall;
				angleToTurn = localMyBodyAngleToBall;

								///	angleToTurn=wm.GetMyAngleToDestination(destination);
								if (fabs(angleToTurn) < 70)
								{
									angleToTurn = localMyBodyAngleToBall;
									///angleToTurn =0;
								}
								else
								{
									//angleToTurn = -localMyBodyAngleToXAxis;
									angleToTurn = localMyBodyAngleToBall;
								//	angleToTurn =0;
								}
				topSpeed = MAX_SPEED;

				}
	if ((wm.GetMyDistanceToDestination(destination) < 0.5 * CELL_LENGTH
				&& fabs(wm.GetMyBodyAngleToXAxis()) < 60) || //
				(wm.GetClosestToBallOpponentDistanceByVision()<0.8 &&wm.GetClosestToBallTeammateDistanceByVision()<0.6
															&&wm.GetMyDistanceToBall()<0.8*CELL_LENGTH
															//&&wm.GetMyDistanceToBall()< CELL_LENGTH
															)||(wm.GetClosestToBallOpponentDistanceByVision()>0.8*CELL_LENGTH && wm.GetClosestToBallTeammateDistanceByVision()<0.55
																	&&	wm.GetMyDistanceToBall()<0.8*CELL_LENGTH))
		{
			//return StopWhereAt();
		 angleToTurn = localMyBodyAngleToBall;
									                                   topSpeed =NULL_SPEED;
		//	topSpeed==AVOID_SPEED;
									                                   if(behavior.IsAvoid()==true)
									                                													                                    	topSpeed=AVOID_SPEED;
									                                    destination = ballCoordinate;
									                                    return NEWWALK(destination, angleToTurn, topSpeed);

		}


#ifdef AGENT_STRATEGY_OUTPUT
		cout << "Vice_Vanguard_1:_________________" << endl;
		cout << "angleToTurn:" << angleToTurn << endl;
		cout << "destination:" << destination << endl;
		cout << "topSpeed:" << topSpeed << endl;
#endif
		return NEWWALK(destination, angleToTurn, topSpeed);

	}



Action Strategy::ViceVanguard_2_Strategy()
{
	stringstream ss("");

	BehaviorDecision();

///	cout<<"       Vicevanguard_2:       "<<wm.GetMyNumber()<<endl;
	switch (decisionChoice)
	{
	case WALK_TO_MY_POSITION:
		ss << ViceVanguard_2_Action();
		break;
	case ALL_STOP_FOR_STAND_UP:
		///	ss<<readData.AllStop();
		ss << CITstandup.dealFallingDown();
		break;

	case PREVENT_FALLING_DOWN:
		ss << CITstandup.DisposeFalling();
		//cout<<"DisposeFalling!!!"<<endl;
		break;

	case STAND_UP:
		ss << CITstandup.StandUp(); //do get up motion
		break;

	case SLIDE_TACKLE:
		ss << slideTackleToSaveBall();
		break;
	case DO_NOTHING:
		ss << basicMotion.StopAllMotion();
		break;
	default:
		ss << basicMotion.StopAllMotion();
	}

//	if(wm.GetTheMessageToSayAboutMyTeamMatePositon()!="000000000")
//	    ss<<mp.Say(wm.GetEncapsulatedWords(wm.GetTheMessageToSayAboutMyTeamMatePositon()));

//	ss<<mp.Say(wm.GetEncapsulatedWords("ViceVanguard_2"));

	return ss.str();
}

Action Strategy::ViceVanguard_2_Action()
{
	//teammateCoordinate-wm.GetMyCoordinate()
	destination = runFormation();
	//destination = Vector3(ball.x()-1.5*1.66 ,ball.y()-1.5*CELL_LENGTH	,0);
	//  destination = ballCoordinate;
//if(ball.x()<my.x() )
	if(ball.x()<my.x() && ball.x()>-7*CELL_LENGTH)
	destination = Vector3(ball.x() ,ball.y()	,0);
if ( !wm.CanDoLocalizationDirectly())
	{

		ball = WalkToDestinationCoordinate(
				wm.GetLastCyclesAverageBallCoordinate());
	}

if (wm.GetMyDistanceToDestination(ball) > 2) ///need do some impove
	{
//				cout
//						<< "Walk to destination Coordinate111111111111111111111111111!!!!"
//						<< endl;

		///	destination=WalkToDestinationCoordinate(destinationCoordinate);

	//	angleToTurn = localMyBodyAngleToBall;
		topSpeed = MAX_SPEED;

		angleToTurn=wm.GetMyAngleToDestination(destination);

		if (fabs(angleToTurn) < 70)
		{
		//	angleToTurn = localMyBodyAngleToBall;
			angleToTurn=wm.GetMyAngleToDestination(destination);
		}
		else
		{
			//angleToTurn = -localMyBodyAngleToXAxis;
	//		angleToTurn = localMyBodyAngleToBall;
			angleToTurn=wm.GetMyAngleToDestination(destination);
		}

	}
	else if (wm.GetMyDistanceToDestination(ball) > 0.7
			&& wm.GetMyDistanceToDestination(ball) <= 2) ///need do some impove
	{
//				cout
//						<< "Walk to destination Coordinate2222222222222222211111111111111!!!!"
//						<< endl;

		///	destination=WalkToDestinationCoordinate(destinationCoordinate);
		angleToTurn = localMyBodyAngleToBall;

		///	angleToTurn=wm.GetMyAngleToDestination(destination);
		if (fabs(angleToTurn) < 70)
		{
			angleToTurn = localMyBodyAngleToBall;
		}
		else
		{
			angleToTurn = -localMyBodyAngleToXAxis;
		}
		topSpeed==MAX_SPEED;

		//	angleToTurn=-wm.GetMyBodyAngleToXAxis();
	}
	else if (wm.GetMyDistanceToDestination(ball) <= 0.7)
	{
#ifdef AGENT_STRATEGY_OUTPUT
		cout << "2222222222222222222222222222222222222222222!!!"
				<< endl;
#endif
		if (fabs(localMyBodyAngleToBall) < 25)
		{
#ifdef AGENT_STRATEGY_OUTPUT
			cout << "fabs(wm.GetMyBodyAngleToBall() )<30 " << endl;
			angleToTurn = localMyBodyAngleToBall;

			cout << "AAAAA11111111111111wm.GetMyBodyAngleToXAxis():    "
					<< localMyBodyAngleToXAxis << endl;
			cout
					<< "AAAAA22222222222wm.GetLastCyclesAverageBallGoalToXAxisAngle(): "
					<< localLastCyclesAverageBallGoalToXAxisAngle
					<< endl;
			cout << "AAAAA33333333angleToTurn:  " << angleToTurn
					<< endl;
#endif
			if (localWhetherCanAttackOppGoal2 == false)
			{

			//	destination = WalkToDestinationCoordinate(
			//			destinationCoordinate);

#ifdef AGENT_STRATEGY_OUTPUT
				cout << "AAAAAA33333333333333333333333333333333"
						<< endl;
#endif

			}
			else ///if(wm.WhetherCanAttackOppGoal2()==true)         ///can not use,otherwish,it will execute two times
			{
				//	angleToTurn=wm.GetLastCyclesAverageBallGoalToXAxisAngle()-wm.GetMyBodyAngleToXAxis();
				///	destination=wm.GetLastCyclesAverageBallCoordinate();
			//	destination = ballCoordinate;
				topSpeed = MAX_SPEED;

				if (fabs(angleToTurn) > 20)
				{
					topSpeed = MIN_SPEED;
				}
#ifdef AGENT_STRATEGY_OUTPUT
				cout << "AAAAAA44444444444444444444444444444444444"
						<< endl;
#endif
			}

		}
		else if (fabs(localMyBodyAngleToBall) >= 25)
		{
			//angleToTurn = localLastCyclesAverageBallGoalToXAxisAngle
				//	- localMyBodyAngleToXAxis;
			angleToTurn=localMyBodyAngleToBall;
#ifdef AGENT_STRATEGY_OUTPUT
			cout
					<< "BBBBBBB11111111111111wm.GetMyBodyAngleToXAxis():    "
					<< localMyBodyAngleToXAxis << endl;
			cout
					<< "BBBBBB22222222222wm.GetLastCyclesAverageBallGoalToXAxisAngle(): "
					<< localLastCyclesAverageBallGoalToXAxisAngle
					<< endl;
			cout << "BBBBBB33333333angleToTurn:  " << angleToTurn
					<< endl;
#endif
			if (localWhetherCanAttackOppGoal2 == false)
			{

				//	angleToTurn=0;
	//			destination = WalkToDestinationCoordinate(
		//				destinationCoordinate);
#ifdef AGENT_STRATEGY_OUTPUT
				cout << "BBBBBB33333333333333333333333333333333"
						<< endl;
#endif

			}
			else ///if(wm.WhetherCanAttackOppGoal2()==true)         ///can not use,otherwish,it will execute two times
			{
				//	angleToTurn=wm.GetLastCyclesAverageBallGoalToXAxisAngle()-wm.GetMyBodyAngleToXAxis();
			//	destination = ballCoordinate;

				topSpeed = MAX_SPEED;
#ifdef AGENT_STRATEGY_OUTPUT
				cout << "BBBBBB44444444444444444444444444444444444"
						<< endl;
#endif
			}

		}

	}
	/*int teammateNumber;
		if (wm.WhetherMyTeammatesBlockMe(teammateNumber) == true)
		{
			Vector3 teammateCoordinate = wm.GetNewTeammateCoordinate(
					teammateNumber);
			float angle = wm.WhetherTeammateInMyWayToDestination(teammateCoordinate,
					my, destination);

	#ifdef AGENT_STRATEGY_OUTPUT
			cout << "wm.WhetherMyTeammatesBlockMe()==true" << endl;

			cout<<"teammateNumber::"<<teammateNumber<<endl;
			cout<<"angle::"<<angle<<endl;
			cout<<"(teammateCoordinate-wm.GetMyCoordinate()).xymod()::"<<(teammateCoordinate-wm.GetMyCoordinate()).xymod()<<endl;
#endif
			if ((teammateCoordinate-wm.GetMyCoordinate()).xymod()<1)
			{
				destination=Vector3Linelength(teammateCoordinate,wm.GetMyCoordinate(),0.2*CELL_LENGTH);
#ifdef AGENT_STRATEGY_OUTPUT
				cout << "wm.WhetherMyTeammatesBlockMe()==true" << endl;
				cout<<"destination"<<destination<<endl;
				cout<<"change destination!!!!"<<endl;

#endif
		//		destination = Vector3(destination.x() + 0.1, destination.y() + 0.1,
		//				destination.z());
				topSpeed = MIDMIN_SPEED;
			}
			///return basicMotion.InitStandUpPose();
		}*/
	int teammateNumber;
			if (wm.WhetherMyTeammatesBlockMe(teammateNumber) == true)
			{
				Vector3 teammateCoordinate = wm.GetNewTeammateCoordinate(
						teammateNumber);
				float angle = wm.WhetherTeammateInMyWayToDestinationVANGUARD(teammateCoordinate,
						my, destination);
		#ifdef AGENT_STRATEGY_OUTPUT
				cout<<"teammateNumber::"<<teammateNumber<<endl;
				cout<<"angle::"<<angle<<endl;
				cout<<"(teammateCoordinate-wm.GetMyCoordinate()).xymod()::"<<(teammateCoordinate-wm.GetMyCoordinate()).xymod()<<endl;
		#endif
				if ((angle<30&&((teammateCoordinate-wm.GetMyCoordinate()).xymod()<1)&&wm.GetMyDistanceToBall()<0.8*CELL_LENGTH)
						||
						(((teammateCoordinate-wm.GetMyCoordinate()).xymod()<0.7) && wm.CanSeeMyTeammate(teammateNumber)))
				{
				/*	destination=Vector3Linelength(teammateCoordinate,wm.GetMyCoordinate(),0.5*CELL_LENGTH);
		#ifdef AGENT_STRATEGY_OUTPUT
					cout << "wm.WhetherMyTeammatesBlockMe()==true" << endl;
		#endif
			//		destination = Vector3(destination.x() + 0.1, destination.y() + 0.1,
			//				destination.z());
		#ifdef AGENT_STRATEGY_OUTPUT
					cout<<"change destination!!!!"<<endl;
		#endif
					topSpeed = MIDMIN_SPEED;*/
				//	angleToTurn = -localMyBodyAngleToXAxis;
					angleToTurn = localLastCyclesAverageBallGoalToXAxisAngle
																			- localMyBodyAngleToXAxis;
					  topSpeed =MIN_SPEED;
					if((ball.x()>teammateCoordinate.x()&&teammateCoordinate.x()>my.x())
						||	(ball.x()<teammateCoordinate.x()&&teammateCoordinate.x()<my.x())
						||(ball.x()<my.x()&&teammateCoordinate.x()<ball.x()))
					{
					angleToTurn = localMyBodyAngleToBall;
									                                 topSpeed =NULL_SPEED;
				//	topSpeed==AVOID_SPEED;
									                                 if(behavior.IsAvoid()==true)
									                               													                                    	topSpeed=AVOID_SPEED;
									                                    destination = ballCoordinate;}

				}

				///return basicMotion.InitStandUpPose();
				return NEWWALK(destination, angleToTurn, topSpeed);
			}
	else ///changed by gaojin
	{
#ifdef AGENT_STRATEGY_OUTPUT
		cout << "wm.WhetherMyTeammatesBlockMe()==false" << endl;
#endif
		theNewWalkSolutions(destination, angleToTurn, topSpeed);
	}
		if(ballCoordinate.x()<myCoordinate.x())
					{destination = ballCoordinate;
					//angleToTurn = localMyBodyAngleToBall;
					angleToTurn = localMyBodyAngleToBall;

									///	angleToTurn=wm.GetMyAngleToDestination(destination);
									if (fabs(angleToTurn) < 70)
									{
										angleToTurn = localMyBodyAngleToBall;
									}
									else
									{
									//	angleToTurn = -localMyBodyAngleToXAxis;
										angleToTurn = localMyBodyAngleToBall;
									//	angleToTurn=0;
									}
					topSpeed = MAX_SPEED;

					}
		if ((wm.GetMyDistanceToDestination(destination) < 0.5 * CELL_LENGTH
					&& fabs(wm.GetMyBodyAngleToXAxis()) < 60)
					||(wm.GetClosestToBallOpponentDistanceByVision()<0.9 &&wm.GetClosestToBallTeammateDistanceByVision()<0.7
							&&wm.GetMyDistanceToBall()<0.8*CELL_LENGTH
							//&&wm.GetMyDistanceToBall()< CELL_LENGTH
							)||(wm.GetClosestToBallOpponentDistanceByVision()>0.8*CELL_LENGTH&&wm.GetClosestToBallTeammateDistanceByVision()<0.6
									&&	wm.GetMyDistanceToBall()<0.8*CELL_LENGTH))
			{
				//return StopWhereAt();
			                                               angleToTurn = localMyBodyAngleToBall;
							                                 topSpeed =NULL_SPEED;
			                                    //       	topSpeed==AVOID_SPEED;
							                                 if(behavior.IsAvoid()==true)
							                                									                               													                                    	topSpeed=AVOID_SPEED;
							                                    destination = ballCoordinate;
							                                    return NEWWALK(destination, angleToTurn, topSpeed);
			}
	else
	{
#ifdef AGENT_STRATEGY_OUTPUT
		cout << "Vice_Vanguard_2:_________________" << endl;
		cout << "angleToTurn:" << angleToTurn << endl;
		cout << "destination:" << destination << endl;
		cout << "topSpeed:" << topSpeed << endl;
#endif
		return NEWWALK(destination, angleToTurn, topSpeed);
	}

}

Action Strategy::ViceVanguard_3_Strategy()
{
	stringstream ss("");

	BehaviorDecision();

///	cout<<"       Vicevanguard_2:       "<<wm.GetMyNumber()<<endl;
	switch (decisionChoice)
	{
	case WALK_TO_MY_POSITION:
		ss << ViceVanguard_2_Action();
		break;
	case ALL_STOP_FOR_STAND_UP:
		///	ss<<readData.AllStop();
		ss << CITstandup.dealFallingDown();
		break;

	case PREVENT_FALLING_DOWN:
		ss << CITstandup.DisposeFalling();
		//cout<<"DisposeFalling!!!"<<endl;
		break;

	case STAND_UP:
		ss << CITstandup.StandUp(); //do get up motion
		break;

	case SLIDE_TACKLE:
		ss << slideTackleToSaveBall();
		break;
	case DO_NOTHING:
		ss << basicMotion.StopAllMotion();
		break;
	default:
		ss << basicMotion.StopAllMotion();
	}

//	if(wm.GetTheMessageToSayAboutMyTeamMatePositon()!="000000000")
//	    ss<<mp.Say(wm.GetEncapsulatedWords(wm.GetTheMessageToSayAboutMyTeamMatePositon()));

//	ss<<mp.Say(wm.GetEncapsulatedWords("ViceVanguard_2"));

	return ss.str();
}



Action Strategy::ViceVanguard_3_Action()
{
	//teammateCoordinate-wm.GetMyCoordinate()
	destination = runFormation();
	destination = Vector3(ball.x()-1.6*1.66 ,ball.y()	,0);
	//  destination = ballCoordinate;
if(ball.x()<my.x() )
	destination = Vector3(ball.x()-1.6*1.66 ,ball.y()	,0);
if ( !wm.CanDoLocalizationDirectly())
	{

		ball = WalkToDestinationCoordinate(
				wm.GetLastCyclesAverageBallCoordinate());
	}

if (wm.GetMyDistanceToDestination(ball) > 2) ///need do some impove
	{
//				cout
//						<< "Walk to destination Coordinate111111111111111111111111111!!!!"
//						<< endl;

		///	destination=WalkToDestinationCoordinate(destinationCoordinate);

	//	angleToTurn = localMyBodyAngleToBall;
		topSpeed = MAX_SPEED;

		angleToTurn=wm.GetMyAngleToDestination(destination);

		if (fabs(angleToTurn) < 70)
		{
		//	angleToTurn = localMyBodyAngleToBall;
			angleToTurn=wm.GetMyAngleToDestination(destination);
		}
		else
		{
			//angleToTurn = -localMyBodyAngleToXAxis;
	//		angleToTurn = localMyBodyAngleToBall;
			angleToTurn=wm.GetMyAngleToDestination(destination);
		}

	}
	else if (wm.GetMyDistanceToDestination(ball) > 0.7
			&& wm.GetMyDistanceToDestination(ball) <= 2) ///need do some impove
	{
		topSpeed==MAX_SPEED;
//				cout
//						<< "Walk to destination Coordinate2222222222222222211111111111111!!!!"
//						<< endl;

		///	destination=WalkToDestinationCoordinate(destinationCoordinate);
		angleToTurn = localMyBodyAngleToBall;

		///	angleToTurn=wm.GetMyAngleToDestination(destination);
		if (fabs(angleToTurn) < 70)
		{
			angleToTurn = localMyBodyAngleToBall;
		}
		else
		{
			angleToTurn = -localMyBodyAngleToXAxis;
		}

		//	angleToTurn=-wm.GetMyBodyAngleToXAxis();
	}
	else if (wm.GetMyDistanceToDestination(ball) <= 0.7)
	{
#ifdef AGENT_STRATEGY_OUTPUT
		cout << "2222222222222222222222222222222222222222222!!!"
				<< endl;
#endif
		if (fabs(localMyBodyAngleToBall) < 25)
		{
#ifdef AGENT_STRATEGY_OUTPUT
			cout << "fabs(wm.GetMyBodyAngleToBall() )<30 " << endl;
			angleToTurn = localMyBodyAngleToBall;

			cout << "AAAAA11111111111111wm.GetMyBodyAngleToXAxis():    "
					<< localMyBodyAngleToXAxis << endl;
			cout
					<< "AAAAA22222222222wm.GetLastCyclesAverageBallGoalToXAxisAngle(): "
					<< localLastCyclesAverageBallGoalToXAxisAngle
					<< endl;
			cout << "AAAAA33333333angleToTurn:  " << angleToTurn
					<< endl;
#endif
			if (localWhetherCanAttackOppGoal2 == false)
			{

			//	destination = WalkToDestinationCoordinate(
			//			destinationCoordinate);

#ifdef AGENT_STRATEGY_OUTPUT
				cout << "AAAAAA33333333333333333333333333333333"
						<< endl;
#endif

			}
			else ///if(wm.WhetherCanAttackOppGoal2()==true)         ///can not use,otherwish,it will execute two times
			{
				//	angleToTurn=wm.GetLastCyclesAverageBallGoalToXAxisAngle()-wm.GetMyBodyAngleToXAxis();
				///	destination=wm.GetLastCyclesAverageBallCoordinate();
			//	destination = ballCoordinate;
				topSpeed = MAX_SPEED;

				if (fabs(angleToTurn) > 20)
				{
					topSpeed = MIN_SPEED;
				}
#ifdef AGENT_STRATEGY_OUTPUT
				cout << "AAAAAA44444444444444444444444444444444444"
						<< endl;
#endif
			}

		}
		else if (fabs(localMyBodyAngleToBall) >= 25)
		{
			//angleToTurn = localLastCyclesAverageBallGoalToXAxisAngle
				//	- localMyBodyAngleToXAxis;
			angleToTurn=localMyBodyAngleToBall;
#ifdef AGENT_STRATEGY_OUTPUT
			cout
					<< "BBBBBBB11111111111111wm.GetMyBodyAngleToXAxis():    "
					<< localMyBodyAngleToXAxis << endl;
			cout
					<< "BBBBBB22222222222wm.GetLastCyclesAverageBallGoalToXAxisAngle(): "
					<< localLastCyclesAverageBallGoalToXAxisAngle
					<< endl;
			cout << "BBBBBB33333333angleToTurn:  " << angleToTurn
					<< endl;
#endif
			if (localWhetherCanAttackOppGoal2 == false)
			{

				//	angleToTurn=0;
	//			destination = WalkToDestinationCoordinate(
		//				destinationCoordinate);
#ifdef AGENT_STRATEGY_OUTPUT
				cout << "BBBBBB33333333333333333333333333333333"
						<< endl;
#endif

			}
			else ///if(wm.WhetherCanAttackOppGoal2()==true)         ///can not use,otherwish,it will execute two times
			{
				//	angleToTurn=wm.GetLastCyclesAverageBallGoalToXAxisAngle()-wm.GetMyBodyAngleToXAxis();
			//	destination = ballCoordinate;

				topSpeed = MAX_SPEED;
#ifdef AGENT_STRATEGY_OUTPUT
				cout << "BBBBBB44444444444444444444444444444444444"
						<< endl;
#endif
			}

		}

	}
	/*int teammateNumber;
		if (wm.WhetherMyTeammatesBlockMe(teammateNumber) == true)
		{
			Vector3 teammateCoordinate = wm.GetNewTeammateCoordinate(
					teammateNumber);
			float angle = wm.WhetherTeammateInMyWayToDestination(teammateCoordinate,
					my, destination);

	#ifdef AGENT_STRATEGY_OUTPUT
			cout << "wm.WhetherMyTeammatesBlockMe()==true" << endl;

			cout<<"teammateNumber::"<<teammateNumber<<endl;
			cout<<"angle::"<<angle<<endl;
			cout<<"(teammateCoordinate-wm.GetMyCoordinate()).xymod()::"<<(teammateCoordinate-wm.GetMyCoordinate()).xymod()<<endl;
#endif
			if ((teammateCoordinate-wm.GetMyCoordinate()).xymod()<1)
			{
				destination=Vector3Linelength(teammateCoordinate,wm.GetMyCoordinate(),0.2*CELL_LENGTH);
#ifdef AGENT_STRATEGY_OUTPUT
				cout << "wm.WhetherMyTeammatesBlockMe()==true" << endl;
				cout<<"destination"<<destination<<endl;
				cout<<"change destination!!!!"<<endl;

#endif
		//		destination = Vector3(destination.x() + 0.1, destination.y() + 0.1,
		//				destination.z());
				topSpeed = MIDMIN_SPEED;
			}
			///return basicMotion.InitStandUpPose();
		}*/
	int teammateNumber;
			if (wm.WhetherMyTeammatesBlockMe(teammateNumber) == true)
			{
				Vector3 teammateCoordinate = wm.GetNewTeammateCoordinate(
						teammateNumber);
				float angle = wm.WhetherTeammateInMyWayToDestinationVANGUARD(teammateCoordinate,
						my, destination);
		#ifdef AGENT_STRATEGY_OUTPUT
				cout<<"teammateNumber::"<<teammateNumber<<endl;
				cout<<"angle::"<<angle<<endl;
				cout<<"(teammateCoordinate-wm.GetMyCoordinate()).xymod()::"<<(teammateCoordinate-wm.GetMyCoordinate()).xymod()<<endl;
		#endif
				if ((angle<30&&((teammateCoordinate-wm.GetMyCoordinate()).xymod()<1)&&wm.GetMyDistanceToBall()<0.8*CELL_LENGTH)
						||
						(((teammateCoordinate-wm.GetMyCoordinate()).xymod()<0.7) && wm.CanSeeMyTeammate(teammateNumber)))
				{
				/*	destination=Vector3Linelength(teammateCoordinate,wm.GetMyCoordinate(),0.5*CELL_LENGTH);
		#ifdef AGENT_STRATEGY_OUTPUT
					cout << "wm.WhetherMyTeammatesBlockMe()==true" << endl;
		#endif
			//		destination = Vector3(destination.x() + 0.1, destination.y() + 0.1,
			//				destination.z());
		#ifdef AGENT_STRATEGY_OUTPUT
					cout<<"change destination!!!!"<<endl;
		#endif
					topSpeed = MIDMIN_SPEED;*/
				//	angleToTurn = -localMyBodyAngleToXAxis;
					angleToTurn = localLastCyclesAverageBallGoalToXAxisAngle
																			- localMyBodyAngleToXAxis;
					  topSpeed =MIN_SPEED;
					if((ball.x()>teammateCoordinate.x()&&teammateCoordinate.x()>my.x())
						||	(ball.x()<teammateCoordinate.x()&&teammateCoordinate.x()<my.x())
						||(ball.x()<my.x()&&teammateCoordinate.x()<ball.x()))
					{
					angleToTurn = localMyBodyAngleToBall;
									                                  topSpeed =NULL_SPEED;
			//		topSpeed==AVOID_SPEED;
									                                    destination = ballCoordinate;}

				}

				///return basicMotion.InitStandUpPose();
				return NEWWALK(destination, angleToTurn, topSpeed);
			}
	else ///changed by gaojin
	{
#ifdef AGENT_STRATEGY_OUTPUT
		cout << "wm.WhetherMyTeammatesBlockMe()==false" << endl;
#endif
		theNewWalkSolutions(destination, angleToTurn, topSpeed);
	}
		if(ballCoordinate.x()<myCoordinate.x())
					{destination = ballCoordinate;
					//angleToTurn = localMyBodyAngleToBall;
					angleToTurn = localMyBodyAngleToBall;

									///	angleToTurn=wm.GetMyAngleToDestination(destination);
									if (fabs(angleToTurn) < 70)
									{
										angleToTurn = localMyBodyAngleToBall;
									}
									else
									{
									//	angleToTurn = -localMyBodyAngleToXAxis;
										angleToTurn = localMyBodyAngleToBall;
									//	angleToTurn=0;
									}
					topSpeed = MAX_SPEED;

					}
		if ((wm.GetMyDistanceToDestination(destination) < 0.5 * CELL_LENGTH
					&& fabs(wm.GetMyBodyAngleToXAxis()) < 60)
					||(wm.GetClosestToBallOpponentDistanceByVision()<0.9 &&wm.GetClosestToBallTeammateDistanceByVision()<0.7
							&&wm.GetMyDistanceToBall()<0.8*CELL_LENGTH
							//&&wm.GetMyDistanceToBall()< CELL_LENGTH
							)||(wm.GetClosestToBallOpponentDistanceByVision()>0.8*CELL_LENGTH&&wm.GetClosestToBallTeammateDistanceByVision()<0.6
									&&	wm.GetMyDistanceToBall()<0.8*CELL_LENGTH))
			{
				//return StopWhereAt();
			                                               angleToTurn = localMyBodyAngleToBall;
							                         //           topSpeed =NULL_SPEED;
			                                           	topSpeed==AVOID_SPEED;
							                                    destination = ballCoordinate;
							                                    return NEWWALK(destination, angleToTurn, topSpeed);
			}
	else
	{
#ifdef AGENT_STRATEGY_OUTPUT
		cout << "Vice_Vanguard_2:_________________" << endl;
		cout << "angleToTurn:" << angleToTurn << endl;
		cout << "destination:" << destination << endl;
		cout << "topSpeed:" << topSpeed << endl;
#endif
		return NEWWALK(destination, angleToTurn, topSpeed);
	}

}



Action Strategy::CentreForwardStrategy()
{
	stringstream ss("");

	BehaviorDecision();
///	cout<<"       CentreForwardStrategy :       "<<wm.GetMyNumber()<<endl;
	switch (decisionChoice)
	{
	case WALK_TO_MY_POSITION:
#ifdef AGENT_STRATEGY_OUTPUT
		cout << "CentreForward_walkToDestination" << endl;
#endif
		ss << CentreForwardAction();
		break;
	case ALL_STOP_FOR_STAND_UP:
		///	ss<<readData.AllStop();
		ss << CITstandup.dealFallingDown();
		break;
	case SHOOT_BALL:
#ifdef AGENT_STRATEGY_OUTPUT
		cout << "CentreForward_ShootBall" << endl;
#endif
		ss << stopAndShootting();
		break;

	case PREVENT_FALLING_DOWN:
		ss << CITstandup.DisposeFalling();
		//cout<<"DisposeFalling!!!"<<endl;
		break;
	case SLIDE_TACKLE:
		ss << slideTackleToSaveBall();
		break;
	case STAND_UP:
		ss << CITstandup.StandUp(); //do get up motion
		break;
	case DO_NOTHING:
		ss << basicMotion.StopAllMotion();
		break;
	default:
		ss << basicMotion.StopAllMotion();
	}
///	if(wm.GetTheMessageToSayAboutMyTeamMatePositon()!="000000000")
///	    ss<<mp.Say(wm.GetEncapsulatedWords(wm.GetTheMessageToSayAboutMyTeamMatePositon()));

//	ss<<mp.Say(wm.GetEncapsulatedWords("CentreForward"));

	return ss.str();
}
Action Strategy::CentreForwardAction()
{


	if(ballCoordinate.x()<myCoordinate.x())
				{destination = ballCoordinate;
				//angleToTurn = localMyBodyAngleToBall;
				angleToTurn = localMyBodyAngleToBall;

			//	destination = Vector3(ball.x()-2*1.66 ,ball.y() / 2	,0);   //gai
								///	angleToTurn=wm.GetMyAngleToDestination(destination);
								if (fabs(angleToTurn) < 70)
								{
									angleToTurn = localMyBodyAngleToBall;
								}
								else
								{
									//angleToTurn = -localMyBodyAngleToXAxis;
									angleToTurn = localMyBodyAngleToBall;
								}
				topSpeed = MAX_SPEED;
			 return NEWWALK(destination, angleToTurn, topSpeed);

				}
	if (
													(wm.GetClosestToBallOpponentDistanceByVision()<0.7 &&wm.GetClosestToBallTeammateDistanceByVision()<0.7
													&&wm.GetMyDistanceToBall()<0.8*CELL_LENGTH
													//&&wm.GetMyDistanceToBall()< CELL_LENGTH
													)||(wm.GetClosestToBallOpponentDistanceByVision()>0.7&&wm.GetClosestToBallTeammateDistanceByVision()<0.4
															&&	wm.GetMyDistanceToBall()<1*CELL_LENGTH))
											{
												//return StopWhereAt();
		 angleToTurn = localMyBodyAngleToBall;
											                             topSpeed =NULL_SPEED;
		//	topSpeed==AVOID_SPEED;
											                                    destination = ballCoordinate;
											                                    return NEWWALK(destination, angleToTurn, topSpeed);
											}

///	Vector3 ballCoordinate=wm.GetLastCyclesAverageBallCoordinate();
///	Vector3 myCoordinate=wm.GetMyCoordinate();
	int mDisToBallIndex;
	wm.GetMyDistanceToBallSortedIndexOld(mDisToBallIndex);
#ifdef AGENT_STRATEGY_OUTPUT
	cout << "wm.GetMyDistanceToTeammate(wm.GetVanguardNumber():"
			<< wm.GetMyDistanceToTeammate(wm.GetVanguardNumber()) << endl;

	cout << "(wm.GetVanguardNumber():" << wm.GetVanguardNumber() << endl;
#endif
	if (wm.MyDistanceToBallSmallerThanMyDistanceToAnyTeammate() == true)
	{
#ifdef AGENT_STRATEGY_OUTPUT
		cout << "CentreForwardAction111111111111111:" << endl;
#endif		
		Vector3 destinationCoordinate;
///		Vector3 ballCoordinate=wm.GetLastCyclesAverageBallCoordinate();
		///Vector3 myCoordinate=wm.GetMyCoordinate();

		if (wm.CanSeeTheBall() && wm.CanDoLocalizationDirectly())
		{
			turnHeadStrategy(fallDownTurnHead);

			//float ballMeToXAxisAngle=wm.GetLastCyclesAverageBallMeToXAxisAngle();
			//float ballGoalToXAxisAngle=wm.GetLastCyclesAverageBallGoalToXAxisAngle();

			destinationCoordinate = wm.GetLastCyclesAverageBallCoordinate();


			if (wm.GetMyDistanceToDestination(destination) > 2) ///need do some impove  //2
			{
				destination = wm.GetLastCyclesAverageBallCoordinate(); ///WalkToDestinationCoordinate(destinationCoordinate);
				angleToTurn = wm.GetMyBodyAngleToBall();
				if (ballCoordinate.x() < 8 && fabs(myCoordinate.y()) < 6  //3 3
									&& (ballCoordinate.x() > myCoordinate.x()))
							{
								//destination = wm.GetLastCyclesAverageBallCoordinate();
								destination = Vector3(ball.x()-1.5*1.66 ,ball.y()	,0);  //1.5
								angleToTurn = wm.GetMyBodyAngleToBall();
								topSpeed = MAX_SPEED;
							}

			}
			else if (wm.GetMyDistanceToDestination(destination) >= 0.7
					&& wm.GetMyDistanceToDestination(destination) <= 2) ///need do some impove
			{
				destination = wm.GetLastCyclesAverageBallCoordinate(); ///WalkToDestinationCoordinate(destinationCoordinate);
				angleToTurn = wm.GetMyBodyAngleToBall();
				if (fabs(angleToTurn) < 90)
				{
					angleToTurn = wm.GetMyBodyAngleToBall();
				}

				else
				{
					angleToTurn = 0;
				}
			}
			else if (wm.GetMyDistanceToDestination(destination) < 0.7)
			{
				if (fabs(wm.GetMyBodyAngleToBall()) < 45)
				{
#ifdef AGENT_STRATEGY_OUTPUT
					cout << "fabs(wm.GetMyBodyAngleToBall() )<45 " << endl;
#endif
					angleToTurn = wm.GetMyBodyAngleToBall();
#ifdef AGENT_STRATEGY_OUTPUT
					cout << "AAAAA11111111111111wm.GetMyBodyAngleToXAxis():    "
							<< wm.GetMyBodyAngleToXAxis() << endl;
					cout
							<< "AAAAA22222222222wm.GetLastCyclesAverageBallGoalToXAxisAngle(): "
							<< wm.GetLastCyclesAverageBallGoalToXAxisAngle()
							<< endl;
					cout << "AAAAA33333333angleToTurn:  " << angleToTurn
							<< endl;
#endif
					if (wm.WhetherCanAttackOppGoal2() == false)
					{

						//	angleToTurn=0;
						destination = WalkToDestinationCoordinate(
								destinationCoordinate);
#ifdef AGENT_STRATEGY_OUTPUT
						cout << "AAAAAA33333333333333333333333333333333"
								<< endl;
#endif
					}
					else ///if(wm.WhetherCanAttackOppGoal2()==true)         ///can not use,otherwish,it will execute two times
					{
						//	angleToTurn=wm.GetLastCyclesAverageBallGoalToXAxisAngle()-wm.GetMyBodyAngleToXAxis();
						destination = wm.GetLastCyclesAverageBallCoordinate();

						topSpeed = MAX_SPEED;

						if (fabs(angleToTurn) > 20)
						{
							topSpeed = MIN_SPEED;
						}
#ifdef AGENT_STRATEGY_OUTPUT
						cout << "AAAAAA44444444444444444444444444444444444"
								<< endl;
#endif

					}

				}
				else
				{
					angleToTurn = wm.GetLastCyclesAverageBallGoalToXAxisAngle()
							- wm.GetMyBodyAngleToXAxis();
#ifdef AGENT_STRATEGY_OUTPUT
					cout
							<< "BBBBBBB11111111111111wm.GetMyBodyAngleToXAxis():    "
							<< wm.GetMyBodyAngleToXAxis() << endl;
					cout
							<< "BBBBBB22222222222wm.GetLastCyclesAverageBallGoalToXAxisAngle(): "
							<< wm.GetLastCyclesAverageBallGoalToXAxisAngle()
							<< endl;
					cout << "BBBBBB33333333angleToTurn:  " << angleToTurn
							<< endl;
#endif
					if (wm.WhetherCanAttackOppGoal2() == false)
					{

						//	angleToTurn=0;
						destination = WalkToDestinationCoordinate(
								destinationCoordinate);
#ifdef AGENT_STRATEGY_OUTPUT
						cout << "BBBBBB33333333333333333333333333333333"
								<< endl;
#endif

					}
					else ///if(wm.WhetherCanAttackOppGoal2()==true)         ///can not use,otherwish,it will execute two times
					{
						//	angleToTurn=wm.GetLastCyclesAverageBallGoalToXAxisAngle()-wm.GetMyBodyAngleToXAxis();
						destination = wm.GetLastCyclesAverageBallCoordinate();

						topSpeed = MAX_SPEED;
#ifdef AGENT_STRATEGY_OUTPUT
						cout << "BBBBBB44444444444444444444444444444444444"
								<< endl;
#endif

					}

				}
			}

			if (ballCoordinate.x() < 8 && fabs(myCoordinate.y()) < 6  //3 3
					&& (ballCoordinate.x() > myCoordinate.x()))
			{
				//destination = wm.GetLastCyclesAverageBallCoordinate();
				destination = Vector3(ball.x()-3.5*1.66 ,ball.y()	,0);//1.5
				angleToTurn = wm.GetMyBodyAngleToBall();
				topSpeed = MAX_SPEED;
			}

		}
		else if (!wm.CanSeeTheBall() && wm.CanDoLocalizationDirectly())
		{
			turnHeadStrategy(fallDownTurnHead);

			angleToTurn = -wm.GetMyBodyAngleToXAxis();
			//	angleToTurn=0;
			//	angleToTurn=wm.GetLastCyclesAverageBallGoalToXAxisAngle()-wm.GetMyBodyAngleToXAxis();
			///		destination=wm.GetMyCoordinate();
			//	destination=Vector3(myCoordinate.x()+0.01,myCoordinate.y()+0.01,0);

			destination = WalkToDestinationCoordinate(
					wm.GetLastCyclesAverageBallCoordinate());
			///	destination=WalkToDestinationCoordinate(Vector3(9,0,0));
			///	topSpeed=MIN_SPEED;

		}
		else if (wm.CanSeeTheBall() && !wm.CanDoLocalizationDirectly())
		{
			turnHeadStrategy(fallDownTurnHead);

			angleToTurn = -wm.GetMyBodyAngleToXAxis();
			//	angleToTurn=0;
			//	angleToTurn=wm.GetLastCyclesAverageBallGoalToXAxisAngle()-wm.GetMyBodyAngleToXAxis();
			///		destination=wm.GetMyCoordinate();
			//	destination=Vector3(myCoordinate.x()+0.01,myCoordinate.y()+0.01,0);

			destination = WalkToDestinationCoordinate(
					wm.GetLastCyclesAverageBallCoordinate());
			///	destination=WalkToDestinationCoordinate(Vector3(9,0,0));
			///	topSpeed=MIN_SPEED;

		}
		else if (!wm.CanSeeTheBall() && !wm.CanDoLocalizationDirectly())
		{
			turnHeadStrategy(fallDownTurnHead);

			angleToTurn = -wm.GetMyBodyAngleToXAxis();
			//	angleToTurn=0;
			//	angleToTurn=wm.GetLastCyclesAverageBallGoalToXAxisAngle()-wm.GetMyBodyAngleToXAxis();
			///		destination=wm.GetMyCoordinate();
			//	destination=Vector3(myCoordinate.x()+0.01,myCoordinate.y()+0.01,0);

			destination = WalkToDestinationCoordinate(
					wm.GetLastCyclesAverageBallCoordinate());
			///	destination=WalkToDestinationCoordinate(Vector3(9,0,0));
			///	topSpeed=MIN_SPEED;
		}

		//	return NEWWALK(destination,angleToTurn,topSpeed);
	}
	else
	{
#ifdef AGENT_STRATEGY_OUTPUT
		cout << "CentreForwardAction2222222222222222:" << endl;
#endif
		if (wm.GetMyDistanceToBall()
				< wm.GetMyDistanceToTeammate(wm.GetVanguardNumber()))
		{
			destination = wm.GetLastCyclesAverageBallCoordinate();
					//	destination = Vector3(ball.x()-1.5*1.66 ,ball.y()	,0);
						angleToTurn = wm.GetMyBodyAngleToBall();
						topSpeed = MAX_SPEED;
		}
		else
		{
///			Vector3 ballCoordinate=wm.GetLastCyclesAverageBallCoordinate();
			///	destination=Vector3(  ballCoordinate.x()-0.33*(ballCoordinate.x()+wm.GetFieldLength()/2) , ballCoordinate.y()  ,0 );

			if (ball.x() > -5 * CELL_LENGTH)
				destination = Vector3(ball.x()-2*1.66 ,ball.y()	,0);
//						{  if(ball.x() > -2 * CELL_LENGTH)
//							destination = standBetweenBallAndMyGoal(
//									wm.GetBallToMyGoalDistance() / 3);
//						else
//						{
//							destination = standBetweenBallAndMyGoal(
//													wm.GetBallToMyGoalDistance() / 4);
//						}
//						}
			else
			{
			//	destination = Vector3(ball.x() + 4 * CELL_LENGTH,ball.y() / 2
				//						,0);
				destination = Vector3(ball.x() ,ball.y() / 2
						,0);

			}

			theNewWalkSolutions(destination, angleToTurn, topSpeed);
			angleToTurn = wm.GetMyBodyAngleToBall();
		}
		//	return NEWWALK(destination,angleToTurn,topSpeed);
	}

	float goalieToBallDistance;
	if (wm.GetGoalieToBallDistance(goalieToBallDistance) == true)
	{
		if (goalieToBallDistance < 1)
		{
			angleToTurn = -wm.GetMyBodyAngleToXAxis();
			if (myCoordinate.y() > ballCoordinate.y())
			{
				destination = Vector3(ballCoordinate.x() + 2.5,
						ballCoordinate.y() + 1, 0);
				///	  destination=Vector3(-8,ballCoordinate.y()+0.5,0);

			}
			else
			{

				destination = Vector3(ballCoordinate.x() + 1.5,
						ballCoordinate.y() - 1, 0);
			}
#ifdef AGENT_STRATEGY_OUTPUT
			cout << "goalieToBallDistance:" << goalieToBallDistance << endl;
#endif
		}
	}

	float lineBackerToBallDistance;
	if (wm.GetLineBackerToBallDistance(lineBackerToBallDistance) == true)
	{
		if (lineBackerToBallDistance < 1)
		{
			angleToTurn = -wm.GetMyBodyAngleToXAxis();
			if (myCoordinate.y() > ballCoordinate.y())
			{
				destination = Vector3(ballCoordinate.x() - 1.5,
						ballCoordinate.y() + 1, 0);
			}
			else
			{
				destination = Vector3(ballCoordinate.x() - 1.5,
						ballCoordinate.y() - 1, 0);
			}
#ifdef AGENT_STRATEGY_OUTPUT
			cout << "lineBackerToBallDistance:" << lineBackerToBallDistance
					<< endl;
#endif
		}
	}

	int teammateNumber;
		if (wm.WhetherMyTeammatesBlockMe(teammateNumber) == true)
		{
			Vector3 teammateCoordinate = wm.GetNewTeammateCoordinate(
					teammateNumber);
			float angle = wm.WhetherTeammateInMyWayToDestination(teammateCoordinate,
					my, destination);

#ifdef AGENT_STRATEGY_OUTPUT
			cout << "wm.WhetherMyTeammatesBlockMe()==true" << endl;

			cout<<"teammateNumber::"<<teammateNumber<<endl;
			cout<<"angle::"<<angle<<endl;
			cout<<"(teammateCoordinate-wm.GetMyCoordinate()).xymod()::"<<(teammateCoordinate-wm.GetMyCoordinate()).xymod()<<endl;
#endif
			if (angle<30||((teammateCoordinate-wm.GetMyCoordinate()).xymod()<1))
			{
				destination=Vector3Linelength(teammateCoordinate,wm.GetMyCoordinate(),0.5*CELL_LENGTH);
#ifdef AGENT_STRATEGY_OUTPUT
				cout << "wm.WhetherMyTeammatesBlockMe()==true" << endl;
				cout<<"change destination!!!!"<<endl;
#endif
		//		destination = Vector3(destination.x() + 0.1, destination.y() + 0.1,
		//				destination.z());
				topSpeed = MIDMIN_SPEED;
			}
			///return basicMotion.InitStandUpPose();
		}
	else
	{
		/*
		 if(ball.x()<-2*CELL_LENGTH)
		 {
		 if(ball.y()>0)
		 {
		 destination=Vector3(-5*CELL_LENGTH,ball.y()/2+(wm.GetMyNumber()%3)*CELL_LENGTH,0);
		 }
		 else if(ball.y()<=0)
		 {
		 destination=Vector3(-5*CELL_LENGTH,ball.y()/2-(wm.GetMyNumber()%3)*CELL_LENGTH,0);
		 }
		 }
		 else if(ball.x()>=-2*CELL_LENGTH&&ball.x()<1*CELL_LENGTH)
		 {
		 if(ball.y()>0)
		 {
		 destination=Vector3(ball.x()-3.5*CELL_LENGTH,ball.y()/2+(wm.GetMyNumber()%3)*CELL_LENGTH,0);
		 }
		 else if(ball.y()<=0)
		 {
		 destination=Vector3(ball.x()-3.5*CELL_LENGTH,ball.y()/2-(wm.GetMyNumber()%3)*CELL_LENGTH,0);
		 }
		 }
		 else
		 {
		 if(ball.y()>0)
		 {
		 destination=Vector3(-1*CELL_LENGTH,ball.y()/2+(wm.GetMyNumber()%3)*CELL_LENGTH,0);
		 }
		 else if(ball.y()<=0)
		 {
		 destination=Vector3(-1*CELL_LENGTH,ball.y()/2-(wm.GetMyNumber()%3)*CELL_LENGTH,0);
		 }
		 }

		 theNewWalkSolutions(destination,angleToTurn,topSpeed);*/

//		/	destination=standBetweenBallAndMyGoal(wm.GetBallToMyGoalDistance()/2);
		destination = Vector3((ball.x() - wm.GetFieldLength() / 2) * 0.4,
				ball.y(), 0);
		theNewWalkSolutions(destination, angleToTurn, topSpeed);
		angleToTurn = wm.GetMyBodyAngleToBall();
#ifdef AGENT_STRATEGY_OUTPUT
		cout << "wm.WhetherMyTeammatesBlockMe()==false" << endl;
#endif
	}
#ifdef AGENT_STRATEGY_OUTPUT
	cout << "CentreForward:_________________" << endl;
	cout << "angleToTurn:" << angleToTurn << endl;
	cout << "destination:" << destination << endl;
	cout << "topSpeed:" << topSpeed << endl;
#endif

	return NEWWALK(destination, angleToTurn, topSpeed);

}

Action Strategy::ViceCentreForward_1_Strategy()
{
	stringstream ss("");

	BehaviorDecision();
///	cout<<"       CentreForwardStrategy :       "<<wm.GetMyNumber()<<endl;
	switch (decisionChoice)
	{
	case WALK_TO_MY_POSITION:
#ifdef AGENT_STRATEGY_OUTPUT
		cout << "ViceCentreForward_1_walkToDestination" << endl;
#endif
		ss << ViceCentreForward_1_Action();
		break;
	case ALL_STOP_FOR_STAND_UP:
		ss << CITstandup.dealFallingDown();
		break;
	case SLIDE_TACKLE:
		ss << slideTackleToSaveBall();
		break;
	case SHOOT_BALL:
#ifdef AGENT_STRATEGY_OUTPUT
		cout << "ViceCentreForward_1_ShootBall" << endl;
#endif
		ss << stopAndShootting();
		break;

	case PREVENT_FALLING_DOWN:
		ss << CITstandup.DisposeFalling();
		//cout<<"DisposeFalling!!!"<<endl;
		break;

	case STAND_UP:
		ss << CITstandup.StandUp(); //do get up motion
		break;
	case DO_NOTHING:
		ss << basicMotion.StopAllMotion();
		break;
	default:
		ss << basicMotion.StopAllMotion();
	}
///	if(wm.GetTheMessageToSayAboutMyTeamMatePositon()!="000000000")
///	    ss<<mp.Say(wm.GetEncapsulatedWords(wm.GetTheMessageToSayAboutMyTeamMatePositon()));
	return ss.str();
}

Action Strategy::ViceCentreForward_1_Action()
{


	if(ballCoordinate.x()<myCoordinate.x())
				{//destination = ballCoordinate;
				//angleToTurn = localMyBodyAngleToBall;
				angleToTurn = localMyBodyAngleToBall;
				if(ball.y()>my.y())
				destination = Vector3(ball.x()-2.5*1.66 ,ball.y()-2.5*1.66
										,0);
				else
					destination = Vector3(ball.x()-2.5*1.66 ,ball.y()+2.5*1.66
															,0);


								///	angleToTurn=wm.GetMyAngleToDestination(destination);
								if (fabs(angleToTurn) < 70)
								{
									angleToTurn = localMyBodyAngleToBall;
								}
								else
								{
									//angleToTurn = -localMyBodyAngleToXAxis;
									angleToTurn = localMyBodyAngleToBall;
								}
				topSpeed = MAX_SPEED;

				}
	if (
													(wm.GetClosestToBallOpponentDistanceByVision()<0.7 &&wm.GetClosestToBallTeammateDistanceByVision()<0.7
													&&wm.GetMyDistanceToBall()<0.8*CELL_LENGTH
													//&&wm.GetMyDistanceToBall()< CELL_LENGTH
													)||(wm.GetClosestToBallOpponentDistanceByVision()<0.7&&wm.GetClosestToBallTeammateDistanceByVision()<0.4
															&&	wm.GetMyDistanceToBall()<0.7))
											{
												//return StopWhereAt();
		                                                                angleToTurn = localMyBodyAngleToBall;
											                                  topSpeed =NULL_SPEED;
		                                                          //  	topSpeed==AVOID_SPEED;
											                                    destination = ballCoordinate;
											                                    return NEWWALK(destination, angleToTurn, topSpeed);
											}
///  	Vector3 ballCoordinate=wm.GetLastCyclesAverageBallCoordinate();
///	Vector3 myCoordinate=wm.GetMyCoordinate();
	int mDisToBallIndex;
	wm.GetMyDistanceToBallSortedIndexOld(mDisToBallIndex);
#ifdef AGENT_STRATEGY_OUTPUT
	cout << "wm.GetMyDistanceToTeammate(wm.GetVanguardNumber():"
			<< wm.GetMyDistanceToTeammate(wm.GetVanguardNumber()) << endl;

	cout << "(wm.GetVanguardNumber():" << wm.GetVanguardNumber() << endl;
#endif
	if (wm.MyDistanceToBallSmallerThanMyDistanceToAnyTeammate() == true)
	{
#ifdef AGENT_STRATEGY_OUTPUT
		cout << "CentreForwardAction111111111111111:" << endl;
#endif
		Vector3 destinationCoordinate;
///		Vector3 ballCoordinate=wm.GetLastCyclesAverageBallCoordinate();
///		Vector3 myCoordinate=wm.GetMyCoordinate();

		if (wm.CanSeeTheBall() && wm.CanDoLocalizationDirectly())
		{
			turnHeadStrategy(fallDownTurnHead);

			/*float ballMeToXAxisAngle =
			 wm.GetLastCyclesAverageBallMeToXAxisAngle();
			 float ballGoalToXAxisAngle =
			 wm.GetLastCyclesAverageBallGoalToXAxisAngle();*/

			//destinationCoordinate = wm.GetLastCyclesAverageBallCoordinate();
			destination = ballCoordinate;

			if (wm.GetMyDistanceToDestination(destination) > 2) ///need do some impove
			{
				destination = wm.GetLastCyclesAverageBallCoordinate(); ///WalkToDestinationCoordinate(destinationCoordinate);
				angleToTurn = wm.GetMyBodyAngleToBall();
				if (ballCoordinate.x() < 8 && fabs(myCoordinate.y()) < 6  //3 3
									&& (ballCoordinate.x() > myCoordinate.x()))
							{
								//destination = wm.GetLastCyclesAverageBallCoordinate();
								destination = Vector3(ball.x()-3.5*1.66 ,ball.y()+2.5*CELL_LENGTH	,0);
								angleToTurn = wm.GetMyBodyAngleToBall();
								topSpeed = MAX_SPEED;
							}

			}
			else if (wm.GetMyDistanceToDestination(destination) >= 0.7
					&& wm.GetMyDistanceToDestination(destination) <= 2) ///need do some impove
			{
				destination = wm.GetLastCyclesAverageBallCoordinate(); ///WalkToDestinationCoordinate(destinationCoordinate);
				angleToTurn = wm.GetMyBodyAngleToBall();
				if (fabs(angleToTurn) < 90)
				{
					angleToTurn = wm.GetMyBodyAngleToBall();
				}
				else
				{
					angleToTurn = 0;
				}
			}
			else if (wm.GetMyDistanceToDestination(destination) < 0.7)
			{
				if (fabs(wm.GetMyBodyAngleToBall()) < 45)
				{
#ifdef AGENT_STRATEGY_OUTPUT
					cout << "fabs(wm.GetMyBodyAngleToBall() )<45 " << endl;
#endif
					angleToTurn = wm.GetMyBodyAngleToBall();
#ifdef AGENT_STRATEGY_OUTPUT
					cout << "AAAAA11111111111111wm.GetMyBodyAngleToXAxis():    "
							<< wm.GetMyBodyAngleToXAxis() << endl;
					cout
							<< "AAAAA22222222222wm.GetLastCyclesAverageBallGoalToXAxisAngle(): "
							<< wm.GetLastCyclesAverageBallGoalToXAxisAngle()
							<< endl;
					cout << "AAAAA33333333angleToTurn:  " << angleToTurn
							<< endl;
#endif
					if (wm.WhetherCanAttackOppGoal2() == false)
					{

						//	angleToTurn=0;
						destination = WalkToDestinationCoordinate(
								destinationCoordinate);
#ifdef AGENT_STRATEGY_OUTPUT
						cout << "AAAAAA33333333333333333333333333333333"
								<< endl;
#endif

					}
					else ///if(wm.WhetherCanAttackOppGoal2()==true)         ///can not use,otherwish,it will execute two times
					{
						//	angleToTurn=wm.GetLastCyclesAverageBallGoalToXAxisAngle()-wm.GetMyBodyAngleToXAxis();
						destination = wm.GetLastCyclesAverageBallCoordinate();

						topSpeed = MAX_SPEED;

						if (fabs(angleToTurn) > 20)
						{
							topSpeed = MIN_SPEED;
						}
#ifdef AGENT_STRATEGY_OUTPUT
						cout << "AAAAAA44444444444444444444444444444444444"
								<< endl;
#endif
					}

				}
				else
				{
					angleToTurn = wm.GetLastCyclesAverageBallGoalToXAxisAngle()
							- wm.GetMyBodyAngleToXAxis();
#ifdef AGENT_STRATEGY_OUTPUT
					cout
							<< "BBBBBBB11111111111111wm.GetMyBodyAngleToXAxis():    "
							<< wm.GetMyBodyAngleToXAxis() << endl;
					cout
							<< "BBBBBB22222222222wm.GetLastCyclesAverageBallGoalToXAxisAngle(): "
							<< wm.GetLastCyclesAverageBallGoalToXAxisAngle()
							<< endl;
					cout << "BBBBBB33333333angleToTurn:  " << angleToTurn
							<< endl;
#endif
					if (wm.WhetherCanAttackOppGoal2() == false)
					{

						//	angleToTurn=0;
						destination = WalkToDestinationCoordinate(
								destinationCoordinate);
#ifdef AGENT_STRATEGY_OUTPUT
						cout << "BBBBBB33333333333333333333333333333333"
								<< endl;
#endif

					}
					else ///if(wm.WhetherCanAttackOppGoal2()==true)         ///can not use,otherwish,it will execute two times
					{
						//	angleToTurn=wm.GetLastCyclesAverageBallGoalToXAxisAngle()-wm.GetMyBodyAngleToXAxis();
						destination = wm.GetLastCyclesAverageBallCoordinate();

						topSpeed = MAX_SPEED;
#ifdef AGENT_STRATEGY_OUTPUT
						cout << "BBBBBB44444444444444444444444444444444444"
								<< endl;
#endif
					}
				}
			}

			if (ballCoordinate.x() <7  && fabs(myCoordinate.y()) < 6//3 3
					&& (ballCoordinate.x() > myCoordinate.x()))
			{
				destination = Vector3(ball.x()-2.5*1.66 ,ball.y()-1.5*1.66
														,0);
				//destination = wm.GetLastCyclesAverageBallCoordinate();
				angleToTurn = wm.GetMyBodyAngleToBall();
				topSpeed = MAX_SPEED;
			}

		}
		else if (!wm.CanSeeTheBall() && wm.CanDoLocalizationDirectly())
		{
			turnHeadStrategy(fallDownTurnHead);

			angleToTurn = -wm.GetMyBodyAngleToXAxis();
			//	angleToTurn=0;
			//	angleToTurn=wm.GetLastCyclesAverageBallGoalToXAxisAngle()-wm.GetMyBodyAngleToXAxis();
			///		destination=wm.GetMyCoordinate();
			//	destination=Vector3(myCoordinate.x()+0.01,myCoordinate.y()+0.01,0);

			destination = WalkToDestinationCoordinate(
					wm.GetLastCyclesAverageBallCoordinate());
			///	destination=WalkToDestinationCoordinate(Vector3(9,0,0));
			///	topSpeed=MIN_SPEED;

		}
		else if (wm.CanSeeTheBall() && !wm.CanDoLocalizationDirectly())
		{
			turnHeadStrategy(fallDownTurnHead);

			angleToTurn = -wm.GetMyBodyAngleToXAxis();
			//	angleToTurn=0;
			//	angleToTurn=wm.GetLastCyclesAverageBallGoalToXAxisAngle()-wm.GetMyBodyAngleToXAxis();
			///		destination=wm.GetMyCoordinate();
			//	destination=Vector3(myCoordinate.x()+0.01,myCoordinate.y()+0.01,0);

			destination = WalkToDestinationCoordinate(
					wm.GetLastCyclesAverageBallCoordinate());
			///	destination=WalkToDestinationCoordinate(Vector3(9,0,0));
			///	topSpeed=MIN_SPEED;

		}
		else if (!wm.CanSeeTheBall() && !wm.CanDoLocalizationDirectly())
		{
			turnHeadStrategy(fallDownTurnHead);

			angleToTurn = -wm.GetMyBodyAngleToXAxis();
			//	angleToTurn=0;
			//	angleToTurn=wm.GetLastCyclesAverageBallGoalToXAxisAngle()-wm.GetMyBodyAngleToXAxis();
			///		destination=wm.GetMyCoordinate();
			//	destination=Vector3(myCoordinate.x()+0.01,myCoordinate.y()+0.01,0);

			destination = WalkToDestinationCoordinate(
					wm.GetLastCyclesAverageBallCoordinate());
			///	destination=WalkToDestinationCoordinate(Vector3(9,0,0));
			///	topSpeed=MIN_SPEED;
		}

		//	return NEWWALK(destination,angleToTurn,topSpeed);
	}
	else
	{
#ifdef AGENT_STRATEGY_OUTPUT
		cout << "CentreForwardAction2222222222222222:" << endl;
#endif
		if (wm.GetMyDistanceToBall()
				< wm.GetMyDistanceToTeammate(wm.GetVanguardNumber()))
		{
			destination = ballCoordinate;
							angleToTurn = wm.GetMyBodyAngleToBall();
							topSpeed = MAX_SPEED;
		}
		else
		{
///				Vector3 ballCoordinate=wm.GetLastCyclesAverageBallCoordinate();
//			destination = Vector3(
//					(ballCoordinate.x() - wm.GetFieldLength() / 2) / 2,
//					ballCoordinate.y() + 2, 0);
			destination = Vector3(ball.x()-2*1.66 ,ball.y()+1.5*CELL_LENGTH	,0);
			theNewWalkSolutions(destination, angleToTurn, topSpeed);
		}
		//	return NEWWALK(destination,angleToTurn,topSpeed);
	}

	float goalieToBallDistance;
	if (wm.GetGoalieToBallDistance(goalieToBallDistance) == true)
	{
		if (goalieToBallDistance < 1)
		{
			angleToTurn = -wm.GetMyBodyAngleToXAxis();
			if (myCoordinate.y() > ballCoordinate.y())
			{
				destination = Vector3(ballCoordinate.x() + 2.5,
						ballCoordinate.y() + 1, 0);
				///	  destination=Vector3(-8,ballCoordinate.y()+0.5,0);

			}
			else
			{

				destination = Vector3(ballCoordinate.x() + 2.5,
						ballCoordinate.y() - 1, 0);
			}
#ifdef AGENT_STRATEGY_OUTPUT
			cout << "goalieToBallDistance:" << goalieToBallDistance << endl;
#endif
		}
	}

	float lineBackerToBallDistance;
	if (wm.GetLineBackerToBallDistance(lineBackerToBallDistance) == true)
	{
		if (lineBackerToBallDistance < 1)
		{
			angleToTurn = -wm.GetMyBodyAngleToXAxis();
			if (myCoordinate.y() > ballCoordinate.y())
			{
				destination = Vector3(ballCoordinate.x() - 1.5,
						ballCoordinate.y() + 1, 0);
			}
			else
			{
				destination = Vector3(ballCoordinate.x() - 1.5,
						ballCoordinate.y() - 1, 0);
			}
#ifdef AGENT_STRATEGY_OUTPUT
			cout << "lineBackerToBallDistance:" << lineBackerToBallDistance
					<< endl;
#endif
		}
	}

	int teammateNumber;
		if (wm.WhetherMyTeammatesBlockMe(teammateNumber) == true)
		{
			Vector3 teammateCoordinate = wm.GetNewTeammateCoordinate(
					teammateNumber);
			float angle = wm.WhetherTeammateInMyWayToDestination(teammateCoordinate,
					my, destination);

#ifdef AGENT_STRATEGY_OUTPUT
			cout << "wm.WhetherMyTeammatesBlockMe()==true" << endl;

			cout<<"teammateNumber::"<<teammateNumber<<endl;
			cout<<"angle::"<<angle<<endl;
			cout<<"(teammateCoordinate-wm.GetMyCoordinate()).xymod()::"<<(teammateCoordinate-wm.GetMyCoordinate()).xymod()<<endl;
#endif
			if ((teammateCoordinate-wm.GetMyCoordinate()).xymod()<1)
			{
				destination=Vector3Linelength(teammateCoordinate,wm.GetMyCoordinate(),0.5*CELL_LENGTH);
#ifdef AGENT_STRATEGY_OUTPUT
				cout << "wm.WhetherMyTeammatesBlockMe()==true" << endl;
#endif
		//		destination = Vector3(destination.x() + 0.1, destination.y() + 0.1,
		//				destination.z());
#ifdef AGENT_STRATEGY_OUTPUT
				cout<<"change destination!!!!"<<endl;
#endif
				topSpeed = MIDMIN_SPEED;
			}
			///return basicMotion.InitStandUpPose();
		}
	else
	{

		if (ball.x() > -5 * CELL_LENGTH)
		{

			destination = standBetweenBallAndMyGoal(
					wm.GetBallToMyGoalDistance() * 0.6 + 0.8 * CELL_LENGTH);
		}
		else
		{
			destination = Vector3(ball.x() + 5 * CELL_LENGTH,ball.y() / 2,0);
		}

		theNewWalkSolutions(destination, angleToTurn, topSpeed);
		angleToTurn = wm.GetMyBodyAngleToBall();
#ifdef AGENT_STRATEGY_OUTPUT
		cout << "wm.WhetherMyTeammatesBlockMe()==false" << endl;
#endif
	}

	return NEWWALK(destination, angleToTurn, topSpeed);
}

Action Strategy::ViceCentreForward_2_Strategy()
{
	stringstream ss("");

	BehaviorDecision();
	switch (decisionChoice)
	{
	case WALK_TO_MY_POSITION:
		cout << "ViceCentreForward_2_walkToDestination" << endl;
		ss << ViceCentreForward_2_Action();
		break;
	case ALL_STOP_FOR_STAND_UP:
		///	ss<<readData.AllStop();
		ss << CITstandup.dealFallingDown();
		break;
	case SHOOT_BALL:
		cout << "ViceCentreForward_2_ShootBall" << endl;
		ss << stopAndShootting();
		break;
	case SLIDE_TACKLE:
		ss << slideTackleToSaveBall();
		break;

	case PREVENT_FALLING_DOWN:
		ss << CITstandup.DisposeFalling();
		//cout<<"DisposeFalling!!!"<<endl;
		break;

	case STAND_UP:
		ss << CITstandup.StandUp(); //do get up motion
		break;
	case DO_NOTHING:
		ss << basicMotion.StopAllMotion();
		break;
	default:
		ss << basicMotion.StopAllMotion();
	}
///	if(wm.GetTheMessageToSayAboutMyTeamMatePositon()!="000000000")
//	    ss<<mp.Say(wm.GetEncapsulatedWords(wm.GetTheMessageToSayAboutMyTeamMatePositon()));
	return ss.str();
}

Action Strategy::ViceCentreForward_2_Action()
{


	if(ballCoordinate.x()<myCoordinate.x())
				{//destination = ballCoordinate;
				destination=Vector3(ball.x()-3*CELL_LENGTH , ball.y() ,0);
				//angleToTurn = localMyBodyAngleToBall;
				angleToTurn = localMyBodyAngleToBall;

								///	angleToTurn=wm.GetMyAngleToDestination(destination);
								if (fabs(angleToTurn) < 70)
								{
									angleToTurn = localMyBodyAngleToBall;
								}
								else
								{
								//	angleToTurn = -localMyBodyAngleToXAxis;
									angleToTurn = localMyBodyAngleToBall;
								}
				topSpeed = MAX_SPEED;

				}
	if (
													(wm.GetClosestToBallOpponentDistanceByVision()<0.7 &&wm.GetClosestToBallTeammateDistanceByVision()<0.7
													&&wm.GetMyDistanceToBall()<0.8*CELL_LENGTH
													//&&wm.GetMyDistanceToBall()< CELL_LENGTH
													)||(wm.GetClosestToBallOpponentDistanceByVision()>0.7&&wm.GetClosestToBallTeammateDistanceByVision()<0.4
															&&	wm.GetMyDistanceToBall()<1*CELL_LENGTH))
											{
												//return StopWhereAt();
		 angleToTurn = localMyBodyAngleToBall;
											                            //        topSpeed =NULL_SPEED;
			topSpeed==AVOID_SPEED;
											                                    destination = ballCoordinate;
											                                    return NEWWALK(destination, angleToTurn, topSpeed);
											}
	/// 	Vector3 ballCoordinate=wm.GetLastCyclesAverageBallCoordinate();
///	Vector3 myCoordinate=wm.GetMyCoordinate();
	int mDisToBallIndex;
	wm.GetMyDistanceToBallSortedIndexOld(mDisToBallIndex);
	cout << "wm.GetMyDistanceToTeammate(wm.GetVanguardNumber():"
			<< wm.GetMyDistanceToTeammate(wm.GetVanguardNumber()) << endl;

	cout << "(wm.GetVanguardNumber():" << wm.GetVanguardNumber() << endl;
	if (wm.MyDistanceToBallSmallerThanMyDistanceToAnyTeammate() == true)
	{

		cout << "CentreForwardAction111111111111111:" << endl;
		Vector3 destinationCoordinate;
///		Vector3 ballCoordinate=wm.GetLastCyclesAverageBallCoordinate();
///		Vector3 myCoordinate=wm.GetMyCoordinate();

		if (wm.CanSeeTheBall() && wm.CanDoLocalizationDirectly())
		{
			turnHeadStrategy(fallDownTurnHead);

			/*float ballMeToXAxisAngle =
			 wm.GetLastCyclesAverageBallMeToXAxisAngle();
			 float ballGoalToXAxisAngle =
			 wm.GetLastCyclesAverageBallGoalToXAxisAngle();*/

			destinationCoordinate = wm.GetLastCyclesAverageBallCoordinate();

			if (wm.GetMyDistanceToDestination(destination) > 2) ///need do some impove
			{
				destination = wm.GetLastCyclesAverageBallCoordinate(); ///WalkToDestinationCoordinate(destinationCoordinate);
				angleToTurn = wm.GetMyBodyAngleToBall();
				destination = Vector3(ball.x()-3.5 ,ball.y()-2*CELL_LENGTH	,0);
			}
			else if (wm.GetMyDistanceToDestination(destination) >= 0.7
					&& wm.GetMyDistanceToDestination(destination) <= 2) ///need do some impove
			{
				destination = wm.GetLastCyclesAverageBallCoordinate(); ///WalkToDestinationCoordinate(destinationCoordinate);
				angleToTurn = wm.GetMyBodyAngleToBall();
				if (fabs(angleToTurn) < 90)
				{
					angleToTurn = wm.GetMyBodyAngleToBall();
				}
				else
				{
					angleToTurn = 0;
				}
			}
			else if (wm.GetMyDistanceToDestination(destination) < 0.7)
			{
				if (fabs(wm.GetMyBodyAngleToBall()) < 45)
				{
					cout << "fabs(wm.GetMyBodyAngleToBall() )<45 " << endl;
					angleToTurn = wm.GetMyBodyAngleToBall();

					cout << "AAAAA11111111111111wm.GetMyBodyAngleToXAxis():    "
							<< wm.GetMyBodyAngleToXAxis() << endl;
					cout
							<< "AAAAA22222222222wm.GetLastCyclesAverageBallGoalToXAxisAngle(): "
							<< wm.GetLastCyclesAverageBallGoalToXAxisAngle()
							<< endl;
					cout << "AAAAA33333333angleToTurn:  " << angleToTurn
							<< endl;
					if (wm.WhetherCanAttackOppGoal2() == false)
					{

						//	angleToTurn=0;
						destination = WalkToDestinationCoordinate(
								destinationCoordinate);
						cout << "AAAAAA33333333333333333333333333333333"
								<< endl;

					}
					else ///if(wm.WhetherCanAttackOppGoal2()==true)         ///can not use,otherwish,it will execute two times
					{
						//	angleToTurn=wm.GetLastCyclesAverageBallGoalToXAxisAngle()-wm.GetMyBodyAngleToXAxis();
						destination = wm.GetLastCyclesAverageBallCoordinate();

						topSpeed = MAX_SPEED;

						if (fabs(angleToTurn) > 20)
						{
							topSpeed = MIN_SPEED;
						}
						cout << "AAAAAA44444444444444444444444444444444444"
								<< endl;
					}

				}
				else
				{
					angleToTurn = wm.GetLastCyclesAverageBallGoalToXAxisAngle()
							- wm.GetMyBodyAngleToXAxis();
					cout
							<< "BBBBBBB11111111111111wm.GetMyBodyAngleToXAxis():    "
							<< wm.GetMyBodyAngleToXAxis() << endl;
					cout
							<< "BBBBBB22222222222wm.GetLastCyclesAverageBallGoalToXAxisAngle(): "
							<< wm.GetLastCyclesAverageBallGoalToXAxisAngle()
							<< endl;
					cout << "BBBBBB33333333angleToTurn:  " << angleToTurn
							<< endl;
					if (wm.WhetherCanAttackOppGoal2() == false)
					{

						//	angleToTurn=0;
						destination = WalkToDestinationCoordinate(
								destinationCoordinate);
						cout << "BBBBBB33333333333333333333333333333333"
								<< endl;

					}
					else ///if(wm.WhetherCanAttackOppGoal2()==true)         ///can not use,otherwish,it will execute two times
					{
						//	angleToTurn=wm.GetLastCyclesAverageBallGoalToXAxisAngle()-wm.GetMyBodyAngleToXAxis();
						destination = wm.GetLastCyclesAverageBallCoordinate();

						topSpeed = MAX_SPEED;
						cout << "BBBBBB44444444444444444444444444444444444"
								<< endl;
					}

				}
			}

			if (ballCoordinate.x() < 7&& fabs(myCoordinate.y()) < 6  //
					&& (ballCoordinate.x() > myCoordinate.x()))
			{
				//destination = wm.GetLastCyclesAverageBallCoordinate();
								destination = Vector3(ball.x()-2.5*1.66 ,ball.y()+1.5*CELL_LENGTH	,0);
									angleToTurn = wm.GetMyBodyAngleToBall();
									topSpeed = MAX_SPEED;
			}

		}
		else if (!wm.CanSeeTheBall() && wm.CanDoLocalizationDirectly())
		{
			turnHeadStrategy(fallDownTurnHead);
			angleToTurn = wm.GetMyBodyAngleToBall();
		//77777	angleToTurn = -wm.GetMyBodyAngleToXAxis();
			//	angleToTurn=0;
			//	angleToTurn=wm.GetLastCyclesAverageBallGoalToXAxisAngle()-wm.GetMyBodyAngleToXAxis();
			///		destination=wm.GetMyCoordinate();
			//	destination=Vector3(myCoordinate.x()+0.01,myCoordinate.y()+0.01,0);

			destination = WalkToDestinationCoordinate(
					wm.GetLastCyclesAverageBallCoordinate());
			///	destination=WalkToDestinationCoordinate(Vector3(9,0,0));
			///	topSpeed=MIN_SPEED;

		}
		else if (wm.CanSeeTheBall() && !wm.CanDoLocalizationDirectly())
		{
			turnHeadStrategy(fallDownTurnHead);
			angleToTurn = wm.GetMyBodyAngleToBall();
			//angleToTurn = -wm.GetMyBodyAngleToXAxis();
			//	angleToTurn=0;
			//	angleToTurn=wm.GetLastCyclesAverageBallGoalToXAxisAngle()-wm.GetMyBodyAngleToXAxis();
			///		destination=wm.GetMyCoordinate();
			//	destination=Vector3(myCoordinate.x()+0.01,myCoordinate.y()+0.01,0);

			destination = WalkToDestinationCoordinate(
					wm.GetLastCyclesAverageBallCoordinate());
			///	destination=WalkToDestinationCoordinate(Vector3(9,0,0));
			///	topSpeed=MIN_SPEED;

		}
		else if (!wm.CanSeeTheBall() && !wm.CanDoLocalizationDirectly())
		{
			turnHeadStrategy(fallDownTurnHead);

			angleToTurn = -wm.GetMyBodyAngleToXAxis();
			//	angleToTurn=0;
			//	angleToTurn=wm.GetLastCyclesAverageBallGoalToXAxisAngle()-wm.GetMyBodyAngleToXAxis();
			///		destination=wm.GetMyCoordinate();
			//	destination=Vector3(myCoordinate.x()+0.01,myCoordinate.y()+0.01,0);

			destination = WalkToDestinationCoordinate(
					wm.GetLastCyclesAverageBallCoordinate());
			///	destination=WalkToDestinationCoordinate(Vector3(9,0,0));
			///	topSpeed=MIN_SPEED;
		}

		//	return NEWWALK(destination,angleToTurn,topSpeed);
	}
	else
	{
		cout << "CentreForwardAction2222222222222222:" << endl;
		if (wm.GetMyDistanceToBall()
				< wm.GetMyDistanceToTeammate(wm.GetVanguardNumber()))
		{
			destination = ballCoordinate;
			//				destination=Vector3(ball.x()-3*CELL_LENGTH , ball.y() ,0);
							//angleToTurn = localMyBodyAngleToBall;
							angleToTurn = localMyBodyAngleToBall;

											///	angleToTurn=wm.GetMyAngleToDestination(destination);
											if (fabs(angleToTurn) < 70)
											{
												angleToTurn = localMyBodyAngleToBall;
											}
											else
											{
											//	angleToTurn = -localMyBodyAngleToXAxis;
												angleToTurn = localMyBodyAngleToBall;
											}
							topSpeed = MAX_SPEED;
		}
		else
		{

///		    Vector3 ballCoordinate=wm.GetLastCyclesAverageBallCoordinate();
//			destination = Vector3(
//					(ballCoordinate.x() - wm.GetFieldLength() / 2) / 2,
//					ballCoordinate.y() - 2, 0);
			destination = Vector3(ball.x()-2.5*1.66 ,ball.y()-1.5*CELL_LENGTH	,0);
			cout << "ViceCentreForward_2_Action" << endl;
			theNewWalkSolutions(destination, angleToTurn, topSpeed);
		}
		//	return NEWWALK(destination,angleToTurn,topSpeed);
	}

	float goalieToBallDistance;
	if (wm.GetGoalieToBallDistance(goalieToBallDistance) == true)
	{
		if (goalieToBallDistance < 1)
		{
			angleToTurn = -wm.GetMyBodyAngleToXAxis();
			if (myCoordinate.y() > ballCoordinate.y())
			{
				destination = Vector3(ballCoordinate.x() + 2.5,
						ballCoordinate.y() + 1, 0);
				///	  destination=Vector3(-8,ballCoordinate.y()+0.5,0);

			}
			else
			{

				destination = Vector3(ballCoordinate.x() + 1.5,
						ballCoordinate.y() - 1, 0);
			}

			cout << "goalieToBallDistance:" << goalieToBallDistance << endl;
		}
	}

	float lineBackerToBallDistance;
	if (wm.GetLineBackerToBallDistance(lineBackerToBallDistance) == true)
	{
		if (lineBackerToBallDistance < 1)
		{
			angleToTurn = -wm.GetMyBodyAngleToXAxis();
			if (myCoordinate.y() > ballCoordinate.y())
			{
				destination = Vector3(ballCoordinate.x() - 1.5,
						ballCoordinate.y() + 1, 0);
			}
			else
			{
				destination = Vector3(ballCoordinate.x() - 1.5,
						ballCoordinate.y() - 1, 0);
			}
			cout << "lineBackerToBallDistance:" << lineBackerToBallDistance
					<< endl;
		}
	}

	int teammateNumber;
		if (wm.WhetherMyTeammatesBlockMe(teammateNumber) == true)
		{
			Vector3 teammateCoordinate = wm.GetNewTeammateCoordinate(
					teammateNumber);
			float angle = wm.WhetherTeammateInMyWayToDestination(teammateCoordinate,
					my, destination);

	#ifdef AGENT_STRATEGY_OUTPUT
			cout << "wm.WhetherMyTeammatesBlockMe()==true" << endl;
	#endif
			cout<<"teammateNumber::"<<teammateNumber<<endl;
			cout<<"angle::"<<angle<<endl;
			cout<<"(teammateCoordinate-wm.GetMyCoordinate()).xymod()::"<<(teammateCoordinate-wm.GetMyCoordinate()).xymod()<<endl;
			if ((teammateCoordinate-wm.GetMyCoordinate()).xymod()<1)
			{
				destination=Vector3Linelength(teammateCoordinate,wm.GetMyCoordinate(),0.5*CELL_LENGTH);
				cout << "wm.WhetherMyTeammatesBlockMe()==true" << endl;
		//		destination = Vector3(destination.x() + 0.1, destination.y() + 0.1,
		//				destination.z());
				cout<<"change destination!!!!"<<endl;
				topSpeed = MIDMIN_SPEED;
			}
			///return basicMotion.InitStandUpPose();
		}
	else
	{

		if (ball.x() > -5 * CELL_LENGTH)
		{
			float dis;

			{
				dis = wm.GetBallToMyGoalDistance() * 0.56 + 0.8 * CELL_LENGTH;
			}
			if (wm.GetFieldLength() / 2
					- (wm.GetBallToMyGoalDistance() * 0.56 + 0.8 * CELL_LENGTH)
					> 3.2 * CELL_LENGTH && ball.x() < -1 * CELL_LENGTH)
			{
				dis = wm.GetBallToMyGoalDistance() - 3.2 * CELL_LENGTH;
			}

			destination = standBetweenBallAndMyGoal(dis);

		}
		else
		{
			destination = Vector3(ball.x() + 6.5 * CELL_LENGTH,ball.y() / 2,0);
		}

		theNewWalkSolutions(destination, angleToTurn, topSpeed);
		angleToTurn = wm.GetMyBodyAngleToBall();
#ifdef AGENT_STRATEGY_OUTPUT
		cout << "wm.WhetherMyTeammatesBlockMe()==false" << endl;
#endif
	}

	return NEWWALK(destination, angleToTurn, topSpeed);
}

Action Strategy::LinebackerStrategy()
{
	stringstream ss("");

	BehaviorDecision();
	switch (decisionChoice)
	{
	case WALK_TO_MY_POSITION:
		ss << LinebackerAction();
#ifdef AGENT_STRATEGY_OUTPUT
		cout << "LineBacker_walkToMyPosition" << endl;
#endif
		break;
	case ALL_STOP_FOR_STAND_UP:
		///	ss<<readData.AllStop();
		ss << CITstandup.dealFallingDown();
		break;

	case PREVENT_FALLING_DOWN:
		ss << CITstandup.DisposeFalling();
		//cout<<"DisposeFalling!!!"<<endl;
		break;

	case STAND_UP:
		ss << CITstandup.StandUp(); //do get up motion
		break;
	case SHOOT_BALL:
#ifdef AGENT_STRATEGY_OUTPUT
		cout << "Linebacker_ShootBall" << endl;
#endif
		ss << stopAndShootting();
		break;
	case DO_NOTHING:
		ss << basicMotion.StopAllMotion();
		break;
	default:
		ss << basicMotion.StopAllMotion();
	}
//	if(wm.GetTheMessageToSayAboutMyTeamMatePositon()!="000000000")
//	    ss<<mp.Say(wm.GetEncapsulatedWords(wm.GetTheMessageToSayAboutMyTeamMatePositon()));

//	ss<<mp.Say(wm.GetEncapsulatedWords("LineBacker"));

	return ss.str();
}

Action Strategy::LinebackerAction()
{
	int mDisToBallIndex;
	wm.GetMyDistanceToBallSortedIndexOld(mDisToBallIndex);
//	cout
//			<< "wm.GetMyDistanceToTeammate(wm.GetTheMinDistanceToBallTeammateNum()):"
//			<< wm.GetMyDistanceToTeammate(
//					wm.GetTheMinDistanceToBallTeammateNum()) << endl;
	Vector3 destinationCoordinate;
///	Vector3 ballCoordinate=wm.GetLastCyclesAverageBallCoordinate();
///	Vector3 myCoordinate=wm.GetMyCoordinate();	
	float goalieToBallDistance;
	wm.GetGoalieToBallDistance(goalieToBallDistance);
#ifdef AGENT_STRATEGY_OUTPUT
	cout<<"LinebackerAction goalieToBallDistance::"<<goalieToBallDistance<<endl;
	cout << "wm.GetTheMinDistanceToBallTeammateNum():"
			<< wm.GetTheMinDistanceToBallTeammateNum() << endl;
#endif
	if ((wm.MyDistanceToBallSmallerThanMyDistanceToAnyTeammate() == true
			&& ballCoordinate.x() < -5.2 * CELL_LENGTH)
			|| wm.GetMyDistanceToBall() < 0.5)
	{
#ifdef AGENT_STRATEGY_OUTPUT
		cout << "LinebackerAction111111111111111:" << endl;
#endif
		if (wm.CanSeeTheBall() && wm.CanDoLocalizationDirectly())
		{
			turnHeadStrategy(fallDownTurnHead);

			/*float ballMeToXAxisAngle =
			 wm.GetLastCyclesAverageBallMeToXAxisAngle();
			 float ballGoalToXAxisAngle =
			 wm.GetLastCyclesAverageBallGoalToXAxisAngle();*/

			destinationCoordinate = wm.GetLastCyclesAverageBallCoordinate();

			if (wm.GetMyDistanceToDestination(destination) > 2) ///need do some impove
			{
				destination = WalkToDestinationCoordinate(
						destinationCoordinate);
				angleToTurn = wm.GetMyBodyAngleToBall();
			}
			else if (wm.GetMyDistanceToDestination(destination) >= 0.7
					&& wm.GetMyDistanceToDestination(destination) <= 2) ///need do some impove
			{
				destination = WalkToDestinationCoordinate(
						destinationCoordinate);
				angleToTurn = wm.GetMyBodyAngleToBall();
				if (fabs(angleToTurn) < 90)
				{
					angleToTurn = wm.GetMyBodyAngleToBall();
				}
				else
				{
					angleToTurn = 0;
				}
			}
			else if (wm.GetMyDistanceToDestination(destination) < 0.7)
			{

				if (fabs(wm.GetMyBodyAngleToBall()) < 45)
				{
#ifdef AGENT_STRATEGY_OUTPUT
					cout << "fabs(wm.GetMyBodyAngleToBall() )<45 " << endl;
#endif
					angleToTurn = wm.GetMyBodyAngleToBall();
#ifdef AGENT_STRATEGY_OUTPUT
					cout << "AAAAA11111111111111wm.GetMyBodyAngleToXAxis():    "
							<< wm.GetMyBodyAngleToXAxis() << endl;
					cout
							<< "AAAAA22222222222wm.GetLastCyclesAverageBallGoalToXAxisAngle(): "
							<< wm.GetLastCyclesAverageBallGoalToXAxisAngle()
							<< endl;
					cout << "AAAAA33333333angleToTurn:  " << angleToTurn
							<< endl;
#endif
					if (wm.WhetherCanAttackOppGoal2() == false)
					{

						//	angleToTurn=0;
						destination = WalkToDestinationCoordinate(
								destinationCoordinate);
#ifdef AGENT_STRATEGY_OUTPUT
						cout << "AAAAAA33333333333333333333333333333333"
								<< endl;
#endif

					}
					else ///if(wm.WhetherCanAttackOppGoal2()==true)         ///can not use,otherwish,it will execute two times
					{
						//	angleToTurn=wm.GetLastCyclesAverageBallGoalToXAxisAngle()-wm.GetMyBodyAngleToXAxis();
						destination = wm.GetLastCyclesAverageBallCoordinate();

						topSpeed = MAX_SPEED;

						if (fabs(angleToTurn) > 20)
						{
							topSpeed = MIN_SPEED;
						}
#ifdef AGENT_STRATEGY_OUTPUT
						cout << "AAAAAA44444444444444444444444444444444444"
								<< endl;
#endif
					}

				}
				else
				{
					angleToTurn = wm.GetLastCyclesAverageBallGoalToXAxisAngle()
							- wm.GetMyBodyAngleToXAxis();
#ifdef AGENT_STRATEGY_OUTPUT
					cout
							<< "BBBBBBB11111111111111wm.GetMyBodyAngleToXAxis():    "
							<< wm.GetMyBodyAngleToXAxis() << endl;
					cout
							<< "BBBBBB22222222222wm.GetLastCyclesAverageBallGoalToXAxisAngle(): "
							<< wm.GetLastCyclesAverageBallGoalToXAxisAngle()
							<< endl;
					cout << "BBBBBB33333333angleToTurn:  " << angleToTurn
							<< endl;
#endif
					if (wm.WhetherCanAttackOppGoal2() == false)
					{

						//	angleToTurn=0;
						destination = WalkToDestinationCoordinate(
								destinationCoordinate);
#ifdef AGENT_STRATEGY_OUTPUT
						cout << "BBBBBB33333333333333333333333333333333"
								<< endl;
#endif

					}
					else ///if(wm.WhetherCanAttackOppGoal2()==true)         ///can not use,otherwish,it will execute two times
					{
						//	angleToTurn=wm.GetLastCyclesAverageBallGoalToXAxisAngle()-wm.GetMyBodyAngleToXAxis();
						destination = wm.GetLastCyclesAverageBallCoordinate();

						topSpeed = MAX_SPEED;
#ifdef AGENT_STRATEGY_OUTPUT
						cout << "BBBBBB44444444444444444444444444444444444"
								<< endl;
#endif
					}

				}
			}


			{
				initPass = false;
				return NEWWALK(destination, angleToTurn, topSpeed);
			}

			if (ballCoordinate.x() < 3 && fabs(myCoordinate.y()) < 3
					&& (ballCoordinate.x() > myCoordinate.x()))
			{
				destination = wm.GetLastCyclesAverageBallCoordinate();
				angleToTurn = wm.GetMyBodyAngleToBall();
				topSpeed = MAX_SPEED;
			}

		}
		else if (!wm.CanSeeTheBall() && wm.CanDoLocalizationDirectly())
		{
			turnHeadStrategy(fallDownTurnHead);

			angleToTurn = -wm.GetMyBodyAngleToXAxis();
			//	angleToTurn=0;
			//	angleToTurn=wm.GetLastCyclesAverageBallGoalToXAxisAngle()-wm.GetMyBodyAngleToXAxis();
			///		destination=wm.GetMyCoordinate();
			//	destination=Vector3(myCoordinate.x()+0.01,myCoordinate.y()+0.01,0);

			destination = WalkToDestinationCoordinate(
					wm.GetLastCyclesAverageBallCoordinate());
			///	destination=WalkToDestinationCoordinate(Vector3(9,0,0));
			///	topSpeed=MIN_SPEED;

		}
		else if (wm.CanSeeTheBall() && !wm.CanDoLocalizationDirectly())
		{
			turnHeadStrategy(fallDownTurnHead);

			angleToTurn = -wm.GetMyBodyAngleToXAxis();
			//	angleToTurn=0;
			//	angleToTurn=wm.GetLastCyclesAverageBallGoalToXAxisAngle()-wm.GetMyBodyAngleToXAxis();
			///		destination=wm.GetMyCoordinate();
			//	destination=Vector3(myCoordinate.x()+0.01,myCoordinate.y()+0.01,0);

			destination = WalkToDestinationCoordinate(
					wm.GetLastCyclesAverageBallCoordinate());
			///	destination=WalkToDestinationCoordinate(Vector3(9,0,0));
			///	topSpeed=MIN_SPEED;

		}
		else if (!wm.CanSeeTheBall() && !wm.CanDoLocalizationDirectly())
		{
			turnHeadStrategy(fallDownTurnHead);

			angleToTurn = -wm.GetMyBodyAngleToXAxis();
			//	angleToTurn=0;
			//	angleToTurn=wm.GetLastCyclesAverageBallGoalToXAxisAngle()-wm.GetMyBodyAngleToXAxis();
			///		destination=wm.GetMyCoordinate();
			//	destination=Vector3(myCoordinate.x()+0.01,myCoordinate.y()+0.01,0);

			destination = WalkToDestinationCoordinate(
					wm.GetLastCyclesAverageBallCoordinate());
			///	destination=WalkToDestinationCoordinate(Vector3(9,0,0));
			///	topSpeed=MIN_SPEED;
		}

//		return NEWWALK(destination,angleToTurn,topSpeed);
	}
	else
	{
#ifdef AGENT_STRATEGY_OUTPUT
		cout << "LinebackerAction:" << endl;
#endif
		///	if(wm.GetMyDistanceToBall()<wm.GetMyDistanceToTeammate(wm.GetVanguardNumber()))
		{

		}
		///	else
		{

			///	destination=Vector3(  -0.8*wm.GetFieldLength()/2,1  ,0 );
			Vector3 Goalcenter=Vector3(-wm.GetFieldLength()/2,0,0);
			float lll=2*GOAL_HALFLENGTH;
//			cout<<"lll::"<<lll<<endl;
			destination=Vector3Linelength(ballCoordinate,Goalcenter,lll,false);
		//	destination = standBetweenBallAndMyGoal(
//					wm.GetBallToMyGoalDistance() - 1.7 * CELL_LENGTH);
			///	destination=Vector3(destination.x()+1.8*CELL_LENGTH,destination.y(),destination.z());
//			cout<<"Goalcenter::"<<Goalcenter<<endl;
//			cout<<"ballCoordinate::"<<ballCoordinate<<endl;
//			cout<<"destination::"<<destination<<endl;
//			cout<<"GetMyCoordinate::"<<wm.GetMyCoordinate()<<endl;

			theNewWalkSolutions(destination, angleToTurn, topSpeed);
			angleToTurn = wm.GetMyBodyAngleToBall();

		}
//		return NEWWALK(destination,angleToTurn,topSpeed);
	}

	if (wm.GetGoalieToBallDistance(goalieToBallDistance) == true)
	{
		if (goalieToBallDistance < 1)
		{
			angleToTurn = -wm.GetMyBodyAngleToXAxis();
			destination = Vector3(ballCoordinate.x() + 1.5,
					ballCoordinate.y() + 0.75, 0);
#ifdef AGENT_STRATEGY_OUTPUT
			cout << "goalieToBallDistance:" << goalieToBallDistance << endl;
#endif
		}
	}

	int teammateNumber;
		if (wm.WhetherMyTeammatesBlockMe(teammateNumber) == true)
		{
			Vector3 teammateCoordinate = wm.GetNewTeammateCoordinate(
					teammateNumber);
			float angle = wm.WhetherTeammateInMyWayToDestination(teammateCoordinate,
					my, destination);

	#ifdef AGENT_STRATEGY_OUTPUT
			cout << "wm.WhetherMyTeammatesBlockMe()==true" << endl;

			cout<<"teammateNumber::"<<teammateNumber<<endl;
			cout<<"angle::"<<angle<<endl;
			cout<<"(teammateCoordinate-wm.GetMyCoordinate()).xymod()::"<<(teammateCoordinate-wm.GetMyCoordinate()).xymod()<<endl;
#endif
			if (fabs(angle) < 30||(teammateCoordinate-wm.GetMyCoordinate()).xymod()<1)
			{
				destination=Vector3Linelength(teammateCoordinate,wm.GetMyCoordinate(),0.5*CELL_LENGTH);
#ifdef AGENT_STRATEGY_OUTPUT
				cout << "wm.WhetherMyTeammatesBlockMe()==true" << endl;
		//		destination = Vector3(destination.x() + 0.1, destination.y() + 0.1,
		//				destination.z());
				cout<<"change destination!!!!"<<endl;
#endif
				topSpeed = MIDMIN_SPEED;
			}
			///return basicMotion.InitStandUpPose();
		}
	else
	{
//		cout << "wm.WhetherMyTeammatesBlockMe()==false" << endl;
	}
#ifdef AGENT_STRATEGY_OUTPUT
	cout << "LineBacker:_________________" << endl;
	cout << "angleToTurn:" << angleToTurn << endl;
	cout << "destination:" << destination << endl;
	cout << "topSpeed:" << topSpeed << endl;
	cout << "MyCoordinate::" << myCoordinate << endl;
#endif
//destination=Vector3(-7,2,0);
//theNewWalkSolutions(destination,angleToTurn,topSpeed);
	return NEWWALK(destination, angleToTurn, topSpeed);
}


/////////////////////////////////////////////////////////

Action Strategy::ViceLinebacker_1_Strategy()
{
	stringstream ss("");

	BehaviorDecision();
	switch (decisionChoice)
	{
	case WALK_TO_MY_POSITION:
		ss << ViceLinebacker_1_Action();
#ifdef AGENT_STRATEGY_OUTPUT
		cout << "ViceLinebacker_1_WalkToPostion" << endl;
#endif
		break;
	case ALL_STOP_FOR_STAND_UP:
		ss << CITstandup.dealFallingDown();
		break;

	case PREVENT_FALLING_DOWN:
		ss << CITstandup.DisposeFalling();
		//cout<<"DisposeFalling!!!"<<endl;
		break;
	case SLIDE_TACKLE:
		ss << slideTackleToSaveBall();
		break;

	case STAND_UP:
		ss << CITstandup.StandUp(); //do get up motion
		break;
	case SHOOT_BALL:
#ifdef AGENT_STRATEGY_OUTPUT
		cout << "ViceLinebacker_1_ShootBall" << endl;
#endif
		ss << stopAndShootting();
		break;
	case DO_NOTHING:
		ss << basicMotion.StopAllMotion();
		break;
	default:
		ss << basicMotion.StopAllMotion();
	}
//	if(wm.GetTheMessageToSayAboutMyTeamMatePositon()!="000000000")
//	    ss<<mp.Say(wm.GetEncapsulatedWords(wm.GetTheMessageToSayAboutMyTeamMatePositon()));
	return ss.str();
}

Action Strategy::ViceLinebacker_1_Action()
{if(ballCoordinate.x()<myCoordinate.x()&&myCoordinate.x()>-5*CELL_LENGTH
)
{
if (/*(wm.GetMyDistanceToDestination(destination) < 0.5 * CELL_LENGTH
			&& fabs(wm.GetMyBodyAngleToXAxis()) < 60) ||*/
			(wm.GetClosestToBallOpponentDistanceByVision()<0.8 &&wm.GetClosestToBallTeammateDistanceByVision()<0.6
														&&wm.GetMyDistanceToBall()<0.8*CELL_LENGTH
														//&&wm.GetMyDistanceToBall()< CELL_LENGTH
														)||(wm.GetClosestToBallOpponentDistanceByVision()>0.8*CELL_LENGTH && wm.GetClosestToBallTeammateDistanceByVision()<0.55
																&&	wm.GetMyDistanceToBall()<0.8*CELL_LENGTH))
	{
		//return StopWhereAt();
	 angleToTurn = localMyBodyAngleToBall;
								                                    topSpeed =NULL_SPEED;
								                                    destination = ballCoordinate;
								                                    return NEWWALK(destination, angleToTurn, topSpeed);

	}
{destination = ballCoordinate;
//angleToTurn = localMyBodyAngleToBall;
angleToTurn = localMyBodyAngleToBall;

		///	angleToTurn=wm.GetMyAngleToDestination(destination);
		if (fabs(angleToTurn) < 70)
		{
			angleToTurn = localMyBodyAngleToBall;
		}
		else
		{
			//angleToTurn = -localMyBodyAngleToXAxis;
			angleToTurn = localMyBodyAngleToBall;
		}
topSpeed = MAX_SPEED;
return NEWWALK(destination, angleToTurn, topSpeed);
}
}
	int mDisToBallIndex;
	wm.GetMyDistanceToBallSortedIndexOld(mDisToBallIndex);
//	cout
//			<< "wm.GetMyDistanceToTeammate(wm.GetTheMinDistanceToBallTeammateNum()):"
//			<< wm.GetMyDistanceToTeammate(
//					wm.GetTheMinDistanceToBallTeammateNum()) << endl;
	Vector3 destinationCoordinate;
///	Vector3 ballCoordinate=wm.GetLastCyclesAverageBallCoordinate();
///	Vector3 myCoordinate=wm.GetMyCoordinate();	
#ifdef AGENT_STRATEGY_OUTPUT
	cout << "wm.GetTheMinDistanceToBallTeammateNum():"
			<< wm.GetTheMinDistanceToBallTeammateNum() << endl;
#endif
	float goalieToBallDistance;
	wm.GetGoalieToBallDistance(goalieToBallDistance);
#ifdef AGENT_STRATEGY_OUTPUT
	cout<<"ViceLinebacker_1_Action goalieToBallDistance::"<<goalieToBallDistance<<endl;
#endif
	if (wm.MyDistanceToBallSmallerThanMyDistanceToAnyTeammate() == true
			&& ballCoordinate.x() < -2.5 * CELL_LENGTH&&wm.GetMyDistanceToBall() < CELL_LENGTH)
	{
#ifdef AGENT_STRATEGY_OUTPUT
		cout << "LinebackerAction111111111111111:" << endl;
#endif

		if (wm.CanSeeTheBall() && wm.CanDoLocalizationDirectly())
		{
			turnHeadStrategy(fallDownTurnHead);

			/*float ballMeToXAxisAngle =
			 wm.GetLastCyclesAverageBallMeToXAxisAngle();
			 float ballGoalToXAxisAngle =
			 wm.GetLastCyclesAverageBallGoalToXAxisAngle();*/

			destinationCoordinate = wm.GetLastCyclesAverageBallCoordinate();

			if (wm.GetMyDistanceToDestination(destination) > 2) ///need do some impove
			{
				destination = WalkToDestinationCoordinate(
						destinationCoordinate);
				angleToTurn = wm.GetMyBodyAngleToBall();
			}
			else if (wm.GetMyDistanceToDestination(destination) >= 0.7
					&& wm.GetMyDistanceToDestination(destination) <= 2) ///need do some impove
			{
				destination = WalkToDestinationCoordinate(
						destinationCoordinate);
				angleToTurn = wm.GetMyBodyAngleToBall();
				if (fabs(angleToTurn) < 90)
				{
					angleToTurn = wm.GetMyBodyAngleToBall();
				}
				else
				{
					angleToTurn = 0;
				}
			}
			else if (wm.GetMyDistanceToDestination(destination) < 0.7)
			{

				if (fabs(wm.GetMyBodyAngleToBall()) < 45)
				{
#ifdef AGENT_STRATEGY_OUTPUT
					cout << "fabs(wm.GetMyBodyAngleToBall() )<45 " << endl;
#endif
					angleToTurn = wm.GetMyBodyAngleToBall();
#ifdef AGENT_STRATEGY_OUTPUT
					cout << "AAAAA11111111111111wm.GetMyBodyAngleToXAxis():    "
							<< wm.GetMyBodyAngleToXAxis() << endl;
					cout
							<< "AAAAA22222222222wm.GetLastCyclesAverageBallGoalToXAxisAngle(): "
							<< wm.GetLastCyclesAverageBallGoalToXAxisAngle()
							<< endl;
					cout << "AAAAA33333333angleToTurn:  " << angleToTurn
							<< endl;
#endif
					if (wm.WhetherCanAttackOppGoal2() == false)
					{

						//	angleToTurn=0;
						destination = WalkToDestinationCoordinate(
								destinationCoordinate);
#ifdef AGENT_STRATEGY_OUTPUT
						cout << "AAAAAA33333333333333333333333333333333"
								<< endl;
#endif

					}
					else ///if(wm.WhetherCanAttackOppGoal2()==true)         ///can not use,otherwish,it will execute two times
					{
						//	angleToTurn=wm.GetLastCyclesAverageBallGoalToXAxisAngle()-wm.GetMyBodyAngleToXAxis();
						destination = wm.GetLastCyclesAverageBallCoordinate();

						topSpeed = MAX_SPEED;

						if (fabs(angleToTurn) > 20)
						{
							topSpeed = MIN_SPEED;
						}
#ifdef AGENT_STRATEGY_OUTPUT
						cout << "AAAAAA44444444444444444444444444444444444"
								<< endl;
#endif
					}

				}
				else
				{
					angleToTurn = wm.GetLastCyclesAverageBallGoalToXAxisAngle()
							- wm.GetMyBodyAngleToXAxis();
#ifdef AGENT_STRATEGY_OUTPUT
					cout
							<< "BBBBBBB11111111111111wm.GetMyBodyAngleToXAxis():    "
							<< wm.GetMyBodyAngleToXAxis() << endl;
					cout
							<< "BBBBBB22222222222wm.GetLastCyclesAverageBallGoalToXAxisAngle(): "
							<< wm.GetLastCyclesAverageBallGoalToXAxisAngle()
							<< endl;
					cout << "BBBBBB33333333angleToTurn:  " << angleToTurn
							<< endl;
#endif
					if (wm.WhetherCanAttackOppGoal2() == false)
					{

						//	angleToTurn=0;
						destination = WalkToDestinationCoordinate(
								destinationCoordinate);
#ifdef AGENT_STRATEGY_OUTPUT
						cout << "BBBBBB33333333333333333333333333333333"
								<< endl;
#endif

					}
					else ///if(wm.WhetherCanAttackOppGoal2()==true)         ///can not use,otherwish,it will execute two times
					{
						//	angleToTurn=wm.GetLastCyclesAverageBallGoalToXAxisAngle()-wm.GetMyBodyAngleToXAxis();
						destination = wm.GetLastCyclesAverageBallCoordinate();

						topSpeed = MAX_SPEED;
#ifdef AGENT_STRATEGY_OUTPUT
						cout << "BBBBBB44444444444444444444444444444444444"
								<< endl;
#endif
					}

				}
			}

			if (wm.GetMyDistanceToBall() < 0.8
					&& fabs(wm.GetMyBodyAngleToBall()) < 25 && ballCoordinate.x() <-4.5*CELL_LENGTH)
			{
				PassDirection passDirection;
				if (initPass == false)
				{
					newWalk.initPass(); ///should be init before pass ball
					initPass = true;
				}
#ifdef AGENT_STRATEGY_OUTPUT
				cout
						<< "777777777777777777777777777777777777777777PassDirection passDirection=PASS_FRONT;"
						<< endl;
#endif
				passDirection = estimatePassDirection();

				return newWalk.PassBall(passDirection);
			}
			else
			{
				initPass = false;
				return NEWWALK(destination, angleToTurn, topSpeed);
			}

			if (ballCoordinate.x() < 3 && fabs(myCoordinate.y()) < 3
					&& (ballCoordinate.x() > myCoordinate.x()))
			{
				destination = wm.GetLastCyclesAverageBallCoordinate();
				angleToTurn = wm.GetMyBodyAngleToBall();
				topSpeed = MAX_SPEED;
			}

		}
		else if (!wm.CanSeeTheBall() && wm.CanDoLocalizationDirectly())
		{
			turnHeadStrategy(fallDownTurnHead);

			angleToTurn = -wm.GetMyBodyAngleToXAxis();
			//	angleToTurn=0;
			//	angleToTurn=wm.GetLastCyclesAverageBallGoalToXAxisAngle()-wm.GetMyBodyAngleToXAxis();
			///		destination=wm.GetMyCoordinate();
			//	destination=Vector3(myCoordinate.x()+0.01,myCoordinate.y()+0.01,0);

			destination = WalkToDestinationCoordinate(
					wm.GetLastCyclesAverageBallCoordinate());
			///	destination=WalkToDestinationCoordinate(Vector3(9,0,0));
			///	topSpeed=MIN_SPEED;

		}
		else if (wm.CanSeeTheBall() && !wm.CanDoLocalizationDirectly())
		{
			turnHeadStrategy(fallDownTurnHead);

			angleToTurn = -wm.GetMyBodyAngleToXAxis();
			//	angleToTurn=0;
			//	angleToTurn=wm.GetLastCyclesAverageBallGoalToXAxisAngle()-wm.GetMyBodyAngleToXAxis();
			///		destination=wm.GetMyCoordinate();
			//	destination=Vector3(myCoordinate.x()+0.01,myCoordinate.y()+0.01,0);

			destination = WalkToDestinationCoordinate(
					wm.GetLastCyclesAverageBallCoordinate());
			///	destination=WalkToDestinationCoordinate(Vector3(9,0,0));
			///	topSpeed=MIN_SPEED;

		}
		else if (!wm.CanSeeTheBall() && !wm.CanDoLocalizationDirectly())
		{
			turnHeadStrategy(fallDownTurnHead);

			angleToTurn = -wm.GetMyBodyAngleToXAxis();
			//	angleToTurn=0;
			//	angleToTurn=wm.GetLastCyclesAverageBallGoalToXAxisAngle()-wm.GetMyBodyAngleToXAxis();
			///		destination=wm.GetMyCoordinate();
			//	destination=Vector3(myCoordinate.x()+0.01,myCoordinate.y()+0.01,0);

			destination = WalkToDestinationCoordinate(
					wm.GetLastCyclesAverageBallCoordinate());
			///	destination=WalkToDestinationCoordinate(Vector3(9,0,0));
			///	topSpeed=MIN_SPEED;
		}

//		return NEWWALK(destination,angleToTurn,topSpeed);
	}
	else
	{
#ifdef AGENT_STRATEGY_OUTPUT
		cout << "LinebackerAction11111111111:" << endl;
#endif
		///	if(wm.GetMyDistanceToBall()<wm.GetMyDistanceToTeammate(wm.GetVanguardNumber()))
		{

		}
		///	else
		{

			///	destination=Vector3(  -0.8*wm.GetFieldLength()/2,1  ,0 );

		//	float dis;
//	if(wm.GetFieldLength()/2-wm.GetBallToMyGoalDistance()*0.6>2.4*CELL_LENGTH)
//			{
//				dis = wm.GetBallToMyGoalDistance() * 0.6;
//			}
//			if (wm.GetFieldLength() / 2 - wm.GetBallToMyGoalDistance() * 0.6
//					< 2.4 * CELL_LENGTH && ball.x() < -1 * CELL_LENGTH)
//			{
//				dis = wm.GetBallToMyGoalDistance() - 2.4 * CELL_LENGTH;
//			}
//
//			destination = standBetweenBallAndMyGoal(dis);

			Vector3 Goalcenter=Vector3(-wm.GetFieldLength()/2,0,0);
			destination=Vector3Linelength(ballCoordinate,Goalcenter,4*GOAL_HALFLENGTH,false);
//			cout<<"Goalcenter::"<<Goalcenter<<endl;
//			cout<<"ballCoordinate::"<<ballCoordinate<<endl;
//			cout<<"destination::"<<destination<<endl;
//			cout<<"GetMyCoordinate::"<<wm.GetMyCoordinate()<<endl;
			///	destination=Vector3(destination.x()+1.8*CELL_LENGTH,destination.y(),destination.z());
			theNewWalkSolutions(destination, angleToTurn, topSpeed);
			angleToTurn = wm.GetMyBodyAngleToBall();

		}
//		return NEWWALK(destination,angleToTurn,topSpeed);
	}

	if (wm.GetGoalieToBallDistance(goalieToBallDistance) == true)
	{
		if (goalieToBallDistance < 1)
		{
			angleToTurn = -wm.GetMyBodyAngleToXAxis();
			destination = Vector3(ballCoordinate.x() + 1.5,
					ballCoordinate.y() + 0.75, 0);
#ifdef AGENT_STRATEGY_OUTPUT
			cout << "goalieToBallDistance:" << goalieToBallDistance << endl;
#endif
		}
	}

	int teammateNumber;
		if (wm.WhetherMyTeammatesBlockMe(teammateNumber) == true)
		{
			Vector3 teammateCoordinate = wm.GetNewTeammateCoordinate(
					teammateNumber);
			float angle = wm.WhetherTeammateInMyWayToDestination(teammateCoordinate,
					my, destination);
#ifdef AGENT_STRATEGY_OUTPUT
			cout << "wm.WhetherMyTeammatesBlockMe()==true" << endl;
			cout<<"TeamBlockMeNumber::"<<teammateNumber<<endl;
			cout<<"angle::"<<angle<<endl;
			cout<<"(teammateCoordinate-wm.GetMyCoordinate()).xymod()::"<<(teammateCoordinate-wm.GetMyCoordinate()).xymod()<<endl;
#endif
			if (fabs(angle)<35&&(teammateCoordinate-wm.GetMyCoordinate()).xymod()<1)
			{
				destination=Vector3Linelength(teammateCoordinate,wm.GetMyCoordinate(),0.5*CELL_LENGTH);
#ifdef AGENT_STRATEGY_OUTPUT
				cout << "wm.WhetherMyTeammatesBlockMe()==true" << endl;
		//		destination = Vector3(destination.x() + 0.1, destination.y() + 0.1,
		//				destination.z());
				cout<<"change destination!!!!"<<endl;
#endif
				topSpeed = MIDMIN_SPEED;
			}
			///return basicMotion.InitStandUpPose();
		}
	else
	{
#ifdef AGENT_STRATEGY_OUTPUT
		cout << "wm.WhetherMyTeammatesBlockMe()==false" << endl;
#endif
		if(wm.whetherTeamatMyDes(destination))
		{
			Vector3 Goalcenter=Vector3(-wm.GetFieldLength()/2,0,0);
			float setdestoball=wm.GetMyDistanceToBall();
			if((Goalcenter-ball).xymod()<setdestoball)
			{
				setdestoball=(Goalcenter-ball).xymod()/2;
			}
			destination=Vector3Linelength(Goalcenter,ballCoordinate,setdestoball,false);
			cout<<"Goalcenter::"<<Goalcenter<<endl;
			cout<<"ballCoordinate::"<<ballCoordinate<<endl;
			cout<<"destination::"<<destination<<endl;
			cout<<"GetMyCoordinate::"<<wm.GetMyCoordinate()<<endl;
			///	destination=Vector3(destination.x()+1.8*CELL_LENGTH,destination.y(),destination.z());
			theNewWalkSolutions(destination, angleToTurn, topSpeed);
			angleToTurn = wm.GetMyBodyAngleToBall();
		}
	}
#ifdef AGENT_STRATEGY_OUTPUT
	cout << "LineBacker1:_________________" << endl;
	cout << "angleToTurn:" << angleToTurn << endl;
	cout << "destination:" << destination << endl;
	cout << "topSpeed:" << topSpeed << endl;
#endif
//destination=Vector3(-7,2,0);
//theNewWalkSolutions(destination,angleToTurn,topSpeed);
	return NEWWALK(destination, angleToTurn, topSpeed);
}


Action Strategy::ViceLinebacker_2_Strategy()
{
	stringstream ss("");

	BehaviorDecision();
	switch (decisionChoice)
	{
	case WALK_TO_MY_POSITION:
		ss << ViceLinebacker_2_Action();
#ifdef AGENT_STRATEGY_OUTPUT
		cout << "ViceLinebacker_2_WalkToPostion" << endl;
#endif
		break;
	case ALL_STOP_FOR_STAND_UP:
		ss << CITstandup.dealFallingDown();
		break;

	case PREVENT_FALLING_DOWN:
		ss << CITstandup.DisposeFalling();
		//cout<<"DisposeFalling!!!"<<endl;
		break;
	case SLIDE_TACKLE:
		ss << slideTackleToSaveBall();
		break;
	case STAND_UP:
		ss << CITstandup.StandUp(); //do get up motion
		break;
	case SHOOT_BALL:
#ifdef AGENT_STRATEGY_OUTPUT
		cout << "ViceLinebacker_2_ShootBall" << endl;
#endif
		ss << stopAndShootting();
		break;
	case DO_NOTHING:
		ss << basicMotion.StopAllMotion();
		break;
	default:
		ss << basicMotion.StopAllMotion();
	}
//	if(wm.GetTheMessageToSayAboutMyTeamMatePositon()!="000000000")
//	    ss<<mp.Say(wm.GetEncapsulatedWords(wm.GetTheMessageToSayAboutMyTeamMatePositon()));
	return ss.str();
}

Action Strategy::ViceLinebacker_2_Action()
{if(ballCoordinate.x()<myCoordinate.x()&&myCoordinate.x()>-5*CELL_LENGTH
)
{
if (/*(wm.GetMyDistanceToDestination(destination) < 0.5 * CELL_LENGTH
			&& fabs(wm.GetMyBodyAngleToXAxis()) < 60) ||*/
			(wm.GetClosestToBallOpponentDistanceByVision()<0.8 &&wm.GetClosestToBallTeammateDistanceByVision()<0.6
														&&wm.GetMyDistanceToBall()<0.8*CELL_LENGTH
														//&&wm.GetMyDistanceToBall()< CELL_LENGTH
														)||(wm.GetClosestToBallOpponentDistanceByVision()>0.8*CELL_LENGTH && wm.GetClosestToBallTeammateDistanceByVision()<0.55
																&&	wm.GetMyDistanceToBall()<0.8*CELL_LENGTH))
	{
		//return StopWhereAt();
	 angleToTurn = localMyBodyAngleToBall;
								                                   topSpeed =NULL_SPEED;
	//	topSpeed==AVOID_SPEED;
								                                    destination = ballCoordinate;
								                                    return NEWWALK(destination, angleToTurn, topSpeed);

	}
{destination = ballCoordinate;
//angleToTurn = localMyBodyAngleToBall;
angleToTurn = localMyBodyAngleToBall;

		///	angleToTurn=wm.GetMyAngleToDestination(destination);
		if (fabs(angleToTurn) < 70)
		{
			angleToTurn = localMyBodyAngleToBall;
		}
		else
		{
			//angleToTurn = -localMyBodyAngleToXAxis;
			angleToTurn = localMyBodyAngleToBall;
		}
topSpeed = MAX_SPEED;
return NEWWALK(destination, angleToTurn, topSpeed);
}
}
	int mDisToBallIndex;
	wm.GetMyDistanceToBallSortedIndexOld(mDisToBallIndex);
//	cout
//			<< "wm.GetMyDistanceToTeammate(wm.GetTheMinDistanceToBallTeammateNum()):"
//			<< wm.GetMyDistanceToTeammate(
//					wm.GetTheMinDistanceToBallTeammateNum()) << endl;
	Vector3 destinationCoordinate;
///	Vector3 ballCoordinate=wm.GetLastCyclesAverageBallCoordinate();
///	Vector3 myCoordinate=wm.GetMyCoordinate();	
#ifdef AGENT_STRATEGY_OUTPUT
	cout << "wm.GetTheMinDistanceToBallTeammateNum():"

			<< wm.GetTheMinDistanceToBallTeammateNum() << endl;
#endif
	if (wm.MyDistanceToBallSmallerThanMyDistanceToAnyTeammate() == true
			&& ballCoordinate.x() < -1 * CELL_LENGTH)
		//	&&wm.GetMyDistanceToBall() < CELL_LENGTH)
	{
#ifdef AGENT_STRATEGY_OUTPUT
		cout << "LinebackerAction111111111111111:" << endl;
#endif
		if (wm.CanSeeTheBall() && wm.CanDoLocalizationDirectly())
		{
			turnHeadStrategy(fallDownTurnHead);

			/*float ballMeToXAxisAngle =
			 wm.GetLastCyclesAverageBallMeToXAxisAngle();
			 float ballGoalToXAxisAngle =
			 wm.GetLastCyclesAverageBallGoalToXAxisAngle();*/

			destinationCoordinate = wm.GetLastCyclesAverageBallCoordinate();

			if (wm.GetMyDistanceToDestination(destination) > 2) ///need do some impove
			{
				destination = WalkToDestinationCoordinate(
						destinationCoordinate);
				angleToTurn = wm.GetMyBodyAngleToBall();
			}
			else if (wm.GetMyDistanceToDestination(destination) >= 0.7
					&& wm.GetMyDistanceToDestination(destination) <= 2) ///need do some impove
			{
				destination = WalkToDestinationCoordinate(
						destinationCoordinate);
				angleToTurn = wm.GetMyBodyAngleToBall();
				if (fabs(angleToTurn) < 90)
				{
					angleToTurn = wm.GetMyBodyAngleToBall();
				}
				else
				{
					angleToTurn = 0;
				}
			}
			else if (wm.GetMyDistanceToDestination(destination) < 0.7)
			{

				if (fabs(wm.GetMyBodyAngleToBall()) < 45)
				{
#ifdef AGENT_STRATEGY_OUTPUT
					cout << "fabs(wm.GetMyBodyAngleToBall() )<45 " << endl;
#endif
					angleToTurn = wm.GetMyBodyAngleToBall();
#ifdef AGENT_STRATEGY_OUTPUT
					cout << "AAAAA11111111111111wm.GetMyBodyAngleToXAxis():    "
							<< wm.GetMyBodyAngleToXAxis() << endl;
					cout
							<< "AAAAA22222222222wm.GetLastCyclesAverageBallGoalToXAxisAngle(): "
							<< wm.GetLastCyclesAverageBallGoalToXAxisAngle()
							<< endl;
					cout << "AAAAA33333333angleToTurn:  " << angleToTurn
							<< endl;
#endif
					if (wm.WhetherCanAttackOppGoal2() == false)
					{

						//	angleToTurn=0;
						destination = WalkToDestinationCoordinate(
								destinationCoordinate);
#ifdef AGENT_STRATEGY_OUTPUT
						cout << "AAAAAA33333333333333333333333333333333"
								<< endl;
#endif

					}
					else ///if(wm.WhetherCanAttackOppGoal2()==true)         ///can not use,otherwish,it will execute two times
					{
						//	angleToTurn=wm.GetLastCyclesAverageBallGoalToXAxisAngle()-wm.GetMyBodyAngleToXAxis();
						destination = wm.GetLastCyclesAverageBallCoordinate();

						topSpeed = MAX_SPEED;

						if (fabs(angleToTurn) > 20)
						{
							topSpeed = MIN_SPEED;
						}
#ifdef AGENT_STRATEGY_OUTPUT
						cout << "AAAAAA44444444444444444444444444444444444"
								<< endl;
#endif
					}

				}
				else
				{
					angleToTurn = wm.GetLastCyclesAverageBallGoalToXAxisAngle()
							- wm.GetMyBodyAngleToXAxis();
#ifdef AGENT_STRATEGY_OUTPUT
					cout
							<< "BBBBBBB11111111111111wm.GetMyBodyAngleToXAxis():    "
							<< wm.GetMyBodyAngleToXAxis() << endl;
					cout
							<< "BBBBBB22222222222wm.GetLastCyclesAverageBallGoalToXAxisAngle(): "
							<< wm.GetLastCyclesAverageBallGoalToXAxisAngle()
							<< endl;
					cout << "BBBBBB33333333angleToTurn:  " << angleToTurn
							<< endl;
#endif
					if (wm.WhetherCanAttackOppGoal2() == false)
					{

						//	angleToTurn=0;
						destination = WalkToDestinationCoordinate(
								destinationCoordinate);
#ifdef AGENT_STRATEGY_OUTPUT
						cout << "BBBBBB33333333333333333333333333333333"
								<< endl;
#endif

					}
					else ///if(wm.WhetherCanAttackOppGoal2()==true)         ///can not use,otherwish,it will execute two times
					{
						//	angleToTurn=wm.GetLastCyclesAverageBallGoalToXAxisAngle()-wm.GetMyBodyAngleToXAxis();
						destination = wm.GetLastCyclesAverageBallCoordinate();

						topSpeed = MAX_SPEED;
#ifdef AGENT_STRATEGY_OUTPUT
						cout << "BBBBBB44444444444444444444444444444444444"
								<< endl;
#endif
					}

				}
			}

			if (wm.GetMyDistanceToBall() < 0.8
					&& fabs(wm.GetMyBodyAngleToBall()) < 25 && ballCoordinate.x() <-4.5*CELL_LENGTH)
			{
				PassDirection passDirection;
				if (initPass == false)
				{
					newWalk.initPass(); ///should be init before pass ball
					initPass = true;
				}
				cout
						<< "777777777777777777777777777777777777777777PassDirection passDirection=PASS_FRONT;"
						<< endl;

				passDirection = estimatePassDirection();

				return newWalk.PassBall(passDirection);
			}
			else
			{
				initPass = false;
				return NEWWALK(destination, angleToTurn, topSpeed);
			}

			if (ballCoordinate.x() < 3 && fabs(myCoordinate.y()) < 3
					&& (ballCoordinate.x() > myCoordinate.x()))
			{
				destination = wm.GetLastCyclesAverageBallCoordinate();
				angleToTurn = wm.GetMyBodyAngleToBall();
				topSpeed = MAX_SPEED;
			}

		}
		else if (!wm.CanSeeTheBall() && wm.CanDoLocalizationDirectly())
		{
			turnHeadStrategy(fallDownTurnHead);

			angleToTurn = -wm.GetMyBodyAngleToXAxis();
			//	angleToTurn=0;
			//	angleToTurn=wm.GetLastCyclesAverageBallGoalToXAxisAngle()-wm.GetMyBodyAngleToXAxis();
			///		destination=wm.GetMyCoordinate();
			//	destination=Vector3(myCoordinate.x()+0.01,myCoordinate.y()+0.01,0);

			destination = WalkToDestinationCoordinate(
					wm.GetLastCyclesAverageBallCoordinate());
			///	destination=WalkToDestinationCoordinate(Vector3(9,0,0));
			///	topSpeed=MIN_SPEED;

		}
		else if (wm.CanSeeTheBall() && !wm.CanDoLocalizationDirectly())
		{
			turnHeadStrategy(fallDownTurnHead);

			angleToTurn = -wm.GetMyBodyAngleToXAxis();
			//	angleToTurn=0;
			//	angleToTurn=wm.GetLastCyclesAverageBallGoalToXAxisAngle()-wm.GetMyBodyAngleToXAxis();
			///		destination=wm.GetMyCoordinate();
			//	destination=Vector3(myCoordinate.x()+0.01,myCoordinate.y()+0.01,0);

			destination = WalkToDestinationCoordinate(
					wm.GetLastCyclesAverageBallCoordinate());
			///	destination=WalkToDestinationCoordinate(Vector3(9,0,0));
			///	topSpeed=MIN_SPEED;

		}
		else if (!wm.CanSeeTheBall() && !wm.CanDoLocalizationDirectly())
		{
			turnHeadStrategy(fallDownTurnHead);

			angleToTurn = -wm.GetMyBodyAngleToXAxis();
			//	angleToTurn=0;
			//	angleToTurn=wm.GetLastCyclesAverageBallGoalToXAxisAngle()-wm.GetMyBodyAngleToXAxis();
			///		destination=wm.GetMyCoordinate();
			//	destination=Vector3(myCoordinate.x()+0.01,myCoordinate.y()+0.01,0);

			destination = WalkToDestinationCoordinate(
					wm.GetLastCyclesAverageBallCoordinate());
			///	destination=WalkToDestinationCoordinate(Vector3(9,0,0));
			///	topSpeed=MIN_SPEED;
		}

//		return NEWWALK(destination,angleToTurn,topSpeed);
	}
	else
	{
#ifdef AGENT_STRATEGY_OUTPUT
		cout << "LinebackerAction22222222:" << endl;
#endif
		///	if(wm.GetMyDistanceToBall()<wm.GetMyDistanceToTeammate(wm.GetVanguardNumber()))
		{

		}
		///	else
		{

			///	destination=Vector3(  -0.8*wm.GetFieldLength()/2,1  ,0 );

//			destination = Vector3((ball.x() - wm.GetFieldLength() / 2) * 0.4,
//					ball.y() * 0.9, 0);
			Vector3 Goalcenter=Vector3(-wm.GetFieldLength()/2,0,0);
			float setdestoball=wm.GetMyDistanceToBall();
			if((Goalcenter-ball).xymod()<setdestoball)
			{
				setdestoball=(Goalcenter-ball).xymod()/2;
			}
			destination=Vector3Linelength(Goalcenter,ballCoordinate,setdestoball,false);
			cout<<"Goalcenter::"<<Goalcenter<<endl;
			cout<<"ballCoordinate::"<<ballCoordinate<<endl;
			cout<<"destination::"<<destination<<endl;
			cout<<"GetMyCoordinate::"<<wm.GetMyCoordinate()<<endl;
			///	destination=Vector3(destination.x()+1.8*CELL_LENGTH,destination.y(),destination.z());
			theNewWalkSolutions(destination, angleToTurn, topSpeed);
			angleToTurn = wm.GetMyBodyAngleToBall();

		}
//		return NEWWALK(destination,angleToTurn,topSpeed);
	}

	float goalieToBallDistance;
	if (wm.GetGoalieToBallDistance(goalieToBallDistance) == true)
	{
		if (goalieToBallDistance < 1)
		{
			angleToTurn = -wm.GetMyBodyAngleToXAxis();
			destination = Vector3(ballCoordinate.x() + 1.5,
					ballCoordinate.y() + 0.75, 0);
#ifdef AGENT_STRATEGY_OUTPUT
			cout << "goalieToBallDistance:" << goalieToBallDistance << endl;
#endif
		}
	}
	int TeamBlockMeNumber;
	if (wm.WhetherMyTeammatesBlockMe(TeamBlockMeNumber) == true)
	{
#ifdef AGENT_STRATEGY_OUTPUT
		cout << "wm.WhetherMyTeammatesBlockMe()==true" << endl;
		cout<<"TeamBlockMeNumber::"<<TeamBlockMeNumber<<endl;
#endif
		Vector3 teamCoord=wm.GetNewTeammateCoordinate(TeamBlockMeNumber);
		destination=Vector3Linelength(teamCoord,wm.GetMyCoordinate(),0.5*CELL_LENGTH);

//		destination = Vector3(destination.x() + 0.1, destination.y() + 0.1,
//				destination.z());
#ifdef AGENT_STRATEGY_OUTPUT
		cout<<"change destination!!!!"<<endl;
#endif
		topSpeed = MIDMIN_SPEED;
	}
	else
	{
#ifdef AGENT_STRATEGY_OUTPUT
		cout << "wm.WhetherMyTeammatesBlockMe()==false" << endl;
#endif
		if(wm.whetherTeamatMyDes(destination))
		{
			Vector3 Goalcenter=Vector3(-wm.GetFieldLength()/2,0,0);
			float setdestoball=wm.GetMyDistanceToBall();
			if((Goalcenter-ball).xymod()<setdestoball)
			{
				setdestoball=(Goalcenter-ball).xymod()/2;
			}
			destination=Vector3Linelength(Goalcenter,ballCoordinate,setdestoball,false);
#ifdef AGENT_STRATEGY_OUTPUT
			cout<<"Goalcenter::"<<Goalcenter<<endl;
			cout<<"ballCoordinate::"<<ballCoordinate<<endl;
			cout<<"destination::"<<destination<<endl;
			cout<<"GetMyCoordinate::"<<wm.GetMyCoordinate()<<endl;
#endif
			///	destination=Vector3(destination.x()+1.8*CELL_LENGTH,destination.y(),destination.z());
			theNewWalkSolutions(destination, angleToTurn, topSpeed);
			angleToTurn = wm.GetMyBodyAngleToBall();
		}
	}
#ifdef AGENT_STRATEGY_OUTPUT
	cout << "LineBacker2:_________________" << endl;
	cout << "angleToTurn:" << angleToTurn << endl;
	cout << "destination:" << destination << endl;
	cout << "topSpeed:" << topSpeed << endl;
#endif
//destination=Vector3(-7,2,0);
//theNewWalkSolutions(destination,angleToTurn,topSpeed);
	return NEWWALK(destination, angleToTurn, topSpeed);
}

Action Strategy::GoalieStrategy()
{
	stringstream ss("");
	BehaviorDecision();
#ifdef AGENT_STRATEGY_OUTPUT
	cout << "       GoaliaStrategy :       " << wm.GetMyNumber() << endl;
#endif
	switch (decisionChoice)
	{
	case WALK_TO_MY_POSITION:
		ss << GoalieAction();
		///	ss<<standUpWithTurnHead();
		break;

	case PREVENT_FALLING_DOWN:
		ss << CITstandup.DisposeFalling();
		//cout<<"DisposeFalling!!!"<<endl;
		break;

	case STAND_UP:
		ss << CITstandup.StandUp(); //do get up motion
		break;
	case ALL_STOP_FOR_STAND_UP:
		///	ss<<readData.AllStop();
		ss << CITstandup.dealFallingDown();
		break;
	case SHOOT_BALL:
#ifdef AGENT_STRATEGY_OUTPUT
		cout << "Goalie_ShootBall" << endl;
#endif
		ss << stopAndShootting();
		break;
	case DO_NOTHING:
		ss << basicMotion.StopAllMotion();
		break;
	default:
		ss << basicMotion.StopAllMotion();
	}
///	if(wm.GetTheMessageToSayAboutMyTeamMatePositon()!="000000000")
///	    ss<<mp.Say(wm.GetEncapsulatedWords(wm.GetTheMessageToSayAboutMyTeamMatePositon()));

	/*
	 if(messageParser.GetWhetherBallBeforeVanguard()==true)
	 {
	 sayMsg+="B";
	 }
	 else
	 {
	 sayMsg+="A";
	 }*/

// if(wm.GetTheMessageToSayAboutMyTeamMatePositon()!="000000000")
// 	    ss<<mp.Say(wm.GetEncapsulatedWords(sayMsg+wm.GetTheMessageToSayAboutMyTeamMatePositon()));
// 	else
// 	  ss<<mp.Say(wm.GetEncapsulatedWords(sayMsg));
	return ss.str();
}

Action Strategy::HandleBall()
{

	int teammateNumber;
		if (wm.WhetherMyTeammatesBlockMe(teammateNumber) == true)
		{
			Vector3 teammateCoordinate = wm.GetNewTeammateCoordinate(
					teammateNumber);
			float angle = wm.WhetherTeammateInMyWayToDestination(teammateCoordinate,
					my, destination);
	#ifdef AGENT_STRATEGY_OUTPUT
			cout<<"teammateNumber::"<<teammateNumber<<endl;
			cout<<"angle::"<<angle<<endl;
			cout<<"(teammateCoordinate-wm.GetMyCoordinate()).xymod()::"<<(teammateCoordinate-wm.GetMyCoordinate()).xymod()<<endl;
	#endif
			if (angle<25&&((teammateCoordinate-wm.GetMyCoordinate()).xymod()<0.3)&&wm.GetMyDistanceToBall()<0.8)
			{

				if((ball.x()>teammateCoordinate.x()&&teammateCoordinate.x()>my.x())
										||	(ball.x()<teammateCoordinate.x()&&teammateCoordinate.x()<my.x())
										||(ball.x()<my.x()&&teammateCoordinate.x()<ball.x()))
									{
									angleToTurn = localMyBodyAngleToBall;
													                                  topSpeed =NULL_SPEED;
							//		topSpeed==AVOID_SPEED;
													                                    destination = ballCoordinate;
													                                    return NEWWALK(destination, angleToTurn, topSpeed);}
			}
			///return basicMotion.InitStandUpPose();

		}
// 	if(wm.GetCurrentGameTime()>3)
// 	{
// 	    if(newWalk.WhichFootRaised()==-1&&newWalk.GetWalkCounter()==4)
// 	    {
// 		  slidedToSaveBall=true;
// 		  slidedDirection=Left;
// 		  return slideTackleToSaveBall();
// 	    }
// 	}
#ifdef AGENT_STRATEGY_OUTPUT
	cout << "GetLastCyclesAverageBodyToXAngle:"
			<< wm.GetLastCyclesAverageBodyToXAngle() << endl;
	cout << "wm.GetMyBodyAngleToXAxis():" << wm.GetMyBodyAngleToXAxis() << endl;

	third(0, 0, 0, 1);
	if (messageParser.GetWhetherPositionAStand() == false)
	{
		cout << "messageParser.GetWhetherPositionAStand()==false" << endl;
	}
	else
	{
		cout << "messageParser.GetWhetherPositionAStand()==true" << endl;
	}
	if (messageParser.GetWhetherPositionBStand() == false)
	{
		cout << "messageParser.GetWhetherPositionBStand()==false" << endl;
	}
	else
	{
		cout << "messageParser.GetWhetherPositionBStand()==true" << endl;
	}
	if (messageParser.GetWhetherPositionCStand() == false)
	{
		cout << "messageParser.GetWhetherPositionCStand()==false" << endl;
	}
	else
	{
		cout << "messageParser.GetWhetherPositionCStand()==true" << endl;
	}
	if (messageParser.GetWhetherPositionDStand() == false)
	{
		cout << "messageParser.GetWhetherPositionDStand()==false" << endl;
	}
	else
	{
		cout << "messageParser.GetWhetherPositionDStand()==true" << endl;
	}

	cout << "messageParser.GetPositionANumberByHear():"
			<< messageParser.GetPositionANumberByHear() << endl;
	cout << "messageParser.GetPositionBNumberByHear():"
			<< messageParser.GetPositionBNumberByHear() << endl;
	cout << "messageParser.GetPositionCNumberByHear():"
			<< messageParser.GetPositionCNumberByHear() << endl;
	cout << "messageParser.GetPositionDNumberByHear():"
			<< messageParser.GetPositionDNumberByHear() << endl;

	cout << "Action SoccerbotBehaviorHandleBall" << endl;

	cout << "localBallCoordinateForRunFormation:"
			<< localBallCoordinateForRunFormation << endl;
#endif
	Vector3 destinationCoordinate;
#ifdef AGENT_STRATEGY_OUTPUT
	cout << "wm.GetClosestToMeOpponentDistanceByVision():"
			<< wm.GetClosestToMeOpponentDistanceByVision() << endl;
	cout << "wm.GetClosestToMeOpponentNumberByVision():"
			<< wm.GetClosestToMeOpponentNumberByVision() << endl;
	cout
			<< "wm.GetOpponentCoordinate["
			<< wm.GetClosestToMeOpponentNumberByVision()
			<< "]:"
			<< wm.GetOpponentCoordinate(
					wm.GetClosestToMeOpponentNumberByVision()) << endl;

	cout << "wm.GetCurrentJointAngle(JID_HEAD_1)"
			<< wm.GetCurrentJointAngle(JID_HEAD_1) << " newk.HedAng():   "
			<< newWalk.GetLastCyclesAverageTurnHeadAngle() << endl;
#endif
	/*
	 if(WhetherUseHalfStepWalk())
	 {
	 if(oneStyleWalkTime>=KEEP_ONE_STYLE_WALK)
	 {
	 useHalfStepWalk=true;
	 if(newWalk.UseNewWalk)
	 {
	 oneStyleWalkTime=0;
	 }
	 }

	 }
	 else
	 {
	 if(oneStyleWalkTime>=KEEP_ONE_STYLE_WALK)
	 {
	 useHalfStepWalk=false;
	 if(newWalk.UseNewWalk==false)
	 {
	 oneStyleWalkTime=0;
	 }
	 }
	 if(!wm.CanSeeTheBall()||fabs(wm.GetMyBodyAngleToBall())>40)
	 {
	 useHalfStepWalk=false;
	 oneStyleWalkTime=0;
	 }
	 }

	 if(oneStyleWalkTime<=KEEP_ONE_STYLE_WALK+1)
	 {
	 oneStyleWalkTime++;
	 }
	 */
//if(useHalfStepWalk==true)
	{
//	return HalfStepWalk();
	}
///else

	{
		float dis = wm.getDistanceOppenentToBall(
				wm.GetClosestToBallOpponentNumberByVision());
		if (wm.CanSeeTheBall() && (ballCoordinate.x() > myCoordinate.x())
				&& wm.GetMyDistanceToBall() > 0.38
				&& wm.GetMyDistanceToBall() < 0.75
				&& wm.GetMyBodyAngleToBall() > 37
				&& wm.GetMyBodyAngleToBall() < 100 && dis > 0 && dis < 0.35 && ball.x()<-7 && 	(wm.GetMyOpponentTeamName()!="CIT3D"))
		{
			if (newWalk.WhichFootRaised() == -1
					&& newWalk.GetWalkCounter() == 4)
			{
				slidedToSaveBall = true;
				slidedDirection = Left;
				return slideTackleToSaveBall();
			}
		}
		else if (wm.CanSeeTheBall() && (ballCoordinate.x() > myCoordinate.x())
				&& wm.GetMyDistanceToBall() > 0.38
				&& wm.GetMyDistanceToBall() < 0.75
				&& wm.GetMyBodyAngleToBall() < -37
				&& wm.GetMyBodyAngleToBall() > -100 && dis > 0 && dis < 0.35 &&  ball.x()<-7 	&& (wm.GetMyOpponentTeamName()!="CIT3D"))
		{
			if (newWalk.WhichFootRaised() == 1 && newWalk.GetWalkCounter() == 4)
			{
				slidedToSaveBall = true;
				slidedDirection = Right;
				return slideTackleToSaveBall();
			}
		}
		else if (wm.CanSeeTheBall() && wm.CanDoLocalizationDirectly())
	//	if (wm.CanSeeTheBall() && wm.CanDoLocalizationDirectly())
		{

			turnHeadStrategy(fallDownTurnHead);
#ifdef A

			GENT_STRATEGY_OUTPUT
			cout << "3333333333333333333333333wm.GetMyBodyAngleToBall():"
					<< localMyBodyAngleToBall << endl;

			cout
					<< "66666666666666666666666666666wm.GetClosestToBallOpponentDistanceByVision():"
					<< wm.GetClosestToBallOpponentDistanceByVision() << endl;
			cout << "wm.GetClosestToBallTeammateDistanceByVision():"
					<< wm.GetClosestToBallTeammateDistanceByVision() << endl;

			cout << "---------------------   -MyBodyAngleToXAxis:    "
					<< -localMyBodyAngleToXAxis << endl;
			cout
					<< "GetBodyToX();                                                                              : "
					<< localBodyToX << endl;
			cout << "######################GetLastCyclesBodyToXAngle():"
					<< localLastCyclesAverageBodyToXAngle << endl;
			cout << "##########GetLastCyclesAverageBallMeToXAxisAngle():"
					<< localLastCyclesAverageBallMeToXAxisAngle << endl;
			cout << "++++++++++++MyHeadAngleToXAxis():  "
					<< localMyHeadAngleToXAxis << endl;

			cout << "=========================Vector3 myCoordinate          "
					<< myCoordinate << "     wm.GetMyCoordinate():     "
					<< wm.GetMyCoordinate() << endl;
			cout << "#########################Vector3 ballCoordinate          "
					<< ballCoordinate << "wm.GetBallCoordinate()"
					<< wm.GetBallCoordinate() << endl;
			cout << "&&&&&&&&&&&&&&&&&&&&&&&&&wm.GetMyDistanceToBall         "
					<< localMyDistanceToBall << endl;
#endif
			///	destinationCoordinate=wm.GetLastCyclesAverageBallCoordinate();
			///	destinationCoordinate=wm.GetTheBallStopCoordinate();
			///	destinationCoordinate=localTheBallStopCoordinate;
			destinationCoordinate = ball;

			TPlayMode localCurrentGameMode = wm.GetCurrentGameMode();

			if ((WhetherBallAndMeInTwoLineArea()
					|| ballCoordinate.x() < -4.0 * CELL_LENGTH)
					&& myCoordinate.x() < ballCoordinate.x()
					&& localCurrentGameMode == PM_PlayOn)
			{
				destination = HandleBallGoalongwithOneOfTwoLine(
						destinationCoordinate);
				//cout << "here is in line area" << destination << endl;
			} /// WhetherBallAndMeInTwoLineArea()==false
			else if (ballCoordinate.x() > 4.5 * CELL_LENGTH
					&& ballCoordinate.x() < 7.0 * CELL_LENGTH
					&& fabs(ballCoordinate.y()) < 4 * CELL_LENGTH
					&& localCurrentGameMode == PM_PlayOn&&wm.GetClosestToBallOpponentDistanceByVision()>0.4)
			{
				destination = HandleBallDestinationForShootBall(
						destinationCoordinate);
				//cout << "here is in right area " << destination << endl;
			}
			/*else if (ballCoordinate.x() > 7 * CELL_LENGTH
			 && fabs(ballCoordinate.y() > 3.5 * CELL_LENGTH)
			 &&myCoordinate.x()<ballCoordinate.x()-0.1
			 && localCurrentGameMode == PM_PlayOn)
			 {
			 destination = ballCoordinate;
			 //cout << "here is pass ball out of area!!!" << endl;
			 }*/
			else
			{
				destination = WalkToDestinationCoordinate(
						destinationCoordinate);
				//cout << "here is n_destination" << destination << endl;
			} ///changed by gaojin

			//destination = WalkToDestinationCoordinate(destinationCoordinate);
			if (wm.GetMyDistanceToDestination(destination) > 2) ///need do some impove
			{
//				cout
//						<< "Walk to destination Coordinate111111111111111111111111111!!!!"
//						<< endl;

				///	destination=WalkToDestinationCoordinate(destinationCoordinate);

				angleToTurn = localMyBodyAngleToBall;

				///	angleToTurn=wm.GetMyAngleToDestination(destination);

				if (fabs(angleToTurn) < 70)
				{
					angleToTurn = localMyBodyAngleToBall;
				}
				else
				{
					//angleToTurn = -localMyBodyAngleToXAxis;
					angleToTurn = localMyBodyAngleToBall;
				}

			}
			else if (wm.GetMyDistanceToDestination(destination) > 0.7
					&& wm.GetMyDistanceToDestination(destination) <= 2) ///need do some impove
			{
//				cout
//						<< "Walk to destination Coordinate2222222222222222211111111111111!!!!"
//						<< endl;

				///	destination=WalkToDestinationCoordinate(destinationCoordinate);
				angleToTurn = localMyBodyAngleToBall;

				///	angleToTurn=wm.GetMyAngleToDestination(destination);
				if (fabs(angleToTurn) < 70)
				{
					angleToTurn = localMyBodyAngleToBall;
				}
				else
				{
					angleToTurn = -localMyBodyAngleToXAxis;
				}

				//	angleToTurn=-wm.GetMyBodyAngleToXAxis();
			}
			else if (wm.GetMyDistanceToDestination(destination) <= 0.7)
			{
#ifdef AGENT_STRATEGY_OUTPUT
				cout << "2222222222222222222222222222222222222222222!!!"
						<< endl;
#endif
				if (fabs(localMyBodyAngleToBall) < 25)
				{
#ifdef AGENT_STRATEGY_OUTPUT
					cout << "fabs(wm.GetMyBodyAngleToBall() )<30 " << endl;
					angleToTurn = localMyBodyAngleToBall;

					cout << "AAAAA11111111111111wm.GetMyBodyAngleToXAxis():    "
							<< localMyBodyAngleToXAxis << endl;
					cout
							<< "AAAAA22222222222wm.GetLastCyclesAverageBallGoalToXAxisAngle(): "
							<< localLastCyclesAverageBallGoalToXAxisAngle
							<< endl;
					cout << "AAAAA33333333angleToTurn:  " << angleToTurn
							<< endl;
#endif
					if (localWhetherCanAttackOppGoal2 == false)
					{

						destination = WalkToDestinationCoordinate(
								destinationCoordinate);

#ifdef AGENT_STRATEGY_OUTPUT
						cout << "AAAAAA33333333333333333333333333333333"
								<< endl;
#endif

					}
					else ///if(wm.WhetherCanAttackOppGoal2()==true)         ///can not use,otherwish,it will execute two times
					{
						//	angleToTurn=wm.GetLastCyclesAverageBallGoalToXAxisAngle()-wm.GetMyBodyAngleToXAxis();
						///	destination=wm.GetLastCyclesAverageBallCoordinate();
						destination = ballCoordinate;
					//	topSpeed = MAX_SPEED;
						topSpeed = MIN_SPEED;

						if (fabs(angleToTurn) <20)//  >20
						{
						//	topSpeed = MIN_SPEED;
							topSpeed = MAX_SPEED;
						}
#ifdef AGENT_STRATEGY_OUTPUT
						cout << "AAAAAA44444444444444444444444444444444444"
								<< endl;
#endif
					}

				}
				else if (fabs(localMyBodyAngleToBall) >= 25)
				{
					//angleToTurn = localLastCyclesAverageBallGoalToXAxisAngle
						//	- localMyBodyAngleToXAxis;
					angleToTurn=localMyBodyAngleToBall;
#ifdef AGENT_STRATEGY_OUTPUT
					cout
							<< "BBBBBBB11111111111111wm.GetMyBodyAngleToXAxis():    "
							<< localMyBodyAngleToXAxis << endl;
					cout
							<< "BBBBBB22222222222wm.GetLastCyclesAverageBallGoalToXAxisAngle(): "
							<< localLastCyclesAverageBallGoalToXAxisAngle
							<< endl;
					cout << "BBBBBB33333333angleToTurn:  " << angleToTurn
							<< endl;
#endif
					if (localWhetherCanAttackOppGoal2 == false)
					{

						//	angleToTurn=0;
						destination = WalkToDestinationCoordinate(
								destinationCoordinate);
#ifdef AGENT_STRATEGY_OUTPUT
						cout << "BBBBBB33333333333333333333333333333333"
								<< endl;
#endif

					}
					else ///if(wm.WhetherCanAttackOppGoal2()==true)         ///can not use,otherwish,it will execute two times
					{
						//	angleToTurn=wm.GetLastCyclesAverageBallGoalToXAxisAngle()-wm.GetMyBodyAngleToXAxis();
						destination = ballCoordinate;

						topSpeed = MAX_SPEED;
#ifdef AGENT_STRATEGY_OUTPUT
						cout << "BBBBBB44444444444444444444444444444444444"
								<< endl;
#endif
					}

				}

			}

			if (localMyDistanceToBall < 1) ///&&wm.GetCurrentGameTime()<3)
			{
				//	topSpeed=MIDMIN_SPEED;
				if (localMyDistanceToBall < 0.8)
				{
					///	  topSpeed=MIN_SPEED;
					//	topSpeed=MID_SPEED;
				}
			}

			if (ball.x() > 7.5 * CELL_LENGTH)
			{
				///	topSpeed=MID_SPEED;
			}

//			cout
//					<< "9999999999999999999999999999999wm.GetLastCyclesAverageBallMeToXAxisAngle():"
//					<< wm.GetLastCyclesAverageBallMeToXAxisAngle() << endl;

#if 1
			/*
			 if(ballCoordinate.x()>=-4*CELL_LENGTH&&ballCoordinate.x()<3.5*CELL_LENGTH&&fabs(myCoordinate.y())<2.5*CELL_LENGTH&&(ballCoordinate.x()>myCoordinate.x() )&&messageParser.WhetherCanTurnToOpponentGoal()==false )
			 {
			 destination=ballCoordinate;
			 angleToTurn=localMyBodyAngleToBall;
			 topSpeed=MAX_SPEED;
			 cout<<"ballCoordinate.x()<4*CELL_LENGTH&&fabs(myCoordinate.y())<2.5*CELL_LENGTH&&(ballCoordinate.x()>myCoordinate.x() )"<<endl;
			 }
			 */
		//	if (myRole == ROLE_VANGUARD)
		/*	if(ballCoordinate.x()<myCoordinate.x())
			{destination = ballCoordinate;
			//angleToTurn = localMyBodyAngleToBall;
			angleToTurn = localMyBodyAngleToBall;

							///	angleToTurn=wm.GetMyAngleToDestination(destination);
							if (fabs(angleToTurn) < 70)
							{
								angleToTurn = localMyBodyAngleToBall;
							}
							else
							{
								angleToTurn = -localMyBodyAngleToXAxis;
							}
			topSpeed = MAX_SPEED;

			}*/
			/*if(ballCoordinate.x()<myCoordinate.x()+1.3 &&ballCoordinate.x()>myCoordinate.x()
					&&fabs(ballCoordinate.y())<fabs(myCoordinate.y())+1.3)
							{destination = ballCoordinate;
							//angleToTurn = localMyBodyAngleToBall;
							angleToTurn = localMyBodyAngleToBall;

											///	angleToTurn=wm.GetMyAngleToDestination(destination);
											if (fabs(angleToTurn) < 80)
											{
												//angleToTurn = localMyBodyAngleToBall;
												///angleToTurn =0;
												topSpeed =BACK_MAX_SPEED;
											}
											else if(fabs(angleToTurn) >110)
											{
												//angleToTurn = -localMyBodyAngleToXAxis;
												angleToTurn = localMyBodyAngleToBall;
												topSpeed =MAX_SPEED;
											//	angleToTurn =0;

											}


							}*/
if(ballCoordinate.x() < myCoordinate.x() && wm.GetClosestToBallOpponentDistanceByVision()<wm.GetMyDistanceToBall())
{
	topSpeed=MAX_SPEED;
}
if((ballCoordinate.x() >-2* CELL_LENGTH&&ballCoordinate.x() <=5* CELL_LENGTH &&fabs(localMyBodyAngleToBall) < 13
			   					&&wm.GetMyBodyAngleToXAxis()<80&&wm.GetMyBodyAngleToXAxis()>-80 &&//fabs(localMyBodyAngleToBall) > 5&&
			   					(ballCoordinate.x() > myCoordinate.x()  && wm.GetClosestToBallOpponentDistanceByVision()<wm.GetMyDistanceToBall()
			   					)&& fabs(ballCoordinate.y()) <=  3.5* CELL_LENGTH  )||
			   					(ballCoordinate.x() >-1* CELL_LENGTH&&ballCoordinate.x() <=5* CELL_LENGTH &&fabs(localMyBodyAngleToBall) < 13
			   								   					&&wm.GetMyBodyAngleToXAxis()<80&&wm.GetMyBodyAngleToXAxis()>80 &&
			   								   					(ballCoordinate.x() > myCoordinate.x()  && wm.GetClosestToBallOpponentDistanceByVision()<wm.GetMyDistanceToBall()
			   								   					)&& fabs(ballCoordinate.y()) <=  3.5* CELL_LENGTH  ))

			               {cout<<"LLLLLLLLL"<< myCoordinate.y();
			            	   destination = ballCoordinate;
			            	   			//			angleToTurn = localMyBodyAngleToBall;
			            	   angleToTurn = localMyBodyAngleToBall;

			            	   				///	angleToTurn=wm.GetMyAngleToDestination(destination);
			            	   				if (fabs(angleToTurn) < 70)
			            	   				{
			            	   					angleToTurn = localMyBodyAngleToBall;
			            	   				}
			            	   				else
			            	   				{
			            	   					//angleToTurn = -localMyBodyAngleToXAxis;
			            	   					angleToTurn = localMyBodyAngleToBall;
			            	   				}

			            	   						topSpeed = MAX_SPEED;
			               }




		//	if (whetherStriker == false)
			if (ballCoordinate.x()< 7 * CELL_LENGTH )//6.4
						{// cout<<"LLLLLLLLL"<< myCoordinate.y();
			               if ((5*CELL_LENGTH<ballCoordinate.x()&& ballCoordinate.x()< 7 * CELL_LENGTH&& fabs(localMyBodyAngleToBall) < 13//&&fabs(localMyBodyAngleToBall) > 5
								&&wm.GetMyBodyAngleToXAxis()<35&&wm.GetMyBodyAngleToXAxis()>-35 &&wm.GetMyDistanceToDestination(destination) <= 0.7&&
								(ballCoordinate.x() > myCoordinate.x())&&wm.GetClosestToBallOpponentDistanceByVision()>1*CELL_LENGTH
								&& fabs(ballCoordinate.y()) < 3 * CELL_LENGTH  ) ||
								(5*CELL_LENGTH<ballCoordinate.x()&& ballCoordinate.x()< 7 * CELL_LENGTH&& fabs(localMyBodyAngleToBall) < 14&&localClosestToBallOpponentDistanceByVision<1*CELL_LENGTH
																&&wm.GetMyBodyAngleToXAxis()<35&&wm.GetMyBodyAngleToXAxis()>-35 &&wm.GetMyDistanceToDestination(destination) <= 0.7&&
																(ballCoordinate.x() > myCoordinate.x())//&&wm.GetClosestToBallOpponentDistanceByVision()<=2*CELL_LENGTH
																&& fabs(ballCoordinate.y()) < 3 * CELL_LENGTH  ))
								{
									destination = ballCoordinate;
									//angleToTurn = localMyBodyAngleToBall;
									angleToTurn = localMyBodyAngleToBall;

													///	angleToTurn=wm.GetMyAngleToDestination(destination);
													if (fabs(angleToTurn) < 70)
													{
														angleToTurn = localMyBodyAngleToBall;
													}
													else
													{
														angleToTurn = -localMyBodyAngleToXAxis;
													}
									topSpeed = MAX_SPEED;
//									cout<<"ooooooooooooooo"<<endl;
//									cout<<"ooooooooooooooo"<<endl;
//									cout<<"ooooooooooooooo"<<endl;
//									cout<<"ooooooooooooooo"<<endl;
								}
			               else if((ballCoordinate.x() >-4* CELL_LENGTH&&ballCoordinate.x() <=5* CELL_LENGTH &&fabs(localMyBodyAngleToBall) < 13
			   					&&wm.GetMyBodyAngleToXAxis()<42&&wm.GetMyBodyAngleToXAxis()>-42 &&//fabs(localMyBodyAngleToBall) > 5&&
			   					(ballCoordinate.x() > myCoordinate.x()  && wm.GetClosestToBallOpponentDistanceByVision()>0.7*CELL_LENGTH
			   					)&& fabs(ballCoordinate.y()) <=  3.5* CELL_LENGTH  )||
			   					(ballCoordinate.x() >-1* CELL_LENGTH&&ballCoordinate.x() <=5* CELL_LENGTH &&fabs(localMyBodyAngleToBall) < 13
			   								   					&&wm.GetMyBodyAngleToXAxis()<40&&wm.GetMyBodyAngleToXAxis()>-40 &&
			   								   					(ballCoordinate.x() > myCoordinate.x()  && wm.GetClosestToBallOpponentDistanceByVision()<=0.7*CELL_LENGTH
			   								   					)&& fabs(ballCoordinate.y()) <=  3.5* CELL_LENGTH  ))
		         //      {cout<<"LLLLLLLLL"<< myCoordinate.y();
			            	   destination = ballCoordinate;
			            	   			//			angleToTurn = localMyBodyAngleToBall;
			            	   angleToTurn = localMyBodyAngleToBall;

			            	   				///	angleToTurn=wm.GetMyAngleToDestination(destination);
			            	   				if (fabs(angleToTurn) < 70)
			            	   				{
			            	   					angleToTurn = localMyBodyAngleToBall;
			            	   				}
			            	   				else
			            	   				{
			            	   					angleToTurn = -localMyBodyAngleToXAxis;
			            	   				}
			            	   						topSpeed = MAX_SPEED;
			               }
			               else    if(((3.5*CELL_LENGTH<ballCoordinate.y()&&ballCoordinate.y()<5.2* CELL_LENGTH&&fabs(localMyBodyAngleToBall)<14
			            		   &&wm.GetMyBodyAngleToXAxis()<20  &&wm.GetMyBodyAngleToXAxis()>-35&&ballCoordinate.x() > myCoordinate.x()
			            		   &&wm.GetClosestToBallOpponentDistanceByVision()<=2*CELL_LENGTH)//&&fabs(localMyBodyAngleToBall) > 5)
			            		      ||  (( ballCoordinate.y()<-3.5* CELL_LENGTH&& ballCoordinate.y()>-5.2* CELL_LENGTH && fabs(localMyBodyAngleToBall) < 14&&fabs(localMyBodyAngleToBall) > 5
			            		      &&wm.GetMyBodyAngleToXAxis()<-20&&wm.GetMyBodyAngleToXAxis()<35 &&ballCoordinate.x() > myCoordinate.x() )
			            		      &&wm.GetClosestToBallOpponentDistanceByVision()<=2*CELL_LENGTH))
			            		      ||
			            		      ((3.5*CELL_LENGTH<ballCoordinate.y()&&ballCoordinate.y()<5.2* CELL_LENGTH&&fabs(localMyBodyAngleToBall)<15
			            		      			            		   &&wm.GetMyBodyAngleToXAxis()<20  &&wm.GetMyBodyAngleToXAxis()>-35&&ballCoordinate.x() > myCoordinate.x()
			            		      			            		   &&wm.GetClosestToBallOpponentDistanceByVision()<=0.5*CELL_LENGTH)
			            		      			            		      ||  (( ballCoordinate.y()<-3.5* CELL_LENGTH&& ballCoordinate.y()>-5.2* CELL_LENGTH && fabs(localMyBodyAngleToBall) < 15
			            		      			            		      &&wm.GetMyBodyAngleToXAxis()<-20&&wm.GetMyBodyAngleToXAxis()<35 &&ballCoordinate.x() > myCoordinate.x() )
			            		      			            		      &&wm.GetClosestToBallOpponentDistanceByVision()<=0.5*CELL_LENGTH)))

			               {
			            	  destination = ballCoordinate;
			           //    destination = Vector3(ballCoordinate.x() ,
			            	  	//		            	   								ballCoordinate.y(), destination.z());
			            	               	   					//	angleToTurn = localMyBodyAngleToBall;
			            	  angleToTurn = localMyBodyAngleToBall;

			            	  				///	angleToTurn=wm.GetMyAngleToDestination(destination);
			            	  				if (fabs(angleToTurn) < 70)
			            	  				{
			            	  					angleToTurn = localMyBodyAngleToBall;
			            	  				}
			            	  				else
			            	  				{
			            	  					angleToTurn = -localMyBodyAngleToXAxis;
			            	  				}
			            	               	   						topSpeed = MAX_SPEED;
			               }
			              if((5.2*CELL_LENGTH<ballCoordinate.y()&&ballCoordinate.y()<=(6* CELL_LENGTH)&&fabs(localMyBodyAngleToBall)<15
			                         		   &&wm.GetMyBodyAngleToXAxis()<=0  &&wm.GetMyBodyAngleToXAxis()>=-45//&&ballCoordinate.x() > myCoordinate.x()
			                         		   &&wm.GetClosestToBallOpponentDistanceByVision()<=2*CELL_LENGTH)//&&fabs(localMyBodyAngleToBall) > 5)
			                         		      ||  ( ballCoordinate.y()<-3.5* CELL_LENGTH&& ballCoordinate.y()>-5.2* CELL_LENGTH && fabs(localMyBodyAngleToBall) < 15
			                         		      &&wm.GetMyBodyAngleToXAxis()<-20&&wm.GetMyBodyAngleToXAxis()<45 &&ballCoordinate.x() > myCoordinate.x()
			                         		      &&wm.GetClosestToBallOpponentDistanceByVision()<=2*CELL_LENGTH)//&&fabs(localMyBodyAngleToBall) > 5)
			                         		      ||
			                         		     (-5.2*CELL_LENGTH>ballCoordinate.y()&&ballCoordinate.y()>=(-7* CELL_LENGTH)&&fabs(localMyBodyAngleToBall)<15
			                         		     			                         		   &&wm.GetMyBodyAngleToXAxis()>=0  &&wm.GetMyBodyAngleToXAxis()<=60//&&ballCoordinate.x() > myCoordinate.x()
			                         		     			                         		   &&wm.GetClosestToBallOpponentDistanceByVision()<=2*CELL_LENGTH&&fabs(localMyBodyAngleToBall) > 0)
			                         		     			                         		   )

			                            {
			                         	  destination = ballCoordinate;
			                        //    destination = Vector3(ballCoordinate.x() ,
			                         	  	//		            	   								ballCoordinate.y(), destination.z());
			                         	               	   					//	angleToTurn = localMyBodyAngleToBall;
			                         	  angleToTurn = localMyBodyAngleToBall;

			                         	  				///	angleToTurn=wm.GetMyAngleToDestination(destination);
			                         	  				if (fabs(angleToTurn) < 70)
			                         	  				{
			                         	  					angleToTurn = localMyBodyAngleToBall;
			                         	  				}
			                         	  				else
			                         	  				{
			                         	  					angleToTurn = -localMyBodyAngleToXAxis;
			                         	  				}
			                         	               	   						topSpeed = MAX_SPEED;
			                            }

						}
			if (
														(wm.GetClosestToBallOpponentDistanceByVision()<0.8 &&wm.GetClosestToBallTeammateDistanceByVision()<0.5
														&&wm.GetMyDistanceToBall()<0.8&&wm.IsVanguardFallDown()
														//&&wm.GetMyDistanceToBall()< CELL_LENGTH
														)||(wm.GetClosestToBallOpponentDistanceByVision()>0.8*CELL_LENGTH&&wm.GetClosestToBallTeammateDistanceByVision()<0.6
																&&	wm.GetMyDistanceToBall()<0.8*CELL_LENGTH))
												{
													//return StopWhereAt();
				                                   angleToTurn = localMyBodyAngleToBall;
				                                    topSpeed =NULL_SPEED;
				                       //        	topSpeed==AVOID_SPEED;
				                                    destination = ballCoordinate;

				                               //     wm.IsVanguardFallDown()

												}
			if (ballCoordinate.x()< 6 * CELL_LENGTH &&ballCoordinate.x()>4.5* CELL_LENGTH){
				if(((2*CELL_LENGTH<ballCoordinate.y()&&ballCoordinate.y()<5.2* CELL_LENGTH&&fabs(localMyBodyAngleToBall)<14
							            		   &&wm.GetMyBodyAngleToXAxis()<20  &&wm.GetMyBodyAngleToXAxis()>-65&&ballCoordinate.x() > myCoordinate.x()
							            		   &&wm.GetClosestToBallOpponentDistanceByVision()<=2*CELL_LENGTH)//&&fabs(localMyBodyAngleToBall) > 5)
							            		      ||  (( ballCoordinate.y()<-2* CELL_LENGTH&& ballCoordinate.y()>-5.2* CELL_LENGTH && fabs(localMyBodyAngleToBall) < 14//&&fabs(localMyBodyAngleToBall) > 5
							            		      &&wm.GetMyBodyAngleToXAxis()>-20&&wm.GetMyBodyAngleToXAxis()<65 &&ballCoordinate.x() > myCoordinate.x() )
							            		      &&wm.GetClosestToBallOpponentDistanceByVision()<=2*CELL_LENGTH))
							            		      ||
							            		      ((2*CELL_LENGTH<ballCoordinate.y()&&ballCoordinate.y()<3.5* CELL_LENGTH&&fabs(localMyBodyAngleToBall)<15
							            		      			            		   &&wm.GetMyBodyAngleToXAxis()<20  &&wm.GetMyBodyAngleToXAxis()>-65&&ballCoordinate.x() > myCoordinate.x()
							            		      			            		   )
							            		      			            		      ||  (( ballCoordinate.y()<-2* CELL_LENGTH&& ballCoordinate.y()>-3.5* CELL_LENGTH && fabs(localMyBodyAngleToBall) < 15
							            		      			            		      &&wm.GetMyBodyAngleToXAxis()>-20&&wm.GetMyBodyAngleToXAxis()<65 &&ballCoordinate.x() > myCoordinate.x() )
							            		      			            		     )))

							               {
							            	  destination = ballCoordinate;
							           //    destination = Vector3(ballCoordinate.x() ,
							            	  	//		            	   								ballCoordinate.y(), destination.z());
							            	               	   					//	angleToTurn = localMyBodyAngleToBall;
							            	  angleToTurn = localMyBodyAngleToBall;

							            	  				///	angleToTurn=wm.GetMyAngleToDestination(destination);
							            	  				if (fabs(angleToTurn) < 70)
							            	  				{
							            	  					angleToTurn = localMyBodyAngleToBall;
							            	  				}
							            	  				else
							            	  				{
							            	  					angleToTurn = -localMyBodyAngleToXAxis;
							            	  				}
							            	               	   						topSpeed = MAX_SPEED;
							               }
			}
			if (ballCoordinate.x()< -2 * CELL_LENGTH &&ballCoordinate.x()>-9* CELL_LENGTH){
							if(((fabs(ballCoordinate.y())<5* CELL_LENGTH&&fabs(localMyBodyAngleToBall)<14
										            		   &&wm.GetMyBodyAngleToXAxis()<65  &&wm.GetMyBodyAngleToXAxis()>-65&&ballCoordinate.x() > myCoordinate.x()
										            		   )
										            		      ||  (( ballCoordinate.y()>-6* CELL_LENGTH&& ballCoordinate.y()<-5* CELL_LENGTH && fabs(localMyBodyAngleToBall) < 14
										            		      &&wm.GetMyBodyAngleToXAxis()>10&&wm.GetMyBodyAngleToXAxis()<70 &&ballCoordinate.x() > myCoordinate.x() )
										            		     ))
										            		      ||
										            		      ((5*CELL_LENGTH<ballCoordinate.y()&&ballCoordinate.y()<6* CELL_LENGTH&&fabs(localMyBodyAngleToBall)<14//&&fabs(localMyBodyAngleToBall)>5
										            		      			            		   &&wm.GetMyBodyAngleToXAxis()<-10  &&wm.GetMyBodyAngleToXAxis()>-70&&ballCoordinate.x() > myCoordinate.x()
										            		      			            		   )
										            		      			            		      ))

										               {
										            	  destination = ballCoordinate;
										           //    destination = Vector3(ballCoordinate.x() ,
										            	  	//		            	   								ballCoordinate.y(), destination.z());
										            	               	   					//	angleToTurn = localMyBodyAngleToBall;
										            	  angleToTurn = localMyBodyAngleToBall;

										            	  				///	angleToTurn=wm.GetMyAngleToDestination(destination);
										            	  				if (fabs(angleToTurn) < 70)
										            	  				{
										            	  					angleToTurn = localMyBodyAngleToBall;
										            	  				}
										            	  				else
										            	  				{
										            	  					angleToTurn = -localMyBodyAngleToXAxis;
										            	  				}
										            	               	   						topSpeed = MAX_SPEED;
										               }
						}
			if(  (fabs(localMyBodyAngleToBall)<13&&fabs(localMyBodyAngleToBall)>0
														&&(wm.GetMyBodyAngleToXAxis())>=-140&& (wm.GetMyBodyAngleToXAxis())<-90
														&&    2.5*CELL_LENGTH<(ballCoordinate.y())  && 8.2*CELL_LENGTH<=ballCoordinate.x()&&   9*CELL_LENGTH>=ballCoordinate.x()&& my.y()>ball.y())
														//&&wm.GetClosestToBallOpponentDistanceByVision()<=0.5*CELL_LENGTH
									||	 (fabs(localMyBodyAngleToBall)<13&&fabs(localMyBodyAngleToBall)>0
											&&(wm.GetMyBodyAngleToXAxis())>=-125&& (wm.GetMyBodyAngleToXAxis())<-75
											&&    2.5*CELL_LENGTH<(ballCoordinate.y())  && 7*CELL_LENGTH<=ballCoordinate.x()&&   8.2*CELL_LENGTH>=ballCoordinate.x())	&& my.y()>ball.y()			)
												{
													destination = ballCoordinate;
												angleToTurn = localMyBodyAngleToBall;
												topSpeed = MAX_SPEED;

												}
												 if((fabs(localMyBodyAngleToBall)<13
														&&(wm.GetMyBodyAngleToXAxis())<140 && (wm.GetMyBodyAngleToXAxis())>90
														&&    -2.5*CELL_LENGTH>(ballCoordinate.y())  && 8.2*CELL_LENGTH<=ballCoordinate.x()&&   9*CELL_LENGTH>=ballCoordinate.x()&& my.y()<ball.y())
                                               ||(fabs(localMyBodyAngleToBall)<13
														&&(wm.GetMyBodyAngleToXAxis())<125 && (wm.GetMyBodyAngleToXAxis())>75
														&&    -2.5*CELL_LENGTH>(ballCoordinate.y())  && 7*CELL_LENGTH<=ballCoordinate.x()&&   8.2*CELL_LENGTH>=ballCoordinate.x())&& my.y()>ball.y()
														)
												{
													destination = ballCoordinate;
																angleToTurn = localMyBodyAngleToBall;
																topSpeed = MAX_SPEED;
												}

			if ((7*CELL_LENGTH<=ballCoordinate.x()&& ballCoordinate.x()<= 9 * CELL_LENGTH&& fabs(localMyBodyAngleToBall) < 13//&&fabs(localMyBodyAngleToBall) > 5
											&&wm.GetMyBodyAngleToXAxis()<25&&wm.GetMyBodyAngleToXAxis()>-45 &&wm.GetMyDistanceToDestination(destination) <= 0.7&&
											(ballCoordinate.x() > myCoordinate.x())
											&& ballCoordinate.y() < 0.35 * CELL_LENGTH &&ballCoordinate.y()>0 ) ||
											(7*CELL_LENGTH<ballCoordinate.x()&& ballCoordinate.x()< 9 * CELL_LENGTH&& fabs(localMyBodyAngleToBall) < 14
																			&&wm.GetMyBodyAngleToXAxis()<45&&wm.GetMyBodyAngleToXAxis()>-25 &&
																			(ballCoordinate.x() > myCoordinate.x())//&&wm.GetClosestToBallOpponentDistanceByVision()<=2*CELL_LENGTH
																			&&ballCoordinate.y() >-0.35 * CELL_LENGTH &&ballCoordinate.y()<=0 ))
											{
											destination = ballCoordinate;
												//angleToTurn = localMyBodyAngleToBall;
												angleToTurn = localMyBodyAngleToBall;

																///	angleToTurn=wm.GetMyAngleToDestination(destination);
																if (fabs(angleToTurn) < 70)
																{
																	angleToTurn = localMyBodyAngleToBall;
																}
																else
																{
																	angleToTurn = -localMyBodyAngleToXAxis;
																}
												topSpeed = MAX_SPEED;}
			 if((7*CELL_LENGTH<=ballCoordinate.x()&& ballCoordinate.x()<= 9 * CELL_LENGTH&& fabs(localMyBodyAngleToBall) < 13//&&fabs(localMyBodyAngleToBall) > 5
					&&wm.GetMyBodyAngleToXAxis()<0&&wm.GetMyBodyAngleToXAxis()>-75 &&
					(ballCoordinate.x() > myCoordinate.x())
					&& ballCoordinate.y() < 3.5 * CELL_LENGTH &&ballCoordinate.y()>0.35*CELL_LENGTH && my.y()>ball.y()) ||
					(7*CELL_LENGTH<ballCoordinate.x()&& ballCoordinate.x()< 8 * CELL_LENGTH&& fabs(localMyBodyAngleToBall) < 14
													&&wm.GetMyBodyAngleToXAxis()<75&&wm.GetMyBodyAngleToXAxis()>0 &&
													(ballCoordinate.x() > myCoordinate.x())//&&wm.GetClosestToBallOpponentDistanceByVision()<=2*CELL_LENGTH
													&&ballCoordinate.y() >-3.5 * CELL_LENGTH &&ballCoordinate.y()<=-0.35*CELL_LENGTH)&& my.y()<ball.y())
			{
		//		destination = ballCoordinate;
																//angleToTurn = localMyBodyAngleToBall;
																angleToTurn = localMyBodyAngleToBall;

																				///	angleToTurn=wm.GetMyAngleToDestination(destination);
																				if (fabs(angleToTurn) < 70)
																				{
																					angleToTurn = localMyBodyAngleToBall;
																				}
																				else
																				{
																					angleToTurn = -localMyBodyAngleToXAxis;
																				}
																topSpeed = MAX_SPEED;
			}
			 if(ballCoordinate.x()<= 7 * CELL_LENGTH && ballCoordinate.x()>=5 * CELL_LENGTH)
	          if((5.2*CELL_LENGTH<ballCoordinate.y()&&ballCoordinate.y()<=(6* CELL_LENGTH)&&fabs(localMyBodyAngleToBall)<15
				                         		   &&wm.GetMyBodyAngleToXAxis()<=0  &&wm.GetMyBodyAngleToXAxis()>=-60//&&ballCoordinate.x() > myCoordinate.x()
				                         		//   &&wm.GetClosestToBallOpponentDistanceByVision()<=2*CELL_LENGTH
				                         		   )//&&fabs(localMyBodyAngleToBall) > 5)
				                         		      ||  ( ballCoordinate.y()<-3.5* CELL_LENGTH&& ballCoordinate.y()>-5.2* CELL_LENGTH && fabs(localMyBodyAngleToBall) < 15
				                         		      &&wm.GetMyBodyAngleToXAxis()<-10&&wm.GetMyBodyAngleToXAxis()<45 &&ballCoordinate.x() > myCoordinate.x()
				                         		      &&wm.GetClosestToBallOpponentDistanceByVision()<=2*CELL_LENGTH)//&&fabs(localMyBodyAngleToBall) > 5)
				                         		      ||
				                         		     (-5.2*CELL_LENGTH>ballCoordinate.y()&&ballCoordinate.y()>=(-6.5* CELL_LENGTH)&&fabs(localMyBodyAngleToBall)<15
				                         		     			                         		   &&wm.GetMyBodyAngleToXAxis()>=0  &&wm.GetMyBodyAngleToXAxis()<=60//&&ballCoordinate.x() > myCoordinate.x()
				                         		     			                         	//	   &&wm.GetClosestToBallOpponentDistanceByVision()<=2*CELL_LENGTH
				                         		     			                         		   &&fabs(localMyBodyAngleToBall) > 0)
				                         		     			                         		   ||
				                         		     			                         		 ( ballCoordinate.y()>3.5* CELL_LENGTH&& ballCoordinate.y()<5.2* CELL_LENGTH && fabs(localMyBodyAngleToBall) < 15
				                         		     			                         						                         		      &&wm.GetMyBodyAngleToXAxis()<10&&wm.GetMyBodyAngleToXAxis()>-45 &&ballCoordinate.x() > myCoordinate.x()
				                         		     			                         						                         		      &&wm.GetClosestToBallOpponentDistanceByVision()<=2*CELL_LENGTH)//&&fabs(localMyBodyAngleToBall) > 5)
				                         		     			                         		   )

				                            {
				                         	  destination = ballCoordinate;
				                        //    destination = Vector3(ballCoordinate.x() ,
				                         	  	//		            	   								ballCoordinate.y(), destination.z());
				                         	               	   					//	angleToTurn = localMyBodyAngleToBall;
				                         	  angleToTurn = localMyBodyAngleToBall;

				                         	  				///	angleToTurn=wm.GetMyAngleToDestination(destination);
				                         	  				if (fabs(angleToTurn) < 70)
				                         	  				{
				                         	  					angleToTurn = localMyBodyAngleToBall;
				                         	  				}
				                         	  				else
				                         	  				{
				                         	  					angleToTurn = -localMyBodyAngleToXAxis;
				                         	  				}
				                         	               	   						topSpeed = MAX_SPEED;
				                            }



			 /////////////////////////////////////////////////////////////

			 if(ballCoordinate.x()<= 8 * CELL_LENGTH && ballCoordinate.x()>=7 * CELL_LENGTH)
						 				          if((5.2*CELL_LENGTH<ballCoordinate.y()&&ballCoordinate.y()<=(6* CELL_LENGTH)&&fabs(localMyBodyAngleToBall)<15
						 							                         		   &&wm.GetMyBodyAngleToXAxis()<=-80  &&wm.GetMyBodyAngleToXAxis()>=-115//&&ballCoordinate.x() > myCoordinate.x()
						 							                         		//   &&wm.GetClosestToBallOpponentDistanceByVision()<=2*CELL_LENGTH
						 							                         		  && ball.y()<my.y()  )// &&fabs(localMyBodyAngleToBall) > 5)
						 							                         		      ||  ( ballCoordinate.y()<-3.5* CELL_LENGTH&& ballCoordinate.y()>-5.2* CELL_LENGTH && fabs(localMyBodyAngleToBall) < 15
						 							                         		      &&wm.GetMyBodyAngleToXAxis()>70&&wm.GetMyBodyAngleToXAxis()<120&& ball.y()>my.y()// &&ballCoordinate.x() > myCoordinate.x()
						 							                         		  //    &&wm.GetClosestToBallOpponentDistanceByVision()<=2*CELL_LENGTH&&fabs(localMyBodyAngleToBall) > 5
						 							                         		      )
						 							                         		      ||
						 							                         		     (-5.2*CELL_LENGTH>ballCoordinate.y()&&ballCoordinate.y()>=(-6.5* CELL_LENGTH)&&fabs(localMyBodyAngleToBall)<15
						 							                         		     			                         		   &&wm.GetMyBodyAngleToXAxis()>=80  &&wm.GetMyBodyAngleToXAxis()<=105//&&ballCoordinate.x() > myCoordinate.x()
						 							                         		     			                         	//	   &&wm.GetClosestToBallOpponentDistanceByVision()<=2*CELL_LENGTH
						 							                         		     			                         		   &&fabs(localMyBodyAngleToBall) > 0&& ball.y()>my.y())
						 							                         		     			                         		   ||
						 							                         		     			                         		 ( ballCoordinate.y()>3.5* CELL_LENGTH&& ballCoordinate.y()<5.2* CELL_LENGTH && fabs(localMyBodyAngleToBall) < 15
						 							                         		     			                         						                         		      &&wm.GetMyBodyAngleToXAxis()<-80&&wm.GetMyBodyAngleToXAxis()>-110 &&ballCoordinate.x() > myCoordinate.x()
						 							                         		     			                         						                         		 && ball.y()<my.y()  &&wm.GetClosestToBallOpponentDistanceByVision()<=2*CELL_LENGTH)//&&fabs(localMyBodyAngleToBall) > 5)
						 							                         		     			                         		   )

						 							                            {
						 				        	 if ((wm.CanSeeTheFlag(VO_GOAL1_R) && wm.CanSeeTheFlag(VO_GOAL2_R)))
						 				        	 {
						 							                         	  destination = ballCoordinate;
						 							                         	 angleToTurn = localMyBodyAngleToBall;

						 							                         				 							                         	  				///	angleToTurn=wm.GetMyAngleToDestination(destination);
						 							                         				 							                         	  				if (fabs(angleToTurn) < 70)
						 							                         				 							                         	  				{
						 							                         				 							                         	  					angleToTurn = localMyBodyAngleToBall;
						 							                         				 							                         	  				}
						 							                         				 							                         	  				else
						 							                         				 							                         	  				{
						 							                         				 							                         	  					angleToTurn = -localMyBodyAngleToXAxis;
						 							                         		 							                         	  				}
						 							                         				 							                         	               	   						topSpeed = MAX_SPEED;
						 				        	 }
						 				        	 else
						 				        	 {
                                                                          if(wm.GetMyDistanceToBall()<0.7)
						 							                       	topSpeed = MIN_SPEED;
						 							                         	angleToTurn = localLastCyclesAverageBallGoalToXAxisAngle- localMyBodyAngleToXAxis;
						 							                         	if(ball.y()<0)
						 							                         		destination = Vector3(ballCoordinate.x() - 0.1,
						 							                         					 							                         	    	      	  								ballCoordinate.y() , destination.z());
						 							                         	else
						 							                        		destination = Vector3(ballCoordinate.x() - 0.1,
						 							                         					 							                         	    	      	  								ballCoordinate.y() , destination.z());
						 							                          }
						 							                        //    destination = Vector3(ballCoordinate.x() ,
						 							                         	  	//		            	   								ballCoordinate.y(), destination.z());
						 							                       //  	               	   					//	angleToTurn = localMyBodyAngleToBall;

						 							                            }

			 if (wm.GetMyTeamIndex() == TI_LEFT)
			 {
						 if(ballCoordinate.x()< 9 * CELL_LENGTH && ballCoordinate.x()>8 * CELL_LENGTH)
									 				          if((fabs(localMyBodyAngleToBall)<15 && ballCoordinate.y()>5.2* CELL_LENGTH
									 							                         		   &&wm.GetMyBodyAngleToXAxis()<=-90  &&wm.GetMyBodyAngleToXAxis()>=-120//&&ballCoordinate.x() > myCoordinate.x()
									 							                         		//   &&wm.GetClosestToBallOpponentDistanceByVision()<=2*CELL_LENGTH
									 							                         		   &&fabs(localMyBodyAngleToBall) > 0)
									 							                         		      ||  ( ballCoordinate.y()<-3.5* CELL_LENGTH&& ballCoordinate.y()>-5.2* CELL_LENGTH && fabs(localMyBodyAngleToBall) < 15
									 							                         		      &&wm.GetMyBodyAngleToXAxis()>90&&wm.GetMyBodyAngleToXAxis()<120// &&ballCoordinate.x() > myCoordinate.x()
									 							                         		  //    &&wm.GetClosestToBallOpponentDistanceByVision()<=2*CELL_LENGTH&&fabs(localMyBodyAngleToBall) > 5
									 							                         		      )
									 							                         		      ||
									 							                         		     (-5.2*CELL_LENGTH>ballCoordinate.y()&&ballCoordinate.y()>=(-6.5* CELL_LENGTH)&&fabs(localMyBodyAngleToBall)<14
									 							                         		     			                         		   &&wm.GetMyBodyAngleToXAxis()>=90  &&wm.GetMyBodyAngleToXAxis()<=120//&&ballCoordinate.x() > myCoordinate.x()
									 							                         		     			                         	//	   &&wm.GetClosestToBallOpponentDistanceByVision()<=2*CELL_LENGTH
									 							                         		     			                         		   &&fabs(localMyBodyAngleToBall) > 0)
									 							                         		     			                         		   ||
									 							                         		     			                         		 ( ballCoordinate.y()>3.5* CELL_LENGTH&& ballCoordinate.y()<5.2* CELL_LENGTH && fabs(localMyBodyAngleToBall) < 13
									 							                         		     			                         						                         		      &&wm.GetMyBodyAngleToXAxis()<-90&&wm.GetMyBodyAngleToXAxis()>-115 //&&ballCoordinate.x() > myCoordinate.x()
									 							                         		     			                         						                         		      &&wm.GetClosestToBallOpponentDistanceByVision()<=2*CELL_LENGTH&&fabs(localMyBodyAngleToBall) > 0)
									 							                         		     			                         		   )

									 							                            {
									 				        	 if ((wm.CanSeeTheFlag(VO_GOAL1_R) && wm.CanSeeTheFlag(VO_GOAL2_R)))
									 				        	 {
									 							                         	  destination = ballCoordinate;
									 							                         	  angleToTurn = localMyBodyAngleToBall;

									 									 							                         	  				///	angleToTurn=wm.GetMyAngleToDestination(destination);
									 									 							                         	  				if (fabs(angleToTurn) < 70)
									 									 							                         	  				{
									 									 							                         	  					angleToTurn = localMyBodyAngleToBall;
									 									 							                         	  				}
									 									 							                         	  				else
									 									 							                         	  				{
									 									 							                         	  					angleToTurn = -localMyBodyAngleToXAxis;
									 									 							                         	  				}
									 									 							                         	               	   						topSpeed = MAX_SPEED;
									 				        	 }
									 				        	 else
									 				        	 {

//									 				        		topSpeed = MIN_SPEED;
//									 				        		angleToTurn = localLastCyclesAverageBallGoalToXAxisAngle- localMyBodyAngleToXAxis;
//									 				        		if(ball.x()<0)
//									 				        					 							                        		destination = Vector3(ballCoordinate.x() + 0.1,
//									 				        					 							                         					 							                         	    	      	  								ballCoordinate.y() +0.15, destination.z());
//									 				        					 							                         	else
//									 				        					 							                        		destination = Vector3(ballCoordinate.x() + 0.1,
									 				       	 destination = WalkToDestinationCoordinate(
									 				        														 			 						destinationCoordinate); 					 							                         					 							                         	    	      	  				//				ballCoordinate.y() -0.15, destination.z());

									 				        	 }
									 							                        //    destination = Vector3(ballCoordinate.x() ,
									 							                         	  	//		            	   								ballCoordinate.y(), destination.z());
									 							                         	               	   					//	angleToTurn = localMyBodyAngleToBall;

									 							                            }



//							if( (wm.GetMyAngleToFlag(VO_GOAL1_R)* wm.GetMyAngleToFlag(VO_GOAL2_R) < 0) &&  ball.x()>7*CELL_LENGTH)  //&&ball.x()>my.x()
//									 {//cout<<"LLLLLLLLL"<< myCoordinate.y();
//												            //	   destination = ballCoordinate;
//								destination = Vector3(ballCoordinate.x() ,
//								    	      	  								ballCoordinate.y() , destination.z());
//												            	   			//			angleToTurn = localMyBodyAngleToBall;
//												            	  // angleToTurn = localMyBodyAngleToBall;
//												            	   angleToTurn = localLastCyclesAverageBallGoalToXAxisAngle- localMyBodyAngleToXAxis;
//
//												            	   				///	angleToTurn=wm.GetMyAngleToDestination(destination);
//
//
//												            	   					topSpeed = MAX_SPEED;
//												            	   					//	if(agent.GetType()!=0 && agent.GetType()!=2)
//												            	   											//		topSpeed=MAXMAX_SPEED;
//												               }
			 }
			 else
			 {
				 ////////////////////////////////////////////////
				 if(ballCoordinate.x()< 9 * CELL_LENGTH && ballCoordinate.x()>8 * CELL_LENGTH)
											 				          if((fabs(localMyBodyAngleToBall)<15 && ballCoordinate.y()>5.2* CELL_LENGTH
											 							                         		   &&wm.GetMyBodyAngleToXAxis()<=-90  &&wm.GetMyBodyAngleToXAxis()>=-120//&&ballCoordinate.x() > myCoordinate.x()
											 							                         		//   &&wm.GetClosestToBallOpponentDistanceByVision()<=2*CELL_LENGTH
											 							                         		   &&fabs(localMyBodyAngleToBall) > 0)
											 							                         		      ||  ( ballCoordinate.y()<-3.5* CELL_LENGTH&& ballCoordinate.y()>-5.2* CELL_LENGTH && fabs(localMyBodyAngleToBall) < 15
											 							                         		      &&wm.GetMyBodyAngleToXAxis()>90&&wm.GetMyBodyAngleToXAxis()<120// &&ballCoordinate.x() > myCoordinate.x()
											 							                         		  //    &&wm.GetClosestToBallOpponentDistanceByVision()<=2*CELL_LENGTH&&fabs(localMyBodyAngleToBall) > 5
											 							                         		      )
											 							                         		      ||
											 							                         		     (-5.2*CELL_LENGTH>ballCoordinate.y()&&ballCoordinate.y()>=(-6.5* CELL_LENGTH)&&fabs(localMyBodyAngleToBall)<14
											 							                         		     			                         		   &&wm.GetMyBodyAngleToXAxis()>=90  &&wm.GetMyBodyAngleToXAxis()<=120//&&ballCoordinate.x() > myCoordinate.x()
											 							                         		     			                         	//	   &&wm.GetClosestToBallOpponentDistanceByVision()<=2*CELL_LENGTH
											 							                         		     			                         		   &&fabs(localMyBodyAngleToBall) > 0)
											 							                         		     			                         		   ||
											 							                         		     			                         		 ( ballCoordinate.y()>3.5* CELL_LENGTH&& ballCoordinate.y()<5.2* CELL_LENGTH && fabs(localMyBodyAngleToBall) < 13
											 							                         		     			                         						                         		      &&wm.GetMyBodyAngleToXAxis()<-90&&wm.GetMyBodyAngleToXAxis()>-115 //&&ballCoordinate.x() > myCoordinate.x()
											 							                         		     			                         						                         		      &&wm.GetClosestToBallOpponentDistanceByVision()<=2*CELL_LENGTH&&fabs(localMyBodyAngleToBall) > 0)
											 							                         		     			                         		   )

											 							                            {
											 				        	 if ((wm.CanSeeTheFlag(VO_GOAL1_L) && wm.CanSeeTheFlag(VO_GOAL2_L)))
											 				        	 {
											 							                         	  destination = ballCoordinate;
											 							                         	  angleToTurn = localMyBodyAngleToBall;

											 									 							                         	  				///	angleToTurn=wm.GetMyAngleToDestination(destination);
											 									 							                         	  				if (fabs(angleToTurn) < 70)
											 									 							                         	  				{
											 									 							                         	  					angleToTurn = localMyBodyAngleToBall;
											 									 							                         	  				}
											 									 							                         	  				else
											 									 							                         	  				{
											 									 							                         	  					angleToTurn = -localMyBodyAngleToXAxis;
											 									 							                         	  				}
											 									 							                         	               	   						topSpeed = MAX_SPEED;
											 				        	 }
											 				        	 else
											 				        	 {

											 				        		topSpeed = MIN_SPEED;
											 				        		angleToTurn = localLastCyclesAverageBallGoalToXAxisAngle- localMyBodyAngleToXAxis;
//											 				        		if(ball.x()<0)
//											 				        					 							                         		destination = Vector3(ballCoordinate.x() + 0.1,
//											 				        					 							                         					 							                         	    	      	  								ballCoordinate.y() +0.15, destination.z());
//											 				        					 							                         	else
//											 				        					 							                         		destination = Vector3(ballCoordinate.x() + 0.1,
//											 				        					 							                         					 							                         	    	      	  								ballCoordinate.y() -0.15, destination.z());
											 				      		 destination = WalkToDestinationCoordinate(
											 				      													 			 						destinationCoordinate);
											 				        	 }
											 							                        //    destination = Vector3(ballCoordinate.x() ,
											 							                         	  	//		            	   								ballCoordinate.y(), destination.z());
											 							                         	               	   					//	angleToTurn = localMyBodyAngleToBall;

											 							                            }

//if(ball.x()>7*CELL_LENGTH && fabs(ball.y()>2.5*CELL_LENGTH))
//	destination = WalkToDestinationCoordinate(
//														destinationCoordinate );

//									if( (wm.GetMyAngleToFlag(VO_GOAL1_L)* wm.GetMyAngleToFlag(VO_GOAL2_L) < 0) &&  ball.x()>7*CELL_LENGTH)  //ball.x()>my.x() &&
//											 {//cout<<"LLLLLLLLL"<< myCoordinate.y();
//														            //	   destination = ballCoordinate;
//										destination = Vector3(ballCoordinate.x() ,
//										    	      	  								ballCoordinate.y() , destination.z());
//														            	   			//			angleToTurn = localMyBodyAngleToBall;
//														            	  // angleToTurn = localMyBodyAngleToBall;
//														            	   angleToTurn = localLastCyclesAverageBallGoalToXAxisAngle- localMyBodyAngleToXAxis;
//
//														            	   				///	angleToTurn=wm.GetMyAngleToDestination(destination);
//
//
//														            	   					topSpeed = MAX_SPEED;
//														            	   					//	if(agent.GetType()!=0 && agent.GetType()!=2)
//														            	   											//		topSpeed=MAXMAX_SPEED;
//														               }

				 /////////////////////////////////////////////
			 }
//			 if (wm.GetMyTeamIndex() == TI_LEFT)
//			 {
//			 if(ball.x()>6.5*CELL_LENGTH && fabs(ball.y())>3.5*CELL_LENGTH   )
//			 {
//				 if ((wm.CanSeeTheFlag(VO_GOAL1_R) || wm.CanSeeTheFlag(VO_GOAL2_R)))
//														 				        	 {
//														 							                         	  destination = ballCoordinate;
//														 							                         	  angleToTurn = localMyBodyAngleToBall;
//
//														 									 							                         	  				///	angleToTurn=wm.GetMyAngleToDestination(destination);
//														 									 							                         	  				if (fabs(angleToTurn) < 70)
//														 									 							                         	  				{
//														 									 							                         	  					angleToTurn = localMyBodyAngleToBall;
//														 									 							                         	  				}
//														 									 							                         	  				else
//														 									 							                         	  				{
//														 									 							                         	  					angleToTurn = -localMyBodyAngleToXAxis;
//														 									 							                         	  				}
//														 									 							                         	               	   						topSpeed = MAX_SPEED;
//														 				        	 }
//			 }
//			 else
//			 {
//
//													 			 destination = WalkToDestinationCoordinate(
//													 			 						destinationCoordinate);
//													 			topSpeed = MAX_SPEED;
//			 }
//			 }
//			 else
//			 {
//				 if(ball.x()>6.5*CELL_LENGTH && fabs(ball.y())>3.5*CELL_LENGTH   )
//						 {
//							 if ((wm.CanSeeTheFlag(VO_GOAL1_L)  || wm.CanSeeTheFlag(VO_GOAL2_L)))
//																	 				        	 {
//																	 							                         	  destination = ballCoordinate;
//																	 							                         	  angleToTurn = localMyBodyAngleToBall;
//
//																	 									 							                         	  				///	angleToTurn=wm.GetMyAngleToDestination(destination);
//																	 									 							                         	  				if (fabs(angleToTurn) < 70)
//																	 									 							                         	  				{
//																	 									 							                         	  					angleToTurn = localMyBodyAngleToBall;
//																	 									 							                         	  				}
//																	 									 							                         	  				else
//																	 									 							                         	  				{
//																	 									 							                         	  					angleToTurn = -localMyBodyAngleToXAxis;
//																	 									 							                         	  				}
//																	 									 							                         	               	   						topSpeed = MAX_SPEED;
//																	 				        	 }
//						 }
//						 else
//						 {
//
//																 			 destination = WalkToDestinationCoordinate(
//																 			 						destinationCoordinate);
//																 			topSpeed = MAX_SPEED;
//						 }
//			 }
		//if (whetherStriker == false)
			{
				if (ballCoordinate.x() >= -4 * CELL_LENGTH
						&& ballCoordinate.x() < 6.5 * CELL_LENGTH
						&& fabs(ballCoordinate.y()) < 5 * CELL_LENGTH
						&& (ballCoordinate.x() > myCoordinate.x())
						&& (fabs(my.y()) < fabs(ball.y()) + 0.1)) ///changed by gaojin
				{
					//if (((my.y() < ball.y() + 0.1) && my.y() >= 0)
					// || ((my.y() > ball.y() - 0.1) && my.y() < 0))
					{
				//		destination = ballCoordinate;
						angleToTurn = localMyBodyAngleToBall;

						destination = Vector3(destination.x() + 0.1, destination.y() ,	destination.z());
						topSpeed = MAX_SPEED;
					}

//					cout
//							<< "ballCoordinate.x()<4*CELL_LENGTH&&fabs(myCoordinate.y())<2.5*CELL_LENGTH&&(ballCoordinate.x()>myCoordinate.x() )"
//							<< endl;
				}

				if (ballCoordinate.x() < -4 * CELL_LENGTH
						&& fabs(myCoordinate.y()) < 3.5 * CELL_LENGTH
						&& (ballCoordinate.x() > myCoordinate.x())
						&& messageParser.WhetherCanTurnToOpponentGoal() == false)
				{
					destination = ballCoordinate;
					angleToTurn = localMyBodyAngleToBall;
					topSpeed = MAX_SPEED;
//					cout
//							<< "ballCoordinate.x()<-4*CELL_LENGTH&&fabs(myCoordinate.y())<3.5*CELL_LENGTH&&(ballCoordinate.x()>myCoordinate.x() )"
//							<< endl;
				}
			}
//if(agent.GetType()==0 && wm.CanSeeTheBall() && wm.GetMyDistanceToBall() <2*CELL_LENGTH
//		&& wm.GetClosestToBallOpponentDistanceByVision()>1.5*CELL_LENGTH &&wm.GetMyAngleToFlag(VO_GOAL2_R ))
//{
//		destination = WalkToDestinationCoordinate(
//															destinationCoordinate );
//		//	destination = Vector3(destination.x()+0.05 , destination.y() ,	destination.z());
//		//	angleToTurn=(wm.GetMyAngleToFlag(VO_GOAL2_R)+wm.GetMyAngleToFlag(VO_GOAL1_R))/2;
//		//	destination=	(	destinationCoordinate.x,destinationCoordinate.y,destinationCoordinate.z );
////		 if (ball.x()>my.x()  &&(wm.CanSeeTheFlag(VO_GOAL1_R) && wm.CanSeeTheFlag(VO_GOAL2_R)))
//	//			 return behavior.stopAndShoottingbeforekick();
//			/////////////////////////////////////////////////////////////////////////////////////////////////
//			if ((localMyDistanceToBall <= 0.21 && fabs(localMyAngleToBall) < 9   //原来为12  0.24
//					&& fabs(localMyAngleToBall) > 0 &&(wm.GetMyAngleToFlag(VO_GOAL2_R)	   )  //&&wm.GetMyAngleToFlag(VO_GOAL2_R)> -25)   //0 -25
//					&&ballCoordinate.y() < 0* CELL_LENGTH&& ball.x()>my.x())
//			|| (localMyDistanceToBall <= 0.21 && fabs(localMyAngleToBall) < 9   //原来为12
//					&& fabs(localMyAngleToBall) > 0 &&(wm.GetMyAngleToFlag(VO_GOAL1_R)	  )//&&wm.GetMyAngleToFlag(VO_GOAL1_R)<25)  // 0 25
//					&&ballCoordinate.y() >  0* CELL_LENGTH&& ball.x()>my.x())
////					||
////					(localMyDistanceToBall <= 0.22 && fabs(localMyAngleToBall) < 10   //原来为12  0.24
////								&& fabs(localMyAngleToBall) > 0 &&(wm.GetMyAngleToFlag(VO_GOAL2_L)	 < 0&&wm.GetMyAngleToFlag(VO_GOAL2_L)> -100)
////								&&ballCoordinate.y() < 0* CELL_LENGTH)
////						|| (localMyDistanceToBall <= 0.22 && fabs(localMyAngleToBall) < 10   //原来为12
////								&& fabs(localMyAngleToBall) > 0 &&(wm.GetMyAngleToFlag(VO_GOAL1_L)	 >0&&wm.GetMyAngleToFlag(VO_GOAL1_L)<100)
////								&&ballCoordinate.y() >  0* CELL_LENGTH)
//			)
//			{
//				beginShoot = true;
//			}
//
//
//			if (beginShoot == false)
//			{
//				if (myRole == ROLE_VANGUARD)
//				{
//					if (wm.IsTheBallOutOfShootArea())
//					{
//						initShootControlParameter();
//					}
//
//				}
//				else
//				{
////					if (!wm.CanSeeTheBall())
////					{
////						initShootControlParameter();
////					}
////					if (localMyDistanceToBall < 0.175)
////					{
////						initShootControlParameter();
////					}
////					if (localMyDistanceToBall < 0.2
////							&& fabs(localMyAngleToBall) > 35)
////					{
////						initShootControlParameter();
////					}
////					if (wm.EstimateWhetherUseHalfWalk() == true)
////					{
////						initShootControlParameter();
////					}
//				}
//			//	return prepareForShootting();
//		//		return prepareShootingForFreeKick();
//		//		return HandleBall();
//			}
//			else
//			{
//		//		if (localMyDistanceToBall > 0.3
//		//				|| fabs(this->localMyBodyAngleToXAxis) > 20)
//		//		{
//		//			finishKick = true;
//		//			initShootControlParameter();
//		//		}
//				if (gaitStoped == true)
//				{
//		//			if (timeCounter >= 98)
//		//				finishKick = true;
//
//					if (rigthFootShoot)
//							return basicMotion.ShootingFromA();
//					//	return basicMotion.NexLTest();
//
//					//	return basicMotion.RightFootShootingBallCIT();
//							//	rightFootShootingBallCIT();
//					else
//					//	return basicMotion.LeftFootShootingBallCIT();
//				//	return basicMotion.NexRTest();
//						return basicMotion.ShootingFromARight();
//				}
//				else
//				{
//					if (newWalk.GetWalkCounter() == 7)
//					{
//						gaitStoped = true;
//						basicMotion.SetTimeCounter(0);
//						if (localMyAngleToBall > 0)
//							rigthFootShoot = false;
//						else
//							rigthFootShoot = true;
//					}
//			//		return prepareForShootting();
//			//	return prepareShootingForFreeKick();
//				//	return HandleBall();
//				}
//			}
//}
////////////////////////////////////////////////////////////////////////////////////////////////////
		//	else if (whetherStriker == false)
			{
//				cout << "I am Striker" << endl;
			}
//			if(ball.x()>0)
//				topSpeed = NULL_SPEED;



#endif

		}
	//	else
			if (!wm.CanSeeTheBall() && wm.CanDoLocalizationDirectly())
		{
			turnHeadStrategy(fallDownTurnHead);

			destination = WalkToDestinationCoordinate(
					wm.GetLastCyclesAverageBallCoordinate());

			if (wm.GetMyDistanceToDestination(destination) <= 0.5)
			{
				angleToTurn = localLastCyclesAverageBallGoalToXAxisAngle
						- localMyBodyAngleToXAxis;
			}
			else
			{
			//	angleToTurn = -localMyBodyAngleToXAxis;
				 angleToTurn = localMyBodyAngleToBall;
			}

		}
		else if (wm.CanSeeTheBall() && !wm.CanDoLocalizationDirectly())
		{
#ifdef AGENT_STRATEGY_OUTPUT
			cout << "in handle ball:" << endl;
			cout
					<< "wm.CanSeeTheBall()&&!wm.CanDoLocalizationDirectly() my.y():"
					<< my.y() << endl;
#endif
			if (fabs(my.y()) < 0.9 * CELL_LENGTH)
			{
				turnHeadStrategy(fallDownTurnHead);

				destination = ballCoordinate;

				if (wm.GetMyDistanceToDestination(destination) <= 0.5)
				{
					angleToTurn = localLastCyclesAverageBallGoalToXAxisAngle
							- localMyBodyAngleToXAxis;
				}
				else
				{
				//	angleToTurn = -localMyBodyAngleToXAxis;
					 angleToTurn = localMyBodyAngleToBall;
				}

				topSpeed = MAX_SPEED;
			}
			else
			{
				turnHeadStrategy(fallDownTurnHead);

				destination = WalkToDestinationCoordinate(
						wm.GetMyCoordinate());
				if (wm.GetMyDistanceToDestination(destination) <= 0.5)
				{
					angleToTurn = localLastCyclesAverageBallGoalToXAxisAngle
							- localMyBodyAngleToXAxis;
				}
				else
				{
				//	angleToTurn = -localMyBodyAngleToXAxis;
					 angleToTurn = localMyBodyAngleToBall;
				}

			}

		}
		else if (!wm.CanSeeTheBall() && !wm.CanDoLocalizationDirectly())
		{
			turnHeadStrategy(fallDownTurnHead);

			destination = WalkToDestinationCoordinate(
					wm.GetLastCyclesAverageBallCoordinate());

			if (wm.GetMyDistanceToDestination(destination) <= 0.5)
			{
				angleToTurn = localLastCyclesAverageBallGoalToXAxisAngle
						- localMyBodyAngleToXAxis;
			}
			else
			{
			//	angleToTurn = -localMyBodyAngleToXAxis;
				 angleToTurn = localMyBodyAngleToBall;
			}

		}
	   if(wm.CanSeeTheBall()&&wm.GetMyDistanceToBall()<0.3*CELL_LENGTH&&wm.GetClosestToBallOpponentDistanceByVision()<0.1
	    		&&ball.x()>=-5&&ball.x()<=7&&wm.GetClosestToMeOpponentDistanceByVision()<0.3*CELL_LENGTH)
	   {
		  destination =ball;
		  cout<<"handle the ball-------------------"<<endl;
	   }
      if(wm.CanSeeTheBall()&&ball.y()>my.y()&&my.y()>1
    	  &&ball.x()>8*CELL_LENGTH&&my.x()>7.5*CELL_LENGTH
    	  &&wm.GetMyDistanceToBall()<wm.GetClosestToBallOpponentDistanceByVision()-0.2*CELL_LENGTH
    	  &&wm.CanSeeTheFlag(VO_FLAG1_R))
       {
    	  destination = Vector3(ballCoordinate.x() + 0.1,
    	  								ballCoordinate.y() + 0.1, destination.z());
    	  cout<<"upupup"<<endl;
       }
      else if(wm.CanSeeTheBall()&&ball.y()<my.y()&&my.y()<-1
        	  &&ball.x()>8*CELL_LENGTH&&my.x()>7.5*CELL_LENGTH
        	  &&wm.GetMyDistanceToBall()<wm.GetClosestToBallOpponentDistanceByVision()-0.2*CELL_LENGTH
        	  &&wm.CanSeeTheFlag(VO_FLAG2_R))
      {
    	  destination = Vector3(ballCoordinate.x() + 0.1,
    	      	  								ballCoordinate.y() - 0.1, destination.z());
    	  cout<<"downdowndown"<<endl;
      }
		Vector3 closestToBallTeammateCoordinate = wm.GetNewTeammateCoordinate(
				wm.GetClosestToBallTeammateNumberByVision());
#ifdef AGENT_STRATEGY_OUTPUT
		cout << "closestToBallTeammateCoordinate:"
				<< closestToBallTeammateCoordinate.x() << ","
				<< closestToBallTeammateCoordinate.y() << "," << endl;
		cout << "wm.GetClosestToBallTeammateDistanceByVision():"
				<< wm.GetClosestToBallTeammateDistanceByVision() << endl;
#endif
//		if (my.x() > ball.x() - 0.3 * CELL_LENGTH
//				&& fabs(my.y() - ball.y()) < 0.8 * CELL_LENGTH
//				&& closestToBallTeammateCoordinate.x() < ball.x()
//				&& fabs(closestToBallTeammateCoordinate.y() - ball.y())
//						< 0.5 * CELL_LENGTH
//				&& wm.GetClosestToBallTeammateDistanceByVision()
//						< 1.2 * CELL_LENGTH)
//		{
//			for (TPlayerSenseMap::iterator iter =
//					messageParser.mTeamMateSenseMap.begin();
//					iter != messageParser.mTeamMateSenseMap.end(); iter++)
//					{
//				if (iter->second.unum
//						== wm.GetClosestToBallTeammateNumberByVision())
//				{
//					if (wm.PlayerWhetherFallDown(iter->first) == false)
//					{
//						cout << "walk forwad" << endl;
//						cout << "closestToBallTeammateCoordinate:"
//								<< closestToBallTeammateCoordinate.x() << ","
//								<< closestToBallTeammateCoordinate.y() << ","
//								<< endl;
//						angleToTurn = -localMyBodyAngleToXAxis;
//						destination = Vector3(ball.x() + 2 * CELL_LENGTH
//						, ball.y(), 0);
//						theNewWalkSolutions(destination, angleToTurn, topSpeed);
//					}
//				}
//			}
//		}

		float goalieToBallDistance;
		if (wm.GetGoalieToBallDistance(goalieToBallDistance) == true)
		{
			if (goalieToBallDistance < 1.5)
			{
				angleToTurn = -localMyBodyAngleToXAxis;
				///	destination=wm.GetMyCoordinate();
				if (ballCoordinate.y() > 0)
				{
					if (myCoordinate.y() > ballCoordinate.y())
					{
						destination = Vector3(ballCoordinate.x() + 2,
								ballCoordinate.y() + 0.8, destination.z());
					}
					else if (myCoordinate.y() <= ballCoordinate.y())
					{
						destination = Vector3(ballCoordinate.x() + 2,
								ballCoordinate.y() * 0.8, destination.z());
					}
				}
				else if (ballCoordinate.y() <= 0)
				{
					if (myCoordinate.y() > ballCoordinate.y())
					{
						destination = Vector3(ballCoordinate.x() + 2,
								ballCoordinate.y() * 0.8, destination.z());
					}
					else if (myCoordinate.y() <= ballCoordinate.y())
					{
						destination = Vector3(ballCoordinate.x() + 2,
								ballCoordinate.y() - 0.8, destination.z());
					}
				}
#ifdef AGENT_STRATEGY_OUTPUT
				cout << "goalieToBallDistance:" << goalieToBallDistance << endl;
#endif
				//		cout<<"i can not see the ball,angleToTurn=-wm.GetMyBodyAngleToXAxis():     "<<angleToTurn<<endl;
				//		cout<<"i can not see the balldestination=wm.GetMyCoordinate();     "<<destination<<endl;
				topSpeed = MAX_SPEED;
			}
		}


	if (localCurrentGameMode != PM_PlayOn) ///changed by gaojin
	{
		if ((localCurrentGameMode == PM_FREE_KICK_Opp)
				&& localMyDistanceToBall < 1.85)
		{
			topSpeed = MIN_SPEED;
		}
		else if (localCurrentGameMode == PM_GOAL_KICK_Opp)
		{
			destination = Vector3(7 * CELL_LENGTH,ball.y(),0);
			theNewWalkSolutions(destination, angleToTurn, topSpeed);
			angleToTurn = localMyBodyAngleToBall;
#ifdef AGENT_STRATEGY_OUTPUT
			cout << "wm.GetCurrentGameMode()==PM_GOAL_KICK_Opp" << endl;
#endif
		}
		else if (localCurrentGameMode == PM_KickIn_Opp
				|| localCurrentGameMode == PM_CORNER_KICK_Opp)
		{
			destination = standBetweenBallAndMyGoal(2 * CELL_LENGTH);
			theNewWalkSolutions(destination, angleToTurn, topSpeed);
			angleToTurn = localMyBodyAngleToBall;
#ifdef AGENT_STRATEGY_OUTPUT
			cout
					<< "wm.GetCurrentGameMode()==PM_KickIn_Opp||wm.GetCurrentGameMode()==PM_CORNER_KICK_Opp"
					<< endl;
#endif
		}
		else if (localCurrentGameMode == PM_CORNER_KICK_Our)
		{
#ifdef AGENT_STRATEGY_OUTPUT
			cout << "inside PM_CORNER_KICK_Our" << endl;
#endif
			/*
			 if(ball.y()>0)
			 {
			 cout<<"1#"<<endl;
			 if(my.y()<ball.y()+0.1)
			 {
			 cout<<"2#"<<endl;
			 if(my.x()<ball.x())
			 {
			 cout<<"3#"<<endl;
			 destination=Vector3(ball.x()-0.2,ball.y()+0.45,0);
			 }
			 else
			 {
			 cout<<"4#"<<endl;
			 destination=Vector3(ball.x()+0.2,ball.y()+0.45,0);
			 }
			 }
			 else
			 {
			 cout<<"5#"<<endl;
			 destination=Vector3(ball.x(),ball.y()+0.45,0);
			 }
			 }
			 else if(ball.y()<0)
			 {
			 cout<<"6#"<<endl;
			 if(my.y()>ball.y()-0.1)
			 {
			 cout<<"7#"<<endl;
			 if(my.x()<ball.x())
			 {
			 cout<<"8#"<<endl;
			 destination=Vector3(ball.x()-0.2,ball.y()-0.45,0);
			 }
			 else
			 {
			 cout<<"9#"<<endl;
			 destination=Vector3(ball.x()+0.2,ball.y()-0.45,0);
			 }
			 }
			 else
			 {
			 cout<<"0#"<<endl;
			 destination=Vector3(ball.x(),ball.y()-0.45,0);
			 }
			 }
			 */
			destination = ball;
			theNewWalkSolutions(destination, angleToTurn, topSpeed);
			angleToTurn = wm.GetLastCyclesAverageBallGoalToXAxisAngle()
					- wm.GetMyBodyAngleToXAxis();
		}
		else if(wm.GetCurrentGameMode()==PM_KickOff_Our)
		{
			destination = ballCoordinate;
								angleToTurn = localMyBodyAngleToBall;
								topSpeed = MAX_SPEED;
		//	return newWalk.CreateWalkGait(destination, angleToTurn, topSpeed);
								theNewWalkSolutions(destination, angleToTurn, topSpeed);
		}
		else if (wm.GetCurrentGameMode() == PM_KickOff_Opp)
		{
			Vector3 opponentCoordinate = wm.GetNewOpponentCoordinate(
					wm.GetClosestToBallOpponentNumberByVision());
#ifdef AGENT_STRATEGY_OUTPUT
			cout << "opponentNumber:"
					<< wm.GetClosestToBallOpponentNumberByVision()
					<< "   opponentCoordinate:" << opponentCoordinate << endl;
#endif
			if (fabs(2 * opponentCoordinate.y()) < 0.35)
			{
				destination = Vector3(-1.45, -2 * opponentCoordinate.y(), 0);
			}
			else
			{
				if (opponentCoordinate.y() > 0)
					destination = Vector3(-1.45, -0.35, 0);
				else
					destination = Vector3(-1.45, 0.35, 0);
			}

			theNewWalkSolutions(destination, angleToTurn, topSpeed);
			angleToTurn = localMyBodyAngleToBall;
#ifdef AGENT_STRATEGY_OUTPUT
			cout << "wm.GetCurrentGameMode()==PM_KickOff_Opp" << endl;
#endif
		}
		else if(wm.GetCurrentGameMode()==PM_KickIn_Our)
			{
//			stringstream ss("");
//				destination = ball;
//				if(ballCoordinate.y()<0 )
//				{
//					if(ballCoordinate.x()>my.x())
//							{
//				 destination = Vector3(ballCoordinate.x() - 0.3,
//				    	  								ballCoordinate.y() - 0.2, destination.z());
//
//					}
//					else
//					{
//						 destination = Vector3(ballCoordinate.x() +0.3,
//									    	  								ballCoordinate.y() - 0.3, destination.z());
//					}
//				}
//					if(ballCoordinate.y()>0 )
//								{
//									if(ballCoordinate.x()>my.x())
//											{
//								 destination = Vector3(ballCoordinate.x() - 0.3,
//								    	  								ballCoordinate.y() + 0.2, destination.z());
//
//									}
//									else
//									{
//										 destination = Vector3(ballCoordinate.x() -0.2,
//													    	  								ballCoordinate.y() + 0.3, destination.z());
//									}
//								}
//
//				//	destination = HandleBallDestinationForShootBall(
//			//							destinationCoordinate);
//							//theNewWalkSolutions(destination, angleToTurn, topSpeed);
//					       topSpeed=MID_SPEED;
//					       if( wm.GetMyDistanceToBall() >0.6)
//					       {
//					    	   if (fabs(angleToTurn) < 70)
//					    	   							                         	  				{
//					    	   							                         	  					angleToTurn = localMyBodyAngleToBall;
//					    	   							                         	  				}
//					    	   							                         	  				else
//					    	   							                         	  				{
//					    	   							                         	  					angleToTurn = -localMyBodyAngleToXAxis;
//					    	   							                         	  				}
//					    	//   angleToTurn = localMyBodyAngleToBall;
//					       }
//					       else
//							angleToTurn = wm.GetLastCyclesAverageBallGoalToXAxisAngle()
//									- wm.GetMyBodyAngleToXAxis();
//							if( wm.GetMyDistanceToBall() >0.4 || !wm.CanSeeTheBall() )//localMyAngleToBall) > 15 &&
//							return NEWWALK(destination, angleToTurn, topSpeed);
//							else
//								 return behavior.stopAndShoottingbeforekick()  ;
//			if(agent.GetType()==0 && wm.CanSeeTheBall() && wm.GetMyDistanceToBall() <2*CELL_LENGTH
//					&& wm.GetClosestToBallOpponentDistanceByVision()>1.5*CELL_LENGTH &&wm.GetMyAngleToFlag(VO_GOAL2_R ))
			if (wm.GetMyTeamIndex() == TI_LEFT)
			{
			{
					destination = WalkToDestinationCoordinate(
																		destinationCoordinate );
				//	destination = Vector3(destination.x()+0.04 , destination.y() ,	destination.z());
				if(wm.GetMyAngleToDestination(destination)<0.4)
						topSpeed=MID_SPEED;
					//	destination = Vector3(destination.x()+0.05 , destination.y() ,	destination.z());
					//	angleToTurn=(wm.GetMyAngleToFlag(VO_GOAL2_R)+wm.GetMyAngleToFlag(VO_GOAL1_R))/2;
					//	destination=	(	destinationCoordinate.x,destinationCoordinate.y,destinationCoordinate.z );
			//		 if (ball.x()>my.x()  &&(wm.CanSeeTheFlag(VO_GOAL1_R) && wm.CanSeeTheFlag(VO_GOAL2_R)))
				//			 return behavior.stopAndShoottingbeforekick();
						/////////////////////////////////////////////////////////////////////////////////////////////////
						if ((localMyDistanceToBall <= 0.21 && fabs(localMyAngleToBall) < 8   //原来为12  0.24
								&& fabs(localMyAngleToBall) > 0 &&(wm.GetMyAngleToFlag(VO_GOAL1_R)	   )  //&&wm.GetMyAngleToFlag(VO_GOAL2_R)> -25)   //0 -25
								&&ballCoordinate.y() < 0* CELL_LENGTH&& ball.x()>my.x() &&wm.GetMyAngleToFlag(VO_GOAL2_R))
						|| (localMyDistanceToBall <= 0.21 && fabs(localMyAngleToBall) < 8   //原来为12
								&& fabs(localMyAngleToBall) > 0 &&(wm.GetMyAngleToFlag(VO_GOAL2_R)	  )//&&wm.GetMyAngleToFlag(VO_GOAL1_R)<25)  // 0 25
								&&ballCoordinate.y() >  0* CELL_LENGTH&& ball.x()>my.x()&&wm.GetMyAngleToFlag(VO_GOAL1_R))
			//					||
			//					(localMyDistanceToBall <= 0.22 && fabs(localMyAngleToBall) < 10   //原来为12  0.24
			//								&& fabs(localMyAngleToBall) > 0 &&(wm.GetMyAngleToFlag(VO_GOAL2_L)	 < 0&&wm.GetMyAngleToFlag(VO_GOAL2_L)> -100)
			//								&&ballCoordinate.y() < 0* CELL_LENGTH)
			//						|| (localMyDistanceToBall <= 0.22 && fabs(localMyAngleToBall) < 10   //原来为12
			//								&& fabs(localMyAngleToBall) > 0 &&(wm.GetMyAngleToFlag(VO_GOAL1_L)	 >0&&wm.GetMyAngleToFlag(VO_GOAL1_L)<100)
			//								&&ballCoordinate.y() >  0* CELL_LENGTH)
						)
						{
							beginShoot = true;
						}


						if (beginShoot == false)
						{
							if (myRole == ROLE_VANGUARD)
							{
								if (wm.IsTheBallOutOfShootArea())
								{
									initShootControlParameter();
								}

							}
							else
							{
								if (!wm.CanSeeTheBall())
								{
									initShootControlParameter();
								}
								if (localMyDistanceToBall < 0.175)
								{
									initShootControlParameter();
								}
								if (localMyDistanceToBall < 0.2
										&& fabs(localMyAngleToBall) > 35)
								{
									initShootControlParameter();
								}
								if (wm.EstimateWhetherUseHalfWalk() == true)
								{
									initShootControlParameter();
								}
							}
						//return prepareForShootting();
							if ((localMyDistanceToBall <= 0.30 && fabs(localMyAngleToBall) < 10   //原来为12  0.24
																					&& fabs(localMyAngleToBall) > 0 &&(wm.GetMyAngleToFlag(VO_GOAL2_R)	   )  //&&wm.GetMyAngleToFlag(VO_GOAL2_R)> -25)   //0 -25
																					&&ballCoordinate.y() < 0* CELL_LENGTH&& ball.x()>my.x())
																			|| (localMyDistanceToBall <= 0.30 && fabs(localMyAngleToBall) < 10   //原来为12
																					&& fabs(localMyAngleToBall) > 0 &&(wm.GetMyAngleToFlag(VO_GOAL1_R)	  )//&&wm.GetMyAngleToFlag(VO_GOAL1_R)<25)  // 0 25
																					&&ballCoordinate.y() >  0* CELL_LENGTH&& ball.x()>my.x()))
						return prepareShootingForFreeKick();
					//		return HandleBall();
						}
						else
						{
					//		if (localMyDistanceToBall > 0.3
					//				|| fabs(this->localMyBodyAngleToXAxis) > 20)
					//		{
					//			finishKick = true;
					//			initShootControlParameter();
					//		}
							if (gaitStoped == true)
							{
					//			if (timeCounter >= 98)
					//				finishKick = true;

								if (rigthFootShoot)
										return basicMotion.ShootingFromA();
								//	return basicMotion.NexLTest();

								//	return basicMotion.RightFootShootingBallCIT();
										//	rightFootShootingBallCIT();
								else
								//	return basicMotion.LeftFootShootingBallCIT();
							//	return basicMotion.NexRTest();
									return basicMotion.ShootingFromARight();
							}
							else
							{
								if (newWalk.GetWalkCounter() == 7)
								{
									gaitStoped = true;
									basicMotion.SetTimeCounter(0);
									if (localMyAngleToBall > 0)
										rigthFootShoot = false;
									else
										rigthFootShoot = true;
								}
						//		return prepareForShootting();
								if ((localMyDistanceToBall <= 0.30 && fabs(localMyAngleToBall) < 10   //原来为12  0.24
															&& fabs(localMyAngleToBall) > 0 &&(wm.GetMyAngleToFlag(VO_GOAL2_R)	   )  //&&wm.GetMyAngleToFlag(VO_GOAL2_R)> -25)   //0 -25
															&&ballCoordinate.y() < 0* CELL_LENGTH&& ball.x()>my.x())
													|| (localMyDistanceToBall <= 0.30 && fabs(localMyAngleToBall) < 10   //原来为12
															&& fabs(localMyAngleToBall) > 0 &&(wm.GetMyAngleToFlag(VO_GOAL1_R)	  )//&&wm.GetMyAngleToFlag(VO_GOAL1_R)<25)  // 0 25
															&&ballCoordinate.y() >  0* CELL_LENGTH&& ball.x()>my.x()))
							return prepareShootingForFreeKick();
							//	return HandleBall();
							}
						}
			}
			}
			else
			{
//////////////////////////////////////////////////////////////
				{
								destination = WalkToDestinationCoordinate(
																					destinationCoordinate );
							//	destination = Vector3(destination.x()+0.04 , destination.y() ,	destination.z());
							if(wm.GetMyAngleToDestination(destination)<0.4)
									topSpeed=MID_SPEED;
								//	destination = Vector3(destination.x()+0.05 , destination.y() ,	destination.z());
								//	angleToTurn=(wm.GetMyAngleToFlag(VO_GOAL2_R)+wm.GetMyAngleToFlag(VO_GOAL1_R))/2;
								//	destination=	(	destinationCoordinate.x,destinationCoordinate.y,destinationCoordinate.z );
						//		 if (ball.x()>my.x()  &&(wm.CanSeeTheFlag(VO_GOAL1_R) && wm.CanSeeTheFlag(VO_GOAL2_R)))
							//			 return behavior.stopAndShoottingbeforekick();
									/////////////////////////////////////////////////////////////////////////////////////////////////
									if ((localMyDistanceToBall <= 0.21 && fabs(localMyAngleToBall) < 8   //原来为12  0.24
											&& fabs(localMyAngleToBall) > 0 &&(wm.GetMyAngleToFlag(VO_GOAL1_L)	   )  //&&wm.GetMyAngleToFlag(VO_GOAL2_R)> -25)   //0 -25
											&&ballCoordinate.y() < 0* CELL_LENGTH&& ball.x()>my.x() &&wm.GetMyAngleToFlag(VO_GOAL2_L))
									|| (localMyDistanceToBall <= 0.21 && fabs(localMyAngleToBall) < 8   //原来为12
											&& fabs(localMyAngleToBall) > 0 &&(wm.GetMyAngleToFlag(VO_GOAL2_L)	  )//&&wm.GetMyAngleToFlag(VO_GOAL1_R)<25)  // 0 25
											&&ballCoordinate.y() >  0* CELL_LENGTH&& ball.x()>my.x()&&wm.GetMyAngleToFlag(VO_GOAL1_L))
						//					||
						//					(localMyDistanceToBall <= 0.22 && fabs(localMyAngleToBall) < 10   //原来为12  0.24
						//								&& fabs(localMyAngleToBall) > 0 &&(wm.GetMyAngleToFlag(VO_GOAL2_L)	 < 0&&wm.GetMyAngleToFlag(VO_GOAL2_L)> -100)
						//								&&ballCoordinate.y() < 0* CELL_LENGTH)
						//						|| (localMyDistanceToBall <= 0.22 && fabs(localMyAngleToBall) < 10   //原来为12
						//								&& fabs(localMyAngleToBall) > 0 &&(wm.GetMyAngleToFlag(VO_GOAL1_L)	 >0&&wm.GetMyAngleToFlag(VO_GOAL1_L)<100)
						//								&&ballCoordinate.y() >  0* CELL_LENGTH)
									)
									{
										beginShoot = true;
									}


									if (beginShoot == false)
									{
										if (myRole == ROLE_VANGUARD)
										{
											if (wm.IsTheBallOutOfShootArea())
											{
												initShootControlParameter();
											}

										}
										else
										{
											if (!wm.CanSeeTheBall())
											{
												initShootControlParameter();
											}
											if (localMyDistanceToBall < 0.175)
											{
												initShootControlParameter();
											}
											if (localMyDistanceToBall < 0.2
													&& fabs(localMyAngleToBall) > 35)
											{
												initShootControlParameter();
											}
											if (wm.EstimateWhetherUseHalfWalk() == true)
											{
												initShootControlParameter();
											}
										}
									//return prepareForShootting();
										if ((localMyDistanceToBall <= 0.30 && fabs(localMyAngleToBall) < 10   //原来为12  0.24
																								&& fabs(localMyAngleToBall) > 0 &&(wm.GetMyAngleToFlag(VO_GOAL2_L)	   )  //&&wm.GetMyAngleToFlag(VO_GOAL2_R)> -25)   //0 -25
																								&&ballCoordinate.y() < 0* CELL_LENGTH&& ball.x()>my.x())
																						|| (localMyDistanceToBall <= 0.30 && fabs(localMyAngleToBall) < 10   //原来为12
																								&& fabs(localMyAngleToBall) > 0 &&(wm.GetMyAngleToFlag(VO_GOAL1_L)	  )//&&wm.GetMyAngleToFlag(VO_GOAL1_R)<25)  // 0 25
																								&&ballCoordinate.y() >  0* CELL_LENGTH&& ball.x()>my.x()))
									return prepareShootingForFreeKick();
								//		return HandleBall();
									}
									else
									{
								//		if (localMyDistanceToBall > 0.3
								//				|| fabs(this->localMyBodyAngleToXAxis) > 20)
								//		{
								//			finishKick = true;
								//			initShootControlParameter();
								//		}
										if (gaitStoped == true)
										{
								//			if (timeCounter >= 98)
								//				finishKick = true;

											if (rigthFootShoot)
													return basicMotion.ShootingFromA();
											//	return basicMotion.NexLTest();

											//	return basicMotion.RightFootShootingBallCIT();
													//	rightFootShootingBallCIT();
											else
											//	return basicMotion.LeftFootShootingBallCIT();
										//	return basicMotion.NexRTest();
												return basicMotion.ShootingFromARight();
										}
										else
										{
											if (newWalk.GetWalkCounter() == 7)
											{
												gaitStoped = true;
												basicMotion.SetTimeCounter(0);
												if (localMyAngleToBall > 0)
													rigthFootShoot = false;
												else
													rigthFootShoot = true;
											}
									//		return prepareForShootting();
											if ((localMyDistanceToBall <= 0.30 && fabs(localMyAngleToBall) < 10   //原来为12  0.24
																		&& fabs(localMyAngleToBall) > 0 &&(wm.GetMyAngleToFlag(VO_GOAL2_L)	   )  //&&wm.GetMyAngleToFlag(VO_GOAL2_R)> -25)   //0 -25
																		&&ballCoordinate.y() < 0* CELL_LENGTH&& ball.x()>my.x())
																|| (localMyDistanceToBall <= 0.30 && fabs(localMyAngleToBall) < 10   //原来为12
																		&& fabs(localMyAngleToBall) > 0 &&(wm.GetMyAngleToFlag(VO_GOAL1_L)	  )//&&wm.GetMyAngleToFlag(VO_GOAL1_R)<25)  // 0 25
																		&&ballCoordinate.y() >  0* CELL_LENGTH&& ball.x()>my.x()))
										return prepareShootingForFreeKick();
										//	return HandleBall();
										}
									}
						}

///////////////////////////////////////////////////////////
			}
							///////////////////////////////////////////////////////////////////////////////
	//						if(my.x()<ball.x() && my.y()<ball.y())
	//							 return behavior.stopAndShoottingbeforekick()  ;
	//						else
	//							return NEWWALK(destination, angleToTurn, topSpeed);
						//	return ;




			}
		/////////////////////////////////////////////////////////////////////////////////////////////////////////add by gaojin
		int teammateNumber;
		if (wm.WhetherMyTeammatesBlockMe(teammateNumber) == true)
		{
			destinationCoordinate = CalcDestinationIfTeamMateBlockMe(
					destinationCoordinate, teammateNumber);
		}

		/////////////////////////////////////////////////////////////////////////////////////////////////////////add by gaojin

		int OpponentNumber;
		if (wm.WhetherOpponentBlockMe(OpponentNumber))
		{
			destinationCoordinate = CalcDestinationIfOpponentBlockMe(
					destinationCoordinate, OpponentNumber);
		}

	}
#ifdef AGENT_STRATEGY_OUTPUT
	cout << "mycoordinate::" << myCoordinate << endl;
	cout << "ball::" << ball << endl;
	cout << "Vanguard:_________________" << endl;
	cout << "angleToTurn:" << angleToTurn << endl;
	cout << "destination:" << destination << endl;
	cout << "topSpeed:" << topSpeed << endl;
#endif
	//destination=my;
	//angleToTurn=23;
	//topSpeed=MAX_SPEED;

	return NEWWALK(destination, angleToTurn, topSpeed);

}

void Strategy::EstimateSpeedByTurnAngle() ///useless
{
	if (fabs(angleToTurn) > 20)
	{
		moveStrategy = HORIZONMOVE_SPEED_NULL;
		walkDirection = WALK_FORWARD;
		currentCycleSpeedStrategy = SPEED_NULL;
		topSpeed = MIN_SPEED;
	}
}

void Strategy::theNewWalkSolutions(Vector3& destination, float& angleToTurn,
		TopSpeed& topSpeed)
{
	Vector3 destinationCoordinate = destination;
//	Vector3 ballCoordinate = wm.GetLastCyclesAverageBallCoordinate();
//	float disTodes = wm.GetMyDistanceToDestination(destinationCoordinate);
	Vector3 myCoordinate = wm.GetMyCoordinate();
	if (wm.CanSeeTheBall() && wm.CanDoLocalizationDirectly())
	{
		turnHeadStrategy(fallDownTurnHead);

		///	float ballMeToXAxisAngle=wm.GetLastCyclesAverageBallMeToXAxisAngle();
		///	float ballGoalToXAxisAngle=wm.GetLastCyclesAverageBallGoalToXAxisAngle();

		if (wm.GetMyDistanceToDestination(destinationCoordinate) > 2)
		{
			destination = WalkToDestinationCoordinate(destinationCoordinate);
			//angleToTurn = -localMyBodyAngleToXAxis;
		//	angleToTurn = ;
			angleToTurn = localMyBodyAngleToBall;

		}
		else if (wm.GetMyDistanceToDestination(destinationCoordinate) > 1
				&& wm.GetMyDistanceToDestination(destinationCoordinate) <= 2) ///need do some impove
		{
			destination = WalkToDestinationCoordinate(destinationCoordinate);

			angleToTurn = -localMyBodyAngleToXAxis;

		}
		else if (wm.GetMyDistanceToDestination(destinationCoordinate) <= 1)
		{
			destination = WalkToDestinationCoordinate(destinationCoordinate);
			if (myRole == ROLE_VICE_VANGUARD_2 || myRole == ROLE_CENTRE_FORWARD
					|| myRole == ROLE_VICE_CENTRE_FORWARD_1
					|| myRole == ROLE_VICE_CENTRE_FORWARD_2)
			{

				angleToTurn = -localMyBodyAngleToXAxis;

			}
			else
			{

				angleToTurn = 0;
			}
		}

	}
	else if (!wm.CanSeeTheBall() && wm.CanDoLocalizationDirectly())
	{
		turnHeadStrategy(fallDownTurnHead);

		angleToTurn = -localMyBodyAngleToXAxis;

		destination = WalkToDestinationCoordinate(destinationCoordinate);

	}
	else if (wm.CanSeeTheBall() && !wm.CanDoLocalizationDirectly())
	{
		turnHeadStrategy(fallDownTurnHead);
		angleToTurn = -localMyBodyAngleToXAxis;

		destination = WalkToDestinationCoordinate(destinationCoordinate);

	}
	else if (!wm.CanSeeTheBall() && !wm.CanDoLocalizationDirectly())
	{
		turnHeadStrategy(fallDownTurnHead);
		angleToTurn = -localMyBodyAngleToXAxis;

		destination = WalkToDestinationCoordinate(destinationCoordinate);

	}
	if (myCoordinate.x() > destination.x()&&myCoordinate.x() - destination.x()>2*CELL_LENGTH)
	{
		cout<<"trun to destination for Defense"<<endl;
		angleToTurn = wm.GetMyAngleToDestination(destination);
		if(myCoordinate.x()>0)
		{
			topSpeed=MAX_SPEED;
		}
	}
	//避让主将
	Vector3 VanCoordinate=wm.GetNewTeammateCoordinate(CITHear.GetNowVanguardnum());
	Vector3 MyCoord=wm.GetMyCoordinate();
	Vector3 Ball=wm.GetBallCoordinate();
	float VandisToBall=(VanCoordinate-Ball).xymod();
	float MydisToBall=(MyCoord-Ball).xymod();
	if(MydisToBall<2*CELL_LENGTH
			&&wm.GetMyNumber()!=CITHear.GetNowVanguardnum()
			&&VandisToBall<1.5*CELL_LENGTH
			&&((Ball-VanCoordinate)*(Ball-MyCoord))<0
			&&MyCoord.x()>ball.x())
	{
#ifdef AGENT_STRATEGY_OUTPUT
		cout<<"避让主将vanguard"<<endl;
#endif
		destination.x(MyCoord.x());
		destination.y(2*MyCoord.y()-Ball.y()-(((MyCoord.x()-Ball.x())*(Ball.y()-VanCoordinate.y()))/(Ball.x()-VanCoordinate.x())));
	}
#ifdef AGENT_STRATEGY_OUTPUT
		cout << "theNewWalkSolutions_____________------_______________" << endl;
	cout << "topSpeed:         " << topSpeed
			<< "        angleToTurn        :    " << angleToTurn
			<< "   destination:   " << destination << "   myRole: " << myRole
			<< endl;
#endif

}

void Strategy::theWalkSolutions(Vector3& destination, float& angleToTurn,
		TopSpeed& topSpeed)
{
	Vector3 destinationCoordinate = destination;
	Vector3 ballCoordinate = wm.GetLastCyclesAverageBallCoordinate();
	float disTodes = wm.GetMyDistanceToDestination(destinationCoordinate);
///	Vector3 myCoordinate=wm.GetMyCoordinate();
	if (wm.CanSeeTheBall() && wm.CanDoLocalizationDirectly())
	{
		turnHeadStrategy(fallDownTurnHead);

		///	float ballMeToXAxisAngle=wm.GetLastCyclesAverageBallMeToXAxisAngle();
		///	float ballGoalToXAxisAngle=wm.GetLastCyclesAverageBallGoalToXAxisAngle();

		if (wm.GetMyDistanceToDestination(destinationCoordinate) > 5)
		{
			destination = WalkToDestinationCoordinate(destinationCoordinate);
			if (ballCoordinate.x() > 0 && disTodes < CELL_LENGTH)
			{
				angleToTurn = -localMyBodyAngleToXAxis;
			}
			else
			{
				angleToTurn = wm.GetMyAngleToDestination(destinationCoordinate);
			}
		}
		else if (wm.GetMyDistanceToDestination(destinationCoordinate) > 1
				&& wm.GetMyDistanceToDestination(destinationCoordinate) <= 5) ///need do some impove
		{
			destination = WalkToDestinationCoordinate(destinationCoordinate);
			if (ballCoordinate.x() > 0 && disTodes < CELL_LENGTH)
			{
				angleToTurn = -localMyBodyAngleToXAxis;
			}
			else
			{
				angleToTurn = wm.GetMyAngleToDestination(destinationCoordinate);
			}
		}
		else if (wm.GetMyDistanceToDestination(destinationCoordinate) <= 1)
		{
			destination = WalkToDestinationCoordinate(destinationCoordinate);
			if (myRole == ROLE_VICE_VANGUARD_2 || myRole == ROLE_CENTRE_FORWARD
					|| myRole == ROLE_VICE_CENTRE_FORWARD_1
					|| myRole == ROLE_VICE_CENTRE_FORWARD_2)
			{
				if (ballCoordinate.x() > 0 && disTodes < CELL_LENGTH)
				{
					angleToTurn = -localMyBodyAngleToXAxis;
				}
				else
				{
					angleToTurn = wm.GetMyAngleToDestination(
							destinationCoordinate);
				}
			}
			else
			{
				if (ballCoordinate.x() > 0)
				{
					angleToTurn = 0;
				}
				else
				{
					angleToTurn = wm.GetMyAngleToDestination(
							destinationCoordinate);
				}
			}
		}

	}
	else if (!wm.CanSeeTheBall() && wm.CanDoLocalizationDirectly())
	{
		turnHeadStrategy(fallDownTurnHead);
		if (ballCoordinate.x() > 0 && disTodes < CELL_LENGTH)
		{
			angleToTurn = -localMyBodyAngleToXAxis;
		}
		else
		{
			angleToTurn = wm.GetMyAngleToDestination(destinationCoordinate);
		}
		destination = WalkToDestinationCoordinate(destinationCoordinate);

	}
	else if (wm.CanSeeTheBall() && !wm.CanDoLocalizationDirectly())
	{
		turnHeadStrategy(fallDownTurnHead);
		if (ballCoordinate.x() > 0 && disTodes < CELL_LENGTH)
		{
			angleToTurn = -localMyBodyAngleToXAxis;
		}
		else
		{
			angleToTurn = wm.GetMyAngleToDestination(destinationCoordinate);
		}

		destination = WalkToDestinationCoordinate(destinationCoordinate);

	}
	else if (!wm.CanSeeTheBall() && !wm.CanDoLocalizationDirectly())
	{
		turnHeadStrategy(fallDownTurnHead);
		if (ballCoordinate.x() > 0 && disTodes < CELL_LENGTH)
		{
			angleToTurn = -localMyBodyAngleToXAxis;
		}
		else
		{
			angleToTurn = wm.GetMyAngleToDestination(destinationCoordinate);
		}

		destination = WalkToDestinationCoordinate(destinationCoordinate);

	}
#ifdef AGENT_STRATEGY_OUTPUT
	cout << "theNewWalkSolutions_____________------_______________" << endl;
	cout << "topSpeed:         " << topSpeed
			<< "        angleToTurn        :    " << angleToTurn
			<< "   destination:   " << destination << "   myRole: " << myRole
			<< endl;
#endif

}
Vector3 Strategy::WalkToDestinationCoordinate(Vector3 destination)
{

	Vector3 ballCoordinate = destination;
	Vector3 destinationCoordinate;

	int mDisToBallIndex;

	wm.GetMyDistanceToBallSortedIndex(mDisToBallIndex);

	if (myRole == ROLE_VANGUARD || (mDisToBallIndex == 1&&myRole<ROLE_LINEBACKER))
	{
//		if(ball.x()>-3*CELL_LENGTH)
		{
			float a, b, c, l, K, B, x0, y0, x2, x, y, mid, L;
#ifdef AGENT_STRATEGY_OUTPUT
			cout << "wm.GetClosestToBallOpponentNumberByVision:"
					<< localClosestToBallOpponentNumberByVision << endl;
			cout << "wm.GetClosestToBallOpponentDistanceByVision:"
					<< localClosestToBallOpponentDistanceByVision << endl;

			cout << "wm.GetLastCyclesAverageBallMeXDifference:"
					<< localLastCyclesAverageBallMeXDifference << endl;
			cout << "wm.GetLastCyclesAverageBallMeYDifference:"
					<< localLastCyclesAverageBallMeYDifference << endl;
			cout << "wm.GetFieldLength():" << localFieldLength
					<< " wm.GetFieldWidth():  " << localFieldWidth << endl;
#endif
			if (localLastCyclesAverageBallMeXDifference < 0

					&& wm.GetClosestToBallOpponentDistanceByVision()
					< 1 * CELL_LENGTH)
			{
				l = 0.7;
			}
			else
			{
				l = 0.25;
			}
#ifdef AGENT_STRATEGY_OUTPUT
			cout << "l:" << l << endl;
#endif
			///	l=0.3;
			x0 = ballCoordinate.x();
			y0 = ballCoordinate.y();
			L = localFieldLength / 2;

			K = (y0) / (x0 - L);
			B = y0 - K * x0;

			a = (L - x0) * (L - x0) + y0 * y0;
			b = -2 * L * y0 * y0 - 2 * x0 * (L - x0) * (L - x0)
							+ 2 * (L - x0) * y0 * y0;
			c = L * L * y0 * y0 + x0 * x0 * (L - x0) * (L - x0)
							+ y0 * y0 * (L - x0) * (L - x0) - 2 * L * y0 * y0 * (L - x0)
							- (L - x0) * (L - x0) * l * l;
#ifdef AGENT_STRATEGY_OUTPUT
			cout << "a:" << a << "  b: " << b << "  c:  " << c
					<< "  (b*b-4*a*c):  " << (b * b - 4 * a * c) << " L:" << L
					<< endl;
			cout << "K:" << K << "  B: " << B << endl;
#endif
			mid = (b * b - 4 * a * c);

			if (mid < 0.01) ///to avoid nan
			{
				mid = 0;
			}
			//float x1;
			//			x1 = (-b + sqrt(mid)) / 2 / a;
			x2 = (-b - sqrt(mid)) / 2 / a;


			x = x2;
			y = K * x + B;
#ifdef AGENT_STRATEGY_OUTPUT
			cout << "my team index is LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL"
					<< endl;
#endif
			if (myCoordinate.x() > ballCoordinate.x())
			{
				if (localMyDistanceToBall < 0.8 * CELL_LENGTH) ///&&wm.GetMyDistanceToBall()>0.2*CELL_LENGTH)
				{
					if (myCoordinate.y() - ballCoordinate.y() > 0.3)
					{
						if (y < ball.y() + 0.3)
						{
							y = ball.y() + 0.3;
						}
#ifdef AGENT_STRATEGY_OUTPUT
						cout << "To the Middle Destination  1A" << endl;
#endif
					}
					else if (myCoordinate.y() - ballCoordinate.y() < -0.3)
					{
						if (y > ball.y() - 0.3)
						{
							y = ball.y() - 0.3;
						}
#ifdef AGENT_STRATEGY_OUTPUT
						cout << "To the Middle Destination  2A" << endl;
#endif
					}
					else
					{

						if (myCoordinate.y() > ballCoordinate.y())
						{
							y = myCoordinate.y() + 0.45;
#ifdef AGENT_STRATEGY_OUTPUT
							cout << "To the Middle Destination  3A" << endl;
#endif
						}
						else
						{
#ifdef AGENT_STRATEGY_OUTPUT
							cout << "To the Middle Destination  4A" << endl;
#endif
							y = myCoordinate.y() - 0.45;
						}

					}
				}

			}



			destinationCoordinate = Vector3(x, y, 0);
			//cout <<"here is destination:::"<<destinationCoordinate<<endl;


			////////////////////////////////add by gaojin
			int OpponentNumber;
			if (wm.WhetherOpponentBlockMe(OpponentNumber))
			{
				destinationCoordinate = CalcDestinationIfOpponentBlockMe(
						destinationCoordinate, OpponentNumber);
			}
			///////////////////////////////////////////////////////////////
		}
//		else
//		{
//			destinationCoordinate=wm.GetBallCoordinate();
//		}
	}
	else ///myRole!=ROLE_VANGUARD
	{
		destinationCoordinate = destination;

		int teammateNumber;

//		cout
//				<< "0000000000000000000000000000000000000wm.GetDestinationMeToXAxisAngle():"
//				<< wm.GetDestinationMeToXAxisAngle(destination)
//				<< " destination:" << destination << endl;

		if (wm.WhetherMyTeammatesBlockMe(teammateNumber) == true)
		{

			destinationCoordinate = CalcDestinationIfTeamMateBlockMe(
					destinationCoordinate, teammateNumber);
		}

		/////////////////////////////////////////////////////////////////////////////////////////////////////////add by gaojin

		int OpponentNumber;
		if (wm.WhetherOpponentBlockMe(OpponentNumber))
		{
			destinationCoordinate = CalcDestinationIfOpponentBlockMe(
					destinationCoordinate, OpponentNumber);
		}
	}
#ifdef AGENT_STRATEGY_OUTPUT
	cout << "ballCoordinate:       " << wm.GetBallCoordinate() << "==" << endl;
	cout << " destinationCoordinate:	" << destinationCoordinate << endl;
	cout << "wm.AverageMyCoordinate() :" << myCoordinate << "==" << myCoordinate
			<< endl;
#endif
	float distanceToDestination;
	distanceToDestination = wm.GetMyDistanceToDestination(
			destinationCoordinate);
// 0.66 .03
	if (distanceToDestination >= 0.5)
	{
		topSpeed = MAX_SPEED;
#ifdef AGENT_STRATEGY_OUTPUT
		cout << "6666666666" << endl;
#endif
	}
	else if (distanceToDestination < 0.5 && distanceToDestination > 0.2)
	{
		topSpeed = MID_SPEED;
#ifdef AGENT_STRATEGY_OUTPUT
		cout << "7777777771111111" << endl;
#endif
	}
	else if (distanceToDestination <= 0.2 && distanceToDestination > 0.1)
	{
		topSpeed = MIDMIN_SPEED;
#ifdef AGENT_STRATEGY_OUTPUT
		cout << "7777777772222222" << endl;
#endif
	}
	else if (distanceToDestination <= 0.1)
	{
		topSpeed = MIN_SPEED;
#ifdef AGENT_STRATEGY_OUTPUT
		cout << "8888888" << endl;
#endif
	}
#ifdef AGENT_STRATEGY_OUTPUT
	cout << "999999999999distanceToDestination:     " << distanceToDestination
			<< endl;
#endif
	return destinationCoordinate;

}

Vector3 Strategy::HandleBallGoalongwithOneOfTwoLine(Vector3 destination) ///
{
	Vector3 ballCoordinate = destination;

	Vector3 myCoordinate = wm.GetMyCoordinate();

	float localFieldLength = wm.GetFieldLength();
	float localFieldWidth = wm.GetFieldWidth();
	float localMyDistanceToBall = wm.GetMyDistanceToBall();

	Vector3 destinationTwo;

	Vector3 BallLastCycleCoordinate = ballCoordinate;

	float l, K, B, x0, y0, x1, y1, x2, y2,  L, W;

	float DistanceOfBallToPoint;

	Vector3 Destination, TemPoint;
	float localLastCyclesAverageBallMeXDifference =
			wm.GetLastCyclesAverageBallMeXDifference();
	if (localLastCyclesAverageBallMeXDifference < 0
			&& wm.GetClosestToBallOpponentDistanceByVision() < 1 * CELL_LENGTH)
	{
		l = 0.7;
	}
	else
	{
		l = 0.25;
	}

	L = localFieldLength / 2;
	W = localFieldWidth / 2;

	if (ballCoordinate.y() >= 0)
	{
		TemPoint = Vector3(L, W - CELL_LENGTH,0);
		//cout << "TemPoint one__ " << TemPoint << endl;
	}
	else
	{
		TemPoint = Vector3(L, -(W - CELL_LENGTH), 0);
		//cout << "TemPoint two__ " << TemPoint << endl;
	}

	x0 = TemPoint.x();
	y0 = TemPoint.y();

	x1 = ballCoordinate.x();
	y1 = ballCoordinate.y();

	DistanceOfBallToPoint = sqrt((x0 - x1) * (x0 - x1) + (y0 - y1) * (y0 - y1));

#if 1
	if (x0 == x1)
	{
		destinationTwo=Vector3(x1,y1,0);
	}
	else
	{

		float D = l * fabs(x0 - x1) / DistanceOfBallToPoint;
		//cout << "here is line area D" << D << endl;
		K = (y0 - y1) / (x0 - x1);
		//cout << "here is line area K" << K << endl;
		B = y0 - K * x0;
		//cout << "here is line area B" << B << endl;
		if (x1 < x0) ///球的坐标小于我设定的目标点的坐标
		{
			if (myCoordinate.x() < x1)
			{
				x2 = x1 + D;
				y2 = K * x2 + B;
				//cout << "here is mycoordinate.x()<ball.x()" << x2 << y2 << endl;
			}
			else
			{
				x2 = x1 - D;
				y2 = K * x2 + B;
				if (localMyDistanceToBall < 0.8 * CELL_LENGTH) ///&&wm.GetMyDistanceToBall()>0.2*CELL_LENGTH)
				{
					if (myCoordinate.y() - ballCoordinate.y() > 0.3)
					{
						if (y2 < BallLastCycleCoordinate.y() + 0.3)
						{
							//cout << "destination case1:::::" << endl;
							y2 = BallLastCycleCoordinate.y() + 0.3;
						}
					}
					else if (myCoordinate.y() - ballCoordinate.y() < -0.3)
					{
						if (y2 > BallLastCycleCoordinate.y() - 0.3)
						{
							y2 = BallLastCycleCoordinate.y() - 0.3;
							//cout << "destination case2::::" << endl;
						}
					}
					else
					{

						if (myCoordinate.y() > ballCoordinate.y())
						{
							y2 = myCoordinate.y() - 0.45;
							//cout << "destination case3:::" << endl;
						}
						else
						{
							y2 = myCoordinate.y() + 0.45;
							//cout << "destination case4:::" << endl;
						}
					}
				}
			} ///end of else
		}
		destinationTwo = Vector3(x2, y2, 0);
	}



	////////////////////////////////add by gaojin
	int OpponentNumber;
	if (wm.WhetherOpponentBlockMe(OpponentNumber))
	{
		destinationTwo = CalcDestinationIfOpponentBlockMe(destinationTwo,
				OpponentNumber);
	}

#endif
	float distanceToDestination;
	distanceToDestination = wm.GetMyDistanceToDestination(destinationTwo);

	if (distanceToDestination >= 0.66)
	{
		topSpeed = MAX_SPEED;
#ifdef AGENT_STRATEGY_OUTPUT
		cout << "6666666666" << endl;
#endif
	}
	else if (distanceToDestination < 0.66 && distanceToDestination > 0.3)
	{
		topSpeed = MID_SPEED;
#ifdef AGENT_STRATEGY_OUTPUT
		cout << "7777777771111111" << endl;
#endif
	}
	else if (distanceToDestination <= 0.3 && distanceToDestination > 0.1)
	{
		topSpeed = MIDMIN_SPEED;
#ifdef AGENT_STRATEGY_OUTPUT
		cout << "7777777772222222" << endl;
#endif
	}
	else if (distanceToDestination <= 0.1)
	{
		topSpeed = MIN_SPEED;
#ifdef AGENT_STRATEGY_OUTPUT
		cout << "8888888" << endl;
#endif
	}

	//cout << "here is mycoordinate" << myCoordinate << endl;
	//cout << "here is destination in go with two line" << destinationTwo << endl;
	//cout << "here is ballCoordinate" << ballCoordinate << endl;

	return destinationTwo;
}

Vector3 Strategy::HandleBallDestinationForShootBall(Vector3 destination) ///以最佳射门点为最终目标点
{

	Vector3 ballCoordinate = destination;
	float localFieldLength = wm.GetFieldLength();
	Vector3 myCoordinate = wm.GetMyCoordinate();

	float localMyDistanceToBall = wm.GetMyDistanceToBall();

	Vector3 BallLastCycleCoordinate = ballCoordinate;

	float a, b, c, l, K, B, x0, y0, x1, y1, x2, y2, mid, L;

	float DistanceOfBallToPoint;

	Vector3 destinationcoordinate;
	float localLastCyclesAverageBallMeXDifference =
			wm.GetLastCyclesAverageBallMeXDifference();
	if (localLastCyclesAverageBallMeXDifference < 0
			&& wm.GetClosestToBallOpponentDistanceByVision() < 1 * CELL_LENGTH)
	{
		l = 0.7;
	}
	else
	{
		l = 0.25;
	}

	L = localFieldLength / 2;

	Vector3 TemPoint; ///根据情况定
	//////////////基于论文：《《基于最大角的足球机器人贪心射门算法》》Author:蔡国武,刘祚时,罗爱华

	int cloestToBallOpponentNumber =
			wm.GetClosestToBallOpponentNumberByVision();
	Vector3 cloestToBallOpponentCoordinate = wm.GetNewOpponentCoordinate(
			cloestToBallOpponentNumber);
	if (fabs(cloestToBallOpponentCoordinate.y()) < 1.0 * CELL_LENGTH)
	{
		float ballDistanceToGole_one_Rignt, ballDistanceToGole_Two_Rignt;
		float cloestToBallOpponentDistanceToGole_one_Rignt,
				cloestToBallOpponentDistanceToGole_Two_Rignt;
		float ballDistanceToCloestToBallOpponent;
		float goleWidth = wm.GetGoalWidth();

		const Vector3 gole_one_Coordinate = Vector3(L, goleWidth, 0);
		const Vector3 gole_Two_Coordinate = Vector3(L, -goleWidth, 0);

		ballDistanceToGole_one_Rignt = wm.GetDistanceBetweenTwoCoordinate(
				ballCoordinate, gole_one_Coordinate);

		ballDistanceToGole_Two_Rignt = wm.GetDistanceBetweenTwoCoordinate(
				ballCoordinate, gole_Two_Coordinate);

		ballDistanceToCloestToBallOpponent = wm.GetDistanceBetweenTwoCoordinate(
				ballCoordinate, cloestToBallOpponentCoordinate);

		cloestToBallOpponentDistanceToGole_one_Rignt =
				wm.GetDistanceBetweenTwoCoordinate(
						cloestToBallOpponentCoordinate, gole_one_Coordinate);

		cloestToBallOpponentDistanceToGole_Two_Rignt =
				wm.GetDistanceBetweenTwoCoordinate(
						cloestToBallOpponentCoordinate, gole_Two_Coordinate);

		float angle_1, angle_2;

		angle_1 = acos(
				((ballDistanceToGole_one_Rignt * ballDistanceToGole_one_Rignt)
						+ (ballDistanceToCloestToBallOpponent
								* ballDistanceToCloestToBallOpponent)
						- (cloestToBallOpponentDistanceToGole_one_Rignt
								* cloestToBallOpponentDistanceToGole_one_Rignt))
						/ (2 * ballDistanceToGole_one_Rignt
								* ballDistanceToCloestToBallOpponent));

		angle_2 = acos(
				((ballDistanceToGole_Two_Rignt * ballDistanceToGole_Two_Rignt)
						+ (ballDistanceToCloestToBallOpponent
								* ballDistanceToCloestToBallOpponent)
						- (cloestToBallOpponentDistanceToGole_Two_Rignt
								* cloestToBallOpponentDistanceToGole_Two_Rignt))
						/ (2 * ballDistanceToGole_Two_Rignt
								* ballDistanceToCloestToBallOpponent));

		if (angle_1 >= angle_2)
		{
			TemPoint = Vector3((L + gole_one_Coordinate.x()) / 2,
					gole_one_Coordinate.y() / 2, 0);
		}
		else
		{
			TemPoint = Vector3(L + gole_Two_Coordinate.x() / 2,
					gole_Two_Coordinate.y() / 2, 0);
		}

	}
	else
	{
		TemPoint = Vector3(localFieldLength, 0, 0);
	}

	x0 = TemPoint.x();
	y0 = TemPoint.y();

	x1 = ballCoordinate.x();
	y1 = ballCoordinate.y();

	DistanceOfBallToPoint = sqrt((x0 - x1) * (x0 - x1) + (y0 - y1) * (y0 - y1));

#if 1
	if (x0 == x1)
	{
		x2 = x1;
		y2 = y1;
	}
	else
	{

		float D = l * fabs(x0 - x1) / DistanceOfBallToPoint;

		K = (y0 - y1) / (x0 - x1);
		B = y0 - K * x0;

		if (x1 < x0) ///球的坐标小于我设定的目标点的坐标
		{
			if (myCoordinate.x() < x1) ///1
			{
				x2 = x1 + D;
				y2 = K * x2 + B;
			} ///end 1
			else ///6
			{
				x2 = x1 - D;
				y2 = K * x2 + B;
				if (localMyDistanceToBall < 0.8 * CELL_LENGTH) ///5	///&&wm.GetMyDistanceToBall()>0.2*CELL_LENGTH)
				{
					if (myCoordinate.y() - ballCoordinate.y() > 0.3) ///2
					{
						if (y2 < BallLastCycleCoordinate.y() + 0.3)
						{
							//cout << "destination case1:::::" <<endl;
							y2 = BallLastCycleCoordinate.y() + 0.3;
						}
					} ///end 2
					else if (myCoordinate.y() - ballCoordinate.y() < -0.3) ///3
					{
						if (y2 > BallLastCycleCoordinate.y() - 0.3)
						{
							y2 = BallLastCycleCoordinate.y() - 0.3;
							//cout << "destination case2::::" <<endl;
						}
					} ///end 3
					else ///4
					{

						if (myCoordinate.y() > ballCoordinate.y())
						{
							y2 = myCoordinate.y() - 0.45;
							//cout << "destination case3:::" <<endl;
						}
						else
						{
							y2 = myCoordinate.y() + 0.45;
							//cout << "destination case4:::" <<endl;
						}
					} ///end 4
				} ///end 5
			} ///end 6
		}
		else /// 超过目标点
		{
			const float PenaltyWidth = 3.9;
			if (ballCoordinate.x() < x1
					&& fabs(ballCoordinate.y()) <= PenaltyWidth / 2)
			{

				K = (y1) / (x1 - L); ///球和球门中点的斜率
				B = y1 - K * x1;

				a = (L - x1) * (L - x1) + y1 * y1;
				b = -2 * L * y1 * y1 - 2 * x1 * (L - x1) * (L - x1)
						+ 2 * (L - x1) * y1 * y1;
				c = L * L * y1 * y1 + x1 * x1 * (L - x1) * (L - x1)
						+ y1 * y1 * (L - x1) * (L - x1)
						- 2 * L * y1 * y1 * (L - x1)
						- (L - x1) * (L - x1) * l * l;
				mid = (b * b - 4 * a * c);
				if (mid < 0.01) ///to avoid nan
				{
					mid = 0;
				}

				//x1=(-b+sqrt(mid))/2/a;
				x2 = (-b - sqrt(mid)) / 2 / a;

				//x=x2;
				y2 = K * x2 + B;
			}
			else
			{
				x2 = x1 - D;
				y2 = K * x2 + B;
				if (localMyDistanceToBall < 0.8 * CELL_LENGTH) ///&&wm.GetMyDistanceToBall()>0.2*CELL_LENGTH)
				{
					if (myCoordinate.y() - ballCoordinate.y() > 0.3)
					{
						if (y2 < BallLastCycleCoordinate.y() + 0.3)
						{
							//cout << "destination case1:::::" << endl;
							y2 = BallLastCycleCoordinate.y() + 0.3;
						}
					}
					else if (myCoordinate.y() - ballCoordinate.y() < -0.3)
					{
						if (y2 > BallLastCycleCoordinate.y() - 0.3)
						{
							y2 = BallLastCycleCoordinate.y() - 0.3;
							//cout << "destination case2::::" << endl;
						}
					}
					else
					{

						if (myCoordinate.y() > ballCoordinate.y())
						{
							y2 = myCoordinate.y() - 0.45;
							//cout << "destination case3:::" << endl;
						}
						else
						{
							y2 = myCoordinate.y() - 0.45;
							//cout << "destination case4:::" << endl;
						}
					}
				} ///end of if
			}
		}
	}
#endif

	destinationcoordinate = Vector3(x2, y2, 0);
	//cout << "here is handleball N_two" << destinationcoordinate << endl;

	////////////////////////////////add by gaojin
	int OpponentNumber;
	if (wm.WhetherOpponentBlockMe(OpponentNumber))
	{
		destinationcoordinate = CalcDestinationIfOpponentBlockMe(
				destinationcoordinate, OpponentNumber);
	}

	float distanceToDestination;
	distanceToDestination = wm.GetMyDistanceToDestination(
			destinationcoordinate);
//0.66  0.3
	if (distanceToDestination >= 0.5)
	{
		topSpeed = MAX_SPEED;
#ifdef AGENT_STRATEGY_OUTPUT
		cout << "6666666666" << endl;
#endif
	}
	else if (distanceToDestination < 0.5 && distanceToDestination > 0.2)
	{
		topSpeed = MID_SPEED;
#ifdef AGENT_STRATEGY_OUTPUT
		cout << "7777777771111111" << endl;
#endif
	}
	else if (distanceToDestination <= 0.2)
	{
		topSpeed = MIN_SPEED;
	}
	/*else if(distanceToDestination<=0.3&&distanceToDestination>0.1)
	 {
	 topSpeed=MIDMIN_SPEED;
	 cout<<"7777777772222222"<<endl;
	 }
	 else if(distanceToDestination<=0.1)
	 {
	 topSpeed=MIN_SPEED;
	 cout<<"8888888"<<endl;
	 }*/
	return destinationcoordinate;
}

/*Vector3 Strategy::SetHandleBallDestinateon(Vector3 destination) ///设置大于球的目标点
{

	Vector3 ballCoordinate = destination;
	float localFieldLength = wm.GetFieldLength();
	Vector3 myCoordinate = wm.GetMyCoordinate();

	float localMyDistanceToBall = wm.GetMyDistanceToBall();

	Vector3 BallLastCycleCoordinate = ballCoordinate;

	float a, b, c, l, K, B, x0, y0, x1, y1, x2, y2, mid, L;

	float DistanceOfBallToPoint;

	Vector3 destinationcoordinate;
	float localLastCyclesAverageBallMeXDifference =
			wm.GetLastCyclesAverageBallMeXDifference();
	if (localLastCyclesAverageBallMeXDifference < 0
			&& wm.GetClosestToBallOpponentDistanceByVision() < 1 * CELL_LENGTH)
	{
		l = 0.7;
	}
	else
	{
		l = 0.25;
	}

	L = localFieldLength / 2;

	Vector3 TemPoint = destination;

	x0 = TemPoint.x();
	y0 = TemPoint.y();

	x1 = ballCoordinate.x();
	y1 = ballCoordinate.y();

	DistanceOfBallToPoint = sqrt((x0 - x1) * (x0 - x1) + (y0 - y1) * (y0 - y1));

#if 1
	if (x0 == x1)
	{
		x2 = x1;
		y2 = y1;
	}
	else
	{
		float D = l * fabs(x0 - x1) / DistanceOfBallToPoint;
		K = (y0 - y1) / (x0 - x1);
		B = y0 - K * x0;
		if (x1 < x0) ///球的坐标小于我设定的目标点的坐标
		{
			if (myCoordinate.x() < x1) ///1
			{
				x2 = x1 + D;
				y2 = K * x2 + B;
			} ///end 1
			else ///6
			{
				x2 = x1 - D;
				y2 = K * x2 + B;
				if (localMyDistanceToBall < 0.8 * CELL_LENGTH) ///5	///&&wm.GetMyDistanceToBall()>0.2*CELL_LENGTH)
				{
					if (myCoordinate.y() - ballCoordinate.y() > 0.3) ///2
					{
						if (y2 < BallLastCycleCoordinate.y() + 0.3)
						{
							//cout << "destination case1:::::" <<endl;
							y2 = BallLastCycleCoordinate.y() + 0.3;
						}
					} ///end 2
					else if (myCoordinate.y() - ballCoordinate.y() < -0.3) ///3
					{
						if (y2 > BallLastCycleCoordinate.y() - 0.3)
						{
							y2 = BallLastCycleCoordinate.y() - 0.3;
							//cout << "destination case2::::" <<endl;
						}
					} ///end 3
					else ///4
					{

						if (myCoordinate.y() > ballCoordinate.y())
						{
							y2 = myCoordinate.y() - 0.45;
							//cout << "destination case3:::" <<endl;
						}
						else
						{
							y2 = myCoordinate.y() + 0.45;
							//cout << "destination case4:::" <<endl;
						}
					} ///end 4
				} ///end 5
			} ///end 6
		}
		else /// 超过目标点
		{
			float PenaltyWidth = wm.GetPenaltyWidth();
			if (ballCoordinate.x() < x1
					&& fabs(ballCoordinate.y()) <= PenaltyWidth / 2)
			{

				K = (y1) / (x1 - L); ///球和球门中点的斜率
				B = y1 - K * x1;
				a = (L - x1) * (L - x1) + y1 * y1;
				b = -2 * L * y1 * y1 - 2 * x1 * (L - x1) * (L - x1)
						+ 2 * (L - x1) * y1 * y1;
				c = L * L * y1 * y1 + x1 * x1 * (L - x1) * (L - x1)
						+ y1 * y1 * (L - x1) * (L - x1)
						- 2 * L * y1 * y1 * (L - x1)
						- (L - x1) * (L - x1) * l * l;
				mid = (b * b - 4 * a * c);
				if (mid < 0.01) ///to avoid nan
				{
					mid = 0;
				}

				//x1=(-b+sqrt(mid))/2/a;
				x2 = (-b - sqrt(mid)) / 2 / a;

				//x=x2;
				y2 = K * x2 + B;
			}
			else
			{
				x2 = x1 - D;
				y2 = K * x2 + B;
				if (localMyDistanceToBall < 0.8 * CELL_LENGTH) ///&&wm.GetMyDistanceToBall()>0.2*CELL_LENGTH)
				{
					if (myCoordinate.y() - ballCoordinate.y() > 0.3)
					{
						if (y2 < BallLastCycleCoordinate.y() + 0.3)
						{
							//cout << "destination case1:::::" << endl;
							y2 = BallLastCycleCoordinate.y() + 0.3;
						}
					}
					else if (myCoordinate.y() - ballCoordinate.y() < -0.3)
					{
						if (y2 > BallLastCycleCoordinate.y() - 0.3)
						{
							y2 = BallLastCycleCoordinate.y() - 0.3;
							//cout << "destination case2::::" << endl;
						}
					}
					else
					{
						if (myCoordinate.y() > ballCoordinate.y())
						{
							y2 = myCoordinate.y() - 0.45;
							//cout << "destination case3:::" << endl;
						}
						else
						{
							y2 = myCoordinate.y() - 0.45;
							//cout << "destination case4:::" << endl;
						}
					}
				} ///end of if
			}
		}
	}
#endif

	destinationcoordinate = Vector3(x2, y2, 0);
	//cout << "here is handleball N_two" << destinationcoordinate << endl;

	////////////////////////////////add by gaojin
	int OpponentNumber;
	if (wm.WhetherOpponentBlockMe(OpponentNumber))
	{
		destinationcoordinate = CalcDestinationIfOpponentBlockMe(
				destinationcoordinate, OpponentNumber);
	}

	float distanceToDestination;
	distanceToDestination = wm.GetMyDistanceToDestination(
			destinationcoordinate);

	if (distanceToDestination >= 0.66)
	{
		topSpeed = MAX_SPEED;
		cout << "6666666666" << endl;
	}
	else if (distanceToDestination < 0.66 && distanceToDestination > 0.3)
	{
		topSpeed = MID_SPEED;
		cout << "7777777771111111" << endl;
	}
	else if (distanceToDestination <= 0.3 && distanceToDestination > 0.1)
	{
		topSpeed = MIDMIN_SPEED;
		cout << "7777777772222222" << endl;
	}
	else if (distanceToDestination <= 0.1)
	{
		topSpeed = MIN_SPEED;
		cout << "8888888" << endl;
	}
	return destinationcoordinate;
}*/

Action Strategy::NEWWALK(Vector3& destination, float& angleToTurn,
		TopSpeed& topSpeed)
{
	Vector3 Mycoordinate = wm.GetMyCoordinate();
	if (myRole == ROLE_VANGUARD)
	{
//		float BallMeAndXAxis = wm.GetAngleBetweenBallMeAndXAxis();
//		if ((Mycoordinate - wm.GetBallCoordinate()).xymod() > 1.5 * CELL_LENGTH
//				&& (BallMeAndXAxis > 45 || BallMeAndXAxis < -45))
//		{
//			cout << "change bodyangle to des" << endl;
//			angleToTurn = wm.GetMyAngleToBall();
//		}
	}
	else
	{
		float DesMeAndXAxis =CITMath::GetTwoPointWithXangle(wm.GetMyCoordinate(),destination);
			if ((Mycoordinate - destination).xymod() > 1.5 * CELL_LENGTH
					&& (DesMeAndXAxis > 45 || DesMeAndXAxis < -45))
			{
#ifdef AGENT_STRATEGY_OUTPUT
				cout << "change bodyangle to des" << endl;
#endif
				angleToTurn = wm.GetMyAngleToDestination(destination);
			}
	}
	if (fabs(angleToTurn) >30)
	{
#ifdef AGENT_STRATEGY_OUTPUT
		cout << "angleToTurn::" << angleToTurn << endl;
		cout << "need deal with angleToTurn!" << endl;
		angleToTurn = (fabs(angleToTurn) / angleToTurn) * 40;
		cout << "angleToTurn::" << angleToTurn << endl;
#endif
	}
	if (CITConf.DrawerBug)
	{
		if(wm.GetMyNumber()!=0)
		{
			string n1 = wm.GetMyTeamName()+"Form.Run." + Convert::ToString(wm.GetMyNumber());
			RGBDraw rgb(0.4, 0.5, 0.6);
#ifdef AGENT_STRATEGY_OUTPUT
			cout << "n1-------::" << n1 << endl;
#endif
			CITMDrawer.drawLine(destination,wm.GetMyCoordinate(), 1, rgb, &n1);
			CITMDrawer.UpdateDrawer(&n1);
		}
	}
	return newWalk.CreateWalkGait(destination, angleToTurn, topSpeed);
}

/**          lr           */
float Strategy::CalculateMyDistanceToDestination(Vector3 myCoordinate,
		Vector3 destination)
{
	float distance = sqrt(
			(myCoordinate.x() - destination.x())
					* (myCoordinate.x() - destination.x())
					+ (myCoordinate.y() - destination.y())
							* (myCoordinate.y() - destination.y()));
	return distance;
}

/**         feng          */

bool Strategy::EstimateCanShoot() //if the player can prepare for shooting
{

	if (wm.GetMyDistanceToBall() < 0.3 && newWalk.GetFootLength() > 0.1)
	{
		return false;
	}
	if (!wm.CanSeeTheBall())
	{
		return false;
	}
	if (fabs(wm.GetMyBodyAngleToBall()) < 15 && whetherCanShoot())
	{
		if (wm.GetMyDistanceToBall() < 0.8)
		{
			if (wm.GetMyAngleToBall() > 0)
				leftShootDistance = true;
			else
				leftShootDistance = false;
			return true;
		}
		else
			return false;
	}
	else
		return false;

}

//Action Strategy::stopAndShoottingbeforekick() //sop for shooting
//{
//#ifdef AGENT_STRATEGY_OUTPUT
//	cout << "stopAndShootting" << endl;
//#endif
//	if (beginShoot == true)
//	{
//		//cout << "beginShoot==true" << endl;
//	}
//	else
//	{
//	//	cout << "beginShoot==false" << endl;
//	}
//	if (wm.GetMyDistanceToBall() <= 0.172 && fabs(wm.GetMyAngleToBall()) < 22    //原来为12
//			&& fabs(wm.GetMyAngleToBall()) > 5)
//	{
//		if (myRole == ROLE_VANGUARD)
//		{
//			if (wm.GetMyTeamIndex() == TI_LEFT)
//			{
//			//	if (wm.GetMyAngleToFlag(VO_GOAL1_R)
//				//		* wm.GetMyAngleToFlag(VO_GOAL2_R) < 0) //&&wm.WhetherCanPassFront())
//				//{
//					beginShoot = true;
//#ifdef AGENT_STRATEGY_OUTPUT
//				//	cout << "1" << endl;
//#endif
//				//}
//				//else
//				//{
//				//	beginShoot = false;
//#ifdef AGENT_STRATEGY_OUTPUT
//				//	cout << "2" << endl;
//#endif
//				//}
//			}
//			else
//			{
//				if (wm.GetMyAngleToFlag(VO_GOAL1_L)
//						* wm.GetMyAngleToFlag(VO_GOAL2_L) < 0)
//				{
//					beginShoot = true;
//#ifdef AGENT_STRATEGY_OUTPUT
//					cout << "3" << endl;
//#endif
//				}
//				else
//				{
//					beginShoot = false;
//#ifdef AGENT_STRATEGY_OUTPUT
//					cout << "4" << endl;
//#endif
//				}
//			}
//		}
//		else
//		{
//			beginShoot = true;
//		}
//	}
//
//	if (beginShoot == false)
//	{
//		if (myRole == ROLE_VANGUARD)
//		{
//#ifdef AGENT_STRATEGY_OUTPUT
//			cout << "a" << endl;
//#endif
//			if (wm.IsTheBallOutOfShootArea())
//			{
//#ifdef AGENT_STRATEGY_OUTPUT
//				cout << "b" << endl;
//#endif
//				initShootControlParameter();
//			}
//
//		}
//		else
//		{
//#ifdef AGENT_STRATEGY_OUTPUT
//			cout << "e" << endl;
//#endif
//			if (!wm.CanSeeTheBall())
//			{
//				initShootControlParameter();
//			}
//			if (wm.GetMyDistanceToBall() < 0.135)
//			{
//				initShootControlParameter();
//			}
//			if (wm.GetMyDistanceToBall() < 0.2
//					&& fabs(wm.GetMyBodyAngleToBall()) > 35)
//			{
//				initShootControlParameter();
//			}
//			if (wm.EstimateWhetherUseHalfWalk() == true)
//			{
//				initShootControlParameter();
//			}
//		}
//		return prepareForShootting();
//	}
//	else
//	{
//		if (gaitStoped == true)
//		{
//			if (basicMotion.GetTimeCounter() == 80)
//			{
//				initShootControlParameter();
//			}
//			if (rigthFootShoot == true)
//				return basicMotion.RightFootShootingBall();
//			else
//				return basicMotion.LeftFootShootingBall();
//		}
//		else
//		{
//			if (newWalk.GetWalkCounter() == 7)
//			{
//				gaitStoped = true;
//				basicMotion.SetTimeCounter(0);
/////				newWalk.beginShoot=true;
//				if (wm.GetMyAngleToBall() > 0)
//					rigthFootShoot = false;
//				else
//					rigthFootShoot = true;
//#ifdef AGENT_STRATEGY_OUTPUT
//				cout << "time =" << wm.GetCurrentGameTime()
//						<< "        do shoot!!! dis" << wm.GetMyDistanceToBall()
//						<< "my angle to ball:" << wm.GetMyAngleToBall() << endl;
//#endif
//				if (wm.GetMyDistanceToBall() > 0.19)
//				{
//					initShootControlParameter();
//				}
//			}
//			return prepareForShootting();
//		}
//	}
//}



////////////////////////////////////////////////////////////////////////////////////////////////


Action Strategy::stopAndShoottingbeforekick() //sop for shooting
{//	&& fabs(localMyAngleToBall) > 0 &&(wm.GetMyAngleToFlag(VO_GOAL1_R)	* wm.GetMyAngleToFlag(VO_GOAL2_R) < 0)
	//fabs(ballCoordinate.y()) < 4 * CELL_LENGTH
	stringstream ss("");
	Vector3 my=wm.GetMyCoordinate();
//	if(localMyDistanceToBall <= 1 && localMyDistanceToBall >0.4)
//		return prepareForShootting();
				Vector3 ball=wm.GetLastCyclesAverageBallCoordinate();
				if(wm.GetMyDistanceToBall() <=0.8 && (ball.x() <my.x())&& (fabs(my.y()) < fabs(ball.y()) + 0.1))
				{
			//		return behavior.MainStrategy();
				}
			//	else{
				if ((localMyDistanceToBall <= 0.22 && fabs(localMyAngleToBall) < 110   //原来为12  0.24  //type 5 13
							&& fabs(localMyAngleToBall) > 0 &&(wm.GetMyAngleToFlag(VO_GOAL2_R)	 < 0&&wm.GetMyAngleToFlag(VO_GOAL2_R)> -40)
							&&ballCoordinate.y() < 0* CELL_LENGTH)
					|| (localMyDistanceToBall <= 0.22 && fabs(localMyAngleToBall) < 10   //原来为12
							&& fabs(localMyAngleToBall) > 0 &&(wm.GetMyAngleToFlag(VO_GOAL1_R)	 >0&&wm.GetMyAngleToFlag(VO_GOAL1_R)<40)
							&&ballCoordinate.y() >  0* CELL_LENGTH)
							||
							( localMyDistanceToBall <= 0.22 && fabs(localMyAngleToBall) < 10   //原来为12  0.24
									&& fabs(localMyAngleToBall) > 0 && (wm.GetCurrentGameMode()==PM_GOAL_KICK_Our)
									)
									||
									(wm.GetMyAngleToFlag(VO_GOAL2_R)&& localMyDistanceToBall <= 0.22  &&wm.GetCurrentGameMode()==PM_KickOff_Our )
									||
									(wm.GetMyAngleToFlag(VO_GOAL2_L)&& localMyDistanceToBall <= 0.22  &&wm.GetCurrentGameMode()==PM_KickOff_Our )
					)
	{
		beginShoot = true;
	}


	if (beginShoot == false)
	{
		if (myRole == ROLE_VANGUARD)
		{
			if (wm.IsTheBallOutOfShootArea())
			{
				initShootControlParameter();
			}

		}
		else
		{
			if (!wm.CanSeeTheBall())
			{
				initShootControlParameter();
			}
			if (localMyDistanceToBall < 0.175)
			{
				initShootControlParameter();
			}
			if (localMyDistanceToBall < 0.2
					&& fabs(localMyAngleToBall) > 35)
			{
				initShootControlParameter();
			}
			if (wm.EstimateWhetherUseHalfWalk() == true)
			{
				initShootControlParameter();
			}
		}
	//	return prepareForShootting();
		return prepareShootingForFreeKick();
//		return HandleBall();
	}
	else
	{
//		if (localMyDistanceToBall > 0.3
//				|| fabs(this->localMyBodyAngleToXAxis) > 20)
//		{
//			finishKick = true;
//			initShootControlParameter();
//		}
		if (gaitStoped == true)
		{
//			if (timeCounter >= 98)
//				finishKick = true;

			if (rigthFootShoot)
			{
			//	return basicMotion.RoboCansLefttoRight();
				return basicMotion.RoboCansRighttoLeft();
		//	return basicMotion.RoboCansLefttoRight4();
		//	return basicMotion.NexLTest();
			//	return basicMotion.ShootingFromA();
			//	return basicMotion.RightFootShootingBallCIT();
					//	rightFootShootingBallCIT();
			//	return basicMotion.RightFootShootingBallFromUT();
		}
			else
			{
			//	return basicMotion.RoboCansRighttoLeft();
				return basicMotion.RoboCansLefttoRight();

			//	return basicMotion.RoboCansRighttoLeft4();
			//	return basicMotion.LeftFootShootingBallCIT();
		//	return basicMotion.NexRTest();
	//		return basicMotion.ShootingFromARight();
		//		return basicMotion.LeftShootingFromNexus3D();
	//			return basicMotion.LeftFootShootingBallFromUT();
			}
		}
		else
		{
			if (newWalk.GetWalkCounter() == 7)
			{
				gaitStoped = true;
				basicMotion.SetTimeCounter(0);
				if (localMyAngleToBall > 0)
					rigthFootShoot = false;
				else
					rigthFootShoot = true;
			}
		//	return prepareForShootting();
		return prepareShootingForFreeKick();
		//	return HandleBall();
		}
	}
}
Action Strategy::stopAndShootting() //sop for shooting
{
#ifdef AGENT_STRATEGY_OUTPUT
	cout << "stopAndShootting" << endl;
#endif
	if (beginShoot == true)
	{
		//cout << "beginShoot==true" << endl;
	}
	else
	{
	//	cout << "beginShoot==false" << endl;
	}
	if (wm.GetMyDistanceToBall() <= 0.172 && fabs(wm.GetMyAngleToBall()) < 22    //原来为12
			&& fabs(wm.GetMyAngleToBall()) > 5)
	{
		if (myRole == ROLE_VANGUARD)
		{
			if (wm.GetMyTeamIndex() == TI_LEFT)
			{
				if (wm.GetMyAngleToFlag(VO_GOAL1_R)
						* wm.GetMyAngleToFlag(VO_GOAL2_R) < 0) //&&wm.WhetherCanPassFront())
				{
					beginShoot = true;
#ifdef AGENT_STRATEGY_OUTPUT
					cout << "1" << endl;
#endif
				}
				else
				{
					beginShoot = false;
#ifdef AGENT_STRATEGY_OUTPUT
					cout << "2" << endl;
#endif
				}
			}
			else
			{
				if (wm.GetMyAngleToFlag(VO_GOAL1_L)
						* wm.GetMyAngleToFlag(VO_GOAL2_L) < 0)
				{
					beginShoot = true;
#ifdef AGENT_STRATEGY_OUTPUT
					cout << "3" << endl;
#endif
				}
				else
				{
					beginShoot = false;
#ifdef AGENT_STRATEGY_OUTPUT
					cout << "4" << endl;
#endif
				}
			}
		}
		else
		{
			beginShoot = true;
		}
	}

	if (beginShoot == false)
	{
		if (myRole == ROLE_VANGUARD)
		{
#ifdef AGENT_STRATEGY_OUTPUT
			cout << "a" << endl;
#endif
			if (wm.IsTheBallOutOfShootArea())
			{
#ifdef AGENT_STRATEGY_OUTPUT
				cout << "b" << endl;
#endif
				initShootControlParameter();
			}

		}
		else
		{
#ifdef AGENT_STRATEGY_OUTPUT
			cout << "e" << endl;
#endif
			if (!wm.CanSeeTheBall())
			{
				initShootControlParameter();
			}
			if (wm.GetMyDistanceToBall() < 0.135)
			{
				initShootControlParameter();
			}
			if (wm.GetMyDistanceToBall() < 0.2
					&& fabs(wm.GetMyBodyAngleToBall()) > 35)
			{
				initShootControlParameter();
			}
			if (wm.EstimateWhetherUseHalfWalk() == true)
			{
				initShootControlParameter();
			}
		}
		return prepareForShootting();
	}
	else
	{
		if (gaitStoped == true)
		{
			if (basicMotion.GetTimeCounter() == 80)
			{
				initShootControlParameter();
			}
			if (rigthFootShoot == true)
				return basicMotion.RightFootShootingBall();
			else
				return basicMotion.LeftFootShootingBall();
		}
		else
		{
			if (newWalk.GetWalkCounter() == 7)
			{
				gaitStoped = true;
				basicMotion.SetTimeCounter(0);
///				newWalk.beginShoot=true;
				if (wm.GetMyAngleToBall() > 0)
					rigthFootShoot = false;
				else
					rigthFootShoot = true;
#ifdef AGENT_STRATEGY_OUTPUT
				cout << "time =" << wm.GetCurrentGameTime()
						<< "        do shoot!!! dis" << wm.GetMyDistanceToBall()
						<< "my angle to ball:" << wm.GetMyAngleToBall() << endl;
#endif
				if (wm.GetMyDistanceToBall() > 0.19)
				{
					initShootControlParameter();
				}
			}
			return prepareForShootting();
		}
	}
}

Action Strategy::prepareShootingForFreeKick()
{
#ifdef AGENT_STRATEGY_OUTPUT
	cout << "prepareForShootting" << endl;
#endif
	if (leftShootDistance == true) //two kinds prepare
		return newWalk.PrepareForFreeKick(1);
	//	return newWalk.PrePareForShoot(1);
	else
		return newWalk.PrepareForFreeKick(-1);
		//return newWalk.PrePareForShoot(-1);
}

Action Strategy::prepareForShootting() //adjust my position for shooting
{
#ifdef AGENT_STRATEGY_OUTPUT
	cout << "prepareForShootting" << endl;
#endif
	if (leftShootDistance == true) //two kinds prepare
		return newWalk.PrePareForShoot(1);
	else
		return newWalk.PrePareForShoot(-1);
}
void Strategy::initShootControlParameter()
{
	////cout<<"initShootControlParameter"<<endl;
	prepareShoot = false;
	finishShoot = true;
	beginShoot = false;
	gaitStoped = false;
	if (myRole == ROLE_GOALIE)
	{
		initSplits();
	}
}

bool Strategy::centreForwardEstimateCanShoot()
{
	if (wm.GetMyDistanceToBall() < 0.3 && newWalk.GetFootLength() > 0.1)
	{
		return false;
	}
	if (fabs(wm.GetMyBodyAngleToBall()) < 10)
	{
		if (centreForwardWhetherCanShoot())
		{
			if (wm.GetMyDistanceToBall() < 0.4)
				shortShootDistance = true;
			else
				shortShootDistance = false;
			return true;
		}
		else
		{
			return false;
		}
	}
	else
		return false;
}

void Strategy::turnHeadStrategy(float fallDownTurnHead)
{
//  Vector3 my=wm.GetMyCoordinate();
//  Vector3 ball=wm.GetLastCyclesAverageBallCoordinate();
	//float myAngleToDestination=wm.GetMyAngleToDestination(ball);
#ifdef AGENT_STRATEGY_OUTPUT
	cout << "wm.GetMyAngleToBall():" << localMyAngleToBall << endl;
	cout << "wm.GetCurrentJointAngle(JID_HEAD_1)"
			<< localCurrentJointAngleJID_HEAD_1 << " newk.HedAng():   "
			<< localLastCyclesAverageTurnHeadAngle << endl;
#endif
	float myHeadAngle = localLastCyclesAverageTurnHeadAngle;

	if (CITstandup.GetfallDownTurnHeadToFindTwoflags() == false)
	{
		if (wm.CanSeeTheBall() && wm.CanDoLocalizationDirectly())
		{
			seeObjectChange = 1;
#ifdef AGENT_STRATEGY_OUTPUT
			cout
					<< "AAAAwm.CanSeeTheBall()&&wm.CanDoLocalizationByTwoFlags()orOneFlag"
					<< endl;
#endif

//	myHeadAngle=wm.GetCurrentJointAngle(JID_HEAD_1);

			if (myRole == ROLE_VANGUARD)
			{
				if (localMyDistanceToBall > 0.65 * CELL_LENGTH)
				{
					if (turnHeadRight == true)
					{
						//	headAngle+=30;
						//	turnHeadAngle
						newWalk.SetTurnHeadAngle(-120);
#ifdef AGENT_STRATEGY_OUTPUT
						cout << "turn head rightRRRRRRRRRRRRRRRRRRRRRRR"
								<< endl;
#endif
						turnHeadRightChanged = false;

						if (localMyAngleToBall > 10)
						{
							turnHeadRight = false;
							turnHeadRightChanged = true;
							///	turnHeadMax=true;
						}

					}
					else if (turnHeadRight == false)
					{
						//	headAngle-=30;
						//	newWalk.SetTurnHeadAngle(120);
						//	fallDownTurnHead=120;
						newWalk.SetTurnHeadAngle(120);
#ifdef AGENT_STRATEGY_OUTPUT
						cout << "turn head leftLLLLLLLLLLLLLLLLLLLLLLLLL"
								<< endl;
#endif
						turnHeadRightChanged = false;

						if (localMyAngleToBall < -10)
						{
							turnHeadRight = true;

							turnHeadRightChanged = true;

							///	turnHeadMax=true;
						}
					}
				}
				else if (localMyDistanceToBall <= 0.8 * CELL_LENGTH)
				{
					turnHeadRightChanged = true;
					newWalk.SetTurnHeadAngle(myHeadAngle + localMyAngleToBall);
				}
			}
			else
			{
				turnHeadRightChanged = true;
				newWalk.SetTurnHeadAngle(myHeadAngle + localMyAngleToBall);
			}
//	newWalk.SetTurnHeadAngle(90);

///	fallDownTurnHead=myHeadAngle+wm.GetMyAngleToBall();

		}
		else if (!wm.CanSeeTheBall() && wm.CanDoLocalizationDirectly())
		{
#ifdef AGENT_STRATEGY_OUTPUT
			cout << "BBBB   !wm.CanSeeTheBall()&&wm.CanDoLocalizationByFlag()"
					<< endl;
#endif
			if (seeObjectChange != 2 && turnHeadMax == false)
			{
				if (turnHeadRight == true)
				{
					turnHeadRight = false;
					turnHeadRightChanged = true;
				}
				else if (turnHeadRight == false)
				{
					turnHeadRight = true;
					turnHeadRightChanged = true;
				}

			}
			else
			{
				turnHeadMax = false;
#ifdef AGENT_STRATEGY_OUTPUT
				cout << "101010101010101!!!GetCurrentJointAngle(JID_HEAD_1)"
						<< localCurrentJointAngleJID_HEAD_1 << endl;
#endif
				if (turnHeadRight == true)
				{
					//	headAngle+=30;
					newWalk.SetTurnHeadAngle(-120);
					fallDownTurnHead = -120;
#ifdef AGENT_STRATEGY_OUTPUT
					cout << "turn head rightRRRRRRRRRRRRRRRRRRRRRRR" << endl;
#endif
					turnHeadRightChanged = false;

					if (localCurrentJointAngleJID_HEAD_1 < -119)
					{
						turnHeadRight = false;
						turnHeadMax = true;
						turnHeadRightChanged = true;
					}

				}
				else if (turnHeadRight == false)
				{
					//	headAngle-=30;
					newWalk.SetTurnHeadAngle(120);
					fallDownTurnHead = 120;
#ifdef AGENT_STRATEGY_OUTPUT
					cout << "turn head leftLLLLLLLLLLLLLLLLLLLLLLLLL" << endl;
#endif
					turnHeadRightChanged = false;

					if (localCurrentJointAngleJID_HEAD_1 > 119)
					{
						turnHeadRight = true;
						turnHeadMax = true;
						turnHeadRightChanged = true;
					}
				}
			}
			seeObjectChange = 2;
		}
		else if (wm.CanSeeTheBall() && !wm.CanDoLocalizationDirectly())
		{
#ifdef AGENT_STRATEGY_OUTPUT
			cout << "CCCC  wm.CanSeeTheBall()&&!wm.CanDoLocalizationByFlag()"
					<< endl;

			cout << "wm.GetLocalizationFlag_1():"
					<< wm.GetLastCycleLocalizationFlag() << " turnHeadRight: "
					<< turnHeadRight << "my.y():" << my.y() << endl;
#endif
			if ((((wm.GetLastCycleLocalizationFlag() == VO_GOAL1_L
					|| wm.GetLastCycleLocalizationFlag() == VO_GOAL2_R)
					&& turnHeadRight == false)
					|| ((wm.GetLastCycleLocalizationFlag() == VO_GOAL2_L
							|| wm.GetLastCycleLocalizationFlag() == VO_GOAL1_R)
							&& turnHeadRight == true))
					&& fabs(my.y()) < 0.9 * CELL_LENGTH)
			{
#ifdef AGENT_STRATEGY_OUTPUT
				cout << "focus on the ball" << endl;
#endif
				newWalk.SetTurnHeadAngle(myHeadAngle + localMyAngleToBall);
			}
			else
			{
#ifdef AGENT_STRATEGY_OUTPUT
				cout << "turnHeadRightChanged=true" << endl;
#endif
				if (seeObjectChange != 3 && turnHeadMax == false)
				{

					if (fabs(localMyBodyAngleToXAxis) <= 90)
					{
						if (my.y() > 0)
						{
							turnHeadRight = true;
							turnHeadRightChanged = true;
						}
						else if (my.y() <= 0)
						{
							turnHeadRight = false;
							turnHeadRightChanged = true;
						}
					}
					else if (fabs(localMyBodyAngleToXAxis) > 90)
					{
						if (my.y() > 0)
						{
							turnHeadRight = false;
							turnHeadRightChanged = true;
						}
						else if (my.y() <= 0)
						{
							turnHeadRight = true;
							turnHeadRightChanged = true;
						}
					}

				}
				else
				{
					turnHeadMax = false;

					if (turnHeadRight == true)
					{
						//	headAngle+=30;
						newWalk.SetTurnHeadAngle(-120);
						fallDownTurnHead = -120;
#ifdef AGENT_STRATEGY_OUTPUT
						cout << "turn head rightRRRRRRRRRRRRRRRRRRRRRRR"
								<< endl;
#endif
						///	turnHeadRightChanged=false;

						if (localCurrentJointAngleJID_HEAD_1 < -119)
						{
							turnHeadRight = false;
							turnHeadMax = true;
							turnHeadRightChanged = true;
						}
					}
					else if (turnHeadRight == false)
					{
						//	headAngle-=30;
						newWalk.SetTurnHeadAngle(120);
						fallDownTurnHead = 120;
#ifdef AGENT_STRATEGY_OUTPUT
						cout << "turn head leftLLLLLLLLLLLLLLLLLLLLLLLLL"
								<< endl;
#endif
						///	turnHeadRightChanged=false;

						if (localCurrentJointAngleJID_HEAD_1 > 119)
						{
							turnHeadRight = true;
							turnHeadMax = true;
							turnHeadRightChanged = true;
						}
					}
				}
				seeObjectChange = 3;
			}

		}
		else if (!wm.CanSeeTheBall() && !wm.CanDoLocalizationDirectly())
		{
// 	if(seeObjectChange!=4)
//  	{
//  	  if(turnHeadRight==true)
//  	  {
//  	      turnHeadRight=false;
//  	  }
//  	  else if(turnHeadRight==false)
//  	  {
//  	   turnHeadRight=true;
//  	  }
//
//  	}
// 	else
			{
//				cout
//						<< "DDDD   !wm.CanSeeTheBall()&& ! wm.CanDoLocalizationByFlag()"
//						<< endl;

				if (turnHeadRight == true)
				{
					//	headAngle+=30;
					newWalk.SetTurnHeadAngle(-120);
					fallDownTurnHead = -120;
#ifdef AGENT_STRATEGY_OUTPUT
					cout << "turn head rightRRRRRRRRRRRRRRRRRRRRRRR" << endl;
#endif
					turnHeadRightChanged = false;

					if (localCurrentJointAngleJID_HEAD_1 < -119)
					{
						turnHeadRight = false;
						turnHeadMax = true;
						turnHeadRightChanged = true;
					}
				}
				else if (turnHeadRight == false)
				{
					//	headAngle-=30;
					newWalk.SetTurnHeadAngle(120);
					fallDownTurnHead = 120;
#ifdef AGENT_STRATEGY_OUTPUT
					cout << "turn head leftLLLLLLLLLLLLLLLLLLLLLLLLL" << endl;
#endif
					turnHeadRightChanged = false;

					if (localCurrentJointAngleJID_HEAD_1 > 119)
					{
						turnHeadRight = true;
						turnHeadMax = true;
						turnHeadRightChanged = true;
					}
				}

			}
///	seeObjectChange=4;

		}
	}
	else if (CITstandup.GetfallDownTurnHeadToFindTwoflags() == true)
	{
#ifdef AGENT_STRATEGY_OUTPUT
		cout << "fallDownTurnHeadToFindTwoflags" << endl;
#endif
		if (turnHeadRight == true)
		{
			newWalk.SetTurnHeadAngle(-120);
			fallDownTurnHead = -120;
#ifdef AGENT_STRATEGY_OUTPUT
			cout << "turn head rightRRRRRRRRRRRRRRRRRRRRRRR" << endl;
#endif
			turnHeadRightChanged = false;

			if (localCurrentJointAngleJID_HEAD_1 < -119)
			{
				turnHeadRight = false;
				turnHeadRightChanged = true;
			}
		}
		else if (turnHeadRight == false)
		{
			newWalk.SetTurnHeadAngle(120);
			fallDownTurnHead = 120;
#ifdef AGENT_STRATEGY_OUTPUT
			cout << "turn head leftLLLLLLLLLLLLLLLLLLLLLLLLL" << endl;
#endif
			turnHeadRightChanged = false;

			if (localCurrentJointAngleJID_HEAD_1 > 119)
			{
				turnHeadRight = true;
				turnHeadRightChanged = true;
			}
		}

		if (wm.CanDoLocalizationByTwoFlags())
		{
			CITstandup.SetfallDownTurnHeadToFindTwoflags(false);
		}
	}

}

Action Strategy::GoalieAction()
{
//	if(wm.GetCurrentGameMode()==PM_GOAL_KICK_Our)
//{
////	if( (my.x()<ball.x()  && wm.CanSeeTheFlag(VO_GOAL2_R) &&wm.GetMyDistanceToBall()<0.5 && fabs(wm.GetMyBodyAngleToBall())<12&&wm.CanSeeTheBall()) ||  (my.x()<ball.x()  && wm.CanSeeTheFlag(VO_GOAL1_R) &&wm.GetMyDistanceToBall()<0.5 && fabs(wm.GetMyBodyAngleToBall())<25&&wm.CanSeeTheBall())
////			|| (wm.CanSeeTheFlag(LI_GOAL_R) && my.x()<ball.x()&&wm.GetMyDistanceToBall()<0.5 && fabs(wm.GetMyBodyAngleToBall())<12&&wm.CanSeeTheBall()) )      // wm.CanSeeMyOwnGoal() &&
//		if(my.x()<ball.x() && fabs(wm.GetMyBodyAngleToBall()<12))
//	{
//		return behavior.stopAndShoottingbeforekick();
//	}
////	else
////	{
////if(my.y()>ball.y())
////{
////	 destination = Vector3(ballCoordinate.x() -0.2,
////									    	  								ballCoordinate.y() + 0.2, destination.z());
////}
////else
////	destination = Vector3(ballCoordinate.x() -0.2,
////										    	  								ballCoordinate.y() - 0.2, destination.z());
////
////	}
////topSpeed=MID_SPEED;
////angleToTurn = localMyBodyAngleToBall;
////return NEWWALK(destination, angleToTurn, topSpeed);
//	return goForwardToSaveBall();
//
//}
	if (CITConf.GoailDrawer)
	{
		if(wm.GetMyNumber()==1)
		{
			string n1 = wm.GetMyTeamName()+"Goail.Coordinate." + Convert::ToString(wm.GetMyNumber());
			RGBDraw rgb(0.4, 0.5, 0.9);
			CITMDrawer.drawLine(wm.GetMyCoordinate(),wm.GetBallCoordinate(), 3, rgb, &n1);
			CITMDrawer.UpdateDrawer(&n1);
		}
	}
	if (wm.CanSeeTheBall())
	{
		myDistanceToBall = wm.GetMyDistanceToBall();
		if (recordDistanceCounter == 0)
		{
			recordDistanceCounter++;
		}
		else
		{
			distanceToBall[recordDistanceCounter - 1] = myDistanceToBall;
			recordDistanceCounter++;
			if (recordDistanceCounter == 13)
				recordDistanceCounter = 1;
		}
		if (recordDistanceCounter == 1)
		{
			theSpeedOfBall = distanceToBall[0] - distanceToBall[11];
		}
		else
		{
			theSpeedOfBall = distanceToBall[recordDistanceCounter - 1]
					- distanceToBall[recordDistanceCounter - 2];
		}
		////cout<<"time :"<<wm.GetCurrentGameTime()<<"    the speed of the ball  ="<<theSpeedOfBall<<endl;
		if (fabs(theSpeedOfBall) < 0.015)
		{
			beginShootAngle = wm.GetMyAngleToBall()
					+ wm.GetMyHeadAngleToXAxis();
			// beginShootDistance=wm.GetMyDistanceToBall();
			//beginShootPos=ballCoordinate;
			// ////cout<<"*************************************ball stoped the opp will shoot!!! beginShootAngle:"<<beginShootAngle<<"	beginShootDistance:"<<beginShootDistance<<endl;
			//////cout<<"*************************************ball stoped the opp will shoot!!!"<<beginShootPos<<endl;
		}
	}
	else
	{
		if (getDownToSaveBall)
		{
			return splitsToSaveBall();
		}
		return goForwardToSaveBall();
	}
	if (getDownToSaveBall)
	{
		return splitsToSaveBall();
	}
	if (wm.GetCurrentGameMode() == PM_PlayOn && goalieClearBall == false)
	{
		int oppNumber = 0;
		for (TPlayerSenseMap::iterator iter =
				messageParser.mOpponentSenseMap.begin();
				iter != messageParser.mOpponentSenseMap.end(); ++iter)
				{
			if ((*iter).second.head.distance != 0)
			{
#ifdef AGENT_STRATEGY_OUTPUT
				cout << "oppNumber :" << oppNumber << endl;
#endif
				oppNumber++;
			}
		}
		if (oppNumber == 1)
			Penalty_Kick = true;
		else
			Penalty_Kick = false;
		goalieClearBall = true;
	}
#ifdef AGENT_STRATEGY_OUTPUT
	cout<<"Penalty_Kick::"<<Penalty_Kick<<endl;
#endif
	Vector3 Goalcenter=Vector3(-wm.GetFieldLength()/2,0,0);
#ifdef AGENT_STRATEGY_OUTPUT
	cout<<"wm.GetMyCoordinate()"<<wm.GetMyCoordinate()<<endl;
	cout<<"wm.GetLastCyclesAverageBallCoordinate()::"<<wm.GetLastCyclesAverageBallCoordinate()<<endl;
#endif
	float GoailCenterdisToball=(Goalcenter-wm.GetLastCyclesAverageBallCoordinate()).xymod();
#ifdef AGENT_STRATEGY_OUTPUT
	cout<<"GoailCenterdisToball::"<<GoailCenterdisToball<<endl;
#endif
	if(GoailCenterdisToball>GOAL_HALFLENGTH)
	{
#ifdef AGENT_STRATEGY_OUTPUT
		cout<<"disToball>GOAL_HALFLENGTH"<<endl;
#endif
		destination=Vector3Linelength(ballCoordinate,Goalcenter,GOAL_HALFLENGTH,false);
	}
#ifdef AGENT_STRATEGY_OUTPUT
	cout<<"theSpeedOfBall::"<<theSpeedOfBall<<endl;
#endif
	 if (wm.GetMyDistanceToBall() < 2.1 * CELL_LENGTH&&theSpeedOfBall > 0.4)
	 {
		 float changeAngle = wm.GetMyAngleToBall()
									+ wm.GetMyHeadAngleToXAxis() - beginShootAngle;
		 if (changeAngle > 2)
		 {
			 if (newWalk.WhichFootRaised() == -1)
			 {
#ifdef AGENT_STRATEGY_OUTPUT
				 cout << "888" << endl;
#endif
				 getDownToSaveBall = true;
			 }
		 }
		 else if (changeAngle < -2)
		 {
			 if (newWalk.WhichFootRaised() == 1)
			 {
#ifdef AGENT_STRATEGY_OUTPUT
				 cout << "9999" << endl;
#endif
				 getDownToSaveBall = true;
			 }
		 }
		 else
		 {
			 if (newWalk.GetWalkCounter() == 0)
			 {
#ifdef AGENT_STRATEGY_OUTPUT
				 cout << "AAA" << endl;
#endif
				 getDownToSaveBall = true;
				 smallAngleSplit = true;
			 }
		 }
	 }
#ifdef AGENT_STRATEGY_OUTPUT
	 cout<<"wm.GetMyDistanceToBall()::"<<wm.GetMyDistanceToBall()<<endl;
	 cout<<"wm.WhetherMyTeammatesBlockMe()::"<<wm.WhetherMyTeammatesBlockMe()<<endl;
#endif
	if((GoailCenterdisToball<2*GOAL_HALFLENGTH ||(wm.GetMyDistanceToBall()<1.3*GOAL_HALFLENGTH&&!wm.WhetherMyTeammatesBlockMe()))&&!getDownToSaveBall)
//if(((GoailCenterdisToball<2*GOAL_HALFLENGTH && wm.GetClosestToBallOpponentDistanceByVision() > 1 * CELL_LENGTH) ||((wm.GetMyDistanceToBall()<1.3*GOAL_HALFLENGTH&&!wm.WhetherMyTeammatesBlockMe()&& wm.GetClosestToBallOpponentDistanceByVision() > 1.3)))&&!getDownToSaveBall)
	{
#ifdef AGENT_STRATEGY_OUTPUT
		cout<<"disToball<1.4*GOAL_HALFLENGTH----goForwardToSaveBall"<<endl;
#endif
		return goForwardToSaveBall();
	}

	if (CITConf.GoailDrawer)
	{
		if(wm.GetMyNumber()==1)
		{
			string n1 = wm.GetMyTeamName()+"Goail.destination" + Convert::ToString(wm.GetMyNumber());
			RGBDraw rgb(0, 0.5, 1);
			CITMDrawer.drawPoint(destination, 3, rgb, &n1);
			CITMDrawer.UpdateDrawer(&n1);
		}
	}
	float disTodes=(destination-wm.GetMyCoordinate()).xymod();
	if(disTodes<=2*GOAL_HALFLENGTH)
	{
#ifdef AGENT_STRATEGY_OUTPUT
		cout<<"wm.GetMyBodyAngleToBall();"<<endl;
#endif
		angleToTurn = wm.GetMyBodyAngleToBall();
	}
	else
	{
#ifdef AGENT_STRATEGY_OUTPUT
		cout<<"wm.GetMyAngleToDestination(destination);"<<endl;
#endif
		angleToTurn=wm.GetMyAngleToDestination(destination);
	}
	newWalk.SetTurnHeadAngle(
				wm.GetMyAngleToBall()
						+ messageParser.mHingeJointSenseMap[JID_HEAD_1].angle);
#ifdef AGENT_STRATEGY_OUTPUT
	cout<<"topSpeed"<<topSpeed<<endl;
#endif

	if(disTodes>0.2*GOAL_HALFLENGTH&&disTodes<2.2*GOAL_HALFLENGTH)
	{
		topSpeed=MIDMIN_SPEED;
	}
	else if(disTodes<=0.2*GOAL_HALFLENGTH)
	{
		topSpeed=MIN_SPEED;
	}
	else if(disTodes<4*GOAL_HALFLENGTH&&disTodes>=2.2*GOAL_HALFLENGTH)
	{
		topSpeed=MID_SPEED;
	}
	else if(disTodes>=4*GOAL_HALFLENGTH)
	{
		topSpeed=MAX_SPEED;
	}
#ifdef AGENT_STRATEGY_OUTPUT
	cout<<"topSpeed"<<topSpeed<<endl;
#endif
	if(angleToTurn>20&&topSpeed==MIN_SPEED)//为了能够迅速转角
	{
		topSpeed=MIDMIN_SPEED;
	}
	else if(angleToTurn<10&&disTodes<=0.2*GOAL_HALFLENGTH)
	{
		topSpeed=MIN_SPEED;
	}
		//destination=(13,5,0);
	return NEWWALK(destination, angleToTurn, topSpeed);
}
Action Strategy::splitsToSaveBall()
{
	if (getDownToSaveBall == false)
	{
		return basicMotion.StopAllMotion();
	}
	if (CITstandup.GetbeginStandUp())
	{
		basicMotion.SetTimeCounter(0);
		CITstandup.SetbeginStandUp(false);
		if (smallAngleSplit)
		{
			basicMotion.SetTimeCounter(-10);
		}
	}
	float dis = wm.getDistanceOppenentToBall(
			wm.GetClosestToBallOpponentNumberByVision());
	if (Penalty_Kick)
	{
		if (wm.CanSeeTheBall())
#ifdef AGENT_STRATEGY_OUTPUT
			cout << "my distance to ball:" << wm.GetMyDistanceToBall()
					<< "my body angle to ball :" << wm.GetMyBodyAngleToBall()
					<< endl;
#endif
		if (!wm.CanSeeTheBall())
		{
			if (basicMotion.GetTimeCounter() > 150)
			{
				CITstandup.SetbeginStandUp(true);
				CITstandup.SetfallDown(true);
				initSplits();
				justAfterSplits = true;
			}
		}
	}
	else
	{
		if (basicMotion.GetTimeCounter() == 200
				|| (theSpeedOfBall < 0.2 && dis > 1
						&& basicMotion.GetTimeCounter() > 80)
				|| (!wm.CanSeeTheBall() && basicMotion.GetTimeCounter() > 120))
		{
			CITstandup.SetbeginStandUp(true);
			CITstandup.SetfallDown(true);
			initSplits();
			justAfterSplits = true;
		}
	}
	return basicMotion.SplitingToSaveBall();

}
void Strategy::initSplits()
{
	for (int i = 0; i < 20; i++)
	{
		distanceToBall[i] = 0;
// 		angleIncreaseOfBall[i]=0;
	}
	theSpeedOfBall = 0;
	recordDistanceCounter = 0;

	justAfterSplits = false;
	smallAngleSplit = false;
	getDownToSaveBall = false;
	////////cout<<"init splits "<<endl;
}
void Strategy::WalkSolutions()
{
	float angle = wm.GetMyBodyAngleToBall();
	EstimateSpeedStrategy(angle);
	//float myBodyAngleToFlag;

	if (angle > 30)
	{
		myMoveDirection = HORIZONMOVE_LEFT;
		currentCycleSpeedStrategy = SLOW_SPEED_DOWN;

	}
	else if (angle < -30)
	{
		myMoveDirection = HORIZONMOVE_RIGHT;
		currentCycleSpeedStrategy = SLOW_SPEED_DOWN;
	}
	else
	{
		myMoveDirection = HORIZONMOVE_NULL;
		currentCycleSpeedStrategy = SPEED_UP;
	}
}
HorizonMoveDirection Strategy::GetHorizonMoveDirection() //thsi function assumes that the agent's body is orient to the ball
{

	if (wm.GetMyTeamIndex() == TI_LEFT)
	{
		if (wm.CanSeeTheFlag(VO_FLAG1_R) && !wm.CanSeeTheFlag(VO_FLAG2_R))
		{
//			cout<<"---move case 1---"<<endl;
			direction = HORIZONMOVE_LEFT;
		}
		else if (!wm.CanSeeTheFlag(VO_FLAG1_R) && wm.CanSeeTheFlag(VO_FLAG2_R))
		{
//			cout<<"---move case 2---"<<endl;
			direction = HORIZONMOVE_RIGHT;
		}
		else if (wm.CanSeeTheFlag(VO_GOAL1_R) && !wm.CanSeeTheFlag(VO_GOAL2_R))
		{
//			cout<<"---move case 3---"<<endl;
			direction = HORIZONMOVE_LEFT;
		}
		else if (!wm.CanSeeTheFlag(VO_GOAL1_R) && wm.CanSeeTheFlag(VO_GOAL2_R))
		{
//			cout<<"---move case 4---"<<endl;
			direction = HORIZONMOVE_RIGHT;
		}
		else if (wm.CanSeeTheFlag(VO_FLAG1_R) && wm.CanSeeTheFlag(VO_FLAG2_R))
		{
			//	float dis1=wm.GetMyDistanceToFlag(VO_FLAG1_R);
			//	float dis2=wm.GetMyDistanceToFlag(VO_FLAG2_R);
//		cout<<"---move case 5---"<<endl;

			float angle1 = wm.GetMyAngleToFlag(VO_FLAG1_R);
			float angle2 = wm.GetMyAngleToFlag(VO_FLAG2_R);

			if (fabs(angle1) > fabs(angle2))
				direction = HORIZONMOVE_RIGHT;
			else
				direction = HORIZONMOVE_LEFT;
		}
		else if (wm.CanSeeTheFlag(VO_GOAL1_R) && wm.CanSeeTheFlag(VO_GOAL2_R))
		{
//			cout<<"---move case 6---"<<endl;
			float angle1 = wm.GetMyAngleToFlag(VO_GOAL1_R);
			float angle2 = wm.GetMyAngleToFlag(VO_GOAL2_R);

			if (fabs(angle1) > fabs(angle2))
				direction = HORIZONMOVE_RIGHT;
			else
				direction = HORIZONMOVE_LEFT;
		}
		else if (wm.CanSeeTheFlag(VO_FLAG1_L) && !wm.CanSeeTheFlag(VO_FLAG2_L))
		{
//			cout<<"---move case 7---"<<endl;
			direction = HORIZONMOVE_LEFT;
		}
		else if (!wm.CanSeeTheFlag(VO_FLAG1_L) && wm.CanSeeTheFlag(VO_FLAG2_L))
		{
//			cout<<"---move case 8---"<<endl;
			direction = HORIZONMOVE_RIGHT;
		}
		else if (wm.CanSeeTheFlag(VO_GOAL1_L) && !wm.CanSeeTheFlag(VO_GOAL2_L))
		{
//			cout<<"---move case 9---"<<endl;
			direction = HORIZONMOVE_LEFT;
		}
		else if (!wm.CanSeeTheFlag(VO_GOAL1_L) && wm.CanSeeTheFlag(VO_GOAL2_L))
		{
//			cout<<"---move case 10---"<<endl;
			direction = HORIZONMOVE_RIGHT;
		}
		else if (wm.CanSeeTheFlag(VO_FLAG1_L) && wm.CanSeeTheFlag(VO_FLAG2_L))
		{
			//	float dis1=wm.GetMyDistanceToFlag(VO_FLAG1_R);
			//	float dis2=wm.GetMyDistanceToFlag(VO_FLAG2_R);
//			cout<<"---move case 11---"<<endl;
			float angle1 = wm.GetMyAngleToFlag(VO_FLAG1_L);
			float angle2 = wm.GetMyAngleToFlag(VO_FLAG2_L);

			if (fabs(angle1) > fabs(angle2))
				direction = HORIZONMOVE_RIGHT;
			else
				direction = HORIZONMOVE_LEFT;
		}
		else if (wm.CanSeeTheFlag(VO_GOAL1_R) && wm.CanSeeTheFlag(VO_GOAL2_L))
		{
//			cout<<"---move case 12---"<<endl;
			float angle1 = wm.GetMyAngleToFlag(VO_GOAL1_L);
			float angle2 = wm.GetMyAngleToFlag(VO_GOAL2_L);

			if (fabs(angle1) > fabs(angle2))
				direction = HORIZONMOVE_RIGHT;
			else
				direction = HORIZONMOVE_LEFT;
		}
	}
	else if (wm.GetMyTeamIndex() == TI_RIGHT)
	{
		if (wm.CanSeeTheFlag(VO_FLAG1_R) && !wm.CanSeeTheFlag(VO_FLAG2_R))
			direction = HORIZONMOVE_RIGHT;
		else if (!wm.CanSeeTheFlag(VO_FLAG1_R) && wm.CanSeeTheFlag(VO_FLAG2_R))
			direction = HORIZONMOVE_LEFT;
		else if (wm.CanSeeTheFlag(VO_GOAL1_R) && !wm.CanSeeTheFlag(VO_GOAL2_R))
			direction = HORIZONMOVE_RIGHT;
		else if (!wm.CanSeeTheFlag(VO_GOAL1_R) && wm.CanSeeTheFlag(VO_GOAL2_R))
			direction = HORIZONMOVE_LEFT;
		else if (wm.CanSeeTheFlag(VO_FLAG1_R) && wm.CanSeeTheFlag(VO_FLAG2_R))
		{
			//	float dis1=wm.GetMyDistanceToFlag(VO_FLAG1_R);
			//	float dis2=wm.GetMyDistanceToFlag(VO_FLAG2_R);

			float angle1 = wm.GetMyAngleToFlag(VO_FLAG1_R);
			float angle2 = wm.GetMyAngleToFlag(VO_FLAG2_R);

			if (fabs(angle1) > fabs(angle2))
				direction = HORIZONMOVE_LEFT;
			else
				direction = HORIZONMOVE_RIGHT;
		}
		else if (wm.CanSeeTheFlag(VO_GOAL1_R) && wm.CanSeeTheFlag(VO_GOAL2_R))
		{
			float angle1 = wm.GetMyAngleToFlag(VO_GOAL1_R);
			float angle2 = wm.GetMyAngleToFlag(VO_GOAL2_R);

			if (fabs(angle1) > fabs(angle2))
				direction = HORIZONMOVE_LEFT;
			else
				direction = HORIZONMOVE_RIGHT;
		}
		else if (wm.CanSeeTheFlag(VO_FLAG1_L) && !wm.CanSeeTheFlag(VO_FLAG2_L))
			direction = HORIZONMOVE_RIGHT;
		else if (!wm.CanSeeTheFlag(VO_FLAG1_L) && wm.CanSeeTheFlag(VO_FLAG2_L))
			direction = HORIZONMOVE_LEFT;
		else if (wm.CanSeeTheFlag(VO_GOAL1_L) && !wm.CanSeeTheFlag(VO_GOAL2_L))
			direction = HORIZONMOVE_RIGHT;
		else if (!wm.CanSeeTheFlag(VO_GOAL1_L) && wm.CanSeeTheFlag(VO_GOAL2_L))
			direction = HORIZONMOVE_LEFT;
		else if (wm.CanSeeTheFlag(VO_FLAG1_L) && wm.CanSeeTheFlag(VO_FLAG2_L))
		{
			//	float dis1=wm.GetMyDistanceToFlag(VO_FLAG1_R);
			//	float dis2=wm.GetMyDistanceToFlag(VO_FLAG2_R);

			float angle1 = wm.GetMyAngleToFlag(VO_FLAG1_L);
			float angle2 = wm.GetMyAngleToFlag(VO_FLAG2_L);

			if (fabs(angle1) > fabs(angle2))
				direction = HORIZONMOVE_LEFT;
			else
				direction = HORIZONMOVE_RIGHT;
		}
		else if (wm.CanSeeTheFlag(VO_GOAL1_R) && wm.CanSeeTheFlag(VO_GOAL2_L))
		{
			float angle1 = wm.GetMyAngleToFlag(VO_GOAL1_L);
			float angle2 = wm.GetMyAngleToFlag(VO_GOAL2_L);

			if (fabs(angle1) > fabs(angle2))
				direction = HORIZONMOVE_LEFT;
			else
				direction = HORIZONMOVE_RIGHT;
		}
	}

	return direction;
}

void Strategy::EstimateSpeedStrategy(float& angleToTurn)
{
	if (fabs(angleToTurn) > 15)
	{
		currentCycleSpeedStrategy = SLOW_SPEED_DOWN;
	}
	else
	{
		currentCycleSpeedStrategy = SPEED_UP;
	}

	if (!wm.CanSeeTheBall()) //can not see my ball
	{
		currentCycleSpeedStrategy = SLOW_SPEED_DOWN;

	}
}
void Strategy::CalculateTurnHeadAngle()
{
	if (turnHeadCounter < turnHeadTimes)
	{
		turnHeadCounter++;
#ifdef AGENT_STRATEGY_OUTPUT
		cout << "time :" << wm.GetCurrentGameTime() << "   	turnHeadCounter :"
				<< turnHeadCounter << endl;
#endif
	}
	else
	{
		turnHeadCounter = 0;
		turnHeadCounterClearZeroNum++;
#ifdef AGENT_STRATEGY_OUTPUT
		cout << "time :" << wm.GetCurrentGameTime()
				<< "   	turnHeadCounterClearZeroNum :"
				<< turnHeadCounterClearZeroNum << endl;
#endif
	}

	if (turnHeadCounter == turnHeadTimes / 2 && firstTurnHead != true
			&& turnHeadCounterClearZeroNum == 2)
	{
		canStopTurnHead = true;
		turnHeadEnable = false;
		turnHeadCounterClearZeroNum = 0;
	}
	else
	{
		canStopTurnHead = false;
	}

	if (firstTurnHead == true)
	{
		head1Angle = head1Angle + turnHeadAngleIncrement;
		if (turnHeadCounter >= turnHeadTimes)
		{
			firstTurnHead = false;
			turnHeadCounter = 0;
#ifdef AGENT_STRATEGY_OUTPUT
			cout << "time :" << wm.GetCurrentGameTime()
					<< "	change turn angle !!!!!" << endl;
#endif
		}
	}
	else
	{
		if (turnHeadToLeft == true)
		{
#ifdef AGENT_STRATEGY_OUTPUT
			cout << "time :" << wm.GetCurrentGameTime() << "	turn  left :"
					<< head1Angle << endl;
#endif
			head1Angle = head1Angle + turnHeadAngleIncrement;
		}
		else if (turnHeadToRight == true)
		{
#ifdef AGENT_STRATEGY_OUTPUT
			cout << "time :" << wm.GetCurrentGameTime() << "	turn  right :"
					<< head1Angle << endl;
#endif
			head1Angle = head1Angle - turnHeadAngleIncrement;
		}
	}

	if (turnHeadCounter <= 0 && turnHeadCounterClearZeroNum != 1)
	{
		if (turnHeadToLeft == true)
		{
			turnHeadToLeft = false;
			turnHeadToRight = true;
		}
		else if (turnHeadToRight == true)
		{
			turnHeadToLeft = true;
			turnHeadToRight = false;
		}
	}
}

void Strategy::initHalfStepParameter()
{
	walkDirection = WALK_FORWARD;
	currentCycleWalkDirection = WALK_FORWARD;
	lastCycleWalkDirection = WALK_FORWARD;
	lastCycleSpeedStrategy = SPEED_UP;
	currentCycleSpeedStrategy = SPEED_UP;
	myMoveDirection = HORIZONMOVE_NULL;

	leftHorizontalMove = true;
	rightHrizontalMove = false;

	adjustBodyDirection = false;
	gotMyMoveDirection = false;
	angleToTurn = 0;
	turnHeadEnable = false;
	beginFindBall = false;
	beginTurnHead = false;

	beginTurnBody = false;
	canStopTurnHead = false;
	firstTurnHead = true;

	turnHeadCounter = 0;
	changeDirection = false;

	CITstandup.SetwalkBegain(true);
}
Action Strategy::HalfStepWalk()
{
	if (newWalk.UseNewWalk == true)
	{
		initHalfStepParameter();
	}
	WalkDirection ww = WALK_FORWARD;
	float cc = wm.GetMyBodyAngleToBall();
	WalkSolutions();
	CalculateTurnHeadAngle();
	return newWalk.HalfStepGait(ww, cc, currentCycleSpeedStrategy,
			myMoveDirection, head1Angle);
}

bool Strategy::WhetherUseHalfStepWalk()
{
	bool res = false;
	if (messageParser.playerAroundMe == OPPONENT_FRONT)
	{
		if (wm.CanSeeTheBall() && wm.WhetherFaceToOppGoal()
				&& fabs(newWalk.GetFootWidth()) < 0.05)
		{
			res = true;
		}
		else
		{
			res = false;
		}
	}

	if (wm.EstimateWhetherUseHalfWalk() && fabs(newWalk.GetFootWidth()) < 0.05)
	{
		res = true;
	}
	else
	{
		return false;
	}

	return res;
}

bool Strategy::whetherCanShoot()
{

	//return true;
///	Vector3 myCoordinate=wm.GetMyCoordinate();

	if ((ball.x() < 4.8725 * CELL_LENGTH || fabs(ball.y()) > 2.5* CELL_LENGTH)  //2   5.8725
			|| wm.GetMyDistanceToBall() > 0.9
		|| wm.GetClosestToBallOpponentDistanceByVision() > 1.9035 * CELL_LENGTH
		//	||wm.WhetherCanPassFront()==false
		|| wm.GetClosestToBallOpponentDistanceByVision() < 1*CELL_LENGTH
		|| wm.GetClosestToMeOpponentDistanceByVision()<0.6)
	{
		return false;
	}
	else
	{
		if (myRole == ROLE_VANGUARD)
		{
			if (wm.IsTheBallOutOfShootArea())
			{
				////cout<<"IsTheBallOutOfShootArea()"<<endl;
				return false;
			}
			if (wm.GetMyTeamIndex() == TI_LEFT)
			{
				if (fabs(wm.GetMyBodyAngleToBall()) < 45
						&& messageParser.mVisionSenseMap[VO_GOAL1_R].phi != 0
						&& messageParser.mVisionSenseMap[VO_GOAL2_R].phi != 0)
				{
					float dis1 =
							messageParser.mVisionSenseMap[VO_GOAL1_R].distance;
					float dis2 =
							messageParser.mVisionSenseMap[VO_GOAL2_R].distance;
					//////cout<<"			dis 1 ="<<dis1<<"		dis 2 ="<<dis2<<endl;
					if (dis1 > dis2)
					{

						if (dis2 < 1.8)
							return false;   //gai

						if (dis2 < 6)  //5.4
						{
							//////cout<<"11111111111"<<endl;
							return true;
						}
						else
							return false;
					}
					else
					{
						if (dis1 < 1.8)
							return false;

						if (dis1 < 6)
						{
							//////cout<<"222222222"<<endl;
							return true;
						}
						else
							return false;
					}
				}
				else if (messageParser.mVisionSenseMap[VO_GOAL1_R].phi != 0)
				{
					if (messageParser.mVisionSenseMap[VO_GOAL1_R].distance < 5.4
							&& messageParser.mVisionSenseMap[VO_GOAL1_R].distance
									> 1.8)
					{
						//////cout<<"		dis 1 ="<<messageParser.mVisionSenseMap[VO_GOAL1_R].distance<<endl;
						return true;
					}
					else
						return false;
				}
				else if (messageParser.mVisionSenseMap[VO_GOAL2_R].phi != 0)
				{
					if (messageParser.mVisionSenseMap[VO_GOAL2_R].distance < 5.4
							&& messageParser.mVisionSenseMap[VO_GOAL2_R].distance
									> 1.8)
					{
						////cout<<"		dis 2 ="<<messageParser.mVisionSenseMap[VO_GOAL2_R].distance<<endl;
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
				if (fabs(wm.GetMyBodyAngleToBall()) < 45
						&& messageParser.mVisionSenseMap[VO_GOAL1_L].phi != 0
						&& messageParser.mVisionSenseMap[VO_GOAL2_L].phi != 0)
				{
					float dis1 =
							messageParser.mVisionSenseMap[VO_GOAL1_L].distance;
					float dis2 =
							messageParser.mVisionSenseMap[VO_GOAL2_L].distance;
					if (dis1 > dis2)
					{

						if (dis2 < 1.8)
							return false;

						if (dis2 < 5.4)
						{
							//////cout<<"11111111111"<<endl;
							return true;
						}
						else
							return false;
					}
					else
					{
						if (dis1 < 1.8)
							return false;

						if (dis1 < 5.4)
						{
							//////cout<<"222222222"<<endl;
							return true;
						}
						else
							return false;
					}
				}
				else if (messageParser.mVisionSenseMap[VO_GOAL1_L].phi != 0)
				{
					if (messageParser.mVisionSenseMap[VO_GOAL1_L].distance < 5.5
							&& messageParser.mVisionSenseMap[VO_GOAL1_L].distance
									> 1.8)
						return true;
					else
						return false;
				}
				else if (messageParser.mVisionSenseMap[VO_GOAL2_L].phi != 0)
				{
					if (messageParser.mVisionSenseMap[VO_GOAL2_L].distance < 5.5
							&& messageParser.mVisionSenseMap[VO_GOAL2_L].distance
									> 1.8)
						return true;
					else
						return false;
				}
				else
					return false;
			}
		}
		else
		{

			if (!wm.CanSeeTheBall())
			{
				return false;
			}
			if (wm.GetMyDistanceToBall() < 0.135)
			{
				return false;
			}
			if (wm.GetMyDistanceToBall() < 0.2
					&& fabs(wm.GetMyBodyAngleToBall()) > 35)
			{
				return false;
			}

///	      	Vector3 my=wm.GetMyCoordinate();
			float angleToX = wm.GetBodyToX();
			////cout<<"CentreForwardWeatherCanShoot()_GetMyCoordinate():"<<wm.GetMyCoordinate()<<endl;
			////cout<<"CentreForwardWeatherCanShoot()_GetBodyToX():"<<wm.GetBodyToX()<<endl;
			////cout<<"wm.GetClosestToBallOpponentDistanceByVision():"<<wm.GetClosestToBallOpponentDistanceByVision()<<endl;
			////cout<<"wm.GetMyDistanceToBall():"<<wm.GetMyDistanceToBall()<<endl;
			////cout<<"wm.GetMyBodyAngleToBall():"<<wm.GetMyBodyAngleToBall()<<endl;
			if (fabs(my.y()) < 3 && fabs(angleToX) < 80
					&& (wm.GetClosestToBallOpponentDistanceByVision() > 0.5
							|| wm.GetClosestToBallOpponentDistanceByVision()
									== 0) && wm.GetMyDistanceToBall() < 0.5
					&& fabs(wm.GetMyBodyAngleToBall()) < 25)
			{
				return true;
			}
			else
			{
				return false;
			}
		}

	}

}

bool Strategy::whetherCanShootForVanguard() ///判断vanguard能否射门，不是为Striker设计，Striker还是使用WhetherCanShoot()来判断add by gaojin
{
#ifdef AGENT_STRATEGY_OUTPUT
	cout << "whetherCanShootForVanguard()" << endl;
#endif
	float goleWidth = wm.GetGoalWidth();
	float L = localFieldLength / 2;
	const Vector3 gole_one_Coordinate = Vector3(L, goleWidth, 0);
	const Vector3 gole_Two_Coordinate = Vector3(L, -goleWidth, 0);
	float myBodyAngleToXAxis = wm.GetMyBodyAngleToXAxis();
	float Ball_G1RToXAxisAngle, Ball_G2RToXAxisAngle;

	Ball_G1RToXAxisAngle = wm.GetDestinationBallToXAxisAngle(
			gole_one_Coordinate);
	Ball_G2RToXAxisAngle = wm.GetDestinationBallToXAxisAngle(
			gole_Two_Coordinate);

	if (wm.IsTheBallOutOfShootArea())
	{
		////cout<<"IsTheBallOutOfShootArea()"<<endl;
#ifdef AGENT_STRATEGY_OUTPUT
		cout << "whetherCanShootForVanguard()--false111" << endl;
#endif
		return false;
	}
#ifdef AGENT_STRATEGY_OUTPUT
	cout << "Ball" << ball << endl;
#endif
	if ((ball.x() < 6.5 * CELL_LENGTH) //change by cw
	|| wm.GetMyDistanceToBall() > 0.9
			/*|| wm.GetClosestToBallOpponentDistanceByVision() > 2.7 * CELL_LENGTH*/
			|| (ballCoordinate.x() > 7.0 * CELL_LENGTH
					&& fabs(ballCoordinate.y()) < 3.5 * CELL_LENGTH)
			|| wm.GetClosestToBallOpponentDistanceByVision() < 1.3 * CELL_LENGTH
			|| (fabs(ballCoordinate.y()) > 2.82 * CELL_LENGTH
					&& wm.GetCurrentGameMode() == PM_PlayOn))
	{
#ifdef AGENT_STRATEGY_OUTPUT
		cout << "whetherCanShootForVanguard()--false222" << endl;
#endif
		return false;
	}

	if (myBodyAngleToXAxis > Ball_G2RToXAxisAngle
			&& myBodyAngleToXAxis < Ball_G1RToXAxisAngle)
	{
#ifdef AGENT_STRATEGY_OUTPUT
		cout << "whetherCanShootForVanguard()--true111" << endl;
#endif
		return true;
	}
	else if (myBodyAngleToXAxis > Ball_G1RToXAxisAngle
			&& myBodyAngleToXAxis < Ball_G2RToXAxisAngle)
	{
#ifdef AGENT_STRATEGY_OUTPUT
		cout << "whetherCanShootForVanguard()--true222" << endl;
#endif
		return true;
	}
	else
	{
#ifdef AGENT_STRATEGY_OUTPUT
		cout << "whetherCanShootForVanguard()--false333" << endl;
#endif
		return false;
	}

}

bool Strategy::centreForwardWhetherCanShoot()
{
	if (!wm.CanSeeTheBall())
	{
#ifdef AGENT_STRATEGY_OUTPUT
		cout << "can not see the ball" << endl;
#endif
		return false;
	}
	if (wm.GetMyDistanceToBall() < 0.135)
	{
#ifdef AGENT_STRATEGY_OUTPUT
		cout << "GetMyDistanceToBall()<0.135" << endl;
#endif
		return false;
	}
	if (wm.GetMyDistanceToBall() < 0.2 && fabs(wm.GetMyBodyAngleToBall()) > 35)
	{
#ifdef AGENT_STRATEGY_OUTPUT
		cout << "GetMyDistanceToBall()<0.2&&fabs(GetMyBodyAngleToBall())>35"
				<< endl;
#endif
		return false;
	}
	return true;
}

bool Strategy::whetherOpponentInMyWayToGoal()
{
	bool res = false;
	int num;

	num = wm.GetClosestToMeOpponentNumberByVision();
#ifdef AGENT_STRATEGY_OUTPUT
	cout << "wm.GetMyAngleToFlag(VO_GOAL1_R):"
			<< wm.GetMyAngleToFlag(VO_GOAL1_R) << endl;
	cout << "wm.GetMyAngleToFlag(VO_GOAL2_R):"
			<< wm.GetMyAngleToFlag(VO_GOAL2_R) << endl;
#endif
	if (wm.GetMyTeamIndex() == TI_LEFT)
	{
		if (wm.GetMyAngleToFlag(VO_GOAL1_R) != 0
				&& wm.GetMyAngleToFlag(VO_GOAL2_R) != 0 && num != 0)
		{
#ifdef AGENT_STRATEGY_OUTPUT
			cout << "wm.GetMyHeadAngleToOpponent(num):"
					<< wm.GetMyHeadAngleToOpponent(num) << endl;
			cout << "wm.GetMyBodyAngleToOpponent(num):"
					<< wm.GetMyBodyAngleToOpponent(num) << endl;
			cout << "wm.GetClosestToMeOpponentDistanceByVision():"
					<< wm.GetClosestToMeOpponentDistanceByVision() << endl;
#endif
			if (wm.GetClosestToMeOpponentDistanceByVision() < 2)
			{
				if (wm.GetMyHeadAngleToOpponent(num)
						< wm.GetMyAngleToFlag(VO_GOAL1_R)
						&& wm.GetMyHeadAngleToOpponent(num)
								> wm.GetMyAngleToFlag(VO_GOAL2_R))
				{
					res = true;
				}
			}
		}
	}
	else if (wm.GetMyTeamIndex() == TI_RIGHT)
	{
	}

	if (res == true)
	{
		cout << "whetherOpponentInMyWayToGoal==true" << endl;
	}
	else
	{
		cout << "whetherOpponentInMyWayToGoal==false" << endl;
	}
	return res;
}
Vector3 Strategy::ALLanumRrunFormation()
{
	if ( my.y()<ball.y() )
	{
		destination = Vector3(ball.x()-2 * FORMCELL_LENGTH,
				ball.y()+2*FORMCELL_LENGTH,0);
	}
	else
	{
		destination = Vector3(ball.x()-2 * FORMCELL_LENGTH,
				ball.y()-2*FORMCELL_LENGTH,0);
	}
	return destination;
	}

Vector3 Strategy::DefenserunFormation()
{
#ifdef AGENT_STRATEGY_OUTPUT
	cout << "Enter runFormation" << endl;
#endif
	Vector3 destination;
////  Vector3 ball=wm.GetLastCyclesAverageBallCoordinate();
/////  Vector3 my=wm.GetMyCoordinate();
//
//	if (messageParser.GetWhetherPositionAStand() == false)
//	{
//		cout << "messageParser.GetWhetherPositionAStand()==false" << endl;
//	}
//	else
//	{
//		cout << "messageParser.GetWhetherPositionAStand()==true" << endl;
//	}
//	if (messageParser.GetWhetherPositionBStand() == false)
//	{
//		cout << "messageParser.GetWhetherPositionBStand()==false" << endl;
//	}
//	else
//	{
//		cout << "messageParser.GetWhetherPositionBStand()==true" << endl;
//	}
//	if (messageParser.GetWhetherPositionCStand() == false)
//	{
//		cout << "messageParser.GetWhetherPositionCStand()==false" << endl;
//	}
//	else
//	{
//		cout << "messageParser.GetWhetherPositionCStand()==true" << endl;
//	}
//	if (messageParser.GetWhetherPositionDStand() == false)
//	{
//		cout << "messageParser.GetWhetherPositionDStand()==false" << endl;
//	}
//	else
//	{
//		cout << "messageParser.GetWhetherPositionDStand()==true" << endl;
//	}
//	cout << "messageParser.GetPositionANumberByHear():"
//			<< messageParser.GetPositionANumberByHear() << endl;
//	cout << "messageParser.GetPositionBNumberByHear():"
//			<< messageParser.GetPositionBNumberByHear() << endl;
//	cout << "messageParser.GetPositionCNumberByHear():"
//			<< messageParser.GetPositionCNumberByHear() << endl;
//	cout << "messageParser.GetPositionDNumberByHear():"
//			<< messageParser.GetPositionDNumberByHear() << endl;
//	cout << "ball:" << ball << endl;
//	cout << "my:" << my << endl;
//
//	if (messageParser.GetWhetherBallBeforeVanguard() == true)
//	{
//		cout << "messageParser.GetWhetherBallBeforeVanguard()==true" << endl;
//	}
//	else
//	{
//		cout << "messageParser.GetWhetherBallBeforeVanguard()==false;" << endl;
//	}
	if(CITHear.GetAnum()==CITHear.GetBnum()&&CITHear.GetAnum()==CITHear.GetCnum()&&CITHear.GetAnum()==CITHear.GetDnum()&&CITHear.GetDnum()==wm.GetMyNumber())
	{
		return ALLanumRrunFormation();
	}
	else
	{
		if (my.x() > ball.x() && my.y() > ball.y())
		{//D
#ifdef AGENT_STRATEGY_OUTPUT
			cout<<"my.x() > ball.x() && my.y() > ball.y()"<<endl;
#endif
//		if (messageParser.GetWhetherPositionDStand() == false)
//		{
//			cout<<"messageParser.GetWhetherPositionDStand() == false"<<endl;
//			if (messageParser.GetPositionDNumberByHear() == wm.GetMyNumber())
//						{
//			destination = wm.GetPositionCoordinate(Position_D);
//						}
//		}
//		else if (messageParser.GetWhetherPositionDStand() == true)
//		{
#ifdef AGENT_STRATEGY_OUTPUT
			cout<<"messageParser.GetWhetherPositionDStand() == true"<<endl;
#endif
			if (messageParser.GetPositionDNumberByHear() == wm.GetMyNumber())
			{
#ifdef AGENT_STRATEGY_OUTPUT
				cout<<"messageParser.GetPositionDNumberByHear() == wm.GetMyNumber()"<<endl;
#endif
				destination = wm.GetPositionCoordinate(Position_D);
			}
			else
			{
				if (messageParser.GetWhetherPositionAStand() == false)
				{
#ifdef AGENT_STRATEGY_OUTPUT
					cout<<"messageParser.GetWhetherPositionAStand() == false"<<endl;
#endif
					destination = wm.GetPositionCoordinate(Position_A);
				}
				else if (messageParser.GetWhetherPositionDStand() == true)
				{
#ifdef AGENT_STRATEGY_OUTPUT
					cout<<"messageParser.GetWhetherPositionAStand() == true"<<endl;
#endif
					if (messageParser.GetPositionANumberByHear()
							== wm.GetMyNumber())
					{
#ifdef AGENT_STRATEGY_OUTPUT
						cout<<"messageParser.GetPositionANumberByHear()== wm.GetMyNumber()"<<endl;
#endif
						destination = wm.GetPositionCoordinate(Position_A);
					}
					else
					{
						if (messageParser.GetWhetherPositionCStand() == false)
						{
							cout<<"messageParser.GetWhetherPositionCStand() == false"<<endl;
							destination = wm.GetPositionCoordinate(Position_C);
						}
						else if (messageParser.GetWhetherPositionCStand()== true)
						{
							cout<<"messageParser.GetWhetherPositionCStand()== true"<<endl;
							if (messageParser.GetPositionCNumberByHear()
									== wm.GetMyNumber())
							{
								destination = wm.GetPositionCoordinate(
										Position_C);
							}
							else
							{
								/*
								 if(ball.x()<my.x())
								 {
								 if(fabs(my.y()-ball.y())<CELL_LENGTH)
								 {
								 if(ball.y()>0)
								 {
								 destination=Vector3(ball.x()-3*CELL_LENGTH,ball.y()-2.5*CELL_LENGTH,0);
								 }
								 else if(ball.y()<=0)
								 {
								 destination=Vector3(ball.x()-3*CELL_LENGTH,ball.y()+2.5*CELL_LENGTH,0);
								 }
								 }
								 else
								 {
								 destination=Vector3(ball.x()-3*CELL_LENGTH,ball.y(),0);
								 }
								 }
								 else
								 {
								 if(fabs(ball.y())<3*CELL_LENGTH)
								 {
								 destination=Vector3(ball.x()-3*CELL_LENGTH,ball.y(),0);
								 }
								 else
								 {
								 destination=Vector3(ball.x()-3*CELL_LENGTH,ball.y()/2,0);
								 }
								 }*/
								cout<<"last::"<<endl;
								if (ball.y() < my.y())
								{

									destination = Vector3(ball.x()- 2* CELL_LENGTH,
											ball.y() + 2.5 * CELL_LENGTH,0);
								}
								else
								{
									destination = Vector3(ball.x()- 2* CELL_LENGTH,
											ball.y() - 1.5 * CELL_LENGTH,0);
								}
							}
						}
					}
				}
			}
//		}
	}
	else if (my.x() > ball.x() && my.y() <= ball.y())
	{//C
//		cout<<"my.x() > ball.x() && my.y() <= ball.y()"<<endl;
//		if (messageParser.GetWhetherPositionCStand() == false)
//		{
//			cout<<"messageParser.GetWhetherPositionCStand() == false"<<endl;
//			destination = wm.GetPositionCoordinate(Position_C);
//		}
//		else if (messageParser.GetWhetherPositionCStand() == true)
//		{
#ifdef AGENT_STRATEGY_OUTPUT
			cout<<"messageParser.GetWhetherPositionCStand() == true"<<endl;
#endif
			if (messageParser.GetPositionCNumberByHear() == wm.GetMyNumber())
			{
#ifdef AGENT_STRATEGY_OUTPUT
				cout<<"messageParser.GetPositionCNumberByHear() == wm.GetMyNumber()"<<endl;
#endif
				destination = wm.GetPositionCoordinate(Position_C);
			}
			else
			{
				if (messageParser.GetWhetherPositionBStand() == false)
				{
#ifdef AGENT_STRATEGY_OUTPUT
					cout<<"messageParser.GetWhetherPositionBStand() == false"<<endl;
#endif
					destination = wm.GetPositionCoordinate(Position_B);
				}
				else if (messageParser.GetWhetherPositionBStand() == true)
				{
#ifdef AGENT_STRATEGY_OUTPUT
					cout<<"messageParser.GetWhetherPositionBStand() == true"<<endl;
#endif
					if (messageParser.GetPositionBNumberByHear()
							== wm.GetMyNumber())
					{
#ifdef AGENT_STRATEGY_OUTPUT
						cout<<"messageParser.GetPositionBNumberByHear()== wm.GetMyNumber()"<<endl;
#endif
						destination = wm.GetPositionCoordinate(Position_B);
					}
					else
					{
						if (messageParser.GetWhetherPositionDStand() == false)
						{
#ifdef AGENT_STRATEGY_OUTPUT
							cout<<"messageParser.GetWhetherPositionDStand() == false"<<endl;
#endif
							destination = wm.GetPositionCoordinate(Position_D);
						}
						else if (messageParser.GetWhetherPositionDStand()== true)
						{
#ifdef AGENT_STRATEGY_OUTPUT
							cout<<"messageParser.GetWhetherPositionDStand()== true"<<endl;
#endif
							if (messageParser.GetPositionDNumberByHear()== wm.GetMyNumber())
							{
#ifdef AGENT_STRATEGY_OUTPUT
								cout<<"messageParser.GetPositionDNumberByHear()== wm.GetMyNumber()"<<endl;
#endif
								destination = wm.GetPositionCoordinate(Position_D);
							}
							else
							{
								/*
								 if(ball.x()<my.x())
								 {
								 if(fabs(my.y()-ball.y())<CELL_LENGTH)
								 {
								 if(ball.y()>0)
								 {
								 destination=Vector3(ball.x()-3*CELL_LENGTH,ball.y()-2.5*CELL_LENGTH,0);
								 }
								 else if(ball.y()<=0)
								 {
								 destination=Vector3(ball.x()-3*CELL_LENGTH,ball.y()+2.5*CELL_LENGTH,0);
								 }
								 }
								 else
								 {
								 destination=Vector3(ball.x()-3*CELL_LENGTH,ball.y(),0);
								 }
								 }
								 else
								 {
								 if(fabs(ball.y())<3*CELL_LENGTH)
								 {
								 destination=Vector3(ball.x()-3*CELL_LENGTH,ball.y(),0);
								 }
								 else
								 {
								 destination=Vector3(ball.x()-3*CELL_LENGTH,ball.y()/2,0);
								 }
								 }*/
#ifdef AGENT_STRATEGY_OUTPUT
								cout<<"last::"<<endl;
#endif
								if (ball.y() < my.y())
								{

									destination = Vector3(ball.x()- 2* FORMCELL_LENGTH,
											ball.y() + 2.5 * FORMCELL_LENGTH,0);
								}
								else
								{
									destination = Vector3(ball.x()- 2* FORMCELL_LENGTH,
											ball.y() - 1.5 * FORMCELL_LENGTH,0);
								}

							}
						}
					}
				}
				else
				{

					destination = wm.GetPositionCoordinate(Position_B);

				}
//			}
		}
	}
	else if (my.x() <= ball.x() && my.y() > ball.y())
	{//A
		if(CITHear.GetEnum()==wm.GetMyNumber())
		{
			destination = wm.GetPositionCoordinate(Position_E);
		}
		else
		{
		if(CITHear.GetDnum()==wm.GetMyNumber())
		{
#ifdef AGENT_STRATEGY_OUTPUT
			cout<<"A::CITHear.GetDnum()==wm.GetMyNumber()"<<endl;
#endif
			destination = wm.GetPositionCoordinate(Position_D);
		}
		else
		{
		if(CITHear.GetAnum()!=CITHear.GetDnum())
		{
#ifdef AGENT_STRATEGY_OUTPUT
			cout<<"my.x() <= ball.x() && my.y() > ball.y()"<<endl;
#endif
			if (messageParser.GetWhetherPositionAStand() == true)
			{
#ifdef AGENT_STRATEGY_OUTPUT
				cout<<"messageParser.GetWhetherPositionAStand() == true"<<endl;
#endif
				if (messageParser.GetPositionANumberByHear() == wm.GetMyNumber())
				{
#ifdef AGENT_STRATEGY_OUTPUT
					cout<<"messageParser.GetPositionANumberByHear() == wm.GetMyNumber()"<<endl;
#endif
					destination = wm.GetPositionCoordinate(Position_A);
				}
				else
				{
						if (messageParser.GetWhetherPositionBStand() == false)
						{
#ifdef AGENT_STRATEGY_OUTPUT
							cout<<"messageParser.GetWhetherPositionBStand() == false"<<endl;
#endif
							destination = wm.GetPositionCoordinate(Position_B);
						}
						else if (messageParser.GetWhetherPositionBStand() == true)
						{
#ifdef AGENT_STRATEGY_OUTPUT
							cout<<"messageParser.GetWhetherPositionBStand() == true"<<endl;
#endif
							if (messageParser.GetPositionBNumberByHear()== wm.GetMyNumber())
							{
#ifdef AGENT_STRATEGY_OUTPUT
								cout<<"messageParser.GetPositionBNumberByHear()== wm.GetMyNumber()"<<endl;
#endif
								destination = wm.GetPositionCoordinate(Position_B);
							}
							else
							{
								if (messageParser.GetWhetherPositionDStand()== false)
								{
#ifdef AGENT_STRATEGY_OUTPUT
									cout<<"messageParser.GetWhetherPositionDStand()== false"<<endl;
#endif
									destination = wm.GetPositionCoordinate(Position_D);
								}
								else if (messageParser.GetWhetherPositionDStand()== true)
								{
#ifdef AGENT_STRATEGY_OUTPUT
									cout<<"messageParser.GetWhetherPositionDStand()== true"<<endl;
#endif
									if (messageParser.GetPositionDNumberByHear()== wm.GetMyNumber())
									{
#ifdef AGENT_STRATEGY_OUTPUT
										cout<<"messageParser.GetPositionDNumberByHear()== wm.GetMyNumber()"<<endl;
#endif
										destination = wm.GetPositionCoordinate(Position_D);
									}
									else	if (messageParser.GetPositionCNumberByHear()== wm.GetMyNumber())
									{
#ifdef AGENT_STRATEGY_OUTPUT
										cout<<"messageParser.GetPositionCNumberByHear()== wm.GetMyNumber()"<<endl;
#endif
										destination = wm.GetPositionCoordinate(Position_C);
									}
									else
									{
										/*
										 if(ball.x()<my.x())
										 {
										 if(fabs(my.y()-ball.y())<CELL_LENGTH)
										 {
										 if(ball.y()>0)
										 {
										 destination=Vector3(ball.x()-3*CELL_LENGTH,ball.y()-2.5*CELL_LENGTH,0);
										 }
										 else if(ball.y()<=0)
										 {
										 destination=Vector3(ball.x()-3*CELL_LENGTH,ball.y()+2.5*CELL_LENGTH,0);
										 }
										 }
										 else
										 {
										 destination=Vector3(ball.x()-3*CELL_LENGTH,ball.y(),0);
										 }
										 }
										 else
										 {
										 if(fabs(ball.y())<3*CELL_LENGTH)
										 {
										 destination=Vector3(ball.x()-3*CELL_LENGTH,ball.y(),0);
										 }
										 else
										 {
										 destination=Vector3(ball.x()-3*CELL_LENGTH,ball.y()/2,0);
										 }
										 }*/
#ifdef AGENT_STRATEGY_OUTPUT
										cout<<"last::"<<endl;
#endif
										if (ball.y() > my.y())
										{
											destination = Vector3(ball.x()-2.5*FORMCELL_LENGTH,
													ball.y() - 1.5 * FORMCELL_LENGTH,0);
										}
										else
										{
											destination = Vector3(ball.x()-2.5*FORMCELL_LENGTH,
													ball.y() + 1.5 * FORMCELL_LENGTH,0);
										}

									}
								}
							}
						}
				}

			}
			else
					{
						destination = wm.GetPositionCoordinate(Position_A);
					}
		}
		else
		{
			destination = wm.GetPositionCoordinate(Position_A);
		}
		}
		}
	}
	else if (my.x() <= ball.x() && my.y() <= ball.y())
	{//B
		if(CITHear.GetEnum()==wm.GetMyNumber())
		{
			destination = wm.GetPositionCoordinate(Position_E);
		}
		else
		{
		if(CITHear.GetCnum()==wm.GetMyNumber())
		{
			destination = wm.GetPositionCoordinate(Position_C);
		}
		else
		{
		if(CITHear.GetBnum()!=CITHear.GetCnum())
		{
#ifdef AGENT_STRATEGY_OUTPUT
			cout<<"my.x() <= ball.x() && my.y() <= ball.y()"<<endl;
#endif
			if (messageParser.GetWhetherPositionBStand() == false)
			{
#ifdef AGENT_STRATEGY_OUTPUT
				cout<<"messageParser.GetWhetherPositionBStand() == false"<<endl;
#endif
				destination = wm.GetPositionCoordinate(Position_B);
			}
			else if (messageParser.GetWhetherPositionBStand() == true)
			{
#ifdef AGENT_STRATEGY_OUTPUT
				cout<<"messageParser.GetWhetherPositionBStand() == true"<<endl;
#endif
				if (messageParser.GetPositionBNumberByHear() == wm.GetMyNumber())
				{
#ifdef AGENT_STRATEGY_OUTPUT
					cout<<"messageParser.GetPositionBNumberByHear() == wm.GetMyNumber()"<<endl;
#endif
					destination = wm.GetPositionCoordinate(Position_B);
				}
				else
				{
#ifdef AGENT_STRATEGY_OUTPUT
					cout<<"messageParser.GetPositionBNumberByHear() != wm.GetMyNumber()"<<endl;
#endif
					if (messageParser.GetWhetherPositionAStand() == false)
					{
#ifdef AGENT_STRATEGY_OUTPUT
						cout<<"messageParser.GetWhetherPositionAStand() == false"<<endl;
#endif
						destination = wm.GetPositionCoordinate(Position_A);
					}
					else if (messageParser.GetWhetherPositionAStand() == true)
					{
#ifdef AGENT_STRATEGY_OUTPUT
						cout<<"messageParser.GetWhetherPositionAStand() == true"<<endl;
#endif
						if (messageParser.GetPositionANumberByHear()
								== wm.GetMyNumber())
						{
#ifdef AGENT_STRATEGY_OUTPUT
							cout<<"messageParser.GetPositionANumberByHear()== wm.GetMyNumber()"<<endl;
#endif
							destination = wm.GetPositionCoordinate(Position_A);
						}
						else
						{
							if (messageParser.GetWhetherPositionCStand() == false)
							{
#ifdef AGENT_STRATEGY_OUTPUT
								cout<<"messageParser.GetWhetherPositionCStand() == false"<<endl;
#endif
								destination = wm.GetPositionCoordinate(Position_C);
							}
							else if (messageParser.GetWhetherPositionCStand()
									== true)
							{
#ifdef AGENT_STRATEGY_OUTPUT
								cout<<"messageParser.GetWhetherPositionCStand()== true"<<endl;
#endif
								if (messageParser.GetPositionCNumberByHear()
										== wm.GetMyNumber())
								{
#ifdef AGENT_STRATEGY_OUTPUT
									cout<<"messageParser.GetPositionCNumberByHear()== wm.GetMyNumber()"<<endl;
#endif
									destination = wm.GetPositionCoordinate(
											Position_C);
								}
								else
										if (messageParser.GetPositionDNumberByHear()
												== wm.GetMyNumber())
										{
#ifdef AGENT_STRATEGY_OUTPUT
											cout<<"messageParser.GetPositionDNumberByHear()== wm.GetMyNumber()"<<endl;
#endif
											destination = wm.GetPositionCoordinate(
													Position_D);
										}
								else
								{
									/*
									 if(ball.x()<my.x())
									 {
									 if(fabs(my.y()-ball.y())<CELL_LENGTH)
									 {
									 if(ball.y()>0)
									 {
									 destination=Vector3(ball.x()-3*CELL_LENGTH,ball.y()-2.5*CELL_LENGTH,0);
									 }
									 else if(ball.y()<=0)
									 {
									 destination=Vector3(ball.x()-3*CELL_LENGTH,ball.y()+2.5*CELL_LENGTH,0);
									 }
									 }
									 else
									 {
									 destination=Vector3(ball.x()-3*CELL_LENGTH,ball.y(),0);
									 }
									 }
									 else
									 {
									 if(fabs(ball.y())<3*CELL_LENGTH)
									 {
									 destination=Vector3(ball.x()-3*CELL_LENGTH,ball.y(),0);
									 }
									 else
									 {
									 destination=Vector3(ball.x()-3*CELL_LENGTH,ball.y()/2,0);
									 }
									 }
									 */
#ifdef AGENT_STRATEGY_OUTPUT
									cout<<"last"<<endl;
#endif
									if (ball.y() > my.y())
									{
										destination = Vector3(ball.x()-2.5*FORMCELL_LENGTH,
												ball.y() - 1.5 * FORMCELL_LENGTH,0);
									}
									else
									{
										destination = Vector3(ball.x()-2.5*FORMCELL_LENGTH,
												ball.y() + 1.5 * FORMCELL_LENGTH,0);
									}
								}
							}
						}
					}
				}
				}
			}
		else
		{
			destination = wm.GetPositionCoordinate(Position_B);
		}
		}
	}
	}
}
	if (ball.x() >6 * CELL_LENGTH)
	{
//		cout<<"ball.x() > 5 * CELL_LENGTH"<<endl;
		if (ball.y() > 0)
		{
//			cout<<"ball.y() > 0"<<endl;
			if (messageParser.GetWhetherPositionCStand() == false)
			{
//				cout<<"messageParser.GetWhetherPositionCStand() == false"<<endl;
				destination = wm.GetPositionCoordinate(Position_C);
			}
			else if (messageParser.GetWhetherPositionCStand() == true)
			{
//				cout<<"messageParser.GetWhetherPositionCStand() == true"<<endl;
				if (messageParser.GetPositionCNumberByHear()
						== wm.GetMyNumber())
				{
//					cout<<"messageParser.GetPositionCNumberByHear()== wm.GetMyNumber()"<<endl;
					destination = wm.GetPositionCoordinate(Position_C);
				}
				else
				{
					if (messageParser.GetWhetherPositionBStand() == false)
					{
//						cout<<"messageParser.GetWhetherPositionCStand() == false"<<endl;
						destination = wm.GetPositionCoordinate(Position_B);
					}
					else if (messageParser.GetWhetherPositionBStand() == true)
					{
//						cout<<"messageParser.GetWhetherPositionCStand() == true"<<endl;
						if (messageParser.GetPositionBNumberByHear()
								== wm.GetMyNumber())
						{
//							cout<<"messageParser.GetPositionCNumberByHear()== wm.GetMyNumber()"<<endl;
							destination = wm.GetPositionCoordinate(Position_B);
						}
						else
						{
							if (messageParser.GetWhetherPositionAStand()
									== false)
							{
//								cout<<"messageParser.GetWhetherPositionAStand()== false"<<endl;
								destination = wm.GetPositionCoordinate(
										Position_A);
							}
							else if (messageParser.GetWhetherPositionAStand()
									== true)
							{
//								cout<<"messageParser.GetWhetherPositionAStand()== true"<<endl;
								if (messageParser.GetPositionANumberByHear()
										== wm.GetMyNumber())
								{
//									cout<<"messageParser.GetPositionANumberByHear()== wm.GetMyNumber()"<<endl;
									destination = wm.GetPositionCoordinate(
											Position_A);
								}
								else
								{
									if (messageParser.GetWhetherPositionDStand()
											== false)
									{
//										cout<<"messageParser.GetWhetherPositionDStand()== false"<<endl;
										destination = wm.GetPositionCoordinate(
												Position_D);
									}
									else if (messageParser.GetWhetherPositionDStand()
											== true)
									{
//										cout<<"messageParser.GetWhetherPositionDStand()== true"<<endl;
										if (messageParser.GetPositionDNumberByHear()
												== wm.GetMyNumber())
										{
//											cout<<"messageParser.GetPositionDNumberByHear()== wm.GetMyNumber()"<<endl;
											destination =
													wm.GetPositionCoordinate(
															Position_D);
										}
										else
										{
											if (ball.y() > my.y())
											{

												destination =
														Vector3(
																ball.x(),
																ball.y()
																		- 1.5
																				* FORMCELL_LENGTH
																		, 0);
											}
											else
											{
												destination =
														Vector3(
																ball.x(),
																ball.y()
																		+ 1.5
																				* FORMCELL_LENGTH
																		, 0);
											}
										}
									}
								}
							}
						}
					}
				}
			}
			else
					{
						destination = wm.GetPositionCoordinate(Position_C);
					}
		}
		else
		{

			if (messageParser.GetWhetherPositionDStand() == false)
			{
//				cout<<"messageParser.GetWhetherPositionDStand() == false"<<endl;
				destination = wm.GetPositionCoordinate(Position_D);
			}
			else if (messageParser.GetWhetherPositionDStand() == true)
			{
//				cout<<"messageParser.GetWhetherPositionDStand() == true"<<endl;
				if (messageParser.GetPositionDNumberByHear()== wm.GetMyNumber())
				{
//					cout<<"messageParser.GetPositionDNumberByHear()== wm.GetMyNumber()"<<endl;
					destination = wm.GetPositionCoordinate(Position_D);
				}
				else
				{
					if (messageParser.GetWhetherPositionAStand() == false)
					{
//						cout<<"messageParser.GetWhetherPositionAStand() == false"<<endl;
						destination = wm.GetPositionCoordinate(Position_A);
					}
					else if (messageParser.GetWhetherPositionAStand() == true)
					{
//						cout<<"messageParser.GetWhetherPositionAStand() == true"<<endl;
						if (messageParser.GetPositionANumberByHear()
								== wm.GetMyNumber())
						{
//							cout<<"messageParser.GetPositionANumberByHear()== wm.GetMyNumber()"<<endl;
							destination = wm.GetPositionCoordinate(Position_A);
						}
						else
						{
							if (messageParser.GetWhetherPositionBStand()
									== false)
							{
//								cout<<"messageParser.GetWhetherPositionBStand()== false"<<endl;
								destination = wm.GetPositionCoordinate(
										Position_B);
							}
							else if (messageParser.GetWhetherPositionBStand()
									== true)
							{
//								cout<<"messageParser.GetWhetherPositionBStand()== true"<<endl;
								if (messageParser.GetPositionBNumberByHear()
										== wm.GetMyNumber())
								{
//									cout<<"messageParser.GetPositionBNumberByHear()== wm.GetMyNumber()"<<endl;
									destination = wm.GetPositionCoordinate(
											Position_B);
								}
								else
								{
									if (messageParser.GetWhetherPositionCStand()
											== false)
									{
//										cout<<"messageParser.GetWhetherPositionCStand()== false"<<endl;
										destination = wm.GetPositionCoordinate(
												Position_C);
									}
									else if (messageParser.GetWhetherPositionCStand()
											== true)
									{
//										cout<<"messageParser.GetWhetherPositionCStand()== true"<<endl;
										if (messageParser.GetPositionCNumberByHear()
												== wm.GetMyNumber())
										{
//											cout<<"messageParser.GetPositionCNumberByHear()== wm.GetMyNumber()"<<endl;
											destination =
													wm.GetPositionCoordinate(
															Position_C);
										}
										else
										{
											if (ball.y() > my.y())
											{
												destination =
														Vector3(
																ball.x(),
																ball.y()
																		- 1.5
																				* FORMCELL_LENGTH
																		, 0);
											}
											else
											{
												destination =
														Vector3(
																ball.x(),
																ball.y()
																		+ 1.5
																				* FORMCELL_LENGTH
																		, 0);
											}
										}
									}
								}
							}
						}
					}
					else
							{
								destination = wm.GetPositionCoordinate(Position_A);
							}
				}
			}
		}

	}
	if(CITHear.GetEnum()==wm.GetMyNumber())
	{
		destination = wm.GetPositionCoordinate(Position_E);
	}


	return destination;
}

Vector3 Strategy::AttackrunFormation()
{
	/////cout<<"Enter runFormation"<<endl;
	Vector3 destination;
//  Vector3 ball=wm.GetLastCyclesAverageBallCoordinate();
///  Vector3 my=wm.GetMyCoordinate();

	if (messageParser.GetWhetherPositionAStand() == false)
	{
		/////cout<<"messageParser.GetWhetherPositionAStand()==false"<<endl;
	}
	else
	{
		/////cout<<"messageParser.GetWhetherPositionAStand()==true"<<endl;
	}
	if (messageParser.GetWhetherPositionBStand() == false)
	{
		/////cout<<"messageParser.GetWhetherPositionBStand()==false"<<endl;
	}
	else
	{
		/////cout<<"messageParser.GetWhetherPositionBStand()==true"<<endl;
	}
	if (messageParser.GetWhetherPositionCStand() == false)
	{
		/////cout<<"messageParser.GetWhetherPositionCStand()==false"<<endl;
	}
	else
	{
		/////cout<<"messageParser.GetWhetherPositionCStand()==true"<<endl;
	}
	if (messageParser.GetWhetherPositionDStand() == false)
	{
		/////cout<<"messageParser.GetWhetherPositionDStand()==false"<<endl;
	}
	else
	{
		/////cout<<"messageParser.GetWhetherPositionDStand()==true"<<endl;
	}
	/////cout<<"messageParser.GetPositionANumberByHear():"<<messageParser.GetPositionANumberByHear()<<endl;
	/////cout<<"messageParser.GetPositionBNumberByHear():"<<messageParser.GetPositionBNumberByHear()<<endl;
	/////cout<<"messageParser.GetPositionCNumberByHear():"<<messageParser.GetPositionCNumberByHear()<<endl;
	/////cout<<"messageParser.GetPositionDNumberByHear():"<<messageParser.GetPositionDNumberByHear()<<endl;
	/////cout<<"ball:"<<ball<<endl;
	/////cout<<"my:"<<my<<endl;

	if (messageParser.GetWhetherBallBeforeVanguard() == true)
	{
		/////cout<<"messageParser.GetWhetherBallBeforeVanguard()==true"<<endl;
	}
	else
	{
		/////cout<<"messageParser.GetWhetherBallBeforeVanguard()==false;"<<endl;
	}

	if (my.x() > ball.x() && my.y() > ball.y())
	{
		if (messageParser.GetWhetherPositionAStand() == false)
		{

			destination = wm.GetPositionCoordinate(Position_A);
		}
		else if (messageParser.GetWhetherPositionAStand() == true)
		{

			if (messageParser.GetPositionANumberByHear() == wm.GetMyNumber())
			{

				destination = wm.GetPositionCoordinate(Position_A);
			}
			else
			{
				if (messageParser.GetWhetherPositionDStand() == false)
				{

					destination = wm.GetPositionCoordinate(Position_D);
				}
				else if (messageParser.GetWhetherPositionDStand() == true)
				{
					if (messageParser.GetPositionDNumberByHear()
							== wm.GetMyNumber())
					{
						destination = wm.GetPositionCoordinate(Position_D);
					}
					else
					{
						if (messageParser.GetWhetherPositionCStand() == false)
						{
							destination = wm.GetPositionCoordinate(Position_C);
						}
						else if (messageParser.GetWhetherPositionCStand()
								== true)
						{
							if (messageParser.GetPositionCNumberByHear()
									== wm.GetMyNumber())
							{
								destination = wm.GetPositionCoordinate(
										Position_C);
							}
							else
							{
								/*
								 if(ball.x()<my.x())
								 {
								 if(fabs(my.y()-ball.y())<CELL_LENGTH)
								 {
								 if(ball.y()>0)
								 {
								 destination=Vector3(ball.x()-3*CELL_LENGTH,ball.y()-2.5*CELL_LENGTH,0);
								 }
								 else if(ball.y()<=0)
								 {
								 destination=Vector3(ball.x()-3*CELL_LENGTH,ball.y()+2.5*CELL_LENGTH,0);
								 }
								 }
								 else
								 {
								 destination=Vector3(ball.x()-3*CELL_LENGTH,ball.y(),0);
								 }
								 }
								 else
								 {
								 if(fabs(ball.y())<3*CELL_LENGTH)
								 {
								 destination=Vector3(ball.x()-3*CELL_LENGTH,ball.y(),0);
								 }
								 else
								 {
								 destination=Vector3(ball.x()-3*CELL_LENGTH,ball.y()/2,0);
								 }
								 }*/
								if (ball.y() > my.y())
								{
									destination = Vector3(ball.x(),
											ball.y() - 1.5 * CELL_LENGTH,0);
								}
								else
								{
									destination = Vector3(ball.x(),
											ball.y() + 1.5 * CELL_LENGTH,0);
								}
							}
						}
					}
				}
			}
		}
	}
	else if (my.x() > ball.x() && my.y() <= ball.y())
	{
		if (messageParser.GetWhetherPositionBStand() == false)
		{

			destination = wm.GetPositionCoordinate(Position_B);
		}
		else if (messageParser.GetWhetherPositionBStand() == true)
		{

			if (messageParser.GetPositionBNumberByHear() == wm.GetMyNumber())
			{

				destination = wm.GetPositionCoordinate(Position_B);
			}
			else
			{
				if (messageParser.GetWhetherPositionCStand() == false)
				{

					destination = wm.GetPositionCoordinate(Position_C);
				}
				else if (messageParser.GetWhetherPositionCStand() == true)
				{
					if (messageParser.GetPositionCNumberByHear()
							== wm.GetMyNumber())
					{
						destination = wm.GetPositionCoordinate(Position_C);
					}
					else
					{
						if (messageParser.GetWhetherPositionDStand() == false)
						{
							destination = wm.GetPositionCoordinate(Position_D);
						}
						else if (messageParser.GetWhetherPositionDStand()
								== true)
						{
							if (messageParser.GetPositionDNumberByHear()
									== wm.GetMyNumber())
							{
								destination = wm.GetPositionCoordinate(
										Position_D);
							}
							else
							{
								/*
								 if(ball.x()<my.x())
								 {
								 if(fabs(my.y()-ball.y())<CELL_LENGTH)
								 {
								 if(ball.y()>0)
								 {
								 destination=Vector3(ball.x()-3*CELL_LENGTH,ball.y()-2.5*CELL_LENGTH,0);
								 }
								 else if(ball.y()<=0)
								 {
								 destination=Vector3(ball.x()-3*CELL_LENGTH,ball.y()+2.5*CELL_LENGTH,0);
								 }
								 }
								 else
								 {
								 destination=Vector3(ball.x()-3*CELL_LENGTH,ball.y(),0);
								 }
								 }
								 else
								 {
								 if(fabs(ball.y())<3*CELL_LENGTH)
								 {
								 destination=Vector3(ball.x()-3*CELL_LENGTH,ball.y(),0);
								 }
								 else
								 {
								 destination=Vector3(ball.x()-3*CELL_LENGTH,ball.y()/2,0);
								 }
								 }*/

								if (ball.y() > my.y())
								{
									destination = Vector3(ball.x(),
											ball.y() - 1.5 * CELL_LENGTH,0);
								}
								else
								{
									destination = Vector3(ball.x(),
											ball.y() + 1.5 * CELL_LENGTH,0);
								}

							}
						}
					}
				}
			}
		}
	}
	else if (my.x() <= ball.x() && my.y() > ball.y())
	{
		if (messageParser.GetWhetherPositionAStand() == false)
		{

			destination = wm.GetPositionCoordinate(Position_A);
		}
		else if (messageParser.GetWhetherPositionAStand() == true)
		{

			if (messageParser.GetPositionANumberByHear() == wm.GetMyNumber())
			{

				destination = wm.GetPositionCoordinate(Position_A);
			}
			else
			{

				{
					if (messageParser.GetWhetherPositionBStand() == false)
					{
						destination = wm.GetPositionCoordinate(Position_B);
					}
					else if (messageParser.GetWhetherPositionBStand() == true)
					{
						if (messageParser.GetPositionBNumberByHear()
								== wm.GetMyNumber())
						{
							destination = wm.GetPositionCoordinate(Position_B);
						}
						else
						{
							if (messageParser.GetWhetherPositionDStand()
									== false)
							{
								destination = wm.GetPositionCoordinate(
										Position_D);
							}
							else if (messageParser.GetWhetherPositionDStand()
									== true)
							{
								if (messageParser.GetPositionDNumberByHear()
										== wm.GetMyNumber())
								{
									destination = wm.GetPositionCoordinate(
											Position_D);
								}
								else
								{
									/*
									 if(ball.x()<my.x())
									 {
									 if(fabs(my.y()-ball.y())<CELL_LENGTH)
									 {
									 if(ball.y()>0)
									 {
									 destination=Vector3(ball.x()-3*CELL_LENGTH,ball.y()-2.5*CELL_LENGTH,0);
									 }
									 else if(ball.y()<=0)
									 {
									 destination=Vector3(ball.x()-3*CELL_LENGTH,ball.y()+2.5*CELL_LENGTH,0);
									 }
									 }
									 else
									 {
									 destination=Vector3(ball.x()-3*CELL_LENGTH,ball.y(),0);
									 }
									 }
									 else
									 {
									 if(fabs(ball.y())<3*CELL_LENGTH)
									 {
									 destination=Vector3(ball.x()-3*CELL_LENGTH,ball.y(),0);
									 }
									 else
									 {
									 destination=Vector3(ball.x()-3*CELL_LENGTH,ball.y()/2,0);
									 }
									 }*/

									if (ball.y() > my.y())
									{
										destination = Vector3(ball.x(),
												ball.y() - 1.5 * CELL_LENGTH,0);
									}
									else
									{
										destination = Vector3(ball.x(),
												ball.y() + 1.5 * CELL_LENGTH,0);
									}

								}
							}
						}
					}
				}
				//	    }
			}
		}
	}
	else if (my.x() <= ball.x() && my.y() <= ball.y())
	{
		if (messageParser.GetWhetherPositionBStand() == false)
		{

			destination = wm.GetPositionCoordinate(Position_B);
		}
		else if (messageParser.GetWhetherPositionBStand() == true)
		{

			if (messageParser.GetPositionBNumberByHear() == wm.GetMyNumber())
			{

				destination = wm.GetPositionCoordinate(Position_B);
			}
			else
			{

				if (messageParser.GetWhetherPositionAStand() == false)
				{
					destination = wm.GetPositionCoordinate(Position_A);
				}
				else if (messageParser.GetWhetherPositionAStand() == true)
				{
					if (messageParser.GetPositionANumberByHear()
							== wm.GetMyNumber())
					{
						destination = wm.GetPositionCoordinate(Position_A);
					}
					else
					{
						if (messageParser.GetWhetherPositionCStand() == false)
						{
							destination = wm.GetPositionCoordinate(Position_C);
						}
						else if (messageParser.GetWhetherPositionCStand()
								== true)
						{
							if (messageParser.GetPositionCNumberByHear()
									== wm.GetMyNumber())
							{
								destination = wm.GetPositionCoordinate(
										Position_C);
							}
							else
							{
								/*
								 if(ball.x()<my.x())
								 {
								 if(fabs(my.y()-ball.y())<CELL_LENGTH)
								 {
								 if(ball.y()>0)
								 {
								 destination=Vector3(ball.x()-3*CELL_LENGTH,ball.y()-2.5*CELL_LENGTH,0);
								 }
								 else if(ball.y()<=0)
								 {
								 destination=Vector3(ball.x()-3*CELL_LENGTH,ball.y()+2.5*CELL_LENGTH,0);
								 }
								 }
								 else
								 {
								 destination=Vector3(ball.x()-3*CELL_LENGTH,ball.y(),0);
								 }
								 }
								 else
								 {
								 if(fabs(ball.y())<3*CELL_LENGTH)
								 {
								 destination=Vector3(ball.x()-3*CELL_LENGTH,ball.y(),0);
								 }
								 else
								 {
								 destination=Vector3(ball.x()-3*CELL_LENGTH,ball.y()/2,0);
								 }
								 }
								 */
								if (ball.y() > my.y())
								{
									destination = Vector3(ball.x(),
											ball.y() - 1.5 * CELL_LENGTH,0);
								}
								else
								{
									destination = Vector3(ball.x(),
											ball.y() + 1.5 * CELL_LENGTH,0);
								}
							}
						}
					}
				}
			}
		}
	}

	if (ball.x() > 5 * CELL_LENGTH)
	{
		if (ball.y() > 0)
		{
			if (messageParser.GetWhetherPositionBStand() == false)
			{
				destination = wm.GetPositionCoordinate(Position_B);
			}
			else if (messageParser.GetWhetherPositionBStand() == true)
			{
				if (messageParser.GetPositionBNumberByHear()
						== wm.GetMyNumber())
				{
					destination = wm.GetPositionCoordinate(Position_B);
				}
				else
				{
					if (messageParser.GetWhetherPositionCStand() == false)
					{
						destination = wm.GetPositionCoordinate(Position_C);
					}
					else if (messageParser.GetWhetherPositionCStand() == true)
					{
						if (messageParser.GetPositionCNumberByHear()
								== wm.GetMyNumber())
						{
							destination = wm.GetPositionCoordinate(Position_C);
						}
						else
						{
							if (messageParser.GetWhetherPositionAStand()
									== false)
							{
								destination = wm.GetPositionCoordinate(
										Position_A);
							}
							else if (messageParser.GetWhetherPositionAStand()
									== true)
							{
								if (messageParser.GetPositionANumberByHear()
										== wm.GetMyNumber())
								{
									destination = wm.GetPositionCoordinate(
											Position_A);
								}
								else
								{
									if (messageParser.GetWhetherPositionDStand()
											== false)
									{

										destination = wm.GetPositionCoordinate(
												Position_D);
									}
									else if (messageParser.GetWhetherPositionDStand()
											== true)
									{
										if (messageParser.GetPositionDNumberByHear()
												== wm.GetMyNumber())
										{
											destination =
													wm.GetPositionCoordinate(
															Position_D);
										}
										else
										{
											if (ball.y() > my.y())
											{
												destination =
														Vector3(
																ball.x(),
																ball.y()
																		- 1.5
																				* CELL_LENGTH
																		, 0);
											}
											else
											{
												destination =
														Vector3(
																ball.x(),
																ball.y()
																		+ 1.5
																				* CELL_LENGTH
																		, 0);
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
		else
		{

			if (messageParser.GetWhetherPositionAStand() == false)
			{
				destination = wm.GetPositionCoordinate(Position_A);
			}
			else if (messageParser.GetWhetherPositionAStand() == true)
			{
				if (messageParser.GetPositionANumberByHear()
						== wm.GetMyNumber())
				{
					destination = wm.GetPositionCoordinate(Position_A);
				}
				else
				{
					if (messageParser.GetWhetherPositionDStand() == false)
					{
						destination = wm.GetPositionCoordinate(Position_D);
					}
					else if (messageParser.GetWhetherPositionDStand() == true)
					{
						if (messageParser.GetPositionDNumberByHear()
								== wm.GetMyNumber())
						{
							destination = wm.GetPositionCoordinate(Position_D);
						}
						else
						{
							if (messageParser.GetWhetherPositionBStand()
									== false)
							{
								destination = wm.GetPositionCoordinate(
										Position_B);
							}
							else if (messageParser.GetWhetherPositionBStand()
									== true)
							{
								if (messageParser.GetPositionBNumberByHear()
										== wm.GetMyNumber())
								{
									destination = wm.GetPositionCoordinate(
											Position_B);
								}
								else
								{
									if (messageParser.GetWhetherPositionCStand()
											== false)
									{

										destination = wm.GetPositionCoordinate(
												Position_C);
									}
									else if (messageParser.GetWhetherPositionCStand()
											== true)
									{
										if (messageParser.GetPositionCNumberByHear()
												== wm.GetMyNumber())
										{
											destination =
													wm.GetPositionCoordinate(
															Position_C);
										}
										else
										{
											if (ball.y() > my.y())
											{
												destination =
														Vector3(
																ball.x(),
																ball.y()
																		- 1.5
																				* CELL_LENGTH
																		, 0);
											}
											else
											{
												destination =
														Vector3(
																ball.x(),
																ball.y()
																		+ 1.5
																				* CELL_LENGTH
																		, 0);
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}

	}

	/////cout<<"zzz destination:"<<destination<<endl;

	/////cout<<"Exit runFormation"<<endl;

	return destination;
}
Vector3 Strategy::NewRunFormation()
{
	int MyNumber=wm.GetMyNumber();
	if(MyNumber==CITHear.GetAnum())
	{
		destination = wm.GetPositionCoordinate(Position_A);
	}
	if(MyNumber==CITHear.GetBnum())
		{
			destination = wm.GetPositionCoordinate(Position_B);
		}
	if(MyNumber==CITHear.GetCnum())
		{
			destination = wm.GetPositionCoordinate(Position_C);
		}
	if(MyNumber==CITHear.GetDnum())
		{
			destination = wm.GetPositionCoordinate(Position_D);
		}

	return destination;
}
Vector3 Strategy::runFormation() ///run to position C D firstly
{
//	if (wm.GetBallCoordinate().x() > wm.GetMyCoordinate().x())
//	{
//		return AttackrunFormation();
//	}
//	else
//	{
	return DefenserunFormation();
//	}
}

Action Strategy::standUpWithTurnHead()
{
	stringstream ss("");

	float turnHeadAngle = 0;

	if (turnHeadRight == true)
	{
		turnHeadAngle = -120;
//		cout << "turn head rightRRRRRRRRRRRRRRRRRRRRRRR" << endl;
		if (wm.GetCurrentJointAngle(JID_HEAD_1) < -115)
		{
			turnHeadRight = false;
		}

	}
	else if (turnHeadRight == false)
	{
		turnHeadAngle = 120;
#ifdef AGENT_STRATEGY_OUTPUT
		cout << "turn head leftLLLLLLLLLLLLLLLLLLLLLLLLL" << endl;
#endif
		if (wm.GetCurrentJointAngle(JID_HEAD_1) > 115)
		{
			turnHeadRight = true;
		}
	}

	if (wm.CanSeeTheBall())
	{
#ifdef AGENT_STRATEGY_OUTPUT
		cout << "standUpWithTurnHead can see the ball" << endl;
#endif
		float angleOfHead = wm.GetCurrentJointAngle(JID_HEAD_1);
		turnHeadAngle = angleOfHead + wm.GetMyAngleToBall();
	}
	else
	{
		cout << "standUpWithTurnHead can not not see the ball" << endl;
	}

	Angle Data =
	{ JointInfo(0, 0), JointInfo(-90, 0), JointInfo(-0, 0), JointInfo(90, 0),
			JointInfo(30, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(38.95,
					0), JointInfo(-81.79, 0), JointInfo(46.82, 0), JointInfo(-0,
					0), JointInfo(-45, 0), JointInfo(-90, 0), JointInfo(0, 0),
			JointInfo(-90, 0), JointInfo(-30, 0), JointInfo(0, 0), JointInfo(0,
					0), JointInfo(38.95, 0), JointInfo(-81.79, 0), JointInfo(
					46.82, 0), JointInfo(-0, 0) };

	float gain = 3;
	float Rdistance = -0.03;
	float Rhigh = 0.175;
	float Ldistance = -0.03;
	float Lhigh = 0.175;

	float k, d, b, c, x, y, Rdatui, Rxiaotui, Ldatui, Lxiaotui;

	k = Rhigh * Rhigh + ShankHeight * ShankHeight + Rdistance * Rdistance
			- ThighHeight * ThighHeight;
	d = 4.0 * Rdistance * Rdistance * ShankHeight * ShankHeight
			+ 4.0 * Rhigh * Rhigh * ShankHeight * ShankHeight;
	b = 4.0 * Rdistance * ShankHeight * k;
	c = k * k - 4.0 * Rhigh * Rhigh * ShankHeight * ShankHeight;
	x = (-b + sqrt(b * b - 4.0 * d * c)) / (2.0 * d);
	y = (x * ShankHeight + Rdistance) / ThighHeight;
	Rdatui = mp.Rad2Deg(asin(y));
	Rxiaotui = mp.Rad2Deg(asin(x)) + Rdatui;

	k = Lhigh * Lhigh + ShankHeight * ShankHeight + Ldistance * Ldistance
			- ThighHeight * ThighHeight;
	d = 4.0 * Ldistance * Ldistance * ShankHeight * ShankHeight
			+ 4.0 * Lhigh * Lhigh * ShankHeight * ShankHeight;
	b = 4.0 * Ldistance * ShankHeight * k;
	c = k * k - 4.0 * Lhigh * Lhigh * ShankHeight * ShankHeight;
	x = (-b + sqrt(b * b - 4.0 * d * c)) / (2.0 * d);
	y = (x * ShankHeight + Ldistance) / ThighHeight;
	Ldatui = mp.Rad2Deg(asin(y));
	Lxiaotui = mp.Rad2Deg(asin(x)) + Ldatui;

	float angHead1 = messageParser.mHingeJointSenseMap[JID_HEAD_1].angle;
	float angHead2 = messageParser.mHingeJointSenseMap[JID_HEAD_2].angle;

	float angLarm1 = messageParser.mHingeJointSenseMap[JID_LARM_1].angle;
	float angLarm2 = messageParser.mHingeJointSenseMap[JID_LARM_2].angle;
	float angLarm3 = messageParser.mHingeJointSenseMap[JID_LARM_3].angle;
	float angLarm4 = messageParser.mHingeJointSenseMap[JID_LARM_4].angle;
	float angLleg1 = messageParser.mHingeJointSenseMap[JID_LLEG_1].angle;
	float angLleg2 = messageParser.mHingeJointSenseMap[JID_LLEG_2].angle;
	float angLleg3 = messageParser.mHingeJointSenseMap[JID_LLEG_3].angle;
	float angLleg4 = messageParser.mHingeJointSenseMap[JID_LLEG_4].angle;
	float angLleg5 = messageParser.mHingeJointSenseMap[JID_LLEG_5].angle;
	float angLleg6 = messageParser.mHingeJointSenseMap[JID_LLEG_6].angle;

	float angRarm1 = messageParser.mHingeJointSenseMap[JID_RARM_1].angle;
	float angRarm2 = messageParser.mHingeJointSenseMap[JID_RARM_2].angle;
	float angRarm3 = messageParser.mHingeJointSenseMap[JID_RARM_3].angle;
	float angRarm4 = messageParser.mHingeJointSenseMap[JID_RARM_4].angle;
	float angRleg1 = messageParser.mHingeJointSenseMap[JID_RLEG_1].angle;
	float angRleg2 = messageParser.mHingeJointSenseMap[JID_RLEG_2].angle;
	float angRleg3 = messageParser.mHingeJointSenseMap[JID_RLEG_3].angle;
	float angRleg4 = messageParser.mHingeJointSenseMap[JID_RLEG_4].angle;
	float angRleg5 = messageParser.mHingeJointSenseMap[JID_RLEG_5].angle;
	float angRleg6 = messageParser.mHingeJointSenseMap[JID_RLEG_6].angle;

	ss
			<< mp.HJHead_1Deg(approximate(turnHeadAngle - angHead1) * gain)
					+ mp.HJLarm_1Deg(approximate(-90 - angLarm1) * gain)
					+ mp.HJLarm_2Deg(
							approximate(Data.Larm2.Aimangle - angLarm2) * gain)
					+ mp.HJLarm_3Deg(
							approximate(Data.Larm3.Aimangle - angLarm3) * gain)
					+ mp.HJLarm_4Deg(
							approximate(Data.Larm4.Aimangle - angLarm4) * gain)
					+ mp.HJLleg_1Deg(
							approximate(Data.Lleg1.Aimangle - angLleg1) * gain)
					+ mp.HJLleg_2Deg(
							approximate(Data.Lleg2.Aimangle - angLleg2) * gain)
					+ mp.HJLleg_3Deg(approximate(Ldatui - angLleg3) * gain)
					+ mp.HJLleg_4Deg(approximate(-Lxiaotui - angLleg4) * gain)
					+ mp.HJLleg_5Deg(
							approximate(Lxiaotui - Ldatui - angLleg5) * gain)
					+ mp.HJLleg_6Deg(
							approximate(Data.Lleg6.Aimangle - angLleg6) * gain)
					+ mp.HJHead_2Deg(approximate(-45 - angHead2) * gain)
					+ mp.HJRarm_1Deg(approximate(-90 - angRarm1) * gain)
					+ mp.HJRarm_2Deg(
							approximate(Data.Rarm2.Aimangle - angRarm2) * gain)
					+ mp.HJRarm_3Deg(
							approximate(Data.Rarm3.Aimangle - angRarm3) * gain)
					+ mp.HJRarm_4Deg(
							approximate(Data.Rarm4.Aimangle - angRarm4) * gain)
					+ mp.HJRleg_1Deg(
							approximate(Data.Rleg1.Aimangle - angRleg1) * gain)
					+ mp.HJRleg_2Deg(
							approximate(Data.Rleg2.Aimangle - angRleg2) * gain)
					+ mp.HJRleg_3Deg(approximate(Rdatui - angRleg3) * gain)
					+ mp.HJRleg_4Deg(approximate(-Rxiaotui - angRleg4) * gain)
					+ mp.HJRleg_5Deg(
							approximate(Rxiaotui - Rdatui - angRleg5) * gain)
					+ mp.HJRleg_6Deg(
							approximate(Data.Rleg6.Aimangle - angRleg6) * gain);

	return ss.str();

}

float Strategy::approximate(float f)
{
	return (fabs(f) < EPS) ? 0 : f;
}
#if 1
PassDirection Strategy::estimatePassDirection()
{
	static int number = 0;

	PassDirection pass;
	float myBodyAngleToXAxis = localMyBodyAngleToXAxis;
	Vector3 closestToBallOpponentCoordinate = wm.GetNewOpponentCoordinate(
			localClosestToBallOpponentNumberByVision);
#ifdef AGENT_STRATEGY_OUTPUT
	cout << "inside estimatePassDirection" << endl;


	if (messageParser.GetWhetherPositionCStand() == false)
	{
		cout << "messageParser.GetWhetherPositionCStand()==false" << endl;
	}
	else
	{
		cout << "messageParser.GetWhetherPositionCStand()==true" << endl;
	}
	if (messageParser.GetWhetherPositionDStand() == false)
	{
		cout << "messageParser.GetWhetherPositionDStand()==false" << endl;
	}
	else
	{
		cout << "messageParser.GetWhetherPositionDStand()==true" << endl;
	}

	cout << "messageParser.GetPositionCNumberByHear():"
			<< messageParser.GetPositionCNumberByHear() << endl;
	cout << "messageParser.GetPositionDNumberByHear():"
			<< messageParser.GetPositionDNumberByHear() << endl;

	cout << "wm.GetClosestToBallOpponentNumberByVision():"
			<< localClosestToBallOpponentNumberByVision << endl;
	cout << "closestToBallOpponentCoordinate:"
			<< closestToBallOpponentCoordinate << endl;
	cout
			<< "wm.GetMyBodyAngleToOpponent(wm.GetClosestToBallOpponentNumberByVision()):"
			<< wm.GetMyBodyAngleToOpponent(
					localClosestToBallOpponentNumberByVision) << endl;
#endif
	if (localWhetherCanPassFront == true && fabs(myBodyAngleToXAxis) < 60)
	{
#ifdef AGENT_STRATEGY_OUTPUT
		cout << "001#" << endl;
#endif
		pass = PASS_FRONT;
		if (ball.y() > 3 * CELL_LENGTH && ball.y() <= 4 * CELL_LENGTH)
		{
			if (myBodyAngleToXAxis > 45)
			{
#ifdef AGENT_STRATEGY_OUTPUT
				cout << "002#" << endl;
#endif
				pass = PASS_RIGHT_FRONT;
			}
		}
		else if (ball.y() > 4 * CELL_LENGTH && ball.y() <= 5 * CELL_LENGTH)
		{
			if (myBodyAngleToXAxis > 30)
			{
#ifdef AGENT_STRATEGY_OUTPUT
				cout << "003#" << endl;
#endif
				pass = PASS_RIGHT_FRONT;
			}
		}
		else if (ball.y() > 5 * CELL_LENGTH)
		{
			if (myBodyAngleToXAxis > 0)
			{
#ifdef AGENT_STRATEGY_OUTPUT
				cout << "004#" << endl;
#endif
				pass = PASS_RIGHT_FRONT;
			}
		}

		if (ball.y() < -3 * CELL_LENGTH && ball.y() >= -4 * CELL_LENGTH)
		{
			if (myBodyAngleToXAxis < -45)
			{
#ifdef AGENT_STRATEGY_OUTPUT
				cout << "005#" << endl;
#endif
				pass = PASS_LEFT_FRONT;
			}
		}
		else if (ball.y() < -4 * CELL_LENGTH && ball.y() >= -5 * CELL_LENGTH)
		{
			if (myBodyAngleToXAxis < -30)
			{
#ifdef AGENT_STRATEGY_OUTPUT
				cout << "006#" << endl;
#endif
				pass = PASS_LEFT_FRONT;
			}

		}
		else if (ball.y() < -5 * CELL_LENGTH)
		{
			if (myBodyAngleToXAxis < -0)
			{
#ifdef AGENT_STRATEGY_OUTPUT
				cout << "007#" << endl;
#endif
				pass = PASS_LEFT_FRONT;
			}
		}

	}
	else
	{
#ifdef AGENT_STRATEGY_OUTPUT
		cout << "0#" << endl;
#endif
		if (fabs(myBodyAngleToXAxis) < 45)
		{
#ifdef AGENT_STRATEGY_OUTPUT
			cout << "1#" << endl;
#endif
			if (messageParser.GetWhetherPositionCStand() == true
					&& messageParser.GetWhetherPositionDStand() == true)
			{
				if (my.y() > closestToBallOpponentCoordinate.y())
				{
#ifdef AGENT_STRATEGY_OUTPUT
					cout << "2#" << endl;
#endif
					pass = PASS_LEFT_FRONT;
				}
				else
				{
#ifdef AGENT_STRATEGY_OUTPUT
					cout << "3#" << endl;
#endif
					pass = PASS_RIGHT_FRONT;
				}

				if (ball.y() > 4.5 * CELL_LENGTH)
				{
#ifdef AGENT_STRATEGY_OUTPUT
					cout << "ball.y()>4.5*CELL_LENGTH" << endl;
#endif
					pass = PASS_RIGHT_FRONT;
				}
				else if (ball.y() < -4.5 * CELL_LENGTH)
				{
#ifdef AGENT_STRATEGY_OUTPUT
					cout << "ball.y()<-4.5*CELL_LENGTH" << endl;
#endif
					pass = PASS_LEFT_FRONT;
				}

			}
			else if (messageParser.GetWhetherPositionCStand() == true
					&& messageParser.GetWhetherPositionDStand() == false)
			{
#ifdef AGENT_STRATEGY_OUTPUT
				cout << "4#" << endl;
#endif
				pass = PASS_RIGHT_FRONT;

				if (ball.y() > 4.5 * CELL_LENGTH)
				{
#ifdef AGENT_STRATEGY_OUTPUT
					cout << "ball.y()>4.5*CELL_LENGTH" << endl;
#endif
					pass = PASS_RIGHT_FRONT;
				}
				else if (ball.y() < -4.5 * CELL_LENGTH)
				{
#ifdef AGENT_STRATEGY_OUTPUT
					cout << "ball.y()<-4.5*CELL_LENGTH" << endl;
#endif
					pass = PASS_LEFT_FRONT;
				}

			}
			else if (messageParser.GetWhetherPositionCStand() == false
					&& messageParser.GetWhetherPositionDStand() == true)
			{
#ifdef AGENT_STRATEGY_OUTPUT
				cout << "5#" << endl;
#endif
				pass = PASS_LEFT_FRONT;

				if (ball.y() > 4.5 * CELL_LENGTH)
				{
#ifdef AGENT_STRATEGY_OUTPUT
					cout << "ball.y()>4.5*CELL_LENGTH" << endl;
#endif
					pass = PASS_RIGHT_FRONT;
				}
				else if (ball.y() < -4.5 * CELL_LENGTH)
				{
#ifdef AGENT_STRATEGY_OUTPUT
					cout << "ball.y()<-4.5*CELL_LENGTH" << endl;
#endif
					pass = PASS_LEFT_FRONT;
				}

			}
			else
			{
				if (my.y() > closestToBallOpponentCoordinate.y())
				{
#ifdef AGENT_STRATEGY_OUTPUT
					cout << "6#" << endl;
#endif
					pass = PASS_LEFT_FRONT;
				}
				else
				{
#ifdef AGENT_STRATEGY_OUTPUT
					cout << "7#" << endl;
#endif
					pass = PASS_RIGHT_FRONT;
				}

				if (ball.y() > 4.5 * CELL_LENGTH)
				{
#ifdef AGENT_STRATEGY_OUTPUT
					cout << "ball.y()>4.5*CELL_LENGTH" << endl;
#endif
					pass = PASS_RIGHT_FRONT;
				}
				else if (ball.y() < -4.5 * CELL_LENGTH)
				{
#ifdef AGENT_STRATEGY_OUTPUT
					cout << "ball.y()<-4.5*CELL_LENGTH" << endl;
#endif
					pass = PASS_LEFT_FRONT;
				}

			}
		}
		else if (fabs(myBodyAngleToXAxis) > 45
				&& fabs(myBodyAngleToXAxis) < 135)
		{
			if (myBodyAngleToXAxis > 0)
			{
#ifdef AGENT_STRATEGY_OUTPUT
				cout << "8#" << endl;
#endif
				pass = PASS_RIGHT_FRONT;
			}
			else if (myBodyAngleToXAxis < 0)
			{
#ifdef AGENT_STRATEGY_OUTPUT
				cout << "9#" << endl;
#endif
				pass = PASS_LEFT_FRONT;
			}
		}
		else
		{
			if (my.y() > closestToBallOpponentCoordinate.y())
			{
#ifdef AGENT_STRATEGY_OUTPUT
				cout << "10#" << endl;
#endif
				pass = PASS_LEFT_FRONT;
			}
			else
			{
#ifdef AGENT_STRATEGY_OUTPUT
				cout << "11#" << endl;
#endif
				pass = PASS_RIGHT_FRONT;
			}
		}
	}
#ifdef AGENT_STRATEGY_OUTPUT
	cout << "pass:" << pass << endl;
#endif
	if (CITConf.RightAttack && wm.GetMyNumber() == 2)
	{
		pass = PASS_RIGHT_FRONT;
		//CITConf.RightAttack = false;
	}
#ifdef AGENT_STRATEGY_OUTPUT
	cout << "number" << number++ << endl;
	cout << "pass::" << pass << endl;
#endif
	return pass;
}
#endif

Action Strategy::dealFallingDown()
{
	if (wm.GetMyFallDirection() == D_BACK)
	{
		return basicMotion.DealFallingDown(0);
	}
	else if (wm.GetMyFallDirection() == D_LEFT)
	{
#ifdef AGENT_STRATEGY_OUTPUT
		cout << "wm.GetCurrentJointAngle(JID_LARM_2)  :"
				<< wm.GetCurrentJointAngle(JID_LARM_2) << endl;
#endif
		if (fabs(wm.GetCurrentJointAngle(JID_LARM_2)) < 55)
			return basicMotion.DealFallingDown(1);
		else
			return basicMotion.DealFallingDown(0);
	}
	else if (wm.GetMyFallDirection() == D_RIGHT)
	{
#ifdef AGENT_STRATEGY_OUTPUT
		cout << "wm.GetCurrentJointAngle(JID_RARM_2)  :"
				<< wm.GetCurrentJointAngle(JID_RARM_2) << endl;
#endif
		if (fabs(wm.GetCurrentJointAngle(JID_RARM_2)) < 55)
			return basicMotion.DealFallingDown(2);
		else
			return basicMotion.DealFallingDown(0);
	}
	return basicMotion.DealFallingDown(0);//这种最后出口是有问题的。
}

Action Strategy::kickOff()
{

	Vector3 destinationCoordinate;

	if (wm.CanSeeTheBall() && wm.CanDoLocalizationDirectly())
	{

		turnHeadStrategy(fallDownTurnHead);
#ifdef AGENT_STRATEGY_OUTPUT
		cout << "3333333333333333333333333wm.GetMyBodyAngleToBall():"
				<< wm.GetMyBodyAngleToBall() << endl;

		cout
				<< "66666666666666666666666666666wm.GetClosestToBallOpponentDistanceByVision():"
				<< wm.GetClosestToBallOpponentDistanceByVision() << endl;
#endif
		{
			angleToTurn = wm.GetMyBodyAngleToBall();
			destination = Vector3(0, -0.3, 0);
			theNewWalkSolutions(destination, angleToTurn, topSpeed);
		}

		if (wm.GetMyDistanceToBall() < 1.8
				&& fabs(wm.GetMyBodyAngleToBall()) < 20)
		{
			if (initPass == false)
			{
				newWalk.initPass(); ///should be init before pass ball
				initPass = true;
			}
#ifdef AGENT_STRATEGY_OUTPUT
			cout
					<< "777777777777777777777777777777777777777777PassDirection passDirection=PASS_FRONT;"
					<< endl;
#endif
			PassDirection passDirection = PASS_LEFT_FRONT;
			///	PassDirection passDirection=estimatePassDirection();
			return newWalk.PassBall(passDirection);
		}
		else
		{
			initPass = false;
		}

		if (wm.GetMyDistanceToBall() < 1) ///&&wm.GetCurrentGameTime()<3)
		{
			//	topSpeed=MIDMIN_SPEED;
			//	topSpeed=MIN_SPEED;
			//	topSpeed=MID_SPEED;
		}

	}
	else if (!wm.CanSeeTheBall() && wm.CanDoLocalizationDirectly())
	{
		turnHeadStrategy(fallDownTurnHead);

		angleToTurn = -wm.GetMyBodyAngleToXAxis();
		destination = WalkToDestinationCoordinate(
				wm.GetLastCyclesAverageBallCoordinate());
	}
	else if (wm.CanSeeTheBall() && !wm.CanDoLocalizationDirectly())
	{
		turnHeadStrategy(fallDownTurnHead);

		angleToTurn = -wm.GetMyBodyAngleToXAxis();
		destination = WalkToDestinationCoordinate(
				wm.GetLastCyclesAverageBallCoordinate());

	}
	else if (!wm.CanSeeTheBall() && !wm.CanDoLocalizationDirectly())
	{
		turnHeadStrategy(fallDownTurnHead);

		angleToTurn = -wm.GetMyBodyAngleToXAxis();
		destination = WalkToDestinationCoordinate(
				wm.GetLastCyclesAverageBallCoordinate());

	}

	return NEWWALK(destination, angleToTurn, topSpeed);

}

Vector3 Strategy::standBetweenBallAndMyGoal(float distanceToBall)
{
	float l, x0, y0, L, K, B, a, b, c, mid, x1, x2, x, y;
	L = -localFieldLength / 2;
#ifdef AGENT_STRATEGY_OUTPUT
	cout << "wm.GetFieldLength():" << localFieldLength << endl;
#endif
	/*float ballToGoalMiddleDistance = sqrt(
	 (ball.x() - L) * (ball.x() - L) + ball.y() * ball.y());*/

	l = distanceToBall;

	x0 = ballCoordinate.x();
	y0 = ballCoordinate.y();

	K = (y0) / (x0 - L);
	B = y0 - K * x0;

	a = (L - x0) * (L - x0) + y0 * y0;
	b = -2 * L * y0 * y0 - 2 * x0 * (L - x0) * (L - x0)
			+ 2 * (L - x0) * y0 * y0;
	c = L * L * y0 * y0 + x0 * x0 * (L - x0) * (L - x0)
			+ y0 * y0 * (L - x0) * (L - x0) - 2 * L * y0 * y0 * (L - x0)
			- (L - x0) * (L - x0) * l * l;
#ifdef AGENT_STRATEGY_OUTPUT
	cout << "a:" << a << "  b: " << b << "  c:  " << c << "  (b*b-4*a*c):  "
			<< (b * b - 4 * a * c) << " L:" << L << endl;
#endif
	mid = (b * b - 4 * a * c);

	if (mid < 0.01) ///to avoid nan
	{
		mid = 0;
	}

	x1 = (-b + sqrt(mid)) / 2 / a;
	x2 = (-b - sqrt(mid)) / 2 / a;

	x = x2;
	y = K * x + B;
#ifdef AGENT_STRATEGY_OUTPUT
	cout << "x1:" << x1;
	cout << "x2:" << x2;
	cout << "y:" << y << endl;
#endif
	return Vector3(x, y, 0);
}

Action Strategy::passBall()
{
#if 1
	if (whetherStriker == false)
	{

		if (ball.x() < 5 * CELL_LENGTH )
		{
            if(ball.x() < -4.5 * CELL_LENGTH)
            {
			//	if(wm.GetMyDistanceToBall()<0.6&&fabs(wm.GetMyBodyAngleToBall())<20&&wm.GetClosestToBallOpponentDistanceByVision()<2*CELL_LENGTH)
			if ((localMyDistanceToBall < 0.6 && fabs(localMyBodyAngleToBall) < 20
					&& localClosestToBallOpponentDistanceByVision
							< 1 * CELL_LENGTH )||(localMyDistanceToBall < 0.6 && fabs(localMyBodyAngleToBall) < 20&& (ball.x() < -4 * CELL_LENGTH&&wm.GetMyBodyAngleToXAxis()<90&&wm.GetMyBodyAngleToXAxis()>-90)))
			//	if(wm.GetMyDistanceToBall()<0.8&&fabs(wm.GetMyBodyAngleToBall())<20&&wm.GetClosestToBallTeammateNumberByVision()!=0)

			{
				if (initPass == false)
				{
					newWalk.initPass(); ///should be init before pass ball
					initPass = true;
				}
#ifdef AGENT_STRATEGY_OUTPUT
				cout
						<< "777777777777777777777777777777777777777777PassDirection passDirection=PASS_FRONT;"
						<< endl;
#endif
				PassDirection passDirection = estimatePassDirection();

				return newWalk.PassBall(passDirection);
			}
            }
            else if(ball.x() >= 4.9 * CELL_LENGTH
            		//&&teammateCoordinate(ROLE_VANGUARD)
            	//	&& myCoordinate.x()<myCoordinate.x(ROLE_VANGUARD)
            		//&&myCoordinate.x()<myCoordinate.x(ROLE_VICE_VANGUARD_1) &&myCoordinate.x()<myCoordinate.x(ROLE_VICE_VANGUARD_2)
            		)
            	if(wm.GetClosestToBallTeammateNumberByVision()!=0)
            {
            	if ((localMyDistanceToBall < 0.6 && fabs(localMyBodyAngleToBall) < 20
            						&& localClosestToBallOpponentDistanceByVision
            								< 2 * CELL_LENGTH ))
            					//if(wm.GetMyDistanceToBall()<0.8&&fabs(wm.GetMyBodyAngleToBall())<20&&wm.GetClosestToBallTeammateNumberByVision()!=0)
            				{
            					if (initPass == false)
            					{
            						newWalk.initPass(); ///should be init before pass ball
            						initPass = true;
            					}
            	#ifdef AGENT_STRATEGY_OUTPUT
            					cout
            							<< "777777777777777777777777777777777777777777PassDirection passDirection=PASS_FRONT;"
            							<< endl;
            	#endif
            					PassDirection passDirection = estimatePassDirection();

            					return newWalk.PassBall(passDirection);
            				}
            }

			}
			else
			{
				initPass = false;
			}

		}
		if (ball.x() >= 5 * CELL_LENGTH && fabs(ball.y()) < 2 * CELL_LENGTH)
		{
		if (localMyDistanceToBall < 0.6 && fabs(localMyBodyAngleToBall) < 20
					&& localWhetherCanAttackOppGoal2 == true)
			{
			/*	if (initPass == false)
				{
					newWalk.initPass(); ///should be init before pass ball
					initPass = true;
				}
				PassDirection passDirection = PASS_FRONT;
#ifdef AGENT_STRATEGY_OUTPUT
				cout
						<< "1111111111111111111111inside handle ball,going to pass front"
						<< endl;
#endif
				return newWalk.PassBall(passDirection);*/
			}
			else
			{
				initPass = false;
			}
		}

	else if (whetherStriker == true)
	{
		if (ball.x() >= 5.5 * CELL_LENGTH && fabs(ball.y()) < 1.8 * CELL_LENGTH)
		{
			if (localMyDistanceToBall < 0.6 && fabs(localMyBodyAngleToBall) < 20
					&& localWhetherCanAttackOppGoal2 == true)
			{
				if (initPass == false)
				{
					newWalk.initPass(); ///should be init before pass ball
					initPass = true;
				}
				PassDirection passDirection = PASS_FRONT;
#ifdef AGENT_STRATEGY_OUTPUT
				cout
						<< "1111111111111111111111inside handle ball,going to pass front"
						<< endl;
#endif
				return newWalk.PassBall(passDirection);
			}
			else
			{
				initPass = false;
			}
		}
	}

	if (whetherStriker == false)
	{
		if (ball.x() >= 5 * CELL_LENGTH && fabs(ball.y()) >= 2 * CELL_LENGTH)
		{

			if (ball.x() <= 7 * CELL_LENGTH)
			{
				if (ball.y() > 0)
				{
					if (localMyDistanceToBall < 0.6
							&& fabs(localMyBodyAngleToBall) < 20
							&& (messageParser.GetWhetherPositionCStand() == true
									|| messageParser.GetWhetherPositionBStand()
											== true)
							&& localMyBodyAngleToXAxis < 25
							&& localMyBodyAngleToXAxis > -135)
					{
						if (initPass == false)
						{
							newWalk.initPass(); ///should be init before pass ball
							initPass = true;
						}

						PassDirection passDirection;

						if (localMyBodyAngleToXAxis > -45)
						{
							passDirection = PASS_RIGHT_FRONT;
						}
						else if (localMyBodyAngleToXAxis <= -45
								&& localMyBodyAngleToXAxis >= -90)
						{
					//		passDirection = PASS_FRONT;
						}
						else if (localMyBodyAngleToXAxis < -90)
						{
							passDirection = PASS_LEFT_FRONT;
						}
						///  passDirection=PASS_RIGHT_FRONT;
						//	  passDirection=PASS_RIGHT_FRONT_LESS_STRENGTH;
#ifdef AGENT_STRATEGY_OUTPUT
						cout
								<< "77777777777777777777777777inside handle ball,going to pass to C passDirection:"
								<< passDirection << endl;
#endif
						return newWalk.PassBall(passDirection);
					}
					else
					{
						initPass = false;
					}
				}
				else if (ball.y() <= 0)
				{
					if (localMyDistanceToBall < 0.6
							&& fabs(localMyBodyAngleToBall) < 20
							&& (messageParser.GetWhetherPositionDStand() == true
									|| messageParser.GetWhetherPositionAStand()
											== true)
							&& localMyBodyAngleToXAxis > -25
							&& localMyBodyAngleToXAxis < 135)
					{
						if (initPass == false)
						{
							newWalk.initPass(); ///should be init before pass ball
							initPass = true;
						}
						PassDirection passDirection;

						if (localMyBodyAngleToXAxis < 45)
						{
							passDirection = PASS_LEFT_FRONT;
						}
						else if (localMyBodyAngleToXAxis >= 45
								&& localMyBodyAngleToXAxis <= 90)
						{
						//	passDirection = PASS_FRONT;
						}
						else if (localMyBodyAngleToXAxis > 90)
						{
							passDirection = PASS_RIGHT_FRONT;
						}
						///	  passDirection=PASS_LEFT_FRONT;
						//	  passDirection=PASS_LEFT_FRONT_LESS_STRENGTH;
#ifdef AGENT_STRATEGY_OUTPUT
						cout
								<< "8888888888888888888888888inside handle ball,going to pass to D passDirection:"
								<< passDirection << endl;
#endif
						return newWalk.PassBall(passDirection);
					}
					else
					{
						initPass = false;
					}
				}
			}
			else if (ball.x() > 7 * CELL_LENGTH)
			{
				if (ball.y() > 0)
				{
					if (localMyDistanceToBall < 0.6
							&& fabs(localMyBodyAngleToBall) < 20
							&& (messageParser.GetWhetherPositionCStand() == true
									|| messageParser.GetWhetherPositionBStand()
											== true)
							&& localMyBodyAngleToXAxis < 0
							&& localMyBodyAngleToXAxis > -180)
					{
						if (initPass == false)
						{
							newWalk.initPass(); ///should be init before pass ball
							initPass = true;
						}

						PassDirection passDirection;

						if (localMyBodyAngleToXAxis > -90)
						{
							///	  if(my.y()>3*CELL_LENGTH)
							{
								passDirection = PASS_RIGHT_FRONT;
							}
							///	  else if(my.y()<=3*CELL_LENGTH)
							{
								///	    passDirection=PASS_RIGHT_FRONT_LESS_STRENGTH;
							}
						}
						else if (localMyBodyAngleToXAxis <= -90
								&& localMyBodyAngleToXAxis >= -135)
						{
							passDirection = PASS_FRONT;
						}
						else if (localMyBodyAngleToXAxis < -135)
						{
							///	  if(my.y()>3*CELL_LENGTH)
							{
								passDirection = PASS_LEFT_FRONT;
							}
							///	  else
							{
								///	    passDirection=PASS_LEFT_FRONT_LESS_STRENGTH;
							}
						}
						///	  passDirection=PASS_RIGHT_FRONT;
						//	  passDirection=PASS_RIGHT_FRONT_LESS_STRENGTH;
#ifdef AGENT_STRATEGY_OUTPUT
						cout
								<< "99999999999999999999999999998inside handle ball,going to pass to C passDirection:"
								<< passDirection << endl;
#endif
						return newWalk.PassBall(passDirection);
					}
					else if (localMyDistanceToBall < 0.6
							&& fabs(localMyBodyAngleToBall) < 20
							&& ballCoordinate.y() > 3.5 * CELL_LENGTH
							&& (messageParser.GetWhetherPositionCStand() == true
									|| messageParser.GetWhetherPositionBStand()
											== true))
					{
						if (initPass == false)
						{
							newWalk.initPass(); ///should be init before pass ball
							initPass = true;
						}
						return newWalk.PassBall(PASS_FRONT);

					} ///add by gaojin
					else
					{
						initPass = false;
					}
				}
				else if (ball.y() < 0)
				{
					if (localMyDistanceToBall < 0.6
							&& fabs(localMyBodyAngleToBall) < 20
							&& (messageParser.GetWhetherPositionDStand() == true
									|| messageParser.GetWhetherPositionAStand()
											== true)
							&& localMyBodyAngleToXAxis > 0
							&& localMyBodyAngleToXAxis < 180)
					{
						if (initPass == false)
						{
							newWalk.initPass(); ///should be init before pass ball
							initPass = true;
						}
						PassDirection passDirection;

						if (localMyBodyAngleToXAxis < 90)
						{
								passDirection = PASS_LEFT_FRONT;
						}
						else if (localMyBodyAngleToXAxis >= 90
								&& localMyBodyAngleToXAxis <= 135)
						{
							passDirection = PASS_FRONT;
						}
						else if (localMyBodyAngleToXAxis > 135)
						{
								passDirection = PASS_RIGHT_FRONT;
#ifdef AGENT_STRATEGY_OUTPUT
						cout
								<< "00000000000000000000000000000inside handle ball,going to pass to D passDirection:"
								<< passDirection << endl;
#endif
						}
						return newWalk.PassBall(passDirection);
					}
					else if (localMyDistanceToBall < 0.6
							&& fabs(localMyBodyAngleToBall) < 20
							&& ballCoordinate.y() < -3.5 * CELL_LENGTH
							&& (messageParser.GetWhetherPositionDStand() == true
									|| messageParser.GetWhetherPositionAStand()
											== true))
					{
						if (initPass == false)
						{
							newWalk.initPass(); ///should be init before pass ball
							initPass = true;
						}

						return newWalk.PassBall(PASS_FRONT);

					} ///add by gaojin
					else
					{
						initPass = false;
					}
				}
			}
		}
	}
	else if (whetherStriker == true)
	{
		/*
		 if(ball.x()>8*CELL_LENGTH&&fabs(ball.y())>2*CELL_LENGTH&&(fabs(ball.y())/fabs(ball.x())<8.0))
		 {
		 if(ball.y()>0)
		 {
		 if(localMyDistanceToBall<0.6&&fabs(localMyBodyAngleToBall)<20&&localMyBodyAngleToXAxis<0&&localMyBodyAngleToXAxis>-135)
		 {
		 if(initPass==false)
		 {
		 newWalk.initPass();  ///should be init before pass ball
		 initPass=true;
		 }

		 PassDirection passDirection;

		 //	  passDirection=PASS_RIGHT_FRONT;
		 passDirection=PASS_RIGHT_FRONT_LESS_STRENGTH;
		 cout<<"99999999999999999999999999998inside handle ball,going to pass to C passDirection:"<<passDirection<<endl;
		 return newWalk.PassBall(passDirection);
		 }
		 else
		 {
		 initPass=false;
		 }
		 }
		 else if(ball.y()<0)
		 {
		 if(localMyDistanceToBall<0.6&&fabs(localMyBodyAngleToBall)<20&&localMyBodyAngleToXAxis>0&&localMyBodyAngleToXAxis<135)
		 {
		 if(initPass==false)
		 {
		 newWalk.initPass();  ///should be init before pass ball
		 initPass=true;
		 }
		 PassDirection passDirection;

		 //	  passDirection=PASS_LEFT_FRONT;
		 passDirection=PASS_LEFT_FRONT_LESS_STRENGTH;
		 cout<<"00000000000000000000000000000inside handle ball,going to pass to D passDirection:"<<passDirection<<endl;
		 return newWalk.PassBall(passDirection);
		 }
		 else
		 {
		 initPass=false;
		 }
		 }
		 }*/
	}

#endif
	/*
	 if(wm.GetMyDistanceToBall()<0.6&&fabs(wm.GetMyBodyAngleToBall())<20&&wm.WhetherCanAttackOppGoal2()==true)
	 {
	 PassDirection passDirection;
	 if(ball.y()>0)
	 {
	 passDirection=PASS_RIGHT_FRONT;
	 }
	 else
	 {
	 passDirection=PASS_LEFT_FRONT;
	 }
	 return newWalk.PassBall(passDirection);
	 }
	 else
	 {
	 initPass=false;
	 }*/
	 return this->HandleBall();
}

Action Strategy::goForwardToSaveBall()
{
#ifdef AGENT_STRATEGY_OUTPUT
	cout<<"goForwardToSaveBall"<<endl;
#endif
	int mDisToBallIndex;
	wm.GetMyDistanceToBallSortedIndex(mDisToBallIndex);
	Vector3 destinationCoordinate;
	if (recordDistanceCounter != 0)
	{
		initSplits();
	}
	if (wm.CanSeeTheBall() && wm.CanDoLocalizationByTwoFlags())
	{
#ifdef AGENT_STRATEGY_OUTPUT
		cout<<"wm.CanSeeTheBall() && wm.CanDoLocalizationByTwoFlags()"<<endl;
#endif
		turnHeadStrategy(fallDownTurnHead);
		///	float ballMeToXAxisAngle=wm.GetLastCyclesAverageBallMeToXAxisAngle();
		///	float ballGoalToXAxisAngle=wm.GetLastCyclesAverageBallGoalToXAxisAngle();
		destinationCoordinate = wm.GetLastCyclesAverageBallCoordinate();
		if (wm.GetMyDistanceToDestination(destination) > 2) ///need do some impove
		{
#ifdef AGENT_STRATEGY_OUTPUT
			cout<<"wm.GetMyDistanceToDestination(destination) > 2"<<endl;
#endif
			destination = WalkToDestinationCoordinate(destinationCoordinate);
			angleToTurn = localMyBodyAngleToBall;
		}
		else if (wm.GetMyDistanceToDestination(destination) > 0.7
				&& wm.GetMyDistanceToDestination(destination) <= 2) ///need do some impove
		{
#ifdef AGENT_STRATEGY_OUTPUT
			cout<<"wm.GetMyDistanceToDestination(destination) <= 2"<<endl;
#endif
			destination = WalkToDestinationCoordinate(destinationCoordinate);
			angleToTurn = localMyBodyAngleToBall;
			if (fabs(angleToTurn) < 90)
			{
#ifdef AGENT_STRATEGY_OUTPUT
				cout<<"fabs(angleToTurn) < 90"<<endl;
#endif
				angleToTurn = localMyBodyAngleToBall;
			}
			else
			{
				angleToTurn = 0;
			}
		}
		else if (wm.GetMyDistanceToDestination(destination) < 0.7)
		{
#ifdef AGENT_STRATEGY_OUTPUT
			cout<<"wm.GetMyDistanceToDestination(destination) < 0.7"<<endl;
#endif
			angleToTurn = localLastCyclesAverageBallGoalToXAxisAngle
					- localMyBodyAngleToXAxis;
			if (localWhetherCanAttackOppGoal2 == false)
			{
#ifdef AGENT_STRATEGY_OUTPUT
				cout<<"localWhetherCanAttackOppGoal2 == false"<<endl;
#endif
				destination = WalkToDestinationCoordinate(
						destinationCoordinate);
			}
			else ///if(wm.WhetherCanAttackOppGoal2()==true)         ///can not use,otherwish,it will execute two times
			{
#ifdef AGENT_STRATEGY_OUTPUT
				cout<<"localWhetherCanAttackOppGoal2 == true"<<endl;
#endif
				destination = ballCoordinate;
				topSpeed = MAX_SPEED;
			}
		}
		if (ballCoordinate.x() < 3 && fabs(myCoordinate.y()) < 3
				&& (ballCoordinate.x() > myCoordinate.x()))
		{
#ifdef AGENT_STRATEGY_OUTPUT
			cout<<"ballCoordinate.x() < 3 && fabs(myCoordinate.y()) < 3"<<endl;
#endif
			destination = ballCoordinate;
			angleToTurn = localMyBodyAngleToBall;
			topSpeed = MAX_SPEED;
		}

		if (localMyDistanceToBall < 1.3 && fabs(localMyBodyAngleToBall) < 35)
		{
#ifdef AGENT_STRATEGY_OUTPUT
			cout<<"localMyDistanceToBall < 1.3 && fabs(localMyBodyAngleToBall) < 35"<<endl;
#endif
			PassDirection passDirection;
			if (initPass == false)
			{
				newWalk.initPass(); ///should be init before pass ball
				initPass = true;
			}


			if(wm.GetCurrentGameMode()==PM_GOAL_KICK_Our)
			{
			if (wm.GetMyTeamIndex() == TI_LEFT)
				{
				{
								destination = WalkToDestinationCoordinate(
																					destinationCoordinate );
							//	destination = Vector3(destination.x()+0.04 , destination.y() ,	destination.z());
							if(wm.GetMyAngleToDestination(destination)<0.4)
									topSpeed=MIDMIN_SPEED;
								//	destination = Vector3(destination.x()+0.05 , destination.y() ,	destination.z());
								//	angleToTurn=(wm.GetMyAngleToFlag(VO_GOAL2_R)+wm.GetMyAngleToFlag(VO_GOAL1_R))/2;
								//	destination=	(	destinationCoordinate.x,destinationCoordinate.y,destinationCoordinate.z );
						//		 if (ball.x()>my.x()  &&(wm.CanSeeTheFlag(VO_GOAL1_R) && wm.CanSeeTheFlag(VO_GOAL2_R)))
							//			 return behavior.stopAndShoottingbeforekick();
									/////////////////////////////////////////////////////////////////////////////////////////////////
									if ((localMyDistanceToBall <= 0.21 && fabs(localMyAngleToBall) < 9   //原来为12  0.24
											&& fabs(localMyAngleToBall) > 0 &&(wm.GetMyAngleToFlag(VO_GOAL1_R)	    //&&wm.GetMyAngleToFlag(VO_GOAL2_R)> -25)   //0 -25
											&& ball.x()>my.x() ))
									|| (localMyDistanceToBall <= 0.21 && fabs(localMyAngleToBall) < 9   //原来为12
											&& fabs(localMyAngleToBall) > 0 &&(wm.GetMyAngleToFlag(VO_GOAL2_R)	  )//&&wm.GetMyAngleToFlag(VO_GOAL1_R)<25)  // 0 25
										&& ball.x()>my.x())
						//					||
						//					(localMyDistanceToBall <= 0.22 && fabs(localMyAngleToBall) < 10   //原来为12  0.24
						//								&& fabs(localMyAngleToBall) > 0 &&(wm.GetMyAngleToFlag(VO_GOAL2_L)	 < 0&&wm.GetMyAngleToFlag(VO_GOAL2_L)> -100)
						//								&&ballCoordinate.y() < 0* CELL_LENGTH)
						//						|| (localMyDistanceToBall <= 0.22 && fabs(localMyAngleToBall) < 10   //原来为12
						//								&& fabs(localMyAngleToBall) > 0 &&(wm.GetMyAngleToFlag(VO_GOAL1_L)	 >0&&wm.GetMyAngleToFlag(VO_GOAL1_L)<100)
						//								&&ballCoordinate.y() >  0* CELL_LENGTH)
									)
									{
										beginShoot = true;
									}


									if (beginShoot == false)
									{
										if (myRole == ROLE_VANGUARD)
										{
											if (wm.IsTheBallOutOfShootArea())
											{
												initShootControlParameter();
											}

										}
										else
										{
											if (!wm.CanSeeTheBall())
											{
												initShootControlParameter();
											}
											if (localMyDistanceToBall < 0.175)
											{
												initShootControlParameter();
											}
											if (localMyDistanceToBall < 0.2
													&& fabs(localMyAngleToBall) > 35)
											{
												initShootControlParameter();
											}
											if (wm.EstimateWhetherUseHalfWalk() == true)
											{
												initShootControlParameter();
											}
										}
									//return prepareForShootting();
										if ((localMyDistanceToBall <= 0.30 && fabs(localMyAngleToBall) < 10   //原来为12  0.24
																								&& fabs(localMyAngleToBall) > 0 &&(wm.GetMyAngleToFlag(VO_GOAL2_R)	   )  //&&wm.GetMyAngleToFlag(VO_GOAL2_R)> -25)   //0 -25
																								&& ball.x()>my.x())
																						|| (localMyDistanceToBall <= 0.30 && fabs(localMyAngleToBall) < 10   //原来为12
																								&& fabs(localMyAngleToBall) > 0 &&(wm.GetMyAngleToFlag(VO_GOAL1_R)	  )//&&wm.GetMyAngleToFlag(VO_GOAL1_R)<25)  // 0 25
																							&& ball.x()>my.x()))
									return prepareShootingForFreeKick();
								//		return HandleBall();
									}
									else
									{
								//		if (localMyDistanceToBall > 0.3
								//				|| fabs(this->localMyBodyAngleToXAxis) > 20)
								//		{
								//			finishKick = true;
								//			initShootControlParameter();
								//		}
										if (gaitStoped == true)
										{
								//			if (timeCounter >= 98)
								//				finishKick = true;

											if (rigthFootShoot)
												//	return basicMotion.ShootingFromA();
												return basicMotion.RoboCansLefttoRight4();
											//	return basicMotion.NexLTest();

											//	return basicMotion.RightFootShootingBallCIT();
													//	rightFootShootingBallCIT();
											else
											//	return basicMotion.LeftFootShootingBallCIT();
										//	return basicMotion.NexRTest();
												//return basicMotion.ShootingFromARight();
												return basicMotion.RoboCansRighttoLeft4();
										}
										else
										{
											if (newWalk.GetWalkCounter() == 7)
											{
												gaitStoped = true;
												basicMotion.SetTimeCounter(0);
												if (localMyAngleToBall > 0)
													rigthFootShoot = false;
												else
													rigthFootShoot = true;
											}
									//		return prepareForShootting();
											if ((localMyDistanceToBall <= 0.30 && fabs(localMyAngleToBall) < 10   //原来为12  0.24
																		&& fabs(localMyAngleToBall) > 0 &&(wm.GetMyAngleToFlag(VO_GOAL2_R)	   )  //&&wm.GetMyAngleToFlag(VO_GOAL2_R)> -25)   //0 -25
																&& ball.x()>my.x())
																|| (localMyDistanceToBall <= 0.30 && fabs(localMyAngleToBall) < 10   //原来为12
																		&& fabs(localMyAngleToBall) > 0 &&(wm.GetMyAngleToFlag(VO_GOAL1_R)	  )//&&wm.GetMyAngleToFlag(VO_GOAL1_R)<25)  // 0 25
																	&& ball.x()>my.x()))
										return prepareShootingForFreeKick();
										//	return HandleBall();
										}
									}
						}
				}
			else
			{
//////////////////////////////////////
				{
											destination = WalkToDestinationCoordinate(
																								destinationCoordinate );
										//	destination = Vector3(destination.x()+0.04 , destination.y() ,	destination.z());
										if(wm.GetMyAngleToDestination(destination)<0.4)
											topSpeed=MIDMIN_SPEED;
											//	destination = Vector3(destination.x()+0.05 , destination.y() ,	destination.z());
											//	angleToTurn=(wm.GetMyAngleToFlag(VO_GOAL2_R)+wm.GetMyAngleToFlag(VO_GOAL1_R))/2;
											//	destination=	(	destinationCoordinate.x,destinationCoordinate.y,destinationCoordinate.z );
									//		 if (ball.x()>my.x()  &&(wm.CanSeeTheFlag(VO_GOAL1_R) && wm.CanSeeTheFlag(VO_GOAL2_R)))
										//			 return behavior.stopAndShoottingbeforekick();
												/////////////////////////////////////////////////////////////////////////////////////////////////
												if ((localMyDistanceToBall <= 0.21 && fabs(localMyAngleToBall) < 9   //原来为12  0.24
														&& fabs(localMyAngleToBall) > 0 &&(wm.GetMyAngleToFlag(VO_GOAL1_L)	    //&&wm.GetMyAngleToFlag(VO_GOAL2_R)> -25)   //0 -25
														&& ball.x()>my.x() ))
												|| (localMyDistanceToBall <= 0.21 && fabs(localMyAngleToBall) < 9   //原来为12
														&& fabs(localMyAngleToBall) > 0 &&(wm.GetMyAngleToFlag(VO_GOAL2_L)	  )//&&wm.GetMyAngleToFlag(VO_GOAL1_R)<25)  // 0 25
													&& ball.x()>my.x())
									//					||
									//					(localMyDistanceToBall <= 0.22 && fabs(localMyAngleToBall) < 10   //原来为12  0.24
									//								&& fabs(localMyAngleToBall) > 0 &&(wm.GetMyAngleToFlag(VO_GOAL2_L)	 < 0&&wm.GetMyAngleToFlag(VO_GOAL2_L)> -100)
									//								&&ballCoordinate.y() < 0* CELL_LENGTH)
									//						|| (localMyDistanceToBall <= 0.22 && fabs(localMyAngleToBall) < 10   //原来为12
									//								&& fabs(localMyAngleToBall) > 0 &&(wm.GetMyAngleToFlag(VO_GOAL1_L)	 >0&&wm.GetMyAngleToFlag(VO_GOAL1_L)<100)
									//								&&ballCoordinate.y() >  0* CELL_LENGTH)
												)
												{
													beginShoot = true;
												}


												if (beginShoot == false)
												{
													if (myRole == ROLE_VANGUARD)
													{
														if (wm.IsTheBallOutOfShootArea())
														{
															initShootControlParameter();
														}

													}
													else
													{
														if (!wm.CanSeeTheBall())
														{
															initShootControlParameter();
														}
														if (localMyDistanceToBall < 0.175)
														{
															initShootControlParameter();
														}
														if (localMyDistanceToBall < 0.2
																&& fabs(localMyAngleToBall) > 35)
														{
															initShootControlParameter();
														}
														if (wm.EstimateWhetherUseHalfWalk() == true)
														{
															initShootControlParameter();
														}
													}
												//return prepareForShootting();
													if ((localMyDistanceToBall <= 0.30 && fabs(localMyAngleToBall) < 10   //原来为12  0.24
																											&& fabs(localMyAngleToBall) > 0 &&(wm.GetMyAngleToFlag(VO_GOAL2_L)	   )  //&&wm.GetMyAngleToFlag(VO_GOAL2_R)> -25)   //0 -25
																											&& ball.x()>my.x())
																									|| (localMyDistanceToBall <= 0.30 && fabs(localMyAngleToBall) < 10   //原来为12
																											&& fabs(localMyAngleToBall) > 0 &&(wm.GetMyAngleToFlag(VO_GOAL1_L)	  )//&&wm.GetMyAngleToFlag(VO_GOAL1_R)<25)  // 0 25
																										&& ball.x()>my.x()))
												return prepareShootingForFreeKick();
											//		return HandleBall();
												}
												else
												{
											//		if (localMyDistanceToBall > 0.3
											//				|| fabs(this->localMyBodyAngleToXAxis) > 20)
											//		{
											//			finishKick = true;
											//			initShootControlParameter();
											//		}
													if (gaitStoped == true)
													{
											//			if (timeCounter >= 98)
											//				finishKick = true;

														if (rigthFootShoot)
																return basicMotion.ShootingFromA();
														//	return basicMotion.NexLTest();

														//	return basicMotion.RightFootShootingBallCIT();
																//	rightFootShootingBallCIT();
														else
														//	return basicMotion.LeftFootShootingBallCIT();
													//	return basicMotion.NexRTest();
															return basicMotion.ShootingFromARight();
													}
													else
													{
														if (newWalk.GetWalkCounter() == 7)
														{
															gaitStoped = true;
															basicMotion.SetTimeCounter(0);
															if (localMyAngleToBall > 0)
																rigthFootShoot = false;
															else
																rigthFootShoot = true;
														}
												//		return prepareForShootting();
														if ((localMyDistanceToBall <= 0.30 && fabs(localMyAngleToBall) < 10   //原来为12  0.24
																					&& fabs(localMyAngleToBall) > 0 &&(wm.GetMyAngleToFlag(VO_GOAL2_L)	   )  //&&wm.GetMyAngleToFlag(VO_GOAL2_R)> -25)   //0 -25
																			&& ball.x()>my.x())
																			|| (localMyDistanceToBall <= 0.30 && fabs(localMyAngleToBall) < 10   //原来为12
																					&& fabs(localMyAngleToBall) > 0 &&(wm.GetMyAngleToFlag(VO_GOAL1_L)	  )//&&wm.GetMyAngleToFlag(VO_GOAL1_R)<25)  // 0 25
																				&& ball.x()>my.x()))
													return prepareShootingForFreeKick();
													//	return HandleBall();
													}
												}
									}
				////////////////////////////////////
			}
			return NEWWALK(destination, angleToTurn, topSpeed);
			}

			passDirection = estimatePassDirection();
			return newWalk.PassBall(passDirection);
		}
		else
		{
			initPass = false;
			return NEWWALK(destination, angleToTurn, topSpeed);
		}

	}
	else if (!wm.CanSeeTheBall() && wm.CanDoLocalizationByTwoFlags())
	{
		turnHeadStrategy(fallDownTurnHead);
		angleToTurn = -localMyBodyAngleToXAxis;
		destination = WalkToDestinationCoordinate(
				Vector3(0.5*FORMCELL_LENGTH-wm.GetFieldLength()/2,0,0));
	}
	else if (wm.CanSeeTheBall() && !wm.CanDoLocalizationByTwoFlags())
	{
		turnHeadStrategy(fallDownTurnHead);
		angleToTurn = -localMyBodyAngleToXAxis;
		destination = WalkToDestinationCoordinate(
				Vector3(0.5*FORMCELL_LENGTH-wm.GetFieldLength()/2,0,0));
	}
	else if (!wm.CanSeeTheBall() && !wm.CanDoLocalizationByTwoFlags())
	{
		turnHeadStrategy(fallDownTurnHead);
		angleToTurn = -localMyBodyAngleToXAxis;
		destination = WalkToDestinationCoordinate(
				Vector3(0.5*FORMCELL_LENGTH-wm.GetFieldLength()/2,0,0));
	}
#ifdef AGENT_STRATEGY_OUTPUT
	cout<<"destination::"<<destination<<endl;
	cout<<"angleToTurn::"<<angleToTurn<<endl;
	cout<<"topSpeed::"<<topSpeed<<endl;
#endif
	if (CITConf.GoailDrawer)
			{
				if(wm.GetMyNumber()==1)
				{
					string n1 = wm.GetMyTeamName()+"Goail.SaveBall." + Convert::ToString(wm.GetMyNumber());
					RGBDraw rgb(0.4, 0.2, 0.6);
					CITMDrawer.drawPoint(destination, 3, rgb, &n1);
					CITMDrawer.UpdateDrawer(&n1);
				}
			}
	return NEWWALK(destination, angleToTurn, topSpeed);
}


void Strategy::updateLocalVariables()
{
	localMyDistanceToBall = wm.GetMyDistanceToBall();

	localMyBodyAngleToBall = wm.GetMyBodyAngleToBall();

	my = wm.GetMyCoordinate();

	myCoordinate = my;

	ball = wm.GetBallCoordinate();

	ballCoordinate = ball;

	localMyFaceAngleToBall = wm.GetMyAngleToBall();

	localMyFaceAngleToBall = wm.GetMyAngleToBall();

	localMyBodyAngleToXAxis = wm.GetMyBodyAngleToXAxis();

	localLastCyclesAverageBodyToXAngle = wm.GetLastCyclesAverageBodyToXAngle();

	localLastCyclesAverageBallMeToXAxisAngle =
			wm.GetLastCyclesAverageBallMeToXAxisAngle();

	localMyHeadAngleToXAxis = wm.GetMyHeadAngleToXAxis();

	localBodyToX = wm.GetBodyToX();

	localTheBallStopCoordinate = wm.GetTheBallStopCoordinate();

	localLastCyclesAverageBallGoalToXAxisAngle =
			wm.GetLastCyclesAverageBallGoalToXAxisAngle();

	localWhetherCanAttackOppGoal2 = wm.WhetherCanAttackOppGoal2();

	localCurrentGameMode = wm.GetCurrentGameMode();

	localClosestToBallOpponentNumberByVision =
			wm.GetClosestToBallOpponentNumberByVision();

	localClosestToBallOpponentDistanceByVision =
			wm.GetClosestToBallOpponentDistanceByVision();

	localLastCyclesAverageBallMeXDifference =
			wm.GetLastCyclesAverageBallMeXDifference();

	localLastCyclesAverageBallMeYDifference =
			wm.GetLastCyclesAverageBallMeYDifference();

	localFieldLength = wm.GetFieldLength();

	localFieldWidth = wm.GetFieldWidth();

	localLastCyclesAverageTurnHeadAngle =
			newWalk.GetLastCyclesAverageTurnHeadAngle();

	localCurrentJointAngleJID_HEAD_1 = wm.GetCurrentJointAngle(JID_HEAD_1);

	localMyAngleToBall = wm.GetMyAngleToBall();

	localBallCoordinateForRunFormation =
			wm.GetLastCyclesAverageBallCoordinateForRunFormation();

	localWhetherCanPassFront = wm.WhetherCanPassFront();

	localLastCyclesAverageHorizontalTurnHeadAngle =
			wm.GetLastCyclesAverageHorizontalTurnHeadAngle();

}

void Strategy::third(double x0, double y0, double x1, double y1)
{
	//cout << "起点坐标：" <<x0<<","<<y0<<" 终点坐标："<<x1<<","<<y1<<endl;
//double theta = atan((y1 - y0) / (x1 - x0));
	// double thetaAngle = theta * 180 / PI;
//	cout << "给定两点的转角：" << thetaAngle <<endl;
//double sumAngle = theta + PI / 3;
//	cout << "旋转后的边的转角：" << (thetaAngle + 60) <<endl;
//double dist = sqrt((y1 - y0) * (y1 - y0) + (x1 - x0) * (x1 - x0));
//	cout << "点0到点1的距离：" << dist <<endl;
	// double x2 = x0 + dist * cos(sumAngle);
	// double y2 = y0 + dist * sin(sumAngle);
//	cout<< "x2 = " << x2 << " , y2 = " << y2 <<endl;
//	cout << "点0到点2的距离：" << sqrt((y2 - y0)*(y2 - y0) + (x2 - x0)*(x2 - x0)) <<endl;
	//cout << "点1到点2的距离：" << sqrt((y2 - y1)*(y2 - y1) + (x2 - x1)*(x2 - x1)) <<endl;
}

bool Strategy::GetWhetherStriker()
{
	return whetherStriker;
}

void Strategy::SetWhetherStriker(bool res)
{
	whetherStriker = res;
}

bool Strategy::whetherEnhanceDefence()
{
	bool res = true;
	for (int i = 0; i < 3; i++)
	{
		if (messageParser.GetOpponetTeamName() == opponentTeamName[i])
		{
			res = true;
		}
	}

	return res;

}

Action Strategy::slideTackleToSaveBall()
{
if(CITConf.slideTackle)
{
	if (CITstandup.GetbeginStandUp())
	{
		basicMotion.SetTimeCounter(0);
		CITstandup.SetbeginStandUp(false);
	}
	if (basicMotion.GetTimeCounter() >= 40)
	{
		CITstandup.SetbeginStandUp(true);
		CITstandup.SetfallDown(true);
		slidedToSaveBall = false;
		justAfterSplits = true;
	}
	if (slidedDirection == Left)
		return basicMotion.SlideTackle(Left);
	else
		return basicMotion.SlideTackle(Right);
}
else
{
	destination=ball;
	topSpeed=MAX_SPEED;
	return NEWWALK(destination, angleToTurn, topSpeed);
	}
}

bool Strategy::WhetherBallAndMeInTwoLineArea() ///判断是否符合 处理边线球的条件
{
//	Vector3 MyCoordinate = wm.GetMyCoordinate();
	Vector3 BallCoordinate = wm.GetLastCyclesAverageBallCoordinate();
	bool InTwoLineArea;

	if (fabs(BallCoordinate.y()) >= 4.0 * CELL_LENGTH
			&& BallCoordinate.x() < 4 * CELL_LENGTH
			)
		InTwoLineArea = true;
	else
		InTwoLineArea = false;
	return InTwoLineArea;

}

Vector3 Strategy::CalcDestinationIfOpponentBlockMe(Vector3 destination,
		int OpponentNumber) ///if opponent or myteammate  block me
//it will calc a destination to avoid opponent
{
	//cout << "here is opponentNum block me!!!" << OpponentNumber << endl;
	int length_1, length_2;
	if (myRole == ROLE_VANGUARD)
	{
		length_1 = 0.5;
		length_2 = 0.35;
	}
	else
	{
		length_1 = 1.25;
		length_2 = 0.5;
	}

	Vector3 OpponentCoordinate = wm.GetNewAverageOpponentCoordinate(
			OpponentNumber);
	//cout << "here is OpponentCoordinate" << OpponentCoordinate << endl;
	float angle = wm.WhetherOpponentInMyWayToDestination(OpponentCoordinate, my,
			destination);
	float myDistanceToOpponent = sqrt(
			(my.x() - OpponentCoordinate.x())
					* (my.x() - OpponentCoordinate.x())
					+ (my.y() - OpponentCoordinate.y())
							* (my.y() - OpponentCoordinate.y()));
	//cout << "here is angle:" << angle << endl;
	cout<<"(teammateCoordinate-wm.GetMyCoordinate()).xymod()::"<<(OpponentCoordinate-wm.GetMyCoordinate()).xymod()<<endl;
	if (fabs(angle) < 30||(OpponentCoordinate-wm.GetMyCoordinate()).xymod()<1)
	{
		//cout << "Opponent Block me!!!" << endl;
		if (myDistanceToOpponent <= length_1 && myDistanceToOpponent > length_2)
		{
			float destination_x, destination_y;
			if (destination.y() >= my.y())
			{
				destination_x =
						my.x()
								- length_1
										* sqrt(
												1
														/ (1
																+ ((OpponentCoordinate.x()
																		- my.x())
																		/ (OpponentCoordinate.y()
																				- my.y()))
																		* ((OpponentCoordinate.x()
																				- my.x())
																				/ (OpponentCoordinate.y()
																						- my.y()))));
				destination_y =
						my.y()
								+ (OpponentCoordinate.x() - my.x())
										/ (OpponentCoordinate.y() - my.y())
										* length_1
										* sqrt(
												1
														/ (1
																+ ((OpponentCoordinate.x()
																		- my.x())
																		/ (OpponentCoordinate.y()
																				- my.y()))
																		* ((OpponentCoordinate.x()
																				- my.x())
																				/ (OpponentCoordinate.y()
																						- my.y()))));
			}
			else if (destination.y() < my.y())
			{
				destination_x =
						my.x()
								+ length_1
										* sqrt(
												1
														/ (1
																+ ((OpponentCoordinate.x()
																		- my.x())
																		/ (OpponentCoordinate.y()
																				- my.y()))
																		* ((OpponentCoordinate.x()
																				- my.x())
																				/ (OpponentCoordinate.y()
																						- my.y()))));
				destination_y =
						my.y()
								- (OpponentCoordinate.x() - my.x())
										/ (OpponentCoordinate.y() - my.y())
										* length_1
										* sqrt(
												1
														/ (1
																+ ((OpponentCoordinate.x()
																		- my.x())
																		/ (OpponentCoordinate.y()
																				- my.y()))
																		* ((OpponentCoordinate.x()
																				- my.x())
																				/ (OpponentCoordinate.y()
																						- my.y()))));
			}
			destination = Vector3(destination_x, destination_y,
					destination.z());
#ifdef AGENT_STRATEGY_OUTPUT
			cout << "here is avoidance opponent111:::" << destination << endl;
#endif
		}
		else if (myDistanceToOpponent <= length_2)
		{
			if (my.x() <= destination.x())
			{
				if (my.y() <= destination.y())
				{
					destination = Vector3(my.x() - length_2, my.y() + length_2,
							destination.z());
#ifdef AGENT_STRATEGY_OUTPUT
					cout << "here is avoidance opponent222:::" << destination
							<< endl;
#endif
				}
				else if (my.y() > destination.y())
				{
					destination = Vector3(my.x() - length_2, my.y() - length_2,
							destination.z());
#ifdef AGENT_STRATEGY_OUTPUT
					cout << "here is avoidance opponent333:::" << destination
							<< endl;
#endif
				}
			}
			else if (my.x() > destination.x())
			{
				if (my.y() <= destination.y())
				{
					destination = Vector3(my.x() + length_2, my.y() + length_2,
							destination.z());
#ifdef AGENT_STRATEGY_OUTPUT
					cout << "here is avoidance opponent444:::" << destination
							<< endl;
#endif
				}
				else if (my.y() > destination.y())
				{
					destination = Vector3(my.x() + length_2, my.y() - length_2,
							destination.z());
#ifdef AGENT_STRATEGY_OUTPUT
					cout << "here is avoidance opponent555:::" << destination
							<< endl;
#endif
				}
			}
		}

	}
	return destination;
}

Vector3 Strategy::CalcDestinationIfTeamMateBlockMe(Vector3 destination,
		int teammateNumber) ///if teammate block me
///it will calc a destination to avoid teammate
{
	Vector3 teammateCoordinate = wm.GetNewTeammateCoordinate(
			teammateNumber);
	float angle = wm.WhetherTeammateInMyWayToDestination(teammateCoordinate, my,
			destination);
#ifdef AGENT_STRATEGY_OUTPUT
	cout << "wm.WhetherMyTeammatesBlockMe()==true  angle:" << angle << endl;
#endif
	/*if (fabs(angle) < 30)
	 {
	 ///  float destinationMeToXAxisAngle=wm.GetDestinationMeToXAxisAngle(destinationCoordinate);
	 float x0 = my.x();
	 float y0 = my.y();
	 float x1 = teammateCoordinate.x();
	 float y1 = teammateCoordinate.y();

	 float theta = atan((y1 - y0) / (x1 - x0));
	 //float thetaAngle = theta * 180 / PI;
	 cout << "给定两点的转角：" << thetaAngle <<endl;
	 float sumAngle = theta + PI / 3;
	 cout << "旋转后的边的转角：" << (thetaAngle + 60) <<endl;
	 float dist = sqrt(
	 (y1 - y0) * (y1 - y0) + (x1 - x0) * (x1 - x0));
	 cout << "点0到点1的距离：" << dist <<endl;
	 float x2 = x0 + (dist + 0.5 * CELL_LENGTH) * cos(sumAngle);
	 float y2 = y0 + (dist + 0.5 * CELL_LENGTH) * sin(sumAngle);

	 destinationCoordinate = Vector3(x2, y2, 0);
	 ///  topSpeed=MIDMIN_SPEED;
	 }*/
	///return basicMotion.InitStandUpPose();
	float myDistanceToTeamMate = sqrt(
			(my.x() - teammateCoordinate.x())
					* (my.x() - teammateCoordinate.x())
					+ (my.y() - teammateCoordinate.y())
							* (my.y() - teammateCoordinate.y()));
#ifdef AGENT_STRATEGY_OUTPUT
	cout<<"(teammateCoordinate-wm.GetMyCoordinate()).xymod()::"<<(teammateCoordinate-wm.GetMyCoordinate()).xymod()<<endl;
#endif
	if (fabs(angle) < 30||(teammateCoordinate-wm.GetMyCoordinate()).xymod()<1)
	{
		//cout << "Opponent Block me!!!" << endl;
		if (myDistanceToTeamMate <= 1.25 && myDistanceToTeamMate > 0.5)
		{
			float destination_x, destination_y;
			if (destination.y() >= my.y())
			{
				destination_x =
						my.x()
								- 1.25
										* sqrt(
												1
														/ (1
																+ ((teammateCoordinate.x()
																		- my.x())
																		/ (teammateCoordinate.y()
																				- my.y()))
																		* ((teammateCoordinate.x()
																				- my.x())
																				/ (teammateCoordinate.y()
																						- my.y()))));
				destination_y =
						my.y()
								+ (teammateCoordinate.x() - my.x())
										/ (teammateCoordinate.y() - my.y())
										* 1.25
										* sqrt(
												1
														/ (1
																+ ((teammateCoordinate.x()
																		- my.x())
																		/ (teammateCoordinate.y()
																				- my.y()))
																		* ((teammateCoordinate.x()
																				- my.x())
																				/ (teammateCoordinate.y()
																						- my.y()))));

			}
			else if (destination.y() < my.y())
			{
				destination_x =
						my.x()
								+ 1.25
										* sqrt(
												1
														/ (1
																+ ((teammateCoordinate.x()
																		- my.x())
																		/ (teammateCoordinate.y()
																				- my.y()))
																		* ((teammateCoordinate.x()
																				- my.x())
																				/ (teammateCoordinate.y()
																						- my.y()))));
				destination_y =
						my.y()
								- (teammateCoordinate.x() - my.x())
										/ (teammateCoordinate.y() - my.y())
										* 1.25
										* sqrt(
												1
														/ (1
																+ ((teammateCoordinate.x()
																		- my.x())
																		/ (teammateCoordinate.y()
																				- my.y()))
																		* ((teammateCoordinate.x()
																				- my.x())
																				/ (teammateCoordinate.y()
																						- my.y()))));
			}

			destination = Vector3(destination_x, destination_y,
					destination.z());
#ifdef AGENT_STRATEGY_OUTPUT
			cout << "here is avoidance teammate111:::" << destination << endl;
#endif
		}
		else if (myDistanceToTeamMate <= 0.5)
		{
			if (my.x() <= destination.x())
			{
				if (my.y() <= destination.y())
				{
					destination = Vector3(my.x() - 0.5, my.y() + 0.5,
							destination.z());
#ifdef AGENT_STRATEGY_OUTPUT
					cout << "here is avoidance teammate222:::" << destination
							<< endl;
#endif
				}
				else if (my.y() > destination.y())
				{
					destination = Vector3(my.x() - 0.5, my.y() - 0.5,
							destination.z());
#ifdef AGENT_STRATEGY_OUTPUT
					cout << "here is avoidance teammate333:::" << destination
							<< endl;
#endif
				}
			}
			else if (my.x() > destination.x())
			{
				if (my.y() <= destination.y())
				{
					destination = Vector3(my.x() + 0.5, my.y() + 0.5,
							destination.z());
#ifdef AGENT_STRATEGY_OUTPUT
					cout << "here is avoidance teammate444:::" << destination
							<< endl;
#endif
				}
				else if (my.y() > destination.y())
				{
					destination = Vector3(my.x() + 0.5, my.y() - 0.5,
							destination.z());
#ifdef AGENT_STRATEGY_OUTPUT
					cout << "here is avoidance teammate555:::" << destination
							<< endl;
#endif
				}
			}
		} //cout << "here is destination!!!" << destination << endl;
		  //topSpeed = MIN_SPEED;
	}
	return destination;
}

///Fuzzy Formation Strategy 算法基于《Robocup 中模糊阵型策略的实现》 Author:梅传根 刘祚时 童俊华 有修改，原文有错误，在求bj时
OffensiveAndDefensiveRating Strategy::OffensiveAndDefensiveDegree() ///用于根据目前场上的状况，决定各种角色的人数
{
	/*表示程度*/
	enum AreaNumber
	{
		Area_A1 = 0, Area_A2 = 1, Area_A3 = 2, Area_A4 = 3
	};

	enum DistanceDegree
	{
		D_Degree_D1 = 0, D_Degree_D2 = 1, D_Degree_D3 = 2
	};

	enum XDegree
	{
		X_Degree_X1 = 0, X_Degree_X2 = 1, X_Degree_X3 = 2, X_Degree_X4 = 3
	};

	enum AngleDegree
	{
		A_Degree_A1 = 0, A_Degree_A2 = 1, A_Degree_A3 = 2, A_Degree_A4 = 3
	};
	/////////////////////////////////////////////////////
	/*判断当前球属于哪个区域*/
	AreaNumber areaNumber;
	if (ballCoordinate.x() >= 0)
	{
		if (ballCoordinate.x() >= 4.0 * CELL_LENGTH)
		{
			areaNumber = Area_A4;
		}
		else
		{
			areaNumber = Area_A3;
		}
	}
	else
	{
		if (ballCoordinate.x() < -5.0 * CELL_LENGTH
				&& fabs(ballCoordinate.y()) < 4.0 * CELL_LENGTH)
		{
			areaNumber = Area_A1;
		}
		else
		{
			areaNumber = Area_A2;
		}
	}

	/*求出敌方所有人到球的距离的和的平均值*/
	float opponentAverageDistanceToBall, opponentTotalDistanceToBall = 0;
	for (int i = 1; i <= PLAYERNUMBER; i++)
	{
		opponentTotalDistanceToBall += wm.getDistanceOppenentToBall(i);
	}
	opponentAverageDistanceToBall = opponentTotalDistanceToBall
			/ PLAYERNUMBER;
	//cout << "here is ballCoordinate::::::::::::" << ballCoordinate << endl;
///	cout << "here is test opponentAverageDistanceToBall::::::::::::::::"
//			<< opponentAverageDistanceToBall << endl;

	/*判断地方离球的距离属于哪个区间，从而可知道地方的控球能力*/
	DistanceDegree distanceDegree;
	if (opponentAverageDistanceToBall <= 2.5)
	{
		distanceDegree = D_Degree_D1;
	}
	else if (opponentAverageDistanceToBall > 2.5
			&& opponentAverageDistanceToBall < 5.0)
	{
		distanceDegree = D_Degree_D2;
	}
	else
	{
		distanceDegree = D_Degree_D3;
	}

	/*求出敌方所有人X坐标的和的平均值*/
	float opponentAverageX_Coordinate, opponentTotalX_Coordinate;
	for (int i = 1; i <= PLAYERNUMBER; i++)
	{
		opponentTotalX_Coordinate += wm.GetNewOpponentCoordinate(i).x();
	}
	opponentAverageX_Coordinate = opponentTotalX_Coordinate
			/ PLAYERNUMBER;

	/*判断对方的X坐标属于哪个区间*/
	XDegree xDegree;
	if (opponentAverageX_Coordinate < -4.5)
	{
		xDegree = X_Degree_X1;
	}
	else if (opponentAverageX_Coordinate >= -4.5
			&& opponentAverageX_Coordinate < 0)
	{
		xDegree = X_Degree_X2;
	}
	else if (opponentAverageX_Coordinate >= 0
			&& opponentAverageX_Coordinate < 4.5)
	{
		xDegree = X_Degree_X3;
	}
	else if (opponentAverageX_Coordinate >= 4.5)
	{
		xDegree = X_Degree_X4;
	}

	/*求出对方机器人与球之间的连线和小球与我方球门线中点连线的夹角的和的平均值*/

	/*float sumAngle=0,averageAngle=0,L;
	 Vector3 opponentCoordinate,ourGoleCenterCoordinate;
	 L=wm.GetFieldLength()/2;
	 ourGoleCenterCoordinate=Vector3(-L,0,0);
	 for (int i=1;i<=PLAYERNUMBER;i++)
	 {
	 opponentCoordinate=wm.GetNewOpponentCoordinate(i);
	 float angle;
	 float ballToOpponentDistance=wm.GetDistanceBetweenTwoCoordinate(ballCoordinate,opponentCoordinate);
	 float opponentToOurGoleCenterDistance=wm.GetDistanceBetweenTwoCoordinate(ourGoleCenterCoordinate,opponentCoordinate);
	 float ballToOurGoleCenterDistance=wm.GetDistanceBetweenTwoCoordinate(ballCoordinate,ourGoleCenterCoordinate);
	 angle=acos(((ballToOpponentDistance*ballToOpponentDistance)
	 +(opponentToOurGoleCenterDistance*opponentToOurGoleCenterDistance)
	 -(ballToOurGoleCenterDistance*ballToOurGoleCenterDistance))
	 /(2*ballToOpponentDistance*opponentToOurGoleCenterDistance));
	 sumAngle=sumAngle+angle;
	 }
	 averageAngle=sumAngle/PLAYERNUMBER;*/
	//cout <<"here is averageAngle:::::::"<<averageAngle<<endl;
	/*判断角度的平均值属于哪个区间*/
	/*AngleDegree angleDegree;
	 if(averageAngle>=0
	 &&averageAngle<30)
	 {
	 angleDegree=A_Degree_A1;
	 }
	 else if(averageAngle>=30
	 &&averageAngle<60)
	 {
	 angleDegree=A_Degree_A2;
	 }
	 else if(averageAngle>=60
	 &&averageAngle<90)
	 {
	 angleDegree=A_Degree_A3;
	 }
	 else if(averageAngle>=90
	 &&averageAngle<=180)
	 {
	 angleDegree=A_Degree_A4;
	 }*/

	//cout <<"here is angleDegree::"<<angleDegree<<endl;
////////////////////////////////////////////////////////////
	float RArray[15] =
	{
	//00 01 02 03 04
			0, 0, 0, 0, 0, //00
			0, 0, 0, 0, 0, //01
			0, 0, 0, 0, 0 //02
			};
	float tempArray[5] =
	{ 0, 0, 0, 0, 0 };
////////////////////////////////////////////////////////////////
	switch (areaNumber)
	{
	case Area_A1:
		tempArray[0] = 1.0;
		tempArray[1] = 0.8;
		tempArray[2] = 0.2;
		tempArray[3] = 0.1;
		tempArray[4] = 0.1;
		break; //1.0 0.8 0.2 0.1 0.1
	case Area_A2:
		tempArray[0] = 0.6;
		tempArray[1] = 1.0;
		tempArray[2] = 0.8;
		tempArray[3] = 0.4;
		tempArray[4] = 0.1;
		break; //0.6 1.0 0.8 0.4 0.1
	case Area_A3:
		tempArray[0] = 0.1;
		tempArray[1] = 0.2;
		tempArray[2] = 0.8;
		tempArray[3] = 1.0;
		tempArray[4] = 0.8;
		break; //0.1 0.2 0.8 1.0 0.8
	case Area_A4:
		tempArray[0] = 0.1;
		tempArray[1] = 0.1;
		tempArray[2] = 0.2;
		tempArray[3] = 0.8;
		tempArray[4] = 1.0;
		break; //0.1 0.1 0.2 0.8 1.0
	default:
///		cout << "some error11111!!" << endl;
		;
	}
	for (int i = 0; i < 5; i++)
	{
		RArray[i] = tempArray[i];
	}
	///////////////////////////////////////////

	switch (distanceDegree)
	{
	case D_Degree_D1:
		tempArray[0] = 1.0;
		tempArray[1] = 0.7;
		tempArray[2] = 0.4;
		tempArray[3] = 0.1;
		tempArray[4] = 0.1;
		break; //1.0 0.7 0.4 0.1 0.1
	case D_Degree_D2:
		tempArray[0] = 0.1;
		tempArray[1] = 0.5;
		tempArray[2] = 0.4;
		tempArray[3] = 0.7;
		tempArray[4] = 0.3;
		break; //0.1 0.5 0.4 0.7 0.3
	case D_Degree_D3:
		tempArray[0] = 0.1;
		tempArray[1] = 0.1;
		tempArray[2] = 0.2;
		tempArray[3] = 0.7;
		tempArray[4] = 1.0;
		break; //0.1 0.1 0.2 0.7 1.0
	default:
		;
//		cout << "some error22222!!" << endl;
	}
	for (int i = 5; i < 10; i++)
	{
		RArray[i] = tempArray[i % 5];
	}
///////////////////////////////////////////////////////
	switch (xDegree)
	{
	case X_Degree_X1:
		tempArray[0] = 1.0;
		tempArray[1] = 0.8;
		tempArray[2] = 0.3;
		tempArray[3] = 0.1;
		tempArray[4] = 0.1;
		break; //1.0 0.8 0.3 0.1 0.1
	case X_Degree_X2:
		tempArray[0] = 0.8;
		tempArray[1] = 1.0;
		tempArray[2] = 0.7;
		tempArray[3] = 0.3;
		tempArray[4] = 0.1;
		break; //0.8 1.0 0.7 0.3 0.1
	case X_Degree_X3:
		tempArray[0] = 0.1;
		tempArray[1] = 0.3;
		tempArray[2] = 0.6;
		tempArray[3] = 1.0;
		tempArray[4] = 0.8;
		break; //0.1 0.3 0.6 1.0 0.8
	case X_Degree_X4:
		tempArray[0] = 0.1;
		tempArray[1] = 0.1;
		tempArray[2] = 0.3;
		tempArray[3] = 0.8;
		tempArray[4] = 1.0;
		break; //0.1 0.1 0.3 0.8 1.0
	default:
//		cout << "some error33333!!" << endl;
		;
	}

	for (int i = 10; i < 15; i++)
	{
		RArray[i] = tempArray[i % 10];
	}
	//////////////////////////////////////////////////////

	/*switch(angleDegree)
	 {
	 case A_Degree_A1:
	 tempArray[0]=1.0;tempArray[1]=0.8;tempArray[2]=0.4;tempArray[3]=0.1;tempArray[4]=0.1;break;//1.0 0.8 0.3 0.1 0.1
	 case A_Degree_A2:
	 tempArray[0]=0.7;tempArray[1]=1.0;tempArray[2]=0.5;tempArray[3]=0.2;tempArray[4]=0.1;break;//0.7 1.0 0.5 0.2 0.1
	 case A_Degree_A3:
	 tempArray[0]=0.1;tempArray[1]=0.1;tempArray[2]=0.5;tempArray[3]=1.0;tempArray[4]=0.8;break;//0.1 0.1 0.5 1.0 0.8
	 case A_Degree_A4:
	 tempArray[0]=0.1;tempArray[1]=0.1;tempArray[2]=0.2;tempArray[3]=0.7;tempArray[4]=1.0;break;//0.1 0.1 0.2 0.7 1.0
	 default:
	 cout <<"some error444444!!"<<endl;
	 }
	 for(int i=15;i<20;i++)
	 {
	 RArray[i]=tempArray[i%15];
	 }*/

//	for(int i=0;i<15;i++)
//	{
//		cout <<"here is test RArray"<<RArray[i]<<endl;
//	}
///////////////////////////////////////////////////////////////////////////////////////////规范列平均法（和法） 计算判断矩阵a各行各个元素mi的和；
	///将a的各行元素的和进行归一化； 该向量即为所求权重向量。
	//float weight[4]={0,0,0,0},sumOfTempArray=0,sumOfOneRow=0;
	/*for(int i=0;i<20;i++)
	 {
	 sumOfTempArray=sumOfTempArray+RArray[i];
	 }
	 cout <<"here is test sum of Temp Array::::"<<sumOfTempArray<<endl;
	 ///////
	 int counter_1=0,counter_2=0;
	 for(int i=0;i<4;i++)
	 {
	 while(counter_1<counter_2+5)
	 {
	 sumOfOneRow=sumOfOneRow+RArray[counter_1];
	 counter_1++;
	 }
	 //cout <<"here is sum of one row:::"<<sumOfOneRow<<endl;
	 weight[i]=sumOfOneRow/sumOfTempArray;
	 sumOfOneRow=0;
	 cout <<"here is weight:::"<<weight[i]<<endl;
	 counter_2=counter_1;///counter_2始终比counter_1大5
	 }*/
	///////////////////////////////////////////////////////////////////////////////////////几何法（根法） 计算判断矩阵a各行各个元素mi的积；
	///将a的各行元素的积进行归一化； 该向量即为所求权重向量。
	float weight[3] =
	{ 0, 0, 0 }, productOfOneRow = 1.0;
	int counter_1 = 0, counter_2 = 0;
	for (int i = 0; i < 3; i++)
	{

		while (counter_1 < counter_2 + 5)
		{
			productOfOneRow = productOfOneRow * RArray[counter_1];
			counter_1++;
		}
		//cout <<"here is sum of one row:::"<<sumOfOneRow<<endl;
		weight[i] = pow(productOfOneRow, 0.2f); ///开5次根
		//	cout <<"here is weight1111111:::"<<weight[i]<<endl;
		productOfOneRow = 1.0;
		counter_2 = counter_1; ///counter_2始终比counter_1大5
	}
///////////////////////////////////////////////////////////////
	///归一化！！
	float sumOfWeight = 0;
	for (int i = 0; i < 3; i++)
	{
		sumOfWeight = sumOfWeight + weight[i];
	}
//	cout <<"here is sumOfWeight:::"<<sumOfWeight<<endl;

	for (int i = 0; i < 3; i++)
	{
		weight[i] = weight[i] / sumOfWeight;
//		cout <<"here is weight2222222:::"<<weight[i]<<endl;
	}
/////////////////////////////////////////////////////////////
	float B[5] =
	{ 0, 0, 0, 0, 0 }, temp[3] =
	{ 0, 0, 0 };

	/*计算bj*/
	int counter_One = 0, counter_Two = 0;
	int ArrayWidth = 3, ArrayLength = 5;
	//for(int compareTime=0;compareTime<ArrayLength;compareTime++)
	//{
	//	counter_Two=compareTime;// 0 1 2 3 4
	/*两两比较*/
	//	while(counter_One<ArrayWidth)
	//	{
	//		if(weight[counter_One]>RArray[counter_Two])
	//		{
	//			temp[counter_One]=RArray[counter_Two];
	//			cout <<"here is compare temp111::::::::"<<temp[counter_One]<<endl;
	//		}
	//		else
	//		{
	//			temp[counter_One]=weight[counter_One];
	//			cout <<"here is compare temp222::::::::"<<temp[counter_One]<<endl;
	//		}
	//		counter_One++;
	//		counter_Two=counter_Two+5;//每次递增5
	//	}
	//	counter_One=0;///计数器清零
	/*找出其中最大的作为bj*/
	//	float maxInArrayTemp=temp[0];
	//	for(int i=0;i<3;i++)
	//	{
	//		if(temp[i]>maxInArrayTemp)
	//		{
	//			maxInArrayTemp=temp[i];
	//		}
	//	}
	//	cout <<"here is maxInArrayTemp"<<maxInArrayTemp<<endl;
	//	B[compareTime]=maxInArrayTemp;//将最大值保存为bj
	//	}
	for (int compareTime = 0; compareTime < ArrayLength; compareTime++)
	{
		counter_Two = compareTime; // 0 1 2 3 4
		/*两两比较*/
		while (counter_One < ArrayWidth)
		{
			temp[counter_One] = weight[counter_One] * RArray[counter_Two];
		//	cout << "here is compare temp111::::::::" << temp[counter_One]
		//			<< endl;
			B[compareTime] = B[compareTime] + temp[counter_One];
			counter_One++;
			counter_Two = counter_Two + 5; //每次递增5
		}
//			cout <<"here is B::::"<<B[compareTime]<<endl;
		counter_One = 0; ///计数器清零
	}

	int maxBNumber = 0;
	float maxB = B[0];
	for (int counter = 1; counter < 5; counter++)
	{
		if (B[counter] > maxB)
		{
			maxB = B[counter];
			maxBNumber = counter;
		}
	}
	//	cout <<"here is test maxBNumber:::::::::"<<maxBNumber<<endl;

	OffensiveAndDefensiveRating offensiveAndDefensiveRating;

	switch (maxBNumber)
	{
	case 0:
		offensiveAndDefensiveRating = OffensiveAndDefensiveRating_FullDefense;
		break;
	case 1:
		offensiveAndDefensiveRating =
				OffensiveAndDefensiveRating_FocusOnDefense;
		break;
	case 2:
		offensiveAndDefensiveRating =
				OffensiveAndDefensiveRating_AttackDefenseBalance;
		break;
	case 3:
		offensiveAndDefensiveRating =
				OffensiveAndDefensiveRating_FocusedOnOffensive;
		break;
	case 4:
		offensiveAndDefensiveRating =
				OffensiveAndDefensiveRating_AllOutOffensive;
		break;
	}

	return offensiveAndDefensiveRating;
}

Action Strategy::StopWhereAt()
{
	destination = wm.GetMyCoordinate();
	angleToTurn = -wm.GetMyBodyAngleToXAxis();
	topSpeed = MIN_SPEED;
	if (destination.x() < -wm.GetFieldLength() + 1.5 * CELL_LENGTH)
	{
		destination.x(-wm.GetFieldLength() + 1.5 * CELL_LENGTH);
	}
	turnHeadStrategy(fallDownTurnHead);
#ifdef AGENT_STRATEGY_OUTPUT
	cout << "Vice_Vanguard_1:_________________" << endl;
	cout << "angleToTurn:" << angleToTurn << endl;
	cout << "destination:" << destination << endl;
	cout << "topSpeed:" << topSpeed << endl;
#endif
	return NEWWALK(destination, angleToTurn, topSpeed);
}
Vector3 Strategy::Vector3Linelength(Vector3 point1,Vector3 point2,float length,bool isAdirection)
{
#ifdef AGENT_STRATEGY_OUTPUT
	cout<<"point1::"<<point1<<endl;
	cout<<"point2::"<<point2<<endl;
	cout<<"Vector3Linelength ---length::"<<length<<endl;
#endif
	length=length*length;
	float kk2=length/(sqr(point1.x()-point2.x())+sqr(point1.y()-point2.y()));
	float k0=sqrt(kk2);
	float k1=-sqrt(kk2);
	Vector3 res1(point2.x()-k0*(point1.x()-point2.x()),
			point2.y()-k0*(point1.y()-point2.y()),0);
	Vector3 res2(point2.x()-k1*(point1.x()-point2.x()),
			point2.y()-k1*(point1.y()-point2.y()),0);
	Vector3 point2_1=point1-point2;
	Vector3 point2ToRes1=point2-res1;
	Vector3 point2ToRes2=point2-res2;
#ifdef AGENT_STRATEGY_OUTPUT
	cout<<"res1::"<<res1<<endl;
	cout<<"res2::"<<res2<<endl;
#endif
	if(isAdirection)
	{
		if(point2_1*point2ToRes1>0)
		{
			return res1;
		}
		else if(point2_1*point2ToRes2>0)
		{
			return res2;
		}
		else
		{
			return res2;
		}
	}
	else
	{
		if(point2_1*point2ToRes1<0)
		{
			return res1;
		}
		else if(point2_1*point2ToRes2<0)
		{
			return res2;
		}
		else
		{
			return res2;
		}
	}
}
