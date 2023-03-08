#include "playerinfo.h"
extern WorldModel wm;
extern Perceptor messageParser;
namespace pla
{
PlayerInfo::PlayerInfo()
{
	//coordinate
	m_iPCflag = 0;
	timetosee=0;
	m_qHeadHigh = new Queue(H_headHighNum);
}
void PlayerInfo::SetInfor(int Teamnum)
{
	if (Teamnum >= 1 && Teamnum <= PLAYERNUMBER)
	{
		this->m_iNum = Teamnum;
	}
}
int PlayerInfo::mgetBackPCFlag(int num)
{
	return (m_iPCflag+REMBER_Player_NUMBER-num) % REMBER_Player_NUMBER;
}
int PlayerInfo::GetTeamNum()
{
	return m_iNum;
}

void PlayerInfo::mPCflagIncrease()
{
	m_iPCflag = (m_iPCflag + 1) % REMBER_Player_NUMBER;
}
void PlayerInfo::insert(PlayerVisionInfo vision)
{
	if (vision.head.phi != 0)
	{
		Vector3 PlayCoordinate = CalculatePlayerDirectlyCoordinate(vision);
		m_vPlayerCoordinate[m_iPCflag] = PlayCoordinate;
		mPCflagIncrease();
		float playerHigh = mGetheadHigh(vision);
		m_qHeadHigh->removedQueue(playerHigh);
		m_distanceOfPlayerToBall=GetDistanceOfPlayerToBall(vision);
		timetosee=vision.senseTime;
	}
}

float PlayerInfo::mGetheadHigh(PlayerVisionInfo vision)
{
	float dis3;
	if (vision.head.distance != 0)
	{
		dis3 =
				fabs(
						vision.rFoot.distance
								* sin(
										fabs(
												-messageParser.mHingeJointSenseMap[JID_HEAD_2].angle
														- vision.rFoot.phi) * PI
												/ 180)
								- vision.head.distance
										* sin(
												fabs(
														-messageParser.mHingeJointSenseMap[JID_HEAD_2].angle
																- vision.head.phi)
														* PI / 180));
	}
	else
	{
		dis3 = 0.45;
		//cout << "can not see" << m_iNum << endl;
	}
	return dis3;
}
float PlayerInfo::GetLastAverageDistanceOfPlayerToMe()
{
	return (GetLastAverageCoordinate() - wm.GetMyCoordinate()).mod();
}
float PlayerInfo::GetDistanceOfPlayerToMe()
{
	return (GetPlayerDirectlyCoordinate() - wm.GetMyCoordinate()).mod();
}
float PlayerInfo::GetDistanceOfPlayerToBall(PlayerVisionInfo vision)
{
	float myAngleToBall = wm.GetMyAngleToBall();
	float myDistanceToBall = wm.GetMyDistanceToBall();

	float myDisToTeammate = vision.head.distance;
	float myAngleToTeammate = vision.head.theta;
	float angle;
	if ((myAngleToBall * myAngleToTeammate) < 0)
	{
		angle = fabs(myAngleToBall) + fabs(myAngleToTeammate);
	}
	else
	{
		angle = fabs(myAngleToBall - myAngleToTeammate);
	}
	float distance = sqrt(
			myDistanceToBall * myDistanceToBall
					+ myDisToTeammate * myDisToTeammate
					- cos(angle * PI / 180) * 2 * myDistanceToBall
							* myDisToTeammate);
	return distance;
}
float PlayerInfo::GetLastAverageDistanceOfPlayerToBall()
{
	return (GetLastAverageCoordinate()
			- wm.GetBallCoordinate()).mod();
}

float PlayerInfo::GetDistanceOfPlayerToAVector(Vector3 target)
{
	Vector3 PlayerVector = GetLastAverageCoordinate();
	return (PlayerVector-target).mod();
}

Vector3 PlayerInfo::GetPlayerDirectlyCoordinate()
{
	return m_vPlayerCoordinate[mgetBackPCFlag(1)];
}

Vector3 PlayerInfo::CalculatePlayerDirectlyCoordinate(PlayerVisionInfo vision)
{
//	VisionSense TeammateSense = vision.head;
	float angle = vision.head.theta + wm.GetCurrentJointAngle(JID_HEAD_1)
			+ wm.GetMyBodyAngleToXAxis();
	Vector3 myCoordinate = wm.GetMyCoordinate();
	Vector3 PlayCoordinate = Vector3(
			myCoordinate.x() + vision.head.distance * cos(angle * PI / 180),
			myCoordinate.y() + vision.head.distance * sin(angle * PI / 180),
			myCoordinate.z());
	return PlayCoordinate;
}

float PlayerInfo::GetTimeOfLastSee()
{
	return timetosee;
}
bool PlayerInfo::isPlayerfallDown()
{
	if (m_qHeadHigh->AvrageQueue() < HeadHighOfDown)
		return true;
	else
		return false;
}

Vector3 PlayerInfo::GetLastAverageCoordinate()
{
	int tempflag;
	Vector3 total(0, 0, 0);
	int count = 0;
	for (count = 0; count < BaseReferenceCycles; count++)
	{
		tempflag = mgetBackPCFlag(count + 1);
		total = total + m_vPlayerCoordinate[tempflag];
	}
//	Vector3 base = total / count;
	tempflag = mgetBackPCFlag(count + 1);
	return total / count;
}
ostream& operator<<(ostream& os, PlayerInfo PV)
{
	stringstream out;
	out << endl;
		out <<"PC_num::"<<PV.m_iPCflag<<"coordinate::"<< PV.m_vPlayerCoordinate[PV.mgetBackPCFlag(1)]<<"var::"<<PV.GetLastAverageCoordinate()<< endl;
	out << " OUTPV NUM:::" << PV.GetTeamNum() << "    Vector3:"<< PV.m_distanceOfPlayerToBall<< endl;
	return (os << out.str());
}
}
