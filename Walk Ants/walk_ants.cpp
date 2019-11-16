/* @Author
	Student Name: Emre KAYDU
	Student ID : 150160552
	Date: 6.12.2018 */
#include <iostream>
#include <fstream>


using namespace std;
//***********************STRUCTS****************************************
struct Node
{
	int data;
	Node *next;
};
struct queueAnt
{
	Node *front;
	Node *back;
	void create();
	void close();
	void enqueue(int);
	int dequeue();
	bool isempty();
	
};
struct stackAnt
{
	Node *head;
	int count();
	void create();
	void makeEmpty();
	void push(int);
	int pop();
	bool isEmpty();
	void print();
	
};
struct Ants {
	queueAnt ants;
	queueAnt holeDepths;
	stackAnt hole;
	void ReadFile (char *);
	void ShowContents (bool );
	void CrossRoad ();
};
//*****************************STACK_ANT_FUNTİONS***********************
int stackAnt::count()
{
	int win = 0;
	Node *p = head;
	while(p)
	{
		p = p->next;
		win++;
	}
	return win;
}
void stackAnt::create()
{
	head = NULL;
}
bool stackAnt::isEmpty()
{
	return head == NULL;
}
void stackAnt::makeEmpty()
{
	Node *p;
	while(head)
	{
		p = head;
		head = head->next;
		delete p;
	}
}
void stackAnt::push(int toAdd)
{
	Node *newnode = new Node;
	newnode->data = toAdd;
	newnode->next = head;
	head = newnode;
	
}
int stackAnt::pop()
{
	if(head == NULL)
		return 0;
	Node *topnode;
	int toReturn;
	topnode = head;
	head = head->next;
	toReturn = topnode->data;
	delete topnode;
	return toReturn;
}
void stackAnt::print()
{
	Node *p = head;
	while(p)
	{
		cout <<p->data<<" ";
		p = p->next;
	}
}
//***********************************ANT_FUNCTİONS**********************
void Ants::ReadFile(char *argv)
{
	ants.create();
	holeDepths.create();
	ifstream myfile;
	myfile.open(argv);
	
	int content;
	int line = 1;
	myfile >> content;
	
	while(line <= content)
	{
		ants.enqueue(line);
		line++;
	}
	for( ;myfile >> content;)
	{
		holeDepths.enqueue(content);
	}
	myfile.close();
}
void Ants::ShowContents(bool bol)
{
	if(bol == 0)
	{
		Node *p = holeDepths.front;
		while(p)
		{
			cout <<" "<<p->data;
			p = p->next;
		}
		cout << " "<< endl;
	}
	if(bol == 1)
	{
		Node *p = ants.front;
		while(p)
		{
			cout <<" "<<p->data;
			p = p->next;
		}
		cout <<" "<< endl;
	}
}
void Ants::CrossRoad ()//move to ants
{
	hole.create();
	int current = 0;
	
	while(!holeDepths.isempty())
	{
		current = holeDepths.dequeue();
		for(int i = 0; i < current; i++ )  
		{
			int temp = ants.dequeue();
			hole.push(temp);		
		}

		for(int i = 0; i < current; i++ )		
		{
			int temp2 = hole.pop();
			ants.enqueue(temp2);		
		}
	}
}

//***********************************QUEUE_FUNCTİONS********************
void queueAnt::create()// create new node
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
void queueAnt::enqueue(int newdata)// add begin of list
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
int queueAnt::dequeue()//remove end of list
{
	Node *topnode;
	int temp;
	topnode = front;
	front = front->next;
	temp = topnode->data;
	delete topnode;
	return temp;
}
bool queueAnt::isempty()//check whether it is empty
{
	bool flag = 0;
	if(front == NULL)
	{
		flag = 1;
	}
	return flag;
}
//*****************************MAIN*************************************
int main(int argc, char**argv)
{
	(void)argc;
		
	Ants a ;
	a.ReadFile ( argv [1]); // store the number of ants and depths of holes
	cout << "The initial Ant sequence is:";
	a.ShowContents (1); // list ant sequence ( initially : 1 , 2 , ... , N )
	cout << "The depth of holes are:";
	a.ShowContents (0); // list depth of holes
	a.CrossRoad ();
	cout << "The final Ant sequence is:";
	a.ShowContents (1);
	return 0;
}
