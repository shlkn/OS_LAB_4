#include <stdio.h>
#include <stdlib.h>

int main()
{
	printf("Please enter file name\n");
	char flName[256];
	scanf("%s", flName);
	FILE *in;
	in = fopen(flName, "r");
	if(in == NULL)
	{
		printf("Error, can`t open file\n");
		exit(-1);
	}



	printf("Reading file - %s\n", flName);
	char buff[1024];
	while(fgets(buff, sizeof(buff), in) != NULL)
		printf("%s", buff);
}