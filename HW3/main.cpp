/*
	author: Emre KAYDU

	ID    : 150160552

	DATE  : 21.10.2018
*/

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <fstream>
using namespace std;
struct Node
{
	int deck;
	Node *next;
};
struct Stack
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
int Stack::count()
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
void Stack::create()
{
	head = NULL;
}
bool Stack::isEmpty()
{
	return head == NULL;
}
void Stack::makeEmpty()
{
	Node *p;
	while(head)
	{
		p = head;
		head = head->next;
		delete p;
	}
}
void Stack::push(int toAdd)
{
	Node *newnode = new Node;
	newnode->deck = toAdd;
	newnode->next = head;
	head = newnode;
	
}
int Stack::pop()
{
	if(head == NULL)
		return 0;
	Node *topnode;
	int toReturn;
	topnode = head;
	head = head->next;
	toReturn = topnode->deck;
	delete topnode;
	return toReturn;
}
void Stack::print()
{
	Node *p = head;
	while(p)
	{
		cout <<p->deck;
		p = p->next;
	}
}

int main(int argc, char **argv)
{
    (void)argc;

	Stack player1, player2, table, bin;
	player1.create();
	player2.create();
	bin.create();
	table.create();
	
	ifstream myfile;
	myfile.open(argv[1]);
	int line, i;
	int array[1000];
	if(myfile.is_open())
	{
		while(!myfile.eof())
		{
			myfile >> line;
			array[i] = line;
			i++;
			
		}
	}
	myfile.close();
	int tablesize = array[0];
	int decksize = array[1];
	//initialize table deck
	for(int k = 2; k < 2 + tablesize; k++)
	{
			table.push(array[k]);
	}
	
	//initialize player1 deck
	for(int l = 2 + tablesize; l < 2 + tablesize + decksize;l++)
	{
		player1.push(array[l]);
	}
	//initialize player2 deck
	for(int m = 2 + tablesize + decksize; m < 2 + tablesize + 2*decksize;m++ )
	{
		player2.push(array[m]);
	}

int turn = 0;
bool flag = 0;
int count = 1;

while(!flag)
{
	//print table
	//cout << "--turn" << count << "begins" <<endl;
	//cout << "Cards of table: " << "[";
	//table.print();
	//cout << "]" <<endl;
	
	//print player1
	//cout << "Cards of the first player:" << "[";
	//player1.print();
	//cout << "]"<< endl;
	
	//print player2
	//cout << "Cards of the Second player:"<< "[";
	//player2.print();
	//cout << "]"<< endl;
	
	//print bin
	//cout << "Cards of Bin:" << "[";
	//bin.print();
	//cout << "]"<< endl;
	
	if(turn%2 == 0)
	{
		//to start with player1
		int select = table.pop();
		if(select == 0)
		{
			if(player1.count() > player2.count())
			{
				//cout << "Game ends."<< endl;
				cout << "There are " << bin.count() << " cards in the bin "<< endl;
				flag = 1;
				break;
			}
			else if(player1.count() < player2.count())
			{
				//cout <<"Game ends."<< endl;
				cout << "There are " << bin.count() << " cards in the bin "<< endl;
				flag = 1;
				break;
			}
			
		}
		//is it negative or positive
		else if(select < 0)
		{
			int give = select*(-1);
			//cout << "First player needs to give "<< give << " cards "<< endl;
			for(int i = 0; i < give ;i++)
			{
				int temp2 = player2.pop();
				int temp1 = player1.pop();
				
				if(temp1 == 0 || temp2 == 0)
				{
					//cout << "Game ends." << endl;
					cout << "There are " << bin.count() << " cards in the bin"<< endl;
					flag = 1;
					break;
				}
				else if(temp1 > temp2)
				{
					//cout << temp1 << ">" << temp2 << " is True -> card"<< temp1 << " is given."<<endl;
					player2.push(temp2);
					player2.push(temp1);
				}
				else
				{
					//cout << temp1 << ">" << temp2 << " is False -> card"<< temp1 << " is throw away."<<endl;
					bin.push(temp1);
					player2.push(temp2);
				}
			}
		}
		else if(select > 0)
		{
			int give = select;
			//cout << "Second player needs to give "<< give << " cards "<< endl;
			for(int j = 0; j < give;j++)
			{
				int temp2 = player2.pop();
				int temp1 = player1.pop();
			
				if(temp1 < temp2)
				{
					//cout << temp2 << ">" << temp1 << " is True -> card"<< temp2 << " is given."<<endl;
					player2.push(temp2);
					player2.push(temp1);
				}
				else
				{
					//cout << temp2 << ">" << temp1 << " is False -> card"<< temp2 << " is throw away."<<endl;
					bin.push(temp1);
					player2.push(temp2);
				}
			}
		}
	}
	else if(turn%2 == 1)
	{
		int select = table.pop();
		if(select == 0)
		{
			//cout << "Game ends." << endl;
			cout << "There are " << bin.count() << " cards in the bin"<< endl;
			flag = 1;
			break;
		}
		// second flayer give cards
		if(select < 0)
		{
			int give = select*(-1);
			//cout << "Second player needs to give "<< give << " cards "<< endl;
			for(int x = 0; x < give; x++)
			{
				int temp1 = player1.pop();
				int temp2 = player2.pop();
				if(temp1 == 0 || temp2 == 0)
				{
					//cout << "Game ends." << endl;
					cout << "There are " << bin.count() << " cards in the bin"<< endl;
					flag = 1;
					break;
				}
				if(temp1 < temp2)
				{
					//cout << temp2 << ">" << temp1 << " is True -> card"<< temp2 << " is given."<<endl;
					player1.push(temp1);
					player1.push(temp2);
				}
				else if(temp1 > temp2)
				{
					//cout << temp2 << ">" << temp1 << " is False -> card"<< temp1 << " is throw away."<<endl;
					bin.push(temp2);
					player1.push(temp1);
				}
			}
		}
		else if(select > 0)
		{
			int give = select;
			//cout << "First player needs to give "<< give << " cards "<< endl;
			for(int z = 0; z < give; z++)
			{
				int temp1 = player1.pop();
				int temp2 = player2.pop();
				if(temp1 == 0 || temp2 == 0)
				{
					//cout << "Game ends." << endl;
					cout << "There are " << bin.count() << " cards in the bin"<< endl;
					flag = 1;
					break;
				}
				if(temp1 > temp2)
				{
					//cout << temp1 << ">" << temp2 << " is True -> card"<< temp1 << " is given."<<endl;
					player2.push(temp1);
				}
				else if(temp1 < temp2)
				{
					//cout << temp1 << ">" << temp2 << " is False -> card"<< temp1 << " is throw away."<<endl;
					bin.push(temp1);
					player2.push(temp2);
				}
				
			}
			
		}
		
	}
	count++;
	turn++;
}
return 0;
}
