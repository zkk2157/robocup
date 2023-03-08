/*
 * NumFilter.cpp
 *
 *  Created on: 2012-5-15
 *      Author: cit32
 */

#include "NumFilter.h"

using namespace std;
NumFilter::NumFilter()
{
	// TODO Auto-generated constructor stub
	subflag = 0;
	Numdifference=true;
}
void NumFilter::init(int val)
{
	subflag = 0;
	for (int i = 0; i < sublong; i++)
	{
		Subffer[i] = val;
	}
	lastfilternum = val;
}
bool NumFilter::InsertNum(int num)
{
	Subffer[subflag] = num;
	subflag = (subflag + 1) % sublong;
	return true;
}
int NumFilter::GetFilterNum()
{
	int statistics[sublong];
	int statNum[sublong];
	for (int i = 0; i < sublong; i++)
	{
		statistics[i] = NoSeeNum;
		statNum[i] = 0;
	}
	for (int i = 0; i < sublong; i++)
	{
		int temp = Subffer[i];
		//	cout<<"temp::"<<temp<<endl;
		for (int k = 0; k < sublong; k++)
		{
			//	cout<<"statistics["<<k<<"]="<<statistics[k]<<"  statNum["<<k<<"]="<<statNum[k]<<endl;
			if (statistics[k] == temp || statistics[k] == NoSeeNum)
			{
				statistics[k] = temp;
				statNum[k]++;
				break;
			}
		}
		for (int k = 0; k < sublong; k++)
		{
			//	cout<<"statistics["<<k<<"]="<<statistics[k]<<"  statNum["<<k<<"]="<<statNum[k]<<endl;
		}
	}
	int falk = 0;
	for (int i = 0; i < sublong; i++)
	{
		if (statNum[falk] < statNum[i])
		{
			falk = i;
		}
	}
//cout<<"falk::"<<falk<<endl;
//	for (int i = 0; i < sublong; i++)
//	{
//      cout<<"Subffer["<<i<<"]="<<Subffer[i]<<endl;
//	}
	if (statNum[falk] == 1 || (falk > sublong))
	{
//		cout << "usingl astfilternum" << endl;
		Numdifference=true;
		if (NumisInSubffer(lastfilternum))
		{

			return lastfilternum;
		}
		else
		{
			return Subffer[(subflag - 1 + sublong) % sublong];
		}
	}
	else
	{

		Numdifference=false;
		lastfilternum = statistics[falk];
		return statistics[falk];
	}
}
bool NumFilter::NumisInSubffer(int num)
{
	for (int i = 0; i < sublong; i++)
	{
		if (num == Subffer[i])
		{
			return true;
		}
	}
	return false;
}
NumFilter::~NumFilter()
{
	// TODO Auto-generated destructor stub
}

