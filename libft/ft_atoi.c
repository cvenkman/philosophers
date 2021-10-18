/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvenkman <cvenkman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 18:41:57 by cvenkman          #+#    #+#             */
/*   Updated: 2021/10/18 16:37:10 by cvenkman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(char const *str)
{
	unsigned int	i;
	int				minus;
	int				num;

	num = 0;
	i = 0;
	minus = 0;
	while ((str[i] > 8 && str[i] < 14) || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			minus++;
		i++;
	}
	while ((str[i] >= '0' && str[i] <= '9') && str[i] != '\0')
	{
		num = num * 10 + str[i] - '0';
		i++;
	}
	if (minus % 2 != 0)
		num *= -1;
	return (num);
}
