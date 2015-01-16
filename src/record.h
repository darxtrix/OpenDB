#ifndef RECORDS_H
#define RECORDS_H

#include <vector>
#include <tuple>
#include "schema.h"

using namespace std;


/*
	Abstraction class for a database record.
	Manages creating of records with given field values/attributes.
*/

/** Basic record data structure:
-> N(number of attributes) slots of size sizeof(short) with each containing offset
   of the start of each attribute.
-> Using this scheme we do not need to scan the whole record for finding a particular
   attribute..
-> Last slot will point to the end of the record.
-> ith value of the slot array will point to the ith attribute
**/

typedef vector< tuple<string,string> > Atts_list; // list of tuples

class Record
{
private:
	Atts_list myatts;
	short numAtts; // number of attributes in the record
	short* att_offset; // offset of each record at the start of the record block

	// Constructor
	Record();

	// Pass the relation to parse the catalog for that relation
	// Record bits are constructed in the order of fiels in catalog file
	static int makeRecord(string rel,vector< tuple<string,string> > myatts); 

	// returns the value of a given field in the record
	// used in displaying result of SQL query
	static string getAttribute(string field_name);

	// return the list of tuples(field_name,value)
	static Atts_list getAttsList();
	
	// prints the record's attributes to the stdout
	static int printRecord();

	// gives the bit representation of the record
	static char* getBits();

	// construct the record according to the schema
	static int suckRecord(Schema* s,char* fName);

	// Destructor
	~Record();

};

#endif /* end RECORDS_H */