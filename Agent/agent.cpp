#include "agent.h"

extern Perceptor messageParser;
extern WorldModel wm;
extern Strategy behavior;
extern Logger myLogger;
extern Logger myLoggerSend;
extern Logger myZMPLogger;
extern Logger myCOMLogger;
CITPlayer player;
extern Logger myRLEG_J1Logger;
extern Logger myRLEG_J2Logger;
extern Logger myRLEG_J3Logger;
extern Logger myRLEG_J4Logger;
extern Logger myRLEG_J5Logger;

extern Logger myLLEG_J1Logger;
extern Logger myLLEG_J2Logger;
extern Logger myLLEG_J3Logger;
extern Logger myLLEG_J4Logger;
extern Logger myLLEG_J5Logger;
extern BasicMotion basicMotion;
#define JOINT_RECORD false
extern Configure CITConf;
extern NewWalk newWalk; ///lr
Agent::Agent()
{
	teamName="Sainty3D";
	playerID=1;
	beamPos=Vector3(-3,0,0);
	delay=0;
	sendMessageCounter=0;
	finishedSendInitMessage=false;
	beam=false;
	Host="127.0.0.1";
	Port=3100;
	haveSetedBeamPos=false;
}
bool Agent::connect()
{
	server=new TcpConnection(Host,Port);  /// connect to server by tcp

	if(!server->ConnectToServer())
	{
	//	cout<<"connection fail"<<endl;
		return false;
	}
	if(playerID!=4 && playerID!=3 && playerID!=8 && playerID!=6)
				server->PutMessage(CreateAgent());//1
		if((playerID==6) || (playerID==8) )
			server->PutMessage(CreateAgent1());//0
		if((playerID==4) ||  (playerID==3))
				server->PutMessage(CreateAgent4());
	cout<<"end connect"<<endl;
	return true;
}
string Agent::CreateAgent()
{     // if(wm.GetMyNumber()==2)
	type=0;

    HIP=0.055;
    THIGH=0.135;
    SHANK=0.11;
    BODYHEIGHT=0.24;
	return "(scene rsg/agent/nao/nao_hetero.rsg 0)";
	//return "(scene rsg/agent/nao/nao.rsg)";//nao model

    // 	return "(scene rsg/agent/soccerbot056.rsg)";
//	return "(scene rsg/agent/soccerbot058/soccerbot.rsg)";
}

string Agent::CreateAgent1()
{     // if(wm.GetMyNumber()==2)
	type=1;
	HIP=0.055;
	THIGH=0.15332;
	SHANK=0.12832;
	BODYHEIGHT=0.275;
	return "(scene rsg/agent/nao/nao_hetero.rsg 1)";
	//return "(scene rsg/agent/nao/nao.rsg)";//nao model

    // 	return "(scene rsg/agent/soccerbot056.rsg)";
//	return "(scene rsg/agent/soccerbot058/soccerbot.rsg)";
}
string Agent::CreateAgent2()
{     // if(wm.GetMyNumber()==2)
	type=2;

    HIP=0.055;
    THIGH=0.135;
    SHANK=0.11;
    BODYHEIGHT=0.24;
	return "(scene rsg/agent/nao/nao_hetero.rsg 2)";
	//return "(scene rsg/agent/nao/nao.rsg)";//nao model

    // 	return "(scene rsg/agent/soccerbot056.rsg)";
//	return "(scene rsg/agent/soccerbot058/soccerbot.rsg)";
}
string Agent::CreateAgent3()
{     // if(wm.GetMyNumber()==2)
	type=3;
	HIP=0.072954;
	THIGH=0.162868424;
	SHANK=0.137868424;
	BODYHEIGHT=0.29;
	return "(scene rsg/agent/nao/nao_hetero.rsg 3)";
	//return "(scene rsg/agent/nao/nao.rsg)";//nao model

    // 	return "(scene rsg/agent/soccerbot056.rsg)";
//	return "(scene rsg/agent/soccerbot058/soccerbot.rsg)";
}
string Agent::CreateAgent4()
{     // if(wm.GetMyNumber()==2)
	type=4;

    HIP=0.055;
    THIGH=0.135;
    SHANK=0.11;
    BODYHEIGHT=0.24;
	return "(scene rsg/agent/nao/nao_hetero.rsg 4)";
	//return "(scene rsg/agent/nao/nao.rsg)";//nao model

    // 	return "(scene rsg/agent/soccerbot056.rsg)";
//	return "(scene rsg/agent/soccerbot058/soccerbot.rsg)";
}
float Agent::GetHIP()
{
	return HIP;
}
float Agent::GetTHIGH()
{
	return  THIGH;
}
float Agent::GetSHANK()
{
	return  SHANK;
}
float Agent::GetBODYHEIGHT()
{
	return  BODYHEIGHT;
}
int Agent::GetType()
{
	return type;
}
void Agent::SetBeamPos(string str)
{
	char *tmp,*substr;
	const char delimiters[]=",";
	float Postmp[3];
	int t = 0;
	tmp = (char*)str.c_str();
	while(substr!=NULL)
	{
		substr = strsep(&tmp,delimiters);
		
		Postmp[t]=ConvertStrToFloat(substr);
		t=t+1;
		if (t==3)
		{
			beamPos = Vector3(Postmp[0],Postmp[1],Postmp[2]);
			break;
		}
	}
	haveSetedBeamPos=true;
}
void Agent::SetTeamName(string str)
{
	teamName=str;
}
void Agent::SetPlayerID(string str)
{
	playerID=ConvertStrToInt(str);
//	cout<<"playerid"<<playerID<<endl;
	if( haveSetedBeamPos==false )
	{
		beamPos=GetNowBeam(playerID,emOurBallForm);
	}
}
void Agent::SetDelayTime(string str)
{
	delay=ConvertStrToFloat(str);
}
Vector3 Agent::GetBeamPos()
{
	return beamPos;
}
string Agent::GetTeamName()
{
	return teamName;
}
int Agent::GetPlayID()
{
	return playerID;
}
string Agent::GetInitParameter()
{
	stringstream ss("");
	ss<<"(init (unum "<<playerID<<")(teamname "<<teamName<<"))";
	return ss.str();
}
string Agent::GetBeamParameter(OurBallFormKind nowMyBeam)
{
	beamPos=GetNowBeam(playerID,nowMyBeam);
//	wm.initMyCoordinate(beamPos);
	stringstream ss("");
	if(wm.GetMyNumber()==2)
	{
		beamPos.y(beamPos.y()+0.02);
		beamPos.x(beamPos.x()-0.04);
	}
	ss<<"(beam "<<beamPos.x()<<" "<<beamPos.y()<<" "<<beamPos.z()<<")";
//	ss<<basicMotion.InitStandUpPose();
	return ss.str();
}
void Agent::OutputInitData()
{
#if 1
	cout<<"\t"<<"team:"<<teamName<<" "<<"playerID:"<<playerID<<" time delay:"<<delay;
	cout<<" beam:"<<"( "<<beamPos.x()<<" , "<<beamPos.y()<<" , "<<beamPos.z()<<" )"<<endl;
	cout<<endl<<"\t"<<"running......"<<endl<<endl;
#endif
}
void Agent::Openlogs()
{
	myLogger.SetEnable(false);
	myLoggerSend.SetEnable(false);
	int myNumber=GetPlayID();

	myLogger.OpenFileStream(Convert::ToString(myNumber)+"Get.log");
	myLoggerSend.OpenFileStream(Convert::ToString(myNumber)+"Send.log");

	myZMPLogger.SetEnable(false);
	myZMPLogger.OpenFileStream();

	myCOMLogger.SetEnable(false);
	myCOMLogger.OpenFileStream();

	jointRecordOpen();///lr
}
void Agent::Closelogs()
{

	myLogger.CloseFileStream();

	myZMPLogger.CloseFileStream();

	myCOMLogger.CloseFileStream();

	jointRecordClose();///lr
}
void Agent::Run()//重点
{
	Openlogs();
	OutputInitData();
	string msg;
	string ss="";

	cout<<"CITConf::"<<CITConf.RightAttack<<endl;

	struct timeval start,stop,diff;

	while( server->GetMessage(msg) )
	{	
		cout<<"------------------------------------"<<endl;//this part continue running
 		//cout<<"message:"<<msg<<endl;
		string name="Sainty3D";
		myLogger.DoLogByFormatting(name,"::%s",msg.c_str());
		gettimeofday(&start,0);
		string input(msg);
		messageParser.ParseMsg(input);// 解析信息
		wm.UpdateWorldModel();
//		cout<<"updated..."<<endl;
		if(finishedSendInitMessage== false)
		{
			TTeamIndex 	nowMyBeamTI=wm.GetMyTeamIndex();
//			cout<<"sendMessageCounter::"<<sendMessageCounter<<endl;
			if(sendMessageCounter ==0)
			{
				ss=GetInitParameter();
				sendMessageCounter++;
			}
			if(nowMyBeamTI!=TI_NONE)//i find it just need to do in different times is OK,no need to use 10 or 15 circle tims to control it
			{
				if(nowMyBeamTI==TI_LEFT)
				{
					cout<<"OurBallRightAttackForm"<<OurBallRightAttackForm<<endl;
					ss=GetBeamParameter(emOurBallForm);
					player.Beam();
				}
				else
				{
					ss=GetBeamParameter(emOppBallForm);
					player.Beam();
				}
				finishedSendInitMessage=true;
			}
		}
		else
		{
			ss=player.Think();//做决策
		}
		
		gettimeofday(&stop,0);
		
		//cout<<"stop->tv_sec:"<<stop.tv_sec<<endl;
		//cout<<"stop->tv_usec:"<<stop.tv_usec<<endl;

		timeval_subtract(&diff,&start,&stop);
		struct timeval* timeDiffer=&diff;

		if(timeDiffer->tv_usec>20000)
		{
//		cout<<"=================================================================="<<endl;
//		cout<<"20000 second   :"<<timeDiffer->tv_sec<<endl;
//		cout<<"20000 micro sec:"<<timeDiffer->tv_usec<<endl;
//		cout<<"=================================================================="<<endl;
		}
		else if(timeDiffer->tv_usec>5000)
		{
//		cout<<"----------------------------------------------------------"<<endl;
//		cout<<"5000 second   :"<<timeDiffer->tv_sec<<endl;
//		cout<<"5000 micro sec:"<<timeDiffer->tv_usec<<endl;
//		cout<<"-----------------------------------------------------------"<<endl;
		}

		//cout<<"time:"<<wm.GetCurrentGameTime()<<endl;
		//cout<<"msg to server:"<<ss<<endl;
		ss=ss+"(syn)";
		server->PutMessage(ss);//发送信息
		myLoggerSend.DoLogByFormatting(name,"  %d   time::%s##%s",newWalk.walkCounter,Convert::ToString(wm.GetCurrentGameTime()).c_str(),ss.c_str());
		ss="";
		cout<<"-----------------------------------time:"<<wm.GetCurrentGameTime()<<endl;
	}
	Closelogs();
}
void Agent::Done()
{
	server->CloseConnectionToServer();
}

/**
 *   计算两个时间的间隔，得到时间差   
 *   @param   struct   timeval*   result   	返回计算出来的时间
 *   @param   struct   timeval*   x             需要计算的前一个时间
 *   @param   struct   timeval*   y             需要计算的后一个时间
 *   return   -1   failure   ,0   success   
 **/
int Agent::timeval_subtract(struct timeval* result,struct timeval* x,struct timeval* y)
{
	//int nsec;

	if(x->tv_sec>y->tv_sec)
		return   -1;

	if((x->tv_sec==y->tv_sec)&&(x->tv_usec>y->tv_usec))
		return   -1;
	result->tv_sec = (y->tv_sec - x->tv_sec);
	result->tv_usec = (y->tv_usec - x->tv_usec);

	if(result->tv_usec<0)
	{
		result->tv_sec--;
		result->tv_usec+=1000000;
	}

	return 0;
}
int Agent::ConvertStrToInt(string str)
{
	int temp;
	stringstream sstr; 
	sstr<<str; 
	sstr>>temp;
	return temp; 
}

float Agent::ConvertStrToFloat(string str)
{
	float temp;
	stringstream sstr; 
	sstr<<str; 
	sstr>>temp;
	return temp; 
}

void Agent::jointRecordOpen()
{
	myRLEG_J1Logger.SetEnable(JOINT_RECORD);
	myRLEG_J1Logger.OpenFileStream();

	myRLEG_J2Logger.SetEnable(JOINT_RECORD);
	myRLEG_J2Logger.OpenFileStream();
	
	myRLEG_J3Logger.SetEnable(JOINT_RECORD);
	myRLEG_J3Logger.OpenFileStream();

	myRLEG_J4Logger.SetEnable(JOINT_RECORD);
	myRLEG_J4Logger.OpenFileStream();

	myRLEG_J5Logger.SetEnable(JOINT_RECORD);
	myRLEG_J5Logger.OpenFileStream();

	myLLEG_J1Logger.SetEnable(JOINT_RECORD);
	myLLEG_J1Logger.OpenFileStream();
	
	myLLEG_J2Logger.SetEnable(JOINT_RECORD);
	myLLEG_J2Logger.OpenFileStream();

	myLLEG_J3Logger.SetEnable(JOINT_RECORD);
	myLLEG_J3Logger.OpenFileStream();

	myLLEG_J4Logger.SetEnable(JOINT_RECORD);
	myLLEG_J4Logger.OpenFileStream();

	myLLEG_J5Logger.SetEnable(JOINT_RECORD);
	myLLEG_J5Logger.OpenFileStream();
}

void Agent::jointRecordClose()
{
	myRLEG_J1Logger.CloseFileStream();
	myRLEG_J2Logger.CloseFileStream();
	myRLEG_J3Logger.CloseFileStream();
	myRLEG_J4Logger.CloseFileStream();
	myRLEG_J5Logger.CloseFileStream();

	myLLEG_J1Logger.CloseFileStream();
	myLLEG_J2Logger.CloseFileStream();
	myLLEG_J3Logger.CloseFileStream();
	myLLEG_J4Logger.CloseFileStream();
	myLLEG_J5Logger.CloseFileStream();
}
Vector3 Agent::GetNowBeam(int num,OurBallFormKind  nowMyBeamTI)
{
	Vector3 nowMyBeam;

	string x, y, z;

	string fileName;
//	cout<<"nowMyBeamTI::"<<nowMyBeamTI<<endl;
	switch(nowMyBeamTI)
	{
	case emOurBallForm:
		fileName="conf/OurBallForm.conf";
		break;
	case emOppBallForm:
		fileName="conf/OppBallForm.conf";
		break;
	case OurBallRightAttackForm:
		fileName="conf/OurBallRightAttackForm.conf";
		break;
	default:
		fileName="conf/OppBallForm.conf";
		break;
	}
	string word;
	//	cout<<".........sada"<<endl;
	cout<<"fileName::"<<fileName<<endl;
	ifstream fin(fileName.c_str());

	int number = num, cordnum = 1;
	char ch, last;
	last = 'a';
	int point = 1;
	while (fin.get(ch))
	{
		//word.insert(word.end(),ch);
		//cout<<"sda"<<endl;
		if (ch == '\n')
		{
			if (cordnum == number)
			{
		//		cout << "Vector3::" << x << "  " << y << "  " << z << endl;
				break;
			}
			cordnum++;
			x = "";
			y = "";
			z = "";
			word = "";
			point = 1;
		}
		else
		{
			//cout<<"ch:"<<ch<<"   "<<(int)ch<<"  "<<((int)ch!=32)<<"  point::"<<point<<endl;
			if (cordnum == number)
			{
				if ((int) ch != 32)
				{
					last = 'a';
					switch (point)
					{
					case 1:
						x.insert(x.end(), ch);
						break;
					case 2:
						y.insert(y.end(), ch);
						break;
					case 3:
						z.insert(z.end(), ch);
						break;
					}
				}
				else
				{
					if (last != ' ')
					{
						point++;
					}

					last = ' ';
				}
			}
			//cout<<"point::"<<point<<endl;

		}
		//cout<<"word::"<<word<<endl;
	}
	//cout<<"X::"<<x<<"    "<<Convert::ToFloat(x)<<endl;
	nowMyBeam=Vector3(Convert::ToFloat(x) ,Convert::ToFloat(y),Convert::ToFloat(z));
	//cout << "Vector3::" <<nowMyBeam<< endl;
	fin.close();
	return nowMyBeam;
}






