/*
 * UDP connection to the server,get message by UDP connection
 *     ///do not finished!!!///
 */
#ifndef UDPCONNECTION_H
#define uDPCONNECTION_H
#include "Communit.h"
class UdpConnection: public Communit
{
public:
	bool ConnectToServer()
	{
		return false;
	}
	void CloseConnectionToServer()
	{
	}
	bool GetMessage(std::string& msg)
	{
		return false;
	}
	void PutMessage(const std::string& msg)
	{
	}
};
#endif
