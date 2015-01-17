#include <iostream>
#include <cstdio> // POSIX C-API
#include <cstdlib>
#include <cstring>
#include "page_utils.h"

// Reads a short int at a specified offset from the start of the block
short readShort(char* block,short offset)
{
	short value = 0;
	short* valptr = &value;
	memcpy(valptr,block+offset,2);
	return *valptr;
}

// Writes a short int at a specified offset 
void writeShort(char* block,short offset,short value)
{
	short* valptr = &value;
	memcpy(block+offset,valptr,2);
}	

// Reads an integer from (block + offset)
int readInt(char* block,short offset)
{
	int value = 0;
	int* valptr = &value;
	memcpy(valptr,block+offset,4);
	return value;
}

// Writes an integer at (block+offset)
void writeInt(char* block,short offset,int value)
{
	int *valptr = &value;
	memcpy(block+offset,valptr,4);
}

// Reads a double from (block + offset)
int readDouble(char* block,short offset)
{
	double value = 0;
	double* valptr = &value;
	memcpy(valptr,block+offset,sizeof(double));
	return value;
}

// Writes a double at (block+offset)
void writeDouble(char* block,short offset,double value)
{
	double *valptr = &value;
	memcpy(block+offset,valptr,sizeof(double));
}

// Reads val<length> bytes in a block of memory starting at (block+offset)
// and return the address of that block
char* readBytes(char* block,short offset,int length)
{
	char* data_block = (char*) malloc(sizeof(char)*length);
	memcpy(data_block,block+offset,length);
	return data_block;
}

// Writes length bytes of data_block starting at (block+offset)
void writeBytes(char* block,short offset,int length,const char* data_block)
{
	memcpy(block+offset,data_block,length);
}

// moves a chunk of bytes from source offset to the destination offset
void moveBytes(char* block,short src_off,short dest_off,short chunk_length)
{
	char* temp = (char*)malloc(sizeof(char)*chunk_length);
	memcpy(temp,block + src_off,chunk_length);
	memcpy(block+dest_off,temp,chunk_length);
	free(temp);
}


