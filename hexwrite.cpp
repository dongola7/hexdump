//
// Copyright 2009, Blair Kitchen
//
// Reads hexdump input from stdin and writes the corresponding
// binary file.
//

#include <stdio.h>

#define BUFFER_LEN 8
#define LINE_LEN 42

int main(int argc, char **argv)
{
    if(argc != 2)
    {
        fprintf(stderr, "Usage: hexwrite <output-file>\n");
        return -1;
    }

    FILE *outFile = fopen(argv[1], "wb");

    unsigned char outBuffer[BUFFER_LEN];
    int parseBuffer[BUFFER_LEN];
    char inBuffer[LINE_LEN + 1];
    inBuffer[LINE_LEN] = '\0';

    while(!feof(stdin))
    {
        size_t bytesRead = fread(inBuffer, 1, LINE_LEN, stdin);
        if(bytesRead == 0)
            return -1;
        
        int dummy;
        sscanf(inBuffer, "%0x %02x %02x %02x %02x %02x %02x %02x %02x", 
            &dummy, &parseBuffer[0], &parseBuffer[1], &parseBuffer[2],
            &parseBuffer[3], &parseBuffer[4], &parseBuffer[5],
            &parseBuffer[6], &parseBuffer[7]);

        for(int i = 0; i < BUFFER_LEN; i++)
            outBuffer[i] = (unsigned char)parseBuffer[i]; 

        fwrite(outBuffer, 1, BUFFER_LEN, outFile);
    }        

    fclose(outFile);

    return 0;
}
