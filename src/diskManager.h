#ifndef DISKMANAGER_H
#define DISKMANAGER_H

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <sys/types.h>
#include "file.h"
#include "page.h"

using namespace std;

/* 
	Abstraction class for representation of the Disk Manager.
	A Disk Manager instance will do all the allocation/deallocation/resizing of the disk.
	The Disk Manager will have an universal instance only.
*/

/**
-> It will allocate the files by making call to the File Class.
-> Manages the list of open databases.
-> Keeps a hash table between file object pointers and database names.
**/



class DM
{	
public:
	// Maps a database to its file object
	unordered_map<string,File*> dbMap;
	// list of open databases
	vector <string> openList;

	// gets file object by taking a database name
	static File* getFObj(string dbName);

	// creates a database of the given name and the corresponding file
	// it does not open the database 
	static int createDB(string dbName);

	// open the database and if the database is already open doesn't do anything
	static int openDB(string dbName,off_t blockId);

	// reads a page into getMe at a given blockId from the start of the file
	static int readDB(string dbName,Page* getMe,short blockId);

	// writes a page into the file at a given blockId from the start of the file
	static int writeDB(string dbName,Page* addMe,short blockId);

	// closes the database and ask storage manager to flush the memory
	static int closeDB(string dbName);

	// calculates the size of the database
	// ?? read from the header page
	static int sizeDB(string dbName);
 

};

#endif /* end DISKMANAGER_H */