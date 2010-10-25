//
// Copyright 2009, Blair Kitchen
//
// Reads hexdump input from stdin and writes the corresponding
// binary file.
//
#include <stdio.h>
#include <string.h>

#include "../config.h"

#if HAVE_STDINT_H
# include <stdint.h>
#elif HAVE_INTTYPES_H
# include <inttypes.h>
#endif

const uint32_t BUFFER_LEN = 8;
const uint32_t LINE_LEN = 42;

int32_t main(int32_t argc, char **argv)
{
    if(argc != 2)
    {
        fprintf(stderr, "Usage: hexwrite <output-file>\n");
        return -1;
    }

    FILE *outFile = fopen(argv[1], "wb");

    uint8_t outBuffer[BUFFER_LEN];
    char inBuffer[LINE_LEN + 1];
    inBuffer[LINE_LEN] = '\0';

    while(!feof(stdin))
    {
        size_t bytesRead = fread(inBuffer, 1, LINE_LEN, stdin);
        if(bytesRead == 0)
            return -1;

        char *token = strtok(inBuffer, " ");
        size_t bytesForOutput = 0;
        for(uint32_t i = 0; i < BUFFER_LEN; i++)
        {
            token = strtok(NULL, " ");
            if(strlen(token) > 2)
                break;
            
            bytesForOutput++;
            uint32_t temp;
            sscanf(token, "%02x", &temp);
            outBuffer[i] = (uint8_t)temp;
        }

        fwrite(outBuffer, 1, bytesForOutput, outFile);
    }        

    fclose(outFile);

    return 0;
}
