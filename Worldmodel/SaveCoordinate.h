/*
 * SaveCoordinate.h
 *
 *  Created on: 2012-5-6
 *      Author: cit32
 */

#ifndef SAVECOORDINATE_H_
#define SAVECOORDINATE_H_
//#define SAVE_LENGTH 20
#include "../Utility/Geometry.h"
#include "../Utility/Types.h"
class SaveCoordinate
{
public:
	void SetAverageTrustLength(float atl){AverageTrustLength=atl;}
	SaveCoordinate();
	bool insert(Vector3 val);
	Vector3 GetAverageAcc();
	Vector3 GetLastVal();
	void clear();
	void init(Vector3 val);
	virtual ~SaveCoordinate();
	friend ostream& operator << ( ostream &os,SaveCoordinate v );
private :
	const static int SAVE_LENGTH=20;
	const static int AVERAGENUM=5;
	float AverageTrustLength;
	int flag;
	bool istart;//是否是一第个周期

	Vector3 sCoord[SAVE_LENGTH];
	Vector3 Acc[SAVE_LENGTH];
	void increaseFlag(){flag=(flag+1)%SAVE_LENGTH;}
	int getDecreaseflag(int num=1){return (flag-num+SAVE_LENGTH)%SAVE_LENGTH;}
};

#endif /* SAVECOORDINATE_H_ */
