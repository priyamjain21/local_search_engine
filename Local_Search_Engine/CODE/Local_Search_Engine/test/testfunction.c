#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include <CUnit.h> // CU_ASSERT

#include "../src/function_definition.c"


void Mytestfunction1(void)
{	
	char arr[] = "/home/shivam/Desktop/files/file2.txt";
	char *filename = extractFileName(arr);
	
	CU_ASSERT_STRING_EQUAL(filename , "file2.txt");

	

}

void Mytestfunction2(void)
{	
	char arr[] = "/home/shivam/Desktop/files/file2.txt";
	int isDir = isFile(arr);
	

	CU_ASSERT(isDir == 1);

	strcpy(arr,"/home/shivam/Desktop/files");
	isDir = isFile(arr);
	

	CU_ASSERT(isDir == 0);


}

void Mytestfunction3(void)
{	
	char arr[] = "/home/shivam/Desktop/files/file2.txt";
	int nodeCreated = createFileNode(arr);
	

	CU_ASSERT(nodeCreated == 0);

}

void Mytestfunction4(void)
{	
	char arr[] = "/home/shivam/Desktop/files/file2.txt";
	strcpy(input,"our");
	int nodeCreated = searchInFile(arr);
	

	CU_ASSERT(nodeCreated == 0);

}

void Mytestfunction5(void)
{	
	File **ptr = NULL;

	int isFreed = freeMemory(ptr);

	//printf("\nfreeMemory %d ",isFreed);
	CU_ASSERT(isFreed == 0);

}

void Mytestfunction6(void)
{	
	char path[] = "/home/shivam/Desktop/files/file2.txt";
	int isfOpened = openFile(path);

	//printf("\n openFile  %d ",isfOpened);

	CU_ASSERT(isfOpened == 0);

	strcpy(path,"/home/shivam/Desktop/files/fi.txt");
	isfOpened = openFile(path);

	//printf("\n openFile  %d ",isfOpened);

	CU_ASSERT(isfOpened == 1);
	

}

void Mytestfunction7(void)
{	
	File **ptr = NULL;
	int isPrinted = printLinkedList(ptr);

	//printf("\n printLinkedList  %d ",isPrinted);

	CU_ASSERT(isPrinted == 1);
	
}

void Mytestfunction8(void)
{	
	int isAlotted = allocateMemory();

	//printf("\n allocateMemory  %d ",isAlotted);

	CU_ASSERT(isAlotted == 0);


	
}

void Mytestfunction9(void)
{	
	char arr[] = "/home/shivam/Desktop/files/text";
	int isFound = searchLocalSystem(arr);

	//printf("\n searchLocalSystem  %d ",isFound);

	CU_ASSERT(isFound == 0);

}

void Mytestfunction10(void)
{	
	
	int isOpend = openWithAbsolutePath();

	//printf("\n openWithAbsolutePath  %d ",isOpend);

	CU_ASSERT(isOpend == 0);

}

void Mytestfunction11(void)
{	
	int fsearch = searchByFilename();

	//printf("\n searchByFilename  %d ",fsearch);

	CU_ASSERT(fsearch == 0);

	
}

void Mytestfunction12(void)
{	
	int wordsearch = searchByWord();

	//printf("\n searchByWord  %d ",wordsearch);

	CU_ASSERT(wordsearch == 0);
	

}

