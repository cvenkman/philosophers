/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvenkman <cvenkman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 18:43:09 by cvenkman          #+#    #+#             */
/*   Updated: 2021/09/20 20:11:59 by tphlogis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	char	*new_str;
	char	*new_str2;

	new_str = malloc(sizeof(char) * (ft_strlen(str) + 1));
	new_str2 = new_str;
	if (!new_str)
		return (NULL);
	while (*str)
	{
		*new_str2 = *str;
		new_str2++;
		str++;
	}
	*new_str2 = '\0';
	return (new_str);
}
