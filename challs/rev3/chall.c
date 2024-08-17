#include <stdio.h>
#include <stdbool.h>
#include <string.h>

int n = 30;
char data[] = {130, 102, 131, 227, 99, 22, 112, 99, 160, 38, 98, 114, 70, 51, 160, 114, 0, 163, 194, 160, 17, 102, 50, 147, 86, 98, 226, 114, 18, 82};

bool crackme(char *input)
{
	int matches = 0;

	for (int i = 0; i < n; i++)
	{
		char c = 0;
		c |= (input[i] >> 4) & 0x0f;
		c |= (input[i] << 4) & 0xf0;
		input[i] = c;
	}

	for (int i = 0; i < n; i++)
	{
		input[i] ^= 0x55;
	}	

	for (int i = 0; i < n; i++)
	{
		//printf("%d, %d\n", input[i], data[n - i - 1]);
		if (input[i] == data[n - i - 1])
			matches++;
	}

	return matches == n;
}

int main(int argc, char **argv)
{
	if (argc != 2)
		return 1;

	if (strlen(argv[1]) != n)
		return 2;

	if (crackme(argv[1]))
		printf("Correct!\n");
	else
		printf("Incorrect!\n");
}
