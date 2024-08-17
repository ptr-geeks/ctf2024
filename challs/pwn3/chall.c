#include <stdio.h>
#include <stdlib.h>

void win() {
	system("/bin/sh");
}

int main() {
	printf("Welcome to the hall of winners!\n");

	char buf[32];
	printf("Enter your name: ");
	scanf("%s", buf);

	printf("Hello, %s!\n", buf);
	printf("The rightful winners are asked to kindly use the hidden entrance.\n");

	return 0;
}
