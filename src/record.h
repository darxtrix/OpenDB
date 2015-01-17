#ifndef RECORD_H
#define RECORD_H

#include <iostream>
#include <vector>
#include <tuple>
#include <string>
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
   attribute.
-> Last slot will point to the end of the record.
-> ith value of the slot array will point to the ith attribute
**/

typedef vector<tuple<char,string>> Atts_list; // list of tuples

class Record
{
private:
	Atts_list myatts;
	short numAtts; // number of attributes in the record
	short* att_offset; // offset array for each record at the start of the record block
	vector<string>& names; // attribute names vector
	vector<string>& types; // attribute types vector
	char* rec_block; // underlying memory for the Record object

	// Constructor
	Record(string rel);

	// Pass the relation to parse the catalog for that relation
	// Record bits are constructed in the order of fields in catalog file
	int makeRecord(vector< tuple<char,string> > myatts); 

	// returns the value of a given field in the record
	// used in displaying result of SQL query
	tuple<char,string> getAttribute(string field_name);

	// return the list of tuples(field_type,value)
	Atts_list getAttsList();
	
	// prints the record's attributes to the stdout
	int printRecord();

	// gives the bit representation of the record
	char* getBits();

	// construct the record according to the schema
	// int suckRecord(Schema* s,char* fName);

	// Destructor
	~Record();

};

#endif /* end RECORDS_H */