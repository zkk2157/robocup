/*
 * Cout.h
 *
 *  Created on: 2012-5-7
 *      Author: cit32
 */

#ifndef COUT_H_
#define COUT_H_
#include "Types.h"
class Cout
{
public:
	Cout();
	static void print(Role val);
    static void print(TPlayMode val);
	//static void print(emOurState val);
	static void print(DecisionMotion dm);
	virtual ~Cout();
};

#endif /* COUT_H_ */
