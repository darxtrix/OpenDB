#ifndef RECORDS_H
#define RECORDS_H

/*
	Abstraction class for a database record.
	Manages creating of records with given field values/attributes, modification of records etc.
*/

/** Basic record data structure:
*  First short will contain the number of attributes of the record according to schema 
*  Maintains an array of
*  1) short(Attribute Type) of the first attribute in the record
*  2) short(Attribute Length) of the former block
**/


struct recAttribute
{
	short attType; // type of the attribute
	short attValue; // value of the attribute
};

typedef struct recAttribute recAttr;

class Record
{
public:
	short numAtts; // number of attributes in the record
	recAttr* atts; // arr representing the records used for printing
	char* rec_bits; // underlying memory of the record

	// returns the bits of the record
	static char* getBits();

	// set the underlying bits of the record from the bits array
	static void setBits(char* bits,int length);

	// copy the Record to the record rec
	static int copyRecord(Record* rec);

	// get the number of attributes in the record
	static int numAtts();

	// prints the record to stdout
	static int printRecord();

	// need to update the record by using schema of the record
	// should be able to add a attribute ?? but length of the attribute changes
	// Use the delimiter way

	/* system catalog should contain the information about the length and type of the 
	records in the table
	??
	*/

};

#endif /* end RECORDS_H */