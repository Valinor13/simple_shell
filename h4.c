#include "shlib.h"

/**
 * _strcmp2 - compare two strings
 * @s1: the first
 * @s2: the second
 * Return: the measure
 */
int _strcmp2(char *s1, char *s2)
{
	int y, x;

	for (y = 0; s1[y] != 00; y++)
	{
		if ((s1[y]) == (s2[y]))
		{
			x = 0;
			continue;
		}
		else if (s1[y] != s2[y])
		{
			x = (s1[y] - s2[y]);
			break;
		}
	}
return (x);
}
