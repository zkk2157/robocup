# include "Tcpconnection.h"

TcpConnection::TcpConnection()
{
	hostIP = "127.0.0.1";
	hostPort = 3100;
	nullstring_counter = 0;
	memset(mBuffer, '\0', sizeof(mBuffer)); //file the memory of mBuffer with '\0'
}

TcpConnection::TcpConnection(string host, int port)
{
	hostIP = host;
	hostPort = port;
	nullstring_counter = 0;
	memset(mBuffer, '\0', sizeof(mBuffer)); //file the memory of mBuffer with '\0'
}

TcpConnection::~TcpConnection()
{
	//delete [] mBuffer;
}
void TcpConnection::SetHostIP(string IP)
{
	hostIP = IP;
}
void TcpConnection::SetHostPort(int port)
{
	hostPort = port;
}
string TcpConnection::GetHostIP()
{
	return hostIP;
}
int TcpConnection::GetHostPort()
{
	return hostPort;
}
bool TcpConnection::ConnectToServer()
{
	/////cout <<"\t"<< "connecting to TCP " << hostIP << " port:" << hostPort << "\n";
#if 1
	try
	{
		Addr local(INADDR_ANY, INADDR_ANY); //why need to connect to local??????????/
gSocket	.bind(local);
}
catch (BindErr error)
{
	cerr <<"\t"<< "failed to bind socket with '"<< error.what() << "'" << endl;
	gSocket.close();
	return false;
}

try
{
	Addr server(hostPort,hostIP);
	cerr<<"\t"<<"server :"<<server<<endl;
	gSocket.connect(server);
}
catch (ConnectErr error)
{
	cerr <<"\t"<< "connection failed with: '"<< error.what() << "'" << endl;
	gSocket.close();
	return false;
}
#endif

#if 0
if(gSocket.connect(hostPort,hostIP) == false)
{
	cerr <<"\t"<< "connection failed !"<< endl;
	gSocket.close();
	return false;
}
#endif
cerr <<"\t"<<"connecting successful !"<<endl;
return true;
}
void TcpConnection::CloseConnectionToServer()
{
	gSocket.close();
	///////cout <<"\t"<< "closed connection to " << hostIP << ":" << hostPort <<endl<<endl;
	/////cout<<"\t"<<"closed connection to server!"<<endl;
}

void TcpConnection::PutMessage(const string& msg)
{
#if 0
	if (msg.empty())
	{
		/////cout<<"\t"<<"my return msg is empty."<<endl;
		return;
	}

	// prefix the message with it's payload length
	unsigned int len = static_cast<unsigned int>(htonl(msg.size()));
	gSocket.send((const char*)&len, sizeof(unsigned int));
	int rval = gSocket.send(msg.data(), msg.size());

//	/////cout<<"msg len:"<<msg.size()<<endl;
//	/////cout<<"sent msg leng:"<<rval<<endl;
	if (rval < 0)
	{
		cerr
		<< "(PutMessage) ERROR: "
		<< " send returned error '"
		<< strerror(errno) << "' " << endl;
		return;
	}
//	return true;
#endif
#if 1
	if (msg.empty())
	{
		/////cout<<"\t"<<"my return msg is empty."<<endl;
		return;
	}
	unsigned int len = htonl(msg.size());
	string prefix((const char*) &len, sizeof(unsigned int));
	string str = prefix + msg;
	write(gSocket.getFD(), str.data(), str.size());

#endif
}

bool TcpConnection::GetMessage(string& msg)
{
#if 1
	static char buffer[16 * 1024];

unsigned	int bytesRead = 0;
	while(bytesRead < sizeof(unsigned int))
	{
		SelectInput();

		int readResult = gSocket.recv(buffer + bytesRead, sizeof(unsigned int) - bytesRead);
		if(readResult <= 0)
		{
			cerr
			<< "(GetMessage) ERROR: "
			<< " read returned error '"
			<< strerror(errno) << "' " << endl;
			// continue;
			return false;
		}
		bytesRead += readResult;
	}

	//cerr << "buffer = |" << string(buffer+1) << "|\n";
	//cerr << "bytesRead = |" << bytesRead << "|\n";
	//cerr << "Size of buffer = |" << sizeof(buffer) << "|\n";
	//cerr << "buffer = |" << buffer << "|\n";
	//cerr << "buffer[5] = |" << buffer[5] << "|\n";
	//printf ("xxx-%s\n", buffer+5);

	// msg is prefixed with it's total length
	unsigned int msgLen = ntohl(*(unsigned int*)buffer);
	// cerr << "GM 6 / " << msgLen << " (bytesRead " << bytesRead << ")\n";
	if(sizeof(unsigned int) + msgLen > sizeof(buffer))
	{
		cerr << "too long message; aborting" << endl;
		abort();
	}

	// read remaining message segments
	unsigned int msgRead = bytesRead - sizeof(unsigned int);

	//cerr << "msgRead = |" << msgRead << "|\n";

	char *offset = buffer + bytesRead;

	while (msgRead < msgLen)
	{
		if (! SelectInput())
		{
			return false;
		}

		int readLen = sizeof(buffer) - msgRead;
		if(readLen > msgLen - msgRead)
		readLen = msgLen - msgRead;

		int readResult = gSocket.recv(offset, readLen);
		if (readResult <= 0)
		{
			cerr
			<< "(GetMessage) ERROR: "
			<< " read returned error '"
			<< strerror(errno) << "' " << endl;

			// continue;
			return false;
		}
		msgRead += readResult;
		offset += readResult;
		//cerr << "msgRead = |" << msgRead << "|\n";
	}

	// zero terminate received data
	(*offset) = 0;

	msg = string(buffer+sizeof(unsigned int));

	// DEBUG
	//	///cout << msg << endl;

	return true;
#endif
#if 0
	/////cout<<"get msg: @1"<<endl;
	if (! SelectInput())
	{
		return false;
	}
	/////cout<<"get msg: @2"<<endl;
	static char buffer[16 * 1024];
	/////cout<<"get msg: @3"<<endl;
	unsigned int bytesRead = read(gSocket.getFD(), buffer, sizeof(buffer));
	/////cout<<"get msg: @4"<<endl;
	if (bytesRead < sizeof(unsigned int))
	{
		return false;
	}
	/////cout<<"get msg: @5"<<endl;
//    msg is prefixed with it's total length
	unsigned int msgLen = ntohl(*(unsigned int*)buffer);
	/////cout<<"get msg: @6"<<endl;
//     read remaining message segments
	unsigned int msgRead = bytesRead - sizeof(unsigned int);
	/////cout<<"get msg: @7"<<endl;
	char *offset = buffer + bytesRead;
	/////cout<<"get msg: @8"<<endl;
	while (msgRead < msgLen)
	{
		if (! SelectInput())
		{
			return false;
		}
		msgRead += read(gSocket.getFD(), offset, sizeof(buffer) - msgRead);

		offset += msgRead;
	}
	/////cout<<"get msg: @9"<<endl;
//     zero terminate received data
	(*offset) = 0;
	/////cout<<"get msg: @10"<<endl;
	msg = string(buffer+sizeof(unsigned int));
	/////cout<<"get msg: @11"<<endl;
	if(msg.length()==0)
	{
		nullstring_counter+=1;
	}
	else
	{
		nullstring_counter = 0;
	}

	if(nullstring_counter>80)
	{
		return false;
	}

	return true;
#endif
}
bool TcpConnection::ReceiveMsg(string& msg)
{
	unsigned int bytesRead = 0;
	int readResult = -1;
	memset(mBuffer, '\0', sizeof(mBuffer)); //useless?????????????????
	unsigned int iLen = sizeof(unsigned int);

	int iTest = 0;
	int iTest2 = 0;

	while (bytesRead < iLen)
	{
		iTest++;
		if (!SelectInput())
		{
			return false;
		}

		readResult = recv(gSocket.getFD(), mBuffer + bytesRead,
				iLen - bytesRead, 0);
		if (readResult <= 0)
		{
			/////cout <<" ReadCError1! "<<strerror(errno)<<endl;
			return false;
		}
		bytesRead += readResult;
	}
	unsigned int iMsgLen = ntohl(*(unsigned int*) mBuffer);
	if (iLen + iMsgLen > sizeof(mBuffer))
	{
		/////cout << "too long message; aborting" << endl;
		return false;
	}
	unsigned int msgRead = bytesRead - iLen;
	char *offset = mBuffer + bytesRead;
	readResult = -1;
	int readLen = 0;
	while (msgRead < iMsgLen)
	{
		iTest2++;
		if (!SelectInput())
		{
			return false;
		}
		readLen = sizeof(mBuffer) - msgRead;
		if (readLen > iMsgLen - msgRead)
			readLen = iMsgLen - msgRead;
		readResult = recv(gSocket.getFD(), offset, readLen, 0);
		if (readResult < 0)
		{
			/////cout <<" ReadError2! "<<strerror(errno)<<endl;
			return false;
		}
		msgRead += readResult;
		offset += readResult;
	}
	(*offset) = '\0';

	msg = string(mBuffer + sizeof(unsigned int));
	return true;
}
bool TcpConnection::SelectInput()
{
	fd_set readfds;
	FD_ZERO(&readfds);
	FD_SET(gSocket.getFD(), &readfds);

#ifdef WIN32
	int maxFd = 0;
#else
	int maxFd = gSocket.getFD() + 1;
#endif
	return select(maxFd, &readfds, 0, 0, 0) > 0;

#if 0
	fd_set readfds;
	struct timeval tv =
	{	60,0};
	FD_ZERO(&readfds);
	FD_SET(gSocket.getFD(),&readfds);

	while(1)
	{
		switch(select(gSocket.getFD()+1,&readfds, 0, 0, &tv))
		{
			case 1:
			if(strerror(errno)== ERRORMsg)
			{
				abort();
			}

			return 1;
			case 0:
			cerr <<"\t"<< "(SelectInput) select failed " << strerror(errno) << endl;
			abort();
			return 0;
			default:
			if(errno == EINTR)
			continue;
			cerr <<"\t"<< "(SelectInput) select failed " << strerror(errno) << endl;
			abort();
			return 0;
		}
	}
#endif
}
