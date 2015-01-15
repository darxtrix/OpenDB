#include <iostream>
#include <cstring>
#include "page.h"
#include "globals.h"
#include "utils/page_utils.h"

using namespace std;


/*
** Storage Manager will alocate the underlying memory for the block to point out
** on it.
*/

Page::Page(char* block)
{	
	this.block = block;
	this.slots_arr = (slot*)malloc(sizeof(slot)*1); // allocating space for a single slot
	this.pre = -1;
	this.next = -1;
	this.freespace = PAGE_SIZE;
	this.actual_freespace = (short)(PAGE_SIZE-2*sizeof(short)-sizeof(slots_arr));
	this.num_recs = (short)0;

	writeInt(this.block,(short)0,num_recs); // the number of records in the page
	writeInt(this.block,(short)4,freespace); // storing the PAGE_SIZE
}

int Page::insertRecord(Record* rec)
{
	char* bits = rec.getBits(); // getting the bits representation of the underlying memory
	short slotNum = this.num_recs;
	short recLength = (short)length(bits);
	short des_off = this.actual_freespace-recLength;

	if ( des_off >= 0 ) // the record can be inserted
	{
		// write the record
		writeBytes(this.block,short(this.actual_freespace-recLength),bits);

		// updating the slot array
		this.slots_arr[num_recs].record_offset = des_off;
		this.slots_arr[num_recs].record_length = recLength;

		// writing the memory
		writeShort(block,4*(this.num_recs+1),des_off);
		writeShort(block,4*(this,num_recs+1)+2,this.recLength);

		this.num_recs++; // inrementing the number of records
		this.freespace = des_off; // updating the freespace pointer

		// updating the headers
		writeShort(block,(short)0,this.num_recs);
		writeShort(block,(short)2,this.freespace);
		return DONE;
	}
	else
	{
		return NOT_DONE;
	}
}

char* Page::getRecord(short slotNum)
{
	if ( slotNum < this.num_recs ) // the record exist
	{
		short recOffset = readShort(this.block,(short)(4*(this.num_recs+1)));
		short recLength = readShort(this.block,(short)(4*(this.num_recs+1)+2));
		char* data = readBytes(this.block,recOffset,recLength);
	}
	else
	{
		char* data = "-1";
	}
	return data;
}







