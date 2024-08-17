#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>

void win(long a, long b) {
	char flag[64];

	if (a == 0xdeadbeef) {
		FILE *f = fopen("flag.txt", "r");
		fgets(flag, sizeof(flag), f);
		fclose(f);
	}

	if (b == 0xcafebabe) {
		puts(flag);
	}
}

int main()
{
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stdin, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);

	printf("This time the hall of winners added a few locks to the door.\n");
	char buf[64];

	while (true) {
		printf("Enter your name: ");
		read(0, buf, 0x256);

		char yn = 'N';
	  printf("You said you name is: %s", buf);
		printf("Enter 'Y' to confirm: ");
		scanf(" %c", &yn);
		getchar();

		if (yn == 'Y') {
			break;
		}
	}
	
	printf("Welcome %s! But you still need to use the hidden door.\n", buf);
	return 0;
}
