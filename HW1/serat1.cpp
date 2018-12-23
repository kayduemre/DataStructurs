/* @Author
 * Serhat Demirkıran
 * serhat.demirkiran@gmail.com
 */ 


#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstdlib>

#define MAX_LEN 20

struct File
{
	
	char type;
	int center_x;
	int center_y;
	int size;
};

using namespace std;


typedef File data;

void filling( data **points, char type, int row, int column, int size );
void remove(data **points, char type, int row, int column, int size );
bool control_conflict( data **points, char type, int row, int column, int size, int total_row, int total_column );
bool control_border (char type, int row, int column, int size, int total_row, int total_column);



int main ( int argc, char *argv[])
{
	char line[20];
	char type[1];
	int row;
	int column;
	int total_row;
	int total_column;
	int size;
	int move_by;


     
			 				
	
	FILE *fptr;
	FILE *fptr2;
	fptr = fopen(argv[1], "r+" );  //opening grid.txt file in both opening and writing mode
	
	if ( fptr == NULL ) 
	{
		cerr << " Cannot open file " << endl;
		exit(1);
	}
	else  
	{
		fscanf(fptr, "%d%d", &total_row, &total_column); // get the row and column informations from first line in grid.txt
		

		//array of struct pointers

		data** points;

		//allocate dynamic memory

		points = new data*[total_row];
		for ( int i = 0; i < total_row; i++ )
			points[i] = new data[total_column];
		
		//initialize
		
		for (int i = 0; i < total_row; i++)
		{
			for ( int j = 0; j < total_column; j++)
			{
				points[i][j].type = 'O';
			}
		}
		
		
		


		
			
		cout << "A grid is created: " << total_row << " " << total_column << endl;
 
		
		

		while ( fgets( line, MAX_LEN, fptr ) != NULL )
		{
			if ( sscanf(line, "%s%d%d%d", type, &row, &column, &size) == 4 )
			{
				

				if (  control_border(type[0], row, column, size, total_row, total_column)  )
					cerr << "BORDER ERROR: Operator " << type[0] << " with size " << size << " can not be placed on (" << row << "," << column << ")." << endl;

				if ( control_conflict(points, type[0], row, column, size, total_row, total_column)  )
					cerr << "CONFLICT ERROR: Operator " << type[0] << " with size " << size << " can not be placed on (" << row << "," << column << ")." << endl;


					

				if ( !control_border(type[0], row, column, size, total_row, total_column)  )
				{
					if ( !control_conflict(points, type[0], row, column, size, total_row, total_column)  )
					{
						filling( points, type[0], row, column, size );
						cout << "SUCCESS: Operator " << type[0] << " with size " << size << " is placed on (" << row << "," << column << ")." << endl;

					}	
				}	


			}
 		}	
		


		//control
		
		for (int i = 0; i < total_row; i++)
		{
			for ( int j = 0; j < total_column; j++)
			{
				cout << points[i][j].type << "     " ;
			}

			cout << "" << endl;
			cout << "" << endl;
		}
		

		cout << "" << endl;
		cout << "" << endl;
		
		
		
		fclose(fptr);


		


		fptr2 = fopen(argv[2], "r+" );  //opening grid.txt file in both opening and writing mode
	
		if ( fptr2 == NULL ) 
		{
			cerr << " Cannot open file " << endl;
			exit(1);
		}
		else
		{

			while ( fgets( line, MAX_LEN, fptr2 ) != NULL )
			{

				if ( sscanf(line, "%s%d%d%d", type, &row, &column, &move_by) == 4 )
				{
					int new_center_x;
					int new_center_y;
					int new_size = points[row-1][column-1].size;

					
					char new_type = points[row-1][column-1].type;
					int old_center_x = points[row-1][column-1].center_x;
					int old_center_y = points[row-1][column-1].center_y;




					///COMPUTING NEW CENTER

					if(type[2] == 'R')
					{	
						new_center_y = old_center_y + move_by;
						new_center_x = old_center_x;
					}	
					if(type[2] == 'L')
					{	
						new_center_y = old_center_y - move_by;
						new_center_x = old_center_x;

					}	
					if(type[2] == 'U' )
					{	
						new_center_y = old_center_y;
						new_center_x = old_center_x - move_by;

					}	
					if(type[2] == 'D' )
					{	
						new_center_y = old_center_y;
						new_center_x = old_center_x + move_by;

					}	


					

					

					remove( points, new_type, old_center_x, old_center_y, new_size );

					


					if (  control_border(new_type, new_center_x, new_center_y, new_size, total_row, total_column)  ){
						cerr << "BORDER ERROR: " << new_type << " can not be moved from (" << old_center_x << "," << old_center_y << ") to (" << new_center_x << "," << new_center_y << ")."<< endl;
					}

					if ( control_conflict(points, new_type, new_center_x, new_center_y, new_size, total_row, total_column)  )
						cerr << "CONFLICT ERROR: " << new_type << " can not be moved from (" << old_center_x << "," << old_center_y << ") to (" << new_center_x << "," << new_center_y << ")."<< endl;


					

					

					if ( !control_conflict(points, new_type, new_center_x, new_center_y, new_size, total_row, total_column)  )
					{
						if (  !control_border(new_type, new_center_x, new_center_y, new_size, total_row, total_column)  )
						{
							filling( points, new_type, new_center_x,new_center_y, new_size );
							cout << "SUCCESS: " << new_type << " moved from (" << old_center_x << "," << old_center_y << ") to (" << new_center_x << "," << new_center_y << ")."<< endl;


						}	
						else
							filling( points, new_type, old_center_x,old_center_y, new_size );

					}	
					else
						filling( points, new_type, old_center_x,old_center_y, new_size );


					


				}


			}

			fclose(fptr2);


		}  

		


		for (int i = 0; i < total_row; i++)
		{
			for ( int j = 0; j < total_column; j++)
			{
				cout << points[i][j].type << "     " ;
			}

			cout << "" << endl;
			cout << "" << endl;
		}





		for ( int i = 0; i < total_row; i++ )
			delete points[i];
		
		
	}
	
	return EXIT_SUCCESS;
	
}

  

/**
 * takes the operator type, its center coordinates and its size then places on the points
 * @param points two dimensional struct array for grid
 * @param type operator type
 * @param row its x coordinate
 * @param column its y coordinate
 * @param size its size
 */
void filling( data **points, char type, int row, int column, int size )
{

	
	switch(type)
	{


////////////////////////////////////////////////////////////////////////////////////////////////////////

		case '+':

				for ( int i = (-size); i <= size; i++)
				{

					(points[row-1] + ((column-1)+i) )->type = type;
					(points[row-1] + ((column-1)+i) )->size = size;
					(points[row-1] + ((column-1)+i) )->center_x = row;
					(points[row-1] + ((column-1)+i) )->center_y = column; 
				}

							

							

				for ( int i = (-size); i <= size; i++)
				{
									
					(points[row-1+i] + (column-1) )->type = type;
					(points[row-1+i] + (column-1) )->size = size;
					(points[row-1+i] + (column-1) )->center_x = row;
					(points[row-1+i] + (column-1) )->center_y = column;
				}

				break;

////////////////////////////////////////////////////////////////////////////////////////////////////////////

		case '-':


				for ( int i = (-size); i <= size; i++)
				{

					(points[row-1] + ((column-1)+i) )->type = type;
					(points[row-1] + ((column-1)+i) )->size = size;
					(points[row-1] + ((column-1)+i) )->center_x = row;
					(points[row-1] + ((column-1)+i) )->center_y = column; 
				}

				break;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////				
		
		case 'x':

				for ( int i = (-size); i <= size; i++)
				{
					(points[row-1+i] + ((column-1)+i) )->type = type;
					(points[row-1+i] + ((column-1)+i) )->size = size;
					(points[row-1+i] + ((column-1)+i) )->center_x = row;
					(points[row-1+i] + ((column-1)+i) )->center_y = column; 
				}	

				for ( int i = (-size); i <= size; i++)
				{
					(points[row-1-i] + ((column-1)+i) )->type = type;
					(points[row-1-i] + ((column-1)+i) )->size = size;
					(points[row-1-i] + ((column-1)+i) )->center_x = row;
					(points[row-1-i] + ((column-1)+i) )->center_y = column; 
				}	

				break;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		case '/':
		
				for ( int i = (-size); i <= size; i++)
				{
					(points[row-1-i] + ((column-1)+i) )->type = type;
					(points[row-1-i] + ((column-1)+i) )->size = size;
					(points[row-1-i] + ((column-1)+i) )->center_x = row;
					(points[row-1-i] + ((column-1)+i) )->center_y = column; 
				}	

				break;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////		

	}						

							
}

/**
 * takes operator type, its center coordinates, its size and grid then removes it from grid
 * @param points our grid
 * @param type operator 
 * @param row x coordinate
 * @param column y coordinate
 * @param size how big the operator
 */
void remove(data **points, char type, int row, int column, int size )
{

	
	switch(type)
	{


////////////////////////////////////////////////////////////////////////////////////////////////////////

		case '+':

				for ( int i = (-size); i <= size; i++)
				{

					(points[row-1] + ((column-1)+i) )->type = 'O';
					(points[row-1] + ((column-1)+i) )->size = 0;
					(points[row-1] + ((column-1)+i) )->center_x = 0;
					(points[row-1] + ((column-1)+i) )->center_y = 0; 
				}

							

							

				for ( int i = (-size); i <= size; i++)
				{
									
					(points[row-1+i] + (column-1) )->type = 'O';
					(points[row-1+i] + (column-1) )->size = 0;
					(points[row-1+i] + (column-1) )->center_x = 0;
					(points[row-1+i] + (column-1) )->center_y = 0;
				}

				break;

////////////////////////////////////////////////////////////////////////////////////////////////////////////

		case '-':


				for ( int i = (-size); i <= size; i++)
				{

					(points[row-1] + ((column-1)+i) )->type = 'O';
					(points[row-1] + ((column-1)+i) )->size = 0;
					(points[row-1] + ((column-1)+i) )->center_x = 0;
					(points[row-1] + ((column-1)+i) )->center_y = 0; 
				}

				break;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////				
		
		case 'x':

				for ( int i = (-size); i <= size; i++)
				{
					(points[row-1+i] + ((column-1)+i) )->type = 'O';
					(points[row-1+i] + ((column-1)+i) )->size = 0;
					(points[row-1+i] + ((column-1)+i) )->center_x = 0;
					(points[row-1+i] + ((column-1)+i) )->center_y = 0; 
				}	

				for ( int i = (-size); i <= size; i++)
				{
					(points[row-1-i] + ((column-1)+i) )->type = 'O';
					(points[row-1-i] + ((column-1)+i) )->size = 0;
					(points[row-1-i] + ((column-1)+i) )->center_x = 0;
					(points[row-1-i] + ((column-1)+i) )->center_y = 0; 
				}	

				break;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		case '/':
		
				for ( int i = (-size); i <= size; i++)
				{
					(points[row-1-i] + ((column-1)+i) )->type = 'O';
					(points[row-1-i] + ((column-1)+i) )->size = 0;
					(points[row-1-i] + ((column-1)+i) )->center_x = 0;
					(points[row-1-i] + ((column-1)+i) )->center_y = 0; 
				}	

				break;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////		

	}						


}

/**
 * It checks whether the operator fits into the grid or not
 * @param type operator
 * @param row x coordinate
 * @param column y coordinate
 * @param size a number in the interval 1-9
 * @param total_row total number of row of grid
 * @param total_column  total number of column of grid
 * @return true at least one cell of the operator is placed outside of the grid
 */
bool control_border(char type, int row, int column, int size, int total_row, int total_column)
{
	bool temp = false;

	switch(type)
	{

		case '+':
		case 'x':
		case '/':
			if ( (row - size <= 0) || (row + size > total_row) || (column - size <= 0) || (column + size > total_column) )	
			{
				temp = true;
				break;
			}

		case '-':

			if ( (column - size <= 0) || (column + size > total_column) )	
			{
				temp = true;
				break;
			}		

	}

	return temp;


}



/**
 * It checks whether the cells were occupied by another previosly placed operator or not
 * @param points array of cells
 * @param type operator
 * @param row x coordinate
 * @param column y coordinate
 * @param size a number in the interval 1-9
 * @param total_row total number of row of grid
 * @param total_column  total number of column of grid
 * @return true if there is a conflict
 */
bool control_conflict( data **points, char type, int row, int column, int size, int total_row, int total_column )
{

	
	/////// copying points struct to new struct and raising its dimensions for not getting segmentation error during execute

	data** newpoints;
	newpoints = new data*[total_row*3];

	for ( int i = 0; i < total_row*3; i++ )
		newpoints[i] = new data[total_column*3];


	

	for (int i = 0; i < total_row; i++)
		{
			for ( int j = 0; j < total_column; j++)
			{
				newpoints[i+total_row][total_column+j] = points[i][j];
			}
		}


	///shifting the rows and columns

	row = row + total_row;
	column = column + total_column;	


	bool temp = false;	
	
	switch(type)
	{	


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		case '+':
		
				for ( int i = (-size); i <= size; i++)
				{
								

					if (newpoints[row-1][(column-1)+i].type == '+' || newpoints[row-1][(column-1)+i].type == '-' || newpoints[row-1][(column-1)+i].type == 'x' || newpoints[row-1][(column-1)+i].type == '/')
					{
							temp = true;
							break;
									
					}	

				}

				for ( int i = (-size); i <= size; i++)
				{
								

					if (newpoints[(row-1)+i][column-1].type == '+' || newpoints[(row-1)+i][column-1].type == '-' || newpoints[(row-1)+i][column-1].type == 'x' || newpoints[(row-1)+i][column-1].type == '/')
					{
							temp = true;
							break;
									
					}	

				}


				break;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		case '-':
		

			for ( int i = (-size); i <= size; i++)
				{
								
					if (newpoints[row-1][(column-1)+i].type == '+' || newpoints[row-1][(column-1)+i].type == '-' || newpoints[row-1][(column-1)+i].type == 'x' || newpoints[row-1][(column-1)+i].type == '/')
					{
							temp = true;	
							break;	
					}	
				}
				
			break;	
		
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		case 'x':
		

				for ( int i = (-size); i <= size; i++)
				{
								

					if (newpoints[row-1+i][(column-1)+i].type == '+' || newpoints[row-1+i][(column-1)+i].type == '-' || newpoints[row-1+i][(column-1)+i].type == 'x' || newpoints[row-1+i][(column-1)+i].type == '/')
					{
						
							temp = true;
							break;
									
					}	

				}

				for ( int i = (-size); i <= size; i++)
				{
								

					if (newpoints[row-1-i][(column-1)+i].type == '+' || newpoints[row-1-i][(column-1)+i].type == '-' || newpoints[row-1-i][(column-1)+i].type == 'x' || newpoints[row-1-i][(column-1)+i].type == '/')
					{
						
							temp = true;
							break;
									
					}	

				}


				break;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		case '/':

				for ( int i = (-size); i <= size; i++)
					{
						if (newpoints[(row-1)-i][column-1+i].type == '+' || newpoints[(row-1)-i][column-1+i].type == '-' || newpoints[(row-1)-i][column-1+i].type == 'x' || newpoints[(row-1-i)+i][column-1+i].type == '/')
						{

								temp = true;
								break;
						}	

					}

				
				break;	

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	}						

	for ( int i = 0; i < total_row * 3; i++ )
					delete newpoints[i];
	
	return temp;			

}
