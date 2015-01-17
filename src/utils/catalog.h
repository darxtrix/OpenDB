#ifndef CATALOG_H
#define CATALOG_H

#include <vector>
#include <string>

using namespace std;
/**
-> Parsing functions for the catalog file.
-> Used by the Record class for keeping the information of number of fields in 
   the column to the type of the column.
**/

int loadCatalog(const char* file_name,string rel,vector<string>& names,vector<string>& types);

#endif /* End CATALOG_H */