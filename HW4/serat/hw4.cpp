/* @Author
Student Name: Serhat Demirkıran
Student ID : 150170719
Date: 12/12/18 */

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <fstream>

using namespace std;

struct node
{
	int data;
	node *next;
};

struct queueAnt 
{
	node *head;
	node *tail;
	void create();
	void close();
	void enqueue(int data);
	int dequeue();
	bool isEmpty();
};

struct stackAnt
{
	node *head;
	void create();
	void makeEmpty();
	void push(int data);
	int pop();
	bool isEmpty();
	void print();
};

struct Ants 
{
	queueAnt ants ;
	queueAnt holeDepths ;
	stackAnt hole ;
	void ReadFile ( char *);
	void ShowContents ( bool );
	void CrossRoad ();
	void Close();
};

int main(int argc, char *argv[])
{
	Ants a;
	a.ReadFile(argv[1]);
	cout << "The initial Ant sequence is:";
	a.ShowContents(1);
	cout << "The depth of holes are:";
	a.ShowContents(0);
	a.CrossRoad();
	cout << "The final Ant sequence is:";
	a.ShowContents(1);
	a.Close();

	return 0;
}

void Ants::ReadFile(char* name)
{
	ifstream infile;
	infile.open(name);

	int numberofAnts;
	int Depths;

	infile >> numberofAnts; //read the first line and store it
	ants.create();			//queueAnt type ants has been created
	holeDepths.create();	//queueAnt type holeDepths has been created

	for ( int i = 1; i <= numberofAnts; i++) 	//from 1 to N
	{
		ants.enqueue(i);
	}

	while(infile >> Depths)		//from 1 to M
	{
		holeDepths.enqueue(Depths);
	}
	infile.close();
}

void Ants::ShowContents(bool flag)
{
	if(flag)  //show the content of queueAnt ants
	{
		node *p = ants.head;
		while(p)
		{
			cout << " " << p->data;
			p = p->next;
		}
		cout << " " << endl;
	}

	if(!flag)	//show the content of queueAnt holeDepths
	{
		node *p = holeDepths.head;
		while(p)
		{
			cout << " " << p->data;
			p = p->next;
		}
		cout << " " << endl;
	}
}

void Ants::CrossRoad()
{
	int currentHole;	//next hole depth
	hole.create();		//hole stack data structure has been created

	while( !holeDepths.isEmpty() )	//If there is still number in holeDepths queue
	{
		currentHole = holeDepths.dequeue();

		for ( int i = 0; i < currentHole; i++ )   //repeat depth of hole times
		{
			hole.push(ants.dequeue());		//push ants to the hole
		}

		for ( int i = 0; i < currentHole; i++ )		//repeat same time
		{
			ants.enqueue(hole.pop());		//pop ants from hole and enqueue back to the queueAnt
		}

	}
}

void Ants::Close()
{
	ants.close();
	holeDepths.close();
	hole.makeEmpty();
}




void queueAnt::create()
{
	head = NULL;
	tail = NULL;
}

void queueAnt::close()
{
	node *p;
	while(head)
	{
		p = head;
		head = head->next;
		delete p;
	}
}

bool queueAnt::isEmpty()
{
	return head == NULL;
}

void queueAnt::enqueue(int data)
{
	node *newnode = new node;
	newnode->data = data;
	newnode->next = NULL;

	if(isEmpty())
	{
		tail = newnode;
		head = tail;
	}
	else
	{
		tail->next = newnode;
		tail = newnode;
	}
}



int queueAnt::dequeue()
{
	int temp;

	node *newnode;
	newnode = head;
	head = head->next;

	temp = newnode->data;
	delete newnode;
	return temp;
}

void stackAnt::create()
{
	head = NULL;
}

void stackAnt::push(int data)
{
	node *newnode = new node;
	newnode->data = data;
	newnode->next = head;
	head = newnode;
}

int stackAnt::pop()
{
	node *topnode;
	int temp;
	topnode = head;
	head = head->next;
	temp = topnode->data;
	delete topnode;
	return temp;
}

bool stackAnt::isEmpty()
{
	return head==NULL;
}

void stackAnt::makeEmpty()
{
	node *p;
	while(head)
	{
		p = head;
		head = head->next;
		delete p;
	}
}

void stackAnt::print()
{
	node *p = head;
	while(p)
	{
		cout << p->data << ", ";
		p = p->next;
	}
	cout << endl;
}






