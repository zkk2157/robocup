/*
 * File input connection,get message from the log file
 *     ///do not finished!!!///
 */
#ifndef FILEINPUT_H
#define FILEINPUT_H
#include "Communit.h"
class FileInput: public Communit
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
