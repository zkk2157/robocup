/*
 * MDrawer.cpp
 *
 *  Created on: 2012-5-1
 *      Author: cit32
 */

#include "MDrawer.h"


extern WorldModel wm;
namespace MonitorDraw
{

MDrawer::MDrawer()
{
	// TODO Auto-generated constructor stub

}
void MDrawer::OpenConnection()
{

	int rv;
	// int numbytes;

	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_DGRAM;

	if ((rv = getaddrinfo(ROBOVIS_HOST, ROBOVIS_PORT, &hints, &servinfo)) != 0)
	{
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
		// return 1;
	}

	// loop through all the results and make a socket
	for (p = servinfo; p != NULL; p = p->ai_next)
	{
		if ((sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol))
				== -1)
		{
			perror("socket");
			continue;
		}

		break;
	}

	if (p == NULL)
	{
		fprintf(stderr, "failed to bind socket\n");
		//return 2;
	}
}
void MDrawer::CloseConnection()
{
	freeaddrinfo(servinfo);
	close(sockfd);
}

/*
 *x1,y1,z1为划线的起始位置
 *x2,y2,z2为划线的在终止位置
 *thickness为线的粗细
 *rgb为三基色
 */
void MDrawer::drawLine(float x1, float y1, float z1, float x2, float y2,
		float z2, float thickness, float r, float g, float b,
		const string* setName)
{
	float pa[3] =
	{ x1, y1, z1 };
	float pb[3] =
	{ x2, y2, z2 };
	float color[3] =
	{ r, g, b };

	int bufSize = -1;
	unsigned char* buf = DrawBuffer::newLine(pa, pb, thickness, color, setName,
			&bufSize);
	sendto(sockfd, buf, bufSize, 0, p->ai_addr, p->ai_addrlen);
	delete[] buf;
}
void MDrawer::drawLine(Vector3 pFrom, Vector3 pTo, float thickness, RGBDraw rgb,
		const string* setName)
{
	if(wm.GetMyTeamIndex()==TI_RIGHT)
	{
		pFrom=Convert::Turn180(pFrom);
		pTo=Convert::Turn180(pTo);
	}
	drawLine(pFrom.x(), pFrom.y(), pFrom.z(), pTo.x(), pTo.y(), pTo.z(),
			thickness, rgb.r, rgb.g, rgb.b, setName);
}
void MDrawer::drawLine(Vector3 pFrom, float angle, float dis, float thickness,
		RGBDraw rgb, const string* setName)
{
	Vector3 pTo;
	if(wm.GetMyTeamIndex()==TI_RIGHT)
	{
		pFrom=Convert::Turn180(pFrom);
		angle=Convert::AngleTurn180(angle);
	}
	pTo.x(pFrom.x() + dis * cosDeg(90 - angle));
	pTo.y(pFrom.y() + dis * sinDeg(90 - angle));
	drawLine(pFrom.x(), pFrom.y(), pFrom.z(), pTo.x(), pTo.y(), pTo.z(),
			thickness, rgb.r, rgb.g, rgb.b, setName);
}
void MDrawer::drawPoint(float x, float y, float z, float size, float r, float g,
		float b, const string* setName)
{

	float center[3] =
	{ x, y, z };
	float color[3] =
	{ r, g, b };

	int bufSize = -1;
	unsigned char* buf = DrawBuffer::newPoint(center, size, color, setName,
			&bufSize);
	sendto(sockfd, buf, bufSize, 0, p->ai_addr, p->ai_addrlen);
	delete[] buf;
}
void MDrawer::TranToMonitor(Vector3 pos, float angle)
{
	if(wm.GetMyTeamIndex()==TI_RIGHT)
	{
		pos=Convert::Turn180(pos);
	}
	int bufSize = -1;
	unsigned char* buf = DrawBuffer::TranToMonitor(pos.x(), pos.y(), angle,
			&bufSize);
	sendto(sockfd, buf, bufSize, 0, p->ai_addr, p->ai_addrlen);
	delete[] buf;
}
void MDrawer::drawPoint(Vector3 point, float size, RGBDraw rgb,
		const string* setName)
{
	if(wm.GetMyTeamIndex()==TI_RIGHT)
	{
		point=Convert::Turn180(point);
	}
	drawPoint(point.x(), point.y(), point.z(), size, rgb.r, rgb.g, rgb.b,
			setName);
}
void MDrawer::UpdateDrawer(const string* setName)
{
	int bufSize = -1;
	unsigned char* buf = DrawBuffer::newBufferSwap(setName, &bufSize);
	sendto(sockfd, buf, bufSize, 0, p->ai_addr, p->ai_addrlen);
	delete[] buf;
}
MDrawer::~MDrawer()
{
	// TODO Auto-generated destructor stub
}

} /* namespace monDraw */
