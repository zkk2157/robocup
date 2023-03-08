/*
 * DrawBuffer.h
 *
 *  Created on: 2012-5-1
 *      Author: cit32
 */

#ifndef DRAWBUFFER_H_
#define DRAWBUFFER_H_
#include <string>
#include <cstdio>
#include <cstring>

using namespace std;
namespace MonitorDraw
{

class DrawBuffer
{
public:
	DrawBuffer();
	static unsigned char* TranToMonitor(float x, float y, float angle,
			int* bufSize);
	static unsigned char* newBufferSwap(const string* name, int* bufSize);
	static unsigned char* newCircle(const float* center, float radius,
			float thickness, const float* color, const string* setName,
			int* bufSize);
	static unsigned char* newLine(const float* a, const float* b,
			float thickness, const float* color, const string* setName,
			int* bufSize);
	static unsigned char* newPoint(const float* p, float size,
			const float* color, const string* setName, int* bufSize);
	static unsigned char* newSphere(const float* p, float radius,
			const float* color, const string* setName, int* bufSize);
	static unsigned char* newPolygon(const float* v, int numVerts,
			const float* color, const string* setName, int* bufSize);
	virtual ~DrawBuffer();
private:
	static inline int writeCharToBuf(unsigned char* buf, unsigned char value);
	static inline int writeFloatToBuf(unsigned char* buf, float value);
	static inline int writeColorToBuf(unsigned char* buf, const float* color,
			int channels);
	static inline int writeStringToBuf(unsigned char* buf, const string* text);
};

} /* namespace monDraw */
#endif /* DRAWBUFFER_H_ */
