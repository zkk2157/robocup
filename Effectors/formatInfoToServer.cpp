#include "formatInfoToServer.h"


extern Perceptor messageParser;
extern JointEffector mp;

FormatInfoToServer::FormatInfoToServer()
{
	beginReadData=false;
	
	Head1a=0;
	Head2a=0;
	Larm1a=0;
	Larm2a=0;
	Larm3a=0;
	Larm4a=0;
	Rarm1a=0;
	Rarm2a=0;
	Rarm3a=0;
	Rarm4a=0;
	Lleg1a=0;
	Lleg2a=0;
	Lleg3a=0;
	Lleg4a=0;
	Lleg5a=0;
	Lleg6a=0;
	Rleg1a=0;
	Rleg2a=0;
	Rleg3a=0;
	Rleg4a=0;
	Rleg5a=0;
	Rleg6a=0;
	
	turnHeadAngle=0;
}

#if 1
Action FormatInfoToServer::ReadDataA( Angle Data)   ///两个角度之差
{
	int gain=1;

	float angHead1 = messageParser.mHingeJointSenseMap[JID_HEAD_1].angle;
	float angHead2 = messageParser.mHingeJointSenseMap[JID_HEAD_2].angle;

	float angLleg1 = messageParser.mHingeJointSenseMap[JID_LLEG_1].angle;
	float angLleg2 = messageParser.mHingeJointSenseMap[JID_LLEG_2].angle;	
	float angLleg3 = messageParser.mHingeJointSenseMap[JID_LLEG_3].angle;
	float angLleg4 = messageParser.mHingeJointSenseMap[JID_LLEG_4].angle;	
	float angLleg5 = messageParser.mHingeJointSenseMap[JID_LLEG_5].angle;
	float angLleg6 = messageParser.mHingeJointSenseMap[JID_LLEG_6].angle;

	float angRleg1 = messageParser.mHingeJointSenseMap[JID_RLEG_1].angle;
	float angRleg2 = messageParser.mHingeJointSenseMap[JID_RLEG_2].angle;	
	float angRleg3 = messageParser.mHingeJointSenseMap[JID_RLEG_3].angle;
	float angRleg4 = messageParser.mHingeJointSenseMap[JID_RLEG_4].angle;	
	float angRleg5 = messageParser.mHingeJointSenseMap[JID_RLEG_5].angle;
	float angRleg6 = messageParser.mHingeJointSenseMap[JID_RLEG_6].angle;

	float angLarm1 = messageParser.mHingeJointSenseMap[JID_LARM_1].angle;	
	float angLarm2 = messageParser.mHingeJointSenseMap[JID_LARM_2].angle;	
	float angLarm3 = messageParser.mHingeJointSenseMap[JID_LARM_3].angle;	
	float angLarm4 = messageParser.mHingeJointSenseMap[JID_LARM_4].angle;

	float angRarm1 = messageParser.mHingeJointSenseMap[JID_RARM_1].angle;	
	float angRarm2 = messageParser.mHingeJointSenseMap[JID_RARM_2].angle;	
	float angRarm3 = messageParser.mHingeJointSenseMap[JID_RARM_3].angle;	
	float angRarm4 = messageParser.mHingeJointSenseMap[JID_RARM_4].angle;


	stringstream ss("");

	ss<<
	 mp.HJHead_1Deg(approximate(Data.Head1.Aimangle-angHead1)*gain)//trun into rad
	+ mp.HJLarm_1Deg(approximate(Data.Larm1.Aimangle-angLarm1)*gain)
	+ mp.HJLarm_2Deg(approximate(Data.Larm2.Aimangle-angLarm2)*gain)
	+ mp.HJLarm_3Deg(approximate(Data.Larm3.Aimangle-angLarm3)*gain)
	+ mp.HJLarm_4Deg(approximate(Data.Larm4.Aimangle-angLarm4)*gain)
	+ mp.HJLleg_1Deg(approximate(Data.Lleg1.Aimangle-angLleg1)*gain)
	+ mp.HJLleg_2Deg(approximate(Data.Lleg2.Aimangle-angLleg2)*gain)
	+ mp.HJLleg_3Deg(approximate(Data.Lleg3.Aimangle-angLleg3)*gain)
	+ mp.HJLleg_4Deg(approximate(Data.Lleg4.Aimangle-angLleg4)*gain)
	+ mp.HJLleg_5Deg(approximate(Data.Lleg5.Aimangle-angLleg5)*gain)
	+ mp.HJLleg_6Deg(approximate(Data.Lleg6.Aimangle-angLleg6)*gain)
	+ mp.HJHead_2Deg(approximate(Data.Head2.Aimangle-angHead2)*gain)
	+ mp.HJRarm_1Deg(approximate(Data.Rarm1.Aimangle-angRarm1)*gain)
	+ mp.HJRarm_2Deg(approximate(Data.Rarm2.Aimangle-angRarm2)*gain)
	+ mp.HJRarm_3Deg(approximate(Data.Rarm3.Aimangle-angRarm3)*gain)
	+ mp.HJRarm_4Deg(approximate(Data.Rarm4.Aimangle-angRarm4)*gain)
	+ mp.HJRleg_1Deg(approximate(Data.Rleg1.Aimangle-angRleg1)*gain)
	+ mp.HJRleg_2Deg(approximate(Data.Rleg2.Aimangle-angRleg2)*gain)
	+ mp.HJRleg_3Deg(approximate(Data.Rleg3.Aimangle-angRleg3)*gain)
	+ mp.HJRleg_4Deg(approximate(Data.Rleg4.Aimangle-angRleg4)*gain)
	+ mp.HJRleg_5Deg(approximate(Data.Rleg5.Aimangle-angRleg5)*gain)
	+ mp.HJRleg_6Deg(approximate(Data.Rleg6.Aimangle-angRleg6)*gain);

	return ss.str();
}
#endif
#if 1
Action FormatInfoToServer::ReadDataA( Angle Data,float gain)   ///两个角度之差
{

/// 4/17
	float angHead1 = messageParser.mHingeJointSenseMap[JID_HEAD_1].angle;
	float angHead2 = messageParser.mHingeJointSenseMap[JID_HEAD_2].angle;

	float angLleg1 = messageParser.mHingeJointSenseMap[JID_LLEG_1].angle;
	float angLleg2 = messageParser.mHingeJointSenseMap[JID_LLEG_2].angle;	
	float angLleg3 = messageParser.mHingeJointSenseMap[JID_LLEG_3].angle;
	float angLleg4 = messageParser.mHingeJointSenseMap[JID_LLEG_4].angle;	
	float angLleg5 = messageParser.mHingeJointSenseMap[JID_LLEG_5].angle;
	float angLleg6 = messageParser.mHingeJointSenseMap[JID_LLEG_6].angle;

	float angRleg1 = messageParser.mHingeJointSenseMap[JID_RLEG_1].angle;
	float angRleg2 = messageParser.mHingeJointSenseMap[JID_RLEG_2].angle;	
	float angRleg3 = messageParser.mHingeJointSenseMap[JID_RLEG_3].angle;
	float angRleg4 = messageParser.mHingeJointSenseMap[JID_RLEG_4].angle;	
	float angRleg5 = messageParser.mHingeJointSenseMap[JID_RLEG_5].angle;
	float angRleg6 = messageParser.mHingeJointSenseMap[JID_RLEG_6].angle;

	float angLarm1 = messageParser.mHingeJointSenseMap[JID_LARM_1].angle;	
	float angLarm2 = messageParser.mHingeJointSenseMap[JID_LARM_2].angle;	
	float angLarm3 = messageParser.mHingeJointSenseMap[JID_LARM_3].angle;	
	float angLarm4 = messageParser.mHingeJointSenseMap[JID_LARM_4].angle;

	float angRarm1 = messageParser.mHingeJointSenseMap[JID_RARM_1].angle;	
	float angRarm2 = messageParser.mHingeJointSenseMap[JID_RARM_2].angle;	
	float angRarm3 = messageParser.mHingeJointSenseMap[JID_RARM_3].angle;	
	float angRarm4 = messageParser.mHingeJointSenseMap[JID_RARM_4].angle;
	


	stringstream ss("");
	
	ss<<
	  mp.HJHead_1Deg(approximate(turnHeadAngle-angHead1)*gain)
	+ mp.HJLarm_1Deg(approximate(Data.Larm1.Aimangle-angLarm1)*gain)
	+ mp.HJLarm_2Deg(approximate(Data.Larm2.Aimangle-angLarm2)*gain)
	+ mp.HJLarm_3Deg(approximate(Data.Larm3.Aimangle-angLarm3)*gain)
	+ mp.HJLarm_4Deg(approximate(Data.Larm4.Aimangle-angLarm4)*gain)
	+ mp.HJLleg_1Deg(approximate(Data.Lleg1.Aimangle-angLleg1)*gain)
	+ mp.HJLleg_2Deg(approximate(Data.Lleg2.Aimangle-angLleg2)*gain)
	+ mp.HJLleg_3Deg(approximate(Data.Lleg3.Aimangle-angLleg3)*gain)
	+ mp.HJLleg_4Deg(approximate(Data.Lleg4.Aimangle-angLleg4)*gain)
	+ mp.HJLleg_5Deg(approximate(Data.Lleg5.Aimangle-angLleg5)*gain)
	+ mp.HJLleg_6Deg(approximate(Data.Lleg6.Aimangle-angLleg6)*gain)
	+ mp.HJHead_2Deg(approximate(-45-angHead2)*gain)
	+ mp.HJRarm_1Deg(approximate(Data.Rarm1.Aimangle-angRarm1)*gain)
	+ mp.HJRarm_2Deg(approximate(Data.Rarm2.Aimangle-angRarm2)*gain)
	+ mp.HJRarm_3Deg(approximate(Data.Rarm3.Aimangle-angRarm3)*gain)
	+ mp.HJRarm_4Deg(approximate(Data.Rarm4.Aimangle-angRarm4)*gain)
	+ mp.HJRleg_1Deg(approximate(Data.Rleg1.Aimangle-angRleg1)*gain)
	+ mp.HJRleg_2Deg(approximate(Data.Rleg2.Aimangle-angRleg2)*gain)
	+ mp.HJRleg_3Deg(approximate(Data.Rleg3.Aimangle-angRleg3)*gain)
	+ mp.HJRleg_4Deg(approximate(Data.Rleg4.Aimangle-angRleg4)*gain)
	+ mp.HJRleg_5Deg(approximate(Data.Rleg5.Aimangle-angRleg5)*gain)
	+ mp.HJRleg_6Deg(approximate(Data.Rleg6.Aimangle-angRleg6)*gain);

	return ss.str();
}
#endif
#if 1
/// 角度相减
Action FormatInfoToServer::ReadDataA(Angle Data,float gain,float Rdistance,float Rhigh,float Ldistance,float Lhigh)
{
		float k,d,b,c,x,y,Rdatui,Rxiaotui,Ldatui,Lxiaotui;
		k=Rhigh*Rhigh+ShankHeight*ShankHeight+Rdistance*Rdistance-ThighHeight*ThighHeight;
		d=4.0*Rdistance*Rdistance*ShankHeight*ShankHeight+4.0*Rhigh*Rhigh*ShankHeight*ShankHeight;
		b=4.0*Rdistance*ShankHeight*k;
		c=k*k-4.0*Rhigh*Rhigh*ShankHeight*ShankHeight;
		x=(-b+sqrt(b*b-4.0*d*c))/(2.0*d);
		y=(x*ShankHeight+Rdistance)/ThighHeight;
		Rdatui=mp.Rad2Deg(asin(y));
		Rxiaotui=mp.Rad2Deg(asin(x))+Rdatui;	


		k=Lhigh*Lhigh+ShankHeight*ShankHeight+Ldistance*Ldistance-ThighHeight*ThighHeight;
		d=4.0*Ldistance*Ldistance*ShankHeight*ShankHeight+4.0*Lhigh*Lhigh*ShankHeight*ShankHeight;
		b=4.0*Ldistance*ShankHeight*k;
		c=k*k-4.0*Lhigh*Lhigh*ShankHeight*ShankHeight;
		x=(-b+sqrt(b*b-4.0*d*c))/(2.0*d);
		y=(x*ShankHeight+Ldistance)/ThighHeight;
		Ldatui=mp.Rad2Deg(asin(y));
		Lxiaotui=mp.Rad2Deg(asin(x))+Ldatui;

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

	stringstream ss("");

	ss<<
	 mp.HJHead_1Deg(approximate(turnHeadAngle-angHead1)*gain)
	+mp.HJLarm_1Deg(approximate(Data.Larm1.Aimangle-angLarm1)*gain)
	+ mp.HJLarm_2Deg(approximate(Data.Larm2.Aimangle-angLarm2)*gain)
	+ mp.HJLarm_3Deg(approximate(Data.Larm3.Aimangle-angLarm3)*gain)
	+ mp.HJLarm_4Deg(approximate(Data.Larm4.Aimangle-angLarm4)*gain)
	+ mp.HJLleg_1Deg(approximate(Data.Lleg1.Aimangle-angLleg1)*gain)
	+ mp.HJLleg_2Deg(approximate(Data.Lleg2.Aimangle-angLleg2)*gain)
	+ mp.HJLleg_3Deg(approximate(Ldatui-angLleg3)*gain)
	+ mp.HJLleg_4Deg(approximate(-Lxiaotui-angLleg4)*gain)
	+ mp.HJLleg_5Deg(approximate(Lxiaotui-Ldatui-angLleg5)*gain)
	+ mp.HJLleg_6Deg(approximate(Data.Lleg6.Aimangle-angLleg6)*gain)
	+ mp.HJHead_2Deg(approximate(Data.Head2.Aimangle-angHead2)*gain)
	+ mp.HJRarm_1Deg(approximate(Data.Rarm1.Aimangle-angRarm1)*gain)
	+ mp.HJRarm_2Deg(approximate(Data.Rarm2.Aimangle-angRarm2)*gain)
	+ mp.HJRarm_3Deg(approximate(Data.Rarm3.Aimangle-angRarm3)*gain)
	+ mp.HJRarm_4Deg(approximate(Data.Rarm4.Aimangle-angRarm4)*gain)
	+ mp.HJRleg_1Deg(approximate(Data.Rleg1.Aimangle-angRleg1)*gain)
	+ mp.HJRleg_2Deg(approximate(Data.Rleg2.Aimangle-angRleg2)*gain)
	+ mp.HJRleg_3Deg(approximate(Rdatui-angRleg3)*gain)
	+ mp.HJRleg_4Deg(approximate(-Rxiaotui-angRleg4)*gain)
	+ mp.HJRleg_5Deg(approximate(Rxiaotui-Rdatui-angRleg5)*gain)
	+ mp.HJRleg_6Deg(approximate(Data.Rleg6.Aimangle-angRleg6)*gain);

	return ss.str();
}
#endif
Action FormatInfoToServer::AllStop()
{
	return	  mp.HJHead_1Rad(0) + mp.HJHead_2Rad(0)
		+ mp.HJLarm_1Rad(0) + mp.HJRarm_1Rad(0)
		+ mp.HJLarm_2Rad(0) + mp.HJRarm_2Rad(0)
		+ mp.HJLarm_3Rad(0) + mp.HJRarm_3Rad(0)
		+ mp.HJLarm_4Rad(0) + mp.HJRarm_4Rad(0)
		+ mp.HJLleg_1Rad(0) + mp.HJRleg_1Rad(0)
		+ mp.HJLleg_2Rad(0) + mp.HJRleg_2Rad(0)
		+ mp.HJLleg_3Rad(0) + mp.HJRleg_3Rad(0)
		+ mp.HJLleg_4Rad(0) + mp.HJRleg_4Rad(0)
		+ mp.HJLleg_5Rad(0) + mp.HJRleg_5Rad(0)
		+ mp.HJLleg_6Rad(0) + mp.HJRleg_6Rad(0);
}
Action FormatInfoToServer::AllStopExceptHead()
{
	float angHead1 = messageParser.mHingeJointSenseMap[JID_HEAD_1].angle;
	float angHead2 = messageParser.mHingeJointSenseMap[JID_HEAD_2].angle;
	return	 
	 mp.HJHead_1Deg(approximate(turnHeadAngle-angHead1)*3) + mp.HJHead_2Deg(approximate(50-angHead2)*3)
	+ mp.HJLarm_1Rad(0) + mp.HJRarm_1Rad(0)
	+ mp.HJLarm_2Rad(0) + mp.HJRarm_2Rad(0)
	+ mp.HJLarm_3Rad(0) + mp.HJRarm_3Rad(0)
	+ mp.HJLarm_4Rad(0) + mp.HJRarm_4Rad(0)
	+ mp.HJLleg_1Rad(0) + mp.HJRleg_1Rad(0)
	+ mp.HJLleg_2Rad(0) + mp.HJRleg_2Rad(0)
	+ mp.HJLleg_3Rad(0) + mp.HJRleg_3Rad(0)
	+ mp.HJLleg_4Rad(0) + mp.HJRleg_4Rad(0)
	+ mp.HJLleg_5Rad(0) + mp.HJRleg_5Rad(0)
	+ mp.HJLleg_6Rad(0) + mp.HJRleg_6Rad(0);

}


#if 1
Action FormatInfoToServer::ReadData_Count( Angle Data,int Count)    /// Count个周期内直接达到角度
{

	if(beginReadData)
	{
		readDataCounter=0;
#if 1
		Head1a=turnHeadAngle-messageParser.mHingeJointSenseMap[JID_HEAD_1].angle;
		Head2a=Data.Head2.Aimangle-messageParser.mHingeJointSenseMap[JID_HEAD_2].angle;
		Larm1a=Data.Larm1.Aimangle-messageParser.mHingeJointSenseMap[JID_LARM_1].angle;
		Larm2a=Data.Larm2.Aimangle-messageParser.mHingeJointSenseMap[JID_LARM_2].angle;
		Larm3a=Data.Larm3.Aimangle-messageParser.mHingeJointSenseMap[JID_LARM_3].angle;
		Larm4a=Data.Larm4.Aimangle-messageParser.mHingeJointSenseMap[JID_LARM_4].angle;
		Rarm1a=Data.Rarm1.Aimangle-messageParser.mHingeJointSenseMap[JID_RARM_1].angle;
		Rarm2a=Data.Rarm2.Aimangle-messageParser.mHingeJointSenseMap[JID_RARM_2].angle;
		Rarm3a=Data.Rarm3.Aimangle-messageParser.mHingeJointSenseMap[JID_RARM_3].angle;
		Rarm4a=Data.Rarm4.Aimangle-messageParser.mHingeJointSenseMap[JID_RARM_4].angle;
		Lleg1a=Data.Lleg1.Aimangle-messageParser.mHingeJointSenseMap[JID_LLEG_1].angle;
		Lleg2a=Data.Lleg2.Aimangle-messageParser.mHingeJointSenseMap[JID_LLEG_2].angle;
		Lleg3a=Data.Lleg3.Aimangle-messageParser.mHingeJointSenseMap[JID_LLEG_3].angle;
		Lleg4a=Data.Lleg4.Aimangle-messageParser.mHingeJointSenseMap[JID_LLEG_4].angle;
		Lleg5a=Data.Lleg5.Aimangle-messageParser.mHingeJointSenseMap[JID_LLEG_5].angle;
		Lleg6a=Data.Lleg6.Aimangle-messageParser.mHingeJointSenseMap[JID_LLEG_6].angle;
		Rleg1a=Data.Rleg1.Aimangle-messageParser.mHingeJointSenseMap[JID_RLEG_1].angle;
		Rleg2a=Data.Rleg2.Aimangle-messageParser.mHingeJointSenseMap[JID_RLEG_2].angle;
		Rleg3a=Data.Rleg3.Aimangle-messageParser.mHingeJointSenseMap[JID_RLEG_3].angle;
		Rleg4a=Data.Rleg4.Aimangle-messageParser.mHingeJointSenseMap[JID_RLEG_4].angle;
		Rleg5a=Data.Rleg5.Aimangle-messageParser.mHingeJointSenseMap[JID_RLEG_5].angle;
		Rleg6a=Data.Rleg6.Aimangle-messageParser.mHingeJointSenseMap[JID_RLEG_6].angle;
#endif
		beginReadData=false;
	}


	readDataCounter++;
	if(readDataCounter == Count)
	{
		beginReadData=true;
	}
		
	stringstream ss("");

	ss<<
	  	mp.HJHead_1Rad((Head1a/Count*PI*50)/180)
		+ mp.HJHead_2Rad((Head2a/Count*PI*50)/180)
		+ mp.HJLarm_1Rad((Larm1a/Count*PI*50)/180)
		+ mp.HJRarm_1Rad((Rarm1a/Count*PI*50)/180)
		+ mp.HJLarm_2Rad((Larm2a/Count*PI*50)/180)
		+ mp.HJRarm_2Rad((Rarm2a/Count*PI*50)/180)
		+ mp.HJLarm_3Rad((Larm3a/Count*PI*50)/180)
		+ mp.HJRarm_3Rad((Rarm3a/Count*PI*50)/180)
		+ mp.HJLarm_4Rad((Larm4a/Count*PI*50)/180)
		+ mp.HJRarm_4Rad((Rarm4a/Count*PI*50)/180)
		+ mp.HJLleg_1Rad((Lleg1a/Count*PI*50)/180)
		+ mp.HJRleg_1Rad((Rleg1a/Count*PI*50)/180)
		+ mp.HJLleg_2Rad((Lleg2a/Count*PI*50)/180)
		+ mp.HJRleg_2Rad((Rleg2a/Count*PI*50)/180)
		+ mp.HJLleg_3Rad((Lleg3a/Count*PI*50)/180)
		+ mp.HJRleg_3Rad((Rleg3a/Count*PI*50)/180)
		+ mp.HJLleg_4Rad((Lleg4a/Count*PI*50)/180)
		+ mp.HJRleg_4Rad((Rleg4a/Count*PI*50)/180)
		+ mp.HJLleg_5Rad((Lleg5a/Count*PI*50)/180)
		+ mp.HJRleg_5Rad((Rleg5a/Count*PI*50)/180)
		+ mp.HJLleg_6Rad((Lleg6a/Count*PI*50)/180)
		+ mp.HJRleg_6Rad((Rleg6a/Count*PI*50)/180);

	return ss.str();

}
#endif
#if 0
Action FormatInfoToServer::ReadDataD( Angle Data,float Rdistance,float Rhigh,float Ldistance,float Lhigh,float Rleg1,float Lleg1,float Rleg2,float Lleg2,float Rleg6,float Lleg6)
{

	float k,d,b,c,x,y,Rdatui,Rxiaotui,Ldatui,Lxiaotui;


	ReadDataSimTime=GetSimTime();
	bBeginReadData= false;
	k=Rhigh*Rhigh+ShankHeight*ShankHeight+Rdistance*Rdistance-ThighHeight*ThighHeight;
	d=4.0*Rdistance*Rdistance*ShankHeight*ShankHeight+4.0*Rhigh*Rhigh*ShankHeight*ShankHeight;
	b=4.0*Rdistance*ShankHeight*k;
	c=k*k-4.0*Rhigh*Rhigh*ShankHeight*ShankHeight;
	x=(-b+sqrt(b*b-4.0*d*c))/(2.0*d);
	y=(x*ShankHeight+Rdistance)/ThighHeight;
	Rdatui=Rad2Deg(asin(y));
	Rxiaotui=Rad2Deg(asin(x))+Rdatui;

	k=Lhigh*Lhigh+ShankHeight*ShankHeight+Ldistance*Ldistance-ThighHeight*ThighHeight;
	d=4.0*Ldistance*Ldistance*ShankHeight*ShankHeight+4.0*Lhigh*Lhigh*ShankHeight*ShankHeight;
	b=4.0*Ldistance*ShankHeight*k;
	c=k*k-4.0*Lhigh*Lhigh*ShankHeight*ShankHeight;
	x=(-b+sqrt(b*b-4.0*d*c))/(2.0*d);
	y=(x*ShankHeight+Ldistance)/ThighHeight;
	Ldatui=Rad2Deg(asin(y));
	Lxiaotui=Rad2Deg(asin(x))+Ldatui;




	TIME mydeltaTime = GetSimTime()-ReadDataSimTime;///0.02s一周期 准备0.02s

	float angHead1,angHead2;
	float angLleg1,angLleg2,angLleg3,angLleg4,angLleg5,angLleg6;
	float angRleg1,angRleg2,angRleg3,angRleg4,angRleg5,angRleg6;
	float angLarm1,angLarm2,angLarm3,angLarm4;
	float angRarm1,angRarm2,angRarm3,angRarm4;


	Record_Received_JointSense();	///记录曾经收到的server发送的消息


	if(bBeginReadDataD==true)
	{
		bBeginReadDataD =false;

		IsFirstinReadData = true;
		CountinReadData = 0;

		angHead1 = mHingeJointSenseMap[JID_HEAD_1].angle;
		angHead2 = mHingeJointSenseMap[JID_HEAD_2].angle;
	
		angLleg1 = mHingeJointSenseMap[JID_LLEG_1].angle;
		angLleg2 = mHingeJointSenseMap[JID_LLEG_2].angle;
		angLleg3 = mHingeJointSenseMap[JID_LLEG_3].angle;
		angLleg4 = mHingeJointSenseMap[JID_LLEG_4].angle;
		angLleg5 = mHingeJointSenseMap[JID_LLEG_5].angle;
		angLleg6 = mHingeJointSenseMap[JID_LLEG_6].angle;
	
		angRleg1 = mHingeJointSenseMap[JID_RLEG_1].angle;
		angRleg2 = mHingeJointSenseMap[JID_RLEG_2].angle;
		angRleg3 = mHingeJointSenseMap[JID_RLEG_3].angle;
		angRleg4 = mHingeJointSenseMap[JID_RLEG_4].angle;
		angRleg5 = mHingeJointSenseMap[JID_RLEG_5].angle;
		angRleg6 = mHingeJointSenseMap[JID_RLEG_6].angle;
	
		angLarm1 = mHingeJointSenseMap[JID_LARM_1].angle;
		angLarm2 = mHingeJointSenseMap[JID_LARM_2].angle;
		angLarm3 = mHingeJointSenseMap[JID_LARM_3].angle;
		angLarm4 = mHingeJointSenseMap[JID_LARM_4].angle;
	
		angRarm1 = mHingeJointSenseMap[JID_RARM_1].angle;
		angRarm2 = mHingeJointSenseMap[JID_RARM_2].angle;
		angRarm3 = mHingeJointSenseMap[JID_RARM_3].angle;
		angRarm4 = mHingeJointSenseMap[JID_RARM_4].angle;
	}
	else
	{
		angHead1 = YuCe_mHingeJointSenseMap[JID_HEAD_1].angle;
		angHead2 = YuCe_mHingeJointSenseMap[JID_HEAD_2].angle;
	
		angLleg1 = YuCe_mHingeJointSenseMap[JID_LLEG_1].angle;
		angLleg2 = YuCe_mHingeJointSenseMap[JID_LLEG_2].angle;
		angLleg3 = YuCe_mHingeJointSenseMap[JID_LLEG_3].angle;
		angLleg4 = YuCe_mHingeJointSenseMap[JID_LLEG_4].angle;
		angLleg5 = YuCe_mHingeJointSenseMap[JID_LLEG_5].angle;
		angLleg6 = YuCe_mHingeJointSenseMap[JID_LLEG_6].angle;
	
		angRleg1 = YuCe_mHingeJointSenseMap[JID_RLEG_1].angle;
		angRleg2 = YuCe_mHingeJointSenseMap[JID_RLEG_2].angle;
		angRleg3 = YuCe_mHingeJointSenseMap[JID_RLEG_3].angle;
		angRleg4 = YuCe_mHingeJointSenseMap[JID_RLEG_4].angle;
		angRleg5 = YuCe_mHingeJointSenseMap[JID_RLEG_5].angle;
		angRleg6 = YuCe_mHingeJointSenseMap[JID_RLEG_6].angle;
	
		angLarm1 = YuCe_mHingeJointSenseMap[JID_LARM_1].angle;
		angLarm2 = YuCe_mHingeJointSenseMap[JID_LARM_2].angle;
		angLarm3 = YuCe_mHingeJointSenseMap[JID_LARM_3].angle;
		angLarm4 = YuCe_mHingeJointSenseMap[JID_LARM_4].angle;
	
		angRarm1 = YuCe_mHingeJointSenseMap[JID_RARM_1].angle;
		angRarm2 = YuCe_mHingeJointSenseMap[JID_RARM_2].angle;
		angRarm3 = YuCe_mHingeJointSenseMap[JID_RARM_3].angle;
		angRarm4 = YuCe_mHingeJointSenseMap[JID_RARM_4].angle;
	}

	if(i_SendedCount==3)
	{
		Delay_mHingeJointSenseMap[JID_HEAD_1].angle = Received_mHingeJointSenseMap3[JID_HEAD_1].angle-Sended_mHingeJointSenseMap2[JID_HEAD_1].angle;
		Delay_mHingeJointSenseMap[JID_HEAD_2].angle = Received_mHingeJointSenseMap3[JID_HEAD_2].angle-Sended_mHingeJointSenseMap2[JID_HEAD_2].angle;

		Delay_mHingeJointSenseMap[JID_LARM_1].angle = Received_mHingeJointSenseMap3[JID_LARM_1].angle-Sended_mHingeJointSenseMap2[JID_LARM_1].angle;
		Delay_mHingeJointSenseMap[JID_LARM_2].angle = Received_mHingeJointSenseMap3[JID_LARM_2].angle-Sended_mHingeJointSenseMap2[JID_LARM_2].angle;
		Delay_mHingeJointSenseMap[JID_LARM_3].angle = Received_mHingeJointSenseMap3[JID_LARM_3].angle-Sended_mHingeJointSenseMap2[JID_LARM_3].angle;
		Delay_mHingeJointSenseMap[JID_LARM_4].angle = Received_mHingeJointSenseMap3[JID_LARM_4].angle-Sended_mHingeJointSenseMap2[JID_LARM_4].angle;

		Delay_mHingeJointSenseMap[JID_RARM_1].angle = Received_mHingeJointSenseMap3[JID_RARM_1].angle-Sended_mHingeJointSenseMap2[JID_RARM_1].angle;
		Delay_mHingeJointSenseMap[JID_RARM_2].angle = Received_mHingeJointSenseMap3[JID_RARM_2].angle-Sended_mHingeJointSenseMap2[JID_RARM_2].angle;
		Delay_mHingeJointSenseMap[JID_RARM_3].angle = Received_mHingeJointSenseMap3[JID_RARM_3].angle-Sended_mHingeJointSenseMap2[JID_RARM_3].angle;
		Delay_mHingeJointSenseMap[JID_RARM_4].angle = Received_mHingeJointSenseMap3[JID_RARM_4].angle-Sended_mHingeJointSenseMap2[JID_RARM_4].angle;

		Delay_mHingeJointSenseMap[JID_LLEG_1].angle = Received_mHingeJointSenseMap3[JID_LLEG_1].angle-Sended_mHingeJointSenseMap2[JID_LLEG_1].angle;
		Delay_mHingeJointSenseMap[JID_LLEG_2].angle = Received_mHingeJointSenseMap3[JID_LLEG_2].angle-Sended_mHingeJointSenseMap2[JID_LLEG_2].angle;
		Delay_mHingeJointSenseMap[JID_LLEG_3].angle = Received_mHingeJointSenseMap3[JID_LLEG_3].angle-Sended_mHingeJointSenseMap2[JID_LLEG_3].angle;
		Delay_mHingeJointSenseMap[JID_LLEG_4].angle = Received_mHingeJointSenseMap3[JID_LLEG_4].angle-Sended_mHingeJointSenseMap2[JID_LLEG_4].angle;
		Delay_mHingeJointSenseMap[JID_LLEG_5].angle = Received_mHingeJointSenseMap3[JID_LLEG_5].angle-Sended_mHingeJointSenseMap2[JID_LLEG_5].angle;
		Delay_mHingeJointSenseMap[JID_LLEG_6].angle = Received_mHingeJointSenseMap3[JID_LLEG_6].angle-Sended_mHingeJointSenseMap2[JID_LLEG_6].angle;

		Delay_mHingeJointSenseMap[JID_RLEG_1].angle = Received_mHingeJointSenseMap3[JID_RLEG_1].angle-Sended_mHingeJointSenseMap2[JID_RLEG_1].angle;
		Delay_mHingeJointSenseMap[JID_RLEG_2].angle = Received_mHingeJointSenseMap3[JID_RLEG_2].angle-Sended_mHingeJointSenseMap2[JID_RLEG_2].angle;
		Delay_mHingeJointSenseMap[JID_RLEG_3].angle = Received_mHingeJointSenseMap3[JID_RLEG_3].angle-Sended_mHingeJointSenseMap2[JID_RLEG_3].angle;
		Delay_mHingeJointSenseMap[JID_RLEG_4].angle = Received_mHingeJointSenseMap3[JID_RLEG_4].angle-Sended_mHingeJointSenseMap2[JID_RLEG_4].angle;
		Delay_mHingeJointSenseMap[JID_RLEG_5].angle = Received_mHingeJointSenseMap3[JID_RLEG_5].angle-Sended_mHingeJointSenseMap2[JID_RLEG_5].angle;
		Delay_mHingeJointSenseMap[JID_RLEG_6].angle = Received_mHingeJointSenseMap3[JID_RLEG_6].angle-Sended_mHingeJointSenseMap2[JID_RLEG_6].angle;

	}
	else
		Delay_mHingeJointSenseMap.clear();

// 	Delay_mHingeJointSenseMap.clear();

	if(IsFirstinReadData)
	{
		Delay_mHingeJointSenseMap.clear();
		CountinReadData++;
		if(CountinReadData>=10)
			IsFirstinReadData = false;
	}
	
	Head1a=Data.Head1.Aimangle-angHead1-Delay_mHingeJointSenseMap[JID_HEAD_1].angle;
	Head2a=Data.Head2.Aimangle-angHead2-Delay_mHingeJointSenseMap[JID_HEAD_2].angle;

	Larm1a=Data.Larm1.Aimangle-angLarm1-Delay_mHingeJointSenseMap[JID_LARM_1].angle;
	Larm2a=Data.Larm2.Aimangle-angLarm2-Delay_mHingeJointSenseMap[JID_LARM_2].angle;
	Larm3a=Data.Larm3.Aimangle-angLarm3-Delay_mHingeJointSenseMap[JID_LARM_3].angle;
	Larm4a=Data.Larm4.Aimangle-angLarm4-Delay_mHingeJointSenseMap[JID_LARM_4].angle;

	Rarm1a=Data.Rarm1.Aimangle-angRarm1-Delay_mHingeJointSenseMap[JID_RARM_1].angle;
	Rarm2a=Data.Rarm2.Aimangle-angRarm2-Delay_mHingeJointSenseMap[JID_RARM_2].angle;
	Rarm3a=Data.Rarm3.Aimangle-angRarm3-Delay_mHingeJointSenseMap[JID_RARM_3].angle;
	Rarm4a=Data.Rarm4.Aimangle-angRarm4-Delay_mHingeJointSenseMap[JID_RARM_4].angle;

	Lleg1a=Lleg1-angLleg1-Delay_mHingeJointSenseMap[JID_LLEG_1].angle;
	Lleg2a=Lleg2-angLleg2-Delay_mHingeJointSenseMap[JID_LLEG_2].angle;
	Lleg3a=Ldatui-angLleg3-Delay_mHingeJointSenseMap[JID_LLEG_3].angle;
	Lleg4a=-Lxiaotui-angLleg4-Delay_mHingeJointSenseMap[JID_LLEG_4].angle;
	Lleg5a=Lxiaotui-Ldatui-angLleg5-Delay_mHingeJointSenseMap[JID_LLEG_5].angle;
	Lleg6a=Lleg6-angLleg6-Delay_mHingeJointSenseMap[JID_LLEG_6].angle;

	Rleg1a=Rleg1-angRleg1-Delay_mHingeJointSenseMap[JID_RLEG_1].angle;
	Rleg2a=Rleg2-angRleg2-Delay_mHingeJointSenseMap[JID_RLEG_2].angle;
	Rleg3a=Rdatui-angRleg3-Delay_mHingeJointSenseMap[JID_RLEG_3].angle;
	Rleg4a=-Rxiaotui-angRleg4-Delay_mHingeJointSenseMap[JID_RLEG_4].angle;
	Rleg5a=Rxiaotui-Rdatui-angRleg5-Delay_mHingeJointSenseMap[JID_RLEG_5].angle;
	Rleg6a=Rleg6-angRleg6-Delay_mHingeJointSenseMap[JID_RLEG_6].angle;
	
	YuCe_mHingeJointSenseMap[JID_HEAD_1].angle = Data.Head1.Aimangle;
	YuCe_mHingeJointSenseMap[JID_HEAD_2].angle = Data.Head2.Aimangle;

	YuCe_mHingeJointSenseMap[JID_LLEG_1].angle = Lleg1;
	YuCe_mHingeJointSenseMap[JID_LLEG_2].angle = Lleg2;
	YuCe_mHingeJointSenseMap[JID_LLEG_3].angle = Ldatui;
	YuCe_mHingeJointSenseMap[JID_LLEG_4].angle = -Lxiaotui;
	YuCe_mHingeJointSenseMap[JID_LLEG_5].angle = Lxiaotui-Ldatui;
	YuCe_mHingeJointSenseMap[JID_LLEG_6].angle = Lleg6;

	YuCe_mHingeJointSenseMap[JID_RLEG_1].angle = Rleg1;
	YuCe_mHingeJointSenseMap[JID_RLEG_2].angle = Rleg2;
	YuCe_mHingeJointSenseMap[JID_RLEG_3].angle = Rdatui;
	YuCe_mHingeJointSenseMap[JID_RLEG_4].angle = -Rxiaotui;
	YuCe_mHingeJointSenseMap[JID_RLEG_5].angle = Rxiaotui-Rdatui;
	YuCe_mHingeJointSenseMap[JID_RLEG_6].angle = Rleg6;

	YuCe_mHingeJointSenseMap[JID_LARM_1].angle = Data.Larm1.Aimangle;
	YuCe_mHingeJointSenseMap[JID_LARM_2].angle = Data.Larm2.Aimangle;
	YuCe_mHingeJointSenseMap[JID_LARM_3].angle = Data.Larm3.Aimangle;
	YuCe_mHingeJointSenseMap[JID_LARM_4].angle = Data.Larm4.Aimangle;

	YuCe_mHingeJointSenseMap[JID_RARM_1].angle = Data.Rarm1.Aimangle;
	YuCe_mHingeJointSenseMap[JID_RARM_2].angle = Data.Rarm2.Aimangle;
	YuCe_mHingeJointSenseMap[JID_RARM_3].angle = Data.Rarm3.Aimangle;
	YuCe_mHingeJointSenseMap[JID_RARM_4].angle = Data.Rarm4.Aimangle;

	Record_Sended_JointSense();	///记录 Agent 发送的消息

	stringstream ss("");


///判断角度是否超过限制
#if 1
if(abs(Lleg3a) > 7.0354)
{
// 	cout<<"(warning!):Ldatui:"<<abs(Lleg3a) - 7.0354<<endl;
	if(Lleg3a > 0)
		Lleg3a = 7.1;
	else
		Lleg3a = -7.1;
}

if(abs(Lleg4a) > 7.0354)
{
// 	cout<<"(warning!):Lxiaotui:"<<abs(Lleg4a) - 7.0354<<endl;
	if(Lleg4a > 0)
		Lleg4a = 7.1;
	else
		Lleg4a = -7.1;
}

if(abs(Lleg5a) > 7.0354)
{
// 	cout<<"(warning!):Lxiaotui:"<<abs(Lleg5a) - 7.0354<<endl;
	if(Lleg5a > 0)
		Lleg5a = 7.1;
	else
		Lleg5a = -7.1;
}

if(abs(Rleg3a) > 7.0354)
{
// 	cout<<"(warning!):Rdatui:"<<abs(Rleg3a) - 7.0354<<endl;
	if(Rleg3a > 0)
		Rleg3a = 7.1;
	else
		Rleg3a = -7.1;
}

if(abs(Rleg4a) > 7.0354)
{
// 	cout<<"(warning!):Rxiaotui:"<<abs(Rleg4a) - 7.0354<<endl;
	if(Rleg4a > 0)
		Rleg4a = 7.1;
	else
		Rleg4a = -7.1;
}

if(abs(Rleg5a) > 7.0354)
{
// 	cout<<"(warning!):Rxiaotui:"<<abs(Rleg5a) - 7.0354<<endl;
	if(Rleg5a > 0)
		Rleg5a = 7.1;
	else
		Rleg5a = -7.1;
}
#endif


	ss<<
	  HJHead_1Rad((Head1a*PI*50)/180)
	+ HJLarm_1Rad((Larm1a*PI*50)/180)
	+ HJLarm_2Rad((Larm2a*PI*50)/180)
	+ HJLarm_3Rad((Larm3a*PI*50)/180)
	+ HJLarm_4Rad((Larm4a*PI*50)/180)
	+ HJLleg_1Rad((Lleg1a*PI*50)/180)
	+ HJLleg_2Rad((Lleg2a*PI*50)/180)
	+ HJLleg_3Rad((Lleg3a*PI*50)/180)
	+ HJLleg_4Rad((Lleg4a*PI*50)/180)
	+ HJLleg_5Rad((Lleg5a*PI*50)/180)
	+ HJLleg_6Rad((Lleg6a*PI*50)/180)
	+ HJHead_2Rad((Head2a*PI*50)/180)
	+ HJRarm_1Rad((Rarm1a*PI*50)/180)
	+ HJRarm_2Rad((Rarm2a*PI*50)/180)
	+ HJRarm_3Rad((Rarm3a*PI*50)/180)
	+ HJRarm_4Rad((Rarm4a*PI*50)/180)
	+ HJRleg_1Rad((Rleg1a*PI*50)/180)
	+ HJRleg_2Rad((Rleg2a*PI*50)/180)
	+ HJRleg_3Rad((Rleg3a*PI*50)/180)
	+ HJRleg_4Rad((Rleg4a*PI*50)/180)
	+ HJRleg_5Rad((Rleg5a*PI*50)/180)
	+ HJRleg_6Rad((Rleg6a*PI*50)/180);

	return ss.str();

}
#endif
Action FormatInfoToServer::AdjustByMaxSpeed(Angle Data)
{
	Head1a=Data.Head1.Aimangle-messageParser.mHingeJointSenseMap[JID_HEAD_1].angle;
	Head2a=Data.Head2.Aimangle-messageParser.mHingeJointSenseMap[JID_HEAD_2].angle;
	Larm1a=Data.Larm1.Aimangle-messageParser.mHingeJointSenseMap[JID_LARM_1].angle;
	Larm2a=Data.Larm2.Aimangle-messageParser.mHingeJointSenseMap[JID_LARM_2].angle;
	Larm3a=Data.Larm3.Aimangle-messageParser.mHingeJointSenseMap[JID_LARM_3].angle;
	Larm4a=Data.Larm4.Aimangle-messageParser.mHingeJointSenseMap[JID_LARM_4].angle;
	Rarm1a=Data.Rarm1.Aimangle-messageParser.mHingeJointSenseMap[JID_RARM_1].angle;
	Rarm2a=Data.Rarm2.Aimangle-messageParser.mHingeJointSenseMap[JID_RARM_2].angle;
	Rarm3a=Data.Rarm3.Aimangle-messageParser.mHingeJointSenseMap[JID_RARM_3].angle;
	Rarm4a=Data.Rarm4.Aimangle-messageParser.mHingeJointSenseMap[JID_RARM_4].angle;
	Lleg1a=Data.Lleg1.Aimangle-messageParser.mHingeJointSenseMap[JID_LLEG_1].angle;
	Lleg2a=Data.Lleg2.Aimangle-messageParser.mHingeJointSenseMap[JID_LLEG_2].angle;
	Lleg3a=Data.Lleg3.Aimangle-messageParser.mHingeJointSenseMap[JID_LLEG_3].angle;
	Lleg4a=Data.Lleg4.Aimangle-messageParser.mHingeJointSenseMap[JID_LLEG_4].angle;
	Lleg5a=Data.Lleg5.Aimangle-messageParser.mHingeJointSenseMap[JID_LLEG_5].angle;
	Lleg6a=Data.Lleg6.Aimangle-messageParser.mHingeJointSenseMap[JID_LLEG_6].angle;
	Rleg1a=Data.Rleg1.Aimangle-messageParser.mHingeJointSenseMap[JID_RLEG_1].angle;
	Rleg2a=Data.Rleg2.Aimangle-messageParser.mHingeJointSenseMap[JID_RLEG_2].angle;
	Rleg3a=Data.Rleg3.Aimangle-messageParser.mHingeJointSenseMap[JID_RLEG_3].angle;
	Rleg4a=Data.Rleg4.Aimangle-messageParser.mHingeJointSenseMap[JID_RLEG_4].angle;
	Rleg5a=Data.Rleg5.Aimangle-messageParser.mHingeJointSenseMap[JID_RLEG_5].angle;
	Rleg6a=Data.Rleg6.Aimangle-messageParser.mHingeJointSenseMap[JID_RLEG_6].angle;
	
	AdjustParameter(Head1a);
	AdjustParameter(Head2a);
	AdjustParameter(Larm1a);
	AdjustParameter(Larm2a);
	AdjustParameter(Larm3a);
	AdjustParameter(Larm4a);
	AdjustParameter(Rarm1a);
	AdjustParameter(Rarm2a);
	AdjustParameter(Rarm3a);
	AdjustParameter(Rarm4a);
	AdjustParameter(Lleg1a);
	AdjustParameter(Lleg2a);
	AdjustParameter(Lleg3a);
	AdjustParameter(Lleg4a);
	AdjustParameter(Lleg5a);
	AdjustParameter(Lleg6a);
	AdjustParameter(Rleg1a);
	AdjustParameter(Rleg2a);
	AdjustParameter(Rleg3a);
	AdjustParameter(Rleg4a);
	AdjustParameter(Rleg5a);
	AdjustParameter(Rleg6a);
	
	stringstream ss("");
	
	float temp=100;
	
	ss<<
			mp.HJHead_1Rad((Head1a*PI*temp)/180)
			+ mp.HJHead_2Rad((Head2a*PI*temp)/180)
			+ mp.HJLarm_1Rad((Larm1a*PI*temp)/180)
			+ mp.HJRarm_1Rad((Rarm1a*PI*temp)/180)
			+ mp.HJLarm_2Rad((Larm2a*PI*temp)/180)
			+ mp.HJRarm_2Rad((Rarm2a*PI*temp)/180)
			+ mp.HJLarm_3Rad((Larm3a*PI*temp)/180)
			+ mp.HJRarm_3Rad((Rarm3a*PI*temp)/180)
			+ mp.HJLarm_4Rad((Larm4a*PI*temp)/180)
			+ mp.HJRarm_4Rad((Rarm4a*PI*temp)/180)
			+ mp.HJLleg_1Rad((Lleg1a*PI*temp)/180)
			+ mp.HJRleg_1Rad((Rleg1a*PI*temp)/180)
			+ mp.HJLleg_2Rad((Lleg2a*PI*temp)/180)
			+ mp.HJRleg_2Rad((Rleg2a*PI*temp)/180)
			+ mp.HJLleg_6Rad((Lleg6a*PI*temp)/180)
			+ mp.HJRleg_6Rad((Rleg6a*PI*temp)/180);
	
	return ss.str();
}

void FormatInfoToServer::AdjustParameter(float & angle)
{
	if(fabs(angle) > 7)
	{
		if(angle > 0)
			angle=7;
		else
			angle=-7;
	}
}
#if 1
Action FormatInfoToServer::ReadDataMax( Angle Data)    /// Count个周期内直接达到角度
{
	Head1a=Data.Head1.Aimangle-messageParser.mHingeJointSenseMap[JID_HEAD_1].angle;
	Head2a=Data.Head2.Aimangle-messageParser.mHingeJointSenseMap[JID_HEAD_2].angle;
	Larm1a=Data.Larm1.Aimangle-messageParser.mHingeJointSenseMap[JID_LARM_1].angle;
	Larm2a=Data.Larm2.Aimangle-messageParser.mHingeJointSenseMap[JID_LARM_2].angle;
	Larm3a=Data.Larm3.Aimangle-messageParser.mHingeJointSenseMap[JID_LARM_3].angle;
	Larm4a=Data.Larm4.Aimangle-messageParser.mHingeJointSenseMap[JID_LARM_4].angle;
	Rarm1a=Data.Rarm1.Aimangle-messageParser.mHingeJointSenseMap[JID_RARM_1].angle;
	Rarm2a=Data.Rarm2.Aimangle-messageParser.mHingeJointSenseMap[JID_RARM_2].angle;
	Rarm3a=Data.Rarm3.Aimangle-messageParser.mHingeJointSenseMap[JID_RARM_3].angle;
	Rarm4a=Data.Rarm4.Aimangle-messageParser.mHingeJointSenseMap[JID_RARM_4].angle;
	Lleg1a=Data.Lleg1.Aimangle-messageParser.mHingeJointSenseMap[JID_LLEG_1].angle;
	Lleg2a=Data.Lleg2.Aimangle-messageParser.mHingeJointSenseMap[JID_LLEG_2].angle;
	Lleg3a=Data.Lleg3.Aimangle-messageParser.mHingeJointSenseMap[JID_LLEG_3].angle;
	Lleg4a=Data.Lleg4.Aimangle-messageParser.mHingeJointSenseMap[JID_LLEG_4].angle;
	Lleg5a=Data.Lleg5.Aimangle-messageParser.mHingeJointSenseMap[JID_LLEG_5].angle;
	Lleg6a=Data.Lleg6.Aimangle-messageParser.mHingeJointSenseMap[JID_LLEG_6].angle;
	Rleg1a=Data.Rleg1.Aimangle-messageParser.mHingeJointSenseMap[JID_RLEG_1].angle;
	Rleg2a=Data.Rleg2.Aimangle-messageParser.mHingeJointSenseMap[JID_RLEG_2].angle;
	Rleg3a=Data.Rleg3.Aimangle-messageParser.mHingeJointSenseMap[JID_RLEG_3].angle;
	Rleg4a=Data.Rleg4.Aimangle-messageParser.mHingeJointSenseMap[JID_RLEG_4].angle;
	Rleg5a=Data.Rleg5.Aimangle-messageParser.mHingeJointSenseMap[JID_RLEG_5].angle;
	Rleg6a=Data.Rleg6.Aimangle-messageParser.mHingeJointSenseMap[JID_RLEG_6].angle;

  stringstream ss("");
  int Count=1;
	
  ss<<
      mp.HJHead_1Rad((Head1a/Count*PI*50)/180)
		  + mp.HJHead_2Rad((Head2a/Count*PI*50)/180)
		  + mp.HJLarm_1Rad((Larm1a/Count*PI*50)/180)
		  + mp.HJRarm_1Rad((Rarm1a/Count*PI*50)/180)
		  + mp.HJLarm_2Rad((Larm2a/Count*PI*50)/180)
		  + mp.HJRarm_2Rad((Rarm2a/Count*PI*50)/180)
		  + mp.HJLarm_3Rad((Larm3a/Count*PI*50)/180)
		  + mp.HJRarm_3Rad((Rarm3a/Count*PI*50)/180)
		  + mp.HJLarm_4Rad((Larm4a/Count*PI*50)/180)
		  + mp.HJRarm_4Rad((Rarm4a/Count*PI*50)/180)
		  + mp.HJLleg_1Rad((Lleg1a/Count*PI*50)/180)
		  + mp.HJRleg_1Rad((Rleg1a/Count*PI*50)/180)
		  + mp.HJLleg_2Rad((Lleg2a/Count*PI*50)/180)
		  + mp.HJRleg_2Rad((Rleg2a/Count*PI*50)/180)
		  + mp.HJLleg_6Rad((Lleg6a/Count*PI*50)/180)
		  + mp.HJRleg_6Rad((Rleg6a/Count*PI*50)/180);
  
  ///left leg
  //left leg 3
  if(fabs(Lleg3a)>=7)
  {
    if(Lleg3a>0)
	    ss<<mp.HJLleg_3Rad((7*PI*50)/180);
    else
	    ss<<mp.HJLleg_3Rad((-7*PI*50)/180);
  }
  else
	  ss<<mp.HJLleg_3Rad((Lleg3a/Count*PI*50)/180);
  //left leg 4
  if(fabs(Lleg4a)>=7)
  {
    if(Lleg4a>0)
	    ss<<mp.HJLleg_4Rad((7*PI*50)/180);
    else
	    ss<<mp.HJLleg_4Rad((-7*PI*50)/180);
  }
  else
	  ss<<mp.HJLleg_4Rad((Lleg4a/Count*PI*50)/180);
  //left leg 5
  if(fabs(Lleg5a)>=7)
  {
    if(Lleg5a>0)
	    ss<<mp.HJLleg_5Rad((7*PI*50)/180);
    else
	    ss<<mp.HJLleg_5Rad((-7*PI*50)/180);
  }
  else
	  ss<<mp.HJLleg_5Rad((Lleg5a/Count*PI*50)/180);
  ///right leg
  //right leg 3
  if(fabs(Rleg3a)>=7)
  {
    if(Rleg3a>0)
	    ss<<mp.HJRleg_3Rad((7*PI*50)/180);
    else
	    ss<<mp.HJRleg_3Rad((-7*PI*50)/180);
  }
  else
	  ss<<mp.HJRleg_3Rad((Rleg3a/Count*PI*50)/180);
  //right leg 4
  if(fabs(Rleg4a)>=7)
  {
    if(Rleg4a>0)
	    ss<<mp.HJRleg_4Rad((7*PI*50)/180);
    else
	    ss<<mp.HJRleg_4Rad((-7*PI*50)/180);
  }
  else
	  ss<<mp.HJRleg_4Rad((Rleg4a/Count*PI*50)/180);
  //right leg 5
  if(fabs(Rleg5a)>=7)
  {
    if(Rleg5a>0)
	    ss<<mp.HJRleg_5Rad((7*PI*50)/180);
    else
	    ss<<mp.HJRleg_5Rad((-7*PI*50)/180);
  }
  else
	  ss<<mp.HJRleg_5Rad((Rleg5a/Count*PI*50)/180);
  
  return ss.str();
}
#endif
Vector3 FormatInfoToServer::approximate(Vector3 Vector)
{
	return Vector3(

			(fabs(Vector.x())<EPS) ? 0:Vector.x(),

			(fabs(Vector.y())<EPS) ? 0:Vector.y(),

			(fabs(Vector.z())<EPS) ? 0:Vector.z()

	);
}

float FormatInfoToServer::approximate(float f)
{
	return (fabs(f)<EPS) ? 0:f;
}
/**          feng               */
Action FormatInfoToServer::ReadData_MaxSpeed(Angle Data)
{
	stringstream ss("");
	ss<<
	  	mp.HJHead_1Rad((Data.Head1.Aimangle*PI*50)/180)
		+ mp.HJHead_2Rad((Data.Head2.Aimangle*PI*50)/180)
		+ mp.HJLarm_1Rad((Data.Larm1.Aimangle*PI*50)/180)
		+ mp.HJRarm_1Rad((Data.Rarm1.Aimangle*PI*50)/180)
		+ mp.HJLarm_2Rad((Data.Larm2.Aimangle*PI*50)/180)
		+ mp.HJRarm_2Rad((Data.Rarm2.Aimangle*PI*50)/180)
		+ mp.HJLarm_3Rad((Data.Larm3.Aimangle*PI*50)/180)
		+ mp.HJRarm_3Rad((Data.Rarm3.Aimangle*PI*50)/180)
		+ mp.HJLarm_4Rad((Data.Larm4.Aimangle*PI*50)/180)
		+ mp.HJRarm_4Rad((Data.Rarm4.Aimangle*PI*50)/180)
		+ mp.HJLleg_1Rad((Data.Lleg1.Aimangle*PI*50)/180)
		+ mp.HJRleg_1Rad((Data.Rleg1.Aimangle*PI*50)/180)
		+ mp.HJLleg_2Rad((Data.Lleg2.Aimangle*PI*50)/180)
		+ mp.HJRleg_2Rad((Data.Rleg2.Aimangle*PI*50)/180)
		+ mp.HJLleg_3Rad((Data.Lleg3.Aimangle*PI*50)/180)
		+ mp.HJRleg_3Rad((Data.Rleg3.Aimangle*PI*50)/180)
		+ mp.HJLleg_4Rad((Data.Lleg4.Aimangle*PI*50)/180)
		+ mp.HJRleg_4Rad((Data.Rleg4.Aimangle*PI*50)/180)
		+ mp.HJLleg_5Rad((Data.Lleg5.Aimangle*PI*50)/180)
		+ mp.HJRleg_5Rad((Data.Rleg5.Aimangle*PI*50)/180)
		+ mp.HJLleg_6Rad((Data.Lleg6.Aimangle*PI*50)/180)
		+ mp.HJRleg_6Rad((Data.Rleg6.Aimangle*PI*50)/180);
	return ss.str();
}


void FormatInfoToServer::TurnHeadToFocusBall()
{
 	if(messageParser.mVisionSenseMap[VO_BALL].phi==0)
	{
	///	cout<<"i can not see the ball"<<endl;
		if(beginTurnHead==false)
		{
			if(messageParser.mVisionSenseMap[VO_FLAG1_L].phi!=0||messageParser.mVisionSenseMap[VO_FLAG1_R].phi!=0)
			{
				turnHeadRight=true;
	//			cout<<"turn Head right"<<endl;
			}
			else if(messageParser.mVisionSenseMap[VO_FLAG2_L].phi!=0||messageParser.mVisionSenseMap[VO_FLAG2_R].phi!=0)
			{
				turnHeadRight=false;
	//			cout<<"turn Head left"<<endl;
			}
			beginTurnHead=true;
		}
		else
		{
			if(turnHeadRight)
			{
			        turnHeadAngle=-120;
	//			cout<<"turn Head angle"<<turnHeadAngle<<endl;
			}
			else
			{
				turnHeadAngle=120;
	//			cout<<"turn Head angle"<<turnHeadAngle<<endl;
			}
			
			if(messageParser.mHingeJointSenseMap[JID_HEAD_1].angle<-100)
			{
			       turnHeadRight=false;
	//		       cout<<"change turn fangxiang to left"<<endl;
			}
			else if(messageParser.mHingeJointSenseMap[JID_HEAD_1].angle>100)
			{
			       turnHeadRight=true;
	//		       cout<<"change turn fangxiang to right"<<endl;
			}
		}
		
 	}
	else
	{
		turnHeadAngle=messageParser.mVisionSenseMap[VO_BALL].theta+messageParser.mHingeJointSenseMap[JID_HEAD_1].angle;
		beginTurnHead=false;
	//			       cout<<"can see the ball"<<endl;
	}
	
}

void FormatInfoToServer::ReadData_Add(Angle Data,Angle & sendAngle)
{
	  	sendAngle.Head1.Aimangle=Data.Head1.Aimangle+sendAngle.Head1.Aimangle;
		sendAngle.Head2.Aimangle=Data.Head2.Aimangle+sendAngle.Head2.Aimangle;
		
		sendAngle.Larm1.Aimangle=Data.Larm1.Aimangle+sendAngle.Larm1.Aimangle;
		sendAngle.Rarm1.Aimangle=Data.Rarm1.Aimangle+sendAngle.Rarm1.Aimangle;
		
		sendAngle.Larm2.Aimangle=Data.Larm2.Aimangle+sendAngle.Larm2.Aimangle;
		sendAngle.Rarm2.Aimangle=Data.Rarm2.Aimangle+sendAngle.Rarm2.Aimangle;
		
		sendAngle.Larm3.Aimangle=Data.Larm3.Aimangle+sendAngle.Larm3.Aimangle;
		sendAngle.Rarm3.Aimangle=Data.Rarm3.Aimangle+sendAngle.Rarm3.Aimangle;
		
		sendAngle.Larm4.Aimangle=Data.Larm4.Aimangle+sendAngle.Larm4.Aimangle;
		sendAngle.Rarm4.Aimangle=Data.Rarm4.Aimangle+sendAngle.Rarm4.Aimangle;
		
		sendAngle.Lleg1.Aimangle=Data.Lleg1.Aimangle+sendAngle.Lleg1.Aimangle;
		sendAngle.Rleg1.Aimangle=Data.Rleg1.Aimangle+sendAngle.Rleg1.Aimangle;
		
		sendAngle.Lleg2.Aimangle=Data.Lleg2.Aimangle+sendAngle.Lleg2.Aimangle;
		sendAngle.Rleg2.Aimangle=Data.Rleg2.Aimangle+sendAngle.Rleg2.Aimangle;
		
		sendAngle.Lleg3.Aimangle=Data.Lleg3.Aimangle+sendAngle.Lleg3.Aimangle;
		sendAngle.Rleg3.Aimangle=Data.Rleg3.Aimangle+sendAngle.Rleg3.Aimangle;
		
		sendAngle.Lleg4.Aimangle=Data.Lleg4.Aimangle+sendAngle.Lleg4.Aimangle;
		sendAngle.Rleg4.Aimangle=Data.Rleg4.Aimangle+sendAngle.Rleg4.Aimangle;
		
		sendAngle.Lleg5.Aimangle=Data.Lleg5.Aimangle+sendAngle.Lleg5.Aimangle;
		sendAngle.Rleg5.Aimangle=Data.Rleg5.Aimangle+sendAngle.Rleg5.Aimangle;
		
		sendAngle.Lleg6.Aimangle=Data.Lleg6.Aimangle+sendAngle.Lleg6.Aimangle;
		sendAngle.Rleg6.Aimangle=Data.Rleg6.Aimangle+sendAngle.Rleg6.Aimangle;
}
