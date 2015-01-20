#include "globals.h"
#include "file.h"
#include "diskManager.h"

File* DM::getFObj(string dbName)
{
	if ( dbMap.count(dbName) == 1 )
	{
		auto itr = dbMap.find(dbName);
		return itr->second;
	}
	else
	{
		#ifdef verbose
			cerr << "No such database file exist" << endl;
		#endif
		return NULL; // File doesn't exist
	}
}

int DM::createDB(string dbName)
{
	File fl = new File(); // we are allocating this dynamically, should delete this
	if (fl)
	{
		File* fl_ptr = &fl;
		fl.createDb(dbName.c_str());
		delete fl_ptr;
		return DONE;
	}
	else
	{
		cerr << "Insufficient Memory" << endl;
		return NOT_DONE;
	}	
}

int DM::openDB(string dbName,off_t blockId)
{
	File fl = new File(); // it will be deleted in the closeDB
	fl.openDb(blockId,dbName.c_str());
	File* fl_ptr = &fl;
	dbMap[dbName] = fl_ptr;
	openList.push_back(dbName);
	return DONE;
}

int DM::closeDB(string dbName)
{
	auto itr = openList.find(openList.begin(),openList.end(),dbName);
	auto end = openList.end();
	if ( itr == openList.end() && !(*end.equals(dbName)) )
	{
		cerr << " No such database file is open !!" << endl;
		return NOT_DONE;
	}
	else // we found a match
	{
		File* file_ptr = dbMap.find(dbName)->second;
		(*file_ptr).close(); 
		// ?? it will return the number of pages in the file
		// ?? write this information in the header page
		delete *file_ptr;
		// remove from dbMap and openList
		// use erase by value
		openList.erase(dbName);
		dbMap.erase(dbName);
		return DONE;
	}
}

int DM::readDB(string dbName,Page* getMe,short blockId)
{
	if ( openList.find(openList.begin(),openList.end(),dbName) ) // the db is open
	{
		File* fl_ptr = dbMap.find(dbName)->second;
		(*fl_ptr).getPage(getMe,blockId);
		return DONE;
	}
	else
	{
		#ifdef verbose
			cerr << "Database not found in openList." << endl;
		#endif
		return NOT_DONE;
	}
}

int DM::writeDB(string dbName,Page* addMe,short blockId)
{
	if ( openList.find(openList.begin(),openList.end(),dbName) ) // the db is open
	{
		File* fl_ptr = dbMap.find(dbName)->second;
		(*fl_ptr).addPage(addMe,blockId);
		return DONE;
	}
	else
	{
		#ifdef verbose
			cerr << "Database not found in openList." << endl;
		#endif
		return NOT_DONE;
	}
}

int DM::sizeDB(string dbName)
{
	// ?? read from the header page
	// Review later
}
