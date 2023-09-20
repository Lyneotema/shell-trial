#include "shell.h"

/**
 * _eputs - input string is Printed
 * @str: The input string printed
 *
 * Return: NILL or Nothing
 **/
void _eputs(char *str)
{
	int v = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		_eputchar(str[i]);
		i++;
	}
}

/**
 * _eputchar - Character is written to stderr
 * @c:  Character to output
 *
 * Return: 1 for success
 * Upon error show -1 then set errno accordingly
 **/
int _eputchar(char c)
{
	static int f;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || f >= WRITE_BUF_SIZE)
	{
		write(2, buf, f);
		f = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * _putfd - Write character to specified fd
 * @c: Character for print
 * @fd:   descriptor File to write and print to
 * Return: 1 upon success -1 for failure and error
 * then errno is set
 */
int _putfd(char c, int fd)
{
	static int h;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || h >= WRITE_BUF_SIZE)
	{
		write(fd, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * _putsfd - input string printer
 * @str: String to prinT
 * @fd:  File Descriptor to write on
 *
 * Return: Number of characters put
 */
int _putsfd(char *str, int fd)
{
	int p = 0;

	if (!str)
		return (0);
	while (*str)
	{
		i += _putfd(*str++, fd);
	}
	return (p);
}

