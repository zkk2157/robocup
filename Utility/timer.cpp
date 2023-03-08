#include "timer.h"

Timer::Timer()
{
	counter = 0;
	limitTime = 0;
}

Timer::Timer(int time)
{
	counter = 0;
	limitTime = time;
}

void Timer::SetLimitTime(int time)
{
	limitTime = time;
}

void Timer::ClearLimitTime()
{
	limitTime = 0;
}

int Timer::GetLimitTime()
{
	return limitTime;
}

void Timer::ClearCounter()
{
	counter = 0;
}

bool Timer::IsTimeOut()
{
	counter++;
	if (counter > limitTime)
		return true;
	else
		return false;
}
