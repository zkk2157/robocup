/*
 * Say.cpp
 *
 *  Created on: 2012-3-17
 *      Author: cit cw
 */

#include "Say.h"
using namespace Sensor;
extern Perceptor messageParser;
extern WorldModel wm;
extern JointEffector mp;

extern Strategy behavior;
extern Cstandup CITstandup;
extern Hear CITHear;
Say::Say()
{
	// TODO Auto-generated constructor stub

}

Say::~Say()
{
	// TODO Auto-generated destructor stub
	isSayMy = false;
}
Action Say::ControlSay()
{
	string res;
	int Saynum = ((CITHear.GetnowSayNumber() + PLAYERNUMBER)
			% PLAYERNUMBER) + 1;
	//cout << "Saynum::" << Saynum << "isSayMy::" << isSayMy << endl;
	if (Saynum == wm.GetMyNumber() && !isSayMy)
	{
		if (behavior.GetNowmyRole() != ROLE_VANGUARD)
		{
			res = noVanguardSay();
		}
		else
		{
			res = VanguardSay();
		}
		CITHear.SetHearNumAsMe();
		isSayMy = true;
	}
	else
	{
		if (CITHear.GetnowSayNumber() == wm.GetMyNumber())
		{
//			cout
//					<< "CITHear.GetnowSayNumber() == wm.GetMyNumber() donotgetothersay::"
//					<< CITHear.donotgetothersay << endl;
			CITHear.donotgetothersay++;
			if (CITHear.donotgetothersay > 4)
			{
				isSayMy = false;
				if (behavior.GetNowmyRole() != ROLE_VANGUARD)
				{
					res = noVanguardSay();
				}
				else
				{
					res = VanguardSay();
				}
				CITHear.donotgetothersay = 0;
			}
		}
	}
	//cout << "res::" << res << endl;
	return res;
}
string Say::VanguardSay()
{
	stringstream aa("");
	//aa << Convert::ToString(Getnum(wm.GetMyNumber()));
	if (CITstandup.GetFallingDown() || CITstandup.GetfallDown())
	{
		aa << "VD";
	}
	else
	{
		aa << "VS";
	}

	if (messageParser.GetWhetherPositionAStand() == true)
	{
		aa
				<< Convert::ToString(
						Getnum(messageParser.GetPositionANumberByHear()));
	}
	else
	{
		aa << "N";
	}

	if (messageParser.GetWhetherPositionBStand() == true)
	{
		aa
				<< Convert::ToString(
						Getnum(messageParser.GetPositionBNumberByHear()));
	}
	else
	{
		aa << "N";
	}

	if (messageParser.GetWhetherPositionCStand() == true)
	{
		aa
				<< Convert::ToString(
						Getnum(messageParser.GetPositionCNumberByHear()));
	}
	else
	{
		aa << "N";
	}

	if (messageParser.GetWhetherPositionDStand() == true)
	{
		aa
				<< Convert::ToString(
						Getnum(messageParser.GetPositionDNumberByHear()));
	}
	else
	{
		aa << "N";
	}
	if (messageParser.GetWhetherPositionEStand() == true)
	{
		aa<< Convert::ToString(
						Getnum(messageParser.GetPositionENumberByHear()));
	}
	else
	{
		aa << "N";
	}
	if (messageParser.WhetherCanTurnToOpponentGoal() == true)
	{
		aa << "Y";
	}
	else
	{
		aa << "N";
	}

	if (wm.GetMyNumber() == 1)
	{
		aa << Convert::ToString(Getnum(wm.GetClosestToMeTeamNumberByVision()));
		aa
				<< Convert::ToString(
						Getnum(wm.GetNextClosestToMeTeamNumberByVision()));
	}
	else
	{
		aa << "00";
	}
	string sayMsg = aa.str();
	if(wm.GetMyTeamIndex()==TI_LEFT)
	{
		sayMsg = "s" + Convert::ToString(Getnum(wm.GetMyNumber())) + "T"
			+ HandleTime()
			+ Convert::ToString(behavior.OffensiveAndDefensiveDegree())
			+ sayMsg;
	}
	else
	{
		sayMsg = "T" + Convert::ToString(Getnum(wm.GetMyNumber())) + "s"
			+ HandleTime()
			+ Convert::ToString(behavior.OffensiveAndDefensiveDegree())
			+ sayMsg;
	}
	//cout << "Vanguard speak:" << sayMsg << endl;
	return mp.Say(sayMsg);
}
string Say::noVanguardSay()
{
	string sayMsg;
	//sayMsg=Convert::ToString(Getnum(wm.GetMyNumber()));
	sayMsg = Convert::ToString(Getnum(wm.GetVanguardNumberByVision()));

	if (CITstandup.GetFallingDown() || CITstandup.GetfallDown())
	{
		sayMsg += "D";
	}
	else
	{
		sayMsg += "S";
	}

	sayMsg += FormationSituation();
	if (wm.WhetherCanTurnToOpponentGoal() == true)
	{
		sayMsg += "Y";
	}
	else
	{
		sayMsg += "N";
	}
	if (wm.GetMyNumber() == 1)
	{
		sayMsg += Convert::ToString(
				Getnum(wm.GetClosestToMeTeamNumberByVision()));
		sayMsg += Convert::ToString(
				Getnum(wm.GetNextClosestToMeTeamNumberByVision()));
	}
	else
	{
		sayMsg += "00";
	}
	if(wm.GetMyTeamIndex()==TI_LEFT)
	{
		sayMsg = "s" + Convert::ToString(Getnum(wm.GetMyNumber())) + "T"
				+ HandleTime()
				+ Convert::ToString(behavior.OffensiveAndDefensiveDegree())
				+ sayMsg;
	//	cout << "Novanguard speak:" << sayMsg << endl;
	}
	else
	{
		sayMsg = "T" + Convert::ToString(Getnum(wm.GetMyNumber())) + "s"
				+ HandleTime()
				+ Convert::ToString(behavior.OffensiveAndDefensiveDegree())
				+ sayMsg;
	//	cout << "Novanguard speak:" << sayMsg << endl;
	}
	return mp.Say(sayMsg);

}
string Say::HandleTime()
{
	//TODO::如果以后信息量增大，可以减少时间位数，因为时间误差不是很大，可以发送时间小数位。
	float time = wm.GetCurrentGameTime();
//	cout << "say::time::" << time << endl;
	string strtime = Convert::ToString(time, 3, 2);
	int point = strtime.find('.');
	string integerpartoftime = strtime.substr(0, point);
	string Decimalparttime = strtime.substr(point + 1);
	return integerpartoftime + Decimalparttime;
}
char Say::Getnum(int num) //加密num,以‘0’开始
{
	char cc;
	cc = num + '0';
	return cc;
}

string Say::FormationSituation()
{
	std::stringstream ss("");
	if (wm.WhetherTeammateStandNorthwestToBall() == true)
	{
		ss << Getnum(wm.GetPositionANumber());
		///cout<<"A:"<<GetPositionANumber()<<endl;
	}
	else
	{
		ss << "N";
		///cout<<"AN"<<endl;
	}

	if (wm.WhetherTeammateStandSouthwestToBall() == true)
	{
		ss << Getnum(wm.GetPositionBNumber());
		///cout<<"B:"<<GetPositionBNumber()<<endl;
	}
	else
	{
		ss << "N";
		///cout<<"BN"<<endl;
	}

	if (wm.WhetherTeammateStandSoutheastToBall() == true)
	{
		ss << Getnum(wm.GetPositionCNumber());
		///cout<<"C:"<<GetPositionCNumber()<<endl;
	}
	else
	{
		ss << "N";
		///cout<<"CN"<<endl;
	}

	if (wm.WhetherTeammateStandNortheastToBall() == true)
	{
		ss << Getnum(wm.GetPositionDNumber());
		///cout<<"D:"<<GetPositionDNumber()<<endl;
	}
	else
	{
		ss << "N";
		///cout<<"DN"<<endl;
	}
	if (wm.WhetherTeammateStandBackToBall() == true)
	{
		ss << Getnum(wm.GetPositionENumber());
		///cout<<"D:"<<GetPositionDNumber()<<endl;
	}
	else
	{
		ss << "N";
		///cout<<"DN"<<endl;
	}
	return ss.str();
}
