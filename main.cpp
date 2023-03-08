#include "Stdafx.h"

///#include "hearandsay.h"           ///czg

using namespace std;
using namespace boost;
using namespace MonitorDraw;
Strategy behavior;
Agent agent;
Perceptor messageParser;
WorldModel wm;
JointEffector mp;

Configure CITConf;


Logger myLoggerSend("asd");
Logger myLogger("WalkLog.log");
Logger myZMPLogger("ZMPLog.log");
Logger myCOMLogger("COMLog.log");

Logger myRLEG_J1Logger("RLEG_J1Logger.log");
Logger myRLEG_J2Logger("RLEG_J2Logger.log");
Logger myRLEG_J3Logger("RLEG_J3Logger.log");
Logger myRLEG_J4Logger("RLEG_J4Logger.log");
Logger myRLEG_J5Logger("RLEG_J5Logger.log");

Logger myLLEG_J1Logger("LLEG_J1Logger.log");
Logger myLLEG_J2Logger("LLEG_J2Logger.log");
Logger myLLEG_J3Logger("LLEG_J3Logger.log");
Logger myLLEG_J4Logger("LLEG_J4Logger.log");
Logger myLLEG_J5Logger("LLEG_J5Logger.log");

MDrawer CITMDrawer;

/**function PrintGreeting():print the greeting message in the terminal*/
void PrintGreeting()
{
#if 1
	cout << endl << endl;
	cout << "\t";
	cout << "*****************************************************" << endl;
	for (int i = 1; i <= 2; ++i)
	{
		cout << "\t";
		cout << "*                                                   *" << endl;
	}
	cout << "\t";
	cout << "*    >>>>>>>>>>>>>> CIT2012 Start <<<<<<<<<<<<<<    *" << endl;
	for (int i = 1; i <= 2; ++i)
	{
		cout << "\t";
		cout << "*                                                   *" << endl;
	}
	cout << "\t";
	cout << "*****************************************************" << endl;

#endif

}

/**function PrintHelp():output the help options to tell you how to input the right parameters*/
void PrintHelp()
{
	///cout << "usage: CIT3D [options]" << endl;
	///cout << "options:" << endl;
	///cout << " --help      prints this message." << endl;
	///cout << " --host=IP   IP of the server." << endl;
	///cout << " --Unum=unum   unum of the agent." << endl;
	///cout << " --beam=Pos    Pos for start game."<<endl;
}

/**function ReadOptions():read the parameters from terminal*/
void ReadOptions(int argc, char* argv[])
{
	//cout<<"ReadOptions::"<<endl;
	for (int i = 0; i < argc; i++)
	{
		//cout<<"i::"<<argv[i]<<endl;
		if (strcmp(argv[i], "--help") == 0) //read the help option
		{
			PrintHelp(); //print the help message
			break;
		}
		else if (strncmp(argv[i], "--host=", 7) == 0) //read the IP of server
		{
			string tmp = argv[i];
			if (tmp.length() <= 7) // minimal sanity check
			{
				PrintHelp(); //print the help message
				break;
			}
		   std::cout<<tmp<<endl;
			agent.setHostIP(tmp.substr(7));
		}
		else if (strncmp(argv[i], "--Unum=", 7) == 0) //read the number of agent
		{
			string tmp = argv[i];
			if (tmp.length() <= 7)
			{
				PrintHelp(); //print the help message
				break;
			}

			agent.SetPlayerID(tmp.substr(7));
		}
		else if (strncmp(argv[i], "--beam=", 7) == 0) //read the beam parameter
		{
			string tmp = argv[i];
			if (tmp.length() <= 7)
			{
				PrintHelp(); //print the help message
				break;
			}
			string pos = tmp.substr(7);

			agent.SetBeamPos(pos);
		}
		else if (strncmp(argv[i],"--port=",7)==0)
		{
			int temp=0;
			string tmp=argv[i];
			string rr=tmp.substr(7);
			temp=Convert::ToInt(rr);
			cout<<tmp<<endl;
			agent.setport(temp);
		}
		else if (strncmp(argv[i], "--team", 6) == 0) //read teamname section
		{
			string tmp = argv[i];
			if (tmp.length() <= 7) // minimal sanity check
			{
				PrintHelp(); //print the help message
			}
			agent.SetTeamName(tmp.substr(7));
		}
		else if (strncmp(argv[i], "--delay=", 8) == 0) //read the data of delay time
		{
			string tmp = argv[i];
			if (tmp.length() <= 8)
			{
				PrintHelp(); //print the help message
				break;
			}
			agent.SetDelayTime(tmp.substr(8));
		}
		else if (strncmp(argv[i], "--striker", 9) == 0) //read the data of delay time
		{
			string tmp = argv[i];
			if (tmp.length() <= 8)
			{
				PrintHelp(); //print the help message
				break;
			}
			agent.SetDelayTime(tmp.substr(8));
			behavior.SetWhetherStriker(true);
		}
	}
	//cout<<"end ReadOptions::"<<endl;
}

/**function main():the entrance of the whole code and also the exit of code*/
int main(int argc, char* argv[])
{
//	cout << "start" << endl;
	CITConf.OpenConf();
	cout<<"+OK+"<<endl;
//	cout << "endl conf" << endl;
	//PrintGreeting(); //print the greeting message
	CITMDrawer.OpenConnection();
	ReadOptions(argc, argv); //get the parameters from the terminal

	if (!agent.connect()) //make a connection to soccer server
	{
		return 1;
	}
	agent.Run(); //the main run loop

	agent.Done(); //colse the coonection to soccer server
	CITMDrawer.CloseConnection();
	return 0;
}

