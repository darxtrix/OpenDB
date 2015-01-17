#ifndef PAGE_H
#define PAGE_H
#include "record.h"

/**
->  Abstraction of a slotted page block.
->  Manages adding, deletion and searching of records in the page itself.
->  blockId of the page will tell about the position of the block in memory.
->  Pages will not be reshuffled within the file i.e their block Id's will remain same.
->  Keeps a <undecided> list of records in a page.
**/
	
struct Slot 
{
	short record_offset; // offset of a record from the start of the page
	short record_length; // length of a record
};

typedef struct Slot slot;

/* Their block Ids will be in the order of their position on the disk*/

class Page
{
private:
	PageId blockId; // pages get pageId in their allocation order, not persistent quantity

	/* These quatities are persistent on the memory block */
	PageId pre; // previous page's block id
	PageId next; // next page's block id
	short num_recs; // number of records currently in the page
	short freespace; // freespace pointer in the page
	slot* slots_arr = NULL; // pointer to the slots_array

	short actual_freespace; // the actual freespace in the page
	char* block; // bits representation of the underlying memory

	/* Constructor */
	Page(char* block);

	// returns the bit representation of the record at the specified slot
	char* getRecord(short slotNum);

	// insert a record into the page if a free slot is found
	int insertRecord(Record* rec);

	// deletes a record pointed by the slot
	int deleteRecordBySlot(short slotNum);

	// deletes a record by finding it
	int deleteRecord(Record* rec);

	// write the binary information of the page to the bits array
	// bits must be of PAGE_SIZE
	void toBinary(char* bits);

	// read the page from the bits array 
	int fromBinary(char* bits);

	// get the number of records
	int getNumRecs();

	// returns the blockId of next page
	int getNextPage();

	// returns the blockId of prev page
	int getPrevPage();

	// empty the page
	void emptyIt();

	/* Destructor */
	~Page();

};

#endif /* end PAGE_H */