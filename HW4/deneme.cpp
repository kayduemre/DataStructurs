#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;
typedef int QueueDataType;
struct Node
{
	QueueDataType data;
	Node *next;
};
struct Queue
{
	Node *front;
	Node *back;
	void create();
	void close();
	void enqueue(int);
	QueueDataType dequeue();
	bool isempty();
	
};
void Queue::create()
{
	front = NULL;
	back = NULL;
}
void Queue::close()
{
	Node *p;
	while(front)
	{
		p = front;
		front = front->next;
		delete p;
	}
}
void Queue::enqueue(QueueDataType newdata)
{
	Node *newnode = new Node;
	newnode->data = newdata;
	newnode->next = NULL;
	if(isempty())
	{
		back = newnode;
		front = back;
	}
	else
	{
		back->next = newnode;
		back = newnode;
	}
}
QueueDataType Queue::dequeue()
{
	Node *topnode;
	QueueDataType temp;
	topnode = front;
	front = front->next;
	temp = topnode->data;
	delete topnode;
	return temp;
}
bool Queue::isempty()
{
	return front == NULL;
}
struct Customer
{
	int arrival_time;
	int service_duration;
	int waiting_time;
	int leaving_time;
};
void initialize(Customer customers[], int c_count)
{
	int arrival_time = 0;
	srand(time(NULL));
	for (int i = 0; i < c_count; i++)
	{
		customers[i].arrival_time = arrival_time + int(rand()%11);
		customers[i].service_duration = int(1 + rand()%5);
		arrival_time = customers[i].arrival_time;
	}
	
}
void queue_simulation(Queue q, Customer customers[], int c_count)
{
	int system_time = 0;
	int index = 0;
	int left_index;
	int leaving_time = customers[index].arrival_time + customers[index].service_duration;
	
	while(index != c_count || !q.isempty())
	{
		if(leaving_time == system_time)
		{
			left_index = q.dequeue();
			
			customers[left_index].leaving_time = leaving_time;
			customers[left_index].waiting_time = leaving_time - customers[left_index].arrival_time - customers[left_index].service_duration; 
			if(!q.isempty())
			{
				leaving_time = system_time + customers[q.front->data].service_duration;
			}
		}
		while(system_time == customers[index].arrival_time)
		{
			if(q.isempty())
				leaving_time = system_time + customers[index].service_duration;
			q.enqueue(index++);
		}
		system_time++;
	}
}
void print(Customer customers[], int c_count)
{
	cout << "Customer num:\tArrival time\twaiting time:\tservice dur.:\tleaving time:\n";
	cout << "----------\t----------\t------------\t-----------\t---------------\n";
	for (int i = 0; i <c_count; i++)
	{
		cout << i+1 <<"\t\t"
		<< customers[i].arrival_time << "\t\t"
		<< customers[i].waiting_time << "\t\t"
		<< customers[i].service_duration << "\t\t"
		<< customers[i].leaving_time << "\t\t";
		
	}
	
}
int main()
{
	int c_count;
	cout<< "customer"<<endl;
	cin >> c_count;
	struct Customer* customers = new Customer[c_count];
	initialize(customers, c_count);
	
	Queue q;
	q.create();
	queue_simulation(q, customers, c_count);
	print(customers, c_count);
	delete [] customers;
	return 0;
}

