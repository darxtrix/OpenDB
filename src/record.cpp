#include <iostream>
#include <cstdio>
#include <utils/catalog.h>
#include <iterator>

using namespace std;

Record::Record()
{
	this.numAtts = 0;
	this.att_offset =0;
	this.myatts = {};
}

int Record::makeRecord(string rel,vector< tuple<string,string> > myatts1){
	vector<string> name;
	vector<string> type;
	int ctr;

	for(ctr = 0; ctr<myatts.size ; ctr++){
		this.myatts1[ctr].get<0> = name[ctr];
		this.myatts1[ctr].get<0> = name[ctr];
	}

	this.numAtts = ctr;
	vector<string>* name_pointer = &name;
	vector<string>* type_pointer = &type;
	loadCatalog(rel, name_pointer, type_pointer);

	this.rec_block = {};

}

string Record::getAttribute(string field_name){

	for(int i=0; i<this.myatts.size ; i++){

		if(this.myatts[i].get<0>==field_name)
			return this.myatts[i].get<1>;
	}
	return "The queried attribute was not found";
}

Atts_list Record::getAttsList(){

	return this.myatts;
} 

int Record::printRecord(){
	for(int i=0 ; i<this.myatts.size ; i++){
		cout << this.myatts[i].get<1> << " : " << this.myatts[i].get<0>;
	}
	return 1;
}

char* Record::getBits(){
	return this.rec_block;
}

int Record::suckRecord(Schema *s, char* fName){

}