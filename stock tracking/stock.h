/*
 * stock.h
 *
 *  Created on: Oct 8, 2019
 *      Author: emre
 */

#ifndef STOCK_H_
#define STOCK_H_

#include "node.h"

struct stock{
	node *head;

	void create();
	void add_stock(int);
	void sell(int);
	void current_stock();
	void clear();
	void update();
};
void stock::create()
{
	head = NULL;
	//std::cout << "create stock list";
}
void stock::add_stock(int to_add)
{
	
	//std::cout << to_add;
	node *traverse;
	node *tail;

	traverse = head;

	node *newnode = new node;
	newnode->size = to_add;
	newnode->quant = 1;
	newnode->next = NULL;
	
	if(head == NULL)
	{
		head = newnode;
		return;
	}
	else if (head->size > newnode->size)
	{
		newnode->next = head;
		head = newnode;
		return;
	}
	
	while (traverse && (traverse->size < newnode->size))
	{

		tail = traverse;
		traverse = traverse->next;
	}
	if (traverse->size == newnode->size)
	{
		traverse->quant +=1;
		return;
	}
	if (traverse)
	{
		newnode->next = traverse;
		tail->next = newnode;
		
	}
	else
	{
		tail->next = newnode;
	}
}
void stock::current_stock()
{
	node *traverse;
	traverse = head;
	while(traverse)
	{
		std::cout << traverse->size << ":" <<traverse->quant<<std::endl;
		traverse = traverse->next;
	}
}
void stock::sell(int sell)
{
	node *traverse;
	node *tail;

	traverse = head;

	if(head->size == sell)
	{
		head->quant -= 1;
		if(head->quant == 0)
		{
			head = head->next;
			//std::cout << sell << std::endl;
			delete traverse;
			return;
		}
		return;
	}

	while((traverse) && (traverse->size != sell))
	{
		tail = traverse;
		traverse = traverse->next;

	}
	if(traverse)
	{
		traverse->quant -=1;
		if(traverse->quant == 0)
		{
			tail->next = traverse->next;
			delete traverse;
		}
		return;
	}
	else
		std::cout << "NO_STOCK"<<std::endl;

}
void stock::clear()
{
	node *temp;
	while(head)
	{
		temp = head;
		head = head->next;
		delete temp;
	}

}

#endif /* STOCK_H_ */
