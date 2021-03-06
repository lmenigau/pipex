#include <stdlib.h>
#include "pipex.h"

size_t	countword(char *s, char c)
{
	size_t	wc;

	wc = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s)
			wc++;
		while (*s && *s != c)
			s++;
	}
	return (wc);
}

size_t	copyword(char **arr, char *str, char c)
{
	size_t	index;
	char	*start;

	index = 0;
	while (*str)
	{
		while (*str && *str == c)
			str++;
		start = str;
		while (*str && *str != c)
			str++;
		if (str == start)
			break ;
		arr[index] = malloc(str - start + 1);
		if (!arr[index])
			return (index);
		ft_memcpy(arr[index], start, str - start);
		arr[index++][str - start] = '\0';
	}
	arr[index] = NULL;
	return (index);
}

char	**ft_split(char const *s, char c)
{
	char		**arr;
	size_t		wc;
	size_t		index;

	wc = countword((char *)s, c);
	arr = malloc(sizeof(char *) * (wc + 1));
	if (!arr)
		return (NULL);
	index = copyword(arr, (char *)s, c);
	if (index < wc)
	{
		while (index--)
			free(arr[index]);
		free(arr);
		return (NULL);
	}
	return (arr);
}
