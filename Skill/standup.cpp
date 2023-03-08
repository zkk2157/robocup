/*
 * standup.cpp
 *
 *  Created on: 2012-2-29
 *      Author: cit
 */

#include "standup.h"
extern BasicMotion basicMotion;
extern WorldModel wm;
extern Strategy behavior;
extern Perceptor messageParser;
extern NewWalk newWalk; ///lr
Cstandup::Cstandup()
{
	// TODO Auto-generated constructor stub
	estimateFallDirectionTimer.SetLimitTime(5);
	walkBegain = true;
	fallingDown = false;
	fallDown = false;
	faceToGround = false;
	faceToSky = false;
	beginStandUp = true;
	finishStandUpMotion = true;
	justAfterStandUp = false;
	fallDownTurnHeadToFindTwoflags = false;
}

Action Cstandup::StandUp()
{
	behavior.turnHeadStrategy(behavior.GetfallDownTurnHead());
	if (estimateFallDirectionTimer.IsTimeOut() == false)
	{
		if (wm.GetMyFallDirection() == D_FORWARD)
		{
			faceToGround = true;
			faceToSky = false;
			///////cout<<"wm.GetMyFallDirection() == D_FORWARD"<<endl;
		}
		else if (wm.GetMyFallDirection() == D_BACK)
		{
			faceToSky = true;
			faceToGround = false;
			///////cout<<"wm.GetMyFallDirection() == D_BACK"<<endl;

		}
		else
		{
		}
	}
	if (justAfterSplits)
	{
		///////////////cout<<"***************justAfterStandUp********************"<<endl;
		faceToGround = true;
		faceToSky = false;
	}
	if (faceToGround == true)
	{
		///////////////cout<<"				stand     Up    from front!! "<<endl;
		return PreventForwardFallingDown();
		//return StandUpFromFront();
	}
	else if (faceToSky == true)
	{
		//return PreventBackFallingDown();
		///////////////cout<<"				stand     Up    from back!! "<<endl;
		return StandUpFromBack();
	}
	else
	{
		estimateFallDirectionTimer.ClearCounter();
		fallDown = false;
		return basicMotion.StopAllMotion();
	}

}
Action Cstandup::DisposeFalling()
{
	if (finishStandUpMotion == true)
	{
		if (wm.GetMyFallDirection() == D_FORWARD)
		{
			faceToGround = true;
			faceToSky = false;
		}
		else if (wm.GetMyFallDirection() == D_BACK)
		{
			faceToSky = true;
			faceToGround = false;
		}
		finishStandUpMotion = false;
	}
	//}
	if (faceToGround == true)
	{
		///////////cout<<"****************D_FORWARD    prevent   Fall    Down_FORWARD"<<endl;
		return PreventForwardFallingDown();
	}
	else if (faceToSky == true)
	{
		///////////cout<<"  ************D_BACK ing**************turn to stand up from back!!"<<endl;
		//return basicMotion.StopAllMotion();
		return PreventBackFallingDown();
	}
	else
	{
		estimateFallDirectionTimer.ClearCounter();
		fallDown = false;
		return basicMotion.StopAllMotion();
	}
}
Action Cstandup::dealFallingDown()
{
	if (wm.GetMyFallDirection() == D_BACK)
	{
		newWalk.changeBody_P(D_BACK);
		return basicMotion.DealFallingDown(0);
	}
	else if (wm.GetMyFallDirection() == D_LEFT)
	{
		newWalk.changeBody_P(D_LEFT);
		/////cout<<"wm.GetCurrentJointAngle(JID_LARM_2)  :"<<wm.GetCurrentJointAngle(JID_LARM_2)<<endl;
		if (fabs(wm.GetCurrentJointAngle(JID_LARM_2)) < 55)
			return basicMotion.DealFallingDown(1);
		else
			return basicMotion.DealFallingDown(0);
	}
	else if (wm.GetMyFallDirection() == D_RIGHT)
	{
		newWalk.changeBody_P(D_RIGHT);
		/////cout<<"wm.GetCurrentJointAngle(JID_RARM_2)  :"<<wm.GetCurrentJointAngle(JID_RARM_2)<<endl;
		if (fabs(wm.GetCurrentJointAngle(JID_RARM_2)) < 55)
			return basicMotion.DealFallingDown(2);
		else
			return basicMotion.DealFallingDown(0);
	}
	return "";
}
void Cstandup::doJudgeFallDown()
{
	if (!fallingDown)
	{
		fallingDown = wm.IsFallingDown_test();
	}
	else //fallingDown=true,wait for self body stable
	{
		fallDown = wm.IsFallDown_test();
		if (fallDown)
			fallingDown = false;
	}
}

Action Cstandup::StandUpFromFront()
{
	behavior.turnHeadStrategy(behavior.GetfallDownTurnHead());
	/////////////cout<<"time :"<<wm.GetCurrentGameTime()<<"		stand up from front!!!"<<basicMotion.GetTimeCounter()<<endl;
	if (beginStandUp)
	{ /////////////cout<<"stand up set 0"<<endl;
		basicMotion.SetTimeCounter(0);
		beginStandUp = false;
		if (messageParser.mHingeJointSenseMap[JID_RLEG_1].angle < -50
				|| messageParser.mHingeJointSenseMap[JID_RLEG_1].angle > 50)
		{
			basicMotion.SetTimeCounter(-15);
			/////////////cout<<"stand up later!!!!!!!";
		}
	}
	if (basicMotion.GetTimeCounter() > 75)
	{
		SGYRSensor gyrSensor = messageParser.GetGYR();
		if ((abs(gyrSensor.x) <= 5 && basicMotion.GetTimeCounter() >= 100)
				|| basicMotion.GetTimeCounter() > 150)
		{
			beginStandUp = true;
			fallDown = false;
			faceToGround = false;
			estimateFallDirectionTimer.ClearCounter();
			newWalk.hasFallDown = true;
			behavior.initSplits();
			behavior.initHalfStepParameter();
			behavior.initShootControlParameter();

			fallDownTurnHeadToFindTwoflags = true;
			finishStandUpMotion = true;
			if (!wm.whetherStandedUp())
			{
				fallDown = true;
			}
		}
	}
	return basicMotion.StandingUpFromFront();
}
Action Cstandup::StandUpFromBack()
{
	//turnHeadStrategy(fallDownTurnHead);
		if (beginStandUp)
		{
			basicMotion.SetTimeCounter(0);
			beginStandUp = false;
		}
		/*if(messageParser.abnormalServerCycle==false)
		{
			if (basicMotion.GetTimeCounter() > 90)
			{
				SGYRSensor gyrSensor = messageParser.GetGYR();
				if ((abs(gyrSensor.x) <= 5 && basicMotion.GetTimeCounter() >= 100)
						|| basicMotion.GetTimeCounter() > 120)
				{
					beginStandUp = true;
					fallDown = false;
					faceToGround = false;
					estimateFallDirectionTimer.ClearCounter();
					newWalk.hasFallDown = true;
					behavior.initSplits();
					behavior.initHalfStepParameter();

					behavior.initShootControlParameter();

					fallDownTurnHeadToFindTwoflags = true;

					finishStandUpMotion = true;
					if (!wm.whetherStandedUp())
					{
						fallDown = true;
					}
				}
			}
			return basicMotion.StandingUpFromBack();
		}
		else*/
		{
	//		cout<<"	if(messageParser.abnormalServerCycle==true) standup"<<endl;
			if(basicMotion.GetTimeCounter()>150)
			{
				SGYRSensor gyrSensor=messageParser.GetGYR();
				if(( abs(gyrSensor.x) <=5 && basicMotion.GetTimeCounter()>= 100 )|| basicMotion.GetTimeCounter()>120)
				{
					beginStandUp=true;
					fallDown=false;
					faceToGround=false;
					estimateFallDirectionTimer.ClearCounter();
					newWalk.hasFallDown=true;
					behavior.initSplits();
					behavior.initHalfStepParameter();

					behavior.initShootControlParameter();

					fallDownTurnHeadToFindTwoflags=true;

					finishStandUpMotion=true;
					if(!wm.whetherStandedUp())
					{
						fallDown=true;
					}
				}
			}
			return basicMotion.StandingUpFromBack_old();
		}

}

Action Cstandup::PreventBackFallingDown() //while NAO is falling down,stand up///not in use
{
	if (beginStandUp)
	{
		basicMotion.SetTimeCounter(0);
		beginStandUp = false;
		noFRPCount = 0;
	}

	if (basicMotion.GetTimeCounter() >= 25
			&& basicMotion.GetTimeCounter() <= 34)
	{
		if (messageParser.GetFRP(FID_LEFT).f.z == 0
				&& messageParser.GetFRP(FID_RIGHT).f.z == 0)
		{
			noFRPCount++;
			///////cout<<"no FRP!!!!!!!!!!!!!!!!!!!!!!!"<<endl;
		}
		if (noFRPCount > 8)
		{
			if (wm.whetherStandedUp())
			{
				fallDown = false;
			}
			else
			{
				fallDown = true;
			}
			faceToGround = false;
			faceToSky = false;
			walkBegain = true;
			beginStandUp = true;
			finishStandUpMotion = true;
			estimateFallDirectionTimer.ClearCounter();
			behavior.initSplits();
			newWalk.hasFallDown = true;
			fallingDown = false;
			justAfterStandUp = true;
			behavior.initShootControlParameter();
		}
	}

	if (basicMotion.GetTimeCounter() > 60)
	{

		if (basicMotion.GetTimeCounter() > 95)
		{
			if (wm.whetherStandedUp())
			{
				fallDown = false;
			}
			else
			{
				fallDown = true;
			}
			faceToGround = false;
			faceToSky = false;
			walkBegain = true;
			beginStandUp = true;
			finishStandUpMotion = true;
			estimateFallDirectionTimer.ClearCounter();
			newWalk.hasFallDown = true;
			fallingDown = false;
			justAfterStandUp = true;
			behavior.initShootControlParameter();
		}
	}
	return basicMotion.PreventingBackFallingDown();
}

Action Cstandup::PreventForwardFallingDown() //while NAO is falling down,stand up///not in use
{
	if (beginStandUp)
	{
		basicMotion.SetTimeCounter(0);
		beginStandUp = false;
	}

	if (basicMotion.GetTimeCounter() > 55)
	{
		if (basicMotion.GetTimeCounter() >= 92)
		{
			if (wm.whetherStandedUp())
			{
				fallDown = false;
			}
			else
			{
				fallDown = true;
			}
			faceToGround = false;
			faceToSky = false;
			walkBegain = true;
			beginStandUp = true;
			finishStandUpMotion = true;
			estimateFallDirectionTimer.ClearCounter();
			behavior.initSplits();
			newWalk.hasFallDown = true;
			fallingDown = false;
			justAfterStandUp = true;
			behavior.initShootControlParameter();
		}
	}
	return basicMotion.PreventingFowardFallingDown();
}
Cstandup::~Cstandup()
{
	// TODO Auto-generated destructor stub
}

