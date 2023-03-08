#if 1
/// \file Geometry.h
/// @author YiFeng Shan

#ifndef _GEOMETRY_
#define _GEOMETRY_

#include <math.h>       // needed for M_PI constant
#include <string>       // needed for string
#include <iostream>
#include <stdio.h>    // needed for sprintf

using namespace std;

typedef float AngRad; /*!< Type definition for angles in degrees. */
typedef float AngDeg; /*!< Type definition for angles in radians. */

#define EPSILON 0.0001  /*!< Value used for floating point equality tests. */

float sqr(float x);

float max(float d1, float d2);
float min(float d1, float d2);
int sign(float d1);

AngDeg Rad2Deg(AngRad x);
AngRad Deg2Rad(AngDeg x);
float cosDeg(AngDeg x);
float sinDeg(AngDeg x);
float tanDeg(AngDeg x);
AngDeg atanDeg(float x);
float atan2Deg(float x, float y);
AngDeg acosDeg(float x);
AngDeg asinDeg(float x);

bool isAngInInterval(AngDeg ang, AngDeg angMin, AngDeg angMax);
AngDeg getBisectorTwoAngles(AngDeg angMin, AngDeg angMax);

void Matrix(float[][4], float[4], float[4]);

enum CoordSystemT
{
	CARTESIAN, POLAR
};

/********************   CLASS VECPOSITION   **********************************/

class Vector3
{
	// private member data
private:

	float X; /*!< x-coordinate of this position */
	float Y; /*!< y-coordinate of this position */
	float Z; /*!< z-coordinate of this position */

	// public methods
public:
	// constructor for Vector3 class
	Vector3(const Vector3& v)
	{
		*this = v;
	}
	Vector3(float xx = 0, float yy = 0, float zz = 0)
	{
		X = xx;
		Y = yy;
		Z = zz;
	}

	// overloaded arithmetic operators
	Vector3 operator -();
	Vector3 operator +(const float &d);
	Vector3 operator +(const Vector3 &p);
	Vector3 operator -(const float &d);
	Vector3 operator -(const Vector3 &p);
	Vector3 operator *(const float &d);
//	Vector3 operator * ( const Vector3 &p );
	float operator *(const Vector3 &p);
	Vector3 operator /(const float &d);
	Vector3 operator /(const Vector3 &p);
	void operator =(const float &d);
	void operator +=(const Vector3 &p);
	void operator +=(const float &d);
	void operator -=(const Vector3 &p);
	void operator -=(const float &d);
	void operator *=(const Vector3 &p);
	void operator *=(const float &d);
	void operator /=(const Vector3 &p);
	void operator /=(const float &d);
	bool operator !=(const Vector3 &p);
	bool operator !=(const float &d);
	bool operator ==(const Vector3 &p);
	bool operator ==(const float &d);

	// methods for producing output
	friend ostream& operator <<(ostream &os, Vector3 v);
	void show();
	string str();

	// set- and get methods for private member variables
	void x(float dX)
	{
		X = dX;
	}
	float x() const
	{
		return X;
	}
	void y(float dY)
	{
		Y = dY;
	}
	float y() const
	{
		return Y;
	}
	void z(float dZ)
	{
		Z = dZ;
	}
	float z() const
	{
		return Z;
	}

	// set- and get methods for derived position information
	void setVector3(float dX = 0, float dY = 0, float dZ = 0);
	float length() const;
	float getDistanceTo(const Vector3 p);
	Vector3 setMod(float d);
	float mod();
	float xymod();
	AngDeg getDirection() const;
	AngDeg getTheta() const;
	AngDeg getPhi() const;
	float getCosAngX();
	float getCosAngY();
	float getCosAngZ();
	// comparison methods for positions
	bool isInFrontOf(const Vector3 &p);
	bool isInFrontOf(const float &d);
	bool isBehindOf(const Vector3 &p);
	bool isBehindOf(const float &d);
	bool isLeftOf(const Vector3 &p);
	bool isLeftOf(const float &d);
	bool isRightOf(const Vector3 &p);
	bool isRightOf(const float &d);
	bool isUpOf(const Vector3 &p);
	bool isUpOf(const float &d);
	bool isDownOf(const Vector3 &p);
	bool isDownOf(const float &d);
	bool isBetweenX(const Vector3 &p1, const Vector3 &p2);
	bool isBetweenX(const float &d1, const float &d2);
	bool isBetweenY(const Vector3 &p1, const Vector3 &p2);
	bool isBetweenY(const float &d1, const float &d2);
	bool isBetweenZ(const Vector3 &p1, const Vector3 &p2);
	bool isBetweenZ(const float &d1, const float &d2);

	// conversion methods for positions
	Vector3 normalizeCalculation();
	Vector3 crossProduct(Vector3 const &other);
	float invSqrt(float x);
	Vector3 normalize();
	Vector3 rotate(AngDeg angle);
	Vector3 globalToRelative(Vector3 orig, AngDeg ang);
	Vector3 relativeToGlobal(Vector3 orig, AngDeg ang);
	Vector3 getVector3OnLineFraction(Vector3 &p, float dFrac);

	// static class methods
	static Vector3 getVector3FromPolar(float dMag, AngDeg theta, AngDeg phi);
	static AngDeg normalizeAngle(AngDeg angle);
};

/*! This is for using a shared position as an unknown position */
const Vector3 UnknownPosition = Vector3(-1000.0, -1000.0, -1000.0);

/*********************   CLASS GEOMETRY   ************************************/

class Geometry
{

public:

	// geometric series
	static float getLengthGeomSeries(float dFirst, float dRatio, float dSum);
	static float getSumGeomSeries(float dFirst, float dRatio, float dLen);
	static float getSumInfGeomSeries(float dFirst, float dRatio);
	static float getFirstGeomSeries(float dSum, float dRatio, float dLen);
	static float getFirstInfGeomSeries(float dSum, float dRatio);

	// abc formula
	static int abcFormula(float a, float b, float c, float *s1, float *s2);
};

/********************** CLASS CIRCLE *****************************************/

class Circle
{
	Vector3 m_posCenter; /*!< Center of the circle  */
	float m_dRadius; /*!< Radius of the circle  */

public:
	Circle();
	Circle(Vector3 pos, float dR);

	void show(ostream& os = cout);

	// get and set methods
	bool setCircle(Vector3 pos, float dR);
	bool setRadius(float dR);
	float getRadius() const;
	bool setCenter(Vector3 pos);
	Vector3 getCenter();
	float getCircumference();
	float getArea();
	float getVolume() const;

	// calculate intersection points and area with other circle
	bool isInside(Vector3 pos, bool bCircle);
	int getCircleIntersectionPoints(Circle c, Vector3 *p1, Vector3 *p2);
	float getIntersectionArea(Circle c, bool bStrict = false);
};

/********************** CLASS SPHERE *****************************************/

typedef Circle Sphere;

/*********************** CLASS LINE ******************************************/

class Line
{
	// a line is defined by the formula: ay + bx + c = 0
	float m_a; /*!< This is the a coefficient in the line ay + bx + c = 0 */
	float m_b; /*!< This is the b coefficient in the line ay + bx + c = 0 */
	float m_c; /*!< This is the c coefficient in the line ay + bx + c = 0 */

public:
	Line(float a = 0, float b = 0, float c = 0);

	// print methods
	void show(ostream& os = cout);
	friend ostream& operator <<(ostream & os, Line l);

	// get intersection points with this line
	Vector3 getIntersection(Line line);
	int getCircleIntersectionPoints(Circle circle, Vector3 *posSolution1,
			Vector3 *posSolution2);
	Line getTangentLine(Vector3 pos);
	Vector3 getPointOnLineClosestTo(Vector3 pos);
	float getDistanceWithPoint(Vector3 pos);
	bool isInBetween(Vector3 pos, Vector3 point1, Vector3 point2);

	// calculate associated variables in the line
	float getYGivenX(float x);
	float getXGivenY(float y);
	float getACoefficient() const;
	float getBCoefficient() const;
	float getCCoefficient() const;

	// static methods to make a line using an easier representation.
	static Line makeLineFromTwoPoints(Vector3 pos1, Vector3 pos2);
	static Line makeLineFromPositionAndAngle(Vector3 vec, AngDeg angle);
};

/******************************************************************************/
/**************************** CLASS RECTANGLE *********************************/
/******************************************************************************/

/*!This class represents a rectangle. A rectangle is defined by two
 Vector3s the one at the upper left corner and the one at the
 right bottom. */
class Rect
{
	Vector3 m_posLeftTop; /*!< top left position of the rectangle      */
	Vector3 m_posRightBottom; /*!< bottom right position of the rectangle  */

public:
	Rect(Vector3 pos, Vector3 pos2);

	void show(ostream& os = cout);

	// checks whether point lies inside the rectangle
	bool isInside(Vector3 pos);

	// standard get and set methods
	void setRectanglePoints(Vector3 pos1, Vector3 pos2);
	bool setPosLeftTop(Vector3 pos);
	Vector3 getPosLeftTop();
	bool setPosRightBottom(Vector3 pos);
	Vector3 getPosRightBottom();
	bool isIntersect(Line line);
};

/******************************************************************************/
/*************************** CLASS PLANE **************************************/
/******************************************************************************/

/*!This class represents a plane in 3 Dimensional space. A plane is
 defined by a normal vector and a point in the plane.
 */
class Plane
{
	float m_Delta;
	Vector3 m_Normal;

public:
	Plane(Vector3 norm = Vector3(0, 0, 0), Vector3 pos = Vector3(0, 0, 0));

	void show(ostream& os = cout) const;

	// checks whether point lies inside the rectangle
	bool isInside(Vector3 pos) const;

	// standard get and set methods
	void setPlane(Vector3 newNormal, Vector3 newPoint);
	bool setPlaneNormal(Vector3 newNormal);
	Vector3 getPlaneNormal() const;
	bool setPlaneDelta(float newDelta);
	float getPlaneDelta() const;
};
#endif
#endif
