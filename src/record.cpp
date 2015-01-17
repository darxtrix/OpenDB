#include "record.h"
#include "utils/catalog.h"
#include "utils/page_utils.h"
#include "globals.h"

Record::Record(string rel,vector<string> a,vector<string> b):names(a),types(b)
{
	// catalog parsing

	this->names = a;
	this->types = b;

	const char* catalog = "catalog"; // name of the catalog
	loadCatalog(catalog,rel,names,types); // flooded names and types
	this->numAtts = names.size();
	this->att_offset = new short[this->numAtts+1];
	this->myatts = {};
	this->rec_block = NULL;
}

int Record::makeRecord(vector< tuple<char,string> > myatts)
{
	this->myatts = myatts;

	short arr_size = sizeof(short)*(this->numAtts+1);
	this->att_offset[0] = arr_size;

	// finding the record size for initialising the underlying storage
	short rec_size = arr_size;
	for( int ctr = 0 ; ctr < this->numAtts ; ctr++ )
	{
		char _type = get<0>(this->myatts[ctr]); // type of the attribute
		// checking the type of the attribute
		switch(_type)
		{
			case INT_T: // it is int
				rec_size += sizeof(int);
				break;
			case DOUBLE_T: // it is double
				rec_size += sizeof(double);
				break;
			default: // it is date or string
				rec_size += get<1>(this->myatts[ctr]).length();

			this->att_offset[ctr+1] += rec_size;
		}
	}

	this->rec_block = new char[rec_size]; // initialising the block_memory
	// writing the offset array
	writeShort(rec_block,0,att_offset[0]); // write the offset of the first attribute
	for ( short ctr = 0 ; ctr < this->numAtts ; ctr++ )
	{
		writeShort(rec_block,(ctr+1)*sizeof(short),att_offset[ctr+1]);
		char _type = get<0>(this->myatts[ctr]);
		string _val = get<1>(this->myatts[ctr]);
		switch(_type)
		{
			// write the attributes
			case INT_T: // integer
				writeInt(rec_block,att_offset[ctr],stoi(_val));
				break;
			case DOUBLE_T:
				writeDouble(rec_block,att_offset[ctr],stod(_val));
				break;
			default:
				writeBytes(rec_block,att_offset[ctr],_val.length(),_val.c_str());
		}
	}
	return DONE;
}

// it is assumed that the records are in the same order as the fields are in names
tuple<char,string> Record::getAttribute(string field_name)
{
	tuple <char,string> retValue;
	auto itr1 = this->names.begin();
	auto itr2 = this->myatts.begin();
	for(  ; itr1 != this->names.end() && itr2 != this->myatts.end() ; itr1++,itr2++ )
	{
		if ( (*itr1).compare(field_name) == 0 ) // match found
		{
			retValue = make_pair(get<0>(*itr2),get<1>(*itr2));
			return retValue;
		}
	}

	cout << "The table does not contain the desired field" << endl;
}

Atts_list Record::getAttsList()
{

	return this->myatts;
} 

int Record::printRecord()
{	
	#ifdef verbose
		cout << "Printing records on stdout." << endl;
	#endif
	auto itr1 = this->myatts.begin();
	auto itr2 = this->names.begin();
	for( ; itr1 != this->myatts.end() && itr2 != this->names.end() ; itr1++,itr2++ )
	{
		cout << *itr2 << ":" << get<1>(*itr1) << endl;
	}
	return DONE;
}

char* Record::getBits()
{
	return this->rec_block;
}

Record::~Record()
{
	delete this->att_offset;
	delete this->rec_block;
}

// int Record::suckRecord(Schema *s, char* fName){

// }