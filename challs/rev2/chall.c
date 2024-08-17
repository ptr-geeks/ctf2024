#include <stdio.h>
#include <string.h>

char *flag = "ptr{N0w_foR_th3_r34l_reVerS1ng}";

int main()
{
	char input[50];
	printf("Enter the flag: ");
	fgets(input, 50, stdin);

	for (int i = 0; i < strlen(flag); i++)
	{
		if (input[i] != flag[i])
		{
			printf("Incorrect!\n");
			return 1;
		}
	}

	printf("Correct!\n");
}
