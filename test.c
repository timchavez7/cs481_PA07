#include <stdio.h>
#include <stdlib.h>
#include <linux/fs.h>
#include "ext2_fs.h"

int main(int argc, char **argv) {
    int inodeNum = 0;
    struct ext2_super_block super;
    struct ext2_group_desc groupDesc;
    struct ext2_inode inode;
    char char_buffer[1024];
    char current = 'c';
    FILE *fp;

    if (argc < 3) {
        printf("ERROR: need inode number and disk image name\n");
        return 0;
    }
    //inode number 
    inodeNum = atoi(argv[1]);

    // Get file system to read
    fp = fopen(argv[2],"r");
    
    fseek(fp, 1024, SEEK_SET);
    fread(&super, sizeof(super), 1, fp);

    fseek(fp, 2048, SEEK_SET);
    fread(&groupDesc, sizeof(groupDesc), 1, fp);

    fseek(fp, (1024 * (groupDesc.bg_inode_table)) + ((inodeNum - 1) * 128), SEEK_SET);
    fread(&inode, sizeof(inode), 1, fp);

    fseek(fp, 1024 * (inode.i_block[0]), SEEK_SET);
    int fileSize = inode.i_size;
    int index = 0;
    while (((current = getc(fp)) != EOF) && (index < fileSize )) {
        printf("%c", current);
        index ++;
    }


    // Get superblock
    // superblock contains group descriptor
    // GD has blocks that are 1024 bytes large AKA 400 hex
    // --- each block is 400 hex byets
    // Its fifth block contains the location of all of the inodes
    // -- the fifth block at 1400 hex
    // Each inode location is offset by a certain amount within that block (in this case could be 128 bytes
    // To get to inode 1 then 1400 + (80 * (i - 1))

    return 0;
}
