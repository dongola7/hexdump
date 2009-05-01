#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define BUFFER_SIZE 8

int main(int argc, char **argv)
{
    if(argc != 2)
    {
        fprintf(stderr, "Usage: hexdump <filename>\n");
        return -1;
    }

    size_t offset = 0;
    unsigned char buffer[BUFFER_SIZE];
    FILE *inFile = fopen(argv[1], "rb");
    while(feof(inFile) == 0)
    {
        memset(buffer, 0, BUFFER_SIZE);
        size_t bytesRead = fread(buffer, 1, BUFFER_SIZE, inFile);
        if(bytesRead == 0)
            break;

        printf("%08x ", offset);
        offset += bytesRead;

        for(int i = 0; i < BUFFER_SIZE; i++)
        {
            if(i < bytesRead)
                printf("%02x ", buffer[i]);
            else
                printf("   ");
        }

        for(int i = 0; i < bytesRead; i++)
        {
            if(isalnum(buffer[i]) == 0)
                printf(".");
            else
                printf("%c", buffer[i]);
        }
    
        printf("\n");
    }
    fclose(inFile);

    return 0;
}
