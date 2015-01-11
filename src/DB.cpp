#include <iostream>
#include <cstring>
#include <algorithm>
#include "DB.h"


DB::DB(string name)
{
	this->db_name = name;
	dbNames.push_back(this->db_name);
	int temp_len = name.length() + 4;
	char temp[temp_len];
	strcpy(temp,name.c_str());
	dbMap[this->db_name] = strcat(temp,".bin"); // strcat cannot modify a constant destination string
}

string DB::getDBLocation()
{
	return dbMap.find(this->db_name)->second;
}

DB::~DB()
{
	dbNames.erase(remove(dbNames.begin(),dbNames.end(),this->db_name),dbNames.end());
}
