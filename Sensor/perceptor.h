#ifndef PARSEMESSAGE_H
#define PARSEMESSAGE_H
/**
 \file parsemessage.h
 @author Leisland <leisland@163.com>
 */
# include "../Stdafx.h"

using namespace std;
using namespace boost;

class Perceptor
{
public:
	Perceptor();
	void ParseMessageInit();
	float GetCurrentJiontAngle(JointID J_ID);
	SGYRSensor GetGYR();
	FRPerceptor GetFRP(FootID vo);
	VisionSense GetVisionPolarCoordinate(VisionObject flagName);
	float GetServerTime();
	float GetGameTime();
	TPlayMode GetCurrentGameMode();
	TTeamIndex GetMyTeamIndex();
	void ChangeMyTeamIndex();
	string GetOpponetTeamName();
	int GetMyNumber();
	int GetVanguardNumber();

	bool ParsevanguardNum(); ///czg

	THingeJointSenseMap GetCurrentJointMap();

	void ParseMsg(string& input);
	bool GetVanPos(Vector3 &VanPos); ///czg

	ACCSensor GetACC();
private:
	/**clear data*/
	void ClearData();

	void InitVariable();
	void SetupMapContainer();
	void SetupJointIDMap();
	void SetupFootIDMap();
	void SetupVisionObjectMap();
	void SetupVisionPlayerMap();
	void SetupGameStateMap(TTeamIndex teamindex);
	void OutputParseResult();

	void RecordOpponetPlayer(string playerID);
	void RecordTeammate(string playerID);
	void ClearPlayerRecord();
public:
	TJointIDMap mJointIDMap;
	TVisionObjectMap mVisionObjectMap;
	TVisionPlayerMap mVisionPlayerMap;
	TFootIDMap mFootIDMap;
	TPlayModeMap mPlayModeMap;
	THingeJointSenseMap mHingeJointSenseMap;
	TUniversalJointSenseMap mUniversalJointSenseMap;
	TFootStatusMap mFootStatusMap;
	TVisionSenseMap mVisionSenseMap;
	FRPSenseMap myFRPSenseMap;

	TPlayerSenseMap mTeamMateSenseMap;
	TPlayerSenseMap mOpponentSenseMap;

	TLineSenseMap mLineSenseMap;

	string bodyPartName[5];
	//FRPerceptor fRPerceptor;
	SGYRSensor gyrSensor;
	ACCSensor accSensor; ///lr
	//current play mode
	TPlayMode currentGameMode;
	//hearing
	int hearmessagecount;
	HearingSense myHearing[20];
	LineVision lineRecord[21];

	HearMessageVector mHearMessageVector;
	//team side
	TTeamIndex mTeamIndex;
	//time
	float gameTime;
	float serverTime;
	//oppenet team
	string opponentTeamName;
	//player number
	int number;

	//
	int vanguardNum;
	//
	bool vanguardFallDown;

	//opponent player record
	int opponentPlayer[PLAYERNUMBER + 1];
	//teammate record
int	teammate[PLAYERNUMBER+1];

	bool CanGetVanPos;///czg

	Vector3 VanPos;///czg

	bool ViceVanguard_1FallDown;

	bool ViceVanguard_2FallDown;

	bool GetIsVanguardStand();
	bool GetIsViceVanguard_1Stand();

	void SetIsVanguardStand(bool stand);
	void SetIsViceVanguard_1Stand(bool stand);

	int GetVanguardNumberByHear();
	int GetViceVanguard_1NumberByHear();

	bool WhetherVanguardUseHalfStepWalk();

	int GetHearVanguardNumber();

	PlayerAroundMe playerAroundMe;

	std::string mOppTeamName;//teamOpponent name

	bool GetWhetherPositionAStand();
	bool GetWhetherPositionBStand();
	bool GetWhetherPositionCStand();
	bool GetWhetherPositionDStand();
	bool GetWhetherPositionEStand();

	int GetPositionANumberByHear();
	int GetPositionBNumberByHear();
	int GetPositionCNumberByHear();
	int GetPositionDNumberByHear();
	int GetPositionENumberByHear();

	bool GetWhetherBallBeforeVanguard();

	bool WhetherCanTurnToOpponentGoal();

	//	bool abnormalServerCycle;

private:
// 		zeitgeist::Zeitgeist mZG;
// 		boost::shared_ptr<oxygen::BaseParser> mParser;

	int notHeardVanguardCount;

	int notHeardViceVanguard_1Count;

	int viceVanguard_1Number;

	bool vanguardUseHalfStepWalk;
	int hearVanguardNumber;

	void recordMyAroundInfo(char info);

	void clearLineRecord();
	void recordLineInfo(int& pointer, string& input);
	void recognizeWhichLine();

	string getWord(int& pointer, string& input, bool let);
	bool isChar ( char chr );

	float getNum( int& pointer,string& input );
	bool isNum ( char chr );

	void setTeamSide ( int& pointer,string& input );
	void setPlayMode ( int& pointer,string& input );

	void setFlag ( int& pointer,string& input,string& name );
	void setGoal ( int& pointer,string& input, string& name );
	void setBall ( int& pointer,string& input );
	void setPlayer ( int& pointer,string& input );
	void setFRP ( int& pointer,string& input,string& name );
	void setHJoint ( int& pointer,string& input,string& name );
	void setHear ( int& pointer,string& input,string& name );
	void ParseHearInfo (string words );
	float getMyDistanceflag(VisionObject ob);
	float getMyDistanceLine(VisionObject ob,int whichOne);

	bool whetherBallBeforeVanguard;

	void ParseMyHearInfo(string words);
public :
	bool isVanguardStand;
	bool isViceVanguard_1Stand;
	bool whetherCanTurnToOpponentGoal;
	int vanguardNumber;
	bool positionAStand;
	bool positionBStand;
	bool positionCStand;
	bool positionDStand;
	bool positionEStand;

	int positionANumberByHear;
	int positionBNumberByHear;
	int positionCNumberByHear;
	int positionDNumberByHear;
	int positionENumberByHear;
};

#endif
