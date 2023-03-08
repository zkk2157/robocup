#if 1
/// \file Geometry.cpp

#include "Geometry.h"
#include <stdio.h>    // needed for sprintf
#include "math.h"

void Matrix(float m_a[4][4], float m_b[4], float resault[4])
{
	float sum;
	for (int a_i = 0; a_i < 4; a_i++)
	{
		sum = 0.0;
		for (int a_j = 0; a_j < 4; a_j++)
		{
			sum += m_a[a_i][a_j] * m_b[a_j];
		}
		resault[a_i] = sum;
	}

}

float Vector3::getCosAngX()
{
	return X / sqrt(X * X + Y * Y + Z * Z);
}

float Vector3::getCosAngY()
{
	return Y / sqrt(X * X + Y * Y + Z * Z);
}

float Vector3::getCosAngZ()
{
	return Z / sqrt(X * X + Y * Y + Z * Z);
}

inline float sqr(float x)
{
	return x * x;
}

int sign(float d1)
{
	return (d1 > 0) ? 1 : -1;
}

float max(float d1, float d2)
{
	return (d1 > d2) ? d1 : d2;
}

float min(float d1, float d2)
{
	return (d1 < d2) ? d1 : d2;
}

AngDeg Rad2Deg(AngRad x)
{
	return (x * 180 / M_PI);
}

AngRad Deg2Rad(AngDeg x)
{
	return (x * M_PI / 180);
}

float cosDeg(AngDeg x)
{
	return (cos(Deg2Rad(x)));
}

float sinDeg(AngDeg x)
{
	return (sin(Deg2Rad(x)));
}

float tanDeg(AngDeg x)
{
	return (tan(Deg2Rad(x)));
}

AngDeg atanDeg(float x)
{
	return (Rad2Deg(atan(x)));
}

float atan2Deg(float x, float y)
{
	if (fabs(x) < EPSILON && fabs(y) < EPSILON)
		return (0.0);

	return (Rad2Deg(atan2(x, y)));
}

AngDeg acosDeg(float x)
{
	if (x >= 1)
		return (0.0);
	else if (x <= -1)
		return (180.0);

	return (Rad2Deg(acos(x)));
}

AngDeg asinDeg(float x)
{
	if (x >= 1)
		return (90.0);
	else if (x <= -1)
		return (-90.0);

	return (Rad2Deg(asin(x)));
}

bool isAngInInterval(AngDeg ang, AngDeg angMin, AngDeg angMax)
{
	// convert all angles to interval 0..360
	if ((ang + 360) < 360)
		ang += 360;
	if ((angMin + 360) < 360)
		angMin += 360;
	if ((angMax + 360) < 360)
		angMax += 360;

	if (angMin < angMax) // 0 ---false-- angMin ---true-----angMax---false--360
		return angMin < ang && ang < angMax;
	else
		// 0 ---true--- angMax ---false----angMin---true---360
		return !(angMax < ang && ang < angMin);
}

AngDeg getBisectorTwoAngles(AngDeg angMin, AngDeg angMax)
{
	// separate sine and cosine part to circumvent boundary problem
	return Vector3::normalizeAngle(
			atan2Deg((sinDeg(angMin) + sinDeg(angMax)) / 2.0,
					(cosDeg(angMin) + cosDeg(angMax)) / 2.0));
}

/*******************   CLASS VECTOR3   ***********************************/

Vector3 Vector3::operator -()
{
	return (Vector3(-X, -Y, -Z));
}

Vector3 Vector3::operator +(const float &d)
{
	return (Vector3(X + d, Y + d, Z + d));
}

Vector3 Vector3::operator +(const Vector3 &p)
{
	return (Vector3(X + p.X, Y + p.Y, Z + p.Z));
}

Vector3 Vector3::operator -(const float &d)
{
	return (Vector3(X - d, Y - d, Z - d));
}

Vector3 Vector3::operator -(const Vector3 &p)
{
	return (Vector3(X - p.X, Y - p.Y, Z - p.Z));
}

Vector3 Vector3::operator *(const float &d)
{
	return (Vector3(X * d, Y * d, Z * d));
}

//Vector3 Vector3::operator * ( const Vector3 &p )
//{
//  return ( Vector3( X * p.X, Y * p.Y, Z * p.Z ) );
//}

float Vector3::operator *(const Vector3 &p)
{
	return (X * p.X + Y * p.Y + Z * p.Z);
}
Vector3 Vector3::operator /(const float &d)
{
	return (Vector3(X / d, Y / d, Z / d));
}

Vector3 Vector3::operator /(const Vector3 &p)
{
	return (Vector3(X / p.X, Y / p.Y, Z / p.Z));
}

void Vector3::operator =(const float &d)
{
	X = d;
	Y = d;
	Z = d;
}

void Vector3::operator +=(const Vector3 &p)
{
	X += p.X;
	Y += p.Y;
	Z += p.Z;
}

void Vector3::operator +=(const float &d)
{
	X += d;
	Y += d;
	Z += d;
}

void Vector3::operator -=(const Vector3 &p)
{
	X -= p.X;
	Y -= p.Y;
	Z -= p.Z;
}

void Vector3::operator -=(const float &d)
{
	X -= d;
	Y -= d;
	Z -= d;
}

void Vector3::operator *=(const Vector3 &p)
{
	X *= p.X;
	Y *= p.Y;
	Z *= p.Z;
}

void Vector3::operator *=(const float &d)
{
	X *= d;
	Y *= d;
	Z *= d;
}

void Vector3::operator /=(const Vector3 &p)
{
	X /= p.X;
	Y /= p.Y;
	Z /= p.Z;
}

void Vector3::operator /=(const float &d)
{
	X /= d;
	Y /= d;
	Z /= d;
}

bool Vector3::operator !=(const Vector3 &p)
{
	return ((X != p.X) || (Y != p.Y) || (Z != p.Z));
}

bool Vector3::operator !=(const float &d)
{
	return ((X != d) || (Y != d) || (Z != d));
}

bool Vector3::operator ==(const Vector3 &p)
{
	return ((X == p.X) && (Y == p.Y) && (Z == p.Z));
}

bool Vector3::operator ==(const float &d)
{
	return ((X == d) && (Y == d) && (Z == d));
}

ostream& operator <<(ostream &os, Vector3 v)
{
	return (os << "( " << v.X << ", " << v.Y << ", " << v.Z << " )");
}

void Vector3::show()
{
	cout << *this << endl;
}

string Vector3::str()
{
	char buf[1024];
	sprintf(buf, "( %f, %f, %f )", x(), y(), z());
	string str(buf);
	return (str);
}

void Vector3::setVector3(float dX, float dY, float dZ)
{
	X = dX;
	Y = dY;
	Z = dZ;
}
float Vector3::length() const
{
	return (X * X + Y * Y + Z * Z);
}
float Vector3::getDistanceTo(const Vector3 p)
{
	return ((*this - p).mod());
}

Vector3 Vector3::setMod(float d)
{
	if (mod() > EPSILON)
		(*this) *= (d / mod() );

	return (*this);
}

float Vector3::mod()
{
	return sqrt(sqr(this->x()) + sqr(this->y()) + sqr(this->z()));
}

float Vector3::xymod()
{
	return sqrt(sqr(this->x()) + sqr(this->y()));
}
Vector3 Vector3::crossProduct(Vector3 const &other)
{
	return Vector3((this->y() * other.z() - this->z() * other.y()), 
	(this->z() * other.x() - this->x() * other.z()),
	(this->x() * other.y() - this->y() * other.x())
	);
}

Vector3 Vector3::normalizeCalculation()
{
	return (*this)
			* invSqrt(
					this->x() * this->x() + this->y() * this->y()
							+ this->z() * this->z());
}

float Vector3::invSqrt(float x)
{
	float xhalf = 0.5f * x;
	int i = *(int*) &x; // get bits for floating value
	i = 0x5f3759df - (i >> 1); // gives initial guess y0
	x = *(float*) &i; // convert bits back to float
	x = x * (1.5f - xhalf * x * x); // Newton step, repeating increases accuracy
	return x;
}

AngDeg Vector3::getDirection() const
{
	return (atan2Deg(Y, X));
}

AngDeg Vector3::getTheta() const
{
	return (atan2Deg(Y, X));
}

AngDeg Vector3::getPhi() const
{
	float dXYPict = sqrt(X * X + Y * Y);
	return (atan2Deg(Z, dXYPict));
}

bool Vector3::isInFrontOf(const Vector3 &p)
{
	return ((X > p.x() ) ? true : false );}

bool Vector3::isInFrontOf(const float &d)
{
	return ((X > d ) ? true : false );}

bool Vector3::isBehindOf(const Vector3 &p)
{
	return ((X < p.x() ) ? true : false );}

bool Vector3::isBehindOf(const float &d)
{
	return ((X < d ) ? true : false );}

bool Vector3::isLeftOf(const Vector3 &p)
{
	return ((Y < p.y() ) ? true : false );}

bool Vector3::isLeftOf(const float &d)
{
	return ((Y < d ) ? true : false );}

bool Vector3::isRightOf(const Vector3 &p)
{
	return ((Y > p.y() ) ? true : false );}

bool Vector3::isRightOf(const float &d)
{
	return ((Y > d ) ? true : false );}

bool Vector3::isUpOf(const Vector3 &p)
{
	return ((Z > p.z() ) ? true : false );}

bool Vector3::isUpOf(const float &d)
{
	return ((Z > d ) ? true : false );}

bool Vector3::isDownOf(const Vector3 &p)
{
	return ((Z < p.z() ) ? true : false );}

bool Vector3::isDownOf(const float &d)
{
	return ((Z < d ) ? true : false );}

bool Vector3::isBetweenX(const Vector3 &p1, const Vector3 &p2)
{
	return ((isInFrontOf(p1) && isBehindOf(p2) ) ? true : false );}

bool Vector3::isBetweenX(const float &d1, const float &d2)
{
	return ((isInFrontOf(d1) && isBehindOf(d2) ) ? true : false );}

bool Vector3::isBetweenY(const Vector3 &p1, const Vector3 &p2)
{
	return ((isRightOf(p1) && isLeftOf(p2) ) ? true : false );}

bool Vector3::isBetweenY(const float &d1, const float &d2)
{
	return ((isRightOf(d1) && isLeftOf(d2) ) ? true : false );}

bool Vector3::isBetweenZ(const Vector3 &p1, const Vector3 &p2)
{
	return ((isUpOf(p1) && isDownOf(p2) ) ? true : false );}

bool Vector3::isBetweenZ(const float &d1, const float &d2)
{
	return ((isUpOf(d1) && isDownOf(d2) ) ? true : false );}

Vector3 Vector3::normalize()
{
	return (setMod(1.0));
}

Vector3 Vector3::rotate(AngDeg angle)
{
	// determine the polar representation of the current Vector3
	float dMag = this->mod();
	float dNewDir = this->getDirection() + angle; // add rotation angle to theta
	setVector3(dMag, dNewDir, this->getPhi()); // convert back to Cartesian
	return (*this);
}

Vector3 Vector3::globalToRelative(Vector3 origin, AngDeg ang)
{
	// convert global coordinates into relative coordinates by aligning
	// relative frame and world frame. First perform translation to make
	// origins of both frames coincide. Then perform rotation to make
	// axes of both frames coincide (use negative angle since you rotate
	// relative frame to world frame).
	*this -= origin;
	return (rotate(-ang));
}

Vector3 Vector3::relativeToGlobal(Vector3 origin, AngDeg ang)
{
	// convert relative coordinates into global coordinates by aligning
	// world frame and relative frame. First perform rotation to make
	// axes of both frames coincide (use positive angle since you rotate
	// world frame to relative frame). Then perform translation to make
	// origins of both frames coincide.
	rotate(ang);
	*this += origin;
	return (*this);
}

Vector3 Vector3::getVector3OnLineFraction(Vector3 &p, float dFrac)
{
	// determine point on line that lies at fraction dFrac of whole line
	// example: this --- 0.25 ---------  p
	// formula: this + dFrac * ( p - this ) = this - dFrac * this + dFrac * p =
	//          ( 1 - dFrac ) * this + dFrac * p
	return ((*this) * (1.0 - dFrac) + (p * dFrac));
}

Vector3 Vector3::getVector3FromPolar(float dMag, AngDeg theta, AngDeg phi)
{
	float z = dMag * sinDeg(phi);
	float XY = dMag * cosDeg(phi);
	float x = XY * cosDeg(theta);
	float y = XY * sinDeg(theta);
	return (Vector3(x, y, z));
}

AngDeg Vector3::normalizeAngle(AngDeg angle)
{
	while (angle > 180.0)
		angle -= 360.0;
	while (angle < -180.0)
		angle += 360.0;

	return (angle);
}

/*****************************************************************************/
/********************** CLASS GEOMETRY ***************************************/
/*****************************************************************************/

/*! A geometric series is one in which there is a constant ratio between each
 element and the one preceding it. This method determines the
 length of a geometric series given its first element, the sum of the
 elements in the series and the constant ratio between the elements.
 Normally: s = a + ar + ar^2 + ...  + ar^n
 Now: dSum = dFirst + dFirst*dRatio + dFirst*dRatio^2 + .. + dFist*dRatio^n
 \param dFirst first term of the series
 \param dRatio ratio with which the the first term is multiplied
 \param dSum the total sum of all the serie
 \return the length(n in above example) of the series */
float Geometry::getLengthGeomSeries(float dFirst, float dRatio, float dSum)
{
	if (dRatio < 0)
		cerr << "(Geometry:getLengthGeomSeries): negative ratio" << endl;

	// s = a + ar + ar^2 + .. + ar^n-1 and thus sr = ar + ar^2 + .. + ar^n
	// subtract: sr - s = - a + ar^n) =>  s(1-r)/a + 1 = r^n = temp
	// log r^n / n = n log r / log r = n = length
	float temp = (dSum * (dRatio - 1) / dFirst) + 1;
	if (temp <= 0)
		return -1.0;
	return log(temp) / log(dRatio);
}

/*! A geometric series is one in which there is a constant ratio between each
 element and the one preceding it. This method determines the sum of a
 geometric series given its first element, the ratio and the number of steps
 in the series
 Normally: s = a + ar + ar^2 + ...  + ar^n
 Now: dSum = dFirst + dFirst*dRatio + ... + dFirst*dRatio^dSteps
 \param dFirst first term of the series
 \param dRatio ratio with which the the first term is multiplied
 \param dLength the number of steps to be taken into account
 \return the sum of the series */
float Geometry::getSumGeomSeries(float dFirst, float dRatio, float dLength)
{
	// s = a + ar + ar^2 + .. + ar^n-1 and thus sr = ar + ar^2 + .. + ar^n
	// subtract: s - sr = a - ar^n) =>  s = a(1-r^n)/(1-r)
	return dFirst * (1 - pow(dRatio, dLength)) / (1 - dRatio);
}

/*! A geometric series is one in which there is a constant ratio between each
 element and the one preceding it. This method determines the sum of an
 infinite geometric series given its first element and the constant ratio
 between the elements. Note that such an infinite series will only converge
 when 0<r<1.
 Normally: s = a + ar + ar^2 + ar^3 + ....
 Now: dSum = dFirst + dFirst*dRatio + dFirst*dRatio^2...
 \param dFirst first term of the series
 \param dRatio ratio with which the the first term is multiplied
 \return the sum of the series */
float Geometry::getSumInfGeomSeries(float dFirst, float dRatio)
{
	if (dRatio > 1)
		cerr << "(Geometry:CalcLengthGeomSeries): series does not converge"
				<< endl;

	// s = a(1-r^n)/(1-r) with n->inf and 0<r<1 => r^n = 0
	return dFirst / (1 - dRatio);
}

/*! A geometric series is one in which there is a constant ratio between each
 element and the one preceding it. This method determines the first element
 of a geometric series given its element, the ratio and the number of steps
 in the series
 Normally: s = a + ar + ar^2 + ...  + ar^n
 Now: dSum = dFirst + dFirst*dRatio + ... + dFirst*dRatio^dSteps
 \param dSum sum of the series
 \param dRatio ratio with which the the first term is multiplied
 \param dLength the number of steps to be taken into account
 \return the first element (a) of a serie */
float Geometry::getFirstGeomSeries(float dSum, float dRatio, float dLength)
{
	// s = a + ar + ar^2 + .. + ar^n-1 and thus sr = ar + ar^2 + .. + ar^n
	// subtract: s - sr = a - ar^n) =>  s = a(1-r^n)/(1-r) => a = s*(1-r)/(1-r^n)
	return dSum * (1 - dRatio) / (1 - pow(dRatio, dLength));
}

/*! A geometric series is one in which there is a constant ratio between each
 element and the one preceding it. This method determines the first element
 of an infinite geometric series given its first element and the constant
 ratio between the elements. Note that such an infinite series will only
 converge when 0<r<1.
 Normally: s = a + ar + ar^2 + ar^3 + ....
 Now: dSum = dFirst + dFirst*dRatio + dFirst*dRatio^2...
 \param dSum sum of the series
 \param dRatio ratio with which the the first term is multiplied
 \return the first term of the series */
float Geometry::getFirstInfGeomSeries(float dSum, float dRatio)
{
	if (dRatio > 1)
		cerr << "(Geometry:getFirstInfGeomSeries):series does not converge"
				<< endl;

	// s = a(1-r^n)/(1-r) with r->inf and 0<r<1 => r^n = 0 => a = s ( 1 - r)
	return dSum * (1 - dRatio);
}

/*! This method performs the abc formula (Pythagoras' Theorem) on the given
 parameters and puts the result in *s1 en *s2. It returns the number of
 found coordinates.
 \param a a parameter in abc formula
 \param b b parameter in abc formula
 \param c c parameter in abc formula
 \param *s1 first result of abc formula
 \param *s2 second result of abc formula
 \return number of found x-coordinates */
int Geometry::abcFormula(float a, float b, float c, float *s1, float *s2)
{
	float dDiscr = b * b - 4 * a * c; // discriminant is b^2 - 4*a*c
	if (fabs(dDiscr) < EPSILON) // if discriminant = 0
	{
		*s1 = -b / (2 * a); //  only one solution
		return 1;
	}
	else if (dDiscr < 0) // if discriminant < 0
		return 0; //  no solutions
	else // if discriminant > 0
	{
		dDiscr = sqrt(dDiscr); //  two solutions
		*s1 = (-b + dDiscr) / (2 * a);
		*s2 = (-b - dDiscr) / (2 * a);
		return 2;
	}
}

/*****************************************************************************/
/********************* CLASS CIRCLE ******************************************/
/*****************************************************************************/

/*! This is the constructor of a circle.
 \param pos first point that defines the center of circle
 \param dR the radius of the circle
 \return circle with pos as center and radius as radius*/
Circle::Circle(Vector3 pos, float dR)
{
	setCircle(pos, dR);
}

/*! This is the constructor of a circle which initializes a circle with a
 radius of zero. */
Circle::Circle()
{
	setCircle(Vector3(-1000.0, -1000.0, -1000.0), 0);
}

/*! This method prints the circle information to the specified output stream
 in the following format: "c: (c_x,c_y,c_z), r: rad" where (c_x,c_y,z_z) denotes
 the center of the circle and rad the radius.
 \param os output stream to which output is written. */
void Circle::show(ostream& os)
{
	os << "c:" << m_posCenter << ", r:" << m_dRadius;
}

/*! This method sets the values of the circle.
 \param pos new center of the circle
 \param dR new radius of the circle
 ( > 0 )
 \return bool indicating whether radius was set */
bool Circle::setCircle(Vector3 pos, float dR)
{
	setCenter(pos);
	return setRadius(dR);
}
/*! This method sets the radius of the circle.
 \param dR new radius of the circle ( > 0 )
 \return bool indicating whether radius was set */
bool Circle::setRadius(float dR)
{
	if (dR > 0)
	{
		m_dRadius = dR;
		return true;
	}
	else
	{
		m_dRadius = 0.0;
		return false;
	}
}

/*! This method returns the radius of the circle.
 \return radius of the circle */
float Circle::getRadius() const
{
	return m_dRadius;
}

/*! This method sets the center of the circle.
 \param pos new center of the circle
 \return bool indicating whether center was set */
bool Circle::setCenter(Vector3 pos)
{
	m_posCenter = pos;
	return true;
}

/*! This method returns the center of the circle.
 \return center of the circle */
Vector3 Circle::getCenter()
{
	return m_posCenter;
}

/*! This method returns the circumference of the circle.
 \return circumference of the circle */
float Circle::getCircumference()
{
	return 2.0 * M_PI * getRadius();
}

/*! This method returns the area inside the circle.
 \return area inside the circle */
float Circle::getArea()
{
	return M_PI * getRadius() * getRadius();
}

/*! This method returns the volume of a circle.
 \return volume inside the circle */
float Circle::getVolume() const
{
	return M_PI * 4 / 3 * getRadius() * getRadius() * getRadius();
}

/*! This method returns a boolean that indicates whether 'pos' is
 located inside the circle.
 
 \param pos position of which should be checked whether it is
 located in the circle
 \param bCircle denotes wheather the check is made for a 
 circle or a sphere

 \return bool indicating whether pos lies inside the circle */
bool Circle::isInside(Vector3 pos, bool bCircle)
{
	if (bCircle)
		pos.z(m_posCenter.z());

	return m_posCenter.getDistanceTo(pos) < getRadius();
}

int Circle::getCircleIntersectionPoints(Circle c, Vector3 *p1, Vector3 *p2)
{
	float x0, y0, r0;
	float x1, y1, r1;

	Vector3 tmpCenter = c.getCenter();
	tmpCenter.z(m_posCenter.z());
	c.setCenter(tmpCenter);

	x0 = getCenter().x();
	y0 = getCenter().y();
	r0 = getRadius();
	x1 = c.getCenter().x();
	y1 = c.getCenter().y();
	r1 = c.getRadius();

	float d, dx, dy, h, a, x, y, p2_x, p2_y;

	// first calculate distance between two centers circles P0 and P1.
	dx = x1 - x0;
	dy = y1 - y0;
	d = sqrt(dx * dx + dy * dy);

	// normalize differences
	dx /= d;
	dy /= d;

	// a is distance between p0 and point that is the intersection point P2
	// that intersects P0-P1 and the line that crosses the two intersection
	// points P3 and P4.
	// Define two triangles: P0,P2,P3 and P1,P2,P3.
	// with distances a, h, r0 and b, h, r1 with d = a + b
	// We know a^2 + h^2 = r0^2 and b^2 + h^2 = r1^2 which then gives
	// a^2 + r1^2 - b^2 = r0^2 with d = a + b ==> a^2 + r1^2 - (d-a)^2 = r0^2
	// ==> r0^2 + d^2 - r1^2 / 2*d
	a = (r0 * r0 + d * d - r1 * r1) / (2.0 * d);

	// h is then a^2 + h^2 = r0^2 ==> h = sqrt( r0^2 - a^2 )
	float arg = r0 * r0 - a * a;
	h = (arg > 0.0) ? sqrt(arg) : 0.0;

	// First calculate P2
	p2_x = x0 + a * dx;
	p2_y = y0 + a * dy;

	// and finally the two intersection points
	x = p2_x - h * dy;
	y = p2_y + h * dx;
	p1->setVector3(x, y);
	x = p2_x + h * dy;
	y = p2_y - h * dx;
	p2->setVector3(x, y);

	return (arg < 0.0) ? 0 : ((arg == 0.0 ) ? 1 : 2);}

	/*! This method returns the size of the intersection area of two circles.
	 \param c circle with which intersection should be determined
	 \param bStrict weather to check the circles z- intersection
	 \return size of the intersection area. */
float Circle::getIntersectionArea(Circle c, bool bStrict)
{
	Vector3 pos1, pos2, pos3;
	float d, h, dArea;
	AngDeg ang;

	if (bStrict && (c.getCenter().z() != m_posCenter.z())) // If the circles are not
		return 0.0; // in the same XY plane --> no intersection

	d = getCenter().getDistanceTo(c.getCenter()); // dist between two centers
	if (d > c.getRadius() + getRadius()) // larger than sum radii
		return 0.0; // circles do not intersect
	if (d <= fabs(c.getRadius() - getRadius())) // one totally in the other
	{
		float dR = min(c.getRadius(), getRadius()); // return area smallest circ
		return M_PI * dR * dR;
	}

	int iNrSol = getCircleIntersectionPoints(c, &pos1, &pos2);
	if (iNrSol != 2)
		return 0.0;

	// the intersection area of two circles can be divided into two segments:
	// left and right of the line between the two intersection points p1 and p2.
	// The outside area of each segment can be calculated by taking the part
	// of the circle pie excluding the triangle from the center to the
	// two intersection points.
	// The pie equals pi*r^2 * rad(2*ang) / 2*pi = 0.5*rad(2*ang)*r^2 with ang
	// the angle between the center c of the circle and one of the two
	// intersection points. Thus the angle between c and p1 and c and p3 where
	// p3 is the point that lies halfway between p1 and p2.
	// This can be calculated using ang = asin( d / r ) with d the distance
	// between p1 and p3 and r the radius of the circle.
	// The area of the triangle is 2*0.5*h*d.

	pos3 = pos1.getVector3OnLineFraction(pos2, 0.5);
	d = pos1.getDistanceTo(pos3);
	h = pos3.getDistanceTo(getCenter());
	ang = asin(d / getRadius());

	dArea = ang * getRadius() * getRadius();
	dArea = dArea - d * h;

	// and now for the other segment the same story
	h = pos3.getDistanceTo(c.getCenter());
	ang = asin(d / c.getRadius());
	dArea = dArea + ang * c.getRadius() * c.getRadius();
	dArea = dArea - d * h;

	return dArea;
}

/*****************************************************************************/
/***********************  CLASS LINE *****************************************/
/*****************************************************************************/

/*! This constructor creates a line by given the three coefficents of the line.
 A line is specified by the formula ay + bx + c = 0.
 \param dA a coefficients of the line
 \param dB b coefficients of the line
 \param dC c coefficients of the line */
Line::Line(float dA, float dB, float dC)
{
	m_a = dA;
	m_b = dB;
	m_c = dC;
}

/*! This function prints the line to the specified output stream in the
 format y = ax + b.
 \param os output stream to which output is written
 \param l line that is written to output stream
 \return output sream to which output is appended. */
ostream& operator <<(ostream & os, Line l)
{
	float a = l.getACoefficient();
	float b = l.getBCoefficient();
	float c = l.getCCoefficient();

	// ay + bx + c = 0 -> y = -b/a x - c/a
	if (a == 0)
		os << "x = " << -c / b;
	else
	{
		os << "y = ";
		if (b != 0)
			os << -b / a << "x ";
		if (c > 0)
			os << "- " << fabs(c / a);
		else if (c < 0)
			os << "+ " << fabs(c / a);
	}
	return os;
}

/*! This method prints the line information to the specified output stream.
 \param os output stream to which output is written. */
void Line::show(ostream& os)
{
	os << *this;
}

/*! This method returns the intersection point between the current Line and
 the specified line.
 \param line line with which the intersection should be calculated.
 \return Vector3 position that is the intersection point. */
Vector3 Line::getIntersection(Line line)
{
	Vector3 pos;
	float x, y;
	if ((m_a / m_b) == (line.getACoefficient() / line.getBCoefficient()))
		return pos; // lines are parallel, no intersection
	if (m_a == 0) // bx + c = 0 and a2*y + b2*x + c2 = 0 ==> x = -c/b
	{ // calculate x using the current line
		x = -m_c / m_b; // and calculate the y using the second line
		y = line.getYGivenX(x);
	}
	else if (line.getACoefficient() == 0)
	{ // ay + bx + c = 0 and b2*x + c2 = 0 ==> x = -c2/b2
		x = -line.getCCoefficient() / line.getBCoefficient(); // calculate x using
		y = getYGivenX(x); // 2nd line and calculate y using current line
	}
	// ay + bx + c = 0 and a2y + b2*x + c2 = 0
	// y = (-b2/a2)x - c2/a2
	// bx = -a*y - c =>  bx = -a*(-b2/a2)x -a*(-c2/a2) - c ==>
	// ==> a2*bx = a*b2*x + a*c2 - a2*c ==> x = (a*c2 - a2*c)/(a2*b - a*b2)
	// calculate x using the above formula and the y using the current line
	else
	{
		x = (m_a * line.getCCoefficient() - line.getACoefficient() * m_c)
				/ (line.getACoefficient() * m_b - m_a * line.getBCoefficient());
		y = getYGivenX(x);
	}

	return Vector3(x, y);
}

/*! This method calculates the intersection points between the current line
 and the circle specified with as center 'posCenter' and radius 'dRadius'.
 The number of solutions are returned and the corresponding points are put
 in the third and fourth argument of the method
 \param circle circle with which intersection points should be found
 \param posSolution1 first intersection (if any)
 \param posSolution2 second intersection (if any) */
int Line::getCircleIntersectionPoints(Circle circle, Vector3 *posSolution1,
		Vector3 *posSolution2)
{
	int iSol;
	float dSol1 = 0, dSol2 = 0;
	float h = circle.getCenter().x();
	float k = circle.getCenter().y();

	// line:   x = -c/b (if a = 0)
	// circle: (x-h)^2 + (y-k)^2 = r^2, with h = center.x and k = center.y
	// fill in:(-c/b-h)^2 + y^2 -2ky + k^2 - r^2 = 0
	//         y^2 -2ky + (-c/b-h)^2 + k^2 - r^2 = 0
	// and determine solutions for y using abc-formula
	if (fabs(m_a) < EPSILON)
	{
		iSol = Geometry::abcFormula(
				1,
				-2 * k,
				((-m_c / m_b) - h) * ((-m_c / m_b) - h) + k * k
						- circle.getRadius() * circle.getRadius(), &dSol1,
				&dSol2);
		posSolution1->setVector3((-m_c / m_b), dSol1 );
		posSolution2->setVector3((-m_c / m_b), dSol2 );
		return iSol;
	}

	// ay + bx + c = 0 => y = -b/a x - c/a, with da = -b/a and db = -c/a
	// circle: (x-h)^2 + (y-k)^2 = r^2, with h = center.x and k = center.y
	// fill in:x^2 -2hx + h^2 + (da*x-db)^2 -2k(da*x-db) + k^2 - r^2 = 0
	//         x^2 -2hx + h^2 + da^2*x^2 + 2da*db*x + db^2 -2k*da*x -2k*db
	//                                                         + k^2 - r^2 = 0
	//       (1+da^2)*x^2 + 2(da*db-h-k*da)*x + h2 + db^2  -2k*db + k^2 - r^2 = 0
	// and determine solutions for x using abc-formula
	// fill in x in original line equation to get y coordinate
	float da = -m_b / m_a;
	float db = -m_c / m_a;

	float dA = 1 + da * da;
	float dB = 2 * (da * db - h - k * da);
	float dC = h * h + db * db - 2 * k * db + k * k
			- circle.getRadius() * circle.getRadius();

	iSol = Geometry::abcFormula(dA, dB, dC, &dSol1, &dSol2);

	posSolution1->setVector3(dSol1, da * dSol1 + db);
	posSolution2->setVector3(dSol2, da * dSol2 + db);
	return iSol;

}

/*! This method returns the tangent line to a Vector3. This is the line
 between the specified position and the closest point on the line to this
 position.
 \param pos Vector3 point with which tangent line is calculated.
 \return Line line tangent to this position */
Line Line::getTangentLine(Vector3 pos)
{
	// ay + bx + c = 0 -> y = (-b/a)x + (-c/a)
	// tangent: y = (a/b)*x + C1 -> by - ax + C2 = 0 => C2 = ax - by
	// with pos.y = y, pos.x = x
	return Line(m_b, -m_a, m_a * pos.x() - m_b * pos.y());
}

/*! This method returns the closest point on a line to a given position.
 \param pos point to which closest point should be determined
 \return Vector3 closest point on line to 'pos'. */
Vector3 Line::getPointOnLineClosestTo(Vector3 pos)
{
	Line l2 = getTangentLine(pos); // get tangent line
	return getIntersection(l2); // and intersection between the two lines
}

/*! This method returns the distance between a specified position and the
 closest point on the given line.
 \param pos position to which distance should be calculated
 \return float indicating the distance to the line. */
float Line::getDistanceWithPoint(Vector3 pos)
{
	return pos.getDistanceTo(getPointOnLineClosestTo(pos));
}

/*! This method determines whether the projection of a point on the
 current line lies between two other points ('point1' and 'point2')
 that lie on the same line.

 \param pos point of which projection is checked.
 \param point1 first point on line
 \param point2 second point on line
 \return true when projection of 'pos' lies between 'point1' and 'point2'.*/
bool Line::isInBetween(Vector3 pos, Vector3 point1, Vector3 point2)
{
	pos = getPointOnLineClosestTo(pos); // get closest point
	float dDist = point1.getDistanceTo(point2); // get distance between 2 pos

	// if the distance from both points to the projection is smaller than this
	// dist, the pos lies in between.
	return pos.getDistanceTo(point1) <= dDist
			&& pos.getDistanceTo(point2) <= dDist;
}

/*! This method calculates the y coordinate given the x coordinate
 \param x coordinate
 \return y coordinate on this line */
float Line::getYGivenX(float x)
{
	if (m_a == 0)
	{
		cerr << "(Line::yGivenX) Cannot calculate Y coordinate: ";
		show(cerr);
		cerr << endl;
		return 0;
	}
	// ay + bx + c = 0 ==> ay = -(b*x + c)/a
	return -(m_b * x + m_c) / m_a;
}

/*! This method calculates the x coordinate given the x coordinate
 \param y coordinate
 \return x coordinate on this line */
float Line::getXGivenY(float y)
{
	if (m_b == 0)
	{
		cerr << "(Line::xGivenY) Cannot calculate X coordinate\n";
		return 0;
	}
	// ay + bx + c = 0 ==> bx = -(a*y + c)/a
	return -(m_a * y + m_c) / m_b;
}

/*! This method creates a line given two points.
 \param pos1 first point
 \param pos2 second point
 \return line that passes through the two specified points. */
Line Line::makeLineFromTwoPoints(Vector3 pos1, Vector3 pos2)
{
	// 1*y + bx + c = 0 => y = -bx - c
	// with -b the direction coefficient (or slope)
	// and c = - y - bx
	float dA, dB, dC;
	float dTemp = pos2.x() - pos1.x(); // determine the slope
	if (fabs(dTemp) < EPSILON)
	{
		// ay + bx + c = 0 with vertical slope=> a = 0, b = 1
		dA = 0.0;
		dB = 1.0;
	}
	else
	{
		// y = (-b)x -c with -b the slope of the line
		dA = 1.0;
		dB = -(pos2.y() - pos1.y()) / dTemp;
	}
	// ay + bx + c = 0 ==> c = -a*y - b*x
	dC = -dA * pos2.y() - dB * pos2.x();
	return Line(dA, dB, dC);
}

/*! This method creates a line given a position and an angle.
 \param vec position through which the line passes
 \param angle direction of the line.
 \return line that goes through position 'vec' with angle 'angle'. */
Line Line::makeLineFromPositionAndAngle(Vector3 vec, AngDeg angle)
{
	// calculate point somewhat further in direction 'angle' and make
	// line from these two points.
	return makeLineFromTwoPoints(vec, vec + Vector3(1, angle, POLAR));
}

/*! This method returns the a coefficient from the line ay + bx + c = 0.
 \return a coefficient of the line. */
float Line::getACoefficient() const
{
	return m_a;
}

/*! This method returns the b coefficient from the line ay + bx + c = 0.
 \return b coefficient of the line. */
float Line::getBCoefficient() const
{
	return m_b;
}

/*! This method returns the c coefficient from the line ay + bx + c = 0.
 \return c coefficient of the line. */
float Line::getCCoefficient() const
{
	return m_c;
}

/*****************************************************************************/
/********************* CLASS RECTANGLE ***************************************/
/*****************************************************************************/

/*! This is the constructor of a Rectangle. Two points will be given. The
 order does not matter as long as two opposite points are given (left
 top and right bottom or right top and left bottom).
 \param pos first point that defines corner of rectangle
 \param pos2 second point that defines other corner of rectangle
 \return rectangle with 'pos' and 'pos2' as opposite corners. */
Rect::Rect(Vector3 pos, Vector3 pos2)
{
	setRectanglePoints(pos, pos2);
}

/*! This method sets the upper left and right bottom point of the current
 rectangle.
 \param pos1 first point that defines corner of rectangle
 \param pos2 second point that defines other corner of rectangle */
void Rect::setRectanglePoints(Vector3 pos1, Vector3 pos2)
{
	m_posLeftTop.x(max(pos1.x(), pos2.x()));
	m_posLeftTop.y(min(pos1.y(), pos2.y()));
	m_posRightBottom.x(min(pos1.x(), pos2.x()));
	m_posRightBottom.y(max(pos1.y(), pos2.y()));
}

/*! This method prints the rectangle to the specified output stream in the
 format rect( top_left_point, bottom_right_point ).
 \param os output stream to which rectangle is written. */
void Rect::show(ostream& os)
{
	os << "rect(" << m_posLeftTop << " " << m_posRightBottom << ")";
}

/*! This method determines whether the given position lies inside the current
 rectangle.
 \param pos position which is checked whether it lies in rectangle
 \return true when 'pos' lies in the rectangle, false otherwise */
bool Rect::isInside(Vector3 pos)
{
	return pos.isBetweenX(m_posRightBottom.x(), m_posLeftTop.x())
			&& pos.isBetweenY(m_posLeftTop.y(), m_posRightBottom.y());

}

/*! This method sets the top left position of the rectangle
 \param pos new top left position of the rectangle
 \return true when update was successful */
bool Rect::setPosLeftTop(Vector3 pos)
{
	m_posLeftTop = pos;
	return true;
}

/*! This method returns the top left position of the rectangle
 \return top left position of the rectangle */
Vector3 Rect::getPosLeftTop()
{
	return m_posLeftTop;
}

/*! This method sets the right bottom position of the rectangle
 \param pos new right bottom position of the rectangle
 \return true when update was succesfull */
bool Rect::setPosRightBottom(Vector3 pos)
{
	m_posRightBottom = pos;
	return true;
}

/*! This method returns the right bottom position of the rectangle
 \return top right bottom of the rectangle */
Vector3 Rect::getPosRightBottom()
{
	return m_posRightBottom;
}

bool Rect::isIntersect(Line line)
{
	bool iscros;
	Vector3 pos_r_t, pos_r_b, pos_l_t, pos_l_b, pos_c;
	pos_r_t = m_posLeftTop;
	pos_l_b = m_posRightBottom;
//	pos_r_b=Vector3::Vector3( m_posLeftTop.x(),m_posRightBottom.y(),0);
//	pos_l_t=Vector3::Vector3( m_posRightBottom.x(),m_posLeftTop.y(),0);

	Line line_r, line_l, line_t, line_b;
	line_r = Line::makeLineFromTwoPoints(pos_r_t, pos_r_b);
	line_l = Line::makeLineFromTwoPoints(pos_l_b, pos_l_t);
	line_t = Line::makeLineFromTwoPoints(pos_r_t, pos_l_t);
	line_b = Line::makeLineFromTwoPoints(pos_l_b, pos_r_b);

	pos_c = line.getIntersection(line_r);
	if (pos_c.isBetweenX(pos_r_t, pos_r_b)
			|| pos_c.isBetweenY(pos_r_t, pos_r_b))
		iscros = true;

	pos_c = line.getIntersection(line_l);
	if (pos_c.isBetweenX(pos_l_t, pos_l_b)
			|| pos_c.isBetweenY(pos_l_t, pos_l_b))
		iscros = true;

	pos_c = line.getIntersection(line_t);
	if (pos_c.isBetweenX(pos_r_t, pos_r_t)
			|| pos_c.isBetweenY(pos_r_t, pos_r_t))
		iscros = true;

	pos_c = line.getIntersection(line_b);
	if (pos_c.isBetweenX(pos_r_b, pos_r_b)
			|| pos_c.isBetweenY(pos_r_b, pos_r_b))
		iscros = true;

	return iscros;
}

/*****************************************************************************/
/************************* CLASS PLANE ***************************************/
/*****************************************************************************/

/*! This is the constructor of a Plane. A normal vector and a position on
 the plane will be given.
 \param norm The normal Vector of plane which plane is based on
 \param pos  The position to which the plane is uniquely created
 \return plane with 'norm' and 'pos' as normal vector and delta creator.
 */
Plane::Plane(Vector3 norm, Vector3 pos)
{
	setPlane(norm, pos);
}

/*! This method prints the plane to the specified output stream in the
 format plane( norm(), delta: ).
 \param os output stream to which plane is written.
 */
void Plane::show(ostream& os) const
{
	os << "plane( norm(" << m_Normal << "), delta: " << m_Delta << ")";
}

/*! This method determines whether the given position lies inside the current
 plane.
 \param pos position which is checked whether it lies in plane
 \return true when 'pos' lies in the plane, false otherwise
 */
bool Plane::isInside(Vector3 pos) const
{
	float delta = (pos.x() * m_Normal.x() + pos.y() * m_Normal.y()
			+ pos.z() * m_Normal.z() );
	return (delta == -m_Delta);
}

/*! This method sets the normal vector and delta of the  current plane.
 \param newNormal The normal vector of the plane
 \param newPoint The point in the rectangle
 */
void Plane::setPlane(Vector3 newNormal, Vector3 newPoint)
{
	setPlaneNormal(newNormal);
	setPlaneDelta(
			-(newPoint.x() * m_Normal.x() + newPoint.y() * m_Normal.y()
					+ newPoint.z() * m_Normal.z() ));
}

/*! This method sets the normal vector of the plane
 \param newNormal The new normal vector of the plane
 \return true when update was successful
 */
bool Plane::setPlaneNormal(Vector3 newNormal)
{
	m_Normal = newNormal;
	return true;
}

/*! This method returns the normal vector of the plane
 \return normal vector of the plane
 */
Vector3 Plane::getPlaneNormal() const
{
	return m_Normal;
}

/*! This method sets the delta of the plane to origin
 \param newDelta The new delta of the plane to origin
 \return true when update was successful
 */
bool Plane::setPlaneDelta(float newDelta)
{
	m_Delta = newDelta;
	return true;
}

/*! This method returns the delta of plane to origin
 \return delta of the plane to the origin
 */
float Plane::getPlaneDelta() const
{
	return m_Delta;
}

/*****************************************************************************/
/********************** TESTING PURPOSES *************************************/
/*****************************************************************************/

/*
 #include <iostream>

 int main( void )
 {
 Plane p(Vector3(1, 0, 0, POLAR));
 p.show();

 return 0;
 }

 int main( void )
 {
 float dFirst = 1.0;
 float dRatio = 2.5;
 float dSum   = 63.4375;
 float dLength = 4.0;

 printf( "sum: %f\n", Geometry::getSumGeomSeries( dFirst, dRatio, dLength));
 printf( "length: %f\n", Geometry::getLengthGeomSeries( dFirst, dRatio, dSum));
 }

 int main( void )
 {
 Line l1(1,-1,3 );
 Line l2(1,-0.2,10 );
 Line l3 = Line::makeLineFromTwoPoints( Vector3(1,-1), Vector3(2,-2) );
 l3.show();
 cout << endl;
 l1.show();
 l2.show();
 l1.getIntersection( l2 ).show();
 }


 int main( void )
 {
 Line l( 1, -1, 0 );
 Vector3 s1, s2;
 int i = l.getCircleIntersectionPoints( Circle( Vector3(1,1),1) &s1,&s2 );
 printf( "number of solutions: %d\n", i );
 if( i == 2 )
 {
 cout << s1 << " " << s2 ;
 }
 else if( i == 1 )
 {
 cout << s1;
 }
 cout << "line: " << l;
 }

 int main( void )
 {
 Circle c11( Vector3( 10, 0 ), 10);
 Circle c12( Vector3( 40, 3 ), 40 );
 Circle c21( Vector3(  0,0 ), 5);
 Circle c22( Vector3(  3,0 ), 40 );

 Vector3 p1, p2;

 cout << c11.getIntersectionArea( c21 ) << endl;
 cout << c12.getIntersectionArea( c21 ) << endl;
 cout << c22.getIntersectionArea( c11 ) << endl;
 cout << c12.getIntersectionArea( c22 ) << endl;
 return 0;
 }

 int main( void )
 {
 cout << getBisectorTwoAngles( -155.3, 179.0 ) << endl;
 cout << getBisectorTwoAngles( -179.3, 179.0 ) << endl;
 }
 */

#endif
