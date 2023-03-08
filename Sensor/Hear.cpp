/*
 * Hear.cpp
 *
 *  Created on: 2012-3-17
 *      Author: cit cw
 */

#include "Hear.h"
extern Perceptor messageParser;
extern Strategy behavior;
extern WorldModel wm;
extern Say CITSay;
namespace Sensor
{

Hear::Hear()
{
	// TODO Auto-generated constructor stub
	notHeardVanguardCount = 0;
	notHeardViceVanguard_1Count = 0;
	nowSaynum = PLAYERNUMBER;
}
void Hear::print()
{
//	cout<< "Vanguardnumfilter::" << Vanguardnumfilter.GetFilterNum() << endl;
//	cout<< "Anumfilter::" << Anumfilter.GetFilterNum() << endl;
//	cout<< "Bnumfilter::" << Bnumfilter.GetFilterNum() << endl;
//	cout<< "Cnumfilter::" << Cnumfilter.GetFilterNum() << endl;
//	cout<< "Dnumfilter::" << Dnumfilter.GetFilterNum() << endl;
//	cout<< "Enumfilter::" << Enumfilter.GetFilterNum() << endl;
//	cout<< "NextClosestTofilter::" << NextClosestTofilter.GetFilterNum()
//			<< endl;
//	cout<< "TheLastPlayerfilter::" << TheLastPlayerfilter.GetFilterNum()
//			<< endl;
}
void Hear::SetHearNumAsMe()
{
	nowSaynum = wm.GetMyNumber();
}
Hear::~Hear()
{
	// TODO Auto-generated destructor stub
}
bool Hear::VanNumdifference()
{
	return this->Vanguardnumfilter.isNumdifference();
}
void Hear::ParseHearInfo(string words)
{
	notHeardVanguardCount++;
	notHeardViceVanguard_1Count++;

	string hearmsg = words;

	//cout<< "@1::" << hearmsg << endl;
	bool isMyteam = false;
	if (hearmsg[0] == 's' && hearmsg[2] == 'T'
			&& wm.GetMyTeamIndex() == TI_LEFT)
	{
		isMyteam = true;
	}
	if (hearmsg[0] == 'T' && hearmsg[2] == 's'
			&& wm.GetMyTeamIndex() == TI_RIGHT)
	{
		isMyteam = true;
	}
//cout<<"isMyteam::"<<isMyteam<<endl;
	if (isMyteam)
	{
		//cout<< "hearmsg[8]::" << hearmsg[8] << endl;
		OffensiveAndDefensiveRating hearstate;
		hearstate = (OffensiveAndDefensiveRating) Convert::ToInt(
				Convert::ToString(hearmsg[8]));
		nowSaynum = GetEnnum(hearmsg[1]);
		CITSay.isSayMy = false;
		donotgetothersay = 0;
		float time = GetEnTime(words.substr(3, 5));

		//cout<< "@2" << endl;
		if (messageParser.gameTime - time > 0.02
				&& messageParser.gameTime - time < 0.06)
		{
			if (hearmsg[9] == 'V')
			{
				//cout<< "@3" << endl;
				Vanguardnumfilter.InsertNum(GetEnnum(hearmsg[1]));
				messageParser.vanguardNum = Vanguardnumfilter.GetFilterNum();

				if (hearmsg[10] == 'D')
				{
					IsStand[nowSaynum - 1] = false;
					messageParser.vanguardFallDown =
							!IsStand[messageParser.vanguardNum - 1];
					//cout<< "time :" << messageParser.gameTime
					//		<< "	vanguard Fall Down!!!" << endl;
				}
				else if (hearmsg[10] == 'S')
				{
					IsStand[nowSaynum - 1] = true;
					//cout<< "@4" << endl;

					//cout<< " time :" << messageParser.gameTime << "	HEAR time:"
					//		<< time << endl;
					if (messageParser.gameTime - time > 0.02
							&& messageParser.gameTime - time < 0.06)
					{
						//	messageParser.vanguardNumber = GetEnnum(hearmsg[1]);

						messageParser.vanguardFallDown =
								!IsStand[messageParser.vanguardNum - 1];
						messageParser.isVanguardStand =
								IsStand[messageParser.vanguardNum - 1];
						notHeardVanguardCount = 0;

						if (hearmsg[11] != 'N')
						{
							Anumfilter.InsertNum(GetEnnum(hearmsg[11]));
							messageParser.positionANumberByHear =
									Anumfilter.GetFilterNum();
							messageParser.positionAStand = true;
						}
						else if (hearmsg[11] == 'N')
						{
							messageParser.positionAStand = false;
						}

						if (hearmsg[12] != 'N')
						{
							Bnumfilter.InsertNum(GetEnnum(hearmsg[12]));
							messageParser.positionBNumberByHear =
									Bnumfilter.GetFilterNum();
							messageParser.positionBStand = true;
						}
						else if (hearmsg[12] == 'N')
						{
							messageParser.positionBStand = false;
						}

						if (hearmsg[13] != 'N')
						{
							Cnumfilter.InsertNum(GetEnnum(hearmsg[13]));
							messageParser.positionCNumberByHear =
									Cnumfilter.GetFilterNum();
							messageParser.positionCStand = true;
						}
						else if (hearmsg[13] == 'N')
						{
							messageParser.positionCStand = false;
						}

						if (hearmsg[14] != 'N')
						{
							Dnumfilter.InsertNum(GetEnnum(hearmsg[14]));
							messageParser.positionDNumberByHear =
									Dnumfilter.GetFilterNum();
							messageParser.positionDStand = true;
						}
						else if (hearmsg[14] == 'N')
						{
							messageParser.positionDStand = false;
						}

						if (hearmsg[15] != 'N')
						{
							Enumfilter.InsertNum(GetEnnum(hearmsg[15]));
							messageParser.positionENumberByHear =
									Enumfilter.GetFilterNum();
							messageParser.positionEStand = true;
						}
						else if (hearmsg[15] == 'N')
						{
							messageParser.positionEStand = false;
						}

						if (hearmsg[16] == 'Y')
						{
							messageParser.whetherCanTurnToOpponentGoal = true;
						}
						else if (hearmsg[16] == 'N')
						{
							messageParser.whetherCanTurnToOpponentGoal = false;
						}

//						//cout<< "A:" << Anumfilter.GetFilterNum();
//						//cout<< "B:" << Bnumfilter.GetFilterNum();
//						//cout<< "C:" << Cnumfilter.GetFilterNum();
//						//cout<< "D:" << Dnumfilter.GetFilterNum();
						if (hearmsg[17] != '0' && hearmsg[18] != '0'
								&& nowSaynum == 1)
						{
							TheLastPlayerfilter.InsertNum(
									GetEnnum(hearmsg[17]));
							NextClosestTofilter.InsertNum(
									GetEnnum(hearmsg[18]));
						}
					}

					//cout<< "time :" << messageParser.gameTime
					//		<< "vanguard stand up !!!" << endl;
				}

			}
			else if (hearmsg[9] >= '1' && hearmsg[9] <= ';') //即编码后的球员号1-9
			{
				Vanguardnumfilter.InsertNum(GetEnnum(hearmsg[9]));
				messageParser.vanguardNum = Vanguardnumfilter.GetFilterNum();

				if (hearmsg[10] == 'S')
				{
					IsStand[nowSaynum - 1] = true;
					float time = GetEnTime(words.substr(3, 5));

					//cout<< "HEAR Goalie######################time:" << time
					//		<< "GetGameTime():" << messageParser.gameTime
					//		<< "GetGameTime()-time:"
					//		<< messageParser.gameTime - time << endl;
					if (messageParser.gameTime - time > 0.02
							&& messageParser.gameTime - time < 0.04)
					{
						//cout<< "@5" << endl;
						if (hearmsg[11] != 'N')
						{
							Anumfilter.InsertNum(GetEnnum(hearmsg[11]));
							messageParser.positionANumberByHear =
									Anumfilter.GetFilterNum();
							messageParser.positionAStand = true;
						}
						else if (hearmsg[11] == 'N')
						{
							messageParser.positionAStand = false;
						}

						if (hearmsg[12] != 'N')
						{
							Bnumfilter.InsertNum(GetEnnum(hearmsg[12]));
							messageParser.positionBNumberByHear =
									Bnumfilter.GetFilterNum();
							messageParser.positionBStand = true;
						}
						else if (hearmsg[12] == 'N')
						{
							messageParser.positionBStand = false;
						}

						if (hearmsg[13] != 'N')
						{
							Cnumfilter.InsertNum(GetEnnum(hearmsg[13]));
							messageParser.positionCNumberByHear =
									Cnumfilter.GetFilterNum();
							messageParser.positionCStand = true;
						}
						else if (hearmsg[13] == 'N')
						{
							messageParser.positionCStand = false;
						}

						if (hearmsg[14] != 'N')
						{
							Dnumfilter.InsertNum(GetEnnum(hearmsg[14]));
							messageParser.positionDNumberByHear =
									Dnumfilter.GetFilterNum();
							messageParser.positionDStand = true;
						}
						else if (hearmsg[14] == 'N')
						{
							messageParser.positionDStand = false;
						}
						if (hearmsg[15] != 'N')
						{
							Enumfilter.InsertNum(GetEnnum(hearmsg[15]));
							messageParser.positionENumberByHear =
									Enumfilter.GetFilterNum();
							messageParser.positionEStand = true;
						}
						else if (hearmsg[15] == 'N')
						{
							messageParser.positionEStand = false;
						}
						if (hearmsg[16] == 'Y')
						{
							messageParser.whetherCanTurnToOpponentGoal = true;
						}
						else if (hearmsg[16] == 'N')
						{
							messageParser.whetherCanTurnToOpponentGoal = false;
						}

//						//cout<< "A:" << Anumfilter.GetFilterNum();
//						//cout<< "B:" << Bnumfilter.GetFilterNum();
//						//cout<< "C:" << Cnumfilter.GetFilterNum();
//						//cout<< "D:" << Dnumfilter.GetFilterNum();
						if (hearmsg[17] != '0' && hearmsg[18] != '0'
								&& nowSaynum == 1)
						{
							TheLastPlayerfilter.InsertNum(
									GetEnnum(hearmsg[17]));
							NextClosestTofilter.InsertNum(
									GetEnnum(hearmsg[18]));
						}
//						//cout<< "A:" << Anumfilter.GetFilterNum();
//						//cout<< "B:" << Bnumfilter.GetFilterNum();
//						//cout<< "C:" << Cnumfilter.GetFilterNum();
//						//cout<< "D:" << Dnumfilter.GetFilterNum();
					}
					//cout<< "time :" << messageParser.gameTime << endl;

				}
				else if (hearmsg[5] == 'D')
				{
					IsStand[nowSaynum - 1] = false;
				}
			}
		}
	}
	//cout<< "notHeardVanguardCount:" << notHeardVanguardCount << endl;
	//cout<< "notHeardViceVanguard_1Count:" << notHeardViceVanguard_1Count
		//	<< endl;
	if (notHeardVanguardCount > 100)
	{
		messageParser.isVanguardStand = false;
		notHeardVanguardCount = 0;
	}

	if (notHeardViceVanguard_1Count > 100)
	{
		messageParser.isViceVanguard_1Stand = false;
		notHeardVanguardCount = 0;
	}
	messageParser.hearmessagecount++;
	if (messageParser.hearmessagecount >= 20)
		messageParser.hearmessagecount = 0;
	return;

}
void Hear::ParseMyHearInfo(string words)
{
	//cout<< "ParseMyHearInfo::" << words << endl;
	string hearmsg = words;
//	bool isMyteam = false;
//	if (hearmsg[0] == 's' && hearmsg[2] == 'T'
//			&& wm.GetMyTeamIndex() == TI_LEFT)
//	{
//		isMyteam = true;
//	}
//	if (hearmsg[0] == 'T' && hearmsg[2] == 's'
//			&& wm.GetMyTeamIndex() == TI_RIGHT)
//	{
//		isMyteam = true;
//	}
//	cout<<"isMyteam::"<<isMyteam<<endl;
//	if (isMyteam)
//	{
//		float time = GetEnTime(words.substr(3, 5));
//		if (messageParser.gameTime - time > 0.02
//				&& messageParser.gameTime - time < 0.06)
//		{
//			nowSaynum = GetEnnum(hearmsg[1]);
//		}
//		//cout<< "myselftime::" << time << endl;
//	}
	this->ParseHearInfo(hearmsg);
}
int Hear::GetEnnum(char num) //解密num,以‘0’开始
{
	int res;
	res = num - '0';
	return res;
}
float Hear::GetEnTime(string str) //
{
	return Convert::ToFloat(str.substr(0, 3) + "." + str.substr(3, 2));
}
} /* namespace Sensor */

