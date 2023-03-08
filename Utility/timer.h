#ifndef TIMER_H
#define TIMER_H
/**
 \file timer.h
 @author Leisland <leisland@163.com>
 */
/**
 \class Timer is a kind of utility.You can use it to control the time,thus,allow the program do something in the selected time.
 You must give a initial vaue to the variant limitTime when you create one new Timer object.The variant limitTime is an ieteger,
 one represent 0.02 seconds,the cycle time of Robocup Simulation 3D server.
 */
class Timer
{
public:
	/*default constructor of Timer,init the value of counter and limintTime.Both the initial value is zero.*/
	Timer();

	/*the overloaded constructor of Timer,init the value of limitTime with the value of time.*/
	Timer(int time);

	/*select the limit time of Timer object.*/
	void SetLimitTime(int time);

	/*clear the limit time of Timer object.*/
	void ClearLimitTime();

	/*return the limit time of timer object.*/
	int GetLimitTime();

	/*clear the counter of Timer object.*/
	void ClearCounter();

	/*test the time if out,if it is true ,return value true;or return value false.*/
	bool IsTimeOut();
private:
	/*counter of timer.*/
	int counter;

	/*limit time of timer.*/
	int limitTime;
};
///end of \class Timer
#endif///end of TIME_H
