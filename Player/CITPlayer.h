/*
 * CITPlayer.h
 *
 *  Created on: 2012-3-2
 *      Author: cit chen
 */

#ifndef CITPLAYER_H_
#define CITPLAYER_H_
#include "../Stdafx.h"
class CITPlayer
{
public:
	float startplayontime;
	CITPlayer();
	Action Think();
	void Beam(){doBeam=false;}
	virtual ~CITPlayer();
	bool isourStartball;
private:
	bool doBeam;
	bool KickOffstart;
	bool isContred;
};

#endif /* CITPLAYER_H_ */
