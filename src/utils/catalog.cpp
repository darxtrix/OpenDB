#include <iostream>
#include <fstream>
#include <sstream>
#include "catalog.h"
#include "../globals.h"


int loadCatalog(char* file_name,string rel,vector<string>& names,vector<string>& types)
{
	ifstream infile(file_name); // input file stream
	string test1,test2,test,att_name,att_type;
	infile >> test1;
	infile >> test2;
	
	while( test1 != "begin" || test2 != rel ) // will break when both matches
	{
		if ( infile.eof() == -1 )
		{
			cout << "Not a valid Catalog file" << endl;
			return NOT_DONE;
		}
		infile >> test1;
		infile >> test2;
	}

	istringstream ss; // wrapper string stream
	infile >> test;

	while( test != "end" )
	{
		ss.str(test);
		ss >> att_name >> att_type;
		names.push_back(att_name);
		types.push_back(att_type);
		infile >> test;
	}
	return DONE;
}







