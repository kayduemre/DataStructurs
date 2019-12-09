/* @Author
Student Name: Emre KAYDU
Student ID : 150160552
Date: 4.11.2019 */
#define NAME_LENGTH 2

struct Task{
	char *name;
	int day;
	int time;
	int priority;

	Task *previous;
	Task *next;
	Task *counterpart;
};
