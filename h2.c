#include "shlib.h"

/**
 * _strcmp - compare two strings
 * @s1: the first
 * @s2: the second
 * Return: the measure
 */

int _strcmp(char *s1, char *s2)
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

/**
 * _strlen - return the length of the string
 *@s: the length of the string
 *
 * Return: the length(x)
 */

size_t _strlen(char *s)
{
size_t x;
x = 0;
while (*(s + x) != '\0')
{
x++;
}
return (x);
}

/**
 * *_strcpy - copy a string
 * @dest: destination
 * @src: source
 *
 * Return: the copy
 */
char *_strcpy(char *dest, char *src)
{
int x, y;
x = _strlen(src);
for (y = 0; y <= x; y++)
{
dest[y] = src[y];
}
return (dest);
}

/**
 * _puts - print a string
 * @str: the string
 * Return: nada
 */

void _puts(char *str)
{
int x;
for (x = 0; str[x] != '\0'; x++)
{
_putchar(str[x]);
}
_putchar('\n');
return;
}

/**
 * _putchar - writes the character c to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char c)
{
return (write(1, &c, 1));
}
