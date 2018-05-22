/*
** EPITECH PROJECT, 2018
** MY_IRC
** File description:
** command2.c
*/

#include "lib.h"

int	find_space(char *str)
{
	int	i = 0;

	while (str[i] != '\0') {
		if (str[i] == ' ')
			return (i + 1);
		i++;
	}
	return (-1);
}

char	*word_after_space(char *str)
{
	char	*tmp;
	int index1 = 0;
	int index2 = 0;

	tmp = malloc(sizeof(char) * strlen(str) + 1);
	index2 = find_space(str);
	while(str[index2]) {
		tmp[index1] = str[index2];
		index1++;
		index2++;

	}
	tmp[index1] = '\0';
	return (tmp);
}

