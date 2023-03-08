/*
 * Say.h
 *
 *  Created on: 2012-3-17
 *      Author: cit cw
 */

#ifndef SAY_H_
#define SAY_H_
#include "../Stdafx.h"
class Say
{
public:
	Action ControlSay();
	Say();
	string VanguardSay();
	string noVanguardSay();
	virtual ~Say();
	bool isSayMy;
	const static int Numberbit=1;
	const static int TimeStartbit=3;
	const static int TimeLengthbit=5;
	const static int Formbit=8;
	const static int VanguardInfobit=9;
	const static int StandInfobit=10;
	const static int AInfobit=11;
	const static int BInfobit=12;
	const static int CInfobit=13;
	const static int DInfobit=14;
	const static int TurnInfobit=15;
	const static int LastInfobit=16;
	const static int NextLastInfobit=17;

private:
	string HandleTime();
	string FormationSituation();
	char Getnum(int num);
private:

	int saycyclesnum;
	const static int cyclesLength = PLAYERNUMBER;
};

#endif /* SAY_H_ */
