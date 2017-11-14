#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    FILE *filepointer;
    unsigned char *buffer;
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

    for (i = 0; i < 4; i++) {
        fread(buffer + i, 1, 1, filepointer);
    }

    
    fclose(filepointer);
    return 0;
}