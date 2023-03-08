#ifndef TCPCONNECTION_H
#define TCPCONNECTION_H

# include <string>
# include <iostream>
# include <errno.h>
# include "socket.h"
# include "Communit.h"

//if use the library of soccer server to create the socket descriptor,need to include the following the head files
# include <netinet/in.h>
# include <rcssnet/tcpsocket.hpp>
# include <rcssnet/exception.hpp>
using namespace rcss::net;

#define ERRORMsg "Connection reset by peer"

using namespace std;

/**
 \file agentconnection.h
 @author Leisland <leisland@163.com>
 */

/**
 \class AgentConnection provides network connection for agent,it can make a connection with the remote simspark server or the local simspark server.once the connection finished,the agent could receive  message from server and send message to server.(editor:leisland date:2008-8-20)
 */

class TcpConnection: public Communit
{
public:
	/**construct function will set the default host port and IP address of remote  server*/
	TcpConnection();

	TcpConnection(string host, int port);

	/**destructor of \class AgentConnection ,it will release the memory of message buffer*/
	~TcpConnection();

	/**set the IP address of host*/
	void SetHostIP(string IP);

	/**set the port of host*/
	void SetHostPort(int port);

	/**get the IP address of host*/
	string GetHostIP();

	/**get the port of host*/
	int GetHostPort();

	/**try to connect to the remote server*/
	bool ConnectToServer();

	/**close the connection between client and server*/
	void CloseConnectionToServer();

	/**send message to the remote server*/
	void PutMessage(const string& msg);

	/**receive message from the remote server*/
	bool GetMessage(string& msg);

	/**receive message from the remote server*/
	bool ReceiveMsg(string& msg);

	/**set the I/O mode*/
	bool SelectInput();
private:
	/**the host IP address*/
	string hostIP;

	/**the host port*/
	int hostPort;

	/**the counter of null stirng*/
	int nullstring_counter;

	/**socket descriptor*/
	//Socket gSocket;
	/**socket descriptor*/
	TCPSocket gSocket; //use the library of soccer server to create the socker descriptor

	/**message buffer*/
	char mBuffer[16 * 1024];}; //end AgentConnection

#endif//end AGENTCONNECTION_H
