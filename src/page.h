#ifndef PAGE_H
#define PAGE_H
#include "record.h"

/*
	Abstraction of a slotted page block.
	Manages adding, deletion and searching of records in the page itself.
	Keeps a <undecided> list of records in a page.
*/
	
struct Slot 
{
	short record_offset; // offset of a record from the start of the page
	short record_length; // length of a record
};

typedef struct Slot slot;

class SlottedPage
{
public:
	PageId blockId; // pages get pageId in their allocation order, not persistent quantity

	/* These quatities are persistent on the block */
	PageId pre; // previous page's block id
	PageId next; // next page's block id
	char* block; // bits representation of the underlying memory
	short num_recs; // number of records currently in the page
	short freespace; // freespace in the page
	slot* slots_arr; // pointer to the slots_array

	/* Constructor */
	Page();

	// returns the bit representation of the record at the specified slot
	static char* getRecord(short slotNum);

	// insert a record into the page if a free slot is found
	static int insertRecord(Record* rec);

	// deletes a record pointed by the slot
	static int deleteRecordBySlot(short slotNum);

	// deletes a record by finding it
	static int deleteRecord(Record* rec);

	// write the binary information of the page to the bits array
	static void toBinary(char* bits);

	// read the page from the bits array 
	static int fromBinary(char* bits);

	// get the number of records
	static int numRecords();

	// returns the blockId of next page
	static int getNextPage();

	// returns the blockId of prev page
	static int getPrevPage();

	// empty the page
	static int emptyIt();

	/* Destructor */
	~Page();

};

#endif /* end PAGES_H */