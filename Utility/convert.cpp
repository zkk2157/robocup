#include "convert.h"
float Convert::ToFloat(string str)
{
	float temp;
	stringstream sstr; 
	sstr<<str; 
	sstr>>temp;
	return temp; 
}
int Convert::ToInt(string str)
{
	int temp;
	stringstream sstr; 
	sstr<<str; 
	sstr>>temp;
	return temp; 
}
string Convert::ToString(int val)
{
	string temp;
	stringstream sstr; 
	sstr<<val; 
	sstr>>temp;
	return temp; 
}
string Convert::ToString(int val,int num)
{
	string temp;
	stringstream sstr; 
	sstr<<val; 
	sstr>>temp;
	if(temp.length()<num)
	{
	      int ll=num-temp.length();
	      for(int i=0;i<ll;i++)
	      {
		temp.insert(0,1,'0');
	      }
	}
	
	return temp; 
}
string Convert::ToString(float val)
{
	string temp;
	stringstream sstr; 
	sstr<<val; 
	sstr>>temp;
	int point=temp.find(".");
	if(point<0)
	{
	      temp.append(".0");
	}
	return temp; 
}
string Convert::ToString(char val)
{
	string temp="";
	temp+=val;
	return temp;
}
string Convert::ToString(float val, int num, int decimalnum)
{
	string temp;
	stringstream sstr;
	sstr<<val;
	sstr>>temp;
	int point=temp.find(".");
//	cout<<"point::"<<point<<endl;
	if(point<0)
	{
	      temp.append(".0");
	      point=temp.find(".");
	}
//	cout<<"point::"<<point<<endl;
	int nowde=temp.length()-point-1;
//	cout<<"num::"<<num<<"   point::"<<point<<"   nowde::"<<nowde<<endl;
	if(num>point)
	{
	      int ll=num-point;
//	      cout<<"num::"<<num<<"   ll::"<<ll<<endl;
	      for(int i=0;i<ll;i++)
	      {
//		cout<<"inserting"<<endl;
		temp.insert(temp.begin(),1,'0');
	      }
	}
	if(nowde<decimalnum)
	{
	      int ll=decimalnum-nowde;
	      for(int i=0;i<ll;i++)
	      {
		temp.append("0");
	      }
	}
	return temp;
}
string Convert::ToStringWithsign(float val, int num, int decimalnum)
{
	bool isBz; //是否大于0
	if (val >= 0)
	{
		isBz = true;
	}
	else
	{
		isBz = false;
	}
	string temp;
	stringstream sstr;
	sstr << val;
	sstr >> temp;
	if (temp.at(0) == '-' || temp.at(0) == '+')
	{
		//	cout << "有符号数字" << endl;
		temp = temp.substr(1);
	}
	int point = temp.find(".");
	//cout << "point::" << point << endl;
	if (point < 0)
	{
		//	cout << "没有小数添加小数部分" << endl;
		temp.append(".0");
		point = temp.find(".");
	}
	//cout << "point::" << point << endl;
	int nowde = temp.length() - point - 1;
	//cout << "num::" << num << "   point::" << point << "   nowde::" << nowde
	//		<< endl;
	if (num > point)
	{
		int ll = num - 1 - point;
//	      cout<<"num::"<<num<<"   ll::"<<ll<<endl;
		for (int i = 0; i < ll; i++)
		{
//		cout<<"inserting"<<endl;
			temp.insert(temp.begin(), 1, '0');
		}
	}
	else
	{
		//整数部分大于最大值，则取最大值eg  Convert::ToString(200,2,3）=+9.000
		//cout<<"temp::"<<temp<<endl;
		string decistr = temp.substr(point, temp.length() - point);
		//cout<<"小数部分是：" <<decistr<<endl;
		//cout<<"大于设定的最大数"<<endl;
		temp = "1";
		int i = 0;
		for (; i < num - 1; i++)
		{
			temp.insert(temp.end(), 1, '0');
		}
		//cout<<"temp::"<<temp<<endl;
		string str = Convert::ToString(Convert::ToInt(temp) - 1);
		//cout<<"str::"<<str<<endl;
		temp = str + decistr;
		point = temp.find(".");
	}
	if (nowde < decimalnum)
	{
		int ll = decimalnum - nowde;
		for (int i = 0; i < ll; i++)
		{
			temp.append("0");
		}
	}
	else
	{
		point = temp.find(".");
		temp = temp.substr(0, point + 1 + decimalnum);
//		cout << "temp::" << temp << endl;
	}
	if (isBz)
	{
		temp.insert(temp.begin(), 1, '+');
	}
	else
	{
		temp.insert(temp.begin(), 1, '-');
	}
	return temp;
}
bool Convert::ToBool(string str)
{
	if(str=="true")
		return true;
	else
		return false;
}
float Convert::AngleTurn180(float val)
{
	float result;
	if (val >= 180)
	{
		result = val - 180;
	}
	else
	{
		result = val + 180;
	}
	return result;
}
Vector3 Convert::Turn180(Vector3 val)
{
	return Vector3(-val.x(), -val.y(), val.z());
}
