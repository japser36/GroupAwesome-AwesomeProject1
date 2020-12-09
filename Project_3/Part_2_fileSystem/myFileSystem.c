

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>


//struct for inodes
typedef struct {
    char name[8];
    int32_t size;
    int32_t blockPointers[8];
    int32_t used;
} Inode;

//struct for file system
typedef struct {
    char freeBlockList[128];
    Inode inode[16];
} FileSystem;


int fd;


FileSystem* createMyFileSystem(char diskName[]){
    FileSystem* fs = malloc(sizeof(FileSystem));
    //open file, the oflags are there because it wouldn't write to file other wise
    fd = open(diskName,O_CREAT | O_RDWR, S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP | S_IXGRP | S_IROTH | S_IWOTH | S_IXOTH );
    //Error statement
    if(fd < 0){
        printf("Error could not find file\n");
        return NULL;
    }

    //read free block list from file
    read(fd, fs->freeBlockList,128);

    //read each inode from file
    for(int i = 0; i < 16; i++){
        read(fd, fs->inode[i].name,8);
        read(fd, &fs->inode[i].size,4);
        read(fd, &fs->inode[i].blockPointers,32);
        read(fd, &fs->inode[i].used,4);
    }
    // Open the file with name diskName


    // Read the first 1KB and parse it to structs/objecs representing the super block
    // 	An easy way to work with the 1KB memory chunk is to move a pointer to a
    //	position where a struct/object begins. You can use the sizeof operator to help
    //	cleanly determine the position. Next, cast the pointer to a pointer of the
    //	struct/object type.

    // Be sure to close the file in a destructor or otherwise before
    // the process exits.
    return fs;
}
//destroy function for fs
int destroy(){
    close(fd);
    return 0;
}

int createFile(FileSystem* fs, char name[8], int32_t size){
    //create a file with this name and this size

    // high level pseudo code for creating a new file


    // Step 1: Look for a free inode by searching the collection of objects
    // representing inodes within the super block object.
    // If none exist, then return an error.
    // Also make sure that no other file in use with the same name exists.
    for(int i = 1; i < 16; i++){
        //find inode with matching name, if one exists then cant create a new oof same name.
        if(strcasecmp(fs->inode[i].name, name) ==0 ){
            printf("Invalid file name, no duplicate file names allowed.\n");
            return -1;
        }
    }


    //find index of first empty inode
    int inodeIndex = -1;
    for(int i = 0; i < 16; i++){
        if(fs->inode[i].used == 0){
            inodeIndex = i;
            break;
        }
    }
    //No empty inode was found return error
    if(inodeIndex == -1) {
        printf("Error the drive as reached maximum capacity\n");
        return -1;
    }


    // Step 2: Look for a number of free blocks equal to the size variable
    // passed to this method. If not enough free blocks exist, then return an error.
    int freeBlockIndex[size];
    int counter = 0;

    //Find the first x number of free blocks and save there locations
    for(int i = 0; i < 128; i++){
        if(fs->freeBlockList[i] == 0){
            freeBlockIndex[counter] = i;
            counter++;
            //if we found enough blocks stop looking for more
            if(counter == size){
                break;
            }
        }
    }
    //Check that we have enough block and that the look didn't just end
    if(counter != size){
        printf("Error not enough free blocks\n");
        return -1;
    }

    // Step 3: Now we know we have an inode and free blocks necessary to
    // create the file. So mark the inode and blocks as used and update the rest of
    // the information in the inode.


    //Save all data to structs
    fs->inode[inodeIndex].used = 1;
    fs->inode[inodeIndex].size = size;
    strcpy(fs->inode[inodeIndex].name, name);
    for(int i = 0; i < size; i ++){
        fs->inode[inodeIndex].blockPointers[i]=freeBlockIndex[i];
        fs->freeBlockList[freeBlockIndex[i]] = 1;
    }

    //write struct to files
    lseek(fd,0,SEEK_SET);
    write(fd, fs,1024);
    // Step 4: Write the entire super block back to disk.
    //	An easy way to do this is to seek to the beginning of the disk
    //	and write the 1KB memory chunk.
} // End Create



int deleteFile(FileSystem* fs, char name[8]){
    // Delete the file with this name

    // Step 1: Look for an inode that is in use with given name
    // by searching the collection of objects
    // representing inodes within the super block object.
    // If it does not exist, then return an error.
    int inodeIndex = -1;
    //find file with name
    for(int i = 0; i < 16; i++){
        if(strcasecmp(fs->inode[i].name, name) == 0 ){
            inodeIndex = i;
            break;
        }
    }
    //return error no file found with name.
    if( inodeIndex == -1){
        printf("Error unable to locate file.\n");
        return -1;
    }

    // Step 2: Free blocks of the file being deleted by updating
    // the object representing the free block list in the super block object.
    for(int i = 0; i < 8; i++){
        int blockIndex = fs->inode[inodeIndex].blockPointers[i];
        if(blockIndex > 0){
            fs->freeBlockList[blockIndex] = 0;
        }
    }

    // Step 3: Mark inode as free.
    fs->inode[inodeIndex].used = 0;

    // Step 4: Write the entire super block back to disk.
    lseek(fd,0,SEEK_SET);
    write(fd, fs,1024);

} // End Delete

int listFiles(FileSystem* fs){
    // List names of all files on disk

    // Step 1: Print the name and size fields of all used inodes.
    for(int i = 0; i < 16; i++) {
        if (fs->inode[i].used == 1) {
            printf("%s\n", fs->inode[i].name);
        }
    }
} // End ls

int readFile(FileSystem* fs, char name[8], int32_t blockNum, char buf[1024]){

    // read this block from this file
    // Return an error if and when appropriate. For instance, make sure
    // blockNum does not exceed size-1.


    // Step 1: Locate the inode for this file as in Step 1 of delete.
    int inodeIndex = -1;
    for(int i = 0; i < 16; i++){
        if(strcasecmp(fs->inode[i].name, name) == 0 ){
            inodeIndex = i;
            break;
        }
    }
    //return error no file found with name.
    if( inodeIndex == -1){
        printf("Error unable to locate file.\n");
        return -1;
    }

    //Check if block number is valid for file
    if(blockNum >= fs->inode[inodeIndex].size){
        printf("Invalid block number.\n");
        return -1;
    }


    // Step 2: Seek to blockPointers[blockNum] and read the block
    // from disk to buf.
    lseek(fd, 1024*(fs->inode[inodeIndex].blockPointers[blockNum]), SEEK_SET);
    read(fd, buf, 1024);

} // End read


int writeFile(FileSystem* fs, char name[8], int32_t blockNum, char buf[1024]){

    // write this block to this file
    // Return an error if and when appropriate.

    // Step 1: Locate the inode for this file as in Step 1 of delete.
    int inodeIndex = -1;
    for(int i = 0; i < 16; i++){
        if(strcasecmp(fs->inode[i].name, name) == 0 ){
            inodeIndex = i;
            break;
        }
    }
    //return error no file found with name.
    if( inodeIndex == -1){
        printf("Error unable to locate file.\n");
        return -1;
    }
    //Check if block number is valid for file
    if(blockNum >= fs->inode[inodeIndex].size){
        printf("Invalid block number.\n");
        return -1;
    }

    lseek(fd,1024 * (fs->inode[inodeIndex].blockPointers[blockNum]), SEEK_SET);
    write(fd, buf, 1024);
    // Step 2: Seek to blockPointers[blockNum] and write buf to disk.

} // end write

