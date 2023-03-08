/*
 * SaveCoordinate.cpp
 *
 *  Created on: 2012-5-6
 *      Author: cit32
 */

#include "SaveCoordinate.h"

SaveCoordinate::SaveCoordinate()
{
	// TODO Auto-generated constructor stub
	flag = 0;
	istart = true;
	Acc[flag] = Vector3(0, 0, 0);
	AverageTrustLength = CELL_LENGTH;
}
void SaveCoordinate::init(Vector3 val)
{
	flag = 0;
	istart = true;
	sCoord[flag] = val;
	Acc[flag] = Vector3(0, 0, 0);
	this->increaseFlag();
}
bool SaveCoordinate::insert(Vector3 val)
{
	//cout << "inserting" << val << endl;
	if (!(isnan(fabs(val.x())) || isnan(fabs(val.y())) ))
	{
		if (isnan(fabs(val.z())))
			val.z(0);
		if (istart && flag < 2)
		{
			Acc[flag] = Vector3(0, 0, 0);
		}
		else
		{
			istart = false;
			Acc[flag] = val - sCoord[this->getDecreaseflag()];
		}
		sCoord[flag] = val;
		increaseFlag();
		return true;
	}
	else
	{
		cout << "inserting error this is nan" << val << endl;
	}
	return false;
}
Vector3 SaveCoordinate::GetAverageAcc()
{
	for (int f = 1; f <= AVERAGENUM; f++)
	{
		cout << "f" << f << "::" << Acc[this->getDecreaseflag(f)] << endl;
	}
	Vector3 result;
	if (istart && flag < AVERAGENUM)
	{
		for (int f = 0; f < flag; f++)
		{
			result += Acc[f];
		}
		result = result / flag;
	}
	else
	{
		for (int f = 1; f <= AVERAGENUM; f++)
		{
			result += Acc[this->getDecreaseflag(f)];
		}
		result = result / AVERAGENUM;
	}

	return result;
}
Vector3 SaveCoordinate::GetLastVal()
{
	return sCoord[this->getDecreaseflag()];
}

SaveCoordinate::~SaveCoordinate()
{
	// TODO Auto-generated destructor stub
}
ostream& operator <<(ostream &os, SaveCoordinate v)
{
	os << "LastVal::" << v.GetLastVal() << "  average::" << v.GetAverageAcc()
			<< endl;
	return os;
}

