/*
 * base class for tcp connection,udp connection, file connection
 */
#ifndef COMMUNIT_H
#define COMMUNIT_H
#include <iostream>

class Communit
{
public:
	virtual bool ConnectToServer()
	{
		return false;
	}
	virtual void CloseConnectionToServer()
	{
	}
	virtual bool GetMessage(std::string& msg)
	{
		return false;
	}
	virtual void PutMessage(const std::string& msg)
	{
	}
	virtual ~Communit()
	{
	}
};

#endif
