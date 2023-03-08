/*
 * DrawBuffer.cpp
 *
 *  Created on: 2012-5-1
 *      Author: cit32
 */

#include "DrawBuffer.h"

namespace MonitorDraw
{

DrawBuffer::DrawBuffer()
{
	// TODO Auto-generated constructor stub

}

inline int DrawBuffer::writeCharToBuf(unsigned char* buf, unsigned char value)
{
	*buf = value;
	return 1;
}

inline int DrawBuffer::writeFloatToBuf(unsigned char* buf, float value)
{
	char temp[20];
	sprintf(temp, "%6f", value);
	memcpy(buf, temp, 6);
	return 6;
}

inline int DrawBuffer::writeColorToBuf(unsigned char* buf, const float* color,
		int channels)
{
	int i;
	for (i = 0; i < channels; i++)
		writeCharToBuf(buf + i, (unsigned char) (color[i] * 255));
	return i;
}

inline int DrawBuffer::writeStringToBuf(unsigned char* buf, const string* text)
{
	long i = 0;
	if (text != NULL
	)
		i += text->copy((char*) buf + i, text->length(), 0);
	i += writeCharToBuf(buf + i, 0);
	return i;
}

unsigned char* DrawBuffer::newBufferSwap(const string* name, int* bufSize)
{
	*bufSize = 3 + ((name != NULL) ? name->length() : 0);
	unsigned char* buf = new unsigned char[*bufSize];

	long i = 0;
	i += writeCharToBuf(buf+i, 0);
	i += writeCharToBuf(buf+i, 0);

	i += writeStringToBuf(buf+i, name);

	return buf;
}

unsigned char* DrawBuffer::newCircle(const float* center, float radius,
		float thickness, const float* color, const string* setName,
		int* bufSize)
{

	*bufSize = 30 + ((setName != NULL) ? setName->length() : 0);
	unsigned char* buf = new unsigned char[*bufSize];

	long i = 0;
	i += writeCharToBuf(buf+i, 1);
	i += writeCharToBuf(buf+i, 0);
	i += writeFloatToBuf(buf+i, center[0]);
	i += writeFloatToBuf(buf+i, center[1]);
	i += writeFloatToBuf(buf+i, radius);
	i += writeFloatToBuf(buf+i, thickness);
	i += writeColorToBuf(buf+i, color, 3);
	i += writeStringToBuf(buf+i, setName);

	return buf;
}

unsigned char* DrawBuffer::newLine(const float* a, const float* b,
		float thickness, const float* color, const string* setName,
		int* bufSize)
{

	*bufSize = 48 + ((setName != NULL) ? setName->length() : 0);
	unsigned char* buf = new unsigned char[*bufSize];

	long i = 0;
	i += writeCharToBuf(buf+i, 1);
	i += writeCharToBuf(buf+i, 1);
	i += writeFloatToBuf(buf+i, a[0]);
	i += writeFloatToBuf(buf+i, a[1]);
	i += writeFloatToBuf(buf+i, a[2]);
	i += writeFloatToBuf(buf+i, b[0]);
	i += writeFloatToBuf(buf+i, b[1]);
	i += writeFloatToBuf(buf+i, b[2]);
	i += writeFloatToBuf(buf+i, thickness);
	i += writeColorToBuf(buf+i, color, 3);

	i += writeStringToBuf(buf+i, setName);

	return buf;
}

unsigned char* DrawBuffer::newPoint(const float* p, float size,
		const float* color, const string* setName, int* bufSize)
{

	*bufSize = 30 + ((setName != NULL) ? setName->length() : 0);
	unsigned char* buf = new unsigned char[*bufSize];

	long i = 0;
	i += writeCharToBuf(buf+i, 1);
	i += writeCharToBuf(buf+i, 2);
	i += writeFloatToBuf(buf+i, p[0]);
	i += writeFloatToBuf(buf+i, p[1]);
	i += writeFloatToBuf(buf+i, p[2]);
	i += writeFloatToBuf(buf+i, size);
	i += writeColorToBuf(buf+i, color, 3);
	i += writeStringToBuf(buf+i, setName);

	return buf;
}

unsigned char* DrawBuffer::newSphere(const float* p, float radius,
		const float* color, const string* setName, int* bufSize)
{

	*bufSize = 30 + ((setName != NULL) ? setName->length() : 0);
	unsigned char* buf = new unsigned char[*bufSize];

	long i = 0;
	i += writeCharToBuf(buf+i, 1);
	i += writeCharToBuf(buf+i, 3);
	i += writeFloatToBuf(buf+i, p[0]);
	i += writeFloatToBuf(buf+i, p[1]);
	i += writeFloatToBuf(buf+i, p[2]);
	i += writeFloatToBuf(buf+i, radius);
	i += writeColorToBuf(buf+i, color, 3);

	i += writeStringToBuf(buf+i, setName);

	return buf;
}
unsigned char* DrawBuffer::TranToMonitor(float x, float y, float angle,
		int* bufSize)
{
	*bufSize = 23;
	unsigned char* buf = new unsigned char[*bufSize];

	long i = 0;
	i += writeCharToBuf(buf + i, 1);
	i += writeCharToBuf(buf + i, 5);
	i += writeFloatToBuf(buf + i, x);
	i += writeFloatToBuf(buf + i, y);
	i += writeFloatToBuf(buf + i, angle);
	i += writeCharToBuf(buf + i, 6);
	i += writeCharToBuf(buf + i, 6);
	i += writeCharToBuf(buf + i, 6);

	return buf;
}

unsigned char* DrawBuffer::newPolygon(const float* v, int numVerts,
		const float* color, const string* setName, int* bufSize)
{

	*bufSize = 18 * numVerts + 8 + ((setName != NULL) ? setName->length() : 0);
	unsigned char* buf = new unsigned char[*bufSize];

	long i = 0;
	i += writeCharToBuf(buf+i, 1);
	i += writeCharToBuf(buf+i, 4);
	i += writeCharToBuf(buf+i, numVerts);
	i += writeColorToBuf(buf+i, color, 4);

	for (int j = 0; j < numVerts; j++)
	{
		i += writeFloatToBuf(buf+i, v[j*3+0]);
		i += writeFloatToBuf(buf+i, v[j*3+1]);
		i += writeFloatToBuf(buf+i, v[j*3+2]);
	}

	i += writeStringToBuf(buf+i, setName);

	return buf;
}
DrawBuffer::~DrawBuffer()
{
	// TODO Auto-generated destructor stub
}

} /* namespace monDraw */
