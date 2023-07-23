#include "shell.h"

/**
* input_buffer - Sequences of commands linked together by buffers
* @info: parameter data structure
* @buffer: buffer's memory location
* @length: variable-length address
*
* Return: number of bytes received
*/

ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
    ssize_t r = 0;
    size_t len_p = 0;

    if (!*len) /* if nothing left in the buffer, fill it */
    {
        /*bfree((void **)info->cmd_buf);*/
        free(*buf);
        *buf = NULL;
        signal(SIGINT, sigintHandler);
#if USE_GETLINE
        r = getline(buf, &len_p, stdin);
#else
        r = _getline(info, buf, &len_p);
#endif
        if (r > 0)
        {
            if ((*buf)[r - 1] == '\n')
            {
                (*buf)[r - 1] = '\0'; /* remove trailing newline */
                r--;
            }
            info->linecount_flag = 1;
            remove_comments(*buf);
            build_history_list(info, *buf, info->histcount++);
            /* if (_strchr(*buf, ';')) is this a command chain? */
            {
                *len = r;
                info->cmd_buf = buf;
            }
        }
    }
    return (r);
}

/**
* get_input_buffer - Obtains a line devoid of the newline character
* @info: parameter data structure
*
* Return: number of bytes received
*/
ssize_t get_input(info_t *info)
{
    static char *buf; /* the ';' command chain buffer */
    static size_t i, j, len;
    ssize_t r = 0;
    char **buf_p = &(info->arg), *p;

    _putchar(BUF_FLUSH);
    r = input_buf(info, &buf, &len);
    if (r == -1) /* EOF */
        return (-1);
    if (len) /* we have commands left in the chain buffer */
    {
        j = i; /* init new iterator to current buf position */
        p = buf + i; /* get pointer for return */

        check_chain(info, buf, &j, i, len);
        while (j < len) /* iterate to semicolon or end */
        {
            if (is_chain(info, buf, &j))
                break;
            j++;
        }

        i = j + 1; /* increment past nulled ';'' */
        if (i >= len) /* reached end of buffer? */
        {
            i = len = 0; /* reset position and length */
            info->cmd_buf_type = CMD_NORM;
        }
        *buf_p = p; /* pass back pointer to current command position */
        return (_strlen(p)); /* return length of current command */
    }
    *buf_p = buf; /* else not a chain, pass back buffer from _getline() */
    return (r); /* return length of buffer from _getline() */
}

/**
* read_buffer - retrieves content from a data
* @info: parameter data structure
* @buffer: data storage buffer
* @index: dimension
*
* Return: number of bytes received
*/
ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
    ssize_t r = 0;

    if (*i)
        return (0);
    r = read(info->readfd, buf, READ_BUF_SIZE);
    if (r >= 0)
        *i = r;
    return (r);
}

/**
* get_line - Retrieves the subsequent input line from STDIN
* @info: parameter data struct
* @ptr: Pointer buffer's address, either preassigned or NULL
* @length: if the preallocated ptr buffer is not NULL, determine the size
*
* Return: s
*/
ssize_t _getline(info_t *info, char **ptr, size_t *length)
{
    static char buf[READ_BUF_SIZE];
    static size_t i, len;
    size_t k;
    ssize_t r = 0, s = 0;
    char *p = NULL, *new_p = NULL, *c;

    p = *ptr;
    if (p && length)
        s = *length;
    if (i == len)
        i = len = 0;
    r = read_buf(info, buf, &len);
    if (r == -1 || (r == 0 && len == 0))
        return (-1);
    c = _strchr(buf + i, '\n');
    k = c ? 1 + (unsigned int)(c - buf) : len;
    new_p = _realloc(p, s, s ? s + k : k + 1);
    if (!new_p) /* MALLOC FAILURE! */
        return (p ? free(p), -1 : -1);
    if (s)
        _strncat(new_p, buf + i, k - i);
    else
        _strncpy(new_p, buf + i, k - i + 1);
    s += k - i;
    i = k;
    p = new_p;
    if (length)
        *length = s;
    *ptr = p;
    return (s);
}

/**
 * sigintHandler -  A signal handler function
 * to block the CTRL-C (SIGINT) signal.
 * @sig_num: The signal no. that triggered the handler (unused in this function).
 *
 * Return: This function doesn't return any value.
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
    _puts("\n");
    _puts("$ ");
    _putchar(BUF_FLUSH);
}
