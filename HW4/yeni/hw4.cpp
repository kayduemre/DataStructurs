
#include <iostream>
#include <fstream>

using namespace std;
typedef int QueueDataType;
struct Node
{
	QueueDataType data;
	Node *next;
};
struct queueAnt
{
	Node *front;
	Node *back;
	void create();
	void close();
	void enqueue(int);
	QueueDataType dequeue();
	bool isempty();
	
};
struct stackAnt
{
	
};
struct Ants {
	queueAnt ants ;
	queueAnt holeDepths ;
	stackAnt hole ;
	void ReadFile (char *);
	void ShowContents ( bool );
	void CrossRoad ();
};
void queueAnt::create()
{
	front = NULL;
	back = NULL;
}
void queueAnt::close()
{
	Node *p;
	while(front)
	{
		p = front;
		front = front->next;
		delete p;
	}
}
void queueAnt::enqueue(int newdata)
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
int queueAnt::dequeue()
{
	Node *topnode;
	int temp;
	topnode = front;
	front = front->next;
	temp = topnode->data;
	delete topnode;
	return temp;
}
bool queueAnt::isempty()
{
	return front == NULL;
}
int main(int argc, char **argv)
{
	(void)argc;
	struct Ants* hole_number = new Ants[4];
	hole_number[0].holeDepths = 1;
	hole_number[1].holeDepths = 9;  
	hole_number[2].holeDepths = 2;  
	hole_number[3].holeDepths = 3;  
  
	
	
	
	
	Ants a ;
	a.ReadFile ( argv [1]); // store the number of ants and depths of holes
	cout << " The initial Ant sequence is : " ;
	a.ShowContents (1); // list ant sequence ( initially : 1 , 2 , ... , N )
	cout << " The depth of holes are : " ;
	a.ShowContents (0); // list depth of holes
	a.CrossRoad ();
	cout << " The final Ant sequence is : " ;
	a.ShowContents (1);
	return 0;
}

