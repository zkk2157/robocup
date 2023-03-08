# ifndef SOCKET_H
# define SOCKET_H

# include <sys/types.h>
# include <sys/socket.h>
# include <unistd.h>
//# include <linux/tcp.h>
# include <netinet/in.h>
#include <arpa/inet.h>
# include <string>
# include <string.h>
# include <stdlib.h>
# include <iostream>

using namespace std;

/**
\file socket.h
@author Leisland <leisland@163.com>
 */

/**
\class Socket is the basic class for network connection,the main function of this class is
bind a socket descriptor to the port,make a connection to the server,close the connection
between client and server.Once you have connected to the server successfuly,you can read and
write the data with the server.(editor:leisland date:2008-8-20)
*/

class Socket
{
	public:
		/**the construc function will be called when you define a new object,and it will call function CreateSocket()
		to get a new socket descriptor*/
		Socket();
		
		/**bind the socket descriptor to local computer's port which is leisure*/
		bool bind();
		
		/**connect to the specified server,the server's IP is hostIP and the port is hostPort*/
		bool connect(int hostPort,string hostIP);
		
		/**close the connection between server and client*/
		void close();
		
		/**get the socket descriptor*/
		int getFD();
		
	private:
		/**define a new socket descriptor*/
		void CreateSocket();
		
		/**set the basic prarameter of server*/
		void SetServerParameter(int port,string IP);
		
		/**print the error message*/
		void PrintErrorMsg(string str);
		
	private:
		/**the socket descriptor*/
		int sockfd;
		
		/**the basic parameter of server*/
		struct sockaddr_in server_addr,my_addr;
		
};///end calss Socket

# endif///end SOCKET_H

