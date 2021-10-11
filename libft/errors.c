/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvenkman <cvenkman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/19 19:02:31 by cvenkman          #+#    #+#             */
/*   Updated: 2021/09/20 18:17:33 by cvenkman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	putstr_exit(char *str)
{
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", 2);
	exit(EXIT_FAILURE);
}

void	perror_exit(char *str)
{
	perror(str);
	exit(EXIT_FAILURE);
}
