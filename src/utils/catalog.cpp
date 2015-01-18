#include <iostream>
#include <fstream>
#include "catalog.h"
#include "../globals.h"


int loadCatalog(char* file_name,string rel,vector<string>& names,vector<string>& types)
{
	ifstream infile(file_name); // input file stream
	string test1,test2,test;
	infile >> test1;
	infile >> test2;
	
	
	while( test1 != "BEGIN" || test2 != rel ) // will break when both matches
	{
		if ( infile.eof() == -1 )
		{	#ifdef verbose
				cout << "Not a valid Catalog file" << endl;
			#endif
			return NOT_DONE;
		}
		infile >> test1;
		infile >> test2;
	}

	infile >> test; // for reading the Tables/marks.bin line
	
	while( true )
	{
		infile >> test1 >> test2;	
		if ( test1 == "END" )
		{
			break;
		}
		names.push_back(test1);
		types.push_back(test2);
	}
	return DONE;
	
}







