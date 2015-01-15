/* Global constants */

#ifndef GLOBALS_H
#define GLOBALS_H

#define BLOCK_SIZE 4096
#define LIST_HEADERS 8 // Storing pre and next pages blockId
#define PAGE_SIZE 131072 - LIST_HEADERS
#define PageId int

/* Data types of the fields*/
#define INT_T 1
#define DOUBLE_T 2
#define STRING_T 3
#define DATE_T 4


enum { NOT_DONE,DONE };




#endif /* end GLOBALS_H */


