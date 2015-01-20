#ifndef DB_H
#define DB_H

#include <string>
#include <vector>
using namespace std;


/**	
	This class maintains the meta information of the database engine.
	The total number of databases created.
	Housekeeping of meta file.
**/

class DB
{
public:

	/* vector for storing the dbNames*/
	static vector<string> dbNames; 

	/* read the meta file and make the vector of dbNames */
	static init();

	/* add this database to the records */
	static addDB(string dbName);
};


#endif /* end DB_H */