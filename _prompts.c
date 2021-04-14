#include "shlib.h"

/**
 * _prompt1 - prints $
 * Return: returns void
 */
void _prompt1(void)
{
	write(STDOUT_FILENO, "$ ", 2);
}

/**
 * _prompt2 - prints >
 * Return: returns void
 */
void _prompt2(void)
{
	write(STDOUT_FILENO, "> ", 2);
}

/**
 * _prompt3 - prints #
 * Return: returns void
 */
void _prompt3(void)
{
	write(STDOUT_FILENO, "# ", 2);
}

/**
 * _pterror - prints an error message
 * @av: program name
 * @tknptr: path and command
 * @ln_cnt: line counts
 * Return: returns void
 */
void _pterror(char **av, char **tknptr, int *ln_cnt)
{
	int i;
	char *tmp = NULL, *tmp2 = NULL, *cnt = NULL;

	cnt = printint(ln_cnt);
	tmp = _strcat(av[0], ": ");
	tmp2 = _strcat(tmp, cnt);
	free(cnt), free(tmp), tmp = NULL;
	tmp = _strcat(tmp2, ": ");
	free(tmp2), tmp2 = NULL;
	tmp2 = _strcat(tmp, tknptr[0]);
	free(tmp), tmp = NULL;
	tmp = _strcat(tmp2, ": not found\n");
	free(tmp2);
	i = _strlen(tmp);
	write(STDERR_FILENO, tmp, i);
	free(tmp);
return;
}

/**
* printint - Conveting integer data to a string
* @ln_cnt: pointer to total line count
*
* Return: pointer to string of numeric characters
*/
char *printint(int *ln_cnt)
{
	char *tmp;
	unsigned int neg;
	int i, rem, num, n, len, x;
/*
 * iterator, last digit, initial integer, copy of initial integer,
 * length of input, length for negatives
 */
	n = *ln_cnt;
	num = n;
	len = i = 0;
	while (n != 0)	/** Integer length */
	{
		len++;
		n /= 10;
	}
	x = len;
	if (num == 0) /** Zero case */
	{
		tmp = malloc(2);
		tmp[0] = '0';
		tmp[1] = '\0';
		return (tmp);
	}
	else if (num < 0) /** Negative case */
	{
		x++; /** Account for dash indicator */
		tmp = malloc(len + 2); /** Dash indicator and null byte */
		tmp[0] = '-';
		neg = num * -1;
	}
	else /** Positive case */
		tmp = malloc(len + 1), neg = num;
	for (; i < len; i++)
	{
		rem = neg % 10; /** Isolate last digt */
		neg /= 10; /** Shorten integer */
		tmp[x - (i + 1)] = (rem + '0'); /** Fill, right to left */
	}
	tmp[x] = '\0';
	return (tmp);
}
