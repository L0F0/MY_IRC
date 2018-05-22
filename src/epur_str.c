/*
** EPITECH PROJECT, 2018
** MY_IRC
** File description:
** epur_str.c
*/

#include "lib.h"

void	epur_str(char *str)
{
	for (int i = 0; str[i]; i++) {
		if (str[i] == '\n')
			str[i] = '\0';
	}
}
