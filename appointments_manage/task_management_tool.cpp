/* @Author
Student Name: Emre KAYDU
Student ID : 150160552
Date: 4.11.2019 */

#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <iomanip>

#include "task_management_tool.h"

using namespace std; 


void WorkPlan::display(bool verbose,bool testing)
{
	string inone="***";
	if (head!=NULL)
	{
		Task *pivot =new Task;
		Task *compeer =new Task;
			
		pivot=head;
		do
		{
			if(testing)
				inone+=" ";
			else
				cout << pivot->day <<". DAY"<< endl;
			compeer=pivot;
			while(compeer!=NULL)
			{
				string PREV= compeer->previous!=NULL?compeer->previous->name:"NULL";
				string NEXT=compeer->next!=NULL?compeer->next->name:"NULL";
				string CONT=compeer->counterpart!=NULL?compeer->counterpart->name:"NULL";
				if (testing)
					inone+=compeer->name;
				else
					if(verbose)
						cout<<"\t"<<setw(2)<< compeer->time <<":00\t"<< PREV<<"\t<- "<< compeer->name <<"("<< compeer->priority <<")->\t"<<NEXT <<"\t |_"<<CONT<<endl;
					else
						cout<<"\t"<<setw(2)<< compeer->time <<":00\t"<< compeer->name <<"("<< compeer->priority <<")"<<endl;				
				compeer=compeer->counterpart;
			}
			pivot=pivot->next;
		}while(pivot!=head);
		if(testing)
		{
			cout<<inone<<endl;
			cout<<"(checking cycled list:";
			if (checkCycledList())
				cout<<" PASS)"<<endl;
			else
				cout<<" FAIL)"<<endl;
		}
	}
	else
		cout<<"There is no task yet!"<<endl;
}
void WorkPlan::delaytask(int day, int time)
{
	Task *oldone=new Task();
	Task *newone=new Task();
	if (day>0 and time>0)
	{ 
		oldone=getTask(day, time);
		
		if (oldone!=NULL)
		{
			newone->name=new char [strlen(oldone->name)];
			newone->name=oldone->name;
			newone->priority=oldone->priority;
			checkAvailableNextTimesFor(oldone);
			cout<<getUsableDay()<<".day and "<<std::setw(2)<<getUsableTime()<<":00 is the first available day and hour for delaying the task "<<oldone->name<<" that is on "<<oldone->day<<".day at "<<std::setw(2)<< oldone->time <<":00"<<endl;
			newone->day=getUsableDay();
			newone->time=getUsableTime();
			remove(oldone);	
			add(newone);
		}
			
	}
	else
		cout<<"Invalid input!"<<endl;
}
bool WorkPlan::checkavailabletime(Task *receive)
{
	Task *traverse; 
	traverse = receive;
	

	int time = 8;
	bool flag = false;
	if (traverse->time > 8)
	{
		usable_time = time;
		flag = true;
		return flag;
	}
	while (traverse)
	{
		
		if((traverse->time != time) && (time !=17))
		{
			usable_time = time;
			flag = true;
			return flag;
		}
		if( traverse->counterpart == NULL && time !=17)
		{
			time++;
			usable_time = time;
			flag = true;
			return flag;
		}
				
			
		traverse = traverse->counterpart;
		time++;
	}
	return flag;
}
void WorkPlan::checkavailableday(Task *receive)
{
	Task *traverse = receive;

	do
	{
		traverse = traverse->next;
		if (checkavailabletime(traverse))
		{
			usable_day = traverse->day;
			return;
		}
		
	}while (traverse != traverse->previous);
	

}
void WorkPlan::make_node(Task *node)
{

	Task *newnode = new Task;
	*newnode = *node;
	newnode->name = new char[strlen(node->name)];
	strcpy(newnode->name, node->name);
	newnode->next = newnode;
	newnode->previous = newnode;
	newnode->counterpart = NULL;
	head = newnode;

}
void WorkPlan::insertbegin(Task *node)
{
	Task *last = head->previous;
	Task *newnode = new Task;
	*newnode = *node;
	newnode->name = new char[strlen(node->name)];
	strcpy(newnode->name, node->name);
	newnode->next = head;
	newnode->previous = last;
	last->next = newnode;
	head->previous = newnode;
	head = newnode;
	newnode->counterpart = NULL;


}
void WorkPlan::insertend(Task *node)
{
	Task *last = head->previous;
	Task *newnode = new Task;
	*newnode =*node;
	newnode->name = new char[strlen(node->name)];
	strcpy(newnode->name, node->name);

	newnode->next = head;
	head->previous = newnode;
	newnode->previous = last;
	last->next = newnode;
	newnode->counterpart =NULL;

}
int WorkPlan::getUsableDay()
{
	return usable_day;
}

int WorkPlan::getUsableTime()
{
	return usable_time;
}


void WorkPlan::create()
{		
	head = NULL;
}

void WorkPlan::close()
{
	/*
	Task *p, *q;
	while (head)
	{
		p = head;
		head = head->next;
		q = p->counterpart;
		while (q)
		{
			p->counterpart = p->counterpart->counterpart;
			delete q;
			q = p->counterpart;
		}
		delete p;
	}
	*/
	
	
}

void WorkPlan::add(Task *task)
{
	Task *last, *begin;

	Task *newnode = new Task;
	*newnode = *task;
	newnode->name = new char[strlen(task->name)];
	strcpy(newnode->name, task->name);
	newnode->counterpart = NULL;
	newnode->next = NULL;
	newnode->previous = NULL;

	if(head == NULL)
	{
		make_node(newnode);
		return;
	}
	else if(head->day > newnode->day)
	{
		insertbegin(newnode);
		return;
	}
	else if(head->previous->day < newnode->day)
	{
		insertend(newnode);
		return;
	}
	else if (head->day == newnode->day)
	{
		Task *traverse, *tail;
		traverse = head;
		tail = head;
		begin = traverse;
		if ((traverse->time > newnode->time))
		{
			last = head->previous;
			newnode->counterpart = traverse;
			traverse = traverse->next;
			newnode->next = traverse;
			traverse->previous = newnode;
			newnode->previous = last;
			last->next = newnode;
			newnode->counterpart->next = NULL;
			newnode->counterpart->previous = NULL;
			head = newnode;

			return;
		}
		while (traverse && (traverse->time < newnode->time))
		{
			tail = traverse;
			traverse = traverse->counterpart;
		}
		if(traverse && (traverse->time > newnode->time))
		{
			newnode->counterpart = traverse;
			tail->counterpart = newnode;
			return;
		}
		
		if (traverse && (traverse->time == newnode->time))
		{
			if ((traverse->priority > newnode->priority) || (traverse->priority == newnode->priority))
			{
				
				if (checkavailabletime(begin))
				{
					int time = getUsableTime();
					newnode->time = time;
					
					add(newnode);
					
				}
				else
				{
					checkavailableday(begin);
					int time = getUsableTime();
					int day = getUsableDay();
					newnode->time = time;
					newnode->day = day;
					add(newnode);
				}
				
			}
			else if (traverse->priority < newnode->priority)
			{
				Task *node = new Task;
				node->name = new char[strlen(traverse->name)];
				node->name = traverse->name;
				node->priority = traverse->priority;
				node->time = traverse->time;
				traverse->name = new char[strlen(newnode->name)];
				traverse->name = newnode->name;
				traverse->priority = newnode->priority;
				newnode->name = new char[strlen(node->name)];
				newnode->name = node->name;
				newnode->priority = node->priority;
				delete node;
				if (checkavailabletime(begin))
				{
					int time = getUsableTime();
					newnode->time = time;
					add(newnode);
					
				}
				else
				{
					checkavailableday(begin);
					int time = getUsableTime();
					int day = getUsableDay();
					newnode->time = time;
					newnode->day = day;
					add(newnode);
				}
			}

		}
		else
		{
			tail->counterpart = newnode;
			return;
		}		
	}
	else
	{
		Task *traverse, *tail, *last;
		traverse = head;
		last = head;
		while((traverse != last->previous) && (traverse->day < newnode->day))
		{
			tail = traverse;
			traverse = traverse->next;
		}
		if ((traverse != traverse->previous) && (traverse->day > newnode->day))
		{
			newnode->next = traverse;
			tail->next = newnode;
			traverse->previous = newnode;
			newnode->previous = tail;
			return;
		}
		
		
		if((traverse->day == newnode->day))
		{
			if ((traverse->time > newnode->time))
			{
				
				
				newnode->counterpart = traverse;
				traverse = traverse->next;
				newnode->next = traverse;
				tail->next = newnode;
				traverse->previous = newnode;
				newnode->previous = tail;
				return;
				
			}
			
			begin = traverse;
			while ((traverse) && (traverse->time < newnode->time))
			{
				tail = traverse;
				traverse = traverse->counterpart;
			}

			if(traverse && (traverse->time > newnode->time))
			{
				

				newnode->counterpart = traverse;
				tail->counterpart = newnode;
				return;
			}
			if (traverse && (traverse->time == newnode->time))
			{
				if ((traverse->priority > newnode->priority) || (traverse->priority == newnode->priority) )
				{
					if(checkavailabletime(begin))
					{
						int time = getUsableTime();
						newnode->time = time;
						add(newnode);
					}
					else
					{
						checkavailableday(begin);
						int time = getUsableTime();
						int day = getUsableDay();
						newnode->time = time;
						newnode->day = day;
						add(newnode);

					}
					
				}
				else if(traverse->priority < newnode->priority)
				{
					Task *node = new Task;
					node->name = new char[strlen(traverse->name)];
					node->name = traverse->name;
					node->priority = traverse->priority;
					traverse->name = new char[strlen(newnode->name)];
					traverse->name = newnode->name;
					traverse->priority = newnode->priority;
					newnode->name = new char[strlen(node->name)];
					newnode->name = node->name;
					newnode->priority = node->priority;
					delete node;
					
					if(checkavailabletime(begin))
					{
							
						int time = getUsableTime();
						newnode->time = time;
						add(newnode);
					}
					else
					{
						checkavailableday(begin);
						int time = getUsableTime();
						int day = getUsableDay();
						newnode->time = time;
						newnode->day = day;
						add(newnode);
					}
				}
			}
			else
			{
				
				tail->counterpart = newnode;
				return;
			}	
		}
		else
		{
			insertend(newnode);
		}
		
	}
} 

Task * WorkPlan::getTask(int day, int time)
{
	Task *traverse = head, *tail;;
	while (traverse)
	{
		if(traverse->day == day)
		{
			while (traverse && (traverse->time != time))
			{
				tail = traverse;
				traverse = traverse->counterpart;
			}
			if (traverse)
			{
				return traverse;
			}
			else
			{
				return tail;
			}
			
		}
		traverse = traverse->next;
	}
	return traverse;
}

void WorkPlan::last_time(Task *day)
{
	Task *traverse = head,*tail;
	while (traverse->day != day->day)
	{
		cout<<traverse->day;
		traverse = traverse->next;
	}

	while (traverse)
	{
		tail = traverse;
		traverse = traverse->counterpart;
	}
	
	last_Time = tail->time;
	
}
void WorkPlan::checkAvailableNextTimesFor(Task *delayed)	
{	
	Task *traverse = head, *node,*checkhead; 
	node = delayed;
	while (traverse->day != node->day)
	{
		traverse = traverse->next;
	}
	traverse = traverse->next;
	checkhead = traverse->next;
	//while (traverse)
	//{
	//	tail = traverse;
	//	traverse = traverse->counterpart;
	//}
	//int lasttime = tail->time;
	//traverse = checkhead;
	
	int time = 8;
	if (traverse->time > 8)
	{
		usable_time = time;
		usable_day = traverse->day;
		return;
	}
	
	while (traverse)
	{
		time = 8;
		if (traverse->time > 8)
		{
			usable_time = time;
			usable_day = traverse->day;
			return;
		}
		
		while (traverse)
		{
			last_time(traverse);
			if((traverse->time != time) && (time !=17) && (traverse->time != last_Time))
			{
				usable_time = time;
				usable_day = traverse->day;
				return;
			}
			if( traverse->counterpart == NULL && (time !=17) && (traverse->time != last_Time))
			{
				usable_time = time;
				usable_day = traverse->day;
				return;
			}


			traverse = traverse->counterpart;
			time++;
		}
		traverse = checkhead;
		traverse = traverse->next;
	}
	
}

void WorkPlan::delayAllTasksOfDay(int day)
{
	Task *traverse = head;
	while (traverse->day != day)
	{
		traverse = traverse->next;
	}

	while (traverse)
	{
		int day = traverse->day;
		int time = traverse->time;
		delaytask(day, time);
		traverse = traverse->counterpart;
	}
	
	
}

void WorkPlan::remove(Task *target)
{

	Task *tail, *traverse, *targetnode, *last;
	targetnode = new Task;
	*targetnode = *target;
	traverse = head;
	tail = traverse;
	last = head->previous;

	if ((traverse->day == targetnode->day))
	{
		if ((traverse->counterpart == NULL))
		{
			last = traverse->previous;
			traverse = traverse->next;
			last->next = head;
			head->previous = last;
			delete traverse;
			return;
		}
		else if (traverse->time == targetnode->time)
		{	
			//Task *del = traverse;
			last = head->previous;
			traverse = traverse->counterpart;
			//delete del;
			traverse->next = head->next;
			head->next->previous = traverse;
			traverse->previous = last;
			head = traverse;
			last->next = head;
			
			return;
		}
		else
		{
			while (traverse && traverse->time !=targetnode->time)
			{
				tail = traverse;
				traverse = traverse->counterpart;
			}
			if (traverse->counterpart != NULL)
			{
				tail->counterpart = traverse->counterpart;
				delete traverse;
			}
			else
			{
				//Task *del = traverse;
				tail->counterpart = NULL;
				//delete del;
			}
			
		}
		
	}
	else if (last->day == targetnode->day)
	{
		if ((last->counterpart == NULL))
		{
			Task *temp= last;
			last = last->previous;
			last->next = head;
			head->previous = last;
			delete temp;
		}
		else if (last->time == targetnode->time)
		{
			Task *temp= last;
			Task *tail = last->previous;
			last = last->counterpart;
			tail->next = last;
			last->previous = tail;
			last->next = head;
			head->previous = last;
			delete temp;	
		}
		else
		{
			traverse = last;
			if (traverse->time ==targetnode->time)
			{
				Task *temp = traverse;
				traverse = traverse->counterpart;
				traverse->next = temp->next;
				temp->next->previous = traverse;
				traverse->previous = tail;
				tail->next = traverse;
				return;
			}
			while (traverse && traverse->time !=targetnode->time)
			{
				tail = traverse;
				traverse = traverse->counterpart;
			}
			
			if (traverse->counterpart != NULL)
			{
				tail->counterpart = traverse->counterpart;
				delete traverse;
			}
			else
			{
				tail->counterpart = NULL;
				delete traverse;
			}
			
		}
	}
	else
	{
		while (traverse->day != targetnode->day)
		{
			tail = traverse;
			traverse = traverse->next;
		}
		if (traverse->counterpart == NULL)
		{
			traverse = traverse->next;
			tail->next = traverse;
			traverse->previous = tail;
			//delete temp;
			return;
		}
		if (traverse->time == targetnode->time)
		{

			Task *temp = traverse;
			traverse = traverse->counterpart;
			traverse->next = temp->next;
			temp->next->previous = traverse;
			traverse->previous = tail;
			tail->next = traverse;
			return;
		}
		while (traverse && (traverse->time != targetnode->time))
		{
			tail = traverse;
			traverse = traverse->counterpart;
		}
		
		if (traverse != NULL)
		{
			tail->counterpart = traverse->counterpart;
			return;
			//delete traverse;
		}
		else
		{
			tail->counterpart = NULL;
			//delete traverse;
		}
	}
}

bool WorkPlan::checkCycledList()
{				
	Task *pivot=new Task();
	pivot=head;
	int patient=100;
	bool r=false;
	while (pivot!=NULL&&patient>0)
	{		
		patient--;
		pivot=pivot->previous;
		if(pivot==head)
		{
			r=true;
			break;
		}
	}
	cout<<"("<<100-patient<<")";
	patient=100;
	bool l=false;
	while (pivot!=NULL&&patient>0)
	{		
		patient--;
		pivot=pivot->next;
		if(pivot==head)
		{
			l=true;
			break;
		}
	}
	return r&l;
}
