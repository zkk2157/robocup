#ifndef MESSAGEPROCESSING_H
#define MESSAGEPROCESSING_H
/**
\file messageprocessing.h
@author CCH
*/

#include <sstream>
#include "../Stdafx.h"

class JointEffector
{
	public:
		/*----------------action system -- angle according to degree-------------------------*/
	/////////////Head

		Action HJHead_1Deg  (float ang_RotToLeft=0);
		Action HJHead_2Deg  (float ang_RotToLeft=0);

	/////////////Leg

		Action HJLleg_1Deg  (float ang_RotToLeft = 0);
		Action HJRleg_1Deg  (float ang_RotToLeft = 0);
	
		Action HJLleg_2Deg  (float ang_RotToLeft = 0);
		Action HJRleg_2Deg  (float ang_RotToLeft = 0);
	
		Action HJLleg_3Deg  (float ang_RotToLeft = 0);
		Action HJRleg_3Deg  (float ang_RotToLeft = 0);

		Action HJLleg_4Deg  (float ang_RotToLeft=0);
		Action HJRleg_4Deg  (float ang_RotToLeft=0);
	
		Action HJLleg_5Deg  (float ang_RotToLeft = 0);
		Action HJRleg_5Deg  (float ang_RotToLeft = 0);
	
		Action HJLleg_6Deg  (float ang_RotToLeft = 0);
		Action HJRleg_6Deg  (float ang_RotToLeft = 0);

	////////////////arm

		Action HJLarm_1Deg  (float ang_RotToLeft = 0);
		Action HJRarm_1Deg  (float ang_RotToLeft = 0);

		Action HJLarm_2Deg  (float ang_RotToLeft = 0);
		Action HJRarm_2Deg  (float ang_RotToLeft = 0);

		Action HJLarm_3Deg  (float ang_RotToLeft = 0);
		Action HJRarm_3Deg  (float ang_RotToLeft = 0);

		Action HJLarm_4Deg  (float ang_RotToLeft = 0);
		Action HJRarm_4Deg  (float ang_RotToLeft = 0);
	
		/*---------------------------end Deg----------------------------*/

		/*----------------action system -- angle according to radian-------------------------*/

	/////////////Head

		Action HJHead_1Rad  (float ang_RotToLeft = 0);
		Action HJHead_2Rad  (float ang_RotToLeft = 0);

	/////////////Leg
	
		Action HJLleg_1Rad  (float ang_RotToLeft = 0);
		Action HJRleg_1Rad  (float ang_RotToLeft = 0);

		Action HJLleg_2Rad  (float ang_RotToLeft = 0);
		Action HJRleg_2Rad  (float ang_RotToLeft = 0);

		Action HJLleg_3Rad  (float ang_RotToLeft = 0);
		Action HJRleg_3Rad  (float ang_RotToLeft = 0);

		Action HJLleg_4Rad  (float ang_RotToLeft=0);
		Action HJRleg_4Rad  (float ang_RotToLeft=0);
	
		Action HJLleg_5Rad  (float ang_RotToLeft = 0);
		Action HJRleg_5Rad  (float ang_RotToLeft = 0);

		Action HJLleg_6Rad  (float ang_RotToLeft = 0);
		Action HJRleg_6Rad  (float ang_RotToLeft = 0);

	////////////////arm

		Action HJLarm_1Rad  (float ang_RotToLeft = 0);
		Action HJRarm_1Rad  (float ang_RotToLeft = 0);
	
		Action HJLarm_2Rad  (float ang_RotToLeft = 0);
		Action HJRarm_2Rad  (float ang_RotToLeft = 0);

		Action HJLarm_3Rad  (float ang_RotToLeft = 0);
		Action HJRarm_3Rad  (float ang_RotToLeft = 0);
	
		Action HJLarm_4Rad  (float ang_RotToLeft = 0);
		Action HJRarm_4Rad  (float ang_RotToLeft = 0);

		Action Say  (string saymessage );

		/*------------------------------end Rad-------------------------*/
			
		float Deg2Rad( float angle);
		float Rad2Deg(float radian);
		
		Action InterceptData(string data,int keepNumberAfterBasePoint);

	private:
};
#endif
