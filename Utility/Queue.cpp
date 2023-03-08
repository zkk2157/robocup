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

#include "Queue.h"

Queue::Queue()
{
	front = 0;
	rear = 0;
	queue = new float[9];
	QueueSize = 9;
}

Queue::Queue(int Cycle)
{
	front = 0;
	rear = 0;
	queue = new float[Cycle];
	QueueSize = Cycle;
}

Queue::~Queue()
{
}

void Queue::Add(float Item)
{
	rear = (rear + 1) % QueueSize;
	if (isFull())
	{
		std::cout << "The Queue is full" << '\n';
		std::cout << "Please delete some data from the Queue " << '\n';
	}
	else
		queue[rear] = Item;
}

float Queue::Delete()
{
	front = (front + 1) % QueueSize;
	if (isEmpty())
	{
		std::cout << "The Queue is empty" << '\n';
		std::cout << "Please add some data ro the Queue " << '\n';
		return -1;
	}
	else
	{
		return queue[front];
	}

}

bool Queue::isEmpty()
{
	return (rear == front);
}

bool Queue::isFull()
{
	return (rear == front);
}

void Queue::printArray()
{
	std::cout << queue[0] << '\t' << queue[1] << '\t' << queue[2] << '\t'
			<< queue[3] << '\t' << queue[4] << '\t' << queue[5] << '\t'
			<< queue[6] << '\t' << queue[7] << '\t' << queue[8] << '\t'; //<<queue[9] << '\t'<<queue[10] << '\t'<<queue[11] << '\t'<<queue[12] << '\t'<<queue[13] << '\t';

}

void Queue::removedQueue(float value)
{
	queue[rear] = value;
	rear = (rear + 1) % QueueSize;
// 	if(QueueSize==9){
// 	  std::cout<<"		now rear , the value next will in :"<<rear;
// 	}
}

float Queue::MaxQueue()
{
	float temp;
	temp = queue[0];
	for (int i = 1; i < QueueSize; i++)
		if (temp < queue[i])
			temp = queue[i];
	return temp;
}

float Queue::MinQuue()
{
	float temp;
	temp = queue[0];
	for (int i = 1; i < QueueSize; i++)
		if (temp > queue[i])
			temp = queue[i];
	return temp;
}

float Queue::AvrageQueue()
{
	float temp = 0;
	for (int i = 0; i < QueueSize; i++)
		temp = temp + queue[i];
	temp = temp / QueueSize;
	return temp;
}

void Queue::Clean()
{
	for (int i = 0; i < QueueSize; i++)
		queue[i] = 0;
}

float Queue::GetFront()
{
	return queue[rear];
}

float Queue::GetRear()
{
	int x = rear;
	x--;
	if (x == -1)
	{
		x = QueueSize - 1;
	}
	//std::cout<<"   GetRear x :"<<x<<"		value :"<<queue[x];
	return queue[x];
}