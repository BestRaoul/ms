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
		final_size += ft_strlen_int(strr[i++]) + ft_strlen_int(joint);
	final_size -= ft_strlen_int(joint);
	res = ft_calloc(final_size + 1, sizeof(char));
	//--NULLCHECK
	i = 0;
	while (strr[i] != NULL)
	{
		strcpy(&res[ft_strlen_int(res)], strr[i++]);
		if (strr[i] != NULL)
			strcpy(&res[ft_strlen_int(res)], joint);
	}
	res[ft_strlen_int(res)] = 0;
	return (res);
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
 * Returns allocated string (start inclusive, end inclusive)
 //printf("CHOP %c(%d) -> %c(%d)\n", str[0], 0, str[end], end);
 */
char	*chop(char *str, int end)
{
	char	temp;
	char	*res;

	if (end < 0)
		return (ft_strdup(""));
	temp = str[end + 1];
	str[end + 1] = 0;
	res = ft_strdup(str);
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
	return (chop(str, i - 1));
}

/* 
 * Returns allocated string of first consecutive NON-matching characters
 */
char	*_scan_nt(char *str, int (*checker)(char c))
{
	int	i;

	i = findf(checker, str);
	return (chop(str, i - 1));
}

/* 
 * Returns allocated string of first consecutive matching characters
 * also moves the pointer along the scan
 */
char	*_scan2(char **str_ptr, int (*checker)(char c))
{
	char	*res;
	int		i;

	i = findf_nt(checker, *str_ptr);
	res = chop(*str_ptr, i - 1);
	*str_ptr+=i;
	return (res);
}

int	strarr_count(char **strarr)
{
	int	i;

	i = 0;
	while (strarr[i])
		i++;
	return (i);
}

char	**realloc_strarr_no_gc(char **strarr)
{
	char	**res;
	int		i;

	res = malloc((strarr_count(strarr) + 1) * sizeof(char *));
	if (res == NULL)
		(perror("malloc: no gc"), exit(69));
	i = 0;
	while (strarr[i])
	{
		res[i] = malloc(ft_strlen(strarr[i]) + 1);
		if (res[i] == NULL)
			(perror("malloc: no gc"), exit(69));
		ft_strlcpy(res[i], strarr[i], ft_strlen(strarr[i]) + 1);
		i++;
	}
	res[i] = NULL;
	return (res);
}
