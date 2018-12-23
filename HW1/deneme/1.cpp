#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

//------------------------------STRUCTS---------------------------

struct operators
{
	char type;
	int row;
	int column;
	int size;

	int border_error();
}location;

struct instruction
{
	char instruct;
	int	row;
	int column;
	int move_by;

	operators* center;
}deneme;

int main()
{
	location.type = &'+';
	location.row[1] = 4;
	location.column = 3;
	location.size = 3;
	
	int array[20];
	deneme.center = &location;
	array[1] = deneme.center;

	cout <<"edfr"<< deneme.center[1]->row[1];
	location.type = '*';
	location.row[2] = 22;
	location.column = 23;
	location.size = 2;

	deneme.center = &location;
	array[1] = deneme.center;
	

	cout <<"edfr"<< array[1]->row[1];
	cout <<"edfr"<< array[2]->row[1];


	return 0;
}