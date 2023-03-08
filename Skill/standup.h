/*
 * standup.h
 *
 *  Created on: 2012-2-29
 *      Author: cit chen
 */

#ifndef STANDUP_H_
#define STANDUP_H_
#include "../Stdafx.h"
class Cstandup {
public:
	Cstandup();
//	Action DisposeFalling();
	Action PreventForwardFallingDown();
	Action StandUpFromBack();
	Action PreventBackFallingDown();
	Action StandUpFromFront();
	Action dealFallingDown();
	Action StandUp();
	Action DisposeFalling();
	virtual ~Cstandup();
	bool GetFallingDown(){return fallingDown;}
	bool GetfallDown(){return fallDown;}
	void SetFallingDown(bool tfallingDwon){fallingDown=tfallingDwon;}
	void SetfallDown(bool tfallDwon){fallDown=tfallDwon;}
	void SetbeginStandUp(bool bsu){beginStandUp=bsu;}
	bool GetbeginStandUp(){return beginStandUp;}
	void doJudgeFallDown();
	void SetwalkBegain(bool wb){wb=walkBegain;}
	void SetfallDownTurnHeadToFindTwoflags(bool fdth){fallDownTurnHeadToFindTwoflags=fdth;}
	bool GetfallDownTurnHeadToFindTwoflags(){return fallDownTurnHeadToFindTwoflags;}
	bool GetfinishStandUpMotion(){return finishStandUpMotion;}
private:
	bool fallingDown;//ljj add for test 090226
	bool fallDown;
	bool beginStandUp;
	bool faceToGround;
	bool faceToSky;
	Timer estimateFallDirectionTimer;
	bool fallDownTurnHeadToFindTwoflags;
	bool finishStandUpMotion;
	bool walkBegain;
	bool justAfterStandUp;
	int noFRPCount;
	bool justAfterSplits;
};

#endif /* STANDUP_H_ */
