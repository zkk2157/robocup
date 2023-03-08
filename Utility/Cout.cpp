/*
 * Cout.cpp
 *
 *  Created on: 2012-5-7
 *      Author: cit32
 */

#include "Cout.h"

Cout::Cout()
{
	// TODO Auto-generated constructor stub

}
void Cout::print(Role val)
{
	switch (val)
	{
	case ROLE_VANGUARD:
		cout << "ROLE_VANGUARD";
		break;
	case ROLE_VICE_VANGUARD_1:
		cout << "ROLE_VICE_VANGUARD_1";
		break;
	case ROLE_VICE_VANGUARD_2:
		cout << "ROLE_VICE_VANGUARD_2";
		break;
	case ROLE_CENTRE_FORWARD:
		cout << "ROLE_CENTRE_FORWARD";
		break;
	case ROLE_LINEBACKER:
		cout << "ROLE_LINEBACKER";
		break;
	case ROLE_VICE_CENTRE_FORWARD_2:
		cout << "ROLE_VICE_CENTRE_FORWARD_2";
		break;
	case ROLE_GOALIE:
		cout << "ROLE_GOALIE";
		break;
	case ROLE_VICE_CENTRE_FORWARD_1:
		cout << "ROLE_VICE_CENTRE_FORWARD_1";
		break;
	case ROLE_VICE_LINEBACKER_1:
		cout << "ROLE_VICE_LINEBACKER_1";
		break;
	case ROLE_VICE_LINEBACKER_2:
		cout << "ROLE_VICE_LINEBACKER_2";
		break;
		break;
	case ROLE_NULL:
		cout << "ROLE_NULL";
		break;
	}
}
void Cout::print(DecisionMotion dm)
{
	switch (dm)
	{
	case DO_NOTHING:
		cout << "DO_NOTHING" << endl;
		break;
	case HANDLE_BALL:
		cout << "HANDLE_BALL" << endl;
		break;
	case STAND_UP:
		cout << "STAND_UP" << endl;
		break;
	case SHOOT_BALL:
		cout << "SHOOT_BALL" << endl;
		break;
	case CURRENT_PLACE_STEP:
		cout << "CURRENT_PLACE_STEP" << endl;
		break;
	case WALK_TO_MY_POSITION:
		cout << "WALK_TO_MY_POSITION" << endl;
		break;
	case ALL_STOP_FOR_STAND_UP: //LJJ ADD FOR PREPARE FOR STAND UP
		cout << "ALL_STOP_FOR_STAND_UP" << endl;
		break;
	case PREVENT_FALLING_DOWN: //when nao is falling down stop it :: powered by feng.
		cout << "PREVENT_FALLING_DOWN" << endl;
		break;
	case PREPARE_FOR_SHOOTING:
		cout << "PREPARE_FOR_SHOOTING" << endl;
		break;
	case PASS_BALL:
		cout << "PASS_BALL" << endl;
		break;
	case SLIDE_TACKLE:
		cout << "SLIDE_TACKLE" << endl;
		break;
	}
}
void Cout::print(TPlayMode val)
{
	switch (val)
	{
	case PM_BeforeKickOff:
		cout << "PM_BeforeKickOff" << endl;
		break;
	case PM_KickOff_Our:
		cout << "PM_KickOff_Our" << endl;
		break;
	case PM_KickOff_Opp:
		cout << "PM_KickOff_Opp" << endl;
		break;
	case PM_PlayOn:
		cout << "PM_PlayOn" << endl;
		break;
	case PM_KickIn_Our:
		cout << "PM_KickIn_Our" << endl;
		break;
	case PM_KickIn_Opp:
		cout << "PM_KickIn_Opp" << endl;
		break;
	case PM_CORNER_KICK_Our:
		cout << "PM_CORNER_KICK_Our" << endl;
		break;
	case PM_CORNER_KICK_Opp:
		cout << "PM_CORNER_KICK_Opp" << endl;
		break;
	case PM_GOAL_KICK_Our:
		cout << "PM_GOAL_KICK_Our" << endl;
		break;
	case PM_GOAL_KICK_Opp:
		cout << "PM_GOAL_KICK_Opp" << endl;
		break;
	case PM_OFFSIDE_Our:
		cout << "PM_OFFSIDE_Our" << endl;
		break;
	case PM_OFFSIDE_Opp:
		cout << "PM_OFFSIDE_Opp" << endl;
		break;
	case PM_GameOver:
		cout << "PM_GameOver" << endl;
		break;
	case PM_Goal_Our:
		cout << "PM_Goal_Our" << endl;
		break;
	case PM_Goal_Opp:
		cout << "PM_Goal_Opp" << endl;
		break;
	case PM_FREE_KICK_Our:
		cout << "PM_FREE_KICK_Our" << endl;
		break;
	case PM_FREE_KICK_Opp:
		cout << "PM_FREE_KICK_Opp" << endl;
		break;
	case PM_NONE:
		cout << "PM_NONE" << endl;
		break;
	}
}
Cout::~Cout()
{
	// TODO Auto-generated destructor stub
}

