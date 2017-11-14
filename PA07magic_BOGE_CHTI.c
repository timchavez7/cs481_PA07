#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    FILE *filepointer;
    unsigned char buffer[8];
    // unsigned char opcode[4] = {0};
    // unsigned char arg1[4] = {0};
    // unsigned char arg2[4] = {0};
    // unsigned char arg3[4] = {0};

    if (argc < 2) {
        printf("ERROR: need filename\n");
        return 0;
    }

    if ((filepointer = fopen(argv[1], "rb")) < 0) {
        printf ("ERROR: Can't open file\n");
        return 0;
    }

    fread(buffer, 1, 4, filepointer);
    if (buffer[0] == 0xff && buffer[1] == 0x00 && buffer[2] == 0xff && buffer[3] == 0xe0) {
        printf("JPG\n");
    }
    else if (buffer[0] == 0x7f && buffer[1] == 0x45 && buffer[2] == 0x4c && buffer[3] == 0x46) {
        printf("ELF\n");
    }
    else if (buffer[0] == 0x25 && buffer[1] == 0x50 && buffer[2] == 0x44 && buffer[3] == 0x46) {
        printf("PDF\n");
    }
    else if (buffer[0] == 0x23 && buffer[1] == 0x21) {
        printf("Linux script\n");
    }
    else {
        if (fseek(filepointer, 257, SEEK_SET) != 0) {
            printf("ERROR: fseek failed\n");
            return 0;
        }
        fread(buffer, 1, 5, filepointer);
        if (buffer[0] == 0x75 && buffer[1] == 0x73 && buffer[2] == 0x74 && buffer[3] == 0x61 && buffer[4] == 0x72) {
            printf("TAR\n");
        }
        else {
            printf("I don't know what it is.\n");
        }
    }
    
    fclose(filepointer);
    return 0;
}