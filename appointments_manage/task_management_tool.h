/* @Author
Student Name: Emre KAYDU
Student ID : 150160552
Date: 4.11.2019 */

#ifndef TASK_MANAGEMENT_TOOL
#define TASK_MANAGEMENT_TOOL

#include <stdio.h>

#define strnicmp strncasecmp

#include "task.h"

struct WorkPlan{
	void create();
	void close();
	void add(Task *task);
	void checkAvailableNextTimesFor(Task *delayed);
	int  getUsableDay();
	int getUsableTime();
	void remove(Task *target);
	void display(bool verbose, bool testing);
	void delayAllTasksOfDay(int day);
	Task * getTask(int day, int time);
	bool checkCycledList();

	void controlpriority(Task *, Task *, Task *);
	void make_node(Task *);
	void insertend(Task *);
	void insertbegin(Task *);
	bool checkavailabletime(Task *);
	void checkavailableday(Task *);
	void delaytask(int, int);
	void last_time(Task *);

	
	Task *head;
	int usable_day;
	int usable_time;
	int last_Time;
};
#endif 

