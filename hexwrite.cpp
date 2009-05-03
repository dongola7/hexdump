//
// Copyright 2009, Blair Kitchen
//
// Reads hexdump input from stdin and writes the corresponding
// binary file.
//
#include <stdio.h>
#include <string.h>

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
    char inBuffer[LINE_LEN + 1];
    inBuffer[LINE_LEN] = '\0';

    while(!feof(stdin))
    {
        size_t bytesRead = fread(inBuffer, 1, LINE_LEN, stdin);
        if(bytesRead == 0)
            return -1;

        char *token = strtok(inBuffer, " ");
        size_t bytesForOutput = 0;
        for(int i = 0; i < BUFFER_LEN; i++)
        {
            token = strtok(NULL, " ");
            if(strlen(token) > 2)
                break;
            
            bytesForOutput++;
            int temp;
            printf("token = %s\n", token);
            sscanf(token, "%02x", &temp);
            outBuffer[i] = (unsigned char)temp;
        }

        fwrite(outBuffer, 1, bytesForOutput, outFile);
    }        

    fclose(outFile);

    return 0;
}
