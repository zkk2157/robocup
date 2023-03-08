#ifndef BASICMOTION_H
#define BASICMOTION_H
/*/////////////////////////////////////////////////////////////
   * all  the  motions  of  NAO  in  CIT3D  Team
   * 
   * 		           2011-03-22
*//////////////////////////////////////////////////////////////
# include <iostream>

# include "math.h"

#include "../Stdafx.h"

using namespace std;

class BasicMotion
{
public:
	BasicMotion();
	
	Action    	StandingUpFromFront();  			 /// stand up
	
	Action 		StandingUpFromBack();   			 /// stand up
	
	Action 		StandingUpFromBackByUT();

	Action 		PreventingFowardFallingDown(); 		/// stand up
	
	Action 		PreventingBackFallingDown();  		/// stadn up
	
	Action 		SplitingToSaveBall();   			/// goal keeper motion
	
	Action 		RightFootShootingBall();  		/// shoot ball
	
	Action 		LeftFootShootingBall();  		/// shoot ball
	Action     RightFootShootingBallCIT();
	Action 		LeftFootShootingBallCIT();
	Action  NexRTest();
	Action  NexLTest();
	Action  _NexLTest();
	Action  _NexRTest();

	Action RoboCansRighttoLeft();
	Action RoboCansLefttoRight();

	Action RoboCansRighttoLeft4();
	Action RoboCansLefttoRight4();

   Action LeftShootapollo();
   Action RightShootapollo();

	Action		ShootingFromNexus3D();

	Action		LeftShootingFromNexus3D();

	Action		ShootingFromA();

	Action		ShootingFromARight();

	Action		ShootingFromNe();

	Action		LeftFootShootingBallFromUT();

	Action		RightFootShootingBallFromUT();

	Action		ShortDistanceShootingBallFromUT();

	Action		ShowBasicAction();

	Action 		InitStandUpPose();     			/// init pose
	
	Action 		StopAllMotion();    			/// stop all joint 
	
	Action 		DealFallingDown(int style);  		/// deal falling 
	
	Action         	SlideTackle(Direction dir);            	///in chinese 铲球
	
	void 		PassBallFront_LeftF(Angle & sendAngle,int step,float footLength); 		/// great strength  front pass
	void 		PassBallFront_RightF(Angle & sendAngle,int step,float footLength); 		/// great strength  front pass
		
	void 		PassBallLeftFront(Angle & sendAngle,int step);			/// left front pass	
	void 		PassBallRightFront(Angle & sendAngle,int step);			/// right front pass

	void 		PassBallLeftFront_LessS(Angle & sendAngle,int step);			/// left front pass,with less strength	
	void 		PassBallRightFront_LessS(Angle & sendAngle,int step);			/// right front pass,with less strength

	
	void 		PassBallBack_LeftF(Angle & sendAngle,int step);			///back pass

	void 		PassBallBack_RightF(Angle & sendAngle,int step);		///back pass
	
	void 		PassBallHoriz(Angle & sendAngle,int step);				/// horiz pass
	
	
	
	void 		SetTimeCounter(int num);			
	int 		GetTimeCounter();
	
	Action  StandingUpFromBack_old();
	void  CalculatingTrackData();
	
private:
	int timeCounter;
	
	bool exceptionalCase;


};
#endif
