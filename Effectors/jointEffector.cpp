#include "jointEffector.h"

extern WorldModel wm;

Action JointEffector::HJHead_1Deg(float ang_RotToLeft)
{
	ang_RotToLeft = Deg2Rad(ang_RotToLeft);
	return HJHead_1Rad(ang_RotToLeft);
}

Action JointEffector::HJHead_2Deg(float ang_RotToLeft)
{
	ang_RotToLeft = Deg2Rad(ang_RotToLeft);
	return HJHead_2Rad(ang_RotToLeft);
}

Action JointEffector::HJLleg_1Deg(float ang_RotToLeft)
{
	ang_RotToLeft = Deg2Rad(ang_RotToLeft);
	return HJLleg_1Rad(ang_RotToLeft);
}

Action JointEffector::HJRleg_1Deg(float ang_RotToLeft)
{
	ang_RotToLeft = Deg2Rad(ang_RotToLeft);
	return HJRleg_1Rad(ang_RotToLeft);
}

Action JointEffector::HJLleg_2Deg(float ang_RotToLeft)
{
	ang_RotToLeft = Deg2Rad(ang_RotToLeft);
	return HJLleg_2Rad(ang_RotToLeft);
}

Action JointEffector::HJRleg_2Deg(float ang_RotToLeft)
{
	ang_RotToLeft = Deg2Rad(ang_RotToLeft);
	return HJRleg_2Rad(ang_RotToLeft);
}

Action JointEffector::HJLleg_3Deg(float ang_RotToLeft)
{
	ang_RotToLeft = Deg2Rad(ang_RotToLeft);
	return HJLleg_3Rad(ang_RotToLeft);
}

Action JointEffector::HJRleg_3Deg(float ang_RotToLeft)
{
	ang_RotToLeft = Deg2Rad(ang_RotToLeft);
	return HJRleg_3Rad(ang_RotToLeft);
}

Action JointEffector::HJLleg_4Deg(float ang_RotToLeft)
{
	ang_RotToLeft = Deg2Rad(ang_RotToLeft);
	return HJLleg_4Rad(ang_RotToLeft);
}

Action JointEffector::HJRleg_4Deg(float ang_RotToLeft)
{
	ang_RotToLeft = Deg2Rad(ang_RotToLeft);
	return HJRleg_4Rad(ang_RotToLeft);
}

Action JointEffector::HJLleg_5Deg(float ang_RotToLeft)
{
	ang_RotToLeft = Deg2Rad(ang_RotToLeft);
	return HJLleg_5Rad(ang_RotToLeft);

}

Action JointEffector::HJRleg_5Deg(float ang_RotToLeft)
{
	ang_RotToLeft = Deg2Rad(ang_RotToLeft);
	return HJRleg_5Rad(ang_RotToLeft);

}

Action JointEffector::HJLleg_6Deg(float ang_RotToLeft)
{
	ang_RotToLeft = Deg2Rad(ang_RotToLeft);
	return HJLleg_6Rad(ang_RotToLeft);

}

Action JointEffector::HJRleg_6Deg(float ang_RotToLeft)
{
	ang_RotToLeft = Deg2Rad(ang_RotToLeft);
	return HJRleg_6Rad(ang_RotToLeft);

}

Action JointEffector::HJLarm_1Deg(float ang_RotToLeft)
{
	ang_RotToLeft = Deg2Rad(ang_RotToLeft);
	return HJLarm_1Rad(ang_RotToLeft);
}

Action JointEffector::HJRarm_1Deg(float ang_RotToLeft)
{
	ang_RotToLeft = Deg2Rad(ang_RotToLeft);
	return HJRarm_1Rad(ang_RotToLeft);
}

Action JointEffector::HJLarm_2Deg(float ang_RotToLeft)
{
	ang_RotToLeft = Deg2Rad(ang_RotToLeft);
	return HJLarm_2Rad(ang_RotToLeft);
}

Action JointEffector::HJRarm_2Deg(float ang_RotToLeft)
{
	ang_RotToLeft = Deg2Rad(ang_RotToLeft);
	return HJRarm_2Rad(ang_RotToLeft);
}

Action JointEffector::HJLarm_3Deg(float ang_RotToLeft)
{
	ang_RotToLeft = Deg2Rad(ang_RotToLeft);
	return HJLarm_3Rad(ang_RotToLeft);
}

Action JointEffector::HJRarm_3Deg(float ang_RotToLeft)
{
	ang_RotToLeft = Deg2Rad(ang_RotToLeft);
	return HJRarm_3Rad(ang_RotToLeft);
}

Action JointEffector::HJLarm_4Deg(float ang_RotToLeft)
{
	ang_RotToLeft = Deg2Rad(ang_RotToLeft);
	return HJLarm_4Rad(ang_RotToLeft);
}

Action JointEffector::HJRarm_4Deg(float ang_RotToLeft)
{
	ang_RotToLeft = Deg2Rad(ang_RotToLeft);
	return HJRarm_4Rad(ang_RotToLeft);
}

Action JointEffector::HJHead_1Rad(float ang_RotToLeft)
{
//	//cout<<"HJHead_1Rad::"<<ang_RotToLeft<<endl;
	stringstream ss("");

	stringstream tempString("");
	tempString << ang_RotToLeft;
	//cout<<"tempString::"<<tempString<<endl;
	ss << "(he1 " << InterceptData(tempString.str(), 3) << ")";
//	//cout<<"ss::"<<ss<<endl;
	//ss<<"( he1 "<<ang_RotToLeft<<" )";
	return ss.str();
}

Action JointEffector::HJHead_2Rad(float ang_RotToLeft)
{
	//cout<<"HJHead_2Rad::"<<ang_RotToLeft<<endl;
	stringstream ss("");

	stringstream tempString("");
	tempString << ang_RotToLeft;
	//cout<<"tempString::"<<tempString<<endl;
	ss << "(he2 " << InterceptData(tempString.str(), 3) << ")";
	//ss<<"( he2 "<<ang_RotToLeft<<" )";
	return ss.str();
}

Action JointEffector::HJLleg_1Rad(float ang_RotToLeft)
{
	stringstream ss("");

	stringstream tempString("");
	tempString << ang_RotToLeft;
	//cout<<"tempString::"<<tempString<<endl;
	ss << "(lle1 " << InterceptData(tempString.str(), 3) << ")";
	//ss<<"( lle1 "<<ang_RotToLeft<<" )";
	return ss.str();
}

Action JointEffector::HJRleg_1Rad(float ang_RotToLeft)
{
	stringstream ss("");

	stringstream tempString("");
	tempString << ang_RotToLeft;
	//cout<<"tempString::"<<tempString<<endl;
	ss << "(rle1 " << InterceptData(tempString.str(), 3) << ")";
	//ss<<"( rle1 "<<ang_RotToLeft<<" )";
	return ss.str();
}

Action JointEffector::HJLleg_2Rad(float ang_RotToLeft)
{
	stringstream ss("");

	stringstream tempString("");
	tempString << ang_RotToLeft;
	//cout<<"tempString::"<<tempString<<endl;
	ss << "(lle2 " << InterceptData(tempString.str(), 3) << ")";
	//ss<<"( lle2 "<<ang_RotToLeft<<" )";
	return ss.str();
}

Action JointEffector::HJRleg_2Rad(float ang_RotToLeft)
{
	stringstream ss("");

	stringstream tempString("");
	tempString << ang_RotToLeft;
	//cout<<"tempString::"<<tempString<<endl;
	ss << "(rle2 " << InterceptData(tempString.str(), 3) << ")";
	//ss<<"( rle2 "<<ang_RotToLeft<<" )";
	return ss.str();
}

Action JointEffector::HJLleg_3Rad(float ang_RotToLeft)
{
	stringstream ss("");

	stringstream tempString("");
	tempString << ang_RotToLeft;
	//cout<<"tempString::"<<tempString<<endl;
	ss << "(lle3 " << InterceptData(tempString.str(), 3) << ")";
	//ss<<"( lle3 "<<ang_RotToLeft<<" )";
	return ss.str();
}

Action JointEffector::HJRleg_3Rad(float ang_RotToLeft)
{
	stringstream ss("");

	stringstream tempString("");
	tempString << ang_RotToLeft;
	//cout<<"tempString::"<<tempString<<endl;
	ss << "(rle3 " << InterceptData(tempString.str(), 3) << ")";
	//ss<<"( rle3 "<<ang_RotToLeft<<" )";
	return ss.str();
}

Action JointEffector::HJLleg_4Rad(float ang_RotToLeft)
{
	stringstream ss("");

	stringstream tempString("");
	tempString << ang_RotToLeft;
	//cout<<"tempString::"<<tempString<<endl;
	ss << "(lle4 " << InterceptData(tempString.str(), 3) << ")";
	//ss<<"( lle4 "<<ang_RotToLeft<<" )";
	return ss.str();
}

Action JointEffector::HJRleg_4Rad(float ang_RotToLeft)
{
	stringstream ss("");

	stringstream tempString("");
	tempString << ang_RotToLeft;
	//cout<<"tempString::"<<tempString<<endl;
	ss << "(rle4 " << InterceptData(tempString.str(), 3) << ")";
	//ss<<"( rle4 "<<ang_RotToLeft<<" )";
	return ss.str();
}

Action JointEffector::HJLleg_5Rad(float ang_RotToLeft)
{
	stringstream ss("");

	stringstream tempString("");
	tempString << ang_RotToLeft;
	//cout<<"tempString::"<<tempString<<endl;
	ss << "(lle5 " << InterceptData(tempString.str(), 3) << ")";
	//ss<<"( lle5 "<<ang_RotToLeft<<" )";
	return ss.str();
}

Action JointEffector::HJRleg_5Rad(float ang_RotToLeft)
{
	stringstream ss("");

	stringstream tempString("");
	tempString << ang_RotToLeft;
	//cout<<"tempString::"<<tempString<<endl;
	ss << "(rle5 " << InterceptData(tempString.str(), 3) << ")";
	//ss<<"( rle5 "<<ang_RotToLeft<<" )";
	return ss.str();
}

Action JointEffector::HJLleg_6Rad(float ang_RotToLeft)
{
	stringstream ss("");

	stringstream tempString("");
	tempString << ang_RotToLeft;
	//cout<<"tempString::"<<tempString<<endl;
	ss << "(lle6 " << InterceptData(tempString.str(), 3) << ")";
	//ss<<"( lle6 "<<ang_RotToLeft<<" )";
	return ss.str();
}

Action JointEffector::HJRleg_6Rad(float ang_RotToLeft)
{
	stringstream ss("");

	stringstream tempString("");
	tempString << ang_RotToLeft;
	//cout<<"tempString::"<<tempString<<endl;
	ss << "(rle6 " << InterceptData(tempString.str(), 3) << ")";
	//ss<<"( rle6 "<<ang_RotToLeft<<" )";
	return ss.str();
}

Action JointEffector::Say(string saymessage)
{
	stringstream ss("");
	ss << "(say " << saymessage << ")";
	return ss.str();
}

///-=
Action JointEffector::HJLarm_1Rad(float ang_RotToLeft)
{
	stringstream ss("");

	stringstream tempString("");
	tempString << ang_RotToLeft;
	//cout<<"tempString::"<<tempString<<endl;
	ss << "(lae1 " << InterceptData(tempString.str(), 3) << ")";
	//ss<<"( lae1 "<<ang_RotToLeft<<" )";
	return ss.str();
}

Action JointEffector::HJRarm_1Rad(float ang_RotToLeft)
{
	stringstream ss("");

	stringstream tempString("");
	tempString << ang_RotToLeft;
	//cout<<"tempString::"<<tempString<<endl;
	ss << "(rae1 " << InterceptData(tempString.str(), 3) << ")";
	//ss<<"( rae1 "<<ang_RotToLeft<<" )";
	return ss.str();
}

Action JointEffector::HJLarm_2Rad(float ang_RotToLeft)
{
	stringstream ss("");

	stringstream tempString("");
	tempString << ang_RotToLeft;
	//cout<<"tempString::"<<tempString<<endl;
	ss << "(lae2 " << InterceptData(tempString.str(), 3) << ")";
	//ss<<"( lae2 "<<ang_RotToLeft<<" )";
	return ss.str();
}

Action JointEffector::HJRarm_2Rad(float ang_RotToLeft)
{
	stringstream ss("");

	stringstream tempString("");
	tempString << ang_RotToLeft;
	//cout<<"tempString::"<<tempString<<endl;
	ss << "(rae2 " << InterceptData(tempString.str(), 3) << ")";
	//ss<<"( rae2 "<<ang_RotToLeft<<" )";
	return ss.str();
}

Action JointEffector::HJLarm_3Rad(float ang_RotToLeft)
{
	stringstream ss("");

	stringstream tempString("");
	tempString << ang_RotToLeft;
	//cout<<"tempString::"<<tempString<<endl;
	ss << "(lae3 " << InterceptData(tempString.str(), 3) << ")";
//	ss<<"( lae3 "<<ang_RotToLeft<<" )";
	return ss.str();
}

Action JointEffector::HJRarm_3Rad(float ang_RotToLeft)
{
	stringstream ss("");

	stringstream tempString("");
	tempString << ang_RotToLeft;
	//cout<<"tempString::"<<tempString<<endl;
	ss << "(rae3 " << InterceptData(tempString.str(), 3) << ")";
	//ss<<"( rae3 "<<ang_RotToLeft<<" )";
	return ss.str();
}

Action JointEffector::HJLarm_4Rad(float ang_RotToLeft)
{
	stringstream ss("");

	stringstream tempString("");
	tempString << ang_RotToLeft;
	//cout<<"tempString::"<<tempString<<endl;
	ss << "(lae4 " << InterceptData(tempString.str(), 3) << ")";
//	ss<<"( lae4 "<<ang_RotToLeft<<" )";
	return ss.str();
}

Action JointEffector::HJRarm_4Rad(float ang_RotToLeft)
{
	stringstream ss("");

	stringstream tempString("");
	tempString << ang_RotToLeft;
	//cout<<"tempString::"<<tempString<<endl;
	ss << "(rae4 " << InterceptData(tempString.str(), 3) << ")";

	//ss<<"( rae4 "<<ang_RotToLeft<<" )";
	return ss.str();
}

float JointEffector::Deg2Rad(float angle)
{
	return angle * PI / 180;
}

float JointEffector::Rad2Deg(float radian)
{
	return radian * 180 / PI;
}

Action JointEffector::InterceptData(string data, int keepNumberAfterBasePoint)
{
#if 0
	if(wm.IsFallDown() == true)
	{
		keepNumberAfterBasePoint=7;
		++keepNumberAfterBasePoint;
		string::size_type pointer=data.find('.');
		if(pointer <= 20)
		data=data.substr(0,pointer+keepNumberAfterBasePoint);
	}
	///rint(floatData*1000)*0.001;//need :#include <cmath>
#endif
	return data;
}

