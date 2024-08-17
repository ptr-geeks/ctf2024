#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

const int note_size = 100;

void note_menu()
{
	printf("1. Add note\n");
	printf("2. View note\n");
	printf("3. Edit note\n");
	printf("4. Delete note\n");
	printf("5. Exit\n");
	printf("Enter choice: ");
}

void note_add(char *notes)
{
	printf("Enter note number: ");

	int note_num;
	scanf("%d", &note_num);
	getchar();

	printf("Enter note: ");
	fgets(notes + note_num * note_size, note_size, stdin);
}

void note_view(char *notes)
{
	printf("Enter note number: ");

	int note_num;
	scanf("%d", &note_num);


	printf("Note %d: ", note_num);
	write(1, notes + note_num * note_size, note_size);
	printf("\n");
}

void note_edit(char *notes)
{
	printf("Enter note number: ");

	int note_num;
	scanf("%d", &note_num);
	getchar();

	printf("Enter new note: ");
	fgets(notes + note_num * note_size, note_size, stdin);
}

void note_delete(char *notes)
{
	printf("Enter note number: ");

	int note_num;
	scanf("%d", &note_num);

	memset(notes + note_num * note_size, 0, note_size);
}

int main()
{
	char *flag = (char *)malloc(50);
	FILE *f = fopen("flag.txt", "r");
	if (f == NULL)
		exit(1);
	fgets(flag, 50, f);

	char *notes = (char *)malloc(10 * note_size * sizeof(char *));

	printf("Welcome to the note-taking program!\n");
	printf("You can take up to 10 notes, each up to %d characters long.\n", note_size);
	while (true)
	{
		note_menu();

		int choice;
		scanf("%d", &choice);

		if (choice == 1)
			note_add(notes);
		else if (choice == 2)
			note_view(notes);
		else if (choice == 3)
			note_edit(notes);
		else if (choice == 4)
			note_delete(notes);
		else if (choice == 5)
			break;
		else
			printf("Invalid choice\n");
	}
	
	return 0;
}
