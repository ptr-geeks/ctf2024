#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

const int size = 50;
const int obstacles = 250;
char maze[size][size];

void genmaze(int n, int m) {
	// Clear maze
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			maze[i][j] = ' ';
		}
	}

	// Add walls
	for (int i = 0; i < n; i++) {
		maze[i][0] = '#';
		maze[i][m - 1] = '#';
	}
	for (int i = 0; i < m; i++) {
		maze[0][i] = '#';
		maze[n - 1][i] = '#';
	}

	// Add obstacles
	for (int i = 0; i < obstacles; i++) {
		int x = rand() % (n - 2) + 1;
		int y = rand() % (m - 2) + 1;
		maze[x][y] = '#';
	}

	// Add an exit
	while (true) {
		int x = rand() % (n - 2) + 1;
		int y = rand() % (m - 2) + 1;
		if (maze[x][y] == ' ') {
			maze[x][y] = 'E';
			break;
		}
	}
}

void printmaze(int n, int m, int x, int y) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (i == x && j == y) {
				printf("P");
				continue;
			}
			printf("%c", maze[i][j]);
		}
		printf("\n");
	}
}

int main() {
	srand(time(NULL));

	genmaze(size, size);
	
	int x = -1, y = -1;
	while (true) {
		x = rand() % (size - 2) + 1;
		y = rand() % (size - 2) + 1;
		if (maze[x][y] == ' ') {
			break;
		}
	}

	while (true) {
		//printmaze(size, size, x, y);
		
		char c;
		scanf(" %c", &c);
		if (c == 'w')
			x--;
		else if (c == 's')
			x++;
		else if (c == 'a')
			y--;
		else if (c == 'd')
			y++;
		else
			continue;

		if (maze[x][y] == '#') {
			break;
		}

		if (maze[x][y] == 'E') {
			char flag[100];
			FILE *f = fopen("flag.txt", "r");
			fgets(flag, 100, f);
			fclose(f);
			printf("%s", flag);
			break;
		}
	}

	return 0;
}
