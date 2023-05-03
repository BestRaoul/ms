#include "ms.h"

/*
 * Returns allocated string of all substrings joined
 */
char	*join(char **strr, char *joint)
{
	char	*res;
	int		final_size;
	int		i;

	final_size = 0;
	i = 0;
	while (strr[i] != NULL)
		final_size += len(strr[i++]) + len(joint);
	final_size -= len(joint);
	res = calloc(final_size + 1, sizeof(char));
	//--NULLCHECK
	i = 0;
	while (strr[i] != NULL)
	{
		strcpy(&res[len(res)], strr[i++]);
		strcpy(&res[len(res)], joint);
	}
	res[len(res)] = 0;
	return (res);
}

/* 
 * Returns index of first occurence of char
 */
int	find(char c, char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

/* 
 * Returns index of first matching char
 */
int	findf(int (*match)(char), char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (match(str[i]))
			return (i);
		i++;
	}
	return (-1);
}

/* 
 * Returns index of first NON-matching char
 */
int	findf_nt(int (*match)(char c), char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (match(str[i]) == 0)
			return (i);
		i++;
	}
	return (-1);
}

/* 
 * Returns length of string
 */
int	len(char *str)
{
	return (strlen(str));
}

/* 
 * Returns count of a char occurences in string
 */
int	count(char c, char *str)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (str[i])
	{
		count += str[i] == c;
		i++;
	}
	return (count);
}

/* 
 * Returns allocated string (start inclusive, end exclusive)
 //printf("CHOP %c(%d) -> %c(%d)\n", str[0], 0, str[end], end);
 */
char	*chop(char *str, int end)
{
	char	temp;
	char	*res;

	if (end < 0)
		return (strdup(""));
	temp = str[end + 1];
	str[end + 1] = 0;
	res = strdup(str);
	str[end + 1] = temp;
	return (res);
}

/* 
 * Returns allocated string of first consecutive matching characters
 */
char	*_scan(char *str, int (*checker)(char c))
{
	int	i;

	i = findf_nt(checker, str);
	if (i < 0)
		i = len(str);
	return (chop(str, i - 1));
}

/* 
 * Returns allocated string of first consecutive NON-matching characters
 */
char	*_scan_nt(char *str, int (*checker)(char c))
{
	int	i;

	i = findf(checker, str);
	if (i < 0)
		i = len(str);
	return (chop(str, i - 1));
}
