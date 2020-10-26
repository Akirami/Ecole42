/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parse_int.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: emassard <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/12/03 16:37:56 by emassard     #+#   ##    ##    #+#       */
/*   Updated: 2019/12/09 08:18:46 by emassard    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void
	write_int3(t_flags *flags, t_count *counter)
{
	if (!flags->is_write && !(flags->prec_zero
		&& (flags->value == 0 && flags->unsigned_value == 0))
		&& !(flags->prc_val_z && !flags->ptr))
	{
		if (flags->hexax)
		{
			ft_base_convert(flags->unsigned_value, HEXA_MINI, 16, counter);
		}
		else if (flags->hex)
			ft_base_convert(flags->unsigned_value, HEXA_MAJ, 16, counter);
		else if (flags->ptr)
		{
			ft_putstr_or_null("0x", counter);
			if (flags->unsigned_value || !flags->point)
				ft_base_convert(flags->unsigned_value, HEXA_MINI, 16, counter);
		}
		else if (flags->unsigned_int)
			ft_putnbr_unsigned(flags->unsigned_value, flags, counter);
		else
		{
			ft_putnbr_custom(flags->value, flags, counter);
		}
	}
	if (flags->prc_val_z && flags->p_dec != 0)
		ft_putchar_count(' ', counter);
}

void
	write_int2(t_flags *flags, t_count *counter)
{
	while (flags->p_dec2 > 0)
	{
		ft_putchar_count(' ', counter);
		flags->p_dec2--;
	}
	while (flags->p_len2 > 0 && !flags->is_write)
	{
		if (flags->value < 0)
		{
			ft_putchar_count('-', counter);
			flags->is_neg_p = 1;
			flags->value *= -1;
		}
		flags->p_zero = 1;
		ft_putchar_count('0', counter);
		flags->p_len2--;
	}
	while (flags->p_dec2 > 0 && flags->is_write)
	{
		ft_putchar_count(' ', counter);
		flags->p_dec2--;
	}
}

void
	write_int1(t_flags *flags, t_count *counter)
{
	if (flags->minus && (!(flags->prec_zero && flags->value == 0)
		|| (flags->unsigned_int && !flags->prec_zero) ||
		(flags->p_dec >= flags->arg_size && !flags->prc_val_z)))
	{
		while (flags->p_len2 > 0)
		{
			if (flags->value < 0)
			{
				ft_putchar_count('-', counter);
				flags->value *= -1;
			}
			flags->p_zero = 1;
			ft_putchar_count('0', counter);
			flags->p_len2--;
		}
		write_int15(flags, counter);
	}
}

void
	write_int(t_flags *flags, t_count *counter)
{
	(flags->p_len >= flags->arg_size && flags->value < 0) ? flags->p_len++ : 1;
	(flags->p_len - 1 >= flags->arg_size && flags->value <
		0) ? flags->p_dec++ : 1;
	flags->p_len2 += (flags->p_len >=
		flags->arg_size) ? flags->p_len - flags->arg_size : 0;
	flags->p_dec2 = flags->p_dec - (flags->prc_val_z ? 1 : flags->arg_size);
	flags->p_dec2 = (flags->p_dec < flags->p_len)
		? 0 : flags->p_dec2 - flags->p_len2;
	(flags->is_neg && flags->p_len2 > 0) ? flags->p_dec2-- : flags->is_neg;
	if (flags->p_dec2 > 0 && !flags->point && flags->zero && !flags->minus)
	{
		flags->p_len2 = flags->p_dec2;
		flags->p_dec2 = 0;
	}
	(flags->ptr) ? flags->p_dec2 -= 2 : flags->ptr;
	write_int1(flags, counter);
	write_int2(flags, counter);
	write_int3(flags, counter);
}

void
	set_offset_int(t_flags *flags, t_count *counter)
{
	((flags->prec_zero || flags->prec_zero_unsigned ||
		(flags->point && flags->p_len == 0)) && (flags->value == 0
		&& flags->unsigned_value == 0)) ? flags->prc_val_z = 1 : 1;
	(flags->value < 0) ? flags->is_neg = 1 : 1;
	if (flags->is_neg && ((flags->zero && flags->p_dec > 0 && !flags->point)
				|| ((flags->p_len - flags->arg_size) > 0 && (!(flags->p_dec -
					(flags->p_len - flags->arg_size) > 2) && flags->point))))
	{
		((flags->is_neg && !flags->point)) ? flags->arg_size++ : 1;
		flags->value *= -1;
		if (!flags->unsigned_int)
		{
			flags->is_neg_p = 1;
			ft_putchar_count('-', counter);
		}
	}
	(flags->value < 0) ? flags->p_len-- : flags->arg_size;
	(flags->value < 0) ? flags->p_dec-- : flags->arg_size;
	((flags->p_len - flags->arg_size >= 0) &&
		flags->prc_val_z) ? flags->p_len2++ : 1;
	((flags->p_dec - flags->arg_size - flags->p_len) >= 0 && flags->is_neg
		&& flags->point && flags->prc_val_z) ? flags->p_dec++ : 1;
	write_int(flags, counter);
}
