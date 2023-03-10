/*
 <one line to give the program's name and a brief idea of what it does.>
 Copyright (C) <year>  <name of author>

 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.

 */

#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>

class Queue
{
public:
	Queue();
	Queue(int Cycle);
	~Queue();

	void Add(float Item);

	float Delete();

	bool isEmpty();

	bool isFull();

	void printArray();

	void removedQueue(float value);

	float MaxQueue();

	float MinQuue();

	float AvrageQueue();

	void Clean();

	float GetFront();

	float GetRear();

private:
	int MaxQueueIndex;
	int QueueSize;
	//float   queue[18];
	float *queue;

	int front, rear;

};

#endif // QUEUE_H
