#ifndef DB_H
#define DB_H

#include <unordered_map>
#include <string>
#include <vector>

/* 	
	A database is represented by an instance of the DB class.
	Class variables of the DB class has all the information of the total databases present
	and about their files.
	Maps instances of the DB class to the instances of the DBFile class.
	Keeps the space map.
*/
using namespace std;

static vector<string> dbNames; /* vector for storing the dbNames*/
static unordered_map<string,string> dbMap; /* maps an element of dbName to it's memory location*/
/* variables are made static to reduce to this file only */
/* Only the files which include this file can see them */

class DB
{
public:
	string db_name; /* name of the DB */

	/* Constructor */
	DB(string name);

	/* Destructor */
	~DB();

	/* Returns the location of the database file */
	string getDBLocation();
};


#endif /* end DB_H */