#ifndef DISKMANAGER_H
#define DISKMANAGER_H

/* 
	Abstraction class for representation of the Disk Manager.
	A Disk Manager instance will do all the allocation/deallocation/resizing of the disk.
	The Disk Manager will have an universal instance only.
	Buffer Manager will make calls to the file manager.
*/

/**
-> It will allocate the files by making call to the File Class.
-> Manages the list of free pages ??
-> Keeps a hash table between file descriptors and file names.
**/

#endif /* end DISKMANAGER_H */