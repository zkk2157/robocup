/*
 * Stdafx.h
 *
 *  Created on: 2012-2-29
 *      Author: cit chen
 */

#ifndef STDAFX_H_
#define STDAFX_H_
#include <cmath>
# include <sys/types.h>
# include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
# include <netinet/in.h>
#include <arpa/inet.h>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include "boost/config.hpp"
#include "boost/detail/workaround.hpp"
#include <sys/time.h>
#include "Utility/Cout.h"
#include "Worldmodel/SaveCoordinate.h"
#include "Worldmodel/playerinfo.h"
#include "Utility/Types.h"
#include "Utility/Geometry.h"
#include "Utility/CITMath.h"
#include "Utility/timer.h"
#include "Utility/Queue.h"
#include "Utility/convert.h"
#include "Agent/agent.h"
#include "Player/agentstrategy.h"
#include "Player/CITPlayer.h"
#include "log/logger.h"
#include "conf/Configure.h"
#include "Sensor/perceptor.h"
#include "Connection/Tcpconnection.h"
#include "Connection/Communit.h"
#include "Effectors/jointEffector.h"
#include "Effectors/formatInfoToServer.h"
#include "Skill/theNewWalk.h"
#include "Skill/basicMotion.h"
#include "Skill/standup.h"
#include "Effectors/Say.h"
#include "Sensor/Hear.h"
#include "Worldmodel/worldmodel.h"
#include "MonitorDraw/MDrawer.h"
#endif /* STDAFX_H_ */
