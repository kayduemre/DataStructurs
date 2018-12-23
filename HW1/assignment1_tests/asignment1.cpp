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

	int border_error();
};

typedef operators location;

struct instruction
{
	char instruct;
	int	row;
	int column;
	int move_by;

};

//------------------------------FUNCTIONSPROTOTYPE-------------------------

//bool control_conflict( data **grid,char curent_type, int row, int col, int curent_row, int curent_col, int curent_size)
bool border_error(int row, int col, int curent_row, int curent_col, char curent_type, int curent_size);
//------------------------------MAIN------------------------------

int main(int argc, char *argv[])
{
	//create file pointer to open file
	FILE *fptr;
	fptr = fopen(argv[1], "r+");
	location** grid;
	int row;
	int col;


	

	//fseek(fptr, 0, SEEK_SET);
	fscanf(fptr, "%d%d \n",&row,&col);

	// create dynamic array
	grid = new location *[row];

	for(int i=0;i<row;i++)
	{
		grid[i]=new location[col];
	}
	cout <<"A grid is created:"<< row << col <<endl;

	char curent_type;
	int curent_row;
	int curent_col; 
	int curent_size;
	
	//read and of file
	while (!feof(fptr))
	{	
		// take information from file
		fscanf(fptr, "%s %d %d %d \n",&curent_type, &curent_row, &curent_col, &curent_size);
		
		//check the borer error in function
		if( !(border_error(row, col, curent_row, curent_col, curent_type, curent_size)) )
		{
			if (curent_type == '+')
			{
				for ( int i = (-curent_size); i <= curent_size; i++)
				{

					(grid[row-1] + ((col-1)+i) )->type = curent_type;
					(grid[row-1] + ((col-1)+i) )->size = curent_size;
					(grid[row-1] + ((col-1)+i) )->row = row;
					(grid[row-1] + ((col-1)+i) )->column = col; 
				}

							

							

				for ( int i = (-curent_size); i <= curent_size; i++)
				{
									
					(grid[row-1+i] + (col-1) )->type = curent_type;
					(grid[row-1+i] + (col-1) )->size = curent_size;
					(grid[row-1+i] + (col-1) )->row = row;
					(grid[row-1+i] + (col-1) )->column = col;
				}

			
			}
			if (curent_type == '-')
			{
				for ( int i = (-curent_size); i <= curent_size; i++)
				{

					(grid[row-1] + ((col-1)+i) )->type = curent_type;
					(grid[row-1] + ((col-1)+i) )->size = curent_size;
					(grid[row-1] + ((col-1)+i) )->row = row;
					(grid[row-1] + ((col-1)+i) )->column = col; 
				}
			}
			if (curent_type == '/')
			{
				for ( int i = (-curent_size); i <= curent_size; i++)
				{
					(grid[row-1-i] + ((col-1)+i) )->type = curent_type;
					(grid[row-1-i] + ((col-1)+i) )->size = curent_size;
					(grid[row-1-i] + ((col-1)+i) )->row = row;
					(grid[row-1-i] + ((col-1)+i) )->column = col; 
				}	
			}
			if (curent_type == 'x')
			{
				for ( int i = (-curent_size); i <= curent_size; i++)
				{
					(grid[row-1+i] + ((col-1)+i) )->type = curent_type;
					(grid[row-1+i] + ((col-1)+i) )->size = curent_size;
					(grid[row-1+i] + ((col-1)+i) )->row = row;
					(grid[row-1+i] + ((col-1)+i) )->column = col; 
				}	

				for ( int i = (-curent_size); i <= curent_size; i++)
				{
					(grid[row-1-i] + ((col-1)+i) )->type = curent_type;
					(grid[row-1-i] + ((col-1)+i) )->size = curent_size;
					(grid[row-1-i] + ((col-1)+i) )->row = row;
					(grid[row-1-i] + ((col-1)+i) )->column = col; 
				}
			}
		}
		
	}
		

	return 0;
}
//---------------------------------------------FUNCTIONS------------------------------------------------------------------
bool border_error(int row, int col, int curent_row, int curent_col, char curent_type, int curent_size)
{
	bool hold = false;
	
	if(curent_type == '+')
	{
		if((curent_row + curent_size > row) || (curent_row - curent_size <= 0) ||
			(curent_col + curent_size > col) || ( curent_col - curent_size <= 0))
		{
			cout << "BORDER ERRORS: Operator"<< curent_type << "with size "<< curent_size << "can not be placed on"<< "(" << curent_row << "," << curent_col << ")"<<endl;
			hold = true;
		}
	}
	else if (curent_type == '-')
	{
		if((curent_col + curent_size > col) || (curent_col - curent_size <= 0))
		{
			
			cout << "BORDER ERRORS: Operator"<< curent_type << "with size "<< curent_size << "can not be placed on"<< "(" << curent_row << "," << curent_col << ")"<<endl;
			hold = true;
		}		
	}
	else if (curent_type == '/')
	{
		if ((curent_row + curent_size > row) || (curent_row - curent_size <= 0) ||
			(curent_col + curent_size > col) || ( curent_col - curent_size <= 0) )
		{
			cout << "BORDER ERRORS: Operator"<< curent_type << "with size "<< curent_size << "can not be placed on"<< "(" << curent_row << "," << curent_col << ")"<<endl;
			hold = true;
		}
	}
	else if (curent_type == 'x')
	{
		if((curent_row + curent_size > row) || (curent_row - curent_size <= 0) ||
			(curent_col + curent_size > col) || ( curent_col - curent_size <= 0))
		{
			
			cout << "BORDER ERRORS: Operator"<< curent_type << "with size "<< curent_size << "can not be placed on"<< "(" << curent_row << "," << curent_col << ")"<<endl;
			hold = true;
		}
	}
	return hold;
}

