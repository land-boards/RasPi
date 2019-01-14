#include <cstdlib>
#include <iostream>

using namespace std;
#include <stdio.h>
#include <stdlib.h>

struct prog
{
       char opcode[4];
       unsigned long operand1;
       unsigned long operand2;
       unsigned longoperand3;       
       };

char programStrings[100][16];

int myFileIO::readInLine(void)
{
	int inLineOffset = 0;
	int readChar;

	inLineCount++;

	while(1)
	{
		readChar = fgetc(inFilePtr);
		if (readChar == EOF)
		{
			if (ferror (inFilePtr))
				return(READCHARERR);
			inLineBuffer[inLineOffset] = 0;
			return(REACHEDEOF);
			inLineCount++;
		}
		if ((char) readChar == '\n')
		{
			inLineBuffer[inLineOffset] = 0;
			return(R1W1_NOERR);
		}
		inLineBuffer[inLineOffset++] = (char) readChar;
		if (inLineOffset > MAXBUFFERLENGTH-1)
			return(INPUTLINETOOLONG);
	}
	return(R1W1_NOERR);
}

int readFileToProgramStrings(void)
{
    FILE * fp;
    fp = fopen("input.txt", "r");
    do
    {
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    fp = fopen("/etc/motd", "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    while ((read = getline(&line, &len, fp)) != -1) 
    {
        printf("Retrieved line of length %zu:\n", read);
        printf("%s", line);
    }

    fclose(fp);
    if (line)
        free(line);
    exit(EXIT_SUCCESS);
                            
    }
    while();
}

int main(int argc, char *argv[])
{
    readFileToProgramStrings();
    system("PAUSE");
    return EXIT_SUCCESS;
}
