/*
** EPITECH PROJECT, 2018
** 
** File description:
** 
*/

#include "lib.h"

void	getnickname(char *str)
{
	char	*tmp;
	int	tmp2 = 0;
	int	index1 = 0;
	int	index2 = 6;

       	tmp2 = strlen(str);
	tmp = malloc(sizeof(char) * tmp2 + 1);
	tmp2 = 6;
	while(index1 < tmp2) {
		tmp[index1] = str[index2];
		index1++;
		index2++;
		
	}
	tmp[index2] = '\0';
	printf("%s\n", tmp);
}

/*void	msg(char *str)
{
	char	*tmp;
	char	*tmp2;
	int	tmp = 0;
	index
	}*/
