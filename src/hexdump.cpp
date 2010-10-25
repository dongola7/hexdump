//
// Copyright Blair Kitchen, 2009
//
// A simple program for generating hex dumps.
//
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#if HAVE_CONFIG_H
# include "../config.h"
#endif

#if HAVE_STDINT_H
# include <stdint.h>
#elif HAVE_INTTYPES_H
# include <inttypes.h>
#endif

const uint32_t BUFFER_SIZE = 8;

int32_t main(int32_t argc, char **argv)
{
    if(argc != 2)
    {
        fprintf(stderr, "Usage: hexdump <filename>\n");
        return -1;
    }

    size_t offset = 0;
    uint8_t buffer[BUFFER_SIZE];
    FILE *inFile = fopen(argv[1], "rb");
    while(feof(inFile) == 0)
    {
        memset(buffer, 0, BUFFER_SIZE);
        size_t bytesRead = fread(buffer, 1, BUFFER_SIZE, inFile);
        if(bytesRead == 0)
            break;

        printf("%08zx ", offset);
        offset += bytesRead;

        for(uint32_t i = 0; i < BUFFER_SIZE; i++)
        {
            if(i < bytesRead)
                printf("%02x ", buffer[i]);
            else
                printf("   ");
        }

        for(uint32_t i = 0; i < bytesRead; i++)
        {
            if(isprint(buffer[i]) == 0)
                printf(".");
            else
                printf("%c", buffer[i]);
        }
    
        printf("\n");
    }
    fclose(inFile);

    return 0;
}
