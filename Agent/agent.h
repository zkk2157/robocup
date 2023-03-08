#ifndef AGENT_H
#define AGENT_H

#include "../Stdafx.h"
#include "../Connection/Tcpconnection.h"
using namespace std;

/**
 \file agent.h
 @author Leisland <leisland@163.com>
 */

/**
 \class Agent is to manage the initial data and basic data of agent,it contains agent create and set 
 beam coordinate、team name、number of player and etc.(editor:leisland date:2008-8-20)
 */

class Agent
{
public:
	/**construct function will set the default parameters of agent*/
	Agent();

	/**send the create command to server,and the server will construct the agent according to a scene description file*/
	string CreateAgent();
	string CreateAgent1();
	string CreateAgent2();
	string CreateAgent3();
	string CreateAgent4();


	/**this function contains the main loop of the whole code,it will get the message from server and send the message to server continuous*/
	void Run();

	/**when the game is over,the code will call the function Done() to close the connection between server and client*/
	void Done();
	void Openlogs();
	void Closelogs();
	/**set the beam coordinate of agent*/
	void SetBeamPos(string str);

	/**set the team name of agent*/
	void SetTeamName(string str);

	/**set the number of agent*/
	void SetPlayerID(string str);

	/**set the delay time of main loop*/
	void SetDelayTime(string str);
	//*set the ip of server*/
	void setport(int temp)
	{
		this->Port=temp;
	}
	void setHostIP(string ip)
	{
		Host = ip;
	}

	/**get the agent's beam coordinate*/
	Vector3 GetBeamPos();

	/**get the agent's team name*/
	string GetTeamName();
		float GetHIP();
		float GetTHIGH();
		float GetSHANK();
		float GetBODYHEIGHT();
		int GetType();
	/**get the agent's number*/
	int GetPlayID();

	/**get the initial parameter of agent*/
	string GetInitParameter();

	/**get beam parameter of agent*/
	string GetBeamParameter(OurBallFormKind nowMyBeam);
	bool connect();
	/**convert string to int type*/
	int ConvertStrToInt(string str);

	void jointRecordOpen(); ///lr

	void jointRecordClose(); ///lr
	Vector3 GetNowBeam(int num, OurBallFormKind nowMyBeamTI);
private:
	int timeval_subtract(struct timeval* result, struct timeval* x,
			struct timeval* y);

	/**convert string to float type*/
	float ConvertStrToFloat(string str);

	/**print the init data onto the terminal*/
	void OutputInitData();

private:
	/**team name of agent*/
	string teamName;

	/**play number of agent*/
	int playerID;
	int type;
		float HIP;
		float THIGH;
		float SHANK;
		float BODYHEIGHT;
	/**beam coordinate of agent*/
	Vector3 beamPos;

	/**delay time of main loop*/
	float delay;
	string Host;
	int Port;
	/**the counter of sended message*/
	int sendMessageCounter;

	/**the flag of send init message*/
	bool finishedSendInitMessage, beam;
	Communit * server;
	/***/
	bool haveSetedBeamPos;

};
#endif
