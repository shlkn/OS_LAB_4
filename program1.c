#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
	char flName[256];
	if(argc > 1)
		strcpy(flName, argv[1]);
	else
	{
		printf("Please enter file name\n");
		scanf("%s", flName);
	}
	FILE *in;
	in = fopen(flName, "r");
	if(in == NULL)
	{
		printf("Error, can`t open file\n");
		exit(-1);
	}



	//printf("Reading file - %s\n", flName);
	char buff[1024];
	while(fgets(buff, sizeof(buff), in) != NULL)
		printf("%s", buff);
}