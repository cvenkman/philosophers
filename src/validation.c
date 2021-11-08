/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvenkman <cvenkman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 19:29:01 by cvenkman          #+#    #+#             */
/*   Updated: 2021/11/08 20:30:16 by cvenkman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

char	**validation(char **argv, int i)
{
	int		j;
	int		len;
	char	**new_arg;

	j = 0;
	new_arg = malloc(sizeof(char *) * (arr_len(argv)));
	while (argv[i])
	{
		new_arg[j] = ft_strtrim(argv[i], " 	");
		if (!new_arg[j])
			return (NULL);
		len = 0;
		while (new_arg[j][len])
		{
			if (!ft_isdigit(new_arg[j][len]) && new_arg[j][len] != '+')
				return (NULL);
			len++;
		}
		i++;
		j++;
	}
	
	new_arg[j] = NULL;
	return (new_arg);
}