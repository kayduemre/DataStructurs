//============================================================================
//
// Student Name      : Emre Kaydu
// Student ID     	 : 150160552
// Date				 : 8.10.2019
//
//============================================================================

#include <iostream>
#include <string>
#include <fstream>

#include "stock.h"

using namespace std;

int main(int argc, char const *argv[])
{

	stock stocklist;
	stocklist.create();

	ifstream file(argv[1]);

	if(file.is_open())
	{
		int line;;
		while(file >>line)
		{
			//cout << line<<endl;
			if(line > 0)
			{
				stocklist.add_stock(line);
			}
			else if(line < 0)
			{
				int sell = -1*line;
				stocklist.sell(sell);

			}
			else if(line == 0)
			{	
				stocklist.current_stock();
			}
		}
	}
	else
	{
		cout << "Failed to open file..";
	}
	file.close();
	stocklist.clear();

	return 0;
}
