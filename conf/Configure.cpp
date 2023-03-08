/*
 * Configure.cpp
 *
 *  Created on: 2012-3-13
 *      Author: cit
 */

#include "Configure.h"
#define LENGTH 100

Configure::Configure()
{
	// TODO Auto-generated constructor stub
	slideTackle=true;
}
void Configure::OpenConf()
{
	fileName = "conf/conf.conf";
	string word;
	//cout << ".........sada" << endl;
	ifstream fin(fileName.c_str());
	char ch;
	while (fin.get(ch))
	{
		////cout<<ch<<endl;
		if (ch == '\n')
		{

			int mid = word.find(":");
			string key = word.substr(0, mid);
			string val = word.substr(mid + 1);

			//cout << key << endl << Convert::ToBool(val) << endl;
			if (key == "RightAttack")
			{
				RightAttack = Convert::ToBool(val);
				//cout<<"RightAttack::"<<RightAttack<<endl;
			}
			if (key == "DrawerBug")
			{
				DrawerBug = Convert::ToBool(val);
				//cout<<"DrawerBug::"<<DrawerBug<<endl;
			}
			if(key=="GoailDrawer")
			{
				GoailDrawer=Convert::ToBool(val);
				//cout<<"GoailDrawer::"<<GoailDrawer<<endl;
			}
			if(key=="slideTackle")
			{
				slideTackle==Convert::ToBool(val);
			}
			word = "";
		}
		else
		{
			if (ch == '#')
			{
				//cout<<"endl conf file"<<endl;
				break;
			}
			word.insert(word.end(), ch);
		}
	}

	fin.close();
	//cout<<"endl conf Configure"<<endl;
}
Configure::~Configure()
{
	// TODO Auto-generated destructor stub
}

