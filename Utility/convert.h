/*
 * <file:Strategy/:the convert class create for convert to all kind of date , cit3d>
 *    Copyright (C) <2011>  <author:chen <chen15861132927@gmail.com>>
 */
#ifndef CIT3DCONVERT_H
#define CIT3DCONVERT_H
#include <string>
#include <iostream>
#include <sstream>
#include <sys/time.h>
#include <stdlib.h>
#include "../Utility/Geometry.h"
using namespace std;
class Convert
{
public:
	static float AngleTurn180(float val);
	static Vector3 Turn180(Vector3 val);
	static bool ToBool(string str);
	static string ToString(int val); //将int型转化成string型
	static string ToString(int val, int num); //将int型转化成string型
	static string ToString(float val); //将float 转化成string型
	static string ToString(float val, int num, int decimalnum); //将float转化成num位整数，decimal位小数的string
	string ToStringWithsign(float val, int num, int decimalnum);
	static string ToString(char a);
	static float ToFloat(string str); //将string转化为float
	static int ToInt(string str); //将string转化为int
};
#endif
