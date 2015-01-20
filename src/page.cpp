#include <iostream>
#include <cstring>
#include <cstdlib>
#include "page.h"
#include "globals.h"
#include "utils/page_utils.h"

using namespace std;


/**
* Storage Manager will alocate the underlying memory for the block of the Page
* Instance to point out on it.
**/

Page::Page(char* block)
{	
	this->block = block;
	this->slots_arr = (slot*)malloc(sizeof(slot)*1); // allocating space for a single slot
	this->pre = -1;
	this->next = -1;
	this->freespace = PAGE_SIZE;
	this->actual_freespace = (short)(PAGE_SIZE-2*sizeof(short)-sizeof(slots_arr));
	this->num_recs = 0;

	writeInt(this->block,(short)0,this->num_recs); // the number of records in the page
	writeInt(this->block,(short)4,this->freespace); // storing the PAGE_SIZE
}

int Page::insertRecord(Record* rec)
{
	char* bits = rec->getBits(); // getting the bits representation of the underlying memory
	short slotNum = this->num_recs;
	short recLength = (short)strlen(bits);
	short new_actual_freespace = this->actual_freespace-recLength;

	if ( new_actual_freespace >= 0 ) // the record can be inserted
	{
		// write the record
		writeBytes(this->block,(short)(this->freespace-recLength),bits);

		// updating the slot array
		this->slots_arr[slotNum].record_offset = this->freespace-recLength;
		this->slots_arr[slotNum].record_length = recLength;

		// writing the memory
		writeShort(block,4*(this->slotNum+1),this->freespace-recLength);
		writeShort(block,4*(this->slotNum+1)+2,this->recLength);

		this->num_recs++; // inrementing the number of records
		this->freespace = this->freespace-recLength; // updating the freespace pointer

		// updating the headers
		writeShort(block,(short)0,this->num_recs);
		writeShort(block,(short)2,this->freespace);

		// reallocating the underlying slots_arra
		this->slots_arr = (slot*)realloc(sizeof(slot)*2);

		return DONE;
	}
	else
	{
		cout << "Need to create a new page, insufficient storage." << endl;
		return NOT_DONE;
	}
}

char* Page::getRecord(short slotNum)
{
	char* data = NULL;
	if ( slotNum < this->num_recs ) // the record exist
	{
		short recOffset = readShort(this->block,(short)(4*(this->num_recs+1)));
		short recLength = readShort(this->block,(short)(4*(this->num_recs+1)+2));
		data = readBytes(this->block,recOffset,recLength);
	}
	else
	{
		data = "-1";
	}
	return data;
}

int Page::deleteRecordBySlot(short slotNum)
// slotNum >= 0
{
	if ( slotNum < this->num_recs )
	{
		// need to replace the record pointed out by this->slot by the contents of
		// the records pointed out by the other slots

		short recLength = this->slots_arr[slotNum].rec_length; // record length
		short recOffset = this->slots_arr[slotNum].rec_offset; // record Offset
		short last_recOffset = this->slots_arr[this->num_recs-1].rec_offset; // last record offset

		moveBytes(this->block,this->block+last_recoffset+recLength,this->block+
				 last_recoffset,recOffset-last_recOffset);

		for ( short ctr = slotNum ; ctr < this->num_recs-1 ; ctr++)
		{
			this->slots_arr[ctr].rec_length = this->slots_arr[ctr+1].rec_length;
			this->slots_arr[ctr].rec_offset = this->slots_arr[ctr+1].rec_offset;
		}

		this->freespace = last_recOffset + recLength; // resetting the freespace
		this->actual_freespace -= recLength;

		this->num_recs--;

		// updating the headers
		writeShort(block,(short)0,this->num_recs);
		writeShort(block,(short)2,this->freespace);

		return DONE;
	}
	else // record not exist
	{
		cout << "Record Not Exist."  << endl;
		return NOT_DONE;
	}
}

int Page::deleteRecord(Record* rec)
{
	char* bits = rec->getBits();
	short length = strlen(bits);
	bool flag = false;

	for ( int ctr = 0 ; ctr < this->num_recs ; ctr++)
	{
		if( this->slots_arr[ctr].rec_length == length ) 
		// means this->can be the record to delete
		{
			// but we need to check for equality of bits
			char* test = readBytes(block,this->slots_arr[ctr].rec_offset,
				this->slots_arr[ctr].rec_length);
			if ( strcmp(test,bits) )
			{
				flag = true; // yes we found a match
				break;
			}
		}
	}

	if ( flag == true )
	{
		this->deleteRecordBySlot(ctr);
		return DONE;
	}
	else // record not exist
	{
		return NOT_DONE;
	}	
}

void Page::toBinary(char* bits);
{
	writeBytes(bits,this->block,PAGE_SIZE);
}

void Page::fromBinary(char* bits)
{
	// does not do any checking of length of bits array
	writeBytes(this->block,bits,PAGE_SIZE);
}

int Page::getNumRecs()
{
	return this->num_recs;
}

int Page::getNextPage()
{
	return this->next;
}

int Page::getPrevPage()
{
	return this->pre;
}

int Page::emptyIt()
{
	memset(this->block,0,PAGE_SIZE);
}

Page::~Page()
{
	free(this->slots_arr);
	// we need to free this->block too
}





