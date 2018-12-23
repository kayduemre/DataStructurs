/***************************************************
 *
 *			  Datasutructure
 *				    HW 1
 *
 *	Name surname : Emre Kaydu
 *  
 *  ID 			 : 150160552
 *
 **************************************************/


//------------------------------LIBRARY---------------------------

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
}location;

struct instruction
{
	char instruct;
	int	row;
	int column;
	int move_by;
};

//------------------------------FUNCTIONSPROTOTYPE-------------------------
void allocate_in_grid(FILE *fptr, char const *argv[], char **grid);

//------------------------------MAIN------------------------------

int main(int argc, char const *argv[])
{
	FILE *fptr;
	fptr = fopen(argv[1], "r");
	char **grid;
	grid = new char *[location.row];

	fseek(fptr, 0, SEEK_SET);
	fscanf(fptr, "%d %d",&location.row,&location.column);

	for(int i=0;i<location.row;i++)
	{
		grid[i]=new char[location.column];
	}
	cout <<"A grid is created:"<< location.row << location.column <<endl;

	allocate_in_grid(fptr, argv[1], grid);

	return 0;
}
void allocate_in_grid(FILE *fptr, char const *argv[1], char **grid)
{
	while(!feof(fptr))
	{
		fscanf(argv[1], "%s %d %d %d", &location.type, &location.row , &location.column, &location.size);
	}
}
