//include the header file function.h
#include "../inc/function.h"

/************************************************************************************
**     FUNCTION NAME     :     isFile
**
**    DESCRIPTION        :    function to find whether given path is a directory or  
**                            a file
**
**     RETURNS           :    return an integer (0=directory,1=file ,-1 =elsewise) 
**     
**     
**      Created by       :    Ravish
************************************************************************************/

int isFile(const char* name)
{
    DIR* directory = opendir(name);

    if(directory != NULL)
    {
     closedir(directory);
     return 0;
    }
    
    if(errno == ENOTDIR) //ENOTDIR will returned if its is not a directory 
    {
     return 1;
    }

    return -1;
}

/************************************************************************************
**     FUNCTION NAME     :     extractFileName
**
**    DESCRIPTION        :    function to extract the File name from given path
**
**     RETURNS           :    return a pointer to char 
**
**
**     Created by        :     Priyam   
************************************************************************************/
char *extractFileName(char * path){
    //tokens are created for each directory in the path and finally for the filename 
    char *token = strtok(path, "/");
    char * prev = (char * ) malloc(MAX_LENGTH * sizeof(char));
    if(prev==NULL)
    {
        return "Memory Allocation Failed!!\n";
    }

    while(token != NULL){
        strcpy(prev, token);
        token = strtok(NULL, "/");
    }

    return prev;
}

/************************************************************************************
**     FUNCTION NAME     :     createFileNode
**
**    DESCRIPTION        :    function to create a node in a Linked List
**
**     RETURNS           :    returns EXIT_SUCCESS/EXIT_FAILURE
**
**
**      Created by       :    Abhishek
************************************************************************************/

int createFileNode(char *path){
    
    char copyPath[MAX_PATH_LENGTH];
    strcpy(copyPath, path);
    //If Linked List is empty
    if(head == NULL){
        head = (File *) malloc(sizeof(File));
        if(head==NULL)
        {
            fprintf(stderr,"%s","Memory Allocation Failed...!!\n");
            return EXIT_FAILURE;
        }
        strcpy(head->f_path, copyPath);
        char * str = extractFileName(path);
        strcpy(head->f_name, str);
        counter=0;
        printf("File %d --> %s path:[%s]\n",counter, head->f_name, head->f_path);
        free(str); 
        head->next = NULL;
        curr = head;       
    }else{
        curr->next = (File *) malloc(sizeof(File));
        if(curr->next==NULL)
        {
            fprintf(stderr,"%s","Memory Allocation Failed...!!\n");
            return EXIT_FAILURE;
        }
        curr = curr->next;
        strcpy(curr->f_path, copyPath);
        char * str = extractFileName(path);
        strcpy(curr->f_name, str);
        counter+=1;
        printf("File %d --> %s path:[%s]\n",counter, curr->f_name, curr->f_path);
        free(str);
        curr->next = NULL;
    }
    return EXIT_SUCCESS;
}

/************************************************************************************
**     FUNCTION NAME     :     searchInFile
**
**    DESCRIPTION        :      it takes a single argument a pointer to char (path of file )
**                              opens the file and check whether givem search argument(string)
**                              is present inside the file. If present create a file node add it
**                              to the Linked List and increment file counter else skip the file. 
**
**     RETURNS           :      returns EXIT_SUCCESS/EXIT_FAILURE
**
**     Created By        :      Priyam
************************************************************************************/

int searchInFile(char *path){
    if( access( path, F_OK ) != 0) {
        //File doesn't have read permission
        return EXIT_FAILURE;
    }
    FILE *f = fopen(path, "r");
    if(f == NULL){
        return EXIT_FAILURE;
    }
    char temp[MAX_LENGTH];
    while (fgets(temp, MAX_LENGTH, f) != NULL)
    {
        if(strstr(temp, input) != NULL){ //Match found(found substring inside the opened file )
            fileCount++;
            int res = createFileNode(path);
            if(res == EXIT_FAILURE){
                return EXIT_FAILURE;
            }
            break;
        }
    }   
    if(f){
        fclose(f);
    }
    return EXIT_SUCCESS;
    
}

/************************************************************************************
**     FUNCTION NAME     :      openFile
**
**    DESCRIPTION        :      it is a utility function which takes the file path and prints its 
**                              contents on the console
**
**     RETURNS           :      returns EXIT_SUCCESS/EXIT_FAILURE
**
**     Created By        :      Shivam
************************************************************************************/

int openFile(char * fpath){
    FILE * fptr = fopen(fpath, "r");
    //if file could not be opened 
    if(fptr == NULL){
        fprintf(stderr,"%s","File not Found...!!\n");
        if(fptr){
            fclose(fptr);
        }
        return EXIT_FAILURE;
    }
    if(isFile(fpath) == 0){//function call
        fprintf(stderr,"%s","Given path is a directory...!!\n");

        if(fptr){
            fclose(fptr);
        }
        return EXIT_FAILURE;
    }
    
    printf("File opened!\n\n");
    LINE
    char c = fgetc(fptr);
    while (c != EOF)
    {
        printf ("%c", c);//printing the content of the file one character at a time
        c = fgetc(fptr);
    }

    printf("\n");
    fclose(fptr);

    return EXIT_SUCCESS;
}

/************************************************************************************
**    FUNCTION NAME      :     printLinkedList
**
**    DESCRIPTION        :     prints the Link List  
**
**     RETURNS           :     returns EXIT_SUCCESS/EXIT_FAILURE
**
**
**    Created By         :      Sachin and Abhishek
************************************************************************************/

int printLinkedList(File **ptr){
    //if no file are present in the Linked List
    if(fileCount == 0 || ptr == NULL){
        fprintf(stderr,"%s","No files Found...!!\n");
        return EXIT_FAILURE;
    }

    int flag = 0;
    char mychoice[MAX_LENGTH];
    LINE//for user interface
    printf("do you want to open any file!!(y/n)\n");
    scanf("%s",mychoice);
    getchar();
    if(mychoice[0]=='y'||mychoice[0]=='Y')
    {
    
    do
    {   
        printf("\n%d file(s) found\n\n", fileCount);
        LINE//for user interface
            
            //taking user input for file number which he wants to open
            printf("Select the file number which you want to open\n");
            char option[MAX_LENGTH];
           
            int myflag = 0; // flag for error detection
            int num = 0; // flag for error detection
            do
            {
                printf("Please enter file index number\n");
                scanf("%s", option);
                getchar();
                myflag=0;
                num=0;
                for(int i = 0; option[i] != '\0'; i++)
                {
                    if(isdigit(option[i]) == 0)
                    {
                        myflag=1;
                        break;
                    }
                    else
                    {
                        num=num*10+(option[i]-48);
                    }
                }
                
                if(myflag == 1 || num <0 || num>fileCount-1)
                    fprintf(stderr,"%s","File index does not exist...!!\n");


            } while (num < 0 || num > fileCount-1 || myflag==1);

            File *tmp = *(ptr+num);

            LINE //for user interface

            int res = openFile(tmp->f_path);
            if(res == EXIT_FAILURE){
                return EXIT_FAILURE;
            }
            num = -1;

            LINE//for user interface

            printf("Do you want to open other file?(y/n)");

            char ch[MAX_LENGTH];
            scanf("%s", ch);
            getchar();
            if(strlen(ch) > 1){
                ch[0] = '5';
            }

            switch (ch[0])
            {
            case 'y'://to check the case that's why no break statement
            case 'Y':
                flag = 0;
                break;
            case 'N'://to check the case that's why no break statement
            case 'n':
                flag = 1;
                break;
            default:
                fprintf(stderr,"%s","Invalid Choice...!!\n");
                flag = 1;
                break;
            }  
        
    } while (flag == 0); 
    }
    else if((mychoice[0]!='n' && mychoice[0]!='N' )||strlen(mychoice)>1)
    {
        fprintf(stderr,"%s","Invalid choice!!\n");
    }

    return EXIT_SUCCESS;
}

/************************************************************************************
**     FUNCTION NAME     :      freeMemory
**
**    DESCRIPTION        :      free all the memory created dynamically till now  
**
**     RETURNS           :      returns EXIT_SUCCESS/EXIT_FAILURE
**
**      Created by       :      Sachin
************************************************************************************/

int freeMemory(File **ptr){

    //checking if ptr is NULL
    if(ptr == NULL){
        return EXIT_SUCCESS;
    }

    // deallocating memory by traversing
    for(int i = 0; i<fileCount; i++){
        if(*(ptr+i) != NULL){
            free(*(ptr+i));
            *(ptr+i)=NULL;
        }
    }
    //setting linked list pointers to NULL
    head = NULL;
    curr = NULL;
    free(ptr); // free double pointer
    ptr = NULL;
    if(ptr != NULL){
        return EXIT_FAILURE;
    }else{
        return EXIT_SUCCESS;
    }
}

/************************************************************************************
**     FUNCTION NAME     :      allocateMemory
**
**    DESCRIPTION        :      creates a pointer to an array of pointers of File structure  
**                              and stores the pointer to every node for quick access and 
**                              calls the function printLinkedList 
**
**     RETURNS           :      returns EXIT_SUCCESS/EXIT_FAILURE 
**
**     Created by        :      Siddharth
************************************************************************************/

int allocateMemory(){

    //pointer to array of pointers
    File **ptr = (File **) malloc(fileCount * sizeof(File *));

    if(ptr == NULL){

        return EXIT_FAILURE;
    }
    //checking if linked list is empty
    if(head != NULL){
        File * tmp = head;
        int c = 0;
        while(tmp != NULL){
            *(ptr + c) = tmp;
            tmp = tmp->next;
            c++;
        }
    }

    int result = printLinkedList(ptr);//function call
    if(result == EXIT_FAILURE){
        return EXIT_FAILURE;
    }

    int res = freeMemory(ptr); // call to free memory
    if(res == EXIT_FAILURE){
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

/************************************************************************************
**     FUNCTION NAME      :      searchLocalSytem
**
**     DESCRIPTION        :      search the system recursively in all the directories for 
**                              the given path
**
**     RETURNS            :      returns EXIT_SUCCESS/EXIT_FAILURE.
**
**     
**     Created by          :      Abhishek
************************************************************************************/

int searchLocalSystem(const char * path){
    
    DIR *d;
    struct dirent *dir;
    d = opendir(path);
    if (d)
    {
        while ((dir = readdir(d)) != NULL) // traversing each files and subdirectory in directory
        {
            //skipping system directories and cache files directories
            if(strcmp(dir->d_name, ".") == 0 ||
                 strcmp(dir->d_name, "..") == 0 ||
                    dir->d_name[0] == '.'){
                continue;
            }

            // creating path for each files in directory
            char *currPath = (char *) calloc(MAX_PATH_LENGTH, sizeof(char));
            strcat(currPath, path);//make a copy of path 
            strcat(currPath, dir->d_name);
            strcat(currPath, "/"); // basic logic for making path

            //if the curr path is directory
            if(isFile(currPath) == 0){
                searchLocalSystem(currPath); // Recursive call to the new appended path
            }else{
                // if curr path is a file
                if(strstr(dir->d_name,".txt")==NULL
                            && strstr(dir->d_name,".c")==NULL   
                                && strstr(dir->d_name,".h")==NULL)
                {
                    free(currPath);
                    continue;
                }
                currPath[strlen(currPath) - 1] = '\0';

                //if we're searching with option 1
                if(search == SEARCH_WITH_WORD){
                    int res = searchInFile(currPath); // if curr path is file serach string in file using searchInFile()
                    if(res == EXIT_FAILURE){
                        free(currPath); // free curr path pointer
                        return EXIT_FAILURE;
                    }
                }else{
                    //if we're searching with option 2
                    if(strcmp(dir->d_name, filename) == 0 || strstr(dir->d_name,filename)!=NULL){
                        fileCount++;
                        int res = createFileNode(currPath); // if file found create node using createFileNode()
                        if(res == EXIT_FAILURE){
                            free(currPath);// free curr path pointer
                            return EXIT_FAILURE;
                        }
                    }                    
                }
            }
            free(currPath); // free curr path pointer
        }
        closedir(d); // closing directory pointer
    }
    else    
        return EXIT_FAILURE;
    return EXIT_SUCCESS;
}

/************************************************************************************
**     FUNCTION NAME     :      searchByWord
**
**    DESCRIPTION        :      function to get the search string and call the file system(searchLocalSystem)   
**                              to find the given word
**
**     RETURNS           :      returns EXIT_SUCCESS/EXIT_FAILURE
**
**     Created By        :      Ravish
************************************************************************************/

int searchByWord(){
    
    //setting up flag for option 1
    search = SEARCH_WITH_WORD;
    int flag = 0;

    //basic input logic
    printf("Enter search string/word:\n");
    fgets(input,MAX_LENGTH, stdin);
    input[strlen(input) - 1] = '\0';
    LINE
    printf("Do you want to search at any specific locations?(y/n)\n");
    
    // Taking user choice input
    char c[MAX_LENGTH];
    fgets(c, MAX_LENGTH, stdin);
    c[strlen(c) - 1] = '\0';
    
    //Error handling for choice
    if(strlen(c) > 1){
        c[0] = 'k';
    }  

    //declaration for userpath
    char userPath[MAX_LENGTH];
    switch (c[0])
    {
        case 'y'://to check the case that's why no break statement
        case 'Y':
            flag = 1;

            //taking user input for path
            printf("Please provide path\n");
            printf("%s", path);
            fgets(userPath, MAX_LENGTH, stdin);
            userPath[strlen(userPath) - 1] = '\0';
            strcat(path, userPath);
            strcat(path, "/"); // making path

            LINE
            printf("Searching..\n");

            //call for serach in local system
            int res = searchLocalSystem(path);
            if(res == EXIT_FAILURE){
                return EXIT_FAILURE;
            }
            break;
        
        case 'n'://to check the case that's why no break statement
        case 'N':
            printf("Searching..\n");
            printf("%s\n", path);
            flag = 1;
             //call for serach in local system
            res = searchLocalSystem(path);
            if(res == EXIT_FAILURE){
                return EXIT_FAILURE;
            }
            break;
        
        default:
            fprintf(stderr,"%s","Wrong Choice...!!\n");
            break;
    }
    
    if(flag == 1){
        //if files found store address of file nodes for quick access using allocateMemory()
        int res = allocateMemory();
        if(res == EXIT_FAILURE){
            fileCount = 0; //resetting file counter
            fprintf(stderr,"%s","Cannot list files.\n");
        return EXIT_FAILURE;
        }
    }
    
    fileCount = 0; // resetting file counter
    
    return EXIT_SUCCESS;
}

/************************************************************************************
**     FUNCTION NAME     :      searchFileName
**
**    DESCRIPTION        :      function to get the search string(file Name) and call the file    
**                              system(searchLocalSystem) to find the given file name
**
**     RETURNS           :      returns EXIT_SUCCESS/EXIT_FAILURE
**
**     Created By        :      Shivam
************************************************************************************/

int searchByFilename(){

    //setting flag for option 2
    search = SEARCH_WITH_FILENAME;
    int flag = 0;

    //getting input filename
    printf("Enter filename to be searched:\n");
    fgets(filename,MAX_LENGTH, stdin);
    printf("Searching %s\n", filename);

    LINE //design

    filename[strlen(filename) - 1] = '\0'; //setting last entered char (\n) to \0
    
    printf("Do you want to provide any absolute directory path?(y/n)\n");
    
    //getting user choice
    char userPath[MAX_LENGTH];
    char c[MAX_LENGTH];
    fgets(c, MAX_LENGTH, stdin);
    c[strlen(c) - 1]='\0';

    //Error handling logic if user provide wrong input
    if(strlen(c) > 1){
        c[0] = 'k';
    }  

    switch (c[0])
    {
        case 'y'://to check the case that's why no break statement
        case 'Y':
            flag = 1;

            // getting path from user
            printf("Enter absolute path:\n");
            printf("$:%s", path);
            fgets(userPath, MAX_LENGTH, stdin);
            userPath[strlen(userPath)-1] = '\0';
            strcat(path, userPath);
            strcat(path, "/"); // path string concatination
            printf("\n");
            LINE
            int res = searchLocalSystem(path); //call for search in local system using searchLocalSystem()
            if(res == EXIT_FAILURE){
                return EXIT_FAILURE;
            }
            break;

        case 'n'://to check the case that's why no break statement
        case 'N':
            flag = 1;
            res = searchLocalSystem(path);//call for search in local system using searchLocalSystem()
            if(res == EXIT_FAILURE){
                return EXIT_FAILURE;
            }
            break;
        default:
             fprintf(stderr,"%s","Innvalid Choice.\n");
            break;
    }    

    if(flag == 1){
        // if files found store address of files node using allocateMemory()
        int res = allocateMemory();
        if(res == EXIT_FAILURE){
            fprintf(stderr,"%s","Cannot list files.\n");
            fileCount = 0; //resetting file count

            return EXIT_FAILURE;
        }
    }
    fileCount = 0;//resetting file count

   return EXIT_SUCCESS;
}

/************************************************************************************
**     FUNCTION NAME     :      openWithAbsolutePath
**
**    DESCRIPTION        :      function to get the absolute file path and displays all the 
**                              contents of the given file path using openFile function 
**
**     RETURNS           :      returns EXIT_SUCCESS/EXIT_FAILURE
**
**     Created by        :      Siddharth
************************************************************************************/

int openWithAbsolutePath(){

    //taking file path input from user in pathInput
    printf("Enter abolute path to the file:\n");
    printf("$:%s",path);
    char pathInput[MAX_LENGTH];

    fgets(pathInput, MAX_LENGTH, stdin);
    pathInput[strlen(pathInput) - 1] = '\0'; //setting last char to \0

    strcat(path, pathInput);

    int res = openFile(path); // call for open file function to display contents
    if(res == EXIT_FAILURE){
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;

}
