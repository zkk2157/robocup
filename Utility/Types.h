#ifndef DATATYPE_H
#define DATATYPE_H
/**
 \file Types.h
 @author Leisland <leisland@163.com>
 */
# include <string>
# include <vector>
# include <map>
#include "Queue.h"
#include "Geometry.h"

///**********************lr *******************/
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <utility>

//#include <sys/time.h>
///********************************************/

#define MAXSPEED 0.172//182  //180
#define SLOWSPEED 0.172
#define MIDSPEED 0.12
#define MIDMINSPEED 0.05
#define MINSPEED 0.01






#define PI 3.141592
#define EPS  0.001
#define ShankHeight 0.11
#define ThighHeight 0.14
#define FIELDWIDTH 16.0
#define FIELDLENGTH 24.0
#define GOALWIDTH 2.0
#define BALLRADIUS 0.042

#define FLAGNUMBER 8
#define PLAYERNUMBER 11

#define LAST_CYCLES_SHORT 15
#define LAST_CYCLES_LONG 50
//#define getLastCycles 30
#define getLastCycles 5
#define LASTCYCLESOFBALL 5
#define LASTCYCLESOFMINE 5
#define LAST_CYCLES_OF_TURN_HEAD_ANGLE 5

#define LAST_CYCLES_OF_BALL_ME_TO_XAXIS_ANGLE 5
#define LAST_CYCLES_OF_BALL_GOAL_TO_XAXIS_ANGLE 5

#define LAST_CYCLES_OF_BODY_TO_X 5

#define CELL_LENGTH 1.666666667
#define FORMCELL_LENGTH 1.175
#define GOAL_HALFLENGTH 1.05

#define PI_180 0.017453289

#define LAST_CYCLES_OF_BALL_FOR_RUN_FORMATION 20

#define LAST_CYCLES_OF_LOCATE_TEAMMATE 50

#define NoTempNode 1000
const int MAX_MAP_WIDTH = 12;
const int MAX_MAP_HEIGHT = 12;

const int MAP_WIDTH = 3;
const int MAP_HEIGHT = 4;

using namespace std;
//using namespace oxygen;
//using namespace boost;

struct SmDistoBall
{
	float DistoBall;

	float DistoMe;
};

struct SFootTouchSensor
{
	int isFootOnGround; //1 =>on the ground      0=>above the ground

	SFootTouchSensor() :
			isFootOnGround(-1)
	{
	}
	;
};

struct SGYRSensor
{
	float x;
	float y;
	float z;
	SGYRSensor() :
			x(0.00), y(0.00), z(0.00)
	{
	}
	;
};
struct ACCSensor
{
	float x;
	float y;
	float z;
	ACCSensor() :
			x(0.00), y(0.00), z(0.00)
	{
	}
	;
};
struct FRPerceptor
{
	SGYRSensor c;
	SGYRSensor f;
};

struct HingeJointSense
{
	/** joint angle */
	float angle;

	/** joint angle rate */
//        float rate;
	HingeJointSense() :
			angle(0)/*, rate(0)*/
	{
	}
	;
};

struct UniversalJointSense
{
	/** joint angle axis 1*/
	float angle1;

	/** joint angle axis 2*/
	float angle2;

	/** joint angle rate axis 1*/
	//       float rate1;
	/** joint angle rate axis 2*/
//        float rate2;
	UniversalJointSense() :
			angle1(0), angle2(0)/*, rate1(0), rate2(0)*/
	{
	}
	;
};

enum TPlayMode
{
	// the order of the first 3 play modes should not be changed.
	PM_BeforeKickOff = 0, /*!< 0 before_kick_off:   before the match  */
	PM_KickOff_Our = 1, /*!< 1 kick_off_left:     kick off for the left team  */
	PM_KickOff_Opp = 2, /*!< 2 kick_off_right:    kick off for the right team */
	PM_PlayOn, /*!< 3 play_on:           regular game play */
	PM_KickIn_Our, /*!< 4 KickIn_r:           KickIn left team */
	PM_KickIn_Opp, /*!< 5 KickIn_l:           KickIn left team */
	PM_CORNER_KICK_Our, /*!< 6 corner_kick_l:     corner kick left team   */
	PM_CORNER_KICK_Opp, /*!< 7 corner_kick_r:     corner kick right team  */
	PM_GOAL_KICK_Our, /*!< 8 goal_kick_l:       goal kick for left team */
	PM_GOAL_KICK_Opp, /*!< 9 goal_kick_r:       goal kick for right team*/
	PM_OFFSIDE_Our, /*!< 10 offside_l:         offside for left team   */
	PM_OFFSIDE_Opp, /*!< 11 offside_r:         offside for right team  */
	PM_GameOver, /*!< 12 GameOver:         GameOver  */
	PM_Goal_Our, /*!< 13 Goal_l:         Goal for right team  */
	PM_Goal_Opp, /*!< 14 Goal_r:         Goal for right team  */
	PM_FREE_KICK_Our, /*!< 15 free_kick_l:       free kick for left team */
	PM_FREE_KICK_Opp, /*!< 16 free_kick_r:       free kick for right team*/
	PM_NONE
/*!< 17 no play mode, this must be the last entry */
};

enum JointID
{
	JID_HEAD_1 = 0,
	JID_HEAD_2 = 1,

	JID_LLEG_1 = 2,
	JID_RLEG_1 = 3,
	JID_LLEG_2 = 4,
	JID_RLEG_2 = 5,
	JID_LLEG_3 = 6,
	JID_RLEG_3 = 7,
	JID_LLEG_4 = 8,
	JID_RLEG_4 = 9,
	JID_LLEG_5 = 10,
	JID_RLEG_5 = 11,
	JID_LLEG_6 = 12,
	JID_RLEG_6 = 13,

	JID_LARM_1 = 14,
	JID_RARM_1 = 15,
	JID_LARM_2 = 16,
	JID_RARM_2 = 17,
	JID_LARM_3 = 18,
	JID_RARM_3 = 19,
	JID_LARM_4 = 20,
	JID_RARM_4 = 21
};

enum FootID
{
	FID_LEFT = 0, FID_RIGHT = 1
};

enum Direction
{
	Left = 0, Right = 1
};

enum BehaviorState
{
	ACT_NONE = 0, LLEG_OUT = 1, RLEG_OUT = 2
};
enum FallDirection
{
	D_NONE = 0, D_FORWARD = 1, D_BACK = 2, D_LEFT = 3, D_RIGHT = 4

};

enum VisionObject
{
	VO_FLAG1_L = 0,
	VO_FLAG2_L = 1,
	VO_FLAG1_R = 2,
	VO_FLAG2_R = 3,

	VO_GOAL1_L = 4,
	VO_GOAL2_L = 5,
	VO_GOAL1_R = 6,
	VO_GOAL2_R = 7,

	VO_BALL = 8,

	TMMT_1 = 9,
	TMMT_2 = 10,
	TMMT_3 = 11,
	TMMT_4 = 12,
	TMMT_5 = 13,
	TMMT_6 = 14,
	TMMT_7 = 15,
	TMMT_8 = 16,
	TMMT_9 = 17,
	TMMT_10 = 18,
	TMMT_11 = 19,

	OPPO_1 = 20,
	OPPO_2 = 21,
	OPPO_3 = 22,
	OPPO_4 = 23,
	OPPO_5 = 24,
	OPPO_6 = 25,
	OPPO_7 = 26,
	OPPO_8 = 27,
	OPPO_9 = 28,
	OPPO_10 = 29,
	OPPO_11 = 30,

	LI_GOAL_L = 31, /// the goal line in left side
	LI_GOAL_R = 32, /// the goal line in right side

	LI_SIDE_P = 33, ///the side line ,in Y >0 side 
	LI_SIDE_N = 34, ///the side line ,in Y<0 side

	LI_PENA_L = 35, ///penalty area line,in left side
	LI_PENA_R = 36, ///penalty area line,in right side
	LI_PENA_SIDE1_L = 37,
	LI_PENA_SIDE2_L = 38,
	LI_PENA_SIDE1_R = 39,
	LI_PENA_SIDE2_R = 40,

	LI_MID = 41,

	VO_NULL = 42
};

enum TTeamIndex
{
	TI_NONE = 0, TI_LEFT = 1, TI_RIGHT = 2
};

enum localizationOption
{
	LOCALIZATION_LEFT = 0,
	LOCALIZATION_RIGHT = 1,
	LOCALIZATION_TOP = 2,
	LOCALIZATION_BOTTOM = 3,
	LOCALIZATION_TURNHEAD = 4,
	LOCALIZATION_SINGL_LEFT, ///         czg
	LOCALIZATION_SINGL_RIGHT, ///        czg
	LOCALIZATION_NULL,
};

enum TGameHalf
{
	GH_NONE = 0, GH_FIRST = 1, GH_SECOND = 2
};

enum DecisionMotion
{
	DO_NOTHING = 0,
	HANDLE_BALL = 1,
	STAND_UP = 2,
	SHOOT_BALL = 3,
	CURRENT_PLACE_STEP = 4,
	WALK_TO_MY_POSITION = 5,
	ALL_STOP_FOR_STAND_UP = 6, //LJJ ADD FOR PREPARE FOR STAND UP
	PREVENT_FALLING_DOWN = 7, //when nao is falling down stop it :: powered by feng
	PREPARE_FOR_SHOOTING = 8,
	PASS_BALL = 9,
	SLIDE_TACKLE = 10
};
enum Role
{
	ROLE_VANGUARD = 0,
	ROLE_VICE_VANGUARD_1 = 1,
	ROLE_VICE_VANGUARD_2 = 2,
	ROLE_VICE_VANGUARD_3=11,
	ROLE_CENTRE_FORWARD = 3,
	ROLE_LINEBACKER = 4,
	ROLE_GOALIE = 5,
	ROLE_VICE_CENTRE_FORWARD_1 = 6,
	ROLE_VICE_CENTRE_FORWARD_2 = 7,
	ROLE_VICE_LINEBACKER_1 = 8,
	ROLE_VICE_LINEBACKER_2 = 9,
	ROLE_NULL
};
/**       lr          */
enum TopSpeed
{
	MAX_SPEED = 0, MID_SPEED = 1, MIDMIN_SPEED = 2, MIN_SPEED = 3,NULL_SPEED=4,AVOID_SPEED=5,SLOW_SPEED=6,

};
enum TopHorizontalSpeed
{
	HORIZONTAL_MAX_SPEED = 0, HORIZONTAL_MID_SPEED = 1, HORIZONTAL_MIN_SPEED = 2
};

enum SpeedStrategy
{
	FORWARD_QUICK_SPEED_UP = 0,
	FORWARD_SLOW_SPEED_UP = 1,
	FORWARD_SLOW_SPEED_DOWN = 2,
	FORWARD_QUICK_SPEED_DOWN = 3,

	BACKWARD_QUICK_SPEED_UP = 4,
	BACKWARD_SLOW_SPEED_UP = 5,
	BACKWARD_SLOW_SPEED_DOWN = 6,
	BACKWARD_QUICK_SPEED_DOWN = 7,

	KEEP_CURRENT_SPEED = 8,
	SPEED_NULL,

///       old thing
	SPEED_UP,
	SLOW_SPEED_DOWN,
	QUICK_SPEED_DOWN,

};

enum WalkDirection
{
	WALK_FORWARD = 0, WALK_BACKWARD = 1, WALK_NULL = 2
};

enum HorizonMoveDirection
{
	HORIZONMOVE_LEFT = 0, HORIZONMOVE_RIGHT = 1, HORIZONMOVE_NULL = 2
};

enum HorizonMoveSpeedStrategy
{
	HORIZONMOVE_LEFT_QUICK_SPEED_UP = 0,
	HORIZONMOVE_LEFT_SLOW_SPEED_UP = 1,
	HORIZONMOVE_RIGHT_QUICK_SPEED_UP = 2,
	HORIZONMOVE_RIGHT_SLOW_SPEED_UP = 3,

	HORIZONMOVE_LEFT_QUICK_SPEED_DOWN = 4,
	HORIZONMOVE_LEFT_SLOW_SPEED_DOWN = 5,
	HORIZONMOVE_RIGHT_QUICK_SPEED_DOWN = 6,
	HORIZONMOVE_RIGHT_SLOW_SPEED_DOWN = 7,

	HORIZONMOVE_SPEED_NULL = 8
};

/*add by gaojin*/
enum OffensiveAndDefensiveRating
{
	OffensiveAndDefensiveRating_FullDefense = 0, //全力防守
	OffensiveAndDefensiveRating_FocusOnDefense = 1, //侧重防守
	OffensiveAndDefensiveRating_AttackDefenseBalance = 2, //攻守平衡
	OffensiveAndDefensiveRating_FocusedOnOffensive = 3, //侧重进攻
	OffensiveAndDefensiveRating_AllOutOffensive = 4
//全力进攻
};

struct PlayerSayInfo
{
	Role agentRole;
	float heardTime;
	float directionAngle;
	int unum;
	bool isFallDown;
	float disToBall;
};

struct VisionSense
{
	/* distance perceptor to object */
	float distance;

	/* theta is the angle in the X-Y (horizontal) plane */
	float theta;

	/* phi is the latitude angle */
	float phi;

	/*this logical variant "updated" is a lable of sense data,if the value is true,it means the sense data has been updated*/
	bool updated;

	/*the sense time of this vision message*/
	float senseTime;

	VisionSense() :
			distance(0), theta(0), phi(0), updated(false), senseTime(0)
	{
	}
	;
};

struct PlayerVisionInfo
{
	/*team name of agent*/
	string teamName;

	/*uniform num of agent*/
	int unum;

	/*sense time*/
	float senseTime;

	bool used;

	/*polar coordinate of agent's head*/
	VisionSense head;

	/*polar coordinate of agent's right low arm*/
	VisionSense rLowerArm;

	/*polar coordinate of agent's left low arm*/
	VisionSense lLowerArm;

	/*polar coordinate of agent's right foot*/
	VisionSense rFoot;

	/*polar coordinate of agent's left foot*/
	VisionSense lFoot;
};

struct IsReachAim
{
	bool isRarm12_1Reach;

	bool isRarm12_2Reach;

	bool isRarm3Reach;

	bool isRarm4Reach;

	bool isRleg1Reach;

	bool isRleg23_1Reach;

	bool isRleg23_2Reach;

	bool isRleg4Reach;

	bool isRleg56_1Reach;

	bool isRleg56_2Reach;

	bool isLarm12_1Reach;

	bool isLarm12_2Reach;

	bool isLarm3Reach;

	bool isLarm4Reach;

	bool isLleg1Reach;

	bool isLleg23_1Reach;

	bool isLleg23_2Reach;

	bool isLleg4Reach;

	bool isLleg56_1Reach;

	bool isLleg56_2Reach;

	bool isAllReach;

};
struct JointInfo
{
	float Aimangle;
	float gain;
	JointInfo() :
			Aimangle(0), gain(0)
	{
	}
	;
	JointInfo(float ai, float ga) :
			Aimangle(ai), gain(ga)
	{
	}
	;
};

struct Angle //22 Values 
{
	JointInfo Head1;

	JointInfo Rarm1;

	JointInfo Rarm2;

	JointInfo Rarm3;

	JointInfo Rarm4;

	JointInfo Rleg1;

	JointInfo Rleg2;

	JointInfo Rleg3;

	JointInfo Rleg4;

	JointInfo Rleg5;

	JointInfo Rleg6;

	//Head2
	JointInfo Head2;

	//L
	JointInfo Larm1;

	JointInfo Larm2;

	JointInfo Larm3;

	JointInfo Larm4;

	JointInfo Lleg1;

	JointInfo Lleg2;

	JointInfo Lleg3;

	JointInfo Lleg4;

	JointInfo Lleg5;

	JointInfo Lleg6;

};

struct HearingSense
{
	float hearTime;
	string direction;
	string words;
};

struct Player
{
	string teamName;
	int number;
	Vector3 coordinate;
	float distanceToBall;
	float distanceToMe;
	bool fallDown;
};

struct LineVision
{
	/* distance perceptor to object */
	float distance1;

	/* theta is the angle in the X-Y (horizontal) plane */
	float theta1;

	/* phi is the latitude angle */
	float phi1;

	float distance2;

	/* theta is the angle in the X-Y (horizontal) plane */
	float theta2;

	/* phi is the latitude angle */
	float phi2;

	/*this logical variant "updated" is a lable of sense data,if the value is true,it means the sense data has been updated*/
	bool updated;

	/*the sense time of this vision message*/
	float senseTime;

	LineVision() :
			distance1(0), theta1(0), phi1(0), distance2(0), theta2(0), phi2(0), updated(
					false), senseTime(0)
	{
	}
	;
};

enum JointID2
{
	BODY_MOTHER = 0,
	BODY = 1,
	RLEG_J0 = 2,
	RLEG_J1 = 3,
	RLEG_J2 = 4,
	RLEG_J3 = 5,
	RLEG_J4 = 6,
	RLEG_J5 = 7,

	LLEG_J0 = 8,
	LLEG_J1 = 9,
	LLEG_J2 = 10,
	LLEG_J3 = 11,
	LLEG_J4 = 12,
	LLEG_J5 = 13
};

enum PlayerAroundMe
{
	ARROUND_NULL = 0,

	OPPONENT_FRONT = 1,
	OPPONENT_LEFT = 2,
	OPPONENT_BACK = 3,
	OPPONENT_RIGHT = 4,

	TEAMMATE_FRONT = 5,
	TEAMMATE_LEFT = 6,
	TEAMMATE_BACK = 7,
	TEAMMATE_RIGHT = 8
};

enum PassDirection
{
	PASS_FRONT = 0,
	PASS_LEFT_FRONT = 1,
	PASS_RIGHT_FRONT = 2,
	PASS_HORIZ = 3,
	PASS_BACK = 4,
	PASS_RIGHT_FRONT_LESS_STRENGTH = 5,
	PASS_LEFT_FRONT_LESS_STRENGTH = 6
};

enum Position
{
	Position_A = 0, Position_B = 1, Position_C = 2, Position_D = 3,Position_E=4
};
enum OurBallFormKind
{
	emOurBallForm = 0, emOppBallForm = 1, OurBallRightAttackForm
};

struct u
{
	int num;
	std::string name;
	float m;
	int mother;
	int sister;
	int child;
	boost::numeric::ublas::vector<float> b;
	boost::numeric::ublas::vector<float> a;
	boost::numeric::ublas::vector<float> c;
	boost::numeric::ublas::vector<float> p;

	boost::numeric::ublas::vector<float> v;
	boost::numeric::ublas::vector<float> w;

	boost::numeric::ublas::matrix<float> R;
	boost::numeric::ublas::matrix<float> I;
	float q;
	float dq;
	float ddq;
};
//}Rfoot,Lfoot,uLINK[14];

//u Rfoot,Lfoot,uLINK[14];
//const u Rfoot,Lfoot,uLINK[14];

typedef std::string Action;
typedef int TYPE;
typedef int CYCLE;
typedef float TIME;
typedef vector<float> FloatVector;
typedef vector<std::string> StringVector;
typedef vector<Player> PlayerVector;
typedef vector<PlayerSayInfo> PlayerSayInfoVector;
typedef vector<HearingSense> HearMessageVector;

typedef std::map<std::string, JointID> TJointIDMap;
typedef std::map<std::string, VisionObject> TVisionObjectMap;
typedef std::map<std::string, VisionObject> TVisionPlayerMap;
typedef std::map<std::string, FootID> TFootIDMap;
typedef std::map<std::string, TPlayMode> TPlayModeMap;
typedef std::map<JointID, HingeJointSense> THingeJointSenseMap;
typedef std::map<JointID, UniversalJointSense> TUniversalJointSenseMap;
typedef std::map<FootID, SFootTouchSensor> TFootStatusMap;
typedef std::map<VisionObject, VisionSense> TVisionSenseMap;
typedef std::map<VisionObject, PlayerVisionInfo> TPlayerSenseMap;
typedef std::map<FootID, FRPerceptor> FRPSenseMap;
typedef std::map<VisionObject, LineVision> TLineSenseMap;
//mapping from VisionObject to Vector
typedef std::map<VisionObject, Vector3> TObjectPosMap;
//mapping form vision object to vector
typedef std::map<VisionObject, Vector3> TObjectVectorMap;

typedef std::map<VisionObject, Queue> PlayerHeadHigh; //record the head hight of the player i see,use for confirm wheher  fall down

#endif//end of DATATYPE_H
