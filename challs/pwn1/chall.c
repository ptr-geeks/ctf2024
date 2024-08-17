#include <stdio.h>
#include <sys/random.h>
#include <stdbool.h>

int money = 100;
int casino_money = 1000000;

int random()
{
	int num;
	getrandom(&num, sizeof(num), 0);
	return num;
}

int main()
{
	printf("Welcome to the Casino!\n");

	long bet;
	int guess;
	while (money > 0)
	{
		printf("You have %d credits.\n", money);
		printf("How much do you want to bet? ");
		scanf("%ld", &bet);

		if ((int)bet > money)
		{
			printf("You don't have enough credits.\n");
			continue;
		}

		if (bet < 0)
		{
			printf("You can't bet negative credits.\n");
			continue;
		}

		printf("Guess the sum of two dice: ");
		scanf("%d", &guess);

		printf("Rolling the dice...\n");
		int dice_1 = random() % 6 + 1;
		int dice_2 = random() % 6 + 1;
		int sum = dice_1 + dice_2;

		if (sum == guess)
		{
			printf("You won!\n");
			money += bet;
			casino_money -= bet;
		}
		else
		{
			printf("You lost!\n");
			money -= bet;
			casino_money += bet;
		}

		if (casino_money < 0)
		{
			printf("Congratulations! You broke the casino!\n");
			char flag[100];
			FILE *f = fopen("flag.txt", "r");
			fgets(flag, sizeof(flag), f);
			printf("Here is your flag: %s\n", flag);
			return 0;
		}
	}

	printf("You lost all your credits. Better luck next time!\n");
	return 0;
}
