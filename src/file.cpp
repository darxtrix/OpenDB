#include <iostream>
#include <fcntl.h> // file control options are defined in this->file
#include <cstdio>
#include <cstdlib>
#include "file.h"
#include "globals.h"
#include "utils/page_utils.h"

using namespace std;

File::File()
{
	this->myfileDes = 0;
	this->currLength = 0;
}

void File::createDb(char* fName)
{
	int mode = O_CREAT | O_RDWR | O_TRUNC; // bitwise OR of the flags
	// It is assumed that the file does not exist before
	int this->myfileDes = open(fName,mode,S_IRUSR+S_IWUSR); 
	if ( this->myfileDes < 0 )
	{
		cerr << fName << " couldn't be created." << endl;
		exit(0);
	}
	else // the file has been created
	{
		#ifdef verbose
			cout << fName << " has been created." << endl;
		#endif
	}
}

void File::openDb(off_t blockId,char* fName)
{
	int mode = O_RDWR;
	// this is assumed that the file exists
	int this->myfileDes = open(fName,mode,S_IWUSR+S_IRUSR);
	if ( this->myfileDes < 0 )
	{
		cerr << fName << " couldn't be opened. It may not exist." << endl;
		exit(0);
	}
	else
	{
		#ifdef verbose
			cout << fName << " has been opened." << endl;
		#endif
		// update the currLength variable
		lseek(this->myfileDes,0,SEEK_SET);
		// read the first(off_t) bytes of first page to get the length of the file
		read(this->myfileDes,&this->currLength,sizeof(off_t));

		if ( blockId >= 0 ) // point to this->block
		{
			lseek(this->myfileDes,blockId*BLOCK_SIZE,SEEK_SET);
		}
		else
		{
			#ifdef verbose
				cout << "Negative blockId is encounterd,blockId :" << blockId << endl;
			#endif
		}
	}
}


int File::addPage(Page* addMe,off_t blockId )
// blockId -> 0 1 2 .. (currLength-1)
{
	if ( blockId > this->currLength ) // means there will be empty pages 
	{
		// zeroing of pages till the offset of blockId has to be done
		// need to add these extra pages to the free list of pages

		int dummy = (blockId-this->currLength)*BLOCK_SIZE;
		char buff[dummy] = {0};

		lseek(this->myfileDes,this->currLength*BLOCK_SIZE,SEEK_SET);
		write(this->myfileDes,buff,dummy);

		// updating the length
		this->currLength = blockId+1;
	}
	
	// now, add the page
	char* bits = new char[BLOCK_SIZE];
	addMe->toBinary(bits+8); // will copy page contents

	// ?? but who will write the linked list headers of the page block

	// pointing the fileDescriptor to correct position
	lseek(this->myfileDes,blockId*BLOCK_SIZE,SEEK_SET);
	// writing the record
	write(this->myfileDes,bits,BLOCK_SIZE);

	delete[] bits;

#ifdef VERBOSE
	cerr << " File: curLength " << curLength << " whichPage " << whichPage << endl;
#endif

	return DONE;
}

int File::getPage(Page* getMe,off_t blockId)
{
	if ( blockId >= this->currLength )
	{
		cerr << "whichPage:" << whichPage << " " << "currentLength: " << this->currLength << endl;
		cerr << "Tried accessing out of the file" << endl;
		exit(1);
	}
	else
	{
		char* bits = new char[BLOCK_SIZE];
		// moving the pointer
		lseek(this->myfileDes,blockId*BLOCK_SIZE,SEEK_SET);
		read(this->myfileDes,bits,BLOCK_SIZE);

		getMe->fromBinary(bits+4);
		// update the pre and next headers of the getMe page ??

		delete[] bits;
		return DONE;
	}

}

off_t File::getLength()
{
	return this->currLength;
}

off_t File::close()
{
	lseek(this->myfileDes,0,SEEK_SET);
	write(this->myfileDes,&this->currLength,sizeof(off_t)); // updating header page
	close(this->myfileDes);
	#ifdef VERBOSE
		cerr << "Closing the file." << endl;
	#endif
		
	return this->currLength;
}