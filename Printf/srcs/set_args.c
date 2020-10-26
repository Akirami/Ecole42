/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   set_args.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: emassard <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/12/09 08:28:26 by emassard     #+#   ##    ##    #+#       */
/*   Updated: 2019/12/09 08:28:29 by emassard    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void
	write_int15(t_flags *flags, t_count *counter)
{
	if (flags->hexax)
	{
		if (!flags->prc_val_z)
			ft_base_convert(flags->unsigned_value, HEXA_MINI, 16, counter);
	}
	else if (flags->hex)
	{
		if (!flags->prc_val_z)
			ft_base_convert(flags->unsigned_value, HEXA_MAJ, 16, counter);
	}
	else if (flags->ptr)
	{
		ft_putstr_or_null("0x", counter);
		if (!flags->prc_val_z)
			ft_base_convert(flags->unsigned_value, HEXA_MINI, 16, counter);
	}
	else if (flags->unsigned_int)
	{
		if (!flags->prc_val_z)
			ft_putnbr_unsigned(flags->unsigned_value, flags, counter);
	}
	else if (!flags->prc_val_z)
		ft_putnbr_custom(flags->value, flags, counter);
	flags->is_write = 1;
}

void
	set_args_type3(char *str, t_flags *flags, va_list params2, t_count *counter)
{
	char *str_arg;

	str_arg = NULL;
	if (*str == 'p')
		flags->unsigned_value = va_arg(params2, size_t);
	else if (*str == 'x' || *str == 'X')
		flags->unsigned_value = va_arg(params2, unsigned int);
	flags->unsigned_int = 1;
	(*str == 'x') ? flags->hexax = 1 : *str;
	(*str == 'X') ? flags->hex = 1 : *str;
	(*str == 'p') ? flags->ptr = 1 : *str;
	if (*str == 'x' || *str == 'X' || *str == 'p')
	{
		str_arg = ft_hexa(flags->unsigned_value, HEXA_MINI, 16);
		if (str_arg == NULL)
			str_arg = "(null)";
		else
		{
			flags->arg_size = (int)ft_strlen(str_arg) + 1;
			free(str_arg);
		}
		set_offset_int(flags, counter);
	}
}

void
	set_args_type2(char *str, t_flags *flags, va_list params2, t_count *counter)
{
	char *str_arg;

	str_arg = NULL;
	if (*str == 's' || *str == 'c' || *str == '%')
	{
		(*str == '%') ? str_arg = "%" : str_arg;
		if (*str == 'c')
			str_arg = char_convert(va_arg(params2, unsigned int));
		(*str == 's') ? str_arg = va_arg(params2, char *) : str_arg;
		(str_arg == NULL) ? str_arg = "(null)" : str_arg;
		if (*str == 'c')
			flags->arg_size = 1;
		else
			flags->arg_size = (int)ft_strlen(str_arg);
		set_offset_str(flags, str_arg, counter);
		if (*str == 'c')
			free(str_arg);
	}
	set_args_type3(str, flags, params2, counter);
}

void
	set_args_type1(char *str, t_flags *flags, va_list params2, t_count *counter)
{
	if (*str == 'd' || *str == 'i' || *str == 'u')
	{
		if (*str == 'u')
		{
			flags->unsigned_value = va_arg(params2, unsigned int);
			flags->unsigned_int = 1;
			flags->arg_size = size_unsigned(flags->unsigned_value) + 1;
		}
		else
		{
			flags->value = va_arg(params2, int);
			flags->arg_size = size_int(flags->value) + 1;
		}
		set_offset_int(flags, counter);
	}
	set_args_type2(str, flags, params2, counter);
}
