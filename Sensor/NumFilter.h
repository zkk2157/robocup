/*
 * NumFilter.h
 *
 *  Created on: 2012-5-15
 *      Author: cit32
 */

#ifndef NUMFILTER_H_
#define NUMFILTER_H_
#include <iostream>
class NumFilter
{
public:
	void init(int val);
	bool InsertNum(int num);
	int GetFilterNum();
	bool isNumdifference(){return Numdifference;}
	NumFilter();
	virtual ~NumFilter();
private:
	bool NumisInSubffer(int num);
private:
	const static int sublong=3;
	const static int NoSeeNum=-1;//不可能出现的数字
	int lastfilternum;
	int subflag;
	int Subffer[sublong];
	bool Numdifference;
};

#endif /* NUMFILTER_H_ */
