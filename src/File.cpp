#include <iostream>
#include <fcntl.h> // file control options are defined in this file
#include <cstdio>
#include <cstdlib>
#include "file.h"
#include "globals.h"

using namespace std;

File::File()
{
	this.myfileDes = 0;
	this.currLength = 0;
}

void File::createDb(char* fName)
{
	int mode = O_CREAT | O_RDWR | O_TRUNC; // bitwise OR of the flags
	// It is assumed that the file does not exist before
	int this.myfileDes = open(fName,mode,S_IRUSR+S_IWUSR); 
	if ( this.myfileDes < 0 )
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

void File::openDb(int length,char* fName)
{
	int mode = O_RDWR;
	// this is assumed that the file exists
	int this.myfileDes = open(fName,mode,S_IWUSR+S_IRUSR);
	if ( this.myfileDes < 0 )
	{
		cerr << fName << " couldn't be opened." << endl;
		exit(0);
	}
	else
	{
		#ifdef verbose
			cout << fName << " has been opened." << endl;
		#endif
	}
	// the file has been opened, seek forward 
	// fileLen = 0, means the header page. File should be point to the first page

	if ( fileLen != 0 ) // point to this page
	{
		lseek(this.myfileDes,0,SEEK_SET);
		// read the first(off_t) bytes of first page to get the length of the file
		read(this.myfileDes,sizeof(off_t),&this.currLength);
	}
	else
	{
		this.currLength = 0; // we need to add Pages
	}

}


int File::addPage(Page* addMe,off_t page_off)
// This method will add the Page  addMe at a given page_off from the start and increment 
// the currLength variable accordingly
{
	// page_off is defined from the start of the file

	if ( page_off > this.currLength ) // means there will be empty pages 
	{
		// zeroing of pages till the offset of page_off
		int dummy = (page_off-this.currentLength)*BLOCK_SIZE;
		char buff[dummy] = {0};

		lseek(this.myfileDes,this.currentLength*BLOCK_SIZE,SEEK_SET);
		write(this.myfileDes,buff,dummy);

		// incementing the currentLength
		this.currentLength = page_off + 1;
	}
	// now, add the page

	char* bits = new char[BLOCK_SIZE];
	addMe->toBinary(bits+8); // will copy page contents

	// pointing the fileDescriptor to correct position
	lseek(this.myfileDes,page_off*BLOCK_SIZE,SEEK_SET);
	// writing the record
	write(this.myfileDes,bits,BLOCK_SIZE);
	delete[] bits;

#ifdef VERBOSE
	cerr << " File: curLength " << curLength << " whichPage " << whichPage << endl;
#endif

	return DONE;
}

int File::getPage(Page* getMe,off_t page_off)
{
	if ( page_off > this.currentLength )
	{
		cerr << "whichPage:" << whichPage << " " << "currentLength: " << this.currentLength << endl;
		cerr << "Tried accessing out of the file" << endl;
		exit(1);
	}
	else
	{
		char* bits = new char[BLOCK_SIZE];
		// moving the pointer
		lseek(this.myfileDes,whichPage*BLOCK_SIZE,SEEK_SET);
		read(this.myfileDes,bits,BLOCK_SIZE);

		getMe->fromBinary(bits+4);
		// update the pre and next headers ??

		delete[] bits;

	}

}

off_t File::close()
{
	lseek(this.myfileDes,0,SEEK_SET);
	write(this.myfileDes,&this.fileLen,sizeof(off_t));
	close(this.myfileDes);
	#ifdef VERBOSE
		cerr << "Closing the file." << endl;
	#endif
		
	return this.fileLen;
}