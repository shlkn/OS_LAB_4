#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void gamma_process(FILE *pfsf, FILE *pfgf); // function that encrypts and decrypts 
FILE*  pipe_process(); // opens pipe to program1 and returns ptr on struct FILE

int main()
{
	FILE *pfsf, *pfgf; // pipe for source file and pipe for gamma file
	// handle pipe for source string
	printf("Enter source file\n");
	pfsf = pipe_process();

	//taking gamma key from another file
	printf("Enter file that contains gamma key\n");
	pfgf = pipe_process();

	// file encryption
	gamma_process(pfsf, pfgf); 
}
FILE*  pipe_process()
{
	FILE *pipePtr; // pipe for source file
	char srcflName[256]; // source file name
	scanf("%s", srcflName);
	char program[256] = "./program1 ", *cmd;
	cmd = strcat(program, srcflName);
	pipePtr = popen(cmd, "r");
	return pipePtr;
}
void gamma_process(FILE *pfsf, FILE *pfgf)
{
	//getting gamma sequences from gamma file
	char gamma[1024]; // gamma key
	fgets(gamma, sizeof(gamma), pfgf);
	if(strlen(gamma) == 1024)
		printf("To long string, will be used first 1024 characters\n");


	// getting and encrypting source file
	char buff[1024];
	int read_cnt = 0;
	FILE *out;
	out = fopen("result.txt", "w+"); // open result file
	int keylen = strlen(gamma);
	gamma[keylen++] = '\0';
	int i = 0;
	while(fgets(buff, sizeof(buff), pfsf) != NULL) // until the end of the file is reached
	{
		read_cnt = strlen(buff);
		char resultStr[1024];
		memset(resultStr, 0, sizeof(resultStr)); 
		for(int j = 0; j < read_cnt; j++) // for each character in src sting
		{
			if(buff[j] == '\n') // if src string contains endl 
			{
				resultStr[j] = '\n'; // copy to result string
				break;
			}
			resultStr[j] = buff[j] ^ gamma[i % keylen]; // if src string < gamma string, loop in gamma string
			i++;
		}
		fputs(resultStr, out);
	}
	fclose(out);
}