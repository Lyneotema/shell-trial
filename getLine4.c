#include "shell.h"
/**
 * input_buf - Chained commands for Buffer.
 * @info: The Parameter struct
 * @buf: The Pointer to buffer
 * @len: Pointer to len var.
 * Return: The Bytes read
 */
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t s = 0;
	size_t len_p = 0;

	if (!*len) /* if nothing is left in the Buffer, fill it */
	{
		/*bfree((void **)info->cmd_buf);*/
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		s = getline(buf, &len_p, stdin);
#else
		s = _getline(info, buf, &len_p);
#endif
		if (s > 0)
		{
			if ((*buf)[s - 1] == '\n')
			{
				(*buf)[s - 1] = '\0'; /* Remove the trailing newline */
				s--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);
			/* if (_strchr(*buf, ';')) is this a command chain? */
			{
				*len = s;
				info->cmd_buf = buf;
			}
		}
	}
	return (s);
}

/**
 * get_input - Finds line minus newline
 * @info: The Parameter struct
 * Return: The Bytes read
 */
ssize_t get_input(info_t *info)
{
	static char *buf; /* The ';' command chain Buffer */
	static size_t i, j, len;
	ssize_t s = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	s = input_buf(info, &buf, &len);
	if (s == -1) /* EOF */
		return (-1);
	if (len) /* Then we have commands left in chain buffer */
	{
		j = i; /* init new iterator to the current buf position */
		p = buf + i; /* Get address for return */

		check_chain(info, buf, &j, i, len);
		while (j < len) /* Iterate to the ; or end */
		{
			if (is_chain(info, buf, &j))
				break;
			j++;
		}

		i = j + 1; /* Increase past nulled ';'' */
		if (i >= len) /* It has hit end of buffer? */
		{
			i = len = 0; /* Reset the position and length */
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p; /* It Passes back pointer to the current command position */
		return (_strlen(p)); /* Return length of current command */
	}

	*buf_p = buf; /* else not Chain, Pass back Buffer from _getline() */
	return (s); /* return the length of buffer from _getline() */
}

/**
 * read_buf - It reads Buffer
 * @info: The parameter struct.
 * @buf: BUFFER.
 * @i: SIZE
 * Return: s
 */
ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
	ssize_t s = 0;

	if (*i)
		return (0);
	s = read(info->readfd, buf, READ_BUF_SIZE);
	if (s >= 0)
		*i = s;
	return (s);
}

/**
 * _getline - Finds next line of input from STDIN
 * @info: The parameter struct
 * @ptr: Pointer to address of buffer, preallocated or NULL
 * @length: This is size of the preallocated ptr buffer if not NULL
 * Return: v
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t s = 0, v = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		v = *length;
	if (i == len)
		i = len = 0;

	s = read_buf(info, buf, &len);
	if (s == -1 || (s == 0 && len == 0))
		return (-1);

	c = _strchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, v, v ? v + k : k + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (v)
		_strncat(new_p, buf + i, k - i);
	else
		_strncpy(new_p, buf + i, k - i + 1);

	v += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = v;
	*ptr = p;
	return (v);
}

/**
 * sigintHandler - It Blocks ctrl-C
 * @sig_num: Signal number.
 * Return: void
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}

