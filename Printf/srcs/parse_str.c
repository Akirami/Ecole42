/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parse_str.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: emassard <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/12/02 19:14:48 by emassard     #+#   ##    ##    #+#       */
/*   Updated: 2019/12/09 08:36:20 by emassard    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

char
	*char_convert(char c)
{
	char *str;

	if (!(str = (char *)malloc(2 * sizeof(char))))
		return (NULL);
	str[1] = '\0';
	str[0] = c;
	return (str);
}

void
	write_str(t_flags *flags, char *str, t_count *counter)
{
	int i;
	int p_dec3;
	int arg_size2;

	i = 0;
	p_dec3 = flags->p_dec2;
	arg_size2 = flags->arg_size;
	while (flags->p_dec2 > 0 && !flags->minus)
	{
		(*str == '%' && flags->zero) ? ft_putchar_count('0',
			counter) : ft_putchar_count(' ', counter);
		flags->p_dec2--;
	}
	while (flags->p_len2 > 0)
	{
		ft_putchar_count(str[i], counter);
		i++;
		flags->p_len2--;
	}
	while (flags->minus && (p_dec3 > 0))
	{
		ft_putchar_count(' ', counter);
		p_dec3--;
	}
}

void
	set_offset_str(t_flags *flags, char *str, t_count *counter)
{
	flags->p_len = (flags->p_len < 0) ? ft_strlen(str) : flags->p_len;
	if (!flags->point)
	{
		flags->p_dec2 = flags->p_dec - flags->arg_size;
		flags->p_len2 = (flags->p_dec >= flags->arg_size)
			? flags->arg_size : flags->p_dec2;
		if (ft_strcmp(str, "(null"))
			flags->p_len2 = flags->arg_size;
	}
	else
	{
		flags->p_len2 = (flags->p_len > flags->arg_size)
			? flags->arg_size : flags->p_len;
		flags->p_dec2 = flags->p_dec - flags->p_len2;
	}
	if (*str == '%')
	{
		flags->p_len2 = 1;
		flags->p_dec2 -= ((flags->point && flags->p_len == 0) ? 1 : 0);
	}
	write_str(flags, str, counter);
}
