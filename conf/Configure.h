/*
 * Configure.h
 *
 *  Created on: 2012-3-13
 *      Author: cit
 */

#ifndef CONFIGURE_H_
#define CONFIGURE_H_
#include "../Stdafx.h"
using namespace std;
class Configure
{
public:
	void OpenConf();
	Configure();
	virtual ~Configure();
	bool RightAttack;
	bool DrawerBug;
	bool GoailDrawer;
	bool slideTackle;
private:

	/**the name of log file*/
	string fileName;

};

#endif /* CONFIGURE_H_ */
