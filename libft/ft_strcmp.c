/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haitkadi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 16:52:53 by haitkadi          #+#    #+#             */
/*   Updated: 2021/07/08 19:08:04 by haitkadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_strcmp(char *s1, char *s2)
{
	unsigned char	*us1;
	unsigned char	*us2;
	int				i;

	if (!s1 && !s2)
		return (0);
	if (!s1 || !s2)
		return (1);
	us1 = (unsigned char *) s1;
	us2 = (unsigned char *) s2;
	i = 0;
	while (us1[i] && us2[i] && us1[i] == us2[i])
		i++;
	return (us1[i] - us2[i]);
}
