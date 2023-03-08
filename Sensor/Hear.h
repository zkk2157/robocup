/*
 * Hear.h
 *
 *  Created on: 2012-3-17
 *      Author: cit cw
 */

#ifndef HEAR_H_
#define HEAR_H_
#include "../Stdafx.h"
#include "NumFilter.h"
#include "perceptor.h"
namespace Sensor
{

class Hear
{
public:
	Hear();
	void SetHearNumAsMe();
	bool VanNumdifference();
	void ParseHearInfo(string words);
	void ParseMyHearInfo(string words);
	int donotgetothersay;
	int GetnowSayNumber()
	{
		return nowSaynum;
	}
	virtual ~Hear();
	int GetClosestToGoaile()
	{
		return TheLastPlayerfilter.GetFilterNum();
	}
	int GetNextClosestToGoaile()
	{
		return NextClosestTofilter.GetFilterNum();
	}
	bool IsStandByHear(int num)
	{
		return IsStand[num - 1];
	}
	int GetNowVanguardnum(){return Vanguardnumfilter.GetFilterNum();}
	int GetAnum(){return Anumfilter.GetFilterNum();}
	int GetBnum(){return Bnumfilter.GetFilterNum();}
	int GetCnum(){return Cnumfilter.GetFilterNum();}
	int GetDnum(){return Dnumfilter.GetFilterNum();}
	int GetEnum(){return Enumfilter.GetFilterNum();}

	int GetNextClosestToNum(){return NextClosestTofilter.GetFilterNum();}
	int GetTheLastPlayerNum(){return TheLastPlayerfilter.GetFilterNum();}
	void print();
private:
	int notHeardVanguardCount;
	int nowSaynum;
	bool IsStand[PLAYERNUMBER];
	NumFilter Vanguardnumfilter;
	NumFilter Anumfilter;
	NumFilter Bnumfilter;
	NumFilter Cnumfilter;
	NumFilter Dnumfilter;
	NumFilter Enumfilter;
	NumFilter NextClosestTofilter;
	NumFilter TheLastPlayerfilter; //离守门员最近的的一个人
	int notHeardViceVanguard_1Count;
	int GetEnnum(char num);
	float GetEnTime(string str);
};

} /* namespace Sensor */
#endif /* HEAR_H_ */
