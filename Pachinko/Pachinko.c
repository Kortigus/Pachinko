#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MINIMUM (100)
#define LINESIZE (1024)

/* Spins the slots */
void playSlots(int slot[], size_t n)
{
	size_t i;
	for (i = 0; i < n; i++)
	{
		slot[i] = rand() % 5;
	}
}

/* Gets the amount the player wants to bet and stores it into bet */
int insertCoin(size_t* bet, size_t* credits)
{
	char line[LINESIZE];
	*bet = 0;
	while (1)
	{
		printf("How much would you like to bet?\n");
		if (!fgets(line, LINESIZE, stdin))
		{
			clearerr(stdin);
			printf("Error reading line");
			return 1;
		}
		if (sscanf_s(line, "%d", bet) != 1)
		{
			printf("%s", "Error reading for bet, exiting game");
			return 0;
		}
		if (*bet >= MINIMUM && *bet <= *credits)
		{
			return 1;
		}
		else if (*bet > *credits)
		{
			printf("%s\n", "You can't bet more than you have!");
		}
		else
		{
			printf("%s\n", "The minimum to bet is 100 Credits, please pick a larger number");
		}
	}
}

/* Checks if the slots match and pays the player accordingly */
void payOut(size_t slot[], size_t* credits, size_t* bet)
{
	size_t i;
	for (i = 0; i < 3; i++)
	{
		switch (slot[i])
		{
		case 0:
		{
			printf("%s", "@");
			break;
		}
		case 1:
		{
			printf("%s", "#");
			break;
		}
		case 2:
		{
			printf("%s", "$");
			break;
		}
		case 3:
		{
			printf("%s", "%");
			break;
		}
		case 4:
		{
			printf("%s", "7");
			break;
		}
		default:
		{
			printf("%s", "Error");
			break;
		}
		}
	}
	if (slot[0] == slot[1] && slot[0] == slot[2])
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
	size_t credits = 1000;
	size_t bet = 0;

	srand((unsigned)time(NULL));

	while (1)
	{
		if (credits < MINIMUM)
		{
			printf("%s\n", "Sorry, you don't have enough credits to continue playing!");
			exit(1);
		}
		printf("%s %d %s\n", "You have ", credits, " Credits");
		if (insertCoin(&bet, &credits) != 1)
		{
			return 1;
		}
		playSlots(slot, 3);
		payOut(slot, &credits, &bet);
	}

	return 0;
}