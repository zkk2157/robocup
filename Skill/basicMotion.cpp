#include "basicMotion.h"
#include "basicmotiondata.h"
extern Configure CITConf;
extern Agent agent;
extern WorldModel wm;
extern u uLINK;

FormatInfoToServer readDataToStr;
BasicMotion::BasicMotion()
{
	timeCounter = 0;
}
void BasicMotion::SetTimeCounter(int num)
{
	timeCounter = num;
	readDataToStr.beginReadData = true;
	readDataToStr.turnHeadAngle = 0;
	if (timeCounter < 0)
		exceptionalCase = true;
	else
		exceptionalCase = false;
}
Action BasicMotion::StopAllMotion()
{
	return readDataToStr.AllStop();
}
Action BasicMotion::DealFallingDown(int style)
{
	if (style == 0)
	{
		return readDataToStr.ReadData_MaxSpeed(preventFallDown_FORWARD[6]);
	}
	else if (style == 1)
	{
		return readDataToStr.ReadData_MaxSpeed(preventFallDown_FORWARD[5]);
	}
	else
	{
		return readDataToStr.ReadData_MaxSpeed(preventFallDown_FORWARD[4]);
	}
}
Action BasicMotion::InitStandUpPose()
{
	readDataToStr.TurnHeadToFocusBall();
	//  return readDataToStr.ReadDataA(aStartWalk[0],3,0,0.12,0,0.12);  
	return readDataToStr.ReadDataA(aStartWalk[1], 3);
	//return readDataToStr.ReadDataA(slideTackleData[2], 0.5);
}
int BasicMotion::GetTimeCounter()
{
	return timeCounter;
}
Action BasicMotion::StandingUpFromFront()
{
	timeCounter++;
	if (timeCounter <= 0)//0
	{
		return readDataToStr.ReadData_Count(aStandUpForward[0], 1); ///恢复身体直//1
	}
	if (timeCounter <= 10)//10
	{
		return readDataToStr.ReadData_Count(aStandUpForward[0], 10); ///恢复身体直//10
	}
	else if (timeCounter <= 25)//25
	{
		return readDataToStr.ReadData_Count(aStandUpForward[1], 5); /////5
	}
	else if (timeCounter <= 45)//45
	{
		readDataToStr.TurnHeadToFocusBall();
		return readDataToStr.ReadData_Count(aStandUpForward[2], 20); /// //20
	}

	else if (timeCounter <= 65)//65
	{
		readDataToStr.TurnHeadToFocusBall();
		return readDataToStr.ReadData_Count(aStandUpForward[6], 20); /// 20
	}
	else if (timeCounter <= 75)   //75
	{
		readDataToStr.TurnHeadToFocusBall();
		return readDataToStr.ReadData_Count(aStandUpForward[6], 10); ///10
	}
	else
	{
		readDataToStr.TurnHeadToFocusBall();
		//	return readDataToStr.ReadDataA(aStartWalk[0],3,-0.03,0.19,-0.03,0.19);

		return readDataToStr.ReadDataA(aStartWalk[1], 3);
	}
}

Action BasicMotion::StandingUpFromBackByUT()
{
	timeCounter++;
	if (timeCounter <= 10)
	{
		return readDataToStr.ReadData_Count(standUpFromUT[0], 10);
	}
	else if (timeCounter <= 15)
	{
		return readDataToStr.ReadData_Count(standUpFromUT[1], 5);
	}
	else if (timeCounter <= 24)
	{
		return readDataToStr.ReadData_Count(standUpFromUT[2], 9);
	}
	else if (timeCounter <= 29)
	{
		return readDataToStr.ReadData_Count(standUpFromUT[3], 5);
	}
	else if (timeCounter <= 40)
	{
		return readDataToStr.ReadData_Count(standUpFromUT[4], 11);
	}
	else if (timeCounter <= 42)
	{
		return readDataToStr.ReadData_Count(standUpFromUT[5], 2);
	}
	else if (timeCounter <= 49)
	{
		return readDataToStr.ReadData_Count(standUpFromUT[6], 7);
	}
//	else if (timeCounter <= 54)
//	{
//		return readDataToStr.ReadData_Count(standUpFromUT[7], 5);
//	}
	else
	{
		return readDataToStr.ReadData_Count(aStartWalk[1], 3);
	}
}

Action BasicMotion::StandingUpFromBack()
{

	timeCounter++;
// 	/*cout*/<<"timecounter :"<<timeCounter<<endl;
	if (timeCounter <= 20)
	{
		return readDataToStr.ReadData_Count(aStandUpBackward[0], 20); //the body recovery
	}
	else if (timeCounter <= 25)
	{
		return readDataToStr.ReadData_Count(aStandUpBackward[0], 5); //the body recovery
	}
	else if (timeCounter <= 71)
	{
		readDataToStr.TurnHeadToFocusBall();
		return standBackUp[timeCounter - 26];
	}
	else if (timeCounter <= 90)
	{
		readDataToStr.TurnHeadToFocusBall();
		return readDataToStr.ReadData_Count(aStandUpBackward[10], 20); //the body recovery
	}
	else
	{
		readDataToStr.TurnHeadToFocusBall();
		//return readDataToStr.ReadDataA(aStartWalk[0],3,-0.03,0.19,-0.03,0.19);

		return readDataToStr.ReadDataA(aStartWalk[1], 3);
	}

}

Action BasicMotion::PreventingFowardFallingDown()
{
	if(agent.GetType()==1)
	{
	timeCounter++;
	if (timeCounter <= 10)
	{
		////cout<<"time "<<wm.GetCurrentGameTime()<<"***********"<<endl;
		return readDataToStr.ReadData_Count(preventFallDown_FORWARD1[0], 1);
	}
	else if (timeCounter <= 20)
	{
		return readDataToStr.ReadData_MaxSpeed(preventFallDown_FORWARD1[2]);
	}
	else if (timeCounter <= 30)
	{
		return readDataToStr.ReadData_Count(preventFallDown_FORWARD1[1], 10);
	}
	else if (timeCounter <= 35)
	{

		return readDataToStr.ReadData_Count(preventFallDown_FORWARD1[1], 5);
	}
	else if (timeCounter <= 45)
	{
		readDataToStr.TurnHeadToFocusBall();
		return readDataToStr.ReadData_MaxSpeed(preventFallDown_FORWARD1[2]);
	}
	else if (timeCounter <= 55)
	{
		readDataToStr.TurnHeadToFocusBall();
		return readDataToStr.ReadData_Count(preventFallDown_FORWARD1[3], 10);
	}
	else
	{
		readDataToStr.TurnHeadToFocusBall();
		//return readDataToStr.ReadDataA(aStartWalk[0],3,-0.03,0.175,-0.03,0.175);

		return readDataToStr.ReadDataA(aStartWalk[1], 3);
	}
	}
	else if(agent.GetType()==3)
	{
		timeCounter++;
			if (timeCounter <= 10)
			{
				////cout<<"time "<<wm.GetCurrentGameTime()<<"***********"<<endl;
				return readDataToStr.ReadData_Count(preventFallDown_FORWARD3[0], 1);
			}
			else if (timeCounter <= 21)
			{
				return readDataToStr.ReadData_MaxSpeed(preventFallDown_FORWARD3[2]);
			}
			else if (timeCounter <= 33)
			{
				return readDataToStr.ReadData_Count(preventFallDown_FORWARD3[1], 11);
			}
			else if (timeCounter <= 38)
			{

				return readDataToStr.ReadData_Count(preventFallDown_FORWARD3[1], 6);
			}
			else if (timeCounter <= 49)
			{
				readDataToStr.TurnHeadToFocusBall();
				return readDataToStr.ReadData_MaxSpeed(preventFallDown_FORWARD3[2]);
			}
			else if (timeCounter <= 61)
			{
				readDataToStr.TurnHeadToFocusBall();
				return readDataToStr.ReadData_Count(preventFallDown_FORWARD3[3], 12);
			}
			else
			{
				readDataToStr.TurnHeadToFocusBall();
				//return readDataToStr.ReadDataA(aStartWalk[0],3,-0.03,0.175,-0.03,0.175);

				return readDataToStr.ReadDataA(aStartWalk[1], 3);
			}
	}
	else
	{
		timeCounter++;
			if (timeCounter <= 10)//10
			{
				////cout<<"time "<<wm.GetCurrentGameTime()<<"***********"<<endl;
				return readDataToStr.ReadData_Count(preventFallDown_FORWARD[0], 1);//1
			}
			else if (timeCounter <= 20)//20
			{
				return readDataToStr.ReadData_MaxSpeed(preventFallDown_FORWARD[2]);//2
			}
			else if (timeCounter <= 30)//30
			{
				return readDataToStr.ReadData_Count(preventFallDown_FORWARD[1], 10);//10
			}
			else if (timeCounter <= 35)//35
			{

				return readDataToStr.ReadData_Count(preventFallDown_FORWARD[1], 5);//5
			}
			else if (timeCounter <= 45)//45
			{
				readDataToStr.TurnHeadToFocusBall();
				return readDataToStr.ReadData_MaxSpeed(preventFallDown_FORWARD[2]);//2
			}
			else if (timeCounter <= 55)//55
			{
				readDataToStr.TurnHeadToFocusBall();
				return readDataToStr.ReadData_Count(preventFallDown_FORWARD[3], 10);//10
			}
			else
			{
				readDataToStr.TurnHeadToFocusBall();
				//return readDataToStr.ReadDataA(aStartWalk[0],3,-0.03,0.175,-0.03,0.175);

				return readDataToStr.ReadDataA(aStartWalk[1], 3);
			}
	}
}
Action BasicMotion::PreventingBackFallingDown()
{
	timeCounter++;
	//cout<<"PreventingBackFallingDown()   timeCounter :"<<timeCounter<<endl;
	if (timeCounter <= 4)
	{
		return readDataToStr.ReadData_Count(preventFallDown_BACK[0], 1); //the body recovery
	}
	if (timeCounter <= 10)
	{
		return readDataToStr.ReadData_Count(preventFallDown_BACK[0], 1); //the body recovery
	}
	if (timeCounter <= 20)
	{
		return readDataToStr.ReadData_Count(preventFallDown_BACK[0], 10); //the body recovery
	}
	else if (timeCounter <= 35)
	{
		return readDataToStr.ReadData_MaxSpeed(preventFallDown_BACK[3]);
	}
	else if (timeCounter <= 45)
	{
		readDataToStr.TurnHeadToFocusBall();
		return readDataToStr.ReadData_Count(preventFallDown_BACK[1], 10); //the body recovery
	}
	else if (timeCounter <= 55)
	{
		readDataToStr.TurnHeadToFocusBall();
		return readDataToStr.ReadData_Count(preventFallDown_BACK[2], 10); //the body recovery
	}
	else if (timeCounter <= 60)
	{
		readDataToStr.TurnHeadToFocusBall();
		return readDataToStr.ReadData_Count(preventFallDown_BACK[2], 5); //the body recovery
	}
	else
	{
		readDataToStr.TurnHeadToFocusBall();
		//	return readDataToStr.ReadDataA(aStartWalk[0],3,-0.03,0.175,-0.03,0.175);	
		return readDataToStr.ReadDataA(aStartWalk[1], 3);
	}
}
Action BasicMotion::SplitingToSaveBall()
{
	timeCounter++;
	//cout<<"timeCounter :"<<timeCounter<<endl;
	if (timeCounter < -5)
	{
		return readDataToStr.ReadData_MaxSpeed(splits[2]);
	}
	else if (timeCounter <= 0)
	{
		return readDataToStr.ReadData_MaxSpeed(splits[3]);;
	}
	else if (timeCounter <= 7 && exceptionalCase)
	{
		readDataToStr.TurnHeadToFocusBall();
		return readDataToStr.ReadData_Count(splits[5], 1);
	}
	else if (timeCounter <= 23 && exceptionalCase)
	{
		readDataToStr.TurnHeadToFocusBall();
		return readDataToStr.ReadData_Count(splits[1], 1);
	}
	else if (timeCounter <= 33)
	{
		readDataToStr.TurnHeadToFocusBall();
		return readDataToStr.ReadData_Count(splits[0], 1);
	}
	else
	{
		readDataToStr.TurnHeadToFocusBall();
		return readDataToStr.AllStopExceptHead();
	}
}
Action BasicMotion::RightFootShootingBall()
{
	timeCounter++;

	if (timeCounter <= 10)
	{
		cout << "timeCounter::" << timeCounter << endl;
		return readDataToStr.ReadData_Count(rightFootShootBall[0], 10); //the body recovery
	}
	else if (timeCounter <= 15)
	{
		cout << "RR-timeCounter::" << timeCounter << endl;
		return readDataToStr.ReadData_Count(rightFootShootBall[0], 5); //the body recovery
	}
	else if (timeCounter <= 35)
	{
		cout << "RR-timeCounter::" << timeCounter << endl;
		return readDataToStr.ReadData_Count(rightFootShootBall[1], 20);
	}
	else if (timeCounter <= 41)
	{
		cout << "RR-timeCounter::" << timeCounter << endl;
		return readDataToStr.ReadData_Count(rightFootShootBall[2], 6); //the body recovery
	}
	else if (timeCounter <= 46)
	{
		cout << "RR-timeCounter::" << timeCounter << endl;
		return readDataToStr.ReadData_Count(rightFootShootBall[3], 5); //the body recovery
	}
	else if (timeCounter <= 48)
	{
		cout << "RR-timeCounter::" << timeCounter << endl;
		return readDataToStr.ReadData_MaxSpeed(rightFootShootBall[4]); //the body recovery
	}
	else if (timeCounter <= 51)
	{
		cout << "RR-timeCounter::" << timeCounter << endl;
		return readDataToStr.ReadData_MaxSpeed(rightFootShootBall[5]); //the body recovery
	}
	else if (timeCounter <= 57)
	{
		cout << "RR-timeCounter::" << timeCounter << endl;
		readDataToStr.TurnHeadToFocusBall();
		return readDataToStr.ReadData_MaxSpeed(rightFootShootBall[6]); //the body recovery
	}
	else
	{
		cout << "RR-timeCounter::" << timeCounter << endl;
		readDataToStr.TurnHeadToFocusBall();
		return readDataToStr.ReadDataA(aStartWalk[1], 3);
	}
}

Action BasicMotion::RoboCansRighttoLeft()
{
//	if(beginPassBall == true)
//		{
//			passBallCounter=0;
//			beginPassBall=false;
//			readData.beginReadData=true;
//		}

	timeCounter++;
	//	passBallCounter++;
		int base=20;//10  //20
	if (timeCounter <= 0)
			{
		//		return readDataToStr.ReadData_Count(RightShootapollo2[0], 1); //huifu
			}
			if(timeCounter <= base+10   && timeCounter >  0)//10
		{
			//return readData.ReadDataA(rightLegPassToLeft[0],10);//10
				return readDataToStr.ReadData_Count(RoboCansRight[0],10);
			//	return readDataToStr.ReadData_MaxSpeed(RoboCansRight[0]);//2
		}
		else if(timeCounter <= base+34)
			return readDataToStr.ReadData_Count(RoboCansRight[1],24);
			//return readData.ReadData_Count(rightLegPassToLeft[1],24);//13//16
		else if(timeCounter <= base+35)
			return readDataToStr.ReadData_Count(RoboCansRight[2],1);
			//return readData.ReadData_Count(rightLegPassToLeft[2],1);//2//2
		else if(timeCounter <= base+36)
			return readDataToStr.ReadData_Count(RoboCansRight[3],1);
		//	return readData.ReadData_Count(rightLegPassToLeft[3],1);//1//1
		else if(timeCounter <= base+37)
			return readDataToStr.ReadData_Count(RoboCansRight[4],1);
		//	return readData.ReadData_Count(rightLegPassToLeft[4],1);//1//2
		else if(timeCounter <= base+38)
			return readDataToStr.ReadData_Count(RoboCansRight[5],1);
		//	return readData.ReadData_Count(rightLegPassToLeft[5],1);//1//1
		else if(timeCounter <= base+40)
			return readDataToStr.ReadData_Count(RoboCansRight[6],2);
		//	return readData.ReadData_Count(rightLegPassToLeft[6],2);//2//1///6
		else if(timeCounter <= base+41)
			return readDataToStr.ReadData_Count(RoboCansRight[7],1);
		//	return readData.ReadData_Count(rightLegPassToLeft[7],1);//1//1
		else if(timeCounter <= base+42)
			return readDataToStr.ReadData_Count(RoboCansRight[8],1);
		//	return readData.ReadData_Count(rightLegPassToLeft[8],1);//3//1
		else if(timeCounter <= base+43)
			return readDataToStr.ReadData_Count(RoboCansRight[9],1);
		//	return readData.ReadData_Count(rightLegPassToLeft[9],1);//1//1
		else if(timeCounter <= base+44)
			return readDataToStr.ReadData_Count(RoboCansRight[10],1);//2
			//return readData.ReadData_Count(rightLegPassToLeft[10],2);//1//5
		else if(timeCounter <= base+46)
			return readDataToStr.ReadData_Count(RoboCansRight[11],2);
			//return readData.ReadData_Count(rightLegPassToLeft[11],2);//1//5
		else if(timeCounter <= base+51)
			return readDataToStr.ReadData_Count(RoboCansRight[12],5);//5
	else
					{
				//		return readDataToStr.ReadData_Count(aStartWalk[1],3);
		cout << "RR-timeCounter::" << timeCounter << endl;
					readDataToStr.TurnHeadToFocusBall();
					return readDataToStr.ReadDataA(aStartWalk[1], 3);
					}
		//	return readData.ReadData_Count(rightLegPassToLeft[12],5);//1//5
//		else if( wm.getAverageOfLastCyclesGYR().mod()>0.9)
//		  return readData.ReadDataA(aStartWalk[0],3,-0.03,0.20,-0.03,0.20,0);
//		  //return readData.ReadDataA(aStartWalk[0],3,-0.03,0.175,-0.03,0.175,0);
//		else
//		{
//			beginPassBall=true;
//			rightFootPass=false;
//			leftFootPass=false;
//			decidedWhichFootWillShoot=false;
//			beginPassBall=true;
//			canPassBall=false;
//			readyToShootBall=false;
//			canShootBall=false;
//			readyToPassBall=false;
//			walkBegain=true;
//			gotUpOrDownLinePos = false;
//			needToUpdateKickAngle=true;
//			decidedWhichFootWillShoot=false;
//			turnHeadToLeft=true;
//			turnHeadToRight=false;
//			continousTurnHeadCounter=0;
//			return readData.AllStop();
//		}

}

Action BasicMotion::RoboCansLefttoRight()
{
//	if(beginPassBall == true)
//		{
//			passBallCounter=0;
//			beginPassBall=false;
//			readData.beginReadData=true;
//		}

	timeCounter++;

		int base=10;//10   //101010100101
		if (timeCounter <= 0)
			{
		//		return readDataToStr.ReadData_Count(RightShootapollo2[0], 1); //huifu

			}
			if(timeCounter <= base+10  && timeCounter > 0)//10
		{
			return readDataToStr.ReadData_Count(RoboCansLeft[0],10);//10
			//	return readDataToStr.ReadData_MaxSpeed(RoboCansLeft[0]);//2
		}
		else if(timeCounter <= base+34)
			return readDataToStr.ReadData_Count(RoboCansLeft[1],24);//13//16
		else if(timeCounter <= base+35)
			return readDataToStr.ReadData_Count(RoboCansLeft[2],1);//2//2
		else if(timeCounter <= base+36)
			return readDataToStr.ReadData_Count(RoboCansLeft[3],1);//1//1
		else if(timeCounter <= base+37)
			return readDataToStr.ReadData_Count(RoboCansLeft[4],1);//1//2
		else if(timeCounter <= base+38)
			return readDataToStr.ReadData_Count(RoboCansLeft[5],1);//1//1
		else if(timeCounter <= base+40)
			return readDataToStr.ReadData_Count(RoboCansLeft[6],2);//2//1///6
		else if(timeCounter <= base+41)
			return readDataToStr.ReadData_Count(RoboCansLeft[7],1);//1//1
		else if(timeCounter <= base+42)
			return readDataToStr.ReadData_Count(RoboCansLeft[8],1);//3//1
		else if(timeCounter <= base+43)
			return readDataToStr.ReadData_Count(RoboCansLeft[9],1);//1//1
		else if(timeCounter <= base+44)
			return readDataToStr.ReadData_Count(RoboCansLeft[10],1);//1//5
		else if(timeCounter <= base+46)
			return readDataToStr.ReadData_Count(RoboCansLeft[11],2);//1//5  //2
		else if(timeCounter <= base+51)
			return readDataToStr.ReadData_Count(RoboCansLeft[12],5);//1//5//5
		else
		{
			cout << "RR-timeCounter::" << timeCounter << endl;
						readDataToStr.TurnHeadToFocusBall();
						return readDataToStr.ReadDataA(aStartWalk[1], 3);
			//return readDataToStr.ReadData_Count(aStartWalk[1],3);
		}
		//else if( wm.getAverageOfLastCyclesGYR().mod()>0.9)
		//  return readDataToStr.ReadData_Count(aStartWalk[0],3,-0.03,0.20,-0.03,0.20,0);
		  //return readData.ReadDataA(aStartWalk[0],3,-0.03,0.175,-0.03,0.175,0);
//		else
		{
//			beginPassBall=true;
//			rightFootPass=false;
//			leftFootPass=false;
//			decidedWhichFootWillShoot=false;
//			beginPassBall=true;
//			canPassBall=false;
//			readyToShootBall=false;
//			canShootBall=false;
//			readyToPassBall=false;
//			walkBegain=true;
//			gotUpOrDownLinePos = false;
//			needToUpdateKickAngle=true;
//			decidedWhichFootWillShoot=false;
//			turnHeadToLeft=true;
//			turnHeadToRight=false;
//			continousTurnHeadCounter=0;
//			return readData.AllStop();
		}
}


Action BasicMotion::RoboCansRighttoLeft4()
{

	timeCounter++;
			int base=20;//10
		if(timeCounter <= base+10)
	{
		//return readData.ReadDataA(rightLegPassToLeft[0],10);
		return readDataToStr.ReadData_Count(RoboCansLeftfour[0],10);//10
	}
	else if(timeCounter <= base+14)
		return readDataToStr.ReadData_Count(RoboCansLeftfour[1],4);//10
		//return readData.ReadData_Count(rightLegPassToLeft[1],4);//4
	else if(timeCounter <= base+19)
		return readDataToStr.ReadData_Count(RoboCansLeftfour[2],5);//5
	else if(timeCounter <= base+32)
		return readDataToStr.ReadData_Count(RoboCansLeftfour[3],13);//13
	else if(timeCounter <= base+33)
		return readDataToStr.ReadData_Count(RoboCansLeftfour[4],1);//1
	else if(timeCounter <= base+34)
		return readDataToStr.ReadData_Count(RoboCansLeftfour[5],1);//1
	else if(timeCounter <= base+35)
		return readDataToStr.ReadData_Count(RoboCansLeftfour[6],1);//1
	else if(timeCounter <= base+36)
		return readDataToStr.ReadData_Count(RoboCansLeftfour[7],1);//1
	else if(timeCounter <= base+37)
		return readDataToStr.ReadData_Count(RoboCansLeftfour[8],1);//1
	else if(timeCounter <= base+38)
		return readDataToStr.ReadData_Count(RoboCansLeftfour[9],1);//1
	else if(timeCounter <= base+39)
		return readDataToStr.ReadData_Count(RoboCansLeftfour[10],1);//1
	else if(timeCounter <= base+41)
		return readDataToStr.ReadData_Count(RoboCansLeftfour[11],2);//1
	else if(timeCounter <= base+48)
		return readDataToStr.ReadData_Count(RoboCansLeftfour[12],7);//7*/
	//	else if( wm.getAverageOfLastCyclesGYR().mod()>0.9)
	//	else if(	wm.getAverageOfLastCyclesGYR()>0.9)
		//	return readDataToStr.ReadDataA(aStartWalk[0],3,-0.03,0.2,-0.03,0.2);
	//		  return readDataToStr.ReadData_Count(aStartWalk[0],3,-0.03,0.20,-0.03,0.20,0);

	else
	{
		readDataToStr.TurnHeadToFocusBall();
	return readDataToStr.ReadData_Count(aStartWalk[1],3);
			}
	//else if( wm.getAverageOfLastCyclesGYR().mod()>0.9)
	//  return readData.ReadDataA(aStartWalk[0],3,-0.03,0.20,-0.03,0.20,0);
	  //return readData.ReadDataA(aStartWalk[0],3,-0.03,0.175,-0.03,0.175,0);

}


Action BasicMotion::RoboCansLefttoRight4()
{



	timeCounter++;
			int base=10;//10
		if(timeCounter <= base+10)
	{
		//return readData.ReadDataA(rightLegPassToLeft[0],10);
		return readDataToStr.ReadData_Count(RoboCansRightfour[0],10);//10
	}
	else if(timeCounter <= base+14)
		return readDataToStr.ReadData_Count(RoboCansRightfour[1],4);//10
		//return readData.ReadData_Count(rightLegPassToLeft[1],4);//4
	else if(timeCounter <= base+19)
		return readDataToStr.ReadData_Count(RoboCansRightfour[2],5);//5
	else if(timeCounter <= base+32)
		return readDataToStr.ReadData_Count(RoboCansRightfour[3],13);//13
	else if(timeCounter <= base+33)
		return readDataToStr.ReadData_Count(RoboCansRightfour[4],1);//1
	else if(timeCounter <= base+34)
		return readDataToStr.ReadData_Count(RoboCansRightfour[5],1);//1
	else if(timeCounter <= base+35)
		return readDataToStr.ReadData_Count(RoboCansRightfour[6],1);//1
	else if(timeCounter <= base+36)
		return readDataToStr.ReadData_Count(RoboCansRightfour[7],1);//1
	else if(timeCounter <= base+37)
		return readDataToStr.ReadData_Count(RoboCansRightfour[8],1);//1
	else if(timeCounter <= base+38)
		return readDataToStr.ReadData_Count(RoboCansRightfour[9],1);//1
	else if(timeCounter <= base+39)
		return readDataToStr.ReadData_Count(RoboCansRightfour[10],1);//1
	else if(timeCounter <= base+41)
		return readDataToStr.ReadData_Count(RoboCansRightfour[11],2);//1
	else if(timeCounter <= base+48)
		return readDataToStr.ReadData_Count(RoboCansRightfour[12],7);//7*/
	//else if( wm.getAverageOfLastCyclesGYR()>0.9)
//		return readDataToStr.ReadDataA(aStartWalk[0],3,-0.03,0.2,-0.03,0.2);
	else
			{
	//			return readDataToStr.ReadData_Count(aStartWalk[1],3);
		cout << "RR-timeCounter::" << timeCounter << endl;
					readDataToStr.TurnHeadToFocusBall();
					return readDataToStr.ReadDataA(aStartWalk[1], 3);
			}
}
Action  BasicMotion::RightShootapollo()
{
	timeCounter++;
		if (timeCounter <= 0)
		{
			return readDataToStr.ReadData_Count(RightShootapollo2[0], 1); //huifu
		}
		if (timeCounter <= 11)
		{
			return readDataToStr.ReadData_Count(RightShootapollo2[0],11);
		}
		else if (timeCounter <=16)
		{
			return readDataToStr.ReadData_Count(RightShootapollo2[1],5);
		}
		else if (timeCounter <= 23)
		{
			return readDataToStr.ReadData_Count(RightShootapollo2[2],7);
		}
		else if (timeCounter <= 30)
		{
			return readDataToStr.ReadData_Count(RightShootapollo2[3],7);
		}
		else if (timeCounter <= 32)
		{
			return readDataToStr.ReadData_Count(RightShootapollo2[4],2);
		}
		else if (timeCounter <= 35)
		{
			return readDataToStr.ReadData_Count(RightShootapollo2[5],3);
		}
		else if (timeCounter <= 38)
		{
			return readDataToStr.ReadData_Count(RightShootapollo2[6],3);
		}
		else if (timeCounter <= 40)
		{
			return readDataToStr.ReadData_Count(RightShootapollo2[7],2);
		}
		else if (timeCounter <= 42)
		{
			return readDataToStr.ReadData_Count(RightShootapollo2[8],2);
		}
		else if (timeCounter <= 47)
		{
			return readDataToStr.ReadData_Count(RightShootapollo2[9],5);
		}
		else if (timeCounter <= 49)
		{
			return readDataToStr.ReadData_Count(RightShootapollo2[10],2);
		}
		else if (timeCounter <= 52)
		{
			return readDataToStr.ReadData_Count(RightShootapollo2[11],3);
		}
		else if (timeCounter <= 53)
		{
			return readDataToStr.ReadData_Count(RightShootapollo2[12],1);
		}
		else if (timeCounter <= 56)
		{
			return readDataToStr.ReadData_Count(RightShootapollo2[13],3);
		}
		else if (timeCounter <= 58)
		{
			return readDataToStr.ReadData_Count(RightShootapollo2[14],2);
		}
		else if (timeCounter <= 59)
		{
			return readDataToStr.ReadData_Count(RightShootapollo2[15],1);
		}
		else if (timeCounter <= 60)
		{
			return readDataToStr.ReadData_Count(rightFootShootBall[16],1);
		}
		else if (timeCounter <= 62)
		{
			return readDataToStr.ReadData_Count(RightShootapollo2[17],2);
		}
		else if (timeCounter <= 64)
		{
			return readDataToStr.ReadData_Count(RightShootapollo2[18],2);
		}
		else if (timeCounter <= 66)
		{
			return readDataToStr.ReadData_Count(RightShootapollo2[19],2);
		}
		else if (timeCounter <= 69)
		{
			return readDataToStr.ReadData_Count(RightShootapollo2[20],3);
		}
		else if (timeCounter <= 71)
		{
			return readDataToStr.ReadData_Count(RightShootapollo2[21],2);
		}
		else if (timeCounter <= 74)
		{
			return readDataToStr.ReadData_Count(RightShootapollo2[22],3);
		}
		else if (timeCounter <= 76)
		{
			return readDataToStr.ReadData_Count(RightShootapollo2[23],2);
		}
		else if (timeCounter <= 78)
		{
			return readDataToStr.ReadData_Count(RightShootapollo2[24],2);
		}
		else if (timeCounter <= 82)
		{
			return readDataToStr.ReadData_Count(RightShootapollo2[25],4);
		}
		else if (timeCounter <= 84)
		{
			return readDataToStr.ReadData_Count(RightShootapollo2[26],2);
		}
		else if (timeCounter <= 91)
		{
			return readDataToStr.ReadData_Count(RightShootapollo2[27],7);
		}
		else if (timeCounter <= 95)
		{
			return readDataToStr.ReadData_Count(RightShootapollo2[28],4);
		}
		else if (timeCounter <= 98)
		{
			return readDataToStr.ReadData_Count(RightShootapollo2[29],3);
		}
		else if (timeCounter <= 100)
		{
			return readDataToStr.ReadData_Count(RightShootapollo2[30],2);
		}
		else if (timeCounter <= 103)
		{
			return readDataToStr.ReadData_Count(RightShootapollo2[31],3);
		}
		else if (timeCounter <= 106)
		{
			return readDataToStr.ReadData_Count(RightShootapollo2[32],3);
		}
		else if (timeCounter <= 111)
		{
			return readDataToStr.ReadData_Count(RightShootapollo2[33],5);
		}
		else if (timeCounter <= 126)
		{
			return readDataToStr.ReadData_Count(RightShootapollo2[34],15);
		}
		else if (timeCounter <= 128)
		{
			return readDataToStr.ReadData_Count(RightShootapollo2[35],2);
		}
		else if (timeCounter <= 133)
		{
			return readDataToStr.ReadData_Count(RightShootapollo2[36],5);
		}
		else if (timeCounter <= 137)
		{
			return readDataToStr.ReadData_Count(RightShootapollo2[37],4);
		}
		else if (timeCounter <= 140)
		{
			return readDataToStr.ReadData_Count(RightShootapollo2[38],3);
		}
		else if (timeCounter <= 142)
		{
			return readDataToStr.ReadData_Count(RightShootapollo2[39],2);
		}
		else if (timeCounter <= 144)
		{
			return readDataToStr.ReadData_Count(RightShootapollo2[40],2);
		}
		else if (timeCounter <= 146)
		{
			return readDataToStr.ReadData_Count(RightShootapollo2[41],2);
		}
		else if (timeCounter <= 148)
		{
			return readDataToStr.ReadData_Count(RightShootapollo2[42],2);
		}
		else if (timeCounter <= 150)
		{
			return readDataToStr.ReadData_Count(RightShootapollo2[43],2);
		}
		else if (timeCounter <= 154)
		{
			return readDataToStr.ReadData_Count(RightShootapollo2[44],4);
		}
		else if (timeCounter <= 157)
		{
			return readDataToStr.ReadData_Count(RightShootapollo2[45],3);
		}
		else if (timeCounter <= 159)
		{
			return readDataToStr.ReadData_Count(RightShootapollo2[46],2);
		}
		else if (timeCounter <= 161)
		{
			return readDataToStr.ReadData_Count(RightShootapollo2[47],2);
		}
		else if (timeCounter <= 163)
		{
			return readDataToStr.ReadData_Count(RightShootapollo2[48],2);
		}
		else if (timeCounter <= 164)
		{
			return readDataToStr.ReadData_Count(RightShootapollo2[49],1);
		}
		else if (timeCounter <= 166)
		{
			return readDataToStr.ReadData_Count(RightShootapollo2[50],2);
		}
		else if (timeCounter <= 168)
		{
			return readDataToStr.ReadData_Count(RightShootapollo2[51],2);
		}
		else if (timeCounter <= 170)
		{
			return readDataToStr.ReadData_Count(RightShootapollo2[52],2);
		}
		else if (timeCounter <= 173)
		{
			return readDataToStr.ReadData_Count(RightShootapollo2[53],3);
		}
		else if (timeCounter <= 175)
		{
			return readDataToStr.ReadData_Count(RightShootapollo2[54],2);
		}
		else if (timeCounter <= 179)
		{
			return readDataToStr.ReadData_Count(RightShootapollo2[55],4);
		}
		else if (timeCounter <= 180)
		{
			return readDataToStr.ReadData_Count(RightShootapollo2[56],1);
		}
		else if (timeCounter <= 183)
		{
			return readDataToStr.ReadData_Count(RightShootapollo2[57],3);
		}
		else if (timeCounter <= 187)
		{
			return readDataToStr.ReadData_Count(RightShootapollo2[58],4);
		}
		else
		{
			cout << "RR-timeCounter::" << timeCounter << endl;
			readDataToStr.TurnHeadToFocusBall();
			return readDataToStr.ReadDataA(aStartWalk[1], 3);
		}




}

Action BasicMotion::LeftShootapollo()
{
	timeCounter++;
		if (timeCounter <= 11)
			{
				return readDataToStr.ReadData_Count(LeftShootapollo1[0],11);
			}
			else if (timeCounter <=16)
			{
				return readDataToStr.ReadData_Count(LeftShootapollo1[1],5);
			}
			else if (timeCounter <= 23)
			{
				return readDataToStr.ReadData_Count(LeftShootapollo1[2],7);
			}
			else if (timeCounter <= 30)
			{
				return readDataToStr.ReadData_Count(LeftShootapollo1[3],7);
			}
			else if (timeCounter <= 32)
			{
				return readDataToStr.ReadData_Count(LeftShootapollo1[4],2);
			}
			else if (timeCounter <= 35)
			{
				return readDataToStr.ReadData_Count(LeftShootapollo1[5],3);
			}
			else if (timeCounter <= 38)
			{
				return readDataToStr.ReadData_Count(LeftShootapollo1[6],3);
			}
			else if (timeCounter <= 40)
			{
				return readDataToStr.ReadData_Count(LeftShootapollo1[7],2);
			}
			else if (timeCounter <= 42)
			{
				return readDataToStr.ReadData_Count(LeftShootapollo1[8],2);
			}
			else if (timeCounter <= 47)
			{
				return readDataToStr.ReadData_Count(LeftShootapollo1[9],5);
			}
			else if (timeCounter <= 49)
			{
				return readDataToStr.ReadData_Count(LeftShootapollo1[10],2);
			}
			else if (timeCounter <= 52)
			{
				return readDataToStr.ReadData_Count(LeftShootapollo1[11],3);
			}
			else if (timeCounter <= 53)
			{
				return readDataToStr.ReadData_Count(LeftShootapollo1[12],1);
			}
			else if (timeCounter <= 56)
			{
				return readDataToStr.ReadData_Count(LeftShootapollo1[13],3);
			}
			else if (timeCounter <= 58)
			{
				return readDataToStr.ReadData_Count(LeftShootapollo1[14],2);
			}
			else if (timeCounter <= 59)
			{
				return readDataToStr.ReadData_Count(LeftShootapollo1[15],1);
			}
			else if (timeCounter <= 60)
			{
				return readDataToStr.ReadData_Count(LeftShootapollo1[16],1);
			}
			else if (timeCounter <= 62)
			{
				return readDataToStr.ReadData_Count(LeftShootapollo1[17],2);
			}
			else if (timeCounter <= 64)
			{
				return readDataToStr.ReadData_Count(LeftShootapollo1[18],2);
			}
			else if (timeCounter <= 66)
			{
				return readDataToStr.ReadData_Count(LeftShootapollo1[19],2);
			}
			else if (timeCounter <= 69)
			{
				return readDataToStr.ReadData_Count(LeftShootapollo1[20],3);
			}
			else if (timeCounter <= 71)
			{
				return readDataToStr.ReadData_Count(LeftShootapollo1[21],2);
			}
			else if (timeCounter <= 74)
			{
				return readDataToStr.ReadData_Count(LeftShootapollo1[22],3);
			}
			else if (timeCounter <= 76)
			{
				return readDataToStr.ReadData_Count(LeftShootapollo1[23],2);
			}
			else if (timeCounter <= 78)
			{
				return readDataToStr.ReadData_Count(LeftShootapollo1[24],2);
			}
			else if (timeCounter <= 82)
			{
				return readDataToStr.ReadData_Count(LeftShootapollo1[25],4);
			}
			else if (timeCounter <= 84)
			{
				return readDataToStr.ReadData_Count(leftFootShootBall[26],2);
			}
			else if (timeCounter <= 91)
			{
				return readDataToStr.ReadData_Count(leftFootShootBall[27],7);
			}
			else if (timeCounter <= 95)
			{
				return readDataToStr.ReadData_Count(LeftShootapollo1[28],4);
			}
			else if (timeCounter <= 98)
			{
				return readDataToStr.ReadData_Count(LeftShootapollo1[29],3);
			}
			else if (timeCounter <= 100)
			{
				return readDataToStr.ReadData_Count(LeftShootapollo1[30],2);
			}
			else if (timeCounter <= 103)
			{
				return readDataToStr.ReadData_Count(LeftShootapollo1[31],3);
			}
			else if (timeCounter <= 106)
			{
				return readDataToStr.ReadData_Count(LeftShootapollo1[32],3);
			}
			else if (timeCounter <= 111)
			{
				return readDataToStr.ReadData_Count(LeftShootapollo1[33],5);
			}
			else if (timeCounter <= 126)
			{
				return readDataToStr.ReadData_Count(LeftShootapollo1[34],15);
			}
			else if (timeCounter <= 128)
			{
				return readDataToStr.ReadData_Count(LeftShootapollo1[35],2);
			}
			else if (timeCounter <= 133)
			{
				return readDataToStr.ReadData_Count(LeftShootapollo1[36],5);
			}
			else if (timeCounter <= 137)
			{
				return readDataToStr.ReadData_Count(LeftShootapollo1[37],4);
			}
			else if (timeCounter <= 140)
			{
				return readDataToStr.ReadData_Count(LeftShootapollo1[38],3);
			}
			else if (timeCounter <= 142)
			{
				return readDataToStr.ReadData_Count(LeftShootapollo1[39],2);
			}
			else if (timeCounter <= 144)
			{
				return readDataToStr.ReadData_Count(LeftShootapollo1[40],2);
			}
			else if (timeCounter <= 146)
			{
				return readDataToStr.ReadData_Count(LeftShootapollo1[41],2);
			}
			else if (timeCounter <= 148)
			{
				return readDataToStr.ReadData_Count(LeftShootapollo1[42],2);
			}
			else if (timeCounter <= 150)
			{
				return readDataToStr.ReadData_Count(LeftShootapollo1[43],2);
			}
			else if (timeCounter <= 154)
			{
				return readDataToStr.ReadData_Count(LeftShootapollo1[44],4);
			}
			else if (timeCounter <= 157)
			{
				return readDataToStr.ReadData_Count(LeftShootapollo1[45],3);
			}
			else if (timeCounter <= 159)
			{
				return readDataToStr.ReadData_Count(LeftShootapollo1[46],2);
			}
			else if (timeCounter <= 161)
			{
				return readDataToStr.ReadData_Count(LeftShootapollo1[47],2);
			}
			else if (timeCounter <= 163)
			{
				return readDataToStr.ReadData_Count(LeftShootapollo1[48],2);
			}
			else if (timeCounter <= 164)
			{
				return readDataToStr.ReadData_Count(LeftShootapollo1[49],1);
			}
			else if (timeCounter <= 166)
			{
				return readDataToStr.ReadData_Count(LeftShootapollo1[50],2);
			}
			else if (timeCounter <= 168)
			{
				return readDataToStr.ReadData_Count(LeftShootapollo1[51],2);
			}
			else if (timeCounter <= 170)
			{
				return readDataToStr.ReadData_Count(LeftShootapollo1[52],2);
			}
			else if (timeCounter <= 173)
			{
				return readDataToStr.ReadData_Count(LeftShootapollo1[53],3);
			}
			else if (timeCounter <= 175)
			{
				return readDataToStr.ReadData_Count(LeftShootapollo1[54],2);
			}
			else if (timeCounter <= 179)
			{
				return readDataToStr.ReadData_Count(LeftShootapollo1[55],4);
			}
			else if (timeCounter <= 180)
			{
				return readDataToStr.ReadData_Count(LeftShootapollo1[56],1);
			}
			else if (timeCounter <= 183)
			{
				return readDataToStr.ReadData_Count(LeftShootapollo1[57],3);
			}
			else if (timeCounter <= 187)
			{
				return readDataToStr.ReadData_Count(LeftShootapollo1[58],4);
			}

			else
			{
				cout << "RR-timeCounter::" << timeCounter << endl;
				readDataToStr.TurnHeadToFocusBall();
				return readDataToStr.ReadDataA(aStartWalk[1], 3);
			}
}


Action BasicMotion::NexRTest()
{
	timeCounter++;
			if (timeCounter <= 15)
			{
				return readDataToStr.ReadData_Count(nexRTest[0],15);
			}
			else if (timeCounter <= 20)
			{
				return readDataToStr.ReadData_Count(nexRTest[1],5);
			}
			else if (timeCounter <= 25)
			{
				return readDataToStr.ReadData_Count(nexRTest[2],5);
			}
			else if (timeCounter <= 30)
			{
				return readDataToStr.ReadData_Count(nexRTest[3],5);
			}
			else if (timeCounter <= 35)
			{
				return readDataToStr.ReadData_Count(nexRTest[4],5);
			}
			else if (timeCounter <= 38)
			{
				return readDataToStr.ReadData_Count(nexRTest[5],3);
			}
			else if (timeCounter <= 40)
			{
				return readDataToStr.ReadData_Count(nexRTest[6],2);
			}
			else if (timeCounter <= 45)
			{
				return readDataToStr.ReadData_Count(nexRTest[7],5);
			}
			else if (timeCounter <= 50)
			{
				return readDataToStr.ReadData_Count(nexRTest[8],5);
			}
			else if (timeCounter <= 55)
			{
				return readDataToStr.ReadData_Count(nexRTest[9],5);
			}
			else if (timeCounter <= 60)
			{
				return readDataToStr.ReadData_Count(nexRTest[10],5);
			}
			else if (timeCounter <= 65)
			{
				return readDataToStr.ReadData_Count(nexRTest[11],5);
			}
			else if (timeCounter <= 85)
			{
				return readDataToStr.ReadData_Count(nexRTest[12],20);
			}
			else if (timeCounter <= 86)
			{
				return readDataToStr.ReadData_Count(nexRTest[13],1);
			}
			else if (timeCounter <= 87)
			{
				return readDataToStr.ReadData_Count(nexRTest[14],1);
			}
			else if (timeCounter <= 88)
			{
				return readDataToStr.ReadData_Count(nexRTest[15],1);
			}
			else if (timeCounter <= 90)
			{
				return readDataToStr.ReadData_Count(nexRTest[16],2);
			}
			else if (timeCounter <= 94)
			{
				return readDataToStr.ReadData_Count(nexRTest[17],4);
			}
			else if (timeCounter <= 97)
			{
				return readDataToStr.ReadData_Count(nexRTest[18],3);
			}
			else if (timeCounter <= 98)
			{
				return readDataToStr.ReadData_Count(nexRTest[19],1);
			}
			else if (timeCounter <= 100)
			{
				return readDataToStr.ReadData_Count(nexRTest[20],2);
			}
			else
			{
				return readDataToStr.ReadData_Count(aStartWalk[1],3);
			}
}


Action BasicMotion::NexLTest()
{
	timeCounter++;
			if (timeCounter <= 15)
			{
				return readDataToStr.ReadData_Count(nexLTest[0],15);
			}
			else if (timeCounter <= 20)
			{
				return readDataToStr.ReadData_Count(nexLTest[1],5);
			}
			else if (timeCounter <= 25)
			{
				return readDataToStr.ReadData_Count(nexLTest[2],5);
			}
			else if (timeCounter <= 30)
			{
				return readDataToStr.ReadData_Count(nexLTest[3],5);
			}
			else if (timeCounter <= 35)
			{
				return readDataToStr.ReadData_Count(nexLTest[4],5);
			}
			else if (timeCounter <= 38)
			{
				return readDataToStr.ReadData_Count(nexLTest[5],3);
			}
			else if (timeCounter <= 40)
			{
				return readDataToStr.ReadData_Count(nexLTest[6],2);
			}
			else if (timeCounter <= 45)
			{
				return readDataToStr.ReadData_Count(nexLTest[7],5);
			}
			else if (timeCounter <= 50)
			{
				return readDataToStr.ReadData_Count(nexLTest[8],5);
			}
			else if (timeCounter <= 55)
			{
				return readDataToStr.ReadData_Count(nexLTest[9],5);
			}
			else if (timeCounter <= 60)
			{
				return readDataToStr.ReadData_Count(nexLTest[10],5);
			}
			else if (timeCounter <= 65)
			{
				return readDataToStr.ReadData_Count(nexLTest[11],5);
			}
			else if (timeCounter <= 85)
			{
				return readDataToStr.ReadData_Count(nexLTest[12],20);
			}
			else if (timeCounter <= 86)
			{
				return readDataToStr.ReadData_Count(nexLTest[13],1);
			}
			else if (timeCounter <= 87)
			{
				return readDataToStr.ReadData_Count(nexLTest[14],1);
			}
			else if (timeCounter <= 88)
			{
				return readDataToStr.ReadData_Count(nexLTest[15],1);
			}
			else if (timeCounter <= 90)
			{
				return readDataToStr.ReadData_Count(nexLTest[16],2);
			}
			else if (timeCounter <= 94)
			{
				return readDataToStr.ReadData_Count(nexLTest[17],4);
			}
			else if (timeCounter <= 97)
			{
				return readDataToStr.ReadData_Count(nexLTest[18],3);
			}
			else if (timeCounter <= 98)
			{
				return readDataToStr.ReadData_Count(nexLTest[19],1);
			}
			else if (timeCounter <= 100)
			{
				return readDataToStr.ReadData_Count(nexLTest[20],2);
			}
			else
			{
				return readDataToStr.ReadData_Count(aStartWalk[1],3);
			}
}

Action BasicMotion::_NexRTest()
{
	//TODO
}

//读取固定的角度，到抬脚的时候停止，只保留移动身体的部分
//coded by zhangkaikai
Action BasicMotion::_NexLTest()
{
	timeCounter++;
			if (timeCounter <= 15)
			{
				return readDataToStr.ReadData_Count(nexLTest[0],15);
			}
			else if (timeCounter <= 20)
			{
				return readDataToStr.ReadData_Count(nexLTest[1],5);
			}
			else if (timeCounter <= 25)
			{
				return readDataToStr.ReadData_Count(nexLTest[2],5);
			}
			else if (timeCounter <= 30)
			{
				return readDataToStr.ReadData_Count(nexLTest[3],5);
			}
			
			else if (timeCounter <= 35)
			{
				return readDataToStr.ReadData_Count(nexLTest[4],5);
			}

			
		//	else if (timeCounter <= 38)
		//	{
				//return readDataToStr.ReadData_Count(nexLTest[5],3);

		//	}

/*
			cout << "打印腿部位置数据" << endl;

	    	cout << uLINK[RLEG_J0].q << endl;
	    	cout << uLINK[RLEG_J1].q << endl;
		    cout << uLINK[RLEG_J2].q << endl;
		    cout << uLINK[RLEG_J3].q << endl;
			cout << uLINK[RLEG_J4].q << endl;
			cout << uLINK[RLEG_J5].q << endl;
		
			cout << uLINK[LLEG_J0].q << endl;
			cout << uLINK[LLEG_J1].q << endl;
			cout << uLINK[LLEG_J2].q << endl;
			cout << uLINK[LLEG_J3].q << endl;
			cout << uLINK[LLEG_J4].q << endl;
			cout << uLINK[LLEG_J5].q << endl;
*/	
			/*
			else if (timeCounter <= 40)
			{
				return readDataToStr.ReadData_Count(nexLTest[6],2);
			}
			
			else if (timeCounter <= 45)
			{
				return readDataToStr.ReadData_Count(nexLTest[7],5);
			}
			
			else if (timeCounter <= 50)
			{
				return readDataToStr.ReadData_Count(nexLTest[8],5);
			}
			
			else if (timeCounter <= 55)
			{
				return readDataToStr.ReadData_Count(nexLTest[9],5);
			}
			
			else if (timeCounter <= 60)
			{
				return readDataToStr.ReadData_Count(nexLTest[10],5);
			}
			else if (timeCounter <= 65)
			{
				return readDataToStr.ReadData_Count(nexLTest[11],5);
			}
			else if (timeCounter <= 85)
			{
				return readDataToStr.ReadData_Count(nexLTest[12],20);
			}
			else if (timeCounter <= 86)
			{
				return readDataToStr.ReadData_Count(nexLTest[13],1);
			}
			else if (timeCounter <= 87)
			{
				return readDataToStr.ReadData_Count(nexLTest[14],1);
			}
			else if (timeCounter <= 88)
			{
				return readDataToStr.ReadData_Count(nexLTest[15],1);
			}
			else if (timeCounter <= 90)
			{
				return readDataToStr.ReadData_Count(nexLTest[16],2);
			}
			else if (timeCounter <= 94)
			{
				return readDataToStr.ReadData_Count(nexLTest[17],4);
			}
			else if (timeCounter <= 97)
			{
				return readDataToStr.ReadData_Count(nexLTest[18],3);
			}
			else if (timeCounter <= 98)
			{
				return readDataToStr.ReadData_Count(nexLTest[19],1);
			}
			else if (timeCounter <= 100)
			{
				return readDataToStr.ReadData_Count(nexLTest[20],2);
			}
			
			else
			{
				return readDataToStr.ReadData_Count(aStartWalk[1],3);
			}
			*/
}



Action BasicMotion::ShowBasicAction()
{
	timeCounter++;
	if (timeCounter % 200 <= 100)
	{
		return readDataToStr.ReadData_Count(showBasicMotion[0],100);
	}
	else if (timeCounter % 200 <= 200)
	{
		return readDataToStr.ReadData_Count(showBasicMotion[1],100);
	}
//	else if (timeCounter % 700 <= 300)
//	{
//		return readDataToStr.ReadData_Count(showBasicMotion[2],100);
//	}
//	else if (timeCounter % 700 <= 400)
//	{
//		return readDataToStr.ReadData_Count(showBasicMotion[3],100);
//	}
//	else if (timeCounter % 700 <= 500)
//	{
//		return readDataToStr.ReadData_Count(showBasicMotion[4],100);
//	}
//	else if (timeCounter % 700 <= 600)
//	{
//		return readDataToStr.ReadData_Count(showBasicMotion[5],100);
//	}
//	else if (timeCounter % 700 <= 600)
//	{
//		return readDataToStr.ReadData_Count(showBasicMotion[6],100);
//	}
//	else
//	{
//		return readDataToStr.ReadData_Count(aStartWalk[1],3);
//	}
}


Action BasicMotion::ShortDistanceShootingBallFromUT()
{
	timeCounter++;
	if (timeCounter <= 31)
	{
		return readDataToStr.ReadData_Count(CutDataShortDistanceShootingFromUT[0], 31);
	}
	else if (timeCounter <= 38)
	{
		return readDataToStr.ReadData_Count(CutDataShortDistanceShootingFromUT[1], 7);
	}
	else if (timeCounter <= 42)
	{
		return readDataToStr.ReadData_Count(CutDataShortDistanceShootingFromUT[2], 4);
	}
	else if (timeCounter <= 45)
	{
		return readDataToStr.ReadData_Count(CutDataShortDistanceShootingFromUT[3], 3);
	}
	else if (timeCounter <= 51)
	{
		return readDataToStr.ReadData_Count(CutDataShortDistanceShootingFromUT[4], 6);
	}
	else if (timeCounter <= 57)
	{
		return readDataToStr.ReadData_Count(CutDataShortDistanceShootingFromUT[5], 6);
	}
	else if (timeCounter <= 61)
	{
		return readDataToStr.ReadData_Count(CutDataShortDistanceShootingFromUT[6], 4);
	}
	else if (timeCounter <= 66)
	{
		return readDataToStr.ReadData_Count(CutDataShortDistanceShootingFromUT[7], 5);
	}
	else
	{
		return readDataToStr.ReadData_Count(aStartWalk[1],10);
	}
}
Action BasicMotion::LeftShootingFromNexus3D()
{
	timeCounter++;
	if (timeCounter <= 10)
	{
		return readDataToStr.ReadData_Count(CutDataLeftFromNexus3D[0], 10);
	}
	else if (timeCounter <= 16)
	{
		return readDataToStr.ReadData_Count(CutDataLeftFromNexus3D[1], 6);
	}
	else if (timeCounter <= 21)
	{
		return readDataToStr.ReadData_Count(CutDataLeftFromNexus3D[2], 5);
	}
	else if (timeCounter <= 26)
	{
		return readDataToStr.ReadData_Count(CutDataLeftFromNexus3D[3], 5);
	}
	else if (timeCounter <= 31)
	{
		return readDataToStr.ReadData_Count(CutDataLeftFromNexus3D[4], 5);
	}
	else if (timeCounter <= 36)
	{
		return readDataToStr.ReadData_Count(CutDataLeftFromNexus3D[5], 5);
	}
	else if (timeCounter <= 41)
	{
		return readDataToStr.ReadData_Count(CutDataLeftFromNexus3D[6], 5);
	}
	else if (timeCounter <= 46)
	{
		return readDataToStr.ReadData_Count(CutDataLeftFromNexus3D[7], 5);
	}
	else if (timeCounter <= 51)
	{
		return readDataToStr.ReadData_Count(CutDataLeftFromNexus3D[8], 5);
	}
	else if (timeCounter <= 56)
	{
		return readDataToStr.ReadData_Count(CutDataLeftFromNexus3D[9], 5);
	}
	else if (timeCounter <= 61)
	{
		return readDataToStr.ReadData_Count(CutDataLeftFromNexus3D[10], 5);
	}
	else if (timeCounter <= 71)
	{
		return readDataToStr.ReadData_Count(CutDataLeftFromNexus3D[11], 10);
	}
	else if (timeCounter <= 76)
	{
		return readDataToStr.ReadData_Count(CutDataLeftFromNexus3D[12], 5);
	}
//	else if (timeCounter <= 80)
//	{
//		return readDataToStr.ReadData_Count(CutDataShootingFromNexus3D[13], 4);
//	}
	else if (timeCounter <= 84)
	{
		return readDataToStr.ReadData_Count(CutDataLeftFromNexus3D[14], 8);
	}
	else if (timeCounter <= 88)
	{
		return readDataToStr.ReadData_Count(CutDataLeftFromNexus3D[15], 4);
	}
	else if (timeCounter <= 92)
	{
		return readDataToStr.ReadData_Count(CutDataLeftFromNexus3D[16], 4);
	}
	else
	{
		return readDataToStr.ReadData_Count(aStartWalk[1],10);
	}
}

Action BasicMotion::ShootingFromNexus3D()
{
	timeCounter++;
	if (timeCounter <= 10)
	{
		return readDataToStr.ReadData_Count(CutDataShootingFromNexus3D[0], 10);
	}
	else if (timeCounter <= 16)
	{
		return readDataToStr.ReadData_Count(CutDataShootingFromNexus3D[1], 6);
	}
	else if (timeCounter <= 21)
	{
		return readDataToStr.ReadData_Count(CutDataShootingFromNexus3D[2], 5);
	}
	else if (timeCounter <= 26)
	{
		return readDataToStr.ReadData_Count(CutDataShootingFromNexus3D[3], 5);
	}
	else if (timeCounter <= 31)
	{
		return readDataToStr.ReadData_Count(CutDataShootingFromNexus3D[4], 5);
	}
	else if (timeCounter <= 36)
	{
		return readDataToStr.ReadData_Count(CutDataShootingFromNexus3D[5], 5);
	}
	else if (timeCounter <= 41)
	{
		return readDataToStr.ReadData_Count(CutDataShootingFromNexus3D[6], 5);
	}
	else if (timeCounter <= 46)
	{
		return readDataToStr.ReadData_Count(CutDataShootingFromNexus3D[7], 5);
	}
	else if (timeCounter <= 51)
	{
		return readDataToStr.ReadData_Count(CutDataShootingFromNexus3D[8], 5);
	}
	else if (timeCounter <= 56)
	{
		return readDataToStr.ReadData_Count(CutDataShootingFromNexus3D[9], 5);
	}
	else if (timeCounter <= 61)
	{
		return readDataToStr.ReadData_Count(CutDataShootingFromNexus3D[10], 5);
	}
//	else if (timeCounter <= 71)
//	{
//		return readDataToStr.ReadData_Count(CutDataShootingFromNexus3D[11], 10);
//	}
	else if (timeCounter <= 66)
	{
		return readDataToStr.ReadData_Count(CutDataShootingFromNexus3D[12], 5);
	}
//	else if (timeCounter <= 80)
//	{
//		return readDataToStr.ReadData_Count(CutDataShootingFromNexus3D[13], 4);
//	}
	else if (timeCounter <= 74)
	{
		return readDataToStr.ReadData_Count(CutDataShootingFromNexus3D[14], 8);
	}
	else if (timeCounter <= 78)
	{
		return readDataToStr.ReadData_Count(CutDataShootingFromNexus3D[15], 4);
	}
	else if (timeCounter <= 82)
	{
		return readDataToStr.ReadData_Count(CutDataShootingFromNexus3D[16], 4);
	}
	else
	{
		return readDataToStr.ReadData_Count(aStartWalk[1],10);
	}
}

Action BasicMotion::ShootingFromARight()
{
	timeCounter++;
//	if (timeCounter <= 10)
//	{
//		return readDataToStr.ReadData_Count(CutRightInfo[0], 5);
//	}
//	else
		if (timeCounter <= 15)
	{
		return readDataToStr.ReadData_Count(CutRightInfo[1], 15);
	}
	else if (timeCounter <= 20)
	{
		return readDataToStr.ReadData_Count(CutRightInfo[2], 5);
	}
	else if (timeCounter <= 25)
	{
		return readDataToStr.ReadData_Count(CutRightInfo[3], 5);
	}
	else if (timeCounter <= 30)
	{
		return readDataToStr.ReadData_Count(CutRightInfo[4], 5);
	}
	else if (timeCounter <= 35)
	{
		return readDataToStr.ReadData_Count(CutRightInfo[5], 5);
	}
//	else if (timeCounter <= 36)
//	{
//		return readDataToStr.ReadData_Count(CutRightInfo[6], 1);
//	}
	else if (timeCounter <= 38)
	{
		return readDataToStr.ReadData_Count(CutRightInfo[7], 3);
	}
//	else if (timeCounter <= 39)
//	{
//		return readDataToStr.ReadData_Count(CutRightInfo[8], 1);
//	}
	else if (timeCounter <= 40)
	{
		return readDataToStr.ReadData_Count(CutRightInfo[9], 2);
	}
	else if (timeCounter <= 45)
	{
		return readDataToStr.ReadData_Count(CutRightInfo[10], 5);
	}
	else if (timeCounter <= 50)
	{
		return readDataToStr.ReadData_Count(CutRightInfo[11], 5);
	}
	else if (timeCounter <= 55)
	{
		return readDataToStr.ReadData_Count(CutRightInfo[12], 5);
	}
	else if (timeCounter <= 60)
	{
		return readDataToStr.ReadData_Count(CutRightInfo[13], 5);
	}
	else if (timeCounter <= 65)
	{
		return readDataToStr.ReadData_Count(CutRightInfo[14], 5);
	}
	else if (timeCounter <= 85)
	{
		return readDataToStr.ReadData_Count(CutRightInfo[15], 20);
	}
	else if (timeCounter <= 86)
	{
		return readDataToStr.ReadData_Count(CutRightInfo[16], 1);
	}
	else if (timeCounter <= 87)
	{
		return readDataToStr.ReadData_Count(CutRightInfo[17], 1);
	}
	else if (timeCounter <= 88)
	{
		return readDataToStr.ReadData_Count(CutRightInfo[18], 1);
	}
	else if (timeCounter <= 90)
	{
		return readDataToStr.ReadData_Count(CutRightInfo[19], 2);
	}
	else if (timeCounter <= 94)
	{
		return readDataToStr.ReadData_Count(CutRightInfo[20], 4);
	}
	else if (timeCounter <= 97)
	{
		return readDataToStr.ReadData_Count(CutRightInfo[21], 3);
	}
	else if (timeCounter <= 98)
	{
		return readDataToStr.ReadData_Count(CutRightInfo[22], 1);
	}
	else if (timeCounter <= 100)
	{
		return readDataToStr.ReadData_Count(CutRightInfo[23], 2);
	}
	else
	{
		return readDataToStr.ReadData_Count(aStartWalk[1],3);
	}

}
Action BasicMotion::ShootingFromA()
{
	timeCounter++;
//	if (timeCounter <= 10)
//	{
//		return readDataToStr.ReadData_Count(CutInfo[0], 10);
//	}
//	else
	if (timeCounter <= 15)
	{
		return readDataToStr.ReadData_Count(CutInfo[1], 15);
	}
	else if (timeCounter <= 20)
	{
		return readDataToStr.ReadData_Count(CutInfo[2], 5);
	}
	else if (timeCounter <= 25)
	{
		return readDataToStr.ReadData_Count(CutInfo[3], 5);
	}
	else if (timeCounter <= 30)
	{
		return readDataToStr.ReadData_Count(CutInfo[4], 5);
	}
	else if (timeCounter <= 35)
	{
		return readDataToStr.ReadData_Count(CutInfo[5], 5);
	}
//	else if (timeCounter <= 36)
//	{
//		return readDataToStr.ReadData_Count(CutInfo[6], 1);
//	}
	else if (timeCounter <= 38)
	{
		return readDataToStr.ReadData_Count(CutInfo[7], 3);
	}
//	else if (timeCounter <= 39)
//	{
//		return readDataToStr.ReadData_Count(CutInfo[8], 1);
//	}
	else if (timeCounter <= 40)
	{
		return readDataToStr.ReadData_Count(CutInfo[9], 2);
	}
	else if (timeCounter <= 45)
	{
		return readDataToStr.ReadData_Count(CutInfo[10], 5);
	}
	else if (timeCounter <= 50)
	{
		return readDataToStr.ReadData_Count(CutInfo[11], 5);
	}
	else if (timeCounter <= 55)
	{
		return readDataToStr.ReadData_Count(CutInfo[12], 5);
	}
	else if (timeCounter <= 60)
	{
		return readDataToStr.ReadData_Count(CutInfo[13], 5);
	}
	else if (timeCounter <= 65)
	{
		return readDataToStr.ReadData_Count(CutInfo[14], 5);
	}
	else if (timeCounter <= 85)
	{
		return readDataToStr.ReadData_Count(CutInfo[15], 20);
	}
	else if (timeCounter <= 86)
	{
		return readDataToStr.ReadData_Count(CutInfo[16], 1);
	}
	else if (timeCounter <= 87)
	{
		return readDataToStr.ReadData_Count(CutInfo[17], 1);
	}
	else if (timeCounter <= 88)
	{
		return readDataToStr.ReadData_Count(CutInfo[18], 1);
	}
	else if (timeCounter <= 90)
	{
		return readDataToStr.ReadData_Count(CutInfo[19], 2);
	}
	else if (timeCounter <= 94)
	{
		return readDataToStr.ReadData_Count(CutInfo[20], 4);
	}
	else if (timeCounter <= 97)
	{
		return readDataToStr.ReadData_Count(CutInfo[21], 3);
	}
	else if (timeCounter <= 98)
	{
		return readDataToStr.ReadData_Count(CutInfo[22], 1);
	}
	else if (timeCounter <= 100)
	{
		return readDataToStr.ReadData_Count(CutInfo[23], 2);
	}
	else
	{
		return readDataToStr.ReadData_Count(aStartWalk[1],3);
	}

}

Action BasicMotion::ShootingFromNe()
{
	timeCounter++;
	if (timeCounter <= 10)
	{
		return readDataToStr.ReadData_Count(CutDataInfo[0], 10);
	}
	else if (timeCounter <= 15)
	{
		return readDataToStr.ReadData_Count(CutDataInfo[1], 5);
	}
	else if (timeCounter <= 20)
	{
		return readDataToStr.ReadData_Count(CutDataInfo[2], 5);
	}
	else if (timeCounter <= 25)
	{
		return readDataToStr.ReadData_Count(CutDataInfo[3], 5);
	}
	else if (timeCounter <= 30)
	{
		return readDataToStr.ReadData_Count(CutDataInfo[4], 5);
	}
	else if (timeCounter <= 35)
	{
		return readDataToStr.ReadData_Count(CutDataInfo[5], 5);
	}
	else if (timeCounter <= 36)
	{
		return readDataToStr.ReadData_Count(CutDataInfo[6], 1);
	}
	else if (timeCounter <= 37)
	{
		return readDataToStr.ReadData_Count(CutDataInfo[7], 1);
	}
	else if (timeCounter <= 38)
	{
		return readDataToStr.ReadData_Count(CutDataInfo[8], 1);
	}
	else if (timeCounter <= 40)
	{
		return readDataToStr.ReadData_Count(CutDataInfo[9], 2);
	}
	else if (timeCounter <= 45)
	{
		return readDataToStr.ReadData_Count(CutDataInfo[10], 5);
	}
	else if (timeCounter <= 50)
	{
		return readDataToStr.ReadData_Count(CutDataInfo[11], 5);
	}
	else if (timeCounter <= 55)
	{
		return readDataToStr.ReadData_Count(CutDataInfo[12], 5);
	}
	else if (timeCounter <= 60)
	{
		return readDataToStr.ReadData_Count(CutDataInfo[13], 5);
	}
	else if (timeCounter <= 65)
	{
		return readDataToStr.ReadData_Count(CutDataInfo[14], 5);
	}
	else if (timeCounter <= 70)
	{
		return readDataToStr.ReadData_Count(CutDataInfo[15], 5);
	}
	else if (timeCounter <= 84)
	{
		return readDataToStr.ReadData_Count(CutDataInfo[16], 14);
	}
	else if (timeCounter <= 86)
	{
		return readDataToStr.ReadData_Count(CutDataInfo[17], 2);
	}
	else if (timeCounter <= 89)
	{
		return readDataToStr.ReadData_Count(CutDataInfo[18], 3);
	}
	else if (timeCounter <= 95)
	{
		return readDataToStr.ReadData_Count(CutDataInfo[19], 6);
	}
	else if (timeCounter <= 97)
	{
		return readDataToStr.ReadData_Count(CutDataInfo[20], 2);
	}
	else if (timeCounter <= 100)
	{
		return readDataToStr.ReadData_Count(CutDataInfo[21], 3);
	}
	else
	{
		return readDataToStr.ReadData_Count(aStartWalk[1],3);
	}
}

Action BasicMotion::LeftFootShootingBallFromUT()
{
	timeCounter++;
	if(timeCounter <= 47)
	{
		return readDataToStr.ReadData_Count(leftFootShootingFromUT[1], 47);
	}
	else if(timeCounter <= 58)
	{
		return readDataToStr.ReadData_Count(leftFootShootingFromUT[2], 11);
	}
	else if(timeCounter <= 67)
	{
		return readDataToStr.ReadData_Count(leftFootShootingFromUT[3], 9);
	}
	else if(timeCounter <= 73)
	{
		return readDataToStr.ReadData_Count(leftFootShootingFromUT[4], 6);
	}
	else if(timeCounter <= 81)
	{
		return readDataToStr.ReadData_Count(leftFootShootingFromUT[5], 8);
	}
	else if(timeCounter <= 86)
	{
		return readDataToStr.ReadData_Count(leftFootShootingFromUT[6], 5);
	}
	else if(timeCounter <= 94)
	{
		return readDataToStr.ReadData_Count(leftFootShootingFromUT[7], 8);
	}
	else if(timeCounter <= 99)
	{
		return readDataToStr.ReadData_Count(leftFootShootingFromUT[8], 5);
	}
	else if(timeCounter <= 109)
	{
		return readDataToStr.ReadData_Count(leftFootShootingFromUT[9], 10);
	}
	else if(timeCounter <= 112)
	{
		return readDataToStr.ReadData_Count(leftFootShootingFromUT[10], 3);
	}
//	else if(timeCounter <= 98)
//	{
//		return readDataToStr.ReadData_Count(CutDataShootingFromUT[11], 6);
//	}
//	else if(timeCounter <= 100)
//	{
//		return readDataToStr.ReadData_Count(CutDataShootingFromUT[12], 8);
//	}
	else if(timeCounter <= 127)
	{
		return readDataToStr.ReadData_Count(leftFootShootingFromUT[13], 15);
	}
//	else if(timeCounter <= 130)
//	{
//		return readDataToStr.ReadData_Count(leftFootShootingFromUT[14], 3);
//	}
//	else if(timeCounter <= 111)
//	{
//		return readDataToStr.ReadData_Count(CutDataShootingFromUT[15], 1);
//	}
//	else if(timeCounter <= 112)
//	{
//		return readDataToStr.ReadData_Count(CutDataShootingFromUT[16], 1);
//	}
//	else if(timeCounter <= 117)
//	{
//		return readDataToStr.ReadData_Count(CutDataShootingFromUT[17], 5);
//	}
//	else if(timeCounter <= 130)
//	{
//		return readDataToStr.ReadData_Count(CutDataShootingFromUT[18], 2);
//	}
	else
	{
		return readDataToStr.ReadData_Count(aStartWalk[1],10);
	}
}


Action BasicMotion::RightFootShootingBallFromUT()
{
	timeCounter++;
	if(timeCounter <= 47)
	{
		return readDataToStr.ReadData_Count(CutDataShootingFromUT[1], 47);
	}
	else if(timeCounter <= 58)
	{
		return readDataToStr.ReadData_Count(CutDataShootingFromUT[2], 11);
	}
	else if(timeCounter <= 67)
	{
		return readDataToStr.ReadData_Count(CutDataShootingFromUT[3], 9);
	}
	else if(timeCounter <= 73)
	{
		return readDataToStr.ReadData_Count(CutDataShootingFromUT[4], 6);
	}
	else if(timeCounter <= 81)
	{
		return readDataToStr.ReadData_Count(CutDataShootingFromUT[5], 8);
	}
	else if(timeCounter <= 86)
	{
		return readDataToStr.ReadData_Count(CutDataShootingFromUT[6], 5);
	}
	else if(timeCounter <= 94)
	{
		return readDataToStr.ReadData_Count(CutDataShootingFromUT[7], 8);
	}
	else if(timeCounter <= 99)
	{
		return readDataToStr.ReadData_Count(CutDataShootingFromUT[8], 5);
	}
	else if(timeCounter <= 109)
	{
		return readDataToStr.ReadData_Count(CutDataShootingFromUT[9], 10);
	}
	else if(timeCounter <= 112)
	{
		return readDataToStr.ReadData_Count(CutDataShootingFromUT[10], 3);
	}
//	else if(timeCounter <= 98)
//	{
//		return readDataToStr.ReadData_Count(CutDataShootingFromUT[11], 6);
//	}
//	else if(timeCounter <= 100)
//	{
//		return readDataToStr.ReadData_Count(CutDataShootingFromUT[12], 8);
//	}
	else if(timeCounter <= 127)
	{
		return readDataToStr.ReadData_Count(CutDataShootingFromUT[13], 15);
	}
//	else if(timeCounter <= 130)
//	{
//		return readDataToStr.ReadData_Count(CutDataShootingFromUT[14], 3);
//	}
//	else if(timeCounter <= 111)
//	{
//		return readDataToStr.ReadData_Count(CutDataShootingFromUT[15], 1);
//	}
//	else if(timeCounter <= 112)
//	{
//		return readDataToStr.ReadData_Count(CutDataShootingFromUT[16], 1);
//	}
//	else if(timeCounter <= 117)
//	{
//		return readDataToStr.ReadData_Count(CutDataShootingFromUT[17], 5);
//	}
//	else if(timeCounter <= 130)
//	{
//		return readDataToStr.ReadData_Count(CutDataShootingFromUT[18], 2);
//	}
	else
	{
		return readDataToStr.ReadData_Count(aStartWalk[1],10);
	}
}


Action BasicMotion::LeftFootShootingBall()
{
	timeCounter++;

	if (timeCounter <= 10)
	{
		cout << "LL-timeCounter::" << timeCounter << endl;
		return readDataToStr.ReadData_Count(leftFootShootBall[0], 10); //the body recovery
	}
	else if (timeCounter <= 15)
	{
		cout << "LL-timeCounter::" << timeCounter << endl;
		return readDataToStr.ReadData_Count(leftFootShootBall[0], 5); //the body recovery
	}
	else if (timeCounter <= 35)
	{
		cout << "LL-timeCounter::" << timeCounter << endl;
		return readDataToStr.ReadData_Count(leftFootShootBall[1], 20);
	}
	else if (timeCounter <= 41)
	{
		cout << "LL-timeCounter::" << timeCounter << endl;
		return readDataToStr.ReadData_Count(leftFootShootBall[2], 6); //the body recovery
	}
	else if (timeCounter <= 46)
	{
		cout << "LL-timeCounter::" << timeCounter << endl;
		return readDataToStr.ReadData_Count(leftFootShootBall[3], 5); //the body recovery
	}
	else if (timeCounter <= 48)
	{
		cout << "LL-timeCounter::" << timeCounter << endl;
		return readDataToStr.ReadData_MaxSpeed(leftFootShootBall[4]); //the body recovery
	}
	else if (timeCounter <= 51)
	{
		cout << "LL-timeCounter::" << timeCounter << endl;
		return readDataToStr.ReadData_MaxSpeed(leftFootShootBall[5]); //the body recovery
	}
	else if (timeCounter <= 57)
	{
		cout << "LL-timeCounter::" << timeCounter << endl;
		readDataToStr.TurnHeadToFocusBall();
		return readDataToStr.ReadData_MaxSpeed(leftFootShootBall[6]); //the body recovery
	}
	else
	{
		readDataToStr.TurnHeadToFocusBall();
		cout << "LL-timeCounter::" << timeCounter << endl;
		return readDataToStr.ReadDataA(aStartWalk[1], 3);
	}
}

void BasicMotion::PassBallFront_LeftF(Angle & sendAngle, int step,
		float footLength)
{
	switch (step)
	{
	case 4:
		if (footLength > 0.05)
			readDataToStr.ReadData_Add(frontPass1[3], sendAngle);
		break;
	case 5:
		readDataToStr.ReadData_Add(frontPass1[0], sendAngle);
		break;
	case 6:
		readDataToStr.ReadData_Add(frontPass1[1], sendAngle);
		break;
	case 7:
		readDataToStr.ReadData_Add(frontPass1[2], sendAngle);
		break;
	default:
		;
	}
}

void BasicMotion::PassBallFront_RightF(Angle & sendAngle, int step,
		float footLength)
{
	switch (step)
	{
	case 4:
		if (footLength > 0.05)
			readDataToStr.ReadData_Add(frontPass1[7], sendAngle);
		break;
	case 5:
		readDataToStr.ReadData_Add(frontPass1[4], sendAngle);
		break;
	case 6:
		readDataToStr.ReadData_Add(frontPass1[5], sendAngle);
		break;
	case 7:
		readDataToStr.ReadData_Add(frontPass1[6], sendAngle);
		break;
	default:
		;
		break;
	}
}

void BasicMotion::PassBallHoriz(Angle& sendAngle, int step)
{
	if (step == 0 || step == 1)
	{
		readDataToStr.ReadData_Add(horizPass[0], sendAngle);
	}
	else if (step == 4 || step == 4 || step == 5)
	{
		readDataToStr.ReadData_Add(horizPass[2], sendAngle);
	}
	else
		readDataToStr.ReadData_Add(horizPass[1], sendAngle);
}

void BasicMotion::PassBallLeftFront(Angle& sendAngle, int step)
{
	switch (step)
	{
	case 1:
		readDataToStr.ReadData_Add(rightFrontPass[1], sendAngle);
		break;
	case 2:
		readDataToStr.ReadData_Add(rightFrontPass[2], sendAngle);
		break;
	case 3:
		readDataToStr.ReadData_Add(rightFrontPass[3], sendAngle);
		break;
	case 4:
		readDataToStr.ReadData_Add(rightFrontPass[4], sendAngle);
		break;
	case 5:
		readDataToStr.ReadData_Add(rightFrontPass[5], sendAngle);
		break;
	case 6:
		readDataToStr.ReadData_Add(rightFrontPass[6], sendAngle);
		break;
	case 7:
		readDataToStr.ReadData_Add(rightFrontPass[7], sendAngle);
		break;
	default:
		;
		break;
	}
}
void BasicMotion::PassBallRightFront(Angle& sendAngle, int step)
{
	switch (step)
	{
	case 1:
		readDataToStr.ReadData_Add(leftFrontPass[1], sendAngle);
		break;
	case 2:
		readDataToStr.ReadData_Add(leftFrontPass[2], sendAngle);
		break;
	case 3:
		readDataToStr.ReadData_Add(leftFrontPass[3], sendAngle);
		break;
	case 4:
		readDataToStr.ReadData_Add(leftFrontPass[4], sendAngle);
		break;
	case 5:
		readDataToStr.ReadData_Add(leftFrontPass[5], sendAngle);
		break;
	case 6:
		readDataToStr.ReadData_Add(leftFrontPass[6], sendAngle);
		break;
	case 7:
		readDataToStr.ReadData_Add(leftFrontPass[7], sendAngle);
		CITConf.RightAttack = false;
		break;
	default:
		;
	}
}

void BasicMotion::PassBallBack_LeftF(Angle& sendAngle, int step) /// do not work well,needs improve
{
	if (step == 5 || step == 6 || step == 7)
		readDataToStr.ReadData_Add(backPass[1], sendAngle);
}

void BasicMotion::PassBallBack_RightF(Angle& sendAngle, int step) /// do not work well,needs improve
{
	if (step == 5 || step == 6 || step == 7)
		readDataToStr.ReadData_Add(backPass[0], sendAngle);
}

void BasicMotion::PassBallLeftFront_LessS(Angle& sendAngle, int step)
{
	switch (step)
	{
	case 1:
		readDataToStr.ReadData_Add(rightFrontPass_LessStrength[1], sendAngle);
		break;
	case 2:
		readDataToStr.ReadData_Add(rightFrontPass_LessStrength[2], sendAngle);
		break;
	case 3:
		readDataToStr.ReadData_Add(rightFrontPass_LessStrength[3], sendAngle);
		break;
	case 4:
		readDataToStr.ReadData_Add(rightFrontPass_LessStrength[4], sendAngle);
		break;
	case 5:
		readDataToStr.ReadData_Add(rightFrontPass_LessStrength[5], sendAngle);
		break;
	case 6:
		readDataToStr.ReadData_Add(rightFrontPass_LessStrength[6], sendAngle);
		break;
	case 7:
		readDataToStr.ReadData_Add(rightFrontPass_LessStrength[7], sendAngle);
		break;
	default:
		;
	}
}
void BasicMotion::PassBallRightFront_LessS(Angle& sendAngle, int step)
{
	switch (step)
	{
	case 1:
		readDataToStr.ReadData_Add(leftFrontPass_LessStrength[1], sendAngle);
		break;
	case 2:
		readDataToStr.ReadData_Add(leftFrontPass_LessStrength[2], sendAngle);
		break;
	case 3:
		readDataToStr.ReadData_Add(leftFrontPass_LessStrength[3], sendAngle);
		break;
	case 4:
		readDataToStr.ReadData_Add(leftFrontPass_LessStrength[4], sendAngle);
		break;
	case 5:
		readDataToStr.ReadData_Add(leftFrontPass_LessStrength[5], sendAngle);
		break;
	case 6:
		readDataToStr.ReadData_Add(leftFrontPass_LessStrength[6], sendAngle);
		break;
	case 7:
		readDataToStr.ReadData_Add(leftFrontPass_LessStrength[7], sendAngle);
		CITConf.RightAttack = false;
		break;
	default:
		;
		break;
	}
}

Action BasicMotion::StandingUpFromBack_old()
{
	cout<<"timeCounter::::::::::::::::::::::"<<timeCounter<<endl;
	if(agent.GetType()==3)
	{
		//cout<<"jjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjj"<<endl;
		timeCounter++;
			if (timeCounter <= 30)
			{
				return readDataToStr.ReadData_Count(aStandUpBackward_old3[0], 10); //the body recovery
			}
			else if (timeCounter <= 55)
			{
				return readDataToStr.ReadData_Count(aStandUpBackward_old3[1], 20); //
			}
			else if (timeCounter <= 74)
			{
				return readDataToStr.ReadData_Count(aStandUpBackward_old3[2], 9); //
			}
			else if (timeCounter <= 96)
			{
				return readDataToStr.ReadData_Count(aStandUpBackward_old3[6], 10); //11 or 10
			}
			else if (timeCounter <= 115)
			{
				return readDataToStr.AllStop(); //
			}
			else
			{
				return readDataToStr.ReadDataA(aStartWalk[1], 3);
			}
	}
	else if(agent.GetType()==1)
	{
		cout<<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<endl;
		timeCounter++;
			if (timeCounter <= 30)
			{
				return readDataToStr.ReadData_Count(aStandUpBackward_old1[0], 10); //the body recovery
			}
			else if (timeCounter <= 55)
			{
				return readDataToStr.ReadData_Count(aStandUpBackward_old1[1], 20); //
			}
			else if (timeCounter <= 75)
			{
				return readDataToStr.ReadData_Count(aStandUpBackward_old1[2],10); //
			}
			else if (timeCounter <=88)
			{
				return readDataToStr.ReadData_Count(aStandUpBackward_old1[6], 9); //
			}
			else if (timeCounter <= 110)
			{
				return readDataToStr.AllStop(); //
			}
			else
			{
				return readDataToStr.ReadDataA(aStartWalk[1], 3);
			}
	}
	else
	{
				timeCounter++;
							if (timeCounter <= 30)
							{
								return readDataToStr.ReadData_Count(aStandUpBackward_old[0], 10); //the body recovery
							}
							else if (timeCounter <= 55)
							{
								return readDataToStr.ReadData_Count(aStandUpBackward_old[1], 20); //
							}
							else if (timeCounter <= 75)
							{
								return readDataToStr.ReadData_Count(aStandUpBackward_old[2], 10); //
							}
							else if (timeCounter <= 88)
							{
								return readDataToStr.ReadData_Count(aStandUpBackward_old[6], 9); //
							}
							else if (timeCounter <= 110)
							{
								return readDataToStr.AllStop(); //
							}
							else
							{
								return readDataToStr.ReadDataA(aStartWalk[1], 3);
							}
	}

}
Action BasicMotion::SlideTackle(Direction dir)
{
	timeCounter++;
	if (timeCounter < 10)
	{
		if (dir == Left)
		{
			return readDataToStr.ReadData_Count(slideTackleData[2], 10); //
		}
		else
		{
			return readDataToStr.ReadData_Count(slideTackleData[3], 10); //
		}
	}
	else if (timeCounter < 30)
	{
		if (dir == Left)
		{
			return readDataToStr.ReadData_Count(slideTackleData[0], 10); //
		}
		else
		{
			return readDataToStr.ReadData_Count(slideTackleData[1], 10); //
		}
	}
	else
	{
		readDataToStr.TurnHeadToFocusBall();
		return readDataToStr.AllStopExceptHead();
	}
}

