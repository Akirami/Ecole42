/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emassard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 18:55:04 by emassard          #+#    #+#             */
/*   Updated: 2020/02/18 18:55:04 by emassard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void
	ft_putstr_fd(char const *s, int fd)
{
	while (*s)
	{
		write(fd, &(*s), 1);
		s++;
	}
}