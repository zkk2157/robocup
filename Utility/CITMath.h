/*
 * CITMath.h
 *
 *  Created on: 2012-5-9
 *      Author: cit32
 */

#ifndef CITMATH_H_
#define CITMATH_H_
#include "Geometry.h"
#include "Types.h"
#include <cmath>
class CITMath
{
public:
	CITMath();
	/**
	 * 注意这是矢量Point1----->Point2的矢量
	 */
	//static float GetTwoPointWithXangle(Vector2 Point1, Vector2 Point2);
	static float GetTwoPointWithXangle(Vector3 Point1,Vector3 Point2);
	//static void sort(SPlayerDis va[], int num);
	virtual ~CITMath();
};

#endif /* CITMATH_H_ */
