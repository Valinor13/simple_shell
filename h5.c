#include "shlib.h"

char *tkn_buf = NULL;
size_t tkn_bsz = 0;
int tkn_idx = -1;

struct token_s eof_token = {
	.tlen = 0,
};

/**
 *
 *
 */
void add_to_buf(char c)
{
	char *tmp;

	tkn_buf[tkn_idx++] = c;
	if (tkn_idx >= int tkn_bsz)
	{
		tmp = _realloc(tkn_buf, tkn_bsz, tkn_bsz * 2);
		if (tmp == NULL)
		{
			perror("OOPS");
			return;
		}
		tkn_buf = tmp;
		tkn_bsz *= 2;
	}
return;
}

/**
 *
 *
 */
sauce_t *create_token(char *ptr)
{
	char *nuptr;
	token_t *tkn;

	tkn = malloc(sizeof(sauce_t));
	if (ptr == NULL)
		return (NULL);
	_memset(tkn, 0, sizeof(sauce_t));
	tkn->tlen = _strlen(ptr);
	nuptr = malloc(tkn->tlen + 1);
	if (nuptr == NULL)
	{
		free(tkn);
		return (NULL);
	}
	_strcpy(nuptr, ptr);
	tkn->txt = nuptr;
	return (tkn);
}

/**
 *
 *
 */
void free_tkn(sauce_t *tkn)
{
	if (tkn->txt != NULL)
		free(tkn->txt);
	free(tkn);
return;
}

/**
 *
 *
 */
token_t *tokenize(sauce_t *ptr)
{
	int endloop = 0;
	char nc;

	if (ptr == NULL || ptr->buffer == NULL || ptr->bsz == 0)
	{
		perror("OOPS");
		return (&eof_token);
	}
	if (tkn_buf == NULL)
	{
		tkn_bsz = 1024, tkn_buf = malloc(tkn_bsz);
		if (tkn_buf == NULL)
		{
			perror("OOPS");
			return (&eof_token);
		}
	}
	tkn_idx = 0, tkn_buf[0] = 00, nc = next_char(ptr);
	if (nc == 0 || nc == -1)
		return (&eof_token);
	while ((nc = next_char(ptr)) != -1)
	{
		switch (nc)
		{
			case 32:
			case 9:
				if (tkn_idx > 0)
					endloop = 1;
				break;
			case 10:
				if (tkn_idx > 0)
					unget_char(ptr);
				else
					add_to_buf(nc);
				endloop = 1;
				break;
			default:
				add_to_buf(nc);
				break;
		}
		if (endloop != 0)
			break;
	}
	if (tkn_idx == 0)
		return (&eof_token);
	if (tkn_idx >= tkn_bsz)
		tkn_idx -= 1;
	tkn_buf[tkn_idx] = 00, token_t *tkn = create_token(tkn_buf);
	if (tkn == NULL)
	{
		perror("Alloc failed");
		return (&eof_token);
	}
	tkn->ptr = ptr;
	return (tkn);
}
