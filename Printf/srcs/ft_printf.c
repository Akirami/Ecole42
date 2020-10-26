/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: emassard <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/13 15:54:03 by emassard     #+#   ##    ##    #+#       */
/*   Updated: 2019/12/09 08:30:17 by emassard    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

char
	*count_int(char *str, t_flags *flags)
{
	char	*precision;
	int		i;
	int		prec_size;

	i = 0;
	if (str[0] == '0' && flags->point)
	{
		flags->prec_zero_unsigned = 1;
		flags->prec_zero = 1;
	}
	while (str[i] >= '0' && str[i] <= '9')
		i++;
	precision = ft_strsub(str, 0, i);
	prec_size = ft_atoi(precision);
	free(precision);
	if (flags->point == 0)
		flags->p_dec = prec_size;
	else
		flags->p_len = prec_size;
	str = &(*(str + i - 1));
	return (&(*(str)));
}

char
	*inspect_next(char *st, va_list params2, t_flags *flags, t_count *counter)
{
	while (!ft_strchr("disxcu%Xp", *st))
	{
		(*st == '-') ? flags->minus = 1 : *st;
		(*st == '.') ? flags->point = 1 : *st;
		if (*st == '*' && !flags->star)
		{
			if (flags->point)
				flags->p_len = my_test_star(flags, va_arg(params2, int));
			else
				flags->p_dec = my_test_star(flags, va_arg(params2, int));
			flags->star = 1;
		}
		else if (*st == '*')
			flags->p_len = my_test_star(flags, va_arg(params2, int));
		(*st == '0' && !flags->point) ? flags->zero = 1 : *st;
		(*st >= '0' && *st <= '9') ? (st = count_int(&(*st), flags)) : st;
		if (!ft_strchr("disxcu%Xp", *st))
			st++;
		else
			break ;
	}
	set_args_type1(&(*st), flags, params2, counter);
	return (&(*(st)));
}

char
	*check_args(char *str, va_list params2, t_flags *flags, t_count *counter)
{
	if (*str == 's')
		ft_putstr_or_null(va_arg(params2, char *), counter);
	else if (*str == '%')
		ft_putchar_count('%', counter);
	else if (*str == '#')
		ft_putstr_or_null("0x", counter);
	else if (*str == 'x')
		ft_base_convert(va_arg(params2, unsigned int), HEXA_MINI, 16, counter);
	else if (*str == 'X')
		ft_base_convert(va_arg(params2, unsigned int), HEXA_MAJ, 16, counter);
	else if (*str == 'p')
		ft_base_p_convert(va_arg(params2, uint64_t), HEXA_MINI, 16, counter);
	else if (*str == 'c')
		ft_putchar_count(va_arg(params2, unsigned int), counter);
	else if (*str == 'u')
		ft_putnbr_unsigned(va_arg(params2, unsigned int), flags, counter);
	else if (*str == 'i' || *str == 'd')
		ft_putnbr_custom(va_arg(params2, int64_t), flags, counter);
	else if (*str == '-' || *str == '.' || *str == '*' || *str == '0')
		str = inspect_next(&(*str), params2, flags, counter);
	else if (*str >= '0' && *str <= '9')
		str = inspect_next(&(*str), params2, flags, counter);
	return (&(*str));
}

int
	free_all(char *str, t_count *counter, va_list params)
{
	int i;

	i = counter->count;
	free(str);
	free(counter);
	va_end(params);
	return (i);
}

int
	ft_printf(const char *str, ...)
{
	char	*str2;
	char	*str3;
	va_list params;
	t_flags *flags;
	t_count *counter;

	new_counter(&counter);
	str2 = ft_strdup(str);
	str3 = str2;
	va_start(params, str);
	while (str2 && *str2)
	{
		if (*str2 == '%')
		{
			str2++;
			flags = new_struct(flags);
			str2 = check_args(&(*str2), params, flags, counter);
			free(flags);
		}
		else
			ft_putchar_count(*str2, counter);
		str2++;
	}
	return (free_all(str3, counter, params));
}
