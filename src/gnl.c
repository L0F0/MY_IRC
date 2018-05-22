/*
** gnl.c for tictactoe in /home/robin.milas/Colle/CPE_2016_stumper6
** 
** Made by Robin MILAS
** Login   <robin.milas@epitech.net>
** 
** Started on  Wed May 24 10:15:49 2017 Robin MILAS
** Last update Wed May 24 13:56:16 2017 Ynaiss PHERON
*/

#include <unistd.h>
#include <stdlib.h>
#include "gnl.h"

static long	find_pos(const char *str, const char c)
{
	long		index;

	if (str == NULL)
		return (-1);
	index = 0;
	while (str[index] != '\0' && str[index] != c)
		index += 1;
	if (str[index] == c)
		return (index);
	return (-1);
}

static char	*my_strdup(const char *str)
{
	long		len;
	char		*res;
	long		index;
	
	len = find_pos(str, '\0');
	if (len < 0)
		return (NULL);
	if ((res = malloc(len + 1)) == NULL)
		return (NULL);
	index = 0;
	while (str[index] != '\0')
	{
		res[index] = str[index];
		index += 1;
	}
	res[index] = '\0';
	return (res);
}

static char	*my_append(const char *store,
			   const char *buf, const long r_size)
{
	long		index;
	char		*res;
	long		len;

	len = (store != NULL) ? find_pos(store, '\0') : 0;
	if ((res = malloc(len + r_size + 1)) == NULL)
		return (NULL);
	index = 0;
	if (store != NULL)
	{
		while (index < len)
		{
			res[index] = store[index];
			index += 1;
		}
	}
	while (index < len + r_size)
	{
		res[index] = buf[index - len];
		index += 1;
	}
	res[index] = '\0';
	return (res);
}

static char	*cut(char **store)
{
	char		*res;
	long		index;

	res = *store;
	*store = NULL;
	if ((index = find_pos(res, '\n')) < 0)
	{
		if (res != NULL && res[0] == '\0')
		{
			free(res);
			res = NULL;
		}
		return (res);
	}
	res[index] = '\0';
	if ((*store = (my_strdup(&(res[index + 1])))) == NULL)
		return (GNL_ERROR);
	return (res);
}

char		*gnl(const int fd)
{
	static char	*store = NULL;
	char		buf[READ_SIZE];
	long		r_size;
	char		*tmp;
	
	if (fd < 0)
	{
		free(store);
		store = NULL;
		return (store);
	}
	while (find_pos(store, '\n') < 0)
	{
		r_size = read(fd, buf, READ_SIZE);
		if (r_size < 0)
			return (GNL_ERROR);
		if (r_size == 0)
			return (cut(&store));
		if ((tmp = my_append(store, buf, r_size)) == NULL)
			return (GNL_ERROR);
		free(store);
		store = tmp;
	}
	return (cut(&store));
}
