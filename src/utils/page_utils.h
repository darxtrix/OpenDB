#ifndef PAGE_UTILS_H
#define PAGE_UTILS_H

/**
* Utilities for reading and writing to the underlying storage array of Page object 
* and not to the disk i.e in memory.
**/

short readShort(char* block,short offset);

void writeShort(char* block,short offset,short value);

int readInt(char* block,short offset);

void writeInt(char* block,short offset,int value);

char* readBytes(char* block,short offset,int length);

void writeBytes(char* block,short offset,int length,int data_block);

void moveBytes(char* block,short src_off,short dest_off,short chunk_length);

#endif

