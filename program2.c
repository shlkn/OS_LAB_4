#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void gamma_process(FILE *pfsf, FILE *pfgf, char *result_fl_name);// function that encrypts and decrypts 

int main()
{
	// handle pipe for source string
	printf("Enter source file\n");
	char srcflName[256];
	scanf("%s", srcflName);
	char program[256] = "./program1 ", *cmd;
	cmd = strcat(program, srcflName);
	FILE *pfsf; // pipe for source file
	pfsf = popen(cmd, "r");

	//taking gamma key from another file
	printf("Enter file that contains gamma key\n");
	char gamflName[256];
	scanf("%s", gamflName);
	char program2[256] = "./program1 ";
	cmd = strcat(program2, gamflName);
	FILE *pfgf; // pipe for gamma file
	pfgf = popen(cmd, "r");

	char result_fl_name[] = "result.txt";
	gamma_process(pfsf, pfgf, result_fl_name); // file encryption
	// encrypted
	/*char decrypted_fl_name[] = "resultdec.txt";
	char program3[256] = "./program1 ";
	cmd = strcat(program3, result_fl_name);
	pfsf = popen(cmd, "r");
	gamma_process(pfsf, pfgf, decrypted_fl_name);*/
	//decrypted
}

void gamma_process(FILE *pfsf, FILE *pfgf, char *result_fl_name)
{
	char gamma[1024]; // gamma key
	fgets(gamma, sizeof(gamma), pfgf);
	if(strlen(gamma) == 1024)
		printf("To long string, will be used first 1024 characters\n");



	char buff[1024];
	int read_cnt = 0;
	FILE *out;
	out = fopen(result_fl_name, "w+");
	int keylen = strlen(gamma);
	gamma[keylen++] = '\0';
	int i = 0;
	while(fgets(buff, sizeof(buff), pfsf) != NULL)
	{
		read_cnt = strlen(buff);
		char resultStr[1024];
		memset(resultStr, 0, sizeof(resultStr));
		for(int j = 0; j < read_cnt; j++)
		{
			if(buff[j] == '\n')
			{
				resultStr[j] = '\n';
				break;
			}
			resultStr[j] = buff[j] ^ gamma[i % keylen];
			i++;
		}
		fputs(resultStr, out);
	}
	fclose(out);
}