/*
 * CITMath.cpp
 *
 *  Created on: 2012-5-9
 *      Author: cit32
 */

#include "CITMath.h"
using namespace std;
CITMath::CITMath()
{
	// TODO Auto-generated constructor stub

}
//void CITMath::sort(SPlayerDis va[], int num)
//{
//	for (int k = 0; k < num; k++)
//	{
//		for (int p = 0; p < num - 1 - k; p++)
//		{
//			if (va[p].dis > va[p + 1].dis)
//			{
//				SPlayerDis temp = va[p];
//				va[p] = va[p + 1];
//				va[p + 1] = temp;
//			}
//		}
//	}
//
//}
//float CITMath::GetTwoPointWithXangle(Vector2 Point1, Vector2 Point2)
//{
//	return GetTwoPointWithXangle(Vector3(Point1.x(), Point1.y(), 0),
//			Vector3(Point2.x(), Point2.y(), 0));
//}
float CITMath::GetTwoPointWithXangle(Vector3 Point1, Vector3 Point2) //注意这是矢量Point1----->Point2的矢量
{
	Vector3 Shiliang = Point2 - Point1;
	//cout<<"Point1::"<<Point1<<endl;
	//cout<<"Point2::"<<Point2<<endl;
	//cout<<"Shiliang.y() ::"<<Shiliang.y() <<endl;
	//cout<<"Shiliang.xymod()"<<Shiliang.xymod()<<endl;
	//cout<<"acos(Shiliang.y() / Shiliang.xymod())::"<<acos(Shiliang.y() / Shiliang.xymod())<<endl;
	float res = Rad2Deg(acos(Shiliang.x() / Shiliang.xymod()));
//	cout << "000res::" << res << endl;
	if (Shiliang.x() > 0 && Shiliang.y() < 0)
	{
		res = res - 180;
//		cout << "		if(Shiliang.x()>0&&Shiliang.y()<0)" << res << endl;
	}
	else if (Shiliang.x() < 0 && Shiliang.y() < 0)
	{
		res = -res;
//		cout << "		else if(Shiliang.x()<0&&Shiliang.y()<0)" << res << endl;
	}
//	cout << "Rad2Deg(acos(Shiliang.y() / Shiliang.xymod()))::" << res << endl;
	return res;
}
CITMath::~CITMath()
{
	// TODO Auto-generated destructor stub
}

