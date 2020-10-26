/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_bonus_data.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emassard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 07:04:24 by emassard          #+#    #+#             */
/*   Updated: 2020/03/02 07:04:27 by emassard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

bool
	check_c_range_double(char c)
{
	if ((c >= 48 && c <= 57) || (c >= 45 && c <= 46))
		return (true);
	return (false);
}

char
	*get_point(char *s, double coor[3])
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	while (ft_strchr("\t\v\n\f\r ", *s))
		s++;
	while (s && s[i] && check_c_range_double(s[i]))
	{
		while (s[i] && check_c_range_double(s[i]))
			i++;
		tmp = ft_strsub(s, 0, i);
		coor[j] = (double)ft_atof(tmp);
		free(tmp);
		s = &(*(s + i));
		j++;
		i = 0;
		if (s && ft_strchr("\t\v\n\f\r ", *s) && j == 3)
			return (s);
		if (s && ft_strchr("\t\v\n\f\r ", *s))
			return (NULL);
		i++;
	}
	return ((j == 3) ? s : NULL);
}

char
	*get_color(char *s, int color[3])
{
	int		i;
	int		j;
	char	*tmp;

	j = 0;
	while ((i = 0) || (s && *s && ft_strchr("\t\v\n\f\r, ", *s)))
		s++;
	while (s && s[i] && check_c_range_uint(s[i]))
	{
		while (s[i] && check_c_range_uint(s[i]))
			i++;
		tmp = ft_strsub(s, 0, i);
		color[j] = ft_atoi(tmp);
		free(tmp);
		j++;
		s = &(*(s + i));
		i = -1;
		(*s == ',') ? s++ : s;
		if (ft_strchr("\t\v\n\f\r ", *s) && j == 3)
			return (s);
		if (ft_strchr("\t\v\n\f\r ", *s))
			return (NULL);
		i++;
	}
	return ((j == 3) ? s : NULL);
}

double
	get_precision(const char *str)
{
	double	prec;
	double	size;
	char	*tmp;
	int		i;

	i = 0;
	str++;
	while (str && str[i] && str[i] >= '0' && str[i] <= '9')
		i++;
	tmp = ft_strsub(str, 0, i);
	prec = ft_atoi(tmp);
	free(tmp);
	size = ft_size_int(prec);
	prec = prec * pow(10, -size);
	return (prec);
}

double
	ft_atof(char *str)
{
	double	nb;
	int		sign;

	sign = 1;
	while (str && *str && ft_strchr("\t\v\n\f\r, ", *str))
		str++;
	if (*str && (*str == '-' || *str == '+'))
	{
		sign = (*str == '-') ? -1 : 1;
		str++;
	}
	if ((nb = 0) || *str == '-' || *str == '+')
		return (0);
	while (str && *str && *str >= '0' && *str <= '9')
	{
		if (nb < 0 && sign == 1)
			return (-1);
		if (nb < 0 && sign == -1)
			return (0);
		nb = nb * 10 + *str - '0';
		str++;
	}
	if (str && *str == '.' && str && *(str + 1) >= '0' && *(str + 1) <= '9')
		nb += get_precision(str);
	return (nb * sign);
}
