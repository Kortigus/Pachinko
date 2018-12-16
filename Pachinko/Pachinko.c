#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MINIMUM (100)
#define LINESIZE (1024)

/* Chooses a random number between 0 and 4 inclusively */
void pickRandom(int* number)
{
	*number = rand() % 4;
}

/* Spins the slots */
void playSlots(int slot[], size_t n)
{
	size_t i;
	for (i = 0; i < 3; i++)
	{
		pickRandom(&slot[i]);
	}
}

/* Gets the amount the player wants to bet and stores it into bet */
int insertCoin(int* bet)
{
	char line[LINESIZE];
	*bet = 0;
	while (1)
	{
		printf("How much would you like to bet?");
		if (!fgets(line, LINESIZE, stdin))
		{
			clearerr(stdin);
			printf("Error reading line");
			return 1;
		}
		if (sscanf_s(line, "%d", bet) == 1 && *bet >= 100)
		{
			return 0;
		}
		printf("%s\n", "The minimum to bet is 100 Credits, please pick a larger number");
	}
}

/* Checks if the slots match and pays the player accordingly */
void payOut(int slot[], int* credits, int* bet)
{
	size_t i;
	int* p = &slot[0];
	for (i = 0; i < 3; i++)
	{
		switch (slot[i])
		{
		case 0: printf("%s", "@");
			    break;
		case 1: printf("%s", "#");
				break;
		case 2: printf("%s", "$");
				break;
		case 3: printf("%s", "%");
				break;
		case 4: printf("%s", "7");
				break;
		default: printf("%s", "Error");
				break;
		}
	}
	if (*p == *(p + 1) && *p == *(p + 2))
	{
		printf(" %s\n", " JACKPOT!!!");
		*credits += *bet * 2;
	}
	else
	{
		printf(" %s\n", "Try again");
		*credits -= *bet;
	}
}

/* Drives the program */
int main(void)
{
	int slot[3];
	int credits = 1000;
	int bet = 0;

	srand((unsigned)time(NULL));

	while (1)
	{
		if (credits < 100)
		{
			printf("%s\n", "Sorry, you don't have enough credits to continue playing!");
			exit(1);
		}
		printf("%s %d %s\n", "You have ", credits, " Credits");
		insertCoin(&bet);
		playSlots(slot, 3);
		payOut(slot, &credits, &bet);
	}

	return 0;
}