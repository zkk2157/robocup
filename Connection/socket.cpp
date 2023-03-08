# include "socket.h"

Socket::Socket()
{
	CreateSocket();
}

void Socket::CreateSocket()
{
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
//	int nodelay=1;
	//int err=setsockopt(sockfd,IPPROTO_TCP,1,&nodelay,sizeof(int));
//	int err=setsockopt(sockfd,IPPROTO_TCP,TCP_NODELAY,&nodelay,sizeof(int));
//	if(sockfd < 0);
//	{
//		PrintErrorMsg("socket");
//		//exit(1);
//	}
}

bool Socket::bind()
{
	my_addr.sin_family = AF_INET;
	my_addr.sin_port = htons(0);
	my_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	bzero(&(my_addr.sin_zero), 8);

	int bindState = -1;
	bindState = ::bind(sockfd, (struct sockaddr *) &my_addr,
			sizeof(struct sockaddr));

	if (bindState < 0)
	{
		PrintErrorMsg("bind");
		return false;
	}
	else
		return true;
}

bool Socket::connect(int hostPort, string hostIP)
{
	SetServerParameter(hostPort, hostIP);

	int connectState = -1;

	connectState = ::connect(sockfd, (struct sockaddr *) &server_addr,
			sizeof(struct sockaddr_in));

	if (connectState < 0)
	{
		PrintErrorMsg("connect");
		return false;
	}

	return true;
}

void Socket::close()
{
	::close(sockfd);
}

int Socket::getFD()
{
	return sockfd;
}

void Socket::SetServerParameter(int port, string IP)
{
	const char *str = IP.c_str();

	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(port);
	server_addr.sin_addr.s_addr = inet_addr(str);
	bzero(&(server_addr.sin_zero), 8);
}

void Socket::PrintErrorMsg(string str)
{
	if (str == "socket")
		cout << "\t" << "can not create the socket descriptor !" << endl;
	else if (str == "bind")
		cout << "\t" << "can not bind to the port !" << endl;
	else if (str == "connect")
		cout << "\t" << "can not connect to the server !" << endl;
}

