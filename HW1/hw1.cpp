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
	int columb;
	int size;
};

struct instruction
{
	char instruct;
	int	row;
	int column;
	int move_by;
};

typedef operators data;
//------------------------------FUNCTIONSPROTOTYPE-------------------------

void border_error(char **grid, int col, int row, struct operators x, int sizes);

//------------------------------MAIN------------------------------

int main()
{
	//mat.create();
	FILE *fptr;
	fptr = fopen("grid.txt", "r+");
	
	int row;
	int col;
	data** grid;
	

	fseek(fptr, 0, SEEK_SET);
	fscanf(fptr, "%d %d", &row, &col);
	grid = new data *[row];
	for(int i=0;i<row;i++)
	{
		grid[i]= new data[col];
	}
	
	cout <<"A grid is created:"<< row << col<<endl;

	struct operators x;

	
	while (!feof(fptr))
	{
		fscanf(fptr, "%s %d %d %d", &x.type, &x.row, &x.columb, &x.size);
		int rows = x.row;
		int columbs = x.columb;
		int sizes = x.size;


		if (x.type == '+')
		{
			for (int i = 0; i < sizes; ++i)
			{
				//eround of operator

				//1.condition
				if(grid[rows - i][columbs] == '+' || grid[rows - i][columbs] == '-' ||
				   grid[rows - i][columbs] == '/' || grid[rows - i][columbs] == 'X' ||
				   grid[rows][columbs] == '+')
				{
					grid[rows][columbs] = '+'; // grid center
					record[rows][columbs] = "+"
					grid[rows - i][columbs] = '+';	
				}
				else
				{
					cout << "CONFLICT ERRORS: Operator"<< x.type << "with size "<< sizes << "can not be placed on"<< "(" << i << "," << j << ")";
					break ;
				}

				//2.conditions
				if(grid[rows][columbs - i] == '+' || grid[rows][columbs - i] == '-' ||
				   grid[rows][columbs - i] == '/' || grid[rows][columbs - i] == 'X')
				{
					grid[rows][columbs - i] = '+';
				}
				else
				{
					cout << "CONFLICT ERRORS: Operator"<< x.type << "with size "<< sizes << "can not be placed on"<< "(" << i << "," << j << ")";
					break ;
				}

				//3.conditions
				if(grid[rows + i][columbs] == '+' || grid[rows + i][columbs] == '-' ||
				   grid[rows + i][columbs] == '/' || grid[rows + i][columbs] == 'X' )
				{
					grid[rows + i][columbs] = '+';
				}
				else
				{
					cout << "CONFLICT ERRORS: Operator"<< x.type << "with size "<< sizes << "can not be placed on"<< "(" << i << "," << j << ")";
					break ;
				}

				//4.conditions
				if(grid[rows][columbs + i] == '+' || grid[rows][columbs + i]== '-' ||
				   grid[rows][columbs + i] == '/' || grid[rows][columbs + i] == 'X')
				{
					grid[rows][columbs + i] = '+';
				}
				else
				{
					cout << "CONFLICT ERRORS: Operator"<< x.type << "with size "<< sizes << "can not be placed on"<< "(" << i << "," << j << ")";
					break ;
				}
			}

			//check the border error
			border_error(grid, col, row, x, sizes);

		}
		else if (x.type == '-')
		{
			for (int i = 0; i < sizes; ++i)
			{


				//1.condition
				if(grid[rows][columbs + i] == '+' || grid[rows][columbs + i] == '-' ||
				   grid[rows][columbs + i]  == '/' || grid[rows][columbs + i] == 'X' ||
				   grid[rows][columbs] == '-')
				{
					// grid center
					grid[rows][columbs] = '-';
					record[rows][columbs] = "-"
					grid[rows][columbs + i] = '-';	
				}
				else
				{
					cout << "CONFLICT ERRORS: Operator"<< x.type << "with size "<< sizes << "can not be placed on"<< "(" << i << "," << j << ")";
					break ;
				}

				//2.conditions
				if(grid[rows][columbs - i] == '+' || grid[rows][columbs - i] == '-' ||
				   grid[rows][columbs - i] == '/' || grid[rows][columbs - i] == 'X')
				{
					grid[rows][columbs - i] = '-';
				}
				else
				{
					cout << "CONFLICT ERRORS: Operator"<< x.type << "with size "<< sizes << "can not be placed on"<< "(" << i << "," << j << ")";
					break ;
				}	
			}

			//check the border error
			border_error(grid, col, row, x, sizes);
		}
		else if (x.type == '/')
		{
			for (int i = 0; i < sizes; ++i)
			{
					//1.condition
				if(grid[rows - i][columbs + i] == '+' || grid[rows - i][columbs + i] == '-' ||
				   grid[rows - i][columbs + i] == '/' || grid[rows - i][columbs + i] == 'X' ||
				   grid[rows][columbs] == '-')
				{
					// grid center
					grid[rows][columbs] = '/';
					record[rows][columbs] = "/"
					grid[rows - i][columbs + i] = '/';
				}
				else
				{
					cout << "CONFLICT ERRORS: Operator"<< x.type << "with size "<< sizes << "can not be placed on"<< "(" << i << "," << j << ")";
					break ;
				}

				//2.conditions
				if(grid[rows + i][columbs - i] == '+' || grid[rows + i][columbs - i]  == '-' ||
				   grid[rows + i][columbs - i]  == '/' || grid[rows + i][columbs - i]  == 'X')
				{
					grid[rows + i][columbs - i] = '/';
				}
				else
				{
					cout << "CONFLICT ERRORS: Operator"<< x.type << "with size "<< sizes << "can not be placed on"<< "(" << i << "," << j << ")";
					break ;
				}	
			}

			//check the border error
			border_error(grid, col, row, x, sizes);	
		}
		else if (x.type == 'x')
		{
			for (int i = 0; i < sizes; ++i)
			{

				//1.condition
				if(grid[rows - i][columbs + i] == '+' || grid[rows - i][columbs + i] == '-' ||
				   grid[rows - i][columbs + i] == '/'|| grid[rows - i][columbs + i]  == 'X' ||
				   grid[rows][columbs] == 'x')
				{
					grid[rows][columbs] = 'x'; // grid center
					record[rows][columbs] = "x"
					grid[rows - i][columbs + i] = 'x';	
				}
				else
				{
					cout << "CONFLICT ERRORS: Operator"<< x.type << "with size "<< sizes << "can not be placed on"<< "(" << i << "," << j << ")";
					break ;
				}

				//2.conditions
				if(grid[rows - i][columbs - i] == '+' || grid[rows - i][columbs - i] == '-' ||
				   grid[rows - i][columbs - i] == '/' || grid[rows - i][columbs - i] == 'X')
				{
					grid[rows - i][columbs - i] = 'x';
				}
				else
				{
					cout << "CONFLICT ERRORS: Operator"<< x.type << "with size "<< sizes << "can not be placed on"<< "(" << i << "," << j << ")";
					break ;
				}

				//3.conditions
				if(grid[rows + i][columbs - i] == '+' || grid[rows + i][columbs - i] == '-' ||
				   grid[rows + i][columbs - i] == '/' || grid[rows + i][columbs - i] == 'X')
				{
					grid[rows + i][columbs - i] = 'x';
				}
				else
				{
					cout << "CONFLICT ERRORS: Operator"<< x.type << "with size "<< sizes << "can not be placed on"<< "(" << i << "," << j << ")";
					break ;
				}

				//4.conditions
				if(grid[rows + i][columbs + i] == '+' || grid[rows + i][columbs + i] == '-' ||
				   grid[rows + i][columbs + i] == '/' || grid[rows + i][columbs + i]== 'X')
				{
					grid[rows + i][columbs + i] = 'x';
				}
				else
				{
					cout << "CONFLICT ERRORS: Operator"<< x.type << "with size "<< sizes << "can not be placed on"<< "(" << i << "," << j << ")";
					break ;
				}
			}

			//check the border error
			border_error(grid, col, row, x, sizes);
		}
		
	}

	fclose(fptr);

	// instructions_file_name.txt

	FILE *fptr2;
	fptr2 = fopen("instructions.txt", "r+");

	struct instruction y;
	while (!eof(fptr2))
	{
		fscanf(fptr, "%c %d %d %d", &y.instruct, &y.row, &y.column, &y.move_by);
		if (y.instruct == "MVR")
		{
			if(center_record[y.row][y.column] == "+" || center_record[y.row][y.column] == "-" || 
			   center_record[y.row][y.column] == "/" || center_record[y.row][y.column] == "x")
			{
				//cout << BORDER ERROR: type can not be moved from (row_c,column_c) to (row_n,column_n).
			}
			else
			{
				//cout << SUCCESS: type moved from (row_c,column_c) to (row_n,column_n).

				
			}
		}
		else if (y.instruct == "MVL")
		{
			/* code */
		}
		else if (y.instruct == "MVU")
		{
			/* code */
		}
		else if (y.instruct == "MVD")
		{
			/* code */
		}
	}
	


	getchar();
}

void border_error(char **grid, int col, int row, int sizes)
{

	for (int i = 0; i < row + 1; ++i)
	{
		for (int j = 0; j < col + 1; ++j)
		{
			if(grid[i][j] == '+')
			{
				cout << "BORDER ERROR: Operator"<< x.type << "with size "<< sizes << "can not be placed on"<< "(" << i << "," << j << ")";
			}
				
		}
	}
}
