/*
 * MDrawer.h
 *
 *  Created on: 2012-5-1
 *      Author: cit32
 */

#ifndef MDRAWER_H_
#define MDRAWER_H_
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string>
#include <math.h>
#include "../Utility/Geometry.h"
#include "../Worldmodel/worldmodel.h"
#include "../Utility/Types.h"

#include "DrawBuffer.h"
//#include "rvdraw.h"
using namespace std;
struct RGBDraw
{
	float r;
	float g;
	float b;
	RGBDraw(float x, float y, float z)
	{
		r = x;
		g = y;
		b = z;
	}
	RGBDraw()
	{
		r = 1;
		g = 1;
		b = 1;
	}
};
namespace MonitorDraw
{
#define ROBOVIS_HOST "192.168.82.21"
#define ROBOVIS_PORT "32769"

class MDrawer
{
public:
	MDrawer();
	void OpenConnection();
	void CloseConnection();
	void UpdateDrawer(const string* setName);
	virtual ~MDrawer();
	void drawLine(Vector3 pFrom, float angle, float dis, float thickness,
			RGBDraw rgb, const string* setName);
	void drawLine(Vector3 pFrom, Vector3 pTo, float thickness, RGBDraw rgb,
			const string* setName);
	void drawPoint(Vector3 point, float size, RGBDraw rgb,
			const string* setName);
	void TranToMonitor(Vector3 pos, float angle);
private:
	void drawLine(float x1, float y1, float z1, float x2, float y2, float z2,
			float thickness, float r, float g, float b, const string* setName);
	void drawPoint(float x, float y, float z, float size, float r, float g,
			float b, const string* setName);
	int sockfd;

	struct addrinfo hints, *servinfo;
	struct addrinfo* p;
	const static int TEST_DURATION = 10000;
};

} /* namespace monDraw */
#endif /* MDRAWER_H_ */
